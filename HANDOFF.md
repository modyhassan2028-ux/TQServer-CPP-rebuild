# HANDOFF

## Two `npcserver` folders — which one is the live work

- `modules/npcserver/{src,unattributed}/` — **the live port.** Verbatim function-by-function bodies keyed by their
  binary address (D88 → D242), manifest-driven suites under `tests/npcserver_d*.cpp`, runner
  `tools/run_npcserver_suites.sh`. 582 of 4099 bodies, 61 suites.
- `npcserver/` (top level, untouched since the 27 Oct reorganisation) — the early wave-1 reconstruction with
  hand-named files (`NpcAssembly.cpp`, `NpcAiTick.cpp`, …) and `main.cpp`, still referenced by `build.sh`. It is a
  different, older effort against the same binary; nothing lands there any more.



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

- Ported bodies in `modules/syndicate/src/CsyndicateLogicTailSlots.cpp`: 69 (42 at 8c97b8d).
  The command, which no longer depends on the return type or a `_name` suffix:
  `grep -cE '^[A-Za-z_][A-Za-z0-9_<>:*& ]* Slot_141[0-9a-f]{6}'` on that file.
  (Earlier patterns here missed `bool` and `const char*` bodies; this one counts them all.)
- `modules/syndicate/src/msg/msgsynctors.cpp`: 17 more (every message constructor)
- `modules/syndicate/src/module.cpp`: the sixteen member seams now fall back to those real bodies
- `modules/syndicate/src/msg/msgleagueroboptpb.cpp` / `msgleaguetokenpb.cpp`: the two `+0x408` protobuf constructors

**Frontier, measured:** 1690 open addresses but only **26 function starts**; 1641 are inside already-ported
functions. Quote the 26, not the 1690. **Syndicate game code is closed.** All 26 starts are accounted for: twenty container accessors (D99), four
comparators (D100), the four forwarders in `vtableforwarders.cpp` (D101). The 0x600-byte entry at
`0x141821f80` turned out to be nine compiler-generated `atexit` registration thunks, not a function, and
`0x1417e8016` is an import thunk — neither is portable. Next: the next module in `Docs/REMAINING_ROADMAP.md`.
- `modules/syndicate/src/vtableforwarders.cpp`: four vtable forwarders and their selector (`0x14177fa10..0x14177fa90`)
- `modules/syndicate/src/syncomparators.cpp`: the four comparator leaves (`0x141780100`, `0x1417e0830`, `0x14174e3a0`, `0x1417b0920`)
- `modules/syndicate/src/containeraccessors.cpp`: twenty container accessors (`0x1417c5980..0x1417c5f5a`)
- `modules/syndicate/src/msg/msgfieldflags.cpp`: the twelve `+0x30` field setters (`0x1417d9840..0x1417d98f7`)
- `modules/syndicate/src/msg/msgpbseams.cpp`: the twenty-one protobuf seams nothing defined, which is why the family now links (`0x1417ac700`, `0x1417ac710`, `0x1417ac720`, `0x1417ac730`, `0x1417ac5e0`)
- `modules/syndicate/src/module.cpp`: 5 more (`0x14177ead0`, `0x14177e890`, `0x14177ec90`, `0x14177ed30`, `0x14177ed40`)
- `modules/syndicate/src/pointrecordmgr.cpp`: 1 more (`0x14177ed50`)
- `modules/syndicate/src/msg/msgleagueopt.cpp`: 1 more (`0x1417d68d0`, 79 cases, 2 tables)
- `modules/syndicate/src/msg/msgleaguerobopt.cpp`: 1 more (`0x1417d8920`, 7 cases, list build)
- `modules/syndicate/src/CMsgLog.cpp`: 19 more (`0x1417d97c0`, twelve setters, then `0x1417dae90`,
  `0x1417daee0`, `0x1417dafe0`, the ctor/dtor and `0x1417db010`), same command.
- Batteries: 14711 + 1284 + 125 + 491 + 198 + 125 + 33 + 27 + 33 + 24 + 24 + 20 + 142 assertions (thirteen suites)
- `tools/run_syndicate_pbsuite.sh` = the protobuf constructor suite, 33 assertions x6 in `tests/syndicate_logic_tail_slots_test.cpp` (219 at 8c97b8d), `tests/syndicate_findoradd_test.cpp` and `tests/syndicate_cmsglog_test.cpp`, `tests/syndicate_msgleagueopt_test.cpp`, `tests/syndicate_leaguerobopt_test.cpp`, `tests/syndicate_module_test.cpp`, `tests/syndicate_slotforwarders_test.cpp`, `tests/syndicate_msgsynctors_test.cpp`, all passing, 6/6 runs, sanitizers clean. Each binary prints its own count: `LOGIC_SLOTS_OK checks=14711 fails=0`, `FINDORADD_OK checks=1284 fails=0`, `CMSGLOG_OK checks=125 fails=0`, `MSGLGOPT_OK checks=491 fails=0`, `LEAGUEROB_OK checks=198 fails=0`, `MODULE_OK checks=125 fails=0`, `SLOTFWD_OK checks=24 fails=0`, `MSGSYNCTOR_OK checks=142 fails=0`.
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

Checked with `python3 tools/frontier.py`: every callee a readable row annotates as `call 0x…`,
`jmp 0x…` or `tail 0x…` now has a body (75 mentions, 0 open). The readable tier of this wave is
closed; `0x1417873a0` is no longer a seam (D86 ported it in `SyndicateRankName.cpp`) and
`0x14172d120` has its body in `CsyndicateLogicTailSlots.cpp`.

- `14172d120`
- `141730cd0`
- `141732040`
- `1417495d0`
- `141779400`
- `14177ace0`
- `14177c6c0`
- `14177f980`
- (the four are the destroy chain 0x1417caa00 runs per node; each is a one-line seam, null by default)
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

## D103 (latest)

- `ini.cpp` / `inimgr.cpp` now live at the binary's own `modules/cqbase/src/` paths
  (renamed from cini/cinimgr). Twelve of the twelve CQBase `__FILE__` paths are present.
- `cqbase_d53` moved to the D102 seam names; `cqbase_d7/d8/d10/d11/d12` keep a log sink
  installed so a shared process does not call through a null `g_pfnLogPrintf`.
- `tools/run_cqbase_cycle.sh` links the syndicate objects its units reach.
- `cqbase_d24` now restores the five release seams it installs, so `cqbase_d25`
  runs clean in the same process: `CQBAE-CYCLE-6X-GREEN: 77 units` (6 passes, ASan+UBSan).
- Next: back to the function porting sequence — the limbs table at 0x1417c5980..
  (the small accessor cluster) is dumped and ready.

## D129 (latest)

- The pure accessor cluster 0x1417c5980..0x1417c5f80 is ported: `modules/syndicate/src/
  synacc.cpp`, 41 bodies, `SYNDICATE_D129_OK ... 56 checks`, 6 passes under ASan+UBSan.
- Next: the rest of the same cluster — 0x1417c5b30 / 0x1417c5b80 (they call the seam at
  0x1418233c0), the sentinel walks 0x1417c5c50 / 0x1417c5f00 / 0x1417c5f30, and the two
  `jmp 0x1417f2fdc` thunks 0x1417c5c80 / 0x1417c5cc0.

## D130 (latest)

- The cluster's non-pure tail is ported: 0x1417c5b30, 0x1417c5b80, 0x1417c5c50, 0x1417c5c70,
  0x1417c5c80, 0x1417c5cc0, 0x1417c5f00, 0x1417c5f30, 0x1417c5f50 ->
  `SYNDICATE_D130_OK ... 24 checks`, 6 passes under ASan+UBSan.
- Next: 0x1417c5e00 / 0x1417c5e80 (re-dump, the earlier reads were truncated) and
  0x1417c5f60, the next iterator comparison on the same seam.

## D131 (latest)

- The accessor cluster is closed: `SYNDICATE_D131_OK ... 20 checks`, 6 passes under
  ASan+UBSan. 57 bodies across D129/D130/D131.
- Next: 0x1417c5fa0, the tree increment (`cmpq $0x0,(%rcx)` / the sentinel check on `0x8(%rbx)`
  / the `0x29` climbs at 0x1417c5fd9 and 0x1417c6007). Its dump must be taken whole this time,
  from 0x1417c5fa0 to the `ret` past 0x1417c6028 before any line is written.

## D132 (latest)

- Sixteen more bodies: `SYNDICATE_D132_OK ... 48 checks`, 6 passes under ASan+UBSan. The
  cluster now stands at 73 bodies (D129 41, D130 9, D131 7, D132 16).
- Next: 0x1417c62e0 needs the seam at `0x141823288` modelled first; 0x1417c63c0 needs a whole
  dump from its start past 0x1417c63fe before a line is written.

## D133 (latest)

- Fifteen more bodies: `SYNDICATE_D133_OK ... 34 checks`, 6 passes under ASan+UBSan.
  The cluster now stands at 88 bodies (D129 41, D130 9, D131 7, D132 16, D133 15).
