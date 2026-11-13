// NpcServer.exe :: google__protobuf__io__CopyingInputStreamAdaptor  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== google::protobuf::io::CopyingInputStreamAdaptor::vf_0x8 @ 14007e260  undefined8 vf_0x8(longlong param_1, longlong * param_2, undefined4 * param_3)

ulonglong google::protobuf::io::CopyingInputStreamAdaptor::vf_0x8
                    (longlong param_1,longlong *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  longlong lVar2;
  undefined8 uVar3;
  ulonglong uVar4;
  
  if (*(char *)(param_1 + 0x11) == '\0') {
    FUN_14007e830(param_1);
    if (*(int *)(param_1 + 0x30) < 1) {
      uVar3 = FUN_14007f2e0((undefined8 *)(param_1 + 0x20));
      uVar1 = (**(code **)(**(longlong **)(param_1 + 8) + 8))
                        (*(undefined8 *)(param_1 + 8),uVar3,*(undefined4 *)(param_1 + 0x28));
      *(undefined4 *)(param_1 + 0x2c) = uVar1;
      if (*(int *)(param_1 + 0x2c) < 1) {
        if (*(int *)(param_1 + 0x2c) < 0) {
          *(undefined1 *)(param_1 + 0x11) = 1;
        }
        uVar4 = FUN_14007e880(param_1);
        uVar4 = uVar4 & 0xffffffffffffff00;
      }
      else {
        *(longlong *)(param_1 + 0x18) =
             (longlong)*(int *)(param_1 + 0x2c) + *(longlong *)(param_1 + 0x18);
        *param_3 = *(undefined4 *)(param_1 + 0x2c);
        lVar2 = FUN_14007f2e0((undefined8 *)(param_1 + 0x20));
        *param_2 = lVar2;
        uVar4 = CONCAT71((int7)((ulonglong)param_2 >> 8),1);
      }
    }
    else {
      lVar2 = FUN_14007f2e0((undefined8 *)(param_1 + 0x20));
      *param_2 = (lVar2 + *(int *)(param_1 + 0x2c)) - (longlong)*(int *)(param_1 + 0x30);
      *param_3 = *(undefined4 *)(param_1 + 0x30);
      *(undefined4 *)(param_1 + 0x30) = 0;
      uVar4 = CONCAT71((int7)((ulonglong)param_1 >> 8),1);
    }
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}


// ==== google::protobuf::io::CopyingInputStreamAdaptor::vf_0x10 @ 14007e3b0  undefined vf_0x10(longlong param_1, int param_2)

void google::protobuf::io::CopyingInputStreamAdaptor::vf_0x10(longlong param_1,int param_2)

{
  longlong lVar1;
  int *piVar2;
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
  if ((*(int *)(param_1 + 0x30) != 0) ||
     (lVar1 = FUN_14007f2e0((undefined8 *)(param_1 + 0x20)), lVar1 == 0)) {
    puVar3 = local_128;
    for (lVar1 = 1; lVar1 != 0; lVar1 = lVar1 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    local_40 = FUN_1400783d0(local_120,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream_impl_lite.cc"
                             ,0x10c);
    local_50 = local_50 | 1;
    local_38 = local_40;
    lVar1 = FUN_140078030((longlong)local_40,
                          "CHECK failed: backup_bytes_ == 0 && buffer_.get() != NULL: ");
    piVar2 = (int *)FUN_140078030(lVar1," BackUp() can only be called after Next().");
    FUN_140078580(local_128,piVar2);
  }
  if ((local_50 & 1) != 0) {
    local_50 = local_50 & 0xfffffffe;
    FUN_140078440((longlong)local_120);
  }
  if (*(int *)(param_1 + 0x2c) < param_2) {
    puVar3 = local_e0;
    for (lVar1 = 1; lVar1 != 0; lVar1 = lVar1 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    local_30 = FUN_1400783d0(local_d8,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream_impl_lite.cc"
                             ,0x10e);
    local_50 = local_50 | 2;
    local_28 = local_30;
    lVar1 = FUN_140078030((longlong)local_30,"CHECK failed: (count) <= (buffer_used_): ");
    piVar2 = (int *)FUN_140078030(lVar1,
                                  " Can\'t back up over more bytes than were returned by the last call to Next()."
                                 );
    FUN_140078580(local_e0,piVar2);
  }
  if ((local_50 & 2) != 0) {
    local_50 = local_50 & 0xfffffffd;
    FUN_140078440((longlong)local_d8);
  }
  if (param_2 < 0) {
    puVar3 = local_98;
    for (lVar1 = 1; lVar1 != 0; lVar1 = lVar1 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    local_20 = FUN_1400783d0(local_90,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream_impl_lite.cc"
                             ,0x111);
    local_50 = local_50 | 4;
    local_18 = local_20;
    lVar1 = FUN_140078030((longlong)local_20,"CHECK failed: (count) >= (0): ");
    piVar2 = (int *)FUN_140078030(lVar1," Parameter to BackUp() can\'t be negative.");
    FUN_140078580(local_98,piVar2);
  }
  if ((local_50 & 4) != 0) {
    local_50 = local_50 & 0xfffffffb;
    FUN_140078440((longlong)local_90);
  }
  *(int *)(param_1 + 0x30) = param_2;
  return;
}


// ==== google::protobuf::io::CopyingInputStreamAdaptor::vf_0x18 @ 14007e650  bool vf_0x18(longlong param_1, int param_2)

bool google::protobuf::io::CopyingInputStreamAdaptor::vf_0x18(longlong param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  longlong lVar4;
  undefined1 *puVar5;
  bool bVar6;
  undefined1 local_74 [4];
  undefined4 local_70 [16];
  uint local_30;
  undefined8 local_28;
  undefined4 *local_20;
  undefined4 *local_18;
  
  local_28 = 0xfffffffffffffffe;
  local_30 = 0;
  if (param_2 < 0) {
    puVar5 = local_74;
    for (lVar4 = 1; lVar4 != 0; lVar4 = lVar4 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    local_20 = FUN_1400783d0(local_70,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream_impl_lite.cc"
                             ,0x118);
    local_30 = local_30 | 1;
    local_18 = local_20;
    piVar3 = (int *)FUN_140078030((longlong)local_20,"CHECK failed: (count) >= (0): ");
    FUN_140078580(local_74,piVar3);
  }
  if ((local_30 & 1) != 0) {
    local_30 = local_30 & 0xfffffffe;
    FUN_140078440((longlong)local_70);
  }
  if (*(char *)(param_1 + 0x11) == '\0') {
    if (*(int *)(param_1 + 0x30) < param_2) {
      iVar1 = param_2 - *(int *)(param_1 + 0x30);
      *(undefined4 *)(param_1 + 0x30) = 0;
      iVar2 = (**(code **)(**(longlong **)(param_1 + 8) + 0x10))(*(undefined8 *)(param_1 + 8),iVar1)
      ;
      *(longlong *)(param_1 + 0x18) = (longlong)iVar2 + *(longlong *)(param_1 + 0x18);
      bVar6 = iVar2 == iVar1;
    }
    else {
      *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) - param_2;
      bVar6 = true;
    }
  }
  else {
    bVar6 = false;
  }
  return bVar6;
}


// ==== google::protobuf::io::CopyingInputStreamAdaptor::vf_0x20 @ 14007e800  longlong vf_0x20(longlong param_1)

longlong google::protobuf::io::CopyingInputStreamAdaptor::vf_0x20(longlong param_1)

{
  return *(longlong *)(param_1 + 0x18) - (longlong)*(int *)(param_1 + 0x30);
}


// ==== google::protobuf::io::CopyingInputStreamAdaptor::vf_0x0 @ 14007f180  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 *
google::protobuf::io::CopyingInputStreamAdaptor::vf_0x0(undefined8 *param_1,uint param_2)

{
  FUN_14007e1c0(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


