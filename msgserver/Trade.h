#pragma once
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <cstdint>

class CUser;

// Player-to-player trade (exchange) v1.
// In the original 6159 the exchange window is driven by the NPC dialog/task
// system (no standalone CMsgTrade exists in the decompile); this core engine
// implements the same ruleset (offers, locks, double-confirm, atomic swap)
// and the dialog layer attaches to it when the task system ports.
class CTradeSession {
public:
    CTradeSession(uint32_t dwA, uint32_t dwB);

    struct Offer {
        std::set<uint32_t> items;
        uint32_t money{0};
        bool locked{false};
    };

    uint32_t Other(uint32_t dwMe) const { return m_dwUserA == dwMe ? m_dwUserB : m_dwUserA; }
    Offer& Side(uint32_t dwUserId) { return m_dwUserA == dwUserId ? m_offerA : m_offerB; }
    const Offer& Side(uint32_t dwUserId) const { return m_dwUserA == dwUserId ? m_offerA : m_offerB; }
    bool BothLocked() const { return m_offerA.locked && m_offerB.locked; }
    bool Has(uint32_t dwUserId) const { return dwUserId == m_dwUserA || dwUserId == m_dwUserB; }

private:
    uint32_t m_dwUserA;
    uint32_t m_dwUserB;
    Offer m_offerA;
    Offer m_offerB;
};

class CTradeManager {
public:
    static CTradeManager& Instance();

    // v1 command surface (chat-driven; dialog packets attach later)
    void Request(std::shared_ptr<CUser> pFrom, std::shared_ptr<CUser> pTo);
    bool AddItem(std::shared_ptr<CUser> pUser, uint32_t dwItemId);
    bool AddMoney(std::shared_ptr<CUser> pUser, uint32_t dwAmount);
    bool Lock(std::shared_ptr<CUser> pUser);          // marks a side finished
    bool Confirm(std::shared_ptr<CUser> pUser);        // second stage: executes the swap
    bool Cancel(std::shared_ptr<CUser> pUser);

    std::shared_ptr<CTradeSession> GetSession(uint32_t dwUserId);

private:
    std::shared_ptr<CTradeSession> Find(uint32_t dwUserId); // no lock, callers hold m_mutex
    void DropSession(CTradeSession* pSession);

    CTradeManager() = default;
    std::map<uint32_t, std::shared_ptr<CTradeSession>> m_sessions; // by both user ids
    std::mutex m_mutex;
};
