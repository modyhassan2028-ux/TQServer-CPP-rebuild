// synlibdtors.cpp — see synlibdtors.h
#include "modules/syndicate/src/synlibdtors.h"

namespace tq {

void (*g_fnLibStrDtor)(void*) = nullptr;
void (*g_fnLibExcDtor)(void*) = nullptr;
void (*g_fnLibFree)(void*) = nullptr;
void (*g_fnLibFreeSized)(void*, uint32_t, uint32_t, void*) = nullptr;
void (*g_fnLibTypeInfoFinish)(void) = nullptr;
const char* (*g_fnLibExcWhat)(void*) = nullptr;

const uintptr_t kSynVftLogicError = 0x141824a60ULL;
const uintptr_t kSynVftLengthError = 0x141824b00ULL;
const uintptr_t kSynVftOutOfRange = 0x141824ba0ULL;
const uintptr_t kSynVftBadAlloc = 0x141824c40ULL;
const uintptr_t kSynVftCString = 0x141824cf0ULL;

// 0x141721090
const char* SynLibWhat(void* pExc) {
    uint8_t* p = (uint8_t*)pExc;
    // 141721090 cmp [rcx+0x38],0x10 ; jb ; 141721097 mov rax,[rcx+0x20] ; else lea rax,[rcx+0x20]
    if (*(uint64_t*)(p + 0x38) < 0x10) {
        return (const char*)(p + 0x20);
    }
    return *(const char**)(p + 0x20);
}

namespace {

// the shape shared by logic_error, length_error and out_of_range: std::string at +0x18,
// then std::exception, then the optional free
void* ErrorFamilyDtor(void* pThis, uint32_t uFlags, uintptr_t uOwnVft, bool bOwnVft) {
    uint8_t* p = (uint8_t*)pThis;
    if (bOwnVft) {
        *(uintptr_t*)p = uOwnVft;      // 1417211dd / 1417212fd — the class's own table
    }
    *(uintptr_t*)p = kSynVftLogicError;             // the base table, always stamped last
    g_fnLibStrDtor(p + 0x18);                       // 1417210db / ... call [0x141823290]
    g_fnLibExcDtor(p);                              // 1417210e5 call [0x141823400]
    if ((uFlags & 1) != 0) {
        g_fnLibFree(p);
    }
    return pThis;
}

}  // namespace

// 0x1417210b0 — logic_error stores only its own table before the base one
void* SynLibLogicErrorDtor(void* pThis, uint32_t uFlags) {
    return ErrorFamilyDtor(pThis, uFlags, kSynVftLogicError, true);
}

// 0x1417211c0 — length_error stores 0x141824b00 and then the base table
void* SynLibLengthErrorDtor(void* pThis, uint32_t uFlags) {
    return ErrorFamilyDtor(pThis, uFlags, kSynVftLengthError, true);
}

// 0x1417212e0 — out_of_range stores 0x141824ba0 and then the base table
void* SynLibOutOfRangeDtor(void* pThis, uint32_t uFlags) {
    return ErrorFamilyDtor(pThis, uFlags, kSynVftOutOfRange, true);
}

// 0x141721450 — bad_alloc has no std::string member at all
void* SynLibBadAllocDtor(void* pThis, uint32_t uFlags) {
    uint8_t* p = (uint8_t*)pThis;
    *(uintptr_t*)p = kSynVftBadAlloc;   // 14172146d
    g_fnLibExcDtor(p);                  // 141721477
    if ((uFlags & 1) != 0) {            // 14172147d test bl,0x1
        g_fnLibFree(p);                 // 141721485
    }
    return pThis;
}

// 0x141721690 — the CString destructor of this binary, string at +8
void* SynLibCStringDtor(void* pThis, uint32_t uFlags) {
    uint8_t* p = (uint8_t*)pThis;
    *(uintptr_t*)p = kSynVftCString;    // 1417216ad
    g_fnLibStrDtor(p + 0x08);           // 1417216bb add rcx,0x8 ; call [0x141823290]
    if ((uFlags & 1) != 0) {            // 1417216c1
        g_fnLibFree(p);                 // 1417216c9
    }
    return pThis;
}

// 0x1417f2f6c — type_info: bit 1 takes the sized-free path, bit 0 the plain one, and the
// object handed back is this-8 on both of them
void* SynLibTypeInfoDtor(void* pThis, uint32_t uFlags) {
    uint8_t* p = (uint8_t*)pThis;
    if ((uFlags & 2) != 0) {
        uint32_t uSize = *(uint32_t*)(p - 0x08);     // 1417f2f85 mov r8d,[rcx-0x8]
        g_fnLibFreeSized((void*)p, 0x18, uSize, (void*)0x1417f3b9cULL);
        if ((uFlags & 1) != 0) {
            g_fnLibFree((void*)(p - 0x08));          // 1417f2fa0 lea rcx,[rbx-0x8]
        }
        return (void*)(p - 0x08);                    // 1417f2fa9
    }
    g_fnLibTypeInfoFinish();                          // 1417f2faf call 0x1417f3b9c
    if ((uFlags & 1) != 0) {
        g_fnLibFree((void*)p);                        // 1417f2fba
    }
    return (void*)p;                                  // 1417f2fc2
}

// 0x1417f2fe8 — a pure thunk into MSVCR90
const char* SynLibExcWhatThunk(void* pExc) {
    return g_fnLibExcWhat(pExc);                      // jmp [0x1418233e0]
}

}  // namespace tq
