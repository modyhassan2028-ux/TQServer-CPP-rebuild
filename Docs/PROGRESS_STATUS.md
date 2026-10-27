# سجل الإنجاز والمتبقي — محدث حتى D84 (27 أكتوبر)
> الرجريشن الأخضر: 88/88 ×6 — ASan/UBSan نظيف.

## المنجز (كل شيء أدناه مرفوع على GitHub، آخر commit: a2fb5d5)
- **D26→D73**: نواة النقابة + عائلات BeRob/RobOpt/LeagueOpt/Token
  + PlunderWarStart (بمراحله الخمس + البث الختامي 0x45) +
  UserAcceptPlunderWarInvite (الشقان) — كل وحدة بورت + اختبارات
  + ASan + دمج رجريشن + push.
- **D74**: AddTodayPlunderWarInfo كاملة — 34 تأكيدًا (78/78).
- **D75**: SendPlunderWarListToClient (FUN_141766500) كاملة —
  بورت + 26 تأكيدًا + ASan نظيف (79/79).
- **D76**: ClientQueryPlunderWarInfo (FUN_141766e90)
  كاملة — أول Pagination في المشروع، 35 تأكيدًا (80/80).
- **D77 (اليوم)**: SendUserPlunderWarStatus (FUN_14176ca70،
  812 سطر) كاملة — كانت seam فقط من D73؛ خمس مراحل:
  حضور RobOpt بتوجيه مزدوج + بوابة الحرب + أربع مراحل
  منسوخة (0x370/0x3b0/0x430/0x470) بعائلة رسالة جديدة
  7-seams ونمط الدفعات مع إعادة الإنشاء بنفس الوسائط.
  بورت + 33 تأكيدًا + ASan صفر تسريبات، 81/81 ×6.
- **D78**: SignUpPlunderWarFromClient كاملة — أول std::vector
  حقيقي في المشروع + منطق cq_token_type.
- **D79**: PlunderWarClose كاملة — إغلاق دورة حرب النهب
  (الحالة 3 + التنظيف + البث 0x46).
- **D80 (اليوم)**: PublishSupportTokenFromClient
  (FUN_1417c3230) كاملة — التوكن 0x6a، النوع 6، تحقق
  141768ec0 الجديد لكل هدف، غياب msg1، بوابات الدعم
  الأربع (param6/nMax2/ppl/charge) مع محادثات
  SUPPORT_TOKEN_USE_FAIL وEMONEY_NOT_ENOUGH، MyLogSave
  350/4323، إشعار الدعم، وvt+0x560 الختامي. بورت +
  42 تأكيدًا + ASan صفر — الحاوية المحلية وسّعت إلى
  8 كلمات لأن فيك الإدراج يحدّث الحاوية عند +0x20.
- **D84 (اليوم)**: تعيين منصب 0x3de
  (FUN_1417acda0، ~142 سطرًا) — معالج رتبة
  0x3de من مفتاح 0x1c في D83: كامل الحوارس
  (لوج CHECKF بالمسار الحرفي، تعيين ذاتي، نقابة
  مغايرة، غير متصل، HasFlag، رتبة ≥0x3de)،
  كتلة التعيين (مسح المنصب الفرعي، SetMemberRank،
  vt+0x328، RecordUpdate، كلام
  STR_APPOINT_SUCCESS ببث vt+0x88، رسالة
  0x27/0x3de بvt+8)، وتتالي الشاغل السابق
  (setmisc 200 → رتبة 0x26c)، ووضع الامتلاء
  (STR_POSITION_FULL). 32 تأكيدًا من أول تشغيل،
  ASan صفر. ملاحظة: FUN_141798010 غير موجودة
  في المفكك (كانت تقديرية)؛ قائمة المتبقي
  الفعلية: 177 دالة > 120 سطرًا، أكبرها
  FUN_141736d40 (CCountry::OnLeagueOnStage،
  ~646).
- **D83 (اليوم)**: CMsgSyndicate::Process
  (FUN_1417db7b0، ~430 سطرًا) — مُوزّع رسائل
  النقابة الكامل: مفاتيح 1..0x32 (~30 حالة)
  بمساراتها الأصلية: حارس idActor بلوج CHECK
  بالمسار الحرفي `f:\version\...\msgsyndicate.cpp`،
  بوابات الحرب (ac6f0/ac710/ac700/ac720/ac730)،
  كلام STR_DIE/STR_INVALID_CHARACTER/
  STR_DENY_APPOINTMENT/
  STR_SYNDICATE_BACKLIST_ADD/REMOVE_SUCCESS،
  توزيع رتب 0x1c و0x1d بنطاقاتها الدقيقة
  (القانوني: 0x1fe/0x1ff/0x25a/0x262/0x263)،
  وبناء ردّ الصلاحيات 0x25 (رسالة 0x453
  بالتسلسل السباعي 1000 ثم 0x3de,0x3d4,0x370,
  0x348,0x2a8,0x25a حرفيًا). 60 seam. 64 تأكيدًا،
  ASan صفر.
