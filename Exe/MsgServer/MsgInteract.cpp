#include "MsgInteract.h"
#include "User.h"
#include "UserManager.h"
#include "MapManager.h"
#include "MonsterManager.h"

#include <cstring>
#include <cstdio>
#include <cstdlib>

bool CMsgInteract::Create(uint16_t usAction, uint32_t dwTargetId, uint32_t dwData,
                          uint16_t usX, uint16_t usY, uint32_t dwSenderId) {
    tq::MsgHead head;
    head.type = 1022; // 0x3FE
    head.length = sizeof(tq::MsgHead) + sizeof(InteractData); // 40 bytes

    m_data.dwSenderId = dwSenderId;
    m_data.dwTargetId = dwTargetId;
    m_data.dwData = dwData;
    m_data.usX = usX;
    m_data.usY = usY;
    m_data.usAction = usAction;
    m_data.usPad = 0;
    m_data.dwData2 = 0;
    m_data.dwData3 = 0;
    m_data.dwZero = 0;

    m_buffer.resize(head.length);
    std::memcpy(m_buffer.data(), &head, sizeof(head));
    std::memcpy(m_buffer.data() + sizeof(head), &m_data, sizeof(m_data));

    m_nType = head.type;
    m_nSize = head.length;
    return true;
}

uint16_t CMsgInteract::GetAction() const {
    return m_data.usAction;
}
uint32_t CMsgInteract::GetSenderId() const { return m_data.dwSenderId; }
uint32_t CMsgInteract::GetTargetId() const { return m_data.dwTargetId; }
uint16_t CMsgInteract::GetX() const { return m_data.usX; }
uint16_t CMsgInteract::GetY() const { return m_data.usY; }

void CMsgInteract::Process(uint32_t dwSender) {
    if (m_buffer.size() < sizeof(tq::MsgHead) + sizeof(InteractData)) return;
    std::memcpy(&m_data, m_buffer.data() + sizeof(tq::MsgHead), sizeof(m_data));

    auto pAttacker = CUserManager::Instance().GetUser(dwSender);
    if (!pAttacker) return;
    if (pAttacker->GetId() != m_data.dwSenderId && m_data.dwSenderId != 0) return; // spoof guard

    // v1: any interact aimed at a monster id is resolved as a melee hit
    auto pMonster = CMonsterManager::Instance().GetMonsterById(m_data.dwTargetId);
    if (!pMonster) return; // user-vs-user interact comes with the PvP system

    if (!pMonster->IsAlive()) return;
    if (pMonster->GetMapId() != pAttacker->GetMapId()) return;

    // simple v1 damage: base + level scale + random, replaces the full
    // BattleSystem formula (crit/dodge/weapon types) which ports later
    uint32_t dwDamage = 15 + pAttacker->GetLevel() * 5 + (std::rand() % 20);
    uint32_t dwLife = pMonster->GetLife() > dwDamage ? pMonster->GetLife() - dwDamage : 0;
    pMonster->SetLife(dwLife);

    // echo the strike to everyone on the map, damage carried in dwData
    CMsgInteract resp;
    resp.Create(m_data.usAction, m_data.dwTargetId, dwDamage,
                m_data.usX, m_data.usY, pAttacker->GetId());
    CMapManager::Instance().Broadcast(pAttacker->GetMapId(), resp.GetBuf(), resp.GetSize());

    printf("[BATTLE] %s hits %s for %u dmg (life %u/%u)\n",
           pAttacker->GetName().c_str(), pMonster->GetName().c_str(),
           dwDamage, dwLife, pMonster->GetMaxLife());

    if (dwLife == 0) {
        CMonsterManager::Instance().OnMonsterKilled(pMonster);
        // attacker rewards (v1): money drops straight to the killer
        pAttacker->AddMoney(50);
        pAttacker->AddConquerPoints(1);
        printf("[BATTLE] %s killed %s (+50 money, +1 CP)\n",
               pAttacker->GetName().c_str(), pMonster->GetName().c_str());
    }
}
