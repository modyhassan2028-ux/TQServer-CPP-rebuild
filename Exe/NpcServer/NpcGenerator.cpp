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
        if (m_fnTailInit) m_fnTailInit(); // FUN_140060e60
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

} // namespace npc
