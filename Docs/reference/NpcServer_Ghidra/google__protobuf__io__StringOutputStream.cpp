// NpcServer.exe :: google__protobuf__io__StringOutputStream  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== google::protobuf::io::StringOutputStream::vf_0x8 @ 14007dc40  undefined8 vf_0x8(longlong param_1, longlong * param_2, int * param_3)

undefined8
google::protobuf::io::StringOutputStream::vf_0x8(longlong param_1,longlong *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  __uint64 _Var3;
  int *piVar4;
  ulonglong uVar5;
  longlong lVar6;
  undefined1 *puVar7;
  undefined1 local_74 [4];
  undefined4 local_70 [16];
  int local_30;
  int local_2c [3];
  undefined4 *local_20;
  undefined4 *local_18;
  
  local_2c[1] = -2;
  local_2c[2] = -1;
  _Var3 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       **)(param_1 + 8));
  iVar1 = (int)_Var3;
  _Var3 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          capacity(*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> **
                    )(param_1 + 8));
  if ((ulonglong)(longlong)iVar1 < _Var3) {
    _Var3 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
            capacity(*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       **)(param_1 + 8));
    FUN_140077900(*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> **)
                   (param_1 + 8),_Var3);
  }
  else {
    iVar2 = std::numeric_limits<int>::max();
    if (iVar2 / 2 < iVar1) {
      puVar7 = local_74;
      for (lVar6 = 1; lVar6 != 0; lVar6 = lVar6 + -1) {
        *puVar7 = 0;
        puVar7 = puVar7 + 1;
      }
      local_20 = FUN_1400783d0(local_70,2,
                               "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream_impl_lite.cc"
                               ,0xaa);
      local_18 = local_20;
      lVar6 = FUN_140078030((longlong)local_20,"Cannot allocate buffer larger than kint32max for ");
      piVar4 = (int *)FUN_140078030(lVar6,"StringOutputStream.");
      FUN_140078580(local_74,piVar4);
      uVar5 = FUN_140078440((longlong)local_70);
      return uVar5 & 0xffffffffffffff00;
    }
    local_30 = 0x10;
    local_2c[0] = iVar1 << 1;
    piVar4 = FUN_14007d190(local_2c,&local_30);
    FUN_140077900(*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> **)
                   (param_1 + 8),(longlong)*piVar4);
  }
  lVar6 = FUN_140077930(*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                          **)(param_1 + 8));
  *param_2 = lVar6 + iVar1;
  _Var3 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       **)(param_1 + 8));
  *param_3 = (int)_Var3 - iVar1;
  return CONCAT71((int7)((ulonglong)param_3 >> 8),1);
}


// ==== google::protobuf::io::StringOutputStream::vf_0x10 @ 14007dde0  undefined vf_0x10(longlong param_1, int param_2)

void google::protobuf::io::StringOutputStream::vf_0x10(longlong param_1,int param_2)

{
  __uint64 _Var1;
  int *piVar2;
  longlong lVar3;
  undefined1 *puVar4;
  undefined1 local_c8 [8];
  undefined4 local_c0 [16];
  undefined1 local_80 [8];
  undefined4 local_78 [16];
  uint local_38;
  undefined8 local_30;
  undefined4 *local_28;
  undefined4 *local_20;
  undefined4 *local_18;
  undefined4 *local_10;
  
  local_30 = 0xfffffffffffffffe;
  local_38 = 0;
  if (param_2 < 0) {
    puVar4 = local_c8;
    for (lVar3 = 1; lVar3 != 0; lVar3 = lVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    local_28 = FUN_1400783d0(local_c0,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream_impl_lite.cc"
                             ,0xbc);
    local_38 = local_38 | 1;
    local_20 = local_28;
    piVar2 = (int *)FUN_140078030((longlong)local_28,"CHECK failed: (count) >= (0): ");
    FUN_140078580(local_c8,piVar2);
  }
  if ((local_38 & 1) != 0) {
    local_38 = local_38 & 0xfffffffe;
    FUN_140078440((longlong)local_c0);
  }
  _Var1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       **)(param_1 + 8));
  if (_Var1 < (ulonglong)(longlong)param_2) {
    puVar4 = local_80;
    for (lVar3 = 1; lVar3 != 0; lVar3 = lVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    local_18 = FUN_1400783d0(local_78,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream_impl_lite.cc"
                             ,0xbd);
    local_38 = local_38 | 2;
    local_10 = local_18;
    piVar2 = (int *)FUN_140078030((longlong)local_18,"CHECK failed: (count) <= (target_->size()): ")
    ;
    FUN_140078580(local_80,piVar2);
  }
  if ((local_38 & 2) != 0) {
    local_38 = local_38 & 0xfffffffd;
    FUN_140078440((longlong)local_78);
  }
  _Var1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       **)(param_1 + 8));
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::resize
            (*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> **)
              (param_1 + 8),_Var1 - (longlong)param_2);
  return;
}


// ==== google::protobuf::io::StringOutputStream::vf_0x18 @ 14007dfa0  undefined vf_0x18(longlong param_1)

void google::protobuf::io::StringOutputStream::vf_0x18(longlong param_1)

{
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
            (*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> **)
              (param_1 + 8));
  return;
}


// ==== google::protobuf::io::StringOutputStream::vf_0x0 @ 14007f100  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * google::protobuf::io::StringOutputStream::vf_0x0(undefined8 *param_1,uint param_2)

{
  FUN_14007dc00(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


