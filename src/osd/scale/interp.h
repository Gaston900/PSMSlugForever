#ifndef __INTERP_INC
#define __INTERP_INC

//#define USE_INTERP_MASK_1
//#define USE_INTERP_MASK_2
#define USE_INTERP_MASK_3

#define INTERP_MASK_15_R	0x7c00
#define INTERP_MASK_15_G	0x03e0
#define INTERP_MASK_15_B	0x001f

#define INTERP_MASK_16_R	0xf800
#define INTERP_MASK_16_G	0x07e0
#define INTERP_MASK_16_B	0x001f

#define INTERP_MASK_32_R	0xff0000
#define INTERP_MASK_32_G	0x00ff00
#define INTERP_MASK_32_B	0x0000ff

#ifdef INTERP_MMX

#include "emuopts.h"

#include <mmintrin.h>

#ifdef __GNUC__
	#define __M64_CONST __m64
	#define _MM_PI16(a, b, c, d) \
		{ (((unsigned short)(c)) << 16) | ((unsigned short)(d)), \
		  (((unsigned short)(a)) << 16) | ((unsigned short)(b)) }
#else
	#define __M64_CONST const __m64
	#define _MM_PI16(a, b, c, d) \
		{ ((((long long)((unsigned short)(a))) << 48) \
		|  (((long long)((unsigned short)(b))) << 32) \
		|  (((long long)((unsigned short)(c))) << 16) \
		|  ((unsigned short)(d))) }
#endif

static __M64_CONST CONST_ZERO = _MM_PI16(0, 0, 0, 0);
static __M64_CONST CONST_3333 = _MM_PI16(3, 3, 3, 3);
static __M64_CONST CONST_4444 = _MM_PI16(4, 4, 4, 4);
static __M64_CONST CONST_5555 = _MM_PI16(5, 5, 5, 5);
static __M64_CONST CONST_6666 = _MM_PI16(6, 6, 6, 6);
static __M64_CONST CONST_7777 = _MM_PI16(7, 7, 7, 7);
static __M64_CONST CONST_8888 = _MM_PI16(8, 8, 8, 8);
static __M64_CONST CONST_9999 = _MM_PI16(9, 9, 9, 9);
static __M64_CONST CONST_AAAA = _MM_PI16(10, 10, 10, 10);
static __M64_CONST CONST_BBBB = _MM_PI16(11, 11, 11, 11);
static __M64_CONST CONST_CCCC = _MM_PI16(12, 12, 12, 12);
static __M64_CONST CONST_DDDD = _MM_PI16(13, 13, 13, 13);
static __M64_CONST CONST_EEEE = _MM_PI16(14, 14, 14, 14);
static __M64_CONST CONST_FFFF = _MM_PI16(15, 15, 15, 15);

static __M64_CONST CONST_YUV_THRESHOLD = _MM_PI16(0, 0, 0x30, 0x0706);

extern UINT32 RGBtoYUV[65536];

inline UINT16 interp_32_to_15(UINT32 src)
{
	return (UINT16)
		( ((src >> 9) & INTERP_MASK_15_R)
		| ((src >> 6) & INTERP_MASK_15_G)
		| ((src >> 3) & INTERP_MASK_15_B));
}

inline UINT32 interp_15_to_32(UINT16 src)
{
	UINT32 color = (UINT32)
		( ((src & INTERP_MASK_15_R) << 9)
		| ((src & INTERP_MASK_15_G) << 6)
		| ((src & INTERP_MASK_15_B) << 3));
	return color | ((color >> 5) & 0x070707);
}

inline UINT16 interp_32_to_16(UINT32 src)
{
	return (UINT16)
		( ((src >> 8) & INTERP_MASK_16_R)
		| ((src >> 5) & INTERP_MASK_16_G)
		| ((src >> 3) & INTERP_MASK_16_B));
}

inline UINT32 interp_16_to_32(UINT16 src)
{
	UINT8 r = (src & INTERP_MASK_16_R) >> 11;
	UINT8 g = (src & INTERP_MASK_16_G) >> 5;
	UINT8 b = (src & INTERP_MASK_16_B);

	r = (r << 3) | (r >> 2);
	g = (g << 2) | (g >> 4);
	b = (b << 3) | (b >> 2);
	return (UINT32)((r << 16) | (g << 8) | b);
}

inline __m64 interp_15_unpack(UINT16 src)
{
	return _mm_unpacklo_pi8(_mm_cvtsi32_si64(interp_15_to_32(src)), CONST_ZERO);
}

inline __m64 interp_16_unpack(UINT16 src)
{
	return _mm_unpacklo_pi8(_mm_cvtsi32_si64(interp_16_to_32(src)), CONST_ZERO);
}

inline __m64 interp_32_unpack(UINT32 src)
{
	return _mm_unpacklo_pi8(_mm_cvtsi32_si64(src), CONST_ZERO);
}

inline UINT16 interp_15_pack(__m64 rgb)
{
	return interp_32_to_15(_mm_cvtsi64_si32(_mm_packs_pu16(rgb, rgb)));
}

inline UINT16 interp_16_pack(__m64 rgb)
{
	return interp_32_to_16(_mm_cvtsi64_si32(_mm_packs_pu16(rgb, rgb)));
}

