# D83 — CMsgSyndicate::Process (FUN_1417db7b0)

## الهوية
مُوزّع رسائل النقابة الكامل (~430 سطرًا، L153595..154050).
param_1 = CMsgSyndicate (البيانات: [0x408] = بلوك
{?, Action(u16)+4, Target(u32)+8, d3+c, d4+10, d5+14}؛
CStringPacker عند +0x410)، param_2 = idActor،
param_4 = معامل الحوار.

## البنية (RAW)
1. **idActor == 0** → log CHECK "ID_NONE != idActor"
   بالمسار الأصلي `f:\version\...\msg\msgsyndicate.cpp` → return.
2. mgr = FUN_1417b6210().
3. **FUN_1417ac6f0 (بوابة)**: 0 → لا شيء.
4. **FUN_1417ac710 == 0** → كلام STR_DIE عبر
   FUN_1417ac750(mgr, id, str, param_4).
5. وإلا **FUN_1417ac700 != 0 && Action != 6** → لا شيء؛
   غير ذلك المفتاح الكامل:

| Action | الشروط | الاستدعاء |
|---|---|---|
| 1 | tgt≠0, tgt≠id, ac6f0, ac720 | 1417bad50(mgr,id,tgt,p4) |
| 2 | tgt≠0, tgt≠id, ac6f0, ac720 | 1417bb0e0(mgr,id,tgt) |
| 3 | — | vt+0x100(mgr,id) |
| 4 | tgt≠0, tgt≠id, ac6f0 | vt+0x120(mgr,id,tgt) |
| 6 | — | 1417ac820(mgr,id,tgt) |
| 7,8,9,10 | StrAmount≠0 → GetString(0,buf,0x24) | 1417b7850 / vt+0x1b0 / vt+0x1a8 / vt+0x1b8 (id,buf) |
| 0xb | !ac730، tgt ≤ ac7e0 | vt+0x138(mgr,id,tgt) |
| 0xc | — | vt+0x18(mgr,id) |
| 0x14 | !ac730 | 1417ac9c0(mgr,id,data[2]) |
| 0x17 | str | 1417bb500(mgr,id,buf,data[2]) |
| 0x18 | — | 1417aab70(mgr,id,data[3],data[4],data[5]) |
| 0x1b | str(0x100) → strlen<0x100 | AnnounceStrCheck(buf,1)==0 → STR_INVALID_CHARACTER وإلا 1417acc80(mgr,id,buf) |
| 0x1c | str؛ tgt<0x264 && (tgt>0x261 ‖ (tgt>0x1fd && (tgt<0x200 ‖ tgt==0x25a))) | 1417b7ae0(mgr,id,buf,tgt)؛ tgt==0x3de → 1417acda0؛ tgt==1000 → vt+0xe8(...,0)؛ وإلا log "Illegal rank:%d Action:%d" |
| 0x1d | str؛ u=ac7f0≠0؛ data[3]==0 → STR_DENY_APPOINTMENT (ac750 مع ac800) وإلا tgt=data[2]: (tgt<0x1fe ‖ (tgt>0x1ff && ≠0x25a && tgt-0x262>1)) → "Illegal rank" وإلا 1417b7c10(mgr,u,id,tgt) |
| 0x1e | str | 1417b7e70(mgr,id,buf) |
| 0x1f | — | 1417adeb0(mgr,id) |
| 0x20 | — | 1417ae130(mgr,id) |
| 0x21,22,23,24 | str | 1417ae3a0 / 1417ad190(+tgt) / 1417ad790 / 1417adbb0 (id,buf) |
| 0x25 | rank=vt+0xf8(id)؛ u=ac810؛ p=ae630(u)≠0 | بناء ردّ CMsgSyndicate: ctor 1417db2b0 + CMsg::Init؛ hdr {0x1c, 0x453, 0x25, 0,0,0}؛ ثم حسب الرتبة: 0x348/0x352→Set(0x1ff)، 0x370/0x37a→0x1fe، 0x398→0x262، 0x3d4/0x3de→0x263 (كلها: 141797ce0 + snprintf "%d %d %d %d %d" + AddString + len=GetSize+0x1b)؛ rank=1000 → التسلسل السباعي (1000 ثم 0x3de,0x3d4,0x370,0x348,0x2a8,0x25a كل واحد: 141791a50+141797ce0+snprintf+AddString+len)؛ ثم ac7d0(mgr) + vftable + ~CStringPacker |
| 0x26 | — | 1417ae6b0(mgr,id,data[2]) |
| 0x2d | vt+0xf8(id)==0x3de؛ u=ac810؛ p=ae630؛ 1417983e0(p,0) | → ac7d0(mgr) |
| 0x30 | u=ac810؛ p=ae630؛ 14179c700(p,id,tgt) | → STR_SYNDICATE_BACKLIST_ADD_SUCCESS |
| 0x32 | u=ac810؛ p=ae630؛ 14179c820(p,id,tgt) | → STR_SYNDICATE_BACKLIST_REMOVE_SUCCESS |

## Seams (25+)
g_fnM83* — كل مساعد: GetMgr(1417b6210)، GateA(ac6f0)،
InWar(ac710)، GateB(ac700)، GateC(ac720)، Talk(ac750)،
GetStr/StrMgr، WarOpen(ac730)، MaxRank(ac7e0)،
TargetUser(ac7f0)، TalkArg(ac800)، LockA(ac810)،
UnkAc430(ac430)، Unlock(ac7d0)، FindByUser(ae630)،
RankSet(141797ce0)، RankAdd(141791a50)، vt+0xf8/0x18/0xe8/
0x100/0x120/0x138/0x1a8/0x1b0/0x1b8، دوال الحالة
(bad50, bb0e0, ac820, b7850, ac9c0, bb500, aab70, acc80,
b7ae0, acda0, b7c10, b7e70, adeb0, ae130, ae3a0, ad190,
ad790, adbb0, ae6b0, 983e0, 9c700, 9c820)،
CMsgSyndicate ctor(1417db2b0)، CMsg::Init، CStringPacker
(GetStrAmount/GetString/AddString/GetSize/dtor)،
snprintf، AnnounceStrCheck، log_InlineLogERROR.

## الاختبار
- idActor=0 → لوج CHECK فقط.
- GateA=0 → لا شيء؛ InWar=0 → STR_DIE فقط.
- GateB=1 + Action≠6 → لا شيء؛ Action=6 يعمل حتى مع GateB=1.
- كل مفتاح: المسار الصحيح + الشروط الحارسة
  (tgt=0/tgt=id للتخطي، StrAmount=0 للتخطي).
- 0x1b: فشل AnnounceStrCheck → INVALID_CHARACTER وإلا acc80؛
  طول ≥0x100 → لا شيء.
- 0x1c: التوزيع الثلاثي (نطاق الرتب → b7ae0؛ 0x3de؛ 1000)؛
  خروج الرتبة → "Illegal rank".
- 0x1d: byte0xc=0 → DENY؛ وإلا نطاق الرتب → Illegal أو b7c10.
- 0x25: كل رتبة → رسالة id=0x453 action=0x25 مع السلسلة
  والطول الصحيحين؛ رتبة 1000 → السباعي كاملًا.
- 0x2d/0x30/0x32: الحوارس والكلام.
