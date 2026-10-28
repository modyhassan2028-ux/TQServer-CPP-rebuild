// msgserver/logthread.cpp — CLogThread::OnProcess (14001b2d0)
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <vector>
#include <string>
#include "logthread.h"
using namespace msg;
static int g_fail = 0, g_ok = 0;
#define CHECK(c, m) do { if (c) { printf("  ok %s\n", m); g_ok++; } \
    else { printf("  FAIL %s\n", m); g_fail++; } } while (0)
#define SECT(x) printf("%s\n", x)
static uint32_t g_clk = 0;
static int g_has = 0, g_left = 0, g_timer = 0, g_proc = 0, g_resync = 0;
static int g_bufLen = 0, g_portOk = 0;
static std::string g_resyncText;
static std::vector<int> g_tick;
int main() {
    SECT("lt1 CLogThread idle / resync / messages");
    uint32_t init = 0, pace = 0, wait = 0;
    CLogThread::Seams s;
    s.TimeGet = +[](int) -> uint32_t { return g_clk; };
    s.WaitMessage = +[](void*, uint32_t t) -> int { (void)t; return g_has; };
    s.GetMessage = +[](void*, int32_t, int32_t, uint32_t len, void*,
                       uint32_t* h) -> int {
        g_bufLen = (int)len;
        if (g_left <= 0) return 0;
        g_left--; h[1] = 0x44; h[2] = 0x55; return 1; };
    s.ProcessMsg = +[](void*, uint32_t a, void*, uint32_t b) {
        g_proc++; g_portOk = (a == 0x44 && b == 0x55); };
    s.OnTimer = +[](void*) { g_timer++; };
    s.WriteResync = +[](void*, void* ctx, const char* t, int f) {
        g_resync++; g_resyncText = t; g_portOk = (f == 1 && ctx != nullptr); };
    s.TickEnter = +[](int i) { g_tick.push_back(i); };
    s.TickLeave = +[](int) {};
    s.pInitFlag = &init; s.pPacing = &pace; s.pWaitTimeout = &wait;
    CLogThread lg;
    lg.m_pCtx = (void*)0xC7;
    g_clk = 3000; g_has = 0;
    CHECK(lg.OnProcess(s) == 1, "returns 1");
    CHECK(init == 1, "init once");
    CHECK(g_timer == 1, "OnTimer called with no args");
    CHECK(pace == 4000, "pacing += 1000 on normal idle");
    CHECK(wait == 2000, "tail 1000 - (3000-4000) = 2000");
    CHECK(g_resync == 0, "no resync while on time");
    CHECK(g_tick.size() == 1 && g_tick[0] == 0x3c, "only 0x3c on idle");
    SECT("lt2 resync path when the deviation passes 0x2711");
    g_clk = 200000; pace = 4000; g_resync = 0; g_resyncText.clear();
    lg.OnProcess(s);
    CHECK(g_resync == 1, "resync written once");
    CHECK(g_resyncText.find("error:: resync CLogThread::OnTimer cumulative "
                           "deviation") == 0, "RAW message text");
    CHECK(g_resyncText.find("196000ms") != std::string::npos,
          "deviation value formatted");
    CHECK(pace == 200000, "pacing reset to now");
    SECT("lt3 message pump uses a 0x800 buffer");
    g_has = 1; g_left = 3; g_proc = 0; g_tick.clear(); g_bufLen = 0;
    g_clk = 201000;
    lg.OnProcess(s);
    CHECK(g_bufLen == 0x800, "GetMessage called with 0x800");
    CHECK(g_proc == 3, "three messages processed");
    CHECK(g_portOk, "ProcessMsg(port, hdr[1], buf, hdr[2])");
    CHECK(g_tick.size() == 4 && g_tick[0] == 0x3c && g_tick[1] == 0x3d,
          "0x3d inside 0x3c, once per message");
    SECT("lt4 ProcessMsg result is ignored in RAW");
    g_has = 1; g_left = 1; g_proc = 0; g_resync = 0;
    g_clk = 202000;
    int r = lg.OnProcess(s);
    CHECK(r == 1 && g_proc == 1, "a failing ProcessMsg still returns 1");
    CHECK(g_resync == 0, "and logs nothing (RAW has no error line)");
    if (g_fail == 0) printf("LOGTHREAD-OK: %d assertions\n", g_ok);
    else printf("LOGTHREAD-FAIL\n");
    return g_fail ? 1 : 0;
}
