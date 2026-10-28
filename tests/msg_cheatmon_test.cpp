// Path-A wave 9g test — 140003dc0 init half.
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstdarg>
#include <cstdint>
#include <string>
#include <vector>
#include "MsgCheatMonitorThread.h"
using namespace msg;
static int g_fail = 0, g_ok = 0;
#define CHECK(c, m) do { if (c) { printf("  ok %s\n", m); g_ok++; } \
    else { printf("  FAIL %s\n", m); g_fail++; } } while (0)
#define SECT(x) printf("%s\n", x)
static std::vector<std::string> s_logV;
static int s_line = 0; static std::string s_what, s_keyNames;
static void* s_portObj = (void*)0x9001; static int s_resetN = 0;
static uint32_t s_tid = 4242; static int s_postMsg = -1;
static uint32_t s_postLen = 0; static std::string s_postText;
static int s_wsaRet = 0; static unsigned char s_ver0 = 2, s_ver1 = 2;
static int64_t s_sockRet = 5; static int s_sockN = 0;
static int s_bindRet = 0, s_listenRet = 0, s_closeN = 0, s_cleanN = 0;
static int s_err = 0; static int s_iniPort = 0, s_iniIpNum = 0;
static std::vector<std::string> s_ipNames, s_ipVals;
static uint16_t s_htons = 0; static int s_bindLen = 0;
static std::string s_ntoa = "0.0.0.0";
static int s_allocN = 0; static void* s_allocFailAt = nullptr;
static int s_allocFailIdx = -1;
static std::string s_desStr; static uint8_t s_desKey[16];
static int s_desSetN = 0; static int s_iniClosed = 0;
static void TLNoArg() { s_logV.push_back("<noarg>"); }
static void TLFmt(const char* f, ...) {
    char b[512]; va_list ap; va_start(ap, f);
    vsnprintf(b, sizeof b, f, ap); va_end(ap);
    s_logV.push_back(b); }
static void TLStr(const char* s) { s_logV.push_back(s); }
static void TCheckF(const char* what, int line, const char*) {
    s_line = line; s_what = what; s_logV.push_back(what); }
static void* TPortGet(int idx) { (void)idx; return s_portObj; }
static void TPortReset(void*) { s_resetN++; }
static uint32_t TThreadId(void*) { return s_tid; }
static void TPost(void*, int, int msg, uint32_t len) {
    s_postMsg = msg; s_postLen = len;
    char b[256]; snprintf(b, sizeof b,
        "#%u: Cheating Program Monitor thread running.", (unsigned)s_tid);
    s_postText = b; }
static int TWsa(uint16_t ver, void* d) {
    if (ver != 0x202) return -5;
    unsigned char* p = (unsigned char*)d; p[0] = s_ver0; p[1] = s_ver1;
    return s_wsaRet; }
static void TClean() { s_cleanN++; }
static int64_t TSock(int a, int t, int p, void*) {
    s_sockN++; if (a != 2 || t != 1 || p != 0) return -100;
    return s_sockRet; }
static int TBind(int64_t s, const void* sa, int len) {
    const unsigned char* b = (const unsigned char*)sa;
    s_bindLen = len;
    if (b[0] != 2 || b[1] != 0) return -101;
    s_htons = *(const uint16_t*)(b + 2);
    if (b[4] || b[5] || b[6] || b[7]) return -102;
    return s_bindRet; }
static int TListen(int64_t, int) { return s_listenRet; }
static int TClose(int64_t) { s_closeN++; return 0; }
static int TErr() { return s_err; }
static uint32_t TIAddr(const char* ip) {
    s_ipVals.push_back(ip);
    return 0x0A000000u + (uint32_t)s_ipVals.size(); }
static const char* TNtoa(uint32_t) { return s_ntoa.c_str(); }
static uint16_t THtons(uint16_t v) { return (uint16_t)((v >> 8) | (v << 8)); }
static void* TIniOpen(const char*, const char*) { return (void*)0x11; }
static int TIniInt(void*, const char* key) {
    if (!strcmp(key, "ListenPort")) return s_iniPort;
    if (!strcmp(key, "IPNum")) return s_iniIpNum;
    return 0; }
static void TIniStr(void*, char* out, const char* key, int) {
    s_ipNames.push_back(key);
    snprintf(out, 24, "10.1.2.%d", (int)s_ipNames.size()); }
