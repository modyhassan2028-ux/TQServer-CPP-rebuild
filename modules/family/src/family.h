// FamilyModule - Family system (create/level/attr/battle shares)
// Original: Family.dll (cqserver-78.0.11-1204/modules/family/src/)
// Original DB tables: family, family_attr, family_battle_effect_share_limit
// Decompiled ABI: CModule size 0xc68; RegisterProcess msgs: [1312, 1313, 1002, 1003]; SetProcess modes: [8]
#pragma once
#include "Common/IModule.h"

namespace family {

class CFamilyModule : public gs::IModule {
public:
    CFamilyModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "family"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from Family.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace family
