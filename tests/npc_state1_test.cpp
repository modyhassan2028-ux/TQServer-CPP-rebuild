#include "../Exe/NpcServer/NpcState.h"
#include <cassert>
#include <cstdio>
#include <vector>
using namespace npc;

struct Cfg {
    uint32_t uFlags = 0;
    CNpcTargetSeam* pTarget = nullptr;
    CNpcTargetSeam m_tele;
    bool bDF70 = false, bAD00 = true, bBC80 = false,
         b2700 = true, b57d30 = true, b580e0 = true,
         b58500 = true, bCreatureInit = true,
         bGenArea68 = true;
    int nSubDist = 10, nSubDist48 = 20;
    uint32_t uW1 = 0, uW2 = 0;      // vt+0x20 words
    int nRandSeq = 0;
    std::vector<uint32_t> vRand;
    int nCreatureCtor = 0, nCreatureSend = 0,
        nCreatureDestroy = 0, nCreatureInit = 0,
        n59c90 = 0, nC960 = -1, n580e0 = 0,
        n58500 = 0, n59f40 = 0, nLogsE = 0,
        nLogsW = 0, nRowVt8 = 0;
    int nGenVt60 = 4, nGenVt50 = 100, nGenVt38 = 5,
        nGenVt58 = 200;
    int nSpawnLo = 7, nSpawnHi = 8;
    CNpcStateData Make() {
        CNpcStateData d;
        d.m_fnRowGetFlag = [this]{ return uFlags; };
        d.m_fnRowGetInt = [](uint32_t){ return 0; };
        d.m_fnFindTarget = [this](int id){
            if (id != 777)
                return (CNpcTargetSeam*)nullptr;
            return pTarget ? pTarget : &m_tele; };
        d.m_fnLogError = [this]{ ++nLogsE; };
        d.m_fnLogWarn = [this]{ ++nLogsW; };
        d.m_fnInSight = [](int, int){ return true; };
        d.m_fnSubId18 = []{ return 4242; };
        d.m_fnSubDist = [this](int, int){
            return nSubDist; };
        d.m_fnSubDist48 = [this](int){
            return nSubDist48; };
        d.m_fnSubMapId = []{ return 1001; };
        d.m_fnSubGetPos = [](int& x, int& y){
            x = 11; y = 22; };
        d.m_fnMoveTo = [](int, int, int){};
        d.m_fnB030 = []{ return true; };
        d.m_fnWanderStart = [](uint32_t){};
        d.m_fnC960 = [this](uint32_t f){
            nC960 = (int)f; return true; };
        d.m_fnBC80 = [this]{ return bBC80; };
        d.m_fnAD00 = [this]{ return bAD00; };
        d.m_fn2700 = [this]{ return b2700; };
        d.m_fnGetRole = []{ return (void*)0; };
        d.m_fnAd20 = [](void*){ return true; };
        d.m_fnAttack = [](int){};
        d.m_fn750 = []{ return true; };
        d.m_fnCB60 = []{ return false; };
        d.m_fnGenGetSpawn =
            [this](int& a, int& b){ a = nSpawnLo;
                                     b = nSpawnHi; };
        d.m_fnGenInArea = [](int, int, int){
            return true; };
        d.m_fn49310 = [](int, int){ return true; };
        d.m_fn59f40 =
            [this](int x, int y, int id){
                assert(x == nSpawnLo &&
                       y == nSpawnHi && id == 4242);
                ++n59f40; };
        d.m_fn5a0d0 = [](int, int, int){};
        d.m_fn59c90 = [this]{ ++n59c90; return true; };
        d.m_fnSub60 = []{ return true; };
        // ===== state-1 seams =====
        d.m_fnNpcVt8 = []{ return 13; };
        d.m_fnCreatureCtor = [this]{ ++nCreatureCtor; };
        d.m_fnCreatureInit =
            [this](uint32_t id, int y, int x){
                assert(id == 4242 && y == 22 &&
                       x == 11);
                ++nCreatureInit;
                return bCreatureInit; };
        d.m_fnCreatureSend = [this](int idx){
            assert(idx == 13); ++nCreatureSend; };
        d.m_fnCreatureDestroy =
            [this]{ ++nCreatureDestroy; };
        d.m_fnDF70 = [this]{ return bDF70; };
        d.m_fnGenArea68 = [this](int x, int y){
            assert(x == 11 && y == 22);
            return bGenArea68; };
        d.m_fnSubGetWord20 =
            [this](int i){ return i ? uW2 : uW1; };
        d.m_fnRowVt8 = [this]{ ++nRowVt8; };
        d.m_fnRandGet = [this](uint32_t m){
            uint32_t v = nRandSeq <
                (int)vRand.size()
                ? vRand[nRandSeq++] : 0;
            return v < m ? v : 0; };
        d.m_fn57d30 = [this]{ return b57d30; };
        d.m_fn580e0 =
            [this](int x, int y, int z){
                assert(z == 0); ++n580e0;
                m_last580e0 = {x, y}; return b580e0; };
        d.m_fn58500 = [this](uint32_t dir){
            assert(dir < 8); ++n58500;
            return b58500; };
        d.m_fnGenVt60 = [this]{ return nGenVt60; };
        d.m_fnGenVt50 = [this]{ return nGenVt50; };
        d.m_fnGenVt38 = [this]{ return nGenVt38; };
        d.m_fnGenVt58 = [this]{ return nGenVt58; };
        d.m_bHasMap = true;
        return d;
    }
    std::pair<int,int> m_last580e0 = {-1,-1};
};

