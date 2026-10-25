#include "MsgServerStamp.h"
#include "MsgDateParse.h"
#include <cstring>

namespace msg {

// ===== ORIGINAL FUN_140508740 @ 140508740
void MsgServerStampInit(MsgServerStamp& rS,
                        MsgServerStampData& rD,
                        uint16_t uP1,
                        uint16_t uP2) {
    // memset(&DAT_1409766d0,0,0x54)
    std::memset(&rS, 0, 0x54);
    // _DAT_14097671c / _DAT_14097671e
    rS.uA = uP1;
    rS.uB = uP2;
    // _DAT_140976710 = tq::TimeGet(1)
    rS.uTimeGet = rD.m_fnTimeGet(1);
    // FUN_140508070(&DAT_1409766dc,
    //              &DAT_1409766d0, 0xc)
    MsgParseDate(rS.tm, rS.sDate, 0xc);
    // DAT_140976720 = FUN_1405082d0()
    rS.uSeed = rD.m_fnGetSeed();
}

// ===== ORIGINAL FUN_1405086f0 @ 1405086f0
uint64_t MsgServerStampStub(void) {
    // returns 1 (the cookie xor is the
    // stack-canary load, not a result)
    return 1;
}

} // namespace msg
