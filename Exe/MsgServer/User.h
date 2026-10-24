#pragma once
#include "Item.h"

class CMonster;
#include "PlayerMagic.h"
#include <cstdio>
#include <string>
#include <cstring>
#include <cctype>
#include <cstdint>
#include <utility>
#include <functional>
#include <vector>
#include <map>

class CGameMap;
class CNetClient;

class CUser {
public:
    CUser(uint32_t dwId);
    ~CUser();

    uint32_t GetId() const { return m_dwId; }

    // ORIGINAL FUN_140167b70: server-side "OS user" gate (used by TaskDetail
    // module CreateTask/DeleteTask and map guards): id above 0xee69a15e AND
    // the OS-user flag (CUser+0x12fc) set.
    bool IsOsUser() const { return m_dwId > 0xee69a15e && m_bOsUser; }
    // vcall+0x220 (FUN_14011c9e0 8011: dead users get STR_CROSS_SERVER_DENY_DEAD)
    bool IsAlive() const { return m_bAlive; }
    void SetAlive(bool b) { m_bAlive = b; }
    // CUser+0x12fc flag setter (FUN_140167b70's second gate)
    void SetOsUserFlag(bool b) { m_bOsUser = b; }
    const std::string& GetName() const { return m_name; }
    void SetName(const std::string& name) { m_name = name; }
    // owning cq_account id (0 = dev/flat mode, unsaved to MySQL)
    void SetAccountId(uint32_t id) { m_dwAccountId = id; }
    uint32_t GetAccountId() const { return m_dwAccountId; }

    uint16_t GetX() const { return m_usX; }
    uint16_t GetY() const { return m_usY; }
    // ORIGINAL CUser ABI: x @+0x40, y @+0x48, direction @+0x50
    uint8_t GetDir() const { return m_byDir; }
    void SetDir(uint8_t byDir) { m_byDir = byDir; }
    void SetPos(uint16_t usX, uint16_t usY) { m_usX = usX; m_usY = usY; }

    uint32_t GetMapId() const { return m_dwMapId; }
    void SetMapId(uint32_t dwMapId) { m_dwMapId = dwMapId; }

    // kernel slot accessors (session-9 damage chain)
    void SetKernelSlots(uint32_t mn, uint32_t mx, uint32_t atk, uint32_t def) {
        m_dwHitMin = mn; m_dwHitMax = mx; m_dwKernelAttack = atk; m_dwKernelDefense = def; }
    uint32_t GetHitMin() const { return m_dwHitMin; }
    uint32_t GetHitMax() const { return m_dwHitMax; }
    uint32_t GetKernelAttack() const { return m_dwKernelAttack; }
    uint32_t GetKernelDefense() const { return m_dwKernelDefense; }
    void SetBless(uint32_t v) { m_dwBless = v; }
    uint32_t GetBless() const { return m_dwBless; }
    void SetDeduct(uint32_t v) { m_dwDeduct = v; }
    uint32_t GetDeduct() const { return m_dwDeduct; }
    uint32_t GetRank() const { return m_dwRank; }
    void SetRank(uint32_t r) { m_dwRank = r; }
    bool IsDie() const { return m_dwLife == 0; } // ORIGINAL vtable+0x290
    bool IsBoss() const { return false; } // ORIGINAL vtable+0x288 (monsters only)
    bool m_bAttackable{true}; // ORIGINAL vtable+0x220 probe target
    bool m_bMonster{false};  // ORIGINAL vtable+0x240 (monster kernels)
    bool IsMonster() const { return m_bMonster; }
    void SetMonster(bool b) { m_bMonster = b; }
    bool IsAttackable() const { return m_bAttackable; }
    void SetAttackable(bool b) { m_bAttackable = b; }
    uint32_t GetLife() const { return m_dwLife; }
    uint32_t GetMaxLife() const { return m_dwMaxLife; }
    void SetMaxLife(uint32_t v) { m_dwMaxLife = v; }

    // cq_itemaddition: snapshot the un-bonused stats (call once after character
    // restore), then recalc whenever equipment changes
    void SnapshotBaseStats() { m_dwBaseMaxLife = m_dwMaxLife; m_dwBaseBP = m_dwBattlePower; }
    void RecalcEquipmentBonuses();
    void SetLife(uint32_t dwLife) { m_dwLife = dwLife; }
    void AddLife(int32_t nDelta) {
        if (nDelta < 0 && (uint32_t)(-nDelta) > m_dwLife) m_dwLife = 0;
        else m_dwLife = (uint32_t)(m_dwLife + nDelta);
    }

    uint32_t GetBattlePower() const { return m_dwBattlePower; }
    // cq_itemaddition attack granted by currently equipped gear
    uint32_t GetEquipmentAttack() const { return m_dwBattlePower - m_dwBaseBP; }
    void SetBattlePower(uint32_t dwBP) { m_dwBattlePower = dwBP; }

    // GM & Economy attributes
    uint64_t GetMoney() const { return m_dwMoney; }
    uint64_t GetBank() const { return m_dwBank; }
    void SetBank(uint64_t v) { m_dwBank = v; }
    void AddBank(int64_t delta) { if (delta >= 0) m_dwBank += (uint64_t)delta; else m_dwBank = (m_dwBank > (uint64_t)(-delta)) ? m_dwBank - (uint64_t)(-delta) : 0; }
    uint32_t GetPkPoints() const { return m_dwPkPoints; }
    void AddPkPoints(uint32_t v) { m_dwPkPoints += v; }
    void SetPkPoints(uint32_t v) { m_dwPkPoints = v; }
    bool IsRedName() const { return m_dwPkPoints >= 30; }
    // active hunt task (v1 quest system)
    bool HasActiveTask() const { return m_task.dwNeeded > 0; }
    struct Task {
        uint32_t dwNpcId{0};        // task giver to return to
        uint32_t dwMonsterType{0}; // target monster type id
        uint32_t dwNeeded{0};
        uint32_t dwDone{0};
        uint32_t dwRewardMoney{0};
        uint32_t dwRewardCp{0};
    } m_task;

    // last NPC the player talked to; digit replies route to its dialog menu
    void SetTalkingNpc(uint32_t id) { m_dwTalkingNpc = id; }
    uint32_t GetTalkingNpc() const { return m_dwTalkingNpc; }

