#define FAST_AUDIT
//#define FASTAUDITDBG

#ifdef FAST_AUDIT
#include <windows.h>
#include <ctype.h>
#include <tchar.h>


#include <io.h>
#include "unzip.h"
#include "winui.h"
#include "fileio_ek.h"
#include "hash_ek.h"
#include "unzip_ek.h"

/* return values from VerifyRomSet and VerifySampleSet */
enum summary
{
	F_CORRECT = 0,
	F_MISSING_OPTIONAL,
	F_BEST_AVAILABLE,
	F_INCORRECT,
	F_NOTFOUND,
	F_CHD		//ekmame
};

/* rom status values for tAuditRecord.status */
#define AUD_ROM_GOOD				0x00000001
#define AUD_ROM_NEED_REDUMP			0x00000002
#define AUD_ROM_NOT_FOUND			0x00000004
#define AUD_NOT_AVAILABLE			0x00000008
#define AUD_BAD_CHECKSUM			0x00000010
#define AUD_MEM_ERROR				0x00000020
#define AUD_LENGTH_MISMATCH			0x00000040
#define AUD_ROM_NEED_DUMP			0x00000080
#define AUD_DISK_GOOD				0x00000100
#define AUD_DISK_NOT_FOUND			0x00000200
#define AUD_DISK_BAD_MD5			0x00000400
#define AUD_OPTIONAL_ROM_NOT_FOUND	0x00000800
#define AUD_DISK_NOT_AVAILABLE		0x00001000
#define AUD_DISK_NEED_DUMP			0x00002000
#define AUD_ROM_NOT_FOUND_PARENT	0x00004000
#define AUD_ROM_NOT_FOUND_BIOS		0x00008000

#define AUD_MAX_ROMS		1200	/* maximum roms per driver */

/*************************************
 *
 *  Type definitions
 *
 *************************************/
typedef struct
{
	char rom[256];				/* name of rom file */

	unsigned int explength;		/* expected length of rom file */
	unsigned int length;		/* actual length of rom file */
	const char* exphash;        /* expected hash data */
	char hash[256];             /* computed hash informations */
	int status;					/* status of rom file */
} tAuditRecord;

typedef struct {
	int		iType;
	UINT32	crc32;
	char	szROM[256];
} GAMEROMLIST;

static GAMEROMLIST*	gRomList = 0;
static tAuditRecord *gAudits = 0;


extern void RetrievePaths(void);

extern char rom_path[MAX_DIRS][MAX_PATH];
extern int num_path;

int g_AuditallocCount = 0;
int g_RomlisttallocCount = 0;
/////////////////////////////////////////////////////////////////////////////////////
void freeRam_fastAudit(void)
{
	if(gAudits)
	{
//		logmsg("\ngAudits Free; count = %10d,	addr = %8X", --g_AuditallocCount, (unsigned)gAudits);
		free(gAudits);
	}
	if(gRomList)
	{
//		logmsg("\ngRomList Free; count = %10d,	addr = %8X", --g_RomlisttallocCount, (unsigned)gRomList);
		free(gRomList);
	}

	gAudits  = 0;
	gRomList = 0;
}

int get_game_rom_list(const char *gamename, GAMEROMLIST *lpRomList, int iListBaseIndex)
{
	int pathindex, iCount;
	GAMEROMLIST *lpList;

	iCount	  = 0;
	lpList	  = &lpRomList[iListBaseIndex];

	/* loop over paths */
	for (pathindex = 0; pathindex < num_path; pathindex ++)
	{
		char fullpath[1024];
		/* first look for path/gamename.zip */
		FILE *f;
		snprintf(fullpath, WINUI_ARRAY_LENGTH(fullpath), "%s\\%s.zip", rom_path[pathindex], gamename);
		f = fopen(fullpath, "r");

		/* if the ZIP file exists, proceed */
		if (f != NULL )
		{
//			logmsg("get game rom list full path <%s> \n",fullpath);

			ZIP* zip;
			struct zipent* ent;

			zip = openzip(FILETYPE_ROM, pathindex, fullpath);
			if (zip) {
				while (readzip(zip)) {
					ent = &(zip->ent);

					lpList[iCount].iType = 1;
					lpList[iCount].crc32 = ent->crc32;
					strcpy( lpList[iCount].szROM, ent->name );
					iCount++;
				}

				suspendzip(zip);
			}
		}

		fclose(f);
	}

	return iCount;
}

