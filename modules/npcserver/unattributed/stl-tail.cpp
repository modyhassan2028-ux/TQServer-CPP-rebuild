// Generated from NpcServer.exe 0x140080000..0x140090000 by tools/gen_stl_tail.py.
#include "modules/npcserver/unattributed/stl-tail.h"

namespace tq {

// 0x140080c40 - move-backward
void* FUN_140080c40(void* pFirst, long long nLast, long long nDst) {
    long long nCount = nLast - (long long)pFirst >> 2;
    void* pDst = (void*)(nDst + nCount * -4);
    if (0 < nCount) {
        g_pfnNpcMemmoveS(pDst, (size_t)(nCount * 4), pFirst, (size_t)(nCount * 4));
    }
    return pDst;
}

// 0x140081b10 - move-backward
void* FUN_140081b10(void* pFirst, long long nLast, long long nDst) {
    long long nCount = nLast - (long long)pFirst >> 2;
    void* pDst = (void*)(nDst + nCount * -4);
    if (0 < nCount) {
        g_pfnNpcMemmoveS(pDst, (size_t)(nCount * 4), pFirst, (size_t)(nCount * 4));
    }
    return pDst;
}

// 0x140081c10 - clear-or-drop
void FUN_140081c10(unsigned long long* pOut) {
    void** pControl = (void**)pOut[1];
    if (pControl == nullptr) {
        pOut[1] = 0;
        pOut[0] = 0;
        return;
    }
    if (__atomic_sub_fetch((int*)((char*)pControl + 0x10), 1, __ATOMIC_SEQ_CST) == 0) {
        ((void (*)(void**))pControl[0])(pControl);
        if (__atomic_sub_fetch((int*)((char*)pControl + 0x14), 1, __ATOMIC_SEQ_CST) == 0) {
            ((void (*)(void**))pControl[1])(pControl);
        }
    }
    pOut[1] = 0;
    pOut[0] = 0;
}

// 0x140082280 - clear-or-drop
void FUN_140082280(unsigned long long* pOut) {
    void** pControl = (void**)pOut[1];
    if (pControl == nullptr) {
        pOut[1] = 0;
        pOut[0] = 0;
        return;
    }
    if (__atomic_sub_fetch((int*)((char*)pControl + 0x10), 1, __ATOMIC_SEQ_CST) == 0) {
        ((void (*)(void**))pControl[0])(pControl);
        if (__atomic_sub_fetch((int*)((char*)pControl + 0x14), 1, __ATOMIC_SEQ_CST) == 0) {
            ((void (*)(void**))pControl[1])(pControl);
        }
    }
    pOut[1] = 0;
    pOut[0] = 0;
}

// 0x140082b70 - ref-fill
void FUN_140082b70(unsigned long long* pOut, unsigned long long* pSource) {
    if (pOut != nullptr) {
        pOut[0] = 0;
        pOut[1] = 0;
        FUN_1400814a0(pOut, pSource[0], (void*)(unsigned long long)pSource[1]);
    }
}

// 0x140082c30 - move-backward
void* FUN_140082c30(void* pFirst, long long nLast, long long nDst) {
    long long nCount = nLast - (long long)pFirst >> 2;
    void* pDst = (void*)(nDst + nCount * -4);
    if (0 < nCount) {
        g_pfnNpcMemmoveS(pDst, (size_t)(nCount * 4), pFirst, (size_t)(nCount * 4));
    }
    return pDst;
}

// 0x140082d80 - position-member
unsigned long long* FUN_140082d80(unsigned long long* pSource, unsigned long long* pOut, long long pMember) {
    unsigned long long nWord = *(unsigned long long*)(pMember + 8);
    pOut[0] = 0;
    if (pSource == nullptr || nWord < pSource[3] || pSource[4] < nWord) {
        NpcInvalidParameter();
    }
    pOut[1] = nWord;
    pOut[0] = pSource[0];
    return pOut;
}

// 0x140083630 - position-member
unsigned long long* FUN_140083630(unsigned long long* pSource, unsigned long long* pOut, long long pMember) {
    unsigned long long nWord = *(unsigned long long*)(pMember + 8);
    pOut[0] = 0;
    if (pSource == nullptr || nWord < pSource[3] || pSource[4] < nWord) {
        NpcInvalidParameter();
    }
    pOut[1] = nWord;
    pOut[0] = pSource[0];
    return pOut;
}

// 0x140083770 - position-member
unsigned long long* FUN_140083770(unsigned long long* pSource, unsigned long long* pOut, long long pMember) {
    unsigned long long nWord = *(unsigned long long*)(pMember + 8);
    pOut[0] = 0;
    if (pSource == nullptr || nWord < pSource[3] || pSource[4] < nWord) {
        NpcInvalidParameter();
    }
    pOut[1] = nWord;
    pOut[0] = pSource[0];
    return pOut;
}

// 0x1400837d0 - ref-fill
void FUN_1400837d0(unsigned long long* pOut, unsigned long long* pSource) {
    if (pOut != nullptr) {
        pOut[0] = 0;
        pOut[1] = 0;
        FUN_1400819a0(pOut, pSource[0], (void*)(unsigned long long)pSource[1]);
    }
}

// 0x140083b10 - ref-fill
void FUN_140083b10(unsigned long long* pOut, unsigned long long* pSource) {
    if (pOut != nullptr) {
        pOut[0] = 0;
        pOut[1] = 0;
        FUN_140081a30(pOut, pSource[0], (void*)(unsigned long long)pSource[1]);
    }
}

// 0x14008e9c0 - clear-or-drop
void FUN_14008e9c0(unsigned long long* pOut) {
    void** pControl = (void**)pOut[1];
    if (pControl == nullptr) {
        pOut[1] = 0;
        pOut[0] = 0;
        return;
    }
    if (__atomic_sub_fetch((int*)((char*)pControl + 0x10), 1, __ATOMIC_SEQ_CST) == 0) {
        ((void (*)(void**))pControl[0])(pControl);
        if (__atomic_sub_fetch((int*)((char*)pControl + 0x14), 1, __ATOMIC_SEQ_CST) == 0) {
            ((void (*)(void**))pControl[1])(pControl);
        }
    }
    pOut[1] = 0;
    pOut[0] = 0;
}

const NpcTailEntry g_aNpcTail_140080000[] = {
    { "140080c40", "move-backward", (void*)&FUN_140080c40, 4LL },
    { "140081b10", "move-backward", (void*)&FUN_140081b10, 4LL },
    { "140081c10", "clear-or-drop", (void*)&FUN_140081c10, 20LL },
    { "140082280", "clear-or-drop", (void*)&FUN_140082280, 20LL },
    { "140082b70", "ref-fill", (void*)&FUN_140082b70, 5369238688LL },
    { "140082c30", "move-backward", (void*)&FUN_140082c30, 4LL },
    { "140082d80", "position-member", (void*)&FUN_140082d80, 8LL },
    { "140083630", "position-member", (void*)&FUN_140083630, 8LL },
    { "140083770", "position-member", (void*)&FUN_140083770, 8LL },
    { "1400837d0", "ref-fill", (void*)&FUN_1400837d0, 5369239968LL },
    { "140083b10", "ref-fill", (void*)&FUN_140083b10, 5369240112LL },
    { "14008e9c0", "clear-or-drop", (void*)&FUN_14008e9c0, 20LL },
};

const int g_nNpcTail_140080000 = 12;

}  // namespace tq
