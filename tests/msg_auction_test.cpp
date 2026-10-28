// Path-A wave 7 test — Auction
// OnProcess (raw-verified)
#include <cassert>
#include <cstdio>
#include <cstring>
#include "MsgAuctionThread.h"
using namespace msg;

static void* s_pQ = (void*)0x40;
static void* s_pSvc = (void*)0x48;
static uint32_t s_t; static bool s_bHas;
static uint32_t s_aPeek[4]; static int s_nPeek;
static bool T_Peek(void* q, uint32_t ms) {
    assert(q == s_pQ);
    s_aPeek[s_nPeek < 4 ? s_nPeek++ : 3] =
        ms;
    return s_bHas;
}
static uint32_t s_aTick[16]; static int s_nT;
static void T_TickOn(uint32_t id) {
    s_aTick[s_nT < 16 ? s_nT++ : 15] = id;
}
static uint32_t s_nOff;
static void T_TickOff() { s_nOff++; }
static uint32_t T_Time() { return s_t; }
static uint32_t s_aKT[2]; static int s_nKT;
static void T_KTimer18(void* k, uint32_t t) {
    assert(k == s_pSvc);
    s_aKT[s_nKT < 2 ? s_nKT++ : 1] = t;
}
struct SMsg { SMGMsgInfo inf; bool ok; };
static SMsg s_aMsgs[4]; static int s_nMsgs;
static int s_iMsg;
static bool T_Wait(void* q, int32_t f1,
        int32_t f2, uint32_t size,
        uint8_t* buf, SMGMsgInfo* inf) {
    assert(q == s_pQ && f1 == -1 &&
           f2 == -1 && size == 0x418);
    if (s_iMsg >= s_nMsgs) return false;
    *inf = s_aMsgs[s_iMsg].inf;
    return s_aMsgs[s_iMsg++].ok;
}
static uint32_t s_aPk[4], s_aA8[4],
       s_aPort[4]; static int s_nPk;
static bool s_bOk = true;
static bool T_Proc5(void* k, uint32_t pk,
        uint8_t* buf, uint32_t a8,
        uint32_t port) {
    assert(k == s_pSvc && buf != nullptr);
    s_aPk[s_nPk < 4 ? s_nPk++ : 3] = pk;
    s_aA8[s_nPk < 4 ? s_nPk - 1 : 3] = a8;
    s_aPort[s_nPk < 4 ? s_nPk - 1 : 3] =
        port;
    return s_bOk;
}
static char s_aErr[2][200];
static uint32_t s_aErrPk[2], s_aErrPort[2];
static int s_nErr;
static void T_Err(const char* f, uint32_t pk,
        uint32_t port) {
    std::snprintf(s_aErr[s_nErr < 2 ?
        s_nErr++ : 1], 199, "%s", f);
    s_aErrPk[s_nErr - 1] = pk;
    s_aErrPort[s_nErr - 1] = port;
}
static char s_aWarn[2][200];
static int s_nWarn;
static void T_Warn(const char* f) {
    std::snprintf(s_aWarn[s_nWarn < 2 ?
        s_nWarn++ : 1], 199, "%s", f);
}
static uint8_t s_th[0x58];

static void Reset() {
    std::memset(&g_ThreadSeams, 0,
        sizeof g_ThreadSeams);
    SThreadSeams& s = g_ThreadSeams;
    s.QWaitMsg = T_Wait;
    s.QPeekMsg = T_Peek;
    s.KProcessMsg5 = T_Proc5;
    s.KOnTimer18 = T_KTimer18;
    s.TimeGet = T_Time;
    s.TickOn = T_TickOn;
    s.TickOff = T_TickOff;
    s.LogError = T_Err;
    s.LogWarning = T_Warn;
    AuctionResetStatics();
    std::memset(s_th, 0, sizeof s_th);
    *(void**)(s_th + 0x40) = s_pQ;
    *(void**)(s_th + 0x48) = s_pSvc;
    s_t = 0; s_bHas = false; s_nPeek = 0;
    s_nT = 0; s_nOff = 0; s_nKT = 0;
    s_nMsgs = 0; s_iMsg = 0; s_nPk = 0;
    s_bOk = true; s_nErr = 0;
    s_nWarn = 0;
}

int main() {
    printf("TH7 start\n"); fflush(stdout);

    // ==== S1: idle — inverted ifaces
    // (queue +0x40 / service +0x48),
    // slide 2000, ticks 0x4a/0x32/0x34
    // ====
    {
        Reset();
        s_t = 3000;
        assert(AuctionOnProcess(s_th) == 1);
        assert(g_AucFirstRun == 1);
        assert(g_AucResyncBase == 5000);
        // 3000 + 2000
        assert(s_nKT == 1 &&
               s_aKT[0] == 3000);
        // Peek on the +0x40 iface
        assert(s_nPeek == 1);
        assert(s_aTick[0] == 0x4a);
        assert(s_aTick[1] == 0x32);
        assert(s_aTick[2] == 0x34);
        // since = 3000-5000 underflow -> 0
        assert(g_AucIdleMs == 0);
        printf("S1 ok (idle)\n"); fflush(stdout);
    }

    // ==== S2: drain — five-arg
    // ProcessMsg on the +0x48 service +
    // ERROR pair + tick 0x33 ====
    {
        Reset();
        g_AucFirstRun = 1;
        g_AucResyncBase = 100;
        s_bHas = true; s_bOk = false;
        s_aMsgs[0] = {{0x55, 9001, 99,
                        0}, true};
        s_aMsgs[1] = {{0x56, 9002, 88,
                        0}, true};
        s_nMsgs = 2;
        s_t = 2000;
        assert(AuctionOnProcess(s_th) == 1);
        assert(s_nPk == 2);
        assert(s_aPk[0] == 9001 &&
               s_aPk[1] == 9002);
        assert(s_aA8[0] == 99 &&
               s_aA8[1] == 88);
        assert(s_aPort[0] == 0x55 &&
               s_aPort[1] == 0x56);
        assert(s_nErr == 2);
        assert(std::strcmp(s_aErr[0],
            "CAuctionSearchThread::"
            "OnProcess ProcessMsg returned"
            " error with packet:%d, port:%d")
               == 0);
        assert(s_aErrPk[0] == 9001 &&
               s_aErrPort[0] == 0x55);
        assert(s_nKT == 0);
        assert(s_aTick[0] == 0x4a);
        assert(s_aTick[1] == 0x32);
        assert(s_aTick[2] == 0x33);
        assert(s_aTick[3] == 0x33);
        printf("S2 ok (drain)\n"); fflush(stdout);
    }

    // ==== S3: resync text + base reset +
    // idle window positive ====
    {
        Reset();
        s_t = 77777;
        g_AucFirstRun = 1;
        g_AucResyncBase = 7;
        AuctionOnProcess(s_th);
        assert(s_nWarn == 1);
        assert(std::strcmp(s_aWarn[0],
            "resync CAuctionSearchService"
            "::OnTimer cumulative deviation"
            " %dms") == 0);
        assert(g_AucResyncBase == 77777);
        // since = t2-base = 0 -> idle 2000
        assert(g_AucIdleMs == 2000);
        // propagation to next Peek
        AuctionOnProcess(s_th);
        assert(s_aPeek[1] == 2000);
        printf("S3 ok (resync)\n"); fflush(stdout);
    }

    printf("TH7 ALL-OK\n");
    return 0;
}
