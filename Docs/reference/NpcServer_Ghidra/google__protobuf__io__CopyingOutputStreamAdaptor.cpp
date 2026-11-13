// NpcServer.exe :: google__protobuf__io__CopyingOutputStreamAdaptor  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== google::protobuf::io::CopyingOutputStreamAdaptor::vf_0x8 @ 14007eb10  undefined8 vf_0x8(longlong param_1, longlong * param_2, int * param_3)

undefined8
google::protobuf::io::CopyingOutputStreamAdaptor::vf_0x8
          (longlong param_1,longlong *param_2,int *param_3)

{
  ulonglong uVar1;
  longlong lVar2;
  
  if ((*(int *)(param_1 + 0x2c) == *(int *)(param_1 + 0x28)) &&
     (uVar1 = FUN_14007ee60(param_1), (uVar1 & 0xff) == 0)) {
    return 0;
  }
  FUN_14007ef20(param_1);
  lVar2 = FUN_14007f2e0((undefined8 *)(param_1 + 0x20));
  *param_2 = lVar2 + *(int *)(param_1 + 0x2c);
  *param_3 = *(int *)(param_1 + 0x28) - *(int *)(param_1 + 0x2c);
  *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(param_1 + 0x28);
  return CONCAT71((uint7)(uint3)((uint)*(undefined4 *)(param_1 + 0x28) >> 8),1);
}


// ==== google::protobuf::io::CopyingOutputStreamAdaptor::vf_0x10 @ 14007ebb0  undefined vf_0x10(longlong param_1, int param_2)

void google::protobuf::io::CopyingOutputStreamAdaptor::vf_0x10(longlong param_1,int param_2)

{
  int *piVar1;
  longlong lVar2;
  undefined1 *puVar3;
  undefined1 local_128 [8];
  undefined4 local_120 [16];
  undefined1 local_e0 [8];
  undefined4 local_d8 [16];
  undefined1 local_98 [8];
  undefined4 local_90 [16];
  uint local_50;
  undefined8 local_48;
  undefined4 *local_40;
  undefined4 *local_38;
  undefined4 *local_30;
  undefined4 *local_28;
  undefined4 *local_20;
  undefined4 *local_18;
  
  local_48 = 0xfffffffffffffffe;
  local_50 = 0;
  if (param_2 < 0) {
    puVar3 = local_128;
    for (lVar2 = 1; lVar2 != 0; lVar2 = lVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    local_40 = FUN_1400783d0(local_120,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream_impl_lite.cc"
                             ,0x165);
    local_50 = local_50 | 1;
    local_38 = local_40;
    piVar1 = (int *)FUN_140078030((longlong)local_40,"CHECK failed: (count) >= (0): ");
    FUN_140078580(local_128,piVar1);
  }
  if ((local_50 & 1) != 0) {
    local_50 = local_50 & 0xfffffffe;
    FUN_140078440((longlong)local_120);
  }
  if (*(int *)(param_1 + 0x2c) != *(int *)(param_1 + 0x28)) {
    puVar3 = local_e0;
    for (lVar2 = 1; lVar2 != 0; lVar2 = lVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    local_30 = FUN_1400783d0(local_d8,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream_impl_lite.cc"
                             ,0x166);
    local_50 = local_50 | 2;
    local_28 = local_30;
    lVar2 = FUN_140078030((longlong)local_30,"CHECK failed: (buffer_used_) == (buffer_size_): ");
    piVar1 = (int *)FUN_140078030(lVar2," BackUp() can only be called after Next().");
    FUN_140078580(local_e0,piVar1);
  }
  if ((local_50 & 2) != 0) {
    local_50 = local_50 & 0xfffffffd;
    FUN_140078440((longlong)local_d8);
  }
  if (*(int *)(param_1 + 0x2c) < param_2) {
    puVar3 = local_98;
    for (lVar2 = 1; lVar2 != 0; lVar2 = lVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    local_20 = FUN_1400783d0(local_90,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream_impl_lite.cc"
                             ,0x168);
    local_50 = local_50 | 4;
    local_18 = local_20;
    lVar2 = FUN_140078030((longlong)local_20,"CHECK failed: (count) <= (buffer_used_): ");
    piVar1 = (int *)FUN_140078030(lVar2,
                                  " Can\'t back up over more bytes than were returned by the last call to Next()."
                                 );
    FUN_140078580(local_98,piVar1);
  }
  if ((local_50 & 4) != 0) {
    local_50 = local_50 & 0xfffffffb;
    FUN_140078440((longlong)local_90);
  }
  *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x2c) - param_2;
  return;
}


// ==== google::protobuf::io::CopyingOutputStreamAdaptor::vf_0x18 @ 14007ee40  longlong vf_0x18(longlong param_1)

longlong google::protobuf::io::CopyingOutputStreamAdaptor::vf_0x18(longlong param_1)

{
  return (longlong)*(int *)(param_1 + 0x2c) + *(longlong *)(param_1 + 0x18);
}


// ==== google::protobuf::io::CopyingOutputStreamAdaptor::vf_0x0 @ 14007f200  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 *
google::protobuf::io::CopyingOutputStreamAdaptor::vf_0x0(undefined8 *param_1,uint param_2)

{
  FUN_14007ea50(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