    // ORIGINAL dialog reply state: the server registers every option
    // (102/103) shown to the player with the action id it jumps to
    // (FUN_14039d300, list capped at 20), so the client's MsgTalk answer
    // text maps back to the next action node.
    // ORIGINAL FUN_14039d300: register the option (list capped at 20,
    // 0x30-byte slots) and return its 0-based INDEX, or -1 (0xFFFFFFFF)
    // when the action id is 0 (dead-end option, client shows plain text)
    // or the list is full ("menu task size overflow" DBERROR log).
    // The index goes into the MsgDialog header byte at offset 10.
    uint32_t PushDialogOption(const std::string& text, uint32_t dwActionId) {
        if (dwActionId == 0) return 0xFFFFFFFF;
        if (m_dialogOptions.size() >= 20) return 0xFFFFFFFF;
        m_dialogOptions.push_back({text, dwActionId});
        return (uint32_t)(m_dialogOptions.size() - 1);
    }
    void ClearDialogOptions() { m_dialogOptions.clear(); m_dwInputAction = 0; }
    const std::vector<std::pair<std::string, uint32_t>>& GetDialogOptions() const { return m_dialogOptions; }
    // ORIGINAL 6159 input flow: a 103 (input) dialog registers the
    // action the typed answer continues at; the client reply text
    // arrives as MsgTalk(1004) to the NPC, the engine stores it as the
    // dialog ctx strInput and jumps there (FUN_14013f4c0-family input
    // branch). Modeled as one pending input action at a time.
    void SetPendingInput(uint32_t dwAction) { m_dwInputAction = dwAction; }
    uint32_t GetPendingInput() const { return m_dwInputAction; }
    // cq_action dialog tree position (0 = no tree open)
    void SetDialogNode(uint32_t id) { m_dwDialogNode = id; }
    uint32_t GetDialogNode() const { return m_dwDialogNode; }
    void SetMoney(uint64_t money) { m_dwMoney = money; }
    void AddMoney(int64_t amount) { m_dwMoney = (amount < 0 && (uint64_t)(-amount) > m_dwMoney) ? 0 : m_dwMoney + amount; }

    uint32_t GetConquerPoints() const { return m_dwEmoney; }
    void SetConquerPoints(uint32_t cps) { m_dwEmoney = cps; }
    void AddConquerPoints(int32_t amount) { m_dwEmoney = (amount < 0 && (uint32_t)(-amount) > m_dwEmoney) ? 0 : m_dwEmoney + amount; }
    // ORIGINAL ProcessActionPkBonus records (cq_pk_item rows): CUser+0x13b8
    // (FUN_140168a60) = records where this user is the TARGET; CUser+0x13e8
    // (FUN_140168a70) = pending claims where this user is the HUNTER.
    // Populated by the DetainEquip module flow (module port pending).
    struct SPkBonusRecord {
        uint32_t dwItem = 0, dwTarget = 0, dwHunter = 0;
        char szTargetName[16] = {0}, szHunterName[16] = {0};
        int32_t nBonus = 0, nBType = 0;
    };
    std::vector<SPkBonusRecord> m_vecPkTarget;  // +0x13b8
    std::vector<SPkBonusRecord> m_vecPkHunter;  // +0x13e8
    // the ProcessActionPkBonus context object (param_1): +0x20 target name,
    // +0x30 hunter name, +0x40 bonus, +0x44 remaining count
    struct SPkBonusCtx {
        char szTargetName[16] = {0}, szHunterName[16] = {0};
        uint32_t dwBonus = 0; int32_t nRemain = 0;
    } m_stPkBonusCtx;

    uint8_t GetLevel() const { return m_ucLevel; }
    void SetLevel(uint8_t level) { m_ucLevel = level; }

    // marriage v1: spouse name persisted in cq_user.spouse_name
    const std::string& GetSpouseName() const { return m_strSpouse; }
    void SetSpouseName(const std::string& n) { m_strSpouse = n; }

    // ORIGINAL user.cpp action vars: int64[8] at CUser+0x2f0 (set by action
    // 1061, read by 1060) and std::string[8] at CUser+0x1b0 (set by 1063,
    // compared by 1062). FUN_140164520/4d0 + FUN_1401645e0/570.
    bool SetActionVar(int nIdx, int64_t nValue) {
        if (nIdx < 0 || nIdx > 7) return false; // ORIGINAL: log + no-op
        m_anActionVars[nIdx] = nValue; return true;
    }
    int64_t GetActionVar(int nIdx) const {
        if (nIdx < 0 || nIdx > 7) return 0;
        return m_anActionVars[nIdx];
    }
    bool SetActionVarStr(int nIdx, const std::string& str) {
        if (nIdx < 0 || nIdx > 7) return false;
        m_astrActionVars[nIdx] = str; return true;
    }
    const char* GetActionVarStr(int nIdx) const {
        if (nIdx < 0 || nIdx > 7) return "";
        return m_astrActionVars[nIdx].c_str();
    }

    // ORIGINAL 1080/1081 timestamp vars (FUN_1403863f0 get / FUN_1403864e0
    // set): the original keeps two std::map<(id_a,id_b),data-module*> trees on
    // CUser (keys a<3 at +0xb0 via FUN_140385a30/5b80, keys a>=3 at +0x40 via
    // FUN_140384640); each stored value is read/written through the module's
    // GetProcess(5) -> vtable+0x40 Get / vtable+0xb8 Set as a single uint32.
    // FUN_140167b70 gates both: GetId > 0xee69a15e && CUser+0x12fc != 0 makes
    // GetTimeStamp return 0 and SetTimeStamp a no-op ("system" user).
    // Not found -> 0 (original returns 0 after the failed tree walk).
    uint32_t GetTimeStamp(uint32_t dwA, uint32_t dwB) const {
        if (m_dwId > 0xee69a15eU && m_nFlag12fc != 0) return 0; // FUN_140167b70
        auto it = m_mapTimeStamps.find({dwA, dwB});
        return it == m_mapTimeStamps.end() ? 0 : it->second;
    }
    void SetTimeStamp(uint32_t dwA, uint32_t dwB, uint32_t dwVal) {
        if (m_dwId > 0xee69a15eU && m_nFlag12fc != 0) return; // FUN_140167b70
        m_mapTimeStamps[{dwA, dwB}] = dwVal;
    }

    // ORIGINAL CUser vtable+0x48: the mate ID (cq_user.mateid). Lazily
    // loaded from cq_user on first use; 0 = unmarried.
    uint32_t GetSpouseID();
    void SetSpouseID(uint32_t dwId);

