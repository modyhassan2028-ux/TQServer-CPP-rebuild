// TotemModule - Clan totem poles (attributes)
// Original: Totem.dll (cqserver-78.0.11-1204/modules/totem/src/)
// Original DB tables: cq_totem_add
// Decompiled ABI: CModule size 0xc50; RegisterProcess msgs: [2203, 2202, 2204]; SetProcess modes: [21]
#pragma once
#include "Common/IModule.h"

namespace totem {

class CTotemModule : public gs::IModule {
public:
    CTotemModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "totem"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from Totem.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace totem
