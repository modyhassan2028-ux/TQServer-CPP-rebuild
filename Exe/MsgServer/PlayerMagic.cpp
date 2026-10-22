// CPlayerMagic - see PlayerMagic.h for the ABI notes.
#include "PlayerMagic.h"
#include "MySQLClient.h"
#include <cstdio>
#include <map>

CMagicTypePool& CMagicTypePool::Instance() {
    static CMagicTypePool s_inst;
    return s_inst;
}

// ORIGINAL cq_magictype schema (6159):
// id, type, sort, name, crime, ground, multi, target, level, use_mp, power,
// intone_speed, percent, step_secs, `range`, distance, status, need_prof,
// need_exp, need_level, delay_ms, weapon_sub
bool CMagicTypePool::LoadFromDB(CMySQLClient* pDB) {
    if (!pDB) return false;
    if (!pDB->Query(
            "SELECT id, type, sort, name, crime, ground, multi, target, level,"
            " use_mp, power, intone_speed, percent, step_secs, `range`, distance,"
            " status, need_prof, need_exp, need_level, need_time, delay_ms, weapon_subtype"
            " FROM cq_magictype")) {
        printf("[MAGIC] cq_magictype load failed: %s\n", pDB->GetError().c_str());
        return false;
    }
    m_oTypes.clear();
    for (auto& row : pDB->GetRows()) {
        if (row.size() < 19) continue;
        CMagicTypeInfo t;
        auto u32 = [&](size_t i) { return (uint32_t)strtoul(row[i].c_str(), nullptr, 10); };
        t.dwId = u32(0);
        t.dwType = u32(1);
        t.dwSort = u32(2);
        t.strName = row[3];
        t.ucCrime = (uint8_t)strtoul(row[4].c_str(), nullptr, 10);
        t.ucGround = (uint8_t)strtoul(row[5].c_str(), nullptr, 10);
        t.ucMulti = (uint8_t)strtoul(row[6].c_str(), nullptr, 10);
        t.dwTarget = u32(7);
        t.dwLevel = u32(8);
        t.dwUseMp = u32(9);
        t.nPower = (int32_t)strtol(row[10].c_str(), nullptr, 10);
        t.dwIntoneSpeed = u32(11);
        t.dwPercent = u32(12);
        t.dwStepSecs = u32(13);
        t.dwRange = u32(14);
        t.dwDistance = u32(15);
        t.nStatus = (int32_t)strtol(row[16].c_str(), nullptr, 10);
        t.dwNeedProf = u32(17);
        t.nNeedExp = (int32_t)strtol(row[18].c_str(), nullptr, 10);
        t.dwNeedLevel = row.size() > 19 ? u32(19) : 0;
        t.dwNeedTime  = row.size() > 20 ? u32(20) : 0;
        t.dwDelayMs = row.size() > 21 ? u32(21) : 0;
        t.dwWeaponSub = row.size() > 22 ? u32(22) : 0;
        m_oTypes[((uint64_t)t.dwType << 16) | (uint16_t)t.dwLevel] = t;
    }
    printf("[MAGIC] cq_magictype: %zu stage(s) loaded.\n", m_oTypes.size());
    return !m_oTypes.empty();
}

const CMagicTypeInfo* CMagicTypePool::Find(uint32_t dwType, uint32_t dwLevel) const {
    auto it = m_oTypes.find(((uint64_t)dwType << 16) | (uint16_t)dwLevel);
    return it == m_oTypes.end() ? nullptr : &it->second;
}

// ---- CPlayerMagic record ABI ----
int32_t CPlayerMagic::GetAttrib(uint32_t dwIdx) const {
    switch (dwIdx) {
    case 0: return (int32_t)m_dwId;
    case 1: return (int32_t)m_dwOwnerid;
    case 2: return (int32_t)m_wType;
    case 3: return (int32_t)m_wLevel;
    case 4: return (int32_t)m_dwExp;
    case 5: return (int32_t)m_ucUnlearn;
    case 6: return (int32_t)m_wOldLevel;
    case 7: return (int32_t)m_ucCurrentEffectType;
    case 8: return (int32_t)m_dwAvailableEffectType;
    case 9: return (int32_t)m_dwEffectMonopoly;
    case 10: return (int32_t)m_dwEffectExorbitant;
    default:
        // ORIGINAL logs an InlineLogDBERROR for out-of-range fields
        printf("[MAGIC] GetAttrib(%u) out of range (type %u)\n", dwIdx, m_wType);
        return 0;
    }
}

