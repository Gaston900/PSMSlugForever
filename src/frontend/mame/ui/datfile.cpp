// license:BSD-3-Clause
// copyright-holders:Maurizio Petrarota
/***************************************************************************

    ui/datfile.cpp

    UI DATs manager.

***************************************************************************/

#include "emu.h"
#include "ui/datfile.h"

#include "drivenum.h"
#include "ui/moptions.h"
#include "ui/utils.h"

#include <utility>

enum
{
	TOKEN_COMMA,
	TOKEN_EQUALS,
	TOKEN_SYMBOL,
	TOKEN_LINEBREAK,
	TOKEN_INVALID=-1
};

#define CMD_LIST

#ifdef CMD_LIST

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define CR	0x0d	/* '\n' and '\r' meanings are swapped in some */
#define LF	0x0a	/*     compilers (e.g., Mac compilers) */

#define MAX_TOKEN_LENGTH	4096
#define MAX_MENUIDX_ENTRIES 64
//#define DATAFILE_TAG '$'

static const char *DATAFILE_TAG_KEY = "$info";
static const char *DATAFILE_TAG_COMMAND = "$cmd";
static const char *DATAFILE_TAG_END = "$end";
//static const char *DATAFILE_TAG_SKIP = "*-------------------------------------------------------------*";


#define FILE_MERGED	1
#define FILE_ROOT	2
#define FILE_TYPEMAX	((FILE_MERGED | FILE_ROOT) + 1)

static running_machine *m_machines = NULL;
//static emu_options *datafile_options = NULL;

struct tDatafileIndex
{
	u64 offset;
	const game_driver *driver;
};

struct tMenuIndex
{
	u64 offset;
	char *menuitem;
};

static struct tDatafileIndex *cmnd_idx[FILE_TYPEMAX];
static struct tMenuIndex *menu_idx = NULL;
static char *menu_filename = NULL;
/****************************************************************************
 *      private data for parsing functions
 ****************************************************************************/
static emu_file *fp = NULL;				/* Our file pointer */
static u64 dwFilePos;				/* file position */
static u8 bToken[MAX_TOKEN_LENGTH];		/* Our current token */

/* an array of driver name/drivers array index sorted by driver name
   for fast look up by name */
typedef struct
{
	const char *name;
	int index;
} driver_data_type;
//static driver_data_type *sorted_drivers = NULL;
static int num_games;
//static void flush_index(void);
//static void ParseClose(void);

extern int GetGameNameIndex(const char *name);

#endif /* CMD_LIST */

extern void ErrorMessageBox(const char *fmt, ...);

bool cmdselect=0;

