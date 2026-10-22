// CrossFlagWarModule - Cross-server flag war event
// Original: CrossFlagWar.dll (cqserver-78.0.11-1204/modules/cross_flag_war/src/)
// Original DB tables: cq_flag_war, cq_flag_war_user
// Decompiled ABI: CModule size 0x1060; RegisterProcess msgs: [2502, 2506, 2504, 2507]; SetProcess modes: []
#pragma once
#include "Common/IModule.h"

namespace cross_flag_war {

class CCrossFlagWarModule : public gs::IModule {
public:
    CCrossFlagWarModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "cross_flag_war"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from CrossFlagWar.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace cross_flag_war
