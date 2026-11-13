// NpcServer.exe :: tq__Singleton<class_CAIStrategyMgr>  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== tq::Singleton<class_CAIStrategyMgr>::vf_0x0 @ 14003f370  undefined8 * vf_0x0(undefined8 * param_1, byte param_2)

undefined8 * tq::Singleton<class_CAIStrategyMgr>::vf_0x0(undefined8 *param_1,byte param_2)

{
  *param_1 = vftable;
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


