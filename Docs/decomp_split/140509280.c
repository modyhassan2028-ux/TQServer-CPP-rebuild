void FUN_140509280(int param_1,undefined8 *param_2)
{
  undefined8 *puVar1;
  void *pvVar2;
  undefined8 uVar3;
  if (param_1 == 0) {
    puVar1 = operator_new(0x890);
    if (puVar1 == (undefined8 *)0x0) {
      puVar1 = (undefined8 *)0x0;
    }
    else {
      *puVar1 = DES::vftable;
    }
    *param_2 = puVar1;
  }
  else if (param_1 == 1) {
    pvVar2 = operator_new(0x60);
    if (pvVar2 == (void *)0x0) {
      uVar3 = 0;
    }
    else {
      uVar3 = FUN_14050a570(pvVar2);
    }
    *param_2 = uVar3;
  }
  else if (param_1 == 2) {
    puVar1 = operator_new(0x60);
    if (puVar1 == (undefined8 *)0x0) {
      puVar1 = (undefined8 *)0x0;
    }
    else {
      FUN_14050a570(puVar1);
      *puVar1 = MD5::CMD5ChecksumStandard::vftable;
    }
    *param_2 = puVar1;
  }
  else if (param_1 != 3) {
    *param_2 = 0;
  }
  return;
}
