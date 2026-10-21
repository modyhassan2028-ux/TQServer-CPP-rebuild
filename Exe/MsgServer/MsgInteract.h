#pragma once
#include "Msg.h"
#include <cstdint>

// Packet 1022 (0x3FE) - MsgInteract, 40 bytes total.
// Layout extracted from decompiled v6159 CMsgInteract::Create:
// Create(usAction, idTarget, dwData, usX, usY, dwData2, dwData3, idSender)
// head(4) + timestamp + sender + target + data + x + y + action + pad + data2 + data3 + zero.

#pragma pack(push, 1)
struct InteractData { // 36 bytes after MsgHead
    uint32_t dwTimeStamp; // +4
    uint32_t dwSenderId;  // +8
    uint32_t dwTargetId;  // +12
    uint32_t dwData;      // +16 (carries damage on responses)
    uint16_t usX;         // +20
    uint16_t usY;         // +22
    uint16_t usAction;    // +24
    uint16_t usPad;       // +26
    uint32_t dwData2;     // +28
    uint32_t dwData3;     // +32
    uint32_t dwZero;      // +36
};
#pragma pack(pop)

class CMsgInteract : public tq::CMsg {
public:
    CMsgInteract() = default;

    bool Create(uint16_t usAction, uint32_t dwTargetId, uint32_t dwData,
                uint16_t usX, uint16_t usY, uint32_t dwSenderId);

    void Process(uint32_t dwSender) override;

    // wire accessors for received packets
    uint16_t GetAction() const;
    uint32_t GetSenderId() const;
    uint32_t GetTargetId() const;
    uint16_t GetX() const;
    uint16_t GetY() const;

private:
    InteractData m_data{};
};
