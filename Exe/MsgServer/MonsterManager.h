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
class CMySQLClient;

class CMonsterManager {
public:
    static CMonsterManager& Instance();

    void Start();   // spawns default monsters + starts the AI thread
    void Stop();
    // original model: cq_monstertype + cq_generator from MySQL.
    // returns spawned count (0 -> caller keeps the built-in table)
    uint32_t SpawnFromDB(CMySQLClient* pDB);
    // cq_cross_monster: cross-realm beasts (kill announced hub-wide)
    uint32_t SpawnCrossFromDB(CMySQLClient* pDB);

    std::vector<std::shared_ptr<CMonster>> GetMapMonsters(uint32_t dwMapId);
    std::shared_ptr<CMonster> GetMonsterById(uint32_t dwMonsterId);
    // nearby player -> attack (v1 proximity, no visual chase); called by the AI tick
    void Aggro(std::shared_ptr<CMonster> pMonster);
    // step a live monster one cell toward the nearest player in sight
    bool Chase(std::shared_ptr<CMonster> pMonster);
    void OnMonsterKilled(std::shared_ptr<CMonster> pMonster); // schedules delayed respawn

public:
    // hourly world boss: big XP + guaranteed drops (classic MMORPG event)
    void SpawnBoss();

private:
    CMonsterManager() = default;
    void SpawnDefaults();
    void AILoop();
    void Roam(std::shared_ptr<CMonster> pMonster);
    void Respawn(std::shared_ptr<CMonster> pMonster);

    std::map<uint32_t, std::vector<std::shared_ptr<CMonster>>> m_byMap;
    std::mutex m_mutex;
    std::atomic<bool> m_bRunning{ false };
    uint32_t m_dwNextId{ 400000000 };
    std::map<uint32_t, int> m_respawnCountdown; // monsterId -> AI ticks left // monster ids start above user ids
    std::map<uint32_t, int> m_crossRespawn;     // cross beasts: cq respawn_secs / 2s ticks
};
