/**********************************************************************************
  Snes9x - Portable Super Nintendo Entertainment System (TM) emulator.

  (c) Copyright 1996 - 2002  Gary Henderson (gary.henderson@ntlworld.com),
                             Jerremy Koot (jkoot@snes9x.com)

  (c) Copyright 2002 - 2004  Matthew Kendora

  (c) Copyright 2002 - 2005  Peter Bortas (peter@bortas.org)

  (c) Copyright 2004 - 2005  Joel Yliluoma (http://iki.fi/bisqwit/)

  (c) Copyright 2001 - 2006  John Weidman (jweidman@slip.net)

  (c) Copyright 2002 - 2006  funkyass (funkyass@spam.shaw.ca),
                             Kris Bleakley (codeviolation@hotmail.com)

  (c) Copyright 2002 - 2007  Brad Jorsch (anomie@users.sourceforge.net),
                             Nach (n-a-c-h@users.sourceforge.net),
                             zones (kasumitokoduck@yahoo.com)

  (c) Copyright 2006 - 2007  nitsuja


  BS-X C emulator code
  (c) Copyright 2005 - 2006  Dreamer Nom,
                             zones

  C4 x86 assembler and some C emulation code
  (c) Copyright 2000 - 2003  _Demo_ (_demo_@zsnes.com),
                             Nach,
                             zsKnight (zsknight@zsnes.com)

  C4 C++ code
  (c) Copyright 2003 - 2006  Brad Jorsch,
                             Nach

  DSP-1 emulator code
  (c) Copyright 1998 - 2006  _Demo_,
                             Andreas Naive (andreasnaive@gmail.com)
                             Gary Henderson,
                             Ivar (ivar@snes9x.com),
                             John Weidman,
                             Kris Bleakley,
                             Matthew Kendora,
                             Nach,
                             neviksti (neviksti@hotmail.com)

  DSP-2 emulator code
  (c) Copyright 2003         John Weidman,
                             Kris Bleakley,
                             Lord Nightmare (lord_nightmare@users.sourceforge.net),
                             Matthew Kendora,
                             neviksti


  DSP-3 emulator code
  (c) Copyright 2003 - 2006  John Weidman,
                             Kris Bleakley,
                             Lancer,
                             z80 gaiden

  DSP-4 emulator code
  (c) Copyright 2004 - 2006  Dreamer Nom,
                             John Weidman,
                             Kris Bleakley,
                             Nach,
                             z80 gaiden

  OBC1 emulator code
  (c) Copyright 2001 - 2004  zsKnight,
                             pagefault (pagefault@zsnes.com),
                             Kris Bleakley,
                             Ported from x86 assembler to C by sanmaiwashi

  SPC7110 and RTC C++ emulator code
  (c) Copyright 2002         Matthew Kendora with research by
                             zsKnight,
                             John Weidman,
                             Dark Force

  S-DD1 C emulator code
  (c) Copyright 2003         Brad Jorsch with research by
                             Andreas Naive,
                             John Weidman

  S-RTC C emulator code
  (c) Copyright 2001-2006    byuu,
                             John Weidman

  ST010 C++ emulator code
  (c) Copyright 2003         Feather,
                             John Weidman,
                             Kris Bleakley,
                             Matthew Kendora

  Super FX x86 assembler emulator code
  (c) Copyright 1998 - 2003  _Demo_,
                             pagefault,
                             zsKnight,

  Super FX C emulator code
  (c) Copyright 1997 - 1999  Ivar,
                             Gary Henderson,
                             John Weidman

  Sound DSP emulator code is derived from SNEeSe and OpenSPC:
  (c) Copyright 1998 - 2003  Brad Martin
  (c) Copyright 1998 - 2006  Charles Bilyue'

  SH assembler code partly based on x86 assembler code
  (c) Copyright 2002 - 2004  Marcus Comstedt (marcus@mc.pp.se)

  2xSaI filter
  (c) Copyright 1999 - 2001  Derek Liauw Kie Fa

  HQ2x, HQ3x, HQ4x filters
  (c) Copyright 2003         Maxim Stepin (maxim@hiend3d.com)

  Blaarg's NTSC Library
  (c) Copyright 2006 - 2007	 Shay Green

  Win32 GUI code
  (c) Copyright 2003 - 2006  blip,
                             funkyass,
                             Matthew Kendora,
                             Nach,
                             nitsuja

  Mac OS GUI code
  (c) Copyright 1998 - 2001  John Stiles
  (c) Copyright 2001 - 2007  zones


  Specific ports contains the works of other authors. See headers in
  individual files.


  Snes9x homepage: http://www.snes9x.com

  Permission to use, copy, modify and/or distribute Snes9x in both binary
  and source form, for non-commercial purposes, is hereby granted without
  fee, providing that this license information and copyright notice appear
  with all copies and any derived work.

  This software is provided 'as-is', without any express or implied
  warranty. In no event shall the authors be held liable for any damages
  arising from the use of this software or it's derivatives.

  Snes9x is freeware for PERSONAL USE only. Commercial users should
  seek permission of the copyright holders first. Commercial use includes,
  but is not limited to, charging money for Snes9x or software derived from
  Snes9x, including Snes9x or derivatives in commercial game bundles, and/or
  using Snes9x as a promotion for your commercial product.

  The copyright holders request that bug fixes and improvements to the code
  should be forwarded to them so everyone can benefit from the modifications
  in future versions.

  Super NES and Super Nintendo Entertainment System are trademarks of
  Nintendo Co., Limited and its subsidiary companies.
**********************************************************************************/



/* Render.CPP
 * ----------
 * Video output filters for the Windows port.
 */
#include <windows.h>
#include <mmsystem.h>
#undef interface

#include "port.h"

//#define R5G6B5 // windows port uses RGB565

#ifdef R5G6B5
	#define	Mask_2	0x07E0	// 00000 111111 00000
	#define	Mask13	0xF81F	// 11111 000000 11111
	#define	Mask_1	0x001F	// 00000 000000 11111
	#define	Mask_3	0xF800	// 11111 000000 00000
	#define CONVERT_16_TO_32(pixel) \
        (((((pixel) >> 11)        ) << /*RedShift+3*/  19) | \
         ((((pixel) >> 6)   & 0x1f) << /*GreenShift+3*/11) | \
          (((pixel)         & 0x1f) << /*BlueShift+3*/ 3))
	#define NUMBITS (16)
#else
	#define	Mask_2	0x03E0	// 00000 11111 00000
	#define	Mask13	0x7C1F	// 11111 00000 11111
	#define	Mask_1	0x001F	// 00000 00000 11111
	#define	Mask_3	0x7C00	// 11111 00000 00000
	#define CONVERT_16_TO_32(pixel) \
        (((((pixel) >> 10)        ) << /*RedShift+3*/  19) | \
         ((((pixel) >> 5)   & 0x1f) << /*GreenShift+3*/11) | \
          (((pixel)         & 0x1f) << /*BlueShift+3*/ 3))
	#define NUMBITS (15)
#endif

static int	RGBtoYUV[1<<NUMBITS];
static uint16 RGBtoBright[1<<NUMBITS];

#define Interp05(c1, c2) \
	(((c1) == (c2)) ? (c1) : \
	((((((c1) & Mask_2)      + ((c2) & Mask_2)) >> 1) & Mask_2) + \
	 (((((c1) & Mask13)      + ((c2) & Mask13)) >> 1) & Mask13)))
#define Interp01(c1, c2) \
	((((c1) == (c2)) ? (c1) : \
	(((((((c1) & Mask_2) *  3) + ((c2) & Mask_2)) >> 2) & Mask_2) + \
	 ((((((c1) & Mask13) *  3) + ((c2) & Mask13)) >> 2) & Mask13))))
#define Halve(c1) \
	((((((c1) & Mask_2)) >> 1) & Mask_2) + \
	 (((((c1) & Mask13)) >> 1) & Mask13))
#define ThreeQuarters(c1) \
	((((((c1) & Mask_2)*3) >> 2) & Mask_2) + \
	 (((((c1) & Mask13)*3) >> 2) & Mask13))

#ifdef LSB_FIRST
	#define TWO_PIX(left,right) ((left) | ((right) << 16))
	#define THREE_PIX(left,middle,right) uint48((left) | ((middle) << 16), (right))
	#define TWO_PIX_32(left,right) (CONVERT_16_TO_32(left) | ((uint64)CONVERT_16_TO_32(right) << 32))
	#define THREE_PIX_32(left,middle,right) uint96(CONVERT_16_TO_32(left) | ((uint64)CONVERT_16_TO_32(middle) << 32), CONVERT_16_TO_32(right))
#else
	#define TWO_PIX(left,right) ((right) | ((left) << 16))
	#define THREE_PIX(left,middle,right) uint48((middle) | ((left) << 16), (right)) // is this right?
//	#define THREE_PIX(left,middle,right) uint48((right) | ((middle) << 16), (left)) // or this?
#endif


// shared EPX-type loop macros
// All of these parameters will be constant values,
// so I hope the compiler is smart enough to optimize away "if(0) ..."

#define DrawRows(scale,diags)            \
	{                                    \
		h = srcHeight - 1;               \
		DoRow(0,1,scale,diags);          \
		for (h = srcHeight - 2; h; h--)  \
			DoRow(1,1,scale,diags);      \
		DoRow(1,0,scale,diags);          \
	}

#define DoRow(topValid,botValid,scale,diags)              \
	{                                                     \
		w = srcWidth - 1;                                 \
		InitLine(topValid,botValid,scale,diags);          \
		DrawPix(0,topValid,0,botValid);                   \
		for (w = srcWidth - 2; w; w--)                    \
		{                                                 \
			NextPixel(topValid,botValid,1,diags);         \
			DrawPix(topValid,topValid,botValid,botValid); \
		}                                                 \
		NextPixel(topValid,botValid,0,diags);             \
		DrawPix(topValid,0,botValid,0);                   \
		srcPtr += srcPitch;                               \
		dstPtr += dstPitch * scale;                       \
	}

#define InitLine(topValid, botValid, scale, diags)                \
	{                                                             \
		if(topValid) uP  = (uint16 *) (srcPtr - srcPitch);        \
		if(botValid) lP  = (uint16 *) (srcPtr + srcPitch);        \
					 sP  = (uint16 *) srcPtr;                     \
					 dP1 = (destType *) dstPtr;                   \
					 dP2 = (destType *) (dstPtr + dstPitch);      \
		if(topValid) colorD = *uP++;                              \
		if(botValid) colorB = *lP++;                              \
					colorX = *sP++;                               \
					colorC = *sP;                                 \
		if(diags) if(topValid) colorH = *uP;                      \
		if(diags) if(botValid) colorG = *lP;                      \
	}

#define NextPixel(topValid, botValid, rightValid, diags)      \
	{                                                         \
		colorA = colorX;                                      \
		colorX = colorC;                                      \
		if(rightValid) colorC = *++sP;                        \
		if(diags) {                                           \
			if(botValid){                                     \
				colorF = colorB;                              \
				colorB = colorG;                              \
				if(rightValid) colorG = *++lP;                \
			}                                                 \
			if(topValid){                                     \
				colorE = colorD;                              \
				colorD = colorH;                              \
				if(rightValid) colorH = *++uP;                \
			}                                                 \
		} else {                                              \
			if(botValid) colorB = *lP++;                      \
			if(topValid) colorD = *uP++;                      \
		}                                                     \
	}

