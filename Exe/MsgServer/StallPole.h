#pragma once
// Minimal models of the two subsystems cq_action 207 (FUN_14013c75a)
// reaches for npc record field 4 (type) == 10 and == 46.
//
// ORIGINAL evidence, objdump-verified:
// - type 10 (stall): FUN_140087ed0 = lazy singleton over the root
//   record manager (global getter [0x1406d8df0]) -> vcall+0x20(0x16)
//   (record class 0x16, cached at 0x140975c50; null -> CHECKF 0x3ef),
//   then mgr vcall+0x328(npcId) -> bool. The stall subsystem itself
//   (opening/owning stalls) is not ported; this registry is where it
//   will register stall npcs, and 207 removes them by npc id.
// - type 46 (pole): root mgr [0x1406d8df0] again; gate =
//   FUN_14008b330([mapgroup+0x77c] byte). Gate true ->
//   vcall+0x20(0x25) (class 0x25) -> rec vcall+0x78(npcId) -> bool;
//   gate false -> vcall+0x20(0x1c) (class 0x1c) -> rec
//   vcall+0x40(npcId) -> bool. Record null -> false (0x14013c8b9).
//   The two record classes are modeled as two id registries; which
//   one answers depends on the pole-mode gate.
#include <cstdint>
#include <unordered_set>

class CStallManager {
public:
    static CStallManager& Instance();

    // stall subsystem / tests register the dyna stall npcs here
    void RegisterStall(uint32_t dwNpcId) { m_stallIds.insert(dwNpcId); }
    bool HasStall(uint32_t dwNpcId) const { return m_stallIds.count(dwNpcId) != 0; }
    // mgr vcall+0x328: remove the stall npc by id, true when it existed
    bool RemoveStall(uint32_t dwNpcId) { return m_stallIds.erase(dwNpcId) != 0; }

private:
    std::unordered_set<uint32_t> m_stallIds;
};

class CPoleManager {
public:
    static CPoleManager& Instance();

    // [mapgroup+0x77c] byte (FUN_14008b330): which record class answers
    void SetPoleMode(bool bOn) { m_bPoleMode = bOn; }
    bool GetPoleMode() const { return m_bPoleMode; }

    // pole subsystem / tests register pole npcs; mode true -> the
    // class-0x25 registry (vcall+0x78), false -> class-0x1c (+0x40)
    void RegisterPole(uint32_t dwNpcId, bool bPoleMode) {
        if (bPoleMode) m_poleModeIds.insert(dwNpcId);
        else           m_normalIds.insert(dwNpcId);
    }
    bool HasPole(uint32_t dwNpcId, bool bPoleMode) const {
        const auto& r = bPoleMode ? m_poleModeIds : m_normalIds;
        return r.count(dwNpcId) != 0;
    }
    // record class 0x25 vcall+0x78 / class 0x1c vcall+0x40: remove by
    // npc id through the class the gate selects, true when it existed
    bool RemovePole(uint32_t dwNpcId) {
        if (m_bPoleMode) return m_poleModeIds.erase(dwNpcId) != 0;
        return m_normalIds.erase(dwNpcId) != 0;
    }

private:
    bool m_bPoleMode{false};          // [mapgroup+0x77c]
    std::unordered_set<uint32_t> m_poleModeIds; // class 0x25
    std::unordered_set<uint32_t> m_normalIds;   // class 0x1c
};
