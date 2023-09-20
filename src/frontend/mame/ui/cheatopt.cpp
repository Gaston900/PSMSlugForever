// license:BSD-3-Clause
// copyright-holders:Nicola Salmoria, Aaron Giles, Nathan Woods
/*********************************************************************

    ui/cheatopt.cpp

    Internal menu for the cheat interface.

*********************************************************************/

#include "emu.h"
#include "cheat.h"
#include "mame.h"

#include "ui/ui.h"
#include "ui/menu.h"
#include "ui/cheatopt.h"

//EKMAME
#define ARRAY_LENGTH(x)		(sizeof(x) / sizeof(x[0]))
extern void convert_command_glyphs(char *s, int buflen);

namespace ui {
// itemrefs for key menu items

#define ITEMREF_CHEATS_SET_ALL              ((void *) 0x0001)
#define ITEMREF_CHEATS_RESET_ALL            ((void *) 0x0002)
#define ITEMREF_CHEATS_RELOAD_ALL           ((void *) 0x0003)
#define ITEMREF_CHEATS_AUTOFIRE_SETTINGS    ((void *) 0x0004)
#define ITEMREF_CHEATS_FIRST_ITEM           ((void *) 0x0005)

// itemrefs for key menu items
#define ITEMREF_AUTOFIRE_STATUS       ((void *) 0x0001)
#define ITEMREF_AUTOFIRE_DELAY        ((void *) 0x0002)
#define ITEMREF_AUTOFIRE_FIRST_BUTTON ((void *) 0x0003)


/*-------------------------------------------------
    menu_cheat - handle the cheat menu
-------------------------------------------------*/

void menu_cheat::handle()
{
	/* process the menu */
	const event *menu_event = process(PROCESS_LR_REPEAT);


	/* handle events */
	if (menu_event != nullptr && menu_event->itemref != nullptr)
	{
		bool changed = false;

		/* clear cheat comment on any movement or keypress */
		machine().popmessage();

		/* handle reset all + reset all cheats for reload all option */
		if ((menu_event->itemref == ITEMREF_CHEATS_RESET_ALL || menu_event->itemref == ITEMREF_CHEATS_RELOAD_ALL) && menu_event->iptkey == IPT_UI_SELECT)
		{
			for (auto &curcheat : mame_machine_manager::instance()->cheat().entries())
				if (curcheat->select_default_state())
					changed = true;
		}
		else if ((menu_event->itemref == ITEMREF_CHEATS_SET_ALL)&& menu_event->iptkey == IPT_UI_SELECT)
		{
			for (auto &curcheat : mame_machine_manager::instance()->cheat().entries())
			{
					curcheat->select_next_state();
					changed = true;				
			}
		}
		/* handle individual cheats */
		else if (menu_event->itemref >= ITEMREF_CHEATS_FIRST_ITEM)
		{
			cheat_entry *curcheat = reinterpret_cast<cheat_entry *>(menu_event->itemref);
			const char *string;
			switch (menu_event->iptkey)
			{
				/* if selected, activate a oneshot */
				case IPT_UI_SELECT:
					changed = curcheat->activate();
					break;

				/* if cleared, reset to default value */
				case IPT_UI_CLEAR:
					changed = curcheat->select_default_state();
					break;

				/* left decrements */
				case IPT_UI_LEFT:
					changed = curcheat->select_previous_state();
					break;

				/* right increments */
				case IPT_UI_RIGHT:
					changed = curcheat->select_next_state();
					break;

				/* bring up display comment if one exists */
				case IPT_UI_DISPLAY_COMMENT:
				case IPT_UI_UP:
				case IPT_UI_DOWN:
					string = curcheat->comment();
					if (string != nullptr && string[0] != 0)
						machine().popmessage(_("Cheat Comment:\n%s"), string);
					break;
			}
		}

		/* handle reload all  */
		if (menu_event->itemref == ITEMREF_CHEATS_RELOAD_ALL && menu_event->iptkey == IPT_UI_SELECT)
		{
			/* re-init cheat engine and thus reload cheats/cheats have already been turned off by here */
			mame_machine_manager::instance()->cheat().reload();

			/* display the reloaded cheats */
			reset(reset_options::REMEMBER_REF);
			machine().popmessage(_("All cheats reloaded"));
		}

		/* handle autofire menu */
		if (menu_event->itemref == ITEMREF_CHEATS_AUTOFIRE_SETTINGS && menu_event->iptkey == IPT_UI_SELECT)
		{
			menu::stack_push<menu_autofire>(ui(), container());
		}

		/* if things changed, update */
		if (changed)
			reset(reset_options::REMEMBER_REF);
	}
}


/*-------------------------------------------------
    menu_cheat_populate - populate the cheat menu
-------------------------------------------------*/

menu_cheat::menu_cheat(mame_ui_manager &mui, render_container &container) : menu(mui, container)
{
}

void menu_cheat::populate(float &customtop, float &custombottom)
{
	/* iterate over cheats */
	std::string text;
	std::string subtext;

	// add the autofire menu
	item_append(_("Autofire Settings"), "", 0, (void *)ITEMREF_CHEATS_AUTOFIRE_SETTINGS);

	/* add a separator */
	item_append(menu_item_type::SEPARATOR);

	// add other cheats
	if (!mame_machine_manager::instance()->cheat().entries().empty()) {
		for (auto &curcheat : mame_machine_manager::instance()->cheat().entries())
		{
			uint32_t flags;
			curcheat->menu_text(text, subtext, flags);
			if (text == MENU_SEPARATOR_ITEM)
				item_append(menu_item_type::SEPARATOR, flags);
			else
				item_append(text, subtext, flags, curcheat.get());
		}

		/* add a separator */
		item_append(menu_item_type::SEPARATOR);

		/* add a set all option */
		item_append(_("Set All"), "", 0, (void *)ITEMREF_CHEATS_SET_ALL);
		
		/* add a reset all option */
		item_append(_("Reset All"), "", 0, (void *)ITEMREF_CHEATS_RESET_ALL);

		/* add a reload all cheats option */
		item_append(_("Reload All"), "", 0, (void *)ITEMREF_CHEATS_RELOAD_ALL);
	}
}

menu_cheat::~menu_cheat()
{
}

/*-------------------------------------------------
    menu_autofire - handle the autofire settings
    menu
-------------------------------------------------*/

menu_autofire::menu_autofire(mame_ui_manager &mui, render_container &container) : menu(mui, container), last_toggle(false)
{
	const screen_device *screen = screen_device_iterator(mui.machine().root_device()).first();

	if (screen == nullptr)
	{
		refresh = 60.0;
	}
	else
	{
		refresh = ATTOSECONDS_TO_HZ(screen->refresh_attoseconds());
	}
}

menu_autofire::~menu_autofire()
{
}

void menu_autofire::handle()
{
	ioport_field *field;
	bool changed = false;

	/* process the menu */
	const event *menu_event = process(0);

	/* handle events */
	if (menu_event != nullptr && menu_event->itemref != nullptr)
	{
		// menu item is changed using left/right keys only
		if (menu_event->iptkey == IPT_UI_LEFT || menu_event->iptkey == IPT_UI_RIGHT)
		{
			if (menu_event->itemref == ITEMREF_AUTOFIRE_STATUS)
			{
				// toggle autofire status
				bool autofire_toggle = machine().ioport().get_autofire_toggle();    // (menu_event->iptkey == IPT_UI_LEFT);
				machine().ioport().set_autofire_toggle(!autofire_toggle);
				changed = true;
			}
			else if (menu_event->itemref == ITEMREF_AUTOFIRE_DELAY)
			{
				// change autofire frequency
				int autofire_delay = machine().ioport().get_autofire_delay();
				if (menu_event->iptkey == IPT_UI_LEFT)
				{
					autofire_delay--;
					if (autofire_delay < 1)
						autofire_delay = 1;
				}
				else
				{
					autofire_delay++;
					if (autofire_delay > 30)
						autofire_delay = 30;
				}
				machine().ioport().set_autofire_delay(autofire_delay);
				changed = true;
			}
			else
			{
				// enable autofire on specific button
				field = (ioport_field *)menu_event->itemref;
				ioport_field::user_settings settings;
				field->get_user_settings(settings);
				settings.autofire = (menu_event->iptkey == IPT_UI_RIGHT);
				field->set_user_settings(settings);
				changed = true;
			}
		}
	}

	// if toggle settings changed, redraw menu to reflect new options
	if (!changed)
	{
		changed = (last_toggle != machine().ioport().get_autofire_toggle());
	}

	/* if something changed, rebuild the menu */
	if (changed)
	{
		reset(reset_options::REMEMBER_REF);
	}
}


/*-------------------------------------------------
    menu_autofire_populate - populate the autofire
    menu
-------------------------------------------------*/

void menu_autofire::populate(float &customtop, float &custombottom)
{
	char temp_text[64];

	/* add autofire toggle item */
	bool autofire_toggle = machine().ioport().get_autofire_toggle();
	item_append(_("Autofire Status"), (autofire_toggle ? _("Disabled") : _("Enabled")),
			(autofire_toggle ? FLAG_RIGHT_ARROW : FLAG_LEFT_ARROW), (void *)ITEMREF_AUTOFIRE_STATUS);

	/* iterate over the input ports and add autofire toggle items */
	int menu_items = 0;
	for (auto &port : machine().ioport().ports())
	{
		bool is_first_button = true;
		for (ioport_field &field : port.second->fields())
		{
			if (field.type() >= IPT_BUTTON1 && field.type() <= IPT_BUTTON16)
			{
				menu_items++;
				ioport_field::user_settings settings;
				field.get_user_settings(settings);

				if (is_first_button)
				{
					/* add a separator for each player */
					item_append(menu_item_type::SEPARATOR);
					is_first_button = false;
				}

				/* add an autofire item */
				char commandbuf[1024];
				strcpy(commandbuf, field.name());
				convert_command_glyphs(commandbuf ,ARRAY_LENGTH(commandbuf));// EKMAME

				item_append_on_off(commandbuf, settings.autofire, (autofire_toggle ? FLAG_DISABLE | FLAG_INVERT : 0), (void *)&field);
			}
		}
	}

	/* add text item if no buttons found */
	if (menu_items==0)
	{
		item_append(menu_item_type::SEPARATOR);
		item_append(_("No buttons found on this machine!"), "", FLAG_DISABLE, nullptr);
	}

	/* add a separator */
	item_append(menu_item_type::SEPARATOR);

	/* add autofire delay item */
	int value = machine().ioport().get_autofire_delay();
	snprintf(temp_text, ARRAY_LENGTH(temp_text), "%d = %.2f Hz", value, (float)refresh/value);
	if (!autofire_toggle)
	{
		item_append(_("Autofire Delay"), temp_text, FLAG_LEFT_ARROW | FLAG_RIGHT_ARROW, (void *)ITEMREF_AUTOFIRE_DELAY);
	}
	else
	{
		item_append(_("Autofire Delay"), temp_text, FLAG_DISABLE | FLAG_INVERT, nullptr);
	}

	/* add a separator */
	item_append(menu_item_type::SEPARATOR);

	last_toggle = autofire_toggle;
}

// EKMAME
/*-------------------------------------------------
    menu_cheat - handle the cheat menu
-------------------------------------------------*/

void menu_cht_Config::handle()
{
	/* process the menu */
	const event *menu_event = process(PROCESS_LR_REPEAT);

	/* handle events */
	if (menu_event != nullptr && menu_event->itemref != nullptr)
	{
		bool changed = false;

		/* clear cheat comment on any movement or keypress */
		machine().popmessage();

		/* handle reset all + reset all cheats for reload all option */
		if ((menu_event->itemref == ITEMREF_CHEATS_RESET_ALL || menu_event->itemref == ITEMREF_CHEATS_RELOAD_ALL) && menu_event->iptkey == IPT_UI_SELECT)
		{
			for (auto &curcheat : mame_machine_manager::instance()->cheat().entries())
				if (curcheat->select_default_state())
					changed = true;
		}
		else if ((menu_event->itemref == ITEMREF_CHEATS_SET_ALL)&& menu_event->iptkey == IPT_UI_SELECT)
		{
			for (auto &curcheat : mame_machine_manager::instance()->cheat().entries())
			{
					curcheat->select_next_state();
					changed = true;				
			}
		}

		/* handle individual cheats */
		else if (menu_event->itemref >= ITEMREF_CHEATS_FIRST_ITEM)
		{
			cheat_entry *curcheat = reinterpret_cast<cheat_entry *>(menu_event->itemref);
			const char *string;
			switch (menu_event->iptkey)
			{
				/* if selected, activate a oneshot */
				case IPT_UI_SELECT:
					changed = curcheat->activate();
					break;

				/* if cleared, reset to default value */
				case IPT_UI_CLEAR:
					changed = curcheat->select_default_state();
					break;

				/* left decrements */
				case IPT_UI_LEFT:
					changed = curcheat->select_previous_state();
					break;

				/* right increments */
				case IPT_UI_RIGHT:
					changed = curcheat->select_next_state();
					break;

				/* bring up display comment if one exists */
				case IPT_UI_DISPLAY_COMMENT:
				case IPT_UI_UP:
				case IPT_UI_DOWN:
					string = curcheat->comment();
					if (string != nullptr && string[0] != 0)
						machine().popmessage(_("Cheat Comment:\n%s"), string);
					break;
			}
		}

		/* handle reload all  */
		if (menu_event->itemref == ITEMREF_CHEATS_RELOAD_ALL && menu_event->iptkey == IPT_UI_SELECT)
		{
			/* re-init cheat engine and thus reload cheats/cheats have already been turned off by here */
			mame_machine_manager::instance()->cheat().reload();

			/* display the reloaded cheats */
			reset(reset_options::REMEMBER_REF);
			machine().popmessage(_("All cheats reloaded"));
		}
		
		/* handle autofire menu */
		if (menu_event->itemref == ITEMREF_CHEATS_AUTOFIRE_SETTINGS && menu_event->iptkey == IPT_UI_SELECT)
		{
			//menu::stack_push<menu_cht_autofire>(ui(), container(),true);
			menu::stack_push<menu_autofire>(ui(), container());
			//ui().menu_call_autofire();			
		}
		
		/* if things changed, update */
		if (changed)
			reset(reset_options::REMEMBER_REF);
	}
}

/*-------------------------------------------------
    menu_cheat_populate - populate the cheat menu
-------------------------------------------------*/

menu_cht_Config::menu_cht_Config(mame_ui_manager &mui, render_container &container, bool menuless_mode) : menu(mui, container)
{
	m_menuless_mode = m_hidden = menuless_mode;
}

menu_cht_Config::~menu_cht_Config()
{
}

void menu_cht_Config::populate(float &customtop, float &custombottom)
{
	/* iterate over cheats */
	std::string text;
	std::string subtext;

	// add the autofire menu
	item_append(_("Autofire Settings"), "", 0, (void *)ITEMREF_CHEATS_AUTOFIRE_SETTINGS);

	/* add a separator */
	item_append(menu_item_type::SEPARATOR);

	// add other cheats
	if (!mame_machine_manager::instance()->cheat().entries().empty()) {
		for (auto &curcheat : mame_machine_manager::instance()->cheat().entries())
		{
			uint32_t flags;
			curcheat->menu_text(text, subtext, flags);
			if (text == MENU_SEPARATOR_ITEM)
				item_append(menu_item_type::SEPARATOR, flags);
			else
				item_append(text, subtext, flags, curcheat.get());
		}

		/* add a separator */
		item_append(menu_item_type::SEPARATOR);

		/* add a set all option */
		item_append(_("Set All"), "", 0, (void *)ITEMREF_CHEATS_SET_ALL);

		/* add a reset all option */
		item_append(_("Reset All"), "", 0, (void *)ITEMREF_CHEATS_RESET_ALL);

		/* add a reload all cheats option */
		item_append(_("Reload All"), "", 0, (void *)ITEMREF_CHEATS_RELOAD_ALL);
	}
}



uint32_t menu_cht_Config::ui_handler(render_container &container, mame_ui_manager &mui)
{
	uint32_t result;
		
	// if this is the first call, push the Cheat menu
	if (topmost_menu<menu_cht_Config>(mui.machine()) == nullptr)
		menu::stack_push<menu_cht_Config>(mui, container, true);

	// handle standard menus
	result = menu::ui_handler(container, mui);

	// if we are cancelled, pop the sliders menu
	if (result == UI_HANDLER_CANCEL)
		menu::stack_pop(mui.machine());

	menu_cht_Config *uim = topmost_menu<menu_cht_Config>(mui.machine());

	return uim && uim->m_menuless_mode ? 0 : UI_HANDLER_CANCEL;
}

#ifdef USE_CUSTOM_BUTTON
/*-------------------------------------------------
	menu_custom_button - handle the custom button
	settings menu
-------------------------------------------------*/
menu_custom_button::menu_custom_button(mame_ui_manager &mui, render_container &container) : menu(mui, container)
{
}

menu_custom_button::~menu_custom_button()
{
}

void menu_custom_button::handle()
{
	const event *menu_event = process(0);
	bool changed = false;
	int custom_buttons_count = 0;

	/* handle events */
	if (menu_event != nullptr && menu_event->itemref != nullptr)
	{
		u16 *selected_custom_button = (u16 *)(uintptr_t)menu_event->itemref;
		int i;
		
		//count the number of custom buttons
		for (auto &port : machine().ioport().ports())
			for (ioport_field &field : port.second->fields())	
			{
				int type = field.type();

				if (type >= IPT_BUTTON1 && type < IPT_BUTTON1 + MAX_NORMAL_BUTTONS)
				{
					type -= IPT_BUTTON1;
					if (type >= custom_buttons_count)
						custom_buttons_count = type + 1;
				}
			}

		input_item_id id = ITEM_ID_1;
		for (i = 0; i < custom_buttons_count; i++, id++)
		{
			if (i == 9)
				id = ITEM_ID_0;

			//fixme: code_pressed_once() doesn't work well
			if (machine().input().code_pressed_once(input_code(DEVICE_CLASS_KEYBOARD, 0, ITEM_CLASS_SWITCH, ITEM_MODIFIER_NONE, id)))
			{
				*selected_custom_button ^= 1 << i;
				changed = true;
				break;
			}
		}
	}

	/* if something changed, rebuild the menu */
	if (changed)
		reset(reset_options::REMEMBER_REF);
}


/*-------------------------------------------------
	menu_custom_button_populate - populate the 
	custom button menu
-------------------------------------------------*/

void menu_custom_button::populate(float &customtop, float &custombottom)
{
	std::string subtext;
	int menu_items = 0;
	int i;

//	item_append(_("Press 1-9 to Config"), NULL, 0, NULL);
//	item_append(MENU_SEPARATOR_ITEM, NULL, 0, NULL);

	/* loop over the input ports and add autofire toggle items */
	for (auto &port : machine().ioport().ports())
		for (ioport_field &field : port.second->fields())	
		{
			int player = field.player();
			int type = field.type();
			const char *name = field.name();

			if (name != NULL && type >= IPT_CUSTOM1 && type < IPT_CUSTOM1 + MAX_CUSTOM_BUTTONS)
			{
				const char colorbutton1 = 'A';
				int n = 1;
				static char commandbuf[256];

				type -= IPT_CUSTOM1;
				subtext.assign("");

				//unpack the custom button value
				for (i = 0; i < MAX_NORMAL_BUTTONS; i++, n <<= 1)
					if (machine().ioport().m_custom_button[player][type] & n)
					{
						if (!subtext.empty())
							subtext.append("_+");
						
						if (!subtext.empty())
							subtext.append(string_format("_%c", colorbutton1 + i));
						else
							subtext = string_format("_%c", colorbutton1 + i);
					}

				strcpy(commandbuf, subtext.c_str());
				convert_command_glyphs(commandbuf ,ARRAY_LENGTH(commandbuf));
				item_append(_(name), commandbuf, 0, (void *)(uintptr_t)&machine().ioport().m_custom_button[player][type]);
				//machine().popmessage(_("custom button pressed %s %i %i",commandbuf,player,type));
				//ErrorMessageBox("custom button %s",commandbuf);
				menu_items++;
			}
		}
}
#endif /* USE_CUSTOM_BUTTON */

/*-------------------------------------------------
	menu_command - handle the command.dat
	menu
-------------------------------------------------*/


} // namespace ui
