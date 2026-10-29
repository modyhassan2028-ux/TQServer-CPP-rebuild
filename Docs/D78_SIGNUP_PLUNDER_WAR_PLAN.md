# D78 — CSyndicateLogic::SignUpPlunderWarFromClient (FUN_1417c2470)
> مصدر واحد: المفكك v6159 (Syndicate.dll @1417c2470، 600
> سطر). أول دالة من CSyndicateLogic في سلسلة النهب (param_1
> = مصفوفة الـ logic: param_1[1] كائن الـ vt، param_1[10]
> = CLeagueMgr). الحالة: محللة، البورت خطوة "كمل" القادمة.

## التوقيع
SignUpPlunderWarFromClient(logic, uUser, nCount, pTargets,
bSupport(param_5), uParam6)

## البنية RAW
1. **البوابات**: uUser != 0؛ 1 <= nCount <= 10؛
   **vt+0x278** == 0 (الحرب لم تبدأ)؛
   **FUN_14174ebd0**(mgr) == 0؛ **vt+0x4a8** != 0؛
   **FUN_1417630d0**(mgr, league) != 0؛ **vt+0x568** !=
   0 (مفتاح العضو)؛ **FUN_141766a70**(mgr, key) == false.
2. **بناء vector\<u32\> حقيقي** (MSVC inline: OpNew(8)
   proxy + FUN_14172d120 insert): لكل هدف: إن كان
   == myLeague(vt+0x3f0) → **FUN_14174e3f0**(mgr) ثم تركيب
   myLeague*1e6 + الهدف؛ وإلا → **FUN_141766950**(mgr, id).
   تجاهل الصفري والمكرر مع مفتاح العضو (uVar6 != uVar9).
   فارغ → تنظيف كامل (delete الـ buffer + proxy) + خروج.
3. **الرمز (Token)**: **FUN_14174bac0**(league, 0x65) أو
   إعادة **FUN_14174bbe0**(league, 0x65, ...) — فشل →
   تنظيف؛ ثم id الرمز بـ **FUN_1417d4ed0** وصف الجدول بـ
   **FUN_141764870** — null → لوج DB
   "table:cq_token_type, can not find token_id[%lu]"
   (المسار الأصلي f:\version\cqserver-78.0.11-1204) + تنظيف.
4. **نص التسجيل**: std::string ctor ثم
   **FUN_1417b2570**(logic, user, league, token, row, str)
   → فشل → dtor الـ string + تنظيف.
5. **سقوف الأهداف**: pplVar16 = **FUN_1417440d0**(league)
   (العدد الحالي؟) و lVar18 = vt+0x10 ثم vt+0x58 (السقف).
   - bSupport == 0: **FUN_14174e940**(mgr) < 1 → تنظيف؛
     وإلا pages = **ceil**((lVar18 - pplVar16)/config) ثم
     **عائلة D71 RobOpt**: ctor 1417d8390 + create(1,
     pages) + حلقة الإلحاق **FUN_1417d8810**(msg, id) مع
     لوج over-size وbreak، ثم Serialize 1417d8570 + العدد
     1417d8700 + الإرسال.
   - فحوص param_6 (0 → خروج؛ uVar6 < param_6 → خروج).
6. **الذيول**: نص الرسالة عبر IStringManager
   _snprintf(buf+0x20, 0x200, format)؛
   **FUN_141744130**(league, pplVar16-lVar18, 1)؛ تحديث
   الرمز: **FUN_1417d4f30**(token, 3, id+1, 0) و(4,
   uVar11, 1)؛ **FUN_141745580**(league, c88)؛ جلب
   الاسمين **FUN_141766b60**(mgr, key, out, 0x10) و
   **FUN_141766d10**(mgr, id, out, 0x10)؛ ثم عائلتا رسالة
   جديدتان: 1417d6110/1417d61c0/1417d6160 (مع
   FUN_1417b5370) و1417d7350/1417d73e0/1417d7770/1417d7440/
   1417d73a0 (فحص 1417d4e70/1417d4ed0 والسقوف).
7. **التنظيف الموحد** في كل مسار: delete الـ vector
   buffer + proxy + string dtor.

