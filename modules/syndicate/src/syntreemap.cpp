// ============================================================================
// syntreemap.cpp — RAW Syndicate.dll v6159 · the searches transliterated pointer for
//   pointer as the binary walks them, including the extra candidate pointer each of them
//   carries so the upper end of a range can be found on the same pass.
// ============================================================================
#include "modules/syndicate/src/syntreemap.h"
#include "modules/cqbase/src/logkernel.h"

namespace tq {

static const char kSynManagerSource[] =
    "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\synmanager.cpp";

static inline uint8_t* Head(void* pMap) { return *(uint8_t**)((uint8_t*)pMap + 0x30); }
static inline bool IsNil(void* pNode, size_t uNilOff) {
    return *(uint8_t*)((uint8_t*)pNode + uNilOff) != 0;
}
static inline uint8_t* Left(void* pNode) { return *(uint8_t**)((uint8_t*)pNode + 0x00); }
static inline uint8_t* Right(void* pNode) { return *(uint8_t**)((uint8_t*)pNode + 0x10); }
static inline uint8_t* Parent(void* pNode) { return *(uint8_t**)((uint8_t*)pNode + 0x08); }
static inline uint32_t KeyUint(void* pNode) { return *(uint32_t*)((uint8_t*)pNode + 0x18); }
static inline std::string* KeyStr(void* pNode) { return (std::string*)((uint8_t*)pNode + 0x18); }

// ---- 0x1417c8f70
void SynTreeFindUint(void* pMap, SynTreeIter* pOut, const uint32_t* pKey) {
    uint8_t* pNode = Head(pMap);
    uint8_t* p = Parent(pNode);
    if (!IsNil(p, 0x29)) {
        uint8_t* pNext;
        do {
            if (KeyUint(p) < *pKey) {
                pNext = Right(p);
            } else {
                pNext = Left(p);
                pNode = p;
            }
            p = pNext;
        } while (!IsNil(pNext, 0x29));
    }
    uint8_t* pHead = Head(pMap);
    pOut->pTag = *(void**)pMap;
    if (pNode == pHead || *pKey < KeyUint(pNode)) pOut->pNode = pHead;
    else pOut->pNode = pNode;
}

// ---- 0x1417c7ff0
void SynTreeEqualRangeUint(void* pMap, SynTreeRange* pOut, const uint32_t* pKey) {
    uint8_t* pHead = Head(pMap);
    uint8_t* pUpper = pHead;      // puVar4 in the binary
    uint8_t* pLower = pHead;      // puVar5
    uint8_t* p = Parent(pHead);
    if (!IsNil(p, 0x29)) {
        uint8_t* pNext;
        do {
            if (KeyUint(p) < *pKey) {
                pNext = Right(p);
            } else {
                if (IsNil(pUpper, 0x29) && *pKey < KeyUint(p)) pUpper = p;
                pNext = Left(p);
                pLower = p;
            }
            p = pNext;
        } while (!IsNil(pNext, 0x29));
    }

    uint8_t* p2;
    if (!IsNil(pUpper, 0x29)) p2 = Left(pUpper);
    else p2 = Parent(Head(pMap));          // the binary re-reads the head and its parent
    if (!IsNil(p2, 0x29)) {
        uint8_t* pNext;
        do {
            if (*pKey < KeyUint(p2)) {
                pNext = Left(p2);
                pUpper = p2;
            } else {
                pNext = Right(p2);
            }
            p2 = pNext;
        } while (!IsNil(pNext, 0x29));
    }

    void* pTag = *(void**)pMap;
    pOut->pTagFirst = pTag;
    pOut->pFirst = pLower;
    pOut->pTagLast = pTag;
    pOut->pLast = pUpper;
}

// ---- 0x1417c81c0
void SynTreeEqualRangeStr(void* pMap, SynTreeRange* pOut, const std::string* pKey) {
    uint8_t* pHead = Head(pMap);
    uint8_t* pUpper = pHead;      // puVar7
    uint8_t* pLastVisited = pHead;   // puVar3
    uint8_t* p = Parent(pHead);
    while (!IsNil(p, 0x41)) {
        uint8_t* pNext;
        if (*KeyStr(p) < *pKey) {
            pNext = Right(p);      // the candidate pointer only moves on the other branch
        } else {
            if (IsNil(pUpper, 0x41) && *pKey < *KeyStr(p)) pUpper = p;
            pNext = Left(p);
            pLastVisited = p;
        }
        p = pNext;
    }

    uint8_t* p2;
    if (!IsNil(pUpper, 0x41)) p2 = Left(pUpper);
    else p2 = Parent(Head(pMap));
    while (!IsNil(p2, 0x41)) {
        uint8_t* pNext;
        if (*pKey < *KeyStr(p2)) {
            pNext = Left(p2);
            pUpper = p2;
        } else {
            pNext = Right(p2);
        }
        p2 = pNext;
    }

    void* pTag = *(void**)pMap;
    pOut->pTagFirst = pTag;
    pOut->pFirst = pLastVisited;
    pOut->pTagLast = pTag;
    pOut->pLast = pUpper;
}

// ---- 0x1417cad00
void* SynManagerRecordById(void* pMgr, uint32_t uId) {
    if (uId == 0) return nullptr;
    SynTreeIter it;
    uint32_t uKey = uId;
    SynTreeFindUint((uint8_t*)pMgr + 0x08, &it, &uKey);
    void* pHead = *(void**)((uint8_t*)pMgr + 0x38);
    if (it.pNode == pHead) return nullptr;
    return *(void**)((uint8_t*)it.pNode + 0x20);
}

// ---- 0x1417cd250
bool SynManagerNameAbsent(void* pMgr, const char* pszNewName) {
    if (pszNewName == nullptr) {
        log_InlineLogERROR("\xa1\xef%s(%s)\xa1\xef in %s, %d", "CHECKF", "pszNewName",
                           kSynManagerSource, 0x48e);
        return false;
    }
    std::string strQuery(pszNewName);

    uint8_t* pHead = *(uint8_t**)((uint8_t*)pMgr + 0x78);
    uint8_t* pNode = Parent(pHead);
    uint8_t* pCand = pHead;
    while (!IsNil(pNode, 0x41)) {
        if (*KeyStr(pNode) < strQuery) {
            pNode = Right(pNode);
        } else {
            pCand = pNode;
            pNode = Left(pNode);
        }
    }

    // the binary compares the candidate against the head and then against the name once more
    uint8_t* pFound;
    if (pCand == pHead || strQuery < *KeyStr(pCand)) pFound = pHead;
    else pFound = pCand;
    return pFound == pHead;
}

}  // namespace tq
