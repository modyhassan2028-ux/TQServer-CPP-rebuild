// unit 37: the map grid data (CMapData) verbatim
// port test - the NPC-facing vt accessors, the base
// grid readers, the overlay walk, the refcount dance
#include "../Exe/NpcServer/NpcMapData.h"
#include <cassert>
#include <cstdio>
using namespace npc;

int main() {
    // ===== 1) the grid helpers (verbatim math) =====
    {
        TqMapGrid g; g.m_nWidth = 10; g.m_nHeight = 5;
        assert(TqMapData::GridInBounds7c0(&g, 0, 0));
        assert(TqMapData::GridInBounds7c0(&g, 9, 4));
        assert(!TqMapData::GridInBounds7c0(&g, -1, 0));
        assert(!TqMapData::GridInBounds7c0(&g, 0, -1));
        assert(!TqMapData::GridInBounds7c0(&g, 10, 0));
        assert(!TqMapData::GridInBounds7c0(&g, 0, 5));
        // FUN_14008d7e0: width * y + x
        assert(TqMapData::GridIndex7e0(&g, 3, 2) == 23);
        assert(TqMapData::GridIndex7e0(&g, 0, 0) == 0);
    }

    // ===== 2) width / height accessors =====
    {
        TqMapGrid g; g.m_nWidth = 320; g.m_nHeight = 240;
        TqMapData m; m.m_pGrid = &g;
        assert(m.WidthVt28() == 320);
        assert(m.HeightVt20() == 240);
    }

    // ===== 3) the base grid readers, direct cells
    //      (tileIdx == 0xffff) =====
    {
        TqMapGrid g; g.m_nWidth = 2; g.m_nHeight = 1;
        // cell 0: lo = 30 (alt = 15, type = 0),
        // cell 1: lo = 31 (alt = 15, type = 1)
        g.m_vCells = {0xffff0000u |
                          (uint32_t)30,
                      0xffff0000u | (uint32_t)31};
        TqMapData m; m.m_pGrid = &g;
        // alt: *(u16*)cell >> 1 (FUN_140096790)
        assert(m.AltVt08(0, 0) == 15);
        // access: 0xffff -> 0
        assert(m.AccessVt10(0, 0) == 0);
        // cellType: (*cell & 1) (FUN_1400967b0)
        assert(m.CellTypeVt18(0, 0) == 0);
        assert(m.CellTypeVt18(1, 0) == 1);
        // alt on the odd cell: 31>>1 = 15
        assert(m.AltVt08(1, 0) == 15);
    }

    // ===== 4) the base readers, tile refs =====
    {
        TqMapGrid g; g.m_nWidth = 2; g.m_nHeight = 1;
        TqTileBuf buf;
        buf.m_au16[0] = 77;   // field A
        buf.m_au16[1] = 88;   // field B
        buf.m_au16[2] = 99;   // field C
        TqTileRefBlock rb; rb.m_nStrong = 1;
        rb.m_nWeak = 1;
        TqTileEntry e; e.m_pBuf = &buf; e.m_pRef = &rb;
        g.m_vTiles.push_back(e);
        // cell 0 -> tile 0 (hi = 0)
        g.m_vCells = {(uint32_t)0u,
                      0xffff0000u};
        TqMapData m; m.m_pGrid = &g;
        int nStrongAfter = 0;
        // alt -> field A (93910)
        assert(m.AltVt08(0, 0) == 77);
        // access -> field A (93910)
        assert(m.AccessVt10(0, 0) == 77);
        // cellType -> field B (93920)
        assert(m.CellTypeVt18(0, 0) == 88);
        // the dance is net-zero on the counts
        assert(rb.m_nStrong == 1);
        // AccessVt10 on the 0xffff cell -> 0
        assert(m.AccessVt10(1, 0) == 0);
        // a tile index out of the vec -> abort hook
        g.m_vCells[0] = (uint32_t)5u << 16;  // tile 5
        int nAborts = 0;
        m.m_fnInvalidParam = [&] { ++nAborts; };
        assert(m.AltVt08(0, 0) == 0);
        assert(nAborts == 1);
    }

    // ===== 5) the three out-of-bounds tails =====
    {
        TqMapGrid g; g.m_nWidth = 2; g.m_nHeight = 2;
        g.m_vCells.assign(4, 0xffff0000u);
        TqMapData m; m.m_pGrid = &g;
        assert(m.AltVt08(5, 5) == 0x7fff);
        assert(m.AccessVt10(5, 5) == 0);
        assert(m.CellTypeVt18(5, 5) == 1);
        assert(m.AltVt08(-1, 0) == 0x7fff);
        assert(m.AccessVt10(-1, 0) == 0);
        assert(m.CellTypeVt18(-1, 0) == 1);
    }

    // ===== 6) the overlay walk =====
    {
        TqMapGrid g; g.m_nWidth = 4; g.m_nHeight = 1;
        g.m_vCells.assign(4, 0xffff0000u | 0u);
            // all direct cells: alt 0, access 0,
            // type 0
        TqMapData m; m.m_pGrid = &g;
        // tile 0 in vec2: A=100 B=200 C=300
        TqTileBuf buf;
        buf.m_au16[0] = 100; buf.m_au16[1] = 200;
        buf.m_au16[2] = 300;
        TqTileRefBlock rb; rb.m_nStrong = 1;
        TqTileEntry e; e.m_pBuf = &buf; e.m_pRef = &rb;
        m.m_vTiles2.push_back(e);
        // patches: cell 1 and cell 3 (keys NOT
        // contiguous - exercises the walk)
        m.m_mapOverlay[1] = 0;
        m.m_mapOverlay[3] = 0;
        // cell 1: patched
        assert(m.AltVt08(1, 0) == 100);       // A
        assert(m.AccessVt10(1, 0) == 300);     // C
        assert(m.CellTypeVt18(1, 0) == 200);  // B
        // cell 3: patched (the lower_bound walk
        // must find the EXACT key)
        assert(m.AltVt08(3, 0) == 100);
        assert(m.AccessVt10(3, 0) == 300);
        assert(m.CellTypeVt18(3, 0) == 200);
        // cells 0 and 2: gaps -> the base readers
        assert(m.AltVt08(0, 0) == 0);
        assert(m.AltVt08(2, 0) == 0);
        assert(m.AccessVt10(0, 0) == 0);
        assert(m.CellTypeVt18(0, 0) == 0);
        // patch value out of vec2 -> abort hook
        m.m_mapOverlay[0] = 9;
        int nAborts = 0;
        m.m_fnInvalidParam = [&] { ++nAborts; };
        m.AltVt08(0, 0);
        assert(nAborts == 1);
    }

    // ===== 7) the refcount dance =====
    {
        int nDestroyed = 0, nDeleted = 0;
        TqTileRefBlock rb;
        rb.m_nStrong = 1; rb.m_nWeak = 1;
        rb.m_fnDestroy = [&](TqTileRefBlock*) {
            ++nDestroyed; };
        rb.m_fnDeleteThis = [&](TqTileRefBlock*) {
            ++nDeleted; };
        TqTileBuf buf; buf.m_au16[0] = 7;
        TqTileEntry e; e.m_pBuf = &buf; e.m_pRef = &rb;
        TqMapData m;
        // null ref block: the dance is a no-op
        m.RefLock(nullptr); m.RefUnlock(nullptr);
        // balanced: net zero, no callbacks
        m.RefLock(&rb);
        assert(rb.m_nStrong == 2);
        m.RefUnlock(&rb);
        assert(rb.m_nStrong == 1);
        assert(nDestroyed == 0 && nDeleted == 0);
        // dec to zero: destroy fires, then the
        // weak release, then delete-this
        m.RefUnlock(&rb);
        assert(rb.m_nStrong == 0 && rb.m_nWeak == 0);
        assert(nDestroyed == 1 && nDeleted == 1);
    }

    printf("NPC_MAPDATA_OK: the map grid data"
           " verbatim (the CMapData NPC-facing vtable"
           " accessors from the binary dump 0x1400d0798"
           " - Alt 84a00 / Access 84bc0 / CellType"
           " 84d80 with their exact out-of-bounds tails"
           " 0x7fff/0/1, Width 81d60 -> d7b0 and Height"
           " 81d50 -> d7a0, the grid helpers d7c0/d7e0,"
           " the base readers 902e0/903e0/904d0 with the"
           " 4-byte cell model {lo, hi=tileIdx} - direct"
           " 0xffff cells reading lo>>1 / 0 / lo&1 and"
           " tile-ref cells reading fields A/A/B of the"
           " shared buffer via 93910/93920, the overlay"
           " map +0x1c0 walked with lower_bound"
           " exact-key semantics feeding the patch tile"
           " vec +0xb8 with fields A/C/B, the"
           " _Ref_count LOCK inc/dec dance of the tile"
           " entries with the destroy/delete-this"
           " callbacks, and the checked tile access of"
           " 83f00 with the abort hook)\n");
    return 0;
}
