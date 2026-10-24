#include "NpcGenerator.h"
#include <cstdio>

namespace npc {

// ===== ORIGINAL FUN_140061040: CNpcGenerator::CreateNpc =====
// faithful flow:
//  1. group = type->vcall+0x28()->vcall+0x40(); reject if
//     FUN_14005f9d0(config, type, group) fails
//  2. config->GetInt(0x12) bit0 == 0 (fixed mode):
//     map id from the +8 lookup (DAT_140102d90), type =
//     GetInt(1). Else (random mode): nTypeParam must be
//     nonzero, map id = FUN_14002b2d0(kernel), type =
//     nTypeParam.
//  3. X = GetInt(7) + tq::RandGet(GetInt(7)); born =
//     TimeGet(0)/1000
//  4. step: GetInt(8) == 0 -> 0; else h = GetInt(6):
//     h > 0 -> (GetInt(5)/h) * (GetInt(4)/h), if 0 -> 1
//  5. map object = FUN_14003ca10(kernel, map id); null ->
//     Close + "Error: npc generator [%u] got invalid map
//     [%u]!" and fail; else FUN_140060e60 tail, fields
//     0xf/0x10, success.
bool CNpcGenerator::CreateNpc(TypeRecord* pType,
                              int nTypeParam) {
    int64_t nGroup = pType ? pType->m_fnGetGroup() : 0;
    if (m_fnGroupFilter && !m_fnGroupFilter(&m_cfg, pType,
                                            nGroup))
        return false;                    // LAB_1400611cb
    if ((m_cfg.m_fnGetInt(0x12) & 1) == 0) {
        // fixed mode: the +8 object lookup by DAT_140102d90
        m_dwMap = m_fnCurrentMapId();
        m_dwType = (uint32_t)m_cfg.m_fnGetInt(1);
    } else {
        if (nTypeParam == 0) return false;
        m_dwType = (uint32_t)nTypeParam;
        m_dwMap = m_fnRandomMapId();
    }
    int nGeo7 = m_cfg.m_fnGetInt(7);
    m_nX = nGeo7 + m_fnRand(nGeo7);
    m_dwBornSec = m_fnTime() / 1000;
    int nStepIn = m_cfg.m_fnGetInt(8);
    if (nStepIn == 0) {
        m_nStep = 0;
    } else {
        int h = m_cfg.m_fnGetInt(6);
        if (h > 0) {
            m_nStep = (m_cfg.m_fnGetInt(5) / h) *
                      (m_cfg.m_fnGetInt(4) / h);
            if (m_nStep <= 0) m_nStep = 1;
        } else {
            m_nStep = 1;
        }
    }
    m_pMap = m_fnFindMap(m_dwType);
    if (m_pMap) {
        if (!LoadCluster()) return false; // FUN_140060e60
        m_dwFieldF = (uint32_t)m_cfg.m_fnGetInt(0xf);
        m_byField10 = (uint8_t)m_cfg.m_fnGetInt(0x10);
        return true;
    }
    // ORIGINAL: vcall+8 Close then the verbatim error
    m_bClosed = true;
    char buf[128];
    std::snprintf(buf, sizeof buf,
        "Error: npc generator [%u] got invalid map [%u]!",
        m_dwType, m_dwMap);
    if (m_fnLog) m_fnLog(buf);
    return false;
}

// ===== ORIGINAL FUN_140060e60: CNpcGenerator::LoadCluster =====
// config GetInt(0x11) == 0 -> true (no cluster).
// else: id = GetInt(9); new CGameData<szMonsterClusterTable>
// (0x18) -> this+0x40; alloc fail -> log @0x1d8, false.
// snprintf(0x40, "SELECT * FROM %s WHERE id = %d LIMIT 1")
// -> InstanceGet()->vcall+0x10(sql, 2): null -> log @0x1e2,
// delete cluster (+0x40 = 0), false. rows (vcall+0x40) ==
// 0 -> log @0x1ea, delete cluster + result, false.
// else: cluster->vcall+0x30(res) (LoadFromRow), free res.
bool CNpcGenerator::LoadCluster() {
    if (m_cfg.m_fnGetInt(0x11) == 0) return true;
    uint32_t dwId = (uint32_t)m_cfg.m_fnGetInt(9);
    m_pCluster = new CGameDataCluster(); // operator_new(0x18)
    if (m_pCluster)
        m_pCluster->m_fnLoadRow = m_fnClusterLoadRow;
    if (!m_pCluster) {
        m_vecErrLogs.push_back("log_InlineLogERROR line 0x1d8");
        return false;
    }
    char szSql[0x40];
    std::snprintf(szSql, sizeof szSql,
        "SELECT * FROM %s WHERE id = %d LIMIT 1",
        "<szMonsterClusterTable: name TBD>", (int)dwId);
    DbResult* pRes = m_fnQuery(szSql, 2, (int)dwId);
    if (!pRes) {
        m_vecErrLogs.push_back("log_InlineLogERROR line 0x1e2");
        delete m_pCluster; m_pCluster = nullptr; // +0x40 = 0
        return false;
    }
    if (pRes->nRows == 0) {
        m_vecErrLogs.push_back("log_InlineLogERROR line 0x1ea");
        delete m_pCluster; m_pCluster = nullptr;
        delete pRes;                       // (**vtable)(res)
        return false;
    }
    bool bOk = m_pCluster->m_fnLoadRow
        ? m_pCluster->m_fnLoadRow(pRes) : true;
    delete pRes;                           // vcall+0x30 tail
    return bOk;
}

} // namespace npc
