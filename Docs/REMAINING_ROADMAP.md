# Remaining roadmap

Measured from the listing itself (`Docs/reference/NpcServer_Ghidra`) against the bodies the port defines:

| | count |
|---|---|
| bodies in the listing | 3,577 |
| have a body in the port | 2,644 (73.9%) |
| **left** | **933** |

## What is holding the 933

| blocker | bodies | what unblocks it |
|---|---|---|
| waits on an unported callee | 455 | bottom-up peeling: no body is a leaf, so each pass unlocks the next layer |
| global with no type | 185 | typing pass over `Docs/NPC_DATA_TYPING.md` (208 globals are used only by address) |
| class missing from the RTTI table | 150 | complete the vtable table: these classes exist in the binary but not in the 1,079 harvested slots |
| `CONCAT` intrinsics | 87 | translate each `CONCAT44(a,b)` into the shift-or it denotes; mechanical but per-site |
| register recovery (`extraout_`) | 56 | read the register from the surrounding machine code by hand (the decompiler lost it) |

**No body left is a leaf**: every one of the 933 calls at least one other unported function, so the tail is a
dependency web and has to be peeled from the top down rather than taken in address order.

## Order of attack

1. The RTTI table gap (~150 bodies): one tool fix, all at once.
2. `CONCAT` (~87): a mechanical rewrite with a per-site check.
3. The typing pass (~185 plus the shared blockers): the worksheet is already generated.
4. Dependency peeling (the rest): each pass ports what is now unblocked, then re-measure.
5. Register recovery (~56) last: those need the disassembly read by hand.

## Honest estimate

The last three sessions moved 1,641 -> 1,669 bodies because the horizontal waves are exhausted. The four
levers above are vertical and each is a day of work, not a batch: after them the number of remaining bodies
should drop from 933 to the low hundreds. The final hundred are hand translations of long bodies and will take
as long as everything above them combined.
