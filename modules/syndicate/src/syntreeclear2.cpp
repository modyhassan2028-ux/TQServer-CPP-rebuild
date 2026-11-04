// ============================================================================
// syntreeclear2.cpp — the four bodies are one body with the nil byte as the only difference
//   (0x21 for the 0x28-byte node kind, 0x29 for the id kind), so they share it here and each
//   entry point keeps its own address comment. The head resets are in the same order the
//   binary writes them: parent, count, left, right.
// ============================================================================
#include "modules/syndicate/src/syntreeclear2.h"

#include <cstddef>
#include <cstdint>
#include <new>

namespace tq {
namespace {

inline uint8_t* Head(void* pMap) { return *(uint8_t**)((uint8_t*)pMap + 0x30); }
inline uint8_t* Left(uint8_t* p) { return *(uint8_t**)p; }
inline uint8_t* Parent(uint8_t* p) { return *(uint8_t**)(p + 0x08); }
inline uint8_t* Right(uint8_t* p) { return *(uint8_t**)(p + 0x10); }
inline uint8_t Nil(uint8_t* p, size_t uOff) { return *(uint8_t*)(p + uOff); }

// right subtree first, then the node, then walk left
void EraseSubtree(void* pMap, uint8_t* pNode, size_t uNil) {
    while (Nil(pNode, uNil) == 0) {
        EraseSubtree(pMap, Right(pNode), uNil);
        uint8_t* pNext = Left(pNode);
        ::operator delete(pNode);
        pNode = pNext;
    }
}

void ClearCore(void* pMap, size_t uNil) {
    uint8_t* pHead = Head(pMap);
    uint8_t* p = *(uint8_t**)(pHead + 0x08);
    while (Nil(p, uNil) == 0) {
        EraseSubtree(pMap, Right(p), uNil);
        uint8_t* pNext = Left(p);
        ::operator delete(p);
        p = pNext;
    }
    uint8_t* pHead2 = Head(pMap);
    *(uint8_t**)(pHead2 + 0x08) = pHead2;
    *(uint64_t*)((uint8_t*)pMap + 0x38) = 0;
    *(uint8_t**)(Head(pMap)) = Head(pMap);
    *(uint8_t**)(Head(pMap) + 0x10) = Head(pMap);
}

}  // namespace

// 0x1417c8770 — free a subtree of the kind whose nil byte sits at +0x21
void SynTreeEraseSubtreeAt21(void* pMap, void* pNode) {
    EraseSubtree(pMap, (uint8_t*)pNode, 0x21);
}

// 0x1417ca1a0 — empty that kind: free every node, then head->parent = head, count = 0,
//   head->left = head, head->right = head
void SynTreeClearAt21(void* pMap) { ClearCore(pMap, 0x21); }

// 0x1417c87c0 — the id kind's own copy of the subtree erase, nil at +0x29
void SynTreeEraseSubtreeIdB(void* pMap, void* pNode) {
    EraseSubtree(pMap, (uint8_t*)pNode, 0x29);
}

// 0x1417ca630 — and its clear
void SynTreeClearIdB(void* pMap) { ClearCore(pMap, 0x29); }

}  // namespace tq
