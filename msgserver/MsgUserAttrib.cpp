#include "MsgUserAttrib.h"

CMsgUserAttrib::CMsgUserAttrib() = default;

bool CMsgUserAttrib::Create(uint32_t dwId, const std::vector<AttribPair>& attribs) {
    tq::MsgHead head;
    head.type = 10017; // 0x2721 CMsgUserAttrib - dispatcher at decompiled.c:196539 + Create at 112185
    uint32_t dataSize = 4 + 4 + static_cast<uint32_t>(attribs.size() * sizeof(AttribPair));
    head.length = sizeof(tq::MsgHead) + dataSize;

    m_buffer.resize(head.length);
    std::memcpy(m_buffer.data(), &head, sizeof(head));
    
    char* pData = m_buffer.data() + sizeof(head);
    std::memcpy(pData, &dwId, 4);
    uint32_t count = static_cast<uint32_t>(attribs.size());
    std::memcpy(pData + 4, &count, 4);

    if (!attribs.empty()) {
        std::memcpy(pData + 8, attribs.data(), attribs.size() * sizeof(AttribPair));
    }

    m_nType = head.type;
    m_nSize = head.length;
    return true;
}

void CMsgUserAttrib::Process(uint32_t) {}