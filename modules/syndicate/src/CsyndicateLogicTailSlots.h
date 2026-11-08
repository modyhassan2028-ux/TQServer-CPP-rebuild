#include <cstddef>
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

// The two lazily created singletons behind 0x14177f980. Both follow the same MSVC shape: read a
// static slot, allocate with operator new, build, store, and log through
// CQBase.dll!log_InlineLogERROR if the allocation came back null. The log call is variadic, so it
// is an injectable seam taking the same four pointers and the same line number the bytes pass.
extern void* (*g_pfnLogic_14177c6c0)(void* mem);              // the 0x40-byte object's constructor
extern void (*g_pfn_log_InlineLogERROR)(const void* p0, const void* p1, const void* p2,
                                        const void* p3, uint32_t line);   // CQBase import
void* Slot_14177c770_singleton(void);                          // 0x40 bytes, ctor 0x14177c6c0
void* Slot_1417b6210_singleton(void);                          // 0x88 bytes, initialised inline
void Slot_14177c770_seed(void* value);                         // test hook: preload the static slot
void Slot_1417b6210_seed(void* value);

// Three callees still to port, kept as seams so neither body below invents anything:
//   0x14177ace0 builds the end node of the map that 0x14177c6c0 constructs
//   0x1417495d0 prepares the argument that 0x1417a6960 then hands to every element
//   0x141732040 is the per-element call 0x1417a6960 makes
extern void* (*g_pfnLogic_14177ace0)(void* self);
extern void* (*g_pfnLogic_1417495d0)(void* arg);
extern void (*g_pfnLogic_141732040)(void* arg, void* elem);

// 0x141732040 appends one 4-byte element, and its capacity-full path hands off to 0x141730cd0,
// which is not ported yet. The second pointer that call receives points at stack space this frame
// never writes, so the port passes a zeroed buffer of the same width and says so rather than
// pretending to know what the callee stores there.
extern void (*g_pfnLogic_141730cd0)(void* self, void* out_or_arg, void* pair, const void* value);
// 0x14172d120 is the actual one-element insert that 0x141730cd0 calls with (self, iterator, 1, value).
// It is unported, so it stays a seam; the port re-reads begin afterwards exactly as the bytes do,
// because an insert may move the buffer.
extern void (*g_pfnLogic_14172d120)(void* self, uint64_t* it, uint64_t count, const void* value);

// 0x141730cd0 — the grow-and-insert path: works out the element offset, calls the insert, then
// re-reads begin and answers an iterator pointing at the element that was inserted.
void* Slot_141730cd0_grow_insert(void* self, uint64_t* out, const uint64_t* pair, const void* value);
// 0x14172d120 — std::vector::_Insert_n, 662 bytes and three paths. Its five code-row callees are all
// unported, so each is a seam: 0x141722c70 throws for length, 0x141724d10 allocates, 0x14172acb0 and
// 0x141727380 move elements, 0x1417f2fdc frees the old buffer. The two four-argument calls are
// MSVCR90!memmove_s (dst, dst size, src, count), not the two-argument memmove they resemble.
extern void (*g_pfnLogic_141722c70)(void);
extern void* (*g_pfnLogic_141724d10)(void* alloc, uint64_t count);
extern uint64_t (*g_pfnLogic_14172acb0)(void* unused, void* src, void* src_end, void* dst);
extern uint64_t (*g_pfnLogic_141727380)(void* src, void* mid, void* dst_end);
extern void (*g_pfnLogic_1417f2fdc)(void* p);
extern void (*g_pfn_memmove_s)(void* dst, size_t dst_size, const void* src, size_t count);
void Slot_14172d120_insert_n(void* self, const uint64_t* it, uint64_t count, const void* value);
// 0x141722c70 — builds std::length_error("vector<T> too long") on the frame and throws it through
// _CxxThrowException. That object layout is MSVC ABI, so the throw itself is one seam taking the text.
// The string the bytes load is at 0x141824f38.
extern void (*g_pfn_throw_length_error)(const char* what);
void Slot_141722c70_throw_length_error(void);

