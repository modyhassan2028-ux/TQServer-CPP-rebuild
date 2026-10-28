#ifndef C_CONNECT_USER_H
#define C_CONNECT_USER_H
// 140073740 CConnectUser::SetType(int type)
//   type == 0 -> +0x7c = 0, +0x78 = 0, +0x34 = 0, return 0
//   type != 1 -> "CConnectUser::SetType, wrong type: %d"
//                (RAW returns an undefined register value)
//   type == 1 -> +0x78 = 0x14; u = TimeGet(0); +0x34 = 1;
//                +0x7c = u / 1000;
//                return ((uint32)u * 0x10624dd3) & 0xffffffff
//                (a 32-bit magic-number artifact of RAW, kept as is)
#include <cstdint>
#include <cstddef>
namespace msg {
class CConnectUser {
public:
    struct Seams {
        uint32_t (*TimeGet)(int mode);
        void (*LogWrongType)(int type);
    };
    uint64_t SetType(int type, Seams& s);
    uint8_t  m_Pad0[0x34] = {};
    int32_t  m_nType    = 0;                      // +0x34
    uint8_t  m_Pad1[0x40] = {};
    int32_t  m_nMode    = 0;                      // +0x78 (0x14 on type 1)
    uint32_t m_nTickSec = 0;                      // +0x7c
};
}
#endif
