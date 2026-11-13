// NpcServer.exe :: CNpcPath  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CNpcPath::vf_0x0 @ 1400657d0  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CNpcPath::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  if ((longlong *)param_1[0xc] != (longlong *)0x0) {
    (**(code **)(*(longlong *)param_1[0xc] + 0x58))();
    param_1[0xc] = 0;
  }
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


