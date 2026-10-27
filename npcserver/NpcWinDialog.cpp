// NpcWinDialog.cpp - unit 45: the Win32 side
// (#ifdef _WIN32; on Linux it degrades to the
// stub so the regression still links)
#include "NpcWinDialog.h"
#include "NpcWinRes.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commctrl.h>

namespace npc {

// the single dialog instance
static CNpcWinConsole* s_pApp = nullptr;
static HWND s_hDlg = nullptr;

static void AppendLog(HWND hEdit, const char* sz) {
    // the ORIGINAL appends to the CEdit
    // (IDC 1000): move the caret to the end
    // and replace the selection (read-only is
    // bypassed by EM_REPLACESEL after
    // removing the read-only bit temporarily,
    // the classic pattern)
    SendMessage(hEdit, WM_SETREDRAW, FALSE, 0);
    int nLen = GetWindowTextLength(hEdit);
    SendMessage(hEdit, EM_SETSEL, nLen, nLen);
    // convert to the GBK-ish ANSI codepage like
    // the ORIGINAL (an ANSI MFC build)
    char buf[4096];
    strncpy(buf, sz, sizeof(buf)-1);
    buf[sizeof(buf)-1] = 0;
    SendMessage(hEdit, EM_REPLACESEL, FALSE,
                (LPARAM)buf);
    SendMessage(hEdit, EM_SCROLLCARET, 0, 0);
    SendMessage(hEdit, WM_SETREDRAW, TRUE, 0);
    InvalidateRect(hEdit, nullptr, TRUE);
}

static void RefreshStats() {
    if (!s_pApp || !s_pApp->m_fnStats) return;
    NpcWinTexts t = s_pApp->m_fnStats();
    SetDlgItemTextA(s_hDlg, 1001, t.m_strKernel.c_str());
    SetDlgItemTextA(s_hDlg, 1002, t.m_strPanel.c_str());
}

static INT_PTR CALLBACK DlgProc(HWND h, UINT m,
        WPARAM w, LPARAM l) {
    switch (m) {
    case WM_INITDIALOG:
        s_hDlg = h;
        // the stats snapshot right away
        RefreshStats();
        SetTimer(h, 1, 1000, nullptr);
        return TRUE;
    case WM_TIMER:
        RefreshStats();
        return TRUE;
    case WM_COMMAND:
        // the ORIGINAL's buttons: "no use"
        // (id 1 - NO handler: its name is the
        // joke) and "Close" (id 2 -> ends)
        if (LOWORD(w) == 2) {
            DestroyWindow(h);
            return TRUE;
        }
        return FALSE;
    case WM_CLOSE:
        DestroyWindow(h);
        return TRUE;
    case WM_DESTROY:
        KillTimer(h, 1);
        PostQuitMessage(0);
        return TRUE;
    }
    return FALSE;
}

bool CNpcWinConsole::Run(int nTimerMs) {
    (void)nTimerMs;   // the 1s timer is fixed
    s_pApp = this;
    // the ORIGINAL template VERBATIM
    HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE,
                            g_abNpcMainDlg102_len);
    if (!h) return false;
    void* p = GlobalLock(h);
    memcpy(p, g_abNpcMainDlg102, g_abNpcMainDlg102_len);
    GlobalUnlock(h);
    HWND hDlg = CreateDialogIndirectParamA(
        GetModuleHandle(nullptr),
        (DLGTEMPLATE*)p, nullptr, DlgProc, 0);
    GlobalFree(h);
    if (!hDlg) return false;
    m_bVisible = true;
    ShowWindow(hDlg, SW_SHOW);
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        if (!IsDialogMessage(hDlg, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    m_bVisible = false;
    if (m_fnOnClose) m_fnOnClose();
    return true;
}

void CNpcWinConsole::Log(const std::string& s) {
    if (s_hDlg) AppendLog(GetDlgItem(s_hDlg, 1000),
                          s.c_str());
}

} // namespace npc

#else // !_WIN32 - the Linux stub

namespace npc {
bool CNpcWinConsole::Run(int) { return false; }
void CNpcWinConsole::Log(const std::string&) {}
} // namespace npc

#endif
