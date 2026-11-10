// D204 — NpcServer.exe 0x140076be0, 0x140076c40, 0x140076ca0 (forwards) and 0x140076e30 (append to string).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_seqN = 0; static int g_seq[16];
static void Note(int c) { if (g_seqN < 16) g_seq[g_seqN] = c; ++g_seqN; }
static unsigned long long g_wrapTarget = 0;
static void Wrap(void* pOut, void* pCoded) { (void)pOut; g_wrapTarget = (unsigned long long)(long long)pCoded; Note(1); }
static void Destroy(void* p) { (void)p; Note(2); }
static int g_byteSize = 8;
static int SizeSlot(long long* p) { (void)p; Note(3); return g_byteSize; }
static void SerSlot(long long* p, long long out) { (void)p; (void)out; Note(4); }
static long long g_arrayEndDelta = 0;
static long long SerArraySlot(long long* p, long long buf) { (void)p; Note(5); return buf + (g_arrayEndDelta ? g_arrayEndDelta : g_byteSize); }
static unsigned char HadError(long long o) { (void)o; Note(6); return 0; }
static long long Room(long long t, unsigned int n) { (void)t; (void)n; Note(7); return 0; }
static int Written(long long t) { (void)t; Note(8); return 0; }
static long long g_resizeTo = -1;
static void Resize(std::string* p, long long n) { (void)p; g_resizeTo = n; Note(9); }
static unsigned char g_strBuf[0x100];
static long long DataOf(std::string* p) { (void)p; Note(10); return (long long)g_strBuf; }
static int g_logLine = 0, g_fail = 0;
static void* Sink(void* pOut, int sev, const char* f, int line) { (void)pOut; (void)sev; (void)f; g_logLine = line; return pOut; }
static long long Append(long long m, const char* t) { (void)m; (void)t; return m; }
static void Fail(void* f, int* t) { (void)f; (void)t; ++g_fail; }
static void Release(long long p) { (void)p; }

static void LogSink(int nSeverity, const char* pszFile, int nLine, std::string* pText) {
    (void)nSeverity; (void)pszFile; (void)pText;
    g_logLine = nLine;
    ++g_fail;
}

int main() {
    long long vt[12];
    std::memset(vt, 0, sizeof vt);
    vt[8] = (long long)&SizeSlot;      // +0x40
    vt[9] = (long long)&SerSlot;       // +0x48
    vt[10] = (long long)&SerArraySlot; // +0x50
    long long aMsg[1] = { (long long)vt };
    g_pfnNpc_14007bbf0 = &Wrap;
    g_pfnNpc_14007bc70 = &Destroy;
    g_pfnNpc_140077840 = &HadError;
    g_pfnNpc_140077850 = &Room;
    g_pfnNpc_1400778a0 = &Written;
    g_pfnNpc_140077900 = &Resize;
    g_pfnNpc_140077930 = &DataOf;
    g_pfnNpcLogSink_1401035c8 = &LogSink;   // the real log bodies now reach this seam

    // the two coded-output wrappers: wrap, serialize, destroy, and hand back the low byte only
    {
        static unsigned char target[0x40];
        g_seqN = 0; g_wrapTarget = 0; g_byteSize = 8;
        unsigned char b = FUN_140076be0(aMsg, (long long)target);
        assert(b == 1);
        assert(g_wrapTarget == (unsigned long long)(long long)target);
        assert(g_seq[0] == 1 && g_seq[g_seqN - 1] == 2);    // wrapped first, destroyed last
        g_seqN = 0; g_arrayEndDelta = 0;
        b = FUN_140076c40(aMsg, (long long)target);
        assert(b == 1);
        assert(g_seq[0] == 1 && g_seq[g_seqN - 1] == 2);
        // the wrapper's own answer decides; a mismatched write inside still reports one
        g_arrayEndDelta = 2; g_fail = 0;
        b = FUN_140076c40(aMsg, (long long)target);
        assert(b == 1 && g_fail == 2);
        g_arrayEndDelta = 0;
    }

    // appending to a string: the string grows by the byte size, and the write starts after its old contents
    {
        std::string s("abc");
        g_seqN = 0; g_resizeTo = -1; g_byteSize = 8; g_fail = 0; g_arrayEndDelta = 0;
        unsigned long long u = FUN_140076e30(aMsg, &s);
        assert(u == 1);
        assert(g_resizeTo == 3 + 8);                        // old size plus the byte size
        // byte size, then the resize, then the data pointer, then the write into it
        assert(g_seqN == 4);
        assert(g_seq[0] == 3 && g_seq[1] == 9 && g_seq[2] == 10 && g_seq[3] == 5);
        // the same through the forwarder
        g_seqN = 0; g_resizeTo = -1;
        FUN_140076ca0(aMsg, &s);
        assert(g_resizeTo == 3 + 8 && g_seq[0] == 3);
        // a write that ends short runs the consistency check and still answers one
        g_arrayEndDelta = 1; g_fail = 0;
        u = FUN_140076e30(aMsg, &s);
        assert(u == 1 && g_fail == 2 && g_logLine == 0x45);
        g_arrayEndDelta = 0;
        // an empty string grows by exactly the byte size
        std::string e;
        g_resizeTo = -1;
        FUN_140076e30(aMsg, &e);
        assert(g_resizeTo == 8);
    }

    std::printf("NPCSERVER_D204_OK: 0x140076be0/c40/ca0/e30\n");
    return 0;
}
