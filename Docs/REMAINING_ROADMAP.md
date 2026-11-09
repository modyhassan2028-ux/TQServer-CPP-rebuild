
## D128 (2026-10-30)
أُغلق هيكل الموديول (CMsg/IModule/CModule). المتبقي في Syndicate: **IProvider**
(0x141834928، 224 فتحة) فقط من الكلاسات الحقيقية؛ الباقي (protobuf/STL:
ArrayInputStream, CopyingStream*, StringOutputStream, MessageLite, Closure,
FatalException, bad_alloc…) مكتبات مغطاة ببدائلها القياسية.

## D129 (2026-10-30) — إقفال كلاسات Syndicate
IProvider مغلق ⇒ لا كلاسات حقيقية متبقية في Syndicate.dll. المرحلة التالية:
الوحدات الصغيرة (Flower, Sponsor, DetainEquip, …) من الـdecompiled + البايناري
الجديد (بدون RTTI ⇒ الاستخراج بأنماط dtor/offset).

## D130 (2026-10-30)
Flower.dll: مغلق 2/5 ملفات (msg/msgflower.cpp، msg/msglog.cpp). المتبقي:
todayflower.cpp (CTodayFlower)، todayflowermgr.cpp (CTodayFlowerMgr)،
flowerservice.cpp (CFlowerService)، module.cpp (flower::CModule 0x140d9bcb8).

## D131 (2026-10-30)
Flower.dll: 3/6 ملفات (msg/msgflower.cpp، msg/msglog.cpp، todayflowermgr.cpp).
المتبقي: todayflower.cpp، module.cpp، flowerservice.cpp.

## D132 (2026-10-30)
Flower.dll: 4/6 ملفات (msg/msgflower، msg/msglog، todayflowermgr، module).
المتبقي: todayflower.cpp، flowerservice.cpp.

## D133 (2026-10-30)
Flower.dll: 5/6 ملفات. المتبقي فقط بقية دوال todayflower.cpp.
بعدها: البايناريهات الأخرى حسب الجرد الكامل في Docs/DLL_FULL_INVENTORY.md
(48 بايناري، 128,853 دالة) — الأولوية للـDLLs متوسطة الحجم المكتملة الأطر
(Family 2,039 · LeaveWord 1,803 · Status 1,559 · Totem 1,152 · Competion 1,088).

## D163 — order of work after the family pass

1. Syndicate.dll families: forwarders done (126), next the destructors, the sized allocators
   (`n*0x28`, `n*0x30`, `n*0x48`) and the `operator delete` thunks, which need those two seams.
2. NpcServer.exe: scaffold is in place (50 paths, `Docs/NPCSERVER_PATHS.md`); port in the author's
   sequence, `npckernel` first because 34 of the 50 paths live there.
3. CQCrossServer.exe (19 paths), then the smaller DLLs as complete units.
4. MsgServer.exe last: 59,977 functions, 6x Syndicate and the largest single binary in the tree.