- **D82 (اليوم)**: AwardPrizeVlmOrCross
  (FUN_1417c3ed0، ~325 سطرًا) — توزيع جوائز
  الدوري VLM/CROSS على 8 مراتب: حارس
  vecSynID.size()==bitset.size، مكرر bitset
  بأسلوب MSVC (141741730/141741c50 =
  التقدّم/السِّيك RAW)، فحص البتة للتخطي في
  bCross، جداول الجوائز مستخرجة حرفيًا من
  .rdata الأصلية (normal: 12000→2000 مال
  ×10000 و3000→200 emoney؛ cross:
  100000→10000 و10000→1000)، إضافة المال
  14179bf80 + MyLogSave بملفي
  gmlog/synvlmaward/syncrossvlmaward، حد
  الإيموني 1e9 مع رزيمة 0x2b بالقيمة القديمة
  (vt+0x350 + 14178f270)، وكلام
  STR_VLM_AWARD/STR_CROSS_VLM_AWARD
  ببث vt+0x40. 26 تأكيدًا، ASan صفر.
- **D81 (اليوم)**: PublishSupportTokenFromMap
  (FUN_1417c1a90، ~410 أسطر) كاملة — الشقيق جهة
  الخريطة لـ D80: الدفع بمال النقابة (خصم
  141744130)، بوابات vt+0x278/0x280/0x4c8 الثلاث
  مع فرع المسجّل (vt+0x450)، الرسائل الثلاث
  (توكن الحالة + msgLeagueInfo بثنائي
  الناهب/المنهوب + نداء LEAGUE_TOKEN_CALLUP)،
  مصفوفة الاستدعاء 1417be5f0 مع بوابات العضو
  vt+0x268/0x4d8/0x280/0x4d0 وإدراج 141732040،
  البث vt+0x40، والسجل الداخلي 141777de0.
  بورت + 33 تأكيدًا + ASan صفر (51 seam
  جديدة بترتيب extern/def موحد).
- **بكج الريلم**: فُك تشفير رابط MEGA (صيغة v2: المفتاح
  = XOR النصفين + nonce من kb[16:24]) → 495 ملفًا في
  Reference/Realm_CrossServer_Package (خريطة 3935، SQL
  كامل، Lua، خرائط، باتش كلينت) — المرجع المعتمد
  لبناء CqCrossServer.
- **Docs**: INVENTORY_REPORT، ROADMAP الرسمي (المراحل الأربع)،
  خطة D74، **خطة D75 (جديدة — التحليل الكامل لـ
  SendPlunderWarListToClient FUN_141766500 + هدف D76
  ClientQueryPlunderWarInfo FUN_141766e90)**.

## الكلاسات — الجرد الكلاسي (67 كلاس مرجعي في الـ DLL)
- **منجز ~15 كلاس**: عائلات BeRob/RobOpt/LeagueOpt/Token كاملة،
  نواة CLeagueMgr وCSyndicateLogic، Meed/Point/CrossMerit/
  ArenicMeed، والـ kit (LowerBound/InsertKey/PairMake/Head/
  Invalid/تدمير الخرائط).
- **متبقي ~52 كلاس**: ~25 عائلة رسائل PB (Concubines،
  ImperialCourtList، PalaceGuardsList، OrderStatus، RobList،
  SynList، MemberList، Proffer، Domain، Compete،
  RecruitAdvertising، OverheadLeagueInfo...) + ~10 مديري حالة/
  كيان (بقية CLeagueMgr، CLeague، CSynManager، CSyndicate،
  CSynAttrMgr، CSynRecruitAdvertisingMgr، CCountry) + بقية الـ
  kit (تُستكمل مع أول استخدام مفكك حقيقي).

## قائمة العمل التالية في سلسلة حرب النهب (جبهة العميل)
1. **D78**: CSyndicateLogic::SignUpPlunderWarFromClient
   (FUN_1417c2470، 600 سطر) — محللة بالكامل في
   Docs/D78_SIGNUP_PLUNDER_WAR_PLAN.md: أول دالة
   CSyndicateLogic في السلسلة، بناء vector حقيقي +
   جدول cq_token_type + نص sprintf + رسالتان جديدتان
   (~14 seam). جاهزة للبورت.
2. ثم بقية دوال 14176xxxx ثم الـ ~52 كلاس متبقٍ.
