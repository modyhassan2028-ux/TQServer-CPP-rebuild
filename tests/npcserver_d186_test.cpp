// D186 — NpcServer.exe 0x140014b30 (event_base_free).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdarg>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static const char* g_log[64]; static int g_logN = 0;
static void Log(const char* t) { if (g_logN < 64) g_log[g_logN] = t; ++g_logN; }
static int g_warns = 0; static const char* g_warnFmt = nullptr; static const char* g_warnArg = nullptr;
static void Warn(const char* pFmt, ...) {
    ++g_warns; g_warnFmt = pFmt;
    va_list ap; va_start(ap, pFmt); g_warnArg = va_arg(ap, const char*); va_end(ap);
}
static void* g_crtFreed[32]; static int g_crtN = 0;
static void* CrtFree(void* p) { Log("crt"); if (g_crtN < 32) g_crtFreed[g_crtN] = p; ++g_crtN; return nullptr; }
static void IocpClose(void* p, unsigned int f) { Log(p == (void*)0x1111 && f == 0xffffffffu ? "iocp" : "iocp?"); }
static void** g_queueSlotPtr = nullptr;
static void* g_pTimer1 = nullptr; static void* g_pTimer2 = nullptr;
static void Rel(void* p) {
    if (p == g_pTimer1) { Log("timer:888"); return; }
    if (p == g_pTimer2) { Log("timer:999"); return; }
    if (p == (void*)0x777) { Log("timer:777"); if (g_queueSlotPtr != nullptr) *g_queueSlotPtr = nullptr; }
    else if (p == (void*)0x888) Log("timer:888");
    else if (p == (void*)0x999) Log("timer:999");
    else Log("timer:other");
}
static long long Ord3(long long h) { Log(h == 0x55 ? "sock:55" : (h == 0x66 ? "sock:66" : "sock:?")); return 0; }
static void* g_pEventObjProbe = nullptr;
static void Acc(long long b) { (void)b; Log("acc"); }
static void Fire(long long b, void* e, int f) {
    (void)b; (void)f; Log(e == (void*)g_pEventObjProbe ? "event:aaa" : "event:?");
}
static void Q25(void* p) { (void)p; Log("q25"); }
static void Q28(void* p) { (void)p; Log("q28"); }
static void Q2(void* p) { (void)p; Log("q2"); }
static void E10(void) { Log("e10"); }
static void E90(void) { Log("e90"); }
static void SelRelease(long long* p) { (void)p; Log("evsel"); }

