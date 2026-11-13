# What the v6159 package's own modules export

Read from the DLLs shipped in `Source/` of the v6159 archive, joined against `NpcServer.exe`'s import table.

- `cqbase.dll`: not in the package
- `db.dll`: not in the package
- `analyst.dll`: 12 exported functions, ordinal base 1
  - ??0CTickAnalyst@@QEAA@H@Z @1; ??0IAnalyst@@QEAA@AEBV0@@Z @2; ??0IAnalyst@@QEAA@XZ @3; ??1CTickAnalyst@@QEAA@XZ @4
- `zlibwapi.dll`: 160 exported functions, ordinal base 1
  - adler32 @1; adler32_combine @140; compress @2; compress2 @39
