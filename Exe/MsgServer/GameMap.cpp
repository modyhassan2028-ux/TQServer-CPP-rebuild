#include "GameMap.h"
#include "User.h"

CGameMap::CGameMap(uint32_t dwId, const std::string& name) : m_dwId(dwId), m_name(name) {}
CGameMap::~CGameMap() = default;

bool CGameMap::AddUser(std::shared_ptr<CUser> user) {
    if (!user) return false;
    m_users[user->GetId()] = user;
    return true;
}

bool CGameMap::RemoveUser(uint32_t dwUserId) {
    return m_users.erase(dwUserId) > 0;
}

bool CGameMap::IsPassable(uint16_t, uint16_t) const {
    return true;
}