#define DrawInit(scale,uintDest)                                                            \
	uint8 *srcPtr = src, *dstPtr = dst;                                     \
	const uint32 srcPitch = srcpitch, dstPitch = dstpitch;                                \
	const uint32 srcHeight = nHeight;                              \
	const uint32 srcWidth = nWidth;                               \
	uint16	colorX, colorA, colorB, colorC, colorD, colorE=0, colorF=0, colorG=0, colorH=0; \
	uint16	*sP, *uP, *lP;                                                                  \
	typedef uintDest destType;                                                              \
	destType *dP1, *dP2;                                                            \
	int		w, h;


// code for improved 2X EPX, which tends to do better with diagonal edges than regular EPX
void RenderEPXB(unsigned char *src, unsigned int srcpitch, unsigned char *dst, unsigned int dstpitch, int nWidth, int nHeight)
{
	// E D H
	// A X C
	// F B G
	#define DrawPix(on00,on01,on10,on11) /* on00 on01 */                                                                                                       \
	{                                    /* on10 on11 */                                                                                                       \
		if ((((on00||on10)?colorA:colorX) != ((on01||on11)?colorC:colorX))                                                                                     \
		&& (((on10||on11)?colorB:colorX) != ((on00||on01)?colorD:colorX))                                                                                      \
		&& ((!on00||!on01||!on10|!on11) ||                                                                                                                     \
			((colorX == colorA) || (colorX == colorB) || (colorX == colorC) || (colorX == colorD) || /* diagonal    */                                         \
			 (((colorE != colorG) || (colorX == colorF) || (colorX == colorH)) &&                    /*  edge       */                                         \
			  ((colorF != colorH) || (colorX == colorE) || (colorX == colorG))))))                   /*   smoothing */                                         \
		{                                                                                                                                                      \
			*dP1++ = _TWO_PIX((on00 && colorD == colorA && (colorX != colorE || colorX != colorG || colorD != colorH || colorA != colorF)) ? colorD : colorX,  \
							  (on01 && colorC == colorD && (colorX != colorH || colorX != colorF || colorC != colorG || colorD != colorE)) ? colorC : colorX); \
			*dP2++ = _TWO_PIX((on10 && colorA == colorB && (colorX != colorF || colorX != colorH || colorA != colorE || colorB != colorG)) ? colorA : colorX,  \
							  (on11 && colorB == colorC && (colorX != colorG || colorX != colorE || colorB != colorF || colorC != colorH)) ? colorB : colorX); \
		} else {                                                                                                                                               \
			*dP1++ = _TWO_PIX(colorX, colorX);                                                                                                                 \
			*dP2++ = _TWO_PIX(colorX, colorX);                                                                                                                 \
		}                                                                                                                                                      \
	}

	// again, this supports 32-bit or 16-bit rendering
#define _TWO_PIX TWO_PIX
	DrawInit(2,uint32);
	DrawRows(2,1); // 2x scale, and diags is on since we do use all 8 surrounding pixels
#undef _TWO_PIX

	#undef DrawPix
}

#define Interp44(c1, c2, c3, c4) \
	((((((c1) & Mask_2) * 5 + ((c2) & Mask_2) + ((c3) & Mask_2) + ((c4) & Mask_2)) >> 3) & Mask_2) + \
	 (((((c1) & Mask13) * 5 + ((c2) & Mask13) + ((c3) & Mask13) + ((c4) & Mask13)) >> 3) & Mask13))

// EPX3 scaled down to 2X
void RenderEPXC(unsigned char *src, unsigned int srcpitch, unsigned char *dst, unsigned int dstpitch, int nWidth, int nHeight)
{
	// E D H
	// A X C
	// F B G
	#define DrawPix(on00,on01,on10,on11) /* on00 on01 */ \
	{                                    /* on10 on11 */ \
		if ((((on00||on10)?colorA:colorX) != ((on01||on11)?colorC:colorX)) \
		 && (((on10||on11)?colorB:colorX) != ((on00||on01)?colorD:colorX))) \
		{ \
			UINT8 XnE = colorX != colorE; \
			UINT8 XnF = colorX != colorF; \
			UINT8 XnG = colorX != colorG; \
			UINT8 XnH = colorX != colorH; \
			UINT8 DA = on00 && colorD == colorA && (XnE || XnG || colorD != colorH || colorA != colorF); \
			UINT8 AB = on10 && colorA == colorB && (XnF || XnH || colorA != colorE || colorB != colorG); \
			UINT8 BC = on11 && colorB == colorC && (XnG || XnE || colorB != colorF || colorC != colorH); \
			UINT8 CD = on01 && colorC == colorD && (XnH || XnF || colorC != colorG || colorD != colorE); \
			if (!on00||!on01||!on10||!on11 || ((colorA != colorC) && (colorB != colorD) && \
				((colorX == colorA) || (colorX==colorB) || (colorX==colorC) || (colorX==colorD) || (colorX==colorE) || (colorX==colorF) || (colorX==colorG) || (colorX==colorH)))) \
			{ \
				const uint16 colorAA = on00&&on10 && ((DA && XnF) || (AB && XnE)) ? colorA : colorX; \
				const uint16 colorBB = on10&&on11 && ((AB && XnG) || (BC && XnF)) ? colorB : colorX; \
				const uint16 colorCC = on01&&on11 && ((BC && XnH) || (CD && XnG)) ? colorC : colorX; \
				const uint16 colorDD = on00&&on01 && ((CD && XnE) || (DA && XnH)) ? colorD : colorX; \
				*dP1++ = _TWO_PIX(Interp44(on00 && DA ? colorA : colorX, colorDD, colorAA, colorX), Interp44(on01 && CD ? colorC : colorX, colorBB, colorCC, colorX)); \
				*dP2++ = _TWO_PIX(Interp44(on10 && AB ? colorA : colorX, colorAA, colorBB, colorX), Interp44(on11 && BC ? colorC : colorX, colorCC, colorDD, colorX)); \
			} else { \
				*dP1++ = _TWO_PIX(Interp01(colorX, on00 && DA && (colorX!=colorB&&colorX!=colorC) ? colorA : colorX), Interp01(colorX, on01 && CD && (colorX!=colorA&&colorX!=colorB) ? colorC : colorX)); \
				*dP2++ = _TWO_PIX(Interp01(colorX, on10 && AB && (colorX!=colorC&&colorX!=colorD) ? colorA : colorX), Interp01(colorX, on11 && BC && (colorX!=colorD&&colorX!=colorA) ? colorC : colorX)); \
			} \
		} else { \
			*dP1++ = _TWO_PIX(colorX, colorX); \
			*dP2++ = _TWO_PIX(colorX, colorX); \
		} \
	}

#define _TWO_PIX TWO_PIX
	DrawInit(2,uint32);
	DrawRows(2,1); // 2x scale, and diags is on since we do use all 8 surrounding pixels
#undef _TWO_PIX

	#undef DrawPix
}



#undef DoRow
#undef InitLine
#undef NextPixel
#undef DrawRows
#undef DrawInit





////////////////////////////////////////////////////////////////////////////////
// HQ2X stuff follows)
////////////////////////////////////////////////////////////////////////////////



#define	Ymask	0xFF0000
#define	Umask	0x00FF00
#define	Vmask	0x0000FF
#define	trY		0x300000
#define	trU		0x000700
#define	trV		0x000006




#define Interp02(c1, c2, c3) \
	((((((c1) & Mask_2) *  2 + ((c2) & Mask_2)     + ((c3) & Mask_2)    ) >> 2) & Mask_2) + \
	(((((c1) & Mask13) *  2 + ((c2) & Mask13)     + ((c3) & Mask13)    ) >> 2) & Mask13))

#define Interp06(c1, c2, c3) \
	((((((c1) & Mask_2) *  5 + ((c2) & Mask_2) * 2 + ((c3) & Mask_2)    ) >> 3) & Mask_2) + \
	(((((c1) & Mask13) *  5 + ((c2) & Mask13) * 2 + ((c3) & Mask13)    ) >> 3) & Mask13))

#define Interp07(c1, c2, c3) \
	((((((c1) & Mask_2) *  6 + ((c2) & Mask_2)     + ((c3) & Mask_2)    ) >> 3) & Mask_2) + \
	(((((c1) & Mask13) *  6 + ((c2) & Mask13)     + ((c3) & Mask13)    ) >> 3) & Mask13))

#define Interp09(c1, c2, c3) \
	((((((c1) & Mask_2) *  2 + ((c2) & Mask_2) * 3 + ((c3) & Mask_2) * 3) >> 3) & Mask_2) + \
	(((((c1) & Mask13) *  2 + ((c2) & Mask13) * 3 + ((c3) & Mask13) * 3) >> 3) & Mask13))

#define Interp10(c1, c2, c3) \
	((((((c1) & Mask_2) * 14 + ((c2) & Mask_2)     + ((c3) & Mask_2)    ) >> 4) & Mask_2) + \
	(((((c1) & Mask13) * 14 + ((c2) & Mask13)     + ((c3) & Mask13)    ) >> 4) & Mask13))

#define PIXEL00_0		*(dp) = w5
#define PIXEL00_10		*(dp) = Interp01(w5, w1)
#define PIXEL00_11		*(dp) = Interp01(w5, w4)
#define PIXEL00_12		*(dp) = Interp01(w5, w2)
#define PIXEL00_20		*(dp) = Interp02(w5, w4, w2)
#define PIXEL00_21		*(dp) = Interp02(w5, w1, w2)
#define PIXEL00_22		*(dp) = Interp02(w5, w1, w4)
#define PIXEL00_60		*(dp) = Interp06(w5, w2, w4)
#define PIXEL00_61		*(dp) = Interp06(w5, w4, w2)
#define PIXEL00_70		*(dp) = Interp07(w5, w4, w2)
#define PIXEL00_90		*(dp) = Interp09(w5, w4, w2)
#define PIXEL00_100		*(dp) = Interp10(w5, w4, w2)

#define PIXEL01_0		*(dp + 1) = w5
#define PIXEL01_10		*(dp + 1) = Interp01(w5, w3)
#define PIXEL01_11		*(dp + 1) = Interp01(w5, w2)
#define PIXEL01_12		*(dp + 1) = Interp01(w5, w6)
#define PIXEL01_20		*(dp + 1) = Interp02(w5, w2, w6)
#define PIXEL01_21		*(dp + 1) = Interp02(w5, w3, w6)
#define PIXEL01_22		*(dp + 1) = Interp02(w5, w3, w2)
#define PIXEL01_60		*(dp + 1) = Interp06(w5, w6, w2)
#define PIXEL01_61		*(dp + 1) = Interp06(w5, w2, w6)
#define PIXEL01_70		*(dp + 1) = Interp07(w5, w2, w6)
#define PIXEL01_90		*(dp + 1) = Interp09(w5, w2, w6)
#define PIXEL01_100		*(dp + 1) = Interp10(w5, w2, w6)

#define PIXEL10_0		*(dp + dst1line) = w5
#define PIXEL10_10		*(dp + dst1line) = Interp01(w5, w7)
#define PIXEL10_11		*(dp + dst1line) = Interp01(w5, w8)
#define PIXEL10_12		*(dp + dst1line) = Interp01(w5, w4)
#define PIXEL10_20		*(dp + dst1line) = Interp02(w5, w8, w4)
#define PIXEL10_21		*(dp + dst1line) = Interp02(w5, w7, w4)
#define PIXEL10_22		*(dp + dst1line) = Interp02(w5, w7, w8)
#define PIXEL10_60		*(dp + dst1line) = Interp06(w5, w4, w8)
#define PIXEL10_61		*(dp + dst1line) = Interp06(w5, w8, w4)
#define PIXEL10_70		*(dp + dst1line) = Interp07(w5, w8, w4)
#define PIXEL10_90		*(dp + dst1line) = Interp09(w5, w8, w4)
#define PIXEL10_100		*(dp + dst1line) = Interp10(w5, w8, w4)

