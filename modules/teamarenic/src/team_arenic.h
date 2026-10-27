// TeamArenicModule - Team PK arena battles
// Original: TeamArenic.dll (cqserver-78.0.11-1204/modules/team_arenic/src/)
// Original DB tables: cq_arenic*
// Decompiled ABI: CModule size 0x30; RegisterProcess msgs: [2245, 2244, 2243, 2242, 2241, 2211, 2247, 1003, 1002]; SetProcess modes: [34]
#pragma once
#include "Common/IModule.h"

namespace team_arenic {

class CTeamArenicModule : public gs::IModule {
public:
    CTeamArenicModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "team_arenic"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from TeamArenic.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace team_arenic
