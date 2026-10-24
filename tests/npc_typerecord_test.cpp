// unit 42: the REAL monster-type records
// (cq_monstertype, 823 REAL v6159 rows) + the
// full type-record leg of FUN_140038010 bound
// for real: vt+0x40(id) -> the record, the
// record's vt+0xe8 -> the shared proxy
#include "../Exe/NpcServer/NpcMapBinder.h"
#include "../Exe/NpcServer/NpcTypeRecord.h"
#include <cassert>
#include <cstdio>
using namespace npc;

int main() {
    CNpcTypeTable tbl;
    if (!tbl.LoadFromCqMonstertype()) {
        printf("SKIP: cq_monstertype not "
               "reachable (no DB)\n");
        return 0;
    }

    // ===== 1) the REAL table: 823 rows =====
    printf("loaded: %zu rows\n", tbl.Size());
    assert(tbl.Size() == 823);

    // ===== 2) the REAL row values (v6159):
    //      id 1 = Pheasant =====
    CNpcTypeRecord* pR = tbl.FindVt40(1);
    assert(pR != nullptr);
    assert(pR->m_szName == "Pheasant");
    assert(pR->m_uLife == 33);
    assert(pR->m_uLookface == 104);
    assert(pR->m_uAtkMax == 3 && pR->m_uAtkMin == 2);
    assert(pR->m_uDodge == 36);
    assert(pR->m_uLevel == 1);

    // id 2 = Turtledove
    pR = tbl.FindVt40(2);
    assert(pR && pR->m_szName == "Turtledove");
    assert(pR->m_uLife == 81);

    // ===== 3) the miss =====
    assert(tbl.FindVt40(99999) == nullptr);

    // ===== 4) the full type-record leg bound
    //      for real: an id OUTSIDE the player
    //      gate, a container MISS, so
    //      FUN_140038010 goes
    //      vt+0x40 -> record -> vt+0xe8 =====
    TqGameMapCore core;
    CNpcMapBinder bind(&core);
    TqGameDataMgr gdm;
    TqLookupMgr look;
    bind.BindTypeRecords(gdm, look, tbl);
    // the shared proxy of record 1 (vt+0xe8)
    CNpcTypeRecord* pRec1 = tbl.FindVt40(1);
    pRec1->m_pProxy = (void*)0x5A000;
    bind.m_pManager = nullptr;   // container leg: absent
    bind.BindLookupContainer(look);
    g_tqKernel.m_pGameData = &gdm;
    // register record 1 under a REACHABLE id
    // (the TBD of the mgr map's key space: the
    // port registers the same record object
    // under id 500000 - in the transform range
    // [400001,700000), straight to the record)
    tbl.Register(500000, pRec1);
    void* p = TqLookupById38100(look, 500000);
    assert(p == (void*)0x5A000);
        // the record's vt+0xe8 -> the proxy

    // ===== 5) a record miss still 0 =====
    assert(TqLookupById38100(look, 499999)
        == nullptr);

    printf("NPC_TYPERECORD_OK: the REAL "
           "cq_monstertype (823 v6159 rows) "
           "loaded and bound - id 1 Pheasant "
           "(life 33, lookface 104, atk 3/2, "
           "dodge 36), id 2 Turtledove, the "
           "vt+0x40 miss, and the full "
           "type-record leg of FUN_140038010: "
           "a reachable id -> vt+0x40 -> the "
           "REAL record -> the vt+0xe8 vcall -> "
           "the shared proxy; the mgr map key "
           "space vs the player gate is a "
           "documented TBD\n");
    return 0;
}
