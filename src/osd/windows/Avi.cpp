/***************************************************************************

  M.A.M.E.32  -  Multiple Arcade machine Emulator for Win32
  Win32 Portions Copyright (C) 1997-2001 Michael Soderstrom and Chris Kirmse

  This file is part of MAME32, and may only be used, modified and
  distributed under the terms of the MAME license, in "readme.txt".
  By continuing to use, modify or distribute this file you indicate
  that you have read the license and understand and accept it fully.

***************************************************************************/
#define MAME_AVI

#ifdef MAME_AVI

/***************************************************************************

  Avi.c

  AVI capture code contributed by John Zissopoulos
                <zissop@theseas.softlab.ece.ntua.gr>

  How it works
  ==================================================

    AviStartCapture(filename, width, height, depth);

    do {
        AviAddBitmap(tBitmap, pPalEntries)
    } while (!done);

    AviEndCapture();

***************************************************************************/

/***************************************************************************
  Original Source from EmeraldMame
  2004.5. Modified by DarkCoder for EK-MAME Plus!
***************************************************************************/
#include "emu.h"

// #define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <commctrl.h>
#include <commdlg.h>
#include <string.h>
#include <sys/stat.h>
#include <wingdi.h>
#include <tchar.h>
/* to shutup the warnings about functions were NOT calling in vfw.h */
#ifdef CDECL
#undef CDECL
#define CDECL CLIB_DECL
#endif
#include <vfw.h>

#include "winui/bitmask.h"	// for LPBITS structure definition (used in winui/options.h)
#include "winui/screenshot.h"	// for MYBITMAPINFO structure definition (used in winui/winui.h)
#include "drawgfx.h"	// tRect structure defined
#include "video.h"		//"Display.h"
#include "Avi.h"
#include "../../frontend/mame/ui/ui.h"
#include "winui/winui_util.h"
#ifndef BMP_PALSIZE
#define BMP_PALSIZE		256
#endif

//#include "win32text.h"

//#include "resource.h"
#define RGB_RED(rgb)		(((rgb) >> 16) & 0xff)
#define RGB_GREEN(rgb)		(((rgb) >> 8) & 0xff)
#define RGB_BLUE(rgb)		((rgb) & 0xff)

enum _bitmap_format
{
	BITMAP_FORMAT_INVALID = 0,		/* invalid format */
	BITMAP_FORMAT_INDEXED8,			/* 8bpp indexed */
	BITMAP_FORMAT_INDEXED16,		/* 16bpp indexed */
	BITMAP_FORMAT_INDEXED32,		/* 32bpp indexed */
	BITMAP_FORMAT_INDEXED64,		/* 64bpp indexed */
	BITMAP_FORMAT_RGB15,			/* 15bpp 5-5-5 RGB */
	BITMAP_FORMAT_RGB32,			/* 32bpp 8-8-8 RGB */
	BITMAP_FORMAT_ARGB32,			/* 32bpp 8-8-8-8 ARGB */
	BITMAP_FORMAT_YUY16,			/* 16bpp 8-8 Y/Cb, Y/Cr in sequence */
	BITMAP_FORMAT_LAST
};

/***************************************************************************
    function prototypes
 ***************************************************************************/

static BOOL     AVI_Check_Version(void);

static void     AVI_Close(char* filename);
static char*    AVI_Convert_Bitmap(running_machine *machine, bitmap_t *tBitmap, UINT32 *pPalEntries);
static void     AVI_Message_Error(void);


static BOOL		AVI_ReInit(char* filename);
static void		AVI_CloseFile(char* filename);

static BOOL     AVI_Init(HWND hwnd ,char* filename, int width, int height, int depth, double fps, tRect *rect);

void			AVI_Create_8bit_Bitmap(void);
static void		AVI_Create_24bit_Bitmap(void);
static void		AVI_Convert_16to8_Bitmap(char *pSrcBitmap);
static void		AVI_Convert_16to24_Bitmap(char *pSrcBitmap);


static void		AVI_Convert_16to24_TVInterlace_Bitmap(char *pSrcBitmap, int l);
static void		AVI_Convert_16to24_TVInterlace_s_Bitmap(char *pSrcBitmap, int l);
static void		AVI_Convert_16to24_TVInterlace_sxy_Bitmap(char *pSrcBitmap, int l);
static void		AVI_Convert_16to24_TVInterlace_sy_Bitmap(char *pSrcBitmap, int l);

// by DarkCoder
void TransformBitmap32to16(running_machine *machine, bitmap_t &tBitmap, unsigned short *dst, UINT32 *pPalEntries);
void TransformBitmap15to16(running_machine *machine, bitmap_t &tBitmap, unsigned short *dst, UINT32 *pPalEntries);
void TransformBitmap16to16(running_machine *machine, bitmap_t &tBitmap, unsigned short *dst, UINT32 *pPalEntries);
void TransformBitmap8to16 (running_machine *machine, bitmap_t &tBitmap, unsigned short *dst, UINT32 *pPalEntries);

/***************************************************************************
    External variables
 ***************************************************************************/

/***************************************************************************
    Internal variables
 ***************************************************************************/
static int			bAviCapture  = 0;

static PAVIFILE     pfile        = NULL;
static PAVISTREAM   psCompressed = NULL;
static PAVISTREAM   ps           = NULL;

// AVI_AUDIO
static PAVISTREAM   audio_ps     = NULL;

static int          nAviAudioSamples   = 0;
static BOOL         bAviAudioRecord  = FALSE;
static char*		pAviAudioBuf = NULL;
static int			nAviAudioBufSize	= 0;

static LONG			lAviAudioBytesWritten = 0;
static LONG			lAviAudioBytesWrittenMax = 0;
static unsigned __int64	nAviAudioFileSize = 0;
// end AVI_AUDIO

static BOOL         bAviError    = FALSE;
static int          nAviFrames;

static DWORD        nAviFPS = 0;
static char         aviFilename[MAX_PATH * 2];
static char         aviBaseFilename[_MAX_PATH];

static char         wavFilename[MAX_PATH * 2];
static char         wavBaseFilename[_MAX_PATH];


#define AVI_MAX_FRAME_CMP 64

static tRect        rectAvi, rectAviSrc;
static int			nAviWidth, nAviHeight;
static int			nAviSrcWidth, nAviSrcHeight;
static int			nAviDepthAvi, nAviDepthSrc;
static int			nAviOrientation = 0;
static int			nAviFlipX, nAviFlipY;
static int			nAviBitmapSize = 0;

static char         *pAviBitmapTemp[AVI_MAX_FRAME_CMP];
static int			nAviTempSize = 0;
static int			nAviTempCount;
static int			nAviCountSub;
static double		AviTempFps;
static double		AviSlFps;
static double		fAviTempNext;
static int			AviTempNext;
static int			AviTempS, AviTempE, AviTempN;
static int          nAviFrameCmp     = 0;
static int          nAviFrameResize  = 0;
static BOOL			bAviFile_Divides = FALSE;
static int          nAviFile_DividesCount  = 0;
static BOOL			bAvi_TVInterlace;
static int          nAvi_TVInterlace_Count;
static LONG lSampWritten  = 0;
static LONG lBytesWritten = 0;
static LONG lAviBytesWrittenMax = 0;

static unsigned __int64         nAviFileSize;
static unsigned __int64         nAviFileSizeMax;

static struct MAME_AVI_STATUS Avi_StatusAvi;

static char			*pAviBitmap_bitConv = NULL;

static double		AviFps = 0;
static DWORD Avi_setfps,Avi_setfpsleft;

RGBQUAD rgb16to8[256] = {
	{   0,   0,   0 }, { 109,   0,   0 }, { 146,   0,   0 }, { 182,   0,   0 },	/*   4 */
	{ 219,   0,   0 }, { 255,   0,   0 }, { 109,  73,   0 }, { 146,  73,   0 },	/*   8 */
	{ 182,  73,   0 }, { 219,  73,   0 }, { 255,  73,   0 }, {   0, 109,   0 },	/*  12 */
	{ 255, 109,   0 }, {   0, 146,   0 }, { 109, 146,   0 }, { 146, 146,   0 },	/*  16 */
	{ 182, 146,   0 }, { 255, 146,   0 }, {   0, 182,   0 }, { 219, 182,   0 },	/*  20 */
	{ 255, 182,   0 }, {   0, 219,   0 }, { 109, 219,   0 }, { 255, 219,   0 },	/*  24 */
	{   0, 255,   0 }, { 109, 255,   0 }, { 146, 255,   0 }, { 182, 255,   0 },	/*  28 */
	{ 255, 255,   0 }, {  73,   0,  85 }, { 146,   0,  85 }, { 182,   0,  85 },	/*  32 */
	{ 255,   0,  85 }, {  73,  36,  85 }, { 146,  36,  85 }, { 182,  36,  85 },	/*  36 */
	{ 219,  36,  85 }, {   0,  73,  85 }, { 109,  73,  85 }, { 146,  73,  85 },	/*  40 */
	{ 219,  73,  85 }, { 255,  73,  85 }, { 182, 109,  85 }, { 219, 109,  85 },	/*  44 */
	{   0, 146,  85 }, {  73, 146,  85 }, { 146, 146,  85 }, { 182, 146,  85 },	/*  48 */
	{ 255, 146,  85 }, {   0, 182,  85 }, { 182, 182,  85 }, { 255, 182,  85 },	/*  52 */
	{  36, 219,  85 }, { 109, 219,  85 }, { 255, 219,  85 }, {  73, 255,  85 },	/*  56 */
	{ 146, 255,  85 }, { 182, 255,  85 }, { 255, 255,  85 }, { 255,   0, 170 },	/*  60 */
	{   0,  36, 170 }, {  36,  36, 170 }, { 109,  36, 170 }, { 146,  36, 170 },	/*  64 */
	{ 182,  36, 170 }, { 255,  36, 170 }, {  73,  73, 170 }, { 146,  73, 170 },	/*  68 */
	{ 219,  73, 170 }, { 255,  73, 170 }, {   0, 109, 170 }, {  73, 109, 170 },	/*  72 */
	{ 146, 109, 170 }, { 182, 109, 170 }, { 219, 109, 170 }, { 255, 109, 170 },	/*  76 */
	{   0, 146, 170 }, {  73, 146, 170 }, { 146, 146, 170 }, { 182, 146, 170 },	/*  80 */
	{ 219, 146, 170 }, { 255, 146, 170 }, {  36, 182, 170 }, { 219, 182, 170 },	/*  84 */
	{ 255, 182, 170 }, {  73, 219, 170 }, { 109, 219, 170 }, { 146, 219, 170 },	/*  88 */
	{ 219, 219, 170 }, { 255, 219, 170 }, {   0, 255, 170 }, { 109, 255, 170 },	/*  92 */
	{ 146, 255, 170 }, { 182, 255, 170 }, { 255, 255, 170 }, { 219,   0, 255 },	/*  96 */
	{ 255,   0, 255 }, {   0,  36, 255 }, {  36,  36, 255 }, {  73,  36, 255 },	/* 100 */
	{ 109,  36, 255 }, { 146,  36, 255 }, { 219,  36, 255 }, { 255,  36, 255 },	/* 104 */
	{  73,  73, 255 }, { 146,  73, 255 }, { 182,  73, 255 }, { 219,  73, 255 },	/* 108 */
	{ 255,  73, 255 }, {   0, 109, 255 }, { 109, 109, 255 }, { 146, 109, 255 },	/* 112 */
	{ 182, 109, 255 }, { 255, 109, 255 }, {   0, 146, 255 }, {  73, 146, 255 },	/* 116 */
	{ 109, 146, 255 }, { 146, 146, 255 }, { 182, 146, 255 }, { 219, 146, 255 },	/* 120 */
	{ 255, 146, 255 }, {   0, 182, 255 }, {  73, 182, 255 }, { 146, 182, 255 },	/* 124 */
	{ 219, 182, 255 }, { 255, 182, 255 }, {   0, 219, 255 }, {  73, 219, 255 },	/* 128 */
	{ 146, 219, 255 }, { 255, 219, 255 }, {   0, 255, 255 }, {  73, 255, 255 },	/* 132 */
	{ 109, 255, 255 }, { 146, 255, 255 }, { 219, 255, 255 }, {  36,  36,   0 },	/* 136 */
	{ 182, 109,   0 }, { 219, 109,   0 }, { 219, 146,   0 }, { 146, 219,   0 },	/* 140 */
	{ 219,   0,  85 }, { 182,  73,  85 }, {  36, 109,  85 }, { 109, 109,  85 },	/* 144 */
	{ 146, 109,  85 }, { 255, 109,  85 }, { 219, 182,  85 }, {   0, 255,  85 },	/* 148 */
	{ 219,   0, 170 }, { 219,  36, 170 }, { 109,  73, 170 }, { 109, 109, 170 },	/* 152 */
	{ 219, 255, 170 }, {  36,  73, 255 }, {  73, 109, 255 }, { 219, 109, 255 },	/* 156 */
	{ 182, 182, 255 }, { 219, 219, 255 }, { 146, 109,   0 }, { 109,  36,  85 },	/* 160 */
	{ 255,  36,  85 }, {   0, 219,  85 }, { 146, 219,  85 }, { 182,   0, 170 },	/* 164 */
	{ 182,  73, 170 }, {   0, 182, 170 }, { 146, 182, 170 }, {  73, 255, 170 },	/* 168 */
	{ 146,   0, 255 }, { 109, 109,   0 }, { 109, 182,   0 }, { 219, 255,   0 },	/* 172 */
	{ 109,   0,  85 }, { 109, 182,  85 }, { 219, 255,  85 }, {  36, 109, 255 },	/* 176 */
	{ 182, 219, 255 }, {  73,  73,   0 }, {   0,  36,  85 }, {  73,  73,  85 },	/* 180 */
	{ 219, 146,  85 }, {  73,  36, 170 }, {   0,  73, 170 }, { 182, 182, 170 },	/* 184 */
	{   0, 219, 170 }, {  36, 182,   0 }, {  36, 219,   0 }, {  36, 255,   0 },	/* 188 */
	{ 109, 146,  85 }, {   0,   0, 170 }, { 109, 146, 170 }, { 182, 219, 170 },	/* 192 */
	{ 182,  36, 255 }, { 109,  73, 255 }, {  36, 182, 255 }, { 109, 182, 255 },	/* 196 */
	{ 109, 219, 255 }, { 182, 255, 255 }, {  73, 182, 170 }, { 109, 182, 170 },	/* 200 */
	{  73,   0,   0 }, { 182,  36,   0 }, { 219,  36,   0 }, { 255,  36,   0 },	/* 204 */
	{ 219, 219,   0 }, { 146, 182,  85 }, { 219, 219,  85 }, {  36, 146,   0 },	/* 208 */
	{ 182, 219,   0 }, {  36, 146,  85 }, {  36, 182,  85 }, {  73, 219,  85 },	/* 212 */
	{ 182, 219,  85 }, {  36, 109, 170 }, {  36, 146, 170 }, { 182,   0, 255 },	/* 216 */
	{  36, 146, 255 }, {  36, 219, 255 }, { 146, 182,   0 }, {   0, 109,  85 },	/* 220 */
	{  36, 255,  85 }, { 146,   0, 170 }, {   0,   0, 255 }, { 146,  36,   0 },	/* 224 */
	{  36, 109,   0 }, {  36, 255, 170 }, {   0,  73, 255 }, {  36, 255, 255 },	/* 228 */
	{ 109,   0, 170 }, {   0,   0,  85 }, { 109,   0, 255 }, {  36, 219, 170 },	/* 232 */
	{ 109, 255,  85 }, {  73, 182,  85 }, { 109,  36,   0 }, {  73, 182,   0 },	/* 236 */
	{  73, 219,   0 }, {  36,  73, 170 }, { 182, 182,   0 }, {  73, 109,  85 },	/* 240 */
	{   0,  73,   0 }, {  73, 146,   0 }, {  36,   0, 170 }, {  73, 255,   0 },	/* 244 */
	{  36,  36,  85 }, {  36,   0,  85 }, {  36,   0, 255 }, {  73, 109,   0 },	/* 248 */
	{  73,  36,   0 }, {  36,  73,  85 }, {  73,   0, 170 }, {  73,   0, 255 },	/* 252 */
	{  36,  73,   0 }, {  36,   0,   0 }, {   0,  36,   0 }, { 255, 255, 255 },	/* 256 */
};

