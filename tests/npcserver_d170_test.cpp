// D170 — NpcServer.exe 0x140001970 .. 0x140001ba0: the counted-object helpers and CClientSocket::Create.
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"
#include "version/cqserver-78.0.11-1204/npcserver/clientsocket.h"

using namespace tq;

static int g_slot0 = 0, g_slot1 = 0, g_order = 0, g_v0 = 0, g_v1 = 0;
static int g_deletes = 0, g_logs = 0;
static const void* g_lastLog = nullptr;
static const void* g_logFile = nullptr; static int g_logLine = 0;
static int g_slot1After = 0;

static void Slot0(void* p) { (void)p; ++g_slot0; g_order = 1; }
static void Slot1(void* p) { (void)p; ++g_slot1; g_order = 2; }
static void* DelHook(void* p) { ++g_deletes; return p; }
static void LogHook(const void* m, ...) {
    ++g_logs; g_lastLog = m;
    va_list ap; va_start(ap, m);
    if (std::strstr((const char*)m, "at %s, %d.") != nullptr || m == (const void*)&g_symNpcStr_1400be4c8) {
        g_logFile = va_arg(ap, const void*);
        g_logLine = va_arg(ap, int);
    }
    va_end(ap);
}
static bool TypeInfoHook(const void* a, const void* b) { return a == b; }

// a counted object: [0]=slot0 [1]=slot1, counters at +0x10 and +0x14
static unsigned char* MakeCounted(int nFirst, int nSecond) {
    unsigned char* p = (unsigned char*)std::calloc(1, 0x20);
    *(void**)(p + 0x00) = (void*)&Slot0;
    *(void**)(p + 0x08) = (void*)&Slot1;
    *(int*)(p + 0x10) = nFirst;
    *(int*)(p + 0x14) = nSecond;
    return p;
}

static int g_iniCtor = 0, g_iniGetString = 0, g_iniGetInt = 0, g_iniDtor = 0;
static int g_iniPort = 0x1234; static char g_ip[32] = {0}; static int g_ipLen = 0;
static void IniCtorHook(void* p, const char* f, const char* s) { (void)p; ++g_iniCtor; assert(std::strcmp(f, "config.ini") == 0); assert(std::strcmp(s, "GameServer") == 0); }
static void IniGetStringHook(void* p, char* out, const char* key, int n) { (void)p; ++g_iniGetString; assert(std::strcmp(key, "GAMESERVER_IP") == 0); g_ipLen = n; std::snprintf(g_ip, sizeof g_ip, "10.1.2.3"); std::snprintf(out, (size_t)n, "%s", g_ip); }
static int IniGetIntHook(void* p, const char* key) { (void)p; ++g_iniGetInt; assert(std::strcmp(key, "GAMESERVER_PORT") == 0); return g_iniPort; }
static void IniDtorHook(void* p) { (void)p; ++g_iniDtor; }

