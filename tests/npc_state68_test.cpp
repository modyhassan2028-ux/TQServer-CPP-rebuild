#include "../npcserver/NpcState.h"
#include <cassert>
#include <cstdio>
using namespace npc;

struct Cfg {
    uint32_t uFlags = 0;       // row 0x15
    uint32_t uRow10 = 3;
    CNpcTargetSeam* pTarget = nullptr;
    bool bInSight = true;
    bool bB030 = true;
    bool b2700 = true, bAd20 = true, bBC80 = false,
         bAD00 = true, b750 = true;
    bool bHasMap = true;
    void* pAttach = nullptr;
    int nSubDist = 10, nSubDist48 = 20;
    int nSightCalls = 0, nMoveCalls = 0, nWandCalls = 0,
        nC960 = -1, nAttacks = 0, nLogs = 0;
    CNpcStateData Make() {
        CNpcStateData d;
        d.m_fnRowGetFlag = [this]{ return uFlags; };
        d.m_fnRowGetInt = [this](uint32_t k){
            assert(k == 0x10); return uRow10; };
        d.m_fnFindTarget = [this](int id){
            return id == 777 ? pTarget
                             : (CNpcTargetSeam*)
                                   nullptr; };
        d.m_fnLogError = [this]{ ++nLogs; };
        d.m_fnInSight = [this](int y, int x){
            ++nSightCalls; return bInSight; };
        d.m_fnSubId18 = []{ return 4242; };
        d.m_fnSubDist = [this](int, int){
            return nSubDist; };
        d.m_fnSubDist48 = [this](int){
            return nSubDist48; };
        d.m_fnSubMapId = []{ return 1001; };
        d.m_fnMoveTo = [this](int x, int y, int id){
            assert(id == 4242); ++nMoveCalls; };
        d.m_fnB030 = [this]{ return bB030; };
        d.m_fnWanderStart = [this](uint32_t v){
            assert(v == uRow10 * 2); ++nWandCalls; };
        d.m_fnC960 = [this](uint32_t f){ nC960=(int)f; return true; };
        d.m_fnBC80 = [this]{ return bBC80; };
        d.m_fnAD00 = [this]{ return bAD00; };
        d.m_fn2700 = [this]{ return b2700; };
        d.m_fnGetRole = []{ return (void*)0x1234; };
        d.m_fnAd20 = [this](void* p){
            assert(p == (void*)0x1234); return bAd20; };
        d.m_fnAttack = [this](int v){
            assert(v == -1); ++nAttacks; };
        d.m_fn750 = [this]{ return b750; };
        d.m_bHasMap = bHasMap;
        d.m_pAttach140 = pAttach;
        return d;
    }
};

