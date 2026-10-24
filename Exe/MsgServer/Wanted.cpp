#include "Wanted.h"
#include "User.h"
#include "UserManager.h"
#include "Guild.h"
#include <cstdio>

CWantedManager& CWantedManager::Instance() {
    static CWantedManager s_mgr;
    return s_mgr;
}

bool CWantedManager::SetTargetBy(uint32_t dwUserId, const std::string& strName) { // +0x120
    std::lock_guard<std::mutex> lock(m_mutex);
    if (strName.empty()) return false;
    auto u = CUserManager::Instance().GetUser(dwUserId);
    if (u && strName == u->GetName()) return false; // own name refused
    m_drafts[dwUserId].strTarget = strName;
    return true;
}

bool CWantedManager::SetAmountBy(uint32_t dwUserId, uint32_t dwAmount) { // +0x130
    std::lock_guard<std::mutex> lock(m_mutex);
    m_drafts[dwUserId].dwAmount = dwAmount;
    return true; // ORIGINAL: unconditional true after the caller's checks
}

uint32_t CWantedManager::GetAmountBy(uint32_t dwUserId) { // +0x128
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_drafts.find(dwUserId);
    return it == m_drafts.end() ? 0 : it->second.dwAmount;
}

bool CWantedManager::GetDraftBy(uint32_t dwUserId, SWantedRec& rec) { // +0x118
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_drafts.find(dwUserId);
    if (it == m_drafts.end() || it->second.strTarget.empty()) return false;
    rec = it->second;
    return true;
}

bool CWantedManager::PublishDraft(SWantedRec& rec, const std::string& strOwner,
                                  uint32_t dwAmount) { // +0x70
    std::lock_guard<std::mutex> lock(m_mutex);
    if (rec.strTarget.empty() || strOwner.empty()) return false;
    rec.dwId = m_dwNextId++;
    rec.strOwner = strOwner;
    rec.dwAmount = dwAmount;
    m_offers.push_back(rec);
    return true;
}

SWantedRec* CWantedManager::FindById(uint32_t dwId) {
    for (auto& o : m_offers) if (o.dwId == dwId) return &o;
    return nullptr;
}
const SWantedRec* CWantedManager::FindById(uint32_t dwId) const {
    for (auto& o : m_offers) if (o.dwId == dwId) return &o;
    return nullptr;
}

bool CWantedManager::IsValidId(uint32_t dwId) { // +0x58
    std::lock_guard<std::mutex> lock(m_mutex);
    return FindById(dwId) != nullptr;
}

uint32_t CWantedManager::GetAmountOf(uint32_t dwId) { // +0x88
    std::lock_guard<std::mutex> lock(m_mutex);
    const SWantedRec* p = FindById(dwId);
    return p ? p->dwAmount : 0;
}

void CWantedManager::CancelWanted(uint32_t dwId) { // +0x50
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto it = m_offers.begin(); it != m_offers.end(); ++it)
        if (it->dwId == dwId) { m_offers.erase(it); return; }
}

void CWantedManager::AcceptWanted(uint32_t dwUserId, uint32_t dwId) { // +0x100
    std::lock_guard<std::mutex> lock(m_mutex);
    m_accepted[dwUserId] = dwId; // "you can take only the last"
}

uint32_t CWantedManager::GetAcceptedOf(uint32_t dwUserId) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_accepted.find(dwUserId);
    return it == m_accepted.end() ? 0 : it->second;
}

void CWantedManager::SelectOwnOffer(uint32_t dwUserId, uint32_t dwId) { // +0xf0
    std::lock_guard<std::mutex> lock(m_mutex);
    m_selected[dwUserId] = dwId;
}

uint32_t CWantedManager::GetSelectedOwnOffer(uint32_t dwUserId) { // +0xe8
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_selected.find(dwUserId);
    return it == m_selected.end() ? 0 : it->second;
}

