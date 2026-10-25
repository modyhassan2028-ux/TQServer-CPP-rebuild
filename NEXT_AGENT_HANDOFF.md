
## تحديث 25/10 — الوحدات M62-M66 (سلسلة الخريطة مكتملة 100%)
- الخريطة (map container) اتقفلت بالكامل حرفياً:
  المُخصّص FUN_140010280/14000f740 (عقدة 0x78،
  color@+0x74، الست inline عند +0x34 غير محاذى
  ببايتات خام + accessor)، النسخة العميقة
  FUN_14000af60/14000bf20 (اللون منسوخ من +0x1c —
  بلا إعادة توازن)، مشية إعادة توازن الإدراج (ذيل
  FUN_140010600: recolor/تسلق/LR-LL/RL-RR)، ومشية
  interior-hint في FUN_140010ec0 (السلف + التحقق +
  قرار الربط). **صفر TBD متبقي في الخريطة**
- حارس الخريطة أسود عند +0x74 (تم اكتشافه عبر
  انهيار غير حتمي تتبع بـ gdb، والسبب النهائي كان
  عدّاد غير مهيأ في اختبار M63 اعترضته بوابة
  max_size الحرفية نفسها)
- الاختبارات: static_asserts على كل الأوفستات
  (0x18/0x1c/0x74/0x75/0x78)، M64-SUBSET-COPY-OK،
  M65-MAP-REBALANCE-OK (10/10)، M66-INTERIOR-HINT-OK
  (8/8). العيلة (M43-M66) خضرا
- الخطوة التالية المرشحة: دوال استهلاك الحاويات
  (بلوك 0x1777 وما بعده) — كل مكونات الخريطة/الست
  جاهزة الآن

# 🔵 NEXT AGENT HANDOFF — ابدأ من هنا
> آخر تحديث: 2026-10-25 10:50 (NpcServer 1-47 كاملة + MsgServer M1-**M54** — **عيلة القبض والشجرة الحمراء-السوداء للحاوية مقفولة بالكامل**: M43 مطبّع الزمن، M44 معالِج القبض، M45+M46 OfflineCheatingGotoJail أونلاين/أوفلاين، M47+M48 ctor الـ CMapGroupKernel والحارسات، M49-M54 الحاوية RB كاملة: insert/erase/splice/rotations/recolor/عقد الرجوع)، بعده **M55 = دوال mapgroupkernel الخارجية اللي بتستهلك الحاويات** (إضافة غشاش لقائمة السجن فعلياً، دوال النطاق/البث زي FUN_1400ef8d0) أو دوال الـ dlg المساعدة (FUN_14001f070/FUN_140021bd0/FUN_14001e540)
> هذا الملف هو نقطة البداية لأي agent هيكمل الشغل. اقرأه كله قبل أي سطر كود.

---

## 1) المشروع والقواعد الصارمة

**الهدف:** نقل `NpcServer.exe` (Conquer Online v6159) إلى C++ بنسبة 100% مطابقة للأصل.

**المسارات والروابط الأساسية:**
- **الريبو اللي شغالين عليه:** محلياً `/app/co_repo` — وعلى GitHub:
  `https://github.com/modyhassan2028-ux/TQServer-CPP-rebuild`
  (branch `main`، remote `origin` مظبوط بالفعل للـ push)
- **الريبو المفكوك (الـ decompile المرجعي):**
  `/app/co_decomp/Native-Decompiled/NpcServer.exe.decompiled.c`
  (ونفس المجلد فيه كل الـ DLLs المفكوكة + ملفات `.index.tsv` للفهرسة:
  `/app/co_decomp/Native-Decompiled/`)
- **الـ binary الأصلي (الملفات الأساسية اللي اتنقلت من المصدر):**
  `/app/co_decomp/orig_binaries/Source/NpcServer.exe`
  (نفس المجلد فيه MsgServer.exe و CQCrossServer.exe و RevampedLoader.exe
  وكل ملفات الـ config: `/app/co_decomp/orig_binaries/Source/`)
  (وفوق فيه `/app/co_decomp/orig_binaries/cq.sql.gz` و `/app/co_decomp/orig_binaries/patch/`)
- الـ binary بيستخدم لاستخراج الجداول الثابتة (راجع الوحدة 30 في PORTING_LOG لطريقة الاستخراج بـ python struct + PE sections)
- ملفات الـ NpcServer المنقولة: `Exe/NpcServer/` — الاختبارات: `tests/`

**قواعد غير قابلة للنقاش (standing instructions من مالك المشروع):**
1. **ممنوع كود متخمَّل (guessed code)** — كل سطر من `NpcServer.exe.decompiled.c` حرفياً.
2. وثّق كل عنوان دالة و offset وسلسلة لوج حرفية في التعليقات.
3. **كل الاختبارات لازم تمر قبل أي commit/push.**
4. حدّث `HANDOFF.md` و `PORTING_LOG.md` مع كل وحدة مكتملة.
5. الريبو يفضل متزامن مع GitHub بعد كل وحدة.
6. بنفس الأسماء المكتشفة بالـ reverse engineering (مثل `CNpc::CheckTransform`).
7. **الغرائب الحرفية في الأصل تُنفَّذ كما هي ويُوثَّق أنها حرفية — لا "تصلح" شيئاً أبداً.** (أمثلة منفذة: تسريب low-byte في `FUN_14005b2d0`، الكود الميت `find(0)` في `FUN_14005bc80`، النداء على pathfinder null بدون else في `FUN_1400580e0`)
8. شغل مستمر وذاتي: سلسلة وحدات متتالية بدون انتظار إذن — المستخدم بيقول "كمل" فقط.

---

## 2) الوضع الحالي

