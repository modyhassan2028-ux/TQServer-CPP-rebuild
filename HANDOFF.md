
# ⚠️ دليل الوكيل التالي — ابدأ من هنا (آخر تحديث 2026-10-24 18:30)

## 0) حالة NpcServer لحظياً (جلسة 24/10 — محدث 25/10 00:45)
- **جديد:** الوحدة 28: **FUN_1400597f0
  (رسالة المشي الحقيقية) جسم حقيقي** في
  NpcStateUtil: بوابة الخريطة +0x98، بوابة
  الحدود FUN_140049480/140049430 (خارجها ->
  اللوج الحرفي)، +0x2c = 0، الوثبة
  FUN_140058610(npc, x, y)، +0x24 = dir،
  ctor الرسالة FUN_1400623e0، **القصّ
  الحرفي (short)** لمواضع الـ sub من
  vt+0x38/0x40، التعبئة
  FUN_140062530(msg, id, xs, ys, (short)dir,
  0x89, (short)x, (short)y, 0) بمعرّف
  الرسالة 0x89، الإرسال FUN_14001c5f0 عند
  نجاح التعبئة فقط، وdtor الرسالة.
  NPC_WALKMSG_OK (6 حالات)، الرجريشن 26/26.
  وبكده **عيلة الحركة/الهجوم كاملة كجسوم
  حقيقية** (260/8b0/9e0/b2d0/97f0/c960)،
  وbc80 أكبر دالة خلصت في الوحدة 27.
- **الوحدة 27: **FUN_14005bc80
  (البحث عن الهدف — أكبر دالة، 294 سطر)
  جسم حقيقي** في NpcTargetSearch.{h,cpp}:
  بوابة الخريطة مع كود 0x66a المحلي
  واللوج، بلوك PK ببتات 8/9 من row(0x15)
  مع FUN_140059dc0 وإرجاعين مبكرين
  (تسريب (v>>8) low-byte حرفي عند bit8 و
  CONCAT71(v>>0x11,1) عند bit9)، **تصفير
  +0x84 قبل find القديم -> find(0) كود
  ميت حرفي**، نداء GetInt بلا وسيط (أثر
  سجل Ghidra) يبوّب المسح على bit1، مسح
  حلقات شبكة 0x12 كتيكة المستخدم بحدود
  490/440 وخلايا 4ac70، **ممر 1: حاوية
  NPC عبر FUN_1400678b0 (npc.cpp سطر
  0x68f)** ببوابة بتات 3/4/0xb مع أعلام
  الـ sub ببتات 0/0xf/0x1d وFUN_14005ab20،
  تثبيت المستوى min(sub GetInt(item
  vt+0x48), sight)، تحسين (d<=best &&
  !vt68) || (d<=468 && sub GetInt(0)>1)，
  **ممر 2: حاوية users عبر FUN_1400678a0
  (npc.cpp سطر 0x6b2)** ببوابة sub58&&item70
  / sub70&&item58 المتقاطعة وبوابة item78/
  sub78/57c50/GetInt(0x24)!=0x3fc، جلب
  المالك vt+0xb0(0x1040) مع تخطي مالك
  bit3، **الممر 2 بياخد id من vt+0x28
  ومش بيحدّث local_460 أبداً**، والختام
  بصيحات STR_GUARD_CALL_s / STR_PPKER_
  CALL_s (theInstance + sprintf +
  FUN_1400586b0) ونداء FUN_14005b760(npc,0).
  NPC_TARGETSEARCH_OK (15 حالة)، الرجريشن
  25/25.
- **الوحدة 26: **FUN_140059770
  (بوابة الحرية) + FUN_14005b2d0 (معالج
  العلوق) جسوم حقيقية** في NpcStateUtil.
  الـ 59770: +0x28 != 2 وبتات 3/4/0xb من
  row(0x15) صفرية -> true. الـ b2d0: سلسلة
  البوابات (59770 ثم attach حي عبر
  FUN_140069750 يرجّع فوراً، ثم FUN_14005ad00
  + sub vt+0x50)، بوابة +0x18، مقارنة
  x(+0x34) بـ stuckX(+0x11c) مع عدّاد
  +0x124 وفوق 10 وثبة عشوائية (RandGet(8)-4
  في المحورين، فحص FUN_14004cc70، العدّاد =
  max(c-5,0)، نداء FUN_1400597f0(nx, ny,
  dir +0x24))، **والإرجاع الحرفي دايماً true
  في مسار stuckX**، تحديث stuckX/Y (والـ
  +0x120 عبر غرابة الحساب بالمؤشر بتاعة
  الأصل)، إعادة تعيين العدّاد، **وتسريب
  low-byte لقيمة y** في مسار التحديث —
  حرفي موثق. NPC_STUCK_OK (14 حالة)،
  الرجريشن 24/24.
- **الوحدة 25: **FUN_14005b9e0
  (خطوة الهجوم/الوثب) جسم حقيقي** في
  NpcStateUtil: بوابة الخريطة +0x98، signed-mod
  للاتجاه مع كتابة +0x24، الخلية المرشحة
  بجداول DAT_1400c89d0/89f0، بوابة الحدود
  FUN_140049480/140049430 (خارجها -> اللوج
  الحرفي)، **فحص المشي الحرفي الغريب**:
  FUN_14004bff0(map, x, y, dir الـ sub نفسه
  من vt+0x18!, u48, 0) — الصفر مش 0x1a
  والاتجاه مش الممرر، مسار الفشل
  !walk && (!attach || !FUN_140049310) ->
  FUN_14005b2d0 (seam)، الرسالة
  FUN_140062030 ctor + FUN_1400620c0(id, dir,
  flavor) (فشلها -> لوج + dtor + false)،
  الإرسال FUN_14001c5f0(kernel, id, msg)،
  الوثبة FUN_140058610(npc, dx + +0x34,
  dy + +0x38)، dtor. NPC_STEPATTACK_OK
  (10 حالات)، الرجريشن 23/23.
- **الوحدة 24: **FUN_1400588b0
  (اختيار اتجاه المطاردة) + FUN_140058b80
  (جلب موقع الـ attach) جسوم حقيقية** في
  NpcStateUtil. الـ 588b0: نفس مسح 58260
  Greedy (RandGet(8) signed-mod، فحص
  FUN_14004bff0، جداول DAT_1400c89d0/89f0،
  Chebyshev، إشارة +0x3c، +0x40/+0x2c=1،
  تسريب low-byte) لكن المرجع = res المُمررة
  مع override من موقع الهدف +0x84، وعند
  فشل اللوقي يقرأ local_resc **غير المهيأ**
  حرفياً (m_nRescGarbage seam). الـ 58b80:
  بوابة +0x140، FUN_1400696d0 نتيجتها
  مهملة حرفياً، سلسلة 1c200->1c130->34e00
  ببوابة صفر، فرع FUN_140069910: 65750==0
  -> gen +0x100 vt+0x28، وإلا 657c0، أو
  65510، والناتج كلمتين. NPC_PURSUIT_OK
  (9 حالات)، الرجريشن 24/24.