unsigned char rgb16to8idx[512] = {
	  0,   0, 229, 229, 189, 189, 222, 222, 	// 8
	254, 254, 178, 178,  60,  60,  97,  97, 	// 16
	240, 240,  37,  37, 182, 182, 226, 226, 	// 24
	 11,  11, 219, 219,  70,  70, 109, 109, 	// 32
	 13,  13,  44,  44,  76,  76, 114, 114, 	// 40
	 18,  18,  49,  49, 165, 165, 121, 121, 	// 48
	 21,  21, 161, 161, 184, 184, 126, 126, 	// 56
	 24,  24, 147, 147,  90,  90, 130, 130, 	// 64
	253, 253, 245, 245, 242, 242, 246, 246, 	// 72
	135, 135, 244, 244,  61,  61,  98,  98, 	// 80
	252, 252, 249, 249, 237, 237, 153, 153, 	// 88
	224, 224, 142, 142, 213, 213, 175, 175, 	// 96
	207, 207, 209, 209, 214, 214, 216, 216, 	// 104
	185, 185, 210, 210,  82,  82, 194, 194, 	// 112
	186, 186,  52,  52, 231, 231, 217, 217, 	// 120
	187, 187, 220, 220, 225, 225, 227, 227, 	// 128
	200, 200,  29,  29, 250, 250, 251, 251, 	// 136
	248, 248,  33,  33, 181, 181,  99,  99, 	// 144
	177, 177, 179, 179,  66,  66, 104, 104, 	// 152
	247, 247, 239, 239,  71,  71, 154, 154, 	// 160
	241, 241,  45,  45,  77,  77, 115, 115, 	// 168
	235, 235, 233, 233, 198, 198, 122, 122, 	// 176
	236, 236, 211, 211,  85,  85, 127, 127, 	// 184
	243, 243,  55,  55, 167, 167, 131, 131, 	// 192
	  1,   1, 172, 172, 228, 228, 230, 230, 	// 200
	234, 234, 159, 159,  62,  62, 100, 100, 	// 208
	  6,   6,  38,  38, 150, 150, 193, 193, 	// 216
	169, 169, 143, 143, 151, 151, 110, 110, 	// 224
	 14,  14, 188, 188, 190, 190, 116, 116, 	// 232
	170, 170, 173, 173, 199, 199, 195, 195, 	// 240
	 22,  22,  53,  53,  86,  86, 196, 196, 	// 248
	 25,  25, 232, 232,  91,  91, 132, 132, 	// 256
	  2,   2,  30,  30, 221, 221, 168, 168, 	// 264
	223, 223,  34,  34,  63,  63, 101, 101, 	// 272
	  7,   7,  39,  39,  67,  67, 105, 105, 	// 280
	158, 158, 144, 144,  72,  72, 111, 111, 	// 288
	 15,  15,  46,  46,  78,  78, 117, 117, 	// 296
	218, 218, 205, 205, 166, 166, 123, 123, 	// 304
	139, 139, 162, 162,  87,  87, 128, 128, 	// 312
	 26,  26,  56,  56,  92,  92, 133, 133, 	// 320
	  3,   3,  31,  31, 163, 163, 215, 215, 	// 328
	201, 201,  35,  35,  64,  64, 192, 192, 	// 336
	  8,   8, 141, 141, 164, 164, 106, 106, 	// 344
	136, 136,  42,  42,  73,  73, 112, 112, 	// 352
	 16,  16,  47,  47,  79,  79, 118, 118, 	// 360
	238, 238,  50,  50, 183, 183, 156, 156, 	// 368
	208, 208, 212, 212, 191, 191, 176, 176, 	// 376
	 27,  27,  57,  57,  93,  93, 197, 197, 	// 384
	  4,   4, 140, 140, 148, 148,  95,  95, 	// 392
	202, 202,  36,  36, 149, 149, 102, 102, 	// 400
	  9,   9,  40,  40,  68,  68, 107, 107, 	// 408
	137, 137,  43,  43,  74,  74, 155, 155, 	// 416
	138, 138, 180, 180,  80,  80, 119, 119, 	// 424
	 19,  19, 146, 146,  83,  83, 124, 124, 	// 432
	204, 204, 206, 206,  88,  88, 157, 157, 	// 440
	171, 171, 174, 174, 152, 152, 134, 134, 	// 448
	  5,   5,  32,  32,  59,  59,  96,  96, 	// 456
	203, 203, 160, 160,  65,  65, 103, 103, 	// 464
	 10,  10,  41,  41,  69,  69, 108, 108, 	// 472
	 12,  12, 145, 145,  75,  75, 113, 113, 	// 480
	 17,  17,  48,  48,  81,  81, 120, 120, 	// 488
	 20,  20,  51,  51,  84,  84, 125, 125, 	// 496
	 23,  23,  54,  54,  89,  89, 129, 129, 	// 504
	 28,  28,  58,  58,  94,  94, 255, 255, 	// 512
};

/*
int load_16to8_bitmap(void *filename, RGBQUAD *rgbq, char* cnv)
{
	int bmpfile = -1;
	char *bm;
	BITMAPINFOHEADER    bmiHeader;
	BITMAPFILEHEADER	bmfh;

	bmpfile = open(filename, O_RDONLY | O_BINARY);
	if (bmpfile == -1) return -1;

	read(bmpfile, &bmfh, sizeof(BITMAPFILEHEADER));

	bm = (char*)(&bmfh.bfType);
	if ( bm[0]!='B' || bm[1]!='M' ) goto error;



	read(bmpfile, &bmiHeader, sizeof(BITMAPINFOHEADER));

	if (bmiHeader.biBitCount		!= 8		||
		bmiHeader.biWidth			!= 256		||
		bmiHeader.biHeight			!= 128		||
		bmiHeader.biCompression		!= BI_RGB	||
		bmiHeader.biClrUsed			>  256
		) goto error;


	{
		int sz = bmiHeader.biClrUsed;
		if (sz == 0) sz=256;
		memset(rgbq, 0, sizeof(RGBQUAD)*256);
		read(bmpfile, rgbq, sizeof(RGBQUAD) * sz);
	}

	{
		char buf[32768];
		int x,y,i;
		int r,g,b,rr,gg,bb;
		FILE *fp;

		for(y=0; y<bmiHeader.biHeight; y++)
			read(bmpfile, &buf[(bmiHeader.biHeight-1-y) * ((bmiHeader.biWidth * (bmiHeader.biBitCount/8)+3)&~3)], (bmiHeader.biWidth * (bmiHeader.biBitCount/8)+3)&~3);

		i=0;
		for(r=0; r<32; r++)
		{
			for(g=0; g<32; g++)
			{
				for(b=0; b<32; b++)
				{
					x = (r + (b&0x7)*32);
					y = (g + (b>>3)*32);
					cnv[i++] = buf[x+y*256];
				}
			}
		}

		fp = fopen( "16to8pl.txt", "wt" );

		i = 0;
		fprintf( fp, "RGBQUAD rgb16to8[256] = {\n" );
		for(i=0; i<256; i+=4 ) {
			fprintf( fp, "\t{ %3u, %3u, %3u }, ", 
				(unsigned char)rgbq[i].rgbRed, (unsigned char)rgbq[i].rgbGreen, (unsigned char)rgbq[i].rgbBlue );
			fprintf( fp, "{ %3u, %3u, %3u }, ", 
				(unsigned char)rgbq[i+1].rgbRed, (unsigned char)rgbq[i+1].rgbGreen, (unsigned char)rgbq[i+1].rgbBlue);
			fprintf( fp, "{ %3u, %3u, %3u }, ", 
				(unsigned char)rgbq[i+2].rgbRed, (unsigned char)rgbq[i+2].rgbGreen, (unsigned char)rgbq[i+2].rgbBlue);
			fprintf( fp, "{ %3u, %3u, %3u },\t// %3d\n", 
				(unsigned char)rgbq[i+3].rgbRed, (unsigned char)rgbq[i+3].rgbGreen, (unsigned char)rgbq[i+3].rgbBlue, (i+4) );
		}
		fprintf( fp, "};\n\n");

		fprintf( fp, "unsigned char rgb16to8idx[512] = {\n");
		i = 0;
		for(r=0; r<8; r++)
		{
			for(g=0; g<8; g++)
			{
				fprintf( fp, "\t");
				for(b=0; b<8; b++)
				{
					rr=r*4; gg=g*4; bb=b*4;

					x = (rr + (bb&0x7)*32);
					y = (gg + (bb>>3)*32);

					i++;
					fprintf( fp, "%3u, ", (unsigned char)buf[x+(y*256)] );
				}
				fprintf( fp, "\t// %d\n", i );
			}
		}
		fprintf( fp, "};\n");
		fclose(fp);
	}

	close(bmpfile);
	return 0;
error:
	close(bmpfile);
	return -1;
}
*/

#if 0
static void delete_file(const char *filename)
{
	struct stat s;
	if (stat(filename, &s) == 0)
		DeleteFile(filename);
}
#endif

// AVI_AUDIO
#include "wav.h"

void* Avi_Get_AudioStreamInfo(LONG *formatSt,LONG *formatLen, AVISTREAMINFO *sinfo,
							  const char *filename, struct WAV_WAVEFORMAT *wfm)
{
	PAVISTREAM pstm;
	int wavfile;
	void *format;

	memset(sinfo,0,sizeof(AVISTREAMINFO));
	sinfo->fccType = streamtypeAUDIO;
	sinfo->dwFlags = AVIF_ISINTERLEAVED;
	sinfo->dwScale = wfm->channel*(wfm->bitrate/8);
	sinfo->dwRate = wfm->samplespersec * sinfo->dwScale;
	sinfo->dwInitialFrames = 1;
	sinfo->dwQuality = 0;
	sinfo->dwSampleSize = wfm->channel*(wfm->bitrate/8);

 
	wavfile = wav_wavefile_create(filename, wfm->samplespersec, wfm->bitrate, wfm->channel);
	if (wavfile == -1)
		return NULL;
	wav_wavefile_close(wavfile);

	AVIStreamOpenFromFile(&pstm,LPWSTR(filename),streamtypeAUDIO,0,
										OF_READ | OF_SHARE_DENY_NONE,NULL);

	*formatSt=AVIStreamStart(pstm);


	if (AVIStreamReadFormat(pstm,*formatSt,NULL,formatLen)!=0)
		goto ERR;
	if ((format=malloc(*formatLen))==NULL)
		goto ERR;
	if (AVIStreamReadFormat(pstm,*formatSt,format,formatLen)!=0)
	{
		free(format);
		goto ERR;
	}

	AVIStreamRelease(pstm);
	delete_file(filename);
	return format;
ERR:
	AVIStreamRelease(pstm);
	delete_file(filename);
	return NULL;

}



int CopyStream(PAVIFILE pavi)
{
	AVISTREAMINFO si;
	LONG st,leng;
	LPVOID p;
	PAVISTREAM ptmp;

	extern struct WAV_WAVEFORMAT mame_mixer_dstwfm;
	p = Avi_Get_AudioStreamInfo(&st, &leng, &si, "avi_audio_temp.wav", &mame_mixer_dstwfm);
	if (p == NULL)
		goto ERR;

	if (AVIFileCreateStream(pavi,&ptmp,&si)!=0)
	{	free(p);	goto ERR;	}

	if (AVIStreamSetFormat(ptmp,st,p,leng)!=0)
	{	free(p);	goto ERR;	}

	audio_ps = ptmp;
	nAviAudioSamples = st;
	
	free(p);
	return 0;
ERR:
	return -1;
}

// end AVI_AUDIO


/***************************************************************************
    External variables
 ***************************************************************************/

/* Set frames per second */
void SetAviFPS(int fps)
{
    nAviFPS = fps;
}

/* Is AVI capturing initialized? */
int GetAviCapture(void)
{
    return bAviCapture;
}

