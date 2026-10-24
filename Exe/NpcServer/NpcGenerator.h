// CNpcGenerator - the monster generator object of
// npcmanager.cpp; CreateNpc = ORIGINAL FUN_140061040
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <functional>
#include <string>
#include <vector>

namespace npc {

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
    int      m_nStep = 0;           // +0x1c
    int      m_nX = 0;             // +0x30 (random X)
    uint32_t m_dwBornSec = 0;       // +0x34 (TimeGet/1000)
    void*    m_pMapIdCell = nullptr; // +0x50 slot source
    uint32_t m_dwMap = 0;          // +0x50 (map id)
    uint32_t m_dwType = 0;         // +0x54 (npc type)
    uint32_t m_dwFieldF = 0;       // +0x48 (config 0xf)
    uint8_t  m_byField10 = 0;      // +0x4c (config 0x10)
    bool     m_bClosed = false;    // vcall+8 Close

    // test seams (kernel lookups)
    std::function<bool(GenConfig*, TypeRecord*, int64_t)>
        m_fnGroupFilter;                 // FUN_14005f9d0
    std::function<uint32_t()> m_fnCurrentMapId; // DAT_140102d90
    std::function<uint32_t()> m_fnRandomMapId;  // FUN_14002b2d0
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
};

} // namespace npc
