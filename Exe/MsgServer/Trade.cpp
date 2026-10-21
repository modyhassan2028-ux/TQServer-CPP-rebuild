#include "Trade.h"
#include "User.h"
#include "UserManager.h"

#include <cstdio>

CTradeSession::CTradeSession(uint32_t dwA, uint32_t dwB)
    : m_dwUserA(dwA), m_dwUserB(dwB) {}

CTradeManager& CTradeManager::Instance() {
    static CTradeManager s_instance;
    return s_instance;
}

// internal, callers already hold m_mutex
std::shared_ptr<CTradeSession> CTradeManager::Find(uint32_t dwUserId) {
    auto it = m_sessions.find(dwUserId);
    return it == m_sessions.end() ? nullptr : it->second;
}

void CTradeManager::DropSession(CTradeSession* pSession) {
    for (auto it = m_sessions.begin(); it != m_sessions.end();) {
        if (it->second.get() == pSession) it = m_sessions.erase(it);
        else ++it;
    }
}

std::shared_ptr<CTradeSession> CTradeManager::GetSession(uint32_t dwUserId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    return Find(dwUserId);
}

void CTradeManager::Request(std::shared_ptr<CUser> pFrom, std::shared_ptr<CUser> pTo) {
    if (!pFrom || !pTo || pFrom->GetId() == pTo->GetId()) return;
    std::lock_guard<std::mutex> lock(m_mutex);
    if (Find(pFrom->GetId()) || Find(pTo->GetId())) {
        pFrom->SendSysMsg("One of you is already trading. /trade cancel first.");
        return;
    }
    auto pSession = std::make_shared<CTradeSession>(pFrom->GetId(), pTo->GetId());
    m_sessions[pFrom->GetId()] = pSession;
    m_sessions[pTo->GetId()] = pSession;
    pFrom->SendSysMsg("Trade opened with " + pTo->GetName() + ". Add items: /trade add <itemId>, money: /trade money <amount>, then /trade ok");
    pTo->SendSysMsg(pFrom->GetName() + " opened a trade with you. Add items: /trade add <itemId>, money: /trade money <amount>, then /trade ok");
    printf("[TRADE] %s requested trade with %s\n",
           pFrom->GetName().c_str(), pTo->GetName().c_str());
}

bool CTradeManager::AddItem(std::shared_ptr<CUser> pUser, uint32_t dwItemId) {
    if (!pUser) return false;
    std::lock_guard<std::mutex> lock(m_mutex);
    auto pSession = Find(pUser->GetId());
    if (!pSession) { pUser->SendSysMsg("No active trade. /trade <player> first."); return false; }
    auto& offer = pSession->Side(pUser->GetId());
    if (offer.locked) { pUser->SendSysMsg("You already locked your offer."); return false; }
    if (!pUser->FindItem(dwItemId)) { pUser->SendSysMsg("You do not have that item."); return false; }
    if (!offer.items.insert(dwItemId).second) { pUser->SendSysMsg("Item already offered."); return false; }

    auto pOther = CUserManager::Instance().GetUser(pSession->Other(pUser->GetId()));
    if (pOther) pOther->SendSysMsg(pUser->GetName() + " offered item " + std::to_string(dwItemId));
    return true;
}

bool CTradeManager::AddMoney(std::shared_ptr<CUser> pUser, uint32_t dwAmount) {
    if (!pUser) return false;
    std::lock_guard<std::mutex> lock(m_mutex);
    auto pSession = Find(pUser->GetId());
    if (!pSession) { pUser->SendSysMsg("No active trade."); return false; }
    auto& offer = pSession->Side(pUser->GetId());
    if (offer.locked) { pUser->SendSysMsg("You already locked your offer."); return false; }
    if (dwAmount == 0 || pUser->GetMoney() < dwAmount) { pUser->SendSysMsg("Invalid amount."); return false; }
    offer.money = dwAmount;

    auto pOther = CUserManager::Instance().GetUser(pSession->Other(pUser->GetId()));
    if (pOther) pOther->SendSysMsg(pUser->GetName() + " offered " + std::to_string(dwAmount) + " money.");
    return true;
}

bool CTradeManager::Lock(std::shared_ptr<CUser> pUser) {
    if (!pUser) return false;
    std::lock_guard<std::mutex> lock(m_mutex);
    auto pSession = Find(pUser->GetId());
    if (!pSession) { pUser->SendSysMsg("No active trade."); return false; }
    auto& offer = pSession->Side(pUser->GetId());
    offer.locked = true;

    auto pOther = CUserManager::Instance().GetUser(pSession->Other(pUser->GetId()));
    if (pOther) pOther->SendSysMsg(pUser->GetName() + " locked their offer.");
    if (pSession->BothLocked())
        pUser->SendSysMsg("Both sides locked. Both type /trade confirm to execute.");
    return true;
}

bool CTradeManager::Confirm(std::shared_ptr<CUser> pUser) {
    if (!pUser) return false;
    uint32_t dwOtherId;
    std::shared_ptr<CTradeSession> pSession;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        pSession = Find(pUser->GetId());
        if (!pSession) { pUser->SendSysMsg("No active trade."); return false; }
        if (!pSession->BothLocked()) { pUser->SendSysMsg("Both sides must lock first (/trade ok)."); return false; }
        dwOtherId = pSession->Other(pUser->GetId());
    }

    auto pOther = CUserManager::Instance().GetUser(dwOtherId);
    if (!pOther) { pUser->SendSysMsg("Trading partner went offline."); Cancel(pUser); return false; }

    auto& myOffer = pSession->Side(pUser->GetId());
    auto& otherOffer = pSession->Side(dwOtherId);

    // atomic swap: money first, then items
    pUser->SetMoney(pUser->GetMoney() - myOffer.money + otherOffer.money);
    pOther->SetMoney(pOther->GetMoney() - otherOffer.money + myOffer.money);

    for (uint32_t dwItemId : myOffer.items) {
        ItemInfo info;
        if (auto* p = pUser->FindItem(dwItemId)) info = *p;
        pUser->RemoveItem(dwItemId);
        pOther->AddItem(info);
    }
    for (uint32_t dwItemId : otherOffer.items) {
        ItemInfo info;
        if (auto* p = pOther->FindItem(dwItemId)) info = *p;
        pOther->RemoveItem(dwItemId);
        pUser->AddItem(info);
    }

    pUser->SendSysMsg("Trade complete.");
    pOther->SendSysMsg("Trade complete.");
    printf("[TRADE] Trade executed between %s and %s (money %u<->%u)\n",
           pUser->GetName().c_str(), pOther->GetName().c_str(),
           myOffer.money, otherOffer.money);

    std::lock_guard<std::mutex> lock(m_mutex);
    DropSession(pSession.get());
    return true;
}

bool CTradeManager::Cancel(std::shared_ptr<CUser> pUser) {
    if (!pUser) return false;
    std::lock_guard<std::mutex> lock(m_mutex);
    auto pSession = Find(pUser->GetId());
    if (!pSession) return false;
    uint32_t dwOtherId = pSession->Other(pUser->GetId());
    DropSession(pSession.get());

    auto pOther = CUserManager::Instance().GetUser(dwOtherId);
    if (pOther) pOther->SendSysMsg(pUser->GetName() + " canceled the trade.");
    pUser->SendSysMsg("Trade canceled.");
    return true;
}
