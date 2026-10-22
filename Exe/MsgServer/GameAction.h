#pragma once
#include "Dialog.h"
#include <memory>
#include <cstdint>

class CUser;

// ORIGINAL CGameAction (msgserver\mapgroupkernel\gameaction.cpp):
// walks the cq_action chain and processes each row by its `type`.
//   - UI/dialog types 101..132 -> CGameAction::ProcessActionOS (FUN_140142880)
//   - check/effect types 1001..1121 -> CGameAction::ProcessActionUser (FUN_14012a6e0)
// This port covers the OS dialog set (101/102/103/104/105) and the
// condition set currently evaluated; remaining types keep walking
// id_next exactly like an action whose semantics are still pending.
class CGameAction {
public:
    // run a chain from dwActionId following id_next (success) /
    // id_nextfail (failure) like the original ProcessAction loop
    static void ProcessActionChain(std::shared_ptr<CUser> pUser, uint32_t dwActionId);

    // ORIGINAL CGameAction::ProcessActionOS case bodies (FUN_140142880):
    // returns true when the row executed successfully.
    static bool ProcessActionOS(std::shared_ptr<CUser> pUser, const CDialogEngine::Node* pNode);

    // ORIGINAL CGameAction::ProcessActionUser (FUN_14012a6e0): types
    // 1001..1121. Returns true on success (chain continues id_next),
    // false on failure (chain continues id_nextfail).
    static bool ProcessActionUser(std::shared_ptr<CUser> pUser, const CDialogEngine::Node* pNode);

    // ORIGINAL cq_action 1001 condition "field op value" evaluator
    static bool ProcessDataCondition(std::shared_ptr<CUser> pUser, const std::string& strParam);
};
