// D196 — NpcServer.exe 0x140075740 (queue teardown), 0x1400757e0 (list walk), 0x140075840 (write accounting).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static long long g_mech[4];
static unsigned char g_qobj[0x38];
static void* g_order[16]; static int g_orderN = 0;
static void FreeSeam(void* p) { if (g_orderN < 16) g_order[g_orderN] = p; ++g_orderN; }
static int g_b930 = 0; static long long g_b930Self = 0;
static void B930(long long self, void* a, void* b, void* c) {
    (void)a; (void)b; (void)c; ++g_b930; g_b930Self = self;
}
static void* g_reset[16]; static unsigned int g_resetVal[16]; static int g_resetN = 0;
static void Dcb0(void* p, unsigned int v) {
    if (g_resetN < 16) { g_reset[g_resetN] = p; g_resetVal[g_resetN] = v; }
    ++g_resetN;
}
static int g_d9a0 = 0; static int g_d9a0Value = -1;
static void D9a0(long long p, int v) { (void)p; ++g_d9a0; g_d9a0Value = v; }
static int g_c160 = 0, g_c220 = 0, g_e30 = 0;
static void C160(long long p) { (void)p; ++g_c160; }
static void C220(void* p) { (void)p; ++g_c220; }
static void E30(void) { ++g_e30; }

