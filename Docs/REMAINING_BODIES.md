# What is left of NpcServer, measured

| | bodies |
|---|---|
| in the Ghidra listing | 3,574 |
| have a definition in `modules/npcserver/` | 2,774 |
| **remaining** | **800** |

Of the 1,797 bodies in the transliterated unit: **1,106 link** (compile clean and held by a suite) and **691 sit in
the pending tier** - the source is written and compiles, but a callee they call is not ported yet.

## The 800, by what holds each one

| blocker | bodies | what it needs |
|---|---|---|
| needs its callee ported first | 465 | peeling: port the leaf of that group, then its callers |
| global not typed | 205 | the global's real bytes/width from the image (partly done: 20 blobs cut) |
| register recovery (extraout_) | 56 | the 16-byte return ABI decision: a callee returning RAX:RDX has to be modelled as a struct |
| 16-byte slice (SUB) | 44 | same ABI decision |
| class of another module (std::) | 27 | msvcp90/msvcr90 - not in the v6159 package |
| ordinal import (no signature) | 18 | mfc90.dll / ws2_32.dll / oleaut32.dll export tables |

## What has to be decided, not coded

1. **The 16-byte return ABI.** `extraout_EDX`/`SUB168(…,8)` mean the callee returned two registers. C has no second
   return value, so every such callee has to become a struct-returning function and every caller adjusted. That is
   one architectural pass over ~180 bodies, not 180 edits.
2. **Module boundaries.** A body that constructs `std::logic_error`, calls `tq::TimeGet`, or stores a `Flower::` vtable
   is executing another module's code. The port's answer so far is a seam (`g_pfn*`); deciding that these bodies count
   as ported *once they use the seam* is a policy call, not a coding one.
3. **Missing system DLLs.** 190 ordinal imports cannot be named without `mfc90.dll`, `ws2_32.dll`, `oleaut32.dll`.
