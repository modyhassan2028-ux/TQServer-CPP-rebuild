#include "MonsterManager.h"
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
        auto p = std::make_shared<CMonster>(m_dwNextId++, s.type, s.name);
        p->SetMapId(s.map);
        p->SetSpawn(s.x, s.y);
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
    SpawnDefaults();
    m_bRunning.store(true);
    std::thread(&CMonsterManager::AILoop, this).detach();
    printf("[MONSTER] AI thread started.\n");
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
            if (!pM->IsAlive()) { Respawn(pM); continue; }
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
