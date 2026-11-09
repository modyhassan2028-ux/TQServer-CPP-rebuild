// D178 — NpcServer.exe 0x140016880 / 0x140016890 / 0x140016990: libevent thread-callback registrars.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static void F1(void) {} static void F2(void) {} static void F3(void) {} static void F4(void) {} static void F5(void) {}

static int g_warns = 0;
static const char* g_warnFmt = nullptr;
static void Warn(const char* pFmt, ...) { ++g_warns; g_warnFmt = pFmt; }
static int g_followCalls = 0, g_followA = -1;
static long long g_followB = -1;
static int g_followRet = 7;
static int Follow(int nFlag, long long nZero, unsigned long long a3, unsigned long long a4) {
    (void)a3; (void)a4; ++g_followCalls; g_followA = nFlag; g_followB = nZero; return g_followRet;
}

static NpcEvthreadCbs Make(int api, int res, void* a, void* b, void* c, void* d) {
    NpcEvthreadCbs s; s.nApiVersion = api; s.nReserved = res;
    s.pfn[0] = a; s.pfn[1] = b; s.pfn[2] = c; s.pfn[3] = d;
    return s;
}
static void Reset(void) {
    g_nNpcEvthreadDebug_140103fb0 = 0;
    g_npcLockCbs_140103fb8 = NpcEvthreadCbs();
    g_npcLockCbsOrig_140104010 = NpcEvthreadCbs();
    g_npcCondCbs_140103fe8 = NpcEvthreadCbs();
    g_npcCondCbsOrig_140104038 = NpcEvthreadCbs();
    g_pNpcCondCopy_140103ff0 = g_pNpcCondCopy_140103ff8 = g_pNpcCondCopy_140104000 = nullptr;
    g_warns = 0; g_warnFmt = nullptr; g_followCalls = 0; g_followA = -1; g_followB = -1;
}
static bool Same(const NpcEvthreadCbs& a, const NpcEvthreadCbs& b) {
    return a.nApiVersion == b.nApiVersion && a.nReserved == b.nReserved &&
           a.pfn[0] == b.pfn[0] && a.pfn[1] == b.pfn[1] && a.pfn[2] == b.pfn[2] && a.pfn[3] == b.pfn[3];
}

int main() {
    g_pfnNpcWarn_1400191c0 = &Warn;
    g_pfnNpc_1400121b0 = &Follow;

    // 0x140016880 stores whatever it is handed
    {
        FUN_140016880((void*)0x1234);
        assert(g_pNpcData_140103fe0 == (void*)0x1234);
        FUN_140016880(nullptr);
        assert(g_pNpcData_140103fe0 == nullptr);
    }

    // an empty request on an empty table is quiet and zeroes it
    {
        Reset();
        assert(FUN_140016890(nullptr, 0x11, 0x22, 0x33) == 0);
        assert(g_warns == 0);
        assert(Same(g_npcLockCbs_140103fb8, NpcEvthreadCbs()));
    }

    // the first complete request is copied and followed by 0x1400121b0(1, 0)
    {
        Reset();
        NpcEvthreadCbs cbs = Make(1, 1, (void*)&F1, (void*)&F2, (void*)&F3, (void*)&F4);
        assert(FUN_140016890(&cbs, 0x11, 0x22, 0x33) == 7);
        assert(Same(g_npcLockCbs_140103fb8, cbs));
        assert(g_followCalls == 1 && g_followA == 1 && g_followB == 0);

        // the identical repeat answers zero and does not call the follow-up again
        assert(FUN_140016890(&cbs, 0, 0, 0) == 0);
        assert(g_followCalls == 1 && g_warns == 0);

        // a change is refused with a warning that carries the installed alloc pointer
        NpcEvthreadCbs other = Make(1, 1, (void*)&F1, (void*)&F2, (void*)&F3, (void*)&F5);
        assert(FUN_140016890(&other, 0, 0, 0) == -1);
        assert(g_warns == 1 && g_warnFmt == g_symNpcStr_LockChange);

        // a request with a hole is refused too, and quietly
        Reset();
        NpcEvthreadCbs holed = Make(1, 1, (void*)&F1, nullptr, (void*)&F3, (void*)&F4);
        assert(FUN_140016890(&holed, 0, 0, 0) == -1);
        assert(g_warns == 0 && Same(g_npcLockCbs_140103fb8, NpcEvthreadCbs()));

        // and disabling a table that is already set warns and clears it
        Reset();
        assert(FUN_140016890(&cbs, 0, 0, 0) == 7);
        g_warns = 0;
        assert(FUN_140016890(nullptr, 0, 0, 0) == 0);
        assert(g_warns == 1 && g_warnFmt == g_symNpcStr_LockDisable);
        assert(Same(g_npcLockCbs_140103fb8, NpcEvthreadCbs()));
    }

    // with the debug flag set the original table is the one that is written
    {
        Reset();
        g_nNpcEvthreadDebug_140103fb0 = 1;
        NpcEvthreadCbs cbs = Make(1, 1, (void*)&F1, (void*)&F2, (void*)&F3, (void*)&F4);
        assert(FUN_140016890(&cbs, 0, 0, 0) == 7);
        assert(Same(g_npcLockCbsOrig_140104010, cbs));
        assert(Same(g_npcLockCbs_140103fb8, NpcEvthreadCbs()));
    }

    // the condition registrar: the same shape, but the second header word is not compared
    {
        Reset();
        NpcEvthreadCbs cbs = Make(2, 5, (void*)&F1, (void*)&F2, (void*)&F3, (void*)&F4);
        assert(FUN_140016990(&cbs, 0, 0, 0) == 0);
        assert(Same(g_npcCondCbs_140103fe8, cbs));
        assert(g_pNpcCondCopy_140103ff0 == nullptr);          // no copies without the debug flag

        NpcEvthreadCbs again = Make(2, 9, (void*)&F1, (void*)&F2, (void*)&F3, (void*)&F4);
        assert(FUN_140016990(&again, 0, 0, 0) == 0);          // the reserved word is ignored
        assert(g_warns == 0);

        NpcEvthreadCbs changed = Make(2, 5, (void*)&F1, (void*)&F2, (void*)&F5, (void*)&F4);
        assert(FUN_140016990(&changed, 0, 0, 0) == 0xffffffffull);
        assert(g_warns == 1 && g_warnFmt == g_symNpcStr_CondChange);

        g_warns = 0;
        assert(FUN_140016990(nullptr, 0, 0, 0) == 0);
        assert(g_warns == 1 && g_warnFmt == g_symNpcStr_CondDisable);
        assert(Same(g_npcCondCbs_140103fe8, NpcEvthreadCbs()));
    }

    // with the debug flag the original table is written and the first three pointers are echoed
    {
        Reset();
        g_nNpcEvthreadDebug_140103fb0 = 1;
        NpcEvthreadCbs cbs = Make(2, 5, (void*)&F1, (void*)&F2, (void*)&F3, (void*)&F4);
        assert(FUN_140016990(&cbs, 0, 0, 0) == 0);
        assert(Same(g_npcCondCbsOrig_140104038, cbs));
        assert(Same(g_npcCondCbs_140103fe8, NpcEvthreadCbs()));
        assert(g_pNpcCondCopy_140103ff0 == (void*)&F1);
        assert(g_pNpcCondCopy_140103ff8 == (void*)&F2);
        assert(g_pNpcCondCopy_140104000 == (void*)&F3);
    }

    std::printf("NPCSERVER_D178_OK: 0x140016880/6890/6990 thread callbacks\n");
    return 0;
}
