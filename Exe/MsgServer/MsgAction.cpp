#include "MsgAction.h"
#include "UserManager.h"

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
    const auto* pData = reinterpret_cast<const ActionData*>(m_buffer.data() + sizeof(tq::MsgHead));
    if (pData->dwAction == Action_Jump) {
        user->SetPos(pData->usX, pData->usY);
    }
}