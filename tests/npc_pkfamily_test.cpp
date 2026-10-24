#include "../Exe/NpcServer/NpcStateUtil.h"
#include <cassert>
#include <cstdio>
using namespace npc;

struct Cfg {
    int nDateD = 0;          // row GetInt(0xd)
    int nField24 = 0;        // row GetInt(0x24)
    int nSight10 = 20;       // row GetInt(0x10)
    int nMy78 = 0;           // my vt+0x78
    int nGetInt0 = 5;        // my GetInt(0)
    CNpcTargetSeam tgt;
    bool bFound = true;
    int nSubX = 50, nSubY = 50;
    int n24Calls = 0, nFindCalls = 0;
    Cfg() { tgt.m_nField48 = 48; }
        // nonzero so GetInt(k) != GetInt(0)
    CNpcStateData Make() {
        CNpcStateData d;
        d.m_fnRowGetFlag = []{ return 0u; };
        d.m_fnRowGetInt =
            [this](uint32_t k) {
                if (k == 0xd) return nDateD;
                if (k == 0x24) { ++n24Calls;
                    return nField24; }
                if (k == 0x10) return nSight10;
                return 0; };
        d.m_fnLogError = []{};
        d.m_fnInSight = [](int, int){ return true; };
        d.m_fnSubId18 = []{ return 4242; };
        d.m_fnSubGetX38 = [this]{ return nSubX; };
        d.m_fnSubGetY40 = [this]{ return nSubY; };
        d.m_fnSubVt48NoArgs = []{ return 7; };
        d.m_fnSubVt8 = []{ return 3; };
        d.m_fnSubDist =
            [this](int x, int y) {
                int ax = x > nSubX ? x - nSubX
                        : nSubX - x;
                int ay = y > nSubY ? y - nSubY
                        : nSubY - y;
                return ax > ay ? ax : ay; };
        d.m_fnSubMapId = []{ return 1001; };
        d.m_fnMapWalkable = [](int, int, int, uint32_t){
            return true; };
        d.m_fnTimeGet = []{ return 1000; };
        d.m_fnRandGet = [](uint32_t){ return 0; };
        d.m_fnGenGetSpawn = [](int&, int&){};
        d.m_fnFindTarget =
            [this](int) -> CNpcTargetSeam* {
                ++nFindCalls;
                return bFound ? &tgt : nullptr; };
        d.m_fnSubHasMap80 = []{ return true; };
        d.m_fnNpcId8 = []{ return 4242u; };
        d.m_fn49480Width = []{ return 1000; };
        d.m_fn49430Height = []{ return 1000; };
        d.m_fnSubVt78 = [this]{ return nMy78 != 0; };
        d.m_fnSubGetInt =
            [this](int k) {
                return k == 0 ? nGetInt0 : 100; };
        return d;
    }
};

