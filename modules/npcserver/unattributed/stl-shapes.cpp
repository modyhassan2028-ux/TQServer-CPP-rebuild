// Generated from NpcServer.exe 0x140080000..0x140090000 by tools/gen_stl_shapes.py.
#include "modules/npcserver/unattributed/stl-shapes.h"

#include <cstring>
#include <new>

namespace tq {


static void NpcMemmoveForward(void* pDst, size_t cbDst, const void* pSrc, size_t cbSrc) {
    (void)cbDst;
    (void)cbSrc;
    std::memmove(pDst, pSrc, cbSrc);
}

void (*g_pfnNpcMemmoveS)(void*, size_t, const void*, size_t) = &NpcMemmoveForward;

// 0x1400806e0 - alloc-raw
void FUN_1400806e0(unsigned long long nCount) {
    if (nCount != 0 && 0xFFFFFFFFFFFFFFFFull / nCount < 0x30ull) {
        throw std::bad_alloc();
    }
    g_pfnNpcOperatorNew((long long)(nCount * 48));
}

// 0x140080760 - alloc-raw
void FUN_140080760(unsigned long long nCount) {
    if (nCount != 0 && 0xFFFFFFFFFFFFFFFFull / nCount < 0x20ull) {
        throw std::bad_alloc();
    }
    g_pfnNpcOperatorNew((long long)(nCount << 5));
}

// 0x140080800 - alloc-raw
void FUN_140080800(unsigned long long nCount) {
    if (nCount != 0 && 0xFFFFFFFFFFFFFFFFull / nCount < 0x20ull) {
        throw std::bad_alloc();
    }
    g_pfnNpcOperatorNew((long long)(nCount << 5));
}

// 0x1400808a0 - alloc-raw
void FUN_1400808a0(unsigned long long nCount) {
    if (nCount != 0 && 0xFFFFFFFFFFFFFFFFull / nCount < 0x10ull) {
        throw std::bad_alloc();
    }
    g_pfnNpcOperatorNew((long long)(nCount << 4));
}

// 0x140080ca0 - memmove-forward
void* FUN_140080ca0(void* pFirst, long long nLast, void* pDest) {
    long long nCount = nLast - (long long)pFirst >> 2;
    size_t cbBytes = (size_t)nCount * 4;
    if (nCount != 0) {
        g_pfnNpcMemmoveS(pDest, cbBytes, pFirst, cbBytes);
    }
    return (void*)((long long)cbBytes + (long long)pDest);
}

// 0x140081310 - alloc-raw
void FUN_140081310(void* pAllocator, unsigned long long nCount) {
    (void)pAllocator;
    if (nCount != 0 && 0xFFFFFFFFFFFFFFFFull / nCount < 0x30ull) {
        throw std::bad_alloc();
    }
    g_pfnNpcOperatorNew((long long)(nCount * 48));
}

// 0x140081380 - alloc-raw
void FUN_140081380(void* pAllocator, unsigned long long nCount) {
    (void)pAllocator;
    if (nCount != 0 && 0xFFFFFFFFFFFFFFFFull / nCount < 0x20ull) {
        throw std::bad_alloc();
    }
    g_pfnNpcOperatorNew((long long)(nCount << 5));
}

// 0x140081410 - alloc-raw
void FUN_140081410(void* pAllocator, unsigned long long nCount) {
    (void)pAllocator;
    if (nCount != 0 && 0xFFFFFFFFFFFFFFFFull / nCount < 0x20ull) {
        throw std::bad_alloc();
    }
    g_pfnNpcOperatorNew((long long)(nCount << 5));
}

// 0x140081680 - alloc-raw
void FUN_140081680(void* pAllocator, unsigned long long nCount) {
    (void)pAllocator;
    if (nCount != 0 && 0xFFFFFFFFFFFFFFFFull / nCount < 0x10ull) {
        throw std::bad_alloc();
    }
    g_pfnNpcOperatorNew((long long)(nCount << 4));
}

// 0x140081cb0 - memmove-forward
void* FUN_140081cb0(void* pFirst, long long nLast, void* pDest) {
    long long nCount = nLast - (long long)pFirst >> 2;
    size_t cbBytes = (size_t)nCount * 4;
    if (nCount != 0) {
        g_pfnNpcMemmoveS(pDest, cbBytes, pFirst, cbBytes);
    }
    return (void*)((long long)cbBytes + (long long)pDest);
}

// 0x140082760 - iterator-bounds
unsigned long long* FUN_140082760(unsigned long long* pOut, unsigned long long nPosition, unsigned long long* pSource) {
    pOut[0] = 0;
    if (pSource == nullptr || nPosition < pSource[3] || pSource[4] < nPosition) {
        NpcInvalidParameter();
    }
    pOut[1] = nPosition;
    pOut[0] = pSource[0];
    return pOut;
}

// 0x140082800 - iterator-bounds
unsigned long long* FUN_140082800(unsigned long long* pOut, unsigned long long nPosition, unsigned long long* pSource) {
    pOut[0] = 0;
    if (pSource == nullptr || nPosition < pSource[3] || pSource[4] < nPosition) {
        NpcInvalidParameter();
    }
    pOut[1] = nPosition;
    pOut[0] = pSource[0];
    return pOut;
}

// 0x140082860 - iterator-bounds
unsigned long long* FUN_140082860(unsigned long long* pOut, unsigned long long nPosition, unsigned long long* pSource) {
    pOut[0] = 0;
    if (pSource == nullptr || nPosition < pSource[3] || pSource[4] < nPosition) {
        NpcInvalidParameter();
    }
    pOut[1] = nPosition;
    pOut[0] = pSource[0];
    return pOut;
}

// 0x140082aa0 - position-build
unsigned long long* FUN_140082aa0(unsigned long long* pOut, unsigned long long* pSource) {
    unsigned long long nWord = pSource[3];
    pOut[0] = 0;
    if ((unsigned long long)pSource[4] < nWord) {
        NpcInvalidParameter();
    }
    pOut[1] = nWord;
    pOut[0] = pSource[0];
    return pOut;
}

// 0x140082af0 - iterator-bounds
unsigned long long* FUN_140082af0(unsigned long long* pOut, unsigned long long nPosition, unsigned long long* pSource) {
    pOut[0] = 0;
    if (pSource == nullptr || nPosition < pSource[3] || pSource[4] < nPosition) {
        NpcInvalidParameter();
    }
    pOut[1] = nPosition;
    pOut[0] = pSource[0];
    return pOut;
}

// 0x140082df0 - memmove-forward
void* FUN_140082df0(void* pFirst, long long nLast, void* pDest) {
    long long nCount = nLast - (long long)pFirst >> 2;
    size_t cbBytes = (size_t)nCount * 4;
    if (nCount != 0) {
        g_pfnNpcMemmoveS(pDest, cbBytes, pFirst, cbBytes);
    }
    return (void*)((long long)cbBytes + (long long)pDest);
}

// 0x1400831a0 - position-build
unsigned long long* FUN_1400831a0(unsigned long long* pOut, unsigned long long* pSource) {
    unsigned long long nWord = pSource[4];
    pOut[0] = 0;
    if (nWord < (unsigned long long)pSource[3]) {
        NpcInvalidParameter();
    }
    pOut[1] = nWord;
    pOut[0] = pSource[0];
    return pOut;
}

// 0x1400831f0 - position-build
unsigned long long* FUN_1400831f0(unsigned long long* pOut, unsigned long long* pSource) {
    unsigned long long nWord = pSource[4];
    pOut[0] = 0;
    if (nWord < (unsigned long long)pSource[3]) {
        NpcInvalidParameter();
    }
    pOut[1] = nWord;
    pOut[0] = pSource[0];
    return pOut;
}

// 0x1400832e0 - iterator-bounds
unsigned long long* FUN_1400832e0(unsigned long long* pOut, unsigned long long nPosition, unsigned long long* pSource) {
    pOut[0] = 0;
    if (pSource == nullptr || nPosition < pSource[3] || pSource[4] < nPosition) {
        NpcInvalidParameter();
    }
    pOut[1] = nPosition;
    pOut[0] = pSource[0];
    return pOut;
}

// 0x140083470 - position-build
unsigned long long* FUN_140083470(unsigned long long* pOut, unsigned long long* pSource) {
    unsigned long long nWord = pSource[3];
    pOut[0] = 0;
    if ((unsigned long long)pSource[4] < nWord) {
        NpcInvalidParameter();
    }
    pOut[1] = nWord;
    pOut[0] = pSource[0];
    return pOut;
}

// 0x140083710 - iterator-bounds
unsigned long long* FUN_140083710(unsigned long long* pOut, unsigned long long nPosition, unsigned long long* pSource) {
    pOut[0] = 0;
    if (pSource == nullptr || nPosition < pSource[3] || pSource[4] < nPosition) {
        NpcInvalidParameter();
    }
    pOut[1] = nPosition;
    pOut[0] = pSource[0];
    return pOut;
}

// 0x1400839b0 - memmove-forward
void* FUN_1400839b0(void* pFirst, long long nLast, void* pDest) {
    long long nCount = nLast - (long long)pFirst >> 2;
    size_t cbBytes = (size_t)nCount * 4;
    if (nCount != 0) {
        g_pfnNpcMemmoveS(pDest, cbBytes, pFirst, cbBytes);
    }
    return (void*)((long long)cbBytes + (long long)pDest);
}

// 0x140083db0 - position-build
unsigned long long* FUN_140083db0(unsigned long long* pOut, unsigned long long* pSource) {
    unsigned long long nWord = pSource[3];
    pOut[0] = 0;
    if ((unsigned long long)pSource[4] < nWord) {
        NpcInvalidParameter();
    }
    pOut[1] = nWord;
    pOut[0] = pSource[0];
    return pOut;
}

// 0x140083e00 - position-build
unsigned long long* FUN_140083e00(unsigned long long* pOut, unsigned long long* pSource) {
    unsigned long long nWord = pSource[4];
    pOut[0] = 0;
    if (nWord < (unsigned long long)pSource[3]) {
        NpcInvalidParameter();
    }
    pOut[1] = nWord;
    pOut[0] = pSource[0];
    return pOut;
}

// 0x1400843a0 - position-build
unsigned long long* FUN_1400843a0(unsigned long long* pOut, unsigned long long* pSource) {
    unsigned long long nWord = pSource[3];
    pOut[0] = 0;
    if ((unsigned long long)pSource[4] < nWord) {
        NpcInvalidParameter();
    }
    pOut[1] = nWord;
    pOut[0] = pSource[0];
    return pOut;
}

// 0x1400843f0 - position-build
unsigned long long* FUN_1400843f0(unsigned long long* pOut, unsigned long long* pSource) {
    unsigned long long nWord = pSource[4];
    pOut[0] = 0;
    if (nWord < (unsigned long long)pSource[3]) {
        NpcInvalidParameter();
    }
    pOut[1] = nWord;
    pOut[0] = pSource[0];
    return pOut;
}

// 0x14008dde0 - alloc-raw
void FUN_14008dde0(unsigned long long nCount) {
    if (nCount != 0 && 0xFFFFFFFFFFFFFFFFull / nCount < 0x58ull) {
        throw std::bad_alloc();
    }
    g_pfnNpcOperatorNew((long long)(nCount * 88));
}

// 0x14008de60 - alloc-raw
void FUN_14008de60(unsigned long long nCount) {
    if (nCount != 0 && 0xFFFFFFFFFFFFFFFFull / nCount < 0x30ull) {
        throw std::bad_alloc();
    }
    g_pfnNpcOperatorNew((long long)(nCount * 48));
}

// 0x14008e470 - alloc-raw
void FUN_14008e470(void* pAllocator, unsigned long long nCount) {
    (void)pAllocator;
    if (nCount != 0 && 0xFFFFFFFFFFFFFFFFull / nCount < 0x58ull) {
        throw std::bad_alloc();
    }
    g_pfnNpcOperatorNew((long long)(nCount * 88));
}

// 0x14008e6b0 - alloc-raw
void FUN_14008e6b0(void* pAllocator, unsigned long long nCount) {
    (void)pAllocator;
    if (nCount != 0 && 0xFFFFFFFFFFFFFFFFull / nCount < 0x30ull) {
        throw std::bad_alloc();
    }
    g_pfnNpcOperatorNew((long long)(nCount * 48));
}

const NpcShapeEntry g_aNpcShape_140080000[] = {
    { "1400806e0", "alloc-raw", (void*)&FUN_1400806e0, 48LL, 1LL },
    { "140080760", "alloc-raw", (void*)&FUN_140080760, 32LL, 1LL },
    { "140080800", "alloc-raw", (void*)&FUN_140080800, 32LL, 1LL },
    { "1400808a0", "alloc-raw", (void*)&FUN_1400808a0, 16LL, 1LL },
    { "140080ca0", "memmove-forward", (void*)&FUN_140080ca0, 4LL, 0LL },
    { "140081310", "alloc-raw", (void*)&FUN_140081310, 48LL, 2LL },
    { "140081380", "alloc-raw", (void*)&FUN_140081380, 32LL, 2LL },
    { "140081410", "alloc-raw", (void*)&FUN_140081410, 32LL, 2LL },
    { "140081680", "alloc-raw", (void*)&FUN_140081680, 16LL, 2LL },
    { "140081cb0", "memmove-forward", (void*)&FUN_140081cb0, 4LL, 0LL },
    { "140082760", "iterator-bounds", (void*)&FUN_140082760, 3LL, 4LL },
    { "140082800", "iterator-bounds", (void*)&FUN_140082800, 3LL, 4LL },
    { "140082860", "iterator-bounds", (void*)&FUN_140082860, 3LL, 4LL },
    { "140082aa0", "position-build", (void*)&FUN_140082aa0, 3LL, 4LL },
    { "140082af0", "iterator-bounds", (void*)&FUN_140082af0, 3LL, 4LL },
    { "140082df0", "memmove-forward", (void*)&FUN_140082df0, 4LL, 0LL },
    { "1400831a0", "position-build", (void*)&FUN_1400831a0, 4LL, 3LL },
    { "1400831f0", "position-build", (void*)&FUN_1400831f0, 4LL, 3LL },
    { "1400832e0", "iterator-bounds", (void*)&FUN_1400832e0, 3LL, 4LL },
    { "140083470", "position-build", (void*)&FUN_140083470, 3LL, 4LL },
    { "140083710", "iterator-bounds", (void*)&FUN_140083710, 3LL, 4LL },
    { "1400839b0", "memmove-forward", (void*)&FUN_1400839b0, 4LL, 0LL },
    { "140083db0", "position-build", (void*)&FUN_140083db0, 3LL, 4LL },
    { "140083e00", "position-build", (void*)&FUN_140083e00, 4LL, 3LL },
    { "1400843a0", "position-build", (void*)&FUN_1400843a0, 3LL, 4LL },
    { "1400843f0", "position-build", (void*)&FUN_1400843f0, 4LL, 3LL },
    { "14008dde0", "alloc-raw", (void*)&FUN_14008dde0, 88LL, 1LL },
    { "14008de60", "alloc-raw", (void*)&FUN_14008de60, 48LL, 1LL },
    { "14008e470", "alloc-raw", (void*)&FUN_14008e470, 88LL, 2LL },
    { "14008e6b0", "alloc-raw", (void*)&FUN_14008e6b0, 48LL, 2LL },
};

const int g_nNpcShape_140080000 = 30;

}  // namespace tq
