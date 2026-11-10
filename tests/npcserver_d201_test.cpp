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
static unsigned char T350(void* a2, long long* pThis) { (void)a2; (void)pThis; Note(6); return (unsigned char)g_accept; }
static unsigned char T380(void* a2, long long* pThis) { (void)a2; (void)pThis; Note(7); return (unsigned char)g_accept; }

int main() {
    g_pfnNpc_140077530 = &Build;
    g_pfnNpc_140077520 = &Valid;
    g_pfnNpc_14007a8e0 = &Stamp;
    g_pfnNpc_14007a9c0 = &ErrState;
    g_pfnNpc_14007a700 = &Destroy;
    g_pfnNpc_1400774a0 = &T350;
    g_pfnNpc_1400774e0 = &T380;
    long long aThis[2] = { 0x111, 0x222 };
    void* pArg = (void*)0x4321;

    // accepted and valid: one, with the wrapper built, offered, checked and destroyed in that order
    {
        g_seqN = 0; g_valid = 1; g_accept = 1;
        assert(FUN_1400763b0(aThis, pArg) == 1);
        assert(g_seqN == 4);
        assert(g_seq[0] == 1 && g_seq[1] == 6 && g_seq[2] == 2 && g_seq[3] == 5);
        assert(g_buildArg == pArg);
        // refused by the thunk: zero, and the validity check never runs
        g_seqN = 0; g_accept = 0;
        assert(FUN_1400763b0(aThis, pArg) == 0);
        assert(g_seqN == 3 && g_seq[2] == 5);
        // accepted but invalid: zero as well, and the wrapper is still destroyed
        g_seqN = 0; g_accept = 1; g_valid = 0;
        assert(FUN_1400763b0(aThis, pArg) == 0);
        assert(g_seqN == 4 && g_seq[3] == 5);
    }

    // the second forward: same decisions, through 0x140076380
    {
        g_seqN = 0; g_accept = 1; g_valid = 1;
        assert(FUN_140076450(aThis, pArg) == 1);
        assert(g_seqN == 4 && g_seq[1] == 7);
        g_seqN = 0; g_accept = 0;
        assert(FUN_140076450(aThis, pArg) == 0);
        assert(g_seqN == 3 && g_seq[1] == 7);
    }

    // with a type stamped on the wrapper: the stamp comes right after the build, and the error state must be
    // zero on top of acceptance and validity
    {
        g_seqN = 0; g_accept = 1; g_valid = 1; g_error = 0; g_stampVal = -1;
        assert(FUN_1400764f0(aThis, pArg, 0x400) == 1);
        assert(g_stampVal == 0x400);
        assert(g_seqN == 6);
        assert(g_seq[0] == 1 && g_seq[1] == 3 && g_seq[2] == 6 && g_seq[3] == 2);
        assert(g_seq[4] == 4 && g_seq[5] == 5);
        // a non-zero error state refuses, and the destroy still runs last
        g_seqN = 0; g_error = -1;
        assert(FUN_1400764f0(aThis, pArg, 1) == 0);
        assert(g_seqN == 6 && g_seq[5] == 5);
        // invalid refuses before the error state is even asked
        g_seqN = 0; g_valid = 0; g_error = 0;
        assert(FUN_1400764f0(aThis, pArg, 1) == 0);
        assert(g_seqN == 5 && g_seq[3] == 2 && g_seq[4] == 5);
        // the same cycle through the other forward
        g_seqN = 0; g_valid = 1; g_error = 0;
        assert(FUN_1400765b0(aThis, pArg, 2) == 1);
        assert(g_seqN == 6 && g_seq[2] == 7 && g_seq[5] == 5);
        g_seqN = 0; g_error = 3;
        assert(FUN_1400765b0(aThis, pArg, 2) == 0);
        assert(g_seqN == 6 && g_seq[5] == 5);
    }

    // a null thunk seam answers zero rather than pretending success
    {
        g_pfnNpc_1400774a0 = nullptr;
        assert(FUN_140076350(aThis, pArg) == 0);
        g_pfnNpc_1400774a0 = &T350;
    }

    std::printf("NPCSERVER_D201_OK: 0x1400763b0/450/4f0/5b0\n");
    return 0;
}
