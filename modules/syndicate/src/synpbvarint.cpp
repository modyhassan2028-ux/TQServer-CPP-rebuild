// synpbvarint.cpp — see synpbvarint.h
#include "modules/syndicate/src/synpbvarint.h"

namespace tq {

int32_t (*g_fnViAvail)(void*) = nullptr;
void    (*g_fnViAdvance)(void*, int32_t) = nullptr;
bool    (*g_fnViSlow)(void*, uint64_t*) = nullptr;

// ---------------------------------------------------------------------------
// 0x1417e3d80
bool SynReadVarint64(void* pThis, uint64_t* pOut) {
    uint8_t* p = (uint8_t*)pThis;

    // 1417e3d98..1417e3dc9 — the guard only runs when fewer than ten bytes are available
    if (g_fnViAvail(pThis) < 10) {
        if (*(uint8_t**)(p + 0x10) <= *(uint8_t**)(p + 0x08)) {   // cmp [rcx+0x10], rax ; jbe
            return g_fnViSlow(pThis, pOut);
        }
        if (*(uint8_t*)(*(uint8_t**)(p + 0x10) - 1) & 0x80) {
            return g_fnViSlow(pThis, pOut);
        }
    }

    const uint8_t* pStart = *(uint8_t**)(p + 0x08);
    const uint8_t* q = pStart;
    uint32_t nLo = 0, nHi = 0, nTop = 0;
    uint32_t b;

    b = *q++; nLo = b;
    if (!(b & 0x80)) goto done;
    nLo -= 0x80;       b = *q++; nLo += b << 7;
    if (!(b & 0x80)) goto done;
    nLo -= 0x4000;     b = *q++; nLo += b << 14;
    if (!(b & 0x80)) goto done;
    nLo -= 0x200000;   b = *q++; nLo += b << 21;
    if (!(b & 0x80)) goto done;

    nLo -= 0x10000000; b = *q++; nHi = b;
    if (!(b & 0x80)) goto done;
    nHi -= 0x80;       b = *q++; nHi += b << 7;
    if (!(b & 0x80)) goto done;
    nHi -= 0x4000;     b = *q++; nHi += b << 14;
    if (!(b & 0x80)) goto done;
    nHi -= 0x200000;   b = *q++; nHi += b << 21;
    if (!(b & 0x80)) goto done;

    nHi -= 0x10000000; b = *q++; nTop = b;
    if (!(b & 0x80)) goto done;
    nTop -= 0x80;      b = *q++; nTop += b << 7;
    if (b & 0x80) {                      // 1417e40d7 — an eleventh byte is a malformed value
        return false;
    }

done:
    g_fnViAdvance(pThis, (int32_t)(q - pStart));       // 1417e50a0
    *pOut = (uint64_t)nLo | ((uint64_t)nHi << 28) | ((uint64_t)nTop << 56);
    return true;
}

// ---------------------------------------------------------------------------
// 0x1417e5610
void* SynWriteVarint32ToArray(uint32_t uValue, void* pDst) {
    uint8_t* p = (uint8_t*)pDst;
    p[0] = (uint8_t)(uValue | 0x80);
    if (uValue < 0x80u) { p[0] &= 0x7f; return p + 1; }
    p[1] = (uint8_t)((uValue >> 7) | 0x80);
    if (uValue < 0x4000u) { p[1] &= 0x7f; return p + 2; }
    p[2] = (uint8_t)((uValue >> 14) | 0x80);
    if (uValue < 0x200000u) { p[2] &= 0x7f; return p + 3; }
    p[3] = (uint8_t)((uValue >> 21) | 0x80);
    if (uValue < 0x10000000u) { p[3] &= 0x7f; return p + 4; }
    p[4] = (uint8_t)(uValue >> 28);     // the last byte carries no continuation bit
    return p + 5;
}

}  // namespace tq
