#include "UserManager.h"
#include "Account.h"

CUserManager& CUserManager::Instance() {
    static CUserManager s_instance;
    return s_instance;
}

bool CUserManager::AddUser(std::shared_ptr<CUser> user) {
    if (!user) return false;
    std::lock_guard<std::mutex> lock(m_mutex);
    m_users[user->GetId()] = user;
    m_names[user->GetName()] = user;
    return true;
}

bool CUserManager::RemoveUser(uint32_t dwId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_users.find(dwId);
    if (it != m_users.end()) {
        // persist the character to cq_user before it leaves (MySQL mode)
        auto pUser = it->second;
        if (pUser && pUser->GetAccountId()) {
            CAccountManager::CharacterRecord rec;
            rec.dwLevel = pUser->GetLevel();
            rec.dwExperience = pUser->GetExperience();
            rec.dwStatPoints = pUser->GetStatPoints();
            rec.dwStrength = pUser->GetStrength();
            rec.dwVitality = pUser->GetVitality();
            rec.dwRebornCount = pUser->GetRebornCount();
            rec.dwMoney = pUser->GetMoney();
            rec.dwCp = pUser->GetConquerPoints();
            rec.dwBank = pUser->GetBank();
            rec.dwPkPoints = pUser->GetPkPoints();
            rec.dwMapId = pUser->GetMapId();
            rec.usX = pUser->GetX();
            rec.usY = pUser->GetY();
            CAccountManager::Instance().SaveCharacter(pUser->GetAccountId(), rec);
            std::vector<CAccountManager::ItemRow> rows;
            for (const auto& it : pUser->GetInventory())
                rows.push_back({ it.dwType, it.usSort, it.dwAmount, it.dwPosition, it.strName });
            CAccountManager::Instance().SaveItems(pUser->GetAccountId(), rows);
        }
        m_names.erase(pUser->GetName());
        m_users.erase(it);
        return true;
    }
    return false;
}

std::shared_ptr<CUser> CUserManager::GetUser(uint32_t dwId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_users.find(dwId);
    return (it != m_users.end()) ? it->second : nullptr;
}

std::shared_ptr<CUser> CUserManager::GetUserByName(const std::string& name) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_names.find(name);
    return (it != m_names.end()) ? it->second : nullptr;
}

size_t CUserManager::GetUserCount() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_users.size();
}
std::vector<std::shared_ptr<CUser>> CUserManager::GetAllUsers() {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::vector<std::shared_ptr<CUser>> out;
    out.reserve(m_users.size());
    for (auto& kv : m_users) out.push_back(kv.second);
    return out;
}
