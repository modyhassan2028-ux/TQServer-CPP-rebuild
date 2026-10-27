// Path-A wave 4 test — CMapGroupThread::
// OnProcess (raw-verified)
#include <cassert>
#include <cstdio>
#include <cstring>
#include "MsgMapGroupThread.h"
using namespace msg;

static uint32_t s_t;   // fake clock
static uint32_t s_aTickOn[16]; static int s_nTickOn;
static uint32_t s_nTickOff;
static uint32_t T_Time() { return s_t; }
static void T_TickOn(uint32_t id) {
    s_aTickOn[s_nTickOn < 16 ?
        s_nTickOn++ : 15] = id;
}
static void T_TickOff() { s_nTickOff++; }

static void* s_pQ = (void*)0x51;
static void* s_pK = (void*)0x42;
static uint32_t s_aPeekMs[4]; static int s_nPeek;
static bool s_bHas = false;
static bool T_Peek(void* q, uint32_t ms) {
    assert(q == s_pQ);
    s_aPeekMs[s_nPeek < 4 ? s_nPeek++ : 3]
        = ms;
    return s_bHas;
}
static uint32_t s_qId = 0x10;   // -> idx 2
static uint32_t T_GetId(void* q) {
    assert(q == s_pQ); return s_qId;
}
// scripted WaitMsg results
struct SMsg { SMGMsgInfo inf; bool ok; };
static SMsg s_aMsgs[8]; static int s_nMsgs;
static int s_iMsg;
static uint32_t s_aWSize[8]; static int s_nWSize;
static bool T_Wait(void* q, int32_t f1,
        int32_t f2, uint32_t size,
        uint8_t* buf, SMGMsgInfo* inf) {
    assert(q == s_pQ);
    assert(f1 == -1 && f2 == -1);
    s_aWSize[s_nWSize < 8 ? s_nWSize++ : 7]
        = size;
    if (s_iMsg >= s_nMsgs) return false;
    *inf = s_aMsgs[s_iMsg].inf;
    // the raw writes the packet into
    // buf too; our kernel seam reads
    // buf — just mark it
    std::memset(buf, 0xAB, 4);
    return s_aMsgs[s_iMsg++].ok;
}
// kernel ProcessMsg recorder
static uint32_t s_aPk[8]; static uint32_t
    s_aArg58[8]; static uint8_t* s_aBuf[8];
static int s_nPk; static bool s_bProcOk;
static bool T_Proc(void* k, uint32_t pk,
        uint8_t* buf, uint32_t a58) {
    assert(k == s_pK);
    s_aPk[s_nPk < 8 ? s_nPk++ : 7] = pk;
    s_aBuf[s_nPk < 8 ? s_nPk - 1 : 7] = buf;
    s_aArg58[s_nPk < 8 ? s_nPk - 1 : 7] = a58;
    return s_bProcOk;
}
static uint32_t s_aKTimer[4]; static int s_nKTimer;
static void T_KTimer(void* k, uint32_t t) {
    assert(k == s_pK);
    s_aKTimer[s_nKTimer < 4 ?
        s_nKTimer++ : 3] = t;
}
static char s_aErr[4][200];
static uint32_t s_aErrPk[4], s_aErrPort[4];
static int s_nErr;
static void T_Err(const char* f, uint32_t pk,
        uint32_t port) {
    std::snprintf(s_aErr[s_nErr], 199, "%s",
                  f);
    s_aErrPk[s_nErr] = pk;
    s_aErrPort[s_nErr] = port;
    s_nErr++;
}
static char s_aWarn[4][200]; static int s_nWarn;
static void T_Warn(const char* f) {
    std::snprintf(s_aWarn[s_nWarn++], 199,
                  "%s", f);
}

static uint8_t s_th[0x58];

