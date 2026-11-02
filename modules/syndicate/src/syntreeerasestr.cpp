// ============================================================================
// syntreeerasestr.cpp — RAW Syndicate.dll v6159 · the name-keyed erase layer. The step and
//   the two rotations are the id-map bodies with the nil test moved to +0x41, so one shared
//   body serves both; the erase itself is written out because it also has to destroy the key
//   string before the node is released.
// ============================================================================
#include "modules/syndicate/src/syntreeerasestr.h"

#include <new>
#include <stdexcept>
#include <string>

namespace tq {

static inline bool IsNil(void* p) { return *(uint8_t*)((uint8_t*)p + 0x41) != 0; }
static inline uint8_t* Left(void* p) { return *(uint8_t**)((uint8_t*)p + 0x00); }
static inline uint8_t* Parent(void* p) { return *(uint8_t**)((uint8_t*)p + 0x08); }
static inline uint8_t* Right(void* p) { return *(uint8_t**)((uint8_t*)p + 0x10); }
static inline void SetLeft(void* p, void* pV) { *(void**)((uint8_t*)p + 0x00) = pV; }
static inline void SetParent(void* p, void* pV) { *(void**)((uint8_t*)p + 0x08) = pV; }
static inline void SetRight(void* p, void* pV) { *(void**)((uint8_t*)p + 0x10) = pV; }
static inline uint8_t& Colour(void* p) { return *(uint8_t*)((uint8_t*)p + 0x40); }
static inline void DestroyKey(void* p) { ((std::string*)((uint8_t*)p + 0x18))->~basic_string(); }

static inline uint8_t* MapHead(void* pMap) { return *(uint8_t**)((uint8_t*)pMap + 0x30); }
static inline uint8_t* MapRoot(void* pMap) { return Parent(MapHead(pMap)); }
static inline void SetMapRoot(void* pMap, void* pNode) { SetParent(MapHead(pMap), pNode); }
static inline uint64_t& MapCount(void* pMap) { return *(uint64_t*)((uint8_t*)pMap + 0x38); }

// ---- 0x1417c63c0
void SynTreeIterIncrementStr(SynTreeIter* pIter) {
    uint8_t* pNode = (uint8_t*)pIter->pNode;
    if (IsNil(pNode)) return;      // the raw reports it and leaves the iterator alone
    uint8_t* pRight = Right(pNode);
    if (!IsNil(pRight)) {
        uint8_t* pLeft = Left(pRight);
        while (!IsNil(pLeft)) {
            pRight = pLeft;
            pLeft = Left(pLeft);
        }
        pIter->pNode = pRight;
        return;
    }
    uint8_t* pParent = Parent(pNode);
    while (!IsNil(pParent) && (uint8_t*)pIter->pNode == Right(pParent)) {
        pIter->pNode = pParent;
        pParent = Parent(pParent);
    }
    pIter->pNode = pParent;
}

// ---- 0x1417c70e0
void SynTreeRotateLeftStr(void* pMap, void* pNode) {
    uint8_t* pRight = Right(pNode);
    SetRight(pNode, Left(pRight));
    if (!IsNil(Left(pRight))) SetParent(Left(pRight), pNode);
    SetParent(pRight, Parent(pNode));
    if (pNode == MapRoot(pMap)) {
        SetMapRoot(pMap, pRight);
    } else {
        uint8_t* pParent = Parent(pNode);
        if (pNode == Left(pParent)) SetLeft(pParent, pRight);
        else SetRight(pParent, pRight);
    }
    SetLeft(pRight, pNode);
    SetParent(pNode, pRight);
}

// ---- 0x1417c7140
void SynTreeRotateRightStr(void* pMap, void* pNode) {
    uint8_t* pLeft = Left(pNode);
    SetLeft(pNode, Right(pLeft));
    if (!IsNil(Right(pLeft))) SetParent(Right(pLeft), pNode);
    SetParent(pLeft, Parent(pNode));
    if (pNode == MapRoot(pMap)) {
        SetMapRoot(pMap, pLeft);
    } else {
        uint8_t* pParent = Parent(pNode);
        if (pNode == Right(pParent)) SetRight(pParent, pLeft);
        else SetLeft(pParent, pLeft);
    }
    SetRight(pLeft, pNode);
    SetParent(pNode, pLeft);
}

// ---- 0x1417cba90
void SynTreeEraseSubtreeStr(void* pMap, void* pNode) {
    uint8_t* p = (uint8_t*)pNode;
    while (!IsNil(p)) {
        SynTreeEraseSubtreeStr(pMap, Right(p));
        uint8_t* pNext = Left(p);
        DestroyKey(p);
        ::operator delete(p);
        p = pNext;
    }
}

// ---- 0x1417cbee0
void SynTreeEraseNodeStr(void* pMap, SynTreeIter* pOut, SynTreeIter* pIter) {
    uint8_t* pNode = (uint8_t*)pIter->pNode;
    if (IsNil(pNode)) throw std::out_of_range("invalid map/set iterator");

    SynTreeIterIncrementStr(pIter);

    uint8_t* p8 = Left(pNode);
    uint8_t* p9 = nullptr;
    bool bSwapped = false;

    if (!IsNil(p8)) {
        p9 = p8;
        if (!IsNil(Right(pNode))) {
            uint8_t* p7 = (uint8_t*)pIter->pNode;
            p9 = Right(p7);
            if (p7 != pNode) {
                SetParent(p8, p7);
                SetLeft(p7, p8);
                p8 = p7;
                if (p7 != Right(pNode)) {
                    p8 = Parent(p7);
                    if (!IsNil(p9)) SetParent(p9, p8);
                    SetLeft(p8, p9);
                    SetRight(p7, Right(pNode));
                    SetParent(Right(pNode), p7);
                }
                if (MapRoot(pMap) == pNode) {
                    SetMapRoot(pMap, p7);
                } else {
                    uint8_t* pParent = Parent(pNode);
                    if (Left(pParent) == pNode) SetLeft(pParent, p7);
                    else SetRight(pParent, p7);
                }
                SetParent(p7, Parent(pNode));
                uint8_t uColour = Colour(p7);
                Colour(p7) = Colour(pNode);
                Colour(pNode) = uColour;
                bSwapped = true;
            }
        }
    } else {
        p9 = Right(pNode);
    }

    if (bSwapped) goto rebalance;

    p8 = Parent(pNode);
    if (!IsNil(p9)) SetParent(p9, p8);
    if (MapRoot(pMap) == pNode) SetMapRoot(pMap, p9);
    else if (Left(p8) == pNode) SetLeft(p8, p9);
    else SetRight(p8, p9);

    if (Left(MapHead(pMap)) == pNode) {
        uint8_t* p7 = p8;
        if (!IsNil(p9)) {
            p7 = p9;
            uint8_t* pLeft = Left(p9);
            while (!IsNil(pLeft)) {
                p7 = pLeft;
                pLeft = Left(pLeft);
            }
        }
        SetLeft(MapHead(pMap), p7);
    }
    if (Right(MapHead(pMap)) == pNode) {
        uint8_t* p7 = p8;
        if (!IsNil(p9)) {
            p7 = p9;
            uint8_t* pRight = Right(p9);
            while (!IsNil(pRight)) {
                p7 = pRight;
                pRight = Right(pRight);
            }
        }
        SetRight(MapHead(pMap), p7);
    }

rebalance:
    if (Colour(pNode) == 1) {
        if (p9 != MapRoot(pMap)) {
            uint8_t* p7 = nullptr;
            do {
                p7 = p8;
                if (Colour(p9) != 1) break;
                p8 = Left(p7);
                if (p9 == p8) {
                    p8 = Right(p7);
                    if (Colour(p8) == 0) {
                        Colour(p8) = 1;
                        Colour(p7) = 0;
                        SynTreeRotateLeftStr(pMap, p7);
                        p8 = Right(p7);
                    }
                    if (!IsNil(p8)) {
                        if ((Colour(Left(p8)) != 1) || (Colour(Right(p8)) != 1)) {
                            if (Colour(Right(p8)) == 1) {
                                Colour(Left(p8)) = 1;
                                Colour(p8) = 0;
                                SynTreeRotateRightStr(pMap, p8);
                                p8 = Right(p7);
                            }
                            Colour(p8) = Colour(p7);
                            Colour(p7) = 1;
                            Colour(Right(p8)) = 1;
                            SynTreeRotateLeftStr(pMap, p7);
                            break;
                        }
                        Colour(p8) = 0;
                    }
                } else {
                    if (Colour(p8) == 0) {
                        Colour(p8) = 1;
                        Colour(p7) = 0;
                        SynTreeRotateRightStr(pMap, p7);
                        p8 = Left(p7);
                    }
                    if (!IsNil(p8)) {
                        if ((Colour(Right(p8)) != 1) || (Colour(Left(p8)) != 1)) {
                            if (Colour(Left(p8)) == 1) {
                                Colour(Right(p8)) = 1;
                                Colour(p8) = 0;
                                SynTreeRotateLeftStr(pMap, p8);
                                p8 = Left(p7);
                            }
                            Colour(p8) = Colour(p7);
                            Colour(p7) = 1;
                            Colour(Left(p8)) = 1;
                            SynTreeRotateRightStr(pMap, p7);
                            break;
                        }
                        Colour(p8) = 0;
                    }
                }
                p8 = Parent(p7);
                p9 = p7;
            } while (p7 != MapRoot(pMap));
        }
        Colour(p9) = 1;
    }

    DestroyKey(pNode);
    ::operator delete(pNode);
    if (MapCount(pMap) != 0) MapCount(pMap) -= 1;
    pOut->pTag = *(void**)pMap;
    pOut->pNode = pIter->pNode;
}

// ---- 0x1417cd890
void SynTreeEraseRangeStr(void* pMap, SynTreeIter* pOut, SynTreeIter* pFirst, SynTreeIter* pLast) {
    uint8_t* pHead = MapHead(pMap);
    if (pFirst->pNode == pHead && pLast->pNode == pHead) {
        SynTreeEraseSubtreeStr(pMap, MapRoot(pMap));
        SetParent(MapHead(pMap), MapHead(pMap));
        MapCount(pMap) = 0;
        SetLeft(MapHead(pMap), MapHead(pMap));
        SetRight(MapHead(pMap), MapHead(pMap));
        pOut->pTag = *(void**)pMap;
        pOut->pNode = *(void**)((uint8_t*)pMap + 0x30);
        return;
    }
    while (pFirst->pNode != pLast->pNode) {
        SynTreeIter it;
        it.pTag = pFirst->pTag;
        it.pNode = pFirst->pNode;
        SynTreeIterIncrementStr(pFirst);
        SynTreeEraseNodeStr(pMap, pOut, &it);
    }
    pOut->pTag = *(void**)pMap;
    pOut->pNode = pFirst->pNode;
}

// ---- 0x1417ce710
int64_t SynManagerEraseByName(void* pMap, const std::string* pKey) {
    SynTreeRange range;
    SynTreeEqualRangeStr(pMap, &range, pKey);

    SynTreeIter first;
    first.pTag = range.pTagFirst;
    first.pNode = range.pFirst;
    SynTreeIter last;
    last.pTag = range.pTagLast;
    last.pNode = range.pLast;

    int64_t nCount = 0;
    while (first.pNode != last.pNode) {
        nCount += 1;
        SynTreeIterIncrementStr(&first);
    }

    SynTreeIter itFirst;
    itFirst.pTag = range.pTagFirst;
    itFirst.pNode = range.pFirst;
    SynTreeIter itLast;
    itLast.pTag = range.pTagLast;
    itLast.pNode = range.pLast;
    SynTreeIter out;
    SynTreeEraseRangeStr(pMap, &out, &itFirst, &itLast);
    return nCount;
}

}  // namespace tq
