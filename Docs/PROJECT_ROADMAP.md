# TQServer-CPP-rebuild — خريطة الطريق الرسمية (v6159)
> المرجع الوحيد: conquer-online-v6159-decompiled + الـ 51 DLL الأصلية.
> القاعدة: طبق الأصل، نفس المسارات والأسماء الأصلية، صفر اختلاف، صفر تخمين.

## المرحلة 1 (جارية): إكمال Syndicate.dll بالكامل
- إجمالي دوال المفكك: **4547** (منها حصة كبيرة PB/CRT/stubs تُعالج آليًا على مستوى العائلات، وليس دالة-دالة).
- المنجز حتى D73: عائلات رسائل النقابة + النهب (D69-D73) والنواة (D26-D68: 77/77 اختبار أخضر ×6).
- المتبقي الوظيفي: بقية سلسلة PlunderWar (حالة الحرب، بوابات 0x45/0x46، عائلة FUN_1417715f0)، بقية مديري العصبة، عائلات PB المتبقية، ثم جرعة الكتلة الميكانيكية (thunks/CRT/PB) بنهاية الوحدة.

## المرحلة 2 (بعد إغلاق Syndicate): جميع الـ DLL الصغيرة أولًا — بالترتيب:
EpochHook(163), Analyst(29), Training(142), Title(144), Peerage(182), Flower(186),
RevampedHook(196), Sponsor(282), DetainEquip(285), TaskDetail(313), Wanted(321),
Booth(322), Trade(323), Common(328), Pigeon(329), Rank(383), FactionMatch(410),
Team(423), Lottery(424), Storage(431), Competion(504), CrossStatus(521),
AntiCheat(523), Guide(531), Totem(565), Relation(653), LeaveWord(655), Arenic(687),
Status(710), VexillumArenic(730), FrontierFlagWar(834), CrossFlagWar(835),
FamilyArenic(850), Family(876), ElitePKArenic(928), TeamArenic(976), CQBase(1140),
PopPKArenic(1181), ClanPKArenic(1182), DB(1377)
(الرقم = عدد دوال المفكك؛ المجلدات: Exe/Dll/<الاسم الأصلي>/Port بنفس تنظيم v6159.)

## المرحلة 3: السيرفرات المتوسطة
- CQCrossServer.exe (1616 دالة)
- NpcServer.exe (4205 دالة)

## المرحلة 4: MsgServer.exe (28042 دالة) — الأضخم، أخيرًا

## التزامات ثابتة في كل المراحل
1. نفس أسماء الكلاسات والدوال والمسارات الأصلية للنسخة v6159 حرفيًا.
2. كل بورت من المفكك فقط؛ ما لا يكفي مصدره يوثق في Docs/NEEDS_RESEARCH.md.
3. Regression خضراء كاملة بعد كل إضافة، وASan/UBSan نظيفة.
4. Git push بعد كل وحدة مغلقة.
