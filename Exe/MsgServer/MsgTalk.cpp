#include "MsgTalk.h"
#include <ctime>
#include <cstdlib>
#include "Account.h"
#include "MapManager.h"
#include "StringPacker.h"
#include "UserManager.h"
#include "Guild.h"
#include "Trade.h"
#include "Team.h"
#include "GroundItems.h"
#include "MsgInteract.h"
#include "CrossServer/CrossClient.h"
#include "MonsterManager.h"
#include "BattleSystem.h"
#include "Npc.h"
#include "User.h"
#include "Item.h"
#include "ItemUpgrade.h"
#include "Activity/ActivityManager.h"
#include "MsgItem.h"
#include "MySQLClient.h"
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>

CMsgTalk::CMsgTalk() = default;

bool CMsgTalk::Create(const std::string& sender, const std::string& recipient, const std::string& message, ChannelType channel) {
    m_sender = sender;
    m_recipient = recipient;
    m_message = message;

    tq::CStringPacker packer;
    packer.AddString(sender.c_str());
    packer.AddString(recipient.c_str());
    packer.AddString(""); // Suffix
    packer.AddString(message.c_str());

    tq::MsgHead head;
    head.type = 1004; // MsgTalk Packet ID
    head.length = static_cast<uint16_t>(sizeof(tq::MsgHead) + sizeof(TalkData) + packer.GetSize());

    TalkData data{};
    data.type = static_cast<uint16_t>(channel);
    data.style = 0;
    data.color = 0xFFFFFF;

    m_buffer.resize(head.length);
    std::memcpy(m_buffer.data(), &head, sizeof(head));
    std::memcpy(m_buffer.data() + sizeof(head), &data, sizeof(data));
    packer.SetBuf(m_buffer.data() + sizeof(head) + sizeof(data), packer.GetSize(), true);

    m_nType = head.type;
    m_nSize = head.length;
    return true;
}

