// ClanPkArenicModule - Clan (guild) PK arena
// Original: ClanPKArenic.dll (cqserver-78.0.11-1204/modules/clan_pk_arenic/src/)
// Original DB tables: cq_arenic*
// Decompiled ABI: CModule size 0x30; RegisterProcess msgs: [1003, 1002, 2230, 2211, 2240, 2232, 2233]; SetProcess modes: [33]
#pragma once
#include "Common/IModule.h"

namespace clan_pk_arenic {

class CClanPkArenicModule : public gs::IModule {
public:
    CClanPkArenicModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "clan_pk_arenic"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from ClanPKArenic.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace clan_pk_arenic
