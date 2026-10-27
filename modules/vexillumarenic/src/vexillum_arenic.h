// VexillumArenicModule - Vexillum (cross-server banner) war arena
// Original: VexillumArenic.dll (cqserver-78.0.11-1204/modules/vexillum_arenic/src/)
// Original DB tables: cq_cross_vexillum
// Decompiled ABI: CModule size 0x848; RegisterProcess msgs: [2224, 1063]; SetProcess modes: [28]
#pragma once
#include "Common/IModule.h"

namespace vexillumarenic {

class CVexillumArenicModule : public gs::IModule {
public:
    CVexillumArenicModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "vexillum_arenic"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from VexillumArenic.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace vexillumarenic
