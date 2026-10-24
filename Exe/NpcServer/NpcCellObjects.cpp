// ============================================================
// NpcServer unit 39: the live-object cell grid
// ============================================================
#include "NpcCellObjects.h"

namespace npc {

// ===== the container (the observable vt surface) =====
uint32_t TqObjContainer::CountVt10() {
    // ORIGINAL vt+0x10: the live count of the set
    // (the set's (end-begin)>>3)
    return (uint32_t)m_vItems.size();
}

uint64_t TqObjContainer::GetVt18(uint32_t uIdx,
        const char* /*pszFile*/, int /*nLine*/) {
    // ORIGINAL vt+0x18: the checked access
    // (the 2bb00-family bounds pattern:
    //  (end-begin)>>3 <= i ->
    //  _invalid_parameter_noinfo; the file/line
    //  are the assert context)
    if ((ulong)m_vItems.size() <= (ulong)uIdx) {
        if (m_fnInvalidParam) m_fnInvalidParam();
        return 0;
    }
    return m_vItems[uIdx];
}

void TqObjContainer::Add(uint64_t uItem) {
    // the runtime set management (see the
    // deviation note in the header)
    m_vItems.push_back(uItem);
}

void TqObjContainer::Remove(uint64_t uItem) {
    for (size_t i = 0; i < m_vItems.size(); i++) {
        if (m_vItems[i] == uItem) {
            m_vItems.erase(m_vItems.begin() +
                           (long)i);
            return;
        }
    }
}

// ===== the cell grid =====
int TqCellGrid::GridWidth49490(int nMapWidth) {
    // ORIGINAL FUN_140049490:
    //   w = mapdata vt+0x28();
    //   return (w - 1) / 0x12 + 1;
    return (nMapWidth - 1) / 0x12 + 1;
}

int TqCellGrid::GridHeight49440(int nMapHeight) {
    // ORIGINAL FUN_140049440:
    //   h = mapdata vt+0x20();
    //   return (h - 1) / 0x12 + 1;
    return (nMapHeight - 1) / 0x12 + 1;
}

TqCell* TqCellGrid::Cell4ac70(int nBase, int nRow) {
    // ORIGINAL FUN_14004ac70(map, base, row):
    //   if ((rows_end - rows_begin)/0x30 <= base)
    //     _invalid_parameter_noinfo;
    //   row = base*0x30 + rows_begin;
    //   if ((cells_end - cells_begin)/0x18 <= row_)
    //     _invalid_parameter_noinfo;
    //   return cells_begin + row*0x18;
    if ((ulong)m_vRows.size() <= (ulong)nBase) {
        if (m_fnInvalidParam) m_fnInvalidParam();
        return nullptr;
    }
    TqCellRow& rRow = m_vRows[nBase];
    if ((ulong)rRow.m_vCells.size() <=
        (ulong)nRow) {
        if (m_fnInvalidParam) m_fnInvalidParam();
        return nullptr;
    }
    return &rRow.m_vCells[nRow];
}

TqObjContainer* TqCellGrid::NpcCont678b0(
        TqCell* pCell) {
    // ORIGINAL FUN_1400678b0: cell+0x10
    return pCell ? pCell->m_pNpcs : nullptr;
}

TqObjContainer* TqCellGrid::UserCont678a0(
        TqCell* pCell) {
    // ORIGINAL FUN_1400678a0: cell+0x08
    return pCell ? pCell->m_pUsers : nullptr;
}

// ===== FUN_14004ad20: the role-presence scan
// (gamemap.cpp; the ORIGINAL get passes its own
// literal assert context gamemap.cpp 0x129 -
// the THIRD file/line pair after npc.cpp
// 0x68f/0x6b2) =====
bool IsRolePresent4ad20(TqCellGrid& rGrid,
                        TqRoleIface* pRole) {
    // ORIGINAL VERBATIM:
    //   if (role == 0) return 0;
    //   cell = FUN_14004aba0(map,
    //          role->vt+0x38(), role->vt+0x40());
    //   cont = FUN_1400678b0(cell);   // +0x10
    //   n = cont->vt+0x10();
    //   i = 0;
    //   while (i < n) {
    //     item = cont->vt+0x18(i,
    //       "f:\version\cqserver-78.0.11-1204"
    //       "\npcserver\npckernel\gamemap.cpp",
    //       0x129);
    //     if (item) {
    //       iface = item + 0x10;
    //       if (iface->vt+0x38() ==
    //               role->vt+0x38()
    //        && iface->vt+0x40() ==
    //               role->vt+0x40())
    //         return 1;
    //     }
    //     ++i;
    //     n = cont->vt+0x10();   // re-read LIVE
    //   }
    //   return 0;
    if (pRole == nullptr)
        return false;
    int nX = pRole->m_fnX38();
    int nY = pRole->m_fnY40();
    TqCell* pCell = rGrid.Cell4ac70(
        nX / 0x12, nY / 0x12);
    if (pCell == nullptr) {
        // the ORIGINAL's 4aba0 has NO null path
        // (raw vector math); the port's
        // checked Cell4ac70 aborts + 0 -
        // documented deviation
        return false;
    }
    TqObjContainer* pCont =
        TqCellGrid::NpcCont678b0(pCell);
    if (pCont == nullptr)
        return false;
    uint32_t uCount = pCont->CountVt10();
    for (uint32_t i = 0; i < uCount; ++i) {
        uint64_t h = pCont->GetVt18(i,
            "f:\\version\\cqserver-78.0.11-1204"
            "\\npcserver\\npckernel\\gamemap.cpp",
            0x129);
        if (h != 0) {
            TqItemIface* pIf =
                rGrid.m_fnItemToIface ?
                rGrid.m_fnItemToIface(h) : nullptr;
            if (pIf && pIf->m_fnX38
                && pIf->m_fnY40
                && pIf->m_fnX38() ==
                    pRole->m_fnX38()
                && pIf->m_fnY40() ==
                    pRole->m_fnY40()) {
                return true;
            }
        }
        uCount = pCont->CountVt10();
            // the ORIGINAL re-reads the count
    }
    return false;
}

} // namespace npc
