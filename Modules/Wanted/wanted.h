// WantedModule - Bounty board (players post rewards)
// Original: Wanted.dll (cqserver-78.0.11-1204/modules/wanted/src/)
// Original DB tables: cq_wanted
// Decompiled ABI: CModule size 0x440; RegisterProcess msgs: [1015]; SetProcess modes: [31]
#pragma once
#include "Common/IModule.h"

namespace wanted {

class CWantedModule : public gs::IModule {
public:
    CWantedModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "wanted"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from Wanted.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace wanted
