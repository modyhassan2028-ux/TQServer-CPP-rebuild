# HANDOFF — نقطة الاستكمال (TQServer / Syndicate.dll)

> **هذا الملف يتحدث بعد كل إغلاق وحدة.** أي Agent جديد يبدأ من هنا.
> السجل التاريخي التفصيلي: PORTING_LOG.md.

## آخر حالة (2026-10-26 — بعد D57)

- آخر commit: **D57 مقفولة** (هذا الـ commit) — الأجسام الحقيقية لمُشيّدات CMsg السبعة عشر (14177ead0 family) + مُشيّدا الحقلين protobuf (1417f1600/1417f05f0). ثلاثة أنماط حرفية: بسيط (12) / packer (3: +0x20/0x3e5, +0x128/0x2d9, +0x1a/0x3ee) / PB (2). RobOptPB لا يستدعي ثنك 1417e8050 خلافاً لـ TokenPB. g_aMsgCtor تربط بالأجسام الحقيقية
- قبلها: **D56** (c2b2b3d): جسم منح الميد الأونلاين 1417814c0 — جسم منح الميد الأونلاين 1417814c0 (المسار الحقيقي لـ seam ‏g_fnMeedAwardOnline في توجيه 21d0): قص الموني (vt+0x3e0−0x230) والإيموني (سقف DAT_141886d68 = INT_MAX، المُهيئ 141821a10)، منح vt+0x138/vt+0x148، ملاحظات syndenote (بوابة 9999 للموني)، prompt+إرسال 2000، gmlogs النوعين 2/3. إصلاح نقل: إعادة حساب القص داخل الشرط
- قبلها: **D55b** (90c6f4a): تدفق توزيع جوائز العصبة كاملاً (15 دالة) — تدفق توزيع جوائز العصبة كاملاً (SyndicateMeedDistribute: 141784cd0 التدفق + 49f0/46e0/2d0 الموزعون الثلاثة + 0b0/1b10/9b60/f0d0/21d0/1860/f250/fa90/fa10/fa60/ae630 = 15 دالة verbatim). إصلاحان أثناء النقل: قراءة end (+0x20) لا cap (+0x28) في زوج فرز 46e0؛ fa60 رُقّي ليرجع قيمة النقطة (مثل fa10)
- قبلها: **D55a** (1ae8280): عائلة متجه مدخلات الـ 5-int + الانترسورت الكامل (SyndicateMeedEntry: 22 دالة). مقارن LAB_141780100 = seam `g_fnMeedEntryCmp` — عائلة متجه مدخلات الـ 5-int + الانترسورت الكامل (SyndicateMeedEntry: 141780750/2020e0/2c20/2480/2550/2060/1ca0/3b70/4100/48f0/3ad0 + عائلة الفرز 1eb0/2640/7c0/1f30/2740/2810/2990/33d0/2ca0/3f50/4260). مقارن LAB_141780100 = seam `g_fnMeedEntryCmp` (thunk غير مفكك)
- قبلها: **D54** (73feb4d) ProcessEndMeed — تدفق ProcessEndMeed 141783470 (1229B) + باني قائمة المعرفات 14177d7a0 + المسح المتعدد 14177d180 (DeleteSynMeed: المسح + compaction + زوج التحرير vt+0x40/vt+0 + إعادة المسح)
- ملحق الجولة: **إصلاح d50 test** (commit 9a8c6b5) — الاختبار القديم لم يكن يتوافق مع parameterization عائلة الترتيب في D52؛ **D53 مقفولة** (deb058f): SetArenicMeed 141780cb0 (2058B) + عائلة Apply كاملة (SetSynMeed/Insert/AddMore/cb90/caa0/ff70/fbc0/fad0/da0d0/141732200)
- الرجريشن الكامل: **58/58 PASS × 6** (syndicate d26-d55a: 33/33 + peerage/analyst 25) بالعلم **O0** (المعيار المعتمد، ممنوع الحكم بـ O1 — d28 SIGSEGV عند O1 قديم ومستقل)
- TBD موثق في SyndicateMeedApply/End: الـ varargs المُسقطة في _snprintf/MyLogSave (لا يوجد Syndicate.dll binary في مساحة العمل هذه لتمريرة objdump — سياسات الـ seam موثقة)
- كل الكود مرفوع على GitHub. **NO BUILD** (لا zig/binaries) حتى اكتمال السورس كله.