    // daily hunt quest: kills counted today, claim flag
    uint32_t GetQuestKills() const { return m_dwQuestKills; }
    void AddQuestKill() { ++m_dwQuestKills; }
    void SetQuestKills(uint32_t v) { m_dwQuestKills = v; }
    bool IsQuestClaimed() const { return m_bQuestClaimed; }
    void SetQuestClaimed(bool b) { m_bQuestClaimed = b; }
    std::string m_strQuestDay; // YYYY-MM-DD the counter belongs to

    // riding: mounted players jump for free (classic horse perk)
    bool IsRiding() const { return m_bRiding; }
    void SetRiding(bool b) { m_bRiding = b; }
    bool HasHorse() const {
        for (const auto& it : m_items)
            if (it.dwType == 750 && it.dwPosition != 255) return true; // 750 = horse
        return false;
    }

    // durability: equipped weapon wears on hits; broken steel hits at half power
    void WearWeapon() {
        for (auto& it : m_items)
            if (it.usSort == 1 && it.dwPosition == 1) { // equipped weapon slot
                if (it.usDurability > 0) --it.usDurability;
                if (it.usDurability == 200)
                    SendSysMsg("Your weapon is badly worn - /repair it soon!");
                else if (it.usDurability == 0)
                    SendSysMsg("Your weapon is broken! Damage halved until /repair.");
                break;
            }
    }
    bool WeaponIsBroken() const {
        for (const auto& it : m_items)
            if (it.usSort == 1 && it.dwPosition == 1) return it.usDurability < 200;
        return false;
    }
    // repair cost: 2 money per point of wear (min 10 if not pristine)
    uint32_t RepairCost() const {
        uint32_t cost = 0;
        for (const auto& it : m_items)
            if (it.usSort <= 2 && it.dwPosition != 255 && 1000 > it.usDurability)
                cost += (1000 - it.usDurability) * 2;
        return cost;
    }
    void DoRepair() {
        for (auto& it : m_items)
            if (it.usSort <= 2 && it.dwPosition != 255) it.usDurability = 1000;
    }

    // profession counters (ranks raise payouts): fish + mining
    uint32_t GetFishCaught() const { return m_dwFishCaught; }
    void AddFishCaught(uint32_t v) { m_dwFishCaught += v; }
    void SetFishCaught(uint32_t v) { m_dwFishCaught = v; }
    uint32_t GetOreMined() const { return m_dwOreMined; }
    void AddOreMined(uint32_t v) { m_dwOreMined += v; }
    void SetOreMined(uint32_t v) { m_dwOreMined = v; }
    // rank from a count: 0-24 Novice, 25-99 Adept, 100-299 Expert, 300+ Master
    static const char* ProfRank(uint32_t count) {
        if (count >= 300) return "Master";
        if (count >= 100) return "Expert";
        if (count >= 25) return "Adept";
        return "Novice";
    }
    static uint32_t ProfBonus(uint32_t count) { // payout multiplier in percent
        if (count >= 300) return 150;
        if (count >= 100) return 125;
        if (count >= 25) return 110;
        return 100;
    }

    // mining: channel end time (0 = idle)
    uint32_t GetMineUntil() const { return m_dwMineUntil; }
    void SetMineUntil(uint32_t t) { m_dwMineUntil = t; }

    // fishing: channel end time (0 = idle)
    uint32_t GetFishUntil() const { return m_dwFishUntil; }
    void SetFishUntil(uint32_t t) { m_dwFishUntil = t; }

    // stamina: 0..100 bar, -15 per jump, regen handled by the world tick
    uint16_t GetStamina() const { return m_usStamina; }
    void SetStamina(uint16_t v) { m_usStamina = v > 100 ? 100 : v; }
    bool SpendStamina(uint16_t v) {
        if (m_usStamina < v) return false;
        m_usStamina -= v;
        return true;
    }
    void RegenStamina(uint16_t v) { SetStamina((uint16_t)(m_usStamina + v)); }

    // daily login reward: returns true when a reward was granted (a new UTC day)
    bool GrantDailyReward();
    const std::string& GetLastRewardDay() const { return m_strLastRewardDay; }
    // daily bank interest: pays once per calendar day at login
    uint64_t GrantDailyBankInterest();
    void SetLastRewardDay(const std::string& d) { m_strLastRewardDay = d; }

    // rebirth: at level 130 /reborn restarts at 15 with permanent growth
    uint32_t GetRebornCount() const { return m_dwRebornCount; }
    // classic reborn: at level 130, reset to 15 keeping power + 30 alloc points
    // returns false with a reason string on failure
    std::string DoReborn();
    void SetRebornCount(uint32_t v) { m_dwRebornCount = v; }
    // ORIGINAL condition fields (CGameAction::ProcessActionUser case 1001)
    void SetProfession(uint16_t v) { m_wProfession = v; }
    uint16_t GetProfession() const { return m_wProfession; }
    void SetMana(uint32_t v) { m_dwMana = v; }
    uint32_t GetMana() const { return m_dwMana; }
    // metempsychosis = reborn count (cq_user column)
    uint32_t GetMetempsychosis() const { return m_dwRebornCount; }
    // ---- ORIGINAL weapon-skill records (cq_weapon_skill; type 1021 path,
    // case 0xf "ACTION_USER_WEAPONSKILL") ----
    struct WeaponSkillRec {
        uint32_t dwId{0};     // cq_weapon_skill.id
        uint32_t dwType{0};
        uint8_t  ucLevel{0};  // record +0x18 (FUN_14039d7e0)
        uint32_t dwExp{0};    // record +0x14 (FUN_14039d860)
    };
    bool LoadWeaponSkillsFromDB(CMySQLClient* pDB);
    WeaponSkillRec* FindWeaponSkill(uint32_t dwType);
    uint32_t GetWeaponSkillMaxLevel(uint32_t dwType); // mapgroup vtable+0x98
    // FUN_140170ae0 CUser::AwardWeaponSkill(type, level): max-lev gate, then
    // set-or-create the cq_weapon_skill record, client sync.
    bool AwardWeaponSkill(uint32_t dwType, uint32_t dwLevel);
    // FUN_140183e30 mode 1: add exp along the cq_weapon_skill_up curve.
    void AddWeaponSkillExp(uint32_t dwType, uint32_t dwAmount);
    // case 0xf addlevtime: amount only guards >=1 (the value itself is
    // unused by the original); below max it nets one level-up.
    bool AwardWeaponSkillTime(uint32_t dwType, int nAmount);

