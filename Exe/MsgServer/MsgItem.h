#pragma once
#include "Msg.h"

#pragma pack(push, 1)
struct ItemActionData {
    uint32_t dwId;
    uint32_t dwData;
    uint32_t dwAction;
    uint32_t dwParam;
};
#pragma pack(pop)

class CMsgItem : public tq::CMsg {
public:
    enum ItemAction {
        Action_Buy = 1,
        Action_Sell = 2,
        Action_Drop = 3,
        Action_Use = 4,
        Action_Equip = 5,
        Action_Unequip = 6
    };

    CMsgItem();
    bool Create(uint32_t dwId, uint32_t dwData, ItemAction action, uint32_t dwParam = 0);
    void Process(uint32_t dwSender) override;
};