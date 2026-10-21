#include "UserManager.h"

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
        m_names.erase(it->second->GetName());
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