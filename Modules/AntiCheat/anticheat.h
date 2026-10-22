// AnticheatModule - Speed/fly/attack-rate cheat detection and kicks
// Original: AntiCheat.dll (cqserver-78.0.11-1204/modules/anticheat/src/)
// Original DB tables: -
// Decompiled ABI: CModule size 0x30; RegisterProcess msgs: [1003, 10010, 1022, 2521, 1003, 10010, 1022, 2521]; SetProcess modes: []
#pragma once
#include "Common/IModule.h"

namespace anticheat {

class CAnticheatModule : public gs::IModule {
public:
    CAnticheatModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "anticheat"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from AntiCheat.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace anticheat
