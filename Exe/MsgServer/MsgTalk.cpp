#include "MsgTalk.h"
#include "StringPacker.h"
#include "UserManager.h"
#include "Guild.h"
#include "User.h"
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
        } else {
            note = "Usage: /guild create|join|quit|disband [name]";
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