int main() {
    CNpcTargetSeam tgt;   // x=0,y=0 default

    // ===== state 6: bit 15 clear -> error log =====
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777;
        c.uFlags = 0;             // bit 15 clear
        assert(CNpcState6(d));
        assert(c.nLogs == 1);      // DAT_1400be0b0
        assert(d.m_nState == 1 && d.m_dwField2C == 0);
        assert(c.nMoveCalls == 0);
    }
    // ===== state 6: bits 3/4 + visible target -> ====
    // ===== move + state 7 ===========================
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        c.uFlags = 1u << 15 | 1u << 3;
        assert(CNpcState6(d));
        assert(c.nSightCalls == 1);
        assert(c.nMoveCalls == 1);   // FUN_1400597f0
        assert(d.m_nState == 7);
    }
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        c.uFlags = 1u << 15 | 1u << 4;   // bit 4 too
        assert(CNpcState6(d));
        assert(c.nMoveCalls == 1 && d.m_nState == 7);
    }
    // ===== state 6: flags without bits 3/4 skip ====
    // ===== the sight path entirely ================
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        c.uFlags = 1u << 15;      // no bits 3/4
        c.bB030 = true;           // B030 true -> skip
        assert(CNpcState6(d));
        assert(c.nSightCalls == 0);
        assert(c.nWandCalls == 0);
    }
    // ===== state 6: LAB_291 - B030 false wander ===
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        c.uFlags = 1u << 15; c.bB030 = false;
        assert(CNpcState6(d));
        assert(c.nWandCalls == 1);   // row(0x10)*2 = 6
        // ORIGINAL: with +0x2c still 0 and a target
        // set, the fall-through sets state 7
        // (FUN_14005b760 would have raised +0x2c)
        assert(d.m_dwField2C == 0);
        assert(d.m_nState == 7);
    }
    // ===== state 6: LAB_291 - target id 0 -> state 1
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 0; c.uFlags = 1u << 15;
        c.bB030 = false;
        d.m_dwField2C = 1;
        assert(CNpcState6(d));
        assert(c.nWandCalls == 0);   // +0x2c != 0
        assert(d.m_nState == 1 && d.m_dwField2C == 0);
    }
    // ===== state 6: LAB_291 - 2c==0 && target!=0 ====
    // ===== -> state 7 ===============================
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.uFlags = 1u << 15;
        c.bB030 = false; c.pTarget = &tgt;
        assert(CNpcState6(d));
        assert(c.nWandCalls == 1);
        assert(d.m_nState == 7);
    }
    // ===== state 6: 2c!=0 -> FUN_14005c960(_,1) =====
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.uFlags = 1u << 15;
        c.bB030 = false; c.pTarget = &tgt;
        d.m_dwField2C = 5;
        assert(CNpcState6(d));
        assert(c.nC960 == 1);
        assert(d.m_nState == 0);    // unchanged
    }
    // ===== state 8: chase - same map, d2>=d1, =====
    // ===== attack + c960(2) when 2c set ============
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        tgt.m_nMapId = 1001; tgt.m_nField48 = 50;
        c.nSubDist = 10; c.nSubDist48 = 20; // d2>d1
        d.m_dwField2C = 1;
        assert(CNpcState8(d));
        assert(c.nAttacks == 1);
        assert(c.nC960 == 2);
        assert(d.m_nField3C == 1);   // gate restored
        assert(d.m_nState == 7);     // LAB_467
    }
    // ===== state 8: 3e flag set -> clear & stop =====
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        tgt.m_nMapId = 1001; c.nSubDist48 = 20;
        d.m_nField3E = 1;
        // ORIGINAL: the attack fires FIRST, then the
        // +0x3e check clears and short-returns
        assert(CNpcState8(d));
        assert(d.m_nField3E == 0);
        assert(c.nAttacks == 1);
        assert(c.nC960 == -1);       // 2c == 0
        assert(d.m_nState == 0);     // no transition
    }
    // ===== state 8: 2700 false -> plain return =====
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        tgt.m_nMapId = 1001; c.b2700 = false;
        c.nSubDist = 10; c.nSubDist48 = 20;
        assert(CNpcState8(d));
        assert(c.nAttacks == 0);
        assert(d.m_nState == 0);
    }
    // ===== state 8: different map -> lose path =====
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        tgt.m_nMapId = 999; c.bBC80 = false;
        assert(CNpcState8(d));
        assert(d.m_nState == 1 && d.m_dwField2C == 0);
    }
    // ===== state 8: d2 < d1 (too far) -> lose path ==
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        tgt.m_nMapId = 1001;
        c.nSubDist = 30; c.nSubDist48 = 5;  // d2<d1
        assert(CNpcState8(d));
        assert(c.nAttacks == 0);
        assert(d.m_nState == 1);
    }
    // ===== state 8: +0x140 with 750 true -> lose ====
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        tgt.m_nMapId = 999;   // mismatch -> LAB_475
        c.pAttach = (void*)1; c.b750 = true;
        d.m_dwField2C = 9;
        assert(CNpcState8(d));
        assert(d.m_nState == 1 && d.m_dwField2C == 0);
    }
    // ===== state 8: +0x140 with 750 false -> the ==
    // ===== aggro re-check (BC80) ====================
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        tgt.m_nMapId = 999;   // mismatch -> LAB_475
        c.pAttach = (void*)1; c.b750 = false;
        c.bBC80 = true;
        // target valid, d1 > d2, 2c set, AD00 true
        tgt.m_nMapId = 1001;
        c.nSubDist = 10; c.nSubDist48 = 20;
        d.m_dwField2C = 1;
        assert(CNpcState8(d));
        assert(d.m_nState == 7);    // keeps chasing
    }
    // ===== state 8: aggro re-check, d1 <= d2 -> ====
    // ===== straight return (state untouched) =======
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        tgt.m_nMapId = 999;   // mismatch -> LAB_475
        c.pAttach = (void*)1; c.b750 = false;
        c.bBC80 = true;
        c.nSubDist = 10; c.nSubDist48 = 10; // d1<=d2
        d.m_dwField2C = 1;
        assert(CNpcState8(d));
        assert(d.m_nState == 0 && d.m_dwField2C == 1);
    }
    // ===== state 8: BC80 false -> reset to state 1 ==
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 777; c.pTarget = &tgt;
        tgt.m_nMapId = 999;   // mismatch -> LAB_475
        c.pAttach = (void*)1; c.b750 = false;
        c.bBC80 = false;
        tgt.m_nMapId = 999;
        d.m_dwField2C = 3;
        assert(CNpcState8(d));
        assert(d.m_nState == 1 && d.m_dwField2C == 0);
    }

    printf("NPC_STATE68_OK: FUN_14005d140 state 6 verbatim"
           " (bit-15 gate + literal log DAT_1400be0b0,"
           " bits 3/4 sight path FUN_14004cc70(map,y,x) ->"
           " FUN_1400597f0(npc,x,y,id18) + state 7,"
           " LAB_14005d291 FUN_14005b030 gate -> wander"
           " FUN_14005b760(row(0x10)*2), target-id-0"
           " reset, 2c==0 -> state 7, else"
           " FUN_14005c960(_,1)) + FUN_14005d330 state 8"
           " verbatim (target vtable+0x50/map/d2>=d1"
           " chase gates, FUN_140002700(+0xa8), attack"
           " FUN_140058260(npc,-1) with +0x3c 0/1 gate,"
           " FUN_14005c960(_,2) when +0x2c, +0x3e clear"
           " short-out, LAB_467 state 7, LAB_475"
           " +0x140/FUN_140069750 gate, LAB_48f aggro"
           " re-check FUN_14005bc80 + keep-chase via"
           " FUN_14005ad00, lose-target reset +0x2c=0"
           " state 1)\n");
    return 0;
}
