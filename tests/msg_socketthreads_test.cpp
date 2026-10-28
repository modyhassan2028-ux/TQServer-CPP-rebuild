// auctionsearchthread.cpp (1400f31f0) + ipadpaymentssocketthread.cpp
// (140510960): the two family members whose layout differs from the
// chat/socket/world shape.
#include <cstdio>
#include <cstdint>
#include <vector>
#include "auctionsearchthread.h"
#include "ipadpaymentssocketthread.h"
using namespace msg;
static int g_fail = 0, g_ok = 0;
#define CHECK(c, m) do { if (c) { printf("  ok %s\n", m); g_ok++; } \
    else { printf("  FAIL %s\n", m); g_fail++; } } while (0)
#define SECT(x) printf("%s\n", x)
static uint32_t g_clk = 1;
static int g_has = 0, g_left = 0, g_proc = 0, g_timer = 0, g_err = 0;
static uint32_t g_h1 = 0, g_h2 = 0;
static std::vector<int> g_tick;
int main() {
    SECT("au1 CAuctionSearchThread: drainer +0x40, port +0x48, slot +0x28");
    uint32_t init = 0, pace = 0, slot = 55;
    CAuctionSearchThread::Seams s;
    s.TimeGet = +[](int) -> uint32_t { return g_clk; };
    s.WaitMessage = +[](void*, uint32_t t) -> int { g_h1 = t; return g_has; };
    s.GetMessage = +[](void*, int32_t, int32_t, uint32_t, void*, uint32_t* h)
        -> int { if (g_left <= 0) return 0; g_left--; h[1] = 0x11;
        h[2] = 0x22; return 1; };
    s.ProcessMsg = +[](void*, uint32_t a, void*, uint32_t b) -> int {
        g_proc++; g_h1 = a; g_h2 = b; return 1; };
    s.OnTimer = +[](void*, uint32_t) { g_timer++; };
    s.LogProcessError = +[](uint32_t, uint32_t) { g_err++; };
    s.TickEnter = +[](int i) { g_tick.push_back(i); };
    s.TickLeave = +[](int) {};
    s.pInitFlag = &init; s.pPacing = &pace; s.pWaitTimeout = &slot;
    CAuctionSearchThread a;
    a.m_pDrainer = (void*)0xD0;
    a.m_pPort    = (void*)0xB0;
    g_clk = 100000; g_has = 0;
    CHECK(a.OnProcess(s) == 1, "returns 1");
    CHECK(g_h1 == 55, "WaitMessage uses the +0x28 slot");
    CHECK(g_timer == 1, "OnTimer from the port object");
    CHECK(pace == 102000, "period 2000 applied");
    CHECK(slot == 4000, "tail 2000 - (100000-102000) = 4000");
    CHECK(g_tick.size() == 3 && g_tick[0] == 0x4a && g_tick[1] == 0x32 &&
          g_tick[2] == 0x34, "ticks 0x4a, 0x32, 0x34");
    g_tick.clear(); g_proc = 0; g_left = 2; g_has = 1; g_clk = 104000;
    a.OnProcess(s);
    CHECK(g_proc == 2, "two messages");
    CHECK(g_h1 == 0x11 && g_h2 == 0x22, "ProcessMsg gets hdr[1]/hdr[2]");
    CHECK(g_tick.size() == 4 && g_tick[0] == 0x4a && g_tick[1] == 0x32 &&
          g_tick[2] == 0x33 && g_tick[3] == 0x33, "0x33 per message");
    g_left = 1; g_proc = 0; g_err = 0;
    s.ProcessMsg = +[](void*, uint32_t, void*, uint32_t) -> int {
        g_proc++; return 0; };
    a.OnProcess(s);
    CHECK(g_proc == 1 && g_err == 1, "failure logged");
    // the pacing is only touched on the idle branch
    g_has = 0; g_left = 0; g_clk = 200000; pace = 100000; slot = 0;
    a.OnProcess(s);
    CHECK(pace == 200000, "idle and far behind -> pacing = now");
    SECT("ip1 CIPADPaymentsSocketThread: idle branch does no work");
    uint32_t iinit = 0, ipace = 0, islot = 9;
    CIPADPaymentsSocketThread::Seams p;
    p.TimeGet = +[](int) -> uint32_t { return g_clk; };
    p.WaitMessage = +[](void*, uint32_t t) -> int { g_h1 = t; return g_has; };
    p.GetMessage = +[](void*, int32_t, int32_t, uint32_t, void*, uint32_t* h)
        -> int { if (g_left <= 0) return 0; g_left--; h[1] = 5; h[2] = 6;
        return 1; };
    p.ProcessMsg = +[](void* self, uint32_t a, void*, uint32_t b) -> int {
        g_proc++; g_h1 = a; g_h2 = b; return self != nullptr; };
    p.LogProcessError = +[](uint32_t, uint32_t) { g_err++; };
    p.TickEnter = +[](int i) { g_tick.push_back(i); };
    p.TickLeave = +[](int) {};
    p.pInitFlag = &iinit; p.pPacing = &ipace; p.pWaitTimeout = &islot;
    CIPADPaymentsSocketThread th;
    th.m_pDrainer = (void*)0xD1;
    g_clk = 5000; g_has = 0; g_tick.clear(); g_proc = 0;
    CHECK(th.OnProcess(p) == 1, "returns 1");
    CHECK(g_proc == 0, "idle: no ProcessMsg");
    CHECK(g_h1 == 9, "WaitMessage gets the global slot");
    CHECK(ipace == 6000, "period 1000");
    CHECK(islot == 2000, "tail 1000 - (5000-6000) = 2000");
    CHECK(g_tick.size() >= 2 && g_tick[0] == 0x35 && g_tick[1] == 0x37,
          "0x35 wraps, 0x37 inside it");
    g_tick.clear(); g_left = 1; g_has = 1; g_proc = 0; g_clk = 8000;
    th.OnProcess(p);
    CHECK(g_proc == 1, "one message processed");
    CHECK(g_h1 == 5 && g_h2 == 6, "hdr forwarded");
    CHECK(g_tick.size() >= 2 && g_tick[1] == 0x36, "0x36 for the message");
    if (g_fail == 0) printf("SOCKTHREADS-OK: %d assertions\n", g_ok);
    else printf("SOCKTHREADS-FAIL\n");
    return g_fail ? 1 : 0;
}
