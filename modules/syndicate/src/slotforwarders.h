// slotforwarders.h — the thin forwarders at 0x1417ac700/0x1417ac710/0x1417ac720/0x1417ac730 and the
// three-field release at 0x1417ac5e0. None of them contains a string, so the original file is not
// recoverable from the image; they are grouped by address here rather than guessed into a module.
#pragma once
#include <cstdint>

namespace tq {

// Each of the first three is three instructions — `mov 0x8(%rcx),%rcx / mov (%rcx),%rax /
// jmp *0xNNN(%rax)` — so it is a transparent tail call into the sub-object's table and passes every
// register argument along untouched. The return value is the callee's, whatever its type.
uintptr_t Slot_1417ac700_Forward(void* pObj, uint32_t nId);   // slot +0x278 — the "known" predicate
uintptr_t Slot_1417ac710_Forward(void* pObj, uint32_t nId);   // slot +0x2d8
uintptr_t Slot_1417ac720_Forward(void* pObj, uint32_t nId);   // slot +0x2c8

// 0x1417ac730 differs: it *calls* slot +0x1f8 and returns whether the answer was zero (`test %eax,%eax
// / sete %al`), so it is a real boolean and not a thunk.
bool Slot_1417ac730_IsZero(void* pObj, uint32_t nId);

// 0x1417ac5e0 — release three optional sub-objects, each only when its field is non-null.
extern void (*g_pfnL_1417a7d70)(void*);
extern void (*g_pfnL_1417d4a10)(void*);
extern void (*g_pfnL_14176aa20)(void*);
void Slot_1417ac5e0_ReleaseRefs(void* pThis);

}  // namespace tq
