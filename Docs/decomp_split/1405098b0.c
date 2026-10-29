void FUN_1405098b0(longlong param_1,void *param_2,void *param_3)
{
  ushort uVar1;
  longlong lVar2;
  int iVar3;
  ulonglong uVar4;
  uint uVar5;
  ulonglong uVar6;
  uVar1 = *(ushort *)(*(longlong *)(param_1 + 0x20) + 6);
  memmove(param_2,param_3,
          (longlong)
          (int)(*(int *)(*(longlong *)(param_1 + 0x20) + 0x54) + ((uint)uVar1 + (uint)uVar1 * 4) * 8
               ));
  uVar4 = 0;
  uVar6 = uVar4;
  if (*(short *)(*(longlong *)(param_1 + 0x20) + 6) != 0) {
    do {
      lVar2 = *(longlong *)(param_1 + 0x28);
      iVar3 = *(int *)(uVar4 + 0xc + lVar2);
      if ((iVar3 != 0) && (uVar5 = *(uint *)(uVar4 + 0x10 + lVar2), uVar5 != 0)) {
        memmove((void *)(ulonglong)(uint)(iVar3 + (int)param_2),
                (void *)(ulonglong)(uint)(*(int *)(uVar4 + 0x14 + lVar2) + (int)param_3),
                (ulonglong)uVar5);
      }
      uVar5 = (int)uVar6 + 1;
      uVar4 = uVar4 + 0x28;
      uVar6 = (ulonglong)uVar5;
    } while ((int)uVar5 < (int)(uint)*(ushort *)(*(longlong *)(param_1 + 0x20) + 6));
  }
  *(void **)(param_1 + 0x18) = param_2;
  iVar3 = *(int *)((longlong)param_2 + 0x3c) + (int)param_2;
  *(longlong *)(param_1 + 0x20) = (longlong)iVar3;
  *(longlong *)(param_1 + 0x28) = (longlong)iVar3 + 0x108;
  return;
}
