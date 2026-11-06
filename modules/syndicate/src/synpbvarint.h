// ============================================================================
// synpbvarint.h — RAW Syndicate.dll v6159 · the varint pair.
//   0x1417e3d80  ReadVarint64(this, uint64_t* out)   the unrolled ten-byte reader
//   0x1417e5610  WriteVarint32ToArray(value, dst)    -> dst + n, n = 1..5
// ============================================================================
#ifndef TQ_SYN_PBVARINT_H
#define TQ_SYN_PBVARINT_H

#include <cstddef>
#include <cstdint>

namespace tq {

// the reader's own pieces, all of which are ported already
extern int32_t (*g_fnViAvail)(void* pThis);              // 0x1417e4fb0
extern void    (*g_fnViAdvance)(void* pThis, int32_t n); // 0x1417e50a0
extern bool    (*g_fnViSlow)(void* pThis, uint64_t* pOut); // 0x1417e3ca0

// 0x1417e3d80
// Ten bytes are read without any per-byte bounds test; every byte but the last subtracts the
// continuation bit it carries, so the three accumulators only ever hold value bits. The
// assembles at the end are 28 and 56 because the accumulators are already pre-shifted.
bool SynReadVarint64(void* pThis, uint64_t* pOut);

// 0x1417e5610 — writes the value with the continuation bit on every byte but the last
void* SynWriteVarint32ToArray(uint32_t uValue, void* pDst);

}  // namespace tq

#endif
