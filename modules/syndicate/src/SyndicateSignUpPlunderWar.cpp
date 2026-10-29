// D78 — CSyndicateLogic::SignUpPlunderWarFromClient helpers.
// The two helpers below are complete ports of their RAW loops; the surrounding
// function (token, sign-up string, tails) is documented in the plan doc.
#include "SyndicateSignUpPlunderWar.h"
#include <cmath>

namespace syndicate {

STargetIdResult ComposeTargetId(void* mgr, uint32_t target, uint32_t myLeague,
                                uint32_t userLeague, uint32_t memberKey,
                                SSignUpPlunderSeams& s) {
    STargetIdResult r{0, false};
    if (target == 0) return r;                     // the RAW skips a zero target
    uint32_t id;
    if (myLeague == target) {                      // vt+0x3f0() == target
        uint32_t own = s.OwnLeagueId(mgr);         // 14174e3f0
        if (own == 0 || own == userLeague) return r;
        id = myLeague * 1000000 + own;             // iVar10 * 1000000 + uVar9
    } else {
        id = s.TargetLeagueId(mgr, target);        // 141766950
    }
    if (id == 0) return r;
    if (memberKey == id) return r;
    r.id = id;
    r.insert = true;
    return r;
}

bool SendRobOptPages(SRobOptSeams& s, void* vt, uint32_t user,
                     int64_t current, int64_t cap, uint32_t freePages,
                     const uint32_t* ids, size_t nIds) {
    if (freePages < 1) return false;               // the caller aborts on < 1
    double pagesD = std::ceil((double)(cap - current) / (double)freePages);
    int pages = (int)(int64_t)pagesD;              // (longlong)dVar1 & 0xffffffff
    void* msg = s.MsgNew();
    if (msg == nullptr) return false;
    if (!s.MsgCreate(msg, 1, pages)) {
        s.MsgDestroy(msg);
        return false;
    }
    for (size_t i = 0; i < nIds; ++i) {
        if (!s.MsgAppend(msg, (int)(ids[i] / 1000000))) {
            s.Log("CSyndicateLogic::SignUpPlunderWarFromClient msg over size");
            break;                                  // the RAW keeps going to send
        }
    }
    if (s.MsgCount(msg) != 0) {
        s.MsgSerialize(msg);
        s.SendToClient(vt, user, msg);
    }
    s.MsgDestroy(msg);
    return true;                                    // CONCAT71(...,1)
}


// ---------------------------------------------------------------------------
// D78 — the function, phases 1 to 5. Every early exit in the RAW repeats the
// same three-step cleanup (string dtor, delete the vector buffer, delete the
// proxy) and returns a zeroed low byte, so the failures here all share `fail`.
// ---------------------------------------------------------------------------
uint32_t SignUpPlunderWarFromClient(void* logic, uint32_t uUser, uint32_t nCount,
                                    const uint32_t* targets, char bSupport,
                                    uint32_t uParam6, SLogicSeams& s) {
    if (uUser == 0 || (int)nCount < 1 || nCount > 10) return 0;        // gates
    void* vt  = *(void**)((char*)logic + 8);      // param_1[1]
    void* mgr = *(void**)((char*)logic + 80);     // param_1[10]
    if (s.WarGateBlocks(vt)) return 0;            // vt+0x278 non-zero blocks
    if (s.core.WarStartState(mgr) != 0) return 0; // 14174ebd0
    uint32_t league = s.core.LeagueOfUser(vt, uUser);   // vt+0x4a8
    if (league == 0) return 0;
    void* synLeague = s.core.FindLeague(mgr, league);   // 1417630d0
    if (synLeague == nullptr) return 0;
    uint32_t key = s.core.MemberKey(vt, uUser);         // vt+0x568
    if (s.core.IsKeyPending(mgr, key)) return 0;        // 141766a70

    // --- phase 2: the target vector ------------------------------------
    uint32_t myLeague = s.core.MyLeague(vt);            // vt+0x3f0, read once
    uint32_t* ids = nullptr;
    size_t nIds = 0, capIds = 0;
    for (uint32_t i = 0; i < nCount; ++i) {
        STargetIdResult r = ComposeTargetId(mgr, targets[i], myLeague, league, key, s.core);
        if (!r.insert) continue;
        if (nIds == capIds) {
            size_t nc = capIds ? capIds * 2 : 4;
            uint32_t* ni = (uint32_t*)s.core.OpNew(nc * sizeof(uint32_t));
            if (ni == nullptr) break;
            for (size_t k = 0; k < nIds; ++k) ni[k] = ids[k];
            if (ids) s.core.OpDelete(ids);
            ids = ni; capIds = nc;
        }
        ids[nIds++] = r.id;
    }
    if (nIds == 0) { if (ids) s.core.OpDelete(ids); return 0; }   // empty -> abort

    // --- phase 3: the token --------------------------------------------
    void* token = s.core.TokenQuery(synLeague, 0x65);                 // 14174bac0
    if (token == nullptr) token = s.core.TokenReload(synLeague, 0x65); // 14174bbe0
    if (token == nullptr) { if (ids) s.core.OpDelete(ids); return 0; }
    uint32_t tokenId = s.core.TokenId(token);                         // 1417d4ed0
    void* row = s.core.TokenTableRow(mgr, tokenId);                    // 141764870
    if (row == nullptr) {
        s.core.LogDb("table:cq_token_type, can not find token_id[%lu] at %s, %d.");
        if (ids) s.core.OpDelete(ids);
        return 0;
    }

    // --- phase 4: the sign-up string ------------------------------------
    void* str = nullptr;                                   // std::string local
    if (!s.core.BuildSignUpString(logic, uUser, synLeague, token, row, &str)) {
        if (str) s.core.OpDelete(str);
        if (ids) s.core.OpDelete(ids);
        return 0;
    }

    // --- phase 5: the ceilings ------------------------------------------
    int64_t current = (int64_t)s.core.LeaguePopulation(synLeague);     // 1417440d0
    int64_t cap     = s.TargetCap(vt);                                  // (vt+0x10)->+0x58
    if (bSupport == 0) {
        if (current < cap) {
            uint32_t free = s.core.FreePages(mgr);                      // 14174e940
            if ((int32_t)free < 1) {
                if (str) s.core.OpDelete(str);
                if (ids) s.core.OpDelete(ids);
                return 0;
            }
            if (!SendRobOptPages(s.robOpt, vt, uUser, current, cap, free, ids, nIds)) {
                if (str) s.core.OpDelete(str);
                if (ids) s.core.OpDelete(ids);
                return 0;
            }
        }
    } else {
        if (uParam6 == 0) {                        // the RAW reports the token
            s.NotifyTokenFail(vt, uUser);
            if (str) s.core.OpDelete(str);
            if (ids) s.core.OpDelete(ids);
            return 0;
        }
        if (s.SpendablePage(vt, uUser) < uParam6) {   // vt+0x238
            if (str) s.core.OpDelete(str);
            if (ids) s.core.OpDelete(ids);
            return 0;
        }
        uint32_t free = s.core.FreePages(mgr);
        cap = cap - (int64_t)free * (int64_t)uParam6;   // free * param_6
        if (cap < 0) {
            if (str) s.core.OpDelete(str);
            if (ids) s.core.OpDelete(ids);
            return 0;
        }
        if (current < cap) {                        // still room -> not allowed
            s.NotifyTokenFail(vt, uUser);
            if (str) s.core.OpDelete(str);
            if (ids) s.core.OpDelete(ids);
            return 0;
        }
        if (!s.SpendMoney(vt, uUser, 0, uParam6)) {  // vt+0x140
            s.NotifyNoMoney(vt, uUser);
            if (str) s.core.OpDelete(str);
            if (ids) s.core.OpDelete(ids);
            return 0;
        }
        s.EmoneyBuyTail(vt, uUser);                  // MyLogSave + i18n + 0x90
    }

    // --- phase 6-7 seam ---------------------------------------------------
    s.FinishTails(logic, uUser, synLeague, token, tokenId, key, current, cap, nullptr);
    if (str) s.core.OpDelete(str);
    if (ids) s.core.OpDelete(ids);
    return 1;                                        // the RAW returns 1 here
}

} // namespace syndicate
