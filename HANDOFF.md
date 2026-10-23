# HANDOFF — نقطة تسليم للأجنت التالي (آخر تحديث: 2026-10-23، نهاية جلسة الوحدات 7-9)

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

## المتبقي بالترتيب (ابدأ من 1)
1. **FUN_140145f60 — محرك منح الـ bonus (PORT-PENDING الوحيد المفتوح).**
   أولوية قصوى: غلاف 1023 مبورت لكن المحرك الداخلي (15KB + ~40 دالة داخلية)
   لا. وحدة عميقة: اقرأها كاملة من MsgServer.exe.decompiled.c، تتبّع
   FUN_140146a10/FUN_1401184a0/FUN_14013b950... وبوّرتها 1:1، ثم فعّل
   المطالبة في 1023 (flag=1 + time + المنح + سطر gmlog/bonus).
2. **عائلات السويتش الأكبر** (0x2a-0x4b...) بنفس المنهجية سطر بسطر
   مع اختبارات ضد صفوف cq_action حقيقية.
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
