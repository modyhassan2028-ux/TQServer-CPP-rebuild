// NpcServer.exe :: CItemType  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CItemType::vf_0x0 @ 14001e570  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CItemType::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  if ((longlong *)param_1[1] != (longlong *)0x0) {
    (**(code **)(*(longlong *)param_1[1] + 0x10))();
  }
  if ((param_2 & 1) != 0) {
    FUN_14001e4b0(param_1);
  }
  return param_1;
}


