void FUN_14002adc0(longlong param_1)
{
  ulong uVar1;
  if (DAT_140975948 == 0) {
    log_InlineLogERROR(&DAT_1406d9c10);
    return;
  }
  if (*(int *)(param_1 + 0xc) != 0) {
    uVar1 = tq::TimeGet(0);
    if ((uint)(*(int *)(param_1 + 0xc) + *(int *)(param_1 + 8)) <= uVar1 / 1000) {
      *(undefined4 *)(param_1 + 0xc) = 0;
      *(undefined4 *)(param_1 + 8) = 0;
      FUN_14002a5a0(param_1);
    }
  }
  return;
}
