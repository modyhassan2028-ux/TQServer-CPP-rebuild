# HANDOFF — نقطة الاستكمال (TQServer / Syndicate.dll)

> **هذا الملف يتحدث بعد كل إغلاق وحدة.** أي Agent جديد يبدأ من هنا.
> السجل التاريخي التفصيلي: PORTING_LOG.md.

## آخر حالة (2026-10-26)

- آخر commit: **D41b/T16 مقفول** (هذا الـ commit) — الـ erase-ones التسعة + الـ 27 ورقة حقيقية (SyndicateLeagueMgrErOne)
- الرجريشن الكامل: **29/29 PASS** (syndicate d26-d40: 18/18 + peerage/analyst: 11/11) بالعلم **O0** (المعيار المعتمد، ممنوع الحكم بـ O1 — d28 SIGSEGV عند O1 قديم ومستقل)
- كل الكود مرفوع على GitHub. **NO BUILD** (لا zig/binaries) حتى اكتمال السورس كله.

## الخطوة التالية بالضبط: D41c — العائلتان المتداخلتان

الـ sub-seams في `SyndicateLeagueMgrErase.{h,cpp}` (تُقاس على خريطة معمولة بِإدخالات حقيقية — محتاجة دوال insert العائلية أو بناء عقد يدوي):

| الـ sub-seam | الدالة الأصلية | الملاحظات |
|---|---|---|
| g_fnNestedErA | 14172a410 | range متداخل (~77): clear=141727640 (25) → subtree 141726210؛ erase-one=141728290 (198) بأوراقه 141724c50/cb0/ed0 |
| g_fnNestedErB | 141762db0 | range متداخل (~77): clear=1417567f0 (25) → subtree 1417540c0؛ erase-one=1417614e0 (198) بأوراقه 14174fe10/141750760/141752ac0 |

(الـ erase-ones التسعة للمدير اتقفلت في D41b — وحدة SyndicateLeagueMgrErOne + 27 ورقة، اختبار d42 7/7 بفاحص RB كامل. **قاعدة الألوان في الكود: 1=أسود و0=أحمر. غلطة rotA القديمة اتصلحت (الذيل y->left). رأس الـ nil لازم يتفضل أسود في أي fixture يدوي.**)

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
