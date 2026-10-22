#include "MsgInteract.h"
#include "User.h"
#include "UserManager.h"
#include "MapManager.h"
#include "Account.h"
#include "MonsterManager.h"
#include "Npc.h"
#include "Guild.h"
#include "MsgItem.h"
#include "BattleSystem.h"
#include "MsgUserAttrib.h"
#include "Team.h"
#include "GroundItems.h"
#include "Item.h"
#include "MsgTalk.h"

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

    // NPC interaction: ids >= CNpcManager::NPC_ID_BASE route to the NPC system
    if (m_data.dwTargetId >= CNpcManager::NPC_ID_BASE) {
        CNpcManager::Instance().SpawnDefaults();
        auto pNpc = CNpcManager::Instance().GetNpc(m_data.dwTargetId);
        if (pNpc) pNpc->Interact(pAttacker);
        else pAttacker->SendSysMsg("There is no such NPC. /npc list");
        return;
    }

    // ---- PvP v1: interact aimed at another player ----
    auto pTarget = CUserManager::Instance().GetUser(m_data.dwTargetId);
    if (pTarget && pTarget->GetId() != pAttacker->GetId()) {
        if (pTarget->GetMapId() != pAttacker->GetMapId()) return;
        if (pTarget->GetLife() == 0) return; // corpse guard

        // safe zone: no PK damage inside protected cities (Twin City)
        auto pCurMap = CMapManager::Instance().GetMap(pAttacker->GetMapId());
        if (pCurMap && pCurMap->IsSafeZone()) {
            pAttacker->SendSysMsg("This is a safe zone - you cannot attack players here.");
            return;
        }

        uint32_t dwDamage = 20 + pAttacker->GetLevel() * 4 + (std::rand() % 25);
        uint32_t dwLife = pTarget->GetLife() > dwDamage ? pTarget->GetLife() - dwDamage : 0;
        pTarget->SetLife(dwLife);

        CMsgInteract resp;
        resp.Create(m_data.usAction, pTarget->GetId(), dwDamage,
                    m_data.usX, m_data.usY, pAttacker->GetId());
        CMapManager::Instance().Broadcast(pAttacker->GetMapId(), resp.GetBuf(), resp.GetSize());

        printf("[PVP] %s hits %s for %u dmg (life %u)\n",
               pAttacker->GetName().c_str(), pTarget->GetName().c_str(),
               dwDamage, dwLife);

        if (dwLife == 0) {
            // arena: map 1038 kills go to the cq_arena ladder, no PK penalty
            bool bArena = (pAttacker->GetMapId() == 1038);
            bool bJustice = false;
            if (bArena) {
                CAccountManager::Instance().RecordArenaKill(pAttacker->GetName(), pTarget->GetName());
                pAttacker->SendSysMsg("Arena kill! Recorded on the ladder. /arena top");
            } else {
            // justice kill: slaying a red-name earns no PK points
            bJustice = pTarget->IsRedName();
            // killer gains PK points; the victim respawns in Twin City
            if (!bJustice) pAttacker->AddPkPoints(10);
            // the victim drops 10% of carried money at the corpse
            CGroundItemManager::Instance().OnPlayerDeath(pTarget);
            } // end non-arena death
            // guild war scoring: kill counts if both are in warring guilds
            auto pKillerGuild = CGuildManager::Instance().GetByMember(pAttacker->GetId());
            auto pVictimGuild = CGuildManager::Instance().GetByMember(pTarget->GetId());
            if (pKillerGuild && pVictimGuild && pKillerGuild->GetId() != pVictimGuild->GetId()) {
                if (CGuildManager::Instance().IsAtWar(pKillerGuild->GetId()))
                    CGuildManager::Instance().OnWarKill(pKillerGuild->GetId(), pVictimGuild->GetId());
            }
            CMapManager::Instance().Broadcast(pAttacker->GetMapId(), resp.GetBuf(), resp.GetSize());
            CMsgTalk notice;
            if (notice.Create("SYSTEM", "",
                               pAttacker->GetName() + " has killed " + pTarget->GetName() +
                               (pAttacker->IsRedName() ? " (RED NAME!)" : ""),
                               CMsgTalk::Channel_Talk))
                CMapManager::Instance().Broadcast(pAttacker->GetMapId(), notice.GetBuf(), notice.GetSize());
            pTarget->SetLife(pTarget->GetMaxLife());
            pTarget->Teleport(1002, 315, 275);
            pTarget->SendSysMsg("You were defeated and respawned in Twin City.");
            if (bArena)
                pAttacker->SendSysMsg("You killed " + pTarget->GetName() + " (arena kill)");
            else
                pAttacker->SendSysMsg("You killed " + pTarget->GetName() +
                                      (bJustice ? " (JUSTICE KILL - no PK points)" :
                                       " (+10 PK points, total " + std::to_string(pAttacker->GetPkPoints()) + ")"));
            printf("[PVP] %s killed %s (+10 PK)\n",
                   pAttacker->GetName().c_str(), pTarget->GetName().c_str());
        }
        return;
    }

    // v1: any interact aimed at a monster id is resolved as a melee hit
    {
        auto pMonster = CMonsterManager::Instance().GetMonsterById(m_data.dwTargetId);
        if (!pMonster) return;
        ResolveMonsterHit(pAttacker.get(), m_data.dwTargetId,
                           CBattleSystem::Instance().CalcMonsterDamage(pAttacker.get(), pMonster.get()),
                           m_data.usAction, m_data.usX, m_data.usY);
    }

}

