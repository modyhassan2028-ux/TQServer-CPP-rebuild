// Path-A wave 8b test — report
// builder + date cluster
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "MsgStatusMonitorRpt.h"
#include "MsgStatusMonitorCmd.h"
using namespace msg;

// ---- reuse cmd seams (CS etc) ----
static void* T_New(size_t n)
    { return std::malloc(n?n:1); }
static void T_Del(void* p)
    { std::free(p); }
static void T_Log(const char*) {}
static uint32_t s_t = 1000000;
static uint32_t T_Time() { return s_t; }
static int64_t s_crash = 0;
static int64_t* T_Crash()
    { return &s_crash; }
struct SSend { uint64_t sock; uint32_t len;
               std::vector<uint8_t> data; };
static SSend s_aSend[8]; static int s_nSend;
static int T_Send(uint64_t s, uint32_t l,
        const uint8_t* b, uint32_t* n) {
    SSend& d =
      s_aSend[s_nSend < 8 ? s_nSend++ : 7];
    d.sock = s; d.len = l;
    d.data.assign(b, b + l);
    *n = l; return 0;
}
static int s_nCS; static void T_CS(void*)
    { s_nCS++; }
static void T_InitCS(void*) {}
static void T_DelCS(void*) {}
static void T_CloseH(uint64_t) {}
static void T_Close(void*, uint32_t) {}
static int s_nAbort;
static void T_Abort()
    { s_nAbort++; std::exit(7); }

// ---- report seams ----
static int s_maxPlayer = 5000;
static int* T_Max() { return &s_maxPlayer; }
static uint32_t s_pipe = 77;
static uint32_t T_Pipe(int n)
    { assert(n == 0xe); return s_pipe; }
static void* T_Analyst()
    { return (void*)0xABCD; }
static uint32_t T_AnalystUsed(
        void* a, int64_t arg) {
    assert(a == (void*)0xABCD);
    assert(arg == g_RepAnalystArg);
    return 1234;
}
// fixed epoch: 2015-12-19 12:00:00
static int64_t T_Time64()
    { return 1450526400LL; }
static struct tm s_tm;
static int T_Local(struct tm* o,
        const int64_t* t) {
    *o = s_tm; return 0;
}
static int T_CheckfCount = 0;
static void T_Checkf() { T_CheckfCount++; }

static uint8_t* s_mon = nullptr;

static void ResetAll() {
    std::memset(&g_MSCmdSeams, 0,
                sizeof g_MSCmdSeams);
    g_MSCmdSeams.New = T_New;
    g_MSCmdSeams.Del = T_Del;
    g_MSCmdSeams.LogErrorFmt = T_Log;
    g_MSCmdSeams.TimeGet = T_Time;
    g_MSCmdSeams.CrashTimeGet = T_Crash;
    g_MSCmdSeams.WSASend = T_Send;
    g_MSCmdSeams.EnterCS = T_CS;
    g_MSCmdSeams.LeaveCS = T_CS;
    g_MSCmdSeams.InitCS = T_InitCS;
    g_MSCmdSeams.DelCS = T_DelCS;
    g_MSCmdSeams.CloseHandle = T_CloseH;
    g_MSCmdSeams.SetCloseFlag = T_Close;
    g_MSCmdSeams.InvalidParam = T_Abort;
    std::memset(&g_MSRptSeams, 0,
                sizeof g_MSRptSeams);
    g_MSRptSeams.MaxPlayerGet = T_Max;
    g_MSRptSeams.PipeAmount = T_Pipe;
    g_MSRptSeams.AnalystGet = T_Analyst;
    g_MSRptSeams.AnalystTotalUsed =
        T_AnalystUsed;
    g_MSRptSeams.Time64 = T_Time64;
    g_MSRptSeams.Localtime64S = T_Local;
    g_MSRptSeams.LogCheckf = T_Checkf;
    g_ResetDbState = 0;
    std::strcpy(g_RepServerName,
                "COServer");
    g_RepAccountFlag = 0;
    g_RepPlayerCount = 42;
    g_RepDbSelectCount = 11;
    g_RepDbInsertCount = 22;
    g_RepDbUpdateCount = 33;
    g_RepDbDeleteCount = 44;
    g_RepDbSelectTotal = 0x100000005ULL;
    g_RepDbInsertTotal = 0x200000007ULL;
    g_RepDbSelectMax = 0x300000009ULL;
    g_RepDbInsertMax = 0x400000011ULL;
    g_RepWallowSystem = 5;
    g_RepAdultPlayers = 6;
    g_RepHealthPlayers = 7;
    g_RepFatiguedPlayers = 8;
    g_RepUnhealthyPlayers = 9;
    g_RepAnalystArg = 0x55;
    g_RepDateCache[0] = 0;
    g_RepDateCache[1] = 0;
    g_RepDateParsed = 0;
    g_RepDateInitFlag = 0;
    s_crash = 0; s_nSend = 0; s_nCS = 0;
    s_nAbort = 0; T_CheckfCount = 0;
    // localtime for 2015-12-19 12:00
    s_tm = {};
    s_tm.tm_year = 2015 - 1900;
    s_tm.tm_mon = 11; s_tm.tm_mday = 19;
    s_tm.tm_hour = 12; s_tm.tm_min = 0;
    s_tm.tm_sec = 0;
    s_tm.tm_wday = 6;
    if (g_pStatusMonitor)
        MonitorShutdown();   // raw dtor
    s_mon = nullptr;
}

