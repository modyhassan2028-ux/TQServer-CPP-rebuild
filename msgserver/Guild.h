#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <set>
#include <mutex>

class CUser;

// Guild (syndicate) v1. Wire-fidelity packets for 6159 guild ops live behind
// COSSyndicateMgr + NPC dialogs in the decompile; this core model ports first,
// driven by chat commands, and the packet layer attaches to it later.
class CGuild {
public:
    CGuild(uint32_t dwId, const std::string& name, uint32_t dwLeaderId);

    uint32_t GetId() const { return m_dwId; }
    const std::string& GetName() const { return m_name; }
    uint32_t GetLeaderId() const { return m_dwLeaderId; }

    void SetAnnouncement(const std::string& text) { m_announcement = text; }
    const std::string& GetAnnouncement() const { return m_announcement; }

    bool AddMember(uint32_t dwUserId);
    bool RemoveMember(uint32_t dwUserId);
    bool IsMember(uint32_t dwUserId) const;

    // guild war (v1)
    uint32_t GetWeeklyWins() const { return m_dwWeeklyWins; }
    void AddWeeklyWin() { ++m_dwWeeklyWins; }
    void ResetWeeklyWins() { m_dwWeeklyWins = 0; }
    uint32_t GetWarScore() const { return m_dwWarScore; }
    void AddWarScore(uint32_t v) { m_dwWarScore += v; }
    void ResetWarScore() { m_dwWarScore = 0; }

    uint64_t GetFund() const { return m_dwFund; }
    void AddFund(uint64_t v) { m_dwFund += v; }
    // warehouse: leader-only withdrawal from the shared fund
    bool TakeFund(uint64_t v) {
        if (v > m_dwFund) return false;
        m_dwFund -= v;
        return true;
    }
    const std::vector<uint32_t>& GetMembers() const { return m_members; }

    // send a chat packet to every online member (id+name of sender passed in)
    class CMsgTalk* BuildChat(class CUser* pSender, const std::string& text);

private:
    uint32_t m_dwId;
    std::string m_name;
    uint32_t m_dwLeaderId;
    std::string m_announcement;
    std::vector<uint32_t> m_members;
    uint32_t m_dwWarScore{0};
    uint64_t m_dwFund{0};
    uint32_t m_dwWeeklyWins{0};

public:
    // ---- syndicate record facade for cq_action 3501/3510/218/219 ----
    // ORIGINAL FUN_140140380 operates on the syn manager's record-8 API:
    // per-member byte rank (vcall+0x160 get / +0x168 set), star_tower
    // (+0x150/+0x158), duty rank (+0x118/+0x120, 100 = leader), and the
    // clan treasury money (64-bit: +0x198 get, +0x190 add, +0x1a0 set).
    struct SMemberSyn {
        uint8_t rank{0};      // 3501 "rank" (0..4)
        uint8_t starTower{0}; // 3501 "star_tower"
        int32_t duty{0};      // 3510 "rank" (100 = leader)
    };
    SMemberSyn* GetSynRec(uint32_t dwUserId) {
        auto it = m_synRec.find(dwUserId);
        return it == m_synRec.end() ? nullptr : &it->second;
    }
    SMemberSyn& GetSynRecForLoad(uint32_t dwUserId) { return m_synRec[dwUserId]; }
    int64_t GetTreasury() const { return m_qwTreasury; } // cq_syndicate.money
    void SetTreasury(int64_t v) { m_qwTreasury = v; }
    void AddTreasury(int64_t v) { m_qwTreasury += v; }
    // family-battle domain state (mgr vcall+0x1c0 hold / +0x1b0 challenge;
    // ORIGINAL per-syn queries against the record-8 API, see 3523/3524)
    uint32_t GetHoldDomain() const { return m_dwHoldDomain; }
    void SetHoldDomain(uint32_t v) { m_dwHoldDomain = v; }
    uint32_t GetChallengeDomain() const { return m_dwChallengeDomain; }
    void SetChallengeDomain(uint32_t v) { m_dwChallengeDomain = v; }

