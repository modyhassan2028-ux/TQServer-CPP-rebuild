#include "Npc.h"
#include "Dialog.h"
#include "MySQLClient.h"
#include "Account.h"
#include "User.h"
#include "UserManager.h"
#include "MsgTalk.h"

#include <cstdio>

CNpc::CNpc(uint32_t dwId, const std::string& name, Type type,
           uint32_t dwMapId, uint16_t usX, uint16_t usY)
    : m_dwId(dwId), m_name(name), m_type(type),
      m_dwMapId(dwMapId), m_usX(usX), m_usY(usY) {}


// shows a cq_action node: its text plus the numbered options beneath it
static void ShowDialogNode(std::shared_ptr<CUser> pUser, uint32_t dwNodeId) {
    auto& eng = CDialogEngine::Instance();
    auto* pNode = eng.GetNode(dwNodeId);
    if (!pNode) return;
    pUser->SetDialogNode(dwNodeId);
    if (!pNode->strText.empty()) pUser->SendSysMsg(pNode->strText);
    auto opts = eng.GetOptions(dwNodeId);
    if (!opts.empty()) {
        std::string menu = "Options:";
        uint32_t i = 1;
        for (auto& o : opts) menu += "\n  " + std::to_string(i++) + ". " + o.strText;
        pUser->SendSysMsg(menu);
    }
}

void CNpc::Interact(std::shared_ptr<CUser> pUser) {
    if (!pUser) return;
    if (pUser->GetMapId() != m_dwMapId) {
        pUser->SendSysMsg("That NPC is not on your map.");
        return;
    }
    pUser->SetTalkingNpc(GetId()); // digit replies now route to this NPC
    // cq_action dialog tree (original 6159 system) takes priority when loaded
    if (m_dwActionId && CDialogEngine::Instance().HasNode(m_dwActionId)) {
        ShowDialogNode(pUser, m_dwActionId);
        return;
    }
    if (!m_strDialog.empty()) pUser->SendSysMsg(m_strDialog);
    // numbered menu (original 6159 style: pick by replying with the number)
    if (!m_options.empty()) {
        std::string menu = "Options:";
        uint32_t i = 1;
        for (auto& o : m_options)
            menu += "\n  " + std::to_string(i++) + ". " + o.text;
        pUser->SendSysMsg(menu);
    }

    if (!m_options.empty()) return; // menu-driven NPCs act on choice
    switch (m_type) {
    case Type::Healer:
        pUser->SetLife(pUser->GetMaxLife());
        pUser->SendSysMsg("You feel refreshed. Life fully restored.");
        printf("[NPC] %s healed by %s\n", pUser->GetName().c_str(), m_name.c_str());
        break;

    case Type::Warehouse:
        pUser->SendSysMsg("Warehouse balance: " + std::to_string(pUser->GetBank()) +
                          " money. Commands: /bank deposit <amount>, /bank withdraw <amount>");
        printf("[NPC] %s opened warehouse with %s\n",
               pUser->GetName().c_str(), m_name.c_str());
        break;

    case Type::Teleporter:
        if (m_dwDestMap == 0) return;
        pUser->Teleport(m_dwDestMap, m_usDestX, m_usDestY);
        pUser->SendSysMsg("Teleported by " + m_name + ".");
        printf("[NPC] %s teleported to map %u via %s\n",
               pUser->GetName().c_str(), m_dwDestMap, m_name.c_str());
        break;
    }
}


