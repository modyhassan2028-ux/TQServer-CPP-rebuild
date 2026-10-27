# D82 — AwardPrizeVlmOrCross (FUN_1417c3ed0)

## الهوية
`CSyndicateLogic::AwardPrizeVlmOrCross(param_1, vecSynID, bitsetIter, bCross)`
— السجل الأصلي يسمّيها حرفيًا:
"CSyndicateLogic::AwardPrizeVlmOrCross. bCross && vecSynID.size() != vecBSelf.size()"
~325 سطر مفكك (L134045–L134365).

## البنية (RAW)
1. **الحارس**: `vecSynID.size() != vecBSelf.size()` → log ثم return.
   (vecSynID = حاوية uint {anchor, begin[3], end[4], cap[5]}؛
   param_3 = مكرر bitset نمط MSVC {proxy[0], wordPtr[1], bitIdx[2],
   beginData[6], endData[7]}).
2. **الحلقة**: `do {...} while (uVar16 < 8)` — حتى 8 مراتب
   (rank = uVar16 = 1..8، ويُستخدم فهرسًا للجداول).
3. **لكل تكرار**:
   - `puVar12 == vecSynID.end()` → return.
   - نسخ نهاية bitset: (anchor=*p3, word=p3[6], bit=0) ثم
     FUN_141741c50 (seek بمقدار p3[2]).
   - `(word == نسخة_النهاية) && (bit == نسخة_النهاية)` → return.
   - uVar16++ و rank++.
   - `if (*puVar12 != 0)`:
     - **bCross**: فحص البتة `*word & (1 << (bit & 0x1f))`
       — صفر → تخطَّ (LAB_1417c449c).
     - FUN_1417cad00(param_1[2], synId) → pSyn؛ null →
       log "SynID[%u] is not exist".
     - **جداول الجوائز** (مستخرجة من .rdata الأصلية):
       | rank | normal money | cross money | normal emoney | cross emoney |
       |---|---|---|---|---|
       | 1 | 12000 | 100000 | 3000 | 10000 |
       | 2 | 10000 | 80000 | 2000 | 8000 |
       | 3 | 8000 | 60000 | 1000 | 6000 |
       | 4 | 6500 | 50000 | 600 | 5000 |
       | 5 | 5000 | 40000 | 500 | 4000 |
       | 6 | 4000 | 30000 | 400 | 3000 |
       | 7 | 3000 | 20000 | 300 | 2000 |
       | 8 | 2000 | 10000 | 200 | 1000 |
       (cross money تُقرأ من DAT_1418347c0+4+rank*4 والبقية
       +rank*4؛ المال يُضرب ×10000 عند التطبيق.)
     - **المال**: uVar4 = money*10000 → FUN_14179bf80(pSyn, uVar4)
       → نجاح → FUN_14178f470 (اسم النقابة) + MyLogSave
       "gmlog/synvlmaward" (bCross=0) أو "gmlog/syncrossvlmaward"
       "Syn:%s[%u] Rank[%d] Get money %u".
     - **الإيموني**: cur = FUN_14178f550(pSyn)؛ new = cur +
       emoneyVal؛ `new < 1000000000` →
       vt+0x350(param_1[1], 0x2b, 0, FUN_14178f270(pSyn)) —
       رزيمة بتغيّر الإيموني بالقيمة القديمة →
       FUN_14178fa70(pSyn, new) → فشل → تخطي اللوج →
       نجاح → MyLogSave "Get emoney %u" (حسب bCross).
     - **الكلام**: bCross → STR_CROSS_VLM_AWARD وإلا
       STR_VLM_AWARD؛ _snprintf(buf, 0x400, fmt, emoneyVal,
       moneyVal)؛ vt+0x40(param_1, synId, buf, 0) بثّ للنقابة.
   - **LAB_1417c449c**: puVar12++ و FUN_141741730 (تقدّم المكرر:
     bit<0x1f ? bit++ : {word+=4; bit=0}).

## المساعدات (seams)
| الدالة | الدور |
|---|---|
| FUN_1417cad00 | g_fnVlmFindSyn — إيجاد النقابة |
| FUN_14179bf80 | g_fnVlmAddMoney — إضافة المال |
| FUN_14178f470 | g_fnVlmSynName — الاسم للّوج |
| FUN_14178f550 | g_fnVlmGetEmoney |
| FUN_14178f270 | g_fnVlmEmoneyField — معامل رزيمة 0x2b |
| FUN_14178fa70 | g_fnVlmSetEmoney |
| FUN_141741730 | g_fnVlmBitAdv — تقدّم المكرر (RAW: bit<0x1f? bit++ : word+=4,bit=0) |
| FUN_141741c50 | g_fnVlmBitSeek — seek(n) (RAW: word += ((bit+n)>>5)*4; bit=(bit+n)&0x1f) |
| vt+0x350 | g_fnVlmSendMsg — الرزيمة 0x2b |
| vt+0x40 (على *param_1) | g_fnVlmBroadcast |
| MyLogSave | g_fnVlmMyLogSave(file, fmt, ...) |
| GetStr/theInstance | g_fnVlmGetStr / g_fnVlmStrMgr |
| _snprintf | g_fnVlmSnprintf(buf, 0x400, fmt, a, b) |

## الاختبار
- الحارس: size مختلفة → log + بدون أي جائزة.
- 8 نقابات، بتات bitset: النقابة ذات البتة الصفرية (bCross) تُتخطى.
- synId=0 يُتخطى (لا بحث ولا جائزة).
- null pSyn → log "is not exist".
- rank n → مال = الجدول[n]*10000 + emoney = الجدول[n]
  (فحص قيم rank1 وrank8 وbCross معاً).
- فشل SetEmoney → لا "Get emoney" log لكن الكلام يبث.
- emoney >= 1e9 → تخطي المال/اللوج إلى الكلام مباشرة.
- MyLogSave بالملف الصحيح (synvlmaward مقابل syncrossvlmaward).
- الكلام: STR_VLM_AWARD أو STR_CROSS_VLM_AWARD + بث vt+0x40.
- 8 تكرارات كحد أقصى؛ بتات المكرر تتقدم عبر حدود الكلمات
  (word+=4 عند bit=0x1f).
