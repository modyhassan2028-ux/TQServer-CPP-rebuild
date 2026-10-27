// Path-A wave 6 test — World/
// UserLogin/Chat OnProcess (raw)
#include <cassert>
#include <cstdio>
#include <cstring>
#include "MsgWorldULChatThreads.h"
using namespace msg;

static uint32_t s_t;
static uint32_t T_Time() { return s_t; }
static uint32_t s_aTickOn[32]; static int s_nTickOn;
static void T_TickOn(uint32_t id) {
    s_aTickOn[s_nTickOn < 32 ?
        s_nTickOn++ : 31] = id;
}
static uint32_t s_nTickOff;
static void T_TickOff() { s_nTickOff++; }

static void* s_pQ = (void*)0x51;
static void* s_pK = (void*)0x42;
static bool s_bHas = false;
static uint32_t s_aPeek[4]; static int s_nPeek;
static bool T_Peek(void* q, uint32_t ms) {
    assert(q == s_pQ);
    s_aPeek[s_nPeek < 4 ? s_nPeek++ : 3] =
        ms;
    return s_bHas;
}
struct SMsg { SMGMsgInfo inf; bool ok; };
static SMsg s_aMsgs[8]; static int s_nMsgs;
static int s_iMsg;
static bool T_Wait(void* q, int32_t f1,
        int32_t f2, uint32_t size,
        uint8_t* buf, SMGMsgInfo* inf) {
    assert(q == s_pQ && f1 == -1 &&
           f2 == -1 && size == 0x418);
    if (s_iMsg >= s_nMsgs) return false;
    *inf = s_aMsgs[s_iMsg].inf;
    std::memset(buf, 0xEF, 4);
    return s_aMsgs[s_iMsg++].ok;
}
static uint32_t s_aPk[8]; static uint32_t
    s_aArg8[8]; static uint32_t
    s_aPort[8]; static int s_nPk;
static bool s_bProcOk = true;
static bool T_Proc5(void* k, uint32_t pk,
        uint8_t* buf, uint32_t a8,
        uint32_t port) {
    assert(k == s_pK && buf != nullptr);
    s_aPk[s_nPk < 8 ? s_nPk++ : 7] = pk;
    s_aArg8[s_nPk < 8 ? s_nPk - 1 : 7] = a8;
    s_aPort[s_nPk < 8 ? s_nPk - 1 : 7] =
        port;
    return s_bProcOk;
}
static uint32_t s_aKT[4]; static int s_nKT;
static void T_KTimer18(void* k, uint32_t t) {
    assert(k == s_pK);
    s_aKT[s_nKT < 4 ? s_nKT++ : 3] = t;
}
static char s_aErr[4][200]; static uint32_t
    s_aErrPk[4], s_aErrPort[4];
static int s_nErr;
static void T_Err(const char* f, uint32_t pk,
        uint32_t port) {
    std::snprintf(s_aErr[s_nErr], 199, "%s",
                  f);
    s_aErrPk[s_nErr] = pk;
    s_aErrPort[s_nErr] = port;
    s_nErr++;
}
static char s_aWarn[4][200];
static int s_nWarn;
static void T_Warn(const char* f) {
    std::snprintf(s_aWarn[s_nWarn < 4 ?
        s_nWarn++ : 3], 199, "%s", f);
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
    ThreadResetStatics();
    std::memset(s_th, 0, sizeof s_th);
    *(void**)(s_th + 0x40) = s_pK;
    *(void**)(s_th + 0x48) = s_pQ;
    s_t = 0; s_nTickOn = 0; s_nTickOff = 0;
    s_bHas = false; s_nPeek = 0;
    s_nMsgs = 0; s_iMsg = 0;
    s_nPk = 0; s_bProcOk = true;
    s_nKT = 0; s_nErr = 0; s_nWarn = 0;
}

