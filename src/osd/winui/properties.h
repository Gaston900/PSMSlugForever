// license:BSD-3-Clause
// copyright-holders:Chris Kirmse, Mike Haaland, René Single, Mamesick

#ifndef PROPERTIES_H
#define PROPERTIES_H

#define MAX_SCREENS				4
#define SHEET_TREE_WIDTH 		180
#define NUMPAGES 				WINUI_ARRAY_LENGTH(g_PropSheets)
#define NUMVIDEO 				WINUI_ARRAY_LENGTH(g_ComboBoxVideo)
#define NUMSOUND 				WINUI_ARRAY_LENGTH(g_ComboBoxSound)
#define NUMSAMPLERATE 			WINUI_ARRAY_LENGTH(g_ComboBoxSampleRate)
#define NUMSELECTSCREEN 		WINUI_ARRAY_LENGTH(g_ComboBoxSelectScreen)
#define NUMVIEW 				WINUI_ARRAY_LENGTH(g_ComboBoxView)
#define NUMFRAMESKIP 			WINUI_ARRAY_LENGTH(g_ComboBoxFrameSkip)
#define NUMDEVICES 				WINUI_ARRAY_LENGTH(g_ComboBoxDevice)
#define NUMSNAPNAME 			WINUI_ARRAY_LENGTH(g_ComboBoxSnapName)
#define NUMSNAPVIEW 			WINUI_ARRAY_LENGTH(g_ComboBoxSnapView)
#define NUMGLSLFILTER 			WINUI_ARRAY_LENGTH(g_ComboBoxGLSLFilter)

#define NUMSELECTVIDEOMODE 		WINUI_ARRAY_LENGTH(g_ComboBoxVideo)

#define NUMSCALEEFFECTS			18
/* Called in winui.c to create the property page */
void InitPropertyPage(HINSTANCE hInst, HWND hWnd, OPTIONS_TYPE opt_type, int folder_id, int game_num);
intptr_t CALLBACK GamePropertiesDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif
