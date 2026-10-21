#include "Npc.h"
#include "User.h"
#include "UserManager.h"
#include "MsgTalk.h"

#include <cstdio>

CNpc::CNpc(uint32_t dwId, const std::string& name, Type type,
           uint32_t dwMapId, uint16_t usX, uint16_t usY)
    : m_dwId(dwId), m_name(name), m_type(type),
      m_dwMapId(dwMapId), m_usX(usX), m_usY(usY) {}

void CNpc::Interact(std::shared_ptr<CUser> pUser) {
    if (!pUser) return;
    if (pUser->GetMapId() != m_dwMapId) {
        pUser->SendSysMsg("That NPC is not on your map.");
        return;
    }
    if (!m_strDialog.empty()) pUser->SendSysMsg(m_strDialog);

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

CNpcManager& CNpcManager::Instance() {
    static CNpcManager s_instance;
    return s_instance;
}

void CNpcManager::SpawnDefaults() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_bSpawned) return;
    m_bSpawned = true;

    auto add = [&](uint32_t dwId, const std::string& name, CNpc::Type type,
                   uint32_t dwMapId, uint16_t x, uint16_t y,
                   const std::string& dialog) {
        auto p = std::make_shared<CNpc>(dwId, name, type, dwMapId, x, y);
        p->m_strDialog = dialog;
        m_npcs[dwId] = p;
    };

    // Twin City (1002) - v1 roster, coords approximate until the MsgNpc
    // spawn packet port makes them visible client-side
    add(NPC_ID_BASE + 1, "Pharmacist", CNpc::Type::Healer, 1002, 310, 265,
        "Welcome! I can restore your health, free of charge.");
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