// 0x141724d10 — allocate count 4-byte elements, with the divide-based overflow guard the bytes make
// before operator new(count*4).
void* Slot_141724d10_allocate(void* unused, uint64_t count);

// 0x14172acb0 — moves src..src_end down to dst and answers dst + byte_count.
// Argument order is the one the bytes take: rcx ignored, rdx src, r8 src_end, r9 dst.
uint64_t Slot_14172acb0_move_block(void* unused, void* src, void* src_end, void* dst);

// 0x141727380 — moves src..mid so it ends at dst_end. The guard is a *signed* jle, so a mid below
// src means no move at all.
uint64_t Slot_141727380_move_tail(void* src, void* mid, void* dst_end);

// 0x1417f2fdc — jmp [0x1418233f0], which iat_slots.json resolves to MSVCR90!operator delete.
void Slot_1417f2fdc_deallocate(void* p);

// 0x1417a8940 — map lookup answering a 32-bit value. Container reads differ from the 0x40-byte map
// already ported: end node at +0x88, container word at +0x58, node _Isnil at +0x21, key at +0x18 and
// the answered value at +0x1c. Do not reuse the other map's offsets here.
uint32_t Slot_1417a8940_lookup(void* self, uint32_t key);

// 0x1417495d0 — clears the 4-byte vector at +0x18/+0x20/+0x28. The memmove the bytes would make is
// a zero-length one, so the only effect is finish = begin; the port keeps the shape that shows it.
void Slot_1417495d0_clear_vector(void* self);

// 0x141732040 — appends one element, growing through 0x141730cd0 when the vector is full.
void Slot_141732040_push_back(void* self, const uint32_t* value);

// 0x14177ace0 — allocates the 0x30-byte node the map constructor uses as its end node: left,
// parent and right cleared, the colour byte at +0x28 set to 1, _Isnil at +0x29 cleared.
void* Slot_14177ace0_new_node(void);

// 0x1417a8520 — lower_bound over the same tree layout. The key arrives by pointer, and the answer is
// an iterator pair: the candidate when it is not the end node and the key is not below its own, the
// end pair otherwise.
uint64_t* Slot_1417a8520_lower_bound(void* self, uint64_t* out, const uint32_t* key);

// 0x14177c6c0 — constructor of the 0x40-byte map: an 8-byte proxy that points back at the map,
// the end node at +0x30 with _Isnil set and left/parent/right pointing at itself, size 0 at +0x38.
void* Slot_14177c6c0_ctor(void* self);

// 0x1417a6960 — walks the range at [self+0x38]..[self+0x40] and calls 0x141732040 with the prepared
// argument and each element. Bounds and the container word are re-checked every step, as written.
void Slot_1417a6960_iterate(void* self, void* arg);

// 0x141779090 — scans the range held at [self+0x20]..[self+0x28] (8-byte slots) for the first
// element whose virtual answer at slot 0x40 equals id and whose answer at slot 0x48 equals kind.
// Writes the iterator pair {container word, slot} into out and answers out.
uint64_t* Slot_141779090_search(void* self, uint64_t* out, uint32_t id, uint32_t kind);

// 0x141779400 — the tail target of 0x14177f980. Runs that scan, re-checks the pair, then takes
// the element through virtual slot 0x10 with 4 and tail-calls the result's slot 0x48.
uint64_t Slot_141779400(void* found, uint32_t id, uint32_t kind);

// 0x14177f980 — the seam itself. Kinds 1..3 ask the 0x88-byte singleton's vtable slot 0x1f8 for an
// id, look that id up in the 0x40-byte singleton's map, and tail-call 0x141779400 with the found
// object, the original id and the kind. Any other kind logs through CQBase and answers 0. The tail
// call goes through this pointer; it now defaults to the ported 0x141779400, so the chain runs end
// to end, and it stays a pointer so a test can watch what gets forwarded.
extern uint64_t (*g_pfnLogic_141779400)(void* found, uint32_t id, uint32_t kind);
uint64_t Slot_14177f980(void* self, uint32_t id, uint32_t kind, uint64_t r9);

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