/* Start capture, initialize */
BOOL AviStartCapture(HWND hwnd, char* filename, struct MAME_AVI_STATUS *AviStatus)
{
	extern int			nAviFrameSkip;
	extern unsigned int	nAviFrameCount;
	extern unsigned int	nAviFrameCountStart;
	extern int			nAviAudioRecord;
	int i;
	double fps, cnvfps;

    if (bAviCapture || (!AVI_Check_Version()))
	{
        return FALSE;
	}

	Avi_StatusAvi = *AviStatus;
	
	fps = AviStatus->def_fps * ((double)(12-AviStatus->frame_skip) / 12.0);
	cnvfps = AviStatus->fps * ((double)(12-AviStatus->frame_skip) / 12.0);


	if (cnvfps <= 0) cnvfps = fps;
	AviSlFps = cnvfps / fps;

	AviFps = fps;
	for(i=0; i<AVI_MAX_FRAME_CMP; i++)
		pAviBitmapTemp[i] = NULL;


	nAviFrameCmp=0;
	if (AviStatus->frame_cmp == TRUE)
	{
		nAviFrameCmp=3;
		if (AviStatus->frame_cmp_pre15 == TRUE)	nAviFrameCmp=1;
		if (AviStatus->frame_cmp_few == TRUE)	nAviFrameCmp=2;
	}
	if (AviStatus->fps == AviStatus->def_fps)	nAviFrameCmp=0;

	AviTempFps = AviFps * AviSlFps;
	fAviTempNext = (AviFps/AviTempFps) * 65536.0;
	{
		int dummy;
		dummy = fAviTempNext;
		AviTempNext = fAviTempNext;

		dummy ^= 0xffffffff;
		if(dummy) dummy = 0;
		dummy++;
	}
	AviFps *= AviSlFps;

	Avi_setfps = AviFps;
	Avi_setfpsleft = AviFps * 1000000.0;


	AviTempS		= 0;
	AviTempN		= AviTempS;
	AviTempE		= AviTempS + AviTempNext;

	nAviTempCount  = 0;
	nAviCountSub   = 0;
	nAviTempSize   = (AviTempNext + 0x1ffff) >> 16;
	nAviBitmapSize = 0;
    
	nAviFrames   = 0;
    bAviError    = FALSE;
	nAvi_TVInterlace_Count = 0;

	if (AviTempNext < 0x10000)
	{
		if (nAviFrameCmp) {nAviFrameCmp = 1;	nAviTempSize = 3;}
		AviTempE = 0;
	}

	nAviDepthSrc = AviStatus->depth;
	if (nAviDepthSrc > 8)  nAviDepthSrc = 16;
	if (nAviDepthSrc <= 8) {nAviFrameCmp = 0;}
	if (nAviFrameCmp == 0) nAviTempSize = 1;

	nAviDepthAvi = AviStatus->avi_depth;

	nAviSrcWidth  = AviStatus->width;
	nAviSrcHeight = AviStatus->height;
	rectAviSrc    = AviStatus->rect;

	nAviOrientation = AviStatus->orientation;
	nAviFlipX       = nAviOrientation & ORIENTATION_FLIP_X;
	nAviFlipY       = nAviOrientation & ORIENTATION_FLIP_Y;

	if( AviStatus->force_flip_y ) {
		nAviFlipY ^= ORIENTATION_FLIP_Y;
	}
	
	if (nAviDepthAvi == 24 && nAviDepthSrc == 16)
	{
		bAvi_TVInterlace = AviStatus->interlace;
		rectAvi    = AviStatus->avi_rect;
		nAviWidth  = AviStatus->avi_width;
		nAviHeight = AviStatus->avi_height;
	}
	else
	{
		bAvi_TVInterlace = FALSE;
		rectAvi    = AviStatus->rect;
		nAviWidth  = AviStatus->rect.m_Width;
		nAviHeight = AviStatus->rect.m_Height;
	}

	/*
	logmsg( "AviStartCapture()----------------------\n" );
	logmsg( "game driver: %s\n", AviStatus->source_file );
	logmsg( "width, height        : %d x %d\n", AviStatus->width, AviStatus->height );
	logmsg( "avi_width, avi_height: %d x %d\n", AviStatus->avi_width, AviStatus->avi_height );
	logmsg( "rect size     : L:%d T:%d %d x %d\n", 
			AviStatus->rect.m_Left, AviStatus->rect.m_Top,
			AviStatus->rect.m_Width, AviStatus->rect.m_Height );
	logmsg( "avi_rect size : L:%d T:%d %d x %d\n", 
			AviStatus->avi_rect.m_Left, AviStatus->avi_rect.m_Top,
			AviStatus->avi_rect.m_Width, AviStatus->avi_rect.m_Height );
	logmsg( "avi_smooth_resize: x:%d y:%d\n", AviStatus->avi_smooth_resize_x, AviStatus->avi_smooth_resize_y );
	logmsg( "orientation : %d\n", AviStatus->orientation & ORIENTATION_MASK );
	logmsg( "flip        : x:%d y:%d\n", AviStatus->orientation & ORIENTATION_FLIP_X, AviStatus->orientation & ORIENTATION_FLIP_Y );
	logmsg( "depth & avi_depth: %d %d\n", nAviDepthSrc, nAviDepthAvi );
	logmsg( "----------------------\n" );
	*/

	if (rectAvi.m_Width > nAviWidth) rectAvi.m_Width = nAviWidth;
	if (bAvi_TVInterlace == TRUE)
	{
		if (rectAvi.m_Height > nAviHeight/2) 
		{
			rectAvi.m_Height = nAviHeight/2; 
			rectAvi.m_Width  = nAviHeight*(3/4);
		}
		rectAvi.m_Top = (nAviHeight/2 - rectAvi.m_Height)/2;
		rectAvi.m_Left = (nAviWidth - rectAvi.m_Width)/2;

		Avi_setfps = AviFps / 2;
		Avi_setfpsleft = AviFps * 500000.0;
	} 
	else
	{
		if (rectAvi.m_Height > nAviHeight) 
		{
			rectAvi.m_Height = nAviHeight; 
			rectAvi.m_Width  = nAviHeight*(3/4);
		}
		rectAvi.m_Left = (nAviWidth - rectAvi.m_Width)/2;
		rectAvi.m_Top = (nAviHeight - rectAvi.m_Height)/2;
	}


	nAviFrameResize = 0;
	if (rectAvi.m_Width != rectAviSrc.m_Width || rectAvi.m_Height != rectAviSrc.m_Height) 
		nAviFrameResize = 1;

	nAviFile_DividesCount    = 0;
	nAviFileSize			 = 0;
	lSampWritten			 = 0;
	lBytesWritten			 = 0;
	lAviBytesWrittenMax		 = 0;
	nAviAudioFileSize		 = 0;
	lAviAudioBytesWritten	 = 0;
	lAviAudioBytesWrittenMax = 0;

	nAviFileSizeMax = (unsigned __int64)AviStatus->avi_filesize * 1000000;
	if (AviStatus->avi_filesize)	bAviFile_Divides = TRUE;
	else							bAviFile_Divides = FALSE;

	strcpy(aviFilename, filename);

	if (Avi_StatusAvi.avi_audio_record_type)
	{
		extern int mame_mixer_wave_cnvnmb;
		extern struct WAV_WAVEFORMAT		mame_mixer_dstwfm, mame_mixer_srcwfm;
		extern struct WAV_SAMPLES_RESIZE	mame_mixer_wsr;

		mame_mixer_srcwfm.channel       = AviStatus->audio_channel;
		mame_mixer_srcwfm.samplespersec = AviStatus->audio_samples_per_sec;
		mame_mixer_srcwfm.bitrate       = AviStatus->audio_bitrate;
		
		mame_mixer_dstwfm.channel       = AviStatus->avi_audio_channel;
		mame_mixer_dstwfm.samplespersec = AviStatus->avi_audio_samples_per_sec;
		mame_mixer_dstwfm.bitrate       = AviStatus->avi_audio_bitrate;

		mame_mixer_wave_cnvnmb = wav_convert_select(&mame_mixer_dstwfm, &mame_mixer_srcwfm, 
													&mame_mixer_wsr, NULL ); //&mame_mixer_wsre );
	}

	if (Avi_StatusAvi.avi_audio_record_type == 1)
		strcpy(wavFilename, (const char *)Avi_StatusAvi.wav_filename);
	
	if (bAviFile_Divides == TRUE)
	{
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
		_splitpath(filename, drive, dir, fname, ext);
		_makepath(aviBaseFilename, drive, dir, fname, NULL);
		sprintf(aviFilename, "%s.%s", aviBaseFilename, "avi");
		
		if (Avi_StatusAvi.avi_audio_record_type == 1)
		{
			_splitpath(wavFilename, drive, dir, fname, ext);
			_makepath(wavBaseFilename, drive, dir, fname, NULL);
			sprintf(wavFilename, "%s.%s", wavBaseFilename, "wav");
		}
	}

	delete_file(aviFilename);
    if (AVI_Init(hwnd, aviFilename, nAviWidth, nAviHeight, nAviDepthAvi, AviFps, &rectAviSrc) == FALSE)
	{
		AVI_Close(aviFilename);
		strcpy(aviFilename, "");
		return FALSE;
	}

	//#ifdef AVI_AUDIO
	if (Avi_StatusAvi.avi_audio_record_type == 2)
		if (AVI_AudioStream_Start())
		{
	        AVI_Message_Error();
			AVI_Close(aviFilename);
			strcpy(aviFilename, "");
			return FALSE;
	}
	//#endif

	nAviFrameSkip = AviStatus->frame_skip;
	nAviFrameCount = 0;
	nAviFrameCountStart = (unsigned int)(((AviStatus->hour*60 + AviStatus->minute)*60 + AviStatus->second) * AviStatus->def_fps);
	nAviAudioRecord = AviStatus->avi_audio_record_type;

    bAviCapture = 1;
    

	if (nAviDepthAvi ==  8 && nAviDepthSrc == 16) 
	{
		AVI_Create_8bit_Bitmap();
	}
	if (nAviDepthAvi == 24 && nAviDepthSrc == 16) {
		AVI_Create_24bit_Bitmap();
	}
	if (nAviDepthAvi == 16 && nAviDepthSrc == 16 && nAviFrameResize) ;//AVI_Create_16bit_Bitmap();

    return TRUE;
}


/* End capture, close file */
void AviEndCapture(void)
{
	int i;
    if (!bAviCapture)
	{
        return;
	}

	nAviBitmapSize = 0;
	for(i=0; i<AVI_MAX_FRAME_CMP; i++)
	{
		if (pAviBitmapTemp[i] != NULL)
		{
			free(pAviBitmapTemp[i]);
			pAviBitmapTemp[i] = NULL;
		}
	}
	nAviTempSize = 0;

	if (pAviBitmap_bitConv != NULL) free(pAviBitmap_bitConv);

	//#ifdef AVI_AUDIO
	if (pAviAudioBuf != NULL)	free(pAviAudioBuf);
	nAviAudioBufSize = 0;
	bAviAudioRecord = FALSE;
	//#endif

    AVI_Close(aviFilename);
    bAviCapture = 0;
    strcpy(aviFilename, "");
}

void AviFrameConv_StreamWrite(char *bitmap)
{
	// HRESULT hr;
	LPBITMAPINFOHEADER lpbit;
	int frames	= nAviFrames;


	if (nAviDepthAvi == 8 && nAviDepthSrc == 16)
	{
		AVI_Convert_16to8_Bitmap(bitmap);
		lpbit = (LPBITMAPINFOHEADER)pAviBitmap_bitConv;
	}
	else if (nAviDepthAvi == 24 && nAviDepthSrc == 16)
	{
		if (bAvi_TVInterlace == TRUE)
		{
			const int field = (Avi_StatusAvi.interlace_odd_number_field == TRUE) ? nAvi_TVInterlace_Count^1:nAvi_TVInterlace_Count;
			
			if (Avi_StatusAvi.avi_smooth_resize_x == TRUE)
			{
				if (Avi_StatusAvi.avi_smooth_resize_y == TRUE)
					AVI_Convert_16to24_TVInterlace_sxy_Bitmap(bitmap, field);
				else
					AVI_Convert_16to24_TVInterlace_s_Bitmap(bitmap, field);
			}
			else if (Avi_StatusAvi.avi_smooth_resize_y == TRUE)
				AVI_Convert_16to24_TVInterlace_sy_Bitmap(bitmap, field);
			else
				AVI_Convert_16to24_TVInterlace_Bitmap(bitmap, field);


			nAvi_TVInterlace_Count = (nAvi_TVInterlace_Count+1) & 0x1;
			if (nAvi_TVInterlace_Count!=0) return;

		} else
		{
			AVI_Convert_16to24_Bitmap(bitmap);
		}
		lpbit = (LPBITMAPINFOHEADER)pAviBitmap_bitConv;
	}
	else {
		lpbit = (LPBITMAPINFOHEADER)bitmap;
	}

	(void)AVIStreamWrite( psCompressed,          /* stream pointer */
                         frames,				/* time of this frame */
                         1,                     /* number to write */
                         (LPBYTE) lpbit +       /* pointer to data */
                         lpbit->biSize +
                         lpbit->biClrUsed * sizeof(RGBQUAD),
                         lpbit->biSizeImage,    /* size of this frame */
                         AVIIF_KEYFRAME,        /* flags.... */
                         &lSampWritten,
                         &lBytesWritten);

	if (lBytesWritten > lAviBytesWrittenMax) lAviBytesWrittenMax = lBytesWritten;
	nAviFileSize += (unsigned __int64)lBytesWritten;
	nAviFrames++;

	return;
}