inline UINT32 interp_32_pack(__m64 rgb)
{
	return _mm_cvtsi64_si32(_mm_packs_pu16(rgb, rgb));
}

inline __m64 interp_11(__m64 c1, __m64 c2)
{
	// (c1+c2)/2;
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 1);
}

inline __m64 interp_211(__m64 c1, __m64 c2, __m64 c3)
{
	// (c1*2+c2+c3)/4;
	c1 = _mm_add_pi16(c1, c1);
	c2 = _mm_add_pi16(c2, c3);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 2);
}

inline __m64 interp_31(__m64 c1, __m64 c2)
{
	// (c1*3+c2)/4;
	c1 = _mm_mullo_pi16(c1, CONST_3333);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 2);
}

inline __m64 interp_521(__m64 c1, __m64 c2, __m64 c3)
{
	// (c1*5+c2*2+c3)/8;
	c1 = _mm_mullo_pi16(c1, CONST_5555);
	c2 = _mm_add_pi16(c2, c2);
	c2 = _mm_add_pi16(c2, c3);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 3);
}

inline __m64 interp_431(__m64 c1, __m64 c2, __m64 c3)
{
	// (c1*4+c2*3+c3)/8;
#ifdef __GNUC__	
	c1 = _mm_add_pi16(c1, c1);
	c1 = _mm_add_pi16(c1, c1);
#else
	c1 = _mm_slli_pi16(c1, 2);
#endif	
	c2 = _mm_mullo_pi16(c2, CONST_3333);
	c2 = _mm_add_pi16(c2, c3);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 3);
}

inline __m64 interp_53(__m64 c1, __m64 c2)
{
	// (c1*5+c2*3)/8;
	c1 = _mm_mullo_pi16(c1, CONST_5555);
	c2 = _mm_mullo_pi16(c2, CONST_3333);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 3);
}

inline __m64 interp_332(__m64 c1, __m64 c2, __m64 c3)
{
	// ((c1+c2)*3+c3*2)/8;
	c1 = _mm_add_pi16(c1, c2);
	c1 = _mm_mullo_pi16(c1, CONST_3333);
	c3 = _mm_add_pi16(c3, c3);
	return _mm_srli_pi16(_mm_add_pi16(c1, c3), 3);
}

inline __m64 interp_611(__m64 c1, __m64 c2, __m64 c3)
{
	// (c1*6+c2+c3)/8;
	c1 = _mm_mullo_pi16(c1, CONST_6666);
	c2 = _mm_add_pi16(c2, c3);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 3);
}

inline __m64 interp_71(__m64 c1, __m64 c2)
{
	// (c1*7+c2)/8;
	c1 = _mm_mullo_pi16(c1, CONST_7777);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 3);
}

inline __m64 interp_655(__m64 c1, __m64 c2, __m64 c3)
{
	// (c1*6+c2*5+c3*5)/16;
	c1 = _mm_mullo_pi16(c1, CONST_6666);
	c2 = _mm_add_pi16(c2, c3);
	c2 = _mm_mullo_pi16(c2, CONST_5555);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 4);
}

inline __m64 interp_754(__m64 c1, __m64 c2, __m64 c3)
{
	// (c1*7+c2*5+c3*4)/16;
	c1 = _mm_mullo_pi16(c1, CONST_7777);
	c2 = _mm_mullo_pi16(c2, CONST_5555);
	c3 = _mm_mullo_pi16(c3, CONST_4444);
	c2 = _mm_add_pi16(c2, c3);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 4);
}

inline __m64 interp_763(__m64 c1, __m64 c2, __m64 c3)
{
	// (c1*7+c2*6+c3*3)/16;
	c1 = _mm_mullo_pi16(c1, CONST_7777);
	c2 = _mm_mullo_pi16(c2, CONST_6666);
	c3 = _mm_mullo_pi16(c3, CONST_3333);
	c2 = _mm_add_pi16(c2, c3);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 4);
}

inline __m64 interp_772(__m64 c1, __m64 c2, __m64 c3)
{
	// ((c1+c2)*7+c3*2)/16;
	c1 = _mm_add_pi16(c1, c2);
	c1 = _mm_mullo_pi16(c1, CONST_7777);
	c3 = _mm_add_pi16(c3, c3);
	return _mm_srli_pi16(_mm_add_pi16(c1, c3), 4);
}

inline __m64 interp_853(__m64 c1, __m64 c2, __m64 c3)
{
	// (c1*8+c2*5+c3*3)/16;
	c1 = _mm_mullo_pi16(c1, CONST_8888);
	c2 = _mm_mullo_pi16(c2, CONST_5555);
	c3 = _mm_mullo_pi16(c3, CONST_3333);
	c2 = _mm_add_pi16(c2, c3);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 4);
}

inline __m64 interp_943(__m64 c1, __m64 c2, __m64 c3)
{
	// (c1*9+c2*4+c3*3)/16;
	c1 = _mm_mullo_pi16(c1, CONST_9999);
	c2 = _mm_mullo_pi16(c2, CONST_4444);
	c3 = _mm_mullo_pi16(c3, CONST_3333);
	c2 = _mm_add_pi16(c2, c3);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 4);
}

