# المتبقي الحقيقي بعد D99 — 20 كلاساً (بدليل RTTI، لا تقدير)

**الطريقة:** استخراج كل أسماء RTTI من `Syndicate.dll`
(`.?AV<Name>@@` و`.?AV<Name>@syndicate@@`) ثم طرح كل اسم له
هيدر في `modules/syndicate/src/` وطرح الـ21 مكتبة الخارجية
المستثناة بقرار المشروع. الناتج = 20 كلاس منطق لعبة فعلي.

| الكلاس | vtable | الحالة |
|---|---|---|
| `CMsgLeagueBeRobPB` | `0x141841318` | **12/12 مكتملة** (D99) |
| `CMsgLeagueBeRobRePB` | `0x141841118` | **12/12 مكتملة** (D101) |
| `CMsgLeagueRobOptPB` | `0x1418423d8` | **12/12 مكتملة** (D100) |
| `CMsgLeagueRobOptServerPB` | `0x141842278` | **12/12 مكتملة** (D100) |
| `CMsgLeagueTokenPB` | `0x141842658` | **12/12 مكتملة** (D101) |
| `CMsgInvadeWarning` | `0x14183bf30` | **5/5 مكتملة** (D118) |
| `CMsgLeagueBeRob` | TBD | 0/12 |
| `CMsgLeagueOpt` | TBD | 0/12 |
| `CMsgLeagueRobOpt` | TBD | 0/12 |
| `CMsgLeagueToken` | TBD | 0/12 |
| `CMsgLog` | `0x14182e4a0` | **5/5 مكتملة** (D117) |
| `CMsgSelfSynMemAwardRank` | TBD | 0/12 |
| `CMsgSynAttrInfo` | TBD | 0/12 |
| `CMsgSynBaseProffer` | TBD | 0/12 |
| `CMsgSynChgDomName` | TBD | 0/12 |
| `CMsgSynDomain` | TBD | 0/12 |
| `CMsgSynMemberInfo` | `0x14183df00` | **5/5 مكتملة** (D119) |
| `CMsgSynMemberList` | TBD | 0/12 |
| `CMsgSynProffer` | TBD | 0/12 |
| `CMsgSynProfferRank` | TBD | 0/12 |
| `CMsgSynRecruitAdvertising*` (3) | TBD | 0/12 |
| `CMsgSyndicate` | TBD | 0/12 |
| `CrossMeritMgr` · `CLeague` · `CToken` | TBD | غير PB |

> أرقام الـvtable غير المعروفة (TBD) تُستخرج بالأداة:
> `python3 tools/find_vtables.py <ClassName>`

---

## تحديث D102 — الكلاسات الباقية ليست Protobuf (مُتحقَّق) [2026-10-30]

**اكتشاف معماري:** الملف يحتوي **12 جدول vtable فقط** من نمط PB
(فتحة 5 = `0x1417de5c0` وفتحة 10 = `0x1417dee40`) وهي بالضبط
الكلاسات الـ12 المنقولة. كل ما تبقّى من الجرد هو **رسائل
`tq::CMsg`** لا `MessageLite`، وتخطيطها 5 فتحات:

| # | الدور |
|---|-------|
| 0 | dtor حاذف (يكتب `<Class>::vftable` ثم `tq::CMsg::vftable`) |
| 1 | `Create` — يستدعي `tq::CMsg::Create` ثم يتحقق من نوع الرسالة |
| 2 | `tq::CMsg::Process(OBJID idActor, void* pInfo)` — هيكل خطأ مشترك `0x14177e2f0` |
| 3 | `Process` الخاص بالكلاس |
| 4 | `tq::CMsg::Process(void* pInfo)` — هيكل خطأ مشترك `0x14177e2d0` |

### عناوين vtables مؤكَّدة (فحص: الفتحة 0 تكتب اسم الكلاس نفسه)

