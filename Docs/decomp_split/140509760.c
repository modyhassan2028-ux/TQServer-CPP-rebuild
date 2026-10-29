undefined8 FUN_140509760(longlong param_1,short *param_2,uint param_3)
{
  ushort uVar1;
  uint uVar2;
  ulonglong uVar3;
  int *piVar4;
  int iVar5;
  if (((0x3f < param_3) && (*(short **)(param_1 + 0x18) = param_2, *param_2 == 0x5a4d)) &&
     ((longlong)*(int *)(param_2 + 0x1e) + 0x108U <= (ulonglong)param_3)) {
    uVar2 = *(int *)(param_2 + 0x1e) + (int)param_2;
    uVar3 = (ulonglong)uVar2;
    *(ulonglong *)(param_1 + 0x20) = uVar3;
    if (((*(int *)(ulonglong)uVar2 == 0x4550) &&
        (uVar1 = *(ushort *)((longlong)(ulonglong)uVar2 + 0x16), (uVar1 & 0x2000) != 0)) &&
       (((uVar1 & 2) != 0 && (*(short *)(uVar3 + 0x14) == 0xf0)))) {
      iVar5 = 0;
      *(longlong *)(param_1 + 0x28) = (longlong)(int)uVar2 + 0x108;
      if (*(short *)(uVar3 + 6) != 0) {
        piVar4 = (int *)((longlong)(int)uVar2 + 0x118);
        do {
          if (param_3 < (uint)(piVar4[1] + *piVar4)) {
            return 0;
          }
          iVar5 = iVar5 + 1;
          piVar4 = piVar4 + 10;
        } while (iVar5 < (int)(uint)*(ushort *)(*(longlong *)(param_1 + 0x20) + 6));
      }
      return 1;
    }
  }
  return 0;
}