inline __m64 interp_961(__m64 c1, __m64 c2, __m64 c3)
{
	// (c1*9+c2*6+c3)/16;
	c1 = _mm_mullo_pi16(c1, CONST_9999);
	c2 = _mm_mullo_pi16(c2, CONST_6666);
	c2 = _mm_add_pi16(c2, c3);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 4);
}

inline __m64 interp_1033(__m64 c1, __m64 c2, __m64 c3)
{
	// (c1*10+c2*3+c3*3)/16;
	c1 = _mm_mullo_pi16(c1, CONST_AAAA);
	c2 = _mm_add_pi16(c2, c3);
	c2 = _mm_mullo_pi16(c2, CONST_3333);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 4);
}

inline __m64 interp_1051(__m64 c1, __m64 c2, __m64 c3)
{
	// (c1*10+c2*5+c3)/16;
	c1 = _mm_mullo_pi16(c1, CONST_AAAA);
	c2 = _mm_mullo_pi16(c2, CONST_5555);
	c2 = _mm_add_pi16(c2, c3);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 4);
}

inline __m64 interp_1132(__m64 c1, __m64 c2, __m64 c3)
{
	// (c1*11+c2*3+c3*2)/16;
	c1 = _mm_mullo_pi16(c1, CONST_BBBB);
	c2 = _mm_mullo_pi16(c2, CONST_3333);
	c3 = _mm_add_pi16(c3, c3);
	c2 = _mm_add_pi16(c2, c3);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 4);
}

inline __m64 interp_115(__m64 c1, __m64 c2)
{
	// (c1*11+c2*5)/16;
	c1 = _mm_mullo_pi16(c1, CONST_BBBB);
	c2 = _mm_mullo_pi16(c2, CONST_5555);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 4);
}

inline __m64 interp_1231(__m64 c1, __m64 c2, __m64 c3)
{
	// (c1*12+c2*3+c3)/16;
	c1 = _mm_mullo_pi16(c1, CONST_CCCC);
	c2 = _mm_mullo_pi16(c2, CONST_3333);
	c2 = _mm_add_pi16(c2, c3);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 4);
}

inline __m64 interp_133(__m64 c1, __m64 c2)
{
	// (c1*13+c2*3)/16;
	c1 = _mm_mullo_pi16(c1, CONST_DDDD);
	c2 = _mm_mullo_pi16(c2, CONST_3333);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 4);
}

inline __m64 interp_1411(__m64 c1, __m64 c2, __m64 c3)
{
	// (c1*14+c2+c3)/16;
	c1 = _mm_mullo_pi16(c1, CONST_EEEE);
	c2 = _mm_add_pi16(c2, c3);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 4);
}

inline __m64 interp_151(__m64 c1, __m64 c2)
{
	// (c1*15+c2)/16;
	c1 = _mm_mullo_pi16(c1, CONST_FFFF);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 4);
}

inline __m64 interp_97(__m64 c1, __m64 c2)
{
	// (c1*9+c2*7)/16;
	c1 = _mm_mullo_pi16(c1, CONST_9999);
	c2 = _mm_mullo_pi16(c2, CONST_7777);
	return _mm_srli_pi16(_mm_add_pi16(c1, c2), 4);
}

inline int interp_diff(UINT16 c1, UINT16 c2)
{
	__m64 yuv1, yuv2, d1, d2;

	if (c1 == c2) return 0;
	yuv1 = _mm_cvtsi32_si64(RGBtoYUV[c1]);
	yuv2 = _mm_cvtsi32_si64(RGBtoYUV[c2]);
	d1 = _mm_subs_pu8(yuv1, yuv2);
	d2 = _mm_subs_pu8(yuv2, yuv1);
	d1 = _mm_or_si64(d1, d2);
	d1 = _mm_subs_pu8(d1, CONST_YUV_THRESHOLD);
	return _mm_cvtsi64_si32(d1);
}

#endif	// INTERP_MMX

#define INTERP_15_MASK_1(v) ((v) & (INTERP_MASK_15_R|INTERP_MASK_15_B))
#define INTERP_15_MASK_2(v) ((v) & INTERP_MASK_15_G)
#define INTERP_16_MASK_1(v) ((v) & (INTERP_MASK_16_R|INTERP_MASK_16_B))
#define INTERP_16_MASK_2(v) ((v) & INTERP_MASK_16_G)
#define INTERP_32_MASK_1(v) ((v) & (INTERP_MASK_32_R|INTERP_MASK_32_B))
#define INTERP_32_MASK_2(v) ((v) & INTERP_MASK_32_G)

#define INTERP_15_HNMASK 	(~0x00c210U)
#define INTERP_16_HNMASK 	(~0x008410U)
#define INTERP_32_HNMASK 	(~0x808080U)

#define INTERP_15_GEN2(a,b) \
inline UINT16 interp_15_##a##b(UINT16 p1, UINT16 p2) \
{ \
	return INTERP_15_MASK_1((INTERP_15_MASK_1(p1)*a + INTERP_15_MASK_1(p2)*b) / 16) \
		| INTERP_15_MASK_2((INTERP_15_MASK_2(p1)*a + INTERP_15_MASK_2(p2)*b) / 16); \
}

