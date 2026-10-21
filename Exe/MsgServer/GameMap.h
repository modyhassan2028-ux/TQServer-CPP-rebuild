#pragma once
#include <string>
#include <unordered_map>
#include <cstdint>
#include <memory>
#include <vector>

class CUser;
class CMonster;

class CGameMap {
public:
    CGameMap(uint32_t dwId, const std::string& name);
    ~CGameMap();

    uint32_t GetId() const { return m_dwId; }
    const std::string& GetName() const { return m_name; }

    bool AddUser(std::shared_ptr<CUser> user);
    bool RemoveUser(uint32_t dwUserId);
    bool IsPassable(uint16_t usX, uint16_t usY) const;
    std::vector<uint32_t> GetUserIds() const;

private:
    uint32_t m_dwId;
    std::string m_name;
    std::unordered_map<uint32_t, std::shared_ptr<CUser>> m_users;
};