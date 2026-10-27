// StatusModule - Buff/status effects (types + timeouts)
// Original: Status.dll (cqserver-78.0.11-1204/modules/status/src/)
// Original DB tables: cq_status, cq_status_timeout, cq_statustype
// Decompiled ABI: CModule size 0x840; RegisterProcess msgs: [1002, 2070]; SetProcess modes: [20]
#pragma once
#include "Common/IModule.h"

namespace status {

class CStatusModule : public gs::IModule {
public:
    CStatusModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "status"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from Status.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace status