- Next: 0x1417c6710 (`div %rcx`, `cmp $0x30,%rax`, then `call *0x1418233e8`) needs a whole
  dump; 0x1417c62e0 needs the `0x141823288` seam modelled first.

## D134 (latest)

- Seventeen more bodies: `SYNDICATE_D134_OK ... 22 checks`, 6 passes under ASan+UBSan.
  Cluster total 105 bodies.
- Next: the four element-count allocators 0x1417c6710 / 0x1417c6790 / 0x1417c6810 /
  0x1417c6910. They need the three length_error seams modelled first: 0x1418233e8 (object
  constructor), the `0x141824c40` vtable store, and 0x1417f3154 (throw helper), with the good
  path tail-calling 0x1417f3166.

## D135 (latest)

- The four element-count allocators are ported, with the length_error path modelled through
  three null-by-default seams: `SYNDICATE_D135_OK ... 30 checks`, 6 passes. Cluster 109 bodies.
- Next: the stretch past 0x1417c69d0 was cut at 0x1417c69ff, so the next unit starts with a
  whole dump from 0x1417c69e0 (the `add $0x18,%rcx` tail jump) onward.

## D136 (latest)

- Four bodies at the head of the 0x1417c69e0 stretch: `SYNDICATE_D136_OK ... 12 checks`,
  6 passes. Cluster 113 bodies.
- Next from the saved dump: 0x1417c6a60 (two `*0x141823030` asserts with lines 0x32a/0x32b,
  then 0x141785dc0 and 0x1417c5640) and 0x1417c69e0 (tail jump through 0x141823290, whose
  slot still holds an unresolved RVA 0x1628a6).

## D137 (latest)

- The 0x141823030 assertion is modelled and the two checked forwarders 0x1417c6a60 / 0x1417c6b30
  are ported: `SYNDICATE_D137_OK ... 34 checks`, 6 passes. Cluster 115 bodies.
- The same family continues in `Docs/ASM/1417c69e0.txt` at 0x1417c6bd0 (it starts
  `mov %r9d,%esi`), which the next unit takes next, using the seams that are now in place.

## D138 (latest)

- 0x1417c69e0 ported as the tail call it is: `SYNDICATE_D138_OK ... 7 checks`, 6 passes.
  Cluster 116 bodies.
- Next from `Docs/ASM/1417c69e0.txt`: 0x1417c6bd0 (starts `mov %r9d,%esi`), the third of the
  checked-forwarder family; the assertion seam it needs is already in place.

## D139 (latest)

- 0x1417c6bd0 ported with its dispatch: `SYNDICATE_D139_OK ... 22 checks`, 6 passes.
  Cluster 117 bodies.
- Next from the dump: 0x1417c6c80 / 0x1417c6c90 (the two `jmp *(%rax)` bodies, one after
  `add $0x98,%rcx`) and 0x1417c6ca0 / 0x1417c6ce0, the `setne` comparisons.

## D140 (latest)

- Three bodies: `SYNDICATE_D140_OK ... 15 checks`, 6 passes. Cluster 120 bodies.
- The dump now runs to 0x1417c6dff. Ready and fully captured for the next unit:
  0x1417c6ce0 (setne), 0x1417c6d20, 0x1417c6d30 / 0x1417c6d40, 0x1417c6d50 (thunk to
  0x1417f2fdc), the repeats at 0x1417c6d60 / 0x1417c6d70 / 0x1417c6d80, 0x1417c6d90 /
  0x1417c6da0 / 0x1417c6db0, and 0x1417c6dc0 (the iterator `+0x18` accessor with two DEBUG
  checks).

## D141 (latest)

- Twelve bodies landed in one unit: `SYNDICATE_D141_OK ... 20 checks`, 6 passes under
  ASan+UBSan. Cluster 132 bodies.
- The saved dump ends at 0x1417c6dff, so the next unit starts by extending
  `Docs/ASM/1417c69e0.txt` past 0x1417c6e00 before any line is written.

## D142 (latest)

- Seven bodies: `SYNDICATE_D142_OK ... 17 checks`, 6 passes. Cluster 139 bodies.
- Next in `Docs/ASM/1417c6e00.txt`: 0x1417c6f60 (the keyed search — `mov 0x30(%rcx),%r8` then a
  `cmp %ecx,0x18(%rax)` loop with `jae`, answering `r8`), then the two rebalance steps
  0x1417c6f90 and 0x1417c6ff0.

## D143 (latest)

- The keyed search and the two rotations are in: `SYNDICATE_D143_OK ... 11 checks`, 6 passes.
  Cluster 142 bodies.
- Next in `Docs/ASM/1417c6e00.txt`: 0x1417c7027 onward — the rest of the mirror rotation's third
  link case and whatever follows it, which the captured range already holds.

## D144 (latest)

- Nine bodies: `SYNDICATE_D144_OK ... 5 units`, 6 passes under ASan+UBSan. Cluster 151 bodies.
- Still open from the captured range: 0x1417c7080 (the comparator-driven find-or-add; its
  `0x141823260` comparator is not modelled yet) and 0x1417c71f0, whose third link case is cut
  by the capture at 0x1417c723e — the range must be re-captured before that one is written.

## D145 (latest)

- Six bodies: `SYNDICATE_D145_OK ... 6 units`, 6 passes. Cluster 157 bodies.
- Next: `Docs/ASM/1417c723a.txt` holds 0x1417c723a..0x1417c7600 (236 lines). The wrappers pattern
  (a call to one cluster body, then the argument handed back) continues there, so batch them.

## D146 (latest)

- Sixteen bodies: `SYNDICATE_D146_OK ... 33 checks`, 6 passes. Cluster 173 bodies.
- `Docs/ASM/1417c723a.txt` is now read to its end (0x1417c75fb). Next unit starts by capturing
  past 0x1417c7600.

## D147 (latest)

- Twelve bodies: `SYNDICATE_D147_OK ... 30 checks`, 6 passes. Cluster 185 bodies.
- `Docs/ASM/1417c7600.txt` (196 lines, 0x1417c7600..0x1417c78ff) is read to the cut at
  0x1417c788d. The comparison at 0x1417c7850 is still open because its closing `ret` sits past
  that cut: re-capture 0x1417c7880..0x1417c7920 before writing it.

## D148 (latest)

- Twelve bodies: `SYNDICATE_D148_OK ... 30 checks`, 6 passes. Cluster 197 bodies.
- `Docs/ASM/1417c7830.txt` holds 0x1417c7830..0x1417c7c3f (274 lines) and is read to the cut at
  0x1417c7a5b. The body at 0x1417c7a50 continues past it, so re-capture from there before writing.

## D149 (latest)

- Eight bodies: `SYNDICATE_D149_OK ... 17 checks`, 6 passes. Cluster 205 bodies.
- `Docs/ASM/1417c7a50.txt` holds 0x1417c7a50..0x1417c7e3f (275 lines); the erase body at
  0x1417c7c30 runs past the cut. Re-capture 0x1417c7e30..0x1417c8200 before writing it, and note
  that test binaries under /tmp can outlive a unit: delete them before each build or a stale
  binary prints another unit's success line.

## 0x1417c7c30 — parked, not claimed

- The subtree erase is translated in full (Docs/PENDING/1417c7c30_erase.cpp) but it does not
  return on the first path the test builds, so it is **out of the build** and no unit number is
  claimed for it. `synacc.cpp` still carries the four seams the sentinel path needs.
- Next step on it: run the body against a tree of one node plus the header before anything else,
  and print the (`node`, `cur`, head->0x8) triple at each turn of the fix-up loop, because the
  loop guard is the only unbounded construct in the body.
- Note for the harness: compiling CsyndicateLogicTailSlots.cpp with ASan takes minutes, so build
  its object once and reuse it; a 300 s tool call is not enough for compile + link + six passes.

## D150 (latest)

- 0x1417c7c30 is in and green: `SYNDICATE_D150_OK ... 19 checks`, 6 passes. Cluster 206 bodies.
- Lesson worth keeping: a whole-qword store at a byte offset inside a node wipes the flag byte
  next to it. When a test builds nodes, write colour/flag bytes one at a time.
- Harness: cache `CsyndicateLogicTailSlots.cpp`'s ASan object and reuse it; only rebuild the file
  that changed, then link. Compile + link + six passes then fits in one call.
- Next in `Docs/ASM/1417c7c30.txt`: 0x1417c7ff0 onward (the tail of that capture holds several
  small bodies and the 0x28-byte node builder at 0x1417c8370).

## D151 (latest)

- Five bodies, green six times: `SYNDICATE_D151_OK ... 22 checks`. Cluster 211 bodies.
- Next from `Docs/ASM/1417c7c30.txt`: 0x1417c82e0 (the 0x48-byte node, its tail already captured
  at 0x1417c8352) and 0x1417c8370 (the 0x28-byte node). Then re-capture past 0x1417c8400.

## D152 (latest)

- The two builders are in: `SYNDICATE_D152_OK ... 19 checks`, 6 passes. Cluster 213 bodies.
- Next: the capture `Docs/ASM/1417c7c30.txt` ends at 0x1417c8400, so extend past it before the
  next unit; 0x1417c83f0 was already visible starting a body and stops mid-way.

