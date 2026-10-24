// CNpcGenerator - the monster generator object of
// npcmanager.cpp; CreateNpc = ORIGINAL FUN_140061040
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <functional>
#include <string>
#include <vector>

namespace npc {

struct AiNpcInfoRecord;   // MsgAiNpcInfo.h

// generator config record (read via vcall+0x10 GetInt(i))
struct GenConfig {
    // ORIGINAL call indices recovered in FUN_140061040:
    // 1 type, 4/5/6/7/8 spawn geometry, 0xf/0x10 npc
    // fields, 0x12 bit0 = random-map mode
    std::function<int(int)> m_fnGetInt;
};

// monster-type record: vcall+0x28 -> vcall+0x40 (group id)
struct TypeRecord {
    std::function<int64_t()> m_fnGetGroup;
};

// ORIGINAL CGameData<&szMonsterClusterTable,&szID>:
// 0x18 bytes - vftable, result @+0x8, flag @+0x10
// (ctor FUN_140060610, vcall+0x30 = LoadFromRow,
//  vcall+0x58 = delete). The exact table name string of
// szMonsterClusterTable is TBD in the decompile.
struct DbResult {                  // SQL result: vcall+0x40
    int nRows = 0;
};

class CGameDataCluster {
public:
    bool m_bFlag = false;          // +0x10
    std::function<bool(DbResult*)> m_fnLoadRow; // vcall+0x30
};

class CNpcGenerator {
public:
    // ORIGINAL FUN_140061040: CNpcGenerator::CreateNpc
    // returns 1 on success (ORIGINAL CONCAT71(...,1))
    bool CreateNpc(TypeRecord* pType, int nTypeParam);

    // object fields (ORIGINAL offsets)
    void*    m_pMap = nullptr;      // +0x28 (map object)
    // vtable dump (vftable at 0x1400c7fc8 in the
    // binary): +0x00 deleting dtor 140060ad0, +0x08
    // GetGenId 14005f510 -> field +0x50, +0x20
    // GetAmount 14005f4e0 -> +0x10, +0x30 GetGenAmount
    // 14005f4f0 -> +0x18, +0x28 GetCenter 1400600d0,
    // +0x38/50/58/60 = GetInt(5)/(2)/(3)/(4) void,
    // +0x68 InRect 14005f580, +0x70 InArea 14005f630,
    // +0x78 restock 14005fb30, +0x80 Process 140060b00
    // (calls Generator 14005fc90), +0x88 DB-row spawner
    // 14005f8c0, +0x90 counter 140060030, +0xa0 Close
    // 14005f7a0. rec+0x08 = vtable+8 = +0x50 = THE
    // GENERATOR ID (the CNpc::Create findGenerator
    // key), NOT a map id.
    int      m_nMaxCap = 0;        // +0x1c grid-cell
                                   // cap (5/6)*(4/6)
                                   // or 1 (vcall+0x48
                                   // getter; NOT a
                                   // step)
    int      m_nTimerSec30 = 0;   // +0x30 spawn
                                   // interval sec
                                   // (FUN_140002700
                                   // pair + +0x34)
    uint32_t m_dwBornSec = 0;     // +0x34 last spawn
                                   // sec (TimeGet/1000)
    uint32_t m_dwGenId = 0;       // +0x50 (vtable+8)
    uint32_t m_dwMapId = 0;       // +0x54 (the map
                                   // object lookup
                                   // key in the
                                   // CreateNpc path)
    uint32_t m_dwFieldF = 0;       // +0x48 (config 0xf)
    uint8_t  m_byField10 = 0;      // +0x4c (config 0x10)
    bool     m_bClosed = false;    // vcall+8 Close

