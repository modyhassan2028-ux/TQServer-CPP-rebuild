#include "MsgData.h"
#include <cstring>
#include <ctime>

bool CMsgData::Create(uint32_t dwYear, uint32_t dwMon, uint32_t dwSec, uint32_t dwMin,
                     uint32_t dwHour, uint32_t dwMday, uint32_t dwYday) {
    tq::MsgHead head;
    head.type = 1033; // 0x409 - ORIGINAL FUN_1403a6a30
    head.length = sizeof(tq::MsgHead) + sizeof(MsgDataBody);

    MsgDataBody b{};
    b.dwTime = static_cast<uint32_t>(time(nullptr));
    b.byP2 = 0;       // ORIGINAL case 0x80 passes 0
    b.dwP3 = dwYear;   // +8
    b.dwP4 = dwMon;    // +0xc
    b.dwP5 = dwSec;    // +0x10
    b.dwP6 = dwMin;    // +0x14
    b.dwP7 = dwHour;   // +0x18
    b.dwP8 = dwMday;   // +0x1c
    b.dwP9 = dwYday;   // +0x20

    m_buffer.resize(head.length);
    std::memcpy(m_buffer.data(), &head, sizeof(head));
    std::memcpy(m_buffer.data() + sizeof(head), &b, sizeof(b));
    m_nType = head.type;
    m_nSize = head.length;
    return true;
}
