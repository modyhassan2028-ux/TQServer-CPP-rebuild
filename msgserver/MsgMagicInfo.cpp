#include <ctime>
#include "MsgMagicInfo.h"
#include <cstring>
#include "Log.h" // tq::MyLogSave; TimeGet = time(nullptr) convention

CMsgMagicInfo::CMsgMagicInfo() = default;

bool CMsgMagicInfo::Create(uint16_t usMode, uint32_t dwMagicType, uint8_t byEffect,
                           uint32_t dwData5, uint32_t dwData6) {
    // ORIGINAL: type == 0 -> log DAT_1406d9c10 + 0
    if (dwMagicType == 0) {
        tq::MyLogSave("gmlog/all", "Create MagicInfo packet failed.");
        return false;
    }
    m_buffer.assign(SIZE, 0);
    auto w32 = [&](uint32_t off, uint32_t v) { std::memcpy(m_buffer.data() + off, &v, 4); };
    auto w16 = [&](uint32_t off, uint16_t v) { std::memcpy(m_buffer.data() + off, &v, 2); };
    auto w8  = [&](uint32_t off, uint8_t v)  { m_buffer.data()[off] = (char)v; };
    w32(0x00, (uint32_t)time(nullptr)); // ORIGINAL buf+0 = TimeGet(0)
    w32(0x08, dwMagicType);
    w16(0x0e, usMode);
    w8 (0x10, byEffect);
    w32(0x14, dwData5);
    w32(0x18, dwData6);
    m_nType = OPCODE;
    m_nSize = SIZE;
    return true;
}

void CMsgMagicInfo::Process(uint32_t) {
    // server->client only in the original
}
