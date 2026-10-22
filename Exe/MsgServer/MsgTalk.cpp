#include "MsgTalk.h"
#include "StringPacker.h"
#include "UserManager.h"
#include "Guild.h"
#include "Trade.h"
#include "Team.h"
#include "GroundItems.h"
#include "Npc.h"
#include "User.h"
#include "Item.h"
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
        } else if (sub == "warstatus") {
            auto g = CGuildManager::Instance().GetByMember(user->GetId());
            note = (g && CGuildManager::Instance().IsAtWar(g->GetId()))
                   ? "Your guild is at war. Current score: " + std::to_string(g->GetWarScore())
                   : "Your guild is not at war.";
        } else {
            note = "Usage: /guild create|join|quit|disband|war|warstatus [name]";
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