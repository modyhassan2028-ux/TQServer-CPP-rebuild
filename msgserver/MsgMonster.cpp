#include "MsgMonster.h"
#include <cstring>

bool CMsgMonsterInfo::Create(uint32_t dwId, uint32_t dwLookface, uint16_t usX, uint16_t usY, uint8_t ucDir) {
    tq::MsgHead head;
    head.type = 20001; // 0x4E21 - from decompiled CMsgMonsterInfo::Create
    head.length = sizeof(tq::MsgHead) + sizeof(MonsterInfoData); // 56 bytes total

    MonsterInfoData data{};
    data.dwId = dwId;
    data.dwLookface = dwLookface;
    data.usX = usX;
    data.usY = usY;
    data.usCount = 1;          // original Create checks this == 1
    data.ucDir = ucDir;

    m_buffer.resize(head.length);
    std::memcpy(m_buffer.data(), &head, sizeof(head));
    std::memcpy(m_buffer.data() + sizeof(head), &data, sizeof(data));

    m_nType = head.type;
    m_nSize = head.length;
    return true;
}

void CMsgMonsterInfo::Process(uint32_t) {}

bool CMsgMonsterJump::Create(uint32_t dwId, uint16_t usX, uint16_t usY, uint16_t usData) {
    tq::MsgHead head;
    head.type = 20002; // 0x4E22 - from decompiled CMsgMonsterJump::Create
    head.length = sizeof(tq::MsgHead) + sizeof(MonsterJumpData); // 12 bytes total

    MonsterJumpData data{};
    data.dwId = dwId;
    data.usX = usX;
    data.usY = usY;
    data.usData = usData;

    m_buffer.resize(head.length);
    std::memcpy(m_buffer.data(), &head, sizeof(head));
    std::memcpy(m_buffer.data() + sizeof(head), &data, sizeof(data));

    m_nType = head.type;
    m_nSize = head.length;
    return true;
}

void CMsgMonsterJump::Process(uint32_t) {}
