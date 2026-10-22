// CrossStatusModule - Cross-server status/buff sync channel
// Original: CrossStatus.dll (cqserver-78.0.11-1204/modules/cross_status/src/)
// Original DB tables: cq_cross_merit
// Decompiled ABI: CModule size 0x18; RegisterProcess msgs: []; SetProcess modes: [1000]
#pragma once
#include "Common/IModule.h"

namespace crossstatus {

class CCrossStatusModule : public gs::IModule {
public:
    CCrossStatusModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "cross_status"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from CrossStatus.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace crossstatus
