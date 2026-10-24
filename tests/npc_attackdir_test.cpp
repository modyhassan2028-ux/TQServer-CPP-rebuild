#include "../Exe/NpcServer/NpcStateUtil.h"
#include <cassert>
#include <cstdio>
#include <vector>
using namespace npc;

struct Cfg {
    bool bHasMap = true, bMapObj80 = true,
         bWalkable = true;
    int nSubX = 100, nSubY = 100;
    int nGenX = 50, nGenY = 50;
    int nCurDist = 0;        // subDist(x,y) result
    int nRand = 0;
    CNpcTargetSeam* pTarget = nullptr;
    int nTargetId = 0;
    int nField3C = 0;
    int nWalkCalls = 0, nLogs = 0;
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
            [this](int x, int y, int dir, uint32_t){
                assert(x == 100 && y == 100);
                assert(dir >= 0 && dir < 8);
                ++nWalkCalls;
                return bWalkable; };
        d.m_fnTimeGet = []{ return 1000; };
        d.m_fnRandGet = [this](uint32_t m){
            return (uint32_t)(nRand < (int)m
                ? nRand : 0); };
        d.m_fnGenGetSpawn =
            [this](int& a, int& b){ a = nGenX;
                                     b = nGenY; };
        d.m_fnFindTarget =
            [this](int id) -> CNpcTargetSeam* {
                return id == nTargetId ? pTarget
                                       : nullptr; };
        d.m_fnSubHasMap80 = [this]{
            return bMapObj80; };
        d.m_bHasMap = bHasMap;
        d.m_nTargetId = nTargetId;
        d.m_nField3C = nField3C;
        return d;
    }
};

