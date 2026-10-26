# سجل الإنجاز والمتبقي — محدث حتى D74 (26 أكتوبر)
> الرجريشن الأخضر: 78/78 ×6 — ASan/UBSan نظيف.

## المنجز (كل شيء أدناه مرفوع على GitHub، آخر commit: a2fb5d5)
- **D26→D73**: نواة النقابة + عائلات BeRob/RobOpt/LeagueOpt/Token
  + PlunderWarStart (بمراحله الخمس + البث الختامي 0x45) +
  UserAcceptPlunderWarInvite (الشقان) — كل وحدة بورت + اختبارات
  + ASan + دمج رجريشن + push.
- **D74 (اليوم)**: CLeagueMgr::AddTodayPlunderWarInfo كاملة —
  34 تأكيدًا، ASan صفر تسريبات، 78/78 ×6.
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
1. **D75**: SendPlunderWarListToClient (FUN_141766500) — محللة،
   جاهزة للبورت.
2. **D76**: ClientQueryPlunderWarInfo (FUN_141766e90، 355 سطر).
3. ثم بقية دوال حالة الحرب غير المُحوَّلة في نطاق 14176xxxx.
