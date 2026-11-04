// ============================================================================
// syntreerot2.cpp — one body per direction, the nil byte carried as a parameter. The order of
//   the writes is the binary's: the child that moves up takes over the turning node's side,
//   its inner child is re-parented only when it is not the sentinel, the parent link is
//   carried over, then the root or the parent's side is rewritten, and finally the two nodes
//   swap places.
// ============================================================================
#include "modules/syndicate/src/syntreerot2.h"

#include <cstddef>
#include <cstdint>

namespace tq {
namespace {

inline uint8_t* MapHead(void* pMap) { return *(uint8_t**)((uint8_t*)pMap + 0x30); }
inline uint8_t* Left(uint8_t* p) { return *(uint8_t**)p; }
inline uint8_t* Parent(uint8_t* p) { return *(uint8_t**)(p + 0x08); }
inline uint8_t* Right(uint8_t* p) { return *(uint8_t**)(p + 0x10); }
inline void SetLeft(uint8_t* p, uint8_t* v) { *(uint8_t**)p = v; }
inline void SetParent(uint8_t* p, uint8_t* v) { *(uint8_t**)(p + 0x08) = v; }
inline void SetRight(uint8_t* p, uint8_t* v) { *(uint8_t**)(p + 0x10) = v; }
inline bool IsNil(uint8_t* p, size_t uNil) { return *(uint8_t*)(p + uNil) != 0; }

// the right child climbs over the node
void RotateLeftCore(void* pMap, uint8_t* pNode, size_t uNil) {
    uint8_t* pRight = Right(pNode);
    SetRight(pNode, Left(pRight));
    if (!IsNil(Left(pRight), uNil)) SetParent(Left(pRight), pNode);
    SetParent(pRight, Parent(pNode));
    if (pNode == *(uint8_t**)(MapHead(pMap) + 0x08)) {
        *(uint8_t**)(MapHead(pMap) + 0x08) = pRight;
        SetLeft(pRight, pNode);
        SetParent(pNode, pRight);
        return;
    }
    uint8_t* pParent = Parent(pNode);
    if (pNode == Left(pParent)) {
        SetLeft(pParent, pRight);
        SetLeft(pRight, pNode);
        SetParent(pNode, pRight);
        return;
    }
    SetRight(pParent, pRight);
    SetLeft(pRight, pNode);
    SetParent(pNode, pRight);
}

// the left child climbs over the node
void RotateRightCore(void* pMap, uint8_t* pNode, size_t uNil) {
    uint8_t* pLeft = Left(pNode);
    SetLeft(pNode, Right(pLeft));
    if (!IsNil(Right(pLeft), uNil)) SetParent(Right(pLeft), pNode);
    SetParent(pLeft, Parent(pNode));
    if (pNode == *(uint8_t**)(MapHead(pMap) + 0x08)) {
        *(uint8_t**)(MapHead(pMap) + 0x08) = pLeft;
        SetRight(pLeft, pNode);
        SetParent(pNode, pLeft);
        return;
    }
    uint8_t* pParent = Parent(pNode);
    if (pNode == Right(pParent)) {
        SetRight(pParent, pLeft);
        SetRight(pLeft, pNode);
        SetParent(pNode, pLeft);
        return;
    }
    SetLeft(pParent, pLeft);
    SetRight(pLeft, pNode);
    SetParent(pNode, pLeft);
}

}  // namespace

// 0x1417c71f0
void SynTreeRotateLeft28(void* pMap, void* pNode) { RotateLeftCore(pMap, (uint8_t*)pNode, 0x21); }

// 0x1417c7250
void SynTreeRotateRight28(void* pMap, void* pNode) { RotateRightCore(pMap, (uint8_t*)pNode, 0x21); }

// 0x1417c6100
void SynTreeRotateLeftIdB(void* pMap, void* pNode) { RotateLeftCore(pMap, (uint8_t*)pNode, 0x29); }

// 0x1417c6170
void SynTreeRotateRightIdB(void* pMap, void* pNode) { RotateRightCore(pMap, (uint8_t*)pNode, 0x29); }

}  // namespace tq
