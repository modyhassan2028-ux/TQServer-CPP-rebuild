#ifndef MSG_BCAST_QUEUE_H
#define MSG_BCAST_QUEUE_H
#include <cstdint>

namespace msg {

// ===== M67b: the broadcast QUEUE object + update =====
//
// FUN_1400f03b0 (ctor) sets the object layout
// VERBATIM:
//   +0x08  byte flag (copied from src in update)
//   +0x10  the LIST object: +0x00 anchor{->list},
//          +0x28 sentinel node, +0x30 size
//   +0x38  sentinel ptr  (= list+0x28)
//   +0x40  list size     (= list+0x30)
//   +0x48  the VECTOR (SBVec layout: anchor@+0x00,
//          FIRST@+0x18, LAST@+0x20, CAP@+0x28)
//   +0x78/+0x80 qword copies, +0x88 dword copy
// LIST nodes: 0x40 = {next@0, prev@8, data@0x10(48)}
// The anchors are operator-new(8) cells holding a
// pointer back to their container (the raw debug
// proxy pattern).
struct SBcastQ {
    uint64_t m_q0;      // +0x00
    uint8_t  m_b8;      // +0x08
    uint8_t  m_pad[7];  // +0x09
    void*    m_pAnchor; // +0x10 (list anchor cell)
    uint64_t m_q18;     // +0x18 (list internals)
    uint64_t m_q20;     // +0x20
    uint64_t m_q28;     // +0x28
    uint64_t m_q30;     // +0x30 (list internals)
    void*    m_pSent;   // +0x38 (sentinel node)
    uint64_t m_qSize;   // +0x40 (list size)
    uint64_t m_vAnchor; // +0x48 (SBVec.m_q0)
    uint64_t m_vq8;     // +0x50 (SBVec.m_q8)
    uint64_t m_vq10;    // +0x58 (SBVec.m_q10)
    void*    m_vFirst;  // +0x60 (SBVec FIRST)
    void*    m_vLast;   // +0x68 (SBVec LAST)
    void*    m_vCap;    // +0x70 (SBVec CAP)
    uint64_t m_q78;     // +0x78
    uint64_t m_q80;     // +0x80
    uint32_t m_dw88;    // +0x88
};

// ===== M67b: ORIGINAL FUN_14009a2a0 VERBATIM =====
// allocate the 0x40 SENTINEL node {next=self,
// prev=self}; returns the node (the ctor stores it
// at +0x38 - Ghidra dropped the return)
void* BcastSentNew();

// ===== M67b: ORIGINAL FUN_14009ad30 VERBATIM =====
// allocate a 0x40 list node {next=pNext,
// prev=pPrev, data[48] copied from pData} (the raw
// literal null-checks on n+1/n+2 are tautological -
// kept as documented). Returns the node.
void* BcastListNodeNew(void* pNext, void* pPrev,
                       const void* pData);

// ===== M67b: ORIGINAL FUN_1400a5f80 VERBATIM =====
// append-COPY the source range into the dest list
// before the dest sentinel. pPos = {dest anchor,
// dest sentinel}; pItFirst/pItLast = {src anchor,
// node} iterators (begin/end). Each iteration: the
// _Compat proxy checks (raw: anchor 0 / anchors
// mismatch / walker==sentinel -> CRT abort), node
// copy, "list<T> too long" at 0x555555555555555,
// size++, relink, advance.
void BcastListAppend(void* pList, uint64_t* pPos,
                     uint64_t* pItFirst,
                     uint64_t* pItLast);

// ===== M67b: ORIGINAL FUN_1400ef8d0 VERBATIM =====
// the broadcast queue update:
//   1. resize the dest VECTOR to the src vector
//      count with fill {anchor, dest sentinel}
//   2. copy +0x78/+0x80/+0x88 from src
//   3. clear the dest list (delete nodes)
//   4. append-COPY the src list (a5f80)
//   5. copy the +0x08 byte
//   6. the sync walk: for each dest vector slot,
//      match src pair[i].second against the src
//      node walker; on match write
//      {anchor, dest walker} and i++; else advance
//      BOTH walkers (end-guards = the CRT abort
//      seam)
void BcastQueueUpdate(SBcastQ* pQ, SBcastQ* pSrc);

// ===== M67b: ORIGINAL FUN_1400f03b0 VERBATIM =====
// the ctor: byte copy, list anchor + sentinel +
// size, vector anchor + null triple, then the
// update from pSrc. Returns pQ.
SBcastQ* BcastQCreate(SBcastQ* pQ, SBcastQ* pSrc);

} // namespace msg

#endif // MSG_BCAST_QUEUE_H
