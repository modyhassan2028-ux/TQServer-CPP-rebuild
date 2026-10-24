# HANDOFF — نقطة تسليم للأجنت التالي (آخر تحديث: 2026-10-24، نهاية جلسة العائلات الأخيرة 3907/8007/8011/9001 — السويتش الوظيفي مكتمل 100% من الصفوف الحية)

> هذا الملف هو نقطة البداية لأي أجنت يكمل الشغل. اقرأ PORTING_LOG.md للمنهجية
> والتاريخ الكامل، وهذا الملف لمعرفة "أنا فين دلوقتي بالظبط".

## القاعدة الحاكمة (لا تُخالف)
- **بورت حرفي فقط** للكود المفكك من MsgServer.exe.decompiled.c (28,042 دالة).
  لا كود مخترع ولا "تحسينات". تعليقات `// ORIGINAL` سطر بسطر.
- **لا final builds ولا zig ولا binaries ولا release uploads** — push كود فقط.
- حدّث PORTING_LOG.md بعد كل وحدة، وحدّث هذا الملف في نهاية كل جلسة.
- الشغل مستمر ذاتيًا بدون طلب إذن (قاعدة المالك). الاختبارات ضد صفوف DB حقيقية.
- **بعد كل وحدة/ميلستون: حدّث هذا الملف فورًا + git commit + git push
  على طول (طلب المالك 2026-10-23) — عشان حالة الشغل تكون محفوظة في
  المستودع لو الكريدت خلص في نص الشغل. مفيش commit من غير push أبدًا.

## البيئة
- المستودع: github.com/modyhassan2028-ux/TQServer-CPP-rebuild (branch main، push مباشر).
- المرجع: ../co_repo/Native-Decompiled/MsgServer.exe.decompiled.c + الباينري
  ../conquer_src/Source/MsgServer.exe (للتحقق بـ objdump).
- قاعدة البيانات: `mariadb -u root cq` (صفوف حقيقية v6159: cq_action 48 ألف صف،
  cq_levexp، cq_rebirth 251 صف، cq_bonus موجودة، cq_itemaddition...).
- بناء اختبار الحوار:
  `g++ -std=c++17 "-D__declspec(x)=" -I. -Iinclude -ICore/CQBase -ICore/DB -ICore/Root -IExe/MsgServer -IExe/NpcServer -IExe/CQCrossServer -Ivendor/lua -IModules/Syndicate -IModules/Trade -Wno-unused-parameter tests/dialog_fidelity_test.cpp tests/stub_cross_client.cpp $(ls Exe/MsgServer/*.cpp | grep -v main.cpp) Exe/MsgServer/LuaScript/LuaVM.cpp Exe/MsgServer/Activity/ActivityManager.cpp Core/CQBase/*.cpp Core/DB/*.cpp Core/Root/*.cpp /tmp/luao/*.o -lm -ldl -lpthread -o /tmp/fidelity_test`
  (objects لوا في /tmp/luao — لو ضاعت: `cd vendor/lua/src && cc -c *.c` لكل ملف
  إلى /tmp/luao، انظر PORTING_LOG).