bool CNpc::ChooseOption(std::shared_ptr<CUser> pUser, uint32_t dwIndex) {
    if (!pUser) return false;
    // cq_action tree: follow the numbered option the player picked
    if (m_dwActionId && CDialogEngine::Instance().IsLoaded()) {
        uint32_t dwCur = pUser->GetDialogNode();
        if (!dwCur || !CDialogEngine::Instance().HasNode(dwCur)) dwCur = m_dwActionId;
        auto opts = CDialogEngine::Instance().GetOptions(dwCur);
        if (dwIndex >= 1 && dwIndex <= opts.size()) {
            auto& o = opts[dwIndex - 1];
            auto* pOpt = CDialogEngine::Instance().GetNode(o.dwTargetNode);
            if (!pOpt) return false;
            switch (pOpt->dwType) {
            case 2: { // accept task: param = task id
                uint32_t dwTaskId = (uint32_t)strtoul(pOpt->strParam.c_str(), nullptr, 10);
                if (pUser->HasActiveTask()) { pUser->SendSysMsg("Finish your current task first!"); return true; }
                // look the task up in the data library
                auto& tasks = CNpcManager::Instance().GetTasks();
                for (const auto& d : tasks) {
                    if (d.dwId != dwTaskId) continue;
                    if (pUser->GetLevel() < d.dwMinLevel) {
                        pUser->SendSysMsg("Come back at level " + std::to_string(d.dwMinLevel) + ".");
                        return true;
                    }
                    pUser->m_task.dwNpcId = GetId();
                    pUser->m_task.dwMonsterType = d.dwMonsterType;
                    pUser->m_task.dwNeeded = d.dwCount;
                    pUser->m_task.dwDone = 0;
                    pUser->m_task.dwRewardMoney = d.dwMoney;
                    pUser->m_task.dwRewardCp = d.dwCp;
                    pUser->SendSysMsg("Task accepted: " + d.strName + "! Kill " +
                                      std::to_string(d.dwCount) + " monster(s), then return.");
                    return true;
                }
                pUser->SendSysMsg("That task is not available.");
                return true;
            }
            case 3: { // turn-in: reuse the v1 flow by delegating to a matching static option
                if (pUser->HasActiveTask() && pUser->m_task.dwDone >= pUser->m_task.dwNeeded) {
                    pUser->AddMoney(pUser->m_task.dwRewardMoney);
                    pUser->AddConquerPoints(pUser->m_task.dwRewardCp);
                    pUser->SendSysMsg("Task complete! Reward: " +
                                      std::to_string(pUser->m_task.dwRewardMoney) + " money, " +
                                      std::to_string(pUser->m_task.dwRewardCp) + " CP.");
                    pUser->m_task = {};
                    return true;
                }
                pUser->SendSysMsg(pUser->HasActiveTask()
                    ? "Not done yet: " + std::to_string(pUser->m_task.dwDone) + "/" +
                      std::to_string(pUser->m_task.dwNeeded) + " killed."
                    : "You have no task with me.");
                return true;
            }
            case 4: { // teleport: param = "map,x,y"
                uint32_t map = 0; int x = 0, y = 0;
                if (sscanf(pOpt->strParam.c_str(), "%u,%d,%d", &map, &x, &y) == 3 && map) {
                    pUser->SetDialogNode(0);
                    pUser->Teleport(map, (uint16_t)x, (uint16_t)y);
                    return true;
                }
                pUser->SendSysMsg("This gate is broken (bad param).");
                return true;
            }
            default: // 0/1: just walk the tree
                pUser->SetDialogNode(0);
                ShowDialogNode(pUser, pOpt->dwNext);
                return true;
            }
        }
        pUser->SendSysMsg("No such option. Talk to me again.");
        return false;
    }
    if (dwIndex == 0 || dwIndex > m_options.size()) {
        pUser->SendSysMsg("No such option. Talk to me again (/npc " +
                          std::to_string(m_dwId) + ").");
        return false;
    }
    const NpcOption& o = m_options[dwIndex - 1];
    switch (o.action) {
    case NpcOption::Action::Heal:
        pUser->SetLife(pUser->GetMaxLife());
        pUser->SendSysMsg("Life fully restored!");
        break;
    case NpcOption::Action::BankBalance:
        pUser->SendSysMsg("Bank balance: " + std::to_string(pUser->GetBank()));
        break;
    case NpcOption::Action::BankDeposit:
        pUser->SendSysMsg("How much? /bank deposit <amount>");
        break;
    case NpcOption::Action::BankWithdraw:
        pUser->SendSysMsg("How much? /bank withdraw <amount>");
        break;
    case NpcOption::Action::Teleport:
        pUser->Teleport(o.dwDestMap, o.usDestX, o.usDestY);
        break;
    case NpcOption::Action::AcceptTask:
        if (pUser->HasActiveTask()) {
            pUser->SendSysMsg("Finish your current task first!");
        } else {
            pUser->m_task.dwNpcId = m_dwId;
            pUser->m_task.dwMonsterType = o.dwTaskMonsterType;
            pUser->m_task.dwNeeded = o.dwTaskCount;
            pUser->m_task.dwDone = 0;
            pUser->m_task.dwRewardMoney = o.dwTaskMoney;
            pUser->m_task.dwRewardCp = o.dwTaskCp;
            pUser->SendSysMsg("Task accepted! Kill " + std::to_string(o.dwTaskCount) +
                              " monsters (type " + std::to_string(o.dwTaskMonsterType) +
                              ") then return to me.");
        }
        break;
    case NpcOption::Action::TurnInTask:
        if (!pUser->HasActiveTask() || pUser->m_task.dwNpcId != m_dwId) {
            pUser->SendSysMsg("You have no task with me. Pick one from my menu.");
        } else if (pUser->m_task.dwDone < pUser->m_task.dwNeeded) {
            pUser->SendSysMsg("Not done yet: " + std::to_string(pUser->m_task.dwDone) + "/" +
                              std::to_string(pUser->m_task.dwNeeded) + " killed.");
        } else {
            pUser->AddMoney(pUser->m_task.dwRewardMoney);
            pUser->AddConquerPoints(pUser->m_task.dwRewardCp);
            pUser->SendSysMsg("Task complete! Reward: " +
                              std::to_string(pUser->m_task.dwRewardMoney) + " money, " +
                              std::to_string(pUser->m_task.dwRewardCp) + " CP.");
            pUser->m_task = {};
            printf("[TASK] %s turned in a hunt task at %s\n",
                   pUser->GetName().c_str(), m_name.c_str());
        }
        break;
    case NpcOption::Action::Chat:
    default:
        if (!o.text.empty()) pUser->SendSysMsg(o.text);
        break;
    }
    printf("[NPC] %s chose option %u on %s\n",
           pUser->GetName().c_str(), dwIndex, m_name.c_str());
    return true;
}


