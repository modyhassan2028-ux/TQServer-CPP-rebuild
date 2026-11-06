// ============================================================================
// synlibdtors.h — RAW Syndicate.dll v6159 · the last rows of six library classes the RTTI
//   scan reports as incomplete. Every body is a scalar deleting destructor: stamp the
//   vtable, destroy the bases, free only when bit 0 of the flags is set, return this.
//   0x141721090  the shared what()  -> (cap at +0x38 < 0x10) ? this+0x20 : *(char**)this+0x20
//   0x1417210b0  std::logic_error        vt 0x141824a60 (one store)
//   0x1417211c0  std::length_error       vt 0x141824b00 THEN 0x141824a60 (two stores)
//   0x1417212e0  std::out_of_range       vt 0x141824ba0 THEN 0x141824a60 (two stores)
//   0x141721450  std::bad_alloc          vt 0x141824c40, no std::string member
//   0x141721690  tq::CString             vt 0x141824cf0, std::string at +8 (not +0x18)
//   0x1417f2f6c  type_info               a different shape: bit 1 frees alongside the object
//   0x1417f2fe8  a thunk: jmp MSVCR90 std::exception::what (IAT 0x1418233e0)
//   The three lower destructors destroy std::string at +0x18 (MSVCP90 0x141823290) and then
//   std::exception (MSVCR90 0x141823400); bad_alloc skips the string; CString destroys at +8.
// ============================================================================
#ifndef SYNDICATE_SYNLIBDTORS_H
#define SYNDICATE_SYNLIBDTORS_H

#include <cstdint>

namespace tq {

// MSVCP90 std::string::~string
extern void (*g_fnLibStrDtor)(void* pStr);
// MSVCR90 std::exception::~exception
extern void (*g_fnLibExcDtor)(void* pExc);
// 0x1417f2fdc — the free every one of these reaches
extern void (*g_fnLibFree)(void* p);
// 0x1417f32ac — the sized free type_info uses on the bit-1 path
extern void (*g_fnLibFreeSized)(void* p, uint32_t uFlags, uint32_t uSize, void* pFn);
// 0x1417f3b9c — type_info's own finisher
extern void (*g_fnLibTypeInfoFinish)(void);
// 0x1418233e0 — MSVCR90 std::exception::what, behind the 0x1417f2fe8 thunk
extern const char* (*g_fnLibExcWhat)(void* pExc);

const char* SynLibWhat(void* pExc);                        // 0x141721090
void* SynLibLogicErrorDtor(void* pThis, uint32_t uFlags);  // 0x1417210b0
void* SynLibLengthErrorDtor(void* pThis, uint32_t uFlags); // 0x1417211c0
void* SynLibOutOfRangeDtor(void* pThis, uint32_t uFlags);  // 0x1417212e0
void* SynLibBadAllocDtor(void* pThis, uint32_t uFlags);    // 0x141721450
void* SynLibCStringDtor(void* pThis, uint32_t uFlags);     // 0x141721690
void* SynLibTypeInfoDtor(void* pThis, uint32_t uFlags);    // 0x1417f2f6c
const char* SynLibExcWhatThunk(void* pExc);                // 0x1417f2fe8

extern const uintptr_t kSynVftLogicError;   // 0x141824a60
extern const uintptr_t kSynVftLengthError;  // 0x141824b00
extern const uintptr_t kSynVftOutOfRange;   // 0x141824ba0
extern const uintptr_t kSynVftBadAlloc;     // 0x141824c40
extern const uintptr_t kSynVftCString;      // 0x141824cf0

}  // namespace tq

#endif  // SYNDICATE_SYNLIBDTORS_H
