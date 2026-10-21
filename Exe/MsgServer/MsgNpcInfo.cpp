#include "MsgNpcInfo.h"
#include "StringPacker.h"

#include <cstring>
#include <cstdio>
#include <ctime>

bool CMsgNpcInfo::Create(uint32_t dwId, uint32_t dwLookface, uint16_t usX, uint16_t usY,
                        uint16_t usDir, const std::string& name) {
    tq::CStringPacker packer;
    packer.AddString(name.c_str());

    uint16_t usLength = static_cast<uint16_t>(4 + FIXED + MYSTERY_PAD + packer.GetSize());

    tq::MsgHead head;
    head.type = 2030; // 0x7ee CMsgNpcInfo
    head.length = usLength;

    m_buffer.resize(usLength);
    char* p = m_buffer.data();
    std::memcpy(p, &head, sizeof(head)); // 4 bytes: len2 + type2
    p += sizeof(head);

    uint32_t dwTime = static_cast<uint32_t>(time(nullptr));
    std::memcpy(p, &dwTime, 4); p += 4;      // timestamp (as in the original writer)
    std::memcpy(p, &dwId, 4);     p += 4;
    std::memcpy(p, &dwLookface, 4); p += 4;
    std::memcpy(p, &usX, 2);      p += 2;
    std::memcpy(p, &usY, 2);      p += 2;
    std::memcpy(p, &usDir, 2);    p += 2;
    *p++ = 0; // MYSTERY_PAD: original length formula packs 0x17 after the head
              // (19 bytes) while the writer shows 18 field bytes; the extra
              // byte is retained to match the original on-wire size exactly

    packer.SetBuf(p, packer.GetSize(), true);

    m_dwId = dwId;
    m_dwLookface = dwLookface;
    m_nType = head.type;
    m_nSize = usLength;
    return true;
}
