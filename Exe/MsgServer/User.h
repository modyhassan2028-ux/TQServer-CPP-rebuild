#pragma once
#include "Item.h"
#include "PlayerMagic.h"
#include <string>
#include <cstdint>
#include <utility>
#include <functional>
#include <vector>
#include <map>

class CGameMap;
class CNetClient;

class CUser {
public:
    CUser(uint32_t dwId);
    ~CUser();

    uint32_t GetId() const { return m_dwId; }
    const std::string& GetName() const { return m_name; }
    void SetName(const std::string& name) { m_name = name; }
    // owning cq_account id (0 = dev/flat mode, unsaved to MySQL)
    void SetAccountId(uint32_t id) { m_dwAccountId = id; }
    uint32_t GetAccountId() const { return m_dwAccountId; }

    uint16_t GetX() const { return m_usX; }
    uint16_t GetY() const { return m_usY; }
    void SetPos(uint16_t usX, uint16_t usY) { m_usX = usX; m_usY = usY; }

    uint32_t GetMapId() const { return m_dwMapId; }
    void SetMapId(uint32_t dwMapId) { m_dwMapId = dwMapId; }

    uint32_t GetLife() const { return m_dwLife; }
    uint32_t GetMaxLife() const { return m_dwMaxLife; }
    void SetMaxLife(uint32_t v) { m_dwMaxLife = v; }

    // cq_itemaddition: snapshot the un-bonused stats (call once after character
    // restore), then recalc whenever equipment changes
    void SnapshotBaseStats() { m_dwBaseMaxLife = m_dwMaxLife; m_dwBaseBP = m_dwBattlePower; }
    void RecalcEquipmentBonuses();
    void SetLife(uint32_t dwLife) { m_dwLife = dwLife; }
    void AddLife(int32_t nDelta) {
        if (nDelta < 0 && (uint32_t)(-nDelta) > m_dwLife) m_dwLife = 0;
        else m_dwLife = (uint32_t)(m_dwLife + nDelta);
    }

    uint32_t GetBattlePower() const { return m_dwBattlePower; }
    // cq_itemaddition attack granted by currently equipped gear
    uint32_t GetEquipmentAttack() const { return m_dwBattlePower - m_dwBaseBP; }
    void SetBattlePower(uint32_t dwBP) { m_dwBattlePower = dwBP; }

    // GM & Economy attributes
    uint64_t GetMoney() const { return m_dwMoney; }
    uint64_t GetBank() const { return m_dwBank; }
    void SetBank(uint64_t v) { m_dwBank = v; }
    void AddBank(int64_t delta) { if (delta >= 0) m_dwBank += (uint64_t)delta; else m_dwBank = (m_dwBank > (uint64_t)(-delta)) ? m_dwBank - (uint64_t)(-delta) : 0; }
    uint32_t GetPkPoints() const { return m_dwPkPoints; }
    void AddPkPoints(uint32_t v) { m_dwPkPoints += v; }
    void SetPkPoints(uint32_t v) { m_dwPkPoints = v; }
    bool IsRedName() const { return m_dwPkPoints >= 30; }
    // active hunt task (v1 quest system)
    bool HasActiveTask() const { return m_task.dwNeeded > 0; }
    struct Task {
        uint32_t dwNpcId{0};        // task giver to return to
        uint32_t dwMonsterType{0}; // target monster type id
        uint32_t dwNeeded{0};
        uint32_t dwDone{0};
        uint32_t dwRewardMoney{0};
        uint32_t dwRewardCp{0};
    } m_task;

    // last NPC the player talked to; digit replies route to its dialog menu
    void SetTalkingNpc(uint32_t id) { m_dwTalkingNpc = id; }
    uint32_t GetTalkingNpc() const { return m_dwTalkingNpc; }

    // ORIGINAL dialog reply state: the server registers every option
    // (102/103) shown to the player with the action id it jumps to
    // (FUN_14039d300, list capped at 20), so the client's MsgTalk answer
    // text maps back to the next action node.
    void PushDialogOption(const std::string& text, uint32_t dwActionId) {
        if (m_dialogOptions.size() < 20) m_dialogOptions.push_back({text, dwActionId});
    }
    void ClearDialogOptions() { m_dialogOptions.clear(); }
    const std::vector<std::pair<std::string, uint32_t>>& GetDialogOptions() const { return m_dialogOptions; }
    // cq_action dialog tree position (0 = no tree open)
    void SetDialogNode(uint32_t id) { m_dwDialogNode = id; }
    uint32_t GetDialogNode() const { return m_dwDialogNode; }
    void SetMoney(uint64_t money) { m_dwMoney = money; }
    void AddMoney(int64_t amount) { m_dwMoney = (amount < 0 && (uint64_t)(-amount) > m_dwMoney) ? 0 : m_dwMoney + amount; }