int main() {
    g_pfnNpcFree_1400119c0 = &FreeSeam;
    g_pfnNpc_14001b930 = &B930;
    g_pfnNpc_14000dcb0 = &Dcb0;
    g_pfnNpc_14000d9a0 = &D9a0;
    g_pfnNpc_14000c160 = &C160;
    g_pfnNpc_14000c220 = &C220;
    g_pfnNpc_140016e30 = &E30;

    // the queue teardown: the mechanism's own teardown first, then the five buffers in offset order, then the
    // object itself, with all seven words cleared before the last release
    {
        static unsigned char b1[8], b2[8], b3[8], b4[8], b5[8];
        std::memset(g_qobj, 0, sizeof g_qobj);
        *(void**)(g_qobj + 8) = b1;
        *(void**)(g_qobj + 0x10) = b2;
        *(void**)(g_qobj + 0x18) = b3;
        *(void**)(g_qobj + 0x20) = b4;
        *(void**)(g_qobj + 0x28) = b5;
        g_mech[1] = (long long)g_qobj;
        g_orderN = 0; g_b930 = 0; g_b930Self = 0;
        FUN_140075740((long long)g_mech, (void*)0x11, (void*)0x22, (void*)0x33);
        assert(g_b930 == 1 && g_b930Self == (long long)g_mech);
        assert(g_orderN == 6);
        assert(g_order[0] == b1 && g_order[1] == b2 && g_order[2] == b3);
        assert(g_order[3] == b4 && g_order[4] == b5 && g_order[5] == (void*)g_qobj);
        for (int i = 0; i < 7; ++i) assert(*(void**)(g_qobj + i * 8) == nullptr);
        // a missing buffer is simply skipped
        std::memset(g_qobj, 0, sizeof g_qobj);
        *(void**)(g_qobj + 0x10) = b2;
        g_orderN = 0;
        FUN_140075740((long long)g_mech, nullptr, nullptr, nullptr);
        assert(g_orderN == 2 && g_order[0] == b2 && g_order[1] == (void*)g_qobj);
    }

    // the list walk: exactly as many entries as +0xa0 says, each reset with the value
    {
        unsigned char base[0x200];
        std::memset(base, 0, sizeof base);
        static long long n1[4], n2[4], n3[4], n4[4];
        *(void**)(base + 0x98) = n2;                  // the walk starts at the field's own value
        n2[0] = (long long)n3; n3[0] = (long long)n4; n4[0] = 0;
        *(int*)(base + 0xa0) = 3;
        g_resetN = 0;
        FUN_1400757e0((long long)base, 0x55);
        assert(g_resetN == 3);
        assert(g_reset[0] == (void*)n2 && g_reset[1] == (void*)n3 && g_reset[2] == (void*)n4);
        assert(g_resetVal[0] == 0x55 && g_resetVal[2] == 0x55);
        // a count of zero walks nothing
        *(int*)(base + 0xa0) = 0;
        g_resetN = 0;
        FUN_1400757e0((long long)base, 1);
        assert(g_resetN == 0);
    }

    // the write accounting over three segments with 25 bytes: 10 into the first node, 15 into the second
    {
        static unsigned char buf[0x200];
        static long long nodeA[8], nodeB[8], nodeC[8], nodeD[8], nodeE[8];
        static long long list1[2], list2[2], list3[2];
        std::memset(buf, 0, sizeof buf);
        std::memset(nodeA, 0, sizeof nodeA); std::memset(nodeB, 0, sizeof nodeB);
        std::memset(nodeC, 0, sizeof nodeC); std::memset(nodeD, 0, sizeof nodeD);
        std::memset(nodeE, 0, sizeof nodeE);
        nodeA[0] = (long long)nodeB;
        nodeB[0] = (long long)nodeC;
        nodeC[0] = (long long)nodeD;
        nodeD[0] = (long long)nodeE;
        nodeE[0] = 0;
        *(unsigned char*)((unsigned char*)nodeB + 0x20) = 0;   // keeps the first node out of the walk
        *(void**)(buf + 0x10) = nodeA;                          // pBuf[2]
        *(unsigned char*)(buf + 0x38) = 0x10;                   // pBuf[7] byte: the buffer is its own target
        *(unsigned int*)(buf + 0x90) = 0xffffffffu;
        list1[0] = (long long)list2; list2[0] = (long long)list3; list3[0] = 0;
        *(void**)(buf + 0x98) = list1;
        *(int*)(buf + 0xa0) = 3;
        *(unsigned int*)(buf + 0xa8) = 10;
        *(unsigned int*)(buf + 0xb8) = 20;
        *(unsigned int*)(buf + 0xc8) = 30;
        g_resetN = 0; g_d9a0 = 0; g_c160 = 0; g_c220 = 0; g_e30 = 0;
        FUN_140075840((void**)buf, 25);
        assert(*(long long*)((unsigned char*)nodeC + 0x18) == 10);   // the first segment's bytes
        assert(*(long long*)((unsigned char*)nodeD + 0x18) == 15);   // the remainder of the second
        assert(*(long long*)((unsigned char*)nodeE + 0x18) == 0);
        // the field is written back before the chain steps on, so it holds the node whose successor
        // received the last bytes, one step behind nodeD
        assert(*(void**)(buf + 0x10) == (void*)nodeC);
        assert(*(long long*)(buf + 0x18) == 25 && *(long long*)(buf + 0x20) == 25);
        assert((*(unsigned int*)(buf + 0x90) & 1u) == 0);
        assert(g_d9a0 == 1 && g_d9a0Value == 0);
        assert(g_resetN == 3 && g_resetVal[0] == 0x10 && g_resetVal[2] == 0x10);
        assert(g_c160 == 1 && g_c220 == 1);
        assert(g_e30 == 0);                                          // no unlock handle
    }

    // an unlock handle at +0x30 makes the write run the hook first, and the totals add up again
    {
        static unsigned char buf[0x200];
        static long long nodeA[8], nodeB[8], nodeC[8], listA[2];
        std::memset(buf, 0, sizeof buf);
        std::memset(nodeA, 0, sizeof nodeA); std::memset(nodeB, 0, sizeof nodeB);
        std::memset(nodeC, 0, sizeof nodeC);
        listA[0] = 0;
        *(void**)(buf + 0x98) = listA;                  // the reset list carries one entry
        nodeA[0] = (long long)nodeB;
        nodeB[0] = (long long)nodeC;
        nodeC[0] = 0;
        *(unsigned char*)((unsigned char*)nodeB + 0x20) = 0;
        *(void**)(buf + 0x10) = nodeA;
        *(void**)(buf + 0x30) = (void*)0x1234;          // pBuf[6]: the unlock handle
        *(unsigned char*)(buf + 0x38) = 0x10;
        *(unsigned int*)(buf + 0x90) = 1;
        *(int*)(buf + 0xa0) = 1;
        *(unsigned int*)(buf + 0xa8) = 7;
        g_resetN = 0; g_d9a0 = 0; g_c160 = 0; g_c220 = 0; g_e30 = 0;
        FUN_140075840((void**)buf, 7);
        assert(g_e30 == 1);
        assert(*(long long*)((unsigned char*)nodeC + 0x18) == 7);
        assert(*(long long*)(buf + 0x18) == 7 && *(long long*)(buf + 0x20) == 7);
        assert(g_resetN == 1 && g_c160 == 1 && g_c220 == 1);
        // asking for nothing still runs the hooks and the reset but moves no bytes
        g_resetN = 0; g_c160 = 0; g_c220 = 0; g_e30 = 0;
        FUN_140075840((void**)buf, 0);
        assert(g_e30 == 1 && g_resetN == 1 && g_c160 == 1 && g_c220 == 1);
        assert(*(long long*)(buf + 0x18) == 7);          // unchanged
    }

    std::printf("NPCSERVER_D196_OK: 0x140075740/e0/840\n");
    return 0;
}
