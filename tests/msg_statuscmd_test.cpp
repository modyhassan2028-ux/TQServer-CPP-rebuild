// Path-A wave 8a test — monitor cmd
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include "MsgStatusMonitorCmd.h"
using namespace msg;

// ---- seams ----
static std::vector<void*> s_allocs;
static std::vector<size_t> s_szAllocs;
static size_t s_lastAlloc = 0;
static bool T_HadAlloc(size_t n) {
    for (size_t i = 0; i < s_szAllocs.size(); i++)
        if (s_szAllocs[i] == n) return true;
    return false;
}
static void* T_New(size_t n) {
    void* p = std::malloc(n ? n : 1);
    s_allocs.push_back(p);
    s_szAllocs.push_back(n);
    s_lastAlloc = n;
    return p;
}
static void T_Del(void* p) {
    // remove from the live set so Reset
    // never double-frees grown-away bufs
    for (size_t i = 0; i < s_allocs.size(); i++)
        if (s_allocs[i] == p) {
            s_allocs[i] = nullptr;
            break;
        }
    std::free(p);
}
static char s_aLog[4][300]; static int s_nLog;
static void T_Log(const char* f) {
    std::snprintf(s_aLog[s_nLog < 4 ? s_nLog++ : 3], 299, "%s", f);
}
static uint32_t s_t;
static uint32_t T_Time() { return s_t; }
static int64_t s_crash = 0;
static int64_t* T_Crash() { return &s_crash; }
struct SSend { uint64_t sock; uint32_t len;
               char buf[8]; uint32_t sent; };
static SSend s_aSend[8]; static int s_nSend;
static int T_Send(uint64_t s, uint32_t l,
        const uint8_t* b, uint32_t* n) {
    SSend& d = s_aSend[s_nSend < 8 ? s_nSend++ : 7];
    d.sock = s; d.len = l;
    std::memcpy(d.buf, b, l); d.sent = l;
    *n = l; return 0;
}
static int s_nCS;
static void T_CS(void*) { s_nCS++; }
static void T_InitCS(void*) {}
static void T_DelCS(void*) {}
static void T_CloseH(uint64_t) {}
static void* s_pMain = (void*)0x99;
static uint32_t s_closeFlag = 0;
static void T_Close(void* m, uint32_t f) {
    assert(m == s_pMain && f == 3);
    s_closeFlag++;
}
static int s_nBuild;
static void T_Build(uint8_t* m) {
    assert(m != nullptr); s_nBuild++;
}
static int s_nAbort;
static void T_Abort() { s_nAbort++; std::exit(7); }

static uint8_t* s_mon = nullptr;

static void Reset() {
    for (void* p : s_allocs) if (p) std::free(p);
    s_allocs.clear(); s_szAllocs.clear(); s_lastAlloc = 0;
    s_nLog = 0; s_t = 1000000;
    s_crash = 0; s_nSend = 0; s_nCS = 0;
    s_closeFlag = 0; s_nBuild = 0;
    s_nAbort = 0;
    std::memset(&g_MSCmdSeams, 0, sizeof g_MSCmdSeams);
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
    g_MSCmdSeams.BuildAndSend = T_Build;
    g_MSCmdSeams.InvalidParam = T_Abort;
    g_pStatusMonitor = nullptr;
    g_ResetDbState = 0;
}

// client entry {sock, offset, buf[...]}
static uint8_t s_cli[64];
static void SetCmd(const char* cmd) {
    std::memset(s_cli, 0, sizeof s_cli);
    *(uint64_t*)(s_cli + 0) = 0x1234;
    size_t n = std::strlen(cmd);
    std::memcpy(s_cli + 0xc, cmd, n);
    *(uint32_t*)(s_cli + 8) = (uint32_t)n;
}