    uint32_t GetConquerPoints() const { return m_dwEmoney; }
    void SetConquerPoints(uint32_t cps) { m_dwEmoney = cps; }
    void AddConquerPoints(int32_t amount) { m_dwEmoney = (amount < 0 && (uint32_t)(-amount) > m_dwEmoney) ? 0 : m_dwEmoney + amount; }

    uint8_t GetLevel() const { return m_ucLevel; }
    void SetLevel(uint8_t level) { m_ucLevel = level; }

    // marriage v1: spouse name persisted in cq_user.spouse_name
    const std::string& GetSpouseName() const { return m_strSpouse; }
    void SetSpouseName(const std::string& n) { m_strSpouse = n; }

    // daily hunt quest: kills counted today, claim flag
    uint32_t GetQuestKills() const { return m_dwQuestKills; }
    void AddQuestKill() { ++m_dwQuestKills; }
    void SetQuestKills(uint32_t v) { m_dwQuestKills = v; }
    bool IsQuestClaimed() const { return m_bQuestClaimed; }
    void SetQuestClaimed(bool b) { m_bQuestClaimed = b; }
    std::string m_strQuestDay; // YYYY-MM-DD the counter belongs to

    // riding: mounted players jump for free (classic horse perk)
    bool IsRiding() const { return m_bRiding; }
    void SetRiding(bool b) { m_bRiding = b; }
    bool HasHorse() const {
        for (const auto& it : m_items)
            if (it.dwType == 750 && it.dwPosition != 255) return true; // 750 = horse
        return false;
    }

    // durability: equipped weapon wears on hits; broken steel hits at half power
    void WearWeapon() {
        for (auto& it : m_items)
            if (it.usSort == 1 && it.dwPosition == 1) { // equipped weapon slot
                if (it.usDurability > 0) --it.usDurability;
                if (it.usDurability == 200)
                    SendSysMsg("Your weapon is badly worn - /repair it soon!");
                else if (it.usDurability == 0)
                    SendSysMsg("Your weapon is broken! Damage halved until /repair.");
                break;
            }
    }
    bool WeaponIsBroken() const {
        for (const auto& it : m_items)
            if (it.usSort == 1 && it.dwPosition == 1) return it.usDurability < 200;
        return false;
    }
    // repair cost: 2 money per point of wear (min 10 if not pristine)
    uint32_t RepairCost() const {
        uint32_t cost = 0;
        for (const auto& it : m_items)
            if (it.usSort <= 2 && it.dwPosition != 255 && 1000 > it.usDurability)
                cost += (1000 - it.usDurability) * 2;
        return cost;
    }
    void DoRepair() {
        for (auto& it : m_items)
            if (it.usSort <= 2 && it.dwPosition != 255) it.usDurability = 1000;
    }

    // profession counters (ranks raise payouts): fish + mining
    uint32_t GetFishCaught() const { return m_dwFishCaught; }
    void AddFishCaught(uint32_t v) { m_dwFishCaught += v; }
    void SetFishCaught(uint32_t v) { m_dwFishCaught = v; }
    uint32_t GetOreMined() const { return m_dwOreMined; }
    void AddOreMined(uint32_t v) { m_dwOreMined += v; }
    void SetOreMined(uint32_t v) { m_dwOreMined = v; }
    // rank from a count: 0-24 Novice, 25-99 Adept, 100-299 Expert, 300+ Master
    static const char* ProfRank(uint32_t count) {
        if (count >= 300) return "Master";
        if (count >= 100) return "Expert";
        if (count >= 25) return "Adept";
        return "Novice";
    }
    static uint32_t ProfBonus(uint32_t count) { // payout multiplier in percent
        if (count >= 300) return 150;
        if (count >= 100) return 125;
        if (count >= 25) return 110;
        return 100;
    }

    // mining: channel end time (0 = idle)
    uint32_t GetMineUntil() const { return m_dwMineUntil; }
    void SetMineUntil(uint32_t t) { m_dwMineUntil = t; }

    // fishing: channel end time (0 = idle)
    uint32_t GetFishUntil() const { return m_dwFishUntil; }
    void SetFishUntil(uint32_t t) { m_dwFishUntil = t; }

