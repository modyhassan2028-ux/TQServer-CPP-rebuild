#pragma once
#include <cstdint>
#include <string>
#include <map>
#include <cstdint>
#include <vector>
#include <map>

// Lightweight v1 item record. Real item types/sort/status bitfields come
// from the original cq_item / itemtype tables when the DB layer ports.
struct ItemInfo {
    uint32_t    dwId{0};       // unique runtime item id
    uint32_t    dwType{0};     // itemtype id
    uint32_t    dwData{0};     // ORIGINAL item data (gem grade/+n/...): with dwType it is the (type,data) container key
    uint16_t    usSort{0};     // 0=consumable, 1=weapon, 2=armor ... (v1)
    uint32_t    dwAmount{1};
    uint32_t    dwPosition{255}; // inventory slot / equip position
    uint8_t     ucPlus{0};        // refinement level +0..+12
    uint16_t    usEnchant{0};    // enchant: bonus life added by gems (0..2048)
    uint16_t    usDurability{1000}; // wear: 1000 = pristine, damage halves below 200
    std::string strName;
    // ORIGINAL action attr engine (FUN_1400fda10 get / FUN_140104140 set):
    // attr 1 = type (proven: class digit checks read GetAttr(1)), attr 2 = id,
    // attr 0x13 = equipment lock status (gmlog special case). The full
    // cq_item column binding ports with the item-attr subsystem; ids without a
    // typed field keep exact per-id fidelity through this map.
    std::map<uint32_t, int64_t> mapActionAttr;

    int64_t GetActionAttr(uint32_t dwAttr) const {
        switch (dwAttr) {
            case 1: return (int64_t)dwType;   // ORIGINAL attr(1,1) = type
            case 2: return (int64_t)dwId;     // ORIGINAL attr(2,1) = id
            default: {
                auto it = mapActionAttr.find(dwAttr);
                return it == mapActionAttr.end() ? 0 : it->second;
            }
        }
    }
    void SetActionAttr(uint32_t dwAttr, int64_t v) {
        switch (dwAttr) {
            case 1: dwType = (uint32_t)v; break;
            case 2: dwId = (uint32_t)v; break;
            default: mapActionAttr[dwAttr] = v; break;
        }
    }
};

inline uint32_t MakeItemId(uint32_t dwSeq) { return 700000000 + dwSeq; }

// cq_itemtype record (original NpcServer model): the type library every
// item creation looks up - name/sort/price come from data, not code.
struct ItemTypeDef {
    uint32_t    dwType{0};
    std::string strName;
    uint16_t    usSort{0};     // 0=consumable, 1=weapon, 2=armor ...
    uint32_t    dwPrice{0};
};

// cq_dropitemrule record: what a monster type may drop on death
struct DropRule {
    uint32_t dwItemType{0};
    uint32_t dwChance{100}; // percent
};

// cq_itemaddition record: stat bonuses an EQUIPPED item grants
struct ItemAddition {
    uint32_t dwLife{0};
    uint32_t dwAttack{0};
};

class CItemLibrary {
public:
    static CItemLibrary& Instance();
    // original model: SELECT id, name, sort, price FROM cq_itemtype
    uint32_t LoadFromDB(class CMySQLClient* pDB);
    // fallback: data/items.ini ("type | name | sort | price")
    uint32_t LoadFromFile(const std::string& path);
    const ItemTypeDef* Lookup(uint32_t dwType) const;
    // numbered shop listing with prices ("1. Sword - 1000 money" per line)
    std::string ShopListText() const;
    const std::map<uint32_t, ItemTypeDef>& GetAllTypes() const { return m_types; }
    size_t Size() const { return m_types.size(); }
    // applies name+sort from the library (keeps item fields when type unknown)
    void Apply(ItemInfo& item) const;

    // cq_itemaddition: equipment bonuses
    uint32_t LoadAdditionsFromDB(class CMySQLClient* pDB);
    uint32_t LoadAdditionsFromFile(const std::string& path); // data/itemadditions.ini: type|life|attack
    // cq_itemaddition is per-plus: rows are (type, plus) and the bonus at +N
    // is the SUM of rows for plus 1..N (a single plus-1 row acts as per-level)
    ItemAddition AdditionBonusAt(uint32_t dwType, uint8_t ucPlus) const;

    // cq_dropitemrule: monster drops (monster_type -> rules)
    uint32_t LoadDropsFromDB(class CMySQLClient* pDB);
    const std::vector<DropRule>* GetDropRules(uint32_t dwMonsterType) const;

private:
    CItemLibrary() = default;
    std::map<uint32_t, ItemTypeDef> m_types;
    std::map<uint32_t, std::map<int, ItemAddition>> m_additions; // type -> plus -> bonus
    std::map<uint32_t, std::vector<DropRule>> m_drops;
};
