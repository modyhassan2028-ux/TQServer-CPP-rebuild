// synholder3.cpp — see synholder3.h. The four constructors share one body; the binary keeps one
// copy per sentinel kind, and the destructors likewise differ only in which clear they call.
#include "modules/syndicate/src/synholder3.h"

#include <new>

#include "modules/syndicate/src/synmap.h"
#include "modules/syndicate/src/synnode.h"
#include "modules/syndicate/src/synerase2.h"
#include "modules/syndicate/src/synrecordrelease.h"
#include "modules/syndicate/src/synmapclear.h"
#include "modules/syndicate/src/syntreeclear2.h"

namespace tq {

namespace {

// the tag is an eight-byte object holding the map address, and the map holds it back
inline uint8_t* MakerTag(uint8_t* pMap) {
    uint8_t* pTag = (uint8_t*)::operator new(8);
    if (pTag != nullptr) {
        *(void**)pTag = pMap;
    } else {
        pTag = nullptr;
    }
    *(void**)pMap = pTag;
    return pTag;
}

inline uint8_t* MakerCtor(uint8_t* pMap, void* (*pfnSentinel)(), uint32_t uNilOff) {
    MakerTag(pMap);
    uint8_t* pHead = (uint8_t*)pfnSentinel();
    *(void**)(pMap + 0x30) = pHead;
    pHead[uNilOff] = 1;
    *(void**)(pHead + 0x08) = pHead;
    *(void**)(pHead + 0x00) = pHead;
    *(void**)(pHead + 0x10) = pHead;
    *(uint64_t*)(pMap + 0x38) = 0;
    return pMap;
}

}  // namespace

// ---- 0x1417ce9a0 and 0x1417cf0c0 ------------------------------------------
void* SynMapCtorNameA(void* pMap) { return MakerCtor((uint8_t*)pMap, &SynNodeNewNameEmpty, 0x41); }
void* SynMapCtorNameB(void* pMap) { return MakerCtor((uint8_t*)pMap, &SynNodeNewNameEmpty, 0x41); }

// ---- 0x1417cf140 ---------------------------------------------------------
void* SynMapCtor28(void* pMap) { return MakerCtor((uint8_t*)pMap, &SynNodeNewEmpty28, 0x21); }

// ---- 0x1417ceaa0 and 0x1417cf1c0 -----------------------------------------
void* SynMapCtorIdC(void* pMap) { return MakerCtor((uint8_t*)pMap, &SynNodeNewIdEmptyB, 0x29); }
void* SynMapCtorIdD(void* pMap) { return MakerCtor((uint8_t*)pMap, &SynNodeNewIdEmptyB, 0x29); }

// ---- the destroyers ------------------------------------------------------
void SynMapDestroyIdA(void* pMap) { SynMapClearAndFreeId(pMap); ::operator delete(*(void**)pMap); }
void SynMapDestroyIdA_B(void* pMap) { SynMapClearAndFreeId(pMap); ::operator delete(*(void**)pMap); }
void SynMapDestroyName(void* pMap) { SynMapClearAndFreeName(pMap); ::operator delete(*(void**)pMap); }
void SynMapDestroyNameB(void* pMap) { SynMapClearAndFreeName(pMap); ::operator delete(*(void**)pMap); }
void SynMapDestroyC(void* pMap) { SynMapClearAndFreeC(pMap); ::operator delete(*(void**)pMap); }
void SynMapDestroyC_B(void* pMap) { SynMapClearAndFreeC(pMap); ::operator delete(*(void**)pMap); }
void SynMapDestroyD(void* pMap) { SynMapClearAndFreeD(pMap); ::operator delete(*(void**)pMap); }
void SynMapDestroyD_B(void* pMap) { SynMapClearAndFreeD(pMap); ::operator delete(*(void**)pMap); }

// ---- 0x1417ce880 ---------------------------------------------------------
void* SynMapFindInsertId(void* pMap, void* pOut, const void* pPair) {
    uint8_t* pMapBytes = (uint8_t*)pMap;
    uint8_t* pHead = *(uint8_t**)(pMapBytes + 0x30);
    uint8_t* pWhere = pHead;
    bool bLeft = true;
    uint8_t* pNode = *(uint8_t**)(pHead + 0x08);
    if (pNode[0x29] == 0) {
        do {
            pWhere = pNode;
            // the comparison is a signed dword against the node's key at +0x18
            bLeft = *(const int32_t*)pPair < *(int32_t*)(pWhere + 0x18);
            pNode = bLeft ? *(uint8_t**)pWhere : *(uint8_t**)(pWhere + 0x10);
        } while (pNode[0x29] == 0);
    }
    uint8_t* pResult = (uint8_t*)SynMapInsertIdB(pMap, pOut, bLeft, pWhere, pPair);
    *(uint64_t*)pOut = *(uint64_t*)pResult;
    *(uint64_t*)((uint8_t*)pOut + 0x08) = *(uint64_t*)(pResult + 0x08);
    return pOut;
}

}  // namespace tq