int main() {
    CNpcTargetSeam tgt;

    // ===== 1. the summoner bit 8: creature cycle ===
    {
        Cfg c; auto d = c.Make();
        c.uFlags = 1u << 8;
        c.bAD00 = false;     // stop before movement
        assert(CNpcState1(d));
        assert(c.nCreatureCtor == 1);
        assert(c.nCreatureInit == 1);
        assert(c.nCreatureSend == 1);
        assert(c.nCreatureDestroy == 1);
    }
    // ===== 2. bit 8 with init failing: the error ===
    // ===== log, no send =============================
    {
        Cfg c; auto d = c.Make();
        c.uFlags = 1u << 8; c.bCreatureInit = false;
        c.bAD00 = false;
        assert(CNpcState1(d));
        assert(c.nLogsE == 1);
        assert(c.nCreatureSend == 0);
        assert(c.nCreatureDestroy == 1);
    }
    // ===== 3. DF70 true -> immediate return ========
    {
        Cfg c; auto d = c.Make();
        c.bDF70 = true; c.bAD00 = false;
        assert(CNpcState1(d));
        assert(d.m_nState == 0);
    }
    // ===== 4. no sight bits, 2c > 0 -> c960(_,0) ====
    {
        Cfg c; auto d = c.Make();
        d.m_dwField2C = 5; c.uFlags = 0;
        assert(CNpcState1(d));
        assert(c.nC960 == 0);
        assert(d.m_dwField2C == 5);   // untouched
    }
    // ===== 5. no sight bits, bit7 + out of gen =====
    // ===== area -> skips the 2700 check =============
    {
        Cfg c; auto d = c.Make();
        c.uFlags = 1u << 7; c.bGenArea68 = false;
        c.bAD00 = false;
        c.bBC80 = false;    // skip aggro
        c.vRand = {1};      // rand5 -> 1: no return
        assert(CNpcState1(d));
        // AD00 false stops before movement
        assert(d.m_nField44 == 0 &&
               d.m_nField3D == 0);   // LAB_eb1c ran
    }
    // ===== 6. LAB_eb1c + aggro: target found, ======
    // ===== in sight range -> state 8 ================
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        c.bBC80 = true; c.uFlags = 1u << 7;
        c.bGenArea68 = false;      // force LAB_eb1c
        c.bAD00 = false;           // AD00 gate later
        tgt.m_nMapId = 1001; tgt.m_nField48 = 50;
        c.nSubDist = 10; c.nSubDist48 = 20; //d1<=d2
        assert(CNpcState1(d));
        assert(c.n59c90 == 1);
        assert(d.m_nState == 8 && d.m_dwField2C == 0);
    }
    // ===== 7. aggro, target out of range, AD00, ====
    // ===== 2c set -> state 7 ========================
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        c.bBC80 = true; c.uFlags = 1u << 3;
        c.bGenArea68 = false; c.bAD00 = true;
        tgt.m_nField48 = 5;
        c.nSubDist = 30; c.nSubDist48 = 5; // d1 > d2
        d.m_dwField2C = 3;
        assert(CNpcState1(d));
        assert(d.m_nState == 7);
    }
    // ===== 8. same but 2c == 0 and rand > 0x4f -> ==
    // ===== state 6 =================================
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        c.bBC80 = true; c.uFlags = 1u << 3;
        c.bGenArea68 = false; c.bAD00 = true;
        tgt.m_nField48 = 5;
        c.nSubDist = 30; c.nSubDist48 = 5;
        c.vRand = {80};      // 0x4f < 80
        assert(CNpcState1(d));
        assert(d.m_nState == 6 && d.m_dwField2C == 0);
    }
    // ===== 9. same but rand <= 0x4f -> plain return
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        c.bBC80 = true; c.uFlags = 1u << 3;
        c.bGenArea68 = false; c.bAD00 = true;
        tgt.m_nField48 = 5;
        c.nSubDist = 30; c.nSubDist48 = 5;
        c.vRand = {79};      // 0x4f == 79, not <
        assert(CNpcState1(d));
        assert(d.m_nState == 0);
    }
    // ===== 10. aggro, no target: the literal ========
    // ===== WARNING log ==============================
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 55;   // find -> null
        c.bBC80 = true; c.uFlags = 1u << 7;
        c.bGenArea68 = false; c.bAD00 = false;
        assert(CNpcState1(d));
        assert(c.nLogsE == 1);
        assert(c.nLogsW == 1);  // "npc: [%d][%d]..."
        assert(c.nRowVt8 == 1);
    }
    // ===== 11. the vt+0x20 word gate: w1 bit5 or ===
    // ===== w2 bit3 blocks the aggro block ===========
    {
        Cfg c; auto d = c.Make();
        c.bBC80 = true; c.uFlags = 1u << 7;
        c.bGenArea68 = false; c.bAD00 = false;
        c.uW1 = 1u << 5;     // bit 5 set
        d.m_nTargetId = 777; c.pTarget = &tgt;
        assert(CNpcState1(d));
        assert(c.nLogsW == 0 && c.n59c90 == 0);
    }
    {
        Cfg c; auto d = c.Make();
        c.bBC80 = true; c.uFlags = 1u << 7;
        c.bGenArea68 = false; c.bAD00 = false;
        c.uW2 = 1u << 3;     // bit 3 set
        d.m_nTargetId = 777; c.pTarget = &tgt;
        assert(CNpcState1(d));
        assert(c.n59c90 == 0);
    }
    // ===== 12. movement: sight bits + 2c > 0 -> =====
    // ===== c960(_,0) =================================
    {
        Cfg c; auto d = c.Make();
        c.uFlags = 1u << 3;
        d.m_dwField2C = 2;
        assert(CNpcState1(d));
        assert(c.nC960 == 0);
    }
    // ===== 13. in gen area, no sight bits: rand5(0) ==
    // ===== + 58500 8-dir wander -> c960(0) ==========
    {
        Cfg c; auto d = c.Make();
        c.uFlags = 0; c.vRand = {0, 3};  // 5, then 8
        assert(CNpcState1(d));
        assert(c.n58500 == 1);   // dir 3
        assert(c.nC960 == 0);
    }
    // ===== 14. in gen area, rand5 != 0: nothing =====
    {
        Cfg c; auto d = c.Make();
        c.uFlags = 0; c.vRand = {2};
        assert(CNpcState1(d));
        assert(c.n58500 == 0);
    }
    // ===== 15. in gen area with sight bits: the =====
    // ===== gen-rect random move ======================
    {
        Cfg c; auto d = c.Make();
        c.uFlags = 1u << 3;
        c.vRand = {0, 1, 2};   // rand5=0, W=1, H=2
        c.nGenVt60 = 4; c.nGenVt50 = 100;
        c.nGenVt38 = 5; c.nGenVt58 = 200;
        assert(CNpcState1(d));
        assert(c.n580e0 == 1);
        assert(c.m_last580e0.first == 100 + 1);
        assert(c.m_last580e0.second == 200 + 2);
        assert(c.nC960 == 0);
    }
    // ===== 16. out of gen area, rand5 != 0, no =======
    // ===== bits 3/4/7 -> plain return ===============
    {
        Cfg c; auto d = c.Make();
        c.uFlags = 0; c.bGenArea68 = false;
        c.vRand = {3};
        assert(CNpcState1(d));
        assert(c.n580e0 == 0);
    }
    // ===== 17. out of gen area: 580e0 to spawn -> ====
    // ===== c960(0) ===================================
    {
        Cfg c; auto d = c.Make();
        c.uFlags = 1u << 3;      // skip the rand5
        c.bGenArea68 = false;
        assert(CNpcState1(d));
        assert(c.n580e0 == 1);
        assert(c.m_last580e0 ==
               std::make_pair(7, 8));   // spawn res
        assert(c.nC960 == 0);
    }
    // ===== 18. out of area, 580e0 fails, bit 5 -> ====
    // ===== teleport FUN_140059f40 ====================
    {
        Cfg c; auto d = c.Make();
        c.uFlags = 1u << 5;      // teleport bit
        c.bGenArea68 = false;
        c.b580e0 = false;
        assert(CNpcState1(d));
        assert(c.n580e0 == 1);
        assert(c.n59f40 == 1);   // to spawn res
        assert(c.nC960 == -1);    // no c960
    }
    // ===== 19. out of area, 580e0 fails, no bits: ====
    // ===== no teleport, plain return ================
    {
        Cfg c; auto d = c.Make();
        c.uFlags = 0;
        c.bGenArea68 = false; c.b580e0 = false;
        c.vRand = {0};           // rand5 == 0
        assert(CNpcState1(d));
        assert(c.n580e0 == 1);
        assert(c.n59f40 == 0);
    }

    printf("NPC_STATE1_OK: FUN_14005e900 state 1 verbatim"
           " (bit-8 summoner cycle FUN_1400623e0/"
           "062460(id,y,x,0x59,0)/01c5f0 send/062430 with"
           " the DAT_1400be0b0 error log, FUN_14005df70"
           " early-out, no-sight 2c>0 -> c960(_,0), bit7"
           " gen vt+0x68 area gate + FUN_140002700,"
           " LAB_14005eb1c +0x44/+0x3d reset, vt+0x20"
           " word gate bits 5/3, aggro block with the"
           " literal WARNING 'npc: [%%d][%%d], target id:"
           " [%%d]', d1<=d2 -> FUN_140059c90 state 8,"
           " AD00 path 2c state 7 / 0x4f<RandGet(100)"
           " state 6, movement: sight c960(0) + 2700,"
           " in-area 8-dir FUN_140058500(RandGet(8)) or"
           " gen-rect RandGet(vt+0x60/vt+0x38)+vt+0x50/"
           "58 via FUN_1400580e0, out-of-area 1/5 gate"
           " -> spawn-res FUN_1400580e0 else bit5"
           " FUN_140059f40 teleport)\n");
    return 0;
}
