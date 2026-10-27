// unit 41: the kernel lookup container leg bound
// to the REAL manager by-id map - the verbatim
// +0x10 offset of FUN_140038010, the player-id
// gate, the transform-range bypass, and the
// type-record fallback leg
#include "../npcserver/NpcMapBinder.h"
#include "../npcserver/NpcManager.h"
#include "../npcserver/TqKernel.h"
#include <cassert>
#include <cstdio>
using namespace npc;

int main() {
    // the manager with two live NPCs
    CNpcManager mgr;
    NpcObj a, b;
    a.m_uId = 400001; b.m_uId = 999999;
    a.m_pIface10 = (void*)0xAAAA;
    b.m_pIface10 = (void*)0xBBBB;
    mgr.m_mapNpcSet[400001] = &a;
    mgr.m_mapNpcSet[999999] = &b;

    TqGameMapCore core;
    CNpcMapBinder bind(&core);
    bind.m_pManager = &mgr;

    TqLookupMgr look;
    bind.BindLookupContainer(look);

    // the kernel game-data (the type-record leg)
    TqGameDataMgr gdm;
    int nTypeCalls = 0;
    gdm.m_fnMapVt40 = [&](int nId) -> void* {
        ++nTypeCalls;
        // the monster-type record for id 500000
        // (in [400001,700000) - the transform range:
        // the live container is NOT probed)
        return nId == 500000 ? (void*)0x7E000 : nullptr;
    };
    TqStrTable tbl;   // unused here, just init
    TqGameDataGet1c7a0();  // touch the singleton
    g_tqKernel.m_pGameData = &gdm;
    // the record vt+0xe8 seam: the type record's
    // proxy vcall
    look.m_fnRecordVtE8 = [](void* pRec) -> void* {
        // the ORIGINAL: rec vt+0xe8() -> the proxy
        return (void*)((char*)pRec + 0xE8);
    };

    // ===== 1) the live-container leg: an NPC id
    //      OUTSIDE the transform range =====
    void* p = TqLookupById38100(look, 999999);
    // verbatim: the container hit's base + 0x10
    assert(p == (char*)&b + 0x10);

    // ===== 2) a MISS on the live container
    //      falls through to the type record =====
    nTypeCalls = 0;
    p = TqLookupById38100(look, 888888);
    assert(nTypeCalls == 1);
    assert(p == nullptr);   // no record for it

    // ===== 3) the transform-range bypass: ids in
    //      [400001, 700000) skip the container and
    //      go straight to the record =====
    nTypeCalls = 0;
    p = TqLookupById38100(look, 500000);
    assert(nTypeCalls == 1);
    assert(p == (void*)0x7E0E8);
        // 0x7E000 + 0xe8 (the seam's model)

    // ===== 4) the player-id gate: [1, 300000)
    //      returns 0 without touching anything =====
    nTypeCalls = 0;
    assert(TqLookupById38100(look, 5) == nullptr);
    assert(nTypeCalls == 0);

    // ===== 5) an NPC in the transform range
    //      [400001,700000): 400001 skips the
    //      container too (goes to the record) =====
    nTypeCalls = 0;
    p = TqLookupById38100(look, 400001);
    assert(nTypeCalls == 1);   // container NOT used
    assert(p == nullptr);      // no record

    // ===== 6) the absent-manager leg (a manager
    //      bound as absent at BIND time: the
    //      lambda captured the null pointer) =====
    bind.m_pManager = nullptr;
    bind.BindLookupContainer(look);
    p = TqLookupById38100(look, 999999);
    assert(p == nullptr);
    bind.m_pManager = &mgr;
    bind.BindLookupContainer(look);

    printf("NPC_LOOKUPBIND_OK: the kernel lookup "
           "container leg bound to the REAL manager "
           "by-id map - the verbatim base+0x10 of "
           "FUN_140038010 (the embedded I3DObj "
           "interface), the player gate [1,300000) "
           "-> 0, the transform-range bypass "
           "[400001,700000) straight to the record, "
           "the miss fallthrough to the type record "
           "leg (the vt+0xe8 seam), and the "
           "absent-manager 0\n");
    return 0;
}