## الخطوة التالية بالضبط: D58

0. **طبقة الوحدة كاملة الآن** — المُشيّد + بوابة التسجيل +
   ModuleCreate (وحدة Module سابقة) والمُشيّدات السبعة عشر (D57).
1. المتبقي في طبقة CMsg: **هاندلرز الرسائل** (أجسام Process
   خلف vtables الفئات السبع عشرة) + مفاتكياتها
   (1417e3b0/1417e430 الـ dtors منقولة، 1417e8050 عميق الـ PB)
   + بقية واجهة المدير (~70 دالة متبقية في نطاق كود اللعبة).
2. ابدأ بفحص فهرس الديكومبايل لأجسام Process للفئات الصغيرة
   (CMsgLog أولاً) ثم اقفلها وحدة وحدة.
3. فحص تغطية الـ 199 دالة المورتة مقابل الديكومبايل.

## قواعد العمل الثابتة (لا تتجاوزها)

1. **Verbatim من الديكومبايل** — المرجع: `conquer-online-v6159-decompiled/Native-Decompiled/Syndicate.dll.decompiled.c` (repo التحليل الثاني).
2. المُشيّدات/المدمرات تُختبر بـ counting registry (malloc tab + operator new/delete override) — القالب جاهز في `tests/syndicate_d40_test.cpp`.
3. الوحدات في `Exe/Dll/Syndicate/Port/`، الاختبارات `tests/syndicate_dXX_test.cpp`.
4. بعد كل وحدة: رجريشن كامل (كل ملفات tests على O0) ثم PORTING_LOG.md + HANDOFF.md + commit + push.
5. مسارات العمل داخل `/app/conversations/6ada078e9883f31f19597098/work/TQServer-CPP-rebuild`.

## بعد D41 (الترتيب)

1. **طبقة الوحدة**: المُشيّد 14177ead0 + بوابة التسجيل 14177e890 + الـ 18 handler CMsg (الـ export الوحيد ModuleCreate @ 14177ec90، ImageBase 0x141720000، كائن 0x4608).
2. واجهة المدير (~65 دالة): بقية accessors/operators (17 منهم مقفولين في D37).
3. فحص تغطية الـ 199 دالة المورتة مقابل الديكومبايل.
4. ثم بقية أنواع cq_action العليا + CQCrossServer الأعمق (حصر 23 أكتوبر: 172 نوع متبقي في 6 عائلات + أنظمة أوسع).

## الأخطاء المكتشفة (تجنب تكرارها)

- بوابة CRT: قارن بـ `*param_1` (proxy) مش `param_1`.
- أحجام الكائنات: آخر خريطة ممتدة 0x40 (proxy/head/size) — المدير **0x580** مش 0x540، الكيان 0x118، الوحدة 0x4608.
- التقدم للمخلف في المسح: prelude بأسلوب do (ابن اليمين أولاً) وإلا تتكسر حالة "ابن يسار ابن اليمين نيل".
- تحرير التوكن: args `(sub, 1, p3, p4, -2)` ثم deleting dtor ذاتي، والقيمة تصفر مرتين (حرفي).

---

## تحديث D58+D58b (2026-10-26)

