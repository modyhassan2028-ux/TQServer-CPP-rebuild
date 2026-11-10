
## D102 — the protobuf seam file stops being a copy of its callers (2026-11-08)

msgleaguetokenpb.cpp called `syndicate::g_fnModMem0428` and `g_fnModMem1088`, names from an
earlier seam generation that no longer existed: the destructors behind them are 0x1417db330 and
0x1417da8b0, and the module seam family lives in `namespace tq` (module.h), so the calls became
`g_pfnL_1417db330` / `g_pfnL_1417da8b0` with the two pointers declared in module.h beside the
other fourteen and defined in module.cpp.

Linking the whole pool then surfaced the real shape of the protobuf seams: msgpbseams.cpp
defined 134 of them while the message files each defined their own copy at the top, so the pool
refused to link with `multiple definition of syndicate::g_pfnPbWriteUnknown` and its siblings.
The pool has to link both sets, so msgpbseams.cpp now defines only the names no message file
defines (22 remain: the five PB write helpers no file owns, g_pfnMessageLiteCtor 0x141823280,
g_fn_1417e8050, and g_qw141886ea0), and the message files keep theirs.

Two suites had to grow to match: run_flower_cycle.sh now compiles modules/cqbase/src/*.cpp, because
synobjects.cpp and syntreemap.cpp need tq::CMyHeap (myheap.cpp) and tq::log_InlineLogERROR
(logkernel.cpp); run_syndicate_pbsuite.sh compiles the same set with include/ and modules/ on the
search path and no longer needs the log stub the test file used to carry.

Verification: run_flower_cycle.sh CYCLE-6X-GREEN 21 units, run_syndicate_pbsuite.sh
PBSUITE-GREEN x6 (33 checks, 0 fails), container accessors 33, comparators 24, vtable forwarders 20.

## D103 — the ini/inimgr sources under their binary paths, and the CQBase cycle's shared-process seams

- `modules/cqbase/src/cini.cpp` -> `modules/cqbase/src/ini.cpp` and
  `modules/cqbase/src/cinimgr.cpp` -> `modules/cqbase/src/inimgr.cpp`, both via `git mv`.
  The eight `ini.cpp` bodies (0x140b91170, 0x140b91260, 0x140b93e10, 0x140b94030,
  0x140b944f0, 0x140b96ed0, 0x140b97740) and the `inimgr.cpp` bodies already in the port
  keep their line strings unchanged; only the source path now matches the binary's own
  `f:\\version\\cqserver-78.0.11-1204\\modules\\cqbase\\src\\ini.cpp` literal.
- `tests/cqbase_d53_test.cpp` re-pointed at the real message-destructor seams after D102:
  `tq::g_pfnL_1417da8b0` (0x1417da8b0, the 1088-byte message destructor) and
  `tq::g_pfnL_1417db330` (0x1417db330, the 1064-byte message destructor).
- `tools/run_cqbase_cycle.sh` now links the syndicate objects the CQBase units reach
  (`EXTRA`): `SynMsgDestroy` (synexc.cpp), the module seam family and the message
  constructors in `modules/syndicate/src/msg/`.
- `tests/cqbase_d10/d11/d12/d7/d8` no longer leave `g_pfnLogPrintf` null at the end of
  their run: the units share one process, and the next unit's first `LogPrintf` went
  straight through a null seam. They leave their `CatchLog` sink installed instead.
- `tests/cqbase_d25_test.cpp` stubs the four `tq::g_LogApi` entry points: a free on a heap
  nothing was taken from still reports, which the original does (`IF_NOT m_lNumAlloc > 0
  myheap.cpp:0x53`) and then falls through to the heap check.
- Verified in isolation: `cqbase_d25` prints
  `SYNDICATE_D25_OK: both initialisers, both teardowns and both frees, 6 units, 57 checks`.
- Closed the same day: `cqbase_d24` installed its own release seams
  (`g_pfnDestroyDomain`, `g_pfnFreeDomainAlloc`, `g_pfnDestroyFacility`,
  `g_pfnFreeFacilityAlloc`, `g_pfnInitCrossVlmList`) and never put the incoming ones
  back, so `cqbase_d25`'s `Release(pDom)` went to d24's lambdas and its own counters
  stayed at zero. `cqbase_d24` now saves them on entry and restores them at the end.
- `tools/run_cqbase_cycle.sh` -> `CQBAE-CYCLE-6X-GREEN: 77 units`.

## D129 — the pure accessor cluster at 0x1417c5980..0x1417c5f80

41 bodies, one source file, no seam: nothing in the cluster calls out, so each body is
its own instruction run and nothing else.

- `modules/syndicate/src/synacc.cpp` + `synacc.h`. Every function is named for its own
  start address because the cluster's `__FILE__` literal is not resolved yet; when it is,
  the two files move to that path and the names take the original's.
- Byte-for-byte forms implemented: `mov (%rdx),%eax / mov %eax,(%rcx)` with the qword at
  `+0x8` (0x1417c5980, 0x1417c5990); `movq $0x0,(%rcx)` (0x1417c59a0); the twelve
  `mov %rcx,%rax` bodies; the fifteen `lea 0xNN(%rcx),%rax` bodies at 0x10/0x18/0x20/0x21/
  0x28/0x29/0x40/0x41; the 0x30 slot loaded plain, `+0x8` and `+0x10` (0x1417c59f0,
  0x1417c5a00, 0x1417c5a60, 0x1417c5a70, 0x1417c5d00, 0x1417c5dd0); the 0x8 slot
  (0x1417c5b00, 0x1417c5b70, 0x1417c5bc0); the two-qwords-and-a-byte copy at +0x10
  (0x1417c5ae0, 0x1417c5b10); the two-qword copy (0x1417c5e60); and the raw
  `movabs $0xfffffffffffffff` answer (0x1417c5ef0).
- `tests/syndicate_d129_test.cpp`: 56 checks, 6 passes, ASan+UBSan clean.
- Left for the next unit because they are not pure: the two seams-calling comparisons at
  0x1417c5b30 and 0x1417c5b80 (`call *0x1418233c0`), the sentinel walks at 0x1417c5c50
  (`cmpb $0x0,0x29(%rax)`) and 0x1417c5f00 / 0x1417c5f30 (`cmpb $0x0,0x41(%rax)`), and the
  two `jmp 0x1417f2fdc` thunks at 0x1417c5c80 and 0x1417c5cc0.

## D130 — the accessor cluster's non-pure tail, 0x1417c5b30..0x1417c5f50

Appended to `modules/syndicate/src/CsyndicateLogicTailSlots.cpp` (the file that already
holds the two seams these bodies need), inside `namespace tq`.

- 0x1417c5b30 and 0x1417c5b80: `mov (%rcx),%rax / test / je` + `cmp (%rdx),%rax / je` then
  `call *0x1418233c0`, the DEBUG iterator check the file already models as
  `g_pfn_invalid_parameter_noinfo`; the answer is `cmp 0x8(%rdx),0x8(%rdi) / sete`.
- 0x1417c5c50: the 0x29 walk. The sentinel byte is read on the **lead** (`cmpl $0x0,0x29(%rax)`
  straight after `mov (%rcx),%rax`), so a null lead is a fault in the original too; rcx starts
  as `this` and only moves inside the loop, which is why this is what comes back when the lead
  already carries the sentinel.
- 0x1417c5c70: `mov %rcx,%rax / ret`.
- 0x1417c5c80 and 0x1417c5cc0: `mov %rdx,%rcx / jmp 0x1417f2fdc`, the deallocate thunk; the
  forwarded pointer is the **second** argument and the first is dropped, exactly as the bytes do.
- 0x1417c5f00: the 0x41 walk stepping through `+0x10`; 0x1417c5f30: the 0x41 walk stepping
  through the lead; both read the sentinel on the node they just loaded.
- 0x1417c5f50: `movabs $0x1fffffffffffffff`.
- `tests/syndicate_d130_test.cpp`: 24 checks, 6 passes, ASan+UBSan clean.
- Left: 0x1417c5e00 and 0x1417c5e80 (their dumps were cut) and the comparison at 0x1417c5f60,
  whose body continues past the same seam.

## D131 — the accessor cluster closed: 0x1417c5e00, 0x1417c5e50, 0x1417c5e80, 0x1417c5ea0, 0x1417c5eb0, 0x1417c5ec0, 0x1417c5f60

- `synacc.cpp` / `synacc.h`: 0x1417c5e50 (`mov 0x8(%rcx),%rax`), 0x1417c5e80 (both qwords then
  `movzbl (%r8)` into +0x10), 0x1417c5ea0 (`movq $0x0,(%rcx)`), 0x1417c5eb0
  (`movabs $0x666666666666666`), 0x1417c5ec0 (the `0x29` walk stepping through `+0x10`).
- `CsyndicateLogicTailSlots.cpp`: 0x1417c5e00 (`mov %rdx,%rcx / jmp 0x1417f2fdc`) and
  0x1417c5f60, which is 0x1417c5b30 word for word except the final `setne` instead of `sete`.
- `tests/syndicate_d131_test.cpp`: 20 checks, 6 passes, ASan+UBSan clean.
- The cluster now stands at 57 bodies over three units (D129 41, D130 9, D131 7). Still open in
  the same run of code: 0x1417c5fa0, the tree increment, whose body continues past 0x1417c601e
  (`cmp %rax,0x8(%rbx)` / `jne` / `mov %rcx,0x8(%rbx)`) and needs a full dump before it can be
  written verbatim.

## D132 — sixteen more bodies of the cluster, 0x1417c5fa0..0x1417c63a0

- `synacc.cpp` / `synacc.h`: 0x1417c60e0 and 0x1417c60f0 (`lea 0x28` / `lea 0x18`),
  0x1417c6160 (the 0x30 slot `+0x10`), 0x1417c6100 and 0x1417c6170 (the two rotations, the
  head branch, the parent branch and the fallthrough all kept as the bytes order them),
  0x1417c6250 and 0x1417c6280 (four qword stores: 0x10 from rdx, 0x10 from r8), 0x1417c62b0
  and 0x1417c6330 (the 0x29 and 0x21 node builds; the pair is the fifth argument, the byte
  the sixth, and the sentinel is cleared last), 0x1417c6360 and the two 0x21 walks
  0x1417c6370 / 0x1417c63a0.
- `CsyndicateLogicTailSlots.cpp`: the two increments 0x1417c5fa0 (0x29 flag) and 0x1417c6040
  (0x41 flag), each with its three routes (header, flagged left child, climb) and the two
  seam jumps; 0x1417c61d0, which reads the lead's lead, takes its 0x30 slot and answers the
  node `+0x18`; and 0x1417c6210, the `setne` comparison.
- `tests/syndicate_d132_test.cpp`: 48 checks, 6 passes, ASan+UBSan clean.
- Note for the next unit: in 0x1417c61d0 a null lead that stays null after the check walks
  into `mov 0x30(%rax),%rax` with rax zero, exactly as the bytes do; the port reproduces that
  read rather than guarding it.
- Excluded on purpose: 0x1417c62e0 (calls `*0x141823288`, a seam not yet modelled in the file)
  and 0x1417c63c0 (dump cut at 0x1417c63fe).

## D133 — fifteen more bodies, 0x1417c63c0..0x1417c6700

- The decrement family, each on its own flag and each its own start: 0x1417c63c0 (0x41),
  0x1417c6580 (0x21) and 0x1417c6610 (0x29). All three take the 0x10 side first: if that
  side carries the flag the parent climb runs (0x1417c6416 / 0x1417c65d6 / 0x1417c6666),
  otherwise the walk goes down the 0x0 lead of the 0x10 child (0x1417c63f5 and friends).
  The climb stores the node it stopped at unconditionally, which is why the loop's exit and
  the entry case share one store.
- 0x1417c64b0: the 0x29 increment, the same three routes as 0x1417c5fa0 (header, flagged
  left child, climb), its own start.
- `synacc.cpp`: 0x1417c6450 and 0x1417c6480 (the two 0x29 walks, +0x10 and lead),
  0x1417c64a0 (`movabs $0xfffffffffffffff`), 0x1417c6550 (the 0x29 node build, the pair from
  the fifth argument, the byte from the sixth, the sentinel cleared between the two pair
  stores), 0x1417c66a0 (two word copies, so the four bytes between them are never assumed to
  move together), the five `ret $0x0` bodies 0x1417c66b0..0x1417c66f0 and 0x1417c6700.
- `tests/syndicate_d133_test.cpp`: 34 checks, 6 passes, ASan+UBSan clean. One test-side fix
  on the way: the buffer handed to the 0x29 build has to be 0x60 bytes, the body writes at
  +0x28 and +0x29.
- Next: 0x1417c6710, the divide-bearing body whose dump must be taken whole (it calls
  `*0x1418233e8` after `div %rcx` and a `cmp $0x30,%rax`), and 0x1417c62e0, which needs the
  `0x141823288` seam modelled (`g_fnLIFT_141823288` in synlift.cpp).

## D134 — seventeen bodies, 0x1417c6780..0x1417c69d0

- The eleven "this back" returns: 0x1417c6780, 0x1417c6800, 0x1417c6880, 0x1417c6890,
  0x1417c68b0, 0x1417c68d0, 0x1417c6900, 0x1417c69a0, 0x1417c69b0, 0x1417c69c0, 0x1417c69d0.
- The four guarded single-qword stores 0x1417c68a0, 0x1417c68c0, 0x1417c68f0, 0x1417c6990:
  `test %rcx,%rcx / je out / mov (%rdx),%rax / mov %rax,(%rcx) / repz ret`. A null destination
  writes nothing and the body answers nothing.
- The two `ret $0x0` bodies 0x1417c68e0 and 0x1417c6980.
- `tests/syndicate_d134_test.cpp`: 22 checks, 6 passes, ASan+UBSan clean. The cluster now
  stands at 105 bodies (D129 41, D130 9, D131 7, D132 16, D133 15, D134 17).
- Held back on purpose, all four the same shape: 0x1417c6710, 0x1417c6790, 0x1417c6810 and
  0x1417c6910. Each takes an element count, divides `-1` by it for the overflow test
  (`cmp $0x30,%rax` / `$0x48` / `$0x28`), and on the failing side builds a `length_error`
  through three seams this file does not model: the object constructor at 0x1418233e8, the
  vtable store `0x141824c40`, and the throw helper at 0x1417f3154. The good side is
  `lea (%rcx,%rcx,N)` / `shl $0x3` and then `jmp 0x1417f3166`.

## D135 — the four element-count allocators and their three seams, 0x1417c6710 / 0x1417c6790 / 0x1417c6810 / 0x1417c6910

The four bodies that were held back at D134 are in, each read straight off its own start.

- The arithmetic is the bytes': `or $-1,%rax` then `xor %edx,%edx` then `div %rcx` gives
  `0xFFFFFFFFFFFFFFFF / nElems`, and the limit each body compares it against is its own
  (`cmp $0x30` at 0x1417c6710 and 0x1417c6910, `cmp $0x48` at 0x1417c6790, `cmp $0x28` at
  0x1417c6810). `jae` means a quotient *at* the limit still allocates, which the test pins
  with `edge = 0xFFFFFFFFFFFFFFFF / 0x30`.
- The stride is the instruction sequence: `lea (%rcx,%rcx,2) / shl $0x4` = 48 bytes per
  element at 0x1417c6710 and 0x1417c6910, `lea (%rcx,%rcx,8) / shl $0x3` = 72 at 0x1417c6790,
  `lea (%rcx,%rcx,4) / shl $0x3` = 40 at 0x1417c6810.
- The failing side builds the exception exactly where the bytes do: a `-2` sentinel in the
  frame, a zeroed qword at `0x50(%rsp)` passed as the second argument, the object at
  `0x28(%rsp)` given to 0x1418233e8, the `0x141824c40` vtable stored over its lead, then
  0x1417f3154 with `0x141881df0` as the message. The bytes then fall through to the size, so
  the port does too.
- Three seams were added for that path, all null by default with the call guarded:
  `g_pfnSynErrCtor_1418233e8`, `g_pfnSynThrow_1417f3154` and `g_pfnSynNew_1417f3166` (the
  operator new the good path tail-jumps to). No behaviour is invented when a seam is unset.
- `tests/syndicate_d135_test.cpp`: 30 checks including the limit boundary, 6 passes,
  ASan+UBSan clean. Cluster total 109 bodies.

## D136 — the head of the 0x1417c69e0 stretch, 0x1417c6a10 / 0x1417c6a20 / 0x1417c6a30 / 0x1417c6a40

- 0x1417c6a10: two words from two separate arguments — `(%rdx)` into `(%rcx)` and `(%r8)`
  into `0x4(%rcx)` — then `this` back. Two 4-byte moves, so the word between them is never
  assumed to travel with either.
- 0x1417c6a20 and 0x1417c6a30: `mov %rcx,%rax / ret`.
- 0x1417c6a40: the direction is reversed against its neighbours — the two qwords come out of
  `(%rcx)` and land in `(%rdx)`, and the answer is `rdx`, not `rcx`.
- `tests/syndicate_d136_test.cpp`: 12 checks, 6 passes, ASan+UBSan clean. Cluster 113 bodies.
- Still to come from the same dump (`Docs/ASM/1417c69e0.txt`, 227 lines): 0x1417c69e0, the
  `add $0x18,%rcx` tail jump through the slot at 0x141823290, and 0x1417c6a60, which asserts
  twice through `*0x141823030` with lines 0x32a and 0x32b and paths 0x14182664c,
  0x141824ca8, 0x141836e5c and 0x141839fe0 before calling 0x141785dc0 and 0x1417c5640.

## D137 — the two checked forwarders 0x1417c6a60 and 0x1417c6b30, with the 0x141823030 assertion modelled

- The assertion seam `g_pfnSynAssert_141823030` takes the four pointers the bytes put in
  rcx/rdx/r8/r9 and the line number they put on the stack. The failing branches carry:
  file 0x141824ca8 and function 0x14182664c in every case, expression 0x141839fe0 in every
  case, and the third pointer differs by branch — 0x141836e5c for the second argument at line
  0x32a, 0x141831610 for the third at line 0x32b, and 0x141836e5c again at line 0x339 in
  0x1417c6b30.
- 0x1417c6a60 forwards `(this, a2, a3, <int from 0x141785dc0>, flag)`; the flag reaches the
  callee as a stack byte (`mov %sil,0x20(%rsp)`), not as a register.
- 0x1417c6b30 forwards `(this, a2, <result of 0x14178c8e0>, a3 as int, flag)`, and the slot
  that prepare step reads is `0x90(%rcx)` on the original `this`, which the test pins by
  giving `this` a distinguishable 0x90 pointer.
- Three more seams, all null by default with the call guarded: `g_pfnSynPrep_141785dc0`,
  `g_pfnSynPrep_14178c8e0` and the shared `g_pfnSynFwd_1417c5640`.
- `tests/syndicate_d137_test.cpp`: 34 checks, 6 passes, ASan+UBSan clean. Cluster 115 bodies.

## D138 — 0x1417c69e0, the `this + 0x18` tail call

- Bytes: `mov %rcx,0x8(%rsp)` / `sub $0x38,%rsp` / `movq $0xfffffffffffffffe,0x20(%rsp)` /
  `add $0x18,%rcx` / `add $0x38,%rsp` / `jmp *0x141823290`. The frame is gone before the jump,
  so it is a genuine tail call and the port keeps it as one.
- The slot at 0x141823290 holds an unresolved RVA (0x1628a6) in the image; rather than guess
  what sits behind it, the port keeps it as `g_pfnSynTail_141823290`, null by default with the
  call guarded. The argument handed over is `this + 0x18`, and the answer is the callee's.
- `tests/syndicate_d138_test.cpp`: 7 checks including the `this + 0x18` identity and the unset
  seam answering nothing, 6 passes, ASan+UBSan clean. Cluster 116 bodies.

## D139 — 0x1417c6bd0, the checked forwarder that also dispatches

- The assertion branch carries a pointer set that differs from its two neighbours:
  file 0x141824ca8, **0x141827b98** in the second slot, 0x141831610 in the third and
  0x141839fe0 in the fourth, at line **0x39c**. That branch is the only one answering false.
- 0x141787300 only decides whether the dispatch runs: its answer goes into `test %al,%al` and
  `je 0x1417c6c5e` jumps straight to `mov $0x1,%al`, so a false there still answers true.
- The dispatch reads `0x88(%rdi)` for the slot, `(%rcx)` for its vtable and `0x1a0(%r9)` for the
  target, with `edx` the `0x141785dc0` answer and `r8d` the flag. Modelled as
  `g_pfnSynVirt_1417c6bd0(pSlot, pFn, n, flag)` so both the slot and the resolved target stay
  visible, while the slot and vtable reads are the bytes' own.
- The hand-off to 0x1417c6a60 passes a **zero** flag (`xor %r9d,%r9d`), not the incoming one,
  and 0x141785dc0 therefore runs twice on this path: once for the dispatch and once inside
  0x1417c6a60. The test pins that count.
- `tests/syndicate_d139_test.cpp`: 22 checks, 6 passes, ASan+UBSan clean. Cluster 117 bodies.

## D140 — 0x1417c6c80 / 0x1417c6c90 / 0x1417c6ca0

- 0x1417c6c80: `add $0x98,%rcx` / `mov (%rcx),%rax` / `jmp *(%rax)`. The disassembly settles the
  indirection: the jump target is the value **at** `*(this+0x98)`, so the slot holds the code
  pointer itself and there is no vtable dereference beyond it. The port reads exactly those two
  levels and hands the object and the target to `g_pfnSynVirt0_1417c6c80`.
- 0x1417c6c90: the identical jump with `this` as the object — `mov (%rcx),%rax` / `jmp *(%rax)`.
- 0x1417c6ca0: the `setne` iterator comparison again, the DEBUG check at 0x1418233c0 running
  unless both leads name one node.
- `tests/syndicate_d140_test.cpp`: 15 checks, 6 passes, ASan+UBSan clean. Cluster 120 bodies.

## D141 — twelve bodies, 0x1417c6ce0 .. 0x1417c6dff

- 0x1417c6ce0: the setne iterator comparison once more, its own start, the DEBUG check at
  0x1418233c0 in the same two places.
- 0x1417c6d20: `movq $0x0,(%rcx)` then `this` back.
- The three `+0x18` accessors 0x1417c6d30 / 0x1417c6d60 / 0x1417c6d90 (`lea 0x18(%rcx),%rax`)
  and the three 0x30-slot accessors 0x1417c6d40 / 0x1417c6d70 / 0x1417c6da0
  (`mov 0x30(%rcx),%rax` / `add $0x8,%rax`).
- The three deallocate thunks 0x1417c6d50 / 0x1417c6d80 / 0x1417c6db0: `mov (%rcx),%rcx` then
  `jmp 0x1417f2fdc`, so the **lead** is what goes to the deallocate, not `this`. The test hands
  each thunk a real allocation so the default seam can take it, and checks the lead still reads
  back afterwards because the body only ever reads it.
- 0x1417c6dc0: the `+0x18` accessor with both DEBUG checks kept. Its first check falls through
  on a lead that stays null after the seam and reads `0x30(%rax)` with rax zero, exactly as the
  bytes do; the port reproduces that read rather than guarding it.
- `tests/syndicate_d141_test.cpp`: 20 checks, 6 passes, ASan+UBSan clean. Cluster 132 bodies.

## D142 — seven bodies, 0x1417c6e00 .. 0x1417c6f50

- 0x1417c6e00: the iterator builder. Its order matters and the port keeps it: the lead is cleared
  first, the node goes to `+0x8` second, and only then is the third argument checked at
  0x1418233c0 before **its** lead is copied in. A null third argument is a fault in the bytes as
  well (`mov (%rdi),%rax` with rdi zero), so nothing is guarded that the original does not guard.
- 0x1417c6e40: the `+0x18` accessor with both DEBUG checks, byte for byte the body at
  0x1417c6dc0, its own start.
- 0x1417c6e80: the `0x29` decrement, the fourth copy of that body — the node's `0x10` side
  decides, then either the left walk from `0x1417c6eab` or the parent climb at `0x1417c6ed6`,
  whose exit stores `rcx` unconditionally.
- 0x1417c6f10: `mov (%rcx),%rcx` / `jmp 0x1417f2fdc`, the lead to the deallocate.
- `synacc.cpp`: 0x1417c6f20 (two qword stores, this back), 0x1417c6f40 (`movq $0x0,(%rcx)`),
  0x1417c6f50 (`movabs $0xfffffffffffffff`).
- `tests/syndicate_d142_test.cpp`: 17 checks, 6 passes, ASan+UBSan clean. Cluster 139 bodies.

## D143 — the keyed search 0x1417c6f60 and the two rotations at 0x1417c6f90 / 0x1417c6ff0

- 0x1417c6f60: `mov 0x30(%rcx),%r8` takes the header out of the tree's 0x30 slot, `mov 0x8(%r8),%rax`
  its root, and the walk then compares `0x18(%rax)` against the argument with a **32-bit**
  `cmp %ecx,0x18(%rax)` / `jae`. Equal keys take the `jae` too, so they turn left like greater
  ones. The answer is the last node the walk turned left at (`r8`), not the node it stopped on,
  which the test pins with the key-7 and key-3 cases and with key 99 keeping the header.
- 0x1417c6f90: the 0x10-side rotation, byte for byte the body at 0x1417c6100 — the same three
  link cases after the `0x30(%rcx)` head test, at its own start.
- 0x1417c6ff0: the mirror, byte for byte the body at 0x1417c6170.
- `tests/syndicate_d143_test.cpp`: 11 checks, 6 passes, ASan+UBSan clean. Cluster 142 bodies.

## D144 — nine bodies, 0x1417c7050..0x1417c71c0

- The three `ret $0x0` stubs 0x1417c7050 / 0x1417c7060 / 0x1417c71a0 and the two constants
  0x1417c7070 (`0x666666666666666`) and 0x1417c71b0 (`0x1fffffffffffffff`).
- 0x1417c70e0: the 0x10-side rotation with every link tested against the **0x41** byte, at its
  own start. The node it lifts is `x->0x10`, so when that slot already holds the sentinel the
  sentinel is what comes back as the answer and what the head ends up naming — the test pins
  exactly that arrangement after the first attempt assumed a fresh node.
- 0x1417c7140: the mirror on the 0x0 side, last link case on 0x10.
- 0x1417c71c0: the 0x21 keyed search, 32-bit `cmp`/`jae`, the answer being the last node the
  walk turned left at. Both the equal key (takes `jae`) and the never-turned-left case (the
  header comes back) are asserted.
- `tests/syndicate_d144_test.cpp`: 5 groups, 6 passes, ASan+UBSan clean. Cluster 151 bodies.

## D145 — six bodies, 0x1417c7080 / 0x1417c71f0 / 0x1417c7250 / 0x1417c72b0 / 0x1417c72c0 / 0x1417c72e0

- 0x1417c7080: the comparator-driven descent. The 0x30 slot gives the header, `0x8` of it the
  root, and the loop calls the comparator at 0x141823260 with `node+0x18` and the argument. A
  true answer walks the `0x10` link and keeps the candidate where it was; a false answer takes
  the node as the new candidate and walks the `0x0` link. The answer is the last left-link node,
  the header when the walk never turned left. `g_pfnSynCmp_141823260` is a new seam, null by
  default, and the test points it at a real `<` so the three cases (7, 3, 99) pin the sides.
- 0x1417c71f0 / 0x1417c7250: the 0x21 rotations, identical shapes to the 0x29 and 0x41 pairs
  already in the cluster, each at its own start.
- 0x1417c72b0: `ret $0x0`.
- 0x1417c72c0 / 0x1417c72e0: call 0x1417c5fa0 / 0x1417c6040 and hand the **iterator** back, so the
  wrapper's return value is its own argument, not the increment's. The test drives both through
  the header case and checks the node slot lands on the root while the answer is the iterator.
- `tests/syndicate_d145_test.cpp`: 6 groups, 6 passes, ASan+UBSan clean. Cluster 157 bodies.

## D146 — sixteen bodies, 0x1417c7300..0x1417c75f0

- 0x1417c7300 (`this+0x18`), the two `ret $0x0` stubs 0x1417c7310 / 0x1417c75e0, the two
  zero-lead bodies 0x1417c7360 / 0x1417c75b0, the constant 0x1417c7580 and the three guarded
  stores 0x1417c75c0 / 0x1417c75d0 / 0x1417c75f0 (destination rdx, source r8).
- 0x1417c7320: the fourth start of the `+0x18` accessor. The first DEBUG check falls through on
  a lead that stays null and then reads `0x30(%rax)` with rax zero, exactly as the bytes do; the
  second runs when the lead's `0x30` slot equals the iterator's node, and the answer is still
  node`+0x18` — the test pins both.
- 0x1417c74c0: the 0x21 increment, three paths and both seams, its own start.
- 0x1417c7560 / 0x1417c7590: call 0x1417c63c0 / 0x1417c64b0 and hand the iterator back, so the
  wrapper answers with its argument. The decrement case in the test put the flag on the header
  instead of the node at first and the original body then walked `0x10` on a null — the case is
  now the tail-seam one where the slot cannot move.
- 0x1417c7370 / 0x1417c73e0 / 0x1417c7450: the three allocators whose **count arrives in rdx**,
  with `call 0x1417f3166` instead of the tail jump. Faithful detail worth keeping: the throw
  branch zeroes the count register (`xor %r8d,%r8d`) and the size is computed from that same
  register afterwards, so a seam that returns leaves the size at zero. The test asserts 96 / 144 /
  80 for two elements and zero after each throw.
- `tests/syndicate_d146_test.cpp`: 33 checks, 6 passes, ASan+UBSan clean. Cluster 173 bodies.

## D147 — twelve bodies, 0x1417c7600..0x1417c7830

- 0x1417c7600 / 0x1417c76b0 / 0x1417c7830: the decrement wrappers, each calling its own body
  (0x1417c6580, 0x1417c6610, 0x1417c63c0) and answering with the iterator.
- 0x1417c7620: the 48-byte allocator body again at its own start, count in rdx, throw branch
  zeroing the count register so a returning seam leaves the size at zero.
- 0x1417c7690 (`ret $0x0`) and 0x1417c76a0 (the guarded store with destination rdx).
- 0x1417c76d0 / 0x1417c7710 / 0x1417c7750 / 0x1417c7790: the four node builders. Eight bytes
  come from 0x1417f3166, the object is written into them, the block (or zero when the seam
  answers null) lands in the object's first qword, and the object comes back. The test covers
  both the live and the null seam.
- 0x1417c77d0: two dword stores, `this` back.
- 0x1417c77e0: the deleting destructor. `this+0x18` goes to 0x141823290 first, then **only bit 0**
  of the flag decides whether `this` is handed to 0x1417f2fdc: the test pins flag 0, flag 3 and
  flag 0xFE (which frees nothing). This body needed `synacc.h` in the tail file for the slot seam.
- `tests/syndicate_d147_test.cpp`: 30 checks, 6 passes, ASan+UBSan clean. Cluster 185 bodies.

## D148 — twelve bodies, 0x1417c7850..0x1417c7a10

- 0x1417c7850: the comparison copies the argument's sixteen bytes to a stack temp **before** it
  touches the lead, then answers `sete` on the two +0x8 words. The copy is why its DEBUG check
  compares against `0x20(%rsp)` and not `(%rdx)`.
- 0x1417c78a0: the pair gets the tree's first qword and the **header's lead**; 0x1417c78c0 gets
  the same first qword and the **header itself**, and stores the two in the other order.
- 0x1417c7920: both qwords cleared through one zeroed register, nothing past them.
- 0x1417c78e0 / 0x1417c7930: the fifth and sixth starts of the +0x18 accessor, both DEBUG
  checks kept, the first check falling through on a lead that stays null.
- 0x1417c7970: the 0x1417c6e80 wrapper, iterator back.
- 0x1417c7990 / 0x1417c79b0 / 0x1417c79d0 / 0x1417c79f0: the four lead frees, each with the
  `-2` frame that is torn down before the jump to 0x1417f2fdc.
- 0x1417c7a10: the keyed descent filling a pair. Its comparison is a **32-bit** `cmp`/`jae`, so
  equal keys turn left like greater ones, and the answer's +0x8 is the last node the walk turned
  left at — the header when it never turned. The test builds two real stop nodes so keys 7, 3 and
  99 land on the root, on n5 and on the header.
- `tests/syndicate_d148_test.cpp`: 30 checks, 6 passes, ASan+UBSan clean. Cluster 197 bodies.

## D149 — eight bodies, 0x1417c7a50..0x1417c7be0

- 0x1417c7a50: the whole-subtree destroy, recursive. The 0x10 side goes first, then the node to
  the deallocate, then the 0x0 side carries the walk on; a node flagged in its 0x29 byte stops it
  before anything runs. The test records the free order (in, then its left, then that one's left)
  and pins that a flagged node frees nothing.
- 0x1417c7aa0 / 0x1417c7b40 / 0x1417c7b80: the iterator builder three more times, each at its own
  start: lead cleared, node into +0x8, holder's first qword into the lead.
- 0x1417c7ae0: the seventh start of the +0x18 accessor, both DEBUG checks kept.
- 0x1417c7b20 / 0x1417c7bc0: the increments wrapped, iterator back — 0x1417c5fa0 and 0x1417c6040.
- 0x1417c7be0: the pair is the object's own first qword and the third argument's +0x8, and the
  DEBUG check runs on the object pointer **before** either is read, so the two come through a
  stack temp in that order.
- `tests/syndicate_d149_test.cpp`: 17 checks, 6 passes, ASan+UBSan clean. Cluster 205 bodies.

## D150 — the subtree erase 0x1417c7c30, 19 checks x6

- The whole body, 0x1417c7c30..0x1417c7fe1: the iterator steps first (0x1417c6e80) before a link
  is read; the 0x29-sentinel path builds its throw through 0x141823270, 0x1418233f8,
  0x141823288 and 0x1417f3154 with vtable 0x141824a60 then 0x141824ba0; the unlink keeps the
  header's 0x0 and 0x10 ends by taking the smallest node on the replacement side (skipped when a
  slot already holds the sentinel); the successor swap moves the +0x28 colour byte between the two
  nodes; the fix-up walks up from the replacement while it is black, with the two rotations
  already in the cluster (0x1417c6f90 and 0x1417c6ff0), and the final store always paints the
  node it stopped on.
- The answer is `{ tree->0x0, iter->0x8 }`, and the size at tree+0x38 drops by one.
- Held back until now because the test cleared **eight** bytes at stop+0x28 (a pointer store of
  zero) which wiped the 0x29 flag beside it, so the decrement walked into an unflagged node and
  never returned. The body was right; the test was wrong. Fixed to one byte.
- `tests/syndicate_d150_test.cpp`: 19 checks, 6 passes, ASan+UBSan clean. Cluster 206 bodies.

## D151 — five bodies, 0x1417c7ff0 / 0x1417c80d0 / 0x1417c8150 / 0x1417c8170 / 0x1417c81c0

- 0x1417c7ff0: both bounds in one walk. The first loop turns left on `jae` and only moves the
  candidate while the candidate is still the header (its 0x29 is set), so an equal key keeps the
  left-side node; the second walk starts from the candidate's `0x0` unless the candidate is still
  the header, and it is the `0x0`/`0x10` choice that decides the right bound. The answer is four
  qwords: `{ tree->0x0, left bound, tree->0x0, right bound }`.
- 0x1417c80d0: the 0x30-byte node, three words then the argument's two qwords, the flag byte, and
  a cleared 0x29.
- 0x1417c8150 / 0x1417c8170: the header pair and the checked pair; the checked one runs its DEBUG
  test on the object pointer before either qword is read.
- 0x1417c81c0: the comparator range with 0x41 flags, two comparator calls per turn on the left
  path — `cmp(node+0x18, key)` first, then `cmp(key, node+0x18)` — the first picks the branch and
  the second only moves the candidate.
- The same lesson as D150, again a test-side slip: the builder seam was never installed, so the
  body had no allocator and returned nothing. Test fixed, body untouched.
- `tests/syndicate_d151_test.cpp`: 22 checks, 6 passes, ASan+UBSan clean. Cluster 211 bodies.

## D152 — the two node builders, 0x1417c82e0 (0x48) and 0x1417c8370 (0x28)

- 0x1417c82e0: three words at +0x0/+0x8/+0x10, then **a sub-object built in place** at +0x18
  through 0x141823288 with the fifth argument (the one node builder in the family that calls out
  while the block is half filled), the flag byte at +0x40 and a cleared +0x41.
- 0x1417c8370: the same three words, then only the **first** qword of the fifth argument at
  +0x18, the flag byte at +0x20 and a cleared +0x21. Nothing past those two bytes is written,
  which the test pins with a 0xCD fill.
- Both go through the 0x1417f3166 seam; an allocator that answers nothing leaves the block
  untouched, so the builders return null with no partial writes.
- `tests/syndicate_d152_test.cpp`: 19 checks, 6 passes, ASan+UBSan clean. Cluster 213 bodies.

## D153 — seven bodies, 0x1417c83f0 .. 0x1417c8530

- 0x1417c83f0: the iterator builder again (lead cleared, node at +0x8, holder's first qword in).
- 0x1417c8430 / 0x1417c84b0: 0x1417c74c0 and 0x1417c64b0 wrapped, the iterator handed back.
- 0x1417c8450 / 0x1417c8480: the pair is copied out **before** the source iterator steps down, and
  the step is applied to the *source*, so the caller's iterator moves while the answer is the out
  pair. The test pins both orders with a node that carries every flag byte, so the step returns
  without moving anything.
- 0x1417c84d0 (0x30) / 0x1417c8530 (0x48): the zeroed nodes. Three slots cleared, colour 1 at the
  node's own pair, the next byte cleared; the `$0x1` / `$0x2` spills at 0x20(%rsp) are dead and
  are kept as locals. Nothing past the pair is written, which a 0xCD fill proves.
- Test note worth keeping: each family reads its **own** byte, and the 0x29 increment reads
  0x0 before 0x10 — the first two attempts crashed because the chain was built for one family
  only. 25 checks, 6 passes, ASan+UBSan clean. Cluster 220 bodies.

## D154 — five bodies, 0x1417c8590 / 0x1417c8620 / 0x1417c8680 / 0x1417c85f0 / 0x1417c8700

- 0x1417c8590 (0x28) and 0x1417c8620 (0x30): the zeroed nodes at their own starts. Three slots
  cleared through a register the bytes zero once, colour 1 at the node's own pair, the byte beside
  it cleared, nothing past it touched. The `$0x1` / `$0x2` spills at 0x20(%rsp) are dead and kept
  as locals.
- 0x1417c8680: the 0x30 node that takes **both** pair qwords from the fifth argument (the 0x28
  builder takes only the first) plus the flag byte at +0x28.
- 0x1417c85f0: the pair is read out before 0x1417c6580 runs, and the step lands on the **source**
  iterator, so the answer and the moved iterator are both observable; the test pins the order.
- 0x1417c8700: the iterator builder once more.
- `tests/syndicate_d154_test.cpp`: 30 checks, 6 passes, ASan+UBSan clean. Cluster 225 bodies.

## D155 — six bodies, 0x1417c8740 / 0x1417c8770 / 0x1417c87c0 / 0x1417c8810 / 0x1417c8860 / 0x1417c88b0

- 0x1417c8740: the pair out first, then 0x1417c6610 steps the **source**. The step climbs to the
  flagged parent in this arrangement, so the pair still holds the pre-step node while the source
  slot moves on; the test asserts both facts separately.
- 0x1417c8770 / 0x1417c87c0: the whole-subtree destroy on 0x21 and 0x29, own starts. Both walk the
  `0x0` chain and recurse on `0x10`, so the free order is inner-first and the count for a two-node
  chain with a shared stop node is **three**, which is what the test pins after the first estimate
  of two was wrong.
- 0x1417c8810 / 0x1417c8860 / 0x1417c88b0: the eight-byte node that stores the block in the
  owner's first qword and the owner in the block. A null allocator answer leaves that qword zero,
  and the test drives both branches.
- `tests/syndicate_d155_test.cpp`: 22 checks, 6 passes, ASan+UBSan clean. Cluster 231 bodies.

## D156 — three bodies, 0x1417c8900 / 0x1417c8950 / 0x1417c8980

- 0x1417c8900: the fourth eight-byte self node, own start, both allocator branches driven.
- 0x1417c8950: the 0x18 tail call again (0x141823290), with the frame built and torn down before
  the jump; the answer is the slot's, and the argument the test sees is `this+0x18`.
- 0x1417c8980: the copied-temp comparison, `setne` here while 0x1417c7850 answers `sete`. The
  copy happens before the lead is read, so the check compares against the temp at 0x20(%rsp).
- `tests/syndicate_d156_test.cpp`: 9 checks, 6 passes, ASan+UBSan clean. Cluster 234 bodies.

## D157 — the iterator distance 0x1417c89d0

- The counter at `(%rdi)` is bumped **once per step, after** the "are we there yet" test, so two
  iterators already on the same node answer zero moves and no bump at all.
- The step is the 0x41 climb/descend the decrement uses, with both DEBUG checks: the leads must
  agree before anything moves (`test`/`je` then `cmp (%rsi),%rax`), and the lead is re-tested after
  the bump (`cmpq $0x0,(%rbx)`).
- Descend goes through `0x10` and then the left spine of that child (`mov (%rax),%rcx` and the
  `0x1417c8a40` loop); climb walks `0x8` while the parent's `0x10` link names the node we came
  from. Both land in `mov %rax,0x8(%rbx)` and jump back to the top of the walk.
- `tests/syndicate_d157_test.cpp`: 5 checks, 6 passes, ASan+UBSan clean. Cluster 235 bodies.

## D158 — the matching walk 0x1417c8aa0

- The argument at `rdx` is the only thing the assert guards (line 0x172, 0x141824ca8 / 0x141827b98 /
  0x14183a778 / 0x141839fe0), and its branch answers zero without touching the tree.
- Two different pointers drive the walk: the **cursor** comes out of the holder at `+0x38` through
  its first qword, the **end** is the holder itself, and the element tested is `0x20(cursor)` after
  0x14178f470 hands it over and 0x1418232b0 answers with the third argument `0x10`. A zero answer
  returns that element.
- The step is the 0x29 climb/descend: `0x10` then the left spine, or `0x8` while the parent's
  `0x10` still names the node we came from; a flagged cursor fires the DEBUG check and loops.
- Test note: the first three attempts crashed because the element, the lead and the cursor live on
  different nodes — reading `0x20(node)` instead of `0x20(cursor)` walks straight into a null
  child. 12 checks, 6 passes, ASan+UBSan clean. Cluster 236 bodies.

## D159 — the scored walk 0x1417c8c10

- Same frame shape as 0x1417c8aa0 but with two more registers carried: the best answer and its
  score, both zeroed before the walk. The score comes from 0x141798060 with the mode passed at
  `edx`, the comparison is **signed 32-bit** (`cmp %eax,%r13d` / `jge`), so only a strictly greater
  answer replaces the one held, and a walk that never scores answers zero.
- The argument is a mode, not a pointer, and nothing on this path is asserted.
- The step is the 0x29 descend (through `0x10`, then the left spine) and climb (`0x8` while the
  parent's `0x10` names the node left), both looping back to the frame's re-read of `0x38(%r14)`
  and `0x8(%r14)`.
- Test note: the descend walks the left spine of the node it lands on, so a second node needs its
  `0x0` link set as well; the first attempt crashed on exactly that read.
- 3 checks, 6 passes, ASan+UBSan clean. Cluster 237 bodies.

## D160 — four bodies, 0x1417c8d80 / 0x1417c8eb0 / 0x1417c8ed0 / 0x1417c8ef0

- 0x1417c8d80: the third of the three walks. It keeps **nothing**: every element at `0x20(cursor)`
  goes to 0x14179bf60 with the mode at `edx` and the answer is dropped. Cursor, end and the DEBUG
  checks are the same three the scored walk uses, and there is no assert on the mode.
- 0x1417c8eb0 / 0x1417c8ed0: the pair is `*(tree)` and the header — the first takes the header's
  **first qword**, the second the header **itself**, and the two stores are in opposite order.
- 0x1417c8ef0: the clear. Each node on the `0x0` chain has its `0x10` subtree destroyed through
  0x1417c7a50 first, then goes to 0x1417f2fdc; afterwards the header names itself in all three
  links and `+0x38` is zeroed. The test counts two frees for a two-node chain and checks all four
  slots.
- `g_pfnSynPerElem_14179bf60` is new (element, mode -> void, null by default).
- `tests/syndicate_d160_test.cpp`: 12 checks, 6 passes, ASan+UBSan clean. Cluster 241 bodies.

## D161 — the leaf generator, 644 bodies in one translation unit

- `tools/family_gen.py` reads an objdump of the binary, splits bodies at `ret` and at padding gaps,
  and keeps only the functions whose **whole** body is one leaf template: `ret`, `xor eax,eax`,
  the identity move, a `movabs`/`mov $imm,%eax` constant, a `mov 0x..(%reg),%reg` field read, the
  same read plus an `add $imm`, a `lea 0x..(%reg),%reg`, and the zero-store that returns its own
  argument. Anything else is skipped, so nothing is guessed.
- 644 bodies came out of 11,928 functions: 185 address reads, 166 empty, 117 field reads, 85
  constants, 64 field-read-plus-bias, 27 zeros. `g_synLeafTable` carries each address, kind and
  arguments, so `tests/syndicate_d161_test.cpp` walks all of them in one pass.
- `(%rip)` reads are **excluded**: the first run crashed at 0x1417d5340 because
  `mov 0xb1b59(%rip),%rax` was read as a field of the argument. A global read is not expressible
  without the image loaded, so those bodies stay for the hand pass.
- The leaf table is one shape family written once and tabulated 644 times; it is the pattern for
  the remaining families (deleters, allocators, thunks).
- 644 checks, 6 passes, ASan+UBSan clean. Cluster 241 hand bodies + 644 generated.

## D162 — the forwarder family, 832 generated bodies

- The generator now splits bodies at `jmp` as well as `ret`, so a tail call stands alone, and it
  keeps a body as a **forwarder** when that body is a single forward jump whose resolved target
  objdump prints. 126 such bodies came out of the image; the four integer argument registers are
  handed to the target through `g_pfnSynTailCall` and the answer is returned unchanged.
- Limit, stated plainly: the forwarder carries `rcx`/`rdx`/`r8`/`r9` only. A target that reads
  `xmm` arguments is not reproduced by this shape, and those bodies stay for the hand pass.
- The generator now writes a complete, compilable unit itself (include, seam, casts, 64-bit
  literals), so `tools/family_gen.py` reproduces `genleaf.cpp` from the binary alone.
- The table is 832 bodies: 223 address reads, 178 empty, 126 forwarders, 120 field reads, 91
  constants, 64 field-read-plus-bias, 30 zeros. All 832 are walked and checked, 6 passes, ASan and
  UBSan clean.

## D163 — the NpcServer.exe scaffold

- `Docs/NPCSERVER_PATHS.md` lists the **50** source paths the binary embeds, all extracted from
  `NpcServer.exe` itself: 22 under `version/cqserver-78.0.11-1204/npcserver/npckernel`, 12 under
  its `network` folder, 5 under `include/basecode`, 4 at the npcserver root, and the rest in
  `include/db`, `comm`, `mapdata` and protobuf's `io` folder.
- All 50 are scaffolded under `modules/npcserver/src/` with their exact relative paths, a header
  guard and an empty `tq` namespace. No body is written: the scaffold only fixes the tree so the
  port has the original layout from its first unit, which is the same rule the Syndicate module
  followed.
- The tree is 34 translation units and 16 headers today.

## D164 — the slot family, and a correction to D162

- Correction: the 126 bodies called forwarders in D162 are **not** direct tail jumps. Their operand
  is `jmp *0x..(%rip)` and the resolved address objdump prints is the **slot**, not the callee, so
  the family is an indirect-slot thunk. `0x1417f2fdc` is the clearest example: its body is
  `jmp *0x3040e(%rip) # 0x1418233f0`, i.e. one load from a slot. The kind is now `slot` and the
  seam is per slot, not per message.
- `Docs/SEAMS.md` counts where the image calls out: **99** indirect slots with **7,238** call
  sites, and **2,340** direct targets with **13,703** sites. Two slots dominate: `0x1418233c0`
  (3,728 sites, `invalid_parameter_noinfo`) and `0x141823030` (776, the custom assert handler).
  The heaviest direct targets are themselves slot thunks: `0x1417f2fdc` (875 sites) jumps through
  `0x1418233f0`, and `0x1417f3166` (548) through `0x1418232a0`.
- `g_synSlotAddr` / `g_synSlotFn` carry one seam per slot (126 today), so a build wires a slot once
  and every thunk through it comes alive together.
- 832 bodies, all walked: 223 address reads, 178 empty, 126 slot thunks, 120 field reads, 91
  constants, 64 field-read-plus-bias, 30 zeros. 6 passes, ASan and UBSan clean.

## D165 — NpcServer.exe, the front of the image (8 bodies)

- `modules/npcserver/src/npckernel/imagefront.cpp`: the bodies that precede the first
  `__FILE__`-attributed function, in address order.
  - `0x140001020` stores `std::tr1::_Ref_count_base::vftable` into its argument.
  - `0x140001040` is the refcount release: `--*(this+0x14)` and, at zero, slot 1 of the object's
    table called with `this`.
  - `0x140001060` returns 0.
  - `0x140001070` stores the same vftable, then deletes when the low byte is set, returning `this`.
  - `0x1400010b0` is `log_InlineLogERROR(&DAT_1400be0b0)`.
  - `0x1400011d0` is `Ordinal_116(); return 1;` (WSA cleanup).
  - `0x1400011f0` deletes a non-null pointer through `operator_delete__`.
  - `0x140001210` clears `+0x10`, then `memset(this+0x14, 0, 0x800)`, then writes
    `+0x818 = -1`, `+0x814 = 0`, `+0x830 = 0`, `+0x820 = 0`, `+0x828 = 0`, and `*this = 0`, in
    that order; the test checks the bytes past `+0x830` stay untouched.
- The file name is **ours**: the image prints no path for these bodies, so they are kept together
  by address and the PORTING_LOG says so. Seams: `operator_delete`, `operator_delete__`,
  `log_InlineLogERROR`, `Ordinal_115` (WSAStartup), `Ordinal_116` (WSACleanup).
- `tests/npcserver_d165_test.cpp`: 20 checks, 6 passes, ASan+UBSan clean.

## D166 — NpcServer.exe 0x140001130 .. 0x140001440 (6 bodies)

- `0x140001130` `WSAStartup(2, &data)`: returns 0 on a non-zero result or when `data[0] != 2`, and 1
  otherwise; the two log strings are `"ERROR: Init WSAStartup() failed."` and
  `"ERROR: WSAStartup Version not match 2.0"`.
- `0x140001280` deletes its argument only when the low byte is set, and returns the argument either way.
- `0x1400012a0` consumes `nBytes` from the receive buffer at `+0x14`: it logs `&DAT_1400be0b0` when
  `nBytes` exceeds `+0x814`, and only acts when `+0x830 == 2`.
  **Deviation, stated:** the original calls `memcpy` with the destination inside the source range.
  The port copies forward byte by byte, which is what the CRT call does here and is defined
  behaviour; without it the sanitisers abort on the overlapping range.
- `0x140001340` frees `+0x820` when it is non-null, clears `+0x830`, and writes `-1` to `+0x818`.
- `0x140001390` is `CClientSocket::SendPacket`. Its strings are
  `"CClientSocket::SendPacket, bufferevent_write packet failed[%d]."` (only when the socket errno is
  not `0x2746`) and `"CClientSocket::SendPacket, invalid socket failed."`. Ghidra's `CONCAT31`
  returns on that path are the low byte of a boolean: 1 on a written packet, 0 otherwise.
- `0x140001440` returns `*(int *)(param_1 + 0x830) == 2`.
- `tests/npcserver_d166_test.cpp`: 26 checks over the success, failure, tolerated-errno and
  not-connected paths; 6 passes, ASan and UBSan clean.

## D167 — attribution evidence, and three retractions

- **The image cannot attribute a body to a translation unit.** Its 49 source-path strings
  (`\version\cqserver-78.0.11-1204\...`, first `clientsocket.cpp`) are dead data: a grep over the
  whole disassembly finds **zero** references to any of their addresses. So there is no evidence
  linking 0x140001130.. to `clientsocket.cpp`, and no such placement is claimed.
- Retraction 1: `modules/npcserver/src/npckernel/imagefront.cpp` was a path of ours, not the
  original's. It is gone; the unit now lives at `modules/npcserver/unattributed/front-of-image.cpp`,
  outside `src/`, so it cannot be mistaken for an original path. The header says why in its first
  lines.
- Retraction 2: the semantic symbol names (`NpcRefCountCtor`, `NpcSendPacket`, ...) were ours. Every
  body is back to the decompiler's own `FUN_<address>`, which is the only name the evidence carries.
- Retraction 3: `g_symNpcRefCountBaseVftbl` followed Ghidra's library signature for
  `std::tr1::_Ref_count_base::vftable`. The instruction is `lea 0x1400be090,%rax`, and the name index
  ties `0x140001000` to `CChatThread::ctor_or_dtor` through that same table, so the symbol is
  `g_symNpcVftbl_1400be090` and no class name is asserted from a decompiler annotation.
- What the name index does give, and is now used as-is: `0x140001000 CChatThread::ctor_or_dtor`,
  `0x140001050 CChatThread::ctor_or_dtor`, `0x1400010e0/1110/11b0 CChatThread::vfunc_1..3`,
  `0x1400013f0 CChatThread::ctor_or_dtor`. Note the mixture: `0x140001390` logs
  `"CClientSocket::SendPacket, ..."` inside that same address range, so the region is not one class
  and no placement is inferred from it.
- Both suites still pass 6 times each (D165 8 bodies / 20 checks, D166 6 bodies / 26 checks).

## D168 — NpcServer.exe 0x1400014d0 and 0x140001520 (2 bodies)

- `0x1400014d0`: frees `+0x820` when set, clears it, writes `-1` to `+0x818`, clears `+0x830`, then
  `operator_delete(this)`. The test snapshots the object *inside* the delete seam and confirms those
  three fields are already in their final state when the delete happens, which is the order the
  decompiled body shows.
- `0x140001520` is `CClientSocket::Open`, ported with its six strings intact:
  `"CClientSocket::Open, bufferevent_socket_new error[%d], at %s, %d."`,
  `"CClientSocket::Open, bufferevent_socket_connect error[%d], at %s, %d."`,
  `"CClientSocket::Open, bufferevent_getfd error[%d], at %s, %d."`, plus `&DAT_1400be0b0` (three
  sites) and `&DAT_1400be2d8`.
- The sockaddr local is reproduced byte for byte: `family = 2` at +0, `Ordinal_9(*(u16*)(this+0x10))`
  at +2, the resolved address at +4, and a zero qword at +8, passed with length `0x10`. The test
  reads those bytes back through the connect seam.
- Finding worth recording: `iVar3 = *(int *)**(undefined8 **)(lVar4 + 0x18)` is **three** reads
  (the slot, then the pointer it holds, then the int). A first test fixture that stopped after two
  made ASan report a stack overflow, which is how the extra dereference was caught.
- Success path writes the original's byte stores: `+0x814..+0x817 = 0` and `+0x830 = 2`,
  `+0x831..+0x833 = 0`, and returns 1. State 2 returns 1 immediately; any other state returns 0.
- Seams added: `Ordinal_11`, `Ordinal_52`, `Ordinal_9`, `Ordinal_111`, `FUN_1400022c0`,
  `FUN_14000b3e0`, `FUN_140005a50`, `FUN_14000b9f0`, `FUN_140006200`, and the value symbols
  `DAT_140002370`, `FUN_1400022f0`, `FUN_140002380`, `DAT_1400be2d8`.
- `tests/npcserver_d168_test.cpp`: 32 checks; D165, D166 and D168 each pass 6 times under ASan+UBSan.

## D169 — the first body placed by its own evidence: clientsocket.cpp

- `FUN_1400017b0` @ `0x1400017b0` lands in
  `modules/npcserver/src/version/cqserver-78.0.11-1204/npcserver/clientsocket.cpp`, and the evidence
  is inside the body: it calls
  `log_InlineLogERROR(&DAT_1400be0b0, "CHECK", "m_pKernelThread",
  "f:\version\cqserver-78.0.11-1204\npcserver\clientsocket.cpp", 0x184)`. The path with its drive
  letter, the two expressions, and the lines `0x184`, `0x187`, `0x1a7` are all reproduced verbatim.
  This is the standard the other bodies wait for: a path from the binary, not from us.
- Checks in the original's order: buffered count must be `>= 1`, then `>= 9`, then
  `>= *(u16*)(this+0x14)`, then the packet length must be `>= 4` and `<= 0x400`. The payload starts
  at `this+0x1c`, the length handed to the virtual call is `size - 8`, the id is `*(u16*)(this+0x16)`
  and the fourth value is `*(u32*)(this+0x18)`.
- The analyst is bracketed exactly as in the source: `CTickAnalyst::CTickAnalyst(local, 0x4e)`,
  the virtual call through slot `+0x18` (index 3), then `CTickAnalyst::~CTickAnalyst(local)`.
- `IF_NOT "this->ClearPacket(nNetPacketSize)"` at `0x1a7` is reachable: when the virtual call leaves
  the socket out of state 2, `FUN_1400012a0` returns 0 and the loop logs it. The test drives that
  exact path (the slot clears `+0x830`), rather than assuming it is dead code.
- The inline-log seam is now variadic (`const void* pMsg, ...`) so the assert form travels through
  the same seam as the plain messages; the three earlier suites were rebuilt and re-run against it.
- `tests/npcserver_d169_test.cpp` covers the two CHECK paths, four early returns, one full packet
  (analyst id `0x4e`, four-byte payload, twelve bytes consumed) and the IF_NOT path.

## D170 — NpcServer.exe 0x140001970 .. 0x140001ba0 (8 bodies)

- `0x140001970`: releases the counted object at `+8`. One decrement of the int at `+0x10`; on zero it
  calls slot 0 of that object's table, then decrements the int at `+0x14` and calls slot 1 when that
  reaches zero. The test pins the order (slot 0 before slot 1).
- `0x1400019b0`: assignment. Bumps the incoming object's `+0x10` first, releases the old one exactly
  as above, and stores both words in **every** branch (the decompiled body repeats the two stores
  inside the branch and after it).
- `0x140001a50`: stores the table at `0x1400be090`, then `param_2` at `[1]`, `0` at `+0x10`, `1` at
  `+0x14`, then overwrites `[0]` with the table at `0x1400be3f0` and stores `param_3` at `[4]`. Both
  table addresses come from the body's two `lea` instructions.
- `0x140001ab0`: `type_info::operator==` against the descriptor at `0x140102090`; returns `this+0x20`
  or 0. The descriptor address is the body's `lea` operand, not a decompiler annotation.
- `0x140001af0`: calls the pointer at `+0x20` with the value at `+8`.
- `0x140001b00` and `0x140001b40`: store the table at `0x1400be090`; `1b40` deletes on the low byte
  and returns its argument.
- `0x140001ba0` is `CClientSocket::Create`, and it is placed in
  `src/version/cqserver-78.0.11-1204/npcserver/clientsocket.cpp` because its own log call passes
  `"f:\version\cqserver-78.0.11-1204\npcserver\clientsocket.cpp"` with line `0x81`. Its other
  strings, by address: `0x1400be540` `"CClientSocket::Create, m_pKernelThread is NULL."`,
  `0x1400be520` `"config.ini"`, `0x1400be530` `"GameServer"`, `0x1400be510` `"GAMESERVER_IP"`,
  `0x1400be500` `"GAMESERVER_PORT"`, `0x1400be488` `"CClientSocket::Create, NpcServer client socket
  Open error."`, and `0x1400be4c8` the port message (GBK text, carried as an address symbol).
- Behaviour recorded as found: `0x140001ba0` returns **1** on both post-open outcomes (open failed or
  opened) and 0 only for a NULL kernel thread. It reads the port, defaults to `0x16b8` when the ini
  gives 0, and stores `port + 4` at `+0x10`.
- `0x1400be090` is the same table D165 ported at `0x140001020`; the symbol is shared by address, and
  no class is claimed for it.
- `tests/npcserver_d170_test.cpp` drives every branch above; D165, D166, D168, D169 and D170 each
  pass 6 times against the same objects.

## D171 — NpcServer.exe 0x140001cb0 .. 0x140001fd0 (10 bodies)

- `0x140001cb0` `CClientSocket::ProcessAllIncoming`: when `+0x820` is null it logs `&DAT_1400be0b0`
  and returns; only state 2 proceeds; more than `0x7ff` buffered forces `0x1400017b0` first. The read
  destination is `this + 0x14 + *(int *)(this+0x814)` and the length is `min(0x800 - count, available)`.
  A read of zero or less reports `*(long long *)(this+0x818)` through `0x140007540`, logs
  `"CClientSocket::ProcessAllIncoming, bufferevent_read err[%d]."`, then resets with `0x140001340`.
  It stays in `unattributed/` because the body names the class but carries no path literal.
- `0x140001db0` is byte-for-byte the release at `0x140001970` at a second address. Both are ported as
  separate functions rather than folded together, because the binary really does hold two copies.
- `0x140001df0` copy-assign, `0x140001e10` release-then-clear (both words cleared in every branch),
  `0x140001ea0` allocates `0x28` through `operator new`, fills the two table words, the two counters
  and `[4]`, then assigns through `0x1400019b0`.
- `0x140001f20` calls slot `+0x10` of the object's table with `(this, 0)` and then deletes it.
  `0x140001f40` releases the counted object at `+0x10`.
- `0x140001f90` clears both words **first** and then calls `0x140001e10`, so its release never runs.
  The test asserts exactly that (the reference count stays where it was) instead of assuming a release.
- `0x140001fb0` clears, then allocates and assigns through `0x140001ea0`.
- `0x140001fd0` is the buffer owner: it clears `[2..5]`, releases through `0x140001e10`, allocates the
  payload with `operator_new__`, wraps it in a counted block whose deleter is `0x1400011f0`, drops the
  temporary reference, then either stores 0 (no payload) or copies the caller's bytes into the payload
  and records the size in `[0]`. The payload lands at `this+8` and the counted block at `this+16`.
- Two structural details had to be reproduced rather than approximated: `0x140001ea0` writes
  `local_40` and `local_38` as one two-word owner, so they are one array in the port (two scalars made
  ASan report a stack write past the first); and the counted block's counters must be bumped before
  the assignment, which is why the block reads `1` at `+0x10` after `0x140001ea0` returns.
- `tests/npcserver_d171_test.cpp` drives all ten; D165, D166, D168, D169, D170 and D171 each pass 6
  times against the same objects.

## D172 — NpcServer.exe 0x1400020d0 .. 0x140002630 (26 bodies)

- Ten are trivial: `0x1400020d0` and `0x140002270` return; `0x1400020f0`, `0x140002130`, `0x140002170`,
  `0x1400021b0`, `0x1400025b0`, `0x1400025f0` log `&DAT_1400be0b0` (the last two also return 0).
- `0x1400021f0` and `0x140002540` store the table at `0x1400be730` into the object and the table at
  `0x1400be6f8` into `+0x40`, then call `CThreadBase::~CThreadBase`; `0x140002540` also deletes on the
  low flag bit. Both table addresses are the bodies' own `lea` operands.
- `0x140002230` .. `0x140002260` are the same three instructions with a different slot offset
  (`0x0`, `0x8`, `0x10`, `0x18`). The machine code is `mov 0x8(%rcx),%rcx; mov (%rcx),%rax;
  jmp *0xN(%rax)`: the word at `+8` is the **object**, and that object's **first word** is the table.
  Reading the slot off the object instead of its table is what a first pass of this unit got wrong, and
  the suite caught it as a segfault. The load also leaves the object in `rcx`, so the callee receives
  it as its first argument.
- `0x140002280` and `0x140002290` forward to `0x140001390` and `0x140001440` through `+0x20`.
  `0x1400022a0` forwards four values to the object at `+0x58` when it exists; `0x1400022c0` returns
  that word and `0x1400022e0` returns `+0x68` (the two words the earlier clientsocket bodies read
  through seams).
- `0x1400022f0` is the read callback: one fd, then one dispatch with `1`, `0x1fbd1`, `8` and the fd's
  address, through the object at `+0x50` and slot `+0x50`.
- `0x140002380` is `CKernelThread::BufferEventCb` with its two strings: bit 7 enables with `6` and
  logs `"CKernelThread::BufferEventCb, bufferevent_enable error[%d]."` on failure, the `0x30` bits
  dispatch with `0x1fbd2`, anything else logs
  `"CKernelThread::BufferEventCb, events[%0x] error."`.
- `0x140002450` stores `TimeGet(0) / 1000` at `+4` and returns the magic-multiply residue the body
  leaves in `eax` (`uVar1 * 0x10624dd3`); `0x140002480` compares the stored sum against `TimeGet(0)/1000`
  and returns that as a boolean.
- `0x1400024f0` logs `"EvnetRoutine worker thread is up and running"` and
  `"EvnetRoutine worker thread exited"` around the four-value forward, misspelling included.
- `0x140002630` is `CKernelThread::OnDestroy`: release `+0x68` through its slot `+0x10`, release
  `+0x60` through `0x140001340` and then `0x1400014d0`, exit the loop with `2`/`0`, log
  `"CKernelThread::OnDestroy, event_base_loopexit error."` when that fails, `Sleep(0x9c4)`,
  `CloseHandle(*(+0x70))`, free the base and zero it, call `0x140012190`, then slot `+0x30` of `+0x50`.
- Casting rule learned here and applied across the file: a **stored function value** must be cast to a
  plain function pointer, while `(*(T **)addr)` is only right when `addr` is the **address of the
  slot**. Four call sites in this unit used the latter form on the former and dereferenced the code
  itself; the audit found no such site elsewhere in the tree.
- `tests/npcserver_d172_test.cpp` drives all 26; seven suites (D165, D166, D168, D169, D170, D171,
  D172) pass 6 times each against the same objects.

## D173 — NpcServer.exe 0x140002700, 0x140002760, 0x140002790 (3 bodies)

- `0x140002700` is the deadline helper. It reads `TimeGet(0)`; when the stored total
  `*(int*)+*(int*)[1]` is at or past `uVar1 / 1000` it reads the clock a **second** time, writes that
  second into `[1]` and returns the magic-multiply residue with the low byte set to 1. Otherwise it
  returns the residue with that byte clear, so the low byte alone answers "was it due".
- `0x140002760` stores the value and the current second (`TimeGet(0) / 1000`) and returns
  `uVar1 * 0x10624dd3`, the residue the body leaves in `eax`.
- `0x140002790` is `CKernelThread`'s constructor: `CThreadBase::CThreadBase` first (through the seam),
  then the table at `0x1400be730` into the object, the table at `0x1400be6f8` into `+0x40`, both
  half-words at `+0x78` and `+0x7c` to zero, and the six words at `+0x48`, `+0x50`, `+0x58`, `+0x60`,
  `+0x68`, `+0x70` to zero. Those are eight-byte stores, so `+0x74` is inside the `+0x70` one.
- `tests/npcserver_d173_test.cpp` drives all three; the whole NpcServer set (D165 to D173) passes.

## D174 — NpcServer.exe 0x140002d70 (CLogThread constructor)

- `CThreadBase::CThreadBase` first (through the seam), then the table at `0x1400bed00` into the object,
  `+0x40` cleared, the value in `+0x48`, and, only when a name is passed, `tq::SafeCopy(+0x50, name,
  0x80)`. A null name leaves `+0x50` untouched. The table address and the copy's `r8d` are the body's
  own operands (`lea 0xbbf5c(%rip)` and `mov $0x80,%r8d`).
- `tests/npcserver_d174_test.cpp` checks the store order (the base sees no table yet), the cleared word,
  the handle, the destination pointer, the source and the 0x80 capacity.

## Deferred: 0x1400027f0 CKernelThread::OnProcess()

- Read in full (132 lines, `0x500`-byte frame) and deliberately not ported yet. It is the only body in
  this stretch whose behaviour depends on a structure this project has not modelled:
  - the receive call `slot +0x48(obj, -1, -1, 0x418)` fills a **packet header** the body then reads as
    `local_4b8[4]` plus an `int` type compared against `0x1fbd1` and `0x1fbd2`, and `local_438[0]`
    holding the fd (-1 short-circuits each branch);
  - three `CTickAnalyst` scopes (`0x4c`, `0x4d`, `0x4f`, `0x50`) wrap the loop, the packet branches and
    the tick call, so their constructor/destructor pair is part of the body's shape;
  - it also walks the watchdog counters at `+0x78`/`+0x7c`, the static tick clock `DAT_140103c60` /
    `DAT_140103c64`, the three atomic statistics `_DAT_140103f28`, `DAT_140103f2c`, `DAT_140103f30`, and
    the adaptive loop delay `DAT_140102148`.
- Writing it now would mean inventing the packet header layout, which this project does not allow, so it
  waits for the receive seam and the packet header to be modelled (the `0x418` buffer bound is the first
  thing to pin down).
- `0x140002b30` (thread launcher, `_SYSTEM_INFO`) follows it and is deferred for the same reason: it
  launches the worker and needs the same objects.

## D175 — NpcServer.exe 0x1400027f0 CKernelThread::OnProcess()  (the D174 deferral, resolved)

- The receive slot is pinned from the machine code at `0x140002887`..`0x1400028ab`: `rdx = r8 = -1`,
  `r9 = 0x418`, and the two stack arguments are `lea 0xd0(%rsp)` and `lea 0x50(%rsp)`. So the call is
  `slot+0x48(obj, -1, -1, 0x418, body, header)` where `body` is the `0x418`-byte buffer whose **first
  eight bytes are the fd** (`cmpq $-1,0xd0(%rsp)`) and `header` is two ints, the second of which is the
  packet type read at `0x54(%rsp)` and compared with `0x1fbd1` / `0x1fbd2`. That resolves the deferral:
  no layout was guessed, the offsets are the body's own stack slots.
- Strings, taken from the image's `.rdata`: `0x1400beab0` = "CKernelThread::OnProcess(), pointer is null.",
  `0x1400beb30` = "CKernelThread::OnProcess(), packet[%d]." (the type is the argument),
  `0x1400beb08` = "Connect to game server again . . .", and `0x1400beae0` is GBK, not ASCII:
  the bytes are `ca b1 d6 d3 c6 ab d2 c6 25 64 c3 eb` = "时钟偏移%d秒" (clock drift %d seconds). It is
  stored byte for byte, so the suite compares pointers, not text.
- The work query is `slot+0x58(obj, DAT_140102148)`; the loop body is the packet dispatch; then
  `0x140001440` is asked whether the link is still up and, only when it is not and `+0x7c` is set, the
  deadline pair at `+0x78`/`+0x7c` is checked and the reconnect sequence runs: slot `+0x8` of `+0x68`,
  slot `0` of `+0x48` with the message above, then `0x140001520`.
- The tick: `DAT_140103c64` bit 0 guards the one-time `DAT_140103c60 = TimeGet(0)`. The delta is
  `TimeGet(0) - DAT_140103c60`; when it exceeds 99 the clock advances by exactly 100 while it is under
  `0x2711`, and past that the GBK warning is logged and the clock jumps to the current value. Either way
  a `0x50` scope wraps the `slot+0x20(obj68, now)` tick call.
- Statistics: `_DAT_140103f28` is incremented, `DAT_140103f2c` gets the elapsed time (`lock xadd`),
  `DAT_140103f30` keeps the maximum, and `DAT_140102148 = 50 - DAT_140102148 - elapsed` clamps to 1.
  The analyst scopes are `0x4c` for the loop, `0x4d` for type `0x1fbd1`, `0x4f` for `0x1fbd2`, `0x50`
  for the tick; the body always returns 1.
- `tests/npcserver_d175_test.cpp` asserts the null guard, the `0x418` bound, three packets, the scope id
  order `4c/4d/4f/50`, four destructors, the single `packet[0x1234]` log, the fd-1 short circuit on both
  branches, the clock landing on 1300, the tick argument, and the three counters.
- The analyst seams already live in `clientsocket.cpp`, so this unit only declares them.

## D176 — NpcServer.exe 0x140002b30 CKernelThread::Create()

- The body stores the socket table at `+0x48` and the object at `+0x50`, then calls slot `+0x38` of
  `*(param_3)` and slot `+0x40` of `*(param_3)` with `0x1e`. Note both are one dereference only: the word
  at `param_3` **is** the table, unlike the two-level objects in D172.
- Then the libevent sequence: `event_config_new` (`0x140012580`), flag `4` (`0x140010a00`), `GetSystemInfo`,
  the processor count read at `+0x20` of `_SYSTEM_INFO` and handed to `0x140010a20`, the base from
  `0x140015ed0` stored at `+0x58`, the config freed by `0x140012660`, the method name from `0x140010d80`
  logged as "libevent method: %s", the engine from `0x14001d350` stored at `+0x68` and asked to accept
  `+0x40` through its slot 0 (slot `+0x10` on refusal).
- Then the socket: `operator_new(0x838)`, `0x140001210` (the ctor), `0x140001ba0` (the open) with the
  thread as its second argument; on either failure the message "CNpcWorld::Create, cannot create NpcServer
  client socket." and the socket released through `0x1400014d0` and cleared.
- Then the worker: `_beginthreadex(0, 0, 0x1400024f0, this, 0, 0)` into `+0x70`, `_errno()` on failure,
  otherwise `GetThreadId` / `GetCurrentThreadId` logged as "thread %u created libevent worker thread %u"
  (current id first), `+0x78 = 1`, `+0x7c = TimeGet(0) / 1000`, and `CThreadBase::CreateThread(this,
  "NPC Server KernelThread", flag)`, whose result is the return value.
- Fifteen seams were needed for the libevent layer and the thread API; none of those bodies is ported yet
  and they are all null-checked, so the unit links and runs without them.
- `tests/npcserver_d176_test.cpp` asserts the argument guard, the four failure messages, the engine
  refusal path, and the full fifteen-step order up to the `0x838` allocation. The successful thread path
  needs a live socket and is not exercised here.

## D177 — NpcServer.exe 0x140005750 (handler registration)

- Two `0x28`-byte tables on the frame at `rsp+0x20` and `rsp+0x48`, each `{ int nFirst = 1; int nSecond = 1;
  void (*pfnHandler[4])(void); }`, filled with the addresses `0x140005400`, `0x140005450`, `0x140005470`,
  `0x1400054a0` and `0x1400054d0`, `0x140005560`, `0x140005590`, `0x1400055f0`.
- `0x140016890(&s1, a2, a3, a4)`, then `0x140016880(&DAT_1400054c0)`, then `0x140016990(&s2, a2, a3, a4)`;
  the body returns 0. Its first argument is dropped: the `lea` into `rcx` overwrites it.
- `DAT_1400054c0` is a fixed image address, so it is modelled by `g_symNpcData_1400054c0`, the same
  placeholder convention as the stored-table symbols.
- The eight handler bodies are not ported yet, so their addresses are kept as the literal values the
  original stores (the `NPCSERVER_HANDLER_ADDR_*` constants) rather than as symbols. This keeps the unit
  linkable without inventing eight bodies; when they are ported the constants become their addresses.
- `tests/npcserver_d177_test.cpp` checks the call order, both tables' two ones, all eight addresses, the
  data pointer and the three forwarded arguments, plus the zero return with no seams wired.

## D178 — NpcServer.exe 0x140016880, 0x140016890, 0x140016990 (libevent thread callbacks)

- The callback record is `0x28` bytes: two header ints then four handler pointers. `0x140016880` stores its
  argument in `DAT_140103fe0` and returns.
- `0x140016890` picks its target from `DAT_140103fb0`: `DAT_140104010` while the flag is set, otherwise
  `DAT_140103fb8`. A null request warns with "Trying to disable lock functions after they have been set up
  will probaby not work." (the original's spelling) when the table is already set, clears all `0x28` bytes
  and answers 0. A first request needs all four pointers, is copied whole and is followed by
  `0x1400121b0(1, 0)`; an identical repeat answers 0; anything else warns "Can't change lock callbacks
  once they have been initialized." and answers -1.
- `0x140016990` is the condition registrar against `DAT_140103fe8` / `DAT_140104038`. It differs in two
  ways that the machine code makes explicit: the equality test compares the first header int and the four
  pointers but **not** the second int, and while `DAT_140103fb0` is set the first three pointers are also
  echoed to `DAT_140103ff0`, `DAT_140103ff8` and `DAT_140104000`. Its refusals answer `0xffffffff`.
- The four messages were re-extracted from `.rdata`; the lock-change one sits behind a `0xE0` byte with no
  terminator between, so the string is taken from its first byte onward.
- `tests/npcserver_d178_test.cpp` covers the empty table, the first request plus follow-up, the identical
  repeat, a changed pointer, a request with a hole, disabling a set table, both debug-flag targets, the
  condition registrar's ignored second word and the three echoed pointers.

## D179 — NpcServer.exe 0x140005400 .. 0x1400055f0 (the eight registered handlers)

These are libevent's Windows threading shims. A lock is a bare `0x28`-byte `CRITICAL_SECTION`; a condition is
`0x40` bytes: the handle at `+0`, the section at `+8`, then `nWaiters` at `+0x30`, `nSignals` at `+0x34`
and `nWaitCount` at `+0x38` (the offsets the code itself uses: `param_1 + 6`, `param_1 + 7`, `+0x34`).

- `0x140005400` allocates `0x28`, initialises with a spin count of **2000**, and frees on failure.
- `0x140005450` releases the section then the block.
- `0x140005470` tests flag `0x10`: the try form answers `TryEnterCriticalSection(...) == 0` (a failed try is
  reported as held), otherwise it enters and answers false.
- `0x1400054a0` leaves the section and answers 0.
- `0x1400054d0` allocates `0x40`, initialises the section at `+8` with spin **2000**, creates a manual-reset
  event (`CreateEventA(0, 1, 0, 0)`) into `+0`, and only then clears the three counters; a missing handle
  releases the section, and every failure frees the block.
- `0x140005560` releases the section, closes the handle, then frees.
- `0x140005590` signals: a single wake increments `nSignals`, a broadcast sets it to `nWaiters`, then
  `nWaitCount` advances and the event is set.
- `0x1400055f0` waits: the timeval is converted by `0x140016450`, the waiter is counted, the caller's lock is
  released, and each round re-computes the remaining interval from `GetTickCount`; running past
  `start + timeout` answers 1, a `WAIT_TIMEOUT` (`0x102`) answers 1, any other wait failure answers
  `0xffffffff`, and a consumed signal answers 0. The last waiter resets the handle.
- `0x140005750` now stores the real addresses of these eight bodies instead of the placeholder constants, so
  the registration is wired end to end; the D177 suite compares against the same symbols.
- Tests: `tests/npcserver_d179_test.cpp` (allocation and failure paths, the try flag, the counters, signal and
  broadcast, and three wait outcomes: deadline, signalled, timeout plus a generic failure).

## D180 — NpcServer.exe event_config and selector wrappers

- `0x140012580` (`event_config_new`) takes `0x30` bytes either from `calloc(1, 0x30)` or, when the hook
  `DAT_140103f98` is installed, from that hook followed by six cleared words; both paths write the same five
  fields and both set errno to `0xc` on failure. The layout the body proves: entry-queue head at `+0` with
  its tail pointer at `+8` pointing at the head **itself**, processor hint at `+0x10`, dispatch interval at
  `+0x14` (`0xffffffff`), callback limit at `+0x1c` (`0x7fffffff`), priority limit at `+0x20` (`1`). That is
  the 2.1 `event_config` with a TAILQ head first, which is why `+8` holds the object's own address.
- `0x140010a00` OR-s the word at `+0x28` (the flags; `0x140015ed0` copies exactly that word to base `+0x1f8`
  and tests bits `2` and `0x20`), answering `0xffffffff` for a null config.
- `0x140010a20` stores the processor hint at `+0x10`, same null answer.
- `0x140010d80` is `event_base_get_method`: the base's first word is the selector and the selector's first
  word is the method name.
- `0x14001d350` allocates `0x68` and hands it to `0x14001ced0`, answering nothing if the allocation fails.
- The hook is typed as taking the size, because the calloc path asks for `0x30` and the hook replaces it
  one-for-one; the decompiler dropped that register.
- `tests/npcserver_d180_test.cpp` covers both allocation paths of the config (including errno `0xc`), the two
  setters with their null answers, the selector indirection, and the factory with a failing allocation.

## D181 — NpcServer.exe 0x140012660 (event_config_free)

- Straight from the instructions, not the pseudo-code: each round reads `node->next` (`+0`) and `node->prev`
  (`+8`), and unlinks with `next ? next->prev = prev : cfg->tail = prev` followed by `*prev = next`. The tail
  word at `+8` is the address of the last node's `next` field, exactly as the TAILQ head in D180 implied.
- The name at `+0x10` is released first (when present), then the node, then finally the config itself.
- Every release goes through `DAT_140103fa8` when that hook is installed, otherwise to the runtime `free` at
  `0x1400bd548`. The hook is re-read after each call (the machine does `mov`, call, `mov` again), so a hook
  that rewires itself mid-walk is honoured; the port reproduces that.
- The config release is a tail jump: hook if installed, else runtime `free`.
- The nameless node is the interesting path: with a hook it still goes through the hook, and with no hook the
  `je` skips the name release and lands straight on the node release.
- `tests/npcserver_d181_test.cpp` checks the runtime path with one and two nodes (unlink arithmetic, the tail
  rewrite, the emptied queue), the hook path, and an empty config that releases only itself.

## D182 — NpcServer.exe 0x140015ed0 (event_base_new_with_config, 925 bytes)

- `0x2b0` bytes from the hook (then cleared by hand) or `calloc(1, 0x2b0)`; both failures set errno `0xc` and
  go straight to the report "%s: calloc" with "event_base_new_with_config".
- The config's flag word (`+0x28`) is copied to base `+0x1f8` **only on the branch that takes it**: the two
  flag probes are `& 2` (which decides whether the precise-timer probe runs at all) and `& 0x20` (which
  already claims precision). Only when neither holds is `EVENT_PRECISE_TIMER` read, and only then is `0x20`
  OR-ed into the base word.
- Fixed field map, all from the body: timer monitor `+0x168`, deferred queue `+0x150`/`+0x158`/`+0x15c`,
  three `-1` sentinels at `+0xa0`, `+0xa8` and `+0x210`, the priority queue head `+0x108` with its tail
  pointing at the head (`+0x110`), `+0x218`, then the three queue/registry constructors at `+0x128`,
  `+0x140` and `+0x10`.
- Dispatch limits: with no config the interval is `0xffffffff` and the callback limit 1; with a config the
  interval is copied as one 8-byte word from `+0x14`, the limit comes from `+0x20`, and `+0x204` is
  `0x7fffffff` when the config's `+0x1c` is negative. The settle rule then fires: a callback limit of
  `0x7fffffff` together with an interval of `-1` sets the limit **and** the priority word at `+0x208` to
  `0x7fffffff` (the priority word is read from `+0x20` first).
- Selector walk: the table at `DAT_140102480` is itself the first element. A selector is skipped when the
  config's avoid list holds its name (the byte loop with the delta index is preserved verbatim rather than
  replaced by a library compare) or when `(sel->features & cfg->require_features) != cfg->require_features`.
  Accepting it needs `!bVar4` or `0x140010860(name) == 0`, then base `+0` takes the selector and base `+8`
  takes `sel->init(base)`.
- No mechanism: "%s: no event mechanism available" and the selector word cleared, then the base is released
  through `0x140014b30` and the call answers nothing. A working base first probes `EVENT_SHOW_METHOD`
  (logged as "libevent using: %s"), calls `0x1400127e0(base, 1)`, and when `0x140016f00` agrees (and the
  config does not set bit 1) installs the notifier through `0x140016df0` / `0x140016e70` / `0x140015e70`,
  reporting "%s: Unable to make base notifiable." on failure. Finally flag bit 4 starts IOCP with the
  config's `+0x10` as the thread count, reporting "%s: Couldn't launch IOCP".
- `tests/npcserver_d182_test.cpp`: no memory, no selector (defaults, settle rule, tail pointer, release),
  one accepted selector, an avoided selector falling through to the next, a feature mismatch, IOCP with a
  failing launch, and the `0x20` flag suppressing the timer probe.

## D183 — NpcServer.exe ten helper bodies (D182's seams, part 1)

- `0x14001a190` clears `+0` and `+8` only; `0x14001ad50` clears `+0`, `+8`, `+0xc`; `0x14001a010` clears
  `+0`..`+0x10` and marks `+0x14` as `0xffffffff`. Nothing beyond those words is touched, which the suite
  checks with a `0xAA`-filled buffer.
- `0x140016f00` is just the flag `DAT_140103fd0`; `0x140016df0` calls the hook `DAT_140103fc0` when set, and
  `0x140016e70` calls the condition slot `DAT_140103ff0`. That last one is the **same word** the thread
  registrar in D178 fills from the condition callbacks, so the port reuses `g_pNpcCondCopy_140103ff0`
  instead of inventing a second global.
- `0x140010860` formats `"EVENT_NO%s"` into a `0x40` buffer and upper-cases from `buf+8`, which is exactly
  past the eight-character prefix, then asks the environment. The loop's exit test is on the *next* byte, so
  the last name character is still folded; the port keeps that shape and the suite counts five folds for
  "epoll".
- `0x140016640` clears `0x50` bytes, takes `GetTickCount64` and `GetTickCount` from kernel32 when flag bit 1
  is clear, stores the resolution routine's reading at both `+0x10` and `+0x20`, and with bit 0 set reads the
  performance counter into `+0x28`, writes `1` at `+0x38` and scales `+0x30` with the `.rdata` double at
  `0x1400c11b8`. That double is `1000000.0` (bits `0x412e848000000000`), read out of the image rather than
  assumed from the shape of the formula.
- `0x1400105b0` takes the notifier down when `+0x1d0` is set, answers the cached word at `+0x160` when it is
  non-zero, otherwise asks `0x140016720` and returns `0xffffffff` on `-1`. When the cached second at
  `+0x1c0` is more than five behind, it refreshes `+0x1b8` / `+0x1bc` from `0x1400163c0` and carries a
  negative microsecond difference by borrowing a second and adding `1000000` back.
- `0x140015e70` answers `0xffffffff` for a null base, cycles the notifier around `0x140014900`, and returns
  the install result truncated to 32 bits, so `-1` survives the round trip.
- `tests/npcserver_d183_test.cpp` covers all ten, including the borrow path and the timer scaling.

## D184 — NpcServer.exe 0x1400165d0, 0x1400163c0, 0x140016720, 0x1400127e0

- `0x1400165d0` (the tick reading) tries the resolved entry point at `+0`, then the fallback at `+8` whose
  result is folded as `(u & 0xffffffff) | ((u >> 0x12) & 0x3fff00000000)`, and only then `GetTickCount`
  with the wrap counter at `+0x18` bumped by `0x100000000` whenever a reading comes back lower than the one
  stored at `+0x10`.
- `0x1400163c0` (the wall clock) refuses a FILETIME at or below `0x19db1ded53e7fff`, otherwise shifts it to
  the 1970 epoch by adding `0xfe624e212ac18000`, divides by `10000000` for the seconds and by `10` for the
  sub-second field, which is then reduced modulo `1000000` in **32-bit** arithmetic. The modular constant is
  `0xFFF0BDC0`, not `0xFFFFF0C0`: subtracting a million is `2^32 - 1000000 = 0xFFF0BDC0`, and getting that
  byte wrong is what the first run of the suite caught.
- `0x140016720` (the monitor read) has two paths. Without the counter flag at `+0x38` the tick is divided by
  a thousand with the image's magic `0x0624dd2f1a9fbe77` and the sequence
  `(((x - hi) >> 1) + hi) >> 9`, which was checked against `x / 1000` over 100k inputs before being
  written. With the flag it scales the counter difference by the stored factor at `+0x30`, and when the two
  readings disagree by more than a second it rebases the stored counter using the `2^63` threshold read from
  `.rdata` at `0x1400c11f0` (`9223372036854775808.0`). `0x1400164f0` always runs afterwards, which is why
  the suite sees the field it adjusts.
- `0x1400127e0` (`event_base_priority_init`): refused unless `+0xd8` is zero and the count is 1..0xff. The
  table at `+0xf8` with its size at `+0x100` is released through the hook `DAT_140103fa8` when installed,
  otherwise through the runtime `free`, then rebuilt with `0x140011850(n, 0x10)`, each `0x10`-byte entry
  being `{ 0, self }`. A failed allocation reports "%s: calloc" with "event_base_priority_init" and answers
  `-1`. The notifier is cycled around the work.
- `tests/npcserver_d184_test.cpp` covers all four, including the tick wrap, the epoch guard, the exact
  seconds/microseconds of a 2026 FILETIME, the drift rebase, the table relinking and the failing allocation.

## D185 — NpcServer.exe 0x140074b80 (the IOCP backend launch)

- The once-init runs on `DAT_140104cc8` before anything else, so even a failed launch has already installed
  it. The control block is `0x50` bytes from `0x140011850(1, 0x50)`.
- Two worker slots are reserved per requested thread: `(short)threads * 2` is stored at `+0x30` and is the
  count handed to the second allocation, `0x140011850(slots, 8)` into `+0x38`. A request below one becomes
  `2` **before** both the doubling and the port call, which is why a zero request asks the port for two
  workers and allocates four slots.
- `CreateIoCompletionPort(-1, 0, 0, threads)` lands at `+0`, then `+0x34` is stamped `0xffffffff`, then one
  semaphore `(0, 1, 0)` goes to `+0x48`. Each worker is started through `_beginthread` with the block as its
  argument, its handle is stored in the slot array, and `+0x40` counts the ones that started.
- A refused worker jumps straight to the unwinding path, which closes the port when it exists, releases the
  slot array, closes the semaphore and finally releases the block. The handle array failing short-circuits
  earlier: no port, no semaphore, and only the block is released.
- The lock is `InitializeCriticalSectionAndSpinCount(block + 8, 1000)`.
- `tests/npcserver_d185_test.cpp` covers the block failing before anything else, a full four-slot launch, the
  zero-request substitution, a worker failing on the third attempt (port, semaphore, array, block all
  released in that order) and the missing slot array.

## D186 — NpcServer.exe 0x140014b30 (event_base_free, 867 bytes)

The sweep order, straight from the body: the IOCP slot at `+0x1f0` (closed with `0xffffffff` and cleared),
the socket pair at `+0x210` / `+0x218` with the lock at `+0x220` and the flags word at `+0x230` losing
`0x80`, the active-queue reset, the active queue itself, the timeout entries, the priority queues, the
once list at `+0x108`, the remainder list at `+0x2a8`, the selector's own release through
`*(evsel + 0x28)`, then `+0x150`, the priority table at `+0xf8` (released **unconditionally**), the three
sub-objects at `+0x128`, `+0x140` and `+0x10`, the two notifier sockets, the current-base slot, and finally
the block.

Two things the machine made clear and the pseudo-code did not:

- The active-queue head at `+0x150` is a pointer **to** the slot holding the first entry, not the entry
  itself: both the loop condition and the call dereference it a second time. Reading it as a single pointer
  turns the loop into an endless one, which is exactly what the first run did.
- The table at `+0x1f` is released without a null test, while `+0x2a` has one, so an empty base still
  passes a null to the release path. The suite pins that as two releases, the first with `nullptr`.

The release helper reproduces the reload behaviour: `DAT_140103fa8` is read again after every call, so a
hook that replaces itself mid-sweep is honoured.

A null base falls back to `DAT_140103f80`; when that is null too the only effect is
"%s: no base to free" with "event_base_free_".

`tests/npcserver_d186_test.cpp` walks a fully loaded base and checks all 21 steps in order, then the socket
markers, the entry flags, the emptied remainder list, the cleared current-base slot, and the block going
last.

## D187 — rewiring 0x140015ed0 onto the real bodies

- The base constructor now calls `0x140016640`, `0x1400105b0`, `0x14001a010/190`, `0x14001ad50`,
  `0x140010860`, `0x1400127e0`, `0x140016f00/df0/e70`, `0x140015e70`, `0x140074b80` and `0x140014b30`
  directly. The thirteen temporary seam globals they replaced are deleted from both the header and the
  translation unit.
- One real defect surfaced during the rewire: the constructor's time read was being handed a null output
  pointer where the machine passes a two-int local. With the seam stub that never mattered, but the real
  `0x1400105b0` writes through it. The call now passes a local pair.
- `tests/npcserver_d182_test.cpp` was rewritten to drive the real bodies through their own seams. It now
  pins an ordering fact the seam version hid: the priority table is built **only** on the branch where a
  mechanism was found, so a base that falls through "no event mechanism available" carries no priority
  table at all and releases just the (empty) field at `+0xf8` and then the block.
- All 21 suites were rebuilt against the trimmed translation unit (2011 lines) and pass, which is the check
  that the deleted seams really had no other callers.

## D188 — NpcServer.exe 0x140074d90 and 0x140074780

- `0x140074d90` (port shutdown) raises the exit flag at `+0x32` under the lock, posts one wake-up per slot
  with key `-1`, waits on the semaphore with the caller's timeout when it is non-negative and with
  `0xffffffff` otherwise, then re-reads the started count at `+0x40`. Only zero lets it delete the lock and
  close both handles before releasing the slot array and the block; anything else answers `-1` and leaves
  everything standing.
- `0x140074780` (worker) reads its wait timeout from `+0x34`, the value the launch stamped as
  `0xffffffff`, and treats any value below one the same way. Each iteration: take the lock, read `+0x32`,
  release, then act. An exit request decrements `+0x40` and releases the semaphore at zero. A completion
  with a key other than `-1` and an overlapped structure carries its routine in the **second** overlapped
  slot's first word (`+0x20`) and calls it as `(overlapped, key, bytes, success)`. A key of `-1` with a
  structure present does nothing at all, while a wait that yields neither is logged with
  "GetQueuedCompletionStatus exited with no event." and then takes the same decrement path.
- `tests/npcserver_d188_test.cpp` covers the shutdown with three posted wake-ups (and checks the lock is
  deleted only after the wait), a still-running worker reporting `-1`, both timeout pass-through cases, a
  completion routed through its routine with the exit flag set from inside it, the empty wait, and the
  `-1` key that must not call anything.

## D189 — NpcServer.exe 0x140074930 (winsock extension resolution)

The decompiler truncated every `WSAIoctl` argument list, so this one was written from the disassembly at
`0x140074930` rather than guessed:

- The socket comes from the import called with `ecx=2, edx=1, r8d=0`, that is a stream socket in the IPv4
  family, and a `-1` result ends the body before anything else.
- Each request is `WSAIoctl(socket, 0xc8000006, guid, 0x10, &out, 8, &bytes, NULL, NULL)`: the input is a
  16-byte GUID, the output buffer is eight bytes, and both the overlapped pointer and the completion
  routine are null.
- The three GUIDs, in the order the body asks for them, with their bytes taken from the stack stores:
  `b5367df1-cbac-11cf-95ca-00805f48a192` (AcceptEx) into `+0`, `25a207b9-ddf3-4660-8ee9-76e58c74063e`
  (ConnectEx) into `+8`, `b5367df2-cbac-11cf-95ca-00805f48a192` (GetAcceptExSockaddrs) into `+0x10`.
  Which is worth noting: the second slot is ConnectEx, not the sockaddr helper the ordering might suggest.
- The socket is closed through the same ordinal the base teardown uses, and `DAT_140104cc8` is only set to
  `1` when the socket opened.

`tests/npcserver_d189_test.cpp` pins the socket family/type/protocol, the control code, both buffer sizes,
the exact sixteen bytes of all three GUIDs, the three resolved values landing in order, the socket being
closed, and the flag only being set on the path that got a socket.

## D190 — the launch goes through the real resolution

- D189 removed the `g_pfnNpc_140074930` seam from the header while the launch body still referenced it, so
  suite D185 stopped compiling. The right repair was not to restore the seam: `0x140074b80` now calls
  `FUN_140074930` directly, with the real destination the machine uses, the three-pointer block at
  `DAT_140104cb0` (now `g_aNpcWsaFn_140104cb0`). The earlier stub was passing the once-flag as the output
  pointer, which only worked because the stub ignored it.
- Suite D185 no longer stubs the once-init; with the winsock seams left null the real body stops at the
  failed socket, which is exactly the behaviour that path should have.
- All 23 suites rebuilt and green against the trimmed unit.

## D191 — Rewiring 0x140002b30 onto the real bodies

- `CKernelThread::Create` now calls `0x140012580` (config new), `0x140010a00` (flag), `0x140010a20`
  (processor count), `0x140015ed0` (base), `0x140012660` (config free), `0x140010d80` (method name),
  `0x14001d350` (engine) and `0x140005750` (handler registration) directly. The eight seam globals are gone.
- One real defect surfaced: the base constructor copies eight bytes from `+0x14` of the config to `+0x1fc`
  of the base. Both are odd offsets, and the C++ access as a `long long` is unaligned, which UBSan flags and
  which no optimizer may assume. The bytes are now moved through a local eight-byte buffer, so the result is
  identical to the machine's move without the undefined behaviour.
- `tests/npcserver_d176_test.cpp` was rewritten to drive the real chain: it pins that the config gets the
  processor count at `+0x10` and the flag at `+0x28`, that six processors produce twelve IOCP slots, that
  the engine's first slot receives the thread base address, that a failed socket allocation reports
  `0x1400bebe0` and clears `+0x60`, and that a refusing engine releases itself through its `+0x10` slot.
  The null-config, null-base and missing-argument paths are covered as before.
- Two typing facts worth recording, both found by the compiler: the linear log seam at `0x140019050` takes
  `const char*` while `InlineLogERROR` takes `const void*`, and the base constructor's second argument is
  `unsigned long long` while its third is `long long`.

## D192 — NpcServer.exe 0x140074e80, 0x140074eb0, 0x140074ec0, 0x140074f40, 0x140075040

- `0x140074e80` posts one completion and answers `0` or `-1`, which is `(ok != 0) - 1` exactly.
- `0x140074eb0` returns the IOCP handle the base keeps at `+0x1f0`.
- `0x140074ec0` sizes both notification queues to `(n - 1) * 8 + 0x10` bytes, reallocating the two pointers at
  `+0x08` and `+0x10` in that order, and commits the size and the own-flag only when both succeeded.
- `0x140074f40` appends a key to one of the two queues. Two facts the tests pinned down: an array carries its
  count in the first four bytes and its entries start **eight** bytes in, each entry eight bytes wide; and the
  guard refuses an append while **that same side's** cursor is non-zero (not the other side's), so a side is
  filled, drained, and only then filled again. A full array doubles the capacity, reallocating both arrays to
  `(2n - 1) * 8 + 0x10`, and the entry goes into the side that asked.
- `0x140075040` withdraws the last handed-out entry: it clears that side's cursor, decrements the array count,
  and only when the new count differs from the withdrawn index does it move the last entry into the hole and
  look the moved key up at `0x14001a880` with the tree at `+0x128`, writing the old cursor value into the node
  field for the side that withdrew.
- Two new seams: the reallocator at `0x1400119a0` and the tree lookup at `0x14001a880`.

## D193/D194 — NpcServer.exe 0x1400750d0, 0x140075210, 0x140075380

- `0x1400750d0` builds the queue object: capacity `0x20` in the first word, five `0x108`-byte index buffers at
  `+0x08, +0x10, +0x18, +0x20, +0x28` (each cleared through its first word), then the object is handed to
  `0x14001b590` with size `0x38`. A negative answer sets flag 1 at `+0x30` and `+0x2a0` of the caller is
  cleared through `0x140008930` on both the good and the bad path. A failed allocation releases everything
  already taken, in offset order, and then the object itself.
- `0x140075210` hands one key to one or both queues: flag 8 refuses outright when the object carries bit 1 at
  `+0x30` (and on its own asks for nothing), flag 2 appends to the first queue when its cursor is empty, flag 4
  to the second when that cursor is empty. Each append leaves the cursor at count + 1. Both halves share one
  append shape, so it is one helper: full array doubles and reallocs both arrays, entries eight bytes apart.
- `0x140075380` withdraws: flag 2 clears the first cursor, flag 4 the second, and each half writes its own
  node field, the first half the node's first field, the second half the field at `+4`. Note the asymmetry
  against `0x140075040`, which writes the first field when its `nWhich` is non-zero: the two functions take
  the flag the other way round relative to the queue index.
- Two new seams: `0x14001b590` and `0x140008930`.

## D195 — NpcServer.exe 0x140075480 (one poll cycle)

- With the resize flag at `+4` of the queue object set, the three poll buffers at `+0x18`, `+0x20`, `+0x28`
  are all resized to `(cap - 1) * 8 + 0x10` first, in the order `+0x18`, `+0x28`, `+0x20`; a failure at any of
  them answers `-1` and leaves the flag set so the resize is retried next cycle.
- The two live arrays are then copied into the three buffers: the first array (`+0x08`) into the first buffer
  (`+0x18`), and the second array (`+0x10`) into **both** the second (`+0x20`) and the third (`+0x28`). Each
  copy moves the count word and `count * 8` bytes of entries from `+8`.
- The higher of the two last counts decides the branch: zero waits, through `0x140016450` when a timeout object
  is given (a negative answer becomes `0x7fffffff`) and `Sleep(0x7fffffff)` when none is; otherwise the poll
  runs with the count and the three buffers, bracketed by `0x140016e50` and `0x140016e30` when the base holds
  a notification handle at `+0x1d0`. A poll answer below one is returned unchanged, so `-1` and `0` reach the
  caller.
- Every non-empty buffer is then walked exactly once, activating each fd through `0x14001a5d0`: the first
  buffer with flag 2, the second and third with flag 4. The walk starts at `0x1400089a0`'s rotating index,
  steps **past** it and wraps when the step reaches the count, so a list of two with a start of one activates
  entry 0 and then entry 1, while a list of three with a start of one activates 2, 0, 1. The tests pin both.
- Five new seams: `Sleep`, `Ordinal_18` (the poll), the timeout-to-milliseconds conversion at `0x140016450`,
  the two notification hooks, the rotating index at `0x1400089a0` and the per-fd activation at `0x14001a5d0`.

## D196 — NpcServer.exe 0x140075740, 0x1400757e0, 0x140075840

- `0x140075740` tears the queue object down: `0x14001b930` for the mechanism first, then the five index buffers
  at `+0x08` through `+0x28` in offset order, then all seven words of the object are cleared and the object is
  released last. Missing buffers are skipped without disturbing the order.
- `0x1400757e0` walks the list held at `+0x98` for exactly `+0xa0` entries, resetting each through
  `0x14000dcb0` with the caller's value, taking the next pointer before the reset so the reset may free the node.
- `0x140075840` accounts a write. The buffer is its own target only when the byte at `+0x38` carries `0x10`.
  The chain starts at `*(long long*)pBuf[2]` and steps to `pBuf[2]` itself only when that first node's byte at
  `+0x20` carries `0x10`, so by default the **first** node is skipped. Each segment at `+0xa8`, spaced `0x10`
  apart and limited to `+0xa0` of them, is capped by the bytes left and added to the successor node's `+0x18`.
  The `pBuf[2]` field is written back **before** the chain steps on, so after the loop it holds the node whose
  successor received the last bytes, one step behind the last node touched. Then the list at `+0x98` is reset
  with `0x10`, bit 0 of `+0x90` is cleared, `+0x18` and `+0x20` both grow by the length, and `0x14000c160` and
  `0x14000c220` run last. A zero length still runs the unlock hook, the reset, both hooks and the totals stay.
- Five new seams: `0x14001b930`, `0x14000dcb0`, `0x14000d9a0`, `0x14000c160`, `0x14000c220`.

## D197 — NpcServer.exe 0x140075950, 0x140075a00, 0x140075a50

- `0x140075950` adds input: unlock hook when `+0x30` is set, the buffer adjustment with 1, the add through
  `0x14000e2a0`, the notification list at `+0x98` reset with `0x20` for `+0xa0` entries, bit 1 of `+0x90`
  cleared, and `0x14000c220` last. Note it has no closing unlock hook, unlike `0x140075840`.
- `0x140075a00` builds the `0x1a8` write context: flag `0x10` or-ed into `+0x38`, `+0x78` cleared, `1` at
  `+0x48`, the object itself at `+0x10`, and the caller's value at `+0x88`. A failed allocation returns quiet.
- `0x140075a50` sends. It is refused with `-1` when the buffer's byte at `+0x38` carries 2 or its `+0x90`
  carries 2, and answers null with nothing to send. Otherwise the chain at the buffer's head becomes the
  notification list at `+0x98` and is walked into at most sixteen WSABUF entries at `+0xa8`: each entry is a
  length and the sum of the node's words at `+0x10` and `+0x28`, capped by what is left, stopping on the node
  that covers the request. Every node looked at is touched through `0x14000be60` with `0x20`, the last one too,
  so a two-node send touches twice. A send answering 0 or `0x3e5` marks `+0x90` with 2 and answers null;
  anything else resets `+0xa0` entries of the list with `0x20`, adjusts the buffer, runs `0x14000c300` and
  answers `-1`. All three entry points read the buffer's flag through `pBuf + 7` (byte `0x38`).
- The `Ordinal_111` seam was retyped to return the error value, since this function compares it with `0x3e5`
  (WSA_IO_PENDING); the earlier call sites ignore the value, so they are unchanged. Five more seams added.

## D198 — NpcServer.exe 0x140075c30, 0x140075e60, 0x140075e80

- `0x140075c30` receives. Refused with `-1` when the buffer's byte at `+0x38` carries 4 or its `+0x90` carries
  bit 0. The list at `+0x98` and the segment array at `+0xa8` (256 bytes) are cleared, then `0x14000ebd0` is
  asked whether the length may be taken; only a `-1` answer stops the cycle, and it still answers `-1`.
  `0x14000cdc0` reserves into a sixteen-entry vector whose entries are `{pointer at +0, length at +8}`, and that
  vector is copied into the WSABUF array as `{length at +0, pointer at +8}` - the two layouts are the other way
  round, so the copy swaps the halves. The chain pointer taken from the reservation's out field becomes the
  list at `+0x98` and every node on it is touched with `0x10`. A receive answering 0 or `0x3e5` marks `+0x90`
  with 1 and answers null; anything else resets `+0xa0` entries with `0x10`, adjusts the buffer with 0, runs
  `0x14000c300` and answers `-1`.
- `0x140075e60` reads `+0x88` for a buffer carrying the own flag at `+0x38`, answering all ones otherwise and for
  a null buffer.
- `0x140075e80` writes `+0x88` only with that flag, bracketed by `0x140016e30` and `0x140016e50` when `+0x30`
  is set. The send side's counterpart is the same pair of entry points on the same field.
- Three new seams: `0x14000ebd0`, `0x14000cdc0` and `WSARecv`.

## D199 — NpcServer.exe 0x140075ef0, 0x140075f10, 0x140075f60

- `0x140075ef0` is the lite message constructor: it installs only the `MessageLite` vtable at `+0` and touches
  nothing else. The vtable address is a data symbol, carried here as `g_pNpcVtblMessageLite`.
- `0x140075f10` is the lite message's missing-fields description, a `std::string` built in the caller's storage
  with the literal `"(cannot determine missing fields for lite message)"`.
- `0x140075f60` is the byte-size consistency check from `message_lite.cc`. It builds up to three separate
  checks, each through `0x1400783d0` with severity 3 and this exact file, at lines `0x3f`, `0x41` and `0x45`:
  the first two only when their sizes differ, the third always, because reaching the function is the error. The
  texts, in order: `CHECK failed: (byte_size_before_serialization) == (byte_size_after_serialization): ` followed
  by `Protocol message was modified concurrently during serialization.`; then
  `CHECK failed: (bytes_produced_by_serialization) == (byte_size_before_serialization): ` followed by
  `Byte size calculation and serialization were inconsistent.  This may indicate a bug in protocol buffers or it
  may be caused by concurrent modification of the message.`; and finally
  `This shouldn't be called if all the sizes are equal.` Each check ends in `0x140078580`, and the two sized
  checks clear their state bit and release their own sink through `0x140078440`, the third releasing
  unconditionally. The single state word packs bit 0 for the first check and bit 1 for the second.
- Four new seams for the protobuf log objects, plus the `MessageLite` vtable data symbol.

## D200 — NpcServer.exe 0x140076190, 0x140076320, 0x140076350, 0x140076380

- `0x140076190` builds the required-fields sentence: `Can't ` + action + ` message of type "` + the type name +
  `" because it is missing required fields: ` + the missing list. The two variable parts come from the message's
  own vtable, slot 1 at `+0x08` for the type name and slot 5 at `+0x28` for the list, each built into its own
  temporary that is destroyed the moment it has been appended. The three temporaries are destroyed exactly once
  each, which matters in a port: as scoped C++ objects they would be destroyed twice.
- `0x140076320`, `0x140076350` and `0x140076380` are three-word thunks that forward their `(this, argument)`
  pair to `0x140077370`, `0x1400774a0` and `0x1400774e0` with the two **the other way round**, so the callee
  receives the argument first and the object second. The tests pin the swap.
- Three new seams for the three forward targets.

## D201 — NpcServer.exe 0x1400763b0, 0x140076450, 0x1400764f0, 0x1400765b0

- The three thunks of D200 are **tail calls** that carry the callee's answer back, so their return type is the
  callee's: each returns one byte. The earlier `void` reading of `0x140076350` in the decompiler was the reason
  this only became visible here, where `0x1400763b0` tests the value the thunk returned.
- `0x1400763b0` builds a `0x50`-byte wrapper around the argument through `0x140077530`, offers it to
  `0x140076350`, and answers 1 only when the offer was accepted **and** `0x140077520` then reports the wrapper
  valid. The wrapper is destroyed through `0x14007a700` on every path, including both refusals.
- `0x140076450` is the same shape through `0x140076380`.
- `0x1400764f0` and `0x1400765b0` stamp a type on the wrapper with `0x14007a8e0` right after the build, and add a
  third condition: `0x14007a9c0` must answer zero. Lazy evaluation matters and the tests pin it: a refused offer
  stops before the validity check, and an invalid wrapper stops before the error state is asked at all.
- Five new seams: the wrapper build, validity, type stamp, error state and destroy.

## D202 — NpcServer.exe 0x140076670, 0x1400766c0, 0x140076710, 0x140076750

- Four hand-overs, all with the same argument order: the bytes first, the length second, the object **last**.
  `0x140076670` and `0x140076710` go to `0x140077620`; `0x1400766c0` and `0x140076750` go to `0x1400777a0`. The
  first of each pair takes a `std::string` and passes `size()` truncated to an `int` and then widened, so a
  string of more than 2^31 bytes would wrap exactly as the machine does; the second of each pair passes the
  caller's length through untouched, negative values included.

## D203 — NpcServer.exe 0x140076790, 0x140076910, 0x140076aa0

- `0x140076790` serializes into a caller's buffer. The byte size comes from the message's slot 11 at `+0x58`, the
  coded output is wrapped around the buffer with a limit of `-1`, the message writes itself through slot 9 at
  `+0x48`, and a coded output that reports an error aborts through the check at line `0xe0` of `message_lite.cc`
  with the single text `CHECK failed: !coded_out.HadError(): ` - no second message on this one. The buffer comes
  down (`0x14007bc70`) before the coded output (`0x14007d810`), and the answer is the buffer advanced by the byte
  size.
- `0x140076910` is a straight forward to `0x140076aa0` and is now wired to the real body.
- `0x140076aa0` serializes into a target. The byte size comes from slot 8 at `+0x40` and the target is asked for
  that much room through `0x140077850`. With no room, the message writes through slot 9 and the bytes are measured
  by `0x1400778a0` before and after. With room, slot 10 at `+0x50` writes into it and answers the end pointer, and
  the end minus the start must equal the byte size. Either mismatch runs `0x140075f60`, so a short write fires
  **two** checks (the produced-count one and the unconditional third); the answer is 1 in the low byte with the
  measured value's upper bytes, and 0 when the target reports an error.
- One real bug found and fixed here, worth remembering for every later vtable call: `(*pMsg + 0x58)` is the
  address of a **slot**, not a function. Writing `(*(T)(*pMsg + 0x58))(...)` calls the slot address itself,
  which is the vtable's own memory - in this port it jumped into the object on the stack and ASan reported a
  stack overflow with the program counter equal to the faulting address. The correct form keeps two stars:
  `(*(T (**)(...))(*pMsg + 0x58))(...)`.
- Seven new seams: the coded output, the output wrapper, the error query, both teardowns, the room request and
  the written-bytes query.

## D204 — NpcServer.exe 0x140076be0, 0x140076c40, 0x140076ca0, 0x140076e30

- `0x140076be0` and `0x140076c40` wrap the target in a coded output through `0x14007bbf0`, serialize through
  `0x140076910` and `0x140076aa0` respectively, destroy the wrapper through `0x14007bc70`, and hand back only the
  **low byte** of the answer.
- `0x140076910` is a tail call too and had to be retyped to return eight bytes; the decompiler shows it as `void`
  and `0x140076be0` reads what it returns. Third instance of this pattern in this cluster.
- `0x140076ca0` forwards to `0x140076e30`.
- `0x140076e30` appends the message's bytes to a string: the byte size comes from slot 8 at `+0x40`, the string is
  grown through `0x140077900` to its own size plus that byte size, its data pointer comes from `0x140077930`, and
  slot 10 at `+0x50` writes starting at data plus the string's old size. A write that does not end exactly at the
  byte size runs `0x140075f60`, which never returns, and the answer is one with the expected end's upper bytes.
- Two new seams: the string resize and its data pointer.

## D205 — NpcServer.exe 0x140076f00, 0x140076f40, 0x140077520, 0x140077840, 0x1400778a0, 0x140077900,
0x140077850, 0x1400774a0, 0x1400774e0

- `0x140076f00` and `0x140076f40` empty the string first and then append through `0x140076ca0` and
  `0x140076e30`; the tests pin the consequence: the resize they cause is the byte size alone, not the old size
  plus it.
- Three field readers: `0x140077520` the wrapper's validity byte at `+0x24`, `0x140077840` the target's error
  byte at `+0x18`, and `0x1400778a0` the bytes written, the cursor at `+0x14` minus the start at `+0x10`, which
  is negative while the cursor still sits behind the start.
- `0x140077900` resizes the string, straight through.
- `0x140077850` hands out the target's buffer at `+0x08` only when the room at `+0x10` is at least the requested
  size, advancing the target through `0x1400778c0`; otherwise it answers null and touches nothing.
- `0x1400774a0` closes the wrapper through its slot 3 at `+0x18` and then runs `0x140077370`, and `0x1400774e0`
  closes it the same way and then hands it to slot 7 at `+0x38`. Both carry the second call's answer back out,
  which is why the thunks of D200 return a byte.
- These bodies now exist, but the earlier ports still reach them through their seams. A rewiring pass for this
  cluster is due - the same job D191 did for the thread create path.

## D206 — NpcServer.exe 0x140076f80, 0x140077120, 0x1400771d0, 0x140077280, 0x140077330

- `0x140076f80` forwards to `0x140077120` and carries its answer back.
- `0x140077120` writes into a caller's room. When the room is smaller than the byte size from slot 8, nothing is
  written and the answer is the size with its **low byte cleared** - `nSize >> 8 << 8` - so the caller reads a
  zero low byte for failure while the upper bytes still carry the size class (a size of 8 answers 0, a size of
  `0x108` answers `0x100`). With room, slot 10 writes and must end exactly at the byte size; a mismatch runs
  `0x140075f60`, and the answer is one with the expected end's upper bytes.
- `0x1400771d0` and `0x140077280` serialize into a string through a temporary, empty it again when the producer
  answers zero, and copy it into the caller's storage. The branch is unreachable in practice: both producers
  answer with a one in the low byte or never return at all, so the temporary is never emptied. Ported as written.
- `0x140077330` is the lite message's deleting form: the vtable is installed unconditionally, the object is
  released only when bit 0 of the flags is set, and the pointer is answered either way.
- `0x140076ca0` had to be retyped to return a byte: fourth tail call of the cluster that the decompiler shows as
  void. `0x1400771d0` reads the value it returns.

## D207 — NpcServer.exe 0x140077370, 0x140077530, 0x140077620

- `0x140077370` accepts a message from a source. Slot 7 at `+0x38` parses and a refusal answers zero at once. A
  parse that succeeds but leaves the message uninitialised is reported as a **warning**, severity 2, at line
  `0x7b` of `message_lite.cc`, with the text built by `0x140076190` for the action word `parse` and appended by
  `0x140077ff0`; the sink and the text are then released and the answer is zero with its low byte cleared. A
  message that parses and is initialised answers one.
- `0x140077530` builds the `0x50`-byte parse wrapper, field by field: source at `+0x00`, cleared at `+0x08`,
  `+0x10`, `+0x18`, `+0x1c`, `+0x20`, the two bytes at `+0x24` and `+0x25`, `0x7fffffff` at `+0x28`, `0` at
  `+0x2c`, `0x4000000` at `+0x30`, `0x2000000` at `+0x34`, `0` at `+0x38`, the data constant `DAT_1401036a0` at
  `+0x3c`, cleared words at `+0x40` and `+0x48`, and `0x14007b7e0` last.
- `0x140077620` parses a run of bytes: the wrapper is built by `0x1400776c0` around the bytes, offered through
  `0x1400774a0`, and the answer is one only when that accepted it **and** `0x140077520` reports the wrapper valid.
  The wrapper is destroyed through `0x14007a700` on every path, refusals included.
- Three new seams and one data constant: `0x140077ff0`, `0x14007b7e0`, `0x1400776c0`, `DAT_1401036a0`.
- Test note worth keeping: the required-fields text is freed by the body right after the failure, so a fixture
  must copy it at the append call, not hold the pointer.

## D208 — NpcServer.exe 0x1400776c0, 0x1400777a0, 0x1400778c0

- `0x1400776c0` builds the same 0x50-byte wrapper as `0x140077530` but around a byte range: cleared at `+0x00`,
  the start at `+0x08`, the end at `+0x10`, the length at `+0x18` **and again at `+0x28`** where the stream form
  puts `0x7fffffff`, then the same `0x4000000` / `0x2000000` / data constant at `+0x30` / `+0x34` / `+0x3c`. No
  `0x14007b7e0` call: this form is already complete when it returns.
- `0x1400777a0` is the twin of `0x140077620`, offering the wrapper through `0x1400774e0` (slot `+0x18`, then slot
  `+0x38`) instead of `0x1400774a0` (slot `+0x18`, then `0x140077370`). Same validity byte at `+0x24` through
  `0x140077520`, same destroy through `0x14007a700` on every path.
- `0x1400778c0` consumes n bytes: the data pointer at `+0x08` moves forward and the remaining count at `+0x10`
  shrinks, leaving a negative count when more than is left is asked for.
- Fixture note: my first sequence helper wrote `g_seq[n] = n` instead of `g_seq[g_seqN] = n`, so the ordering
  assertions read zeros while the counter advanced. Worth watching for across the remaining suites.

## D209 — NpcServer.exe 0x140077930, 0x140077950, 0x1400779a0, 0x1400779c0, 0x14007a700

- `0x140077930` → `0x140077950` → `0x1400779a0` → `0x1400779c0`. `0x140077950` answers **zero** for an empty string
  instead of a pointer into itself; `0x1400779a0` is another tail call the decompiler shows as void.
- `0x1400779c0` is MSVC's checked iterator unwrap: the container word at `+0x00` is compared against the unlinked
  sentinel **-4**, then the container must be known and the answer must satisfy `base + *(container+0x18) > iterator`
  (note the bound: a pointer **at** base+size already trips it). Every failure calls `_invalid_parameter_noinfo` and
  the answer is always the pointer word at `+0x08`.
  Divergence to record: the word at `+0x18` is MSVC's string field; under libstdc++ that offset is not the size, so
  the bound check can report an invalid parameter for an ordinary `std::string`. The value returned is unaffected.
- `0x14007a700` releases the byte chain at `+0x00` through `0x14007a830` and compares the word at `+0x34` with the
  **-2** sentinel: that state logs a CHECK failure at `coded_stream.cc` line **0x4e**, severity 1, text
  "The total number of bytes read was " followed by the count at `+0x18`.

## D210 — NpcServer.exe 0x14007a830, 0x14007a8e0, 0x14007a9c0

- `0x14007a9c0` answers **-1** when the limit at `+0x28` is still `0x7fffffff`, so "no limit" is distinguishable from
  "nothing left" (which answers 0). `0x14007a8e0` answers the limit from **before** the raise, and `0x14007d140` has
  the final word over the value it stores back; a negative amount, or a sum that would pass `0x7fffffff` from the
  bytes already consumed, pins the limit at `0x7fffffff`.
- `0x14007a830` flushes only a **positive** amount (pending from `0x14007c650` + `+0x2c` + `+0x1c`) through sink slot
  2 at `+0x10`, then drops the read count at `+0x18` by the re-read pending value plus `+0x2c`, copies `+0x08` into
  `+0x10` (current into end), and clears both counters.
- Everything answered through a measured `int` re-read after the sink call: the pending count is asked twice on
  purpose, and the second answer is the one used for the bookkeeping.

## D211 — NpcServer.exe 0x1400783d0, 0x140078440, 0x140078030, 0x140077ff0, 0x140078100, 0x140078580, 0x140078470

- The log message is 0x38 bytes: severity at `+0`, the file pointer at `+8`, the line at `+0x10`, and a `std::string`
  at `+0x18` that the constructor builds in place and `0x140078440` destroys.
- `0x140078100` formats with `"%d"` into a **0x80** buffer from an **unsigned** word, so a value such as `0xFFFFFFF0`
  lands in the text as `-16`. Pinned in the suite.
- `0x140078470` is the sink. Severity 3 (fatal) skips the rotation entirely, still goes through the log function at
  `0x1401035c8`, and then throws `0x1400fee98`, which is what makes a failed check end the run. Every other severity
  first rotates the log file (`0x140077fc0`), takes the lock (`0x140078d20`) and lets it go (`0x140078d60`), and only
  logs when the quiet flag `140104cd8` the rotation leaves behind is clear.
- `0x140078580` is the finisher form of the same sink: its first word is ignored.

## D212 — rewiring pass 1: the log message bodies

- `0x1400783d0`, `0x140078030`, `0x140078100`, `0x140078440`, `0x140078580` and `0x140077ff0` now have real bodies, so
  their seams are gone. Every call site (27 of them, in `0x140075f60`, `0x140076790`, `0x140077370` and
  `0x14007a700`) calls the body directly, exactly as the image does.
- The suites for those four bodies now observe at the one seam that is genuinely foreign to this image: the log
  function at `0x1401035c8`, reached from the real sink `0x140078470` with severity, file, line and the finished
  text. That is a stronger check than the old one: the tests read the **composed** message,
  e.g. `CHECK failed: (byte_size_before_serialization) == (byte_size_after_serialization): Protocol message was
  modified concurrently during serialization.`, instead of the individual appends.
- Note that these checks carry severity 3, and `0x140078470` throws only through its own throw seam, so with that
  seam unset the port logs and keeps going. The machine's abort comes from the throw info the image passes at
  `0x1400fee98`.

## D213 — NpcServer.exe 0x140077fc0, 0x140077f50, 0x140078d20, 0x140078d60, 0x140078d80

- `0x140078d80` builds `google::protobuf::FatalException`. The object is **0x48** bytes: the `std::exception` base at
  `+0`, the vtable the image stores is **0x1400cdd70** (confirmed by objdump of the constructor, `lea 0x54fb7(%rip)`
  into `(%rcx)`), the file at `+0x18`, the line at `+0x20` and a **copy** of the message at `+0x28`. The copy matters:
  the message object the caller built can go away, and the exception keeps its text.
- `0x140078d20` stores the mutex into the wrapper **before** taking it, so the wrapper is already usable if the take
  reports a problem; `0x140078d60` only releases.
- `0x140077fc0` runs the one-time log initialisation: it hands `0x140078b30` the state word at `0x140104ce8` and the
  **address** of `0x140077f50`, not a call.
