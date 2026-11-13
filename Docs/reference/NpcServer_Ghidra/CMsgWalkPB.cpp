// NpcServer.exe :: CMsgWalkPB  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMsgWalkPB::vf_0x18 @ 140097330  undefined vf_0x18(longlong param_1)

void CMsgWalkPB::vf_0x18(longlong param_1)

{
  if ((*(byte *)(param_1 + 0x30) & 0x1f) != 0) {
    *(undefined4 *)(param_1 + 0x38) = 0;
    *(undefined4 *)(param_1 + 0x3c) = 0;
    *(undefined4 *)(param_1 + 0x40) = 0;
    *(undefined4 *)(param_1 + 0x44) = 0;
    *(undefined4 *)(param_1 + 0x48) = 0;
  }
  *(undefined4 *)(param_1 + 0x30) = 0;
                    /* WARNING: Could not recover jumptable at 0x000140097350. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::clear
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 8));
  return;
}


// ==== CMsgWalkPB::vf_0x48 @ 140097360  undefined vf_0x48(longlong param_1, undefined8 * param_2)

void CMsgWalkPB::vf_0x48(longlong param_1,undefined8 *param_2)

{
  void *pvVar1;
  
  if ((*(byte *)(param_1 + 0x30) & 1) != 0) {
    FUN_1400a2960(1,*(uint *)(param_1 + 0x38),param_2);
  }
  if ((*(uint *)(param_1 + 0x30) >> 1 & 1) != 0) {
    FUN_1400a2960(2,*(uint *)(param_1 + 0x3c),param_2);
  }
  if ((*(uint *)(param_1 + 0x30) >> 2 & 1) != 0) {
    FUN_1400a2960(3,*(uint *)(param_1 + 0x40),param_2);
  }
  if ((*(uint *)(param_1 + 0x30) >> 3 & 1) != 0) {
    FUN_1400a2960(4,*(uint *)(param_1 + 0x44),param_2);
  }
  if ((*(uint *)(param_1 + 0x30) >> 4 & 1) != 0) {
    FUN_1400a2960(5,*(uint *)(param_1 + 0x48),param_2);
  }
  if (*(ulonglong *)(param_1 + 0x28) < 0x10) {
    pvVar1 = (void *)(param_1 + 0x10);
  }
  else {
    pvVar1 = *(void **)(param_1 + 0x10);
  }
  FUN_14007bd80(param_2,pvVar1,(int)*(undefined8 *)(param_1 + 0x20));
  return;
}


// ==== CMsgWalkPB::vf_0x40 @ 140097420  int vf_0x40(longlong param_1)

int CMsgWalkPB::vf_0x40(longlong param_1)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  int iVar4;
  
  iVar4 = 0;
  if (*(char *)(param_1 + 0x30) != '\0') {
    iVar2 = 1;
    if ((*(byte *)(param_1 + 0x30) & 1) != 0) {
      if (*(uint *)(param_1 + 0x38) < 0x80) {
        iVar4 = 1;
      }
      else {
        uVar3 = FUN_14007c3e0(*(uint *)(param_1 + 0x38));
        iVar4 = (int)uVar3;
      }
      iVar4 = iVar4 + 1;
    }
    if ((*(uint *)(param_1 + 0x30) >> 1 & 1) != 0) {
      if (*(uint *)(param_1 + 0x3c) < 0x80) {
        iVar1 = 1;
      }
      else {
        uVar3 = FUN_14007c3e0(*(uint *)(param_1 + 0x3c));
        iVar1 = (int)uVar3;
      }
      iVar4 = iVar4 + 1 + iVar1;
    }
    if ((*(uint *)(param_1 + 0x30) >> 2 & 1) != 0) {
      if (*(uint *)(param_1 + 0x40) < 0x80) {
        iVar1 = 1;
      }
      else {
        uVar3 = FUN_14007c3e0(*(uint *)(param_1 + 0x40));
        iVar1 = (int)uVar3;
      }
      iVar4 = iVar4 + 1 + iVar1;
    }
    if ((*(uint *)(param_1 + 0x30) >> 3 & 1) != 0) {
      if (*(uint *)(param_1 + 0x44) < 0x80) {
        iVar1 = 1;
      }
      else {
        uVar3 = FUN_14007c3e0(*(uint *)(param_1 + 0x44));
        iVar1 = (int)uVar3;
      }
      iVar4 = iVar4 + 1 + iVar1;
    }
    if ((*(uint *)(param_1 + 0x30) >> 4 & 1) != 0) {
      if (0x7f < *(uint *)(param_1 + 0x48)) {
        uVar3 = FUN_14007c3e0(*(uint *)(param_1 + 0x48));
        iVar2 = (int)uVar3;
      }
      iVar4 = iVar4 + 1 + iVar2;
    }
  }
  iVar4 = iVar4 + *(int *)(param_1 + 0x20);
  *(int *)(param_1 + 0x34) = iVar4;
  return iVar4;
}


// ==== CMsgWalkPB::vf_0x20 @ 140097650  bool vf_0x20(longlong param_1)

bool CMsgWalkPB::vf_0x20(longlong param_1)

{
  return (*(byte *)(param_1 + 0x30) & 0xf) == 0xf;
}


// ==== CMsgWalkPB::vf_0x8 @ 140097660  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * vf_0x8(undefined8 param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
CMsgWalkPB::vf_0x8(undefined8 param_1,
                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_2)

{
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(param_2,"CMsgWalkPB")
  ;
  return param_2;
}


// ==== CMsgWalkPB::vf_0x58 @ 140097830  undefined4 vf_0x58(longlong param_1)

undefined4 CMsgWalkPB::vf_0x58(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x34);
}


// ==== CMsgWalkPB::vf_0x10 @ 1400978f0  undefined8 * vf_0x10(void)

undefined8 * CMsgWalkPB::vf_0x10(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x50);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = google::protobuf::MessageLite::vftable;
    *puVar1 = vftable;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               (puVar1 + 1));
    *(undefined4 *)((longlong)puVar1 + 0x34) = 0;
    *(undefined4 *)(puVar1 + 7) = 0;
    *(undefined4 *)((longlong)puVar1 + 0x3c) = 0;
    *(undefined4 *)(puVar1 + 8) = 0;
    *(undefined4 *)((longlong)puVar1 + 0x44) = 0;
    *(undefined4 *)(puVar1 + 9) = 0;
    *(undefined4 *)(puVar1 + 6) = 0;
  }
  return puVar1;
}


// ==== CMsgWalkPB::vf_0x0 @ 140097bb0  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMsgWalkPB::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 1));
  FUN_140075ef0(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CMsgWalkPB::vf_0x38 @ 140097c40  undefined8 vf_0x38(longlong param_1, undefined8 * param_2)

ulonglong CMsgWalkPB::vf_0x38(longlong param_1,undefined8 *param_2)

{
  byte bVar1;
  byte *pbVar2;
  char *pcVar3;
  int iVar4;
  char cVar5;
  uint uVar6;
  ulonglong uVar7;
  undefined8 uVar8;
  undefined8 local_40 [2];
  undefined8 local_30 [5];
  
  FUN_14007dbb0(local_40,param_1 + 8);
  FUN_14007bbf0(local_30,local_40);
LAB_140097c80:
  while ((pbVar2 = (byte *)param_2[1], (byte *)param_2[2] <= pbVar2 ||
         (bVar1 = *pbVar2, (char)bVar1 < '\x01'))) {
    uVar7 = FUN_14007b260(param_2);
    uVar6 = (uint)uVar7;
    uVar7 = uVar7 & 0xffffffff;
    *(uint *)(param_2 + 4) = uVar6;
    if (uVar6 - 1 < 0x7f) goto LAB_140097cbd;
LAB_140097eba:
    if ((uVar6 == 0) || (((byte)uVar6 & 7) == 4)) goto LAB_140097f02;
    cVar5 = FUN_1400a2330(param_2,uVar6,local_30);
    if (cVar5 == '\0') {
LAB_140097ee9:
      FUN_14007bc70(local_30);
      uVar7 = FUN_14007dc00(local_40);
      return uVar7 & 0xffffffffffffff00;
    }
  }
  uVar7 = (ulonglong)bVar1;
  *(uint *)(param_2 + 4) = (uint)bVar1;
  param_2[1] = pbVar2 + 1;
LAB_140097cbd:
  uVar6 = (uint)uVar7;
  iVar4 = (int)(uVar7 >> 3);
  if (iVar4 == 1) {
    if (uVar6 != 8) goto LAB_140097eba;
    if (((byte *)param_2[1] < (byte *)param_2[2]) && (bVar1 = *(byte *)param_2[1], bVar1 < 0x80)) {
      *(uint *)(param_1 + 0x38) = (uint)bVar1;
      param_2[1] = param_2[1] + 1;
    }
    else {
      uVar8 = FUN_14007b0f0(param_2,(uint *)(param_1 + 0x38));
      if ((char)uVar8 == '\0') goto LAB_140097ee9;
    }
    *(uint *)(param_1 + 0x30) = *(uint *)(param_1 + 0x30) | 1;
    pcVar3 = (char *)param_2[1];
    if (((char *)param_2[2] <= pcVar3) || (*pcVar3 != '\x10')) goto LAB_140097c80;
    param_2[1] = pcVar3 + 1;
LAB_140097d6f:
    if (((byte *)param_2[1] < (byte *)param_2[2]) && (bVar1 = *(byte *)param_2[1], bVar1 < 0x80)) {
      *(uint *)(param_1 + 0x3c) = (uint)bVar1;
      param_2[1] = param_2[1] + 1;
    }
    else {
      uVar8 = FUN_14007b0f0(param_2,(uint *)(param_1 + 0x3c));
      if ((char)uVar8 == '\0') goto LAB_140097ee9;
    }
    *(uint *)(param_1 + 0x30) = *(uint *)(param_1 + 0x30) | 2;
    pcVar3 = (char *)param_2[1];
    if (((char *)param_2[2] <= pcVar3) || (*pcVar3 != '\x18')) goto LAB_140097c80;
    param_2[1] = pcVar3 + 1;
LAB_140097dc2:
    if (((byte *)param_2[1] < (byte *)param_2[2]) && (bVar1 = *(byte *)param_2[1], bVar1 < 0x80)) {
      *(uint *)(param_1 + 0x40) = (uint)bVar1;
      param_2[1] = param_2[1] + 1;
    }
    else {
      uVar8 = FUN_14007b0f0(param_2,(uint *)(param_1 + 0x40));
      if ((char)uVar8 == '\0') goto LAB_140097ee9;
    }
    *(uint *)(param_1 + 0x30) = *(uint *)(param_1 + 0x30) | 4;
    pcVar3 = (char *)param_2[1];
    if (((char *)param_2[2] <= pcVar3) || (*pcVar3 != ' ')) goto LAB_140097c80;
    param_2[1] = pcVar3 + 1;
LAB_140097e15:
    if (((byte *)param_2[1] < (byte *)param_2[2]) && (bVar1 = *(byte *)param_2[1], bVar1 < 0x80)) {
      *(uint *)(param_1 + 0x44) = (uint)bVar1;
      param_2[1] = param_2[1] + 1;
    }
    else {
      uVar8 = FUN_14007b0f0(param_2,(uint *)(param_1 + 0x44));
      if ((char)uVar8 == '\0') goto LAB_140097ee9;
    }
    *(uint *)(param_1 + 0x30) = *(uint *)(param_1 + 0x30) | 8;
    pcVar3 = (char *)param_2[1];
    if (((char *)param_2[2] <= pcVar3) || (*pcVar3 != '(')) goto LAB_140097c80;
    param_2[1] = pcVar3 + 1;
  }
  else {
    if (iVar4 == 2) {
      if (uVar6 != 0x10) goto LAB_140097eba;
      goto LAB_140097d6f;
    }
    if (iVar4 == 3) {
      if (uVar6 != 0x18) goto LAB_140097eba;
      goto LAB_140097dc2;
    }
    if (iVar4 == 4) {
      if (uVar6 != 0x20) goto LAB_140097eba;
      goto LAB_140097e15;
    }
    if ((iVar4 != 5) || (uVar6 != 0x28)) goto LAB_140097eba;
  }
  if (((byte *)param_2[1] < (byte *)param_2[2]) && (bVar1 = *(byte *)param_2[1], bVar1 < 0x80)) {
    *(uint *)(param_1 + 0x48) = (uint)bVar1;
    param_2[1] = param_2[1] + 1;
  }
  else {
    uVar8 = FUN_14007b0f0(param_2,(uint *)(param_1 + 0x48));
    if ((char)uVar8 == '\0') goto LAB_140097ee9;
  }
  *(uint *)(param_1 + 0x30) = *(uint *)(param_1 + 0x30) | 0x10;
  if ((param_2[1] == param_2[2]) &&
     ((*(int *)((longlong)param_2 + 0x2c) != 0 || (*(int *)(param_2 + 3) == *(int *)(param_2 + 5))))
     ) {
    *(undefined4 *)(param_2 + 4) = 0;
    *(undefined1 *)((longlong)param_2 + 0x24) = 1;
LAB_140097f02:
    FUN_14007bc70(local_30);
    uVar8 = FUN_14007dc00(local_40);
    return CONCAT71((int7)((ulonglong)uVar8 >> 8),1);
  }
  goto LAB_140097c80;
}


