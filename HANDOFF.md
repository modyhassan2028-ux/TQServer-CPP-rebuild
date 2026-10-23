# HANDOFF — نقطة تسليم للأجنت التالي (آخر تحديث: 2026-10-23)

> هذا الملف هو نقطة البداية لأي أجنت يكمل الشغل. اقرأ PORTING_LOG.md للمنهجية
> والتاريخ الكامل، وهذا الملف لمعرفة "أنا فين دلوقتي بالظبط".

## القاعدة الحاكمة (لا تُخالف)
- **بورت حرفي فقط** للكود المفكك من MsgServer.exe.decompiled.c (28,042 دالة).
  لا كود مخترع ولا "تحسينات". تعليقات `// ORIGINAL` سطر بسطر.
- **لا final builds ولا zig ولا binaries ولا release uploads** — push كود فقط.
- حدّث PORTING_LOG.md بعد كل وحدة، وحدّث هذا الملف في نهاية كل جلسة.
- الشغل مستمر ذاتيًا بدون طلب إذن (قاعدة المالك). الاختبارات ضد صفوف DB حقيقية.

## البيئة
- المستودع: github.com/modyhassan2028-ux/TQServer-CPP-rebuild (branch main، push مباشر).
- المرجع: ../co_repo/Native-Decompiled/MsgServer.exe.decompiled.c + الباينري
  ../conquer_src/Source/MsgServer.exe (للتحقق بـ objdump).
- قاعدة البيانات: `mariadb -u root cq` (صفوف حقيقية v6159: cq_action 48 ألف صف،
  cq_levexp، cq_rebirth 251 صف، cq_bonus موجودة، cq_itemaddition...).
- بناء اختبار الحوار:
  `g++ -std=c++17 "-D__declspec(x)=" -I. -Iinclude -ICore/CQBase -ICore/DB -ICore/Root -IExe/MsgServer -IExe/NpcServer -IExe/CQCrossServer -Ivendor/lua -IModules/Syndicate -IModules/Trade -Wno-unused-parameter tests/dialog_fidelity_test.cpp tests/stub_cross_client.cpp $(ls Exe/MsgServer/*.cpp | grep -v main.cpp) Exe/MsgServer/LuaScript/LuaVM.cpp Exe/MsgServer/Activity/ActivityManager.cpp Core/CQBase/*.cpp Core/DB/*.cpp Core/Root/*.cpp /tmp/luao/*.o -lm -ldl -lpthread -o /tmp/fidelity_test`
  (objects لوا في /tmp/luao — لو ضاعت: `cd vendor/lua/src && cc -c *.c -o /tmp/luao/xx.o` تقريبًا، انظر PORTING_LOG).
- ملاحظات مالية: credits الشهر على وشك النفاد عادة (لو الرسائل فشلت: انتظر التجديد).

## وين وصلنا — سويتش cq_action (FUN_14012a6e0، 175 case)
مربوطة حرفيًا ومختبرة: 1010/1011/1013-1021 القديمة، 1022 (0x10 gmlog)،
**1025** (0x13 mate)، **1026** (0x14 face gate: lookface/10000==1)،
**1027** (0x15 task)، **1040** (0x22 rebirth)، **1080/1081** (timestamp vars)،
**1086** (0x4c levexp var، objdump-verified)، **1028** (0x16 flag chk/add/clr)،
وأصناف 503-520 القديمة.
**التالية بالترتيب:**
1. **1023 (case 0x11)** = FUN_140172910: مزاعم bonus — يحرس
   `(bonus_list_end-bonus_list_beg)>>2 < 0x28` ثم
   `SELECT * FROM cq_bonus WHERE id_account=%u AND flag=0 LIMIT 1` (الجدول
   موجود في DB). اقرأ باقي الدالة وعملها حرفيًا.
2. **1024 (case 0x12)** = FUN_140173e20: يعتمد على Family.dll
   (CurrentInstanceGet vcall+0x20(8)) — وحدد أولًا الدلالة؛ ممكن يتعمل
   تعويضًا عبر منطق الجيلد عندنا مع توثيق.
3. **1029 (case 0x17)** = "play" wave للعميل: sscanf
   `"%s %s %hu %hu %u"`، باكِت NAMEACT_PLAYER_WAVE (0x201a)، FUN_14037e0a0.
4. بعد الأنواع دي: باقي عائلات السويتش (0x2a-0x4b...) بنفس المنهجية.

## تقنيات مثبتة (مهمة جدًا)
- **الـ exe بلا relocations (.reloc=0)** → الـ vtables مخزنة كـ VA كاملة
  (qword 8 بايت). جدول **CUser الحقيقي عند file offset 0x71d348** (49 خانة):
  slot+0x8=GetId(+0xe80)، +0x50=FUN_1401bf470=[+0xeac]/10000،
  +0xa0=GetExp(+0xed0)، +0x108=GetMetempsychosis(+0xf00).
- تحويل VA→file offset: `off = 0x400 + (VA - 0x140001000)`؛
  ثم `objdump -d --start-address=... --stop-address=...` للتحقق.
- **Ghidra يفقد تفاصيل** (مثل زيادة عداد الحلقة في FUN_140382f00) — عند أي
  شك: objdump مباشرة على الباينري هو المصدر النهائي.
- الـ CGameData records: field(0)=level إلخ حسب ترتيب أعمدة الـ SELECT،
  وقيم الحقول عبر الـ wrapper vcall+0x58 (int64) / +0x10 (اختيار الحقل).

## وضع الأنظمة الكلية
- شغالة ومختبرة: شبكة/لوجين/حركة/خرايط، NPC+حوار، وحوش، أشياء+ترقية،
  سوق لاعبين، جيلد وار+PK bounty، أنشطة، Lua bridge، كروس سيرفر.
- أكبر ناقص في الـ gameplay: **نظام المهارات (Skills)** — لم يبدأ حرفيًا.
- تقدير الوضع الكامل (للسؤال المتكرر): حوالي 30-40% من دوال السيرفر
  الوظيفية معمولة (نصفها حرفي بالكامل) من أصل 28,042 دالة مفككة.