namespace tq {

// ============================================================================
// 0x1417caa00 — the manager's map clear (synmanager.cpp). Ported from the bytes.
//
// The body walks the map at this+8 from its begin to its end node, and calls the
// element destructor chain on node[0x20] for every node it passes:
//     0x14179db30(ptr, 0x3ff) -> 0x1417a1180(ptr) -> 0x14179a150(ptr) -> 0x14179a020(ptr)
// None of the four is ported, so each is an injectable seam named by its address; the
// default is null, which is the honest state ("nobody has transcribed this yet").
//
// Shape read off the bytes:
//   +0x38  the map's end node, and the same word is the iterator's stop value
//   +0x08  the proxy word the iterator carries; *(word) is the map itself (its +0x30 is
//          the end node again, so the _DEBUG check compares the node against it)
//   node   +0x00 left, +0x08 parent, +0x10 right, +0x20 the value pointer, +0x29 _Isnil
//
// The loop carries a dead-loop guard: ebp counts iterations, `cmp ebp,0xf4240 / ja` sends
// the run to CQBase!log_InlineLogERROR at IAT 0x141823030 with the four strings the image
// holds at 0x141824ca8 (format "\xa1\xef%s(%s)\xa1\xef in %s, %d"), 0x141832a18
// ("DEAD_LOOP_BREAK"), 0x141832a28 ("uLoopCount") and 0x141839fe0 (the synmanager.cpp
// path), with line 0x117 = 279. After reporting it returns true, exactly as the epilogue
// at 0x1417cab65 does.
// ============================================================================
extern uint64_t (*g_pfnLogic_14179db30)(void* p, uint32_t n);
extern uint64_t (*g_pfnLogic_1417a1180)(void* p);
extern uint64_t (*g_pfnLogic_14179a150)(void* p);
extern uint64_t (*g_pfnLogic_14179a020)(void* p);
extern void (*g_pfn_log_141823030)(const char* fmt, const char* expr, const char* which,
                                   const char* file, int line);
bool Slot_1417caa00_erase_all(void* self);

}  // namespace tq

namespace tq {

// 0x14178f470 — the "IF_OK(m_pRec)" gate from syndicate.cpp, line 0x8a8 (2216).
// Bytes: cmpq $0,[rcx+0x428] / jne; the miss reports through 0x141823030 and answers
// the empty string at 0x141827409. The hit loads m_pRec, calls its vtable slot 0x10
// with edx = 1, then tail-jumps through slot 0x78 of the vtable of what came back.
extern const char* Slot_14178f470(void* self);

}  // namespace tq

namespace tq {

// 0x141797e00 — the id predicate from the map at this+0x290 (a second layout: the node's
// nil byte is at +0x1d and the key at +0x18, not the +0x29/+0x18 the count map uses).
// The walk turns left (and records the candidate) when id >= node key, right otherwise;
// a candidate equal to the end node, or one whose key is above the id, selects the
// end-node pair instead. The answer is whether the chosen node differs from the end node.
extern bool Slot_141797e00(void* self, uint32_t id);

}  // namespace tq

namespace tq {

// 0x14179a020 — the last call of the destroy chain. It clears the container at +0x2a0,
// then walks the id range 0x19..0x27 (< 0x28) reading the record through vtable slot 2,
// asking slot 8 for the id, looking that up with 0x1417cad00 on the map at +0x438, and
// either erasing from the +0x2a0 container (0x14172ae00) or releasing the record through
// slots 0x16 and 7. A hit whose +0x428 is null is reported as "IF_OK(m_pRec)" at line
// 0x956 (2390) before the erase path runs.
extern void (*g_pfnLogic_141727640)(void* p);                    // the +0x2a0 clear
extern void (*g_pfnLogic_14172ae00)(void* container, void* out, void* key);  // the erase
void Slot_14179a020(void* self);
// 0x14179a150 is the same routine over the container at +0x2e0 and the id range 0xa..0x18.
// Proven by comparing the two rows instruction by instruction: 69 each, 57 byte-identical, and
// the only differences are those two immediates, the one displacement (+0x2a0 vs +0x2e0) and the
// rel32 targets that have to differ with the row's address.
void Slot_14179a150(void* self);

}  // namespace tq

