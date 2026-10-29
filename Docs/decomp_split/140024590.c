void FUN_140024590(undefined8 *param_1,undefined8 *param_2)
{
  undefined8 *puVar1;
  undefined8 *puVar2;
  ulonglong uVar3;
  undefined8 local_28;
  undefined8 *puStack_20;
  undefined1 local_18 [16];
  puVar1 = (undefined8 *)param_1[3];
  if (puVar1 == (undefined8 *)0x0) {
    uVar3 = 0;
  }
  else {
    uVar3 = param_1[5] - (longlong)puVar1 >> 3;
  }
  puVar2 = (undefined8 *)param_1[4];
  if ((ulonglong)((longlong)puVar2 - (longlong)puVar1 >> 3) < uVar3) {
    *puVar2 = *param_2;
    param_1[4] = puVar2 + 1;
    return;
  }
  if (puVar2 < puVar1) {
    _invalid_parameter_noinfo();
  }
  local_28 = *param_1;
  puStack_20 = puVar2;
  FUN_140024280(param_1,local_18,&local_28,param_2);
  return;
}