## D153 (latest)

- Seven bodies: `SYNDICATE_D153_OK ... 25 checks`, 6 passes. Cluster 220 bodies.
- Next in `Docs/ASM/1417c83f0.txt`: 0x1417c8590 (the 0x28 zeroed node) is cut at 0x1417c85e6, so
  extend the capture past 0x1417c8800 before writing it; the rest of that file (271 lines) is
  untouched.

## D154 (latest)

- Five bodies: `SYNDICATE_D154_OK ... 30 checks`, 6 passes. Cluster 225 bodies.
- `Docs/ASM/1417c8590.txt` (322 lines) still holds 0x1417c8740 onward: the copy-then-step family
  with 0x1417c6610, plus the iterator builders and the pair fills that follow, most of them cut
  by the capture's end at 0x1417c8a80. Read that file before starting the next unit.

## D155 (latest)

- Six bodies: `SYNDICATE_D155_OK ... 22 checks`, 6 passes. Cluster 231 bodies.
- `Docs/ASM/1417c8590.txt` still holds 0x1417c8900 onward (the fourth self node and whatever
  follows); read it before the next unit. Note that a `void*` and an `unsigned char*` parameter
  mangle differently — a test declaration that says void* will fail to link against these bodies.

## D156 (latest)

- Three bodies: `SYNDICATE_D156_OK ... 9 checks`, 6 passes. Cluster 234 bodies.
- `Docs/ASM/1417c8a70.txt` (193 lines) is captured: 0x1417c89d0 is the iterator **distance** —
  a loop that increments the counter at `(%rdi)` and steps 0x41-flagged nodes until the two
  iterators name the same node. Its own tail runs past the old capture, so work from the new file.

## D157 (latest)

- The distance is in: `SYNDICATE_D157_OK ... 5 checks`, 6 passes. Cluster 235 bodies.
- Next in `Docs/ASM/1417c8a70.txt`: 0x1417c8aa0 is a checked body (assert at line 0x172 with
  0x14183a778 and 0x141827b98) that then reads `0x38(%rcx)`, `0x8(%rcx)` and compares
  `0x8(%rbp)` — the shape of a range/verify step. Read the file before starting it.

## D158 (latest)

- The matching walk is in: `SYNDICATE_D158_OK ... 12 checks`, 6 passes. Cluster 236 bodies.
- `g_pfnSynCmp3_1418232b0` is new (three-argument comparison, null by default); 0x14178f470 was
  already modelled as `g_pfnLogic_14178f470` with a uint64 signature.
- Next: 0x1417c8c10 in `Docs/ASM/1417c8a70.txt`, the same walk with a count and a 0x60 frame.

## D159 (latest)

- The scored walk is in: `SYNDICATE_D159_OK ... 3 checks`, 6 passes. Cluster 237 bodies.
- `g_pfnSynScore_141798060` is new (element, mode -> int, null by default).
- Next: `Docs/ASM/1417c8a70.txt` ends at 0x1417c8d80 with the scored walk's epilogue, so extend the
  capture past 0x1417c8d80 before the next unit.

## D160 (latest)

- Four bodies: `SYNDICATE_D160_OK ... 12 checks`, 6 passes. Cluster 241 bodies.
- Next in `Docs/ASM/1417c8d80.txt`: 0x1417c8f70 is a keyed lower/upper pair that also asserts on its
  own lead (`cmp %rax,%rax`), and its tail runs beyond the capture's end at 0x1417c9200 — extend
  the capture before writing it.

## D161 (latest)

- The leaf generator works: `tools/family_gen.py` -> `modules/syndicate/src/genleaf.cpp`, 644 bodies,
  `SYNDICATE_D161_OK ... 644 checked`, 6 passes. `Docs/TPL_FAMILIES.md` carries the family plan.
- Rule to keep: a generated body must be the *whole* function and must avoid `(%rip)` operands.
- Next: the destructor and allocator families in the same generated form, then the NpcServer scaffold.

## D162 (latest)

- 832 generated bodies, `SYNDICATE_D162` covered by `SYNDICATE_D161_OK ... 832 checked`, 6 passes.
- `tools/family_gen.py` now emits the whole unit; never hand edit `genleaf.cpp`.
- Next: the destructor and allocator families (need the `operator delete` / `operator new` seams),
  then the NpcServer.exe scaffold over its 50 embedded paths.

## D163 (latest)

- NpcServer.exe scaffolded: 56 paths from the binary (corrected in D228; was 50), `Docs/NPCSERVER_PATHS.md`, no bodies yet.
- The work order is now written down in `Docs/REMAINING_ROADMAP.md`; `npckernel` is 34 of the 50.

## D164 (latest)

- Slot family in place: 126 thunks, 126 seams, `SYNDICATE_D161_OK ... 832 checked`, 6 passes.
- D162's "forwarders" were slot thunks; the label is corrected in PORTING_LOG and TPL_FAMILIES.
- `Docs/SEAMS.md` is the new map: 99 slots / 7,238 sites, 2,340 direct targets / 13,703 sites.
- Next: the destructor and allocator families need the vtable symbols (`tools/read_vtable_slots.py`,
  `Docs/SYNDICATE_CLASS_MAP.md`), then the NpcServer `npckernel` unit 1.

## D165 (latest)

- NpcServer.exe first unit landed: 8 bodies, `NPCSERVER_D165_OK`, 6 passes.
- Corpus: 832 generated Syndicate bodies + 241 hand bodies + 8 NpcServer bodies.
- Next: continue NpcServer by address (0x140001280 onwards) and pick up the WSAStartup body
  0x140001130, whose tail was cut in the listing — read the full body before porting it.

## D166 (latest)

- NpcServer now has 14 bodies ported (0x140001020 .. 0x140001440), `NPCSERVER_D166_OK`, 6 passes.
- Note for the next unit: 0x1400012a0's in-place shift is a forward byte loop in the port, because the
  original memcpy range overlaps.
- Next: continue by address from 0x1400014b0, and attribute bodies to their `__FILE__` paths as soon
  as a path shows up in the image.

## D167 (latest)

- Rule now enforced: no path, file name or symbol is invented. Unattributed bodies live in
  `modules/npcserver/unattributed/` (outside `src/`), symbols keep the decompiler's `FUN_<address>`.
- Evidence limits written down: the 49 path strings are unreferenced dead data, so per-TU
  attribution is unavailable from the image. `Docs/NPCSERVER_PATHS.md` says so in its note.
- Next: continue by address from 0x1400014b0; when a body's class comes from the name index, record
  the index row in PORTING_LOG and still place the body by evidence only.

## D168 (latest)

- NpcServer: 16 bodies ported (0x140001020 .. 0x140001520). `NPCSERVER_D168_OK`, 6 passes, and the
  earlier two suites re-run clean against the same object.
- Next: continue by address from 0x1400016xx, same rules (decompiler names, no invented paths).

## D169 (latest)

- NpcServer: 17 bodies. The first one is now placed by evidence into
  `src/version/cqserver-78.0.11-1204/npcserver/clientsocket.cpp` because the body prints that path in
  its own assert call. D165, D166, D168, D169 all pass 6 times.
- Every seam is registered in one place; the log seam is variadic to carry the assert form.
- Next: 0x140001990 and onward; any body whose assert text names a path joins that exact path.

## D170 (latest)

- NpcServer: 25 bodies across 0x140001020 .. 0x140001ba0. Two now sit in their original path
  (`npckernel` D165..D170 helpers stay in `unattributed/`; clientsocket bodies in
  `src/version/cqserver-78.0.11-1204/npcserver/clientsocket.cpp`).
- All five suites pass 6 times (D165, D166, D168, D169, D170).
- Next: 0x140001c00 onward. Watch for bodies whose assert text names a new path; those move into
  that exact path.

## D171 (latest)

- NpcServer: 35 bodies, 0x140001020 .. 0x140001fd0. Six suites green 6x each.
- New seams: `operator_new`, `operator_new__`, `FUN_140005b70`, `FUN_14000c370`, `FUN_140005c30`.
- Next: 0x1400020c0 onward.

## D172 (latest)

- NpcServer: 61 bodies, 0x140001020 .. 0x140002630. Seven suites green 6x each.
- The thread class work is now grounded: object at +8 / +0x50 / +0x68 each carry their table in the
  first word, and the slots are reached through that word.
- Next: 0x1400026xx onward.

## D173 (latest)

- NpcServer: 64 bodies, 0x140001020 .. 0x140002790. Eight suites green.
- `0x1400027f0` is next and it is large (0x500-byte frame, `CTickAnalyst` temporaries), so it gets its
  own unit with its full body read first.

## D174 (latest)

- NpcServer: 65 bodies. Suites D165 to D174 all green.
- Log thread is now started: `CLogThread` ctor at 0x140002d70 with the table at 0x1400bed00.
- Blocker on the sequence: 0x1400027f0 (`OnProcess`) and 0x140002b30 (thread launcher) need the packet
  header that receive slot +0x48 fills (type 0x1fbd1/0x1fbd2, fd at word 0, 0x418 bound) and the
  CTickAnalyst scope pair. Model those two seams first, then both bodies can be written verbatim.

