//============================================================
//
//  drawgdd.h - Win32 direct draw drawing
//
//============================================================

#pragma once

#ifndef __DRAWDRAW__
#define __DRAWDRAW__

// standard windows headers
//#include <windows.h>
#include <ddraw.h>

// MAME headers

// MAMEOS headers
#include "window.h"

struct direct_draw_callback
{
	osd_renderer *(*create)(std::shared_ptr<osd_window> window);
	void (*exit)(void);
};

//============================================================
//  TYPE DEFINITIONS
//============================================================

/* dd_info is the information about DirectDraw for the current screen */
class renderer_dd : public osd_renderer
{
public:
	renderer_dd(std::shared_ptr<osd_window> window)
	: osd_renderer(window, FLAG_NONE),
		width(0),
		height(0),
		refresh(0),
		adapter_ptr(nullptr),
		clearouter(0),
		blitwidth(0), blitheight(0),
		//lastdest
		ddraw(nullptr),
		primary(nullptr),
		back(nullptr),
		blit(nullptr),
		clipper(nullptr),
		gamma(nullptr),
		membuffer(nullptr),
		membuffersize(0)
	{ }

	virtual ~renderer_dd();
	static bool init(running_machine &machine); 
	static void exit();

	virtual int create() override;
	virtual render_primitive_list *get_primitives() override;
	virtual int draw(const int update) override;
	virtual void save() override {};
	virtual void record() override {};
	virtual void toggle_fsfx() override {};
	virtual void destroy();

	int                     width, height;              // current width, height
	int                     refresh;                    // current refresh rate

private:

	inline void update_outer_rects();

	// surface management
	int ddraw_create();
	int ddraw_create_surfaces();
	void ddraw_delete();
	void ddraw_delete_surfaces();
	int ddraw_verify_caps();
	int ddraw_test_cooperative();
	HRESULT create_surface(DDSURFACEDESC2 *desc, IDirectDrawSurface7 **surface, const char *type);
	int create_clipper();

	// drawing helpers
	void compute_blit_surface_size();
	void blit_to_primary(int srcwidth, int srcheight);

	// video modes
	int config_adapter_mode();
	void get_adapter_for_monitor(osd_monitor_info *monitor);
	void pick_best_mode();

	// various
	void calc_fullscreen_margins(DWORD desc_width, DWORD desc_height, RECT *margins);


	GUID                    adapter;                    // current display adapter
	GUID *                  adapter_ptr;                // pointer to current display adapter
	int                     clearouter;                 // clear the outer areas?

	INT32                   blitwidth, blitheight;      // current blit width/height values
	RECT                    lastdest;                   // last destination rectangle

	IDirectDraw7 *          ddraw;                      // pointer to the DirectDraw object
	IDirectDrawSurface7 *   primary;                    // pointer to the primary surface object
	IDirectDrawSurface7 *   back;                       // pointer to the back buffer surface object
	IDirectDrawSurface7 *   blit;                       // pointer to the blit surface object
	IDirectDrawClipper *    clipper;                    // pointer to the clipper object
	IDirectDrawGammaControl *gamma;                     // pointer to the gamma control object

	DDSURFACEDESC2          primarydesc;                // description of the primary surface
	DDSURFACEDESC2          blitdesc;                   // description of the blitting surface
	DDSURFACEDESC2          origmode;                   // original video mode

	DDCAPS                  ddcaps;                     // capabilities of the device
	DDCAPS                  helcaps;                    // capabilities of the hardware

	UINT8 *                 membuffer;                  // memory buffer for complex rendering
	unsigned int            membuffersize;              // current size of the memory buffer
};


#endif // __DRAWDRAW__

