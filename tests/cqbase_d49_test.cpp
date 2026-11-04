// ============================================================================
// cqbase_d49 — the 46 leaf getters of the 0x1417c5900 range (15 distinct bodies).
//   Every expectation below was generated from the verified objdump classification of the
//   original body, so a mismatch means the port drifted from the binary.
// ============================================================================
#include "modules/syndicate/src/synleaves.h"

#include <cassert>
#include <cstdio>
#include <cstring>

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; assert(x); } while (0)

int main() {
    static uint8_t aBuf[0x200];
    std::memset(aBuf, 0, sizeof(aBuf));

        CHECK(SynLeaf_1417c59b0(aBuf + 0x100) == (void*)(aBuf + 0x100));         // 0x1417c59b0
        CHECK(SynLeaf_1417c59c0(aBuf + 0x100) == (void*)(aBuf + 0x100 + 0x29));   // 0x1417c59c0
        CHECK(SynLeaf_1417c59b0(aBuf + 0x100) == (void*)(aBuf + 0x100));         // 0x1417c59d0
        CHECK(SynLeaf_1417c59e0(aBuf + 0x100) == (void*)(aBuf + 0x100 + 0x10));   // 0x1417c59e0
        *(void**)(aBuf + 0x100 + 0x30) = (void*)0x1122; CHECK(SynLeaf_1417c59f0(aBuf + 0x100) == (void*)0x1122);   // 0x1417c59f0
        *(void**)(aBuf + 0x100 + 0x30) = (void*)0x1122; CHECK(SynLeaf_1417c5a00(aBuf + 0x100) == (void*)(0x1122 + 0x10));   // 0x1417c5a00
        CHECK(SynLeaf_1417c59b0(aBuf + 0x100) == (void*)(aBuf + 0x100));         // 0x1417c5a10
        CHECK(SynLeaf_1417c59b0(aBuf + 0x100) == (void*)(aBuf + 0x100));         // 0x1417c5a20
        CHECK(SynLeaf_1417c5a30(aBuf + 0x100) == (void*)(aBuf + 0x100 + 0x41));   // 0x1417c5a30
        CHECK(SynLeaf_1417c59b0(aBuf + 0x100) == (void*)(aBuf + 0x100));         // 0x1417c5a40
        CHECK(SynLeaf_1417c59e0(aBuf + 0x100) == (void*)(aBuf + 0x100 + 0x10));   // 0x1417c5a50
        *(void**)(aBuf + 0x100 + 0x30) = (void*)0x1122; CHECK(SynLeaf_1417c59f0(aBuf + 0x100) == (void*)0x1122);   // 0x1417c5a60
        *(void**)(aBuf + 0x100 + 0x30) = (void*)0x1122; CHECK(SynLeaf_1417c5a00(aBuf + 0x100) == (void*)(0x1122 + 0x10));   // 0x1417c5a70
        CHECK(SynLeaf_1417c59b0(aBuf + 0x100) == (void*)(aBuf + 0x100));         // 0x1417c5a80
        CHECK(SynLeaf_1417c5a90(aBuf + 0x100) == (void*)(aBuf + 0x100 + 0x21));   // 0x1417c5a90
        CHECK(SynLeaf_1417c59b0(aBuf + 0x100) == (void*)(aBuf + 0x100));         // 0x1417c5aa0
        CHECK(SynLeaf_1417c59e0(aBuf + 0x100) == (void*)(aBuf + 0x100 + 0x10));   // 0x1417c5ab0
        CHECK(SynLeaf_1417c59b0(aBuf + 0x100) == (void*)(aBuf + 0x100));         // 0x1417c5ac0
        CHECK(SynLeaf_1417c59b0(aBuf + 0x100) == (void*)(aBuf + 0x100));         // 0x1417c5ad0
        *(void**)(aBuf + 0x100 + 0x8) = (void*)0x1122; CHECK(SynLeaf_1417c5b00(aBuf + 0x100) == (void*)0x1122);   // 0x1417c5b00
        *(void**)(aBuf + 0x100 + 0x8) = (void*)0x1122; CHECK(SynLeaf_1417c5b00(aBuf + 0x100) == (void*)0x1122);   // 0x1417c5b70
        *(void**)(aBuf + 0x100 + 0x8) = (void*)0x1122; CHECK(SynLeaf_1417c5b00(aBuf + 0x100) == (void*)0x1122);   // 0x1417c5bc0
        CHECK(SynLeaf_1417c59b0(aBuf + 0x100) == (void*)(aBuf + 0x100));         // 0x1417c5bd0
        CHECK(SynLeaf_1417c59b0(aBuf + 0x100) == (void*)(aBuf + 0x100));         // 0x1417c5c10
        CHECK(SynLeaf_1417c5c20(aBuf + 0x100) == (void*)(aBuf + 0x100 + 0x28));   // 0x1417c5c20
        CHECK(SynLeaf_1417c5c30(aBuf + 0x100) == (void*)(aBuf + 0x100 + 0x8));   // 0x1417c5c30
        CHECK(SynLeaf_1417c5c40(aBuf + 0x100) == (void*)(aBuf + 0x100 + 0x18));   // 0x1417c5c40
        CHECK(SynLeaf_1417c5c30(aBuf + 0x100) == (void*)(aBuf + 0x100 + 0x8));   // 0x1417c5ca0
        CHECK(SynLeaf_1417c5c40(aBuf + 0x100) == (void*)(aBuf + 0x100 + 0x18));   // 0x1417c5cb0
        CHECK(SynLeaf_1417c5cd0(aBuf + 0x100) == (void*)(aBuf + 0x100 + 0x20));   // 0x1417c5cd0
        CHECK(SynLeaf_1417c5c30(aBuf + 0x100) == (void*)(aBuf + 0x100 + 0x8));   // 0x1417c5ce0
        CHECK(SynLeaf_1417c5c40(aBuf + 0x100) == (void*)(aBuf + 0x100 + 0x18));   // 0x1417c5cf0
        *(void**)(aBuf + 0x100 + 0x30) = (void*)0x1122; CHECK(SynLeaf_1417c59f0(aBuf + 0x100) == (void*)0x1122);   // 0x1417c5d00
        *(void**)(aBuf + 0x100 + 0x30) = (void*)0x1122; CHECK(SynLeaf_1417c5a00(aBuf + 0x100) == (void*)(0x1122 + 0x10));   // 0x1417c5d10
        CHECK(SynLeaf_1417c59b0(aBuf + 0x100) == (void*)(aBuf + 0x100));         // 0x1417c5d20
        CHECK(SynLeaf_1417c59c0(aBuf + 0x100) == (void*)(aBuf + 0x100 + 0x29));   // 0x1417c5d80
        CHECK(SynLeaf_1417c59b0(aBuf + 0x100) == (void*)(aBuf + 0x100));         // 0x1417c5d90
        CHECK(SynLeaf_1417c5c30(aBuf + 0x100) == (void*)(aBuf + 0x100 + 0x8));   // 0x1417c5da0
        CHECK(SynLeaf_1417c59e0(aBuf + 0x100) == (void*)(aBuf + 0x100 + 0x10));   // 0x1417c5db0
        *(void**)(aBuf + 0x100 + 0x30) = (void*)0x1122; CHECK(SynLeaf_1417c59f0(aBuf + 0x100) == (void*)0x1122);   // 0x1417c5dc0
        *(void**)(aBuf + 0x100 + 0x30) = (void*)0x1122; CHECK(SynLeaf_1417c5dd0(aBuf + 0x100) == (void*)(0x1122 + 0x8));   // 0x1417c5dd0
        CHECK(SynLeaf_1417c59b0(aBuf + 0x100) == (void*)(aBuf + 0x100));         // 0x1417c5de0
        CHECK(SynLeaf_1417c59b0(aBuf + 0x100) == (void*)(aBuf + 0x100));         // 0x1417c5df0
        *(void**)(aBuf + 0x100 + 0x8) = (void*)0x1122; CHECK(SynLeaf_1417c5b00(aBuf + 0x100) == (void*)0x1122);   // 0x1417c5e50
        CHECK(SynLeaf_1417c5eb0() == 0x666666666666666ULL);   // 0x1417c5eb0
        CHECK(SynLeaf_1417c5ef0() == 0xfffffffffffffffULL);   // 0x1417c5ef0

    std::printf("SYNDICATE_D49_OK: the leaf getters, 46 addresses / 15 bodies, %d checks\n",
                g_nChecks);
    return 0;
}
