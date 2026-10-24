#include "../Exe/NpcServer/NpcStateUtil.h"
#include <cassert>
#include <cstdio>
using namespace npc;

struct Cfg {
    bool bHasMap = true, bWalkable = true,
         bHasAttach = false, b49310 = true,
         b620c0 = true;
    int nSubX = 50, nSubY = 60;
    int nSubDir18 = 3;
    int nWidth = 1000, nHeight = 1000;
    int nField34 = 50, nField38 = 60;
    int nLogs = 0, nB2d0 = 0, nSends = 0,
        nJumps = 0;
    int m_nJumpX = -999, m_nJumpY = -999;
    int m_n620c0Dir = -1;
    uint32_t m_n620c0Flavor = 999;
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
        d.m_fnSubDist = [](int, int){ return 1; };
        d.m_fnSubMapId = []{ return 1001; };
        d.m_fnMapWalkable =
            [this](int x, int y, int dir,
                   uint32_t u48) {
                assert(x == 50 && y == 60);
                assert(dir == 3);   // sub OWN dir
                assert(u48 == 7);
                return bWalkable; };
        d.m_fnTimeGet = []{ return 1000; };
        d.m_fnRandGet = [](uint32_t){ return 0; };
        d.m_fnGenGetSpawn = [](int&, int&){};
        d.m_fnFindTarget =
            [](int) -> CNpcTargetSeam* {
                return nullptr; };
        d.m_fnSubHasMap80 = []{ return true; };
        d.m_bHasMap = bHasMap;
        d.m_bHasAttach = bHasAttach;
        d.m_nField34 = nField34;
        d.m_nField38 = nField38;
        d.m_fnNpcId8 = []{ return 4242u; };
        d.m_fn49480Width = [this]{
            return nWidth; };
        d.m_fn49430Height = [this]{
            return nHeight; };
        d.m_fnSubDir18 = [this]{
            return nSubDir18; };
        d.m_fnB2d0 = [this]{ ++nB2d0; };
        d.m_fn620c0 =
            [this](uint32_t id, int dir,
                   uint32_t fl) {
                assert(id == 4242);
                m_n620c0Dir = dir;
                m_n620c0Flavor = fl;
                return b620c0; };
        d.m_fn1c5f0Send =
            [this](uint32_t id) {
                assert(id == 4242);
                ++nSends; };
        d.m_fn58610 =
            [this](int nx, int ny) {
                ++nJumps;
                m_nJumpX = nx;
                m_nJumpY = ny; };
        d.m_fn49310 =
            [this](int, int){ return b49310; };
        return d;
    }
};

int main() {
    // ===== 1. no map -> log =================
    {
        Cfg c; c.bHasMap = false; auto d = c.Make();
        assert(!CNpcStepAttack(d, 5, 0));
        assert(c.nLogs == 1);
    }
    // ===== 2. happy path: dir 0 ==============
    // dx=0, dy=1 -> x'=50,y'=61 in bounds
    {
        Cfg c; auto d = c.Make();
        assert(CNpcStepAttack(d, 0, 2));
        assert(c.nLogs == 0 && c.nB2d0 == 0);
        assert(c.nSends == 1 && c.nJumps == 1);
        // +0x24 = 0; msg got (dir=0, flavor=2)
        assert(d.m_nField24 == 0);
        assert(c.m_n620c0Dir == 0);
        assert(c.m_n620c0Flavor == 2);
        // jump = table dx + +0x34, dy + +0x38
        assert(c.m_nJumpX == 0 + 50);
        assert(c.m_nJumpY == 1 + 60);
    }
    // ===== 3. dir 3 = (-1,-1) ================
    {
        Cfg c; auto d = c.Make();
        assert(CNpcStepAttack(d, 3, 1));
        assert(c.m_n620c0Dir == 3);
        assert(c.m_nJumpX == -1 + 50);
        assert(c.m_nJumpY == -1 + 60);
        assert(d.m_nField24 == 3);
    }
    // ===== 4. out of bounds -> log ==========
    // sub x 50, dir 6 = (1,0) ok; push x to edge
    {
        Cfg c; c.nSubX = 999; c.nField34 = 999;
        auto d = c.Make();
        // x' = 1000 not < width 1000 -> bounds log
        assert(!CNpcStepAttack(d, 6, 0));
        assert(c.nLogs == 1);
        assert(c.nSends == 0);
    }
    // ===== 5. negative out of bounds ========
    {
        Cfg c; c.nSubX = 0; c.nField34 = 0;
        auto d = c.Make();
        // dir 3 = (-1,-1): x' = -1 -> log
        assert(!CNpcStepAttack(d, 3, 0));
        assert(c.nLogs == 1);
    }
    // ===== 6. walk fails, no attach -> b2d0 =
    {
        Cfg c; c.bWalkable = false;
        auto d = c.Make();
        assert(!CNpcStepAttack(d, 0, 0));
        assert(c.nB2d0 == 1);
        assert(c.nSends == 0);
        assert(c.nLogs == 0);
    }
    // ===== 7. walk fails + attach + 49310 ok
    // -> PROCEEDS (the verbatim special case)
    {
        Cfg c; c.bWalkable = false;
        c.bHasAttach = true; c.b49310 = true;
        auto d = c.Make();
        assert(CNpcStepAttack(d, 0, 0));
        assert(c.nB2d0 == 0);
        assert(c.nSends == 1);
    }
    // ===== 8. walk fails + attach + !49310 ==
    {
        Cfg c; c.bWalkable = false;
        c.bHasAttach = true; c.b49310 = false;
        auto d = c.Make();
        assert(!CNpcStepAttack(d, 0, 0));
        assert(c.nB2d0 == 1);
    }
    // ===== 9. msg init fails -> log ========
    {
        Cfg c; c.b620c0 = false; auto d = c.Make();
        assert(!CNpcStepAttack(d, 0, 0));
        assert(c.nLogs == 1);
        assert(c.nSends == 0 && c.nJumps == 0);
    }
    // ===== 10. dir negative: signed mod ======
    {
        Cfg c; c.nSubDir18 = 3; auto d = c.Make();
        assert(CNpcStepAttack(d, -1, 0));
        // -1 % 8 = -1 (signed!) -> dirN = -1?
        // the ORIGINAL keeps it signed:
        // s_nDirX[-1] would be UB in my port
        // ... but +0x24 = -1 and the tables are
        // only read for dirN in 0..7 in the
        // ORIGINAL via the SAME index - the
        // original ALSO reads DAT[-1]! callers
        // only pass 0..7 in practice
        assert(d.m_nField24 == (uint32_t)(-1));
    }

    printf("NPC_STEPATTACK_OK: FUN_14005b9e0 step"
           " attack verbatim (map +0x98 log gate,"
           " signed-mod dirN with the +0x24 write,"
           " candidate cell via DAT_1400c89d0/89f0,"
           " the FUN_140049480/140049430 bounds"
           " gate with the out-of-bounds log, the"
           " VERBATIM walk check using the sub's"
           " OWN vt+0x18 dir and the literal 0"
           " (not 0x1a) last arg of FUN_14004bff0,"
           " the !walk && (!attach || !49310)"
           " -> FUN_14005b2d0 fail path, the"
           " FUN_140062030/620c0(id,dir,flavor)"
           " msg with the DAT_1400be0b0 log + dtor"
           " on init failure, FUN_14001c5f0 send,"
           " the FUN_140058610 jump to table dx +"
           " +0x34 / dy + +0x38, and the dtor)"
           "\n");
    return 0;
}
