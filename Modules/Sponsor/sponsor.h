// SponsorModule - Event sponsorship (NPC sponsorships)
// Original: Sponsor.dll (cqserver-78.0.11-1204/modules/sponsor/src/)
// Original DB tables: cq_sponsor, cq_competesponsor
// Decompiled ABI: CModule size 0x840; RegisterProcess msgs: [1064, 1065]; SetProcess modes: [26]
#pragma once
#include "Common/IModule.h"

namespace sponsor {

class CSponsorModule : public gs::IModule {
public:
    CSponsorModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "sponsor"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from Sponsor.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace sponsor
