// D201 — NpcServer.exe 0x1400763b0, 0x140076450, 0x1400764f0, 0x1400765b0 (wrapper accept/reject cycles).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_seq[16]; static int g_seqN = 0;
static void Note(int code) { if (g_seqN < 16) g_seq[g_seqN] = code; ++g_seqN; }
static void* g_wrapper = nullptr; static void* g_buildArg = nullptr;
static void Build(void* w, void* a2) { g_wrapper = w; g_buildArg = a2; Note(1); }
static int g_valid = 1;
static unsigned char Valid(long long w) { (void)w; Note(2); return (unsigned char)g_valid; }
static int g_stampVal = -1;
static void Stamp(long long w, int v) { (void)w; g_stampVal = v; Note(3); }
static int g_error = 0;
static int ErrState(long long w) { (void)w; Note(4); return g_error; }
static void Destroy(void* w) { (void)w; Note(5); }
static int g_accept = 1;
// the handler marks the wrapper it was handed: +0x24 is the validity byte the real check reads back
// the offer thunks are real now: what answers is the seam at the last hop, 0x140077370, which also marks the
// wrapper it was handed
static unsigned char T370(void* a2, long long* pThis) {
    (void)pThis;
    *(unsigned char*)((unsigned char*)a2 + 0x24) = (unsigned char)(g_accept != 0 ? g_valid : 0);
    Note(6); return (unsigned char)g_accept;
}
static int g_closed = 0;
static void Closer(long long* p) { (void)p; ++g_closed; }
static int g_slot7 = 0;
static unsigned char Slot7(long long* p, void* a) {
    (void)p;
    *(unsigned char*)((unsigned char*)a + 0x24) = (unsigned char)(g_accept != 0 ? g_valid : 0);
    ++g_slot7; Note(7); return (unsigned char)g_accept;
}


int main() {
    g_pfnNpc_140077370 = &T370;
    g_pfnNpc_14007a8e0 = &Stamp;
    g_pfnNpc_14007a9c0 = &ErrState;
    g_pfnNpc_14007a700 = &Destroy;
    long long aThisVt[8];
    std::memset(aThisVt, 0, sizeof aThisVt);
    aThisVt[3] = (long long)&Closer;          // +0x18, closed before the work
    aThisVt[7] = (long long)&Slot7;           // +0x38, the second path's own answer
    long long aThis[2] = { (long long)aThisVt, 0x222 };
    void* pArg = (void*)0x4321;

    // accepted and valid: the real wrapper is built (its validity byte cleared), the handler marks it, the
    // validity check reads it back, and the wrapper is destroyed last
    {
        g_seqN = 0; g_valid = 1; g_accept = 1;
        assert(FUN_1400763b0(aThis, pArg) == 1);
        assert(g_seqN == 2 && g_seq[0] == 6 && g_seq[1] == 5);
        // refused by the thunk: zero, and the validity check never runs, so the byte stays clear
        g_seqN = 0; g_accept = 1; g_valid = 0;
        assert(FUN_1400763b0(aThis, pArg) == 0);
        assert(g_seqN == 2 && g_seq[1] == 5);
        g_accept = 1; g_valid = 1;
    }

    // the second forward: same decisions, through 0x140076380
    {
        g_seqN = 0; g_accept = 1; g_valid = 1; g_closed = 0; g_slot7 = 0;
        assert(FUN_140076450(aThis, pArg) == 1);
        assert(g_seqN == 2 && g_seq[0] == 7 && g_seq[1] == 5);
        assert(g_closed == 1 && g_slot7 == 1);
        // the object refusing through its own slot reads as refused, and the wrapper still comes down
        g_seqN = 0; g_accept = 0;
        assert(FUN_140076450(aThis, pArg) == 0);
        assert(g_seqN == 2 && g_seq[1] == 5);
        g_accept = 1; g_valid = 1;
    }

    // with a type stamped on the wrapper: the stamp comes right after the build, and the error state must be
    // zero on top of acceptance and validity
    {
        g_seqN = 0; g_accept = 1; g_valid = 1; g_error = 0; g_stampVal = -1;
        assert(FUN_1400764f0(aThis, pArg, 0x400) == 1);
        assert(g_stampVal == 0x400);
        assert(g_seqN == 4);
        assert(g_seq[0] == 3 && g_seq[1] == 6 && g_seq[2] == 4 && g_seq[3] == 5);
        // a non-zero error state refuses, and the destroy still runs last
        g_seqN = 0; g_error = -1;
        assert(FUN_1400764f0(aThis, pArg, 1) == 0);
        assert(g_seqN == 4 && g_seq[3] == 5);
        // invalid refuses before the error state is even asked
        g_seqN = 0; g_valid = 0; g_error = 0;
        assert(FUN_1400764f0(aThis, pArg, 1) == 0);
        assert(g_seqN == 3 && g_seq[2] == 5);
        // the same cycle through the other forward
        g_seqN = 0; g_valid = 1; g_error = 0;
        assert(FUN_1400765b0(aThis, pArg, 2) == 1);
        assert(g_seqN == 4 && g_seq[1] == 7 && g_seq[3] == 5);
        g_seqN = 0; g_error = 3;
        assert(FUN_1400765b0(aThis, pArg, 2) == 0);
        assert(g_seqN == 4 && g_seq[3] == 5);
    }

    // a null seam at the last hop answers zero rather than pretending success
    {
        long long aWrap[10];
        std::memset(aWrap, 0, sizeof aWrap);
        g_pfnNpc_140077370 = nullptr;
        assert(FUN_140076350(aThis, aWrap) == 0);
        g_pfnNpc_140077370 = &T370;
    }

    std::printf("NPCSERVER_D201_OK: 0x1400763b0/450/4f0/5b0\n");
    return 0;
}
