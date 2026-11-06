// ============================================================================
// synpioprim.h — RAW Syndicate.dll v6159 · ten primitives that were still seams, now ported.
//   Each one is small enough that the whole body is visible in the instructions:
//     0x1417e7d50  ZeroCopyInputStream's destructor: *(void**)this = 0x141840c70
//     0x1417e7d70  ZeroCopyOutputStream's destructor: *(void**)this = 0x141840cd8
//     0x1417e7bf0  return *(void**)this
//     0x1417e7c40  return *(int32_t*)this
//     0x1417e4fb0  return (int32_t)(this->[0x10] - this->[0x8])
//     0x1417e50a0  this->[0x8] += (int64_t)count
//     0x1417e5aa0  the smaller of the two ints, returned as a pointer to it
//     0x1417e7ba0  the holder setter: release the old value only when it differs
//     0x1417e7830  allocate the block only when the holder is still null
//     0x1417e7770  the adaptor's flush:
//                    +0x11 set -> 0;  +0x2c == 0 -> 1;
//                    stream vt[1](stream, buffer(+0x20), +0x2c) succeeded -> +0x18 += +0x2c,
//                    +0x2c = 0, answer 1;  otherwise +0x11 = 1, 0x1417e7890(this), answer 0
// ============================================================================
#ifndef SYNDICATE_SYNPIOPRIM_H
#define SYNDICATE_SYNPIOPRIM_H

#include <cstdint>

namespace tq {

// 0x1417f37de — release a holder value
extern void (*g_fnPrimRelease)(void* pValue);
// 0x1417f2f14 — allocate a block of n bytes
extern void* (*g_fnPrimAlloc)(int64_t nBytes);
// 0x1417e7890 — the reset the flush runs on failure (port: SynMiscReset)
extern void (*g_fnPrimReset)(void* pThis);

void SynZeroInDtorBody(void* pThis);                    // 0x1417e7d50
void SynZeroOutDtorBody(void* pThis);                   // 0x1417e7d70
void* SynHolderGet(void* pThis);                        // 0x1417e7bf0
int32_t SynProbeInt(void* pThis);                       // 0x1417e7c40
int32_t SynReaderAvail(void* pThis);                    // 0x1417e4fb0
void SynReaderAdvance(void* pThis, int32_t nCount);     // 0x1417e50a0
int32_t* SynClampMin(int32_t* pA, int32_t* pB);         // 0x1417e5aa0
void SynHolderSet(void* pHolder, void* pValue);         // 0x1417e7ba0
void SynAllocateBuffer(void* pThis);                    // 0x1417e7830
bool SynOutAdaptorFlush(void* pThis);                   // 0x1417e7770

}  // namespace tq

#endif  // SYNDICATE_SYNPIOPRIM_H
