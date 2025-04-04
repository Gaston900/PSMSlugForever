// license:BSD-3-Clause
// copyright-holders:Aaron Giles
//============================================================
//
//  video.cpp - Win32 video handling
//
//============================================================

// standard windows headers
#include <windows.h>

// MAME headers
#include "emu.h"
#include "emuopts.h"
#include "render.h"
#include "uiinput.h"

// MAMEOS headers
#include "winmain.h"
#include "window.h"
#include "strconv.h"

#include "modules/osdwindow.h"
//#ifdef USE_SCALE_EFFECTS
#include "scale/osdscale.h"
//#endif /* USE_SCALE_EFFECTS */

//============================================================
//  CONSTANTS
//============================================================


//============================================================
//  GLOBAL VARIABLES
//============================================================

osd_video_config video_config;

//============================================================
//  LOCAL VARIABLES
//============================================================

//#ifdef USE_SCALE_EFFECTS
static int cur_scale_xsize;
static int cur_scale_ysize;
//#endif /* USE_SCALE_EFFECTS */

//============================================================
//  PROTOTYPES
//============================================================

static void get_resolution(const char *defdata, const char *data, osd_window_config *config, int report_error);


//============================================================
//  video_init
//============================================================

// FIXME: Temporary workaround
static osd_window_config   windows[MAX_VIDEO_WINDOWS];        // configuration data per-window

bool windows_osd_interface::video_init()
{
	// extract data from the options
	extract_video_config();

	// initialize the window system so we can make windows
	window_init();

	// create the windows
	auto &options = downcast<windows_options &>(machine().options());
	for (int index = 0; index < video_config.numscreens; index++)
	{
		win_window_info::create(machine(), index, m_monitor_module->pick_monitor(options, index), &windows[index]);
	}

	if (video_config.mode != VIDEO_MODE_NONE)
		SetForegroundWindow(std::static_pointer_cast<win_window_info>(osd_common_t::s_window_list.front())->platform_window());

	return true;
}

//============================================================
//  video_exit
//============================================================

void windows_osd_interface::video_exit()
{
	window_exit();
}

//============================================================
//  update
//============================================================

void windows_osd_interface::update(bool skip_redraw)
{
	osd_common_t::update(skip_redraw);

	// if we're not skipping this redraw, update all windows
	if (!skip_redraw)
	{
//#ifdef USE_SCALE_EFFECTS
		extern int win_scale_res_changed;
		win_scale_res_changed = 0;

		if (scale_effect.xsize != cur_scale_xsize || scale_effect.ysize != cur_scale_ysize)
		{
			win_scale_res_changed = 1;
			cur_scale_xsize = scale_effect.xsize;
			cur_scale_ysize = scale_effect.ysize;
		}
//#endif /* USE_SCALE_EFFECTS */	
//      profiler_mark(PROFILER_BLIT);
		for (const auto &window : osd_common_t::s_window_list)
			window->update();
//      profiler_mark(PROFILER_END);
	}

	// if we're running, disable some parts of the debugger
	if ((machine().debug_flags & DEBUG_FLAG_OSD_ENABLED) != 0)
		debugger_update();
}


//============================================================
//  input_update
//============================================================

void windows_osd_interface::input_update()
{
	// poll the joystick values here
	winwindow_process_events(machine(), true, false);
	poll_input(machine());
	check_osd_inputs();
}

//============================================================
//  check_osd_inputs
//============================================================

void windows_osd_interface::check_osd_inputs()
{
	// check for toggling fullscreen mode
	if (machine().ui_input().pressed(IPT_OSD_1))
		winwindow_toggle_full_screen();

	// check for taking fullscreen snap
	if (machine().ui_input().pressed(IPT_OSD_2))
		winwindow_take_snap();

	// check for taking fullscreen video
	if (machine().ui_input().pressed(IPT_OSD_3))
		winwindow_take_video();

	// check for taking fullscreen video
	if (machine().ui_input().pressed(IPT_OSD_4))
		winwindow_toggle_fsfx();
}



//============================================================
//  extract_video_config
//============================================================

