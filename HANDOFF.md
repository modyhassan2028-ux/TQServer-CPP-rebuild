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
- المرسلات/التأثير: ~~FUN_1404851b0~~ تمت (جلسة خامسة). ~~FUN_140486fb0
  GroupByPos~~ **تمت كاملة** (جلسة سابعة): بث 1105 جماعي + سحب الأهداف
  (JumpPos) + لوج 0x1f00 + بث 0x6e المشهدي (لوج) + CMsgAction الزعيم
  (407 في خانة البيانات والاتجاه في خانة الـ action — حرفي). الخضائرات
  كلها مبورتة (جلسة سادسة): CreateGroup=FUN_140386a50،
  AppendGroup=FUN_140387150، JumpPos=FUN_140388a40،
  IsValidPos=FUN_14015f9d0. بوابات الإطلاق تمت (جلسة ثامنة):
  FUN_1404864f0 (IsTargetProtected حرفي: منطقة/PK>999+STR_PK/
  حصانة السورتات/friendly) وFUN_1404831f0+1403e9290 (بوابة
  السحب: status 0xa0 + رول مقاومة) وFUN_140483270 (هوك خامل).
  **اكتشاف ABI**: GetAttrib(idx>=100) = عمود cq_magictype
  (0x66=sort/0x68=crime/0x7a=weapon_subtype/0x82=weapon_hit/
  0x87+0x88=status_data) — CPlayerMagic اتوسع بيه. فاضل
  FUN_1404847d0/140484670 (حساب الضرر) ثم FUN_1404a1f70 كامل +
  حلقة المروحة (DAT_140786e20) ثم FUN_140499830 وFUN_14048c4c0
  (إشارتا MagicEffect — غالبًا Launch/Apply).
- **جلسة تاسعة (تحليل فقط، لا كود)**: FUN_1404847d0 (حساب
  الضرر) قُرئ كاملًا مع هيلبراته — **المواصفة الكاملة الحرفية في
  PORTING_LOG.md قسم "جلسة تاسعة"**: المعادلات (جسدي/سحري/سموم)،
  الحالات المضاعفة (0x6c/0x78 ×2)، النوع 0x3070 بيفضل 1 HP،
  النوع 0x305c سقف attr_power + بديل power=status_data0، وكل
  أنواع السورت/النوع (0x25/0x39/0x2f26/0x2f30/0x2ed6/...).
  ABI إضافي مؤكد: 0x6e=power، 0x8b=attr_power، 0x90=data،
  0x89=status_data2، 0x91/0x92=أعمدة runtime 45/46 خارج الجدول.
  **تمت قراءة السلسلة كلها (كوميت 680574b — PORTING_LOG قسم
  "جلسة تاسعة، تكملة")**: FUN_1403ec0a0 (LaunchDamage) بتسلسل 14
  خطوة حرفي، والمكوّنات الأربعة (رول السلاح/هجوم-دفاع وسحرياتهما)،
  وFUN_1402f3100 جزئيًا. **البورت يبدأ كود من دلوقتي بالترتيب**:
  (1) kernel slots على موديل CUser (0x88/0x90/0xa0/0xb8/0x200/
  0x210/0x38) — أغلبها موجود، راجع User.h، (2) المكوّنات الأربعة
  بستابات موثقة للـ PK-adjust/الحماية/جودة السلاح (قيم كمعاملات)،
  (3) FUN_1403ec0a0 حرفي (stubs: aggro 1402f2de0/1402f2e10،
  التوجيه 14031d8a0، الكريتيكال 14031cfb0، الصد 140182560،
  التسوية 1403eb000)، (4) FUN_1404847d0 من مواصفة الجلسة تاسعة،
  (5) اختبارات ببذور RandGet محقونة. ملاحظات دقيقة: خصم الدفاع
  الأول بحد أقصى نص الضرر (FUN_1401811180 cap 100)، الثاني /100
  (ثابت 0x51eb851f)، الكريتيكال MulDiv(x,150,100)، بونص الخاتمة
  cap 1000 لنوع 8001، floor نهائي 2.
  الهيلبرات المفهومة: 140481400=IsPhysicalHit (weapon_hit==0)،
  140481560=IsMagicHit، 1404831a0=شفاء 12120/30/40،
  140483100=power بالمُحدد *(caster+0xf8).
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

