// TitleModule - Player titles (CTitle/CTitleMgr)
// Original: Title.dll (cqserver-78.0.11-1204/modules/title/src/)
// Original DB tables: -
// Decompiled ABI: CModule size 0xc48; RegisterProcess msgs: [1130, 1002, 1003]; SetProcess modes: [14]
#pragma once
#include "Common/IModule.h"

namespace title {

class CTitleModule : public gs::IModule {
public:
    CTitleModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "title"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from Title.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace title