### أصول جديدة مهمة جداً
1. **Syndicate.dll الأصلي مسترجع**: `co_decomp/orig_binaries/Source/Syndicate.dll` (1.59MB، ImageBase 0x141720000 مطابق 100% للفهرس) — من أرشيف `Conquer_Online_Source_v6159.7z` (829MB، فيه كل مصادر اللعبة: MsgServer/NpcServer/DLLs الأصلية). أي دالة يفشل فيها الـ decompiler يمكن فكّها يدوياً الآن بـ capstone (القالب موجود في سجل هذه الوحدة).
2. **جرد vtables كامل**: `tools/syndicate_vtables.json` — 66 جدول مسمّى عبر RTTI، أهمها:
   - نمط جدول CMsg (5 فتحات): `[dtor, deleting, Init(base 0x14177e2f0), Process, tail(0x14177e2d0)]` — **Process لكل فئة الآن معلوم العنوان** (CMsgLog=0x1417d97c0, ChgDomName=0x1417daee0, LeagueOpt=0x1417d68d0, LeagueRobOpt=0x1417d8920 ...).
   - جدول CModule (9 فتحات) مؤكد: Startup=+0x10 (0x14177e620), SvcPassThrough=+0x18 (0x14177eaa0), ProcessMsg=+0x20 (0x14177ec30).
   - جدول CSyndicateLogic = **232 فتحة** وIProvider = 224 — خريطة المنافذ الكاملة لوحدات المنطق القادمة.
   - ملحوظة thunk غريبة: بعض خانات deleting-dtor تشير لعنوان فردي 0x1417e7fda (thunk بيتوسط تعليمة) — عالجه كأنه entry+N سابق عند الفك.

### حالة D58
- مكتمل ومقفول: ذيل الوحدة (20 دالة) + **SendLeaveAward (14177eda0) مفكوك يدوياً ومنقول حرفياً** في `SyndicateLeaveAward.{h,cpp}` — كان الـ TBD الوحيد.
- الاختبار: 9 أقسام (D58-9 يربط Flow بالجسم الحقيقي E2E)، رجريجن 62/62 × 6، ASan نظيف.
- فتحات mgr الموثقة لـ SendLeaveAward: +0x138/+0x148/+0x1d8/+0x1f8/+0x230/+0x238/+0x3e0 (انظر PORTING_LOG للتفاصيل والسلاسل الحرفية).

### التالي (بالأولوية)
1. **D59: أجسام Process لفئات CMsg** — العناوين الآن كلها معلومة من الجرد؛ ابدأ بـ CMsgLog::Process (0x1417d97c0) ثم ChgDomName (0x1417daee0) — كلاهما في نطاق كود اللعبة.
2. بقية الفئات الـ 37 (كل Process فريد في الجرد).
3. الفشلان المتبقيان في الفهرس (1417ab8c0 502 بايت، 1417ac2d0 346 بايت — كلاهما داخل جدول CSyndicateLogic) — فكّ يدوي بنفس أسلوب SendLeaveAward.
4. واجهة المدير المتبقية + إغلاق ModuleCreate (14177ec90).


---

## تحديث D59 (2026-10-26)

- **D59 مقفول**: أول جسدين Process حرفيين — CMsgLog (0x1417d97c0) + CMsgSynChgDomName (0x1417daee0) + نداء الذيل 1417ac7d0 منقول من التفكيك مباشرة (`rcx=[p+8]; rax=[rcx]; jmp [rax+8]` — الـ decompiler أظهره "jumptable" وهمياً؛ الحرفية: deref اثنتان فقط).
- رجريجن **63/63 × 6** + ‏ASan نظيف. الملفات: `Exe/Dll/Syndicate/Port/SyndicateMsgProcess.{h,cpp}`، اختبار قسمين.
- **دروس مهمة**: (1) ثق بالتفكيك على الـ decompiler في النndlات القصيرة — 1417ac7d0 كان 3 تعليمات فقط. (2) ثقوب vtable الأساسية 14177e2d0/2e0/2f0 هي Process-error loggers حرفية ("tq::CMsg::Process(...) error") وليست Init. (3) tq::CMsg::Init الحقيقي @ 1417e8016 = ‏thunk للـ PB runtime (نفس عائلة 1417e8050 الـ TBD).
- **الترتيب التالي (D60+)**: بقية أجسام Process من الجرد — LeagueOpt (0x1417d68d0) ثم LeagueRobOpt (0x1417d8920)، أو إغلاق العمق أولاً: 1417b7010 (تدفق سجل الإعلان) / 1417ac620 (إزالة السجل) / 1417afb20 (فحص الاسم) — كلها seams مفتوحة موثقة في PORTING_LOG.

