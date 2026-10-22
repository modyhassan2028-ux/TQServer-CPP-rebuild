#pragma once
// ORIGINAL CMsgData (FUN_1403a6980 ctor / FUN_1403a6a30 Create), packet 0x409.
#include "Msg.h"
#include <cstdint>

#pragma pack(push, 1)
// ORIGINAL body, 36 bytes (FUN_1403a6a30 writes):
// 36 bytes: [u32 time][u8 p2@4][3 pad][u32 p3@8][u32 p4@0xc][u32 p5@0x10]
// [u32 p6@0x14][u32 p7@0x18][u32 p8@0x1c][u32 p9@0x20]
struct MsgDataBody {
    uint32_t dwTime;
    uint8_t  byP2;
    uint8_t  byPad[3]; // ORIGINAL: u8 @+4, next field starts @+8
    uint32_t dwP3;
    uint32_t dwP4;
    uint32_t dwP5;
    uint32_t dwP6;
    uint32_t dwP7;
    uint32_t dwP8;
    uint32_t dwP9;
};
#pragma pack(pop)

class CMsgData : public tq::CMsg {
public:
    CMsgData() = default;
    // ORIGINAL FUN_1403a6a30(buf, 0, year, mon, sec, min, hour, mday, yday)
    bool Create(uint32_t dwYear, uint32_t dwMon, uint32_t dwSec, uint32_t dwMin,
                uint32_t dwHour, uint32_t dwMday, uint32_t dwYday);
    void Process(uint32_t dwSender) override {}
};