int main() {
    printf("TH6 start\n"); fflush(stdout);

    // ==== S1: World idle — slide 1000,
    // ticks 0x1d/0x1f, stats recorded
    // ====
    {
        Reset();
        static uint32_t st; st = 0;
        g_ThreadSeams.TimeGet = []() {
            static const uint32_t v[]
                = {1000, 1000, 1050};
            return v[st < 3 ? st++ : 2];
        };
        assert(WorldOnProcess(s_th) == 1);
        g_ThreadSeams.TimeGet = T_Time;
        assert(g_WFirstRun == 1);
        assert(g_WResyncBase == 2000);
        // 1000 + 1000 slide
        assert(s_nKT == 1 &&
               s_aKT[0] == 1000);
        assert(s_aTickOn[0] == 0x1d);
        assert(s_aTickOn[1] == 0x1f);
        assert(g_WCnt == 1);
        assert(g_WCum == 50);
        assert(g_WMax == 50);
        // since = 1050-2000 -> underflow
        // -> idle 0
        assert(g_WIdleMs == 0);
        printf("S1 ok (world idle)\n"); fflush(stdout);
    }

    // ==== S2: UserLogin idle — slide
    // 2000, ticks 0x20/0x22, NO stats,
    // idle propagation ====
    {
        Reset();
        static uint32_t st; st = 0;
        g_ThreadSeams.TimeGet = []() {
            static const uint32_t v[]
                = {1000, 1000, 2100};
            return v[st < 3 ? st++ : 2];
        };
        assert(UserLoginOnProcess(s_th)
               == 1);
        g_ThreadSeams.TimeGet = T_Time;
        assert(g_ULResyncBase == 3000);
        // 1000 + 2000
        assert(s_aTickOn[0] == 0x20);
        assert(s_aTickOn[1] == 0x22);
        // no stats for UL: world counters
        // untouched
        assert(g_WCnt == 0);
        // since = 2100-3000 underflow -> 0
        assert(g_ULIdleMs == 0);
        // run with t inside window:
        ThreadResetStatics();
        static uint32_t st2; st2 = 0;
        g_ThreadSeams.TimeGet = []() {
            uint32_t v = 2000 + st2 * 10;
            st2++;
            return v;
        };
        g_ULFirstRun = 1;
        g_ULResyncBase = 2000;
        UserLoginOnProcess(s_th);
        // t1=2000 t2=2010: slide 2000->
        // 4000; since = 2010-4000 <0 -> 0
        assert(g_ULIdleMs == 0);
        g_ThreadSeams.TimeGet = T_Time;
        printf("S2 ok (userlogin)\n"); fflush(stdout);
    }

    // ==== S3: Chat — the 0x49 WaitMsg
    // tick around Peek + slide 2000 +
    // idle window positive case ====
    {
        Reset();
        static uint32_t st; st = 0;
        g_ThreadSeams.TimeGet = []() {
            static const uint32_t v[]
                = {1000, 1000, 1000};
            return v[st < 3 ? st++ : 2];
        };
        assert(ChatOnProcess(s_th) == 1);
        g_ThreadSeams.TimeGet = T_Time;
        // Chat ONLY: 0x49 around Peek
        assert(s_aTickOn[0] == 0x49);
        assert(s_aTickOn[1] == 0x2f);
        assert(s_aTickOn[2] == 0x31);
        // base = 1000 slide -> 3000;
        // since = 1000-3000 underflow -> 0
        assert(g_CResyncBase == 3000);
        assert(g_CIdleMs == 0);
        // window positive: base reset
        // to now -> since 0 -> idle 2000
        s_t = 1000;
        g_CResyncBase = 2500;
        ChatOnProcess(s_th);   // t1=t2=1000
        // diff = 1000-2500 underflows
        // -> resync
        assert(s_nWarn >= 1);
        assert(std::strcmp(s_aWarn[0],
            "resync CChatKernel::OnTimer"
            " cumulative deviation %dms")
               == 0);
        assert(g_CResyncBase == 1000);
        // since = t2-base = 0 < 2000
        assert(g_CIdleMs == 2000);
        printf("S3 ok (chat)\n"); fflush(stdout);
    }

    // ==== S4: drain — all three use
    // the FIVE-arg ProcessMsg with the
    // raw (packet, arg8, port) and the
    // ERROR pairs; tick ids per class
    // ====
    {
        Reset();
        s_bHas = true;
        s_bProcOk = false;
        s_aMsgs[0] = {{0x77, 7001, 321,
                        0}, true};
        s_aMsgs[1] = {{0x78, 7002, 322,
                        0}, true};
        s_nMsgs = 2;
        s_t = 5000;
        g_WFirstRun = 1; g_WResyncBase =
            4999;
        assert(WorldOnProcess(s_th) == 1);
        assert(s_nPk == 2);
        assert(s_aPk[0] == 7001 &&
               s_aPk[1] == 7002);
        assert(s_aArg8[0] == 321 &&
               s_aArg8[1] == 322);
        assert(s_aPort[0] == 0x77 &&
               s_aPort[1] == 0x78);
        assert(s_nErr == 2);
        assert(std::strcmp(s_aErr[0],
            "CWorldThread::OnProcess"
            " ProcessMsg returned error"
            " with packet:%d, port:%d")
               == 0);
        assert(s_aErrPk[0] == 7001 &&
               s_aErrPort[0] == 0x77);
        // drain ticks: 0x1d, 0x1e, 0x1e
        assert(s_aTickOn[0] == 0x1d);
        assert(s_aTickOn[1] == 0x1e);
        assert(s_aTickOn[2] == 0x1e);
        // now UL drain
        Reset();
        s_bHas = true; s_bProcOk = true;
        s_aMsgs[0] = {{0x81, 8001, 1, 0},
                       true};
        s_nMsgs = 1;
        g_ULFirstRun = 1;
        g_ULResyncBase = 100;
        assert(UserLoginOnProcess(s_th)
               == 1);
        assert(s_nPk == 1 && s_nErr == 0);
        assert(s_aTickOn[0] == 0x20);
        assert(s_aTickOn[1] == 0x21);
        printf("S4 ok (drain)\n"); fflush(stdout);
    }

    // ==== S5: resync — World text + UL
    // text + base reset ====
    {
        Reset();
        s_t = 99999;
        g_WFirstRun = 1; g_WResyncBase = 1;
        WorldOnProcess(s_th);
        assert(std::strcmp(s_aWarn[0],
            "resync CWorldKernel::OnTimer"
            " cumulative deviation %dms")
               == 0);
        assert(g_WResyncBase == 99999);
        Reset();
        s_t = 88888;
        g_ULFirstRun = 1;
        g_ULResyncBase = 5;
        UserLoginOnProcess(s_th);
        assert(std::strcmp(s_aWarn[0],
            "resync CUserKernel::OnTimer"
            " cumulative deviation %dms")
               == 0);
        assert(g_ULResyncBase == 88888);
        printf("S5 ok (resync)\n"); fflush(stdout);
    }

    printf("TH6 ALL-OK\n");
    return 0;
}
