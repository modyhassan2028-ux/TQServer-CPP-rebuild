#include "FamilyBattle.h"
#include "Account.h"
#include "MySQLClient.h"

CFamilyBattleManager& CFamilyBattleManager::Instance() {
    static CFamilyBattleManager s_instance;
    return s_instance;
}

CFamilyBattleManager::SDomain* CFamilyBattleManager::Find(uint32_t dwId) {
    auto it = m_byId.find(dwId);
    return it == m_byId.end() ? nullptr : &it->second;
}

CFamilyBattleManager::SDomain& CFamilyBattleManager::Create(uint32_t dwId) {
    auto& rec = m_byId[dwId];
    rec.dwId = dwId;
    return rec;
}

void CFamilyBattleManager::SeedFromDB(CMySQLClient* pDB) {
    // ORIGINAL: the domain records are created by the family-battle
    // scheduler at mapgroup boot. That subsystem is not ported yet; seed
    // the ids the shipped cq_action chains actually reference so the
    // vcall+0x88 lookup behaves the same for real rows.
    if (!pDB) return;
    if (!pDB->Query("SELECT DISTINCT data FROM cq_action WHERE "
                    "type IN (3521, 3523, 3524) AND data != 0"))
        return;
    for (auto& row : pDB->GetRows()) {
        if (row.empty()) continue;
        uint32_t id = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        if (id && !Find(id)) Create(id);
    }
}
