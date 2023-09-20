/***************************************************************************

    fileio.c - file access functions

***************************************************************************/
#include <stdlib.h>

#include <zlib.h>
#include <windows.h>
#include <ctype.h>
#include <tchar.h>

#include <assert.h>
#include "winui.h"
#include "hash_ek.h"
#include "fileio_ek.h"
#include "unzip_ek.h"
//#include "winalloc_ek.h"

#include <locale.h>
#include <wchar.h>

#ifdef MESS
#include "image.h"
#endif


/***************************************************************************
    DEBUGGING
***************************************************************************/

/* Verbose outputs to error.log ? */
#define VERBOSE 					0

/* enable lots of logging */
#if VERBOSE
#define LOG(x)	logerror x
#else
#define LOG(x)
#endif

#ifdef UNICODE
#define appendstring(dest,src)	wsprintf((dest) + wcslen(dest), TEXT("%S"), (src))
#else
#define appendstring(dest,src)	strcat((dest), (src))
#endif // UNICODE

#define _appendstring(dest,src)	strcat((dest), (src))


/***************************************************************************
    CONSTANTS
***************************************************************************/

#define PLAIN_FILE				0
#define RAM_FILE				1
#define ZIPPED_FILE				2
#define UNLOADED_ZIPPED_FILE	3

#define FILEFLAG_OPENREAD		0x0001
#define FILEFLAG_OPENWRITE		0x0002
#define FILEFLAG_HASH			0x0100
#define FILEFLAG_REVERSE_SEARCH	0x0200
#define FILEFLAG_VERIFY_ONLY	0x0400
#define FILEFLAG_NOZIP			0x0800
#define FILEFLAG_MUST_EXIST		0x1000

#ifdef MESS
#define FILEFLAG_ALLOW_ABSOLUTE	0x2000
#define FILEFLAG_ZIP_PATHS		0x4000
#define FILEFLAG_CREATE_GAMEDIR	0x8000
#define FILEFLAG_GHOST			0x0004
#endif

#ifdef MAME_DEBUG
#define DEBUG_COOKIE			0xbaadf00d
#endif


#define FILE_BUFFER_SIZE	256
#define MAX_OPEN_FILES		16

/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/
struct pathdata
{
	const char *rawpath;
	const char **path;
	int pathcount;
};

struct _osd_file
{
	HANDLE		handle;
	u64		filepos;
	u64		end;
	u64		offset;
	u64		bufferbase;
	DWORD	bufferbytes;
	u8		buffer[FILE_BUFFER_SIZE];
};


static struct pathdata pathlist[FILETYPE_end];
static osd_files openfiles[MAX_OPEN_FILES];

char *rompath_extra;

struct _mame_file
{
#ifdef DEBUG_COOKIE
	u32 debug_cookie;
#endif
	osd_files *file;
	u8 *data;
	u64 offset;
	u64 length;
	u8 eof;
	u8 type;
	char hash[HASH_BUF_SIZE];
	int back_char; /* Buffered char for unget. EOF for empty. */
};

/***************************************************************************
    GLOBALS
***************************************************************************/

#ifdef MESS
int mess_ghost_images;
#endif


/***************************************************************************
    PROTOTYPES
***************************************************************************/

static mame_file *generic_fopen(int pathtype, const char *gamename, const char *filename, const char* hash, UINT32 flags);
static const char *get_extension_for_filetype(int filetype);
static int checksum_file(int pathtype, int pathindex, const char *file, u8 **p, u64 *size, char* hash);


//============================================================
//	osd_die
//============================================================

void CLIB_DECL osd_die(const char *text,...)
{
	va_list arg;

	/* standard vfprintf stuff here */
	va_start(arg, text);
//	vlogerror(text, arg);
	vprintf(text, arg);
	va_end(arg);

	exit(-1);
}

//============================================================
//	is_pathsep
//============================================================

inline int is_pathsep(TCHAR c)
{
	return (c == '/' || c == '\\' || c == ':');
}

//============================================================
//	find_reverse_path_sep
//============================================================

static TCHAR *find_reverse_path_sep(TCHAR *name)
{
	TCHAR *p = name + _tcslen(name) - 1;
	while (p >= name && !is_pathsep(*p))
		p--;
	return (p >= name) ? p : NULL;
}

//============================================================
//	create_path
//============================================================

static void create_path(TCHAR *path, int has_filename)
{
	TCHAR *sep = find_reverse_path_sep(path);
	DWORD attributes;

	/* if there's still a separator, and it's not the root, nuke it and recurse */
	if (sep && sep > path && !is_pathsep(sep[-1]))
	{
		*sep = 0;
		create_path(path, 0);
		*sep = '\\';
	}

	/* if we have a filename, we're done */
	if (has_filename)
		return;

	/* if the path already exists, we're done */
	attributes = GetFileAttributes(path);
	if (attributes != INVALID_FILE_ATTRIBUTES)
		return;

	/* create the path */
	CreateDirectory(path, NULL);
}

//============================================================
//	is_variablechar
//============================================================

inline int is_variablechar(char c)
{
	return (isalnum(c) || c == '_' || c == '-');
}

//============================================================
//	parse_variable
//============================================================

static const char *parse_variable(const char **start, const char *end)
{
	const char *src = *start, *var;
	char variable[1024];
	char *dest = variable;

	/* copy until we hit the end or until we hit a non-variable character */
	for (src = *start; src < end && is_variablechar(*src); src++)
		*dest++ = *src;

	// an empty variable means "$" and should not be expanded
	if(src == *start)
		return("$");

	/* NULL terminate and return a pointer to the end */
	*dest = 0;
	*start = src;

	/* return the actual variable value */
	var = getenv(variable);
	return (var) ? var : "";
}

//============================================================
//	copy_and_expand_variables
//============================================================

static char *copy_and_expand_variables(const char *path, int len)
{
	char *dst, *result;
	const char *src;
	int length = 0;

	/* first determine the length of the expanded string */
	for (src = path; src < path + len; )
		if (*src++ == '$')
			length += strlen(parse_variable(&src, path + len));
		else
			length++;

	/* allocate a string of the appropriate length */
	result = (char *)malloc(length + 1);
	if (!result)
		goto out_of_memory;

	/* now actually generate the string */
	for (src = path, dst = result; src < path + len; )
	{
		char c = *src++;
		if (c == '$')
			dst += sprintf(dst, "%s", parse_variable(&src, path + len));
		else
			*dst++ = c;
	}

	/* NULL terminate and return */
	*dst = 0;
	return result;

out_of_memory:
	osd_die("Out of memory in variable expansion!\n");

	return 0;
}

//============================================================
//	expand_pathlist
//============================================================

