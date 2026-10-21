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

bool CGameMap::LoadCollision(const std::string& dmapPath) {
    return m_dmap.Load(dmapPath);
}

bool CGameMap::IsPassable(uint16_t usX, uint16_t usY) const {
    if (m_dmap.IsLoaded())
        return m_dmap.IsWalkable(usX, usY); // real terrain from the original .DMap
    return true; // no dmap on disk: free movement (synthetic v1)
}

std::vector<uint32_t> CGameMap::GetUserIds() const {
    std::vector<uint32_t> ids;
    ids.reserve(m_users.size());
    for (auto& kv : m_users) ids.push_back(kv.first);
    return ids;
}