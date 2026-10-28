#ifndef C_MSG_ROULETTE_PLAYER_BET_H
#define C_MSG_ROULETTE_PLAYER_BET_H
// 1404ddb30 CMsgRoulettePlayerBet::Create(seat)
//   seat > 4 -> "CMsgRoulettePlayerBet::Create failed, seat num is
//               error, seat num:%u."  (only the low byte of the RAW
//               return is defined: 0)
//   +0x0c = 2; +0x08 = 0xafa; buf = *(u8**)(this+0x428);
//   buf[1] = 0; buf[0] = seat; return 1
#include <cstdint>
#include <cstddef>
namespace msg {
class CMsgRoulettePlayerBet {
public:
    struct Seams {
        void (*LogBadSeat)(unsigned seat);
    };
    int Create(uint8_t seat, Seams& s);
    uint8_t m_Pad0[8] = {};
    int32_t m_nMsgId = 0;                         // +0x08 = 0xafa
    int32_t m_nKind  = 0;                         // +0x0c = 2
    uint8_t m_Pad1[0x418] = {};
    uint8_t* m_pBody = nullptr;                   // +0x428
};
}
#endif
