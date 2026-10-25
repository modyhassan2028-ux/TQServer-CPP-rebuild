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
#include <string>
#include <cstring>
#include <vector>
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

namespace msg {

// ===== M55: ORIGINAL FUN_14000d480 @ 14000d480 =====
// the KEYED sorted insert (std::_Tree::insert): walk the
// tree from inner->right (the root) comparing the u32
// keys @+0x18 (less -> +0 left, else -> +0x10), reject
// duplicates (<= leaf key on the right path / predecessor
// equality on the left path -> ret flag 0 + the existing
// head node), else insert via FUN_14000bfd0 with
// (set, iter, bAfter=bLess, hint=leaf, key).
// returns the NEW node (or nullptr when the key exists -
// in the ORIGINAL the ret pair carries the flag).
SSetNode* SetInsertKeyed(SObjSet* pSet, uint32_t dwKey,
                         bool* pbExists);

} // namespace msg

namespace msg {

// ===== M57: ORIGINAL FUN_140011620 (the prison-map list
// segment, decompile 14470-14504) =====
// Builds the LOCAL set of jail/prison map ids:
//  - local sentinel init (the 3 self-links) + a CLEAR
//    walk deleting any previous nodes (FUN_1400098c0
//    callback per node - seam)
//  - VERBATIM literal inserts: 0x177a, 0x177b, 0x177e
//    (unconditional) then, GATED by FUN_14008ac00:
//    0x177f, 0x1780, 0x1781
//  - then the ORIGINAL walks cq_config (separate unit)
struct SPrisonMaps {
    SObjSet  m_set;             // the local set (0x40)
    SInnerObj m_inner;          // its sentinel (0x20 node)
    std::function<void(uint32_t)> m_fnOnClearNode;
    std::function<bool()> m_fnGate;    // FUN_14008ac00
    SPrisonMaps();
    void Build();
    bool Has(uint32_t dwMapId);  // walk probe (test)
    size_t Size() const { return m_set.m_qCount; }
};
// ===== M58: ORIGINAL FUN_14000aff0 (find) +
// FUN_14000d630 (erase-by-key) =====
// find: the two-tracker walk from the root
// (key<nodekey -> +0x10 RIGHT, else track cand -> +0
// LEFT). Returns the EXACT-match node or nullptr.
SSetNode* SetFind(SObjSet* pSet, uint32_t dwKey);

// erase-by-key: find + erase loop; returns the erased
// count (the ORIGINAL counts duplicates - multiset).
uint32_t SetEraseKeyed(SObjSet* pSet, uint32_t dwKey);

// ===== M59: ORIGINAL FUN_140011620 percent-config block
// (decompile 14547-14605): sscanf "%u" x13, the
// over-100 zeroing + the VERBATIM error log, and the
// per-value sink dispatch (target +0xe0 when the
// config ID == 0x177a, else +0x128).
struct SPercentCfg {
    std::function<void(uint32_t, uint32_t)> m_fnSinkA;
    std::function<void(uint32_t, uint32_t)> m_fnSinkB;
    std::vector<std::string> m_vecErrs;
    // returns the parsed count (0 when out of the
    // ORIGINAL range check iVar9-1U < 0xd)
    uint32_t LoadPercentConfig(uint32_t dwId,
                               uint32_t dwType,
                               const char* szDescrib);
};

// ===== M60: ORIGINAL FUN_140011280 @ 140011280 =====
// the ACTIVITY-MAP operator[] (find-or-default-insert).
// Node layout (from the walk + the return):
//   +0 left, +8 parent, +0x10 right (M57 field map),
//   +0x18 u32 key, +0x1c VALUE record start
//   (6 ints + a sub-set), +0x75 the end-flag byte
struct SMapNode {
    SMapNode* m_pLeft;
    SMapNode* m_pParent;   // +8 (M57 map: parent)
    SMapNode* m_pRight;    // +0x10
    uint32_t  m_dwKey;     // +0x18
    uint32_t  m_aRecord[6];// +0x1c..+0x30 (6 ints)
    // +0x34..0x74: the record's INLINE SET - the ctor
    // calls FUN_14000e970(node+0x34, record+0x1c) =
    // construct + deep-copy from the source record's
    // set. RAW BYTES: the binary places the set object
    // at an UNALIGNED +0x34 (not a member), so the
    // accessor reinterprets - x64 tolerates it.
    uint8_t   m_abSubSet[0x40];
    uint8_t   m_byColor;   // +0x74 (0=red, 1=black)
    uint8_t   m_byFlag;    // +0x75 (0=node, 1=sentinel)
    SMapNode() : m_pLeft(nullptr), m_pParent(nullptr),
                 m_pRight(nullptr), m_dwKey(0),
                 m_byColor(1), m_byFlag(0) {
        std::memset(m_aRecord, 0, sizeof m_aRecord);
        std::memset(m_abSubSet, 0, sizeof m_abSubSet);
    }
};
struct SObjMap {
    void*     m_pInner;    // the sentinel node
    uint64_t  m_qCount;
};

// the operator[] VERBATIM walk + default record
// {key,0,0,0,0,0,0}; the node INSERT is a seam (the
// ORIGINAL calls FUN_140010ec0 with the built record -
// not yet ported). Returns the VALUE pointer
// (node + 0x1c).
uint32_t* MapOperatorAt(SObjMap* pMap, uint32_t dwKey);

// ===== M61: ORIGINAL FUN_140010600 link core +
// FUN_140010ec0 hint-insert head (the map insert) =====
// the VERBATIM max_size gate ("map/set<T> too long"),
// count++, and the EXACT link branches of the set
// insert generalized to map nodes:
//   root:  sent+8 = sent+0 = sent+0x10 = node
//   bAfter==0: hint+0x10(right) = node; if hint ==
//     rightmost -> rightmost = node
//   else: hint+0(left) = node; if hint == leftmost ->
//     leftmost = node
// The node ALLOCATOR (FUN_140010280: new(0x78) +
// record copy) and the map RB-fixup walk (the +0x74
// chain after the links) are the NEXT TBDs.
void MapInsertLink(SObjMap* pMap, SMapNode* pHint,
                   bool bAfter, SMapNode* pNew);

// ===== M62: ORIGINAL FUN_140010280 (new 0x78) +
// FUN_14000f740 (the node ctor) =====
// VERBATIM layout: left/parent/right links, key@+0x18,
// 6 record ints@+0x1c..+0x30, the sub-set@+0x34
// (deep copy FUN_14000e970 = TBD seam, zero-init),
// color@+0x74, end-flag@+0x75 = 0
// M64: pSrcSet = the source record's set (ctor
// param_5+7); null = construct an empty subset.
SMapNode* MapNodeNew(SMapNode* pLeft, SMapNode* pParent,
                     SMapNode* pRight,
                     const uint32_t aRec[7],
                     uint8_t byColor,
                     const SObjSet* pSrcSet);

// ===== M63: ORIGINAL FUN_14000af60 (the recursive
// clone) + FUN_14000bf20 (the set COPY) =====
// VERBATIM: clone each node via the M50 allocator
// (color copied from src+0x1c - no rebalance needed),
// recurse left/right with the new node as parent;
// dest root = the clone of the src root (sent+8);
// count copied VERBATIM from src; then the two
// boundary walks (leftmost via +0 chain, rightmost
// via +0x10 chain) from the dest root.
SSetNode* CloneTree(SObjSet* pSet, SSetNode* pSrc,
                    SSetNode* pParent);
void SetCopy(SObjSet* pDst, SObjSet* pSrc);

// the inline-set accessor (the binary's raw +0x34
// placement):
inline SObjSet* MapNodeSubSet(SMapNode* p) {
    return reinterpret_cast<SObjSet*>(p->m_abSubSet);
}

// ===== M65: ORIGINAL the FUN_140010600 tail - the
// map INSERT RB-fixup (colors @+0x74, flags @+0x75,
// root @ sent+8). The standard MSVC _Tree rebalance:
// red-parent loop, red-uncle recolor, LR/LL + RL/RR
// rotations with the root/sentinel fixups, final root
// BLACK. One aliasing line in the decompile's rotate
// operands was ambiguous; resolved to the canonical
// MSVC form (riser->parent = pivot->parent).
void MapInsertRebalance(SObjMap* pMap, SMapNode* pNew);

} // namespace msg