bool CheckDumpStatus(const char* data, const char *str)
{
	char* res=strstr(data, str);

	if(!res)
		return 0;

	return 1;
}


int FastAuditRomSet (int game, tAuditRecord **audit)
{
	const char *name=NULL;
	const game_driver *gamedrv=NULL;
	const game_driver *drv=NULL;
	UINT8  crcs[4];
	UINT32 crc32;
	const char *parentname=NULL;

	int i, iRomExist, iRomCount, count;
	tAuditRecord *aud=NULL;
	int	err;

	if (!gAudits)
	{
		gAudits = (tAuditRecord *)malloc (AUD_MAX_ROMS * sizeof (tAuditRecord));
		memset(gAudits, 0, AUD_MAX_ROMS * sizeof(tAuditRecord));
//		logmsg("\n Alloc %10d bytes, count = %10d,	addr = %8X", AUD_MAX_ROMS * sizeof (tAuditRecord), g_AuditallocCount++, (unsigned)gAudits);

		// Make sure the memory is cleared - it's needed by the hashing
		//  engine
	}
	if(!gRomList)
	{
		gRomList = (GAMEROMLIST *)malloc (AUD_MAX_ROMS * sizeof (GAMEROMLIST));
		memset(gRomList, 0, AUD_MAX_ROMS * sizeof(GAMEROMLIST));
//		logmsg("\n Romlist Alloc %10d bytes, count = %10d,	addr = %8X", AUD_MAX_ROMS * sizeof (tAuditRecord), g_RomlisttallocCount++, (unsigned)gRomList);
	}


	if (gAudits)
		*audit = aud = gAudits;
	else
	{
		return 0;
	}

	gamedrv = &driver_list::driver(game);
	if (!gamedrv->rom) return -1;

	
	iRomCount = 0;

	/* check for existence of romset */
	/* 롬파일이 있는지 찾는다.*/
	iRomExist = mame_faccess_filepath(gamedrv->name, num_path);

	if (!iRomExist )
	{
		/* 혹시  모를 부모롬을 찾는다. */

//	logmsg("<%s> romExist<%d> <game index count %d>\n", gamedrv->name,iRomExist,game );


//		logmsg( "<%s> not found index <%d>\n", gamedrv->name,game );
		int parentIndex = GetParentIndex(&driver_list::driver(game));
		const char *Getparentname = GetDriverGameName(parentIndex);

		if ((!DriverIsClone(game))||(!mame_faccess_filepath(Getparentname, num_path)))
		{/* 클론롬도 아니고 부모롬 도 없다. ㅠ*/
			return 0;
		}
		else
		{// 클론을 찾지 못햇으나 부모롬을 찾은 경우 (merged rom 인경우 )
//			logmsg( "<%s> not found but parent <<%s>> found \n", gamedrv->name,Getparentname );
			i = get_game_rom_list( Getparentname, gRomList, iRomCount);
			iRomCount += i;

			int GetParentindex =-1;
			GetParentindex= GetGameNameIndex(Getparentname);
//			logmsg( "Clone Not Found --> parent name %s of parent index is : %d	\n",Getparentname, GetParentindex );

			if(GetParentindex !=-1)
			{
				gamedrv = &driver_list::driver(GetParentindex);
//				logmsg( "Clone Not Found --> parent is : %s	\n", gamedrv->name );
			}			
		}
	}
	else 
	{
		/* 부모롬을 찾은 경우 , 찾았으면 롬 정보를 읽어 버퍼에 저장 한다.*/
//		logmsg( "<%s> found index<%d> parent name <%s>\n", gamedrv->name ,game, gamedrv->parent);

		i = get_game_rom_list( gamedrv->name, gRomList, iRomCount );
		iRomCount += i;
	}

	/* 읽어 온 롬의 parent 가 있는지 확인하다.*/
	parentname = gamedrv->parent;
	
	while(core_stricmp(parentname, "0"))	
	{	
//		logmsg( "<%s> found and parent found : [%s]	\n", gamedrv->name,parentname );

		if(mame_faccess_filepath(parentname, num_path))
		{
			i = get_game_rom_list( parentname, gRomList, iRomCount );
			iRomCount += i;		
		}

		parentname=0;
		
		int Getindex =-1;
		Getindex= GetGameNameIndex(parentname);
//		logmsg( "	parent name <%s> of parent index is : <%d>	\n",parentname, Getindex );

		if(Getindex !=-1)
		{
			drv = &driver_list::driver(Getindex);
			parentname =drv->parent;
		}
		else
		{
			break;	
		}
	}

#ifdef FASTAUDITDBG
	logmsg("\n<%s> search result ---------", gamedrv->name );
	for(i=0; i<iRomCount; i++) {
		logmsg("%2d) %d:<%-12s>:%08x\n", i, gRomList[i].iType, gRomList[i].szROM, gRomList[i].crc32 );
	}
	logmsg("\n" );
#endif

	if( !iRomCount ) return 0;

	count = 0;

	const game_driver *gameinx = &driver_list::driver(game);
	machine_config config(*gameinx, MameUIGlobal());

	for (device_t &device : device_iterator(config.root_device()))
	{
		for (const rom_entry *region = rom_first_region(device); region; region = rom_next_region(region))
		{
			for (const rom_entry *rom = rom_first_file(region); rom; rom = rom_next_file(rom))
			{
				if (ROMREGION_ISROMDATA(region))
				{
					name = ROM_GETNAME(rom);
					strcpy (aud->rom, name);
					aud->explength = 0;
					aud->length	   = 0;
					aud->status    = AUD_ROM_GOOD;
//					aud->exphash   = ROM_GETHASHDATA(rom);
//					hash_data_copy(aud->hash, aud->exphash);

					hash_data_copy(aud->hash, ROM_GETHASHDATA(rom));

					count++;
		
			
					crc32 = 0;
					if (hash_data_extract_binary_checksum(aud->hash, HASH_CRC, crcs) != 0)
					{
						/* Store the CRC in a single DWORD */
						crc32 = ((unsigned long)crcs[0] << 24) | ((unsigned long)crcs[1] << 16) |
							    ((unsigned long)crcs[2] <<  8) | ((unsigned long)crcs[3] <<  0);
					}
				
					aud->explength = crc32;
#ifdef FASTAUDITDBG
					logmsg("\n");
					logmsg("[ ROMNAME :<%s> ROMHash:< %s > CRC32:< %08x > ]\n",aud->rom,aud->hash,aud->explength);
#endif
					err = 1;
					
					for(i=0; i<iRomCount; i++) 
					{
						if( gRomList[i].iType == 1 ) // ZIP format
						{
							
							if(!core_stricmp(gRomList[i].szROM, name)) 
							{ 								
								// 파일명으로 찾았으나 CRC가 다른 경우
								if(crc32 && (gRomList[i].crc32 != crc32)) {
									aud->length = gRomList[i].crc32;
									err = 2;
								}
								else 
								{// 파일명 및 CRC 모두 OK
									err = 0; 
								}
								break; 
							}

							// 파일명은 다르나 CRC가 같은 경우
							if(crc32 && (gRomList[i].crc32 == crc32)) 
							{ 	
								err = 0; 
								break; 
							}
						}
						else {
							// ZIP포맷이 아닌 경우 파일명으로만 체크
							if(!core_stricmp(gRomList[i].szROM, name)) { err = 0; break; }
						}
					}
		

					switch(err) 
					{
						case 1:
							if(CheckDumpStatus(aud->hash,"^"))
							{
								//logmsg(" BAD Dump\n", aud->exphash);
								aud->status = AUD_ROM_NEED_REDUMP;
							}
							else if(CheckDumpStatus(aud->hash,"!"))
							{
								//logmsg(" No Dump\n", aud->exphash);
								aud->status = AUD_ROM_NEED_DUMP;
							}
							else if(CheckDumpStatus(aud->rom, "dl-1425.bin"))
							{
								//logmsg(" CPS2 qsound_hle\n", aud->rom);
								aud->status = AUD_ROM_NEED_DUMP;
							}
//							else if (hash_data_has_info(aud->exphash, HASH_INFO_NO_DUMP))
//							{
//								/* not found but it's not good anyway */
//								aud->status = AUD_NOT_AVAILABLE;
//							}
							else if( ROM_ISOPTIONAL(rom) ) {
								aud->status = AUD_OPTIONAL_ROM_NOT_FOUND;
							}
							else {
								aud->status = AUD_ROM_NOT_FOUND;
#ifdef FASTAUDITDBG								
								logmsg("[ Result : ROM Not Found : %d \n",aud->status);
#endif
							}
							break;


						case 2:

							aud->status = AUD_BAD_CHECKSUM;
#ifdef FASTAUDITDBG							
							logmsg("[ Result : BAD CheckSUM : %d \n",aud->status);
#endif
							break;
						case 0: // GOOD
							/* matching hash */
			
							if(CheckDumpStatus(aud->hash,"^"))
							{
								//logmsg(" BAD Dump\n", aud->exphash);
								aud->status = AUD_ROM_NEED_REDUMP;
							}
							else if(CheckDumpStatus(aud->hash,"!"))
							{
								//logmsg(" No Dump\n", aud->exphash);
								aud->status = AUD_ROM_NEED_DUMP;
							}
							else if(CheckDumpStatus(aud->rom, "dl-1425.bin"))
							{
								//logmsg(" CPS2 qsound_hle\n", aud->rom);
								aud->status = AUD_ROM_NEED_DUMP;
							}
#ifdef FASTAUDITDBG
							logmsg("[ Result : GOOD : %d \n",aud->status);
#endif
							break;
					}

					if( !iRomExist )
					{
						//logmsg("------- Rom Not Exist\n");
						aud->status |= 0x80000000;
					}
					aud++;
				}
				// CHD 파일 검색은 공식 마메것으로 대체 
			}
		}
	
	}
	return count;
}

