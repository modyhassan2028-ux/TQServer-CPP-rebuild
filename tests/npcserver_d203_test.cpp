// D203 — NpcServer.exe 0x140076790 (serialize to buffer), 0x140076910/aa0 (serialize to target).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_seq[16]; static int g_seqN = 0;
static void Note(int c) { if (g_seqN < 16) g_seq[g_seqN] = c; ++g_seqN; }
static int g_byteSize = 8;
static int SizeSlot(long long* p) { (void)p; Note(10); return g_byteSize; }
static int g_serCalls = 0;
static void SerSlot(long long* p, long long out) { (void)p; (void)out; Note(11); ++g_serCalls; }
static long long g_arrayEnd = 0;
static long long SerArraySlot(long long* p, long long buf) { (void)p; Note(12); return g_arrayEnd ? g_arrayEnd : buf + g_byteSize; }
static int g_hadError = 0;
static unsigned char HadError(long long out) { (void)out; Note(13); return (unsigned char)g_hadError; }
static long long g_room = 0;
static unsigned int g_roomSize = 0;
static long long Room(long long t, unsigned int n) { (void)t; g_roomSize = n; Note(14); return g_room; }
static int g_written = 0;
static int Written(long long t) { (void)t; Note(15); return g_written; }
static int g_coded, g_out;
static void Coded(void* pCoded, long long out, int n, int lim) { (void)pCoded; (void)out; Note(16); assert(n == g_byteSize); assert(lim == -1); }
static void Wrap(void* pOut, void* pCoded) { (void)pCoded; Note(17); }
static void DestroyOut(void* p) { (void)p; Note(18); }
static void DestroyCoded(void* p) { (void)p; Note(19); }
static int g_logLine = 0; static const char* g_logText = nullptr; static int g_fail = 0;
static void* Sink(void* pOut, int sev, const char* f, int line) { (void)pOut; (void)sev; (void)f; g_logLine = line; Note(20); return pOut; }
static long long Append(long long m, const char* t) { (void)m; g_logText = t; Note(21); return m; }
static void Fail(void* f, int* t) { (void)f; (void)t; ++g_fail; Note(22); }
static void Release(long long p) { (void)p; Note(23); }

int main() {
    long long vt[12];
    std::memset(vt, 0, sizeof vt);
    vt[8] = (long long)&SizeSlot;        // +0x40
    vt[9] = (long long)&SerSlot;         // +0x48
    vt[10] = (long long)&SerArraySlot;   // +0x50
    vt[11] = (long long)&SizeSlot;       // +0x58
    long long aMsg[1] = { (long long)vt };
    g_pfnNpc_14007d760 = &Coded;
    g_pfnNpc_14007bbf0 = &Wrap;
    g_pfnNpc_140077840 = &HadError;
    g_pfnNpc_14007bc70 = &DestroyOut;
    g_pfnNpc_14007d810 = &DestroyCoded;
    g_pfnNpc_140077850 = &Room;
    g_pfnNpc_1400778a0 = &Written;
    g_pfnNpc_1400783d0 = &Sink;
    g_pfnNpc_140078030 = &Append;
    g_pfnNpc_140078580 = &Fail;
    g_pfnNpc_140078440 = &Release;
    static unsigned char aBuf[0x100];

    // into a buffer: the size, the coded output around the buffer with limit -1, the write at slot 9, and the
    // two teardowns in order
    {
        g_seqN = 0; g_hadError = 0;
        long long lRet = FUN_140076790(aMsg, (long long)aBuf);
        assert(lRet == (long long)aBuf + 8);
        assert(g_seqN == 7);
        assert(g_seq[0] == 10 && g_seq[1] == 16 && g_seq[2] == 17 && g_seq[3] == 11);
        assert(g_seq[4] == 13);
        // the buffer comes down before the coded output it was wrapped in
        assert(g_seq[5] == 18 && g_seq[6] == 19);
        assert(g_fail == 0);
        // an error in the coded output aborts through the check at line 0xe0, and the sink is released
        g_seqN = 0; g_hadError = 1;
        FUN_140076790(aMsg, (long long)aBuf);
        assert(g_logLine == 0xe0 && g_fail == 1);
        assert(std::strcmp(g_logText, "CHECK failed: !coded_out.HadError(): ") == 0);
        assert(g_seq[g_seqN - 1] == 19);          // the coded output still comes down last
        g_hadError = 0;
    }

    // into a target with no room handed back: the write counts bytes through the target
    {
        g_seqN = 0; g_room = 0; g_hadError = 0; g_written = 0; g_byteSize = 8; g_serCalls = 0;
        unsigned long long u = FUN_140076aa0(aMsg, 0x5000);
        assert(u == 1);
        assert(g_roomSize == 8);                  // the target was asked for the byte size
        assert(g_serCalls == 1);
        // into a target with room: the array writer is used and must end exactly at the byte size
        g_seqN = 0; g_room = 0x6000; g_arrayEnd = 0;
        u = FUN_140076aa0(aMsg, 0x5000);
        assert(u == 1);
        assert(g_seq[2] == 12);                   // the array writer at slot 10
        // a short write runs the consistency check, which reports and still answers one
        g_seqN = 0; g_arrayEnd = 0x6000 + 3; g_fail = 0;
        u = FUN_140076aa0(aMsg, 0x5000);
        assert(u == 1);
        // the produced count differs, so the second check and the unconditional third both fire
        assert(g_fail == 2 && g_logLine == 0x45);
        g_arrayEnd = 0;
        // an error from the target refuses with zero
        g_room = 0; g_hadError = 1;
        u = FUN_140076aa0(aMsg, 0x5000);
        assert(u == 0);
        g_hadError = 0;
    }

    // the forwarder reaches the same body
    {
        g_room = 0; g_written = 0; g_hadError = 0;
        g_serCalls = 0;
        FUN_140076910(aMsg, 0x7000);
        assert(g_serCalls == 1);
    }

    std::printf("NPCSERVER_D203_OK: 0x140076790/910/aa0\n");
    return 0;
}
