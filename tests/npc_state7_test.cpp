#include "../Exe/NpcServer/NpcState.h"
#include <cassert>
#include <cstdio>
using namespace npc;

struct Cfg {
    uint32_t uFlags = 0;       // row 0x15
    CNpcTargetSeam* pTarget = nullptr;
    CNpcTargetSeam m_tele;     // for re-find paths
    bool bCB60 = false, bGenInAreaMe = true,
         bGenInAreaTgt = true, b49310 = true,
         bBC80 = false, bAD00 = true, bSub60 = true,
         bC960Ret = true, bHasMap = true;
    int nSubDist = 10, nSubDist48 = 20;
    int nSubMapId = 1001;
    int n5a0d0 = 0, n59f40 = 0, n59c90 = 0, nMove = 0,
        nLogs = 0;
    int nC960Flag = -1;
    int nRes8 = 55, nResc = 66;
    CNpcStateData Make() {
        CNpcStateData d;
        d.m_fnRowGetFlag = [this]{ return uFlags; };
        d.m_fnRowGetInt = [](uint32_t){ return 0; };
        d.m_fnFindTarget = [this](int id){
            if (id != 777) return (CNpcTargetSeam*)
                                  nullptr;
            return pTarget ? pTarget : &m_tele; };
        d.m_fnLogError = [this]{ ++nLogs; };
        d.m_fnInSight = [](int, int){ return true; };
        d.m_fnSubId18 = []{ return 4242; };
        d.m_fnSubDist = [this](int, int){
            return nSubDist; };
        d.m_fnSubDist48 = [this](int){
            return nSubDist48; };
        d.m_fnSubMapId = [this]{ return nSubMapId; };
        d.m_fnSubGetPos = [](int& x, int& y){
            x = 11; y = 22; };
        d.m_fnMoveTo = [this](int, int, int){
            ++nMove; };
        d.m_fnB030 = []{ return true; };
        d.m_fnWanderStart = [](uint32_t){};
        d.m_fnC960 = [this](uint32_t f){
            nC960Flag = (int)f; return bC960Ret; };
        d.m_fnBC80 = [this]{ return bBC80; };
        d.m_fnAD00 = [this]{ return bAD00; };
        d.m_fn2700 = []{ return true; };
        d.m_fnGetRole = []{ return (void*)0; };
        d.m_fnAd20 = [](void*){ return true; };
        d.m_fnAttack = [](int){};
        d.m_fn750 = []{ return true; };
        d.m_fnCB60 = [this]{ return bCB60; };
        d.m_fnGenGetSpawn =
            [this](int& a, int& b){ a = nRes8;
                                    b = nResc; };
        d.m_fnGenInArea =
            [this](int map, int x, int y) {
                // me: (1001, 11, 22); tgt: its own
                if (map == 1001 && x == 11 && y == 22)
                    return bGenInAreaMe;
                return bGenInAreaTgt; };
        d.m_fn49310 = [this](int, int){
            return b49310; };
        d.m_fn59f40 = [this](int, int, int){
            ++n59f40; };
        d.m_fn5a0d0 = [this](int a, int b, int id){
            assert(a == 55 && b == 66 && id == 4242);
            ++n5a0d0; };
        d.m_fn59c90 = [this]{ ++n59c90; return true; };
        d.m_fnSub60 = [this]{ return bSub60; };
        d.m_bHasMap = bHasMap;
        return d;
    }
};

