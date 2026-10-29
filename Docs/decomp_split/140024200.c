undefined8 FUN_140024200(longlong param_1)
{
  undefined8 uVar1;
  undefined8 *puVar2;
  if ((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18) & 0xfffffffffffffff8U) == 0) {
    log_InlineLogERROR(&DAT_1406d9c10);
    return 0;
  }
  puVar2 = (undefined8 *)FUN_140023c10();
  uVar1 = *puVar2;
  if ((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18) & 0xfffffffffffffff8U) != 0) {
    *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + -8;
  }
  return uVar1;
}
