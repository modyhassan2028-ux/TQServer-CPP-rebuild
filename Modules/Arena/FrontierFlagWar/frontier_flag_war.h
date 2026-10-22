// FrontierFlagWarModule - Frontier (border) flag war
// Original: FrontierFlagWar.dll (cqserver-78.0.11-1204/modules/frontier_flag_war/src/)
// Original DB tables: cq_flag_war*
// Decompiled ABI: CModule size 0x1068; RegisterProcess msgs: [2502, 2506, 2504, 2507]; SetProcess modes: [37] (module index)
#pragma once
#include "Common/IModule.h"

namespace frontier_flag_war {

class CFrontierFlagWarModule : public gs::IModule {
public:
    CFrontierFlagWarModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "frontier_flag_war"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from FrontierFlagWar.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace frontier_flag_war
