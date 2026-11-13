# طريقة الشغل — دليل تفصيلي لأي وكيل يكمّل على نفس الشغل

> اقرأ هذا الملف كله قبل أي سطر كود. الفكرة باختصار: **ننقل أجسام الدوال من البايناري الأصلي حرفيًا، واحدًا
> واحدًا، بعنوانه، مع سويت يثبته** — مش نعيد كتابة البرنامج بالمعنى.

---

## 0) القاعدة الذهبية

1. **ممنوع تخمين كود.** كل جسم يُنسخ من `Native-Decompiled/NpcServer.exe.decompiled.c` كما هو. لو مش فاهم
   تعليمة، تفتح `objdump` على نفس العنوان وتقرأها، ما تكتبش "حاجة شبه كده".
2. **ممنوع تسمية من عندك.** الاسم `FUN_<addr>` لحد ما تلاقي literal من `__FILE__` في البايناري يثبت المسار
   والاسم الأصلي. ساعتها بس تسمّي الكلاس/الملف بالاسم الأصلي.
3. **كل جسم بيتسجّل بعنوانه** في منيفست + سويت. جسم من غير اختبار = جسم مش موجود.
4. **الاختبارات 6 دورات** على مجموعة موحّدة، تحت ASan+UBSan، قبل أي commit.
5. **الريبو دايمًا متزامن**: commit + push في نفس الدفعة، مش "بعدين".

---

## 1) خريطة المكانين (أهم نقطة يغلطوا فيها)

| المسار | إيه ده | نشتغل فيه؟ |
|---|---|---|
| `modules/npcserver/{src,unattributed}/` | **الشغل الحالي**: بورت حرفي بعنوان كل دالة | ✅ أيوه |
| `tests/npcserver_d*.cpp` + `tools/run_npcserver_suites.sh` | السويتات والرنر | ✅ |
| `npcserver/` (توب ليفل) | إعادة بناء يدوية قديمة (موجة 1) بأسماء مُخمّنة، صفر عناوين `0x140...`، وفيها `// TBD` وقيم مخترعة. بتُبنى من `build.sh` بس مش مصدر حقيقة | ❌ **متعملش فيها** |

الفرق بالأرقام (تاريخ كتابة الملف): القديم 5119 سطر / 86 دالة / **0** عنوان. الجديد 10277 سطر / 587 جسم مربوطة
بعنوانها. نفس البايناري، بس طريقتين مختلفتين تمامًا.

المصادر الأصلية:

```
/app/co_decomp/Native-Decompiled/NpcServer.exe.decompiled.c   ← الجسم الحرفي (4099 دالة)
/app/co_decomp/Native-Decompiled/NpcServer.exe.index.tsv     ← فهرس الدوال
/app/co_decomp/orig_binaries/Source/NpcServer.exe            ← البايناري (لـobjdump)
Docs/NPCSERVER_PATHS.md                                      ← 56 مسار __FILE__ المؤكدة
```

---

## 2) دورة الوحدة (ما تاخد أكتر من عشر دقايق)

اسم الدفعة `D<n>`، وكل دفعة = جسم واحد أو أكثر بنفس العنقود.

### أ. اختيار العنوان
```bash
ls /tmp/ported_addrs.txt            # العناوين المنقولة (المصدر الوحيد للحقيقة)
```
لو الملف مش موجود، أعده من المنيفستات:
```bash
grep -rho '"14[0-9a-f]\{7\}"' modules/npcserver/unattributed/*.cpp | tr -d '"' | sed 's/^/FUN_/' | sort -u > /tmp/ported_addrs.txt
```

### ب. قراءة الجسم وقياس التبعيات
```bash
python3 - <<'PY'
import re
src=open('/app/co_decomp/Native-Decompiled/NpcServer.exe.decompiled.c',errors='ignore').read()
B={}
for p in re.split(r'\n(?=[a-zA-Z_][\w \*]*\bFUN_[0-9a-fA-F]{9}\()', src):
    p=p.split('\n// ====')[0]
    m=re.match(r'[a-zA-Z_][\w \*]*\b(FUN_[0-9a-fA-F]{9})\(', p)
    if m: B[m.group(1)]=p.strip()
print(B['FUN_14003cd80'])
PY
```
بعدها شوف كل نداء: منقول ولا لأ؟
```bash
for a in 14003ca10 1400550f0 14001c7a0 140032e20; do printf "%s " $a; grep -qx "FUN_$a" /tmp/ported_addrs.txt && echo ported || echo missing; done
```
- منقول → نادِه **مباشرة**.
- مش منقول → seam (شوف القسم 4).

