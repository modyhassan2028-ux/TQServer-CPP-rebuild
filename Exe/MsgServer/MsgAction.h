#pragma once
#include "Msg.h"

#pragma pack(push, 1)
struct ActionData {
    uint32_t dwTime;
    uint32_t dwId;
    uint32_t dwData;
    uint16_t usX;
    uint16_t usY;
    uint32_t dwAction;
};
#pragma pack(pop)

class CMsgAction : public tq::CMsg {
public:
    enum ActionType {
        Action_ChangeDir = 79,
        Action_Jump = 137,
        Action_GetItem = 138,
        Action_ChgMap = 85,
        Action_PostCmd = 100
    };

    CMsgAction();
    bool Create(uint32_t dwId, uint32_t dwData, uint16_t usX, uint16_t usY, ActionType action);
    void Process(uint32_t dwSender) override;
};