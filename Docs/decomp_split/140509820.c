int FUN_140509820(longlong param_1)
{
  int iVar1;
  longlong lVar2;
  int iVar3;
  ulonglong uVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  lVar2 = *(longlong *)(param_1 + 0x20);
  if (lVar2 != 0) {
    iVar1 = *(int *)(lVar2 + 0x38);
    uVar4 = (ulonglong)*(ushort *)(lVar2 + 6);
    iVar5 = ((*(int *)(lVar2 + 0x54) + -1 + iVar1) / iVar1) * iVar1;
    if (*(ushort *)(lVar2 + 6) != 0) {
      piVar7 = (int *)(*(longlong *)(param_1 + 0x28) + 0xc);
      piVar6 = (int *)(*(longlong *)(param_1 + 0x28) + 0x10);
      do {
        iVar3 = piVar6[-2];
        if (piVar6[-2] < *piVar6) {
          iVar3 = *piVar6;
        }
        iVar3 = ((iVar3 + *piVar7 + -1 + iVar1) / iVar1) * iVar1;
        if (iVar5 < iVar3) {
          iVar5 = iVar3;
        }
        piVar6 = piVar6 + 10;
        piVar7 = piVar7 + 10;
        uVar4 = uVar4 - 1;
      } while (uVar4 != 0);
    }
    return iVar5;
  }
  return 0;
}