## سجل بيئة موازية (2026-10-25) — مهم قبل أي عمل Peerage
شغال على نفس المشروع من حساب/ريبو تاني (الـ commit 0b1c9cc بتاعه
مش هنا). سجّل: **D22** (عائلة أسلاك الرسائل: بوابات Create
0x3ea/0x810، بناءات type 1/2/4، إلحاق مجمع، موزّع 141557690، سجل
0x30، ProcessMsg) مقفولة عنده 10/10 + 22/22 × 6، مع فخ موثق:
فiasco تهيئة std::function الساكنة في الاختبارات. **D23** (عائلة
التبرّع 141551750-780/141554c40/b10/1415558a0/141556db0/
141555dc0/1415520c0) عنده PeerageDonate.{h,cpp} (10 دوال) مكتوبة
وBuildMsgType1 متوحّد على g_fnMsgAppend، والاختبار (9 أقسام)
واقف على إصلاح تخطيط SElem (SVt دخلت جواها فكسرت +8=row). لو
هتشغل على Peerage هنا: دوال الديكومبايل جاهزة في
co_repo/Native-Decompiled/Peerage.dll.decompiled.c، ومفيش أي ملف
D22/D23 في هذا الريبو — البداية من الصفر مع مراعاة تخطيط SElem
(+8 = row) وسِمات TBD للأرجُم المسقطة من Ghidra. **والأولوية هنا
قبل كده**: قفل شغل حساب الضرر المعلق (attr_power في الـ loader +
إخضرار damage_roll_test + رجريشن + رفع). التفاصيل الكاملة في
PORTING_LOG قسم "جلسة 2026-10-25".

## آخر حالة الـ Agent الموازي (2026-10-25، غير مرفوعة عنده)
D22 موجودة في الريبو (0b1c9cc). المتبقي الوحيد في الشغل الموازي:
**D23 عائلة التبرّع** — PeerageDonate.{h,cpp} (10 دوال: 141551750-
780، 141554c40، 141554b10، 1415558a0، 141555dc0، 1415520c0،
141556db0) مكتوبة بسِمات TBD للأرجُم المسقطة من Ghidra (باينري
Peerage.dll غير متوفر)، BuildMsgType1 متوحّد على g_fnMsgAppend،
اختبار D23 (9 أقسام، mocks حقيقية) واقف على إصلاح تخطيط SElem
(+8 = row). لو هتكمل D23 من هنا: ابدأ بمراجعة مكانه في
Exe/Dll/Peerage/Port/ + دوال الديكومبايل في
co_repo/Native-Decompiled/Peerage.dll.decompiled.c (FUN_141551750
سطر 433، FUN_141556db0 سطر 4763). التفاصيل في PORTING_LOG قسم
"جلسة 2026-10-25 (لاحقة)".

## D23 مقفولة (جلسة 2026-10-25 مساءً)
عائلة التبرّع Peerage كاملة مبورة ومختبرة: PeerageDonate.{h,cpp}
(10 دوال حرفية) + BuildMsgType1 متوحّد على g_fnMsgAppend ويرجّع
نتيجة الإلحاق (char) + peerage_d23_test (14 قسمًا) + رجريشن
**23/23 × 6 أخضر**. سِمات TBD موثقة في الهيدر للأرجُم المسقطة
من Ghidra. الإجمالي الآن: D1-D23 كلها مقفولة. **التالي المقترح**:
D24 — راجع REMAINING_ROADMAP.md أو دوال Peerage.dll المتبقية
(مثل 141551920 rank query + أي دوال خدمة غير مُدارة)، أو الانتقال
للـ DLL التالي في الموجة. أي عمل جديد: التزم بالسِمات الموثقة
والتخطيطات الحرفية (row عند elem+8) ورجريشن 23/23 × 6 قبل الرفع.

## نقطة البداية للجلسة الجاية

- **D24 مقفولة:** PeerageService.{h,cpp} (9 دوال: 141551920/1a00/1b00/1b90/1bf0/1c20/1eb0 + 1415549d0/141555070). رجريشن 24/24 × 6.
- **المتبقي في Peerage.dll:** عائلة CMyHeap/السرد (141552040-1415527a0، 141552ed0-141553210) ثم DLL التالي (Syndicate.dll الأضخم).
- نقطة الاستئناف: `bash tools/run_dwave_regression.sh` → ALL-6X-GREEN: 24/24.

