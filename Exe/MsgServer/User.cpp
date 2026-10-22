#include "User.h"
#include "Item.h"
#include "MsgTalk.h"
#include <iostream>
#include "NetCore.h"
#include "Npc.h"
#include "MsgNpcInfo.h"

CUser::CUser(uint32_t dwId) : m_dwId(dwId) {}
CUser::~CUser() = default;

void CUser::Teleport(uint32_t dwMapId, uint16_t usX, uint16_t usY) {
    m_dwMapId = dwMapId;
    m_usX = usX;
    m_usY = usY;
    std::cout << "[GM System] Teleported User " << m_name << " (ID: " << m_dwId << ") to Map "
              << dwMapId << " (" << usX << ", " << usY << ")\n";
    SendSysMsg("Teleported to Map " + std::to_string(dwMapId) + " at (" + std::to_string(usX) + ", " + std::to_string(usY) + ")");

    // announce the NPCs of the destination map (CMsgNpcInfo 2030)
    for (auto& pNpc : CNpcManager::Instance().GetNpcsOnMap(dwMapId)) {
        CMsgNpcInfo info;
        if (info.Create(pNpc->GetId(), pNpc->GetLookface(), pNpc->GetX(), pNpc->GetY(),
                        pNpc->GetDir(), pNpc->GetName()))
            SendMsg(info.GetBuf(), info.GetSize());
    }
}

void CUser::SendSysMsg(const std::string& message) {
    CMsgTalk talk;
    if (talk.Create("SYSTEM", m_name, "[GM Control] " + message, CMsgTalk::Channel_Broadcast))
        SendMsg(talk.GetBuf(), talk.GetSize());
}

void CUser::SendMsg(const void* pBuf, uint16_t usSize) {
    if (m_pNet)
        static_cast<CNetClient*>(m_pNet)->Send(pBuf, usSize);
}
// sum cq_itemaddition bonuses over every equipped item (position != 255)
void CUser::RecalcEquipmentBonuses() {
    uint32_t bonusLife = 0, bonusAtk = 0;
    for (const auto& it : m_items) {
        if (it.dwPosition == 255) continue; // not equipped
        auto* a = CItemLibrary::Instance().LookupAddition(it.dwType);
        if (!a) continue;
        bonusLife += a->dwLife;
        bonusAtk += a->dwAttack;
    }
    uint32_t newMax = m_dwBaseMaxLife + bonusLife;
    if (m_dwLife > newMax) m_dwLife = newMax;
    m_dwMaxLife = newMax;
    m_dwBattlePower = m_dwBaseBP + bonusAtk;
}

// grant xp with level-ups: each level grants +20 base max life and full heal
uint32_t CUser::AddExperience(uint64_t dwXp) {
    m_dwExperience += dwXp;
    uint32_t ups = 0;
    while (m_ucLevel < 130 && m_dwExperience >= ExpForLevel(m_ucLevel)) {
        ++m_ucLevel;
        ++ups;
    }
    if (ups > 0) {
        m_dwBaseMaxLife += 20 * ups;   // permanent base growth
        m_dwStatPoints += 3 * ups;     // attribute points to spend
        RecalcEquipmentBonuses();      // re-apply gear on the new base
        m_dwLife = m_dwMaxLife;        // level-up fully heals
        SendSysMsg("LEVEL UP! You are now level " + std::to_string(m_ucLevel) +
                   " (+" + std::to_string(20 * ups) + " max life).");
        printf("[LEVEL] %s reached level %u\n", m_name.c_str(), m_ucLevel);
    }
    return ups;
}

// /stat str N  -> +N attack per point; /stat vit N -> +5 base max life per point
std::string CUser::AllocStat(const std::string& stat, uint32_t count) {
    if (count == 0) return "Amount must be positive.";
    if (m_dwStatPoints < count)
        return "Only " + std::to_string(m_dwStatPoints) + " stat points left.";
    if (stat == "str" || stat == "strength") {
        m_dwStrength += count;
    } else if (stat == "vit" || stat == "vitality") {
        m_dwVitality += count;
        m_dwBaseMaxLife += 5 * count;   // permanent base growth
        RecalcEquipmentBonuses();
    } else {
        return "Unknown stat '" + stat + "'. Use str or vit.";
    }
    m_dwStatPoints -= count;
    SendSysMsg("Allocated " + std::to_string(count) + " point(s) to " + stat +
               " (" + std::to_string(m_dwStatPoints) + " left).");
    return "";
}
