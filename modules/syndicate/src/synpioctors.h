// ============================================================================
// synpioctors.h — RAW Syndicate.dll v6159 · three constructors whose class identity is
//   proven by the vtable each one stores, plus two self-contained bodies.
//   0x1417e6070 ArrayOutputStream(void* buffer, int size, int block_size)
//        base 0x1417e7960, vtable 0x141840ca0, +0x08 = buffer, +0x10 = size,
//        +0x14 = (block_size > 0 ? block_size : size), +0x18 = 0, +0x1c = 0
//   0x1417e6a00 CopyingInputStreamAdaptor(CopyingInputStream* input, int block_size)
//        base 0x1417e78c0, vtable 0x141840d68, +0x08 = input, +0x10 = 0, +0x11 = 0,
//        +0x18 = 0, 0x1417e7b50(+0x20, 0), +0x28 = (block_size > 0 ? block_size : 0x2000),
//        +0x2c = 0, +0x30 = 0
//   0x1417e72a0 CopyingOutputStreamAdaptor(CopyingOutputStream* output, int block_size)
//        base 0x1417e7960, vtable 0x141840db0, the same fields up to +0x2c — no +0x30
//   The offsets line up exactly with the rows ported earlier (Next/BackUp/Skip/ByteCount),
//   which cross-checks both readings.
//   0x1417e51c0  little-endian 64-bit read: *out = b[0..7] assembled, return buffer + 8
//   0x1417e50d0  read `count` bytes into a std::string: a negative count or more than the
//        available bytes goes to 0x1417e3790; otherwise resize, memcpy from this+0x08,
//        advance by count and answer 1.
// ============================================================================
#ifndef SYNDICATE_SYNPIOCTORS_H
#define SYNDICATE_SYNPIOCTORS_H

#include <cstdint>

namespace tq {

extern void (*g_fnCtorBase7960)(void* pThis);           // 0x1417e7960
extern void (*g_fnCtorBase78C0)(void* pThis);           // 0x1417e78c0
extern void (*g_fnCtorMember7B50)(void* pThis, void*);  // 0x1417e7b50
extern int32_t (*g_fnCtorAvail)(void* pThis);          // 0x1417e4fb0
extern void (*g_fnCtorStrResize)(void* pStr, int64_t); // 0x1417dffb0
extern void* (*g_fnCtorStrData)(void* pStr);           // 0x1417dffe0
extern void* (*g_fnCtorCopy)(void* pDst, void* pSrc, int64_t nLen);  // 0x1417f3160
extern void (*g_fnCtorAdvance)(void* pThis, int32_t);  // 0x1417e50a0
extern bool (*g_fnCtorSlowRead)(void* pThis, void* pOut, int32_t nCount);  // 0x1417e3790

extern const uintptr_t kSynVftArrayOut;        // 0x141840ca0
extern const uintptr_t kSynVftCopyInAdaptor;   // 0x141840d68
extern const uintptr_t kSynVftCopyOutAdaptor;  // 0x141840db0

void* SynCtorArrayOut(void* pThis, void* pBuffer, int32_t nSize, int32_t nBlock);      // 0x1417e6070
void* SynCtorCopyInAdaptor(void* pThis, void* pInput, int32_t nBlock);                 // 0x1417e6a00
void* SynCtorCopyOutAdaptor(void* pThis, void* pOutput, int32_t nBlock);               // 0x1417e72a0
void* SynReadLe64(const void* pBuffer, uint64_t* pValue);                              // 0x1417e51c0
bool SynReadString(void* pThis, void* pOut, int32_t nCount);                           // 0x1417e50d0

}  // namespace tq

#endif  // SYNDICATE_SYNPIOCTORS_H
