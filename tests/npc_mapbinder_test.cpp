// unit 38: the map seam binder - the REAL TqMapData
// (37) + the blocker grid wired into the ported
// seams; every seam checked against the same
// verbatim bodies called directly
#include "../Exe/NpcServer/NpcMapBinder.h"
#include <cassert>
#include <cstdio>
using namespace npc;

int main() {
    // ===== a real 6x4 map: a border wall of
    //      cellType 1, the interior free =====
    TqMapGrid g; g.m_nWidth = 6; g.m_nHeight = 4;
    g.m_vCells.assign(24, 0xffff0000u);
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 6; x++) {
            int nIdx = y * 6 + x;
            bool bWall = (x == 0 || y == 0 ||
                          x == 5 || y == 3);
            // lo & 1 = the direct cellType bit
            g.m_vCells[nIdx] =
                0xffff0000u | (bWall ? 1u : 0u);
        }
    TqMapData md; md.m_pGrid = &g;
    // a blocker on interior cell (2,2)
    TqBlockerGrid gr;
    gr.m_vRows.resize(4);
    for (int y = 0; y < 4; y++)
        gr.m_vRows[y].m_vCells.assign(6, 0);
    gr.m_vRows[2].m_vCells[2] = 3;
    TqGameMapCore core;
    core.m_pMapData = &md;
    core.m_pBlockers = &gr;

    CNpcMapBinder b(&core);
    int nAborts = 0;
    b.m_fnInvalidParam = [&] { ++nAborts; };

    // ===== 1) the mapdata seams =====
    assert(b.m_cell.m_fnMdWidth28() == 6);
    assert(b.m_cell.m_fnMdHeight20() == 4);
    // cellType: the direct bit - walls are 1
    assert(b.m_cell.m_fnCellType18(0, 0) == 1);
    assert(b.m_cell.m_fnCellType18(2, 2) == 0);
    // alt: the direct value (lo >> 1) = 0
    assert(b.m_cell.m_fnCellAlt8(3, 1) == 0);

    // ===== 2) the gates: the REAL bodies =====
    // 49310: in bounds + cellType == 0
    assert(b.m_cell.m_fn49310(2, 2));      // free
    assert(!b.m_cell.m_fn49310(0, 0));     // wall
    assert(!b.m_cell.m_fn49310(-1, 2));
    assert(!b.m_cell.m_fn49310(2, -1));
    assert(!b.m_cell.m_fn49310(6, 2));
    assert(!b.m_cell.m_fn49310(2, 4));
    // 4ab40: pure bounds, no cell check
    assert(b.m_cell.m_fn4ab40(0, 0));     // wall ok
    assert(!b.m_cell.m_fn4ab40(6, 2));

    // ===== 3) the blocker grid chain =====
    assert(b.m_cell.m_fnCellGrid(2, 2) == 3);
    assert(b.m_cell.m_fnCellGrid(1, 1) == 0);
    // out of range -> the abort hook + 0
    int nBefore = nAborts;
    assert(b.m_cell.m_fnCellGrid(9, 2) == 0);
    assert(nAborts == nBefore + 1);

    // ===== 4) the state seams (against direct
    //      verbatim calls) =====
    CNpcStateData s;
    b.BindStateMap(s);
    // 4cc70 = free gate: 49310 && blockers == 0
    assert(s.m_fnInSight(2, 2) == false);
        // 49310 ok but blockers 3
    assert(s.m_fnInSight(1, 1) == true);
    assert(s.m_fn4cc70(0, 0) == false);  // wall
    // 49310 seam == the gate
    assert(s.m_fn49310(2, 2) == true);
    // the walkable check: a free straight cell
    // (dir 0 = S from (3,1) -> (3,2))
    assert(s.m_fnMapWalkable(3, 1, 0 /*S*/, 0));
    // the blocked cell (blockers 3) refuses the
    // type-0 walk (VERBATIM: type 0 < 3 &&
    // 0 < blockers)
    assert(!s.m_fnMapWalkable(2, 1, 0 /*S*/, 0));

    // ===== 5) the transform seams =====
    CNpcTransform t;
    b.BindTransformMap(t);
    assert(t.m_fnMapWidth() == 6);
    assert(t.m_fnMapHeight() == 4);
    assert(t.m_fnMapCell(0, 0) == 1);
    assert(t.m_fnMapCell(2, 2) == 0);

    // ===== 6) consistency: the bound seams give
    //      the same answers as the direct
    //      verbatim calls =====
    {
        // direct: CNpcCellFree on a manually
        // built cell-check data with the same
        // seams as lambdas over the same objects
        CNpcCellCheckData d2;
        d2.m_fnMdWidth28 = [&]{ return 6; };
        d2.m_fnMdHeight20 = [&]{ return 4; };
        d2.m_fnCellType18 = [&](int x, int y) {
            return g.m_vCells[y*6+x] & 1; };
        d2.m_fnCellAlt8 = [&](int, int) { return 0; };
        d2.m_fnCellGrid = [&](int x, int y) {
            return gr.m_vRows[y].m_vCells[x]; };
        d2.m_fn49310 = [&](int x, int y) {
            return CNpcPosValid49310(b.m_gates, x, y); };
        d2.m_fn4ab40 = [&](int x, int y) {
            return CNpcInBounds4ab40(b.m_gates, x, y) != 0; };
        for (int y = 0; y < 4; y++)
            for (int x = 0; x < 6; x++) {
                uint32_t uA = CNpcCellFree(b.m_cell, x, y);
                uint32_t uB = CNpcCellFree(d2, x, y);
                assert(uA == uB);
                assert(CNpcWalkCheck(b.m_cell, x, y,
                        2, 0, 0) ==
                       CNpcWalkCheck(d2, x, y, 2, 0, 0));
            }
    }

    // ===== 7) the live-object grid seams =====
    {
        TqCellGrid cells;
        TqObjContainer npcCont, userCont;
        cells.m_vRows.resize(2);
        for (int b = 0; b < 2; b++)
            cells.m_vRows[b].m_vCells.resize(2);
        for (int b = 0; b < 2; b++)
            for (int r = 0; r < 2; r++) {
                cells.m_vRows[b].m_vCells[r]
                    .m_pNpcs = &npcCont;
                cells.m_vRows[b].m_vCells[r]
                    .m_pUsers = &userCont;
            }
        core.m_pCells = &cells;
        npcCont.m_fnInvalidParam = [&]{ ++nAborts; };
        userCont.m_fnInvalidParam = [&]{ ++nAborts; };

        CNpcTargetSearchData ts;
        b.BindTargetSearchCells(ts);
        // the region bounds: 6 wide -> (6-1)/18+1
        // = 1; 4 high -> 1
        assert(ts.m_fn490Width() == 1);
        assert(ts.m_fn440Height() == 1);
        npcCont.Add(0x55);
        userCont.Add(0x66);
        uint64_t uCell = ts.m_fnAc70(0, 0);
        uint64_t uNpc = ts.m_fn678b0(uCell);
        uint64_t uUser = ts.m_fn678a0(uCell);
        assert(ts.m_fnContCount(uNpc) == 1);
        assert(ts.m_fnContGet(uNpc, 0,
            "f:\\version\\cqserver-78.0.11-1204"
            "\\npcserver\\npckernel\\npc.cpp",
            0x68f) == 0x55);
        assert(ts.m_fnContGet(uUser, 0,
            "npc.cpp", 0x6b2) == 0x66);

        CNpcUserTickData ut;
        b.BindUserTickCells(ut);
        assert(ut.m_fn490Width() == 1);
        assert(ut.m_fn678a0(
            ut.m_fnAc70(0, 0)) == uUser);
        assert(ut.m_fnContGet(uUser, 0,
            "npc.cpp", 0x57, 0, 0) == 0x66);
    }

    // ===== 8) the finale: the string table
    //      chain (unit 40) =====
    {
        TqStrTable tbl;
        tbl.LoadIni(
            "Language=English\n"
            "STR_GUARD_CALL_s=Warning %s, no PK "
            "within city limits.\n"
            "STR_PPKER_CALL_s=You have been "
            "slain, %s. We reap what we sow.\n");
        TqStrTableSetInstance(&tbl);
        std::string sShouted;
        CNpcShoutData sh;
        sh.m_fnLogError = []{};
        sh.m_fnGetName = []{ return "Guard"; };
        sh.m_fnNpcId8 = []{ return (uint32_t)
            0x7d1; };
        sh.m_fnCompose =
            [](const char* msg,
               const char* name,
               const char* chan) { return true; };
        sh.m_fnSend = [&](uint32_t uId) {
            (void)uId; sShouted = "sent"; return
            true; };
        // capture via the compose: the text lands
        // in the msg object; here verify the
        // chain fires and returns
        CNpcTargetSearchData ts2;
        b.BindTargetSearchFinale(ts2, sh);
        ts2.m_fnShout("STR_GUARD_CALL_s");
        assert(!sShouted.empty());
        sShouted.clear();
        ts2.m_fnShout("STR_PPKER_CALL_s");
        assert(!sShouted.empty());
        TqStrTableSetInstance(nullptr);
    }

    printf("NPC_MAPBINDER_OK: the map seam binder" " wired the real TqMapData (37) and the"
           " blocker grid (49580 -> 3e890 -> *uint"
           " checked chain) into the ported seams -"
           " the cell-check data (width/height/"
           "cellType/alt/grid/49310/4ab40), the map"
           " gates (49310 = bounds + cellType==0,"
           " 4ab40 = pure bounds), the state seams"
           " (InSight = 4cc70 = CNpcCellFree,"
           " MapWalkable = 4bff0 with the literal"
           " mode 0x1a) and the transform probes -"
           " all consistent with the direct verbatim"
           " calls across the full 6x4 map\n");
    return 0;
}