#define PIXEL11_0		*(dp + dst1line + 1) = w5
#define PIXEL11_10		*(dp + dst1line + 1) = Interp01(w5, w9)
#define PIXEL11_11		*(dp + dst1line + 1) = Interp01(w5, w6)
#define PIXEL11_12		*(dp + dst1line + 1) = Interp01(w5, w8)
#define PIXEL11_20		*(dp + dst1line + 1) = Interp02(w5, w6, w8)
#define PIXEL11_21		*(dp + dst1line + 1) = Interp02(w5, w9, w8)
#define PIXEL11_22		*(dp + dst1line + 1) = Interp02(w5, w9, w6)
#define PIXEL11_60		*(dp + dst1line + 1) = Interp06(w5, w8, w6)
#define PIXEL11_61		*(dp + dst1line + 1) = Interp06(w5, w6, w8)
#define PIXEL11_70		*(dp + dst1line + 1) = Interp07(w5, w6, w8)
#define PIXEL11_90		*(dp + dst1line + 1) = Interp09(w5, w6, w8)
#define PIXEL11_100		*(dp + dst1line + 1) = Interp10(w5, w6, w8)

#define Absolute(c) \
(!((c) & (1 << 31)) ? (c) : (~(c) + 1))


inline UINT8 Diff(int c1, int c2)
{
	int c1y = (c1 & Ymask) - (c2 & Ymask);
	int c1u = (c1 & Umask) - (c2 & Umask);
	int c1v = (c1 & Vmask) - (c2 & Vmask);

	if (Absolute(c1y) > trY) return true;
	if (Absolute(c1u) > trU) return true;
	if (Absolute(c1v) > trV) return true;

	return false;
}

void InitLUTs(void)
{
	int	c, r, g, b, y, u, v;
	static int hasInit = 0;

	if (hasInit > 0)
		return;

	for (c = 0 ; c < (1<<NUMBITS) ; c++)
  	{
#ifdef R5G6B5
		b = (int)((c & 0x1F)) << 3;
		g = (int)((c & 0x7E0)) >> 3;
		r = (int)((c & 0xF800)) >> 8;
#else
		b = (int)((c & 0x1F)) << 3;
		g = (int)((c & 0x3E0)) >> 2;
		r = (int)((c & 0x7C00)) >> 7;
#endif
		RGBtoBright[c] = r+r+r + g+g+g + b+b;

		y = (int)( 0.256788f*r + 0.504129f*g + 0.097906f*b + 0.5f) + 16;
		u = (int)(-0.148223f*r - 0.290993f*g + 0.439216f*b + 0.5f) + 128;
		v = (int)( 0.439216f*r - 0.367788f*g - 0.071427f*b + 0.5f) + 128;

		RGBtoYUV[c] = (y << 16) + (u << 8) + v;

//		y = (r + g + b) >> 2;
//    	u = 128 + ((r - b) >> 2);
//    	v = 128 + ((-r + 2 * g - b) >> 3);
//
//		RGBtoYUVLQ[c] = (y << 16) + (u << 8) + v;
	}

	hasInit = 1;
}

