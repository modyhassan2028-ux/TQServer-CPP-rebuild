// unit 39: the live-object cell grid - the
// containers (vt+0x10 count / vt+0x18 checked
// get), the cell access chain 4ac70, the
// container getters 678b0/678a0, the region
// bounds 49490/49440
#include "../Exe/NpcServer/NpcCellObjects.h"
#include <cassert>
#include <cstdio>
using namespace npc;

int main() {
    // ===== 1) the region bounds (verbatim
    //      (w-1)/0x12+1) =====
    assert(TqCellGrid::GridWidth49490(320) ==
           (320 - 1) / 0x12 + 1);   // 18
    assert(TqCellGrid::GridWidth49490(18) == 1);
    assert(TqCellGrid::GridWidth49490(19) == 2);
    assert(TqCellGrid::GridWidth49490(1) == 1);
        // the ORIGINAL quirk: (1-1)/18+1 = 1
    assert(TqCellGrid::GridHeight49440(240) ==
           (240 - 1) / 0x12 + 1);   // 14

    // ===== 2) the grid + containers =====
    TqCellGrid grid;
    // a 2x2 grid, each cell with its containers
    TqObjContainer conts[2][2][2];
        // [base][row][0=user, 1=npc]
    grid.m_vRows.resize(2);
    for (int b = 0; b < 2; b++)
        grid.m_vRows[b].m_vCells.resize(2);
    for (int b = 0; b < 2; b++)
        for (int r = 0; r < 2; r++) {
            grid.m_vRows[b].m_vCells[r]
                .m_pUsers = &conts[b][r][0];
            grid.m_vRows[b].m_vCells[r]
                .m_pNpcs = &conts[b][r][1];
        }
    int nAborts = 0;
    grid.m_fnInvalidParam = [&] { ++nAborts; };
    for (int b = 0; b < 2; b++)
        for (int r = 0; r < 2; r++)
            for (int k = 0; k < 2; k++)
                conts[b][r][k].m_fnInvalidParam =
                    [&] { ++nAborts; };

    // ===== 3) the cell access (4ac70) =====
    TqCell* pC = grid.Cell4ac70(0, 0);
    assert(pC == &grid.m_vRows[0].m_vCells[0]);
    assert(grid.Cell4ac70(1, 1) ==
           &grid.m_vRows[1].m_vCells[1]);
    // out of bounds -> abort + null
    int nBefore = nAborts;
    assert(grid.Cell4ac70(2, 0) == nullptr);
    assert(nAborts == nBefore + 1);
    assert(grid.Cell4ac70(0, 2) == nullptr);
    assert(nAborts == nBefore + 2);

    // ===== 4) the container getters =====
    assert(TqCellGrid::NpcCont678b0(pC) ==
           pC->m_pNpcs);
    assert(TqCellGrid::UserCont678a0(pC) ==
           pC->m_pUsers);
    assert(TqCellGrid::NpcCont678b0(nullptr) ==
           nullptr);

    // ===== 5) the container vt surface =====
    TqObjContainer* pNpc = TqCellGrid::NpcCont678b0(
        grid.Cell4ac70(1, 1));
    pNpc->Add(0x1000);
    pNpc->Add(0x2000);
    pNpc->Add(0x3000);
    assert(pNpc->CountVt10() == 3);
    // the checked get - the literal npc.cpp lines
    assert(pNpc->GetVt18(0,
        "f:\\version\\cqserver-78.0.11-1204\\"
        "npcserver\\npckernel\\npc.cpp", 0x68f)
        == 0x1000);
    assert(pNpc->GetVt18(2,
        "f:\\version\\cqserver-78.0.11-1204\\"
        "npcserver\\npckernel\\npc.cpp", 0x68f)
        == 0x3000);
    // out of bounds -> abort + 0
    nBefore = nAborts;
    assert(pNpc->GetVt18(3,
        "f:\\version\\cqserver-78.0.11-1204\\"
        "npcserver\\npckernel\\npc.cpp", 0x68f)
        == 0);
    assert(nAborts == nBefore + 1);
    // remove
    pNpc->Remove(0x2000);
    assert(pNpc->CountVt10() == 2);
    assert(pNpc->GetVt18(1, "npc.cpp", 0x68f)
        == 0x3000);

    // ===== 6) an integration walk: the
    //      region-derived search the target
    //      search performs (base from x/0x12,
    //      row from y/0x12) =====
    {
        // a 36x36 map -> grid 2x2
        assert(TqCellGrid::GridWidth49490(36) == 2);
        assert(TqCellGrid::GridHeight49440(36) == 2);
        // a creature at tile (20, 25) lives in
        // cell [20/18][25/18] = [1][1]
        int nBase = 20 / 0x12;
        int nRow = 25 / 0x12;
        TqCell* pCell = grid.Cell4ac70(nBase, nRow);
        TqObjContainer* pU =
            TqCellGrid::UserCont678a0(pCell);
        pU->Add(0xdeadbeef);
        assert(pU->GetVt18(0, "npc.cpp", 0x6b2)
            == 0xdeadbeef);
    }

    printf("NPC_CELLOBJECTS_OK: the live-object"
           " cell grid verbatim - the region bounds"
           " 49490/49440 ((w-1)/0x12+1 with the"
           " width-1 quirk), the checked cell access"
           " 4ac70 (rows 0x30 / cells 0x18 with the"
           " abort hooks), the container getters"
           " 678b0 (cell+0x10 NPCs) / 678a0"
           " (cell+0x08 users), the container vt"
           " surface (count at +0x10, the checked"
           " get at +0x18 with the literal original"
           " build path"
           " f:\\version\\cqserver-78.0.11-1204"
           "\\npcserver\\npckernel\\npc.cpp lines"
           " 0x68f/0x6b2 preserved), and the"
           " region-derived cell walk (x/0x12,"
           " y/0x12) - the set-management internals"
           " documented as a deviation (movement"
           " code paths, not yet ported)\n");
    return 0;
}
