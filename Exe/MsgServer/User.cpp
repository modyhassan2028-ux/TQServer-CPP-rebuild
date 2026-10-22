#include "User.h"
#include "Item.h"
#include "MsgTalk.h"
#include <iostream>
#include "NetCore.h"
#include "Npc.h"
#include "MsgNpcInfo.h"
#include "Account.h"
#include "MySQLClient.h"

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
    if (m_packetSink) { m_packetSink(pBuf, usSize); return; }
    if (m_pNet)
        static_cast<CNetClient*>(m_pNet)->Send(pBuf, usSize);
}
// sum cq_itemaddition bonuses over every equipped item (position != 255)
void CUser::RecalcEquipmentBonuses() {
    uint32_t bonusLife = 0, bonusAtk = 0;
    for (const auto& it : m_items) {
        if (it.dwPosition == 255) continue; // not equipped
        // cq_itemaddition is per-plus and cumulative: +N grants the sum of
        // rows 1..N for this type; types without rows keep the flat v1 rates
        auto a = CItemLibrary::Instance().AdditionBonusAt(it.dwType, it.ucPlus);
        if (a.dwLife || a.dwAttack) {
            bonusLife += a.dwLife;
            bonusAtk += a.dwAttack;
        } else {
            if (it.usSort == 1) bonusAtk += it.ucPlus * 5;
            else if (it.usSort == 2) bonusLife += it.ucPlus * 10;
        }
        // enchant: gems add flat life to any equipped piece
        bonusLife += it.usEnchant;
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

// daily login reward: once per UTC day - 2000 money + 5 healing pills.
// Day tracking is a plain YYYY-MM-DD string persisted in cq_user.
bool CUser::GrantDailyReward() {
    time_t now = time(nullptr);
    tm t{};
#ifdef _WIN32
    gmtime_s(&t, &now);
#else
    gmtime_r(&now, &t);
#endif
    char day[16];
    snprintf(day, sizeof(day), "%04d-%02d-%02d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday);
    std::string strDay(day);
    if (m_strLastRewardDay == strDay) return false;
    m_strLastRewardDay = strDay;
    AddMoney(2000);
    // stack 5 healing pills (or start a fresh stack)
    for (auto& it : m_items)
        if (it.dwType == 725013 && it.dwAmount < 1000) {
            uint32_t room = 1000 - it.dwAmount;
            it.dwAmount += (room < 5) ? room : 5;
            SendSysMsg("Daily reward: +2000 money, healing pills (x" + std::to_string(it.dwAmount) + ").");
            printf("[DAILY] %s claimed the %s reward (stack)\n", m_name.c_str(), day);
            return true;
        }
    ItemInfo pill;
    pill.dwId = MakeItemId(NextItemSeq());
    pill.dwType = 725013; pill.usSort = 50; pill.dwAmount = 5;
    pill.strName = "HealingPill x5"; pill.dwPosition = 255;
    m_items.push_back(pill);
    SendSysMsg("Daily reward: +2000 money, +5 healing pills. Come back tomorrow!");
    printf("[DAILY] %s claimed the %s reward\n", m_name.c_str(), day);
    return true;
}

// reborn: level 130 characters reset to level 15 and keep 15% of the XP bar
// progress, plus a permanent +500 base life bonus and 30 fresh stat points
// per reborn. The classic 'start over stronger' loop.
std::string CUser::DoReborn() {
    if (m_ucLevel < 130)
        return "You must be level 130 to reborn.";
    if (m_dwRebornCount >= 2)
        return "Maximum reborns (2) reached.";
    ++m_dwRebornCount;
    m_ucLevel = 15;
    m_dwExperience = ExpForLevel(15) / 10; // a head start on the new life
    m_dwBaseMaxLife += 500;                // permanent reborn bonus
    m_dwStatPoints += 30;
    RecalcEquipmentBonuses();
    m_dwLife = m_dwMaxLife;
    SendSysMsg("REBORN! You start a new life at level 15 with +500 max life and +30 stat points.");
    printf("[REBORN] %s reborn #%u\n", m_name.c_str(), m_dwRebornCount);
    return "";
}

// daily bank interest: 2% of the bank balance, capped at 50,000/day,
// credited once per calendar day (same rollover marker as the login reward).
uint64_t CUser::GrantDailyBankInterest() {
    char dayBuf[16];
    time_t now = time(nullptr);
    struct tm lt;
#ifdef _WIN32
    localtime_s(&lt, &now);
#else
    localtime_r(&now, &lt);
#endif
    strftime(dayBuf, sizeof(dayBuf), "%Y-%m-%d", &lt);
    std::string today(dayBuf);
    if (m_strLastRewardDay == today)
        return 0; // already paid today
    uint64_t interest = m_dwBank / 50;            // 2%
    if (interest > 50000) interest = 50000;       // cap
    if (interest > 0) {
        m_dwBank += interest;
        SendSysMsg("Daily bank interest: +" + std::to_string(interest) +
                   " money (" + std::to_string(m_dwBank) + " saved).");
        printf("[BANK] %s interest +%llu\n", m_name.c_str(), (unsigned long long)interest);
    }
    return interest;
}

// ===========================================================================
// ORIGINAL magic record API (CPlayerMagic port)
// ===========================================================================

// FUN_14048b5f0(user, type): iterate the user's magic map and return the
// first record whose GetAttrib(rec, 2) == dwType.
CPlayerMagic* CUser::FindMagic(uint32_t dwType) {
    auto it = m_oMagics.find(dwType);
    return it == m_oMagics.end() ? nullptr : &it->second;
}

// load this character's cq_magic rows (the original record pool for the
// owner; logged on login, written back on change)
bool CUser::LoadMagicsFromDB(CMySQLClient* pDB) {
    if (!pDB) return false;
    if (!pDB->Query("SELECT id, ownerid, type, level, exp, unlearn, old_level,"
                    " current_effect_type, available_effect_type, effect_monopoly,"
                    " effect_exorbitant FROM cq_magic WHERE ownerid=" +
                    std::to_string(m_dwId))) {
        printf("[MAGIC] cq_magic load failed: %s\n", pDB->GetError().c_str());
        return false;
    }
    m_oMagics.clear();
    for (auto& row : pDB->GetRows()) {
        if (row.size() < 11) continue;
        CPlayerMagic m;
        m.m_dwId = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        m.m_dwOwnerid = (uint32_t)strtoul(row[1].c_str(), nullptr, 10);
        m.m_wType = (uint16_t)strtoul(row[2].c_str(), nullptr, 10);
        m.m_wLevel = (uint16_t)strtoul(row[3].c_str(), nullptr, 10);
        m.m_dwExp = (uint32_t)strtoul(row[4].c_str(), nullptr, 10);
        m.m_ucUnlearn = (uint8_t)strtoul(row[5].c_str(), nullptr, 10);
        m.m_wOldLevel = (uint16_t)strtoul(row[6].c_str(), nullptr, 10);
        m.m_ucCurrentEffectType = (uint8_t)strtoul(row[7].c_str(), nullptr, 10);
        m.m_dwAvailableEffectType = (uint32_t)strtoul(row[8].c_str(), nullptr, 10);
        m.m_dwEffectMonopoly = (uint32_t)strtoul(row[9].c_str(), nullptr, 10);
        m.m_dwEffectExorbitant = (uint32_t)strtoul(row[10].c_str(), nullptr, 10);
        if (m_dwMagicCounter < m.m_dwId) m_dwMagicCounter = m.m_dwId;
        m_oMagics[m.m_wType] = m;
    }
    return true;
}

// FUN_1404939c0(user, type, level, byTask):
//  1. the cq_magictype (type, level) stage must exist, else
//     "CPlayerMagic::LearnMagic(), Can't Find Magic(Type:%d, Level:%d)"
//  2. already-known type -> re-learn only clears the unlearn flag, then
//     returns false (the original also returns 0 on this path)
//  3. new record: owner/type/level set, exp 0, id from the pool counter
//  4. persist + (original sends a MsgMagic packet here; wire pending)
bool CUser::LearnMagic(uint32_t dwType, uint32_t dwLevel) {
    if (!dwType) return false;
    const CMagicTypeInfo* pType = CMagicTypePool::Instance().Find(dwType, dwLevel);
    if (!pType) {
        printf("[MAGIC] CPlayerMagic::LearnMagic(), Can't Find Magic(Type:%u, Level:%u)\n",
               dwType, dwLevel);
        return false;
    }
    if (CPlayerMagic* pRec = FindMagic(dwType)) {
        // ORIGINAL: known + unlearn + inactive -> clear the flag, resend
        if (pRec->IsUnlearn()) {
            pRec->SetUnlearn(0);
            pRec->Save(CAccountManager::Instance().GetDB());
        }
        return false; // can't learn twice
    }
    CPlayerMagic m;
    m.m_dwOwnerid = m_dwId;
    m.m_wType = (uint16_t)dwType;
    m.m_wLevel = (uint16_t)dwLevel;
    m.m_dwExp = 0;
    if (!m.Save(CAccountManager::Instance().GetDB())) {
        printf("[MAGIC] pop cq_magic rec err:owner=%u,type=%u,lev=%u\n",
               m_dwId, dwType, dwLevel);
        return false;
    }
    m_oMagics[dwType] = m;
    ++m_dwMagicCounter;
    return true;
}

// FUN_14048fd10 UpLevelByTask: level+1 stage must exist in cq_magictype,
// else "CPlayerMagic::UpLevelByTask(), Can't Find Magic(Type,Level)"
bool CUser::UpLevelMagic(uint32_t dwType) {
    CPlayerMagic* pRec = FindMagic(dwType);
    if (!pRec) return false;
    uint32_t dwNew = (uint32_t)pRec->GetAttrib(3) + 1;
    if (!CMagicTypePool::Instance().Find(dwType, dwNew)) {
        printf("[MAGIC] CPlayerMagic::UpLevelByTask(), Can't Find Magic(Type:%u, Level:%u)\n",
               dwType, dwNew);
        return false;
    }
    pRec->SetAttrib(3, (int32_t)dwNew);
    pRec->SetAttrib(4, 0); // exp resets on level-up
    pRec->Save(CAccountManager::Instance().GetDB());
    return true;
}

// FUN_140493f70 DeleteMagic(user, type, mode=0):
// old_level = max(old_level, level); unlearn = 1 (record kept)
bool CUser::DeleteMagic(uint32_t dwType) {
    CPlayerMagic* pRec = FindMagic(dwType);
    if (!pRec) return false;
    int32_t nOld = pRec->GetAttrib(6);
    int32_t nLev = pRec->GetAttrib(3);
    if (nOld < nLev) pRec->SetAttrib(6, nLev);
    pRec->SetAttrib(5, 1);
    pRec->Save(CAccountManager::Instance().GetDB());
    return true;
}

// ---------------------------------------------------------------------------
// ORIGINAL FUN_1404918c0 CPlayerMagic::AddMagicExp(user, type, amount)
// Gates (linked cq_magictype attrs of the record's stage):
//   attr 0x76 (need_exp)  == -1/0  -> fail (chain end, no exp)
//   attr 0x78 (need_level of the NEXT stage) vs the player's level: the
//     session vtable+0x70 getter must reach it or no exp is gained
//   attr 0x75 (need_prof mask) vs the user flag byte at +0xeee: not yet
//     ported (our users carry no flag byte); need_prof==0 covers 1,195 of
//     the 1,266 stages so the gate is passed until the flag byte lands.
// Loop: while exp >= need_exp and the next stage exists -> FUN_14048fd10
// (UpLevelMagic). Chain end / level gate inside the loop RESETS exp to 0.
// Cap: 0xf4241 (1,000,001) iterations, then InlineLogERROR.
// Exit: SetAttrib(rec, 4, exp) + Save + MsgMagic update packet (type 1104,
// FUN_1403f0020 layout [u32 exp][u32][u16 type][u8 mode=1]; wire pending
// the msg-class family port).
bool CUser::AddMagicExp(uint32_t dwType, int nAmount) {
    if (nAmount < 1) return false;                       // original: param_3 < 1 -> 0
    CPlayerMagic* pRec = FindMagic(dwType);               // FUN_14048b5f0
    if (!pRec) return false;
    auto& pool = CMagicTypePool::Instance();
    uint32_t dwLev = (uint32_t)pRec->GetAttrib(3);
    const CMagicTypeInfo* pStage = pool.Find(dwType, dwLev);
    if (!pStage || pStage->nNeedExp <= 0) return false;
    const CMagicTypeInfo* pNext = pool.Find(dwType, dwLev + 1);
    if (!pNext) return false;                            // chain end: no next gate
    if ((int32_t)GetLevel() < (int32_t)pNext->dwNeedLevel) return false;
    // TODO(port): need_prof mask vs user flag byte +0xeee (FUN_140480a00)

    int nExp = pRec->GetAttrib(4) + nAmount;
    int nLevels = 0;
    do {
        dwLev = (uint32_t)pRec->GetAttrib(3);
        pStage = pool.Find(dwType, dwLev);
        if (!pStage || pStage->nNeedExp <= 0) { nExp = 0; break; }
        pNext = pool.Find(dwType, dwLev + 1);
        if (!pNext || (int32_t)GetLevel() < (int32_t)pNext->dwNeedLevel) { nExp = 0; break; }
        if (nExp < pStage->nNeedExp) break;
        nExp -= pStage->nNeedExp;
        UpLevelMagic(dwType);                             // FUN_14048fd10(user, type, 0)
        nLevels++;
        if (nLevels >= 1000001) {                        // 0xf4241
            printf("[MAGIC] AddMagicExp: level loop overflow (type %u)\n", dwType);
            break;
        }
    } while (true);
    pRec->SetAttrib(4, nExp);                             // FUN_140418d90(rec, 4, exp)
    pRec->Save(CAccountManager::Instance().GetDB());      // FUN_140418450(rec)
    return true;
}

// ---------------------------------------------------------------------------
// ORIGINAL FUN_140491be0 CPlayerMagic::AwardMgcTime(user, type, ms)
// Converts ms to exp through the ORIGINAL CalcTimeToExp (FUN_1402f1340,
// CWeaponSkillUp): time = need_time*(exp/need_exp) + ms, walk stages while
// time >= need_time (accumulate their need_exp), add the partial
// need_exp*(time/need_time), floor at the current exp, and return the DELTA.
// Delta capped at 0x7fffffff (log on overflow), then AddMagicExp.
bool CUser::AwardMgcTime(uint32_t dwType, int nMs) {
    if (nMs < 1) return false;                            // original: 0 < param_3
    CPlayerMagic* pRec = FindMagic(dwType);
    if (!pRec) return false;
    auto& pool = CMagicTypePool::Instance();
    int32_t nLevel = pRec->GetAttrib(3);                  // FUN_140418c50(rec, 3)
    int32_t nExpCur = pRec->GetAttrib(4);                 // FUN_140418c50(rec, 4)

    int64_t llGained = 0;                                 // lVar3
    bool bPartial = false;                                // normal-exit flag
    const CMagicTypeInfo* pStage = pool.Find(dwType, (uint32_t)nLevel);
    if (pStage) {
        float fNeedExp = (float)pStage->nNeedExp;
        if (fNeedExp <= 0.0f) fNeedExp = 1.0f;            // iVar2 = 1 when need_exp <= 0
        float fTime = (float)pStage->dwNeedTime * ((float)nExpCur / fNeedExp) + (float)nMs;
        int32_t nLastNeedTime = (int32_t)pStage->dwNeedTime;
        while (true) {
            pStage = pool.Find(dwType, (uint32_t)nLevel);
            if (!pStage) break;                           // goto out (skip partial)
            int32_t nNeedTime = (int32_t)pStage->dwNeedTime;   // field 0x13
            if (nNeedTime == -1 || nNeedTime == 0) break;      // goto out
            if (fTime < (float)nNeedTime) {               // normal exit -> partial
                nLastNeedTime = nNeedTime;
                bPartial = true;
                break;
            }
            fTime -= (float)nNeedTime;
            int32_t nNeedExp = pStage->nNeedExp;           // field 0x12
            nLevel++;
            llGained += nNeedExp;
            if (nLevel > 100) {                            // overflow guard -> out
                printf("[MAGIC] CalcTimeToExp: level overflow (type %u)\n", dwType);
                break;
            }
        }
        if (bPartial) {
            const CMagicTypeInfo* pCur = pool.Find(dwType, (uint32_t)nLevel);
            if (pCur) {
                int32_t nNeedTime = nLastNeedTime > 0 ? nLastNeedTime : 1;
                llGained += (int64_t)((float)pCur->nNeedExp * (fTime / (float)nNeedTime));
            }
        }
    }
    if (llGained < nExpCur) llGained = nExpCur;           // never below current exp
    int64_t llDelta = llGained - nExpCur;
    if (llDelta > 0x7fffffffLL) {                         // 0x7fffffff cap + log
        printf("[MAGIC] CPlayerMagic::AwardMgcTime, effect lost: %lld\n",
               (long long)(llDelta - 0x7fffffff));
        llDelta = 0x7fffffff;
    }
    return AddMagicExp(dwType, (int)llDelta);
}