    // ---- ORIGINAL magic record API (CPlayerMagic, ported) ----
    // FUN_14048b5f0: first record with GetAttrib(rec,2) == dwType
    CPlayerMagic* FindMagic(uint32_t dwType);
    // ORIGINAL: cq_magic rows owned by this character, loaded on login
    bool LoadMagicsFromDB(CMySQLClient* pDB);
    // FUN_1404939c0 LearnMagic(type, level, byTask): (type, level) must
    // exist in cq_magictype; already-known magic returns false (a known
    // but unlearned record just clears its unlearn flag, like original)
    bool LearnMagic(uint32_t dwType, uint32_t dwLevel);
    // FUN_14048fd10 UpLevelByTask: needs the cq_magictype (type, level+1)
    // row to exist, else logs "Can't Find Magic" and fails
    bool UpLevelMagic(uint32_t dwType);
    // FUN_140493f70 DeleteMagic(user, type, mode=0): old_level = max(
    // old_level, level), unlearn = 1 (record kept, like original)
    bool DeleteMagic(uint32_t dwType);
    // FUN_1404918c0 CPlayerMagic::AddMagicExp: award skill exp, auto level-up
    // while the stage chain allows (need_exp>0, player level >= next stage's
    // need_level); at chain end exp resets to 0; record saved (attr 4).
    bool AddMagicExp(uint32_t dwType, int nAmount);
    // FUN_140491be0 CPlayerMagic::AwardMgcTime: convert levtime ms to exp via
    // CWeaponSkillUp::CalcTimeToExp (FUN_1402f1340) then AddMagicExp.
    bool AwardMgcTime(uint32_t dwType, int nMs);
    uint32_t GetMagicCount() const { return (uint32_t)m_oMagics.size(); }
    // ---- ORIGINAL magic EFFECT-mask API (CPlayerMagic, ported) ----
    // attribs on the record: 7 = current effect, 8 = available mask,
    // 9 = effect_monopoly mask, 10 = effect_exorbitant mask (cq_magic cols).
    // FUN_14048c770 AllowLaunchEffect(type, effect): the available mask
    // must hold the effect bit; then current = effect + record save.
    bool AllowLaunchEffect(uint32_t dwMagicType, uint8_t byEffect);
    // FUN_14048c7e0 AttachEffectType(type, effect, bMonopoly, bExorbitant):
    // refuses an already-available effect; sets current+available (+the
    // monopoly/exorbitant masks when asked), saves, and pushes a
    // MsgMagicInfo (mode 4) with available + exorbitant to the client.
    bool AttachEffectType(uint32_t dwMagicType, uint8_t byEffect,
                          bool bMonopoly, bool bExorbitant);
    // FUN_14048c4c0 DropMagicEffect(type, effect): clears the effect bits
    // from available/exorbitant (and current when it matched); a monopoly
    // bit pays out the converted effect item (type 3000694), else the
    // monopoly mask bit is also cleared and the monopoly item is paid;
    // pushes MsgMagicInfo (mode 6). Magic-count gate: 40 records max.
    bool DropMagicEffect(uint32_t dwMagicType, uint8_t byEffect);
    // FUN_1404851b0 SendMagicEffectAfterProcess: builds the FULL 1105 from
    // the record (attr 2 type, 3 level, 7 current-effect flag) + caller
    // damage/data fields and broadcasts it map-wide (original map
    // vtable+0x348 with flag 1 = include self). Caller-param mapping
    // (verified against FUN_140386e00's 13 params): data5 / d3 / d2 /
    // damage / target id.
    bool SendMagicEffectAfterProcess(uint32_t dwMagicType, uint32_t dwData5,
                                     uint32_t dwD3, uint32_t dwD2,
                                     uint32_t dwDamage, uint32_t dwTargetId);
    // ORIGINAL FUN_140486fb0 target handle: the original loops ONE proxy
    // vector where each proxy resolves to a user or a monster (vtable
    // 0x220 = IsAlive gate, 0x240 = IsBoss, 0x288/0x290 = dead/ghost
    // gates, GetPoint(0x1001) = the map record, GetPoint(0x1002) = the
    // CMonster for -2 sweeps).
    struct SMagicTarget {
        CUser* pUser{nullptr};
        CMonster* pMonster{nullptr};
    };

    // FUN_140486fb0 CPlayerMagic::SendMagicEffectAfterProcessGroupByPos:
    // batches ONE 1105 for the whole target group (CreateGroup header +
    // AppendGroup per target; on the 0x400 gate refusal the packet is
    // broadcast first, a fresh header is created and the CURRENT target
    // is re-appended). Per entry: id = target id, damage = the damage
    // code (the -2 code becomes damage 0 + data5 = 2), d2 = scene diff
    // (0 in our single-scene port), dwNext/data4 = 0 (leftover stack
    // slots in the original call), data6 = y, data7 = x. The final
    // packet is broadcast map-wide (include self, original map proxy
    // vtable+0x348 flag 1). vecUnused5/vecUnused6 = the original
    // param_5/param_6 u32 arrays, loaded by the original but only ever
    // reaching stack slots past the append signature (kept for the
    // literal call shape). Loop 2 (reposition): alive targets with
    // damage != -1: code -2 -> CMonster::JumpPos(x, y) (FUN_140388a40);
    // else JumpPos via the map-bounds path (FUN_14015f9d0; failure logs
    // the 0x1f00 "user%u map%u(%d, %d) at %s, %d" playermagic.cpp line).
    // The original then dispatches the kernel scene op (target id,
    // 0x6e, 0) — FUN_1401181a0 singleton, kernel-side packet outside
    // our slice, ported as a logged dispatch — and for boss monsters
    // (0x240) sends CMsgAction(id, x, y, dir = 0, p6 = 3, data = 407,
    // action = monster dir) to the creature's map.
    bool SendMagicEffectAfterProcessGroupByPos(
        uint32_t dwMagicType, uint32_t dwPair0, uint32_t dwPair1,
        const std::vector<SMagicTarget>& vecTargets,
        const std::vector<int>& vecDamage,
        const std::vector<uint32_t>& vecUnused5,
        const std::vector<uint32_t>& vecUnused6,
        const std::vector<std::pair<uint32_t, uint32_t>>& vecXY);

    // ORIGINAL creature vtable slot 0x378 (JumpPos) for user targets of
    // the sweep: position move; the user-side teleport packet of the
    // original slot is outside the ported slice (TODO with FUN_140499830).
    void JumpPos(uint16_t usX, uint16_t usY);

