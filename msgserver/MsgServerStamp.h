// ============================================================
// MsgServer strict port - unit M17
// ORIGINAL: FUN_140508740 @ 140508740
//  the server-stamp initializer over the
//  DAT_1409766d0..0x724 block (0x54 bytes)
//  FUN_1405086f0 @ 1405086f0: returns 1
// Layout (VERBATIM offsets from 0x1409766d0):
//  +0x00 sDate[0xc]   the date text
//  +0x0c tm[9]        the struct tm
//  +0x40 uTimeGet     (tq::TimeGet(1))
//  +0x4c uA, +0x4e uB (the two undefined2
//                      params)
//  +0x50 uSeed        (FUN_1405082d0, the
//                     machine fingerprint)
// The LITERAL flow:
//  memset(&DAT_1409766d0, 0, 0x54);
//  _DAT_14097671c = p1; _DAT_14097671e = p2;
//  _DAT_140976710 = tq::TimeGet(1);
//  FUN_140508070(&DAT_1409766dc,
//               &DAT_1409766d0, 0xc);
//  DAT_140976720 = FUN_1405082d0();
// (the parse runs on the JUST-ZEROED text -
// an empty-string parse, kept LITERAL)
// ============================================================
#pragma once
#include <cstdint>
#include <functional>

namespace msg {

struct MsgServerStamp {   // base 0x1409766d0
    char sDate[0xc];      // +0x00
    int tm[9];            // +0x0c
    uint8_t pad0[0x10];   // +0x30
    uint32_t uTimeGet;    // +0x40
    uint8_t pad1[0x8];    // +0x44
    uint16_t uA;          // +0x4c
    uint16_t uB;          // +0x4e
    uint32_t uSeed;       // +0x50
};                        // total 0x54

struct MsgServerStampData {
    // tq::TimeGet(1)
    std::function<uint32_t(int)> m_fnTimeGet;
    // FUN_1405082d0 (the machine seed)
    std::function<uint32_t()> m_fnGetSeed;
};

// ===== ORIGINAL FUN_140508740 @ 140508740
void MsgServerStampInit(MsgServerStamp& rS,
                        MsgServerStampData& rD,
                        uint16_t uP1,
                        uint16_t uP2);

// ===== ORIGINAL FUN_1405086f0 @ 1405086f0
uint64_t MsgServerStampStub(void);

} // namespace msg
