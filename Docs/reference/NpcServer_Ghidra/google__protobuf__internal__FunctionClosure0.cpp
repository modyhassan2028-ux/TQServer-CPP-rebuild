// NpcServer.exe :: google__protobuf__internal__FunctionClosure0  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== google::protobuf::internal::FunctionClosure0::vf_0x8 @ 140078c50  undefined vf_0x8(undefined8 * param_1)

void google::protobuf::internal::FunctionClosure0::vf_0x8(undefined8 *param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 2);
  (*(code *)param_1[1])();
  if ((cVar1 != '\0') && (param_1 != (undefined8 *)0x0)) {
    (**(code **)*param_1)(param_1,1);
  }
  return;
}


// ==== google::protobuf::internal::FunctionClosure0::vf_0x0 @ 140078cc0  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * google::protobuf::internal::FunctionClosure0::vf_0x0(undefined8 *param_1,uint param_2)

{
  FUN_1400786e0(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