#define HQ2XCASES \
	case 0: case 1: case 4: case 32: case 128: case 5: case 132: case 160: case 33: case 129: case 36: case 133: case 164: case 161: case 37: case 165: PIXEL00_20; PIXEL01_20; PIXEL10_20; PIXEL11_20; break; \
	case 2: case 34: case 130: case 162: PIXEL00_22; PIXEL01_21; PIXEL10_20; PIXEL11_20; break; \
	case 16: case 17: case 48: case 49: PIXEL00_20; PIXEL01_22; PIXEL10_20; PIXEL11_21; break; \
	case 64: case 65: case 68: case 69: PIXEL00_20; PIXEL01_20; PIXEL10_21; PIXEL11_22; break; \
	case 8: case 12: case 136: case 140: PIXEL00_21; PIXEL01_20; PIXEL10_22; PIXEL11_20; break; \
	case 3: case 35: case 131: case 163: PIXEL00_11; PIXEL01_21; PIXEL10_20; PIXEL11_20; break; \
	case 6: case 38: case 134: case 166: PIXEL00_22; PIXEL01_12; PIXEL10_20; PIXEL11_20; break; \
	case 20: case 21: case 52: case 53: PIXEL00_20; PIXEL01_11; PIXEL10_20; PIXEL11_21; break; \
	case 144: case 145: case 176: case 177: PIXEL00_20; PIXEL01_22; PIXEL10_20; PIXEL11_12; break; \
	case 192: case 193: case 196: case 197: PIXEL00_20; PIXEL01_20; PIXEL10_21; PIXEL11_11; break; \
	case 96: case 97: case 100: case 101: PIXEL00_20; PIXEL01_20; PIXEL10_12; PIXEL11_22; break; \
	case 40: case 44: case 168: case 172: PIXEL00_21; PIXEL01_20; PIXEL10_11; PIXEL11_20; break; \
	case 9: case 13: case 137: case 141: PIXEL00_12; PIXEL01_20; PIXEL10_22; PIXEL11_20; break; \
	case 18: case 50: PIXEL00_22; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_10; else PIXEL01_20; PIXEL10_20; PIXEL11_21; break; \
	case 80: case 81: PIXEL00_20; PIXEL01_22; PIXEL10_21; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_10; else PIXEL11_20; break; \
	case 72: case 76: PIXEL00_21; PIXEL01_20; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_10; else PIXEL10_20; PIXEL11_22; break; \
	case 10: case 138: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_10; else PIXEL00_20; PIXEL01_21; PIXEL10_22; PIXEL11_20; break; \
	case 66: PIXEL00_22; PIXEL01_21; PIXEL10_21; PIXEL11_22; break; \
	case 24: PIXEL00_21; PIXEL01_22; PIXEL10_22; PIXEL11_21; break; \
	case 7: case 39: case 135: PIXEL00_11; PIXEL01_12; PIXEL10_20; PIXEL11_20; break; \
	case 148: case 149: case 180: PIXEL00_20; PIXEL01_11; PIXEL10_20; PIXEL11_12; break; \
	case 224: case 228: case 225: PIXEL00_20; PIXEL01_20; PIXEL10_12; PIXEL11_11; break; \
	case 41: case 169: case 45: PIXEL00_12; PIXEL01_20; PIXEL10_11; PIXEL11_20; break; \
	case 22: case 54: PIXEL00_22; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_20; PIXEL10_20; PIXEL11_21; break; \
	case 208: case 209: PIXEL00_20; PIXEL01_22; PIXEL10_21; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_20; break; \
	case 104: case 108: PIXEL00_21; PIXEL01_20; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_20; PIXEL11_22; break; \
	case 11: case 139: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_20; PIXEL01_21; PIXEL10_22; PIXEL11_20; break; \
	case 19: case 51: if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL00_11, PIXEL01_10; else PIXEL00_60, PIXEL01_90; PIXEL10_20; PIXEL11_21; break; \
	case 146: case 178: PIXEL00_22; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_10, PIXEL11_12; else PIXEL01_90, PIXEL11_61; PIXEL10_20; break; \
	case 84: case 85: PIXEL00_20; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL01_11, PIXEL11_10; else PIXEL01_60, PIXEL11_90; PIXEL10_21; break; \
	case 112: case 113: PIXEL00_20; PIXEL01_22; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL10_12, PIXEL11_10; else PIXEL10_61, PIXEL11_90; break; \
	case 200: case 204: PIXEL00_21; PIXEL01_20; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_10, PIXEL11_11; else PIXEL10_90, PIXEL11_60; break; \
	case 73: case 77: if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL00_12, PIXEL10_10; else PIXEL00_61, PIXEL10_90; PIXEL01_20; PIXEL11_22; break; \
	case 42: case 170: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_10, PIXEL10_11; else PIXEL00_90, PIXEL10_60; PIXEL01_21; PIXEL11_20; break; \
	case 14: case 142: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_10, PIXEL01_12; else PIXEL00_90, PIXEL01_61; PIXEL10_22; PIXEL11_20; break; \
	case 67: PIXEL00_11; PIXEL01_21; PIXEL10_21; PIXEL11_22; break; \
	case 70: PIXEL00_22; PIXEL01_12; PIXEL10_21; PIXEL11_22; break; \
	case 28: PIXEL00_21; PIXEL01_11; PIXEL10_22; PIXEL11_21; break; \
	case 152: PIXEL00_21; PIXEL01_22; PIXEL10_22; PIXEL11_12; break; \
	case 194: PIXEL00_22; PIXEL01_21; PIXEL10_21; PIXEL11_11; break; \
	case 98: PIXEL00_22; PIXEL01_21; PIXEL10_12; PIXEL11_22; break; \
	case 56: PIXEL00_21; PIXEL01_22; PIXEL10_11; PIXEL11_21; break; \
	case 25: PIXEL00_12; PIXEL01_22; PIXEL10_22; PIXEL11_21; break; \
	case 26: case 31: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_20; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_20; PIXEL10_22; PIXEL11_21; break; \
	case 82: case 214: PIXEL00_22; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_20; PIXEL10_21; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_20; break; \
	case 88: case 248: PIXEL00_21; PIXEL01_22; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_20; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_20; break; \
	case 74: case 107: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_20; PIXEL01_21; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_20; PIXEL11_22; break; \
	case 27: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_20; PIXEL01_10; PIXEL10_22; PIXEL11_21; break; \
	case 86: PIXEL00_22; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_20; PIXEL10_21; PIXEL11_10; break; \
	case 216: PIXEL00_21; PIXEL01_22; PIXEL10_10; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_20; break; \
	case 106: PIXEL00_10; PIXEL01_21; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_20; PIXEL11_22; break; \
	case 30: PIXEL00_10; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_20; PIXEL10_22; PIXEL11_21; break; \
	case 210: PIXEL00_22; PIXEL01_10; PIXEL10_21; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_20; break; \
	case 120: PIXEL00_21; PIXEL01_22; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_20; PIXEL11_10; break; \
	case 75: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_20; PIXEL01_21; PIXEL10_10; PIXEL11_22; break; \
	case 29: PIXEL00_12; PIXEL01_11; PIXEL10_22; PIXEL11_21; break; \
	case 198: PIXEL00_22; PIXEL01_12; PIXEL10_21; PIXEL11_11; break; \
	case 184: PIXEL00_21; PIXEL01_22; PIXEL10_11; PIXEL11_12; break; \
	case 99: PIXEL00_11; PIXEL01_21; PIXEL10_12; PIXEL11_22; break; \
	case 57: PIXEL00_12; PIXEL01_22; PIXEL10_11; PIXEL11_21; break; \
	case 71: PIXEL00_11; PIXEL01_12; PIXEL10_21; PIXEL11_22; break; \
	case 156: PIXEL00_21; PIXEL01_11; PIXEL10_22; PIXEL11_12; break; \
	case 226: PIXEL00_22; PIXEL01_21; PIXEL10_12; PIXEL11_11; break; \
	case 60: PIXEL00_21; PIXEL01_11; PIXEL10_11; PIXEL11_21; break; \
	case 195: PIXEL00_11; PIXEL01_21; PIXEL10_21; PIXEL11_11; break; \
	case 102: PIXEL00_22; PIXEL01_12; PIXEL10_12; PIXEL11_22; break; \
	case 153: PIXEL00_12; PIXEL01_22; PIXEL10_22; PIXEL11_12; break; \
	case 58: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_10; else PIXEL00_70; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_10; else PIXEL01_70; PIXEL10_11; PIXEL11_21; break; \
	case 83: PIXEL00_11; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_10; else PIXEL01_70; PIXEL10_21; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_10; else PIXEL11_70; break; \
	case 92: PIXEL00_21; PIXEL01_11; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_10; else PIXEL10_70; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_10; else PIXEL11_70; break; \
	case 202: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_10; else PIXEL00_70; PIXEL01_21; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_10; else PIXEL10_70; PIXEL11_11; break; \
	case 78: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_10; else PIXEL00_70; PIXEL01_12; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_10; else PIXEL10_70; PIXEL11_22; break; \
	case 154: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_10; else PIXEL00_70; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_10; else PIXEL01_70; PIXEL10_22; PIXEL11_12; break; \
	case 114: PIXEL00_22; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_10; else PIXEL01_70; PIXEL10_12; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_10; else PIXEL11_70; break; \
	case 89: PIXEL00_12; PIXEL01_22; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_10; else PIXEL10_70; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_10; else PIXEL11_70; break; \
	case 90: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_10; else PIXEL00_70; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_10; else PIXEL01_70; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_10; else PIXEL10_70; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_10; else PIXEL11_70; break; \
	case 55: case 23: if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL00_11, PIXEL01_0; else PIXEL00_60, PIXEL01_90; PIXEL10_20; PIXEL11_21; break; \
	case 182: case 150: PIXEL00_22; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0, PIXEL11_12; else PIXEL01_90, PIXEL11_61; PIXEL10_20; break; \
	case 213: case 212: PIXEL00_20; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL01_11, PIXEL11_0; else PIXEL01_60, PIXEL11_90; PIXEL10_21; break; \
	case 241: case 240: PIXEL00_20; PIXEL01_22; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL10_12, PIXEL11_0; else PIXEL10_61, PIXEL11_90; break; \
	case 236: case 232: PIXEL00_21; PIXEL01_20; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0, PIXEL11_11; else PIXEL10_90, PIXEL11_60; break; \
	case 109: case 105: if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL00_12, PIXEL10_0; else PIXEL00_61, PIXEL10_90; PIXEL01_20; PIXEL11_22; break; \
	case 171: case 43: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0, PIXEL10_11; else PIXEL00_90, PIXEL10_60; PIXEL01_21; PIXEL11_20; break; \
	case 143: case 15: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0, PIXEL01_12; else PIXEL00_90, PIXEL01_61; PIXEL10_22; PIXEL11_20; break; \
	case 124: PIXEL00_21; PIXEL01_11; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_20; PIXEL11_10; break; \
	case 203: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_20; PIXEL01_21; PIXEL10_10; PIXEL11_11; break; \
	case 62: PIXEL00_10; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_20; PIXEL10_11; PIXEL11_21; break; \
	case 211: PIXEL00_11; PIXEL01_10; PIXEL10_21; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_20; break; \
	case 118: PIXEL00_22; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_20; PIXEL10_12; PIXEL11_10; break; \
	case 217: PIXEL00_12; PIXEL01_22; PIXEL10_10; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_20; break; \
	case 110: PIXEL00_10; PIXEL01_12; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_20; PIXEL11_22; break; \
	case 155: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_20; PIXEL01_10; PIXEL10_22; PIXEL11_12; break; \
	case 188: PIXEL00_21; PIXEL01_11; PIXEL10_11; PIXEL11_12; break; \
	case 185: PIXEL00_12; PIXEL01_22; PIXEL10_11; PIXEL11_12; break; \
	case 61: PIXEL00_12; PIXEL01_11; PIXEL10_11; PIXEL11_21; break; \
	case 157: PIXEL00_12; PIXEL01_11; PIXEL10_22; PIXEL11_12; break; \
	case 103: PIXEL00_11; PIXEL01_12; PIXEL10_12; PIXEL11_22; break; \
	case 227: PIXEL00_11; PIXEL01_21; PIXEL10_12; PIXEL11_11; break; \
	case 230: PIXEL00_22; PIXEL01_12; PIXEL10_12; PIXEL11_11; break; \
	case 199: PIXEL00_11; PIXEL01_12; PIXEL10_21; PIXEL11_11; break; \
	case 220: PIXEL00_21; PIXEL01_11; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_10; else PIXEL10_70; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_20; break; \
	case 158: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_10; else PIXEL00_70; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_20; PIXEL10_22; PIXEL11_12; break; \
	case 234: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_10; else PIXEL00_70; PIXEL01_21; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_20; PIXEL11_11; break; \
	case 242: PIXEL00_22; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_10; else PIXEL01_70; PIXEL10_12; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_20; break; \
	case 59: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_20; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_10; else PIXEL01_70; PIXEL10_11; PIXEL11_21; break; \
	case 121: PIXEL00_12; PIXEL01_22; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_20; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_10; else PIXEL11_70; break; \
	case 87: PIXEL00_11; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_20; PIXEL10_21; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_10; else PIXEL11_70; break; \
	case 79: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_20; PIXEL01_12; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_10; else PIXEL10_70; PIXEL11_22; break; \
	case 122: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_10; else PIXEL00_70; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_10; else PIXEL01_70; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_20; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_10; else PIXEL11_70; break; \
	case 94: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_10; else PIXEL00_70; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_20; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_10; else PIXEL10_70; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_10; else PIXEL11_70; break; \
	case 218: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_10; else PIXEL00_70; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_10; else PIXEL01_70; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_10; else PIXEL10_70; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_20; break; \
	case 91: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_20; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_10; else PIXEL01_70; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_10; else PIXEL10_70; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_10; else PIXEL11_70; break; \
	case 229: PIXEL00_20; PIXEL01_20; PIXEL10_12; PIXEL11_11; break; \
	case 167: PIXEL00_11; PIXEL01_12; PIXEL10_20; PIXEL11_20; break; \
	case 173: PIXEL00_12; PIXEL01_20; PIXEL10_11; PIXEL11_20; break; \
	case 181: PIXEL00_20; PIXEL01_11; PIXEL10_20; PIXEL11_12; break; \
	case 186: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_10; else PIXEL00_70; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_10; else PIXEL01_70; PIXEL10_11; PIXEL11_12; break; \
	case 115: PIXEL00_11; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_10; else PIXEL01_70; PIXEL10_12; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_10; else PIXEL11_70; break; \
	case 93: PIXEL00_12; PIXEL01_11; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_10; else PIXEL10_70; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_10; else PIXEL11_70; break; \
	case 206: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_10; else PIXEL00_70; PIXEL01_12; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_10; else PIXEL10_70; PIXEL11_11; break; \
	case 205: case 201: PIXEL00_12; PIXEL01_20; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_10; else PIXEL10_70; PIXEL11_11; break; \
	case 174: case 46: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_10; else PIXEL00_70; PIXEL01_12; PIXEL10_11; PIXEL11_20; break; \
	case 179: case 147: PIXEL00_11; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_10; else PIXEL01_70; PIXEL10_20; PIXEL11_12; break; \
	case 117: case 116: PIXEL00_20; PIXEL01_11; PIXEL10_12; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_10; else PIXEL11_70; break; \
	case 189: PIXEL00_12; PIXEL01_11; PIXEL10_11; PIXEL11_12; break; \
	case 231: PIXEL00_11; PIXEL01_12; PIXEL10_12; PIXEL11_11; break; \
	case 126: PIXEL00_10; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_20; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_20; PIXEL11_10; break; \
	case 219: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_20; PIXEL01_10; PIXEL10_10; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_20; break; \
	case 125: if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL00_12, PIXEL10_0; else PIXEL00_61, PIXEL10_90; PIXEL01_11; PIXEL11_10; break; \
	case 221: PIXEL00_12; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL01_11, PIXEL11_0; else PIXEL01_60, PIXEL11_90; PIXEL10_10; break; \
	case 207: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0, PIXEL01_12; else PIXEL00_90, PIXEL01_61; PIXEL10_10; PIXEL11_11; break; \
	case 238: PIXEL00_10; PIXEL01_12; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0, PIXEL11_11; else PIXEL10_90, PIXEL11_60; break; \
	case 190: PIXEL00_10; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0, PIXEL11_12; else PIXEL01_90, PIXEL11_61; PIXEL10_11; break; \
	case 187: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0, PIXEL10_11; else PIXEL00_90, PIXEL10_60; PIXEL01_10; PIXEL11_12; break; \
	case 243: PIXEL00_11; PIXEL01_10; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL10_12, PIXEL11_0; else PIXEL10_61, PIXEL11_90; break; \
	case 119: if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL00_11, PIXEL01_0; else PIXEL00_60, PIXEL01_90; PIXEL10_12; PIXEL11_10; break; \
	case 237: case 233: PIXEL00_12; PIXEL01_20; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_100; PIXEL11_11; break; \
	case 175: case 47: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_100; PIXEL01_12; PIXEL10_11; PIXEL11_20; break; \
	case 183: case 151: PIXEL00_11; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_100; PIXEL10_20; PIXEL11_12; break; \
	case 245: case 244: PIXEL00_20; PIXEL01_11; PIXEL10_12; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_100; break; \
	case 250: PIXEL00_10; PIXEL01_10; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_20; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_20; break; \
	case 123: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_20; PIXEL01_10; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_20; PIXEL11_10; break; \
	case 95: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_20; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_20; PIXEL10_10; PIXEL11_10; break; \
	case 222: PIXEL00_10; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_20; PIXEL10_10; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_20; break; \
	case 252: PIXEL00_21; PIXEL01_11; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_20; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_100; break; \
	case 249: PIXEL00_12; PIXEL01_22; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_100; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_20; break; \
	case 235: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_20; PIXEL01_21; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_100; PIXEL11_11; break; \
	case 111: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_100; PIXEL01_12; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_20; PIXEL11_22; break; \
	case 63: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_100; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_20; PIXEL10_11; PIXEL11_21; break; \
	case 159: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_20; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_100; PIXEL10_22; PIXEL11_12; break; \
	case 215: PIXEL00_11; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_100; PIXEL10_21; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_20; break; \
	case 246: PIXEL00_22; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_20; PIXEL10_12; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_100; break; \
	case 254: PIXEL00_10; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_20; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_20; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_100; break; \
	case 253: PIXEL00_12; PIXEL01_11; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_100; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_100; break; \
	case 251: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_20; PIXEL01_10; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_100; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_20; break; \
	case 239: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_100; PIXEL01_12; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_100; PIXEL11_11; break; \
	case 127: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_100; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_20; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_20; PIXEL11_10; break; \
	case 191: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_100; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_100; PIXEL10_11; PIXEL11_12; break; \
	case 223: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_20; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_100; PIXEL10_10; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_20; break; \
	case 247: PIXEL00_11; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_100; PIXEL10_12; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_100; break; \
	case 255: if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) PIXEL00_0; else PIXEL00_100; if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) PIXEL01_0; else PIXEL01_100; if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) PIXEL10_0; else PIXEL10_100; if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) PIXEL11_0; else PIXEL11_100; break;


