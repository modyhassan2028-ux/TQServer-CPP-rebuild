// synpioctors.cpp — see synpioctors.h
#include "modules/syndicate/src/synpioctors.h"

namespace tq {

void (*g_fnCtorBase7960)(void*) = nullptr;
void (*g_fnCtorBase78C0)(void*) = nullptr;
void (*g_fnCtorMember7B50)(void*, void*) = nullptr;
int32_t (*g_fnCtorAvail)(void*) = nullptr;
void (*g_fnCtorStrResize)(void*, int64_t) = nullptr;
void* (*g_fnCtorStrData)(void*) = nullptr;
void* (*g_fnCtorCopy)(void*, void*, int64_t) = nullptr;
void (*g_fnCtorAdvance)(void*, int32_t) = nullptr;
bool (*g_fnCtorSlowRead)(void*, void*, int32_t) = nullptr;

const uintptr_t kSynVftArrayOut = 0x141840ca0ULL;
const uintptr_t kSynVftCopyInAdaptor = 0x141840d68ULL;
const uintptr_t kSynVftCopyOutAdaptor = 0x141840db0ULL;

// 0x1417e6070 — ArrayOutputStream(void* buffer, int size, int block_size)
void* SynCtorArrayOut(void* pThis, void* pBuffer, int32_t nSize, int32_t nBlock) {
    uint8_t* p = (uint8_t*)pThis;
    g_fnCtorBase7960(pThis);                        // 1417e6081 call 0x1417e7960
    *(uintptr_t*)p = kSynVftArrayOut;               // 1417e60a1 lea rax,[0x141840ca0] ; store
    *(void**)(p + 0x08) = pBuffer;                  // 1417e60bd
    *(int32_t*)(p + 0x10) = nSize;                  // 1417e60c9
    // 1417e60d0 cmp block,0 ; jle ; else the block size, otherwise the size
    *(int32_t*)(p + 0x14) = (nBlock > 0) ? nBlock : nSize;
    *(int32_t*)(p + 0x18) = 0;                      // 1417e60ee
    *(int32_t*)(p + 0x1c) = 0;                      // 1417e60f9
    return pThis;                                   // 1417e6103 mov rax,this
}

// 0x1417e6a00 — CopyingInputStreamAdaptor(CopyingInputStream* input, int block_size)
void* SynCtorCopyInAdaptor(void* pThis, void* pInput, int32_t nBlock) {
    uint8_t* p = (uint8_t*)pThis;
    g_fnCtorBase78C0(pThis);                        // 1417e6a16
    *(uintptr_t*)p = kSynVftCopyInAdaptor;          // 1417e6a2c
    *(void**)(p + 0x08) = pInput;                   // 1417e6a48
    p[0x10] = 0;                                    // 1417e6a54
    p[0x11] = 0;                                    // 1417e6a5f
    *(uint64_t*)(p + 0x18) = 0;                     // 1417e6a6b
    g_fnCtorMember7B50(p + 0x20, nullptr);          // 1417e6a77 add rcx,0x20 ; xor edx,edx
    // 1417e6a80 cmp block,0 ; jle -> 0x2000
    *(int32_t*)(p + 0x28) = (nBlock > 0) ? nBlock : 0x2000;
    *(int32_t*)(p + 0x2c) = 0;                      // 1417e6aa7
    *(int32_t*)(p + 0x30) = 0;                      // 1417e6ab2
    return pThis;                                   // 1417e6abc
}

// 0x1417e72a0 — CopyingOutputStreamAdaptor(CopyingOutputStream* output, int block_size)
void* SynCtorCopyOutAdaptor(void* pThis, void* pOutput, int32_t nBlock) {
    uint8_t* p = (uint8_t*)pThis;
    g_fnCtorBase7960(pThis);                        // 1417e72b6 — the same base as ArrayOutputStream
    *(uintptr_t*)p = kSynVftCopyOutAdaptor;         // 1417e72cc
    *(void**)(p + 0x08) = pOutput;                  // 1417e72e8
    p[0x10] = 0;                                    // 1417e72f4
    p[0x11] = 0;                                    // 1417e72ff
    *(uint64_t*)(p + 0x18) = 0;                     // 1417e730b
    g_fnCtorMember7B50(p + 0x20, nullptr);          // 1417e7317
    *(int32_t*)(p + 0x28) = (nBlock > 0) ? nBlock : 0x2000;
    *(int32_t*)(p + 0x2c) = 0;                      // 1417e7347
    return pThis;                                   // 1417e7351 — no +0x30 store here
}

// 0x1417e51c0
void* SynReadLe64(const void* pBuffer, uint64_t* pValue) {
    const uint8_t* b = (const uint8_t*)pBuffer;
    // the two 32-bit halves are assembled separately, then the high one is shifted by 32
    uint32_t nLo = (uint32_t)b[0] | ((uint32_t)b[1] << 8) | ((uint32_t)b[2] << 16) |
                   ((uint32_t)b[3] << 24);
    uint32_t nHi = (uint32_t)b[4] | ((uint32_t)b[5] << 8) | ((uint32_t)b[6] << 16) |
                   ((uint32_t)b[7] << 24);
    *pValue = (uint64_t)nLo | ((uint64_t)nHi << 32);
    return (void*)(b + 8);                          // 1417e5290 add rax,0x8
}

// 0x1417e50d0
bool SynReadString(void* pThis, void* pOut, int32_t nCount) {
    uint8_t* p = (uint8_t*)pThis;
    if (nCount < 0) return false;                   // 1417e50e5 jge ; xor al,al
    // 1417e50f7 call 0x1417e4fb0 ; cmp eax,count ; jl -> the slow path
    if (g_fnCtorAvail(pThis) < nCount) {
        return g_fnCtorSlowRead(pThis, pOut, nCount);   // 1417e5155 call 0x1417e3790
    }
    g_fnCtorStrResize(pOut, (int64_t)nCount);       // 1417e510a call 0x1417dffb0
    if (nCount > 0) {                               // 1417e5115 jle
        g_fnCtorCopy(g_fnCtorStrData(pOut), *(void**)(p + 0x08), (int64_t)nCount);
        g_fnCtorAdvance(pThis, nCount);             // 1417e5147
    }
    return true;                                    // 1417e514f mov al,1
}

}  // namespace tq
