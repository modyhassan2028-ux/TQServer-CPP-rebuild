# M71 — دليل تنفيذ إغلاق خريطة الهاش (f880 + fd50 + 10970)
> هذا دليل تنفيذ مُحقق: كل الأجسام أدناه مُقروءة بالكامل من
> MsgServer.exe.decompiled.c (كل سطر f880 الثلاثة في سجل المحادثة)،
> وكل التبعيات منفذة ومختبرة (M67-M70). لا يحتاج أي بحث إضافي.

## الحاوية (تخطيط حرفي مُحقق — يطابق M67 وM68 وM70 معاً)
```
+0x10  قائمة M68 المدمجة: first@+0x10, END@+0x38, size@+0x40
+0x48  فيكتور دلول M70 (FIRST@+0x60, LAST@+0x68, CAP@+0x70)
+0x78  القناع (mask)            +0x80  عدد الدلول
+0x88  max_load_factor (float)
عقدة الهاش (0x18): next@0, prev@8, key@0x10(int), value@0x14
دلو (0x10): slot0@+0, رأس السلسلة@+8 — سلسلة الدلو i = [head[i], head[i+1])
القائمة دائرية عبر END (self-linked عند الفراغ — نفس فيكسچر M68)
```

## الدوال المنفذة الجاهزة للاستدعاء (أسماء في Port/)
- `HashProbeFind(uint8_t* pC, void** ppOut, int32_t* pKey)` — M67 (db40)
- `HashListEmplace(pList, ppOut, ppIt, pKeyBlk)` — M68 (cae0)
- `HashListErase(pList, ppOut, ppIt)` — M68 (cbd0)
- `HashListTransfer(pList1, ppIt1, pList2, ppIt2)` — M68 (f1c0)
- `HashListBump / HashListNodeNew` — M68 (a300/a280)
- `VecClearRefill(SVec*, qN, pVal)` — M70 (f4a0) | `VecInsertFront` — M70 (eab0)
- pList للحاوية = container+0x10 (قائمة M68 أولها@pList+0)

## FUN_14000f880 (الإدراج الكامل 183 سطر) — البنية الحرفية
1. **الهاش:** `ldiv(key,0x1f31d); rem*0x41a7 + quot*-0xb14; <0 ? +0x7fffffff;
   idx = h & mask; if (count<=idx) idx += -1-(mask>>1)` (المحاذاة الفردية)
2. **المشي الخلفي:** lVar8 = head[idx+1]، وفي كل دورة:
   `if (lVar8 == head[idx]) goto INSERT` (الفاصل فاضي)
   ثم `lVar8 = *(lVar8+8)` (خطوة prev) ثم فحص `key == lVar8->key@0x10`
   → تكرار حتى: فاصل مفرّغ (goto) أو مفتاح مكرر (خروج while)
3. **مسار التكرار (dup):** إذا hint[1] != END: erase للعقدة المُلمَّحة
   (cbd0)؛ inserted=false؛ out = {first captured@الدخول}
4. **مسار الإدراج (LAB_fa44):** position = lStack_60 (آخر lVar8)
   - hint[1]==END (لا تلميح): emplace جديد (cae0) بزوج {first, position}
     ثم hint = مخرج cae0 = {*(pList+0), العقدة الجديدة}
   - تلميح صالح: transfer (f1c0) لعقدة التلميح لموقع {first, position}
5. **حلقة حدود الدلول (المسار الحرج للتحقق):** بينما `head[idx]==position`:
   اكتب `bucket[idx] = {local_58, lStack_60}` حيث
   `local_58 = *(*(hint[0]))` (المشي الدائري: hint[0]->next->next)
   ثم idx--, حتى idx==0. **ملاحظة تحقق:** لاول إدراج في حاوية
   فارغة تكتب {END, END} = لا تغيير — يجب التحقق بفحص هل head
   يجب أن يشير للعقدة الجديدة عبر خطوة المشي (المقصود: تحديث
   حدود الدلول الفارغة التي تشترك في نفس الحد)
6. **محفز إعادة التجزئة:** `if (max_load <= (float)size / (float)count
   && != )`: نمو ×2 حتى 3 دورات (حارس 0x7fffffffffffffe)،
   قيمة التعبئة = `local_58 = *(*(first))`, `lStack_50 = END` →
   `VecClearRefill(vec@+0x48, newCount+1, pair)`، ثم
   `mask = newCount-1; count = newCount; FUN_14000fd50(container)`
7. **الناتج:** out = {hint[0], hint[1]}, inserted=true (بايت @param_2[2].quot)

## FUN_14000fd50 (إعادة البناء 57 سطر)
حلقة: plVar1 = container+0x10؛ plVar2 = first؛
`while (first != *(END))`: node = first؛ بناء زوج المفتاح
`{node->key@0x10}` (المشي الحرفي 4×SUB84) ثم
`f880(container, out, node+0x10, &keyPair)` — إعادة إدراج كل عقدة
(المكرر: plVar1 = *(container+0x10) يتحدث عبر نجاح الإدراج —
تتبع بيانات الحرفية في السجلات 1400fd50-1400fda0)

## FUN_140010970 (op[] 41 سطر)
`HashProbeFind(pC+0x10, &it, &key)`؛ إذا it[1]==END (miss):
بناء hint = {*(pC+0x10), END} ثم `f880(pC, &it2, &key, &hint)`؛
الناتج النهائي: **it2[1] + 0x14** = مؤشر القيمة للكتابة.

## أسئلة التحقق الثلاثة قبل بدء التنفيذ (كلها قابلة للفحص في دقائق)
1. من يحدّث الخانة +0x10 بعد أول emplace؟ (المرجح: تُزامن تلقائياً عبر
   دائرية END: first == END->next — تحقق بفيكسچر M68 الاختبارية)
2. حلقة حدود الدلول: هل slot0@+0 يُقرأ فعلاً في db40؟ (فيكسچر M67 يضبطه
   صفراً دائماً — إن كان الدلو يقرأ +8 فقط فالكتابة في +0 تجميلية)
3. مسار dup مع تلميح صالح: هل erase يحدث قبل أم بعد إرجاع المكرر؟
   (تسلسل 14000f9xx الحرفي في السجل)

## سيناريوهات الاختبار المطلوبة (M71-HASH-INSERT-OK)
1. إدراج في حاوية فارغة → inserted=true, size=1, probe يجد
2. تكرار نفس المفتاح → inserted=false, size=1, المكرر للعقدة القائمة
3. مفتاحان متصادمان في نفس الدلو → المشي الخلفي يجد كليهما
4. محفز إعادة التجزئة (max_load صغير) → تتضاعف الدلول وprobe يجد
   كل العقد بعد fd50
5. op[] على مفتاح موجود/غائب → كتابة القيمة تُقرأ ثانية
