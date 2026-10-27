# سجل الإنجاز والمتبقي — محدث حتى D80 (27 أكتوبر)
> الرجريشن الأخضر: 84/84 ×6 — ASan/UBSan نظيف.

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