void CMsgTalk::Process(uint32_t dwSender) {
    auto user = CUserManager::Instance().GetUser(dwSender);
    if (!user) return;

    // ---- guild v1 (chat-driven) ----
    if (m_message.rfind("&", 0) == 0) { // "&text" = guild chat
        auto pGuild = CGuildManager::Instance().GetByMember(user->GetId());
        if (pGuild) {
            CMsgTalk guildMsg;
            if (guildMsg.Create(user->GetName(), "",
                                "[" + pGuild->GetName() + "] " + user->GetName() + ": " + m_message.substr(1),
                                CMsgTalk::Channel_Syndicate))
                CGuildManager::Instance().Broadcast(pGuild, guildMsg.GetBuf(), guildMsg.GetSize());
        } else {
            user->SendSysMsg("You are not in a guild. /guild create <name> or /guild join <name>");
        }
        return;
    }
    // plain digits route to the open NPC dialog menu (original 6159 interaction)
    if (!m_message.empty() && m_message.find_first_not_of("0123456789") == std::string::npos) {
        uint32_t dwNpc = user->GetTalkingNpc();
        if (dwNpc >= CNpcManager::NPC_ID_BASE) {
            auto pNpc = CNpcManager::Instance().GetNpc(dwNpc);
            if (pNpc) { pNpc->ChooseOption(user, static_cast<uint32_t>(strtoul(m_message.c_str(), nullptr, 10))); return; }
        }
    }
if (m_message.rfind("/npc", 0) == 0) {
        std::string arg = m_message.length() > 4 ? m_message.substr(5) : "";
        CNpcManager::Instance().SpawnDefaults();
        if (arg == "list") {
            auto list = CNpcManager::Instance().GetNpcsOnMap(user->GetMapId());
            if (list.empty()) user->SendSysMsg("No NPCs on this map.");
            for (auto& p : list)
                user->SendSysMsg(p->GetName() + " (id " + std::to_string(p->GetId()) +
                                 ") at (" + std::to_string(p->GetX()) + "," + std::to_string(p->GetY()) + ")");
        } else if (!arg.empty()) {
            uint32_t dwId = static_cast<uint32_t>(strtoul(arg.c_str(), nullptr, 10));
            auto pNpc = CNpcManager::Instance().GetNpc(dwId);
            if (pNpc) pNpc->Interact(user);
            else user->SendSysMsg("No such NPC. /npc list");
        } else {
            user->SendSysMsg("Usage: /npc list, /npc <id>");
        }
        return;
    }
    // ---- inventory: /inv to list, /sell <slot> [n] to sell back ----
    if (m_message == "/inv" || m_message == "/inv2" || m_message == "/items") {
        std::string out = "Inventory:";
        uint32_t i = 1;
        for (const auto& it : user->GetInventory()) {
            if (out.size() > 350) { out += "\n  (use /inv2 for more)"; break; }
            out += "\n  " + std::to_string(i) + ". " + it.strName;
            if (it.dwAmount > 1) out += " x" + std::to_string(it.dwAmount);
            if (it.dwPosition != 255) out += " (equipped)";
            else if (it.ucPlus > 0) out += " +" + std::to_string(it.ucPlus);
            ++i;
        }
        user->SendSysMsg(out);
        return;
    }
    if (m_message.rfind("/sell ", 0) == 0) {
        std::istringstream iss(m_message.substr(6));
        uint32_t slot = 0, n = 1;
        iss >> slot >> n;
        if (slot == 0) { user->SendSysMsg("Usage: /sell <slot> [count] - /inv to list."); return; }
        auto& inv = user->GetInventory();
        if (slot > inv.size()) { user->SendSysMsg("No such slot. /inv to list."); return; }
        auto& it = inv[slot - 1];
        if (it.dwPosition != 255) { user->SendSysMsg("Unequip it first."); return; }
        if (n == 0) n = 1;
        if (n > it.dwAmount) n = it.dwAmount;
        auto* pDef = CItemLibrary::Instance().Lookup(it.dwType);
        uint64_t unit = pDef ? pDef->dwPrice / 2 : 0;   // shop buys at half price
        if (pDef && pDef->dwPrice / 2 == 0) unit = 1;
        uint64_t total = unit * n;
        it.dwAmount -= n;
        if (it.dwAmount == 0) inv.erase(inv.begin() + (slot - 1));
        user->AddMoney(total);
        user->SendSysMsg("Sold " + std::to_string(n) + " x " + it.strName +
                         " for " + std::to_string(total) + " money.");
        printf("[SHOP] %s sold %u x %s for %llu\n", user->GetName().c_str(), n,
               it.strName.c_str(), (unsigned long long)total);
        return;
    }

    // ---- CP (conquer points) shop: premium currency from monster kills ----
    if (m_message.rfind("/cpshop", 0) == 0) {
        std::string out = "CP Shop (conquer points):";
        for (const auto& kv : CItemLibrary::Instance().GetAllTypes()) {
            const auto& d = kv.second;
            if (d.dwPrice / 1000 < 1) continue;   // only premium-priced goods
            out += "\n  " + std::to_string(d.dwType) + ". " + d.strName +
                   " - " + std::to_string(d.dwPrice / 1000) + " CP (you have " +
                   std::to_string(user->GetConquerPoints()) + ")";
            if (out.size() > 380) { out += "\n  ..."; break; }
        }
        user->SendSysMsg(out);
        return;
    }
    if (m_message.rfind("/cpbuy ", 0) == 0) {
        std::istringstream iss(m_message.substr(7));
        uint32_t dwType = 0, dwCount = 1;
        iss >> dwType >> dwCount;
        if (dwCount == 0) dwCount = 1;
        auto* pDef = CItemLibrary::Instance().Lookup(dwType);
        if (!pDef) { user->SendSysMsg("No such item type. /cpshop to list."); return; }
        uint32_t cpEach = pDef->dwPrice / 1000;
        if (cpEach < 1) cpEach = 1;
        uint64_t total = (uint64_t)cpEach * dwCount;
        if (user->GetConquerPoints() < total) {
            user->SendSysMsg("Not enough CP: need " + std::to_string(total) +
                             ", you have " + std::to_string(user->GetConquerPoints()) + ".");
            return;
        }
        user->SetConquerPoints(user->GetConquerPoints() - (uint32_t)total);
        uint32_t dwGiven = 0;
        if (pDef->usSort == 0) { // consumables stack first
            for (auto& it : user->GetInventory()) {
                if (it.dwType == dwType && it.dwAmount < 1000) {
                    uint32_t room = 1000 - it.dwAmount;
                    uint32_t add = (room < dwCount) ? room : dwCount;
                    it.dwAmount += add; dwCount -= add; dwGiven += add;
                    break;
                }
            }
        }
        while (dwCount > 0) {
            uint32_t amt = (dwCount > 1000) ? 1000 : dwCount;
            ItemInfo item;
            item.dwId = MakeItemId(user->NextItemSeq());
            item.dwType = dwType;
            item.usSort = pDef->usSort;
            item.dwAmount = pDef->usSort == 0 ? amt : 1;
            item.strName = pDef->strName;
            item.dwPosition = 255;
            user->GetInventory().push_back(item);
            dwGiven += item.dwAmount;
            if (pDef->usSort == 0) dwCount -= amt; else dwCount = 0;
        }
        user->SendSysMsg("Bought " + std::to_string(dwGiven) + " x " + pDef->strName +
                         " for " + std::to_string(total) + " CP.");
        printf("[CPSHOP] %s bought %u x %s for %llu CP\n", user->GetName().c_str(),
               dwGiven, pDef->strName.c_str(), (unsigned long long)total);
        return;
    }

    // ---- shop commands (prices from cq_itemtype / data/items.ini) ----
    if (m_message.rfind("/shop", 0) == 0) {
        user->SendSysMsg(CItemLibrary::Instance().ShopListText());
        return;
    }
    if (m_message.rfind("/buy ", 0) == 0) {
        std::istringstream iss(m_message.substr(5));
        uint32_t dwType = 0, dwCount = 1;
        iss >> dwType >> dwCount;
        if (dwCount == 0) dwCount = 1;
        auto* pDef = CItemLibrary::Instance().Lookup(dwType);
        if (!pDef) { user->SendSysMsg("No such item type. /shop to list."); return; }
        uint64_t ullTotal = (uint64_t)pDef->dwPrice * dwCount;
        if (user->GetMoney() < ullTotal) {
            user->SendSysMsg("Not enough money: need " + std::to_string(ullTotal) +
                             ", you have " + std::to_string(user->GetMoney()) + ".");
            return;
        }
        user->AddMoney(-(int64_t)ullTotal);
        // stack with an existing stack of the same type first
        uint32_t dwGiven = 0;
        if (pDef->usSort == 0) { // consumables stack
            for (auto& it : user->GetInventory()) {
                if (it.dwType == dwType && it.dwAmount < 1000) {
                    uint32_t room = 1000 - it.dwAmount;
                    uint32_t add = (room < dwCount) ? room : dwCount;
                    it.dwAmount += add; dwCount -= add; dwGiven += add;
                    break;
                }
            }
        }
        while (dwCount > 0) {
            uint32_t amt = (dwCount > 1000) ? 1000 : dwCount;
            ItemInfo item;
            item.dwId = MakeItemId(user->NextItemSeq());
            item.dwType = dwType;
            item.dwAmount = amt;
            item.dwPosition = 255;
            item.strName = pDef->strName;
            item.usSort = pDef->usSort;
            CItemLibrary::Instance().Apply(item);
            user->AddItem(item);
            dwCount -= amt; dwGiven += amt;
            CMsgItem msgItem;
            if (msgItem.Create(item, CMsgItem::Action_Buy))
                user->SendMsg(msgItem.GetBuf(), msgItem.GetSize());
        }
        user->SendSysMsg("Bought " + std::to_string(dwGiven) + "x " + pDef->strName + " for " +
                         std::to_string(ullTotal) + " money.");
        return;
    }
    if (m_message.rfind("/sell ", 0) == 0) {
        std::istringstream iss(m_message.substr(6));
        uint32_t dwType = 0, dwCount = 1;
        iss >> dwType >> dwCount;
        if (dwCount == 0) dwCount = 1;
        auto* pDef = CItemLibrary::Instance().Lookup(dwType);
        if (!pDef) { user->SendSysMsg("No such item type."); return; }
        uint32_t sold = 0;
        auto& inv = user->GetInventory();
        for (size_t i = 0; i < inv.size() && sold < dwCount; ) {
            if (inv[i].dwType == dwType && inv[i].dwPosition == 255) {
                uint32_t take = (inv[i].dwAmount <= dwCount - sold) ? inv[i].dwAmount : dwCount - sold;
                inv[i].dwAmount -= take; sold += take;
                uint32_t dwId = inv[i].dwId;
                if (inv[i].dwAmount == 0) { user->RemoveItem(dwId); continue; }
                else { CMsgItem m; if (m.Create(inv[i], CMsgItem::Action_Sell)) user->SendMsg(m.GetBuf(), m.GetSize()); }
            }
            ++i;
        }
        if (sold == 0) { user->SendSysMsg("You carry none of that."); return; }
        uint64_t pay = (uint64_t)(pDef->dwPrice / 2) * sold;
        user->AddMoney((int64_t)pay);
        user->SendSysMsg("Sold " + std::to_string(sold) + "x " + pDef->strName + " for " +
                         std::to_string(pay) + " money (half price).");
        return;
    }
    // ---- team commands ----
    // ---- /top level|money|pk: DB rankings ----
    if (m_message.rfind("/top", 0) == 0) {
        std::string col = m_message.size() > 5 ? m_message.substr(5) : "level";
        while (!col.empty() && col.back() == ' ') col.pop_back();
        if (col.empty()) col = "level";
        std::string display = col == "pk_points" ? "PK points" : col;
        auto rows = CAccountManager::Instance().GetTopPlayers(col);
        if (rows.empty()) { user->SendSysMsg("No ranking data."); return; }
        std::string out = "Top " + std::to_string(rows.size()) + " (" + display + "):";
        int rank = 1;
        for (auto& r : rows) {
            out += "\n  " + std::to_string(rank++) + ". " + r.strName + " - " +
                   std::to_string(r.qwValue);
            if (out.size() > 380) { out += "\n  ..."; break; }
        }
        user->SendSysMsg(out);
        return;
    }

    // ---- offline mail: /mail send <name> <text> (delivered at login) ----
    if (m_message.rfind("/mail ", 0) == 0) {
        std::string arg = m_message.substr(6);
        if (arg.rfind("send ", 0) == 0) {
            std::string rest = arg.substr(5);
            size_t sp = rest.find(' ');
            if (sp == std::string::npos) { user->SendSysMsg("Usage: /mail send <name> <text>"); return; }
            std::string to = rest.substr(0, sp);
            std::string body = rest.substr(sp + 1);
            if (body.empty() || body.size() > 200) { user->SendSysMsg("Text too long (max 200)."); return; }
            bool online = CUserManager::Instance().GetUserByName(to) != nullptr;
            if (CAccountManager::Instance().SendMail(to, user->GetName(), body)) {
                user->SendSysMsg("Mail sent to " + to + (online ? " (they are online - they will read it next login or /mail check)" : " (they will get it at next login)"));
                printf("[MAIL] %s -> %s: %s\n", user->GetName().c_str(), to.c_str(), body.c_str());
            } else {
                user->SendSysMsg("Mail failed (no database).");
            }
        } else if (arg == "check") {
            auto mails = CAccountManager::Instance().LoadUnreadMail(user->GetName());
            if (mails.empty()) { user->SendSysMsg("You have no unread mail."); return; }
            for (auto& m : mails)
                user->SendSysMsg("[Mail from " + m.strFrom + "] " + m.strBody);
            CAccountManager::Instance().MarkMailRead(user->GetName());
            user->SendSysMsg("(inbox marked read)");
        } else {
            user->SendSysMsg("Usage: /mail send <name> <text> | /mail check");
        }
        return;
    }

    // ---- marriage v1: /marry <name> propose, /marry accept, /divorce ----
    if (m_message.rfind("/marry", 0) == 0) {
        std::string arg = m_message.substr(6);
        while (!arg.empty() && arg[0] == ' ') arg.erase(0, 1);
        auto& mates = CUserManager::Instance(); // singleton holder
        static std::map<uint32_t, uint32_t> s_pendingMarry; // target -> proposer
        if (arg == "accept") {
            auto it = s_pendingMarry.find(user->GetId());
            if (it == s_pendingMarry.end()) { user->SendSysMsg("No marriage proposal pending."); return; }
            auto proposer = mates.GetUser(it->second);
            s_pendingMarry.erase(it);
            if (!proposer) { user->SendSysMsg("The proposer went offline."); return; }
            if (proposer->GetId() == user->GetId()) { user->SendSysMsg("You cannot marry yourself."); return; }
            if (!user->GetSpouseName().empty() || !proposer->GetSpouseName().empty()) {
                user->SendSysMsg("One of you is already married. /divorce first.");
                return;
            }
            user->SetSpouseName(proposer->GetName());
            proposer->SetSpouseName(user->GetName());
            if (user->GetAccountId()) CAccountManager::Instance().UpdateSpouse(user->GetAccountId(), user->GetSpouseName());
            if (proposer->GetAccountId()) CAccountManager::Instance().UpdateSpouse(proposer->GetAccountId(), proposer->GetSpouseName());
            CMsgTalk wed;
            if (wed.Create("SYSTEM", "", proposer->GetName() + " and " + user->GetName() +
                           " are now married! May your blades stay sharp.", CMsgTalk::Channel_Broadcast))
                CMapManager::Instance().BroadcastToAll(wed.GetBuf(), wed.GetSize());
            user->SendSysMsg("You married " + proposer->GetName() + "!");
            proposer->SendSysMsg(user->GetName() + " accepted - you are married!");
            printf("[MARRY] %s + %s\n", proposer->GetName().c_str(), user->GetName().c_str());
            return;
        }
        if (arg.empty()) { user->SendSysMsg("Usage: /marry <name> (they then type /marry accept)"); return; }
        auto target = mates.GetUserByName(arg);
        if (!target) { user->SendSysMsg(arg + " is not online."); return; }
        if (target->GetId() == user->GetId()) { user->SendSysMsg("You cannot marry yourself."); return; }
        if (!user->GetSpouseName().empty()) { user->SendSysMsg("You are already married to " + user->GetSpouseName() + "."); return; }
        if (!target->GetSpouseName().empty()) { user->SendSysMsg(target->GetName() + " is already married."); return; }
        s_pendingMarry[target->GetId()] = user->GetId();
        target->SendSysMsg(user->GetName() + " proposes marriage! Type /marry accept to say yes.");
        user->SendSysMsg("Proposal sent to " + target->GetName() + ".");
        return;
    }
    if (m_message == "/divorce") {
        if (user->GetSpouseName().empty()) { user->SendSysMsg("You are not married."); return; }
        std::string ex = user->GetSpouseName();
        auto target = CUserManager::Instance().GetUserByName(ex);
        if (target) {
            target->SetSpouseName("");
            target->SendSysMsg(user->GetName() + " divorced you.");
            if (target->GetAccountId()) CAccountManager::Instance().UpdateSpouse(target->GetAccountId(), "");
        }
        user->SetSpouseName("");
        if (user->GetAccountId()) CAccountManager::Instance().UpdateSpouse(user->GetAccountId(), "");
        CMsgTalk div;
        if (div.Create("SYSTEM", "", user->GetName() + " and " + ex + " have divorced.", CMsgTalk::Channel_Broadcast))
            CMapManager::Instance().BroadcastToAll(div.GetBuf(), div.GetSize());
        printf("[DIVORCE] %s + %s\n", user->GetName().c_str(), ex.c_str());
        return;
    }

    if (m_message.rfind("/team", 0) == 0) {
        std::string sub = m_message.size() > 6 ? m_message.substr(6) : "";
        if (!sub.empty() && sub[0] == ' ') sub = sub.substr(1);
        if (sub.rfind("invite ", 0) == 0) {
            std::string target = sub.substr(7);
            std::string err = CTeamManager::Instance().Invite(user, target);
            if (!err.empty()) user->SendSysMsg(err);
        } else if (sub == "accept") {
            std::string err = CTeamManager::Instance().Accept(user);
            if (!err.empty()) user->SendSysMsg(err);
        } else if (sub == "quit" || sub == "leave") {
            std::string err = CTeamManager::Instance().Quit(user);
            if (!err.empty()) user->SendSysMsg(err);
        } else { // list / help
            user->SendSysMsg(CTeamManager::Instance().RosterText(user));
        }
        return;
    }
    // ---- refinement ----
    if (m_message == "/upgrade" || m_message == "/refine") {
        std::string err = user->UpgradeEquipped();
        if (!err.empty()) user->SendSysMsg(err);
        return;
    }
    // ---- rebirth at the level cap ----
    // ---- /fish + /catch: fish by the water for money/CP ----
    // ---- /profession: fishing + mining ranks and bonuses ----
    if (m_message == "/profession") {
        user->SendSysMsg("Professions:\n"
                         "  Fishing: " + std::to_string(user->GetFishCaught()) + " catches - " +
                         CUser::ProfRank(user->GetFishCaught()) + " (+" +
                         std::to_string(CUser::ProfBonus(user->GetFishCaught()) - 100) + "% pay)\n"
                         "  Mining: " + std::to_string(user->GetOreMined()) + " digs - " +
                         CUser::ProfRank(user->GetOreMined()) + " (+" +
                         std::to_string(CUser::ProfBonus(user->GetOreMined()) - 100) + "% pay)");
        return;
    }

    // ---- live event schedule: /events ----
    if (m_message == "/events") {
        user->SendSysMsg(CActivityManager::Instance().StatusText());
        return;
    }

    // ---- weekly guild war standings: /gwtop ----
    if (m_message == "/gwtop") {
        user->SendSysMsg(CGuildManager::Instance().WeeklyStandingsText());
        return;
    }

    // ---- cross-server hub link: /cross <text>, /crosswho ----
    if (m_message.rfind("/cross ", 0) == 0) {
        std::string text = m_message.substr(7);
        if (text.empty()) { user->SendSysMsg("Usage: /cross <text>"); return; }
        if (!cross::CCrossClient::Instance().IsLinked()) {
            user->SendSysMsg("Cross hub is not linked."); return;
        }
        cross::CCrossClient::Instance().SendTalk(user->GetName(), text);
        user->SendSysMsg("[Cross] " + user->GetName() + ": " + text);
        return;
    }
    if (m_message == "/crosswho") {
        if (!cross::CCrossClient::Instance().IsLinked()) {
            user->SendSysMsg("Cross hub is not linked."); return;
        }
        cross::CCrossClient::Instance().RequestWho(user->GetId());
        user->SendSysMsg("Asking the cross hub... (roster incoming)");
        return;
    }

    // ---- refinement: /up <slot> pushes an item +1 (max +12) ----
    if (m_message.rfind("/up ", 0) == 0) {
        std::istringstream iss(m_message.substr(4));
        uint32_t slot = 0;
        iss >> slot;
        if (slot == 0) { user->SendSysMsg("Usage: /up <slot> - /inv to list."); return; }
        auto& inv = user->GetInventory();
        if (slot > inv.size()) { user->SendSysMsg("No such slot. /inv to list."); return; }
        auto& it = inv[slot - 1];
        if (it.dwPosition != 255) { user->SendSysMsg("Unequip it first."); return; }
        if (it.usSort == 0) { user->SendSysMsg("Only weapons and armor can be refined."); return; }
        if (it.ucPlus >= upgrade::kMaxPlus) {
            user->SendSysMsg(it.strName + " is already +" + std::to_string(it.ucPlus) +
                             " - it cannot be refined further.");
            return;
        }
        auto* pDef = CItemLibrary::Instance().Lookup(it.dwType);
        uint32_t dwPrice = pDef ? pDef->dwPrice : 1000;
        uint64_t dwCost = upgrade::UpgradeCost(dwPrice, it.ucPlus);
        uint32_t dwChance = upgrade::SuccessChance(it.ucPlus);
        if (user->GetMoney() < dwCost) {
            user->SendSysMsg("Refining to +" + std::to_string(it.ucPlus + 1) +
                             " costs " + std::to_string(dwCost) + " silver - you do not have enough.");
            return;
        }
        user->AddMoney(-(int64_t)dwCost);
        uint32_t roll = rand() % 100;
        if (roll < dwChance) {
            ++it.ucPlus;
            user->RecalcEquipmentBonuses();
            std::string strMsg = user->GetName() + " refined " + it.strName +
                                 " to +" + std::to_string(it.ucPlus) + "!";
            user->SendSysMsg("Success! " + it.strName + " is now +" +
                             std::to_string(it.ucPlus) + " (" + std::to_string(dwChance) +
                             "% chance, cost " + std::to_string(dwCost) + " silver).");
            if (it.ucPlus >= 7) {
                CMsgTalk note;
                if (note.Create("SYSTEM", "", strMsg, CMsgTalk::Channel_Broadcast))
                    CMapManager::Instance().BroadcastToAll(note.GetBuf(), note.GetSize());
            }
            printf("[UPGRADE] %s %s -> +%u\n", user->GetName().c_str(),
                   it.strName.c_str(), it.ucPlus);
        } else {
            user->SendSysMsg("The refinement failed (rolled " + std::to_string(roll) +
                             " vs " + std::to_string(dwChance) + "%). The silver is lost, " +
                             it.strName + " is unharmed at +" + std::to_string(it.ucPlus) + ".");
        }
        return;
    }

    // ---- blacksmith: /repair restores equipped weapon/armor durability ----
    if (m_message == "/repair") {
        uint32_t cost = user->RepairCost();
        if (cost == 0) { user->SendSysMsg("Your gear is already pristine."); return; }
        if (user->GetMoney() < cost) {
            user->SendSysMsg("Repair costs " + std::to_string(cost) + " money - you lack it."); return;
        }
        user->AddMoney(-(int64_t)cost);
        user->DoRepair();
        user->SendSysMsg("Your gear is restored to pristine. -" + std::to_string(cost) + " money.");
        printf("[REPAIR] %s -%u money\n", user->GetName().c_str(), cost);
        return;
    }

    // ---- player market: /market list|sell <slot> <price>|buy <id> ----
    if (m_message == "/market" || m_message == "/market list") {
        auto rows = CAccountManager::Instance().LoadMarket();
        if (rows.empty()) { user->SendSysMsg("The market is empty. /market sell <slot> <price>"); return; }
        std::string out = "Market (newest):";
        for (auto& r : rows)
            out += "\n  #" + std::to_string(r.dwId) + " " + r.strName + " x" + std::to_string(r.dwAmount) +
                   " (+ " + std::to_string(r.dwPrice) + " money) - " + r.strSeller;
        user->SendSysMsg(out);
        return;
    }
    if (m_message.rfind("/market sell ", 0) == 0) {
        // usage: /market sell <inventory slot> <money price>
        std::istringstream iss(m_message.substr(13));
        int slot = 0; uint64_t price = 0;
        if (!(iss >> slot >> price) || slot < 0 || price == 0) {
            user->SendSysMsg("Usage: /market sell <slot> <money price>"); return;
        }
        auto& inv = user->GetInventory();
        if ((uint32_t)slot >= inv.size()) { user->SendSysMsg("No item in that slot."); return; }
        auto& it = inv[slot];
        if (it.dwPosition != 255) { user->SendSysMsg("Unequip it first."); return; }
        if (it.dwType == 750) { user->SendSysMsg("Horses cannot be sold."); return; }
        uint32_t id = 0;
        if (!CAccountManager::Instance().SaveMarketListing(user->GetName(), it.dwType, it.strName,
                                                          it.usSort, it.dwAmount, it.ucPlus,
                                                          it.usEnchant, price, id)) {
            user->SendSysMsg("Market listing failed."); return;
        }
        std::string nm = it.strName; uint32_t amt = it.dwAmount;
        user->RemoveItem(it.dwId); // take the item out of the inventory
        user->SendSysMsg("Listed " + nm + " x" + std::to_string(amt) + " on the market as #" +
                         std::to_string(id) + " for " + std::to_string(price) + " money.");
        printf("[MARKET] %s listed %s x%u for %llu\n", user->GetName().c_str(),
               nm.c_str(), amt, (unsigned long long)price);
        return;
    }
    if (m_message.rfind("/market buy ", 0) == 0) {
        uint32_t id = strtoul(m_message.substr(12).c_str(), nullptr, 10);
        if (!id) { user->SendSysMsg("Usage: /market buy <id>"); return; }
        // price check before claiming: refuse offers the buyer cannot afford
        auto rows = CAccountManager::Instance().LoadMarket();
        const CAccountManager::MarketRow* pRow = nullptr;
        for (auto& r : rows) if (r.dwId == id) { pRow = &r; break; }
        if (!pRow) { user->SendSysMsg("Listing not found (or sold). /market list"); return; }
        if (pRow->strSeller == user->GetName()) { user->SendSysMsg("You cannot buy your own listing."); return; }
        if (user->GetMoney() < pRow->dwPrice) { user->SendSysMsg("Not enough money."); return; }
        CAccountManager::MarketRow bought;
        if (!CAccountManager::Instance().BuyMarketItem(id, user->GetName(), bought)) {
            user->SendSysMsg("Too late - someone else bought it."); return;
        }
        // charge AFTER a successful claim (price from the claimed row)
        user->AddMoney(-(int64_t)bought.dwPrice);
        ItemInfo item;
        item.dwId = MakeItemId(user->NextItemSeq());
        item.dwType = bought.dwType;
        item.usSort = bought.usSort;
        item.dwAmount = bought.dwAmount;
        item.dwPosition = 255;
        item.ucPlus = bought.ucPlus;
        item.usEnchant = bought.usEnchant;
        item.strName = bought.strName;
        user->AddItem(item);
        CMsgItem mi; if (mi.Create(item, CMsgItem::Action_Buy))
            user->SendMsg(mi.GetBuf(), mi.GetSize());
        user->SendSysMsg("Bought " + bought.strName + " x" + std::to_string(bought.dwAmount) +
                         " from " + bought.strSeller + " for " + std::to_string(bought.dwPrice) +
                         " money. Seller paid via bank.");
        printf("[MARKET] %s bought #%u from %s\n", user->GetName().c_str(), id,
               bought.strSeller.c_str());
        return;
    }

    // ---- weapon skills v1: /skills, /thunder <id>, /fastblade ----
    if (m_message == "/skills") {
        user->SendSysMsg("Skills: /thunder <monsterid> (level 10+, 20 stamina, 2.5x damage)\n"
                         "         /fastblade (level 30+, 30 stamina, hits the 3 nearest, 1.5x each)\n"
                         "         Usable on any monster on your map.");
        return;
    }
    if (m_message.rfind("/thunder ", 0) == 0) {
        if (user->GetLevel() < 10) { user->SendSysMsg("Thunder requires level 10."); return; }
        if (!user->SpendStamina(20)) { user->SendSysMsg("Not enough stamina (20)."); return; }
        uint32_t id = strtoul(m_message.substr(9).c_str(), nullptr, 10);
        auto pMonster = CMonsterManager::Instance().GetMonsterById(id);
        if (!pMonster || !pMonster->IsAlive() || pMonster->GetMapId() != user->GetMapId()) {
            user->SendSysMsg("No such monster here. /skills for usage."); return;
        }
        uint32_t base = CBattleSystem::Instance().CalcMonsterDamage(user.get(), pMonster.get());
        uint32_t dmg = base * 5 / 2; // 2.5x melee
        CMsgInteract::ResolveMonsterHit(user.get(), id, dmg, 21, user->GetX(), user->GetY());
        user->SendSysMsg("THUNDER strikes " + pMonster->GetName() + " for " + std::to_string(dmg) + "!");
        return;
    }
    if (m_message == "/fastblade") {
        if (user->GetLevel() < 30) { user->SendSysMsg("FastBlade requires level 30."); return; }
        if (!user->SpendStamina(30)) { user->SendSysMsg("Not enough stamina (30)."); return; }
        // the 3 nearest living monsters on the map, 1.5x melee each
        auto monsters = CMonsterManager::Instance().GetMapMonsters(user->GetMapId());
        std::vector<std::pair<uint32_t, uint32_t>> hits; // (dist2, id)
        for (auto& m : monsters) {
            if (!m || !m->IsAlive()) continue;
            uint32_t dx = (uint32_t)abs((int)m->GetX() - (int)user->GetX());
            uint32_t dy = (uint32_t)abs((int)m->GetY() - (int)user->GetY());
            hits.push_back({ dx * dx + dy * dy, m->GetId() });
        }
        std::sort(hits.begin(), hits.end());
        uint32_t n = 0;
        for (auto& h : hits) {
            if (n >= 3) break;
            auto pMonster = CMonsterManager::Instance().GetMonsterById(h.second);
            if (!pMonster || !pMonster->IsAlive()) continue;
            uint32_t base = CBattleSystem::Instance().CalcMonsterDamage(user.get(), pMonster.get());
            uint32_t dmg = base * 3 / 2; // 1.5x melee
            CMsgInteract::ResolveMonsterHit(user.get(), h.second, dmg, 21,
                                            user->GetX(), user->GetY());
            ++n;
        }
        user->SendSysMsg("FASTBLADE sweeps " + std::to_string(n) + " monster(s)!");
        return;
    }

    // ---- riding: buy a horse once, then /ride on|off for free jumps ----
    if (m_message == "/buyhorse") {
        const uint64_t kHorsePrice = 100000;
        if (user->HasHorse()) { user->SendSysMsg("You already own a horse."); return; }
        if (user->GetMoney() < kHorsePrice) {
            user->SendSysMsg("A horse costs " + std::to_string(kHorsePrice) + " money.");
            return;
        }
        user->AddMoney(-(int64_t)kHorsePrice);
        ItemInfo horse; horse.dwId = MakeItemId(user->NextItemSeq());
        horse.dwType = 750; horse.usSort = 3; horse.strName = "Stallion"; horse.dwPosition = 253;
        user->AddItem(horse);
        user->SendSysMsg("You bought a Stallion! /ride on to mount.");
        printf("[RIDE] %s bought a horse\n", user->GetName().c_str());
        return;
    }
    if (m_message == "/ride on" || m_message == "/ride") {
        if (!user->HasHorse()) { user->SendSysMsg("You need a horse first. /buyhorse"); return; }
        if (user->IsRiding()) { user->SendSysMsg("You are already riding."); return; }
        user->SetRiding(true);
        user->SendSysMsg("You mount your horse. Jumps no longer cost stamina!");
        return;
    }
    if (m_message == "/ride off") {
        if (!user->IsRiding()) { user->SendSysMsg("You are not riding."); return; }
        user->SetRiding(false);
        user->SendSysMsg("You dismount.");
        return;
    }

    // ---- item warehouse: /whstore <id> /whlist /whtake <id> ----
    if (m_message.rfind("/whstore ", 0) == 0) {
        uint32_t id = strtoul(m_message.substr(9).c_str(), nullptr, 10);
        ItemInfo* pItem = user->FindItem(id);
        if (!pItem) { user->SendSysMsg("No such item in your bag."); return; }
        if (pItem->dwPosition != 255) { user->SendSysMsg("Unequip it first."); return; }
        if (user->GetWarehouse().size() >= 40) { user->SendSysMsg("Warehouse full (40)."); return; }
        ItemInfo copy = *pItem;
        user->RemoveItem(id);
        user->WarehouseStore(copy);
        user->SendSysMsg("Stored " + copy.strName + " in the warehouse.");
        printf("[WAREHOUSE] %s stored %s\n", user->GetName().c_str(), copy.strName.c_str());
        return;
    }
    if (m_message == "/whlist") {
        auto& whs = user->GetWarehouse();
        if (whs.empty()) { user->SendSysMsg("Warehouse empty. /whstore <itemid> to store."); return; }
        std::string out = "Warehouse (" + std::to_string(whs.size()) + "/40):";
        for (auto& it : whs) {
            out += "\n  " + std::to_string(it.dwId) + ". " + it.strName;
            if (it.dwAmount > 1) out += " x" + std::to_string(it.dwAmount);
            if (out.size() > 380) { out += "\n  ..."; break; }
        }
        user->SendSysMsg(out);
        return;
    }
    if (m_message.rfind("/whtake ", 0) == 0) {
        uint32_t id = strtoul(m_message.substr(8).c_str(), nullptr, 10);
        ItemInfo* pItem = user->WarehouseFind(id);
        if (!pItem) { user->SendSysMsg("No such item in the warehouse. /whlist"); return; }
        if (user->GetInventory().size() >= 40) { user->SendSysMsg("Bag full - free a slot first."); return; }
        ItemInfo copy = *pItem;
        user->WarehouseRemove(id);
        user->AddItem(copy);
        user->SendSysMsg("Took " + copy.strName + " from the warehouse.");
        printf("[WAREHOUSE] %s took %s\n", user->GetName().c_str(), copy.strName.c_str());
        return;
    }

    // ---- /enchant: socket gems into equipped gear for bonus life ----
    if (m_message.rfind("/enchant", 0) == 0) {
        // find an equipped item (first equipped piece)
        ItemInfo* pGear = nullptr;
        for (auto& it : user->GetInventory())
            if (it.dwPosition != 255) { pGear = &it; break; }
        if (!pGear) { user->SendSysMsg("Equip a weapon or armor first."); return; }
        uint16_t target = (uint16_t)(pGear->usEnchant == 0 ? 255 :
                          pGear->usEnchant == 255 ? 512 :
                          pGear->usEnchant == 512 ? 1024 : 2048);
        if (pGear->usEnchant >= 2048) { user->SendSysMsg("This gear is fully enchanted."); return; }
        // cost: current enchant tier * 20,000 money
        uint32_t cost = (pGear->usEnchant == 0 ? 20000 :
                         pGear->usEnchant == 255 ? 40000 :
                         pGear->usEnchant == 512 ? 80000 : 160000);
        if (user->GetMoney() < cost) {
            user->SendSysMsg("Enchanting to +" + std::to_string(target) +
                             " costs " + std::to_string(cost) + " money.");
            return;
        }
        user->AddMoney(-cost);
        pGear->usEnchant = target;
        user->RecalcEquipmentBonuses();
        user->SetLife(user->GetLife()); // clamp against the new max
        user->SendSysMsg("Enchant succeeded! " + pGear->strName + " now grants +" +
                         std::to_string(target) + " bonus life.");
        printf("[ENCHANT] %s %s +%u\n", user->GetName().c_str(),
               pGear->strName.c_str(), target);
        return;
    }

    // ---- /lottery: spend 5 CP, roll for prizes ----
    if (m_message == "/lottery") {
        const uint32_t kCost = 5;
        if (user->GetConquerPoints() < kCost) {
            user->SendSysMsg("You need " + std::to_string(kCost) +
                             " CP to play. (Earn CP from bosses, quests, mining gems.)");
            return;
        }
        user->AddConquerPoints(-kCost);
        int roll = std::rand() % 1000;
        if (roll < 550) { // 55%: nothing
            user->SendSysMsg("Lucky Lottery: better luck next time...");
        } else if (roll < 800) { // 25%: small coins
            user->AddMoney(3000);
            user->SendSysMsg("Lucky Lottery: +3,000 money!");
        } else if (roll < 920) { // 12%: CP back x2
            user->AddConquerPoints(10);
            user->SendSysMsg("Lucky Lottery: +10 CP!");
        } else if (roll < 980) { // 6%: jackpot tier
            user->AddMoney(30000);
            user->SendSysMsg("Lucky Lottery: JACKPOT! +30,000 money!");
        } else { // 2%: grand prize
            user->AddMoney(50000);
            user->AddConquerPoints(10);
            user->SendSysMsg("Lucky Lottery: GRAND PRIZE! +50,000 money, +10 CP!");
            CMsgTalk note;
            if (note.Create("SYSTEM", "", user->GetName() + " hit the lottery GRAND PRIZE!",
                            CMsgTalk::Channel_Broadcast))
                CMapManager::Instance().BroadcastToAll(note.GetBuf(), note.GetSize());
        }
        printf("[LOTTERY] %s roll=%d\n", user->GetName().c_str(), roll);
        return;
    }

    // ---- /quest: daily hunt - kill 10 monsters, claim a reward ----
    if (m_message.rfind("/quest", 0) == 0) {
        // day rollover: reset the counter if the calendar day changed
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
        if (user->m_strQuestDay != today) {
            user->m_strQuestDay = today;
            user->SetQuestClaimed(false);
            user->SetQuestKills(0); // fresh counter for the new day
        }
        if (m_message == "/quest" || m_message == "/quest status") {
            user->SendSysMsg("Daily hunt: kill 10 monsters today for 10,000 money + 10 CP."
                             " Progress: " + std::to_string(user->GetQuestKills()) + "/10" +
                             (user->IsQuestClaimed() ? " (claimed - come back tomorrow)" : ""));
            return;
        }
        if (m_message == "/quest claim") {
            if (user->IsQuestClaimed()) { user->SendSysMsg("You already claimed today's reward."); return; }
            if (user->GetQuestKills() < 10) {
                user->SendSysMsg("Not enough kills yet: " + std::to_string(user->GetQuestKills()) + "/10.");
                return;
            }
            user->SetQuestClaimed(true);
            user->AddMoney(10000);
            user->AddConquerPoints(10);
            user->SendSysMsg("Daily hunt complete! +10,000 money, +10 CP. See you tomorrow.");
            printf("[QUEST] %s claimed the daily hunt\n", user->GetName().c_str());
            return;
        }
        user->SendSysMsg("Usage: /quest | /quest claim");
        return;
    }

    // ---- /arena: free-PvP zone with a kill ladder ----
    if (m_message.rfind("/arena", 0) == 0) {
        std::string sub = m_message.size() > 7 ? m_message.substr(7) : "enter";
        while (!sub.empty() && sub.front() == ' ') sub.erase(0, 1);
        if (sub == "enter") {
            user->Teleport(1038, 50, 50); // arena map
            user->SendSysMsg("Welcome to the Arena! Kills here earn arena points, no PK penalty.");
            return;
        }
        if (sub == "leave") {
            user->Teleport(1002, 315, 275); // back to Twin City
            user->SendSysMsg("You left the Arena.");
            return;
        }
        if (sub == "top") {
            auto rows = CAccountManager::Instance().GetArenaLadder();
            if (rows.empty()) { user->SendSysMsg("No arena fights yet. Be the first!"); return; }
            std::string out = "Arena top " + std::to_string(rows.size()) + ":";
            int rank = 1;
            for (auto& r : rows) {
                out += "\n  " + std::to_string(rank++) + ". " + r.strName +
                       " - " + std::to_string(r.dwKills) + " kills / " +
                       std::to_string(r.dwDeaths) + " deaths";
                if (out.size() > 380) { out += "\n  ..."; break; }
            }
            user->SendSysMsg(out);
            return;
        }
        user->SendSysMsg("Usage: /arena enter | leave | top");
        return;
    }

    // ---- /mine + /dig: mine ore veins for money (profession v1) ----
    if (m_message == "/mine") {
        static const struct { uint16_t x, y, r; } kVeins[] = { // Twin City ore veins
            { 380, 220, 10 }, { 660, 380, 10 }, { 180, 420, 10 },
        };
        bool bAtVein = false;
        for (const auto& v : kVeins) {
            int32_t dx = (int32_t)user->GetX() - v.x;
            int32_t dy = (int32_t)user->GetY() - v.y;
            if (dx * dx + dy * dy <= v.r * v.r) { bAtVein = true; break; }
        }
        if (!bAtVein) { user->SendSysMsg("Find an ore vein to mine (rocky areas)."); return; }
        if (user->GetMineUntil() != 0) { user->SendSysMsg("You are already mining."); return; }
        user->SetMineUntil((uint32_t)time(nullptr) + 6); // 6s swing
        user->SendSysMsg("You swing your pickaxe... wait 6 seconds, then type /dig.");
        return;
    }
    if (m_message == "/dig") {
        uint32_t until = user->GetMineUntil();
        if (until == 0) { user->SendSysMsg("You are not mining. Use /mine first."); return; }
        if ((uint32_t)time(nullptr) < until) { user->SendSysMsg("Too early - the rock is still cracking."); return; }
        user->SetMineUntil(0);
        int roll = std::rand() % 100;
        user->AddOreMined(1); // every resolved dig counts toward rank
        uint32_t bonus = CUser::ProfBonus(user->GetOreMined());
        if (roll < 35) { // 35%: dust
            user->SendSysMsg("Just dust and pebbles.");
        } else if (roll < 75) { // 40%: iron ore
            uint32_t pay = 200 * bonus / 100;
            user->AddMoney(pay);
            user->SendSysMsg("You mined iron ore! +" + std::to_string(pay) +
                             " money (" + CUser::ProfRank(user->GetOreMined()) + " miner).");
            printf("[MINE] %s iron +%u\n", user->GetName().c_str(), pay);
        } else if (roll < 95) { // 20%: copper
            uint32_t pay = 600 * bonus / 100;
            user->AddMoney(pay);
            user->SendSysMsg("You mined a copper vein! +" + std::to_string(pay) + " money.");
            printf("[MINE] %s copper +%u\n", user->GetName().c_str(), pay);
        } else { // 5%: gemstone
            uint32_t pay = 3000 * bonus / 100;
            uint32_t cp = 3 * bonus / 100; if (cp < 3) cp = 3;
            user->AddMoney(pay);
            user->AddConquerPoints(cp);
            user->SendSysMsg("A gemstone sparkles in the rubble! +" + std::to_string(pay) +
                             " money, +" + std::to_string(cp) + " CP.");
            printf("[MINE] %s gem +%u\n", user->GetName().c_str(), pay);
        }
        return;
    }
    if (m_message == "/fish") {
        static const struct { uint16_t x, y, r; } kWater[] = { // Twin City water spots
            { 240, 260, 12 }, { 610, 520, 12 }, { 420, 140, 12 },
        };
        bool bNearWater = false;
        for (const auto& w : kWater) {
            int32_t dx = (int32_t)user->GetX() - w.x;
            int32_t dy = (int32_t)user->GetY() - w.y;
            if (dx * dx + dy * dy <= w.r * w.r) { bNearWater = true; break; }
        }
        if (!bNearWater) { user->SendSysMsg("You need to stand near water to fish."); return; }
        if (user->GetFishUntil() != 0) { user->SendSysMsg("You are already fishing."); return; }
        user->SetFishUntil((uint32_t)time(nullptr) + 8); // 8s cast
        user->SendSysMsg("You cast your line... wait 8 seconds, then type /catch.");
        return;
    }
    if (m_message == "/catch") {
        uint32_t until = user->GetFishUntil();
        if (until == 0) { user->SendSysMsg("You are not fishing. Use /fish first."); return; }
        if ((uint32_t)time(nullptr) < until) { user->SendSysMsg("Too early - the fish is still circling."); return; }
        user->SetFishUntil(0);
        int roll = std::rand() % 100;
        user->AddFishCaught(1); // every resolved cast counts toward rank
        uint32_t bonus = CUser::ProfBonus(user->GetFishCaught());
        if (roll < 45) { // 45%: nothing
            user->SendSysMsg("Nothing took the bait...");
        } else if (roll < 85) { // 40%: common fish +150 money
            uint32_t pay = 150 * bonus / 100;
            user->AddMoney(pay);
            user->SendSysMsg("You caught a small fish! +" + std::to_string(pay) +
                             " money (" + CUser::ProfRank(user->GetFishCaught()) + " angler).");
            printf("[FISH] %s small fish +%u\n", user->GetName().c_str(), pay);
        } else { // 15%: golden fish
            uint32_t pay = 2000 * bonus / 100;
            uint32_t cp = 2 * bonus / 100; if (cp < 2) cp = 2;
            user->AddMoney(pay);
            user->AddConquerPoints(cp);
            user->SendSysMsg("A golden fish! +" + std::to_string(pay) + " money, +" +
                             std::to_string(cp) + " CP.");
            printf("[FISH] %s golden fish +%u\n", user->GetName().c_str(), pay);
        }
        return;
    }
    if (m_message == "/reborn") {
        std::string err = user->Reborn();
        if (!err.empty()) user->SendSysMsg(err);
        return;
    }
    // ---- consumables: /eat ----
    if (m_message == "/eat" || m_message == "/eat pill" || m_message == "/use pill") {
        if (!user->ConsumeByType(725013))
            user->SendSysMsg("No healing pills. Monsters drop them!");
        return;
    }
    // ---- attributes: /stats, /stat <str|vit> <n> ----
    if (m_message == "/stats" || m_message == "/stat") {
        user->SendSysMsg("Str " + std::to_string(user->GetStrength()) +
                         ", Vit " + std::to_string(user->GetVitality()) +
                         ", unspent points: " + std::to_string(user->GetStatPoints()) +
                         " (/stat str|vit <n>)");
        return;
    }
    if (m_message.rfind("/stat ", 0) == 0) {
        std::istringstream iss(m_message.substr(6));
        std::string st; uint32_t n = 1;
        iss >> st >> n;
        std::string err = user->AllocStat(st, n);
        if (!err.empty()) user->SendSysMsg(err);
        return;
    }
    // ---- ground drops: /pick, /drops ----
    if (m_message == "/pick" || m_message == "/pick up") {
        std::string err = CGroundItemManager::Instance().Pick(user);
        if (!err.empty()) user->SendSysMsg(err);
        return;
    }
    if (m_message == "/drops") {
        user->SendSysMsg(CGroundItemManager::Instance().ListNearby(user));
        return;
    }
    // ---- warehouse: /wh deposit|withdraw|info <amount> ----
    if (m_message.rfind("/wh ", 0) == 0 || m_message == "/wh") {
        std::istringstream iss(m_message.size() > 4 ? m_message.substr(4) : "");
        std::string op; int64_t amount = 0;
        iss >> op >> amount;
        if (op == "deposit" && amount > 0) {
            if (user->GetMoney() < (uint64_t)amount) {
                user->SendSysMsg("Not enough money to deposit.");
            } else {
                user->AddMoney(-amount);
                user->AddBank(amount);
                user->SendSysMsg("Deposited " + std::to_string(amount) +
                                 " money. Warehouse: " + std::to_string(user->GetBank()));
            }
        } else if (op == "withdraw" && amount > 0) {
            if (user->GetBank() < (uint64_t)amount) {
                user->SendSysMsg("Warehouse holds only " + std::to_string(user->GetBank()) + ".");
            } else {
                user->AddBank(-amount);
                user->AddMoney(amount);
                user->SendSysMsg("Withdrew " + std::to_string(amount) +
                                 " money. Warehouse: " + std::to_string(user->GetBank()));
            }
        } else {
            user->SendSysMsg("Warehouse: " + std::to_string(user->GetBank()) +
                             " money. Usage: /wh deposit|withdraw <amount>");
        }
        return;
    }
    if (m_message.rfind("/bank", 0) == 0) {
        std::string arg = m_message.length() > 5 ? m_message.substr(6) : "";
        std::string sub;
        size_t sp = arg.find(' ');
        if (sp == std::string::npos) { sub = arg; arg = ""; }
        else { sub = arg.substr(0, sp); arg = arg.substr(sp + 1); }
        uint32_t dwAmount = static_cast<uint32_t>(strtoul(arg.c_str(), nullptr, 10));
        if (sub == "deposit") CNpcManager::Instance().BankDeposit(user, dwAmount);
        else if (sub == "withdraw") CNpcManager::Instance().BankWithdraw(user, dwAmount);
        else user->SendSysMsg("Bank: " + std::to_string(user->GetBank()) +
                              ". Usage: /bank deposit|withdraw <amount>");
        return;
    }
    if (m_message.rfind("/trade", 0) == 0) {
        std::string arg = m_message.length() > 6 ? m_message.substr(7) : "";
        std::string sub;
        size_t sp = arg.find(' ');
        if (sp == std::string::npos) { sub = arg; arg = ""; }
        else { sub = arg.substr(0, sp); arg = arg.substr(sp + 1); }

        if (sub.empty()) {
            user->SendSysMsg("Usage: /trade <player>, /trade add <itemId>, /trade money <amount>, /trade ok, /trade confirm, /trade cancel");
        } else if (sub == "add" || sub == "money") {
            uint32_t dwVal = static_cast<uint32_t>(strtoul(arg.c_str(), nullptr, 10));
            sub == "add" ? CTradeManager::Instance().AddItem(user, dwVal)
                         : CTradeManager::Instance().AddMoney(user, dwVal);
        } else if (sub == "ok") {
            CTradeManager::Instance().Lock(user);
        } else if (sub == "confirm") {
            CTradeManager::Instance().Confirm(user);
        } else if (sub == "cancel") {
            CTradeManager::Instance().Cancel(user);
        } else {
            auto pTarget = CUserManager::Instance().GetUserByName(sub);
            if (pTarget) CTradeManager::Instance().Request(user, pTarget);
            else user->SendSysMsg("Player not online: " + sub);
        }
        return;
    }
    if (m_message.rfind("/guild ", 0) == 0) {
        std::string arg = m_message.substr(7);
        std::string sub;
        size_t sp = arg.find(' ');
        if (sp == std::string::npos) { sub = arg; arg = ""; }
        else { sub = arg.substr(0, sp); arg = arg.substr(sp + 1); }

        bool ok = false;
        std::string note;
        if (sub == "create" && !arg.empty()) {
            ok = CGuildManager::Instance().Create(arg, user);
            note = ok ? "Guild '" + arg + "' created. You are the leader." : "Cannot create (name taken, or leave your current guild first).";
        } else if (sub == "join" && !arg.empty()) {
            ok = CGuildManager::Instance().Join(arg, user);
            note = ok ? "You joined '" + arg + "'." : "Cannot join (no such guild, or leave your current guild first).";
        } else if (sub == "quit") {
            ok = CGuildManager::Instance().Quit(user);
            note = ok ? "You left the guild." : "You are not in a guild.";
        } else if (sub == "disband") {
            ok = CGuildManager::Instance().Disband(user);
            note = ok ? "Guild disbanded." : "Only the guild leader can disband.";
        } else if (sub == "war" && !arg.empty()) {
            ok = CGuildManager::Instance().DeclareWar(user, arg);
            note = ok ? "War declared for 30 minutes!" : "War failed (be a leader, target a real guild, no active war).";
        } else if (sub == "fund") {
            auto g = CGuildManager::Instance().GetByMember(user->GetId());
            note = g ? "Guild fund: " + std::to_string(g->GetFund()) : "You are not in a guild.";
        } else if (sub == "deposit" && !arg.empty()) {
            uint64_t n = strtoull(arg.c_str(), nullptr, 10);
            auto g = CGuildManager::Instance().GetByMember(user->GetId());
            if (!g) note = "You are not in a guild.";
            else if (n == 0) note = "Usage: /guild deposit <amount>";
            else if (user->GetMoney() < n) note = "You only have " + std::to_string(user->GetMoney()) + " money.";
            else {
                user->AddMoney(-(int64_t)n);
                g->AddFund(n);
                std::string what = "deposited " + std::to_string(n) + " (fund " + std::to_string(g->GetFund()) + ")";
                CMsgTalk noteMsg;
                if (noteMsg.Create("SYSTEM", "", user->GetName() + " " + what, CMsgTalk::Channel_Talk))
                    CGuildManager::Instance().Broadcast(g, noteMsg.GetBuf(), noteMsg.GetSize());
                note = "Deposited " + std::to_string(n) + ". Fund: " + std::to_string(g->GetFund());
                ok = true;
            }
        } else if (sub == "withdraw" && !arg.empty()) {
            uint64_t n = strtoull(arg.c_str(), nullptr, 10);
            auto g = CGuildManager::Instance().GetByMember(user->GetId());
            if (!g) note = "You are not in a guild.";
            else if (g->GetLeaderId() != user->GetId()) note = "Only the leader can withdraw.";
            else if (n == 0) note = "Usage: /guild withdraw <amount>";
            else if (!g->TakeFund(n)) note = "Fund only has " + std::to_string(g->GetFund()) + ".";
            else {
                user->AddMoney(n);
                std::string what = "withdrew " + std::to_string(n) + " (fund " + std::to_string(g->GetFund()) + ")";
                CMsgTalk noteMsg;
                if (noteMsg.Create("SYSTEM", "", user->GetName() + " " + what, CMsgTalk::Channel_Talk))
                    CGuildManager::Instance().Broadcast(g, noteMsg.GetBuf(), noteMsg.GetSize());
                note = "Withdrew " + std::to_string(n) + ". Fund: " + std::to_string(g->GetFund());
                ok = true;
            }
        } else if (sub == "warstatus") {
            auto g = CGuildManager::Instance().GetByMember(user->GetId());
            note = (g && CGuildManager::Instance().IsAtWar(g->GetId()))
                   ? "Your guild is at war. Current score: " + std::to_string(g->GetWarScore())
                   : "Your guild is not at war.";
        } else {
            note = "Usage: /guild create|join|quit|disband|war|warstatus|fund|deposit|withdraw [amount|name]";
        }
        user->SendSysMsg(note);
        return;
    }

    // Check for Hidden GM In-Game Command prefix "//"
    if (m_message.rfind("//", 0) == 0) {
        std::string cmdLine = m_message.substr(2);
        std::stringstream ss(cmdLine);
        std::string cmd;
        ss >> cmd;
        std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

        if (cmd == "help") {
            user->SendSysMsg("Hidden GM Commands: //tc, //pc, //ac, //dc, //bi, //market, //teleport <map> <x> <y>, //givecp <amount>, //givemoney <amount>, //level <1-140>, //reborn <1-2>, //vip <1-6>, //godmode, //invisible");
        }
        else if (cmd == "tc") {
            user->Teleport(1002, 430, 380);
        }
        else if (cmd == "pc") {
            user->Teleport(1011, 200, 260);
        }
        else if (cmd == "ac") {
            user->Teleport(1020, 560, 580);
        }
        else if (cmd == "dc") {
            user->Teleport(1000, 500, 650);
        }
        else if (cmd == "bi") {
            user->Teleport(1015, 720, 570);
        }
        else if (cmd == "market") {
            user->Teleport(1036, 210, 200);
        }
        else if (cmd == "teleport") {
            uint32_t mapId = 1002;
            uint16_t x = 400, y = 400;
            if (ss >> mapId >> x >> y) {
                user->Teleport(mapId, x, y);
            } else {
                user->SendSysMsg("Usage: //teleport <mapId> <x> <y>");
            }
        }
        else if (cmd == "givecp" || cmd == "cp") {
            int32_t amount = 0;
            if (ss >> amount && amount > 0) {
                user->AddConquerPoints(amount);
                user->SendSysMsg("Received " + std::to_string(amount) + " CPs! Current Total: " + std::to_string(user->GetConquerPoints()));
            } else {
                user->SendSysMsg("Usage: //givecp <amount>");
            }
        }
        else if (cmd == "givemoney" || cmd == "money") {
            int64_t amount = 0;
            if (ss >> amount && amount > 0) {
                user->AddMoney(amount);
                user->SendSysMsg("Received " + std::to_string(amount) + " Silvers! Current Total: " + std::to_string(user->GetMoney()));
            } else {
                user->SendSysMsg("Usage: //givemoney <amount>");
            }
        }
        else if (cmd == "level" || cmd == "setlevel") {
            int lvl = 1;
            if (ss >> lvl && lvl >= 1 && lvl <= 140) {
                user->SetLevel(static_cast<uint8_t>(lvl));
                user->SendSysMsg("Character Level set to " + std::to_string(lvl));
            } else {
                user->SendSysMsg("Usage: //level <1-140>");
            }
        }
        else if (cmd == "reborn") {
            int r = 1;
            if (ss >> r && r >= 0 && r <= 2) {
                user->SetReborn(static_cast<uint8_t>(r));
                user->SendSysMsg("Character Reborn count set to " + std::to_string(r));
            } else {
                user->SendSysMsg("Usage: //reborn <0-2>");
            }
        }
        else if (cmd == "vip") {
            int v = 6;
            if (ss >> v && v >= 0 && v <= 6) {
                user->SetVipLevel(static_cast<uint8_t>(v));
                user->SendSysMsg("VIP Level set to " + std::to_string(v));
            } else {
                user->SendSysMsg("Usage: //vip <0-6>");
            }
        }
        else if (cmd == "godmode") {
            user->SetGodMode(!user->IsGodMode());
            user->SendSysMsg(std::string("God Mode: ") + (user->IsGodMode() ? "ENABLED (Invulnerable)" : "DISABLED"));
        }
        else if (cmd == "invisible") {
            user->SetInvisible(!user->IsInvisible());
            user->SendSysMsg(std::string("Invisibility: ") + (user->IsInvisible() ? "ENABLED (Hidden from players)" : "DISABLED"));
        }
        else {
            user->SendSysMsg("Unknown GM Command: //" + cmd + ". Type //help for command list.");
        }
        return;
    }
}