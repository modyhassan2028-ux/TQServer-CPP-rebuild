# PORTING_LOG — سجل بورت TQServer (Conquer Online v6159)

آخر تحديث: 2026-10-23 (بعد commit `76c26c8`)
هذا الملف سجل تسليم: كل اللي اتعمل، المنهجية، وواقفين فين، علشان اللي يكمل بعد كذا يعرف الصورة كاملة.

---

## 1. المشروع والبيئة

- **الهدف:** بورت طبق الأصل لسيرفر Conquer Online v6159 (MsgServer + AccountServer + Loader + CrossServer + كل الـ DLLs) من الكود المفكك.
- **Repo البورت:** `TQServer-CPP-rebuild` (مجلد العمل: `conversations/work/TQServer-CPP-rebuild`).
- **Repo المرجع المفكك:** `conquer-online-v6159-decompiled` (الملف الرئيسي: `Native-Decompiled/MsgServer.exe.decompiled.c`).
- **فهرس الأسماء:** `NameIndex/names_final.tsv` — يربط عناوين الدوال بأسماء مستخرجة (سلاسل لوج، كولجراف). استخدمه دائماً للتسمية.
- **القاعدة:** الـ dump الأصلي كامل محمّل محلياً في MariaDB باسم `cq` (267 جدول). الـ dump الضخم لا يُرفع؛ نسخة السكيما فقط على GitHub.
- **الاختبارات:** native على لينكس ضد القاعدة الحقيقية (`tests/dialog_fidelity_test.cpp` + `tests/orig_db_fidelity_test.cpp` — كلاهما أخضر الآن).
- **البناء:** ملفات ويندوز عبر zig (7 ملفات) — فقط في نهاية جلسة كبيرة أو بطلب صريح. الرفع اليومي كود فقط.

## 2. المنهجية: علاقة القاعدة بالسورس (مهم جداً)

**القاعدة هي "وقود" السيرفر والسورس هو "المحرك".** جدول `cq_action` هو المُفسِّر: كل صف = خطوة منطقية، وعمود `type` يحدد أي كود ينفذها (switch عملاق في `CGameAction::ProcessActionUser`).

**مشكلة موثوقية Ghidra:** الـ switch الأصلي عند سطر 242238 في الـ decompile عليه تحذير صريح `Could not find normalized switch variable to match jumptable` — يعني **أرقام case المعروضة (0x30, 0x37...) غير موثوقة ولا تُحسب منها type مباشرة**.

**الحل — الربط بالمطابقة السلوكية مع صفوف القاعدة:**
1. اقرأ جسم الكود (sscanf format، أسماء العمليات، الدوال المساعدة).
2. افحص صفوف القاعدة الحقيقية لكل type (param patterns + الجداول المرجعية التي تشير لها الصفوف).
3. المطابقة تثبت أي جسم يخدم أي type. أمثلة محسومة:
   - صفوف 1020 تشير لـ ids موجودة في `cq_magictype` (1000 Thunder, 8002 RapidFire) → 1020 = عمليات الماجيك.
   - صفوف 1021 تشير لـ ids موجودة في `cq_weapon_skill_up` (410/420/421...) → 1021 = مهارات السلاح. وسطر اللوق الأصلي نفسه يسميها `ACTION_USER_WEAPONSKILL`.
   - صفوف 1056 = `new/delete/isexit` (مهام)، 1027 = `self %` (فحص الشريك).
4. القاعدة تعرّف البُنى: مثلاً `cq_weapon_skill` (owner_id+type+level+exp) وسجل السلاح في الذاكرة (+0x14 exp, +0x18 level byte) و`cq_weapon_skill_up` (منحنى req_exp/req_uplevtime لكل مستوى).
5. الاختبار النهائي: البورت يجب أن ينتج نفس النتائج التي ينتجها السيرفر الأصلي على نفس الصفوف — لهذا كل اختبار يعمل ضد صفوف حقيقية من القاعدة.

**الأرقام (1001, 1010, 1020...) ليست بكتات (packets).** دي أنواع أكشن داخلية في عمود `type` بجدول `cq_action` — أوامر مفسّر الحوار/المنطق. (بكتات الشبكة لها أرقامها هي أيضاً لكن مساحة مختلفة تماماً ولا علاقة بينهما.)

## 3. اللي خلص (بالتزامت، الأحدث أولاً)

| Commit | النوع/النظام | الوصف |
|---|---|---|
| `76c26c8` | **1021** | مهارات السلاح (ACTION_USER_WEAPONSKILL, case 0xf): سجلات `cq_weapon_skill`، check (مطلوب <= الحالي)، learn = AwardWeaponSkill مع بوابة max-level من `cq_weapon_skill_up`، addexp على المنحنى، addlevtime. + اختبارات 1020 على صفوف حقيقية |
| `b05c828` | **1060, 1064** | مقارنة رقمية (`var(N) > x`) وعملية حسابية (`var(N) += x`) — عنقود متغيرات الأكشن |
| `3ff3c24` | **1062, 1063** | مقارنة نصية strcmp (شرط type==1062 الأصلي) وتعيين نصي `var(N) = str` |
| `5fcc182` | **1065** | فحص عائلة العتاد المُعدّ (خوذة/سلاح/فستان/خاتم) عبر singleton |
| `95e2645` | **1061** | تعيين متغير رقمي `var(N) = x` (FUN_140164520 على مصفوفة int64 في CUser) |
| `4cdc7fe` | **1027** | فحص الشريك (mate-id, FUN_140164440) — الـ param مهمل في الأصل عمداً |
| `eddf673` | **1056** | عمليات المهام new/delete/isexit عبر ABI أصلية من TaskDetail.dll |
| `02e4d42` | **1057** | متغيرات task_detail (data1-7/notify/complete/overtime) |
| `5d5b076` | **1073, 1074** | عدادات stc(type,data): فحص العدد + التعيين/الزيادة |
| `eaa8b47` | **1003** | الانتقال (teleport) + CUser::FlyMap، خرائط من cq_map |
| `f10a0d6` | **1010, 1085** | قناة كلام NPC + gmlog + جدول remap الـ switch |
| `ddf3634` | ماجيك exp | AddMagicExp/AwardMgcTime (FUN_1404918c0/140491be0) بمنطق CalcTimeToExp الأصلي |
| `3243e8c` | CPlayerMagic | بورت كامل لسجلات cq_magic + pool الـ cq_magictype |
| `06a19b4` | **1001 (جزئي!), 1020** | شروط بيانات اللاعب + فحوص الماجيك + ABI استضافة الموديولات |

