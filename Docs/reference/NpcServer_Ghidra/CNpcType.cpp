// NpcServer.exe :: CNpcType  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CNpcType::vf_0x8 @ 140056e60  undefined vf_0x8(longlong param_1)

void CNpcType::vf_0x8(longlong param_1)

{
  longlong *plVar1;
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0x10) + 8);
  plVar1 = (longlong *)(**(code **)(*plVar1 + 0x20))(plVar1,&DAT_140102d90);
                    /* WARNING: Could not recover jumptable at 0x000140056e83. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x40))(plVar1);
  return;
}


// ==== CNpcType::vf_0x0 @ 140056e90  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CNpcType::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  if ((longlong *)param_1[2] != (longlong *)0x0) {
    (**(code **)(*(longlong *)param_1[2] + 0x58))();
  }
  FUN_1400695e0(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