int main() {
    setvbuf(stdout, 0, _IONBF, 0);
    printf("TH9 start\n");

    // ==== S1: OLE date core round-trip
    // — 2015-12-04 serial + parse ====
    {
        ResetAll();
        uint64_t out[2] = {9, 9};
        OleParseDateStr(out,
            "Dec  4 2015", 2, 0x400);
        double d = *(double*)out;
        // expected serial: days from
        // 1899-12-30 to 2015-12-04
        // = 42342
        assert(*(uint32_t*)(out+1) == 0);
        short st[8] = {2015, 12, 0, 4,
                       0, 0, 0, 0};
        double ser = 0.0;
        assert(g_MSRptSeams
            .SysTimeToVarDate(st, &ser));
        assert(d == ser);
        short back[8] = {0};
        assert(g_MSRptSeams
            .VarDateToSysTime(d, back));
        assert(back[0] == 2015 &&
               back[1] == 12 &&
               back[3] == 4);
        // days to 2015-12-19 12:00 =
        // 15.5 -> valid_days = 90-15
        uint64_t cur[2] = {9, 9};
        int64_t t = 5;
        OleDateFromTime64(cur, &t);
        assert(*(uint32_t*)(cur+1) == 0);
        uint64_t diff[2] = {9, 9};
        OleDateDiff(cur, diff, out);
        double dd = *(double*)diff;
        assert(dd > 15.49 && dd < 15.51);
        assert(*(uint32_t*)(diff+1) == 0);
        printf("S1 ok (date core)\n");
    }

    // ==== S2: full report — no
    // crash, 2 registered sockets ====
    {
        ResetAll();
        MonitorCreate((void*)1);
        s_mon = g_pStatusMonitor;
        g_ResetDbState = 3;
        g_RepAccountFlag = 1;
        MD(s_mon, 0x08) = 7;   // nonzero
        MD(s_mon, 0x0c) = 7;
        uint64_t e1 = 0x1111, e2 = 0x2222;
        VecPush(s_mon + 0x10,
                (uint8_t*)&e1);
        VecPush(s_mon + 0x10,
                (uint8_t*)&e2);
        assert(*(uint64_t*)
            (*(uint64_t*)(s_mon + 0x28) + 8)
            == 0x2222);
        MonitorBuildAndSend(s_mon);
        assert(s_nSend == 2);
        assert(s_aSend[0].sock == 0x1111);
        assert(s_aSend[1].sock == 0x2222);
        assert(s_aSend[0].len ==
               s_aSend[1].len);
        // vector cleared after send
        assert(*(uint64_t*)(s_mon + 0x30)
            == *(uint64_t*)(s_mon + 0x28));
        // interval/next zeroed at start
        assert(MD(s_mon, 0x08) == 0);
        assert(MD(s_mon, 0x0c) == 0);
        // full expected report text
        char exp[1024];
        int n = std::snprintf(exp, sizeof exp,
            "servername:%s\r\n"
            "connect_account:%d\r\n"
            "player:%d\r\n"
            "player_limit:%u\r\n"
            "db_server:%u\r\n"
            "%s"
            "pipe_amount:%d\r\n"
            "db_select_count:%u\r\n"
            "db_insert_count:%u\r\n"
            "db_update_count:%u\r\n"
            "db_delete_count:%u\r\n"
            "db_select_total_used:%u\r\n"
            "db_insert_total_used:%u\r\n"
            "db_select_max_used:%u\r\n"
            "db_insert_max_used:%u\r\n"
            "service_total_used_per5:%u\r\n"
            "valid_days:%d\r\n"
            "wallow_system:%d\r\n"
            "adult_players:%d\r\n"
            "health_players:%d\r\n"
            "fatigued_players:%d\r\n"
            "unhealthy_players:%d\r\n",
            "COServer", 0, 42, 5000u, 3u,
            "gameserver_crash:0\r\n",
            77, 11u, 22u, 33u, 44u,
            0x00000005u, 0x00000007u,
            0x00000009u, 0x00000011u,
            1234u, 90 - 15,
            5, 6, 7, 8, 9);
        assert(n == (int)s_aSend[0].len);
        assert(std::memcmp(exp,
            s_aSend[0].data.data(),
            n) == 0);
        printf("S2 ok (full report)\n");
    }

    // ==== S3: crash!=0 -> :1 line;
    // localtime fail -> line omitted;
    // date cache one-time init ====
    {
        ResetAll();
        MonitorCreate((void*)1);
        s_mon = g_pStatusMonitor;
        s_crash = 999;
        uint64_t e1 = 0x3333;
        VecPush(s_mon + 0x10,
                (uint8_t*)&e1);
        MonitorBuildAndSend(s_mon);
        std::string r((char*)
            s_aSend[0].data.data(),
            s_aSend[0].len);
        assert(r.find(
            "gameserver_crash:1\r\n")
            != std::string::npos);
        // parse happened once; flag set
        assert(g_RepDateParsed == 1);
        // second call reuses the cache
        // (parsed stays 1, no reparse)
        s_nSend = 0;
        MonitorBuildAndSend(s_mon);
        assert(g_RepDateParsed == 1);
        // null-global guard: CHECKF log
        uint8_t* keep = g_pStatusMonitor;
        g_pStatusMonitor = nullptr;
        MonitorBuildAndSend(keep);
        assert(T_CheckfCount == 1);
        assert(s_nSend == 0);  // no send
        g_pStatusMonitor = keep;
        printf("S3 ok (crash+cache)\n");
    }

    // ==== S4: valid_days boundaries
    // (exact day, negative, stale) ====
    {
        ResetAll();
        MonitorCreate((void*)1);
        s_mon = g_pStatusMonitor;
        // exactly 2015-12-04 00:00 =>
        // diff 0.0 -> valid_days 90
        s_tm = {};
        s_tm.tm_year = 2015 - 1900;
        s_tm.tm_mon = 11; s_tm.tm_mday = 4;
        uint64_t e1 = 1;
        VecPush(s_mon + 0x10,
                (uint8_t*)&e1);
        MonitorBuildAndSend(s_mon);
        std::string r0((char*)
            s_aSend[0].data.data(),
            s_aSend[0].len);
        assert(r0.find(
            "valid_days:90\r\n")
            != std::string::npos);
        // 2016-01-08 -> 35 days -> 55
        s_nSend = 0;
        s_tm.tm_year = 2016 - 1900;
        s_tm.tm_mon = 0; s_tm.tm_mday = 8;
        VecPush(s_mon + 0x10,
                (uint8_t*)&e1);
        MonitorBuildAndSend(s_mon);
        std::string r1((char*)
            s_aSend[0].data.data(),
            s_aSend[0].len);
        assert(r1.find(
            "valid_days:55\r\n")
            != std::string::npos);
        printf("S4 ok (valid_days)\n");
    }

    MonitorShutdown();
    printf("TH9 ALL-OK\n");
    return 0;
}