namespace tq {

// 0x14179db30 — the memberwise tidy of a record (this, flags in dx). Nine vector members at a
// 0x30 stride are released under one flag bit each, then a masked block (0x1f) releases the
// member at 0x200 with a different callee. Constants read off the bytes:
//
//   bit  begin/finish/cap        type helper        bit   begin/finish/cap        type helper
//   0x01 0x50 / 0x68 / 0x70      0x1417862c0        0x40  0x170 / 0x188 / 0x190   0x141786500
//   0x02 0x80 / 0x98 / 0xa0      0x141786320        0x80  0x1a0 / 0x1b8 / 0x1c0   0x141786560
//   0x04 0xb0 / 0xc8 / 0xd0      0x141786380        0x100 0x1d0 / 0x1e8 / 0x1f0   0x1417865c0
//   0x08 0xe0 / 0xf8 / 0x100     0x1417863e0        0x1f  0x200 / 0x218 / 0x220   0x14178efd0
//   0x10 0x110 / 0x128 / 0x130   0x141786440              (masked, callee 0x14179cf10)
//   0x20 0x140 / 0x158 / 0x160   0x1417864a0
//
// The flag byte is read as `movzwl %dx,%esi`, so only bits 0..8 can ever be set.
extern void* (*g_pfnLogic_141787c50)(void* out, const void* type);                 // the type/allocator
extern void (*g_pfnLogic_14179cde0)(void* first, void* last, uint64_t count, void* alloc);
extern void (*g_pfnLogic_14179cf10)(void* first, void* last, uint64_t count, void* fn);
void Slot_14179db30(void* self, uint32_t uFlags);

}  // namespace tq

namespace tq {

// 0x141787c50 — three instructions: `mov %rdx,(%rcx) / mov %rcx,%rax / ret`, i.e. store the
// type row into the caller's slot and answer that slot.
void* Slot_141787c50(void* out, const void* type);

// 0x141726210 — free a subtree of the map whose node layout is the +0x1d one: right child
// recursed first, then the node deleted, then the walk moves to the left child.
void Slot_141726210(void* container, void* node);

// 0x141727640 — the same walk over the whole tree, then the head at +0x30 is pointed at itself
// on all three links and the size at +0x38 is cleared. Node nil byte +0x1d, key +0x18.
void Slot_141727640(void* container);

}  // namespace tq

