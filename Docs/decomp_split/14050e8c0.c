void FUN_14050e8c0(void)
{
  undefined8 *puVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong *plVar4;
  longlong lVar5;
  plVar4 = DAT_140976740;
  plVar2 = DAT_140976728;
  if (DAT_140976748 < DAT_140976740) {
    _invalid_parameter_noinfo();
    plVar2 = DAT_140976728;
  }
  while( true ) {
    plVar3 = DAT_140976748;
    if (DAT_140976748 < DAT_140976740) {
      _invalid_parameter_noinfo();
    }
    if ((plVar2 == (longlong *)0x0) || (plVar2 != DAT_140976728)) {
      _invalid_parameter_noinfo();
    }
    if (plVar4 == plVar3) break;
    if (plVar2 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar5 = 0;
    }
    else {
      lVar5 = *plVar2;
    }
    if (*(longlong **)(lVar5 + 0x20) <= plVar4) {
      _invalid_parameter_noinfo();
    }
    puVar1 = (undefined8 *)*plVar4;
    if (puVar1 != (undefined8 *)0x0) {
      (**(code **)*puVar1)(puVar1,1);
    }
    if (plVar2 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar5 = 0;
    }
    else {
      lVar5 = *plVar2;
    }
    if (*(longlong **)(lVar5 + 0x20) <= plVar4) {
      _invalid_parameter_noinfo();
    }
    plVar4 = plVar4 + 1;
  }
  FUN_14050de60(&DAT_140976728);
  return;
}