int main() {
    // ===== 1. no map: the literal error ============
    {
        Cfg c; c.bHasMap = false; auto d = c.Make();
        assert(!CNpcAttackDir(d, 3));
        assert(c.nLogs == 1);
    }
    // ===== 2. the full scan: 3c==0 (maximize) ======
    // sub at (100,100), gen ref (50,50).
    // subDist is a stub returning nCurDist, so the
    // improvement test compares the stub ref with
    // the true chebyshev d. Set ref (nCurDist) = 5,
    // field3c=0 (sign -1): improvement when
    // 0 < -(5 - d) i.e. d > 5. All 8 cells
    // walkable: d from (100+dx, 100+dy) to (50,50)
    // is ~50, so ALL dirs improve; the greedy keeps
    // the LAST improving one in scan order from
    // rand r. dirs 0..7 excluding curDir=2:
    // scan r=0: dirs 0,1,3,4,5,6,7. The last
    // improving = 7 (dx=1, dy=1 -> d = 51). With
    // ref updated to each d, later d must exceed
    // the previous best.
    {
        Cfg c; c.nCurDist = 5; auto d = c.Make();
        // true chebyshev values per dir (ref 50,50):
        // 0:(101,100)->51  1:(99,100)->51
        // 3:(99,99)->51    4:(100,99)->51
        // 5:(99,99)... hmm compute exactly below
        int exp[8];
        for (int t = 0; t < 8; t++) {
            static const int dx[8] =
                { 0,-1,-1,-1, 0, 1, 1, 1 };
            static const int dy[8] =
                { 1, 1, 0,-1,-1,-1, 0, 1 };
            int ax = std::abs(100 + dx[t] - 50);
            int ay = std::abs(100 + dy[t] - 50);
            exp[t] = ax > ay ? ax : ay;
        }
        // all 50 or 51 -> every non-cur dir improves
        // only if strictly greater than the running
        // ref. first candidate sets ref=exp[d0].
        (void)exp;
        assert(CNpcAttackDir(d, 2));
        // greedy: keep the best (max, since 3c==0)
        int nBestVal = -1, nBestDir = -1;
        int nRef = 5;
        for (int i = 0; i < 8; i++) {
            int t = i % 8;
            if (t == 2) continue;
            int v = exp[t];
            if (0 < -1 * (nRef - v)) {
                nBestDir = t; nRef = v;
            }
        }
        (void)nBestVal;
        assert(d.m_dirQueue[0] == nBestDir);
        assert(d.m_dwField2C == 1);
        assert(c.nWalkCalls == 7);
    }
    // ===== 3. 3c != 0: minimize (sign +1) ==========
    // ref (nCurDist) = 60: improvement when
    // 0 < (60 - d) i.e. d < 60 - all improve, the
    // MINIMUM wins (last improving = the smallest)
    {
        Cfg c; c.nCurDist = 60; c.nField3C = 1;
        auto d = c.Make();
        assert(CNpcAttackDir(d, 2));
        int nRef = 60, nBestDir = -1;
        static const int dx[8] =
            { 0,-1,-1,-1, 0, 1, 1, 1 };
        static const int dy[8] =
            { 1, 1, 0,-1,-1,-1, 0, 1 };
        for (int i = 0; i < 8; i++) {
            int t = i % 8;
            if (t == 2) continue;
            int ax = std::abs(100 + dx[t] - 50);
            int ay = std::abs(100 + dy[t] - 50);
            int v = ax > ay ? ax : ay;
            if (0 < 1 * (nRef - v)) {
                nBestDir = t; nRef = v;
            }
        }
        assert(d.m_dirQueue[0] == nBestDir);
    }
    // ===== 4. target position overrides the gen ===
    // ref = target pos (150,150): sub at (100,100)
    // -> d for dir 7 (101,101) = 49; curDir=2.
    // nCurDist must exceed... set 3c!=0 and
    // nCurDist=100: all improve, minimum wins.
    {
        Cfg c; c.nCurDist = 100; c.nField3C = 1;
        CNpcTargetSeam t; t.m_nX = 150; t.m_nY = 150;
        c.pTarget = &t; c.nTargetId = 77;
        auto d = c.Make();
        assert(CNpcAttackDir(d, 2));
        static const int dx[8] =
            { 0,-1,-1,-1, 0, 1, 1, 1 };
        static const int dy[8] =
            { 1, 1, 0,-1,-1,-1, 0, 1 };
        int nRef = 100, nBestDir = -1;
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
    // ===== 5. not walkable anywhere -> the leak =====
    // uRet = 0 after the last failed 4bff0 -> false
    {
        Cfg c; c.bWalkable = false; auto d = c.Make();
        assert(!CNpcAttackDir(d, 2));
        assert(d.m_dwField2C == 0);
    }
    // ===== 6. map object null: leak = 0 -> false ===
    {
        Cfg c; c.bMapObj80 = false;
        auto d = c.Make();
        assert(!CNpcAttackDir(d, 2));
        assert(c.nWalkCalls == 0);
    }
    // ===== 7. no improvement at all: 3c==0, ========
    // ===== d never > ref (nCurDist huge) ===========
    // last iteration computed d -> leak nonzero
    {
        Cfg c; c.nCurDist = 999; auto d = c.Make();
        // sign -1: 0 < -(999 - d) needs d > 999,
        // never -> no best. uRet leaks the last
        // computed chebyshev (~51) -> true (the
        // ORIGINAL low-byte leak, verbatim)
        assert(CNpcAttackDir(d, 2));
        assert(d.m_dwField2C == 0);   // unchanged
        assert(d.m_nField40 == 0);
    }

    printf("NPC_ATTACKDIR_OK: FUN_140058260 attack-dir"
           " pick verbatim (map+0x98 log gate, +0x2c=0,"
           " gen vt+0x28 reference overridden by the"
           " +0x84 target position, sub vt+8 ref dist,"
           " RandGet(8) scan start with signed-mod"
           " dirs skipping curDir, sub vt+0x80 map"
           " null -> leak 0, FUN_14004bff0(map,x,y,dir,"
           "u48,0x1a) walk gate, DAT_1400c89d0/89f0"
           " candidate cells (=the 140087d50 wander"
           " table, binary-verified), chebyshev distance,"
           " +0x3c sign: 0 -> maximize / 1 -> minimize"
           " with greedy ref update, +0x40 best dir +"
           " +0x2c=1 on success, and the verbatim"
           " uVar9 low-byte distance leak on the"
           " no-best fall-through)\n");
    return 0;
}