- **بناء سريع (جديد، موصى بيه)**: كاش objects موحّد بـ g++ -O0 في
  **/tmp/objs2** (48 object، ABI واحد __cxx11 — كان في مشكلة خلط
  zig/libc++ مع g++/libstdc++ قبل كده). أي اختبار جديد:
  `g++ -std=c++17 -O0 "-D__declspec(x)=" -I. -Iinclude -ICore/CQBase -ICore/DB -ICore/Root -IExe/MsgServer -IExe/NpcServer -IExe/CQCrossServer -Ivendor/lua -Wno-unused-parameter -c tests/X.cpp -o /tmp/tu.o && g++ -o /tmp/xtest $(ls /tmp/objs2/*.o | grep -v tu_) /tmp/tu.o /tmp/luao/*.o -lm -ldl -lpthread`
  (~10 ثواني بدل 8 دقايق). لو /tmp/objs2 ضاعت، أعد بناءها متوازيًا:
  `(ls Exe/MsgServer/*.cpp | grep -v main.cpp; echo tests/stub_cross_client.cpp; ls Exe/MsgServer/Activity/ActivityManager.cpp Exe/MsgServer/LuaScript/LuaVM.cpp Core/CQBase/*.cpp Core/DB/*.cpp Core/Root/*.cpp) | xargs -P $(nproc) -I{} sh -c 'f="{}"; g++ -std=c++17 -O0 "-D__declspec(x)=" -I. -Iinclude -ICore/CQBase -ICore/DB -ICore/Root -IExe/MsgServer -IExe/NpcServer -IExe/CQCrossServer -Ivendor/lua -Wno-unused-parameter -c "$f" -o /tmp/objs2/$(echo $f | tr "/" "_")'`
  (غيّر امتداد .cpp إلى .o في الاسم). الربط النهائي بـ g++ مش zig.
- ملاحظات مالية: لو الرسائل/الدفعات فشلت: انتظر تجديد الـ credits الشهرية.

## وين وصلنا بالظبط — سويتش cq_action (FUN_14012a6e0، 175 case)
مربوطة حرفيًا ومختبرة كلها: 1010/1011/1013-1021 القديمة، 1022 (0x10 gmlog)،
**1023** (0x11 غلاف المطالبة — لكن انظر PORT-PENDING تحت)،
**1024** (0x12 طلاق كامل: غرض 0x109a02=1088002 للرفيق + مسح mateid للطرفين +
chk_sum بمعادلة FUN_1400fe140 كاملة + LAST_INSERT_ID)،
**1025** (0x13 mate)، **1026** (0x14 face gate: lookface/10000==1)،
**1027** (0x15 task)، **1028** (0x16 flag chk/add/clr)،
**1029** (0x17 play/broacast موجات: باكِت MsgName 1015 / action 0x14)،
**1040** (0x22 rebirth)، **1080/1081** (timestamp vars)،
**1086** (0x4c levexp var، objdump-verified)، وأصناف 503-520 القديمة.
**النتيجة: كل الأنواع الصغيرة الشائعة في السويتش خلصت.**

## المتبقي بالترتيب (ابدأ من 1 — المهم دلوقتي: مهارة 3 Skills)

### خطة نظام المهارات (تم تحديده بالفعل — ابدأ من هنا)
**مبورت خلاص (متلمم ومختبر جزئيًا)**:
- CMagicTypePool::LoadFromDB (cq_magictype، 1,266 صف في القاعدة) +
  CPlayerMagic record (cq_magic، 680 صف) + Save/Erase/SetAttrib.
- CUser::LearnMagic (FUN_1404939c0 حرفي: بوابة النوع/المستوى، re-learn
  يمسح unlearn بس، id من الـ pool) — User.cpp.
- WeaponSkill: LoadFromDB/Find/GetMaxLevel/AwardWeaponSkill
  (FUN_140170ae0)/AddWeaponSkillExp/AwardWeaponSkillTime — User.h/cpp.
- بوابات التست الحالية (gates 10/30، stamina 20/30، ضرر 2.5x/1.5x)
  في tests/skills_test.cpp.

**مبورت خلاص كمان (اتكوميت 07d137f + 4c93c92، 2026-10-24)**:
- عائلة CMsgMagicEffect **كاملة** (1105 = 0x419): Create
  (FUN_140386800)، CreateWithTarget (FUN_1403868f0)، AppendTarget
  (FUN_140386d00 بسقف < 0x400)، CreateFull (FUN_140386e00 بغرابة
  param_9 على قاعدة الإدخال التالي) — MsgMagicEffect.h/cpp،
  تخطيطات بايت-مطابقة مختبرة (tests/magic_effect_packets_test.cpp).
- عائلة CMsgMagicInfo **كاملة** (1103 = 0x44f، FUN_140457240): mode 4
  (attach) و mode 6 (drop) — MsgMagicInfo.h/cpp.