// shared monster-hit resolution: damage -> broadcast -> retaliation ->
// the full kill pipeline (drops, task, xp, team share, quest, loot, pk
// decay). Weapon skills reuse it with their own damage numbers.
void CMsgInteract::ResolveMonsterHit(CUser* pAttacker, uint32_t dwTargetId,
                                     uint32_t dwDamage, uint16_t usAction,
                                     uint16_t usX, uint16_t usY) {
    // team share APIs take the shared_ptr handle - recover it by user id
    auto pAttackerRef = CUserManager::Instance().GetUser(pAttacker->GetId());
    // v1: any interact aimed at a monster id is resolved as a melee hit
    auto pMonster = CMonsterManager::Instance().GetMonsterById(dwTargetId);
    if (!pMonster) return;

    if (!pMonster->IsAlive()) return;
    if (pMonster->GetMapId() != pAttacker->GetMapId()) return;

    // dwDamage comes from the caller: melee roll or a skill's own formula
    uint32_t dwLife = pMonster->GetLife() > dwDamage ? pMonster->GetLife() - dwDamage : 0;
    pMonster->SetLife(dwLife);

    // echo the strike to everyone on the map, damage carried in dwData
    CMsgInteract resp;
    resp.Create(usAction, dwTargetId, dwDamage,
                usX, usY, pAttacker->GetId());
    CMapManager::Instance().Broadcast(pAttacker->GetMapId(), resp.GetBuf(), resp.GetSize());

    printf("[BATTLE] %s hits %s for %u dmg (life %u/%u)\n",
           pAttacker->GetName().c_str(), pMonster->GetName().c_str(),
           dwDamage, dwLife, pMonster->GetMaxLife());

    // the monster fights back: retaliation damage to the attacker
    if (pMonster->IsAlive()) {
        uint32_t back = CBattleSystem::Instance().CalcPlayerDamage(pMonster.get(), pAttacker);
        uint32_t heroLife = pAttacker->GetLife() > back ? pAttacker->GetLife() - back : 0;
        pAttacker->SetLife(heroLife);
        std::vector<AttribPair> attribs = { { CMsgUserAttrib::Attrib_Life, heroLife } };
        CMsgUserAttrib m;
        if (m.Create(pAttacker->GetId(), attribs))
            pAttacker->SendMsg(m.GetBuf(), m.GetSize());
        pAttacker->SendSysMsg(pMonster->GetName() + " hits you for " + std::to_string(back) + "!");
        if (heroLife == 0) {
            // fallen hero: respawn in Twin City, monster resets to full life
            pAttacker->SetLife(pAttacker->GetMaxLife());
            pAttacker->Teleport(1002, 315, 275);
            pMonster->SetLife(pMonster->GetMaxLife());
            pAttacker->SendSysMsg("You were slain by " + pMonster->GetName() +
                                  " and revived in Twin City.");
            printf("[BATTLE] %s was slain by %s\n",
                   pAttacker->GetName().c_str(), pMonster->GetName().c_str());
            return;
        }
    }

    if (dwLife == 0) {
        // the bounty falls on the floor - walk over and /pick it up
        CGroundItemManager::Instance().OnMonsterDeath(pMonster->GetMapId(),
                                                      pMonster->GetX(), pMonster->GetY(),
                                                      pMonster->GetLevel());
        CMonsterManager::Instance().OnMonsterKilled(pMonster);
        // hunt task progress (type 0 = any monster)
        if (pAttacker->HasActiveTask() &&
            (pAttacker->m_task.dwMonsterType == 0 ||
             pAttacker->m_task.dwMonsterType == pMonster->GetTypeId()) &&
            pAttacker->m_task.dwDone < pAttacker->m_task.dwNeeded) {
            ++pAttacker->m_task.dwDone;
            pAttacker->SendSysMsg("Task progress: " + std::to_string(pAttacker->m_task.dwDone) +
                                  "/" + std::to_string(pAttacker->m_task.dwNeeded) +
                                  (pAttacker->m_task.dwDone == pAttacker->m_task.dwNeeded
                                   ? " - return to the TaskMaster!" : ""));
        }
        // experience scales with monster level (original model: harder mobs = more xp)
        uint32_t dwXp = 10 + pMonster->GetLevel() * 15;
        if (pMonster->IsBoss()) dwXp *= 20; // world boss jackpot
        pAttacker->AddExperience(dwXp);
        // teammates on the same map each earn half the kill XP
        CTeamManager::Instance().ShareKillXp(pAttackerRef, dwXp);
        // daily hunt quest: every monster kill counts
        pAttacker->AddQuestKill();
        if (!pAttacker->IsQuestClaimed() && pAttacker->GetQuestKills() == 10)
            pAttacker->SendSysMsg("Daily hunt ready! /quest claim for your reward.");
        if (pMonster->IsBoss()) {
            CMsgTalk note;
            if (note.Create("SYSTEM", "", pAttacker->GetName() + std::string(" has slain the TerraDragon!"),
                            CMsgTalk::Channel_Broadcast))
                CMapManager::Instance().BroadcastToAll(note.GetBuf(), note.GetSize());
        }
        // attacker rewards: base bounty; teams split it among same-map members
        CTeamManager::Instance().ShareKillReward(pAttackerRef, 50, 1);
        pAttacker->AddMoney(50);
        pAttacker->AddConquerPoints(1);
        // cq_dropitemrule: roll the monster's loot table (v1: straight to bag)
        auto* pRules = CItemLibrary::Instance().GetDropRules(pMonster->GetTypeId());
        if (pRules) {
            for (const auto& r : *pRules) {
                if ((uint32_t)(rand() % 100) >= r.dwChance) continue;
                auto* pDef = CItemLibrary::Instance().Lookup(r.dwItemType);
                if (!pDef) continue;
                // stack with an existing consumable stack
                bool bStacked = false;
                if (pDef->usSort == 0) {
                    for (auto& it : pAttacker->GetInventory()) {
                        if (it.dwType == r.dwItemType && it.dwAmount < 1000) {
                            ++it.dwAmount; bStacked = true;
                            CMsgItem m; if (m.Create(it, CMsgItem::Action_Buy))
                                pAttacker->SendMsg(m.GetBuf(), m.GetSize());
                            break;
                        }
                    }
                }
                if (!bStacked) {
                    ItemInfo item;
                    item.dwId = MakeItemId(pAttacker->NextItemSeq());
                    item.dwType = r.dwItemType;
                    item.usSort = pDef->usSort;
                    item.dwAmount = 1;
                    item.dwPosition = 255;
                    item.strName = pDef->strName;
                    pAttacker->AddItem(item);
                    CMsgItem m; if (m.Create(item, CMsgItem::Action_Buy))
                        pAttacker->SendMsg(m.GetBuf(), m.GetSize());
                }
                pAttacker->SendSysMsg("Lucky! " + pMonster->GetName() + " dropped " +
                                       pDef->strName + ".");
            }
        }
        // pk decay (v1): monster kills shed 1 PK point, red names fade over time
        if (pAttacker->GetPkPoints() > 0) {
            pAttacker->SetPkPoints(pAttacker->GetPkPoints() - 1);
        }
        printf("[BATTLE] %s killed %s (+50 money, +1 CP)\n",
               pAttacker->GetName().c_str(), pMonster->GetName().c_str());
    }
}