namespace ui {
namespace {
//-------------------------------------------------
//  TAGS
//-------------------------------------------------
std::string const DATAFILE_TAG("$");
std::string const TAG_BIO("$bio");
std::string const TAG_INFO("$info");
std::string const TAG_MAME("$mame");
std::string const TAG_COMMAND("$cmd");
std::string const TAG_END("$end");
std::string const TAG_DRIVER("$drv");
std::string const TAG_STORY("$story");
std::string const TAG_HISTORY_R("## REVISION:");
std::string const TAG_MAMEINFO_R("# MAMEINFO.DAT");
std::string const TAG_MESSINFO_R("#     MESSINFO.DAT");
std::string const TAG_SYSINFO_R("# This file was generated on");
std::string const TAG_STORY_R("# version");
std::string const TAG_COMMAND_SEPARATOR("-----------------------------------------------");
std::string const TAG_GAMEINIT_R("# GAMEINIT.DAT");

} // anonymous namespace

//-------------------------------------------------
//  Statics
//-------------------------------------------------
datfile_manager::dataindex datfile_manager::m_histidx;
datfile_manager::dataindex datfile_manager::m_mameidx;
datfile_manager::dataindex datfile_manager::m_messidx;
datfile_manager::dataindex datfile_manager::m_cmdidx;
datfile_manager::dataindex datfile_manager::m_sysidx;
datfile_manager::dataindex datfile_manager::m_storyidx;
datfile_manager::dataindex datfile_manager::m_ginitidx;
datfile_manager::drvindex datfile_manager::m_drvidx;
datfile_manager::drvindex datfile_manager::m_messdrvidx;
datfile_manager::drvindex datfile_manager::m_menuidx;
datfile_manager::swindex datfile_manager::m_swindex;
std::string datfile_manager::m_history_rev;
std::string datfile_manager::m_mame_rev;
std::string datfile_manager::m_mess_rev;
std::string datfile_manager::m_sysinfo_rev;
std::string datfile_manager::m_story_rev;
std::string datfile_manager::m_ginit_rev;
bool datfile_manager::first_run = true;

#define opendatsfile(f) do { fileptr datfile = parseopen(#f".dat"); if (datfile) init_##f(std::move(datfile)); } while (false)

//-------------------------------------------------
// ctor
//-------------------------------------------------
datfile_manager::datfile_manager(running_machine &machine, ui_options &moptions)
	: m_machine(machine)
	, m_options(moptions)
{
	//if (m_options.enabled_dats() && first_run)
	if (first_run)
	{
		first_run = false;
		opendatsfile(mameinfo);
		opendatsfile(command);
		opendatsfile(command_en);
		opendatsfile(story);
		opendatsfile(messinfo);
		opendatsfile(sysinfo);
		opendatsfile(history);
		opendatsfile(gameinit);
	}

#ifdef CMD_LIST
	datafile_init(machine);
#endif /* CMD_LIST */
}

//-------------------------------------------------
//  initialize sysinfo.dat index
//-------------------------------------------------
void datfile_manager::init_sysinfo(fileptr &&fp)
{
	int swcount = 0;
	auto count = index_datafile(std::move(fp), m_sysidx, swcount, m_sysinfo_rev, TAG_SYSINFO_R, '.');
	osd_printf_verbose("Sysinfo.dat games found = %i\n", count);
	osd_printf_verbose("Rev = %s\n", m_sysinfo_rev.c_str());
}

//-------------------------------------------------
//  initialize story.dat index
//-------------------------------------------------
void datfile_manager::init_story(fileptr &&fp)
{
	int swcount = 0;
	auto count = index_datafile(std::move(fp), m_storyidx, swcount, m_story_rev, TAG_STORY_R, 's');
	osd_printf_verbose("Story.dat games found = %i\n", count);
}

//-------------------------------------------------
//  initialize history.dat index
//-------------------------------------------------
void datfile_manager::init_history(fileptr &&fp)
{
	int swcount = 0;
	auto count = index_datafile(std::move(fp), m_histidx, swcount, m_history_rev, TAG_HISTORY_R, ' ');
	osd_printf_verbose("History.dat systems found = %i\n", count);
	osd_printf_verbose("History.dat software packages found = %i\n", swcount);
	osd_printf_verbose("Rev = %s\n", m_history_rev.c_str());
}

//-------------------------------------------------
//  initialize gameinit.dat index
//-------------------------------------------------
void datfile_manager::init_gameinit(fileptr &&fp)
{
	int swcount = 0;
	drvindex tmp;
	auto count = index_mame_mess_info(std::move(fp), m_ginitidx, tmp, swcount);
	osd_printf_verbose("Gameinit.dat games found = %i\n", count);
	osd_printf_verbose("Rev = %s\n", m_ginit_rev.c_str());
}

//-------------------------------------------------
//  initialize mameinfo.dat index
//-------------------------------------------------
void datfile_manager::init_mameinfo(fileptr &&fp)
{
	int drvcount = 0;
	auto count = index_mame_mess_info(std::move(fp), m_mameidx, m_drvidx, drvcount);
	osd_printf_verbose("Mameinfo.dat games found = %i\n", count);
	osd_printf_verbose("Mameinfo.dat drivers found = %d\n", drvcount);
	osd_printf_verbose("Rev = %s\n", m_mame_rev.c_str());
}

//-------------------------------------------------
//  initialize messinfo.dat index
//-------------------------------------------------
void datfile_manager::init_messinfo(fileptr &&fp)
{
	int drvcount = 0;
	auto count = index_mame_mess_info(std::move(fp), m_messidx, m_messdrvidx, drvcount);
	osd_printf_verbose("Messinfo.dat games found = %i\n", count);
	osd_printf_verbose("Messinfo.dat drivers found = %d\n", drvcount);
	osd_printf_verbose("Rev = %s\n", m_mess_rev.c_str());
}

//-------------------------------------------------
//  initialize command.dat index
//-------------------------------------------------
void datfile_manager::init_command(fileptr &&fp)
{
	int swcount = 0;
	std::string tmp;
	auto count = index_datafile(std::move(fp), m_cmdidx, swcount, tmp, std::string(), 'c');
	osd_printf_verbose("Command.dat games found = %i\n", count);
}

void datfile_manager::init_command_en(fileptr &&fp)
{
	int swcount = 0;
	std::string tmp;
	auto count = index_datafile(std::move(fp), m_cmdidx, swcount, tmp, std::string(), 'c');
	osd_printf_verbose("Command_en.dat games found = %i\n", count);
}

bool datfile_manager::has_software(std::string const &softlist, std::string const &softname, std::string const &parentname) const
{
	return bool(find_software(softlist, softname, parentname));
}

long const *datfile_manager::find_software(std::string const &softlist, std::string const &softname, std::string const &parentname) const
{
	// Find software in software list index
	auto const software(m_swindex.find(softlist));
	if (software == m_swindex.end())
		return nullptr;

	auto itemsiter = software->second.find(softname);
	if ((itemsiter == software->second.end()) && !parentname.empty())
		itemsiter = software->second.find(parentname);

	return (itemsiter != software->second.end()) ? &itemsiter->second : nullptr;
}

//-------------------------------------------------
//  load software info
//-------------------------------------------------
void datfile_manager::load_software_info(std::string const &softlist, std::string &buffer, std::string const &softname, std::string const &parentname)
{
	if (m_swindex.empty())
		return;

	// Load history text
	fileptr const datfile = parseopen("history.dat");
	if (datfile)
	{
		// Find software in software list index
		long const *const s_offset = find_software(softlist, softname, parentname);
		if (!s_offset)
			return;

		char rbuf[64 * 1024];
		std::fseek(datfile.get(), *s_offset, SEEK_SET);
		std::string readbuf;
		while (std::fgets(rbuf, 64 * 1024, datfile.get()) != nullptr)
		{
			readbuf = chartrimcarriage(rbuf);

			// end entry when a end tag is encountered
			if (readbuf == TAG_END)
				break;

			// add this string to the buffer
			buffer.append(readbuf).append("\n");
		}
	}
}

//-------------------------------------------------
//  load_data_info
//-------------------------------------------------
void datfile_manager::load_data_info(const game_driver *drv, std::string &buffer, int type)
{
	dataindex const *index_idx = nullptr;
	drvindex const *driver_idx = nullptr;
	std::string const *tag;
	std::string filename;

	switch (type)
	{
	case UI_HISTORY_LOAD:
		filename = "history.dat";
		tag = &TAG_BIO;
		index_idx = &m_histidx;
		break;
	case UI_MAMEINFO_LOAD:
		filename = "mameinfo.dat";
		tag = &TAG_MAME;
		index_idx = &m_mameidx;
		driver_idx = &m_drvidx;
		break;
	case UI_SYSINFO_LOAD:
		filename = "sysinfo.dat";
		tag = &TAG_BIO;
		index_idx = &m_sysidx;
		break;
	case UI_MESSINFO_LOAD:
		filename = "messinfo.dat";
		tag = &TAG_MAME;
		index_idx = &m_messidx;
		driver_idx = &m_messdrvidx;
		break;
	case UI_STORY_LOAD:
		filename = "story.dat";
		tag = &TAG_STORY;
		index_idx = &m_storyidx;
		break;
	case UI_GINIT_LOAD:
		filename = "gameinit.dat";
		tag = &TAG_MAME;
		index_idx = &m_ginitidx;
		break;
	default:
		assert(false);
		return;
	}

	fileptr const datfile = parseopen(filename.c_str());
	if (datfile)
	{
		load_data_text(datfile.get(), drv, buffer, *index_idx, *tag);

		// load driver info
		if (driver_idx && !driver_idx->empty())
			load_driver_text(datfile.get(), drv, buffer, *driver_idx, TAG_DRIVER);

		// cleanup mameinfo and sysinfo double line spacing
		if (((*tag == TAG_MAME) && (type != UI_GINIT_LOAD)) || (type == UI_SYSINFO_LOAD))
			strreplace(buffer, "\n\n", "\n");
	}
}

//-------------------------------------------------
//  load a game text into the buffer
//-------------------------------------------------
void datfile_manager::load_data_text(FILE *fp, game_driver const *drv, std::string &buffer, dataindex const &idx, std::string const &tag)
{
	auto itemsiter = idx.find(drv);
	if (itemsiter == idx.end())
	{
		auto cloneof = driver_list::non_bios_clone(*drv);
		if (cloneof == -1)
			return;
		else
		{
			auto c_drv = &driver_list::driver(cloneof);
			itemsiter = idx.find(c_drv);
			if (itemsiter == idx.end())
				return;
		}
	}

	auto s_offset = itemsiter->second;
	std::fseek(fp, s_offset, SEEK_SET);
	char rbuf[64 * 1024];
	std::string readbuf;
	while (std::fgets(rbuf, 64 * 1024, fp) != nullptr)
	{
		readbuf = chartrimcarriage(rbuf);

		// end entry when a end tag is encountered
		if (readbuf == TAG_END)
			break;

		// continue if a specific tag is encountered
		if (readbuf == tag)
			continue;

		// add this string to the buffer
		buffer.append(readbuf).append("\n");
	}
}

//-------------------------------------------------
//  load a driver name and offset into an
//  indexed array
//-------------------------------------------------
void datfile_manager::load_driver_text(FILE *fp, game_driver const *drv, std::string &buffer, drvindex const &idx, std::string const &tag)
{
	std::string s(core_filename_extract_base(drv->type.source()));
	auto index = idx.find(s);

	// if driver not found, return
	if (index == idx.end())
		return;

	buffer.append("\n--- DRIVER INFO ---\n").append("Driver: ").append(s).append("\n\n");
	auto s_offset = index->second;
	std::fseek(fp, s_offset, SEEK_SET);
	char rbuf[64 * 1024];
	std::string readbuf;
	while (std::fgets(rbuf, 64 * 1024, fp) != nullptr)
	{
		readbuf = chartrimcarriage(rbuf);

		// end entry when a end tag is encountered
		if (readbuf == TAG_END)
			break;

		// continue if a specific tag is encountered
		if (readbuf == tag)
			continue;

		// add this string to the buffer
		buffer.append(readbuf).append("\n");
	}
}

//-------------------------------------------------
//  load a game name and offset into an
//  indexed array (mameinfo)
//-------------------------------------------------
int datfile_manager::index_mame_mess_info(fileptr &&fp, dataindex &index, drvindex &index_drv, int &drvcount)
{
	size_t foundtag;
	auto t_mame = TAG_MAMEINFO_R.size();
	auto t_mess = TAG_MESSINFO_R.size();
	auto t_ginit = TAG_GAMEINIT_R.size();
	auto t_info = TAG_INFO.size();

	char rbuf[64 * 1024];
	std::string readbuf, xid, name;
	while (std::fgets(rbuf, 64 * 1024, fp.get()) != nullptr)
	{
		readbuf = chartrimcarriage(rbuf);
		if (m_mame_rev.empty() && readbuf.compare(0, t_mame, TAG_MAMEINFO_R) == 0)
		{
			auto found = readbuf.find(" ", t_mame + 1);
			m_mame_rev = readbuf.substr(t_mame + 1, found - t_mame);
		}
		else if (m_mess_rev.empty() && (foundtag = readbuf.find(TAG_MESSINFO_R)) != std::string::npos)
		{
			auto found = readbuf.find(" ", foundtag + t_mess + 1);
			m_mess_rev = readbuf.substr(foundtag + t_mess + 1, found - t_mess - foundtag);
		}
		else if (m_ginit_rev.empty() && readbuf.compare(0, t_ginit, TAG_GAMEINIT_R) == 0)
		{
			auto found = readbuf.find(" ", t_ginit + 1);
			m_ginit_rev = readbuf.substr(t_ginit + 1, found - t_ginit);
		}
		else if (readbuf.compare(0, t_info, TAG_INFO) == 0)
		{
			// TAG_INFO
			std::fgets(rbuf, 64 * 1024, fp.get());
			xid = chartrimcarriage(rbuf);
			name = readbuf.substr(t_info + 1);
			if (xid == TAG_MAME)
			{
				// validate driver
				auto game_index = driver_list::find(name.c_str());
				if (game_index != -1)
					index.emplace(&driver_list::driver(game_index), std::ftell(fp.get()));
			}
			else if (xid == TAG_DRIVER)
			{
				index_drv.emplace(name, std::ftell(fp.get()));
				drvcount++;
			}
		}
	}
	return index.size();
}

//-------------------------------------------------
//  load a game name and offset into an
//  indexed array
//-------------------------------------------------
int datfile_manager::index_datafile(fileptr &&fp, dataindex &index, int &swcount, std::string &rev, std::string const &tag, char sep)
{
	std::string readbuf;
	auto const tag_size = tag.size();
	auto const t_info = TAG_INFO.size();
	auto const t_bio = TAG_BIO.size();
	char rbuf[64 * 1024];
	while (std::fgets(rbuf, 64 * 1024, fp.get()) != nullptr)
	{
		readbuf = chartrimcarriage(rbuf);

		if (!tag.empty())
		{
			if (rev.empty() && readbuf.compare(0, tag_size, tag) == 0)
			{
				if (sep != 's')
					rev = readbuf.substr(tag_size + 1, readbuf.find(sep, tag_size + 1) - tag_size);
				else
					rev = readbuf.substr(tag_size + 1);
			}
		}

		if (readbuf.compare(0, t_info, TAG_INFO) == 0)
		{
			// search for game info
			auto rd = readbuf.substr(t_info + 1);
			std::vector<std::string> gamelist = tokenize(rd, ',');
			for (auto & e : gamelist)
			{
				auto game_index = driver_list::find(e.c_str());
				if (game_index != -1)
					index.emplace(&driver_list::driver(game_index), std::ftell(fp.get()));
			}
		}
		else if (!readbuf.empty() && readbuf[0] == DATAFILE_TAG[0])
		{
			// search for software info
			std::fgets(rbuf, 64 * 1024, fp.get());
			std::string readbuf_2(chartrimcarriage(rbuf));
			if (readbuf_2.compare(0, t_bio, TAG_BIO) == 0)
			{
				auto eq_sign = readbuf.find('=');
				std::string s_list(readbuf.substr(1, eq_sign - 1));
				std::string s_roms(readbuf.substr(eq_sign + 1));
				std::vector<std::string> token_list = tokenize(s_list, ',');
				std::vector<std::string> token_roms = tokenize(s_roms, ',');
				for (auto & li : token_list)
					for (auto & ro : token_roms)
						m_swindex[li].emplace(ro, std::ftell(fp.get()));
				swcount++;
			}
		}
	}
	return index.size();
}

//---------------------------------------------------------
//  parseopen - Open up file for reading
//---------------------------------------------------------
datfile_manager::fileptr datfile_manager::parseopen(const char *filename)
{
	emu_file file(m_options.history_path(), OPEN_FLAG_READ);
	if (file.open(filename) != osd_file::error::NONE)
		return fileptr(nullptr, &std::fclose);

	std::string const fullpath = file.fullpath();
	file.close();
	fileptr result(std::fopen(fullpath.c_str(), "rb"), &std::fclose);

	fgetc(result.get());
	fseek(result.get(), 0, SEEK_SET);
	return result;
}

//-------------------------------------------------
//  create the menu index
//-------------------------------------------------
void datfile_manager::index_menuidx(fileptr &&fp, const game_driver *drv, dataindex const &idx, drvindex &index)
{
	auto itemsiter = idx.find(drv);
	if (itemsiter == idx.end())
	{
		auto const cloneof = driver_list::non_bios_clone(*drv);
		if (cloneof == -1)
			return;

		auto const c_drv = &driver_list::driver(cloneof);
		if ((itemsiter = idx.find(c_drv)) == idx.end())
			return;
	}

	// seek to correct point in datafile
	auto const s_offset = itemsiter->second;
	std::fseek(fp.get(), s_offset, SEEK_SET);
	auto const tinfo = TAG_INFO.size();
//	auto const tend = TAG_END.size();
	char rbuf[64 * 1024];
	
	std::string readbuf;

//	FILE *fp2;
//	fp2 = fopen("index_menu.txt","a+t");
//	int counts=0;
//	bool setindex=0;
	
	while (std::fgets(rbuf, 64 * 1024, fp.get()) != nullptr)
	{
		readbuf = chartrimcarriage(rbuf);
//		fprintf(fp2, "readbuf : %s count %d\n", readbuf.c_str(),counts); 

		if (!core_strnicmp(TAG_INFO.c_str(), readbuf.c_str(), tinfo))
			break;

		// TAG_COMMAND identifies the driver
		if(readbuf == TAG_END)
		{
			std::fgets(rbuf, 64 * 1024, fp.get());
			readbuf = chartrimcarriage(rbuf);	
			if(readbuf == TAG_COMMAND)
			{
				/*nothing*/	
//				fprintf(fp2, "TAG FOUND END=CMD\n");
			}
		}
		else if (readbuf == TAG_COMMAND)
		{
			std::fgets(rbuf, 64 * 1024, fp.get());

			readbuf = chartrimcarriage(rbuf);

//			fprintf(fp2, "readbuf in CMD: %s count %d\n", readbuf.c_str(),counts); 
			
			if(readbuf != TAG_END)
			{
//				fprintf(fp2, "tag : %s\n count %d\n", &rbuf[0],counts);
				index.emplace(rbuf, std::ftell(fp.get()));
			}
		}

//		fprintf(fp2, "rbuf : %s\n count %d\n", &rbuf[0],counts);	
//		counts++;		
	}

//	fprintf(fp2, "end--------------------------%s\n", &rbuf[0]);	
//	fclose(fp2);
	
}

//-------------------------------------------------
//  load command text into the buffer
//-------------------------------------------------
void datfile_manager::load_command_info(std::string &buffer, std::string const &sel)
{
	std::string filename;

	if(cmdselect==0)
	{
		filename = "command.dat";
	}
	else
	{
		filename = "command_en.dat";
	}
	
	fileptr const datfile= parseopen(filename.c_str());

	
	if (datfile)
	{
	
		// open and seek to correct point in datafile
		auto const offset = m_menuidx.at(sel);
		std::fseek(datfile.get(), offset, SEEK_SET);
		char rbuf[64 * 1024];
		std::string readbuf;

//		FILE *fp;
//		fp = fopen("commandRead.txt", "a+t");
//		int counts=0;
		
		while (std::fgets(rbuf, 64 * 1024, datfile.get()) != nullptr)
		{
			char *ptr;
			readbuf = chartrimcarriage(rbuf);
//			fprintf(fp,"readbuf:%s,rbuf:%s,count:%d\n",readbuf.c_str(),&rbuf[0],counts);
			// skip separator lines
			if (readbuf == TAG_COMMAND_SEPARATOR)
			{
//				fprintf(fp,"TAG_SEPARATOR : readbuf:%s,rbuf:%s\n",readbuf.c_str(),&rbuf[0]);
				continue;
			}

			ptr = strstr(readbuf.c_str(),"$cmd");
			if (ptr != nullptr)
				continue;			

			ptr = strstr(readbuf.c_str(),"$end");
			if (ptr != nullptr)
				continue;
			
			ptr = strstr(readbuf.c_str(),"$info");
			if(ptr !=nullptr )
			{
//				fprintf(fp,"TAG_INFO :readbuf:%s,rbuf:%s\n",readbuf.c_str(),&rbuf[0]);
				break;
			}

			// add this string to the buffer
			buffer.append(readbuf).append("\n");

	//		counts++;
		}

//		fprintf(fp, "%s\n", &buffer[0]);		
//		fclose(fp);
	}
}

//-------------------------------------------------
//  load submenu item for command.dat
//-------------------------------------------------
void datfile_manager::command_sub_menu(const game_driver *drv, std::vector<std::string> &menuitems)
{
//	FILE *fp;
//	fp =fopen("command_sub_menu.txt", "a+t");

	fileptr datfile = parseopen("command.dat");
	
	if (datfile)
	{
		m_menuidx.clear();
		index_menuidx(std::move(datfile), drv, m_cmdidx, m_menuidx);
		cmdselect=0;
		
		if(m_menuidx.empty())
		{
//			fprintf(fp,"empty\n");
			datfile = parseopen("command_en.dat");	
			if(datfile)
			{
				m_menuidx.clear();
				index_menuidx(std::move(datfile), drv, m_cmdidx, m_menuidx);
				menuitems.reserve(m_menuidx.size());
				for (auto const &elem : m_menuidx)
					menuitems.push_back(elem.first);
				cmdselect=1;
			}
		}
		else
		{
			menuitems.reserve(m_menuidx.size());
			for (auto const &elem : m_menuidx)
				menuitems.push_back(elem.first);			
		}
		
	}

//	fclose(fp);
}

#ifdef CMD_LIST

static void flush_index(void)
{
	int i;

	for (i = 0; i < FILE_TYPEMAX; i++)
	{
		if (i & FILE_ROOT)
			continue;

		if (cmnd_idx[i])
		{
			auto_free(*m_machines, cmnd_idx[i]);
			cmnd_idx[i] = 0;
		}
	}
}

char *core_strdup(const char *str)
{
	char *cpy = nullptr;
	if (str != nullptr)
	{
		cpy = (char*) malloc(strlen(str)+1);
		if (cpy != nullptr)
			strcpy(cpy, str);
	}
	return cpy;
}

/****************************************************************************
 *      ParseClose - Closes the existing opened file (if any)
 ****************************************************************************/
static void ParseClose(void)
{
	/* If the file is open, time for fclose. */
	if (fp)
	{
		fp->close();
		global_free(fp);
	}

	fp = NULL;
}

void datfile_manager::datafile_exit()
{
	flush_index();
	ParseClose();
}

void datfile_manager::datafile_init(running_machine &machine)
{
	m_machines = &machine;
	num_games = driver_list::total();
	machine.add_notifier(MACHINE_NOTIFY_EXIT, machine_notify_delegate(&datfile_manager::datafile_exit, this));
}

/****************************************************************************
 *      ParseOpen - Open up file for reading
 ****************************************************************************/
static u8 ParseOpen(const char *pszFilename)
{
	osd_file::error filerr;

	ParseClose();

	/* Open file up in binary mode */
	fp = global_alloc(emu_file(OPEN_FLAG_READ));
	filerr = fp->open(pszFilename);
	if (filerr != osd_file::error::NONE)
		return 0;

	/* Otherwise, prepare! */
	dwFilePos = 0;

	/* identify text file type first */
	fp->getc();
	fp->seek(dwFilePos, SEEK_SET);

	return 1;
}

/****************************************************************************
 *      ParseSeek - Move the file position indicator
 ****************************************************************************/
static u8 ParseSeek(u64 offset, int whence)
{
	int result = fp->seek(offset, whence);

	if (0 == result)
	{
		dwFilePos = fp->tell();
	}
	return (u8)result;
}

/****************************************************************************
 *      GetNextToken - Pointer to the token string pointer
 *                     Pointer to position within file
 *
 *      Returns token, or TOKEN_INVALID if at end of file
 ****************************************************************************/
static u32 GetNextToken(u8 **ppszTokenText, u64 *pdwPosition)
{
	u32 dwLength;			/* Length of symbol */
	u8 *pbTokenPtr = bToken;		/* Point to the beginning */
	u8 bData;				/* Temporary data byte */

	u8 space, character;

	space     = '\t';
	character = ' ' - 1;

//	FILE *fpp;
//	fpp = fopen("readdata.txt", "a+t");
	
	while (1)
	{
		dwFilePos = fp->tell();
		bData = fp->getc();		/* Get next character */

//		fprintf(fpp,"%d\n",);
		/* If we're at the end of the file, bail out */

		if (fp->eof())
			return(TOKEN_INVALID);

		/* If it's not whitespace, then let's start eating characters */

		if (space != bData && '\t' != bData)
		{
			/* Store away our file position (if given on input) */

			if (pdwPosition)
				*pdwPosition = dwFilePos;

			/* If it's a separator, special case it */

			if (',' == bData || '=' == bData)
			{
				*pbTokenPtr++ = bData;
				*pbTokenPtr = '\0';
				dwFilePos = fp->tell();

				if (',' == bData)
					return(TOKEN_COMMA);
				else
					return(TOKEN_EQUALS);
			}

			/* Otherwise, let's try for a symbol */

			if (bData > character)
			{
				dwLength = 0;			/* Assume we're 0 length to start with */

				/* Loop until we've hit something we don't understand */

				while (bData != ',' &&
				       bData != '=' &&
				       bData != space &&
				       bData != '\t' &&
				       bData != '\n' &&
				       bData != '\r' &&
				       fp->eof() == 0)
				{
					dwFilePos = fp->tell();
					*pbTokenPtr++ = bData;	/* Store our byte */
					++dwLength;
					assert(dwLength < MAX_TOKEN_LENGTH);
					bData = fp->getc();
				}

				/* If it's not the end of the file, put the last received byte */
				/* back. We don't want to touch the file position, though if */
				/* we're past the end of the file. Otherwise, adjust it. */

				if (0 == fp->eof())
				{
					fp->seek(dwFilePos, SEEK_SET);
				}

				/* Null terminate the token */

				*pbTokenPtr = '\0';

				/* Connect up the */

				if (ppszTokenText)
					*ppszTokenText = bToken;

				return(TOKEN_SYMBOL);
			}

			/* Not a symbol. Let's see if it's a cr/cr, lf/lf, or cr/lf/cr/lf */
			/* sequence */

			if (LF == bData)
			{
				u64 dwPos;

				/* Unix style perhaps? */

				dwFilePos = fp->tell();
				bData = fp->getc();		/* Peek ahead */
				dwPos = fp->tell();
				fp->seek(dwFilePos, SEEK_SET);	/* Force a retrigger if subsequent LF's */

				if (LF == bData)		/* Two LF's in a row - it's a UNIX hard CR */
				{
					dwFilePos = dwPos;
					*pbTokenPtr++ = bData;	/* A real linefeed */
					*pbTokenPtr = '\0';
					return(TOKEN_LINEBREAK);
				}

				/* Otherwise, fall through and keep parsing. */

			}
			else
                        if (CR == bData)			/* Carriage return? */
			{
				/* Figure out if it's Mac or MSDOS format */

				dwFilePos = fp->tell();
				bData = fp->getc();		/* Peek ahead */

				/* We don't need to bother with EOF checking. It will be 0xff if */
				/* it's the end of the file and will be caught by the outer loop. */

				if (CR == bData)		/* Mac style hard return! */
				{
					/* Do not advance the file pointer in case there are successive */
					/* CR/CR sequences */

					/* Stuff our character back upstream for successive CR's */

					fp->seek(dwFilePos, SEEK_SET);

					*pbTokenPtr++ = bData;	/* A real carriage return (hard) */
					*pbTokenPtr = '\0';

					return(TOKEN_LINEBREAK);
				}
				else if (LF == bData)		/* MSDOS format! */
				{
					dwFilePos = fp->tell();

					*pbTokenPtr++ = bData;	/* A real carriage return (hard) */
					*pbTokenPtr = '\0';

					return(TOKEN_LINEBREAK);
				
				}
				else
				{
					fp->seek(dwFilePos, SEEK_SET);	/* Put the character back. No good */
				}

				/* Otherwise, fall through and keep parsing */
			}
		}
	}

//	fclose(fpp);
	
}

/****************************************************************************
 *      GetNextToken_ex - Pointer to the token string pointer
 *                        Pointer to position within file
 *
 *      Returns token, or TOKEN_INVALID if at end of file
 ****************************************************************************/
static u32 GetNextToken_ex(u8 **ppszTokenText, u64 *pdwPosition)
{
	u32 dwLength;			/* Length of symbol */
	u8 *pbTokenPtr = bToken;		/* Point to the beginning */
	u8 bData;				/* Temporary data byte */

	while (1)
	{
		dwFilePos = fp->tell();
		bData = fp->getc();		/* Get next character */

		/* If we're at the end of the file, bail out */

		if (fp->eof())
			return(TOKEN_INVALID);

		/* If it's not whitespace, then let's start eating characters */

		if ('\t' != bData)
		{
			/* Store away our file position (if given on input) */

			if (pdwPosition)
				*pdwPosition = dwFilePos;

			/* Fixed: exclude a separator of comma */
			/* If it's a separator, special case it */
//			if (',' == bData || '=' == bData)
			if ('=' == bData)
			{
				*pbTokenPtr++ = bData;
				*pbTokenPtr = '\0';
				dwFilePos = fp->tell();

				return(TOKEN_EQUALS);
			}

			/* Otherwise, let's try for a symbol */
			if (bData >= ' ')
			{
				dwLength = 0;			/* Assume we're 0 length to start with */

				/* Loop until we've hit something we don't understand */

				/* Fixed: exclude a separator of comma and equal */
				while (
//				      (bData != ',' &&
//				       bData != '=' &&
				       bData != '\t' &&
				       bData != '\n' &&
				       bData != '\r' &&
				       fp->eof() == 0)
				{
					dwFilePos = fp->tell();
					*pbTokenPtr++ = bData;	/* Store our byte */
					++dwLength;
					assert(dwLength < MAX_TOKEN_LENGTH);
					bData = fp->getc();
				}

				/* If it's not the end of the file, put the last received byte */
				/* back. We don't want to touch the file position, though if */
				/* we're past the end of the file. Otherwise, adjust it. */

				if (0 == fp->eof())
				{
					fp->seek(dwFilePos, SEEK_SET);
				}

				/* Null terminate the token */

				*pbTokenPtr = '\0';

				/* Connect up the */

				if (ppszTokenText)
					*ppszTokenText = bToken;

				return(TOKEN_SYMBOL);
			}

			/* Not a symbol. Let's see if it's a cr/cr, lf/lf, or cr/lf/cr/lf */
			/* sequence */

			if (LF == bData)
			{
				u64 dwPos;

				/* Unix style perhaps? */

				dwFilePos = fp->tell();
				bData = fp->getc();		/* Peek ahead */
				dwPos = fp->tell();
				fp->seek(dwFilePos, SEEK_SET);	/* Force a retrigger if subsequent LF's */

				if (LF == bData)		/* Two LF's in a row - it's a UNIX hard CR */
				{
					dwFilePos = dwPos;
					*pbTokenPtr++ = bData;	/* A real linefeed */
					*pbTokenPtr = '\0';
					return(TOKEN_LINEBREAK);
				}

				/* Otherwise, fall through and keep parsing. */

			}
			else if (CR == bData)			/* Carriage return? */
			{
				/* Figure out if it's Mac or MSDOS format */

				dwFilePos = fp->tell();
				bData = fp->getc();		/* Peek ahead */

				/* We don't need to bother with EOF checking. It will be 0xff if */
				/* it's the end of the file and will be caught by the outer loop. */

				if (CR == bData)		/* Mac style hard return! */
				{
					/* Do not advance the file pointer in case there are successive */
					/* CR/CR sequences */

					/* Stuff our character back upstream for successive CR's */

					fp->seek(dwFilePos, SEEK_SET);

					*pbTokenPtr++ = bData;	/* A real carriage return (hard) */
					*pbTokenPtr = '\0';

					return(TOKEN_LINEBREAK);
				}
				else if (LF == bData)		/* MSDOS format! */
				{
					dwFilePos = fp->tell();

					*pbTokenPtr++ = bData;	/* A real carriage return (hard) */
					*pbTokenPtr = '\0';

					return(TOKEN_LINEBREAK);

				}
				else
				{
					fp->seek(dwFilePos, SEEK_SET);	/* Put the character back. No good */
				}

				/* Otherwise, fall through and keep parsing */
			}
		}
	}
}

/**************************************************************************
 *      index_datafile
 *      Create an index for the records in the currently open datafile.
 *
 *      Returns 0 on error, or the number of index entries created.
 **************************************************************************/
 
static int index_datafile (struct tDatafileIndex **_index)
{
	struct tDatafileIndex *idx;
	int count = 0;
	u32 token = TOKEN_SYMBOL;

	/* rewind file */
	if (ParseSeek (0L, SEEK_SET)) return 0;

	/* allocate index */
	idx = *_index = (tDatafileIndex *)malloc ((num_games + 1) * sizeof (struct tDatafileIndex));
//	idx = *_index = auto_alloc_array(*m_machines, tDatafileIndex, (num_games + 1) * sizeof (struct tDatafileIndex));

	if (NULL == idx) return 0;

	/* loop through datafile */
	while (count < num_games && TOKEN_INVALID != token)
	{
		u64 tell;
		u8 *s;

		token = GetNextToken (&s, &tell);
		if (TOKEN_SYMBOL != token) continue;

		/* DATAFILE_TAG_KEY identifies the driver */
		if (!core_strnicmp (DATAFILE_TAG_KEY, (char *)s, strlen (DATAFILE_TAG_KEY)))
		{
			token = GetNextToken (&s, &tell);
			if (TOKEN_EQUALS == token)
			{
				int done = 0;

				token = GetNextToken (&s, &tell);
				while (count < num_games && !done && TOKEN_SYMBOL == token)
				{
					int game_index;
					u8 *p;
					for (p = s; *p; p++)
						*p = tolower(*p);

					game_index = GetGameNameIndex((char *)s);
					if (game_index >= 0)
					{
						idx->driver = &driver_list::driver(game_index);
						idx->offset = tell;
						idx++;
						count++;
						/* done = 1;  Not done, as we must process other clones in list */

					}
					if (!done)
					{
						token = GetNextToken (&s, &tell);

						if (TOKEN_COMMA == token)
							token = GetNextToken (&s, &tell);
						else
							done = 1;	/* end of key field */
					}
				}
			}
		}
	}

	/* mark end of index */
	idx->offset = 0L;
	idx->driver = 0;
	return count;
}

static int index_menuidx (const game_driver *drv, struct tDatafileIndex *d_idx, struct tMenuIndex **_index)
{
	struct tMenuIndex *m_idx;
	const game_driver *gdrv;
	struct tDatafileIndex *gd_idx;
	int cl;
	int m_count = 0;
	u32 token = TOKEN_SYMBOL;

	u64 tell;
	u64 cmdtag_offset = 0;
	u8 *s;

	gdrv = drv;
	do
	{
		gd_idx = d_idx;

		/* find driver in datafile index */
		while (gd_idx->driver)
		{
			if (gd_idx->driver == gdrv) break;
			gd_idx++;
		}

		if (gd_idx->driver == gdrv) break;
		cl = driver_list::clone(*gdrv);
		if (cl == -1) break;
		gdrv = &driver_list::driver(cl);
	} while (!gd_idx->driver && gdrv);

	if (gdrv == 0) return 0;	/* driver not found in Data_file_index */

	/* seek to correct point in datafile */
	if (ParseSeek (gd_idx->offset, SEEK_SET)) return 0;

	/* allocate index */
//	m_idx = *_index = auto_alloc_array(*m_machines, tMenuIndex, MAX_MENUIDX_ENTRIES * sizeof (struct tMenuIndex));
	m_idx = *_index = (tMenuIndex *)malloc (MAX_MENUIDX_ENTRIES * sizeof (struct tMenuIndex));
	if (NULL == m_idx) return 0;

	/* loop through between $cmd= */
	token = GetNextToken (&s, &tell);
	while ((m_count < (MAX_MENUIDX_ENTRIES - 1)) && TOKEN_INVALID != token)
	{
		if (!core_strnicmp (DATAFILE_TAG_KEY, (char *)s, strlen (DATAFILE_TAG_KEY)))
			break;

		/* DATAFILE_TAG_COMMAND identifies the driver */
		if (!core_strnicmp (DATAFILE_TAG_COMMAND, (char *)s, strlen (DATAFILE_TAG_COMMAND)))
		{
			cmdtag_offset = tell;
			token = GetNextToken_ex (&s, &tell);

			if (token == TOKEN_EQUALS)
				token = GetNextToken_ex (&s, &tell);
			else
			{
				while (TOKEN_SYMBOL != token)
					token = GetNextToken_ex (&s, &tell);
			}

			m_idx->menuitem = auto_alloc_array(*m_machines, char, strlen((char *)s)+1);
			strcpy(m_idx->menuitem, (char *)s);

			m_idx->offset = cmdtag_offset;

			m_idx++;
			m_count++;
		}
		token = GetNextToken (&s, &tell);
	}

	/* mark end of index */
	m_idx->offset = 0L;
	m_idx->menuitem = NULL;

	return m_count;
}

static void free_menuidx(struct tMenuIndex **_index)
{
	if (*_index)
	{
		struct tMenuIndex *m_idx = *_index;

		while(m_idx->menuitem != NULL)
		{
			auto_free(*m_machines, m_idx->menuitem);
			m_idx->menuitem = NULL;
			m_idx++;
		}

		auto_free(*m_machines, *_index);
		*_index = NULL;
	}
}

/**************************************************************************
 *	find_command
 **************************************************************************/
static int find_command (const game_driver *drv)
{
	int where;
	int i;
	bool cantfind=0;
	
	if (menu_filename)
	{
		free(menu_filename);
		menu_filename = NULL;
	}

//	FILE *fp2;
//	fp2 = fopen("find_command.txt","a+t");

	for (where = 0; where <= FILE_ROOT; where += FILE_ROOT)
	{
		char filename[80];
		char *base;
		char *base_en;

		filename[0] = '\0';

		base = filename + strlen(filename);
		base_en = filename + strlen(filename);
		
//		fprintf(fp2, "--------base/ baseen ----------------\n");	
//		fprintf(fp2, "base    : %s\n", base);	
//		fprintf(fp2, "base en : %s\n", base_en);	


		for (i = where; i <= where + FILE_MERGED; i += FILE_MERGED)
		{
			int status = 0;
			cantfind=0;
			
			if (i & FILE_MERGED)
			{// 한글로된 공략 단일 파일 로드
				strcpy(base, "dats/command.dat");

//				fprintf(fp2, "--------------- command \n");
//				fprintf(fp2, "%s\n", base);	
//				fprintf(fp2, "%s\n", filename);	

				/* try to open command datafile */
				if (!ParseOpen (filename))
					continue;

				/* create index if necessary */
				if (cmnd_idx[i])
					status = 1;
				else
				{				
					status = (index_datafile (&cmnd_idx[i]) != 0);
					free_menuidx(&menu_idx);
				}

				/* create menu_index */
				
				status = (index_menuidx (drv, cmnd_idx[i], &menu_idx) != 0);

				if (!status)
				{
					cantfind=1;
					
//					fprintf(fp2, "can not find command \n");	

					free_menuidx(&menu_idx);
				}
				ParseClose ();

				if(cantfind)
				{// 한글 공략 파일에 공략 데이터가 없을시 영문 공략 파일내에서 검색
					strcpy(base_en, "dats/command_en.dat");
					
//					fprintf(fp2, "--------------- command_en \n");
//					fprintf(fp2, "%s\n", base_en);	
//					fprintf(fp2, "%s\n", filename);	

					/* try to open command datafile */
					if (!ParseOpen (filename))
						continue;

					/* create index if necessary */
					if (cmnd_idx[i])
					{
						auto_free(*m_machines, cmnd_idx[i]);
						cmnd_idx[i] = 0;
					}
					
					status = (index_datafile (&cmnd_idx[i]) != 0);
					free_menuidx(&menu_idx);
					
					/* create menu_index */					
					status = (index_menuidx (drv, cmnd_idx[i], &menu_idx) != 0);

					if (!status)
						free_menuidx(&menu_idx);
					ParseClose ();					
				}				
				
			}
			else
			{// 개별 공략 파일 로드
				const game_driver *gdrv;
				int cl;
				
				for (gdrv = drv; !status && gdrv && gdrv->name[0] && ((cl = driver_list::clone(*gdrv)) != -1); gdrv = &driver_list::driver(cl))
				{
					strcpy(base, "command\\");
					strcat(base, gdrv->name);
					strcat(base, ".dat");
					
					/* try to open command datafile */
					if (!ParseOpen (filename))
						continue;

					if (cmnd_idx[i])
					{
						auto_free(*m_machines, cmnd_idx[i]);
						cmnd_idx[i] = 0;
					}

					status = (index_datafile (&cmnd_idx[i]) != 0);
					free_menuidx(&menu_idx);

					/* create menu_index */
					status = (index_menuidx (drv, cmnd_idx[i], &menu_idx) != 0);

					if (!status)
						free_menuidx(&menu_idx);

					ParseClose ();
				}
			}

			if (status)
			{
				menu_filename = core_strdup(filename);

				
//				fclose(fp2);
				return 0;
			}
		}
	}


//	fclose(fp2);
	//ErrorMessageBox("return 1");
	return 1;
}


/**************************************************************************
 *	load_datafile_text_ex
 *
 *	Loads text field for a driver into the buffer specified. Specify the
 *	driver, a pointer to the buffer, the buffer size, the index created by
 *	index_datafile(), and the desired text field (e.g., DATAFILE_TAG_BIO).
 *
 *	Returns 0 if successful.
 **************************************************************************/
static int load_datafile_text_ex (char *buffer, int bufsize,
	const char *tag, struct tMenuIndex *m_idx, const int menu_sel)
{
	int offset = 0;
	u32	token = TOKEN_SYMBOL;
//	u32 	prev_token = TOKEN_SYMBOL;
	u8 *s = NULL;
	int len;
	u64 tell;

	*buffer = '\0';

	/* seek to correct point in datafile */
	if (ParseSeek ((m_idx + menu_sel)->offset, SEEK_SET)) return 1;

	/* read text until tag is found */
	while (TOKEN_INVALID != token)
	{
		token = GetNextToken (&s, &tell);

		if (TOKEN_INVALID == token)
			break;

		if (TOKEN_SYMBOL == token)
		{
			/* looking for requested tag */
			if (!core_strnicmp (tag, (char *)s, strlen (tag)))
			{
				token = GetNextToken_ex (&s, &tell);

				if (TOKEN_EQUALS == token)
					token = GetNextToken_ex (&s, &tell);
				else
				{
					while (TOKEN_SYMBOL != token)
						token = GetNextToken_ex (&s, &tell);
				}

				break;
			}
			else if (!core_strnicmp (DATAFILE_TAG_KEY, (char *)s, strlen (DATAFILE_TAG_KEY)))
			{
				token = TOKEN_INVALID;
				break;	/* error: tag missing */
			}
		}
	}

	/* read text until buffer is full or end of entry is encountered */
	while (TOKEN_INVALID != token)
	{
		/* end entry when a tag is encountered */
		if (TOKEN_SYMBOL == token && !core_strnicmp (DATAFILE_TAG_END, (char *)s, strlen (DATAFILE_TAG_END)))
			break;

//		prev_token = token;

		/* translate platform-specific linebreaks to '\n' */
		if (TOKEN_LINEBREAK == token)
			strcpy ((char *)s, "\n");

		/* add this word to the buffer */
		len = strlen ((char *)s);
		if ((len + offset) >= bufsize) break;
		strcpy (buffer, (char *)s);
		buffer += len;
		offset += len;

		token = GetNextToken_ex (&s, &tell);
	}

	return TOKEN_INVALID == token;
}

/**************************************************************************
 *	load_driver_command_ex
 **************************************************************************/
int load_driver_command_ex (const game_driver *drv, char *buffer, int bufsize, const int menu_sel)
{
	*buffer = 0;

	//if (find_command (drv))
	//	return 1;

	if (!menu_filename)
		return 1;

	/* try to open command datafile */
	if (ParseOpen (menu_filename))
	{
		int err;

		err = load_datafile_text_ex (buffer, bufsize,
									 DATAFILE_TAG_COMMAND, menu_idx, menu_sel);

		ParseClose ();

		if (!err)
			return 0;
	}

	return 1;
}


/**************************************************************************
 *	command_sub_menu
 **************************************************************************/
u8 cmd_sub_menu(const game_driver *drv, const char *menu_item[])
{

	if (find_command (drv))
		return 0;

	if (menu_idx)
	{		
		struct tMenuIndex *m_idx = menu_idx;
		int total = 0;

		while(m_idx->menuitem != NULL)
		{
			menu_item[total++] = m_idx->menuitem;
			m_idx++;
		}

		return total;
	}
	

	return 0;
}
#endif

} // namespace ui
