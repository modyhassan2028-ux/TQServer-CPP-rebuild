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

## متبقٍ حقيقي (12) — يحتاج تحليل جسم

| الكلاس | vtable | الفتحات |
|---|---|---|
| `CMsgLeagueConcubines` | `0x14183c1e0` | 5 |
| `CMsgLeagueConcubinesInfoPB` | `0x1418415e8` | 12 |
| `CMsgLeagueConcubinesPB` | `0x141841748` | 12 |
| `CMsgLeagueOrderStatus` | `0x14183c708` | 5 |
| `CMsgLeagueOrderStatusInfoPB` | `0x1418419c8` | 12 |
| `CMsgLeagueOrderStatusPB` | `0x141841b48` | 12 |
| `CMsgLeagueRobItemPB` | `0x141841e08` | 12 |
| `CMsgLeagueRobList` | `0x14183ca70` | 5 |
| `CMsgLeagueRobListPB` | `0x141841f68` | 12 |
| `CMsgOverheadLeagueInfo` | `0x14183d3d8` | 5 |
| `CMsgOverheadLeagueInfoPB` | `0x141842828` | 12 |

## مكتبات خارجية — مستثناة بقرار المشروع (21)

`ArrayInputStream`، `ArrayOutputStream`، `Closure`، `CopyingInputStream`، `CopyingInputStreamAdaptor`، `CopyingOutputStream`، `CopyingOutputStreamAdaptor`، `FatalException`، `FunctionClosure0`، `IModule`، `IProvider`، `ISynMngModify`، `MessageLite`، `StringOutputStream`، `ZeroCopyInputStream`، `ZeroCopyOutputStream`، `bad_alloc`، `length_error`، `logic_error`، `out_of_range`، `type_info` — كود protobuf/CRT، مش جزء من منطق اللعبة.

**تصحيح للجرد القديم:** «52 كلاس متبقٍ» كان رقمًا مبنيًا على تقدير، والواقع من الثنائي:
42 كلاس غير موجود باسمه في الشجرة، منهم 21 مكتبة خارجية مستثناة و9 اتغطّوا في هذه الدفعة،
فالباقي الحقيقي من منطق اللعبة **12 كلاس** فقط.
