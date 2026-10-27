#include "MsgCheatTime.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace msg {

MsgCheatTimeCtx::MsgCheatTimeCtx() {
    m_fnBias = [] {
        // host localtime Bias (minutes): UTC+8 -> -480
        std::time_t t = std::time(nullptr);
        std::tm lo{};
        localtime_r(&t, &lo);
        return -(int)(lo.tm_gmtoff / 60);
    };
    m_fnMktime = [](std::tm* p) -> int64_t {
        return (int64_t)std::mktime(p);
    };
    m_fnLocaltime = [](int64_t t, std::tm* p) -> bool {
        time_t tt = (time_t)t;
        return localtime_r(&tt, p) != nullptr;
    };
    m_fnLog = [this](int nLine) {
        char sz[64];
        std::snprintf(sz, sizeof sz,
            "log_InlineLogERROR(&DAT_1406d9c10) line 0x%x",
            nLine);
        m_vecErrLogs.push_back(sz);
    };
}

// ===== ORIGINAL FUN_140001ce0 @ 140001ce0 =====
bool MsgCheatTimeCtx::Normalize(char* pYear, char* pMon,
                                char* pDay, char* pHour,
                                const char* pSrc) {
    if (pSrc == nullptr) {
        m_fnLog(0x227);
        return false;
    }
    // the -1/-2 walk: EMPTY string -> -2 -> fail
    int64_t nWalk = -1;
    const char* p = pSrc;
    do {
        if (nWalk == 0) break;
        --nWalk;
        char c = *p; ++p;
        if (c == '\0') break;
    } while (true);
    if (nWalk == -2) {
        m_fnLog(0x228);
        return false;
    }
    // u16 field split (2 bytes each, no NUL added)
    std::memcpy(pYear, pSrc + 0, 2);
    std::memcpy(pMon,  pSrc + 2, 2);
    std::memcpy(pDay,  pSrc + 4, 2);
    std::memcpy(pHour, pSrc + 6, 2);
    int nBias = m_fnBias();
    if (nBias != -0x1e0) {   // not GMT+8: normalize
        std::tm t{};
        t.tm_year = (int)std::strtoul(pYear, nullptr, 10)
                   + 100;
        t.tm_mon  = (int)std::strtoul(pMon, nullptr, 10)
                   - 1;
        t.tm_mday = (int)std::strtoul(pDay, nullptr, 10);
        t.tm_hour = (int)std::strtoul(pHour, nullptr, 10);
        t.tm_min = 0; t.tm_sec = 0; t.tm_isdst = 0;
        int64_t tCal = m_fnMktime(&t);
        // t2 = t - 0x7080 - Bias*60
        int64_t tAdj = tCal - 0x7080
                     - (int64_t)nBias * 60;
        std::tm lo{};
        if (!m_fnLocaltime(tAdj, &lo)) {
            m_fnLog(0x244);
            return false;
        }
        // itoa back (UNPADDED - literal quirk)
        std::snprintf(pYear, 12, "%d",
            (lo.tm_year + 0x76c) % 100);
        std::snprintf(pMon, 12, "%d", lo.tm_mon + 1);
        std::snprintf(pDay, 12, "%d", lo.tm_mday);
        std::snprintf(pHour, 12, "%d", lo.tm_hour);
    }
    return true;
}

} // namespace msg