// data/tasks.ini - one task per line:
// id | name | npc_id | monster_type | count | money | cp | min_level
uint32_t CNpcManager::LoadTasks(const std::string& path) {
    m_taskDefs.clear();
    FILE* f = fopen(path.c_str(), "r");
    if (!f) { printf("[TASK] %s not found - keeping the built-in defaults.\n", path.c_str()); return 0; }
    char line[512];
    while (fgets(line, sizeof(line), f)) {
        std::string ln(line);
        // strip comments and newlines
        size_t hash = ln.find_first_of("#\r\n");
        if (hash != std::string::npos) ln = ln.substr(0, hash);
        if (ln.find_first_not_of(" \t") == std::string::npos) continue;
        std::vector<std::string> parts;
        size_t pos = 0;
        while (pos < ln.size()) {
            size_t bar = ln.find('|', pos);
            if (bar == std::string::npos) bar = ln.size();
            std::string part = ln.substr(pos, bar - pos);
            // trim
            size_t b = part.find_first_not_of(" \t");
            size_t e = part.find_last_not_of(" \t");
            parts.push_back(b == std::string::npos ? "" : part.substr(b, e - b + 1));
            pos = bar + 1;
        }
        if (parts.size() < 7) continue;
        TaskDef d;
        d.dwId          = (uint32_t)strtoul(parts[0].c_str(), nullptr, 10);
        d.strName       = parts[1];
        d.dwNpcId       = (uint32_t)strtoul(parts[2].c_str(), nullptr, 10);
        d.dwMonsterType = (uint32_t)strtoul(parts[3].c_str(), nullptr, 10);
        d.dwCount       = (uint32_t)strtoul(parts[4].c_str(), nullptr, 10);
        d.dwMoney       = (uint32_t)strtoul(parts[5].c_str(), nullptr, 10);
        d.dwCp          = (uint32_t)strtoul(parts[6].c_str(), nullptr, 10);
        d.dwMinLevel    = parts.size() > 7 ? (uint32_t)strtoul(parts[7].c_str(), nullptr, 10) : 1;
        if (d.dwId && d.dwCount) m_taskDefs.push_back(d);
    }
    fclose(f);
    printf("[TASK] Loaded %zu task definition(s) from %s.\n", m_taskDefs.size(), path.c_str());
    return (uint32_t)m_taskDefs.size();
}

