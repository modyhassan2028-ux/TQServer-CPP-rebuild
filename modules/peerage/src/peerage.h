// PeerageModule - Nobility/peerage (knight/baron donations)
// Original: Peerage.dll (cqserver-78.0.11-1204/modules/peerage/src/)
// Original DB tables: cq_user.nobility
// Decompiled ABI: CModule size 0x858; RegisterProcess msgs: [2064, 1002]; SetProcess modes: []
#pragma once
#include "Common/IModule.h"

namespace peerage {

class CPeerageModule : public gs::IModule {
public:
    CPeerageModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "peerage"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from Peerage.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace peerage
