// NpcServer.exe :: CSingleMap<class_INpc>  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CSingleMap<class_INpc>::vf_0x8 @ 140030100  undefined vf_0x8(undefined8 * param_1)

void CSingleMap<class_INpc>::vf_0x8(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    (**(code **)*param_1)(param_1,1);
  }
  return;
}


// ==== CSingleMap<class_INpc>::vf_0x48 @ 1400302a0  undefined8 vf_0x48(longlong param_1)

undefined8 CSingleMap<class_INpc>::vf_0x48(longlong param_1)

{
  return *(undefined8 *)(param_1 + 0x48);
}


// ==== CSingleMap<class_INpc>::vf_0x10 @ 140030c50  undefined8 * vf_0x10(longlong param_1, undefined8 * param_2)

undefined8 * CSingleMap<class_INpc>::vf_0x10(longlong param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  
  uVar1 = **(undefined8 **)(param_1 + 0x40);
  *param_2 = *(undefined8 *)(param_1 + 0x10);
  param_2[1] = uVar1;
  return param_2;
}


// ==== CSingleMap<class_INpc>::vf_0x18 @ 140030c70  undefined8 * vf_0x18(longlong param_1, undefined8 * param_2)

undefined8 * CSingleMap<class_INpc>::vf_0x18(longlong param_1,undefined8 *param_2)

{
  param_2[1] = *(undefined8 *)(param_1 + 0x40);
  *param_2 = *(undefined8 *)(param_1 + 0x10);
  return param_2;
}


// ==== CSingleMap<class_INpc>::vf_0x20 @ 140030c90  undefined8 vf_0x20(undefined8 param_1, longlong * param_2)

