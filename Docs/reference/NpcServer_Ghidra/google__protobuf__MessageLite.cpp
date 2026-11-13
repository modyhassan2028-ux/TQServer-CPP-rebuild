// NpcServer.exe :: google__protobuf__MessageLite  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== google::protobuf::MessageLite::vf_0x28 @ 140075f10  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * vf_0x28(undefined8 param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
google::protobuf::MessageLite::vf_0x28
          (undefined8 param_1,
          basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (param_2,"(cannot determine missing fields for lite message)");
  return param_2;
}


// ==== google::protobuf::MessageLite::vf_0x50 @ 140076790  longlong vf_0x50(longlong * param_1, longlong param_2)

longlong google::protobuf::MessageLite::vf_0x50(longlong *param_1,longlong param_2)

{
  char cVar1;
  int *piVar2;
  longlong lVar3;
  undefined1 *puVar4;
  undefined8 local_c8 [4];
  int local_a8;
  undefined8 local_a0 [4];
  undefined1 local_80 [8];
  undefined4 local_78 [16];
  longlong local_38;
  uint local_30;
  undefined8 local_28;
  undefined4 *local_20;
  undefined4 *local_18;
  
  local_28 = 0xfffffffffffffffe;
  local_30 = 0;
  local_a8 = (**(code **)(*param_1 + 0x58))(param_1);
  FUN_14007d760(local_a0,param_2,local_a8,-1);
  FUN_14007bbf0(local_c8,local_a0);
  (**(code **)(*param_1 + 0x48))(param_1,local_c8);
  cVar1 = FUN_140077840((longlong)local_c8);
  if (cVar1 != '\0') {
    puVar4 = local_80;
    for (lVar3 = 1; lVar3 != 0; lVar3 = lVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    local_20 = FUN_1400783d0(local_78,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\message_lite.cc"
                             ,0xe0);
    local_30 = local_30 | 1;
    local_18 = local_20;
    piVar2 = (int *)FUN_140078030((longlong)local_20,"CHECK failed: !coded_out.HadError(): ");
    FUN_140078580(local_80,piVar2);
  }
  if ((local_30 & 1) != 0) {
    local_30 = local_30 & 0xfffffffe;
    FUN_140078440((longlong)local_78);
  }
  local_38 = param_2 + local_a8;
  FUN_14007bc70(local_c8);
  FUN_14007d810(local_a0);
  return local_38;
}


// ==== google::protobuf::MessageLite::vf_0x0 @ 140077330  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * google::protobuf::MessageLite::vf_0x0(undefined8 *param_1,uint param_2)

{
  FUN_140075ef0(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