void RenderHQ2X(unsigned char *src, unsigned int srcpitch, unsigned char *dst, unsigned int dstpitch, int nWidth, int nHeight, int GuiScale)
{
	uint8 *srcPtr = src;
	uint8 *dstPtr = dst;
	uint32 srcPitch = srcpitch;
	uint32 dstPitch = dstpitch;
	int width = nWidth;
	int height = nHeight;

	int	w1, w2, w3, w4, w5, w6, w7, w8, w9;

	uint32	src1line = srcPitch >> 1;
	uint32	dst1line = dstPitch >> 1;
	uint16	*sp = (uint16 *) srcPtr;
	uint16	*dp = (uint16 *) dstPtr;

	const int* RGBtoYUVtable = RGBtoYUV;

	uint32  pattern;
	int		l, y;

	for (int h = 0; h < height; h++)
	{
    	uint16 * sp0 = sp - src1line;
	    if (h == 0 && sp0 < (uint16 *) srcPtr)
	          sp0 = sp;

		sp--;
		sp0--;

		w1 = *(sp0);
		w4 = *(sp);
		w7 = *(sp + src1line);

		sp++;
		sp0++;

		w2 = *(sp0);
		w5 = *(sp);
		w8 = *(sp + src1line);

		for (l = width; l; l--)
		{
			sp++;
			sp0++;

			w3 = *(sp0);
			w6 = *(sp);
			w9 = *(sp + src1line);

			pattern = 0;

			switch(GuiScale)
			{
			case 0: {
				const uint16 avg = (RGBtoBright[w1] + RGBtoBright[w2] + RGBtoBright[w3] + RGBtoBright[w4] + RGBtoBright[w5] + RGBtoBright[w6] + RGBtoBright[w7] + RGBtoBright[w8] + RGBtoBright[w9]) / 9;
				UINT8 diff5 = RGBtoBright[w5] > avg;
				if ((w1 != w5) && ((RGBtoBright[w1] > avg) != diff5)) pattern |= (1 << 0);
				if ((w2 != w5) && ((RGBtoBright[w2] > avg) != diff5)) pattern |= (1 << 1);
				if ((w3 != w5) && ((RGBtoBright[w3] > avg) != diff5)) pattern |= (1 << 2);
				if ((w4 != w5) && ((RGBtoBright[w4] > avg) != diff5)) pattern |= (1 << 3);
				if ((w6 != w5) && ((RGBtoBright[w6] > avg) != diff5)) pattern |= (1 << 4);
				if ((w7 != w5) && ((RGBtoBright[w7] > avg) != diff5)) pattern |= (1 << 5);
				if ((w8 != w5) && ((RGBtoBright[w8] > avg) != diff5)) pattern |= (1 << 6);
				if ((w9 != w5) && ((RGBtoBright[w9] > avg) != diff5)) pattern |= (1 << 7);
              }  break;

			case 1: {
				UINT8 nosame = true;
				if(w1 == w5 || w3 == w5 || w7 == w5 || w9 == w5)
					nosame = false;

				if(nosame)
				{
					const uint16 avg = (RGBtoBright[w1] + RGBtoBright[w2] + RGBtoBright[w3] + RGBtoBright[w4] + RGBtoBright[w5] + RGBtoBright[w6] + RGBtoBright[w7] + RGBtoBright[w8] + RGBtoBright[w9]) / 9;
					UINT8 diff5 = RGBtoBright[w5] > avg;
					if((RGBtoBright[w1] > avg) != diff5) pattern |= (1 << 0);
					if((RGBtoBright[w2] > avg) != diff5) pattern |= (1 << 1);
					if((RGBtoBright[w3] > avg) != diff5) pattern |= (1 << 2);
					if((RGBtoBright[w4] > avg) != diff5) pattern |= (1 << 3);
					if((RGBtoBright[w6] > avg) != diff5) pattern |= (1 << 4);
					if((RGBtoBright[w7] > avg) != diff5) pattern |= (1 << 5);
					if((RGBtoBright[w8] > avg) != diff5) pattern |= (1 << 6);
					if((RGBtoBright[w9] > avg) != diff5) pattern |= (1 << 7);
				}
				else
				{
					y = RGBtoYUV[w5];
					if ((w1 != w5) && (Diff(y, RGBtoYUV[w1]))) pattern |= (1 << 0);
					if ((w2 != w5) && (Diff(y, RGBtoYUV[w2]))) pattern |= (1 << 1);
					if ((w3 != w5) && (Diff(y, RGBtoYUV[w3]))) pattern |= (1 << 2);
					if ((w4 != w5) && (Diff(y, RGBtoYUV[w4]))) pattern |= (1 << 3);
					if ((w6 != w5) && (Diff(y, RGBtoYUV[w6]))) pattern |= (1 << 4);
					if ((w7 != w5) && (Diff(y, RGBtoYUV[w7]))) pattern |= (1 << 5);
					if ((w8 != w5) && (Diff(y, RGBtoYUV[w8]))) pattern |= (1 << 6);
					if ((w9 != w5) && (Diff(y, RGBtoYUV[w9]))) pattern |= (1 << 7);
				}
              }  break;
	        default:
            case 2:
				y = RGBtoYUVtable[w5];
				if ((w1 != w5) && (Diff(y, RGBtoYUVtable[w1]))) pattern |= (1 << 0);
				if ((w2 != w5) && (Diff(y, RGBtoYUVtable[w2]))) pattern |= (1 << 1);
				if ((w3 != w5) && (Diff(y, RGBtoYUVtable[w3]))) pattern |= (1 << 2);
				if ((w4 != w5) && (Diff(y, RGBtoYUVtable[w4]))) pattern |= (1 << 3);
				if ((w6 != w5) && (Diff(y, RGBtoYUVtable[w6]))) pattern |= (1 << 4);
				if ((w7 != w5) && (Diff(y, RGBtoYUVtable[w7]))) pattern |= (1 << 5);
				if ((w8 != w5) && (Diff(y, RGBtoYUVtable[w8]))) pattern |= (1 << 6);
				if ((w9 != w5) && (Diff(y, RGBtoYUVtable[w9]))) pattern |= (1 << 7);
                break;
			}

			switch (pattern)
			{
				HQ2XCASES
			}

			w1 = w2; w4 = w5; w7 = w8;
			w2 = w3; w5 = w6; w8 = w9;

			dp += 2;
		}

		dp += ((dst1line - width) << 1);
		sp +=  (src1line - width);
	}
}














#define PIXEL00_1M  *(dp) = Interp01(w5, w1);
#define PIXEL00_1U  *(dp) = Interp01(w5, w2);
#define PIXEL00_1L  *(dp) = Interp01(w5, w4);
#define PIXEL00_2   *(dp) = Interp02(w5, w4, w2);
#define PIXEL00_4   *(dp) = Interp04(w5, w4, w2);
#define PIXEL00_5   *(dp) = Interp05(w4, w2);
#define PIXEL00_C   *(dp) = w5;

#define PIXEL01_1   *(dp + 1) = Interp01(w5, w2);
#define PIXEL01_3   *(dp + 1) = Interp03(w5, w2);
#define PIXEL01_6   *(dp + 1) = Interp01(w2, w5);
#define PIXEL01_C   *(dp + 1) = w5;

#define PIXEL02_1M  *(dp + 2) = Interp01(w5, w3);
#define PIXEL02_1U  *(dp + 2) = Interp01(w5, w2);
#define PIXEL02_1R  *(dp + 2) = Interp01(w5, w6);
#define PIXEL02_2   *(dp + 2) = Interp02(w5, w2, w6);
#define PIXEL02_4   *(dp + 2) = Interp04(w5, w2, w6);
#define PIXEL02_5   *(dp + 2) = Interp05(w2, w6);
#define PIXEL02_C   *(dp + 2) = w5;

#define PIXEL10_1   *(dp + dst1line) = Interp01(w5, w4);
#define PIXEL10_3   *(dp + dst1line) = Interp03(w5, w4);
#define PIXEL10_6   *(dp + dst1line) = Interp01(w4, w5);
#define PIXEL10_C   *(dp + dst1line) = w5;

#define PIXEL11     *(dp + dst1line + 1) = w5;

#define PIXEL12_1   *(dp + dst1line + 2) = Interp01(w5, w6);
#define PIXEL12_3   *(dp + dst1line + 2) = Interp03(w5, w6);
#define PIXEL12_6   *(dp + dst1line + 2) = Interp01(w6, w5);
#define PIXEL12_C   *(dp + dst1line + 2) = w5;

#define PIXEL20_1M  *(dp + dst1line + dst1line) = Interp01(w5, w7);
#define PIXEL20_1D  *(dp + dst1line + dst1line) = Interp01(w5, w8);
#define PIXEL20_1L  *(dp + dst1line + dst1line) = Interp01(w5, w4);
#define PIXEL20_2   *(dp + dst1line + dst1line) = Interp02(w5, w8, w4);
#define PIXEL20_4   *(dp + dst1line + dst1line) = Interp04(w5, w8, w4);
#define PIXEL20_5   *(dp + dst1line + dst1line) = Interp05(w8, w4);
#define PIXEL20_C   *(dp + dst1line + dst1line) = w5;

#define PIXEL21_1   *(dp + dst1line + dst1line + 1) = Interp01(w5, w8);
#define PIXEL21_3   *(dp + dst1line + dst1line + 1) = Interp03(w5, w8);
#define PIXEL21_6   *(dp + dst1line + dst1line + 1) = Interp01(w8, w5);
#define PIXEL21_C   *(dp + dst1line + dst1line + 1) = w5;

#define PIXEL22_1M  *(dp + dst1line + dst1line + 2) = Interp01(w5, w9);
#define PIXEL22_1D  *(dp + dst1line + dst1line + 2) = Interp01(w5, w8);
#define PIXEL22_1R  *(dp + dst1line + dst1line + 2) = Interp01(w5, w6);
#define PIXEL22_2   *(dp + dst1line + dst1line + 2) = Interp02(w5, w6, w8);
#define PIXEL22_4   *(dp + dst1line + dst1line + 2) = Interp04(w5, w6, w8);
#define PIXEL22_5   *(dp + dst1line + dst1line + 2) = Interp05(w6, w8);
#define PIXEL22_C   *(dp + dst1line + dst1line + 2) = w5;

#define Interp03(c1, c2) \
	(((c1 == c2) ? c1 : \
	((((((c1) & Mask_2) *  7 + ((c2) & Mask_2)) >> 3) & Mask_2) + \
	(((((c1) & Mask13) *  7 + ((c2) & Mask13)) >> 3) & Mask13))))

#define Interp04(c1, c2, c3) \
	((((((c1) & Mask_2) *  2 + ((c2) & Mask_2) * 7 + ((c3) & Mask_2) * 7) >> 4) & Mask_2) + \
	(((((c1) & Mask13) *  2 + ((c2) & Mask13) * 7 + ((c3) & Mask13) * 7) >> 4) & Mask13))

