ulonglong FUN_140023c10(longlong *param_1)
{
  ulonglong uVar1;
  longlong lVar2;
  longlong lVar3;
  uVar1 = param_1[4];
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  param_1 = (longlong *)*param_1;
  lVar3 = 0;
  if (param_1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar2 = lVar3;
  }
  else {
    lVar2 = *param_1;
  }
  uVar1 = uVar1 - 8;
  if (uVar1 <= *(ulonglong *)(lVar2 + 0x20)) {
    lVar2 = lVar3;
    if (param_1 != (longlong *)0x0) {
      lVar2 = *param_1;
    }
    if (*(ulonglong *)(lVar2 + 0x18) <= uVar1) goto LAB_140023c87;
  }
  _invalid_parameter_noinfo();
LAB_140023c87:
  if (param_1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  else {
    lVar3 = *param_1;
  }
  if (*(ulonglong *)(lVar3 + 0x20) <= uVar1) {
    _invalid_parameter_noinfo();
  }
  return uVar1;
}
