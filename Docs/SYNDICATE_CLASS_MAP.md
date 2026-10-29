# خريطة كلاسات Syndicate.dll — الحالة الحقيقية (2026-10-29)

استُخرجت من الـRTTI مباشرة (`tools/rtti_vtables.py`): **75 كلاس** و**860 فتحة vtable**.

## منقول في هذه الدفعة (9)

| الكلاس | vtable | الفتحات |
|---|---|---|
| `CMsgLeagueImperialCourtList` | `0x14183c398` | 5 |
| `CMsgLeagueInfo` | `0x14183c448` | 5 |
| `CMsgLeagueList` | `0x14183c4f8` | 5 |
| `CMsgLeaguePalaceGuardsList` | `0x14183c8e8` | 5 |
| `CMsgLeagueRank` | `0x14183c998` | 5 |
| `CMsgLeagueSynList` | `0x14183cec8` | 5 |
| `CMsgLeagueUserMemberList` | `0x14183d1f0` | 5 |
| `CMsgSynCompete` | `0x14183dad0` | 5 |
| `CSynManager` | `0x14183b430` | 2 |

## منقول في D115 (4) — أغلفة الرسائل ذات مدمرات الأعضاء

| الكلاس | vtable | الفتحات | المدمر |
|---|---|---|---|
| `CMsgLeagueConcubines` | `0x14183c1e0` | 5 | `0x1417d5c60` → `0x1417eb830` |
| `CMsgLeagueOrderStatus` | `0x14183c708` | 5 | `0x1417d7550` → `0x1417ed1a0` |
| `CMsgLeagueRobList` | `0x14183ca70` | 5 | `0x1417d8050` → `0x1417eea60` |
| `CMsgOverheadLeagueInfo` | `0x14183d3d8` | 5 | `0x1417d99a0` → `0x1417f2400` |

أجسام مدمرات الأعضاء نفسها منقولة حرفياً في
`modules/syndicate/src/CMsgPBMemberDtors.cpp`: ‏0x1417eb830،
0x1417ed1a0، 0x1417eea60 (متجه مؤشرات عند +0x38/+0x44) و
0x1417f2400 (متجه نصوص عند +0x48/+0x54 يمر بـ 0x1417e0320)،
والأساس المشترك 0x1417de5a0 الذي يكتب
`MessageLite::vftable` = **0x14183eee8** (مقروء من
`lea 0x60937(%rip)` بـ objdump، لا تخمين).

## متبقٍ حقيقي (7) — كلاسات PB الاثنا-عشرية

| الكلاس | vtable | الفتحات |
|---|---|---|
| `CMsgLeagueConcubinesInfoPB` | `0x1418415e8` | 12 — **مكتملة 12/12** (D90+D91+D93) |
| `CMsgLeagueConcubinesPB` | `0x141841748` | 12 — **6 منقولة** (dtor/نوع/New/Clear/Init/cached) |
| `CMsgLeagueOrderStatusInfoPB` | `0x1418419c8` | 12 — **مكتملة 12/12** (D92+D94) |
| `CMsgLeagueOrderStatusPB` | `0x141841b48` | 12 — **مكتملة 12/12** (D92+D95) |
| `CMsgLeagueRobItemPB` | `0x141841e08` | 12 — **6 منقولة** |
| `CMsgLeagueRobListPB` | `0x141841f68` | 12 — **6 منقولة** |
| `CMsgOverheadLeagueInfoPB` | `0x141842828` | 12 — **6 منقولة** |

## مكتبات خارجية — مستثناة بقرار المشروع (21)

`ArrayInputStream`، `ArrayOutputStream`، `Closure`، `CopyingInputStream`، `CopyingInputStreamAdaptor`، `CopyingOutputStream`، `CopyingOutputStreamAdaptor`، `FatalException`، `FunctionClosure0`، `IModule`، `IProvider`، `ISynMngModify`، `MessageLite`، `StringOutputStream`، `ZeroCopyInputStream`، `ZeroCopyOutputStream`، `bad_alloc`، `length_error`، `logic_error`، `out_of_range`، `type_info` — كود protobuf/CRT، مش جزء من منطق اللعبة.

**تصحيح للجرد القديم:** «52 كلاس متبقٍ» كان رقمًا مبنيًا على تقدير، والواقع من الثنائي:
42 كلاس غير موجود باسمه في الشجرة، منهم 21 مكتبة خارجية مستثناة و9 اتغطّوا في هذه الدفعة،
فالباقي الحقيقي من منطق اللعبة **12 كلاس** فقط.