    // ---- ORIGINAL launch-loop per-target gates (FUN_1404a1f70 call
    // chain, ported literal) ----

    // FUN_1404864f0 CPlayerMagic::IsTargetProtected: nonzero in the
    // original = skip the hit entirely. Record null or target null ->
    // gate open (0). Sort 50 (0x32) -> gate open. Zone check (map
    // vtable+0x3d8, sorts 6..7 pass the in-map flag) refused -> skip.
    // PK-warning cascade (target 0x278 == 0 = user OR PK map OR
    // weapon_hit == 0 OR weapon_subtype 500/610 OR sort 65 OR type
    // 11030) with map pk-count > 999 -> STR_PK tip + skip. The ~30-sort
    // switch runs the monster dyna-type immunity bit (FUN_14016cfc0).
    // Final gate: FUN_140186200 friendly-fire check.
    bool IsTargetProtected(uint32_t dwMagicType, const SMagicTarget& t);

    // FUN_1404831f0 CPlayerMagic::SweepTarget: the -2 sweep only fires
    // for (record crime attr 0x68 != 0 OR magic type == 0x2d46) AND the
    // target IsAlive, and then FUN_1403e9290 must roll true: target
    // status 0xa0 + kernel resistance roll (10000 sides, resistance
    // from kernel slot 0xb0(id, 0xa0); the port stores the value with
    // the status).
    bool SweepTarget(uint32_t dwMagicType, const SMagicTarget& t, bool bTypeEq2d46);

    // FUN_140483270: pre-hit attack-position registry hook (singleton
    // FUN_140087ed0 slot 0x2d8: target id, attacker id, life, x, y) behind
    // a double FUN_140167b70 trace-toggle read. The registry subsystem is
    // outside the ported slice; the hook stays inert and logged.
    void RecordHitPos(const SMagicTarget& t);

    // FUN_140186200 model (friendly fire): the attacker himself is
    // always protected; team/guild/marriage cascade lands with those
    // systems.
    bool IsFriendlyTarget(const SMagicTarget& t) const;
    // attr-0 counter (original CUser+0x88) for newly created records
    uint32_t m_dwMagicCounter{0};
    // returns an error message, or "" on success
    std::string Reborn();

    // attribute points: +3 per level, /stat str|vit allocates
    // (agi/spi come with the port of the original dodge/mana systems)
    uint32_t GetStatPoints() const { return m_dwStatPoints; }
    void SetStatPoints(uint32_t v) { m_dwStatPoints = v; }
    uint32_t GetStrength() const { return m_dwStrength; }
    uint32_t GetVitality() const { return m_dwVitality; }
    void SetStrength(uint32_t v) { m_dwStrength = v; }
    void SetVitality(uint32_t v) { m_dwVitality = v; }
    // returns an error message, or "" on success
    std::string AllocStat(const std::string& stat, uint32_t count);

    // experience + level-ups (original v6159 curve, v1 approximation:
    // exp needed for next level = 30 * level^2 + 40 * level)
    uint64_t GetExperience() const { return m_dwExperience; }
    void SetExperience(uint64_t v) { m_dwExperience = v; }
    static uint64_t ExpForLevel(uint8_t ucLevel) { return 30ull * ucLevel * ucLevel + 40ull * ucLevel; }
    // grants xp; returns the number of levels gained (stats grow per level)
    uint32_t AddExperience(uint64_t dwXp);

    uint8_t GetReborn() const { return m_ucReborn; }
    void SetReborn(uint8_t reborn) { m_ucReborn = reborn; }

    uint8_t GetVipLevel() const { return m_ucVip; }
    void SetVipLevel(uint8_t vip) { m_ucVip = vip; }

    // ---- inventory (v1) ----
    void AddItem(const ItemInfo& item) { m_items.push_back(item); }
    // ORIGINAL FUN_140385cf0 CUser::ItemCount(type, data): total stack amount
    // of the (type,data) container key. type 1 = silvers, 2 = CPs (pseudo
    // items in the original item tree).
    uint32_t CountItems(uint32_t dwType, uint32_t dwData) const {
        if (dwType == 1) { (void)dwData; return (uint32_t)m_dwMoney; }
        if (dwType == 2) { (void)dwData; return m_dwEmoney; }
        uint32_t n = 0;
        for (auto& it : m_items)
            if (it.dwType == dwType && it.dwData == dwData) n += it.dwAmount;
        return n;
    }
    // ORIGINAL FUN_140385de0 CUser::SetItemCount(type, data, count): 1074
    // '+=' stacks onto the key, '=' replaces it; 0 removes the stack.
    bool SetItemCount(uint32_t dwType, uint32_t dwData, uint32_t dwAmount, bool bAdd) {
        if (dwType == 1) { (void)dwData;
            if (bAdd) m_dwMoney += dwAmount;
            else m_dwMoney = dwAmount;
            return true; }
        if (dwType == 2) { (void)dwData;
            m_dwEmoney = bAdd ? m_dwEmoney + dwAmount : dwAmount;
            return true; }
        for (auto& it : m_items)
            if (it.dwType == dwType && it.dwData == dwData) {
                it.dwAmount = bAdd ? it.dwAmount + dwAmount : dwAmount;
                if (it.dwAmount == 0) return true; // stack kept at 0 like an empty stack
                return true;
            }
        if (dwAmount == 0) return true;
        ItemInfo info; info.dwType = dwType; info.dwData = dwData; info.dwAmount = dwAmount;
        info.dwPosition = 0; info.strName = "stc";
        m_items.push_back(info);
        return true;
    }
    // eats one charge of a usable stack (by type id); false if not carried
    bool ConsumeByType(uint32_t dwType);
    // refine the equipped weapon; returns an error message or ""
    std::string UpgradeEquipped();
    ItemInfo* FindItem(uint32_t dwItemId) {
        for (auto& it : m_items) if (it.dwId == dwItemId) return &it;
        return nullptr;
    }
    void RemoveItem(uint32_t dwItemId) {
        for (size_t i = 0; i < m_items.size(); ++i)
            if (m_items[i].dwId == dwItemId) { m_items.erase(m_items.begin() + i); return; }
    }
    std::vector<ItemInfo>& GetInventory() { return m_items; }
    // ORIGINAL FUN_14032b4b0: positions 21..29 (warehouse pages) fold to 1..9
    // (pos%10), then position 1..19 indexes the user's position array.
    ItemInfo* FindItemById(uint32_t dwId) {
        for (auto& it : m_items) if (it.dwId == dwId) return &it;
        return nullptr;
    }
    ItemInfo* FindItemByPosition(int nPos) {
        if (nPos >= 21 && nPos <= 29) nPos %= 10;
        if (nPos < 1 || nPos > 19) return nullptr; // ORIGINAL: logs + 0
        for (auto& it : m_items) if ((int)it.dwPosition == nPos) return &it;
        for (auto& it : m_warehouse) if ((int)it.dwPosition == nPos) return &it;
        return nullptr;
    }
    // warehouse: a second, bank-like bag for long-term storage
    std::vector<ItemInfo>& GetWarehouse() { return m_warehouse; }
    void WarehouseStore(ItemInfo& item) { m_warehouse.push_back(item); }
    ItemInfo* WarehouseFind(uint32_t dwItemId) {
        for (auto& it : m_warehouse) if (it.dwId == dwItemId) return &it;
        return nullptr;
    }
    void WarehouseRemove(uint32_t dwItemId) {
        for (size_t i = 0; i < m_warehouse.size(); ++i)
            if (m_warehouse[i].dwId == dwItemId) { m_warehouse.erase(m_warehouse.begin() + i); return; }
    }
    uint32_t NextItemSeq() { return ++m_dwItemSeq; }

