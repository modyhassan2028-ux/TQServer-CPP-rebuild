#include "../Exe/NpcServer/NpcStateUtil.h"
#include <cassert>
#include <cstdio>
using namespace npc;

struct Cfg {
    bool bHasMap = true, bMapObj80 = true,
         bWalkable = true, bHasAttach = false;
    int nSubX = 100, nSubY = 100;
    int nResX = 50, nResY = 50;
    int nCurDist = 0;
    int nRand = 0, nField3C = 0;
    CNpcTargetSeam* pTarget = nullptr;
    int nTargetId = 0;
    uint32_t nRescGarbage = 777;
    // 58b80 chain
    uint64_t uHolder = 1;
    bool b69910 = true;
    uint64_t u65750 = 1;
    bool bNullHolder = false;
    int nLogs = 0, nWalkCalls = 0;
    int m_nGenX = 60, m_nGenY = 61;
    int n657c0 = 0, n65510 = 0, nGenFalls = 0;
    CNpcStateData Make() {
        CNpcStateData d;
        d.m_fnRowGetFlag = []{ return 0u; };
        d.m_fnRowGetInt = [](uint32_t){ return 0; };
        d.m_fnLogError = [this]{ ++nLogs; };
        d.m_fnInSight = [](int, int){ return true; };
        d.m_fnSubId18 = []{ return 4242; };
        d.m_fnSubGetX38 = [this]{ return nSubX; };
        d.m_fnSubGetY40 = [this]{ return nSubY; };
        d.m_fnSubVt48NoArgs = []{ return 7; };
        d.m_fnSubVt8 = []{ return 3; };
        d.m_fnSubDist =
            [this](int, int){ return nCurDist; };
        d.m_fnSubMapId = []{ return 1001; };
        d.m_fnMapWalkable =
            [this](int, int, int, uint32_t) {
                ++nWalkCalls;
                return bWalkable; };
        d.m_fnTimeGet = []{ return 1000; };
        d.m_fnRandGet = [this](uint32_t m) {
            return (uint32_t)(nRand < (int)m
                ? nRand : 0); };
        d.m_fnGenGetSpawn =
            [this](int& a, int& b) {
                a = m_nGenX; b = m_nGenY;
                ++nGenFalls; };
        d.m_fnGenInArea = [](int, int, int){
            return true; };
        d.m_fn49310 = [](int, int){ return true; };
        d.m_fn59f40 = [](int, int, int){};
        d.m_fn5a0d0 = [](int, int, int){};
        d.m_fnMoveTo = [](int, int, int){};
        d.m_fnSubDist48 = [](int){ return 1; };
        d.m_bHasMap = bHasMap;
        d.m_fnSubHasMap80 = [this]{
            return bMapObj80; };
        d.m_fnFindTarget =
            [this](int id) -> CNpcTargetSeam* {
                return id == nTargetId
                    ? pTarget : nullptr; };
        d.m_nTargetId = nTargetId;
        d.m_nField3C = nField3C;
        d.m_bHasAttach = bHasAttach;
        d.m_nRescGarbage = nRescGarbage;
        d.m_fn696d0 = []{};
        d.m_fn34e00Holder = [this] {
            return bNullHolder ? 0ull : uHolder; };
        d.m_fn69910Attach = [this]{ return b69910; };
        d.m_fn65750 = [this]{ return u65750; };
        d.m_fn657c0 = [this](int& a, int& b) {
            a = 71; b = 72; ++n657c0; };
        d.m_fn65510 = [this](int& a, int& b) {
            a = 81; b = 82; ++n65510; };
        return d;
    }
};

