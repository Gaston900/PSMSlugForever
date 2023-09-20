/***************************************************************************

  M.A.M.E.32  -  Multiple Arcade Machine Emulator for Win32
  Win32 Portions Copyright (C) 1997-2001 Michael Soderstrom and Chris Kirmse

  This file is part of MAME32, and may only be used, modified and
  distributed under the terms of the MAME license, in "readme.txt".
  By continuing to use, modify or distribute this file you indicate
  that you have read the license and understand and accept it fully.

 ***************************************************************************/
/***************************************************************************
  Original Source from EmeraldMame
  2004.5. Modified by DarkCoder for MAME32K PLUS
 ***************************************************************************/

#ifndef MAME32AVI_H
#define MAME32AVI_H

#ifdef MAME_AVI

typedef struct
{
    DWORD   m_Top;
    DWORD   m_Left;
    DWORD   m_Width;
    DWORD   m_Height;
} tRect;

struct MAME_AVI_STATUS_SAVEDIR
{
	char	filename[MAX_PATH];
	UINT32	filesize;
	UINT32	filesizecheck_frame;
	BOOL	pause;
};

struct MAME_AVI_STATUS
{
	char *name;				// test
	char *source_file;
	int index;				// test
	double def_fps, fps;
	UINT32 flags;			/* orientation and other flags; see defines below */
	int frame_skip;
	BOOL frame_cmp, frame_cmp_pre15, frame_cmp_few;
	BOOL wave_record;
	BOOL bmp_16to8_cnv;
	int width, height, depth;
	UINT32 orientation;
	tRect rect;

	BOOL interlace;
	BOOL interlace_odd_number_field;

	UINT32 avi_filesize;
	UINT32 avi_filesizecheck_frame;
	BOOL avi_savefile_pause;

	int avi_width, avi_height, avi_depth;
	tRect avi_rect;
	BOOL avi_smooth_resize_x;
	BOOL avi_smooth_resize_y;


	void *wav_filename;
	int audio_type;
	int audio_channel;
	int audio_samples_per_sec;
	int audio_bitrate;
	int avi_audio_record_type;
	int avi_audio_channel;
	int avi_audio_samples_per_sec;
	int avi_audio_bitrate;
	BOOL avi_audio_cmp;

	int hour, minute, second;

	// DarkCoder
	BOOL force_flip_y;
}; //kt

//#define AVI_AUDIO
BOOL    AviStartCapture(HWND hwnd, char* filename, struct MAME_AVI_STATUS *AviStatus);

void    AviEndCapture(void);

void    AviAddBitmap(running_machine *machine, bitmap_t *tBitmap, UINT32 *pPalEntries);

void    SetAviFPS(int fps);
int     GetAviCapture(void);

//#ifdef AVI_AUDIO
int		AVI_AudioStream_Start(void);
void	AVI_AudioStream_WriteWaveData(char* lpwav, int len);
//#endif

int 	load_16to8_bitmap(void *filename, RGBQUAD *rgbq, char* cnv);
void 	SetAviStatus(struct MAME_AVI_STATUS *status);
struct 	MAME_AVI_STATUS* GetAviStatus(void);

#endif /* MAME_AVI */

#endif /* MAME32AVI_H */
