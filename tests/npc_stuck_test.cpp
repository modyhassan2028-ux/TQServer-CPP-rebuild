#include "../Exe/NpcServer/NpcStateUtil.h"
#include <cassert>
#include <cstdio>
using namespace npc;

struct Cfg {
    // 59770 gate
    int nField28 = 0;
    uint32_t nRow15 = 0;
    bool bHasAttach = false;
    bool b69750 = false;
    bool bAd00 = true, bVt50 = true;
    bool bHasField18 = true;
    int nField34 = 100, nField38 = 200;
    int nStuckX = 0, nStuckY = 0, nStuckCount = 0;
    uint32_t nDir24 = 5;
    int nRand = 0;
    bool b4cc70 = true;
    int n4cc70Calls = 0, n597f0Calls = 0;
    int m_nNX = -1, m_nNY = -1;
    uint32_t m_nDirArg = 999;
    int nRowGetIntCalls = 0;
    CNpcStateData Make() {
        CNpcStateData d;
        d.m_fnRowGetFlag = []{ return 0u; };
        d.m_fnRowGetInt =
            [this](uint32_t k) {
                assert(k == 0x15);
                ++nRowGetIntCalls;
                return (int)nRow15; };
        d.m_fnLogError = []{};
        d.m_fnInSight = [](int, int){ return true; };
        d.m_fnSubId18 = []{ return 4242; };
        d.m_fnSubGetX38 = [this]{ return nField34; };
        d.m_fnSubGetY40 = [this]{ return nField38; };
        d.m_fnSubVt48NoArgs = []{ return 7; };
        d.m_fnSubVt8 = []{ return 3; };
        d.m_fnSubDist = [](int, int){ return 1; };
        d.m_fnSubMapId = []{ return 1001; };
        d.m_fnMapWalkable = [](int, int, int, uint32_t){
            return true; };
        d.m_fnTimeGet = []{ return 1000; };
        d.m_fnRandGet = [this](uint32_t m){
            return (uint32_t)(nRand < (int)m
                ? nRand : 0); };
        d.m_fnGenGetSpawn = [](int&, int&){};
        d.m_fnFindTarget = [](int) -> CNpcTargetSeam*{
            return nullptr; };
        d.m_fnSubHasMap80 = []{ return true; };
        d.m_bHasMap = true;
        d.m_nField28 = nField28;
        d.m_bHasField18 = bHasField18;
        d.m_nField34 = nField34;
        d.m_nField38 = nField38;
        d.m_nStuckX = nStuckX;
        d.m_nStuckY = nStuckY;
        d.m_nStuckCount = nStuckCount;
        d.m_nField24 = nDir24;
        d.m_bHasAttach = bHasAttach;
        d.m_fn69750Alive = [this]{ return b69750; };
        d.m_fnAd00 = [this]{ return bAd00; };
        d.m_fnSubVt50 = [this]{ return bVt50; };
        d.m_fn4cc70 =
            [this](int x, int y) {
                ++n4cc70Calls;
                m_nNX = x; m_nNY = y;
                return b4cc70; };
        d.m_fn597f0 =
            [this](int x, int y, uint32_t dir) {
                ++n597f0Calls;
                m_nNX = x; m_nNY = y;
                m_nDirArg = dir;
                return 7u; };
        return d;
    }
};

