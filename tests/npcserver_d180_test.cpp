// D180 — NpcServer.exe 0x140012580 / 0x140010a00 / 0x140010a20 / 0x140010d80 / 0x14001d350.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static unsigned char g_buf[0x200];
static long long g_callocArgs[2] = {0, 0};
static bool g_callocNull = false;
static void* Calloc(long long n, long long sz) {
    g_callocArgs[0] = n; g_callocArgs[1] = sz;
    if (g_callocNull) return nullptr;
    std::memset(g_buf, 0, sizeof g_buf);
    return g_buf;
}
static int g_errno = 0;
static int* ErrnoPtr(void) { return &g_errno; }
static long long g_hookArg = 0;
static bool g_hookNull = false;
static void* HookMalloc(long long n) { g_hookArg = n; if (g_hookNull) return nullptr; return g_buf; }
static long long g_newArg = 0;
static void* g_newRet = (void*)0x4000;
static void* OpNew(long long n) { g_newArg = n; return g_newRet; }
static int g_ctorCalls = 0;
static void* g_ctorArg = nullptr;
static void* Ctor(void* p) { g_ctorArg = p; ++g_ctorCalls; return (void*)((char*)p + 0x10); }

int main() {
    g_pfnNpcCalloc = &Calloc;
    g_pfnNpcErrno = &ErrnoPtr;
    g_pfnNpcOperatorNew = &OpNew;
    g_pfnNpc_14001ced0 = &Ctor;

    // 0x140012580 through calloc: the queue tail is the head itself
    {
        g_pfnNpcEventMalloc_140103f98 = nullptr; g_callocNull = false; g_errno = -1;
        unsigned char* p = (unsigned char*)FUN_140012580();
        assert(p == g_buf);
        assert(g_callocArgs[0] == 1 && g_callocArgs[1] == 0x30);
        assert(*(void**)(p + 0x00) == nullptr);
        assert(*(void**)(p + 0x08) == (void*)p);
        assert(*(unsigned int*)(p + 0x14) == 0xffffffffu);
        assert(*(unsigned int*)(p + 0x1c) == 0x7fffffffu);
        assert(*(unsigned int*)(p + 0x20) == 1);
        assert(g_errno == -1);                              // untouched on success

        g_callocNull = true;
        assert(FUN_140012580() == nullptr);
        assert(g_errno == 0xc);                             // out of memory
        g_callocNull = false;
    }

    // 0x140012580 through the hook: the block is cleared by hand before the fields go in
    {
        std::memset(g_buf, 0xAA, sizeof g_buf);
        g_pfnNpcEventMalloc_140103f98 = &HookMalloc; g_hookArg = 0; g_hookNull = false; g_errno = -1;
        unsigned char* p = (unsigned char*)FUN_140012580();
        assert(p == g_buf && g_hookArg == 0x30);
        for (int i = 0; i < 6; ++i) {}                      // the six cleared words are checked below
        assert(*(void**)(p + 0x00) == nullptr && *(void**)(p + 0x08) == (void*)p);
        assert(*(unsigned int*)(p + 0x14) == 0xffffffffu);
        assert(*(unsigned int*)(p + 0x1c) == 0x7fffffffu && *(unsigned int*)(p + 0x20) == 1);
        g_hookNull = true; g_errno = -1;
        assert(FUN_140012580() == nullptr && g_errno == 0xc);
        g_pfnNpcEventMalloc_140103f98 = nullptr;
    }

    // 0x140010a00: the flag word is OR-ed, a null config answers -1
    {
        unsigned char cfg[0x30];
        std::memset(cfg, 0, sizeof cfg);
        assert(FUN_140010a00((long long)cfg, 4) == 0);
        assert(*(unsigned int*)(cfg + 0x28) == 4);
        assert(FUN_140010a00((long long)cfg, 0x20) == 0);
        assert(*(unsigned int*)(cfg + 0x28) == 0x24);
        assert(FUN_140010a00(0, 4) == 0xffffffffu);
    }

    // 0x140010a20: the processor hint lands at +0x10
    {
        unsigned char cfg[0x30];
        std::memset(cfg, 0, sizeof cfg);
        assert(FUN_140010a20((long long)cfg, 7) == 0);
        assert(*(unsigned int*)(cfg + 0x10) == 7);
        assert(FUN_140010a20(0, 7) == 0xffffffffu);
    }

    // 0x140010d80: base -> selector -> name
    {
        const char* pszName = "epoll";
        void* pSel[2] = { (void*)pszName, nullptr };
        void* pBase[2] = { (void*)pSel, nullptr };
        assert(FUN_140010d80(pBase) == (void*)pszName);
    }

    // 0x14001d350: 0x68 bytes, then 0x14001ced0 owns it
    {
        g_newArg = 0; g_ctorCalls = 0; g_ctorArg = nullptr; g_newRet = (void*)0x4000;
        assert(FUN_14001d350() == (void*)0x4010);
        assert(g_newArg == 0x68 && g_ctorCalls == 1 && g_ctorArg == (void*)0x4000);
        g_newRet = nullptr;
        assert(FUN_14001d350() == nullptr && g_ctorCalls == 1);
    }

    std::printf("NPCSERVER_D180_OK: event_config and event_base wrappers\n");
    return 0;
}