- **الوحدات 1–47 مكتملة.** آخر دفعة: 35 (تحقيق آلة الحالات — اتقفل بالدليل: الحالات 2-5 dead في الأصل، الموزّع 1/6/7/8 فقط، مصادر 6 و8 موثقة) + 36 (نواة kernel TqKernel: بوابات المعرّفات + الإكسسورات + 27a40 + 38100 + الإرسال 1c5f0).
- **الرجريشن 34/34 أخضر** + سموك `main` شغال (login → generator → spawn).
- **MsgServer (المرحلة الحالية):** M1-M25 مكتملة، 21 ملف اختبار msg في `tests/`، الرجريجن الكلي 66/66. تفاصيل كل وحدة في القسم (د) أدناه وفي PORTING_LOG.md.
- 42 ملف اختبار npc في `tests/` + طبقة `Win/` (واجهة الأصل الحقيقية)، كل واحد بيطبع سطر `_OK` واحد يحتوي توثيق كامل. (npc_ops_205_207_208 وnpc_record_201 اختبارات MsgServer بتتصرف مع سورسات تانية — مش في عدّ الرجريشن).

### المكتمل كأجسام حقيقية:
- **النواة:** main.cpp الأصلي (login `0x3ade68b1`، `NPC Server KernelThread` 1Hz)، NpcAssembly، CNpcWorld + timer، CAIStrategyMgr::Process (`1400489b0`).
- **الرسائل:** CMsgAiNpcInfo (ctor/Create/CreateFromBuf/GetBuf/Process)، رسالة المشي `FUN_1400597f0` (623e0/62530/1c5f0/62430)، رسالة الوثبة (62030/620c0).
- **المولّد:** CNpcGenerator::Generator (`14005fc90`)، `14005f7e0`، `14005fb30`، Process (`140060b00`، vftable 21 entries @ `0x1400c7fc8`).
- **التحوّل والموت:** CNpc::CheckTransform/Transform، CNpc::Close (`14005f020`)، مسار الموت كامل.
- **آلة الحالات:** State 6 (`14005d140`)، State 8 (`14005d330`)، State 7 (`14005d550`)، State 1 (`14005e900`).
- **عيلة الحركة/الهجوم (كاملة!):** `FUN_140058260` (اختيار اتجاه الهجوم)، `FUN_1400588b0` (اتجاه المطاردة)، `FUN_140058b80` (موقع attach)، `FUN_14005b9e0` (خطوة الهجوم/الوثب — **انتبه: الاتجاه المفحوص من vt+0x18 للـ sub مش الممرر، وآخر وسيط 0 مش 0x1a**)، `FUN_14005b2d0` (معالج العلوق +0x11c/+0x120/+0x124)، `FUN_140059770` (بوابة الحرية: +0x28≠2 وبتات 3/4/0xb من row(0x15))، `FUN_1400597f0` (رسالة المشي، معرّف 0x89)، `FUN_1400580e0` (طلب المسار — **النداء على pf null بيستمر بدون else**)، `FUN_14005c960` (خطوة المشي)، `FUN_140059f40` (التليبورت).
- **البحث عن الهدف:** `FUN_14005bc80` (أكبر دالة، 294 سطر) في `NpcTargetSearch.{h,cpp}` — مسح حلقات شبكة 0x12، ممرّان (678b0/678a0)، صيحات `STR_GUARD_CALL_s`/`STR_PPKER_CALL_s`، حرفياً `npc.cpp` سطور 0x68f/0x6b2.
- **فحوص الخلية:** `FUN_14004b140` (المانعات)، `FUN_14004cc70` (خالية للوقوف — إرجاع 0xffffff00)، `FUN_14004bff0` (فحص المشي الكامل — النوع 3-4 يفحص الخلايا البعيدة فقط cheb>half) في `NpcCellCheck.{h,cpp}`. جداول `0x7428/0x7448` مستخرجة من الـ binary ومطابقة لـ `0x89d0/0x89f0`.
- الـ user tick، الـ wander، قائمة الخطوات، المعالجة بالـ vtable (+0x54 type مش map id في مسار المولّد).

---

## 3) نمط الشغل الثابت (اتبع نفس النمط بالظبط)

كل وحدة:
1. اقرأ الدالة من `NpcServer.exe.decompiled.c` بـ `awk '/Function: FUN_xxx @/,/^\}$/'` — كاملة مش جزء.
2. انتبه لغرائب Ghidra: `(longlong)param_1 + N` = offset بايت، أما `param_1 + N` بدون cast = **N×8 بايت**! والـ `return uVar & 0xff..00` معناها low byte صفر = false، و`CONCAT71(x>>8, 1)` = إرجاع 1.
3. الجداول الثابتة تُستخرج من الـ binary نفسه (python struct + PE sections — راجع PORTING_LOG الوحدة 30) مش من التخمين.
4. نفّذ في ملف `.cpp/.h` بتعليقات توثّق الأصل. الدوال التابعة الصغيرة تتحول **seams** في struct بيانات (`std::function`) لو لسه مش منفذة — ولما تتنفذ بعدين تتربط.
5. اكتب اختبار `tests/npc_xxx_test.cpp` يطبع سطر `NPC_XXX_OK: ...` بكل التفاصيل الحرفية. الحالات اللي تفشل بتكشف غلطك في فهم الـ decompile — راجع الأصل تاني مش الاختبار.
6. الرجريشن الكامل: كل الاختبارات (28 حالياً) + سموك `main`. القائمة الكاملة للأوامر موجودة في PORTING_LOG أو انسخها من آخر جلسة (كل test مع مصدره).
7. حدّث `HANDOFF.md` (القسم 0 — أول ما في الملف) و `PORTING_LOG.md` (إضافة بالأسفل).
8. commit برسالة تفصيلية + `git push origin main`.
9. كمّل الوحدة اللي بعدها مباشرة بدون انتظار.