LPBITMAPINFOHEADER AviFrameBlend(void)
{
	LPBITMAPINFOHEADER lpbit = (LPBITMAPINFOHEADER)pAviBitmap_bitConv;
	HRESULT hr;

	if (nAviFrameCmp) nAviTempCount++;
	AviTempN += 0x10000;
	if ((AviTempN >= AviTempE) && !bAviError)
	{
		int i,j;


		if (!nAviFrames)
		{
			if ((nAviDepthAvi == 8 || nAviDepthAvi == 24) && nAviDepthSrc == 16)
			{
				lpbit = (LPBITMAPINFOHEADER)pAviBitmap_bitConv;
			}
			else 
			{
				lpbit = (LPBITMAPINFOHEADER)(pAviBitmapTemp[0]);
			}

			hr = AVIStreamSetFormat(psCompressed, 0,
									lpbit,              /* stream format */
									lpbit->biSize +     /* format size */
	                                lpbit->biClrUsed * sizeof(RGBQUAD));

			if (hr != AVIERR_OK)
			{
	            bAviError = TRUE;
			}
		}

		j = ((AviTempN + 0xffff) >> 16) + nAviCountSub;
		nAviTempCount = 0;



		switch (nAviFrameCmp)
		{
		case 1:
		for(i=1; i<j; i++)
		{
			int x,y,line;
			unsigned int r,g,b,alpha;
			unsigned int rd,gd,bd;
			short col;
			line = (rectAviSrc.m_Width * (16/8)+3)&~3;

			alpha = 32768;
			{
				int s,e;
				s = (AviTempS & 0xffff);
				e = (AviTempE & 0xffff);
				if (e==0) e=0x10000;

				if(i==1) 
				{
					alpha = 65536-(32768 - (s >> 1));
				}
				else 
				{
					if(i==(j-1)) alpha = (e >> 1);
				}
			}

			for(y=0; y<rectAviSrc.m_Height; y++)
			{
				unsigned short* dst = (unsigned short*)(pAviBitmapTemp[0] + sizeof(BITMAPINFOHEADER) + y * line);
				const unsigned short* src = (unsigned short*)(pAviBitmapTemp[i] + sizeof(BITMAPINFOHEADER) + y * line);
				for(x=0; x<rectAviSrc.m_Width; x++)
				{
					col = src[x];
					b = (col >>  0) & 0x1f;
					g = (col >>  5) & 0x1f;
					r = (col >> 10) & 0x1f;
					col = dst[x];
					bd = (col >>  0) & 0x1f;
					gd = (col >>  5) & 0x1f;
					rd = (col >> 10) & 0x1f;

					r = (r * alpha + rd * (65536-alpha)) >> 16;
					g = (g * alpha + gd * (65536-alpha)) >> 16;
					b = (b * alpha + bd * (65536-alpha)) >> 16;

					dst[x] =	(r << 10) |
								(g << 5) |
								(b << 0);
				}
			}
		}
		break;
		case 2:
		{
			int x,y,line;
			unsigned int r,g,b;
			unsigned int rs,gs,bs;
			short col;
			unsigned int alp[AVI_MAX_FRAME_CMP];
			line = (rectAviSrc.m_Width * (16/8)+3)&~3;

			for(i=1; i<j; i++)
			{
				int s,e;
				alp[i] = 32768;
				
				s = (AviTempS & 0xffff);
				e = (AviTempE & 0xffff);
				if (e==0) e=0x10000;

				if(i==1) 
				{
					alp[i] = 65536-(32768 - (s >> 1));
				}
				else 
				{
					if(i==(j-1)) alp[i] = (e >> 1);
				}
			}

			for(y=0; y<rectAviSrc.m_Height; y++)
			{
				const int bmpline = sizeof(BITMAPINFOHEADER) + y * line;
				unsigned short* dst = (unsigned short*)(pAviBitmapTemp[0] + bmpline);
				for(x=0; x<rectAviSrc.m_Width; x++)
				{
					col = dst[x];
					b = (col >>  0) & 0x1f;
					g = (col >>  5) & 0x1f;
					r = (col >> 10) & 0x1f;

					b |= (b<<5) | (b<<10); 
					g |= (g<<5) | (g<<10); 
					r |= (r<<5) | (r<<10);

					for(i=1; i<j; i++)
					{
					const unsigned short* src = (unsigned short*)(pAviBitmapTemp[i] + bmpline);
					const unsigned int alpha = alp[i];
					col = src[x];
					bs = (col >>  0) & 0x1f;
					gs = (col >>  5) & 0x1f;
					rs = (col >> 10) & 0x1f;

					bs |= (bs<<5) | (bs<<10); 
					gs |= (gs<<5) | (gs<<10); 
					rs |= (rs<<5) | (rs<<10);

					r = (rs * alpha + r * (65536-alpha)) >> 16;
					g = (gs * alpha + g * (65536-alpha)) >> 16;
					b = (bs * alpha + b * (65536-alpha)) >> 16;
					}

					if(r>32767) r=32767;
					if(g>32767) g=32767;
					if(b>32767) b=32767;
					dst[x] =	( r			& (0x1f<<10))		|
								((g >> 5)	& (0x1f<<5))	|
								((b >> 10)	&  0x1f);

				}
			}
		}
		break;
		case 3:
		{
			int x,y,line;
			unsigned int r,g,b;
			unsigned int rs,gs,bs;
			short col;
			unsigned int alp[AVI_MAX_FRAME_CMP];
			int s,e;
			unsigned int t;
			line = (rectAviSrc.m_Width * (16/8)+3)&~3;
			s = (AviTempS & 0xffff);
			e = (AviTempE & 0xffff);

			t=j << 16;

			if (e==0) e=0x10000;
			t = t - s;
			t = t - (65536-e);


			for(i=0; i<j; i++)
			{
				alp[i] = 65536;
				if(i==0) 
				{
					alp[i] = 65536 - s;
				}
				else 
				{
					if(i==(j-1)) alp[i] = e;
				}

				alp[i] = (unsigned int)(((unsigned __int64)alp[i] << 16) / t);
			}

			for(y=0; y<rectAviSrc.m_Height; y++)
			{
				const int bmpline = sizeof(BITMAPINFOHEADER) + y * line;
				unsigned short* dst = (unsigned short*)(pAviBitmapTemp[0] + bmpline);
				for(x=0; x<rectAviSrc.m_Width; x++)
				{
					unsigned int alpha = alp[0];
					col = dst[x];
					b = (col >>  0) & 0x1f;
					g = (col >>  5) & 0x1f;
					r = (col >> 10) & 0x1f;

					b |= (b<<5) | (b<<10); 
					g |= (g<<5) | (g<<10); 
					r |= (r<<5) | (r<<10);

					r = r * alpha;
					g = g * alpha;
					b = b * alpha;

					for(i=1; i<j; i++)
					{
					const unsigned short* src = (unsigned short*)(pAviBitmapTemp[i] + bmpline);
					alpha = alp[i];
					col = src[x];
					bs = (col >>  0) & 0x1f;
					gs = (col >>  5) & 0x1f;
					rs = (col >> 10) & 0x1f;

					bs |= (bs<<5) | (bs<<10);
					gs |= (gs<<5) | (gs<<10);
					rs |= (rs<<5) | (rs<<10);

					r += (rs * alpha);
					g += (gs * alpha);
					b += (bs * alpha);
					}

					if(r>0x7fffffff) r=0x7fffffff;
					if(g>0x7fffffff) g=0x7fffffff;
					if(b>0x7fffffff) b=0x7fffffff;
					dst[x] =	((r	>> (0+16))	& (0x1f<<10))		|
								((g >> (5+16))	& (0x1f<<5))	|
								((b >> (10+16))	&  0x1f);
				}
			}
		}
		break;
		default:;
			j=0;
		}
		


		AviFrameConv_StreamWrite(pAviBitmapTemp[0]);

		if((AviTempE & 0xffff) && (j>1))
		{
			char *lp = pAviBitmapTemp[0];
			pAviBitmapTemp[0] = pAviBitmapTemp[j-1];
			pAviBitmapTemp[j-1] = lp;
			nAviTempCount++;
			nAviCountSub = 1;
		} else
		{
			nAviCountSub = 0;
		}
		AviTempS = AviTempE & 0xffff;
		AviTempE = AviTempE + AviTempNext - AviTempN;
		AviTempN = AviTempN & 0xffff;
	}

	return lpbit;
}

LPBITMAPINFOHEADER AviFrameSmooth(void)
{
	HRESULT hr;
	LPBITMAPINFOHEADER lpbit = (LPBITMAPINFOHEADER)pAviBitmap_bitConv;

	if (nAviFrameCmp) nAviTempCount++;

	if (!bAviError)
	{
		int j;

		if (AviTempE)
		{
		for(j=AviTempS; j<0x10000; j+=AviTempNext)
		{

		switch (nAviFrameCmp)
		{
		case 1:
		{
			int x,y,line;
			unsigned int r,g,b;
			unsigned int rs,gs,bs;
			short col;
			const unsigned int alpha = j & 0xffff;

			line = (rectAviSrc.m_Width * (16/8)+3)&~3;
			for(y=0; y<rectAviSrc.m_Height; y++)
			{
				const int bmpline = sizeof(BITMAPINFOHEADER) + y * line;
				unsigned short* dst = (unsigned short*)(pAviBitmapTemp[2] + bmpline);
				const unsigned short* src1 = (unsigned short*)(pAviBitmapTemp[1] + bmpline);
				const unsigned short* src2 = (unsigned short*)(pAviBitmapTemp[0] + bmpline);
				for(x=0; x<rectAviSrc.m_Width; x++)
				{
					col = src1[x];
					b = (col >>  0) & 0x1f;
					g = (col >>  5) & 0x1f;
					r = (col >> 10) & 0x1f;

					b |= (b<<5) | (b<<10); 
					g |= (g<<5) | (g<<10); 
					r |= (r<<5) | (r<<10);

					r = r * alpha;
					g = g * alpha;
					b = b * alpha;

					col = src2[x];
					bs = (col >>  0) & 0x1f;
					gs = (col >>  5) & 0x1f;
					rs = (col >> 10) & 0x1f;

					bs |= (bs<<5) | (bs<<10);
					gs |= (gs<<5) | (gs<<10);
					rs |= (rs<<5) | (rs<<10);

					r += (rs * (0x10000-alpha));
					g += (gs * (0x10000-alpha));
					b += (bs * (0x10000-alpha));

					if(r>0x7fffffff) r=0x7fffffff;
					if(g>0x7fffffff) g=0x7fffffff;
					if(b>0x7fffffff) b=0x7fffffff;
					dst[x] =	((r	>> (0+16))	& (0x1f<<10))	|
								((g >> (5+16))	& (0x1f<<5))	|
								((b >> (10+16))	&  0x1f);
				}
			}
		}
		break;

		default:;
		}

		if (!nAviFrames)
		{
			if ((nAviDepthAvi == 8 || nAviDepthAvi == 24) && nAviDepthSrc == 16) 
			{
				lpbit = (LPBITMAPINFOHEADER)pAviBitmap_bitConv;
			}
			else {
				lpbit = (LPBITMAPINFOHEADER)(pAviBitmapTemp[0]);
			}

			hr = AVIStreamSetFormat(psCompressed, 0,
									lpbit,              /* stream format */
									lpbit->biSize +     /* format size */
	                                lpbit->biClrUsed * sizeof(RGBQUAD));

			if (hr != AVIERR_OK)
			{
	            bAviError = TRUE;
			}
		}


		AviFrameConv_StreamWrite(pAviBitmapTemp[nAviTempCount]);


		AviTempN += AviTempNext;

		}
		

		AviTempN -= 0x10000;
		AviTempS = AviTempN;

		{
			char *lp = pAviBitmapTemp[0];
			pAviBitmapTemp[0] = pAviBitmapTemp[1];
			pAviBitmapTemp[1] = lp;
			nAviTempCount=1;
		}
		}


		AviTempE = 1;
	}

	return lpbit;
}

/* Add a frame to an open AVI */
extern int			win_visible_width;
extern int			win_visible_height;
void AviAddBitmap(running_machine *machine, bitmap_t *tBitmap, UINT32* pPalEntries)
{
	extern unsigned __int64 mame_mixer_wave_FileSize;
    LPBITMAPINFOHEADER lpbit;
    char* bitmap;
	
	//static int aviverb = 0;
	//if( aviverb == 0 ) {
	//	logmsg( "AviAddBitmap()----------------------\n" );
	//	logmsg( "width, height            : %d x %d\n", tBitmap->width, tBitmap->height );
	//	logmsg( "win_visible_width, height: %d x %d\n", win_visible_width, win_visible_height );
	//	logmsg( "AviAddBitmap()----------------------\n" );
	//	aviverb = 1;
	//}

    if (!bAviCapture)
        return;

    bitmap = AVI_Convert_Bitmap(machine, tBitmap, pPalEntries);

	if (AviTempNext < 0x10000)	
		lpbit = AviFrameSmooth();
	else
		lpbit = AviFrameBlend();


	if (bAviFile_Divides == TRUE)
	{
		unsigned __int64 audio_size = 0;
		if (Avi_StatusAvi.avi_audio_record_type == 1) audio_size = mame_mixer_wave_FileSize;
		if (Avi_StatusAvi.avi_audio_record_type == 2) audio_size = nAviAudioFileSize;

		if (nAviFileSize + audio_size > nAviFileSizeMax)
		{
			lSampWritten = 0;
			lBytesWritten = 0;
			lAviAudioBytesWritten = 0;

			if (Avi_StatusAvi.avi_audio_record_type)
			{
				mame_mixer_wave_FileSize = 0;
				nAviAudioFileSize = 0;
			}

			{
				extern int avi_nextfile(running_machine *machine);
				extern struct WAV_WAVEFORMAT mame_mixer_dstwfm;
				int br = TRUE;

				AVI_CloseFile(aviFilename);

				if (nAviFile_DividesCount == 0)
				{
					//int nResult;
					TCHAR buf[_MAX_PATH];

					_stprintf(buf, TEXT("%s_%03d.%s"), LPWSTR(aviBaseFilename), 0, TEXT("avi"));
					DeleteFile(buf);
					(void)MoveFile(LPWSTR(aviFilename), buf);
				}
				nAviFile_DividesCount++;

				sprintf(aviFilename, "%s_%03d.%s", aviBaseFilename, nAviFile_DividesCount, "avi");
				if (Avi_StatusAvi.avi_audio_record_type == 1)
				{
					wav_stop_log_wave();

					if (nAviFile_DividesCount-1 == 0)
					{
						TCHAR buf[_MAX_PATH];
						// int nResult;
						
						_stprintf(buf, TEXT("%s_%03d.%s"), LPWSTR(wavBaseFilename), 0, TEXT("wav"));
						DeleteFile(buf);
						(void)MoveFile(LPWSTR(wavFilename), buf);
					}
					sprintf(wavFilename, "%s_%03d.%s", wavBaseFilename, nAviFile_DividesCount, "wav");
				}

				if (Avi_StatusAvi.avi_savefile_pause == TRUE)
					br = avi_nextfile(machine);

				if (AVI_ReInit(aviFilename) == FALSE) {bAviError = TRUE; return;}

				if (Avi_StatusAvi.avi_audio_record_type == 1)
				{
					if (wav_start_log_wave(wavFilename, &mame_mixer_dstwfm) == 0)
					{;

					} 
					else
					{
						Avi_StatusAvi.avi_audio_record_type = 0;
						ErrorMessageBox("Unable to open file '%s' for wave.", wavFilename );
					}


				}

				//#ifdef AVI_AUDIO
				if (Avi_StatusAvi.avi_audio_record_type == 2)
					if (AVI_AudioStream_Start())
					{
						bAviError = TRUE;
						return;
				}
				//#endif

				if (br == FALSE)
				{
					extern int bAviRun;
					bAviRun = 0;
					if (Avi_StatusAvi.avi_audio_record_type)
					{
						extern int mame_mixer_wave_loging;
						mame_mixer_wave_loging = 0;
					}
					return;
				}
			}
		}
	}

    //free(bitmap);
}

