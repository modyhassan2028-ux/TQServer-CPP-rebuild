// D182 — NpcServer.exe 0x140015ed0 event_base_new_with_config.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static unsigned char g_base[0x2b0];
static bool g_callocNull = false;
static void* Calloc(long long n, long long sz) {
    assert(n == 1 && sz == 0x2b0);
    if (g_callocNull) return nullptr;
    std::memset(g_base, 0, sizeof g_base);
    return g_base;
}
static int g_errno = 0;
static int* ErrnoPtr(void) { return &g_errno; }
static int g_errLogs = 0; static const char* g_errFmt = nullptr;
static void ErrLog(const char* pFmt, ...) { ++g_errLogs; g_errFmt = pFmt; }
static int g_msgLogs = 0;
static void MsgLog(const char* pFmt, ...) { (void)pFmt; ++g_msgLogs; }
static int g_getenvCalls = 0; static const char* g_getenvLast = nullptr;
static bool g_preciseEnv = false, g_showEnv = false;
static char* GetenvStub(const char* n) {
    ++g_getenvCalls; g_getenvLast = n;
    if (std::strcmp(n, "EVENT_PRECISE_TIMER") == 0) return g_preciseEnv ? (char*)"1" : nullptr;
    if (std::strcmp(n, "EVENT_SHOW_METHOD") == 0) return g_showEnv ? (char*)"1" : nullptr;
    return nullptr;
}
static long long g_offsets[8]; static int g_initCalls = 0;
static void Monitor(void* p, unsigned int f) { g_offsets[g_initCalls++] = (long long)((char*)p - (char*)g_base); (void)f; }
static long long g_deferred = 0; static void Deferred(void* p, void* o) { (void)o; g_deferred = (long long)((char*)p - (char*)g_base); }
static long long g_q25 = 0, g_q28 = 0, g_q2 = 0;
static void Q25(void* p) { g_q25 = (long long)((char*)p - (char*)g_base); }
static void Q28(void* p) { g_q28 = (long long)((char*)p - (char*)g_base); }
static void Q2(void* p) { g_q2 = (long long)((char*)p - (char*)g_base); }
static int g_usableRet = 0; static int g_usableCalls = 0;
static int Usable(const char* n) { (void)n; ++g_usableCalls; return g_usableRet; }
static unsigned int g_notifyRet = 0; static int g_notifyCalls = 0; static void* g_notifyBase = nullptr;
static unsigned int Notify(void* b, int f) { (void)f; ++g_notifyCalls; g_notifyBase = b; return g_notifyRet; }
static int g_canNotifiable = 0;
static int CanNotifiable(void) { return g_canNotifiable; }
static long long g_a = 0, g_b = 0;
static long long FnA(void) { return ++g_a; }
static long long FnB(void) { return ++g_b; }
static unsigned int g_makeNotifiableRet = 0; static int g_makeNotifiableCalls = 0;
static unsigned int MakeNotifiable(void* b, unsigned long long a) { (void)b; (void)a; ++g_makeNotifiableCalls; return g_makeNotifiableRet; }
static unsigned int g_iocpThreads = 0; static void* g_iocpRet = (void*)0x900;
static void* LaunchIocp(unsigned int t) { g_iocpThreads = t; return g_iocpRet; }
static int g_releaseCalls = 0;
static void Release(void* b, int f) { (void)b; (void)f; ++g_releaseCalls; }

static void* SelectorInit(void* pBase) { (void)pBase; return (void*)0xBEEF; }

