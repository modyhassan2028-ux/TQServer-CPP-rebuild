// ============================================================================
// basefunc.h — RAW CQBase.dll v6159 · basefunc.cpp helpers
//   the random pair, the two string helpers, and the whole date/time stamp
//   family the game packs into integers (YYYYMMDD, YYMMDDHHMM, ...).
//   Constants read from .rdata: 0x45ee0 = 1.0, 0x45ee8 = 1000.0,
//   0x45ef0 = 3.1415926 (the pi the sine uses).
// ============================================================================
#ifndef CQBASE_UTIL_BASEFUNC_H
#define CQBASE_UTIL_BASEFUNC_H

#include <cstdint>
#include <ctime>

namespace tq {

int RandGet(int nMax);                       // 0x140b82fb0
double RandomRateGet(double dRate);          // 0x140b82ff0
bool StrCopy(char* pszDst, const char* pszSrc, uint64_t nSize);   // 0x140b830d0
char* StrStrCh(char* pszStr, const char* pszChars);               // 0x140b876d0
int* CQLanguageGet();                        // 0x140b87a50

bool IsTimeRange(uint32_t uBegin, uint32_t uEnd, int64_t tCheck);   // 0x140b877d0
void DateTime(char* pszOut, int64_t tValue);                        // 0x140b878c0
uint32_t SysTimeGet();                       // 0x140b87940
int DateStamp(int64_t tValue);               // 0x140b87980
uint32_t TimeStampGet();                     // 0x140b879e0
int DateStampPass(int nStamp, int nDayDelta);   // 0x140b87c30
int DateStampDiff(int nStampA, int nStampB);    // 0x140b87d40
uint32_t SysTimeGetEx();                     // 0x140b87e90
void DateTimeStamp(char* pszOut, int64_t tValue);   // 0x140b87ef0
bool IsActiveTime(int64_t tValue, uint32_t uStamp); // 0x140b87f70
uint64_t TimeStampGetEx();                   // 0x140b88370
uint64_t TurnStampToTime(uint32_t uStamp);   // 0x140b883f0

// the SYSTEMTIME the millisecond stamp reads
struct SysLocalTime {
    uint16_t wYear, wMonth, wDayOfWeek, wDay;
    uint16_t wHour, wMinute, wSecond, wMilliseconds;
};
extern void (*g_pfnGetLocalTime)(SysLocalTime* pOut);
extern int64_t (*g_pfnMkTime64)(tm* pTm);        // _mktime64
extern int64_t (*g_pfnTime64Local)(void);        // _time64 for this file
int* g_pCQLanguageValue();                       // the DAT_140be79a0 seam

}  // namespace tq
#endif
