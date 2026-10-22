// RankModule - Dynamic rank ladders
// Original: Rank.dll (cqserver-78.0.11-1204/modules/rank/src/)
// Original DB tables: cq_dyna_rank_rec, cq_dyna_rank_type, dyna_rank_rec, dyna_rank_type, cq_fate_rank
// Decompiled ABI: CModule size 0x838; RegisterProcess msgs: [1151, 1002]; SetProcess modes: [17]
#pragma once
#include "Common/IModule.h"

namespace rank {

class CRankModule : public gs::IModule {
public:
    CRankModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "rank"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from Rank.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace rank
