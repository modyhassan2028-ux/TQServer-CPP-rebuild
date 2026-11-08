// ============================================================================
// SyndicateDtorFamily.cpp — instruction-by-instruction transcription of the nine
// class slots listed in the header. Each function keeps the original order of
// effects: destructor first, release second, only when `flags & 1`.
// ============================================================================
#include "SyndicateDtorFamily.h"

namespace tq {

static void noop_release(void*) {}
static void noop_dtor(void*) {}
static void noop_typeinfo_destroy(void*, unsigned, unsigned, const void*) {}

void (*g_pfnSyRelease)(void*) = noop_release;                       // 0x1417f2fdc
void (*g_pfnSyFatalBaseDtor)(void*) = noop_release;                 // 0x1418231f0
void (*g_pfnCCrossMeritMgrDtor)(void*) = noop_dtor;                 // 0x14173ecf0
void (*g_pfnCLeagueDtor)(void*) = noop_dtor;                        // 0x14174cfc0
void (*g_pfnCLeagueMgrDtor)(void*) = noop_dtor;                     // 0x141775800
void (*g_pfnCopyingInputStreamDtor)(void*) = noop_dtor;             // 0x1417e68e0
void (*g_pfnCopyingOutputStreamDtor)(void*) = noop_dtor;            // 0x1417e7280
void (*g_pfnFatalExceptionDtor)(void*) = noop_dtor;                 // 0x1417e13e0
void (*g_pfnTypeInfoBaseDtor)(void*) = noop_dtor;                   // 0x1417f3b9c
void (*g_pfnTypeInfoDestroy)(void*, unsigned, unsigned, const void*) = noop_typeinfo_destroy;  // 0x1417f32ac

// 0x1417e5aa0
//   mov rcx,[rsp+0x28] / mov rax,[rsp+0x20]     ; arg2, arg1
//   cmp [rcx],eax ...                           ; *arg1 - *arg2
//   sf == of  -> return arg1 (arg1 <= arg2), else arg2
static int* smaller_of(int* a, int* b) { return (*b >= *a) ? a : b; }   // ties go to `a`
int* (*g_pfnSySmallerOf)(int*, int*) = smaller_of;

// 0x14173f950
//   mov [rcx],0x141828048        ; refresh its own vftable
//   lea rbx,[rcx+8] / mov rcx,rbx / call 0x14173ecf0
//   mov rcx,[rbx] / call 0x1417f2fdc
//   test al,1 / jz skip / mov rcx,rsi / call 0x1417f2fdc
//   mov rax,rsi
void* CCrossMeritMgr_ScalarDeletingDtor(CCrossMeritMgr* self, unsigned flags) {
    self->vft = (void*)(uintptr_t)0x141828048;
    g_pfnCCrossMeritMgrDtor((uint8_t*)self + 0x8);
    g_pfnSyRelease(*(void**)((uint8_t*)self + 0x8));
    if (flags & 1u)
        g_pfnSyRelease(self);
    return self;
}

// 0x14174d8d0 / 0x141775df0 / 0x1417e7a50 / 0x1417e7ad0 / 0x1417e1760
//   mov edi,ecx / mov ebx,edx / call <class dtor>
//   test bl,1 / jz skip / mov rcx,rdi / call 0x1417f2fdc
//   mov rax,rdi
#define SY_DELETING_DTOR(NAME, TYPE, DTOR_FN)                                  \
    void* NAME(TYPE* self, unsigned flags) {                                   \
        DTOR_FN(self);                                                         \
        if (flags & 1u)                                                        \
            g_pfnSyRelease(self);                                              \
        return self;                                                           \
    }

SY_DELETING_DTOR(CLeague_ScalarDeletingDtor, CLeague, g_pfnCLeagueDtor)
SY_DELETING_DTOR(CLeagueMgr_ScalarDeletingDtor, CLeagueMgr, g_pfnCLeagueMgrDtor)
SY_DELETING_DTOR(CopyingInputStream_ScalarDeletingDtor, CopyingInputStream, g_pfnCopyingInputStreamDtor)
SY_DELETING_DTOR(CopyingOutputStream_ScalarDeletingDtor, CopyingOutputStream, g_pfnCopyingOutputStreamDtor)
SY_DELETING_DTOR(FatalException_ScalarDeletingDtor, FatalException, g_pfnFatalExceptionDtor)
#undef SY_DELETING_DTOR

// 0x1417e1430 — eight instructions, no stack frame of its own:
//   add rcx,0x28 / jmp [0x1418231f0]
// so it destroys the sub-object at +0x28 through an import, never returning to here.
void FatalException_BaseDtor(FatalException* self) {
    g_pfnSyFatalBaseDtor((uint8_t*)self + 0x28);
}

// 0x1417f2f6c — MSVC type_info deleting destructor.
//   mov rsi,rdx / mov rbx,rcx
//   test dl,2 / jz L18
//   mov r8d,[rcx-8] / mov r9,0x1417f3b9c / mov edx,0x18 / call 0x1417f32ac
//   test sil,1 / jz L16 / lea rcx,[rbx-8] / call 0x1417f2fdc
//   L16: lea rax,[rbx-8] / jmp L24
//   L18: call 0x1417f3b9c            ; base destructor on `this`
//        test sil,1 / jz L23 / mov rcx,rbx / call 0x1417f2fdc
//   L23: mov rax,rbx
//   L24: ...
// Note the two arms return different addresses: the flags&2 arm returns `this - 8`,
// the other returns `this`. The original does that; it is preserved.
void* TypeInfo_ScalarDeletingDtor(TypeInfo* self, unsigned flags) {
    if (flags & 2u) {
        unsigned size = *(uint32_t*)((uint8_t*)self - 0x8);
        g_pfnTypeInfoDestroy((uint8_t*)self - 0x8, 0x18u, size, (const void*)(uintptr_t)0x1417f3b9c);
        if (flags & 1u)
            g_pfnSyRelease((uint8_t*)self - 0x8);
        return (uint8_t*)self - 0x8;
    }
    g_pfnTypeInfoBaseDtor(self);
    if (flags & 1u)
        g_pfnSyRelease(self);
    return self;
}

// 0x1417e6900 — CopyingInputStream::Skip
//   sub rsp,0x1058 (0x1000-byte buffer at rsp+0x30, stack cookie at rsp+0x1048)
//   L9: cmp total,count / jns L40
//       mov dword [rsp+0x1038],0x1000 / call 0x1417e7c40   ; avail = 0x1000
//       eax = count - total / call 0x1417e5aa0             ; &min(avail, remaining)
//       r8d = (int)*that / rdx = buffer / rcx = this / call [vft+8]
//       got = eax ; if (got != 0 && got > 0) goto L35 ; else return total
//   L35: total += got / jmp L9
//   L40: return total
// The buffer is read into and never inspected: the bytes are discarded, which is what
// makes this Skip rather than Read. A read of exactly 0 ends the loop, so a stream that
// returns 0 early leaves `total` short, and a negative count returns 0 without reading.
int CopyingInputStream_Skip(CopyingInputStream* self, int count) {
    char buffer[0x1000];
    int total = 0;
    while (total < count) {
        int avail = 0x1000;
        int remaining = count - total;
        int* limit = g_pfnSySmallerOf(&avail, &remaining);
        int got = ((int (*)(void*, void*, int))(*(void***)self)[1])(self, buffer, *limit);
        if (!(got != 0 && got > 0))
            break;
        total += got;
    }
    return total;
}

// 0x1417f3bc0 — three bytes, `c2 00 00`: an empty slot that returns to its caller.
void ThankYou_EmptySlot(void* /*self*/) {}

}  // namespace tq
