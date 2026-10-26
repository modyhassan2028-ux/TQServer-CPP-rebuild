# D72 — PlunderWarStart (FUN_14176b0d0) Analysis & Port Plan

Status: ANALYSIS (port not started). All facts below from
`Syndicate.dll.decompiled.c` + capstone RAW checks on the
recovered original Syndicate.dll (Dec 2015 build).

## Signature & frame
```
void FUN_14176b0d0(longlong mgr, int flag)
```
Stack CMsgs (offsets from FUN_14176b0d0 frame, sizes in
bytes, MSVC /GS cookie at the tail):
| local | size | role |
|---|---|---|
| local_12b8 | 1072 | CMsgLeagueOpt (0x430) — chat/type-0x3f |
| local_e88  | 1072 | CMsg (0x430) — Create(0x45) via 1417d6740 |
| local_a18  | 1136 | CMsgLeagueBeRob (D69, 0x470) |
| local_5a8  | 1120 | CMsgLeagueRobOpt (D71, 0x460) |
| local_148  | 0x100 | snprintf name buffer |
| local_138  | ~2048 | the two snprintf text buffers (0x100 each) |

Entry gate: `if (param_2 != 0)` — the whole flow is the
nonzero branch. Sets `*(int*)(mgr+0x358)` (see below).

## Phase structure

### Phase 0 — setup
- `*(int*)(mgr+0x358) = ...` written at entry (store
  appears at the top of the nonzero branch).

### Phase A — plundered-league walk (outer while)
- Tree at `mgr+0x370` (league-keyed map, same layout as
  the D70 maps: head@+0x30 of root etc.).
- For each league (key uVar13):
  - `FUN_141766170(mgr, uVar13, &local_148, 0x10)` —
    league name (D70 seam EXISTS: `g_fn14176...170`).
  - Fail → `log_InlineLogERROR("CLeagueMgr::PlunderWarStart
    cannot find the plundered league[%lu]", ...)` and
    the lVar18 == -2 retry with `FUN_141766250` (D70
    seam EXISTS).
  - Success → build the D71 message:
    - `FUN_1417d8390(local_5a8)` — CMsgLeagueRobOpt ctor
      (D71 ✓ `CtorCMsgLeagueRobOpt`)
    - `FUN_1417d84d0(local_5a8, 4, 0)` — Create(4, 0)
      (D71 ✓ `CreateLeagueRobOpt`)
    - on success → `FUN_1417d8570(local_5a8)` — Serialize
      (D71 ✓ `SerializeLeagueRobOpt`)
    - on failure → immediate dtor pair (see teardown)
  - Build the D69 message:
    - `FUN_1417d5460(local_a18)` (D69 ctor ✓)
    - `FUN_1417d54f0(local_a18, 1, uVar12, *(uint*)(mgr+0x358), ...)`
      — the D69 Create
    - member walk (inner while over `mgr+0x370`'s sibling
      map, plVar20/plVar21/plVar6/plVar7 with the +0x1d
      flags — same inverted-tree iterator as D70):
      - per member: `FUN_1417d5820(local_a18, iVar4)` —
        D69 AppendDword; on FALSE → the flush-and-restart
        dance: `1417d55e0` (Serialize) + `1417d55a0`
        (send) + re-Create + re-Append (ALL D69 ✓).
    - `FUN_1417d5770(local_a18)` — D69 GetCount; nonzero
      → `1417d55e0` (Serialize+send).
  - Name formatting (uVar12 == uVar13 vs not — TWO
    different format strings):
    - `theInstance()` → `pIVar16` (IStringManager)
    - `_snprintf(&local_138, 0x100, fmt, ...)` ×2
    - `FUN_1417d6640(local_12b8)` — CMsgLeagueOpt ctor
      (✓ `CtorCMsgLeagueOpt` in SyndicateCMsgCtors)
    - `FUN_1417d6820(local_12b8, 0x3f, &local_138, 0, uVar12, 0)`
      — ✓ seam `g_fn1417d6820` in SyndicateInviteNotify.h
    - `FUN_1417d66c0(local_12b8)` — CMsgLeagueOpt dtor
      (NOT yet ported — 205 chars, trivial)
  - `FUN_1417d54b0(local_a18, uVar14, pCVar22, uVar23)` —
    D69 AppendDwordString (✓ D69)
  - teardown: `FUN_1417d83e0(local_5a8)` (D71 dtor ✓) and
    the D69 dtor.

### Phase B — the 0x45 message (FUN_1417d6740)
- `FUN_1417d6740(local_e88, 0x45)` — Create on a raw CMsg
  (359 chars, NOT ported) + `FUN_1417d66c0`-family dtor.
- Also references `FUN_1417630d0(mgr, key)` — a map
  lookup on `mgr+0x68` (MSVC tree descent, +0x29 color
  byte, +0x18 key slot at *(node+3)=+0x18 — same kit
  family as D70's maps) and `FUN_141766000(mgr, key, out)`
  (2423 chars) — likely the by-member league-name /
  by-key resolver. BOTH need capstone RAW work.

### Other callees
- `FUN_141743e00/FUN_141743dd0` (497 chars each) —
  interface hops: `(mgr+8)` service → vt+0x10 query
  (magic 4) → vt+0x78 call. Seam-only candidates.
- `SafeCopy` ×4, `log_InlineLogERROR` ×6, `_snprintf` ×4,
  `theInstance` ×4 — seams.
- `FUN_141766000` — 2423 chars: needs RAW (probable
  name/owner resolution used in the uVar12 != uVar13
  branch).
- `FUN_1417630d0` — 1856 chars: map/mgr+0x68 lookup.

## Reuse map (already green)
| raw | ported as |
|---|---|
| 1417d5460/1417d54f0/1417d54b0/1417d5820/1417d55e0/1417d55a0/1417d5770 | D69 CMsgLeagueBeRob family |
| 1417d8390/1417d84d0/1417d8570/1417d83e0 | D71 CMsgLeagueRobOpt family |
| 141766170/141766250 | D70 name getters (SyndicateLeagueBeRobFlow seams) |
| 1417d6640 | CtorCMsgLeagueOpt (SyndicateCMsgCtors) |
| 1417d6820 | g_fn1417d6820 (SyndicateInviteNotify.h) |

## TODO for the D72 port
1. RAW-capstone 1417d6740 (CMsg Create 0x45), 1417d66c0
   (LeagueOpt dtor), 1417d66c0-family, 1417630d0,
   141766000, 141743e00/dd0.
2. New seams: SafeCopy, snprintf-format theInstance texts
   (record the two format strings from the .rdata),
   the type-0x3f send, the 0x45 send.
3. Port skeleton: SyndicateLeagueRobOptFlow.{h,cpp} with
   the two-phase walk; fixture trees like D70's kit.
4. Test syndicate_d72_test.cpp; regression 76/76 x6;
   ASan clean; commit + push.