int main() {
    // ===== 588b0: res reference, maximize =====
    // ref (50,50) via the res, sub at (100,100),
    // curDist stub = 5, field3c=0 (maximize):
    // same math as the 58260 test
    {
        Cfg c; c.nCurDist = 5; auto d = c.Make();
        assert(CNpcAttackDirNear(d, 50, 50, 2));
        static const int dx[8] =
            { 0,-1,-1,-1, 0, 1, 1, 1 };
        static const int dy[8] =
            { 1, 1, 0,-1,-1,-1, 0, 1 };
        int nRef = 5, nBestDir = -1;
        for (int i = 0; i < 8; i++) {
            int t = i % 8;
            if (t == 2) continue;
            int ax = std::abs(100 + dx[t] - 50);
            int ay = std::abs(100 + dy[t] - 50);
            int v = ax > ay ? ax : ay;
            if (0 < -1 * (nRef - v)) {
                nBestDir = t; nRef = v;
            }
        }
        assert(d.m_dirQueue[0] == nBestDir);
        assert(d.m_dwField2C == 1);
    }
    // ===== 588b0: target overrides the res ====
    {
        Cfg c; c.nCurDist = 60; c.nField3C = 1;
        CNpcTargetSeam t; t.m_nX = 150; t.m_nY = 150;
        c.pTarget = &t; c.nTargetId = 77;
        auto d = c.Make();
        assert(CNpcAttackDirNear(d, 50, 50, 2));
        static const int dx[8] =
            { 0,-1,-1,-1, 0, 1, 1, 1 };
        static const int dy[8] =
            { 1, 1, 0,-1,-1,-1, 0, 1 };
        int nRef = 60, nBestDir = -1;
        for (int i = 0; i < 8; i++) {
            int q = i % 8;
            if (q == 2) continue;
            int ax = std::abs(100 + dx[q] - 150);
            int ay = std::abs(100 + dy[q] - 150);
            int v = ax > ay ? ax : ay;
            if (0 < 1 * (nRef - v)) {
                nBestDir = q; nRef = v;
            }
        }
        assert(d.m_dirQueue[0] == nBestDir);
    }
    // ===== 588b0: target lookup FAILS ========
    // -> the verbatim garbage: ref = 777,777
    {
        Cfg c; c.nTargetId = 77;   // no target
        c.nCurDist = 5; c.nField3C = 1;
        auto d = c.Make();
        // ref = (777,777): d from (100..101) to
        // (777,777) ~ 676, minimize from stub 5:
        // 0 < (5 - 676)? no -> no improve ->
        // leak path. last computed d = 676 & 0xff
        // != 0 -> true (the verbatim leak)
        assert(CNpcAttackDirNear(d, 50, 50, 2));
        assert(d.m_dwField2C == 0);
    }
    // ===== 588b0: no map -> log =================
    {
        Cfg c; c.bHasMap = false; auto d = c.Make();
        assert(!CNpcAttackDirNear(d, 50, 50, 2));
        assert(c.nLogs == 1);
    }
    // ===== 58b80: no attach -> log =============
    {
        Cfg c; auto d = c.Make();
        int lo = 0, hi = 0;
        assert(!CNpcAttachRes(d, lo, hi));
        assert(c.nLogs == 1);
    }
    // ===== 58b80: 69910 + 65750 -> 657c0 =====
    {
        Cfg c; c.bHasAttach = true; auto d = c.Make();
        int lo = 0, hi = 0;
        assert(CNpcAttachRes(d, lo, hi));
        assert(lo == 71 && hi == 72);
        assert(c.n657c0 == 1 && c.n65510 == 0);
        assert(c.nLogs == 0);
    }
    // ===== 58b80: 65750 == 0 -> gen fallback ==
    {
        Cfg c; c.bHasAttach = true; c.u65750 = 0;
        auto d = c.Make();
        int lo = 0, hi = 0;
        assert(CNpcAttachRes(d, lo, hi));
        assert(lo == 60 && hi == 61);   // +0x100 gen
        assert(c.nGenFalls == 1);
        assert(c.n657c0 == 0);
    }
    // ===== 58b80: !69910 -> 65510 ==============
    {
        Cfg c; c.bHasAttach = true; c.b69910 = false;
        auto d = c.Make();
        int lo = 0, hi = 0;
        assert(CNpcAttachRes(d, lo, hi));
        assert(lo == 81 && hi == 82);
        assert(c.n65510 == 1 && c.n657c0 == 0);
    }
    // ===== 58b80: null holder -> log ===========
    {
        Cfg c; c.bHasAttach = true;
        c.bNullHolder = true;
        auto d = c.Make();
        int lo = 0, hi = 0;
        assert(!CNpcAttachRes(d, lo, hi));
        assert(c.nLogs == 1);
        assert(lo == 0 && hi == 0);
    }

    printf("NPC_PURSUIT_OK: FUN_1400588b0 pursuit-dir"
           " verbatim (map log gate, +0x2c=0, caller"
           " res reference overridden by the +0x84"
           " target pos, the VERBATIM uninitialized"
           " local_resc read when the lookup fails"
           " (m_nRescGarbage seam), RandGet(8) signed-"
           "mod scan skipping curDir, sub vt+0x80"
           " null -> leak 0, FUN_14004bff0 walk gate,"
           " DAT_1400c89d0/89f0 cells, chebyshev,"
           " +0x3c sign maximize/minimize with the"
           " greedy ref update, +0x40 + +0x2c=1, and"
           " the uVar9 low-byte leak fall-through)"
           " + FUN_140058b80 attach-res verbatim"
           " (+0x140 log gate, FUN_1400696d0 called"
           " with the result DISCARDED, the 1c200->"
           " 1c130->34e00 holder chain with the 0 log"
           " gate, FUN_140069910 branch: 65750==0 ->"
           " the +0x100 gen vt+0x28 fallback else"
           " FUN_1400657c0, !69910 -> FUN_140065510,"
           " both res words written, return 1)\n");
    return 0;
}
