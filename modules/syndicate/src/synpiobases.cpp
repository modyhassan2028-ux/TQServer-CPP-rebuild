// synpiobases.cpp — see synpiobases.h
#include "modules/syndicate/src/synpiobases.h"

namespace tq {

void (*g_fnBaseZeroOutDtor)(void*) = nullptr;
void (*g_fnBaseZeroInDtor)(void*) = nullptr;
bool (*g_fnBaseFlush)(void*) = nullptr;
void (*g_fnBaseHolderDtor)(void*) = nullptr;

const uintptr_t kSynVftZeroOut = 0x141840cd8ULL;
const uintptr_t kSynVftZeroIn = 0x141840c70ULL;
const uintptr_t kSynVftStringOut = 0x141840d10ULL;

// 0x1417e7960
void* SynZeroOutCtor(void* pThis) {
    *(uintptr_t*)pThis = kSynVftZeroOut;   // lea rax,[0x141840cd8] ; store
    return pThis;                          // mov rax,this
}

// 0x1417e78c0
void* SynZeroInCtor(void* pThis) {
    *(uintptr_t*)pThis = kSynVftZeroIn;    // lea rax,[0x141840c70] ; store
    return pThis;
}

// 0x1417e7b50
void* SynHolderAssign(void* pThis, void* pVft) {
    *(void**)pThis = pVft;                 // mov rax,[rsp+0x10] ; mov [rcx],rax
    return pThis;
}

// 0x1417e6120
void SynArrayOutBodyDtor(void* pThis) {
    *(uintptr_t*)pThis = 0x141840ca0ULL;   // 1417e6129 lea rax,[0x141840ca0]
    g_fnBaseZeroOutDtor(pThis);            // 1417e6134 call 0x1417e7d70
}

// 0x1417e6510
void SynStringOutBodyDtor(void* pThis) {
    *(uintptr_t*)pThis = kSynVftStringOut;  // 1417e6519 lea rax,[0x141840d10]
    g_fnBaseZeroOutDtor(pThis);             // 1417e6524 call 0x1417e7d70
}

// 0x1417e7360
void SynCopyOutAdaptorBodyDtor(void* pThis) {
    uint8_t* p = (uint8_t*)pThis;
    *(uintptr_t*)p = kSynVftCopyOutAdaptor;      // 1417e7369 lea rax,[0x141840db0]
    g_fnBaseFlush(pThis);                        // 1417e7384 call 0x1417e7770
    // 1417e738b movzx eax,[this+0x10] ; test ; je -> skip the destroy
    if (p[0x10] != 0) {
        void* pStream = *(void**)(p + 0x08);     // 1417e739f
        if (pStream != nullptr) {
            // 1417e73bc edx = 1 ; rcx = stream ; call [stream vft + 0]
            ((void* (*)(void*, uint32_t))(*(void***)pStream)[0])(pStream, 1);
        }
    }
    g_fnBaseHolderDtor(p + 0x20);                // 1417e73e0 add rcx,0x20 ; call 0x1417e7b70
    g_fnBaseZeroOutDtor(pThis);                  // 1417e73f0 call 0x1417e7d70
}

}  // namespace tq
