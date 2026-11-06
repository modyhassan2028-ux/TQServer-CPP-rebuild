// synpbread2.cpp — see synpbread2.h
#include "modules/syndicate/src/synpbread2.h"

#include "modules/syndicate/src/synpbvar2.h"   // SynParseVarint32Array

namespace tq {

int32_t (*g_fnR2Avail)(void*) = nullptr;
bool (*g_fnR2ReadVarint64)(void*, uint64_t*) = nullptr;
int32_t* (*g_fnR2ClampMin)(int32_t*, int32_t*) = nullptr;

// ---------------------------------------------------------------------------
// 0x1417e3a10
bool SynReadVarint32Via64(void* pThis, uint32_t* pOut) {
    uint64_t uValue = 0;
    if (!g_fnR2ReadVarint64(pThis, &uValue)) return false;   // 1417e3a25
    *pOut = (uint32_t)uValue;                                // 1417e3a38 mov eax,[rsp+0x20]
    return true;
}

// ---------------------------------------------------------------------------
// 0x1417e3a50
bool SynReadVarint32Fast(void* pThis, uint32_t* pOut) {
    uint8_t* p = (uint8_t*)pThis;

    if (g_fnR2Avail(pThis) < 10) {                            // 1417e3a66 cmp eax,0xa
        if (*(uint8_t**)(p + 0x10) <= *(uint8_t**)(p + 0x08)) {   // 1417e3a7e jbe
            return SynReadVarint32Via64(pThis, pOut);         // 1417e3acf
        }
        if (*(uint8_t*)(*(uint8_t**)(p + 0x10) - 1) & 0x80) {
            return SynReadVarint32Via64(pThis, pOut);
        }
    }

    void* pNext = SynParseVarint32Array(*(void**)(p + 0x08), pOut);   // 1417e3a97
    if (pNext == nullptr) return false;                       // 1417e3ab3
    *(void**)(p + 0x08) = pNext;
    return true;
}

// ---------------------------------------------------------------------------
// 0x1417e5000
void SynResetBlockBounds(void* pThis) {
    uint8_t* p = (uint8_t*)pThis;

    // 1417e500c: end += the bytes held back (sign extended)
    *(uint8_t**)(p + 0x10) += (int64_t)*(int32_t*)(p + 0x2c);

    // 1417e5020..0x1417e5038: the smaller of the two counts
    int32_t* pMin = g_fnR2ClampMin((int32_t*)(p + 0x28), (int32_t*)(p + 0x30));
    int32_t nMin = *pMin;

    if (nMin < *(int32_t*)(p + 0x18)) {                       // 1417e5045 jge
        *(int32_t*)(p + 0x2c) = *(int32_t*)(p + 0x18) - nMin;
        *(uint8_t**)(p + 0x10) -= (int64_t)*(int32_t*)(p + 0x2c);
    } else {
        *(int32_t*)(p + 0x2c) = 0;                            // 1417e5086
    }
}

}  // namespace tq
