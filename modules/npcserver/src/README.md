# `modules/npcserver/src` — the original file tree, and why the files here are thin

Every `.cpp` and `.h` under this directory mirrors one of the **56 `__FILE__` paths embedded in `NpcServer.exe`**
(listed in `Docs/NPCSERVER_PATHS.md`). Each one is a three line scaffold:

```cpp
// version/cqserver-78.0.11-1204/npcserver/kernelthread.cpp — scaffolded from the path embedded in NpcServer.exe.
// Bodies are ported verbatim from the binary; nothing is written here until a unit covers it.
#include "version/cqserver-78.0.11-1204/npcserver/kernelthread.h"
```

**They are not the port.** They are the skeleton the port has to grow into, and nothing is written into one until a unit
actually covers that file. That is a deliberate rule, not an omission: putting a body in a file whose name we only know
from `__FILE__` would be claiming an attribution we do not have.

## Where the ported code actually is

| | count |
|---|---|
| functions in the decompiled listing | 3574 |
| functions with a body in this repository | **2768** |
| of those, in a listing file Ghidra could not name (`_unnamed_*.cpp`) | 2691 |
| of those, in a listing file named after the class Ghidra saw | 77 |

The bodies live in `../unattributed/`, one file per kind of body rather than per source file:

| file | bodies |
|---|---|
| `unattributed/transliterated.cpp` | 1983 |
| `unattributed/stl-global.cpp` | 226 |
| `unattributed/small-bodies.cpp` | 172 |
| `unattributed/front-of-image.cpp` | 171 |
| `unattributed/stl-internals.cpp` | 85 |
| `unattributed/stl-shapes.cpp` | 30 |
| `unattributed/stl-iterators.cpp` | 23 |
| `unattributed/container-bodies.cpp` | 14 |
| `unattributed/stl-refs.cpp` | 10 |
| `unattributed/container-nodes.cpp` | 8 |

## Why not one file per original path

The image carries RTTI (class names) but no source line information: no PDB, no `-Z7` sections, no `.debug$` streams.
The decompiler therefore knows which **class** a function belongs to, and nothing more. 2691 of the 2768 ported
functions come from translation units the compiler left unnamed, so there is no fact in the binary that says which
`__FILE__` path they came from. Filing them under a guess is the one thing this port does not do.

If the original `.pdb` ever turns up, `Docs/NPCSERVER_PATHS.md`'s list and this tree are ready for the attribution to be
filled in mechanically.
