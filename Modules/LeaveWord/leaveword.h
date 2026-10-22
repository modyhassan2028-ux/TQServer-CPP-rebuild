// LeavewordModule - Offline messages left for players
// Original: LeaveWord.dll (cqserver-78.0.11-1204/modules/leaveword/src/)
// Original DB tables: cq_leaveword, cq_sys_leaveword
// Decompiled ABI: CModule size 0x850; RegisterProcess msgs: [2170, 1002, 1003]; SetProcess modes: [29]
#pragma once
#include "Common/IModule.h"

namespace leaveword {

class CLeavewordModule : public gs::IModule {
public:
    CLeavewordModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "leaveword"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from LeaveWord.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace leaveword