#define HQ3XCASES \
	case 0: case 1: case 4: case 32: case 128: case 5: case 132: case 160: case 33: case 129: case 36: case 133: case 164: case 161: case 37: case 165: { PIXEL00_2 PIXEL01_1 PIXEL02_2 PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_2 PIXEL21_1 PIXEL22_2 break; }\
	case 2: case 34: case 130: case 162: { PIXEL00_1M PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_2 PIXEL21_1 PIXEL22_2 break; }\
	case 16: case 17: case 48: case 49: { PIXEL00_2 PIXEL01_1 PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_2 PIXEL21_1 PIXEL22_1M break; }\
	case 64: case 65: case 68: case 69: { PIXEL00_2 PIXEL01_1 PIXEL02_2 PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C PIXEL22_1M break; }\
	case 8: case 12: case 136: case 140: { PIXEL00_1M PIXEL01_1 PIXEL02_2 PIXEL10_C PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_1 PIXEL22_2 break; }\
	case 3: case 35: case 131: case 163: { PIXEL00_1L PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_2 PIXEL21_1 PIXEL22_2 break; }\
	case 6: case 38: case 134: case 166: { PIXEL00_1M PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_2 PIXEL21_1 PIXEL22_2 break; }\
	case 20: case 21: case 52: case 53: { PIXEL00_2 PIXEL01_1 PIXEL02_1U PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_2 PIXEL21_1 PIXEL22_1M break; }\
	case 144: case 145: case 176: case 177: { PIXEL00_2 PIXEL01_1 PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_2 PIXEL21_1 PIXEL22_1D break; }\
	case 192: case 193: case 196: case 197: { PIXEL00_2 PIXEL01_1 PIXEL02_2 PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C PIXEL22_1R break; }\
	case 96: case 97: case 100: case 101: { PIXEL00_2 PIXEL01_1 PIXEL02_2 PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C PIXEL22_1M break; }\
	case 40: case 44: case 168: case 172: { PIXEL00_1M PIXEL01_1 PIXEL02_2 PIXEL10_C PIXEL11 PIXEL12_1 PIXEL20_1D PIXEL21_1 PIXEL22_2 break; }\
	case 9: case 13: case 137: case 141: { PIXEL00_1U PIXEL01_1 PIXEL02_2 PIXEL10_C PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_1 PIXEL22_2 break; }\
	case 18: case 50: { PIXEL00_1M if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL01_C PIXEL02_1M PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 } PIXEL10_1 PIXEL11 PIXEL20_2 PIXEL21_1 PIXEL22_1M break; }\
	case 80: case 81: { PIXEL00_2 PIXEL01_1 PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL20_1M if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL12_C PIXEL21_C PIXEL22_1M } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 } break; }\
	case 72: case 76: { PIXEL00_1M PIXEL01_1 PIXEL02_2 PIXEL11 PIXEL12_1 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL10_C PIXEL20_1M PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 } PIXEL22_1M break; }\
	case 10: case 138: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_1M PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 } PIXEL02_1M PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_1 PIXEL22_2 break; }\
	case 66: { PIXEL00_1M PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C PIXEL22_1M break; }\
	case 24: { PIXEL00_1M PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1 PIXEL22_1M break; }\
	case 7: case 39: case 135: { PIXEL00_1L PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_2 PIXEL21_1 PIXEL22_2 break; }\
	case 148: case 149: case 180: { PIXEL00_2 PIXEL01_1 PIXEL02_1U PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_2 PIXEL21_1 PIXEL22_1D break; }\
	case 224: case 228: case 225: { PIXEL00_2 PIXEL01_1 PIXEL02_2 PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C PIXEL22_1R break; }\
	case 41: case 169: case 45: { PIXEL00_1U PIXEL01_1 PIXEL02_2 PIXEL10_C PIXEL11 PIXEL12_1 PIXEL20_1D PIXEL21_1 PIXEL22_2 break; }\
	case 22: case 54: { PIXEL00_1M if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 } PIXEL10_1 PIXEL11 PIXEL20_2 PIXEL21_1 PIXEL22_1M break; }\
	case 208: case 209: { PIXEL00_2 PIXEL01_1 PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL20_1M if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 } break; }\
	case 104: case 108: { PIXEL00_1M PIXEL01_1 PIXEL02_2 PIXEL11 PIXEL12_1 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 } PIXEL22_1M break; }\
	case 11: case 139: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 } PIXEL02_1M PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_1 PIXEL22_2 break; }\
	case 19: case 51: { if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL00_1L PIXEL01_C PIXEL02_1M PIXEL12_C } else { PIXEL00_2 PIXEL01_6 PIXEL02_5 PIXEL12_1 } PIXEL10_1 PIXEL11 PIXEL20_2 PIXEL21_1 PIXEL22_1M break; }\
	case 146: case 178: { if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL01_C PIXEL02_1M PIXEL12_C PIXEL22_1D } else { PIXEL01_1 PIXEL02_5 PIXEL12_6 PIXEL22_2 } PIXEL00_1M PIXEL10_1 PIXEL11 PIXEL20_2 PIXEL21_1 break; }\
	case 84: case 85: { if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL02_1U PIXEL12_C PIXEL21_C PIXEL22_1M } else { PIXEL02_2 PIXEL12_6 PIXEL21_1 PIXEL22_5 } PIXEL00_2 PIXEL01_1 PIXEL10_1 PIXEL11 PIXEL20_1M break; }\
	case 112: case 113: { if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL12_C PIXEL20_1L PIXEL21_C PIXEL22_1M } else { PIXEL12_1 PIXEL20_2 PIXEL21_6 PIXEL22_5 } PIXEL00_2 PIXEL01_1 PIXEL02_1M PIXEL10_1 PIXEL11 break; }\
	case 200: case 204: { if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL10_C PIXEL20_1M PIXEL21_C PIXEL22_1R } else { PIXEL10_1 PIXEL20_5 PIXEL21_6 PIXEL22_2 } PIXEL00_1M PIXEL01_1 PIXEL02_2 PIXEL11 PIXEL12_1 break; }\
	case 73: case 77: { if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL00_1U PIXEL10_C PIXEL20_1M PIXEL21_C } else { PIXEL00_2 PIXEL10_6 PIXEL20_5 PIXEL21_1 } PIXEL01_1 PIXEL02_2 PIXEL11 PIXEL12_1 PIXEL22_1M break; }\
	case 42: case 170: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_1M PIXEL01_C PIXEL10_C PIXEL20_1D } else { PIXEL00_5 PIXEL01_1 PIXEL10_6 PIXEL20_2 } PIXEL02_1M PIXEL11 PIXEL12_1 PIXEL21_1 PIXEL22_2 break; }\
	case 14: case 142: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_1M PIXEL01_C PIXEL02_1R PIXEL10_C } else { PIXEL00_5 PIXEL01_6 PIXEL02_2 PIXEL10_1 } PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_1 PIXEL22_2 break; }\
	case 67: { PIXEL00_1L PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C PIXEL22_1M break; }\
	case 70: { PIXEL00_1M PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C PIXEL22_1M break; }\
	case 28: { PIXEL00_1M PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1 PIXEL22_1M break; }\
	case 152: { PIXEL00_1M PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1 PIXEL22_1D break; }\
	case 194: { PIXEL00_1M PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C PIXEL22_1R break; }\
	case 98: { PIXEL00_1M PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C PIXEL22_1M break; }\
	case 56: { PIXEL00_1M PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1 PIXEL22_1M break; }\
	case 25: { PIXEL00_1U PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1 PIXEL22_1M break; }\
	case 26: case 31: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL10_C } else { PIXEL00_4 PIXEL10_3 } PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_C PIXEL12_C } else { PIXEL02_4 PIXEL12_3 } PIXEL11 PIXEL20_1M PIXEL21_1 PIXEL22_1M break; }\
	case 82: case 214: { PIXEL00_1M if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL01_C PIXEL02_C } else { PIXEL01_3 PIXEL02_4 } PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_1M if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL21_C PIXEL22_C } else { PIXEL21_3 PIXEL22_4 } break; }\
	case 88: case 248: { PIXEL00_1M PIXEL01_1 PIXEL02_1M PIXEL11 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL10_C PIXEL20_C } else { PIXEL10_3 PIXEL20_4 } PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL12_C PIXEL22_C } else { PIXEL12_3 PIXEL22_4 } break; }\
	case 74: case 107: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL01_C } else { PIXEL00_4 PIXEL01_3 } PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_1 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_C PIXEL21_C } else { PIXEL20_4 PIXEL21_3 } PIXEL22_1M break; }\
	case 27: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 } PIXEL02_1M PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1 PIXEL22_1M break; }\
	case 86: { PIXEL00_1M if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 } PIXEL10_1 PIXEL11 PIXEL20_1M PIXEL21_C PIXEL22_1M break; }\
	case 216: { PIXEL00_1M PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL20_1M if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 } break; }\
	case 106: { PIXEL00_1M PIXEL01_C PIXEL02_1M PIXEL11 PIXEL12_1 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 } PIXEL22_1M break; }\
	case 30: { PIXEL00_1M if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 } PIXEL10_C PIXEL11 PIXEL20_1M PIXEL21_1 PIXEL22_1M break; }\
	case 210: { PIXEL00_1M PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL20_1M if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 } break; }\
	case 120: { PIXEL00_1M PIXEL01_1 PIXEL02_1M PIXEL11 PIXEL12_C if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 } PIXEL22_1M break; }\
	case 75: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 } PIXEL02_1M PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C PIXEL22_1M break; }\
	case 29: { PIXEL00_1U PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1 PIXEL22_1M break; }\
	case 198: { PIXEL00_1M PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C PIXEL22_1R break; }\
	case 184: { PIXEL00_1M PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1 PIXEL22_1D break; }\
	case 99: { PIXEL00_1L PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C PIXEL22_1M break; }\
	case 57: { PIXEL00_1U PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1 PIXEL22_1M break; }\
	case 71: { PIXEL00_1L PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C PIXEL22_1M break; }\
	case 156: { PIXEL00_1M PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1 PIXEL22_1D break; }\
	case 226: { PIXEL00_1M PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C PIXEL22_1R break; }\
	case 60: { PIXEL00_1M PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1 PIXEL22_1M break; }\
	case 195: { PIXEL00_1L PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C PIXEL22_1R break; }\
	case 102: { PIXEL00_1M PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C PIXEL22_1M break; }\
	case 153: { PIXEL00_1U PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1 PIXEL22_1D break; }\
	case 58: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1 PIXEL22_1M break; }\
	case 83: { PIXEL00_1L PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL22_1M } else { PIXEL22_2 } break; }\
	case 92: { PIXEL00_1M PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL22_1M } else { PIXEL22_2 } break; }\
	case 202: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_1 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C PIXEL22_1R break; }\
	case 78: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C PIXEL02_1R PIXEL10_C PIXEL11 PIXEL12_1 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C PIXEL22_1M break; }\
	case 154: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1 PIXEL22_1D break; }\
	case 114: { PIXEL00_1M PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_1L PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL22_1M } else { PIXEL22_2 } break; }\
	case 89: { PIXEL00_1U PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_C if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL22_1M } else { PIXEL22_2 } break; }\
	case 90: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_C PIXEL11 PIXEL12_C if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL22_1M } else { PIXEL22_2 } break; }\
	case 55: case 23: { if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL00_1L PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL00_2 PIXEL01_6 PIXEL02_5 PIXEL12_1 } PIXEL10_1 PIXEL11 PIXEL20_2 PIXEL21_1 PIXEL22_1M break; }\
	case 182: case 150: { if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL01_C PIXEL02_C PIXEL12_C PIXEL22_1D } else { PIXEL01_1 PIXEL02_5 PIXEL12_6 PIXEL22_2 } PIXEL00_1M PIXEL10_1 PIXEL11 PIXEL20_2 PIXEL21_1 break; }\
	case 213: case 212: { if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL02_1U PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL02_2 PIXEL12_6 PIXEL21_1 PIXEL22_5 } PIXEL00_2 PIXEL01_1 PIXEL10_1 PIXEL11 PIXEL20_1M break; }\
	case 241: case 240: { if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL12_C PIXEL20_1L PIXEL21_C PIXEL22_C } else { PIXEL12_1 PIXEL20_2 PIXEL21_6 PIXEL22_5 } PIXEL00_2 PIXEL01_1 PIXEL02_1M PIXEL10_1 PIXEL11 break; }\
	case 236: case 232: { if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL10_C PIXEL20_C PIXEL21_C PIXEL22_1R } else { PIXEL10_1 PIXEL20_5 PIXEL21_6 PIXEL22_2 } PIXEL00_1M PIXEL01_1 PIXEL02_2 PIXEL11 PIXEL12_1 break; }\
	case 109: case 105: { if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL00_1U PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL00_2 PIXEL10_6 PIXEL20_5 PIXEL21_1 } PIXEL01_1 PIXEL02_2 PIXEL11 PIXEL12_1 PIXEL22_1M break; }\
	case 171: case 43: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL01_C PIXEL10_C PIXEL20_1D } else { PIXEL00_5 PIXEL01_1 PIXEL10_6 PIXEL20_2 } PIXEL02_1M PIXEL11 PIXEL12_1 PIXEL21_1 PIXEL22_2 break; }\
	case 143: case 15: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL01_C PIXEL02_1R PIXEL10_C } else { PIXEL00_5 PIXEL01_6 PIXEL02_2 PIXEL10_1 } PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_1 PIXEL22_2 break; }\
	case 124: { PIXEL00_1M PIXEL01_1 PIXEL02_1U PIXEL11 PIXEL12_C if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 } PIXEL22_1M break; }\
	case 203: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 } PIXEL02_1M PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C PIXEL22_1R break; }\
	case 62: { PIXEL00_1M if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 } PIXEL10_C PIXEL11 PIXEL20_1D PIXEL21_1 PIXEL22_1M break; }\
	case 211: { PIXEL00_1L PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL20_1M if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 } break; }\
	case 118: { PIXEL00_1M if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 } PIXEL10_1 PIXEL11 PIXEL20_1L PIXEL21_C PIXEL22_1M break; }\
	case 217: { PIXEL00_1U PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL20_1M if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 } break; }\
	case 110: { PIXEL00_1M PIXEL01_C PIXEL02_1R PIXEL11 PIXEL12_1 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 } PIXEL22_1M break; }\
	case 155: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 } PIXEL02_1M PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1 PIXEL22_1D break; }\
	case 188: { PIXEL00_1M PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1 PIXEL22_1D break; }\
	case 185: { PIXEL00_1U PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1 PIXEL22_1D break; }\
	case 61: { PIXEL00_1U PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1 PIXEL22_1M break; }\
	case 157: { PIXEL00_1U PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1 PIXEL22_1D break; }\
	case 103: { PIXEL00_1L PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C PIXEL22_1M break; }\
	case 227: { PIXEL00_1L PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C PIXEL22_1R break; }\
	case 230: { PIXEL00_1M PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C PIXEL22_1R break; }\
	case 199: { PIXEL00_1L PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C PIXEL22_1R break; }\
	case 220: { PIXEL00_1M PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_1M } else { PIXEL20_2 } if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 } break; }\
	case 158: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_1M } else { PIXEL00_2 } if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 } PIXEL10_C PIXEL11 PIXEL20_1M PIXEL21_1 PIXEL22_1D break; }\
	case 234: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C PIXEL02_1M PIXEL11 PIXEL12_1 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 } PIXEL22_1R break; }\
	case 242: { PIXEL00_1M PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_1 PIXEL11 PIXEL20_1L if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 } break; }\
	case 59: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 } if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_1M } else { PIXEL02_2 } PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1 PIXEL22_1M break; }\
	case 121: { PIXEL00_1U PIXEL01_1 PIXEL02_1M PIXEL11 PIXEL12_C if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 } if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL22_1M } else { PIXEL22_2 } break; }\
	case 87: { PIXEL00_1L if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 } PIXEL10_1 PIXEL11 PIXEL20_1M PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL22_1M } else { PIXEL22_2 } break; }\
	case 79: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 } PIXEL02_1R PIXEL11 PIXEL12_1 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C PIXEL22_1M break; }\
	case 122: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_1M } else { PIXEL02_2 } PIXEL11 PIXEL12_C if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 } if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL22_1M } else { PIXEL22_2 } break; }\
	case 94: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_1M } else { PIXEL00_2 } if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 } PIXEL10_C PIXEL11 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL22_1M } else { PIXEL22_2 } break; }\
	case 218: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_C PIXEL11 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_1M } else { PIXEL20_2 } if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 } break; }\
	case 91: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 } if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_1M } else { PIXEL02_2 } PIXEL11 PIXEL12_C if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL22_1M } else { PIXEL22_2 } break; }\
	case 229: { PIXEL00_2 PIXEL01_1 PIXEL02_2 PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C PIXEL22_1R break; }\
	case 167: { PIXEL00_1L PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_2 PIXEL21_1 PIXEL22_2 break; }\
	case 173: { PIXEL00_1U PIXEL01_1 PIXEL02_2 PIXEL10_C PIXEL11 PIXEL12_1 PIXEL20_1D PIXEL21_1 PIXEL22_2 break; }\
	case 181: { PIXEL00_2 PIXEL01_1 PIXEL02_1U PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_2 PIXEL21_1 PIXEL22_1D break; }\
	case 186: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1 PIXEL22_1D break; }\
	case 115: { PIXEL00_1L PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_1L PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL22_1M } else { PIXEL22_2 } break; }\
	case 93: { PIXEL00_1U PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL22_1M } else { PIXEL22_2 } break; }\
	case 206: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C PIXEL02_1R PIXEL10_C PIXEL11 PIXEL12_1 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C PIXEL22_1R break; }\
	case 205: case 201: { PIXEL00_1U PIXEL01_1 PIXEL02_2 PIXEL10_C PIXEL11 PIXEL12_1 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_1M } else { PIXEL20_2 } PIXEL21_C PIXEL22_1R break; }\
	case 174: case 46: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_1M } else { PIXEL00_2 } PIXEL01_C PIXEL02_1R PIXEL10_C PIXEL11 PIXEL12_1 PIXEL20_1D PIXEL21_1 PIXEL22_2 break; }\
	case 179: case 147: { PIXEL00_1L PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_1M } else { PIXEL02_2 } PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_2 PIXEL21_1 PIXEL22_1D break; }\
	case 117: case 116: { PIXEL00_2 PIXEL01_1 PIXEL02_1U PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_1L PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL22_1M } else { PIXEL22_2 } break; }\
	case 189: { PIXEL00_1U PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1 PIXEL22_1D break; }\
	case 231: { PIXEL00_1L PIXEL01_C PIXEL02_1R PIXEL10_1 PIXEL11 PIXEL12_1 PIXEL20_1L PIXEL21_C PIXEL22_1R break; }\
	case 126: { PIXEL00_1M if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_4 PIXEL12_3 } PIXEL11 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_4 PIXEL21_3 } PIXEL22_1M break; }\
	case 219: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_4 PIXEL01_3 PIXEL10_3 } PIXEL02_1M PIXEL11 PIXEL20_1M if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_4 } break; }\
	case 125: { if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL00_1U PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL00_2 PIXEL10_6 PIXEL20_5 PIXEL21_1 } PIXEL01_1 PIXEL02_1U PIXEL11 PIXEL12_C PIXEL22_1M break; }\
	case 221: { if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL02_1U PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL02_2 PIXEL12_6 PIXEL21_1 PIXEL22_5 } PIXEL00_1U PIXEL01_1 PIXEL10_C PIXEL11 PIXEL20_1M break; }\
	case 207: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL01_C PIXEL02_1R PIXEL10_C } else { PIXEL00_5 PIXEL01_6 PIXEL02_2 PIXEL10_1 } PIXEL11 PIXEL12_1 PIXEL20_1M PIXEL21_C PIXEL22_1R break; }\
	case 238: { if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL10_C PIXEL20_C PIXEL21_C PIXEL22_1R } else { PIXEL10_1 PIXEL20_5 PIXEL21_6 PIXEL22_2 } PIXEL00_1M PIXEL01_C PIXEL02_1R PIXEL11 PIXEL12_1 break; }\
	case 190: { if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL01_C PIXEL02_C PIXEL12_C PIXEL22_1D } else { PIXEL01_1 PIXEL02_5 PIXEL12_6 PIXEL22_2 } PIXEL00_1M PIXEL10_C PIXEL11 PIXEL20_1D PIXEL21_1 break; }\
	case 187: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL01_C PIXEL10_C PIXEL20_1D } else { PIXEL00_5 PIXEL01_1 PIXEL10_6 PIXEL20_2 } PIXEL02_1M PIXEL11 PIXEL12_C PIXEL21_1 PIXEL22_1D break; }\
	case 243: { if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL12_C PIXEL20_1L PIXEL21_C PIXEL22_C } else { PIXEL12_1 PIXEL20_2 PIXEL21_6 PIXEL22_5 } PIXEL00_1L PIXEL01_C PIXEL02_1M PIXEL10_1 PIXEL11 break; }\
	case 119: { if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL00_1L PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL00_2 PIXEL01_6 PIXEL02_5 PIXEL12_1 } PIXEL10_1 PIXEL11 PIXEL20_1L PIXEL21_C PIXEL22_1M break; }\
	case 237: case 233: { PIXEL00_1U PIXEL01_1 PIXEL02_2 PIXEL10_C PIXEL11 PIXEL12_1 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_C } else { PIXEL20_2 } PIXEL21_C PIXEL22_1R break; }\
	case 175: case 47: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C } else { PIXEL00_2 } PIXEL01_C PIXEL02_1R PIXEL10_C PIXEL11 PIXEL12_1 PIXEL20_1D PIXEL21_1 PIXEL22_2 break; }\
	case 183: case 151: { PIXEL00_1L PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_C } else { PIXEL02_2 } PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_2 PIXEL21_1 PIXEL22_1D break; }\
	case 245: case 244: { PIXEL00_2 PIXEL01_1 PIXEL02_1U PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_1L PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL22_C } else { PIXEL22_2 } break; }\
	case 250: { PIXEL00_1M PIXEL01_C PIXEL02_1M PIXEL11 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL10_C PIXEL20_C } else { PIXEL10_3 PIXEL20_4 } PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL12_C PIXEL22_C } else { PIXEL12_3 PIXEL22_4 } break; }\
	case 123: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL01_C } else { PIXEL00_4 PIXEL01_3 } PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_C if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_C PIXEL21_C } else { PIXEL20_4 PIXEL21_3 } PIXEL22_1M break; }\
	case 95: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL10_C } else { PIXEL00_4 PIXEL10_3 } PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_C PIXEL12_C } else { PIXEL02_4 PIXEL12_3 } PIXEL11 PIXEL20_1M PIXEL21_C PIXEL22_1M break; }\
	case 222: { PIXEL00_1M if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL01_C PIXEL02_C } else { PIXEL01_3 PIXEL02_4 } PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1M if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL21_C PIXEL22_C } else { PIXEL21_3 PIXEL22_4 } break; }\
	case 252: { PIXEL00_1M PIXEL01_1 PIXEL02_1U PIXEL11 PIXEL12_C if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL10_C PIXEL20_C } else { PIXEL10_3 PIXEL20_4 } PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL22_C } else { PIXEL22_2 } break; }\
	case 249: { PIXEL00_1U PIXEL01_1 PIXEL02_1M PIXEL10_C PIXEL11 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_C } else { PIXEL20_2 } PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL12_C PIXEL22_C } else { PIXEL12_3 PIXEL22_4 } break; }\
	case 235: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL01_C } else { PIXEL00_4 PIXEL01_3 } PIXEL02_1M PIXEL10_C PIXEL11 PIXEL12_1 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_C } else { PIXEL20_2 } PIXEL21_C PIXEL22_1R break; }\
	case 111: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C } else { PIXEL00_2 } PIXEL01_C PIXEL02_1R PIXEL10_C PIXEL11 PIXEL12_1 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_C PIXEL21_C } else { PIXEL20_4 PIXEL21_3 } PIXEL22_1M break; }\
	case 63: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C } else { PIXEL00_2 } PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_C PIXEL12_C } else { PIXEL02_4 PIXEL12_3 } PIXEL10_C PIXEL11 PIXEL20_1D PIXEL21_1 PIXEL22_1M break; }\
	case 159: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL10_C } else { PIXEL00_4 PIXEL10_3 } PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_C } else { PIXEL02_2 } PIXEL11 PIXEL12_C PIXEL20_1M PIXEL21_1 PIXEL22_1D break; }\
	case 215: { PIXEL00_1L PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_C } else { PIXEL02_2 } PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_1M if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL21_C PIXEL22_C } else { PIXEL21_3 PIXEL22_4 } break; }\
	case 246: { PIXEL00_1M if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL01_C PIXEL02_C } else { PIXEL01_3 PIXEL02_4 } PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_1L PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL22_C } else { PIXEL22_2 } break; }\
	case 254: { PIXEL00_1M if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL01_C PIXEL02_C } else { PIXEL01_3 PIXEL02_4 } PIXEL11 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL10_C PIXEL20_C } else { PIXEL10_3 PIXEL20_4 } if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL12_C PIXEL21_C PIXEL22_C } else { PIXEL12_3 PIXEL21_3 PIXEL22_2 } break; }\
	case 253: { PIXEL00_1U PIXEL01_1 PIXEL02_1U PIXEL10_C PIXEL11 PIXEL12_C if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_C } else { PIXEL20_2 } PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL22_C } else { PIXEL22_2 } break; }\
	case 251: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL01_C } else { PIXEL00_4 PIXEL01_3 } PIXEL02_1M PIXEL11 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL10_C PIXEL20_C PIXEL21_C } else { PIXEL10_3 PIXEL20_2 PIXEL21_3 } if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL12_C PIXEL22_C } else { PIXEL12_3 PIXEL22_4 } break; }\
	case 239: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C } else { PIXEL00_2 } PIXEL01_C PIXEL02_1R PIXEL10_C PIXEL11 PIXEL12_1 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_C } else { PIXEL20_2 } PIXEL21_C PIXEL22_1R break; }\
	case 127: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL01_C PIXEL10_C } else { PIXEL00_2 PIXEL01_3 PIXEL10_3 } if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_C PIXEL12_C } else { PIXEL02_4 PIXEL12_3 } PIXEL11 if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_C PIXEL21_C } else { PIXEL20_4 PIXEL21_3 } PIXEL22_1M break; }\
	case 191: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C } else { PIXEL00_2 } PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_C } else { PIXEL02_2 } PIXEL10_C PIXEL11 PIXEL12_C PIXEL20_1D PIXEL21_1 PIXEL22_1D break; }\
	case 223: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C PIXEL10_C } else { PIXEL00_4 PIXEL10_3 } if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL01_C PIXEL02_C PIXEL12_C } else { PIXEL01_3 PIXEL02_2 PIXEL12_3 } PIXEL11 PIXEL20_1M if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL21_C PIXEL22_C } else { PIXEL21_3 PIXEL22_4 } break; }\
	case 247: { PIXEL00_1L PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_C } else { PIXEL02_2 } PIXEL10_1 PIXEL11 PIXEL12_C PIXEL20_1L PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL22_C } else { PIXEL22_2 } break; }\
	case 255: { if (Diff(RGBtoYUVtable[w4], RGBtoYUVtable[w2])) { PIXEL00_C } else { PIXEL00_2 } PIXEL01_C if (Diff(RGBtoYUVtable[w2], RGBtoYUVtable[w6])) { PIXEL02_C } else { PIXEL02_2 } PIXEL10_C PIXEL11 PIXEL12_C if (Diff(RGBtoYUVtable[w8], RGBtoYUVtable[w4])) { PIXEL20_C } else { PIXEL20_2 } PIXEL21_C if (Diff(RGBtoYUVtable[w6], RGBtoYUVtable[w8])) { PIXEL22_C } else { PIXEL22_2 } break; }


