# D81 — PublishSupportTokenFromMap (FUN_1417c1a90)

## الهوية
`CSyndicateLogic::PublishSupportTokenFromMap(idUser, idLeagueTarget, idTarget, nParam5, param6, param7)`
— الأصل: `f:\version\cqserver-78.0.11-1204\modules\syndicate\src\syndicatelogic.cpp`
~410 سطر مفكك (L132500–L132910). شقيق D80 من جهة الخريطة:
الخريطة تنشر التوكن وتدفع **مال النقابة** (لا eMoney العضو)
ثم تنادي كل الأعضاء المؤهلين (LEAGUE_TOKEN_CALLUP).

## المراحل (RAW)
1. **الحراس**: param_2≠0، param_3≠0، param_4≠0، param_5≠0 — وإلا return.
2. **vt+0x288**: حالة الحرب؛ 0 → STR_DIE + vt+0x18 → return.
3. **vt+0x278**: هل العضو مسجّل؟
   - مسجّل (≠0) → vt+0x4c8؛ 0 → STR_MAP_CANNOT_PUBLISH_TOKEN → return؛
     وإلا vt+0x450(userLeague, idUser, idTarget) → return (كـ 1).
   - غير مسجّل (0) → vt+0x280؛ ≠0 → مسار النشر الكامل.
     vt+0x4c8≠0 → المسار الكامل أيضًا؛ وإلا MAP_CANNOT → return.
4. **المسار الرئيسي**:
   - vt+0x4a8 → userLeague؛ FUN_1417630d0 → pSynLeague ("IF_NOT").
   - FUN_14174bac0(lg,user) → pToken؛ null → FUN_14174bbe0(lg,user,
     param_3, param_4) → "IF_NOT pToken".
   - FUN_1417d4ed0 → tokenId؛ FUN_141764870(mgr,tokenId) → pRow؛
     null → logDB "table:cq_token_type… 0x202d".
   - basic_string؛ FUN_1417b2570(pLogic,idUser,pLeague,pToken,pRow,&str)؛
     0 → dtor + return.
   - pRow->field(4)->vt+0x58 → التكلفة؛ FUN_1417440d0(pLeague) → المال؛
     مال < تكلفة → STR_NOT_ENOUGH_LEAGUE_MONEY_TO_PUBLISH_TOKEN → return.
   - FUN_141744130(pLeague, money-cost, 1)؛ TokenSet(3, tokenId+1, 0)؛
     TokenSet(4, TimeGet(1), 1)؛ field(3)->vt+0x50 → offset؛ حساب الصلاحية.
   - الرسالة 1 (1417d7350 ctor، 1417d4e70 flag، 1417d7650 create) →
     vt+8 إرسال.
   - memset(a78)؛ FUN_141745580(pLeague, buf)؛ تصفير f88/f80/name.
   - vt+0x568(idUser, userLeague) → المفتاح؛ FUN_141766b60(mgr,key,
     &f88, name+0x10, 0x10) و FUN_141766d10(mgr,key,f80,name,0x10).
   - الرسالة 2 (1417d6110 ctor، 1417b5370 award، 1417d61c0
     msgLeagueInfo.Create(plundered=f88/1e6, plunder=f80[0]/1e6)) → vt+8.
   - شجرتان (f60/f18): نمط MSVC-tree الكامل؛ العضو ينجز
     vt+0x268 && vt+0x4d8 && (vt+0x280 || vt+0x4d0) →
     FUN_141732040 إدراج.
   - الرسالة 3 (1417d9000 ctor؛ SSO 0xf؛ vt+0x4b0 timeout؛
     1417d9140 = LeagueToken::Create(1=LEAGUE_TOKEN_CALLUP, idUser,
     tokType, str, timeout)) → الفشل log "IF_OK"؛ النجاح → vt+0x40 بث.
   - السجل: f30=idTarget، f2c=param_5، f28=param_6، f24=param_7،
     _time64، f20=vt+0x4b0+time → FUN_141777de0(mgr[0xb],idUser,
     tokenId,&f30).
   - التنظيف: 1417d9050؛ الشجرتان؛ 1417d6160؛ 1417d73a0؛
     dtor السلسلة → return 1.

## Seams
| الدالة | الدور | الحالة |
|---|---|---|
| FUN_14174bac0/bbe0/d4ed0/64870 | توكن/صف التوكن | موجود |
| FUN_1417b2570 | بناء نص النشر | g_fnMapBuildText (جديد) |
| FUN_1417440d0 | قراءة المال | موجود |
| FUN_141744130 | ضبط المال | g_fnMapSetMoney (جديد) |
| FUN_1417d7650 | إنشاء رسالة التوكن | g_fnMsgTokCreate (جديد) |
| FUN_1417d4e70 | علامة التوكن | موجود |
| FUN_141745580 | معلومات النقابة | موجود |
| FUN_141766b60/d10 | ثنائي الاسمين | موجود (D75) |
| FUN_1417b5370 | علامة الجائزة | موجود (D77) |
| FUN_1417d61c0 | msgLeagueInfo.Create | موجود (D77) |
| FUN_141732040 | إدراج الشجرة | g_fnMapTreeInsert (جديد) |
| FUN_1417d9000/9050 | ctor/dtor LeagueToken | g_fnMsgLtCtor/Dtor (جديد) |
| FUN_1417d9140 | LeagueToken::Create | g_fnMsgLtCreate (جديد) |
| FUN_141777de0 | سجل النشر | g_fnMapPublishRecord (جديد) |
| FUN_1417be5f0 | حجز الاستدعاء | g_fnMapReserveCallup (جديد) |
| vt+0x40 | البث | g_fnMapBroadcast (جديد) |
| vt+0x450 | نشر مسجّل | g_fnMapSignedPublish (جديد) |
| vt+0x4b0 | GetMaxCallupTimeOut | g_fnMapCallupTimeout (جديد) |
| vt+0x268/0x4d8/0x280/0x4d0 | بوابات العضو | فيك vt |

## الاختبار (نمط D78/D80)
الحراس الأربعة؛ STR_DIE؛ فرع المسجّل (MAP_CANNOT + vt+0x450)؛
IF_NOT pSynLeague/pToken؛ سجل cq_token_type 0x202d؛
FUN_1417b2570=0؛ تكلفة>مال → NOT_ENOUGH؛ خصم MoneySet(money-cost)؛
TokenSet(3/4)؛ الرسائل الثلاث + البث + السجل؛ return 1؛ ASan صفر.