- **الوحدة 23: **FUN_140066820 تيكة
  المستخدم (جسم حرفي)** في NpcUserTick.{h,cpp}:
  بوابة الاستحقاق (فاصل +0xa0 + طابع +0xa4
  <= TimeGet/1000 مع تحديث الطابع)، الأثر
  الحرفي (TimeGet*0x10624dd3 & 0xffffffff)
  يُرجع في حالة الخمول (موثق مش مُصلّح)،
  توسّع حلقات من base=(x/0x12-1<1?0:
  x/0x12-1) محدود بـ x/0x12+1 و
  FUN_140049490، صفوف row=(y/0x12-1<1?0:
  y/0x12-1)..y/0x12+1 محدودة بـ
  FUN_140049440، خلايا FUN_14004ac70 ->
  حاوية FUN_1400678a0 (عدّاد vt+0x10
  وجلب vt+0x18 حاملين اللوج الحرفي
  "f:\version\cqserver-78.0.11-1204\
  npcserver\npckernel\user.cpp" وسطر
  0x57)، فحص حي vt+0x50 ومسافة sub
  vt+8(item x/y) مع إرجاع < 0x13 عند
  اللقاء، وإلا broadcast الخروج
  (FUN_14001c210->vt+0x10 world vt+0x28
  بمعرّف this vt+0x8). NPC_USERTICK_OK
  (9 حالات)، الرجريشن 23/23.
- **الوحدة 22: **FUN_140058260
  (اختيار اتجاه الهجوم) جسم حقيقي** في
  NpcStateUtil: المرجع = نقطة ولادة المولد
  (gen vt+0x28) أو موقع الهدف +0x84 لو موجود،
  مسح 8 اتجاهات يبدأ من RandGet(8) بالmodulo
  بإشارة متخطياً الاتجاه الحالي، بوابة خريطة
  sub vt+0x80 (null -> تسريب 0)، فحص المشي
  FUN_14004bff0(map,x,y,dir,u48,0x1a)، الخلية
  المرشحة بجداول DAT_1400c89d0/89f0 (تحققت
  من الـ binary: مطابقة تماماً لجدول الـ wander
  بتاع FUN_140087d50)، مسافة Chebyshev، إشارة
  +0x3c: صفر -> تعظيم البعد / واحد -> تقريبه،
  تحديث جشع للمرجع، وعند النجاح +0x40 = أفضل
  اتجاه و+0x2c=1. **ملاحظة حرفية**: عند عدم
  وجود اتجاه أفضل، الأصل بيرجّع low-byte من
  آخر مسافة محسوبة (تسريب uVar9) - بورت
  حرفياً مش مُصلّح. NPC_ATTACKDIR_OK،
  الرجريشن 22/22.
- **الوحدة 21: **FUN_14005c960 —
  منفّذ خطوة الـ AI الأساسي — جسم حقيقي**
  في NpcStateUtil: بوابة المعدل FUN_14005a8f0
  (نافذة/2x-نافذة: < نافذة → معدّل منضبط، ≥
  2x → reset، بينهما → تقديم الطابع) مع مفتاح
  الصف 0x13/0x1a حسب النكهة، قائمة اتجاهات
  +0x40 مع إزاحة memcpy الحرفية عند البوب
  والباقي modulo بإشارة، FUN_14005b9e0 خطوة،
  مسار بلا attach: هجوم FUN_140058260 مع
  LAB_14005caf0 (+0x2c=0 وb9e0(queue[0])) أو
  بت 5 → teleport للولادة عبر جسم 59f40
  الحقيقي، مسار الـ attach: FUN_140058b80
  (ناتج كلمتين lo/hi) + RandGet(100)<0x46؟
  0 : GetInt(0x10) + FUN_1400580e0 ثم سلسلة
  !b9e0(queue[0]) && FUN_1400588b0 && 2c!=0 →
  caf0، وقيمة الإرجاع في نهاية المسار هي
  نتيجة 580e0 نفسها (بورتهت حرفياً — موش
  false). FUN_140069750 (attach alive: +8!=0
  && +0x10!=0) جسم حقيقي أيضاً. NPC_C960_OK،
  الرجريشن 21/21.
- **الوحدة 20: **أجسام حقيقية
  للمساعدات الصغيرة المستقلة** في
  NpcStateUtil.{h,cpp}: FUN_140057d30
  (= ~(row(0x15)>>15)&1 نفس بت القفل بتاع
  الحالة 6)، FUN_14005ad00 (بوابة الحركة:
  كلمتا vt+0x20 بتات 5/3 مانعتان، وبت 6 من
  النوع يتطلب بت 5)، FUN_140059f40
  (الـ teleport-approach: عدد الخطوات من sub
  vt+8، استيفاء i/steps من الموقع الحالي مع
  فحص FUN_14004cc70 عند كل خطوة x-first، أول
  خطوة مرئية تفوز → FUN_1400597f0، مع سقوط
  أخير على الهدف، وsteps<1/لا خريطة → false
  مع DAT_1400be0b0)، FUN_140058500 (خطوة
  الـ wander 8-اتجاه: u48 من sub vt+0x48،
  فحص FUN_14004bff0(map,x,y,dir,u48,0x1a)،
  ثم +0x40=الاتجاه و+0x2c=1). لاحظ ترتيب
  الوسائط في FUN_14004cc70 مختلف بين
  59f40 (x أولاً) وd140 (y أولاً) — موثق
  حرفياً عند كل استدعاء. NPC_STATEUTIL_OK،
  الرجريشن 20/20.
- **الوحدة 19: **معالج الحالة 1
  (FUN_14005e900) — أضخم معالج — بورت حرفي**.
  كل آلة موت الـ NPC الأربع حالات مكتملة الآن.
  المحتوى: قسم الاستدعاء (بت 8: دورة المخلوق
  FUN_1400623e0 ctor → FUN_140062460(id,y,x,0x59,0)
  → إرسال FUN_14001c200/1c5f0 → dtor FUN_140062430
  مع اللوج DAT_1400be0b0 عند الفشل)، early-out
  FUN_14005df70، قسم no-sight (2c>0 → c960(_,0)،
  بت 7 + gen vt+0x68 خارج المنطقة → تخطي فحص
  FUN_140002700)، LAB_14005eb1c (reset +0x44/+0x3d،
  بوابة كلمتَي vt+0x20 بتات 5/3)، كتلة العدوان
  (اللوج الحرفي WARNING "npc: [%d][%d], target id:
  [%d]" عند فقدان الهدف، d1<=d2 → FUN_140059c90
  وحالة 8، مسار AD00: 2c → حالة 7، أو
  0x4f<RandGet(100) → حالة 6)، قسم الحركة
  (بتات الرؤية → c960(0)+2700، داخل منطقة المولد:
  8-اتجاه FUN_140058500(RandGet(8)) أو نقط عشوائية
  في مستطيل المولد RandGet(vt+0x60/vt+0x38)+
  vt+0x50/58 عبر FUN_1400580e0، خارج المنطقة:
  بوابة 1/5 → حركة لنقطة الولادة gen vt+0x28 وإلا
  teleport بت 5 عبر FUN_140059f40). NPC_STATE1_OK
  (19 حالة اختبار)، الرجريشن 19/19.
