// ============================================================
// NpcServer unit 37: the map grid data (CMapData)
// - verbatim port of the NPC-facing accessors
// ============================================================
#include "NpcMapData.h"

namespace npc {

// ===== the base grid helpers (verbatim) =====
bool TqMapData::GridInBounds7c0(const TqMapGrid* pG,
                                int nX, int nY) {
    // ORIGINAL FUN_14008d7c0:
    //   return x >= 0 && y >= 0 &&
    //          x < *(int*)g && y < g[1];
    return ((((-1 < nX) && (-1 < nY)) &&
             (nX < pG->m_nWidth)) &&
            (nY < pG->m_nHeight));
}

int TqMapData::GridIndex7e0(const TqMapGrid* pG,
                            int nX, int nY) {
    // ORIGINAL FUN_14008d7e0:
    //   return *param_1 * param_3 + param_2;
    return pG->m_nWidth * nY + nX;
}

int TqMapData::HeightVt20() {
    // ORIGINAL FUN_140081d50:
    //   FUN_14008d7a0(*(this + 0x100)) =
    //   *(int *)(grid + 4)
    return m_pGrid->m_nHeight;
}

int TqMapData::WidthVt28() {
    // ORIGINAL FUN_140081d60:
    //   FUN_14008d7b0(*(this + 0x100)) =
    //   *(int *)grid
    return m_pGrid->m_nWidth;
}

// ===== the refcount dance of the base readers =====
// ORIGINAL (in 902e0/903e0/904d0): the tile entry's
// +0x08 _Ref_count block: LOCK; strong(+0x10) += 1;
// UNLOCK; ... read ...; LOCK; strong -= 1; UNLOCK;
// if (strong == 0) { block->vt+0x00 (destroy);
//   LOCK; weak(+0x14) -= 1; UNLOCK;
//   if (weak == 0) block->vt+0x08 (delete this); }
void TqMapData::RefLock(TqTileRefBlock* pR) {
    if (pR != nullptr) {
        ++pR->m_nStrong;
    }
}

void TqMapData::RefUnlock(TqTileRefBlock* pR) {
    if (pR != nullptr) {
        --pR->m_nStrong;
        if (pR->m_nStrong == 0) {
            if (pR->m_fnDestroy) {
                pR->m_fnDestroy(pR);
            }
            --pR->m_nWeak;
            if (pR->m_nWeak == 0 && pR->m_fnDeleteThis) {
                pR->m_fnDeleteThis(pR);
            }
        }
    }
}

// ===== the checked tile access (83f00) =====
const TqTileEntry* TqMapData::TileAt1st83f00(
    const std::vector<TqTileEntry>& rv, int nIdx) {
    // ORIGINAL: the outer bounds check happens at
    // the call site ((end-begin)/0x30 <= idx ->
    // _invalid_parameter_noinfo); FUN_140083f00
    // is the MSVC checked-iterator dereference
    // (debug checks with no behavior beyond the
    // abort) returning &vec[idx]
    if ((long)rv.size() <= nIdx) {
        if (m_fnInvalidParam) m_fnInvalidParam();
        return nullptr;
    }
    return &rv[nIdx];
}

// ===== the overlay walk =====
bool TqMapData::OverlayFind(int nIdx,
                            int& rnTileIdx) {
    // ORIGINAL: the std::map tree walk of the
    // three accessors: lower_bound(idx); found
    // iff candidate != head && !(idx < key)
    // (i.e. the EXACT key - verified by tracing
    // the walk on the decompile)
    auto it = m_mapOverlay.lower_bound(nIdx);
    if (it == m_mapOverlay.end() ||
        it->first > nIdx) {
        return false;
    }
    rnTileIdx = it->second;   // node+0x1c (the
                             // value right after
                             // the +0x18 key)
    return true;
}

// ===== the base grid readers (verbatim) =====
uint16_t TqMapData::BaseAlt902e0(const TqMapGrid* pG,
                                 int nX, int nY) {
    // cell = cells + (width*y + x)*4; the tile
    // idx = *(u16*)(cell+2) (FUN_1400967a0)
    const uint8_t* pCell =
        reinterpret_cast<const uint8_t*>(
            pG->m_vCells.data()) +
        (long)(pG->m_nWidth * nY + nX) * 4;
    int iVar8 = *(const uint16_t*)(pCell + 2);
    if (iVar8 == 0xffff) {
        // FUN_140096790: return *(u16*)cell >> 1
        return *(const uint16_t*)pCell >> 1;
    }
    if ((ulong)pG->m_vTiles.size() <=
        (ulong)(long)iVar8) {
        if (m_fnInvalidParam) m_fnInvalidParam();
        return 0;
    }
    const TqTileEntry& rE = pG->m_vTiles[iVar8];
    RefLock(rE.m_pRef);
    // FUN_140093910: *(u16*)entryBuf
    uint16_t uRet = rE.m_pBuf->m_au16[0];
    RefUnlock(rE.m_pRef);
    return uRet;
}

uint16_t TqMapData::BaseAccess903e0(
        const TqMapGrid* pG, int nX, int nY) {
    const uint8_t* pCell =
        reinterpret_cast<const uint8_t*>(
            pG->m_vCells.data()) +
        (long)(pG->m_nWidth * nY + nX) * 4;
    int iVar5 = *(const uint16_t*)(pCell + 2);
    if (iVar5 == 0xffff) {
        return 0;    // VERBATIM: direct -> 0
    }
    if ((ulong)pG->m_vTiles.size() <=
        (ulong)(long)iVar5) {
        if (m_fnInvalidParam) m_fnInvalidParam();
        return 0;
    }
    const TqTileEntry& rE = pG->m_vTiles[iVar5];
    RefLock(rE.m_pRef);
    uint16_t uRet = rE.m_pBuf->m_au16[0];
    RefUnlock(rE.m_pRef);
    return uRet;
}

uint16_t TqMapData::BaseType904d0(const TqMapGrid* pG,
                                 int nX, int nY) {
    const uint8_t* pCell =
        reinterpret_cast<const uint8_t*>(
            pG->m_vCells.data()) +
        (long)(pG->m_nWidth * nY + nX) * 4;
    int iVar8 = *(const uint16_t*)(pCell + 2);
    if (iVar8 == 0xffff) {
        // FUN_1400967b0: (*cell & 1) == 1
        return (uint16_t)(
            (*pCell & 1) == 1 ? 1 : 0);
    }
    if ((ulong)pG->m_vTiles.size() <=
        (ulong)(long)iVar8) {
        if (m_fnInvalidParam) m_fnInvalidParam();
        return 0;
    }
    const TqTileEntry& rE = pG->m_vTiles[iVar8];
    RefLock(rE.m_pRef);
    // FUN_140093920: *(u16*)(entryBuf + 2)
    uint16_t uRet = rE.m_pBuf->m_au16[1];
    RefUnlock(rE.m_pRef);
    return uRet;
}

// ===== the NPC-facing accessors (verbatim) =====
uint16_t TqMapData::AltVt08(int nX, int nY) {
    // ORIGINAL FUN_140084a00:
    //   if (!bounds(grid, x, y)) return 0x7fff;
    //   idx = width*y+x;
    //   overlay walk -> patch: vec2[value] ->
    //     *(u16*)entryBuf (93910);
    //   not found -> FUN_1400902e0(grid, x, y)
    if (!GridInBounds7c0(m_pGrid, nX, nY)) {
        return 0x7fff;
    }
    int nIdx = GridIndex7e0(m_pGrid, nX, nY);
    int nTileIdx = 0;
    if (OverlayFind(nIdx, nTileIdx)) {
        const TqTileEntry* pE =
            TileAt1st83f00(m_vTiles2, nTileIdx);
        if (pE != nullptr) {
            return pE->m_pBuf->m_au16[0];
        }
        return 0;
    }
    return BaseAlt902e0(m_pGrid, nX, nY);
}

uint16_t TqMapData::AccessVt10(int nX, int nY) {
    // ORIGINAL FUN_140084bc0: the twin of
    // FUN_140084a00 with the base reader
    // FUN_1400903e0 and the patch field
    // *(u16*)(entryBuf+4) (93930); the
    // out-of-bounds tail returns 0
    if (!GridInBounds7c0(m_pGrid, nX, nY)) {
        return 0;
    }
    int nIdx = GridIndex7e0(m_pGrid, nX, nY);
    int nTileIdx = 0;
    if (OverlayFind(nIdx, nTileIdx)) {
        const TqTileEntry* pE =
            TileAt1st83f00(m_vTiles2, nTileIdx);
        if (pE != nullptr) {
            // FUN_140093930: *(u16*)(buf+4)
            return pE->m_pBuf->m_au16[2];
        }
        return 0;
    }
    return BaseAccess903e0(m_pGrid, nX, nY);
}

uint16_t TqMapData::CellTypeVt18(int nX, int nY) {
    // ORIGINAL FUN_140084d80: the twin with the
    // base reader FUN_1400904d0 and the patch
    // field *(u16*)(entryBuf+2) (93920); the
    // out-of-bounds tail returns 1
    if (!GridInBounds7c0(m_pGrid, nX, nY)) {
        return 1;
    }
    int nIdx = GridIndex7e0(m_pGrid, nX, nY);
    int nTileIdx = 0;
    if (OverlayFind(nIdx, nTileIdx)) {
        const TqTileEntry* pE =
            TileAt1st83f00(m_vTiles2, nTileIdx);
        if (pE != nullptr) {
            // FUN_140093920: *(u16*)(buf+2)
            return pE->m_pBuf->m_au16[1];
        }
        return 0;
    }
    return BaseType904d0(m_pGrid, nX, nY);
}

} // namespace npc
