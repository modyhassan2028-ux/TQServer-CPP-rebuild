#include "../npcserver/NpcDeath.h"
#include <cassert>
#include <cstdio>
using namespace npc;

struct Cfg {
    uint64_t uNow = 0;
    uint32_t uFlags = 0;          // type row 0x15
    uint32_t uRow4 = 44, uRow5 = 55;
    int nX = 111, nY = 222;
    bool bGenInArea = true;
    bool bMapPosValid = true;
    bool bHasMap = true;
    bool bCheck50 = true;
    bool bGate148 = false;
    bool bHas140 = true, b6750 = true;
    bool b6991 = false, b6974 = false;
    int nState1 = 0, nState6 = 0, nState7 = 0,
        nState8 = 0;
    bool bState1Ret = true;
    CNpcDeathData Make() {
        CNpcDeathData d;
        d.m_fnNow = [this]{ return uNow; };
        d.m_fnRowGetFlag = [this]{ return uFlags; };
        d.m_fnRowGetInt = [this](uint32_t k){
            return k == 4 ? uRow4 : uRow5; };
        d.m_fnGetPos = [this](int& x, int& y){
            x = nX; y = nY; };
        d.m_fnGenInArea = [this](int x, int y){
            assert(x == 111 && y == 222);
            return bGenInArea; };
        d.m_fnHasMap = [this]{ return bHasMap; };
        d.m_fnMapPosValid = [this](int x, int y){
            assert(x == 111 && y == 222);
            return bMapPosValid; };
        d.m_fnCheck50 = [this]{ return bCheck50; };
        d.m_bGate148 = bGate148;
        d.m_fnHasAttach140 = [this]{ return bHas140; };
        d.m_fn6750 = [this]{ return b6750; };
        d.m_fn6991 = [this]{ return b6991; };
        d.m_fn6974 = [this]{ return b6974; };
        d.m_fnState1 = [this]{ ++nState1;
            return bState1Ret; };
        d.m_fnState6 = [this]{ ++nState6; return true; };
        d.m_fnState7 = [this]{ ++nState7; return true; };
        d.m_fnState8 = [this]{ ++nState8; return true; };
        return d;
    }
};

