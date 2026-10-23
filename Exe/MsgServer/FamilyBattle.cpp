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

// ================= income record store (FUN_1401512e0 family) ============
#include <ctime>

static uint64_t IncomeKey(uint32_t d, uint32_t s, uint32_t t) {
    return ((uint64_t)d << 40) | ((uint64_t)s << 20) | (uint64_t)t;
}

CFamilyBattleManager::SIncomeRec* CFamilyBattleManager::FindIncome(
        uint32_t d, uint32_t s, uint32_t t) {
    auto it = m_income.find(IncomeKey(d, s, t));
    return it == m_income.end() ? nullptr : &it->second;
}

int64_t CFamilyBattleManager::ReadIncome(uint32_t d, uint32_t s, uint32_t t) {
    // ORIGINAL FUN_140151580: lookup then FUN_1403ac920(rec, 4) -> int64;
    // missing record reads as 0
    auto* p = FindIncome(d, s, t);
    return p ? p->qwAmount : 0;
}

void CFamilyBattleManager::ResetIncome(uint32_t d, uint32_t s, uint32_t t) {
    // ORIGINAL FUN_140151380: create-or-reset the record with
    // {1:domain, 2:syn, 3:type, 4:0} and store it
    auto& r = m_income[IncomeKey(d, s, t)];
    r.dwDomain = d; r.dwSyn = s; r.dwType = t; r.qwAmount = 0;
}

void CFamilyBattleManager::EraseIncome(uint32_t d, uint32_t s, uint32_t t) {
    // ORIGINAL FUN_1401511e0: release + hash erase
    m_income.erase(IncomeKey(d, s, t));
}

void CFamilyBattleManager::AccumIncome(uint32_t d, uint32_t s, uint32_t t,
                                       int64_t n) {
    // ORIGINAL FUN_1401515b0: record found -> field4 += amount
    auto* p = FindIncome(d, s, t);
    if (p) p->qwAmount += n;
}

int32_t CFamilyBattleManager::KernelMinutes() {
    if (m_nKernelMinutes >= 0) return m_nKernelMinutes;
    time_t t = time(nullptr);
    struct tm* pTm = localtime(&t);
    return pTm ? pTm->tm_hour * 60 + pTm->tm_min : 0;
}
