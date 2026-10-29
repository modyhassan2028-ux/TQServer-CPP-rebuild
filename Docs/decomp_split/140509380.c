int FUN_140509380(int *param_1,ulonglong param_2)
{
  char cVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  longlong lVar5;
  uint uVar6;
  ulonglong uVar7;
  char *pcVar8;
  longlong lVar9;
  ulonglong uVar10;
  int iVar11;
  ulonglong uVar12;
  lVar5 = *(longlong *)(param_1 + 8);
  if (((*(int *)(lVar5 + 0x88) == 0) || (*(int *)(lVar5 + 0x8c) == 0)) || (*param_1 == 0)) {
    return 0;
  }
  iVar3 = param_1[4];
  uVar4 = *(uint *)(lVar5 + 0x88);
  uVar7 = (ulonglong)(iVar3 + uVar4);
  if ((param_2 & 0xffff0000) == 0) {
    uVar6 = 0xffffU - *(int *)((ulonglong)(iVar3 + uVar4) + 0x10) & (uint)param_2;
LAB_14050949f:
    if (((-1 < (int)uVar6) && ((int)uVar6 < *(int *)(uVar7 + 0x14))) &&
       ((uVar6 = *(uint *)((ulonglong)(uint)(*(int *)(uVar7 + 0x1c) + iVar3) +
                          (longlong)(int)uVar6 * 4), uVar6 <= uVar4 ||
        (*(int *)(lVar5 + 0x8c) + uVar4 <= uVar6)))) {
      return param_1[4] + uVar6;
    }
  }
  else {
    uVar10 = 0;
    uVar12 = uVar10;
    if (0 < (longlong)*(int *)(uVar7 + 0x18)) {
      do {
        pcVar8 = (char *)(ulonglong)
                         (uint)(*(int *)((ulonglong)(uint)(*(int *)(uVar7 + 0x20) + iVar3) +
                                        uVar10 * 4) + iVar3);
        lVar9 = param_2 - (longlong)pcVar8;
        do {
          cVar1 = *pcVar8;
          cVar2 = pcVar8[lVar9];
          if (cVar1 != cVar2) break;
          pcVar8 = pcVar8 + 1;
        } while (cVar2 != '\0');
        iVar11 = (int)uVar12;
        if (cVar1 == cVar2) {
          if (iVar11 < 0) {
            return 0;
          }
          uVar6 = (uint)*(ushort *)
                         ((ulonglong)(uint)(*(int *)(uVar7 + 0x24) + iVar3) + (longlong)iVar11 * 2);
          goto LAB_14050949f;
        }
        uVar10 = uVar10 + 1;
        uVar12 = (ulonglong)(iVar11 + 1);
      } while ((longlong)uVar10 < (longlong)*(int *)(uVar7 + 0x18));
    }
  }
  return 0;
}
