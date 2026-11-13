# Where a class lives, and what that means for a body that constructs it

Read from `NpcServer.exe`'s own RTTI and from the class tables of the DLLs in the v6159 package.

- `NpcServer.exe` carries **125 RTTI class names**; `Docs/VTABLE_SLOTS.tsv` covers **60** of them, so the port's own
  vtable table is not the gap it was assumed to be.
- 46 of the package's DLLs carry RTTI of their own: **1,030 classes**, none of which appear in `NpcServer.exe`'s
  list. `Syndicate.dll` alone has 81, `DB.dll` 45, `Common.dll` and the rest the remainder.
- Therefore a body rejected for `::vftable not in table` is almost always reaching for a **class of another module**
  (`std::logic_error`, `std::bad_alloc`, `std::tr1::_Ref_count_base`, `std::out_of_range` - all msvcp90/msvcr90, which
  the package does not ship). The port cannot have those vtables, and it will not invent them.

## Class census per module (top)

| mfc42.dll | 402 |
| libmySQL.dll | 83 |
| Msvcp60.dll | 82 |
| Syndicate.dll | 81 |
| DB.dll | 45 |
| CQBase.dll | 35 |
| FamilyArenic.dll | 28 |
| TeamArenic.dll | 26 |
| CrossFlagWar.dll | 23 |
| FrontierFlagWar.dll | 23 |
| Rank.dll | 23 |
| Arenic.dll | 22 |
