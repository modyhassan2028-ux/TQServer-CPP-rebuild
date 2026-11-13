// NpcServer.exe :: google__protobuf__FatalException  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== google::protobuf::FatalException::vf_0x8 @ 140078ad0  undefined vf_0x8(longlong param_1)

void google::protobuf::FatalException::vf_0x8(longlong param_1)

{
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::c_str
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x28));
  return;
}


// ==== google::protobuf::FatalException::vf_0x0 @ 140078e00  exception * vf_0x0(exception * param_1, uint param_2)

exception * google::protobuf::FatalException::vf_0x0(exception *param_1,uint param_2)

{
  FUN_140078a80(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