void windows_osd_interface::extract_video_config()
{
	const char *stemp;
//#ifdef USE_SCALE_EFFECTS
	stemp = options().value(OPTION_SCALE_EFFECT);

	if (stemp)
	{
		scale_decode(stemp);

		if (scale_effect.effect)
			osd_printf_verbose("Using %s scale effect\n", scale_name(scale_effect.effect));
	}
//#endif /* USE_SCALE_EFFECTS */

	// global options: extract the data
	video_config.windowed      = options().window();
	video_config.prescale      = options().prescale();
	video_config.filter        = options().filter();
	video_config.keepaspect    = options().keep_aspect();
	video_config.numscreens    = options().numscreens();

	// if we are in debug mode, never go full screen
	if (machine().debug_flags & DEBUG_FLAG_OSD_ENABLED)
		video_config.windowed = TRUE;

	// per-window options: extract the data
	const char *default_resolution = options().resolution();
	get_resolution(default_resolution, options().resolution(0), &windows[0], TRUE);
	get_resolution(default_resolution, options().resolution(1), &windows[1], TRUE);
	get_resolution(default_resolution, options().resolution(2), &windows[2], TRUE);
	get_resolution(default_resolution, options().resolution(3), &windows[3], TRUE);

	// video options: extract the data
	stemp = options().video();
	if (strcmp(stemp, "d3d") == 0)
		video_config.mode = VIDEO_MODE_D3D;
	else if (strcmp(stemp, "auto") == 0)
		video_config.mode = VIDEO_MODE_D3D;
	else if (strcmp(stemp, "ddraw") == 0)			// DDRAW
		video_config.mode = VIDEO_MODE_DDRAW;	
	else if (strcmp(stemp, "gdi") == 0)
		video_config.mode = VIDEO_MODE_GDI;
	else if (strcmp(stemp, "bgfx") == 0)
		video_config.mode = VIDEO_MODE_BGFX;
	else if (strcmp(stemp, "none") == 0)
	{
		video_config.mode = VIDEO_MODE_NONE;
		if (!emulator_info::standalone() && options().seconds_to_run() == 0)
			osd_printf_warning("Warning: -video none doesn't make much sense without -seconds_to_run\n");
	}
#if (USE_OPENGL)
	else if (strcmp(stemp, "opengl") == 0)
		video_config.mode = VIDEO_MODE_OPENGL;
#endif
	else
	{
		osd_printf_warning("Invalid video value %s; reverting to gdi\n", stemp);
		video_config.mode = VIDEO_MODE_GDI;
	}
	video_config.waitvsync     = options().wait_vsync();
	video_config.syncrefresh   = options().sync_refresh();
	video_config.triplebuf     = options().triple_buffer();
	video_config.switchres     = options().switch_res();

	// ddraw options: extract the data
	video_config.hwstretch     = options().hwstretch();// DDRAW

	if (video_config.prescale < 1 || video_config.prescale > 8)
	{
		osd_printf_warning("Invalid prescale option, reverting to '1'\n");
		video_config.prescale = 1;
	}
	#if (USE_OPENGL)
		// default to working video please
		video_config.forcepow2texture = options().gl_force_pow2_texture();
		video_config.allowtexturerect = !(options().gl_no_texture_rect());
		video_config.vbo         = options().gl_vbo();
		video_config.pbo         = options().gl_pbo();
		video_config.glsl        = options().gl_glsl();
		video_config.glsl_sync	 = options().glsl_sync();
		if ( video_config.glsl )
		{
			int i;
			const char *glsl_dir = options().glsl_path();

			video_config.glsl_filter = options().glsl_filter();

			video_config.glsl_shader_mamebm_num=0;

			for(i=0; i<GLSL_SHADER_MAX; i++)
			{
				stemp = options().shader_mame(i);
				if (stemp && strcmp(stemp, OSDOPTVAL_NONE) != 0 && strlen(stemp)>0)
				{
					video_config.glsl_shader_mamebm[i] = (char *)malloc(strlen(stemp)+strlen(glsl_dir)+2);
					sprintf(video_config.glsl_shader_mamebm[i], "%s%s%s", glsl_dir, PATH_SEPARATOR, stemp);
					video_config.glsl_shader_mamebm_num++;
				} else {
					video_config.glsl_shader_mamebm[i] = nullptr;
				}
			}

			video_config.glsl_shader_scrn_num=0;

			for(i=0; i<GLSL_SHADER_MAX; i++)
			{
				stemp = options().shader_screen(i);
				if (stemp && strcmp(stemp, OSDOPTVAL_NONE) != 0 && strlen(stemp)>0)
				{
					video_config.glsl_shader_scrn[i] = (char *)malloc(strlen(stemp)+strlen(glsl_dir)+2);
					sprintf(video_config.glsl_shader_scrn[i], "%s%s%s", glsl_dir, PATH_SEPARATOR, stemp);
					video_config.glsl_shader_scrn_num++;
				} else {
					video_config.glsl_shader_scrn[i] = nullptr;
				}
			}
		} else {
			int i;
			video_config.glsl_filter = 0;
			video_config.glsl_shader_mamebm_num=0;
			for(i=0; i<GLSL_SHADER_MAX; i++)
			{
				video_config.glsl_shader_mamebm[i] = nullptr;
			}
			video_config.glsl_shader_scrn_num=0;
			for(i=0; i<GLSL_SHADER_MAX; i++)
			{
				video_config.glsl_shader_scrn[i] = nullptr;
			}
		}

	#endif /* USE_OPENGL */

}


//============================================================
//  get_resolution
//============================================================

static void get_resolution(const char *defdata, const char *data, osd_window_config *config, int report_error)
{
	config->width = config->height = config->depth = config->refresh = 0;
	if (strcmp(data, OSDOPTVAL_AUTO) == 0)
	{
		if (strcmp(defdata, OSDOPTVAL_AUTO) == 0)
			return;
		data = defdata;
	}

	if (sscanf(data, "%dx%dx%d", &config->width, &config->height, &config->depth) < 2 && report_error)
		osd_printf_error("Illegal resolution value = %s\n", data);

	const char * at_pos = strchr(data, '@');
	if (at_pos)
		if (sscanf(at_pos + 1, "%d", &config->refresh) < 1 && report_error)
			osd_printf_error("Illegal refresh rate in resolution value = %s\n", data);
}
