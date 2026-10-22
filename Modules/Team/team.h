// TeamModule - Party/team system
// Original: Team.dll (cqserver-78.0.11-1204/modules/team/src/)
// Original DB tables: -
// Decompiled ABI: CModule size 0xc50; RegisterProcess msgs: [1002, 1003, 1023, 2045, 1023, 2045]; SetProcess modes: [30]
#pragma once
#include "Common/IModule.h"

namespace team {

class CTeamModule : public gs::IModule {
public:
    CTeamModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "team"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from Team.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace team