## D175 (latest)

- NpcServer: 66 bodies, 0x140001020 .. 0x140002d70 with 0x1400027f0 now included. Ten suites green.
- The packet header is modelled from the stack: two ints, the second is the type (0x1fbd1 / 0x1fbd2),
  and the body buffer is 0x418 with the fd in its first eight bytes.
- Next: 0x140002b30 (thread launcher, `_SYSTEM_INFO`) now that the same objects are understood.

## D176 (latest)

- NpcServer: 67 bodies. Suites D165 to D176 all green.
- `CKernelThread::Create` is in with fifteen null-checked seams for the libevent layer
  (`0x140012580`, `0x140010a00`, `0x140010a20`, `0x140015ed0`, `0x140012660`, `0x140010d80`, `0x14001d350`,
  `0x140005750`) and the thread API (`_beginthreadex`, `GetThreadId`, `GetCurrentThreadId`, `_errno`,
  `CThreadBase::CreateThread`, `GetSystemInfo`).
- Next: those eight libevent bodies in `0x140005750`..`0x140016xxx` are now the critical path, because
  every remaining thread body leans on them.

## D177 (latest)

- NpcServer: 68 bodies. Suites D165 to D177 all green.
- The libevent layer has started: 0x140005750 registers the eight handlers at 0x140005400..0x1400055f0.
- Next in that layer: the two registrar bodies it calls (0x140016890, 0x140016880, 0x140016990) and the
  eight handlers themselves, which are the ones that actually touch `event_base`.

## D178 (latest)

- NpcServer: 71 bodies. Suites D165 to D178 all green.
- The thread-callback half of the libevent layer is done: 0x140016880, 0x140016890, 0x140016990.
- Next: the eight handlers 0x140005400..0x1400055f0 that 0x140005750 registers, then 0x140012580 /
  0x140010a00 / 0x140010a20 / 0x140015ed0 (the event-config and event-base wrappers).

## D179 (latest)

- NpcServer: 79 bodies. Suites D165 to D179 all green.
- The registered handlers are ported and wired: the lock and condition shims with spin count 2000.
- Next in the layer: 0x140012580 (event_config_new), 0x140010a00, 0x140010a20, 0x140015ed0 (event_base_new),
  0x140012660, 0x140010d80, 0x14001d350, then 0x1400121b0 and 0x140016450 which the callbacks already call.

## D180 (latest)

- NpcServer: 84 bodies. Suites D165 to D180 all green.
- event_config is understood end to end: the five fields, the tail pointer that points at the head, and the
  flag word at +0x28 that the base copies to +0x1f8.
- Next: 0x140012660 (event_config_free, needs the disassembly for its entry list) and 0x140015ed0
  (event_base_new_with_config, 925 bytes). Then rewire 0x140002b30 and the other seam users to these real
  bodies.

## D181 (latest)

- NpcServer: 85 bodies. Suites D165 to D181 all green.
- The event_config family is complete: new (0x140012580), free (0x140012660), set_flag (0x140010a00),
  set_num_cpus_hint (0x140010a20). The hooks are DAT_140103f98 (allocate) and DAT_140103fa8 (release).
- Next: 0x140015ed0 event_base_new_with_config, 925 bytes, the largest body left in this layer. Its field map
  is already partly known from D180 (config flags land at base +0x1f8, the interval at +0x1fc, the callback
  limit at +0x204).

## D182 (latest)

- NpcServer: 86 bodies. Suites D165 to D182 all green.
- The libevent bootstrap is now complete end to end: config new/free/set_flag/set_num_cpus_hint,
  thread-callback registrars, the eight threading handlers, and event_base_new_with_config.
- Next: the remaining seams of 0x140015ed0 (0x140016640, 0x1400105b0, 0x14001a010/190, 0x14001ad50,
  0x140010860, 0x1400127e0, 0x140016f00/df0/e70, 0x140015e70, 0x140074b80, 0x140014b30) and then rewiring
  0x140002b30 to the real bodies instead of its seams.

## D183 (latest)

- NpcServer: 96 bodies. Suites D165 to D183 all green.
- D182's seams are now mostly real bodies. Still seams inside 0x140015ed0: 0x1400127e0 (302),
  0x140074b80 (346) and 0x140014b30 (867), plus 0x140016720 / 0x1400163c0 / 0x1400165d0 which the new
  timer code calls.
- Next: those three larger ones, then rewire 0x140002b30 and 0x140015ed0 to call the real bodies directly.

## D184 (latest)

- NpcServer: 100 bodies. Suites D165 to D184 all green.
- Remaining seams: 0x140074b80 (346, IOCP launch) and 0x140014b30 (867, event_base_free).
- Then the payoff step: rewire 0x140002b30 (CKernelThread::Create) and 0x140015ed0 to call these real bodies
  instead of their seams.

## D185 (latest)

- NpcServer: 101 bodies. Suites D165 to D185 all green.
- One seam left in the base layer: 0x140014b30 (867, event_base_free).
- Then rewire 0x140002b30 and 0x140015ed0 onto the real bodies and drop the duplicate seams.

## D186 (latest)

- NpcServer: 102 bodies. Suites D165 to D186 all green.
- The libevent bootstrap layer is now complete: no seam remains inside 0x140015ed0 or 0x140014b30.
- Next: rewire 0x140002b30 (CKernelThread::Create) and 0x140015ed0 onto these real bodies and delete the
  duplicate seams they replace, then continue with the next cluster after 0x140074b80.

## D187 (latest)

- NpcServer: 102 bodies, 21 suites. 0x140015ed0 is fully wired to real bodies, no seams left inside it.
- Next: the same treatment for 0x140002b30 (CKernelThread::Create), then continue the port after
  0x140074b80 (the IOCP backend, 0x140074780 onwards).

## D188 (latest)

- NpcServer: 104 bodies, 22 suites. The IOCP cluster now has its worker and its shutdown.
- Left in that cluster: 0x140074930 (the winsock extension resolution, 568 bytes) - it needs its WSAIoctl
  argument list read out of the disassembly before it can be written, since the decompiler truncated the
  call.
- After it: 0x140002b30 can be rewired onto the real bodies (its eight callees are all ported now).

## D189 (latest)

- NpcServer: 105 bodies, 23 suites. The IOCP cluster is complete; 0x140074930 is the last seam it had.
- Next: rewire 0x140002b30 onto its eight real callees (all ported) and point 0x140074b80 at the real
  0x140074930, adjusting suites D176 and D185 in the same commit.

## D190 (latest)

- 105 bodies, 23 suites green. 0x140074b80 -> real 0x140074930.
- Next: 0x140002b30 onto its eight ported callees (needs suite D176 rewritten to drive real internals:
  0x140012580/0x140010a00/0x140010a20/0x140010d80/0x140012660/0x14001d350/0x140005750/0x140015ed0).

## D191 (latest)

- 105 bodies, 23 suites green. NpcServer's thread create path is entirely on real bodies.
- Next cluster: continue after 0x140074b80 in address order (0x140074d90/0x140074930 are done; the next
  entries are the 0x140075000 region), and keep an eye out for other unaligned `long long` field moves of
  the kind fixed here.

## D192 (latest)

- NpcServer: 110 bodies, 24 suites. The notification queue pair is ported with its append/withdraw rules.
- Next: 0x1400750d0 (the 0x38 queue object with five 0x108 buffers and 0x14001b590), whose failure path
  needs the rest of its body read, then 0x140075210 onward.

## D194 (latest)

- NpcServer: 113 bodies, 26 suites. The notification mechanism (queue object plus its hand-over and withdraw
  pair) is ported.
- Next: 0x140075480 (700 bytes, the largest left in this cluster), then 0x140075740 onward.

## D195 (latest)

- NpcServer: 114 bodies, 27 suites green. The poll cycle is ported; the notification cluster's backbone is done.
- Next: 0x140075740, 0x1400757e0, 0x140075840, 0x140075950, 0x140075a00 continuing in address order.

## D196 (latest)

- NpcServer: 117 bodies, 28 suites green.
- Next: 0x140075950 (173), 0x140075a00 (71), 0x140075a50 (471) in address order.

## D197 (latest)

- NpcServer: 120 bodies, 29 suites green.
- Next: 0x140075c30 (547), 0x140075e60 (24), 0x140075e80 (99) in address order.

## D198 (latest)

- NpcServer: 123 bodies, 30 suites green. Both directions of the buffer object are now ported.
- Next: 0x140075ef0 (21), 0x140075f10 (71), 0x140075f60 (545), 0x140076190 (391).

## D199 (latest)

- NpcServer: 126 bodies, 31 suites green.
- Next: 0x140076190 (391), 0x140076320/0x140076350/0x140076380 (34 each), then 0x1400763b0 onward.

## D200 (latest)

