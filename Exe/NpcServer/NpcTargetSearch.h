#pragma once
// ============================================================
// NpcServer unit 27: FUN_14005bc80 — target search
// (file literal: "f:\version\cqserver-78.0.11-1204\
//  npcserver\npckernel\npc.cpp" lines 0x68f/0x6b2)
// ============================================================
// ORIGINAL flow (verbatim quirks documented in
// NpcTargetSearch.cpp):
//  - map gate with the local_488 = 0x66a code
//  - the PK block on row(0x15) bits 8/9 with
//    FUN_140059dc0 and TWO early returns
//  - +0x84 is ZEROED before the old-target
//    find, so the validate block looks up id 0
//    (dead in the original - kept verbatim)
//  - the argument-less GetInt render gating the
//    scan on bit 1
//  - ring scan (0x12 grid) like FUN_140066820
//  - pass 1: the FUN_1400678b0 NPC container
//    (literal npc.cpp 0x68f), pass 2: the
//    FUN_1400678a0 user container (0x6b2)
//  - the STR_GUARD_CALL_s / STR_PPKER_CALL_s
//    shouts via theInstance() + sprintf +
//    FUN_1400586b0
//  - FUN_14005b760(npc, 0) at the end
// ============================================================
#include <cstdint>
#include <functional>

namespace npc {

inline const char* const k_pszNpcCppFile =
    "f:\\version\\cqserver-78.0.11-1204"
    "\\npcserver\\npckernel\\npc.cpp";

struct CNpcTargetSearchData {
    bool m_bHasMap = false;
        // +0x98 (param_1[0x13])
    int32_t m_nTargetId = 0;
        // +0x84 - cleared at scan start
    int32_t m_nField18Int = 0;
        // +0x18 as int (== 1 -> the PPKER guard)
    std::function<void()> m_fnLogError;
        // log_InlineLogERROR(DAT_1400be0b0)
    // ===== row (via +0xa0 +0x10) =====
    std::function<int(uint32_t)> m_fnRowGetInt;
        // row vt+0x10(key) - keys 0x15/0x10/0x24
    std::function<int()> m_fnRowGetIntNoArg;
        // the ARGUMENT-LESS render gating the
        // scan (stale-register artifact; tests
        // bind it to GetInt(0x10))
    // ===== helper gates =====
    std::function<bool()> m_fn59dc0;
        // FUN_140059dc0(npc)
    std::function<bool(uint64_t)> m_fn5ab20;
        // FUN_14005ab20(item)
    std::function<bool()> m_fn59710;
        // FUN_140059710(npc)
    std::function<bool()> m_fn57c50;
        // FUN_140057c50(npc)
    // ===== target lookups =====
    std::function<uint64_t(int)> m_fnFindTarget;
        // FUN_140038010(FUN_14001c210(), id)
    std::function<int(int, int)> m_fnSubDist;
        // sub vt+8(x, y)
    std::function<int(int)> m_fnSubGetInt;
        // sub vt+0x10(key) - the level lookup
        // and the GetInt(0) > 1 attacker count
    std::function<int()> m_fnSubGetX38,
                         m_fnSubGetY40;
    std::function<bool()> m_fnSubVt58,
                         m_fnSubVt70,
                         m_fnSubVt78;
    // ===== item accessors =====
    std::function<bool(uint64_t)> m_fnItemAlive;
        // item vt+0x50 (pass 2 / validate)
    std::function<bool(uint64_t)> m_fnItemSubAlive;
        // the item SUB vt+0x50 (pass 1)
    std::function<uint32_t(uint64_t)>
        m_fnItemSubFlags;
        // item sub vt+0x20 word
        // (bits 0 / 0xf / 0x1d)
    std::function<int(uint64_t)> m_fnItemSubGet48;
        // item sub vt+0x48 (level)
    std::function<int(uint64_t)> m_fnItemX38,
                                 m_fnItemY40;
    std::function<uint32_t(uint64_t)> m_fnItemId8;
        // pass 1 target id (item vt+8)
    std::function<uint32_t(uint64_t)>
        m_fnItemId28;
        // pass 2 target id (item vt+0x28)
    std::function<bool(uint64_t)> m_fnItemVt58,
                                  m_fnItemVt68,
                                  m_fnItemVt70,
                                  m_fnItemVt78;
    std::function<uint64_t(uint64_t)>
        m_fnItemVtB0;
        // item vt+0xb0(0x1040, &owner) ->
        // the owner handle (0 = none)
    std::function<bool(uint64_t)>
        m_fnOwnerRow15Bit3;
        // the owner's row(0x15) bit 3
    // ===== the map / cell grid =====
    std::function<int()> m_fn490Width;
        // FUN_140049490(map)
    std::function<int()> m_fn440Height;
        // FUN_140049440(map)
    std::function<uint64_t(int, int)> m_fnAc70;
        // FUN_14004ac70(map, base, row)
    std::function<uint64_t(uint64_t)>
        m_fn678b0;
        // FUN_1400678b0(cell) - NPC container
    std::function<uint64_t(uint64_t)>
        m_fn678a0;
        // FUN_1400678a0(cell) - user container
    std::function<uint32_t(uint64_t)>
        m_fnContCount;
        // container vt+0x10
    std::function<uint64_t(uint64_t, uint32_t,
        const char*, int)> m_fnContGet;
        // container vt+0x18(cont, i,
        //     npc.cpp literal, line)
    // ===== the finale =====
    std::function<void(const char*)> m_fnShout;
        // theInstance()->get("STR_..._s") +
        // sprintf + FUN_1400586b0(npc, buf, 0)
    std::function<void()> m_fn5b760;
        // FUN_14005b760(npc, 0)
};

// returns 1 if a target was acquired
uint32_t CNpcTargetSearch(
    CNpcTargetSearchData& rD);

// ============================================================
// ===== (unit 32) BIND the real PK-family bodies ==========
// ===== onto this search's seams ==========================
// ============================================================
// Wires m_fn59dc0 / m_fn59710 / m_fn57c50 /
// m_fn5b760 / m_fn5ab20 to the unit-31/32/34
// real bodies (CNpcKeepPkTarget59dc0 /
// CNpcWorldPkGate59710 / CNpcPkDay57c50 /
// CNpcPursuit5b760(npc, 0) / CNpcPkMask5ab20).
// The candidate's flag word for 5ab20 comes from
// THIS data's m_fnItemSubFlags (the same
// +0x10 sub-object vtable+0x20 accessor).
// NOTE: m_fnShout stays a seam - the
// theInstance()->get("STR_..._s") string-table
// lookup is not ported yet (the big integration).
struct CNpcStateData;   // NpcState.h
void CNpcBindPkFamily(
    CNpcTargetSearchData& rD,
    CNpcStateData& rN);

} // namespace npc
