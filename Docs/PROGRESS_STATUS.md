# سجل الإنجاز والمتبقي — محدث حتى D76 (27 أكتوبر)
> الرجريشن الأخضر: 80/80 ×6 — ASan/UBSan نظيف.

## المنجز (كل شيء أدناه مرفوع على GitHub، آخر commit: a2fb5d5)
- **D26→D73**: نواة النقابة + عائلات BeRob/RobOpt/LeagueOpt/Token
  + PlunderWarStart (بمراحله الخمس + البث الختامي 0x45) +
  UserAcceptPlunderWarInvite (الشقان) — كل وحدة بورت + اختبارات
  + ASan + دمج رجريشن + push.
- **D74**: AddTodayPlunderWarInfo كاملة — 34 تأكيدًا (78/78).
- **D75**: SendPlunderWarListToClient (FUN_141766500) كاملة —
  بورت + 26 تأكيدًا + ASan نظيف (79/79).
- **D76 (اليوم)**: ClientQueryPlunderWarInfo (FUN_141766e90)
  كاملة — أول Pagination في المشروع، بورت + 35 تأكيدًا +
  ASan صفر تسريبات، 80/80 ×6 (commit f12c8b9).
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
1. **D77+**: بقية دوال جبهة العميل/حالة الحرب غير
   المُحوَّلة في نطاق 14176xxxx (جرد دقيق عند البدء).
2. ثم استكمال ~52 كلاس متبقٍ حسب الجرد الكلاسي أعلاه.
