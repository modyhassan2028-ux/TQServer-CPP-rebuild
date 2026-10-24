// CNpcGenerator::CreateNpc (FUN_140061040) - test
#include "../Exe/NpcServer/NpcGenerator.h"
#include <cassert>
#include <cstdio>
#include <string>
#include <vector>
using namespace npc;

int main() {
    CNpcGenerator g;
    std::vector<std::string> logs;
    g.m_fnLog = [&](const char* s){ logs.push_back(s); };
    g.m_fnRand = [](int n){ return n - 1; };  // deterministic
    g.m_fnTime = []{ return 5000; };          // sec 5
    int nDummy = 0;
    g.m_fnGroupFilter = [&](GenConfig*, TypeRecord*,
                             int64_t){ ++nDummy; return true; };
    // config table: idx -> value
    int vals[0x13] = {}; vals[1] = 1111;
    vals[4] = 100; vals[5] = 100; vals[6] = 10;
    vals[7] = 50; vals[8] = 1;
    vals[0xf] = 0x2a; vals[0x10] = 0x1;
    vals[0x12] = 0;                          // fixed mode
    g.m_cfg.m_fnGetInt = [&](int i){ return vals[i]; };
    g.m_fnCurrentGenId = []{ return 700; };
    g.m_fnRandomGenId = []{ return 800; };
    g.m_fnFindMap = [&](uint32_t t)->void*{
        return t == 1111 ? (void*)0x1234 : nullptr; };
    int nTail = 0;             // 0x11 = 0: no cluster
    TypeRecord rec; rec.m_fnGetGroup = []{ return 42; };

    // fixed mode: map from lookup, type from config 1
    assert(g.CreateNpc(&rec, 0));
    assert(g.m_dwGenId == 700 && g.m_dwMapId == 1111);
    // X = 50 + RandGet(50) = 50 + 49
    assert(g.m_nTimerSec30 == 99);
    assert(g.m_dwBornSec == 5);
    // step = (100/10) * (100/10) = 100
    assert(g.m_nMaxCap == 100);
    assert(g.m_dwFieldF == 0x2a && g.m_byField10 == 0x1);
    assert(g.m_pCluster == nullptr && logs.empty());

    // random mode (0x12 bit0): type from param, map random
    vals[0x12] = 1; vals[1] = 2222;
    g.m_fnFindMap = [](uint32_t){ return (void*)0x5678; };
    assert(g.CreateNpc(&rec, 3333));
    assert(g.m_dwMapId == 3333 && g.m_dwGenId == 800);
    // random mode, param 0 -> fail
    assert(!g.CreateNpc(&rec, 0));

    // group filter reject -> fail, no fields touched
    g.m_fnGroupFilter = [](GenConfig*, TypeRecord*, int64_t){
        return false; };
    assert(!g.CreateNpc(&rec, 1));
    assert(logs.empty());

    // map not found: Close + verbatim error - the
    // ORIGINAL arg order is [vtable+8 = +0x50 gen id]
    // then [+0x54 map id]
    g.m_fnGroupFilter = [](GenConfig*, TypeRecord*, int64_t){
        return true; };
    vals[0x12] = 0; vals[1] = 5555;
    g.m_fnFindMap = [](uint32_t){ return nullptr; };
    assert(!g.CreateNpc(&rec, 0));
    assert(g.m_bClosed);
    assert(logs.size() == 1 &&
           logs[0].find("Error: npc generator [700] got "
                        "invalid map [5555]!") ==
           std::string::npos ? false : true);
    // step input 0 -> step 0
    vals[8] = 0;
    g.m_fnFindMap = [](uint32_t){ return (void*)1; };
    assert(g.CreateNpc(&rec, 0));
    assert(g.m_nMaxCap == 0);

    // ---- LoadCluster (FUN_140060e60) ----
    CNpcGenerator c;
    int cvals[0x13] = {}; cvals[9] = 77; cvals[0x11] = 0;
    c.m_cfg.m_fnGetInt = [&](int i){ return cvals[i]; };
    c.m_fnTime = []{ return 0; };
    c.m_fnRand = [](int){ return 0; };
    c.m_fnCurrentGenId = []{ return 1; };
    c.m_fnFindMap = [](uint32_t){ return (void*)1; };
    // flag 0x11 == 0 -> immediate true, no query
    assert(c.LoadCluster() && c.m_pCluster == nullptr);
    cvals[0x11] = 1;
    int nQ = 0, nFree = 0; bool bRow = false;
    c.m_fnQuery = [&](const char* sql, int, int id){
        ++nQ;
        // the formatted ORIGINAL: %s = the cluster table
        // (name TBD), %d = GetInt(9) = 77; the 0x40 buffer
        // truncates the placeholder tail, so assert the
        // surviving prefix
        assert(std::string(sql).find(
            "SELECT * FROM <szMonsterClusterTable") ==
            0);
        assert(std::string(sql).find("WHERE id = 77") !=
            std::string::npos);
        DbResult* r = new DbResult();
        r->nRows = bRow ? 1 : 0;
        return r; };
    // rows 0 -> fail, log 0x1ea, cluster freed
    assert(!c.LoadCluster());
    assert(nQ == 1 && c.m_pCluster == nullptr);
    assert(c.m_vecErrLogs.size() == 1 &&
           c.m_vecErrLogs[0].find("0x1ea") != std::string::npos);
    // rows > 0 -> LoadRow (the class' fixed vtable loader)
    bRow = true; nQ = 0; c.m_vecErrLogs.clear();
    int nRow = 0;
    c.m_fnClusterLoadRow = [&](DbResult*){ ++nRow;
        return true; };
    assert(c.LoadCluster() && nQ == 1 && nRow == 1);
    assert(c.LoadCluster() && nRow == 2);
    // query null -> log 0x1e2
    c.m_fnQuery = [](const char*, int, int){
        return (DbResult*)nullptr; };
    assert(!c.LoadCluster());
    assert(c.m_vecErrLogs.size() == 1 &&
           c.m_vecErrLogs[0].find("0x1e2") != std::string::npos);

    printf("NPC_GENERATOR_OK: fixed/random modes, group "
           "filter, geo step, rand X, born sec, invalid-map "
           "verbatim log\n");  // + cluster load flows
    return 0;
}