#define INTERP_15_GEN3(a,b,c) \
inline UINT16 interp_15_##a##b##c(UINT16 p1, UINT16 p2, UINT16 p3) \
{ \
	return INTERP_15_MASK_1((INTERP_15_MASK_1(p1)*a + INTERP_15_MASK_1(p2)*b + INTERP_15_MASK_1(p3)*c) / 16) \
		| INTERP_15_MASK_2((INTERP_15_MASK_2(p1)*a + INTERP_15_MASK_2(p2)*b + INTERP_15_MASK_2(p3)*c) / 16); \
}

#define INTERP_16_GEN2(a,b) \
inline UINT16 interp_16_##a##b(UINT16 p1, UINT16 p2) \
{ \
	return INTERP_16_MASK_1((INTERP_16_MASK_1(p1)*a + INTERP_16_MASK_1(p2)*b) / 16) \
		| INTERP_16_MASK_2((INTERP_16_MASK_2(p1)*a + INTERP_16_MASK_2(p2)*b) / 16); \
}

#define INTERP_16_GEN3(a,b,c) \
inline UINT16 interp_16_##a##b##c(UINT16 p1, UINT16 p2, UINT16 p3) \
{ \
	return INTERP_16_MASK_1((INTERP_16_MASK_1(p1)*a + INTERP_16_MASK_1(p2)*b + INTERP_16_MASK_1(p3)*c) / 16) \
		| INTERP_16_MASK_2((INTERP_16_MASK_2(p1)*a + INTERP_16_MASK_2(p2)*b + INTERP_16_MASK_2(p3)*c) / 16); \
}

#define INTERP_32_GEN2(a,b) \
inline UINT32 interp_32_##a##b(UINT32 p1, UINT32 p2) \
{ \
	return INTERP_32_MASK_1((INTERP_32_MASK_1(p1)*a + INTERP_32_MASK_1(p2)*b) / 16) \
		| INTERP_32_MASK_2((INTERP_32_MASK_2(p1)*a + INTERP_32_MASK_2(p2)*b) / 16); \
}

#define INTERP_32_GEN3(a,b,c) \
inline UINT32 interp_32_##a##b##c(UINT32 p1, UINT32 p2, UINT32 p3) \
{ \
	return INTERP_32_MASK_1((INTERP_32_MASK_1(p1)*a + INTERP_32_MASK_1(p2)*b + INTERP_32_MASK_1(p3)*c) / 16) \
		| INTERP_32_MASK_2((INTERP_32_MASK_2(p1)*a + INTERP_32_MASK_2(p2)*b + INTERP_32_MASK_2(p3)*c) / 16); \
}


inline UINT16 interp_15_11(UINT16 p1, UINT16 p2)
{
#ifdef USE_INTERP_MASK_1
	return INTERP_15_MASK_1((INTERP_15_MASK_1(p1) + INTERP_15_MASK_1(p2)) / 2)
		| INTERP_15_MASK_2((INTERP_15_MASK_2(p1) + INTERP_15_MASK_2(p2)) / 2);
#else
	/*
	 * This function compute (a + b) / 2 for any rgb nibble, using the
	 * the formula (a + b) / 2 = ((a ^ b) >> 1) + (a & b).
	 * To extend this formula to a serie of packed nibbles the formula is
	 * implemented as (((v0 ^ v1) >> 1) & MASK) + (v0 & v1) where MASK
	 * is used to clear the high bit of all the packed nibbles.
	 */
	return (((p1 ^ p2) >> 1) & INTERP_15_HNMASK) + (p1 & p2);
#endif
}

inline UINT16 interp_15_211(UINT16 p1, UINT16 p2, UINT16 p3)
{
#ifdef USE_INTERP_MASK_2
	return INTERP_15_MASK_1((INTERP_15_MASK_1(p1)*2 + INTERP_15_MASK_1(p2) + INTERP_15_MASK_1(p3)) / 4)
		| INTERP_15_MASK_2((INTERP_15_MASK_2(p1)*2 + INTERP_15_MASK_2(p2) + INTERP_15_MASK_2(p3)) / 4);
#else
	return interp_15_11(p1, interp_15_11(p2, p3));
#endif
}

inline UINT16 interp_15_31(UINT16 p1, UINT16 p2)
{
#ifdef USE_INTERP_MASK_2
	return INTERP_15_MASK_1((INTERP_15_MASK_1(p1)*3 + INTERP_15_MASK_1(p2)) / 4)
		| INTERP_15_MASK_2((INTERP_15_MASK_2(p1)*3 + INTERP_15_MASK_2(p2)) / 4);
#else
	return interp_15_11(p1, interp_15_11(p1, p2));
#endif
}

inline UINT16 interp_15_521(UINT16 p1, UINT16 p2, UINT16 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_15_MASK_1((INTERP_15_MASK_1(p1)*5 + INTERP_15_MASK_1(p2)*2 + INTERP_15_MASK_1(p3)) / 8)
		| INTERP_15_MASK_2((INTERP_15_MASK_2(p1)*5 + INTERP_15_MASK_2(p2)*2 + INTERP_15_MASK_2(p3)) / 8);
#else
	return interp_15_11(p1, interp_15_11(p2, interp_15_11(p1, p3)));
#endif
}

