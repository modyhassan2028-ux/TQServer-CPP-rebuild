// CQBase.dll v6159 — basefunc.cpp helpers (0x140b82fb0..0x140b883f0)
#include "modules/cqbase/src/basefunc.h"

#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <cctype>

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


// ============================================================================
// the string checks — basefunc.cpp, 0x140b880b0..0x140b88dd0
// ============================================================================

static const char kSz_ZhangSanFeng[] = "\xd5\xc5\xc8\xfd\xb7\xe1";  // '张三丰' at 0x46ccc
static const char kSz_DaJia[] = "\xb4\xf3\xbc\xd2";  // '大家' at 0x46cd4
static const char kSz_HaoYou[] = "\xba\xc3\xd3\xd1";  // '好友' at 0x46cdc
static const char kSz_DuiWu[] = "\xb6\xd3\xce\xe9";  // '队伍' at 0x46ce4
static const char kSz_ShouWei[] = "\xca\xd8\xce\xc0";  // '守卫' at 0x46cec
static const char kSz_WeiBing[] = "\xce\xc0\xb1\xf8";  // '卫兵' at 0x46cf4
static const char kSz_BangPai[] = "\xb0\xef\xc5\xc9";  // '帮派' at 0x46cfc
static const char kSz_A6BF[] = "\xa6\xbf";  // '��' at 0x46d04
static const char kSz_LingJiang[] = "\xc1\xec\xbd\xb1";  // '领奖' at 0x46d08
static const char kSz_GongGao[] = "\xb9\xab\xb8\xe6";  // '公告' at 0x46d10
static const char kSz_KeFu[] = "\xbf\xcd\xb7\xfe";  // '客服' at 0x46d18
static const char kSz_GuanLi[] = "\xb9\xdc\xc0\xed";  // '管理' at 0x46d20
static const char kSz_FuWu[] = "\xb7\xfe\xce\xf1";  // '服务' at 0x46d28
static const char kSz_CeHua[] = "\xb2\xdf\xbb\xae";  // '策划' at 0x46d30
static const char kSz_XiTong[] = "\xcf\xb5\xcd\xb3";  // '系统' at 0x46d38
static const char kSz_TianQing[] = "\xcc\xec\xc7\xe7";  // '天晴' at 0x46d40
static const char kSz_gm1[] = "\x67\xa3\xed";  // 'gｍ' at 0x46d48
static const char kSz_Gm1[] = "\x47\xa3\xed";  // 'Gｍ' at 0x46d4c
static const char kSz_gM1[] = "\x67\xa3\xcd";  // 'gＭ' at 0x46d50
static const char kSz_GM1[] = "\x47\xa3\xcd";  // 'GＭ' at 0x46d54
static const char kSz_gm2[] = "\xa3\xe7\x4d";  // 'ｇM' at 0x46d58
static const char kSz_Gm2[] = "\xa3\xe7\x6d";  // 'ｇm' at 0x46d5c
static const char kSz_GM2[] = "\xa3\xc7\x4d";  // 'ＧM' at 0x46d60
static const char kSz_GmAscii[] = "\xa3\xc7\x6d";  // 'Ｇm' at 0x46d64
static const char kSz_GMfull[] = "\xa3\xc7\xa3\xed";  // 'Ｇｍ' at 0x46d68
static const char kSz_FullGM2[] = "\xa3\xe7\xa3\xcd";  // 'ｇＭ' at 0x46d70
static const char kSz_FullGM3[] = "\xa3\xc7\xa3\xcd";  // 'ＧＭ' at 0x46d78
static const char kSz_FullLower[] = "\xa3\xe7\xa3\xed";  // 'ｇｍ' at 0x46d80
static const char kSz_FullPM1[] = "\xa3\xf0\xa3\xcd";  // 'ｐＭ' at 0x46d88
static const char kSz_FullPM2[] = "\xa3\xd0\xa3\xed";  // 'Ｐｍ' at 0x46d90
static const char kSz_FullPM3[] = "\xa3\xd0\xa3\xcd";  // 'ＰＭ' at 0x46d98
static const char kSz_FullPM4[] = "\xa3\xf0\xa3\xed";  // 'ｐｍ' at 0x46da0
static const char kSz_BracketClose[] = "\xa1\xbf";  // '】' at 0x46da8
static const char kSz_BracketOpen[] = "\xa1\xbe";  // '【' at 0x46dac
static const char kSz_IdeoSpace[] = "\xa1\xa1";  // '\u3000' at 0x46db0
static const char kSz_A3A0[] = "\xa3\xa0";  // '��' at 0x46db4
static const char kSz_RefMark[] = "\xa1\xf9";  // '※' at 0x46db8
static const char kSz_WuZi[] = "\xce\xde";  // '无' at 0x46dbc
static const char kSz_JinTao[] = "\xbd\xf5\xcc\xce";  // '锦涛' at 0x46c68
static const char kSz_ZeMin[] = "\xd4\xf3\xc3\xf1";  // '泽民' at 0x46c70
static const char kSz_HongZhi[] = "\xba\xea\xd6\xbe";  // '宏志' at 0x46c78
static const char kSz_MinJin[] = "\xc3\xf1\xbd\xf8";  // '民进' at 0x46c80
static const char kSz_DuLi[] = "\xb6\xc0\xc1\xa2";  // '独立' at 0x46c88
static const char kSz_TaiDu[] = "\xcc\xa8\xb6\xc0";  // '台独' at 0x46c90
static const char kSz_FaLun[] = "\xb7\xa8\xc2\xd6";  // '法轮' at 0x46c98

