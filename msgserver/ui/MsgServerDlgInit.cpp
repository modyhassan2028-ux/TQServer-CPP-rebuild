// ===== Path-A wave 9a: ctor + OnInitDialog
// — VERBATIM raw-objdump-verified =====
#include "MsgServerDlgInit.h"
#include <cstring>
#include <cstdio>
#include <strings.h>

namespace msg {

SDlgInitSeams g_DlgInitSeams = {};

uint8_t g_DlgPerfBlock[0x168];
uint32_t g_DlgPerfA;
uint32_t g_DlgPerfB;
uint32_t g_DlgMapGroups;
char g_DlgInnerFlag;
char g_DlgSrcFile[0x40];
uint32_t g_DlgSrcFlag;
uint64_t g_DlgSrvName0;
uint64_t g_DlgSrvName1;

// raw inner-server language magics (1406e0670)
static const uint32_t kInnerLangs[2] =
    {0x060817ac, 0x090b17ac};
// raw GBK "\xd6\xd0\xce\xc4" (1406e0658)
static const char kLangZh[] =
    "\xd6\xd0\xce\xc4";

// FUN_140005c10 — the auth member at
// dlg+0x240 (size 0x2030+)
void DlgAuthMemberInit(void* at) {
    uint8_t* p = (uint8_t*)at;
    *(uint64_t*)(p + 0x20) =
        0xffffffffffffffff;
    *(uint32_t*)(p + 0x10) = 0;
    *(uint32_t*)(p + 0x14) = 0;
    *(uint32_t*)(p + 0x18) = 0;
    *(uint32_t*)(p + 0x1028) = 0;
    *(uint32_t*)(p + 0x202c) = 0;
    *(uint32_t*)(p + 0x2030) = 0;
    *(uint32_t*)(p) = 0;
    std::memset(p + 0x28, 0, 0x1000);
    std::memset(p + 0x102c, 0, 0x1000);
}

// FUN_1400238a0 — CMsgServerDlg ctor
void* DlgCtor(void* dlg, void* parent) {
    SDlgInitSeams& s = g_DlgInitSeams;
    uint8_t* p = (uint8_t*)dlg;
    s.DlgBaseInit(dlg, 0x66, parent);
    // 5 empty CStringT at +0xe8..+0x108
    for (int i = 0xe8; i <= 0x108;
         i += 8)
        *(uint64_t*)(p + i) = 0;
    // +0x134..+0x150 zeroing
    for (int i = 0x134; i <= 0x150;
         i += 4)
        *(uint32_t*)(p + i) = 0;
    s.PerfInfoInit(p + 0x158);
    s.ThreadTimesInit(p + 0x168);
    void* n1 = s.New(8);
    void* n2 = nullptr;
    if (n1 != nullptr) {
        *(void**)n1 = (void*)(p +
            0x188);
        n2 = n1;
    }
    *(void**)(p + 0x188) = n2;
    *(uint64_t*)(p + 0x1a0) = 0;
    *(uint64_t*)(p + 0x1a8) = 0;
    *(uint64_t*)(p + 0x1b0) = 0;
    for (int i = 0x210; i <= 0x21c;
         i += 4)
        *(uint32_t*)(p + i) = 0;
    DlgAuthMemberInit(p + 0x240);
    *(uint32_t*)(p + 0x22bc) = 0;
    *(uint32_t*)(p + 0x22c0) = 0;
    // operator= ("") x5 — empty again
    for (int i = 0xe8; i <= 0x108;
         i += 8)
        *(uint64_t*)(p + i) = 0;
    void* hInst = s.AfxFindRes(0x80,
                               0xe);
    *(void**)(p + 0x200) =
        s.LoadIconA(hInst, 0x80);
    *(uint32_t*)(p + 0x1fc) = 0;
    *(uint32_t*)(p + 0x1f8) = 0;
    *(uint64_t*)(p + 0x1f0) = 0;
    *(uint64_t*)(p + 0x1b8) = 0;
    *(uint64_t*)(p + 0x1c0) = 0;
    *(uint64_t*)(p + 0x1c8) = 0;
    *(uint64_t*)(p + 0x1d0) = 0;
    *(uint64_t*)(p + 0x178) = 0;
    *(uint64_t*)(p + 0x180) = 0;
    *(uint64_t*)(p + 0x1d8) = 0;
    *(uint64_t*)(p + 0x1e0) = 0;
    *(uint64_t*)(p + 0x1e8) = 0;
    *(uint64_t*)(p + 0x208) = 0;
    *(uint64_t*)(p + 0x220) = 0;
    *(uint64_t*)(p + 0x228) = 0;
    *(uint64_t*)(p + 0x230) = 0;
    *(uint64_t*)(p + 0x238) = 0;
    *(uint64_t*)(p + 0x110) = 0;
    *(uint64_t*)(p + 0x118) = 0;
    *(uint64_t*)(p + 0x120) = 0;
    *(uint64_t*)(p + 0x128) = 0;
    *(uint32_t*)(p + 0x130) = 0;
    return dlg;
}

// raw qword-copy loop (the OnInitDialog
// strcpy between auth string fields)
// raw byte-copy loop (1400283e1)
static void CopyQStr(void* dst,
                     const void* src) {
    uint8_t* d = (uint8_t*)dst;
    const uint8_t* sp =
        (const uint8_t*)src;
    uint8_t v;
    do {
        v = *sp++;
        *d++ = v;
    } while (v != 0);
}

// FUN_140027dd0 — OnInitDialog
int DlgOnInitDialog(void* dlg) {
    SDlgInitSeams& s = g_DlgInitSeams;
    uint8_t* p = (uint8_t*)dlg;
    void* hwnd = *(void**)(p + 0x40);
    char sbuf[0x200];   // CStringT temp
    s.BaseOnInit(dlg);
    // About menu (raw LoadStringA 0x65)
    void* hMenu = s.GetSystemMenu(hwnd, 0);
    void* pMenu = s.MenuFromHandle(hMenu);
    if (pMenu != nullptr) {
        sbuf[0] = 0;
        s.LoadStringA(0x65, sbuf);
        if (sbuf[0] != 0) {
            s.AppendMenu(pMenu, 0x800,
                         0, nullptr);
            s.AppendMenu(pMenu, 0, 0x10,
                         sbuf);
        }
    }
    s.SendMsg(hwnd, 0x80, 1,
        (uintptr_t)*(void**)(p + 0x200));
    s.SendMsg(hwnd, 0x80, 0,
        (uintptr_t)*(void**)(p + 0x200));
    void* hEv = s.CreateEvent();
    *(void**)(p + 0x208) = hEv;
    if (hEv == nullptr) {
        s.MsgBox(dlg,
            "Create exit event failed!",
            -1);
        s.EndDialog(dlg, -1);
        return 0;
    }
    std::memset(g_DlgPerfBlock, 0,
               0x168);
    g_DlgPerfA = 5000;
    g_DlgPerfB = 3000;
    int64_t t = s.Time32();
    s.DateTimeInit(p + 0x120, t);
    if (s.LoadConfig(dlg) == 0) {
        s.MsgBox(dlg,
            "Load config.ini failed!", 0);
    }
    else if (s.IntraPortInit(
            g_DlgMapGroups + 0xe) == 0) {
        s.MsgBox(dlg,
            "Initial intra message port "
            "failed!", 0);
    }
    else {
        void* mc = s.GetMsgCenter();
        if (mc != nullptr) {
            void* mc2 = s.GetMsgCenter();
            if (s.MsgCenterStart(mc2)
                    != 0) {
                void* mgr =
                    s.ThreadRecMgrNew();
                *(void**)(p + 0x1f0) = mgr;
                s.MgrVt38(mgr);
                s.MgrVt40(*(void**)(p +
                    0x1f0), 1);
                *(uint32_t*)(p + 0x1fc) = 1;
                goto lab_fff;
            }
        }
        s.MsgBox(dlg,
            "Initial CThreadRecordPtrMgr "
            "failed!", 0);
    }
lab_fff:
    // dead-loop set init
    {
        int32_t n = 0;
        uint32_t cnt =
            g_DlgMapGroups + 0xe;
        while (n < (int32_t)cnt) {
            void* n1 = s.New(8);
            void* slot[2] = {nullptr,
                            nullptr};
            if (n1 != nullptr) {
                *(void**)n1 = slot;
                slot[0] = n1;
            }
            s.DeadLoopInsert(
                s.DeadLoopHead(), slot);
            s.Del(slot[0]);
            n = n + 1;
        }
    }
    // shell.ini / AccountServer
    char ini1[0x400];
    s.IniOpen(ini1);
    s.IniGetStr(ini1, (char*)(p + 0x110),
        "SERVERNAME", 0x10);
    g_DlgSrvName0 =
        *(uint64_t*)(p + 0x110);
    g_DlgSrvName1 =
        *(uint64_t*)(p + 0x118);
    std::snprintf(sbuf, sizeof sbuf,
        "%s - %s - %s %s",
        "Conquer Online Server",
        (char*)(p + 0x110),
        "Dec  4 2015", "14:00:43");
    s.SetWindowText(dlg, sbuf);
    s.CreateDir("syslog");
    s.CreateDir("gmlog");
    t = s.Time32();
    s.InitLog(sbuf, "syslog/cqserver",
        "syslog/sysdb", t);
    s.LogStr("=================================================================");
    s.LogStr(sbuf);
    s.LogStr("=================================================================");
    s.Run20570();
    uint32_t* lang = s.CQLangGet();
    *lang = (uint32_t)s.LangValueGet();
    s.LogFmtU("CQLanguage = %u", *lang);
    s.Run21c80(dlg);
    // auth fields zeroing
    for (int i = 0x227c; i <= 0x22a4;
         i += 8)
        *(uint64_t*)(p + i) = 0;
    *(uint32_t*)(p + 0x22b0) = 0;
    *(uint32_t*)(p + 0x22b8) = 0;
    *(uint32_t*)(p + 0x2278) = 0;
    std::snprintf(g_DlgSrcFile, 0x40,
        "f:\\version\\cqserver-78.0."
        "11-1204\\msgserver\\"
        "msgserverdlg.cpp");
    g_DlgSrcFlag = 0;
    // shell.ini / System SERVE_PORT
    char ini2[0x400];
    s.IniOpen(ini2);
    int32_t port = s.IniGetInt(ini2,
        "SERVE_PORT");
    *(int32_t*)(p + 0x22c4) = port;
    if (port == 0)
        *(uint32_t*)(p + 0x22c4) =
            0x16b8;
    s.LogFmtSU("%s[%d]", g_DlgSrcFile,
        *(uint32_t*)(p + 0x22c4));
    // inner-server language check
    bool inner = false;
    for (int i = 0; i < 2; i++) {
        if (s.IsInnerLang(
                kInnerLangs[i]) != 0) {
            s.SafeCopy((char*)(p + 0x227c),
                "192.168.9.138", 0x10);
            s.SafeCopy((char*)(p + 0x228c),
                "192.168.9.138", 0x10);
            *(uint32_t*)(p + 0x22ac) =
                0x268d;
            g_DlgInnerFlag = 1;
            s.LogStr("This is a inner "
                "server.");
            inner = true;
            break;
        }
    }
    if (!inner) {
        const char* lg =
            s.InstanceLang(s.TheInstance());
        if (strcasecmp(lg, kLangZh)
                == 0) {
            s.SafeCopy((char*)(p + 0x227c),
                "121.207.253.12", 0x10);
            s.SafeCopy((char*)(p + 0x228c),
                "58.49.94.9", 0x10);
        }
        else {
            s.SafeCopy((char*)(p + 0x227c),
                "216.93.176.117", 0x10);
            s.SafeCopy((char*)(p + 0x228c),
                "92.52.79.12", 0x10);
        }
        *(uint32_t*)(p + 0x22ac) = 0x268d;
        g_DlgInnerFlag = 0;
    }
    s.Run5b50();
    // auth connect: primary
    CopyQStr(p + 0x229c, p + 0x227c);
    if (s.AuthTryConnect(p + 0x240,
            (char*)(p + 0x229c),
            *(uint32_t*)(p + 0x22ac),
            0xf, 0x8000, 0x8000) == 0) {
        s.AuthClose240(p + 0x240);
        // fallback server
        CopyQStr(p + 0x229c, p + 0x228c);
        if (s.AuthTryConnect(p + 0x240,
                (char*)(p + 0x229c),
                *(uint32_t*)(p + 0x22ac),
                0xf, 0x8000, 0x8000) == 0) {
            s.AuthClose240(p + 0x240);
        }
    }
    if (s.AuthIsConnected() == 0) {
        if (g_DlgInnerFlag != 0) {
            s.LogError(
                "connect authserver(%s) "
                "failed.",
                (char*)(p + 0x229c));
        }
    }
    else {
        *(uint32_t*)(p + 0x2278) = 1;
        s.AuthStartListen(p + 0x240,
            *(uint32_t*)(p + 0x22c4));
        if (g_DlgInnerFlag != 0) {
            s.LogFmtS("connect authserver"
                "(%s) ok.",
                (char*)(p + 0x229c));
        }
    }
    *(uint32_t*)(p + 0x22bc) = 600;
    *(uint32_t*)(p + 0x22c0) =
        (uint32_t)(s.TimeGet(0) / 1000);
    s.SetTimer(hwnd, 2, 100);
    std::snprintf(sbuf, sizeof sbuf,
        "%s - %s",
        "Conquer Online Server",
        (char*)(p + 0x110));
    s.SetProp(hwnd, sbuf, (void*)1);
    s.Run2a480(dlg);
    s.Run2440(dlg);
    s.IniClose(ini2);
    s.IniClose(ini1);
    return 1;
}

} // namespace msg