static void expand_pathlist(struct pathdata *list)
{
	const char *rawpath = (list->rawpath) ? list->rawpath : "";
	const char *token;

#if VERBOSE
	printf("Expanding: %s\n", rawpath);
#endif

	// free any existing paths
	if (list->pathcount != 0)
	{
		int pathindex;

		for (pathindex = 0; pathindex < list->pathcount; pathindex++)
			free((void *)list->path[pathindex]);
		free(list->path);
	}

	// by default, start with an empty list
	list->path = NULL;
	list->pathcount = 0;

	// look for separators
	token = strchr(rawpath, ';');
	if (!token)
		token = rawpath + strlen(rawpath);

	// loop until done
	while (1)
	{
		// allocate space for the new pointer
		list->path = (const char **)realloc(list->path, (list->pathcount + 1) * sizeof(char *));
		if (!list->path)
			goto out_of_memory;

		// copy the path in
		list->path[list->pathcount++] = copy_and_expand_variables(rawpath, token - rawpath);
#if VERBOSE
		printf("  %s\n", list->path[list->pathcount - 1]);
#endif

		// if this was the end, break
		if (*token == 0)
			break;
		rawpath = token + 1;

		// find the next separator
		token = strchr(rawpath, ';');
		if (!token)
			token = rawpath + strlen(rawpath);
	}

	// when finished, reset the path info, so that future INI parsing will
	// cause us to get called again
	free((void *)list->rawpath);
	list->rawpath = NULL;
	return;

out_of_memory:
	osd_die("Out of memory!\n");
}

//============================================================
//	get_path_for_filetype
//============================================================

const char *get_path_for_filetype(int filetype, int pathindex, DWORD *count)
{
	struct pathdata *list;

	if( filetype >= FILETYPE_end ) {
		return "";
	}


	// handle aliasing of some paths
	switch (filetype)
	{
#ifndef MESS
		case FILETYPE_IMAGE:
			list = &pathlist[FILETYPE_ROM];
			break;
#endif

		default:
			list = &pathlist[filetype];
			break;
	}

	// if we don't have expanded paths, expand them now
	if (list->pathcount == 0 || list->rawpath)
	{
		// special hack for ROMs
		if (list == &pathlist[FILETYPE_ROM] && rompath_extra)
		{
			// this may leak a little memory, but it's a hack anyway! :-P
			const char *rawpath = (list->rawpath) ? list->rawpath : "";
			char *newpath = (char *)malloc(strlen(rompath_extra) + strlen(rawpath) + 2);
			sprintf(newpath, "%s;%s", rompath_extra, rawpath);
			free((void *)list->rawpath);
			list->rawpath = newpath;
		}

		// decompose the path
		expand_pathlist(list);
	}

	// set the count
	if (count)
		*count = list->pathcount;

	// return a valid path always
	return (pathindex < list->pathcount) ? list->path[pathindex] : "";
}

//============================================================
//	compose_path
//============================================================

void compose_path(TCHAR *output, int pathtype, int pathindex, const char *filename)
{
	const char *basepath = get_path_for_filetype(pathtype, pathindex, NULL);
	TCHAR *p;

	/* compose the full path */
	*output = 0;
	if (basepath)
		appendstring(output, basepath);
	if (*output && !is_pathsep(output[_tcslen(output) - 1]))
		appendstring(output, "\\");
	appendstring(output, filename);

	/* convert forward slashes to backslashes */
	for (p = output; *p; p++)
		if (*p == '/')
			*p = '\\';

}

void osd_compose_path(char *output, int pathtype, int pathindex, const char *filename)
{
	const char *basepath = get_path_for_filetype(pathtype, pathindex, NULL);
	char *p;

	/* compose the full path */
	*output = 0;
	if (basepath)
		_appendstring(output, basepath);
	if (*output && !is_pathsep(output[strlen(output) - 1]))
		_appendstring(output, "\\");
	_appendstring(output, filename);

	/* convert forward slashes to backslashes */
	for (p = output; *p; p++)
		if (*p == '/')
			*p = '\\';


#if 0
	FILE *fppp;
	fppp=fopen("fullpath.txt","a+t");
	fprintf(fppp, "<fullpath %s : basepath %s> \n", output, basepath );
	fclose(fppp);
#endif

		
}

//============================================================
//	osd_get_path_info
//============================================================
extern char rom_path[MAX_DIRS][MAX_PATH];
int osd_get_path_info(int pathtype, int pathindex, const char *filename)
{
	char fullpath[1024];
	DWORD attributes;
	int returnvalue;
	
	/* compose the full path */
//	compose_path(fullpath, pathtype, pathindex, filename);
	snprintf(fullpath, WINUI_ARRAY_LENGTH(fullpath), "%s\\%s", rom_path[pathindex], filename);


	/* get the file attributes */
	attributes = GetFileAttributesA(fullpath);
	if (attributes == INVALID_FILE_ATTRIBUTES)
		returnvalue= PATH_NOT_FOUND;
	else if (attributes & FILE_ATTRIBUTE_DIRECTORY)
		returnvalue= PATH_IS_DIRECTORY;
	else
		returnvalue= PATH_IS_FILE;

	return returnvalue;
}

//============================================================
//	osd_fread
//============================================================

