void FUN_140023cc0(longlong param_1,longlong param_2,ulonglong param_3,undefined8 *param_4)
{
  void *pvVar1;
  undefined8 uVar2;
  void *_Dst;
  undefined8 uVar3;
  longlong lVar4;
  ulonglong uVar5;
  undefined8 *puVar6;
  longlong lVar7;
  rsize_t rVar8;
  ulonglong uVar9;
  ulonglong uVar10;
  undefined8 *puVar11;
  lVar4 = *(longlong *)(param_1 + 0x18);
  if (lVar4 == 0) {
    uVar5 = 0;
  }
  else {
    uVar5 = *(longlong *)(param_1 + 0x28) - lVar4 >> 3;
  }
  uVar9 = 0;
  if (param_3 != 0) {
    lVar7 = *(longlong *)(param_1 + 0x20);
    lVar4 = lVar7 - lVar4 >> 3;
    if (0x1fffffffffffffffU - lVar4 < param_3) {
                    /* WARNING: Subroutine does not return */
      FUN_14001f810();
    }
    uVar10 = param_3 + lVar4;
    if (uVar5 < uVar10) {
      if (uVar5 <= 0x1fffffffffffffff - (uVar5 >> 1)) {
        uVar9 = uVar5 + (uVar5 >> 1);
      }
      if (uVar9 < uVar10) {
        uVar9 = uVar10;
      }
      _Dst = (void *)FUN_1400223a0(param_1 + 0x10,uVar9);
      lVar4 = *(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18) >> 3;
      puVar6 = (undefined8 *)((longlong)_Dst + lVar4 * 8);
      for (uVar5 = param_3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *puVar6 = *param_4;
        puVar6 = puVar6 + 1;
      }
      lVar7 = *(longlong *)(param_2 + 8) - (longlong)*(void **)(param_1 + 0x18) >> 3;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 3;
        memmove_s(_Dst,rVar8,*(void **)(param_1 + 0x18),rVar8);
      }
      lVar7 = *(longlong *)(param_1 + 0x20) - (longlong)*(void **)(param_2 + 8) >> 3;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 3;
        memmove_s((void *)((longlong)_Dst + (lVar4 + param_3) * 8),rVar8,*(void **)(param_2 + 8),
                  rVar8);
      }
      pvVar1 = *(void **)(param_1 + 0x18);
      lVar4 = *(longlong *)(param_1 + 0x20);
      if (pvVar1 != (void *)0x0) {
        operator_delete(pvVar1);
      }
      *(void **)(param_1 + 0x28) = (void *)((longlong)_Dst + uVar9 * 8);
      *(void **)(param_1 + 0x20) =
           (void *)((longlong)_Dst + (param_3 + (lVar4 - (longlong)pvVar1 >> 3)) * 8);
      *(void **)(param_1 + 0x18) = _Dst;
    }
    else if ((ulonglong)(lVar7 - *(longlong *)(param_2 + 8) >> 3) < param_3) {
      uVar2 = *param_4;
      FUN_140023700(param_1,*(longlong *)(param_2 + 8),lVar7,
                    *(longlong *)(param_2 + 8) + param_3 * 8);
      puVar6 = *(undefined8 **)(param_1 + 0x20);
      for (lVar4 = param_3 - ((longlong)puVar6 - *(longlong *)(param_2 + 8) >> 3); lVar4 != 0;
          lVar4 = lVar4 + -1) {
        *puVar6 = uVar2;
        puVar6 = puVar6 + 1;
      }
      *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + param_3 * 8;
      lVar4 = *(longlong *)(param_1 + 0x20);
      for (puVar6 = *(undefined8 **)(param_2 + 8); puVar6 != (undefined8 *)(lVar4 + param_3 * -8);
          puVar6 = puVar6 + 1) {
        *puVar6 = uVar2;
      }
    }
    else {
      uVar2 = *param_4;
      lVar4 = lVar7 + param_3 * -8;
      uVar3 = FUN_140023700(param_1,lVar4,lVar7,lVar7);
      *(undefined8 *)(param_1 + 0x20) = uVar3;
      FUN_140022d80(*(undefined8 *)(param_2 + 8),lVar4,lVar7);
      puVar11 = *(undefined8 **)(param_2 + 8);
      puVar6 = puVar11 + param_3;
      for (; puVar11 != puVar6; puVar11 = puVar11 + 1) {
        *puVar11 = uVar2;
      }
    }
  }
  return;
}
