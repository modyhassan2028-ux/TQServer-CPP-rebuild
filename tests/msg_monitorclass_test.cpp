// CCheatingProgramMonitor — the complete unit test.
#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <vector>
#include <string>
#include "CCheatingProgramMonitor.h"
using namespace msg;
static int g_fail = 0, g_ok = 0;
#define CHECK(c, m) do { if (c) { printf("  ok %s\n", m); g_ok++; } \
    else { printf("  FAIL %s\n", m); g_fail++; } } while (0)
#define SECT(x) printf("%s\n", x)
// ---- seams: the port / kernel / ini side (Init guards) ----
static std::vector<std::string> s_logs;
static void* s_port = (void*)0x9001;
static void LMsg(int, const char* t) { s_logs.push_back(t ? t : "<null>"); }
static void LFmt(int, const char* f, const char*, unsigned long, long) {
    s_logs.push_back(f ? f : "<null>"); }
static void LFmt1(int, const char* f, long) {
    s_logs.push_back(f ? f : "<null>"); }
static void* TGetPort(int) { return s_port; }
static void TPortInit(void*) {}
static int  TPortState(void*) { return 2; }
static void TNotify(void*, uint32_t, uint32_t, uint32_t, const void*) {}
static const char* TStr(const char* n) { return n; }
static void* TIniOpen(const char*, const char*) { return (void*)0x1; }
static long TIniInt(void*, const char*) { return 1; }
static void TIniStr(void*, char* o, const char*, size_t m) {
    if (o && m) o[0] = 0; }
static uint64_t TSockCreate() { return 0; }
static int TBind(uint64_t, uint16_t) { return 0; }
static int TListen(uint64_t) { return 0; }
static int TSelect(const uint64_t*, size_t, uint32_t*, long) { return 0; }
static void TClose(uint64_t) {}
// ---- frame seams (both handlers) ----
static int s_postN = 0, s_postId = -1, s_postMsg = -1;
static uint32_t s_postLen = 0; static std::string s_postData;
static std::vector<std::string> s_flogs;
static void* s_fport = (void*)0x5001;
static int s_allocN = 0, s_freeN = 0, s_allocFail = 0;
static uint8_t s_pool[0x30];
static void FLNoArg() { s_flogs.push_back("<noarg>"); }
static void FLFmt(const char* f, ...) {
    char b[300]; va_list ap; va_start(ap, f);
    vsnprintf(b, sizeof b, f, ap); va_end(ap); s_flogs.push_back(b); }
static void* FPort(int) { return s_fport; }
static void FPost(void*, int id, int m, uint32_t len, void* d) {
    s_postN++; s_postId = id; s_postMsg = m; s_postLen = len;
    if (d) s_postData.assign((const char*)d, len); }
