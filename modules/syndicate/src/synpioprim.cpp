// synpioprim.cpp — see synpioprim.h
#include "modules/syndicate/src/synpioprim.h"

namespace tq {

void (*g_fnPrimRelease)(void*) = nullptr;
void* (*g_fnPrimAlloc)(int64_t) = nullptr;
void (*g_fnPrimReset)(void*) = nullptr;

// 0x1417e7d50
void SynZeroInDtorBody(void* pThis) {
    *(uintptr_t*)pThis = 0x141840c70ULL;    // lea rax,[rip+0x58f0f] = 0x141840c70
}

// 0x1417e7d70
void SynZeroOutDtorBody(void* pThis) {
    *(uintptr_t*)pThis = 0x141840cd8ULL;    // lea rax,[rip+0x58f57] = 0x141840cd8
}

// 0x1417e7bf0
void* SynHolderGet(void* pThis) {
    return *(void**)pThis;                  // mov rax,[rax]
}

// 0x1417e7c40
int32_t SynProbeInt(void* pThis) {
    return *(int32_t*)pThis;                // mov eax,[rax]
}

// 0x1417e4fb0
int32_t SynReaderAvail(void* pThis) {
    uint8_t* p = (uint8_t*)pThis;
    // 1417e4fb0 rcx = [this+0x8] ; rax = [this+0x10] ; sub rax,rcx
    return (int32_t)((uintptr_t)*(void**)(p + 0x10) - (uintptr_t)*(void**)(p + 0x08));
}

// 0x1417e50a0
void SynReaderAdvance(void* pThis, int32_t nCount) {
    uint8_t* p = (uint8_t*)pThis;
    // 1417e50a0 movsxd rcx,count ; add rcx,[this+0x8] ; store
    *(void**)(p + 0x08) = (void*)((uint8_t*)*(void**)(p + 0x08) + (int64_t)nCount);
}

// 0x1417e5aa0
int32_t* SynClampMin(int32_t* pA, int32_t* pB) {
    // 1417e5aa0 eax = *pA ; cmp *pB,eax ; jge -> pA ; otherwise pB
    return (*pB < *pA) ? pB : pA;
}

// 0x1417e7ba0
void SynHolderSet(void* pHolder, void* pValue) {
    uint8_t* p = (uint8_t*)pHolder;
    // 1417e7ba0 cmp [rsp+0x48],rax([this]) ; je -> nothing
    if (*(void**)p == pValue) return;
    void* pOld = *(void**)p;                // 1417e7bb0
    g_fnPrimRelease(pOld);                  // 1417e7bc0 call 0x1417f37de
    *(void**)p = pValue;                    // 1417e7bd2 mov [rcx],rax
}

// 0x1417e7830
void SynAllocateBuffer(void* pThis) {
    uint8_t* p = (uint8_t*)pThis;
    // 1417e7830 add rcx,0x20 ; xor edx,edx ; call 0x1417e7c00  -> "holder == null"
    if (*(void**)(p + 0x20) == nullptr) {
        // 1417e7856 movsxd rcx,[this+0x28] ; call 0x1417f2f14
        void* pBlock = g_fnPrimAlloc((int64_t)*(int32_t*)(p + 0x28));
        // 1417e7867 add rcx,0x20 ; rdx = block ; call 0x1417e7ba0
        SynHolderSet(p + 0x20, pBlock);
    }
}

// 0x1417e7770
bool SynOutAdaptorFlush(void* pThis) {
    uint8_t* p = (uint8_t*)pThis;
    if (p[0x11] != 0) return false;         // 1417e777e test ; xor al,al
    if (*(int32_t*)(p + 0x2c) == 0) return true;   // 1417e7792 jne ; else mov al,1
    // 1417e779c..1417e77cb stream vt[1](stream, buffer(+0x20), +0x2c)
    void* pStream = *(void**)(p + 0x08);
    void* pBuf = *(void**)(p + 0x20);
    int32_t nUsed = *(int32_t*)(p + 0x2c);
    bool bOk = ((bool (*)(void*, void*, int32_t))(*(void***)pStream)[1])(pStream, pBuf, nUsed);
    if (bOk) {
        // 1417e77db..1417e77f6: byte_count_ += used ; used = 0
        *(int64_t*)(p + 0x18) = *(int64_t*)(p + 0x18) + (int64_t)*(int32_t*)(p + 0x2c);
        *(int32_t*)(p + 0x2c) = 0;
        return true;
    }
    // 1417e7803..1417e7811: mark the failure and reset
    p[0x11] = 1;
    g_fnPrimReset(pThis);
    return false;
}

}  // namespace tq