| الكلاس | vtable | dtor |
|--------|--------|------|
| `CMsgLog` | `0x14182e4a0` | `0x14177e3e0` |
| `CMsgSynChgDomName` | `0x14182e520` | `0x14177e460` |
| `CMsgInvadeWarning` | `0x14183bf30` | `0x1417d52f0` |
| `CMsgLeagueBeRob` | `0x14183c008` | `0x1417d5710` |
| `CMsgLeagueOpt` | `0x14183c5a8` | `0x1417d7260` |
| `CMsgLeagueRobOpt` | `0x14183cc78` | `0x1417d86a0` |
| `CMsgLeagueToken` | `0x14183cfa0` | `0x1417d93b0` |
| `CMsgSelfSynMemAwardRank` | `0x14183d558` | `0x1417da810` |
| `CMsgSynAttrInfo` | `0x14183d768` | `0x1417dabe0` |
| `CMsgSynBaseProffer` | `0x14183d888` | `0x1417dadc0` |
| `CMsgSynCompete` | `0x14183dad0` | `0x1417db260` |
| `CMsgSyndicate` | `0x14183dc10` | `0x1417dca00` |
| `CMsgSynDomain` | `0x14183de00` | `0x1417dcff0` |
| `CMsgSynMemberInfo` | `0x14183df00` | `0x1417dd1e0` |
| `CMsgSynMemberList` | `0x14183e010` | `0x1417dd690` |
| `CMsgSynProffer` | `0x14183e180` | `0x1417dd9a0` |
| `CMsgSynProfferRank` | `0x14183e2b0` | `0x1417ddc10` |

### مرجع CMsgLog (أصغر وحدة في الموجة الجديدة)

- **النوعان المقبولان:** `0x3ea` و`0x3eb` (يُكتب `0` أو `1` في
  `pInfo + 8`). أي نوع آخر → `Create` يرجع false.
- **Process:** `FUN_1417b6210()` (مدير السينديكيت) ثم فرعان:
  `0` → `FUN_1417b7010(mgr, pInfo)`، `1` → `FUN_1417ac620(mgr, pInfo)`،
  وإلا السجل الحرفي:
  `"syndicate::CMsgLog::Process(idActor), idActor:%d, Type:%d, MsgType:%d"`

**متطلب سابق للوحدة التالية:** تخطيط `tq::CMsg` الأساسي
(`tq::CMsg::vftable`, `Create`, `Init`, وحقول `+0x50` و`+0x2040`)
لازم يُنقل قبل معالجات الرسائل.

## ملاحظات التحقق (2026-10-30)

- الأدوات `find_vtables.py` تعيد MISS للأسماء
  `CMsgSynAttrInfo`, `CMsgSynBaseProffer`, `CMsgSynDomain`, `CMsgSyndicate`,
  `CMsgSynMemberList`, `CMsgSynProffer`, `CMsgSynRecruitAdvertising*`
  بصيغتها المجرّدة — يلزم تمرير الاسم المؤهّل (`syndicate::…`) أو البحث
  عن نوع RTTI البديل قبل بناء الوحدات التالية.
- بقية أسماء هذا المستند بصيغة `tq::CMsg` بـ5 فتحات، وليست 12.
- مسار المصدر الأصلي للرسائل: `modules/syndicate/src/msg/`
  (مؤكَّد من نص CHECKF في D119) — نقل ملفات الرسائل إلى المجلد ده
  مطلوب لمطابقة الشجرة الأصلية.

## الجدول المرجعي الكامل (مستخرج من tools/syndicate_vtables.json — 2026-10-30)

