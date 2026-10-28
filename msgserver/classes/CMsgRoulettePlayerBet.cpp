// 1404ddb30
#include "CMsgRoulettePlayerBet.h"
namespace msg {
int CMsgRoulettePlayerBet::Create(uint8_t seat, Seams& s) {
    if (seat > 4) {
        s.LogBadSeat(seat);
        return 0;                 // RAW defines only the low byte: 0
    }
    m_nKind  = 2;
    m_nMsgId = 0xafa;
    m_pBody[1] = 0;
    m_pBody[0] = seat;
    return 1;
}
}
