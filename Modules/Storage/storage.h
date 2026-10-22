// StorageModule - Warehouse/storage boxes
// Original: Storage.dll (cqserver-78.0.11-1204/modules/storage/src/)
// Original DB tables: cq_depot
// Decompiled ABI: CModule size 0x1060; RegisterProcess msgs: [1009, 1102, 1003, 1002]; SetProcess modes: []
#pragma once
#include "Common/IModule.h"

namespace storage {

class CStorageModule : public gs::IModule {
public:
    CStorageModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "storage"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from Storage.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace storage
