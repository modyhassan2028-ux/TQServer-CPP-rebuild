// ============================================================================
// synpbcodec.h — RAW Syndicate.dll v6159 · four bodies around the coded reader.
//   Two layouts appear, and they are NOT the same class, so each body keeps its own view of
//   the offsets it reads (no class identity is claimed beyond what the instructions show):
//     layout A  +0x00 the underlying stream (its vt[1] is Next(void**, int*)),
//               +0x08 buffer_, +0x10 buffer_size_ (int), +0x14 total_ (int),
//               +0x18 the end flag (byte)
//     layout B  +0x08 buffer_ (pointer), +0x10 buffer_end_ (pointer)
//   0x1417e4cb0 (A) Refresh: the stream's Next writes the size straight into +0x10 while the
//        data lands in a local and is stored at +0x08; on success total_ += size; on failure
//        buffer_ = 0, size = 0, the end flag is set and the answer is 0.
//   0x1417e4680 (A) Next(data, size): when size is already non-zero it skips the refresh,
//        otherwise a failed Refresh answers 0; then data = buffer_, size = buffer_size_.
//   0x1417e4610 (A) Skip(count): a negative count answers 0; a count above the buffered size
//        is reduced and the body refreshes and repeats; otherwise 0x1417dff70(this, count).
//   0x1417e5450 (B) a single-byte varint: buffer_ < buffer_end_ and a byte under 0x80 is
//        stored and 0x1417e50a0(this, 1) advances one byte; anything else goes to
//        0x1417e3d80 for the general read.
// ============================================================================
#ifndef SYNDICATE_SYNPBCODEC_H
#define SYNDICATE_SYNPBCODEC_H

#include <cstdint>

namespace tq {

// 0x1417dff70 — consume bytes from the current block
extern void (*g_fnCodecConsume)(void* pThis, int32_t nCount);
// 0x1417e50a0 — advance the read pointer by n
extern void (*g_fnCodecAdvance)(void* pThis, int32_t nCount);
// 0x1417e3d80 — the general varint read
extern bool (*g_fnCodecReadVarint)(void* pThis, uint64_t* pValue);
// the underlying stream's Next(void** data, int* size), reached through vt[1]
extern bool (*g_fnCodecStreamNext)(void* pStream, void** ppData, int32_t* pnSize);

bool SynCodecRefresh(void* pThis);                                  // 0x1417e4cb0
bool SynCodecNext(void* pThis, void** ppData, int32_t* pnSize);      // 0x1417e4680
bool SynCodecSkip(void* pThis, int32_t nCount);                      // 0x1417e4610
bool SynCodecReadVarintFast(void* pThis, uint64_t* pValue);          // 0x1417e5450

}  // namespace tq

#endif  // SYNDICATE_SYNPBCODEC_H