int main() {
    // ===== 59770: the gates ==================
    {
        Cfg c; c.nField28 = 2; auto d = c.Make();
        assert(!CNpcFreeGate(d));
        assert(c.nRowGetIntCalls == 0);
    }
    {
        Cfg c; auto d = c.Make();
        assert(CNpcFreeGate(d));   // all clear
    }
    {
        Cfg c; c.nRow15 = 0x8; auto d = c.Make();
        assert(!CNpcFreeGate(d));  // bit3
    }
    {
        Cfg c; c.nRow15 = 0x10; auto d = c.Make();
        assert(!CNpcFreeGate(d));  // bit4
    }
    {
        Cfg c; c.nRow15 = 0x800; auto d = c.Make();
        assert(!CNpcFreeGate(d));  // bit11
    }
    // ===== b2d0: gate chain ==================
    // 59770 false -> 0
    {
        Cfg c; c.nField28 = 2; auto d = c.Make();
        assert(CNpcStuckHandler(d) == 0);
    }
    // attach alive -> 1, no further calls
    {
        Cfg c; c.bHasAttach = true; c.b69750 = true;
        auto d = c.Make();
        assert(CNpcStuckHandler(d) == 1);
        assert(c.n597f0Calls == 0);
    }
    // attach dead + ad00 false -> 0
    {
        Cfg c; c.bHasAttach = true; c.b69750 = false;
        c.bAd00 = false;
        auto d = c.Make();
        assert(CNpcStuckHandler(d) == 0);
    }
    // vt50 false -> 0
    {
        Cfg c; c.bVt50 = false; auto d = c.Make();
        assert(CNpcStuckHandler(d) == 0);
    }
    // +0x18 == 0 -> count reset, return vt50 (1)
    {
        Cfg c; c.bHasField18 = false;
        c.nStuckCount = 5;
        auto d = c.Make();
        assert(CNpcStuckHandler(d) == 1);
        assert(d.m_nStuckCount == 0);
    }
    // x != stuckX -> stuck update + the y leak
    {
        Cfg c; c.nStuckX = 50;   // differs
        c.nStuckY = 60;
        c.nStuckCount = 3;
        auto d = c.Make();
        uint32_t r = CNpcStuckHandler(d);
        // VERBATIM: low byte of y (200) = 200
        assert(r == (uint32_t)(200 & 0xff));
        assert(d.m_nStuckX == 100);
        assert(d.m_nStuckY == 200);
        assert(d.m_nStuckCount == 0);  // reset
        assert(c.n597f0Calls == 0);
    }
    // x == stuckX, count small -> count++, ret 1
    {
        Cfg c; c.nStuckX = 100; c.nStuckCount = 5;
        auto d = c.Make();
        assert(CNpcStuckHandler(d) == 1);
        assert(d.m_nStuckCount == 6);
        assert(c.n4cc70Calls == 0);
    }
    // x == stuckX, count 11 -> random jump
    // rand=0: nx = 0-4+100 = 96, ny = 96+... y:
    // ny = 0-4+200 = 196
    {
        Cfg c; c.nStuckX = 100; c.nStuckCount = 11;
        auto d = c.Make();
        assert(CNpcStuckHandler(d) == 1);
        assert(c.n4cc70Calls == 1);
        assert(c.n597f0Calls == 1);
        assert(c.m_nNX == 96 && c.m_nNY == 196);
        assert(c.m_nDirArg == 5);   // +0x24 dir
        // count: 11++ -> 12, then 12-5 = 7
        assert(d.m_nStuckCount == 7);
    }
    // 4cc70 fails -> count KEPT at 12, no walk
    {
        Cfg c; c.nStuckX = 100; c.nStuckCount = 11;
        c.b4cc70 = false;
        auto d = c.Make();
        assert(CNpcStuckHandler(d) == 1);
        assert(c.n597f0Calls == 0);
        assert(d.m_nStuckCount == 12);  // ++ kept
    }
    // rand=7: nx = 7-4+100 = 103
    {
        Cfg c; c.nStuckX = 100; c.nStuckCount = 11;
        c.nRand = 7;
        auto d = c.Make();
        assert(CNpcStuckHandler(d) == 1);
        assert(c.m_nNX == 103 && c.m_nNY == 203);
    }

    printf("NPC_STUCK_OK: FUN_140059770 free gate"
           " verbatim (+0x28 != 2 state gate, the"
           " row(0x15) GetInt with bits 3/4/0xb all"
           " clear -> true, else false) +"
           " FUN_14005b2d0 stuck handler verbatim"
           " (the 59770 gate, the attach-alive"
           " FUN_140069750 early true, the"
           " FUN_14005ad00 + sub vt+0x50 chain,"
           " +0x18 gate, the +0x34 x vs +0x11c"
           " stuckX compare with the +0x124 counter"
           " ++ and the >10 random unstuck jump"
           " (RandGet(8)-4 offsets, FUN_14004cc70"
           " check, count = max(count-5,0),"
           " FUN_1400597f0(nx,ny,+0x24 dir)) with"
           " the LITERAL always-true return on the"
           " stuck-x path, the stuckX/Y remember"
           " update (+0x120 via the ORIGINAL"
           " pointer-arith quirk), the +0x124"
           " reset, and the VERBATIM y low-byte"
           " leak on the update path)\n");
    return 0;
}
