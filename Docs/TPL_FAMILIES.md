# Shape families — Syndicate.dll

Generated from the binary. 11928 functions, 2415 distinct shapes after normalising
addresses and register names. The rewrite so far cites 227 starts in PORTING_LOG.md,
196 of which are function starts in this pass; their 75 shapes account for
2161 functions in the image, so one shape is written once and then again at each start.

| # | functions already ported | shape |
|---|---:|---|
| 1 | 10 | rex push %R ; sub    $H,%R ; mov    %R,%R |
| 2 | 9 | ret    $H |
| 3 | 8 | mov    %R,%R ; ret |
| 4 | 8 | movabs $H,%R ; ret |
| 5 | 7 | mov    H(%R),%R ; add    $H,%R ; ret |
| 6 | 7 | mov    H(%R),%R ; ret |
| 7 | 7 | movq   $H,(%R) ; mov    %R,%R ; ret |
| 8 | 6 | mov    %R,H(%R) ; push   %R ; sub    $H,%R |
| 9 | 6 | rex push %R ; sub    $H,%R ; mov    (%R),%R |
| 10 | 4 | rex push %R ; sub    $H,%R ; cmpq   $H,(%R) |

## Reading of the numbers

- The ported set is thin in *functions* and wide in *shapes*: nearly every function we wrote sits
  in its own family. That is why the work is slow, not the difficulty of any single body.
- The dartboard for the next pass is the shapes with a high count and no ported member yet: a
  single translation covers every start that shares the shape once the differences are tabulated
  (node offset, flag byte 0x21/0x29/0x41, seam address).

## What the generator already covers

`tools/family_gen.py` produced **644** leaf bodies (`modules/syndicate/src/genleaf.cpp`), tabulated
with their addresses in `g_synLeafTable`. The generator's rule is the point: a body is kept only if
its *entire* instruction list is one template, so the table is a transcription, not an inference.

Next families in the same form: the deleting/scalar destructors, the `n*0x28`/`n*0x30`/`n*0x48`
allocators, the `operator delete` thunks, and the iterator-construct-with-check shape.

## D162 — forwarders

126 single-`jmp` bodies became a family of their own. They forward `rcx`/`rdx`/`r8`/`r9` to the
target printed by objdump and return its answer. **The float registers are not carried**, so this
shape is only faithful for integer-only targets; `xmm` cases must not be added to this family.

The generated unit is now produced whole by `tools/family_gen.py` (832 bodies), which keeps the
table and the bodies in step by construction.
