# Comprehensive inventory: decompiled vs ported (auto-generated)

Generated: 2026-10-26 by tools/full_inventory.py. A function address counts as ported when it appears in port code AND exists in that binary's index.

| Binary | decompiled funcs | ported addr refs | % |
|---|---|---|---|
| Analyst.dll | 85 | 24 | 28.2% |
| AntiCheat.dll | 1,133 | 0 | 0.0% |
| Arenic.dll | 1,420 | 0 | 0.0% |
| Booth.dll | 601 | 0 | 0.0% |
| CQBase.dll | 3,095 | 0 | 0.0% |
| CQCrossServer.exe | 3,127 | 129 | 4.1% |
| ClanPKArenic.dll | 2,317 | 0 | 0.0% |
| Common.dll | 428 | 0 | 0.0% |
| Competion.dll | 1,088 | 0 | 0.0% |
| CrossFlagWar.dll | 1,569 | 0 | 0.0% |
| CrossStatus.dll | 1,095 | 0 | 0.0% |
| DB.dll | 2,736 | 0 | 0.0% |
| DetainEquip.dll | 792 | 0 | 0.0% |
| ElitePKArenic.dll | 2,227 | 0 | 0.0% |
| EpochHook.dll | 254 | 0 | 0.0% |
| FactionMatch.dll | 863 | 0 | 0.0% |
| Family.dll | 2,041 | 0 | 0.0% |
| FamilyArenic.dll | 1,756 | 0 | 0.0% |
| Flower.dll | 402 | 0 | 0.0% |
| FrontierFlagWar.dll | 1,563 | 0 | 0.0% |
| Guide.dll | 1,232 | 0 | 0.0% |
| INIFileParser.dll | 209 | 0 | 0.0% |
| LeaveWord.dll | 1,803 | 0 | 0.0% |
| Lottery.dll | 1,051 | 0 | 0.0% |
| MsgServer.exe | 59,977 | 637 | 1.1% |
| NpcServer.exe | 7,239 | 219 | 3.0% |
| Peerage.dll | 327 | 89 | 27.2% |
| Pigeon.dll | 696 | 0 | 0.0% |
| PopPKArenic.dll | 2,313 | 0 | 0.0% |
| Rank.dll | 768 | 0 | 0.0% |
| Relation.dll | 1,458 | 0 | 0.0% |
| RevampedHook.dll | 259 | 0 | 0.0% |
| RevampedLoader.exe | 119 | 1 | 0.8% |
| Sponsor.dll | 614 | 0 | 0.0% |
| Status.dll | 1,559 | 0 | 0.0% |
| Storage.dll | 908 | 0 | 0.0% |
| Syndicate.dll | 9,865 | 312 | 3.2% |
| TaskDetail.dll | 691 | 11 | 1.6% |
| Team.dll | 993 | 0 | 0.0% |
| TeamArenic.dll | 2,039 | 0 | 0.0% |
| Title.dll | 330 | 54 | 16.4% |
| Totem.dll | 1,152 | 0 | 0.0% |
| Trade.dll | 791 | 0 | 0.0% |
| Training.dll | 333 | 55 | 16.5% |
| VexillumArenic.dll | 1,478 | 0 | 0.0% |
| Wanted.dll | 637 | 0 | 0.0% |
| root.dll | 719 | 0 | 0.0% |
| root_real.dll | 719 | 0 | 0.0% |
| **Total** | **128,871** | **1,531** | |

---

## تحديث 26/10 (بعد D69) — استرجاع المرجع الخام الكامل

- أرشيف المصدر الأصلي Conquer_Online_Source_v6159.7z (829MB) استُرجع من MediaFire بنجاح.
- **كل الـ 51 DLL أصلية** (بناء 2015-12-11) استُخرجت إلى co_decomp/orig_binaries/Source/ بجوار الـ EXEs: كل وحدات اللعبة (Syndicate, Analyst, Title, Training, Peerage, Family, Flower, Trade, Wanted, ... إلخ) + runtime DLLs. حجم المجموعة 18MB.
- بذلك كل تحقق خام لاحق (capstone) يتم محليًا بدون MediaFire. مفاتيح فك PE: imagebase(Syndicate)=0x141720000، قسم .text raw=0x400/va=0x1000.
- أول استخدام: وحدة D69 (عائلة CMsgLeagueBeRob) — كل الأشكال الملتبسة أُكدت بالبايت من Syndicate.dll الأصلي.
- الجرد المحدث لـ Syndicate.dll بعد D69: 325+17 دالة منقولة (الأدق مع نمط 0x غير FUN_). أكبر المتبقي: FUN_141771f90 (7453B، مستهلك عيلة D69 مباشرة) ثم 14176b0d0 (6549B) و14176ca70 (4163B) و141736d40 (3762B).

## تحديث 26/10 (بعد D70) — اكتمال موزّع رسائل LeagueBeRob

- FUN_141771f90 (7453B، أكبر دالة متبقية في عيلة العصبة) مُنقولة كاملة كـ LeagueBeRobBroadcast: مسارات A/B (التداخل المزدوج على +0x3f0/+0x430 مع النزول المُضمَّن)، C (رسالة النوع 3 + فشل الاسم)، D (اتحاد مدى المفاتيح من +0x370/+0x3b0 إلى +0x470 ومجموعة النتائج)، E (مشي الخرائط + رسائل النوع 4 المزدوجة)، والكتلة المجمّعة (النوع 2 + رقصة الإفراغ وإعادة التشغيل + الأنواع 2/3/4 + رسائل مجموعة النتائج 5/6).
- أكبر المتبقي في Syndicate.dll الآن: 14176b0d0 (6549B) ثم 14176ca70 (4163B) و141736d40 (3762B).
