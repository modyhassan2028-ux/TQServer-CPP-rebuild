#include "GroundItems.h"
#include "User.h"
#include "Item.h"
#include <thread>
#include <chrono>
#include <cstdio>

CGroundItemManager& CGroundItemManager::Instance() {
    static CGroundItemManager s_instance;
    return s_instance;
}

void CGroundItemManager::Start() {
    if (m_bRunning) return;
    m_bRunning = true;
    std::thread([this]() {
        while (m_bRunning) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            Tick();
        }
    }).detach();
    printf("[DROPS] Ground item thread started.\n");
}

void CGroundItemManager::Stop() { m_bRunning = false; }

void CGroundItemManager::Tick() {
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto it = m_drops.begin(); it != m_drops.end(); ) {
        if (it->second.dwTicksLeft > 0) --it->second.dwTicksLeft;
        if (it->second.dwTicksLeft == 0) {
            printf("[DROPS] Drop %u (%s) despawned.\n",
                   it->first, it->second.strName.c_str());
            it = m_drops.erase(it);
        } else ++it;
    }
}

void CGroundItemManager::OnMonsterDeath(uint32_t dwMapId, uint16_t usX, uint16_t usY,
                                        uint32_t dwMonsterLevel) {
    std::lock_guard<std::mutex> lock(m_mutex);
    GroundDrop d;
    d.dwDropId = NextId();
    d.dwMapId = dwMapId;
    d.usX = usX;
    d.usY = usY;
    d.qwMoney = 20 + dwMonsterLevel * 25;          // bounty on the floor
    if (std::rand() % 100 < 15) {                   // 15% pill drop
        d.dwItemType = 725013;                     // original Healing Pill type id
        d.dwAmount = 1 + std::rand() % 3;
        d.strName = "HealingPill x" + std::to_string(d.dwAmount);
    } else {
        d.strName = "Money " + std::to_string(d.qwMoney);
    }
    m_drops[d.dwDropId] = d;
    printf("[DROPS] %s fell on map %u (%u,%u).\n",
           d.strName.c_str(), dwMapId, usX, usY);
}

std::string CGroundItemManager::Pick(std::shared_ptr<CUser> pUser) {
    if (!pUser) return "No player.";
    uint32_t best = 0;
    int bestDist = 10; // > 3 cells squared (9)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (auto& kv : m_drops) {
            auto& d = kv.second;
            if (d.dwMapId != pUser->GetMapId()) continue;
            int dx = (int)d.usX - (int)pUser->GetX();
            int dy = (int)d.usY - (int)pUser->GetY();
            int dist = dx * dx + dy * dy;
            if (dist < bestDist) { bestDist = dist; best = kv.first; }
        }
    }
    if (best == 0) return "Nothing to pick up nearby. (/drops to look)";
    GroundDrop d;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        auto it = m_drops.find(best);
        if (it == m_drops.end()) return "Someone grabbed it first.";
        d = it->second;
        m_drops.erase(it);
    }
    if (d.dwItemType != 0) {
        ItemInfo info;
        info.dwType = d.dwItemType;
        info.usSort = 50;                       // usable stack
        info.dwAmount = d.dwAmount;
        info.strName = d.strName;
        info.dwPosition = 255;
        pUser->AddItem(info);
    }
    if (d.qwMoney > 0) pUser->AddMoney(d.qwMoney);
    pUser->SendSysMsg("Picked up " + d.strName + ".");
    return "";
}

std::string CGroundItemManager::ListNearby(std::shared_ptr<CUser> pUser) {
    if (!pUser) return "No player.";
    std::string out;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        for (auto& kv : m_drops) {
            auto& d = kv.second;
            if (d.dwMapId != pUser->GetMapId()) continue;
            int dx = (int)d.usX - (int)pUser->GetX();
            int dy = (int)d.usY - (int)pUser->GetY();
            if (dx * dx + dy * dy > 400) continue;   // within 20 cells
            out += "\n  " + d.strName + " at (" + std::to_string(d.usX) + "," +
                   std::to_string(d.usY) + ")";
        }
    }
    return out.empty() ? "No drops nearby." : "Drops nearby:" + out;
}

size_t CGroundItemManager::GetDropCount() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_drops.size();
}

// a slain player drops 10% of carried money at the corpse (original model:
// red-name deaths drop items; money-only keeps v1 simple and fair)
void CGroundItemManager::OnPlayerDeath(std::shared_ptr<CUser> pVictim) {
    if (!pVictim) return;
    uint64_t qwLoss = pVictim->GetMoney() / 10;
    if (qwLoss == 0) return;
    pVictim->AddMoney(-(int64_t)qwLoss);
    std::lock_guard<std::mutex> lock(m_mutex);
    GroundDrop d;
    d.dwDropId = NextId();
    d.dwMapId = pVictim->GetMapId();
    d.usX = pVictim->GetX();
    d.usY = pVictim->GetY();
    d.qwMoney = qwLoss;
    d.strName = "Money " + std::to_string(qwLoss);
    m_drops[d.dwDropId] = d;
    printf("[DROPS] %s dropped %llu money at their corpse.\n",
           pVictim->GetName().c_str(), (unsigned long long)qwLoss);
}