- دوال الأثر الثلاثة على CUser: AllowLaunchEffect (FUN_14048c770)،
  AttachEffectType (FUN_14048c7e0)، DropMagicEffect (FUN_14048c4c0
  بسقف 40 سجل + صنف التحول 0x2dd5b6=3000694) — User.h/cpp.
  ملاحظة: available_effect_type العمود افتراضه 1 (بت 0).

**الناقص (محرك الإطلاق الفعلي — نقطة البداية المحددة في الدمب)**:
- ~~عائلة CMsgMagicEffect~~ **تمت كاملة** بما فيها Process
  (FUN_1403872c0 ستب بلوج "invalid msg CMsgMagicEffect." الحرفي)
  و FUN_1404851b0 SendMagicEffectAfterProcess (بث 1105 FULL من
  السجل للخريطة كلها) — جلسة 2026-10-24 الخامسة، ريجريشن 33/33.
- عائلة CMsgMagicInfo: ~~FUN_140457240~~ تمت — فاضل Process عند
  869377+ (FUN_140456ea0/140456f80 طاقة ctor/dtor).
- المرسلات/التأثير: ~~FUN_1404851b0~~ تمت (جلسة خامسة). فاضل
  FUN_140486fb0 (GroupByPos) وخضائره كلها جاهزة خلاص (جلسة سادسة):
  CreateGroup=FUN_140386a50، AppendGroup=FUN_140387150 (نفس غرابة
  dwNext على قاعدة الإدخال التالي)، JumpPos=FUN_140388a40،
  IsValidPos=FUN_14015f9d0 — كلها مبورتة ومختبرة بايت-مطابق.
  FUN_14048c4c0 (2 إشارة MagicEffect — ده غالبًا Launch/Apply).
- الحلقة المفقودة: Intone (شحن السحر) → Launch (إطلاق) → التحقق
  من الهدف/المسافة/crime → حساب الضرر من cq_magictype (power/
  percent/level) → تطبيق التأثير على الأهداف → بث MsgMagicEffect
  للخريطة → خصم MP/stamina → exp uplevel (بوابة need_exp/
  need_level من cq_magictype).
- ملاحظة قاعدة: المهارات الحية في cq_magictype نوعها sort=1 (سحر)
  وسلاح XP في جدول أسطح: تحقق من عمود weapon_subtype.
- طريقة العمل المعتادة: objdump على الباينري الأصلي عند كل شك،
  بورت حرفي، تست بصفوف حقيقية (تعلم/شحن/إطلاق/ضرر/uplevel)،
  ريجريشن، commit+push فورًا.

1. ~~FUN_140145f60 — تم اكتشاف أنه مبورت خلاص (هو ProcessAction
   الرئيسي نفسه، سويتش العائلات الـ22 + العمق + البروفايلنغ)، ومطالبة
   1023 موصولة بيه ومختبرة حية (جلسة 2026-10-24): اختبار
   action_1023_bonus_test ALL PASSED — صف 17510 حقيقي يمنح
   UltraBadge 721716 بسلسلة 4010171، flag=1+time، إعادة المطالبة
   فاضية، بوابة STR_BAG_FULL. ملاحظة حرفية مهمة: المعالج لو رجّع
   false بيمشي id_nextfail، ولما يوصل صفر بيرجع المحرك 1 حرفيًا
   (LAB_1401469ca) — نتيجة ProcessAction مش دليل نجاح المطالبة،
   الدليل في الأثر (المنح/العلم).~~