- **الوحدة 18: **معالج الحالة 7
  (FUN_14005d550) بورت حرفي** في NpcState. مسار
  الهدف الصالح: بوابات الخريطة والمسافة، ثم
  early-out مركّب (!bit3 && !FUN_14005ad00 &&
  sub vt+0x60 && +0x3c==0 && +0x2c>0 &&
  FUN_14005c960(_,1)) وإلا FUN_140059c90 وحالة 8.
  مسار LAB_14005d668: بوابة FUN_14005cb60، نتيجة
  gen vtable+0x28 (نقطة الولادة)، رقصة InArea
  لبتات 3/4/7 عبر gen vtable+0x70(map,x,y,0x30)
  مع LAB_969 (إسقاط الهدف +0x84=0 +
  FUN_14005a0d0(res8,resc,id) → حالة 1)، LAB_789:
  حركة بعيدة المدى لبت 0xb (مسافة > 5 +
  FUN_140049310 → FUN_1400597f0)، بوابة +0x2c →
  FUN_14005c960(0/1 حسب +0x84)، ثم
  FUN_14005bc80 + بت 5 → FUN_140059f40 (teleport)
  أو اللوج DAT_1400be0b0. NPC_STATE7_OK،
  الرجريشن 18/18.
- **الوحدة 17: **معالجتا حالتَي 6 و8
  بورت حرفي** في NpcState.{h,cpp}. الحالة 6
  (FUN_14005d140): بوابة البت 15 مع اللوج الحرفي
  DAT_1400be0b0، مسار الرؤية (بتات 3/4)
  FUN_14004cc70(map,y,x) → FUN_1400597f0 والانتقال
  للحالة 7، LAB_14005d291: بوابة FUN_14005b030 →
  wander بـ FUN_14005b760(row(0x10)*2)، ولا-هدف →
  حالة 1، 2c==0 → حالة 7، وإلا FUN_14005c960(_,1).
  الحالة 8 (FUN_14005d330): بوابات المطاردة
  (هدف/خريطة/d2>=d1)، FUN_140002700(+0xa8)، الهجوم
  FUN_140058260(npc,-1) ببوابة +0x3c صفر/واحد
  حوله، FUN_14005c960(_,2) لو +0x2c، ماسك الخروج
  +0x3e، LAB_467 → حالة 7، LAB_475: بوابة
  +0x140/FUN_140069750، إعادة فحص العدوان
  FUN_14005bc80 مع الاستمرار في المطاردة عبر
  FUN_14005ad00، وفقدان الهدف → +0x2c=0 وحالة 1.
  NPC_STATE68_OK جديد، الرجريشن 17/17.
- **الوحدة 16: **تيكة الموت/reborn
  (FUN_14005b5c0) + بوابة الاستمرار (FUN_140058860)
  + مُوزّع حالات الموت (FUN_14005f3b0) بورت حرفي**
  في NpcDeath.{h,cpp}. التيكة: بوابة 1Hz
  (+0xb4=+0xb0)، فلاجات صف النوع 0x15 البتات
  3/4/7 → فحص مساحة المولد vtable+0x68(gen,x,y)،
  فحص الموضع FUN_14004ae30 → إعادة ضبط إحداثيات
  الـ reborn من عمودي الصف 4/5 إلى +0x1c/+0x20 مع
  +0x2c=0 و +0x18=0 (عودة للحياة). الموزّع: التيكة
  أولاً، ولو لفّت النتيجة بيتخطى آلة الحالات؛ وإلا
  بوابة sub vtable+0x50 && !+0x148 ثم حلقة الـ 10
  مرات على الحالة +0x18: 1→FUN_14005e900، 6→
  FUN_14005d140، 7→FUN_14005d550، 8→FUN_14005d330
  (المعالجات نفسها seams للوحدة القادمة).
  NPC_DEATH_OK جديد، الرجريشن 16/16.
- **الوحدة 15: مسار موت الـ NPC مُكتشف ومُنفّذ**. (1) تصحيح مهم: كل عناوين الجداول في
  الوحدات السابقة كانت raw offsets في الملف —
  جدول CNpc الحقيقي VA 0x1400c92f8 = raw 0xc78f8
  (37 فتحة +0x00..+0x118)، وجدول CNpcGenerator VA
  0x1400c99c8 = raw 0xc7fc8 (متوافق مع الوحدة 13 ✓).
  (2) **CNpc vtable+0xf0 = FUN_14005f450 =
  CloseAndDelete**: FUN_14005f020 (CNpc::Close) ثم
  deleting dtor vtable+0(_,1) — نفس الفتحة بتاعة
  فشل الإنشاء في الوحدة 9 ✓. (3) **FUN_14005f020 =
  CNpc::Close = مسار الموت**: reset التحوّل
  (+0x118=0/+0x114=0)، إزالة من الخريطة
  FUN_14004c900، **لوج مغادرة لنطاق الوحوش
  0x61a82..0x7a11e** (FUN_14001c7a0→FUN_140025c20→
  FUN_14005e230 بـ record الـ id؛ فرع 0x7a121/599999
  في الديكومبايل كود ميت)، **RESTOCK أخيراً:
  gen->vtable+0x78(gen,id) = FUN_14005fb30 عند
  الموت**، ببوابة FUN_14001c1c0(+0x80) OR
  (+0x128 && +0x12c)، مسار التقرير FUN_14005df30 +
  إلغاء تسجيل المولد من مدير التقارير vtable+0x28
  (mgr, genId) لو gen->vtable+0x20()==0، ثم
  FUN_14005da00 النهائي. (4) حديقة RTTI كاملة:
  IAIStrategy/CDefaultAIStrategy (raw 0xc4ac8،
  فتحة +0x18 = FUN_140067070 → FUN_14005f3b0
  مُوزّع الموت)/CNeuralAIStrategy (raw 0xc56e8،
  +0x20 = FUN_140067390 → FUN_14005b5c0 تيكة الموت،
  +0x10 = FUN_140067090 مُجمّع fitness)/CAIStrategyMgr
  (raw 0xc53e0). (5) **FUN_14005f3b0** = مُوزّع حالات
  الموت: FUN_14005b5c0 أولاً ثم حسب +0x18: 1→
  FUN_14005e900، 6→FUN_14005d140، 7→FUN_14005d550،
  8→FUN_14005d330 (آلة حالات الـ reborn 6/7/8).
  بورت في NpcClose.{h,cpp} مع NPC_CLOSE_OK والربط
  بالتجميعة (مسار فشل الإنشاء بيشغّل الـ Close
  الحقيقي الآن).
