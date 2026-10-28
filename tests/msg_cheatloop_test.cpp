// Path-A wave 9h test — the 140003dc0 select/accept/recv loop.
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
static std::vector<std::string> s_logV, s_msgV;
static std::vector<int> s_alive;
static int s_aliveI = 0;
static int s_selectRet = 0;
static std::vector<int64_t> s_ready;
static int64_t s_accRet = -1; static int s_acceptN = 0;
static uint16_t s_peerPort = 5555; static uint32_t s_peerAddr = 0;
static int s_peerNameRet = 0;
static int s_recvRet = 0; static uint32_t s_recvGot = 0;
static std::string s_parsed; static int s_parseN = 0, s_postN = 0;
static int s_shutN = 0, s_closeN = 0, s_cleanN = 0;
static std::string s_checkWhat; static int s_checkLine = 0;
static int s_err = 0;
static void TLStr(const char* s) { s_logV.push_back(s); }
static void TLFmt(const char* f, ...) {
    char b[400]; va_list ap; va_start(ap, f);
    vsnprintf(b, sizeof b, f, ap); va_end(ap); s_logV.push_back(b); }
static void TMsg(const char* f, ...) {
    char b[400]; va_list ap; va_start(ap, f);
    vsnprintf(b, sizeof b, f, ap); va_end(ap); s_msgV.push_back(b); }
static void TCheckF(const char* w, int line, const char*) {
    s_checkWhat = w; s_checkLine = line; s_logV.push_back(w); }
static int TAlive(void*) {
    if (s_aliveI < (int)s_alive.size()) return s_alive[s_aliveI++];
    return 3; }
static int TSelect(int nfds, SMonFdSet* set, int32_t* tv) {
    if (nfds != 0 || tv[0] != 0 || tv[1] != 500) return -99;
    if (s_selectRet < 0) return s_selectRet;
    // the ready set is scripted; count what is still in the built set
    int cnt = 0;
    for (size_t i = 0; i < s_ready.size(); ++i) {
        for (uint32_t k = 0; k < set->count; ++k) {
            if (set->fd[k] == s_ready[i]) { cnt++; break; }
        }
    }
    return cnt; }
static int TFdIsSet(int64_t s, const SMonFdSet*) {
    for (size_t i = 0; i < s_ready.size(); ++i) {
        if (s_ready[i] == s) return 1;
    }
    return 0; }
static int64_t TAccept(int64_t, void* sa, int* len) {
    s_acceptN++;
    if (*len != 0x10) return -200;
    SMonPeer* p = (SMonPeer*)sa;
    p->family = 2; p->port = s_peerPort; p->addr = s_peerAddr;
    return s_accRet; }
static int TPeer(int64_t, void* sa, int* len) {
    if (*len != 0x10) return -201;
    SMonPeer* p = (SMonPeer*)sa;
    p->family = 2; p->port = s_peerPort; p->addr = s_peerAddr;
    return s_peerNameRet; }
static int TRecv(int64_t, void* buf, uint32_t len, uint32_t* got,
                 uint32_t* flags) {
    (void)buf; (void)len; (void)flags;
    *got = s_recvGot;
    return s_recvRet; }
static int TShut(int64_t, int) { s_shutN++; return 0; }
static int TClose(int64_t) { s_closeN++; return 0; }
static int TErr() { return s_err; }
static const char* TNtoa(uint32_t ip) {
    static char b[32]; snprintf(b, sizeof b, "10.9.9.%u", ip & 0xff);
    return b; }
static void TParse(void* d, uint32_t n) {
    s_parseN++; s_parsed.assign((const char*)d, n); }
