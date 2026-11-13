// NpcServer.exe :: CMsgInstance  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMsgInstance::vf_0x8 @ 140063550  ulonglong vf_0x8(longlong param_1, void * param_2, uint param_3)

ulonglong CMsgInstance::vf_0x8(longlong param_1,void *param_2,uint param_3)

{
  ulonglong uVar1;
  
  uVar1 = CNetMsg::vf_0x8(param_1,param_2,param_3);
  if ((int)uVar1 == 0) {
    return uVar1;
  }
  return (ulonglong)(*(int *)(param_1 + 8) == 0x961);
}


// ==== CMsgInstance::vf_0x18 @ 140063580  undefined vf_0x18(longlong param_1)

void CMsgInstance::vf_0x18(longlong param_1)

{
  short *psVar1;
  longlong lVar2;
  
  psVar1 = *(short **)(param_1 + 0x418);
  if (*psVar1 == 5) {
    lVar2 = FUN_14001c7b0();
    FUN_140025690(lVar2,*(undefined4 *)(psVar1 + 8),*(undefined4 *)(psVar1 + 2),
                  *(uint *)(psVar1 + 4));
  }
  else if (*psVar1 == 6) {
    lVar2 = FUN_14001c7b0();
    FUN_140025750(lVar2,*(uint *)(psVar1 + 2));
    return;
  }
  return;
}


// ==== CMsgInstance::vf_0x0 @ 1400635d0  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMsgInstance::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  tq::CStringPacker::~CStringPacker((CStringPacker *)(param_1 + 0x84));
  FUN_140034810(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


