/***************************************************************************

    fileio.h

    Core file I/O interface functions and definitions.

***************************************************************************/

#pragma once

#ifndef __FILEIO_H__
#define __FILEIO_H__

#include <stdarg.h>
//#include "osdepend.h"
#include "hash_ek.h"


/* file types */
enum
{
	FILETYPE_RAW = 0,
	FILETYPE_ROM,
	FILETYPE_IMAGE,
	FILETYPE_IMAGE_DIFF,
	FILETYPE_SAMPLE,
	FILETYPE_ARTWORK,
	FILETYPE_NVRAM,
	FILETYPE_HIGHSCORE,
	FILETYPE_HIGHSCORE_DB,
	FILETYPE_CONFIG,
	FILETYPE_INPUTLOG,
#ifdef KAILLERA
	FILETYPE_INPUTLOG2,
#endif
	FILETYPE_STATE,
	FILETYPE_MEMCARD,
	FILETYPE_SCREENSHOT,
	FILETYPE_HISTORY,
	FILETYPE_CHEAT,
	FILETYPE_LANGUAGE,
	FILETYPE_CTRLR,
	FILETYPE_INI,
#ifdef MESS
	FILETYPE_HASH,
#endif

#ifdef MAME_AVI
	FILETYPE_AVI,
#endif

#ifdef LOG_WAV
	FILETYPE_WAVE,
#endif /*LOG_WAV*/
	
	FILETYPE_end /* dummy last entry */
};


enum
{
	PATH_NOT_FOUND,
	PATH_IS_FILE,
	PATH_IS_DIRECTORY
};


/* gamename holds the driver name, filename is only used for ROMs and    */
/* samples. If 'write' is not 0, the file is opened for write. Otherwise */
/* it is opened for read. */

typedef struct _mame_file mame_file;
typedef struct _osd_file osd_files;

int mame_faccess(const char *filename, int filetype);
mame_file *mame_fopen(const char *gamename, const char *filename, int filetype, int openforwrite);
mame_file *mame_fopen_rom(const char *gamename, const char *filename, const char* exphash);
UINT32 mame_fread(mame_file *file, void *buffer, UINT32 length);
UINT32 mame_fwrite(mame_file *file, const void *buffer, UINT32 length);
UINT32 mame_fread_swap(mame_file *file, void *buffer, UINT32 length);
UINT32 mame_fwrite_swap(mame_file *file, const void *buffer, UINT32 length);
#ifdef LSB_FIRST
#define mame_fread_msbfirst mame_fread_swap
#define mame_fwrite_msbfirst mame_fwrite_swap
#define mame_fread_lsbfirst mame_fread
#define mame_fwrite_lsbfirst mame_fwrite
#else
#define mame_fread_msbfirst mame_fread
#define mame_fwrite_msbfirst mame_fwrite
#define mame_fread_lsbfirst mame_fread_swap
#define mame_fwrite_lsbfirst mame_fwrite_swap
#endif
int mame_fseek(mame_file *file, INT64 offset, int whence);
void mame_fclose(mame_file *file);
int mame_fchecksum(const char *gamename, const char *filename, unsigned int *length, char* hash);
UINT64 mame_fsize(mame_file *file);
const char *mame_fhash(mame_file *file);
int mame_fgetc(mame_file *file);
int mame_ungetc(int c, mame_file *file);
char *mame_fgets(char *s, int n, mame_file *file);
int mame_feof(mame_file *file);
UINT64 mame_ftell(mame_file *file);

int mame_fputs(mame_file *f, const char *s);
int mame_vfprintf(mame_file *f, const char *fmt, va_list va);

#ifdef __GNUC__
int CLIB_DECL mame_fprintf(mame_file *f, const char *fmt, ...)
      __attribute__ ((format (printf, 2, 3)));
#else
int CLIB_DECL mame_fprintf(mame_file *f, const char *fmt, ...);
#endif /* __GNUC__ */

#ifdef MAME_AVI
void GetDirectory(void* filename, char* dst, int dstlen);
#endif

/* Seek within a file */
int osd_fseek(osd_files *file, INT64 offset, int whence);
/* Attempt to open a file with the given name and mode using the specified path type */
osd_files *osd_fopen(int pathtype, int pathindex, const char *filename, const char *mode);
/* Close an open file */
void osd_fclose(osd_files *file);
/* Read bytes from a file */
UINT32 osd_fread(osd_files *file, void *buffer, UINT32 length);
/* Return current file position */
UINT64 osd_ftell(osd_files *file);
int osd_get_path_count(int pathtype);
int osd_get_path_info(int pathtype, int pathindex, const char *filename);
void osd_compose_path(char *output, int pathtype, int pathindex, const char *filename);
void compose_path(TCHAR *output, int pathtype, int pathindex, const char *filename);

int mame_faccess_filepath(const char *filename, int filepath);
int mame_faccess_fileindex(const char *filename,int pathindex);


#endif	/* __FILEIO_H__ */
