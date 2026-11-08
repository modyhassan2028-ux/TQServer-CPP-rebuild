
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
