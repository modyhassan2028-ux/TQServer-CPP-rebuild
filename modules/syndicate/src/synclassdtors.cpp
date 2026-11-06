// synclassdtors.cpp — see synclassdtors.h
#include "modules/syndicate/src/synclassdtors.h"

namespace tq {

void (*g_fnCsBodyDtor)(void*) = nullptr;
void (*g_fnCsFree)(void*) = nullptr;
void (*g_fnCsFree2)(void*) = nullptr;
void (*g_fnPbEBF80)(void) = nullptr;

const uintptr_t kSynCtokenVft = 0x14183be50ULL;

// 0x1417a2890
void* SynCsDeletingDtor(void* pThis, uint32_t uFlags) {
    g_fnCsBodyDtor(pThis);              // 1417a289f call 0x1417a1bf0
    if ((uFlags & 1) != 0) {            // 1417a28a4 test bl,0x1 ; je
        g_fnCsFree(pThis);              // 1417a28ac call 0x141791990
    }
    return pThis;                       // 1417a28b1 mov rax,rdi
}

// 0x1417d5090
void* SynTokenDeletingDtor(void* pThis, uint32_t uFlags) {
    *(uintptr_t*)pThis = kSynCtokenVft;         // 1417d5096 lea rax,[0x14183be50] ; store
    if ((uFlags & 1) != 0) {                    // 1417d50a3 test dl,0x1 ; je
        g_fnCsFree2(pThis);                     // 1417d50a8 call 0x1417f2fdc
    }
    return pThis;                               // 1417d50ad mov rax,rbx
}

// 0x1417ec100
void SynConcubinesThunk(void) {
    g_fnPbEBF80();                      // 1417ec100 jmp 0x1417ebf80
}

}  // namespace tq
