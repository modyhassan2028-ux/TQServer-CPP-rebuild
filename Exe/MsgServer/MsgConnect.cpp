#include "MsgConnect.h"
#include "MsgTalk.h"
#include "MsgUserAttrib.h"
#include "MsgItem.h"
#include "User.h"
#include "UserManager.h"
#include "MapManager.h"
#include "MonsterManager.h"
#include "MsgMonster.h"
#include "NetCore.h"
#include "StringPacker.h"

#include <cstring>
#include <cstdio>
#include <memory>

bool CMsgConnect::Create(uint32_t dwId, uint32_t dwData, const std::string& account, const std::string& password) {
    tq::CStringPacker packer;
    packer.AddString(account.c_str());
    packer.AddString(password.c_str());
    packer.AddString("TQServer"); // server name

    tq::MsgHead head;
    head.type = 1001; // MsgConnect
    uint32_t dataSize = 4 + 4 + packer.GetSize();
    head.length = static_cast<uint16_t>(sizeof(tq::MsgHead) + dataSize);

    m_buffer.resize(head.length);
    std::memcpy(m_buffer.data(), &head, sizeof(head));

    char* pData = m_buffer.data() + sizeof(head);
    std::memcpy(pData, &dwId, 4);
    std::memcpy(pData + 4, &dwData, 4);
    packer.SetBuf(pData + 8, packer.GetSize(), true);

    m_nType = head.type;
    m_nSize = head.length;
    return true;
}

void CMsgConnect::Process(uint32_t) {}

void CMsgConnect::Process(uint32_t dwSender, void* pContext) {
    if (m_buffer.size() < sizeof(tq::MsgHead) + 8) return;

    const char* pData = m_buffer.data() + sizeof(tq::MsgHead);
    uint32_t dwId = 0, dwData = 0;
    std::memcpy(&dwId, pData, 4);
    std::memcpy(&dwData, pData + 4, 4);

    tq::CStringPacker packer;
    packer.SetBuf(const_cast<char*>(pData + 8),
                   static_cast<uint32_t>(m_buffer.size()) - sizeof(tq::MsgHead) - 8, false);
    char buf[64] = { 0 };
    if (packer.GetStrAmount() >= 2) {
        packer.GetString(0, buf, sizeof(buf) - 1);
        m_account = buf;
        packer.GetString(1, buf, sizeof(buf) - 1);
        m_password = buf;
    }

    auto* pClient = static_cast<CNetClient*>(pContext);
    if (!pClient) return;

    printf("[LOGIN] Session %u: account='%s' (auth v1: accepted)\n",
           dwSender, m_account.c_str());

    // Create the player bound to this socket session
    auto pUser = std::make_shared<CUser>(dwSender);
    pUser->SetName(m_account.empty() ? ("Guest" + std::to_string(dwSender)) : m_account);
    pUser->SetLevel(1);
    pUser->SetLife(1000);
    pUser->SetMoney(100000);
    pUser->SetConquerPoints(5000);
    pUser->BindNet(pClient);
    CUserManager::Instance().AddUser(pUser);
    CMapManager::Instance().GetOrCreate(1002, "Twin City")->AddUser(pUser); // spawn in Twin City

    // 1017: push core attributes so the client sees a live character
    std::vector<AttribPair> attribs = {
        { CMsgUserAttrib::Attrib_Life,     pUser->GetLife() },
        { CMsgUserAttrib::Attrib_MaxLife,  pUser->GetMaxLife() },
        { CMsgUserAttrib::Attrib_Level,    pUser->GetLevel() },
        { CMsgUserAttrib::Attrib_Money,    pUser->GetMoney() },
        { CMsgUserAttrib::Attrib_ConquerPoints, pUser->GetConquerPoints() },
    };
    CMsgUserAttrib msgAttrib;
    if (msgAttrib.Create(pUser->GetId(), attribs))
        pUser->SendMsg(msgAttrib.GetBuf(), msgAttrib.GetSize());

    // starting kit: weapon + armor + potions
    struct KitDef { uint32_t type; uint16_t sort; const char* name; uint32_t amount; };
    static const KitDef kit[] = {
        { 410011, 1, "Sword",   1 },
        { 900020, 2, "Armor",   1 },
        { 100020, 0, "Potion",  5 },
    };
    for (const auto& k : kit) {
        ItemInfo item;
        item.dwId = MakeItemId(pUser->NextItemSeq());
        item.dwType = k.type;
        item.usSort = k.sort;
        item.dwAmount = k.amount;
        item.dwPosition = 255;
        item.strName = k.name;
        pUser->AddItem(item);
        CMsgItem msgItem;
        if (msgItem.Create(item, CMsgItem::Action_Buy))
            pUser->SendMsg(msgItem.GetBuf(), msgItem.GetSize());
    }

    // 20001: spawn the map's monsters for the new client
    for (auto& pMon : CMonsterManager::Instance().GetMapMonsters(pUser->GetMapId())) {
        if (!pMon || !pMon->IsAlive()) continue;
        CMsgMonsterInfo info;
        if (info.Create(pMon->GetId(), pMon->GetTypeId(), pMon->GetX(), pMon->GetY(), pMon->GetDir()))
            pUser->SendMsg(info.GetBuf(), info.GetSize());
    }

    // 1004: welcome
    CMsgTalk talk;
    if (talk.Create("SYSTEM", pUser->GetName(),
                    "Welcome to the C++ rebuild. Login accepted.",
                    CMsgTalk::Channel_Broadcast))
        pUser->SendMsg(talk.GetBuf(), talk.GetSize());
}