| الكلاس | vtable | الفتحات | الحالة |
|---|---|---|---|
| `CMsg` | `0x14182e368` | 5 | متبقية |
| `CMsgInvadeWarning` | `0x14183bf30` | 5 | **منقولة** |
| `CMsgLeagueBeRob` | `0x14183c008` | 5 | متبقية |
| `CMsgLeagueBeRobPB` | `0x141841318` | 12 | **منقولة** |
| `CMsgLeagueBeRobRePB` | `0x141841118` | 12 | **منقولة** |
| `CMsgLeagueConcubines` | `0x14183c1e0` | 5 | **منقولة** |
| `CMsgLeagueConcubinesInfoPB` | `0x1418415e8` | 12 | **منقولة** |
| `CMsgLeagueConcubinesPB` | `0x141841748` | 12 | **منقولة** |
| `CMsgLeagueImperialCourtList` | `0x14183c398` | 5 | **منقولة** |
| `CMsgLeagueInfo` | `0x14183c448` | 5 | **منقولة** |
| `CMsgLeagueList` | `0x14183c4f8` | 5 | **منقولة** |
| `CMsgLeagueOpt` | `0x14183c5a8` | 6 | متبقية |
| `CMsgLeagueOrderStatus` | `0x14183c708` | 5 | **منقولة** |
| `CMsgLeagueOrderStatusInfoPB` | `0x1418419c8` | 12 | **منقولة** |
| `CMsgLeagueOrderStatusPB` | `0x141841b48` | 12 | **منقولة** |
| `CMsgLeaguePalaceGuardsList` | `0x14183c8e8` | 5 | **منقولة** |
| `CMsgLeagueRank` | `0x14183c998` | 5 | **منقولة** |
| `CMsgLeagueRobItemPB` | `0x141841e08` | 12 | **منقولة** |
| `CMsgLeagueRobList` | `0x14183ca70` | 5 | **منقولة** |
| `CMsgLeagueRobListPB` | `0x141841f68` | 12 | **منقولة** |
| `CMsgLeagueRobOpt` | `0x14183cc78` | 5 | متبقية |
| `CMsgLeagueRobOptPB` | `0x1418423d8` | 12 | **منقولة** |
| `CMsgLeagueRobOptServerPB` | `0x141842278` | 12 | **منقولة** |
| `CMsgLeagueSynList` | `0x14183cec8` | 5 | **منقولة** |
| `CMsgLeagueToken` | `0x14183cfa0` | 5 | متبقية |
| `CMsgLeagueTokenPB` | `0x141842658` | 12 | **منقولة** |
| `CMsgLeagueUserMemberList` | `0x14183d1f0` | 5 | **منقولة** |
| `CMsgLog` | `0x14182e4a0` | 5 | **منقولة** |
| `CMsgOverheadLeagueInfo` | `0x14183d3d8` | 5 | **منقولة** |
| `CMsgOverheadLeagueInfoPB` | `0x141842828` | 12 | **منقولة** |
| `CMsgSelfSynMemAwardRank` | `0x14183d558` | 5 | متبقية |
| `CMsgSynAttrInfo` | `0x14183d768` | 5 | متبقية |
| `CMsgSynBaseProffer` | `0x14183d888` | 5 | متبقية |
| `CMsgSynChgDomName` | `0x14182e520` | 5 | متبقية |
| `CMsgSynCompete` | `0x14183dad0` | 5 | **منقولة** |
| `CMsgSynDomain` | `0x14183de00` | 5 | متبقية |
| `CMsgSynMemberInfo` | `0x14183df00` | 5 | **منقولة** |
| `CMsgSynMemberList` | `0x14183e010` | 5 | متبقية |
| `CMsgSynProffer` | `0x14183e180` | 5 | متبقية |
| `CMsgSynProfferRank` | `0x14183e2b0` | 5 | متبقية |
| `CMsgSynRecruitAdvertising` | `0x14183e3f8` | 5 | متبقية |
| `CMsgSynRecruitAdvertisingList` | `0x14183e508` | 5 | متبقية |
| `CMsgSynRecruitAdvertisingOpt` | `0x14183e620` | 5 | متبقية |
| `CMsgSyndicate` | `0x14183dc10` | 5 | متبقية |

**المتبقي: 17 كلاس** — العائلة `tq::CMsg` (5-6 فتحات) كلها موجودة في الخريطة، فلا حاجة للبحث عن vtables بعد الآن.

ملاحظة: `CMsgLeagueRobOpt` و`CMsgLeagueToken` و`CMsgLeagueOpt` Creates فيها استدعاء `ParseFromArray` (مثل `0x1417dedc0`) ورسالة فشل `CMsgLeagueRobOpt::CreateBufMsg ParseFromArray failed ,error：%s` — أعقد من هيكل tq::CMsg البسيط.
