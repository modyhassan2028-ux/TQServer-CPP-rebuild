// NpcServer.exe :: google__protobuf__io__CopyingInputStream  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== google::protobuf::io::CopyingInputStream::vf_0x10 @ 14007dff0  undefined vf_0x10(longlong * param_1, int param_2)

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void google::protobuf::io::CopyingInputStream::vf_0x10(longlong *param_1,int param_2)

{
  int *piVar1;
  undefined1 auStack_1058 [32];
  int local_1038;
  undefined1 local_1028 [4096];
  int local_28;
  int local_24;
  undefined8 local_20;
  int local_18 [2];
  ulonglong local_10;
  undefined8 uStack_8;
  
  uStack_8 = 0x14007e003;
  local_10 = DAT_140103510 ^ (ulonglong)auStack_1058;
  for (local_1038 = 0; local_1038 < param_2; local_1038 = local_1038 + local_28) {
    local_20 = 0x1000;
    local_24 = FUN_14007f330((undefined4 *)&local_20);
    local_18[0] = param_2 - local_1038;
    piVar1 = FUN_14007d140(local_18,&local_24);
    local_28 = (**(code **)(*param_1 + 8))(param_1,local_1028,*piVar1);
    if (local_28 < 1) break;
  }
  __security_check_cookie(local_10 ^ (ulonglong)auStack_1058);
  return;
}


// ==== google::protobuf::io::CopyingInputStream::vf_0x0 @ 14007f140  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * google::protobuf::io::CopyingInputStream::vf_0x0(undefined8 *param_1,uint param_2)

{
  FUN_14007dfd0(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


