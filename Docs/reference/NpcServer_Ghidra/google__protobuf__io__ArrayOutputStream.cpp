// NpcServer.exe :: google__protobuf__io__ArrayOutputStream  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== google::protobuf::io::ArrayOutputStream::vf_0x8 @ 14007d850  bool vf_0x8(longlong param_1, longlong * param_2, undefined4 * param_3)

bool google::protobuf::io::ArrayOutputStream::vf_0x8
               (longlong param_1,longlong *param_2,undefined4 *param_3)

{
  bool bVar1;
  int *piVar2;
  int local_18 [6];
  
  bVar1 = *(int *)(param_1 + 0x10) <= *(int *)(param_1 + 0x18);
  if (bVar1) {
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  else {
    local_18[0] = *(int *)(param_1 + 0x10) - *(int *)(param_1 + 0x18);
    piVar2 = FUN_14007d140((int *)(param_1 + 0x14),local_18);
    *(int *)(param_1 + 0x1c) = *piVar2;
    *param_2 = (longlong)*(int *)(param_1 + 0x18) + *(longlong *)(param_1 + 8);
    *param_3 = *(undefined4 *)(param_1 + 0x1c);
    *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + *(int *)(param_1 + 0x1c);
  }
  return !bVar1;
}


// ==== google::protobuf::io::ArrayOutputStream::vf_0x10 @ 14007d910  undefined vf_0x10(longlong param_1, int param_2)

void google::protobuf::io::ArrayOutputStream::vf_0x10(longlong param_1,int param_2)

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
  if (*(int *)(param_1 + 0x1c) < 1) {
    puVar3 = local_128;
    for (lVar2 = 1; lVar2 != 0; lVar2 = lVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    local_40 = FUN_1400783d0(local_120,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream_impl_lite.cc"
                             ,0x88);
    local_50 = local_50 | 1;
    local_38 = local_40;
    lVar2 = FUN_140078030((longlong)local_40,"CHECK failed: (last_returned_size_) > (0): ");
    piVar1 = (int *)FUN_140078030(lVar2,"BackUp() can only be called after a successful Next().");
    FUN_140078580(local_128,piVar1);
  }
  if ((local_50 & 1) != 0) {
    local_50 = local_50 & 0xfffffffe;
    FUN_140078440((longlong)local_120);
  }
  if (*(int *)(param_1 + 0x1c) < param_2) {
    puVar3 = local_e0;
    for (lVar2 = 1; lVar2 != 0; lVar2 = lVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    local_30 = FUN_1400783d0(local_d8,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream_impl_lite.cc"
                             ,0x8a);
    local_50 = local_50 | 2;
    local_28 = local_30;
    piVar1 = (int *)FUN_140078030((longlong)local_30,
                                  "CHECK failed: (count) <= (last_returned_size_): ");
    FUN_140078580(local_e0,piVar1);
  }
  if ((local_50 & 2) != 0) {
    local_50 = local_50 & 0xfffffffd;
    FUN_140078440((longlong)local_d8);
  }
  if (param_2 < 0) {
    puVar3 = local_98;
    for (lVar2 = 1; lVar2 != 0; lVar2 = lVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    local_20 = FUN_1400783d0(local_90,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream_impl_lite.cc"
                             ,0x8b);
    local_50 = local_50 | 4;
    local_18 = local_20;
    piVar1 = (int *)FUN_140078030((longlong)local_20,"CHECK failed: (count) >= (0): ");
    FUN_140078580(local_98,piVar1);
  }
  if ((local_50 & 4) != 0) {
    local_50 = local_50 & 0xfffffffb;
    FUN_140078440((longlong)local_90);
  }
  *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) - param_2;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  return;
}


// ==== google::protobuf::io::ArrayOutputStream::vf_0x18 @ 14007db90  longlong vf_0x18(longlong param_1)

longlong google::protobuf::io::ArrayOutputStream::vf_0x18(longlong param_1)

{
  return (longlong)*(int *)(param_1 + 0x18);
}


// ==== google::protobuf::io::ArrayOutputStream::vf_0x28 @ 14007f070  undefined1 vf_0x28(void)

undefined1 google::protobuf::io::ArrayOutputStream::vf_0x28(void)

{
  return 0;
}


// ==== google::protobuf::io::ArrayOutputStream::vf_0x0 @ 14007f0c0  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * google::protobuf::io::ArrayOutputStream::vf_0x0(undefined8 *param_1,uint param_2)

{
  FUN_14007d810(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== google::protobuf::io::ArrayOutputStream::vf_0x20 @ 14007f480  ulonglong vf_0x20(void)

ulonglong google::protobuf::io::ArrayOutputStream::vf_0x20(void)

{
  int *piVar1;
  ulonglong uVar2;
  longlong lVar3;
  undefined1 *puVar4;
  undefined1 local_68 [8];
  undefined4 local_60 [16];
  undefined8 local_20;
  undefined4 *local_18;
  undefined4 *local_10;
  
  local_20 = 0xfffffffffffffffe;
  puVar4 = local_68;
  for (lVar3 = 1; lVar3 != 0; lVar3 = lVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  local_18 = FUN_1400783d0(local_60,3,
                           "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream.cc"
                           ,0x31);
  local_10 = local_18;
  piVar1 = (int *)FUN_140078030((longlong)local_18,
                                "This ZeroCopyOutputStream doesn\'t support aliasing. Reaching here usually means a ZeroCopyOutputStream implementation bug."
                               );
  FUN_140078580(local_68,piVar1);
  uVar2 = FUN_140078440((longlong)local_60);
  return uVar2 & 0xffffffffffffff00;
}


