// ============================================================================
// synpbwrite.h — RAW Syndicate.dll v6159 · four writer primitives.
//   Argument order is taken from the home-space reloads, not from the type names: the value
//   travels in rcx and the destination in rdx, and the little-endian helpers answer dst+n.
//   0x1417e5520  WriteLe32(value, dst)          -> dst + 4
//   0x1417e5570  WriteLe64(value, dst)          -> dst + 8
//   0x1417e46e0  WriteToBuffer(this, src, count)
//   0x1417e54d0  WriteUntilDone(obj, data, remaining*)
// ============================================================================
#ifndef TQ_SYN_PBWRITE_H
#define TQ_SYN_PBWRITE_H

#include <cstddef>
#include <cstdint>

namespace tq {

// 0x1417e5520 — writes the four bytes of the value low-first and answers the next position
void* SynWriteLe32(uint32_t uValue, void* pDst);

// 0x1417e5570 — the same for eight bytes, built from the two 32-bit halves
void* SynWriteLe64(uint64_t uValue, void* pDst);

// 0x1417e46e0 — copies into the buffer, flushing through +0x08 whenever the block is smaller
// than what is left. 0x1417e4cb0 supplies the next block and is the only way forward.
extern void (*g_fnWrGetBuffer)(void* pThis);                 // 0x1417e4cb0
extern void (*g_fnWrCopy)(void* pDst, const void* pSrc, int64_t nLen);  // 0x1417f3160
extern void (*g_fnWrConsume)(void* pThis, int32_t nCount);   // 0x1417dff70
void SynWriteToBuffer(void* pThis, const void* pSrc, int32_t nCount);

// 0x1417e54d0 — repeats the virtual call while it succeeds and the remaining count is not
// zero. The flag is the last answer, so a failure ends the loop and is reported.
bool SynWriteUntilDone(void* pObj, void* pData, int32_t* pnRemaining);

}  // namespace tq

#endif