CNpcManager& CNpcManager::Instance() {
    static CNpcManager s_instance;
    return s_instance;
}


// original 6159 model: every NPC lives in cq_npc
//  id, name, type, map_id, x, y, lookface, action_id
// type: 0=generic(dialog-driven), 1=healer, 2=warehouse, 3=teleporter
uint32_t CNpcManager::SpawnNpcsFromDB(CMySQLClient* pDB) {
    if (!pDB) return 0;
    if (!pDB->Query("SELECT id, name, type, map_id, x, y, lookface, action_id FROM cq_npc")) {
        printf("[NPC] cq_npc load failed: %s\n", pDB->GetError().c_str());
        return 0;
    }
    std::lock_guard<std::mutex> lock(m_mutex);
    uint32_t spawned = 0;
    for (auto& row : pDB->GetRows()) {
        if (row.size() < 8) continue;
        uint32_t id = (uint32_t)strtoul(row[0].c_str(), nullptr, 10);
        uint32_t type = (uint32_t)strtoul(row[2].c_str(), nullptr, 10);
        uint32_t mapId = (uint32_t)strtoul(row[3].c_str(), nullptr, 10);
        uint16_t x = (uint16_t)strtoul(row[4].c_str(), nullptr, 10);
        uint16_t y = (uint16_t)strtoul(row[5].c_str(), nullptr, 10);
        uint32_t lookface = (uint32_t)strtoul(row[6].c_str(), nullptr, 10);
        uint32_t actionId = (uint32_t)strtoul(row[7].c_str(), nullptr, 10);
        if (!id || !mapId) continue;
        CNpc::Type eType = (type == 1) ? CNpc::Type::Healer
                        : (type == 2) ? CNpc::Type::Warehouse
                        : (type == 3) ? CNpc::Type::Teleporter
                        : CNpc::Type::Healer; // generic NPCs default to Healer shell; dialogs drive behavior
        auto p = std::make_shared<CNpc>(id, row[1], eType, mapId, x, y);
        p->m_dwLookface = lookface;
        p->m_dwActionId = actionId; // cq_action tree root (0 = plain text greeting)
        m_npcs[id] = p;
        ++spawned;
    }
    printf("[NPC] cq_npc: spawned %u NPCs from MySQL.\n", spawned);
    return spawned;
}

