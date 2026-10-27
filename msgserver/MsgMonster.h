#pragma once
#include "Msg.h"
#include <cstdint>

// Wire formats extracted from the decompiled v6159 MsgServer.exe
// (CMsgMonsterInfo::Create / CMsgMonsterJump::Create pseudocode).

#pragma pack(push, 1)
struct MonsterInfoData { // 52 bytes after MsgHead (total packet = 56)
    uint32_t dwId;       // +4   monster id
    uint32_t dwLookface; // +8   look/type
    uint32_t dwData;     // +12
    uint32_t dwStatus;   // +16
    uint16_t usX;        // +20
    uint16_t usY;        // +22
    uint16_t usCount;    // +24  always 1 in Create
    uint16_t usHeld;     // +26
    uint8_t  ucDir;      // +28
    uint8_t  ucPad[23];  // +29..+51 (unknown fields zero-filled)
};
#pragma pack(pop)

class CMsgMonsterInfo : public tq::CMsg {
public:
    CMsgMonsterInfo() = default;
    bool Create(uint32_t dwId, uint32_t dwLookface, uint16_t usX, uint16_t usY, uint8_t ucDir);
    void Process(uint32_t dwSender) override;
};

#pragma pack(push, 1)
struct MonsterJumpData { // 8 bytes after MsgHead (total packet = 12)
    uint32_t dwId;   // +4 monster id
    uint16_t usX;    // +6
    uint16_t usY;    // +8
    uint16_t usData; // +10
};
#pragma pack(pop)

class CMsgMonsterJump : public tq::CMsg {
public:
    CMsgMonsterJump() = default;
    bool Create(uint32_t dwId, uint16_t usX, uint16_t usY, uint16_t usData);
    void Process(uint32_t dwSender) override;
};