int main() {
    g_pfnNpcWarn_1400191c0 = &Warn;
    g_pfnNpcCrtFree = &CrtFree;
    g_pfnNpcEventFree_140103fa8 = nullptr;
    g_pfnNpc_140074d90 = &IocpClose;
    g_pfnNpc_140014300 = &Rel;
    g_pfnNpcOrdinal3 = &Ord3;
    g_pfnNpc_14001acc0 = &Acc;
    g_pfnNpc_140014a00 = &Fire;
    g_pfnNpc_14001a030 = &Q25;
    g_pfnNpc_14001a1a0 = &Q28;
    g_pfnNpc_14001af30 = &Q2;
    g_pfnNpc_140016e10 = &E10;
    g_pfnNpc_140016e90 = &E90;

    // no base and no current base: only the report
    {
        g_pNpcBase_140103f80 = nullptr; g_warns = 0; g_crtN = 0; g_logN = 0;
        FUN_140014b30(nullptr, 1);
        assert(g_warns == 1 && std::strcmp(g_warnFmt, "%s: no base to free") == 0);
        assert(std::strcmp(g_warnArg, "event_base_free_") == 0);
        assert(g_crtN == 0 && g_logN == 0);
    }

    // a fully loaded base: every sweep runs, in order, and the block goes last
    {
        static unsigned char base[0x2b0];
        static unsigned char pEntry[0x30];
        static unsigned char pTimer1[0x30], pTimer2[0x30];
        static void* pTimeoutTable[1];
        static void* pPriTable[1];
        static void* pEventObj[2];
        static long long pNode[2];
        static long long pSel[8];
        static void* pQueueSlot;
        std::memset(base, 0, sizeof base);
        std::memset(pEntry, 0, sizeof pEntry);
        std::memset(pTimer1, 0, sizeof pTimer1);
        std::memset(pTimer2, 0, sizeof pTimer2);

        *(void**)(base + 0x1f0) = (void*)0x1111;
        *(long long*)(base + 0x210) = 0x55;
        *(long long*)(base + 0x218) = 0x66;
        *(unsigned short*)(base + 0x230) = 0xFFFF;
        pQueueSlot = (void*)0x777;
        g_queueSlotPtr = &pQueueSlot;
        *(void**)(base + 0x150) = &pQueueSlot;
        *(int*)(base + 0x158) = 1;
        // one timeout entry carrying a timer at +0x18 and a two-node timer list from +0
        *(void**)(pEntry + 0x00) = pTimer1;
        g_pTimer1 = pTimer1; g_pTimer2 = pTimer2;
        *(unsigned short*)(pEntry + 0x28) = 0xFFFF;
        *(unsigned char*)(pTimer1 + 0x10) = 0x00;                    // not flagged: released
        *(void**)(pTimer1 + 0x28) = pTimer2;
        *(unsigned char*)(pTimer2 + 0x10) = 0x10;                    // flagged: skipped
        *(void**)(pTimer2 + 0x28) = nullptr;
        pTimeoutTable[0] = pEntry;
        *(void**)(base + 0x118) = pTimeoutTable;
        *(int*)(base + 0x120) = 1;
        pEventObj[0] = nullptr; pEventObj[1] = nullptr; g_pEventObjProbe = pEventObj;
        pPriTable[0] = (void*)pEventObj;
        *(void**)(base + 0xf8) = pPriTable;
        *(int*)(base + 0x100) = 1;
        *(long long*)(base + 0x108) = 0;
        // the remainder list: one node whose prev is the head itself
        pNode[0] = 0; pNode[1] = (long long)(base + 0x2a8);
        *(void**)(base + 0x2a8) = pNode;
        // the selector's own release at +0x28
        pSel[5] = (long long)&SelRelease;                            // +0x28
        *(void**)(base + 0x00) = pSel;
        *(long long*)(base + 0x1d0) = 1;
        *(long long*)(base + 0x1d8) = 1;
        g_pNpcBase_140103f80 = base;

        g_logN = 0; g_crtN = 0;
        FUN_140014b30((long long*)base, 1);

        const char* expect[] = {
            "iocp",                    // the completion port goes first, and the slot is cleared
            "timer:other",             // the socket's lock at +0x220
            "sock:55", "sock:66",
            "acc",                     // the active queue reset
            "timer:777",               // the queue head
            "timer:other",             // the entry's own timer at +0x18
            "timer:888",               // the unflagged timer of the list
            "crt",                     // the entry itself
            "crt",                     // the timeout table
            "event:aaa",               // the priority queue's first event
            "crt",                     // the remainder node
            "evsel",                   // the selector's release
            "crt",                     // the field at +0x150
            "crt",                     // the priority table at +0xf8
            "q25", "q28", "q2",        // the three sub-objects
            "e10", "e90",              // the two notifier sockets
            "crt"                      // the block itself, last
        };
        assert(g_logN == (int)(sizeof expect / sizeof expect[0]));
        for (int i = 0; i < g_logN; ++i) {
            if (std::strcmp(g_log[i], expect[i]) != 0) {
                std::fprintf(stderr, "step %d: got %s, expected %s\n", i, g_log[i], expect[i]);
                std::fflush(stderr);
                return 1;
            }
        }
        // the socket pair is closed and marked, the flags word keeps everything but 0x80
        assert(*(long long*)(base + 0x210) == -1 && *(long long*)(base + 0x218) == -1);
        assert(*(unsigned short*)(base + 0x230) == 0xFF7F);
        assert(*(void**)(base + 0x1f0) == nullptr);
        assert(*(unsigned short*)(pEntry + 0x28) == 0xFF7F);
        assert(*(void**)(base + 0x2a8) == nullptr);
        assert(g_pNpcBase_140103f80 == nullptr);                     // the current base was cleared
        assert(g_crtFreed[g_crtN - 1] == (void*)base);               // and the block was released last
        assert(g_crtN == 6);   // the entry, both tables, the node, the +0x150 block and the base
    }

    // a null base falls back to the current one
    {
        static unsigned char base2[0x2b0];
        std::memset(base2, 0, sizeof base2);
        g_pNpcBase_140103f80 = base2;
        g_logN = 0; g_crtN = 0; g_warns = 0;
        FUN_140014b30(nullptr, 0);
        assert(g_warns == 0);
        // the priority table is released unconditionally, even when it is empty, then the block
        assert(g_crtN == 2 && g_crtFreed[0] == nullptr && g_crtFreed[1] == (void*)base2);
        assert(g_pNpcBase_140103f80 == nullptr);
    }

    std::printf("NPCSERVER_D186_OK: 0x140014b30 event_base_free\n");
    return 0;
}
