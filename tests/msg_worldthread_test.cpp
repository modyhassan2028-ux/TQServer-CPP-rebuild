// msgserver/worldkernel/worldkernel.cpp
//   CWorldThread::OnProcess   14002e990
//   CUserLoginThread::OnProcess 14002e580
#include <cstdio>
#include <cstdint>
#include <vector>
#include "worldkernel.h"
using namespace msg;
static int g_fail = 0, g_ok = 0;
#define CHECK(c, m) do { if (c) { printf("  ok %s\n", m); g_ok++; } \
    else { printf("  FAIL %s\n", m); g_fail++; } } while (0)
#define SECT(x) printf("%s\n", x)
static uint32_t g_clk = 10000;
static int g_has = 0, g_left = 0, g_timer = 0, g_proc = 0, g_err = 0;
static std::vector<int> g_ticks;
static uint32_t g_hdr1 = 0, g_hdr2 = 0;
static int g_waitArg = -1;
int main() {
    SECT("wt1 CWorldThread: 1000ms period, tick scopes 0x1d/0x1e/0x1f");
    uint32_t init = 0, pace = 0, wait = 0;
    int32_t sum = 0, cnt = 0, mx = 0;
    CWorldThread::Seams s;
    s.TimeGet = +[](int) -> uint32_t { return g_clk; };
    s.WaitMessage = +[](void*, uint32_t t) -> int { g_waitArg = (int)t;
        return g_has; };
    s.GetMessage = +[](void*, int32_t, int32_t, uint32_t, void*, uint32_t* h)
        -> int { if (g_left <= 0) return 0; g_left--; h[1] = 7; h[2] = 9;
        return 1; };
    s.ProcessMsg = +[](void*, uint32_t a, void*, uint32_t b) -> int {
        g_proc++; g_hdr1 = a; g_hdr2 = b; return 1; };
    s.OnTimer = +[](void*, uint32_t) { g_timer++; };
    s.LogProcessError = +[](uint32_t, uint32_t) { g_err++; };
    s.TickEnter = +[](int id) { g_ticks.push_back(id); };
    s.TickLeave = +[](int) {};
    s.pInitFlag = &init; s.pPacing = &pace; s.pWaitTimeout = &wait;
    s.pSpentSum = &sum; s.pSpentCount = &cnt; s.pSpentMax = &mx;
    CWorldThread w;
    g_clk = 10000; g_has = 0;
    CHECK(w.OnProcess(s) == 1, "returns 1");
    CHECK(init == 1, "init flag");
    CHECK(pace == 11000, "pacing = seed + 1000 (idle branch)");
    CHECK(g_timer == 1, "OnTimer on idle");
    CHECK(wait == 2000, "tail: 1000 - (10000-11000) = 2000");
    CHECK(g_ticks.size() >= 2 && g_ticks[0] == 0x1d, "0x1d opens after wait");
    CHECK(g_ticks.size() >= 2 && g_ticks[1] == 0x1f, "then 0x1f for OnTimer");
    g_ticks.clear(); g_timer = 0; g_proc = 0; g_left = 2; g_has = 1;
    g_clk = 12000; w.OnProcess(s);
    CHECK(g_proc == 2, "two messages processed");
    CHECK(g_hdr1 == 7 && g_hdr2 == 9, "ProcessMsg(port, hdr[1], buf, hdr[2])");
    CHECK(g_ticks.size() == 3 && g_ticks[0] == 0x1d && g_ticks[1] == 0x1e &&
          g_ticks[2] == 0x1e, "0x1e entered once per message inside 0x1d");
    CHECK(g_err == 0, "no error logged");
    g_left = 1; g_proc = 0; g_err = 0;
    g_timer = 0; g_has = 1;
    w.OnProcess(s);
    CHECK(g_proc == 1 && g_err == 0, "success path stays quiet");
    SECT("wt2 CWorldThread counters");
    sum = 0; cnt = 0; mx = 0; g_clk = 20000;
    w.OnProcess(s);
    CHECK(cnt == 1, "one sample");
    CHECK(sum >= 0, "sum accumulated");
    CHECK(mx >= 0, "max tracked");
    SECT("wt3 CUserLoginThread: 2000ms period, ticks 0x20/0x21/0x22");
    uint32_t linit = 0, lpace = 0, lwait = 0;
    CUserLoginThread::Seams ls;
    ls.TimeGet = +[](int) -> uint32_t { return g_clk; };
    ls.WaitMessage = +[](void*, uint32_t t) -> int { g_waitArg = (int)t;
        return g_has; };
    ls.GetMessage = +[](void*, int32_t, int32_t, uint32_t, void*, uint32_t* h)
        -> int { if (g_left <= 0) return 0; g_left--; h[1] = 3; h[2] = 4;
        return 1; };
    ls.ProcessMsg = +[](void*, uint32_t a, void*, uint32_t b) -> int {
        g_proc++; g_hdr1 = a; g_hdr2 = b; return 1; };
    ls.OnTimer = +[](void*, uint32_t) { g_timer++; };
    ls.LogProcessError = +[](uint32_t, uint32_t) { g_err++; };
    ls.TickEnter = +[](int id) { g_ticks.push_back(id); };
    ls.TickLeave = +[](int) {};
    ls.pInitFlag = &linit; ls.pPacing = &lpace; ls.pWaitTimeout = &lwait;
    CUserLoginThread u;
    g_ticks.clear(); g_timer = 0; g_proc = 0; g_err = 0;
    g_has = 0; g_clk = 50000; lwait = 777;
    CHECK(u.OnProcess(ls) == 1, "returns 1");
    CHECK(g_waitArg == 777, "wait uses the global wait slot");
    CHECK(lpace == 52000, "pacing = seed + 2000");
    CHECK(g_timer == 1, "OnTimer on idle");
    CHECK(lwait == 4000, "tail 2000 - (50000-52000) = 4000 (RAW)");
    CHECK(g_ticks.size() >= 2 && g_ticks[0] == 0x20 && g_ticks[1] == 0x22,
          "0x20 opens after wait, 0x22 for the timer");
    g_ticks.clear(); g_left = 1; g_has = 1; g_proc = 0; g_clk = 60000;
    u.OnProcess(ls);
    CHECK(g_proc == 1 && g_hdr1 == 3 && g_hdr2 == 4, "message path");
    CHECK(g_ticks.size() >= 2 && g_ticks[0] == 0x20 && g_ticks[1] == 0x21,
          "0x21 for ProcessMsg");
    g_left = 1; g_proc = 0; g_err = 0;
    ls.ProcessMsg = +[](void*, uint32_t, void*, uint32_t) -> int {
        g_proc++; return 0; };
    u.OnProcess(ls);
    CHECK(g_proc == 1 && g_err == 1, "failure logged");
    if (g_fail == 0) printf("WORLD-OK: %d assertions\n", g_ok);
    else printf("WORLD-FAIL\n");
    return g_fail ? 1 : 0;
}
