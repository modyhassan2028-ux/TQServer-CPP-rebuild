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
// The seam stays injectable; its default now runs the ported lookup below, so the three
// wrappers are seam-free in practice while a test can still substitute it.
extern uint64_t (*g_pfnLogic_1417cad00)(uint64_t, uint64_t, uint64_t, uint64_t);
// 0x1417cad00 — the shared lookup, ported on top of the walk above; node value lives at +0x20.
//   test edx,edx / jz -> answer 0 for id 0 without touching the tree
//   lower_bound(this+8, &it, &id);  it[0]=scary, it[1]=node
//   the two _DEBUG iterator checks (error path 0x1418233c0, then execution continues)
//   node == head -> answer 0;  otherwise answer node[0x20]
uint64_t Slot_1417cad00_lookup(void* self, uint32_t id, uint64_t r8, uint64_t r9);
extern uint64_t (*g_pfnLogic_141797e00)(uint64_t, uint64_t);                      // 2-arg tail
extern uint64_t (*g_pfnLogic_14178f470)(uint64_t);                                // 1-arg tail

// 0x1417c8f70 — the tree walk 0x1417cad00 uses. Proven layout, straight from the bytes:
//   node +0x00 left, +0x08 parent, +0x10 right, +0x18 key (u32), +0x29 _Isnil byte
//   container +0x00 the word carried into the returned iterator, +0x30 the end node
//   iterator written to `out` = { container[0x30] or the found node, paired with container[0] }
// The routine is `lower_bound`: it descends by comparing node[0x18] against *(u32*)key,
// remembering the last node it turned left at, and answers the end node when the walk
// overshoots. 0x1418233c0 is the error path taken when container[0x00] is null.
// 0x1418233c0 is not an unknown: it is the IAT slot for MSVCR90.dll!__invalid_parameter_noinfo,
// resolved from the import directory (tools/bulk/iat_slots.json). That matters for fidelity: this
// entry point RETURNS in the CRT's contract, which is why the bytes keep executing after the call,
// and why a port that "helpfully" treated it as noreturn would be wrong. With the default handler
// in place it terminates, so the following dereference of a zeroed r11 never actually happens.
extern void (*g_pfn_invalid_parameter_noinfo)(void);                              // MSVCR90 import
void* Slot_1417c8f70_lower_bound(void* container, void* out, const uint32_t* key);

// 0x1417a8520 is the SAME routine as 0x1417c8f70: 55 instructions, identical mnemonics, and
// operands that differ only in jump/call targets, which must differ because the code sits at a
// different address. Verified by comparing the two disassemblies instruction by instruction, so
// the ported walk serves both and no second port is written.
extern void (*g_pfnLogic_1417a6960)(void* value, uint64_t arg);                    // 2-arg method
// 0x1417a8a50: id 0 answers false; otherwise lower_bound over the map at this+0x18, and on a hit
// whose stored pointer is non-null, call 0x1417a6960(pointer, arg3). Answers true for every id
// that is not 0, whether or not the key was found.
bool Slot_1417a8a50(void* self, uint32_t id, uint64_t arg3, uint64_t r9);

// 0x14177c0a0 — exact-key search over the same node layout as the ported walk
// (right +0x10, key +0x18, value +0x20, _Isnil +0x29). Answers the stored value, or 0 when the
// key is absent; the candidate is the smallest node whose key is >= the wanted one, so
// `key < candidate->key` is how the bytes decide "absent".
uint64_t Slot_14177c0a0_find(void* self, uint32_t key);

// 0x141724850 — 168 call sites. Two instructions: reload the pointer from [rcx] and tail-call
// operator delete on it. Nothing is null-checked, exactly as in the bytes.
void Slot_141724850_delete_through(void* holder);

// 0x1417ac810 — 51 call sites. Dispatch through a vtable reached as [self+8] -> [inner] ->
// slot 0x1f8. The id in edx is forwarded unchanged.
uint64_t Slot_1417ac810_vcall_1f8(void* self, uint32_t id);

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