undefined8 CSingleMap<class_INpc>::vf_0x20(undefined8 param_1,longlong *param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_2;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_2;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140030cb2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140030cb2:
  if (param_2[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return *(undefined8 *)(param_2[1] + 0x20);
}


// ==== CSingleMap<class_INpc>::vf_0x40 @ 140030cd0  undefined8 vf_0x40(longlong param_1, uint param_2)

undefined8 CSingleMap<class_INpc>::vf_0x40(longlong param_1,uint param_2)

{
  char cVar1;
  longlong *plVar2;
  undefined8 *puVar3;
  longlong lVar4;
  undefined8 *puVar5;
  undefined8 uVar6;
  longlong *plVar7;
  undefined8 *puVar8;
  longlong lVar9;
  longlong local_38;
  undefined8 *local_30;
  longlong local_28;
  undefined8 local_20;
  longlong *local_18;
  longlong local_10;
  
  puVar8 = (undefined8 *)(*(undefined8 **)(param_1 + 0x40))[1];
  cVar1 = *(char *)((longlong)puVar8 + 0x29);
  puVar3 = *(undefined8 **)(param_1 + 0x40);
  while (cVar1 == '\0') {
    if (*(uint *)(puVar8 + 3) < param_2) {
      puVar5 = (undefined8 *)puVar8[2];
      puVar8 = puVar3;
    }
    else {
      puVar5 = (undefined8 *)*puVar8;
    }
    puVar3 = puVar8;
    puVar8 = puVar5;
    cVar1 = *(char *)((longlong)puVar5 + 0x29);
  }
  puVar8 = *(undefined8 **)(param_1 + 0x40);
  local_30 = puVar3;
  local_38 = *(longlong *)(param_1 + 0x10);
  if (*(longlong *)(param_1 + 0x10) == 0) {
    _invalid_parameter_noinfo();
  }
  if ((puVar3 == puVar8) || (param_2 < *(uint *)(puVar3 + 3))) {
    plVar7 = &local_28;
    local_20 = *(undefined8 *)(param_1 + 0x40);
    local_28 = *(longlong *)(param_1 + 0x10);
  }
  else {
    plVar7 = &local_38;
  }
  plVar2 = (longlong *)*plVar7;
  lVar9 = *(longlong *)(param_1 + 0x40);
  local_18 = plVar2;
  local_10 = plVar7[1];
  if ((plVar2 == (longlong *)0x0) || (plVar2 != *(longlong **)(param_1 + 0x10))) {
    _invalid_parameter_noinfo();
  }
  lVar4 = local_10;
  if (local_10 == lVar9) {
    uVar6 = 0;
  }
  else {
    if (plVar2 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar9 = 0;
    }
    else {
      lVar9 = *plVar2;
    }
    if (lVar4 == *(longlong *)(lVar9 + 0x30)) {
      _invalid_parameter_noinfo();
    }
    uVar6 = *(undefined8 *)(lVar4 + 0x20);
  }
  return uVar6;
}


// ==== CSingleMap<class_INpc>::vf_0x28 @ 140031590  undefined8 vf_0x28(longlong * param_1, longlong * param_2)

undefined8 CSingleMap<class_INpc>::vf_0x28(longlong *param_1,longlong *param_2)

{
  longlong lVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 *puVar5;
  ulonglong extraout_RAX;
  uint local_res10 [2];
  
  if (param_2 != (longlong *)0x0) {
    iVar3 = (**(code **)(*param_2 + 0x28))(param_2);
    if (iVar3 != 0) {
      if ((char)param_1[1] != '\0') {
        lVar1 = *param_1;
        uVar4 = (**(code **)(*param_2 + 0x28))(param_2);
        cVar2 = (**(code **)(lVar1 + 0x30))(param_1,uVar4);
        if (cVar2 != '\0') {
          log_InlineLogERROR(&DAT_1400be0b0);
        }
      }
      local_res10[0] = (**(code **)(*param_2 + 0x28))(param_2);
      puVar5 = FUN_140031350(param_1 + 2,local_res10);
      *puVar5 = param_2;
      return CONCAT71((int7)((ulonglong)puVar5 >> 8),1);
    }
  }
  log_InlineLogERROR(&DAT_1400be0b0);
  return extraout_RAX & 0xffffffffffffff00;
}


// ==== CSingleMap<class_INpc>::vf_0x30 @ 140031670  bool vf_0x30(longlong * param_1, uint param_2)

bool CSingleMap<class_INpc>::vf_0x30(longlong *param_1,uint param_2)

{
  longlong *plVar1;
  longlong lVar2;
  uint local_res10 [2];
  longlong local_38;
  longlong lStack_30;
  undefined8 local_28 [4];
  
  local_res10[0] = param_2;
  if ((char)param_1[1] == '\0') {
    lVar2 = FUN_140031450(param_1 + 2,local_res10);
    return lVar2 != 0;
  }
  FUN_1400308e0(param_1 + 2,&local_38,local_res10);
  lVar2 = param_1[8];
  if ((local_38 == 0) || (local_38 != param_1[2])) {
    _invalid_parameter_noinfo();
  }
  if (lStack_30 != lVar2) {
    plVar1 = (longlong *)(**(code **)(*param_1 + 0x20))(param_1,&local_38);
    (**(code **)(*plVar1 + 0xf0))(plVar1);
    FUN_140029570(param_1 + 2,local_28,&local_38);
    return true;
  }
  return false;
}


// ==== CSingleMap<class_INpc>::vf_0x38 @ 140031750  bool vf_0x38(longlong param_1, uint param_2)

bool CSingleMap<class_INpc>::vf_0x38(longlong param_1,uint param_2)

{
  longlong lVar1;
  uint local_res10 [6];
  
  local_res10[0] = param_2;
  lVar1 = FUN_140031450((longlong *)(param_1 + 0x10),local_res10);
  return lVar1 != 0;
}


// ==== CSingleMap<class_INpc>::vf_0x0 @ 1400317e0  longlong * vf_0x0(longlong * param_1, uint param_2)

longlong * CSingleMap<class_INpc>::vf_0x0(longlong *param_1,uint param_2)

{
  *param_1 = (longlong)vftable;
  FUN_1400310f0(param_1);
  FUN_14002d9a0(param_1 + 2);
  operator_delete((void *)param_1[2]);
  *param_1 = (longlong)ISingleMap<class_INpc>::vftable;
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


