// FamilyArenicModule - Family PK arena
// Original: FamilyArenic.dll (cqserver-78.0.11-1204/modules/family_arenic/src/)
// Original DB tables: cq_arenic*
// Decompiled ABI: CModule size 0x28; RegisterProcess msgs: [2216, 2215, 2214, 2213, 2212, 2211, 1003, 1002]; SetProcess modes: []
#pragma once
#include "Common/IModule.h"

namespace family_arenic {

class CFamilyArenicModule : public gs::IModule {
public:
    CFamilyArenicModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "family_arenic"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from FamilyArenic.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace family_arenic