---

## 4) المتبقي (مرتّب بالأولوية)

### أ) ~~دوال مرجعية كانت seams~~ — **كلها خلصت في الوحدات 31-34:**
1. ~~FUN_140059dc0 / 59710 / 57c50~~ — أجسام حقيقية (وحدة 31) **+ الربط تم** (`CNpcBindPkFamily` في NpcTargetSearch).
2. ~~`FUN_14005ab20`~~ — جسم حقيقي `CNpcPkMask5ab20` (وحدة 32) + مربوط بالرابط.
3. ~~`FUN_140049310`~~ — الجسم الموحّد `CNpcPosValid49310` في NpcCellCheck؛ `NpcTransform::PosValid` بيهوجّه له (وحدة 32).
4. ~~`FUN_14004ab40`~~ — جسم حقيقي `CNpcInBounds4ab40` (وحدة 32).
5. ~~`FUN_1400586b0`~~ — جسم حقيقي `CNpcShout586b0` (وحدة 33). **ملاحظة:** seam الـ `m_fnShout` في `CNpcTargetSearchData` لسه موجود — الربط الكامل محتاج جدول النصوص theInstance()->get("STR_..._s") (جزء من التكامل الكبير).
6. ~~`FUN_14005b760`~~ — جسم حقيقي `CNpcPursuit5b760` (وحدة 34) + مربوط بالرابط (نداء bc80: 5b760(npc, 0)).

### ب) التكامل الكبير (المتبقي الفعلي):
7. **ربط الـ seams بأصحابها الحقيقيين — قريب من الإغلاق:** الوحدات 38-46 عملت طبقة الربط كاملة: NpcMapBinder (الخريطة/الشبكة/الصيحة/حاوية الـ id/سجلات cq_monstertype/فحص الدور 4ad20) + بانل الإحصائيات (44) + **واجهة Win32 طبق الأصل بقالب RT_DIALOG الحقيقي مزروع بالبايت (45)** + **إغلاق TBD مساحة مفاتيح الـ mgr: الوحوش [400001,500000] بـ ring FIFO حرفي (2a690)، pets [700001,800000)، players [1e6,...]، بوابة الترانسفورم [400001,700000) (46)**. المتبقي: (د) بناء ويندوز فعلي بالـ build_win.bat للتأكد البصري من الشاشة — الـ smoke المطوّل (ب) اكتمل بالوحدة 47 (npc_long_smoke: 300 ثانية افتراضية، 3 مولدات، caps 3/5/4، عدادات 38090، اللوحة الحرفية، ring recycle، ذيل مستقر).
8. ~~التحقق من الحالات الناقصة في آلة الحالات~~ — **اتقفل في الوحدة 35 بالدليل:** الموزّع `FUN_14005f3b0` بيعالج 1/6/7/8 فقط (لوب 10 مرات بيعيد قراءة +0x18)، والحالات 2-5 **مش بتتكتب أصلًا** في كود NpcServer. البورت الحالي مطابق — لا تعديل.

### ج) تحقق نهائي:
9. ~~سموك أطول لـ `main`~~ — **اكتمل (الوحدة 47):** npc_long_smoke: 300 ثانية افتراضية، 3 مولدات caps 3/5/4، عدادات 38090، اللوحة الحرفية، ring recycle، ذيل مستقر بدون تسريبات.
10. مراجعة `HANDOFF.md` قسم "المتبقي" وتحديثه.

### د) MsgServer — المرحلة الجديدة (البورت الحرفي):
- **الوحدة M1 مكتملة:** FUN_14045bc00 + FUN_14045b990 (لوجين NpcServer من جهة MsgServer): المفاتيح 0x3ade68b1/b2، كلماتا السر الحرفيتان "NpcServer Tqdig"/"skl8934##VJICW " (المسافة حرفية)، المصافحة 0xe/0x2720+0x2722/0xea65، سجل SYSTEM/ALLUSERS/ANSWER_OK بالواصف المزروع، والـ keepalive 0x9c41 بغرابة strlen+1 (الـ NUL بيركب). ملفات: Exe/MsgServer/Port/MsgNpcLogin.{h,cpp} + tests/msg_login_test.cpp.
- **الوحدة M2 مكتملة:** عيلة CMsgTalk الحقيقية FUN_14015b240/14015b300/14015b2c0 (ctor: +0x428=this+0x10 + SetBuf(+0x2d,0x3e1)؛ Create ببوابات الأطوال len<0x10/len<0x100 — الـ idiom بيرجع len نفسه مش len-1 — والترتيب الحرفي name,to,TEXT,from + +8=0x3ec + +0xc=GetSize+0x1f؛ dtor). **تصحيح M1 موثق:** الحقول اللي كانت "واصف مزروع" هي وسائط الستاك الصادرة لـ Create (null text، 0xffffff، 0x835، 0،0،0،1). الـ CStringPacker نفسه DLL-import (seams). ملفات: Exe/MsgServer/Port/MsgTalkRecord.{h,cpp}.
- **التالي (M5+):** ~~مستلم الرسائل حول FUN_140008520~~ (خلصت في M4: سجل slots النواة 0x850 بالبوابة الحرفية 0xd — أول 14 مرفوضين — + النسخة العضوية 140006fe0)، والبوت الحرفي (CSocketKernel::Create بتاع MsgServer — "libevent method" عند السطر 988332)، ~~وبورت كائن الاتصال (+0x410 group id → ربط الـ m_fnGetKernel بالسجل)~~ (خلص في M5)، ~~البوت الحرفي CSocketKernel::Create~~ (خلص في M6: FUN_1404fc940 كاملة بسلسلة libevent/MPO/ini/listeners/clients/thread/QueryConfig بمسار الـ PDB الحرفي)، ~~وعيلة FUN_1402b5600/1402b55f0~~ (خلصت في M3: 2ba1c0 ctor الـ CNetMsg بالتنظيف المزدوج الحرفي + 2b5600 + 2b55f0 dtor chain). القاعدة نفسها: قراءة الدالة كاملة من MsgServer.exe.decompiled.c قبل أي سطر.

