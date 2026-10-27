#ifndef MSG_VECTOR_FAMILY_H
#define MSG_VECTOR_FAMILY_H
#include <cstdint>

namespace msg {

// ===== M70: the VECTOR assign family behind the
// hash bucket-array growth (the f880 rehash path).
//
// VECTOR object layout (offsets VERBATIM):
//   +0x18 FIRST, +0x20 LAST, +0x28 CAP
// Elements are 0x10-byte pairs.
struct SVec {
    uint64_t m_q0;    // +0x00 base/proxy (debug only)
    uint64_t m_q8;    // +0x08
    uint64_t m_q10;   // +0x10
    void*    m_pFirst;   // +0x18
    void*    m_pLast;    // +0x20
    void*    m_pCap;     // +0x28
};

// ORIGINAL FUN_1400092d0: allocate n elements with
// the bad_alloc guard (returns the new buffer)
void* VecAlloc(void* pVec, uint64_t qElems);

// ORIGINAL FUN_14000a6e0: fill n elements with the
// 16-byte value pair
void VecFill(void* pDst, int64_t qN, const void* pVal);

// ORIGINAL FUN_140009710: copy [pFrom, pTo) ->
// pDst (returns the new end)
void* VecCopy(const void* pFrom, const void* pTo,
              void* pDst);

// ORIGINAL FUN_14000bac0: move [pFrom, pTo) UP by
// (pEnd - pTo) bytes - the backward-walking overlap
// safe copy; returns the destination end
void* VecMoveBack(const void* pFrom, const void* pTo,
                  const void* pEnd);

// ORIGINAL FUN_14000eab0: insert n copies of the
// value pair AT THE FRONT of the vector (the 3
// branches VERBATIM: grow / shift / move-back)
void VecInsertFront(SVec* pV, void* pBasePair,
                    uint64_t qN, const void* pVal);

// ORIGINAL FUN_14000f4a0: clear the vector (LAST =
// FIRST) then refill with n copies of the value
// (the bucket-array rebuild primitive)
void VecClearRefill(SVec* pV, uint64_t qN,
                    const void* pVal);

} // namespace msg
#endif