static const char* FStr(const char*) { return "SIN"; }
static void* FAlloc(size_t) { s_allocN++; return s_allocFail ? nullptr : s_pool; }
static void FFree(void*) { s_freeN++; }
int main() {
    SECT("cls-1 the unit exists with the RAW names");
    CCheatingProgramMonitor mon;
    CHECK(mon.Clients() != nullptr, "slot pool reachable");
    CHECK(mon.ClientCount() == 0, "no clients yet");
    CHECK(mon.State().listen_sock == 0, "state zeroed by the ctor");
    CHECK(mon.State().initialized == false, "not initialised");
    SECT("cls-2 GetPort is 14050c340(5)");
    CHECK(CCheatingProgramMonitor::GetPort(nullptr) == nullptr,
          "null seam -> null");
    CHECK(CCheatingProgramMonitor::GetPort(TGetPort) == s_port,
          "port object through the seam");
    SECT("cls-3 Init guard path (RAW early exit)");
    MsgCheatSeams ms;
    memset(&ms, 0, sizeof ms);
    ms.get_port = TGetPort; ms.port_init = TPortInit;
    ms.port_state = TPortState; ms.notify = TNotify; ms.str = TStr;
    ms.ini_open = TIniOpen; ms.ini_get_int = TIniInt;
    ms.ini_get_string = TIniStr;
    ms.sock_create = TSockCreate; ms.sock_bind = TBind;
    ms.sock_listen = TListen; ms.sock_select = TSelect;
    ms.sock_close = TClose;
    ms.log_msg = LMsg; ms.log_fmt = LFmt; ms.log_fmt1 = LFmt1;
    s_port = nullptr; s_logs.clear();
    bool inited = mon.Init(ms);
    CHECK(inited == false, "null port -> Init fails");
    CHECK(!s_logs.empty(), "and logs the RAW check literal");
    s_port = (void*)0x9001;
    SECT("cls-4 GetThreadState (14001f4c0)");
    unsigned char p[0x210];
    memset(p, 0, sizeof p);
    *(uint32_t*)(p + 0x1fc) = 2;
    CHECK(CCheatingProgramMonitor::GetThreadState(p) == 2,
          "state 2 = keep running");
    *(uint32_t*)(p + 0x1fc) = 6;
    CHECK(CCheatingProgramMonitor::GetThreadState(p) == 6,
          "value follows +0x1fc");
    SECT("cls-5 ProcessMsg15 through the class");
    SMonFrameSeams fs;
    fs.LogErrNoArg = FLNoArg; fs.LogErrFmt = FLFmt;
    fs.PortObjGet = FPort; fs.PostMsg = FPost; fs.GetString = FStr;
    fs.Alloc = FAlloc; fs.Free = FFree;
    unsigned char f15[0x0f];
    s_postN = 0; s_allocN = s_freeN = 0; s_flogs.clear();
    memset(f15, 0, sizeof f15);
    *(uint16_t*)(f15 + 4) = 2;
    memcpy(f15 + 6, "NAME12345", 9);
    mon.ProcessMsg15(f15, fs);
    CHECK(s_postN == 1 && s_postLen == 0x30, "posts 0x30");
    CHECK(s_postMsg == 0xea61 && s_postId == 0x0e, "RAW 0xe/0xea61");
    CHECK(s_postData.compare(0x0f, 3, "SIN") == 0, "sin filled at +0xf");
    CHECK(s_allocN == 1 && s_freeN == 1, "block allocated and freed");
    s_postN = 0; s_flogs.clear(); s_allocN = s_freeN = 0;
    *(uint16_t*)(f15 + 4) = 9;
    mon.ProcessMsg15(f15, fs);
    CHECK(s_postN == 0 && s_flogs.size() == 1, "wrong kind -> log only");
    CHECK(s_freeN == 0, "RAW leak on the wrong kind preserved");
    SECT("cls-6 ProcessMsg30 through the class");
    unsigned char f30[0x30];
    memset(f30, 0x11, sizeof f30); f30[0x0f] = 0x44;
    s_postN = 0; s_postData.clear();
    mon.ProcessMsg30(f30, fs);
    CHECK(s_postN == 1 && s_postLen == 0x30, "posts the 0x30 block");
    CHECK((unsigned char)s_postData[0x2f] == 0, "last byte cleared");
    CHECK((unsigned char)s_postData[0x0f] == 0x44, "0xf untouched");
    memset(f30, 0x11, sizeof f30); f30[0x0f] = 0;
    s_postN = 0; s_postData.clear();
    mon.ProcessMsg30(f30, fs);
    CHECK(s_postData.compare(0x0f, 3, "SIN") == 0,
          "zero byte 0xf pulls the string");
    s_postN = 0; s_flogs.clear();
    mon.ProcessMsg30(nullptr, fs);
    CHECK(s_postN == 0 && s_flogs.size() == 1, "null frame -> log only");
    SECT("cls-7 Stop");
    s_logs.clear();
    mon.Stop(ms);
    CHECK(mon.State().initialized == false, "Stop clears the flag");
    if (g_fail == 0) printf("MONCLASS-OK: %d assertions\n", g_ok);
    else printf("MONCLASS-FAIL\n");
    return g_fail ? 1 : 0;
}
