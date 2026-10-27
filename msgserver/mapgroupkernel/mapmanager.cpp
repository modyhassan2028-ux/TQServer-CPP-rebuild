#include "MapManager.h"
#include "User.h"
#include "MySQLClient.h"
#include "UserManager.h"
#include "DMap.h"
#include <filesystem>
#include <cstdio>

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
    if (!m_bScanned) ScanDMaps();
    auto itD = m_dmapFiles.find(dwId);

    std::lock_guard<std::mutex> lock(m_mutex);
    auto& pMap = m_maps[dwId];
    if (!pMap) {
        pMap = std::make_shared<CGameMap>(dwId, name);
        if (itD != m_dmapFiles.end())
            pMap->LoadCollision(itD->second); // real terrain from the original .DMap
        pMap->SetSafeZone(dwId == 1002); // Twin City: PK-safe city
    }
    return pMap;
}

// ORIGINAL: the map-doc materializes a CGameMap per cq_map row (id, name).
// Safe zone = Twin City (1002) as before the full flag dword is ported.
uint32_t CMapManager::LoadMapsFromDb(CMySQLClient* pDB) {
    if (!pDB) return 0;
    if (!pDB->Query("SELECT id, name FROM cq_map")) {
        printf("[MAP] cq_map load failed: %s\n", pDB->GetError().c_str());
        return 0;
    }
    uint32_t n = 0;
    for (auto& row : pDB->GetRows()) {
        if (row.size() < 2) continue;
        uint32_t id = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        if (!id) continue;
        GetOrCreate(id, row[1]);
        ++n;
    }
    printf("[MAP] cq_map loaded: %u map(s).\n", n);
    return n;
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

// scan a directory tree for .DMap files; index by the map id in the header
void CMapManager::ScanDMaps(const std::string& mapDir) {
    namespace fs = std::filesystem;
    std::error_code ec;
    if (!fs::exists(mapDir, ec) || ec) {
        printf("[DMAP] Directory '%s' not found - running with synthetic passability.\n", mapDir.c_str());
        m_bScanned = true;
        return;
    }
    for (fs::recursive_directory_iterator it(mapDir, ec), end; it != end && !ec; it.increment(ec)) {
        if (!it->is_regular_file(ec)) continue;
        std::string ext = it->path().extension().string();
        for (char& c : ext) c = char(::tolower((unsigned char)c));
        if (ext != ".dmap") continue;
        uint32_t dwId = 0;
        if (CDMap::PeekMapId(it->path().string(), dwId))
            m_dmapFiles[dwId] = it->path().string();
    }
    m_bScanned = true;
    printf("[DMAP] Indexed %zu DMap file(s).\n", m_dmapFiles.size());
}

// world broadcast: deliver the packet to every online user
bool CMapManager::BroadcastToAll(const void* pBuf, uint16_t usLen) {
    bool any = false;
    for (auto& pU : CUserManager::Instance().GetAllUsers()) {
        if (pU) { pU->SendMsg(pBuf, usLen); any = true; }
    }
    return any;
}