### ج. الملف والمكان
- دوال ليها `__FILE__` مؤكد → `modules/npcserver/src/<المسار الأصلي>`.
- دوال من غير أصل → `modules/npcserver/unattributed/<عنقود>.cpp` + هيدر بنفس الاسم.
- كل ملف بيبدأ بتعليق: `// Transcribed from NpcServer.exe; see <header>.`
- كل جسم بياخد سطر تعليق فوقه: `// 0x14003cd80 - <وصف سطر واحد للي بيعمله>`.

### د. المنيفست
```cpp
struct NpcCInstanceEntry { const char* pszAddress; const char* pszKind; void* pfn; };
extern const NpcCInstanceEntry g_aNpcCInstance[];
extern const int g_nNpcCInstance;
```
`pszAddress` = العنوان بدون `FUN_`، و`pszKind` كلمة مفتاحية للسلوك، والسويت بتلفّ على المنيفست (مش على أسماء
دوال) عشان مفيش جسم يتنسى.

### هـ. السويت
`tests/npcserver_d<n>_test.cpp`، بيفحص كل حالة في الجسم:
- كل مسار (نجاح/فشل/حقول صفرية/null).
- سلسلة اللوج الحرفية لو فيه لوج.
- كل offset مكتوب (بمقارنة قيمة الاختبار بالـoffset).
- `assert` على عدد النداءات، مش على "اشتغل وخلاص".