    // ---- 701-732 family (FUN_140128290 ProcessActionSyn) facade ----
    // guild-to-guild relations by syn id: the 711-714 chains
    // ("hostile"/"reconciled"/"allied"/"unallied" dialog texts)
    bool IsHostileTo(uint32_t synId) const { return m_hostile.count(synId) > 0; }
    bool IsAlliedTo(uint32_t synId) const { return m_allies.count(synId) > 0; }
    void SetHostile(uint32_t synId, bool on) { if (on) m_hostile.insert(synId); else m_hostile.erase(synId); }
    void SetAlly(uint32_t synId, bool on) { if (on) m_allies.insert(synId); else m_allies.erase(synId); }
    // 715 (mgr +0x118): deputy appointed by leader, by member name
    uint32_t GetDeputyId() const { return m_dwDeputyId; }
    void SetDeputyId(uint32_t id) { m_dwDeputyId = id; }
    // 717 "member_title =" (mgr +0x110): syn-wide member title byte
    uint8_t GetMemberTitle() const { return m_ucMemberTitle; }
    bool SetMemberTitle(uint8_t t) { m_ucMemberTitle = t; return true; }

private:
    std::set<uint32_t> m_hostile, m_allies;
    uint32_t m_dwDeputyId{0};
    uint8_t m_ucMemberTitle{0};
    std::map<uint32_t, SMemberSyn> m_synRec;
    int64_t m_qwTreasury{0};
    uint32_t m_dwHoldDomain{0};
    uint32_t m_dwChallengeDomain{0};
};

class CGuildManager {
public:
    static CGuildManager& Instance();

    // command entry points (v1: driven by chat commands)
    bool Create(const std::string& name, std::shared_ptr<CUser> pLeader);
    bool Join(const std::string& name, std::shared_ptr<CUser> pUser);
    bool Quit(std::shared_ptr<CUser> pUser);
    bool Disband(std::shared_ptr<CUser> pLeader);

    std::shared_ptr<CGuild> FindByName(const std::string& name);
    std::shared_ptr<CGuild> GetByMember(uint32_t dwUserId);

    void Broadcast(std::shared_ptr<CGuild> pGuild, const void* pBuf, uint16_t usLen);

    // guild war: leader declares, defender auto-accepts, 30 min, kill scoring
    bool DeclareWar(std::shared_ptr<CUser> pLeader, const std::string& strTargetGuild);
    // weekly guild war champion: crowns the top war winner of the week
    void WeeklyChampionPayout();
    std::string WeeklyStandingsText(); // /gwtop
    void OnWarKill(uint32_t dwKillerGuildId, uint32_t dwVictimGuildId);
    bool IsAtWar(uint32_t dwGuildId) const;
    // settles expired wars, announces the winner and pays the reward
    void TickWars();

    // ---- syndicate record facade for cq_action 3501/3510/218/219 ----
    // ORIGINAL: the singleton syn manager (0x1406d8df0) exposes record 8;
    // every cq_action 35xx call resolves the member through it.
    uint32_t GetSynIdOfUser(uint32_t dwUserId);        // vcall+0x128
    CGuild* GetSynOf(uint32_t dwUserId);               // resolve + member rec
    CGuild::SMemberSyn* GetSynRecOf(uint32_t dwUserId);
    int64_t GetTreasuryOf(uint32_t dwUserId);          // vcall+0x198
    // family-battle domain queries BY SYN ID (rec8 vcall+0x1c0 / +0x1b0)
    uint32_t GetHoldDomainOfSyn(uint32_t dwSynId);
    uint32_t GetChallengeDomainOfSyn(uint32_t dwSynId);
    void SetChallengeDomainOfSyn(uint32_t dwSynId, uint32_t dwDomain); // +0x1b8
    CGuild* GetSynById(uint32_t dwSynId);
    std::shared_ptr<CGuild> GetSynByIdShared(uint32_t dwSynId);
    // treasury add BY SYN ID (rec8 vcall+0x190)
    bool AddTreasuryOfSyn(uint32_t dwSynId, int64_t n);
    // clan announcement (rec8 vcall+0x148): set + broadcast to members
    void AnnounceOfSyn(uint32_t dwSynId, const std::string& text);
    bool AddTreasuryOf(uint32_t dwUserId, int64_t n);  // vcall+0x190
    bool SetTreasuryOf(uint32_t dwUserId, int64_t n);  // vcall+0x1a0