/***************************************************************************
    External variables
 ***************************************************************************/
static void AVI_SetBitmapinfoHeader(int width, int height, int depth)
{
	BITMAPINFOHEADER    bmiHeader;
    DWORD dwSize;
    DWORD wColSize;
    UINT wLineLen;
	int i;


    wLineLen = (width * depth + 31) / 32 * 4;
    wColSize = sizeof(RGBQUAD) * ((depth <= 8) ? BMP_PALSIZE : 0);
    dwSize = sizeof(BITMAPINFOHEADER) + wColSize +
                (DWORD)(UINT)wLineLen * (DWORD)(UINT)height;

    /* This is the BITMAPINFOHEADER structure */
    bmiHeader.biSize            = sizeof(BITMAPINFOHEADER);
    bmiHeader.biWidth           = width;
    bmiHeader.biHeight          = height;
    bmiHeader.biPlanes          = 1;
    bmiHeader.biBitCount        = (depth <= 8) ? 8 : 16;
    bmiHeader.biCompression     = BI_RGB;
    bmiHeader.biSizeImage       = dwSize - sizeof(BITMAPINFOHEADER) - wColSize;
    bmiHeader.biXPelsPerMeter   = 0;
    bmiHeader.biYPelsPerMeter   = 0;
    bmiHeader.biClrUsed         = (depth == 8) ? BMP_PALSIZE : 0;
    bmiHeader.biClrImportant    = 0;

    /* Write the BITMAPINFOHEADER */
	for(i=0; i<nAviTempSize; i++)
		memcpy(pAviBitmapTemp[i], (void*)&bmiHeader, sizeof(BITMAPINFOHEADER));
}

static AVICOMPRESSOPTIONS AviCompressOpts;

static BOOL AVI_Init(HWND hwnd, char* filename, int width, int height, int depth, double fps, tRect *rect)
{
    /* Must pass the following parameters */
    /* width  = drivers[index]->drv->screen_width */
    /* height = drivers[index]->drv->screen_height */
    /* depth  = bits per pixel */

    HRESULT hr;
    AVISTREAMINFO strhdr;
    DWORD dwSize;
    DWORD wColSize;
    DWORD biSizeImage;
    UINT wLineLen;
    AVICOMPRESSOPTIONS* aopts[1];

    aopts[0] = &AviCompressOpts;

    AVIFileInit();

    hr = AVIFileOpen(&pfile,                      /* returned file pointer */
                     LPWSTR(filename),          /* file name */
                     OF_WRITE | OF_CREATE,        /* mode to open file with */
                     NULL);                       /* use handler determined */
                                                  /* from file extension.... */
    if (hr != AVIERR_OK)
    {
        AVI_Message_Error();
        return FALSE;
    }

	nAviWidth	= width;
	nAviHeight	= height;
    wLineLen = ((DWORD)nAviWidth * depth + 31) / 32 * 4;

    wColSize = sizeof(RGBQUAD) * ((depth <= 8) ? BMP_PALSIZE : 0);

    dwSize = sizeof(BITMAPINFOHEADER) + wColSize +
                (DWORD)(UINT)wLineLen * (DWORD)(UINT)nAviHeight;

    biSizeImage = dwSize - sizeof(BITMAPINFOHEADER) - wColSize;

    /*
       Fill in the header for the video stream....
       The video stream will run in 60ths of a second....To be changed
    */

    _fmemset(&strhdr, 0, sizeof(strhdr));
    strhdr.fccType          = streamtypeVIDEO;
    strhdr.fccHandler       = 0;
	strhdr.dwFlags			= AVIF_ISINTERLEAVED;
	if ((Avi_setfpsleft % 1000000) == 0)
	{
		strhdr.dwScale      = 1;
		strhdr.dwRate       = Avi_setfps;		// fps
	} else
	{
		strhdr.dwScale      = 1000000;
		strhdr.dwRate       = Avi_setfpsleft;	// fps
	}
	strhdr.dwInitialFrames	= 0;

    strhdr.dwSuggestedBufferSize  = biSizeImage;

    SetRect(&strhdr.rcFrame, 0, 0,          /* rectangle for stream */
            (int) nAviWidth,
            (int) nAviHeight);

    /* And create the stream */
    hr = AVIFileCreateStream(pfile,         /* file pointer */
                             &ps,           /* returned stream pointer */
                             &strhdr);      /* stream header */
    if (hr != AVIERR_OK)
    {
        AVI_Message_Error();
        return FALSE;
    }

    _fmemset(&AviCompressOpts, 0, sizeof(AviCompressOpts));
    if (!AVISaveOptions(hwnd, 0, 1, &ps, aopts))	/* CodecSelect dialog */
    {
        AVI_Message_Error();
        return FALSE;
    }

	/*
	logmsg( "Selected Codec Info(CompressInfo)---------\n" );
	logmsg( "fccType          : %x(%x)\n", AviCompressOpts.fccType, AviCompressOpts.fccHandler );
	logmsg( "dwKeyFrameEvery  : %d\n", AviCompressOpts.dwKeyFrameEvery );
	logmsg( "dwQuality        : %d\n", AviCompressOpts.dwQuality );
	logmsg( "dwBytesPerSecond : %d\n", AviCompressOpts.dwBytesPerSecond );
	logmsg( "dwFlags          : %s %s %s %s\n",
		(AviCompressOpts.dwFlags & AVICOMPRESSF_DATARATE   ) ? "AVICOMPRESSF_DATARATE " : "",
		(AviCompressOpts.dwFlags & AVICOMPRESSF_INTERLEAVE ) ? "AVICOMPRESSF_INTERLEAVE " : "",
		(AviCompressOpts.dwFlags & AVICOMPRESSF_KEYFRAMES  ) ? "AVICOMPRESSF_KEYFRAMES " : "",
		(AviCompressOpts.dwFlags & AVICOMPRESSF_VALID      ) ? "AVICOMPRESSF_VALID " : "" );
	logmsg( "dwInterleaveEvery: %d (Used only if the AVICOMPRESSF_INTERLEAVE flag is set)\n", AviCompressOpts.dwInterleaveEvery );
	logmsg( "-----------------------\n\n" );
	*/

    hr = AVIMakeCompressedStream(&psCompressed, ps, &AviCompressOpts, NULL);
    if (hr != AVIERR_OK)
    {
        AVI_Message_Error();
        return FALSE;
    }

    return TRUE;
}

static BOOL AVI_ReInit(char* filename)
{
    /* Must pass the following parameters */
    /* width  = drivers[index]->drv->screen_width */
    /* height = drivers[index]->drv->screen_height */
    /* depth  = bits per pixel */

    HRESULT hr;
    AVISTREAMINFO strhdr;
    DWORD dwSize;
    DWORD wColSize;
    DWORD biSizeImage;
    UINT wLineLen;
    AVICOMPRESSOPTIONS* aopts[1];
	const int depth = nAviDepthAvi;

    aopts[0] = &AviCompressOpts;

	nAviFileSize = 0;

	delete_file(filename);

    hr = AVIFileOpen(&pfile,                      /* returned file pointer */
                     LPWSTR(filename),          /* file name */
                     OF_WRITE | OF_CREATE,        /* mode to open file with */
                     NULL);                       /* use handler determined */
                                                  /* from file extension.... */
    if (hr != AVIERR_OK)
    {
        return FALSE;
    }

    wLineLen = ((DWORD)nAviWidth * depth + 31) / 32 * 4;
    wColSize = sizeof(RGBQUAD) * ((depth <= 8) ? BMP_PALSIZE : 0);

    dwSize = sizeof(BITMAPINFOHEADER) + wColSize +
                (DWORD)(UINT)wLineLen * (DWORD)(UINT)nAviHeight;

    biSizeImage = dwSize - sizeof(BITMAPINFOHEADER) - wColSize;

    /*
       Fill in the header for the video stream....
       The video stream will run in 60ths of a second....To be changed
    */

    _fmemset(&strhdr, 0, sizeof(strhdr));
    strhdr.fccType    = streamtypeVIDEO;
    strhdr.fccHandler = 0;
	if ((Avi_setfpsleft % 1000000) == 0)
	{
		strhdr.dwScale = 1;
		strhdr.dwRate  = Avi_setfps;
	} else
	{
		strhdr.dwScale = 1000000;
		strhdr.dwRate  = Avi_setfpsleft;
	}

    strhdr.dwSuggestedBufferSize  = biSizeImage;

    SetRect(&strhdr.rcFrame, 0, 0,          /* rectangle for stream */
            (int) nAviWidth,
            (int) nAviHeight);

    /* And create the stream */
    hr = AVIFileCreateStream(pfile,         /* file pointer */
                             &ps,           /* returned stream pointer */
                             &strhdr);      /* stream header */
    if (hr != AVIERR_OK)
    {
        return FALSE;
    }

    hr = AVIMakeCompressedStream(&psCompressed, ps, &AviCompressOpts, NULL);
    if (hr != AVIERR_OK)
    {
        return FALSE;
    }

    return TRUE;
}

static void AVI_CloseFile(char* filename)
{
    FILE* fp;

    if (ps)
        AVIStreamClose(ps);

    if (psCompressed)
        AVIStreamClose(psCompressed);

	//#ifdef AVI_AUDIO
	if (audio_ps)	AVIStreamClose(audio_ps);

	audio_ps		 = NULL;
	nAviAudioSamples = 0;
	//#endif

    if (pfile)
        AVIFileClose(pfile);

    pfile        = NULL;
    ps           = NULL;
    psCompressed = NULL;
    nAviFrames   = 0;
    bAviError    = FALSE;

	if ((fp = fopen(filename, "rb+")) != NULL)
	{
		fseek(fp, 0x70, SEEK_SET);
		fwrite(&AviCompressOpts.fccHandler, 1, 4, fp);
		fclose(fp);
	}
}
static void AVI_Close(char* filename)
{
    FILE* fp;

    if (ps)
        AVIStreamClose(ps);

    if (psCompressed)
        AVIStreamClose(psCompressed);

	//#ifdef AVI_AUDIO
    if (audio_ps)
        AVIStreamClose(audio_ps);
	audio_ps			= NULL;
	nAviAudioSamples	= 0;
	//#endif

    if (pfile)
        AVIFileClose(pfile);

    AVIFileExit();

    pfile        = NULL;
    ps           = NULL;
    psCompressed = NULL;
    nAviFrames   = 0;
    bAviError    = FALSE;

	if ((fp = fopen(filename, "rb+")) != NULL)
	{
		fseek(fp, 0x70, SEEK_SET);
		fwrite(&AviCompressOpts.fccHandler, 1, 4, fp);
		fclose(fp);
	}

	/* Directly edit the frame rate information */
	nAviTempSize = 0;
	nAviTempCount = 0;

}


static BOOL AVI_Check_Version(void)
{
    WORD wVer;

    /* first let's make sure we are running on 1.1 */
    wVer = HIWORD(VideoForWindowsVersion());
    if (wVer < 0x010a)
    {
        return FALSE;
    }
    return TRUE;
}

static void AVI_Message_Error(void)
{
    MessageBox(NULL, TEXT("AVI File Error!"), TEXT("Error"), MB_OK);

}

// 32bit triplets (888) -> 16bit RGB triplets (555) by DarkCoder
void TransformBitmap32to16(running_machine *machine, bitmap_t &tBitmap, unsigned short *dst, UINT32 *pPalEntries)
{
	UINT32 *ptr;
	UINT16 *prev_dst;
	int i, x, nLineSize, nTop, nLeft, nWidth, nHeight;
	unsigned char r, g, b;
	int depth = 16;

	nTop    = rectAviSrc.m_Top;
	nLeft   = rectAviSrc.m_Left;
	nWidth  = rectAviSrc.m_Width;
	nHeight = rectAviSrc.m_Height;

	nLineSize  = (((rectAviSrc.m_Width * depth) / 8) + 3) & ~3;
	nLineSize /= sizeof(unsigned short);

	if( nAviOrientation & ORIENTATION_SWAP_XY ) {

		if( (nAviSrcWidth != tBitmap.height()) || (nAviSrcHeight != tBitmap.width()) ) 
		{
			//logmsg( "Invalid size: nAviSrcWidth(%d) != height(%d) or nAviSrcHeight(%d) != width(%d).\n",
			//	nAviSrcWidth, tBitmap->height, nAviSrcHeight, tBitmap->width );

			return;
		}

		if( nAviFlipX ) {
			dst += ((nHeight - 1)  * nLineSize);
			dst += (nLineSize-1);
			for (i=0; i<nWidth; i++)
			{
				prev_dst = dst;
				// ptr = (UINT32 *)BITMAP_ADDR32(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT32>(i + nLeft, nTop);

				for (x = 0; x<nHeight; x++)
				{
					r = (ptr[x] >> 19) & 0x1f;
					g = (ptr[x] >> 11) & 0x1f;
					b = (ptr[x] >>  3) & 0x1f;
					*dst = (r << 10) | (g << 5) | (b);
					dst -= nLineSize;
				}
				dst = prev_dst; dst--;
			}
			//----
		}
		else if( nAviFlipY ) {
			for (i=0; i<nWidth; i++)
			{
				prev_dst = dst;
				// ptr = (UINT32 *)BITMAP_ADDR32(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT32>(i + nLeft, nTop);
				for (x = 0; x<nHeight; x++)
				{
					r = (ptr[x] >> 19) & 0x1f;
					g = (ptr[x] >> 11) & 0x1f;
					b = (ptr[x] >>  3) & 0x1f;
					*dst = (r << 10) | (g << 5) | (b);
					dst += nLineSize;
				}
				dst = &prev_dst[1];
			}
			//----
		}
		else {
			dst += ((nHeight - 1)  * nLineSize);
			for (i=0; i<nWidth; i++)
			{
				prev_dst = dst;
				// ptr = (UINT32 *)BITMAP_ADDR32(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT32>(i + nLeft, nTop);
				for (x = 0; x<nHeight; x++)
				{
					r = (ptr[x] >> 19) & 0x1f;
					g = (ptr[x] >> 11) & 0x1f;
					b = (ptr[x] >>  3) & 0x1f;
					*dst = (r << 10) | (g << 5) | (b);
					dst -= nLineSize;
				}
				dst = &prev_dst[1];
			}
			//----
		}
	}
	else {
		if( nAviFlipX && nAviFlipY ) {
			for (i=0; i<nHeight; i++)
			{
				// ptr = (UINT32 *)BITMAP_ADDR32(tBitmap, i + nTop, nLeft);
				ptr = &tBitmap.pixt<UINT32>(i + nLeft, nTop);
				for (x = nWidth-1; x >=0; x--)
				{
					r = (ptr[x] >> 19) & 0x1f;
					g = (ptr[x] >> 11) & 0x1f;
					b = (ptr[x] >>  3) & 0x1f;
					dst[x] = (r << 10) | (g << 5) | (b);
				}
				dst += nLineSize;
			}
			//----
		}
		else if( nAviFlipX ) {
			int x2;
			dst += ((nHeight - 1)  * nLineSize);
			for (i=0; i<nHeight; i++)
			{
				// ptr = (UINT32 *)BITMAP_ADDR32(tBitmap, i + nTop, nLeft);
				ptr = &tBitmap.pixt<UINT32>(i + nLeft, nTop);
				for (x = nWidth-1,x2=0; x >=0; x--,x2++)
				{
					r = (ptr[x] >> 19) & 0x1f;
					g = (ptr[x] >> 11) & 0x1f;
					b = (ptr[x] >>  3) & 0x1f;
					dst[x] = (r << 10) | (g << 5) | (b);
				}
				dst -= nLineSize;
			}
			//----
		}
		else if( nAviFlipY ) {
			for (i=0; i<nHeight; i++)
			{
				// ptr = (UINT32 *)BITMAP_ADDR32(tBitmap, i + nTop, nLeft);
				ptr = &tBitmap.pixt<UINT32>(i + nLeft, nTop);
				for (x = 0; x < nWidth; x++)
				{
					r = (ptr[x] >> 19) & 0x1f;
					g = (ptr[x] >> 11) & 0x1f;
					b = (ptr[x] >>  3) & 0x1f;
					dst[x] = (r << 10) | (g << 5) | (b);
				}
				dst += nLineSize;
			}
			//----
		}
		else {
			dst += ((nHeight - 1)  * nLineSize);
			for (i=0; i<nHeight; i++)
			{
				// ptr = (UINT32 *)BITMAP_ADDR32(tBitmap, i + nTop, nLeft);
				ptr = &tBitmap.pixt<UINT32>(i + nLeft, nTop);
				for (x = 0; x < nWidth; x++)
				{
					r = (ptr[x] >> 19) & 0x1f;
					g = (ptr[x] >> 11) & 0x1f;
					b = (ptr[x] >>  3) & 0x1f;
					dst[x] = (r << 10) | (g << 5) | (b);
				}
				dst -= nLineSize;
			}
			//----
		}
	}
}

