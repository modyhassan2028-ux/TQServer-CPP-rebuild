// D209 — NpcServer.exe 0x140077930/950/9a0/9c0 (string data unwrap) and 0x14007a700 (coded input teardown).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include "modules/npcserver/unattributed/front-of-image.h"

namespace {
using namespace tq;

int g_hasContainerCalls = 0; int g_myPtrCalls = 0; int g_invalid = 0;
int g_a830Calls = 0; int g_sinkLine = 0; const char* g_sinkFile = nullptr; int g_sinkSeverity = 0;
std::string g_text; std::string g_logFile; int g_logLine = 0; unsigned int g_value = 0; int g_fail = 0; int g_release = 0;

bool HasContainer(void* p) { (void)p; ++g_hasContainerCalls; return true; }
bool UnknownContainer(void* p) { (void)p; ++g_hasContainerCalls; return false; }
char* MyPtr(void* p) { ++g_myPtrCalls; return *(char**)p; }   // the container's buffer word at +0x00
void InvalidParam(void) { ++g_invalid; }
// the flush is a real body now: what it needs from outside is how many bytes are still pending (0x14007c650 is
// still unported) and a sink to hand them to, reached through the object's own slot 2
int g_pending = 0, g_pendingAfter = 0, g_sinkAmount = 0; long long* g_sinkObj = nullptr;
long long Pending(long long p) { (void)p; return g_pending; }
void FlushSink(long long p, int nAmount) { g_sinkObj = (long long*)p; g_sinkAmount = nAmount; g_pending = g_pendingAfter; }
void* Sink(void* pOut, int sev, const char* file, int line) {
    g_sinkSeverity = sev; g_sinkFile = file; g_sinkLine = line; return pOut; }
long long AppendText(long long m, const char* t) { (void)m; g_text = t; return m; }   // unused since the real bodies run
int* AppendValue(long long m, unsigned int v) { g_value = v; return (int*)m; }
void Fail(void* fin, int* m) { (void)fin; (void)m; ++g_fail; }
void ReleaseSink(long long p) { (void)p; ++g_release; }

}  // namespace

static void LogSink(int nSeverity, const char* pszFile, int nLine, std::string* pText) {
    g_sinkSeverity = nSeverity;
    g_sinkFile = pszFile;
    g_sinkLine = nLine;
    if (pszFile != nullptr) g_logFile = pszFile;
    g_logLine = nLine;
    g_text = pText != nullptr ? *pText : std::string();
    ++g_fail;
}

// the log layer's one-time initialiser is a real body now, so these suites have to answer for what it needs: the
// FunctionClosure0 vtable (slot 1 runs the stored function) and the body 0x140077f50 reaches.
static long long g_onceVt[3] = { 0, 0, 0 };
static void OnceRun(void* pThis) {
    void (*pfn)(void) = *(void (**)(void))((unsigned char*)pThis + 0x08);
    if (pfn != nullptr) pfn();
}
static void OnceVtable(void) {
    g_onceVt[1] = (long long)&OnceRun;
    g_pNpcVtblFunctionClosure0 = (const void*)g_onceVt;
}

