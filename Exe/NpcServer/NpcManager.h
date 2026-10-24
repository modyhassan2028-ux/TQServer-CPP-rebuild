// CNpcManager - ORIGINAL f:\version\cqserver-78.0.11-1204\npcserver
// \npckernel\npcmanager.cpp (recovered from CHECKF/MYASSERT
// strings of FUN_14002b380)
#pragma once
#include <stdint.h>
// (unit 44: FUN_140038090 needs the container)
#include "NpcCellObjects.h"
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace npc {

// ORIGINAL error sink (log_InlineLogERROR @ DAT_1400be0b0)
using LogFn = std::function<void(const char*,
                                 const char*)>;

// generator object: vcall +0x80 = Process(budget) ->
// consumed (monster spawns this tick)
struct NpcGenerator {
    std::function<uint32_t(uint32_t)> m_fnProcess;
};

// NPC object: vcall +0xe0 = the AI tick (CTickAnalyst 0x54)
struct NpcObj {
    std::function<void()> m_fnAITick;
    bool m_bFlag29 = false;   // +0x29 tree flag (TBD use)
    // +0x10: the embedded I3DObj interface pointer.
    // FUN_140038010 returns the container hit's
    // BASE + 0x10, and the callers deref the result
    // as an object whose first qword is a vptr
    // (vt+0x38/vt+0x40 = the position getters) -
    // this field models that embedded interface.
    void* m_pIface10 = nullptr;
    // the id (the map key of the ORIGINAL by-id
    // container, vt+0x30(id))
    uint64_t m_uId = 0;
};

// ===== FUN_140038090: the Player/Pet/Other
// id-space counters (usermanager.cpp) - the
// PRIMARY-EVIDENCE id spaces of the server:
//   pets:    id in [0xaae61, 0xaae61+0x1869f)
//            = [700001, 800000)  (0xaae61 = 700001
//            - JUST above the 700000 transform gate!)
//   players: id in [1000000, 1000000+0xee5be5c0)
//   others:  everything else (the monsters)
void CountPlayerPetOther38090(
    TqObjContainer* pCont,
    std::function<uint64_t(uint64_t)> fnItemId,
        // the item's vt+0x8 id getter
    int* pPlayers, int* pPets, int* pOthers);

class CNpcManager {
public:
    // ORIGINAL FUN_14002b380: the generator/NPC tick
    void ProcessGenerators();

    // test seams / state
    std::vector<NpcGenerator*> m_vecGenSet;   // +0x10
    std::map<uint64_t, NpcObj*> m_mapNpcSet;  // +0x8
    // the ORIGINAL live-object by-id container
    // access (the vt+0x30(id) of FUN_140038010's
    // container): 0 when absent
    NpcObj* LookupByIdVt30(uint64_t uId);
    // DAT_1401028c0: global per-tick spawn budget
    uint32_t m_dwBudget = 100;
    // DAT_1401045cc: the every-3rd-tick counter
    uint32_t m_nTickMod3 = 0;
    // CHECKF seam targets (m_pNpcGenSet / m_pNpcSet):
    bool m_bGenSetOk = true, m_bNpcSetOk = true;
    // FUN_140028820 / FUN_140057cf0: NPC AI guards
    std::function<bool(NpcObj*)> m_fnGuardA;
    std::function<bool(NpcObj*)> m_fnGuardB;
    LogFn m_fnLog;
    // observed log lines (for the test)
    std::vector<std::string> m_vecLogs;

private:
    void CheckF(bool bOk, const char* szName,
                const char* szFile, int nLine);
};

} // namespace npc
