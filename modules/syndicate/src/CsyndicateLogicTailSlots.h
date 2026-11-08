// ============================================================================
// CsyndicateLogicTailSlots.h — the last twelve CSyndicateLogic vtable slots that no
// hand-written file had mentioned. CSyndicateLogic holds 128 slots; 116 were already
// covered, these twelve were not.
//
// None of them carries a symbol, so each is named by the address it lives at and the
// header says so rather than inventing a method name. What the bytes state:
//
//   0x1417abe60  mov rcx,[rcx+0x10] / jmp 0x1417cadb0     forward member @0x10
//   0x1417ac010  mov rcx,[rcx+0x10] / jmp 0x1417caa00     forward member @0x10
//   0x1417ab1d0  mov rcx,[rcx+0x10] / jmp 0x1417cad90     forward member @0x10
//   0x1417ab1c0  mov rcx,[rcx+0x10] / jmp 0x1417cb000     forward member @0x10
//   0x1417aaf90  mov eax,0xf / ret                        constant 15
//   0x1417aafa0  mov eax,0xf / ret                        constant 15
//   0x1417abc50  cmp edx,0x3de / setge al                 (int32)arg >= 990
//   0x1417abc60  cmp edx,0x37a / setle al                 (int32)arg <= 890
//   0x1417aeba0  mov ecx,edx / jmp 0x1417873a0            forward the argument, drop this
//   0x1417af2f0  mov rcx,[rcx+0x20] / test / jz 0 / jmp 0x1417a8a50
//   0x1417af310  mov rcx,[rcx+0x20] / test / jz 0 / jmp 0x1417a8940
//   0x1417afac0  mov rcx,[rcx+0x28] / test / jz 0 / jmp 0x14177f980
//
// Eleven of the twelve end in a jump out of their own row, i.e. a tail jump: the callee
// starts with the caller's registers still live. The port models that honestly by passing
// the incoming rdx/r8/r9 through to the seam instead of dropping them.
//
// The comparison in 0x1417abc50/0x1417abc60 is decided by `sf == of` on a 32-bit
// subtraction, which is the SIGNED reading of edx, so a negative argument answers 0 for
// both even though its unsigned value is huge. That asymmetry is preserved and tested.
//
// The eight callee rows (0x1417cadb0, 0x1417caa00, 0x1417cad90, 0x1417cb000,
// 0x1417873a0, 0x1417a8a50, 0x1417a8940, 0x14177f980) exist as lifted bodies but are not
// ported by hand yet, so they are seams here, named by address.
// ============================================================================
#ifndef SYNDICATE_LOGICT_SLOTS_H
#define SYNDICATE_LOGICT_SLOTS_H

#include <cstdint>

namespace tq {

extern uint64_t (*g_pfnLogic_1417cadb0)(uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_pfnLogic_1417caa00)(uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_pfnLogic_1417cad90)(uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_pfnLogic_1417cb000)(uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_pfnLogic_1417873a0)(uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_pfnLogic_1417a8a50)(uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_pfnLogic_1417a8940)(uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_pfnLogic_14177f980)(uint64_t, uint64_t, uint64_t, uint64_t);

// The three lookup wrappers these forwarders land on, and the lookup itself. 0x1417cad00
// walks a container at this+8 (it calls 0x1417c8f70 and 0x1418233c0) and is not ported yet,
// so it stays a seam; the three wrappers around it are ported here.
extern uint64_t (*g_pfnLogic_1417cad00)(uint64_t, uint64_t, uint64_t, uint64_t);  // the lookup
extern uint64_t (*g_pfnLogic_141797e00)(uint64_t, uint64_t);                      // 2-arg tail
extern uint64_t (*g_pfnLogic_14178f470)(uint64_t);                                // 1-arg tail

// 0x1417cad90: call lookup / return (result != 0)
int      Slot_1417cad90(void* self, uint64_t rdx, uint64_t r8, uint64_t r9);
// 0x1417cadb0: call lookup(this, (u32)r8, ...) / on hit tail-call (hit, (u32)rdx) / on miss 0
uint64_t Slot_1417cadb0(void* self, uint64_t rdx, uint64_t r8, uint64_t r9);
// 0x1417cb000: call lookup / on miss substitute 0x141827409 / tail-call it
uint64_t Slot_1417cb000(void* self, uint64_t rdx, uint64_t r8, uint64_t r9);

uint64_t Slot_1417abe60(void* self, uint64_t rdx, uint64_t r8, uint64_t r9);
uint64_t Slot_1417ac010(void* self, uint64_t rdx, uint64_t r8, uint64_t r9);
uint64_t Slot_1417ab1d0(void* self, uint64_t rdx, uint64_t r8, uint64_t r9);
uint64_t Slot_1417ab1c0(void* self, uint64_t rdx, uint64_t r8, uint64_t r9);
uint64_t Slot_1417aeba0(void* self, uint64_t rdx, uint64_t r8, uint64_t r9);
int      Slot_1417aaf90(void* self);
int      Slot_1417aafa0(void* self);
int      Slot_1417abc50(void* self, int32_t arg);
int      Slot_1417abc60(void* self, int32_t arg);
int      Slot_1417af2f0(void* self, uint64_t rdx, uint64_t r8, uint64_t r9);
int      Slot_1417af310(void* self, uint64_t rdx, uint64_t r8, uint64_t r9);
int      Slot_1417afac0(void* self, uint64_t rdx, uint64_t r8, uint64_t r9);

}  // namespace tq

#endif
