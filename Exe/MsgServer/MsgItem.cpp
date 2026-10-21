#include "MsgItem.h"
#include "UserManager.h"

CMsgItem::CMsgItem() = default;

bool CMsgItem::Create(uint32_t dwId, uint32_t dwData, ItemAction action, uint32_t dwParam) {
    tq::MsgHead head;
    head.type = 1009; // MsgItem Packet ID
    head.length = sizeof(tq::MsgHead) + sizeof(ItemActionData);

    ItemActionData data{};
    data.dwId = dwId;
    data.dwData = dwData;
    data.dwAction = static_cast<uint32_t>(action);
    data.dwParam = dwParam;

    m_buffer.resize(head.length);
    std::memcpy(m_buffer.data(), &head, sizeof(head));
    std::memcpy(m_buffer.data() + sizeof(head), &data, sizeof(data));

    m_nType = head.type;
    m_nSize = head.length;
    return true;
}

void CMsgItem::Process(uint32_t dwSender) {
    auto user = CUserManager::Instance().GetUser(dwSender);
    if (!user) return;
}