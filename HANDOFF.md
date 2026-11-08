# HANDOFF

Written 2026-11-08 by the agent working the CQBase/Syndicate port. Read this first, then AGENTS.md,
then the tail of PORTING_LOG.md. The point of this file is that the next agent can start a batch
within minutes without re-deriving anything.

## The method (do not change it)

Nothing is written from memory, guessing or "reasonable" reconstruction. Every body is read out of
the disassembly of the original `Syndicate.dll` (Conquer Online v6159) byte by byte, then transcribed
into C++ so that each statement sits next to the comment naming the instruction it came from. If a
callee is not ported yet, the body calls it through a named `g_pfnLogic_<address>` seam that is
documented and left null or defaulted, and the seam is recorded in the header and in the commit
message. A seam is never filled with invented behaviour, and an unported callee is never inlined by
guesswork.

Each batch is verified before it is committed:

    g++ -std=c++17 -I. -g -Wall -Wextra -fsanitize=address,undefined \
        -o /tmp/logic_test tests/syndicate_logic_tail_slots_test.cpp \
        modules/syndicate/src/CsyndicateLogicTailSlots.cpp

then run six consecutive times, all six passes required. ASan, UBSan and LSan are all live in that
one build. A batch is committed and pushed only after those six runs.

One rule learned the hard way: **a stale binary is not a pass.** Always confirm the compile line
produced no errors before believing a green run, because a failed build silently leaves the previous
binary in /tmp and the test prints a plausible number. This already produced one commit (`9239ad9`)
whose message described code that did not compile; it was corrected in the following commit. Check
the build output, not just the test output.

## Where the work stands

- Ported bodies in `modules/syndicate/src/CsyndicateLogicTailSlots.cpp`: 26 (24 at 8c97b8d).
  Two commands, because two bodies do not start with the four original types:
  `grep -cE '^(void|void\*|uint64_t\*|uint64_t|bool|int|uint32_t) Slot_[0-9a-f]+_'` = 25
  plus `grep -cE '^const char\* Slot_'` = 1 (`Slot_14178f470`).
- Batteries: 255 assertions in `tests/syndicate_logic_tail_slots_test.cpp` (219 at 8c97b8d, 240 after 0x1417caa00), all passing, 6/6 runs, sanitizers clean. The binary prints the count itself: `LOGIC_SLOTS_OK checks=255 fails=0`.
- The `0x14177f980` family is complete and wired: `0x14177f980` -> `0x141779400` -> `0x141779090`,
  plus both singletons (`0x14177c770`, `0x1417b6210`), the map constructor `0x14177c6c0`, its end-node
  builder `0x14177ace0`, the key search `0x14177c0a0`, `lower_bound` `0x1417a8520`, the range pass
  `0x1417a6960`, the vector clear `0x1417495d0`, the append `0x141732040` and the grow-and-insert
  `0x141730cd0`.

### Data shapes confirmed from the bytes (stop re-deriving these)

- Map container (0x40 bytes): `+0x00` proxy word, `+0x30` end node, `+0x38` size.
  The proxy is an 8-byte allocation holding the map pointer itself, so `*word` leads back to the
  owner. `0x14177c6c0` builds it; the iterator checks in the walks compare against it.
- Tree node: `+0x00` left, `+0x08` parent, `+0x10` right, `+0x18` key (32-bit), `+0x20` value,
  `+0x28` colour byte, `+0x29` `_Isnil`. The map's own end node has `_Isnil` set; the node built by
  `0x14177ace0` has it clear.
- 4-byte vector: `+0x18` begin, `+0x20` finish, `+0x28` capacity end, `+0x00` container word.
- `0x1417b6210`'s 0x88-byte object: two vtable stores in sequence, so `0x141835068` is what survives
  at `+0x00`; words 8..0x58 cleared, byte at `0x60`, unaligned words at `0x61`, `0x69`, `0x71`, `0x79`.
- Failure paths in these bodies call `CQBase.dll!log_InlineLogERROR` (not an assert) or
  MSVCR90's `__invalid_parameter_noinfo`; both are seams, never crashes invented in the port.

### Seams still open (each is a callee nobody has ported yet)

