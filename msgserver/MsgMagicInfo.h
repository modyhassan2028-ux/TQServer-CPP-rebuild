#pragma once
#include "Msg.h"
#include <cstdint>

// ============================================================================
// ORIGINAL CMsgMagicInfo (opcode 0x44f = 1103), server->client magic record
// update. Ported from FUN_140457240 (Create) + FUN_140456f30 (ctor) +
// FUN_140456f80 (dtor). Payload (post 4-byte tq::MsgHead, original
// buf-relative offsets):
//   +0x00 time        (u32) tq::TimeGet(0)
//   +0x08 magic type  (u32) param_3  (0 -> error log + false)
//   +0x0e mode        (u16) param_2
//   +0x10 effect      (u8)  param_4
//   +0x14 data5       (u32) param_5
//   +0x18 data6       (u32) param_6
// size 0x1c (28).
// Observed modes: 4 (effect attach, FUN_14048c7e0), 6 (effect drop,
// FUN_14048c4c0).
// ============================================================================
class CMsgMagicInfo : public tq::CMsg {
public:
    static constexpr uint32_t OPCODE = 1103;     // ORIGINAL *(int*)(this+8) = 0x44f
    static constexpr uint32_t SIZE  = 0x1c;      // ORIGINAL *(int*)(this+0xc) = 0x1c

    CMsgMagicInfo();

    bool Create(uint16_t usMode, uint32_t dwMagicType, uint8_t byEffect,
                uint32_t dwData5, uint32_t dwData6);

    void Process(uint32_t dwSender) override;
};
