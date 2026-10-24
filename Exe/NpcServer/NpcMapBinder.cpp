// ============================================================
// NpcServer unit 38: the map seam binder
// - wires the real TqMapData (37) + the blocker
//   grid into the ported seams
// ============================================================
#include "NpcMapBinder.h"

namespace npc {

// ===== the blocker grid (verbatim) =====
const TqBlockerRow* TqBlockerGrid::Row49580(int nX) {
    // ORIGINAL FUN_140049580:
    //   if ((end - begin)/0x30 <= x)
    //     _invalid_parameter_noinfo;
    //   return x*0x30 + begin;
    if ((ulong)m_vRows.size() <= (ulong)nX) {
        if (m_fnInvalidParam) m_fnInvalidParam();
        return nullptr;
    }
    return &m_vRows[nX];
}

const uint32_t* TqBlockerGrid::Cell3e890(
        const TqBlockerRow& rRow, int nY) {
    // ORIGINAL FUN_14003e890:
    //   if ((end - begin)>>2 <= y)
    //     _invalid_parameter_noinfo;
    //   return begin + y*4;
    if ((ulong)rRow.m_vCells.size() <= (ulong)nY) {
        if (m_fnInvalidParam) m_fnInvalidParam();
        return nullptr;
    }
    return &rRow.m_vCells[nY];
}

uint32_t TqBlockerGrid::At(int nX, int nY) {
    const TqBlockerRow* pR = Row49580(nX);
    if (pR == nullptr) return 0;
    const uint32_t* pC = Cell3e890(*pR, nY);
    if (pC == nullptr) return 0;
    return *pC;
}

// ===== the binder =====
CNpcMapBinder::CNpcMapBinder(TqGameMapCore* pMap)
    : m_pMap(pMap) {
    BindCellCheck();
    BindGates();
}

void CNpcMapBinder::BindCellCheck() {
    // null guards (a documented port deviation:
    // the ORIGINAL faults on a null map; the
    // binder binds only what exists so tests can
    // use a bare core)
    if (m_pMap == nullptr)
        return;
    TqMapData* pMd = m_pMap->m_pMapData;
    // ===== the mapdata accessors (unit 37) =====
    if (pMd == nullptr)
        return;
    m_cell.m_fnMdWidth28 = [pMd]() {
        return pMd->WidthVt28(); };
    m_cell.m_fnMdHeight20 = [pMd]() {
        return pMd->HeightVt20(); };
    m_cell.m_fnCellType18 =
        [pMd](int nX, int nY) {
            return pMd->CellTypeVt18(nX, nY); };
    m_cell.m_fnCellAlt8 =
        [pMd](int nX, int nY) {
            return (int)pMd->AltVt08(nX, nY); };
    // ===== the blocker grid chain (49580 ->
    //      3e890 -> *uint) =====
    TqBlockerGrid* pGr = m_pMap->m_pBlockers;
    if (pGr == nullptr)
        return;
    pGr->m_fnInvalidParam =
        [this]() {
            if (m_fnInvalidParam) m_fnInvalidParam(); };
    m_cell.m_fnCellGrid =
        [pGr](int nX, int nY) {
            return pGr->At(nX, nY); };
    // ===== the two gates: the REAL bodies
    //      (units 12/32) on the bound gates =====
    m_cell.m_fn49310 = [this](int nX, int nY) {
        return CNpcPosValid49310(m_gates, nX, nY); };
    m_cell.m_fn4ab40 = [this](int nX, int nY) {
        return CNpcInBounds4ab40(m_gates, nX,
                                 nY) != 0; };
}

void CNpcMapBinder::BindGates() {
    TqMapData* pMd = m_pMap->m_pMapData;
    // FUN_140049310/4ab40 read the mapdata vt
    // slots +0x28/+0x20/+0x18 directly
    m_gates.m_fnWidth28 = [pMd]() {
        return pMd->WidthVt28(); };
    m_gates.m_fnHeight20 = [pMd]() {
        return pMd->HeightVt20(); };
    m_gates.m_fnCell18 =
        [pMd](int nX, int nY) {
            return (int)pMd->CellTypeVt18(nX, nY); };
}

void CNpcMapBinder::BindStateMap(CNpcStateData& rS) {
    // the walkable-cell check: FUN_14004cc70 =
    // CNpcCellFree on the bound cell data
    rS.m_fnInSight = [this](int nX, int nY) {
        return CNpcCellFree(m_cell, nX, nY) != 0; };
    rS.m_fn4cc70 = rS.m_fnInSight;
    // the position gate: FUN_140049310 =
    // CNpcPosValid49310 on the bound gates
    rS.m_fn49310 = [this](int nX, int nY) {
        return CNpcPosValid49310(m_gates, nX, nY); };
    // the walk check: FUN_14004bff0 with the
    // mode 0x1a of the ORIGINAL state call site
    rS.m_fnMapWalkable =
        [this](int nX, int nY, int nDir,
               uint32_t u48) {
            return CNpcWalkCheck(m_cell, nX, nY,
                                 nDir, u48, 0x1a); };
}

void CNpcMapBinder::BindTargetSearchCells(
        CNpcTargetSearchData& rT) {
    TqMapData* pMd = m_pMap->m_pMapData;
    TqCellGrid* pGr = m_pMap->m_pCells;
    pGr->m_fnInvalidParam =
        [this]() {
            if (m_fnInvalidParam) m_fnInvalidParam(); };
    // the region bounds (49490/49440 read the
    // mapdata width/height off +0x10)
    rT.m_fn490Width = [pMd]() {
        return TqCellGrid::GridWidth49490(
            pMd->WidthVt28()); };
    rT.m_fn440Height = [pMd]() {
        return TqCellGrid::GridHeight49440(
            pMd->HeightVt20()); };
    // the checked cell access (4ac70)
    rT.m_fnAc70 = [pGr](int nBase, int nRow) {
        return (uint64_t)(uintptr_t)
            pGr->Cell4ac70(nBase, nRow); };
    // the cell containers (678b0 / 678a0)
    rT.m_fn678b0 = [pGr](uint64_t uCell) {
        TqCell* pC =
            (TqCell*)(uintptr_t)uCell;
        return (uint64_t)(uintptr_t)
            TqCellGrid::NpcCont678b0(pC); };
    rT.m_fn678a0 = [pGr](uint64_t uCell) {
        TqCell* pC =
            (TqCell*)(uintptr_t)uCell;
        return (uint64_t)(uintptr_t)
            TqCellGrid::UserCont678a0(pC); };
    // the container vt surface (count/get)
    auto fnCount = [](uint64_t uCont) {
        TqObjContainer* p =
            (TqObjContainer*)(uintptr_t)uCont;
        p->m_fnInvalidParam = nullptr;
        return p->CountVt10(); };
    rT.m_fnContCount = fnCount;
    rT.m_fnContGet =
        [](uint64_t uCont, uint32_t uIdx,
           const char* pszFile, int nLine) {
            TqObjContainer* p =
                (TqObjContainer*)(
                    uintptr_t)uCont;
            return p->GetVt18(uIdx, pszFile,
                               nLine); };
}

void CNpcMapBinder::BindTargetSearchFinale(
        CNpcTargetSearchData& rT,
        CNpcShoutData& rShout) {
    // the ORIGINAL finale: theInstance() ->
    // vt[0](key) -> sprintf(buf, fmt) ->
    // FUN_1400586b0(npc, buf, 0)
    rT.m_fnShout =
        [&rShout](const char* pszKey) {
            TqStrTable* pTbl =
                TqStrTableInstance();
            const char* pszFmt =
                pTbl->GetVt0(pszKey);
            char buf[256];
            // the ORIGINAL decompile shows
            // sprintf(buf, fmt) with NO
            // varargs (the %s ambiguity -
            // modeled verbatim, see unit 40)
            sprintf(buf, "%s", pszFmt);
            CNpcShout586b0(rShout, buf,
                           nullptr);
        };
}

void CNpcMapBinder::BindTypeRecords(
        TqGameDataMgr& rG, TqLookupMgr& rL,
        CNpcTypeTable& rTbl) {
    // the ORIGINAL: mgr+0x8 map vt+0x40(id) ->
    // the monster-type record (the cq_monstertype
    // rows); FUN_140038010 then CALLS the
    // record's vt+0xe8 -> the shared proxy
    rG.m_fnMapVt40 = [&rTbl](int nId) -> void* {
        return rTbl.FindVt40((uint32_t)nId);
    };
    rL.m_fnRecordVtE8 =
        [](void* pRec) -> void* {
            return static_cast<CNpcTypeRecord*>(
                pRec)->ProxyVtE8();
        };
}

void CNpcMapBinder::BindLookupContainer(
        TqLookupMgr& rL) {
    // the ORIGINAL: FUN_14001c210()->+0x8
    // container vt+0x30(id) -> the LIVE NPC
    // base; FUN_140038010 then returns base+0x10
    // (the offset is verbatim in the ported
    // TqLookupById38100)
    CNpcManager* pMgr = m_pManager;
    rL.m_fnContainerVt30 =
        [pMgr](int nId) -> void* {
            if (!pMgr)
                return nullptr;
            return pMgr->LookupByIdVt30(
                (uint64_t)(uint32_t)nId);
        };
}

void CNpcMapBinder::BindUserTickCells(
        CNpcUserTickData& rU) {
    TqMapData* pMd = m_pMap->m_pMapData;
    TqCellGrid* pGr = m_pMap->m_pCells;
    rU.m_fn490Width = [pMd]() {
        return TqCellGrid::GridWidth49490(
            pMd->WidthVt28()); };
    rU.m_fn440Height = [pMd]() {
        return TqCellGrid::GridHeight49440(
            pMd->HeightVt20()); };
    rU.m_fnAc70 = [pGr](int nBase, int nRow) {
        return (uint64_t)(uintptr_t)
            pGr->Cell4ac70(nBase, nRow); };
    rU.m_fn678a0 = [pGr](uint64_t uCell) {
        TqCell* pC =
            (TqCell*)(uintptr_t)uCell;
        return (uint64_t)(uintptr_t)
            TqCellGrid::UserCont678a0(pC); };
    rU.m_fnContCount = [](uint64_t uCont) {
        TqObjContainer* p =
            (TqObjContainer*)(uintptr_t)uCont;
        return p->CountVt10(); };
    rU.m_fnContGet =
        [](uint64_t uCont, uint32_t uIdx,
           const char* pszFile, int nLine,
           int /*nRow*/, int /*nIdx2*/) {
            // ORIGINAL: (cont, i, file, 0x57,
            // row, i) - the user pass asserts at
            // npc.cpp line 0x57 with the row and
            // index repeated as context
            TqObjContainer* p =
                (TqObjContainer*)(
                    uintptr_t)uCont;
            return p->GetVt18(uIdx, pszFile,
                               nLine); };
}

void CNpcMapBinder::BindTransformMap(CNpcTransform& rT) {
    TqMapData* pMd = m_pMap->m_pMapData;
    rT.m_fnMapWidth = [pMd]() {
        return pMd->WidthVt28(); };
    rT.m_fnMapHeight = [pMd]() {
        return pMd->HeightVt20(); };
    rT.m_fnMapCell =
        [pMd](int nX, int nY) {
            return (int)pMd->CellTypeVt18(nX, nY); };
}

} // namespace npc