static void TIniClose(void*) { s_iniClosed++; }
static void* TAlloc(size_t n) {
    if (s_allocFailIdx >= 0 && s_allocN == s_allocFailIdx) { s_allocN++; return nullptr; }
    s_allocN++; return calloc(1, n); }
static void TFree(void* p) { free(p); }
static void TDesStr(const char* s, uint8_t* out) {
    s_desStr = s; memset(out, 0x5A, 16); }
static void TDesSet(const uint8_t* k) { s_desSetN++; memcpy(s_desKey, k, 16); }
static SMonThreadSeams S;
static void Wire() {
    S.LogErrNoArg = TLNoArg; S.LogErrFmt = TLFmt; S.LogErrStr = TLStr;
    S.LogWarnStr = TLStr; S.CheckF = TCheckF;
    S.PortObjGet = TPortGet; S.PortObjReset = TPortReset;
    S.PortObjThreadId = TThreadId; S.PortObjPost = TPost;
    S.WsaStartup = TWsa; S.WsaCleanup = TClean; S.Socket = TSock;
    S.Bind = TBind; S.Listen = TListen; S.CloseSocket = TClose;
    S.GetLastError = TErr; S.InetAddr = TIAddr; S.InetNtoa = TNtoa;
    S.Htons = THtons;
    S.IniOpen = TIniOpen; S.IniGetInt = TIniInt;
    S.IniGetString = TIniStr; S.IniClose = TIniClose;
    S.Alloc = TAlloc; S.Free = TFree;
    S.DesStringToKey = TDesStr; S.DesSetKey = TDesSet;
}
static SMonInitResult R;
static void FreeSlots() {
    for (int i = 0; i < R.slotCount; ++i) { free(R.slots[i]); R.slots[i] = nullptr; }
    R.slotCount = 0; }
