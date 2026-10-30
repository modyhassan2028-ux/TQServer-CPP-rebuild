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