2. ~~عائلات السويتش الأكبر~~ — اكتمل الفحص (جلسة 2026-10-24):
   - **701-798 (ProcessActionSyn/FUN_140128290): مبورتة كاملة**
     (الأنواع الحية 701-722 كلها + اكتشاف أن 705/708/709 مالهاش
     كيس في الأصل خالص → false حرفي). اختبار
     action_701_722_syn_test ALL PASSED على 20 سيناريو بصفوف حقيقية،
     ريجريشن 7/7. تفاصيل كاملة في PORTING_LOG.
   - **3501-3598**: كانت مبورتة خلاص من قبل (3501/3510/3521/3523/3524
     تغطي كل الصفوف الحية الـ118) — توثيق قديم بس كان ناقص.
   - عائلات **صفر صفوف حية**: 601-698، 3601-3698، 3801-3898 —
     مفيش صفوف في cq_action، الأولوية الأدنى.
   - **3001-3012 (ProcessActionWanted/FUN_14011a7e0): مبورتة كاملة**
     (جلسة 2026-10-24 الثانية) — مكتب المكافا: نشر/قبول/إلغاء/زيادة
     مكافأة + لوح الشرطة + بوابة المطلوبين، مدير CWantedManager
     جديد، توكنات %iter_wanted/%iter_police_wanted. اختبار
     action_3001_3012_wanted_test ALL PASSED (15 سيناريو حي).
     3009 مالهاش كيس في الأصل → false حرفي.
   - ~~**المتبقي الفعلي**: 3907 (5 صفوف)، 8007/8011 (7)، 9001 (1)~~ —
     **تمت (جلسة 2026-10-24 الرابعة)**: 3907 award gate (FUN_140131eb0)،
     8001-8384 dialog/other-server (FUN_140128b30)، 9001-9384
     OS-visitor/frontier (FUN_14012f860) كلها مبورتة حرفيًا.
     اختبار tests/action_final_families_test.cpp الجديد 33 سيناريو
     ALL PASSED + ريجريشن 7/7 (fidelity 3/3 جولات). تفاصيل objdump
     كاملة في PORTING_LOG. **السويتش الوظيفي للـ cq_action مكتمل
     100% من ناحية الصفوف الحية** — كل الأنواع الحية ليها معالج.
3. **نظام المهارات (Skills)** — أكبر ناقص في الـ gameplay كله، لم يبدأ حرفيًا.
4. بعد كده: بقية دوال السيرفر الوظيفية (تقدير الحالي: 30-40% معمول،
   نصفه حرفي بالكامل، من أصل 28,042 دالة مفككة).

## تقنيات مثبتة (مهمة جدًا — موثقة بالتفصيل في PORTING_LOG)
- **الـ exe بلا relocations (.reloc=0)** → الـ vtables مخزنة كـ VA كاملة
  (qword 8 بايت). جدول **CUser الحقيقي عند file offset 0x71d348** (49 خانة):
  slot+0x8=GetId(+0xe80)، +0x50=FUN_1401bf470=[+0xeac]/10000،
  +0xa0=GetExp(+0xed0)، +0x108=GetMetempsychosis(+0xf00).
- **تحويل VA→file offset: يجب عبر جدول الـ sections** (مثال: .rdata VA
  0x1406d8000 ↔ file 0x6d6600). الصيغة المختصرة `0x400+(VA-0x140001000)`
  صحيحة **فقط للـ .text**؛ في .rdata تضلّ 0xA00 بايت (اتعملت الوحدة 7).
- **Ghidra يفقد تفاصيل ويطوي الوسائط** (sscanf/_snprintf: راجع objdump
  للسجلات الفعلية قبل تحديد القيم). عند أي شك: objdump مباشرة على
  الباينري هو المصدر النهائي.
- **printf المخزن يضيع عند assert** — استخدم fprintf(stderr)+fflush أثناء
  التشخيص.
- الـ CGameData records: field(0)=level إلخ حسب ترتيب أعمدة الـ SELECT،
  وقيم الحقول عبر الـ wrapper vcall+0x58 (int64) / +0x10 (اختيار الحقل).

## وضع الأنظمة الكلية
- شغالة ومختبرة: شبكة/لوجين/حركة/خرايط، NPC+حوار، وحوش، أشياء+ترقية،
  سوق لاعبين، جيلد وار+PK bounty، أنشطة، Lua bridge، كروس سيرفر.