int FastVerifyRomSet (int game)
{
	tAuditRecord			*aud=NULL;
	int						count, i;
	int						archive_status = 0;


	// chd 파일이 필요한 롬셋은 여기서 검사 하지 않는다.
	if (DriverIsHarddisk(game))
	{
		return F_CHD;
	}

	count = FastAuditRomSet(game, &aud);

	if (count == 0) // 롬파일 없음.
	{
		return F_NOTFOUND;
	} 
	else if (count == -1)  // 롬파일 이미 있음.
	{
		return F_CORRECT;
	}

	for(i=0; i<count; i++) {
		archive_status |= aud[i].status;
	}

	if(archive_status & 0x80000000) 
		archive_status ^= 0x80000000; // clear bit


	if (archive_status & (AUD_ROM_NOT_FOUND|AUD_BAD_CHECKSUM|AUD_MEM_ERROR|AUD_LENGTH_MISMATCH|AUD_DISK_NOT_FOUND|AUD_DISK_BAD_MD5)) {
		return F_INCORRECT;
	}

	if (archive_status & (AUD_ROM_NEED_DUMP|AUD_ROM_NEED_REDUMP|AUD_NOT_AVAILABLE|AUD_DISK_NOT_AVAILABLE|AUD_DISK_NEED_DUMP)) {

		return F_BEST_AVAILABLE;
	}
	
	if (archive_status & (AUD_OPTIONAL_ROM_NOT_FOUND)) {
		return F_MISSING_OPTIONAL;
	}

	return F_CORRECT;

}

