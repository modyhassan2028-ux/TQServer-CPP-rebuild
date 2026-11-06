// synpbcodec.cpp — see synpbcodec.h
#include "modules/syndicate/src/synpbcodec.h"

namespace tq {

void (*g_fnCodecConsume)(void*, int32_t) = nullptr;
void (*g_fnCodecAdvance)(void*, int32_t) = nullptr;
bool (*g_fnCodecReadVarint)(void*, uint64_t*) = nullptr;
bool (*g_fnCodecStreamNext)(void*, void**, int32_t*) = nullptr;

// 0x1417e4cb0
bool SynCodecRefresh(void* pThis) {
    uint8_t* p = (uint8_t*)pThis;
    void* pData = nullptr;
    // 1417e4cb7 r8 = this+0x10 ; rcx = *(void**)this ; rax = vt ; call [vt+0x8]
    bool bOk = g_fnCodecStreamNext(*(void**)p, &pData, (int32_t*)(p + 0x10));
    if (bOk) {
        // 1417e4cfd mov [this+0x8],data ; 1417e4d07 total_ += buffer_size_
        *(void**)(p + 0x08) = pData;
        *(int32_t*)(p + 0x14) = *(int32_t*)(p + 0x14) + *(int32_t*)(p + 0x10);
        return true;                    // 1417e4d2a mov al,1
    }
    // 1417e4d10..1417e4d2c the failure stores
    *(void**)(p + 0x08) = nullptr;
    *(int32_t*)(p + 0x10) = 0;
    p[0x18] = 1;
    return false;                       // 1417e4d32 xor al,al
}

// 0x1417e4680
bool SynCodecNext(void* pThis, void** ppData, int32_t* pnSize) {
    uint8_t* p = (uint8_t*)pThis;
    // 1417e4680 cmp DWORD [this+0x10],0 ; jne -> already buffered
    if (*(int32_t*)(p + 0x10) == 0) {
        if (!SynCodecRefresh(pThis)) return false;   // 1417e4695 xor al,al
    }
    // 1417e46b3 *ppData = [this+0x8] ; *pnSize = [this+0x10]
    *ppData = *(void**)(p + 0x08);
    *pnSize = *(int32_t*)(p + 0x10);
    return true;                        // 1417e46d2 mov al,1
}

// 0x1417e4610
bool SynCodecSkip(void* pThis, int32_t nCount) {
    uint8_t* p = (uint8_t*)pThis;
    if (nCount < 0) return false;       // 1417e4622 jge ; else xor al,al
    while (nCount > *(int32_t*)(p + 0x10)) {
        // 1417e4635: take what is buffered and refresh for the rest
        nCount -= *(int32_t*)(p + 0x10);
        if (!SynCodecRefresh(pThis)) return false;   // 1417e4657 xor al,al
        // 1417e465d jmp back to the compare
    }
    g_fnCodecConsume(pThis, nCount);    // 1417e4668 call 0x1417dff70
    return true;                        // 1417e466d mov al,1
}

// 0x1417e5450
bool SynCodecReadVarintFast(void* pThis, uint64_t* pValue) {
    uint8_t* p = (uint8_t*)pThis;
    // 1417e5450 cmp [this+0x8],rax([this+0x10]) ; jae -> the general read
    if ((uintptr_t)*(void**)(p + 0x08) < (uintptr_t)*(void**)(p + 0x10)) {
        uint8_t uByte = **(uint8_t**)(p + 0x08);
        // 1417e5477 cmp eax,0x80 ; jge -> the general read
        if (uByte < 0x80) {
            *pValue = (uint64_t)uByte;              // 1417e5490 mov [rax],rcx
            g_fnCodecAdvance(pThis, 1);             // 1417e549b mov edx,1 ; call 0x1417e50a0
            return true;                            // 1417e54a3 mov al,1
        }
    }
    return g_fnCodecReadVarint(pThis, pValue);      // 1417e54b7 call 0x1417e3d80
}

}  // namespace tq
