// UI-4 unit test — the ORIGINAL dialog handlers
#include <cassert>
#include <cstdio>
#include <cstring>
#include "MsgServerDlgUI4.h"
using namespace msg;

static uint8_t s_dlg[0x2400];
template<class T> T& F(size_t o) {
    return *(T*)((char*)s_dlg + o);
}
// the log buffer model (CString at +0x108):
// stored as std::string content in +0x108..: use
// a side buffer since CString is dynamic in raw
static char s_logBuf[0x8000];
static int s_nUpdateSave = 0, s_nUpdateShow = 0,
           s_nBroadcast = 0, s_nAbout = 0,
           s_nPostCmd = 0, s_nMsgBox = 0,
           s_nIconic = 0, s_nTrim = 0,
           s_nDateTime = 0, s_nInline = 0,
           s_nInlineErr = 0, s_nRefresh = 0,
           s_nPerf = 0;
static int s_msgBoxRet = 1;
static char s_aBroadcast[256];
static uint32_t s_bcLen, s_bcCmd;
static int s_bcA;
static char s_aLastMsg[256];
static char s_aLastStatus[256];

static void TUpdate(void*, bool b) {
    if (b) s_nUpdateSave++; else s_nUpdateShow++;
}
static void TBroadcast(void*, int a, int cmd,
                       uint32_t len,
                       const char* s) {
    s_nBroadcast++; s_bcA = a; s_bcCmd = cmd;
    s_bcLen = len;
    std::strncpy(s_aBroadcast, s ? s : "",
                 sizeof s_aBroadcast - 1);
}
static void TTrim(void*) {
    s_nTrim++;
    char* nl = std::strchr(s_logBuf, '\n');
    if (nl) std::memmove(s_logBuf, nl + 1,
        std::strlen(nl + 1) + 1);
}
static void TAppend(void*, const char* s) {
    std::strncat(s_logBuf, s,
        sizeof s_logBuf - std::strlen(s_logBuf) - 1);
}
static void TDateTime(void*) {
    s_nDateTime++;
    std::strncat(s_logBuf, "[DATE]",
        sizeof s_logBuf - std::strlen(s_logBuf) - 1);
}
static void TInline(const char*, const char* s) {
    std::strncpy(s_aLastMsg, s ? s : "",
        sizeof s_aLastMsg - 1);
    s_nInline++;
}
static void TInlineErr(const char*) {
    s_nInlineErr++;
}
static void* TAbout(void*) { s_nAbout++;
    return nullptr; }
static void TPostCmd(void*, int) { s_nPostCmd++; }
static int TMsgBox(void*, const char* s,
                   uint32_t t) {
    assert(t == 0x101);   // the raw flags
    assert(std::strcmp(s, "Are you sure?") == 0);
    s_nMsgBox++;
    return s_msgBoxRet;
}
static bool TIconic(void*) { s_nIconic++;
    return false; }
static void TPaint(void*) {}
static void TDrawIcon(void*) {}
static void TRefresh(void*) { s_nRefresh++; }
static void TPerf(void*) { s_nPerf++; }
static uint32_t TStrLen(const char* s) {
    return s ? (uint32_t)std::strlen(s) : 0;
}
static bool TStrEmpty(const char* s) {
    return !s || !*s;
}

static void ResetSeams() {
    std::memset(&g_UI4Seams, 0,
                sizeof g_UI4Seams);
    std::memset(s_dlg, 0, sizeof s_dlg);
    std::memset(s_logBuf, 0, sizeof s_logBuf);
    s_logBuf[0] = 0;
    g_UI4Seams.UpdateData = TUpdate;
    g_UI4Seams.KernelBroadcast = TBroadcast;
    g_UI4Seams.LogTrim = TTrim;
    g_UI4Seams.LogAppend = TAppend;
    g_UI4Seams.LogDateTime = TDateTime;
    g_UI4Seams.InlineLogMessage = TInline;
    g_UI4Seams.InlineLogError = TInlineErr;
    g_UI4Seams.AboutModal = TAbout;
    g_UI4Seams.PostCommand = TPostCmd;
    g_UI4Seams.MessageBox = TMsgBox;
    g_UI4Seams.IsIconic = TIconic;
    g_UI4Seams.DlgOnPaint = TPaint;
    g_UI4Seams.DrawIconCentered = TDrawIcon;
    g_UI4Seams.StatusRefresh = TRefresh;
    g_UI4Seams.RecordPerfNow = TPerf;
    g_UI4Seams.StrLen = TStrLen;
    g_UI4Seams.StrEmpty = TStrEmpty;
    s_nUpdateSave = s_nUpdateShow =
    s_nBroadcast = s_nAbout = s_nPostCmd =
    s_nMsgBox = s_nIconic = s_nTrim =
    s_nDateTime = s_nInline = s_nInlineErr =
    s_nRefresh = s_nPerf = 0;
    s_msgBoxRet = 1;
}

