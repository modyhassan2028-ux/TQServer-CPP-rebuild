bool FUN_140005d60(longlong param_1)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  if (*(int *)(param_1 + 0x2030) != 2) {
    return false;
  }
  if (*(int *)(param_1 + 0x202c) == 0) {
    return true;
  }
  iVar2 = Ordinal_19(*(undefined8 *)(param_1 + 0x20),param_1 + 0x102c,*(int *)(param_1 + 0x202c),0);
  if (0 < iVar2) {
    iVar3 = *(int *)(param_1 + 0x202c) - iVar2;
    if (0 < iVar3) {
      memcpy((void *)(param_1 + 0x102c),(void *)((longlong)iVar2 + 0x102c + param_1),(longlong)iVar3
            );
    }
    piVar1 = (int *)(param_1 + 0x202c);
    *piVar1 = *piVar1 - iVar2;
    if (*piVar1 < 0) {
      log_InlineLogERROR(&DAT_1406d9c10);
    }
    return *(int *)(param_1 + 0x202c) == 0;
  }
  iVar2 = Ordinal_111();
  if (iVar2 != 0x2746) {
    log_InlineLogERROR("Flush packet failed[%d].");
  }
  if (*(longlong *)(param_1 + 0x20) != -1) {
    Ordinal_3();
  }
  *(undefined4 *)(param_1 + 0x2030) = 0;
  *(undefined4 *)(param_1 + 0x1028) = 0;
  *(undefined4 *)(param_1 + 0x202c) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0xffffffffffffffff;
  return false;
}