// 15bit RGB triplets (555) -> 16bit RGB triplets (555) by DarkCoder
void TransformBitmap15to16(running_machine *machine, bitmap_t &tBitmap, unsigned short *dst, UINT32 *pPalEntries)
{
	UINT16 *ptr, *prev_dst;
	int i, x, nLineSize, nTop, nLeft, nWidth, nHeight;
	int depth = 16;

	nTop    = rectAviSrc.m_Top;
	nLeft   = rectAviSrc.m_Left;
	nWidth  = rectAviSrc.m_Width;
	nHeight = rectAviSrc.m_Height;

	nLineSize  = (((rectAviSrc.m_Width * depth) / 8) + 3) & ~3;
	nLineSize /= sizeof(unsigned short);

	if( nAviOrientation & ORIENTATION_SWAP_XY ) {

		if( (nAviSrcWidth != tBitmap.height()) || (nAviSrcHeight != tBitmap.width()) ) 
		{
			//logmsg( "Invalid size: nAviSrcWidth(%d) != height(%d) or nAviSrcHeight(%d) != width(%d).\n",
			//	nAviSrcWidth, tBitmap->height, nAviSrcHeight, tBitmap->width );

			return;
		}

		if( nAviFlipX ) {
			dst += ((nHeight - 1)  * nLineSize);
			dst += (nLineSize-1);
			for (i=0; i<nWidth; i++)
			{
				prev_dst = dst;
				// ptr = (UINT16 *)BITMAP_ADDR16(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT16>(i + nLeft, nTop);
				for (x = 0; x<nHeight; x++)
				{
					*dst = (*ptr++);
					dst -= nLineSize;
				}
				dst = prev_dst; dst--;
			}
			//----
		}
		else if( nAviFlipY ) {
			for (i=0; i<nWidth; i++)
			{
				prev_dst = dst;
				// ptr = (UINT16 *)BITMAP_ADDR16(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT16>(i + nLeft, nTop);
				for (x = 0; x<nHeight; x++)
				{
					*dst = (*ptr++);
					dst += nLineSize;
				}
				dst = &prev_dst[1];
			}
			//----
		}
		else {
			dst += ((nHeight - 1)  * nLineSize);
			for (i=0; i<nWidth; i++)
			{
				prev_dst = dst;
				// ptr = (UINT16 *)BITMAP_ADDR16(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT16>(i + nLeft, nTop);
				for (x = 0; x<nHeight; x++)
				{
					*dst = (*ptr++);
					dst -= nLineSize;
				}
				dst = &prev_dst[1];
			}
			//----
		}
	}
	else {
		if( nAviFlipX && nAviFlipY ) {
			for (i=0; i<nHeight; i++)
			{
				// ptr = (UINT16 *)BITMAP_ADDR16(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT16>(i + nLeft, nTop);
				for (x = nWidth-1; x >=0; x--)
				{
					dst[x] = (*ptr++);
				}
				dst += nLineSize;
			}
			//----
		}
		else if( nAviFlipX ) {
			dst += ((nHeight - 1)  * nLineSize);
			for (i=0; i<nHeight; i++)
			{
				// ptr = (UINT16 *)BITMAP_ADDR16(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT16>(i + nLeft, nTop);
				for (x = nWidth-1; x >=0; x--)
				{
					dst[x] = (*ptr++);
				}
				dst -= nLineSize;
			}
			//----
		}
		else if( nAviFlipY ) {
			for (i=0; i<nHeight; i++)
			{
				// ptr = (UINT16 *)BITMAP_ADDR16(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT16>(i + nLeft, nTop);
				for (x = 0; x < nWidth; x++)
				{
					dst[x] = (*ptr++);
				}
				dst += nLineSize;
			}
			//----
		}
		else {
			dst += ((nHeight - 1)  * nLineSize);
			for (i=0; i<nHeight; i++)
			{
				// ptr = (UINT16 *)BITMAP_ADDR16(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT16>(i + nLeft, nTop);
				for (x = 0; x < nWidth; x++)
				{
					dst[x] = (*ptr++);
				}
				dst -= nLineSize;
			}
			//----
		}
	}
}

// 16bit indexed -> 16bit RGB triplets (555) by DarkCoder
void TransformBitmap16to16(running_machine *machine, bitmap_t &tBitmap, unsigned short *dst, UINT32 *pPalEntries)
{
	UINT16 *ptr, *prev_dst;
	int i, x, nLineSize, nTop, nLeft, nWidth, nHeight;
	//UINT32		  palColor;
	unsigned char r, g, b;
	int depth = 16;
	rgb_t color;

	nTop    = rectAviSrc.m_Top;
	nLeft   = rectAviSrc.m_Left;
	nWidth  = rectAviSrc.m_Width;
	nHeight = rectAviSrc.m_Height;

	palette_device m_palette;

	nLineSize  = (((rectAviSrc.m_Width * depth) / 8) + 3) & ~3;
	nLineSize /= sizeof(unsigned short);

	if( nAviOrientation & ORIENTATION_SWAP_XY ) {

		if( (nAviSrcWidth != tBitmap.height()) || (nAviSrcHeight != tBitmap.width()) ) 
		{
			//logmsg( "Invalid size: nAviSrcWidth(%d) != height(%d) or nAviSrcHeight(%d) != width(%d).\n",
			//	nAviSrcWidth, tBitmap->height, nAviSrcHeight, tBitmap->width );

			return;
		}

		if( nAviFlipX ) {
			dst += ((nHeight - 1)  * nLineSize);
			dst += (nLineSize-1);
			for (i=0; i<nWidth; i++)
			{
				prev_dst = dst;
				// ptr = (UINT16 *)BITMAP_ADDR16(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT16>(i + nLeft, nTop);

				for (x = 0; x<nHeight; x++)
				{
					color = palette_get_color(machine, *ptr++);
					r = ((RGB_RED(color) >> 3) & 0x1f);
					g = ((RGB_GREEN(color) >> 3) & 0x1f);
					b = ((RGB_BLUE(color) >> 3) & 0x1f);
					*dst = (r << 10) | (g << 5) | (b);
					dst -= nLineSize;
				}
				dst = prev_dst; dst--;
			}
			//----
		}
		else if( nAviFlipY ) {
			for (i=0; i<nWidth; i++)
			{
				prev_dst = dst;
				// ptr = (UINT16 *)BITMAP_ADDR16(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT16>(i + nLeft, nTop);

				for (x = 0; x<nHeight; x++)
				{
					color = palette_get_color(machine, *ptr++);
					r = ((RGB_RED(color) >> 3) & 0x1f);
					g = ((RGB_GREEN(color) >> 3) & 0x1f);
					b = ((RGB_BLUE(color) >> 3) & 0x1f);
					*dst = (r << 10) | (g << 5) | (b);
					dst += nLineSize;
				}
				dst = &prev_dst[1];
			}
			//----
		}
		else {
			dst += ((nHeight - 1)  * nLineSize);
			for (i=0; i<nWidth; i++)
			{
				prev_dst = dst;
				// ptr = (UINT16 *)BITMAP_ADDR16(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT16>(i + nLeft, nTop);
				for (x = 0; x<nHeight; x++)
				{
					color = palette_get_color(machine, *ptr++);
					r = ((RGB_RED(color) >> 3) & 0x1f);
					g = ((RGB_GREEN(color) >> 3) & 0x1f);
					b = ((RGB_BLUE(color) >> 3) & 0x1f);
					*dst = (r << 10) | (g << 5) | (b);
					dst -= nLineSize;
				}
				dst = &prev_dst[1];
			}
			//----
		}
	}
	else {
		if( nAviFlipX && nAviFlipY ) {
			for (i=0; i<nHeight; i++)
			{
				// ptr = (UINT16 *)BITMAP_ADDR16(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT16>(i + nLeft, nTop);
				for (x = nWidth-1; x >=0; x--)
				{
					color = palette_get_color(machine, *ptr++);
					r = ((RGB_RED(color) >> 3) & 0x1f);
					g = ((RGB_GREEN(color) >> 3) & 0x1f);
					b = ((RGB_BLUE(color) >> 3) & 0x1f);
					dst[x] = (r << 10) | (g << 5) | (b);
				}
				dst += nLineSize;
			}
			//----
		}
		else if( nAviFlipX ) {
			dst += ((nHeight - 1)  * nLineSize);
			for (i=0; i<nHeight; i++)
			{
				// ptr = (UINT16 *)BITMAP_ADDR16(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT16>(i + nLeft, nTop);
				for (x = nWidth-1; x >=0; x--)
				{
					color = palette_get_color(machine, *ptr++);
					r = ((RGB_RED(color) >> 3) & 0x1f);
					g = ((RGB_GREEN(color) >> 3) & 0x1f);
					b = ((RGB_BLUE(color) >> 3) & 0x1f);
					dst[x] = (r << 10) | (g << 5) | (b);
				}
				dst -= nLineSize;
			}
			//----
		}
		else if( nAviFlipY ) {
			for (i=0; i<nHeight; i++)
			{
				// ptr = (UINT16 *)BITMAP_ADDR16(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT16>(i + nLeft, nTop);
				for (x = 0; x < nWidth; x++)
				{
					color = palette_get_color(machine, *ptr++);
					r = ((RGB_RED(color) >> 3) & 0x1f);
					g = ((RGB_GREEN(color) >> 3) & 0x1f);
					b = ((RGB_BLUE(color) >> 3) & 0x1f);
					dst[x] = (r << 10) | (g << 5) | (b);
				}
				dst += nLineSize;
			}
			//----
		}
		else {
			dst += ((nHeight - 1)  * nLineSize);
			for (i=0; i<nHeight; i++)
			{
				// ptr = (UINT16 *)BITMAP_ADDR16(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT16>(i + nLeft, nTop);
				for (x = 0; x < nWidth; x++)
				{
					color = palette_get_color(machine, *ptr++);
					r = ((RGB_RED(color) >> 3) & 0x1f);
					g = ((RGB_GREEN(color) >> 3) & 0x1f);
					b = ((RGB_BLUE(color) >> 3) & 0x1f);
					dst[x] = (r << 10) | (g << 5) | (b);
				}
				dst -= nLineSize;
			}
			//----
		}
	}
}

