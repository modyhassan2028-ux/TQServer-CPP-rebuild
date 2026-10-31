// CQBase.dll v6159 — basefunc.cpp helpers (0x140b82fb0..0x140b883f0)
#include "modules/cqbase/src/basefunc.h"

#include <cmath>
#include <cstdio>
#include <cstring>

#include "modules/cqbase/src/ctimer.h"

namespace tq {

static int64_t DefMkTime(tm* pTm) { return (int64_t)mktime(pTm); }
static void DefLocalTime(SysLocalTime* pOut) { std::memset(pOut, 0, sizeof(*pOut)); }
int64_t (*g_pfnMkTime64)(tm* pTm) = DefMkTime;
void (*g_pfnGetLocalTime)(SysLocalTime* pOut) = DefLocalTime;

static int s_nCQLanguage = 0;
int* g_pCQLanguageValue() { return &s_nCQLanguage; }
int* CQLanguageGet() { return g_pCQLanguageValue(); }

// _localtime64 on the file's clock seam
static tm* LocaltimeHere(int64_t tValue) {
#if defined(_WIN32)
    return _localtime64(&tValue);
#else
    static thread_local tm s_tm;
    time_t tRaw = (time_t)tValue;
    return localtime_r(&tRaw, &s_tm) ? &s_tm : nullptr;
#endif
}

// 0x140b82fb0 — two rand draws folded into 0x8000 base, zero or less is 0.
// The multiply overflows a signed int in the original and the compiler wraps,
// so the sum is formed in 32 bits and the modulo keeps the dividend's sign.
int RandGet(int nMax) {
    if (0 < nMax) {
        int a = rand();
        int b = rand();
        int32_t nFolded = (int32_t)((uint32_t)b + (uint32_t)a * 0x8000u);
        return nFolded % nMax;
    }
    return 0;
}

// 0x140b82ff0 — the rate curve: 1..999 through sin, then a double square root.
// Past 89 the result is 1.0 + rate - root * rate, otherwise
// root * rate + (1.0 - rate).
double RandomRateGet(double dRate) {
    int a = rand();
    int b = rand();
    int32_t nFolded = (int32_t)((uint32_t)a * 0x8000u + (uint32_t)b);
    int nPoint = nFolded % 999 + 1;
    double dSin = std::sin(((double)nPoint * 3.1415926) / 1000.0);
    if (0x59 < nPoint) {
        double dBase = dRate + 1.0;
        double dRoot = std::sqrt(std::sqrt(dSin));
        return dBase - dRoot * dRate;
    }
    double dRoot = std::sqrt(std::sqrt(dSin));
    return dRoot * dRate + (1.0 - dRate);
}

// 0x140b830d0 — a size that can hold the source is a bounded copy with a
// forced terminator; a size that cannot is an unbounded copy instead.
bool StrCopy(char* pszDst, const char* pszSrc, uint64_t nSize) {
    if (((pszDst == nullptr) || (pszSrc == nullptr)) || (nSize == 0)) return false;
    uint64_t uLen = std::strlen(pszSrc);
    if (nSize <= uLen) {
        strncpy(pszDst, pszSrc, nSize);
        pszDst[nSize - 1] = '\0';
        return true;
    }
    char* pWrite = pszDst;
    const char* pRead = pszSrc;
    char c;
    do {
        c = *pRead++;
        *pWrite++ = c;
    } while (c != '\0');
    return true;
}

// 0x140b876d0 — the original's byte walk: an ASCII byte advances one, a lead
// byte (0x81..0xFF) advances two so a double byte pair is never split, and the
// candidate is compared with strncmp against the char set. Two of its steps
// dereference one byte past the terminator; the port stops at the terminator
// instead of reading that byte.
char* StrStrCh(char* pszStr, const char* pszChars) {
    if ((pszStr == nullptr) || (pszChars == nullptr)) return nullptr;
    uint64_t uSetLen = std::strlen(pszChars);
    if (uSetLen == 0) return nullptr;
    uint64_t uLen = std::strlen(pszStr);
    if (uSetLen > uLen) return nullptr;
    char cSet = *pszChars;
    char* pEnd = pszStr + uLen;              // the terminator
    char* pCur = pszStr;
    char cCur = *pCur;
    while (cCur != 0) {
        cCur = *pCur;
        while (cCur != 0) {
            if (cCur == cSet) {
                if ((*pCur != '\0') && (std::strncmp(pCur, pszChars, uSetLen) == 0)) {
                    return pCur;
                }
                break;
            }
            char* pNext = pCur;
            if (((uint8_t)(cCur + 0x7f) < 0x7e) && (pCur[1] != '\0')) {
                pNext = pCur + 1;
            }
            pCur = pNext + 1;
            cCur = (pCur < pEnd) ? *pCur : 0;
        }
        pCur = pCur + 1;
        cCur = (pCur < pEnd) ? *pCur : 0;
    }
    return nullptr;
}

// 0x140b877d0 — the packed stamp the window compares. A stamp whose leading
// day part is empty uses the weekday form, otherwise the month-day form. A
// window that wraps (end before begin) matches outside the pair.
bool IsTimeRange(uint32_t uBegin, uint32_t uEnd, int64_t tCheck) {
    int64_t tUsed = tCheck;
    if (tCheck == 0) tUsed = g_pfnTime64();
    tm* pTm = LocaltimeHere(tUsed);
    if (pTm == nullptr) return false;
    int nNow;
    if (uBegin / 100000000 == 0) {
        nNow = ((pTm->tm_wday * 100 + pTm->tm_hour) * 100 + pTm->tm_min) * 100 + pTm->tm_sec;
    } else {
        nNow = ((pTm->tm_mday * 10000 + pTm->tm_hour) * 100 + pTm->tm_min) * 100 + pTm->tm_sec;
    }
    if ((int)uEnd < (int)uBegin) {
        if (nNow < (int)uEnd) return true;
        if ((int)uBegin <= nNow) return true;
        return false;
    }
    if ((int)uBegin <= nNow) {
        if (nNow < (int)uEnd) return true;
        return false;
    }
    return false;
}

// 0x140b878c0 — "%04d-%02d-%02d %02d:%02d:%02d"; the tail arguments sit on
// the stack in the dump, so they are written out here in that order.
void DateTime(char* pszOut, int64_t tValue) {
    if (pszOut == nullptr) return;
    int64_t tUsed = tValue;
    if (tValue == 0) tUsed = g_pfnTime64();
    tm* pTm = LocaltimeHere(tUsed);
    if (pTm != nullptr) {
        sprintf(pszOut, "%04d-%02d-%02d %02d:%02d:%02d", pTm->tm_year + 0x76c, pTm->tm_mon + 1,
                pTm->tm_mday, pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
    }
}

// 0x140b87940 — hour and minute packed as HHMM.
uint32_t SysTimeGet() {
    int64_t tNow = g_pfnTime64();
    tm* pTm = LocaltimeHere(tNow);
    if (pTm == nullptr) return 0;
    return (uint32_t)(pTm->tm_hour * 100 + pTm->tm_min);
}

// 0x140b87980 — YYYYMMDD as (year*100 + 190001 + month)*100 + day.
int DateStamp(int64_t tValue) {
    int64_t tUsed = tValue;
    if (tValue == 0) tUsed = g_pfnTime64();
    tm* pTm = LocaltimeHere(tUsed);
    if (pTm != nullptr) {
        return (pTm->tm_year * 100 + 0x2e631 + pTm->tm_mon) * 100 + pTm->tm_mday;
    }
    return 0;
}

// 0x140b879e0 — YYMMDDHHMM.
uint32_t TimeStampGet() {
    int64_t tNow = g_pfnTime64();
    tm* pTm = LocaltimeHere(tNow);
    if (pTm == nullptr) return 0;
    return (((((uint32_t)(pTm->tm_year % 100) * 100 + 1 + (uint32_t)pTm->tm_mon) * 100 +
              (uint32_t)pTm->tm_mday) * 100 + (uint32_t)pTm->tm_hour) * 100 +
            (uint32_t)pTm->tm_min);
}

// 0x140b87c30 — add days to a YYYYMMDD stamp through mktime, then re-encode.
// Anything mktime refuses answers -1, and a zero result is replaced by now.
int DateStampPass(int nStamp, int nDayDelta) {
    tm tmv;
    std::memset(&tmv, 0, sizeof(tmv));
    tmv.tm_year = nStamp / 10000 + -0x76c;
    tmv.tm_mday = nStamp % 100 + nDayDelta;
    tmv.tm_mon = (nStamp / 100) % 100 + -1;
    int64_t tMade = g_pfnMkTime64(&tmv);
    if (tMade == -1) return -1;
    int64_t tUsed = tMade;
    if (tMade == 0) tUsed = g_pfnTime64();
    tm* pTm = LocaltimeHere(tUsed);
    if (pTm != nullptr) {
        return (pTm->tm_year * 100 + 0x2e631 + pTm->tm_mon) * 100 + pTm->tm_mday;
    }
    return 0;
}

// 0x140b87d40 — whole days between two stamps; the first argument is mktime'd
// second, and the subtraction is divided by 0x15180.
int DateStampDiff(int nStampA, int nStampB) {
    tm tmB;
    tm tmA;
    std::memset(&tmB, 0, sizeof(tmB));
    std::memset(&tmA, 0, sizeof(tmA));
    tmA.tm_year = nStampA / 10000 + -0x76c;
    tmA.tm_mday = nStampA % 100;
    tmA.tm_mon = (nStampA / 100) % 100 + -1;
    tmB.tm_year = nStampB / 10000 + -0x76c;
    tmB.tm_mday = nStampB % 100;
    tmB.tm_mon = (nStampB / 100) % 100 + -1;
    int64_t tB = g_pfnMkTime64(&tmB);
    int64_t tA = g_pfnMkTime64(&tmA);
    return (int)((tB - tA) / 0x15180);
}

// 0x140b87e90 — MMDDHHMMSS, and note the month is taken raw, not +1.
uint32_t SysTimeGetEx() {
    int64_t tNow = g_pfnTime64();
    tm* pTm = LocaltimeHere(tNow);
    if (pTm == nullptr) return 0;
    return ((((uint32_t)pTm->tm_mon * 100 + (uint32_t)pTm->tm_mday) * 100 +
             (uint32_t)pTm->tm_hour) * 100 + (uint32_t)pTm->tm_min) * 100 +
           (uint32_t)pTm->tm_sec;
}

// 0x140b87ef0 — "%04d%02d%02d%02d%02d%02d", same hidden tail as DateTime.
void DateTimeStamp(char* pszOut, int64_t tValue) {
    if (pszOut == nullptr) return;
    int64_t tUsed = tValue;
    if (tValue == 0) tUsed = g_pfnTime64();
    tm* pTm = LocaltimeHere(tUsed);
    if (pTm != nullptr) {
        sprintf(pszOut, "%04d%02d%02d%02d%02d%02d", pTm->tm_year + 0x76c, pTm->tm_mon + 1,
                pTm->tm_mday, pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
    }
}

// 0x140b87f70 — a weekday window (leading part under 10^8) filters the day of
// week through ((wday + 6) % 7) + 1, the other shape filters the month day.
// Hour, minute and second must match either way.
bool IsActiveTime(int64_t tValue, uint32_t uStamp) {
    tm* pTm = LocaltimeHere(tValue);
    if (pTm == nullptr) return false;
    bool bHourOk;
    if (uStamp / 100000000 == 0) {
        if ((uStamp / 1000000 != 0) &&
            ((uint32_t)((pTm->tm_wday + 6) % 7 + 1) != uStamp / 1000000)) {
            return false;
        }
        bHourOk = (uint32_t)pTm->tm_hour == (uStamp / 10000) % 100;
    } else {
        if ((uint32_t)pTm->tm_mday != uStamp / 100000000) return false;
        bHourOk = (uint32_t)pTm->tm_hour == (uStamp / 10000) % 100;
    }
    if (bHourOk && ((uint32_t)pTm->tm_min == (uStamp / 100) % 100) &&
        ((uint32_t)pTm->tm_sec == uStamp % 100)) {
        return true;
    }
    return false;
}

// 0x140b88370 — YYMMDDHHMMSSmmm from GetLocalTime, built from the outside in.
uint64_t TimeStampGetEx() {
    SysLocalTime st;
    g_pfnGetLocalTime(&st);
    return ((((((uint64_t)(st.wYear % 100) * 100 + st.wMonth) * 100 + st.wDay) * 100 + st.wHour) *
                 100 + st.wMinute) * 100 + st.wSecond) * 1000 + st.wMilliseconds;
}

// 0x140b883f0 — seconds to YYYYMMDDHHMMSS, zero meaning now.
uint64_t TurnStampToTime(uint32_t uStamp) {
    int64_t tUsed = 0;
    if (uStamp == 0) {
        tUsed = g_pfnTime64();
    } else {
        tUsed = (int64_t)uStamp;
    }
    tm* pTm = LocaltimeHere(tUsed);
    if (pTm == nullptr) return 0;
    return (uint64_t)(pTm->tm_mday * 1000000) + (uint64_t)((pTm->tm_mon + 1) * 100000000) +
           (uint64_t)(pTm->tm_year + 0x76c) * 10000000000ULL +
           (uint64_t)(pTm->tm_hour * 10000) + (uint64_t)(pTm->tm_min * 100) +
           (uint64_t)pTm->tm_sec;
}

}  // namespace tq
