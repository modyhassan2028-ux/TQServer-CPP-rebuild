// CNpcGenerator::Generator (FUN_14005fc90) + ClusterType
// (FUN_14005f7e0) + restock (FUN_14005fb30) - unit 12
#include "../npcserver/NpcGenerator.h"
#include "../npcserver/MsgAiNpcInfo.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>
using namespace npc;

struct Fix {
    CNpcGenerator g;
    std::vector<AiNpcInfoRecord> sent;
    bool bCellOk = true, bPosValid = false;
    uint32_t idSeq = 0x61a81;
    int rand100 = 0;

    void Wire() {
        memset(&g.m_cfg, 0, sizeof g.m_cfg);
        g.m_cfg.m_fnGetInt = [this](int idx){
            return idx == 2 ? 500 : idx == 3 ? 300
                 : idx == 4 ? 40  : idx == 5 ? 30
                 : idx == 9 ? 7777 : idx == 0xc ? 0
                 : idx == 0xd ? 909 : idx == 8 ? 1
                 : idx == 0xf ? 0 : 0; };
        g.m_fnRand = [this](int n){
            return n == 100 ? rand100 : n / 2; };
        g.m_fnTime = []{ return 0u; };
        g.m_pMap = (void*)0x55;         // +0x28
        g.m_dwFieldF = 0;               // +0x48 = 0
        g.m_nRest14 = 5;                // +0x14
        g.m_fnCellOk = [this](void*, int, int){
            return bCellOk; };
        g.m_fnPosValid = [this](void*, int, int){
            return bPosValid; };
        g.m_fnSpawnNewNpcId = [this]{
            return ++idSeq; };
        g.m_fnGetMapId = []{ return 1002u; };
        g.m_fnGetId = []{ return 42u; };
        g.m_fnBuildSpawnMsg =
            [this](const AiNpcInfoRecord& r){
                sent.push_back(r); return true; };
        g.m_fnSendMsg = [](const AiNpcInfoRecord&){};
    }
};

