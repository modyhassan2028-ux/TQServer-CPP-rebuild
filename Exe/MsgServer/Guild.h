#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
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
    uint32_t GetWarScore() const { return m_dwWarScore; }
    void AddWarScore(uint32_t v) { m_dwWarScore += v; }
    void ResetWarScore() { m_dwWarScore = 0; }
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
    void OnWarKill(uint32_t dwKillerGuildId, uint32_t dwVictimGuildId);
    bool IsAtWar(uint32_t dwGuildId) const;

private:
    CGuildManager() = default;
    std::map<std::string, std::shared_ptr<CGuild>> m_byName;
    std::map<uint32_t, std::shared_ptr<CGuild>> m_byMember;
    std::mutex m_mutex;
    uint32_t m_dwNextId{ 900000 };
};