static const char * RetrieveCHDNames(int romset)
{
	static const char *name = NULL;
	const game_driver *game = &driver_list::driver(romset);
	machine_config config(*game, MameUIGlobal());

	for (device_t &device : device_iterator(config.root_device()))
	{
		for (const rom_entry *region = rom_first_region(device); region != nullptr; region = rom_next_region(region))
		{
			for (const rom_entry *rom = rom_first_file(region); rom != nullptr; rom = rom_next_file(rom))
			{
				if (ROMREGION_ISDISKDATA(region))
				{
					name = ROM_GETNAME(rom);
					break;
				}
			}
		}
	}

	return name;
}

bool RomSetFounds(int index)
{
	char filename[MAX_PATH];
	const char *gamename = GetDriverGameName(index);
	const char *chdname = NULL;
	bool found = false;
	int iRomExist=0;
	int pathindex=0;
	
	// obtain real CHD name from core if game has one
	if (DriverIsHarddisk(index))
		chdname = RetrieveCHDNames(index);

	// don't search for empty romsets (e.g. pong, breakout)
//	if (!DriverUsesRoms(index))
//		return true;

	// parse all paths defined by the user
	for (pathindex = 0; pathindex < num_path; pathindex++)
	{
		snprintf(filename, WINUI_ARRAY_LENGTH(filename), "%s.zip", gamename);
		iRomExist = mame_faccess_fileindex(filename,pathindex);

//		if(iRomExist)
//			logmsg("Slow Audit FOUND! <%s>\n",&filename[0]);
		
		// it could be a merged romset so check if we at least have the parent
		if (!iRomExist && DriverIsClone(index))
		{
			int parent = GetParentIndex(&driver_list::driver(index));
			int parent_found = GetRomAuditResults(parent);

			// don't check clones of BIOSes but continue to next rompath
			if (DriverIsBios(parent))
				continue;

			if (IsAuditResultYes(parent_found)) // parent already found
			{
				found = true;
				return found;
			}
			else // re-check if parent exists
			{
				const char *parentname = GetDriverGameName(parent);
				snprintf(filename, WINUI_ARRAY_LENGTH(filename), "%s.zip", parentname);
				iRomExist = mame_faccess_fileindex(filename,pathindex);

				if(iRomExist)
				{
					found = true;
					return found;
				}
			}
		}

		// maybe is a game with chd and no romset (e.g. taito g-net games)
		if (!iRomExist && DriverIsHarddisk(index))
		{
			snprintf(filename, WINUI_ARRAY_LENGTH(filename), "%s\\%s.chd", gamename, chdname);
			iRomExist = mame_faccess_fileindex(filename,pathindex);
		}

		// let's try the last attempt in the root folder
		if (!iRomExist && DriverIsHarddisk(index))
		{
			snprintf(filename, WINUI_ARRAY_LENGTH(filename), "%s.chd", chdname);
			iRomExist = mame_faccess_fileindex(filename,pathindex);
		}

		// success, so close the file and call core to audit the rom
		if (iRomExist)
		{
			found = true;
			return found;
		}
	}

	// return if we found something or not
	return found;
}

int Mame32FastVerifyRomSet(int game)
{
	int iStatus;

	iStatus = FastVerifyRomSet(game);

	if((iStatus != F_CORRECT)&&(iStatus != F_BEST_AVAILABLE))
	{
		if (!RomSetFounds(game))
		{
			SetRomAuditResults(game, media_auditor::NOTFOUND);
			return media_auditor::NOTFOUND;
		}
		driver_enumerator enumerator(MameUIGlobal(), driver_list::driver(game));
		enumerator.next();
		media_auditor auditor(enumerator);
		media_auditor::summary summary = auditor.audit_media(AUDIT_VALIDATE_FAST);
		util::ovectorstream buffer;
		buffer.clear();
		buffer.seekp(0);
		auditor.winui_summarize(GetDriverGameName(game), &buffer);
		buffer.put('\0');

		SetRomAuditResults(game, summary);
	}
	else
	{
		SetRomAuditResults(game, iStatus);
	}
	return iStatus;
}

#endif

