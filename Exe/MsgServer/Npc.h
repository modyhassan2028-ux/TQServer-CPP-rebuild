#pragma once
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include <cstdint>

class CUser;

// NPC system v1.
// The original 6159 NPC/dialog flow (CMsgNpc + task scripts) ports on top of
// this core later; v1 NPCs are fully functional server-side via interact ids
// and chat commands.

struct NpcOption {
    enum class Action { Heal, BankBalance, BankDeposit, BankWithdraw, Teleport, Chat,
                         AcceptTask, TurnInTask };
    Action action{Action::Chat};
    std::string text;       // shown in the numbered menu
    // hunt task the option assigns (AcceptTask)
    uint32_t dwTaskMonsterType{0}, dwTaskCount{0}, dwTaskMoney{0}, dwTaskCp{0};

    // teleport destination
    uint32_t dwDestMap{0};
    uint16_t usDestX{0}, usDestY{0};
};

class CNpc {
public:
    enum class Type {
        Healer,      // restores life
        Warehouse,   // bank storage
        Teleporter   // sends the player to a fixed destination
    };

    CNpc(uint32_t dwId, const std::string& name, Type type,
         uint32_t dwMapId, uint16_t usX, uint16_t usY);

    uint32_t GetId() const { return m_dwId; }
    const std::string& GetName() const { return m_name; }
    Type GetType() const { return m_type; }
    uint32_t GetMapId() const { return m_dwMapId; }
    uint16_t GetX() const { return m_usX; }
    uint16_t GetY() const { return m_usY; }
    uint32_t GetLookface() const { return m_dwLookface; }
    uint16_t GetDir() const { return m_usDir; }

    uint32_t m_dwLookface{0}; // client c3 mesh id (placeholder values until matched to the client ini)
    uint16_t m_usDir{2};

    // teleporter destination (only meaningful for Type::Teleporter)
    uint32_t m_dwDestMap{0};
    uint16_t m_usDestX{0};
    uint16_t m_usDestY{0};

    std::vector<NpcOption> m_options; // numbered dialog menu

    // dialog text shown on interaction
    std::string m_strDialog;

    void Interact(std::shared_ptr<CUser> pUser); // shows the greeting + numbered menu
    // player picked option n (1-based); returns false if out of range
    bool ChooseOption(std::shared_ptr<CUser> pUser, uint32_t dwIndex);

private:
    uint32_t m_dwId;
    std::string m_name;
    Type m_type;
    uint32_t m_dwMapId;
    uint16_t m_usX;
    uint16_t m_usY;
};

class CNpcManager {
public:
    static CNpcManager& Instance();

    // spawn the default v1 NPC roster (Twin City + Desert loop)
    void SpawnDefaults();

    std::shared_ptr<CNpc> GetNpc(uint32_t dwId);
    std::vector<std::shared_ptr<CNpc>> GetNpcsOnMap(uint32_t dwMapId);

    // warehouse (bank) operations, shared by /bank chat commands and the NPC
    bool BankDeposit(std::shared_ptr<CUser> pUser, uint32_t dwAmount);
    bool BankWithdraw(std::shared_ptr<CUser> pUser, uint32_t dwAmount);

    static constexpr uint32_t NPC_ID_BASE = 4000000;

private:
    CNpcManager() = default;
    std::map<uint32_t, std::shared_ptr<CNpc>> m_npcs;
    std::mutex m_mutex;
    bool m_bSpawned{false};
};
