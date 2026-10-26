# HANDOFF — نقطة الاستكمال (TQServer / Syndicate.dll)

> **هذا الملف يتحدث بعد كل إغلاق وحدة.** أي Agent جديد يبدأ من هنا.
> السجل التاريخي التفصيلي: PORTING_LOG.md.

## آخر حالة (2026-10-26)

- آخر commit: **32875c9** (D40a/T15 مقفول)
- الرجريشن الكامل: **29/29 PASS** (syndicate d26-d40: 18/18 + peerage/analyst: 11/11) بالعلم **O0** (المعيار المعتمد، ممنوع الحكم بـ O1 — d28 SIGSEGV عند O1 قديم ومستقل)
- كل الكود مرفوع على GitHub. **NO BUILD** (لا zig/binaries) حتى اكتمال السورس كله.

## الخطوة التالية بالضبط: D41 — عائلات الـ erase التسعة

الـ seams في `SyndicateLeagueMgrLife.{h,cpp}` بانتظار التطبيق الحقيقي:

| الـ seam | الدالة الأصلية | ملاحظات |
|---|---|---|
| g_fnMgrErase38  | 14175bda0 | عائلة +0x38، head 0x30/isnil 0x29، clear=141757580→subtree 141755490، erase-one=141758050 |
| g_fnMgrErase538 | 14175e410 | يمر بـ 141757840/14175a710 |
| g_fnMgrErase4f8 | 14175e0b0 | isnil 0x69 |
| g_fnMgrErase4b0 | 14175df00 | |
| g_fnMgrErase470 | 1417742e0 | **تُنادى 5 مرات** (خرائط 141775750 الخمسة) |
| g_fnMgrErase318 | 14175dba0 | |
| g_fnMgrErase2b0 | 141775470 | خريطة 141775ac0 (رأس 0x68/isnil 0x61) |
| g_fnMgrErase228 | 14175d9f0 | |
| g_fnMgrErase108 | 14175d690 | رأس 0x60/isnil 0x59 |

(العائلة العاشرة 0x28 مغلقة فعلاً عبر OwnEraseRange 14173cb90 — لا تلمسها.)

- كل erase-range ~77-82 سطر: بوابات CRT (`*param_3 != *param_1` — قيمة الـ proxy، **مش عنوان الخريطة**؛ اتصلح غلط قديم في D40a)، مسار الفارغ = clear العائلة، مسار النقطة = erase-one العائلي + التقدم inline.
- الـ erase-ones (141758050 وأخواتها) فيها الـ RB-rebalance — لو كبيرة اعملها seams جديدة (D41b) وأقفل الـ erase-ranges نفسها.

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
