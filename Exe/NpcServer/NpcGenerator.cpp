#include "NpcGenerator.h"
#include "MsgAiNpcInfo.h"
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



// ============================================================
// ===== ORIGINAL FUN_14005fc90: CNpcGenerator::Generator =====
// ============================================================
// int FUN_14005fc90(longlong *param_1, int param_2)
//   [param_1 = generator, param_2 = budget; CTickAnalyst
//    0x53 "    | `-CNpcGenerator::Generator" - the slot
//    CNpcManager::OnTimer's walk calls via vtable+0x80]
//   if (+0x28 map == 0) return 0;
//   else if ((int)+0x48 (config 0xf) != 0) return 0;
//   attempts = max(1, GetInt(5) * GetInt(4));
//   typeParam = GetInt(9);  spawned = 0;
//   if (budget > 0) while (+0x14 remaining > 0):
//     probe loop (up to `attempts`):
//       GetInt(0xc) >= 1 -> fixed: x = GetInt(0xc),
//                           y = GetInt(0xd)
//       else -> random: x = GetInt(2) + RandGet(GetInt(4)),
//                       y = GetInt(3) + RandGet(GetInt(5))
//       FUN_14004cc70(map, x, y) != 0 -> break (usable)
//       else: if (!bFound && FUN_140049310(map,x,y))
//                 bFound = true;
//             tries++; if (tries >= attempts) -> idle
//     idle (LAB_14005ffa2): if (spawned < 1 &&
//         attempts > 8 && !bFound):
//       now = TimeGet(0); if ((int)(now - +0x24) > 999):
//         +0x24 = now;
//         log_InlineLogDBERROR(DAT_1400c9af0, vtable+8)
//         // DAT_1400c9af0 (GBK) =
//         // "cq_generator.id=%u，出生点不可站"
//       break;
//     spawn: +0x40 cluster != 0 ->
//              wType = FUN_14005f7e0(...) (0 -> return
//              spawned); else wType = (word)GetInt(9)
//     id = FUN_14002b270(FUN_14001c7a0());
//     record 0x38 (the CMsgAiNpcInfo buffer):
//       +0x00 id | +0x04 vcall+0x40 | +0x08 vtable+8 |
//       +0x0c 0 | +0x10 0 | +0x14 (word)x | +0x16 (word)y
//       | +0x18 (word)1 (tag) | +0x1a (word)type |
//       +0x1c 0 | +0x20 0 | +0x24 0 | +0x28 0 |
//       +0x2c (byte)+0x4c | +0x30 0 | +0x34 0
//     FUN_140061220 (ctor) + FUN_1400613a0
//     (CreateFromBuffer): ok -> +0x14--, +0x18++,
//       +0x20++, spawned++, FUN_14001c5f0(inst,0,msg)
//     FUN_140061270 (dtor)
//     if (budget <= spawned) break;
//   return spawned
uint32_t CNpcGenerator::Generator(uint32_t dwBudget) {
    if (m_pMap == nullptr) return 0;          // +0x28
    if ((int32_t)m_dwFieldF != 0) return 0;   // +0x48
    // attempts = max(1, GetInt(5) * GetInt(4))
    int nAttempts = m_cfg.m_fnGetInt(5)
                  * m_cfg.m_fnGetInt(4);
    if (nAttempts < 1) nAttempts = 1;
    uint32_t nSpawned = 0;
    int nTypeParam = m_cfg.m_fnGetInt(9);
    bool bFoundValid = false;
    if ((int32_t)dwBudget > 0) {
        while (m_nRest14 > 0) {               // +0x14
            if (nAttempts < 1) break;
            int nTries = 0;
            int nX = 0, nY = 0;
            bool bCellOk = false;
            while (true) {
                int nFixed = m_cfg.m_fnGetInt(0xc);
                if (nFixed < 1) {
                    nX = m_cfg.m_fnGetInt(2)
                       + m_fnRand(m_cfg.m_fnGetInt(4));
                    nY = m_cfg.m_fnGetInt(3)
                       + m_fnRand(m_cfg.m_fnGetInt(5));
                } else {
                    nX = nFixed;      // (word)duplicated
                    nY = m_cfg.m_fnGetInt(0xd);
                }
                if (m_fnCellOk(m_pMap, nX, nY)) {
                    bCellOk = true;
                    break;
                }
                if (!bFoundValid &&
                    m_fnPosValid(m_pMap, nX, nY))
                    bFoundValid = true;
                nTries++;
                if (nTries >= nAttempts) break;
            }
            if (!bCellOk) {
                // LAB_14005ffa2: the idle DB-error log
                if (nSpawned < 1 && 8 < nAttempts &&
                    !bFoundValid) {
                    uint32_t uNow = m_fnTime();
                    if (999 < (int32_t)(uNow
                             - m_dwLastLogMs24)) {
                        m_dwLastLogMs24 = uNow;   // +0x24
                        // DAT_1400c9af0 (GBK verbatim)
                        m_vecDbErrLogs.push_back(
                          "cq_generator.id=%u"
                          "\xa3\xac\xb3\xf6\xc9\xfa\xb5\xe3"
                          "\xb2\xbb\xbf\xc9\xd5\xbe");
                    }
                }
                break;
            }
            // spawn: cluster type or plain typeParam
            uint16_t wType;
            if (m_pCluster != nullptr) {       // +0x40
                uint32_t t = ClusterType();
                if (t == 0) return nSpawned;
                wType = (uint16_t)t;
            } else {
                wType = (uint16_t)nTypeParam;
            }
            AiNpcInfoRecord rec;
            for (auto& d : rec.dw) d = 0;
            rec.dw[0] = m_fnSpawnNewNpcId();
            rec.dw[1] = m_fnGetMapId();        // vcall+0x40
            rec.dw[2] = m_fnGetId();           // vtable+8
            rec.setw(0x14, (uint16_t)nX);
            rec.setw(0x16, (uint16_t)nY);
            rec.setw(0x18, 1);                 // the tag
            rec.setw(0x1a, wType);
            rec.setb(0x2c, m_byField10);      // +0x4c
            // FUN_140061220 + FUN_1400613a0
            if (m_fnBuildSpawnMsg(rec)) {
                m_nRest14--;                   // +0x14
                m_nGenAmount18++;              // +0x18
                m_nMonsters20++;               // +0x20
                nSpawned++;
                // FUN_14001c200 + FUN_14001c5f0
                m_fnSendMsg(rec);
            }
            if ((int32_t)dwBudget <= (int32_t)nSpawned)
                break;
        }
    }
    return nSpawned;
}