static const char* const kForbiddenWords[] = {
    kSz_RefMark, kSz_A3A0, kSz_IdeoSpace, kSz_BracketOpen, kSz_BracketClose,
    kSz_FullPM4, kSz_FullPM3, kSz_FullPM2, kSz_FullPM1, kSz_FullLower, kSz_FullGM3,
    kSz_FullGM2, kSz_GM2, kSz_GmAscii, kSz_GM1, kSz_gM1, kSz_Gm1, kSz_gm1,
    kSz_TianQing, kSz_XiTong, kSz_CeHua, kSz_FuWu, kSz_GuanLi, kSz_KeFu, kSz_GongGao,
    kSz_LingJiang, kSz_A6BF, kSz_BangPai, kSz_WeiBing, kSz_ShouWei, kSz_DuiWu,
    kSz_HaoYou, kSz_DaJia, kSz_ZhangSanFeng,
};
// 队伍 (DuiWu, the team word) is skipped when the caller allows it
static const char* const kBannedWords[] = {
    kSz_JinTao, kSz_ZeMin, kSz_HongZhi, kSz_MinJin, kSz_DuLi, kSz_TaiDu, kSz_FaLun,
};

static std::vector<std::string>& BannedTable() {
    static std::vector<std::string> s_words;
    return s_words;
}
void BannedWordAdd(const char* pszWord) { BannedTable().push_back(pszWord); }
void BannedWordClear() { BannedTable().clear(); }

// 0x140b8a250 — walks the banned word table and answers 1, or a null string
// answers 1 as well (the caller treats a non zero answer as refused).
bool HasBannedWord(char* pszStr) {
    if (pszStr == nullptr) return true;
    for (const std::string& r : BannedTable()) {
        if (std::strstr(pszStr, r.c_str()) != nullptr) return true;
    }
    return false;
}

// 0x140b880b0 — the general check. A lead byte (0x81..0xFF) counts as a double
// byte character and only advances when the language is neither 5 nor 7; with
// those two languages a lead byte advances one and skips every test. 0x80 is
// always refused, and so are the control bytes, except that a caller allowing a
// break also allows 0x0a and 0x0d.
int StringCheck(char* pszStr, int nAllowBreak) {
    if (pszStr == nullptr) return 0;
    uint64_t uLen = std::strlen(pszStr);
    if (uLen != 0) {
        uint64_t uStep = 1;
        uint64_t i = 0;
        do {
            uint8_t c = (uint8_t)pszStr[i];
            if ((uint8_t)(c + 0x7f) < 0x7e) {
                int nLang = *g_pCQLanguageValue();
                if ((nLang != 5) && (nLang != 7)) {
                    if (uLen <= uStep) return 0;
                    i = i + 1;
                    uStep = uStep + 1;
                }
            } else {
                if (c == 0x80) return 0;
                if (nAllowBreak == 0) {
                    if (c < 0x20) return 0;
                } else if (((c < 0x20) && (c != 10)) && (c != 0xd)) {
                    return 0;
                }
            }
            i = i + 1;
            uStep = uStep + 1;
        } while (i < uLen);
    }
    return 1;
}

