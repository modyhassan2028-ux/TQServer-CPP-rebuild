// FactionMatchModule - Faction matching battles (CGameAction::ProcessActionFactionMatch)
// Original: FactionMatch.dll (cqserver-78.0.11-1204/modules/faction_match/src/)
// Original DB tables: cq_fate_*
// Decompiled ABI: CModule size 0x30; RegisterProcess msgs: [2330, 2333, 1003]; SetProcess modes: [24]
#pragma once
#include "Common/IModule.h"

namespace factionmatch {

class CFactionMatchModule : public gs::IModule {
public:
    CFactionMatchModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "faction_match"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from FactionMatch.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace factionmatch