## الـ seams الجديدة (~14)
- البوابات: FUN_14174ebd0، FUN_141766a70
- vector: FUN_14172d120 (insert) + OpNew(8)/OpDelete موجودتان
- الأهداف: FUN_14174e3f0، FUN_141766950، FUN_14174e940
- الرمز: FUN_14174bac0، FUN_14174bbe0، FUN_1417d4ed0،
  FUN_1417d4e70، FUN_1417d4f30، FUN_141764870
- العصبة/النص: FUN_1417b2570، FUN_1417440d0، FUN_141744130،
  FUN_141745580، FUN_141766b60، FUN_141766d10
- الرسالتان الجديدتان: 1417d6110/1417d61c0/1417d6160 +
  1417d7350/1417d73e0/1417d7770/1417d7440/1417d73a0 +
  FUN_1417b5370
- IStringManager _snprintf: seam بسيط (buf, cap, fmt)
- المعاد استخدام: D71 RobOpt كاملة + vt+0x278/0x4a8/0x568/
  0x3f0 + FUN_1417630d0

## خطة الاختبار (~32 تأكيدًا)
البوابات السبعة؛ بناء الـ vector (التركيب المركب
myLeague*1e6+target، التكرار، الصفري، الفارغ)؛ فشل الرمز
(المساران)؛ لوج الرمز المفقود؛ فشل نص التسجيل؛ مسار
ceil/RobOpt (مع ceil دقيق 1/2 صفحات، over-size break)؛
فحوص param_6؛ الذيول (تحديث الرمز بالوسائط الثلاث،
snprintf، الرسالتان الجديدتان، التنظيف الكامل بدون
تسريبات ASan).

## حالة 2026-10-29 — الأساس جاهز
- **الهيدر مكتوب:** `modules/syndicate/src/SyndicateSignUpPlunderWar.h`
  (اسم الملف على نمط بقية وحدات `modules/syndicate/src/Syndicate*.h`).
  فيه توقيع الخام المؤكد، وبوابات **المرحلة 1 مؤكدة سطر بسطر**، وتفصيل
  المرحلة 2 (بما في ذلك أن `CONCAT44` معناها إن النص الأعلى من مؤشر الـproxy
  بيتحفظ والـid = `14174e3f0() * 1000000 + target`)، وجدول الـseams كامل.
- **الباقي للنقل:** قراءة الأسطر 120-591 من الخام ثم كتابة
  `SyndicateSignUpPlunderWar.cpp` بالمراحل 3-7 والتنظيف الموحّد، مع اختبار
  ~32 تأكيدًا كما في الخطة.

## 2026-10-29 (تكملة) — المرحلتان 2 و5 منقولتان
`modules/syndicate/src/SyndicateSignUpPlunderWar.cpp`:
- **`ComposeTargetId`** (المرحلة 2 كاملة): صفر → لا إدراج؛ الهدف ==
  `vt+0x3f0` → `14174e3f0`، ولو صفر أو == عصبة المستخدم → لا إدراج، وإلا
  `myLeague*1000000 + own`؛ غير كده `141766950(mgr,target)`؛ ثم رفض
  الصفر ورفض المساواة بمفتاح العضو.
- **`SendRobOptPages`** (المرحلة 5): `freePages < 1` فشل؛
  `pages = (int)(long long)ceil((cap-current)/freePages)`؛ ctor
  `1417d8390`؛ create `1417d84d0(msg,1,pages)`؛ حلقة الإلحاق
  `1417d8810(msg, id/1000000)` — **قسمة على مليون لاستخراج العصبة**؛ فشل
  الإلحاق → لوج `"... msg over size"` و**break مع الاستمرار للإرسال**؛
  `1417d8700` (short) != 0 → `1417d8570` ثم الإرسال عبر `vt+0x8`؛
  ثم `1417d83e0`؛ والنتيجة 1.

**اختبار:** `syn_d78_test` **28 تأكيدًا** ×6 (فيهم ceil لصفحة/صفحتين،
over-size عند أول إلحاق وأثناءه) — **109/109 ×6**.

**باقي D78:** الرمز (14174bac0/14174bbe0/1417d4ed0/141764870 + لوج
`cq_token_type`)، نص التسجيل `1417b2570`، `param_6`/`vt+0x238`،
وذيل الرسالتين الجديدتين، والتنظيف الموحّد.
