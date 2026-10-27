#include "../npcserver/NpcStateUtil.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace npc;

struct Cfg {
    bool bHasMap = true;
    bool bHasPathfinder = true;
    int nSubX = 50, nSubY = 60;
    int nW = 1000, nH = 1000;
    uint32_t nCount = 3;
    uint64_t qA0 = 0xAABBCCDD11223344ull;
    uint8_t steps[76] = {5, 6, 7};
    int nLogs = 0, nPathCalls = 0;
    int m_nEndX = -1, m_nEndY = -1;
    int m_nStartX = -1, m_nStartY = -1;
    uint32_t m_nFlag = 999;
    uint32_t m_nField2CIn = 7;
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
        d.m_fnMapWalkable = [](int, int, int, uint32_t){
            return true; };
        d.m_fnTimeGet = []{ return 1000; };
        d.m_fnRandGet = [](uint32_t){ return 0; };
        d.m_fnGenGetSpawn = [](int&, int&){};
        d.m_fnFindTarget = [](int) -> CNpcTargetSeam*{
            return nullptr; };
        d.m_fnSubHasMap80 = []{ return true; };
        d.m_bHasMap = bHasMap;
        d.m_dwField2C = m_nField2CIn;
        d.m_fnNpcId8 = []{ return 4242u; };
        d.m_fn49480Width = [this]{ return nW; };
        d.m_fn49430Height = [this]{ return nH; };
        d.m_bHasPathfinder = bHasPathfinder;
        d.m_fnFindPath =
            [this](int sx, int sy, int ex, int ey,
                uint32_t fl, uint64_t& q,
                uint8_t* out) {
                ++nPathCalls;
                m_nStartX = sx; m_nStartY = sy;
                m_nEndX = ex; m_nEndY = ey;
                m_nFlag = fl;
                q = qA0;
                std::memcpy(out, steps, 76);
                return nCount; };
        return d;
    }
};

int main() {
    // ===== 1. no map -> 0x533 log =========
    {
        Cfg c; c.bHasMap = false; auto d = c.Make();
        assert(!CNpcMoveTo(d, 10, 20, 9));
        assert(c.nLogs == 1);
        assert(c.nPathCalls == 0);
    }
    // ===== 2. already there -> false, no log
    {
        Cfg c; auto d = c.Make();
        assert(!CNpcMoveTo(d, 50, 60, 9));
        assert(c.nLogs == 0);
        assert(c.nPathCalls == 0);
        assert(d.m_dwField2C == 0);  // reset 1st
    }
    // ===== 3. happy path =================
    {
        Cfg c; auto d = c.Make();
        assert(CNpcMoveTo(d, 80, 90, 0x1a));
        assert(c.nLogs == 0);
        assert(c.nPathCalls == 1);
        assert(c.m_nStartX == 50 && c.m_nStartY == 60);
        assert(c.m_nEndX == 80 && c.m_nEndY == 90);
        assert(c.m_nFlag == 0x1a);
        assert(d.m_qField90 == 0xAABBCCDD11223344ull);
        assert(d.m_dirQueue[0] == 5);
        assert(d.m_dirQueue[1] == 6);
        assert(d.m_dirQueue[2] == 7);
        assert(d.m_dwField2C == 3);
    }
    // ===== 4. empty path -> false ========
    {
        Cfg c; c.nCount = 0; auto d = c.Make();
        assert(!CNpcMoveTo(d, 80, 90, 1));
        assert(c.nPathCalls == 1);
        assert(d.m_dwField2C == 0);
    }
    // ===== 5. null pathfinder: log + CALL
    // ANYWAY (the verbatim quirk) ============
    {
        Cfg c; c.bHasPathfinder = false;
        auto d = c.Make();
        assert(CNpcMoveTo(d, 80, 90, 1));
        assert(c.nLogs == 1);      // 0x2c code
        assert(c.nPathCalls == 1); // called!
        assert(d.m_dwField2C == 3);
    }
    // ===== 6. full 76-step path ===========
    {
        Cfg c; c.nCount = 76;
        for (int i = 0; i < 76; i++)
            c.steps[i] = (uint8_t)(i & 7);
        auto d = c.Make();
        assert(CNpcMoveTo(d, 80, 90, 1));
        assert(d.m_dwField2C == 76);
        assert(d.m_dirQueue[75] == 3);
    }

    printf("NPC_MOVETO_OK: FUN_1400580e0 the move-to"
           " path verbatim (map +0x98 gate with the"
           " 0x533 code + DAT_1400be0b0 log, +0x2c"
           " zeroed first, the same-cell early"
           " false, the start cell from sub"
           " vt+0x38/0x40, the VERBATIM null-"
           " pathfinder quirk: the 0x2c code + log"
           " with NO else so the vt+0x58 call RUNS"
           " ANYWAY, the pf->vt+0x58(pf, out, 0x58,"
           " &start) request with the startX/"
           " startY/endX/endY/flag block, the +0x90"
           " 8-byte header write, the memcpy of"
           " count dir bytes into the +0x40 path"
           " area, +0x2c = count, and the"
           " 0 < count return)\n");
    return 0;
}
