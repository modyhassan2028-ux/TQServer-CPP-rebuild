#pragma once
// ============================================================
// NpcServer unit 39: the live-object cell grid
// THE CELL GRID (CGameMap +0x30): rows of 0x30
// bytes (FUN_14004ac70 checks base against
// (end+0x38-begin+0x30)/0x30), each row's cell vec
// at +0x18 (0x18-byte cells, checked against
// (row_end+0x20-row_begin+0x18)/0x18).
// THE BOUNDS (the region-derived grid size):
//   FUN_140049490: (width-1)/0x12 + 1
//   FUN_140049440: (height-1)/0x12 + 1
// THE CELL (0x18 bytes):
//   +0x08 the USER container (FUN_1400678a0)
//   +0x10 the NPC container (FUN_1400678b0)
// THE CONTAINERS (vt+0x10 = count, vt+0x18 =
// get(i, __FILE__, line)):
//   the ORIGINAL call site passes the literal
//   "f:\version\cqserver-78.0.11-1204\npcserver
//   \npckernel\npc.cpp" and the line 0x68f (the
//   NPC pass) / 0x6b2 (the user pass) - a real
//   build-path disclosure of the original tree,
//   preserved verbatim in the port.
//   The get body = the checked 8-byte-stride set
//   access (the 2bb00-family bounds pattern:
//   (end-begin)>>3 <= i -> _invalid_parameter).
// DOCUMENTED DEVIATION: the container's internal
// set-management functions (add/remove/insert of
// the 2bb40 family) belong to the movement code
// paths (not yet ported); the container here
// exposes the OBSERVABLE vt surface the ported
// readers use: count, checked get, and simple
// add/remove for tests/runtime.
// ============================================================
#include <cstdint>
#include <functional>
#include <vector>

namespace npc {

// the per-cell live-object container
// (ORIGINAL: the vt-bearing set object)
class TqObjContainer {
public:
    std::vector<uint64_t> m_vItems;
        // the 8-byte-stride item set (the 2bb00
        // family checks (end-begin)>>3)
    std::function<void()> m_fnInvalidParam;
        // the checked-access abort hook

    // vt+0x10: the live count
    uint32_t CountVt10();
    // vt+0x18: the checked get - the file/line
    // are the ORIGINAL assert context (npc.cpp
    // 0x68f NPC pass / 0x6b2 user pass)
    uint64_t GetVt18(uint32_t uIdx,
                     const char* pszFile, int nLine);
    // the runtime set management (movement code
    // paths - see the deviation note above)
    void Add(uint64_t uItem);
    void Remove(uint64_t uItem);
};

// the cell (ORIGINAL 0x18 bytes): +0x08 the
// user container, +0x10 the NPC container
struct TqCell {
    TqObjContainer* m_pUsers = nullptr;  // +0x08
    TqObjContainer* m_pNpcs = nullptr;   // +0x10
};

// the row (ORIGINAL 0x30 bytes): the cell vec
struct TqCellRow {
    std::vector<TqCell> m_vCells;   // +0x18
};

// the grid (ORIGINAL CGameMap+0x30)
class TqCellGrid {
public:
    std::vector<TqCellRow> m_vRows;  // +0x30
    std::function<void()> m_fnInvalidParam;

    // FUN_140049490(map): the base bound:
    //   vt28(mapdata) = width; (width-1)/0x12+1
    // (the mapdata width/height supplied by the
    //  binder, same as the ORIGINAL reads them
    //  off the +0x10 mapdata object)
    static int GridWidth49490(int nMapWidth);
    // FUN_140049440(map): (height-1)/0x12+1
    static int GridHeight49440(int nMapHeight);
    // FUN_14004ac70(map, base, row): the checked
    // [base][row] cell access
    TqCell* Cell4ac70(int nBase, int nRow);
    // FUN_1400678b0(cell): the NPC container
    static TqObjContainer* NpcCont678b0(
        TqCell* pCell);   // cell+0x10
    // FUN_1400678a0(cell): the user container
    static TqObjContainer* UserCont678a0(
        TqCell* pCell);  // cell+0x08
};

} // namespace npc