**أنظمة أخرى جاهزة:** CPlayerMagic كامل (Learn/UpLevel/Delete/AddExp/AwardMgcTime مطابقة FUN_1404939c0/14048fd10/140493f70/1404918c0/140491be0)، Lua 5.4 NPC bridge، جسر CrossServer، اللودر، والاختبارات الأصلية للقاعدة.

## 4. الغرائب الأصلية المحفوظة عمداً (لا "تصلحها")

- **1001/1020:** عملية غير معروفة في 1020 → يرجع 1 (نجاح) بعد لوق.
- **1020 check بـ 3 args:** مساواة **حرفية** بالمستوى (`level == x`) وليس `>=`.
- **1021 learn بدون صف cq_weapon_skill:** لا يتعلَّم لكن يرجع 1.
- **1021 addlevtime:** القيمة نفسها مهملة (مجرد بوابة >=1)؛ النتيجة تصعيد مستوى واحد.
- **1021 uplevel:** غير مدعومة أصلاً → ترجع 0 (يوجد صف واحد فقط بهذا الشكل).
- **1027:** الـ param مهمل كلياً رغم أن الصفوف تحتويه.
- **أرقام case في Ghidra:** لا تُستخدم أبداً في الاشتقاق (انظر المنهجية).

## 5. واقفين فين + التالي

### أولاً: إكمال 1001 (الهدف التالي، 10,775 صف)
يوجد بورت جزئي (`ProcessDataCondition`) يدعم 10 حقول فقط (life/mana/money/e_money/level/exp/pk/strength/profession/metempsychosis).
**الحصيلة الحقيقية من القاعدة أكبر بكتير:** profession (3,220), level (2,261), money (1,233), exp (1,093), **vip (917)**, e_money (882), metempsychosis, **e_money_mono (196)**, pk, life, **mentor (74), rank (52), iterator, transform, speed, force, cultivation, xp, mana, health, virtue, e_money_trial, look, soul, strengthvalue, ep, rankshow, business, storage_money** — بالإضافة لعمليات `=`, `+=`, `-=` (وأيضاً `ep +=`, `storage_money +=`).
**المطلوب:** قراءة جسم الـ 1001 من الـ decompile (جسم "field op value" — سياقه switch على اسم الحقل) وبورت قائمة الحقول كاملة + عمليات الجمع/الطرح/التعيين، ثم اختبارات على صفوف حقيقية (مثل 5025700 `level == 132`, 6074065 `money += 400`, 9232063 `vip > 3`).

### بعدها — الأنواع الكبيرة المتبقية (حسب عدد الصفوف)
| النوع | الصفوف | المعنى (من عينات القاعدة) |
|---|---|---|
| 501 | 20,956 | صفوف مكافآت/award (معظمها param فارغ = خطوات قفز chain) |
| 101 | 20,343 | نص حوار NPC (`~` بدل المسافة) |
| 102 | 20,158 | خيارات الحوار (نص + task id) |
| 1085 | 13,392 | gm log (**مبورت**: f10a0d6) |
| 1010 | 12,379 | كلام NPC (**مبورت**) |
| 121 | 11,281 | قيم ثنائية ("1 2", "312 10000" — غالباً rand/جدولة) |
| 105 | 6,168 | رسائل نظام (You received... / pack opens) |
| 502 | 6,007 | award بباراميتر |
| 801 | 4,130 | (id_next على شكل "52"/"53"/"54" — يلزم تحليل) |
| 1066 | 0 صفوف | مبورت ضمن العنقود |

### منهجية الاختبار الثابتة
كل نوع جديد: اقرأ الجسم من الـ decompile → طبّق مع صفوف القاعدة → اكتب test block في `dialog_fidelity_test.cpp` بـ asserts على صفوف حقيقية (مُعلَّق عليها ids الجداول المرجعية) → `origdb_test` + `dialog_test` أخضر → commit + push (كود فقط).

## 6. بيئة البناء السريعة

```bash
W=/app/conversations/6ada078e9883f31f19597098/work/.objt
F="-std=c++17 -O0 -I. -IExe/MsgServer -Iinclude -ICore/CQBase -ICore/DB -ICore/Root -IExe/MsgServer/CrossServer -IExe/CQCrossServer -Ivendor/lua -D__declspec(x)="
g++ $F -c <file.cpp> -o "$W/<name>.o"
# ربط الاختبارات:
OBJS=$(find $W -name '*.o' ! -name '*main.cpp*' ! -name '*CrossServer*' ! -name '*orig_db*' | tr '\n' ' ')
g++ $OBJS -o $W/dialog_test -lpthread ./build/liblua_native.a
mariadb -u root cq   # القاعدة الأصلية الحية
```
