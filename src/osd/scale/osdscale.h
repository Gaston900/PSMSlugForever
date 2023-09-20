/***************************************************************************

    osdscale.h

    OS-scale code interface.

    This is an unofficial version based on MAME.
    Please do not send any reports from this build to the MAME team.

***************************************************************************/

#ifndef __OSDSCALE_H__
#define __OSDSCALE_H__


//============================================================
//	GLOBAL VARIABLES
//============================================================

struct scale_effect
{
	int effect;
	int xsize;
	int ysize;
	const char *name;
};

extern struct scale_effect scale_effect;



//============================================================
//	PROTOTYPES
//============================================================

int scale_init(void);
int scale_exit(void);
int scale_check(int depth);
int scale_perform_scale(UINT8 *src, UINT8 *dst, int src_pitch, int dst_pitch, int width, int height, int depth, int update, int bank);
int scale_decode(const char *arg);
const char *scale_name(int effect);
const char *scale_desc(int effect);

#endif
