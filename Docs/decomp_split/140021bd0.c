/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
undefined8 FUN_140021bd0(longlong param_1)
{
  char cVar1;
  undefined8 uVar2;
  undefined1 auStack_488 [32];
  undefined1 *local_468;
  undefined4 *local_460;
  undefined4 local_458;
  undefined4 local_454;
  undefined4 local_450;
  undefined8 local_448;
  undefined1 local_438 [1056];
  ulonglong local_18;
  local_448 = 0xfffffffffffffffe;
  local_18 = DAT_1409707c0 ^ (ulonglong)auStack_488;
  local_460 = &local_458;
  local_468 = local_438;
  cVar1 = (**(code **)(**(longlong **)(param_1 + 0x1f0) + 0x48))
                    (*(longlong **)(param_1 + 0x1f0),0xffffffff,0xffffffff,0x418);
  if (cVar1 == '\0') {
    uVar2 = 1;
  }
  else {
    local_468 = (undefined1 *)CONCAT44(local_468._4_4_,local_458);
    cVar1 = FUN_14001e670(param_1,local_454,local_438,local_450);
    if (cVar1 == '\0') {
      FUN_14001e540(param_1,"ERROR: CMsgServerDlg::Process() ProcessMsg()");
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  return uVar2;
}
