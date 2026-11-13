# Parity ledger — what is the original's, what is the decompiler's, what is mine

This exists because I described the port as "verbatim from the binary" more times than was honest. It is verbatim from
the **decompiler's listing of the binary**. Those two sentences are not the same, and the difference is measurable.

## Byte-exact from `NpcServer.exe` (evidence: the image itself)

| what | count | how it was taken |
|---|---|---|
| embedded `__FILE__` paths, mirrored in `modules/npcserver/src` | **56 / 56** | `strings`, `Docs/NPCSERVER_PATHS.md` |
| imported symbols (name + DLL + IAT) | 467 | import directory, `Docs/NPCSERVER_EXPORT_MAP.tsv` |
| imports by ordinal | 194 | same table; no signature anywhere in the image |
| RTTI class names | 101 | `.data` type descriptors |
| vtable rows (class -> vtable address) | 1,217 | RTTI + `VTABLE_SLOTS.tsv` |
| literal strings and log-format constants used by ported bodies | all referenced | cut from the image, `npc-data.cpp` / `npc-underscore-data.cpp` |
| globals carried as real bytes | 105 | `tools/emit_data_blobs.py`, `tools/emit_underscore_data.py` |

## Derived from the listing (correct in behaviour, not the original text)

| what | count | why it cannot be the original |
|---|---|---|
| function bodies transcribed | 2,768 of 3,574 | Ghidra's C output: canonicalised control flow, `param_1`/`uVar1`/`local_20` names, folded expressions |
| function bodies in the linked tier | 1,110 | compiled and held by the suites |
| function bodies pending a callee | 694 | text exists, syntax-checked, not linked |

The original `.pdb` and any `-Z7` debug streams are absent from the image, so local names, statement order and file
attribution are unrecoverable. A decompiler cannot produce them, at any tier of effort.

## Mine, not the original's (and this is the honest correction)

- **Class names**: the port declares 55 classes. **8** are named in the image's RTTI. **8 more** are named in the
  image's bytes (`CIniFile`, `CIniMgr`, `CMyHeap`, `CStringPacker`, `IAnalyst`, `ILogKernel`, `IStringManager`,
  `ITerrainObjInfoMgr`). The rest are Windows SDK types - and **25 are scaffolding I invented**: `NpcSmallBodyEntry`,
  `NpcTreeEraseEntry`, `NpcStlEntry`, `NpcLogStubEntry`, and the rest of the `Npc*Entry` family. They are the port's
  own index/registry structs. They do not exist in the original and must never be read as recovered names.
- **File attribution**: 2,691 of the 2,768 ported bodies sit in `_unnamed_*.cpp` listing files - the compiler did not
  name those translation units, so no fact in the image says which of the 56 paths they came from.
- **Class layouts**: bodies reach members by offset (`*(int *)(param_1 + 0x10)`), because member names and field order
  are not in the image. The offsets are evidence; the names would not be.

## What that means for "100%

100% behavioural parity with the original server is the reachable target and is not yet met: 800 of 3,574 bodies are
still unwritten, and the linked tier is 1,110. 100% *source* parity is not reachable from a binary alone, and any claim
of it - including mine, earlier - is wrong.
