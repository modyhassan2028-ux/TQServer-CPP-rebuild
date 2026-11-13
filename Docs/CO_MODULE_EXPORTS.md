# What the v6159 package's own modules export

Read from the DLLs shipped in `Source/` of the v6159 archive, joined against `NpcServer.exe`'s 467 imports.

- `Analyst.dll`: 12 exported functions, ordinal base 1, image base 0x140a40000
- `CQBase.dll`: 306 exported functions, ordinal base 1, image base 0x140b80000
  - `?TimeGet@tq@@YAKH@Z` at 0x140b82df0
  - `?SysTimeGet@tq@@YAKXZ` at 0x140b87940
  - `?IsTimeRange@tq@@YA_NKK_J@Z` at 0x140b877d0
  - `?DateTime@tq@@YAXPEAD_J@Z` at 0x140b878c0
- `DB.dll`: 36 exported functions, ordinal base 1, image base 0x140c00000
- `zlibwapi.dll`: 160 exported functions, ordinal base 1, image base 0x141a60000