UINT32 osd_fread(osd_files *file, void *buffer, UINT32 length)
{
	UINT32 bytes_left = length;
	int bytes_to_copy;
	DWORD result;

	// handle data from within the buffer
	if (file->offset >= file->bufferbase && file->offset < file->bufferbase + file->bufferbytes)
	{
		// copy as much as we can
		bytes_to_copy = file->bufferbase + file->bufferbytes - file->offset;
		if (bytes_to_copy > length)
			bytes_to_copy = length;
		memcpy(buffer, &file->buffer[file->offset - file->bufferbase], bytes_to_copy);

		// account for it
		bytes_left -= bytes_to_copy;
		file->offset += bytes_to_copy;
		buffer = (u8 *)buffer + bytes_to_copy;

		// if that's it, we're done
		if (bytes_left == 0)
			return length;
	}

	// attempt to seek to the current location if we're not there already
	if (file->offset != file->filepos)
	{
		LONG upperPos = file->offset >> 32;
		result = SetFilePointer(file->handle, (UINT32)file->offset, &upperPos, FILE_BEGIN);
		if (result == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
		{
			file->filepos = ~0;
			return length - bytes_left;
		}
		file->filepos = file->offset;
	}

	// if we have a small read remaining, do it to the buffer and copy out the results
	if (length < FILE_BUFFER_SIZE/2)
	{
		// read as much of the buffer as we can
		file->bufferbase = file->offset;
		file->bufferbytes = 0;
		ReadFile(file->handle, file->buffer, FILE_BUFFER_SIZE, &file->bufferbytes, NULL);
		file->filepos += file->bufferbytes;

		// copy it out
		bytes_to_copy = bytes_left;
		if (bytes_to_copy > file->bufferbytes)
			bytes_to_copy = file->bufferbytes;
		memcpy(buffer, file->buffer, bytes_to_copy);

		// adjust pointers and return
		file->offset += bytes_to_copy;
		bytes_left -= bytes_to_copy;
		return length - bytes_left;
	}

	// otherwise, just read directly to the buffer
	else
	{
		// do the read
		ReadFile(file->handle, buffer, bytes_left, &result, NULL);
		file->filepos += result;

		// adjust the pointers and return
		file->offset += result;
		bytes_left -= result;
		return length - bytes_left;
	}
}

//============================================================
//	osd_fopen
//============================================================

osd_files *osd_fopen(int pathtype, int pathindex, const char *filename, const char *mode)
{
	DWORD disposition = 0, access = 0, sharemode = 0, flags = 0;
	TCHAR fullpath[1024];
	DWORD upperPos = 0;
	osd_files *file;
	int i;
	const TCHAR *s;
	TCHAR temp_dir[1024];
	TCHAR temp_file[MAX_PATH];

	temp_file[0] = '\0';

	/* find an empty file handle */
	for (i = 0; i < MAX_OPEN_FILES; i++)
		if (openfiles[i].handle == NULL || openfiles[i].handle == INVALID_HANDLE_VALUE)
			break;
	if (i == MAX_OPEN_FILES)
		goto error;

	/* zap the file record */
	file = &openfiles[i];
	memset(file, 0, sizeof(*file));

	/* convert the mode into disposition and access */
	if (strchr(mode, 'r'))
		disposition = OPEN_EXISTING, access = GENERIC_READ, sharemode = FILE_SHARE_READ;
	if (strchr(mode, 'w'))
		disposition = CREATE_ALWAYS, access = GENERIC_WRITE, sharemode = 0;
	if (strchr(mode, '+'))
		access = GENERIC_READ | GENERIC_WRITE;

	/* compose the full path */
	compose_path(fullpath, pathtype, pathindex, filename);

	/* if 'g' is specified, we 'ghost' our changes; in other words any changes
	 * made to the file last only as long as the file is open.  Under the hood
	 * this is implemented by using a temporary file */
	if (strchr(mode, 'g'))
	{
		GetTempPath(sizeof(temp_dir) / sizeof(temp_dir[0]), temp_dir);
		GetTempFileName(temp_dir, TEXT("tmp"), 0, temp_file);

		if (!CopyFile(fullpath, temp_file, FALSE))
			goto error;

		s = temp_file;
		flags |= FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE;
	}
	else
	{
		s = fullpath;
	}

	/* attempt to open the file */
	file->handle = CreateFile(s, access, sharemode, NULL, disposition, 0, NULL);
	if (file->handle == INVALID_HANDLE_VALUE)
	{
		DWORD error = GetLastError();

		/* if it's read-only, or if the path exists, then that's final */
		if (!(access & GENERIC_WRITE) || error != ERROR_PATH_NOT_FOUND)
			goto error;

		/* create the path and try again */
		create_path(fullpath, 1);
		file->handle = CreateFile(fullpath, access, sharemode, NULL, disposition, flags, NULL);

		/* if that doesn't work, we give up */
		if (file->handle == INVALID_HANDLE_VALUE)
			goto error;
	}

	/* get the file size */
	file->end = GetFileSize(file->handle, &upperPos);
	file->end |= (u64)upperPos << 32;
	return file;

error:
	if (temp_file[0])
		DeleteFile(temp_file);
	return NULL;
}


//============================================================
//	osd_fseek
//============================================================

int osd_fseek(osd_files *file, INT64 offset, int whence)
{
	/* convert the whence into method */
	switch (whence)
	{
		default:
		case SEEK_SET:	file->offset = offset;				break;
		case SEEK_CUR:	file->offset += offset;				break;
		case SEEK_END:	file->offset = file->end + offset;	break;
	}
	return 0;
}


//============================================================
//	osd_fclose
//============================================================

void osd_fclose(osd_files *file)
{
	// close the handle and clear it out
	if (file->handle)
		CloseHandle(file->handle);
	file->handle = NULL;
}

//============================================================
//	osd_ftell
//============================================================

UINT64 osd_ftell(osd_files *file)
{
	return file->offset;
}

//============================================================
//	osd_fwrite
//============================================================

UINT32 osd_fwrite(osd_files *file, const void *buffer, UINT32 length)
{
	LONG upperPos;
	DWORD result;

	// invalidate any buffered data
	file->bufferbytes = 0;

	// attempt to seek to the current location
	upperPos = file->offset >> 32;
	result = SetFilePointer(file->handle, (UINT32)file->offset, &upperPos, FILE_BEGIN);
	if (result == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
		return 0;

    // do the write
    WriteFile(file->handle, buffer, length, &result, NULL);
    file->filepos = file->offset + result;

	// adjust the pointers
	file->offset += result;
	if (file->offset > file->end)
		file->end = file->offset;
	return result;
}


//============================================================
//	osd_feof
//============================================================

int osd_feof(osd_files *file)
{
	return (file->offset >= file->end);
}


/***************************************************************************
    compose_path
***************************************************************************/

inline void compose_path(char *output, const char *gamename, const char *filename, const char *extension)
{
	char *filename_base = output;
	*output = 0;

#ifdef MESS
	if (filename && osd_is_absolute_path(filename))
	{
		strcpy(output, filename);
		return;
	}
#endif

	/* if there's a gamename, add that; only add a '/' if there is a filename as well */
	if (gamename)
	{
		strcat(output, gamename);
		if (filename)
		{
			strcat(output, "/");
			filename_base = &output[strlen(output)];
		}
	}

	/* if there's a filename, add that */
	if (filename)
		strcat(output, filename);

	/* if there's no extension in the filename, add the extension */
	if (extension && !strchr(filename_base, '.'))
	{
		strcat(output, ".");
		strcat(output, extension);
	}
}

/***************************************************************************
    mame_fopen
***************************************************************************/

mame_file *mame_fopen(const char *gamename, const char *filename, int filetype, int openforwrite)
{
#ifdef KAILLERA
	extern int kPlay;

	if (kPlay)
	{
		switch (filetype)
		{
			case FILETYPE_NVRAM:
			case FILETYPE_MEMCARD:
			case FILETYPE_HIGHSCORE:
			case FILETYPE_HIGHSCORE_DB:
			return NULL;
		}
	}
#endif

	/* first verify that we aren't trying to open read-only types as writeables */
	switch (filetype)
	{
		/* read-only cases */
		case FILETYPE_ROM:
#ifndef MESS
		case FILETYPE_IMAGE:
#endif
		case FILETYPE_SAMPLE:
		case FILETYPE_HIGHSCORE_DB:
		case FILETYPE_ARTWORK:
		case FILETYPE_HISTORY:
		case FILETYPE_LANGUAGE:
		case FILETYPE_CTRLR:
#ifndef MESS
		case FILETYPE_INI:
#endif
			if (openforwrite)
			{
//				logerror("mame_fopen: type %02x write not supported\n", filetype);
				return NULL;
			}
			break;
			
#ifdef LOG_WAV
		case FILETYPE_WAVE:
#endif /*LOG_WAV*/	

		/* write-only cases */
		case FILETYPE_SCREENSHOT:
			if (!openforwrite)
			{
//				logerror("mame_fopen: type %02x read not supported\n", filetype);
				return NULL;
			}
			break;
	}

	/* now open the file appropriately */
	switch (filetype)
	{
		/* ROM files */
		case FILETYPE_ROM:
			return generic_fopen(filetype, gamename, filename, 0, FILEFLAG_OPENREAD | FILEFLAG_HASH);

		/* read-only disk images */
		case FILETYPE_IMAGE:
#ifndef MESS
			return generic_fopen(filetype, gamename, filename, 0, FILEFLAG_OPENREAD | FILEFLAG_NOZIP);
#else
			{
				int flags = FILEFLAG_ALLOW_ABSOLUTE;
				switch(openforwrite) {
				case OSD_FOPEN_READ:
					flags |= FILEFLAG_OPENREAD | FILEFLAG_ZIP_PATHS;
					break;
				case OSD_FOPEN_WRITE:
					flags |= FILEFLAG_OPENWRITE;
					break;
				case OSD_FOPEN_RW:
					flags |= FILEFLAG_OPENREAD | FILEFLAG_OPENWRITE | FILEFLAG_MUST_EXIST;
					break;
				case OSD_FOPEN_RW_CREATE:
					flags |= FILEFLAG_OPENREAD | FILEFLAG_OPENWRITE;
					break;
				}
				if (mess_ghost_images)
					flags |= FILEFLAG_GHOST;

				return generic_fopen(filetype, gamename, filename, 0, flags);
			}
#endif

		/* differencing disk images */
		case FILETYPE_IMAGE_DIFF:
			return generic_fopen(filetype, gamename, filename, 0, FILEFLAG_OPENREAD | FILEFLAG_OPENWRITE);

		/* samples */
		case FILETYPE_SAMPLE:
			return generic_fopen(filetype, gamename, filename, 0, FILEFLAG_OPENREAD);

		/* artwork files */
		case FILETYPE_ARTWORK:
			return generic_fopen(filetype, gamename, filename, 0, FILEFLAG_OPENREAD);

		/* NVRAM files */
		case FILETYPE_NVRAM:
#ifdef MESS
			if (filename)
				return generic_fopen(filetype, gamename, filename, 0, openforwrite ? FILEFLAG_OPENWRITE | FILEFLAG_CREATE_GAMEDIR : FILEFLAG_OPENREAD);
#endif
			return generic_fopen(filetype, NULL, gamename, 0, openforwrite ? FILEFLAG_OPENWRITE : FILEFLAG_OPENREAD);

		/* high score files */
		case FILETYPE_HIGHSCORE:
//			if (!mame_highscore_enabled())
//				return NULL;
			return generic_fopen(filetype, NULL, gamename, 0, openforwrite ? FILEFLAG_OPENWRITE : FILEFLAG_OPENREAD);

		/* highscore database */
		case FILETYPE_HIGHSCORE_DB:
			return generic_fopen(filetype, NULL, filename, 0, FILEFLAG_OPENREAD);

		/* config files */
		case FILETYPE_CONFIG:
			return generic_fopen(filetype, NULL, gamename, 0, openforwrite ? FILEFLAG_OPENWRITE : FILEFLAG_OPENREAD);

		/* input logs */
		case FILETYPE_INPUTLOG:
#ifdef KAILLERA
			return generic_fopen(filetype, gamename, filename, 0, openforwrite ? FILEFLAG_OPENWRITE : FILEFLAG_OPENREAD);

		case FILETYPE_INPUTLOG2:
			return generic_fopen(filetype, gamename, filename, 0, openforwrite ? FILEFLAG_OPENWRITE : FILEFLAG_OPENREAD);
#else
			return generic_fopen(filetype, NULL, gamename, 0, openforwrite ? FILEFLAG_OPENWRITE : FILEFLAG_OPENREAD);
#endif

		/* save state files */
		case FILETYPE_STATE:
#ifndef MESS
			return generic_fopen(filetype, NULL, filename, 0, openforwrite ? FILEFLAG_OPENWRITE : FILEFLAG_OPENREAD);
#else
			return generic_fopen(filetype, NULL, filename, 0, FILEFLAG_ALLOW_ABSOLUTE | (openforwrite ? FILEFLAG_OPENWRITE : FILEFLAG_OPENREAD));
#endif

		/* memory card files */
		case FILETYPE_MEMCARD:
			return generic_fopen(filetype, NULL, filename, 0, openforwrite ? FILEFLAG_OPENWRITE : FILEFLAG_OPENREAD);

#ifdef LOG_WAV
		/* wave files */
		case FILETYPE_WAVE:
			return generic_fopen(filetype, NULL, filename, 0, FILEFLAG_OPENWRITE);
#endif /*LOG_WAV*/

		/* screenshot files */
		case FILETYPE_SCREENSHOT:
#ifndef MESS
			return generic_fopen(filetype, NULL, filename, 0, FILEFLAG_OPENWRITE);
#else
			return generic_fopen(filetype, NULL, filename, 0, FILEFLAG_ALLOW_ABSOLUTE | FILEFLAG_OPENWRITE);
#endif

		/* history files */
		case FILETYPE_HISTORY:
#ifndef MESS
			return generic_fopen(filetype, NULL, filename, 0, FILEFLAG_OPENREAD);
#else
			return generic_fopen(filetype, NULL, filename, 0, FILEFLAG_ALLOW_ABSOLUTE | FILEFLAG_OPENREAD);
#endif

		/* cheat file */
		case FILETYPE_CHEAT:
			return generic_fopen(filetype, NULL, filename, 0, FILEFLAG_OPENREAD | (openforwrite ? FILEFLAG_OPENWRITE : 0));

		/* language file */
		case FILETYPE_LANGUAGE:
			return generic_fopen(filetype, NULL, filename, 0, FILEFLAG_OPENREAD);

		/* ctrlr files */
		case FILETYPE_CTRLR:
			return generic_fopen(filetype, NULL, filename, 0, FILEFLAG_OPENREAD);

		/* game specific ini files */
		case FILETYPE_INI:
#ifndef MESS
			return generic_fopen(filetype, NULL, gamename, 0, FILEFLAG_OPENREAD);
#else
			return generic_fopen(filetype, NULL, gamename, 0, openforwrite ? FILEFLAG_OPENWRITE : FILEFLAG_OPENREAD);
#endif

#ifdef MESS
		/* CRC files */
		case FILETYPE_HASH:
			return generic_fopen(filetype, NULL, gamename, 0, openforwrite ? FILEFLAG_OPENWRITE : FILEFLAG_OPENREAD);
#endif

		/* anything else */
		default:
//			logerror("mame_fopen(): unknown filetype %02x\n", filetype);
			return NULL;
	}
	return NULL;
}


/***************************************************************************
    mame_fopen_rom
***************************************************************************/

/* Similar to mame_fopen(,,FILETYPE_ROM), but lets you specify an expected checksum
   (better encapsulation of the load by CRC used for ZIP files) */
mame_file *mame_fopen_rom(const char *gamename, const char *filename, const char* exphash)
{
	return generic_fopen(FILETYPE_ROM, gamename, filename, exphash, FILEFLAG_OPENREAD | FILEFLAG_HASH);
}


/***************************************************************************
    mame_fclose
***************************************************************************/

void mame_fclose(mame_file *file)
{
#ifdef DEBUG_COOKIE
	assert(file->debug_cookie == DEBUG_COOKIE);
	file->debug_cookie = 0;
#endif

	/* switch off the file type */
	switch (file->type)
	{
		case PLAIN_FILE:
			osd_fclose(file->file);
			break;

		case ZIPPED_FILE:
		case RAM_FILE:
			if (file->data)
				free(file->data);
			break;
	}

	/* free the file data */
	free(file);
}

//============================================================
//	osd_get_path_count
//============================================================

int osd_get_path_count(int pathtype)
{
	DWORD count=0;
	const char *path=NULL;
	char name[256];	

	/* get the count and return it */
	path = get_path_for_filetype(pathtype, 0, &count);
#if 1
	FILE *fpp;
	fpp=fopen("osd_get_path_count.txt","a+t");
	sprintf(name, "%s", path);
	fprintf(fpp,"path %s count %d\n",name,(int)count);
	fclose(fpp);
#endif	
	return count;
}

/***************************************************************************
    mame_faccess
***************************************************************************/
extern int num_path;

int mame_faccess(const char *filename, int filetype)
{
//	const char *extension = get_extension_for_filetype(filetype);
//	int pathcount = osd_get_path_count(filetype);
	const char *extension = NULL;

	char modified_filename[256];
	int pathindex;
	
	/* copy the filename and add an extension */
	strcpy(modified_filename, filename);
	if (extension)
	{
		char *p = strchr(modified_filename, '.');
		if (p)
			strcpy(p, extension);
		else
		{
			strcat(modified_filename, ".");
			strcat(modified_filename, extension);
		}
	}


	/* loop over all paths */
	for (pathindex = 0; pathindex < num_path; pathindex++)
	{
		char name[256];

		/* first check the raw filename, in case we're looking for a directory */
		sprintf(name, "%s", filename);
		if (osd_get_path_info(filetype, pathindex, name) != PATH_NOT_FOUND)
			return 1;

		/* try again with a .zip extension */
		sprintf(name, "%s.zip", filename);
		if (osd_get_path_info(filetype, pathindex, name) != PATH_NOT_FOUND)
			return 1;

		/* does such a directory (or file) exist? */
		sprintf(name, "%s", modified_filename);
		if (osd_get_path_info(filetype, pathindex, name) != PATH_NOT_FOUND)
			return 1;

	}

	/* no match */
	return 0;
}

/***************************************************************************
    mame_fread
***************************************************************************/

UINT32 mame_fread(mame_file *file, void *buffer, UINT32 length)
{
	/* flush any buffered char */
	file->back_char = EOF;

	/* switch off the file type */
	switch (file->type)
	{
		case PLAIN_FILE:
			return osd_fread(file->file, buffer, length);

		case ZIPPED_FILE:
		case RAM_FILE:
			if (file->data)
			{
				if (file->offset + length > file->length)
				{
					length = file->length - file->offset;
					file->eof = 1;
				}
				memcpy(buffer, file->data + file->offset, length);
				file->offset += length;
				return length;
			}
			break;
	}

	return 0;
}



/***************************************************************************
    mame_fwrite
***************************************************************************/

UINT32 mame_fwrite(mame_file *file, const void *buffer, UINT32 length)
{
	/* flush any buffered char */
	file->back_char = EOF;

	/* switch off the file type */
	switch (file->type)
	{
		case PLAIN_FILE:
			return osd_fwrite(file->file, buffer, length);
	}

	return 0;
}



/***************************************************************************
    mame_fseek
***************************************************************************/

int mame_fseek(mame_file *file, INT64 offset, int whence)
{
	int err = 0;

	/* flush any buffered char */
	file->back_char = EOF;

	/* switch off the file type */
	switch (file->type)
	{
		case PLAIN_FILE:
			return osd_fseek(file->file, offset, whence);

		case ZIPPED_FILE:
		case RAM_FILE:
			switch (whence)
			{
				case SEEK_SET:
					file->offset = offset;
					break;
				case SEEK_CUR:
					file->offset += offset;
					break;
				case SEEK_END:
					file->offset = file->length + offset;
					break;
			}
			file->eof = 0;
			break;
	}

	return err;
}



/***************************************************************************
    mame_fchecksum
***************************************************************************/

int mame_fchecksum(const char *gamename, const char *filename, unsigned int *length, char* hash)
{
	mame_file *file;

	/* first open the file; we pass the source hash because it contains
       the expected checksum for the file (used to load by checksum) */
	file = generic_fopen(FILETYPE_ROM, gamename, filename, hash, FILEFLAG_OPENREAD | FILEFLAG_HASH | FILEFLAG_VERIFY_ONLY);

	/* if we didn't succeed return -1 */
	if (!file)
		return -1;

	/* close the file and save the length & checksum */
	hash_data_copy(hash, file->hash);
	*length = file->length;
	mame_fclose(file);
	return 0;
}



/***************************************************************************
    mame_fsize
***************************************************************************/

u64 mame_fsize(mame_file *file)
{
	/* switch off the file type */
	switch (file->type)
	{
		case PLAIN_FILE:
		{
			int size, offs;
			offs = osd_ftell(file->file);
			osd_fseek(file->file, 0, SEEK_END);
			size = osd_ftell(file->file);
			osd_fseek(file->file, offs, SEEK_SET);
			return size;
		}

		case RAM_FILE:
		case ZIPPED_FILE:
			return file->length;
	}

	return 0;
}



/***************************************************************************
    mame_fhash
***************************************************************************/

const char* mame_fhash(mame_file *file)
{
	return file->hash;
}



/***************************************************************************
    mame_fgetc
***************************************************************************/

int mame_fgetc(mame_file *file)
{
	unsigned char buffer;

	if (file->back_char != EOF) {
		buffer = file->back_char;
		file->back_char = EOF;
		return buffer;
	}

	/* switch off the file type */
	switch (file->type)
	{
		case PLAIN_FILE:
			if (osd_fread(file->file, &buffer, 1) == 1)
				return buffer;
			return EOF;

		case RAM_FILE:
		case ZIPPED_FILE:
			if (file->offset < file->length)
				return file->data[file->offset++];
			else
				file->eof = 1;
			return EOF;
	}
	return EOF;
}



/***************************************************************************
    mame_ungetc
***************************************************************************/

int mame_ungetc(int c, mame_file *file)
{
	file->back_char = c;

	return c;
}



/***************************************************************************
    mame_fgets
***************************************************************************/

char *mame_fgets(char *s, int n, mame_file *file)
{
	char *cur = s;

	/* loop while we have characters */
	while (n > 0)
	{
		int c = mame_fgetc(file);
		if (c == EOF)
			break;

		/* if there's a CR, look for an LF afterwards */
		if (c == 0x0d)
		{
			int c2 = mame_fgetc(file);
			if (c2 != 0x0a)
				mame_ungetc(c2, file);
			*cur++ = 0x0d;
			n--;
			break;
		}

		/* if there's an LF, reinterp as a CR for consistency */
		else if (c == 0x0a)
		{
			*cur++ = 0x0d;
			n--;
			break;
		}

		/* otherwise, pop the character in and continue */
		*cur++ = c;
		n--;
	}

	/* if we put nothing in, return NULL */
	if (cur == s)
		return NULL;

	/* otherwise, terminate */
	if (n > 0)
		*cur++ = 0;
	return s;
}



/***************************************************************************
    mame_feof
***************************************************************************/

int mame_feof(mame_file *file)
{
	/* check for buffered chars */
	if (file->back_char != EOF)
		return 0;

	/* switch off the file type */
	switch (file->type)
	{
		case PLAIN_FILE:
			return osd_feof(file->file);

		case RAM_FILE:
		case ZIPPED_FILE:
			return (file->eof);
	}

	return 1;
}



/***************************************************************************
    mame_ftell
***************************************************************************/

u64 mame_ftell(mame_file *file)
{
	/* switch off the file type */
	switch (file->type)
	{
		case PLAIN_FILE:
			return osd_ftell(file->file);

		case RAM_FILE:
		case ZIPPED_FILE:
			return file->offset;
	}

	return -1L;
}



/***************************************************************************
    mame_fread_swap
***************************************************************************/

UINT32 mame_fread_swap(mame_file *file, void *buffer, UINT32 length)
{
	u8 *buf;
	u8 temp;
	int res, i;

	/* standard read first */
	res = mame_fread(file, buffer, length);

	/* swap the result */
	buf = (u8 *)buffer;
	for (i = 0; i < res; i += 2)
	{
		temp = buf[i];
		buf[i] = buf[i + 1];
		buf[i + 1] = temp;
	}

	return res;
}



/***************************************************************************
    mame_fwrite_swap
***************************************************************************/

UINT32 mame_fwrite_swap(mame_file *file, const void *buffer, UINT32 length)
{
	u8 *buf;
	u8 temp;
	int res, i;

	/* swap the data first */
	buf = (u8 *)buffer;
	for (i = 0; i < length; i += 2)
	{
		temp = buf[i];
		buf[i] = buf[i + 1];
		buf[i + 1] = temp;
	}

	/* do the write */
	res = mame_fwrite(file, buffer, length);

	/* swap the data back */
	for (i = 0; i < length; i += 2)
	{
		temp = buf[i];
		buf[i] = buf[i + 1];
		buf[i + 1] = temp;
	}

	return res;
}

/***************************************************************************
    get_extension_for_filetype
***************************************************************************/

static const char *get_extension_for_filetype(int filetype)
{
	const char *extension;

	/* now open the file appropriately */
	switch (filetype)
	{
		case FILETYPE_RAW:			/* raw data files */
		case FILETYPE_ROM:			/* ROM files */
		case FILETYPE_HIGHSCORE_DB:	/* highscore database/history files */
		case FILETYPE_HISTORY:		/* game history files */
		case FILETYPE_CHEAT:		/* cheat file */
		default:					/* anything else */
			extension = NULL;
			break;

#ifndef MESS
		case FILETYPE_IMAGE:		/* disk image files */
			extension = "chd";
			break;
#endif

		case FILETYPE_IMAGE_DIFF:	/* differencing drive images */
			extension = "dif";
			break;

#ifdef LOG_WAV
		case FILETYPE_WAVE:			/* wave files */
#endif /*LOG_WAV*/

		case FILETYPE_SAMPLE:		/* samples */
			extension = "wav";
			break;

		case FILETYPE_ARTWORK:		/* artwork files */
		case FILETYPE_SCREENSHOT:	/* screenshot files */
			extension = "png";
			break;

		case FILETYPE_NVRAM:		/* NVRAM files */
			extension = "nv";
			break;

		case FILETYPE_HIGHSCORE:	/* high score files */
			extension = "hi";
			break;

		case FILETYPE_LANGUAGE:		/* language files */
			extension = "lng";
			break;

		case FILETYPE_CTRLR:		/* controller files */
		case FILETYPE_CONFIG:		/* config files */
			extension = "cfg";
			break;

		case FILETYPE_INPUTLOG:		/* input logs */
			extension = "inp";
			break;
#ifdef KAILLERA
		case FILETYPE_INPUTLOG2:	/* input logs */
			extension = "trc";
			break;
#endif
		case FILETYPE_STATE:		/* save state files */
			extension = "sta";
			break;

		case FILETYPE_MEMCARD:		/* memory card files */
			extension = "mem";
			break;

		case FILETYPE_INI:			/* game specific ini files */
			extension = "ini";
			break;

#ifdef MESS
		case FILETYPE_HASH:
			extension = "hsi";
			break;
#endif
	}
	return extension;
}


/***************************************************************************
    generic_fopen
***************************************************************************/

static mame_file *generic_fopen(int pathtype, const char *gamename, const char *filename, const char* hash, UINT32 flags)
{
	static const char *access_modes[] = { "rb", "rb", "wb", "r+b", "rb", "rb", "wbg", "r+bg" };
	const char *extension = get_extension_for_filetype(pathtype);
	int pathcount = osd_get_path_count(pathtype);
	int pathindex, pathstart, pathstop, pathinc;
	mame_file file, *newfile;
	char tempname[256];

#ifdef MESS
	int is_absolute_path = osd_is_absolute_path(filename);
	if (is_absolute_path)
	{
		if ((flags & FILEFLAG_ALLOW_ABSOLUTE) == 0)
			return NULL;
		pathcount = 1;
	}
#endif /* MESS */

	LOG(("generic_fopen(%d, %s, %s, %s, %X)\n", pathc, gamename, filename, extension, flags));

	/* reset the file handle */
	memset(&file, 0, sizeof(file));

	file.back_char = EOF;

	/* check for incompatible flags */
	if ((flags & FILEFLAG_OPENWRITE) && (flags & FILEFLAG_HASH))
		fprintf(stderr, "Can't use HASH option with WRITE option in generic_fopen!\n");

	/* determine start/stop based on reverse search flag */
	if (!(flags & FILEFLAG_REVERSE_SEARCH))
	{
		pathstart = 0;
		pathstop = pathcount;
		pathinc = 1;
	}
	else
	{
		pathstart = pathcount - 1;
		pathstop = -1;
		pathinc = -1;
	}

	/* loop over paths */
	for (pathindex = pathstart; pathindex != pathstop; pathindex += pathinc)
	{
		char name[1024];

		/* ----------------- STEP 1: OPEN THE FILE RAW -------------------- */

		/* first look for path/gamename as a directory */
		compose_path(name, gamename, NULL, NULL);
		LOG(("Trying %s\n", name));

#ifdef MESS
		if (is_absolute_path)
		{
			*name = 0;
		}
		else if (flags & FILEFLAG_CREATE_GAMEDIR)
		{
			if (osd_get_path_info(pathtype, pathindex, name) == PATH_NOT_FOUND)
				osd_create_directory(pathtype, pathindex, name);
		}
#endif

		/* if the directory exists, proceed */
		if (*name == 0 || osd_get_path_info(pathtype, pathindex, name) == PATH_IS_DIRECTORY)
		{
			/* now look for path/gamename/filename.ext */
			compose_path(name, gamename, filename, extension);

			/* if we need checksums, load it into RAM and compute it along the way */
			if (flags & FILEFLAG_HASH)
			{
				if (checksum_file(pathtype, pathindex, name, &file.data, &file.length, file.hash) == 0)
				{
					file.type = RAM_FILE;
					break;
				}
			}

			/* otherwise, just open it straight */
			else
			{
				file.type = PLAIN_FILE;
				file.file = osd_fopen(pathtype, pathindex, name, access_modes[flags & 7]);
				if (file.file == NULL && (flags & (3 | FILEFLAG_MUST_EXIST)) == 3)
					file.file = osd_fopen(pathtype, pathindex, name, "w+b");
				if (file.file != NULL)
					break;
			}

#ifdef MESS
			if (flags & FILEFLAG_ZIP_PATHS)
			{
				int path_info = PATH_NOT_FOUND;
				const char *oldname = name;
				const char *zipentryname;
				char *newname = NULL;
				char *oldnewname = NULL;
				char *s;
				UINT32 ziplength;

				while ((oldname[0]) && ((path_info = osd_get_path_info(pathtype, pathindex, oldname)) == PATH_NOT_FOUND))
				{
					/* get name of parent directory into newname & oldname */
					newname = osd_dirname(oldname);

					/* if we are at a "blocking point", break out now */
					if (newname && !strcmp(oldname, newname))
						newname = NULL;

					if (oldnewname)
						free(oldnewname);
					oldname = oldnewname = newname;
					if (!newname)
						break;

					/* remove any trailing path separator if needed */
					for (s = newname + strlen(newname) - 1; s >= newname && osd_is_path_separator(*s); s--)
						*s = '\0';
				}

				if (newname)
				{
					if ((oldname[0]) &&(path_info == PATH_IS_FILE))
					{
						zipentryname = name + strlen(newname);
						while(osd_is_path_separator(*zipentryname))
							zipentryname++;

						if (load_zipped_file(pathtype, pathindex, newname, zipentryname, &file.data, &ziplength) == 0)
						{
							unsigned functions;
							functions = hash_data_used_functions(hash);
							LOG(("Using (mame_fopen) zip file for %s\n", filename));
							file.length = ziplength;
							file.type = ZIPPED_FILE;
							hash_compute(file.hash, file.data, file.length, functions);
							break;
						}
					}
					free(newname);
				}
			}
			if (is_absolute_path)
				continue;
#endif
		}

		/* ----------------- STEP 2: OPEN THE FILE IN A ZIP -------------------- */

		/* now look for it within a ZIP file */
		if (!(flags & (FILEFLAG_OPENWRITE | FILEFLAG_NOZIP)))
		{
			/* first look for path/gamename.zip */
			compose_path(name, gamename, NULL, "zip");
			LOG(("Trying %s file\n", name));

			/* if the ZIP file exists, proceed */
			if (osd_get_path_info(pathtype, pathindex, name) == PATH_IS_FILE)
			{
				UINT32 ziplength;

				/* if the file was able to be extracted from the ZIP, continue */
				compose_path(tempname, NULL, filename, extension);

				/* verify-only case */
				if (flags & FILEFLAG_VERIFY_ONLY)
				{
					u8 crcs[4];
					UINT32 crc = 0;

					/* Since this is a .ZIP file, we extract the CRC from the expected hash
                       (if any), so that we can load by CRC if needed. We must check that
                       the hash really contains a CRC, because it could be a NO_DUMP rom
                       for which we do not know the CRC yet. */
					if (hash && hash_data_extract_binary_checksum(hash, HASH_CRC, crcs) != 0)
					{
						/* Store the CRC in a single DWORD */
						crc = ((unsigned long)crcs[0] << 24) |
							  ((unsigned long)crcs[1] << 16) |
							  ((unsigned long)crcs[2] <<  8) |
							  ((unsigned long)crcs[3] <<  0);
					}

					hash_data_clear(file.hash);

					if (checksum_zipped_file(pathtype, pathindex, name, tempname, &ziplength, &crc) == 0)
					{
						file.length = ziplength;
						file.type = UNLOADED_ZIPPED_FILE;

						crcs[0] = (u8)(crc >> 24);
						crcs[1] = (u8)(crc >> 16);
						crcs[2] = (u8)(crc >> 8);
						crcs[3] = (u8)(crc >> 0);
						hash_data_insert_binary_checksum(file.hash, HASH_CRC, crcs);
						break;
					}
				}

				/* full load case */
				else
				{
					int err;

					/* Try loading the file */
					err = load_zipped_file(pathtype, pathindex, name, tempname, &file.data, &ziplength);

					/* If it failed, since this is a ZIP file, we can try to load by CRC
                       if an expected hash has been provided. unzip.c uses this ugly hack
                       of specifying the CRC as filename. */
					if (err && hash)
					{
						char crcn[9];

						if (hash_data_extract_printable_checksum(hash, HASH_CRC, crcn) != 0)
							err = load_zipped_file(pathtype, pathindex, name, crcn, &file.data, &ziplength);
					}

					if (err == 0)
					{
						unsigned functions;

						LOG(("Using (mame_fopen) zip file for %s\n", filename));
						file.length = ziplength;
						file.type = ZIPPED_FILE;

						/* Since we already loaded the file, we can easily calculate the
                           checksum of all the functions. In practice, we use only the
                           functions for which we have an expected checksum to compare with. */
						functions = hash_data_used_functions(hash);

						/* If user asked for CRC only, and there is an expected checksum
                           for CRC in the driver, compute only CRC. */
//						if (options.crc_only && (functions & HASH_CRC))
						functions = HASH_CRC;

						hash_compute(file.hash, file.data, file.length, functions);
						break;
					}
				}
			}
		}
	}

	/* if we didn't succeed, just return NULL */
	if (pathindex == pathstop)
		return NULL;

	/* otherwise, duplicate the file */
	newfile = (mame_file *)malloc(sizeof(file));
	if (newfile)
	{
		*newfile = file;
#ifdef DEBUG_COOKIE
		newfile->debug_cookie = DEBUG_COOKIE;
#endif
	}

	return newfile;
}



/***************************************************************************
    checksum_file
***************************************************************************/

static int checksum_file(int pathtype, int pathindex, const char *file, u8 **p, u64 *size, char* hash)
{
	u64 length;
	u8 *data;
	osd_files *f;
	unsigned int functions;

	/* open the file */
	f = osd_fopen(pathtype, pathindex, file, "rb");
	if (!f)
		return -1;

	/* determine length of file */
	if (osd_fseek(f, 0L, SEEK_END) != 0)
	{
		osd_fclose(f);
		return -1;
	}

	length = osd_ftell(f);
	if (length == -1L)
	{
		osd_fclose(f);
		return -1;
	}

	/* allocate space for entire file */
	data = (u8 *)malloc(length);
	if (!data)
	{
		osd_fclose(f);
		return -1;
	}

	/* read entire file into memory */
	if (osd_fseek(f, 0L, SEEK_SET) != 0)
	{
		free(data);
		osd_fclose(f);
		return -1;
	}

	if (osd_fread(f, data, length) != length)
	{
		free(data);
		osd_fclose(f);
		return -1;
	}

	*size = length;


	/* compute the checksums (only the functions for which we have an expected
       checksum). Take also care of crconly: if the user asked, we will calculate
       only the CRC, but only if there is an expected CRC for this file. */
//	functions = hash_data_used_functions(hash);
//	if (options.crc_only && (functions & HASH_CRC))
	functions = HASH_CRC;
	hash_compute(hash, data, length, functions);

	/* if the caller wants the data, give it away, otherwise free it */
	if (p)
		*p = data;
	else
		free(data);

	/* close the file */
	osd_fclose(f);
	return 0;
}



/***************************************************************************
    mame_fputs
***************************************************************************/

#if !defined(CRLF) || (CRLF < 1) || (CRLF > 3)
#error CRLF undefined: must be 1 (CR), 2 (LF) or 3 (CR/LF)
#endif

int mame_fputs(mame_file *f, const char *s)
{
	char convbuf[1024];
	char *pconvbuf;

	for (pconvbuf = convbuf; *s; s++)
	{
		if (*s == '\n')
		{
			if (CRLF == 1)		/* CR only */
				*pconvbuf++ = 13;
			else if (CRLF == 2)	/* LF only */
				*pconvbuf++ = 10;
			else if (CRLF == 3)	/* CR+LF */
			{
				*pconvbuf++ = 13;
				*pconvbuf++ = 10;
			}
		}
		else
			*pconvbuf++ = *s;
	}
	*pconvbuf++ = 0;

	return mame_fwrite(f, convbuf, strlen(convbuf));
}



/***************************************************************************
    mame_vfprintf
***************************************************************************/

int mame_vfprintf(mame_file *f, const char *fmt, va_list va)
{
	char buf[1024];
	vsnprintf(buf, sizeof(buf), fmt, va);
	return mame_fputs(f, buf);
}



/***************************************************************************
    mame_fprintf
***************************************************************************/

int CLIB_DECL mame_fprintf(mame_file *f, const char *fmt, ...)
{
	int rc;
	va_list va;
	va_start(va, fmt);
	rc = mame_vfprintf(f, fmt, va);
	va_end(va);
	return rc;
}

int _osd_get_path_info(const char *filename,int pathindex)
{
	char fullpath[1024];
	DWORD attributes;
	int returnvalue;

	snprintf(fullpath, WINUI_ARRAY_LENGTH(fullpath), "%s\\%s", rom_path[pathindex],filename );
	
	/* get the file attributes */
	attributes = GetFileAttributesA(fullpath);
	if (attributes == INVALID_FILE_ATTRIBUTES)
		returnvalue= PATH_NOT_FOUND;
	else if (attributes & FILE_ATTRIBUTE_DIRECTORY)
		returnvalue= PATH_IS_DIRECTORY;
	else
		returnvalue= PATH_IS_FILE;

	return returnvalue;
}


int mame_faccess_filepath(const char *filename, int filepath)
{
	int pathindex=0;
	
	/* loop over all paths */
	for (pathindex = 0; pathindex < filepath; pathindex++)
	{
		char name[256];

		/*  a .zip extension */
		sprintf(name, "%s.zip", filename);
		if (_osd_get_path_info(name,pathindex) != PATH_NOT_FOUND)
			return 1;
	}

	/* no match */
	return 0;
}

int mame_faccess_fileindex(const char *filename,int pathindex)
{
	char name[256];
	int rtvalue=0;
	
	/* first check the raw filename, in case we're looking for a directory */
	sprintf(name, "%s", filename);
	if (_osd_get_path_info(name,pathindex) != PATH_NOT_FOUND)
		rtvalue =1;

	/* no match */
	return rtvalue;
}

