#pragma once
#include "GameMap.h"
#include <map>
#include <memory>
#include <mutex>

// World map registry. v1: built-in base maps with free movement;
// real .dmap/.map loading from the original data files is on the roadmap.
class CMapManager {
public:
    static CMapManager& Instance();

    std::shared_ptr<CGameMap> GetMap(uint32_t dwId);
    std::shared_ptr<CGameMap> GetOrCreate(uint32_t dwId, const std::string& name);

    // scan <mapDir> recursively for .DMap files and index them by map id
    void ScanDMaps(const std::string& mapDir = "map");
    void RegisterDefaultMaps();

    // send a packet to every user on a map (optionally skipping one id)
    bool Broadcast(uint32_t dwMapId, const void* pBuf, uint16_t usLen, uint32_t dwExceptId = 0);

private:
    CMapManager() = default;
    std::map<uint32_t, std::shared_ptr<CGameMap>> m_maps;
    std::mutex m_mutex;
    std::unordered_map<uint32_t, std::string> m_dmapFiles;
    bool m_bScanned{false};
};