inline UINT16 interp_15_431(UINT16 p1, UINT16 p2, UINT16 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_15_MASK_1((INTERP_15_MASK_1(p1)*4 + INTERP_15_MASK_1(p2)*3 + INTERP_15_MASK_1(p3)) / 8)
		| INTERP_15_MASK_2((INTERP_15_MASK_2(p1)*4 + INTERP_15_MASK_2(p2)*3 + INTERP_15_MASK_2(p3)) / 8);
#else
	return interp_15_11(p1, interp_15_11(p2, interp_15_11(p2, p3)));
#endif
}

inline UINT16 interp_15_53(UINT16 p1, UINT16 p2)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_15_MASK_1((INTERP_15_MASK_1(p1)*5 + INTERP_15_MASK_1(p2)*3) / 8)
		| INTERP_15_MASK_2((INTERP_15_MASK_2(p1)*5 + INTERP_15_MASK_2(p2)*3) / 8);
#else
	return interp_15_11(p1, interp_15_11(p2, interp_15_11(p1, p2)));
#endif
}

inline UINT16 interp_15_332(UINT16 p1, UINT16 p2, UINT16 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_15_MASK_1(((INTERP_15_MASK_1(p1) + INTERP_15_MASK_1(p2))*3 + INTERP_15_MASK_1(p3)*2) / 8)
		| INTERP_15_MASK_2(((INTERP_15_MASK_2(p1) + INTERP_15_MASK_2(p2))*3 + INTERP_15_MASK_2(p3)*2) / 8);
#else
	UINT16 t = interp_15_11(p1, p2);
	return interp_15_11(t, interp_15_11(p3, t));
#endif
}

inline UINT16 interp_15_611(UINT16 p1, UINT16 p2, UINT16 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_15_MASK_1((INTERP_15_MASK_1(p1)*6 + INTERP_15_MASK_1(p2) + INTERP_15_MASK_1(p3)) / 8)
		| INTERP_15_MASK_2((INTERP_15_MASK_2(p1)*6 + INTERP_15_MASK_2(p2) + INTERP_15_MASK_2(p3)) / 8);
#else
	return interp_15_11(p1, interp_15_11(p1, interp_15_11(p2, p3)));
#endif
}

inline UINT16 interp_15_71(UINT16 p1, UINT16 p2)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_15_MASK_1((INTERP_15_MASK_1(p1)*7 + INTERP_15_MASK_1(p2)) / 8)
		| INTERP_15_MASK_2((INTERP_15_MASK_2(p1)*7 + INTERP_15_MASK_2(p2)) / 8);
#else
	return interp_15_11(p1, interp_15_11(p1, interp_15_11(p1, p2)));
#endif
}

#if 0
inline UINT16 interp_15_772(UINT16 p1, UINT16 p2, UINT16 p3)
{
	return INTERP_15_MASK_1(((INTERP_15_MASK_1(p1) + INTERP_15_MASK_1(p2))*7 + INTERP_15_MASK_1(p3)*2) / 16)
		| INTERP_15_MASK_2(((INTERP_15_MASK_2(p1) + INTERP_15_MASK_2(p2))*7 + INTERP_15_MASK_2(p3)*2) / 16);
}

inline UINT16 interp_15_1411(UINT16 p1, UINT16 p2, UINT16 p3)
{
	return INTERP_15_MASK_1((INTERP_15_MASK_1(p1)*14 + INTERP_15_MASK_1(p2) + INTERP_15_MASK_1(p3)) / 16)
		| INTERP_15_MASK_2((INTERP_15_MASK_2(p1)*14 + INTERP_15_MASK_2(p2) + INTERP_15_MASK_2(p3)) / 16);
}

inline UINT16 interp_15_151(UINT16 p1, UINT16 p2)
{
	return INTERP_15_MASK_1((INTERP_15_MASK_1(p1)*15 + INTERP_15_MASK_1(p2)) / 16)
		| INTERP_15_MASK_2((INTERP_15_MASK_2(p1)*15 + INTERP_15_MASK_2(p2)) / 16);
}

inline UINT16 interp_15_97(UINT16 p1, UINT16 p2)
{
	return INTERP_15_MASK_1((INTERP_15_MASK_1(p1)*9 + INTERP_15_MASK_1(p2)*7) / 16)
		| INTERP_15_MASK_2((INTERP_15_MASK_2(p1)*9 + INTERP_15_MASK_2(p2)*7) / 16);
}
#endif

INTERP_15_GEN3(6,5,5)
INTERP_15_GEN3(7,5,4)
INTERP_15_GEN3(7,6,3)
INTERP_15_GEN3(7,7,2)
INTERP_15_GEN3(8,5,3)
INTERP_15_GEN3(9,4,3)
INTERP_15_GEN3(9,6,1)
INTERP_15_GEN3(10,3,3)
INTERP_15_GEN3(10,5,1)
INTERP_15_GEN3(11,3,2)
INTERP_15_GEN2(11,5)
INTERP_15_GEN3(12,3,1)
INTERP_15_GEN2(13,3)
INTERP_15_GEN3(14,1,1)
INTERP_15_GEN2(15,1)
INTERP_15_GEN2(9,7)

