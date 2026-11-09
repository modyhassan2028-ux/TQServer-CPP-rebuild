// D171 — NpcServer.exe 0x140001cb0 .. 0x140001fd0: ProcessAllIncoming, the shared_ptr helpers,
// and the buffer owner.
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"
#include "version/cqserver-78.0.11-1204/npcserver/clientsocket.h"

using namespace tq;

static int g_slot0 = 0, g_slot1 = 0, g_deletes = 0, g_logs = 0, g_errnoCalls = 0;
static const void* g_lastLog = nullptr;
static long long g_errnoArg = 0;
static void Slot0(void* p) { (void)p; ++g_slot0; }
static void Slot1(void* p) { (void)p; ++g_slot1; }
static void* DelHook(void* p) { ++g_deletes; return p; }
static void LogHook(const void* m, ...) { ++g_logs; g_lastLog = m; }
static int ErrnoHook(long long h) { ++g_errnoCalls; g_errnoArg = h; return 9; }

static unsigned char* MakeCounted(int nFirst, int nSecond) {
    unsigned char* p = (unsigned char*)std::calloc(1, 0x20);
    *(void**)(p + 0x00) = (void*)&Slot0;
    *(void**)(p + 0x08) = (void*)&Slot1;
    *(int*)(p + 0x10) = nFirst;
    *(int*)(p + 0x14) = nSecond;
    return p;
}

static int g_newCalls = 0, g_newSize = 0; static void* g_newRet = nullptr;
static void* NewHook(long long n) { ++g_newCalls; g_newSize = (int)n; return g_newRet; }
static int g_newCalls2 = 0, g_newSize2 = 0;
static void* g_newRet2 = nullptr;
static void* NewUnderscoreHook(long long n) { ++g_newCalls2; g_newSize2 = (int)n; return g_newRet2; }

static int g_bevInput = 0; static unsigned long long g_avail = 0;
static long long g_readRet = 0; static int g_readLen = 0; static void* g_readDst = nullptr;
static void* BevInputHook(void* p) { (void)p; ++g_bevInput; return (void*)0x5000; }
static unsigned long long EvbufLenHook(void* p) { (void)p; return g_avail; }
static long long EvbufRemoveHook(void* pBev, void* pDst, long long n) {
    (void)pBev; g_readLen = (int)n; g_readDst = pDst; return g_readRet;
}

static int g_slot4Called = 0; static long long* g_slot4Self = nullptr; static long long g_slot4Arg = -1;
static void Slot4(void* self, long long arg) { ++g_slot4Called; g_slot4Self = (long long*)self; g_slot4Arg = arg; }

