#pragma once
#include "Msg.h"
#include <string>
#include <vector>
#include <cstdint>

// MsgNpcInfo (type 2030 / 0x7ee) - NPC spawn announcement to the client.
// Reverse-engineered from the 6159 MsgServer CMsgNpcInfo writer
// (FUN_140454b0): [len:2][type:2][time:4][id:4][lookface:4][x:2][y:2][dir:2]
// [pad:1] followed by a TQ StringPacker block carrying the name.
// Original length formula: packerSize + 0x17 (23).

class CMsgNpcInfo : public tq::CMsg {
public:
    bool Create(uint32_t dwId, uint32_t dwLookface, uint16_t usX, uint16_t usY,
                uint16_t usDir, const std::string& name);

    void Process(uint32_t) override {}

private:
    // length must stay even-aligned with the original writer's +0x17
    static constexpr uint32_t FIXED = 18; // time4 + id4 + look4 + x2 + y2 + dir2
    static constexpr uint32_t MYSTERY_PAD = 1; // see comment in Create
    uint32_t m_dwId{0};
    uint32_t m_dwLookface{0};
};
