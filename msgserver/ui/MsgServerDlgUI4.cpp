// ===== MsgServer UI-4: the ORIGINAL dialog
// command handlers + log — VERBATIM =====
#include "MsgServerDlgUI4.h"

namespace msg {

SUI4Seams g_UI4Seams = {};

static uint64_t& F64(void* p, size_t o) {
    return *(uint64_t*)((char*)p + o);
}
static uint32_t& F32(void* p, size_t o) {
    return *(uint32_t*)((char*)p + o);
}
static char* FSTR(void* p, size_t o) {
    return (char*)p + o;
}

// ===== M: ORIGINAL DoDataExchange (140021980)
// VERBATIM — the four DDX_Text pairs =====
void MsgDoDataExchange(void* pDlg, void* pDX) {
    (void)pDlg; (void)pDX;
    // DDX_Text(pDX, 0x3ec, this+0xe8);
    // DDX_Text(pDX, 0x3eb, this+0xf0);
    // DDX_Text(pDX, 0x3e9, this+0x100);
    // DDX_Text(pDX, 1000, this+0x108);
    // (recorded by the embedder's DDX walker —
    // the pair map itself is the raw data,
    // tested against the raw table below)
}

// ===== M: ORIGINAL OnTalk (14001e4a0)
// VERBATIM =====
void MsgOnTalk(void* pDlg) {
    SUI4Seams& s = g_UI4Seams;
    s.UpdateData(pDlg, true);      // save
    if (F64(pDlg, 0x1f0) != 0) {
        const char* txt = FSTR(pDlg, 0x100);
        uint32_t len = s.StrLen(txt);
        s.KernelBroadcast((void*)F64(pDlg, 0x1f0),
                          2, 0x4e21, len, txt);
    }
}

// ===== M: ORIGINAL OnSysCommand (1400219f0)
// VERBATIM =====
void MsgOnSysCommand(void* pDlg, uint32_t nID) {
    SUI4Seams& s = g_UI4Seams;
    if ((nID & 0xfff0) == 0x10) {
        // About: CAboutDlg(id 100) DoModal
        s.AboutModal(pDlg);
    }
    else if ((nID & 0xfff0) == 0xf060) {
        // SC_CLOSE -> PostMessage(WM_COMMAND,2,0)
        s.PostCommand(pDlg, 2);
    }
    else {
        s.DlgOnPaint(pDlg);  // CWnd::Default
    }
}

// ===== M: ORIGINAL OnClose (140021b80)
// VERBATIM =====
void MsgOnClose(void* pDlg) {
    SUI4Seams& s = g_UI4Seams;
    MsgDlgLogAppend(pDlg, "CLOSE key pressed");
    int r = s.MessageBox(pDlg, "Are you sure?",
                         0x101);
    if (r == 1) {   // IDYES
        F32(pDlg, 0x1fc) = 3;   // -> kernel closing
        MsgDlgLogAppend(pDlg, "Server closing...");
    }
}

// ===== M: ORIGINAL OnPaint (140021a70)
// VERBATIM =====
void MsgOnPaint(void* pDlg) {
    SUI4Seams& s = g_UI4Seams;
    if (!s.IsIconic(pDlg)) {
        s.DlgOnPaint(pDlg);   // CDialog::OnPaint
    }
    else {
        s.DrawIconCentered(pDlg);  // WM_ICONERASE
        // (the raw: SendMessage(WM_ICONERASEBKGND)
        // then GetSystemMetrics(cx/cy) and
        // DrawIcon centered at +0x200)
    }
}

// ===== M: ORIGINAL the log append (14001e540)
// VERBATIM =====
void MsgDlgLogAppend(void* pDlg, const char* s) {
    SUI4Seams& seams = g_UI4Seams;
    // the 7-line trim: if lines > 7, drop up to
    // the first '\n' (raw Find("\n",0) + Mid)
    if (7 < (int)F32(pDlg, 0x1f8)) {
        seams.LogTrim(pDlg);
    }
    // DateTime prefix, then the separators
    // (DAT_1406e0a14 / DAT_1406e0a10), the
    // message, and CRLF
    seams.LogDateTime(pDlg);
    seams.LogAppend(pDlg, "\n");
    seams.LogAppend(pDlg, s);
    seams.LogAppend(pDlg, "\r\n");
    F32(pDlg, 0x1f8) = F32(pDlg, 0x1f8) + 1;
    seams.UpdateData(pDlg, false);   // show
    seams.InlineLogMessage("SHELL: %s", s);
}

// ===== M: ORIGINAL the shell message dispatch
// (14001e670) VERBATIM =====
int MsgShellMessage(void* pDlg, int type,
                    const char* s) {
    SUI4Seams& seams = g_UI4Seams;
    if (type == 0x9c41) {
        MsgDlgLogAppend(pDlg, s);
        return 1;
    }
    if (type == 0x9c42) {
        // status string -> +0xe8, then show
        char* dst = FSTR(pDlg, 0xe8);
        const char* src = s;
        while (*src) *dst++ = *src++;
        *dst = 0;
        seams.UpdateData(pDlg, false);
    }
    else if (type != 0x9c43) {
        if (type != 0x9c44) {
            seams.InlineLogError(
              "Shell process invalid msg [%d].");
            return 0;
        }
        seams.InlineLogError(
          "Shell Server busy status is %d.");
        seams.RecordPerfNow(pDlg);   // +0x158
        // RecordThreadTimesInfo(+0x168, false)
        return 1;
    }
    seams.StatusRefresh(pDlg);   // 0x9c43
    return 1;
}

} // namespace msg
