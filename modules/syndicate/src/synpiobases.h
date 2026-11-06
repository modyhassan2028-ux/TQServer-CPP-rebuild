// ============================================================================
// synpiobases.h — RAW Syndicate.dll v6159 · the base constructors and the three body
//   destructors that were still seams. Each stored vtable names its class:
//     0x1417e7960  ZeroCopyOutputStream's constructor   -> 0x141840cd8
//     0x1417e78c0  ZeroCopyInputStream's constructor    -> 0x141840c70
//     0x1417e7b50  the holder assignment: *(void**)this = arg, return this
//     0x1417e6120  ArrayOutputStream's destructor       -> 0x141840ca0, then 0x1417e7d70
//     0x1417e6510  StringOutputStream's destructor      -> 0x141840d10, then 0x1417e7d70
//     0x1417e7360  CopyingOutputStreamAdaptor's destructor -> 0x141840db0, then the flush
//                  0x1417e7770, and only when the byte at +0x10 is set does it destroy the
//                  underlying stream through that stream's vt[0](stream, 1); then
//                  0x1417e7b70(+0x20) and the base destructor 0x1417e7d70.
//   That last body is the ownership flag protobuf keeps beside its output stream, and the
//   port keeps the same order: flush, optional destroy, member, base.
// ============================================================================
#ifndef SYNDICATE_SYNPIOBASES_H
#define SYNDICATE_SYNPIOBASES_H

#include <cstdint>

#include "modules/syndicate/src/synpioctors.h"   // kSynVftCopyOutAdaptor

namespace tq {

extern void (*g_fnBaseZeroOutDtor)(void* pThis);   // 0x1417e7d70
extern void (*g_fnBaseZeroInDtor)(void* pThis);    // 0x1417e7d50
extern bool (*g_fnBaseFlush)(void* pThis);         // 0x1417e7770
extern void (*g_fnBaseHolderDtor)(void* pThis);    // 0x1417e7b70

extern const uintptr_t kSynVftZeroOut;       // 0x141840cd8
extern const uintptr_t kSynVftZeroIn;        // 0x141840c70
extern const uintptr_t kSynVftStringOut;     // 0x141840d10

void* SynZeroOutCtor(void* pThis);                                  // 0x1417e7960
void* SynZeroInCtor(void* pThis);                                   // 0x1417e78c0
void* SynHolderAssign(void* pThis, void* pVft);                     // 0x1417e7b50
void SynArrayOutBodyDtor(void* pThis);                              // 0x1417e6120
void SynStringOutBodyDtor(void* pThis);                             // 0x1417e6510
void SynCopyOutAdaptorBodyDtor(void* pThis);                        // 0x1417e7360

}  // namespace tq

#endif  // SYNDICATE_SYNPIOBASES_H