    // stamina: 0..100 bar, -15 per jump, regen handled by the world tick
    uint16_t GetStamina() const { return m_usStamina; }
    void SetStamina(uint16_t v) { m_usStamina = v > 100 ? 100 : v; }
    bool SpendStamina(uint16_t v) {
        if (m_usStamina < v) return false;
        m_usStamina -= v;
        return true;
    }
    void RegenStamina(uint16_t v) { SetStamina((uint16_t)(m_usStamina + v)); }

    // daily login reward: returns true when a reward was granted (a new UTC day)
    bool GrantDailyReward();
    const std::string& GetLastRewardDay() const { return m_strLastRewardDay; }
    // daily bank interest: pays once per calendar day at login
    uint64_t GrantDailyBankInterest();
    void SetLastRewardDay(const std::string& d) { m_strLastRewardDay = d; }

    // rebirth: at level 130 /reborn restarts at 15 with permanent growth
    uint32_t GetRebornCount() const { return m_dwRebornCount; }
    // classic reborn: at level 130, reset to 15 keeping power + 30 alloc points
    // returns false with a reason string on failure
    std::string DoReborn();
    void SetRebornCount(uint32_t v) { m_dwRebornCount = v; }
    // ORIGINAL condition fields (CGameAction::ProcessActionUser case 1001)
    void SetProfession(uint16_t v) { m_wProfession = v; }
    uint16_t GetProfession() const { return m_wProfession; }
    void SetMana(uint32_t v) { m_dwMana = v; }
    uint32_t GetMana() const { return m_dwMana; }
    // metempsychosis = reborn count (cq_user column)
    uint32_t GetMetempsychosis() const { return m_dwRebornCount; }
    // ---- ORIGINAL magic record API (CPlayerMagic, ported) ----
    // FUN_14048b5f0: first record with GetAttrib(rec,2) == dwType
    CPlayerMagic* FindMagic(uint32_t dwType);
    // ORIGINAL: cq_magic rows owned by this character, loaded on login
    bool LoadMagicsFromDB(CMySQLClient* pDB);
    // FUN_1404939c0 LearnMagic(type, level, byTask): (type, level) must
    // exist in cq_magictype; already-known magic returns false (a known
    // but unlearned record just clears its unlearn flag, like original)
    bool LearnMagic(uint32_t dwType, uint32_t dwLevel);
    // FUN_14048fd10 UpLevelByTask: needs the cq_magictype (type, level+1)
    // row to exist, else logs "Can't Find Magic" and fails
    bool UpLevelMagic(uint32_t dwType);
    // FUN_140493f70 DeleteMagic(user, type, mode=0): old_level = max(
    // old_level, level), unlearn = 1 (record kept, like original)
    bool DeleteMagic(uint32_t dwType);
    uint32_t GetMagicCount() const { return (uint32_t)m_oMagics.size(); }
    // attr-0 counter (original CUser+0x88) for newly created records
    uint32_t m_dwMagicCounter{0};
    // returns an error message, or "" on success
    std::string Reborn();

    // attribute points: +3 per level, /stat str|vit allocates
    // (agi/spi come with the port of the original dodge/mana systems)
    uint32_t GetStatPoints() const { return m_dwStatPoints; }
    void SetStatPoints(uint32_t v) { m_dwStatPoints = v; }
    uint32_t GetStrength() const { return m_dwStrength; }
    uint32_t GetVitality() const { return m_dwVitality; }
    void SetStrength(uint32_t v) { m_dwStrength = v; }
    void SetVitality(uint32_t v) { m_dwVitality = v; }
    // returns an error message, or "" on success
    std::string AllocStat(const std::string& stat, uint32_t count);

    // experience + level-ups (original v6159 curve, v1 approximation:
    // exp needed for next level = 30 * level^2 + 40 * level)
    uint64_t GetExperience() const { return m_dwExperience; }
    void SetExperience(uint64_t v) { m_dwExperience = v; }
    static uint64_t ExpForLevel(uint8_t ucLevel) { return 30ull * ucLevel * ucLevel + 40ull * ucLevel; }
    // grants xp; returns the number of levels gained (stats grow per level)
    uint32_t AddExperience(uint64_t dwXp);

    uint8_t GetReborn() const { return m_ucReborn; }
    void SetReborn(uint8_t reborn) { m_ucReborn = reborn; }

    uint8_t GetVipLevel() const { return m_ucVip; }
    void SetVipLevel(uint8_t vip) { m_ucVip = vip; }