int main() {
    CNpcTargetSeam tgt;

    // ===== 1. valid target, same map, in range, ====
    // ===== bit3 set -> state 8 via FUN_140059c90 ====
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        tgt.m_nMapId = 1001; tgt.m_nField48 = 50;
        c.uFlags = 1u << 3;
        assert(CNpcState7(d));
        assert(c.n59c90 == 1);
        assert(d.m_nState == 8 && d.m_dwField2C == 0);
    }
    // ===== 2. the c960 early-out: bit3 clear, AD00 ==
    // ===== false, sub60 true, 3c==0, 2c>0 ===========
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        tgt.m_nMapId = 1001; tgt.m_nField48 = 50;
        c.uFlags = 0; c.bAD00 = false; c.bSub60 = true;
        d.m_nField3C = 0; d.m_dwField2C = 3;
        assert(CNpcState7(d));
        assert(c.nC960Flag == 1);        // c960(_,1)
        assert(d.m_nState == 0);         // early-out
        assert(c.n59c90 == 0);
    }
    // ===== 3. gate fails (3c != 0) -> state 8 ======
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        tgt.m_nMapId = 1001; tgt.m_nField48 = 50;
        c.uFlags = 0; c.bAD00 = false; c.bSub60 = true;
        d.m_nField3C = 1; d.m_dwField2C = 3;
        assert(CNpcState7(d));
        assert(c.nC960Flag == -1);       // not called
        assert(d.m_nState == 8);
    }
    // ===== 4. different map -> LAB_668 -> state 1 ==
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        tgt.m_nMapId = 999;
        assert(CNpcState7(d));
        assert(d.m_nState == 1 && d.m_dwField2C == 0);
    }
    // ===== 5. too far (d2 < d1) -> LAB_668 =========
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        tgt.m_nMapId = 1001;
        c.nSubDist = 30; c.nSubDist48 = 5;
        assert(CNpcState7(d));
        assert(d.m_nState == 1);
    }
    // ===== 6. CB60 true -> plain return ============
    {
        Cfg c; auto d = c.Make();
        c.bCB60 = true;
        assert(CNpcState7(d));
        assert(d.m_nState == 0);       // untouched
    }
    // ===== 7. sight bits + me in gen area -> ======
    // ===== LAB_969: drop target, 5a0d0, state 1 ====
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        tgt.m_bValid50 = false;   // force LAB_668
        c.uFlags = 1u << 3; c.bGenInAreaMe = true;
        assert(CNpcState7(d));
        assert(c.n5a0d0 == 1);
        assert(d.m_nTargetId == 0);
        assert(d.m_nState == 1 && d.m_dwField2C == 0);
    }
    // ===== 8. sight bits + me out, target in -> ====
    // ===== LAB_969 with target-area call ===========
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        tgt.m_bValid50 = false;   // force LAB_668
        c.uFlags = 1u << 4;
        c.bGenInAreaMe = false; c.bGenInAreaTgt = true;
        assert(CNpcState7(d));
        assert(c.n5a0d0 == 1 && d.m_nState == 1);
    }
    // ===== 9. sight bits, both out of area -> ======
    // ===== LAB_789, bit 0xb move path (d > 5) =====
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        tgt.m_bValid50 = false;   // force LAB_668
        c.uFlags = 1u << 0xb;
        c.bGenInAreaMe = false;
        c.bGenInAreaTgt = false;
        c.nSubDist = 10;   // > 5
        assert(CNpcState7(d));
        assert(c.nMove == 1);   // FUN_1400597f0
        assert(d.m_nState == 0);
    }
    // ===== 10. LAB_789: 2c set -> c960 flag by ====
    // ===== target id (0 -> 0, 777 -> 1) ============
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 0;   // no target id
        d.m_dwField2C = 4;
        assert(CNpcState7(d));
        assert(c.nC960Flag == 0);
        assert(d.m_nState == 0);   // early return
    }
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = nullptr;
        d.m_dwField2C = 4;
        assert(CNpcState7(d));
        assert(c.nC960Flag == 1);
    }
    // ===== 11. LAB_789: BC80 + bit 5 teleport path
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = nullptr;
        c.bBC80 = true; c.uFlags = 1u << 5;
        assert(CNpcState7(d));
        assert(c.n59f40 == 1);   // FUN_140059f40
        assert(d.m_nState == 0);
    }
    // ===== 12. BC80 + bit 5 but no target found: ===
    // ===== literal log DAT_1400be0b0 ===============
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 77;    // find -> null
        c.bBC80 = true; c.uFlags = 1u << 5;
        assert(CNpcState7(d));
        assert(c.nLogs == 1);
        assert(c.n59f40 == 0);
    }
    // ===== 13. BC80 with 2c set -> early return ====
    {
        Cfg c; auto d = c.Make();
        d.m_dwField2C = 7; c.bBC80 = true;
        c.uFlags = 0;          // no bit 5
        assert(CNpcState7(d));
        assert(d.m_nState == 0 && d.m_dwField2C == 7);
    }
    // ===== 14. plain fall-through: state 1 =========
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 0;
        assert(CNpcState7(d));
        assert(d.m_nState == 1 && d.m_dwField2C == 0);
    }

    printf("NPC_STATE7_OK: FUN_14005d550 state 7 verbatim"
           " (valid-target gates map/d2>=d1, the"
           " !bit3+!AD00+sub60+3c==0+2c>0+c960(_,1)"
           " early-out, FUN_140059c90 -> state 8, LAB_668"
           " FUN_14005cb60 gate, gen vt+0x28 spawn res,"
           " sight-bits 3/4/7 InArea dance gen vt+0x70"
           " (map,x,y,0x30) with LAB_969 drop-target +"
           " FUN_14005a0d0(res8,resc,id) -> state 1,"
           " LAB_789 bit 0xb long-range move d>5 +"
           " FUN_140049310 -> FUN_1400597f0, 2c c960"
           " (0/1 by +0x84), FUN_14005bc80 + bit5"
           " FUN_140059f40 teleport or literal log"
           " DAT_1400be0b0, fall-through state 1)"
           "\n");
    return 0;
}
