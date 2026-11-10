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
// the limit and the remaining-bytes count are real bodies now: the only thing left to supply is how many bytes the
// wire has already handed over (0x14007c670 is still unported)
static int g_consumed = 0;
static int Consumed(long long w) { (void)w; return g_consumed; }
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
    g_pfnNpc_14007a700 = &Destroy;
    g_pfnNpc_14007c670 = &Consumed;      // the wire's byte count, still a seam
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

    // with a limit stamped on the wrapper: the limit is raised from what the wire already consumed, and the call
    // only succeeds when the wrapper is left with nothing unread
    {
        g_seqN = 0; g_accept = 1; g_valid = 1; g_consumed = 0x400;
        assert(FUN_1400764f0(aThis, pArg, 0) == 1);       // an allowance of zero leaves nothing unread
        assert(g_seqN == 2 && g_seq[0] == 6 && g_seq[1] == 5);
        // any allowance beyond what was consumed leaves bytes unread, and that reads as a refusal
        g_seqN = 0; g_consumed = 0;
        assert(FUN_1400764f0(aThis, pArg, 0x400) == 0);
        assert(g_seqN == 2 && g_seq[1] == 5);
        // a negative amount pins the limit at 0x7fffffff, which answers -1 before anything is compared
        g_seqN = 0;
        assert(FUN_1400764f0(aThis, pArg, -1) == 0);
        assert(g_seqN == 2 && g_seq[1] == 5);
        // invalid refuses before the remaining count is asked
        g_seqN = 0; g_valid = 0; g_consumed = 0x400;
        assert(FUN_1400764f0(aThis, pArg, 1) == 0);
        assert(g_seqN == 2 && g_seq[1] == 5);
        // the same cycle through the other forward
        g_seqN = 0; g_valid = 1; g_consumed = 0x400;
        assert(FUN_1400765b0(aThis, pArg, 0) == 1);
        assert(g_seqN == 2 && g_seq[0] == 7 && g_seq[1] == 5);
        g_seqN = 0; g_consumed = 0;
        assert(FUN_1400765b0(aThis, pArg, 2) == 0);
        assert(g_seqN == 2 && g_seq[1] == 5);
    }

    // the two remaining-bytes rules read straight off a coded input
    {
        long long aCoded[8];
        std::memset(aCoded, 0, sizeof aCoded);
        *(int*)((unsigned char*)aCoded + 0x28) = 0x7fffffff;
        assert(FUN_14007a9c0((long long)aCoded) == -1);          // unlimited answers -1
        *(int*)((unsigned char*)aCoded + 0x28) = 10;
        *(int*)((unsigned char*)aCoded + 0x18) = 4;               // four bytes consumed, nothing overrun
        assert(FUN_14007a9c0((long long)aCoded) == 6);            // the limit less what was consumed
        assert(FUN_14007a8e0((long long)aCoded, 5) == 10);        // the old limit comes back
        assert(*(int*)((unsigned char*)aCoded + 0x28) == 9);      // consumed plus the allowance

        // the pin: a negative amount sends the limit to 0x7fffffff, and settling against the old 0x7fffffff is a tie,
        // so the limit keeps the top value and reads as unlimited again
        *(int*)((unsigned char*)aCoded + 0x28) = 0x7fffffff;
        *(int*)((unsigned char*)aCoded + 0x18) = 0;
        *(int*)((unsigned char*)aCoded + 0x2c) = 0;
        *(int*)((unsigned char*)aCoded + 0x30) = 0;
        assert(FUN_14007a8e0((long long)aCoded, -1) == 0x7fffffff);
        assert(*(unsigned int*)((unsigned char*)aCoded + 0x28) == 0x7fffffff);   // pinned, not wrapped
        assert(FUN_14007a9c0((long long)aCoded) == -1);           // and the pin reads as unlimited
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