static void ResetAll() {
    FreeSlots();
    s_logV.clear(); s_line = 0; s_what.clear(); s_ipNames.clear();
    s_ipVals.clear(); s_resetN = s_sockN = s_closeN = s_cleanN = 0;
    s_tid = 4242; s_postMsg = -1; s_postLen = 0; s_postText.clear();
    s_wsaRet = 0; s_ver0 = 2; s_ver1 = 2; s_sockRet = 5;
    s_bindRet = 0; s_listenRet = 0; s_err = 0; s_iniPort = 0;
    s_iniIpNum = 0; s_htons = 0; s_bindLen = 0; s_ntoa = "0.0.0.0";
    s_allocN = 0; s_allocFailIdx = -1;
    s_desStr.clear(); s_desSetN = 0; s_iniClosed = 0;
    memset(s_desKey, 0, 16);
}
int main() {
    memset(&R, 0, sizeof R);
    Wire();
    SECT("9g-1 guards");
    ResetAll(); s_portObj = nullptr;
    CHECK(CheatMonitorThreadInit((void*)1, &R, S) == 0, "no port obj -> 0");
    CHECK(s_what == "pPort" && s_line == 0xff, "CHECKF pPort line 0xff");
    ResetAll(); s_portObj = (void*)0x9001;
    CHECK(CheatMonitorThreadInit(nullptr, &R, S) == 0, "no thread -> 0");
    CHECK(s_what == "pMainThread" && s_line == 0x103,
          "CHECKF pMainThread line 0x103");
    CHECK(s_resetN == 1, "vtable+0x38 reset before the thread check");
    SECT("9g-2 WSA and socket");
    ResetAll();
    CHECK(CheatMonitorThreadInit((void*)1, &R, S) == 1, "happy -> 1");
    ResetAll(); s_wsaRet = 7;
    CHECK(CheatMonitorThreadInit((void*)1, &R, S) == 7, "startup err");
    CHECK(s_sockN == 0, "no socket after startup error");
    ResetAll(); s_ver1 = 1;
    CHECK(CheatMonitorThreadInit((void*)1, &R, S) == 0,
          "version mismatch returns 0");
    CHECK(s_sockN == 0, "no socket");
    ResetAll(); s_sockRet = -1; s_err = 10055;
    CHECK(CheatMonitorThreadInit((void*)1, &R, S) == 10055,
          "socket fail returns the error");
    CHECK(s_cleanN == 1, "WSACleanup on socket failure");
    SECT("9g-3 ini and the ip list");
    ResetAll(); s_iniPort = 0; s_iniIpNum = 0;
    CheatMonitorThreadInit((void*)1, &R, S);
    CHECK(R.port == 9150, "ListenPort 0 -> 9150 (0x23be)");
    CHECK((uint16_t)((s_htons >> 8) | (s_htons << 8)) == 9150,
          "network-order 9150 in the sockaddr");
    CHECK(s_bindLen == 0x10, "bind len 0x10");
    ResetAll(); s_iniPort = 1234; s_iniIpNum = 3;
    CheatMonitorThreadInit((void*)1, &R, S);
    CHECK(R.port == 1234 && R.ipCount == 3, "port + 3 ips");
    CHECK(s_ipNames.size() == 3 && s_ipNames[0] == "IP1" &&
          s_ipNames[2] == "IP3", "1-based IP%d keys");
    CHECK(s_ipVals[0] == "10.1.2.1", "GetString value passed to inet_addr");
    CHECK(R.ips[0] == (int32_t)(0x0A000000u + 1), "ips[0] stored");
    ResetAll(); s_iniIpNum = 0x30;
    CheatMonitorThreadInit((void*)1, &R, S);
    CHECK(R.ipCount == 20, "IPNum clamped to 20");
    CHECK(!s_logV.empty() &&
          s_logV[0] == "astrict ip number overrun max ip number!",
          "RAW clamp warning text");
    CHECK(s_ipNames.size() == 20, "20 names read");
    SECT("9g-4 the 64 slots");
    ResetAll();
    CHECK(CheatMonitorThreadInit((void*)1, &R, S) == 1, "happy");
    CHECK(s_allocN == 64 && R.slotCount == 64, "64 x 0x8020");
    CHECK(R.slots[0]->active == 1 && R.slots[0]->sock == s_sockRet,
          "slot 0 = listener, active");
    CHECK(R.slots[1]->active == 0 && R.slots[1]->sock == 0,
          "slot 1 zeroed");
    SECT("9g-5 bind / listen failures");
    ResetAll(); s_bindRet = -1; s_err = 10048;
    CHECK(CheatMonitorThreadInit((void*)1, &R, S) == 10048, "bind err");
    CHECK(s_logV.size() == 1 && s_logV[0] ==
          "Cheating Program Monitor can not bind to (0.0.0.0 : 9150),"
          " nErr : 10048", "RAW bind text (ntoa, port, err)");
    CHECK(s_closeN == 1 && s_cleanN == 1 && s_iniClosed == 1,
          "closesocket + WSACleanup + ini dtor");
    ResetAll(); s_listenRet = -1; s_err = 10022;
    CHECK(CheatMonitorThreadInit((void*)1, &R, S) == 10022, "listen err");
    CHECK(s_logV[0] == "Cheating Program Monitor listen failed : 10022",
          "RAW listen text");
    CHECK(s_closeN == 1 && s_cleanN == 1 && s_iniClosed == 1,
          "same cleanup");
    ResetAll(); s_allocFailIdx = 3; s_err = 0;
    CHECK(CheatMonitorThreadInit((void*)1, &R, S) == 0, "alloc fail -> 0");
    CHECK(s_what == "pClientInfo" && s_line == 0x155,
          "CHECKF pClientInfo line 0x155");
    CHECK(s_iniClosed == 1, "ini closed on alloc failure");
    SECT("9g-6 DES + the running message");
    ResetAll();
    CheatMonitorThreadInit((void*)1, &R, S);
    CHECK(s_desStr == "df29duw", "DES_string_to_key(\"df29duw\")");
    CHECK(s_desSetN == 1 && R.desKey[0] == 0x5A, "key installed");
    CHECK(s_postMsg == 0x9c41, "post id 0x9c41");
    CHECK(s_postText == "#4242: Cheating Program Monitor thread"
          " running.", "RAW running text with the thread id");
    CHECK(s_postLen == s_postText.size(), "length posted");
    FreeSlots();
    if (g_fail == 0) printf("CHEATMON-OK: %d assertions\n", g_ok);
    else printf("CHEATMON-FAIL\n");
    return g_fail ? 1 : 0;
}
