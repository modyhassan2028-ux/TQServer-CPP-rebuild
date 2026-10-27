#pragma once
#include <unordered_map>
#include <memory>
#include <mutex>
#include <vector>
#include "User.h"

class CUserManager {
public:
    static CUserManager& Instance();

    bool AddUser(std::shared_ptr<CUser> user);
    bool RemoveUser(uint32_t dwId);
    std::shared_ptr<CUser> GetUser(uint32_t dwId);
    std::shared_ptr<CUser> GetUserByName(const std::string& name);

    size_t GetUserCount();
    // snapshot of all online users (for autosave/sweeps)
    std::vector<std::shared_ptr<CUser>> GetAllUsers();

private:
    CUserManager() = default;
    std::unordered_map<uint32_t, std::shared_ptr<CUser>> m_users;
    std::unordered_map<std::string, std::shared_ptr<CUser>> m_names;
    std::mutex m_mutex;
};