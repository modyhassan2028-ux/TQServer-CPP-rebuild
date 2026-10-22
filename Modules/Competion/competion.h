// CompetionModule - Weekly competition ranking rewards
// Original: Competion.dll (cqserver-78.0.11-1204/modules/competion/src/)
// Original DB tables: cq_syncompeterank, cq_competesponsor
// Decompiled ABI: CModule size 0xc60; RegisterProcess msgs: [2068, 1003, 1002]; SetProcess modes: [5]
#pragma once
#include "Common/IModule.h"

namespace competion {

class CCompetionModule : public gs::IModule {
public:
    CCompetionModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "competion"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from Competion.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace competion
