# D74 — CLeagueMgr::AddTodayPlunderWarInfo (FUN_1417715f0)
> مصدر واحد: المفكك v6159 (Syndicate.dll @1417715f0). لا تخمين.

## التوقيع والغرض
`AddTodayPlunderWarInfo(mgr, uIdPlunder, nCount, aTargets[])`
تُسجّل عصبة النهب اليومي: تدخل uIdPlunder في mgr+0x370 (خريطة PLUNDERING
بقيمة خريطة أعضاء)، ولكل هدف (حتى 10) تدخل الهدف في mgr+0x3b0
(خريطة PLUNDERED بقيمة خريطة uIdPlunder)، وترسل LeagueOpt (type 4)
لكل هدف على نفس سيرفر عصبتنا (id/1e6 == myLeague).

## البنية RAW بالتفصيل
1. `uIdPlunder == 0 || nCount <= 0` → رجوع.
2. lower_bound(mgr+0x370, uIdPlunder) + فحوص الـ iterator
   (proxy فارغ/مغيّر → invalid). **إن وُجد → لوج "CLeagueMgr::
   AddTodayPlunderWarInfo data repeat idPlunder[lu%]" ثم يتابع** (لا يعود!).
3. إنشاء الخريطة الخارجية الجديدة (قيمة إدخال mgr+0x370):
   - wrapper = operator_new(8); *wrapper = &container; container[0] = wrapper
     (هذا هو الـ proxy بالضبط: *proxy → container، مطابق لـ kit D70).
   - treehead = FUN_141726c30() (isnil@+0x1d=1، ثلاث روابط ذاتية) → seam
     جاهز: g_fnLbrHeadAlloc.
   - الحجم (local_660) يبدأ صفرًا — يزيد داخليًا عند الإدخال.
4. حلقة الأهداف (i من 0 إلى nCount-1، **كسر صريح عند i > 9** — سقف 10):
   - uT = aTargets[i]؛ مفتاح الإدخال الخارجي = {lo:uT, hi:وحدات RAW
     مجاورة} (المفتاح الفعلي u32 واحد — موثق).
   - إن uT == 0 → تخطّي.
   - بحث في mgr+0x3b0 (نفس تخطيط الـ kit: key@+0x18، isnil@+0x61) عن uT.
   - **غير موجود** (node==head أو uT < node.key):
     - خريطة داخلية جديدة {wrapper8، container، treehead=141726c30، size=0}.
     - FUN_14172ae00(الـ proxycell الجديد, iter, uIdPlunder) — find-or-insert
       (seam جديد: g_fnLbrMapFindOrAdd).
     - قالب الزوج: FUN_1417695b0 (نسخ container 8 بايت) + FUN_14176f690
       (بناء زوج {u32 first, u64 second}) (seam جديد: g_fnLbrPairMakeId)
       ثم FUN_141770ea0(mgr+0x3b0, out, pair) = الإدخال (g_fnLbrMapInsertKey
       موجود) — الخريطة الجديدة تنتقل بالملكية إلى mgr+0x3b0.
     - تفكيك المؤقتات: FUN_14172c560 ×2 + operator_delete ×2 (seam جديد:
       g_fnLbrPairClear) ثم dtor الخريطة (14172a410 → g_fnLbrMapTreeDtor
       موجود؟ تحقق: الاسم في kit هو g_fnLbrMapTreeDtor/g_fnLbrMapEraseRange)
       + operator_delete للـ wrapper (نمط الحركة move).
   - **موجود**: فحوص proxy/deref ثم FUN_14172ae00(node+0x20, iter,
     uIdPlunder) — find-or-insert داخل خريطة القيمة الموجودة.
   - بعد كلا الفرعين: FUN_14172ae00(الخريطة الخارجية الجديدة, iter, uT)
     — إدخال الهدف في خريطة الأعضاء.
   - uMy = vt+0x3f0 (myLeague — g_fnLbrGetMyLeague).
   - إن (uT/1e6 == uMy): **إرسال LeagueOpt للاهداف**:
     - FUN_1417d8390(msg) ctor (g_fnPwsCtorCMsgLeagueOpt موجود من D72)
     - إن فشل FUN_1417d84d0(msg, 4, 0) → dtor + تفكيك الخارجية + رجوع
       (seam جديد: g_fnPwsCreateLeagueOpt4 + g_fnPwsFlushLeagueOpt=1417d8570)
     - FUN_1417d8570(msg) ثم **vt+0xb8(logic, uT%1e6, msg, 0, 1)** — إرسال
       نصي (seam جديد: g_fnAtpSendOptText) ثم dtor (1417d83e0).
5. بعد الحلقة: إن ظل حجم الخريطة الخارجية صفرًا → تفكيكها فقط
   (14172a410 dtor + delete الـ treehead + delete الـ wrapper).
6. وإلا: بناء زوج {uIdPlunder, container} بنفس القالب (1417695b0 +
   14176f690) + FUN_141770ea0(mgr+0x370, out, pair) + تفكيك المؤقتات.
   ثم إن (uIdPlunder/1e6 == uMy): نفس كتلة إرسال LeagueOpt (بعلم 0 بدل 1
   في وسيط vt+0xb8 الرابع).
7. التفكيك الختامي للخريطة الخارجية دائمًا (dtor + delete ×2).

## الـ seams الجديدة المطلوبة
- g_fnLbrMapFindOrAdd ← FUN_14172ae00 (proxycell, iter[2], key*)
- g_fnLbrPairMakeId ← FUN_14176f690 (out, u32, src*)
- g_fnLbrPairClear ← FUN_14172c560 (pair*)
- تأكيد مطابقة: g_fnLbrHeadAlloc == FUN_141726c30، g_fnLbrPairMake ==
  FUN_1417695b0، g_fnLbrMapInsertKey == FUN_141770ea0، dtor الخريطة ==
  FUN_14172a410 (موجودة كـ g_fnLbrMapTreeDtor/g_fnLbrMapEraseRange)
- g_fnPwsCreateLeagueOpt4 ← FUN_1417d84d0، g_fnPwsFlushLeagueOpt ←
  FUN_1417d8570، g_fnAtpSendOptText ← vt+0xb8، dtor ← FUN_1417d83e0

## خطة الاختبار (نقاط التأكيد المتوقعة ~30)
1. البوابات (id=0، count<=0) بلا أي أثر.
2. التكرار: إدخال مرتين → اللوج + يتابع ويدخل قيمة ثانية.
3. سقف العشرة أهداف (كسر الحلقة).
4. تخطي uT == 0.
5. مسار "غير موجود" في mgr+0x3b0: إدخال uT + خريطة داخلية جديدة
   (يعمل مرتين على نفس uT → المسار الثاني "موجود").
6. الإرسال: فقط للأهداف التي uT/1e6 == myLeague، بوسائط (uT%1e6, msg, 0, 1).
7. الحجم صفر (كل الأهداف صفرية) → لا إدخال خارجي ولا إرسال نهائي.
8. الإدخال الخارجي النهائي + إرسال الختام بعلم 0.
9. فشل Create → تفكيك فوري ورجوع.
10. ASan/UBSan نظيف (حركة الخرائط بالملكية بدقة — أخطر نقطة في الوحدة).
