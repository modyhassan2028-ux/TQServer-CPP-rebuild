#include "MonsterManager.h"
#include "MySQLClient.h"
#include "Account.h"
#include "MapManager.h"
#include "GameMap.h"
#include "MsgMonster.h"
#include "MapManager.h"
#include "UserManager.h"

#include <thread>
#include <chrono>
#include <cstdlib>
#include <cstdio>

CMonsterManager& CMonsterManager::Instance() {
    static CMonsterManager s_instance;
    return s_instance;
}


// original 6159 model (NpcServer.exe loads the same tables):
//   cq_monstertype: id, name, level, life
//   cq_generator:   id, type_id, map_id, count, x0, y0, x1, y1
uint32_t CMonsterManager::SpawnFromDB(CMySQLClient* pDB) {
    if (!pDB) return 0;
    // 1) monster types
    std::map<uint32_t, std::pair<std::string, std::pair<uint32_t, uint32_t>>> types; // id -> (name, (level, life))
    if (!pDB->Query("SELECT id, name, level, life FROM cq_monstertype")) {
        printf("[MONSTER] cq_monstertype load failed: %s\n", pDB->GetError().c_str());
        return 0;
    }
    for (auto& row : pDB->GetRows()) {
        if (row.size() < 4) continue;
        uint32_t id = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        uint32_t level = (uint32_t)strtoul(row[2].c_str(), nullptr, 10);
        uint32_t life = (uint32_t)strtoul(row[3].c_str(), nullptr, 10);
        types[id] = { row[1], { level, life } };
    }
    if (types.empty()) return 0;
    // 2) generators (spawners), like NpcServer: mask order
    if (!pDB->Query("SELECT type_id, map_id, count, x0, y0, x1, y1 FROM cq_generator ORDER BY id")) {
        printf("[MONSTER] cq_generator load failed: %s\n", pDB->GetError().c_str());
        return 0;
    }
    uint32_t spawned = 0;
    for (auto& row : pDB->GetRows()) {
        if (row.size() < 7) continue;
        uint32_t typeId = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        uint32_t mapId  = (uint32_t)strtoul(row[1].c_str(), nullptr, 10);
        uint32_t count  = (uint32_t)strtoul(row[2].c_str(), nullptr, 10);
        uint16_t x0 = (uint16_t)strtoul(row[3].c_str(), nullptr, 10);
        uint16_t y0 = (uint16_t)strtoul(row[4].c_str(), nullptr, 10);
        uint16_t x1 = (uint16_t)strtoul(row[5].c_str(), nullptr, 10);
        uint16_t y1 = (uint16_t)strtoul(row[6].c_str(), nullptr, 10);
        auto it = types.find(typeId);
        if (it == types.end() || !count) continue;
        auto& def = it->second;
        for (uint32_t i = 0; i < count; ++i) {
            uint16_t spawnX = (uint16_t)(x0 + (x1 > x0 ? rand() % (x1 - x0 + 1) : 0));
            uint16_t spawnY = (uint16_t)(y0 + (y1 > y0 ? rand() % (y1 - y0 + 1) : 0));
            auto pMap = CMapManager::Instance().GetMap(mapId);
            if (pMap && pMap->HasRealCollision()) {
                uint32_t rx = 0, ry = 0;
                if (pMap->RandomWalkableCell(rx, ry)) { spawnX = (uint16_t)rx; spawnY = (uint16_t)ry; }
            }
            auto p = std::make_shared<CMonster>(m_dwNextId++, typeId, def.first);
            p->SetMapId(mapId);
            p->SetSpawn(spawnX, spawnY);
            p->SetLevel(def.second.first);
            p->SetLife(def.second.second);
            p->SetMaxLife(def.second.second);
            m_byMap[mapId].push_back(p);
            ++spawned;
        }
    }
    printf("[MONSTER] cq_generator: spawned %u monsters from MySQL (%zu types).\n",
           spawned, types.size());
    return spawned;
}

void CMonsterManager::SpawnDefaults() {
    // v1 built-in spawns (map, type, name, x, y, level, life).
    // Real spawn data loads from the original monster config later.
    struct SpawnDef { uint32_t map, type; const char* name; uint16_t x, y; uint32_t level, life; };
    static const SpawnDef kSpawns[] = {
        { 1002, 1,  "Pheasant",   650, 320, 1,  30 },
        { 1002, 1,  "Pheasant",   700, 380, 1,  30 },
        { 1002, 2,  "RoamingRat", 560, 400, 2,  50 },
        { 1002, 2,  "RoamingRat", 620, 450, 2,  50 },
        { 1000, 10, "SandMonk",   500, 300, 12, 400 },
        { 1001, 20, "Bandit",     400, 400, 15, 500 },
    };
    for (const auto& s : kSpawns) {
        // when the map has real terrain (.dmap), snap the spawn to a walkable cell
        uint16_t spawnX = s.x, spawnY = s.y;
        auto pMap = CMapManager::Instance().GetMap(s.map);
        if (pMap && pMap->HasRealCollision()) {
            uint32_t rx = 0, ry = 0;
            if (pMap->RandomWalkableCell(rx, ry)) { spawnX = (uint16_t)rx; spawnY = (uint16_t)ry; }
        }
        auto p = std::make_shared<CMonster>(m_dwNextId++, s.type, s.name);
        p->SetMapId(s.map);
        p->SetSpawn(spawnX, spawnY);
        p->SetLevel(s.level);
        p->SetLife(s.life);
        p->SetMaxLife(s.life);
        m_byMap[s.map].push_back(p);
    }
    printf("[MONSTER] Spawned %zu default monsters on 3 maps.\n",
           sizeof(kSpawns) / sizeof(kSpawns[0]));
}

