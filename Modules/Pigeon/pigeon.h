// PigeonModule - In-game mail system (carrier pigeon)
// Original: Pigeon.dll (cqserver-78.0.11-1204/modules/pigeon/src/)
// Original DB tables: cq_mail, cq_operating_mail_record
// Decompiled ABI: CModule size 0x850; RegisterProcess msgs: [2050, 1002]; SetProcess modes: []
#pragma once
#include "Common/IModule.h"

namespace pigeon {

class CPigeonModule : public gs::IModule {
public:
    CPigeonModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "pigeon"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from Pigeon.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace pigeon