## نقطة البداية للجلسة الجاية (بعد D25)

- **D25 مقفولة ومرفوعة:** PeerageSortObj.{h,cpp} (12 دالة: 141552040/180/190/250/2b0/310/780/7a0/ed0/f10/f80/fc0). **Peerage.dll مقفول بالكامل** — رجريشن 25/25 × 6.
- **التالي:** Syndicate.dll (9,862 دالة — الأضخم في الخريطة) بنفس قواعد الحرفية: قراءة → سِمات TBD → اختبار → رجريشن → توثيق → رفع.
- نقطة الاستئناف: `bash tools/run_dwave_regression.sh` يجب أن تطبع ALL-6X-GREEN: 25/25 قبل أي شغل جديد. الديكومبايل في co_repo/Native-Decompiled/Syndicate.dll.decompiled.c.

## نقطة البداية للجلسة الجاية (بعد D26)

- **D26 مقفولة ومرفوعة:** SyndicateModule.{h,cpp} — هيكل الموديول 0x4608 كامل (22 دالة). رجريشن 26/26 × 6.
- **التالي (D27):** عائلة CCrossMeritMgr في co_repo/Native-Decompiled/Syndicate.dll.decompiled.c (سطر ~25507 فأعلى: vftable ثم المُنشئات) أو عائلة CLeague (سطر ~37149). نفس المنهج.
- `bash tools/run_dwave_regression.sh` يجب أن تطبع ALL-6X-GREEN: 26/26.

## نقطة البداية للجلسة الجاية (بعد D27)

- **D27 مقفولة ومرفوعة:** SyndicateCrossMerit.{h,cpp} — قشرة CCrossMeritMgr (7 دوال). رجريشن 27/27 × 6.
- **التالي (D28):** استعلامات CCrossMeritMgr: FUN_14173f680 (الجولة على المفاتيح)، f8e0/f950/f9c0 (سطر 25769+ في الديكومبايل)، أو عائلة الخريطة الداخلية (eb10/cb90/c470 في 25089+).
- `bash tools/run_dwave_regression.sh` يجب أن تطبع ALL-6X-GREEN: 27/27.
- تخطيط العقدة: left@+0, parent@+8, right@+0x10, key@+0x18, _Isnil@+0x61 (الأوراق تشير للرأس sentinel).

## نقطة البداية للجلسة الجاية (بعد D28)

- **D28 مقفولة ومرفوعة:** عائلة CCrossMeritMgr كاملة (13 دالة في 14173f3e0–14173fc80). رجريشن 28/28 × 6.
- **التالي (D29):** عائلة الخريطة الداخلية المشتركة (FUN_14173eb10/cb90/c470/d1e0/e790/f0c0 — سطور 24986-25332 في الديكومبايل) أو عائلة CLeague (سطر ~37149).
- `bash tools/run_dwave_regression.sh` يجب أن تطبع ALL-6X-GREEN: 28/28.
- تخطيط العقدة: left@+0, parent@+8, right@+0x10, key@+0x18, _Isnil@+0x61 (الأوراق تشير للرأس sentinel).

## نقطة البداية للجلسة الجاية (بعد D29)

- **D29 مقفولة ومرفوعة:** SyndicateMapTree.{h,cpp} — نواة الخريطة الحقيقية (8 دوال). رجريشن 29/29 × 6.
- **التالي (D30):** طبقة مكرّرات الملكية فوق النواة (FUN_14173eb10/cb90/c470/c0b0/f0c0/ef80 — سطور 23256/24986/25332) — تكمّل ما زال سِمات في CrossMerit — أو عائلة CLeague (سطر ~37149).
- `bash tools/run_dwave_regression.sh` يجب أن تطبع ALL-6X-GREEN: 29/29.
- عرف الورقة: أولاد عقدة الإدراج يشيرون للـ head sentinel والأب = عقدة الالتصاق (e790 → e1a0).
- قيم العقد: مخزنا heap عند +0x20 و+0x50 (تحررهما e240)؛ اللون +0x60؛ _Isnil +0x61.

## نقطة البداية للجلسة الجاية (بعد D30)

