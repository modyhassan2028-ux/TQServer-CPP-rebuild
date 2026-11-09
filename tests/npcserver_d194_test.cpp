// D194 — NpcServer.exe 0x140075210 (hand a key to the queues) and 0x140075380 (withdraw it).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static unsigned char g_q[0x38], g_a1[0x100], g_a2[0x100];
static void Reset(unsigned int nCap) {
    std::memset(g_q, 0, sizeof g_q); std::memset(g_a1, 0, sizeof g_a1); std::memset(g_a2, 0, sizeof g_a2);
    *(unsigned int*)g_q = nCap;
    *(void**)(g_q + 8) = g_a1;
    *(void**)(g_q + 0x10) = g_a2;
}
static long long g_mech[4];
static long long Link(void) { g_mech[1] = (long long)g_q; return (long long)g_mech; }
static int g_reallocCalls = 0;
static void* Realloc(void* p, unsigned long long n) { (void)n; ++g_reallocCalls; return p; }
static long long g_treeKey = 0; static int* g_node = nullptr; static int g_nodeCalls = 0;
static void* TreeFind(long long* t, long long k) { (void)t; g_treeKey = k; ++g_nodeCalls; return g_node; }

int main() {
    g_pfnNpcRealloc_1400119a0 = &Realloc;
    g_pfnNpc_14001a880 = &TreeFind;
    long long pMechanism = Link();

    // flag 8 refuses when the queue object carries bit 1 at +0x30
    {
        Reset(4); *(unsigned int*)(g_q + 0x30) = 1;
        int active[2] = { 0, 0 };
        assert(FUN_140075210(pMechanism, 0xAA, 0, 8, active) == 0xffffffffull);
        assert(*(unsigned int*)g_a1 == 0);
        *(unsigned int*)(g_q + 0x30) = 0;
        assert(FUN_140075210(pMechanism, 0xAA, 0, 8, active) == 0);   // the flag alone asks for nothing
        assert(*(unsigned int*)g_a1 == 0 && *(unsigned int*)g_a2 == 0);
    }

    // a plain hand-over with both flags: the key goes to both queues and both cursors record count + 1
    {
        Reset(4);
        int active[2] = { 0, 0 };
        assert(FUN_140075210(pMechanism, 0x11, 0, 6, active) == 0);
        assert(*(unsigned long long*)(g_a1 + 8) == 0x11);
        assert(*(unsigned long long*)(g_a2 + 8) == 0x11);
        assert(*(unsigned int*)g_a1 == 1 && *(unsigned int*)g_a2 == 1);
        assert(active[0] == 1 && active[1] == 1);
    }

    // the first cursor already holds a key: that side is skipped, the other still takes it
    {
        Reset(4);
        int active[2] = { 1, 0 };
        assert(FUN_140075210(pMechanism, 0x22, 0, 2, active) == 0);
        assert(*(unsigned int*)g_a1 == 0);              // skipped
        assert(active[0] == 1);                          // untouched
        Reset(4);
        int active2[2] = { 1, 0 };
        assert(FUN_140075210(pMechanism, 0x22, 0, 6, active2) == 0);
        assert(*(unsigned int*)g_a1 == 0);              // flag 2 skipped
        assert(*(unsigned int*)g_a2 == 1);              // flag 4 still appended
        assert(active2[1] == 1);
    }

    // a full array doubles both, and the key lands after the entries already there
    {
        Reset(2);
        *(unsigned int*)g_a1 = 2;                        // the first queue is exactly full
        int active[2] = { 0, 0 };
        g_reallocCalls = 0;
        assert(FUN_140075210(pMechanism, 0x33, 0, 2, active) == 0);
        assert(g_reallocCalls == 2);
        assert(*(unsigned int*)g_q == 4);                // the capacity doubled
        assert(*(unsigned long long*)(g_a1 + 8 + 2 * 8) == 0x33);
        assert(*(unsigned int*)g_a1 == 3 && active[0] == 3);
    }

    // withdrawing from both queues: counts come down, entries move and the node is written on both sides
    {
        Reset(4);
        *(unsigned int*)g_a1 = 4; *(unsigned int*)g_a2 = 4;
        *(unsigned long long*)(g_a1 + 8) = 0xA1;
        *(unsigned long long*)(g_a1 + 0x10) = 0xA2;
        *(unsigned long long*)(g_a1 + 0x18) = 0xA3;
        *(unsigned long long*)(g_a1 + 0x20) = 0xA4;
        *(unsigned long long*)(g_a2 + 8) = 0xB1;
        *(unsigned long long*)(g_a2 + 0x18) = 0xB3;
        *(unsigned long long*)(g_a2 + 0x20) = 0xB4;
        int active[2] = { 2, 2 };
        int node[2] = { 0, 0 };
        g_node = node; g_nodeCalls = 0; g_treeKey = 0;
        assert(FUN_140075380(pMechanism, 0, 0, 6, active) == 0);
        assert(active[0] == 0 && active[1] == 0);
        assert(*(unsigned int*)g_a1 == 3 && *(unsigned int*)g_a2 == 3);
        assert(*(unsigned long long*)(g_a1 + 0x10) == 0xA4);   // first queue: last entry took the hole
        assert(*(unsigned long long*)(g_a2 + 0x10) == 0xB4);   // second queue likewise
        assert(g_nodeCalls == 2);
        assert(node[0] == 2);                                  // the first half writes the node's first field
        assert(node[1] == 2);                                  // the second half writes the second field
        // only one flag at a time, and an empty cursor changes nothing
        g_nodeCalls = 0; active[0] = 1; active[1] = 0;
        assert(FUN_140075380(pMechanism, 0, 0, 2, active) == 0);
        assert(active[0] == 0 && g_nodeCalls == 1);
        g_nodeCalls = 0;
        assert(FUN_140075380(pMechanism, 0, 0, 2, active) == 0);   // nothing was handed out
        assert(g_nodeCalls == 0);
    }

    std::printf("NPCSERVER_D194_OK: 0x140075210/0x140075380\n");
    return 0;
}
