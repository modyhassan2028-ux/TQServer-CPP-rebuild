// NpcServer.exe :: CMsgLogin  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMsgLogin::vf_0x8 @ 140048ea0  ulonglong vf_0x8(longlong param_1, void * param_2, uint param_3)

ulonglong CMsgLogin::vf_0x8(longlong param_1,void *param_2,uint param_3)

{
  ulonglong uVar1;
  
  uVar1 = CNetMsg::vf_0x8(param_1,param_2,param_3);
  if ((int)uVar1 == 0) {
    return uVar1;
  }
  return (ulonglong)(*(int *)(param_1 + 8) == 0x3ea);
}


// ==== CMsgLogin::vf_0x18 @ 140048ed0  undefined vf_0x18(void)

void CMsgLogin::vf_0x18(void)

{
  log_InlineLogERROR(&DAT_1400be0b0);
  return;
}


// ==== CMsgLogin::vf_0x0 @ 140048f10  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMsgLogin::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  FUN_140034810(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


