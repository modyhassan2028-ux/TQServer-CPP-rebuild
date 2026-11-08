
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
