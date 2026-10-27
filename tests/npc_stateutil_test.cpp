#include "../npcserver/NpcStateUtil.h"
#include <cassert>
#include <cstdio>
#include <vector>
using namespace npc;

struct Cfg {
    uint32_t uFlags = 0;
    uint32_t uW1 = 0, uW2 = 0;
    bool bHasMap = true;
    int nSteps = 3;
    int nCurX = 10, nCurY = 20;
    uint32_t u48 = 7;
    bool bWalkable = true;
    std::vector<std::pair<int,int>> vSight, vMoves;
    int nLogs = 0;
    CNpcStateData Make() {
        CNpcStateData d;
        d.m_fnRowGetFlag = [this]{ return uFlags; };
        d.m_fnSubGetWord20 =
            [this](int i){ return i ? uW2 : uW1; };
        d.m_fnLogError = [this]{ ++nLogs; };
        d.m_bHasMap = bHasMap;
        d.m_fnSubVt8 = [this]{ return nSteps; };
        d.m_fnSubVt48NoArgs = [this]{ return u48; };
        d.m_fnSubGetX38 = [this]{ return nCurX; };
        d.m_fnSubGetY40 = [this]{ return nCurY; };
        d.m_fnInSight =
            [this](int a, int b){
                vSight.push_back({a, b});
                for (auto& p : vVisible)
                    if (p.first == a && p.second == b)
                        return true;
                return false; };
        d.m_fnMoveTo =
            [this](int x, int y, int id){
                assert(id == 4242);
                vMoves.push_back({x, y}); };
        d.m_fnMapWalkable =
            [this](int x, int y, int dir, uint32_t u){
                assert(x == 10 && y == 20);
                assert(u == 7);
                m_lastDir = dir;
                return bWalkable; };
        return d;
    }
    std::vector<std::pair<int,int>> vVisible;
    int m_lastDir = -1;
};

int main() {
    // ===== FUN_140057d30 ==========================
    {
        Cfg c; auto d = c.Make();
        c.uFlags = 0;           // bit 15 clear
        assert(CNpcIsTransformLocked(d) == 1);
        c.uFlags = 1u << 15;     // bit 15 set
        assert(CNpcIsTransformLocked(d) == 0);
    }
    // ===== FUN_14005ad00: the block gates ========
    {
        Cfg c; auto d = c.Make();
        assert(CNpcCanAct(d));          // all clear
        c.uW1 = 1u << 5;
        assert(!CNpcCanAct(d));         // w1 bit5
        c.uW1 = 0; c.uW2 = 1u << 3;
        assert(!CNpcCanAct(d));         // w2 bit3
        c.uW2 = 0; c.uFlags = 1u << 6;  // bit6, no bit5
        assert(!CNpcCanAct(d));
        c.uFlags = 1u << 6 | 1u << 5;
        assert(CNpcCanAct(d));          // bit6+bit5
        c.uFlags = 0;                   // bit6 clear
        assert(CNpcCanAct(d));          // bit5 free
    }
    // ===== FUN_140059f40: the interpolation ======
    // cur (10,20) -> target (40,50), steps 3:
    // i=1: (20,30); i=2: (30,40); i=3: (40,50)
    {
        Cfg c; auto d = c.Make();
        c.vVisible = {{20, 30}};
        assert(CNpcTeleportApproach(d, 40, 50, 4242));
        assert(c.vSight.size() == 1);
        assert(c.vSight[0] == std::make_pair(20, 30));
        assert(c.vMoves.size() == 1);
        assert(c.vMoves[0] == std::make_pair(20, 30));
    }
    // ===== mid step visible ==================================
    {
        Cfg c; auto d = c.Make();
        c.vVisible = {{30, 40}};
        assert(CNpcTeleportApproach(d, 40, 50, 4242));
        assert(c.vSight.size() == 2);   // 1st failed
        assert(c.vMoves[0] == std::make_pair(30, 40));
    }
    // ===== only the final target visible ====================
    // i=3 lands exactly on (40,50), so the LOOP finds
    // it - the trailing fallback is not reached
    {
        Cfg c; auto d = c.Make();
        c.vVisible = {{40, 50}};
        assert(CNpcTeleportApproach(d, 40, 50, 4242));
        assert(c.vSight.size() == 3);   // steps only
        assert(c.vMoves[0] == std::make_pair(40, 50));
    }
    // ===== nothing visible -> false =========================
    {
        Cfg c; auto d = c.Make();
        assert(!CNpcTeleportApproach(d, 40, 50, 4242));
        assert(c.vMoves.empty());
    }
    // ===== steps < 1 -> false ===============================
    {
        Cfg c; auto d = c.Make();
        c.nSteps = 0;
        assert(!CNpcTeleportApproach(d, 40, 50, 4242));
        assert(c.vSight.empty());
    }
    // ===== no map -> the literal error log ==================
    {
        Cfg c; c.bHasMap = false; auto d = c.Make();
        assert(!CNpcTeleportApproach(d, 40, 50, 4242));
        assert(c.nLogs == 1);
    }
    // ===== FUN_140058500: the happy path ====================
    {
        Cfg c; auto d = c.Make();
        assert(CNpcWanderStep(d, 3));
        assert(c.m_lastDir == 3);
        assert(d.m_nField40 == 3);   // +0x40 = dir
        assert(d.m_dwField2C == 1);   // +0x2c = 1
    }
    // ===== dir >= 8: the error log ==========================
    {
        Cfg c; auto d = c.Make();
        assert(!CNpcWanderStep(d, 8));
        assert(c.nLogs == 1);
        assert(c.m_lastDir == -1);
    }
    // ===== no map: the error log ===========================
    {
        Cfg c; c.bHasMap = false; auto d = c.Make();
        assert(!CNpcWanderStep(d, 1));
        assert(c.nLogs == 1);
    }
    // ===== not walkable -> false ===========================
    {
        Cfg c; auto d = c.Make();
        c.bWalkable = false;
        assert(!CNpcWanderStep(d, 2));
        assert(d.m_nField40 == 0);
        assert(d.m_dwField2C == 0);
    }

    printf("NPC_STATEUTIL_OK: FUN_140057d30 (~row(0x15)"
           " >> 0xf & 1) + FUN_14005ad00 can-act gate"
           " (vt+0x20 w1 bit5 / w2 bit3 blocks, row"
           " 0x15 bit6 requires bit5) + FUN_140059f40"
           " teleport-approach (sub vt+8 step count,"
           " i/steps interpolation from current pos"
           " checking FUN_14004cc70 x-first, first"
           " visible step -> FUN_1400597f0, final"
           " fallback, steps<1/no-map false with"
           " DAT_1400be0b0) + FUN_140058500 wander step"
           " (dir<8 && map, sub vt+0x48 no-arg,"
           " FUN_14004bff0(map,x,y,dir,u48,0x1a) walk"
           " check, +0x40=dir +0x2c=1)\n");
    return 0;
}