int main() {
    OnceVtable();
    g_pfnNpcIteratorHasContainer = &HasContainer;
    g_pfnNpcStringMyPtr = &MyPtr;
    g_pfnNpcInvalidParameter = &InvalidParam;
    g_pfnNpc_14007c650 = &Pending;      // how many bytes are still waiting, still a seam
    g_pfnNpcLogSink_1401035c8 = &LogSink;   // the real log bodies now reach this seam

    // the data pointer of a string
    {
        std::string s("abcdef");
        assert(FUN_140077930(&s) == (void*)s.data());
        assert(FUN_140077950(&s) == (void*)s.data());
        // The unwrap's own bound check reads the container word at +0x18, which is MSVC's string word; under this
        // library's string layout that offset is not the size, so the check may report an invalid parameter without
        // changing the answer. The value is what matters here, and the checked path itself is pinned below with a
        // container shaped the way the original expects.
        struct { long long c; char* p; } aIter = { (long long)&s, (char*)s.data() };
        assert(FUN_1400779c0(&aIter) == (void*)s.data());
    }

    // the checked path with a container carrying its size at +0x18, as the original expects
    {
        struct FakeContainer { char* pBase; char* pIgnored; size_t nIgnore; size_t nSize; };
        char aBase[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 0, 0 };
        FakeContainer aContainer = { aBase, nullptr, 0, 6 };
        struct { long long c; char* p; } it = { (long long)&aContainer, aBase };
        g_hasContainerCalls = 0; g_myPtrCalls = 0; g_invalid = 0;
        assert(FUN_1400779c0(&it) == (void*)aBase);
        assert(g_hasContainerCalls == 1 && g_myPtrCalls == 1 && g_invalid == 0);
        // an iterator sitting past the end of the buffer trips the check; one before the end does not
        it.p = aBase + 7;
        assert(FUN_1400779c0(&it) == (void*)(aBase + 7));
        assert(g_invalid == 1);
        // the end itself also trips it: the test is "base + size <= iterator", so only earlier pointers pass
        it.p = aBase + 6;
        g_invalid = 0;
        assert(FUN_1400779c0(&it) == (void*)(aBase + 6));
        assert(g_invalid == 1);
        it.p = aBase + 5;
        g_invalid = 0;
        assert(FUN_1400779c0(&it) == (void*)(aBase + 5));
        assert(g_invalid == 0);
    }

    // an empty string answers zero and never touches the iterator checks
    {
        std::string e;
        g_hasContainerCalls = 0; g_myPtrCalls = 0;
        assert(FUN_140077930(&e) == nullptr);
        assert(g_hasContainerCalls == 0 && g_myPtrCalls == 0);
    }

    // the unlinked sentinel skips the checks but still answers the pointer word
    {
        long long aIter[2] = { -4, 0x4321 };
        g_hasContainerCalls = 0;
        assert(FUN_1400779c0(aIter) == (void*)0x4321);
        assert(g_hasContainerCalls == 0 && g_myPtrCalls == 0);
    }

    // a container the check does not know reports the invalid parameter and the unwrap still answers the pointer
    {
        struct FakeContainer { char* pBase; char* pIgnored; size_t nIgnore; size_t nSize; };
        char aBase[8] = { 0 };
        FakeContainer aContainer = { aBase, nullptr, 0, 6 };
        struct { long long c; char* p; } it = { (long long)&aContainer, aBase + 2 };
        g_hasContainerCalls = 0; g_myPtrCalls = 0; g_invalid = 0;
        g_pfnNpcIteratorHasContainer = &UnknownContainer;
        assert(FUN_1400779c0(&it) == (void*)(aBase + 2));
        assert(g_hasContainerCalls == 1 && g_invalid == 1 && g_myPtrCalls == 1);
        g_pfnNpcIteratorHasContainer = &HasContainer;
    }

    // the coded input's teardown: the chain is released and the -2 state logs the byte count
    {
        long long aCoded[8];
        std::memset(aCoded, 0, sizeof aCoded);
        aCoded[0] = 0x7000;                           // a chain is attached
        *(unsigned int*)((unsigned char*)aCoded + 0x18) = 1234;
        *(unsigned int*)((unsigned char*)aCoded + 0x34) = -2;
        g_pending = 0; g_sinkAmount = 0; g_fail = 0; g_release = 0; g_value = 0; g_text.clear();
        FUN_14007a700(aCoded);
        assert(g_sinkAmount == 0);                    // nothing is waiting, so the sink is never reached
        assert(g_fail == 1);
        assert(g_sinkSeverity == 1 && g_sinkLine == 0x4e);
        assert(g_sinkFile != nullptr && std::strstr(g_sinkFile, "coded_stream.cc") != nullptr);
        assert(g_text.find("The total number of bytes read was ") == 0);
        assert(g_text.find("1234") != std::string::npos);   // the count is formatted into the same message
    }

    // the flush itself: pending plus the two counters is what the sink is handed, then the read count loses the
    // bytes that are still pending plus the counter at +0x2c, the current pointer copies back to +0x08 and both
    // counters clear
    {
        long long aVt[4] = { 0, 0, 0, 0 };
        aVt[2] = (long long)&FlushSink;               // vtable +0x10
        long long aInner[2] = { (long long)aVt, 0 }; // what the first word points at, and the word itself
        long long aObj[8];
        std::memset(aObj, 0, sizeof aObj);
        aObj[0] = (long long)aInner;
        aObj[1] = 0x1111; aObj[2] = 0x2222;
        *(unsigned int*)((unsigned char*)aObj + 0x18) = 100;
        *(unsigned int*)((unsigned char*)aObj + 0x1c) = 7;
        *(unsigned int*)((unsigned char*)aObj + 0x2c) = 5;
        g_pending = 3; g_pendingAfter = 1; g_sinkAmount = 0; g_sinkObj = nullptr;
        FUN_14007a830(aObj);
        assert(g_sinkObj == aInner && g_sinkAmount == 15);   // 3 pending + 5 + 7
        assert(*(unsigned int*)((unsigned char*)aObj + 0x18) == 100 - (1 + 5));
        assert(aObj[2] == 0x1111);                         // the current pointer comes back to +0x08
        assert(*(unsigned int*)((unsigned char*)aObj + 0x2c) == 0);
        assert(*(unsigned int*)((unsigned char*)aObj + 0x1c) == 0);
        // an amount of zero, or less, never reaches the sink and leaves the object untouched
        g_pending = 0; g_pendingAfter = 0; g_sinkAmount = 0;
        *(unsigned int*)((unsigned char*)aObj + 0x1c) = 0;
        *(unsigned int*)((unsigned char*)aObj + 0x2c) = 0;
        FUN_14007a830(aObj);
        assert(g_sinkAmount == 0);
        assert(*(unsigned int*)((unsigned char*)aObj + 0x18) == 94);
    }

    // no chain and another state: nothing happens
    {
        long long aCoded[8];
        std::memset(aCoded, 0, sizeof aCoded);
        *(unsigned int*)((unsigned char*)aCoded + 0x34) = 7;
        g_sinkAmount = 0; g_fail = 0;
        FUN_14007a700(aCoded);
        assert(g_sinkAmount == 0 && g_fail == 0);
    }

    std::printf("NPCSERVER_D209_OK: 0x140077930/950/9a0/9c0 and 0x14007a700\n");
    return 0;
}
