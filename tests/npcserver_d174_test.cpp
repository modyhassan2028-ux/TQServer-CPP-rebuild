// D174 — NpcServer.exe 0x140002d70: CLogThread's constructor.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static int g_ctorCalls = 0;
static bool g_tableStoredBeforeCtor = false;
static void CtorHook(void* p) {
    ++g_ctorCalls;
    g_tableStoredBeforeCtor = (*(void**)p == (void*)&g_symNpcVftbl_1400bed00);
}
static int g_copyCalls = 0;
static void* g_copyDst = nullptr;
static const char* g_copySrc = nullptr;
static unsigned long long g_copyCap = 0;
static void SafeCopyHook(char* pDst, const char* pSrc, unsigned long long uCapacity) {
    ++g_copyCalls; g_copyDst = pDst; g_copySrc = pSrc; g_copyCap = uCapacity;
    std::snprintf(pDst, (size_t)uCapacity, "%s", pSrc);
}

int main() {
    g_pfnNpcThreadBaseCtor = &CtorHook;
    g_pfnNpcSafeCopy = &SafeCopyHook;

    // with a name: base, table, cleared +0x40, handle at +0x48, the name copied into +0x50
    {
        unsigned char obj[0x100];
        std::memset(obj, 0xEF, sizeof obj);
        g_ctorCalls = 0; g_tableStoredBeforeCtor = true; g_copyCalls = 0;
        assert(FUN_140002d70(obj, 0x1234, "net-log") == (void*)obj);
        assert(g_ctorCalls == 1);
        assert(g_tableStoredBeforeCtor == false);                  // the base ran before the store
        assert(*(void**)(obj + 0x00) == (void*)&g_symNpcVftbl_1400bed00);
        assert(*(void**)(obj + 0x40) == nullptr);                  // cleared
        assert(*(void**)(obj + 0x48) == (void*)0x1234);
        assert(g_copyCalls == 1);
        assert(g_copyDst == (void*)(obj + 0x50));
        assert(g_copySrc != nullptr && std::strcmp(g_copySrc, "net-log") == 0);
        assert(g_copyCap == 0x80);                                 // the body's r8d
        assert(std::strcmp((const char*)(obj + 0x50), "net-log") == 0);
    }

    // without a name: the copy is skipped and the buffer keeps what it had
    {
        unsigned char obj[0x100];
        std::memset(obj, 0xEF, sizeof obj);
        g_ctorCalls = 0; g_copyCalls = 0;
        assert(FUN_140002d70(obj, 0x77, nullptr) == (void*)obj);
        assert(g_ctorCalls == 1 && g_copyCalls == 0);
        assert(*(void**)(obj + 0x48) == (void*)0x77);
        assert(*(unsigned char*)(obj + 0x50) == 0xEF);             // untouched
    }

    std::printf("NPCSERVER_D174_OK: 0x140002d70 CLogThread ctor\n");
    return 0;
}
