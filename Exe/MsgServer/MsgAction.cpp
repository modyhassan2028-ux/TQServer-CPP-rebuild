#include "MsgAction.h"
#include "UserManager.h"
#include "MapManager.h"

CMsgAction::CMsgAction() = default;

bool CMsgAction::Create(uint32_t dwId, uint32_t dwData, uint16_t usX, uint16_t usY, ActionType action) {
    tq::MsgHead head;
    head.type = 1010; // MsgAction Packet ID
    head.length = sizeof(tq::MsgHead) + sizeof(ActionData);

    ActionData data{};
    data.dwId = dwId;
    data.dwData = dwData;
    data.usX = usX;
    data.usY = usY;
    data.dwAction = static_cast<uint32_t>(action);

    m_buffer.resize(head.length);
    std::memcpy(m_buffer.data(), &head, sizeof(head));
    std::memcpy(m_buffer.data() + sizeof(head), &data, sizeof(data));

    m_nType = head.type;
    m_nSize = head.length;
    return true;
}

void CMsgAction::Process(uint32_t dwSender) {
    auto user = CUserManager::Instance().GetUser(dwSender);
    if (!user) return;
    if (m_buffer.size() < sizeof(tq::MsgHead) + sizeof(ActionData)) return;
    const auto* pData = reinterpret_cast<const ActionData*>(m_buffer.data() + sizeof(tq::MsgHead));

    auto pOldMap = CMapManager::Instance().GetMap(user->GetMapId());

    switch (pData->dwAction) {
    case Action_Jump: { // 137: jump - validate target tile then move
        auto pMap = CMapManager::Instance().GetMap(user->GetMapId());
        if (!pMap || !pMap->IsPassable(pData->usX, pData->usY)) return;
        user->SetPos(pData->usX, pData->usY);
        break;
    }
    case Action_ChgMap: { // 85: map change - dwData = target map id
        uint32_t dwTargetMap = pData->dwData;
        auto pNewMap = CMapManager::Instance().GetOrCreate(dwTargetMap, "Map" + std::to_string(dwTargetMap));
        if (!pNewMap->IsPassable(pData->usX, pData->usY)) return;
        if (pOldMap) pOldMap->RemoveUser(user->GetId());
        user->SetMapId(dwTargetMap);
        user->SetPos(pData->usX, pData->usY);
        pNewMap->AddUser(user);
        printf("[MAP] User %s moved to map %u at (%u,%u)\n",
               user->GetName().c_str(), dwTargetMap, pData->usX, pData->usY);
        break;
    }
    default:
        // other actions (change dir, get item...) are accepted as-is in v1
        user->SetPos(pData->usX, pData->usY);
        break;
    }

    // acknowledge the action back to the sender
    user->SendMsg(GetBuf(), GetSize());

    // let everyone else on the same map see the movement
    CMapManager::Instance().Broadcast(user->GetMapId(), GetBuf(), GetSize(), user->GetId());
}
