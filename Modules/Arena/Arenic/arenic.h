// ArenicModule - Solo PK arena: signup, honor, bonus
// Original: Arenic.dll (cqserver-78.0.11-1204/modules/arenic/src/)
// Original DB tables: cq_arenic, cq_arenic_bonus, cq_arenic_honor
// Decompiled ABI: CModule size 0x28; RegisterProcess msgs: [2209, 2208, 2207, 2206, 2205, 2211, 1003, 1002]; SetProcess modes: [4]
#pragma once
#include "Common/IModule.h"

namespace arenic {

class CArenicModule : public gs::IModule {
public:
    CArenicModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "arenic"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from Arenic.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace arenic
