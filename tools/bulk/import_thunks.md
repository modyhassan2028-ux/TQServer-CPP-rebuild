# Call targets that are imports, not code

74 of the 2,340 distinct call targets in the image are not rows in our inventory. They are thunks
and IAT slots, resolved here from the PE import directory rather than guessed from names:

| address | calls | resolves to |
| --- | --- | --- |
| 0x1417f2fdc | 875 | `MSVCR90.dll!??3@YAXPEAX@Z` — `operator delete(void*)` |
| 0x1417f3166 | 548 | `MSVCR90.dll!??2@YAPEAX_K@Z` — `operator new(unsigned __int64)` |
| 0x1417f3154 | 287 | `MSVCR90.dll!_CxxThrowException` |
| 0x1417f30c0 | 112 | `MSVCR90.dll!memset` |
| 0x1417e8016 | 107 | `CQBase.dll!?Init@CMsg@tq@@IEAAXXZ` — `tq::CMsg::Init()` |
| 0x1417f3160 | 75 | IAT slot beside `memset` (resolved in iat_slots.json) |
| 0x1417214b0 | 378 | `ret 0` — a stub, no code to port |
| 0x141724850 | 168 | `mov rcx,[rcx] ; jmp operator delete` — delete through a member |

Two consequences for the porting work:

1. Calls to 0x1417f2fdc / 0x1417f3166 are `delete` and `new`. They are not unknowns to be stubbed;
   a faithful port can use `delete` / `new` directly.
2. `0x1418233c0`, the "error path" the tree walks call, is
   `MSVCR90.dll!__invalid_parameter_noinfo`. It *returns*; it is not
   `_invalid_parameter_noinfo_noreturn`. The bytes after the call are reachable in the CRT's
   contract and must be reproduced, not deleted.

The full slot table is in `tools/bulk/iat_slots.json` (127 slots).
