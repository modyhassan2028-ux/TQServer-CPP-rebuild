// D176 — NpcServer.exe 0x140002b30 CKernelThread::Create().
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdarg>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static const char* g_trace[24];
static int g_traceN = 0;
static void Trace(const char* s) { if (g_traceN < 24) g_trace[g_traceN] = s; ++g_traceN; }

static void* Slot38Arg = nullptr;
static long long Slot40Self = 0, Slot40Arg = 0;
static void Slot38(long long self) { Slot38Arg = (void*)self; Trace("open38"); }
static void Slot40(long long self, long long v) { Slot40Self = self; Slot40Arg = v; Trace("open40"); }
// the object the body receives holds its table in the first word, so the fixture is two levels deep
static void* g_vt38[16] = { (void*)&Slot38, (void*)&Slot38, (void*)&Slot38, (void*)&Slot38,
                            (void*)&Slot38, (void*)&Slot38, (void*)&Slot38, (void*)&Slot38,
                            (void*)&Slot38, (void*)&Slot38, (void*)&Slot38, (void*)&Slot38,
                            (void*)&Slot38, (void*)&Slot38, (void*)&Slot38, (void*)&Slot38 };
static long long g_obj3[1] = { (long long)g_vt38 };
static void* Seam5750(void* a, long long b, void* c, void* d) {
    (void)a; (void)b; (void)c; (void)d; Trace("seam5750"); return nullptr;
}
static void* g_config = (void*)0x1000;
static void* CfgNew(void) { Trace("cfgNew"); return g_config; }
static long long g_cfgFlag = -1;
static void CfgFlag(void* p, long long v) { (void)p; g_cfgFlag = v; Trace("cfgFlag"); }
static unsigned int g_cpu = 7;
static void GetSysInfo(void* p) { *(unsigned int*)((char*)p + 0x20) = g_cpu; Trace("sysinfo"); }
static unsigned int g_cfgCpu = 0;
static void CfgCpu(void* p, unsigned int n) { (void)p; g_cfgCpu = n; Trace("cfgCpu"); }
static void* g_base = (void*)0x2000;
static unsigned long long g_baseCpu = 0;
static int g_baseCalls = 0;
static void* BaseNew(void* p, unsigned long long uCpu, void* a3, void* a4) {
    (void)p; (void)a3; (void)a4; g_baseCpu = uCpu; ++g_baseCalls; Trace("baseNew"); return g_base;
}
static int g_cfgFrees = 0;
static void CfgFree(void* p) { (void)p; ++g_cfgFrees; Trace("cfgFree"); }
static const char* Method(void* p) { (void)p; Trace("method"); return "epoll"; }
static const char* g_logFmt = nullptr;
static const char* g_logStr = nullptr;
static int g_logCalls = 0;
static void LogFmt(const char* pFmt, ...) {
    g_logFmt = pFmt; ++g_logCalls;
    va_list ap; va_start(ap, pFmt);
    if (pFmt == g_symNpcStr_1400beca8) g_logStr = va_arg(ap, const char*);
    va_end(ap);
    Trace("logFmt");
}
static void* g_engine = nullptr;
static void* EngineNew(void) { Trace("engine"); return g_engine; }
static bool g_slot0Ok = true;
static long long g_slot0Self = 0, g_slot0Arg = 0;
static bool Slot0(void* self, long long arg) { g_slot0Self = (long long)self; g_slot0Arg = arg; Trace("slot0"); return g_slot0Ok; }
static int g_slot2 = 0;
static void Slot2(void* self) { (void)self; ++g_slot2; Trace("slot2"); }
// the engine the body receives is an object whose first word is its table
static void* g_engVt[3] = { (void*)&Slot0, nullptr, (void*)&Slot2 };
static long long g_engObj[1] = { (long long)g_engVt };
static int g_newBytes = 0;
static void* g_newRet = nullptr;
static void* OperatorNew(long long n) { g_newBytes = (int)n; Trace("opNew"); return g_newRet; }
static int g_errLogs = 0;
static const void* g_errFmt = nullptr;
static void ErrLog(const void* pFmt, ...) { ++g_errLogs; g_errFmt = pFmt; Trace("errLog"); }

