// ============================================================================
// synpbraw.h — RAW Syndicate.dll v6159 · four coded-OUTPUT bodies.
//   Correction worth recording: these were first read as readers. The helper 0x1417e5520
//   turns out to WRITE a 32-bit value little-endian into the pointer it is given and return
//   pointer+4, and the helper the varint path uses writes too — so all four are writers, and
//   the class is the output side: +0x00 the stream (vt[2] flushes, vt[4] writes),
//   +0x08 buffer_, +0x10 buffer_size_, +0x14 total_, +0x18 the error flag.
//   0x1417e47d0 WriteRaw(data, count): what fits is copied into the buffer; otherwise the
//        buffered bytes are flushed through vt[2], total_ loses the buffer size, the buffer is
//        cleared, total_ gains the count, the stream writes straight from `data` through vt[4],
//        and the error flag ORs in "the write answered zero". The size test uses buffer_size_
//        itself, not the room left — kept exactly as the instructions do it.
//   0x1417e48e0 WriteLittleEndian32(value): with four bytes of room the value is written into
//        the buffer and four bytes are consumed; otherwise into a local four and 0x1417e46e0
//        appends them.
//   0x1417e4990 WriteLittleEndian64(value): the same with eight.
//   0x1417e4b80 WriteVarint64(value): with ten bytes of room 0x1417e5740 writes the varint
//        straight into the buffer and the bytes used are consumed; otherwise a local varint is
//        built 7 bits at a time and appended through 0x1417e46e0.
// ============================================================================
#ifndef SYNDICATE_SYNPBRAW_H
#define SYNDICATE_SYNPBRAW_H

#include <cstdint>

namespace tq {

extern void (*g_fnRawConsume)(void* pThis, int32_t nCount);            // 0x1417dff70
extern bool (*g_fnRawAppend)(void* pThis, const void* pSrc, int32_t nCount);  // 0x1417e46e0
extern void* (*g_fnRawLe32)(uint32_t uValue, void* pDst);              // 0x1417e5520
extern void* (*g_fnRawLe64)(uint64_t uValue, void* pDst);              // 0x1417e5570
extern void* (*g_fnRawVarint)(uint64_t uValue, void* pDst);            // 0x1417e5740

void SynOutWriteRaw(void* pThis, const void* pData, int32_t nCount);   // 0x1417e47d0
void SynOutWriteLe32(void* pThis, uint32_t uValue);                    // 0x1417e48e0
void SynOutWriteLe64(void* pThis, uint64_t uValue);                    // 0x1417e4990
void SynOutWriteVarint64(void* pThis, uint64_t uValue);                // 0x1417e4b80

}  // namespace tq

#endif  // SYNDICATE_SYNPBRAW_H
