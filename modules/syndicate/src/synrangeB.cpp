// synrangeB.cpp — see synrangeB.h
#include "modules/syndicate/src/synrangeB.h"

#include <cstddef>
#include <new>

namespace tq {

namespace {

}  // namespace

// 0x1417c5d40 — id instantiation: value at qword[1] + 0x18, head sentinel at owner +0x30
void* SynIterValueId(void* pIter) {
    void** p = (void**)pIter;
    void* pOwner = p[0];
    void* pHead = nullptr;
    if (pOwner == nullptr) {
        ::syndicate::g_fnInvalidParam();
        pOwner = p[0];
        pHead = nullptr;
        if (pOwner == nullptr) goto CheckedId;   // unreachable in the release build
    }
    pHead = *(void**)pOwner;
CheckedId:
    if (p[1] == *(void**)((uint8_t*)pHead + 0x30)) ::syndicate::g_fnInvalidParam();
    return (uint8_t*)p[1] + 0x18;
}

// 0x1417c61d0 — name instantiation, byte for byte the same body
void* SynIterValueName(void* pIter) {
    void** p = (void**)pIter;
    void* pOwner = p[0];
    void* pHead = nullptr;
    if (pOwner == nullptr) {
        ::syndicate::g_fnInvalidParam();
        pOwner = p[0];
        pHead = nullptr;
        if (pOwner == nullptr) goto CheckedName;  // unreachable in the release build
    }
    pHead = *(void**)pOwner;
CheckedName:
    if (p[1] == *(void**)((uint8_t*)pHead + 0x30)) ::syndicate::g_fnInvalidParam();
    return (uint8_t*)p[1] + 0x18;
}

// 0x1417c5fa0 — operator-- for the id instantiation
void SynIterPrevId(void* pIter) {
    void** p = (void**)pIter;
    if (p[0] == nullptr) ::syndicate::g_fnInvalidParam();
    uint8_t* pNode = (uint8_t*)p[1];
    if (pNode[0x29] != 0) {                       // the iterator sits on the sentinel
        uint8_t* pNext = *(uint8_t**)(pNode + 0x00);
        p[1] = pNext;
        if (pNext[0x29] != 0) { ::syndicate::g_fnInvalidParam(); return; }
        return;
    }
    uint8_t* pLeft = *(uint8_t**)(pNode + 0x00);
    if (pLeft[0x29] == 0) {                       // a left child exists: down, then right spine
        uint8_t* pRight = *(uint8_t**)(pLeft + 0x10);
        if (pRight[0x29] != 0) { p[1] = pLeft; return; }
        do {
            pLeft = pRight;
            pRight = *(uint8_t**)(pRight + 0x10);
        } while (pRight[0x29] == 0);
        p[1] = pLeft;
        return;
    }
    uint8_t* pParent = *(uint8_t**)(pNode + 0x08);
    if (pParent[0x29] == 0) {
        do {
            uint8_t* pParentLeft = *(uint8_t**)(pParent + 0x00);
            if (p[1] != pParentLeft) break;
            p[1] = pParent;
            pParent = *(uint8_t**)(pParent + 0x08);
        } while (pParent[0x29] == 0);
    }
    if (((uint8_t*)p[1])[0x29] != 0) { ::syndicate::g_fnInvalidParam(); return; }
    p[1] = pParent;
}

// 0x1417c6040 — the same walk with the name instantiation's nil byte at +0x41
void SynIterPrevName(void* pIter) {
    void** p = (void**)pIter;
    if (p[0] == nullptr) ::syndicate::g_fnInvalidParam();
    uint8_t* pNode = (uint8_t*)p[1];
    if (pNode[0x41] != 0) {
        uint8_t* pNext = *(uint8_t**)(pNode + 0x00);
        p[1] = pNext;
        if (pNext[0x41] != 0) { ::syndicate::g_fnInvalidParam(); return; }
        return;
    }
    uint8_t* pLeft = *(uint8_t**)(pNode + 0x00);
    if (pLeft[0x41] == 0) {
        uint8_t* pRight = *(uint8_t**)(pLeft + 0x10);
        if (pRight[0x41] != 0) { p[1] = pLeft; return; }
        do {
            pLeft = pRight;
            pRight = *(uint8_t**)(pRight + 0x10);
        } while (pRight[0x41] == 0);
        p[1] = pLeft;
        return;
    }
    uint8_t* pParent = *(uint8_t**)(pNode + 0x08);
    if (pParent[0x41] == 0) {
        do {
            uint8_t* pParentLeft = *(uint8_t**)(pParent + 0x00);
            if (p[1] != pParentLeft) break;
            p[1] = pParent;
            pParent = *(uint8_t**)(pParent + 0x08);
        } while (pParent[0x41] == 0);
    }
    if (((uint8_t*)p[1])[0x41] != 0) { ::syndicate::g_fnInvalidParam(); return; }
    p[1] = pParent;
}

// 0x1417c5c50 — leftmost node, starting from the head's left link
void* SynMapMinId(void* pHead) {
    uint8_t* pArg = (uint8_t*)pHead;
    uint8_t* pNode = *(uint8_t**)pArg;
    if (pNode[0x29] != 0) return pArg;
    do {
        pArg = pNode;
        pNode = *(uint8_t**)pNode;
    } while (pNode[0x29] == 0);
    return pArg;
}

// 0x1417c5ec0 — rightmost node, starting from the head's right link
void* SynMapMaxId(void* pHead) {
    uint8_t* pArg = (uint8_t*)pHead;
    uint8_t* pNode = *(uint8_t**)(pArg + 0x10);
    if (pNode[0x29] != 0) return pArg;
    do {
        pArg = pNode;
        pNode = *(uint8_t**)(pNode + 0x10);
    } while (pNode[0x29] == 0);
    return pArg;
}

// 0x1417c5f30
void* SynMapMinName(void* pHead) {
    uint8_t* pArg = (uint8_t*)pHead;
    uint8_t* pNode = *(uint8_t**)pArg;
    if (pNode[0x41] != 0) return pArg;
    do {
        pArg = pNode;
        pNode = *(uint8_t**)pNode;
    } while (pNode[0x41] == 0);
    return pArg;
}

// 0x1417c5f00
void* SynMapMaxName(void* pHead) {
    uint8_t* pArg = (uint8_t*)pHead;
    uint8_t* pNode = *(uint8_t**)(pArg + 0x10);
    if (pNode[0x41] != 0) return pArg;
    do {
        pArg = pNode;
        pNode = *(uint8_t**)(pNode + 0x10);
    } while (pNode[0x41] == 0);
    return pArg;
}

// 0x1417c5e60 — copy the first 16 bytes and hand the destination back
void* SynIterCopy16(void* pOut, void* pSrc) {
    uint8_t* pDst = (uint8_t*)pOut;
    uint8_t* pFrom = (uint8_t*)pSrc;
    *(uint64_t*)(pDst + 0x00) = *(uint64_t*)(pFrom + 0x00);
    *(uint64_t*)(pDst + 0x08) = *(uint64_t*)(pFrom + 0x08);
    return pOut;
}

// 0x1417c5ae0 — the same copy plus one flag byte into +0x10
void* SynIterCopy16Flag(void* pOut, void* pSrc, void* pFlag) {
    uint8_t* pDst = (uint8_t*)pOut;
    uint8_t* pFrom = (uint8_t*)pSrc;
    *(uint64_t*)(pDst + 0x00) = *(uint64_t*)(pFrom + 0x00);
    *(uint64_t*)(pDst + 0x08) = *(uint64_t*)(pFrom + 0x08);
    pDst[0x10] = *(uint8_t*)pFlag;
    return pOut;
}

// 0x1417c5980 — a dword key and a qword value (0x1417c5990 is the same body)
void* SynPairInit(void* pOut, void* pKey, void* pValue) {
    uint8_t* pDst = (uint8_t*)pOut;
    *(uint32_t*)(pDst + 0x00) = *(uint32_t*)pKey;
    *(uint64_t*)(pDst + 0x08) = *(uint64_t*)pValue;
    return pOut;
}

// 0x1417c5c80 — rcx is overwritten from rdx, then a tail jump into operator delete
void SynIterRelease(void* pUnused, void* pTarget) {
    (void)pUnused;
    ::operator delete(pTarget);
}

// 0x1417c5c70
void* SynIterIdent(void* pIn) { return pIn; }

// 0x1417c59a0 — clear the first qword, hand the object back
void* SynIterClearIdent(void* pIn) {
    *(void**)pIn = nullptr;
    return pIn;
}

// 0x1417c5c90
void* SynIterOff40(void* pIn) { return (uint8_t*)pIn + 0x40; }

// 0x1417c5f50 — the constant 0x1fffffffffffffff (max_size for the name instantiation)
uint64_t SynIterMaxSize(void) { return 0x1fffffffffffffffULL; }

}  // namespace tq