void CNpcManager::SpawnDefaults() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_bSpawned) return;
    m_bSpawned = true;

    // original data model first: every NPC from cq_npc
    if (CAccountManager::Instance().IsMySQLMode() &&
        SpawnNpcsFromDB(CAccountManager::Instance().GetDB()) > 0) {
        LoadTasks("data/tasks.ini");
        if (CAccountManager::Instance().GetDB())
            CDialogEngine::Instance().LoadFromDB(CAccountManager::Instance().GetDB());
        return; // DB world wins; built-in roster skipped
    }


    auto add = [&](uint32_t dwId, const std::string& name, CNpc::Type type,
                   uint32_t dwMapId, uint16_t x, uint16_t y,
                   const std::string& dialog) {
        auto p = std::make_shared<CNpc>(dwId, name, type, dwMapId, x, y);
        p->m_strDialog = dialog;
        m_npcs[dwId] = p;
    };

    // Twin City (1002) - v1 roster, coords approximate until the MsgNpc
    // spawn packet port makes them visible client-side
    {
        auto pHealer = std::make_shared<CNpc>(NPC_ID_BASE + 1, "Pharmacist",
            CNpc::Type::Healer, 1002, 310, 265);
        pHealer->m_dwLookface = 8301;
        pHealer->m_strDialog = "Welcome! I can restore your health, free of charge.";
        NpcOption heal; heal.action = NpcOption::Action::Heal;
        heal.text = "Heal me, please.";
        pHealer->m_options.push_back(heal);
        NpcOption bye; bye.action = NpcOption::Action::Chat; bye.text = "I am fine, thanks.";
        pHealer->m_options.push_back(bye);
        m_npcs[pHealer->GetId()] = pHealer;
    }
    add(NPC_ID_BASE + 2, "WarehouseMan", CNpc::Type::Warehouse, 1002, 300, 270,
        "I keep your money safe. You can deposit or withdraw anytime.");
    // placeholder client mesh ids; the real values come from the client npc ini
    m_npcs[NPC_ID_BASE + 1]->m_dwLookface = 8301;  // pharmacist
    m_npcs[NPC_ID_BASE + 2]->m_dwLookface = 8302;  // warehouse
    auto pTcToDesert = std::make_shared<CNpc>(NPC_ID_BASE + 3, "CityGuard",
        CNpc::Type::Teleporter, 1002, 320, 270);
    pTcToDesert->m_dwDestMap = 1000; pTcToDesert->m_usDestX = 500; pTcToDesert->m_usDestY = 600;
    pTcToDesert->m_strDialog = "Need a ride to the Desert? Off you go!";
    pTcToDesert->m_dwLookface = 8303;
    m_npcs[pTcToDesert->GetId()] = pTcToDesert;

    // Desert (1000): way back to Twin City
    auto pDesertToTc = std::make_shared<CNpc>(NPC_ID_BASE + 4, "DesertGuard",
        CNpc::Type::Teleporter, 1000, 505, 605);
    pDesertToTc->m_dwDestMap = 1002; pDesertToTc->m_usDestX = 315; pDesertToTc->m_usDestY = 275;
    pDesertToTc->m_strDialog = "Back to Twin City it is!";
    pDesertToTc->m_dwLookface = 8304;
    m_npcs[pDesertToTc->GetId()] = pDesertToTc;

    LoadTasks("data/tasks.ini"); // data-driven task library (before TaskMaster menu)
    // original 6159 system: cq_action dialog trees from MySQL
    if (CAccountManager::Instance().IsMySQLMode() && CAccountManager::Instance().GetDB())
        CDialogEngine::Instance().LoadFromDB(CAccountManager::Instance().GetDB());

    // Twin City hub: gates to every base map (coords land on walkable dmap cells
    // once real maps are indexed; synthetic maps fall back to these values)
    struct Gate { const char* name; uint32_t dest, x, y; };
    static const Gate kGates[] = {
        {"DesertGate",    1000, 500, 600},
        {"CanyonGate",    1001, 500, 600},
        {"BirdIslandGate",1015, 200, 300},
        {"ApeMountainGate",1020, 200, 300},
    };
    uint32_t dwGateId = NPC_ID_BASE + 10;
    for (const auto& g : kGates) {
        auto pGate = std::make_shared<CNpc>(dwGateId++, g.name,
            CNpc::Type::Teleporter, 1002, 330, 270 + (uint16_t)(dwGateId - NPC_ID_BASE));
        pGate->m_dwDestMap = g.dest; pGate->m_usDestX = g.x; pGate->m_usDestY = g.y;
        pGate->m_dwLookface = 8300 + (dwGateId - NPC_ID_BASE);
        pGate->m_strDialog = "Traveler! Where to?";
        {
            NpcOption op;
            op.action = NpcOption::Action::Teleport;
            op.text = std::string("Travel to map ") + std::to_string(g.dest);
            op.dwDestMap = g.dest; op.usDestX = g.x; op.usDestY = g.y;
            pGate->m_options.push_back(op);
        }
        {
            NpcOption op;
            op.action = NpcOption::Action::Chat;
            op.text = "Just passing by.";
            pGate->m_options.push_back(op);
        }
        m_npcs[pGate->GetId()] = pGate;
        // return gate on the destination map
        auto pBack = std::make_shared<CNpc>(dwGateId++, g.name,
            CNpc::Type::Teleporter, g.dest, (uint16_t)(g.x + 5), (uint16_t)(g.y + 5));
        pBack->m_dwDestMap = 1002; pBack->m_usDestX = 335; pBack->m_usDestY = 275;
        pBack->m_dwLookface = 8300 + (dwGateId - NPC_ID_BASE);
        pBack->m_strDialog = "Done out here?";
        {
            NpcOption op;
            op.action = NpcOption::Action::Teleport;
            op.text = "Return to Twin City";
            op.dwDestMap = 1002; op.usDestX = 335; op.usDestY = 275;
            pBack->m_options.push_back(op);
        }
        m_npcs[pBack->GetId()] = pBack;
    }

    // TaskMaster: menu built from the data-driven task library
    // (built-in defaults mirror the original starter hunts; data/tasks.ini wins)
    if (m_taskDefs.empty()) {
        m_taskDefs.push_back({1001, "RatRumble",  NPC_ID_BASE + 5, 0, 5, 500, 2, 1});
        m_taskDefs.push_back({1002, "WolfWhisper", NPC_ID_BASE + 5, 0, 15, 2000, 10, 10});
    }
    {
        auto pTm = std::make_shared<CNpc>(NPC_ID_BASE + 5, "TaskMaster",
            CNpc::Type::Healer, 1002, 315, 260); // type unused; menu-driven
        pTm->m_dwLookface = 8305;
        pTm->m_dwActionId = 5000; // cq_action tree root (sql/seed_dialog.sql)
        pTm->m_strDialog = "Adventurer! I have work for hunters of any skill.";
        for (const auto& d : m_taskDefs) {
            if (d.dwNpcId != pTm->GetId()) continue;
            NpcOption t;
            t.action = NpcOption::Action::AcceptTask;
            t.text = d.strName + ": kill " + std::to_string(d.dwCount) + " monsters for " +
                     std::to_string(d.dwMoney) + " money + " + std::to_string(d.dwCp) + " CP";
            t.dwTaskMonsterType = d.dwMonsterType;
            t.dwTaskCount = d.dwCount;
            t.dwTaskMoney = d.dwMoney;
            t.dwTaskCp = d.dwCp;
            pTm->m_options.push_back(t);
        }
        NpcOption ti;
        ti.action = NpcOption::Action::TurnInTask;
        ti.text = "I finished my task - pay me!";
        pTm->m_options.push_back(ti);
        NpcOption no;
        no.action = NpcOption::Action::Chat;
        no.text = "Maybe later.";
        pTm->m_options.push_back(no);
        m_npcs[pTm->GetId()] = pTm;
    }

    printf("[NPC] Spawned %zu default NPC(s).\n", m_npcs.size());
}