- **المحرك الرئيسي FUN_140145f60 اكتمل** (1deb328): كل سلاسل cq_action
  تمر الآن عبر الـ master walker الحرفي — بوابات id-0/عمق-11/[PM]/OS-user،
  قاعدة الصف 320 (توقف السلسلة حرفيًا)، حد 33 خطوة، بروفايل per-type،
  وتفعيل 1023 منح حقيقي. كلا الاختبارين PASSED (dialog + orig_db).
- **أنواع 205/207/208 (FUN_14013b950 subcases) اكتملت:**
  205 = حذف NPC (data=0 → NPC الحوار مع مسح ctx + بوابة [+0xb4]،
  data!=0 → purge كل NPC من النوع ده، مسح فاشل يوقف بـ false، مشي
  فاضي يرجّع true)، 207 = تفريع حسب نوع NPC الحوار (نوع 10 stall /
  46 pole — العمليتين pending للنظامين الفرعيين، غيره false)،
  208 = استنساخ NPC الحوار إلى (id,map,x,y) من فورمات "%u %u %d %d"
  مع دايناميك + بث الظهور، ويرجع false دايمًا زي الأصل. CNpcManager
  كسب RemoveNpc/GetAllNpcs. اختبار npc_ops_205_207_208_test PASSED
  مع القواعد الثلاثة القديمة (35 صفًا حقيقيًا مغطى).
- **218/219/3501/3510 اكتملت (منظومة الـ Clan كاملة):**
  218 = إنشاء Clan من الاسم المكتوب في dialog 103 (ctx.strInput عبر
  tq::NameStrCheck الأصلية؛ اسم رافض → رسالة STR_INVALID_FAMILY_NAME
  + false؛ صالح → INSERT cq_syndicate + cq_synattr rank=1000 مع
  LAST_INSERT_ID، مكرر/عضو موجود → false)،
  219 = حل Clan (syn id للازم، leader-only، del_flag=1 في
  cq_syndicate + حذف cq_synattr + مسح كل الأعضاء من الفهرس)،
  3501 = عمليات سجل العضو (FUN_140140380 idx0): rank byte بعمليات
  > == += -= = مع الأبواب الحرفية (+= يجب ≤4، -= يحتاج rank>=قيمة،
  = يرفض >4، كل رفض بسجل "Wrong param" 0x140710420)، وstar_tower
  byte بعمليات عادية، وmoney int64 لخزنة الكلان (vcall+0x198/190/1a0)،
  3510 = عمليات الـ duty rank (idx9، field "rank" فقط: == >= += -= =،
  القائد duty=100). واجهة الـ syn كاملة على CGuildManager:
  GetSynIdOfUser (+0x128)، GetSynRecOf (rank/star/duty)، خزنة
  Get/Add/SetTreasuryOf، CreateForAction (vcall+0xf0)،
  DisbandForAction (vcall+0x100)، LoadFromDB (cq_syndicate +
  cq_synattr، duty = rank/10)، AttachMember. اختبار
  clan_218_219_35xx_test PASSED (26 assert) مع القواعد الأربع
  القديمة كلها خضرا، وختام DB round-trip حقيقي (إنشاء/حل مع فحص
  الصفوف في MariaDB).
- **نوع 201 (FUN_14013ba1e) اكتمل:** عمليات سجل الـ DynaNpc بالكامل —
  ownerid/ownertype/lookface (=/==)، datastr (=/==، عمود 15)،
  data0-3 (=,+=,==,<,<=,>,>=)، "accept" تعيد قراءة إدخال اللاعب
  (ctx.strInput)، life(24)/maxlife(25) مع بث CMsgUserAttrib للخريطة،
  استهداف npcId بالتوكن الرابع، gmlog/npc_820 لسجل 820، وبوابة
  IsDynaNpc. حقول السجل أضيفت لـ CNpc (m_bDyna يضبط من 2007 spawn)،
  وسياق الحوار صار يتعبأ من NPC التفاعل في MsgInteract. اختبار
  npc_record_201_test PASSED مع القاعدتين القديمتين.
