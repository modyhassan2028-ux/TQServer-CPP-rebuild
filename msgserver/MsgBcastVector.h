#ifndef MSG_BCAST_VECTOR_H
#define MSG_BCAST_VECTOR_H
#include <cstdint>

namespace msg {

// ===== M67a: the broadcast-queue VECTOR family =====
//
// The chain behind the broadcast queue update
// (FUN_1400ef8d0 - M67b):
//   FUN_140096be0  alloc (n << 4, bad_alloc guard)
//   FUN_140098660  copy range of pairs
//   FUN_14009cc60  fill n pairs
//   FUN_1400a17a0  the backward block move
//   FUN_14008e820  _Xlength_error "vector<T> too long"
//   FUN_1400b6290  the generic _Insert_n engine
//   FUN_1400ec4f0  resize (grow-at-end / shrink)
//
// VECTOR object layout (offsets VERBATIM, same shape
// as M70's SVec):
//   +0x00 head-proxy chain, +0x10 proxy formal,
//   +0x18 FIRST, +0x20 LAST, +0x28 CAP.
// Elements are 0x10-byte pairs. The insert position
// is carried by a caller STACK PAIR whose +8 holds
// the position pointer (FIRST = front insert,
// LAST = append - the engine is generic).
struct SBVec {
    uint64_t m_q0;     // +0x00 debug head chain
    uint64_t m_q8;     // +0x08
    uint64_t m_q10;    // +0x10 proxy formal
    void*    m_pFirst; // +0x18
    void*    m_pLast;  // +0x20
    void*    m_pCap;   // +0x28
};

// the _invalid_parameter_noinfo seam: the ORIGINAL
// calls the CRT abort; tests wire this to a recorder.
// Default = std::abort (the CRT behavior).
extern void (*g_fnBcastInvalidParam)();

// ===== M67a: ORIGINAL FUN_140096be0 VERBATIM =====
// the guard: n != 0 and (max / n) < 0x10 ->
// std::bad_alloc; else operator new(n << 4).
// (the ORIGINAL returns the operator_new result -
// Ghidra typed the body void; raw disasm confirms
// b6290 takes RAX after the call)
void* BcastVecAlloc(void* pProxy, uint64_t qElems);

// ===== M67a: ORIGINAL FUN_140098660 VERBATIM =====
// copy the pair range [pFrom, pTo) to pDst; return
// the advanced pDst. NOTE the literal null-guard on
// the DESTINATION before each pair copy (the raw
// MSVC release-iterator skeleton).
uint64_t* BcastVecCopy(const uint64_t* pFrom,
                       const uint64_t* pTo,
                       uint64_t* pDst);

// ===== M67a: ORIGINAL FUN_14009cc60 VERBATIM =====
// fill qN pairs from *pVal. Same literal null-guard
// on the destination.
void BcastVecFill(uint64_t* pDst, uint64_t qN,
                  const uint64_t* pVal);

// ===== M67a: ORIGINAL FUN_1400a17a0 VERBATIM =====
// the backward-walking block move: the range
// [pFrom, pTo) moves UP to end at pEnd (each pair
// at src-0x10 goes to (pEnd-pTo)+src-0x10).
void* BcastVecMoveBack(const void* pFrom,
                       const void* pTo,
                       const void* pEnd);

// ===== M67a: ORIGINAL FUN_14008e820 VERBATIM =====
[[noreturn]] void BcastVecTooLong();

// ===== M67a: ORIGINAL FUN_1400b6290 VERBATIM =====
// the generic _Insert_n engine. pPair = param_2 of
// the ORIGINAL: a stack pair whose +8 holds the
// insert position inside the vector (used at RUNTIME
// as the pos - the raw's iterator-guard dead loops
// are kept literal).
void BcastVecInsert(SBVec* pV, void* pPair,
                    uint64_t qN, const void* pVal);

// ===== M67a: ORIGINAL FUN_1400ec4f0 VERBATIM =====
// resize: grow appends (qN - size) pairs at the END
// (pair = {head, LAST}); equal -> no-op; shrink
// walks the (release-dead) move skeleton and sets
// LAST = FIRST + qN * 0x10. The proxy-chain checks
// follow the raw deref chain: *pV (head) ->
// *(head) (the container) -> +0x18/+0x20 bounds.
void BcastVecResize(SBVec* pV, uint64_t qN,
                    const void* pVal);

} // namespace msg

#endif // MSG_BCAST_VECTOR_H