int main() {
    // ===== 1. the 1Hz interval gate (+0xb0/+0xb4) ==
    {
        Cfg c; auto d = c.Make();
        d.m_nIntervalB0 = 5;
        d.m_nStampB4 = 1000;
        c.uNow = 1004 * 1000;          // 1004 < 1000+5
        assert(!CNpcRebornTick(d));
        c.uNow = 1005 * 1000;          // 1005 >= 1005
        assert(CNpcRebornTick(d));
        assert(d.m_nStampB4 == 1005);
        assert(d.m_dwField1C == 44 && d.m_dwField20 == 55);
        assert(d.m_dwField2C == 0 && d.m_nState == 0);
    }
    // ===== 2. flag bits 3/4/7 -> gen vtable+0x68 ====
    // ===== area check blocks the reborn ============
    {
        Cfg c; c.uFlags = 1u << 3;      // bit 3
        auto d = c.Make(); c.bGenInArea = false;
        d.m_fnGenInArea = [&](int, int){ return false; };
        assert(!CNpcRebornTick(d));
        assert(d.m_nState == 0 && d.m_dwField1C == 0);
        c.uFlags = 1u << 4;            // bit 4
        auto d2 = c.Make();
        d2.m_fnGenInArea = [&](int, int){ return false; };
        assert(!CNpcRebornTick(d2));
        c.uFlags = 1u << 7;            // bit 7
        auto d3 = c.Make();
        d3.m_fnGenInArea = [&](int, int){ return false; };
        assert(!CNpcRebornTick(d3));
    }
    // ===== 3. flags clear -> no gen check, map path ==
    {
        Cfg c; c.uFlags = 1u << 2;      // bit 2 only
        auto d = c.Make();
        assert(CNpcRebornTick(d));     // no area call
    }
    // ===== 4. map pos invalid -> return 0 ============
    {
        Cfg c; auto d = c.Make(); c.bMapPosValid = false;
        d.m_fnMapPosValid = [](int, int){ return false; };
        assert(!CNpcRebornTick(d));
        assert(d.m_nState == 0);       // unchanged
    }
    // ===== 5. no map -> return 0 =====================
    {
        Cfg c; auto d = c.Make(); c.bHasMap = false;
        d.m_fnHasMap = []{ return false; };
        assert(!CNpcRebornTick(d));
    }
    // ===== 6. FUN_140058860 the gate ================
    {
        Cfg c; auto d = c.Make();
        assert(CNpcContinueGate(d));    // 750&&!91&&!74
        c.b6750 = false; auto d2 = c.Make();
        assert(!CNpcContinueGate(d2));
        c.b6750 = true; c.b6991 = true; auto d3 = c.Make();
        assert(!CNpcContinueGate(d3));
        c.b6991 = false; c.b6974 = true; auto d4 = c.Make();
        assert(!CNpcContinueGate(d4));
        c.b6974 = false; c.bHas140 = false; auto d5 = c.Make();
        assert(!CNpcContinueGate(d5));
    }
    // ===== 7. dispatcher: tick handled -> no state ==
    // ===== machine ==================================
    {
        Cfg c; c.uFlags = 0; auto d = c.Make();
        d.m_nStampB4 = 0; d.m_nIntervalB0 = 0;
        d.m_nState = 6;                // would dispatch
        CNpcDieDispatch(d);
        assert(c.nState6 == 0);        // skipped!
        assert(d.m_nState == 0);       // reborn won
    }
    // ===== 8. dispatcher: state routing 1/6/7/8 =====
    {
        Cfg c; auto d = c.Make();
        d.m_nStampB4 = 9999; d.m_nIntervalB0 = 0;
        c.uNow = 10 * 1000;            // gate blocks tick
        d.m_fnNow = []{ return 10000; };
        d.m_nState = 1;
        CNpcDieDispatch(d);
        assert(c.nState1 == 1 && c.nState6 == 0);
        d.m_nState = 6;
        CNpcDieDispatch(d);
        assert(c.nState6 == 1);
        d.m_nState = 7;
        CNpcDieDispatch(d);
        assert(c.nState7 == 1);
        d.m_nState = 8;
        CNpcDieDispatch(d);
        assert(c.nState8 == 1);
    }
    // ===== 9. dispatcher: the +0x50 check and the ==
    // ===== +0x148 gate ==============================
    {
        Cfg c; auto d = c.Make();
        d.m_nStampB4 = 9999; d.m_nIntervalB0 = 0;
        d.m_fnNow = []{ return 10000; };
        d.m_nState = 6;
        d.m_fnCheck50 = []{ return false; };
        CNpcDieDispatch(d);
        assert(c.nState6 == 0);
        Cfg c2; auto d2 = c2.Make();
        d2.m_nStampB4 = 9999; d2.m_nIntervalB0 = 0;
        d2.m_fnNow = []{ return 10000; };
        d2.m_nState = 6;
        d2.m_bGate148 = true;          // +0x148 set
        CNpcDieDispatch(d2);
        assert(c2.nState6 == 0);
    }
    // ===== 10. handler returning false: the 10-pass
    // ===== loop re-dispatches (state may flip) ======
    {
        Cfg c; auto d = c.Make();
        d.m_nStampB4 = 9999; d.m_nIntervalB0 = 0;
        d.m_fnNow = []{ return 10000; };
        d.m_nState = 6;
        d.m_fnState6 = [&]() -> bool {
            // first pass: refuse; second pass: accept
            ++c.nState6;
            if (c.nState6 == 1) { d.m_nState = 8; }
            return c.nState6 > 1;
        };
        d.m_fnState8 = [&]{ ++c.nState8; return true; };
        CNpcDieDispatch(d);
        assert(c.nState6 == 1 && c.nState8 == 1);
    }

    printf("NPC_DEATH_OK: FUN_14005b5c0 reborn tick verbatim"
           " (1Hz gate +0xb4/+0xb0, type-row 0x15 flag bits"
           " 3/4/7 -> gen vtable+0x68(gen,x,y) area check,"
           " map pos FUN_14004ae30 -> reborn offsets row4/5"
           " -> +0x1c/+0x20, +0x2c=0, +0x18=0) +"
           " FUN_140058860 gate (+0x140: FUN_140069750 &&"
           " !FUN_140069910 && !FUN_140069740) +"
           " FUN_14005f3b0 die dispatcher (tick first,"
           " then vtable+0x50 && !+0x148 gate, 10-pass"
           " state loop 1->FUN_14005e900/6->FUN_14005d140"
           "/7->FUN_14005d550/8->FUN_14005d330)\n");
    return 0;
}
