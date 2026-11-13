// NpcServer.exe :: CMsgMonsterTransform  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMsgMonsterTransform::vf_0x8 @ 140063b00  ulonglong vf_0x8(longlong param_1, void * param_2, uint param_3)

ulonglong CMsgMonsterTransform::vf_0x8(longlong param_1,void *param_2,uint param_3)

{
  ulonglong uVar1;
  
  uVar1 = CNetMsg::vf_0x8(param_1,param_2,param_3);
  if ((int)uVar1 == 0) {
    return uVar1;
  }
  return (ulonglong)(*(int *)(param_1 + 8) == 0x412);
}


// ==== CMsgMonsterTransform::vf_0x18 @ 140063b30  undefined vf_0x18(void)

void CMsgMonsterTransform::vf_0x18(void)

{
  return;
}


// ==== CMsgMonsterTransform::vf_0x0 @ 140063b40  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMsgMonsterTransform::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  FUN_140034810(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