static void Reset() {
    std::memset(&g_MapGroupSeams, 0,
        sizeof g_MapGroupSeams);
    SMapGroupSeams& s = g_MapGroupSeams;
    s.QGetId = T_GetId;
    s.QWaitMsg = T_Wait;
    s.QPeekMsg = T_Peek;
    s.KProcessMsg = T_Proc;
    s.KOnTimer = T_KTimer;
    s.TimeGet = T_Time;
    s.TickOn = T_TickOn;
    s.TickOff = T_TickOff;
    s.LogError = T_Err;
    s.LogWarning = T_Warn;
    MGResetStatics();
    std::memset(s_th, 0, sizeof s_th);
    *(void**)(s_th + 0x40) = s_pK;
    *(void**)(s_th + 0x48) = s_pQ;
    s_t = 0; s_nTickOn = 0; s_nTickOff = 0;
    s_nPeek = 0; s_bHas = false;
    s_qId = 0x10;
    s_nMsgs = 0; s_iMsg = 0; s_nWSize = 0;
    s_nPk = 0; s_bProcOk = true;
    s_nKTimer = 0;
    s_nErr = 0; s_nWarn = 0;
}

int main() {
    printf("TH4 start\n"); fflush(stdout);

    // ==== S1: first-run init + the
    // idle path (no msg): OnTimer +
    // resync slide + stats + idle ====
    {
        Reset();
        // stepping clock: first-run base
        // 5000, t1 5000, t2 5200
        static uint32_t s1Step;
        s1Step = 0;
        g_MapGroupSeams.TimeGet = []() {
            static const uint32_t v[]
                = {5000, 5000, 5200};
            return v[s1Step < 3 ?
                s1Step++ : 2];
        };
        assert(MapGroupOnProcess(s_th) == 1);
        g_MapGroupSeams.TimeGet = T_Time;
        assert(g_MGFirstRun == 1);
        // no msg: kernel OnTimer(t1)
        assert(s_nKTimer == 1);
        assert(s_aKTimer[0] == 5000);
        // slide: diff 0 <= 0x2710
        assert(g_MGResyncBase == 5125);
        assert(s_nWarn == 0);
        // tick order: 0x47, 0, 0xc
        assert(s_nTickOn == 3);
        assert(s_aTickOn[0] == 0x47);
        assert(s_aTickOn[1] == 0);
        assert(s_aTickOn[2] == 0xc);
        // stats idx = 0x10-0xe = 2
        assert(g_MGCnt[2] == 1);
        assert(g_MGCum[2] == 200);
        assert(g_MGMax[2] == 200);
        // idle: since = 5200-5125 = 75
        assert(g_MGIdleMs == 50);
        printf("S1 ok (idle path)\n"); fflush(stdout);
    }

    // ==== S2: resync — deviation
    // > 0x2710: WARNING (fmt only,
    // no args) + base = t1 ====
    {
        Reset();
        s_t = 50000;
        g_MGFirstRun = 1;
        g_MGResyncBase = 10000;   // old
        MapGroupOnProcess(s_th);
        assert(s_nWarn == 1);
        assert(std::strcmp(s_aWarn[0],
            "resync CMapGroupKernel::"
            "OnTimer cumulative "
            "deviation %dms") == 0);
        assert(g_MGResyncBase == 50000);
        printf("S2 ok (resync)\n"); fflush(stdout);
    }

    // ==== S3: the drain loop — 2 ok
    // msgs + 1 failing: packet/port in
    // the ERROR log, buf+arg58 pass
    // through, size 0x418, loop ends
    // at WaitMsg false ====
    {
        Reset();
        g_MGFirstRun = 1;
        g_MGResyncBase = 100;
        s_bHas = true;
        s_aMsgs[0] = {{0x1e61, 1001, 55,
                        0}, true};
        s_aMsgs[1] = {{0x1e62, 1002, 66,
                        0}, true};
        s_aMsgs[2] = {{0x1e63, 1003, 77,
                        0}, true};
        s_nMsgs = 3;
        s_bProcOk = false;   // all fail
        s_t = 2000;
        assert(MapGroupOnProcess(s_th)
               == 1);
        // 3 accepted + the final
        // false = 4 WaitMsg calls
        assert(s_nWSize == 4);
        assert(s_aWSize[0] == 0x418);
        assert(s_aWSize[3] == 0x418);
        assert(s_nPk == 3);
        assert(s_aPk[0] == 1001 &&
               s_aPk[1] == 1002 &&
               s_aPk[2] == 1003);
        assert(s_aArg58[0] == 55 &&
               s_aArg58[2] == 77);
        assert(s_aBuf[0] != nullptr);
        // three ERROR logs with the
        // raw (packet, port) pair
        assert(s_nErr == 3);
        assert(std::strcmp(s_aErr[0],
            "CMapGroupThread::OnProcess"
            " ProcessMsg returned error"
            " with packet:%d, port:%d")
               == 0);
        assert(s_aErrPk[0] == 1001 &&
               s_aErrPort[0] == 0x1e61);
        assert(s_aErrPk[2] == 1003 &&
               s_aErrPort[2] == 0x1e63);
        // no kernel OnTimer ran
        assert(s_nKTimer == 0);
        printf("S3 ok (drain loop)\n"); fflush(stdout);
    }

    // ==== S4: stats clamp — idx > 4
    // (queueId < 0xe or > 0x12) skips
    // the arrays; max keeps max ====
    {
        Reset();
        g_MGFirstRun = 1;
        g_MGResyncBase = 0;
        s_qId = 3;   // 3-0xe underflows
        s_t = 1000;
        MapGroupOnProcess(s_th);
        assert(g_MGCnt[0] == 0 &&
               g_MGCnt[1] == 0 &&
               g_MGCnt[2] == 0 &&
               g_MGCnt[3] == 0 &&
               g_MGCnt[4] == 0);
        // now an in-range id + a real
        // elapsed: tick the clock
        Reset();
        g_MGFirstRun = 1;
        g_MGResyncBase = 100000;
        s_qId = 0x12;   // idx 4
        // simulate elapsed via two
        // TimeGet values: hook via a
        // counter (t1 then t2)
        // simplest: set s_t through a
        // custom TimeGet that steps
        auto oldT = g_MapGroupSeams.TimeGet;
        static uint32_t step;
        step = 0;
        g_MapGroupSeams.TimeGet = []() {
            uint32_t v = 1000 + step;
            step += 7;
            return v;
        };
        MapGroupOnProcess(s_th);
        g_MapGroupSeams.TimeGet = oldT;
        assert(g_MGCnt[4] == 1);
        assert(g_MGCum[4] == 7);   // t2-t1
        assert(g_MGMax[4] == 7);
        printf("S4 ok (stats)\n"); fflush(stdout);
    }

    // ==== S5: idle propagation — the
    // NEXT PeekMsg call sees the idle
    // computed by the previous run ====
    {
        Reset();
        g_MGFirstRun = 1;
        g_MGResyncBase = 100000;
        s_t = 100125;   // slide to 100125,
        // since = t2-base = 0 -> 125
        MapGroupOnProcess(s_th);
        assert(g_MGIdleMs == 125);
        assert(s_aPeekMs[0] == 0);   // pre
        // second run: Peek gets 125
        s_t = 100250;   // base 100125 +
        // 125 = 100250; slide keeps it
        MapGroupOnProcess(s_th);
        assert(s_aPeekMs[1] == 125);
        // a resync run: deviation huge
        // -> WARNING, base = t1, and
        // the idle goes back to 125
        s_t = 200000;
        g_MGResyncBase = 1000;
        MapGroupOnProcess(s_th);
        assert(s_nWarn >= 1);
        assert(g_MGIdleMs == 125);
        // the next same-clock run
        // slides ahead -> since
        // underflows -> idle 0
        MapGroupOnProcess(s_th);
        assert(g_MGIdleMs == 0);
        assert(s_aPeekMs[3] == 125);
        printf("S5 ok (idle)\n"); fflush(stdout);
    }

    printf("TH4 ALL-OK\n");
    return 0;
}
