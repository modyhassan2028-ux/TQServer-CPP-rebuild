# استخدام مرجع Ghidra الجديد (التسميات والـvtable)

مجلد `Docs/reference/NpcServer_Ghidra/` فيه فكّ تجميع كامل لـ **نفس** `NpcServer.exe` (نفس الـimage base
`0x140000000`)، منزّل بترتيب كلاسي: ملف لكل كلاس + `_INDEX.txt` (كل النصوص مع عناوينها) + `_VTABLES.txt`
(كل vftable مع سلوتاته) + `_unnamed_N.cpp` للدوال اللي مفيش لها مالك.

**تأكيد المطابقة:** `CInstance::vftable @ 1400c7340` في `_VTABLES.txt` هو نفس العنوان اللي طلعناه بـ`objdump`
من `0x1400491b0` في D243. الأرقام والعناوين واحدة، فهو نفس البايناري مش نسخة تانية.

## الجداول المولّدة (متجددّة آليًا)

```bash
python3 tools/build_name_map.py
# functions: 7053 (named 3479, unnamed 3574)
# vtable slots: 1079
```
- `Docs/FUN_NAME_MAP.tsv` — `address  name  signature` لكل 7053 دالة.
- `Docs/VTABLE_SLOTS.tsv` — `vtable  class  slot  function` لكل 1079 سلوت.

## تلات استخدامات (بالترتيب)

### 1. تحويل نداء virtual لمسمى
عندك في الجسم `(**(code **)(*plVar + 0x268))(...)`. اعرف كلاس الكائن من `FUN_NAME_MAP.tsv` أو من الـ`__FILE__`،
وبعدها:
```bash
awk -F'\t' '$2=="CInstance" && $3=="0x268"' Docs/VTABLE_SLOTS.tsv
```
لو رجع اسم → ده الاسم الأصلي للدالة، ودوّر عليه في `FUN_NAME_MAP.tsv` تاخد عنوانه، وروح للجسم بتاعه.

### 2. اسم الكلاس/الملف الأصلي
```bash
grep -P "^14003cd80\t" Docs/FUN_NAME_MAP.tsv      # → FUN_14003cd80  (لسه مش مسمّى)
grep -rn "@ 14003ca10 " Docs/reference/NpcServer_Ghidra/*.cpp
```
ولو الدالة بتستخدم literal مسار (زي `f:\version\cqserver-78.0.11-1204\npcserver\npckernel\mapmanager.cpp`)
فالمسار ده يثبّت مكان الملف في شجرة المصدر.

### 3. نص لوج بعنوانه
`_INDEX.txt` فيه `address  text` لكل النصوص. لو الجسم بيبعت `&DAT_1400be0b0` كوسيط لوج، ابحث عن العنوان:
```bash
grep -n "1400be0b0" Docs/reference/NpcServer_Ghidra/_INDEX.txt
```

## قواعد الاستخدام

1. **الجسم يفضل منقول من المصدر الأول** (`NpcServer.exe.decompiled.c`) اللي بنشتغل منه من D1. المرجع الجديد
   للـ**أسماء والعناوين والـvtables والـprototypes**، ومصدر تاني للمقارنة لو حصل غموض في جسم.
2. لو الاتنين اختلفوا في **الشكل** (أسماء متغيرات، ترتيب تعبيرات) مفيش مشكلة — دي فروق ديكمبايلر.
   لو اختلفوا في **السلوك** (نداء زيادة، ترتيب عمليات) → ده إنذار: راجع الـlisting بـ`objdump` قبل أي حكم.
3. الـ3574 دالة غير مسمّاة هي نفسها الأجسام اللي عندنا بـ`FUN_` — مفيش اسم مستتر وراها، فمتضيّعش وقت تدوّر.
4. أي جسم بننقله وله اسم في `FUN_NAME_MAP.tsv`، الاسم ده يتحط في تعليق الجسم وفي التوثيق فورًا
   (زي `// 0x14003ca10 - CMapManager::FindMap`).
