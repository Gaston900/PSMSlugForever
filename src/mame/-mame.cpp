// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    mame.c

    Specific (per target) constants

****************************************************************************/

#include "emu.h"

#define APPNAME                 "PSMAME PLUS (METAL SLUG FOREVER SPECIAL EDITION FINAL)"
#define APPNAME_LOWER           "PSMAME PLUS (METAL SLUG FOREVER SPECIAL EDITION FINAL)"
#define CONFIGNAME              "PSMame Plus"
#define COPYRIGHT               "Copyright Gaston90\nand the HBMAME team\nhttp://psarcadeplus.blogspot.com"
#define COPYRIGHT_INFO          "Copyright Gaston90 and the PSMAMEPLUS"

const char * emulator_info::get_appname() { return APPNAME;}
const char * emulator_info::get_appname_lower() { return APPNAME_LOWER;}
const char * emulator_info::get_configname() { return CONFIGNAME;}
const char * emulator_info::get_copyright() { return COPYRIGHT;}
const char * emulator_info::get_copyright_info() { return COPYRIGHT_INFO;}
