// NpcServer.exe :: CNpcGenerator  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CNpcGenerator::vf_0x20 @ 14005f4e0  undefined4 vf_0x20(longlong param_1)

undefined4 CNpcGenerator::vf_0x20(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x10);
}


// ==== CNpcGenerator::vf_0x30 @ 14005f4f0  undefined4 vf_0x30(longlong param_1)

undefined4 CNpcGenerator::vf_0x30(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x18);
}


// ==== CNpcGenerator::vf_0x38 @ 14005f500  undefined vf_0x38(longlong param_1)

void CNpcGenerator::vf_0x38(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00014005f50c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),5);
  return;
}


// ==== CNpcGenerator::vf_0x8 @ 14005f510  undefined4 vf_0x8(longlong param_1)

undefined4 CNpcGenerator::vf_0x8(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x50);
}


// ==== CNpcGenerator::vf_0x48 @ 14005f530  undefined4 vf_0x48(longlong param_1)

undefined4 CNpcGenerator::vf_0x48(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x1c);
}


// ==== CNpcGenerator::vf_0x50 @ 14005f540  undefined vf_0x50(longlong param_1)

void CNpcGenerator::vf_0x50(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00014005f54c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),2);
  return;
}


// ==== CNpcGenerator::vf_0x58 @ 14005f550  undefined vf_0x58(longlong param_1)

void CNpcGenerator::vf_0x58(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00014005f55c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),3);
  return;
}


// ==== CNpcGenerator::vf_0x60 @ 14005f570  undefined vf_0x60(longlong param_1)

void CNpcGenerator::vf_0x60(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00014005f57c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),4);
  return;
}


// ==== CNpcGenerator::vf_0x68 @ 14005f580  ulonglong vf_0x68(longlong param_1, int param_2, int param_3)

ulonglong CNpcGenerator::vf_0x68(longlong param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  ulonglong uVar4;
  
  uVar4 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),2);
  if ((int)uVar4 <= param_2) {
    iVar1 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),2);
    iVar2 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),4);
    uVar4 = (ulonglong)(uint)(iVar2 + iVar1);
    if ((param_2 < iVar2 + iVar1) &&
       (uVar4 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))
                          (*(longlong **)(param_1 + 0x38),3), (int)uVar4 <= param_3)) {
      iVar1 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))
                        (*(longlong **)(param_1 + 0x38),3);
      iVar2 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))
                        (*(longlong **)(param_1 + 0x38),5);
      uVar3 = iVar2 + iVar1;
      uVar4 = (ulonglong)uVar3;
      if (param_3 < (int)uVar3) {
        return CONCAT71((uint7)(uint3)(uVar3 >> 8),1);
      }
    }
  }
  return uVar4 & 0xffffffffffffff00;
}


// ==== CNpcGenerator::vf_0x70 @ 14005f630  undefined8 vf_0x70(longlong param_1, int param_2, int param_3, int param_4, int param_5)

undefined8 CNpcGenerator::vf_0x70(longlong param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  ulonglong in_RAX;
  
  if ((*(longlong *)(param_1 + 0x28) != 0) &&
     (in_RAX = (**(code **)(**(longlong **)(param_1 + 0x28) + 8))(), (int)in_RAX == param_2)) {
    iVar1 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),2);
    in_RAX = (ulonglong)(uint)(iVar1 - param_5);
    if (iVar1 - param_5 <= param_3) {
      iVar1 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))
                        (*(longlong **)(param_1 + 0x38),2);
      iVar2 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))
                        (*(longlong **)(param_1 + 0x38),4);
      uVar3 = iVar2 + iVar1 + param_5;
      in_RAX = (ulonglong)uVar3;
      if (param_3 < (int)uVar3) {
        iVar1 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))
                          (*(longlong **)(param_1 + 0x38),3);
        in_RAX = (ulonglong)(uint)(iVar1 - param_5);
        if (iVar1 - param_5 <= param_4) {
          iVar1 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))
                            (*(longlong **)(param_1 + 0x38),3);
          iVar2 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))
                            (*(longlong **)(param_1 + 0x38),5);
          uVar3 = iVar2 + iVar1 + param_5;
          in_RAX = (ulonglong)uVar3;
          if (param_4 < (int)uVar3) {
            return (ulonglong)(uint3)(uVar3 >> 8) << 8;
          }
        }
      }
    }
  }
  return CONCAT71((int7)(in_RAX >> 8),1);
}


