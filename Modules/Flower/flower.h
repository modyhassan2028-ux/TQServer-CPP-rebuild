// FlowerModule - Flower gifting/ranking system
// Original: Flower.dll (cqserver-78.0.11-1204/modules/flower/src/)
// Original DB tables: flower
// Decompiled ABI: CModule size 0x848; RegisterProcess msgs: [1150, 1002, 1003]; SetProcess modes: [9]
#pragma once
#include "Common/IModule.h"

namespace flower {

class CFlowerModule : public gs::IModule {
public:
    CFlowerModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "flower"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from Flower.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace flower