- **الوحدة 14: عيلة التيك كاملة + هوية السنجلتون
  = CAIStrategyMgr**. الاكتشافات:
  (1) **FUN_14001d390 (تيكة CNpcWorld، فتحة الجدول
  موثقة بـ RTTI ".?AVCNpcWorld@@") بتنادي 4 خطوات
  بالترتيب**: FUN_14003c520 (فارغة تماماً — جسم RET
  واحد)، FUN_140037f80 (مشية المستخدمين على +0x38)،
  CTickAnalyst(0x51) + FUN_14002b380 (المدير — الوحدات
  11-13)، ثم FUN_14001d230 → FUN_1400489b0.
  (2) **FUN_14001d230 = tq::Singleton<CAIStrategyMgr>**
  (ctor FUN_140045ff0 بيحط vftable السنجلتون ثم
  CAIStrategyMgr، 0x98 بايت، زوج shared_ptr عالمي
  DAT_140103c70/78 مع رقصة refcount LOCK/UNLOCK).
  (3) **FUN_1400489b0 = CAIStrategyMgr::Process —
  مدرّب الحقب (epoch) للـ AI العصبي!** كل 599999ms
  (~10 دقائق): عدّ الاستراتيجيات اللي fitness
  (vtable+8, double) بتاعتها <= 2.220446049250313e-16
  (epsilon الآلة، DAT_1400c7218)؛ لو count*8 < عدد
  السكان → لو مرت 10800000ms (3 ساعات) من آخر
  reload → FUN_140043700 ثم ++generation (+0x8)؛
  لكل جين: FUN_1400670d0/e0 ولو generation > 1 →
  لوج حرفي SysLogSave("ainpc", "Gene[%d]\tGeneration
  [%d]\tFitness[%d]")؛ ثم "Epoch neural AI generation
  %d" و FUN_1400476a0 (التطوير) و "CAIStrategyMgr::
  Process() update neural AI generation %d.".
  (4) **FUN_140037f80**: مشية عكسية على مجموعة
  المستخدمين مع إعادة جلب العدد كل لفة (توقف لو اتغير)
  و accessor بيحمل المسار الحرفي "f:\version\cqserver-
  78.0.11-1204\npcserver\npckernel\usermanager.cpp"
  سطر 0x3a (نمط MSVC vector::at) ثم FUN_140066820
  لكل مستخدم (تيكة مستخدم بزوج 1s +0xa0/+0xa4 — جسم
  TBD).
  (5) **حفر RTTI**: الجدول بتاع FUN_140056fd0 هو
  CGameData<szNpcType,szID> (+0x18)؛ الثنكات
  FUN_1400222e0/310/330 = CGameData<szInstanceTypeTable,
  szID> — كلها استدعاءات جداول DB **مش** رستوك
  المولد. نداء vtable+0x90 (العدّاد) موثوق من CNpc::
  Create (FUN_14005e2e0) — مسار إنشاء الـ NPC بيزود
  عدادات المولد. **متبقي**: مين بينادي restock
  (vtable+0x78 = FUN_14005fb30) عند موت NPC — نبدأ من
  مسار Close/الـ dtor بتاع CNpc (مؤشر المولد +0x100).
- **جديد:** الوحدة 13: **Process الحقيقي
  (FUN_140060b00) + تصحيح معاني الحقول من vtable
  محفور من البيناري**. الاكتشافات:
  (1) **vtable+0x80 مش FUN_14005fc90 مباشرة** — هو
  FUN_140060b00، غلاف بمنطق كامل قبل ما ينادي
  FUN_14005fc90. اتحفر الـ vftable نفسه من
  orig_binaries (0x1400c7fc8، بطريقة بحث qword على
  عنوان FUN_140060b00) — كل السلوتات موثقة في
  NpcGenerator.h.
  (2) **كاتب +0x14 اتشال TBD**: Process نفسه بيكتبه
  = GetInt(8) كل ما مؤقت الـ spawn (FUN_140002700
  على زوج +0x30 interval sec / +0x34 آخر spawn
  sec) يعلّ "due"، ومع إعادة تسليح لو GetInt(7) >
  599 (+0x30 = GetInt(7)+RandGet(GetInt(7))).
  (3) **بوابات Process**: +0x48 != 0 → 0؛ bit1
  (GetInt(0x12)) && +0x1c <= +0x20 → 0؛ +0x1c <=
  +0x18 → 0؛ الـ headroom: (+0x18 - +0x10) <
  budget وإلا 0. البودجت: (budget - +0x10 +
  +0x18) مقصوص على (+0x1c - +0x18) ثم على +0x14.
  (4) **تصحيح أسماء الحقول** (تصرفات متطابقة،
  الديمو والاختبارات اتحدثت): +0x50 = **مُعرّف
  المولد نفسه** (vtable+8 = GetGenId → rec+0x08 →
  مفتاح findGenerator — مش الـ map!)؛ +0x54 =
  **مُعرّف الخريطة** (مفتاح شغل كائن الخريطة في
  FUN_140061040)؛ +0x1c = **سقف الشبكة** (5/6)*(4/6)
  أو 1 (مش step)؛ +0x30 = **فاصل spawn بالثواني**
  (مش X عشوائي). لوج "Error: npc generator [%u] got
  invalid map [%u]!" ترتيبه الأصلي [+0x50][+0x54].
  (5) **vtable slots الصغيرة كلها معروفة دلوقتي**:
  +0x20 = GetAmount (+0x10)، +0x30 = GetGenAmount
  (+0x18)، +0x48 = سقف +0x1c، +0x68 = InRect،
  +0x70 = InArea (FUN_14005f630)، +0x78 = restock
  FUN_14005fb30، +0x88 =FUN_14005f8c0 (spawner
  صفوف DB)، +0x90 = FUN_140060030 (عدّاد آخر بلوج
  "GeneratorID[%u]: m_nGenAmount[%d] >
  m_nAmount[%d]")، +0xa0 = Close.
  (6) التجميعة بتشغّل **السلسلة الحقيقية بالكامل**:
  walk المدير → Process → (مؤقت due؟ → restock
  GetInt(8)) → Generator → سجل 0x38 → loop-back →
  مسار الوحدة 9. الديمو: سقف شبكة 2 ((30/20)*
  (40/20))، فاصل 1 ثانية، رستوك 1 — الاختبار بيشوف
  spawn 1/tick لحد السقف ثم يتوقف. **الرجريشن
  13/13 خضرا** + سموك main.
- **جديد:** الوحدة 12: **CNpcGenerator::Generator
  الحقيقي (FUN_14005fc90، analyst 0x53) + عائلته**
  — الـ cadence المخمّن في التجميعة اتشال. في
  Exe/NpcServer/NpcGenerator.{h,cpp}:
  (1) **Generator(budget)** حرفياً: بوابات (+0x28
  map=0 / +0x48 cap≠0 / budget=0 → 0)، محاولات
  max(1, GetInt(5)*GetInt(4))، probe إما ثابت
  (0xc/0xd) أو عشوائي (GetInt(2)+RandGet(GetInt(4)),
  GetInt(3)+RandGet(GetInt(5)))، FUN_14004cc70 يوقف
  الـ probe (موقع صالح)، FUN_140049310 يرفع علم
  found، **يبني سجل CMsgAiNpcInfo 0x38 بنفس تخطيط
  الوحدة 9 بالظبط** (id+0x00 من FUN_14002b270،
  vcall+0x40 map @+0x04، vtable+8 gen id @+0x08،
  x/y words @+0x14/+0x16، **التاج 1 word@0x18**،
  النوع word@0x1a من GetInt(9) أو الكلاستر، byte
  +0x4c @+0x2c) — تحقق قاطع إن المولد بيرسل نفس
  رسالة الـ DB. العدادات: +0x14--، +0x18++، +0x20++
  لكل spawn ناجح، والبودجت يقفل اللوب. لوج الخمول
  الحرفي من البيناري (GBK): **"cq_generator.id=%u،
  出生点不可站"** (DAT_1400c9af0) بخنق 999ms وشروط
  (لا spawn + attempts>8 + !found).
  (2) **ClusterType (FUN_14005f7e0)**: نوع مرجّح —
  RandGet(100)، أوزان أعمدة 2,4..0x14 وأنواع
  أعمدة **1,3..0x15** (idx*2+1)، إرهاق → 0 →
  Generator يرجع بدري.
  (3) **إعادة التعبئة (FUN_14005fb30)**: +0x10--،
  GetInt(8)، مزامنة +0x18=+0x10 مع اللوجين
  الحرفيين "GeneratorID[%u]: m_nGenAmount[%d] <
  m_nAmount[%d]" و"GeneratorID[%u]: m_nAmount <= 0".
  (4) حقول جديدة موثقة (+0x10/+0x14/+0x18/+0x20/
  +0x24)؛ كاتب +0x14 الأصلي **TBD** (مش في
  FUN_140061040؛ غالباً مشية +0x38 بتاعة العالم)
  — التجميعة بتزرع السقف فيه مؤقتاً.
  (5) **التجميعة اتلمّت على الحقيقي**: glue الـ
  SpawnFromGenerator اتشال؛ التسجيل بيعمل CreateNpc
  مرة (نمط FUN_140032800) وسجل 0x38 بيتلوب عبر
  m_fnSendMsg → HandleAiNpcInfo (seam الـ socket
  loop-back) → مسار الوحدة 9 كامل. الإحصائيات
  بقرأت vcall+0x30 من +0x20 (in-game الحقيقي) و
  vcall+0x48 من cap. **main الحقيقي بيعمل الدورة
  كاملة**: boot → login → "Generator begin." →
  Generator يولد 3 → الإحصائيات تشوفهم. اختبار
  **NPC_GENPROC_OK** جديد + تجميعة محدثة.
- **جديد:** الوحدة 11: **التجميعة الحقيقية** — الـ stub
  المخمّن في main.cpp اتشال واستبدل. ملفات جديدة:
  Exe/NpcServer/NpcAssembly.{h,cpp} (CNpcServerApp) +
  main.cpp حقيقي + tests/npc_assembly_test —
  **NPC_ASSEMBLY_OK**. الترتيب حرفياً من عائلة
  CSocketKernel::Create (FUN_140002xxx): "libevent
  method: %s" → CNpcWorld::Create (FUN_140001210 ctor
  + FUN_140001ba0 socket + اللوج الحرفي "CNpcWorld::
  Create, cannot create NpcServer client socket." عند
  الفشل) → "thread %u created libevent worker thread
  %u" → "NPC Server KernelThread" (KernelTick = 1Hz
  OnTimer). المسار الكامل شغال: state 0 (مفتاح
  0x3ade68b1) → OnConnectOK (FUN_14001c700) → 10s
  "Generator begin." → FUN_14002b380 (مولدات ببودجت
  + مشي AI كل 3 تيكات مع حارسات skip) → FUN_140061040
  (المولد، بجدول GetInt الأصلي: 1 type/0xf cap/0x12
  random-mode/4-8 geometry/0x11 cluster) → FUN_14005d9c0
  + FUN_14005e2e0 (إنشاء CNpc) بمعرفات FUN_14002b270 →
  تيك AI (+0xe0) → dispatch → FUN_140087d50 wander →
  FUN_140086430 steplist عند الوصول → إحصائيات كل 30s.
  مسار الرسالة شغال كامل: CMsgAiNpcInfo (9) →
  CNpc::Create (10) → تسجيل في المدير. ملاحظتان
  حرفيتان مهمتان: (1) FUN_14003ca10 في مسار المولد
  بيبحث بالخانة +0x54 (الـ **type** مش الـ map id) —
  اتأكدنا من الديكمبايل. (2) SpawnNewNpcID عامه عام
  private على CNpcTransform؛ التجميعة بتناديه عبر
  SpawnNewNpcID_External (glue موثق).