std::shared_ptr<CNpc> CNpcManager::GetNpc(uint32_t dwId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_npcs.find(dwId);
    return it == m_npcs.end() ? nullptr : it->second;
}

std::vector<std::shared_ptr<CNpc>> CNpcManager::GetNpcsOnMap(uint32_t dwMapId) {
    SpawnDefaults();
    std::lock_guard<std::mutex> lock(m_mutex);
    std::vector<std::shared_ptr<CNpc>> out;
    for (auto& kv : m_npcs)
        if (kv.second->GetMapId() == dwMapId) out.push_back(kv.second);
    return out;
}

bool CNpcManager::BankDeposit(std::shared_ptr<CUser> pUser, uint32_t dwAmount) {
    if (!pUser || dwAmount == 0) return false;
    if (pUser->GetMoney() < dwAmount) { pUser->SendSysMsg("Not enough money."); return false; }
    pUser->SetMoney(pUser->GetMoney() - dwAmount);
    pUser->SetBank(pUser->GetBank() + dwAmount);
    pUser->SendSysMsg("Deposited. Bank: " + std::to_string(pUser->GetBank()));
    return true;
}

bool CNpcManager::BankWithdraw(std::shared_ptr<CUser> pUser, uint32_t dwAmount) {
    if (!pUser || dwAmount == 0) return false;
    if (pUser->GetBank() < dwAmount) { pUser->SendSysMsg("Not enough in the bank."); return false; }
    pUser->SetBank(pUser->GetBank() - dwAmount);
    pUser->SetMoney(pUser->GetMoney() + dwAmount);
    pUser->SendSysMsg("Withdrew. Bank: " + std::to_string(pUser->GetBank()));
    return true;
}
