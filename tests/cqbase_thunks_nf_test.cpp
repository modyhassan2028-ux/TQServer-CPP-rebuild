// Generated with family NF — every field of the node, plus the null path.
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include "modules/syndicate/src/synthunks_nf.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static uint32_t g_nSize = 0; static int g_nAlloc = 0; static bool g_bNull = false;
static unsigned char aNode[0x40];
static void* Hook(uint32_t uSize) { ++g_nAlloc; g_nSize = uSize;
    if (g_bNull) return nullptr;
    std::memset(aNode, 0xCC, sizeof(aNode)); return aNode; }

int main() {
    g_fnNF_1417f3166 = &Hook;

    {   // 0x1417264d0
        static unsigned char key[4]; unsigned char a2 = 0, a3 = 0, a4 = 0;
        const uint32_t uKey = 0xA1B2C3D4u; std::memcpy(key, &uKey, 4);
        g_nAlloc = 0; g_nSize = 0; g_bNull = false;
        void* pR = SynMakeNode_1417264d0(nullptr, &a2, &a3, &a4, (const uint32_t*)key, 0x77);
        CHECK(g_nAlloc == 1); CHECK(g_nSize == 0x20);
        CHECK(pR == (void*)aNode);
        CHECK(*(void**)(aNode + 0x0) == (void*)&a2);
        CHECK(*(void**)(aNode + 0x8) == (void*)&a3);
        CHECK(*(void**)(aNode + 0x10) == (void*)&a4);
        CHECK(*(uint32_t*)(aNode + 0x18) == 0xA1B2C3D4u);
        CHECK(*(unsigned char*)(aNode + 0x1c) == 0x77);
        CHECK(*(unsigned char*)(aNode + 0x1d) == 0x00);
        g_bNull = true; g_nAlloc = 0;
        pR = SynMakeNode_1417264d0(nullptr, &a2, &a3, &a4, (const uint32_t*)key, 0x77);
        CHECK(pR == nullptr); CHECK(g_nAlloc == 1);   // no store ran: the block is untouched
    }
    {   // 0x141726e10
        static unsigned char key[4]; unsigned char a2 = 0, a3 = 0, a4 = 0;
        const uint32_t uKey = 0xA1B2C3D4u; std::memcpy(key, &uKey, 4);
        g_nAlloc = 0; g_nSize = 0; g_bNull = false;
        void* pR = SynMakeNode_141726e10(nullptr, &a2, &a3, &a4, (const uint32_t*)key, 0x77);
        CHECK(g_nAlloc == 1); CHECK(g_nSize == 0x20);
        CHECK(pR == (void*)aNode);
        CHECK(*(void**)(aNode + 0x0) == (void*)&a2);
        CHECK(*(void**)(aNode + 0x8) == (void*)&a3);
        CHECK(*(void**)(aNode + 0x10) == (void*)&a4);
        CHECK(*(uint32_t*)(aNode + 0x18) == 0xA1B2C3D4u);
        CHECK(*(unsigned char*)(aNode + 0x1c) == 0x77);
        CHECK(*(unsigned char*)(aNode + 0x1d) == 0x00);
        g_bNull = true; g_nAlloc = 0;
        pR = SynMakeNode_141726e10(nullptr, &a2, &a3, &a4, (const uint32_t*)key, 0x77);
        CHECK(pR == nullptr); CHECK(g_nAlloc == 1);   // no store ran: the block is untouched
    }

    std::printf("SYNDICATE_THUNKS_NF_OK: 2 bodies, %d checks\n", g_nChecks);
    return 0;
}