---

## تحديث D60 (2026-10-26)

- **D60 مقفول**: تدفق إزالة سجل المستخدم 1417ac620 (جسم الـ seam من D59) + 13 دالة تابعة حرفية في `Exe/Dll/Syndicate/Port/SyndicateLogRemove.{h,cpp}` — مشيات خريطة حمراء-سوداء حرفية (LogRecMapFind/AcctTreeFind/AcctFieldSet)، وسم+تيك (RecFlagTick عبر vt slots 2/22/7)، getters الرتبة، مقارنة الفرز، فرز الفيكتور بفحصي checked-iterator (invalid مرتان)، فرع الجلسة (+0x4f0 owner → إدراج → إرسال)، ومسح (ErasePrep).
- رجريجن **64/64 × 6** + ‏ASan نظيف (اختبار 9 أقسام + تدفقان E2E).
- **دروس مهمة**: (1) أزواج iterator في الديكمبايلر = فتحات ستاك متجاورة — حوّلها دائماً `aPair[2]` صريح (ASan يكشفها). (2) عقدة شجرة الحسابات stride 0x40 بـ isnil@+0x3d. (3) نداءات vt عبر فهرسة slot صريحة لا **(code**).
- **المتبقي في Syndicate.dll (~20-30 دالة، ~4% من نطاق اللعبة)**: أجسام Process لفئات CMsg المتبقية (LeagueOpt 0x1417d68d0، LeagueRobOpt 0x1417d8920، وبقية الجرد)، 1417b7010 (تدفق سجل الإعلان)، 1417afb20 (فحص تغيير الاسم)، جدول CSyndicateLogic (232 فتحة)، IProvider (224)، إغلاق ModuleCreate (14177ec90)، وهدفان فك يدوي (1417ab8c0، 1417ac2d0).

---

## تحديث D61 (2026-10-26)

- **D61 مقفول**: موزّع CMsgLeagueOpt::Process ‏(1417d68d0) — أكبر Process في الجرد (45+ حالة) + البوابة 1417ac700 + نداء الذيل 1417ac7d0 + 12 غلافاً حرفياً (تمرير الحساب، المحظية 1417b15b0/b14c0 بسلاسلها الحرفية، الجلسة 1417b1980/b1a40، المحوّل 1417bf4d0).
- رجريجن **65/65 × 6** + ‏ASan نظيف (8 أقسام).
- **دروس مهمة**: (1) فحص القائمة البيضاء قبل الموزّع الرئيسي عند gate≠0. (2) قلب الوسائط الحرفي في 0x4c/0x4d. (3) vtable ‏الـ logic يُقرأ بـ deref واحد (*(void***)logic) بينما كائن mgr باثنين.
- **seams الجديدة الموثقة**: الأجسام العميقة 1417b0a40 (تطبيق الاسم)، 1417b4310، 1417b98e0، 1417b03b0، 1417b0680، 1417b48b0، 1417b4d60، 1417b0ea0، 1417b3300، 1417bed70، 1417b3a90 + طبقة الحساب 14174ed50..14174ee90 + طبقة الجلسة 14176e600/14176ea30/141767560 + packer GetString/GetStrAmount + مدير السلاسل.
- **التالي (D62+)**: LeagueRobOpt::Process (0x1417d8920) أو فك يدوي لـ 1417ab8c0/1417ac2d0، ثم إغلاق جدول CSyndicateLogic وModuleCreate.

