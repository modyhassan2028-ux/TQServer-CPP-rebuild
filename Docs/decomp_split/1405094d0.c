void FUN_1405094d0(longlong param_1,longlong param_2)
{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  longlong *plVar4;
  uint uVar5;
  longlong lVar6;
  uint *puVar7;
  uVar5 = *(int *)(*(longlong *)(param_1 + 0x20) + 0xb0) + (int)param_2;
  puVar7 = (uint *)(ulonglong)uVar5;
  uVar2 = ((int *)(ulonglong)uVar5)[1];
  iVar3 = uVar2 + *(int *)(ulonglong)uVar5;
  while (iVar3 != 0) {
    lVar6 = 0;
    iVar3 = (int)((ulonglong)uVar2 - 8 >> 1);
    if (0 < iVar3) {
      do {
        uVar1 = *(ushort *)((longlong)puVar7 + lVar6 * 2 + 8);
        if ((uVar1 & 0xf000) == 0xa000) {
          plVar4 = (longlong *)((ulonglong)*puVar7 + param_2 + (ulonglong)(uVar1 & 0xfff));
          *plVar4 = *plVar4 + (param_2 - *(longlong *)(*(longlong *)(param_1 + 0x20) + 0x30));
        }
        lVar6 = lVar6 + 1;
      } while (lVar6 < iVar3);
    }
    puVar7 = (uint *)((longlong)puVar7 + (ulonglong)puVar7[1]);
    uVar2 = puVar7[1];
    iVar3 = uVar2 + *puVar7;
  }
  return;
}
