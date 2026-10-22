#pragma once
#include "Msg.h"

#pragma pack(push, 1)
// ORIGINAL FUN_140362620 (CMsgAction::Create) body layout, 28 bytes:
// [u32 time][u32 id][u32 data(p7)][4 reserved][u32 action(p8)]
// [u16 p6][u16 p5][u16 x(p3)][u16 y(p4)]
// The original client->server validator reads the action at body+0x10
// (values 0x89=137 jump, 0x55=85 chgmap, 0xb1=177).
struct ActionData {
    uint32_t dwTime;
    uint32_t dwId;
    uint32_t dwData;      // ORIGINAL param_7
    uint32_t dwReserved;  // ORIGINAL leaves body+0x0c unwritten (0)
    uint32_t dwAction;    // ORIGINAL param_8, the action code @+0x10
    uint16_t usP6;        // ORIGINAL param_6 @+0x14
    uint16_t usP5;        // ORIGINAL param_5 (direction) @+0x16
    uint16_t usX;         // ORIGINAL param_3 @+0x18
    uint16_t usY;         // ORIGINAL param_4 @+0x1a
};
#pragma pack(pop)

class CMsgAction : public tq::CMsg {
public:
    enum ActionType {
        Action_ChangeDir = 79,
        Action_Jump = 137,
        Action_GetItem = 138,
        Action_ChgMap = 85,
        Action_PostCmd = 100,
        // ORIGINAL cq_action OS-side sends (cases 0x7c/0x7e/0x83):
        Action_ScreenEffect = 116,   // 0x74: case 124, mapgroup in data
        Action_Shockwave = 159,      // 0x9f: case 126
        Action_UpdateStatus = 162    // 0xa2: case 131, (x,y) from param
    };

    CMsgAction();
    // ORIGINAL FUN_140362620 Create(id, x=p3, y=p4, dir=p5, p6, data=p7, action=p8)
    bool Create(uint32_t dwId, uint16_t usX, uint16_t usY, uint8_t byDir,
                uint16_t usP6, uint32_t dwData, ActionType action);
    void Process(uint32_t dwSender) override;
};