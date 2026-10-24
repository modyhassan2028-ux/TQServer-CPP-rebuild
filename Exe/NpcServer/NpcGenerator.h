// CNpcGenerator - the monster generator object of
// npcmanager.cpp; CreateNpc = ORIGINAL FUN_140061040
#pragma once
#include <stdint.h>
#include <stddef.h>
#include <functional>

namespace npc {

// generator config record (read via vcall+0x10 GetInt(i))
struct GenConfig {
    // ORIGINAL call indices recovered in FUN_140061040:
    // 1 type, 4/5/6/7/8 spawn geometry, 0xf/0x10 npc
    // fields, 0x12 bit0 = random-map mode
    std::function<int(int)> m_fnGetInt;
};

// monster-type record: vcall+0x28 -> vcall+0x40 (group id)
struct TypeRecord {
    std::function<int64_t()> m_fnGetGroup;
};

class CNpcGenerator {
public:
    // ORIGINAL FUN_140061040: CNpcGenerator::CreateNpc
    // returns 1 on success (ORIGINAL CONCAT71(...,1))
    bool CreateNpc(TypeRecord* pType, int nTypeParam);

    // object fields (ORIGINAL offsets)
    void*    m_pMap = nullptr;      // +0x28 (map object)
    int      m_nStep = 0;           // +0x1c
    int      m_nX = 0;             // +0x30 (random X)
    uint32_t m_dwBornSec = 0;       // +0x34 (TimeGet/1000)
    void*    m_pMapIdCell = nullptr; // +0x50 slot source
    uint32_t m_dwMap = 0;          // +0x50 (map id)
    uint32_t m_dwType = 0;         // +0x54 (npc type)
    uint32_t m_dwFieldF = 0;       // +0x48 (config 0xf)
    uint8_t  m_byField10 = 0;      // +0x4c (config 0x10)
    bool     m_bClosed = false;    // vcall+8 Close

    // test seams (kernel lookups)
    std::function<bool(GenConfig*, TypeRecord*, int64_t)>
        m_fnGroupFilter;                 // FUN_14005f9d0
    std::function<uint32_t()> m_fnCurrentMapId; // DAT_140102d90
    std::function<uint32_t()> m_fnRandomMapId;  // FUN_14002b2d0
    std::function<void*(uint32_t)> m_fnFindMap; // FUN_14003ca10
    std::function<void()> m_fnTailInit;          // FUN_140060e60
    std::function<int(int)> m_fnRand;            // tq::RandGet
    std::function<uint32_t()> m_fnTime;          // tq::TimeGet
    std::function<void(const char*)> m_fnLog;
    GenConfig m_cfg;
};

} // namespace npc
