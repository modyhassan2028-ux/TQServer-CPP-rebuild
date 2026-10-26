# HANDOFF — نقطة الاستكمال (TQServer / Syndicate.dll)

> **هذا الملف يتحدث بعد كل إغلاق وحدة.** أي Agent جديد يبدأ من هنا.
> السجل التاريخي التفصيلي: PORTING_LOG.md.

## آخر حالة (2026-10-26 — بعد D57)

- آخر commit: **D57 مقفولة** (هذا الـ commit) — الأجسام الحقيقية لمُشيّدات CMsg السبعة عشر (14177ead0 family) + مُشيّدا الحقلين protobuf (1417f1600/1417f05f0). ثلاثة أنماط حرفية: بسيط (12) / packer (3: +0x20/0x3e5, +0x128/0x2d9, +0x1a/0x3ee) / PB (2). RobOptPB لا يستدعي ثنك 1417e8050 خلافاً لـ TokenPB. g_aMsgCtor تربط بالأجسام الحقيقية
- قبلها: **D56** (c2b2b3d): جسم منح الميد الأونلاين 1417814c0 — جسم منح الميد الأونلاين 1417814c0 (المسار الحقيقي لـ seam ‏g_fnMeedAwardOnline في توجيه 21d0): قص الموني (vt+0x3e0−0x230) والإيموني (سقف DAT_141886d68 = INT_MAX، المُهيئ 141821a10)، منح vt+0x138/vt+0x148، ملاحظات syndenote (بوابة 9999 للموني)، prompt+إرسال 2000، gmlogs النوعين 2/3. إصلاح نقل: إعادة حساب القص داخل الشرط
- قبلها: **D55b** (90c6f4a): تدفق توزيع جوائز العصبة كاملاً (15 دالة) — تدفق توزيع جوائز العصبة كاملاً (SyndicateMeedDistribute: 141784cd0 التدفق + 49f0/46e0/2d0 الموزعون الثلاثة + 0b0/1b10/9b60/f0d0/21d0/1860/f250/fa90/fa10/fa60/ae630 = 15 دالة verbatim). إصلاحان أثناء النقل: قراءة end (+0x20) لا cap (+0x28) في زوج فرز 46e0؛ fa60 رُقّي ليرجع قيمة النقطة (مثل fa10)
- قبلها: **D55a** (1ae8280): عائلة متجه مدخلات الـ 5-int + الانترسورت الكامل (SyndicateMeedEntry: 22 دالة). مقارن LAB_141780100 = seam `g_fnMeedEntryCmp` — عائلة متجه مدخلات الـ 5-int + الانترسورت الكامل (SyndicateMeedEntry: 141780750/2020e0/2c20/2480/2550/2060/1ca0/3b70/4100/48f0/3ad0 + عائلة الفرز 1eb0/2640/7c0/1f30/2740/2810/2990/33d0/2ca0/3f50/4260). مقارن LAB_141780100 = seam `g_fnMeedEntryCmp` (thunk غير مفكك)
- قبلها: **D54** (73feb4d) ProcessEndMeed — تدفق ProcessEndMeed 141783470 (1229B) + باني قائمة المعرفات 14177d7a0 + المسح المتعدد 14177d180 (DeleteSynMeed: المسح + compaction + زوج التحرير vt+0x40/vt+0 + إعادة المسح)
- ملحق الجولة: **إصلاح d50 test** (commit 9a8c6b5) — الاختبار القديم لم يكن يتوافق مع parameterization عائلة الترتيب في D52؛ **D53 مقفولة** (deb058f): SetArenicMeed 141780cb0 (2058B) + عائلة Apply كاملة (SetSynMeed/Insert/AddMore/cb90/caa0/ff70/fbc0/fad0/da0d0/141732200)
- الرجريشن الكامل: **58/58 PASS × 6** (syndicate d26-d55a: 33/33 + peerage/analyst 25) بالعلم **O0** (المعيار المعتمد، ممنوع الحكم بـ O1 — d28 SIGSEGV عند O1 قديم ومستقل)
- TBD موثق في SyndicateMeedApply/End: الـ varargs المُسقطة في _snprintf/MyLogSave (لا يوجد Syndicate.dll binary في مساحة العمل هذه لتمريرة objdump — سياسات الـ seam موثقة)
- كل الكود مرفوع على GitHub. **NO BUILD** (لا zig/binaries) حتى اكتمال السورس كله.

## الخطوة التالية بالضبط: D58

0. **طبقة الوحدة كاملة الآن** — المُشيّد + بوابة التسجيل +
   ModuleCreate (وحدة Module سابقة) والمُشيّدات السبعة عشر (D57).
1. المتبقي في طبقة CMsg: **هاندلرز الرسائل** (أجسام Process
   خلف vtables الفئات السبع عشرة) + مفاتكياتها
   (1417e3b0/1417e430 الـ dtors منقولة، 1417e8050 عميق الـ PB)
   + بقية واجهة المدير (~70 دالة متبقية في نطاق كود اللعبة).
2. ابدأ بفحص فهرس الديكومبايل لأجسام Process للفئات الصغيرة
   (CMsgLog أولاً) ثم اقفلها وحدة وحدة.
3. فحص تغطية الـ 199 دالة المورتة مقابل الديكومبايل.

## قواعد العمل الثابتة (لا تتجاوزها)