    void BindNet(CNetClient* pNet) { m_pNet = pNet; }
    CNetClient* NetClient() const { return m_pNet; }

    bool IsGodMode() const { return m_bGodMode; }
    void SetGodMode(bool god) { m_bGodMode = god; }

    bool IsInvisible() const { return m_bInvisible; }
    void SetInvisible(bool inv) { m_bInvisible = inv; }

    void Teleport(uint32_t dwMapId, uint16_t usX, uint16_t usY);
    // ORIGINAL CUser::FlyMap @ 0x1401c55b0 (user.cpp): move the player to a
    // map/cell. Return codes (consumed by cq_action 1003, gameaction.cpp
    // case 2): 0 = moved inside this map-doc (action succeeds, chain walks
    // id_next), 1 = transfer to another map-doc (action succeeds and HALTS
    // the chain), 2 = mount gate refused (action fails), -1 = error (action
    // fails; the original then re-flies the player to the recorded pos).
    // TODO(port): map-flag bit 0x40 gates, transform clear (0x26/0x194),
    // leave-map check FUN_1401a4030, os-enter gate FUN_14016ced0, mount
    // gate (STR_EQUIP_HORSE) and the cross-doc transfer FUN_1401995a0.
    int32_t FlyMap(uint32_t dwMapId, uint32_t usX, uint32_t usY, bool bForce);
    void SendMsg(const void* pBuf, uint16_t usSize);
    // test seam: when set, outgoing packets are captured here instead of
    // going to the socket (system tests assert on real packet bytes)
    void SetPacketSink(std::function<void(const void*, uint16_t)> sink) { m_packetSink = std::move(sink); }
    void SendSysMsg(const std::string& message);
    // ORIGINAL cq_action 1010 (gameaction.cpp case 9): talk message on the
    // channel given by the action's data column (0 -> 2000) via the CUser
    // vtable+0x150 sender ("SYSTEM" -> player, MsgTalk type 1004).
    bool SendTalkMsg(const std::string& strText, uint32_t dwChannel);

private:
    uint32_t m_dwId{0};
    bool     m_bOsUser{false}; // ORIGINAL CUser+0x12fc (set when OS users exist)
    bool     m_bAlive{true};   // ORIGINAL user vcall+0x220 IsAlive gate
    // ORIGINAL status probe vtable+0x2d8 (FUN_1404864f0 checks 0x6e);
    // the port stores the status resistance value with the status.
    void AddStatus(uint32_t dwStatus, uint32_t dwValue) { m_mapStatus[dwStatus] = dwValue; }
    bool HasStatus(uint32_t dwStatus) const { return m_mapStatus.count(dwStatus) != 0; }
    bool GetStatusValue(uint32_t dwStatus, uint32_t& dwValue) const {
        auto it = m_mapStatus.find(dwStatus);
        if (it == m_mapStatus.end()) return false;
        dwValue = it->second; return true;
    }
    std::map<uint32_t, uint32_t> m_mapStatus;
                               // (ProcessActionCrossServer 8011 denies dead users)
    std::string m_name;
    uint32_t m_dwMapId{1002}; // Twin City default
    uint16_t m_usX{400};
    uint16_t m_usY{400};
    uint8_t m_byDir{0};
    uint32_t m_dwLife{1000};
    uint32_t m_dwMaxLife{1000};
    uint32_t m_dwBaseMaxLife{1000};
    uint64_t m_dwExperience{0};
    uint32_t m_dwStatPoints{0};
    uint32_t m_dwStrength{0};
    uint32_t m_dwVitality{0};
    uint32_t m_dwRebornCount{0};
    uint16_t m_usStamina{100};
    std::string m_strLastRewardDay;
    std::string m_strSpouse;
    uint32_t m_dwMateId{0};     // ORIGINAL cq_user.mateid
    int m_nFlag12fc{0};          // ORIGINAL CUser+0x12fc gate used by FUN_140167b70
    std::map<std::pair<uint32_t, uint32_t>, uint32_t> m_mapTimeStamps; // ORIGINAL: two maps a<3/+0xb0, a>=3/+0x40
    int64_t     m_anActionVars[8]{};   // ORIGINAL CUser+0x2f0
    std::string m_astrActionVars[8];  // ORIGINAL CUser+0x1b0
    bool     m_bMateLoaded{false};
    uint32_t m_dwFishUntil{0};
    uint32_t m_dwMineUntil{0};
    bool m_bRiding{false};
    uint32_t m_dwFishCaught{0};
    uint32_t m_dwOreMined{0};
    uint32_t m_dwQuestKills{0};
    bool m_bQuestClaimed{false};
    uint32_t m_dwBaseBP{100};
    uint32_t m_dwBattlePower{100};

