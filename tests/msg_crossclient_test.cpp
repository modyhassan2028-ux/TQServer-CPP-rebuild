// crossclient/crossclientthread.cpp — CCrossClientThread::OnProcess
// (14004c300)
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <vector>
#include "crossclientthread.h"
using namespace msg;
static int g_fail = 0, g_ok = 0;
#define CHECK(c, m) do { if (c) { printf("  ok %s\n", m); g_ok++; } \
    else { printf("  FAIL %s\n", m); g_fail++; } } while (0)
#define SECT(x) printf("%s\n", x)
struct QMsg { uint32_t id; uint32_t size; uint32_t b0; uint16_t kind;
              int32_t len; uint8_t pay[8]; };
static std::vector<QMsg> g_q;
static int g_waitArg = -1, g_localN = 0, g_sendN = 0, g_isClient = 1;
static int g_session = 5, g_sendRet = 1;
static uint32_t g_lastId = 0;
static SCrossOutPacket g_out;
static std::vector<int> g_tick;
static int Feed(void* rec) {
    if (g_q.empty()) return 0;
    QMsg m = g_q.front(); g_q.erase(g_q.begin());
    SCrossInPacket* p = (SCrossInPacket*)rec;
    memset(p, 0, sizeof *p);
    p->id = m.id; p->size = m.size;
    p->body.b0 = m.b0; p->body.kind = m.kind; p->body.len = m.len;
    memcpy(p->body.payload, m.pay, sizeof m.pay);
    return 1;
}
int main() {
    SECT("cc1 CCrossClientThread buffer pump");
    CCrossClientThread::Seams s;
    s.WaitMessage = +[](void*, uint32_t t) -> int { g_waitArg = (int)t;
        return 0; };
    s.GetMessage = +[](void*, int32_t, int32_t, uint32_t, void* r) -> int {
        return Feed(r); };
    s.ProcessLocalMsg = +[](void*, uint32_t id, SCrossBody*, uint32_t) {
        g_localN++; g_lastId = id; };
    s.IsClientBody = +[](void*, SCrossBody*) -> int { return g_isClient; };
    s.GetSession = +[](void*, SCrossBody*) -> int { return g_session; };
    s.SendBuiltPacket = +[](CCrossClientThread*, SCrossOutPacket* p) -> int {
        g_sendN++; g_out = *p; return g_sendRet; };
    s.TickEnter = +[](int i) { g_tick.push_back(i); };
    s.TickLeave = +[](int) {};
    CCrossClientThread c;
    c.m_bFlag = 1;
    g_q.clear(); g_localN = g_sendN = 0; g_tick.clear();
    CHECK(c.OnProcess(s) == 1, "empty queue returns 1");
    CHECK(g_waitArg == 0x14, "WaitMessage gets the constant 0x14");
    CHECK(g_tick.size() == 2 && g_tick[0] == 0x48 && g_tick[1] == 0x2b,
          "ticks 0x48 then 0x2b");
    SECT("cc2 local messages (id != 0x3e9)");
    QMsg m; memset(&m, 0, sizeof m);
    m.id = 0x3f1; m.size = 12;
    g_q.push_back(m);
    g_tick.clear(); g_localN = 0;
    c.OnProcess(s);
    CHECK(g_localN == 1 && g_lastId == 0x3f1, "0x3f1 dispatched");
    CHECK(g_tick.size() >= 3 && g_tick[2] == 0x2d, "0x2d scope used");
    g_q.clear(); g_localN = 0;
    m.id = 0x3fc; m.b0 = 0x9c4f; g_q.push_back(m);
    c.OnProcess(s);
    CHECK(g_localN == 1, "0x3fc with b0 == 0x9c4f passes");
    // The whole id filter is gated on *(u8*)(this+0x50) == 0 in RAW.
    c.m_bFlag = 0;
    g_q.clear(); g_localN = 0;
    m.id = 0x3fc; m.b0 = 0x1111; g_q.push_back(m);
    c.OnProcess(s);
    CHECK(g_localN == 0, "flag 0: 0x3fc with a different b0 is dropped");
    g_q.clear(); g_localN = 0;
    m.id = 0x2222; g_q.push_back(m);
    c.OnProcess(s);
    CHECK(g_localN == 0, "flag 0: unknown id dropped");
    g_q.clear(); g_localN = 0;
    m.id = 0x11173; g_q.push_back(m);
    c.OnProcess(s);
    CHECK(g_localN == 1, "flag 0: 0x11173 passes");
    g_q.clear(); g_localN = 0;
    m.id = 0x3fc; m.b0 = 0x9c4f; g_q.push_back(m);
    c.OnProcess(s);
    CHECK(g_localN == 1, "flag 0: 0x3fc with 0x9c4f passes");
    c.m_bFlag = 1;
    g_q.clear(); g_localN = 0;
    m.id = 0x2222; g_q.push_back(m);
    c.OnProcess(s);
    CHECK(g_localN == 1, "flag 1: every id reaches ProcessLocalMsg");
    SECT("cc3 client messages (id == 0x3e9)");
    g_q.clear(); g_sendN = 0; g_tick.clear();
    memset(&m, 0, sizeof m);
    m.id = 0x3e9; m.kind = 0x77; m.len = 4; m.pay[0] = 1; m.pay[1] = 2;
    m.pay[2] = 3; m.pay[3] = 4;
    g_q.push_back(m);
    c.OnProcess(s);
    CHECK(g_sendN == 1, "packet built and sent");
    CHECK(g_out.zero == 0 && g_out.ff == 0xffffffffu, "zero + 0xffffffff");
    CHECK(g_out.kind == 0x77, "kind copied");
    CHECK(g_out.total == 0x14, "total = len + 0x10");
    CHECK(g_out.v == 5, "session value in +0x04");
    CHECK(g_out.payload[0] == 1 && g_out.payload[3] == 4, "payload copied");
    CHECK(g_tick.size() >= 3 && g_tick.back() != 0, "0x2c scope present");
    g_q.clear(); g_sendN = 0; g_tick.clear();
    m.len = 0x409; g_q.push_back(m);
    c.OnProcess(s);
    CHECK(g_sendN == 0, "len+0x10 >= 0x419 -> not sent (RAW guard)");
    g_q.clear(); g_sendN = 0;
    m.len = 4; g_isClient = 0; g_q.push_back(m);
    c.OnProcess(s);
    CHECK(g_sendN == 0, "IsClientBody false -> no send");
    g_isClient = 1; g_session = 0; g_q.push_back(m);
    c.OnProcess(s);
    CHECK(g_sendN == 0, "no session -> no send");
    g_session = 5; c.m_bFlag = 0; g_q.push_back(m);
    c.OnProcess(s);
    CHECK(g_sendN == 0, "flag 0 -> client path skipped");
    c.m_bFlag = 1;
    SECT("cc4 send failure ends the pass");
    g_q.clear(); g_sendN = 0; g_tick.clear(); g_sendRet = 0;
    g_q.push_back(m);
    CHECK(c.OnProcess(s) == 1, "still returns 1");
    CHECK(g_sendN == 1, "send attempted once");
    CHECK(g_q.empty(), "remaining queue not drained after the failure");
    g_sendRet = 1;
    if (g_fail == 0) printf("CROSSCLIENT-OK: %d assertions\n", g_ok);
    else printf("CROSSCLIENT-FAIL\n");
    return g_fail ? 1 : 0;
}