- **جديد:** الوحدة 10: **CNpc::Create (FUN_14005e2e0،
  1565 بايت)** حرفياً في Exe/NpcServer/NpcCreate.{h,cpp}
  — كائن CNpcObject كامل 0x158 بأوفستات بايتية
  مستخرجة (+0x80 id، +0x98 map، +0xa0 type، +0x100 gen،
  +0x108..0x118 حقول التحويل — نفس بتاعة CheckTransform/
  Transform، +0x128/+0x12c/+0x130/+0x134 الحمولة،
  +0x1c/+0x20 life، +0x34/+0x38 x/y، +0xa8 speed
  =max(1,val(0x12)*3/1000)، +0xb0=0x3c، +0xac/+0xb4 born
  sec، +0xbc born ms، +0xc0 كائن الاسم، +0xe8..+0xfc
  تصفير 6 dwords)؛ كل المسارات: بوابة id==0/type،
  تهيئة التحويل (0x35/0x36/0x37 + زوج +0x114/+0x118)،
  bit8 من val(0x15) مرتين (+0x84/+0x18=8 ثم فرع
  إعادة قراءة X/Y عبر vt40/vt38 مع FUN_14004ae30)،
  بلوك الاسم (0x27 → FUN_140042b80 + FUN_1400402d0 +
  رقصة refcount)، خريطة مفقودة → vtable+0x18(rec,1) +
  اللوج الحرفي "CNpc::Create(), Create Npc(type:%d,
  name:%s) can't find map(%u) at %s, %d"، مولد مفقود →
  لوج DAT_1400c9620، مولد صناعي FUN_14006a4c0(…,4,4) مع
  مسار رسالة الفشل (FUN_140063b90/c60/c20 +
  FUN_14001c5f0)، vt90/gen + FUN_14001c1c0/fun_14001c220،
  FUN_14005dc80، والإرجاع CONCAT71(uVar13>>8, 1).
  محوّل NpcCreateFromAiRecord بترتيب Process الحرفي.
  tests/npc_create_test — **NPC_CREATE_OK**، رجريشن 11/11
  خضرا.
- **جديد:** الوحدة 9: CMsgAiNpcInfo كاملة (رسالة 0x4e21)
  من NpcServer.exe نفسه (مش من MsgServer): ctor
  FUN_140061220 / dtor FUN_140061270 / Create
  FUN_1400612a0 (بوابة ver==1 + سجل 0x38 بتاج
  word@0x18=1 + ترتيب الحقول الحرفي) / CreateFromBuffer
  FUN_1400613a0 (بوابة التاج) / SetBuffer FUN_140061430 /
  deleting dtor FUN_140061490 / **Process FUN_1400614f0**:
  conn==0→خروج، بحث بالمعرف vtable+0x40 → موجود = لا
  شيء، غير موجود → FUN_14005d9c0 (new CNpc 0x158) →
  FUN_14005e2e0 (CNpc::Create بسجل 0x38، **seam للوحدة
  10**) → فشل: vtable+0xf0(npc+0x10)؛ نجاح: vtable+0x28
  (تسجيل) + لو سجل+0x34≠0 → vtable+0x98. الملفات:
  Exe/NpcServer/MsgAiNpcInfo.{h,cpp} + tests/
  npc_msgainfo_test — **NPC_MSGAINFO_OK**، رجريشن 10/10
  خضرا (8 وحدات + اختبارا DB).
