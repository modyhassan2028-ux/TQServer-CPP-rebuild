// BoothModule - Player market stalls (booth selling)
// Original: Booth.dll (cqserver-78.0.11-1204/modules/booth/src/)
// Original DB tables: -
// Decompiled ABI: CModule size 0x30; RegisterProcess msgs: [10010]; SetProcess modes: [27]
#pragma once
#include "Common/IModule.h"

namespace booth {

class CBoothModule : public gs::IModule {
public:
    CBoothModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "booth"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from Booth.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace booth
