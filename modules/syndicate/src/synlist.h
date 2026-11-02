// ============================================================================
// synlist.h — RAW Syndicate.dll v6159 · the two list shapes CSyndicate is made of.
//   A simple one: an eight byte sentinel node that points back at its head, then three
//   qwords the constructor clears (0x30 bytes).
//   A heavier one: the sentinel plus a header allocated at the end, carrying a nil flag in
//   its last two bytes and three pointers that point at itself (0x40 bytes).
// ============================================================================
#ifndef SYNDICATE_SYNLIST_H
#define SYNDICATE_SYNLIST_H

#include <cstdint>
#include <cstddef>

namespace tq {

// +0x00 the sentinel node, +0x18/+0x20/+0x28 cleared, +0x08/+0x10 left alone
struct SynSimpleList {
    void* pNode;    // +0x00
    uint64_t u8;    // +0x08
    uint64_t u10;   // +0x10
    uint64_t u18;   // +0x18
    uint64_t u20;   // +0x20
    uint64_t u28;   // +0x28
};

// the header an owned block allocates: three pointers that are all set to itself
struct SynHeader {
    SynHeader* p0;      // +0x00
    SynHeader* p8;      // +0x08
    SynHeader* p10;     // +0x10
};

// a node of the tree these blocks hold: left, right, value, and the nil flag at +0x1d
struct SynNode {
    SynNode* pLeft;     // +0x00
    void* pParent;      // +0x08
    SynNode* pRight;    // +0x10
};

struct SynBlock {
    void* pNode;        // +0x00
    uint64_t u8;        // +0x08
    uint64_t u10;       // +0x10
    uint64_t u18;       // +0x18
    uint64_t u20;       // +0x20
    uint64_t u28;       // +0x28
    void* pHeader;      // +0x30
    uint64_t u38;       // +0x38, the count
};

// the four header allocators, each a size and two flag bytes at the end
void* SynHeaderAlloc28();   // 0x141793680, 0x28 bytes, bytes 0x20=1 0x21=0
void* SynHeaderAlloc30();   // 0x141793760, 0x30 bytes, bytes 0x28=1 0x29=0
void* SynHeaderAlloc20();   // 0x141726c30, 0x20 bytes, bytes 0x1c=1 0x1d=0
void* SynHeaderAlloc68();   // 0x1417935d0, 0x68 bytes, bytes 0x60=1 0x61=0

// the block initialisers, each named for the header it takes
void SynBlockInit08(void* pBlock);      // 0x14179d4d0, header 0x28, nil flag 0x21
void SynBlockInit20(void* pBlock);      // 0x141731fc0, header 0x20, nil flag 0x1d
void SynBlockInit30(void* pBlock);      // 0x14179d550, header 0x30, nil flag 0x29
void SynBlockInit68(void* pBlock);      // 0x1417a23f0, header 0x68, nil flag 0x61

// the simple one, as the constructor writes it
void SynSimpleListInit(void* pHead);    // inline in 0x1417a2470

// 0x141726210 and 0x141727640
void SynNodeErase(void* pCtx, SynNode* pNode);
void SynBlockClear(SynBlock* pBlock);

}  // namespace tq

#endif  // SYNDICATE_SYNLIST_H
