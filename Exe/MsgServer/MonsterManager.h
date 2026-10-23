#pragma once
#include "Monster.h"
#include <map>
#include <vector>
#include <mutex>
#include <atomic>
#include <memory>
#include <condition_variable>
#include <set>

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
    // cq_action 2006 (case 0x7d6): dynamic monster spawn; returns 0 on a
    // name collision (ORIGINAL FUN_14008a1d0 path)
    std::shared_ptr<CMonster> SpawnDynamic(uint32_t dwMapId, uint16_t usX, uint16_t usY,
                                            uint32_t dwTypeId, uint32_t dwGenId,
                                            const std::string& strName);
    std::shared_ptr<CMonster> FindMonsterByName(const std::string& strName);
    // whole-registry scans (cq_action 2002/2009 iterate the map object tree)
    std::vector<std::shared_ptr<CMonster>> GetAllMonsters();
    // ORIGINAL FUN_14038e270(record,1): guards record+0x154 == 0 (live),
    // then detaches the monster from its map + the registry. The
    // (record+0x10 monster) vcall+0x60(6,0) disappear packet ports with
    // the monster-packet subsystem (documented open in PORTING_LOG).
    bool RemoveMonster(std::shared_ptr<CMonster> p);

    // nearby player -> attack (v1 proximity, no visual chase); called by the AI tick
    void Aggro(std::shared_ptr<CMonster> pMonster);
    // step a live monster one cell toward the nearest player in sight
    bool Chase(std::shared_ptr<CMonster> pMonster);
    void OnMonsterKilled(std::shared_ptr<CMonster> pMonster); // schedules delayed respawn
    // ORIGINAL Transform2 lookup: cq_monstertype existence (loaded ids set)
    bool HasMonsterType(uint32_t dwType);

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
    std::set<uint32_t> m_loadedTypeIds; // cq_monstertype ids seen by SpawnFromDB
    std::map<uint32_t, int> m_crossRespawn;     // cross beasts: cq respawn_secs / 2s ticks
};
