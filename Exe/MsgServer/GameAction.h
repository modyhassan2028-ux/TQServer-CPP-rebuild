#pragma once
#include "Dialog.h"
#include <memory>
#include <cstdint>

class CUser;

// ORIGINAL CGameAction (msgserver\mapgroupkernel\gameaction.cpp):
// walks the cq_action chain and processes each row by its `type`.
//   - the master entry is ProcessAction (FUN_140145f60): it resolves the
//     param column through the two substitution stages, dispatches each
//     type to its family handler and follows id_next / id_nextfail
//   - UI/dialog types 101..198 -> FUN_140142db0 (ProcessActionOS port)
//   - check/effect types -> FUN_14012a6e0 (ProcessActionUser port) and the
//     other family handlers merged into it (301/501/2001/2201 cases ...)
// Family functions not yet ported are dispatched with pass-through
// behavior (documented PORT-PENDING per family).
class CGameAction {
public:
    // ORIGINAL CGameAction::ProcessAction — FUN_140145f60, literal port:
    // depth guard (11), 33-step chain cap, per-type profiling, [PM] trace,
    // OS-user type gate, type-320 id_next rule. Returns true when the
    // chain ran to completion (or was cut short by design), false only
    // when dwActionId is 0 or the call stack overflows 11 levels.
    static bool ProcessAction(std::shared_ptr<CUser> pUser, uint32_t dwActionId);

    // legacy walker kept for older callers; delegates to ProcessAction
    static void ProcessActionChain(std::shared_ptr<CUser> pUser, uint32_t dwActionId);

    // ORIGINAL CGameAction::ProcessActionOS case bodies (FUN_140142db0):
    // returns true when the row executed successfully.
    static bool ProcessActionOS(std::shared_ptr<CUser> pUser, const CDialogEngine::Node* pNode);

    // ORIGINAL CGameAction::ProcessActionUser (FUN_14012a6e0): types
    // 1001..1121. Returns true on success (chain continues id_next),
    // false on failure (chain continues id_nextfail).
    static bool ProcessActionUser(std::shared_ptr<CUser> pUser, const CDialogEngine::Node* pNode);
    // ORIGINAL FUN_140127070: the 801..898 window (dropitem/dropmoney +
    // per-monster money piles). Anything but 801/802 in the window is
    // "wrong action type" -> FALSE.
    static bool ProcessActionFamily8xx(std::shared_ptr<CUser> pUser, const CDialogEngine::Node* pNode);
    // ORIGINAL FUN_1401199d0 (ProcessActionItemOnly): the 401..498 window.
    // 401 = register EVENT_LAYNPC continuation ([user+0xa34] + empty
    // buffer at +0xa38, FUN_140117b50), 402 = npc count condition
    // (all/furniture/name/type < N / == N), 403 = lay the npc at the
    // client-picked cell (pszAccept = ctx.strInput model), 498 = use-
    // item consume + STR_USE_ITEM. Others in the window: DBERR + FALSE.
    static bool ProcessActionItemOnly(std::shared_ptr<CUser> pUser, const CDialogEngine::Node* pNode);
    static bool ProcessItemQuench(std::shared_ptr<CUser> pUser, const CDialogEngine::Node* pNode,
                                   uint32_t dwItemId, uint32_t dwMatId); // ORIGINAL FUN_14011b910

    // ORIGINAL cq_action 1001 condition "field op value" evaluator
    static bool ProcessDataCondition(std::shared_ptr<CUser> pUser, const std::string& strParam);
    // ORIGINAL CGameAction::ProcessActionPkBonus (FUN_140141c80): dispatch
    // range [2201..2263) (main switch `iVar8 - 0x899 < 0x62`). Pk-bonus
    // bounty system (cq_pk_bonus / cq_pk_item): 2201 target/hunter bonus
    // conditions, 2202 assign a record to the hunter, 2203 cleanup, 2204
    // claim the bonus, 2205 DetainEquip target/hunter checks.
    static bool ProcessActionPkBonus(std::shared_ptr<CUser> pUser,
                                     const CDialogEngine::Node* pNode);

    // ---- param substitution stages (used by ProcessAction) ----
    // ORIGINAL FUN_1401184a0 (CGameAction::ReplaceParamStr): @name@ vars
    // resolved through IStringManager. This DB holds no '@' in any of the
    // 192,895 cq_action param rows, so the SafeCopy path covers it.
    static void ReplaceParamStr(char* szOut, const char* szSrc, size_t nOut);
    // ORIGINAL FUN_14011efb0: the %token% resolver (sysdata(...), taskdata
    // (...), %<width>user_lev% ...). Ported tokens are implemented with
    // their verified getters; the rest fall through literally exactly like
    // the original's unmatched-token path.
    static void ReplacePercentStr(std::shared_ptr<CUser> pUser, char* szOut,
                                  const char* szSrc, size_t nOut);
};