int main() {
    // ===== gates =====
    { Fix f; f.Wire(); f.g.m_pMap = nullptr;
      assert(f.g.Generator(100) == 0); }
    { Fix f; f.Wire(); f.g.m_dwFieldF = 3;   // +0x48 != 0
      assert(f.g.Generator(100) == 0); }
    { Fix f; f.Wire(); assert(f.g.Generator(0) == 0);
      assert(f.sent.empty()); }

    // ===== random-mode spawn + record layout =====
    { Fix f; f.Wire();
      uint32_t n = f.g.Generator(100);
      assert(n == 5);                    // rest 5, budget 100
      assert(f.sent.size() == 5);
      const AiNpcInfoRecord& r = f.sent[0];
      assert(r.dw[0] == 0x61a82);        // SpawnNewNpcID
      assert(r.dw[1] == 1002);           // vcall+0x40
      assert(r.dw[2] == 42);             // vtable+8
      assert(r.dw[3] == 0 && r.dw[4] == 0);
      assert(r.w(0x14) == 520);          // 500+RandGet(40)
      assert(r.w(0x16) == 315);          // 300+RandGet(30)
      assert(r.w(0x18) == 1);            // THE TAG
      assert(r.w(0x1a) == 7777);         // GetInt(9) type
      assert(r.b(0x2c) == 0);
      // counters: +0x14 drained, +0x18/+0x20 up
      assert(f.g.m_nRest14 == 0);
      assert(f.g.m_nGenAmount18 == 5);
      assert(f.g.m_nMonsters20 == 5); }

    // ===== budget cap stops the loop =====
    { Fix f; f.Wire(); f.g.m_nRest14 = 5;
      assert(f.g.Generator(2) == 2);
      assert(f.g.m_nRest14 == 3); }

    // ===== fixed mode (GetInt(0xc) >= 1) =====
    { Fix f; f.Wire();
      f.g.m_cfg.m_fnGetInt = [&f](int idx){
          return idx == 0xc ? 0xabcd
               : idx == 0xd ? 909
               : idx == 4 ? 40 : idx == 5 ? 30
               : idx == 9 ? 7777 : 0; };
      f.g.m_nRest14 = 1;
      assert(f.g.Generator(100) == 1);
      assert(f.sent[0].w(0x14) == 0xabcd);
      assert(f.sent[0].w(0x16) == 909); }

    // ===== probe exhaustion + idle DB log =====
    { Fix f; f.Wire();
      f.bCellOk = false; f.bPosValid = false;
      f.g.m_nRest14 = 1;
      // the throttle gate needs TimeGet - +0x24 > 999
      uint32_t ms = 5000;
      f.g.m_fnTime = [&]{ return ms; };
      // attempts = max(1, 30*40) > 8
      assert(f.g.Generator(100) == 0);
      assert(f.g.m_vecDbErrLogs.size() == 1);
      // GBK literal "cq_generator.id=%u，出生点不可站"
      assert(f.g.m_vecDbErrLogs[0].find(
                 "cq_generator.id=%u") == 0);
      assert(f.g.m_vecDbErrLogs[0].find(
                 "\xb2\xbb\xbf\xc9\xd5\xbe") !=
             std::string::npos); }

    // ===== idle log suppressed by bPosValid =====
    { Fix f; f.Wire();
      f.bCellOk = false; f.bPosValid = true;
      f.g.m_nRest14 = 1;
      assert(f.g.Generator(100) == 0);
      assert(f.g.m_vecDbErrLogs.empty()); }

    // ===== idle log throttled (999ms window) =====
    { Fix f; f.Wire();
      f.bCellOk = false; f.bPosValid = false;
      f.g.m_nRest14 = 1;
      uint32_t ms = 5000;
      f.g.m_fnTime = [&]{ return ms; };
      assert(f.g.Generator(100) == 0);      // logged @5000
      assert(f.g.m_vecDbErrLogs.size() == 1);
      ms = 5900;
      assert(f.g.Generator(100) == 0);      // inside window
      assert(f.g.m_vecDbErrLogs.size() == 1);
      ms = 6000;
      assert(f.g.Generator(100) == 0);      // >999ms
      assert(f.g.m_vecDbErrLogs.size() == 2);
      assert(f.g.m_dwLastLogMs24 == 6000); }

    // ===== ClusterType (FUN_14005f7e0) =====
    { Fix f; f.Wire();
      f.g.m_pCluster = (CGameDataCluster*)0x99;
      f.g.m_fnClusterVal = [](uint32_t idx){
          // weights at 2,4 / types at 1,3 (FUN_14005f7e0:
          // type col = idx*2 + 1, first idx = 0 -> col 1)
          return idx == 2 ? 30 : idx == 4 ? 40
               : idx == 1 ? 111 : idx == 3 ? 222 : 0; };
      f.rand100 = 10;                  // 10 < 30 -> idx 0
      assert(f.g.ClusterType() == 111);
      f.rand100 = 50;                  // 30 <= 50 < 70
      assert(f.g.ClusterType() == 222);
      f.rand100 = 99;                  // sum 70 < 99
      assert(f.g.ClusterType() == 0); }
    { Fix f; f.Wire();
      f.g.m_pCluster = nullptr;
      assert(f.g.ClusterType() == 0);
      assert(f.g.m_vecErrLogs.size() == 1); }

    // ===== cluster type 0 -> Generator returns early =====
    { Fix f; f.Wire();
      f.g.m_pCluster = (CGameDataCluster*)0x99;
      f.g.m_fnClusterVal = [](uint32_t){ return 0; };
      f.rand100 = 50;                    // weights all 0
      f.g.m_nRest14 = 3;
      assert(f.g.Generator(100) == 0);   // early return
      assert(f.sent.empty());
      assert(f.g.m_nRest14 == 3);        // untouched
    }

    // ===== restock (FUN_14005fb30) =====
    { Fix f; f.Wire();
      f.g.m_nAmount10 = 4;               // +0x10
      f.g.m_nGenAmount18 = 4;            // +0x18
      f.g.AdjustAmountOnLeave();
      // 4-1=3; GetInt(8)=1>0: 4-1=3; 3 < 3? no -> no log
      assert(f.g.m_nAmount10 == 3);
      assert(f.g.m_nGenAmount18 == 3);
      assert(f.g.m_vecMsgLogs.empty());
      f.g.m_nGenAmount18 = 0;
      f.g.AdjustAmountOnLeave();
      // 3-1=2; 0-1=-1 < 2 -> sync + log
      assert(f.g.m_nAmount10 == 2);
      assert(f.g.m_nGenAmount18 == 2);
      assert(f.g.m_vecMsgLogs.size() == 1);
      assert(f.g.m_vecMsgLogs[0].find(
          "GeneratorID[%u]: m_nGenAmount[%d] < "
          "m_nAmount[%d]") == 0); }
    { Fix f; f.Wire();
      f.g.m_nAmount10 = 0;               // <= 0 branch
      f.g.AdjustAmountOnLeave();
      assert(f.g.m_vecMsgLogs.size() == 1);
      assert(f.g.m_vecMsgLogs[0].find(
          "GeneratorID[%u]: m_nAmount <= 0") == 0); }

    // ===== Process (FUN_140060b00, vtable+0x80) =====
    // cap field gate
    { Fix f; f.Wire();
      f.g.m_dwFieldF = 3;                 // +0x48 != 0
      assert(f.g.Process(100) == 0); }
    // +0x1c grid cap <= generated -> stop
    { Fix f; f.Wire();
      f.g.m_nMaxCap = 2; f.g.m_nGenAmount18 = 2;
      assert(f.g.Process(100) == 0); }
    // bit1(GetInt(0x12)) gate: max <= monsters
    { Fix f; f.Wire();
      f.g.m_nMaxCap = 2; f.g.m_nMonsters20 = 2;
      // GetInt(0x12) = 2 -> bit1 set
      f.g.m_cfg.m_fnGetInt = [&f](int idx){
          return idx == 0x12 ? 2
               : idx == 8 ? 1 : idx == 9 ? 7777
               : idx == 2 ? 500 : idx == 3 ? 300
               : idx == 4 ? 40 : idx == 5 ? 30
               : 0; };
      assert(f.g.Process(100) == 0); }
    // headroom gate: genAmount - amount >= budget -> 0
    { Fix f; f.Wire();
      f.g.m_nGenAmount18 = 50; f.g.m_nAmount10 = 10;
      assert(f.g.Process(100) == 0); }
    // budget clamp to max - genAmount
    { Fix f; f.Wire();
      f.g.m_nMaxCap = 3; f.g.m_nGenAmount18 = 1;
      // timer due (interval 1 sec passed)
      uint32_t ms = 500000;
      f.g.m_fnTime = [&]{ return ms; };
      f.g.m_nTimerSec30 = 1;
      f.g.m_dwBornSec = 0;              // due now
      f.g.m_nRest14 = 0;                // restock sets it
      // clamp: max - genAmount = 2, restock GetInt(8)
      // = 1 -> budget 1 -> ONE spawn this tick
      assert(f.g.Process(100) == 1);
      assert(f.g.m_nRest14 == 0);         // spent by Generator
      assert(f.g.m_nGenAmount18 == 2);   // 1 + 1 spawn
      assert(f.g.m_nMonsters20 == 1);    // +0x20 spawn
      assert(f.g.m_dwBornSec == 500);    // pair update
      assert(f.sent.size() == 1); }
    // restock gate: +0x14 < 1 after (no) timer due
    { Fix f; f.Wire();
      f.g.m_nTimerSec30 = 10; f.g.m_dwBornSec =
          f.g.m_fnTime() / 1000;        // not due
      f.g.m_nRest14 = 0;
      assert(f.g.Process(100) == 0); }
    // rearm: GetInt(7) > 599 -> new interval
    { Fix f; f.Wire();
      f.g.m_cfg.m_fnGetInt = [](int idx){
          return idx == 7 ? 1000
               : idx == 8 ? 1 : idx == 9 ? 7777
               : idx == 2 ? 500 : idx == 3 ? 300
               : idx == 4 ? 40 : idx == 5 ? 30
               : 0; };
      uint32_t ms = 900000;
      f.g.m_fnTime = [&]{ return ms; };
      f.g.m_nMaxCap = 5;      // +0x1c gate (Wire leaves 0)
      f.g.m_nTimerSec30 = 1; f.g.m_dwBornSec = 0;
      f.g.m_fnRand = [](int n){ return n / 2; };
      assert(f.g.Process(100) >= 1);
      // rearm: +0x30 = 1000 + RandGet(1000) = 1500
      assert(f.g.m_nTimerSec30 == 1500);
      assert(f.g.m_dwBornSec == 900); }

    printf("NPC_GENPROC_OK: gates (map +0x28 / cap +0x48 "
           "/ budget), attempts max(1, GetInt(5)*GetInt(4)), "
           "fixed 0xc/0xd + random 2/4 3/5 probes, "
           "FUN_14004cc70 break + FUN_140049310 flag, "
           "0x38 record (id +0/vcall+0x40 +4/vtable+8 +8/"
           "x +0x14/y +0x16/tag 1 +0x18/type +0x1a/byte "
           "+0x2c), counters +0x14/- +0x18/+ +0x20/+, "
           "idle DB log GBK verbatim + 999ms throttle, "
           "cluster weighted type cols 2..0x14/3,5,..0x15 "
           "with early 0-return, restock GetInt(8) + sync "
           "log verbatim, Process FUN_140060b00 (cap field "
           "+ bit1 gate, +0x1c grid-cap, headroom "
           "genAmount-amount, budget clamp max-genAmount, "
           "FUN_140002700 timer pair due + rearm "
           "GetInt(7)>599, +0x14 = GetInt(8) restock, "
           "min(rest,budget) -> Generator)\n");
    return 0;
}
