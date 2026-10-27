#pragma once
// ============================================================
// NpcServer unit 38: the map seam binder
// Wires the REAL map objects of units 32/37
// (TqMapData + the blocker grid) into the
// std::function seams of the ported modules -
// the first integration layer. Everything bound
// here is verbatim: each seam maps to its
// ORIGINAL function body (already ported in
// units 12/32) or the verbatim TqMapData
// accessors (unit 37).
// ============================================================
#include <cstdint>
#include <functional>
#include <vector>
#include "NpcCellCheck.h"
#include "NpcState.h"
#include "NpcTransform.h"
#include "NpcTargetSearch.h"
#include "NpcUserTick.h"
#include "NpcMapData.h"
#include "NpcCellObjects.h"
#include "NpcStrTable.h"
#include "NpcStateUtil.h"
#include "NpcManager.h"
#include "NpcTypeRecord.h"
#include "TqKernel.h"

namespace npc {

// ORIGINAL: the blocker-count grid of CGameMap
// (+0x58): rows of 0x30 bytes, the u32 vec of
// each row at +0x18 (FUN_140049580 checks the row
// index against (end+0x20 - begin+0x18)/0x30;
// FUN_14003e890 checks the cell index against
// (end+0x20 - begin+0x18)>>2)
struct TqBlockerRow {
    std::vector<uint32_t> m_vCells;   // +0x18
};

struct TqBlockerGrid {
    std::vector<TqBlockerRow> m_vRows;  // +0x18
    std::function<void()> m_fnInvalidParam;
        // the _invalid_parameter_noinfo of the two
        // checked accesses (the MSVC debug
        // internals documented, not modeled)

    // FUN_140049580(grid, x): the checked row
    // access -> &rows[x]
    const TqBlockerRow* Row49580(int nX);
    // FUN_14003e890(row, y): the checked u32
    // access -> &row.cells[y]
    const uint32_t* Cell3e890(const TqBlockerRow& rRow,
                              int nY);
    // the chain 49580 -> 3e890 -> *uint
    // (the seam m_fnCellGrid body)
    uint32_t At(int nX, int nY);
};

// the NPC-side view of CGameMap: the +0x10
// mapdata object (unit 37) and the +0x58 blocker
// grid
struct TqGameMapCore {
    TqMapData* m_pMapData = nullptr;   // +0x10
    TqCellGrid* m_pCells = nullptr;    // +0x30
    TqBlockerGrid* m_pBlockers = nullptr; // +0x58
};

class CNpcMapBinder {
public:
    explicit CNpcMapBinder(TqGameMapCore* pMap);

    // the shared abort hook (funneled from the
    // grid + the checked tile accesses)
    std::function<void()> m_fnInvalidParam;

    // the seam structs this binder owns and keeps
    // bound to the REAL map
    CNpcCellCheckData m_cell;
    CNpcMapGateData m_gates;

    // bind the map seams of a state data (the
    // ORIGINAL call sites all pass the same map):
    //   m_fnInSight(a, b)  = FUN_14004cc70(map, a, b)
    //   m_fn4cc70(a, b)    = FUN_14004cc70(map, a, b)
    //   m_fn49310(a, b)    = FUN_140049310(map, a, b)
    //   m_fnMapWalkable(x, y, dir, u48) =
    //       FUN_14004bff0(map, x, y, dir, u48, 0x1a)
    void BindStateMap(CNpcStateData& rS);

    // bind the live-object grid seams of the
    // target search (the ORIGINAL passes the
    // same map): m_fn490Width/m_fn440Height =
    // the region bounds 49490/49440;
    // m_fnAc70 = the checked cell access;
    // m_fn678b0/m_fn678a0 = the cell's NPC /
    // user containers; m_fnContCount =
    // vt+0x10; m_fnContGet = vt+0x18 with
    // the literal npc.cpp lines 0x68f/0x6b2
    void BindTargetSearchCells(
        CNpcTargetSearchData& rT);
    // bind the user-tick container seams (the
    // user pass: npc.cpp line 0x6b2)
    void BindUserTickCells(CNpcUserTickData& rU);
    // bind the target-search finale: the
    // shout chain theInstance()->get(key) +
    // sprintf + FUN_1400586b0(npc, buf, 0)
    // (the string table unit 40 + the ported
    // shout unit 33)
    void BindTargetSearchFinale(
        CNpcTargetSearchData& rT,
        CNpcShoutData& rShout);
    // bind the state's m_fnAd20 (unit 43):
    // FUN_14004ad20(map, role) - the REAL
    // role-presence scan body over the grid
    // (the ORIGINAL passes the same map +0x98)
    void BindAd20(CNpcStateData& rS);
    // bind the REAL type records (unit 42):
    // the game-data mgr's vt+0x40(id) -> the
    // cq_monstertype table, and the lookup's
    // record vt+0xe8 vcall -> the record's
    // ProxyVtE8 (the shared proxy object)
    void BindTypeRecords(TqGameDataMgr& rG,
                        TqLookupMgr& rL,
                        CNpcTypeTable& rTbl);
    // bind the kernel lookup container leg
    // (FUN_140038010's vt+0x30(id)) to the REAL
    // manager by-id map (the +0x10 offset stays
    // verbatim inside the ported lookup)
    void BindLookupContainer(TqLookupMgr& rL);
    // the manager this binder binds (owned by
    // the runtime harness)
    CNpcManager* m_pManager = nullptr;

    // bind the transform's 49310 probes:
    //   m_fnMapWidth  = mapdata vt+0x28
    //   m_fnMapHeight = mapdata vt+0x20
    //   m_fnMapCell(x, y) = mapdata vt+0x18
    void BindTransformMap(CNpcTransform& rT);

private:
    TqGameMapCore* m_pMap;
    void BindCellCheck();
    void BindGates();
};

} // namespace npc
