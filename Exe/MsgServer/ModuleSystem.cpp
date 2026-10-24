#include "ModuleSystem.h"

int64_t CSynvarModule::QueryInt(uint32_t dwVarId) const {
    auto it = m_byId.find(dwVarId);
    return it == m_byId.end() ? 0 : it->second;
}
void CSynvarModule::WriteInt(uint32_t dwVarId, int64_t nValue) {
    m_byId[dwVarId] = nValue;
}
bool CSynvarModule::HasName(const std::string& s) const {
    return m_byName.count(s) != 0;
}
int64_t CSynvarModule::QueryName(const std::string& s) const {
    auto it = m_byName.find(s);
    return it == m_byName.end() ? 0 : it->second;
}
void CSynvarModule::WriteName(const std::string& s, int64_t v) {
    m_byName[s] = v;
}

CModuleManager& CModuleManager::Instance() {
    static CModuleManager s_inst;
    return s_inst;
}
std::shared_ptr<IModule> CModuleManager::GetModule(uint32_t dwId) {
    auto it = m_modules.find(dwId);
    if (it != m_modules.end()) return it->second;
    std::shared_ptr<IModule> p;
    if (dwId == 0x1e) p = std::make_shared<CSynvarModule>();
    if (dwId == 0xd)  p = std::make_shared<CTaskManagerModule>(); // task mgr binding (task_detail)
    if (dwId == 10)   p = std::make_shared<CLotteryModule>(); // pLotteryProvider
    if (!p) return nullptr; // unknown module id -> module absent
    m_modules[dwId] = p;
    return p;
}
CSynvarModule* CModuleManager::Synvar() {
    auto p = std::dynamic_pointer_cast<CSynvarModule>(GetModule(0x1e));
    return p.get();
}

// ---------- module 10: pLotteryProvider ----------
#include "Account.h"
#include "MySQLClient.h"
#include <cstdlib>
#include <vector>
size_t CLotteryModule::RowCount(uint32_t uType) {
    auto* pDB = CAccountManager::Instance().GetDB();
    if (!pDB) return 0;
    pDB->Query("SELECT COUNT(*) FROM cq_lottery WHERE type=" +
               std::to_string(uType));
    auto& rows = pDB->GetRows();
    return rows.empty() ? 0 : (size_t)atoi(rows[0][0].c_str());
}
bool CLotteryModule::RollPrize(uint32_t uType, SPrize& out) {
    auto* pDB = CAccountManager::Instance().GetDB();
    if (!pDB) return false;
    pDB->Query("SELECT id,rank,chance,prize_name,prize_item,color,"
               "hole_num,addition_lev FROM cq_lottery WHERE type=" +
               std::to_string(uType));
    auto& rows = pDB->GetRows();
    if (rows.empty()) return false;
    std::vector<const std::vector<std::string>*> weighted;
    for (auto& r : rows)
        for (uint32_t i = 0; i < (uint32_t)atoi(r[2].c_str()); ++i)
            weighted.push_back(&r);
    if (weighted.empty()) return false;
    const auto& r = *weighted[std::rand() % weighted.size()];
    out.dwRowId   = (uint32_t)atoi(r[0].c_str());
    out.uRank     = (uint8_t)atoi(r[1].c_str());
    out.uChance   = (uint32_t)atoi(r[2].c_str());
    out.strName   = r[3];
    out.dwItem    = (uint32_t)atoi(r[4].c_str());
    out.ucColor   = (uint8_t)atoi(r[5].c_str());
    out.ucHoles   = (uint8_t)atoi(r[6].c_str());
    out.ucAddition= (uint8_t)atoi(r[7].c_str());
    return true;
}
CLotteryModule* CModuleManager::Lottery() {
    auto p = std::dynamic_pointer_cast<CLotteryModule>(GetModule(10));
    return p.get();
}