    // ---- inventory (v1) ----
    void AddItem(const ItemInfo& item) { m_items.push_back(item); }
    // eats one charge of a usable stack (by type id); false if not carried
    bool ConsumeByType(uint32_t dwType);
    // refine the equipped weapon; returns an error message or ""
    std::string UpgradeEquipped();
    ItemInfo* FindItem(uint32_t dwItemId) {
        for (auto& it : m_items) if (it.dwId == dwItemId) return &it;
        return nullptr;
    }
    void RemoveItem(uint32_t dwItemId) {
        for (size_t i = 0; i < m_items.size(); ++i)
            if (m_items[i].dwId == dwItemId) { m_items.erase(m_items.begin() + i); return; }
    }
    std::vector<ItemInfo>& GetInventory() { return m_items; }
    // warehouse: a second, bank-like bag for long-term storage
    std::vector<ItemInfo>& GetWarehouse() { return m_warehouse; }
    void WarehouseStore(ItemInfo& item) { m_warehouse.push_back(item); }
    ItemInfo* WarehouseFind(uint32_t dwItemId) {
        for (auto& it : m_warehouse) if (it.dwId == dwItemId) return &it;
        return nullptr;
    }
    void WarehouseRemove(uint32_t dwItemId) {
        for (size_t i = 0; i < m_warehouse.size(); ++i)
            if (m_warehouse[i].dwId == dwItemId) { m_warehouse.erase(m_warehouse.begin() + i); return; }
    }
    uint32_t NextItemSeq() { return ++m_dwItemSeq; }

    void BindNet(CNetClient* pNet) { m_pNet = pNet; }
    CNetClient* NetClient() const { return m_pNet; }

    bool IsGodMode() const { return m_bGodMode; }
    void SetGodMode(bool god) { m_bGodMode = god; }

    bool IsInvisible() const { return m_bInvisible; }
    void SetInvisible(bool inv) { m_bInvisible = inv; }

    void Teleport(uint32_t dwMapId, uint16_t usX, uint16_t usY);
    void SendMsg(const void* pBuf, uint16_t usSize);
    // test seam: when set, outgoing packets are captured here instead of
    // going to the socket (system tests assert on real packet bytes)
    void SetPacketSink(std::function<void(const void*, uint16_t)> sink) { m_packetSink = std::move(sink); }
    void SendSysMsg(const std::string& message);

private:
    uint32_t m_dwId{0};
    std::string m_name;
    uint32_t m_dwMapId{1002}; // Twin City default
    uint16_t m_usX{400};
    uint16_t m_usY{400};
    uint32_t m_dwLife{1000};
    uint32_t m_dwMaxLife{1000};
    uint32_t m_dwBaseMaxLife{1000};
    uint64_t m_dwExperience{0};
    uint32_t m_dwStatPoints{0};
    uint32_t m_dwStrength{0};
    uint32_t m_dwVitality{0};
    uint32_t m_dwRebornCount{0};
    uint16_t m_usStamina{100};
    std::string m_strLastRewardDay;
    std::string m_strSpouse;
    uint32_t m_dwFishUntil{0};
    uint32_t m_dwMineUntil{0};
    bool m_bRiding{false};
    uint32_t m_dwFishCaught{0};
    uint32_t m_dwOreMined{0};
    uint32_t m_dwQuestKills{0};
    bool m_bQuestClaimed{false};
    uint32_t m_dwBaseBP{100};
    uint32_t m_dwBattlePower{100};

    // Economy & Special State
    uint64_t m_dwMoney{0};
    uint64_t m_dwBank{0};
    uint32_t m_dwPkPoints{0};
    uint32_t m_dwTalkingNpc{0};
    uint32_t m_dwDialogNode{0};
    std::vector<std::pair<std::string, uint32_t>> m_dialogOptions;
    uint16_t m_wProfession{0};   // cq_user.profession (short @ +0xef4)
    uint32_t m_dwMana{0};
    std::map<uint32_t, CPlayerMagic> m_oMagics; // type -> cq_magic record
    std::function<void(const void*, uint16_t)> m_packetSink;
    uint32_t m_dwAccountId{0};
    uint32_t m_dwEmoney{0};
    uint8_t m_ucLevel{1};
    uint8_t m_ucReborn{0};
    uint8_t m_ucVip{0};
    bool m_bGodMode{false};
    bool m_bInvisible{false};
    CNetClient* m_pNet{nullptr};
    std::vector<ItemInfo> m_items;
    std::vector<ItemInfo> m_warehouse;
    uint32_t m_dwItemSeq{0};
};