// ==== CNpcGenerator::vf_0x98 @ 14005f790  undefined vf_0x98(void)

void CNpcGenerator::vf_0x98(void)

{
  return;
}


// ==== CNpcGenerator::vf_0xa0 @ 14005f7a0  undefined8 vf_0xa0(undefined8 * param_1)

undefined8 CNpcGenerator::vf_0xa0(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    (**(code **)*param_1)(param_1,1);
  }
  return 0;
}


// ==== CNpcGenerator::vf_0x40 @ 14005f8b0  undefined vf_0x40(longlong param_1)

void CNpcGenerator::vf_0x40(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00014005f8b7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(longlong **)(param_1 + 0x28) + 8))();
  return;
}


// ==== CNpcGenerator::vf_0x88 @ 14005f8c0  undefined vf_0x88(longlong param_1, undefined4 * param_2)

void CNpcGenerator::vf_0x88(longlong param_1,undefined4 *param_2)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined1 auStack_468 [32];
  undefined8 local_448;
  undefined8 local_438 [132];
  ulonglong local_18;
  
  local_448 = 0xfffffffffffffffe;
  local_18 = DAT_140103510 ^ (ulonglong)auStack_468;
  iVar1 = param_2[4];
  if ((iVar1 != 0) && (param_2[5] != 0)) {
    lVar4 = FUN_14001c7a0();
    plVar5 = (longlong *)FUN_140027a40(lVar4,iVar1);
    if ((plVar5 != (longlong *)0x0) &&
       ((lVar4 = (**(code **)(*plVar5 + 0x80))(plVar5), lVar4 != 0 &&
        (bVar2 = FUN_140049310(lVar4,param_2[2],param_2[3]), bVar2)))) {
      *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + 1;
      *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + 1;
      FUN_140063a10(local_438);
      uVar6 = FUN_140063a90((longlong)local_438,param_2);
      if ((int)uVar6 == 0) {
        FUN_140063a60(local_438);
      }
      else {
        uVar3 = (**(code **)(*plVar5 + 0x28))(plVar5);
        lVar4 = FUN_14001c200();
        FUN_14001c5f0(lVar4,uVar3,(longlong)local_438);
        FUN_140063a60(local_438);
      }
    }
  }
  __security_check_cookie(local_18 ^ (ulonglong)auStack_468);
  return;
}


// ==== CNpcGenerator::vf_0x78 @ 14005fb30  undefined vf_0x78(longlong * param_1)

void CNpcGenerator::vf_0x78(longlong *param_1)

