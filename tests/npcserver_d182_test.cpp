// D182 — NpcServer.exe 0x140015ed0 event_base_new_with_config, driving the real bodies it now calls.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdarg>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static unsigned char g_base[0x2b0];
static bool g_callocNull = false;
static void* Calloc(long long n, long long sz) {
    assert(n == 1 && sz == 0x2b0);
    if (g_callocNull) return nullptr;
    std::memset(g_base, 0, sizeof g_base);
    return g_base;
}
static int g_errno = 0;
static int* ErrnoPtr(void) { return &g_errno; }
static int g_errLogs = 0; static const char* g_errFmt = nullptr; static const char* g_errArg = nullptr;
static void ErrLog(const char* pFmt, ...) {
    ++g_errLogs; g_errFmt = pFmt;
    va_list ap; va_start(ap, pFmt); g_errArg = va_arg(ap, const char*); va_end(ap);
}
static int g_warns = 0; static const char* g_warnFmt = nullptr;
static void Warn(const char* pFmt, ...) { ++g_warns; g_warnFmt = pFmt; }
static void* g_crtFreed[8]; static int g_crtN = 0;
static void* CrtFree(void* p) { if (g_crtN < 8) g_crtFreed[g_crtN] = p; ++g_crtN; return nullptr; }
static char g_envAsked[8][0x40]; static int g_envN = 0;
static bool g_envNoMethod = false;
static char* GetenvStub(const char* n) {
    if (g_envN < 8) std::strncpy(g_envAsked[g_envN], n, 0x40);
    ++g_envN;
    if (g_envNoMethod) return (char*)"1";                        // say the method is disabled
    return nullptr;
}
static char g_fmt[32];
static int SprintfStub(char* pBuf, unsigned long long n, const char* pFmt, const char* pszArg) {
    (void)n; std::strncpy(g_fmt, pFmt, sizeof g_fmt);
    std::strcpy(pBuf, "EVENT_NO"); std::strcat(pBuf, pszArg);
    return (int)std::strlen(pBuf);
}
static unsigned char UpperStub(unsigned char c) { return (unsigned char)(c >= 'a' && c <= 'z' ? c - 32 : c); }
static unsigned char g_table[0x40], g_block[0x60], g_handles[0x40];
static void* Alloc(long long n, long long sz) {
    if (n == 1 && sz == 0x10) { std::memset(g_table, 0, sizeof g_table); return g_table; }
    if (n == 1 && sz == 0x50) { std::memset(g_block, 0, sizeof g_block); return g_block; }
    if (sz == 8) { std::memset(g_handles, 0, sizeof g_handles); return g_handles; }
    return nullptr;
}
static void* SelectorInit(void* pBase) { (void)pBase; return (void*)0xBEEF; }