inline UINT16 interp_16_11(UINT16 p1, UINT16 p2)
{
#ifdef USE_INTERP_MASK_1
	return INTERP_16_MASK_1((INTERP_16_MASK_1(p1) + INTERP_16_MASK_1(p2)) / 2)
		| INTERP_16_MASK_2((INTERP_16_MASK_2(p1) + INTERP_16_MASK_2(p2)) / 2);
#else
	/*
	 * This function compute (a + b) / 2 for any rgb nibble, using the
	 * the formula (a + b) / 2 = ((a ^ b) >> 1) + (a & b).
	 * To extend this formula to a serie of packed nibbles the formula is
	 * implemented as (((v0 ^ v1) >> 1) & MASK) + (v0 & v1) where MASK
	 * is used to clear the high bit of all the packed nibbles.
	 */
	return (((p1 ^ p2) >> 1) & INTERP_16_HNMASK) + (p1 & p2);
#endif
}

inline UINT16 interp_16_211(UINT16 p1, UINT16 p2, UINT16 p3)
{
#ifdef USE_INTERP_MASK_2
	return INTERP_16_MASK_1((INTERP_16_MASK_1(p1)*2 + INTERP_16_MASK_1(p2) + INTERP_16_MASK_1(p3)) / 4)
		| INTERP_16_MASK_2((INTERP_16_MASK_2(p1)*2 + INTERP_16_MASK_2(p2) + INTERP_16_MASK_2(p3)) / 4);
#else
	return interp_16_11(p1, interp_16_11(p2, p3));
#endif
}

inline UINT16 interp_16_31(UINT16 p1, UINT16 p2)
{
#ifdef USE_INTERP_MASK_2
	return INTERP_16_MASK_1((INTERP_16_MASK_1(p1)*3 + INTERP_16_MASK_1(p2)) / 4)
		| INTERP_16_MASK_2((INTERP_16_MASK_2(p1)*3 + INTERP_16_MASK_2(p2)) / 4);
#else
	return interp_16_11(p1, interp_16_11(p1, p2));
#endif
}

inline UINT16 interp_16_521(UINT16 p1, UINT16 p2, UINT16 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_16_MASK_1((INTERP_16_MASK_1(p1)*5 + INTERP_16_MASK_1(p2)*2 + INTERP_16_MASK_1(p3)) / 8)
		| INTERP_16_MASK_2((INTERP_16_MASK_2(p1)*5 + INTERP_16_MASK_2(p2)*2 + INTERP_16_MASK_2(p3)) / 8);
#else
	return interp_16_11(p1, interp_16_11(p2, interp_16_11(p1, p3)));
#endif
}

inline UINT16 interp_16_431(UINT16 p1, UINT16 p2, UINT16 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_16_MASK_1((INTERP_16_MASK_1(p1)*4 + INTERP_16_MASK_1(p2)*3 + INTERP_16_MASK_1(p3)) / 8)
		| INTERP_16_MASK_2((INTERP_16_MASK_2(p1)*4 + INTERP_16_MASK_2(p2)*3 + INTERP_16_MASK_2(p3)) / 8);
#else
	return interp_16_11(p1, interp_16_11(p2, interp_16_11(p2, p3)));
#endif
}

inline UINT16 interp_16_53(UINT16 p1, UINT16 p2)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_16_MASK_1((INTERP_16_MASK_1(p1)*5 + INTERP_16_MASK_1(p2)*3) / 8)
		| INTERP_16_MASK_2((INTERP_16_MASK_2(p1)*5 + INTERP_16_MASK_2(p2)*3) / 8);
#else
	return interp_16_11(p1, interp_16_11(p2, interp_16_11(p1, p2)));
#endif
}

inline UINT16 interp_16_332(UINT16 p1, UINT16 p2, UINT16 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_16_MASK_1(((INTERP_16_MASK_1(p1) + INTERP_16_MASK_1(p2))*3 + INTERP_16_MASK_1(p3)*2) / 8)
		| INTERP_16_MASK_2(((INTERP_16_MASK_2(p1) + INTERP_16_MASK_2(p2))*3 + INTERP_16_MASK_2(p3)*2) / 8);
#else
	UINT16 t = interp_16_11(p1, p2);
	return interp_16_11(t, interp_16_11(p3, t));
#endif
}

inline UINT16 interp_16_611(UINT16 p1, UINT16 p2, UINT16 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_16_MASK_1((INTERP_16_MASK_1(p1)*6 + INTERP_16_MASK_1(p2) + INTERP_16_MASK_1(p3)) / 8)
		| INTERP_16_MASK_2((INTERP_16_MASK_2(p1)*6 + INTERP_16_MASK_2(p2) + INTERP_16_MASK_2(p3)) / 8);
#else
	return interp_16_11(p1, interp_16_11(p1, interp_16_11(p2, p3)));
#endif
}