- **D30 مقفولة ومرفوعة:** SyndicateOwnTree.{h,cpp} — عائلة شجرة الملكية 0x28 (8 دوال، من بينها bf40 بدلالة equal_range الموثقة تجريبيًا). رجريشن 30/30 × 6.
- **D31 مقفولة ومرفوعة:** SyndicateEraseLayer.{h,cpp} — طبقة الإزالة/المسح الكاملة
  (b0e0/b140/c0b0/cb90/e350/eb10/ecf0): نواة الخريطة الآن كاملة
  (insert + find + erase + erase-range + clear + dtor حقيقية بالكامل).
  4 أخطاء حساب مؤشرات/نسخ اكتُشفت بالتتبع وصُلحت (وثّقها PORTING_LOG D31)، أهمها:
  والد دخول حلقة التوازن = المُلتقط من unlink/swap وليس plVar9->parent،
  وb140 كانت تقارن عنوان P->right لا قيمته، وecf0 مكرّر البداية {anchor, *head}.
  **رجريشن 36/36 × 6 (d26-d31) + Peerage 9/9 كلها خضراء.**
- **D32 مقفولة ومرفوعة:** SyndicateLeagueTree.{h,cpp} — شجرة أعضاء CLeague كاملة
  (13 دالة، عُقد 0x30: لون@+0x28/isnil@+0x29): تخصيص العقدة/الرأس (746790/746a60)،
  ctor/dtor العضو (c4b0/c530)، find (749fc0)، insert + التوازن (748820)، iter++
  (7447d0)، erase (749c00)، erase-range (74a150)، clear (747270/746650)، الدورانات
  (744560/745ad0). **5 أخطاء نسخ اكتُشفت بالتتبع التجريبي وصُلحت (وثّقها PORTING_LOG D32)**
  أهمها: RotateL كان فيها deref مزدوج (يرفع الحفيد بدل الابن)، وشرط الابن البعيد في
  توازن المسح الأيمن كان يفحص القريب. **رجريشن 96/96 × 6 (d26-d32 + Peerage 9).**
- **ملاحظة -O1:** MeritGrant في CrossMerit (D28) بتنهار عند -O1 (UB كامن قديم، ليس من
  تعديلات D32) — الرجريشن المعتمد بـ -g -O0. لو هتصلّحها: تحقق من قراءات strict-aliasing
  في f600/fa40.
- **قرار المالك (2026-10-25): كبر حجم الدفعة لكل جلسة** — من عائلة واحدة لـ 2-3 عائلات
  لكل جلسة، بشرط ثبات قواعد الحرفية والرجريشن الأخضر قبل كل commit.
- **D33 مقفولة ومرفوعة:** SyndicateLeagueSort.{h,cpp} — عائلة فرز قوائم الأعضاء
  (introsort حقيقي، 9 دوال: cb10/147090/147c80/146f30/146310/147ec0/1463a0/145480/148e30).
  خطآن نسخ اتصلحا (فخ comma في مسير الحارس + وسيط top في الغربلة) — PORTING_LOG D33.
  **رجريشن 102/102 × 6 (d26-d33 + Peerage 9).**
- **D34 مقفولة ومرفوعة:** SyndicateLeagueCmp.{h,cpp} — مخطط المقارِن كامل
  (6 دوال: المفردة b6210 + البحث c8f70/cad00 + المجلِبان 78f270/78f410 +
  المقارِن ba4c0) — **الحلقة مع D33 مغلقة**: الفرز يعمل الآن عبر المقارِن
  الحرفي المربوط بـ g_fnLeagueCmp (اختبار تكامل 45 عضوًا). فخ تراص خانات
  المكرّر في c8f70 موثق (PORTING_LOG D34).
  **رجريشن 108/108 × 6 (d26-d34 + Peerage 9).**
- **التالي (D35):** عائلة كيان العصبة c0c0/c5a0/c6d0/14174a350/14174a300
  (تستدعي 749c00 على الخريطة +0xd8 وتعتمد على 1417d5070/1417d4db0 —
  استقدمهما مع العائلة)، أو شقّ تهيئة مفردة CSyndicateLogic (من يملأ
  الخانة [2] بمدير الأعضاء).
- `bash tools/run_dwave_regression.sh` يجب أن تطبع ALL-6X-GREEN: 30/30
  (وsyndicate d26-d34 + peerage: 108/108 ×6 — سكربت البناء في PORTING_LOG D34).
- عرف الورقة (D29) سارٍ في العائلتين؛ bf40 = equal_range وليست "pair walk" عامة.