- **منظومة 35xx كاملة (3521 آخرها):** 3521 = توزيع دخل معركة العيلة —
  فُكّ مخزن الدخل العالمي (0x140975e00، مفتاح (domain,syn,type)):
  FUN_140151580 قراءة / 151380 إنشاء+تصفير / 1511e0 مسح / 1515b0 تراكم؛
  FUN_14018eb30 = field4 من سجل المستخدم+0x1100؛ FUN_14008a6c0 = دقائق
  من [mapgroup+0x3b8] (نُمذجت SetKernelMinutes). البورت الحرفي: بوابات
  domain/vcall+0x40 early-true/holder(field19)/جمع أونلاين نفس السين +
  نافذة 15 دقيقة ثلاثية المسارات + SUCCESS (استهلاك الدخل → خزنة
  +0x190 → إعلان STR_FAMILY_BATTLE_SUCCESS_ADD_INCOME → +0x1a8 →
  رسالة DEFEND_SUCCESS) وDEFEND (مسح دخل المتحدى → خزنته → إعلان
  FAIL_ADD_INCOME → تبديل التحدي +0x1b8 → رسالة CHALLENGE_SUCCESS) +
  حلقة الالتقاط المتأخرة بأقصى قيمة معركة. CFamilyBattleManager كسب
  مخزن الدخل وقيم المعركة وKernelMinutes؛ CGuildManager كسب
  AddTreasuryOfSyn/SetChallengeDomainOfSyn/AnnounceOfSyn. اختبار
  family_income_3521_test PASSED (9 حالات) — القواعد الثمانية كلها
  خضرا. نمذجة موثقة: +0x1a8 = علامة "تم التوزيع" (الكاتب الوحيد
  المرئي لعلم vcall+0x40).
- آخر 3 commits: 207 stall/pole + input flow (هذا)، 223/224 home
  furniture (e3c2393)، 3521 income (b0fd4a8).
