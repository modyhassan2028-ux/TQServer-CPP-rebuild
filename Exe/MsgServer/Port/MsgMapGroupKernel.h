// ============================================================
// MsgServer strict port - unit M47
// ORIGINAL: FUN_1400f0000 @ 1400f0000 - the CMapGroupKernel
// CONSTRUCTOR + its intrusive container family:
//   FUN_14000ef40 @ 14000ef40 - ObjSet A init
//     (inner alloc FUN_140009e80, flag @inner+0x1d)
//   FUN_1400ec260 @ 1400ec260 - ObjSet B init
//     (inner alloc FUN_1400e4f40, flag @inner+0x29)
//   FUN_1400ef850 @ 1400ef850 - the arrest/jail list init
//     (inner alloc FUN_1400e50b0 = new(0x80), flag
//     @inner+0x79; FUN_1400e50b0 also zeroes the first 3
//     qwords and sets @+0x78=1)
// Container layout (0x40): [+0x00]=head node ptr
// (new(8) = {owner backptr}), [+0x30]=the inner sentinel
// (tri-self-link @+0/+8/+0x10), [+0x38]=count (0).
// Kernel layout: pairs @+0x48/+0x88, +0xc8/+0x108,
// +0x148/+0x188 (A/B) and the jail list @+0x1c8;
// dword @+0x44 = 0.
// ============================================================
#pragma once
#include <cstdint>
#include <functional>
namespace msg {
struct SInnerObj {                 // the allocated sentinel
    uint64_t m_q[16];              // sized: 0x80 for jail
};
struct SObjSet {                   // 0x40, VERBATIM layout
    void*     m_pHead;             // +0x00 (new(8) node)
    uint64_t  m_qPad[5];           // +0x08..+0x2f
    SInnerObj* m_pInner;           // +0x30 (param_1[6])
    uint64_t  m_qCount;            // +0x38 (param_1[7])
};
class CMapGroupKernel {
public:
    CMapGroupKernel();             // FUN_1400f0000
    // VERBATIM state (declaration order = the ORIGINAL
    // offsets; the std::function seams come AFTER so they
    // never shift the fixed layout):
    uint64_t m_qVft;     // +0x00: vftable slot
    uint8_t  m_base[0x3c]; // +0x08..0x43: base-class data
    uint32_t m_dw44;      // +0x44: zeroed by the ctor
    SObjSet  m_setA1;   // +0x48
    SObjSet  m_setB1;   // +0x88
    SObjSet  m_setA2;   // +0xc8
    SObjSet  m_setB2;   // +0x108
    SObjSet  m_setA3;   // +0x148
    SObjSet  m_setB3;   // +0x188
    SObjSet  m_setJail; // +0x1c8 (the arrest list)
    // the ctor seams (inner allocators), non-layout:
    std::function<SInnerObj*()> m_fnAllocA;  // FUN_140009e80
    std::function<SInnerObj*()> m_fnAllocB;  // FUN_1400e4f40
    std::function<SInnerObj*()> m_fnAllocJail; // FUN_1400e50b0
    // test observation: sizes in ctor call order (A,B,A,B,
    // A,B,JAIL = 0x20,0x30,...,0x80)
    std::vector<size_t> m_vecAllocSizes;
};


} // namespace msg

namespace msg {

// ===== M49: container insert/erase (the MSVC-Tree-style
// intrusive family). ORIGINAL:
//   FUN_14000bfd0 @ 14000bfd0 - insert
//   FUN_14000ab40 @ 14000ab40 - erase
// The sentinel flag byte (+0x1d) IS the "end()" marker.
struct SSetNode {          // ORIGINAL 0x20 node layout
    SSetNode* m_pPrev;    // +0x00 left
    SSetNode* m_pNext;    // +0x08 right
    SSetNode* m_pParent;  // +0x10 parent
    uint32_t  m_dwKey;    // +0x18 (param_5 of FUN_140009ab0)
    uint8_t   m_byColor;  // +0x1c color
    uint8_t   m_byFlag;   // +0x1d: node 0 / sentinel 1
    uint8_t   m_byReady;  // +0x1e pad (sentinel pre-flag
                          // pattern lives at size-4/-3 raw)
};

// insert: returns the new node; throws the VERBATIM
// std::length_error("map/set<T> too long") past max.
// bAfter: ORIGINAL param_3 ('\0' = link AFTER hint).
SSetNode* SetInsert(SObjSet* pSet, SSetNode* pHint,
                    bool bAfter, uint64_t qKey);

// erase: throws the VERBATIM std::out_of_range
// ("invalid map/set<T> iterator") when pIt is the
// sentinel (end()). RETURNS the updated iterator node
// (the ORIGINAL tail: uVar8=*(it+8); *ret=*set;
// ret[1]=uVar8) and decrements the count ONLY when
// nonzero (VERBATIM `if (param_1[7] != 0)`).
SSetNode* SetErase(SObjSet* pSet, SSetNode* pIt);

// ===== M50: the real tree internals (closing the M49 seams)
// ORIGINAL FUN_140009ab0 @ 140009ab0 - the tree NODE
// allocator: new(0x20) = { left, right, parent, u32 key,
// color @+0x1c, end-flag @+0x1d = 0 }.
SSetNode* TreeNodeAlloc(SSetNode* pLeft, SSetNode* pRight,
                        SSetNode* pParent, uint32_t dwKey,
                        uint8_t byColor);

// ORIGINAL FUN_1400075f0 @ 1400075f0 - the iterator
// PREVIOUS walk (operator--): three verbatim paths on the
// +0x1d sentinel flag.
void IteratorPrev(SSetNode** ppNode);
// ===== M52: the RB rotations VERBATIM =====
// ORIGINAL FUN_140008940 @ 140008940: rotate at the
// PARENT of the given node (the parent goes down-left).
void TreeRotateAtParent(SObjSet* pSet, SSetNode* p);
// ORIGINAL FUN_1400089a0 @ 1400089a0: the mirror rotate
// (the given node's LEFT rises; the node goes down).
void TreeRotateMirror(SObjSet* pSet, SSetNode* p);
} // namespace msg