### حالة MsgServer — المكتمل (M7-M25، كل وحدة باختبار أخضر ومرفوعة):
- **M7-M13 (عيلة libevent والـ crypto):** عيلات عمال libevent (1404f72a0/8110)، جدول MD5 القياسي (140507260 بمعاملات RFC 1321 كاملة)، خدمة MD5 (Update/Finalize عبر vt+8/vt+0x10، digest عند +0x58)، مولّد key.dat (MD5+DES بذر 0x12)، بنّاء التوكن (140507ca0: توكن 32 حرف + توقيع MD5 مزدوج)، محمّل dh.pem (12 مؤشر BIGNUM عند 0x140970xxx)، محلّل التاريخ (strptime hand-rolled)، خام التاريخ الحرفي.
- **M14-M17:** تبادل مفاتيح CAST (DH ثم MD5 مزدوج على المفتاح المتفق)، تشفير الجلسة، المُرسِل المشفّر، الـ server stamp (سلاسل DAT_1409766dc).
- **M18-M21:** مستلم الرسائل بعد فك التشفير، المُرسِل (بمسارات البث والبث المصقول والـ raw والإفراج).
- **M22:** محمّل مفتاح الأداة FUN_1405087d0 (ini\\tool.ini: كل بايت رابع XOR 0x12، أو ريجستري HKCU Software\\microsoft\\vis قيمة "key").
- **M23:** عيلة بوابات الحماية على DAT_140976718: الستُتِرات |=4، بوابة التاريخ (خنق 600s، نافذة 0x794a00) → بتة 0x10، البوابة الرئيسية FUN_140508eb0 برجع حرفي من الـ asm (thresh&~0xFF / (f&~0xFF)|1 / f&~0xFF — الفاشلة 0x16 مش 0x1c)، بصمة MAC عبر القناة 1، shell.dat عبر القناة 0.
- **M24:** محلّل تصدير البلجن FUN_140509380 (GetProcAddress داخلي: desc علم@0/بيس@0x10/هيدر@0x20، export dir عند هيدر+0x88/0x8c، جداول PE قياسية، فحص forwarder، غرركة الـ ordinal الحرفية (0xffff-ordBase)&ordinal) + dispatch نواة العالم FUN_140508f10 (CreateMapGroup/CreateWorldKernel/CreateMapGroupDefaultData على DAT_1409766a0) + مصنع القنوات FUN_140509280 (0→DES 0x890، 1→مبلّغ 0x60، 2→+vftable MD5، 3→المؤشر يظل كما هو).
- **M25:** ctor الـ MD5 checksum FUN_14050a570 (حالة MD5 القياسية A/B/C/D عند +0x50..0x5c).
- **M26:** تحقق الـ PE FUN_140509760 + الحجم الافتراضي FUN_140509820 (e_lfanew عند +0x3c!) في MsgPeValidate.
- **M27:** محمّل الـ PE اليدوي كامل FUN_1405098b0/4d0/5a0/990 في MsgPeLoader: نسخ الهيدرات والسكاشن وإعادة ربط الديسكربتور على النسخة المُعيّنة، relocs DIR64 عند NT+0xb0 (الدالتا base-ImageBase@NT+0x30)، imports عند NT+0x90 (GetModuleHandleA/GetProcAddress + FirstThunk)، والموزّع r8-size مع VirtualAlloc 0x3000/0x40 وentry(base,1) وفشل بينظف بentry(base,0,0)+VirtualFree.
- **M28:** مثبّت البلجن FUN_140508f60 + forwarder الـ CreateNewMapData FUN_1405090c0 في MsgPluginInstall: حراس 8-محاذى، مفتاح DES الحرفي "*J_@'n 3" عبر القناة 0، تحميلات msvcp90/msvcr90، نداء محمّل M27، وبوابة التصديرات الأربعة.
- **M29:** عيلة كائن CMD5Checksum في MsgMd5Object (FUN_140509110/120/140/150/160/170/180/240/1b0/1f0) + الجدولان الحقيقيان من البيناري (0x14079b8b8/0x14079b928)؛ تحديث M25 للعنوان الحقيقي.
- **M30:** عيلة الـ Checksum Update في MsgMd5Checksum (FUN_14050a4a0/a5d0/a910/aa70/a7f0): MD5Update/Finalize على ctx خاص (buf@+8/count@+0x48/A@+0x50)، Finalize بسلسلة 32 hex صغيرة، السولت الحرفي A3 AC A1 A3 eur506,j89jfmncvl للـ Checksum والـ Standard بدون سولت، والاتنان في المكان (in-place)؛ كل الفيلكتورات من python hashlib.
- **M31:** برولوج WM_TIMER في MsgTimerProc (FUN_140024860 سطور 29534-29641): فلاج مرة واحدة لحدث shutdown (WaitForSingleObject 20ms) + نص "shutdown" وعدّ 50 ثانية، ثم "kickoutall" بمهلة 10 ثوانٍ، مع تصفير → state 3 + Refresh. سلسلة إنشاء خيوط timer 1 = seam (m_fnRest) للـ M32.
- **M32:** سلسلة إنشاء الخيوط في MsgInitChain (FUN_140024860 سطور 29643-29890): state 0→4/1→3، 14 خيط بالترتيب الحرفي (178→180→1c0→1e0→الخرائط→1c8→1b8→[1d8]→1e8→[228]/[238]/[230]) مع AddThreadHandle بعد كل تحقق وموجة Resume مرتّبة، state 2 + مؤقتات 600/300 ثانية بعد البوست-إينت. الفشل في أي خطوة يوقف السلسلة (state تفضل 3).
- **M33:** شلال الإغلاق في MsgKernelClose (FUN_140024860 state 3، سطور ~30057-30404): موجة CloseThread أولى بالترتيب والمه Literal (2000/3000/4000/10000/120000/3000/60000/8000/4000) ثم موجة الإغلاق+التدمير+التحديث بجدول الرسائل الحرفي (Cross/World/Chat/Auction/AsyncDB/Log + لوب الخرائط 300000) مع SetLogThreadStatus(0) قبل خيط اللوج، والذيل → state 4.
- **M34:** بلوك الأداء والإحصائيات في MsgPerfStats (FUN_140024860 state 2، سطور ~29890-30056): فترات 600/300 ثانية، تصفير 8+12 عداد بـ LOCK/UNLOCK، البانر "-"×47، فورمات إحصائيات السوكيتات الحرفي، قاعدة انحراف CCU (نافذة signed ±10 + العبور الصفري، وFromOSCCU/ToOSCCU بـ abs)، فحص انسداد الأنبوب (>10000 و%1000==0)، وrequest الريستارت → state 3.
- **M35:** state 4 في MsgState4 (سطور ~30387-30410): KillTimer(1) + f070 + Sleep(3000) + إعادة التشغيل الشرطية بنفس الـ EXE + التنظيف + OnOK.
- **M36:** فرع timer-2 كاملًا في MsgAuthTimer (سطور ~30413-30533): سلسلة أسماء الـ authserver ببوابات الاتصال، مسار الفقد (فحص DEADLOOP + Ordinal_12 + باقت "IP:%s VERSION:%s" + لوج faild بالإملاء الحرفي)، تنزيل البلجن بالتقطيع (الحجم في أول 4 بايت من القطعة الأولى + استهلاك 4، memmove تجميعي، بوابة الاكتمال)، FUN_140508f60 بالمسار الحرفي عند الفشل + SetTimer(1,200) عند النجاح، ومهلة المصادقة. **FUN_140024860 (CMsgServerDlg::OnTimer) اكتملت بجميع فروعها.**
- **M41:** سلسلة التشفير الموصولة: المصنع (M38) بيوصل DES الحقيقي (M40) وMD5 (M30) افتراضيًا عبر pImpl، والاختبار msg_crypto_chain_test بيشغّل المسارات الأربعة الحقيقية (vt interface ضد متجهات M40، البلجن بفك الصورة بمفتاح '*J_@'n 3'، key.dat بتبديل نصفي+صفر الذيل، shell.dat بتبديل نصلي بدون setkey، بصمة MAC بالسولت). الاكتشاف: التهيئة الصفرية = نمذجة fresh-heap، ومسارات بدون setkey = تبديل نصفي للبلوكات.
- **M40:** كائن DES الكامل (MsgDes): تخطيط الـ vftable مستخرج من .rdata (delete/ECB-enc/ECB-dec/setkey/stubs)، بنية descore (8 SP tables + 16×8 schedule بترتيب 6-bits/byte)، الـ S-boxes **معدّلة عن القياسي** (variant مخصص - مش DES قياسي!)، الجولات الـ unswapped مع الـ IP-by-load والـ FP-by-store الضمني، فك التشفير بالأدوار المعاكسة، الـ ECB بـ padding الأصفار، وثلاث quirks حرفية: decrypt(غير مضاعف 8) بيلف للأبد، الـ ECB encrypt بيستاهل len<1 فقط، وفرع schedule-الخام كود ميت.
- **M39:** عيلة serverlock في MsgServerLock: FUN_140508440 (iphlpapi/GetAdaptersInfo 0x2c00، تخطي 192.168.39/181، strcmp مع Ordinal_12، لوجات IF_OK/hModule وASSERT بالمسار الحرفي، والمشي مستمر بعد فشل الاستعلام حرفيًا) + FUN_14001e3d0 (جدول dwordين 0x060817ac/0x090b17ac من .data) + فرع OnInitDialog (192.168.9.138 في عناوين الـ authserver + منفذ 0x268d + لوج "This is a inner server.").
- **M38:** مصنع مزودات التشفير FUN_140509280 في MsgCryptoFactory: 0=DES(0x890)، 1=CMD5Checksum (السولت)، 2=Standard، 3=الـ slot يفضل UNTOUCHED (حرفي)، أكبر→NULL. **إجابة سؤال السولت (متبقي M23):** السولت مخصوص لمسار بصمة MAC (القناة 1) فقط — MD5(input+السولت)؛ وkey.dat/shell.dat/البلجن بيستخدموا الـ DES (vt+8 تشفير/vt+0x10 فك/vt+0x18 مفتاح "*J_@'n 3").
- **M37:** التجميع في MsgOnTimer: البرولوج (M31) على كل tick + حارس DAT_14097593c + توزيع +0x1fc (0/1→M32، 2→M34، 3→M33، 4→M35، غير معروف→ERROR) + timer 2→M36 + بقية المعرفات→CWnd::Default. مصدر الحقيقة الوحيد لـ +0x1fc هو prologue.nState. MsgOnTimerResetBoot ينزّل الحارس بعد نجاح استيراد البلجن لبوت جديد. اختبار دورة حياة كامل (بوت→عمل→restart→إغلاق→خروج + auth→بلجن→بوت + shutdown→kickout→إغلاق بنفس الـ tick).

### التالي (بالترتيب):
1. **M42:** خيط Cheating Program Monitor (~سطر 3151 في MsgServerDlg OnTimer): DES_string_to_key("df29duw", ...) + DES_set_key_checked + DES_cfb64_encrypt — واردات libeay32 (OpenSSL) — موديول محتمل جديد؛ وكمان FUN_14001f070 وFUN_140021bd0 وFUN_14001e540 (دوال الـ dlg المساعدة) لو ظهروا في مسار. ملحوظة: 14050ac50 (دمج جدولين 128-بايت) ليس له منادون في الديكومبايل — كود ميت على الأغلب.
2. **M42:** خيط Cheating Program Monitor (~سطر 3151): DES_string_to_key("df29duw", ...) + DES_set_key_checked — الواردات من libeay32 (OpenSSL الأصلي!) للـ cfb — موديول محتمل جديد.
3. لاحقًا: موديولات دخول MsgServer المتبقية من M1-M22 إن وجدت، ثم تجميع الـ smoke المطول.
2. **M34:** وصل m_fnRest في MsgTimerProc بالـ MsgTimerInitChain الحقيقي (الخياطات الافتراضية) وأزود حقول الـ dlg-state المشتركة.
3. **M35:** مين بيستخدم vt+8 بتوع الجدولين؟ (فهم معنى السولت).
4. بعدها: عيلة 140508xxx المتبقية (معالجات الرسائل بعد فك التشفير).

## 5) وحدة M42 (الجديدة — اترفعت على GitHub)

**M42 = Cheating Program Monitor كاملة** (`Exe/MsgServer/Port/MsgStdDes.{h,cpp}` + `MsgCheatMonitor.{h,cpp}` + `tests/msg_cheat_monitor_test.cpp`):

- **MsgStdDes:** محرك DES القياسي (FIPS) — محاكاة libeay32 اللي بيستوردها المونيتور (مستقلة تماماً عن descore بتاع M40). كل قطعة متحققة آلياً:
  - البلوك مقابل OpenSSL (legacy provider) + pycryptodome: 500/500 عشوائي + المتجهات الكلاسيكية (3fa40e8a984d4815 / 0000000000000000 / d5d44ff720683d0d)
  - `DES_string_to_key("df29duw")` (كلمة السر الحرفية في FUN_140003dc0) = **382c5b389ebc1916** — طبق str2key.c حرفياً (fold<<1، parity table، cbc_cksum بـ ivec=key مع zero-pad للذيل، parity تاني)
  - `DES_cfb64_encrypt` مطابق لـ `openssl enc -des-cfb` بايت-بايت (48 بايت + 7 بايت جزئي) — feedback بتاع فك التشفير = بايت السيفertext نفسه، و`num` (0..7) بيكمل عبر النداءات
- **MsgCheatMonitor:** FUN_140001c70 (wrapper فك التشفير بحوارسه: null → log "Cheating Program Monitor invalid msg"، len في 1..0x30، num null) + FUN_140002510 (demux: 1001 تكرار، النوع u16 عند buf+4؛ النوع 0 محتاج 0x30 → FUN_140001900 (النسخة بقناع البايت 47 + سبب STR_GENERAL_BOT_SIN لو buf[0xf]==0)، الأنواع 1..4 محتاجة 0xf → FUN_140001a50 (struct 0x30: u32 id + u16 type + اسم 9 بايت عند +6 + سبب عند +0xf: GENERAL/KEY/SERIOUS_BOT_SIN أو HACK_TOOL_SIN)، أي نوع تاني = توقف الحلقة) + الخيط FUN_140003dc0 كآلة حالة (Init/Tick/Stop عبر seams): ini "CheatingMonitor" (ListenPort افتراضي 0x23be، IPNum بحد 20 مع لوج "astrict ip number overrun max ip number!")، 64 سلوث (السلوث 0 = الـ listen pseudo-client)، select بـ 500usec، قبول + رفض "lawless ip address %s!"، recv → فك تشفير في الموضع → demux، مسار الخروج بلوجين client(%s : %u) logout / one client logout، والفشل select → إيقاف. ملاحظة: **ivec/num بتوع CFB مشتركين على مستوى الخيط كله** (الحالة منقولة عبر النداءات) — حرفياً كما في الأصل.
- الاختبار `tests/msg_cheat_monitor_test.cpp` أخضر بالكامل، ومفيش **أي تعديل** على ملفات موجودة (وحدة إضافة صافية) — فالرجريجن 82/82 القديم في أمان.
- **التالي (M43):** دوال MsgServer اللي بعد المونيتور في سلسلة الـ recv، أو أي وحدة تالية من PORTING_LOG. فيه ملاحظة إن `DES_set_key_checked` بيرجع نتيجة فحص الـ parity/weak-key **والبيناري بيتجاهلها حرفياً** — منفذة كده.

## 6) وحدة M43 (الجديدة — مُطبّع زمن الحدث)

**M43 = FUN_140001ce0** (`Exe/MsgServer/Port/MsgCheatTime.{h,cpp}` + `tests/msg_cheat_time_test.cpp`):

- الدالة اللي بيناديها كولرَي الـ msgserverdlg (سطر 198639 و198797) لتطبيع زمن الحدث: مصدر واحد "YYMMDDHH" بيتقسم u16 لأربع خانات YY/MM/DD/HH (الكولر بيجيب بافرات مُصفّرة)
- الحارسان: null → 0x227، نص فاضي → 0x228 — **quirk حرفي:** أي نص غير فاضي بيعدي و8 بايت بتتقرأ برضه (الأصل متكئ على بافر الكولر)
- لو Bias != -0x1e0 (GMT+8): mktime → t2 = t - 0x7080 - Bias×60 → localtime (فشل → 0x244) → إعادة بـ itoa **من غير حشو** ("9" مش "09")
- الخياطات (m_fnBias/m_fnMktime/m_fnLocaltime) قابلة للحقن للاختبار، والافتراضي وقت المضيف
- **MSG_CHEAT_TIME_OK** من أول تشغيلة؛ وحدة إضافة صافية (صفر تعديلات) + rerun عيلة المونيتور أخضر
- **التالي (M44):** الدوال المحيطة عند الكولرَي (198639/198797) — سياق الـ msgserverdlg اللي بيستهلك المُطبّع، أو أي وحدة تالية من PORTING_LOG

## 7) وحدة M44 (الجديدة — مُعالِج القبض)

**M44 = مُعالِج القبض بتاع المونيتور** (`Exe/MsgServer/Port/MsgArrestHandler.{h,cpp}` + `tests/msg_arrest_test.cpp`)، دوال mapgroupkernel.cpp عند الكولرَي:

- المسار الكامل: الحارسان (0x2e0/0x2e7) + رسالة القبض (0x2ec) + توزيع الساعات → STR_USE_NONLICET_TOOLS1..4 + **gmlog/cheater الحرفي** ("Cheater found.  UserID:[%u], cheat type:[%s], subtype:[%s]" مع _TYPE_CHEATING_SYSTEM)
- **quirk حرفي:** فشل ExtractLocalTime (0x2f9) مش بيرجّع — بيكمل
- الأونلاين: vcall+0x98 → لو الخريطة != **0x1772 (سجن الغش 6002)** → إرسال النص + FUN_1401ca920(obj, 0x1772, STR_GOTO_CHEATJAIL, 1)
- الأوفلاين: SQL الحرفي "SELECT  id, recordmap_id FROM cq_user WHERE id = %u LIMIT 1" + المسارات 0x339 (فشل استعلام) / 0x33f WARNING (لا صفوف) / 0x350 (أصلًا في السجن) / 0x358 (ماب مفقود)
- **TBD موثق:** ذيل إحداثيات البوابة بعد جلب ماب 6002 (map+0x58 vcall+0x10(0xb)) — جزئي الاستخراج
- **MSG_ARREST_OK** (8 حالات)؛ إضافة صافية + rerun العيلة أخضر
- **التالي (M45):** ذيل بوابة الأوفلاين (سطر ~198790 وما بعده)، أو FUN_1400ef850 (الوظيفة الشقيقة عند 198856 بنفس توزيع الساعات لكن بـ LAB مختلفة)، أو أي وحدة من PORTING_LOG

## 8) وحدة M45 (الجديدة — OfflineCheatingGotoJail)

**M45 = ذيل M44 المعلق اكتمل** (`Exe/MsgServer/Port/MsgJailEx.{h,cpp}` + `tests/msg_jail_ex_test.cpp`)، ORIGINAL FUN_1400e36a0:

- **السجن بيتكتب في سجل الدخول:** "UPDATE cq_user SET recordmap_id = %u, recordx = %d, recordy = %d WHERE account_id = %u LIMIT 1" بإحداثيات بوابة ماب 6002 (map+0x58 vcall+0x10(0xb)) — فالغشاش الأوفلاين بيقع في السجن عند أولوجن
- 6 مسارات فشل بلوجات gmlog/cheater الحرفية (0x669/**0x66e بالغلط الإملائي "palyer"**/0x679/0x67e/0x685/0x68f — الأخير بيرسل الإيميل برضه)
- الإيميل: vcall+8("SYSTEM", idCheater, STR_OFFLINE_CHEATING_GOTO_JAIL)
- توزيع الساعات التاني (TOOLS1..4) + **quirk:** خارج المدى → TOOLS1 + لوج "GameJailEx time(%s) is error."
- MyLogSave بصيغة "AccountID" (مختلفة عن "UserID" بتاعة M44)
- **MSG_JAIL_EX_OK** + rerun العيلة أخضر
- **التالي (M46):** فرع الأونلاين-بالحساب في e36a0 (~198918+)، أو FUN_1400ef850، أو أي وحدة من PORTING_LOG

## 9) الوحدات M46→M54 (مكتملة كلها — التفاصيل في PORTING_LOG.md)

- **M46:** الفرع الأونلاين-بالحساب في FUN_1400e36a0 — lookup بمعرّف المستخدم (vcall+0x98/param_2)، لوج 0x65c، بوابة الرسالة غير الفارغة، تيليبورت بعلم **3** (مقابل 1 في M44)
- **M47+M48:** ctor الـ CMapGroupKernel (FUN_1400f0000) بتخطيطه الحرفي (أزواج الحاويات @+0x48/+0x88/+0xc8/+0x108/+0x148/+0x188 والسجن @+0x1c8) + الحارسات التلاتة بأحجامها (A=0x20 بعلم +0x1c، B=0x30 بعلم +0x28، Jail=0x80 بعلم +0x78 — والحاوية بتقفل علم size-3)
- **M49-M54:** الحاوية = شجرة حمراء-سوداء intrusive بستايل MSVC STL مقفولة كاملة: insert (FUN_14000bfd0 بحارس max_size وthrow "map/set<T> too long")، erase (FUN_14000ab40 بفحص end() بعلم الحارس +0x1d وthrow "invalid map/set<T> iterator")، مُخصّص العقدة FUN_140009ab0 (left/right/parent/key@+0x18/color@+0x1c/end@+0x1d)، مشية السلف FUN_1400075f0، الـ splice الحرفي بتبديل الألوان، التدويرات FUN_140008940/FUN_1400089a0، حلقة الـ recolor LAB_14000ad2c، وعقد الرجوع بالـ iterator المحدّث + العدّاد المحروس `if (param_1[7] != 0)`
- **نموذج الملفات:** Exe/MsgServer/Port/MsgMapGroupKernel.{h,cpp} (الشجرة) + MsgJailEx.{h,cpp} + MsgArrestHandler.{h,cpp} + MsgCheatTime.{h,cpp}؛ الاختبارات: tests/msg_mapgroup_ctor_test.cpp (يشمل الشجرة كلها) وmsg_jail_ex_test وmsg_arrest_test وmsg_cheat_time_test
- **TBD الموثق الوحيد في الشجرة:** نصوص فرع الطفل الواحد الكاملة في erase (decompile 8648-8662، المطبق حالياً مبسّط سليم) — لو محتاجينا لدقة قصوى
- **M55 المرشحة:** دوال mapgroupkernel الخارجية (مستهلكي الحاويات: إضافة غشاش للسجن، البحث، دوال النطاق/البث زي FUN_1400ef8d0 عند decompile ~195680) أو دوال الـ dlg المساعدة (FUN_14001f070 / FUN_140021bd0 / FUN_14001e540)

**تحذير منهجي:** أي تعديل على الملف ده لازم يتأكد فيه إن النص المستهدف موجود (python assert) — جلسات سابقة عدلت "آخر تحديث" واستبدالات فشلت بصمت فظل الملف متوقف من عهد M6.

## 5) فخاخ معروفة (متعملهاش تاني)

- **Ghidra pointer arithmetic:** `param_1 + 0x24` على `longlong*` = offset 0x120 مش 0x24 (حصلت في `FUN_14005b2d0` والـ stuckY).
- **عداد b2d0:** بيزيد الأول (11→12) وبعدين -5 → 7 مش 6.
- **تقييم printf:** ترتيب تقييم الوسائط غير محدد — متحطش نداء الدالة والـ assert على نفس السطر (غلطة الوحدة 27).
- **النوع 3-4 في 4bff0:** half = (type+1)/2 والفحص للخلايا cheb > half **من نقطة الأصل** مش من الهدف.
- **`m_dirQueue` اتوسعت لـ 76 بايت** (580e0 بينسخ حتى 76 بايت مسار) — متصغّرهاش.
- **(جديد، وحدة 34) idiom الباقي بإشارة:** `(uVar + x & 7) - uVar` مع `uVar = (x>>31)&7` هو باقي القسمة **بإشارة C %** — البايت 0xFE = -2 بيرجع **-2 مش 6** (حصلت في 5b760؛ اتأكدت في الاختبار). المتوقع إن نفس الـ idiom موجود في c960/b9e0 — راجع بورتاتهم لو استخدمت Euclidean بالغلط.
- **(جديد، وحدة 32) 4ab40 مش بيفحص خلية:** بوابة الحدود خالصة — أي فحص blockers بتاع 49310 غلط هناك. وكمان الإرجاع الفاشل بيرجّع **آخر قيمة نداء** (عرض/ارتفاع) مقمّعة، مش صفر ثابت.
- **(جديد، وحدة 40) جدول النصوص الحقيقي:** En_Res.ini الأصلي (فولدر Source، 324 مفتاح) بقيم الصيحة الحرفية STR_GUARD_CALL_s="Warning %s, no PK within city limits." / STR_PPKER_CALL_s="You have been slain, %s. We reap what we sow." + غموض sprintf بلا varargs موثق في الكود.
- **(جديد، وحدة 39) مسار البناء الأصلي الحرفي في نداءات الحاويات:** "f:\version\cqserver-78.0.11-1204\npcserver\npckernel\npc.cpp" بأسطر 0x68f/0x6b2/0x57 — محفوظ في البورت، متحذفوش.
- **(جديد، وحدة 37) قيم الخروج الثلاثة بره الحدود مختلفة حرفيًا:** Alt بيرجع 0x7fff وAccess بيرجع 0 وCellType بيرجع 1 — متوحدوش. ومؤشر الـ tile في الـ u16 العالي من الخلية (بايتات 2-3)، مش الواطي.
- **(جديد، وحدة 35) الحالات 2-5 dead:** الموزّع 1/6/7/8 فقط والحالات 2-5 مش بتتكتب أصلًا — متضيفش معالجات ليها أبدًا (كسر مطابقة للأصل).
- **(جديد، وحدة 36) فشل الإرسال 1c5f0 بيرجع TRUE:** الفشل بيتسجل فقط في كلمة الحالة +8 = 3 على السنجلتون — المتصلين شايفين TRUE دايمًا بعد محاولة إرسال. وكمان النوع بيتقتطع u32->u16 في الباكت.
- **(جديد، وحدة 34) 5b760 بيمسح +0x84 من 3 مسارات فقط:** مش موجود/ميت/بعيد عن النظر — مسارات سلسلة +0x3c بتسقط **بدون مسح**. وكمان +0x2c بيتصفّر أول الدالة دايمًا: القيمة اللي بتقراها بعد 580e0 لازم يكتبها الـ seam نفسه.

---

*آخر صيغة للتحقق الذاتي: `cd /app/co_repo && git log --oneline -1` لازم يكون أحدث من آخر commit في السجل تحت، والرجريشن 34/34 أو أكثر (كل ملف اختبار يطبع سطر واحد فيه "OK"). أمر البناء الكامل للرجريشن: لكل `tests/npc_*_test.cpp`: `g++ -std=c++17 -O0 -I. -Wno-unused-parameter <test> $(ls Exe/NpcServer/*.cpp | grep -v main.cpp) -o /tmp/reg/<name>` ثم تشغيله والبحث عن OK (اختبارا ops_205/record_201 مش في العد — سورسات MsgServer).*
