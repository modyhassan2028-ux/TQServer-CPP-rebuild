// TaskDetailModule - Quest log details/progress UI
// Original: TaskDetail.dll (cqserver-78.0.11-1204/modules/task_detail/src/)
// Original DB tables: cq_task
// Decompiled ABI: CModule size 0x1468; RegisterProcess msgs: [1134, 1002, 1003, 1135, 3000]; SetProcess modes: [13]
#pragma once
#include "Common/IModule.h"

namespace taskdetail {

class CTaskDetailModule : public gs::IModule {
public:
    CTaskDetailModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "task_detail"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from TaskDetail.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace taskdetail