void RenderHQ3X(unsigned char *src, unsigned int srcpitch, unsigned char *dst, unsigned int dstpitch, int nWidth, int nHeight, int GuiScale)
{
	uint8 *srcPtr = src;
	uint8 *dstPtr = dst;
	uint32 srcPitch = srcpitch;
	uint32 dstPitch = dstpitch;
	int width = nWidth;
	int height = nHeight;

	int	w1, w2, w3, w4, w5, w6, w7, w8, w9;

	uint32	src1line = srcPitch >> 1;
	uint32	dst1line = dstPitch >> 1;
	uint16	*sp = (uint16 *) srcPtr;
	uint16	*dp = (uint16 *) dstPtr;

	const int* RGBtoYUVtable = RGBtoYUV;

	uint32  pattern;
	int		l, y;

	for (int h = 0; h < height; h++)
	{
    	uint16 * sp0 = sp - src1line;
	    if (h == 0 && sp0 < (uint16 *) srcPtr)
	          sp0 = sp;

		sp--;
		sp0--;

		w1 = *(sp0);
		w4 = *(sp);
		w7 = *(sp + src1line);

		sp++;
		sp0++;

		w2 = *(sp0);
		w5 = *(sp);
		w8 = *(sp + src1line);

		for (l = width; l; l--)
		{
			sp++;
			sp0++;

			w3 = *(sp0);
			w6 = *(sp);
			w9 = *(sp + src1line);

			pattern = 0;

			switch(GuiScale)
			{
			case 0: {
				const uint16 avg = (RGBtoBright[w1] + RGBtoBright[w2] + RGBtoBright[w3] + RGBtoBright[w4] + RGBtoBright[w5] + RGBtoBright[w6] + RGBtoBright[w7] + RGBtoBright[w8] + RGBtoBright[w9]) / 9;
				UINT8 diff5 = RGBtoBright[w5] > avg;
				if ((w1 != w5) && ((RGBtoBright[w1] > avg) != diff5)) pattern |= (1 << 0);
				if ((w2 != w5) && ((RGBtoBright[w2] > avg) != diff5)) pattern |= (1 << 1);
				if ((w3 != w5) && ((RGBtoBright[w3] > avg) != diff5)) pattern |= (1 << 2);
				if ((w4 != w5) && ((RGBtoBright[w4] > avg) != diff5)) pattern |= (1 << 3);
				if ((w6 != w5) && ((RGBtoBright[w6] > avg) != diff5)) pattern |= (1 << 4);
				if ((w7 != w5) && ((RGBtoBright[w7] > avg) != diff5)) pattern |= (1 << 5);
				if ((w8 != w5) && ((RGBtoBright[w8] > avg) != diff5)) pattern |= (1 << 6);
				if ((w9 != w5) && ((RGBtoBright[w9] > avg) != diff5)) pattern |= (1 << 7);
              }  break;

			case 1: {
				UINT8 nosame = true;
				if(w1 == w5 || w3 == w5 || w7 == w5 || w9 == w5)
					nosame = false;

				if(nosame)
				{
					const uint16 avg = (RGBtoBright[w1] + RGBtoBright[w2] + RGBtoBright[w3] + RGBtoBright[w4] + RGBtoBright[w5] + RGBtoBright[w6] + RGBtoBright[w7] + RGBtoBright[w8] + RGBtoBright[w9]) / 9;
					UINT8 diff5 = RGBtoBright[w5] > avg;
					if((RGBtoBright[w1] > avg) != diff5) pattern |= (1 << 0);
					if((RGBtoBright[w2] > avg) != diff5) pattern |= (1 << 1);
					if((RGBtoBright[w3] > avg) != diff5) pattern |= (1 << 2);
					if((RGBtoBright[w4] > avg) != diff5) pattern |= (1 << 3);
					if((RGBtoBright[w6] > avg) != diff5) pattern |= (1 << 4);
					if((RGBtoBright[w7] > avg) != diff5) pattern |= (1 << 5);
					if((RGBtoBright[w8] > avg) != diff5) pattern |= (1 << 6);
					if((RGBtoBright[w9] > avg) != diff5) pattern |= (1 << 7);
				}
				else
				{
					y = RGBtoYUV[w5];
					if ((w1 != w5) && (Diff(y, RGBtoYUV[w1]))) pattern |= (1 << 0);
					if ((w2 != w5) && (Diff(y, RGBtoYUV[w2]))) pattern |= (1 << 1);
					if ((w3 != w5) && (Diff(y, RGBtoYUV[w3]))) pattern |= (1 << 2);
					if ((w4 != w5) && (Diff(y, RGBtoYUV[w4]))) pattern |= (1 << 3);
					if ((w6 != w5) && (Diff(y, RGBtoYUV[w6]))) pattern |= (1 << 4);
					if ((w7 != w5) && (Diff(y, RGBtoYUV[w7]))) pattern |= (1 << 5);
					if ((w8 != w5) && (Diff(y, RGBtoYUV[w8]))) pattern |= (1 << 6);
					if ((w9 != w5) && (Diff(y, RGBtoYUV[w9]))) pattern |= (1 << 7);
				}
              }  break;
	        default:
            case 2:
				y = RGBtoYUVtable[w5];
				if ((w1 != w5) && (Diff(y, RGBtoYUVtable[w1]))) pattern |= (1 << 0);
				if ((w2 != w5) && (Diff(y, RGBtoYUVtable[w2]))) pattern |= (1 << 1);
				if ((w3 != w5) && (Diff(y, RGBtoYUVtable[w3]))) pattern |= (1 << 2);
				if ((w4 != w5) && (Diff(y, RGBtoYUVtable[w4]))) pattern |= (1 << 3);
				if ((w6 != w5) && (Diff(y, RGBtoYUVtable[w6]))) pattern |= (1 << 4);
				if ((w7 != w5) && (Diff(y, RGBtoYUVtable[w7]))) pattern |= (1 << 5);
				if ((w8 != w5) && (Diff(y, RGBtoYUVtable[w8]))) pattern |= (1 << 6);
				if ((w9 != w5) && (Diff(y, RGBtoYUVtable[w9]))) pattern |= (1 << 7);
                break;
			}

			switch (pattern)
			{
				HQ3XCASES
			}

			w1 = w2; w4 = w5; w7 = w8;
			w2 = w3; w5 = w6; w8 = w9;

			dp += 3;
		}

		dp += ((dst1line - width) * 3);
		sp +=  (src1line - width);
	}
}


#undef Interp02
#undef Interp06
#undef Interp07
#undef Interp10
#undef Interp03
#undef Interp01
#undef Interp09
#undef Interp04