---

## تحديث D62 (2026-10-26)

- **D62 مقفول**: موزّع CMsgLeagueRobOpt::Process ‏(1417d8920) — 6 أنواع سطو، بوابة 1417ac700 ‏معادة الاستخدام، حلقة جمع 10 مُعرّفات، قسمة /1000 ‏و%1000 ‏عبر magic. الديكمبايلر وسم الوسيط الخامس in_stack غامضاً؛ التفكيك حسمه: بايت + ‏dword في خانتي ستاك.
- رجريجن **66/66 × 6** + ‏ASan نظيف (6 أقسام).
- **درس مهم**: "in_stack & 0xffffff00" في الديكمبايل = خانة بايت صُفِّرت في الستاك — التفكيك يفرّق بين mov byte/dword [rsp+X].
- **التالي (D63+)**: بقية أجسام Process من الجرد، أو الأعماق الموثقة: 1417b0a40 ‏(تطبيق الاسم 122 سطراً)، 1417b4310 ‏(237)، جدول CSyndicateLogic، ثم إغلاق ModuleCreate ‏(14177ec90) وهدايا الفك اليدوي 1417ab8c0/1417ac2d0.

---

## تحديث D63 (2026-10-26)

- **D63 مقفولة**: تدفق تطبيق اسم النقابة 1417b0a40 (جسم seam ‏g_fn1417b0a40 من حالة 6) + 6 مساعدين حرفيين في `Exe/Dll/Syndicate/Port/SyndicateLeagueNameApply.{h,cpp}` — الفاحصات (cb0/e00/4030)، علم 1000 ‏(1417868c0)، مشيّة "الاسم مأخوذ" على خريطة العصبات (14175eb70)، ومنسّق tq::CString ‏(1417215d0).
- **الاكتشاف الحرج (تفكيك خام)**: النداءان لـ 141743cb0 ظهرا في الديكمبايلر بلا فهرس؛ الخام أظهر `mov edx,8` ثم `mov edx,2` — الفهرس يعبر خلال الـ tail-jump إلى فتحة resolve (+0x10). الدالة ثنائية الوسائط.
- رجريجن **67/67 × 6** + ‏ASan نظيف (9 أقسام + E2E عبر موزّع D61).
- **دروس مهمة**: (1) سطور InlineLogERROR حرفية: 322 ‏(cb0, ""/"")، 431 ‏(4030, CHECK/m_pRec)، 1128 ‏(8c0, IF_OK/m_pRec, synattr.cpp). (2) strncmp ‏بحد 0x10 مش قص بادئة — التطابق يقع فقط إن اتفقت أول 0x10 بايت. (3) مخازن std::string ‏الحرفية في الستاك تُبنى بـ union raw + placement-ctor يدوي وإلا double-free.
- **التالي (D64+)**: بقية الأعماق الموثقة من D61 — 1417b4310 ‏(237 سطراً)، 1417b98e0، 1417b03b0 ‏(فحص تغيير الاسم 116)، 1417b0680، 1417b48b0، 1417b4d60، 1417b0ea0، 1417b3300، 1417bed70، 1417b3a90، أو جدول CSyndicateLogic ‏(232 فتحة)، ثم إغلاق ModuleCreate ‏(14177ec90) وهدايا الفك اليدوي 1417ab8c0/1417ac2d0.

---

## تحديث D64 (2026-10-26)