- `14172d120`
- `141730cd0`
- `141732040`
- `1417495d0`
- `141779400`
- `14177ace0`
- `14177c6c0`
- `14177f980`
- `1417873a0`
- `141797e00`
- `14179db30`   the value at node[0x20], first of the four; takes 0x3ff as its second argument
- `1417a1180`   the value at node[0x20], second
- `14179a150`   the value at node[0x20], third
- `14179a020`   the value at node[0x20], fourth and last
  (the four are the destroy chain 0x1417caa00 runs per node; each is a one-line seam, null by default)
- `1417a6960`
- `1417a8940`
- `1417a8a50`
- `1417cad00`
- `1417cad90`
- `1417cadb0`
- `1417cb000`

## What to do next

1. Port the seams above in the order they are called, smallest first; `0x14172d120` is the only call
   `0x141730cd0` makes.
2. Keep the frontier list fresh:

       python3 - <<'PY'
       # calls made by ported bodies that no ported body satisfies
       # (see the frontier script in PORTING_LOG.md entries of 2026-11-08)
       PY

3. Do not extend a fragmented `.pdata` row by guessing where it ends. If a row needs bytes beyond
   its record, take them from the next record's start or from Capstone over the physical image, and
   write down which evidence you used.


## Decoded (already ported): 0x14172d120 (the one-element insert)

This body was decoded first and then ported with its tests; the decode is kept here as the evidence trail. It is
662 bytes, 187 instructions, `std::vector::_Insert_n` with three paths.

Signature: `(self /*rcx*/, it /*rdx, pair*/, count /*r8*/, value /*r9*/)`.

Setup: capacity = `begin ? (cap_end - begin) >> 2 : 0`; if `count == 0` there is nothing to do; size =
`(finish - begin) >> 2`; `max_size = 0x3fffffffffffffff` (`movabs`), so `max_size - size < count`
throws through `0x141722c70` and the bytes put an `int3` right after that call.

Path A — reallocate (`cap < count + size`):
  `half = cap >> 1`; `grown = (max_size - half < cap) ? 0 : cap + half`; then `grown = max(grown,
  count + size)` (`cmovb`). Allocate with `0x141724d10(self + 0x10, grown)`. Offset =
  `(it[1] - begin) >> 2`. Fill `count` copies of `*value` at `buffer + offset*4`, then two
  `memmove_s` calls: the head (`begin`, `offset*4` bytes) into `buffer`, and the tail (`it[1]`,
  `(old_finish - it[1]) >> 2 * 4` bytes) into `buffer + (offset + count)*4`. The old buffer goes to
  `0x1417f2fdc` when it is non-null. Then `cap_end = buffer + grown*4`, `finish = buffer +
  (count+size)*4`, `begin = buffer`.

Path B — room exists (`cap >= count + size`), and there are at least `count` elements after the
insertion point (`(finish - it[1]) >> 2 >= count`): save `*value`; `tail_bytes = count*4`;
`new_finish = finish - tail_bytes`; call `0x14172acb0(self, new_finish, finish, finish)` and store its
return in `finish`; call `0x141727380(it[1], new_finish, finish)`; then fill `count` elements from
`it[1]` with the saved value.

Path C — room exists but fewer than `count` elements sit after the point: call
`0x14172acb0(self, it[1], finish, it[1] + count*4)`; fill the gap from `it[1]` to the old finish, then
`finish += count*4` and fill the remaining `count - moved` copies after the fact.

Resolved callers, so nothing here needs guessing:

  - `0x1418232a8` (both memmove-looking calls) is **`MSVCR90.dll!memmove_s`** — that is why the calls
    carry four arguments (dst, dst size, src, count). Keep the four-argument shape, and let the seam
    forward to `::memmove` on Linux, noting that the valid-argument path is identical.
  - `0x141722c70` length error, `0x141724d10` allocate, `0x14172acb0` and `0x141727380` element
    moves, `0x1417f2fdc` deallocate: all five are code rows, all five still unported, all five seams.

## How to keep this file honest

Update it at the end of every batch: the ported count, the assertion count taken from the test binary
itself, the seam list taken from the header, and one line on what the next batch is. Never write a
number here you did not just measure, and never describe a body as done before its compile line came
back clean.


