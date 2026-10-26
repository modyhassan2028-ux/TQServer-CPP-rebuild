# HANDOFF — نقطة الاستكمال (TQServer / Syndicate.dll)

> **هذا الملف يتحدث بعد كل إغلاق وحدة.** أي Agent جديد يبدأ من هنا.
> السجل التاريخي التفصيلي: PORTING_LOG.md.

## آخر حالة (2026-10-26)

- آخر commit: **D41c/T16 مقفول** (هذا الـ commit) — طبقة محو المدير كلها حقيقية end-to-end (المتداخلتان في SyndicateLeagueMgrNested)
- الرجريشن الكامل: **29/29 PASS** (syndicate d26-d40: 18/18 + peerage/analyst: 11/11) بالعلم **O0** (المعيار المعتمد، ممنوع الحكم بـ O1 — d28 SIGSEGV عند O1 قديم ومستقل)
- كل الكود مرفوع على GitHub. **NO BUILD** (لا zig/binaries) حتى اكتمال السورس كله.

## الخطوة التالية بالضبط: طبقة الوحدة (ModuleCreate + 18 handler)
1. فك 14177ec90 (ModuleCreate، تخصيص 0x4608) و14177ead0 (مُشيّد الوحدة، يبني vtable الـ 18 handler) و14177e890 (التدمير) من الديكومبايل
2. الوحدة تستدعي طبقة المدير المكتملة (D37-D41) — الربط النهائي للأصناف
3. اختبار d44: بناء الوحدة كاملة عبر ModuleCreate + استدعاء handler من vtable + التدمير الكامل (مع خرائط عامرة للتحقق من طبقة المحو الحقيقية)
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