int main() {
    // ===== 57c50: the free-PK day =========
    {
        Cfg c; c.nDateD = 500000;   // digit 5, rest 0
        auto d = c.Make();
        assert(CNpcPkDay57c50(d) == 1);
        // month slot 5 but day digits != 0
        c.nDateD = 550000;
        assert(CNpcPkDay57c50(d) == 0);
        // the masked hash product (false path)
        c.nDateD = 1234567;
        uint32_t exp =
            (uint32_t)1234567u * 0x14f8b589u;
        assert(CNpcPkDay57c50(d) ==
               (exp & 0xffffff00u));
        c.nDateD = 0;
        assert(CNpcPkDay57c50(d) == 0);
    }
    // ===== 59710 ==========================
    {
        // PK day (57c50 true) -> false
        Cfg c; c.nDateD = 500000;
        auto d = c.Make();
        assert(CNpcWorldPkGate59710(d) == 0);
        // not a PK day + 0x24 == 0 -> true
        c.nDateD = 1234567; c.nField24 = 0;
        assert(CNpcWorldPkGate59710(d) == 1);
        // 0x24 == 0x3fc -> true (the only
        // allowed nonzero)
        c.nField24 = 0x3fc;
        assert(CNpcWorldPkGate59710(d) == 1);
        // 0x24 other -> false (double read!)
        c.nField24 = 55;
        c.n24Calls = 0;
        assert(CNpcWorldPkGate59710(d) == 0);
        assert(c.n24Calls == 2);  // verbatim
    }
    // ===== 59dc0 ===========================
    // no target id -> false, cleared
    {
        Cfg c; auto d = c.Make();
        d.m_nTargetId = 0;
        assert(CNpcKeepPkTarget59dc0(d) == 0);
        assert(d.m_nTargetId == 0);
    }
    // not found -> false, cleared
    {
        Cfg c; c.bFound = false; auto d = c.Make();
        d.m_nTargetId = 77;
        assert(CNpcKeepPkTarget59dc0(d) == 0);
        assert(d.m_nTargetId == 0);
    }
    // dead -> false, cleared
    {
        Cfg c; c.tgt.m_bValid50 = false;
        auto d = c.Make();
        d.m_nTargetId = 77;
        assert(CNpcKeepPkTarget59dc0(d) == 0);
        assert(d.m_nTargetId == 0);
    }
    // alive, near (dist 5 <= sight 20), no
    // flags -> true, kept
    {
        Cfg c; c.tgt.m_nX = 55; c.tgt.m_nY = 50;
        auto d = c.Make();
        d.m_nTargetId = 77;
        assert(CNpcKeepPkTarget59dc0(d) == 1);
        assert(d.m_nTargetId == 77);
    }
    // far (dist 30 > sight 20), 30 > v
    // (v = min(100, 20) = 20) -> drop
    {
        Cfg c; c.tgt.m_nX = 80; c.tgt.m_nY = 50;
        auto d = c.Make();
        d.m_nTargetId = 77;
        assert(CNpcKeepPkTarget59dc0(d) == 0);
        assert(d.m_nTargetId == 0);
    }
    // VERBATIM FINDING: with sight < d the
    // keep branch (d <= v) is UNREACHABLE
    // (v = min(v, sight) <= sight < d), so
    // the far path ALWAYS drops. Raising
    // sight makes it near instead:
    // sight 100, d=30 -> the vt68-less keep
    {
        Cfg c; c.nSight10 = 100;
        c.tgt.m_nX = 80; c.tgt.m_nY = 50;
        auto d = c.Make();
        d.m_nTargetId = 77;
        assert(CNpcKeepPkTarget59dc0(d) == 1);
        // the GetInt(0) attacker count does
        // NOT matter here (no drop-check)
        c.nGetInt0 = 1;
        assert(CNpcKeepPkTarget59dc0(d) == 1);
        assert(d.m_nTargetId == 77);
    }
    // target vt+0x68 set -> the drop-check
    {
        Cfg c; c.tgt.m_bVt68 = true;
        c.tgt.m_nX = 55; c.tgt.m_nY = 50;
        auto d = c.Make();
        d.m_nTargetId = 77;
        // near: d=5 <= v=20 -> GetInt(0)>1
        // -> keep
        assert(CNpcKeepPkTarget59dc0(d) == 1);
        // attacker count 1 -> drop-check fails
        c.nGetInt0 = 1;
        assert(CNpcKeepPkTarget59dc0(d) == 0);
        assert(d.m_nTargetId == 0);
    }
    // THE QUIRK: target vt+0x78 set, my
    // vt+0x78 clear, PK day (9710 false ->
    // fall through); make 97110 true:
    // 0x24 == 0 -> true -> return false
    // WITHOUT clearing the target
    {
        Cfg c; c.tgt.m_bVt78 = true;
        c.nDateD = 1234567;   // not a PK day
        c.nField24 = 0;       // 97110 true
        c.tgt.m_nX = 55; c.tgt.m_nY = 50;
        auto d = c.Make();
        d.m_nTargetId = 77;
        assert(CNpcKeepPkTarget59dc0(d) == 0);
        assert(d.m_nTargetId == 77);   // KEPT!
    }
    // target vt+0x78 + MY vt+0x78 set ->
    // skip the 97110 gate -> normal logic
    {
        Cfg c; c.tgt.m_bVt78 = true;
        c.nMy78 = 1;
        c.tgt.m_nX = 55; c.tgt.m_nY = 50;
        auto d = c.Make();
        d.m_nTargetId = 77;
        assert(CNpcKeepPkTarget59dc0(d) == 1);
    }

    printf("NPC_PKFAMILY_OK: FUN_140057c50 the"
           " free-PK-day check verbatim (row"
           " GetInt(0xd), the (d%10000000)*0x14f8b589"
           " unsigned hash product, the ==5 digit"
           " slot with the -((d%100000)>>31) sign"
           " idiom, the ((d%100000)/1000)*1000==0"
           " day check returning 1, and the"
           " 0xffffff00 masked FALSE path) +"
           " FUN_140059710 the world PK gate"
           " verbatim (the 57c50 false fall,"
           " the VERBATIM double row GetInt(0x24)"
           " re-read, the 0x3fc only-allowed-value"
           " true, the CONCAT71 literal 1, and"
           " the PK-day masked false) +"
           " FUN_140059dc0 keep-PK-target verbatim"
           " (the +0x84 zero gate with the"
           " uninitialized-register return, the"
           " find/alive gates clearing the"
           " target, the target vt+0x78 + my"
           " vt+0x78-clear + 59710 TRUE path"
           " returning false WITHOUT clearing"
           " the target (the verbatim quirk),"
           " the min(my GetInt(t vt+0x48), sight)"
           " clamp, and the converged drop-check"
           " (sight < d or t vt+0x68: keep only"
           " if d <= v and my GetInt(0) > 1,"
           " else clear + false))\n");
    return 0;
}
