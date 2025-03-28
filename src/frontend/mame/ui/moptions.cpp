// license:BSD-3-Clause
// copyright-holders:Maurizio Petrarota
/***************************************************************************

    ui/moptions.cpp

    UI main options manager.

***************************************************************************/

#include "emu.h"
#include "options.h"
#include "ui/moptions.h"


//**************************************************************************
//  UI EXTRA OPTIONS
//**************************************************************************

const options_entry ui_options::s_option_entries[] =
{
	// search path options
	{ nullptr,                              nullptr,                       OPTION_HEADER,  "UI SEARCH PATH OPTIONS" },
	{ OPTION_HISTORY_PATH,                  "support/history;dats;.",              OPTION_STRING,  "path to history files" },
	{ OPTION_CATEGORYINI_PATH,              "support/folders",                     OPTION_STRING,  "path to catagory ini files" },
	{ OPTION_CABINETS_PATH,                 "support/cabinets;cabdevs",            OPTION_STRING,  "path to cabinets / devices image" },
	{ OPTION_CPANELS_PATH,                  "support/cpanel",                      OPTION_STRING,  "path to control panel image" },
	{ OPTION_PCBS_PATH,                     "support/pcb",                         OPTION_STRING,  "path to pcbs image" },
	{ OPTION_FLYERS_PATH,                   "support/flyers",                      OPTION_STRING,  "path to flyers image" },
	{ OPTION_TITLES_PATH,                   "support/titles",                      OPTION_STRING,  "path to titles image" },
	{ OPTION_ENDS_PATH,                     "support/ends",                        OPTION_STRING,  "path to ends image" },
	{ OPTION_MARQUEES_PATH,                 "support/marquees",                    OPTION_STRING,  "path to marquees image" },
	{ OPTION_ARTPREV_PATH,                  "support/artpreview",                  OPTION_STRING,  "path to artwork preview image" },
	{ OPTION_BOSSES_PATH,                   "support/bosses",                      OPTION_STRING,  "path to bosses image" },
	{ OPTION_LOGOS_PATH,                    "support/logo",                        OPTION_STRING,  "path to logos image" },
	{ OPTION_SCORES_PATH,                   "support/scores",                      OPTION_STRING,  "path to scores image" },
	{ OPTION_VERSUS_PATH,                   "support/versus",                      OPTION_STRING,  "path to versus image" },
	{ OPTION_GAMEOVER_PATH,                 "support/gameover",                    OPTION_STRING,  "path to gameover image" },
	{ OPTION_HOWTO_PATH,                    "support/howto",                       OPTION_STRING,  "path to howto image" },
	{ OPTION_SELECT_PATH,                   "support/select",                      OPTION_STRING,  "path to select image" },
	{ OPTION_ICONS_PATH,                    "support/icons",                       OPTION_STRING,  "path to ICOns image" },
	{ OPTION_COVER_PATH,                    "support/covers",                      OPTION_STRING,  "path to software cover image" },
	{ OPTION_UI_PATH,                       "config/ui",                           OPTION_STRING,  "path to UI files" },

	// misc options
	{ nullptr,                              nullptr,    OPTION_HEADER,      "UI MISC OPTIONS" },
	{ OPTION_REMEMBER_LAST,                 "1",        OPTION_BOOLEAN,     "reselect in main menu last played game" },
	{ OPTION_ENLARGE_SNAPS,                 "1",        OPTION_BOOLEAN,     "enlarge arts (snapshot, title, etc...) in right panel (keeping aspect ratio)" },
	{ OPTION_FORCED4X3,                     "1",        OPTION_BOOLEAN,     "force the appearance of the snapshot in the list software to 4:3" },
	{ OPTION_USE_BACKGROUND,                "1",        OPTION_BOOLEAN,     "enable background image in main view" },
	{ OPTION_SKIP_BIOS_MENU,                "1",        OPTION_BOOLEAN,     "skip bios submenu, start with configured or default" },
	{ OPTION_SKIP_PARTS_MENU,               "0",        OPTION_BOOLEAN,     "skip parts submenu, start with first part" },
	{ OPTION_LAST_USED_FILTER,              "",         OPTION_STRING,      "latest used filter" },
	{ OPTION_LAST_RIGHT_PANEL "(0-1)",      "0",        OPTION_INTEGER,     "latest right panel focus" },
	{ OPTION_LAST_USED_MACHINE,             "",         OPTION_STRING,      "latest used machine" },
	{ OPTION_INFO_AUTO_AUDIT,               "0",        OPTION_BOOLEAN,     "enable auto audit in the general info panel" },
	{ OPTION_HIDE_ROMLESS,                  "1",        OPTION_BOOLEAN,     "hide romless machine from available list" },

	// UI options
	{ nullptr,                              nullptr,        OPTION_HEADER,      "UI OPTIONS" },
	{ OPTION_INFOS_SIZE "(0.05-1.00)",      "0.75",         OPTION_FLOAT,       "UI right panel infos text size (0.05 - 1.00)" },
	{ OPTION_FONT_ROWS "(25-40)",           "30",           OPTION_INTEGER,     "UI font lines per screen (25 - 40)" },
	{ OPTION_HIDE_PANELS "(0-3)",           "0",            OPTION_INTEGER,     "UI hide left/right panel in main view (0 = Show all, 1 = hide left, 2 = hide right, 3 = hide both" },
	{ OPTION_UI_BORDER_COLOR,               "ffffffff",     OPTION_STRING,      "UI border color (ARGB)" },
	{ OPTION_UI_BACKGROUND_COLOR,           "ef101030",     OPTION_STRING,      "UI background color (ARGB)" },
	{ OPTION_UI_CLONE_COLOR,                "ff808080",     OPTION_STRING,      "UI clone color (ARGB)" },
	{ OPTION_UI_DIPSW_COLOR,                "ffffff00",     OPTION_STRING,      "UI dipswitch color (ARGB)" },
	{ OPTION_UI_GFXVIEWER_BG_COLOR,         "ef101030",     OPTION_STRING,      "UI gfx viewer color (ARGB)" },
	{ OPTION_UI_MOUSEDOWN_BG_COLOR,         "b0606000",     OPTION_STRING,      "UI mouse down bg color (ARGB)" },
	{ OPTION_UI_MOUSEDOWN_COLOR,            "ffffff80",     OPTION_STRING,      "UI mouse down color (ARGB)" },
	{ OPTION_UI_MOUSEOVER_BG_COLOR,         "70404000",     OPTION_STRING,      "UI mouse over bg color (ARGB)" },
	{ OPTION_UI_MOUSEOVER_COLOR,            "ffffff80",     OPTION_STRING,      "UI mouse over color (ARGB)" },
	{ OPTION_UI_SELECTED_BG_COLOR,          "ef808000",     OPTION_STRING,      "UI selected bg color (ARGB)" },
	{ OPTION_UI_SELECTED_COLOR,             "ffffff00",     OPTION_STRING,      "UI selected color (ARGB)" },
	{ OPTION_UI_SLIDER_COLOR,               "ffffffff",     OPTION_STRING,      "UI slider color (ARGB)" },
	{ OPTION_UI_SUBITEM_COLOR,              "ffffffff",     OPTION_STRING,      "UI subitem color (ARGB)" },
	{ OPTION_UI_TEXT_BG_COLOR,              "ef000000",     OPTION_STRING,      "UI text bg color (ARGB)" },
	{ OPTION_UI_TEXT_COLOR,                 "ffffffff",     OPTION_STRING,      "UI text color (ARGB)" },
	{ OPTION_UI_UNAVAILABLE_COLOR,          "ff404040",     OPTION_STRING,      "UI unavailable color (ARGB)" },
	{ nullptr }
};
#if 0
	{ OPTION_UI_BORDER_COLOR,               "ffffffff",     OPTION_STRING,      "UI border color (ARGB)" },
	{ OPTION_UI_BACKGROUND_COLOR,           "ef101030",     OPTION_STRING,      "UI background color (ARGB)" },
	{ OPTION_UI_CLONE_COLOR,                "ff808080",     OPTION_STRING,      "UI clone color (ARGB)" },
	{ OPTION_UI_DIPSW_COLOR,                "ffffff00",     OPTION_STRING,      "UI dipswitch color (ARGB)" },
	{ OPTION_UI_GFXVIEWER_BG_COLOR,         "ef101030",     OPTION_STRING,      "UI gfx viewer color (ARGB)" },
	{ OPTION_UI_MOUSEDOWN_BG_COLOR,         "b0606000",     OPTION_STRING,      "UI mouse down bg color (ARGB)" },
	{ OPTION_UI_MOUSEDOWN_COLOR,            "ffffff80",     OPTION_STRING,      "UI mouse down color (ARGB)" },
	{ OPTION_UI_MOUSEOVER_BG_COLOR,         "70404000",     OPTION_STRING,      "UI mouse over bg color (ARGB)" },
	{ OPTION_UI_MOUSEOVER_COLOR,            "ffffff80",     OPTION_STRING,      "UI mouse over color (ARGB)" },
	{ OPTION_UI_SELECTED_BG_COLOR,          "ef808000",     OPTION_STRING,      "UI selected bg color (ARGB)" },
	{ OPTION_UI_SELECTED_COLOR,             "ffffff00",     OPTION_STRING,      "UI selected color (ARGB)" },
	{ OPTION_UI_SLIDER_COLOR,               "ff22b14c",     OPTION_STRING,      "UI slider color (ARGB)" },
	{ OPTION_UI_SUBITEM_COLOR,              "ffFF9900",     OPTION_STRING,      "UI subitem color (ARGB)" },
	{ OPTION_UI_TEXT_BG_COLOR,              "ef000000",     OPTION_STRING,      "UI text bg color (ARGB)" },
	{ OPTION_UI_TEXT_COLOR,                 "ffffffff",     OPTION_STRING,      "UI text color (ARGB)" },
	{ OPTION_UI_UNAVAILABLE_COLOR,          "ff404040",     OPTION_STRING,      "UI unavailable color (ARGB)" },

#endif
//-------------------------------------------------
//  ui_options - constructor
//-------------------------------------------------

ui_options::ui_options() : core_options()
{
	add_entries(ui_options::s_option_entries);
}

//-------------------------------------------------
//  rgb_value - decode an RGB option
//-------------------------------------------------

rgb_t ui_options::rgb_value(const char *option) const
{
	// find the entry
	core_options::entry::shared_const_ptr entry = get_entry(option);

	// look up the value, and sanity check the result
	const char *value = entry->value();
	int len = strlen(value);
	if (len != 8)
		value = entry->default_value().c_str();

	// convert to an rgb_t
	return rgb_t((uint32_t)strtoul(value, nullptr, 16));
}