1. **Verbatim من الديكومبايل** — المرجع: `conquer-online-v6159-decompiled/Native-Decompiled/Syndicate.dll.decompiled.c` (repo التحليل الثاني).
2. المُشيّدات/المدمرات تُختبر بـ counting registry (malloc tab + operator new/delete override) — القالب جاهز في `tests/syndicate_d40_test.cpp`.
3. الوحدات في `Exe/Dll/Syndicate/Port/`، الاختبارات `tests/syndicate_dXX_test.cpp`.
4. بعد كل وحدة: رجريشن كامل (كل ملفات tests على O0) ثم PORTING_LOG.md + HANDOFF.md + commit + push.
5. مسارات العمل داخل `/app/conversations/6ada078e9883f31f19597098/work/TQServer-CPP-rebuild`.

## بعد D41 (الترتيب)

1. **طبقة الوحدة**: المُشيّد 14177ead0 + بوابة التسجيل 14177e890 + الـ 18 handler CMsg (الـ export الوحيد ModuleCreate @ 14177ec90، ImageBase 0x141720000، كائن 0x4608).
2. واجهة المدير (~65 دالة): بقية accessors/operators (17 منهم مقفولين في D37).
3. فحص تغطية الـ 199 دالة المورتة مقابل الديكومبايل.
4. ثم بقية أنواع cq_action العليا + CQCrossServer الأعمق (حصر 23 أكتوبر: 172 نوع متبقي في 6 عائلات + أنظمة أوسع).

## الأخطاء المكتشفة (تجنب تكرارها)

- بوابة CRT: قارن بـ `*param_1` (proxy) مش `param_1`.
- أحجام الكائنات: آخر خريطة ممتدة 0x40 (proxy/head/size) — المدير **0x580** مش 0x540، الكيان 0x118، الوحدة 0x4608.
- التقدم للمخلف في المسح: prelude بأسلوب do (ابن اليمين أولاً) وإلا تتكسر حالة "ابن يسار ابن اليمين نيل".
- تحرير التوكن: args `(sub, 1, p3, p4, -2)` ثم deleting dtor ذاتي، والقيمة تصفر مرتين (حرفي).

---

## تحديث D58+D58b (2026-10-26)

### أصول جديدة مهمة جداً
1. **Syndicate.dll الأصلي مسترجع**: `co_decomp/orig_binaries/Source/Syndicate.dll` (1.59MB، ImageBase 0x141720000 مطابق 100% للفهرس) — من أرشيف `Conquer_Online_Source_v6159.7z` (829MB، فيه كل مصادر اللعبة: MsgServer/NpcServer/DLLs الأصلية). أي دالة يفشل فيها الـ decompiler يمكن فكّها يدوياً الآن بـ capstone (القالب موجود في سجل هذه الوحدة).
2. **جرد vtables كامل**: `tools/syndicate_vtables.json` — 66 جدول مسمّى عبر RTTI، أهمها:
   - نمط جدول CMsg (5 فتحات): `[dtor, deleting, Init(base 0x14177e2f0), Process, tail(0x14177e2d0)]` — **Process لكل فئة الآن معلوم العنوان** (CMsgLog=0x1417d97c0, ChgDomName=0x1417daee0, LeagueOpt=0x1417d68d0, LeagueRobOpt=0x1417d8920 ...).
   - جدول CModule (9 فتحات) مؤكد: Startup=+0x10 (0x14177e620), SvcPassThrough=+0x18 (0x14177eaa0), ProcessMsg=+0x20 (0x14177ec30).
   - جدول CSyndicateLogic = **232 فتحة** وIProvider = 224 — خريطة المنافذ الكاملة لوحدات المنطق القادمة.
   - ملحوظة thunk غريبة: بعض خانات deleting-dtor تشير لعنوان فردي 0x1417e7fda (thunk بيتوسط تعليمة) — عالجه كأنه entry+N سابق عند الفك.

### حالة D58
- مكتمل ومقفول: ذيل الوحدة (20 دالة) + **SendLeaveAward (14177eda0) مفكوك يدوياً ومنقول حرفياً** في `SyndicateLeaveAward.{h,cpp}` — كان الـ TBD الوحيد.
- الاختبار: 9 أقسام (D58-9 يربط Flow بالجسم الحقيقي E2E)، رجريجن 62/62 × 6، ASan نظيف.
- فتحات mgr الموثقة لـ SendLeaveAward: +0x138/+0x148/+0x1d8/+0x1f8/+0x230/+0x238/+0x3e0 (انظر PORTING_LOG للتفاصيل والسلاسل الحرفية).

### التالي (بالأولوية)
1. **D59: أجسام Process لفئات CMsg** — العناوين الآن كلها معلومة من الجرد؛ ابدأ بـ CMsgLog::Process (0x1417d97c0) ثم ChgDomName (0x1417daee0) — كلاهما في نطاق كود اللعبة.
2. بقية الفئات الـ 37 (كل Process فريد في الجرد).
3. الفشلان المتبقيان في الفهرس (1417ab8c0 502 بايت، 1417ac2d0 346 بايت — كلاهما داخل جدول CSyndicateLogic) — فكّ يدوي بنفس أسلوب SendLeaveAward.
4. واجهة المدير المتبقية + إغلاق ModuleCreate (14177ec90).