// 8bit indexed -> 16bit RGB triplets (555) by DarkCoder
void TransformBitmap8to16(running_machine *machine, bitmap_t &tBitmap, unsigned short *dst, UINT32 *pPalEntries)
{
	UINT8 *ptr;
	UINT16 *prev_dst;
	int i, x, nLineSize, nTop, nLeft, nWidth, nHeight;
	//UINT32		  palColor;
	unsigned char r, g, b;
	int depth = 16;
	rgb_t color;

	nTop    = rectAviSrc.m_Top;
	nLeft   = rectAviSrc.m_Left;
	nWidth  = rectAviSrc.m_Width;
	nHeight = rectAviSrc.m_Height;

	nLineSize = (((rectAviSrc.m_Width * depth) / 8) + 3) & ~3;
	nLineSize /= sizeof(unsigned short);

	if( nAviOrientation & ORIENTATION_SWAP_XY ) {

		if( (nAviSrcWidth != tBitmap.height()) || (nAviSrcHeight != tBitmap.width()) ) 
		{
			//logmsg( "Invalid size: nAviSrcWidth(%d) != height(%d) or nAviSrcHeight(%d) != width(%d).\n",
			//	nAviSrcWidth, tBitmap->height, nAviSrcHeight, tBitmap->width );

			return;
		}

		if( nAviFlipX ) {
			dst += ((nHeight - 1)  * nLineSize);
			dst += (nLineSize-1);
			for (i=0; i<nWidth; i++)
			{
				prev_dst = dst;
				// ptr = (UINT8 *)BITMAP_ADDR8(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT8>(i + nLeft, nTop);
				for (x = 0; x<nHeight; x++)
				{
					color = palette_get_color(machine, *ptr++);
					r = ((RGB_RED(color) >> 3) & 0x1f);
					g = ((RGB_GREEN(color) >> 3) & 0x1f);
					b = ((RGB_BLUE(color) >> 3) & 0x1f);
					*dst = (r << 10) | (g << 5) | (b);
					dst -= nLineSize;
				}
				dst = prev_dst; dst--;
			}
			//----
		}
		else if( nAviFlipY ) {
			for (i=0; i<nWidth; i++)
			{
				prev_dst = dst;
				// ptr = (UINT8 *)BITMAP_ADDR8(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT8>(i + nLeft, nTop);
				for (x = 0; x<nHeight; x++)
				{
					color = palette_get_color(machine, *ptr++);
					r = ((RGB_RED(color) >> 3) & 0x1f);
					g = ((RGB_GREEN(color) >> 3) & 0x1f);
					b = ((RGB_BLUE(color) >> 3) & 0x1f);
					*dst = (r << 10) | (g << 5) | (b);
					dst += nLineSize;
				}
				dst = &prev_dst[1];
			}
			//----
		}
		else {
			dst += ((nHeight - 1)  * nLineSize);
			for (i=0; i<nWidth; i++)
			{
				prev_dst = dst;
				// ptr = (UINT8 *)BITMAP_ADDR8(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT8>(i + nLeft, nTop);
				for (x = 0; x<nHeight; x++)
				{
					color = palette_get_color(machine, *ptr++);
					r = ((RGB_RED(color) >> 3) & 0x1f);
					g = ((RGB_GREEN(color) >> 3) & 0x1f);
					b = ((RGB_BLUE(color) >> 3) & 0x1f);
					*dst = (r << 10) | (g << 5) | (b);
					dst -= nLineSize;
				}
				dst = &prev_dst[1];
			}
			//----
		}
	}
	else {
		if( nAviFlipX && nAviFlipY ) {
			for (i=0; i<nHeight; i++)
			{
				// ptr = (UINT8 *)BITMAP_ADDR8(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT8>(i + nLeft, nTop);
				for (x = nWidth-1; x >=0; x--)
				{
					color = palette_get_color(machine, *ptr++);
					r = ((RGB_RED(color) >> 3) & 0x1f);
					g = ((RGB_GREEN(color) >> 3) & 0x1f);
					b = ((RGB_BLUE(color) >> 3) & 0x1f);
					dst[x] = (r << 10) | (g << 5) | (b);
				}
				dst += nLineSize;
			}
			//----
		}
		else if( nAviFlipX ) {
			dst += ((nHeight - 1)  * nLineSize);
			for (i=0; i<nHeight; i++)
			{
				// ptr = (UINT8 *)BITMAP_ADDR8(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT8>(i + nLeft, nTop);
				for (x = nWidth-1; x >=0; x--)
				{
					color = palette_get_color(machine, *ptr++);
					r = ((RGB_RED(color) >> 3) & 0x1f);
					g = ((RGB_GREEN(color) >> 3) & 0x1f);
					b = ((RGB_BLUE(color) >> 3) & 0x1f);
					dst[x] = (r << 10) | (g << 5) | (b);
				}
				dst -= nLineSize;
			}
			//----
		}
		else if( nAviFlipY ) {
			for (i=0; i<nHeight; i++)
			{
				// ptr = (UINT8 *)BITMAP_ADDR8(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT8>(i + nLeft, nTop);
				for (x = 0; x < nWidth; x++)
				{
					color = palette_get_color(machine, *ptr++);
					r = ((RGB_RED(color) >> 3) & 0x1f);
					g = ((RGB_GREEN(color) >> 3) & 0x1f);
					b = ((RGB_BLUE(color) >> 3) & 0x1f);
					dst[x] = (r << 10) | (g << 5) | (b);
				}
				dst += nLineSize;
			}
			//----
		}
		else {
			dst += ((nHeight - 1)  * nLineSize);
			for (i=0; i<nHeight; i++)
			{
				// ptr = (UINT8 *)BITMAP_ADDR8(tBitmap, i + nLeft, nTop);
				ptr = &tBitmap.pixt<UINT8>(i + nLeft, nTop);
				for (x = 0; x < nWidth; x++)
				{
					color = palette_get_color(machine, *ptr++);
					r = ((RGB_RED(color) >> 3) & 0x1f);
					g = ((RGB_GREEN(color) >> 3) & 0x1f);
					b = ((RGB_BLUE(color) >> 3) & 0x1f);
					dst[x] = (r << 10) | (g << 5) | (b);
				}
				dst -= nLineSize;
			}
			//----
		}
	}
}

static char* AVI_Convert_Bitmap(running_machine *machine, bitmap_t &tBitmap, UINT32 *pPalEntries)
{
    char*     bitmap;
    int       i;
    UINT      wLineLen;

	int size;
	int bmihSize;
	int depth;

	depth = 16; //nAviDepthSrc;
	wLineLen = (rectAviSrc.m_Width * depth + 31) / 32 * 4;

	size = 0;
	//if( depth <= 8 ) size = (BMP_PALSIZE * sizeof(RGBQUAD));
	size += (rectAviSrc.m_Height * wLineLen);
	
	if( size != nAviBitmapSize)
	{
		for(i=0; i<nAviTempSize; i++)
		{
			if(pAviBitmapTemp[i] != NULL) free(pAviBitmapTemp[i]);
			pAviBitmapTemp[i] = (char*)malloc(size + sizeof(BITMAPINFOHEADER));
			if(pAviBitmapTemp[i] == NULL)
			{
				bAviError = TRUE;
				return NULL;
			}
		}

		nAviBitmapSize = size;
		AVI_SetBitmapinfoHeader(rectAviSrc.m_Width, rectAviSrc.m_Height, depth);
	}

	bitmap = pAviBitmapTemp[nAviTempCount];
	bmihSize = sizeof(BITMAPINFOHEADER);

	{
		unsigned short *dst;

		dst = (unsigned short*)&bitmap[bmihSize];

		if(tBitmap.format() == BITMAP_FORMAT_INDEXED32 || tBitmap.format() == BITMAP_FORMAT_RGB32) {
			TransformBitmap32to16(machine, tBitmap, dst, pPalEntries);
		}
		else if(tBitmap.format()  == BITMAP_FORMAT_RGB15) {
			TransformBitmap15to16(machine, tBitmap, dst, pPalEntries);
		}
		else if(tBitmap.format()  == BITMAP_FORMAT_INDEXED16) {
			TransformBitmap16to16(machine, tBitmap, dst, pPalEntries);
		}
		else if(tBitmap.format()  == BITMAP_FORMAT_INDEXED8) 
		{
			TransformBitmap8to16(machine, tBitmap, dst, pPalEntries);
		}
	}

	/*
	if( bAviForceFlipY != FALSE )
	{
		int		  x, nLineSize, nWidth, nHeight, nHalfHeight;
		DWORD	 *lpLineTop, *lpLineBtm, dwTemp;

		nWidth	  = rectAviSrc.m_Width;
		nHeight   = rectAviSrc.m_Height;

		nLineSize  = (((nWidth * depth) / 8) + 3) & ~3;
		nLineSize /= sizeof(DWORD);

		lpLineTop = (DWORD*)&bitmap[bmihSize];
		lpLineBtm = lpLineTop + ((nHeight-1) * nLineSize);

		nHalfHeight = nHeight / 2;
		
		for (i=0; i<nHalfHeight; i++)
		{
			for (x = 0; x < nLineSize; x++)
			{
				dwTemp = lpLineTop[x];
				lpLineTop[x] = lpLineBtm[x];
				lpLineBtm[x] = dwTemp;
			}
			lpLineTop += nLineSize;
			lpLineBtm -= nLineSize;
		}
	}
	*/

    return bitmap;
}

void AVI_Create_8bit_Bitmap(void)
{
	int size;
	int depth = 8;
	UINT wLineLen;
	wLineLen = (nAviWidth * depth + 31) / 32 * 4;

	if (pAviBitmap_bitConv != NULL) free(pAviBitmap_bitConv);
	size = BMP_PALSIZE * sizeof(RGBQUAD) + nAviHeight * wLineLen; // * depth / 8;

	pAviBitmap_bitConv = (char*)malloc(size + sizeof(BITMAPINFOHEADER));
	if (pAviBitmap_bitConv == NULL)
	{
		bAviError = TRUE;
		return;
	}

	memset(pAviBitmap_bitConv, 0, size + sizeof(BITMAPINFOHEADER));

	{
		BITMAPINFOHEADER    bmiHeader;
		DWORD dwSize;
		DWORD wColSize;
		int width = nAviWidth;
		int height = nAviHeight;

		wColSize = sizeof(RGBQUAD) * ((depth <= 8) ? BMP_PALSIZE : 0);
		dwSize   = sizeof(BITMAPINFOHEADER) + wColSize +
						  (DWORD)(UINT)wLineLen * (DWORD)(UINT)height;

		/* This is the BITMAPINFOHEADER structure */
		bmiHeader.biSize            = sizeof(BITMAPINFOHEADER);
		bmiHeader.biWidth           = width;
		bmiHeader.biHeight          = height;
		bmiHeader.biPlanes          = 1;
		bmiHeader.biBitCount        = (depth <= 8) ? 8 : 16;
		bmiHeader.biCompression     = BI_RGB;
		bmiHeader.biSizeImage       = dwSize - sizeof(BITMAPINFOHEADER) - wColSize;
		bmiHeader.biXPelsPerMeter   = 0;
		bmiHeader.biYPelsPerMeter   = 0;
		bmiHeader.biClrUsed         = (depth == 8) ? BMP_PALSIZE : 0;
		bmiHeader.biClrImportant    = 0;

		memcpy(pAviBitmap_bitConv, (void*)&bmiHeader, sizeof(BITMAPINFOHEADER));
	}

	size = sizeof(RGBQUAD) * BMP_PALSIZE;
    memcpy(pAviBitmap_bitConv + sizeof(BITMAPINFOHEADER), &rgb16to8[0], size);
}

static void AVI_Create_24bit_Bitmap(void)
{
	int size;
	int depth = 24;
	UINT wLineLen;
	DWORD wColSize;
	wLineLen = (nAviWidth * depth + 31) / 32 * 4;

	if (pAviBitmap_bitConv != NULL) free(pAviBitmap_bitConv);

    wColSize = sizeof(RGBQUAD) * ((depth <= 8) ? BMP_PALSIZE : 0);
    size     = wColSize + (DWORD)(UINT)wLineLen * (DWORD)(UINT)nAviHeight;

	pAviBitmap_bitConv = (char*)malloc(size + sizeof(BITMAPINFOHEADER));
	if (pAviBitmap_bitConv == NULL)
	{
		bAviError = TRUE;
		return;
	}
	memset(pAviBitmap_bitConv, 0, size + sizeof(BITMAPINFOHEADER));

	{
	BITMAPINFOHEADER    bmiHeader;
    DWORD dwSize;
	int width = nAviWidth;
	int height = nAviHeight;

    dwSize = sizeof(BITMAPINFOHEADER) + wColSize +
                (DWORD)(UINT)wLineLen * (DWORD)(UINT)height;
    /* This is the BITMAPINFOHEADER structure */
    bmiHeader.biSize            = sizeof(BITMAPINFOHEADER);
    bmiHeader.biWidth           = width;
    bmiHeader.biHeight          = height;
    bmiHeader.biPlanes          = 1;
    bmiHeader.biBitCount        = depth;
    bmiHeader.biCompression     = BI_RGB;
    bmiHeader.biSizeImage       = dwSize - sizeof(BITMAPINFOHEADER) - wColSize;
    bmiHeader.biXPelsPerMeter   = 0;
    bmiHeader.biYPelsPerMeter   = 0;
    bmiHeader.biClrUsed         = (depth == 8) ? BMP_PALSIZE : 0;
    bmiHeader.biClrImportant    = 0;

	memcpy(pAviBitmap_bitConv, (void*)&bmiHeader, sizeof(BITMAPINFOHEADER));
	}
}


static void AVI_Convert_16to8_Bitmap(char *pSrcBitmap)
{
	int x,y;

	const int line8  = (nAviWidth * (8/8)+3) & ~3;
	const int line16 = ((rectAviSrc.m_Width * (16/8)+3) & ~3 ) / sizeof(unsigned short);// line size fix by DarkCoder
	const unsigned short* src;
	unsigned char* dst;
	unsigned short color16, r,g,b;

	src = (unsigned short*)(pSrcBitmap + sizeof(BITMAPINFOHEADER));
	dst = (unsigned char*)(pAviBitmap_bitConv + (sizeof(BITMAPINFOHEADER) + BMP_PALSIZE * sizeof(RGBQUAD)));


	for(y=0; y<rectAviSrc.m_Height; y++)
	{
		for(x=0; x<rectAviSrc.m_Width; x++)
		{
			color16 = src[x];
			r = (color16 >> 12) & 0x0007;
			g = (color16 >>  4) & 0x0038;		// ((color16 >> 7) & 0x07) << 3 (*8)
			b = (color16 <<  4) & 0x01c0;		// ((color16 >> 2) & 0x07) << 6 (*64)
			color16 = b + g + r;

			dst[x] = rgb16to8idx[color16];
		}

		src += line16;
		dst += line8;
	}
}

static void AVI_Convert_16to24_Bitmap(char *pSrcBitmap)
{
	int x,y;

	const int line24 = (nAviWidth * (24/8)+3) & ~3;
	const int line16 = ((rectAviSrc.m_Width * (16/8)+3) & ~3) / sizeof(unsigned short); // line size fix by DarkCoder
	const unsigned short* src;
	unsigned char*        dst, *tmp_dst;

	src = (unsigned short*)(pSrcBitmap + sizeof(BITMAPINFOHEADER));
	dst = (unsigned char*)(pAviBitmap_bitConv + sizeof(BITMAPINFOHEADER));

	for(y=0; y<rectAviSrc.m_Height; y++)
	{
		tmp_dst = dst;
		for(x=0; x<rectAviSrc.m_Width; x++)
		{
			const unsigned short col = src[x];
			unsigned char t;

			t = (col >>  0) & 0x1f;
			*(dst++) = (t<<3) | (t>>2);
			t = (col >>  5) & 0x1f;
			*(dst++) = (t<<3) | (t>>2);
			t = (col >> 10) & 0x1f;
			*(dst++) = (t<<3) | (t>>2);
		}

		src += line16;
		dst  = tmp_dst + line24;
	}
}

