// D152 — the two node builders at their own starts: 0x1417c82e0 (0x48, sub-object through
//   0x141823288) and 0x1417c8370 (0x28, one qword from the argument).
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/syndicate/src/synacc.h"

using namespace tq;

static unsigned char* g_pBlock;
static uint64_t g_cbSeen;
static int g_subCalls;
static void* g_subDst;
static void* g_subSrc;

static void* NewHook(uint64_t cb) { g_cbSeen = cb; return g_pBlock; }
static void  SubHook(void* pDst, void* pSrc) { ++g_subCalls; g_subDst = pDst; g_subSrc = pSrc; }

int main() {
    alignas(16) unsigned char blk[0x60];
    uint64_t pair[2] = { 0xAA11, 0xBB22 };

    g_pfnSynNew_1417f3166 = &NewHook;
    g_pfnSyn_141823288 = &SubHook;

    // ---- 0x1417c82e0: 0x48 bytes, the sub-object at +0x18, flag at +0x40, +0x41 cleared
    {
        std::memset(blk, 0xCD, sizeof blk);
        g_pBlock = blk; g_cbSeen = 0; g_subCalls = 0;
        void* r = SynAccNew48Node_1417c82e0(nullptr, (void*)0x1001, (void*)0x1002, (void*)0x1003,
                                            (void*)0x2000, 0x7F);
        assert(g_cbSeen == 0x48);
        assert(r == (void*)blk);
        assert(*(void**)(blk) == (void*)0x1001);
        assert(*(void**)(blk + 8) == (void*)0x1002);
        assert(*(void**)(blk + 0x10) == (void*)0x1003);
        assert(g_subCalls == 1 && g_subDst == (void*)(blk + 0x18) && g_subSrc == (void*)0x2000);
        assert(blk[0x40] == 0x7F);
        assert(blk[0x41] == 0x00);
        // the allocator answering nothing means the body touches no byte at all
        std::memset(blk, 0xCD, sizeof blk);
        g_pBlock = nullptr;
        assert(SynAccNew48Node_1417c82e0(nullptr, nullptr, nullptr, nullptr, nullptr, 0) == nullptr);
        assert(blk[0x40] == 0xCD && blk[0x41] == 0xCD);
    }

    // ---- 0x1417c8370: 0x28 bytes, one qword from the argument, flag at +0x20, +0x21 cleared
    {
        std::memset(blk, 0xCD, sizeof blk);
        g_pBlock = blk; g_cbSeen = 0;
        void* r = SynAccNew28Node_1417c8370(nullptr, (void*)0x3001, (void*)0x3002, (void*)0x3003,
                                            (const void*)pair, 0x01);
        assert(g_cbSeen == 0x28);
        assert(r == (void*)blk);
        assert(*(void**)(blk) == (void*)0x3001);
        assert(*(void**)(blk + 8) == (void*)0x3002);
        assert(*(void**)(blk + 0x10) == (void*)0x3003);
        assert(*(void**)(blk + 0x18) == (void*)0xAA11);   // the argument's first qword only
        assert(blk[0x20] == 0x01);
        assert(blk[0x21] == 0x00);
        assert(blk[0x22] == 0xCD);                        // nothing past the two bytes is touched
    }

    std::printf("SYNDICATE_D152_OK: two node builders, 2 units, 19 checks\n");
    return 0;
}
