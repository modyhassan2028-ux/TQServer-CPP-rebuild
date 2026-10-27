# D84 — Appoint to position 0x3de (FUN_1417acda0)

## الهوية
CSyndicateLogic معالج تعيين عضو بمنصب 0x3de
(نائب القائد) مع تتالي خفض شاغل المنصب السابق
إلى 0x26c. ~142 سطرًا. مسار المصدر الأصلي في
لوج CHECKF: `...\syndicatelogic.cpp`.

## RAW
1. szAccept==0 → log CHECKF "szAccept" (المسار
   الحرفي) → return 0.
2. actor = FindUserById(consumer[0x18], idActor)؛
   0 → return 0.
3. !IsValid(actor) → return 0.
4. synId = GetSynId(actor)؛ 0 → return.
5. pSyn = FindSyn([0x10], synId)؛ 0 → return 0.
6. target = FindUserByName(users, string(szAccept))؛
   0 → return 0.
7. !IsOnline(target) → كلام vt+0x18(consumer, idActor,
   STR_SYN_APPOINT_TARGET_OFFLINE) → return.
8. GetId(target)==idActor → return (لا تعيين ذاتي).
9. GetSynId(target) != synId → return.
10. HasFlag786960(target) → return.
11. GetRank(target) >= 0x3de → return.
12. count = RankCount(pSyn,0x3de); max = RankMax(pSyn,0x3de):
    - count >= max → كلام vt+0x18(..., STR_POSITION_FULL,
      0x3de) → return 0.
    - وإلا كتلة التعيين:
      a. HasSubRank(target) → ClearSubRank(target, 0)
      b. SetMemberRank(pSyn, target, 0x3de)
      c. uVar5 = vt+0x328(consumer, synId)
      d. RecordUpdate([0x10], target, pSyn, uVar5)
      e. كلام STR_APPOINT_SUCCESS: الاسم =
         GetActorName(actor)؛ snprintf(buf,0x400,fmt,name)؛
         vt+0x88(consumer, synId, buf, 0)
      f. MsgCtor(msg)؛ MsgAppend(msg, 0x27, 0x3de, uVar5, 0)
         → ok → vt+8(consumer, idActor, msg)
      g. تتالي الشاغل السابق: HasOldPos(target) →
         oldId = GetOldId(target)؛ old = FindUserById(oldId)؛
         إن وُجد && GetSynId(old)==synId &&
         GetRank(old)<0x26c && !HasFlag786960(old):
         RankSetMisc(pSyn, old, 200, uVar5, 0)؛
         SetMemberRank(pSyn, old, 0x26c)؛
         RecordUpdate([0x10], old, pSyn, uVar5)
      h. RankSetMisc(pSyn, target, 0x263, uVar5, 0)
      i. SynSave(pSyn)؛ MsgDtor(msg)؛ return 1

## الاختبار
كل حارس + النجاح الكامل + التتالي + الوضع الممتلئ.
