// NpcServer.exe :: CAIStrategyMgr  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CAIStrategyMgr::vf_0x0 @ 140046290  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CAIStrategyMgr::vf_0x0(undefined8 *param_1,uint param_2)

{
  FUN_140045820(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


