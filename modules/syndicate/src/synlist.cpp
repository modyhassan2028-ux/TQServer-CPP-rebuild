// ============================================================================
// synlist.cpp — RAW Syndicate.dll v6159 · the container primitives, ported as the binary
//   writes them: the allocation is operator new, a failed node allocation leaves the head
//   null, and the header's own pointers all end up pointing back at the header.
// ============================================================================
#include "modules/syndicate/src/synlist.h"

#include <new>

namespace tq {

static_assert(sizeof(SynSimpleList) == 0x30, "the simple list is 0x30 bytes");
static_assert(sizeof(SynBlock) == 0x40, "the owned block is 0x40 bytes");
static_assert(sizeof(SynNode) == 0x18, "a node is three pointers");
static_assert(offsetof(SynBlock, pHeader) == 0x30, "the header pointer sits at +0x30");
static_assert(offsetof(SynBlock, u38) == 0x38, "the count sits at +0x38");

// ---- the four header allocators: size, three cleared pointers, two flag bytes
static void* SynHeaderAllocCommon(size_t uSize, size_t uHeadFlagOff, size_t uNilFlagOff) {
    SynHeader* p = (SynHeader*)::operator new(uSize);
    p->p0 = nullptr;
    p->p8 = nullptr;
    p->p10 = nullptr;
    *(uint8_t*)((char*)p + uHeadFlagOff) = 1;   // the "this is the header" byte
    *(uint8_t*)((char*)p + uNilFlagOff) = 0;    // the nil byte the initialisers raise
    return p;
}

void* SynHeaderAlloc28() { return SynHeaderAllocCommon(0x28, 0x20, 0x21); }  // 0x141793680
void* SynHeaderAlloc30() { return SynHeaderAllocCommon(0x30, 0x28, 0x29); }  // 0x141793760
void* SynHeaderAlloc20() { return SynHeaderAllocCommon(0x20, 0x1c, 0x1d); }  // 0x141726c30
void* SynHeaderAlloc68() { return SynHeaderAllocCommon(0x68, 0x60, 0x61); }  // 0x1417935d0

// ---- the shared block body: node at the head, header next, flag, three self pointers
static void SynBlockInitCommon(void* pBlock, void* pHeader, size_t uNilFlagOff) {
    void* pNode = ::operator new(8);
    void* pLink = nullptr;
    if (pNode != nullptr) {
        *(void**)pNode = pBlock;                // the node points back at the head
        pLink = pNode;
    }
    *(void**)pBlock = pLink;

    SynBlock* p = (SynBlock*)pBlock;
    p->pHeader = pHeader;
    *(uint8_t*)((char*)pHeader + uNilFlagOff) = 1;
    *(void**)((char*)pHeader + 0x08) = pHeader;
    *(void**)pHeader = pHeader;
    *(void**)((char*)pHeader + 0x10) = pHeader;
    p->u38 = 0;
}

void SynBlockInit08(void* pBlock) {   // 0x14179d4d0
    SynBlockInitCommon(pBlock, SynHeaderAlloc28(), 0x21);
}
void SynBlockInit20(void* pBlock) {   // 0x141731fc0
    SynBlockInitCommon(pBlock, SynHeaderAlloc20(), 0x1d);
}
void SynBlockInit30(void* pBlock) {   // 0x14179d550
    SynBlockInitCommon(pBlock, SynHeaderAlloc30(), 0x29);
}
void SynBlockInit68(void* pBlock) {   // 0x1417a23f0
    SynBlockInitCommon(pBlock, SynHeaderAlloc68(), 0x61);
}

// ---- the simple list as the constructor writes it at eleven different offsets
void SynSimpleListInit(void* pHead) {
    void* pNode = ::operator new(8);
    void* pLink = nullptr;
    if (pNode != nullptr) {
        *(void**)pNode = pHead;
        pLink = pNode;
    }
    *(void**)pHead = pLink;
    SynSimpleList* p = (SynSimpleList*)pHead;
    p->u18 = 0;
    p->u20 = 0;
    p->u28 = 0;
}

// ---- 0x141726210 — erase one subtree, right hand side first, then the node itself
void SynNodeErase(void* pCtx, SynNode* pNode) {
    uint8_t uNil = *(uint8_t*)((char*)pNode + 0x1d);
    while (uNil == 0) {
        SynNodeErase(pCtx, pNode->pRight);
        SynNode* pNext = pNode->pLeft;
        ::operator delete((void*)pNode);
        pNode = pNext;
        uNil = *(uint8_t*)((char*)pNode + 0x1d);
    }
}

// ---- 0x141727640 — walk from the header's right, erase and delete each, then reset the
//      header's three pointers to itself and the count to zero
void SynBlockClear(SynBlock* pBlock) {
    void* pHeader = pBlock->pHeader;
    SynNode* pNode = *(SynNode**)((char*)pHeader + 0x08);
    uint8_t uNil = *(uint8_t*)((char*)pNode + 0x1d);
    while (uNil == 0) {
        SynNodeErase(pBlock, pNode->pRight);
        SynNode* pNext = pNode->pLeft;
        ::operator delete((void*)pNode);
        pNode = pNext;
        uNil = *(uint8_t*)((char*)pNode + 0x1d);
    }
    *(void**)((char*)pHeader + 0x08) = pHeader;
    pBlock->u38 = 0;
    *(void**)pHeader = pHeader;
    *(void**)((char*)pHeader + 0x10) = pHeader;
}

}  // namespace tq
