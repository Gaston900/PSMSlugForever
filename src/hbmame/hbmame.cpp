// license:BSD-3-Clause
// copyright-holders:Robbbert
/***************************************************************************

    hbmame.c

    Specific (per target) constants

****************************************************************************/

#include "emu.h"

#define APPNAME             "PSMAME PLUS (Special Edition)"
#define APPNAME_LOWER       "PSMAME PLUS (Special Edition)"
#define CONFIGNAME          "PSMame Plus"
#define COPYRIGHT           "Copyright Gaston90\nand the MAME team\nhttp://psarcadeplus.blogspot.com"
#define COPYRIGHT_INFO      "\nMAME portions are copyright the MAME team.\n" \
                            "PSMame Plus portions are copyright Gaston90."
							

const char * emulator_info::get_appname() { return APPNAME;}
const char * emulator_info::get_appname_lower() { return APPNAME_LOWER;}
const char * emulator_info::get_configname() { return CONFIGNAME;}
const char * emulator_info::get_copyright() { return COPYRIGHT;}
const char * emulator_info::get_copyright_info() { return COPYRIGHT_INFO;}