int main() {
    g_pfnNpcCalloc = &Calloc;
    g_pfnNpcErrno = &ErrnoPtr;
    g_pfnNpcWarn_1400191c0 = &ErrLog;
    g_pfnNpc_140019050 = &ErrLog;
    g_pfnNpc_1400191f0 = &MsgLog;
    g_pfnNpcGetenv = &GetenvStub;
    g_pfnNpc_140016640 = &Monitor;
    g_pfnNpc_1400105b0 = &Deferred;
    g_pfnNpc_14001a010 = &Q25;
    g_pfnNpc_14001a190 = &Q28;
    g_pfnNpc_14001ad50 = &Q2;
    g_pfnNpc_140010860 = &Usable;
    g_pfnNpc_1400127e0 = &Notify;
    g_pfnNpc_140016f00 = &CanNotifiable;
    g_pfnNpc_140016df0 = &FnA;
    g_pfnNpc_140016e70 = &FnB;
    g_pfnNpc_140015e70 = &MakeNotifiable;
    g_pfnNpc_140074b80 = &LaunchIocp;
    g_pfnNpc_140014b30 = &Release;

    // no memory: errno 0xc and the calloc report
    {
        g_callocNull = true; g_errno = 0; g_errLogs = 0; g_errFmt = nullptr;
        assert(FUN_140015ed0(nullptr, 0, 0, nullptr) == nullptr);
        assert(g_errno == 0xc && g_errLogs == 1);
        assert(std::strcmp(g_errFmt, "%s: calloc") == 0);
        g_callocNull = false;
    }

    // no selector at all: the defaults, the no-mechanism report and the release
    {
        g_apNpcEventSelTable_140102480[0] = nullptr;
        g_initCalls = 0; g_errLogs = 0; g_releaseCalls = 0; g_getenvCalls = 0; g_preciseEnv = false;
        assert(FUN_140015ed0(nullptr, 0, 0, nullptr) == nullptr);
        assert(g_releaseCalls == 1);
        assert(g_initCalls == 1);                                        // the timer monitor only
        assert(g_offsets[0] == 0x168 && g_deferred == 0x00);
        assert(g_q25 == 0x128 && g_q28 == 0x140 && g_q2 == 0x10);
        assert(*(unsigned int*)(g_base + 0x1fc) == 0xffffffffu);
        assert(*(unsigned int*)(g_base + 0x204) == 0x7fffffffu);
        assert(*(unsigned int*)(g_base + 0x208) == 0x7fffffffu);          // the settle rule
        assert(*(void**)(g_base + 0x110) == (void*)(g_base + 0x108));
        assert(*(int*)(g_base + 0x150) == 0 && *(long long*)(g_base + 0x0a0) == -1);
        assert(*(unsigned int*)(g_base + 0x1f8) == 0x20);                 // no env, no precise flag: still set
        assert(g_errLogs == 1);
        assert(std::strcmp(g_errFmt, "%s: no event mechanism available") == 0);
    }

    // one usable selector: it is stored with its init result and the base comes back
    {
        static NpcEventSel sel;
        sel.pszName = "epoll"; sel.pfnInit = &SelectorInit; sel.nFeatures = 0;
        g_apNpcEventSelTable_140102480[0] = &sel;
        g_apNpcEventSelTable_140102480[1] = nullptr;
        g_releaseCalls = 0; g_notifyCalls = 0; g_canNotifiable = 0; g_usableCalls = 0;
        g_preciseEnv = true;
        void* p = FUN_140015ed0(nullptr, 0, 0, nullptr);
        assert(p == (void*)g_base);
        assert(*(void**)(g_base + 0x00) == (void*)&sel);
        assert(*(void**)(g_base + 0x08) == (void*)0xBEEF);
        assert(g_usableCalls == 1);                                       // the null config keeps the check
        assert(g_notifyCalls == 1 && g_notifyBase == (void*)g_base);
        assert(g_releaseCalls == 0);
        assert(*(long long*)(g_base + 0x1d0) == 0);                        // not notifiable
    }

    // an avoid-method entry skips the matching selector, the next one is taken
    {
        static NpcEventSel s1, s2;
        s1.pszName = "select"; s1.pfnInit = &SelectorInit; s1.nFeatures = 0;
        s2.pszName = "epoll"; s2.pfnInit = &SelectorInit; s2.nFeatures = 0;
        g_apNpcEventSelTable_140102480[0] = &s1;
        g_apNpcEventSelTable_140102480[1] = &s2;
        g_apNpcEventSelTable_140102480[2] = nullptr;
        static struct { void* pNext; void* pPrev; char* pszName; } node;
        node.pNext = nullptr; node.pPrev = nullptr; node.pszName = (char*)"select";
        unsigned char cfg[0x30];
        std::memset(cfg, 0, sizeof cfg);
        *(void**)(cfg + 0) = &node;
        g_releaseCalls = 0;
        void* p = FUN_140015ed0(cfg, 0, 0, nullptr);
        assert(p == (void*)g_base);
        assert(*(void**)(g_base + 0x00) == (void*)&s2);                    // "select" was avoided
        assert(g_releaseCalls == 0);
        g_apNpcEventSelTable_140102480[0] = nullptr;
    }

    // a selector that does not offer the required feature is skipped
    {
        static NpcEventSel s1;
        s1.pszName = "epoll"; s1.pfnInit = &SelectorInit; s1.nFeatures = 2;
        g_apNpcEventSelTable_140102480[0] = &s1;
        g_apNpcEventSelTable_140102480[1] = nullptr;
        unsigned char cfg[0x30];
        std::memset(cfg, 0, sizeof cfg);
        *(unsigned int*)(cfg + 0x24) = 4;                                  // require_features
        g_releaseCalls = 0;
        assert(FUN_140015ed0(cfg, 0, 0, nullptr) == nullptr);
        assert(g_releaseCalls == 1);                                       // nothing was usable
        g_apNpcEventSelTable_140102480[0] = nullptr;
    }

    // flag 4 asks for IOCP with the processor hint from the config
    {
        static NpcEventSel sel;
        sel.pszName = "epoll"; sel.pfnInit = &SelectorInit; sel.nFeatures = 0;
        g_apNpcEventSelTable_140102480[0] = &sel;
        g_apNpcEventSelTable_140102480[1] = nullptr;
        unsigned char cfg[0x30];
        std::memset(cfg, 0, sizeof cfg);
        *(unsigned int*)(cfg + 0x28) = 0x04;                               // EVENT_BASE_FLAG_STARTUP_IOCP
        *(unsigned int*)(cfg + 0x10) = 9;                                  // n_cpus
        g_iocpThreads = 0; g_iocpRet = (void*)0x900;
        void* p = FUN_140015ed0(cfg, 0, 0, nullptr);
        assert(p == (void*)g_base);
        assert(g_iocpThreads == 9);
        assert(*(void**)(g_base + 0x1f0) == (void*)0x900);
        g_iocpRet = nullptr; g_errLogs = 0;
        assert(FUN_140015ed0(cfg, 0, 0, nullptr) == (void*)g_base);        // a failing IOCP only reports
        assert(g_errLogs == 1 && std::strcmp(g_errFmt, "%s: Couldn't launch IOCP") == 0);
        g_apNpcEventSelTable_140102480[0] = nullptr;
    }

    // flag 0x20 suppresses the precise-timer probe
    {
        static NpcEventSel sel;
        sel.pszName = "epoll"; sel.pfnInit = &SelectorInit; sel.nFeatures = 0;
        g_apNpcEventSelTable_140102480[0] = &sel;
        g_apNpcEventSelTable_140102480[1] = nullptr;
        unsigned char cfg[0x30];
        std::memset(cfg, 0, sizeof cfg);
        *(unsigned int*)(cfg + 0x28) = 0x20;
        g_getenvCalls = 0; g_getenvLast = nullptr;
        assert(FUN_140015ed0(cfg, 0, 0, nullptr) == (void*)g_base);
        assert(g_getenvCalls == 1);                                        // only the method probe
        assert(std::strcmp(g_getenvLast, "EVENT_SHOW_METHOD") == 0);
        assert(*(unsigned int*)(g_base + 0x1f8) == 0x20);                  // the config's own word
        g_apNpcEventSelTable_140102480[0] = nullptr;
    }

    std::printf("NPCSERVER_D182_OK: 0x140015ed0 event_base_new_with_config\n");
    return 0;
}
