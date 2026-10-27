// D88: FUN_14179ba80 — walks the member tree
// (mgr+0x390) with the MSVC lower_bound pattern
// (nil flag at +0x61, candidate updated on left
// turns), then inserts the member's sub-key
// (FUN_141785dc0) into the found node's sub-tree
// at +0x20 (FUN_14178cd30). Null member -> 0.
#pragma once
#include <cstdint>
namespace syndicate {
// seams
extern uint64_t (*g_fnD88MemberKey)(void*);        // 1417867d0 (vt+0x10(2))
extern uint64_t (*g_fnD88MemberSub)(void*);        // 141785dc0
extern uint64_t (*g_fnD88TreeInsert)(void*, uint32_t*); // 14178cd30
extern void (*g_fnD88Invalid)();                   // _invalid_parameter_noinfo
uint64_t MemberSubkeyAdd88(void* pMgr, void* pMember); // 14179ba80
}
