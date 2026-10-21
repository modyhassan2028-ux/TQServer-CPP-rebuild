#pragma once
#include "Item.h"
#include <string>
#include <cstdint>

class CGameMap;
class CNetClient;

class CUser {
public:
    CUser(uint32_t dwId);
    ~CUser();

    uint32_t GetId() const { return m_dwId; }
    const std::string& GetName() const { return m_name; }
    void SetName(const std::string& name) { m_name = name; }

    uint16_t GetX() const { return m_usX; }
    uint16_t GetY() const { return m_usY; }
    void SetPos(uint16_t usX, uint16_t usY) { m_usX = usX; m_usY = usY; }

    uint32_t GetMapId() const { return m_dwMapId; }
    void SetMapId(uint32_t dwMapId) { m_dwMapId = dwMapId; }

    uint32_t GetLife() const { return m_dwLife; }
    uint32_t GetMaxLife() const { return m_dwMaxLife; }
    void SetLife(uint32_t dwLife) { m_dwLife = dwLife; }

    uint32_t GetBattlePower() const { return m_dwBattlePower; }
    void SetBattlePower(uint32_t dwBP) { m_dwBattlePower = dwBP; }

    // GM & Economy attributes
    uint64_t GetMoney() const { return m_dwMoney; }
    uint64_t GetBank() const { return m_dwBank; }
    void SetBank(uint64_t v) { m_dwBank = v; }
    uint32_t GetPkPoints() const { return m_dwPkPoints; }
    void AddPkPoints(uint32_t v) { m_dwPkPoints += v; }
    void SetPkPoints(uint32_t v) { m_dwPkPoints = v; }
    bool IsRedName() const { return m_dwPkPoints >= 30; }
    void SetMoney(uint64_t money) { m_dwMoney = money; }
    void AddMoney(int64_t amount) { m_dwMoney = (amount < 0 && (uint64_t)(-amount) > m_dwMoney) ? 0 : m_dwMoney + amount; }

    uint32_t GetConquerPoints() const { return m_dwEmoney; }
    void SetConquerPoints(uint32_t cps) { m_dwEmoney = cps; }
    void AddConquerPoints(int32_t amount) { m_dwEmoney = (amount < 0 && (uint32_t)(-amount) > m_dwEmoney) ? 0 : m_dwEmoney + amount; }

    uint8_t GetLevel() const { return m_ucLevel; }
    void SetLevel(uint8_t level) { m_ucLevel = level; }

    uint8_t GetReborn() const { return m_ucReborn; }
    void SetReborn(uint8_t reborn) { m_ucReborn = reborn; }

    uint8_t GetVipLevel() const { return m_ucVip; }
    void SetVipLevel(uint8_t vip) { m_ucVip = vip; }

    // ---- inventory (v1) ----
    void AddItem(const ItemInfo& item) { m_items.push_back(item); }
    ItemInfo* FindItem(uint32_t dwItemId) {
        for (auto& it : m_items) if (it.dwId == dwItemId) return &it;
        return nullptr;
    }
    void RemoveItem(uint32_t dwItemId) {
        for (size_t i = 0; i < m_items.size(); ++i)
            if (m_items[i].dwId == dwItemId) { m_items.erase(m_items.begin() + i); return; }
    }
    std::vector<ItemInfo>& GetInventory() { return m_items; }
    uint32_t NextItemSeq() { return ++m_dwItemSeq; }

    void BindNet(CNetClient* pNet) { m_pNet = pNet; }
    CNetClient* NetClient() const { return m_pNet; }

    bool IsGodMode() const { return m_bGodMode; }
    void SetGodMode(bool god) { m_bGodMode = god; }

    bool IsInvisible() const { return m_bInvisible; }
    void SetInvisible(bool inv) { m_bInvisible = inv; }

    void Teleport(uint32_t dwMapId, uint16_t usX, uint16_t usY);
    void SendMsg(const void* pBuf, uint16_t usSize);
    void SendSysMsg(const std::string& message);

private:
    uint32_t m_dwId{0};
    std::string m_name;
    uint32_t m_dwMapId{1002}; // Twin City default
    uint16_t m_usX{400};
    uint16_t m_usY{400};
    uint32_t m_dwLife{1000};
    uint32_t m_dwMaxLife{1000};
    uint32_t m_dwBattlePower{100};

    // Economy & Special State
    uint64_t m_dwMoney{0};
    uint64_t m_dwBank{0};
    uint32_t m_dwPkPoints{0};
    uint32_t m_dwEmoney{0};
    uint8_t m_ucLevel{1};
    uint8_t m_ucReborn{0};
    uint8_t m_ucVip{0};
    bool m_bGodMode{false};
    bool m_bInvisible{false};
    CNetClient* m_pNet{nullptr};
    std::vector<ItemInfo> m_items;
    uint32_t m_dwItemSeq{0};
};