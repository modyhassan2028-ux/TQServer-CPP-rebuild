#include "CrossMsgAction.h"

CCrossMsgAction::CCrossMsgAction() = default;

bool CCrossMsgAction::Create(uint32_t dwServerId, uint32_t dwUserId, uint32_t dwAction, uint64_t qwData) {
    tq::MsgHead head;
    head.type = 3001; // CrossMsgAction Packet ID
    head.length = sizeof(tq::MsgHead) + sizeof(CrossActionData);

    CrossActionData data{};
    data.dwServerId = dwServerId;
    data.dwUserId = dwUserId;
    data.dwAction = dwAction;
    data.qwData = qwData;

    m_buffer.resize(head.length);
    std::memcpy(m_buffer.data(), &head, sizeof(head));
    std::memcpy(m_buffer.data() + sizeof(head), &data, sizeof(data));

    m_nType = head.type;
    m_nSize = head.length;
    return true;
}

void CCrossMsgAction::Process(uint32_t) {}