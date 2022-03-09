// license:BSD-3-Clause
// copyright-holders:Chris Kirmse, Mike Haaland, René Single, Mamesick

#ifndef MUI_AUDIT_H
#define MUI_AUDIT_H

void AuditDialog(void);
void AuditRefresh(void);
intptr_t CALLBACK GameAuditDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
intptr_t CALLBACK AuditWindowProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
int MameUIVerifyRomSet(int game, bool refresh);
bool IsAuditResultYes(int audit_result);
bool IsAuditResultNo(int audit_result);

#endif
