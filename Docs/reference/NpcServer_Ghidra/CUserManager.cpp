// NpcServer.exe :: CUserManager  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CUserManager::vf_0x8 @ 140037f20  undefined8 vf_0x8(undefined8 * param_1)

undefined8 CUserManager::vf_0x8(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    (**(code **)*param_1)(param_1,1);
  }
  return 0;
}


// ==== CUserManager::vf_0x10 @ 140037f40  longlong vf_0x10(longlong param_1)

longlong CUserManager::vf_0x10(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = *(longlong *)(param_1 + 8);
  if (lVar1 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    lVar1 = 0;
  }
  return lVar1;
}


// ==== CUserManager::vf_0x0 @ 140038a10  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CUserManager::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  if ((longlong *)param_1[1] != (longlong *)0x0) {
    (**(code **)(*(longlong *)param_1[1] + 8))();
  }
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


