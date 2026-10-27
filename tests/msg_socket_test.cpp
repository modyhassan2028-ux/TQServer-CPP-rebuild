// Path-A wave 5 test — CSocketThread::
// OnProcess (raw-verified)
#include <cassert>
#include <cstdio>
#include <cstring>
#include "MsgSocketThread.h"
using namespace msg;

static uint32_t s_t;
static uint32_t T_Time() { return s_t; }
static uint32_t s_aTickOn[16]; static int s_nTickOn;
static uint32_t s_nTickOff;
static void T_TickOn(uint32_t id) {
    s_aTickOn[s_nTickOn < 16 ?
        s_nTickOn++ : 15] = id;
}
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
    std::memset(buf, 0xCD, 4);
    return s_aMsgs[s_iMsg++].ok;
}
static uint32_t s_aPk[8]; static uint32_t
    s_aArg8[8]; static uint32_t
    s_aPort5[8]; static int s_nPk;
static bool s_bProcOk = true;
static bool T_Proc5(void* k, uint32_t pk,
        uint8_t* buf, uint32_t a8,
        uint32_t port) {
    assert(k == s_pK && buf != nullptr);
    s_aPk[s_nPk < 8 ? s_nPk++ : 7] = pk;
    s_aArg8[s_nPk < 8 ? s_nPk - 1 : 7] = a8;
    s_aPort5[s_nPk < 8 ? s_nPk - 1 : 7] =
        port;
    return s_bProcOk;
}
static uint32_t s_aKTimer[4]; static int s_nKT;
static void T_KTimer(void* k, uint32_t t) {
    assert(k == s_pK);
    s_aKTimer[s_nKT < 4 ? s_nKT++ : 3] = t;
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
static char s_aWarn[2][200];
static int s_nWarn;
static void T_Warn(const char* f) {
    std::snprintf(s_aWarn[s_nWarn < 2 ?
        s_nWarn++ : 1], 199, "%s", f);
}

static uint8_t s_th[0x58];

static void Reset() {
    std::memset(&g_SocketSeams, 0,
        sizeof g_SocketSeams);
    SSocketSeams& s = g_SocketSeams;
    s.QWaitMsg = T_Wait;
    s.QPeekMsg = T_Peek;
    s.KProcessMsg5 = T_Proc5;
    s.KOnTimer = T_KTimer;
    s.TimeGet = T_Time;
    s.TickOn = T_TickOn;
    s.TickOff = T_TickOff;
    s.LogError = T_Err;
    s.LogWarning = T_Warn;
    SockResetStatics();
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
    printf("TH5 start\n"); fflush(stdout);

    // ==== S1: idle path — first-run,
    // OnTimer, slide +0x4c, tick order
    // 0x23/0x2a, direct stats ====
    {
        Reset();
        static uint32_t st;
        st = 0;
        g_SocketSeams.TimeGet = []() {
            static const uint32_t v[]
                = {1000, 1000, 1080};
            return v[st < 3 ? st++ : 2];
        };
        assert(SocketOnProcess(s_th) == 1);
        g_SocketSeams.TimeGet = T_Time;
        assert(g_SockFirstRun == 1);
        assert(g_SockResyncBase == 1076);
        // base 1000 + 0x4c
        assert(s_nKT == 1 &&
               s_aKTimer[0] == 1000);
        assert(s_nTickOn == 2);
        assert(s_aTickOn[0] == 0x23);
        assert(s_aTickOn[1] == 0x2a);
        // stats: elapsed 80
        assert(g_SockCnt == 1);
        assert(g_SockCum == 80);
        assert(g_SockMax == 80);
        // idle: 1080-1076 = 4 -> 76-4=72
        assert(g_SockIdleMs == 72);
        assert(s_nWarn == 0);
        printf("S1 ok (idle)\n"); fflush(stdout);
    }

    // ==== S2: resync — diff > 0x2710:
    // WARNING fmt-only + base = t1 ====
    {
        Reset();
        s_t = 50000;
        g_SockFirstRun = 1;
        g_SockResyncBase = 1000;
        SocketOnProcess(s_th);
        assert(s_nWarn == 1);
        assert(std::strcmp(s_aWarn[0],
            "resync CSocketKernel::"
            "OnTimer cumulative "
            "deviation %dms") == 0);
        assert(g_SockResyncBase == 50000);
        printf("S2 ok (resync)\n"); fflush(stdout);
    }

    // ==== S3: drain — FIVE-arg
    // ProcessMsg with (packet, arg8,
    // port) raw order + the ERROR pairs;
    // ticks 0x24 ====
    {
        Reset();
        g_SockFirstRun = 1;
        g_SockResyncBase = 100;
        s_bHas = true;
        s_bProcOk = false;
        s_aMsgs[0] = {{0x99, 5001, 111,
                        0}, true};
        s_aMsgs[1] = {{0x9a, 5002, 222,
                        0}, true};
        s_nMsgs = 2;
        s_t = 2000;
        assert(SocketOnProcess(s_th) == 1);
        assert(s_nPk == 2);
        assert(s_aPk[0] == 5001 &&
               s_aPk[1] == 5002);
        assert(s_aArg8[0] == 111 &&
               s_aArg8[1] == 222);
        // the 5th arg = info+0 = port
        assert(s_aPort5[0] == 0x99 &&
               s_aPort5[1] == 0x9a);
        assert(s_nErr == 2);
        assert(std::strcmp(s_aErr[0],
            "CSocketThread::OnProcess"
            " ProcessMsg returned error"
            " with packet:%d, port:%d")
               == 0);
        assert(s_aErrPk[0] == 5001 &&
               s_aErrPort[0] == 0x99);
        assert(s_nKT == 0);   // no timer
        // tick order: 0x23, 0x24, 0x24
        assert(s_aTickOn[0] == 0x23);
        assert(s_aTickOn[1] == 0x24);
        assert(s_aTickOn[2] == 0x24);
        printf("S3 ok (drain)\n"); fflush(stdout);
    }

    // ==== S4: max keeps the largest;
    // idle zero at/after window ====
    {
        Reset();
        g_SockFirstRun = 1;
        g_SockResyncBase = 0;
        // three runs, growing elapsed
        static uint32_t st4; st4 = 0;
        g_SocketSeams.TimeGet = []() {
            uint32_t v = 100 + st4 * 50;
            st4++;
            return v;
        };
        for (int i = 0; i < 3; i++) {
            SocketOnProcess(s_th);
            g_SockResyncBase =
                g_SockResyncBase;  // slide
        }
        // each run elapsed = 50
        assert(g_SockCnt == 3);
        assert(g_SockCum == 150);
        assert(g_SockMax == 50);
        // idle: t2-base; the base slid
        // +0x4c each run -> t2 - base
        // is large -> idle 0
        assert(g_SockIdleMs == 0);
        printf("S4 ok (stats)\n"); fflush(stdout);
    }

    // ==== S5: idle propagation to the
    // next PeekMsg (window 0x4c) ====
    {
        Reset();
        g_SockFirstRun = 1;
        g_SockResyncBase = 100000;
        s_t = 100076;   // base+76: slide to
        // 100076, since=0 -> idle 76
        SocketOnProcess(s_th);
        assert(g_SockResyncBase == 100076);
        assert(g_SockIdleMs == 76);
        assert(s_aPeek[0] == 0);
        SocketOnProcess(s_th);   // peek 76
        assert(s_aPeek[1] == 76);
        printf("S5 ok (idle)\n"); fflush(stdout);
    }

    printf("TH5 ALL-OK\n");
    return 0;
}