- **D64 مقفولة**: تدفق تغيير اسم النقابة GM ‏1417b03b0 (جسم seam ‏g_fn1417b03b0 من حالة 0x33) + قارئ السعر 14174e750 ‏(*(uint*)(host+0x18c)) في `Exe/Dll/Syndicate/Port/SyndicateLeagueGmName.{h,cpp}`.
- **اكتشافات التفكيك الخام**: (1) cb0 الوحيد هنا edx=2 ولا بوابة sub-8. (2) vt+0x140 ‏ستة وسائط: (mgr, actor, 0, price, 0x43, byte 1). (3) MyLogSave ‏بخمسة varargs موثقة كاملة ("gmlog/emoney_buy", "%u\t%s\t%u\t350\t4237\t%d\t%d\t1\t") — seam كامل g_fnGmNameLogSave بخلاف TBD-LOGSAVE القديم. (4) بوابة e3f0 **معكوسة** عن b0a40 (≠ synId، الاسم وسيط خامس). (5) لا SetFlagFlush ولا rec4.
- **تصحيح D63**: kCStrVftable ‏= 0x141824cf0 ‏(كان 0x14182cef0 خطأ حسابياً) + static_assert.
- رجريجن **68/68 × 6** + ‏ASan نظيف (4 أقسام + E2E ‏0x33).
- **التالي (D65+)**: 1417b4310 ‏(237 سطراً)، 1417b98e0، 1417b0680 (الإعلان — AnnounceStrCheck + ‏STR_INVALID_CHARACTER + 1417ac750)، 1417b48b0، 1417b4d60، 1417b0ea0، 1417b3300، 1417bed70، 1417b3a90، أو جدول CSyndicateLogic ‏(232 فتحة)، ثم ModuleCreate ‏(14177ec90) وهدايا الفك اليدوي 1417ab8c0/1417ac2d0.

---

## تحديث D65 (2026-10-26)

- **D65 مقفولة**: توزيع رواتب النقابة ‏1417b4310 ‏(جسم seam g_fn1417b4310 من حالة 0x27) في `Exe/Dll/Syndicate/Port/SyndicateLeagueSalary.{h,cpp}`: ثلاثة أنواع (مساهمة emoney / emoney / سقوط type4) بمقاطعها الحرفية، مشيتا خرائط الرواتب والأعضاء (مفاتيح u16/u32)، بنية الإيميل كاملة عبر vt+0x118، والرد CMsgLeagueOpt بعلم single-shot (0x508→0x500) أو حلقة البريد.
- **اكتشافات التفكيك الخام**: (1) قراءة الرتبة vt+0x518 (فتحة **163**) قبل موزّع الأنواع. (2) ‏esi ‏النوع 3 = **الحرة** مش emoney. (3) الماجيك 0xd1b71759 ‏shr 13 = قسمة على **10000** (مش 86400) — معادلة تاريخ البريد الحرفية. (4) السلسلة المسحوبة من StringMgr هي الـ format ‏نفسه لـ _snprintf بثلاثة varargs. (5) ‏vt+0x298 ‏بياخد دلتا **int64** سالبة (-cost). (6) ‏vt+0x140 ‏بستة وسائط والوسيط الخامس **0x49** ‏(0x43 في D64) + سطر gmlog 4318.
- رجريجن **69/69 × 6** + ‏ASan نظيف (7 أقسام + E2E ‏0x27 عبر موزّع D61). ملاحظة: UBSan بيعترض على stores غير المحاذاة في PB ‏— حرفية مقصودة، البروتوكول ASan-only.
- **التالي (D66+)**: من الأعماق الموثقة — 1417b98e0، 1417b0680 ‏(الإعلان — AnnounceStrCheck + ‏STR_INVALID_CHARACTER + 1417ac750)، 1417b48b0، 1417b4d60، 1417b0ea0، 1417b3300، 1417bed70، 1417b3a90، أو جدول CSyndicateLogic ‏(232 فتحة)، ثم ModuleCreate ‏(14177ec90) وهدايا الفك اليدوي 1417ab8c0/1417ac2d0.

## D66 (2026-10-26) — تحزيم الفئات: 12 جسم CMsg::Process الصغيرة الباقية دفعة واحدة

