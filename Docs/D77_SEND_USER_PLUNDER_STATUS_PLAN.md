# D77 — CLeagueMgr::SendUserPlunderWarStatus (FUN_14176ca70)
> مصدر واحد: المفكك v6159 (Syndicate.dll @14176ca70، 812
> سطر). الاسم موثق من اللوجات
> "CLeagueMgr::SendUserPlunderWarStatus cannot find the
> plundered league[%lu]" و"...support idServerTarget[%lu]".
> كانت seam فقط (g_fn14176ca70 في SyndicateInviteNotify، D73).
> الحالة: محللة بالكامل، البورت خطوة "كمل" القادمة.

## التوقيع
SendUserPlunderWarStatus(mgr, uKey, uParam3, uParam4)
— إرسال حالة حرب النهب لمستخدم (uKey = مفتاح العضو).
uParam3/uParam4: وجهتا الإرسال (vt+8 بـ uParam3 أو vt+0x38
بـ uParam4).

## البنية RAW (خمس مراحل)
0. **البوابات**: uKey != 0؛ (uParam3==0 && uParam4==0) →
   خروج. ثم lower_bound على mgr+0x370 بـ uKey: موجود →
   أكمل؛ غائب → lower_bound على mgr+0x3b0: غائب أيضًا →
   قفزة لمرحلة الحرب (LAB_14176cbb9).
1. **رسالة الحضور** (عائلة D71 RobOpt): ctor 1417d8390 +
   create(4, 0)؛ فشل → dtor + return. ثم Serialize 1417d8570
   + إرسال: uParam3==0 → **vt+0x38**(logic, uParam4, msg)
   وإلا **vt+8**(logic, uParam3, msg) + dtor.
2. **بوابة الحرب**: mgr+0x35c != 2 → return.
3. **أربع مراحل منسوخة RAW** بنفس القالب (كلها على
   رسالة العائلة الجديدة):
   - mgr+0x370 (PLUNDERING): create(1, id/1e6, 0x358, name)
   - mgr+0x3b0 (PLUNDERED): create(0, ...)
   - mgr+0x430 (SUPPORT): create(2, ...)
   - mgr+0x470 (الجرد الختامي): create(4, 0, 0x358, "")
   القالب: lower_bound بـ uKey → غائب تخطَّ؛ size@+0x58 !=
   0 → leftmost → id@+0x18 → جلب الاسم (مرحلة 370/430:
   141766170 ثم مسار -2 الاحتياطي لـ 141766250؛ مراحل
   3b0/470: 141766250 مباشرة) — فشل الجلب → لوج + return
   الكامل. حلقة المشي الترتيبي (isnil@+0x1d) مع نمط
   الدفعات: فشل الإلحاق 1417d5820 → Flush 1417d55e0 +
   إرسال (vt+0x38/uParam4 أو vt+8/uParam3) + Clear
   1417d55a0 + **إعادة إنشاء 1417d54f0 بنفس الوسائط** +
   إعادة الإلحاق مرة. الختام: العدد 1417d5770 != 0 →
   Flush + إرسال، ثم dtor 1417d54b0 دائمًا.

## عائلة الرسالة الجديدة (7 seams)
- g_fnSusMsgCtor **1417d5460**
- g_fnSusMsgCreate **1417d54f0**(msg, type, id, warFlag, name)
- g_fnSusMsgAppend **1417d5820**(msg, id)
- g_fnSusMsgFlush **1417d55e0**
- g_fnSusMsgClear **1417d55a0**
- g_fnSusMsgCount **1417d5770**
- g_fnSusMsgDtor **1417d54b0**
+ الإرسال الجديد **vt+0x38**: g_fnSusSendAlt(logic, id, msg)

## خطة الاختبار (~30 تأكيدًا)
البوابات الثلاثة؛ مسار الحضور (create(4,0)+serialize+
الوجهتين)؛ بوابة 0x35c؛ المراحل الأربع (نوع create،
مسار الاسم حسب المرحلة، اللوج عند فشل الجلب + return)؛
نمط الدفعات (flush+إرسال+clear+إعادة الإنشاء بنفس
الوسائط+إعادة)؛ الختام (العدد صفر → لا إرسال)؛ المفاتيح
الغائبة تتخطى؛ ASan نظيف بعقد fixture مطابقة لـ D76.

## ملاحظة تنفيذية
القالب المنسوخ ×4 يجعل البورت طويلًا لكن ميكانيكيًا —
يُنقل حرفيًا كأربع نسخ (كما في D72/D76، لا دمج — الـ
RAW لا يدمج).