int main() {
    g_pfnNpcInlineLogError = &LogHook;
    g_pfnNpcOperatorDelete = &DelHook;
    g_pfnNpcSocketErrno = &ErrnoHook;
    g_pfnNpcOperatorNew = &NewHook;
    g_pfnNpcOperatorNewUnderscore = &NewUnderscoreHook;
    g_pfnNpcBevInput_140005b70 = &BevInputHook;
    g_pfnNpcEvbufLen_14000c370 = &EvbufLenHook;
    g_pfnNpcEvbufRemove_140005c30 = &EvbufRemoveHook;

    // 0x140001cb0 — no bufferevent: the plain message, then out
    {
        unsigned char* p = (unsigned char*)std::calloc(1, 0x840);
        g_logs = 0;
        FUN_140001cb0((long long)p);
        assert(g_logs == 1 && g_lastLog == (const void*)&g_symNpcStr_1400be0b0);
        assert(g_bevInput == 0);
        std::free(p);
    }

    // 0x140001cb0 — not connected: nothing happens even with a bufferevent
    {
        unsigned char* p = (unsigned char*)std::calloc(1, 0x840);
        *(long long*)(p + 0x820) = 0x7000;
        *(int*)(p + 0x830) = 1;
        g_logs = 0; g_bevInput = 0;
        FUN_140001cb0((long long)p);
        assert(g_logs == 0 && g_bevInput == 0);
        std::free(p);
    }

    // 0x140001cb0 — 0x800 already buffered forces the parse call before any read
    {
        unsigned char* p = (unsigned char*)std::calloc(1, 0x840);
        *(long long*)(p + 0x820) = 0x7000;
        *(int*)(p + 0x830) = 2;
        *(int*)(p + 0x814) = 0x800;
        g_logs = 0; g_avail = 0; g_bevInput = 0;
        FUN_140001cb0((long long)p);
        // 0x1400017b0 runs with no kernel thread, so it logs its CHECK message first
        assert(g_logs == 1);
        assert(g_bevInput == 1);
        std::free(p);
    }

    // 0x140001cb0 — a read of 20 bytes lands at this+0x14 and the count follows
    {
        unsigned char* p = (unsigned char*)std::calloc(1, 0x840);
        *(long long*)(p + 0x820) = 0x7000;
        *(int*)(p + 0x830) = 2;
        *(int*)(p + 0x814) = 0;
        g_avail = 20; g_readRet = 20; g_readLen = 0; g_readDst = nullptr; g_logs = 0;
        FUN_140001cb0((long long)p);
        assert(g_readLen == 20 && g_readDst == (void*)(p + 0x14));
        assert(*(int*)(p + 0x814) == 20);
        std::free(p);
    }

    // 0x140001cb0 — a failed read reports the socket errno and clears the buffer
    {
        unsigned char* p = (unsigned char*)std::calloc(1, 0x840);
        *(long long*)(p + 0x820) = 0x7000;
        *(int*)(p + 0x830) = 2;
        *(int*)(p + 0x814) = 0;
        *(long long*)(p + 0x818) = 0x99;
        g_avail = 64; g_readRet = 0; g_errnoCalls = 0; g_logs = 0;
        FUN_140001cb0((long long)p);
        assert(g_errnoCalls == 1 && g_errnoArg == 0x99);
        assert(g_logs == 1 && std::strcmp((const char*)g_lastLog,
               "CClientSocket::ProcessAllIncoming, bufferevent_read err[%d].") == 0);
        assert(*(int*)(p + 0x830) == 0);            // 0x140001340 ran
        std::free(p);
    }

    // 0x140001db0 — the same release as 0x140001970
    {
        unsigned char owner[16] = {0};
        unsigned char* c = MakeCounted(1, 1);
        *(void**)(owner + 8) = c;
        g_slot0 = g_slot1 = 0;
        FUN_140001db0(owner);
        assert(g_slot0 == 1 && g_slot1 == 1);
        std::free(c);
    }

    // 0x140001df0 — copy-assign copies both words and bumps the new counter
    {
        unsigned char dst[16] = {0};
        unsigned char* c = MakeCounted(1, 1);
        void* src[2] = { (void*)0xC1, (void*)c };
        assert(FUN_140001df0((void**)dst, src) == (void*)dst);
        assert(*(void**)(dst + 0) == (void*)0xC1 && *(void**)(dst + 8) == c);
        assert(*(int*)(c + 0x10) == 2);
        std::free(c);
    }

    // 0x140001e10 — empty clears both words; a live reference is released first
    {
        unsigned char owner[16] = {0};
        *(void**)(owner + 0) = (void*)0xC3;   // a live first word with no counted object behind it
        FUN_140001e10((void**)owner);
        assert(*(void**)(owner + 0) == nullptr && *(void**)(owner + 8) == nullptr);
        unsigned char* c = MakeCounted(1, 1);
        *(void**)(owner + 8) = c;
        *(void**)(owner + 0) = (void*)0xC2;
        g_slot0 = g_slot1 = 0;
        FUN_140001e10((void**)owner);
        assert(g_slot0 == 1 && g_slot1 == 1);
        assert(*(void**)(owner + 0) == nullptr && *(void**)(owner + 8) == nullptr);
        std::free(c);
    }

    // 0x140001ea0 — the 0x28 block is filled and handed to 0x1400019b0
    {
        unsigned char owner[16] = {0};
        unsigned char block[0x28];
        std::memset(block, 0, sizeof block);
        g_newRet = block; g_newCalls = 0; g_newSize = 0;
        FUN_140001ea0((void**)owner, (void*)0xD1, (void*)0xD2);
        assert(g_newCalls == 1 && g_newSize == 0x28);
        assert(*(void**)(block + 0x00) == (void*)&g_symNpcVftbl_1400be3f0);
        assert(*(void**)(block + 0x08) == (void*)0xD1);
        // the block starts at 0/1 and 0x1400019b0 then bumps the first counter, so it reads 1 here
        assert(*(uint32_t*)(block + 0x10) == 1 && *(uint32_t*)(block + 0x14) == 1);
        assert(*(void**)(block + 0x20) == (void*)0xD2);
        assert(*(void**)(owner + 8) == block && *(void**)(owner + 0) == (void*)0xD1);
    }

    // 0x140001ea0 — allocation failure stores a null block
    {
        unsigned char owner[16] = {0};
        g_newRet = nullptr;
        FUN_140001ea0((void**)owner, (void*)0xD3, (void*)0xD4);
        assert(*(void**)(owner + 8) == nullptr && *(void**)(owner + 0) == (void*)0xD3);
    }

    // 0x140001f20 — slot 4 gets a zero argument, then the object is deleted
    {
        long long vtbl[4] = { 0, 0, (long long)&Slot4, 0 };
        long long obj[1] = { (long long)vtbl };
        g_slot4Called = 0; g_deletes = 0;
        FUN_140001f20(obj);
        assert(g_slot4Called == 1 && g_slot4Self == obj && g_slot4Arg == 0);
        assert(g_deletes == 1);
    }

    // 0x140001f40 — releases the counted object at +0x10
    {
        unsigned char holder[0x18] = {0};
        unsigned char* c = MakeCounted(1, 1);
        *(void**)(holder + 0x10) = c;
        g_slot0 = g_slot1 = 0;
        FUN_140001f40((long long)holder);
        assert(g_slot0 == 1 && g_slot1 == 1);
        std::free(c);
    }

    // 0x140001f90 — clears then releases
    {
        unsigned char owner[16];
        std::memset(owner, 0xAB, sizeof owner);
        unsigned char* c = MakeCounted(2, 1);
        *(void**)(owner + 8) = c;
        g_slot0 = g_slot1 = 0;
        assert(FUN_140001f90((void**)owner) == (void*)owner);
        // the body clears both words first, so the release it then calls finds nothing to release
        assert(*(int*)(c + 0x10) == 2 && g_slot0 == 0 && g_slot1 == 0);
        assert(*(void**)(owner + 0) == nullptr && *(void**)(owner + 8) == nullptr);
        std::free(c);
    }

    // 0x140001fb0 — clears then allocates and assigns
    {
        unsigned char owner[16];
        std::memset(owner, 0xCD, sizeof owner);
        unsigned char block[0x28];
        std::memset(block, 0, sizeof block);
        g_newRet = block;
        assert(FUN_140001fb0((void**)owner, (void*)0xE1, (void*)0xE2) == (void*)owner);
        assert(*(void**)(owner + 8) == block && *(void**)(owner + 0) == (void*)0xE1);
        assert(*(void**)(block + 0x20) == (void*)0xE2);
    }

    // 0x140001fd0 — the buffer owner copies the caller's bytes and records the size
    {
        unsigned char* counted = (unsigned char*)std::calloc(1, 0x28);   // the 0x28 counted block
        unsigned char* buffer = (unsigned char*)std::calloc(1, 16);      // operator_new__ result
        g_newRet = counted; g_newRet2 = buffer;
        int owner[6] = {0};
        const char src[] = "hello-buffer";
        int* r = FUN_140001fd0(owner, src, (int)sizeof src);
        assert(r == owner);
        assert(g_newCalls2 == 1 && g_newSize2 == (int)sizeof src);
        assert(*owner == (int)sizeof src);
        assert(*(void**)(owner + 2) == (void*)buffer);         // this+8 holds the buffer pointer
        assert(*(void**)(owner + 4) == (void*)counted);        // this+16 holds the counted block
        assert(std::memcmp(buffer, src, sizeof src) == 0);     // the bytes were copied in
        std::free(buffer);
        std::free(counted);
    }

    // 0x140001cb0 keeps its two CHECK paths reachable through 0x1400017b0
    {
        unsigned char* p = (unsigned char*)std::calloc(1, 0x840);
        g_logs = 0;
        FUN_1400017b0((long long)p);
        assert(g_logs == 1);
        std::free(p);
    }

    std::printf("NPCSERVER_D171_OK: 0x140001cb0..0x140001fd0, 10 bodies\n");
    return 0;
}
