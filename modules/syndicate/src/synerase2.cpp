// synerase2.cpp — see synerase2.h. Bodies mirror the ported id/name erases with the kind's
// own colour byte, nil byte, step and rotation pair.
#include "modules/syndicate/src/synerase2.h"

#include "modules/syndicate/src/syntreeclear2.h"
#include "modules/syndicate/src/syntreerot2.h"

#include <cstddef>
#include <cstdint>
#include <new>
#include <stdexcept>

namespace tq {
namespace {

typedef void (*StepFn)(SynTreeIter*);
typedef void (*RotFn)(void*, void*);

uint8_t* U8(void* p) { return (uint8_t*)p; }
uint8_t& At(void* p, size_t uOff) { return U8(p)[uOff]; }
uint8_t* LinkLeft(void* p) { return *(uint8_t**)p; }
uint8_t* LinkParent(void* p) { return *(uint8_t**)(U8(p) + 0x08); }
uint8_t* LinkRight(void* p) { return *(uint8_t**)(U8(p) + 0x10); }
void SetQ(void* p, size_t uOff, void* pValue) { *(void**)(U8(p) + uOff) = pValue; }

struct Kind {
    size_t uColor;
    size_t uNil;
    StepFn pfnStep;
    RotFn pfnLeft;
    RotFn pfnRight;
};

// the step of 0x1417c6580: 0x1417c6e80 with the nil byte at another offset
void IncrementAt(SynTreeIter* pIter, size_t uNil) {
    uint8_t* pNode = (uint8_t*)pIter->pNode;
    if (pNode == nullptr) {
        // the raw reports this and leaves the iterator alone
        return;
    }
    if (At(pNode, uNil) != 0) {
        // the raw reports this and leaves the iterator alone
        return;
    }
    uint8_t* pRight = LinkRight(pNode);
    if (At(pRight, uNil) == 0) {
        uint8_t* pWalk = LinkLeft(pRight);
        while (At(pWalk, uNil) == 0) {
            pRight = pWalk;
            pWalk = LinkLeft(pWalk);
        }
        pIter->pNode = pRight;
        return;
    }
    uint8_t* pWalk = LinkParent(pNode);
    while (At(pWalk, uNil) == 0 && (uint8_t*)pIter->pNode == LinkRight(pWalk)) {
        pIter->pNode = pWalk;
        pWalk = LinkParent(pWalk);
    }
    pIter->pNode = pWalk;
}

// 0x1417c9de0 with the kind's byte offsets and rotations
void EraseNodeCore(void* pMap, SynTreeIter* pOut, SynTreeIter* pIter, const Kind& rKind) {
    uint8_t* pNode = (uint8_t*)pIter->pNode;
    if (At(pNode, rKind.uNil) != 0) {
        // the raw builds a std::logic_error then a std::out_of_range carrying exactly this text
        throw std::out_of_range("invalid map/set<T> iterator");
    }
    rKind.pfnStep(pIter);

    uint8_t* pHead = *(uint8_t**)(U8(pMap) + 0x30);
    uint8_t* p8 = LinkLeft(pNode);
    uint8_t* p9 = nullptr;
    bool bSwapped = false;

    if (At(p8, rKind.uNil) == 0) {
        p9 = p8;
        if (At(LinkRight(pNode), rKind.uNil) == 0) {
            uint8_t* p7 = (uint8_t*)pIter->pNode;
            p9 = LinkRight(p7);
            if (p7 != pNode) {
                SetQ(p8, 0x08, p7);
                SetQ(p7, 0x00, p8);
                p8 = p7;
                if (p7 != LinkRight(pNode)) {
                    p8 = LinkParent(p7);
                    if (At(p9, rKind.uNil) == 0) SetQ(p9, 0x08, p8);
                    SetQ(p8, 0x00, p9);
                    SetQ(p7, 0x10, LinkRight(pNode));
                    SetQ(LinkRight(pNode), 0x08, p7);
                }
                if (*(uint8_t**)(pHead + 0x08) == pNode) {
                    SetQ(pHead, 0x08, p7);
                } else {
                    uint8_t* pParent = LinkParent(pNode);
                    if (LinkLeft(pParent) == pNode) {
                        SetQ(pParent, 0x00, p7);
                    } else {
                        SetQ(pParent, 0x10, p7);
                    }
                }
                SetQ(p7, 0x08, LinkParent(pNode));
                if (At(p7, rKind.uColor) != At(pNode, rKind.uColor)) {
                    uint8_t uSaved = At(p7, rKind.uColor);
                    At(p7, rKind.uColor) = At(pNode, rKind.uColor);
                    At(pNode, rKind.uColor) = uSaved;
                }
                bSwapped = true;
            }
        }
    } else {
        p9 = LinkRight(pNode);
    }

    if (!bSwapped) {
        p8 = LinkParent(pNode);
        if (At(p9, rKind.uNil) == 0) SetQ(p9, 0x08, p8);
        if (*(uint8_t**)(pHead + 0x08) == pNode) {
            SetQ(pHead, 0x08, p9);
        } else if (LinkLeft(p8) == pNode) {
            SetQ(p8, 0x00, p9);
        } else {
            SetQ(p8, 0x10, p9);
        }
        if (*(uint8_t**)(pHead + 0x00) == pNode) {
            uint8_t* p7 = p8;
            if (At(p9, rKind.uNil) == 0) {
                p7 = p9;
                uint8_t* pLeft = LinkLeft(p9);
                while (At(pLeft, rKind.uNil) == 0) {
                    p7 = pLeft;
                    pLeft = LinkLeft(pLeft);
                }
            }
            SetQ(pHead, 0x00, p7);
        }
        if (*(uint8_t**)(pHead + 0x10) == pNode) {
            uint8_t* p7 = p8;
            if (At(p9, rKind.uNil) == 0) {
                p7 = p9;
                uint8_t* pRight = LinkRight(p9);
                while (At(pRight, rKind.uNil) == 0) {
                    p7 = pRight;
                    pRight = LinkRight(pRight);
                }
            }
            SetQ(pHead, 0x10, p7);
        }
    }

    if (At(pNode, rKind.uColor) == 1) {
        if (p9 != *(uint8_t**)(pHead + 0x08)) {
            uint8_t* p7 = nullptr;
            do {
                p7 = p8;
                if (At(p9, rKind.uColor) != 1) break;
                p8 = LinkLeft(p7);
                if (p9 == p8) {
                    p8 = LinkRight(p7);
                    if (At(p8, rKind.uColor) == 0) {
                        At(p8, rKind.uColor) = 1;
                        At(p7, rKind.uColor) = 0;
                        rKind.pfnLeft(pMap, p7);
                        p8 = LinkRight(p7);
                    }
                    if (At(p8, rKind.uNil) == 0) {
                        if ((At(LinkLeft(p8), rKind.uColor) != 1) ||
                            (At(LinkRight(p8), rKind.uColor) != 1)) {
                            if (At(LinkRight(p8), rKind.uColor) == 1) {
                                At(LinkLeft(p8), rKind.uColor) = 1;
                                At(p8, rKind.uColor) = 0;
                                rKind.pfnRight(pMap, p8);
                                p8 = LinkRight(p7);
                            }
                            At(p8, rKind.uColor) = At(p7, rKind.uColor);
                            At(p7, rKind.uColor) = 1;
                            At(LinkRight(p8), rKind.uColor) = 1;
                            rKind.pfnLeft(pMap, p7);
                            break;
                        }
                        At(p8, rKind.uColor) = 0;
                    }
                } else {
                    if (At(p8, rKind.uColor) == 0) {
                        At(p8, rKind.uColor) = 1;
                        At(p7, rKind.uColor) = 0;
                        rKind.pfnRight(pMap, p7);
                        p8 = LinkLeft(p7);
                    }
                    if (At(p8, rKind.uNil) == 0) {
                        if ((At(LinkRight(p8), rKind.uColor) != 1) ||
                            (At(LinkLeft(p8), rKind.uColor) != 1)) {
                            if (At(LinkLeft(p8), rKind.uColor) == 1) {
                                At(LinkRight(p8), rKind.uColor) = 1;
                                At(p8, rKind.uColor) = 0;
                                rKind.pfnLeft(pMap, p8);
                                p8 = LinkLeft(p7);
                            }
                            At(p8, rKind.uColor) = At(p7, rKind.uColor);
                            At(p7, rKind.uColor) = 1;
                            At(LinkLeft(p8), rKind.uColor) = 1;
                            rKind.pfnRight(pMap, p7);
                            break;
                        }
                        At(p8, rKind.uColor) = 0;
                    }
                }
                p8 = LinkParent(p7);
                p9 = p7;
            } while (p7 != *(uint8_t**)(pHead + 0x08));
        }
        At(p9, rKind.uColor) = 1;
    }

    ::operator delete(pNode);
    // the counter only goes down when it is not already zero, exactly as in the binary
    if (*(uint64_t*)(U8(pMap) + 0x38) != 0) {
        --*(uint64_t*)(U8(pMap) + 0x38);
    }
    pOut->pTag = *(void**)pMap;
    pOut->pNode = (void*)pIter->pNode;
}

void EraseRangeCore(void* pMap, SynTreeIter* pOut, SynTreeIter* pFirst, SynTreeIter* pLast,
                    const Kind& rKind) {
    uint8_t* pHead = *(uint8_t**)(U8(pMap) + 0x30);
    if ((uint8_t*)pFirst->pNode == pHead && (uint8_t*)pLast->pNode == pHead) {
        // 0x1417ca1a0 / 0x1417ca630
        if (rKind.uNil == 0x21) {
            SynTreeClearAt21(pMap);
        } else {
            SynTreeClearIdB(pMap);
        }
        pOut->pNode = *(void**)(U8(pMap) + 0x30);
        pOut->pTag = *(void**)pMap;
        return;
    }
    while ((uint8_t*)pFirst->pNode != (uint8_t*)pLast->pNode) {
        SynTreeIter aErase = *pFirst;
        rKind.pfnStep(pFirst);
        EraseNodeCore(pMap, pOut, &aErase, rKind);
    }
    pOut->pTag = *(void**)pMap;
    pOut->pNode = pFirst->pNode;
}

void ClearAndFreeCore(void* pMap, bool bEight) {
    uint8_t* pHead = *(uint8_t**)(U8(pMap) + 0x30);
    SynTreeIter aFirst;
    aFirst.pTag = *(void**)pMap;
    aFirst.pNode = LinkLeft(pHead);
    SynTreeIter aLast;
    aLast.pTag = *(void**)pMap;
    aLast.pNode = pHead;
    SynTreeIter aOut;
    if (bEight) {
        SynTreeEraseRange28(pMap, &aOut, &aFirst, &aLast);
    } else {
        SynTreeEraseRangeIdB(pMap, &aOut, &aFirst, &aLast);
    }
    ::operator delete(*(void**)(U8(pMap) + 0x30));
    *(void**)(U8(pMap) + 0x30) = nullptr;
    *(uint64_t*)(U8(pMap) + 0x38) = 0;
}

const Kind kKind28 = {0x20, 0x21, &SynTreeIterIncrement28, &SynTreeRotateLeft28,
                      &SynTreeRotateRight28};
const Kind kKindIdB = {0x28, 0x29, &SynTreeIterIncrementIdB, &SynTreeRotateLeftIdB,
                       &SynTreeRotateRightIdB};

}  // namespace

// 0x1417c6580
void SynTreeIterIncrement28(SynTreeIter* pIter) { IncrementAt(pIter, 0x21); }

// 0x1417c6610 — the same body as 0x1417c6e80
void SynTreeIterIncrementIdB(SynTreeIter* pIter) { IncrementAt(pIter, 0x29); }

// 0x1417c9de0
void SynTreeEraseNode28(void* pMap, SynTreeIter* pOut, SynTreeIter* pIter) {
    EraseNodeCore(pMap, pOut, pIter, kKind28);
}

// 0x1417ca270
void SynTreeEraseNodeIdB(void* pMap, SynTreeIter* pOut, SynTreeIter* pIter) {
    EraseNodeCore(pMap, pOut, pIter, kKindIdB);
}

// 0x1417cc2a0
void SynTreeEraseRange28(void* pMap, SynTreeIter* pOut, SynTreeIter* pFirst, SynTreeIter* pLast) {
    EraseRangeCore(pMap, pOut, pFirst, pLast, kKind28);
}

// 0x1417cc450
void SynTreeEraseRangeIdB(void* pMap, SynTreeIter* pOut, SynTreeIter* pFirst, SynTreeIter* pLast) {
    EraseRangeCore(pMap, pOut, pFirst, pLast, kKindIdB);
}

// 0x1417cdae0
void SynMapClearAndFreeC(void* pMap) { ClearAndFreeCore(pMap, true); }

// 0x1417cdbc0
void SynMapClearAndFreeD(void* pMap) { ClearAndFreeCore(pMap, false); }

}  // namespace tq
