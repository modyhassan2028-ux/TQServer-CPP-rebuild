// Path-A wave 9j test — 140001900 / 140001a50 / 14001f4c0.
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdarg>
#include <string>
#include <vector>
#include "MsgCheatMonitorFrames.h"
using namespace msg;
static int g_fail = 0, g_ok = 0;
#define CHECK(c, m) do { if (c) { printf("  ok %s\n", m); g_ok++; } \
    else { printf("  FAIL %s\n", m); g_fail++; } } while (0)
#define SECT(x) printf("%s\n", x)
static std::vector<std::string> s_logV;
static void* s_port = (void*)0x5001;
static int s_postN = 0, s_postId = -1, s_postMsg = -1;
static uint32_t s_postLen = 0; static std::string s_postData;
static std::string s_lastKey; static const char* s_strVal = "BOTNAME";
static int s_allocN = 0, s_freeN = 0; static int s_allocFail = 0;
static void TLNoArg() { s_logV.push_back("<noarg>"); }
static void TLFmt(const char* f, ...) {
    char b[300]; va_list ap; va_start(ap, f);
    vsnprintf(b, sizeof b, f, ap); va_end(ap); s_logV.push_back(b); }
static void* TPort(int) { return s_port; }
static void TPost(void*, int id, int msg, uint32_t len, void* d) {
    s_postN++; s_postId = id; s_postMsg = msg; s_postLen = len;
    if (d) s_postData.assign((const char*)d, len); }
static const char* TStr(const char* k) { s_lastKey = k; return s_strVal; }
// the RAW wrong-kind path leaks, so the test uses a static pool
// instead of malloc and ASan stays clean.
static uint8_t s_pool[0x30];
static bool s_poolBusy = false;
static void* TAlloc(size_t n) {
    s_allocN++; if (s_allocFail) return nullptr;
    s_poolBusy = true; memset(s_pool, 0xAB, n);
    return s_pool; }
