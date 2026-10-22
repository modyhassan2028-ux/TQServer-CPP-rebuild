#include "MonsterManager.h"
#include "MsgUserAttrib.h"
#include "BattleSystem.h"
#include "MySQLClient.h"
#include "Account.h"
#include "MapManager.h"
#include "MsgTalk.h"
#include "GameMap.h"
#include "MsgMonster.h"
#include "MapManager.h"
#include "MsgTalk.h"
#include "UserManager.h"

#include <thread>
#include <chrono>
#include <cstdlib>
#include <cstdio>

CMonsterManager& CMonsterManager::Instance() {
    static CMonsterManager s_instance;
    return s_instance;
}


// ORIGINAL 6159 model (NpcServer.exe loads the same tables):
//   cq_monstertype: id, name, level, life, attack_max, attack_min, defence
//   cq_generator:   npctype, mapid, bound_x, bound_y, bound_cx, bound_cy, maxnpc, rest_secs
bool CMonsterManager::HasMonsterType(uint32_t dwType) {
    // ORIGINAL: table lookup cq_monstertype (Transform2 error path)
    if (m_loadedTypeIds.empty()) return true; // config not loaded yet: permissive
    return m_loadedTypeIds.count(dwType) != 0;
}

uint32_t CMonsterManager::SpawnFromDB(CMySQLClient* pDB) {
    if (!pDB) return 0;
    // 1) monster types (original columns)
    struct TypeDef { std::string name; uint32_t level, life, attack, defense; };
    std::map<uint32_t, TypeDef> types; // id -> def
    if (!pDB->Query("SELECT id, name, level, life, attack_max, attack_min, defence FROM cq_monstertype")) {
        printf("[MONSTER] cq_monstertype load failed: %s\n", pDB->GetError().c_str());
        return 0;
    }
    for (auto& row : pDB->GetRows()) {
        if (row.size() < 7) continue;
        TypeDef d;
        uint32_t id = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        d.name = row[1];
        d.level = (uint32_t)strtoul(row[2].c_str(), nullptr, 10);
        d.life = (uint32_t)strtoul(row[3].c_str(), nullptr, 10);
        d.attack = (uint32_t)strtoul(row[4].c_str(), nullptr, 10); // attack_max
        d.defense = (uint32_t)strtoul(row[6].c_str(), nullptr, 10); // defence
        types[id] = d;
    }
    if (types.empty()) return 0;
    // 2) generators: original bound-rect spawn rules
    if (!pDB->Query("SELECT npctype, mapid, bound_x, bound_y, bound_cx, bound_cy, maxnpc, rest_secs "
                    "FROM cq_generator ORDER BY id")) {
        printf("[MONSTER] cq_generator load failed: %s\n", pDB->GetError().c_str());
        return 0;
    }
    uint32_t spawned = 0;
    for (auto& row : pDB->GetRows()) {
        if (row.size() < 7) continue;
        uint32_t typeId = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        uint32_t mapId  = (uint32_t)strtoul(row[1].c_str(), nullptr, 10);
        uint32_t count  = (uint32_t)strtoul(row[6].c_str(), nullptr, 10); // maxnpc
        uint16_t x0 = (uint16_t)strtoul(row[2].c_str(), nullptr, 10);    // bound_x
        uint16_t y0 = (uint16_t)strtoul(row[3].c_str(), nullptr, 10);    // bound_y
        uint16_t x1 = (uint16_t)(x0 + strtoul(row[4].c_str(), nullptr, 10)); // + bound_cx
        uint16_t y1 = (uint16_t)(y0 + strtoul(row[5].c_str(), nullptr, 10)); // + bound_cy
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
            auto p = std::make_shared<CMonster>(m_dwNextId++, typeId, def.name);
            p->SetMapId(mapId);
            p->SetSpawn(spawnX, spawnY);
            p->SetLevel(def.level);
            p->SetLife(def.life);
            p->SetMaxLife(def.life);
            p->SetAttack(def.attack);
            p->SetDefense(def.defense);
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
    auto it = m_crossRespawn.find(pMonster->GetId());
    if (pMonster->IsCross() && it != m_crossRespawn.end())
        m_respawnCountdown[pMonster->GetId()] = it->second;
    else
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
            // aggro first: a player within 5 cells gets attacked (2s tick = cooldown)
            Aggro(pM);
            // chase: a player within 7 cells but out of melee range pulls the
            // monster one step closer every tick (visible via the jump packet)
            if (!Chase(pM) && std::rand() % 4 == 0) Roam(pM);
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

// v1 aggro: alive monster attacks any player within 5 cells on its map.
// (visual chase + pathing comes with the port of the original MsgMonster walk)
void CMonsterManager::Aggro(std::shared_ptr<CMonster> pM) {
    if (!pM || !pM->IsAlive()) return;
    auto pMap = CMapManager::Instance().GetMap(pM->GetMapId());
    if (!pMap) return;
    if (pMap->IsSafeZone()) return; // monsters hold their fire in safe zones
    for (auto pUser : CUserManager::Instance().GetAllUsers()) {
        if (!pUser || pUser->GetMapId() != pM->GetMapId() || pUser->GetLife() == 0) continue;
        int dx = (int)pUser->GetX() - (int)pM->GetX();
        int dy = (int)pUser->GetY() - (int)pM->GetY();
        if (dx * dx + dy * dy > 25) continue; // 5-cell aggro radius

        uint32_t back = CBattleSystem::Instance().CalcPlayerDamage(pM.get(), pUser.get());
        uint32_t life = pUser->GetLife() > back ? pUser->GetLife() - back : 0;
        pUser->SetLife(life);
        std::vector<AttribPair> attribs = { { CMsgUserAttrib::Attrib_Life, life } };
        CMsgUserAttrib m;
        if (m.Create(pUser->GetId(), attribs))
            CMapManager::Instance().Broadcast(pM->GetMapId(), m.GetBuf(), m.GetSize());
        if (life == 0) {
            pUser->SetLife(pUser->GetMaxLife());
            pUser->Teleport(1002, 315, 275);
            pUser->SendSysMsg("You were slain by " + pM->GetName() +
                              " and revived in Twin City.");
            pM->SetLife(pM->GetMaxLife());
            printf("[AI] %s slew %s\n", pM->GetName().c_str(), pUser->GetName().c_str());
        }
        return; // one target per tick
    }
}

// visual chase: the nearest player within 7 sight cells (but beyond the
// 5-cell melee range) pulls the monster one step closer per tick. Returns
// false when nobody is in sight so roaming can take over. Leash is 15 cells
// from the spawn point; beyond that the monster gives up and holds ground.
bool CMonsterManager::Chase(std::shared_ptr<CMonster> pM) {
    if (!pM || !pM->IsAlive()) return false;
    auto pMap = CMapManager::Instance().GetMap(pM->GetMapId());
    if (!pMap) return false;
    std::shared_ptr<CUser> pTarget;
    long best = 0;
    for (auto pUser : CUserManager::Instance().GetAllUsers()) {
        if (!pUser || pUser->GetMapId() != pM->GetMapId() || pUser->GetLife() == 0) continue;
        long dx = (long)pUser->GetX() - (long)pM->GetX();
        long dy = (long)pUser->GetY() - (long)pM->GetY();
        long d2 = dx * dx + dy * dy;
        if (d2 > 49) continue;              // sight radius: 7 cells
        if (d2 <= 25) continue;              // already in melee range: aggro handles it
        if (!pTarget || d2 < best) { pTarget = pUser; best = d2; }
    }
    if (!pTarget) return false;
    int stepX = pM->GetX(), stepY = pM->GetY();
    int tx = pTarget->GetX(), ty = pTarget->GetY();
    if (tx != stepX) stepX += (tx > stepX) ? 1 : -1;
    if (ty != stepY) stepY += (ty > stepY) ? 1 : -1;
    if (stepX < 0 || stepY < 0) return false;
    // leash: never stray more than 15 cells from the spawn point
    if (stepX < (int)pM->GetSpawnX() - 15 || stepX > (int)pM->GetSpawnX() + 15 ||
        stepY < (int)pM->GetSpawnY() - 15 || stepY > (int)pM->GetSpawnY() + 15)
        return true;                        // holding ground is still "in chase"
    if (!pMap->IsPassable(static_cast<uint16_t>(stepX), static_cast<uint16_t>(stepY))) {
        // blocked straight ahead: try the two axis-only alternatives
        if (pMap->IsPassable(static_cast<uint16_t>(pM->GetX() + (tx > (int)pM->GetX() ? 1 : -1)),
                             pM->GetY()) &&
            tx != pM->GetX())
            stepY = pM->GetY();
        else if (ty != pM->GetY() &&
                 pMap->IsPassable(pM->GetX(),
                                 static_cast<uint16_t>(pM->GetY() + (ty > (int)pM->GetY() ? 1 : -1))))
            stepX = pM->GetX();
        else return true;                    // wedged: wait for the player to move
    }
    pM->SetPos(static_cast<uint16_t>(stepX), static_cast<uint16_t>(stepY));
    uint8_t dir = 0;
    int dx = tx - stepX, dy = ty - stepY;
    if (dx > 0 && dy == 0) dir = 2; else if (dx < 0 && dy == 0) dir = 6;
    else if (dx == 0 && dy > 0) dir = 4; else if (dx == 0 && dy < 0) dir = 0;
    else if (dx > 0 && dy > 0) dir = 3; else if (dx < 0 && dy > 0) dir = 5;
    else if (dx > 0 && dy < 0) dir = 1; else dir = 7;
    pM->SetDir(dir);

    CMsgMonsterJump jump;
    if (jump.Create(pM->GetId(), pM->GetX(), pM->GetY(), pM->GetDir()))
        CMapManager::Instance().Broadcast(pM->GetMapId(), jump.GetBuf(), jump.GetSize());
    return true;
}

// spawn the hourly world boss in Twin City with a world announcement.
// boss = 20x the XP of a normal kill and flags a guaranteed drop bonus.
// cq_cross_monster: JOIN cq_monstertype for stats, spawn on the realm map.
// Cross beasts respawn on their own cq-configured cadence.
uint32_t CMonsterManager::SpawnCrossFromDB(CMySQLClient* pDB) {
    if (!pDB) return 0;
    if (!pDB->Query("SELECT c.map_id, c.count, c.x, c.y, c.respawn_secs, c.cp_reward, "
                    "t.name, t.level, t.life, t.attack_max, t.defence "
                    "FROM cq_cross_monster c JOIN cq_monstertype t ON t.id = c.type_id")) {
        printf("[CROSS] cq_cross_monster load failed: %s\n", pDB->GetError().c_str());
        return 0;
    }
    // runs after Start(): the AI thread is live, guard the map
    std::lock_guard<std::mutex> lock(m_mutex);
    uint32_t dwSpawned = 0;
    for (auto& row : pDB->GetRows()) {
        if (row.size() < 9) continue;
        uint32_t dwMapId  = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        uint32_t dwCount  = (uint32_t)strtoul(row[1].c_str(), nullptr, 10);
        uint16_t usX      = (uint16_t)strtoul(row[2].c_str(), nullptr, 10);
        uint16_t usY      = (uint16_t)strtoul(row[3].c_str(), nullptr, 10);
        uint32_t dwResp   = (uint32_t)strtoul(row[4].c_str(), nullptr, 10);
        uint32_t dwCp     = (uint32_t)strtoul(row[5].c_str(), nullptr, 10);
        const std::string& strName = row[6];
        uint32_t dwLevel  = (uint32_t)strtoul(row[7].c_str(), nullptr, 10);
        uint32_t dwLife   = (uint32_t)strtoul(row[8].c_str(), nullptr, 10);
        uint32_t dwAtk    = row.size() > 9 ? (uint32_t)strtoul(row[9].c_str(), nullptr, 10) : 10;
        uint32_t dwDef    = row.size() > 10 ? (uint32_t)strtoul(row[10].c_str(), nullptr, 10) : 2;
        for (uint32_t i = 0; i < dwCount && dwCount < 50; ++i) {
            auto p = std::make_shared<CMonster>(m_dwNextId++, 0, strName);
            p->SetMapId(dwMapId);
            p->SetSpawn(usX, usY);
            p->SetLevel(dwLevel);
            p->SetLife(dwLife);
            p->SetMaxLife(dwLife);
            p->SetAttack(dwAtk);
            p->SetDefense(dwDef);
            p->SetCross(true);
            p->SetCrossCp(dwCp);
            // cross respawn cadence (fallback 60s)
            m_crossRespawn[p->GetId()] = dwResp ? dwResp / 2 : 30; // AI ticks are 2s
            m_byMap[dwMapId].push_back(p);
            ++dwSpawned;
        }
    }
    if (dwSpawned)
        printf("[CROSS] %u cross-realm beasts spawned from cq_cross_monster\n", dwSpawned);
    return dwSpawned;
}

void CMonsterManager::SpawnBoss() {
    auto pMap = CMapManager::Instance().GetMap(1002);
    uint16_t x = 550, y = 480;
    if (pMap && pMap->HasRealCollision()) {
        uint32_t rx = 0, ry = 0;
        if (pMap->RandomWalkableCell(rx, ry)) { x = (uint16_t)rx; y = (uint16_t)ry; }
    }
    auto p = std::make_shared<CMonster>(m_dwNextId++, 999, "TerraDragon");
    p->SetMapId(1002);
    p->SetSpawn(x, y);
    p->SetLevel(50);
    p->SetLife(50000);
    p->SetMaxLife(50000);
    p->SetBoss(true);
    m_byMap[1002].push_back(p);
    // world announcement
    CMsgTalk note;
    if (note.Create("SYSTEM", "", "The TerraDragon has appeared in Twin City! Great rewards await...",
                    CMsgTalk::Channel_Broadcast))
        CMapManager::Instance().BroadcastToAll(note.GetBuf(), note.GetSize());
    printf("[BOSS] TerraDragon spawned at 1002 (%u,%u)\n", x, y);
}