// 0x140b88160 — the Chinese empty char scan. Only languages 0 and 1 take part;
// every other language answers true at once. The GBK zone table refuses the
// rows and cells that hold symbols rather than characters.
bool CheckChineseEmptyChar(char* pszStr) {
    if (pszStr == nullptr) return false;
    int nLang = *g_pCQLanguageValue();
    if ((nLang != 0) && (nLang != 1)) return true;
    uint64_t uLen = std::strlen(pszStr);
    if (uLen > 1) {
        uint64_t i = 0;
        uint64_t uStep = 1;
        do {
            uint8_t b1 = (uint8_t)pszStr[i];
            if (b1 < 0x21) return false;
            if (b1 == 0x7f) return false;
            if (b1 < 0x7f) {
                i = i + 1;
                uStep = uStep + 1;
            } else {
                if (nLang == 1) return false;
                if (uLen <= uStep) return true;
                uint8_t b2 = (uint8_t)pszStr[i + 1];
                i = i + 2;
                uStep = uStep + 2;
                if (b1 < 0xa1) return false;
                if ((0xa9 < b1) && (b1 < 0xb0)) return false;
                if (0xf7 < b1) return false;
                if (b2 < 0xa1) return false;
                if (b2 == 0xff) return false;
                bool bTail = false;    // the shared arm at joined_140b88348
                if (b1 == 0xa1) {
                    if (b2 == 0xa1) return false;
                } else if (b1 == 0xa2) {
                    if ((0xaa < b2) && (b2 < 0xb1)) return false;
                    if ((0xe2 < b2) && (b2 < 0xe5)) return false;
                    if ((0xee < b2) && (b2 < 0xf1)) return false;
                    if (0xfc < b2) bTail = true;
                } else if (b1 == 0xa4) {
                    if (0xf3 < b2) bTail = true;
                } else if (b1 == 0xa5) {
                    if (0xf6 < b2) bTail = true;
                } else if (b1 == 0xa6) {
                    if ((0xb8 < b2) && (b2 < 0xc1)) return false;
                    if ((0xd8 < b2) && (b2 < 0xe0)) return false;
                    if ((0xeb < b2) && (b2 < 0xee)) return false;
                    if (0xf5 < b2) bTail = true;
                } else if (b1 == 0xa7) {
                    if ((0xc1 < b2) && (b2 < 0xd1)) return false;
                    if (0xf1 < b2) bTail = true;
                } else if (b1 == 0xa8) {
                    if ((0xc0 < b2) && (b2 < 0xc5)) return false;
                    if (0xe9 < b2) bTail = true;
                } else if (b1 == 0xa9) {
                    if ((0xa0 < b2) && (b2 < 0xa4)) return false;
                    if (0xef < b2) bTail = true;
                } else if ((b1 == 0xd7) && (0xf9 < b2)) {
                    bTail = true;
                }
                if (bTail && (b2 != 0xff)) return false;
            }
        } while (i < uLen);
    }
    return true;
}

// 0x140b88540 — the seven word table in front of StringCheck.
int CheckForbiddenWords(char* pszStr, int nFlag) {
    static const char* const kPrefixes[] = { kSz_FaLun, kSz_TaiDu, kSz_DuLi, kSz_MinJin,
                                             kSz_HongZhi, kSz_ZeMin, kSz_JinTao };
    for (const char* pszWord : kPrefixes) {
        if (std::strstr(pszStr, pszWord) != nullptr) return 0;
    }
    return StringCheck(pszStr, nFlag);
}

