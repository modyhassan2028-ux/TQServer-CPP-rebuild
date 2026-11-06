// synpbwrite.cpp — see synpbwrite.h
#include "modules/syndicate/src/synpbwrite.h"

namespace tq {

void (*g_fnWrGetBuffer)(void*) = nullptr;
void (*g_fnWrCopy)(void*, const void*, int64_t) = nullptr;
void (*g_fnWrConsume)(void*, int32_t) = nullptr;

// ---------------------------------------------------------------------------
// 0x1417e5520
void* SynWriteLe32(uint32_t uValue, void* pDst) {
    uint8_t* p = (uint8_t*)pDst;
    p[0] = (uint8_t)uValue;
    p[1] = (uint8_t)(uValue >> 8);
    p[2] = (uint8_t)(uValue >> 16);
    p[3] = (uint8_t)(uValue >> 24);
    return p + 4;
}

// ---------------------------------------------------------------------------
// 0x1417e5570 — the body splits the value into its two halves in the home space first, then
// writes each half byte by byte
void* SynWriteLe64(uint64_t uValue, void* pDst) {
    uint32_t nLow = (uint32_t)uValue;
    uint32_t nHigh = (uint32_t)(uValue >> 32);
    uint8_t* p = (uint8_t*)pDst;
    p[0] = (uint8_t)nLow;
    p[1] = (uint8_t)(nLow >> 8);
    p[2] = (uint8_t)(nLow >> 16);
    p[3] = (uint8_t)(nLow >> 24);
    p[4] = (uint8_t)nHigh;
    p[5] = (uint8_t)(nHigh >> 8);
    p[6] = (uint8_t)(nHigh >> 16);
    p[7] = (uint8_t)(nHigh >> 24);
    return p + 8;
}

// ---------------------------------------------------------------------------
// 0x1417e46e0
// The comparison is against the whole block size (+0x10), not against what is still free, and
// the buffered part is copied before the count is reduced.
void SynWriteToBuffer(void* pThis, const void* pSrc, int32_t nCount) {
    uint8_t* p = (uint8_t*)pThis;
    const uint8_t* pData = (const uint8_t*)pSrc;
    for (;;) {
        int32_t nSize = *(int32_t*)(p + 0x10);
        void* pBuffer = *(void**)(p + 0x08);
        if (nSize >= nCount) {                      // 1417e46f3 cmp / jge
            g_fnWrCopy(pBuffer, pData, (int64_t)nCount);
            g_fnWrConsume(pThis, nCount);           // 1417dff70
            return;
        }
        // only the block's worth goes in, then the block is flushed and the rest follows
        g_fnWrCopy(pBuffer, pData, (int64_t)nSize);
        nCount -= nSize;
        pData += nSize;
        g_fnWrGetBuffer(pThis);                     // 1417e4cb0; a failure simply ends the loop
        if (*(int32_t*)(p + 0x18) != 0) {           // the failed flag the getter can raise
            return;
        }
    }
}

// ---------------------------------------------------------------------------
// 0x1417e54d0
bool SynWriteUntilDone(void* pObj, void* pData, int32_t* pnRemaining) {
    bool bOk;
    do {
        bOk = ((bool (*)(void*, void*, int32_t*))(*(void***)pObj)[1])(pObj, pData, pnRemaining);
    } while (bOk && *pnRemaining != 0);
    return bOk;
}

}  // namespace tq
