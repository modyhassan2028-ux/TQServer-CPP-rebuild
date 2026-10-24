#include "../Exe/NpcServer/NpcStateUtil.h"
#include <cassert>
#include <cstdio>
using namespace npc;

struct Cfg {
    bool bHasMap = true, b62530 = true;
    int nWidth = 1000, nHeight = 1000;
    int nSubX = 100, nSubY = 200;
    uint32_t nDir24 = 3;
    int nLogs = 0, nJumps = 0, nSends = 0,
        nMsgFills = 0;
    int m_nJumpX = -1, m_nJumpY = -1;
    short m_sX = -1, m_sY = -1, m_sDir = -1,
          m_sTx = -1, m_sTy = -1;
    uint32_t m_nIdArg = 0;
    uint32_t m_nField2CIn = 5;
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
        d.m_nField24 = 0;
        d.m_fnNpcId8 = []{ return 4242u; };
        d.m_fn49480Width = [this]{ return nWidth; };
        d.m_fn49430Height = [this]{ return nHeight; };
        d.m_fn58610 = [this](int x, int y) {
            ++nJumps; m_nJumpX = x; m_nJumpY = y; };
        d.m_fn62530 =
            [this](uint32_t id, short sx, short sy,
                   short sdir, short stx, short sty) {
                ++nMsgFills;
                m_nIdArg = id;
                m_sX = sx; m_sY = sy;
                m_sDir = sdir;
                m_sTx = stx; m_sTy = sty;
                return b62530; };
        d.m_fn1c5f0Send = [this](uint32_t id) {
            assert(id == 4242);
            ++nSends; };
        d.m_fnB2d0 = []{};
        d.m_fnSubDir18 = []{ return 1; };
        return d;
    }
};

int main() {
    // ===== 1. no map -> log, nothing ==========
    {
        Cfg c; c.bHasMap = false; auto d = c.Make();
        CNpcWalkMsg(d, 10, 20, 3);
        assert(c.nLogs == 1);
        assert(c.nJumps == 0);
    }
    // ===== 2. happy path =====================
    {
        Cfg c; auto d = c.Make();
        CNpcWalkMsg(d, 105, 206, 7);
        assert(c.nLogs == 0);
        assert(c.nJumps == 1);
        assert(c.m_nJumpX == 105 && c.m_nJumpY == 206);
        assert(d.m_dwField2C == 0);       // +0x2c
        assert(d.m_nField24 == 7);        // +0x24
        // 62530: (id, sub x, sub y, dir,
        // target x, target y) all SHORTS
        assert(c.m_nIdArg == 4242);
        assert(c.m_sX == 100 && c.m_sY == 200);
        assert(c.m_sDir == 7);
        assert(c.m_sTx == 105 && c.m_sTy == 206);
        assert(c.nSends == 1);
    }
    // ===== 3. bounds: x out -> log ============
    {
        Cfg c; c.nWidth = 100; auto d = c.Make();
        CNpcWalkMsg(d, 100, 50, 1);
        assert(c.nLogs == 1);
        assert(c.nJumps == 0 && c.nMsgFills == 0);
    }
    // ===== 4. bounds: negative y -> log =======
    {
        Cfg c; auto d = c.Make();
        CNpcWalkMsg(d, 50, -1, 1);
        assert(c.nLogs == 1);
    }
    // ===== 5. msg fill fails -> no send ======
    {
        Cfg c; c.b62530 = false; auto d = c.Make();
        CNpcWalkMsg(d, 10, 20, 2);
        assert(c.nMsgFills == 1);
        assert(c.nSends == 0);
        assert(c.nJumps == 1);   // move ran first
    }
    // ===== 6. the SHORT truncation ===========
    // sub pos 70000 -> (short)70000 = 4464
    {
        Cfg c; c.nSubX = 70000; c.nSubY = -70000;
        auto d = c.Make();
        CNpcWalkMsg(d, 10, 20, 1);
        assert(c.m_sX == (short)70000);   // 4464
        assert(c.m_sY == (short)(-70000));
    }

    printf("NPC_WALKMSG_OK: FUN_1400597f0 the walk"
           " msg verbatim (map +0x98 log gate, the"
           " FUN_140049480/140049430 bounds gate"
           " with the literal log, +0x2c = 0,"
           " FUN_140058610(npc, x, y) move, +0x24 ="
           " dir, the FUN_1400623e0 ctor, the"
           " SHORT-truncated sub vt+0x38/0x40"
           " getters, FUN_140062530(msg, id, xs,"
           " ys, (short)dir, 0x89, (short)x,"
           " (short)y, 0) fill with the 0x89 msg"
           " id, the FUN_14001c5f0 send only on"
           " fill success, and the FUN_140062430"
           " dtor)\n");
    return 0;
}