inline UINT16 interp_16_71(UINT16 p1, UINT16 p2)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_16_MASK_1((INTERP_16_MASK_1(p1)*7 + INTERP_16_MASK_1(p2)) / 8)
		| INTERP_16_MASK_2((INTERP_16_MASK_2(p1)*7 + INTERP_16_MASK_2(p2)) / 8);
#else
	return interp_16_11(p1, interp_16_11(p1, interp_16_11(p1, p2)));
#endif
}

INTERP_16_GEN3(6,5,5)
INTERP_16_GEN3(7,5,4)
INTERP_16_GEN3(7,6,3)
INTERP_16_GEN3(7,7,2)
INTERP_16_GEN3(8,5,3)
INTERP_16_GEN3(9,4,3)
INTERP_16_GEN3(9,6,1)
INTERP_16_GEN3(10,3,3)
INTERP_16_GEN3(10,5,1)
INTERP_16_GEN3(11,3,2)
INTERP_16_GEN2(11,5)
INTERP_16_GEN3(12,3,1)
INTERP_16_GEN2(13,3)
INTERP_16_GEN3(14,1,1)
INTERP_16_GEN2(15,1)
INTERP_16_GEN2(9,7)

inline UINT32 interp_32_11(UINT32 p1, UINT32 p2)
{
#ifdef USE_INTERP_MASK_1
	return INTERP_32_MASK_1((INTERP_32_MASK_1(p1) + INTERP_32_MASK_1(p2)) / 2)
		| INTERP_32_MASK_2((INTERP_32_MASK_2(p1) + INTERP_32_MASK_2(p2)) / 2);
#else
	/*
	 * This function compute (a + b) / 2 for any rgb nibble, using the
	 * the formula (a + b) / 2 = ((a ^ b) >> 1) + (a & b).
	 * To extend this formula to a serie of packed nibbles the formula is
	 * implemented as (((v0 ^ v1) >> 1) & MASK) + (v0 & v1) where MASK
	 * is used to clear the high bit of all the packed nibbles.
	 */
	return (((p1 ^ p2) >> 1) & INTERP_32_HNMASK) + (p1 & p2);
#endif
}

inline UINT32 interp_32_211(UINT32 p1, UINT32 p2, UINT32 p3)
{
#ifdef USE_INTERP_MASK_2
	return INTERP_32_MASK_1((INTERP_32_MASK_1(p1)*2 + INTERP_32_MASK_1(p2) + INTERP_32_MASK_1(p3)) / 4)
		| INTERP_32_MASK_2((INTERP_32_MASK_2(p1)*2 + INTERP_32_MASK_2(p2) + INTERP_32_MASK_2(p3)) / 4);
#else
	return interp_32_11(p1, interp_32_11(p2, p3));
#endif
}

inline UINT32 interp_32_31(UINT32 p1, UINT32 p2)
{
#ifdef USE_INTERP_MASK_2
	return INTERP_32_MASK_1((INTERP_32_MASK_1(p1)*3 + INTERP_32_MASK_1(p2)) / 4)
		| INTERP_32_MASK_2((INTERP_32_MASK_2(p1)*3 + INTERP_32_MASK_2(p2)) / 4);
#else
	return interp_32_11(p1, interp_32_11(p1, p2));
#endif
}

inline UINT32 interp_32_521(UINT32 p1, UINT32 p2, UINT32 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_32_MASK_1((INTERP_32_MASK_1(p1)*5 + INTERP_32_MASK_1(p2)*2 + INTERP_32_MASK_1(p3)) / 8)
		| INTERP_32_MASK_2((INTERP_32_MASK_2(p1)*5 + INTERP_32_MASK_2(p2)*2 + INTERP_32_MASK_2(p3)) / 8);
#else
	return interp_32_11(p1, interp_32_11(p2, interp_32_11(p1, p3)));
#endif
}

inline UINT32 interp_32_431(UINT32 p1, UINT32 p2, UINT32 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_32_MASK_1((INTERP_32_MASK_1(p1)*4 + INTERP_32_MASK_1(p2)*3 + INTERP_32_MASK_1(p3)) / 8)
		| INTERP_32_MASK_2((INTERP_32_MASK_2(p1)*4 + INTERP_32_MASK_2(p2)*3 + INTERP_32_MASK_2(p3)) / 8);
#else
	return interp_32_11(p1, interp_32_11(p2, interp_32_11(p2, p3)));
#endif
}

inline UINT32 interp_32_53(UINT32 p1, UINT32 p2)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_32_MASK_1((INTERP_32_MASK_1(p1)*5 + INTERP_32_MASK_1(p2)*3) / 8)
		| INTERP_32_MASK_2((INTERP_32_MASK_2(p1)*5 + INTERP_32_MASK_2(p2)*3) / 8);
#else
	return interp_32_11(p1, interp_32_11(p2, interp_32_11(p1, p2)));
#endif
}

inline UINT32 interp_32_332(UINT32 p1, UINT32 p2, UINT32 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_32_MASK_1(((INTERP_32_MASK_1(p1) + INTERP_32_MASK_1(p2))*3 + INTERP_32_MASK_1(p3)*2) / 8)
		| INTERP_32_MASK_2(((INTERP_32_MASK_2(p1) + INTERP_32_MASK_2(p2))*3 + INTERP_32_MASK_2(p3)*2) / 8);
#else
	UINT32 t = interp_32_11(p1, p2);
	return interp_32_11(t, interp_32_11(p3, t));
#endif
}

