// RelationModule - Friends/enemies lists (add/delete/notify)
// Original: Relation.dll (cqserver-78.0.11-1204/modules/relation/src/)
// Original DB tables: cq_friend, cq_friend_timeout, cq_enemy, cq_enemy_timeout
// Decompiled ABI: CModule size 0x1880; RegisterProcess msgs: [1002, 1003, 2046, 1019, 1041, 2033, 2047]; SetProcess modes: [32]
#pragma once
#include "Common/IModule.h"

namespace relation {

class CRelationModule : public gs::IModule {
public:
    CRelationModule(gs::IWorldKernel* pKernel, uint32_t dwModuleIndex)
        : m_pKernel(pKernel), m_dwModuleIndex(dwModuleIndex) {}

    bool Initialize() override { return true; }
    void Shutdown() override {}
    void OnProcess() override {}
    const char* GetModuleName() const override { return "relation"; }

    gs::IWorldKernel* GetKernel() const { return m_pKernel; }
    uint32_t GetModuleIndex() const { return m_dwModuleIndex; }
    void* GetProcessor() { return &m_oProcessor; }

private:
    gs::IWorldKernel* m_pKernel;
    uint32_t m_dwModuleIndex;
    // TODO(port): the module's CMsgProcess dispatcher (operator_new(0x18) in the
    // original init) - port from Relation.dll.decompiled.c
    unsigned char m_oProcessor[3 * sizeof(void*)]{};
};

} // namespace relation
