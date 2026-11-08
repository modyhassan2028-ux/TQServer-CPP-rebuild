// ============================================================================
// SyndicateDtorFamily.h — the nine vtable classes the port had not named yet.
//
// Every one of these classes was found the same way: the RTTI chain in the image
// (type descriptor -> complete object locator -> the word before slot 0) resolves
// a vtable base, and no hand-written file had ever mentioned that base. Their
// slots turn out to be almost entirely deleting destructors, which is why nothing
// had reason to name them.
//
//   class                 vtable base   slots
//   CCrossMeritMgr        0x141828048   0x14173f950
//   CLeague               0x141829550   0x14174d8d0
//   CLeagueMgr            0x14182d008   0x141775df0
//   CopyingInputStream    0x141840d48   0x1417e7a50, 0x1417f3374 (purecall), 0x1417e6900
//   CopyingOutputStream   0x141840d98   0x1417e7ad0, 0x1417f3374 (purecall)
//   FatalException        0x14183f6c0   0x1417e1760, 0x1417e1430
//   ISynMngModify         0x141839f98   0x1417f3374 (purecall)
//   Thank_you             0x141842df8   0x1417f3bc0  (`c2 00 00` = ret 0, an empty slot)
//   type_info             0x1418429d0   0x1417f2f6c
//
// Shape proved by the bodies themselves: every deleting destructor in this family
// is the same three steps in the same order —
//     run the class destructor, then `if (flags & 1)` release the object, return `this`.
// The release goes through the import thunk at 0x1417f2fdc (three `jmp [rip+x]`
// instructions in a row at 0x1417f2fdc/2fe2/2fe8, so it is an import, not a body);
// the image's IAT is unbound here, so the imported name is NOT proven and the seam
// is named for its address rather than invented.
//
// 0x1417f3374 resolves to the purecall thunk (already documented by iprovider.h and
// module.cpp), which is why four of these classes hold it: their interfaces declare
// virtuals they never define.
//
// CopyingInputStream's third slot 0x1417e6900 was held back until its callees were
// proven; both now are:
//   0x1417e7c40  `mov rax,[rsp+8] / mov eax,[rax]`            -> reads the int it is given
//   0x1417e5aa0  returns whichever of two int* holds the smaller value (ties -> arg1);
//                0x1417e6900 only ever reads that result, so it is the min of the two
//   [rax+8]      the object's own vtable slot 1, called as (this, buffer, length)
// The loop reads `min(0x1000, count - total)` bytes at a time and stops when a read
// returns <= 0, so the slot is protobuf io::CopyingInputStream::Skip. The method name
// is taken from that interface's shape and the proven behaviour, not from a symbol.
// ============================================================================
#ifndef SYNDICATE_DTOR_FAMILY_H
#define SYNDICATE_DTOR_FAMILY_H

#include <cstddef>
#include <cstdint>

namespace tq {

// --- seams -------------------------------------------------------------------
// 0x1417f2fdc: import thunk used for `if (flags & 1)` release, and by
//              CCrossMeritMgr for the pointer it owns at +0x8.
extern void (*g_pfnSyRelease)(void* p);              // 0x1417f2fdc
// 0x1418231f0: import slot FatalException's second slot jumps to (unbound IAT).
extern void (*g_pfnSyFatalBaseDtor)(void* p);        // 0x1418231f0
// class destructors these slots call before releasing
extern void (*g_pfnCCrossMeritMgrDtor)(void* self);  // 0x14173ecf0, called with self+0x8
extern void (*g_pfnCLeagueDtor)(void* self);         // 0x14174cfc0
extern void (*g_pfnCLeagueMgrDtor)(void* self);      // 0x141775800
extern void (*g_pfnCopyingInputStreamDtor)(void* self);   // 0x1417e68e0
extern void (*g_pfnCopyingOutputStreamDtor)(void* self);  // 0x1417e7280
extern void (*g_pfnFatalExceptionDtor)(void* self);  // 0x1417e13e0
// type_info's two callees
extern void (*g_pfnTypeInfoBaseDtor)(void* self);    // 0x1417f3b9c
extern void (*g_pfnTypeInfoDestroy)(void* self, unsigned size, unsigned data, const void* name); // 0x1417f32ac
// 0x1417e5aa0: pointer to whichever int is smaller, ties to the first argument.
extern int* (*g_pfnSySmallerOf)(int* a, int* b);

struct CCrossMeritMgr {
    void*   vft;        // +0x00, set to 0x141828048 by the destructor
    void*   owned;      // +0x08, destroyed then released
};

struct CLeague      { void* vft; };   // vtable base 0x141829550
struct CLeagueMgr   { void* vft; };   // vtable base 0x14182d008
struct CopyingInputStream  { void* vft; };   // vtable base 0x141840d48
struct CopyingOutputStream { void* vft; };   // vtable base 0x141840d98

struct FatalException {
    void* vft;          // +0x00, vtable base 0x14183f6c0
    // +0x28 is the sub-object whose destructor the second slot tail-calls
};

// MSVC type_info: the object passed to the deleting destructor points at the vftable
// word, and the allocation starts 8 bytes before it (`this - 8` in the body).
struct TypeInfo {
    void*   vft;        // +0x00
    void*   name;       // +0x08
    // the body reads a 32-bit field at `this - 8` and passes it as the destroy size
};

// --- the ported slots -------------------------------------------------------
void* CCrossMeritMgr_ScalarDeletingDtor(CCrossMeritMgr* self, unsigned flags);   // 0x14173f950
void* CLeague_ScalarDeletingDtor(CLeague* self, unsigned flags);                 // 0x14174d8d0
void* CLeagueMgr_ScalarDeletingDtor(CLeagueMgr* self, unsigned flags);           // 0x141775df0
void* CopyingInputStream_ScalarDeletingDtor(CopyingInputStream* self, unsigned flags);   // 0x1417e7a50
void* CopyingOutputStream_ScalarDeletingDtor(CopyingOutputStream* self, unsigned flags); // 0x1417e7ad0
void* FatalException_ScalarDeletingDtor(FatalException* self, unsigned flags);   // 0x1417e1760
void  FatalException_BaseDtor(FatalException* self);                             // 0x1417e1430
void* TypeInfo_ScalarDeletingDtor(TypeInfo* self, unsigned flags);               // 0x1417f2f6c
void  ThankYou_EmptySlot(void* self);                                            // 0x1417f3bc0
int   CopyingInputStream_Skip(CopyingInputStream* self, int count);              // 0x1417e6900

}  // namespace tq

#endif  // SYNDICATE_DTOR_FAMILY_H
