# HANDOFF — نقطة الاستكمال (TQServer / Syndicate.dll)

> **هذا الملف يتحدث بعد كل إغلاق وحدة.** أي Agent جديد يبدأ من هنا.
> السجل التاريخي التفصيلي: PORTING_LOG.md.

## آخر حالة (2026-10-26 — بعد D55b)

- آخر commit: **D55b مقفولة** (هذا الـ commit) — تدفق توزيع جوائز العصبة كاملاً (SyndicateMeedDistribute: 141784cd0 التدفق + 49f0/46e0/2d0 الموزعون الثلاثة + 0b0/1b10/9b60/f0d0/21d0/1860/f250/fa90/fa10/fa60/ae630 = 15 دالة verbatim). إصلاحان أثناء النقل: قراءة end (+0x20) لا cap (+0x28) في زوج فرز 46e0؛ fa60 رُقّي ليرجع قيمة النقطة (مثل fa10)
- قبلها: **D55a** (1ae8280): عائلة متجه مدخلات الـ 5-int + الانترسورت الكامل (SyndicateMeedEntry: 22 دالة). مقارن LAB_141780100 = seam `g_fnMeedEntryCmp` — عائلة متجه مدخلات الـ 5-int + الانترسورت الكامل (SyndicateMeedEntry: 141780750/2020e0/2c20/2480/2550/2060/1ca0/3b70/4100/48f0/3ad0 + عائلة الفرز 1eb0/2640/7c0/1f30/2740/2810/2990/33d0/2ca0/3f50/4260). مقارن LAB_141780100 = seam `g_fnMeedEntryCmp` (thunk غير مفكك)
- قبلها: **D54** (73feb4d) ProcessEndMeed — تدفق ProcessEndMeed 141783470 (1229B) + باني قائمة المعرفات 14177d7a0 + المسح المتعدد 14177d180 (DeleteSynMeed: المسح + compaction + زوج التحرير vt+0x40/vt+0 + إعادة المسح)
- ملحق الجولة: **إصلاح d50 test** (commit 9a8c6b5) — الاختبار القديم لم يكن يتوافق مع parameterization عائلة الترتيب في D52؛ **D53 مقفولة** (deb058f): SetArenicMeed 141780cb0 (2058B) + عائلة Apply كاملة (SetSynMeed/Insert/AddMore/cb90/caa0/ff70/fbc0/fad0/da0d0/141732200)
- الرجريشن الكامل: **58/58 PASS × 6** (syndicate d26-d55a: 33/33 + peerage/analyst 25) بالعلم **O0** (المعيار المعتمد، ممنوع الحكم بـ O1 — d28 SIGSEGV عند O1 قديم ومستقل)
- TBD موثق في SyndicateMeedApply/End: الـ varargs المُسقطة في _snprintf/MyLogSave (لا يوجد Syndicate.dll binary في مساحة العمل هذه لتمريرة objdump — سياسات الـ seam موثقة)
- كل الكود مرفوع على GitHub. **NO BUILD** (لا zig/binaries) حتى اكتمال السورس كله.

## الخطوة التالية بالضبط: D56 — تدفق منح الميد 1417814c0

0. **D55a/D55b جاهزتان أسفلهما بالكامل** — التوزيع مقفول
   (الفرز+الجمع+الحصص+المنح+السجلات+الإعلان) والمقارن =
   seam `g_fnMeedEntryCmp`.
1. بورت 1417814c0 (تدفق منح الميد) — تحقق أولاً من معالجه في
   الديكومبايل (نفس أسلوب 4cd0: نظافة/جمع/منح/سجل).
2. ثم بقية واجهة المدير وهاندلرز الوحدة/طبقة CMsg الباقية
   (~89 دالة متبقية في نطاق كود اللعبة) + فحص تغطية الـ 199
   دالة المورتة مقابل الديكومبايل.

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