- **الجرد المكتمل (مسح بيناري)**: نمط qword (slot2=0x14177e2f0، slot4=0x14177e2d0) → **32 جدول CMsg**؛ ربط كل فئة بـ Process عبر تفكيك المُشيّدات (lea rip-rel). ‏4 مقفولين سابقاً + ‏12 هنا + ‏CMsgSyndicate ‏(1417db7b0، 416 سطراً → D67 لوحده) + الباقي stubs.
- **الأجسام**: SynDomain/SynProffer/SynAttrInfo/SynMemberInfo/SynMemberList/SynBaseProffer(`ret 0`)/SynProfferRank/SelfSynMemAwardRank(جدول قفز 13 خانة عند 0x1417da7d0)/SynRecruitAdvertising(نداء 11 وسطاً vt+0x3e8)/SynRecruitAdvertisingOpt/SynRecruitAdvertisingList(movsxd)/LeagueToken(vt+0x610 سبعة وسطاء / vt+0x608).
- **كذبات الديكومبايلر المكتشفة بالخام**: (1) ‏ac6f0/ac710 بياخدوا (logic, actor) — edx عدّاي عبر mgr-thunk. (2) ‏ac810(logic, actor). (3) ‏**b2df0(logic, actor, u32* out×3)** — مؤشرات OUT حذفها الديكومبايلر. (4) ‏`cmp r12d,r12d` ‏no-op حرفي في حالة 2-7. (5) جدول القفز: 8/9 → افتراضي. (6) ‏**r9 stale** في كل نداءات ac750. (7) اسم الإعلان > 0xff → عودة صامتة بدون announce.
- الملفات: `Exe/Dll/Syndicate/Port/SyndicateMsgProcess2.{h,cpp}` + `tests/syndicate_d66_test.cpp` (12 قسماً، 39 تأكيداً).
- رجريجن **70/70 × 6** + ‏ASan نظيف.
- **التالي (D67+)**: ‏CMsgSyndicate::Process (0x1417db7b0) وحدة مستقلة، ثم الأعماق الموثقة (1417b98e0، 1417b03b0، 1417b0680، 1417b48b0، 1417b4d60، 1417b0ea0، 1417b3300، 1417bed70، 1417b3a90)، جدول CSyndicateLogic (232 فتحة)، إغلاق ModuleCreate (14177ec90)، وفك يدوي 1417ab8c0/1417ac2d0.

## D67 (2026-10-26) — CMsgSyndicate::Process (4297 بايت) — أكبر جسم

- فك 3 جداول قفز (رئيسي 29 حالة + جدولا الرتب). **انتبه: r13=0x141720000 — الجداول عند 0x1417dc87c/944/95c بعد نهاية الدالة.**
- كذبات الديكومبايلر: كل _snprintf خمسة وسائط «%d %d %d %d %d» (rank, ce0ret/1, a50ret/1, ac430ret, ثابت لكل رتبة: 0/650/320/270/100/0)؛ عائد ac430 مستخدم؛ ac7f0 بياخد الـ GetString buffer؛ r9=0x100 متقادم في 0x1b؛ r9=ac800ret في 0x1d؛ معالج 0x348 بدون memset؛ 0x25 يرد عبر CMsgSyndicate كومة-مكدس (مُشيّد D57) وac7d0 مرسالها stackMsg بينما 0x2d مرسالها الرسالة الواردة.
- الملفات: `Exe/Dll/Syndicate/Port/SyndicateMsgSyndicate.{h,cpp}` + `tests/syndicate_d67_test.cpp` (13 قسماً، 67 تأكيداً، خريطة D34 حقيقية للسلسلة).
- رجريجن **71/71 × 6** + ASan نظيف.
- **التالي (D68+)**: طبقة CMsg كلها مقفولة الآن — انتقال للأعماق: 1417b98e0، 1417b03b0، 1417b0680، 1417b48b0، 1417b4d60، 1417b0ea0، 1417b3300، 1417bed70، 1417b3a90 (التحزيم ممكن)، جدول CSyndicateLogic (232 فتحة)، إغلاق ModuleCreate (14177ec90)، وفك يدوي 1417ab8c0/1417ac2d0.

