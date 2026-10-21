#pragma once
#include <cstdint>
#include <string>
#include <vector>

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
