// Generated from NpcServer.exe 0x140080000..0x140090000 by tools/gen_stl_refs.py.
#include "modules/npcserver/unattributed/stl-refs.h"
#include "modules/npcserver/unattributed/front-of-image.h"

#include <stdexcept>

namespace tq {


// 0x140080070 - too-long
void FUN_140080070(void) {
    throw std::length_error("vector<T> too long");
}

// 0x140080260 - too-long
void FUN_140080260(void) {
    throw std::length_error("vector<T> too long");
}

// 0x140080300 - too-long
void FUN_140080300(void) {
    throw std::length_error("vector<bool> too long");
}

// 0x1400803c0 - too-long
void FUN_1400803c0(void) {
    throw std::length_error("vector<T> too long");
}

// 0x1400814a0 - ref-assign
void FUN_1400814a0(unsigned long long* pOut, unsigned long long pValue, void* pControl) {
    if (pControl != nullptr) {
        __atomic_add_fetch((int*)((char*)pControl + 0x10), 1, __ATOMIC_SEQ_CST);
    }
    void** pOld = (void**)pOut[1];
    if (pOld != nullptr) {
        // the block this pair already held loses its strong reference, then its weak one
        if (__atomic_sub_fetch((int*)((char*)pOld + 0x10), 1, __ATOMIC_SEQ_CST) == 0) {
            ((void (*)(void**))pOld[0])(pOld);
            if (__atomic_sub_fetch((int*)((char*)pOld + 0x14), 1, __ATOMIC_SEQ_CST) == 0) {
                ((void (*)(void**))pOld[1])(pOld);
            }
        }
    }
    pOut[1] = (unsigned long long)pControl;
    pOut[0] = pValue;
}

// 0x140081910 - ref-assign
void FUN_140081910(unsigned long long* pOut, unsigned long long pValue, void* pControl) {
    if (pControl != nullptr) {
        __atomic_add_fetch((int*)((char*)pControl + 0x10), 1, __ATOMIC_SEQ_CST);
    }
    void** pOld = (void**)pOut[1];
    if (pOld != nullptr) {
        // the block this pair already held loses its strong reference, then its weak one
        if (__atomic_sub_fetch((int*)((char*)pOld + 0x10), 1, __ATOMIC_SEQ_CST) == 0) {
            ((void (*)(void**))pOld[0])(pOld);
            if (__atomic_sub_fetch((int*)((char*)pOld + 0x14), 1, __ATOMIC_SEQ_CST) == 0) {
                ((void (*)(void**))pOld[1])(pOld);
            }
        }
    }
    pOut[1] = (unsigned long long)pControl;
    pOut[0] = pValue;
}

// 0x1400819a0 - ref-assign
void FUN_1400819a0(unsigned long long* pOut, unsigned long long pValue, void* pControl) {
    if (pControl != nullptr) {
        __atomic_add_fetch((int*)((char*)pControl + 0x10), 1, __ATOMIC_SEQ_CST);
    }
    void** pOld = (void**)pOut[1];
    if (pOld != nullptr) {
        // the block this pair already held loses its strong reference, then its weak one
        if (__atomic_sub_fetch((int*)((char*)pOld + 0x10), 1, __ATOMIC_SEQ_CST) == 0) {
            ((void (*)(void**))pOld[0])(pOld);
            if (__atomic_sub_fetch((int*)((char*)pOld + 0x14), 1, __ATOMIC_SEQ_CST) == 0) {
                ((void (*)(void**))pOld[1])(pOld);
            }
        }
    }
    pOut[1] = (unsigned long long)pControl;
    pOut[0] = pValue;
}

// 0x140081a30 - ref-assign
void FUN_140081a30(unsigned long long* pOut, unsigned long long pValue, void* pControl) {
    if (pControl != nullptr) {
        __atomic_add_fetch((int*)((char*)pControl + 0x10), 1, __ATOMIC_SEQ_CST);
    }
    void** pOld = (void**)pOut[1];
    if (pOld != nullptr) {
        // the block this pair already held loses its strong reference, then its weak one
        if (__atomic_sub_fetch((int*)((char*)pOld + 0x10), 1, __ATOMIC_SEQ_CST) == 0) {
            ((void (*)(void**))pOld[0])(pOld);
            if (__atomic_sub_fetch((int*)((char*)pOld + 0x14), 1, __ATOMIC_SEQ_CST) == 0) {
                ((void (*)(void**))pOld[1])(pOld);
            }
        }
    }
    pOut[1] = (unsigned long long)pControl;
    pOut[0] = pValue;
}

// 0x140081e00 - ref-copy
unsigned long long* FUN_140081e00(unsigned long long* pOut, unsigned long long* pSource) {
    pOut[0] = 0;
    pOut[1] = 0;
    FUN_1400814a0(pOut, pSource[0], (void*)pSource[1]);
    return pOut;
}

// 0x1400824c0 - too-long
void FUN_1400824c0(void) {
    throw std::length_error("list<T> too long");
}

// 0x140082600 - too-long
void FUN_140082600(void) {
    throw std::length_error("list<T> too long");
}

// 0x140082e60 - ref-release
void* FUN_140082e60(void* pThis, unsigned int nFlags) {
    void** pControl = *(void***)((char*)pThis + 8);
    if (pControl != nullptr) {
        if (__atomic_sub_fetch((int*)((char*)pControl + 0x10), 1, __ATOMIC_SEQ_CST) == 0) {
            ((void (*)(void**))pControl[0])(pControl);
            if (__atomic_sub_fetch((int*)((char*)pControl + 0x14), 1, __ATOMIC_SEQ_CST) == 0) {
                ((void (*)(void**))pControl[1])(pControl);
            }
        }
    }
    if ((nFlags & 1) != 0) {
        g_pfnNpcOperatorDelete(pThis);
    }
    return pThis;
}

// 0x140083060 - ref-copy
unsigned long long* FUN_140083060(unsigned long long* pOut, unsigned long long* pSource) {
    pOut[0] = 0;
    pOut[1] = 0;
    FUN_140081910(pOut, pSource[0], (void*)pSource[1]);
    return pOut;
}

// 0x1400830d0 - ref-copy
unsigned long long* FUN_1400830d0(unsigned long long* pOut, unsigned long long* pSource) {
    pOut[0] = 0;
    pOut[1] = 0;
    FUN_1400819a0(pOut, pSource[0], (void*)pSource[1]);
    return pOut;
}

// 0x1400836e0 - ref-copy
unsigned long long* FUN_1400836e0(unsigned long long* pOut, unsigned long long* pSource) {
    pOut[0] = 0;
    pOut[1] = 0;
    FUN_140081a30(pOut, pSource[0], (void*)pSource[1]);
    return pOut;
}

// 0x140086430 - too-long
void FUN_140086430(void) {
    throw std::length_error("list<T> too long");
}

const NpcRefEntry g_aNpcRef_140080000[] = {
    { "140080070", "too-long", (void*)&FUN_140080070, "vector<T> too long", 0LL },
    { "140080260", "too-long", (void*)&FUN_140080260, "vector<T> too long", 0LL },
    { "140080300", "too-long", (void*)&FUN_140080300, "vector<bool> too long", 0LL },
    { "1400803c0", "too-long", (void*)&FUN_1400803c0, "vector<T> too long", 0LL },
    { "1400814a0", "ref-assign", (void*)&FUN_1400814a0, "", 16LL },
    { "140081910", "ref-assign", (void*)&FUN_140081910, "", 16LL },
    { "1400819a0", "ref-assign", (void*)&FUN_1400819a0, "", 16LL },
    { "140081a30", "ref-assign", (void*)&FUN_140081a30, "", 16LL },
    { "140081e00", "ref-copy", (void*)&FUN_140081e00, "", 5369238688LL },
    { "1400824c0", "too-long", (void*)&FUN_1400824c0, "list<T> too long", 0LL },
    { "140082600", "too-long", (void*)&FUN_140082600, "list<T> too long", 0LL },
    { "140082e60", "ref-release", (void*)&FUN_140082e60, "", 8LL },
    { "140083060", "ref-copy", (void*)&FUN_140083060, "", 5369239824LL },
    { "1400830d0", "ref-copy", (void*)&FUN_1400830d0, "", 5369239968LL },
    { "1400836e0", "ref-copy", (void*)&FUN_1400836e0, "", 5369240112LL },
    { "140086430", "too-long", (void*)&FUN_140086430, "list<T> too long", 0LL },
};

const int g_nNpcRef_140080000 = 16;

}  // namespace tq
