// TrainingModule - Training/vitality (CTrainingVitalityMgr)
// Original: Training.dll (cqserver-78.0.11-1204/modules/training/src/)
// Original DB tables: cq_user
// Decompiled ABI: CModule size 0xc48; RegisterProcess msgs: [2044, 1002, 1003]; SetProcess modes: [15]
#pragma once
#include "Common/IModule.h"

namespace training {

class CTrainingModule : public gs::IModule {
public:
    CTrainingModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "training"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from Training.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace training
