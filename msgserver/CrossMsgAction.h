#pragma once
#include "Msg.h"

#pragma pack(push, 1)
struct CrossActionData {
    uint32_t dwServerId;
    uint32_t dwUserId;
    uint32_t dwTargetId;
    uint32_t dwAction;
    uint64_t qwData;
};
#pragma pack(pop)

class CCrossMsgAction : public tq::CMsg {
public:
    CCrossMsgAction();
    bool Create(uint32_t dwServerId, uint32_t dwUserId, uint32_t dwAction, uint64_t qwData);
    void Process(uint32_t dwSender) override;
};