int main() {
    printf("TH8 start\n"); fflush(stdout);

    // ==== S1: create + ctor layout ====
    {
        Reset();
        assert(MonitorCreate(s_pMain) == 1);
        s_mon = g_pStatusMonitor;
        assert(s_mon != nullptr);
        assert(T_HadAlloc(0x70));
        assert(MQ(s_mon, 0x00) == (uint64_t)s_pMain);
        assert(MD(s_mon, 0x08) == 0);
        assert(MD(s_mon, 0x0c) == 0);
        assert(MQ(s_mon, 0x28) == 0);   // first
        assert(MQ(s_mon, 0x30) == 0);   // last
        assert(MQ(s_mon, 0x38) == 0);   // cap
        assert(MQ(s_mon, 0x68) == 0);
        // proxy: alloc(8), *proxy = mon+0x10
        uint64_t proxy = MQ(s_mon, 0x10);
        assert(proxy != 0);
        assert(*(uint64_t*)proxy ==
            (uint64_t)(s_mon + 0x10));
        // second create is a no-op
        assert(MonitorCreate((void*)5) == 1);
        assert(g_pStatusMonitor == s_mon);
        printf("S1 ok (create)\n"); fflush(stdout);
    }

    // ==== S2: get_run_info — first
    // (empty) push, no crash -> state=2
    // + next=t/1000, NO reply, offset=0
    // ====
    {
        Reset();
        MonitorCreate(s_pMain);
        s_mon = g_pStatusMonitor;
        SetCmd("get_run_info\r\n");
        MonitorHandleCmd(s_mon, s_cli);
        // vector now holds the socket
        assert(MON_LAST(s_mon) ==
            MON_FIRST(s_mon) + 8);
        assert(*(uint64_t*)MON_FIRST(s_mon)
               == 0x1234);
        assert(s_nSend == 0);   // no reply
        assert(MD(s_mon, 0x08) == 2);
        assert(MD(s_mon, 0x0c) ==
            s_t / 1000);
        assert(*(uint32_t*)(s_cli + 8) == 0);
        assert(s_nBuild == 0);   // no crash
        assert(s_nCS == 2);   // enter+leave
        printf("S2 ok (get_run_info first)\n"); fflush(stdout);
    }

    // ==== S3: get_run_info — dedup
    // (same socket NOT re-added) + a
    // different socket added; crashed ->
    // builder runs ====
    {
        Reset();
        MonitorCreate(s_pMain);
        s_mon = g_pStatusMonitor;
        SetCmd("get_run_info\r\n");
        MonitorHandleCmd(s_mon, s_cli);
        SetCmd("get_run_info\r\n");   // re-arm
        MonitorHandleCmd(s_mon, s_cli);   // dup
        assert(MON_LAST(s_mon) ==
            MON_FIRST(s_mon) + 8);   // 1
        // another socket
        *(uint64_t*)s_cli = 0x5678;
        s_crash = 42;   // crashed
        std::memcpy(s_cli + 0xc,
            "get_run_info\r\n", 14);
        *(uint32_t*)(s_cli + 8) = 14;
        MonitorHandleCmd(s_mon, s_cli);
        assert(MON_LAST(s_mon) ==
            MON_FIRST(s_mon) + 16);
        assert(s_nBuild == 1);
        // crashed: state pair untouched
        assert(MD(s_mon, 0x08) == 2);
        printf("S3 ok (dedup + crash)\n"); fflush(stdout);
    }

    // ==== S4: partial command waits;
    // long garbage resets offset ====
    {
        Reset();
        MonitorCreate(s_pMain);
        s_mon = g_pStatusMonitor;
        SetCmd("get_r");   // no CRLF, <3? no 5 chars
        MonitorHandleCmd(s_mon, s_cli);
        // len 5, no CRLF, <0x1f -> wait
        assert(*(uint32_t*)(s_cli + 8) == 5);
        // 3 chars without CRLF
        SetCmd("abc");
        MonitorHandleCmd(s_mon, s_cli);
        assert(*(uint32_t*)(s_cli + 8) == 3);
        // 0x1f no-CRLF -> drop (reset)
        SetCmd("012345678901234567890123456789012");
        assert(std::strlen("012345678901234567890123456789012") == 0x21);
        MonitorHandleCmd(s_mon, s_cli);
        assert(*(uint32_t*)(s_cli + 8) == 0);
        assert(s_nSend == 0);
        printf("S4 ok (partial)\n"); fflush(stdout);
    }

    // ==== S5: close_server -> event(3)
    // + OK reply; main==0 -> silent return
    // reset_crash_state -> crash zeroed +
    // OK; reset_dbserver_state -> flag
    // zeroed + OK; unknown -> "\r\n" (2)
    // ====
    {
        Reset();
        MonitorCreate(s_pMain);
        s_mon = g_pStatusMonitor;
        SetCmd("close_server\r\n");
        MonitorHandleCmd(s_mon, s_cli);
        assert(s_closeFlag == 1);
        assert(s_nSend == 1);
        assert(s_aSend[0].len == 4 &&
               std::memcmp(s_aSend[0].buf, "OK\r\n", 4) == 0);
        // reset crash
        s_crash = 555;
        SetCmd("reset_crash_state\r\n");
        MonitorHandleCmd(s_mon, s_cli);
        assert(s_crash == 0);
        assert(s_aSend[1].len == 4);
        // crash==0 path also replies OK
        SetCmd("reset_crash_state\r\n");
        MonitorHandleCmd(s_mon, s_cli);
        assert(s_aSend[2].len == 4);
        // reset dbserver state
        g_ResetDbState = 9;
        SetCmd("reset_dbserver_state\r\n");
        MonitorHandleCmd(s_mon, s_cli);
        assert(g_ResetDbState == 0);
        assert(s_aSend[3].len == 4);
        // unknown command -> 2-byte \r\n
        SetCmd("hello\r\n");
        MonitorHandleCmd(s_mon, s_cli);
        assert(s_aSend[4].len == 2);
        assert(std::memcmp(s_aSend[4].buf, "\r\n", 2) == 0);
        // close_server with no main ->
        // silent (no event, no reply)
        MQ(s_mon, 0x00) = 0;
        s_closeFlag = 0;
        SetCmd("close_server\r\n");
        MonitorHandleCmd(s_mon, s_cli);
        assert(s_closeFlag == 0);
        assert(s_nSend == 5);
        assert(*(uint32_t*)(s_cli + 8) == 0);
        printf("S5 ok (commands)\n"); fflush(stdout);
    }

    // ==== S6: vector growth — push past
    // capacity (raw insert_n branch 1 +
    // realloc 1.5x); then clear ====
    {
        Reset();
        MonitorCreate(s_pMain);
        s_mon = g_pStatusMonitor;
        SetCmd("get_run_info\r\n");
        // push 3 distinct sockets via the
        // handler dedup path (each under
        // CS). crash=0 keeps state logic
        for (uint64_t sk = 10; sk < 13;
             sk++) {
            *(uint64_t*)s_cli = sk;
            std::memcpy(s_cli + 0xc,
                "get_run_info\r\n", 14);
            *(uint32_t*)(s_cli + 8) = 14;
            MonitorHandleCmd(s_mon, s_cli);
        }
        assert(MON_LAST(s_mon) -
            MON_FIRST(s_mon) == 24);
        assert(*(uint64_t*)(MON_FIRST(s_mon)+16) == 12);
        // cap grew: 0 -> 1 slot? raw
        // branch1 with capSize 0: newCap
        // 0 -> max(0,1)=1... first push
        // grew to 1, second to 2 (1.5x
        // -> 1), etc. check >= 3 slots
        assert((MON_CAP(s_mon) -
            MON_FIRST(s_mon)) / 8 >= 3);
        // clear -> last = first
        VecClear(s_mon + 0x10);
        assert(MON_LAST(s_mon) ==
            MON_FIRST(s_mon));
        printf("S6 ok (growth)\n"); fflush(stdout);
    }

    // ==== S7: timer-check — next != 0
    // and next+interval <= now/1000 ->
    // zero + builder ====
    {
        Reset();
        MonitorCreate(s_pMain);
        s_mon = g_pStatusMonitor;
        MD(s_mon, 0x0c) = 100;   // next
        MD(s_mon, 0x08) = 2;     // interval
        s_t = 103 * 1000;        // now/1000=103
        MonitorTimerCheck(s_mon);
        assert(s_nBuild == 1);
        assert(MD(s_mon, 0x0c) == 0);
        assert(MD(s_mon, 0x08) == 0);
        // too early -> nothing
        MD(s_mon, 0x0c) = 100;
        MD(s_mon, 0x08) = 2;
        s_t = 101 * 1000;
        MonitorTimerCheck(s_mon);
        assert(s_nBuild == 1);
        assert(MD(s_mon, 0x0c) == 100);
        // null monitor -> log error only
        MonitorTimerCheck(nullptr);
        assert(s_nLog == 1);
        printf("S7 ok (timer)\n"); fflush(stdout);
    }

    // ==== S8: shutdown frees everything
    // + handler with null monitor logs
    // ====
    {
        Reset();
        MonitorCreate(s_pMain);
        s_mon = g_pStatusMonitor;
        SetCmd("get_run_info\r\n");
        MonitorHandleCmd(s_mon, s_cli);
        size_t nBefore = s_allocs.size();
        MonitorShutdown();
        assert(g_pStatusMonitor == nullptr);
        // all frees happened (del proxy,
        // buf, self) - can't easily count
        // dels, but re-create works after
        assert(MonitorCreate(s_pMain) == 1);
        assert(nBefore >= 3);
        // null-monitor handler
        MonitorHandleCmd(nullptr, s_cli);
        assert(s_nLog >= 1);
        printf("S8 ok (shutdown)\n"); fflush(stdout);
    }

    printf("TH8 ALL-OK\n");
    return 0;
}
