// DetainEquipModule - Detained equipment (jail item holding)
// Original: DetainEquip.dll (cqserver-78.0.11-1204/modules/detain_equip/src/)
// Original DB tables: cq_itemstatus, cq_itemstatus_timeout
// Decompiled ABI: CModule size 0x860; RegisterProcess msgs: [1009, 10010]; SetProcess modes: [19]
#pragma once
#include "Common/IModule.h"

namespace detainequip {

class CDetainEquipModule : public gs::IModule {
public:
    CDetainEquipModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "detain_equip"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from DetainEquip.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace detainequip
