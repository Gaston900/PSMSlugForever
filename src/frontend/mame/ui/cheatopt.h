// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria, Aaron Giles, Nathan Woods
/***************************************************************************

    ui/cheatopt.h

    Internal menu for the cheat interface.

***************************************************************************/
#ifndef MAME_FRONTEND_UI_CHEATOPT_H
#define MAME_FRONTEND_UI_CHEATOPT_H

#pragma once

#include "ui/menu.h"
namespace ui {
//EKMAME
class menu_cht_Config : public menu
{
public:
	menu_cht_Config(mame_ui_manager &mui, render_container &container, bool menuless_mode);
	virtual ~menu_cht_Config() override;

	static uint32_t ui_handler(render_container &container, mame_ui_manager &mui);

private:
	virtual void populate(float &customtop, float &custombottom) override;
	virtual void handle() override;

	bool m_menuless_mode;
	bool m_hidden;
};

class menu_cheat : public menu
{
public:
	menu_cheat(mame_ui_manager &mui, render_container &container);
	virtual ~menu_cheat() override;

private:
	virtual void populate(float &customtop, float &custombottom) override;
	virtual void handle() override;
};

class menu_autofire : public menu
{
public:
	menu_autofire(mame_ui_manager &mui, render_container &container);
	virtual ~menu_autofire() override;

private:
	virtual void populate(float &customtop, float &custombottom) override;
	virtual void handle() override;

	float refresh;
	bool last_toggle;
};

#ifdef USE_CUSTOM_BUTTON
class menu_custom_button : public menu 
{
public:
	menu_custom_button(mame_ui_manager &mui, render_container &container);
	virtual ~menu_custom_button() override;
private:	
	virtual void populate(float &customtop, float &custombottom) override;
	virtual void handle() override;
};
#endif /* USE_CUSTOM_BUTTON */

} // namespace ui

#endif  /* MAME_FRONTEND_UI_CHEATOPT_H */