    // test seams (kernel lookups)
    std::function<bool(GenConfig*, TypeRecord*, int64_t)>
        m_fnGroupFilter;                 // FUN_14005f9d0
    std::function<uint32_t()> m_fnCurrentGenId;   // +0x50 fixed // DAT_140102d90
    std::function<uint32_t()> m_fnRandomGenId;    // +0x50 random  // FUN_14002b2d0
    std::function<void*(uint32_t)> m_fnFindMap; // FUN_14003ca10
    // ORIGINAL FUN_140060e60: LoadCluster - the CreateNpc
    // tail (config 0x11 flag, SELECT * FROM <cluster table>
    // WHERE id = GetInt(9) LIMIT 1 via InstanceGet)
    bool LoadCluster();
    CGameDataCluster* m_pCluster = nullptr;   // +0x40
    // InstanceGet()->vcall+0x10(sql, 2): query seam
    std::function<DbResult*(const char*, int,
                            int)> m_fnQuery;
    // the cluster class' fixed vtable row loader
    // (vcall+0x30) as a seam
    std::function<bool(DbResult*)> m_fnClusterLoadRow;
    std::vector<std::string> m_vecErrLogs;    // 1400be0b0
    std::function<int(int)> m_fnRand;            // tq::RandGet
    std::function<uint32_t()> m_fnTime;          // tq::TimeGet
    std::function<void(const char*)> m_fnLog;
    GenConfig m_cfg;

    // ---------- counters (ORIGINAL offsets, ctor
    // FUN_140060d60 zeros all five) ----------
    int32_t  m_nAmount10 = 0;       // +0x10 m_nAmount (FUN_14005fb30)
    int32_t  m_nRest14 = 0;        // +0x14 remaining to
                                    // spawn (Generator loop
                                    // gate; the ORIGINAL
                                    // writer is TBD - not
                                    // in FUN_140061040;
                                    // likely the +0x38 walk)
    int32_t  m_nGenAmount18 = 0;   // +0x18 m_nGenAmount
    int32_t  m_nMonsters20 = 0;   // +0x20 in-game count
                                    // (stats vcall+0x30)
    uint32_t m_dwLastLogMs24 = 0; // +0x24 idle-log ms

    // ---------- FUN_14005fc90 seams ----------
    // FUN_14004cc70(map, x, y): position usable
    // (nonzero -> the probe loop breaks and the spawn
    // proceeds)
    std::function<bool(void*, int, int)> m_fnCellOk;
    // FUN_140049310(map, x, y): position valid (feeds the
    // bVar2 flag that suppresses the idle log)
    std::function<bool(void*, int, int)> m_fnPosValid;
    // FUN_14001c7a0 + FUN_14002b270: SpawnNewNpcID
    std::function<uint32_t()> m_fnSpawnNewNpcId;
    // vcall+0x40 on the generator vtable -> record +0x04
    std::function<uint32_t()> m_fnGetMapId;
    // vtable+8 (GetId) -> record +0x08 / log %u
    std::function<uint32_t()> m_fnGetId;
    // FUN_140061220 ctor + FUN_1400613a0
    // CreateFromBuffer(&record): build the 0x38
    // CMsgAiNpcInfo from the filled record
    std::function<bool(const AiNpcInfoRecord&)>
        m_fnBuildSpawnMsg;
    // FUN_14001c200 + FUN_14001c5f0(inst, 0, msg) -
    // the assembled buffer is the record
    std::function<void(const AiNpcInfoRecord&)>
        m_fnSendMsg;
    // vtable+0x10 on the +0x40 cluster object by index
    // (weights 2,4,..0x14 / types 3,5,..0x15)
    std::function<int(uint32_t)> m_fnClusterVal;
    // sinks: log_InlineLogDBERROR(DAT_1400c9af0) /
    // InlineLogMessage / InlineLogERROR(DAT_1400be0b0)
    std::vector<std::string> m_vecDbErrLogs;
    std::vector<std::string> m_vecMsgLogs;

    // ===== ORIGINAL FUN_14005fc90: CNpcGenerator::
    // Generator (CTickAnalyst 0x53) =====
    uint32_t Generator(uint32_t dwBudget);
    // ===== ORIGINAL FUN_140060b00 (THE vtable+0x80
    // slot the CNpcManager walk calls with the budget;
    // wraps FUN_14005fc90 and IS the +0x14 writer) =====
    uint32_t Process(uint32_t dwBudget);
    // ===== ORIGINAL FUN_140002700: spawn-timer pair
    // (+0x30 interval sec + +0x34 last spawn sec) =====
    bool TimerDue();
    // ===== ORIGINAL FUN_14005f7e0: weighted cluster type
    // (RandGet(100) over cluster columns) =====
    uint32_t ClusterType();
    // ===== ORIGINAL FUN_14005fb30: amount restock on NPC
    // leave/death (glue name) =====
    void AdjustAmountOnLeave();
};

} // namespace npc
