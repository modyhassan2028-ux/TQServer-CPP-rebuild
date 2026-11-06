// ============================================================================
// synpbread2.h — RAW Syndicate.dll v6159 · three reader helpers.
//   0x1417e3a10  ReadVarint32Via64(this, uint32_t* out): reads through the 64-bit reader and
//        keeps only the low word of the result.
//   0x1417e3a50  ReadVarint32Fast(this, uint32_t* out): the completeness test again (ten bytes,
//        or a non-empty buffer whose last byte ends the value), the array parser when it holds,
//        and 0x1417e3a10 otherwise.
//   0x1417e5000  ResetBlockBounds(this): end moves forward by the bytes held back, then the
//        smaller of +0x28/+0x30 decides how much is held back again and the end is corrected.
// ============================================================================
#ifndef TQ_SYN_PBREAD2_H
#define TQ_SYN_PBREAD2_H

#include <cstdint>

namespace tq {

extern int32_t (*g_fnR2Avail)(void* pThis);              // 0x1417e4fb0
extern bool (*g_fnR2ReadVarint64)(void* pThis, uint64_t* pOut);   // 0x1417e3d80
extern int32_t* (*g_fnR2ClampMin)(int32_t* pA, int32_t* pB);      // 0x1417e5aa0

bool SynReadVarint32Via64(void* pThis, uint32_t* pOut);   // 0x1417e3a10
bool SynReadVarint32Fast(void* pThis, uint32_t* pOut);    // 0x1417e3a50
void SynResetBlockBounds(void* pThis);                    // 0x1417e5000

}  // namespace tq

#endif
