// ============================================================================
// synclassdtors.h — RAW Syndicate.dll v6159 · the last unported row of three classes found
//   with an RTTI scan (tools/scan_classes.py: vtable-8 -> locator -> type descriptor).
//   0x1417a2890  CSyndicate@tq        vt 0x141833f20  the scalar deleting destructor
//        call 0x1417a1bf0(this)                       — the body destructor, always
//        if (flags & 1) 0x141791990(this)             — the free, only on bit 0
//        return this
//   0x1417d5090  CToken@syndicate     vt 0x14183be50  the scalar deleting destructor
//        *(void**)this = 0x14183be50                  — its own vtable is re-stamped
//        if (flags & 1) 0x1417f2fdc(this)             — the free, only on bit 0
//        return this                                  — no body destructor is called
//   0x1417ec100  CMsgLeagueConcubinesPB vt 0x141841748 row 8: a 5-byte thunk, jmp 0x1417ebf80
// ============================================================================
#ifndef SYNDICATE_SYNCLASSDTORS_H
#define SYNDICATE_SYNCLASSDTORS_H

#include <cstdint>

namespace tq {

// 0x1417a1bf0 — the CSyndicate body destructor
extern void (*g_fnCsBodyDtor)(void* pThis);
// 0x141791990 — the free CSyndicate reaches through its one-time heap guard
extern void (*g_fnCsFree)(void* pThis);
// 0x1417f2fdc — the free CToken reaches (already declared as g_pfnCSynManagerDelete)
extern void (*g_fnCsFree2)(void* pThis);
// 0x1417ebf80 — the target of the concubines thunk
extern void (*g_fnPbEBF80)(void);

void* SynCsDeletingDtor(void* pThis, uint32_t uFlags);      // 0x1417a2890
void* SynTokenDeletingDtor(void* pThis, uint32_t uFlags);   // 0x1417d5090
void SynConcubinesThunk(void);                              // 0x1417ec100

// the vtable CSyndicate's slot writes and the one the token slot stamps back
extern const uintptr_t kSynCtokenVft;   // 0x14183be50

}  // namespace tq

#endif  // SYNDICATE_SYNCLASSDTORS_H
