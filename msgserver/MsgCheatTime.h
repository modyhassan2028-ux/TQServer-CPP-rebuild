// ============================================================
// MsgServer strict port - unit M43
// ORIGINAL: FUN_140001ce0 @ 140001ce0
// The event-time normalizer used by the GM/log event
// path (callers at decompile lines 198639 / 198797 in
// the msgserverdlg region).
//  param_1..4 = FOUR caller buffers (pre-zeroed in the
//    ORIGINAL callers, min ~0x100 bytes each): the
//    2-char YEAR / MONTH / DAY / HOUR fields
//  param_5   = the source "YYMMDDHH" string
// The flow VERBATIM:
//  - null source      -> log @0x227 -> 0
//  - EMPTY source     -> log @0x228 -> 0
//    (the walk: lVar7 from -1; a NUL at [0] leaves -2.
//     NOTE: any NON-empty string passes the guard, even
//     shorter than 8 - then 8 bytes are read anyway:
//     the ORIGINAL relies on the caller's zeroed buffer)
//  - u16 field split:  [0..2)->year [2..4)->mon
//                      [4..6)->day [6..8)->hour
//  - GetTimeZoneInformation: if Bias != -0x1e0
//    (= GMT+8, China) the fields are re-normalized:
//      tm_year = strtoul(year)+100, tm_mon = mon-1,
//      mday, hour, min=sec=isdst=0
//      t = mktime(tm)
//      t2 = t - 0x7080 - Bias*60  (0x7080 = 8h)
//      localtime(t2) null -> log @0x244 -> 0
//      itoa back: year=(tm_year+0x76c)%100,
//                mon+1, mday, hour   (UNPADDED: itoa,
//                so "9" NOT "09" - LITERAL quirk)
//  - returns 1
// The three log paths share the generic ERROR format
// DAT_1406d9c10 (like FUN_140001a50).
// ============================================================
#pragma once
#include <cstdint>
#include <ctime>
#include <functional>
#include <string>
#include <vector>

namespace msg {

struct MsgCheatTimeCtx {
    // ---- seams ----
    // ORIGINAL GetTimeZoneInformation: Bias in MINUTES
    // (default: the host localtime offset)
    std::function<int()> m_fnBias;
    // ORIGINAL _mktime32
    std::function<int64_t(std::tm*)> m_fnMktime;
    // ORIGINAL _localtime32 (null = the 0x244 path)
    std::function<bool(int64_t, std::tm*)> m_fnLocaltime;
    // log sink (line numbers 0x227/0x228/0x244)
    std::function<void(int)> m_fnLog;

    MsgCheatTimeCtx();   // host-time defaults

    // ---- ORIGINAL FUN_140001ce0 ----
    // the four field buffers must be pre-zeroed by the
    // CALLER (as in the ORIGINAL); returns the ORIGINAL
    // bool
    bool Normalize(char* pYear, char* pMon, char* pDay,
                   char* pHour, const char* pSrc);

    // error records (shared-format DAT_1406d9c10 + line)
    std::vector<std::string> m_vecErrLogs;
};

} // namespace msg