bool CPlayerMagic::SetAttrib(uint32_t dwIdx, int32_t nValue) {
    switch (dwIdx) {
    case 0: m_dwId = (uint32_t)nValue; return true;
    case 1: m_dwOwnerid = (uint32_t)nValue; return true;
    case 2: m_wType = (uint16_t)nValue; return true;
    case 3: m_wLevel = (uint16_t)nValue; return true;
    case 4: m_dwExp = (uint32_t)nValue; return true;
    case 5: m_ucUnlearn = (uint8_t)nValue; return true;
    case 6: m_wOldLevel = (uint16_t)nValue; return true;
    case 7: m_ucCurrentEffectType = (uint8_t)nValue; return true;
    case 8: m_dwAvailableEffectType = (uint32_t)nValue; return true;
    case 9: m_dwEffectMonopoly = (uint32_t)nValue; return true;
    case 10: m_dwEffectExorbitant = (uint32_t)nValue; return true;
    default:
        printf("[MAGIC] SetAttrib(%u) out of range\n", dwIdx);
        return false;
    }
}

bool CPlayerMagic::Save(CMySQLClient* pDB) {
    if (!pDB) return false;
    if (m_dwId) {
        std::string sql =
            "UPDATE cq_magic SET ownerid=" + std::to_string(m_dwOwnerid) +
            ", type=" + std::to_string(m_wType) +
            ", level=" + std::to_string(m_wLevel) +
            ", exp=" + std::to_string(m_dwExp) +
            ", unlearn=" + std::to_string((unsigned)m_ucUnlearn) +
            ", old_level=" + std::to_string((unsigned)m_wOldLevel) +
            ", current_effect_type=" + std::to_string((unsigned)m_ucCurrentEffectType) +
            ", available_effect_type=" + std::to_string(m_dwAvailableEffectType) +
            ", effect_monopoly=" + std::to_string(m_dwEffectMonopoly) +
            ", effect_exorbitant=" + std::to_string(m_dwEffectExorbitant) +
            " WHERE id=" + std::to_string(m_dwId);
        return pDB->Query(sql);
    }
    std::string sql =
        "INSERT INTO cq_magic (ownerid, type, level, exp, unlearn, old_level,"
        " current_effect_type, available_effect_type, effect_monopoly, effect_exorbitant)"
        " VALUES (" + std::to_string(m_dwOwnerid) + ", " + std::to_string(m_wType) +
        ", " + std::to_string(m_wLevel) + ", " + std::to_string(m_dwExp) +
        ", " + std::to_string((unsigned)m_ucUnlearn) + ", " + std::to_string((unsigned)m_wOldLevel) +
        ", " + std::to_string((unsigned)m_ucCurrentEffectType) + ", " + std::to_string(m_dwAvailableEffectType) +
        ", " + std::to_string(m_dwEffectMonopoly) + ", " + std::to_string(m_dwEffectExorbitant) + ")";
    if (!pDB->Query(sql)) return false;
    // attr 0 comes back from the pool (AUTO_INCREMENT id in the rebuild;
    // the original used its record-counter - same observable behavior)
    std::string sid = pDB->Scalar("SELECT LAST_INSERT_ID()");
    if (!sid.empty()) m_dwId = (uint32_t)strtoul(sid.c_str(), nullptr, 10);
    return true;
}

bool CPlayerMagic::EraseFromDB(CMySQLClient* pDB) {
    if (!pDB || !m_dwId) return false;
    return pDB->Query("DELETE FROM cq_magic WHERE id=" + std::to_string(m_dwId));
}