static void TFree(void* p) { s_freeN++; s_poolBusy = false; (void)p; }
static SMonFrameSeams S;
static void ResetAll() {
    s_logV.clear(); s_port = (void*)0x5001;
    s_postN = 0; s_postId = s_postMsg = -1; s_postLen = 0;
    s_postData.clear(); s_lastKey.clear(); s_strVal = "BOTNAME";
    s_allocN = s_freeN = 0; s_allocFail = 0;
}
int main() {
    S.LogErrNoArg = TLNoArg; S.LogErrFmt = TLFmt; S.PortObjGet = TPort;
    S.PostMsg = TPost; S.GetString = TStr;
    S.Alloc = TAlloc; S.Free = TFree;
    uint8_t f30[0x30];
    uint8_t f15[0x0f];
    SECT("9j-1 Handle30");
    ResetAll();
    CheatMonitorHandle30(nullptr, S);
    CHECK(s_logV.size() == 1 && s_postN == 0, "null -> noarg, no post");
    ResetAll(); s_port = nullptr;
    memset(f30, 0x11, sizeof f30);
    CheatMonitorHandle30(f30, S);
    CHECK(s_logV.size() == 1 && s_postN == 0, "no port -> noarg");
    ResetAll(); memset(f30, 0x11, sizeof f30);
    memset(f30, 0x11, 0x30);
    f30[0x0f] = 0x22;                       // non-zero: no string fill
    CheatMonitorHandle30(f30, S);
    CHECK(s_postN == 1, "one post");
    CHECK(s_postId == 0x0e && s_postMsg == 0xea61 && s_postLen == 0x30,
          "RAW id 0xe / msg 0xea61 / len 0x30");
    CHECK(s_postData.size() == 0x30, "the whole 0x30 block is posted");
    CHECK((uint8_t)s_postData[0] == 0x11 && (uint8_t)s_postData[0x2e] == 0x11,
          "frame bytes copied");
    CHECK((uint8_t)s_postData[0x2f] == 0, "last byte cleared (RAW mask)");
    CHECK((uint8_t)s_postData[0x0f] == 0x22, "0xf untouched when non-zero");
    CHECK(s_lastKey.empty(), "no string lookup");
    ResetAll(); memset(f30, 0x11, 0x30); f30[0x0f] = 0;
    CheatMonitorHandle30(f30, S);
    CHECK(s_lastKey == "STR_GENERAL_BOT_SIN", "RAW string key");
    CHECK(s_postData.compare(0x0f, 7, "BOTNAME") == 0,
          "0x21 bytes filled at +0xf");
    SECT("9j-2 Handle15 kinds");
    ResetAll();
    CheatMonitorHandle15(nullptr, S);
    CHECK(s_logV.size() == 1 && s_postN == 0, "null -> noarg");
    ResetAll(); s_port = nullptr;
    memset(f15, 0, sizeof f15);
    CheatMonitorHandle15(f15, S);
    CHECK(s_logV.size() == 1 && s_postN == 0, "no port -> noarg");
    ResetAll(); s_allocFail = 1;
    memset(f15, 0, sizeof f15);
    CheatMonitorHandle15(f15, S);
    CHECK(s_logV.size() == 1 && s_postN == 0, "alloc fail -> noarg");
    const char* keys[] = { "STR_GENERAL_BOT_SIN", "STR_KEY_BOT_SIN",
                           "STR_SERIOUS_BOT_SIN", "STR_HACK_TOOL_SIN" };
    for (int k = 1; k <= 4; ++k) {
        ResetAll();
        memset(f15, 0, sizeof f15);
        *(uint32_t*)f15 = 0xA1A2A3A4u;
        *(uint16_t*)(f15 + 4) = (uint16_t)k;
        memcpy(f15 + 6, "NAME12345", 9);
        CheatMonitorHandle15(f15, S);
        char m[64];
        snprintf(m, sizeof m, "kind %d -> %s", k, keys[k - 1]);
        CHECK(s_lastKey == keys[k - 1], m);
        CHECK(s_postN == 1 && s_postLen == 0x30, "posted 0x30");
        CHECK((uint8_t)s_postData[0] == 0xA4 &&
              (uint8_t)s_postData[3] == 0xA1, "u32 head copied");
        CHECK(*(uint16_t*)(s_postData.data() + 4) == k, "kind copied");
        CHECK(s_postData.compare(6, 9, "NAME12345") == 0,
              "9 name bytes copied");
        CHECK(s_postData.compare(0x0f, 7, "BOTNAME") == 0,
              "sin at +0xf");
        CHECK(s_allocN == 1 && s_freeN == 1, "block freed");
    }
    SECT("9j-3 wrong kind");
    ResetAll(); memset(f15, 0, sizeof f15);
    *(uint16_t*)(f15 + 4) = 5;
    CheatMonitorHandle15(f15, S);
    CHECK(s_postN == 0, "no post");
    CHECK(!s_logV.empty() && s_logV[0] ==
          "CCheatingProgramMonitor::ProcessMsg, wrong cheat type : 5",
          "RAW wrong-type text with %u");
    CHECK(s_freeN == 0, "RAW leaks the block on a wrong kind");
    ResetAll(); memset(f15, 0, sizeof f15);
    *(uint16_t*)(f15 + 4) = 0;
    CheatMonitorHandle15(f15, S);
    CHECK(s_postN == 0 && s_logV.size() == 1, "kind 0 also rejected");
    SECT("9j-4 thread state");
    uint8_t p[0x210];
    memset(p, 0, sizeof p);
    *(uint32_t*)(p + 0x1fc) = 2;
    CHECK(CheatMonitorThreadState(p) == 2, "reads +0x1fc");
    *(uint32_t*)(p + 0x1fc) = 7;
    CHECK(CheatMonitorThreadState(p) == 7, "value follows the field");
    if (g_fail == 0) printf("CHEATFRAMES-OK: %d assertions\n", g_ok);
    else printf("CHEATFRAMES-FAIL\n");
    return g_fail ? 1 : 0;
}