inline UINT32 interp_32_611(UINT32 p1, UINT32 p2, UINT32 p3)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_32_MASK_1((INTERP_32_MASK_1(p1)*6 + INTERP_32_MASK_1(p2) + INTERP_32_MASK_1(p3)) / 8)
		| INTERP_32_MASK_2((INTERP_32_MASK_2(p1)*6 + INTERP_32_MASK_2(p2) + INTERP_32_MASK_2(p3)) / 8);
#else
	return interp_32_11(p1, interp_32_11(p1, interp_32_11(p2, p3)));
#endif
}

inline UINT32 interp_32_71(UINT32 p1, UINT32 p2)
{
#ifdef USE_INTERP_MASK_3
	return INTERP_32_MASK_1((INTERP_32_MASK_1(p1)*7 + INTERP_32_MASK_1(p2)) / 8)
		| INTERP_32_MASK_2((INTERP_32_MASK_2(p1)*7 + INTERP_32_MASK_2(p2)) / 8);
#else
	return interp_32_11(p1, interp_32_11(p1, interp_32_11(p1, p2)));
#endif
}

INTERP_32_GEN3(6,5,5)
INTERP_32_GEN3(7,5,4)
INTERP_32_GEN3(7,6,3)
INTERP_32_GEN3(7,7,2)
INTERP_32_GEN3(8,5,3)
INTERP_32_GEN3(9,4,3)
INTERP_32_GEN3(9,6,1)
INTERP_32_GEN3(10,3,3)
INTERP_32_GEN3(10,5,1)
INTERP_32_GEN3(11,3,2)
INTERP_32_GEN2(11,5)
INTERP_32_GEN3(12,3,1)
INTERP_32_GEN2(13,3)
INTERP_32_GEN3(14,1,1)
INTERP_32_GEN2(15,1)
INTERP_32_GEN2(9,7)

/***************************************************************************/
/* diff */

#define INTERP_Y_LIMIT (0x30*4)
#define INTERP_U_LIMIT (0x07*4)
#define INTERP_V_LIMIT (0x06*8)

inline int interp_15_diff(UINT16 p1, UINT16 p2)
{
	int r, g, b;
	int y, u, v;

	if (p1 == p2)
		return 0;

	b = (int)((p1 & INTERP_MASK_15_B) - (p2 & INTERP_MASK_15_B)) << 3;
	g = (int)((p1 & INTERP_MASK_15_G) - (p2 & INTERP_MASK_15_G)) >> 2;
	r = (int)((p1 & INTERP_MASK_15_R) - (p2 & INTERP_MASK_15_R)) >> 7;

	y = r + g + b;
	if (y < -INTERP_Y_LIMIT || y > INTERP_Y_LIMIT)
		return 1;

	u = r - b;
	if (u < -INTERP_U_LIMIT || u > INTERP_U_LIMIT)
		return 1;

	v = -r + 2*g - b;
	if (v < -INTERP_V_LIMIT || v > INTERP_V_LIMIT)
		return 1;

	return 0;
}

inline int interp_16_diff(UINT16 p1, UINT16 p2)
{
	int r, g, b;
	int y, u, v;

	if (p1 == p2)
		return 0;

	b = (int)((p1 & INTERP_MASK_16_B) - (p2 & INTERP_MASK_16_B)) << 3;
	g = (int)((p1 & INTERP_MASK_16_G) - (p2 & INTERP_MASK_16_G)) >> 3;
	r = (int)((p1 & INTERP_MASK_16_R) - (p2 & INTERP_MASK_16_R)) >> 8;

	y = r + g + b;
	if (y < -INTERP_Y_LIMIT || y > INTERP_Y_LIMIT)
		return 1;

	u = r - b;
	if (u < -INTERP_U_LIMIT || u > INTERP_U_LIMIT)
		return 1;

	v = -r + 2*g - b;
	if (v < -INTERP_V_LIMIT || v > INTERP_V_LIMIT)
		return 1;

	return 0;
}

inline int interp_32_diff(UINT32 p1, UINT32 p2)
{
	int r, g, b;
	int y, u, v;

	if ((p1 & 0xF8F8F8) == (p2 & 0xF8F8F8))
		return 0;

	b = (int)((p1 & INTERP_MASK_32_B) - (p2 & INTERP_MASK_32_B));
	g = (int)((p1 & INTERP_MASK_32_G) - (p2 & INTERP_MASK_32_G)) >> 8;
	r = (int)((p1 & INTERP_MASK_32_R) - (p2 & INTERP_MASK_32_R)) >> 16;

	y = r + g + b;
	if (y < -INTERP_Y_LIMIT || y > INTERP_Y_LIMIT)
		return 1;

	u = r - b;
	if (u < -INTERP_U_LIMIT || u > INTERP_U_LIMIT)
		return 1;

	v = -r + 2*g - b;
	if (v < -INTERP_V_LIMIT || v > INTERP_V_LIMIT)
		return 1;

	return 0;
}
#endif
