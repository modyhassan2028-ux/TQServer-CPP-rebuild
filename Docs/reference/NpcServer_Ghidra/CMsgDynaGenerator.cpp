// NpcServer.exe :: CMsgDynaGenerator  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMsgDynaGenerator::vf_0x8 @ 140061870  undefined8 vf_0x8(longlong param_1, void * param_2, uint param_3)

undefined8 CMsgDynaGenerator::vf_0x8(longlong param_1,void *param_2,uint param_3)

{
  if (param_2 == (void *)0x0) {
    return 0;
  }
  memcpy((void *)(param_1 + 0x10),param_2,(ulonglong)param_3);
  return 1;
}


// ==== CMsgDynaGenerator::vf_0x18 @ 1400618a0  undefined vf_0x18(longlong param_1, longlong param_2)

void CMsgDynaGenerator::vf_0x18(longlong param_1,longlong param_2)

{
  uint *puVar1;
  longlong lVar2;
  
  if ((param_2 != 0) && (puVar1 = *(uint **)(param_1 + 0x418), puVar1 != (uint *)0x0)) {
    lVar2 = FUN_14001c7a0();
    FUN_140033340(lVar2,puVar1);
  }
  return;
}


// ==== CMsgDynaGenerator::vf_0x0 @ 1400618e0  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMsgDynaGenerator::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  FUN_140034810(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