- NpcServer: 130 bodies, 32 suites green.
- Next: 0x1400763b0 and 0x140076450 (145 each), 0x1400764f0 and 0x1400765b0 (181 each).

## D201 (latest)

- NpcServer: 134 bodies, 33 suites green.
- The thunk return type is a general lesson: any `FUN_` the decompiler shows as `void` that is called as a tail
  call in another function carries a value back. 0x140076320/350/380 are now typed that way.
- Next: 0x140076670 and 0x1400766c0 (61 each), 0x140076710 and 0x140076750 (43 each), then 0x140076790.

## D202 (latest)

- NpcServer: 138 bodies, 34 suites green.
- Next: 0x140076790 (370), 0x140076910 (385), 0x140076aa0 (295).

## D203 (latest)

- NpcServer: 141 bodies, 35 suites green.
- Lesson worth re-checking in every vtable port: a call through a slot needs `*(T (**)(...))(pBase + off)`, two
  stars. One star calls the slot's address (vtable memory) and shows up as a jump to a stack or data address.
- Next: 0x140076be0 and 0x140076c40 (77 each), then 0x140076ca0 (385).

## D204 (latest)

- NpcServer: 145 bodies, 36 suites green.
- Next: 0x140076f60 onward in address order. Re-check every forwarder's return type at the call site: three of
  them in this cluster were tail calls the decompiler labelled void.

## D205 (latest)

- NpcServer: 154 bodies, 37 suites green.
- Pending rewiring pass for the protobuf-target cluster. These seams now have real bodies behind them:
  0x140077370 (still a seam, not yet ported), 0x1400774a0, 0x1400774e0, 0x140077520, 0x140077840, 0x140077850,
  0x1400778a0, 0x140077900. Call sites to rewire: 0x140075a50, 0x140075c30, 0x140076790, 0x140076aa0,
  0x140076e30, 0x1400763b0/450/4f0/5b0 and the three thunks.
- Next: 0x140076f80 (398), 0x140077120 (164), 0x1400771d0 and 0x140077280 (161 each).

## D206 (latest)

- NpcServer: 159 bodies, 38 suites green.
- Dead branch worth knowing: the `clear()` in 0x1400771d0/0x140077280 can never run, because 0x140076ca0 and
  0x140076e30 answer 1 in the low byte or abort.
- Next: 0x140077370 (294 - which would let the three thunks be rewired), 0x140077530 (227), 0x140077620 (157).

## D207 (latest)

- NpcServer: 162 bodies, 39 suites green.
- The three thunks 0x140076320/350/380 can now be rewired: 0x140077370, 0x1400774a0 and 0x1400774e0 all have real
  bodies. That is part of the pending rewiring pass noted under D205.
- Next: 0x1400776c0 (223), 0x1400777a0 (157), 0x1400778c0 (55).

## D208 (latest)

- NpcServer: 165 bodies, 40 suites green.
- Next: 0x140077930 (35), 0x140077370's neighbours done; then 0x1400778c0's callers and 0x14007a700 (the wrapper
  destroy) so the pending rewiring pass can close.

## D209 (latest)

- NpcServer: 170 bodies, 41 suites green.
- The wrapper destroy `0x14007a700` and the data unwrap chain are now real. The pending rewiring pass can start:
  seams whose bodies now exist — 0x140077370, 0x1400774a0, 0x1400774e0, 0x140077520, 0x140077530, 0x140077620,
  0x1400776c0, 0x1400777a0, 0x140077840, 0x140077850, 0x1400778a0, 0x1400778c0, 0x140077900, 0x140077930,
  0x14007a700.

## D210 (latest)

- NpcServer: 173 bodies, 42 suites green. The coded-input cluster is complete.
- Next: the rewiring pass listed under D209, or 0x140077ff0 / 0x140078030 / 0x1400783d0 (log helpers) to close the
  logging seams.

## D211 (latest)

- NpcServer: 180 bodies, 43 suites green. The logging layer now has real bodies; its seams stay until the rewiring
  pass, which is the next unit.

## D212 (latest)

- Rewiring pass 1 done: the six log seams are removed, 27 call sites are direct, and the affected suites (D199,
  D203, D204, D207, D209) observe end to end at the log sink. All 43 suites green, the five rewritten ones six times.
- Still on the pending rewiring list: 140077370, 1400774a0, 1400774e0, 140077520, 140077530, 140077620, 1400776c0,
  1400777a0, 140077840, 140077850, 1400778a0, 1400778c0, 140077900, 140077930, 14007a700, 14007a830, 14007a8e0,
  14007a9c0, and the libevent group 1400163c0/1400165d0/140016720/140016880/140016890/140016990/140074d90.

## D213 (latest)

- NpcServer: 185 bodies, 44 suites green. The logging layer is complete except 0x140078b30/0x1400787c0/0x1400787f0,
  which are still seams.
- Rewiring pass 2 (the tree/queue cluster) was started and rolled back: 13 suites substitute those seams for
  infrastructure, not just observation, so the pass needs its suites rebuilt one at a time. Nothing is left red.

## D214 (latest)

- Rewiring pass 2, slice 1 done: 140077900, 140077930, 1400778c0 rewired; D204/D205/D206 rebuilt against real state.
  44 suites green, the three rebuilt ones six times.
- Next slice: 140077840, 140077850, 1400778a0 (readers used by 0x140076790 and 0x140076aa0). A first attempt showed the
  target's fields must exist for the real 140077850, so D203/D204 need their targets filled before that group moves.

## D215 (latest)

- Rewiring pass 2, slice 2 done: 140077840, 140077850, 1400778a0 rewired. D203 and D204 rebuilt around real coded
  outputs (buffer/room/cursor inside the wrapper, read at teardown). 44 suites green, the rebuilt ones six times.
- Next slice: 140077520/140077530 (wrapper validity and construction), then 140077370/1400774a0/1400774e0.

## D216 (latest)

- Rewiring pass 2, slice 3 done: 140077530/140077520 rewired, D201 rebuilt. 44 suites green, six cycles on the
  six suites around the wrappers.
- Next slice: 140077370 / 1400774a0 / 1400774e0, then 140077620/1400776c0/1400777a0.

## D217 (latest)

- 140077620 / 1400777a0 / 1400776c0 rewired; D202 and D207 now watch real wrappers. 44 suites green, both six times.
- `rewire_seams.py` is in the conversation's tools_local. Next: a830/a8e0/a9c0 (blocked on suites that need a real
  coded input: vtable slot +0x10, state at +0x18/+0x1c/+0x28/+0x2c), then 774a0/774e0, then the log pair.

## D218 (latest)

- 1400774a0 / 1400774e0 rewired; D200 and D201 now drive a real object with slots at +0x18 and +0x38. 44 suites
  green, four of them six times.
- Next: the coded-input helpers a830/a8e0/a9c0 (each suite needs a real coded input: vtable +0x10, state at
  +0x18/+0x1c/+0x28/+0x2c), then the log layer pair, then 160880/160890.

## D219 (latest)

- 140016880 / 140016890 rewired; D177 reads the real registry tables. 44 suites green, both six times.
- Next: a830/a8e0/a9c0, then the log layer (77f50/77fc0/78d20/78d60), then 16990.

## D220 (latest)

- 14007a8e0 / 14007a9c0 rewired; D201 drives the real limit rules. 44 suites green, three of them six times.
- Next: a830 (needs a coded input with a vtable slot at +0x10), then the log layer (77f50/77fc0/78d20/78d60).

## D222 (latest)

- 14007a830 rewired, and one missing indirection fixed in its sink call. 44 suites green, three of them six times.
- Next: the log layer (77f50/77fc0/78d20/78d60), then 16990, then the coded-input cluster around a8e0/a9c0 is done.

## D223 (latest)

- 140077fc0 / 140078d20 / 140078d60 rewired; D211 observes the layer below. 44 suites green, two of them six times.
- Next: 140016990 (the condition twin), then 140078b30 / 1400787c0 / 1400787f0 to close the log layer.

## D224 (latest)

- 140016990 rewired; D177 reads the lock and condition tables directly. 44 suites green, two of them six times.
- Next: 140078b30 (the one-time initialiser that takes a callback) to close the log layer.

## D225 (latest)

- Once-init cluster ported and 0x140077fc0 calls it directly: the log layer is closed end to end.
- 45 suites green, the whole set run six times. Next: the remaining coded-stream seams (0x14007c650 pending count,
  0x14007c9xx) and then back to the 0x14008xxxx range.

## D226 (latest)

- Coded-input bounds ported; the 0x14007a8xx/0x14007c6xx slice has no seams left. 46 suites, six clean cycles.
- Next: back into the 0x14008xxxx range for the next unported cluster.

## D227 (latest)

- 86 container-internal bodies of 0x140080000..0x140090000 ported by `tools/gen_stl_family.py`, with a manifest
  (`g_aNpcStl_140080000`) and a walk suite, D227. 47 suites, six cycles, one command: `tools/run_npcserver_suites.sh`.
- 305 bodies left in the range; the shapes to take next are listed at the end of PORTING_LOG.md.

## D228 (latest)

