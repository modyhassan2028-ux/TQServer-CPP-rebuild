// NpcServer.exe :: CNpc  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CNpc::vf_0xc0 @ 140057a40  undefined vf_0xc0(longlong param_1)

void CNpc::vf_0xc0(longlong param_1)

{
  *(undefined1 *)(param_1 + 0x2e) = 1;
  return;
}


// ==== CNpc::vf_0x8 @ 140057a60  int vf_0x8(longlong * param_1, int param_2, int param_3)

int CNpc::vf_0x8(longlong *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = (**(code **)(*param_1 + 0x38))();
  uVar3 = param_2 - iVar1 >> 0x1f;
  iVar2 = (**(code **)(*param_1 + 0x40))(param_1);
  uVar4 = param_3 - iVar2 >> 0x1f;
  if ((int)((param_3 - iVar2 ^ uVar4) - uVar4) < (int)((param_2 - iVar1 ^ uVar3) - uVar3)) {
    iVar1 = (**(code **)(*param_1 + 0x38))();
    uVar3 = param_2 - iVar1;
  }
  else {
    iVar1 = (**(code **)(*param_1 + 0x40))(param_1);
    uVar3 = param_3 - iVar1;
  }
  return (uVar3 ^ (int)uVar3 >> 0x1f) - ((int)uVar3 >> 0x1f);
}


// ==== CNpc::vf_0x18 @ 140057ae0  undefined4 vf_0x18(longlong param_1)

undefined4 CNpc::vf_0x18(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x14);
}


// ==== CNpc::vf_0x20 @ 140057af0  undefined4 * vf_0x20(longlong param_1, undefined4 * param_2)

undefined4 * CNpc::vf_0x20(longlong param_1,undefined4 *param_2)

{
  *param_2 = *(undefined4 *)(param_1 + 0xd8);
  param_2[1] = *(undefined4 *)(param_1 + 0xdc);
  param_2[2] = *(undefined4 *)(param_1 + 0xe0);
  param_2[3] = *(undefined4 *)(param_1 + 0xe4);
  param_2[4] = *(undefined4 *)(param_1 + 0xe8);
  param_2[5] = *(undefined4 *)(param_1 + 0xec);
  return param_2;
}


// ==== CNpc::vf_0x8 @ 140057b40  undefined4 vf_0x8(longlong param_1)

undefined4 CNpc::vf_0x8(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x80);
}


// ==== CNpc::vf_0x80 @ 140057b80  undefined8 vf_0x80(longlong param_1)

undefined8 CNpc::vf_0x80(longlong param_1)

{
  return *(undefined8 *)(param_1 + 0x88);
}


// ==== CNpc::vf_0x38 @ 140057ba0  undefined4 vf_0x38(longlong param_1)

undefined4 CNpc::vf_0x38(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x24);
}


// ==== CNpc::vf_0x40 @ 140057bb0  undefined4 vf_0x40(longlong param_1)

undefined4 CNpc::vf_0x40(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x28);
}


// ==== CNpc::vf_0x48 @ 140057bd0  undefined vf_0x48(longlong param_1)

void CNpc::vf_0x48(longlong param_1)

