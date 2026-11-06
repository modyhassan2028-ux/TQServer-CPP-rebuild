// ============================================================================
// cqbase_d72 — four writer primitives. The little-endian helpers are checked byte by byte
//   through their return pointers, and the buffer writer is checked across the flush boundary
//   where the original restarts from the next block.
// ============================================================================
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "modules/syndicate/src/synpbwrite.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { \
    std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)

// ---- the buffer the writer flushes through
static std::vector<uint8_t> g_aBuffer(8, 0);
static std::vector<uint8_t> g_aSink;          // everything the copies produced, in order
static const uint8_t* g_pSrcBase = nullptr;
static int32_t g_nConsumed = 0;
static int g_nGetBuffer = 0;
static std::vector<int32_t> g_aCopyLens;

static void CopyHook(void* pDst, const void* pSrc, int64_t nLen) {
    g_aCopyLens.push_back((int32_t)nLen);
    if (nLen > 0) std::memcpy(pDst, pSrc, (size_t)nLen);
    // record what landed in the buffer so the order can be checked
    g_aSink.assign((uint8_t*)pDst, (uint8_t*)pDst + nLen);
}
static void ConsumeHook(void*, int32_t n) { g_nConsumed = n; }
static void GetBufferHook(void* p) { ++g_nGetBuffer; *(int32_t*)((uint8_t*)p + 0x18) = 0; }

int main() {
    g_fnWrCopy = &CopyHook;
    g_fnWrConsume = &ConsumeHook;
    g_fnWrGetBuffer = &GetBufferHook;

    // ---- WriteLe32 puts the low byte first and answers dst + 4
    {
        uint8_t a[8] = {0};
        void* pEnd = SynWriteLe32(0x04030201u, a);
        CHECK(pEnd == a + 4);
        CHECK(a[0] == 0x01 && a[1] == 0x02 && a[2] == 0x03 && a[3] == 0x04);
        CHECK(a[4] == 0);                      // nothing past the four bytes
    }

    // ---- WriteLe64 writes eight bytes, high half last
    {
        uint8_t a[12] = {0};
        void* pEnd = SynWriteLe64(0x0807060504030201ULL, a);
        CHECK(pEnd == a + 8);
        for (int i = 0; i < 8; ++i) CHECK(a[i] == (uint8_t)(i + 1));
        CHECK(a[8] == 0);
    }

    // ---- WriteToBuffer when everything fits: one copy, the count consumed, no flush
    {
        struct Obj { uint8_t a[0x40]; };
        Obj o;
        std::memset(&o, 0, sizeof(o));
        std::vector<uint8_t> aBuf(16, 0);
        *(void**)(o.a + 0x08) = aBuf.data();
        *(int32_t*)(o.a + 0x10) = 16;
        std::vector<uint8_t> aData = {1, 2, 3, 4};
        g_nGetBuffer = 0; g_nConsumed = -1; g_aCopyLens.clear();
        SynWriteToBuffer(&o, aData.data(), 4);
        CHECK(g_nGetBuffer == 0);
        CHECK(g_nConsumed == 4);
        CHECK(g_aCopyLens.size() == 1 && g_aCopyLens[0] == 4);
        CHECK(aBuf[0] == 1 && aBuf[3] == 4);
    }

    // ---- more than the block: the block's worth goes first, then a new block is asked for
    {
        struct Obj { uint8_t a[0x40]; };
        Obj o;
        std::memset(&o, 0, sizeof(o));
        std::vector<uint8_t> aBuf(8, 0);
        *(void**)(o.a + 0x08) = aBuf.data();
        *(int32_t*)(o.a + 0x10) = 8;
        std::vector<uint8_t> aData = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        g_nGetBuffer = 0; g_nConsumed = -1; g_aCopyLens.clear();
        SynWriteToBuffer(&o, aData.data(), 10);
        CHECK(g_nGetBuffer == 1);
        CHECK(g_aCopyLens.size() == 2);
        CHECK(g_aCopyLens[0] == 8);            // the whole block
        CHECK(g_aCopyLens[1] == 2);            // the remainder
        CHECK(g_nConsumed == 2);
        // the fake getter hands back the same block, so the remainder lands over its start;
        // what proves the order is the copy lengths above, not the final bytes
        CHECK(aBuf[7] == 8);                   // the last byte of the first block is untouched
        CHECK(aBuf[0] == 9 && aBuf[1] == 10);  // the remainder was written second
    }

    // ---- a failed block fetch ends the loop and leaves the count untouched
    {
        struct Obj { uint8_t a[0x40]; };
        Obj o;
        std::memset(&o, 0, sizeof(o));
        std::vector<uint8_t> aBuf(4, 0);
        *(void**)(o.a + 0x08) = aBuf.data();
        *(int32_t*)(o.a + 0x10) = 4;
        std::vector<uint8_t> aData = {1, 2, 3, 4, 5, 6};
        g_nConsumed = -1; g_aCopyLens.clear();
        // a getter that fails: it raises the flag instead of producing a block
        g_fnWrGetBuffer = [](void* p) { ++g_nGetBuffer; *(int32_t*)((uint8_t*)p + 0x18) = 1; };
        g_nGetBuffer = 0;
        SynWriteToBuffer(&o, aData.data(), 6);
        CHECK(g_nGetBuffer == 1);
        CHECK(g_nConsumed == -1);              // nothing consumed after the failure
        CHECK(g_aCopyLens.size() == 1 && g_aCopyLens[0] == 4);
        g_fnWrGetBuffer = &GetBufferHook;
    }

    // ---- WriteUntilDone repeats while the call succeeds and the remainder is not zero
    {
        struct Obj { void** ppVt; };
        static int s_nCalls = 0;
        static int32_t s_aSeq[4] = {3, 2, 0, 0};
        static bool s_bOk = true;
        struct Fn {
            static bool Write(void*, void*, int32_t* pRem) { *pRem = s_aSeq[s_nCalls++]; return s_bOk; }
        };
        static void* apVt[2] = {nullptr, (void*)&Fn::Write};
        Obj o;
        o.ppVt = apVt;
        int32_t nRem = 9;
        s_nCalls = 0; s_bOk = true;
        CHECK(SynWriteUntilDone(&o, nullptr, &nRem) == true);
        CHECK(s_nCalls == 3);                  // 3, 2, then 0 ends it

        // a failure stops immediately and is what the call answers
        s_nCalls = 0; s_bOk = false;
        CHECK(SynWriteUntilDone(&o, nullptr, &nRem) == false);
        CHECK(s_nCalls == 1);
    }

    std::printf("SYNDICATE_D72_OK: four writer primitives, %d checks\n", g_nChecks);
    return 0;
}