// 0x140b88c50 — the legal name scan: a leading or trailing '~', any "~~", a
// control byte, the punctuation set, a banned word, then the Chinese scan.
bool LegalStrCheck(char* pszStr) {
    if (pszStr == nullptr) return false;
    uint64_t uLen = std::strlen(pszStr);
    if ((*pszStr == '~') || (pszStr[uLen - 1] == '~')) return false;
    if (std::strstr(pszStr, "~~") != nullptr) return false;
    for (uint64_t i = 0; i < uLen; ++i) {
        uint8_t c = (uint8_t)pszStr[i];
        if (c < 0x20) return false;
        switch ((char)c) {
            case ' ': case '#': case '%': case '\'': case ',': case '/': case ';':
            case '=': case '@': case '\\':
                return false;
        }
    }
    if (HasBannedWord(pszStr)) return false;
    return CheckChineseEmptyChar(pszStr);
}

// 0x140b88610 — the name scan. An empty name logs and refuses; a leading or
// trailing '~', any "~~", a control byte, the punctuation set, one of the
// forbidden words, or one of the blocked words in the uppercased copy all
// refuse. The team word is skipped when the caller allows it.
int NameStrCheck(char* pszStr, bool bAllowTeamWord) {
    if (pszStr == nullptr) return 0;
    uint64_t uLenWith = std::strlen(pszStr) + 1;   // the original's ~mask keeps the null
    if (uLenWith == 1) return 0;
    uint64_t uLen = uLenWith - 1;
    if (*pszStr == '~') return 0;
    if (pszStr[uLen - 1] == '~') return 0;
    if (std::strstr(pszStr, "~~") != nullptr) return 0;
    for (uint64_t i = 0; i < uLen; ++i) {
        uint8_t c = (uint8_t)pszStr[i];
        if (c < 0x20) return 0;
        switch ((char)c) {
            case ' ': case '"': case '%': case '\'': case ',': case '/': case ';':
            case '=': case '@': case '[': case '\\': case ']':
                return 0;
        }
    }
    if (std::memcmp(pszStr, kSz_WuZi, 3) == 0) return 0;    // the three byte start
    for (const char* pszWord : kForbiddenWords) {
        if (pszWord == kSz_DuiWu && bAllowTeamWord) continue;
        if (std::strstr(pszStr, pszWord) != nullptr) return 0;
    }
    char szUpper[256];
    std::memset(szUpper, 0, sizeof(szUpper));
    for (uint64_t i = 0; i < uLen && i < 255; ++i) {
        szUpper[i] = (char)toupper((uint8_t)pszStr[i]);
    }
    static const char* const kBlockedUpper[] = { "GM", "PM", "SYSTEM", "NPC", "GUARD",
                                                 "PATROL", "NONE" };
    for (const char* pszWord : kBlockedUpper) {
        if (std::strstr(szUpper, pszWord) != nullptr) return 0;
    }
    if (!CheckChineseEmptyChar(pszStr)) return 0;
    return CheckForbiddenWords(pszStr, 0);
}

// 0x140b88d60 — talk: no control byte except 0x0a and 0x0d, no quote, no
// apostrophe, no backslash, then the word table.
int TalkStrCheck(char* pszStr, int nFlag) {
    if (pszStr == nullptr) return 0;
    uint64_t uLen = std::strlen(pszStr);
    for (uint64_t i = 0; i < uLen; ++i) {
        uint8_t c = (uint8_t)pszStr[i];
        if (((c < 0x20) && (c != 0xd)) && (c != 10)) return 0;
        if (c == 0x22) return 0;
        if (c == 0x27) return 0;
        if (c == 0x5c) return 0;
    }
    return CheckForbiddenWords(pszStr, nFlag);
}

// 0x140b88dd0 — announce: the talk set plus '^'.
int AnnounceStrCheck(char* pszStr, int nFlag) {
    if (pszStr == nullptr) return 0;
    uint64_t uLen = std::strlen(pszStr);
    for (uint64_t i = 0; i < uLen; ++i) {
        uint8_t c = (uint8_t)pszStr[i];
        if (((c < 0x20) && (c != 0xd)) && (c != 10)) return 0;
        if (c == 0x22) return 0;
        if (c == 0x27) return 0;
        if (c == 0x5c) return 0;
        if (c == 0x5e) return 0;
    }
    return CheckForbiddenWords(pszStr, nFlag);
}

}  // namespace tq