bool CWantedManager::SetOwnOfferAmount(uint32_t dwUserId, uint32_t dwTotal) { // +0x90
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_selected.find(dwUserId);
    if (it == m_selected.end()) return false;
    SWantedRec* p = FindById(it->second);
    if (!p) return false;
    p->dwAmount = dwTotal;
    return true;
}

void CWantedManager::RefreshOwnOffer(uint32_t dwUserId) { // +0xa0
    // ORIGINAL refresh/save slot - the in-memory port is already current;
    // kept for the flow documentation
    (void)dwUserId;
}

bool CWantedManager::IsUserWanted(uint32_t dwUserId) { // +0x30
    auto u = CUserManager::Instance().GetUser(dwUserId);
    if (!u) return false;
    const std::string& name = u->GetName();
    std::lock_guard<std::mutex> lock(m_mutex);
    for (const auto& o : m_offers) if (o.strTarget == name) return true;
    return false;
}

bool CWantedManager::WalkPoliceIndex(uint32_t dwIdx) { // +0x38
    std::lock_guard<std::mutex> lock(m_mutex);
    return dwIdx >= 1 && dwIdx <= m_offers.size();
}

bool CWantedManager::WalkOfferIndex(uint32_t dwIdx) { // +0x60
    std::lock_guard<std::mutex> lock(m_mutex);
    return dwIdx >= 1 && dwIdx <= m_offers.size();
}

std::string CWantedManager::GetTargetNameOf(uint32_t dwId) { // +0x80
    std::lock_guard<std::mutex> lock(m_mutex);
    const SWantedRec* p = FindById(dwId);
    return p ? p->strTarget : "";
}

std::string CWantedManager::GetOwnerNameOf(uint32_t dwId) { // +0xe0
    std::lock_guard<std::mutex> lock(m_mutex);
    const SWantedRec* p = FindById(dwId);
    return p ? p->strOwner : "";
}

uint32_t CWantedManager::GetBountyOf(uint32_t dwId) { // +0xc8
    return GetAmountOf(dwId);
}

void CWantedManager::PoliceAccept(uint32_t dwUserId, const std::string& strOwnerName) { // +0x110
    std::lock_guard<std::mutex> lock(m_mutex);
    m_police[dwUserId] = strOwnerName;
}

std::string CWantedManager::FormatOfferLine(uint32_t dwIdx) { // %iter_wanted
    std::lock_guard<std::mutex> lock(m_mutex);
    if (dwIdx < 1 || dwIdx > m_offers.size()) return "";
    const SWantedRec& o = m_offers[dwIdx - 1];
    // the "Offer Target Reward" board columns
    return std::to_string(o.dwId) + " " + o.strTarget + " " +
           std::to_string(o.dwAmount);
}

std::string CWantedManager::FormatPoliceLine(uint32_t dwIdx) { // %iter_police_wanted
    std::lock_guard<std::mutex> lock(m_mutex);
    if (dwIdx < 1 || dwIdx > m_offers.size()) return "";
    const SWantedRec& o = m_offers[dwIdx - 1];
    // the "Board Wanted-Target Guild Level PK-points" columns; guild/
    // level/pk resolve from the ONLINE target (offline -> 0/None)
    auto u = CUserManager::Instance().GetUserByName(o.strTarget);
    uint32_t dwSyn = u ? CGuildManager::Instance().GetSynIdOfUser(u->GetId()) : 0;
    std::string strGuild = dwSyn ? std::to_string(dwSyn) : "None";
    return std::to_string(o.dwId) + " " + o.strTarget + " " + strGuild +
           " " + std::to_string(u ? u->GetLevel() : 0) +
           " " + std::to_string(u ? u->GetPkPoints() : 0);
}

void CWantedManager::ClearForTest() {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_offers.clear(); m_drafts.clear(); m_accepted.clear();
    m_selected.clear(); m_police.clear(); m_dwNextId = 1;
}
