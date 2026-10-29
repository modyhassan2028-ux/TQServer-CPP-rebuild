undefined8 FUN_14050c390(int param_1)
{
  ulonglong uVar1;
  undefined8 uVar2;
  if (-1 < param_1) {
    uVar1 = DAT_140976748 - DAT_140976740 >> 3;
    if (param_1 < (int)uVar1) {
      if (uVar1 <= (ulonglong)(longlong)param_1) {
        _invalid_parameter_noinfo();
      }
                    /* WARNING: Could not recover jumptable at 0x00014050c3db. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar2 = (**(code **)(**(longlong **)(DAT_140976740 + (longlong)param_1 * 8) + 0x10))();
      return uVar2;
    }
  }
  return 0xffffffff;
}