### و. التشغيل والتوثيق والدفع
```bash
sh tools/run_npcserver_suites.sh          # لازم: all NpcServer suites green, six cycles
python3 tools/check_npcserver_paths.py    # لازم: paths listed 56, present 56
git add -A && git commit -m "D###: <سطر واحد>" && git push origin HEAD
```
وممنوع تنسى تحديث: `Docs/PORTING_LOG.md` (جدول + أي اكتشاف)، `HANDOFF.md` (قسم D### بالأرقام والتالي)،
`Docs/REMAINING_ROADMAP.md` (حركة العنقود).

---

## 3) قواعد الترجمة الحرفية (الفروق اللي بتوقع الناس)

| في الديكمبايل | في البورت |
|---|---|
| `undefined8` / `undefined4` / `undefined1` | `unsigned long long` / `unsigned` / `unsigned char` |
| `(**(code **)(*pObj + 0x28))(pObj, a)` | استخرج المؤشر الأول في متغير ثم نادِه — **مش** `(*(T (**)(...))(*pObj + 0x28))` |
| نجاح بترجع `CONCAT71(...,1)` | `return 1;` والفشل `return 0;` |
| `log_InlineLogERROR(&DAT_1400be0b0)` | `g_pfnNpcInlineLogError((const void*)0x1400be0b0)` |
| `log_InlineLogERROR("نص")` | نفس النص **حرفيًا** (السويت بتقارنه بـ`strcmp`) |
| `operator_new(n)` | `g_pfnNpcOperatorNew(n)` |
| `memmove_s` | غلاف حقيقي؛ الحالات المتداخلة تُنقل يدويًا لو الـsanitizer رفض |
|伤的 `LOCK`/`UNLOCK` | `__atomic_add_fetch(..., SEQ_CST)` / `__atomic_sub_fetch` |

**مفخّات اتكشفت فعليًا:**
- cast لمؤشر دالة عبر `(void (**)(...))(*pObj)` بيدereference عنوان الدالة نفسها → SEGV. الصح: متغير مؤشر دالة.
- `operator_delete` للـnode لازم ياخد العنوان الأصلي، والتحرير بالترتيب الموجود في الجسم (مش بالترتيب المنطقي).
- في "copy-then-step" الحركة بتحصل **قبل** تحديث الـiterator.
- قيمة راجعة 8 بايت من دالة الـdecompiler كاتبها `void` (tail call) — اتبع الـlisting.
- vtable slot أحيانًا على مستويين: `(**(code**)(*(long long*)*param_1 + 0x10))(*param_1, i)`.
- **الـlocalات اللي بتتبعت بالعنوان كـpair لازم تكون array.** `long long local_38; long long* local_30;` وبعدها
  `FUN(&local_38)` معناه إن الكالي بيقرا الأربع سلوتس متجاورة. الكمبايلر مش ملزم يرتبهم كده → ASan هيمسك stack
  overflow. الحل: `long long aPair[2];` وبعتها بالعنوان. حصلت فعليًا في D246.
- **الـvtable دايمًا double dereference.** `(**(code **)(*pObj + 0x28))(...)` معناه: اقرأ *قيمة* الفتحة. لو كتبتها
  `(char (*)(...))(*(long long*)pObj + 0x28)` هتـjump على **عنوان** الفتحة نفسها (pc = 0x28 أو pc = عنوان الجدول).
  الصح: `long long* pVt = (long long*)*pObj; pVt[0x28/8]`. حصلت فعليًا في D245.

---

## 4) نظام الـseams (إزاي نكمّل جسم قبل ما نكمّل اللي بيناديه)

الـseam = مؤشر دالة عام في namespace `tq` بيتظبط من السويت، وبيتشال أول ما الجسم الحقيقي ينزل.

```cpp
// العقد في الهيدر — بيقول للناس إن ده مؤقت
extern long long (*g_pfnNpc_14003cd80)(long long pSingleton, unsigned nMapId, unsigned nLow);
// التعريف في الـcpp
long long (*g_pfnNpc_14003cd80)(long long pSingleton, unsigned nMapId, unsigned nLow) = nullptr;
```
قواعد:
1. اسم الـseam = `g_pfnNpc_<العنوان>`، والـcomment جنبه بيقول الهدف.
2. **عندك رخصة 2-4 seams للجسم**؛ أكتر من كده معناها إن العنقود لسه بدري عليه — انزل للتبعيات.
3. الجسم اللي بيستخدم seam مبيبقاش "خلصان" — اكتبه في `REMAINING_ROADMAP.md` كـ"بيتصلح لما X ينزل".
4. لما ينزل: شيل الـseam من الهيدر والـcpp، غيّر النداء للاسم الحقيقي، وشيل الـfake من السويت، وحدّث
   توقّع الاختبار بناءً على الجسم الحقيقي (مش تخلّي الـassert على fake).
   الأداة: `python3 tools/rewire_seams.py` بتساعد في الشيل، بس **راجع** اللي عملته (بتمسح fake من السويت).
5. الـseam اللي بيتغطّى بـfake في السويت = نقطة عمى. ده بالظبط اللي خلّى خطأ في `0x140024340` يعيش (كان بيرمي
   عقدة الـiterator من `pSet[0]` بدل `*(*(pSet+6))`) لحد ما الجسم الحقيقي نزل ووقّع.

---

## 5) الأنماط المتكررة والمولّدات

قبل أي شغل يدوي، اسأل: هو ده نمط بيتكرر؟
- `tools/gen_leaf.py` و`tools/gen_stl_tail.py` بيولّدوا عائلات الأجسام الصغيرة من الـskeleton بعد
  تثبيت المتغيرات (`plVar`/`param_`/الأرقام). 644 جسم اتولّدوا كده في Syndicate، و~600+ في NpcServer.
- الهيستوجرام أداة القرار:
```bash
# اقسم كل الأجسام المتبقية على شكلها (skeleton) وشوف أكبر عائلة
```
لما أكبر عائلة تبقى بـ2 جسم، معناها إن العنقود خلص وأنماطه اتغطّت، والوقت بقى لغيره.

---

## 6) الحاجات المخفية (vtable / RTTI / نصوص)

**vtable من غير فهرس:** لو الاسم `CInstance::vftable` مش موجود في الـindex، متخمّنش. افتح البايناري:
```bash
objdump -d --start-address=0x1400491b0 --stop-address=0x140049260 /app/co_decomp/orig_binaries/Source/NpcServer.exe
# lea 0x7e118(%rip),%rax  # 0x1400c7340   ← mov %rax,(%rbx)  =  عنوان الـvtable
```
نفس الـlisting بيوريك وسايط اللوج (العنوان، السطر، الملف، الدالة) والـflags في النداءات — ده أسرع وأدق من
الديكمبايل في الحاجات دي.

**RTTI:** ابحث عن `.?AV<ClassName>@@` في `.rdata`؛ الـTypeDescriptor قبل النص بـ16 بايت، والـCOL بيشاور عليه في
+0xC. لو مفيش vtable pointer بيشاور على الـCOL، معناها إن الـvtable مش في الصورة بطريقة عادية → ارجع لـobjdump.

**النصوص الحرفية** (خصوصًا GBK الصينية في اللوج): تُنسخ كبايتات من البايناري أو من الديكمبايل، ومتوثّق
العنوان بتاعها في `PORTING_LOG.md`.

---

## 7) الاختبارات

- بنية السويت: `main()` بيضبط الـseams على fakes → بيلفّ على المنيفست → لكل `pszKind` بينفّذ سيناريوهات.
- الـfakes بتسجّل **مين اتنادى وبأي وسايط وبأي ترتيب**، والسويت بتتحقق من الوسايط بالـoffset.
- شجرة/حاوية: اعمل `Count`/`Check` بتمشي الـlinks وتتأكد من `parent` والعقد الحيّة و`count`، ورتّب العقد
  بألوان تمنع الـrebalance المتوقّع عشان النتيجة تكون حتمية.
- السويت لازم تفشل لما الكود يغلط. لو حاسس إن `assert` بيمرّ لأي حال، ده عيب في السويت مش نجاح.
- الأداء: البناء الكامل تقيل، فبدل ما تعيد لينك كل حاجة استخدم `.o` مشترك في `/tmp` (زي `/tmp/clt150.o`) وامسح
  أي بايناري قديم في `/tmp` قبل التشغيل (وإلا هتشوف نتيجة قديمة وتفتكرها نجاح).

---

## 8) التوثيق الإلزامي (4 ملفات + الالتزام بالمسارات)

| الملف | إيه بيتكتب فيه |
|---|---|
| `Docs/PORTING_LOG.md` | قسم لكل دفعة: جدول العنواين + أي اكتشاف بنيوي (offset، vtable، قرار) |
| `HANDOFF.md` | قسم `D### (latest)` بالأرقام والتالي فورًا |
| `Docs/REMAINING_ROADMAP.md` | حركة العنقود: اللي قفل واللي فاضل والترتيب |
| `Docs/NPCSERVER_PATHS.md` + `tools/check_npcserver_paths.py` | 56 مسار من `__FILE__`، لازم 56/56 |
| `DLL_WAVE_INVENTORY.md` | **DLLs فقط (44 ملف)** — NpcServer.exe مش متسجّل فيه، متبحثش فيه عن أرقامه |

كل commit: `D###: <الفعل بالإنجليزي>` وبيتضمن الملفات + السويت + التوثيق مع بعض.

---

## 9) الحالة الحالية (آخر تحديث: D246)

- **591 من 4099 جسم** منقولة، **64 سويت** خضراء، 6 دورات، ASan+UBSan.
- العناقيد المقفولة: `0x14000xxxx` (front/libevent/IOCP)، `0x14007xxxx` (coded streams + logging)،
  `0x14008xxxx` (STL shapes)، `0x14002xxxx` (RBT tree + erase + containers + CInstance + map factory).
- التالي بالترتيب: `0x140024000` (نواة الإدراج) و`0x140023290` (بحث المدى) → `0x1400250e0/0x140025690/0x140025750`
  → `0x140026xxx` … وهكذا صاعدًا في النطاق.
- أوامر التحقق السريع:
```bash
cd /app/co_repo
sh tools/run_npcserver_suites.sh | tail -1
python3 tools/check_npcserver_paths.py
git log --oneline -3
wc -l < /tmp/ported_addrs.txt
```

---

## 10) أول ساعة لأي وكيل جديد

1. اقرأ `HANDOFF.md` + هذا الملف + `Docs/REMAINING_ROADMAP.md`.
2. `sh tools/run_npcserver_suites.sh` وتأكد إنك بتشوف green قبل أي تعديل.
3. ابدأ بالعنوان المكتوب في "التالي" بـ`HANDOFF.md`، مش من أول البايناري.
4. جسم واحد → سويت → 6 دورات → توثيق → commit/push. متعملش 10 أجسام قبل أول تشغيل.
5. لو حاجة غامضة: **objdump**، مش تخمين. ولو لسه غامضة: سيبها seam وسجّلها في `REMAINING_ROADMAP.md`.

**علامة إنك ماشي صح:** كل جسم ليه عنوان، كل عنوان في منيفست، كل منيفست ليه سويت، و`git log` فيه D### متزايد.
**علامة إنك ماشي غلط:** كود بيبان منطقي بس من غير عنوان، أو اسم كلاس من تأليفك، أو سويت بتمرّ من غير ما تتحقق من وسايط.
