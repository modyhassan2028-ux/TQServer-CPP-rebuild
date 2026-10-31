// CQBase.dll v6159 — tq::CStringPacker (0x140bb0b00..0x140bb0d90)
#include "modules/cqbase/src/cstrpacker.h"

#include <cstring>

namespace tq {

void* g_pVftCStringPacker = nullptr;

CStringPacker::CStringPacker() {
    pBuf = nullptr;
    pVft = (void**)g_pVftCStringPacker;
}

CStringPacker::CStringPacker(const CStringPacker& r) {
    pVft = (void**)g_pVftCStringPacker;
    pBuf = r.pBuf;
    nBufSize = r.nBufSize;
}

CStringPacker::~CStringPacker() {
    pVft = (void**)g_pVftCStringPacker;
}

CStringPacker& CStringPacker::operator=(const CStringPacker& r) {
    pBuf = r.pBuf;
    nBufSize = r.nBufSize;
    return *this;
}

void CStringPacker::SetBuf(char* pBuf_, uint32_t nSize, bool bClear) {
    pBuf = pBuf_;
    nBufSize = nSize;
    if (bClear) std::memset(pBuf_, 0, (uint64_t)nSize);
}

uint32_t CStringPacker::GetStrAmount() {
    return (uint32_t)(uint8_t)pBuf[0];
}

// 0x140bb0bb0 — one byte for the count, then 1 + length per string.
uint32_t CStringPacker::GetSize() {
    uint32_t uSize = 1;
    uint8_t cAmount = (uint8_t)pBuf[0];
    uint64_t uLeft = (uint64_t)cAmount;
    uint8_t* pWalk = (uint8_t*)pBuf + 1;
    if (cAmount != 0) {
        do {
            uSize = uSize + 1 + (uint32_t)*pWalk;
            pWalk = pWalk + (int)(*pWalk + 1);
            uLeft = uLeft - 1;
        } while (uLeft != 0);
    }
    return uSize;
}

// 0x140bb0ca0 — a null string still bumps the count and writes one terminator;
// a real string has to fit in a byte and inside the buffer.
bool CStringPacker::AddString(const char* psz) {
    if (pBuf == nullptr) return false;
    if (psz == nullptr) {
        uint32_t uSize = 1;
        uint8_t cAmount = (uint8_t)pBuf[0];
        uint64_t uLeft = (uint64_t)cAmount;
        uint8_t* pWalk = (uint8_t*)pBuf + 1;
        if (cAmount != 0) {
            do {
                uSize = uSize + 1 + (uint32_t)*pWalk;
                pWalk = pWalk + (int)(*pWalk + 1);
                uLeft = uLeft - 1;
            } while (uLeft != 0);
        }
        char* pCount = pBuf;
        *pCount = (char)(*pCount + 1);
        pCount[uSize] = '\0';
        return true;
    }
    uint64_t uLen = std::strlen(psz);
    if (uLen < 0x100) {
        uint32_t uSize = GetSize();
        if ((uint64_t)uSize + uLen <= (uint64_t)nBufSize) {
            char* pCount = pBuf;
            *pCount = (char)(*pCount + 1);
            pCount[uSize] = (char)uLen;
            std::memcpy(pCount + uSize + 1, psz, uLen);
            return true;
        }
        return false;
    }
    return false;
}

// 0x140bb0d90 — the walk stops as soon as the index is found, and the copy is
// refused when the entry would run past the buffer or would not fit the
// caller's size (which is a <= test, so a full fit is refused).
bool CStringPacker::GetString(uint32_t nIndex, char* pOut, uint32_t nOutSize) {
    std::memset(pOut, 0, (uint64_t)nOutSize);
    uint8_t cAmount = (uint8_t)pBuf[0];
    uint8_t* pWalk = (uint8_t*)pBuf + 1;
    if (nIndex < cAmount) {
        uint32_t i = 0;
        if (cAmount != 0) {
            do {
                uint8_t cLen = *pWalk;
                if (nIndex == i) {
                    if ((uint8_t*)((uint64_t)nBufSize + (uint64_t)(uintptr_t)pBuf) <
                        pWalk + (int)(cLen + 1)) {
                        return false;
                    }
                    if (nOutSize <= cLen) return false;
                    std::memcpy(pOut, pWalk + 1, (uint64_t)cLen);
                    return true;
                }
                i = i + 1;
                pWalk = pWalk + (int)(cLen + 1);
            } while (i < cAmount);
        }
    }
    return false;
}

}  // namespace tq