### Evidence for the five seams of 0x14172d120

Full disassembly of each callee is saved in `docs/evidence/14172d120_callees.txt`, so the next batch
does not need to re-survey. Sizes, all small enough to port together:

- `0x141722c70` 106 bytes, 21 instructions, calls `0x1417f3154`, `0x141823270`, `0x141823288`, `0x1418233f8`
- `0x141724d10` 109 bytes, 26 instructions, calls `0x1417f3154`, `0x1417f3166`, `0x1418233e8`
- `0x14172acb0` 60 bytes, 18 instructions, calls `0x1418232a8` (`memmove_s`)
- `0x141727380` 59 bytes, 18 instructions, calls `0x1418232a8` (`memmove_s`)
- `0x1417f2fdc` is **not a `.pdata` row start**; it lives inside another row, so locate the containing
  row before transcribing it. Do not invent a body for it.

That is 9-ish instructions of real work per body: the batch is a single sitting if the containing row
for `0x1417f2fdc` is found first.


## Frontier after the 0x14172d120 family (surveyed 2026-11-08)

Evidence for all three is in `docs/evidence/frontier_after_14172d120.txt`.

- **`0x1417a8940` (268 bytes, 73 instructions) — ported.** A map lookup that answers a 32-bit
  value. Container reads: end node at `+0x88`, container word at `+0x58`, node `_Isnil` at `+0x21`,
  key at `+0x18`, and the answered value at `+0x1c`. The walk is the usual one (`cmp [rax+0x18],edx /
  jae` then right or left), the candidate check is `edi < [rbx+0x18]` against the searched key, and a
  miss returns 0. Note the differing offsets from the 0x40-byte map (`+0x58`/`+0x88`/`+0x21`), so do
  not reuse the other map's constants.
- **`0x1417873a0` (2051 bytes, 345 instructions) — do not start as a single unit.** It is a jump-table
  dispatcher: a chain of `cmp ecx,<id>` selects a case, each case calls a singleton getter and then
  tail-jumps through the object's vtable (`mov r8,[rax] / jmp qword ptr [r8]`). The table is indexed
  by `movzx` from a byte table, so the case count and the ids have to be extracted from the bytes
  before anything is transcribed. This needs its own batch with the jump table decoded first.
- **`0x1417caa00`** is ported now (`Slot_1417caa00_erase_all`); its four destroy callees are the seams above.

## Bugs that were mine, not the port's (so the next agent does not repeat them)

Every one of these was in the test scaffolding:

- A fake object stored the function pointer in its first word instead of a pointer *at* the vtable
  table. The object's word 0 must be the table address.
- A fake container word at `+0x20`/`+0x00` was a bare pointer instead of the proxy shape above, so a
  bound load went through null.
- An end pointer was set on the last slot instead of one past it, so a range looked one shorter.
- A fake container was too small for the `+0x40` the code reads.
- A miss case asked the map for the key it actually held, and a final expectation asked for a kind
  the scan had never matched.

When a check fails, suspect the scaffolding before the transcription, but prove which one is wrong
against the bytes before changing either.

## Commit style

`port: <what>` for a batch, with the body explaining what the bytes do, the seams that remain, the
assertion count, and any bug that was the test's fault rather than the port's. `fix: <hash> <what>`
when an earlier commit was wrong. Push every successful batch immediately.

## Counts are cheap to check, so check them

The first draft of this file said 27 bodies and 193 assertions. The real numbers on the commit that
carries it are 17 bodies (`grep -cE '^(void|uint64_t\*|uint64_t|void\*) Slot_[0-9a-f]+_'`) and 191
assertions (the test binary prints its own count). Take numbers from the tool that produced them, not
from memory, because a handoff with wrong numbers is worse than one with none.

Seams declared in the header: 19 (some are already defaulted to a ported body, some are still null).

## Next batch

`0x14172d120` is ported and tested, so the frontier moves to the five seams it still calls:
`0x141722c70` (length error), `0x141724d10` (allocate), `0x14172acb0` and `0x141727380` (element
moves), `0x1417f2fdc` (deallocate). Take them smallest first and wire each seam to its ported body the
way `g_pfnLogic_141779400` was wired, keeping the pointer so a test can still watch the arguments.
