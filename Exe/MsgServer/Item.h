#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <map>

// Lightweight v1 item record. Real item types/sort/status bitfields come
// from the original cq_item / itemtype tables when the DB layer ports.
struct ItemInfo {
    uint32_t    dwId{0};       // unique runtime item id
    uint32_t    dwType{0};     // itemtype id
    uint16_t    usSort{0};     // 0=consumable, 1=weapon, 2=armor ... (v1)
    uint32_t    dwAmount{1};
    uint32_t    dwPosition{255}; // inventory slot / equip position
    std::string strName;
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

class CItemLibrary {
public:
    static CItemLibrary& Instance();
    // original model: SELECT id, name, sort, price FROM cq_itemtype
    uint32_t LoadFromDB(class CMySQLClient* pDB);
    // fallback: data/items.ini ("type | name | sort | price")
    uint32_t LoadFromFile(const std::string& path);
    const ItemTypeDef* Lookup(uint32_t dwType) const;
    size_t Size() const { return m_types.size(); }
    // applies name+sort from the library (keeps item fields when type unknown)
    void Apply(ItemInfo& item) const;

private:
    CItemLibrary() = default;
    std::map<uint32_t, ItemTypeDef> m_types;
};
