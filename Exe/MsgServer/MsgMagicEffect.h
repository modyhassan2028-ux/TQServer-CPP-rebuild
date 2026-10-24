#pragma once
#include "Msg.h"
#include <vector>
#include <cstdint>

// ============================================================================
// ORIGINAL CMsgMagicEffect (opcode 0x451 = 1105). objdump-verified ports of:
//   FUN_140386800 Create (attacker, type, level, dir, target, flag)
//   FUN_1403868f0 Create + first target entry (8f0 layout)
//   FUN_140386bd0 Create (target id at +4 byte variant)
//   FUN_140386d00 AppendTarget (0x400 size cap)
//   FUN_140386e00 CreateFull (13-arg layout)
// The payload buffer starts AFTER the 4-byte tq::MsgHead. All payload offsets
// below are the ORIGINAL buf-relative offsets from the decompile; the base
// size 0x34 and the +0x20 target stride are literal. The original logs the
// DAT_1406d9c10 error string on zero attacker/target and returns false.
// ============================================================================
class CMsgMagicEffect : public tq::CMsg {
public:
    static constexpr uint32_t OPCODE = 1105;      // ORIGINAL *(int*)(this+8) = 0x451
    static constexpr uint32_t BASE_SIZE = 0x34;   // ORIGINAL *(int*)(this+0xc) = 0x34
    static constexpr uint32_t TARGET_STRIDE = 0x20;
    static constexpr uint32_t MAX_SIZE = 0x400;  // ORIGINAL append gate

    // ONE target entry, ORIGINAL per-entry payload offsets
    // (base = payload + 0x14 + count*0x20):
    //   +0x00 id, +0x04 damage, +0x08 data2, +0x10 data3,
    //   +0x14 data4, +0x18 data5, +0x1c data6; the slot AFTER the last
    //   entry is zero-terminated by the original writers.
    struct Target {
        uint32_t dwId{0};
        uint32_t dwDamage{0};
        uint32_t dwData2{0};
        uint32_t dwData3{0};
        uint32_t dwData4{0};
        uint32_t dwData5{0};
        uint32_t dwData6{0};
    };

    CMsgMagicEffect();

    // ORIGINAL FUN_140386800: attacker/target/type/level/dir/flag header.
    // Zero attacker or target -> error log + false.
    bool Create(uint32_t dwAttacker, uint32_t dwTarget, uint16_t usType,
                uint16_t usLevel, uint8_t byDir, uint8_t byFlag);

    // ORIGINAL FUN_1403868f0: header + one full target entry
    // (id, damage, data2, data6-at-+0x1c) + zero terminator, count = 1.
    bool CreateWithTarget(uint32_t dwAttacker, uint32_t dwTarget, uint16_t usType,
                          uint16_t usLevel, uint8_t byDir, uint32_t dwDamage,
                          uint32_t dwData2, uint32_t dwData6, uint8_t byFlag);

    // ORIGINAL FUN_140386d00: append a target while
    // size + 0x20 < 0x400 (else refused with false), terminator zeroed,
    // count byte incremented. Entry fields: id/damage/data2/data6
    // (the original writes param_3/param_4 at +0x18/+0x1c and param_5 at
    // +0x30 = entry +0x1c).
    bool AppendTarget(uint32_t dwId, uint32_t dwDamage, uint32_t dwData2, uint32_t dwData6);

    // ORIGINAL FUN_140386e00 CreateFull: args (attacker, target, type,
    // level, dir, dmg, d2, d3, d4, d5, d6, flag); entry fields at
    // +0x14 id / +0x18 dmg / +0x1c d2 / +0x24 d4 / +0x2c d6 / +0x30 d5 and
    // d3 written at the NEXT entry base (literal original quirk).
    bool CreateFull(uint32_t dwAttacker, uint32_t dwTarget, uint16_t usType,
                    uint16_t usLevel, uint8_t byDir, uint32_t dwDamage,
                    uint32_t dwData2, uint32_t dwData3, uint32_t dwData4,
                    uint32_t dwData5, uint32_t dwData6, uint8_t byFlag);

    // ORIGINAL FUN_140386a50 (group-broadcast create, used by
    // FUN_140486fb0 SendMagicEffectAfterProcessGroupByPos): attacker u32 at
    // +0 with the target id SPLIT as two u16 halves at +4/+6 (the caller
    // passes 0,0), type/level/dir header, count field zeroed, flag at +0x10.
    // If dwEntryId != 0 one first entry (id/dmg/d2) is written and the next
    // entry base is zero-terminated. Zero attacker -> error log + false.
    bool CreateGroup(uint32_t dwAttacker, uint16_t usType, uint16_t usLevel,
                     uint8_t byDir, uint16_t usTargetLo, uint16_t usTargetHi,
                     uint32_t dwEntryId, uint32_t dwEntryDamage,
                     uint32_t dwEntryData2, uint8_t byFlag);

    // ORIGINAL FUN_140387150 (group append): id == 0 -> error log but the
    // entry is STILL appended (no early return in the original); gate is
    // size + 0x20 < 0x400 else false with nothing written. Entry layout:
    // id +0, damage +4, data2 +8, dwNext +0x10-slot-of-the-NEXT-entry-base
    // (literal quirk: param_5 writes at (count+1)*0x20 + 0x14), then
    // dwData4 +0x10, dwData5 +0x14, dwData6 +0x18, dwData7 +0x1c of the
    // entry; count byte incremented. No separate terminator: the dwNext
    // write IS the next-base slot.
    bool AppendGroup(uint32_t dwId, uint32_t dwDamage, uint32_t dwData2,
                     uint32_t dwNext, uint32_t dwData4, uint32_t dwData5,
                     uint32_t dwData6, uint32_t dwData7);

    void Process(uint32_t dwSender) override;

    uint8_t GetTargetCount() const { return m_byCount; }
    uint32_t GetTotalSize() const { return m_dwSizeField; }

private:
    uint32_t m_dwSizeField{0};  // ORIGINAL *(int*)(this+0xc): 0x34 + 0x20*targets
    uint8_t  m_byCount{0};      // ORIGINAL payload +0xf target count byte
};
