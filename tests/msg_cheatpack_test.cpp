// Path-A wave 9i test — 140001c70 + 140002510.
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdarg>
#include <string>
#include <vector>
#include "MsgCheatMonitorPackets.h"
using namespace msg;
static int g_fail = 0, g_ok = 0;
#define CHECK(c, m) do { if (c) { printf("  ok %s\n", m); g_ok++; } \
    else { printf("  FAIL %s\n", m); g_fail++; } } while (0)
#define SECT(x) printf("%s\n", x)
static std::vector<std::string> s_logV;
static std::string s_msg;
static int s_desN = 0, s_desMode = -1, s_desLen = 0;
static int s_h30 = 0, s_h15 = 0;
static std::string s_h30First, s_h15First;
static uint16_t s_kindOfFrame = 0xFFFF;
static void TLNoArg() { s_logV.push_back("<noarg>"); }
static void TLStr(const char* s) { s_logV.push_back(s); }
static void TMsg(const char* f, ...) {
    char b[256]; va_list ap; va_start(ap, f);
    vsnprintf(b, sizeof b, f, ap); va_end(ap); s_msg = b; }
static void TDes(uint8_t* buf, int len, void*, void*, void*, int mode) {
    s_desN++; s_desMode = mode; s_desLen = len;
    for (int i = 0; i < len; ++i) buf[i] ^= 0x5A;   // visible effect
}
static void TH30(void* f) {
    s_h30++;
    char* p = (char*)f;
    s_h30First.assign(p, 4);
    s_kindOfFrame = *(uint16_t*)(p + 4); }
static void TH15(void* f) {
    s_h15++;
    char* p = (char*)f;
    s_h15First.assign(p, 4);
    s_kindOfFrame = *(uint16_t*)(p + 4); }
static SMonPacketSeams S;
static void ResetAll() {
    s_logV.clear(); s_msg.clear();
    s_desN = 0; s_desMode = -1; s_desLen = 0;
    s_h30 = s_h15 = 0; s_h30First.clear(); s_h15First.clear();
    s_kindOfFrame = 0xFFFF;
}
int main() {
    S.LogErrNoArg = TLNoArg; S.LogErrStr = TLStr;
    S.LogMessage = TMsg; S.DesCfb64 = TDes;
    S.Handle30 = TH30; S.Handle15 = TH15;
    uint8_t buf[0x60];
    SECT("9i-1 ParsePacket");
    ResetAll();
    CHECK(CheatMonitorParsePacket(nullptr, 10, (void*)1, (void*)2,
                                  (void*)3, S) == 0, "null -> 0");
    CHECK(s_msg == "Cheating Program Monitor invalid msg",
          "RAW invalid msg text");
    ResetAll(); memset(buf, 0x11, sizeof buf);
    CHECK(CheatMonitorParsePacket(buf, 0x20, (void*)1, (void*)2,
                                  (void*)3, S) == 1, "decrypt -> 1");
    CHECK(s_desN == 1 && s_desMode == 0 && s_desLen == 0x20,
          "DES_cfb64 in place, mode 0 (decrypt)");
    CHECK(buf[0] == (0x11 ^ 0x5A), "bytes transformed in place");
    ResetAll();
    CHECK(CheatMonitorParsePacket(buf, 0x20, (void*)1, (void*)2,
                                  nullptr, S) == 0, "no keystate -> 0");
    CHECK(s_desN == 0, "no decrypt without the key state");
    ResetAll();
    CHECK(CheatMonitorParsePacket(buf, 0, (void*)1, (void*)2,
                                  (void*)3, S) == 0, "len 0 -> 0");
    CHECK(CheatMonitorParsePacket(buf, 0x31, (void*)1, (void*)2,
                                  (void*)3, S) == 0, "len 0x31 -> 0");
    CHECK(s_desN == 0, "out-of-range lengths never decrypt");
    SECT("9i-2 ProcessPackets: 0x30 frames");
    ResetAll();
    SMonClient* c = (SMonClient*)calloc(1, sizeof(SMonClient));
    memset(c, 0, sizeof(SMonClient));
    memset(c->data, 'A', 0x30);
    *(uint16_t*)((char*)c + 0x24) = 0;      // kind 0
    memset((char*)c + 0x50, 'B', 0x10);
    c->used = 0x40;
    CheatMonitorProcessPackets(c, S);
    CHECK(s_h30 == 1, "one 0x30 frame handled");
    CHECK(s_h30First == "AAAA", "handler got the frame head");
    CHECK(s_kindOfFrame == 0, "frame kind 0 seen by the handler");
    CHECK(c->used == 0x10, "used -= 0x30");
    CHECK(c->data[0] == 'B' && c->data[0x0f] == 'B',
          "remainder shifted to the head");
    ResetAll(); c->used = 0x20;
    *(uint16_t*)((char*)c + 0x24) = 0;
    CheatMonitorProcessPackets(c, S);
    CHECK(s_h30 == 0 && c->used == 0x20, "short frame left pending");
    SECT("9i-3 ProcessPackets: 0xf frames");
    ResetAll(); memset(c, 0, sizeof(SMonClient));
    memset(c->data, 'C', 0xf);
    *(uint16_t*)((char*)c + 0x24) = 2;      // kind 2 -> 0xf
    memset((char*)c + 0x2f, 'D', 8);
    c->used = 0xf + 8;
    CheatMonitorProcessPackets(c, S);
    CHECK(s_h15 == 1 && s_h30 == 0, "one 0xf frame");
    CHECK(c->used == 8 && c->data[0] == 'D', "used -= 0xf + shift");
    ResetAll(); memset(c, 0, sizeof(SMonClient));
    memset(c->data, 'C', 0xc);
    *(uint16_t*)((char*)c + 0x24) = 4;
    c->used = 0xc;
    CheatMonitorProcessPackets(c, S);
    CHECK(s_h15 == 0 && c->used == 0xc, "short 0xf frame left");
    SECT("9i-4 guards");
    ResetAll(); memset(c, 0, sizeof(SMonClient));
    *(uint16_t*)((char*)c + 0x24) = 9;      // kind 9
    c->used = 0x40;
    CheatMonitorProcessPackets(c, S);
    CHECK(s_h15 == 0 && s_h30 == 0 && c->used == 0x40,
          "kinds above 4 are not consumed");
    CHECK(s_logV.empty(), "no log for an unknown kind");
    ResetAll(); c->used = 7;
    CheatMonitorProcessPackets(c, S);
    CHECK(s_logV.empty() && c->used == 7, "under 8 bytes waits");
    ResetAll();
    CheatMonitorProcessPackets(nullptr, S);
    CHECK(s_logV.size() == 1 && s_logV[0] == "<noarg>", "null log");
    ResetAll();
    // 500 back-to-back 0xf frames, each with kind 2 at its +4
    memset(c, 0, sizeof(SMonClient));
    for (int i = 0; i < 500; ++i) {
        *(uint16_t*)((char*)c + 0x20 + i * 0xf + 4) = 2;
    }
    c->used = 0xf * 500;
    CheatMonitorProcessPackets(c, S);
    CHECK(s_h15 == 500, "500 frames drained in one call");
    CHECK(c->used == 0, "buffer emptied");
    free(c);
    if (g_fail == 0) printf("CHEATPACK-OK: %d assertions\n", g_ok);
    else printf("CHEATPACK-FAIL\n");
    return g_fail ? 1 : 0;
}
