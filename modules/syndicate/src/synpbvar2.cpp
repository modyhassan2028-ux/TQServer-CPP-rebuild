// synpbvar2.cpp — see synpbvar2.h
#include "modules/syndicate/src/synpbvar2.h"

namespace tq {

int32_t (*g_fnV2Avail)(void*) = nullptr;
void    (*g_fnV2Advance)(void*, int32_t) = nullptr;
bool    (*g_fnV2Refill)(void*) = nullptr;
uint32_t (*g_fnV2FromBlock)(void*) = nullptr;

// ---------------------------------------------------------------------------
// 0x1417e5270
void* SynParseVarint32Array(const void* pData, uint32_t* pOut) {
    const uint8_t* q = (const uint8_t*)pData;
    uint32_t nAcc = 0;
    uint32_t b;

    b = *q++; nAcc = b;
    if (!(b & 0x80)) goto done;
    nAcc -= 0x80;       b = *q++; nAcc += b << 7;
    if (!(b & 0x80)) goto done;
    nAcc -= 0x4000;     b = *q++; nAcc += b << 14;
    if (!(b & 0x80)) goto done;
    nAcc -= 0x200000;   b = *q++; nAcc += b << 21;
    if (!(b & 0x80)) goto done;
    nAcc -= 0x10000000; b = *q++; nAcc += b << 28;
    if (!(b & 0x80)) goto done;

    // every bit of the value is already in: only continuation bytes can follow, five at most
    for (int i = 0;;) {
        if (i >= 5) return nullptr;             // 1417e53fc cmp i,5 ; jge -> fail
        b = *q++;
        if (!(b & 0x80)) goto done;
        ++i;                                    // 1417e53f1
    }

done:
    *pOut = nAcc;                               // 1417e543a
    return (void*)q;
}

// ---------------------------------------------------------------------------
// 0x1417e3bc0
uint32_t SynReadVarint32(void* pThis) {
    uint8_t* p = (uint8_t*)pThis;
    int32_t nAvail = g_fnV2Avail(pThis);        // 1417e3bce

    // 1417e3bd7: ten or more, or a non-empty buffer whose last byte ends the value
    if (nAvail >= 10 ||
        (nAvail > 0 && !(*(uint8_t*)(*(uint8_t**)(p + 0x10) - 1) & 0x80))) {
        uint32_t nValue = 0;
        void* pNext = SynParseVarint32Array(*(void**)(p + 0x08), &nValue);   // 1417e3c09
        if (pNext == nullptr) return 0;         // 1417e3c13
        *(void**)(p + 0x08) = pNext;            // 1417e3c29
        return nValue;
    }

    // 1417e3c35
    if (nAvail != 0) return g_fnV2FromBlock(pThis);
    if (*(int32_t*)(p + 0x2c) <= 0) {           // 1417e3c41 jg skips this test
        if (*(int32_t*)(p + 0x18) != *(int32_t*)(p + 0x28)) return g_fnV2FromBlock(pThis);
    }
    // 1417e3c59
    if (*(int32_t*)(p + 0x18) - *(int32_t*)(p + 0x2c) < *(int32_t*)(p + 0x30)) {
        p[0x24] = 1;                            // 1417e3c7a
        return 0;
    }
    return g_fnV2FromBlock(pThis);              // 1417e3c82
}

// ---------------------------------------------------------------------------
// 0x1417e3ca0
bool SynReadVarint64Slow(void* pThis, uint64_t* pOut) {
    uint8_t* p = (uint8_t*)pThis;
    uint64_t uResult = 0;
    int32_t nShift = 0;

    for (;;) {
        if (nShift == 10) return false;         // 1417e3cc4 cmp [rsp+0x20],0xa ; jne
        if (*(void**)(p + 0x08) == *(void**)(p + 0x10)) {   // 1417e3cda
            if (!g_fnV2Refill(pThis)) return false;         // 1417e3ce3
        }
        uint32_t b = **(uint8_t**)(p + 0x08);   // 1417e3d01
        // 1417e3d16 imul eax,eax,7 ; movzx ecx,al ; shl rax,cl
        uResult |= (uint64_t)(b & 0x7f) << (uint8_t)(nShift * 7);
        g_fnV2Advance(pThis, 1);                // 1417e3d2c mov edx,1
        ++nShift;                               // 1417e3d35
        if (!(b & 0x80)) {
            *pOut = uResult;                    // 1417e3d52
            return true;
        }
    }
}

}  // namespace tq