---

## تحديث D89 (2026-10-27)

- **D89 مقفولة**: CLeagueMgr::FlyToInvadeWarning (141774500، 299 سطراً) + كيت CMsgInvadeWarning الحرفي (المُشيّد 1417d50f0 / Init النوع 0xc1c عبر 1417d5250 / فحص الإنشاء 1417d5170 / المدمران) في `Exe/Dll/Syndicate/Port/SyndicateLeagueInvadeWarn.{h,cpp}`.
- رجريجن **93/93 × 6** + ‏ASan/UBSan نظيف (اختبار 10 أقسام، 26 تأكيداً، التقاط محتوى الرسالة وقت الإرسال).
- **دروس مهمة**: (1) بوابة vt+0x288 ‏this ‏فقط (الخام بلا edx). (2) رأس الخريطة يُقرأ من *(map+0x30) — 600 عشري في الديكمبايل = +0x258. (3) local_538 = قيمة إرجاع rax من إدراج الخريطة الفرعية. (4) 4 نداءات operator_delete حرفية في مسار الإدراج. (5) بوابة الـ pop: plVar3 != *plVar3.
- **التالي (D90+)**: بقية نطاق Syndicate.dll ‏— أجسام Process/CMsg ‏المتبقية من الجرد، 1417b4310 ‏(237)، جدول CSyndicateLogic (232)، IProvider (224)، إغلاق ModuleCreate (14177ec90)، هدفا الفك اليدوي (1417ab8c0، 1417ac2d0).

---

## تحديث D90 (2026-10-27)

- **D90 مقفولة** (أول وحدة بنمط الفئات المسرّع): الموجة 1 من جدول CSyndicateLogic — 18 جسماً حرفياً (الفتحات +0x000..+0x0a8) في `SyndicateLogicTable1.{h,cpp}` + 21 seam جديد و8 مُعاد استخدامها.
- رجريجن **94/94 × 6** + ‏ASan/UBSan نظيف.
- **نمط العمل الجديد**: وحدة = دفعة أجسام من فئة/جدول واحد + اختبار مجمّع واحد، بدل دالة/وحدة.
- **التالي (D91+)**: بقية الجدول دفعات: ~35 فتحة صغيرة (25-60 سطراً) + 24 متوسطة + 15 كبيرة؛ ثم IProvider (224 فتحة معظمها stub نقاء)، ثم ModuleCreate وهدفا الفك اليدوي.

---

## تحديث D91 (2026-10-27)

- **D91 مقفولة**: إعادة التنظيم على الهيكل الأصلي الحقيقي — استخراج مسارات الملفات الأصلية من حرفية السجلات (modules/syndicate/src/{syndicatelogic,country,synmanager,league,meedrecord,...}.cpp + msg/)، وترحيل D89 إلى league.cpp كـ `CLeagueMgr::FlyToInvadeWarning` وD90 إلى syndicatelogic.cpp كطرق `class CSyndicateLogic` مع الأسماء الحقيقية حيث تكشفها السلاسل.
- القاعدة الجديدة: **كل نقل جديد يُكتب في ملفه الأصلي باسم صنفه الأصلي**؛ شيمات Port/ مؤقتة تُزال تدريجياً عند ترحيل الوحدات القديمة.
- رجريجن **94/94 × 6**.
- **التالي (D92+)**: موجة 2 من جدول CSyndicateLogic داخل syndicatelogic.cpp (~35 فتحة صغيرة ثم المتوسطة)، ثم إعادة توطين الوحدات القديمة على ملفاتها الأصلية (country.cpp لـ CCountry::OnLeagueOnStage D85، msg/*.cpp لأجسام Process، ...).
