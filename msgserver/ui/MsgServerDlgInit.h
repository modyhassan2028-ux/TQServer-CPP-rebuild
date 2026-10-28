#ifndef MSG_SERVER_DLG_INIT_H
#define MSG_SERVER_DLG_INIT_H
// ===== Path-A wave 9a: CMsgServerDlg ctor
// (1400238a0) + OnInitDialog (140027dd0)
// — VERBATIM raw-verified =====
// Constants extracted from the binary:
//  - inner-server language magics
//    {0x060817ac, 0x090b17ac} @1406e0670
//  - GBK "\xd6\xd0\xce\xc4" @1406e0658
//  - auth IPs @1406e3e78..3eb8:
//    192.168.9.138 / 92.52.79.12 /
//    216.93.176.117 / 58.49.94.9 /
//    121.207.253.12
//  - title date/time strings
//    "Dec  4 2015" "14:00:43"
//  - template id 0x66 (dialog 102)
//  - SERVE_PORT default 0x16b8
#include <cstdint>
#include <cstddef>

namespace msg {

struct SDlgInitSeams {
    void* (*New)(size_t n);
    void (*Del)(void* p);
    void (*DlgBaseInit)(void* dlg, int tpl,
        void* parent);          // CDialog::CDialog
    void (*BaseOnInit)(void* dlg);
    void* (*GetSystemMenu)(
        void* hwnd, int rev);
    void* (*MenuFromHandle)(void* h);
    int (*LoadStringA)(int id, char* out);
    void (*AppendMenu)(void* hmenu,
        uint32_t flags, uint32_t id,
        const char* s);
    void (*SendMsg)(void* hwnd, uint32_t m,
        uintptr_t wp, uintptr_t lp);
    void* (*CreateEvent)();     // null=fail
    void (*MsgBox)(void* dlg,
        const char* text, int r);
    void (*EndDialog)(void* dlg, int r);
    int64_t (*Time32)();
    void (*DateTimeInit)(void* at,
        int64_t t);            // tq::DateTime
    char (*LoadConfig)(void* dlg); // 14001f2f0
    char (*IntraPortInit)(
        uint32_t v);           // 14050f8b0
    void* (*GetMsgCenter)();   // 14002e300
    char (*MsgCenterStart)(
        void* p);              // 14002c6b0
    void* (*ThreadRecMgrNew)();// 14050c340(0)
    void (*MgrVt38)(void* mgr);
    void (*MgrVt40)(void* mgr,
        uint32_t one);
    void (*DeadLoopInsert)(
        void* head, void* node);// 140027b70
    void* (*DeadLoopHead)();  // g_setDeadLoop
    void (*IniOpen)(void* buf);
    void (*IniOpen2)(void* buf,
        const char* file,
        const char* section);
    void (*IniSetSection)(void* ini,
        const char* s);
    void (*IniGetStr)(void* ini,
        char* dst, const char* key, int sz);
    int32_t (*IniGetInt)(
        void* ini, const char* key);
    void (*IniClose)(void* ini);
    void (*SetWindowText)(
        void* dlg, const char* s);
    void (*CreateDir)(const char* n);
    void (*InitLog)(const char* s,
        const char* a, const char* b,
        int64_t t);
    void (*LogStr)(const char* s);
    void (*LogFmtS)(const char* fmt,
        const char* a);
    void (*LogFmtSU)(const char* fmt,
        const char* a, uint32_t v);
    void (*LogFmtU)(const char* fmt,
        uint32_t v);
    void (*LogError)(const char* fmt,
        const char* a);
    void (*LogError4)(const char* fmt,
        const char* a, const char* b,
        const char* c, uint32_t d);
    // extraproc (140021c80 / 14001f4d0)
    void (*SysLogSave)(const char* file,
        const char* fmt, const char* a);
    int (*CreateProc)(const char* app,
        void* pi);          // pi: hProc,hThr
    void (*CloseHandle)(void* h);
    int64_t (*SnapCreate)();
    int (*SnapFirst)(int64_t snap, void* e);
    int (*SnapNext)(int64_t snap, void* e);
    void (*Run20570)();
    void (*Run21c80)(void* dlg);
    uint32_t* (*CQLangGet)();
    int (*LangValueGet)();    // 14001e220
    char (*IsInnerLang)(
        uint32_t v);           // 140508440
    void* (*TheInstance)();
    const char* (*InstanceLang)(
        void* inst);           // vt "Language"
    void (*SafeCopy)(char* dst,
        const char* src, int sz);
    void (*Run5b50)();        // 140005b50
    char (*AuthTryConnect)(void* auth,
        const char* ip, uint32_t port,
        uint32_t r9f, uint32_t f1,
        uint32_t f2);
    void (*AuthClose240)(void* auth);
    char (*AuthIsConnected)(); //140005e80
    void (*AuthStartListen)(
        void* auth, uint32_t port);
    uint64_t (*TimeGet)(int);
    void (*SetTimer)(void* hwnd,
        uint32_t id, uint32_t ms);
    void (*SetProp)(void* hwnd,
        const char* s, void* val);
    void (*Run2a480)(void* dlg);
    void (*Run2440)(void* dlg);
    void* (*AfxFindRes)(int id, int ty);
    void* (*LoadIconA)(void* h,
        int id);
    void (*PerfInfoInit)(void* at);
    void (*ThreadTimesInit)(void* at);
};

extern SDlgInitSeams g_DlgInitSeams;

// module globals (raw DAT_ addresses)
extern uint8_t g_DlgPerfBlock[0x168]; // 975660
extern uint32_t g_DlgPerfA;            // 975780=5000
extern uint32_t g_DlgPerfB;            // 975784=3000
extern uint32_t g_DlgMapGroups;        // 9757d0
extern char g_DlgInnerFlag;            // 949790
extern char g_DlgSrcFile[0x40];        // 949750
extern uint32_t g_DlgSrcFlag;          // 94978f
extern uint64_t g_DlgSrvName0;         // 975674
extern uint64_t g_DlgSrvName1;         // 97567c
extern uint32_t g_DlgCfg7d4;           // 9757d4
extern uint32_t g_DlgCfg7d8;           // 9757d8
extern uint8_t  g_DlgCfg7dc;           // 9757dc
extern uint32_t g_DlgCfg7ec;           // 9757ec
extern uint8_t  g_DlgCfg7f0;           // 9757f0
extern uint32_t g_DlgFreeLev;         // 949794
extern void**   g_MonRegistry;         // 9754e8

void DlgAuthMemberInit(void* at); // FUN_140005c10
void* DlgCtor(void* dlg, void* parent);
int DlgOnInitDialog(void* dlg);
int DlgLoadConfig(void* dlg);   // 14001f2f0
int DlgMonitorRegInit(void* dlg); // 140002440
void DlgLaunchExtraProcs(void* dlg); // 140021c80
uint32_t DlgFindProcByName(void* dlg,
    const char* name);    // 14001f4d0

} // namespace msg
#endif
