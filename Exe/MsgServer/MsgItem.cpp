#include "MsgItem.h"
#include "User.h"
#include "UserManager.h"
#include "MapManager.h"
#include "MsgUserAttrib.h"

#include <cstring>
#include <cstdio>

bool CMsgItem::Create(const ItemInfo& item, uint16_t usAction, uint32_t dwData) {
    tq::MsgHead head;
    head.type = 1009; // 0x3F1
    head.length = sizeof(tq::MsgHead) + sizeof(ItemData); // 87 bytes

    m_data = ItemData{};
    m_data.dwIdItem = item.dwId;
    m_data.dwData = dwData;
    m_data.dwData2 = item.dwAmount;
    m_data.usAction = usAction;
    m_data.dwParam = item.dwPosition;
    // v1 attribute block: type, sort, amount, position + zeros
    m_data.dwAttrs[0] = item.dwType;
    m_data.dwAttrs[1] = item.usSort;
    m_data.dwAttrs[2] = item.dwAmount;
    m_data.dwAttrs[3] = item.dwPosition;

    m_buffer.resize(head.length);
    std::memcpy(m_buffer.data(), &head, sizeof(head));
    std::memcpy(m_buffer.data() + sizeof(head), &m_data, sizeof(m_data));

    m_nType = head.type;
    m_nSize = head.length;
    return true;
}

void CMsgItem::Process(uint32_t dwSender) {
    if (m_buffer.size() < sizeof(tq::MsgHead) + sizeof(ItemData)) return;
    std::memcpy(&m_data, m_buffer.data() + sizeof(tq::MsgHead), sizeof(m_data));

    auto pUser = CUserManager::Instance().GetUser(dwSender);
    if (!pUser) return;

    ItemInfo* pItem = pUser->FindItem(m_data.dwIdItem);
    switch (m_data.usAction) {
    case Action_Use: { // 4: consumables
        if (!pItem || pItem->usSort != 0) {
            CMsgItem resp;
            if (pItem) resp.Create(*pItem, Action_Use, Result_CannotUse);
            else { ItemInfo none{}; none.dwId = m_data.dwIdItem; resp.Create(none, Action_Use, Result_ItemNotFound); }
            pUser->SendMsg(resp.GetBuf(), resp.GetSize());
            return;
        }
        // healing potion: restore life, then consume
        uint32_t dwLife = pUser->GetLife() + 500;
        if (dwLife > pUser->GetMaxLife()) dwLife = pUser->GetMaxLife();
        pUser->SetLife(dwLife);
        std::vector<AttribPair> attribs = { { CMsgUserAttrib::Attrib_Life, dwLife } };
        CMsgUserAttrib msgAttrib;
        if (msgAttrib.Create(pUser->GetId(), attribs))
            pUser->SendMsg(msgAttrib.GetBuf(), msgAttrib.GetSize());

        if (pItem->dwAmount > 1) {
            pItem->dwAmount--;
            CMsgItem resp;
            resp.Create(*pItem, Action_Use, Result_Ok);
            pUser->SendMsg(resp.GetBuf(), resp.GetSize());
        } else {
            uint32_t dwId = pItem->dwId;
            pUser->RemoveItem(dwId);
            CMsgItem resp;
            ItemInfo gone{}; gone.dwId = dwId; gone.dwAmount = 0;
            resp.Create(gone, Action_Use, Result_Ok);
            pUser->SendMsg(resp.GetBuf(), resp.GetSize());
        }
        printf("[ITEM] %s used item %u, life now %u/%u\n",
               pUser->GetName().c_str(), m_data.dwIdItem, dwLife, pUser->GetMaxLife());
        break;
    }
    case Action_Drop: { // 3: remove from inventory (ground items come with MsgMapItem)
        if (pItem) {
            pUser->RemoveItem(m_data.dwIdItem);
            CMsgItem resp;
            ItemInfo dropped = *pItem;
            dropped.dwAmount = 0;
            resp.Create(dropped, Action_Drop, Result_Ok);
            pUser->SendMsg(resp.GetBuf(), resp.GetSize());
            printf("[ITEM] %s dropped %s (%u)\n",
                   pUser->GetName().c_str(), dropped.strName.c_str(), dropped.dwId);
        }
        break;
    }
    case Action_Equip: { // 5: move to equipment slot
        if (pItem && pItem->usSort > 0) {
            pItem->dwPosition = m_data.dwParam; // slot the client asked for
            pUser->RecalcEquipmentBonuses();
            CMsgItem resp;
            resp.Create(*pItem, Action_Equip, Result_Ok);
            pUser->SendMsg(resp.GetBuf(), resp.GetSize());
        }
        break;
    }
    case Action_Unequip: { // 6: back to inventory
        if (pItem) {
            pItem->dwPosition = 255;
            pUser->RecalcEquipmentBonuses();
            CMsgItem resp;
            resp.Create(*pItem, Action_Unequip, Result_Ok);
            pUser->SendMsg(resp.GetBuf(), resp.GetSize());
        }
        break;
    }
    default:
        // buy/sell arrive with the NPC shop system; v1 accepts and ignores
        break;
    }
}