    // ---- 701-732 family (FUN_140128290 ProcessActionSyn) facade ----
    // Mappings documented per-case against the decompiled switch; the
    // manager is the ORIGINAL syn-manager singleton (FUN_140087ed0).
    bool IsValidSyn(uint32_t synId);                        // +0x248
    int64_t GetSynTreasuryById(uint32_t synId);             // +0x268 (717 "money <")
    void AddSynTreasuryById(uint32_t synId, int64_t n);     // +0x270 (717 "money +=")
    bool SetSynMemberTitle(uint32_t synId, uint8_t t);      // +0x110 (717 "member_title =")
    bool SynHasDomain(uint32_t synId);                       // +0x2e8 (717 "has_domain ==")
    bool NextSynIter(uint32_t& rSlot);                      // +0x260 (720: writes slot)
    uint32_t GetSynIdByName(const std::string& name);       // +0x250 (721)
    bool NextSynMemberIter(uint32_t dwSynId, uint32_t& rSlot); // +0xb8 (722)
    bool CreateSynForAction(std::shared_ptr<CUser> pUser,
                            const std::string& name, int64_t n0); // +0x228 (701)
    bool JoinLeague(std::shared_ptr<CUser> pUser);           // +0x230 (702, +0x510 gate)
    bool DonateToSyn(std::shared_ptr<CUser> pUser,
                     uint32_t synId, int64_t n);             // +0x138/+0x198 (703/707)
    bool SetAnnouncementOf(std::shared_ptr<CUser> pUser,
                           const std::string& text);          // +0xe8 (704)
    bool InviteMemberByName(std::shared_ptr<CUser> pUser,
                            const std::string& name);         // +0xd8 (706)
    bool SetHostileByName(std::shared_ptr<CUser> pUser,
                          const std::string& name);           // +0x1a8 (711)
    bool SetReconcileByName(std::shared_ptr<CUser> pUser,
                            const std::string& name);         // +0x1b8 (712)
    bool AcceptAlly(std::shared_ptr<CUser> pUser);           // +0x1a0 (713, ally list)
    void AddAllyRequest(uint32_t dwSynId, uint32_t dwTargetSynId); // ally list source
    bool SetUnallyByName(std::shared_ptr<CUser> pUser,
                         const std::string& name);            // +0x1b0 (714)
    bool AppointDeputyByName(std::shared_ptr<CUser> pUser,
                             const std::string& name);        // +0x118 (715)
    // %iter_member_name resolver support: the member iterator state
    // (which syn is being walked; the slot index lives on the user)
    void SetIterMemberSyn(uint32_t synId) { m_dwIterMemberSyn = synId; }
    std::string GetIterMemberName(uint32_t dwIdx);

    // cq_action 218 (0x14013ca63): create clan from the typed dialog name.
    // Duplicate name / already member -> false (chain shows "taken" text).
    bool CreateForAction(uint32_t dwUserId, const std::string& name);
    // cq_action 219 (0x14013cb21): disband, leader-only, del_flag=1.
    bool DisbandForAction(uint32_t dwUserId);

    // cq_syndicate (del_flag=0) + cq_synattr load; returns guild count
    uint32_t LoadFromDB(class CMySQLClient* pDB);
    // registers an existing member in the manager-side index (used by
    // LoadFromDB and membership flows); creates the default member rec
    void AttachMember(uint32_t dwUserId, uint32_t dwSynId);

private:
    CGuildManager() = default;
    std::map<uint32_t, uint32_t> m_allyRequests; // target syn id -> requester syn id
    uint32_t m_dwIterMemberSyn{0};               // 722 walk state
    std::map<std::string, std::shared_ptr<CGuild>> m_byName;
    std::map<uint32_t, std::shared_ptr<CGuild>> m_byId;
    std::map<uint32_t, std::shared_ptr<CGuild>> m_byMember;
    std::mutex m_mutex;
    uint32_t m_dwNextId{ 900000 };
};
