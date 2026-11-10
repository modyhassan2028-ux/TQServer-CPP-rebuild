// D176 — NpcServer.exe 0x140002b30 CKernelThread::Create(), driving the real bodies it now calls.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdarg>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static unsigned char g_cfgBuf[0x30], g_baseBuf[0x2b0], g_table[0x40], g_handles[0x100], g_iocp[0x50];
static unsigned char g_engineBuf[0x68], g_socketBuf[0x838];
static bool g_cfgNull = false, g_socketNull = true;
static void* Calloc(long long n, long long sz) {
    if (n == 1 && sz == 0x30) { if (g_cfgNull) return nullptr; std::memset(g_cfgBuf, 0, sizeof g_cfgBuf); return g_cfgBuf; }
    if (n == 1 && sz == 0x2b0) { std::memset(g_baseBuf, 0, sizeof g_baseBuf); return g_baseBuf; }
    return nullptr;
}
static int g_errno = 5;
static int* ErrnoPtr(void) { return &g_errno; }
static void* g_crtFreed[8]; static int g_crtN = 0;
static void* CrtFree(void* p) { if (g_crtN < 8) g_crtFreed[g_crtN] = p; ++g_crtN; return nullptr; }
static int g_warns = 0; static const char* g_warnFmt = nullptr;
static void Warn(const char* pFmt, ...) { ++g_warns; g_warnFmt = pFmt; }
static int g_errCalls = 0; static const void* g_errFmt = nullptr;
static void ErrLog(const void* pMsg, ...) { ++g_errCalls; g_errFmt = pMsg; }
static void EvErr(const char* pFmt, ...) { ++g_errCalls; g_errFmt = (const void*)pFmt; }
static void H880(void* p) { (void)p; }
static void H890(void* p, long long a, long long b, long long c) { (void)p; (void)a; (void)b; (void)c; }
static char* GetenvStub(const char* n) { (void)n; return nullptr; }
static int SprintfStub(char* pBuf, unsigned long long n, const char* pFmt, const char* pszArg) {
    (void)n; std::strcpy(pBuf, "EVENT_NO"); std::strcat(pBuf, pszArg); (void)pFmt;
    return (int)std::strlen(pBuf);
}
static unsigned char UpperStub(unsigned char c) { return (unsigned char)(c >= 'a' && c <= 'z' ? c - 32 : c); }
static void* Alloc(long long n, long long sz) {
    if (n == 1 && sz == 0x10) { std::memset(g_table, 0, sizeof g_table); return g_table; }
    if (n == 1 && sz == 0x50) { std::memset(g_iocp, 0, sizeof g_iocp); return g_iocp; }
    if (sz == 8) { std::memset(g_handles, 0, sizeof g_handles); return g_handles; }
    return nullptr;
}
static void* IocpNew(void* a, void* b, unsigned long c, unsigned int d) {
    (void)a; (void)b; (void)c; (void)d; return (void*)0x9000;
}
static void* SemNew(void* a, long i, long m, const char* n) { (void)a; (void)i; (void)m; (void)n; return (void*)0x9001; }
static int g_beginCalls = 0;
static unsigned long long Begin(void (*fn)(void*), unsigned int st, void* arg) {
    (void)fn; (void)st; (void)arg; ++g_beginCalls; return 0x9100ull + (unsigned long long)g_beginCalls;
}
static unsigned long Spin(void* p, unsigned long n) { (void)p; (void)n; return 1; }
static int CloseH(void* h) { (void)h; return 1; }
static void FreeSeam(void* p) { (void)p; }
static unsigned int g_cpu = 6;
static void SysInfo(void* p) { *(unsigned int*)((char*)p + 0x20) = g_cpu; }
static int g_logCalls = 0; static const void* g_logFmt = nullptr;
static void LogFmt(const char* pFmt, ...) { ++g_logCalls; g_logFmt = (const void*)pFmt; }
static int g_newBytes = 0;
static void* OperatorNew(long long n) {
    g_newBytes = (int)n;
    if (n == 0x68) { std::memset(g_engineBuf, 0, sizeof g_engineBuf); return g_engineBuf; }
    if (n == 0x838) return g_socketNull ? nullptr : (void*)g_socketBuf;
    return nullptr;
}
static void* g_engVt[3];
static void* EngineSetup(void* p) { *(void**)p = (void*)g_engVt; return p; }
static void* SelectorInit(void* p) { (void)p; return (void*)0xBEEF; }
static int g_slot0Calls = 0, g_slot2Calls = 0;
static long long g_slot0Self = 0, g_slot0Arg = 0;
static bool g_slot0Ok = true;
static bool Slot0(void* self, long long arg) {
    ++g_slot0Calls; g_slot0Self = (long long)self; g_slot0Arg = arg; return g_slot0Ok;
}
static void Slot2(void* self) { (void)self; ++g_slot2Calls; }
static void H1(void) {}
static int g_hReg = 0;
static void Slot38(long long self) { (void)self; }
static void Slot40(long long self, long long v) { (void)self; (void)v; }
static void* g_vt38[16];
static long long g_obj3[1];
int main() {
    for (int i = 0; i < 16; ++i) g_vt38[i] = (void*)&Slot38;
    g_vt38[8] = (void*)&Slot40;                    // the objects table: +0x38 open, +0x40 configure
    g_obj3[0] = (long long)g_vt38;
    long long* table3 = g_obj3;
    g_engVt[0] = (void*)&Slot0; g_engVt[1] = (void*)&H1; g_engVt[2] = (void*)&Slot2;
    g_pfnNpcCalloc = &Calloc;
    g_pfnNpcErrno = &ErrnoPtr;
    g_pfnNpcCrtFree = &CrtFree;
    g_pfnNpcWarn_1400191c0 = &Warn;
    g_pfnNpc_140019050 = &EvErr;
    g_pfnNpcGetenv = &GetenvStub;
    g_pfnNpc_140009250 = &SprintfStub;
    g_pfnNpc_140008820 = &UpperStub;
    g_pfnNpc_140011850 = &Alloc;
    g_pfnNpcCreateIoCompletionPort = &IocpNew;
    g_pfnNpcCreateSemaphoreA = &SemNew;
    g_pfnNpcBeginThread = &Begin;
    g_pfnNpcInitializeCriticalSectionAndSpinCount = &Spin;
    g_pfnNpcCloseHandle = &CloseH;
    g_pfnNpcFree_1400119c0 = &FreeSeam;
    g_pfnNpcGetSystemInfo = &SysInfo;
    g_pfnNpcInlineLogError = &ErrLog;
    g_pfnNpcLogMessageFmt = &LogFmt;
    g_pfnNpcOperatorNew = &OperatorNew;
    g_pfnNpc_14001ced0 = &EngineSetup;
    (void)g_hReg;

    // either argument missing ends it before anything is touched
    {
        unsigned char obj[0x90]; std::memset(obj, 0xEE, sizeof obj);
        assert(FUN_140002b30((long long)obj, 0, 0x500, 0) == false);
        assert(FUN_140002b30((long long)obj, 0x400, 0, 0) == false);
        assert(*(long long*)(obj + 0x48) == (long long)0xEEEEEEEEEEEEEEEEull);
    }

    // the config cannot be allocated: its own message, nothing else
    {
        unsigned char obj[0x90]; std::memset(obj, 0, sizeof obj);
        g_cfgNull = true; g_errCalls = 0; g_errFmt = nullptr; g_crtN = 0;
        assert(FUN_140002b30((long long)obj, 0x400, (long long)table3, 0) == false);
        assert(g_errCalls == 1 && g_errFmt == (const void*)&g_symNpcStr_1400beb80);
        assert(*(void**)(obj + 0x58) == nullptr);
        g_cfgNull = false;
    }

    // no usable mechanism: the base is released again and the config after it
    {
        unsigned char obj[0x90]; std::memset(obj, 0, sizeof obj);
        g_apNpcEventSelTable_140102480[0] = nullptr;
        g_errCalls = 0; g_errFmt = nullptr; g_crtN = 0; g_warns = 0;
        assert(FUN_140002b30((long long)obj, 0x400, (long long)table3, 0) == false);
        assert(g_errCalls == 1 && g_errFmt == (const void*)&g_symNpcStr_1400bebb0);
        assert(g_warns == 1 && std::strcmp(g_warnFmt, "%s: no event mechanism available") == 0);
        assert(*(void**)(obj + 0x58) == nullptr);
        bool sawBase = false, sawCfg = false;
        for (int i = 0; i < g_crtN; ++i) {
            if (g_crtFreed[i] == (void*)g_baseBuf) sawBase = true;
            if (g_crtFreed[i] == (void*)g_cfgBuf) sawCfg = true;
        }
        assert(sawBase && sawCfg);                       // both the failed base and the config come back
    }

    // the whole chain works and stops where the socket object cannot be allocated
    {
        static NpcEventSel sel;
        sel.pszName = "epoll"; sel.pfnInit = &SelectorInit; sel.nFeatures = 0;
        g_apNpcEventSelTable_140102480[0] = &sel;
        g_apNpcEventSelTable_140102480[1] = nullptr;
        unsigned char obj[0x90]; std::memset(obj, 0, sizeof obj);
        g_errCalls = 0; g_errFmt = nullptr; g_logCalls = 0; g_beginCalls = 0;
        g_slot0Calls = 0; g_slot2Calls = 0; g_slot0Ok = true; g_newBytes = 0;
        assert(FUN_140002b30((long long)obj, 0x400, (long long)table3, 7) == false);
        assert(*(long long*)(obj + 0x48) == 0x400);      // the open call was made first
        assert(*(long long*)(obj + 0x50) == (long long)table3);
        assert(*(void**)(obj + 0x58) == (void*)g_baseBuf);   // the base came back from the real builder
        assert(*(void**)(g_baseBuf) == (void*)&sel);        // the selector itself is stored at +0
        assert(*(void**)(g_baseBuf + 8) == (void*)0xBEEF);  // and its init result at +8
        assert(*(const char**)*(void**)g_baseBuf != nullptr);  // +0 of the selector is the method name
        assert(*(int*)(g_cfgBuf + 0x10) == 6);           // the processor count went into the config
        assert(*(unsigned int*)(g_cfgBuf + 0x28) != 0);  // and the flag was set on it
        assert(g_beginCalls == 12);                      // six processors, two slots each
        assert(*(void**)(obj + 0x68) == (void*)g_engineBuf);
        assert(g_slot0Calls == 1 && g_slot0Self == (long long)g_engineBuf);
        assert(g_slot0Arg == (long long)(obj + 0x40));   // the engine is handed the thread base address
        assert(g_newBytes == 0x838);                     // then the socket object is asked for
        assert(g_errCalls == 1 && g_errFmt == (const void*)&g_symNpcStr_1400bebe0);
        assert(*(void**)(obj + 0x60) == nullptr);
        // the method name was logged through the format at 0x1400beca8
        assert(g_logCalls >= 1 && g_logFmt == (const void*)&g_symNpcStr_1400beca8);
        g_apNpcEventSelTable_140102480[0] = nullptr;
    }

    // the engine refusing its owner releases itself through slot +0x10
    {
        static NpcEventSel sel;
        sel.pszName = "epoll"; sel.pfnInit = &SelectorInit; sel.nFeatures = 0;
        g_apNpcEventSelTable_140102480[0] = &sel;
        g_apNpcEventSelTable_140102480[1] = nullptr;
        unsigned char obj[0x90]; std::memset(obj, 0, sizeof obj);
        g_slot0Calls = 0; g_slot2Calls = 0; g_slot0Ok = false; g_errCalls = 0;
        assert(FUN_140002b30((long long)obj, 0x400, (long long)table3, 0) == false);
        assert(g_slot0Calls == 1 && g_slot2Calls == 1);
        assert(g_errCalls == 0);                          // this path says nothing
        assert(*(void**)(obj + 0x68) == (void*)g_engineBuf);
        g_apNpcEventSelTable_140102480[0] = nullptr;
    }

    std::printf("NPCSERVER_D176_OK: 0x140002b30 CKernelThread::Create\n");
    return 0;
}