// ============================================================
// ===== ORIGINAL FUN_14005f7e0: cluster weighted type =====
// ============================================================
// if (+0x40 == 0) log DAT_1400be0b0, return 0;
// r = RandGet(100); sum = 0; idx = 0; col = 2;
// do { if (0x15 < col) return 0;           // exhausted
//      sum += val(col);                    // weight cols
//      if (r < sum) break;
//      idx++; col += 2;
//    } while (sum < 100);
// return idx < 10 ? val(idx*2 + 1) : 0;   // type cols
uint32_t CNpcGenerator::ClusterType() {
    if (m_pCluster == nullptr) {
        m_vecErrLogs.push_back("DAT_1400be0b0");
        return 0;
    }
    int nSum = 0, nIdx = 0;
    int nRand = m_fnRand(100);
    int nCol = 2;
    do {
        if (0x15 < nCol) return 0;    // LAB_14005f888
        nSum += m_fnClusterVal((uint32_t)nCol);
        if (nRand < nSum) break;
        nIdx++;
        nCol += 2;
    } while (nSum < 100);
    if (nIdx < 10)
        return (uint32_t)m_fnClusterVal(
                           (uint32_t)(nIdx * 2 + 1));
    return 0;
}

// ============================================================
// ===== ORIGINAL FUN_14005fb30: restock on NPC leave =====
// ============================================================
// if (0 < +0x10 m_nAmount): +0x10--;
//   iVar = GetInt(8); if (0 < iVar):
//     +0x18--; if (+0x18 < +0x10):
//       vtable+8 (GetId for the log);
//       log_InlineLogMessage("GeneratorID[%u]: "
//         "m_nGenAmount[%d] < m_nAmount[%d]");
//       +0x18 = +0x10;
// else: vtable+8;
//   log_InlineLogERROR("GeneratorID[%u]: m_nAmount <= 0");
void CNpcGenerator::AdjustAmountOnLeave() {
    if (0 < m_nAmount10) {
        m_nAmount10--;
        int iVar = m_cfg.m_fnGetInt(8);
        if (0 < iVar) {
            m_nGenAmount18--;
            if (m_nGenAmount18 < m_nAmount10) {
                m_vecMsgLogs.push_back(
                    "GeneratorID[%u]: m_nGenAmount[%d] < "
                    "m_nAmount[%d]");
                m_nGenAmount18 = m_nAmount10;
            }
        }
        return;
    }
    m_vecMsgLogs.push_back(
        "GeneratorID[%u]: m_nAmount <= 0");
}

} // namespace npc
