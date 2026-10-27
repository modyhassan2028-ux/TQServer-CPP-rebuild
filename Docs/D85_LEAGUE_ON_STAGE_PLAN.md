# D85 — CCountry::OnLeagueOnStage (FUN_141736d40)

## الهوية
أضخم دالة متبقية (~647 سطرًا، L153595 مجاور...
المصدر: country.cpp — المسار الحرفي في اللوج:
`f:\version\cqserver-78.0.11-1204\modules\syndicate\src\country.cpp`
param_1 = CCountry this، param_2 = idLeague/المرشح،
param_4 = szName. **الغرض:** صعود دوري الدولة
(الملك 4000 + تسلسل "البلد مرة أخرى").

## البنية RAW (7 مراحل)
### 1. بوابة إنشاء الملك (سطر 49)
`if (this[0xb] == 0)`:
- king = FUN_141721be0(this, this[10] (int),
  *(u32*)(this+0x54), 1000)
- this[0xb] = king؛ صفر → لوج حرفي
  `"CCountry::OnLeagueOnStage, create king fail, idLeague[%lu]."` → return
- نجح → FUN_141721780(this, 0)

### 2. تحديد المرشح على العرش (سطور 61-355)
`bVar4 = false؛ if (param_2 != 0):`
- **مسح A** على خريطة `[0x22]` (العقد: key u32
  عند +0xc، القيمة node[4]): البحث عن رتبة 4000
  (الملك الحالي) ومقارنة id مع param_2:
  - العقدة بلا قيمة → لوج DAT
  - `sVar6 == 4000` → كسر (وجدنا الملك)
- عند نهاية الخريطة (plVar10 == plVar11):
  - **لو ملك موجود plVar14 ≠ 0**: id =
    vt+0x10(plVar14,1) ثم vt+0x40:
    - **id ≠ param_2** (تغيير الملك):
      1. FUN_14172b160(this+0x22, lower_bound probe)
      2. مسح B على `[0x40]`/`[0x3a]` (m_mapHaremInfo):
         بحث by id؛ عند الفشل لوج **سطر 0x276**
         حرفي `"iterInfo != m_mapHaremInfo.end()"`
         وإلا FUN_14172b870(this+0x3a, insert)
      3. FUN_14172f500(this, 4000)
      4. FUN_1417360a0(this, plVar14, pcVar18, param_4)
      5. FUN_141731d50(this, param_2)
      6. bVar4 = true → goto LAB_1417373ed
    - **id == param_2** (نفس الملك): bVar4 = false
- مسح ثانٍ (سطر 197) لغير الموجود 4000: عند
  النهاية → FUN_141731d50(this, param_2)؛ bVar4 = true

### 3. LAB_1417373ed (سطر 358)
FUN_1417524d0(this[1], this[10], 1)

### 4. الخريطة المؤقتة (سطور 360-380)
- proxy = operator_new(8) (نمط proxy الشجري
  المعروف من D70-D72)
- head = FUN_141726c30()؛ تهيئة الحارس
  (بايت +0x1d = 1، مؤشرات ذاتية، size=0)
- FUN_14172f970(this, &tempMap) — ملء المرشحين

### 5. مسح C على الخريطة المؤقتة (سطور 382-430)
لكل عقدة (key عند +0xc):
- الحارس غير المتطابق → _invalid_parameter_noinfo
- `if (key != param_2 || !bVar4)`:
  - rank = FUN_14172ecb0(this, key)
  - FUN_1417524d0(this[1], key, rank)
- التقدم: خليفة MSVC الحرفي المتضمن
  (نمط +0x1d يسار/يمين — نفس أدوات D70/D72
  لكن مضمّن RAW هنا، يجب نسخه حرفيًا)

### 6. مسح D على `[0x1a]` (سطور 432-490) — لوج سطر **0x299**
لكل عقدة: value = node[4]؛ صفر → لوج؛ وإلا:
- obj3 = vt+0x10(value, 3)؛ leaderNameId = vt+0x30(obj3)
- FUN_141768020(this[1], leaderNameId)
- كلام `"STR_LEAGUE_COUNTRY_AGAIN"`:
  _snprintf(buf, 0x200, str)
- vt+0x28(this, vt+0x40(vt+0x10(value,1)), buf,
  **0xffff00**) — البث باللون الأصفر الأصلي

### 7. مسح E على `[0x12]` (سطور 492-550) — نفس الجسم، لوج سطر **0x2a7**
### 8. مسح F على `[0x22]` (سطور 552-630) — لوج سطر **0x2b5**
لكل عضو: id = vt+0x40(vt+0x10(value,1))؛
`if (id != param_2 || !bVar4)` → نفس كلام
STR_LEAGUE_COUNTRY_AGAIN بالبث 0xffff00

### 9. التنظيف (سطور 632-645)
FUN_14172a410(tempMap — clear) ؛ delete الحارس؛
delete الـ proxy. ASan: يجب صفر تسريب.

## Seams (14 دالة + vt)
FUN_141721be0 (إنشاء ملك)، FUN_141721780،
FUN_141731d50 (تنصيب)، FUN_14172b160 (بحث
خريطة)، FUN_14172b870 (إدراج)، FUN_14172f500
(رتبة 4000)، FUN_1417360a0 (نقل)، FUN_141726c30
(رأس شجرة)، FUN_14172f970 (ملء)، FUN_14172ecb0
(رتبة عضو)، FUN_14172a410 (تفريغ)،
FUN_1417524d0 (تحديث عضو)، FUN_141768020
(اسم زعيم)، log_InlineLogERROR، theInstance/
GetStr، _snprintf، vt: +0x10(1/3)، +0x30،
+0x40، +0x28 (بث).

## الاختبار المخطط (~45 تأكيدًا)
1. this[0xb]=0 + فشل الإنشاء → لوج create king
   + return (لا مسوحات).
2. نجاح الإنشاء → 141721780 مرة واحدة.
3. param_2=0 → قفزة مباشرة للمسح D/E/F
   (كل الأعضاء يبثون، لا 141731d50).
4. ملك حالي id==param_2 → bVar4=false →
   المسح C يرتب الجميع والمسح F يبث للجميع.
5. ملك حالي id≠param_2 → مسار تغيير الملك:
   14172b160/14172b870 (نجاح harem) →
   14172f500(4000) + 1417360a0 + 141731d50 →
   bVar4=true → المسح C يتخطى param_2 فقط
   والمسح F لا يبث لparam_2.
6. فشل harem → لوج 0x276 الحرفي.
7. قيم null في المسحات D/E/F → لوج
   0x299/0x2a7/0x2b5.
8. تنسيق البث: buf بنص STR_LEAGUE_COUNTRY_AGAIN
   واللون 0xffff00.
9. التنظيف: delete ×2 — ASan صفر.

## ملاحظات البورت
- المسوحات: الخليفة الحرفي المضمّن (نمط
  +0x29/+0x1d) يُنسخ كما هو من RAW وليس عبر
  عدّاد STL حديث — مثل D82 تمامًا.
- 6 خرائط تُمسح: [0x1a]/[0x20]، [0x12]/[0x18]،
  [0x22]/[0x28]، [0x3a]/[0x40]، المؤقتة.