- **3523/3524 اكتملت (فحوص نطاق معركة العيلة):** النوعين يحسّنان
  (rec8 vcall+0x1c0 = نطاق الحيازة / +0x1b0 = نطاق التحدي لكل عيلة)
  مقابل عمود data (مجموعة 10026-10035 في القاعدة)، مع بوابة سجل
  المجال vcall+0x88 (سجل غير موجود → false). CFamilyBattleManager جديد
  (Exe/MsgServer/FamilyBattle.h/cpp): سجلات نطاقات معركة العيلة بمقابض
  حرفية (field19=حيازة السين، field1=المتحدي vcall
  FUN_1400872b0(rec,idx)، field4=مبلغ الدخل، vcall+0x40=علم "تم
  التوزيع")، seeding من قيم data المميزة في cq_action لأن نظام جدولة
  المعركة نفسه لم يُبورت بعد. SeedFromDB موصولة في main.cpp.
  CGuild كسب m_dwHoldDomain/m_dwChallengeDomain + مدير m_byId
  (GetSynById). اختبار family_battle_352x_test PASSED.
- **منظومة FUN_14013b950 (201-224) كاملة — 223/224 آخرها:**
  - **223** (jump idx22 @ 0x14013cf17): نقل أثاث بيت اللاعب — بعد
    تعويض %vars، parser حرفي لأعداد مفصولة بمسافات في مصفوفة 64
    (الأرقام فقط تتراكم، التوكن غير الرقمي يُحتسب بقيمة 0)، شرط >= 4
    أعداد (سطر 0xcca)، بوابات map!=0/type>0 (سطر 0xcd2)، npcMgr
    vcall+0xc8(map,type) لازم غير فارغ (لوغ GBK "لا يوجد NPC
    بالنوع")، سجل الخريطة FUN_1400876b0 vcall+0x10 ("الخريطة غير
    محملة")، لكل NPC زوج (x,y) واحد يُستهلك معه: فحص
    FUN_1402c3cc0 (Invalid Point لوغ ويُستهلك الزوج)، كتابة fields
    8/9 (x/y)، نقل FUN_1402bf7a0، لوغ حرفي
    gmlog/ActionNpcChangePos بنص NpcID/OwnerID/NpcName/Old/New.
    دائمًا true.
  - **224** (jump idx23 @ 0x14013d604): فحص عد الأثاث — sscanf
    "%u %d %d" (شرط >= 2 قيم وإلا لوغ 0xd17)، النتيجة =
    vcall+0xa8(map,type) (عدد NPC النوع على الخريطة) >= (v3!=0?
    v3:1).
  - CNpc::MoveTo(map,x,y) (كتابة fields 8/9 + النقل)؛
    CNpcManager::GetNpcsOnMapOfType (vcall+0xc8). اختبار
    home_furniture_223_224_test PASSED (9 حالات). **القواعد التسعة
    كلها خضرا.**
- **آخر نقطتين في الخطة اكتملتا — PORT-PENDING القديم انتهى:**
  - **207 نوع 10/46** (فك 0x14013c7ef..0x14013c8b4): النوع 10 → مدير
    الستول FUN_140087ed0 (singleton كسول: root mgr [0x1406d8df0] →
    vcall+0x20(0x16) مخزن عند 0x140975c50، CHECKF 0x3ef لو null) ثم
    vcall+0x328(npcId)؛ النوع 46 → نفس الـ root mgr، بوابة
    FUN_14008b330 ([mapgroup+0x77c]): true → فئة 0x25 عبر
    vcall+0x78(npcId)، false → فئة 0x1c عبر vcall+0x40(npcId).
    نمذجة: StallPole.h/cpp — CStallManager (سجل معرفات الستول) و
    CPoleManager (بوابة pole-mode + سجلان: فئة 0x25/0x1c)، النقل
    إزالة بالمعرف → bool. النظم المُنشِئة للستول/الأعمدة (أنظمة
    أخرى) لما تُبورت تسجل هنا.
  - **إدخال الحوار 6159**: حوار 103 (input) يسجل الآن فعل الاستمرار
    في User::SetPendingInput (مع خيار البوش القديم)، ورد العميل
    المكتوب يصل MsgTalk(1004) إلى الـ NPC المتحدث: فرع الإدخال في
    MsgTalk::Process يخزن النص في ctx.strInput ويقفز للفعل، ثم
    يُستهلك. ClearDialogOptions يمسح البندنق. اختبار
    dialog_input_flow_test PASSED (صف حقيقي 5021750 نوع 218).
  - **القواعد الـ 11 كلها خضرا.**
  عائلات النطاقات الأخرى
  غير الشائعة تسقط لسلوك محفوظ (return محدد لكل عائلة)، وفرع
  sysdata/taskdata في المُحلِّل — صفر استخدام في القاعدة الحقيقية.

## جولة 801/802 (عائلة FUN_140127070) — مكتملة (2026-10-23)
- **النافذة 801..862 كلها مفتوحة الآن**: 801 (dropitem/dropmoney
  بمعادلات roll الحرفية: bound + tq::RandGet(100-bound)، mod-100
  الموقّع، بوابات level<80&&money<=10 الصامتة، LuckyTime، >>3/>>2)
  و802 (أكوام مالية لكل وحوش النوع نفسه على الخريطة، نطاق مستويات
  [min,max]، حد 0x12). أي نوع آخر في النافذة = سجل "wrong Action
  Type" + FALSE حرفيًا (ProcessActionFamily8xx).
- **CMonster**: m_dwDropMoneyBase [mon+0x2c]، m_dwLuckyTime
  [mon+0x1230→power]، m_bDropBonus [mon+0x10f8]، m_dwDropBonusLevel
  [mon+0x100] — عامة للقراءة من الأنظمة الأخرى (مصدرها لودر الوحوش
  الأصلي، يوصل لما يُبورت).
- **CUser::m_dwSourceMonsterId** = استعلام "0x1002" (وحش مصدر الفعل
  — سلاسل ذكاء الوحش). فشله يفشل 801/802 حرفيًا.
- **tq::RandGet** (CQBase 0x140b82fb0) في Msg.h — بورت حرفي مع قناع
  15-bit (rand على glibc 31-bit).
- **GroundItems**: AddMoneyDrop/AddItemDrop/FindDrop/AllDrops
  (بوابات صريحة للاختبارات والأنظمة).
- **اختبار action_801_802_test**: 14 حالة على صفوف حقيقية — ALL
  PASSED، والقواعد 13 القديمة كلها خضرا.
- **فحص نزاهة القاعدة (تحقق ذاتي، أرقام موثقة في PORTING_LOG):**
  cq_action جزئية من cq_action_total (157,019 صفًا محجوزًا)؛ 605
  أهداف مكسورة في السلاسل (517 قابلة للاستعادة حرفيًا من total)؛
  9,442 مدخل task بلا صف (8,524 قابل للاستعادة).
  **→ حُذفت مرحلة "استكمال cq_action من total" نهائيًا (تصويب المالك
  2026-10-24): القاعدة كاملة بالحرف زي الأصل. cq_action فهرس جزئي
  صارم عمدًا؛ الوصلات المعلقة هدفها مش في الفهرس عمدًا والموتور
  الأصلي بيستانسها ويمشي id_nextfail. لا استكمال ولا إضافة صفوف —
  ده هيبعدنا عن الأصل.**

## جولة عائلة 401/402/403/498 (FUN_1401199d0) — مكتملة (2026-10-24)
- **النافذة 401..498 مفتوحة كلها في ProcessActionItemOnly**:
  401 (تسجيل مهمة وضع الوحش: [user+0xa34]=next، [user+0xa38]=""
  ثم EVENT_LAYNPC deferral)، 402 (عدّ cnpc الخريطة بسوكنس
  "%s %s %s %d" الحرفي 4 توكنز — all/furniture=type 25/name/type
  مع "<" و"==" فقط)، 403 (رد الخلية ≥3 أرقام + خلية ممشوقة وفاضية
  + سپيك 22 خانة + بوابة sort 0xf -> STR_DISABLE_LAY_SYNTRANS +
  بوابة nGate — 3=دروب أرضي بالخلية — + owner 1/2/3 ثم CNpc::Create
  و[user+0xa30]=id الوحش)، 498 (استهلاك العنصر FUN_140340190 +
  [user+0x14c]=0 + STR_USE_ITEM).
- **تصويبان مهمان من الأصل**: النافذة مافيش فيها default فاصل فوق
  199 يكسر السلاسل، و402 لازم 4 توكنز حرفيًا حتى لو العداد "all"
  (خانة المعطى placeholder).
- **صفوف حقيقية في الاختبار**: 150050/150060/150061 (تمثال MoonBox
  721055: زرع دروب → 403 ينشئ عند الخلية → 498 يستهلك)، 410406
  "type 25 < 8"، 410412 furniture، 150160 GuildTeleporter1 (sort 15 —
  متعطل بالبوابة الحرفية عمدًا)، وسلسلة حية 150050 -> 150060 -> 150061.
- **إصلاح جذري لتلف 69 ملف Modules المتكرر**: المولّد
  gen_module_skeletons.py كان بيكتب من مصدر ../conquer-online-v6159-decompiled
  الغايب في السانبوكس فيفرغ الهياكل في كل بناء. الآن fallback إلى
  co_repo + حرس no-op لو المصدر اختفى — التوليد الجديد مطابق
  للملتزم 100% (git status نضيف).
- **اختبار action_401_498_test: ALL PASSED** + ريجريشن أخضر
  (action_801_802_test PASS بعد التعديلات).
- **قيادة الاختبارات المُثبتة (native)**: استخدم /tmp/build401.sh
  كنموذج (zig c++ native + /tmp/luao/*.o لوا native — لو ضاعت:
  cd vendor/lua && cc -c -O2 -w *.c إلى /tmp/luao). CrossClient
  يستبدل بـ tests/stub_cross_client.cpp (مصدر CrossServer/*.cpp
  winsock-only فلا يدخل في بناء native أبدًا).