- `modules/npcserver/src` rebuilt from the image's own `strings`: 56 `__FILE__` paths, not 50. `src/` now holds
  `cq/` (the six protobuf translation units, which the old table had mis-pathed under `google/`) and `version/`.
  `version/.../protobuf/msgwalk.pb.cc` added. `tools/check_npcserver_paths.py`: 56 listed, 56 present, no invented
  folder.

## D229 (latest)

- 23 more bodies of 0x140080000..0x140090000: 15 forwarding wrappers and 8 pair constructs, generated by
  `tools/gen_stl_iterators.py` into `stl-iterators.{h,cpp}` with manifest `g_aNpcIter_140080000`.
- Runner is now one command: `tools/run_npcserver_suites.sh` (48 suites, six cycles, sanitizers on).
- Next shapes in the range: `vector::insert` bounds (6 + 5), aligned allocate (4), `memmove_s` move (4).

## D230 (latest)

- 30 bodies of 0x140080000..0x140090000: 12 alloc-raw, 4 memmove-forward, 6 iterator-bounds, 8 position-build, in
  `stl-shapes.{h,cpp}` with manifest `g_aNpcShape_140080000`.
- 49 suites green, six cycles, `tools/run_npcserver_suites.sh`.
- Next in the range: the `vector<T> too long` throwers, the reference-count assign/release pair, and the
  `operator_delete` cleanup wrappers.

## D231 (latest)

- 16 bodies of 0x140080000..0x140090000: 4 ref-assign, 4 ref-copy, 1 ref-release, 7 length-error throwers, in
  `stl-refs.{h,cpp}` with manifest `g_aNpcRef_140080000`.
- 50 suites green, six cycles, `tools/run_npcserver_suites.sh`.
- Remaining in the range: 375 bodies, led by the `operator_delete` cleanup wrappers and the remaining
  iterator/position builders.

## D232 (latest)

- 12 bodies: move-backward, clear-or-drop, ref-fill, position-member (three each) in `stl-tail.{h,cpp}`.
- 51 suites green, six cycles.
- The STL-internals cluster is now down to 224 unmatched bodies in a very long tail (largest remaining group is 2),
  so the generator route is exhausted here. Recommendation for the next batch: leave the remainder alone for now and
  return to the module surface past 0x140090000, or port the tail by hand, two or three per batch.

## D233 (latest)

- 226 bodies across the whole image: 88 node-push, 86 delete-holder, 52 move-forward, in `stl-global.{h,cpp}`
  with manifest `g_aNpcGlobal`. Total ported: 393 of 4099 bodies.
- 52 suites green, six cycles.
- Next by mass: the logging stubs `log_InlineLogERROR(&DAT_x); return 0/void;` (141 bodies). They need the static
  descriptor layout (file/line/severity) read out of the image first, so that is its own batch.

## D234 (latest)

- 134 fixed-argument log stubs in `log-stubs.{h,cpp}`: `MYASSERT("PURE_VIRTUAL_FUNCTION")` with each body's own file
  and line, extracted from the machine code (rcx=file, rdx=expression, r8=kind, r9=format, stack=line).
- 53 suites green, six cycles. Total ported: 527 of 4099 bodies.
- Follow-up: the six log bodies already in `front-of-image.cpp` pass a format pointer as the first argument; the bytes
  say the first register is the source file. Reconcile them when that file is next touched.
- Next by mass: the remaining 54 log bodies (variants with a saved register or a forwarding shape) and the `x21`
  shapes in the 0x14008 window.

## D235 (latest)

- 6 member getters with a CHECKF log in `log-getters.{h,cpp}`; log arguments taken from the bytes, not the decompiler.
- 54 suites green, six cycles. Total ported: 533 of 4099 bodies.
- The remaining 116 log-bearing bodies are not stubs: they are real functions with a log on a failure path (vtable
  guards, arity checks, jump tables). They belong to their module batches, not to an extraction pass.

## D236 (latest)

- 17 bodies in `container-bodies.{h,cpp}`: 3 vtable stores, 3 deleting destructors, 1 vtable release,
  9 protected iterator comparisons, 1 member address (`+0x28`).
- 55 suites green, six cycles. Total ported: 550 of 4099 bodies.
- The parse gap: the true addresses of `ISingleMap<INpc>`, `IGameObjSet<IGenerator>` and `IGameObjSet<CNpcType>`
  vtables are now on record, which is what the interface classes' own batches will need.

## D237 (latest)

- 10 bodies in `container-nodes.{h,cpp}`: 4 node builders, 2 erase-then-free destructors, 4 deleters.
  The seams `g_pfnNpc_140022a40`, `_140022af0`, `_140023df0`, `_1400243b0` are owned by that file until their bodies land.
- 56 suites green, six cycles. Total ported: 560 of 4099 bodies.
- Next in this cluster: `0x140023df0` / `0x1400243b0` (the RB-tree erase loops) and `0x140022a40` / `0x140022af0`
  (the sentinel allocators), which retire four seams at once.

## D238 (latest)

- 6 bodies in `map-tree.{h,cpp}`: 2 sentinel-head allocators (now returning their block, as the bytes do), 2 recursive
  subtree frees, 2 tree clears.
- Two seams retired: `g_pfnNpc_140022a40` / `_140022af0` are gone and `container-nodes.cpp` calls the real bodies.
- 57 suites green, six cycles. Total ported: 566 of 4099 bodies.
- Still seams: `0x140023df0`, `0x1400243b0` (need `0x140022e50` / `0x140023400`, the erase-with-throw pair).

## D239 (latest)

- 6 bodies in `vector-accessors.{h,cpp}`: 2 position readers, 2 steppers (8 and 4 bytes), 2 tail readers (+0x18).
- 58 suites green, six cycles. Total ported: 572 of 4099 bodies.
- Next in the cluster: the erase-with-throw pair `0x140022e50` / `0x140023400` (~120 lines each, they need the
  successor `0x140021f50` and the two rotations `0x140021e60` / `0x140021ec0`), then the two erase loops that wait on them.

## D240 (latest)

- 3 bodies in `tree-links.{h,cpp}`: the successor step and the two rotations. Node shape used: left +0, parent +8,
  right +0x10, colour +0x28, nil flag +0x29; the head is at tree + 0x30 and the root at head + 8.
- 59 suites green, six cycles. Total ported: 575 of 4099 bodies.
- Everything the erase-with-throw pair needs is now in place: next is `0x140022e50` (then `0x140023400`, its twin),
  which retires the last two seams in `container-nodes.cpp`, and after them `0x140023df0` / `0x1400243b0`.

## D241 (latest)

- 5 bodies in `tree-erase.{h,cpp}`: both erase-with-iterator bodies (`0x140022e50`, `0x140023400`) and the three
  helpers the second one calls (`0x140021fe0`, `0x140021d50`, `0x140021db0`).
- `g_pfnNpcThrowOutOfRange` is the only new seam; it throws `std::out_of_range("invalid map/set<T> iterator")`.
- 60 suites green, six cycles. Total ported: 580 of 4099 bodies.
- Next: `0x140023df0` / `0x1400243b0`, the two erase loops that call these bodies, which retires the last seams in
  `container-nodes.cpp`, then the rest of the 0x140024xxx cluster.

## D242 (latest)

- 2 bodies in `tree-erase-range.{h,cpp}`: `0x140023df0` and `0x1400243b0`, the range erases with the whole-tree
  shortcut into the clear.
- Corrected `0x140024340` / `0x140024d70` in `container-nodes.cpp`: the first iterator is `{owner, leftmost}` and the
  last is `{owner, head}`, so those destructors take the clear shortcut. The old port read `pSet[0]` for both nodes.
- Seams gone from `container-nodes.cpp` (`g_pfnNpc_140023df0`, `g_pfnNpc_1400243b0`); D237's destructor cases were
  rebuilt on a real empty tree.
- 61 suites green, six cycles. Total ported: 582 of 4099 bodies.
- Next: the rest of the 0x140024xxx cluster (`0x140025210` and the containers above it), then the 0x140026xxx tails.

## D243 (latest)

- 4 bodies in `cinstance.{h,cpp}`: `0x140049050`, `0x140049070`, `0x140048f90`, `0x1400491b0`.
- `CInstance::vftable` resolved to `0x1400c7340` from the `lea` inside `0x1400491b0` (the RTTI record is unreferenced, so
  the index could not supply it).
- New seams: `g_pfnNpc_14001c790`, `g_pfnNpc_14003cc10`, `g_pfnNpc_140048fb0`.
- 62 suites green, six cycles. Total ported: 586 of 4099 bodies.
- Next: `0x140048fb0` (the map bring-up, needs `0x14003cd80`), then `0x140024fe0` / `0x140024970` / `0x140024b20`, and
  after them `0x1400250e0` / `0x140025690` / `0x140025750` become stitchable.

## D244 (latest)

- `0x140048fb0` ported into the same `cinstance` manifest (now five bodies); `0x1400491b0` calls it directly and the
  seam `g_pfnNpc_140048fb0` is gone. New seam: `g_pfnNpc_14003cd80`.
