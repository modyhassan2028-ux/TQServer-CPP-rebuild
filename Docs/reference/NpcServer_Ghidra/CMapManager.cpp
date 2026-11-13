// NpcServer.exe :: CMapManager  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMapManager::vf_0x0 @ 14003cd50  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMapManager::vf_0x0(undefined8 *param_1,uint param_2)

{
  FUN_14003c9c0(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


