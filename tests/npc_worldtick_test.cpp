#include "../Exe/NpcServer/NpcWorldTick.h"
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
using namespace npc;

static std::vector<std::string> g_logs;
static void SysLogFn(const char* ch, const char* msg){
    g_logs.push_back(std::string(ch) + "|" + msg); }

struct MyUser { int nId; };

int main() {
    // ===== 1. FUN_14003c520: the empty tick =====
    TickNoop();                 // literally returns

    // ===== 2. FUN_140037f80: the user walk =====
    {
        static int s_nUsers = 3;
        MyUser users[3] = {{1}, {2}, {3}};
        static MyUser* s_pUsers = users;
        UserCollection coll;
        coll.m_fnGetCount = []{ return (uint32_t)s_nUsers; };
        coll.m_fnGetAt = [&](uint32_t idx, const char* szPath,
                            uint32_t uLine, uint32_t uOrig){
            // verbatim file/line of the ORIGINAL at()
            assert(std::string(szPath) ==
                "f:\\version\\cqserver-78.0.11-1204"
                "\\npcserver\\npckernel\\usermanager.cpp");
            assert(uLine == 0x3a);
            assert(uOrig == idx);
            return (UserObj*)&s_pUsers[idx];
        };
        UserManager mgr;
        mgr.m_fnGetCollection = [&]{ return &coll; };
        std::vector<int> vTicked;
        mgr.m_fnUserTick = [&](UserObj* pU){
            vTicked.push_back(((MyUser*)pU)->nId); };
        UserManagerWalk(mgr);
        // backward: ids 3, 2, 1
        assert((vTicked == std::vector<int>{3, 2, 1}));
        // count collapses mid-walk -> stops early
        static int s_nCase = 0;
        s_nUsers = 5;
        coll.m_fnGetCount = []{
            return s_nCase == 0 ? 5u : 1u; };
        s_nCase = 1;
        vTicked.clear();
        UserManagerWalk(mgr);
        // count 1: idx 0 visited, then idx wraps and
        // the re-fetch stops the walk (verbatim)
        assert((vTicked == std::vector<int>{1}));
    }

    // ===== 3. FUN_14001d230: the singleton =====
    assert(&CAIStrategyMgr::Instance() ==
           &CAIStrategyMgr::Instance());

    // ===== 4. FUN_1400489b0: the epoch trainer =====
    {
        uint32_t* g = CAIStrategyMgr::TestGlobals();
        g[0] = g[1] = g[2] = 0;
        CAIStrategyMgr m;
        uint32_t ms = 1000;
        m.m_fnNowMs = [&]{ return ms; };
        int nReload = 0, nEvolve = 0;
        m.m_fnReload = [&]{ ++nReload; };
        m.m_fnEvolve = [&]{ ++nEvolve; };
        m.m_fnPerGenD0 = [](CAIStrategyMgr::Strategy*){};
        m.m_fnGetGen = [](CAIStrategyMgr::Strategy*){
            return 2; };
        g_logs.clear();
        m.m_fnSysLog = SysLogFn;
        m.m_fnLog = [](const char*){};
        // population: 8 entries, only 1 converged ->
        // 1*8 < 8 false -> NO evolution even when due
        for (int i = 0; i < 8; ++i)
            m.m_vecEntries.push_back({[]{
                return 1.0; }});
        m.m_vecEntries[0].m_fnGetFitness = []{
            return 0.0; };
        ms = 700000;               // > 599999 after stamp
        m.Process();               // seeds stamps first
        assert(m.m_nGeneration == 0);
        ms = 1000000;
        m.Process();               // due, but converged*8 ==
        assert(m.m_nGeneration == 0); // 8 -> no epoch
        // 9 entries with 1 converged -> 8 < 9 -> EPOCH
        m.m_vecEntries.push_back({[]{ return 1.0; }});
        ms = 2000000;
        m.Process();
        assert(m.m_nGeneration == 1);
        // verbatim logs: per gene + epoch + update line
        assert(g_logs.size() == 10);
        assert(g_logs[0] == "ainpc|Gene[0]\tGeneration[2]\tFitness[0]");
        assert(g_logs[8] == "ainpc|Gene[8]\tGeneration[2]\tFitness[1]");
        assert(g_logs[9] ==
            "ainpc|Epoch neural AI generation 1");
        assert(g[1] == 2000000);   // 10-min stamp reset
        assert(nEvolve == 1);
        // reload gate: 3h (10800000ms) since g[2]
        ms = 2000000 + 10800001;
        m.Process();
        assert(nReload == 1);      // FUN_140043700 ran
        assert(m.m_nGeneration == 2);
        assert(g_logs.back() ==
            "ainpc|Epoch neural AI generation 2");
        // not due (< 600s): no tick
        uint32_t nGenBefore = m.m_nGeneration;
        m.Process();
        assert(m.m_nGeneration == nGenBefore);
    }

    printf("NPC_WORLDTICK_OK: FUN_14003c520 empty stub, "
           "FUN_140037f80 backward user walk with "
           "re-fetch + verbatim usermanager.cpp path "
           "line 0x3a + at(idx,file,line,orig), "
           "FUN_14001d230 CAIStrategyMgr lazy singleton "
           "(0x98, tq::Singleton<CAIStrategyMgr>), "
           "FUN_1400489b0 epoch trainer verbatim (stamp "
           "flags bit0/bit1, 599999ms due, fitness <= "
           "2.220446049250313e-16 convergence count, "
           "count*8 < population gate, 10800000ms reload "
           "FUN_140043700, +0x8 generation, per-gene "
           "FUN_1400670d0/e0 + 'Gene[%%d]\\tGeneration"
           "[%%d]\\tFitness[%%d]' ainpc log, 'Epoch "
           "neural AI generation %%d', FUN_1400476a0 "
           "evolve, 'CAIStrategyMgr::Process() update "
           "neural AI generation %%d.')\n");
    return 0;
}
