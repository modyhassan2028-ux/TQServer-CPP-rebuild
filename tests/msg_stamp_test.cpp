// MsgServer unit M17 - the server stamp
// FUN_140508740 / FUN_1405086f0
#include "../Exe/MsgServer/Port/MsgServerStamp.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstddef>
using namespace msg;

int main() {
    // ===== the VERBATIM layout =====
    static_assert(sizeof(MsgServerStamp) == 0x54,
        "the 0x54 memset block");
    static_assert(offsetof(MsgServerStamp, sDate)
        == 0x00, "DAT_1409766d0");
    static_assert(offsetof(MsgServerStamp, tm)
        == 0x0c, "DAT_1409766dc");
    static_assert(offsetof(MsgServerStamp,
        uTimeGet) == 0x40, "DAT_140976710");
    static_assert(offsetof(MsgServerStamp, uA)
        == 0x4c, "DAT_14097671c");
    static_assert(offsetof(MsgServerStamp, uB)
        == 0x4e, "DAT_14097671e");
    static_assert(offsetof(MsgServerStamp, uSeed)
        == 0x50, "DAT_140976720");

    int nTimeArg = -1;
    MsgServerStampData d;
    d.m_fnTimeGet = [&](int n) {
        nTimeArg = n; return 0x5f5e1000u; };
    d.m_fnGetSeed = []{ return 0x11223344u; };

    // ===== the init over a pre-dirtied stamp
    MsgServerStamp s;
    std::memset(&s, 0xAB, sizeof(s));
    MsgServerStampInit(s, d, 0x1234, 0x5678);
    // the full 0x54 zeroed then the fields
    assert(nTimeArg == 1);   // TimeGet(1)
    assert(s.uTimeGet == 0x5f5e1000);
    assert(s.uA == 0x1234 && s.uB == 0x5678);
    assert(s.uSeed == 0x11223344);
    // the empty-string parse: tm all zeros,
    // the date text untouched-but-zeroed
    for (int i = 0; i < 9; ++i)
        assert(s.tm[i] == 0);
    for (int i = 0; i < 0xc; ++i)
        assert(s.sDate[i] == '\0');
    // the padding stays zeroed
    for (int i = 0; i < 0x10; ++i)
        assert(s.pad0[i] == 0);
    for (int i = 0; i < 0x8; ++i)
        assert(s.pad1[i] == 0);

    // ===== the stub =====
    assert(MsgServerStampStub() == 1);

    printf("MSG_SERVER_STAMP_OK: FUN_140508740 "
           "VERBATIM (the 0x54 memset over the "
           "DAT_1409766d0 block, the 0x71c/0x71e "
           "u16 stores, tq::TimeGet(1) to "
           "0x140976710, the empty-string date "
           "parse kept LITERAL, the 0x140976720 "
           "seed) + FUN_1405086f0 (returns 1) - "
           "layout validated with static_assert "
           "offsets\n");
    return 0;
}
