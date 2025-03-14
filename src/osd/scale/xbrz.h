// ****************************************************************************
// * This file is part of the HqMAME project. It is distributed under         *
// * GNU General Public License: http://www.gnu.org/licenses/gpl.html         *
// * Copyright (C) Zenju (zenju AT gmx DOT de) - All Rights Reserved          *
// *                                                                          *
// * Additionally and as a special exception, the author gives permission     *
// * to link the code of this program with the MAME library (or with modified *
// * versions of MAME that use the same license as MAME), and distribute      *
// * linked combinations including the two. You must obey the GNU General     *
// * Public License in all respects for all of the code used other than MAME. *
// * If you modify this file, you may extend this exception to your version   *
// * of the file, but you are not obligated to do so. If you do not wish to   *
// * do so, delete this exception statement from your version.                *
// ****************************************************************************

#ifndef XBRZ_HEADER_3847894708239054
#define XBRZ_HEADER_3847894708239054

#include "port.h"
#include "xbrz_config.h"

/*
-------------------------------------------------------------------------
| xBRZ: "Scale by rules" - high quality image upscaling filter by Zenju |
-------------------------------------------------------------------------
using a modified approach of xBR:
http://board.byuu.org/viewtopic.php?f=10&t=2248
- new rule set preserving small image features
- support multithreading
- support 64 bit architectures
- support processing image slices
*/

/*
-> map source (srcWidth * srcHeight) to target (scale * width x scale * height) image, optionally processing a half-open slice of rows [yFirst, yLast) only
-> color format: ARGB (BGRA byte order), alpha channel unused
-> support for source/target pitch in bytes!
-> if your emulator changes only a few image slices during each cycle (e.g. DOSBox) then there's no need to run xBRZ on the complete image:
   Just make sure you enlarge the source image slice by 2 rows on top and 2 on bottom (this is the additional range the xBRZ algorithm is using during analysis)
   Caveat: If there are multiple changed slices, make sure they do not overlap after adding these additional rows in order to avoid a memory race condition 
   in the target image data if you are using multiple threads for processing each enlarged slice!

THREAD-SAFETY: - parts of the same image may be scaled by multiple threads as long as the [yFirst, yLast) ranges do not overlap!
               - there is a minor inefficiency for the first row of a slice, so avoid processing single rows only
*/
void xbrz_scale(size_t factor, //valid range: 2 - 5
           const xbrz_uint32* src, xbrz_uint32* trg, int srcWidth, int srcHeight,
           const XbrzScalerCfg& cfg = XbrzScalerCfg(),
           int yFirst = 0, int yLast = 0, int srcPitch = 1, int trgPitch = 1); //slice of source image

void nearestNeighborScale(const xbrz_uint32* src, int srcWidth, int srcHeight,
                          xbrz_uint32* trg, int trgWidth, int trgHeight);

enum SliceType
{
    NN_SCALE_SLICE_SOURCE,
    NN_SCALE_SLICE_TARGET,
};
void nearestNeighborScale(const xbrz_uint32* src, int srcWidth, int srcHeight, int srcPitch, //pitch in bytes!
                          xbrz_uint32* trg, int trgWidth, int trgHeight, int trgPitch,
                          SliceType st, int yFirst, int yLast);

//parameter tuning
bool equalColorTest(xbrz_uint32 col1, xbrz_uint32 col2, double luminanceWeight, double equalColorTolerance);





//########################### implementation ###########################
inline
void nearestNeighborScale(const xbrz_uint32* src, int srcWidth, int srcHeight,
                          xbrz_uint32* trg, int trgWidth, int trgHeight)
{
    nearestNeighborScale(src, srcWidth, srcHeight, srcWidth * sizeof(xbrz_uint32),
                         trg, trgWidth, trgHeight, trgWidth * sizeof(xbrz_uint32),
                         NN_SCALE_SLICE_TARGET, 0, trgHeight);
}


#endif
