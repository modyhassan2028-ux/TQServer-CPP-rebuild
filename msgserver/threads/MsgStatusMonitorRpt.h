#ifndef MSG_STATUS_MONITOR_RPT_H
#define MSG_STATUS_MONITOR_RPT_H
// ===== Path-A wave 8b: report
// builder 14002a5a0 + OLE date
// cluster (140029870 / 140029310 /
// 140029440) — VERBATIM raw-verified
// =====
// Report (23 _snprintf appends, all
// raw-extracted): servername:%s /
// connect_account:%d / player:%d /
// player_limit:%u / db_server:%u /
// gameserver_crash via %s or :1 /
// pipe_amount:%d / db_{select,insert,
// update,delete}_count:%u /
// db_{select,insert}_total_used:%u /
// db_{select,insert}_max_used:%u /
// service_total_used_per5:%u /
// valid_days:%d (90 - round(days))
// / wallow_system:%d / adult_players
// / health_players / fatigued_players
// / unhealthy_players =====
#include <cstdint>
#include <cstddef>
#include <ctime>

namespace msg {

// ---- report globals (raw .data) ----
extern char     g_RepServerName[];      // 0x140975674 (buffer)
extern uint8_t  g_RepAccountFlag;       // 0x1409757c4 byte
extern uint32_t g_RepPlayerCount;       // 0x1409756f0
extern uint32_t g_RepDbSelectCount;    // 0x140975968
extern uint32_t g_RepDbInsertCount;    // 0x14097596c
extern uint32_t g_RepDbUpdateCount;    // 0x140975970
extern uint32_t g_RepDbDeleteCount;    // 0x140975974
extern uint64_t g_RepDbSelectTotal;    // 0x140975978
extern uint64_t g_RepDbInsertTotal;    // 0x140975980
extern uint64_t g_RepDbSelectMax;      // 0x140975988
extern uint64_t g_RepDbInsertMax;      // 0x140975990
extern uint32_t g_RepWallowSystem;     // 0x140975950
extern uint32_t g_RepAdultPlayers;     // 0x140975954
extern uint32_t g_RepHealthPlayers;    // 0x140975958
extern uint32_t g_RepFatiguedPlayers;  // 0x14097595c
extern uint32_t g_RepUnhealthyPlayers; // 0x140975960
extern int64_t  g_RepAnalystArg;       // 0x1409759a8
// build-date cache (0x1409759b8)
extern uint64_t g_RepDateCache[2];     // {DATE double,flag}
extern uint8_t  g_RepDateParsed;       // 0x1409759b0 byte
extern uint8_t  g_RepDateInitFlag;     // 0x1409759c8 bit0

struct SMSRptSeams {
    int* (*MaxPlayerGet)();            // ptr
    uint32_t (*PipeAmount)(int n);     // 14050c390
    void* (*AnalystGet)();             // Analyst()
    uint32_t (*AnalystTotalUsed)(
        void* analyst, int64_t arg);   // vt+0x18
    int64_t (*Time64)();               // _time64(0)
    int (*Localtime64S)(
        struct tm* out, const int64_t* t); // localtime64_s
    int (*SysTimeToVarDate)(
        const short* st, double* out); // Ordinal_184
    int (*VarDateToSysTime)(
        double d, short* out);         // Ordinal_185
    int (*VarDateFromStr)(
        const char16_t* w, uint32_t lcid,
        uint32_t flags, double* out);  // Ordinal_94
    int (*WidenAtoW)(const char* src,
        char16_t* dst, int dstChars);  // MB2WC(3)
    // CHECKF ERROR: fmt, "CHECK",
    // "m_pServerStatusMonitor", file, 111
    void (*LogCheckf)();
};
extern SMSRptSeams g_MSRptSeams;

// raw SYSTEMTIME: {y,mo,dow,d,h,mi,s,ms}
// (8 shorts, packed exactly as raw)
void OleParseDateStr(uint64_t* out16,
    const char* str, uint32_t lcid,
    uint32_t flags);            // 140029870
void OleDateFromTime64(
    uint64_t* out16, int64_t* t);// 140029310
void OleDateDiff(uint64_t* p1,
    uint64_t* out, uint64_t* p3);// 140029440

// the builder (14002a5a0) — matches
// the cmd-module BuildAndSend seam
void MonitorBuildAndSend(uint8_t* mon);

} // namespace msg
#endif
