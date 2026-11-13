// NpcServer.exe :: CNetMsg  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CNetMsg::vf_0x10 @ 140034850  bool vf_0x10(longlong param_1)

bool CNetMsg::vf_0x10(longlong param_1)

{
  return *(int *)(param_1 + 8) != 0;
}


// ==== CNetMsg::vf_0x8 @ 140034860  undefined8 vf_0x8(longlong param_1, void * param_2, uint param_3)

undefined8 CNetMsg::vf_0x8(longlong param_1,void *param_2,uint param_3)

{
  if (param_2 == (void *)0x0) {
    return 0;
  }
  memcpy((void *)(param_1 + 0x10),param_2,(ulonglong)param_3);
  return 1;
}


// ==== CNetMsg::vf_0x18 @ 140034890  undefined vf_0x18(void)

void CNetMsg::vf_0x18(void)

{
  undefined1 auStack_438 [32];
  char local_418 [1024];
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_438;
  sprintf(local_418,"Process Msg:%d, Size:%d");
  log_InlineLogERROR(local_418);
  __security_check_cookie(local_18 ^ (ulonglong)auStack_438);
  return;
}


// ==== CNetMsg::vf_0x20 @ 1400348f0  undefined vf_0x20(longlong param_1, longlong param_2)

void CNetMsg::vf_0x20(longlong param_1,longlong param_2)

{
  longlong lVar1;
  
  lVar1 = FUN_14001c200();
  FUN_14001c5f0(lVar1,*(undefined4 *)(param_1 + 0x410),param_2);
  return;
}


// ==== CNetMsg::vf_0x0 @ 140034970  undefined8 * vf_0x0(undefined8 * param_1, byte param_2)

undefined8 * CNetMsg::vf_0x0(undefined8 *param_1,byte param_2)

{
  *param_1 = vftable;
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


