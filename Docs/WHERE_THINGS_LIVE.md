# Where the NPC port lives, and which tree is which

There are two trees with similar names in this repository. They are not the same work, and one of them is frozen.

| | `npcserver/` (repo root) | `modules/npcserver/` |
|---|---|---|
| what it is | hand-written attempt from the first weeks, before the verbatim method | the port that is actually verified |
| files | 54 | 114 |
| size | 338 KB | 1.9 MB |
| address mapping | comments only (`// ===== ORIGINAL FUN_140061220`) | every body carries `//@START <address>` / `//@END` and is listed in the unit's own address table |
| tests | none of its own | 598 test files, one suite per unit batch |
| last touched | 2026-10-27 (repo reorganisation) | every working session, currently D260 |
| body count | ~152 function-like lines | 1,669 transliterated bodies |

**`npcserver/` at the root is legacy.** Its code was written by reading the decompiler and typing classes by hand. It is
plausible C++ that was never held against a single machine-code address, so nothing in it can be called verified - which
is exactly the rule this project runs on (no guessed code, every unit checked against the listing and held by a suite).
It is kept only as reading material. Nothing new should be written there, and nothing there counts toward the port's
numbers.

**`modules/npcserver/` is the port.** Bodies are extracted from the listing, address-linked, and each batch is proven by
its own suite. `Docs/REMAINING_ROADMAP.md` counts against this tree only.

So: the numbers in `PORTING_LOG.md` and `HANDOFF.md` (3,577 bodies in the binary, 2,644 ported, 933 left) refer to
`modules/npcserver/`. Nothing is being re-done: the root tree was superseded in October and has not been touched since.
