// NpcServer.exe :: google__protobuf__io__ZeroCopyInputStream  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== google::protobuf::io::ZeroCopyInputStream::vf_0x0 @ 14007efd0  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * google::protobuf::io::ZeroCopyInputStream::vf_0x0(undefined8 *param_1,uint param_2)

{
  FUN_14007f440(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