{
  longlong *plVar1;
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0x90) + 0x10);
                    /* WARNING: Could not recover jumptable at 0x000140057be3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x10))(plVar1,0x18);
  return;
}


// ==== CNpc::vf_0x58 @ 140057d60  bool vf_0x58(longlong param_1)

bool CNpc::vf_0x58(longlong param_1)

{
  longlong *plVar1;
  ulonglong uVar2;
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0x90) + 0x10);
  uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
  return (uVar2 & 0x2004) == 0;
}


// ==== CNpc::vf_0x60 @ 140057dc0  bool vf_0x60(longlong param_1)

bool CNpc::vf_0x60(longlong param_1)

{
  longlong *plVar1;
  int iVar2;
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0x90) + 0x10);
  iVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0xf);
  return 2 < iVar2;
}


// ==== CNpc::vf_0x68 @ 140057ee0  undefined1 vf_0x68(void)

undefined1 CNpc::vf_0x68(void)

{
  return 0;
}


// ==== CNpc::vf_0x70 @ 140057f20  uint vf_0x70(longlong param_1)

uint CNpc::vf_0x70(longlong param_1)

{
  longlong *plVar1;
  uint uVar2;
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0x90) + 0x10);
  uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
  return uVar2 >> 2 & 1;
}


// ==== CNpc::vf_0x78 @ 140057fe0  uint vf_0x78(longlong param_1)

uint CNpc::vf_0x78(longlong param_1)

{
  longlong *plVar1;
  uint uVar2;
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0x90) + 0x10);
  uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
  return uVar2 >> 0xc & 1;
}


// ==== CNpc::vf_0xb0 @ 140058010  undefined vf_0xb0(longlong param_1, int param_2, longlong * param_3)

void CNpc::vf_0xb0(longlong param_1,int param_2,longlong *param_3)

{
  longlong lVar1;
  
  lVar1 = 0;
  if (param_2 == 0x1040) {
    lVar1 = param_1 + -0x10;
  }
  if (param_3 != (longlong *)0x0) {
    *param_3 = lVar1;
  }
  return;
}


// ==== CNpc::vf_0x88 @ 140058030  longlong vf_0x88(longlong param_1)

longlong CNpc::vf_0x88(longlong param_1)

{
  return param_1 + 0xc0;
}


// ==== CNpc::vf_0xe8 @ 140058040  longlong vf_0xe8(longlong param_1)

longlong CNpc::vf_0xe8(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = 0;
  if (param_1 != 0x10) {
    lVar1 = param_1;
  }
  return lVar1;
}


// ==== CNpc::vf_0xf8 @ 140058050  undefined vf_0xf8(longlong param_1)

void CNpc::vf_0xf8(longlong param_1)

{
  if (*(char *)(param_1 + 0x2f) == '\0') {
    *(undefined1 *)(param_1 + 0x2f) = 1;
  }
  return;
}


// ==== CNpc::vf_0x90 @ 140058070  undefined vf_0x90(longlong param_1, undefined4 * param_2)

void CNpc::vf_0x90(longlong param_1,undefined4 *param_2)

{
  *(undefined4 *)(param_1 + 0xd8) = *param_2;
  *(undefined4 *)(param_1 + 0xdc) = param_2[1];
  *(undefined4 *)(param_1 + 0xe0) = param_2[2];
  *(undefined4 *)(param_1 + 0xe4) = param_2[3];
  *(undefined4 *)(param_1 + 0xe8) = param_2[4];
  *(undefined4 *)(param_1 + 0xec) = param_2[5];
  return;
}


// ==== CNpc::vf_0x98 @ 1400580b0  undefined vf_0x98(longlong param_1, undefined4 param_2)

void CNpc::vf_0x98(longlong param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0xc) = param_2;
  return;
}


// ==== CNpc::vf_0xa0 @ 1400580c0  undefined vf_0xa0(longlong param_1, undefined4 param_2)

void CNpc::vf_0xa0(longlong param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x10) = param_2;
  return;
}


// ==== CNpc::vf_0xa8 @ 1400580d0  undefined vf_0xa8(void)

void CNpc::vf_0xa8(void)

{
  return;
}


// ==== CNpc::vf_0x30 @ 1400585f0  undefined8 vf_0x30(longlong param_1)

undefined8 CNpc::vf_0x30(longlong param_1)

{
  undefined8 uVar1;
  
  if (*(longlong *)(param_1 + 0x88) != 0) {
                    /* WARNING: Could not recover jumptable at 0x000140058604. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(**(longlong **)(param_1 + 0x88) + 8))();
    return uVar1;
  }
  return 0;
}


// ==== CNpc::vf_0x110 @ 140058d60  undefined vf_0x110(longlong param_1, undefined1 param_2)

void CNpc::vf_0x110(longlong param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x138) = param_2;
  return;
}


// ==== CNpc::vf_0x118 @ 140058d80  undefined vf_0x118(longlong param_1, ushort param_2, ushort param_3, undefined4 param_4)

void CNpc::vf_0x118(longlong param_1,ushort param_2,ushort param_3,undefined4 param_4)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  longlong lVar5;
  uint uVar6;
  uint uVar7;
  undefined1 auStackY_4a8 [32];
  undefined8 local_468 [132];
  ulonglong local_48;
  
  local_48 = DAT_140103510 ^ (ulonglong)auStackY_4a8;
  lVar5 = *(longlong *)(param_1 + 0x88);
  if (lVar5 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  else {
    iVar2 = FUN_140049480(lVar5);
    uVar7 = (uint)param_2;
    if ((int)uVar7 < iVar2) {
      iVar2 = FUN_140049430(lVar5);
      uVar6 = (uint)param_3;
      if ((int)uVar6 < iVar2) {
        bVar1 = FUN_140049310(*(longlong *)(param_1 + 0x88),uVar7,uVar6);
        if (bVar1) {
          *(undefined4 *)(param_1 + 0x1c) = 0;
          FUN_140058610(param_1 + -0x10,uVar7,uVar6);
          *(undefined4 *)(param_1 + 0x14) = param_4;
          FUN_140061610(local_468);
          uVar3 = (**(code **)(*(longlong *)(param_1 + -0x10) + 8))(param_1 + -0x10);
          uVar4 = FUN_1400616c0((longlong)local_468,uVar3,param_2,param_3,(short)param_4);
          if ((int)uVar4 != 0) {
            uVar3 = (**(code **)(*(longlong *)(param_1 + -0x10) + 8))(param_1 + -0x10);
            lVar5 = FUN_14001c200();
            FUN_14001c5f0(lVar5,uVar3,(longlong)local_468);
          }
          FUN_140061660(local_468);
        }
        else {
          log_InlineLogERROR(&DAT_1400be0b0);
        }
        goto LAB_140058f17;
      }
    }
    log_InlineLogERROR(&DAT_1400be0b0);
  }
LAB_140058f17:
  __security_check_cookie(local_48 ^ (ulonglong)auStackY_4a8);
  return;
}


// ==== CNpc::vf_0x10 @ 1400596b0  int vf_0x10(longlong * param_1, int param_2)

int CNpc::vf_0x10(longlong *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (**(code **)(**(longlong **)(param_1[0x12] + 0x10) + 0x10))
                    (*(longlong **)(param_1[0x12] + 0x10),0xf);
  iVar2 = (**(code **)(*param_1 + 0x48))(param_1);
  return (iVar2 + 1 + param_2) / 2 + iVar1;
}


// ==== CNpc::vf_0xd8 @ 140059990  undefined vf_0xd8(longlong * param_1, int param_2, int param_3)

void CNpc::vf_0xd8(longlong *param_1,int param_2,int param_3)

{
  bool bVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined7 extraout_var;
  longlong lVar5;
  undefined1 auStackY_4c8 [32];
  undefined8 local_468 [132];
  ulonglong local_48;
  
  local_48 = DAT_140103510 ^ (ulonglong)auStackY_4c8;
  FUN_1400623e0(local_468);
  uVar3 = (**(code **)(*param_1 + 0x30))(param_1);
  uVar2 = (**(code **)(*param_1 + 0x18))(param_1);
  iVar4 = (**(code **)(param_1[-2] + 8))(param_1 + -2);
  bVar1 = FUN_140062530((longlong)local_468,iVar4,(short)param_2,(short)param_3,uVar2,0x92,
                        (short)param_2,(short)param_3,uVar3);
  if ((int)CONCAT71(extraout_var,bVar1) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  else {
    uVar3 = (**(code **)(param_1[-2] + 8))(param_1 + -2);
    lVar5 = FUN_14001c200();
    FUN_14001c5f0(lVar5,uVar3,(longlong)local_468);
  }
  *(undefined4 *)((longlong)param_1 + 0x1c) = 0;
  if (param_1[0x11] != 0) {
    FUN_14004e140(param_1[0x11],param_1,param_2,param_3);
  }
  *(int *)((longlong)param_1 + 0x24) = param_2;
  *(int *)(param_1 + 5) = param_3;
  FUN_140062430(local_468);
  __security_check_cookie(local_48 ^ (ulonglong)auStackY_4c8);
  return;
}


// ==== CNpc::vf_0x100 @ 140059ad0  undefined vf_0x100(longlong * param_1, int param_2, int param_3, int param_4, int param_5)

void CNpc::vf_0x100(longlong *param_1,int param_2,int param_3,int param_4,int param_5)

{
  bool bVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  int iVar7;
  undefined4 uVar8;
  undefined7 extraout_var;
  longlong lVar9;
  undefined1 auStackY_4c8 [32];
  undefined8 local_468 [132];
  ulonglong local_48;
  
  local_48 = DAT_140103510 ^ (ulonglong)auStackY_4c8;
  iVar7 = (**(code **)(*param_1 + 0x38))();
  if ((iVar7 == param_2) && (iVar7 = (**(code **)(*param_1 + 0x40))(param_1), iVar7 == param_3)) {
    iVar7 = (**(code **)(*param_1 + 0x38))(param_1);
    if ((iVar7 != param_4) || (iVar7 = (**(code **)(*param_1 + 0x40))(param_1), iVar7 != param_5)) {
      *(undefined4 *)((longlong)param_1 + 0x1c) = 0;
      FUN_140058610((longlong)(param_1 + -2),param_4,param_5);
    }
  }
  else {
    FUN_1400623e0(local_468);
    uVar8 = (**(code **)(*param_1 + 0x30))(param_1);
    uVar2 = (**(code **)(*param_1 + 0x40))(param_1);
    uVar3 = (**(code **)(*param_1 + 0x38))(param_1);
    uVar4 = (**(code **)(*param_1 + 0x18))(param_1);
    uVar5 = (**(code **)(*param_1 + 0x40))(param_1);
    uVar6 = (**(code **)(*param_1 + 0x38))(param_1);
    iVar7 = (**(code **)(param_1[-2] + 8))(param_1 + -2);
    bVar1 = FUN_140062530((longlong)local_468,iVar7,uVar6,uVar5,uVar4,0x92,uVar3,uVar2,uVar8);
    if ((int)CONCAT71(extraout_var,bVar1) == 0) {
      log_InlineLogERROR(&DAT_1400be0b0);
    }
    else {
      uVar8 = (**(code **)(param_1[-2] + 8))(param_1 + -2);
      lVar9 = FUN_14001c200();
      FUN_14001c5f0(lVar9,uVar8,(longlong)local_468);
    }
    FUN_140062430(local_468);
  }
  __security_check_cookie(local_48 ^ (ulonglong)auStackY_4c8);
  return;
}


// ==== CNpc::vf_0x108 @ 14005a230  undefined vf_0x108(longlong param_1, char * param_2)

void CNpc::vf_0x108(longlong param_1,char *param_2)

{
  longlong *plVar1;
  uint uVar2;
  char *pcVar3;
  undefined1 auStack_468 [32];
  undefined4 local_448;
  undefined4 local_440;
  undefined4 local_438;
  undefined4 local_430;
  undefined4 local_428;
  uint local_420;
  char local_418 [1024];
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_468;
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0x90) + 0x10);
  uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
  if ((uVar2 >> 3 & 1) != 0) {
    pcVar3 = strstr(param_2,"[GM]");
    if (pcVar3 == (char *)0x0) {
      pcVar3 = strstr(param_2,"[PM]");
      if (pcVar3 == (char *)0x0) goto LAB_14005a30b;
    }
    plVar1 = *(longlong **)(*(longlong *)(param_1 + 0x90) + 0x10);
    (**(code **)(*plVar1 + 0x18))(plVar1,1);
    local_420 = (uint)*(byte *)(param_1 + 0x2f);
    local_428 = *(undefined4 *)(param_1 + 0x1c);
    local_430 = *(undefined4 *)(param_1 + 0x74);
    local_438 = *(undefined4 *)(param_1 + 0x28);
    local_440 = *(undefined4 *)(param_1 + 0x24);
    local_448 = *(undefined4 *)(param_1 + 8);
    sprintf(local_418,"Name:%s,ID:%d,Mode:%d,Coord(%d,%d),Target:%d,PathSize=%d,IsDie:%d");
    FUN_1400586b0((longlong *)(param_1 + -0x10),local_418,(char *)0x0);
  }
LAB_14005a30b:
  __security_check_cookie(local_18 ^ (ulonglong)auStack_468);
  return;
}


// ==== CNpc::vf_0x50 @ 14005ac70  undefined8 vf_0x50(longlong * param_1)

undefined8 CNpc::vf_0x50(longlong *param_1)

{
  uint *in_RAX;
  undefined1 local_28 [40];
  
  if ((*(char *)((longlong)param_1 + 0x2f) == '\0') && (0 < *(int *)((longlong)param_1 + 0xc))) {
    in_RAX = (uint *)(**(code **)(*param_1 + 0x20))(param_1,local_28);
    if ((*in_RAX >> 5 & 1) == 0) {
      return CONCAT71((int7)((ulonglong)in_RAX >> 8),1);
    }
  }
  return (ulonglong)in_RAX & 0xffffffffffffff00;
}


// ==== CNpc::vf_0xb8 @ 14005acb0  undefined8 vf_0xb8(longlong * param_1)

undefined8 CNpc::vf_0xb8(longlong *param_1)

{
  uint *puVar1;
  undefined1 local_38 [24];
  undefined1 local_20 [24];
  
  puVar1 = (uint *)(**(code **)(*param_1 + 0x20))(param_1,local_38);
  if ((*puVar1 >> 10 & 1) == 0) {
    puVar1 = (uint *)(**(code **)(*param_1 + 0x20))(param_1,local_20);
    if ((*puVar1 >> 0x1b & 1) == 0) {
      return CONCAT71((int7)((ulonglong)puVar1 >> 8),1);
    }
  }
  return (ulonglong)puVar1 & 0xffffffffffffff00;
}


// ==== CNpc::vf_0xe0 @ 14005ada0  undefined vf_0xe0(longlong param_1)

void CNpc::vf_0xe0(longlong param_1)

{
  longlong *plVar1;
  ulong uVar2;
  undefined8 uVar3;
  
  if (*(int *)(param_1 + 0x140) != 0) {
    uVar2 = tq::TimeGet(0);
    if (uVar2 / 1000 < (uint)(*(int *)(param_1 + 0x140) + *(int *)(param_1 + 0x13c))) {
      return;
    }
    *(undefined4 *)(param_1 + 0x140) = 0;
    *(undefined4 *)(param_1 + 0x13c) = 0;
  }
  uVar3 = FUN_14005a660(param_1 + -0x10);
  if ((char)uVar3 == '\0') {
    plVar1 = *(longlong **)(param_1 + 0xb0);
    if (plVar1 != (longlong *)0x0) {
      (**(code **)(*plVar1 + 0x20))(plVar1,param_1 + -0x10);
    }
    return;
  }
  FUN_14005a3b0(param_1 + -0x10);
  return;
}


// ==== CNpc::vf_0x0 @ 14005b550  undefined vf_0x0(longlong param_1, uint param_2)

void CNpc::vf_0x0(longlong param_1,uint param_2)

{
  vf_0x0((undefined8 *)(param_1 + -0x10),param_2);
  return;
}


// ==== CNpc::vf_0x28 @ 14005b560  undefined vf_0x28(longlong param_1)

void CNpc::vf_0x28(longlong param_1)

{
  vf_0x8(param_1 + -0x10);
  return;
}


// ==== CNpc::vf_0xd0 @ 14005b570  undefined vf_0xd0(longlong param_1)

void CNpc::vf_0xd0(longlong param_1)

{
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 8) = 1;
  return;
}


// ==== CNpc::vf_0x0 @ 14005c610  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CNpc::vf_0x0(undefined8 *param_1,uint param_2)

{
  FUN_14005b4b0(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CNpc::vf_0xc8 @ 14005c640  undefined vf_0xc8(longlong * param_1, longlong * param_2)

void CNpc::vf_0xc8(longlong *param_1,longlong *param_2)

{
  longlong lVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  ulonglong uVar9;
  
  if ((param_1[0x26] != 0) && (bVar2 = FUN_140069750(param_1[0x26]), bVar2)) {
    uVar9 = (**(code **)(**(longlong **)(param_1[0x12] + 0x10) + 0x10))
                      (*(longlong **)(param_1[0x12] + 0x10),0x15);
    if (((uVar9 & 1) == 0) &&
       (uVar9 = (**(code **)(**(longlong **)(param_1[0x12] + 0x10) + 0x10))
                          (*(longlong **)(param_1[0x12] + 0x10),0x15), (uVar9 & 2) == 0)) {
      return;
    }
    if ((((param_1[0x26] != 0) && (bVar2 = FUN_140069750(param_1[0x26]), bVar2)) &&
        (param_1[0x26] != 0)) && (iVar4 = FUN_1400696e0(param_1[0x26]), iVar4 == 3)) {
      return;
    }
  }
  if (param_2 == (longlong *)0x0) {
    return;
  }
  uVar5 = (**(code **)(*param_2 + 0x28))(param_2);
  *(undefined4 *)(param_1 + 0xf) = uVar5;
  cVar3 = (**(code **)(*param_1 + 0x50))(param_1);
  if (cVar3 == '\0') {
    if (param_1[0x26] == 0) {
      return;
    }
    bVar2 = FUN_140069750(param_1[0x26]);
    if (!bVar2) {
      return;
    }
    FUN_140069850((undefined4 *)param_1[0x26],4);
    return;
  }
  uVar9 = FUN_14005ad00((longlong)(param_1 + -2));
  if ((char)uVar9 == '\0') {
    return;
  }
  uVar6 = (**(code **)(**(longlong **)(param_1[0x12] + 0x10) + 0x10))
                    (*(longlong **)(param_1[0x12] + 0x10),0x15);
  if ((~(byte)(uVar6 >> 0xf) & 1) == 0) {
LAB_14005c7bf:
    lVar1 = *param_1;
    uVar5 = (**(code **)(*param_2 + 0x40))(param_2);
    uVar8 = (**(code **)(*param_2 + 0x38))(param_2);
    iVar4 = (**(code **)(lVar1 + 8))(param_1,uVar8,uVar5);
    cVar3 = (**(code **)(*param_1 + 0x60))(param_1);
    if (((cVar3 == '\0') || (cVar3 = (**(code **)(*param_2 + 0x60))(param_2), cVar3 != '\0')) ||
       (2 < iVar4)) {
      uVar9 = FUN_14005aed0((longlong)(param_1 + -2),param_2);
      if ((((char)uVar9 != '\0') &&
          (((int)param_1[1] < 7 || (cVar3 = FUN_140058830((longlong)(param_1 + -2)), cVar3 != '\0'))
          )) && (((int)param_1[1] != 6 || (iVar4 = tq::RandGet(100), 0x4f < iVar4)))) {
        uVar5 = (**(code **)(*param_2 + 0x28))(param_2);
        *(undefined4 *)((longlong)param_1 + 0x74) = uVar5;
        iVar4 = tq::RandGet(100);
        if (iVar4 < 0x50) {
          *(undefined4 *)(param_1 + 1) = 7;
          iVar4 = (**(code **)(*param_2 + 0x40))(param_2);
          iVar7 = (**(code **)(*param_2 + 0x38))(param_2);
          FUN_1400580e0((longlong)(param_1 + -2),iVar7,iVar4,0);
          if (0 < *(int *)((longlong)param_1 + 0x1c)) {
            return;
          }
        }
        uVar6 = FUN_140057d30((longlong)(param_1 + -2));
        if ((char)uVar6 != '\0') {
          *(undefined4 *)((longlong)param_1 + 0x1c) = 0;
          *(undefined4 *)(param_1 + 1) = 6;
          uVar5 = (**(code **)(**(longlong **)(param_1[0x12] + 0x10) + 0x10))
                            (*(longlong **)(param_1[0x12] + 0x10),0x10);
          iVar4 = (**(code **)(*param_2 + 0x40))(param_2);
          iVar7 = (**(code **)(*param_2 + 0x38))(param_2);
          FUN_1400580e0((longlong)(param_1 + -2),iVar7,iVar4,uVar5);
        }
      }
    }
    else {
      uVar5 = (**(code **)(*param_2 + 0x28))(param_2);
      lVar1 = *param_1;
      *(undefined4 *)((longlong)param_1 + 0x74) = uVar5;
      uVar5 = (**(code **)(*param_2 + 0x48))(param_2);
      iVar7 = (**(code **)(lVar1 + 0x10))(param_1,uVar5);
      iVar7 = iVar7 - iVar4;
      FUN_14005b760(param_1 + -2,iVar7);
      if (iVar7 < *(int *)((longlong)param_1 + 0x1c)) {
        *(int *)((longlong)param_1 + 0x1c) = iVar7;
      }
      *(undefined4 *)(param_1 + 1) = 7;
    }
  }
  else {
    uVar9 = (**(code **)(**(longlong **)(param_1[0x12] + 0x10) + 0x10))
                      (*(longlong **)(param_1[0x12] + 0x10),0x15);
    if ((uVar9 & 1) == 0) {
      uVar5 = (**(code **)(*param_2 + 0x28))(param_2);
      *(undefined4 *)((longlong)param_1 + 0x74) = uVar5;
    }
    else {
      iVar4 = *(int *)((longlong)param_1 + 0xc);
      iVar7 = (**(code **)(**(longlong **)(param_1[0x12] + 0x10) + 0x10))
                        (*(longlong **)(param_1[0x12] + 0x10),0x11);
      if (iVar7 <= iVar4) goto LAB_14005c7bf;
    }
    *(undefined4 *)((longlong)param_1 + 0x1c) = 0;
    *(undefined4 *)(param_1 + 1) = 6;
  }
  return;
}


// ==== CNpc::vf_0xf0 @ 14005f450  undefined vf_0xf0(longlong param_1)

void CNpc::vf_0xf0(longlong param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(param_1 + -0x10);
  FUN_14005f020(plVar1);
  if (plVar1 != (longlong *)0x0) {
    (**(code **)*plVar1)(plVar1,1);
  }
  return;
}


