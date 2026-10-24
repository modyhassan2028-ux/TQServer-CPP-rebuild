#pragma once
// ============================================================
// NpcServer unit 37: the map grid data (CMapData)
// ORIGINAL: the object at CGameMap+0x10, vtable
// 0x1400d0798 in NpcServer.exe (14 slots; slot+0x48
// = FUN_14008bde0, the deleting dtor; the ctor is
// FUN_14008b610 with IMapData::vftable first)
// THE NPC-FACING SLOTS (all verified from the
// binary vtable dump):
//  +0x08 FUN_140084a00 Alt(x, y) - the altitude
//  +0x10 FUN_140084bc0 the access field C reader
//  +0x18 FUN_140084d80 CellType(x, y)
//  +0x20 FUN_140081d50 Height() -> FUN_14008d7a0
//  +0x28 FUN_140081d60 Width()  -> FUN_14008d7b0
// THE CELL MODEL (4 bytes / cell, the base grid
// readers FUN_1400902e0 / 903e0 / 904d0):
//   cell = { u16 lo, u16 hi = tileIdx }
//   hi == 0xffff -> direct: alt lo>>1 (96790) /
//     access 0 / cellType lo&1 (967b0)
//   else -> grid tile vec [hi] (0x30-byte entries)
//     -> the entry's +0x00 buffer -> field
//     A=*(u16*)buf (93910) / B=*(u16*)(buf+2)
//     (93920) / C=*(u16*)(buf+4) (93930)
// THE OVERLAY (CMapData +0x1c0, std::map<int,int>
// cellIdx -> tileIdx into the +0xb8 vec): walked
// by the three accessors BEFORE the base read -
// lower_bound(idx) semantics; found (key == idx)
// -> tile vec2 [value] -> entry buffer field
// A (alt) / C (access) / B (cellType); the found
// branch reads the SAME field as the base reader
// of each accessor.
// OUT-OF-BOUNDS returns: alt 0x7fff, access 0,
// cellType 1 (the tails verified verbatim).
// ============================================================
#include <cstdint>
#include <map>
#include <vector>
#include <functional>

namespace npc {

// the tile value buffer (>= 6 bytes used):
// {A@+0, B@+2, C@+4} - the shared per-tile data
struct TqTileBuf {
    uint16_t m_au16[4] = {};
};

// ORIGINAL tile entry (0x30 bytes): +0x00 the
// shared value buffer, +0x08 the _Ref_count block
// (the LOCK inc/dec dance of the base readers,
// fields: strong +0x10, weak +0x14, vt+0x00 the
// destroy pair)
struct TqTileRefBlock {
    int m_nStrong = 0;             // +0x10
    int m_nWeak = 0;               // +0x14
    std::function<void(TqTileRefBlock*)> m_fnDestroy;   // vt+0x00
    std::function<void(TqTileRefBlock*)> m_fnDeleteThis;// vt+0x08
};

struct TqTileEntry {
    const TqTileBuf* m_pBuf = nullptr;  // +0x00
    TqTileRefBlock* m_pRef = nullptr;   // +0x08
    // ORIGINAL pads to 0x30 bytes (unused tail)
};

// the base grid (ORIGINAL CMapData +0x100):
// width +0x00, height +0x04, cells +0x08
// (4 bytes / cell), tile vec +0x1c (0x30 entries)
struct TqMapGrid {
    int m_nWidth = 0;        // FUN_14008d7b0: *(int*)grid
    int m_nHeight = 0;       // FUN_14008d7a0: *(int*)(grid+4)
    std::vector<uint32_t> m_vCells;      // +0x08
    std::vector<TqTileEntry> m_vTiles;   // +0x1c
};

class TqMapData {
public:
    // ===== ORIGINAL CMapData members used here =====
    TqMapGrid* m_pGrid = nullptr;       // +0x100
    std::vector<TqTileEntry> m_vTiles2; // +0xb8 (the
        // overlay-patch tile vec; size check
        // (+0xc0-+0xb8)/0x30 verbatim in the walk)
    std::map<int, int> m_mapOverlay;    // +0x1c0:
        // cellIdx -> index into m_vTiles2
    // ===== test seams =====
    std::function<void()> m_fnInvalidParam;
        // _invalid_parameter_noinfo (the checked
        // vector access + the debug iterator
        // validation of FUN_140083f00 - modeled
        // as this single abort hook; the inner
        // MSVC debug checks have no behavior
        // beyond the abort and are documented,
        // not modeled)

    // ===== the vt accessors (verbatim) =====
    uint16_t AltVt08(int nX, int nY);        // 84a00
    uint16_t AccessVt10(int nX, int nY);    // 84bc0
    uint16_t CellTypeVt18(int nX, int nY);  // 84d80
    int HeightVt20();                       // 81d50
    int WidthVt28();                        // 81d60

    // ===== the base grid helpers =====
    // FUN_14008d7c0: in-bounds check
    static bool GridInBounds7c0(const TqMapGrid* pG,
                                int nX, int nY);
    // FUN_14008d7e0: the cell index *width + x
    static int GridIndex7e0(const TqMapGrid* pG,
                            int nX, int nY);

    // ===== the refcount dance of the base
    //      readers (public for the unit test;
    //      the callers in the original are the
    //      base readers themselves) =====
    void RefLock(TqTileRefBlock* pR);
    void RefUnlock(TqTileRefBlock* pR);

private:
    // the shared overlay walk: returns true and
    // fills rnTileIdx when an EXACT overlay
    // entry exists for the cell (the lower_bound
    // + `!(idx < key)` found-condition verbatim)
    bool OverlayFind(int nIdx, int& rnTileIdx);
    // the checked tile access (FUN_140083f00
    // semantics: bounds check + &vec[idx])
    const TqTileEntry* TileAt1st83f00(
        const std::vector<TqTileEntry>& rv, int nIdx);
    // the base readers (verbatim):
    uint16_t BaseAlt902e0(const TqMapGrid* pG,
                          int nX, int nY);
    uint16_t BaseAccess903e0(const TqMapGrid* pG,
                             int nX, int nY);
    uint16_t BaseType904d0(const TqMapGrid* pG,
                           int nX, int nY);
};

} // namespace npc
