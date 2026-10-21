#pragma once
#include "Monster.h"
#include <map>
#include <vector>
#include <mutex>
#include <atomic>
#include <memory>
#include <condition_variable>

// Monster world manager: spawn tables, AI tick thread (roam + respawn).
// v1 spawn table is built-in; loading the original cq monster config is on the roadmap.
class CMonsterManager {
public:
    static CMonsterManager& Instance();

    void Start();   // spawns default monsters + starts the AI thread
    void Stop();

    std::vector<std::shared_ptr<CMonster>> GetMapMonsters(uint32_t dwMapId);

private:
    CMonsterManager() = default;
    void SpawnDefaults();
    void AILoop();
    void Roam(std::shared_ptr<CMonster> pMonster);
    void Respawn(std::shared_ptr<CMonster> pMonster);

    std::map<uint32_t, std::vector<std::shared_ptr<CMonster>>> m_byMap;
    std::mutex m_mutex;
    std::atomic<bool> m_bRunning{ false };
    uint32_t m_dwNextId{ 400000000 }; // monster ids start above user ids
};
