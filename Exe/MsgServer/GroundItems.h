#pragma once
#include <cstdint>
#include <memory>
#include <map>
#include <mutex>
#include <string>
#include <vector>

class CUser;

// v1 ground drops: a killed monster leaves its bounty on the floor at the
// kill spot instead of paying the killer directly - anyone can /pick it up.
// Original model ports the MsgMapItem (1101/1102) packets with the visual;
// for now drops are listed via /drops and collected with /pick.
struct GroundDrop {
    uint32_t dwDropId{0};
    uint32_t dwMapId{0};
    uint16_t usX{0}, usY{0};
    uint64_t qwMoney{0};
    uint32_t dwItemType{0};     // 0 = pure money pile
    uint32_t dwAmount{1};       // stack count for usable items
    std::string strName;
    uint32_t dwTicksLeft{60};   // ~2s per tick => despawn after ~2 min
};

class CGroundItemManager {
public:
    static CGroundItemManager& Instance();

    void Start();                       // despawn tick thread
    void Stop();
    // monster death -> money scaled by level + 15% chance of a pill drop
    void OnMonsterDeath(uint32_t dwMapId, uint16_t usX, uint16_t usY, uint32_t dwMonsterLevel);
    // slain player drops 10% of carried money at the corpse
    void OnPlayerDeath(std::shared_ptr<CUser> pVictim);
    // pick the nearest drop within 3 cells; returns an error message or ""
    std::string Pick(std::shared_ptr<CUser> pUser);
    std::string ListNearby(std::shared_ptr<CUser> pUser);   // /drops
    // split a picked money pile across same-map team members
    void TeamShare(std::shared_ptr<CUser> pPicker, uint64_t qwMoney);
    size_t GetDropCount();

private:
    CGroundItemManager() = default;
    void Tick();
    uint32_t NextId() { return ++m_dwNextId; }

    std::map<uint32_t, GroundDrop> m_drops;
    uint32_t m_dwNextId{0};
    std::mutex m_mutex;
    bool m_bRunning{false};
};
