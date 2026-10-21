#include "MapManager.h"
#include "User.h"
#include "UserManager.h"

CMapManager& CMapManager::Instance() {
    static CMapManager s_instance;
    return s_instance;
}

std::shared_ptr<CGameMap> CMapManager::GetMap(uint32_t dwId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_maps.find(dwId);
    return it == m_maps.end() ? nullptr : it->second;
}

std::shared_ptr<CGameMap> CMapManager::GetOrCreate(uint32_t dwId, const std::string& name) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto& pMap = m_maps[dwId];
    if (!pMap) pMap = std::make_shared<CGameMap>(dwId, name);
    return pMap;
}

void CMapManager::RegisterDefaultMaps() {
    // base 6159-family maps (id, name) - full list loads from GameMap config later
    GetOrCreate(1000, "Desert");
    GetOrCreate(1001, "Canyon");
    GetOrCreate(1002, "Twin City");
    GetOrCreate(1015, "Bird Island");
    GetOrCreate(1020, "Ape Mountain");
}

bool CMapManager::Broadcast(uint32_t dwMapId, const void* pBuf, uint16_t usLen, uint32_t dwExceptId) {
    auto pMap = GetMap(dwMapId);
    if (!pMap) return false;
    bool bSent = false;
    for (uint32_t dwId : pMap->GetUserIds()) {
        if (dwId == dwExceptId) continue;
        auto pUser = CUserManager::Instance().GetUser(dwId);
        if (pUser) { pUser->SendMsg(pBuf, usLen); bSent = true; }
    }
    return bSent;
}
