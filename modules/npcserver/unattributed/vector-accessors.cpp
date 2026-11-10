// Transcribed from NpcServer.exe; see vector-accessors.h.
#include "modules/npcserver/unattributed/vector-accessors.h"

namespace tq {

// 0x140026600 - the position, guarded by the owner's size at +0x20
long long FUN_140026600(long long* pIter) {
    long long* pOwner = (long long*)pIter[0];
    long long nSize;
    if (pOwner == nullptr) {
        g_pfnNpcInvalidParameter();
        pOwner = (long long*)pIter[0];
        if (pOwner == nullptr) {
            nSize = 0;
        } else {
            nSize = *pOwner;
        }
    } else {
        nSize = *pOwner;
    }
    if ((unsigned long long)*(unsigned long long*)(nSize + 0x20) <= (unsigned long long)pIter[1]) {
        g_pfnNpcInvalidParameter();
    }
    return pIter[1];
}

// 0x140026700 - the same body
long long FUN_140026700(long long* pIter) {
    long long* pOwner = (long long*)pIter[0];
    long long nSize;
    if (pOwner == nullptr) {
        g_pfnNpcInvalidParameter();
        pOwner = (long long*)pIter[0];
        if (pOwner == nullptr) {
            nSize = 0;
        } else {
            nSize = *pOwner;
        }
    } else {
        nSize = *pOwner;
    }
    if ((unsigned long long)*(unsigned long long*)(nSize + 0x20) <= (unsigned long long)pIter[1]) {
        g_pfnNpcInvalidParameter();
    }
    return pIter[1];
}

// 0x140026640 - step by 8, answering the iterator
long long* FUN_140026640(long long* pIter) {
    long long* pOwner = (long long*)pIter[0];
    long long nSize;
    if (pOwner == nullptr) {
        g_pfnNpcInvalidParameter();
        pOwner = (long long*)pIter[0];
        if (pOwner == nullptr) {
            nSize = 0;
        } else {
            nSize = *pOwner;
        }
    } else {
        nSize = *pOwner;
    }
    if ((unsigned long long)*(unsigned long long*)(nSize + 0x20) <= (unsigned long long)pIter[1]) {
        g_pfnNpcInvalidParameter();
    }
    pIter[1] = pIter[1] + 8;
    return pIter;
}

// 0x140026740 - step by 4, answering the iterator
long long* FUN_140026740(long long* pIter) {
    long long* pOwner = (long long*)pIter[0];
    long long nSize;
    if (pOwner == nullptr) {
        g_pfnNpcInvalidParameter();
        pOwner = (long long*)pIter[0];
        if (pOwner == nullptr) {
            nSize = 0;
        } else {
            nSize = *pOwner;
        }
    } else {
        nSize = *pOwner;
    }
    if ((unsigned long long)*(unsigned long long*)(nSize + 0x20) <= (unsigned long long)pIter[1]) {
        g_pfnNpcInvalidParameter();
    }
    pIter[1] = pIter[1] + 4;
    return pIter;
}

// 0x1400268f0 - the slot after the position, refusing the end marker at +0x30
long long FUN_1400268f0(long long* pIter) {
    long long* pOwner = (long long*)pIter[0];
    long long nSize;
    if (pOwner == nullptr) {
        g_pfnNpcInvalidParameter();
        pOwner = (long long*)pIter[0];
        if (pOwner == nullptr) {
            nSize = 0;
        } else {
            nSize = *pOwner;
        }
    } else {
        nSize = *pOwner;
    }
    if (pIter[1] == *(long long*)(nSize + 0x30)) {
        g_pfnNpcInvalidParameter();
    }
    return pIter[1] + 0x18;
}

// 0x140026a30 - the same body
long long FUN_140026a30(long long* pIter) {
    long long* pOwner = (long long*)pIter[0];
    long long nSize;
    if (pOwner == nullptr) {
        g_pfnNpcInvalidParameter();
        pOwner = (long long*)pIter[0];
        if (pOwner == nullptr) {
            nSize = 0;
        } else {
            nSize = *pOwner;
        }
    } else {
        nSize = *pOwner;
    }
    if (pIter[1] == *(long long*)(nSize + 0x30)) {
        g_pfnNpcInvalidParameter();
    }
    return pIter[1] + 0x18;
}

const NpcVectorAccessorEntry g_aNpcVectorAccessor[] = {
    { "140026600", "position", (void*)&FUN_140026600, 0 },
    { "140026700", "position", (void*)&FUN_140026700, 0 },
    { "140026640", "step",     (void*)&FUN_140026640, 8 },
    { "140026740", "step",     (void*)&FUN_140026740, 4 },
    { "1400268f0", "tail",     (void*)&FUN_1400268f0, 0x18 },
    { "140026a30", "tail",     (void*)&FUN_140026a30, 0x18 },
};

const int g_nNpcVectorAccessor = 6;

}  // namespace tq