- **جديد:** الوحدة 8: زوج التحويل CNpc::CheckTransform
  (FUN_14005a660) + CNpc::Transform (FUN_14005a3b0) —
  الهوية من نصوص اللوجات الحرفية جواهم ("CNpc::Transform,
  wrong postion (%d, %d)"...) — **مش خطوة AI عامة ولا
  ليهم صلة بـ CNpcWander في الديكمبايل** (تصحيح لتقدير
  الجلسة السابقة). شامل حرفياً: كل البوابات
  (+0xa0/+0x98/+0x100/+0x108/+0x10c≥0x3e9/+0x110/+0x114/
  +0x118/+0x128/+0x12c)، نافذة زمن flag==1 عبر
  FUN_140002480 (start+delta ≤ TimeGet/1000)، MulDiv
  flag==2، بوابة الموضع FUN_140049310 (خريطة vtable
  +0x28/+0x20/+0x18)، بحث النوع (FUN_14001c7a0 →
  FUN_140025be0 → vcall+0x30)، السقف cap، مسح
  +0x114/+0x118/+0x108 عند النجاح، و**FUN_14002b270 =
  CNpcManager::SpawnNewNpcID** (عداد 499999 → لف
  0x61a81 بسلسلة اللوج الحرفية GBK) — الربط مع التيكة
  عبر CNpcAiTick::BindTransform. **NPC_TRANSFORM_OK** +
  رجريشن NpcServer 9/9 خضرا (7 وحدات + اختبارا DB
  القديمان ops 205/207/208 وrecord 201)
- **جديد:** الوحدة 7: CNpcAiTick (FUN_14005ada0 =
  vtable+0xe0) — vtable CNpc اتستخرج كاملاً من
  البيناري @ 0x1400c92f0 عبر RTTI. NPC_AITICK_OK
- **6 وحدات NpcServer مكتملة ومختبرة** (الاختبارات
  القديمة 4 + الجديدة wander/steplist كلها خضرا):
  1. `CNpcWorld::OnTimer` (FUN_14001d390) — آلة الحالة
     كاملة: الترخيص (0x3ade68b1 + المفتاحان الحرفيان)،
     لوجين السيرفر كل 5 ثواني، تيكة العالم كل 0x20
  2. `CNpcManager` (FUN_140061040/npcmanager.cpp) —
     إدارة المولّدات + التيكة كل 3 فرامات
  3. `CNpcGenerator` (CreateNpc) — الأنماط الثابتة/
     العشوائية + فلتر المجموعة + الخطوة الجغرافية
  4. `CNpcGenerator::LoadCluster` (FUN_140060e60) — علم
     0x11 + CGameData<szMonsterClusterTable> (0x18) +
     الاستعلام الحرفي SELECT...LIMIT 1 + لوجات
     0x1d8/0x1e2/0x1ea
  5. **جديد:** `CNpcWander::Step` (FUN_140087d50) — خطوة
     تجوال الوحش: جدول الاتجاهات الثمانية حرفياً
     (dx={0,-1,-1,-1,0,1,1,1}/dy={1,1,0,-1,-1,-1,0,1})،
     بوابة القبول (سالكة/إشغال/حرة/مدى 0x1a=26)، عقدة
     0x28 (due = base + 0x586 قُطر / 1000 مستقيم،
     travel = chebyshev×1000)، فرع الوصول → FUN_140086430
  6. **جديد:** `CNpcStepList::AppendChain`
     (FUN_140086430) — نقل سلسلة العقد لللست @+0x68 مع
     العدّاد @+0x98 وحد 0xfffffffffffffff ورمي
     std::length_error("list<T> too long") الحرفي
- **البيناري الأصلي NpcServer.exe متأكد من وجوده على
  ريموت الريبو المفكك** (orig_binaries/Source/، MD5
  8c5495f4ca35f4693fe78b26b4b6fbd1) — لا حاجة لإعادة
  رفعه
- ملفات الجديد: Exe/NpcServer/{NpcWander,NpcStepList}.
  {h,cpp} + tests/{npc_wander,npc_steplist}_test.cpp
  (التشغيل: g++ -std=c++17 -I. -o /tmp/nw ... والباقي
  بنفس النمط؛ كل binaries قديمة في /tmp لو لسه شغالة)

## 0.1) ترتيب الشغل الجاي (محدَّث)
1. ~~تيكة الـ AI (vcall+0xe0)~~ **مكتملة** و~~FUN_14005a660/
   FUN_14005a3b0~~ **مكتملان** (الوحدة 8 — زوج
   CheckTransform/Transform في
   Exe/NpcServer/NpcTransform.{h,cpp}، مربوطين بـ
   BindTransform، لا صلة بالديكمبايل بـ CNpcWander).
   المتبقي TBD موثق: ذيل FUN_14002a690 (نزع حلقة
   المعرفات عبر FUN_140026b80) — seam فقط.
2. ~~CMsgAiNpcInfo~~ **مكتملة** (الوحدة 9 — الفئة
   داخل NpcServer.exe نفسه: FUN_140061220..1400614f0،
   والـ RTTI في names_final.tsv بتاعة MsgServer كان
   عنوانه مضلل). **الجاي مباشرة:** CNpc::Create
   الحقيقي **FUN_14005e2e0 (1565 بايت)** مع عائلته
   (FUN_14005ce80 ctor 0x158، FUN_14005dc80،
   FUN_14006a4c0، FUN_14004ae30، FUN_14003ca10...)
   — هو seam جاهز في CMsgAiNpcInfo::Process.
3. ~~استبدال main.cpp النموذجي~~ **مكتمل** (الوحدة 11)
   و~~عيلة Process بتاعة المولد (FUN_14005fc90/
   FUN_14005f7e0/FUN_14005fb30)~~ **مكتملة** (الوحدة 12).
4. المتبقي قبل القفل: (أ) **عيلة +0x140**
   (FUN_140069750/696d0/696e0/69960/69bd0/
   69c30/69c80...) — هي اللي تفتح أجسام
   FUN_14005c960/df70/b030 العميقة، مع
   FUN_140058b80/5b9e0/58ca0 وFUN_140065xxx؛
   (ب) FUN_1400580e0/597f0/4cc70/4bff0
   (عيلة حركة الخريطة)؛ (ج) جسم تيكة المستخدم
   FUN_140066820 (زوج 1s)؛ (ج) جسم عيلة
   CAIStrategyMgr العميقة (FUN_140043700 reload،
   FUN_1400476a0 evolve، FUN_1400670d0/e0). بعدها:
   قفل NpcServer والانتقال لـ Loaderhock (الترتيب
   الموثق في الخطة).
- عناوين مفاتيح للفتوة القادمة: FUN_140084300 (إدراج
  اللست)، FUN_1400846d0 (بناء العقدة)، FUN_140081e30،
  FUN_1400824c0 (إشارة الطابور)، FUN_14008d7c0/14008d7e0
  (خريطة الخلية)، FUN_140086ff0/140085ea0 (بتات
  الإشغال)، FUN_1400867a0 (مُساعد CNpc).

> هذا القسم مكتوب خصيصاً عشان أي وكيل يكمل الشغل بدون ما
> يتلغبط. اقرأه كاملاً قبل أي تنفيذ، ثم التفاصيل التاريخية
> تحت.

## 1) القواعد الصارمة (لا تنتهكها أبداً)
- **ممنوع أي كود مخمّن/مصنوع.** كل تنفيذ طبق حرفي للديكمبايل
  (Native-Decompiled) مع توثيق عنوان الدالة الأصلية
  (مثال: `FUN_14002b560`) والأوفستات ونصوص اللوجات
  الحرفية في التعليقات.
- أي جزء ناقص يوثّق كـ `TBD` بعنوانه. لا تخترع.
- قبل كل commit: **كل الاختبارات خضرا**. لا ترفع كود أحمر.
- بعد كل وحدة: commit + push فوراً (أول بأول).

## 2) المسارات الأساسية
| ماذا | أين |
|---|---|
| الريبو (rebuild) | `/app/co_repo` (remote: TQServer-CPP-rebuild؛ توكن GitHub OAuth داخل رابط origin — لو ضاع: أعد ربط GitHub من الوكيل الرئيسي وset في remote) |
| الريبو الرئيسي (الأصول) | `/app/co_decomp` (remote: conquer-online-v6159-decompiled، clone عمومي) |
| الديكمبايل | `/app/co_decomp/Native-Decompiled/<Name>.exe.decompiled.c` |
| فهرس الدوال | `<Name>.exe.index.tsv` (العنوان/الحجم/الحالة) |
| أسماء RTTI | `/app/co_decomp/NameIndex/names_final.tsv` |
| البيناري الأصلي | `/app/co_decomp/orig_binaries/Source/NpcServer.exe` (MD5 8c5495f4ca35f4693fe78b26b4b6fbd1) |
| الدمب المصحح | `sql/original_full/cq_with_plunder_war.sql.gz` |
| ملاحظة git | لو فشل commit: `git -c user.name="Mody Hassan" -c user.email="mody@local" commit ...` |

## 3) الحالة الحالية (لا تكرر شغل مخلص)
- **CQCrossServer: مقفول ✅ كامل** — 7 اختبارات regression
  كلها ALL OK: cross_kernel, cross_league, cross_os_msg,
  cross_plunder_war, cross_connect_ok, cross_socketkernel.
  لا تعيد فتحه إلا لو اختبار كسر.
  المتبقي فيه فقط 16 ملاحظة TBD "جزئي الاستخراج" موثقة
  بعناوينها (معظمها كلمات أوامر إرسال داخلية).
- الأصل مرفوع بالكامل على الريبو الرئيسي (سورس v6159 +
  patch + cq.sql.gz). الـ 7z (791M) وcq.sql الخام (108M)
  فوق حد GitHub — مقصودين بـ .gitignore وموجودين في
  السانبوكس.

## 4) خطتك الفورية: NpcServer.exe (الوحدة 1)
- `Exe/NpcServer/main.cpp` **الحالي stub تمثيلي قديم
  (كود مخمّن) — استبدله بالبورت الحقيقي، لا تبني عليه**.
- الديكمبايل: `NpcServer.exe.decompiled.c` (181,583 سطر،
  7,240 دالة). ابدأ بـ:
  1. **آلة حالة الاتصال بالـ MsgServer**: `FUN_14001c700`
     (سطر ~23690 في الديكمبايل): state=2 @+8،
     `tq::TimeGet(0)/1000` @+0x1c، "Login OK. generator
     monster after %d secs" عبر vcall @+0x10. واعرف
     عائلتها (من يدخل الحالة 1؟ من ينادي state=2؟) عبر
     البحث عن `FUN_14001c7` والدوال المجاورة
     (`InstanceGet @14001c780`، `FUN_14001c790/a0/b0`).
  2. **world_kernel + المولّد** (بعد اللوجن: "Generator
     begin." سطر ~24734) — ابحث عن عائلة
     "Generator active/full/over".
  3. **رسائل AI-NPC**: `CMsgAiNpcInfo@world_kernel`
     (أسماء RTTI جاهزة في names_final.tsv، عناوين
     140067320/140074f20/140082eb0..).
  4. **DLLs الجانبية**: Arenic.dll, Booth.dll,
     Analyst.dll, AntiCheat.dll (ديكمبايلاتها جاهزة).
- نفي البورت: نفس أسلوب CQCrossServer (classes في
  `Exe/NpcServer/`، اختبار `tests/npc_*_test.cpp`، سطر
  البناء يتصرف من أخواته في PORTING_LOG.md).
- **ترتيب البناء للسيرفرات**: g++ مثل سطور الرجريشن في
  PORTING_LOG.md (شوف آخر أمر build كامل هناك).

## 5) بعد NpcServer
1. Loaderhock.exe (الموديول الأخير، الديكمبايل جاهز).
2. الأيقونات/الصور مطابقة للأصل (القاعدة الثابتة).
3. وحوش الكروس سيرفر في الريلم (cq_config المرمّع صف
   149883 هو المرجع القياسي).
4. أي ناقص من conquer.exe بأداة Rea (ريموت morluto/rea) في /app/co_decomp.

## 6) نصائح عدم التلغبط
- الدالة تقرأ بأمر:
  `awk '/Function: NAME @/,/^}$/' <file>.decompiled.c`
- مقاس الدالة قبل القراءة:
  `grep NAME <file>.index.tsv`.
- اعمل grep على نصوص اللوجات الإنجليزية ("Login game",
  "Generator"...) للوصول السريع للمناطق الوظيفية.
- آلية الحفظ: PORTING_LOG.md = سجل تفصيلي لكل جلسة،
  HANDOFF.md = الحالة والخطة، وحدّث القسم ده دايماً.

---

# HANDOFF — نقطة تسليم للأجنت التالي (آخر تحديث: 2026-10-24 متأخراً (جلسة 3) — قاعدة البيانات الكاملة المعدلة مرفوعة في الريبو + خطة موسعة بقرار المالك: NpcServer + RevampedLoader + أيقونات + وحوش الريلام + conquer.exe)

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
- المرجع: /app/co_decomp/Native-Decompiled/MsgServer.exe.decompiled.c + الباينري
  /app/co_decomp/orig_binaries/Source/MsgServer.exe (للتحقق بـ objdump).
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
- **بيئة سانبوكس جديدة (جلسة 24/10 عصراً):** MariaDB اتسطّب
  واشتغل (apt مصادر http→https)، المستخدم `tqserver`/
  `tqpass123` واتعمل، وقاعدة `cq` اتحملت من
  `sql/original_full/cq_with_plunder_war.sql.gz` (صف
  149883 موجود). الاثنين DB-backed (ops 205/207/208 و
  record 201) اشتغلوا وخضرا. لو السانبوكس اتجدد: أعد
  التسطيب/التحميل بنفس الخطوات دي.


## خطة موسعة بقرار المالك (جلسة 2026-10-24 الثالثة — بالترتيب)
1. **[تم ✔]** إصلاح القاعدة: صف cq_config type=149883 (أوقات حرب
   السلب) اتضاف للقاعدة الحية (id=80278) **وللريبو**:
   sql/original_full/cq_with_plunder_war.sql.gz (الدمب الكامل 267
   جدول + الصف، 9.8MB مضغوط، محمّل ومختبر) + sql/patches/
   cq_config_plunder_war_149883.sql (ترقيع لقاعدة موجودة) +
   Docs/DB_SETUP.md. أي قاعدة هدف لازم تتظبط كده.
2. **[TBD — التالي بعد استكمال CQCrossServer]** إكمال CQCrossServer:
   رسائل الليج (LeagueInfo 40066 / LeagueStr 40067 — التحليل
   الكامل في PORTING_LOG جلسة 23:20) ثم LeagueList/LeagueRank/
   LeagueBrick/OSConnectInfo/ServerName/EnterOSUserSocketOpt
   (الجرد في نفس الجلسة).
3. **[TBD]** **NpcServer.exe كامل** — القرار: البورت طبق الأصل.
   الديكمبايل موجود وجاهز: /app/co_decomp/Native-Decompiled/
   NpcServer.exe.decompiled.c (**181,583 سطر** — كبير: يُبورت
   وحدة وحدة زي MsgServer). مجلدنا Exe/NpcServer فيه بس
   vcxproj + main.cpp. **البيناري الأصلي مش موجود في البيئة**
   (ساحة المحادثة القديمة اتمسحت) — للأيقونات والتحقق بـ objdump
   محتاجين البيناري يترفع تاني.
4. **[TBD]** **RevampedLoader.exe** (= "Loaderhock.exe" بتاع
   المالك): الديكمبايل موجود: RevampedLoader.exe.decompiled.c
   (**4,331 سطر** — صغير ومناسب كبداية) + في نفس العائلة
   EpochHook.dll وRevampedHook.dll. يُنشأ مشروع Exe/RevampedLoader
   بورت حرفي. البيناري الأصلي مش موجود (نفس ملاحظة 3).
5. **[TBD]** **الأيقونات/الريسورسز**: مطابقة صور وايقونات
   البرامج للأصل. البيناري الوحيد المتاح حالياً:
   /tmp/orig_src/CQCrossServer.exe (أيقونته تُستخرج بـ wrestool/
   icoutils أو python-pefile). باقي البيناريات (MsgServer/
   NpcServer/Loader/...) مطلوب رفعها من عند المالك.
6. **[TBD]** **وحوش الكروس سيرفر في الريلام**: المطلوب إضافة
   وحوش الخريطة العابرة القارات في القاعدة (cq_monsters؟) —
   يُبحث في الدمب الكامل (الجداول الـ 267) عن جداول الوحوش
   وأعمدة الريلام/الكروس، ويتحقق من CQCrossServer/الديكمبايل
   لو فيه منطق spawn. **لو ناقص باتشات عندنا**: المالك عنده
   ملف conquer.exe (الكلينت) قابل للفك بأداة "Rea" اللي بعتها
   قبل كده — **الأداة والملف مش موجودين في البيئة الحالية
   (المحادثة القديمة اتمسحت) — يُطلب من المالك رفعهما تاني**
   لاستخراج أي packets/assets ناقصة.

**ملاحظة بيئة [محسوبة 2026-10-24]:** المالك رفع الأرشيف
الأصلي Conquer_Online_Source_v6159.7z (829MB) — محفوظ في
/app/co_repo/Conquer_Online_Source_v6159.7z، والبيناريات
مستخرجة في /app/co_repo/orig_binaries/:
Source/{CQCrossServer,MsgServer,NpcServer,RevampedLoader}.exe
+ patch/Conquer.exe (الكلينت) + cq.sql الرسمي الكامل 112MB
(267 جدول — **مفيهوش** صف cq_config 149883: ترقيعنا
sql/patches/ هو الصحيح) + ini السيرفرات (crossshell.ini/
crossconn.ini/config.ini...). **تحقق hash:** CQCrossServer.exe
بالأرشيف md5 028ce85f91b0703ba873dc5cfe762712 = نفس البيناري
المفكوك → كل عناوين الدوال الموثقة في PORTING_LOG صحيحة
للنسخة دي. خطوات 3/5/6 (NpcServer + أيقونات + وحوش
الريلام) كلها متاحة دلوقتي. أداة REA (Reverse Engineer
Anything، MCP من github.com/morluto/rea) مستنسخة في /opt/rea.

## وين وصلنا — CQCrossServer (نظام الكونتري + حرب السلب) ✔ مكتمل (2026-10-24)
- **CCountrySysMgr:** Init الثلاثي (LoadLeagueInfo + التوزيع
  الحرفي للطاقة الاحتياطية + LoadPlunderTimeConfig + LoadPlunderWarInfo)،
  الحالات 0/1/2/4/5/6 كلها منفذة حرفياً (Status/Score/Choose/
  UpdateDate/Broadcast/ProduceFirst) — شوف جلسات 22:55→23:10 في PORTING_LOG.
- **حرب السلب (Plunder War):** آلة الحالات OnTimer
  (FUN_14001a400: 0→1→2→3 ببوابات HHMM)، SignUpPlunderWar
  (FUN_140019e20 بسبع بوابات ولوجات حرفية)، PublishSupportToken
  (FUN_14001d560 على idServerLeague)، بث FUN_140018870
  (خريطة server→country فقط)، الجدولة والاستثناء في الكيرنل (40041).
- **تصحيح TimeGet الحرفي (CQBase.dll @140b82df0):** TimeGet(1)=ثواني
  يونكس، TimeGet(3)=غرابة سنة-1900 محفوظة، TimeGet(4)=HHMMSS.
- **مهم للتشغيل:** الديمبو الأصلي cq.sql **مفيهوش صف type=149883**
  في cq_config (أوقات الحرب: data1=1900 signup end، data2=2000
  بداية، data3=2100 نهاية) — بدونه LoadPlunderTimeConfig بيفشل
  Init. يُضاف يدوياً على أي داتابيز هدف.
- **اختبار شامل:** tests/cross_plunder_war_test.cpp (8 أقسام،
  خضراء) + cross_kernel_test + cross_socket_e2e كلها خضراء.
- **build.sh:** خطوة CQCrossServer بتربط main+CrossKernel+
  CountrySysMgr+MySQLClient+SHA1؛ البيلد الكروس بـ zig لسه
  محتاج بيئة فيها zig (مش متاحة في الساندبوكس الحالي).

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

## تحديث 2026-10-24 — حالة CQCrossServer
- منفذ ومختبر بالكامل: النواة (hello/talk/roster/who/
  disconnect) + رسائل OS (40015/40021/40023/40036/40040) +
  NotifyOSConnect/DisConnect + BroadcastOtherServers + نظام
  الليجات والبلاد (40065/40066 مصححة wire) + PlunderWar
  (40041/40042) + ProcessServerConnectOK (FUN_14001ade0).
- الاختبارات: cross_kernel / cross_league / cross_os_msg /
  cross_plunder_war / cross_connect_ok — كلها ALL OK.
- متبقي في CQCrossServer: FUN_14002c4e0 فقط (13 حالة أوامر
  نصية 0x7562..0x756e) + تدقيق نهائي.
- بعدها حسب الخطة المعتمدة: NpcServer.exe (فولدره شبه فارغ،
  الديكمبايل جاهز في Native-Decompiled) → Loaderhock.exe →
  الأيقونات/الصور مطابقة للأصل → وحوش الكروس في الريلم +
  conquer.exe باداة Rea إن نقص شي.


---

## تحديث 2026-10-24 (قفل CQCrossServer)

**CQCrossServer: مقفول ✅** — كل الدوال الرئيسية منفذة حرفياً
ومختبرة (رجريشن 7/7). الـ TBDs المتبقية (16) موثقة بعناوينها
كلها تفاصيل جزئية الاستخراج.

**الجبهة المفتوحة: NpcServer.exe**
- الديكمبايل: Native-Decompiled/NpcServer.exe.decompiled.c
  (181,583 سطر، 7,240 دالة)، فهرس .index.tsv، أسماء RTTI
  في NameIndex/names_final.tsv (world_kernel::*).
- **main.cpp الحالي هو stub تمثيلي قديم — هيتم استبداله
  بالبورت الحقيقي حسب الآتي:**
  1. آلة حالة الاتصال بالـ MsgServer (FUN_14001c700:
     "Login OK. generator monster after %d secs")
  2. world_kernel + المولّد (Generator) وحلقة الوحوش
  3. رسائل AI-NPC (CMsgAiNpcInfo) وبروتوكولاتها
  4. DLLs الجانبية: Arenic, Booth, Analyst, AntiCheat
