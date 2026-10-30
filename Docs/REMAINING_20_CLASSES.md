# المتبقي الحقيقي بعد D99 — 20 كلاساً (بدليل RTTI، لا تقدير)

**الطريقة:** استخراج كل أسماء RTTI من `Syndicate.dll`
(`.?AV<Name>@@` و`.?AV<Name>@syndicate@@`) ثم طرح كل اسم له
هيدر في `modules/syndicate/src/` وطرح الـ21 مكتبة الخارجية
المستثناة بقرار المشروع. الناتج = 20 كلاس منطق لعبة فعلي.

| الكلاس | vtable | الحالة |
|---|---|---|
| `CMsgLeagueBeRobPB` | `0x141841318` | **12/12 مكتملة** (D99) |
| `CMsgLeagueBeRobRePB` | `0x141841130` | 0/12 |
| `CMsgLeagueRobOptPB` | `0x1418423d8` | **12/12 مكتملة** (D100) |
| `CMsgLeagueRobOptServerPB` | `0x141842278` | **12/12 مكتملة** (D100) |
| `CMsgLeagueTokenPB` | `0x141842670` | 0/12 |
| `CMsgInvadeWarning` | TBD | 0/12 |
| `CMsgLeagueBeRob` | TBD | 0/12 |
| `CMsgLeagueOpt` | TBD | 0/12 |
| `CMsgLeagueRobOpt` | TBD | 0/12 |
| `CMsgLeagueToken` | TBD | 0/12 |
| `CMsgLog` | TBD | 0/12 |
| `CMsgSelfSynMemAwardRank` | TBD | 0/12 |
| `CMsgSynAttrInfo` | TBD | 0/12 |
| `CMsgSynBaseProffer` | TBD | 0/12 |
| `CMsgSynChgDomName` | TBD | 0/12 |
| `CMsgSynDomain` | TBD | 0/12 |
| `CMsgSynMemberInfo` | TBD | 0/12 |
| `CMsgSynMemberList` | TBD | 0/12 |
| `CMsgSynProffer` | TBD | 0/12 |
| `CMsgSynProfferRank` | TBD | 0/12 |
| `CMsgSynRecruitAdvertising*` (3) | TBD | 0/12 |
| `CMsgSyndicate` | TBD | 0/12 |
| `CrossMeritMgr` · `CLeague` · `CToken` | TBD | غير PB |

> أرقام الـvtable غير المعروفة (TBD) تُستخرج بالأداة:
> `python3 tools/find_vtables.py <ClassName>`