- 62 suites green, six cycles. Total ported: 587 of 4099 bodies.
- Next: `0x14003cd80`, then `0x140024fe0` / `0x140024970` / `0x140024b20`; after those the `0x140025xxx` containers
  (`0x1400250e0`, `0x140025690`, `0x140025750`) have no missing callees left.

## D245 (latest)

- `0x14003cd80` in `cmapmanager-instance.{h,cpp}`: the map-instance factory, with four seams for its callees
  (`0x14003ca10`, `0x1400550f0`, `0x14001c7a0`, `0x140032e20`).
- `Docs/WORKING_METHOD.md` added: the full working method in Arabic, written for a fresh agent on another account.
- 63 suites green, six cycles. Total ported: 588 of 4099 bodies.
- Next: `0x140024fe0` / `0x140024970` / `0x140024b20`, then `0x1400250e0` / `0x140025690` / `0x140025750`.

## D246 (latest)

- `0x140024970`, `0x140024b20`, `0x140024fe0` in `map-insert-erase.{h,cpp}`: hinted insert, counted range erase, and
  the key lookup. Seams: `g_pfnNpc_140024000`, `g_pfnNpc_140023290`.
- Iterator pairs are declared as arrays now; separate locals broke the callee's two-slot layout (see PORTING_LOG).
- 64 suites green, six cycles. Total ported: 591 of 4099 bodies.
- Next: `0x140024000` (the insert core, needs `0x140024970`'s caller shape) and `0x140023290` (the range lookup), then
  `0x1400250e0` / `0x140025690` / `0x140025750` close out with no missing callees.

## D247 (latest)

- `0x140023290` ported into the same manifest: the equal range, no seams.
- 64 suites green, six cycles. Total ported: 592 of 4099 bodies.
- Next: `0x140024000` — the insert core with the rebalance (the big one, ~600 lines including the length_error throw).
  After it the `0x140024970` seam goes away, and `0x1400250e0` / `0x140025690` / `0x140025750` close out clean.

## D248 (latest)

- New reference: `Docs/reference/NpcServer_Ghidra/` (class-level Ghidra dump of the same image) + `tools/build_name_map.py`
  → `Docs/FUN_NAME_MAP.tsv` (7053 functions, 3479 named) and `Docs/VTABLE_SLOTS.tsv` (1079 slots); how-to in
  `Docs/NAME_CROSSWALK.md`.
- 4 bodies in `module-singletons.{h,cpp}` (`0x14001c790`, `0x14001c7a0`, `0x14001c7b0`, `0x14001c7f0`); the first two
  retire seams in the CInstance and CMapManager files.
- 65 suites green, six cycles. Total ported: 596 of 4099 bodies.
- Next: `0x14003ca10` (CMapManager::FindMap — needs the `InstanceGet` thunk from `objdump`, the decompile marks it
  unrecoverable) and `0x140024000` (the insert core with rebalance).

## D249 (latest)

- `0x14003ca10` (CMapManager::FindMap) and `0x14001c200` (module base) ported; the `g_pfnNpc_14003ca10` seam is retired
  and only `g_pfnNpcInstanceGet` remains for that family (an import thunk: `jmp *0x1400bd190`).
- 65 suites green, six cycles. Total ported: 598 of 4099 bodies.
- Next: `0x140024000` (the insert core with the rebalance and the `map/set<T> too long` length_error) — it owns two seams
  today (`0x140024970` and the hint path) and is the last big body of the 0x14002xxxx cluster.

## D250 (latest)

- `0x1400228f0` (node builder) and `0x140024000` (insert + red-black repair) in `tree-insert.{h,cpp}`; the
  `g_pfnNpc_140024000` seam is retired and `0x140024970` now inserts for real.
- 66 suites green, six cycles. Total ported: 600 of 4099 bodies.
- Next: the `0x140025xxx` container family (`0x1400250e0`, `0x140025690`, `0x140025750`, `0x140025340`) now has no
  missing callee, then `0x14003ca10`'s neighbours and the `0x140026xxx` vtables.

## D251 (latest)

- `0x1400250e0`, `0x140025690`, `0x140025750` in `cinstancemgr.{h,cpp}`; the `g_pfnNpc_140023290` seam is retired too.
- CInstanceMgr keeps two maps: records at `+8` (head `+0x38`) and live instances at `+0x48` (head `+0x78`).
- 67 suites green, six cycles. Total ported: 603 of 4099 bodies.
- Next: `0x140025340` (the CInstanceMgr constructor/clear, 153 lines) and the rest of `0x140025xxx`, then `0x140026xxx`.

## D273 (latest)

- `Docs/MODULE_RTTI.md`: image has 125 RTTI classes, table covers them; package DLLs add 1,030 unrelated classes.
- `::vftable` rejections are module-boundary (`std::` exceptions from msvcp90), not missing rows. Not fixable here.
- ws2_32 ordinals (1..116 gap-toothed) cannot be mapped honestly: the package ships no ws2_32/mfc90/oleaut32.

## D272

- The v6159 archive is a **server package with no C++ source** (0 code files); porting stays transliteration-based.
- `Docs/NPCSERVER_EXPORT_MAP.tsv`: 467 imports joined to real export tables (273 named / 194 ordinal).
- The 194 ordinals are system libs: mfc90 165, ws2_32 25, oleaut32 1; the 3 zlibwapi ones resolved by name.
- `Docs/CO_MODULE_EXPORTS.md`: CQBase 306 exports (tq::TimeGet @0x140b82df0, SysTimeGet @0x140b87940,
  IsTimeRange @0x140b877d0, DateTime @0x140b878c0), DB 36, Analyst 12, zlibwapi 160.
- Decision: `tq::` entry points stay seam hooks; their bodies belong to another module.

## D271 (corrected)

- Loader merge of `_unnamed_*.cpp` reverted: it gained nothing and it is what broke the build in `a2f5eca`.
- `basic_string` (unqualified in the listing) is rejected rather than given an invented type.
- **Verified build**: 0 compile errors, 69 suites green x6, **1,793 bodies** (1,102 linked, 695 pending).

## D270

- Loader now merges the split `_unnamed_*.cpp` listing files (102 addresses that existed only there). Count unchanged:
  **1,793 bodies** (1,102 linked, 696 pending). 69 suites green, six cycles.
- Do not glob the whole reference tree into the loader: it holds other images' listings and produced 40,944 bodies.

## D270

- `npc-tq-imports.h`: `tq::TimeGet`, `SysTimeGet`, `IsTimeRange`, `DateTime` declared from their mangled import names
  and wired as null-defaulted inline seam pointers (`g_pfnTimeGet`, ...).
- Standing: **1,793 bodies** (1,102 linked, 691 pending). 69 suites green, six cycles.
- Ordinal-only imports: 194 of 467 - no signature derivable, those bodies stay shut without the exporting DLL.

## D269

- `Docs/disasm/remaining.txt`: 830 remaining functions disassembled from the image by `tools/disasm_remaining.py`
  (capstone, entry to next entry, bytes + mnemonics). This is the evidence earlier batches said they lacked.
- Standing count unchanged this unit: **1,781 bodies**, 69 suites green.

## D268

- `npc-win-types.h`: the Windows SDK types the listing names, documented definitions only; `CRITICAL_SECTION` forward
  declared (pointer use only); `va_list` = `__builtin_va_list`.
- Standing count: **1,781 bodies** (1,091 linked, 690 pending). 69 suites green, six cycles.
- `tools/transliterate.py` accepts `TQ_ONLY` (address list) and `TQ_OUT` (scratch output) for subset experiments.

## D267

- Bare `undefined` is mapped to `unsigned char` (Ghidra's `undefined1`, also its "no meaningful return" type); the
  reject tokens are gone. Net **0**, pending-tier compile errors 489 -> 463.
- `Docs/REMAINING_BODIES.md`: the full list of the 846 remaining bodies, grouped by blocking tag.
- Standing count: **1,770 transliterated** (1,090 linked, 680 pending); **2,728 of 3,574 bodies** have definitions.

## D266

- `_DAT_` blobs are now written non-const (the body's own expression gives the width of a store) and
  `body_globals_ok` allows storing through a `_DAT_`; plain `DAT_` strings still wait. Net **0**.
- **Real remaining count over the whole listing: 846 of 3,574 bodies** (port has 2,728 = 76.3%). The six decline
  labels all reduce to one missing thing: widths that only the instruction stream states.
- Nothing to read those widths from is in the tree yet - a disassembly export (or the PDB) is the unlock.

## D265

- `tools/emit_underscore_data.py` cuts the 20 `_DAT_` blobs out of `NpcServer.exe` (PE-mapped, 32 bytes each, exact
  bytes) into `npc-underscore-data.{h,cpp}`.
- `body_globals_ok` now applies the address-only rule to the `_DAT_` spelling too; storage users are declined instead
  of silently approximated.
- Net **0** (1,770). The 87 declined bodies are blocked by the bare Ghidra `undefined` type, not by missing globals.
- Standing count: **1,770 bodies** (1,090 linked, 680 pending). 69 suites green, six cycles.

## D264

- Throw family attempted: `g_pfnNpcCxxThrowException` seam declared (`log-stubs.h`) and defined
  (`front-of-image.cpp`), `_CxxThrowException(` rewritten to it, `exception` removed from the reject list.
- **Net gain 0** (1,770 -> 1,770): every one of those bodies also reaches a `_DAT_` global the port does not carry.
  The decline label simply moved from "exception 51" to "undefined 87". Seam kept, it is the right call shape.
- Standing count: **1,770 bodies** (1,090 linked, 680 pending). 69 suites green, six cycles.
- `_DAT_` is now the last structural hole; it cannot be closed with an opaque declaration without risking silent
  numeric wrongness.

## D263

- vftable capture now reads the class name backwards with angle brackets balanced, so template keys
  (`CGameData<&char*_szGenerator,...>`) match the way `VTABLE_SLOTS.tsv` spells them. Third fix of the same class of
  bug; the table's spelling is the authority.
- Standing count: **1,770 bodies** (1,090 linked, 680 pending). 69 suites green, six cycles.
- "vftable not in table" is now 0. Top declines: `extraout_` 105, callee with no usable declaration 69, `SUB168` 67,
  exception objects 51.

## D262

- The vftable lookup could not see scoped names (`std::bad_alloc::vftable`, `std::tr1::_Ref_count_base::vftable`);
  the table always had them. Capture widened to the full scope, matched whole then by last component.
- Standing count: **1,720 bodies** (1,046 linked, 674 pending). 69 suites green, six cycles.
- "vftable not in table" 88 -> 65 (the rest are classes the RTTI harvest does not carry).
- `SUB84`/`SUB168` (67) left alone on purpose: the listing does not establish which half the operand points at.

## D261

- `modules/npcserver/unattributed/npc-concat.h`: the eleven `CONCATxy` macros plus the Ghidra slice typedefs
  (`int7`/`uint7`/...), defined from the name and nothing else. `CONCAT` left the reject list.
- Standing count: **1,707 bodies** (1,031 linked, 676 pending). 69 suites green, six cycles.
- Vtable symbols are now emitted for every RTTI slot (no body should fail on an undefined slot). The 88 bodies still
  declined as "vftable not in table" are a name-form mismatch in the lookup, not a missing definition.
- Next wall: `extraout_` 105, vftable-name mismatch 88, callee with no usable declaration 69, `SUB` slices 67.

## D260

- Correction: `rewrite_std_string()` and `rewrite_log_calls()` were documented in D258/D259 but were **not** in
  `tools/transliterate.py` (patches anchored on names the file no longer had). They are in now, applied before
  `map_types()`. Measured effect: 1,641 -> **1,669 bodies** (1,015 linked, 654 pending).
- `tools/extract_data.py` had its PE section fields swapped; fixed, the same pass now resolves **111 strings** of the
  214 globals instead of 1 (102 remain address-only). Log-string bodies log through `::tq::g_pfnNpcInlineLogError`.
- Remaining top blockers, measured: `extraout_` 105, `CONCAT` 95, vftable-not-in-table 87, `SUB168` 67.
- 69 suites green, six cycles.

## D259

- `Docs/NPC_DATA_TYPING.md` (from `tools/type_worksheet.py`): the evidence for all 214 globals - mentions, casts,
  callers-by-address, image bytes. **208 of 214 are used only by address**, so a width cannot be derived from use.
- Three consumers dominate: log format strings (317 bodies, `DAT_1400be0b0`), `_CxxThrowException` ThrowInfo blobs
  (77 + 39 + 15 bodies), and data tables (`DAT_140103510`, 106 bodies, 4-byte entries).
- Guard added: a body touching a global must have it typed in `npc-data.h` and must only take its address.
  `log_InlineLogERROR` now routes to `::tq::g_pfnNpcInlineLogError`; `WARNING`/`INFO` stay rejected (no seam yet).
- Standing count: **1,641 bodies** (994 linked, 647 pending). 69 suites green, six cycles.

## D258

- `rewrite_std_string()` in `tools/transliterate.py` maps the demangled `basic_string` instantiation onto the port's own
  `std::string` (members, `begin/end`, dtor, placement ctor, and the four operators). Unlisted members stay declined.
- It unlocked **no** bodies: re-measured, the 176 `std::` bodies simply re-sort onto their real blockers (`DAT_` 394,
  vftable-not-in-table 86, `CONCAT` 73, `extraout_` 105, 51 with no usable callee declaration). The std:: call was the
  visible defect of bodies that also touch globals and vtables.
- Standing count: **1,645 bodies** (996 linked, 649 pending). The 1,738 in D257 was a pre-prune figure; corrected here.
- 69 suites green, six cycles.

## D257

- `tools/harvest_data.py` + `tools/extract_data.py` open the data wave: widths from the listing's own casts, bytes from
  the image via the PE section table. `Docs/NPC_DATA_WIDTHS.tsv` records the evidence per global.
- Measured scope: 214 `DAT_` names, only 7 sizeable today (1 string, 6 blobs), 190 with no width evidence, 17
  unresolvable. `npc-data.{h,cpp}` carries the 7; `DAT_` bodies stay declined until a typing pass decides what each
  global is.
- 1,645 bodies transliterated (996 linked, 649 pending) after pruning; 69 suites green, six cycles.

## D256

- The transliterated unit now carries **1,645 bodies** (996 linked, 649 pending): 2,751 of 4,099 decompiled bodies have
  source in the port.
- `code *` and `code **` call sites rewrite to `tq::CallCode(...)`, a variadic template that keeps the call site's own
  argument types (a plain variadic cast would lose float arguments). `goto LAB_...` bodies keep their labels as
  `lab_<address>` and are declined only when the jump crosses an initialization.
- Still declined: 287 `DAT_` (data wave), 176 `std::`, 105 `extraout_`, 72 `CONCAT`, 63 vftable-not-in-table, and the
  file-IO bodies waiting on the CRT shims.

## D255

- `modules/npcserver/unattributed/transliterated.{h,cpp}`: **1,418 bodies** copied from the listing by
  `tools/transliterate.py` (782 linked, 636 pending behind `TQ_TRANSLIT_PENDING`). 2,511 of 4,099 decompiled bodies
  now have source in the port.
- The unit's accounting is exported (`g_aNpcTranslitAddr`, `g_nNpcTranslitCount/Linked/Pending`) and asserted by
  `tests/npcserver_d255_test.cpp`. `tools/translit_loop.sh` regenerates, prunes what will not compile, and builds both
  tiers; a declined body is recorded by address in `Docs/TRANSLIT_DENY.txt`.
- `Docs/TRANSLIT_AVAILABLE.txt` (nm over the linked objects) and `Docs/TRANSLIT_SYMS.tsv` (demangled signatures) decide
  what "already ported" means. Reading availability out of the runner instead of the tree is what removed a whole class
  of duplicate-definition and signature-mismatch link errors.
- Still declined: 577 `code *`, 298 `goto`, 162 `std::`, 128 `DAT_`, 51 vftable-not-in-table, 47 intrinsics, plus the
  file-IO bodies that need the `_open/_read/_write/_close` shims.

## D254

- `small-bodies.{h,cpp}` regenerated to **290 bodies / 18 shapes** (move-a 33, move-c 22, refcount-dtor 20, identity 9,
  size-getter 9, log-clear-iter 6, zero 6, deref-get 6, ptr-add 4, move-b 4, plus the earlier families).
- The two move spellings differ in what they return: `move-a` -> start of the copied block, `move-c` -> end. `move-c` may
  also sit behind leading parameters; the manifest carries that count in `nExtra`.
- Generator gotcha, now guarded: `defined_bodies()` must ignore `small-bodies.cpp` while rewriting it.
- 68 suites green, six cycles.

## D253

- Generator grew `iter-assign` (18) and `vtable-set` (30, addresses resolved through the normalised RTTI names in
  `Docs/VTABLE_SLOTS.tsv`). `small-bodies.{h,cpp}` now carries **171** generated bodies, all driven by the suite.
- Still hand-work for the 79 `memmove_s` forward-move bodies: several decompiler spellings must be matched by hand first.

## D252

- `tools/gen_small_bodies.py` + `Docs/` batch: **123 generated bodies** in `small-bodies.{h,cpp}` (53 iterator compares,
  41 field getters, 22 empty bodies, 2 range predicates, 2 module-base getters, 2 stores, 1 compare), all driven from
  `g_aNpcSmallBody` by `tests/npcserver_d252_test.cpp`.
- **Count corrected:** the denominator is **7239** distinct functions (the listing and `index.tsv` agree; all status
  `ok`), not 4099. `tools/count_bodies.py` prints the live numbers: 922 defined bodies (12.7%), 586 manifest entries.
  The 336 bodies older than the manifest pattern are inside that 922 and are covered by their earlier suites only.
- 68 suites green, six cycles.
- Next: keep the generator running over the remaining recognised shapes, and hand-port the big families it refuses
  (`memmove_s` wrappers, `_Ref_count` destructors, iterator assigns).