    // Economy & Special State
    uint64_t m_dwMoney{0};
    uint64_t m_dwBank{0};
    uint32_t m_dwPkPoints{0};
    uint32_t m_dwTalkingNpc{0};
    uint32_t m_dwDialogNode{0};
    std::vector<std::pair<std::string, uint32_t>> m_dialogOptions;
    uint32_t m_dwInputAction{0}; // pending 103 input continuation
    uint16_t m_wProfession{0};   // cq_user.profession (short @ +0xef4)
    uint32_t m_dwMana{0};
public:
    // ORIGINAL lay-npc state block: [user+0xa34] next task, [user+0xa38]
    // the accept buffer string (set "" by FUN_140117b50), [user+0xa30]
    // the created npc id (403), [user+0x14c] use-item state (498)
    uint32_t m_dwLayNpcTask{0};
    std::string m_strLayNpcBuf;
    uint32_t m_dwCreatedNpcId{0};
    uint32_t m_dwUseItemPos{0};
    // ---- ORIGINAL ACTION_USER_ATTR (cq_action type 1001) fields ----
    // In-memory mirrors of the cq_user attribute set read/written by the
    // original case-0 field chain (gameaction.cpp 242240-244770). Setters
    // print the original client-sync notices; persistence rides on the
    // record layer (CPlayerMagic-style Save paths) where applicable.
    uint32_t m_dwLookface{0};      // cq_user.lookface (look/face/sex derive)
    uint32_t m_dwMentor{0};        // mentor system id
    int32_t  m_nTransform{0};     // user+0x798 transform state
    uint32_t m_dwEmoneyTrial{0};  // trial CP wallet (sync type 0x34)
    uint32_t m_dwEmoneyMono{0};   // cq_user.emoney_mono
    uint16_t m_wForce{0};         // attrib 15, ushort user+0xED8
    uint16_t m_wSpeed{0};         // cq_user.Speed, attrib 16, +0xEDC
    uint16_t m_wHealth{0};        // cq_user.health, attrib 14, +0xEDE
    uint16_t m_wSoul{0};          // cq_user.soul, attrib 13, +0xEE0
    uint32_t m_dwRank{0};         // rank manager value (kernel slot 0x38)
    // ---- kernel slots (session-9 damage chain, FUN_1403ec0a0 ABI) ----
    uint32_t m_dwHitMin{0};        // 0x88: physical hit min
    uint32_t m_dwHitMax{0};        // 0x90: physical hit max
    uint32_t m_dwKernelAttack{0};  // 0xa0: kernel attack
    uint32_t m_dwKernelDefense{0};// 0xb8: kernel defense (atk-def component)
    uint32_t m_dwBless{0};         // 0x200: bless bonus (step 13)
    uint32_t m_dwDeduct{0};        // 0x210: deduct (step 13 subtraction)
    uint32_t m_dwIterator{0};     // user+0xA78 (iter_var_data)
    uint32_t m_dwCrime{0};        // crime state
    int32_t  m_nVirtue{0};        // cq_user.virtue, attrib 23
    uint32_t m_dwGamecard{0};     // FUN_140330ef0
    uint32_t m_dwGamecard2{0};    // FUN_140330f80
    uint32_t m_dwXp{0};           // xp bar
    int32_t  m_nEp{0};            // energy points
    uint16_t m_wFirstProf{0};     // cq_user.first_prof
    uint16_t m_wOldProf{0};       // cq_user.old_prof
    uint32_t m_dwMount{0};        // FUN_140160ba0
    uint32_t m_dwRidingPoint{0}; // cq_user.ridepet_point
    uint32_t m_dwCultivation{0};  // cq_user.cultivation
    uint32_t m_dwPkProtocol{0};  // cq_user.pkprotocol
    uint32_t m_dwStrengthValue{0};// cq_user.strength_value
    uint32_t m_dwCultureValue{0}; // cq_user.culture_value
    uint32_t m_dwClientVer{0};    // FUN_140165160
    uint32_t m_dwPeerage{0};      // nobility peerage
    uint8_t  m_ucBusiness{0};     // cq_user.business
    uint32_t m_dwVipValue{0};     // cq_user.vip_value
    uint16_t m_wBattleLev{0};    // FUN_14018eb30

    uint32_t GetLookface() const { return m_dwLookface; }
    // ORIGINAL user+0xf24: 32-bit action flag array (case 0x16 = type 1028);
    // FUN_14039a210 chk / FUN_14039a150 add / FUN_14039a1b0 clr (bit <= 31
    // else LOGERR + no-op; add/clr go through the FUN_1403724f0(user+0xe78)
    // sync wrapper).
    uint32_t m_dwActionFlags{0};
    bool IsActionFlag(int n) const { return n >= 0 && n <= 31 && ((m_dwActionFlags >> n) & 1) != 0; }
    void SetActionFlag(int n, bool b) {
        if (n < 0 || n > 31) return; // ORIGINAL: LOGERR + no-op
        if (b) m_dwActionFlags |= (1u << n); else m_dwActionFlags &= ~(1u << n);
    }

    void SetLookface(uint32_t v) { m_dwLookface = v; printf("[USER] %u lookface -> %u (client sync)\n", m_dwId, v); }
    int32_t  GetTransform() const { return m_nTransform; }
    uint32_t m_dwTransformLookface{0}; // ORIGINAL: transform display look
    uint32_t m_dwTransformMonsterType{0}; // ORIGINAL: cq_monstertype id of the transform
    uint32_t m_dwTransformSecs{0}; // ORIGINAL: transform duration (timer system pending)
    // ORIGINAL action iteration vars: %iter_var_dataN tokens resolve to these
    // (populated by the iteration actions - var engine family C)
    int64_t m_arIterVarData[65]{};
    // ORIGINAL quench (refinery) context: the two item ids the quench UI
    // passes to CGameAction::ProcessActionItemQuench (FUN_14011b910)
    uint32_t m_dwQuenchItemId{0};
    uint32_t m_dwQuenchMaterialId{0};
    void SetIterVarData(uint32_t n, int64_t v) { if (n && n < 65) m_arIterVarData[n] = v; }
    int64_t GetIterVarData(uint32_t n) const { return (n && n < 65) ? m_arIterVarData[n] : 0; }
    uint32_t m_dwHomeMapId{0}; // %user_home_id (house system feeds this)
    uint32_t m_dwGenId{0}; // dynamic-user generator id (cq_action 2008 gen_id)
    uint32_t GetGenId() const { return m_dwGenId; }
    void SetGenId(uint32_t g) { m_dwGenId = g; }
    // ORIGINAL dialog/npc context resolved as %id/%data/%datastr/%name/
    // %npc_life/%npc_ownerid/%npc_x/%npc_y (the central resolver reads the
    // message dialog fields - the npc the player is interacting with)
    struct DialogCtx {
        uint32_t dwId{0}, dwData{0}, dwNpcLife{0}, dwNpcOwnerId{0};
        uint16_t wX{0}, wY{0};
        std::string strDatastr, strName;
        // ORIGINAL walker arg7 (FUN_140145f60 stack 0x1168): the string the
        // player typed into an input dialog, re-parsed by the "accept"
        // operand of cq_action type 201 data ops. Wired once client dialog
        // replies land here (MsgDialog::Process stub).
        std::string strInput;
    } m_stDialogCtx;
    // ORIGINAL role+0xa68 (param_4[0x14d]): the family-70x dialog syn
    // slot - 720 guild-list iterator state, 721 name-resolved syn id,
    // 722 member-iterator index, 707 donate target. One field, four uses.
    uint32_t m_dwIterSynState{0};
    uint32_t GetIterSynState() const { return m_dwIterSynState; }
    void SetIterSynState(uint32_t v) { m_dwIterSynState = v; }
    // ORIGINAL family 801/802 (FUN_140127070) queries its "0x1002" object -
    // the monster record the action runs from (monster AI chains). The
    // query failing fails the whole handler; modeled as the source
    // monster id resolved through CMonsterManager.
    uint32_t m_dwSourceMonsterId{0};
    uint32_t GetHomeMapId() const { return m_dwHomeMapId; }
    void SetHomeMapId(uint32_t m) { m_dwHomeMapId = m; }
    // ORIGINAL: action vars resolve centrally before the case runs
    uint32_t m_dwSynId{0};       // ORIGINAL %syn_id (syndicate/guild id)
    uint32_t GetSynId() const { return m_dwSynId; }
    void  SetSynId(uint32_t v) { m_dwSynId = v; }