int main() {
    g_pfnNpcCalloc = &Calloc;
    g_pfnNpcErrno = &ErrnoPtr;
    g_pfnNpcCrtFree = &CrtFree;
    g_pfnNpcWarn_1400191c0 = &Warn;
    g_pfnNpc_140019050 = &ErrLog;
    g_pfnNpcGetenv = &GetenvStub;
    g_pfnNpc_140009250 = &SprintfStub;
    g_pfnNpc_140008820 = &UpperStub;
    g_pfnNpc_140011850 = &Alloc;
    g_pfnNpcEventFree_140103fa8 = nullptr;
    g_nNpcFlag_140103fd0 = 0;

    // no memory: the errno and the calloc report
    {
        g_callocNull = true; g_errno = 0; g_errLogs = 0;
        assert(FUN_140015ed0(nullptr, 0, 0, nullptr) == nullptr);
        assert(g_errno == 0xc && g_errLogs == 1);
        assert(std::strcmp(g_errFmt, "%s: calloc") == 0);
        assert(std::strcmp(g_errArg, "event_base_new_with_config") == 0);
        g_callocNull = false;
    }

    // no selector at all: the defaults, the report, and the block released again
    {
        g_apNpcEventSelTable_140102480[0] = nullptr;
        g_warns = 0; g_crtN = 0; g_envN = 0;
        assert(FUN_140015ed0(nullptr, 0, 0, nullptr) == nullptr);
        assert(*(unsigned int*)(g_base + 0x1fc) == 0xffffffffu);
        assert(*(unsigned int*)(g_base + 0x204) == 0x7fffffffu);
        assert(*(unsigned int*)(g_base + 0x208) == 0x7fffffffu);       // the settle rule
        assert(*(void**)(g_base + 0x110) == (void*)(g_base + 0x108));
        assert(*(void**)(g_base + 0xf8) == nullptr);                   // no mechanism, so no priority table
        assert(*(int*)(g_base + 0x100) == 0);
        assert(g_warns == 1 && std::strcmp(g_warnFmt, "%s: no event mechanism available") == 0);
        // the empty priority field is still released, then the block
        assert(g_crtN == 2 && g_crtFreed[0] == nullptr && g_crtFreed[1] == (void*)g_base);
    }

    // one usable selector: it is stored with its init result and the base comes back
    {
        static NpcEventSel sel;
        sel.pszName = "epoll"; sel.pfnInit = &SelectorInit; sel.nFeatures = 0;
        g_apNpcEventSelTable_140102480[0] = &sel;
        g_apNpcEventSelTable_140102480[1] = nullptr;
        g_warns = 0; g_crtN = 0; g_envN = 0;
        void* p = FUN_140015ed0(nullptr, 0, 0, nullptr);
        assert(p == (void*)g_base);
        assert(*(void**)(g_base + 0x00) == (void*)&sel);
        assert(*(void**)(g_base + 0x08) == (void*)0xBEEF);
        assert(g_warns == 0 && g_crtN == 0);
        assert(*(void**)(g_base + 0xf8) == (void*)g_table);            // the priority table was built
        assert(*(int*)(g_base + 0x100) == 1);
        assert(*(void**)(*(void**)(g_base + 0xf8)) == nullptr);        // its single entry is empty
        assert(*(void**)((char*)*(void**)(g_base + 0xf8) + 8) == *(void**)(g_base + 0xf8));
        // the availability probe builds EVENT_NO<NAME> and asks for it, then the method is probed
        bool askedMethod = false, askedEpoll = false;
        for (int i = 0; i < g_envN; ++i) {
            if (std::strcmp(g_envAsked[i], "EVENT_NOEPOLL") == 0) askedEpoll = true;
            if (std::strcmp(g_envAsked[i], "EVENT_SHOW_METHOD") == 0) askedMethod = true;
        }
        assert(askedEpoll && askedMethod);
        assert(std::strcmp(g_fmt, "EVENT_NO%s") == 0);
    }

    // an avoid-list entry skips the matching selector, the next one is taken
    {
        static NpcEventSel s1, s2;
        s1.pszName = "epoll"; s1.pfnInit = &SelectorInit; s1.nFeatures = 0;
        s2.pszName = "select"; s2.pfnInit = &SelectorInit; s2.nFeatures = 0;
        g_apNpcEventSelTable_140102480[0] = &s1;
        g_apNpcEventSelTable_140102480[1] = &s2;
        g_apNpcEventSelTable_140102480[2] = nullptr;
        static struct { void* pNext; void* pPrev; char* pszName; } node;
        node.pNext = nullptr; node.pPrev = nullptr; node.pszName = (char*)"epoll";
        unsigned char cfg[0x30];
        std::memset(cfg, 0, sizeof cfg);
        *(void**)(cfg + 0) = &node;
        g_warns = 0;
        void* p = FUN_140015ed0(cfg, 0, 0, nullptr);
        assert(p == (void*)g_base);
        assert(*(void**)(g_base + 0x00) == (void*)&s2);                // "epoll" was avoided
        g_apNpcEventSelTable_140102480[0] = nullptr;
    }

    // a required feature the selector does not offer leaves no mechanism
    {
        static NpcEventSel sel;
        sel.pszName = "epoll"; sel.pfnInit = &SelectorInit; sel.nFeatures = 2;
        g_apNpcEventSelTable_140102480[0] = &sel;
        g_apNpcEventSelTable_140102480[1] = nullptr;
        unsigned char cfg[0x30];
        std::memset(cfg, 0, sizeof cfg);
        *(unsigned int*)(cfg + 0x24) = 4;
        g_warns = 0; g_crtN = 0;
        assert(FUN_140015ed0(cfg, 0, 0, nullptr) == nullptr);
        assert(g_warns == 1 && std::strcmp(g_warnFmt, "%s: no event mechanism available") == 0);
        // the empty priority field is still released, then the block
        assert(g_crtN == 2 && g_crtFreed[0] == nullptr && g_crtFreed[1] == (void*)g_base);
        g_apNpcEventSelTable_140102480[0] = nullptr;
    }

    std::printf("NPCSERVER_D182_OK: 0x140015ed0 event_base_new_with_config\n");
    return 0;
}