{
  int iVar1;
  
  if (0 < (int)param_1[2]) {
    *(int *)(param_1 + 2) = (int)param_1[2] + -1;
    iVar1 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],8);
    if ((0 < iVar1) &&
       (*(int *)(param_1 + 3) = (int)param_1[3] + -1, (int)param_1[3] < (int)param_1[2])) {
      (**(code **)(*param_1 + 8))(param_1);
      log_InlineLogMessage("GeneratorID[%u]: m_nGenAmount[%d] < m_nAmount[%d]");
      *(int *)(param_1 + 3) = (int)param_1[2];
    }
    return;
  }
  (**(code **)(*param_1 + 8))();
                    /* WARNING: Could not recover jumptable at 0x00014005fb54. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  log_InlineLogERROR("GeneratorID[%u]: m_nAmount <= 0");
  return;
}


// ==== CNpcGenerator::vf_0x90 @ 140060030  undefined vf_0x90(longlong * param_1, int param_2)

void CNpcGenerator::vf_0x90(longlong *param_1,int param_2)

{
  int iVar1;
  
  if (param_2 != 0) {
    *(int *)(param_1 + 2) = (int)param_1[2] + 1;
    iVar1 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],8);
    if ((0 < iVar1) && (DAT_1401028c0 < (int)param_1[3] - (int)param_1[2])) {
      (**(code **)(*param_1 + 8))(param_1);
      log_InlineLogERROR("GeneratorID[%u]: m_nGenAmount[%d] > m_nAmount[%d]");
    }
    return;
  }
  log_InlineLogERROR(&DAT_1400be0b0);
  return;
}


// ==== CNpcGenerator::vf_0x28 @ 1400600d0  int * vf_0x28(longlong param_1, int * param_2)

int * CNpcGenerator::vf_0x28(longlong param_1,int *param_2)

{
  longlong *plVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),2);
  iVar3 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),4);
  plVar1 = *(longlong **)(param_1 + 0x38);
  *param_2 = iVar3 / 2 + iVar2;
  iVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,3);
  iVar3 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),5);
  param_2[1] = iVar3 / 2 + iVar2;
  return param_2;
}


// ==== CNpcGenerator::vf_0x0 @ 140060ad0  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CNpcGenerator::vf_0x0(undefined8 *param_1,uint param_2)

{
  FUN_14005fab0(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CNpcGenerator::vf_0x80 @ 140060b00  undefined8 vf_0x80(longlong * param_1, int param_2)

undefined8 CNpcGenerator::vf_0x80(longlong *param_1,int param_2)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  ulong uVar5;
  ulong uVar6;
  int iVar7;
  undefined4 uVar8;
  ulonglong uVar9;
  undefined8 uVar10;
  
  if ((int)param_1[9] != 0) {
    return 0;
  }
  uVar2 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],0x12);
  if (((uVar2 >> 1 & 1) != 0) &&
     (iVar3 = (**(code **)(*param_1 + 0x48))(param_1), iVar3 <= (int)param_1[4])) {
    return 0;
  }
  iVar3 = (**(code **)(*param_1 + 0x48))(param_1);
  if (iVar3 <= (int)param_1[3]) {
    return 0;
  }
  iVar3 = (**(code **)(*param_1 + 0x30))(param_1);
  iVar4 = (**(code **)(*param_1 + 0x20))(param_1);
  if (iVar3 - iVar4 < param_2) {
    iVar4 = (**(code **)(*param_1 + 0x30))(param_1);
    iVar3 = (**(code **)(*param_1 + 0x20))(param_1);
    iVar3 = (param_2 - iVar4) + iVar3;
    iVar4 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],10);
    if (iVar4 != 0) {
      uVar5 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],0xb);
      uVar6 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],10);
      bVar1 = tq::IsTimeRange(uVar6,uVar5,0);
      if (!bVar1) {
        return 0;
      }
    }
    iVar4 = (**(code **)(*param_1 + 0x48))(param_1);
    if (iVar4 - (int)param_1[3] < iVar3) {
      iVar3 = (**(code **)(*param_1 + 0x48))(param_1);
      iVar3 = iVar3 - (int)param_1[3];
    }
    uVar9 = FUN_140002700((int *)(param_1 + 6));
    if ((char)uVar9 != '\0') {
      iVar4 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],7);
      if (599 < iVar4) {
        iVar4 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],7);
        iVar7 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],7);
        iVar7 = tq::RandGet(iVar7);
        *(int *)(param_1 + 6) = iVar7 + iVar4;
        uVar5 = tq::TimeGet(0);
        *(uint *)((longlong)param_1 + 0x34) = uVar5 / 1000;
      }
      uVar8 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],8);
      *(undefined4 *)((longlong)param_1 + 0x14) = uVar8;
    }
    iVar4 = *(int *)((longlong)param_1 + 0x14);
    if (iVar4 < 1) {
      return 0;
    }
    if (iVar4 < iVar3) {
      iVar3 = iVar4;
    }
    uVar10 = FUN_14005fc90(param_1,iVar3);
    return uVar10;
  }
  return 0;
}


