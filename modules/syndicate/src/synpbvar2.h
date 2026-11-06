// ============================================================================
// synpbvar2.h — RAW Syndicate.dll v6159 · the rest of the varint reader chain.
//   0x1417e5270  ParseVarint32Array(p, uint32_t* out) -> new pointer, or 0 when the value
//        carries more than five continuation bytes past its thirty-second bit. The five bytes
//        are unrolled with the same subtraction of the continuation bit that the 64-bit reader
//        uses, then a bounded skip loop counts the leftovers.
//   0x1417e3bc0  ReadVarint32(this) -> uint32: from the buffer through 0x1417e5270 when the
//        bytes are known to be complete, otherwise 0x1417e3af0 walks the block; the branch that
//        reaches the block also runs the end-of-stream test at +0x2c/+0x18/+0x28/+0x30 and can
//        raise +0x24 instead.
//   0x1417e3ca0  ReadVarint64Slow(this, uint64_t* out): one byte at a time, refilling through
//        0x1417e4140 when the buffer runs dry, at most ten bytes.
// ============================================================================
#ifndef TQ_SYN_PBVAR2_H
#define TQ_SYN_PBVAR2_H

#include <cstddef>
#include <cstdint>

namespace tq {

extern int32_t (*g_fnV2Avail)(void* pThis);               // 0x1417e4fb0
extern void    (*g_fnV2Advance)(void* pThis, int32_t n);  // 0x1417e50a0
extern bool    (*g_fnV2Refill)(void* pThis);              // 0x1417e4140
extern uint32_t (*g_fnV2FromBlock)(void* pThis);          // 0x1417e3af0

void* SynParseVarint32Array(const void* pData, uint32_t* pOut);   // 0x1417e5270
uint32_t SynReadVarint32(void* pThis);                            // 0x1417e3bc0
bool SynReadVarint64Slow(void* pThis, uint64_t* pOut);            // 0x1417e3ca0

}  // namespace tq

#endif
