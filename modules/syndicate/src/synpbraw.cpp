// synpbraw.cpp — see synpbraw.h
#include "modules/syndicate/src/synpbraw.h"

namespace tq {

void (*g_fnRawConsume)(void*, int32_t) = nullptr;
bool (*g_fnRawAppend)(void*, const void*, int32_t) = nullptr;
void* (*g_fnRawLe32)(uint32_t, void*) = nullptr;
void* (*g_fnRawLe64)(uint64_t, void*) = nullptr;
void* (*g_fnRawVarint)(uint64_t, void*) = nullptr;

// 0x1417e47d0
void SynOutWriteRaw(void* pThis, const void* pData, int32_t nCount) {
    uint8_t* p = (uint8_t*)pThis;
    // 1417e47d0 eax = [this+0x10] ; cmp count,eax ; jge -> the flush path
    if (nCount < *(int32_t*)(p + 0x10)) {
        g_fnRawAppend(pThis, pData, nCount);        // 1417e47f5 call 0x1417e46e0
        return;
    }
    if (*(int32_t*)(p + 0x10) > 0) {                // 1417e480a jle
        void* pStream = *(void**)(p);
        int32_t nSize = *(int32_t*)(p + 0x10);
        ((void (*)(void*, int32_t))(*(void***)pStream)[2])(pStream, nSize);
        // 1417e483d total_ -= buffer_size_ ; then the buffer is cleared
        *(int32_t*)(p + 0x14) = *(int32_t*)(p + 0x14) - *(int32_t*)(p + 0x10);
        *(void**)(p + 0x08) = nullptr;
        *(int32_t*)(p + 0x10) = 0;
    }
    *(int32_t*)(p + 0x14) = *(int32_t*)(p + 0x14) + nCount;   // 1417e4868
    void* pStream = *(void**)(p);
    bool bOk = ((bool (*)(void*, const void*, int32_t))(*(void***)pStream)[4])(pStream, pData,
                                                                              nCount);
    p[0x18] = (uint8_t)(p[0x18] | (bOk ? 0 : 1));             // 1417e48b5 or ecx,[rsp+0x20]
}

// 0x1417e48e0
void SynOutWriteLe32(void* pThis, uint32_t uValue) {
    uint8_t* p = (uint8_t*)pThis;
    // 1417e48e0 movsxd rax,[this+0x10] ; cmp rax,0x4 ; jb -> the local path
    bool bFast = (*(int32_t*)(p + 0x10) >= 4);
    uint8_t aLocal[4];
    void* pDst = bFast ? *(void**)(p + 0x08) : (void*)aLocal;
    g_fnRawLe32(uValue, pDst);                      // 1417e4950 call 0x1417e5520
    if (bFast) {
        g_fnRawConsume(pThis, 4);                   // 1417e4960
    } else {
        g_fnRawAppend(pThis, aLocal, 4);            // 1417e497a
    }
}

// 0x1417e4990
void SynOutWriteLe64(void* pThis, uint64_t uValue) {
    uint8_t* p = (uint8_t*)pThis;
    bool bFast = (*(int32_t*)(p + 0x10) >= 8);      // 1417e4990 cmp rax,0x8
    uint8_t aLocal[8];
    void* pDst = bFast ? *(void**)(p + 0x08) : (void*)aLocal;
    g_fnRawLe64(uValue, pDst);                      // 1417e4a10 call 0x1417e5570
    if (bFast) {
        g_fnRawConsume(pThis, 8);                   // 1417e4a20
    } else {
        g_fnRawAppend(pThis, aLocal, 8);            // 1417e4a3a
    }
}

// 0x1417e4b80
void SynOutWriteVarint64(void* pThis, uint64_t uValue) {
    uint8_t* p = (uint8_t*)pThis;
    // 1417e4b80 cmp DWORD [this+0x10],0xa ; jl -> the local builder
    if (*(int32_t*)(p + 0x10) >= 10) {
        uint8_t* pDst = (uint8_t*)*(void**)(p + 0x08);
        uint8_t* pEnd = (uint8_t*)g_fnRawVarint(uValue, pDst);   // 1417e4ba9
        int32_t nUsed = (int32_t)(pEnd - pDst);                  // 1417e4bbe sub rax,rcx
        g_fnRawConsume(pThis, nUsed);                            // 1417e4bc9
        return;
    }
    uint8_t aTmp[10];
    int32_t nOut = 0;                                            // [rsp+0x38] = 0
    while (uValue > 0x7f) {                                      // 1417e4bf3 cmp rax,0x7f
        aTmp[nOut] = (uint8_t)((uValue & 0x7f) | 0x80);
        ++nOut;
        uValue >>= 7;                                            // 1417e4c22 shr rax,0x7
    }
    aTmp[nOut] = (uint8_t)(uValue & 0x7f);                       // 1417e4c2d
    ++nOut;
    g_fnRawAppend(pThis, aTmp, nOut);                            // 1417e4c47
}

}  // namespace tq