    void ResolveActionVars(std::string& s) const {
        ResolveIterVars(s);
        // %user_map_id -> current map; %user_home_id -> house map
        auto sub = [&](const char* szTok, const std::string& v) {
            size_t p = 0;
            while ((p = s.find(szTok, p)) != std::string::npos)
                s.replace(p, strlen(szTok), v);
        };
        // ORIGINAL resolver token order (longest first: %datastr before %data)
        sub("%user_map_id", std::to_string(m_dwMapId));
        sub("%user_home_id", std::to_string(m_dwHomeMapId));
        sub("%user_map_x", std::to_string(m_usX));
        sub("%user_map_y", std::to_string(m_usY));
        sub("%user_lev", std::to_string(m_ucLevel));
        sub("%user_id", std::to_string(m_dwId));
        sub("%user_name", m_name);
        sub("%id", std::to_string(m_stDialogCtx.dwId));
        sub("%datastr", m_stDialogCtx.strDatastr);
        sub("%data", std::to_string(m_stDialogCtx.dwData));
        sub("%name", m_stDialogCtx.strName);
        sub("%npc_life", std::to_string(m_stDialogCtx.dwNpcLife));
        sub("%npc_ownerid", std::to_string(m_stDialogCtx.dwNpcOwnerId));
        sub("%npc_x", std::to_string(m_stDialogCtx.wX));
        sub("%npc_y", std::to_string(m_stDialogCtx.wY));
        sub("%syn_id", std::to_string(m_dwSynId));
    }
    void ResolveIterVars(std::string& s) const {
        const char* szTok = "%iter_var_data";
        size_t p = 0;
        while ((p = s.find(szTok, p)) != std::string::npos) {
            size_t q = p + strlen(szTok);
            uint32_t idx = 0; size_t r = q;
            while (r < s.size() && isdigit((unsigned char)s[r])) r++;
            idx = (uint32_t)strtoul(s.substr(q, r - q).c_str(), nullptr, 10);
            s.replace(p, r - p, std::to_string(GetIterVarData(idx)));
            p = q;
        }
    }
    // cq_action 1005 (ORIGINAL attr 0x1a): the hair/style attribute.
    // style digits: cur = (cur/100)*100 + style; < 100 -> + 300.
    // color digits: cur = (color - (cur%1000)/100) * 100 + cur.
    uint32_t m_dwHairStyle{321};  // ORIGINAL default look cluster
    uint32_t GetHairStyle() const { return m_dwHairStyle; }
    void SetHairStyle(uint32_t v) { m_dwHairStyle = v; printf("[USER] %u hair -> %u\n", m_dwId, v); }

    void SetTransform(int32_t v) { m_nTransform = v; printf("[USER] %u transform -> %d\n", m_dwId, v); }
    uint32_t GetIteratorVar() const { return m_dwIterator; }
    void SetIteratorVar(uint32_t v) { m_dwIterator = v; }
    int32_t  GetVirtue() const { return m_nVirtue; }
    uint32_t GetEmoneyMono() const { return m_dwEmoneyMono; }
    uint32_t GetRidingPoint() const { return m_dwRidingPoint; }
    uint32_t GetCultivation() const { return m_dwCultivation; }
    uint32_t GetStrengthValue() const { return m_dwStrengthValue; }
    uint32_t GetCultureValue() const { return m_dwCultureValue; }
    uint32_t GetBankMoney() const { return m_dwBank; }
    uint16_t GetForce() const { return m_wForce; }
    uint16_t GetUserSpeed() const { return m_wSpeed; }
    uint16_t GetUserHealth() const { return m_wHealth; }
    uint16_t GetUserSoul() const { return m_wSoul; }
    uint32_t GetVipValue() const { return m_dwVipValue; }
    uint32_t GetXp() const { return m_dwXp; }
    void SetXp(uint32_t v) { m_dwXp = v; printf("[USER] %u xp -> %u (client sync)\n", m_dwId, v); }

private:
    std::map<uint32_t, CPlayerMagic> m_oMagics; // type -> cq_magic record
    std::map<uint32_t, WeaponSkillRec> m_oWeaponSkills; // cq_weapon_skill rows
    bool m_bWSkillsLoaded{false};
    std::function<void(const void*, uint16_t)> m_packetSink;
    uint32_t m_dwAccountId{0};
    uint32_t m_dwEmoney{0};
    uint8_t m_ucLevel{1};
    uint8_t m_ucReborn{0};
    uint8_t m_ucVip{0};
    bool m_bGodMode{false};
    bool m_bInvisible{false};
    CNetClient* m_pNet{nullptr};
    std::vector<ItemInfo> m_items;
    std::vector<ItemInfo> m_warehouse;
    uint32_t m_dwItemSeq{0};
};