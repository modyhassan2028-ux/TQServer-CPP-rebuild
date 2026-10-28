// ===== Path-A wave 8b: the ORIGINAL
// report builder + OLE date cluster
// VERBATIM (raw objdump-verified) =====
#include "MsgStatusMonitorRpt.h"
#include "MsgStatusMonitorCmd.h"
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <strings.h>

namespace msg {

SMSRptSeams g_MSRptSeams = {};

char     g_RepServerName[32] = {};
uint8_t  g_RepAccountFlag = 0;
uint32_t g_RepPlayerCount = 0;
uint32_t g_RepDbSelectCount = 0;
uint32_t g_RepDbInsertCount = 0;
uint32_t g_RepDbUpdateCount = 0;
uint32_t g_RepDbDeleteCount = 0;
uint64_t g_RepDbSelectTotal = 0;
uint64_t g_RepDbInsertTotal = 0;
uint64_t g_RepDbSelectMax = 0;
uint64_t g_RepDbInsertMax = 0;
uint32_t g_RepWallowSystem = 0;
uint32_t g_RepAdultPlayers = 0;
uint32_t g_RepHealthPlayers = 0;
uint32_t g_RepFatiguedPlayers = 0;
uint32_t g_RepUnhealthyPlayers = 0;
int64_t  g_RepAnalystArg = 0;
uint64_t g_RepDateCache[2] = {0, 0};
uint8_t  g_RepDateParsed = 0;
uint8_t  g_RepDateInitFlag = 0;

// ===== raw helpers: OLE automation
// DATE (days since 1899-12-30) =====
static int64_t DaysFromCivil(
        int64_t y, uint32_t m, uint32_t d) {
    // proleptic Gregorian (exact OLE)
    y -= m <= 2;
    const int64_t era =
        (y >= 0 ? y : y - 399) / 400;
    const uint64_t yoe = (uint64_t)(
        y - era * 400);
    const uint64_t doy =
        (153 * (m + (m > 2 ? -3 : 9)) + 2)
            / 5 + d - 1;
    const uint64_t doe =
        yoe * 365 + yoe / 4 - yoe / 100 +
        doy;
    return era * 146097 +
        (int64_t)doe - 719468;
}
static void CivilFromDays(int64_t z,
        int64_t* y, uint32_t* m,
        uint32_t* d) {
    z += 719468;
    const int64_t era =
        (z >= 0 ? z : z - 146096) / 146097;
    const uint64_t doe =
        (uint64_t)(z - era * 146097);
    const uint64_t yoe =
        (doe - doe / 1460 + doe / 36524
         - doe / 146096) / 365;
    const int64_t yy =
        (int64_t)(yoe) + era * 400;
    const uint64_t doy =
        doe - (365 * yoe + yoe / 4
               - yoe / 100);
    const uint64_t mp =
        (5 * doy + 2) / 153;
    *d = (uint32_t)(doy -
        (153 * mp + 2) / 5 + 1);
    *m = (uint32_t)(mp +
        (mp < 10 ? 3 : -9));
    *y = yy + (*m <= 2);
}

// ===== M: raw default Ordinal_184
static int DefSysTimeToVarDate(
        const short* st, double* out) {
    int64_t y = st[0];
    uint32_t mo = (uint32_t)st[1];
    uint32_t d = (uint32_t)st[3];
    // raw oleaut: years 1753..9999
    if (y < 1753 || y > 9999 ||
        mo < 1 || mo > 12 || d < 1 ||
        d > 31)
        return 0;
    // verify day-in-month
    static const uint32_t mdays[13] =
        {0,31,28,31,30,31,30,31,31,30,
         31,30,31};
    uint32_t dim = mdays[mo];
    if (mo == 2 &&
        ((y % 4 == 0 && y % 100 != 0)
         || y % 400 == 0))
        dim = 29;
    if (d > dim) return 0;
    int64_t serial = DaysFromCivil(
        y, mo, d) -
        DaysFromCivil(1899, 12, 30);
    uint32_t secs = (uint32_t)st[4] *
        3600u + (uint32_t)st[5] * 60u +
        (uint32_t)st[6];
    double frac = 0.0;
    if (secs >= 86400u) return 0;
    if (secs || st[7])
        frac = (secs * 1000u +
               (uint32_t)st[7]) /
               86400000.0;
    *out = (double)serial + frac;
    return 1;
}

// ===== M: raw default Ordinal_185
static int DefVarDateToSysTime(
        double dt, short* out) {
    if (!(dt >= -657434.0 &&
          dt < 2958466.0))
        return 0;
    double ipart = 0.0;
    double frac = std::modf(dt,
                            &ipart);
    int64_t serial = (int64_t)ipart;
    if (frac < 0.0) {
        // pre-1900 reflection: the
        // raw VariantTimeToSystemTime
        // takes the ceil day
        serial -= 1;
        frac += 1.0;
    }
    int64_t y; uint32_t m, d;
    CivilFromDays(serial + 0 +
        DaysFromCivil(1899, 12, 30),
        &y, &m, &d);
    out[0] = (short)y;
    out[1] = (short)m;
    out[2] = 0;   // dow: unused in the
                  // raw round-trip
    out[3] = (short)d;
    uint32_t ms = (uint32_t)(
        frac * 86400000.0 + 0.5);
    out[7] = (short)(ms % 1000);
    ms /= 1000;
    out[6] = (short)(ms % 60);
    ms /= 60;
    out[5] = (short)(ms % 60);
    out[4] = (short)(ms / 60);
    return 1;
}

// ===== M: raw default Ordinal_94
// (VarDateFromStr) — the English
// "Mon DD YYYY" form used by the raw
static int DefVarDateFromStr(
        const char16_t* w, uint32_t,
        uint32_t, double* out) {
    static const char* mons[13] =
        {0,"january","february","march",
         "april","may","june","july",
         "august","september","october",
         "november","december"};
    char buf[64]; int n = 0;
    for (int i = 0; w[i] && n < 63;
         i++)
        buf[n++] = (char)w[i];
    buf[n] = 0;
    // "Dec  4 2015" (extra spaces)
    char* p = buf;
    auto skip = [&](char*& q) {
        while (*q == ' ') q++; };
    char mtok[16]; int mi = 0;
    skip(p);
    while (*p && *p != ' ' && mi < 15)
        mtok[mi++] = *p++;
    mtok[mi] = 0;
    int mon = 0;
    for (int i = 1; i <= 12; i++) {
        if (strncasecmp(
                mons[i], mtok,
                std::strlen(mtok)) == 0) {
            mon = i; break; }
    }
    if (!mon) return
        (int)(int32_t)0x80020005; // TYPEMISMATCH
    skip(p);
    long day = std::strtol(p, &p, 10);
    skip(p);
    long yr = std::strtol(p, &p, 10);
    short st[8] = {(short)yr,
        (short)mon, 0, (short)day,
        0, 0, 0, 0};
    double d = 0.0;
    if (!DefSysTimeToVarDate(st, &d))
        return (int)(int32_t)0x80020005;
    *out = d;
    return 0;   // S_OK
}

// ===== M: raw default
// MultiByteToWideChar(3,...)
static int DefWiden(const char* src,
        char16_t* dst, int chars) {
    int i = 0;
    for (; src[i] && i < chars - 1;
         i++)
        dst[i] = (char16_t)
            (unsigned char)src[i];
    if (src[i]) return 0;   // overflow
    dst[i] = 0;
    return i + 1;   // incl. NUL (raw)
}

// ===== M: raw default _localtime64_s
static int DefLocaltime64S(
        struct tm* out,
        const int64_t* t) {
    time_t tt = (time_t)*t;
    struct tm r;
    if (!localtime_r(&tt, &r))
        return 1;   // errno
    *out = r;
    return 0;
}

void RptSeamsInitDefaults() {
    if (!g_MSRptSeams.SysTimeToVarDate)
        g_MSRptSeams.SysTimeToVarDate =
            DefSysTimeToVarDate;
    if (!g_MSRptSeams.VarDateToSysTime)
        g_MSRptSeams.VarDateToSysTime =
            DefVarDateToSysTime;
    if (!g_MSRptSeams.VarDateFromStr)
        g_MSRptSeams.VarDateFromStr =
            DefVarDateFromStr;
    if (!g_MSRptSeams.WidenAtoW)
        g_MSRptSeams.WidenAtoW =
            DefWiden;
    if (!g_MSRptSeams.Localtime64S)
        g_MSRptSeams.Localtime64S =
            DefLocaltime64S;
}

// ===== M: ORIGINAL OleParseDateStr
// (140029870): widen -> VarDateFromStr
// -> {DATE, flag}
void OleParseDateStr(uint64_t* out16,
        const char* str, uint32_t lcid,
        uint32_t flags) {
    RptSeamsInitDefaults();
    SMSRptSeams& s = g_MSRptSeams;
    if (str == nullptr) str = "";
    // raw: (len+1)*2 bytes; <0x401 ->
    // stack path
    int len = (int)strlen(str);
    int bytes = (len + 1) * 2;
    if (bytes >= 0x401) {
        // raw: malloc chain
        char16_t* w =
            (char16_t*)std::malloc(
                bytes + 0x10);
        if (!w) {
            *(double*)out16 = 0.0;
            *(uint32_t*)(out16 + 1) = 1;
            return;
        }
        if (s.WidenAtoW(str, w,
                bytes / 2) == 0) {
            std::free(w);
            *(double*)out16 = 0.0;
            *(uint32_t*)(out16 + 1) = 1;
            return;
        }
        int hr = s.VarDateFromStr(
            w, lcid, flags,
            (double*)out16);
        std::free(w);
        if (hr < 0) {
            if (hr == -0x7ffdfffb)
                *(double*)out16 = 0.0;
            else
                *(double*)out16 = -1.0;
            *(uint32_t*)(out16 + 1) = 1;
        }
        else {
            *(uint32_t*)(out16 + 1) = 0;
        }
        return;
    }
    char16_t wbuf[0x401];
    if (s.WidenAtoW(str, wbuf,
            bytes / 2) == 0) {
        *(double*)out16 = 0.0;
        *(uint32_t*)(out16 + 1) = 1;
        return;
    }
    int hr = s.VarDateFromStr(
        wbuf, lcid, flags,
        (double*)out16);
    if (hr < 0) {
        if (hr == -0x7ffdfffb)
            *(double*)out16 = 0.0;
        else
            *(double*)out16 = -1.0;
        *(uint32_t*)(out16 + 1) = 1;
    }
    else {
        *(uint32_t*)(out16 + 1) = 0;
    }
}

// ===== M: ORIGINAL OleDateFromTime64
// (140029310): localtime -> pack
// SYSTEMTIME -> VariantTime +
// round-trip check -> {DATE, flag}
void OleDateFromTime64(
        uint64_t* out16, int64_t* t) {
    RptSeamsInitDefaults();
    SMSRptSeams& s = g_MSRptSeams;
    *(uint32_t*)(out16 + 1) = 1;
    struct tm lt;
    if (s.Localtime64S(&lt, t) == 0) {
        short st[8];
        st[0] = (short)lt.tm_year +
                0x76c;
        st[1] = (short)lt.tm_mon + 1;
        st[2] = (short)lt.tm_wday;
        st[3] = (short)lt.tm_mday;
        st[4] = (short)lt.tm_hour;
        st[5] = (short)lt.tm_min;
        st[6] = (short)lt.tm_sec;
        st[7] = 0;
        if (out16 == nullptr) {
            // raw: FUN_140028780
            // (0x80004005) — no return
            std::abort();
        }
        double date = 0.0;
        if (s.SysTimeToVarDate(
                st, &date)) {
            short rt[8] = {0};
            double d2 = date;
            if (s.VarDateToSysTime(
                    d2, rt)) {
                if (st[0] == rt[0] &&
                    st[1] == rt[1] &&
                    st[3] == rt[3] &&
                    st[4] == rt[4] &&
                    st[5] == rt[5] &&
                    st[6] == rt[6]) {
                    *(uint32_t*)
                        (out16 + 1) = 0;
                }
            }
        }
        *(double*)out16 = date;
    }
    else {
        *(double*)out16 = 0.0;
    }
}

// ===== M: ORIGINAL OleDateDiff
// (140029440): negative reflection +
// diff + range flag (±3615897.0)
void OleDateDiff(uint64_t* p1,
        uint64_t* out, uint64_t* p3) {
    double d1 = *(double*)p1;
    if (d1 < 0.0) {
        double c = std::ceil(d1);
        d1 = c - (d1 - c);
    }
    double d2 = *(double*)p3;
    if (d2 < 0.0) {
        double c = std::ceil(d2);
        d2 = c - (d2 - c);
    }
    double d = d1 - d2;
    *(uint32_t*)(out + 1) = 0;
    *(double*)out = d;
    if (d < -3615897.0 ||
        d > 3615897.0) {
        *(uint32_t*)(out + 1) = 1;
    }
}

// ===== M: ORIGINAL builder
// (14002a5a0) VERBATIM =====
void MonitorBuildAndSend(uint8_t* m) {
    RptSeamsInitDefaults();
    SMSRptSeams& s = g_MSRptSeams;
    if (g_pStatusMonitor == 0) {
        // raw CHECKF line 111
        if (s.LogCheckf) s.LogCheckf();
        return;
    }
    *(uint32_t*)(m + 0x0c) = 0;
    *(uint32_t*)(m + 0x08) = 0;
    static char buf[0x400];
    int total = 0;
    #define _snprintf snprintf
    #define RSN(f, ...) \
        total += _snprintf( \
            buf + total, 0x400 - total, \
            f, ##__VA_ARGS__)
    RSN("servername:%s\r\n",
        &g_RepServerName[0]);
    RSN("connect_account:%d\r\n",
        g_RepAccountFlag == 0 ? 1 : 0);
    RSN("player:%d\r\n",
        (int)g_RepPlayerCount);
    int* pMax = s.MaxPlayerGet();
    RSN("player_limit:%u\r\n",
        (uint32_t)*pMax);
    RSN("db_server:%u\r\n",
        g_ResetDbState);
    int64_t crash = *g_MSCmdSeams
        .CrashTimeGet();
    if (crash == 0) {
        RSN("%s",
            "gameserver_crash:0\r\n");
    }
    else {
        int64_t ct = *g_MSCmdSeams
            .CrashTimeGet();
        struct tm* pt = nullptr;
        struct tm lt;
        // raw: _localtime64(&crash)
        time_t tt = (time_t)ct;
        pt = localtime_r(&tt, &lt) ?
            &lt : nullptr;
        if (pt != nullptr) {
            RSN("gameserver_crash:1\r\n");
        }
    }
    RSN("pipe_amount:%d\r\n",
        (int)s.PipeAmount(0xe));
    RSN("db_select_count:%u\r\n",
        g_RepDbSelectCount);
    RSN("db_insert_count:%u\r\n",
        g_RepDbInsertCount);
    RSN("db_update_count:%u\r\n",
        g_RepDbUpdateCount);
    RSN("db_delete_count:%u\r\n",
        g_RepDbDeleteCount);
    RSN("db_select_total_used:%u\r\n",
        (uint32_t)g_RepDbSelectTotal);
    RSN("db_insert_total_used:%u\r\n",
        (uint32_t)g_RepDbInsertTotal);
    RSN("db_select_max_used:%u\r\n",
        (uint32_t)g_RepDbSelectMax);
    RSN("db_insert_max_used:%u\r\n",
        (uint32_t)g_RepDbInsertMax);
    void* analyst = s.AnalystGet();
    uint32_t svc = s.AnalystTotalUsed(
        analyst, g_RepAnalystArg);
    RSN("service_total_used_per5:%u\r\n",
        svc);
    if ((g_RepDateInitFlag & 1) == 0) {
        g_RepDateInitFlag |= 1;
        *(double*)g_RepDateCache = 0.0;
        *(uint32_t*)(g_RepDateCache+1)
            = 0;
    }
    if (g_RepDateParsed == 0) {
        OleParseDateStr(
            g_RepDateCache,
            "Dec  4 2015", 2, 0x400);
        g_RepDateParsed = 1;
    }
    int64_t now = s.Time64();
    uint64_t curDate[2] = {0, 0};
    OleDateFromTime64(curDate, &now);
    uint64_t diff[2] = {0, 0};
    OleDateDiff(curDate, diff,
                g_RepDateCache);
    double d = *(double*)diff;
    double halfSec =
        (d >= 0.0)
            ? 5.787037037037037e-06
            : -5.787037037037037e-06;
    int days = (int)(d + halfSec);
    RSN("valid_days:%d\r\n",
        0x5a - days);
    RSN("wallow_system:%d\r\n",
        (int)g_RepWallowSystem);
    RSN("adult_players:%d\r\n",
        (int)g_RepAdultPlayers);
    RSN("health_players:%d\r\n",
        (int)g_RepHealthPlayers);
    RSN("fatigued_players:%d\r\n",
        (int)g_RepFatiguedPlayers);
    total += _snprintf(
        buf + total, 0x400 - total,
        "unhealthy_players:%d\r\n",
        (int)g_RepUnhealthyPlayers);
    #undef RSN
#undef _snprintf
    // send loop under CS
    g_MSCmdSeams.EnterCS(m + 0x40);
    {
        uint64_t first =
            *(uint64_t*)(m + 0x28);
        uint64_t last =
            *(uint64_t*)(m + 0x30);
        if (last < first)
            if (g_MSCmdSeams
                .InvalidParam)
                g_MSCmdSeams
                    .InvalidParam();
        uint32_t sent = 0;
        for (uint64_t it = first;
             it != last; it += 8) {
            g_MSCmdSeams.WSASend(
                *(uint64_t*)it,
                (uint32_t)total,
                (const uint8_t*)buf,
                &sent);
        }
        VecClear(m + 0x10);
    }
    g_MSCmdSeams.LeaveCS(m + 0x40);
}

} // namespace msg