int main() {
    g_pfnNpcOperatorDelete = &DelHook;
    g_pfnNpcInlineLogError = &LogHook;
    g_pfnNpcTypeInfoEquals = &TypeInfoHook;
    g_pfnNpcIniCtor = &IniCtorHook;
    g_pfnNpcIniGetString = &IniGetStringHook;
    g_pfnNpcIniGetInt = &IniGetIntHook;
    g_pfnNpcIniDtor = &IniDtorHook;

    // 0x140001970 — nothing to release
    {
        unsigned char owner[16] = {0};
        g_slot0 = g_slot1 = 0;
        FUN_140001970(owner);
        assert(g_slot0 == 0 && g_slot1 == 0);
    }

    // 0x140001970 — one decrement only while the first counter is above one
    {
        unsigned char owner[16] = {0};
        unsigned char* c = MakeCounted(2, 1);
        *(void**)(owner + 8) = c;
        g_slot0 = g_slot1 = 0;
        FUN_140001970(owner);
        assert(*(int*)(c + 0x10) == 1 && g_slot0 == 0 && g_slot1 == 0);
        std::free(c);
    }

    // 0x140001970 — both counters hit zero: slot 0, then slot 1, in that order
    {
        unsigned char owner[16] = {0};
        unsigned char* c = MakeCounted(1, 1);
        *(void**)(owner + 8) = c;
        g_slot0 = g_slot1 = g_order = 0;
        FUN_140001970(owner);
        assert(g_slot0 == 1 && g_slot1 == 1 && g_order == 2);
        std::free(c);
    }

    // 0x140001970 — the second counter stays above zero
    {
        unsigned char owner[16] = {0};
        unsigned char* c = MakeCounted(1, 3);
        *(void**)(owner + 8) = c;
        g_slot0 = g_slot1 = 0;
        FUN_140001970(owner);
        assert(g_slot0 == 1 && g_slot1 == 0 && *(int*)(c + 0x14) == 2);
        std::free(c);
    }

    // 0x1400019b0 — the new object is bumped, and an empty owner takes it without releasing
    {
        unsigned char owner[16] = {0};
        unsigned char* fresh = MakeCounted(1, 1);
        void* pNew = (void*)0xAA;
        g_slot0 = g_slot1 = 0;
        FUN_1400019b0((void**)owner, pNew, (long long)fresh);
        assert(*(int*)(fresh + 0x10) == 2);
        assert(*(void**)(owner + 8) == fresh && *(void**)owner == pNew);
        assert(g_slot0 == 0 && g_slot1 == 0);
        std::free(fresh);
    }

    // 0x1400019b0 — replacing releases the old one first, then stores in both branches
    {
        unsigned char owner[16] = {0};
        unsigned char* old = MakeCounted(1, 1);
        unsigned char* fresh = MakeCounted(1, 1);
        *(void**)(owner + 8) = old;
        void* pNew = (void*)0xBB;
        g_slot0 = g_slot1 = 0;
        FUN_1400019b0((void**)owner, pNew, (long long)fresh);
        assert(g_slot0 == 1 && g_slot1 == 1);
        assert(*(int*)(fresh + 0x10) == 2);
        assert(*(void**)(owner + 8) == fresh && *(void**)owner == pNew);
        std::free(old); std::free(fresh);
    }

    // 0x140001a50 — both table stores, counters, fourth word
    {
        void* obj[5] = {0};
        void* a2 = (void*)0x11; void* a3 = (void*)0x22;
        assert(FUN_140001a50(obj, a2, a3) == (void*)obj);
        assert(obj[0] == (void*)&g_symNpcVftbl_1400be3f0);
        assert(obj[1] == a2 && obj[4] == a3);
        assert(*(uint32_t*)((unsigned char*)obj + 0x10) == 0);
        assert(*(uint32_t*)((unsigned char*)obj + 0x14) == 1);
    }

    // 0x140001ab0 — the compare decides between this+0x20 and zero
    {
        unsigned char obj[0x40] = {0};
        const void* ti = (const void*)0x1234;
        assert(FUN_140001ab0((long long)obj, ti) == 0);                 // hook says different
        assert(FUN_140001ab0((long long)obj, (const void*)&g_symNpcRtti_140102090) == (long long)(obj + 0x20));
    }

    // 0x140001af0 — the pointer at +0x20 is called with the value at +8
    {
        unsigned char obj[0x40] = {0};
        static void* g_got = nullptr;
        static void (*Target)(void*) = nullptr;
        struct Local { static void Fn(void* p) { g_got = p; } };
        Target = &Local::Fn;
        *(void**)(obj + 0x20) = (void*)Target;
        *(void**)(obj + 8) = (void*)0x99;
        FUN_140001af0((long long)obj);
        assert(g_got == (void*)0x99);
    }

    // 0x140001b00 and 0x140001b40 — the table store, and the delete only on the low byte
    {
        void* obj[2] = {0};
        FUN_140001b00(obj);
        assert(obj[0] == (void*)&g_symNpcVftbl_1400be090);
        obj[0] = nullptr;
        g_deletes = 0;
        assert(FUN_140001b40(obj, 0) == (void*)obj && g_deletes == 0);
        assert(obj[0] == (void*)&g_symNpcVftbl_1400be090);
        assert(FUN_140001b40(obj, 1) == (void*)obj && g_deletes == 1);
    }

    // 0x140001ba0 — no kernel thread: the NULL message, return 0, no ini work
    {
        unsigned char* p = (unsigned char*)std::calloc(1, 0x840);
        g_logs = g_iniCtor = g_iniDtor = 0;
        assert(FUN_140001ba0((char*)p, 0) == 0);
        assert(g_logs == 1 && std::strcmp((const char*)g_lastLog,
               "CClientSocket::Create, m_pKernelThread is NULL.") == 0);
        assert(g_iniCtor == 0 && g_iniDtor == 0);
        assert(*(long long*)(p + 0x828) == 0);         // assigned before the check
        std::free(p);
    }

    // 0x140001ba0 — the port is missing, so 0x16b8 is used and stored as +4
    {
        unsigned char* p = (unsigned char*)std::calloc(1, 0x840);
        unsigned char eventBase[8] = {0};
        *(long long*)(p + 0x828) = 0;                  // set by the call itself
        g_iniPort = 0; g_logs = 0; g_iniCtor = g_iniGetString = g_iniGetInt = g_iniDtor = 0;
        g_logFile = nullptr; g_logLine = 0;
        // Open fails here (no seams for it yet), which is the body's own error branch
        assert(FUN_140001ba0((char*)p, (long long)eventBase) == 1);
        assert(g_iniCtor == 1 && g_iniGetString == 1 && g_iniGetInt == 1 && g_iniDtor == 1);
        assert(*(int*)(p + 0x10) == 0x16b8 + 4);
        assert(g_logs >= 1);
        // the port message carries the unit path and line 0x81
        assert(g_logFile != nullptr && std::strcmp((const char*)g_logFile,
               "f:\\version\\cqserver-78.0.11-1204\\npcserver\\clientsocket.cpp") == 0);
        assert(g_logLine == 0x81);
        std::free(p);
    }

    std::printf("NPCSERVER_D170_OK: 0x140001970..0x140001ba0, 8 bodies\n");
    return 0;
}
