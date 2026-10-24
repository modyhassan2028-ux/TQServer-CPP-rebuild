#include "NpcManager.h"

namespace npc {

// ORIGINAL log_InlineLogERROR(&DAT_1400be0b0, "CHECKF",
//   name, npcmanager.cpp, line)
void CNpcManager::CheckF(bool bOk, const char* szName,
                        const char* szFile, int nLine) {
    if (bOk) return;
    char buf[256];
    std::snprintf(buf, sizeof buf,
                  "log_InlineLogERROR CHECKF %s %s %d",
                  szName, szFile, nLine);
    m_vecLogs.push_back(buf);
    if (m_fnLog) m_fnLog("CHECKF", szName);
}

// ===== ORIGINAL FUN_14002b380 =====
// CNpcManager::ProcessGenerators (npcmanager.cpp):
//  1. walk m_pNpcGenSet (@+0x10): for each generator
//     (MYASSERT pNpcGenerator @0x16b if the GetAt @0x16a
//     returns null), CTickAnalyst(0x52): consumed =
//     gen->vcall+0x80(budget); budget -= consumed, while
//     budget >= 1. CHECKF(m_pNpcGenSet) @0x1a1.
//  2. DAT_1401045cc++; every 3rd call: walk m_pNpcSet (@+8)
//     (CHECKF @0x1d4), find each by key (FUN_140025c40 ->
//     vcall+0x20), skip if FUN_140028820 or FUN_140057cf0
//     return true, else CTickAnalyst(0x54): npc->vcall+0xe0.
//     The ORIGINAL walks a node tree via the +0x29 flag
//     (partially recovered) - the rebuild iterates the map.
void CNpcManager::ProcessGenerators() {
    uint32_t dwBudget = m_dwBudget;   // DAT_1401028c0
    for (uint32_t i = 0;; ++i) {
        CheckF(m_bGenSetOk, "m_pNpcGenSet",
               "f:\\version\\cqserver-78.0.11-1204\\npcserver"
               "\\npckernel\\npcmanager.cpp", 0x1a1);
        if (i >= m_vecGenSet.size() || dwBudget < 1) break;
        NpcGenerator* pGen = m_vecGenSet[i];
        if (!pGen) {
            // MYASSERT("pNpcGenerator") @0x16b
            m_vecLogs.push_back(
                "log_InlineLogERROR MYASSERT pNpcGenerator "
                "npcmanager.cpp 0x16b");
            if (m_fnLog) m_fnLog("MYASSERT", "pNpcGenerator");
            continue;
        }
        uint32_t nUsed = pGen->m_fnProcess
            ? pGen->m_fnProcess(dwBudget) : 0;
        dwBudget -= nUsed <= dwBudget ? nUsed : dwBudget;
    }
    // every 3rd tick: the NPC AI pass
    m_nTickMod3 = (m_nTickMod3 + 1) % 3; // DAT_1401045cc
    if (m_nTickMod3 == 0) {
        CheckF(m_bNpcSetOk, "m_pNpcSet",
               "f:\\version\\cqserver-78.0.11-1204\\npcserver"
               "\\npckernel\\npcmanager.cpp", 0x1d4);
        for (auto& kv : m_mapNpcSet) {
            NpcObj* pNpc = kv.second;
            if (!pNpc) continue;
            // ORIGINAL: skip if either guard returns true
            if (m_fnGuardA && m_fnGuardA(pNpc)) continue;
            if (m_fnGuardB && m_fnGuardB(pNpc)) continue;
            if (pNpc->m_fnAITick) pNpc->m_fnAITick();
        }
    }
}

} // namespace npc
