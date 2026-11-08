
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
