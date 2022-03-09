// license:BSD-3-Clause
// copyright-holders:Chris Kirmse, Mike Haaland, René Single, Mamesick

#ifndef DIALOGS_H
#define DIALOGS_H

#define FILTERTEXT_LEN  256
#define NUM_EXCLUSIONS  10
#define NUMHISTORYTAB   WINUI_ARRAY_LENGTH(g_ComboBoxHistoryTab)

const char * GetFilterText(void);
intptr_t CALLBACK ResetDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
intptr_t CALLBACK InterfaceDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
intptr_t CALLBACK FilterDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
intptr_t CALLBACK AboutDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
intptr_t CALLBACK AddCustomFileDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

#endif
