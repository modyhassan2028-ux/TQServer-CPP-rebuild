#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <mutex>

// ============================================================================
// CWantedManager - the bounty-office singleton. ORIGINAL: FUN_1401182a0
// (MsgServer.exe), the manager behind CGameAction::ProcessActionWanted
// (FUN_14011a7e0, the 3001..3012 family). Every method below documents
// the vtable slot it models; semantics cross-checked against the live
// cq_action chains (17020..17112 bounty office, 17613..17663 police
// board, 200000+ teleport wanted-gate).
//
// Live dialog texts that pin the flow:
//   17010  "My enemy is:"            -> 3002 set target name (draft)
//   17021  "How much do you offer?"  -> 3003 set amount (draft)
//   17032  "I have taken your offer" -> 3004 publish (charge, min 100k)
//   17041  "Offer Target Reward"     -> 3001 list walk (%iter_wanted)
//   17063  "you can take only the last" -> 3005 hunter accepts (fee 1000)
//   17081  "I have canceled this offer for double the reward" -> 3006 cancel
//   17101  "increase? No less than 10,000 each time" -> 3007 select + 3008 add
//   17611  "Board Wanted-Target Guild Level PK-points" -> 3010 police walk
//                                     (%iter_police_wanted), 3011 accept
//   200001 "You are the wanted criminal" -> 3012 is-wanted gate
// ============================================================================
struct SWantedRec {
    uint32_t dwId = 0;
    std::string strTarget; // the enemy
    std::string strOwner;  // the offerer
    uint32_t dwAmount = 0;
};

class CWantedManager {
public:
    static CWantedManager& Instance();

    // +0x120 (3002): set the draft target by name. False: empty/own name.
    bool SetTargetBy(uint32_t dwUserId, const std::string& strName);
    // +0x130 (3003): set the draft amount (draft or not). True always.
    bool SetAmountBy(uint32_t dwUserId, uint32_t dwAmount);
    // +0x128 (3004/3011): the draft amount of the user (0 when none)
    uint32_t GetAmountBy(uint32_t dwUserId);
    // +0x118 (3004): copy the user's draft into rec. False: no target.
    bool GetDraftBy(uint32_t dwUserId, SWantedRec& rec);
    // +0x70 (3004): publish the draft as an active offer
    bool PublishDraft(SWantedRec& rec, const std::string& strOwner, uint32_t dwAmount);

    // +0x58: active offer id?
    bool IsValidId(uint32_t dwId);
    // +0x88: bounty amount of an offer
    uint32_t GetAmountOf(uint32_t dwId);
    // +0x50 (3006): remove the offer
    void CancelWanted(uint32_t dwId);
    // +0x100 (3005): hunter accepts the offer - only the LAST accepted
    // counts (per-user state)
    void AcceptWanted(uint32_t dwUserId, uint32_t dwId);
    uint32_t GetAcceptedOf(uint32_t dwUserId);
    // +0xf0 (3007): owner selects which of their offers to add reward to
    void SelectOwnOffer(uint32_t dwUserId, uint32_t dwId);
    // +0xe8 (3008): the owner's selected offer id (0 = none)
    uint32_t GetSelectedOwnOffer(uint32_t dwUserId);
    // +0x90 (3008): set the new total on the selected offer
    bool SetOwnOfferAmount(uint32_t dwUserId, uint32_t dwTotal);
    // +0xa0 (3008): refresh/save after the change (side-effect slot)
    void RefreshOwnOffer(uint32_t dwUserId);

    // +0x30 (3012): is this user's NAME the target of an active offer?
    // ("You are the wanted criminal" teleport gate)
    bool IsUserWanted(uint32_t dwUserId);

    // +0x38 (3010)/(+0x60 for 3001): list walks. The slot at role+0xa68 is
    // incremented FIRST by the handler, so these take the 1-based index.
    bool WalkPoliceIndex(uint32_t dwIdx);
    bool WalkOfferIndex(uint32_t dwIdx);

    // +0x80 (3005): target name of an offer (the enemy)
    std::string GetTargetNameOf(uint32_t dwId);
    // +0xe0 (3011): owner (offerer) name of an offer
    std::string GetOwnerNameOf(uint32_t dwId);
    // +0xc8 (3011): the bounty shown in the police-accept message
    uint32_t GetBountyOf(uint32_t dwId);
    // +0x110 (3011): police hunter accepts the offer (per-user state)
    void PoliceAccept(uint32_t dwUserId, const std::string& strOwnerName);

    // %iter_wanted (3001 walk): "<id> <target> <amount>" of the offer at
    // the 1-based index - the "Offer Target Reward" board line
    std::string FormatOfferLine(uint32_t dwIdx);
    // %iter_police_wanted (3010 walk): the "Board Wanted-Target Guild
    // Level PK-points" line; guild/level/pk resolve from the ONLINE target
    std::string FormatPoliceLine(uint32_t dwIdx);

    void ClearForTest();

private:
    CWantedManager() = default;
    SWantedRec* FindById(uint32_t dwId);
    const SWantedRec* FindById(uint32_t dwId) const;

    uint32_t m_dwNextId = 1;
    std::vector<SWantedRec> m_offers;          // active offers
    std::map<uint32_t, SWantedRec> m_drafts;   // per-user drafts
    std::map<uint32_t, uint32_t> m_accepted;   // hunter -> offer id
    std::map<uint32_t, uint32_t> m_selected;   // owner -> offer id
    std::map<uint32_t, std::string> m_police;  // police hunter -> offerer
    mutable std::mutex m_mutex;
};
