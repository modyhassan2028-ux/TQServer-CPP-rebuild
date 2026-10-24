// CNpcManager::ProcessGenerators (FUN_14002b380) - test
#include "../Exe/NpcServer/NpcManager.h"
#include <cassert>
#include <cstdio>
using namespace npc;

int main() {
    CNpcManager m;
    std::vector<std::string> spawns;

    // 3 generators consuming from the shared budget
    NpcGenerator g1, g2, g3;
    g1.m_fnProcess = [&](uint32_t b){
        spawns.push_back("g1"); return 30; };
    g2.m_fnProcess = [&](uint32_t b){
        spawns.push_back("g2"); return 30; };
    g3.m_fnProcess = [&](uint32_t b){
        spawns.push_back("g3"); return 30; };
    m.m_vecGenSet = {&g1, &g2, &g3};

    // 2 NPCs with AI ticks; guard A blocks the second
    NpcObj n1, n2;
    int nAI = 0;
    n1.m_fnAITick = [&]{ ++nAI; };
    n2.m_fnAITick = [&]{ ++nAI; };
    m.m_mapNpcSet[11] = &n1; m.m_mapNpcSet[22] = &n2;
    m.m_fnGuardA = [](NpcObj* p){ return p->m_bFlag29; };
    n2.m_bFlag29 = true;              // blocked by guard A

    // tick 1: generators run (fresh budget per tick, like
    // the ORIGINAL reading DAT_1401028c0 every call), no AI
    m.ProcessGenerators();
    assert(spawns.size() == 3);
    assert(nAI == 0);
    // ticks 2, 3: same again; tick 3 fires the AI pass
    m.ProcessGenerators(); m.ProcessGenerators();
    assert(spawns.size() == 9);
    assert(nAI == 1);                  // tick 3 (mod 3)

    // budget forces early stop: budget 50, each consumes 30
    m.m_dwBudget = 50; m.m_nTickMod3 = 2;
    m.ProcessGenerators();
    // g1 takes 30 (20 left), g2 takes 20 -> budget 0 -> stop
    assert(spawns.size() == 11);       // g3 not called
    assert(nAI == 2);                 // mod3 wrapped to 0

    // MYASSERT on a null generator slot
    m.m_vecGenSet.push_back(nullptr);
    m.m_dwBudget = 200; m.ProcessGenerators();
    bool bAssert = false;
    for (auto& s : m.m_vecLogs)
        if (s.find("pNpcGenerator") != std::string::npos)
            bAssert = true;
    assert(bAssert);

    // CHECKF when the set pointer is null
    m.m_bGenSetOk = false; m.ProcessGenerators();
    bool bCheck = false;
    for (auto& s : m.m_vecLogs)
        if (s.find("m_pNpcGenSet") != std::string::npos)
            bCheck = true;
    assert(bCheck);

    printf("NPC_MANAGER_OK: budgeted generator walk, 3-tick AI "
           "pass, guards, MYASSERT/CHECKF verbatim logs\n");
    return 0;
}
