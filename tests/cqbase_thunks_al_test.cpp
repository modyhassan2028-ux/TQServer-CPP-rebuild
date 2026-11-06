// Generated with family AL — the block is filled with 0xCC first so every zeroing store is provable.
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include "modules/syndicate/src/synthunks_al.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)
static uint32_t g_nSizeSeen = 0; static int g_nAlloc = 0;
static unsigned char aBlk[0x200];
static void* Hook(uint32_t uSize) { ++g_nAlloc; g_nSizeSeen = uSize; std::memset(aBlk, 0xCC, sizeof(aBlk)); return aBlk; }
static void* NullHook(uint32_t) { ++g_nAlloc; return nullptr; }

int main() {
    g_fnAL_1417f3166 = &Hook;

    {   // 0x141726c90
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_141726c90(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x30);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x28] == 0x1);                               // marker
        CHECK(aBlk[0x29] == 0x0);                               // marker
    }
    {   // 0x141726cf0
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_141726cf0(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x58);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x50] == 0x1);                               // marker
        CHECK(aBlk[0x51] == 0x0);                               // marker
    }
    {   // 0x141726d50
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_141726d50(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x50);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x48] == 0x1);                               // marker
        CHECK(aBlk[0x49] == 0x0);                               // marker
    }
    {   // 0x141726db0
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_141726db0(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x20);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x1c] == 0x1);                               // marker
        CHECK(aBlk[0x1d] == 0x0);                               // marker
    }
    {   // 0x141726ec0
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_141726ec0(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x20);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x1a] == 0x1);                               // marker
        CHECK(aBlk[0x1b] == 0x0);                               // marker
    }
    {   // 0x14173bc00
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_14173bc00(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x68);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x60] == 0x1);                               // marker
        CHECK(aBlk[0x61] == 0x0);                               // marker
    }
    {   // 0x14173bcb0
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_14173bcb0(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x28);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x20] == 0x1);                               // marker
        CHECK(aBlk[0x21] == 0x0);                               // marker
    }
    {   // 0x141746a00
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_141746a00(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x40);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x3c] == 0x1);                               // marker
        CHECK(aBlk[0x3d] == 0x0);                               // marker
    }
    {   // 0x141746a60
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_141746a60(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x30);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x28] == 0x1);                               // marker
        CHECK(aBlk[0x29] == 0x0);                               // marker
    }
    {   // 0x141755f90
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_141755f90(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x30);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x2c] == 0x1);                               // marker
        CHECK(aBlk[0x2d] == 0x0);                               // marker
    }
    {   // 0x141756200
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_141756200(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x30);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x28] == 0x1);                               // marker
        CHECK(aBlk[0x29] == 0x0);                               // marker
    }
    {   // 0x141756260
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_141756260(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x60);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x58] == 0x1);                               // marker
        CHECK(aBlk[0x59] == 0x0);                               // marker
    }
    {   // 0x1417562c0
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_1417562c0(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x30);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x28] == 0x1);                               // marker
        CHECK(aBlk[0x29] == 0x0);                               // marker
    }
    {   // 0x1417563b0
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_1417563b0(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x68);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x60] == 0x1);                               // marker
        CHECK(aBlk[0x61] == 0x0);                               // marker
    }
    {   // 0x141756410
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_141756410(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x30);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x28] == 0x1);                               // marker
        CHECK(aBlk[0x29] == 0x0);                               // marker
    }
    {   // 0x141756470
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_141756470(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x68);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x60] == 0x1);                               // marker
        CHECK(aBlk[0x61] == 0x0);                               // marker
    }
    {   // 0x1417564d0
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_1417564d0(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x30);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x28] == 0x1);                               // marker
        CHECK(aBlk[0x29] == 0x0);                               // marker
    }
    {   // 0x1417565b0
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_1417565b0(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x70);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x68] == 0x1);                               // marker
        CHECK(aBlk[0x69] == 0x0);                               // marker
    }
    {   // 0x141756610
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_141756610(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x30);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x28] == 0x1);                               // marker
        CHECK(aBlk[0x29] == 0x0);                               // marker
    }
    {   // 0x141776670
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_141776670(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x40);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x38] == 0x1);                               // marker
        CHECK(aBlk[0x39] == 0x0);                               // marker
    }
    {   // 0x14177ace0
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_14177ace0(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x30);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x28] == 0x1);                               // marker
        CHECK(aBlk[0x29] == 0x0);                               // marker
    }
    {   // 0x14178a6a0
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_14178a6a0(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x30);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x28] == 0x1);                               // marker
        CHECK(aBlk[0x29] == 0x0);                               // marker
    }
    {   // 0x14178a700
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_14178a700(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x50);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x48] == 0x1);                               // marker
        CHECK(aBlk[0x49] == 0x0);                               // marker
    }
    {   // 0x1417a76e0
        g_nAlloc = 0; g_nSizeSeen = 0;
        void* pR = SynAllocNode_1417a76e0(nullptr);
        CHECK(g_nAlloc == 1);
        CHECK(g_nSizeSeen == 0x30);                              // rcx at insn 2
        CHECK(pR == (void*)aBlk);                                // rax comes back untouched
        CHECK(*(void**)(aBlk + 0x0) == nullptr);                 // [rax] = 0
        CHECK(*(void**)(aBlk + 0x8) == nullptr);                // lea rax+0x8
        CHECK(*(void**)(aBlk + 0x10) == nullptr);                // lea rax+0x10
        CHECK(aBlk[0x28] == 0x1);                               // marker
        CHECK(aBlk[0x29] == 0x0);                               // marker
    }

    // the null path: the raw skips [rax] and then still stores through rax+off, so it faults.
    // it is not exercised here because doing so would be an invented guard, not the original.
    std::printf("SYNDICATE_THUNKS_AL_OK: 24 bodies, %d checks\n", g_nChecks);
    return 0;
}