int main() {
    printf("UI4 start\n"); fflush(stdout);

    // ==== S1: OnTalk — input -> kernel broadcast
    // (2, 0x4e21, len, text) ====
    {
        ResetSeams();
        std::strcpy((char*)s_dlg + 0x100, "/hi all");
        F<uint64_t>(0x1f0) = 0x777;
        MsgOnTalk(s_dlg);
        assert(s_nUpdateSave == 1);
        assert(s_nBroadcast == 1);
        assert(s_bcA == 2 && s_bcCmd == 0x4e21);
        assert(s_bcLen == 7);   // strlen
        assert(std::strcmp(s_aBroadcast,
                          "/hi all") == 0);
        // no kernel -> no broadcast
        s_nBroadcast = 0;
        F<uint64_t>(0x1f0) = 0;
        MsgOnTalk(s_dlg);
        assert(s_nBroadcast == 0);
        printf("S1 ok (OnTalk)\n"); fflush(stdout);
    }

    // ==== S2: OnSysCommand — About / SC_CLOSE ==
    // ==
    {
        ResetSeams();
        MsgOnSysCommand(s_dlg, 0x12);   // About (==0x10 band)
        assert(s_nAbout == 1);
        MsgOnSysCommand(s_dlg, 0xf060);   // close
        assert(s_nPostCmd == 1);
        MsgOnSysCommand(s_dlg, 0xf000);   // other
        assert(s_nAbout == 1);  // unchanged
        printf("S2 ok (OnSysCommand)\n");
        fflush(stdout);
    }

    // ==== S3: OnClose — "CLOSE key pressed" +
    // "Are you sure?" 0x101 -> state 3 ====
    {
        ResetSeams();
        F<uint32_t>(0x1fc) = 2;
        MsgOnClose(s_dlg);
        assert(s_nMsgBox == 1);
        assert(F<uint32_t>(0x1fc) == 3);
        assert(std::strstr(s_logBuf,
                "CLOSE key pressed") != nullptr);
        assert(std::strstr(s_logBuf,
                "Server closing...") != nullptr);
        // answering NO: state unchanged
        ResetSeams();
        s_msgBoxRet = 7;   // not IDYES
        F<uint32_t>(0x1fc) = 2;
        MsgOnClose(s_dlg);
        assert(F<uint32_t>(0x1fc) == 2);
        printf("S3 ok (OnClose)\n"); fflush(stdout);
    }

    // ==== S4: the log append — the 7-line trim
    // and the SHELL line ====
    {
        ResetSeams();
        for (int i = 0; i < 10; i++) {
            char buf[32];
            std::snprintf(buf, sizeof buf, "L%d", i);
            MsgDlgLogAppend(s_dlg, buf);
        }
        // counter grew to 10; trims fired for
        // entries 9 and 10 (after lines > 7)
        assert(F<uint32_t>(0x1f8) == 10);
        assert(s_nTrim >= 2);
        assert(s_nInline == 10);
        assert(std::strcmp(s_aLastMsg, "L9") == 0);
        assert(std::strstr(s_logBuf, "L0") ==
            nullptr);   // trimmed away
        assert(std::strstr(s_logBuf, "L8") !=
            nullptr);
        printf("S4 ok (log append/trim)\n");
        fflush(stdout);
    }

    // ==== S5: shell messages — 0x9c41 log,
    // 0x9c42 status, 0x9c43 refresh, 0x9c44 perf,
    // invalid -> 0 ====
    {
        ResetSeams();
        assert(MsgShellMessage(s_dlg, 0x9c41,
                               "boot") == 1);
        assert(std::strstr(s_logBuf, "boot"));
        assert(MsgShellMessage(s_dlg, 0x9c42,
                               "STATUS") == 1);
        assert(std::strcmp((char*)s_dlg + 0xe8,
                          "STATUS") == 0);
        assert(MsgShellMessage(s_dlg, 0x9c43,
                               nullptr) == 1);
        // RAW: 0x9c42 also falls through to the
        // refresh (28960/2a5a0) at the chain end
        assert(s_nRefresh == 2);
        assert(MsgShellMessage(s_dlg, 0x9c44,
                               nullptr) == 1);
        assert(s_nPerf == 1);
        assert(s_nRefresh == 2);  // unchanged
        assert(MsgShellMessage(s_dlg, 0x9999,
                               nullptr) == 0);
        assert(s_nInlineErr >= 1);
        printf("S5 ok (shell dispatch)\n");
        fflush(stdout);
    }

    // ==== S6: OnPaint ====
    {
        ResetSeams();
        MsgOnPaint(s_dlg);
        assert(s_nIconic == 1);
        printf("S6 ok (OnPaint)\n"); fflush(stdout);
    }

    printf("UI4 ALL-OK\n");
    return 0;
}