void CMonsterManager::Start() {
    std::lock_guard<std::mutex> lock(m_mutex);
    // original data model first: cq_monstertype + cq_generator from MySQL
    uint32_t dwDbSpawned = 0;
    if (CAccountManager::Instance().IsMySQLMode())
        dwDbSpawned = SpawnFromDB(CAccountManager::Instance().GetDB());
    if (dwDbSpawned == 0) SpawnDefaults();
    m_bRunning.store(true);
    std::thread(&CMonsterManager::AILoop, this).detach();
    printf("[MONSTER] AI thread started.\n");
}

std::shared_ptr<CMonster> CMonsterManager::GetMonsterById(uint32_t dwMonsterId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto& kv : m_byMap)
        for (auto& m : kv.second)
            if (m && m->GetId() == dwMonsterId) return m;
    return nullptr;
}

void CMonsterManager::OnMonsterKilled(std::shared_ptr<CMonster> pMonster) {
    if (!pMonster) return;
    std::lock_guard<std::mutex> lock(m_mutex);
    m_respawnCountdown[pMonster->GetId()] = 8; // ~16s at 2s ticks
    printf("[MONSTER] %s (%u) died, respawn in ~16s.\n", pMonster->GetName().c_str(), pMonster->GetId());
}

void CMonsterManager::Stop() {
    m_bRunning.store(false);
}

std::vector<std::shared_ptr<CMonster>> CMonsterManager::GetMapMonsters(uint32_t dwMapId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_byMap.find(dwMapId);
    return it == m_byMap.end() ? std::vector<std::shared_ptr<CMonster>>{} : it->second;
}

void CMonsterManager::AILoop() {
    using namespace std::chrono;
    auto lastTick = steady_clock::now();
    while (m_bRunning.load()) {
        std::this_thread::sleep_for(milliseconds(500));
        auto now = steady_clock::now();
        if (duration_cast<milliseconds>(now - lastTick).count() < 2000) continue; // AI tick = 2s
        lastTick = now;

        std::vector<std::shared_ptr<CMonster>> all;
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            for (auto& kv : m_byMap)
                for (auto& m : kv.second) all.push_back(m);
        }
        for (auto& pM : all) {
            if (!pM) continue;
            if (!pM->IsAlive()) {
                std::lock_guard<std::mutex> lock(m_mutex);
                int& nLeft = m_respawnCountdown[pM->GetId()];
                if (nLeft > 0) { --nLeft; continue; }
                Respawn(pM);
                m_respawnCountdown.erase(pM->GetId());
                continue;
            }
            // 1-in-4 chance per tick to take a roam step (original AI ticks per state machine)
            if (std::rand() % 4 == 0) Roam(pM);
        }
    }
}

void CMonsterManager::Roam(std::shared_ptr<CMonster> pM) {
    int dx = (std::rand() % 7) - 3;
    int dy = (std::rand() % 7) - 3;
    int newX = pM->GetX() + dx;
    int newY = pM->GetY() + dy;
    if (newX < 0 || newY < 0) return;
    // leash: keep the monster within ~10 cells of its spawn point
    if (newX < pM->GetSpawnX() - 10 || newX > pM->GetSpawnX() + 10 ||
        newY < pM->GetSpawnY() - 10 || newY > pM->GetSpawnY() + 10) return;
    auto pMap = CMapManager::Instance().GetMap(pM->GetMapId());
    if (!pMap || !pMap->IsPassable(static_cast<uint16_t>(newX), static_cast<uint16_t>(newY))) return;
    pM->SetPos(static_cast<uint16_t>(newX), static_cast<uint16_t>(newY));
    pM->SetDir(static_cast<uint8_t>(std::rand() % 8));

    // everyone on the map sees the jump
    CMsgMonsterJump jump;
    if (jump.Create(pM->GetId(), pM->GetX(), pM->GetY(), pM->GetDir()))
        CMapManager::Instance().Broadcast(pM->GetMapId(), jump.GetBuf(), jump.GetSize());
}

void CMonsterManager::Respawn(std::shared_ptr<CMonster> pM) {
    // v1: respawn at spawn point with full life
    pM->SetLife(pM->GetMaxLife());
    pM->SetPos(pM->GetSpawnX(), pM->GetSpawnY());
    printf("[MONSTER] Monster %s (%u) respawned at (%u,%u).\n",
           pM->GetName().c_str(), pM->GetId(), pM->GetSpawnX(), pM->GetSpawnY());
}