static void TPost() { s_postN++; }
static void TClean() { s_cleanN++; }
static SMonThreadSeams S;
static SMonLoopSeams L;
static void Wire() {
    S.LogErrStr = TLStr; S.LogErrFmt = TLFmt; S.CloseSocket = TClose;
    S.WsaCleanup = TClean;
    L.LogErrStr = TLStr; L.LogErrFmt = TLFmt; L.LogWarnStr = TLStr;
    L.LogMessage = TMsg; L.CheckF = TCheckF; L.ThreadAlive = TAlive;
    L.Select = TSelect; L.FdIsSet = TFdIsSet; L.Accept = TAccept;
    L.GetPeerName = TPeer; L.WsaRecv = TRecv; L.Shutdown = TShut;
    L.CloseSocket = TClose; L.GetLastError = TErr;
    L.InetNtoa = TNtoa; L.ParsePacket = TParse; L.PostRecv = TPost;
    L.WsaCleanup = TClean;
}
static SMonLoop ST;
static SMonClient* SLOTS[64];
static void Setup() {
    s_logV.clear(); s_msgV.clear(); s_alive.clear(); s_aliveI = 0;
    s_selectRet = 0; s_ready.clear(); s_accRet = -1; s_acceptN = 0;
    s_peerPort = 5555; s_peerAddr = 0; s_peerNameRet = 0;
    s_recvRet = 0; s_recvGot = 0; s_parsed.clear();
    s_parseN = s_postN = s_shutN = s_closeN = s_cleanN = 0;
    s_checkWhat.clear(); s_checkLine = 0; s_err = 0;
    for (int i = 0; i < 64; ++i) {
        if (!SLOTS[i]) SLOTS[i] = (SMonClient*)calloc(1, sizeof(SMonClient));
        memset(SLOTS[i], 0, sizeof(SMonClient));
        ST.slots[i] = SLOTS[i];
    }
    ST.slotCount = 64; ST.listenSock = 7; ST.activeCount = 1;
    ST.ipCount = 1; ST.ips[0] = 1;
    ST.spinBuild = 0; ST.spinRecv = 0;
    ST.slots[0]->active = 1; ST.slots[0]->sock = 7;
}
int main() {
    Wire();
    Setup();
    SECT("9h-1 thread gate and stop path");
    Setup(); s_alive.push_back(3);
    CHECK(CheatMonitorThreadLoop((void*)1, &ST, S, L) == 0, "-> 0");
    CHECK(!s_msgV.empty() &&
          s_msgV[s_msgV.size() - 1] ==
          "Cheating Program Monitor Thread stop", "RAW stop text");
    CHECK(s_closeN == 1 && s_cleanN == 1, "listener closed, WSA cleaned");
    SECT("9h-2 select errors and spins");
    Setup(); s_alive.push_back(2); s_selectRet = -1; s_err = 10004;
    CheatMonitorThreadLoop((void*)1, &ST, S, L);
    CHECK(s_logV.size() == 1 &&
          s_logV[0] == "Cheating Program Monitor select failed : 10004",
          "RAW select error text");
    CHECK(s_msgV.back() == "Cheating Program Monitor Thread stop",
          "select failure stops the thread");
    Setup(); s_alive = { 2, 2, 3 }; s_selectRet = 0;
    CheatMonitorThreadLoop((void*)1, &ST, S, L);
    CHECK(s_aliveI == 3, "two select timeouts then the gate");
    SECT("9h-3 accept + whitelist");
    Setup(); s_alive = { 2, 3 };
    s_ready.push_back(7); s_accRet = 11; s_peerAddr = 1; s_peerPort = 4000;
    CheatMonitorThreadLoop((void*)1, &ST, S, L);
    CHECK(s_acceptN == 1, "accept called");
    CHECK(s_msgV.size() == 2 &&
          s_msgV[0] == "Cheating Program Monitor client(10.9.9.1 : 4000)"
          " login", "RAW login text");
    // RAW teardown on stop closes every ACTIVE slot, so the proof
    // that slot 1 was taken is the shutdown it receives.
    CHECK(s_shutN == 1, "accepted client shut down by the RAW teardown");
    CHECK(ST.slots[1]->active == 0 && ST.slots[1]->sock == 0,
          "stop clears live slots (RAW LAB_14000524a)");
    CHECK(ST.activeCount == 2, "active count incremented");
    Setup(); s_alive = { 2, 3 };
    s_ready.push_back(7); s_accRet = 11; s_peerAddr = 99;
    CheatMonitorThreadLoop((void*)1, &ST, S, L);
    CHECK(s_logV.size() >= 1 &&
          s_logV[0] == "lawless ip address %s!", "RAW lawless warning");
    CHECK(s_closeN == 2, "the rejected client is closed (+ listener)");
    CHECK(ST.slots[1]->active == 0, "no slot taken");
    CHECK(ST.activeCount == 1, "count unchanged");
    Setup(); s_alive = { 2, 3 }; ST.activeCount = 64;
    s_ready.push_back(7); s_accRet = 11;
    CheatMonitorThreadLoop((void*)1, &ST, S, L);
    CHECK(s_acceptN == 0, "no accept when full");
    CHECK(s_logV.size() == 1 && s_logV[0] ==
          "Cheating Program Monitor too many clients", "RAW full text");
    Setup(); s_alive = { 2, 3 };
    s_ready.push_back(7); s_accRet = -1; s_err = 10024;
    CheatMonitorThreadLoop((void*)1, &ST, S, L);
    CHECK(s_logV.size() == 1 && s_logV[0] ==
          "Cheating Program Monitor Accept client failed : 10024",
          "RAW accept-fail text");
    SECT("9h-4 recv path");
    Setup(); ST.slots[2]->active = 1; ST.slots[2]->sock = 21;
    ST.activeCount = 2;
    s_alive = { 2, 3 }; s_ready.push_back(21);
    s_recvRet = 0; s_recvGot = 4;
    CheatMonitorThreadLoop((void*)1, &ST, S, L);
    CHECK(s_parseN == 1 && s_postN == 1, "parse + post after a read");
    CHECK(ST.slots[2]->used == 4, "used += bytes");
    CHECK(s_parsed.size() == 4, "parser got the slot's data area");
    Setup(); ST.slots[2]->active = 1; ST.slots[2]->sock = 21;
    ST.slots[2]->used = 0x8000;
    ST.activeCount = 2; s_alive = { 2, 3 }; s_ready.push_back(21);
    CheatMonitorThreadLoop((void*)1, &ST, S, L);
    CHECK(s_checkWhat == "WSABuff.len > 0" && s_checkLine == 0x1da,
          "RAW WSABuff guard at 0x1da");
    SECT("9h-5 logout paths");
    Setup(); ST.slots[3]->active = 1; ST.slots[3]->sock = 31;
    ST.activeCount = 2; s_alive = { 2, 3 }; s_ready.push_back(31);
    s_recvRet = -1; s_peerNameRet = 0; s_peerAddr = 3; s_peerPort = 6001;
    CheatMonitorThreadLoop((void*)1, &ST, S, L);
    CHECK(s_msgV.size() >= 1 && s_msgV[0] ==
          "Cheating Program Monitor client(10.9.9.3 : 6001) logout",
          "RAW logout text");
    CHECK(s_shutN == 1 && ST.slots[3]->active == 0 &&
          ST.slots[3]->sock == 0, "shutdown + slot cleared");
    CHECK(ST.activeCount == 1, "count decremented");
    Setup(); ST.slots[3]->active = 1; ST.slots[3]->sock = 31;
    ST.activeCount = 2; s_alive = { 2, 3 }; s_ready.push_back(31);
    s_recvRet = -1; s_peerNameRet = -1;
    CheatMonitorThreadLoop((void*)1, &ST, S, L);
    CHECK(s_msgV.size() >= 1 && s_msgV[0] ==
          "Cheating Program Monitor one client logout",
          "RAW anonymous logout text");
    SECT("9h-6 dead-loop guards");
    Setup(); s_alive = { 2, 3 }; ST.spinBuild = 1000000;
    CheatMonitorThreadLoop((void*)1, &ST, S, L);
    CHECK(s_checkWhat == "DEAD_LOOP_BREAK" && s_checkLine == 0x177,
          "build guard at 0x177");
    Setup(); ST.slots[4]->active = 1; ST.slots[4]->sock = 41;
    ST.activeCount = 2; ST.spinRecv = 1000000; s_alive = { 2, 3 };
    s_ready.push_back(41);
    CheatMonitorThreadLoop((void*)1, &ST, S, L);
    CHECK(s_checkWhat == "DEAD_LOOP_BREAK" && s_checkLine == 0x208,
          "recv guard at 0x208");
    for (int i = 0; i < 64; ++i) free(SLOTS[i]);
    if (g_fail == 0) printf("CHEATLOOP-OK: %d assertions\n", g_ok);
    else printf("CHEATLOOP-FAIL\n");
    return g_fail ? 1 : 0;
}
