#ifndef _PORT_H_
#define _PORT_H_

#include <limits.h>

#ifndef STORM
#include <string.h>
#else
#include <strings.h>
#include <clib/powerpc_protos.h>
#endif

#ifndef ACCEPT_SIZE_T
#ifdef __WIN32__
#define ACCEPT_SIZE_T int
#else
#define ACCEPT_SIZE_T unsigned int
#endif
#endif

#include <sys/types.h>
#include "osdcore.h"

/* #define PIXEL_FORMAT RGB565 */
#define GFX_MULTI_FORMAT

#ifndef NOASM
//#define USE_X86_ASM
#endif

#ifdef __MACOSX__

	#ifdef _C
	#undef _C
	#endif

	#ifdef _D
	#undef _D
	#endif

	#define CHECK_SOUND()
	#define PIXEL_FORMAT RGB555
	#undef GFX_MULTI_FORMAT
	#undef USE_X86_ASM
	#undef _MAX_PATH

	#define SET_UI_COLOR(r,g,b)	SetInfoDlgColor(r,g,b)
	void SetInfoDlgColor(unsigned char, unsigned char, unsigned char);

#endif /* __MACOSX__ */

#ifndef snes9x_types_defined
#define snes9x_types_defined

typedef unsigned char bool8;

#ifdef HAVE_STDINT_H
#include <stdint.h>

typedef int8_t int8;
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef int32_t int32;
typedef uint32_t uint32;
typedef int64_t int64;
typedef uint64_t uint64;
typedef intptr_t pint;

#else /* Don't have stdint.h */

#ifdef PTR_NOT_INT
typedef long pint;
#else /* pointer is int */
typedef int pint;
#endif /* PTR_NOT_INT */

/* FIXME: Refactor this by moving out the BORLAND part and unifying typedefs */
#ifndef __WIN32__
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef signed char int8;
typedef short int16;
typedef int int32;
typedef unsigned int uint32;
# ifdef __GNUC__  /* long long is not part of ISO C++ */
__extension__
# endif
typedef long long int64;
typedef unsigned long long uint64;
#else /* __WIN32__ */

#include <windows.h>

# ifdef __BORLANDC__
#   include <systypes.h>
# else

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef signed char int8;
typedef short int16;

# ifndef WSAAPI
/* winsock2.h typedefs int32 as well. */
typedef long int32;

#   define PLAT_SOUND_BUFFER SoundBuffer
#   define RIGHTSHIFT_IS_SAR
# endif

# if defined(_MSC_VER) && (_MSC_VER == 1400) /* VC8.0 */
/* temporary solution for fatal error C1063 (cl.exe 14.00.50727.762) */
#   ifdef RIGHTSHIFT_IS_SAR
#     undef RIGHTSHIFT_IS_SAR
#   endif /* RIGHTSHIFT_IS_SAR */
#   define RIGHTSHIFT_INT8_IS_SAR
#   define RIGHTSHIFT_INT16_IS_SAR
#   define RIGHTSHIFT_INT32_IS_SAR
# endif /* VC8.0 */

typedef unsigned int uint32;

# endif /* __BORLANDC__ */

typedef __int64 int64;
typedef unsigned __int64 uint64;

#endif /* __WIN32__ */
#endif /* HAVE_STDINT_H */
#endif /* snes9x_types_defined */


typedef UINT8  u8;
typedef UINT16 u16;
typedef UINT32 u32;
typedef UINT64 u64;
typedef INT8   s8;
typedef INT16  s16;
typedef INT32  s32;
typedef INT64  s64;

// from advmame
typedef UINT16 interp_uint16;
typedef UINT32 interp_uint32;

typedef UINT8 scale2x_uint8;
typedef UINT16 scale2x_uint16;
typedef UINT32 scale2x_uint32;

typedef UINT8 scale3x_uint8;
typedef UINT16 scale3x_uint16;
typedef UINT32 scale3x_uint32;

typedef UINT32 xbrz_uint32;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#ifndef bool
#define bool BOOL
#endif

#endif

