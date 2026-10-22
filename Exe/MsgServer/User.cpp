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
        if (a) {
            bonusLife += a->dwLife;
            bonusAtk += a->dwAttack;
        }
        // refinement applies to ANY equipped item, with or without an addition record:
        // weapons gain +5 attack per plus, armor +10 life per plus
        if (it.usSort == 1) bonusAtk += it.ucPlus * 5;
        else if (it.usSort == 2) bonusLife += it.ucPlus * 10;
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

// consume one charge of a usable stack; healing pills restore 200 hp
bool CUser::ConsumeByType(uint32_t dwType) {
    for (auto& it : m_items) {
        if (it.dwType != dwType || it.dwAmount == 0) continue;
        if (--it.dwAmount == 0) RemoveItem(it.dwId);
        if (dwType == 725013) {          // HealingPill
            uint32_t life = m_dwLife + 200;
            if (life > m_dwMaxLife) life = m_dwMaxLife;
            m_dwLife = life;
            SendSysMsg("You eat a healing pill (+200 life, now " + std::to_string(life) + ").");
        } else {
            SendSysMsg("You use the item.");
        }
        return true;
    }
    return false;
}

// rebirth at the level cap: restart at 15, keep allocated str/vit, gain
// +1000 permanent base life and +45 bonus points per rebirth (v6159 model:
// reborn characters grow stronger through retained stats + bonus points)
std::string CUser::Reborn() {
    if (m_ucLevel < 130) return "Rebirth requires level 130.";
    ++m_dwRebornCount;
    m_ucLevel = 15;
    m_dwExperience = 0;
    m_dwBaseMaxLife += 1000;              // permanent rebirth growth
    m_dwStatPoints += 45;                 // reborn bonus points
    RecalcEquipmentBonuses();
    m_dwLife = m_dwMaxLife;
    SendSysMsg("REBORN! You are level 15 again, +1000 max life and +45 stat points (rebirth " +
               std::to_string(m_dwRebornCount) + ").");
    printf("[REBORN] %s reborn (count %u)\n", m_name.c_str(), m_dwRebornCount);
    return "";
}

// /upgrade: refine the equipped weapon to +1..+12 (cq_itemaddition model).
// Cost = 10k * (next plus); success chance falls ~8% per level (100% at +0 -> 10% at +11).
// v1 is forgiving: a failure keeps the current plus, only the money burns.
std::string CUser::UpgradeEquipped() {
    ItemInfo* pWeapon = nullptr;
    for (auto& it : m_items)
        if (it.dwPosition != 255 && it.usSort == 1) { pWeapon = &it; break; }
    if (!pWeapon) return "Equip a weapon first.";
    if (pWeapon->ucPlus >= 12) return "Weapon is already at the +12 cap.";
    uint32_t dwCost = 10000 * (uint32_t)(pWeapon->ucPlus + 1);
    if (m_dwMoney < dwCost) return "Upgrading to +" + std::to_string(pWeapon->ucPlus + 1) +
                                       " costs " + std::to_string(dwCost) + " money.";
    m_dwMoney -= dwCost;
    int chance = 100 - pWeapon->ucPlus * 8;
    if (chance < 10) chance = 10;
    if (std::rand() % 100 < chance) {
        ++pWeapon->ucPlus;
        RecalcEquipmentBonuses();
        SendSysMsg("SUCCESS! " + pWeapon->strName + " refined to +" +
                   std::to_string(pWeapon->ucPlus) + "!");
        printf("[REFINE] %s upgraded %s to +%u\n", m_name.c_str(),
               pWeapon->strName.c_str(), pWeapon->ucPlus);
    } else {
        SendSysMsg("The refining failed... your " + pWeapon->strName +
                   " stays +" + std::to_string(pWeapon->ucPlus) + ".");
        printf("[REFINE] %s failed refining %s (cost %u)\n", m_name.c_str(),
               pWeapon->strName.c_str(), dwCost);
    }
    return "";
}