namespace tq {

// 0x14179cde0 and 0x14179cf10 — the two range routines the tidy calls. Both take
// (first, last, count, fn), return nothing, and are the same algorithm: while the range holds
// more than 0x20 eight-byte elements, partition it through one helper and recurse into the
// smaller side with count/2 + count/4, keeping the larger side for the loop; when the range
// drops to <= 0x20 elements and the count still allows it, one tail call finishes the range;
// when the count runs out first, two helpers run and the routine returns.
//
// The two rows differ only in the four callees they use (verified against the two listings):
//   partition 0x141795a30 / 0x141795d40     tail 0x141793d50 / 0x141793fd0
//   exhausted 0x141795ca0 / 0x141795f70 and 0x141797670 / 0x1417976e0
// Their register allocation differs (fn in rax vs rbp, the midpoint in rbp vs r10) but the
// values, offsets, threshold and branch sense are identical.
extern void (*g_pfnLogic_141795a30)(void* out, void* first, void* last, void* fn);
extern void (*g_pfnLogic_141795d40)(void* out, void* first, void* last, void* fn);
extern void (*g_pfnLogic_141793d50)(void* first, void* last, void* fn, void* zero);
extern void (*g_pfnLogic_141793fd0)(void* first, void* last, void* fn, void* zero);
extern void (*g_pfnLogic_141795ca0)(void* first, void* last, void* fn);
extern void (*g_pfnLogic_141795f70)(void* first, void* last, void* fn);
extern void (*g_pfnLogic_141797670)(void* first, void* last, void* fn);
extern void (*g_pfnLogic_1417976e0)(void* first, void* last, void* fn);
void Slot_14179cde0(void* pFirst, void* pLast, int64_t nCount, void* pfn);
void Slot_14179cf10(void* pFirst, void* pLast, int64_t nCount, void* pfn);
// 0x141793fd0 — the small-range row of the 0x14179cf10 family. Its third argument is a
// comparator over 8-byte elements and the fourth is never read.
void Slot_141793fd0(void* pFirst, void* pLast, bool (*pfnLess)(void* a, void* b), void* unused);
// 0x141795d40 — the partition of the same family: the median of three is put in place by
// 0x141793e70, then the range splits around it. The pair comes back through the first argument.
extern void (*g_pfnLogic_141793e70)(void* first, void* mid, void* last,
                                   bool (*pfnLess)(void* a, void* b));
void Slot_141795d40(void** pOut, void* pFirst, void* pLast, bool (*pfnLess)(void* a, void* b));

}  // namespace tq

namespace tq {

// The four heap helpers the two range routines reach when the count runs out. All four
// work on 8-byte elements and take (first, last, fn); each pair differs only in which
// sift row it calls, and in both pairs the fn argument is stored to a stack slot and
// never read again, so it is carried and ignored exactly as the bytes do.
//
//   0x141795ca0 / 0x141795f70  make the heap: sift down parents count/2 .. 1, each with
//                              the element it currently holds (mov -0x8(%rdi,%rbx,8),%r9
//                              before the dec, so the index passed is the decremented one)
//   0x141797670 / 0x1417976e0  drain the heap: copy the head onto the tail slot, sift the
//                              saved tail down the shortened range, repeat while > 1 left
extern void (*g_pfnLogic_1417929f0)(void* first, uint64_t index, uint64_t count, void* elem);
extern void (*g_pfnLogic_141792b70)(void* first, uint64_t index, uint64_t count, void* elem);

void Slot_141795ca0(void* pFirst, void* pLast, void* pfn);
void Slot_141795f70(void* pFirst, void* pLast, void* pfn);
void Slot_141797670(void* pFirst, void* pLast, void* pfn);
void Slot_1417976e0(void* pFirst, void* pLast, void* pfn);

}  // namespace tq

namespace tq {

// 0x141792b70 — the sift handed a comparator as a fifth argument (stack slot 0x60 at entry).
// It walks the child pair down, then walks the hole back up against the saved element.
void Slot_141792b70(void* pFirst, int64_t nIndex, int64_t nCount, void* pElem,
                    bool (*pfnLess)(void* a, void* b));

}  // namespace tq

namespace tq {

// 0x1417929f0 — the twin sift. Its comparator (0x141787c60) writes an out slot that the
// up-pass row (0x1417917a0) then receives as a fifth argument, so both stay seams with their
// real shapes: (out, right, left) returning a verdict, and (first, hole, orig, elem, out).
extern bool (*g_pfnLogic_141787c60)(void* out, void* right, void* left);
extern void (*g_pfnLogic_1417917a0)(void* first, int64_t hole, int64_t orig, void* elem,
                                   uint64_t outValue);
void Slot_1417917a0(void* pFirst, int64_t nHole, int64_t nOrig, void* pElem, uint64_t outSlot);
void Slot_1417929f0(void* pFirst, int64_t nIndex, int64_t nCount, void* pElem);

}  // namespace tq

#endif
