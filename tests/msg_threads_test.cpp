// The thread module batch: CAnalystProfile (14001e720),
// CChatThread (1400011b0), CMapGroupThread (14001d530),
// CSocketThread (14002bbe0 + 14002bd30).
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <vector>
#include <string>
#include "CAnalystProfile.h"
#include "CChatThread.h"
#include "CMapGroupThread.h"
#include "CSocketThread.h"
using namespace msg;
static int g_fail = 0, g_ok = 0;
#define CHECK(c, m) do { if (c) { printf("  ok %s\n", m); g_ok++; } \
    else { printf("  FAIL %s\n", m); g_fail++; } } while (0)
#define SECT(x) printf("%s\n", x)
// ---- analyst ----
static std::vector<int> s_ids; static std::vector<std::string> s_txt;
static std::string s_file; static int s_analystCalls = 0;
int main() {
    SECT("th1 CAnalystProfile::RegisterAll (14001e720)");
    CAnalystProfile::Seams as;
    as.Analyst = +[]() -> void* { s_analystCalls++; return (void*)0xA; };
    as.SetLogFile = +[](void*, const char* f) { s_file = f; };
    as.AddItem = +[](void*, int id, int flag, const char* t) {
        s_ids.push_back(id); s_txt.push_back(t);
        if (flag != 1) s_ids.push_back(-999); };
    CAnalystProfile::RegisterAll(as);
    CHECK(s_file == "syslog/analyst", "log file path");
    CHECK(CAnalystProfile::kItemCount == 76, "76 rows from the RAW");
    CHECK((int)s_ids.size() == 76, "every row added once");
    CHECK(s_analystCalls == 1 + 76, "Analyst() re-called per row");
    CHECK(s_txt[0] == "CMapGroupThread::OnProcess", "row 0");
    bool foundChat = false, foundAuc = false, foundLog = false;
    for (size_t i = 0; i < s_txt.size(); ++i) {
        if (s_txt[i] == "CChatThread::OnProcess") foundChat = true;
        if (s_txt[i] == "CAuctionSearchThread WaitMsg") foundAuc = true;
        if (s_txt[i] == "`-CLogThread ProcessMsg") foundLog = true;
    }
    CHECK(foundChat, "CChatThread::OnProcess row present");
    CHECK(foundAuc, "CAuctionSearchThread WaitMsg present");
    CHECK(foundLog, "`-CLogThread ProcessMsg present");
    CHECK(s_txt[72] == "CAuctionSearchThread WaitMsg", "row 72");
    CHECK(s_txt[75] == "`-CLogThread ProcessMsg", "last row");
    int badFlag = 0; for (int i = 0; i < (int)s_ids.size(); ++i)
        if (s_ids[i] == -999) badFlag++;
    CHECK(badFlag == 0, "every AddItem used flag 1");
    SECT("th2 CChatThread::OnProcess (1400011b0)");
    static uint32_t s_clk = 100000, s_pace = 0, s_wait = 500;
    static uint32_t s_init = 0;
    static int s_timerN = 0, s_procN = 0, s_waitN = 0, s_waitArg = -1;
    static int s_getN = 0, s_getsLeft = 0, s_procOk = 1, s_errLog = 0;
    static uint32_t s_procHdr1 = 0, s_procHdr2 = 0;
    static std::vector<int> s_tickSeq;
    CChatThread::Seams cs;
    cs.TimeGet = +[](int) -> uint32_t { return s_clk; };
    cs.WaitMessage = +[](void*, uint32_t t) -> int { s_waitN++;
        s_waitArg = (int)t; return s_getsLeft > 0 ? 1 : 0; };
    cs.GetMessage = +[](void*, int32_t, int32_t, uint32_t, void*, uint32_t* h)
        -> int { if (s_getsLeft <= 0) return 0; s_getsLeft--; s_getN++;
        h[1] = 0x1234; h[2] = 0x40; return 1; };
    cs.ProcessMsg = +[](void*, uint32_t h1, void*, uint32_t h2) -> int {
        s_procN++; s_procHdr1 = h1; s_procHdr2 = h2; return s_procOk; };
    cs.OnTimer = +[](void*, uint32_t) { s_timerN++; };
    cs.LogProcessError = +[](uint32_t, uint32_t) { s_errLog++; };
    cs.TickEnter = +[](int id) { s_tickSeq.push_back(id); };
    cs.TickLeave = +[](int) {};
    cs.pInitFlag = &s_init; cs.pPacing = &s_pace;
    cs.pWaitTimeout = &s_wait;
    CChatThread ch;
    CHECK(ch.OnProcess(cs) == 1, "returns 1");
    CHECK(s_init == 1, "init flag set once");
    // idle branch bumps the pacing by the period, so after one pass
    // it is seed + 2000
    CHECK(s_pace == 102000, "pacing seeded then +2000 (RAW order)");
    CHECK(s_waitN == 1 && s_waitArg == 500, "WaitMessage gets s+0x20");
    CHECK(s_timerN == 1 && s_procN == 0, "no msg -> OnTimer");
    CHECK(s_pace == 102000, "catch-up adds 2000ms");
    // RAW: the idle branch already moved the pacing ahead, so the
    // tail computes 2000 - (now - pacing) = 2000 + 2000 = 4000
    CHECK(s_wait == 4000, "wait 4000 because pacing is ahead (RAW)");
    CHECK(s_tickSeq.size() == 3 && s_tickSeq[0] == 0x49 &&
          s_tickSeq[1] == 0x2f && s_tickSeq[2] == 0x31,
          "tick order 0x49, 0x2f (body), 0x31 (timer)");
    s_timerN = s_procN = s_getN = s_errLog = 0; s_tickSeq.clear();
    s_getsLeft = 1; s_clk = 102000; s_wait = 2000;
    ch.OnProcess(cs);
    CHECK(s_procN == 1 && s_timerN == 0, "message path");
    CHECK(s_procHdr1 == 0x1234 && s_procHdr2 == 0x40,
          "ProcessMsg(port, hdr[1], buf, hdr[2])");
    CHECK(s_tickSeq.size() >= 3 && s_tickSeq[2] == 0x30,
          "0x30 ticks around ProcessMsg");
    s_getsLeft = 1; s_procOk = 0; s_procN = 0; s_errLog = 0;
    ch.OnProcess(cs);
    CHECK(s_procN == 1 && s_errLog == 1, "failure logged");
    s_procOk = 1; s_getsLeft = 0; s_clk = 200000; s_pace = 100000;
    s_wait = 0;
    ch.OnProcess(cs);
    CHECK(s_pace == 200000, "far behind -> pacing resets to now");
    s_clk = 300000; s_pace = 300000;
    ch.OnProcess(cs);
    CHECK(s_pace == 302000, "on-time idle still bumps by 2000");
    CHECK(s_wait == 4000, "and the tail yields 4000 (RAW double)");
    SECT("th3 CMapGroupThread::OnProcess (14001d530)");
    static uint32_t m_clk = 5000, m_pace = 0, m_wait = 0, m_init = 0;
    static int m_idx = 0x0e; static int m_timer = 0, m_proc = 0;
    static int32_t m_sum[8] = {}, m_cnt[8] = {}, m_max[8] = {};
    CMapGroupThread::Seams ms;
    ms.TimeGet = +[](int) -> uint32_t { return m_clk; };
    ms.WaitMessage = +[](void*, uint32_t) -> int { return 0; };
    ms.GetMessage = +[](void*, int32_t, int32_t, uint32_t, void*, uint32_t*)
        -> int { return 0; };
    ms.ProcessMsg = +[](void*, uint32_t, void*, uint32_t) -> int {
        m_proc++; return 1; };
    ms.OnTimer = +[](void*, uint32_t) { m_timer++; };
    ms.GetKernelIndex = +[](void*) -> int { return m_idx; };
    ms.LogProcessError = +[](uint32_t, uint32_t) {};
    ms.TickEnter = +[](int) {}; ms.TickLeave = +[](int) {};
    ms.pInitFlag = &m_init; ms.pPacing = &m_pace;
    ms.pWaitTimeout = &m_wait;
    ms.pSpentSum = m_sum; ms.pSpentCount = m_cnt; ms.pSpentMax = m_max;
    CMapGroupThread mg;
    for (int i = 0; i < 8; ++i) { m_sum[i] = m_cnt[i] = m_max[i] = 0; }
    m_idx = 0x0e; m_clk = 5000;
    CHECK(mg.OnProcess(ms) == 1, "returns 1");
    CHECK(m_timer == 1, "OnTimer when idle");

    CHECK(m_pace == 5000 + 0x7d, "pacing advanced by 0x7d");
    CHECK(m_cnt[0] == 1 && m_sum[0] == 0,
          "slot 0 counted with 0 ms spent");
    m_idx = 0x12;                       // 0x12 - 0xe = 4 -> last slot
    m_clk = 6000; mg.OnProcess(ms);
    CHECK(m_cnt[4] == 1, "index 0x12 maps to slot 4");
    m_idx = 0x13; m_cnt[5] = 0; m_clk = 7000;
    mg.OnProcess(ms);
    CHECK(m_cnt[5] == 0, "index 0x13 is out of the 5 slots");
    m_sum[1] = 0; m_cnt[1] = 0; m_max[1] = 0;
    m_idx = 0x0f; m_clk = 9000;
    mg.OnProcess(ms);
    CHECK(m_cnt[1] == 1, "slot 1 counted");
    CHECK(m_max[1] >= 0, "max tracked");
    SECT("th4 CSocketThread::CreateThread (14002bbe0)");
    static int s_base = 1, s_attach = 1, s_mb = 0;
    CSocketThread::Seams ss;
    memset(&ss, 0, sizeof ss);
    ss.BaseCreateThread = +[](void*, const char* n, int) -> int {
        return (n && strcmp(n, "SocketThread") == 0) ? s_base : 0; };
    ss.GetSocketKernel = +[]() -> void* { return (void*)0x90; };
    ss.KernelAttach = +[](void*, void*, void*) -> int { return s_attach; };
    ss.MessageBox = +[](void*, const char*, const char*, unsigned) {
        s_mb++; };
    ss.TimeGet = +[](int) -> uint32_t { return 1000; };
    ss.WaitMessage = +[](void*, uint32_t) -> int { return 0; };
    ss.GetMessage = +[](void*, int32_t, int32_t, uint32_t, void*, uint32_t*)
        -> int { return 0; };
    ss.ProcessMsg = +[](void*, uint32_t, void*, uint32_t) -> int { return 1; };
    ss.OnTimer = +[](void*, uint32_t) {};
    ss.LogProcessError = +[](uint32_t, uint32_t) {};
    ss.TickEnter = +[](int) {}; ss.TickLeave = +[](int) {};
    static uint32_t c_init = 0, c_pace = 0, c_wait = 0;
    static int32_t c_sum = 0, c_cnt = 0, c_max = 0;
    ss.pInitFlag = &c_init; ss.pPacing = &c_pace;
    ss.pWaitTimeout = &c_wait;
    ss.pSpentSum = &c_sum; ss.pSpentCount = &c_cnt; ss.pSpentMax = &c_max;
    CSocketThread st;
    s_base = 1; s_attach = 1; s_mb = 0;
    CHECK(st.CreateThread(1, ss) == 1, "created");
    CHECK(s_mb == 0, "no message box on success");
    s_attach = 0; s_mb = 0;
    CHECK(st.CreateThread(1, ss) == 0, "attach failure -> 0");
    CHECK(s_mb == 1, "the RAW message box shown");
    s_base = 0; s_mb = 0;
    CHECK(st.CreateThread(1, ss) == 0, "base failure -> 0");
    CHECK(s_mb == 0, "and no message box (RAW returns early)");
    SECT("th5 CSocketThread::OnProcess (14002bd30)");
    c_sum = c_cnt = c_max = 0;
    CHECK(st.OnProcess(ss) == 1, "returns 1");
    CHECK(c_init == 1, "init once");
    CHECK(c_cnt == 1, "one sample counted");
    CHECK(c_sum >= 0, "spent accumulated");
    if (g_fail == 0) printf("THREADS-OK: %d assertions\n", g_ok);
    else printf("THREADS-FAIL\n");
    return g_fail ? 1 : 0;
}