static void AVI_Convert_16to24_TVInterlace_Bitmap(char *pSrcBitmap, int l)
{
	int x,y;

	unsigned int srcoffs, dstoffs;
	const unsigned short* src;
	unsigned char*        dst;

	int srcx,srcy;
	int dstx,dsty;

	int addx, addy;

	srcx = rectAviSrc.m_Width  << 16;
	srcy = rectAviSrc.m_Height << 16;

	dstx = rectAvi.m_Width;
	dsty = rectAvi.m_Height;

	addx = srcx / dstx;
	addy = 0x10000;
	if (dstx > 720) dstx = 720;
	
	if (dsty != (srcy>>16))
	{
		dsty = 240;
		addy = srcy / dsty;
		rectAvi.m_Top = 0;
	}

	
	srcoffs = (unsigned int)(pSrcBitmap + sizeof(BITMAPINFOHEADER));
	dstoffs = (unsigned int)(pAviBitmap_bitConv + (rectAvi.m_Left * 3) + sizeof(BITMAPINFOHEADER));

	l &= 0x1;

	srcy = 0;
	for(y=0; y<dsty; y++)
	{
		src = (unsigned short*)(srcoffs + (srcy >> 16));
		dst = (unsigned char *)(dstoffs + (((y+rectAvi.m_Top)<<1) + l));
		srcx = 0;
		for(x=0; x<dstx; x++)
		{
			const unsigned short col = src[(srcx+0x7fff) >> 16];
			unsigned char t;

			t = (col >>  0) & 0x1f;
			*(dst++) = (t<<3) | (t>>2);
			t = (col >>  5) & 0x1f;
			*(dst++) = (t<<3) | (t>>2);
			t = (col >> 10) & 0x1f;
			*(dst++) = (t<<3) | (t>>2);


			srcx += addx;
		}
		srcy += addy;
	}
}


static void AVI_Convert_16to24_TVInterlace_s_Bitmap(char *pSrcBitmap, int l)
{
	int x,y;

	unsigned int srcoffs, dstoffs;
	const unsigned short* src;
	unsigned char*        dst;

	int srcx,srcy;
	int dstx,dsty;

	int addx, addy;

	srcx = rectAviSrc.m_Width << 16;
	srcy = rectAviSrc.m_Height << 16;

	dstx = rectAvi.m_Width;
	dsty = rectAvi.m_Height;

	addx = (srcx-0xffff) / (dstx-1);
	addy = 0x10000;
	if (dstx > 720) dstx = 720;

	if (dsty != (srcy>>16))
	{
		dsty = 240;
		addy = srcy / dsty;
		rectAvi.m_Top = 0;
	}


	srcoffs = (unsigned int)(pSrcBitmap + sizeof(BITMAPINFOHEADER));
	dstoffs = (unsigned int)(pAviBitmap_bitConv + (rectAvi.m_Left * 3) + sizeof(BITMAPINFOHEADER));

	l &= 0x1;

	srcy = 0;
	for(y=0; y<dsty; y++)
	{
		src = (unsigned short*)(srcoffs + (srcy >> 16));
		dst = (unsigned char *)(dstoffs + (((y+rectAvi.m_Top)<<1) + l));
		srcx = 0;
		for(x=0; x<dstx; x++)
		{
			const unsigned short col1 = src[srcx >> 16];
			const unsigned short col2 = src[(srcx+0xffff) >> 16];
			const int alpha = srcx & 0xffff;
			unsigned int r,g,b;
			unsigned int rr,gg,bb;

			b = (col1 >>  0) & 0x1f;
			g = (col1 >>  5) & 0x1f;
			r = (col1 >> 10) & 0x1f;
			b |= (b<<5) | (b<<10);
			g |= (g<<5) | (g<<10);
			r |= (r<<5) | (r<<10);

			bb = (col2 >>  0) & 0x1f;
			gg = (col2 >>  5) & 0x1f;
			rr = (col2 >> 10) & 0x1f;
			bb |= (bb<<5) | (bb<<10);
			gg |= (gg<<5) | (gg<<10);
			rr |= (rr<<5) | (rr<<10);

			r = (r * (0x10000-alpha)) + (rr * alpha);
			g = (g * (0x10000-alpha)) + (gg * alpha);
			b = (b * (0x10000-alpha)) + (bb * alpha);


			if(r>0x7fffffff) r=0x7fffffff;
			if(g>0x7fffffff) g=0x7fffffff;
			if(b>0x7fffffff) b=0x7fffffff;

			*(dst++) = (unsigned char)(b>>23);
			*(dst++) = (unsigned char)(g>>23);
			*(dst++) = (unsigned char)(r>>23);


			srcx += addx;
		}
		srcy += addy;
	}
}


static void AVI_Convert_16to24_TVInterlace_sxy_Bitmap(char *pSrcBitmap, int l)
{
	int x,y;

	const int line24 = (nAviWidth * (24/8)+3) & ~3;
	const int line16 = (rectAviSrc.m_Width * (16/8)+3) & ~3;
	unsigned int srcoffs, srcoffsa, dstoffs;
	const unsigned short *src, *srca;
	unsigned char        *dst;

	int srcx,srcy;
	int dstx,dsty;

	int addx, addy;
	int starty = 0;

	l &= 0x1;

	srcx = rectAviSrc.m_Width << 16;
	srcy = rectAviSrc.m_Height << 16;

	dstx = rectAvi.m_Width;
	dsty = rectAvi.m_Height;

	addx = (srcx-0xffff) / (dstx-1);
	addy = 0x10000;
	if (dstx > 720) dstx = 720;

	if (dsty != (srcy>>16))
	{
		int sy;
		sy = (srcy-0xffff) / (dsty*2-1);
		addy = sy*2; starty = (sy*l);
		rectAvi.m_Top = 0;
	}

	srcoffs  = (unsigned int)(pSrcBitmap + sizeof(BITMAPINFOHEADER));
	srcoffsa = (unsigned int)(pSrcBitmap + sizeof(BITMAPINFOHEADER));
	dstoffs  = (unsigned int)(pAviBitmap_bitConv + (rectAvi.m_Left * 3) + sizeof(BITMAPINFOHEADER));

	srcy = starty;
	for(y=0; y<dsty; y++)
	{
		const int alphay = srcy & 0xffff;

		src  = (unsigned short*)(srcoffs  + (srcy >> 16) * line16);
		srca = (unsigned short*)(srcoffsa + ((srcy+0xffff) >> 16) * line16);
		dst  = (unsigned char *)(dstoffs  + (((y+rectAvi.m_Top)<<1) + l) * line24);
		srcx = 0;
		for(x=0; x<dstx; x++)
		{
			const unsigned short col1 = src[srcx >> 16];
			const unsigned short col2 = src[(srcx+0xffff) >> 16];
			const unsigned short col1a = srca[srcx >> 16];
			const unsigned short col2a = srca[(srcx+0xffff) >> 16];
			const int alpha = srcx & 0xffff;
			unsigned int r,g,b;
			unsigned int rr,gg,bb;
			unsigned int ra,ga,ba;

			b = (col1 >>  0) & 0x1f;
			g = (col1 >>  5) & 0x1f;
			r = (col1 >> 10) & 0x1f;
			b |= (b<<5) | (b<<10);
			g |= (g<<5) | (g<<10);
			r |= (r<<5) | (r<<10);

			bb = (col2 >>  0) & 0x1f;
			gg = (col2 >>  5) & 0x1f;
			rr = (col2 >> 10) & 0x1f;
			bb |= (bb<<5) | (bb<<10);
			gg |= (gg<<5) | (gg<<10);
			rr |= (rr<<5) | (rr<<10);

			r = (r * (0x10000-alpha)) + (rr * alpha);
			g = (g * (0x10000-alpha)) + (gg * alpha);
			b = (b * (0x10000-alpha)) + (bb * alpha);


			ba = (col1a >>  0) & 0x1f;
			ga = (col1a >>  5) & 0x1f;
			ra = (col1a >> 10) & 0x1f;
			ba |= (ba<<5) | (ba<<10);
			ga |= (ga<<5) | (ga<<10);
			ra |= (ra<<5) | (ra<<10);

			bb = (col2a >>  0) & 0x1f;
			gg = (col2a >>  5) & 0x1f;
			rr = (col2a >> 10) & 0x1f;
			bb |= (bb<<5) | (bb<<10);
			gg |= (gg<<5) | (gg<<10);
			rr |= (rr<<5) | (rr<<10);

			ra = (ra * (0x10000-alpha)) + (rr * alpha);
			ga = (ga * (0x10000-alpha)) + (gg * alpha);
			ba = (ba * (0x10000-alpha)) + (bb * alpha);

			r = ((r>>16) * (0x10000-alphay)) + ((ra>>16) * alphay);
			g = ((g>>16) * (0x10000-alphay)) + ((ga>>16) * alphay);
			b = ((b>>16) * (0x10000-alphay)) + ((ba>>16) * alphay);

			if(r>0x7fffffff) r=0x7fffffff;
			if(g>0x7fffffff) g=0x7fffffff;
			if(b>0x7fffffff) b=0x7fffffff;

			*(dst++) = (unsigned char)(b>>23);
			*(dst++) = (unsigned char)(g>>23);
			*(dst++) = (unsigned char)(r>>23);


			srcx += addx;
		}
		srcy += addy;
	}
}


static void AVI_Convert_16to24_TVInterlace_sy_Bitmap(char *pSrcBitmap, int l)
{
	int x,y;

	const int line24 = (nAviWidth * (24/8)+3) & ~3;
	const int line16 = (rectAviSrc.m_Width * (16/8)+3) & ~3;
	unsigned int srcoffs, srcoffsa, dstoffs;
	const unsigned short *src, *srca;
	unsigned char        *dst;

	int srcx,srcy;
	int dstx,dsty;

	int addx, addy;
	int starty = 0;

	l &= 0x1;

	srcx = rectAviSrc.m_Width << 16;
	srcy = rectAviSrc.m_Height << 16;

	dstx = rectAvi.m_Width;
	dsty = rectAvi.m_Height;

	addx = srcx / dstx;
	addy = 0x10000;
	if (dstx > 720) dstx = 720;
	if (dsty > 240)
	{
		dsty = 240;
	}
	if (dsty != (srcy>>16))
	{
		int sy;
		sy = (srcy-0xffff) / (dsty*2-1);
		addy = sy*2; starty = (sy*l);
		rectAvi.m_Top = 0;
	}

	srcoffs  = (unsigned int)(pSrcBitmap + sizeof(BITMAPINFOHEADER));
	srcoffsa = (unsigned int)(pSrcBitmap + sizeof(BITMAPINFOHEADER));
	dstoffs  = (unsigned int)(pAviBitmap_bitConv + (rectAvi.m_Left * 3) + sizeof(BITMAPINFOHEADER));

	srcy = starty;
	for(y=0; y<dsty; y++)
	{
		const int alphay = srcy & 0xffff;
		src  = (unsigned short*)(srcoffs + (srcy >> 16) * line16);
		srca = (unsigned short*)(srcoffsa + ((srcy+0xffff) >> 16) * line16);
		dst  = (unsigned char*)(dstoffs + (((y+rectAvi.m_Top)<<1) + l) * line24);
		srcx = 0;
		for(x=0; x<dstx; x++)
		{
			const unsigned short col = src[(srcx+0x7fff) >> 16];
			const unsigned short cola = srca[(srcx+0x7fff) >> 16];
			//const int alpha = srcx & 0xffff;
			unsigned int r,g,b;
			unsigned int ra,ga,ba;

			b = (col >>  0) & 0x1f;
			g = (col >>  5) & 0x1f;
			r = (col >> 10) & 0x1f;
			b |= (b<<5) | (b<<10);
			g |= (g<<5) | (g<<10);
			r |= (r<<5) | (r<<10);


			ba = (cola >>  0) & 0x1f;
			ga = (cola >>  5) & 0x1f;
			ra = (cola >> 10) & 0x1f;
			ba |= (ba<<5) | (ba<<10);
			ga |= (ga<<5) | (ga<<10);
			ra |= (ra<<5) | (ra<<10);


			r = (r * (0x10000-alphay)) + (ra * alphay);
			g = (g * (0x10000-alphay)) + (ga * alphay);
			b = (b * (0x10000-alphay)) + (ba * alphay);

			if(r>0x7fffffff) r=0x7fffffff;
			if(g>0x7fffffff) g=0x7fffffff;
			if(b>0x7fffffff) b=0x7fffffff;

			*(dst++) = (unsigned char)(b>>23);
			*(dst++) = (unsigned char)(g>>23);
			*(dst++) = (unsigned char)(r>>23);


			srcx += addx;
		}
		srcy += addy;
	}
}


/* ------------------------AUDIO---------------------------------*/
//#ifdef AVI_AUDIO
int AVI_AudioStream_Start(void)
{
	nAviAudioBufSize         = 0;
	nAviAudioFileSize        = 0;
	lAviAudioBytesWritten    = 0;
	lAviAudioBytesWrittenMax = 0;

	if (pfile == NULL) return -1;

	if (CopyStream(pfile))
	{
        return -1;
	}
	bAviAudioRecord = TRUE;
	return 0;
}

void AVI_AudioStream_WriteWaveData(char* lpwav, int samples)
{
	int dstlen;

	if (bAviAudioRecord == FALSE || bAviError == TRUE) return;


		dstlen = samples * (Avi_StatusAvi.avi_audio_channel * (Avi_StatusAvi.avi_audio_bitrate/8));

	if (AVIStreamWrite(audio_ps,nAviAudioSamples,samples, lpwav, dstlen ,AVIIF_KEYFRAME,NULL,&lAviAudioBytesWritten)!=0)
	{
		bAviError = TRUE;
	}

	if (lAviAudioBytesWritten > lAviAudioBytesWrittenMax) lAviAudioBytesWrittenMax = lAviAudioBytesWritten;

	nAviAudioFileSize += (unsigned __int64)lAviAudioBytesWritten;
	nAviAudioSamples += samples;

}
//#endif	/* AUDIO */

#endif /* MAME_AVI */