int main() {
    g_vt38[8] = (void*)&Slot40;                       // the +0x40 slot

    g_engine = (void*)g_engObj;
    g_pfnNpcEventConfigNew_140012580 = &CfgNew;
    g_pfnNpcEventConfigFlag_140010a00 = &CfgFlag;
    g_pfnNpcGetSystemInfo = &GetSysInfo;
    g_pfnNpcEventConfigCpu_140010a20 = &CfgCpu;
    g_pfnNpcEventBaseNew_140015ed0 = &BaseNew;
    g_pfnNpcEventConfigFree_140012660 = &CfgFree;
    g_pfnNpcEventBaseMethod_140010d80 = &Method;
    g_pfnNpcLogMessageFmt = &LogFmt;
    g_pfnNpc_14001d350 = &EngineNew;
    g_pfnNpcOperatorNew = &OperatorNew;
    g_pfnNpcInlineLogError = &ErrLog;
    g_pfnNpc_140005750 = &Seam5750;

    // either argument missing ends it before anything is touched
    {
        unsigned char obj[0x80]; std::memset(obj, 0xEE, sizeof obj);
        g_traceN = 0;
        assert(FUN_140002b30((long long)obj, 0, 0x500, 0) == false);
        assert(FUN_140002b30((long long)obj, 0x400, 0, 0) == false);
        assert(g_traceN == 0);
        assert(*(long long*)(obj + 0x48) == (long long)0xEEEEEEEEEEEEEEEEull);
    }

    // a missing config stops at its own message
    {
        unsigned char obj[0x80]; std::memset(obj, 0, sizeof obj);
        long long* table3 = g_obj3;
        long long table4[1] = { (long long)&Slot40 };
        (void)table4;
        g_config = nullptr; g_traceN = 0; g_errLogs = 0;
        assert(FUN_140002b30((long long)obj, 0x400, (long long)table3, 0) == false);
        assert(g_errLogs == 1 && g_errFmt == (const void*)&g_symNpcStr_1400beb80);
        g_config = (void*)0x1000;
    }

    // a missing base is reported after the config is freed
    {
        unsigned char obj[0x80]; std::memset(obj, 0, sizeof obj);
        long long* table3 = g_obj3;
        g_base = nullptr; g_traceN = 0; g_errLogs = 0; g_cfgFrees = 0;
        assert(FUN_140002b30((long long)obj, 0x400, (long long)table3, 0) == false);
        assert(g_errLogs == 1 && g_errFmt == (const void*)&g_symNpcStr_1400bebb0);
        assert(g_cfgFrees == 1);
        assert(*(void**)(obj + 0x58) == nullptr);
        g_base = (void*)0x2000;
    }

    // a missing engine returns quietly
    {
        unsigned char obj[0x80]; std::memset(obj, 0, sizeof obj);
        long long* table3 = g_obj3;
        g_engine = nullptr; g_traceN = 0; g_errLogs = 0;
        assert(FUN_140002b30((long long)obj, 0x400, (long long)table3, 0) == false);
        assert(g_errLogs == 0);
        assert(*(void**)(obj + 0x68) == nullptr);
        g_engine = (void*)g_engObj;
    }

    // the engine refusing its owner goes through slot +0x10
    {
        unsigned char obj[0x80]; std::memset(obj, 0, sizeof obj);
        long long* table3 = g_obj3;
        g_engine = (void*)g_engObj; g_slot0Ok = false; g_slot2 = 0; g_traceN = 0; g_errLogs = 0;
        assert(FUN_140002b30((long long)obj, 0x400, (long long)table3, 0) == false);
        assert(g_slot0Ok == false && g_slot2 == 1);
        assert(g_slot0Arg == (long long)(obj + 0x40));       // the body passes +0x40
        assert(g_errLogs == 0);
        g_slot0Ok = true; g_engine = (void*)g_engObj;
    }

    // the whole opening sequence, ending where the socket allocation fails
    {
        unsigned char obj[0x80]; std::memset(obj, 0, sizeof obj);
        long long* table3 = g_obj3;
        g_traceN = 0; g_errLogs = 0; g_baseCalls = 0; g_cfgFlag = -1; g_cfgCpu = 0;
        g_cpu = 7; g_newRet = nullptr; g_slot0Ok = true;
        assert(FUN_140002b30((long long)obj, 0x400, (long long)table3, 0x9) == false);
        assert(g_traceN == 15);                              // fourteen steps plus the failure log
        assert(std::strcmp(g_trace[0], "open38") == 0);      // slot +0x38 first
        assert(std::strcmp(g_trace[1], "open40") == 0 && Slot40Arg == 0x1e);
        assert(std::strcmp(g_trace[2], "seam5750") == 0);
        assert(std::strcmp(g_trace[3], "cfgNew") == 0);
        assert(std::strcmp(g_trace[4], "cfgFlag") == 0 && g_cfgFlag == 4);
        assert(std::strcmp(g_trace[5], "sysinfo") == 0);
        assert(std::strcmp(g_trace[6], "cfgCpu") == 0 && g_cfgCpu == 7);
        assert(std::strcmp(g_trace[7], "baseNew") == 0 && g_baseCpu == 7);
        assert(std::strcmp(g_trace[8], "cfgFree") == 0);     // freed right after the base
        assert(std::strcmp(g_trace[9], "method") == 0);
        assert(std::strcmp(g_trace[10], "logFmt") == 0);
        assert(g_logFmt == g_symNpcStr_1400beca8 && g_logStr != nullptr && std::strcmp(g_logStr, "epoll") == 0);
        assert(std::strcmp(g_trace[11], "engine") == 0);
        assert(std::strcmp(g_trace[12], "slot0") == 0);
        assert(std::strcmp(g_trace[13], "opNew") == 0 && g_newBytes == 0x838);
        assert(std::strcmp(g_trace[14], "errLog") == 0);
        assert(g_newBytes == 0x838);                         // the allocation size
        assert(*(long long*)(obj + 0x48) == 0x400);
        assert(*(void**)(obj + 0x50) == (void*)g_obj3);
        assert(*(void**)(obj + 0x58) == (void*)0x2000);
        assert(*(void**)(obj + 0x68) == (void*)g_engObj);
        assert(*(void**)(obj + 0x60) == nullptr);            // the failed socket was cleared
        assert(g_errLogs == 1 && g_errFmt == (const void*)&g_symNpcStr_1400bebe0);
    }

    std::printf("NPCSERVER_D176_OK: 0x140002b30 CKernelThread::Create\n");
    return 0;
}
