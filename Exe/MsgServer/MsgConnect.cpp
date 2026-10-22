#include "MsgConnect.h"
#include "MsgTalk.h"
#include "MsgUserAttrib.h"
#include "MsgItem.h"
#include "User.h"
#include "UserManager.h"
#include "Item.h"
#include "MapManager.h"
#include "MonsterManager.h"
#include "MsgMonster.h"
#include "NetCore.h"
#include "StringPacker.h"
#include "Account.h"

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

    // real account validation: salted SHA-256 store (accounts.dat)
    uint32_t dwAccountId = 0;
    auto result = CAccountManager::Instance().Validate(m_account, m_password, dwAccountId);
    if (result == CAccountManager::Result::WrongPassword) {
        printf("[LOGIN] Session %u: account='%s' REJECTED (wrong password)\n", dwSender, m_account.c_str());
        CMsgTalk err;
        if (err.Create("SYSTEM", m_account, "Invalid password for this account.", CMsgTalk::Channel_Talk))
            pClient->Send(err.GetBuf(), err.GetSize());
        return; // do not spawn a player
    }
    if (result == CAccountManager::Result::Banned) {
        printf("[LOGIN] Session %u: account='%s' REJECTED (banned)\n", dwSender, m_account.c_str());
        CMsgTalk err;
        if (err.Create("SYSTEM", m_account, "This account is banned.", CMsgTalk::Channel_Talk))
            pClient->Send(err.GetBuf(), err.GetSize());
        return;
    }
    if (result == CAccountManager::Result::NoSuchAccount) {
        printf("[LOGIN] Session %u: account='%s' REJECTED (no such account)\n", dwSender, m_account.c_str());
        CMsgTalk err;
        if (err.Create("SYSTEM", m_account, "Account does not exist.", CMsgTalk::Channel_Talk))
            pClient->Send(err.GetBuf(), err.GetSize());
        return;
    }
    printf("[LOGIN] Session %u: account='%s' authenticated (id %u)\n", dwSender, m_account.c_str(), dwAccountId);

    // Create the player bound to this socket session
    auto pUser = std::make_shared<CUser>(dwSender);
    pUser->SetName(m_account.empty() ? ("Guest" + std::to_string(dwSender)) : m_account);
    pUser->SetAccountId(dwAccountId);
    pUser->SetLevel(1);
    pUser->SetLife(1000);
    pUser->SetMoney(100000);
    pUser->SetConquerPoints(5000);

    // restore a saved character from cq_user when MySQL is live
    uint32_t dwSpawnMap = 1002;
    CAccountManager::CharacterRecord rec;
    if (dwAccountId && CAccountManager::Instance().LoadCharacter(dwAccountId, rec)) {
        pUser->SetLevel((uint8_t)rec.dwLevel);
        pUser->SetMoney(rec.dwMoney);
        pUser->SetConquerPoints((uint32_t)rec.dwCp);
        pUser->SetBank(rec.dwBank);
        pUser->SetPkPoints(rec.dwPkPoints);
        pUser->SetExperience(rec.dwExperience);
        pUser->SetStatPoints(rec.dwStatPoints);
        pUser->SetStrength(rec.dwStrength);
        pUser->SetVitality(rec.dwVitality);
        pUser->SetRebornCount(rec.dwRebornCount);
        pUser->SetLastRewardDay(rec.strLastRewardDay);
        pUser->SetSpouseName(rec.strSpouseName);
        pUser->SetLife(1000);
        // base max life scales with restored level (+20/level) and vitality (+5/point)
        pUser->SetMaxLife(1000 + (rec.dwLevel > 1 ? (rec.dwLevel - 1) * 20 : 0) +
                          rec.dwVitality * 5 + rec.dwRebornCount * 1000);
        pUser->SetPos(rec.usX, rec.usY);
        dwSpawnMap = rec.dwMapId;
        printf("[LOGIN] Account %u: character restored (level %u, money %llu, map %u)\n",
               dwAccountId, rec.dwLevel, (unsigned long long)rec.dwMoney, rec.dwMapId);
    }
    // level-scaled max life becomes the base BEFORE equipment bonuses apply
    pUser->SetLife(pUser->GetMaxLife());
    pUser->SnapshotBaseStats();
    pUser->BindNet(pClient);
    pUser->GrantDailyBankInterest(); // same-day gate, pays before the reward save
    if (pUser->GrantDailyReward())
        CAccountManager::Instance().SaveRewardDay(dwAccountId, pUser->GetLastRewardDay());
    {   // sync the stamina bar
        CMsgUserAttrib st;
        if (st.Create(pUser->GetId(), { { CMsgUserAttrib::Attrib_Stamina, pUser->GetStamina() } }))
            pUser->SendMsg(st.GetBuf(), st.GetSize());
    }
    {   // deliver offline mail once the character is in the world
        auto mails = CAccountManager::Instance().LoadUnreadMail(pUser->GetName());
        if (!mails.empty()) {
            pUser->SendSysMsg("You have " + std::to_string(mails.size()) + " unread mail(s):");
            for (auto& m : mails)
                pUser->SendSysMsg("[Mail from " + m.strFrom + "] " + m.strBody);
            CAccountManager::Instance().MarkMailRead(pUser->GetName());
        }
    }
    CUserManager::Instance().AddUser(pUser);
    CMapManager::Instance().GetOrCreate(dwSpawnMap, "Twin City")->AddUser(pUser);

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

    // restore the saved inventory when one exists (otherwise starter kit)
    bool bGaveKit = false;
    if (dwAccountId) {
        std::vector<CAccountManager::ItemRow> rows;
        if (CAccountManager::Instance().LoadItems(dwAccountId, rows)) {
            for (const auto& r : rows) {
                ItemInfo item;
                item.dwId = MakeItemId(pUser->NextItemSeq());
                item.dwType = r.dwType;
                item.usSort = r.usSort;
                item.dwAmount = r.dwAmount;
                bool bWarehouse = r.dwPosition >= 1000; // stored marker
                item.dwPosition = bWarehouse ? 255 : r.dwPosition;
                item.strName = r.strName;
                item.ucPlus = r.ucPlus;
                if (bWarehouse) { pUser->WarehouseStore(item); continue; }
                pUser->AddItem(item);
                CMsgItem msgItem;
                if (msgItem.Create(item, CMsgItem::Action_Buy))
                    pUser->SendMsg(msgItem.GetBuf(), msgItem.GetSize());
            }
            printf("[LOGIN] Account %u: %zu item(s) restored from cq_item.\n",
                   dwAccountId, rows.size());
            bGaveKit = true;
        }
    }
    pUser->RecalcEquipmentBonuses(); // equipped restores now add cq_itemaddition stats

    // starting kit: weapon + armor + potions
    struct KitDef { uint32_t type; uint16_t sort; const char* name; uint32_t amount; };
    static const KitDef kit[] = {
        { 410011, 1, "Sword",   1 },
        { 900020, 2, "Armor",   1 },
        { 100020, 0, "Potion",  5 },
    };
    if (!bGaveKit)
    for (const auto& k : kit) {
        ItemInfo item;
        item.dwId = MakeItemId(pUser->NextItemSeq());
        item.dwType = k.type;
        item.usSort = k.sort;
        item.dwAmount = k.amount;
        item.dwPosition = 255;
        item.strName = k.name;
        CItemLibrary::Instance().Apply(item); // cq_itemtype drives name/sort
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
