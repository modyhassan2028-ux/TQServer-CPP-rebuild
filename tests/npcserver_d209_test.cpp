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
void ReleaseChain(long long* p) { (void)p; ++g_a830Calls; }
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

int main() {
    g_pfnNpcIteratorHasContainer = &HasContainer;
    g_pfnNpcStringMyPtr = &MyPtr;
    g_pfnNpcInvalidParameter = &InvalidParam;
    g_pfnNpc_14007a830 = &ReleaseChain;
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
        g_a830Calls = 0; g_fail = 0; g_release = 0; g_value = 0; g_text.clear();
        FUN_14007a700(aCoded);
        assert(g_a830Calls == 1);
        assert(g_fail == 1);
        assert(g_sinkSeverity == 1 && g_sinkLine == 0x4e);
        assert(g_sinkFile != nullptr && std::strstr(g_sinkFile, "coded_stream.cc") != nullptr);
        assert(g_text.find("The total number of bytes read was ") == 0);
        assert(g_text.find("1234") != std::string::npos);   // the count is formatted into the same message
    }

    // no chain and another state: nothing happens
    {
        long long aCoded[8];
        std::memset(aCoded, 0, sizeof aCoded);
        *(unsigned int*)((unsigned char*)aCoded + 0x34) = 7;
        g_a830Calls = 0; g_fail = 0;
        FUN_14007a700(aCoded);
        assert(g_a830Calls == 0 && g_fail == 0);
    }

    std::printf("NPCSERVER_D209_OK: 0x140077930/950/9a0/9c0 and 0x14007a700\n");
    return 0;
}
