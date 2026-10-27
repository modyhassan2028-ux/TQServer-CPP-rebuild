// ElitePkArenicModule - Elite PK tournament arena
// Original: ElitePKArenic.dll (cqserver-78.0.11-1204/modules/elite_pk_arenic/src/)
// Original DB tables: cq_arenic*
// Decompiled ABI: CModule size 0x1478; RegisterProcess msgs: [2223, 2219, 2211, 1002, 2239]; SetProcess modes: [25]
#pragma once
#include "Common/IModule.h"

namespace elitepkarenic {

class CElitePkArenicModule : public gs::IModule {
public:
    CElitePkArenicModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "elite_pk_arenic"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from ElitePKArenic.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace elitepkarenic
