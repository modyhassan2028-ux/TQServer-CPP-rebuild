longlong * FUN_140024280(longlong *param_1,longlong *param_2,longlong *param_3,undefined8 param_4)
{
  ulonglong uVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  longlong *local_28;
  ulonglong uStack_20;
  lVar2 = 0;
  uVar1 = param_1[3];
  lVar3 = lVar2;
  if ((param_1[4] - uVar1 & 0xfffffffffffffff8) != 0) {
    if ((ulonglong)param_1[4] < uVar1) {
      _invalid_parameter_noinfo();
    }
    if ((*param_3 == 0) || (*param_3 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    lVar3 = (longlong)(param_3[1] - uVar1) >> 3;
  }
  local_28 = (longlong *)*param_3;
  uStack_20 = param_3[1];
  FUN_140023cc0(param_1,&local_28,1,param_4);
  uVar1 = param_1[3];
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  param_1 = (longlong *)*param_1;
  local_28 = param_1;
  uStack_20 = uVar1;
  if (param_1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar4 = lVar2;
  }
  else {
    lVar4 = *param_1;
  }
  uVar1 = uVar1 + lVar3 * 8;
  if (uVar1 <= *(ulonglong *)(lVar4 + 0x20)) {
    if (param_1 != (longlong *)0x0) {
      lVar2 = *param_1;
    }
    if (*(ulonglong *)(lVar2 + 0x18) <= uVar1) goto LAB_140024374;
  }
  _invalid_parameter_noinfo();
LAB_140024374:
  *param_2 = (longlong)local_28;
  param_2[1] = uVar1;
  return param_2;
}
