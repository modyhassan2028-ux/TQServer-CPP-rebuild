// NpcServer.exe :: _unnamed  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== FUN_1400547a0 @ 1400547a0  undefined FUN_1400547a0(longlong * param_1, ulonglong param_2, undefined8 * param_3)

void FUN_1400547a0(longlong *param_1,ulonglong param_2,undefined8 *param_3)

{
  longlong *plVar1;
  longlong *plVar2;
  ulonglong uVar3;
  longlong lVar4;
  undefined8 *puVar5;
  longlong *plVar6;
  longlong local_28;
  longlong *plStack_20;
  
  plVar1 = (longlong *)param_1[4];
  plVar2 = (longlong *)param_1[3];
  uVar3 = ((longlong)plVar1 - (longlong)plVar2) / 0x30;
  if (uVar3 < param_2) {
    if (plVar1 < plVar2) {
      _invalid_parameter_noinfo();
    }
    local_28 = *param_1;
    plStack_20 = plVar1;
    FUN_140054130((longlong)param_1,(longlong)&local_28,param_2 - (param_1[4] - param_1[3]) / 0x30,
                  param_3);
    goto LAB_140054945;
  }
  if (uVar3 <= param_2) goto LAB_140054945;
  if (plVar1 < plVar2) {
    _invalid_parameter_noinfo();
  }
  uVar3 = param_1[3];
  if ((ulonglong)param_1[4] < uVar3) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)*param_1;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar4 = 0;
  }
  else {
    lVar4 = *plVar2;
  }
  plVar6 = (longlong *)(uVar3 + param_2 * 0x30);
  if (*(longlong **)(lVar4 + 0x20) < plVar6) {
LAB_1400548b9:
    _invalid_parameter_noinfo();
  }
  else {
    if (plVar2 == (longlong *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar2;
    }
    if (plVar6 < *(longlong **)(lVar4 + 0x18)) goto LAB_1400548b9;
  }
  if ((plVar6 < (longlong *)param_1[3]) || ((longlong *)param_1[4] < plVar6)) {
    _invalid_parameter_noinfo();
  }
  lVar4 = *param_1;
  if ((plVar1 < (longlong *)param_1[3]) || ((longlong *)param_1[4] < plVar1)) {
    _invalid_parameter_noinfo();
  }
  if ((lVar4 == 0) || (lVar4 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (plVar6 != plVar1) {
    puVar5 = (undefined8 *)FUN_1400520b0(plVar1,(longlong *)param_1[4],(longlong)plVar6);
    FUN_140052130(puVar5,(undefined8 *)param_1[4]);
    param_1[4] = (longlong)puVar5;
  }
LAB_140054945:
  if ((void *)param_3[3] != (void *)0x0) {
    operator_delete((void *)param_3[3]);
  }
  param_3[3] = 0;
  param_3[4] = 0;
  param_3[5] = 0;
  operator_delete((void *)*param_3);
  return;
}


// ==== FUN_140054990 @ 140054990  undefined FUN_140054990(longlong param_1, longlong param_2, ulonglong param_3, longlong param_4)

void FUN_140054990(longlong param_1,longlong param_2,ulonglong param_3,longlong param_4)

{
  ulonglong uVar1;
  undefined8 *puVar2;
  code *pcVar3;
  longlong *plVar4;
  longlong *plVar5;
  longlong lVar6;
  longlong lVar7;
  ulonglong uVar8;
  longlong local_68 [6];
  
  lVar7 = *(longlong *)(param_1 + 0x18);
  if (lVar7 == 0) {
    uVar8 = 0;
  }
  else {
    lVar6 = *(longlong *)(param_1 + 0x28) - lVar7;
    lVar6 = lVar6 / 6 + (lVar6 >> 0x3f);
    uVar8 = (lVar6 >> 3) - (lVar6 >> 0x3f);
  }
  if (param_3 != 0) {
    lVar7 = (*(longlong *)(param_1 + 0x20) - lVar7) / 0x30;
    if (0x555555555555555U - lVar7 < param_3) {
      FUN_1400497c0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    uVar1 = lVar7 + param_3;
    if (uVar8 < uVar1) {
      if (0x555555555555555 - (uVar8 >> 1) < uVar8) {
        uVar8 = 0;
      }
      else {
        uVar8 = uVar8 + (uVar8 >> 1);
      }
      if (uVar8 < uVar1) {
        uVar8 = uVar1;
      }
      plVar4 = (longlong *)FUN_14004b370(param_1 + 0x10,uVar8);
      lVar7 = *(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18);
      lVar7 = lVar7 / 6 + (lVar7 >> 0x3f);
      lVar7 = (lVar7 >> 3) - (lVar7 >> 0x3f);
      FUN_140053ba0(plVar4 + lVar7 * 6,param_3,param_4);
      FUN_140053c20(*(longlong **)(param_1 + 0x18),*(longlong **)(param_2 + 8),plVar4);
      FUN_140053c20(*(longlong **)(param_2 + 8),*(longlong **)(param_1 + 0x20),
                    plVar4 + (lVar7 + param_3) * 6);
      puVar2 = *(undefined8 **)(param_1 + 0x18);
      lVar7 = *(longlong *)(param_1 + 0x20);
      if (puVar2 != (undefined8 *)0x0) {
        FUN_140053a70(puVar2,*(undefined8 **)(param_1 + 0x20));
        operator_delete(*(void **)(param_1 + 0x18));
      }
      *(longlong **)(param_1 + 0x28) = plVar4 + uVar8 * 6;
      *(longlong **)(param_1 + 0x20) = plVar4 + (param_3 + (lVar7 - (longlong)puVar2) / 0x30) * 6;
      *(longlong **)(param_1 + 0x18) = plVar4;
    }
    else if ((ulonglong)((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_2 + 8)) / 0x30) <
             param_3) {
      FUN_140051170(local_68,param_4);
      FUN_140053c20(*(longlong **)(param_2 + 8),*(longlong **)(param_1 + 0x20),
                    *(longlong **)(param_2 + 8) + param_3 * 6);
      FUN_140053ba0(*(undefined8 **)(param_1 + 0x20),
                    param_3 - ((longlong)*(undefined8 **)(param_1 + 0x20) -
                              *(longlong *)(param_2 + 8)) / 0x30,(longlong)local_68);
      *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + param_3 * 0x30;
      lVar7 = *(longlong *)(param_1 + 0x20);
      for (plVar4 = *(longlong **)(param_2 + 8); plVar4 != (longlong *)(lVar7 + param_3 * -0x30);
          plVar4 = plVar4 + 6) {
        FUN_1400522b0(plVar4,local_68);
      }
      FUN_140051ad0(local_68);
    }
    else {
      FUN_140051170(local_68,param_4);
      plVar4 = *(longlong **)(param_1 + 0x20);
      plVar5 = FUN_140053c20(plVar4 + param_3 * -6,plVar4,plVar4);
      *(longlong **)(param_1 + 0x20) = plVar5;
      FUN_1400545e0(*(longlong **)(param_2 + 8),plVar4 + param_3 * -6,plVar4);
      plVar5 = *(longlong **)(param_2 + 8);
      plVar4 = plVar5 + param_3 * 6;
      for (; plVar5 != plVar4; plVar5 = plVar5 + 6) {
        FUN_1400522b0(plVar5,local_68);
      }
      FUN_140051ad0(local_68);
    }
  }
  return;
}


// ==== FUN_140054d60 @ 140054d60  undefined FUN_140054d60(undefined8 * param_1)

void FUN_140054d60(undefined8 *param_1)

{
  if ((undefined8 *)param_1[3] != (undefined8 *)0x0) {
    FUN_140053a70((undefined8 *)param_1[3],(undefined8 *)param_1[4]);
    operator_delete((void *)param_1[3]);
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140054dc0 @ 140054dc0  undefined FUN_140054dc0(longlong * param_1)

void FUN_140054dc0(longlong *param_1)

{
  longlong *plVar1;
  longlong *plVar2;
  longlong lVar3;
  undefined8 *puVar4;
  
  plVar1 = (longlong *)param_1[4];
  if (plVar1 < (longlong *)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)param_1[3];
  if ((longlong *)param_1[4] < plVar2) {
    _invalid_parameter_noinfo();
  }
  if ((plVar2 < (longlong *)param_1[3]) || ((longlong *)param_1[4] < plVar2)) {
    _invalid_parameter_noinfo();
  }
  lVar3 = *param_1;
  if ((plVar1 < (longlong *)param_1[3]) || ((longlong *)param_1[4] < plVar1)) {
    _invalid_parameter_noinfo();
  }
  if ((lVar3 == 0) || (lVar3 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (plVar2 != plVar1) {
    puVar4 = (undefined8 *)FUN_140053030(plVar1,(longlong *)param_1[4],(longlong)plVar2);
    FUN_140053a70(puVar4,(undefined8 *)param_1[4]);
    param_1[4] = (longlong)puVar4;
  }
  return;
}


// ==== FUN_140054e90 @ 140054e90  undefined FUN_140054e90(longlong * param_1, ulonglong param_2)

void FUN_140054e90(longlong *param_1,ulonglong param_2)

{
  longlong *plVar1;
  longlong *local_38 [3];
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  
  plVar1 = (longlong *)operator_new(8);
  local_38[0] = (longlong *)0x0;
  if (plVar1 != (longlong *)0x0) {
    *plVar1 = (longlong)local_38;
    local_38[0] = plVar1;
  }
  local_20 = 0;
  local_18 = 0;
  local_10 = 0;
  FUN_1400547a0(param_1,param_2,local_38);
  return;
}


// ==== FUN_140054f20 @ 140054f20  undefined FUN_140054f20(longlong * param_1, ulonglong param_2, undefined8 * param_3)

void FUN_140054f20(longlong *param_1,ulonglong param_2,undefined8 *param_3)

{
  longlong *plVar1;
  longlong *plVar2;
  ulonglong uVar3;
  undefined8 *puVar4;
  longlong *plVar5;
  longlong lVar6;
  longlong lVar7;
  longlong local_38;
  longlong *plStack_30;
  
  plVar1 = (longlong *)param_1[4];
  plVar2 = (longlong *)param_1[3];
  uVar3 = ((longlong)plVar1 - (longlong)plVar2) / 0x30;
  if (uVar3 < param_2) {
    if (plVar1 < plVar2) {
      _invalid_parameter_noinfo();
    }
    local_38 = *param_1;
    plStack_30 = plVar1;
    FUN_140054990((longlong)param_1,(longlong)&local_38,param_2 - (param_1[4] - param_1[3]) / 0x30,
                  (longlong)param_3);
    goto LAB_1400550c4;
  }
  if (uVar3 <= param_2) goto LAB_1400550c4;
  if (plVar1 < plVar2) {
    _invalid_parameter_noinfo();
  }
  uVar3 = param_1[3];
  if ((ulonglong)param_1[4] < uVar3) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)*param_1;
  lVar7 = 0;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar6 = lVar7;
  }
  else {
    lVar6 = *plVar2;
  }
  plVar5 = (longlong *)(uVar3 + param_2 * 0x30);
  if (*(longlong **)(lVar6 + 0x20) < plVar5) {
LAB_140055038:
    _invalid_parameter_noinfo();
  }
  else {
    if (plVar2 != (longlong *)0x0) {
      lVar7 = *plVar2;
    }
    if (plVar5 < *(longlong **)(lVar7 + 0x18)) goto LAB_140055038;
  }
  if ((plVar5 < (longlong *)param_1[3]) || ((longlong *)param_1[4] < plVar5)) {
    _invalid_parameter_noinfo();
  }
  lVar7 = *param_1;
  if ((plVar1 < (longlong *)param_1[3]) || ((longlong *)param_1[4] < plVar1)) {
    _invalid_parameter_noinfo();
  }
  if ((lVar7 == 0) || (lVar7 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (plVar5 != plVar1) {
    puVar4 = (undefined8 *)FUN_140053030(plVar1,(longlong *)param_1[4],(longlong)plVar5);
    FUN_140053a70(puVar4,(undefined8 *)param_1[4]);
    param_1[4] = (longlong)puVar4;
  }
LAB_1400550c4:
  FUN_140051ad0(param_3);
  return;
}


// ==== FUN_1400550f0 @ 1400550f0  undefined8 * FUN_1400550f0(undefined8 * param_1)

undefined8 * FUN_1400550f0(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  
  FUN_1400695c0(param_1);
  *param_1 = CGameMap::vftable;
  puVar1 = (undefined8 *)operator_new(8);
  puVar3 = (undefined8 *)0x0;
  puVar2 = puVar3;
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_1 + 3;
    puVar2 = puVar1;
  }
  param_1[3] = puVar2;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  puVar1 = (undefined8 *)operator_new(8);
  puVar2 = puVar3;
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_1 + 0xb;
    puVar2 = puVar1;
  }
  param_1[0xb] = puVar2;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  CGameMap::vf_0x18((longlong)param_1,0x1008);
  param_1[2] = 0;
  puVar2 = (undefined8 *)operator_new(8);
  if (puVar2 != (undefined8 *)0x0) {
    *puVar2 = 0;
    puVar3 = puVar2;
  }
  param_1[9] = puVar3;
  *(undefined4 *)(param_1 + 10) = 0;
  *(undefined1 *)(param_1 + 0x11) = 1;
  *(undefined4 *)((longlong)param_1 + 0x8c) = 0;
  return param_1;
}


// ==== FUN_140055230 @ 140055230  undefined FUN_140055230(undefined8 * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_140055230(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  longlong *plVar1;
  undefined8 *puVar2;
  
  *param_1 = CGameMap::vftable;
  plVar1 = (longlong *)param_1[9];
  if (plVar1 != (longlong *)0x0) {
    puVar2 = (undefined8 *)*plVar1;
    if (puVar2 != (undefined8 *)0x0) {
      (**(code **)*puVar2)(puVar2,0,param_3,param_4,0xfffffffffffffffe);
    }
    operator_delete(plVar1);
  }
  if ((longlong *)param_1[2] != (longlong *)0x0) {
    (**(code **)(*(longlong *)param_1[2] + 0x60))();
  }
  if ((undefined8 *)param_1[0xe] != (undefined8 *)0x0) {
    FUN_140052130((undefined8 *)param_1[0xe],(undefined8 *)param_1[0xf]);
    operator_delete((void *)param_1[0xe]);
  }
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  operator_delete((void *)param_1[0xb]);
  if ((undefined8 *)param_1[6] != (undefined8 *)0x0) {
    FUN_140053a70((undefined8 *)param_1[6],(undefined8 *)param_1[7]);
    operator_delete((void *)param_1[6]);
  }
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  operator_delete((void *)param_1[3]);
  FUN_1400695e0(param_1);
  return;
}


// ==== FUN_140055330 @ 140055330  undefined FUN_140055330(longlong * param_1, ulonglong param_2)

void FUN_140055330(longlong *param_1,ulonglong param_2)

{
  longlong *plVar1;
  longlong *local_38 [3];
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  
  plVar1 = (longlong *)operator_new(8);
  local_38[0] = (longlong *)0x0;
  if (plVar1 != (longlong *)0x0) {
    *plVar1 = (longlong)local_38;
    local_38[0] = plVar1;
  }
  local_20 = 0;
  local_18 = 0;
  local_10 = 0;
  FUN_140054f20(param_1,param_2,local_38);
  return;
}


// ==== FUN_140056060 @ 140056060  undefined8 FUN_140056060(longlong * param_1, uint param_2)

ulonglong FUN_140056060(longlong *param_1,uint param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  longlong *plVar6;
  ulonglong uVar7;
  undefined8 uVar8;
  longlong *plVar9;
  longlong lVar10;
  longlong *plVar11;
  longlong *plVar12;
  longlong lVar13;
  ulonglong extraout_RAX;
  undefined8 *puVar14;
  undefined8 extraout_RAX_00;
  ulonglong uVar15;
  longlong lVar16;
  ulonglong uVar17;
  longlong *plVar18;
  undefined4 *puVar19;
  int iVar20;
  longlong *local_res18;
  longlong **local_res20;
  longlong *local_118 [3];
  undefined4 *local_100;
  undefined4 *local_f8;
  longlong local_f0;
  longlong *local_e8 [3];
  undefined4 *local_d0;
  undefined4 *local_c8;
  longlong local_c0;
  longlong *local_b8;
  undefined4 *puStack_b0;
  undefined8 local_a8;
  longlong *local_98;
  undefined4 *puStack_90;
  longlong *local_78 [3];
  undefined8 local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  
  local_48 = 0xfffffffffffffffe;
  plVar6 = (longlong *)(**(code **)(**(longlong **)param_1[9] + 0x10))(*(longlong **)param_1[9],3);
  uVar3 = (**(code **)(*plVar6 + 0x48))(plVar6);
  iVar4 = (**(code **)(*param_1 + 8))(param_1);
  plVar6 = (longlong *)(**(code **)(**(longlong **)param_1[9] + 0x10))(*(longlong **)param_1[9],3);
  (**(code **)(*plVar6 + 0xb0))(plVar6,param_2);
  plVar6 = (longlong *)(**(code **)(**(longlong **)param_1[9] + 0x10))(*(longlong **)param_1[9],4);
  uVar7 = (**(code **)(*plVar6 + 0x58))(plVar6);
  if ((uVar7 >> 10 & 1) == 0) {
    plVar6 = (longlong *)(**(code **)(**(longlong **)param_1[9] + 0x10))(*(longlong **)param_1[9],3)
    ;
    (**(code **)(*plVar6 + 0xb0))(plVar6,uVar3);
    uVar8 = (**(code **)(**(longlong **)param_1[9] + 0x58))();
    uVar7 = CONCAT71((int7)((ulonglong)uVar8 >> 8),1);
  }
  else {
    (**(code **)(**(longlong **)param_1[9] + 0x58))();
    local_res18 = (longlong *)operator_new(8);
    plVar6 = (longlong *)0x0;
    local_118[0] = plVar6;
    if (local_res18 != (longlong *)0x0) {
      *local_res18 = (longlong)local_118;
      local_118[0] = local_res18;
    }
    local_100 = (undefined4 *)0x0;
    local_f8 = (undefined4 *)0x0;
    local_f0 = 0;
    local_res20 = (longlong **)local_res18;
    plVar9 = (longlong *)FUN_14001c210();
    plVar9 = (longlong *)(**(code **)(*plVar9 + 0x10))(plVar9);
    lVar10 = (**(code **)(*plVar9 + 0x10))(plVar9);
    plVar9 = plVar6;
    if (lVar10 != 0) {
      do {
        plVar11 = (longlong *)FUN_14001c210();
        plVar11 = (longlong *)(**(code **)(*plVar11 + 0x10))(plVar11);
        plVar11 = (longlong *)
                  (**(code **)(*plVar11 + 0x18))
                            (plVar11,plVar9,
                             "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\gamemap.cpp"
                             ,0x252);
        if ((plVar11 != (longlong *)0x0) &&
           (iVar5 = (**(code **)(plVar11[2] + 0x30))(), iVar5 == iVar4)) {
          uVar3 = (**(code **)(*plVar11 + 8))(plVar11);
          puVar19 = local_f8;
          local_res18 = (longlong *)CONCAT44(local_res18._4_4_,uVar3);
          plVar11 = plVar6;
          if (local_100 != (undefined4 *)0x0) {
            plVar11 = (longlong *)(local_f0 - (longlong)local_100 >> 2);
          }
          if ((longlong *)((longlong)local_f8 - (longlong)local_100 >> 2) < plVar11) {
            *local_f8 = uVar3;
            local_f8 = local_f8 + 1;
          }
          else {
            if (local_f8 < local_100) {
              _invalid_parameter_noinfo();
            }
            puVar2 = local_100;
            plVar11 = local_118[0];
            local_b8 = local_118[0];
            puStack_b0 = puVar19;
            plVar18 = plVar6;
            if (((longlong)local_f8 - (longlong)local_100 & 0xfffffffffffffffcU) != 0) {
              if (local_f8 < local_100) {
                _invalid_parameter_noinfo();
              }
              if ((plVar11 == (longlong *)0x0) || (plVar11 != local_118[0])) {
                _invalid_parameter_noinfo();
              }
              plVar18 = (longlong *)((longlong)puVar19 - (longlong)puVar2 >> 2);
            }
            local_98 = local_b8;
            puStack_90 = puStack_b0;
            FUN_14002d450((longlong)local_118,(longlong)&local_98,1,(undefined4 *)&local_res18);
            puVar19 = local_100;
            if (local_f8 < local_100) {
              _invalid_parameter_noinfo();
            }
            plVar11 = local_118[0];
            if (local_118[0] == (longlong *)0x0) {
              _invalid_parameter_noinfo();
              plVar12 = plVar6;
            }
            else {
              plVar12 = (longlong *)*local_118[0];
            }
            if (puVar19 + (longlong)plVar18 <= (undefined4 *)plVar12[4]) {
              plVar12 = plVar6;
              if (plVar11 != (longlong *)0x0) {
                plVar12 = (longlong *)*plVar11;
              }
              if ((undefined4 *)plVar12[3] <= puVar19 + (longlong)plVar18) goto LAB_140056332;
            }
            _invalid_parameter_noinfo();
          }
        }
LAB_140056332:
        plVar9 = (longlong *)((longlong)plVar9 + 1);
        plVar11 = (longlong *)FUN_14001c210();
        plVar11 = (longlong *)(**(code **)(*plVar11 + 0x10))(plVar11);
        plVar11 = (longlong *)(**(code **)(*plVar11 + 0x10))(plVar11);
      } while (plVar9 < plVar11);
    }
    puVar19 = local_100;
    plVar9 = local_118[0];
    if (local_f8 < local_100) {
      _invalid_parameter_noinfo();
      plVar9 = local_118[0];
    }
    while( true ) {
      puVar2 = local_f8;
      if (local_f8 < local_100) {
        _invalid_parameter_noinfo();
      }
      if ((plVar9 == (longlong *)0x0) || (plVar9 != local_118[0])) {
        _invalid_parameter_noinfo();
      }
      if (puVar19 == puVar2) break;
      if (plVar9 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        plVar11 = plVar6;
      }
      else {
        plVar11 = (longlong *)*plVar9;
      }
      if ((undefined4 *)plVar11[4] <= puVar19) {
        _invalid_parameter_noinfo();
      }
      log_InlineLogWARNING("CGameMap::ChangeMapDoc. DelUser[%u]");
      plVar11 = (longlong *)FUN_14001c210();
      plVar11 = (longlong *)(**(code **)(*plVar11 + 0x10))(plVar11);
      if (plVar9 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        plVar18 = plVar6;
      }
      else {
        plVar18 = (longlong *)*plVar9;
      }
      if ((undefined4 *)plVar18[4] <= puVar19) {
        _invalid_parameter_noinfo();
      }
      (**(code **)(*plVar11 + 0x28))(plVar11,*puVar19);
      if (plVar9 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        plVar11 = plVar6;
      }
      else {
        plVar11 = (longlong *)*plVar9;
      }
      if ((undefined4 *)plVar11[4] <= puVar19) {
        _invalid_parameter_noinfo();
      }
      puVar19 = puVar19 + 1;
    }
    local_res18 = (longlong *)operator_new(8);
    if (local_res18 != (longlong *)0x0) {
      *local_res18 = (longlong)local_e8;
      plVar6 = local_res18;
    }
    local_d0 = (undefined4 *)0x0;
    local_c8 = (undefined4 *)0x0;
    local_c0 = 0;
    local_res20 = (longlong **)local_res18;
    local_e8[0] = plVar6;
    lVar10 = FUN_14001c7a0();
    lVar10 = FUN_140025c40(lVar10);
    plVar6 = (longlong *)**(undefined8 **)(lVar10 + 0x40);
    plVar9 = *(longlong **)(lVar10 + 0x10);
LAB_1400564a2:
    plVar11 = *(longlong **)(lVar10 + 0x40);
    if ((plVar9 == (longlong *)0x0) || (plVar9 != *(longlong **)(lVar10 + 0x10))) {
      _invalid_parameter_noinfo();
    }
    puVar19 = local_d0;
    if (plVar6 != plVar11) {
      if (plVar9 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar16 = 0;
      }
      else {
        lVar16 = *plVar9;
      }
      if (plVar6 == *(longlong **)(lVar16 + 0x30)) {
        _invalid_parameter_noinfo();
      }
      plVar11 = (longlong *)plVar6[4];
      if (plVar11 == (longlong *)0x0) {
        log_InlineLogERROR(&DAT_1400be0b0);
      }
      if (plVar9 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
      }
      if (*(char *)((longlong)plVar6 + 0x29) == '\0') {
        plVar18 = (longlong *)plVar6[2];
        if (*(char *)((longlong)plVar18 + 0x29) == '\0') {
          cVar1 = *(char *)(*plVar18 + 0x29);
          plVar6 = plVar18;
          plVar18 = (longlong *)*plVar18;
          while (cVar1 == '\0') {
            cVar1 = *(char *)(*plVar18 + 0x29);
            plVar6 = plVar18;
            plVar18 = (longlong *)*plVar18;
          }
        }
        else {
          cVar1 = *(char *)(plVar6[1] + 0x29);
          plVar12 = (longlong *)plVar6[1];
          plVar18 = plVar6;
          while ((plVar6 = plVar12, cVar1 == '\0' && (plVar18 == (longlong *)plVar6[2]))) {
            cVar1 = *(char *)(plVar6[1] + 0x29);
            plVar12 = (longlong *)plVar6[1];
            plVar18 = plVar6;
          }
        }
      }
      else {
        _invalid_parameter_noinfo();
      }
      if (((plVar11 != (longlong *)0x0) &&
          (plVar11 = (longlong *)(**(code **)(*plVar11 + 0xb0))(plVar11,0x1040,0),
          plVar11 != (longlong *)0x0)) &&
         (iVar5 = (**(code **)(plVar11[2] + 0x30))(), iVar5 == iVar4)) {
        uVar3 = (**(code **)(*plVar11 + 8))(plVar11);
        puVar19 = local_c8;
        local_res18 = (longlong *)CONCAT44(local_res18._4_4_,uVar3);
        if (local_d0 == (undefined4 *)0x0) {
          uVar7 = 0;
        }
        else {
          uVar7 = local_c0 - (longlong)local_d0 >> 2;
        }
        if ((ulonglong)((longlong)local_c8 - (longlong)local_d0 >> 2) < uVar7) {
          *local_c8 = uVar3;
          local_c8 = local_c8 + 1;
          goto LAB_1400564a2;
        }
        if (local_c8 < local_d0) {
          _invalid_parameter_noinfo();
        }
        puVar2 = local_d0;
        plVar11 = local_e8[0];
        local_b8 = local_e8[0];
        puStack_b0 = puVar19;
        if (((longlong)local_c8 - (longlong)local_d0 & 0xfffffffffffffffcU) == 0) {
          lVar16 = 0;
        }
        else {
          if (local_c8 < local_d0) {
            _invalid_parameter_noinfo();
          }
          if ((plVar11 == (longlong *)0x0) || (plVar11 != local_e8[0])) {
            _invalid_parameter_noinfo();
          }
          lVar16 = (longlong)puVar19 - (longlong)puVar2 >> 2;
        }
        local_98 = local_b8;
        puStack_90 = puStack_b0;
        FUN_14002d450((longlong)local_e8,(longlong)&local_98,1,(undefined4 *)&local_res18);
        puVar19 = local_d0;
        if (local_c8 < local_d0) {
          _invalid_parameter_noinfo();
        }
        plVar11 = local_e8[0];
        if (local_e8[0] == (longlong *)0x0) {
          _invalid_parameter_noinfo();
          lVar13 = 0;
        }
        else {
          lVar13 = *local_e8[0];
        }
        if (puVar19 + lVar16 <= *(undefined4 **)(lVar13 + 0x20)) {
          if (plVar11 == (longlong *)0x0) {
            lVar13 = 0;
          }
          else {
            lVar13 = *plVar11;
          }
          if (*(undefined4 **)(lVar13 + 0x18) <= puVar19 + lVar16) goto LAB_1400564a2;
        }
        _invalid_parameter_noinfo();
      }
      goto LAB_1400564a2;
    }
    plVar6 = local_e8[0];
    if (local_c8 < local_d0) {
      _invalid_parameter_noinfo();
      plVar6 = local_e8[0];
    }
    while( true ) {
      puVar2 = local_c8;
      if (local_c8 < local_d0) {
        _invalid_parameter_noinfo();
      }
      if ((plVar6 == (longlong *)0x0) || (plVar6 != local_e8[0])) {
        _invalid_parameter_noinfo();
      }
      if (puVar19 == puVar2) break;
      if (plVar6 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar10 = 0;
      }
      else {
        lVar10 = *plVar6;
      }
      if (*(undefined4 **)(lVar10 + 0x20) <= puVar19) {
        _invalid_parameter_noinfo();
      }
      log_InlineLogWARNING("CGameMap::ChangeMapDoc. DelMonster[%u]");
      lVar10 = FUN_14001c7a0();
      plVar9 = (longlong *)FUN_140025c40(lVar10);
      if (plVar6 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar10 = 0;
      }
      else {
        lVar10 = *plVar6;
      }
      if (*(undefined4 **)(lVar10 + 0x20) <= puVar19) {
        _invalid_parameter_noinfo();
      }
      (**(code **)(*plVar9 + 0x30))(plVar9,*puVar19);
      if (plVar6 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar10 = 0;
      }
      else {
        lVar10 = *plVar6;
      }
      if (*(undefined4 **)(lVar10 + 0x20) <= puVar19) {
        _invalid_parameter_noinfo();
      }
      puVar19 = puVar19 + 1;
    }
    lVar10 = FUN_1400515a0(param_2);
    if (lVar10 == 0) {
      log_InlineLogERROR(&DAT_1400c8708);
      if (local_d0 != (undefined4 *)0x0) {
        operator_delete(local_d0);
      }
      local_d0 = (undefined4 *)0x0;
      local_c8 = (undefined4 *)0x0;
      local_c0 = 0;
      operator_delete(local_e8[0]);
      if (local_100 != (undefined4 *)0x0) {
        operator_delete(local_100);
      }
      local_100 = (undefined4 *)0x0;
      local_f8 = (undefined4 *)0x0;
      local_f0 = 0;
      operator_delete(local_118[0]);
      uVar7 = extraout_RAX & 0xffffffffffffff00;
    }
    else {
      param_1[2] = lVar10;
      plVar6 = param_1 + 3;
      local_res18 = plVar6;
      FUN_140054dc0(plVar6);
      iVar4 = (**(code **)(*(longlong *)param_1[2] + 0x28))();
      local_res20 = local_78;
      local_b8 = (longlong *)operator_new(8);
      if (local_b8 == (longlong *)0x0) {
        local_78[0] = (longlong *)0x0;
      }
      else {
        *local_b8 = (longlong)local_78;
        local_78[0] = local_b8;
      }
      plVar9 = (longlong *)0x0;
      local_60 = 0;
      local_58 = 0;
      local_50 = 0;
      local_98 = local_b8;
      FUN_140054f20(plVar6,(longlong)((iVar4 + -1) / 0x12 + 1),local_78);
      FUN_140053ed0(param_1 + 0xb);
      iVar4 = (**(code **)(*(longlong *)param_1[2] + 0x28))();
      local_res20 = local_78;
      local_b8 = (longlong *)operator_new(8);
      local_78[0] = plVar9;
      if (local_b8 != (longlong *)0x0) {
        *local_b8 = (longlong)local_78;
        local_78[0] = local_b8;
      }
      local_60 = 0;
      local_58 = 0;
      local_50 = 0;
      local_98 = local_b8;
      FUN_1400547a0(param_1 + 0xb,(longlong)iVar4,local_78);
      plVar11 = plVar9;
      plVar18 = plVar9;
      if (0 < (int)((param_1[0xf] - param_1[0xe]) / 0x30)) {
        do {
          iVar4 = (**(code **)(*(longlong *)param_1[2] + 0x20))();
          iVar5 = (int)plVar18;
          if ((ulonglong)((param_1[0xf] - param_1[0xe]) / 0x30) <= (ulonglong)(longlong)iVar5) {
            _invalid_parameter_noinfo();
          }
          FUN_140051960((longlong *)((longlong)iVar5 * 0x30 + param_1[0xe]),(longlong)iVar4,0);
          uVar15 = 0;
          uVar7 = uVar15;
          while( true ) {
            if ((longlong *)((param_1[0xf] - param_1[0xe]) / 0x30) <= plVar11) {
              _invalid_parameter_noinfo();
            }
            lVar10 = param_1[0xe];
            if ((int)(*(longlong *)((longlong)plVar9 + lVar10 + 0x20) -
                      *(longlong *)((longlong)plVar9 + lVar10 + 0x18) >> 2) <= (int)uVar7) break;
            if ((longlong *)((param_1[0xf] - lVar10) / 0x30) <= plVar11) {
              _invalid_parameter_noinfo();
            }
            lVar10 = param_1[0xe];
            if ((ulonglong)
                (*(longlong *)((longlong)plVar9 + lVar10 + 0x20) -
                 *(longlong *)((longlong)plVar9 + lVar10 + 0x18) >> 2) <= uVar15) {
              _invalid_parameter_noinfo();
            }
            *(undefined4 *)(*(longlong *)((longlong)plVar9 + lVar10 + 0x18) + uVar15 * 4) = 0;
            uVar7 = (ulonglong)((int)uVar7 + 1);
            uVar15 = uVar15 + 1;
          }
          plVar9 = plVar9 + 6;
          plVar6 = local_res18;
          plVar11 = (longlong *)((longlong)plVar11 + 1);
          plVar18 = (longlong *)(ulonglong)(iVar5 + 1U);
        } while ((int)(iVar5 + 1U) < (int)((param_1[0xf] - lVar10) / 0x30));
      }
      uVar17 = 0;
      uVar7 = uVar17;
      uVar15 = uVar17;
      if (0 < (int)((plVar6[4] - plVar6[3]) / 0x30)) {
        do {
          iVar5 = 0;
          iVar4 = (**(code **)(*(longlong *)param_1[2] + 0x20))();
          iVar20 = (int)uVar15;
          if ((ulonglong)((plVar6[4] - plVar6[3]) / 0x30) <= (ulonglong)(longlong)iVar20) {
            _invalid_parameter_noinfo();
          }
          lVar10 = plVar6[3];
          puVar14 = (undefined8 *)FUN_140067830((undefined1 *)&local_98);
          local_b8 = (longlong *)*puVar14;
          puStack_b0 = (undefined4 *)puVar14[1];
          local_a8 = puVar14[2];
          FUN_140052dd0((longlong *)((longlong)iVar20 * 0x30 + lVar10),
                        (longlong)((iVar4 + -1) / 0x12 + 1),&local_b8);
          FUN_140067850((longlong)&local_98);
          while( true ) {
            if ((ulonglong)((plVar6[4] - plVar6[3]) / 0x30) <= uVar7) {
              _invalid_parameter_noinfo();
            }
            if ((int)((*(longlong *)(uVar17 + 0x20 + plVar6[3]) -
                      *(longlong *)(uVar17 + 0x18 + plVar6[3])) / 0x18) <= iVar5) break;
            if ((ulonglong)((plVar6[4] - plVar6[3]) / 0x30) <= uVar7) {
              _invalid_parameter_noinfo();
            }
            lVar10 = plVar6[3];
            if ((ulonglong)
                ((*(longlong *)(uVar17 + 0x20 + lVar10) - *(longlong *)(uVar17 + 0x18 + lVar10)) /
                0x18) <= (ulonglong)(longlong)iVar5) {
              _invalid_parameter_noinfo();
            }
            FUN_140069310(*(longlong *)(uVar17 + 0x18 + lVar10) + (longlong)iVar5 * 0x18);
            iVar5 = iVar5 + 1;
          }
          uVar17 = uVar17 + 0x30;
          uVar7 = uVar7 + 1;
          uVar15 = (ulonglong)(iVar20 + 1U);
        } while ((int)(iVar20 + 1U) < (int)((plVar6[4] - plVar6[3]) / 0x30));
      }
      if (local_d0 != (undefined4 *)0x0) {
        operator_delete(local_d0);
      }
      local_d0 = (undefined4 *)0x0;
      local_c8 = (undefined4 *)0x0;
      local_c0 = 0;
      operator_delete(local_e8[0]);
      if (local_100 != (undefined4 *)0x0) {
        operator_delete(local_100);
      }
      local_100 = (undefined4 *)0x0;
      local_f8 = (undefined4 *)0x0;
      local_f0 = 0;
      operator_delete(local_118[0]);
      uVar7 = CONCAT71((int7)((ulonglong)extraout_RAX_00 >> 8),1);
    }
  }
  return uVar7;
}


// ==== FUN_140056da0 @ 140056da0  undefined FUN_140056da0(undefined8 * param_1)

void FUN_140056da0(undefined8 *param_1)

{
  *param_1 = CNpcType::vftable;
  if ((longlong *)param_1[2] != (longlong *)0x0) {
    (**(code **)(*(longlong *)param_1[2] + 0x58))();
  }
  FUN_1400695e0(param_1);
  return;
}


// ==== FUN_140056de0 @ 140056de0  bool FUN_140056de0(longlong param_1)

bool FUN_140056de0(longlong param_1)

{
  char cVar1;
  
  if (*(longlong *)(param_1 + 0x10) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return false;
  }
  cVar1 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x30))();
  return cVar1 != '\0';
}


// ==== FUN_140056e30 @ 140056e30  undefined FUN_140056e30(longlong param_1)

void FUN_140056e30(longlong param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)
           (**(code **)(**(longlong **)(param_1 + 8) + 0x20))
                     (*(longlong **)(param_1 + 8),&DAT_140102d90);
                    /* WARNING: Could not recover jumptable at 0x000140056e4f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x40))(plVar1);
  return;
}


// ==== FUN_140056ef0 @ 140056ef0  undefined8 * FUN_140056ef0(undefined8 * param_1, undefined1 param_2)

undefined8 * FUN_140056ef0(undefined8 *param_1,undefined1 param_2)

{
  *param_1 = IGameData::vftable;
  *param_1 = CGameData<&char*_szNpcType,&char*_szID>::vftable;
  *(undefined1 *)(param_1 + 2) = param_2;
  param_1[1] = 0;
  return param_1;
}


// ==== FUN_140056f30 @ 140056f30  undefined FUN_140056f30(undefined8 * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_140056f30(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 *puVar1;
  
  *param_1 = CGameData<&char*_szNpcType,&char*_szID>::vftable;
  puVar1 = (undefined8 *)param_1[1];
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,*(char *)(param_1 + 2) == '\0',param_3,param_4,0xfffffffffffffffe);
  }
  *param_1 = IGameData::vftable;
  return;
}


// ==== FUN_1400573b0 @ 1400573b0  undefined8 * FUN_1400573b0(undefined1 param_1)

undefined8 * FUN_1400573b0(undefined1 param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x18);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = IGameData::vftable;
    *puVar1 = CGameData<&char*_szNpcType,&char*_szID>::vftable;
    *(undefined1 *)(puVar1 + 2) = param_1;
    puVar1[1] = 0;
  }
  return puVar1;
}


// ==== FUN_140057400 @ 140057400  undefined8 * FUN_140057400(undefined8 * param_1)

undefined8 * FUN_140057400(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  FUN_1400695c0(param_1);
  *param_1 = CNpcType::vftable;
  CGameMap::vf_0x18((longlong)param_1,0x4000);
  puVar1 = (undefined8 *)operator_new(0x18);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = IGameData::vftable;
    *puVar1 = CGameData<&char*_szNpcType,&char*_szID>::vftable;
    *(undefined1 *)(puVar1 + 2) = 0;
    puVar1[1] = 0;
  }
  param_1[2] = puVar1;
  return param_1;
}


// ==== FUN_140057490 @ 140057490  undefined FUN_140057490(undefined8 * param_1)

void FUN_140057490(undefined8 *param_1)

{
  *param_1 = IRole::vftable;
  return;
}


// ==== FUN_1400579a0 @ 1400579a0  undefined8 FUN_1400579a0(longlong param_1)

undefined8 FUN_1400579a0(longlong param_1)

{
  if (*(longlong *)(param_1 + 0x10) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return *(undefined8 *)(param_1 + 0x10);
  }
  return *(undefined8 *)(param_1 + 0x10);
}


// ==== FUN_140057a10 @ 140057a10  undefined FUN_140057a10(undefined8 * param_1)

void FUN_140057a10(undefined8 *param_1)

{
  *param_1 = IRole::vftable;
  return;
}


// ==== FUN_140057c10 @ 140057c10  undefined FUN_140057c10(longlong param_1)

void FUN_140057c10(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x000140057c1a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(longlong **)(param_1 + 0xa0) + 8))();
  return;
}


// ==== FUN_140057c20 @ 140057c20  uint FUN_140057c20(longlong param_1)

uint FUN_140057c20(longlong param_1)

{
  longlong *plVar1;
  uint uVar2;
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
  uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
  return uVar2 >> 10 & 1;
}


// ==== FUN_140057c50 @ 140057c50  uint FUN_140057c50(longlong param_1)

uint FUN_140057c50(longlong param_1)

{
  longlong *plVar1;
  int iVar2;
  uint uVar3;
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
  iVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0xd);
  uVar3 = (iVar2 % 10000000) * 0x14f8b589;
  if ((iVar2 % 10000000) / 100000 == 5) {
    uVar3 = -(iVar2 % 100000 >> 0x1f);
    if (((iVar2 % 100000) / 1000) * 1000 == 0) {
      return 1;
    }
  }
  return uVar3 & 0xffffff00;
}


// ==== FUN_140057cf0 @ 140057cf0  bool FUN_140057cf0(longlong param_1)

bool FUN_140057cf0(longlong param_1)

{
  return *(int *)(param_1 + 0x18) == 0;
}


// ==== FUN_140057d00 @ 140057d00  uint FUN_140057d00(longlong param_1)

uint FUN_140057d00(longlong param_1)

{
  longlong *plVar1;
  uint uVar2;
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
  uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
  return ~(uVar2 >> 8) & 1;
}


// ==== FUN_140057d30 @ 140057d30  uint FUN_140057d30(longlong param_1)

uint FUN_140057d30(longlong param_1)

{
  longlong *plVar1;
  uint uVar2;
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
  uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
  return ~(uVar2 >> 0xf) & 1;
}


// ==== FUN_140057d90 @ 140057d90  uint FUN_140057d90(longlong param_1)

uint FUN_140057d90(longlong param_1)

{
  longlong *plVar1;
  uint uVar2;
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
  uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
  return uVar2 >> 0xb & 1;
}


// ==== FUN_140057df0 @ 140057df0  uint FUN_140057df0(longlong param_1)

uint FUN_140057df0(longlong param_1)

{
  longlong *plVar1;
  uint uVar2;
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
  uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
  return uVar2 >> 7 & 1;
}


// ==== FUN_140057e20 @ 140057e20  uint FUN_140057e20(longlong param_1)

uint FUN_140057e20(longlong param_1)

{
  longlong *plVar1;
  uint uVar2;
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
  uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
  return uVar2 >> 3 & 1;
}


// ==== FUN_140057e50 @ 140057e50  uint FUN_140057e50(longlong param_1)

uint FUN_140057e50(longlong param_1)

{
  longlong *plVar1;
  uint uVar2;
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
  uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
  return uVar2 >> 5 & 1;
}


// ==== FUN_140057e80 @ 140057e80  uint FUN_140057e80(longlong param_1)

uint FUN_140057e80(longlong param_1)

{
  longlong *plVar1;
  uint uVar2;
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
  uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
  return uVar2 >> 9 & 1;
}


// ==== FUN_140057eb0 @ 140057eb0  uint FUN_140057eb0(longlong param_1)

uint FUN_140057eb0(longlong param_1)

{
  longlong *plVar1;
  uint uVar2;
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
  uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
  return uVar2 >> 8 & 1;
}


// ==== FUN_140057ef0 @ 140057ef0  uint FUN_140057ef0(longlong param_1)

uint FUN_140057ef0(longlong param_1)

{
  longlong *plVar1;
  uint uVar2;
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
  uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
  return uVar2 >> 4 & 1;
}


// ==== FUN_140057f50 @ 140057f50  undefined8 FUN_140057f50(longlong param_1)

undefined8 FUN_140057f50(longlong param_1)

{
  longlong *plVar1;
  ulonglong uVar2;
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
  uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x24);
  if ((int)uVar2 != 0) {
    plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
    uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x24);
    if ((int)uVar2 != 0x3fc) {
      return CONCAT71((int7)(uVar2 >> 8),1);
    }
  }
  return uVar2 & 0xffffffffffffff00;
}


// ==== FUN_140057fb0 @ 140057fb0  uint FUN_140057fb0(longlong param_1)

uint FUN_140057fb0(longlong param_1)

{
  longlong *plVar1;
  uint uVar2;
  
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
  uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
  return ~(uVar2 >> 6) & 1;
}


// ==== FUN_1400580e0 @ 1400580e0  undefined FUN_1400580e0(longlong param_1, int param_2, int param_3, undefined4 param_4)

void FUN_1400580e0(longlong param_1,int param_2,int param_3,undefined4 param_4)

{
  longlong lVar1;
  longlong *plVar2;
  int iVar3;
  undefined1 auStack_e8 [32];
  int *local_c8;
  undefined4 local_c0;
  undefined4 local_b8;
  undefined4 local_b4;
  int local_b0;
  int local_ac;
  undefined1 local_a8 [8];
  undefined8 local_a0;
  uint local_98;
  undefined1 local_94 [76];
  ulonglong local_48;
  
  local_48 = DAT_140103510 ^ (ulonglong)auStack_e8;
  if (*(longlong *)(param_1 + 0x98) == 0) {
    local_c8 = (int *)CONCAT44(local_c8._4_4_,0x533);
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  else {
    *(undefined4 *)(param_1 + 0x2c) = 0;
    iVar3 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x38))();
    if ((param_2 != iVar3) ||
       (iVar3 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x40))(param_1 + 0x10),
       param_3 != iVar3)) {
      local_b8 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x38))(param_1 + 0x10);
      local_b4 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x40))(param_1 + 0x10);
      lVar1 = *(longlong *)(param_1 + 0x98);
      local_b0 = param_2;
      local_ac = param_3;
      if (*(longlong *)(lVar1 + 0x10) == 0) {
        local_c8 = (int *)CONCAT44(local_c8._4_4_,0x2c);
        log_InlineLogERROR(&DAT_1400be0b0);
      }
      plVar2 = *(longlong **)(lVar1 + 0x10);
      local_c8 = &local_b0;
      local_c0 = param_4;
      (**(code **)(*plVar2 + 0x58))(plVar2,local_a8,0x58,&local_b8);
      *(undefined8 *)(param_1 + 0x90) = local_a0;
      memcpy((void *)(param_1 + 0x40),local_94,(ulonglong)local_98);
      *(uint *)(param_1 + 0x2c) = local_98;
    }
  }
  __security_check_cookie(local_48 ^ (ulonglong)auStack_e8);
  return;
}


// ==== FUN_140058260 @ 140058260  undefined8 FUN_140058260(longlong param_1, int param_2)

ulonglong FUN_140058260(longlong param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  ulonglong extraout_RAX;
  longlong lVar7;
  longlong *plVar8;
  ulonglong uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint local_res8;
  int local_res20;
  int local_res24;
  
  if (*(longlong *)(param_1 + 0x98) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return extraout_RAX & 0xffffffffffffff00;
  }
  *(undefined4 *)(param_1 + 0x2c) = 0;
  (**(code **)(**(longlong **)(param_1 + 0x100) + 0x28))
            (*(longlong **)(param_1 + 0x100),&local_res20);
  iVar1 = *(int *)(param_1 + 0x84);
  if (iVar1 != 0) {
    lVar7 = FUN_14001c210();
    plVar8 = (longlong *)FUN_140038010(lVar7,iVar1);
    if (plVar8 != (longlong *)0x0) {
      local_res20 = (**(code **)(*plVar8 + 0x38))(plVar8);
      local_res24 = (**(code **)(*plVar8 + 0x40))(plVar8);
    }
  }
  local_res8 = (**(code **)(*(longlong *)(param_1 + 0x10) + 8))
                         (param_1 + 0x10,local_res20,local_res24);
  uVar13 = 0xffffffff;
  iVar1 = tq::RandGet(8);
  uVar2 = iVar1 + 8;
  uVar9 = (ulonglong)uVar2;
  if (iVar1 < (int)uVar2) {
    do {
      uVar10 = iVar1 >> 0x1f & 7;
      uVar10 = (iVar1 + uVar10 & 7) - uVar10;
      uVar9 = (ulonglong)uVar10;
      if (uVar10 != param_2) {
        lVar7 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x80))(param_1 + 0x10);
        if (lVar7 == 0) {
          uVar9 = 0;
        }
        else {
          uVar3 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x48))(param_1 + 0x10);
          iVar4 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x40))(param_1 + 0x10);
          iVar5 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x38))(param_1 + 0x10);
          lVar7 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x80))(param_1 + 0x10);
          uVar9 = FUN_14004bff0(lVar7,iVar5,iVar4,uVar10,uVar3,0x1a);
          if ((char)uVar9 != '\0') {
            iVar5 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x38))(param_1 + 0x10);
            iVar4 = *(int *)(&DAT_1400c89d0 + (longlong)(int)uVar10 * 4);
            iVar6 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x40))(param_1 + 0x10);
            uVar3 = (iVar5 + iVar4) - local_res20;
            uVar11 = (int)uVar3 >> 0x1f;
            uVar12 = (iVar6 + *(int *)(&DAT_1400c89f0 + (longlong)(int)uVar10 * 4)) - local_res24;
            uVar11 = (uVar3 ^ uVar11) - uVar11;
            uVar3 = (int)uVar12 >> 0x1f;
            uVar3 = (uVar12 ^ uVar3) - uVar3;
            if ((int)uVar3 < (int)uVar11) {
              uVar3 = uVar11;
            }
            uVar9 = (ulonglong)uVar3;
            iVar4 = -1;
            if (*(char *)(param_1 + 0x3c) != '\0') {
              iVar4 = 1;
            }
            if (0 < (int)(iVar4 * (local_res8 - uVar3))) {
              uVar13 = uVar10;
              local_res8 = uVar3;
            }
          }
        }
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < (int)uVar2);
    if (uVar13 != 0xffffffff) {
      *(char *)(param_1 + 0x40) = (char)uVar13;
      *(undefined4 *)(param_1 + 0x2c) = 1;
      return CONCAT71((int7)(uVar9 >> 8),1);
    }
  }
  return uVar9 & 0xffffffffffffff00;
}


// ==== FUN_140058500 @ 140058500  undefined8 FUN_140058500(longlong param_1, uint param_2)

ulonglong FUN_140058500(longlong param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  ulonglong uVar4;
  ulonglong extraout_RAX;
  
  if ((param_2 < 8) && (*(longlong *)(param_1 + 0x98) != 0)) {
    uVar1 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x48))(param_1 + 0x10);
    iVar2 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x40))(param_1 + 0x10);
    iVar3 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x38))(param_1 + 0x10);
    uVar4 = FUN_14004bff0(*(longlong *)(param_1 + 0x98),iVar3,iVar2,param_2,uVar1,0x1a);
    if ((char)uVar4 != '\0') {
      *(char *)(param_1 + 0x40) = (char)param_2;
      *(undefined4 *)(param_1 + 0x2c) = 1;
      return CONCAT71((int7)(uVar4 >> 8),1);
    }
  }
  else {
    log_InlineLogERROR(&DAT_1400be0b0);
    uVar4 = extraout_RAX;
  }
  return uVar4 & 0xffffffffffffff00;
}


// ==== FUN_140058610 @ 140058610  undefined FUN_140058610(longlong param_1, int param_2, int param_3)

void FUN_140058610(longlong param_1,int param_2,int param_3)

{
  if (*(longlong *)(param_1 + 0x98) != 0) {
    FUN_14004e140(*(longlong *)(param_1 + 0x98),(longlong *)(param_1 + 0x10),param_2,param_3);
    *(int *)(param_1 + 0x34) = param_2;
    *(int *)(param_1 + 0x38) = param_3;
    return;
  }
  *(int *)(param_1 + 0x34) = param_2;
  *(int *)(param_1 + 0x38) = param_3;
  return;
}


// ==== FUN_140058670 @ 140058670  undefined FUN_140058670(longlong * param_1, longlong param_2)

void FUN_140058670(longlong *param_1,longlong param_2)

{
  undefined4 uVar1;
  longlong lVar2;
  
  uVar1 = (**(code **)(*param_1 + 8))();
  lVar2 = FUN_14001c200();
  FUN_14001c5f0(lVar2,uVar1,param_2);
  return;
}


// ==== FUN_1400586b0 @ 1400586b0  undefined FUN_1400586b0(longlong * param_1, char * param_2, char * param_3)

void FUN_1400586b0(longlong *param_1,char *param_2,char *param_3)

{
  bool bVar1;
  undefined4 uVar2;
  char *pcVar3;
  undefined7 extraout_var;
  longlong lVar4;
  char *pcVar5;
  undefined1 auStackY_4c8 [32];
  undefined8 local_468 [136];
  ulonglong local_28;
  
  local_28 = DAT_140103510 ^ (ulonglong)auStackY_4c8;
  if (param_2 == (char *)0x0) {
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  else {
    pcVar5 = "ALLUSERS";
    if (param_3 != (char *)0x0) {
      pcVar5 = param_3;
    }
    FUN_140064d20(local_468);
    pcVar3 = (char *)(**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x18))();
    bVar1 = FUN_140064de0((longlong)local_468,pcVar3,pcVar5,param_2,(char *)0x0,0xffffff,0x7d1,0,0,1
                         );
    if ((int)CONCAT71(extraout_var,bVar1) == 0) {
      FUN_140064da0(local_468);
    }
    else {
      uVar2 = (**(code **)(*param_1 + 8))(param_1);
      lVar4 = FUN_14001c200();
      FUN_14001c5f0(lVar4,uVar2,(longlong)local_468);
      FUN_140064da0(local_468);
    }
  }
  __security_check_cookie(local_28 ^ (ulonglong)auStackY_4c8);
  return;
}


// ==== FUN_1400587e0 @ 1400587e0  undefined1 FUN_1400587e0(char * param_1)

undefined1 FUN_1400587e0(char *param_1)

{
  char *pcVar1;
  
  pcVar1 = strstr(param_1,"[GM]");
  if (pcVar1 == (char *)0x0) {
    pcVar1 = strstr(param_1,"[PM]");
    if (pcVar1 == (char *)0x0) {
      return (char)pcVar1;
    }
  }
  return 1;
}


// ==== FUN_140058830 @ 140058830  undefined1 FUN_140058830(longlong param_1)

undefined1 FUN_140058830(longlong param_1)

{
  bool bVar1;
  
  if (*(longlong *)(param_1 + 0x140) != 0) {
    bVar1 = FUN_140069750(*(longlong *)(param_1 + 0x140));
    if (bVar1) {
      return 1;
    }
  }
  return 0;
}


// ==== FUN_140058860 @ 140058860  undefined1 FUN_140058860(longlong param_1)

undefined1 FUN_140058860(longlong param_1)

{
  bool bVar1;
  
  if (*(longlong *)(param_1 + 0x140) != 0) {
    bVar1 = FUN_140069750(*(longlong *)(param_1 + 0x140));
    if (bVar1) {
      bVar1 = FUN_140069910(*(longlong *)(param_1 + 0x140));
      if (!bVar1) {
        bVar1 = FUN_140069740(*(longlong *)(param_1 + 0x140));
        if (!bVar1) {
          return 1;
        }
      }
    }
  }
  return 0;
}


// ==== FUN_1400588b0 @ 1400588b0  undefined8 FUN_1400588b0(longlong param_1, uint param_2, ulonglong param_3, int param_4)

ulonglong FUN_1400588b0(longlong param_1,uint param_2,ulonglong param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  ulonglong extraout_RAX;
  longlong lVar7;
  longlong *plVar8;
  ulonglong uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint local_res8;
  uint local_resc;
  uint local_48;
  int local_44;
  
  local_res8 = (uint)param_3;
  if (*(longlong *)(param_1 + 0x98) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return extraout_RAX & 0xffffffffffffff00;
  }
  iVar1 = *(int *)(param_1 + 0x84);
  *(undefined4 *)(param_1 + 0x2c) = 0;
  local_48 = param_2;
  if (iVar1 != 0) {
    lVar7 = FUN_14001c210();
    plVar8 = (longlong *)FUN_140038010(lVar7,iVar1);
    if (plVar8 == (longlong *)0x0) {
      param_3 = (ulonglong)local_resc;
      local_res8 = local_resc;
      local_48 = local_resc;
    }
    else {
      local_48 = (**(code **)(*plVar8 + 0x38))(plVar8);
      local_res8 = (**(code **)(*plVar8 + 0x40))(plVar8);
      param_3 = (ulonglong)local_res8;
    }
  }
  local_44 = (**(code **)(*(longlong *)(param_1 + 0x10) + 8))(param_1 + 0x10,local_48,param_3);
  uVar13 = 0xffffffff;
  iVar1 = tq::RandGet(8);
  uVar2 = iVar1 + 8;
  uVar9 = (ulonglong)uVar2;
  if (iVar1 < (int)uVar2) {
    do {
      uVar10 = iVar1 >> 0x1f & 7;
      uVar10 = (iVar1 + uVar10 & 7) - uVar10;
      uVar9 = (ulonglong)uVar10;
      if (uVar10 != param_4) {
        lVar7 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x80))(param_1 + 0x10);
        if (lVar7 == 0) {
          uVar9 = 0;
        }
        else {
          uVar3 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x48))(param_1 + 0x10);
          iVar4 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x40))(param_1 + 0x10);
          iVar5 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x38))(param_1 + 0x10);
          lVar7 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x80))(param_1 + 0x10);
          uVar9 = FUN_14004bff0(lVar7,iVar5,iVar4,uVar10,uVar3,0x1a);
          if ((char)uVar9 != '\0') {
            iVar5 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x38))(param_1 + 0x10);
            iVar4 = *(int *)(&DAT_1400c89d0 + (longlong)(int)uVar10 * 4);
            iVar6 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x40))();
            uVar12 = (iVar5 + iVar4) - local_48;
            uVar3 = (iVar6 + *(int *)(&DAT_1400c89f0 + (longlong)(int)uVar10 * 4)) - local_res8;
            uVar11 = (int)uVar3 >> 0x1f;
            iVar4 = (uVar3 ^ uVar11) - uVar11;
            uVar3 = (int)uVar12 >> 0x1f;
            iVar5 = (uVar12 ^ uVar3) - uVar3;
            if (iVar4 < iVar5) {
              iVar4 = iVar5;
            }
            iVar5 = -1;
            if (*(char *)(param_1 + 0x3c) != '\0') {
              iVar5 = 1;
            }
            uVar9 = (ulonglong)(uint)(local_44 - iVar4);
            if (0 < iVar5 * (local_44 - iVar4)) {
              uVar13 = uVar10;
              local_44 = iVar4;
            }
          }
        }
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < (int)uVar2);
    if (uVar13 != 0xffffffff) {
      *(char *)(param_1 + 0x40) = (char)uVar13;
      *(undefined4 *)(param_1 + 0x2c) = 1;
      return CONCAT71((int7)(uVar9 >> 8),1);
    }
  }
  return uVar9 & 0xffffffffffffff00;
}


// ==== FUN_140058b50 @ 140058b50  void * FUN_140058b50(void * param_1, uint param_2)

void * FUN_140058b50(void *param_1,uint param_2)

{
  FUN_140069610();
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_140058b80 @ 140058b80  undefined8 FUN_140058b80(longlong param_1, undefined8 * param_2)

ulonglong FUN_140058b80(longlong param_1,undefined8 *param_2)

{
  bool bVar1;
  ulonglong extraout_RAX;
  longlong lVar2;
  longlong *plVar3;
  ulonglong extraout_RAX_00;
  longlong lVar4;
  undefined8 *puVar5;
  undefined8 local_res8;
  
  if (*(longlong *)(param_1 + 0x140) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return extraout_RAX & 0xffffffffffffff00;
  }
  FUN_1400696d0(*(longlong *)(param_1 + 0x140));
  lVar2 = FUN_14001c200();
  plVar3 = (longlong *)FUN_14001c130(lVar2);
  lVar2 = FUN_140034e00(plVar3);
  if (lVar2 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return extraout_RAX_00 & 0xffffffffffffff00;
  }
  bVar1 = FUN_140069910(*(longlong *)(param_1 + 0x140));
  if (bVar1) {
    lVar4 = FUN_140065750(lVar2);
    if (lVar4 == 0) {
      puVar5 = (undefined8 *)
               (**(code **)(**(longlong **)(param_1 + 0x100) + 0x28))
                         (*(longlong **)(param_1 + 0x100),&local_res8);
    }
    else {
      puVar5 = FUN_1400657c0(lVar2,&local_res8);
    }
  }
  else {
    puVar5 = FUN_140065510(lVar2,&local_res8);
  }
  *param_2 = *puVar5;
  return CONCAT71((int7)((ulonglong)puVar5 >> 8),1);
}


// ==== FUN_140058ca0 @ 140058ca0  ulonglong FUN_140058ca0(longlong param_1, ulonglong param_2)

ulonglong FUN_140058ca0(longlong param_1,ulonglong param_2)

{
  int iVar1;
  int iVar2;
  ulonglong uVar3;
  uint uVar4;
  undefined4 local_res10;
  undefined4 uStackX_14;
  
  iVar1 = (**(code **)(*(longlong *)(param_1 + 0x10) + 8))(param_1 + 0x10,param_2,param_2 >> 0x20);
  iVar2 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x48))(param_1 + 0x10);
  uVar3 = (ulonglong)(uint)(iVar2 / 2);
  if (iVar2 / 2 < iVar1) {
    iVar1 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x38))(param_1 + 0x10);
    local_res10 = (int)param_2;
    iVar2 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x40))(param_1 + 0x10);
    uStackX_14 = (int)(param_2 >> 0x20);
    uVar4 = iVar1 - local_res10 >> 0x1f;
    uVar4 = (iVar1 - local_res10 ^ uVar4) - uVar4;
    uVar3 = (ulonglong)uVar4;
    if (((4 < (int)uVar4) ||
        (uVar4 = iVar2 - uStackX_14 >> 0x1f, uVar4 = (iVar2 - uStackX_14 ^ uVar4) - uVar4,
        uVar3 = (ulonglong)uVar4, 4 < (int)uVar4)) ||
       (*(int *)(param_1 + 0x138) = *(int *)(param_1 + 0x138) + 1, *(int *)(param_1 + 0x138) < 5)) {
      return uVar3 & 0xffffffffffffff00;
    }
  }
  *(undefined4 *)(param_1 + 0x138) = 0;
  return CONCAT71((int7)(uVar3 >> 8),1);
}


// ==== FUN_140058f60 @ 140058f60  undefined FUN_140058f60(longlong param_1)

void FUN_140058f60(longlong param_1)

{
  ulong uVar1;
  
  uVar1 = tq::TimeGet(0);
  *(ulong *)(param_1 + 4) = uVar1;
  return;
}


// ==== FUN_140058fb0 @ 140058fb0  undefined FUN_140058fb0(void)

void FUN_140058fb0(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [48];
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_70,"deque<T> too long");
  std::exception::exception((exception *)local_48);
  local_48[0] = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
  local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
}


// ==== FUN_140059060 @ 140059060  undefined FUN_140059060(ulonglong param_1)

void FUN_140059060(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 8)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 << 3);
  return;
}


// ==== FUN_1400590d0 @ 1400590d0  bool FUN_1400590d0(longlong param_1, int param_2)

bool FUN_1400590d0(longlong param_1,int param_2)

{
  ulong uVar1;
  
  uVar1 = tq::TimeGet(0);
  return (uint)(param_2 + *(int *)(param_1 + 4)) <= uVar1;
}


// ==== FUN_140059100 @ 140059100  undefined1 FUN_140059100(longlong * param_1)

undefined1 FUN_140059100(longlong *param_1)

{
  if ((*param_1 != 0) && (param_1[1] == 0)) {
    return 1;
  }
  return 0;
}


// ==== FUN_140059120 @ 140059120  undefined FUN_140059120(longlong * param_1)

void FUN_140059120(longlong *param_1)

{
  char cVar1;
  
  if (*param_1 != 0) {
    cVar1 = FUN_140059100(param_1);
    if (cVar1 != '\0') {
      log_InlineLogERROR(&DAT_1400be0b0);
      return;
    }
    *(longlong *)(param_1[1] + 0x10) = param_1[2];
    if (param_1[2] != 0) {
      *(longlong *)(param_1[2] + 8) = param_1[1];
    }
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  return;
}


// ==== FUN_140059220 @ 140059220  void * FUN_140059220(void * param_1, longlong param_2, void * param_3)

void * FUN_140059220(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_1400592c0 @ 1400592c0  undefined8 * FUN_1400592c0(undefined8 * param_1)

undefined8 * FUN_1400592c0(undefined8 *param_1)

{
  *param_1 = IRole::vftable;
  *param_1 = INpc::vftable;
  return param_1;
}


// ==== FUN_140059710 @ 140059710  undefined8 FUN_140059710(longlong param_1)

undefined8 FUN_140059710(longlong param_1)

{
  longlong *plVar1;
  uint uVar2;
  undefined4 extraout_var;
  ulonglong uVar3;
  
  uVar2 = FUN_140057c50(param_1);
  uVar3 = CONCAT44(extraout_var,uVar2);
  if ((char)uVar2 == '\0') {
    plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
    uVar3 = (**(code **)(*plVar1 + 0x10))(plVar1,0x24);
    if ((int)uVar3 != 0) {
      plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
      uVar3 = (**(code **)(*plVar1 + 0x10))(plVar1,0x24);
      if ((int)uVar3 != 0x3fc) goto LAB_140059761;
    }
    return CONCAT71((int7)(uVar3 >> 8),1);
  }
LAB_140059761:
  return uVar3 & 0xffffffffffffff00;
}


// ==== FUN_140059770 @ 140059770  ulonglong FUN_140059770(longlong param_1)

ulonglong FUN_140059770(longlong param_1)

{
  longlong *plVar1;
  uint uVar2;
  ulonglong in_RAX;
  
  if (*(int *)(param_1 + 0x28) != 2) {
    plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
    uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
    in_RAX = (ulonglong)(uVar2 >> 3);
    if ((uVar2 >> 3 & 1) == 0) {
      plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
      uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
      in_RAX = (ulonglong)(uVar2 >> 4);
      if ((uVar2 >> 4 & 1) == 0) {
        plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
        uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
        in_RAX = (ulonglong)(uVar2 >> 0xb);
        if ((uVar2 >> 0xb & 1) == 0) {
          return CONCAT71((uint7)(uint3)(uVar2 >> 0x13),1);
        }
      }
    }
  }
  return in_RAX & 0xffffffffffffff00;
}


// ==== FUN_1400597f0 @ 1400597f0  undefined FUN_1400597f0(longlong * param_1, int param_2, int param_3, undefined4 param_4)

void FUN_1400597f0(longlong *param_1,int param_2,int param_3,undefined4 param_4)

{
  bool bVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined7 extraout_var;
  longlong lVar6;
  undefined1 auStackY_4c8 [32];
  undefined8 local_468 [132];
  ulonglong local_48;
  
  local_48 = DAT_140103510 ^ (ulonglong)auStackY_4c8;
  lVar6 = param_1[0x13];
  if (lVar6 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  else {
    if (-1 < param_2) {
      iVar4 = FUN_140049480(lVar6);
      if ((param_2 < iVar4) && (-1 < param_3)) {
        iVar4 = FUN_140049430(lVar6);
        if (param_3 < iVar4) {
          *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
          FUN_140058610((longlong)param_1,param_2,param_3);
          *(undefined4 *)((longlong)param_1 + 0x24) = param_4;
          FUN_1400623e0(local_468);
          uVar2 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
          uVar3 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
          iVar4 = (**(code **)(*param_1 + 8))(param_1);
          bVar1 = FUN_140062530((longlong)local_468,iVar4,uVar3,uVar2,(short)param_4,0x89,
                                (short)param_2,(short)param_3,0);
          if ((int)CONCAT71(extraout_var,bVar1) != 0) {
            uVar5 = (**(code **)(*param_1 + 8))(param_1);
            lVar6 = FUN_14001c200();
            FUN_14001c5f0(lVar6,uVar5,(longlong)local_468);
          }
          FUN_140062430(local_468);
          goto LAB_14005996d;
        }
      }
    }
    log_InlineLogERROR(&DAT_1400be0b0);
  }
LAB_14005996d:
  __security_check_cookie(local_48 ^ (ulonglong)auStackY_4c8);
  return;
}


// ==== FUN_140059c90 @ 140059c90  undefined FUN_140059c90(longlong * param_1)

void FUN_140059c90(longlong *param_1)

{
  undefined2 uVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  longlong lVar6;
  undefined1 auStackY_488 [32];
  undefined8 local_438 [132];
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStackY_488;
  if (*(int *)((longlong)param_1 + 0x84) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  else {
    FUN_140064650(local_438);
    uVar1 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
    uVar2 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
    iVar3 = (**(code **)(*param_1 + 8))(param_1);
    uVar5 = FUN_140064700((longlong)local_438,2,iVar3,*(int *)((longlong)param_1 + 0x84),uVar2,uVar1
                          ,0);
    if ((int)uVar5 != 0) {
      uVar4 = (**(code **)(*param_1 + 8))(param_1);
      lVar6 = FUN_14001c200();
      FUN_14001c5f0(lVar6,uVar4,(longlong)local_438);
    }
    if ((int)param_1[0x11] != *(int *)((longlong)param_1 + 0x84)) {
      *(undefined1 *)((longlong)param_1 + 0x3d) = 1;
    }
    FUN_1400646a0(local_438);
  }
  __security_check_cookie(local_18 ^ (ulonglong)auStackY_488);
  return;
}


// ==== FUN_140059dc0 @ 140059dc0  undefined8 FUN_140059dc0(longlong param_1)

ulonglong FUN_140059dc0(longlong param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  ulonglong in_RAX;
  longlong lVar7;
  longlong *plVar8;
  longlong *plVar9;
  ulonglong uVar10;
  
  iVar4 = *(int *)(param_1 + 0x84);
  if (iVar4 == 0) {
    *(undefined4 *)(param_1 + 0x84) = 0;
    return in_RAX & 0xffffffffffffff00;
  }
  lVar7 = FUN_14001c210();
  plVar8 = (longlong *)FUN_140038010(lVar7,iVar4);
  plVar9 = plVar8;
  if (plVar8 != (longlong *)0x0) {
    plVar9 = (longlong *)(**(code **)(*plVar8 + 0x50))(plVar8);
    if ((char)plVar9 != '\0') {
      cVar1 = (**(code **)(*plVar8 + 0x78))(plVar8);
      if (cVar1 != '\0') {
        cVar1 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x78))(param_1 + 0x10);
        if (cVar1 == '\0') {
          plVar9 = (longlong *)FUN_140059710(param_1);
          if ((char)plVar9 != '\0') goto LAB_140059f28;
        }
      }
      plVar9 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
      iVar2 = (**(code **)(*plVar9 + 0x10))(plVar9,0x10);
      lVar7 = *(longlong *)(param_1 + 0x10);
      uVar3 = (**(code **)(*plVar8 + 0x48))(plVar8);
      iVar4 = (**(code **)(lVar7 + 0x10))(param_1 + 0x10,uVar3);
      lVar7 = *(longlong *)(param_1 + 0x10);
      if (iVar2 <= iVar4) {
        iVar4 = iVar2;
      }
      uVar3 = (**(code **)(*plVar8 + 0x40))(plVar8);
      uVar5 = (**(code **)(*plVar8 + 0x38))(plVar8);
      uVar10 = (**(code **)(lVar7 + 8))(param_1 + 0x10,uVar5,uVar3);
      iVar6 = (int)uVar10;
      if (iVar2 < iVar6) {
LAB_140059eda:
        if (iVar6 <= iVar4) {
          uVar10 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x10))(param_1 + 0x10,0);
          if (1 < (int)uVar10) goto LAB_140059ef3;
        }
        *(undefined4 *)(param_1 + 0x84) = 0;
        uVar10 = uVar10 & 0xffffffffffffff00;
      }
      else {
        uVar10 = (**(code **)(*plVar8 + 0x68))(plVar8);
        if ((char)uVar10 != '\0') goto LAB_140059eda;
LAB_140059ef3:
        uVar10 = CONCAT71((int7)(uVar10 >> 8),1);
      }
      return uVar10;
    }
  }
  *(undefined4 *)(param_1 + 0x84) = 0;
LAB_140059f28:
  return (ulonglong)plVar9 & 0xffffffffffffff00;
}


// ==== FUN_140059f40 @ 140059f40  undefined8 FUN_140059f40(longlong * param_1, int param_2, int param_3, undefined4 param_4)

ulonglong FUN_140059f40(longlong *param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  ulonglong extraout_RAX;
  undefined8 uVar6;
  ulonglong uVar7;
  undefined4 extraout_var;
  int iVar8;
  
  if (param_1[0x13] == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return extraout_RAX & 0xffffffffffffff00;
  }
  uVar6 = (**(code **)(param_1[2] + 8))(param_1 + 2);
  iVar1 = (int)uVar6;
  if (iVar1 < 1) {
    uVar7 = CONCAT71((int7)((ulonglong)uVar6 >> 8),1);
  }
  else {
    iVar8 = 1;
    if (1 < iVar1 + 1) {
      do {
        iVar2 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
        iVar3 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
        iVar3 = iVar3 + ((param_2 - iVar2) * iVar8) / iVar1;
        iVar2 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
        iVar4 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
        iVar4 = iVar4 + ((param_3 - iVar2) * iVar8) / iVar1;
        uVar5 = FUN_14004cc70(param_1[0x13],iVar3,iVar4);
        if ((char)uVar5 != '\0') {
          uVar6 = FUN_1400597f0(param_1,iVar3,iVar4,param_4);
          return CONCAT71((int7)((ulonglong)uVar6 >> 8),1);
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 < iVar1 + 1);
    }
    uVar5 = FUN_14004cc70(param_1[0x13],param_2,param_3);
    if ((char)uVar5 == '\0') {
      uVar7 = CONCAT44(extraout_var,uVar5) & 0xffffffffffffff00;
    }
    else {
      uVar6 = FUN_1400597f0(param_1,param_2,param_3,param_4);
      uVar7 = CONCAT71((int7)((ulonglong)uVar6 >> 8),1);
    }
  }
  return uVar7;
}


// ==== FUN_14005a0d0 @ 14005a0d0  undefined8 FUN_14005a0d0(longlong * param_1, int param_2, int param_3, undefined4 param_4)

ulonglong FUN_14005a0d0(longlong *param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  ulonglong extraout_RAX;
  undefined8 uVar5;
  undefined4 extraout_var;
  undefined4 extraout_var_00;
  int iVar7;
  ulonglong uVar6;
  
  if (param_1[0x13] == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return extraout_RAX & 0xffffffffffffff00;
  }
  uVar5 = (**(code **)(param_1[2] + 8))(param_1 + 2);
  iVar1 = (int)uVar5;
  if (0 < iVar1) {
    uVar2 = FUN_14004cc70(param_1[0x13],param_2,param_3);
    uVar6 = CONCAT44(extraout_var,uVar2);
    if ((char)uVar2 == '\0') {
      iVar7 = 1;
      if (1 < iVar1 + 1) {
        do {
          iVar3 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
          iVar3 = (iVar3 - param_2) * iVar7;
          iVar4 = iVar3 / iVar1 + param_2;
          iVar3 = (**(code **)(param_1[2] + 0x40))
                            (param_1 + 2,(longlong)iVar3 % (longlong)iVar1 & 0xffffffff);
          iVar3 = ((iVar3 - param_3) * iVar7) / iVar1 + param_3;
          uVar2 = FUN_14004cc70(param_1[0x13],iVar4,iVar3);
          uVar6 = CONCAT44(extraout_var_00,uVar2);
          if ((char)uVar2 != '\0') {
            uVar5 = FUN_1400597f0(param_1,iVar4,iVar3,param_4);
            return CONCAT71((int7)((ulonglong)uVar5 >> 8),1);
          }
          iVar7 = iVar7 + 1;
        } while (iVar7 < iVar1 + 1);
      }
      return uVar6 & 0xffffffffffffff00;
    }
    uVar5 = FUN_1400597f0(param_1,param_2,param_3,param_4);
  }
  return CONCAT71((int7)((ulonglong)uVar5 >> 8),1);
}


// ==== FUN_14005a330 @ 14005a330  undefined8 FUN_14005a330(longlong param_1)

undefined8 FUN_14005a330(longlong param_1)

{
  bool bVar1;
  
  if (*(longlong *)(param_1 + 0x140) != 0) {
    bVar1 = FUN_140069750(*(longlong *)(param_1 + 0x140));
    if (bVar1) {
      return *(undefined8 *)(param_1 + 0x140);
    }
  }
  return 0;
}


// ==== FUN_14005a370 @ 14005a370  int FUN_14005a370(longlong param_1, undefined4 param_2)

int FUN_14005a370(longlong param_1,undefined4 param_2)

{
  ulong uVar1;
  
  *(undefined4 *)(param_1 + 0x14c) = param_2;
  uVar1 = tq::TimeGet(0);
  *(uint *)(param_1 + 0x150) = uVar1 / 1000;
  return uVar1 * 0x10624dd3;
}


// ==== FUN_14005a3b0 @ 14005a3b0  undefined8 FUN_14005a3b0(longlong param_1)

ulonglong FUN_14005a3b0(longlong param_1)

{
  bool bVar1;
  int nDenominator;
  int nNumerator;
  uint uVar2;
  ulonglong extraout_RAX;
  ulonglong extraout_RAX_00;
  uint *puVar3;
  ulonglong extraout_RAX_01;
  longlong lVar4;
  longlong *plVar5;
  ulonglong extraout_RAX_02;
  ulonglong extraout_RAX_03;
  ulonglong uVar6;
  uint local_38;
  undefined4 local_34;
  int local_30;
  int local_2c;
  uint local_28;
  undefined4 local_24;
  uint local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  if (*(longlong *)(param_1 + 0xa0) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return extraout_RAX & 0xffffffffffffff00;
  }
  if (*(longlong *)(param_1 + 0x98) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return extraout_RAX_00 & 0xffffffffffffff00;
  }
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_38 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  if (*(longlong **)(param_1 + 0x100) == (longlong *)0x0) {
    return 0;
  }
  local_1c = (**(code **)(**(longlong **)(param_1 + 0x100) + 8))();
  local_28 = *(uint *)(param_1 + 0x80);
  if ((local_28 < 0x61a81) || (499999 < local_28)) {
    local_20 = 0;
  }
  else {
    puVar3 = (uint *)FUN_14001c7a0();
    local_20 = FUN_14002b270(puVar3);
  }
  local_24 = *(undefined4 *)(param_1 + 0x110);
  local_30 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x38))(param_1 + 0x10);
  local_2c = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x40))(param_1 + 0x10);
  local_34 = (**(code **)(**(longlong **)(param_1 + 0x98) + 8))();
  local_18 = CONCAT31(local_18._1_3_,*(undefined1 *)(param_1 + 0x108));
  bVar1 = FUN_140049310(*(longlong *)(param_1 + 0x98),local_30,local_2c);
  if (!bVar1) {
    log_InlineLogERROR("CNpc::Transform, wrong postion (%d, %d)");
    return extraout_RAX_01 & 0xffffffffffffff00;
  }
  lVar4 = FUN_14001c7a0();
  plVar5 = (longlong *)FUN_140025be0(lVar4);
  lVar4 = (**(code **)(*plVar5 + 0x30))(plVar5,local_24);
  if (lVar4 == 0) {
    log_InlineLogERROR("CNpc::Transform, wrong transform monster type: %d");
    uVar6 = extraout_RAX_02;
  }
  else {
    if (*(char *)(param_1 + 0x108) == '\x01') {
      local_38 = (**(code **)(**(longlong **)(lVar4 + 0x10) + 0x10))(*(longlong **)(lVar4 + 0x10),4)
      ;
    }
    else {
      if (*(char *)(param_1 + 0x108) != '\x02') {
        log_InlineLogERROR("CNpc::Transform, wrong monster transform flag:%u");
        uVar6 = extraout_RAX_03;
        goto LAB_14005a56f;
      }
      plVar5 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
      nDenominator = (**(code **)(*plVar5 + 0x10))(plVar5,4);
      nNumerator = (**(code **)(**(longlong **)(lVar4 + 0x10) + 0x10))
                             (*(longlong **)(lVar4 + 0x10),4);
      local_38 = MulDiv(*(int *)(param_1 + 0x1c),nNumerator,nDenominator);
    }
    uVar2 = (**(code **)(**(longlong **)(lVar4 + 0x10) + 0x10))(*(longlong **)(lVar4 + 0x10),4);
    if (uVar2 <= local_38) {
      local_38 = (**(code **)(**(longlong **)(lVar4 + 0x10) + 0x10))(*(longlong **)(lVar4 + 0x10),4)
      ;
    }
    uVar6 = (**(code **)(**(longlong **)(param_1 + 0x100) + 0x88))
                      (*(longlong **)(param_1 + 0x100),&local_38);
    if ((char)uVar6 != '\0') {
      *(undefined4 *)(param_1 + 0x118) = 0;
      *(undefined4 *)(param_1 + 0x114) = 0;
      *(undefined1 *)(param_1 + 0x108) = 0;
      return CONCAT71((int7)(uVar6 >> 8),1);
    }
  }
LAB_14005a56f:
  return uVar6 & 0xffffffffffffff00;
}


// ==== FUN_14005a660 @ 14005a660  undefined8 FUN_14005a660(longlong param_1)

ulonglong FUN_14005a660(longlong param_1)

{
  byte bVar1;
  longlong *plVar2;
  int iVar3;
  ulonglong extraout_RAX;
  ulonglong uVar4;
  ulonglong extraout_RAX_00;
  undefined4 extraout_var;
  
  if (*(longlong *)(param_1 + 0xa0) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return extraout_RAX & 0xffffffffffffff00;
  }
  uVar4 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x50))(param_1 + 0x10);
  if ((char)uVar4 != '\0') {
    bVar1 = *(byte *)(param_1 + 0x108);
    uVar4 = 0;
    if (((bVar1 != 0) && (bVar1 < 3)) && (*(int *)(param_1 + 0x110) != 0)) {
      if (((*(uint *)(param_1 + 0x10c) != 0) && (*(int *)(param_1 + 0x128) == 0)) &&
         (*(int *)(param_1 + 300) == 0)) {
        if (bVar1 == 1) {
          if (*(int *)(param_1 + 0x118) != 0) {
            uVar4 = FUN_140002480((int *)(param_1 + 0x114));
            if ((char)uVar4 != '\0') goto LAB_14005a75e;
          }
        }
        else {
          if (bVar1 != 2) {
            log_InlineLogERROR("CNpc::CheckTransform, wrong monster transform flag:%u");
            return extraout_RAX_00 & 0xffffffffffffff00;
          }
          if (*(uint *)(param_1 + 0x10c) < 0x3e9) {
            plVar2 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
            iVar3 = (**(code **)(*plVar2 + 0x10))(plVar2,4);
            iVar3 = MulDiv(iVar3,*(int *)(param_1 + 0x10c),1000);
            uVar4 = CONCAT44(extraout_var,iVar3);
            if (*(int *)(param_1 + 0x1c) <= iVar3) {
LAB_14005a75e:
              return CONCAT71((int7)(uVar4 >> 8),1);
            }
          }
        }
      }
    }
  }
  return uVar4 & 0xffffffffffffff00;
}


// ==== FUN_14005a7e0 @ 14005a7e0  undefined FUN_14005a7e0(longlong * param_1, longlong param_2)

void FUN_14005a7e0(longlong *param_1,longlong param_2)

{
  if ((*param_1 == 0) && (param_2 != 0)) {
    *param_1 = param_2;
    return;
  }
  log_InlineLogERROR(&DAT_1400be0b0);
  *param_1 = param_2;
  return;
}


// ==== FUN_14005a880 @ 14005a880  undefined FUN_14005a880(undefined8 param_1, ulonglong param_2)

void FUN_14005a880(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 8)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 8);
  return;
}


// ==== FUN_14005a8f0 @ 14005a8f0  ulonglong FUN_14005a8f0(longlong param_1, int param_2)

ulonglong FUN_14005a8f0(longlong param_1,int param_2)

{
  int iVar1;
  ulong uVar2;
  undefined4 extraout_var;
  undefined4 extraout_var_00;
  
  uVar2 = tq::TimeGet(0);
  iVar1 = *(int *)(param_1 + 4);
  if (uVar2 < (uint)(param_2 + iVar1)) {
    return CONCAT44(extraout_var,uVar2) & 0xffffffffffffff00;
  }
  uVar2 = tq::TimeGet(0);
  if ((uint)(iVar1 + param_2 * 2) <= uVar2) {
    uVar2 = tq::TimeGet(0);
    *(ulong *)(param_1 + 4) = uVar2;
    return CONCAT71((int7)(CONCAT44(extraout_var_00,uVar2) >> 8),1);
  }
  *(int *)(param_1 + 4) = iVar1 + param_2;
  return CONCAT71((uint7)(uint3)((uint)(iVar1 + param_2) >> 8),1);
}


// ==== FUN_14005a970 @ 14005a970  undefined FUN_14005a970(longlong * param_1)

void FUN_14005a970(longlong *param_1)

{
  longlong *plVar1;
  longlong *plVar2;
  int iVar3;
  
  if ((*param_1 == 0) || (param_1[1] != 0)) {
    FUN_140059120(param_1);
    return;
  }
  iVar3 = 0;
  plVar2 = (longlong *)param_1[2];
  do {
    if (plVar2 == (longlong *)0x0) goto LAB_14005aa47;
    plVar1 = (longlong *)plVar2[2];
    if (*plVar2 == 0) {
      log_InlineLogERROR(&DAT_1400be0b0);
    }
    iVar3 = iVar3 + 1;
    *plVar2 = 0;
    plVar2[1] = 0;
    plVar2[2] = 0;
    plVar2 = plVar1;
  } while (iVar3 < 0x65);
  log_InlineLogERROR(&DAT_1400be0b0);
LAB_14005aa47:
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  return;
}


// ==== FUN_14005ab20 @ 14005ab20  undefined8 FUN_14005ab20(longlong param_1)

undefined8 FUN_14005ab20(longlong param_1)

{
  longlong *plVar1;
  uint *puVar2;
  undefined1 local_58 [24];
  undefined1 local_40 [24];
  undefined1 local_28 [32];
  
  plVar1 = (longlong *)(param_1 + 0x10);
  puVar2 = (uint *)(**(code **)(*(longlong *)(param_1 + 0x10) + 0x20))(plVar1,local_58);
  if ((*puVar2 >> 0xe & 1) == 0) {
    puVar2 = (uint *)(**(code **)(*plVar1 + 0x20))(plVar1,local_40);
    if ((*puVar2 >> 0xf & 1) == 0) {
      puVar2 = (uint *)(**(code **)(*plVar1 + 0x20))(plVar1,local_28);
      if ((*puVar2 & 1) == 0) {
        return CONCAT71((int7)((ulonglong)puVar2 >> 8),1);
      }
    }
  }
  return (ulonglong)puVar2 & 0xffffffffffffff00;
}


// ==== FUN_14005ab80 @ 14005ab80  uint FUN_14005ab80(longlong param_1)

uint FUN_14005ab80(longlong param_1)

{
  uint *puVar1;
  undefined1 local_28 [40];
  
  puVar1 = (uint *)(**(code **)(*(longlong *)(param_1 + 0x10) + 0x20))(param_1 + 0x10,local_28);
  return *puVar1 >> 0xf & 0xffffff01;
}


// ==== FUN_14005aba0 @ 14005aba0  byte FUN_14005aba0(longlong param_1)

byte FUN_14005aba0(longlong param_1)

{
  byte *pbVar1;
  undefined1 local_28 [40];
  
  pbVar1 = (byte *)(**(code **)(*(longlong *)(param_1 + 0x10) + 0x20))(param_1 + 0x10,local_28);
  return *pbVar1 & 1;
}


// ==== FUN_14005abc0 @ 14005abc0  undefined FUN_14005abc0(longlong param_1, int param_2)

void FUN_14005abc0(longlong param_1,int param_2)

{
  longlong *plVar1;
  
  plVar1 = *(longlong **)(param_1 + 0xc0);
  if (plVar1 != (longlong *)0x0) {
    (**(code **)(*plVar1 + 0x10))(plVar1,(double)param_2);
  }
  return;
}


// ==== FUN_14005abf0 @ 14005abf0  undefined FUN_14005abf0(longlong param_1, int param_2)

void FUN_14005abf0(longlong param_1,int param_2)

{
  longlong *plVar1;
  
  plVar1 = *(longlong **)(param_1 + 0xc0);
  if (plVar1 != (longlong *)0x0) {
    (**(code **)(*plVar1 + 0x18))(plVar1,(double)param_2);
  }
  return;
}


// ==== FUN_14005ac20 @ 14005ac20  undefined8 FUN_14005ac20(longlong param_1)

undefined8 FUN_14005ac20(longlong param_1)

{
  longlong *plVar1;
  uint *puVar2;
  undefined1 local_38 [24];
  undefined1 local_20 [24];
  
  plVar1 = (longlong *)(param_1 + 0x10);
  puVar2 = (uint *)(**(code **)(*(longlong *)(param_1 + 0x10) + 0x20))(plVar1,local_38);
  if ((*puVar2 >> 5 & 1) == 0) {
    puVar2 = (uint *)(**(code **)(*plVar1 + 0x20))(plVar1,local_20);
    if ((*puVar2 >> 3 & 1) == 0) {
      return CONCAT71((int7)((ulonglong)puVar2 >> 8),1);
    }
  }
  return (ulonglong)puVar2 & 0xffffffffffffff00;
}


// ==== FUN_14005ad00 @ 14005ad00  ulonglong FUN_14005ad00(longlong param_1)

ulonglong FUN_14005ad00(longlong param_1)

{
  longlong *plVar1;
  byte bVar2;
  uint uVar3;
  uint *puVar4;
  undefined1 local_38 [24];
  undefined1 local_20 [24];
  
  puVar4 = (uint *)(**(code **)(*(longlong *)(param_1 + 0x10) + 0x20))(param_1 + 0x10,local_38);
  if ((*puVar4 >> 5 & 1) == 0) {
    puVar4 = (uint *)(**(code **)(*(longlong *)(param_1 + 0x10) + 0x20))(param_1 + 0x10,local_20);
    if ((*puVar4 >> 3 & 1) == 0) {
      plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
      uVar3 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
      bVar2 = ~(byte)(uVar3 >> 6);
      puVar4 = (uint *)(ulonglong)CONCAT31((uint3)(uVar3 >> 0xe),bVar2);
      if ((bVar2 & 1) == 0) {
        plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
        uVar3 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
        puVar4 = (uint *)(ulonglong)(uVar3 >> 5);
        if ((uVar3 >> 5 & 1) == 0) goto LAB_14005ad8a;
      }
      return CONCAT71((int7)((ulonglong)puVar4 >> 8),1);
    }
  }
LAB_14005ad8a:
  return (ulonglong)puVar4 & 0xffffffffffffff00;
}


// ==== FUN_14005ae30 @ 14005ae30  undefined8 FUN_14005ae30(longlong * param_1, int param_2)

undefined8 FUN_14005ae30(longlong *param_1,int param_2)

{
  undefined4 uVar1;
  undefined8 in_RAX;
  
  if (param_2 == 0) {
    uVar1 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                      (*(longlong **)(param_1[0x14] + 0x10),4);
    *(undefined4 *)((longlong)param_1 + 0x1c) = uVar1;
    in_RAX = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                       (*(longlong **)(param_1[0x14] + 0x10),5);
    *(int *)(param_1 + 4) = (int)in_RAX;
  }
  else if (param_2 == 8) {
    in_RAX = FUN_140059c90(param_1);
  }
  else if (param_2 == 7) {
    *(undefined4 *)(param_1 + 3) = 7;
    return CONCAT71((int7)((ulonglong)in_RAX >> 8),1);
  }
  *(int *)(param_1 + 3) = param_2;
  *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
  return CONCAT71((int7)((ulonglong)in_RAX >> 8),1);
}


// ==== FUN_14005aeb0 @ 14005aeb0  undefined FUN_14005aeb0(longlong param_1, int param_2)

void FUN_14005aeb0(longlong param_1,int param_2)

{
  int iVar1;
  
  iVar1 = param_2 + *(int *)(param_1 + 0xb8);
  if (iVar1 <= param_2) {
    param_2 = iVar1;
  }
  *(int *)(param_1 + 0xb8) = param_2;
  return;
}


// ==== FUN_14005aed0 @ 14005aed0  ulonglong FUN_14005aed0(longlong param_1, longlong * param_2)

ulonglong FUN_14005aed0(longlong param_1,longlong *param_2)

{
  char cVar1;
  ulonglong uVar2;
  undefined4 *puVar3;
  undefined1 local_28 [32];
  
  cVar1 = (**(code **)(*param_2 + 0x78))(param_2);
  if (cVar1 != '\0') {
    cVar1 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x78))(param_1 + 0x10);
    if (cVar1 == '\0') {
      uVar2 = FUN_140059710(param_1);
      if ((char)uVar2 != '\0') {
        return uVar2 & 0xffffffffffffff00;
      }
    }
  }
  puVar3 = (undefined4 *)(**(code **)(*param_2 + 0x20))(param_2,local_28);
  return (ulonglong)(byte)~(byte)((uint)*puVar3 >> 0x1d) & 0xffffffffffffff01;
}


// ==== FUN_14005af40 @ 14005af40  undefined FUN_14005af40(longlong * param_1, undefined4 param_2, undefined4 param_3)

void FUN_14005af40(longlong *param_1,undefined4 param_2,undefined4 param_3)

{
  bool bVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  longlong lVar4;
  undefined1 auStackY_4b8 [32];
  undefined8 local_468 [136];
  ulonglong local_28;
  
  local_28 = DAT_140103510 ^ (ulonglong)auStackY_4b8;
  FUN_140063b90(local_468);
  if (param_1[0x28] != 0) {
    bVar1 = FUN_140069750(param_1[0x28]);
    if (bVar1) {
      lVar4 = param_1[0x28];
      goto LAB_14005af99;
    }
  }
  lVar4 = 0;
LAB_14005af99:
  uVar2 = 0;
  if (lVar4 != 0) {
    uVar2 = FUN_140069920(lVar4);
  }
  uVar3 = FUN_140063c60((longlong)local_468,param_2,*(undefined4 *)((longlong)param_1 + 300),param_3
                        ,(int)param_1[0x10],(int)param_1[0x25],0,uVar2);
  if ((int)uVar3 != 0) {
    uVar2 = (**(code **)(*param_1 + 8))(param_1);
    lVar4 = FUN_14001c200();
    FUN_14001c5f0(lVar4,uVar2,(longlong)local_468);
  }
  FUN_140063c20(local_468);
  __security_check_cookie(local_28 ^ (ulonglong)auStackY_4b8);
  return;
}


// ==== FUN_14005b030 @ 14005b030  undefined8 FUN_14005b030(longlong param_1)

ulonglong FUN_14005b030(longlong param_1)

{
  bool bVar1;
  ulonglong in_RAX;
  undefined7 extraout_var;
  longlong *plVar2;
  longlong lVar3;
  ulonglong extraout_RAX;
  int local_res8;
  int local_resc;
  
  if (*(longlong *)(param_1 + 0x140) != 0) {
    bVar1 = FUN_140069750(*(longlong *)(param_1 + 0x140));
    in_RAX = CONCAT71(extraout_var,bVar1);
    if (bVar1) {
      FUN_1400696d0(*(longlong *)(param_1 + 0x140));
      plVar2 = (longlong *)FUN_14001c250();
      lVar3 = FUN_140034e00(plVar2);
      if (lVar3 == 0) {
        log_InlineLogERROR(&DAT_1400be0b0);
        in_RAX = extraout_RAX;
      }
      else {
        in_RAX = FUN_140058b80(param_1,(undefined8 *)&local_res8);
        if ((char)in_RAX != '\0') {
          if (*(int *)(param_1 + 0x2c) == 0) {
            in_RAX = FUN_1400580e0(param_1,local_res8,local_resc,0);
          }
          *(undefined4 *)(param_1 + 0x18) = 7;
          return CONCAT71((int7)(in_RAX >> 8),1);
        }
      }
    }
  }
  return in_RAX & 0xffffffffffffff00;
}


// ==== FUN_14005b0f0 @ 14005b0f0  undefined FUN_14005b0f0(longlong * param_1, int param_2)

void FUN_14005b0f0(longlong *param_1,int param_2)

{
  undefined8 uVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  ulonglong uVar6;
  longlong lVar7;
  undefined8 *puVar8;
  undefined1 auStackY_4b8 [32];
  int iStack_474;
  undefined1 local_468 [16];
  undefined8 local_458 [136];
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStackY_4b8;
  cVar2 = (**(code **)(param_1[2] + 0x50))(param_1 + 2);
  if (cVar2 != '\0') {
    uVar6 = FUN_14005ad00((longlong)param_1);
    if ((char)uVar6 != '\0') {
      if (param_1[0x28] == 0) {
        log_InlineLogERROR(&DAT_1400be0b0);
      }
      else if (param_2 == 0) {
        *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
        *(undefined4 *)(param_1 + 3) = 1;
      }
      else if (param_2 == 1) {
        puVar8 = (undefined8 *)
                 (**(code **)(*(longlong *)param_1[0x20] + 0x28))
                           ((longlong *)param_1[0x20],local_468);
        uVar1 = *puVar8;
        uVar3 = (**(code **)(param_1[2] + 0x18))(param_1 + 2);
        iStack_474 = (int)((ulonglong)uVar1 >> 0x20);
        FUN_14005a0d0(param_1,(int)uVar1,iStack_474,uVar3);
      }
      else if (param_2 == 2) {
        *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
        *(undefined4 *)(param_1 + 3) = 1;
      }
      else if (param_2 == 3) {
        FUN_140063b90(local_458);
        uVar3 = FUN_140069920(param_1[0x28]);
        uVar4 = FUN_1400696d0(param_1[0x28]);
        uVar5 = FUN_140069770(param_1[0x28]);
        FUN_140063c60((longlong)local_458,0xb,uVar5,0,(int)param_1[0x10],uVar4,0,uVar3);
        uVar3 = (**(code **)(*param_1 + 8))(param_1);
        lVar7 = FUN_14001c200();
        FUN_14001c5f0(lVar7,uVar3,(longlong)local_458);
        (**(code **)(param_1[2] + 0xf8))(param_1 + 2);
        FUN_140063c20(local_458);
      }
    }
  }
  __security_check_cookie(local_18 ^ (ulonglong)auStackY_4b8);
  return;
}


// ==== FUN_14005b2d0 @ 14005b2d0  undefined8 FUN_14005b2d0(longlong * param_1)

undefined8 FUN_14005b2d0(longlong *param_1)

{
  uint uVar1;
  bool bVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  ulonglong uVar6;
  undefined7 extraout_var;
  undefined4 extraout_var_00;
  int iVar7;
  
  uVar6 = FUN_140059770((longlong)param_1);
  if ((char)uVar6 != '\0') {
    if (param_1[0x28] != 0) {
      bVar2 = FUN_140069750(param_1[0x28]);
      uVar6 = CONCAT71(extraout_var,bVar2);
      if (bVar2) goto LAB_14005b3db;
    }
    uVar6 = FUN_14005ad00((longlong)param_1);
    if (((char)uVar6 != '\0') && (uVar6 = (**(code **)(param_1[2] + 0x50))(), (char)uVar6 != '\0'))
    {
      if ((int)param_1[3] != 0) {
        uVar1 = *(uint *)((longlong)param_1 + 0x34);
        uVar6 = (ulonglong)uVar1;
        if (uVar1 == *(uint *)((longlong)param_1 + 0x11c)) {
          *(int *)((longlong)param_1 + 0x124) = *(int *)((longlong)param_1 + 0x124) + 1;
          if (10 < *(int *)((longlong)param_1 + 0x124)) {
            iVar3 = tq::RandGet(8);
            iVar7 = iVar3 + -4 + *(int *)((longlong)param_1 + 0x34);
            iVar3 = tq::RandGet(8);
            iVar3 = iVar3 + -4 + (int)param_1[7];
            uVar4 = FUN_14004cc70(param_1[0x13],iVar7,iVar3);
            uVar6 = CONCAT44(extraout_var_00,uVar4);
            if ((char)uVar4 != '\0') {
              iVar5 = *(int *)((longlong)param_1 + 0x124) + -5;
              if (iVar5 < 0) {
                iVar5 = 0;
              }
              *(int *)((longlong)param_1 + 0x124) = iVar5;
              uVar6 = FUN_1400597f0(param_1,iVar7,iVar3,*(undefined4 *)((longlong)param_1 + 0x24));
            }
          }
          return CONCAT71((int7)(uVar6 >> 8),1);
        }
        *(uint *)((longlong)param_1 + 0x11c) = uVar1;
        uVar6 = (ulonglong)*(uint *)(param_1 + 7);
        *(uint *)(param_1 + 0x24) = *(uint *)(param_1 + 7);
      }
      *(undefined4 *)((longlong)param_1 + 0x124) = 0;
    }
  }
LAB_14005b3db:
  return uVar6 & 0xffffffffffffff00;
}


// ==== FUN_14005b440 @ 14005b440  void * FUN_14005b440(void * param_1, longlong param_2, void * param_3)

void * FUN_14005b440(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14005b4b0 @ 14005b4b0  undefined FUN_14005b4b0(undefined8 * param_1)

void FUN_14005b4b0(undefined8 *param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  *param_1 = CNpc::vftable;
  param_1[2] = CNpc::vftable;
  FUN_14005a970(param_1 + 0x1a);
  plVar3 = (longlong *)param_1[0x19];
  if (plVar3 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar3 + 2;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)*plVar1 == 0) {
      (**(code **)*plVar3)(plVar3);
      LOCK();
      piVar2 = (int *)((longlong)plVar3 + 0x14);
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (*piVar2 == 0) {
        (**(code **)(*plVar3 + 8))(plVar3);
      }
    }
  }
  param_1[2] = IRole::vftable;
  FUN_1400695e0(param_1);
  return;
}


// ==== FUN_14005b580 @ 14005b580  int FUN_14005b580(longlong param_1)

int FUN_14005b580(longlong param_1)

{
  ulong uVar1;
  
  uVar1 = tq::TimeGet(0);
  *(uint *)(param_1 + 0xb4) = uVar1 / 1000;
  if (*(int *)(param_1 + 0x18) == 0) {
    *(undefined4 *)(param_1 + 0x2c) = 0;
    *(undefined4 *)(param_1 + 0x18) = 1;
  }
  return uVar1 * 0x10624dd3;
}


// ==== FUN_14005b5c0 @ 14005b5c0  ulonglong FUN_14005b5c0(longlong param_1)

ulonglong FUN_14005b5c0(longlong param_1)

{
  longlong *plVar1;
  longlong lVar2;
  ulong uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  ulonglong uVar9;
  
  uVar3 = tq::TimeGet(0);
  if (uVar3 / 1000 < (uint)(*(int *)(param_1 + 0xb4) + *(int *)(param_1 + 0xb0))) {
    return (ulonglong)uVar3 * 0x10624dd3 & 0xffffff00;
  }
  uVar3 = tq::TimeGet(0);
  *(uint *)(param_1 + 0xb4) = uVar3 / 1000;
  plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
  uVar4 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
  if ((uVar4 >> 3 & 1) == 0) {
    plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
    uVar4 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
    if ((uVar4 >> 4 & 1) != 0) goto LAB_14005b673;
    plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
    uVar4 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15);
    uVar9 = (ulonglong)(uVar4 >> 7);
    if ((uVar4 >> 7 & 1) != 0) goto LAB_14005b673;
  }
  else {
LAB_14005b673:
    lVar2 = **(longlong **)(param_1 + 0x100);
    uVar5 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x40))(param_1 + 0x10);
    uVar6 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x38))(param_1 + 0x10);
    uVar9 = (**(code **)(lVar2 + 0x68))(*(undefined8 *)(param_1 + 0x100),uVar6,uVar5);
    if ((char)uVar9 == '\0') goto LAB_14005b739;
  }
  if (*(longlong *)(param_1 + 0x98) != 0) {
    iVar7 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x40))(param_1 + 0x10);
    iVar8 = (**(code **)(*(longlong *)(param_1 + 0x10) + 0x38))(param_1 + 0x10);
    uVar9 = FUN_14004ae30(*(longlong *)(param_1 + 0x98),iVar8,iVar7);
    if ((char)uVar9 != '\0') {
      plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
      uVar5 = (**(code **)(*plVar1 + 0x10))(plVar1,4);
      *(undefined4 *)(param_1 + 0x1c) = uVar5;
      plVar1 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
      uVar5 = (**(code **)(*plVar1 + 0x10))(plVar1,5);
      *(undefined4 *)(param_1 + 0x20) = uVar5;
      *(undefined4 *)(param_1 + 0x2c) = 0;
      *(undefined4 *)(param_1 + 0x18) = 0;
      return 1;
    }
  }
LAB_14005b739:
  return uVar9 & 0xffffffffffffff00;
}


// ==== FUN_14005b760 @ 14005b760  bool FUN_14005b760(longlong * param_1, int param_2)

bool FUN_14005b760(longlong *param_1,int param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  longlong lVar6;
  longlong *plVar7;
  undefined8 uVar8;
  uint uVar9;
  int iVar10;
  
  if (param_1[0x13] == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return false;
  }
  *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
  *(bool *)((longlong)param_1 + 0x3c) = param_2 == 0;
  lVar6 = FUN_14001c210();
  plVar7 = (longlong *)FUN_140038010(lVar6,*(int *)((longlong)param_1 + 0x84));
  if ((plVar7 != (longlong *)0x0) && (cVar1 = (**(code **)(*plVar7 + 0x50))(plVar7), cVar1 != '\0'))
  {
    iVar2 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                      (*(longlong **)(param_1[0x14] + 0x10),0x10);
    lVar6 = param_1[2];
    uVar3 = (**(code **)(*plVar7 + 0x40))(plVar7);
    uVar4 = (**(code **)(*plVar7 + 0x38))(plVar7);
    iVar5 = (**(code **)(lVar6 + 8))(param_1 + 2,uVar4,uVar3);
    if (iVar5 <= iVar2) {
      iVar2 = (**(code **)(*plVar7 + 0x40))(plVar7);
      iVar5 = (**(code **)(*plVar7 + 0x38))(plVar7);
      cVar1 = FUN_1400580e0((longlong)param_1,iVar5,iVar2,param_2);
      if (cVar1 == '\0') {
        return false;
      }
      if (*(int *)((longlong)param_1 + 0x2c) < 1) {
LAB_14005b998:
        return *(int *)((longlong)param_1 + 0x2c) != 0;
      }
      uVar9 = (int)(char)param_1[8] >> 0x1f & 7;
      iVar10 = (uVar9 + (int)(char)param_1[8] & 7) - uVar9;
      uVar9 = (**(code **)(param_1[2] + 0x48))(param_1 + 2);
      iVar2 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
      iVar5 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
      uVar8 = FUN_14004bff0(param_1[0x13],iVar5,iVar2,iVar10,uVar9,0);
      if ((char)uVar8 == '\0') {
        FUN_140058260((longlong)param_1,iVar10);
        if (*(int *)((longlong)param_1 + 0x2c) == 0) {
          FUN_14005b2d0(param_1);
          return false;
        }
        return true;
      }
      if (*(char *)((longlong)param_1 + 0x3c) != '\0') {
        lVar6 = *plVar7;
        uVar3 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
        uVar4 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
        iVar2 = (**(code **)(lVar6 + 8))(plVar7,uVar4,uVar3);
        iVar5 = (**(code **)(*plVar7 + 8))
                          (plVar7,(int)param_1[0x12],*(undefined4 *)((longlong)param_1 + 0x94));
        if (iVar2 <= iVar5) goto LAB_14005b9a8;
      }
      if (*(char *)((longlong)param_1 + 0x3c) != '\0') goto LAB_14005b998;
      lVar6 = *plVar7;
      uVar3 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
      uVar4 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
      iVar2 = (**(code **)(lVar6 + 8))(plVar7,uVar4,uVar3);
      iVar5 = (**(code **)(*plVar7 + 8))
                        (plVar7,(int)param_1[0x12],*(undefined4 *)((longlong)param_1 + 0x94));
      if (iVar2 < iVar5) goto LAB_14005b998;
      goto LAB_14005b9a8;
    }
  }
  *(undefined4 *)((longlong)param_1 + 0x84) = 0;
LAB_14005b9a8:
  *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
  return false;
}


// ==== FUN_14005b9e0 @ 14005b9e0  undefined FUN_14005b9e0(longlong * param_1, int param_2, undefined4 param_3)

void FUN_14005b9e0(longlong *param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  undefined8 uVar10;
  longlong lVar11;
  uint uVar12;
  undefined1 auStackY_4f8 [32];
  undefined8 local_4b8 [142];
  ulonglong local_48;
  
  local_48 = DAT_140103510 ^ (ulonglong)auStackY_4f8;
  if (param_1[0x13] == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    goto LAB_14005bc4b;
  }
  uVar12 = param_2 >> 0x1f & 7;
  iVar3 = (param_2 + uVar12 & 7) - uVar12;
  *(int *)((longlong)param_1 + 0x24) = iVar3;
  iVar1 = *(int *)(&DAT_1400c89d0 + (longlong)iVar3 * 4);
  iVar3 = *(int *)(&DAT_1400c89f0 + (longlong)iVar3 * 4);
  iVar4 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
  iVar4 = iVar1 + iVar4;
  iVar5 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
  iVar5 = iVar3 + iVar5;
  lVar11 = param_1[0x13];
  if (-1 < iVar4) {
    iVar6 = FUN_140049480(lVar11);
    if ((iVar4 < iVar6) && (-1 < iVar5)) {
      iVar6 = FUN_140049430(lVar11);
      if (iVar5 < iVar6) {
        uVar12 = (**(code **)(param_1[2] + 0x48))(param_1 + 2);
        iVar6 = (**(code **)(param_1[2] + 0x18))(param_1 + 2);
        iVar7 = (**(code **)(param_1[2] + 0x40))();
        iVar8 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
        uVar10 = FUN_14004bff0(param_1[0x13],iVar8,iVar7,iVar6,uVar12,0);
        if ((char)uVar10 == '\0') {
          if (param_1[0x28] != 0) {
            bVar2 = FUN_140069750(param_1[0x28]);
            if (bVar2) {
              bVar2 = FUN_140049310(param_1[0x13],iVar4,iVar5);
              if (bVar2) goto LAB_14005bb72;
            }
          }
          FUN_14005b2d0(param_1);
        }
        else {
LAB_14005bb72:
          FUN_140062030(local_4b8);
          iVar4 = (**(code **)(*param_1 + 8))(param_1);
          uVar10 = FUN_1400620c0((longlong)local_4b8,iVar4,param_2,param_3);
          if ((int)uVar10 == 0) {
            log_InlineLogERROR(&DAT_1400be0b0);
            FUN_140062080(local_4b8);
          }
          else {
            uVar9 = (**(code **)(*param_1 + 8))(param_1);
            lVar11 = FUN_14001c200();
            FUN_14001c5f0(lVar11,uVar9,(longlong)local_4b8);
            FUN_140058610((longlong)param_1,iVar1 + *(int *)((longlong)param_1 + 0x34),
                          iVar3 + (int)param_1[7]);
            FUN_140062080(local_4b8);
          }
        }
        goto LAB_14005bc4b;
      }
    }
  }
  log_InlineLogERROR(&DAT_1400be0b0);
LAB_14005bc4b:
  __security_check_cookie(local_48 ^ (ulonglong)auStackY_4f8);
  return;
}


// ==== FUN_14005bc80 @ 14005bc80  undefined FUN_14005bc80(longlong * param_1)

void FUN_14005bc80(longlong *param_1)

{
  longlong *plVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined8 uVar10;
  ulonglong uVar11;
  longlong lVar12;
  longlong *plVar13;
  longlong *plVar14;
  byte *pbVar15;
  uint *puVar16;
  ulonglong uVar17;
  IStringManager *pIVar18;
  char *pcVar19;
  undefined1 auStack_4a8 [32];
  undefined4 local_488;
  int local_478;
  int local_474;
  int local_470;
  int local_46c;
  int local_468;
  longlong *local_460;
  longlong local_458;
  undefined1 local_450 [24];
  char local_438 [1024];
  ulonglong local_38;
  
  local_38 = DAT_140103510 ^ (ulonglong)auStack_4a8;
  if (param_1[0x13] == 0) {
    local_488 = 0x66a;
    log_InlineLogERROR(&DAT_1400be0b0);
    goto LAB_14005c5c4;
  }
  uVar3 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                    (*(longlong **)(param_1[0x14] + 0x10),0x15);
  if (((uVar3 >> 8 & 1) != 0) ||
     (uVar3 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                        (*(longlong **)(param_1[0x14] + 0x10),0x15), (uVar3 >> 9 & 1) != 0)) {
    uVar10 = FUN_140059dc0((longlong)param_1);
    if ((char)uVar10 == '\0') {
      uVar3 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                        (*(longlong **)(param_1[0x14] + 0x10),0x15);
      uVar3 = uVar3 >> 8;
    }
    else {
      uVar3 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                        (*(longlong **)(param_1[0x14] + 0x10),0x15);
      uVar3 = uVar3 >> 9;
    }
    if ((uVar3 & 1) != 0) goto LAB_14005c5c4;
  }
  iVar4 = *(int *)((longlong)param_1 + 0x84);
  *(undefined4 *)((longlong)param_1 + 0x84) = 0;
  local_460 = (longlong *)0x0;
  local_46c = iVar4;
  uVar11 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))();
  plVar14 = (longlong *)0x0;
  if ((uVar11 & 2) != 0) {
    lVar12 = FUN_14001c210();
    plVar13 = (longlong *)FUN_140038010(lVar12,*(int *)((longlong)param_1 + 0x84));
    if ((plVar13 == (longlong *)0x0) ||
       (cVar2 = (**(code **)(*plVar13 + 0x50))(plVar13), cVar2 == '\0')) {
LAB_14005be4b:
      *(undefined4 *)((longlong)param_1 + 0x84) = 0;
    }
    else {
      iVar4 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                        (*(longlong **)(param_1[0x14] + 0x10),0x10);
      lVar12 = param_1[2];
      uVar5 = (**(code **)(*plVar13 + 0x40))(plVar13);
      uVar6 = (**(code **)(*plVar13 + 0x38))(plVar13);
      iVar7 = (**(code **)(lVar12 + 8))(param_1 + 2,uVar6,uVar5);
      if (iVar4 < iVar7) goto LAB_14005be4b;
    }
    iVar7 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                      (*(longlong **)(param_1[0x14] + 0x10),0x10);
    local_470 = iVar7;
    iVar4 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
    if (iVar4 / 0x12 + -1 < 1) {
      local_474 = 0;
    }
    else {
      iVar4 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
      local_474 = iVar4 / 0x12 + -1;
    }
    iVar9 = local_474;
    iVar8 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
    iVar4 = local_46c;
    if (iVar9 <= iVar8 / 0x12 + 1) {
      do {
        iVar8 = FUN_140049490(param_1[0x13]);
        plVar14 = local_460;
        iVar4 = local_46c;
        if (iVar8 <= iVar9) break;
        iVar4 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
        if (iVar4 / 0x12 + -1 < 1) {
          local_478 = 0;
        }
        else {
          iVar4 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
          local_478 = iVar4 / 0x12 + -1;
        }
        iVar4 = local_478;
        iVar8 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
        if (iVar4 <= iVar8 / 0x12 + 1) {
          do {
            uVar11 = 0;
            iVar8 = FUN_140049440(param_1[0x13]);
            if (iVar8 <= iVar4) break;
            lVar12 = FUN_14004ac70(param_1[0x13],iVar9,iVar4);
            plVar14 = (longlong *)FUN_1400678b0(lVar12);
            lVar12 = (**(code **)(*plVar14 + 0x10))(plVar14);
            if (lVar12 != 0) {
              do {
                plVar13 = (longlong *)
                          (**(code **)(*plVar14 + 0x18))
                                    (plVar14,uVar11,
                                     "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\npc.cpp"
                                     ,0x68f);
                if (((plVar13 != (longlong *)0x0) &&
                    (cVar2 = (**(code **)(plVar13[2] + 0x50))(plVar13 + 2), cVar2 != '\0')) &&
                   (((((uVar3 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                                          (*(longlong **)(param_1[0x14] + 0x10),0x15),
                       (uVar3 >> 3 & 1) != 0 &&
                       (pbVar15 = (byte *)(**(code **)(plVar13[2] + 0x20))(plVar13 + 2,local_450),
                       (*pbVar15 & 1) != 0)) ||
                      ((uVar3 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                                          (*(longlong **)(param_1[0x14] + 0x10),0x15),
                       (uVar3 >> 4 & 1) != 0 &&
                       (puVar16 = (uint *)(**(code **)(plVar13[2] + 0x20))(plVar13 + 2,local_450),
                       (*puVar16 >> 0xf & 1) != 0)))) ||
                     (((uVar3 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                                          (*(longlong **)(param_1[0x14] + 0x10),0x15),
                       (uVar3 >> 0xb & 1) != 0 &&
                       (uVar10 = FUN_14005ab20((longlong)plVar13), (char)uVar10 != '\0')) ||
                      (((cVar2 = (**(code **)(param_1[2] + 0x58))(param_1 + 2), cVar2 != '\0' &&
                        (uVar3 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                                           (*(longlong **)(param_1[0x14] + 0x10),0x15),
                        (uVar3 >> 4 & 1) == 0)) &&
                       (uVar3 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                                          (*(longlong **)(param_1[0x14] + 0x10),0x15),
                       (uVar3 >> 0xb & 1) == 0)))))) &&
                    ((((cVar2 = (**(code **)(plVar13[2] + 0x78))(plVar13 + 2), cVar2 == '\0' ||
                       (cVar2 = (**(code **)(param_1[2] + 0x78))(param_1 + 2), cVar2 != '\0')) ||
                      (uVar10 = FUN_140059710((longlong)param_1), (char)uVar10 == '\0')) &&
                     (puVar16 = (uint *)(**(code **)(plVar13[2] + 0x20))(plVar13 + 2,local_450),
                     (*puVar16 >> 0x1d & 1) == 0)))))) {
                  lVar12 = param_1[2];
                  uVar5 = (**(code **)(plVar13[2] + 0x48))(plVar13 + 2);
                  local_468 = (**(code **)(lVar12 + 0x10))(param_1 + 2,uVar5);
                  if (iVar7 <= local_468) {
                    local_468 = iVar7;
                  }
                  lVar12 = param_1[2];
                  uVar5 = (**(code **)(plVar13[2] + 0x40))(plVar13 + 2);
                  uVar6 = (**(code **)(plVar13[2] + 0x38))(plVar13 + 2);
                  iVar4 = (**(code **)(lVar12 + 8))(param_1 + 2,uVar6,uVar5);
                  iVar7 = local_470;
                  if (((iVar4 <= local_470) &&
                      (cVar2 = (**(code **)(plVar13[2] + 0x68))(plVar13 + 2), cVar2 == '\0')) ||
                     ((iVar4 <= local_468 &&
                      (iVar9 = (**(code **)(param_1[2] + 0x10))(param_1 + 2,0), 1 < iVar9)))) {
                    local_470 = iVar4;
                    uVar5 = (**(code **)(*plVar13 + 8))(plVar13);
                    *(undefined4 *)((longlong)param_1 + 0x84) = uVar5;
                    local_460 = plVar13;
                    iVar7 = iVar4;
                  }
                }
                uVar11 = uVar11 + 1;
                uVar17 = (**(code **)(*plVar14 + 0x10))(plVar14);
                iVar9 = local_474;
                iVar4 = local_478;
              } while (uVar11 < uVar17);
            }
            lVar12 = FUN_14004ac70(param_1[0x13],iVar9,iVar4);
            plVar14 = (longlong *)FUN_1400678a0(lVar12);
            uVar11 = 0;
            lVar12 = (**(code **)(*plVar14 + 0x10))(plVar14);
            if (lVar12 != 0) {
              do {
                plVar13 = (longlong *)
                          (**(code **)(*plVar14 + 0x18))
                                    (plVar14,uVar11,
                                     "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\npc.cpp"
                                     ,0x6b2);
                if (((plVar13 != (longlong *)0x0) &&
                    (cVar2 = (**(code **)(*plVar13 + 0x50))(plVar13), cVar2 != '\0')) &&
                   ((((cVar2 = (**(code **)(param_1[2] + 0x58))(param_1 + 2), cVar2 != '\0' &&
                      (cVar2 = (**(code **)(*plVar13 + 0x70))(plVar13), cVar2 != '\0')) ||
                     ((cVar2 = (**(code **)(param_1[2] + 0x70))(param_1 + 2), cVar2 != '\0' &&
                      (cVar2 = (**(code **)(*plVar13 + 0x58))(plVar13), cVar2 != '\0')))) &&
                    ((cVar2 = (**(code **)(*plVar13 + 0x78))(plVar13), cVar2 == '\0' ||
                     (((cVar2 = (**(code **)(param_1[2] + 0x78))(param_1 + 2), cVar2 != '\0' ||
                       (uVar3 = FUN_140057c50((longlong)param_1), (char)uVar3 != '\0')) ||
                      ((iVar4 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                                          (*(longlong **)(param_1[0x14] + 0x10),0x24), iVar4 != 0 &&
                       (iVar4 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                                          (*(longlong **)(param_1[0x14] + 0x10),0x24),
                       iVar4 != 0x3fc)))))))))) {
                  local_458 = 0;
                  (**(code **)(*plVar13 + 0xb0))(plVar13,0x1040,&local_458);
                  if ((local_458 == 0) ||
                     (plVar1 = *(longlong **)(*(longlong *)(local_458 + 0xa0) + 0x10),
                     uVar3 = (**(code **)(*plVar1 + 0x10))(plVar1,0x15), (uVar3 >> 3 & 1) == 0)) {
                    lVar12 = param_1[2];
                    uVar5 = (**(code **)(*plVar13 + 0x40))(plVar13);
                    uVar6 = (**(code **)(*plVar13 + 0x38))(plVar13);
                    iVar4 = (**(code **)(lVar12 + 8))(param_1 + 2,uVar6,uVar5);
                    iVar7 = local_470;
                    if (iVar4 <= local_470) {
                      local_470 = iVar4;
                      uVar5 = (**(code **)(*plVar13 + 0x28))(plVar13);
                      *(undefined4 *)((longlong)param_1 + 0x84) = uVar5;
                      iVar7 = iVar4;
                    }
                  }
                }
                uVar11 = uVar11 + 1;
                uVar17 = (**(code **)(*plVar14 + 0x10))(plVar14);
                iVar9 = local_474;
                iVar4 = local_478;
              } while (uVar11 < uVar17);
            }
            iVar4 = iVar4 + 1;
            local_478 = iVar4;
            iVar8 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
          } while (iVar4 <= iVar8 / 0x12 + 1);
        }
        iVar9 = iVar9 + 1;
        local_474 = iVar9;
        iVar8 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
        plVar14 = local_460;
        iVar4 = local_46c;
      } while (iVar9 <= iVar8 / 0x12 + 1);
    }
  }
  if (*(int *)((longlong)param_1 + 0x84) != 0) {
    if ((plVar14 != (longlong *)0x0) &&
       (iVar7 = (**(code **)(*plVar14 + 8))(plVar14), iVar4 != iVar7)) {
      uVar3 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                        (*(longlong **)(param_1[0x14] + 0x10),0x15);
      if (((uVar3 >> 3 & 1) == 0) ||
         (pbVar15 = (byte *)(**(code **)(plVar14[2] + 0x20))(plVar14 + 2,local_450),
         (*pbVar15 & 1) == 0)) {
        uVar3 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))();
        if ((((uVar3 >> 4 & 1) != 0) &&
            (puVar16 = (uint *)(**(code **)(plVar14[2] + 0x20))(plVar14 + 2),
            (*puVar16 >> 0xf & 1) != 0)) && ((int)param_1[3] == 1)) {
          pIVar18 = theInstance();
          pcVar19 = (char *)(*(code *)**(undefined8 **)pIVar18)(pIVar18,"STR_PPKER_CALL_s");
          sprintf(local_438,pcVar19);
          FUN_1400586b0(param_1,local_438,(char *)0x0);
        }
      }
      else {
        pIVar18 = theInstance();
        pcVar19 = (char *)(*(code *)**(undefined8 **)pIVar18)(pIVar18,"STR_GUARD_CALL_s");
        sprintf(local_438,pcVar19);
        FUN_1400586b0(param_1,local_438,(char *)0x0);
      }
    }
    FUN_14005b760(param_1,0);
  }
LAB_14005c5c4:
  __security_check_cookie(local_38 ^ (ulonglong)auStack_4a8);
  return;
}


// ==== FUN_14005c960 @ 14005c960  undefined8 FUN_14005c960(longlong * param_1, int param_2)

undefined8 FUN_14005c960(longlong *param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  ulonglong uVar5;
  uint7 uVar7;
  undefined8 uVar6;
  longlong *plVar8;
  uint uVar9;
  int iVar10;
  uint local_res18;
  uint local_res1c;
  longlong lVar4;
  
  if (param_2 == 0) {
    uVar3 = 0x13;
    plVar8 = *(longlong **)(param_1[0x14] + 0x10);
    lVar4 = *plVar8;
  }
  else {
    uVar3 = 0x1a;
    plVar8 = *(longlong **)(param_1[0x14] + 0x10);
    lVar4 = *plVar8;
  }
  iVar2 = (**(code **)(lVar4 + 0x10))(plVar8,uVar3);
  uVar5 = FUN_14005a8f0((longlong)(param_1 + 0x17),iVar2);
  uVar7 = (uint7)(uVar5 >> 8);
  if ((char)uVar5 == '\0') {
    return CONCAT71(uVar7,1);
  }
  if (*(int *)((longlong)param_1 + 0x2c) < 1) {
    return (ulonglong)uVar7 << 8;
  }
  uVar9 = (int)(char)param_1[8] >> 0x1f & 7;
  iVar10 = (uVar9 + (int)(char)param_1[8] & 7) - uVar9;
  iVar2 = *(int *)((longlong)param_1 + 0x2c) + -1;
  *(int *)((longlong)param_1 + 0x2c) = iVar2;
  if (iVar2 != 0) {
    memcpy(param_1 + 8,(void *)((longlong)param_1 + 0x41),(longlong)iVar2);
  }
  uVar6 = FUN_14005b9e0(param_1,iVar10,param_2);
  if ((char)uVar6 != '\0') {
    return CONCAT71((int7)((ulonglong)uVar6 >> 8),1);
  }
  if ((param_1[0x28] == 0) || (bVar1 = FUN_140069750(param_1[0x28]), !bVar1)) {
    uVar6 = FUN_140058260((longlong)param_1,iVar10);
    if (((char)uVar6 != '\0') && (*(int *)((longlong)param_1 + 0x2c) != 0)) {
LAB_14005caf0:
      *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
      uVar6 = FUN_14005b9e0(param_1,(int)(char)param_1[8],param_2);
      return uVar6;
    }
    uVar9 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                      (*(longlong **)(param_1[0x14] + 0x10),0x15);
    uVar5 = (ulonglong)(uVar9 >> 5);
    if ((uVar9 >> 5 & 1) != 0) {
      (**(code **)(*(longlong *)param_1[0x20] + 0x28))((longlong *)param_1[0x20],&local_res18);
      uVar3 = (**(code **)(param_1[2] + 0x18))(param_1 + 2);
      uVar6 = FUN_140059f40(param_1,local_res18,local_res1c,uVar3);
      return uVar6;
    }
  }
  else {
    uVar5 = FUN_140058b80((longlong)param_1,(undefined8 *)&local_res18);
    if ((char)uVar5 != '\0') {
      *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
      iVar2 = tq::RandGet(100);
      if (iVar2 < 0x46) {
        uVar3 = 0;
      }
      else {
        uVar3 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                          (*(longlong **)(param_1[0x14] + 0x10),0x10);
      }
      uVar5 = FUN_1400580e0((longlong)param_1,local_res18,local_res1c,uVar3);
      if (((((char)uVar5 != '\0') &&
           (uVar5 = FUN_14005b9e0(param_1,(int)(char)param_1[8],param_2), (char)uVar5 == '\0')) &&
          (uVar5 = FUN_1400588b0((longlong)param_1,local_res18,(ulonglong)local_res1c,iVar10),
          (char)uVar5 != '\0')) && (*(int *)((longlong)param_1 + 0x2c) != 0)) goto LAB_14005caf0;
    }
  }
  return uVar5 & 0xffffffffffffff00;
}


// ==== FUN_14005cb60 @ 14005cb60  undefined8 FUN_14005cb60(longlong * param_1)

ulonglong FUN_14005cb60(longlong *param_1)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  ulonglong in_RAX;
  undefined7 extraout_var;
  longlong lVar7;
  longlong *plVar8;
  ulonglong extraout_RAX;
  undefined8 uVar9;
  ulonglong uVar10;
  undefined7 extraout_var_00;
  undefined4 extraout_var_01;
  uint local_res8;
  uint uStackX_c;
  
  if (param_1[0x28] != 0) {
    bVar1 = FUN_140069750(param_1[0x28]);
    in_RAX = CONCAT71(extraout_var,bVar1);
    if (bVar1) {
      FUN_1400696d0(param_1[0x28]);
      lVar7 = FUN_14001c200();
      plVar8 = (longlong *)FUN_14001c130(lVar7);
      lVar7 = FUN_140034e00(plVar8);
      if (lVar7 == 0) {
        log_InlineLogERROR(&DAT_1400be0b0);
        return extraout_RAX & 0xffffffffffffff00;
      }
      lVar7 = FUN_14001c210();
      plVar8 = (longlong *)FUN_140038010(lVar7,*(int *)((longlong)param_1 + 0x84));
      if ((plVar8 != (longlong *)0x0) && (iVar3 = FUN_1400696e0(param_1[0x28]), iVar3 != 3)) {
        lVar7 = param_1[2];
        uVar4 = (**(code **)(*plVar8 + 0x40))(plVar8);
        uVar5 = (**(code **)(*plVar8 + 0x38))(plVar8);
        uVar9 = (**(code **)(lVar7 + 8))(param_1 + 2,uVar5,uVar4);
        if ((0x12 < (int)uVar9) ||
           (uVar9 = (**(code **)(*plVar8 + 0x50))(plVar8), (char)uVar9 == '\0')) {
          *(undefined4 *)(param_1 + 3) = 1;
          *(undefined4 *)((longlong)param_1 + 0x84) = 0;
          *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
          return CONCAT71((int7)((ulonglong)uVar9 >> 8),1);
        }
        lVar7 = param_1[2];
        uVar4 = (**(code **)(*plVar8 + 0x40))(plVar8);
        uVar5 = (**(code **)(*plVar8 + 0x38))(plVar8);
        iVar3 = (**(code **)(lVar7 + 8))(param_1 + 2,uVar5,uVar4);
        lVar7 = param_1[2];
        uVar4 = (**(code **)(*plVar8 + 0x48))(plVar8);
        iVar6 = (**(code **)(lVar7 + 0x10))(param_1 + 2,uVar4);
        if (iVar3 <= iVar6) {
          uVar9 = FUN_140059c90(param_1);
          *(undefined4 *)(param_1 + 3) = 8;
          *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
          return CONCAT71((int7)((ulonglong)uVar9 >> 8),1);
        }
        uVar10 = FUN_14005ad00((longlong)param_1);
        if ((char)uVar10 != '\0') {
          iVar3 = (**(code **)(*plVar8 + 0x40))(plVar8);
          iVar6 = (**(code **)(*plVar8 + 0x38))(plVar8);
          cVar2 = FUN_1400580e0((longlong)param_1,iVar6,iVar3,0);
          if (cVar2 != '\0') {
            uVar9 = FUN_14005c960(param_1,1);
            return CONCAT71((int7)((ulonglong)uVar9 >> 8),1);
          }
        }
      }
      uVar9 = FUN_140058b80((longlong)param_1,(undefined8 *)&local_res8);
      if ((char)uVar9 == '\0') {
        return uVar9;
      }
      uVar10 = FUN_140058ca0((longlong)param_1,CONCAT44(uStackX_c,local_res8));
      if ((char)uVar10 == '\0') {
        if (*(int *)((longlong)param_1 + 0x2c) != 0) {
          uVar9 = FUN_14005c960(param_1,0);
          return CONCAT71((int7)((ulonglong)uVar9 >> 8),1);
        }
        cVar2 = FUN_1400580e0((longlong)param_1,local_res8,uStackX_c,0);
        if (cVar2 != '\0') {
          uVar9 = FUN_14005c960(param_1,0);
          return CONCAT71((int7)((ulonglong)uVar9 >> 8),1);
        }
        iVar3 = (**(code **)(param_1[2] + 0x18))(param_1 + 2);
        uVar9 = FUN_1400588b0((longlong)param_1,local_res8,(ulonglong)uStackX_c,iVar3);
        if ((char)uVar9 != '\0') {
          *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
          uVar9 = FUN_14005b9e0(param_1,(int)(char)param_1[8],0);
          return CONCAT71((int7)((ulonglong)uVar9 >> 8),1);
        }
      }
      else {
        bVar1 = FUN_140069910(param_1[0x28]);
        uVar9 = CONCAT71(extraout_var_00,bVar1);
        if (!bVar1) {
          iVar3 = FUN_1400696e0(param_1[0x28]);
          uVar9 = CONCAT44(extraout_var_01,iVar3);
          if (iVar3 != 2) {
            *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
            uVar9 = FUN_140069b60((undefined4 *)param_1[0x28]);
            *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
            *(undefined4 *)(param_1 + 3) = 1;
            return CONCAT71((int7)((ulonglong)uVar9 >> 8),1);
          }
        }
      }
      *(undefined4 *)(param_1 + 3) = 1;
      *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
      return CONCAT71((int7)((ulonglong)uVar9 >> 8),1);
    }
  }
  return in_RAX & 0xffffffffffffff00;
}


// ==== FUN_14005ce80 @ 14005ce80  undefined8 * FUN_14005ce80(undefined8 * param_1)

undefined8 * FUN_14005ce80(undefined8 *param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong lVar3;
  undefined8 *puVar4;
  longlong lVar5;
  undefined8 local_30;
  longlong *local_28;
  
  FUN_1400695c0(param_1);
  puVar4 = param_1 + 2;
  *puVar4 = IRole::vftable;
  *puVar4 = INpc::vftable;
  *param_1 = CNpc::vftable;
  *puVar4 = CNpc::vftable;
  *(undefined4 *)((longlong)param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 5) = 0;
  *(undefined1 *)((longlong)param_1 + 0x3e) = 0;
  *(undefined4 *)((longlong)param_1 + 0x8c) = 0;
  *(undefined4 *)(param_1 + 0x15) = 0;
  *(undefined4 *)((longlong)param_1 + 0xac) = 0;
  *(undefined4 *)(param_1 + 0x16) = 0;
  *(undefined4 *)((longlong)param_1 + 0xb4) = 0;
  *(undefined4 *)(param_1 + 0x17) = 0;
  *(undefined4 *)((longlong)param_1 + 0xbc) = 0;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  FUN_140041230(param_1 + 0x18);
  param_1[0x1a] = 0;
  param_1[0x1b] = 0;
  param_1[0x1c] = 0;
  lVar5 = 5;
  lVar3 = 5;
  do {
    *(undefined4 *)((longlong)param_1 + lVar3 * 4 + 0xe8) = 0;
    lVar3 = lVar3 + -1;
  } while (-1 < lVar3);
  param_1[0x20] = 0;
  *(undefined1 *)(param_1 + 0x21) = 0;
  *(undefined4 *)((longlong)param_1 + 0x10c) = 0;
  *(undefined4 *)(param_1 + 0x22) = 0;
  *(undefined4 *)((longlong)param_1 + 0x114) = 0;
  *(undefined4 *)(param_1 + 0x23) = 0;
  *(undefined4 *)((longlong)param_1 + 0x11c) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)((longlong)param_1 + 0x124) = 0;
  *(undefined4 *)(param_1 + 0x25) = 0;
  *(undefined4 *)((longlong)param_1 + 300) = 0;
  *(undefined1 *)(param_1 + 0x26) = 1;
  *(undefined4 *)((longlong)param_1 + 0x134) = 0;
  *(undefined4 *)(param_1 + 0x27) = 0;
  param_1[0x28] = 0;
  *(undefined1 *)(param_1 + 0x29) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14c) = 0;
  *(undefined4 *)(param_1 + 0x2a) = 0;
  CGameMap::vf_0x18((longlong)param_1,0x1040);
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  param_1[0x14] = 0;
  *(undefined4 *)(param_1 + 3) = 1;
  *(undefined4 *)(param_1 + 0x15) = 0;
  param_1[0x13] = 0;
  *(undefined4 *)(param_1 + 7) = 0;
  do {
    *(undefined4 *)((longlong)param_1 + lVar5 * 4 + 0xe8) = 0;
    lVar5 = lVar5 + -1;
  } while (-1 < lVar5);
  *(undefined4 *)((longlong)param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 6) = 0;
  *(undefined4 *)(param_1 + 0x11) = 0;
  *(undefined1 *)((longlong)param_1 + 0x3d) = 0;
  *(undefined4 *)((longlong)param_1 + 0x84) = 0;
  *(undefined1 *)((longlong)param_1 + 0x3c) = 1;
  *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x17) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14c) = 0;
  *(undefined1 *)((longlong)param_1 + 0x3f) = 0;
  if ((param_1[0x1a] != 0) || (puVar4 == (undefined8 *)0x0)) {
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  param_1[0x1a] = puVar4;
  lVar3 = FUN_14001d230();
  puVar4 = FUN_140042b80(lVar3,&local_30,0);
  FUN_1400402d0(param_1 + 0x18,*puVar4,puVar4[1]);
  if (local_28 != (longlong *)0x0) {
    LOCK();
    plVar1 = local_28 + 2;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)*plVar1 == 0) {
      (**(code **)*local_28)(local_28);
      LOCK();
      piVar2 = (int *)((longlong)local_28 + 0x14);
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (*piVar2 == 0) {
        (**(code **)(*local_28 + 8))(local_28);
      }
    }
  }
  return param_1;
}


// ==== FUN_14005d140 @ 14005d140  undefined8 FUN_14005d140(longlong * param_1)

undefined8 FUN_14005d140(longlong *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 extraout_RAX;
  longlong lVar5;
  longlong *plVar6;
  undefined8 uVar7;
  uint7 extraout_var;
  undefined7 uVar8;
  
  uVar1 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                    (*(longlong **)(param_1[0x14] + 0x10),0x15);
  if ((~(byte)(uVar1 >> 0xf) & 1) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
    *(undefined4 *)(param_1 + 3) = 1;
    return CONCAT71((int7)((ulonglong)extraout_RAX >> 8),1);
  }
  lVar5 = FUN_14001c210();
  plVar6 = (longlong *)FUN_140038010(lVar5,*(int *)((longlong)param_1 + 0x84));
  uVar1 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                    (*(longlong **)(param_1[0x14] + 0x10),0x15);
  if ((uVar1 >> 3 & 1) == 0) {
    uVar1 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                      (*(longlong **)(param_1[0x14] + 0x10),0x15);
    if ((uVar1 >> 4 & 1) == 0) goto LAB_14005d291;
  }
  if (plVar6 != (longlong *)0x0) {
    iVar2 = (**(code **)(*plVar6 + 0x40))(plVar6);
    iVar3 = (**(code **)(*plVar6 + 0x38))(plVar6);
    uVar4 = FUN_14004cc70(param_1[0x13],iVar3,iVar2);
    if ((char)uVar4 != '\0') {
      uVar4 = (**(code **)(param_1[2] + 0x18))(param_1 + 2);
      iVar2 = (**(code **)(*plVar6 + 0x40))(plVar6);
      iVar3 = (**(code **)(*plVar6 + 0x38))(plVar6);
      uVar7 = FUN_1400597f0(param_1,iVar3,iVar2,uVar4);
      *(undefined4 *)(param_1 + 3) = 7;
      return CONCAT71((int7)((ulonglong)uVar7 >> 8),1);
    }
  }
LAB_14005d291:
  lVar5 = FUN_14005b030((longlong)param_1);
  if ((char)lVar5 == '\0') {
    if (*(int *)((longlong)param_1 + 0x2c) == 0) {
      iVar2 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                        (*(longlong **)(param_1[0x14] + 0x10),0x10);
      FUN_14005b760(param_1,iVar2 * 2);
      lVar5 = (ulonglong)extraout_var << 8;
    }
    uVar8 = (undefined7)((ulonglong)lVar5 >> 8);
    if (*(int *)((longlong)param_1 + 0x84) == 0) {
      *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
      *(undefined4 *)(param_1 + 3) = 1;
      return CONCAT71(uVar8,1);
    }
    if (*(int *)((longlong)param_1 + 0x2c) == 0) {
      *(undefined4 *)(param_1 + 3) = 7;
      return CONCAT71(uVar8,1);
    }
    lVar5 = FUN_14005c960(param_1,1);
  }
  return CONCAT71((int7)((ulonglong)lVar5 >> 8),1);
}


// ==== FUN_14005d330 @ 14005d330  undefined8 FUN_14005d330(longlong * param_1)

undefined8 FUN_14005d330(longlong *param_1)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  longlong lVar7;
  longlong *plVar8;
  undefined7 extraout_var;
  longlong *plVar9;
  
  lVar7 = FUN_14001c210();
  plVar8 = (longlong *)FUN_140038010(lVar7,*(int *)((longlong)param_1 + 0x84));
  if (plVar8 == (longlong *)0x0) {
LAB_14005d475:
    if (param_1[0x28] == 0) {
LAB_14005d48f:
      plVar8 = (longlong *)FUN_14005bc80(param_1);
      if ((char)plVar8 != '\0') {
        lVar7 = FUN_14001c210();
        plVar9 = (longlong *)FUN_140038010(lVar7,*(int *)((longlong)param_1 + 0x84));
        plVar8 = plVar9;
        if (plVar9 == (longlong *)0x0) goto LAB_14005d535;
        plVar8 = (longlong *)(**(code **)(*plVar9 + 0x50))(plVar9);
        if ((char)plVar8 == '\0') goto LAB_14005d535;
        lVar7 = param_1[2];
        uVar5 = (**(code **)(*plVar9 + 0x40))(plVar9);
        uVar6 = (**(code **)(*plVar9 + 0x38))(plVar9);
        iVar3 = (**(code **)(lVar7 + 8))(param_1 + 2,uVar6,uVar5);
        uVar5 = (**(code **)(*plVar9 + 0x48))(plVar9);
        plVar8 = (longlong *)(**(code **)(lVar7 + 0x10))(param_1 + 2,uVar5);
        if (iVar3 <= (int)plVar8) goto LAB_14005d535;
        if (*(int *)((longlong)param_1 + 0x2c) != 0) {
          plVar8 = (longlong *)FUN_14005ad00((longlong)param_1);
          if ((char)plVar8 != '\0') goto LAB_14005d467;
        }
      }
    }
    else {
      bVar2 = FUN_140069750(param_1[0x28]);
      plVar8 = (longlong *)CONCAT71(extraout_var,bVar2);
      if (!bVar2) goto LAB_14005d48f;
    }
    *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
    *(undefined4 *)(param_1 + 3) = 1;
  }
  else {
    cVar1 = (**(code **)(*plVar8 + 0x50))(plVar8);
    if (cVar1 == '\0') goto LAB_14005d475;
    iVar3 = (**(code **)(param_1[2] + 0x30))(param_1 + 2);
    iVar4 = (**(code **)(*plVar8 + 0x30))(plVar8);
    if (iVar4 != iVar3) goto LAB_14005d475;
    lVar7 = param_1[2];
    uVar5 = (**(code **)(*plVar8 + 0x40))(plVar8);
    uVar6 = (**(code **)(*plVar8 + 0x38))(plVar8);
    iVar3 = (**(code **)(lVar7 + 8))(param_1 + 2,uVar6,uVar5);
    uVar5 = (**(code **)(*plVar8 + 0x48))(plVar8);
    iVar4 = (**(code **)(lVar7 + 0x10))(param_1 + 2,uVar5);
    if (iVar4 < iVar3) goto LAB_14005d475;
    plVar8 = (longlong *)FUN_140002700((int *)(param_1 + 0x15));
    if ((char)plVar8 == '\0') goto LAB_14005d535;
    if (param_1[0x13] != 0) {
      plVar8 = (longlong *)(**(code **)(param_1[2] + 0xe8))(param_1 + 2);
      plVar8 = (longlong *)FUN_14004ad20(param_1[0x13],plVar8);
      if ((char)plVar8 != '\0') {
        *(undefined1 *)((longlong)param_1 + 0x3c) = 0;
        plVar8 = (longlong *)FUN_140058260((longlong)param_1,-1);
        *(undefined1 *)((longlong)param_1 + 0x3c) = 1;
        if (*(int *)((longlong)param_1 + 0x2c) != 0) {
          plVar8 = (longlong *)FUN_14005c960(param_1,2);
        }
      }
    }
    if (*(char *)((longlong)param_1 + 0x3e) != '\0') {
      *(undefined1 *)((longlong)param_1 + 0x3e) = 0;
      goto LAB_14005d535;
    }
LAB_14005d467:
    *(undefined4 *)(param_1 + 3) = 7;
  }
LAB_14005d535:
  return CONCAT71((int7)((ulonglong)plVar8 >> 8),1);
}


// ==== FUN_14005d550 @ 14005d550  undefined8 FUN_14005d550(longlong * param_1)

undefined8 FUN_14005d550(longlong *param_1)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  uint uVar7;
  undefined4 uVar8;
  longlong lVar9;
  longlong *plVar10;
  ulonglong uVar11;
  ulonglong extraout_RAX;
  int local_res8;
  int local_resc;
  
  lVar9 = FUN_14001c210();
  plVar10 = (longlong *)FUN_140038010(lVar9,*(int *)((longlong)param_1 + 0x84));
  if ((plVar10 == (longlong *)0x0) ||
     (cVar1 = (**(code **)(*plVar10 + 0x50))(plVar10), cVar1 == '\0')) {
LAB_14005d668:
    uVar11 = FUN_14005cb60(param_1);
    if ((char)uVar11 != '\0') goto LAB_14005d99a;
    (**(code **)(*(longlong *)param_1[0x20] + 0x28))((longlong *)param_1[0x20],&local_res8);
    uVar7 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                      (*(longlong **)(param_1[0x14] + 0x10),0x15);
    if ((((uVar7 >> 3 & 1) == 0) &&
        (uVar7 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                           (*(longlong **)(param_1[0x14] + 0x10),0x15), (uVar7 >> 4 & 1) == 0)) &&
       (uVar7 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                          (*(longlong **)(param_1[0x14] + 0x10),0x15), (uVar7 >> 7 & 1) == 0)) {
LAB_14005d789:
      uVar7 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))();
      if (((((uVar7 >> 3 & 1) != 0) ||
           (uVar7 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))(),
           (uVar7 >> 4 & 1) != 0)) ||
          (uVar7 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))(),
          (uVar7 >> 0xb & 1) != 0)) && (plVar10 != (longlong *)0x0)) {
        lVar9 = param_1[2];
        uVar5 = (**(code **)(*plVar10 + 0x40))(plVar10);
        uVar6 = (**(code **)(*plVar10 + 0x38))(plVar10);
        iVar3 = (**(code **)(lVar9 + 8))(param_1 + 2,uVar6,uVar5);
        if ((5 < iVar3) && (param_1[0x13] != 0)) {
          iVar3 = (**(code **)(*plVar10 + 0x40))(plVar10);
          iVar4 = (**(code **)(*plVar10 + 0x38))(plVar10);
          bVar2 = FUN_140049310(param_1[0x13],iVar4,iVar3);
          if (bVar2) {
            uVar5 = (**(code **)(param_1[2] + 0x18))(param_1 + 2);
            iVar3 = (**(code **)(*plVar10 + 0x40))(plVar10);
            iVar4 = (**(code **)(*plVar10 + 0x38))(plVar10);
            uVar11 = FUN_1400597f0(param_1,iVar4,iVar3,uVar5);
            goto LAB_14005d99a;
          }
        }
      }
      if (*(int *)((longlong)param_1 + 0x2c) != 0) {
        if (*(int *)((longlong)param_1 + 0x84) == 0) {
          uVar11 = FUN_14005c960(param_1,0);
        }
        else {
          uVar11 = FUN_14005c960(param_1,1);
        }
        goto LAB_14005d99a;
      }
      uVar11 = FUN_14005bc80(param_1);
      if ((char)uVar11 != '\0') {
        if (*(int *)((longlong)param_1 + 0x2c) != 0) {
          return uVar11 & 0xffffffffffffff00;
        }
        uVar7 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                          (*(longlong **)(param_1[0x14] + 0x10),0x15);
        uVar11 = (ulonglong)(uVar7 >> 5);
        if ((uVar7 >> 5 & 1) != 0) {
          lVar9 = FUN_14001c210();
          plVar10 = (longlong *)FUN_140038010(lVar9,*(int *)((longlong)param_1 + 0x84));
          if (plVar10 == (longlong *)0x0) {
            log_InlineLogERROR(&DAT_1400be0b0);
            uVar11 = extraout_RAX;
          }
          else {
            uVar5 = (**(code **)(param_1[2] + 0x18))(param_1 + 2);
            iVar3 = (**(code **)(*plVar10 + 0x40))(plVar10);
            iVar4 = (**(code **)(*plVar10 + 0x38))(plVar10);
            uVar11 = FUN_140059f40(param_1,iVar4,iVar3,uVar5);
          }
          goto LAB_14005d99a;
        }
      }
    }
    else {
      lVar9 = *(longlong *)param_1[0x20];
      uVar5 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
      uVar6 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
      uVar8 = (**(code **)(param_1[2] + 0x30))(param_1 + 2);
      cVar1 = (**(code **)(lVar9 + 0x70))(param_1[0x20],uVar8,uVar6,uVar5,0x30);
      if (cVar1 == '\0') {
        if (plVar10 != (longlong *)0x0) {
          lVar9 = *(longlong *)param_1[0x20];
          uVar5 = (**(code **)(*plVar10 + 0x40))(plVar10);
          uVar6 = (**(code **)(*plVar10 + 0x38))(plVar10);
          uVar8 = (**(code **)(*plVar10 + 0x30))(plVar10);
          cVar1 = (**(code **)(lVar9 + 0x70))(param_1[0x20],uVar8,uVar6,uVar5,0x30);
          if (cVar1 != '\0') goto LAB_14005d969;
        }
        goto LAB_14005d789;
      }
LAB_14005d969:
      *(undefined4 *)((longlong)param_1 + 0x84) = 0;
      uVar5 = (**(code **)(param_1[2] + 0x18))(param_1 + 2);
      uVar11 = FUN_14005a0d0(param_1,local_res8,local_resc,uVar5);
    }
    *(undefined4 *)(param_1 + 3) = 1;
  }
  else {
    iVar3 = (**(code **)(*plVar10 + 0x30))(plVar10);
    iVar4 = (**(code **)(param_1[2] + 0x30))(param_1 + 2);
    if (iVar3 != iVar4) goto LAB_14005d668;
    lVar9 = param_1[2];
    uVar5 = (**(code **)(*plVar10 + 0x40))(plVar10);
    uVar6 = (**(code **)(*plVar10 + 0x38))(plVar10);
    iVar3 = (**(code **)(lVar9 + 8))(param_1 + 2,uVar6,uVar5);
    uVar5 = (**(code **)(*plVar10 + 0x48))(plVar10);
    iVar4 = (**(code **)(lVar9 + 0x10))(param_1 + 2,uVar5);
    if (iVar4 < iVar3) goto LAB_14005d668;
    uVar7 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                      (*(longlong **)(param_1[0x14] + 0x10),0x15);
    if ((((((uVar7 >> 3 & 1) == 0) &&
          (uVar11 = FUN_14005ad00((longlong)param_1), (char)uVar11 == '\0')) &&
         (cVar1 = (**(code **)(param_1[2] + 0x60))(param_1 + 2), cVar1 != '\0')) &&
        ((*(char *)((longlong)param_1 + 0x3c) == '\0' && (0 < *(int *)((longlong)param_1 + 0x2c)))))
       && (uVar11 = FUN_14005c960(param_1,1), (char)uVar11 != '\0')) goto LAB_14005d99a;
    uVar11 = FUN_140059c90(param_1);
    *(undefined4 *)(param_1 + 3) = 8;
  }
  *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
LAB_14005d99a:
  return CONCAT71((int7)(uVar11 >> 8),1);
}


// ==== FUN_14005d9c0 @ 14005d9c0  undefined8 * FUN_14005d9c0(void)

undefined8 * FUN_14005d9c0(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x158);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    puVar1 = FUN_14005ce80(puVar1);
  }
  return puVar1;
}


// ==== FUN_14005da00 @ 14005da00  undefined FUN_14005da00(longlong param_1)

void FUN_14005da00(longlong param_1)

{
  int *piVar1;
  void *pvVar2;
  longlong *plVar3;
  int iVar4;
  longlong lVar5;
  undefined8 *puVar6;
  undefined8 local_20;
  longlong *local_18;
  
  pvVar2 = *(void **)(param_1 + 0x140);
  if (pvVar2 != (void *)0x0) {
    FUN_140069610();
    operator_delete(pvVar2);
    *(undefined8 *)(param_1 + 0x140) = 0;
  }
  plVar3 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
  iVar4 = (**(code **)(*plVar3 + 0x10))(plVar3,0x27);
  if (iVar4 != 0) {
    lVar5 = FUN_14001d230();
    puVar6 = FUN_140042b80(lVar5,&local_20,1);
    FUN_1400402d0((undefined8 *)(param_1 + 0xc0),*puVar6,puVar6[1]);
    if (local_18 != (longlong *)0x0) {
      LOCK();
      plVar3 = local_18 + 2;
      *(int *)plVar3 = (int)*plVar3 + -1;
      UNLOCK();
      if ((int)*plVar3 == 0) {
        (**(code **)*local_18)(local_18);
        LOCK();
        piVar1 = (int *)((longlong)local_18 + 0x14);
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (*piVar1 == 0) {
          (**(code **)(*local_18 + 8))(local_18);
        }
      }
    }
  }
  return;
}


// ==== FUN_14005dac0 @ 14005dac0  undefined FUN_14005dac0(longlong param_1, ulonglong param_2)

void FUN_14005dac0(longlong param_1,ulonglong param_2)

{
  void *pvVar1;
  void *_Dst;
  ulonglong uVar2;
  code *pcVar3;
  ulonglong uVar4;
  void *_Dst_00;
  rsize_t rVar5;
  longlong lVar6;
  longlong lVar7;
  
  uVar2 = *(ulonglong *)(param_1 + 0x28);
  if (0xfffffffffffffff - uVar2 < param_2) {
    FUN_140058fb0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  uVar4 = uVar2 >> 1;
  if (uVar4 < 8) {
    uVar4 = 8;
  }
  if ((param_2 < uVar4) && (uVar2 <= 0xfffffffffffffff - uVar4)) {
    param_2 = uVar4;
  }
  uVar4 = *(ulonglong *)(param_1 + 0x30) >> 2;
  _Dst_00 = (void *)FUN_14005a880(param_1 + 0x10,uVar2 + param_2);
  lVar6 = uVar4 * 8;
  pvVar1 = (void *)(lVar6 + *(longlong *)(param_1 + 0x20));
  lVar7 = (*(longlong *)(param_1 + 0x28) * 8 - (longlong)pvVar1) + *(longlong *)(param_1 + 0x20) >>
          3;
  rVar5 = lVar7 * 8;
  _Dst = (void *)(rVar5 + lVar6 + (longlong)_Dst_00);
  if (lVar7 != 0) {
    memmove_s((void *)(lVar6 + (longlong)_Dst_00),rVar5,pvVar1,rVar5);
  }
  if (param_2 < uVar4) {
    lVar7 = (longlong)(param_2 * 8) >> 3;
    if (lVar7 != 0) {
      rVar5 = lVar7 << 3;
      memmove_s(_Dst,rVar5,*(void **)(param_1 + 0x20),rVar5);
    }
    pvVar1 = (void *)(*(longlong *)(param_1 + 0x20) + param_2 * 8);
    lVar6 = (lVar6 - (longlong)pvVar1) + *(longlong *)(param_1 + 0x20) >> 3;
    rVar5 = lVar6 * 8;
    if (lVar6 != 0) {
      memmove_s(_Dst_00,rVar5,pvVar1,rVar5);
    }
    if (param_2 != 0) {
      memset((void *)(rVar5 + (longlong)_Dst_00),0,param_2 << 3);
    }
  }
  else {
    rVar5 = (lVar6 >> 3) * 8;
    if (lVar6 >> 3 != 0) {
      memmove_s(_Dst,rVar5,*(void **)(param_1 + 0x20),rVar5);
    }
    if (param_2 - uVar4 != 0) {
      memset((void *)(rVar5 + (longlong)_Dst),0,(param_2 - uVar4) * 8);
    }
    if (uVar4 != 0) {
      memset(_Dst_00,0,uVar4 << 3);
    }
  }
  if (*(void **)(param_1 + 0x20) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x20));
  }
  *(longlong *)(param_1 + 0x28) = *(longlong *)(param_1 + 0x28) + param_2;
  *(void **)(param_1 + 0x20) = _Dst_00;
  return;
}


// ==== FUN_14005dc80 @ 14005dc80  undefined8 FUN_14005dc80(longlong * param_1, undefined4 param_2)

ulonglong FUN_14005dc80(longlong *param_1,undefined4 param_2)

{
  longlong *plVar1;
  int *piVar2;
  char cVar3;
  bool bVar4;
  undefined4 uVar5;
  ulonglong uVar6;
  longlong lVar7;
  undefined8 *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined8 uVar11;
  undefined8 local_30;
  longlong *local_28;
  
  if ((int)param_1[0x25] == 0) {
    uVar6 = FUN_14005af40(param_1,4,0);
    uVar6 = uVar6 & 0xffffffffffffff00;
  }
  else {
    uVar6 = FUN_14005ad00((longlong)param_1);
    if (((char)uVar6 == '\0') || (cVar3 = (**(code **)(param_1[2] + 0x50))(), cVar3 == '\0')) {
      (**(code **)(*(longlong *)param_1[0x14] + 8))();
      (**(code **)(*param_1 + 8))(param_1);
      log_InlineLogWARNING(&DAT_1400c95b8);
      uVar6 = FUN_14005af40(param_1,4,0);
      uVar6 = uVar6 & 0xffffffffffffff00;
    }
    else if ((param_1[0x28] == 0) ||
            ((bVar4 = FUN_140069750(param_1[0x28]), !bVar4 ||
             (bVar4 = FUN_140069910(param_1[0x28]), bVar4)))) {
      if (param_1[0x28] != 0) {
        FUN_14005af40(param_1,4,0);
        FUN_14005da00((longlong)param_1);
      }
      lVar7 = FUN_14001d230();
      puVar8 = FUN_140042b80(lVar7,&local_30,0);
      FUN_1400402d0(param_1 + 0x18,*puVar8,puVar8[1]);
      if (local_28 != (longlong *)0x0) {
        LOCK();
        plVar1 = local_28 + 2;
        lVar7 = *plVar1;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)lVar7 == 1) {
          (**(code **)*local_28)(local_28);
          LOCK();
          piVar2 = (int *)((longlong)local_28 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*local_28 + 8))(local_28);
          }
        }
      }
      if (param_1[0x18] == 0) {
        log_InlineLogERROR(&DAT_1400be0b0);
        uVar6 = FUN_14005af40(param_1,4,0);
        uVar6 = uVar6 & 0xffffffffffffff00;
      }
      else {
        FUN_14005b580((longlong)param_1);
        puVar10 = (undefined4 *)0x0;
        *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
        *(undefined4 *)(param_1 + 3) = 1;
        puVar9 = (undefined4 *)operator_new(0x2c);
        if (puVar9 != (undefined4 *)0x0) {
          puVar10 = FUN_140069930(puVar9);
        }
        param_1[0x28] = (longlong)puVar10;
        if (puVar10 == (undefined4 *)0x0) {
          log_InlineLogERROR(&DAT_1400be0b0);
          uVar6 = FUN_14005af40(param_1,4,0);
          uVar6 = uVar6 & 0xffffffffffffff00;
        }
        else {
          *(undefined4 *)((longlong)param_1 + 0x84) = 0;
          *(undefined4 *)(param_1 + 0x11) = 0;
          *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
          *(undefined4 *)(param_1 + 3) = 1;
          uVar5 = (**(code **)(*param_1 + 8))(param_1);
          FUN_140069620((undefined4 *)param_1[0x28],*(undefined4 *)((longlong)param_1 + 300),uVar5,
                        (int)param_1[0x25],(char)param_1[0x26],param_2,
                        *(undefined4 *)((longlong)param_1 + 0x134));
          uVar11 = FUN_140069a60((undefined4 *)param_1[0x28]);
          uVar6 = CONCAT71((int7)((ulonglong)uVar11 >> 8),1);
        }
      }
    }
    else {
      uVar6 = FUN_14005af40(param_1,4,0);
      uVar6 = uVar6 & 0xffffffffffffff00;
    }
  }
  return uVar6;
}


// ==== FUN_14005df30 @ 14005df30  undefined FUN_14005df30(longlong param_1)

void FUN_14005df30(longlong param_1)

{
  bool bVar1;
  
  if (*(undefined4 **)(param_1 + 0x140) != (undefined4 *)0x0) {
    FUN_140069dd0(*(undefined4 **)(param_1 + 0x140));
    bVar1 = FUN_140069910(*(longlong *)(param_1 + 0x140));
    if (!bVar1) {
      FUN_14005da00(param_1);
    }
  }
  return;
}


// ==== FUN_14005df70 @ 14005df70  undefined8 FUN_14005df70(longlong * param_1)

ulonglong FUN_14005df70(longlong *param_1)

{
  bool bVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  ulonglong in_RAX;
  undefined7 extraout_var;
  longlong lVar5;
  longlong *plVar6;
  ulonglong extraout_RAX;
  ulonglong uVar7;
  undefined4 extraout_var_02;
  undefined6 extraout_var_01;
  undefined7 extraout_var_00;
  undefined8 uVar8;
  ulonglong *puVar9;
  ulonglong uVar10;
  ulonglong extraout_RAX_00;
  undefined8 local_res8;
  
  if (param_1[0x28] == 0) {
LAB_14005e224:
    return in_RAX & 0xffffffffffffff00;
  }
  bVar1 = FUN_140069750(param_1[0x28]);
  in_RAX = CONCAT71(extraout_var,bVar1);
  if (!bVar1) goto LAB_14005e224;
  FUN_1400696d0(param_1[0x28]);
  lVar5 = FUN_14001c200();
  plVar6 = (longlong *)FUN_14001c130(lVar5);
  lVar5 = FUN_140034e00(plVar6);
  if (lVar5 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    uVar7 = extraout_RAX;
LAB_14005dff7:
    return uVar7 & 0xffffffffffffff00;
  }
  uVar7 = FUN_140058b80((longlong)param_1,&local_res8);
  if ((char)uVar7 == '\0') goto LAB_14005dff7;
  iVar3 = FUN_1400696e0(param_1[0x28]);
  uVar7 = local_res8;
  uVar8 = CONCAT44(extraout_var_02,iVar3);
  if (iVar3 == 2) {
    uVar2 = FUN_140065700(lVar5);
    bVar1 = FUN_140069bd0(param_1[0x28],(int)CONCAT62(extraout_var_01,uVar2));
    uVar8 = CONCAT71(extraout_var_00,bVar1);
    if (!bVar1) goto LAB_14005e216;
    FUN_140069c80((undefined4 *)param_1[0x28]);
    lVar5 = FUN_1400654b0();
    if (lVar5 == 0) {
      uVar8 = FUN_140069c30((undefined4 *)param_1[0x28]);
      return CONCAT71((int7)((ulonglong)uVar8 >> 8),1);
    }
    puVar9 = FUN_140065510(lVar5,&local_res8);
    uVar7 = *puVar9;
    local_res8 = uVar7;
    uVar4 = FUN_140065490(lVar5);
    FUN_140069960((undefined4 *)param_1[0x28],uVar4);
    *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
LAB_14005e13b:
    lVar5 = FUN_1400580e0((longlong)param_1,(int)uVar7,local_res8._4_4_,0);
    if ((char)lVar5 != '\0') goto LAB_14005e149;
  }
  else if (iVar3 == 5) {
    uVar10 = FUN_140058ca0((longlong)param_1,local_res8);
    if ((char)uVar10 != '\0') {
      lVar5 = FUN_140065750(lVar5);
      if (lVar5 == 0) {
        uVar8 = FUN_14005da00((longlong)param_1);
        return CONCAT71((int7)((ulonglong)uVar8 >> 8),1);
      }
      uVar4 = FUN_140065490(lVar5);
      FUN_140069960((undefined4 *)param_1[0x28],uVar4);
      FUN_140058b80((longlong)param_1,&local_res8);
      *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
      uVar7 = local_res8;
      goto LAB_14005e13b;
    }
  }
  else if ((iVar3 == 3) || (iVar3 == 4)) goto LAB_14005e216;
  *(undefined4 *)(param_1 + 0x11) = 0;
  *(undefined1 *)((longlong)param_1 + 0x3d) = 0;
  uVar10 = FUN_14005ac20((longlong)param_1);
  if (((char)uVar10 != '\0') && (iVar3 = *(int *)((longlong)param_1 + 0x84), iVar3 != 0)) {
    lVar5 = FUN_14001c210();
    lVar5 = FUN_140038010(lVar5,iVar3);
    if (lVar5 != 0) {
LAB_14005e149:
      *(undefined4 *)(param_1 + 3) = 7;
      return CONCAT71((int7)((ulonglong)lVar5 >> 8),1);
    }
    log_InlineLogERROR(&DAT_1400be0b0);
    uVar10 = extraout_RAX_00;
  }
  if (*(int *)((longlong)param_1 + 0x2c) != 0) {
    return uVar10 & 0xffffffffffffff00;
  }
  uVar10 = FUN_140058ca0((longlong)param_1,uVar7);
  if ((char)uVar10 == '\0') {
    *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
    FUN_1400580e0((longlong)param_1,(int)uVar7,local_res8._4_4_,0);
    *(undefined4 *)(param_1 + 3) = 7;
    uVar8 = FUN_14005c960(param_1,0);
    return CONCAT71((int7)((ulonglong)uVar8 >> 8),1);
  }
  uVar8 = FUN_140069b60((undefined4 *)param_1[0x28]);
LAB_14005e216:
  return CONCAT71((int7)((ulonglong)uVar8 >> 8),1);
}


// ==== FUN_14005e230 @ 14005e230  undefined FUN_14005e230(longlong param_1, undefined4 * param_2)

void FUN_14005e230(longlong param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  void *pvVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  
  if (((*(char *)(param_1 + 0x30) + (char)*(longlong *)(param_1 + 0x38) & 3U) == 0) &&
     (*(ulonglong *)(param_1 + 0x28) <= *(longlong *)(param_1 + 0x38) + 4U >> 2)) {
    FUN_14005dac0(param_1,1);
  }
  uVar3 = *(longlong *)(param_1 + 0x30) + *(longlong *)(param_1 + 0x38);
  uVar4 = uVar3 >> 2;
  if (*(ulonglong *)(param_1 + 0x28) <= uVar4) {
    uVar4 = uVar4 - *(ulonglong *)(param_1 + 0x28);
  }
  if (*(longlong *)(*(longlong *)(param_1 + 0x20) + uVar4 * 8) == 0) {
    pvVar2 = operator_new(0x10);
    *(void **)(*(longlong *)(param_1 + 0x20) + uVar4 * 8) = pvVar2;
  }
  puVar1 = (undefined4 *)
           (*(longlong *)(*(longlong *)(param_1 + 0x20) + uVar4 * 8) +
           (ulonglong)((uint)uVar3 & 3) * 4);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = *param_2;
  }
  *(longlong *)(param_1 + 0x38) = *(longlong *)(param_1 + 0x38) + 1;
  return;
}


// ==== FUN_14005e2e0 @ 14005e2e0  undefined FUN_14005e2e0(longlong * param_1, int param_2, undefined4 param_3, int param_4, int param_5, int param_6, int param_7, int param_8, undefined4 param_9, undefined4 param_10, int param_11, int param_12, undefined1 param_13, int param_14, undefined4 param_15)

void FUN_14005e2e0(longlong *param_1,int param_2,undefined4 param_3,int param_4,int param_5,
                  int param_6,int param_7,int param_8,undefined4 param_9,undefined4 param_10,
                  int param_11,int param_12,undefined1 param_13,int param_14,undefined4 param_15)

{
  int *piVar1;
  undefined1 uVar2;
  bool bVar3;
  undefined4 uVar4;
  ulong uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  byte extraout_AH;
  longlong lVar9;
  longlong *plVar10;
  undefined8 *puVar11;
  undefined8 uVar12;
  undefined1 auStackY_4f8 [32];
  undefined8 local_4a8;
  longlong *local_4a0;
  undefined8 local_498 [136];
  ulonglong local_58;
  
  local_58 = DAT_140103510 ^ (ulonglong)auStackY_4f8;
  if (param_2 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  else {
    lVar9 = FUN_14001c7a0();
    plVar10 = (longlong *)FUN_140025be0(lVar9);
    lVar9 = (**(code **)(*plVar10 + 0x30))(plVar10,param_3);
    param_1[0x14] = lVar9;
    if (lVar9 == 0) {
      log_InlineLogERROR(&DAT_1400be0b0);
    }
    else {
      uVar2 = (**(code **)(**(longlong **)(lVar9 + 0x10) + 0x10))(*(longlong **)(lVar9 + 0x10),0x35)
      ;
      *(undefined1 *)(param_1 + 0x21) = uVar2;
      uVar4 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                        (*(longlong **)(param_1[0x14] + 0x10),0x36);
      *(undefined4 *)((longlong)param_1 + 0x10c) = uVar4;
      uVar4 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                        (*(longlong **)(param_1[0x14] + 0x10),0x37);
      *(undefined4 *)(param_1 + 0x22) = uVar4;
      if (((char)param_1[0x21] == '\x01') && (*(int *)((longlong)param_1 + 0x10c) != 0)) {
        *(int *)((longlong)param_1 + 0x114) = *(int *)((longlong)param_1 + 0x10c);
        uVar5 = tq::TimeGet(0);
        *(uint *)(param_1 + 0x23) = uVar5 / 1000;
      }
      *(int *)(param_1 + 0x10) = param_2;
      lVar9 = FUN_14001c790();
      lVar9 = FUN_14003ca10(lVar9,param_4);
      param_1[0x13] = lVar9;
      *(int *)((longlong)param_1 + 0x34) = param_5;
      *(int *)(param_1 + 7) = param_6;
      lVar9 = 5;
      do {
        *(undefined4 *)((longlong)param_1 + lVar9 * 4 + 0xe8) = 0;
        lVar9 = lVar9 + -1;
      } while (-1 < lVar9);
      uVar4 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                        (*(longlong **)(param_1[0x14] + 0x10),4);
      *(undefined4 *)((longlong)param_1 + 0x1c) = uVar4;
      uVar4 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                        (*(longlong **)(param_1[0x14] + 0x10),5);
      *(undefined4 *)(param_1 + 4) = uVar4;
      iVar6 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                        (*(longlong **)(param_1[0x14] + 0x10),0x12);
      iVar6 = (iVar6 * 3) / 1000;
      iVar8 = 1;
      if (0 < iVar6) {
        iVar8 = iVar6;
      }
      *(int *)(param_1 + 0x15) = iVar8;
      uVar5 = tq::TimeGet(0);
      *(uint *)((longlong)param_1 + 0xac) = uVar5 / 1000;
      uVar4 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                        (*(longlong **)(param_1[0x14] + 0x10),0x13);
      *(undefined4 *)(param_1 + 0x17) = uVar4;
      uVar5 = tq::TimeGet(0);
      *(ulong *)((longlong)param_1 + 0xbc) = uVar5;
      *(undefined4 *)(param_1 + 0x16) = 0x3c;
      uVar5 = tq::TimeGet(0);
      *(uint *)((longlong)param_1 + 0xb4) = uVar5 / 1000;
      *(int *)((longlong)param_1 + 0x8c) = param_8;
      *(undefined4 *)(param_1 + 5) = param_9;
      if (param_8 == 0) {
        *(undefined4 *)(param_1 + 5) = 0;
      }
      uVar7 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                        (*(longlong **)(param_1[0x14] + 0x10),0x15);
      if ((uVar7 >> 8 & 1) != 0) {
        *(undefined4 *)((longlong)param_1 + 0x84) = param_10;
        *(undefined4 *)(param_1 + 3) = 8;
      }
      iVar6 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                        (*(longlong **)(param_1[0x14] + 0x10),0x27);
      if (iVar6 != 0) {
        lVar9 = FUN_14001d230();
        puVar11 = FUN_140042b80(lVar9,&local_4a8,1);
        FUN_1400402d0(param_1 + 0x18,*puVar11,puVar11[1]);
        if (local_4a0 != (longlong *)0x0) {
          LOCK();
          plVar10 = local_4a0 + 2;
          *(int *)plVar10 = (int)*plVar10 + -1;
          UNLOCK();
          if ((int)*plVar10 == 0) {
            (**(code **)*local_4a0)(local_4a0);
            LOCK();
            piVar1 = (int *)((longlong)local_4a0 + 0x14);
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (*piVar1 == 0) {
              (**(code **)(*local_4a0 + 8))(local_4a0);
            }
          }
        }
      }
      if (param_1[0x13] == 0) {
        (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x18))
                  (*(longlong **)(param_1[0x14] + 0x10),1);
        log_InlineLogERROR(
                          "CNpc::Create(), Create Npc(type:%d, name:%s) can\'t find map(%u) at %s, %d"
                          );
      }
      else {
        FUN_14004ddd0(param_1[0x13],param_1 + 2);
        (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                  (*(longlong **)(param_1[0x14] + 0x10),0x15);
        if ((~extraout_AH & 1) != 0) {
          iVar6 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
          iVar8 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
          uVar12 = FUN_14004ae30(param_1[0x13],iVar8,iVar6);
          if ((char)uVar12 != '\0') {
            uVar4 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                              (*(longlong **)(param_1[0x14] + 0x10),4);
            *(undefined4 *)((longlong)param_1 + 0x1c) = uVar4;
            uVar4 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                              (*(longlong **)(param_1[0x14] + 0x10),5);
            *(undefined4 *)(param_1 + 4) = uVar4;
            *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
            *(undefined4 *)(param_1 + 3) = 0;
          }
        }
        if ((((param_7 == 0) && (param_12 != 0)) && (param_11 != 0)) && (param_14 != 0)) {
          plVar10 = FUN_14006a4c0(param_3,param_4,param_5,param_6,4,4);
          if (plVar10 == (longlong *)0x0) {
            log_InlineLogERROR(&DAT_1400be0b0);
            FUN_140063b90(local_498);
            uVar12 = FUN_140063c60((longlong)local_498,4,param_11,param_11,0,param_12,0,param_14);
            if ((int)uVar12 != 0) {
              lVar9 = FUN_14001c200();
              FUN_14001c5f0(lVar9,0,(longlong)local_498);
            }
            FUN_140063c20(local_498);
            goto LAB_14005e8d9;
          }
        }
        else {
          lVar9 = FUN_14001c7a0();
          plVar10 = (longlong *)FUN_140025b50(lVar9);
          plVar10 = (longlong *)(**(code **)(*plVar10 + 0x30))(plVar10,param_7);
          if (plVar10 == (longlong *)0x0) {
            log_InlineLogDBERROR(&DAT_1400c9620);
            goto LAB_14005e8d9;
          }
        }
        param_1[0x20] = (longlong)plVar10;
        bVar3 = FUN_14001c1c0(param_2);
        if (bVar3) {
          lVar9 = *plVar10;
          uVar4 = (**(code **)(*param_1 + 8))(param_1);
          (**(code **)(lVar9 + 0x90))(plVar10,uVar4);
        }
        else {
          lVar9 = *plVar10;
          uVar4 = (**(code **)(*param_1 + 8))(param_1);
          (**(code **)(lVar9 + 0x90))(plVar10,uVar4);
          lVar9 = FUN_14001c200();
          FUN_14001c220(lVar9);
        }
        *(int *)(param_1 + 0x25) = param_12;
        *(undefined1 *)(param_1 + 0x26) = param_13;
        *(int *)((longlong)param_1 + 300) = param_11;
        *(undefined4 *)((longlong)param_1 + 0x134) = param_15;
        if (((param_11 != 0) && (param_12 != 0)) && (param_14 != 0)) {
          FUN_14005dc80(param_1,param_14);
        }
      }
    }
  }
LAB_14005e8d9:
  __security_check_cookie(local_58 ^ (ulonglong)auStackY_4f8);
  return;
}


// ==== FUN_14005e900 @ 14005e900  undefined FUN_14005e900(longlong * param_1)

void FUN_14005e900(longlong *param_1)

{
  bool bVar1;
  char cVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined7 extraout_var;
  undefined8 uVar13;
  ulonglong uVar14;
  uint *puVar15;
  longlong lVar16;
  longlong *plVar17;
  undefined8 *puVar18;
  undefined1 auStackY_4c8 [32];
  undefined8 local_488;
  undefined8 local_480;
  undefined1 local_478 [24];
  undefined1 local_460 [24];
  undefined8 local_448 [132];
  ulonglong local_28;
  
  local_480 = 0xfffffffffffffffe;
  local_28 = DAT_140103510 ^ (ulonglong)auStackY_4c8;
  uVar6 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                    (*(longlong **)(param_1[0x14] + 0x10),0x15);
  if ((uVar6 >> 8 & 1) != 0) {
    FUN_1400623e0(local_448);
    uVar3 = (**(code **)(param_1[2] + 0x18))(param_1 + 2);
    uVar4 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
    uVar5 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
    iVar7 = (**(code **)(*param_1 + 8))(param_1);
    bVar1 = FUN_140062460((longlong)local_448,iVar7,uVar5,uVar4,uVar3,0x59,0);
    if ((int)CONCAT71(extraout_var,bVar1) == 0) {
      log_InlineLogERROR(&DAT_1400be0b0);
    }
    else {
      uVar8 = (**(code **)(*param_1 + 8))(param_1);
      lVar16 = FUN_14001c200();
      FUN_14001c5f0(lVar16,uVar8,(longlong)local_448);
    }
    FUN_140062430(local_448);
  }
  uVar13 = FUN_14005df70(param_1);
  if ((char)uVar13 != '\0') goto LAB_14005efca;
  uVar6 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                    (*(longlong **)(param_1[0x14] + 0x10),0x15);
  if ((((uVar6 >> 3 & 1) == 0) &&
      (uVar6 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                         (*(longlong **)(param_1[0x14] + 0x10),0x15), (uVar6 >> 4 & 1) == 0)) &&
     (uVar6 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))(), (uVar6 >> 0xb & 1) == 0
     )) {
    if (0 < *(int *)((longlong)param_1 + 0x2c)) {
      FUN_14005c960(param_1,0);
      goto LAB_14005efca;
    }
    uVar6 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                      (*(longlong **)(param_1[0x14] + 0x10),0x15);
    if ((uVar6 >> 7 & 1) != 0) {
      lVar16 = *(longlong *)param_1[0x20];
      uVar8 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
      uVar9 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
      cVar2 = (**(code **)(lVar16 + 0x68))(param_1[0x20],uVar9,uVar8);
      if (cVar2 == '\0') goto LAB_14005eb1c;
    }
    uVar14 = FUN_140002700((int *)(param_1 + 0x15));
    if ((char)uVar14 == '\0') goto LAB_14005efca;
  }
LAB_14005eb1c:
  *(undefined4 *)(param_1 + 0x11) = 0;
  *(undefined1 *)((longlong)param_1 + 0x3d) = 0;
  puVar15 = (uint *)(**(code **)(param_1[2] + 0x20))(param_1 + 2,local_478);
  if ((((*puVar15 >> 5 & 1) == 0) &&
      (puVar15 = (uint *)(**(code **)(param_1[2] + 0x20))(param_1 + 2,local_460),
      (*puVar15 >> 3 & 1) == 0)) && (cVar2 = FUN_14005bc80(param_1), cVar2 != '\0')) {
    lVar16 = FUN_14001c210();
    plVar17 = (longlong *)FUN_140038010(lVar16,*(int *)((longlong)param_1 + 0x84));
    if (plVar17 == (longlong *)0x0) {
      log_InlineLogERROR(&DAT_1400be0b0);
      (**(code **)(*(longlong *)param_1[0x14] + 8))();
      (**(code **)(*param_1 + 8))(param_1);
      log_InlineLogWARNING("npc: [%d][%d], target id: [%d]");
    }
    else {
      lVar16 = param_1[2];
      uVar8 = (**(code **)(*plVar17 + 0x40))(plVar17);
      uVar9 = (**(code **)(*plVar17 + 0x38))(plVar17);
      iVar7 = (**(code **)(lVar16 + 8))(param_1 + 2,uVar9,uVar8);
      lVar16 = param_1[2];
      uVar8 = (**(code **)(*plVar17 + 0x48))(plVar17);
      iVar10 = (**(code **)(lVar16 + 0x10))(param_1 + 2,uVar8);
      if (iVar7 <= iVar10) {
        FUN_140059c90(param_1);
        *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
        *(undefined4 *)(param_1 + 3) = 8;
        goto LAB_14005efca;
      }
      uVar14 = FUN_14005ad00((longlong)param_1);
      if ((char)uVar14 != '\0') {
        if (*(int *)((longlong)param_1 + 0x2c) == 0) {
          uVar6 = FUN_140057d30((longlong)param_1);
          if (((char)uVar6 != '\0') && (iVar7 = tq::RandGet(100), 0x4f < iVar7)) {
            *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
            *(undefined4 *)(param_1 + 3) = 6;
          }
        }
        else {
          *(undefined4 *)(param_1 + 3) = 7;
        }
        goto LAB_14005efca;
      }
    }
  }
  uVar6 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))();
  if ((((uVar6 >> 3 & 1) != 0) ||
      (uVar6 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))(), (uVar6 >> 4 & 1) != 0)
      ) || (uVar6 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))(),
           (uVar6 >> 0xb & 1) != 0)) {
    if (0 < *(int *)((longlong)param_1 + 0x2c)) {
      FUN_14005c960(param_1,0);
      goto LAB_14005efca;
    }
    uVar14 = FUN_140002700((int *)(param_1 + 0x15));
    if ((char)uVar14 == '\0') goto LAB_14005efca;
  }
  uVar14 = FUN_14005ad00((longlong)param_1);
  if ((char)uVar14 != '\0') {
    lVar16 = *(longlong *)param_1[0x20];
    uVar8 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
    uVar9 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
    cVar2 = (**(code **)(lVar16 + 0x68))(param_1[0x20],uVar9,uVar8);
    if (cVar2 == '\0') {
      uVar6 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                        (*(longlong **)(param_1[0x14] + 0x10),0x15);
      if ((((uVar6 >> 3 & 1) != 0) ||
          (uVar6 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                             (*(longlong **)(param_1[0x14] + 0x10),0x15), (uVar6 >> 4 & 1) != 0)) ||
         ((uVar6 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                             (*(longlong **)(param_1[0x14] + 0x10),0x15), (uVar6 >> 7 & 1) != 0 ||
          (iVar7 = tq::RandGet(5), iVar7 == 0)))) {
        puVar18 = (undefined8 *)
                  (**(code **)(*(longlong *)param_1[0x20] + 0x28))
                            ((longlong *)param_1[0x20],&local_488);
        local_488 = *puVar18;
        iVar7 = (int)local_488;
        cVar2 = FUN_1400580e0((longlong)param_1,iVar7,(int)((ulonglong)local_488 >> 0x20),0);
        if (cVar2 == '\0') {
          uVar6 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                            (*(longlong **)(param_1[0x14] + 0x10),0x15);
          if ((((uVar6 >> 3 & 1) != 0) ||
              (uVar6 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                                 (*(longlong **)(param_1[0x14] + 0x10),0x15), (uVar6 >> 4 & 1) != 0)
              ) || (uVar6 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                                      (*(longlong **)(param_1[0x14] + 0x10),0x15),
                   (uVar6 >> 5 & 1) != 0)) {
            uVar8 = (**(code **)(param_1[2] + 0x18))(param_1 + 2);
            FUN_140059f40(param_1,iVar7,local_488._4_4_,uVar8);
          }
        }
        else {
          FUN_14005c960(param_1,0);
        }
      }
    }
    else {
      uVar6 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                        (*(longlong **)(param_1[0x14] + 0x10),0x15);
      if ((((uVar6 >> 3 & 1) == 0) &&
          (uVar6 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                             (*(longlong **)(param_1[0x14] + 0x10),0x15), (uVar6 >> 4 & 1) == 0)) &&
         (uVar6 = (**(code **)(**(longlong **)(param_1[0x14] + 0x10) + 0x10))
                            (*(longlong **)(param_1[0x14] + 0x10),0x15), (uVar6 >> 0xb & 1) == 0)) {
        iVar7 = tq::RandGet(5);
        if (iVar7 == 0) {
          uVar6 = tq::RandGet(8);
          uVar13 = FUN_140058500((longlong)param_1,uVar6);
          if ((char)uVar13 != '\0') {
            FUN_14005c960(param_1,0);
          }
        }
      }
      else {
        iVar7 = tq::RandGet(5);
        if (((iVar7 == 0) && (iVar7 = (**(code **)(*(longlong *)param_1[0x20] + 0x60))(), 1 < iVar7)
            ) || (iVar7 = (**(code **)(*(longlong *)param_1[0x20] + 0x38))(), 1 < iVar7)) {
          plVar17 = (longlong *)param_1[0x20];
          iVar7 = (**(code **)(*plVar17 + 0x60))(plVar17);
          iVar7 = tq::RandGet(iVar7);
          iVar10 = (**(code **)(*plVar17 + 0x50))(plVar17);
          plVar17 = (longlong *)param_1[0x20];
          iVar11 = (**(code **)(*plVar17 + 0x38))(plVar17);
          iVar11 = tq::RandGet(iVar11);
          iVar12 = (**(code **)(*plVar17 + 0x58))(plVar17);
          cVar2 = FUN_1400580e0((longlong)param_1,iVar7 + iVar10,iVar12 + iVar11,0);
          if (cVar2 != '\0') {
            FUN_14005c960(param_1,0);
          }
        }
      }
    }
  }
LAB_14005efca:
  __security_check_cookie(local_28 ^ (ulonglong)auStackY_4c8);
  return;
}


// ==== FUN_14005f000 @ 14005f000  undefined FUN_14005f000(longlong param_1, undefined4 param_2)

void FUN_14005f000(longlong param_1,undefined4 param_2)

{
  undefined4 local_res10 [6];
  
  local_res10[0] = param_2;
  FUN_14005e230(param_1,local_res10);
  return;
}


// ==== FUN_14005f020 @ 14005f020  undefined FUN_14005f020(longlong * param_1)

void FUN_14005f020(longlong *param_1)

{
  bool bVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  longlong lVar5;
  longlong *plVar6;
  undefined4 local_res10 [2];
  
  if ((int)param_1[0x23] != 0) {
    *(undefined4 *)(param_1 + 0x23) = 0;
    *(undefined4 *)((longlong)param_1 + 0x114) = 0;
  }
  if (param_1[0x13] != 0) {
    FUN_14004c900(param_1[0x13],param_1 + 2);
  }
  if (param_1[0x20] == 0) goto LAB_14005f130;
  uVar2 = (**(code **)(*param_1 + 8))(param_1);
  if (uVar2 < 0x61a82) {
LAB_14005f0c3:
    uVar2 = (**(code **)(*param_1 + 8))(param_1);
    if (0x7a121 < uVar2) {
      uVar2 = (**(code **)(*param_1 + 8))(param_1);
      if (uVar2 < 599999) {
        lVar5 = FUN_14001c200();
        FUN_14001c230(lVar5);
      }
    }
  }
  else {
    uVar2 = (**(code **)(*param_1 + 8))(param_1);
    if (0x7a11e < uVar2) goto LAB_14005f0c3;
    local_res10[0] = (**(code **)(*param_1 + 8))(param_1);
    lVar5 = FUN_14001c7a0();
    lVar5 = FUN_140025c20(lVar5);
    FUN_14005e230(lVar5,local_res10);
  }
  bVar1 = FUN_14001c1c0((int)param_1[0x10]);
  if ((bVar1) || (((int)param_1[0x25] != 0 && (*(int *)((longlong)param_1 + 300) != 0)))) {
    lVar5 = *(longlong *)param_1[0x20];
    uVar3 = (**(code **)(*param_1 + 8))(param_1);
    (**(code **)(lVar5 + 0x78))(param_1[0x20],uVar3);
  }
LAB_14005f130:
  if (((int)param_1[0x25] != 0) && (*(int *)((longlong)param_1 + 300) != 0)) {
    FUN_14005df30((longlong)param_1);
    if (param_1[0x20] != 0) {
      iVar4 = (**(code **)(*(longlong *)param_1[0x20] + 0x20))();
      if (iVar4 == 0) {
        lVar5 = FUN_14001c7a0();
        plVar6 = (longlong *)FUN_140025ba0(lVar5);
        lVar5 = *plVar6;
        uVar3 = (**(code **)(*(longlong *)param_1[0x20] + 8))();
        (**(code **)(lVar5 + 0x28))(plVar6,uVar3);
      }
    }
  }
  FUN_14005da00((longlong)param_1);
  return;
}


// ==== FUN_14005f1b0 @ 14005f1b0  undefined8 FUN_14005f1b0(longlong param_1, longlong * param_2)

undefined8 FUN_14005f1b0(longlong param_1,longlong *param_2)

{
  longlong lVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  longlong lVar7;
  longlong *plVar8;
  undefined6 extraout_var;
  undefined8 uVar9;
  double local_res8;
  
  lVar7 = FUN_14001c210();
  plVar8 = (longlong *)FUN_140038010(lVar7,*(int *)(param_1 + 0x84));
  if (plVar8 == (longlong *)0x0) {
    return 0;
  }
  FUN_140043a50(param_2);
  lVar7 = (**(code **)(*plVar8 + 0xb0))(plVar8,0x1001,0);
  if (lVar7 == 0) {
    lVar7 = (**(code **)(*plVar8 + 0xb0))(plVar8,0x1040,0);
    if (lVar7 == 0) {
      return 0;
    }
    plVar8 = *(longlong **)(*(longlong *)(lVar7 + 0xa0) + 0x10);
    iVar3 = (**(code **)(*plVar8 + 0x10))(plVar8,0x14);
    local_res8 = (double)iVar3 / 140.0;
    FUN_140044700(param_2,&local_res8);
    plVar8 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
  }
  else {
    uVar2 = FUN_140065e20(lVar7);
    local_res8 = (double)(CONCAT62(extraout_var,uVar2) & 0xffffffff) / 140.0;
    FUN_140044700(param_2,&local_res8);
    plVar8 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
  }
  iVar3 = (**(code **)(*plVar8 + 0x10))(plVar8,7);
  local_res8 = (double)iVar3 / 10000.0;
  FUN_140044700(param_2,&local_res8);
  plVar8 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
  iVar3 = (**(code **)(*plVar8 + 0x10))(plVar8,4);
  local_res8 = (double)*(int *)(param_1 + 0x1c) / (double)iVar3;
  FUN_140044700(param_2,&local_res8);
  plVar8 = *(longlong **)(*(longlong *)(param_1 + 0xa0) + 0x10);
  iVar3 = (**(code **)(*plVar8 + 0x10))(plVar8,0x10);
  lVar1 = *(longlong *)(param_1 + 0x10);
  uVar4 = (**(code **)(*(longlong *)(lVar7 + 0x10) + 0x40))(lVar7 + 0x10);
  uVar5 = (**(code **)(*(longlong *)(lVar7 + 0x10) + 0x38))(lVar7 + 0x10);
  iVar6 = (**(code **)(lVar1 + 8))(param_1 + 0x10,uVar5,uVar4);
  local_res8 = (double)iVar6 / (double)iVar3;
  uVar9 = FUN_140044700(param_2,&local_res8);
  return CONCAT71((int7)((ulonglong)uVar9 >> 8),1);
}


// ==== FUN_14005f3b0 @ 14005f3b0  undefined FUN_14005f3b0(longlong * param_1)

void FUN_14005f3b0(longlong *param_1)

{
  int iVar1;
  char cVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  int iVar5;
  
  uVar3 = FUN_14005b5c0((longlong)param_1);
  if ((((char)uVar3 == '\0') &&
      (cVar2 = (**(code **)(param_1[2] + 0x50))(param_1 + 2), cVar2 != '\0')) &&
     ((char)param_1[0x29] == '\0')) {
    FUN_140058860((longlong)param_1);
    iVar5 = 0;
    do {
      iVar1 = (int)param_1[3];
      if (iVar1 == 1) {
        cVar2 = FUN_14005e900(param_1);
joined_r0x00014005f43b:
        if (cVar2 != '\0') {
          return;
        }
      }
      else {
        if (iVar1 == 6) {
          uVar4 = FUN_14005d140(param_1);
          cVar2 = (char)uVar4;
          goto joined_r0x00014005f43b;
        }
        if (iVar1 == 7) {
          uVar4 = FUN_14005d550(param_1);
          cVar2 = (char)uVar4;
          goto joined_r0x00014005f43b;
        }
        if (iVar1 == 8) {
          uVar4 = FUN_14005d330(param_1);
          cVar2 = (char)uVar4;
          goto joined_r0x00014005f43b;
        }
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < 10);
  }
  return;
}


// ==== FUN_14005f480 @ 14005f480  undefined FUN_14005f480(undefined8 * param_1)

void FUN_14005f480(undefined8 *param_1)

{
  *param_1 = IGenerator::vftable;
  FUN_1400695e0(param_1);
  return;
}


// ==== FUN_14005f4b0 @ 14005f4b0  undefined8 * FUN_14005f4b0(undefined8 * param_1)

undefined8 * FUN_14005f4b0(undefined8 *param_1)

{
  FUN_1400695c0(param_1);
  *param_1 = IGenerator::vftable;
  return param_1;
}


// ==== FUN_14005f720 @ 14005f720  undefined8 FUN_14005f720(undefined8 param_1)

undefined8 FUN_14005f720(undefined8 param_1)

{
  return param_1;
}


// ==== FUN_14005f730 @ 14005f730  bool FUN_14005f730(uint param_1, uint param_2)

bool FUN_14005f730(uint param_1,uint param_2)

{
  return (param_1 >> (param_2 & 0x1f) & 1) != 0;
}


// ==== FUN_14005f740 @ 14005f740  bool FUN_14005f740(longlong param_1, uint param_2)

bool FUN_14005f740(longlong param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),0x12)
  ;
  return (uVar1 >> (param_2 & 0x1f) & 1) != 0;
}


// ==== FUN_14005f770 @ 14005f770  uint FUN_14005f770(longlong param_1)

uint FUN_14005f770(longlong param_1)

{
  uint uVar1;
  
  uVar1 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),0x12)
  ;
  return uVar1 & 1;
}


// ==== FUN_14005f7e0 @ 14005f7e0  undefined8 FUN_14005f7e0(longlong param_1)

undefined8 FUN_14005f7e0(longlong param_1)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if (*(longlong *)(param_1 + 0x40) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return 0;
  }
  iVar5 = 0;
  iVar6 = 0;
  iVar1 = tq::RandGet(100);
  iVar4 = 2;
  do {
    if (0x15 < iVar4) goto LAB_14005f888;
    iVar2 = (**(code **)(**(longlong **)(param_1 + 0x40) + 0x10))
                      (*(longlong **)(param_1 + 0x40),iVar4);
    iVar5 = iVar5 + iVar2;
    if (iVar1 < iVar5) break;
    iVar6 = iVar6 + 1;
    iVar4 = iVar4 + 2;
  } while (iVar5 < 100);
  if (iVar6 < 10) {
    uVar3 = (**(code **)(**(longlong **)(param_1 + 0x40) + 0x10))
                      (*(longlong **)(param_1 + 0x40),iVar6 * 2 + 1);
  }
  else {
LAB_14005f888:
    uVar3 = 0;
  }
  return uVar3;
}


// ==== FUN_14005f9d0 @ 14005f9d0  undefined8 FUN_14005f9d0(longlong param_1, longlong * param_2, int param_3)

ulonglong FUN_14005f9d0(longlong param_1,longlong *param_2,int param_3)

{
  ulonglong in_RAX;
  ulonglong extraout_RAX;
  longlong *plVar1;
  undefined8 uVar2;
  
  if (*(char *)(param_1 + 0x10) == '\0') {
    *(longlong **)(param_1 + 8) = param_2;
    if (param_2 != (longlong *)0x0) {
      plVar1 = (longlong *)(**(code **)(*param_2 + 0x20))(param_2,&DAT_140102d90);
      uVar2 = (**(code **)(*plVar1 + 0x40))(plVar1);
      if ((int)uVar2 != param_3) {
        plVar1 = (longlong *)
                 (**(code **)(**(longlong **)(param_1 + 8) + 0x20))
                           (*(longlong **)(param_1 + 8),&DAT_140102d90);
        uVar2 = (**(code **)(*plVar1 + 0xb8))(plVar1,param_3);
      }
      return CONCAT71((int7)((ulonglong)uVar2 >> 8),1);
    }
  }
  else {
    log_InlineLogERROR(&DAT_1400be0b0);
    in_RAX = extraout_RAX;
  }
  return in_RAX & 0xffffffffffffff00;
}


// ==== FUN_14005fa80 @ 14005fa80  undefined FUN_14005fa80(longlong param_1)

void FUN_14005fa80(longlong param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)
           (**(code **)(**(longlong **)(param_1 + 8) + 0x20))
                     (*(longlong **)(param_1 + 8),&DAT_140102d90);
                    /* WARNING: Could not recover jumptable at 0x00014005fa9f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x40))(plVar1);
  return;
}


// ==== FUN_14005fab0 @ 14005fab0  undefined FUN_14005fab0(undefined8 * param_1)

/* WARNING: Restarted to delay deadcode elimination for space: register */

void FUN_14005fab0(undefined8 *param_1)

{
  *param_1 = CNpcGenerator::vftable;
  tq::MyLogSave("gmlog/npc_generator","generator:%-9u, monster:%-9d",*(undefined4 *)(param_1 + 10),
                *(undefined4 *)(param_1 + 4));
  if ((longlong *)param_1[7] != (longlong *)0x0) {
    (**(code **)(*(longlong *)param_1[7] + 0x58))();
  }
  if ((longlong *)param_1[8] != (longlong *)0x0) {
    (**(code **)(*(longlong *)param_1[8] + 0x58))();
  }
  *param_1 = IGenerator::vftable;
  FUN_1400695e0(param_1);
  return;
}


// ==== FUN_14005fbc0 @ 14005fbc0  int * FUN_14005fbc0(longlong param_1, int * param_2)

int * FUN_14005fbc0(longlong param_1,int *param_2)

{
  longlong *plVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),0xc);
  if (iVar2 < 1) {
    iVar2 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),2);
    iVar3 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),4);
    iVar3 = tq::RandGet(iVar3);
    plVar1 = *(longlong **)(param_1 + 0x38);
    *param_2 = iVar3 + iVar2;
    iVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,3);
    iVar3 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),5);
    iVar3 = tq::RandGet(iVar3);
    param_2[1] = iVar3 + iVar2;
    return param_2;
  }
  iVar2 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),0xc);
  plVar1 = *(longlong **)(param_1 + 0x38);
  *param_2 = iVar2;
  iVar2 = (**(code **)(*plVar1 + 0x10))(plVar1,0xd);
  param_2[1] = iVar2;
  return param_2;
}


// ==== FUN_14005fc90 @ 14005fc90  undefined FUN_14005fc90(longlong * param_1, int param_2)

void FUN_14005fc90(longlong *param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  ulong uVar10;
  uint uVar11;
  undefined8 uVar12;
  uint *puVar13;
  longlong lVar14;
  undefined2 uVar15;
  undefined1 auStack_4e8 [32];
  undefined4 local_4c8;
  undefined4 uStack_4c4;
  int local_4c0;
  int local_4bc;
  uint local_4b8;
  undefined4 local_4b4;
  undefined4 local_4b0;
  undefined4 local_4ac;
  undefined4 local_4a8;
  undefined2 local_4a4;
  undefined2 local_4a2;
  undefined2 local_4a0;
  undefined2 local_49e;
  undefined2 local_49c;
  undefined4 local_498;
  undefined4 local_494;
  undefined4 local_490;
  undefined1 local_48c;
  undefined4 local_488;
  undefined4 local_484;
  CTickAnalyst local_480 [24];
  undefined8 local_468;
  undefined8 local_458 [132];
  ulonglong local_38;
  
  local_468 = 0xfffffffffffffffe;
  local_38 = DAT_140103510 ^ (ulonglong)auStack_4e8;
  local_4bc = param_2;
  CTickAnalyst::CTickAnalyst(local_480,0x53);
  if (param_1[5] == 0) {
    CTickAnalyst::~CTickAnalyst(local_480);
  }
  else if ((int)param_1[9] == 0) {
    iVar4 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],4);
    iVar5 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],5);
    iVar1 = iVar5 * iVar4;
    if (iVar5 * iVar4 < 1) {
      iVar1 = 1;
    }
    iVar4 = 0;
    local_4c0 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],9);
    bVar2 = false;
    if (0 < param_2) {
      while (iVar5 = 0, 0 < *(int *)((longlong)param_1 + 0x14)) {
        if (iVar1 < 1) {
LAB_14005ffa2:
          if (((iVar4 < 1) && (8 < iVar1)) && (!bVar2)) {
            uVar10 = tq::TimeGet(0);
            if (999 < uVar10 - *(int *)((longlong)param_1 + 0x24)) {
              *(ulong *)((longlong)param_1 + 0x24) = uVar10;
              uVar11 = (**(code **)(*param_1 + 8))(param_1);
              log_InlineLogDBERROR(&DAT_1400c9af0,(ulonglong)uVar11);
            }
          }
          break;
        }
        while( true ) {
          iVar6 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],0xc);
          if (iVar6 < 1) {
            iVar6 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],2);
            iVar7 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],4);
            iVar7 = tq::RandGet(iVar7);
            iVar6 = iVar6 + iVar7;
            local_4c8 = iVar6;
            iVar7 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],3);
            iVar8 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],5);
            iVar8 = tq::RandGet(iVar8);
            iVar7 = iVar7 + iVar8;
          }
          else {
            iVar6 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],0xc);
            local_4c8._0_2_ = (undefined2)iVar6;
            local_4c8._2_2_ = (undefined2)((uint)iVar6 >> 0x10);
            iVar7 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],0xd);
          }
          uStack_4c4 = iVar7;
          uVar9 = FUN_14004cc70(param_1[5],iVar6,iVar7);
          if ((char)uVar9 != '\0') break;
          if (!bVar2) {
            bVar3 = FUN_140049310(param_1[5],iVar6,iVar7);
            if (bVar3) {
              bVar2 = true;
            }
          }
          iVar5 = iVar5 + 1;
          if (iVar1 <= iVar5) goto LAB_14005ffa2;
        }
        if (iVar1 <= iVar5) goto LAB_14005ffa2;
        if (param_1[8] == 0) {
          uVar15 = (undefined2)local_4c0;
        }
        else {
          uVar12 = FUN_14005f7e0((longlong)param_1);
          local_4c0 = (int)uVar12;
          uVar15 = (undefined2)uVar12;
          if (local_4c0 == 0) {
            CTickAnalyst::~CTickAnalyst(local_480);
            goto LAB_14005fff1;
          }
        }
        puVar13 = (uint *)FUN_14001c7a0();
        local_4b8 = FUN_14002b270(puVar13);
        local_4b4 = (**(code **)(*param_1 + 0x40))(param_1);
        local_4b0 = (**(code **)(*param_1 + 8))(param_1);
        local_4ac = 0;
        local_4a8 = 0;
        local_4a4 = (undefined2)local_4c8;
        local_4a2 = (undefined2)uStack_4c4;
        local_4a0 = 1;
        local_49c = 0;
        local_498 = 0;
        local_494 = 0;
        local_490 = 0;
        local_48c = *(undefined1 *)((longlong)param_1 + 0x4c);
        local_488 = 0;
        local_484 = 0;
        local_49e = uVar15;
        FUN_140061220(local_458);
        uVar12 = FUN_1400613a0((longlong)local_458,&local_4b8);
        if ((int)uVar12 != 0) {
          *(int *)((longlong)param_1 + 0x14) = *(int *)((longlong)param_1 + 0x14) + -1;
          *(int *)(param_1 + 3) = (int)param_1[3] + 1;
          *(int *)(param_1 + 4) = (int)param_1[4] + 1;
          iVar4 = iVar4 + 1;
          lVar14 = FUN_14001c200();
          FUN_14001c5f0(lVar14,0,(longlong)local_458);
        }
        FUN_140061270(local_458);
        if (local_4bc <= iVar4) break;
      }
    }
    CTickAnalyst::~CTickAnalyst(local_480);
  }
  else {
    CTickAnalyst::~CTickAnalyst(local_480);
  }
LAB_14005fff1:
  __security_check_cookie(local_38 ^ (ulonglong)auStack_4e8);
  return;
}


// ==== FUN_140060150 @ 140060150  undefined8 * FUN_140060150(undefined8 * param_1, undefined1 param_2)

undefined8 * FUN_140060150(undefined8 *param_1,undefined1 param_2)

{
  *param_1 = IGameData::vftable;
  *param_1 = CGameData<&char*_szGenerator,&char*_szID>::vftable;
  *(undefined1 *)(param_1 + 2) = param_2;
  param_1[1] = 0;
  return param_1;
}


// ==== FUN_140060190 @ 140060190  undefined FUN_140060190(undefined8 * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_140060190(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 *puVar1;
  
  *param_1 = CGameData<&char*_szGenerator,&char*_szID>::vftable;
  puVar1 = (undefined8 *)param_1[1];
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,*(char *)(param_1 + 2) == '\0',param_3,param_4,0xfffffffffffffffe);
  }
  *param_1 = IGameData::vftable;
  return;
}


// ==== FUN_140060610 @ 140060610  undefined8 * FUN_140060610(undefined8 * param_1, undefined1 param_2)

undefined8 * FUN_140060610(undefined8 *param_1,undefined1 param_2)

{
  *param_1 = IGameData::vftable;
  *param_1 = CGameData<&char*_szMonsterClusterTable,&char*_szID>::vftable;
  *(undefined1 *)(param_1 + 2) = param_2;
  param_1[1] = 0;
  return param_1;
}


// ==== FUN_140060650 @ 140060650  undefined FUN_140060650(undefined8 * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_140060650(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 *puVar1;
  
  *param_1 = CGameData<&char*_szMonsterClusterTable,&char*_szID>::vftable;
  puVar1 = (undefined8 *)param_1[1];
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,*(char *)(param_1 + 2) == '\0',param_3,param_4,0xfffffffffffffffe);
  }
  *param_1 = IGameData::vftable;
  return;
}


// ==== FUN_140060860 @ 140060860  bool FUN_140060860(longlong param_1, longlong * param_2)

bool FUN_140060860(longlong param_1,longlong *param_2)

{
  longlong lVar1;
  
  if (*(char *)(param_1 + 0x10) != '\0') {
    log_InlineLogERROR(&DAT_1400be0b0);
    return false;
  }
  lVar1 = (**(code **)(*param_2 + 0x38))(param_2);
  *(longlong *)(param_1 + 8) = lVar1;
  return lVar1 != 0;
}


// ==== FUN_1400608c0 @ 1400608c0  bool FUN_1400608c0(longlong param_1, undefined8 param_2)

bool FUN_1400608c0(longlong param_1,undefined8 param_2)

{
  longlong *plVar1;
  longlong lVar2;
  
  plVar1 = (longlong *)InstanceGet();
  lVar2 = (**(code **)(*plVar1 + 0x20))(plVar1,param_2);
  *(longlong *)(param_1 + 8) = lVar2;
  return lVar2 != 0;
}


// ==== FUN_140060900 @ 140060900  bool FUN_140060900(longlong param_1)

bool FUN_140060900(longlong param_1)

{
  longlong *plVar1;
  longlong lVar2;
  
  plVar1 = (longlong *)InstanceGet();
  lVar2 = (**(code **)(*plVar1 + 0x20))(plVar1,s_cq_monster_cluster_140102f68);
  *(longlong *)(param_1 + 8) = lVar2;
  return lVar2 != 0;
}


// ==== FUN_140060930 @ 140060930  ulonglong FUN_140060930(longlong param_1)

ulonglong FUN_140060930(longlong param_1)

{
  ulonglong extraout_RAX;
  ulonglong uVar1;
  
  if (*(char *)(param_1 + 0x10) != '\0') {
    log_InlineLogERROR(&DAT_1400be0b0);
    return extraout_RAX & 0xffffffffffffff00;
  }
                    /* WARNING: Could not recover jumptable at 0x000140060976. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (**(code **)(**(longlong **)(param_1 + 8) + 0x40))();
  return uVar1;
}


// ==== FUN_140060980 @ 140060980  undefined FUN_140060980(longlong param_1)

void FUN_140060980(longlong param_1)

{
  longlong *plVar1;
  
  (**(code **)(**(longlong **)(param_1 + 8) + 0x50))(*(longlong **)(param_1 + 8),1);
  plVar1 = (longlong *)
           (**(code **)(**(longlong **)(param_1 + 8) + 0x20))
                     (*(longlong **)(param_1 + 8),&DAT_140102d90);
                    /* WARNING: Could not recover jumptable at 0x0001400609b1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x40))(plVar1);
  return;
}


// ==== FUN_1400609c0 @ 1400609c0  undefined FUN_1400609c0(undefined8 * param_1)

void FUN_1400609c0(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    (**(code **)*param_1)(param_1,1);
  }
  return;
}


// ==== FUN_1400609e0 @ 1400609e0  undefined FUN_1400609e0(longlong param_1, undefined8 param_2, undefined4 param_3)

void FUN_1400609e0(longlong param_1,undefined8 param_2,undefined4 param_3)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(**(code **)(**(longlong **)(param_1 + 8) + 0x10))();
                    /* WARNING: Could not recover jumptable at 0x000140060a00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0xb0))(plVar1,param_3);
  return;
}


// ==== FUN_140060a10 @ 140060a10  undefined FUN_140060a10(longlong param_1, undefined8 param_2, undefined8 param_3)

void FUN_140060a10(longlong param_1,undefined8 param_2,undefined8 param_3)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(**(code **)(**(longlong **)(param_1 + 8) + 0x10))();
                    /* WARNING: Could not recover jumptable at 0x000140060a31. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x80))(plVar1,param_3);
  return;
}


// ==== FUN_140060a40 @ 140060a40  undefined8 FUN_140060a40(longlong param_1)

undefined8 FUN_140060a40(longlong param_1)

{
  undefined8 in_RAX;
  undefined8 uVar1;
  
  if (*(char *)(param_1 + 0x10) == '\0') {
                    /* WARNING: Could not recover jumptable at 0x000140060a4f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(**(longlong **)(param_1 + 8) + 0x38))(*(longlong **)(param_1 + 8),0);
    return uVar1;
  }
  return CONCAT71((int7)((ulonglong)in_RAX >> 8),1);
}


// ==== FUN_140060cc0 @ 140060cc0  undefined8 * FUN_140060cc0(undefined1 param_1)

undefined8 * FUN_140060cc0(undefined1 param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x18);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = IGameData::vftable;
    *puVar1 = CGameData<&char*_szGenerator,&char*_szID>::vftable;
    *(undefined1 *)(puVar1 + 2) = param_1;
    puVar1[1] = 0;
  }
  return puVar1;
}


// ==== FUN_140060d10 @ 140060d10  undefined8 * FUN_140060d10(undefined1 param_1)

undefined8 * FUN_140060d10(undefined1 param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x18);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = IGameData::vftable;
    *puVar1 = CGameData<&char*_szMonsterClusterTable,&char*_szID>::vftable;
    *(undefined1 *)(puVar1 + 2) = param_1;
    puVar1[1] = 0;
  }
  return puVar1;
}


// ==== FUN_140060d60 @ 140060d60  undefined8 * FUN_140060d60(undefined8 * param_1)

undefined8 * FUN_140060d60(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  FUN_1400695c0(param_1);
  *param_1 = IGenerator::vftable;
  *param_1 = CNpcGenerator::vftable;
  puVar2 = (undefined8 *)0x0;
  *(undefined4 *)(param_1 + 6) = 0;
  *(undefined4 *)((longlong)param_1 + 0x34) = 0;
  param_1[8] = 0;
  *(undefined4 *)(param_1 + 9) = 0;
  *(undefined1 *)((longlong)param_1 + 0x4c) = 0;
  *(undefined4 *)(param_1 + 10) = 0;
  *(undefined4 *)((longlong)param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 3) = 0;
  *(undefined4 *)((longlong)param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)((longlong)param_1 + 0x24) = 0;
  param_1[5] = 0;
  CGameMap::vf_0x18((longlong)param_1,0x2000);
  puVar1 = (undefined8 *)operator_new(0x18);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = IGameData::vftable;
    *puVar1 = CGameData<&char*_szGenerator,&char*_szID>::vftable;
    *(undefined1 *)(puVar1 + 2) = 0;
    puVar1[1] = 0;
    puVar2 = puVar1;
  }
  param_1[7] = puVar2;
  return param_1;
}


// ==== FUN_140060e20 @ 140060e20  undefined8 * FUN_140060e20(void)

undefined8 * FUN_140060e20(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x58);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    puVar1 = FUN_140060d60(puVar1);
  }
  return puVar1;
}


// ==== FUN_140060e60 @ 140060e60  undefined FUN_140060e60(longlong param_1)

void FUN_140060e60(longlong param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined8 *puVar3;
  longlong *plVar4;
  longlong lVar5;
  undefined1 auStack_98 [32];
  undefined4 local_78;
  undefined8 *local_68;
  undefined8 local_60;
  char local_58 [64];
  ulonglong local_18;
  
  local_60 = 0xfffffffffffffffe;
  local_18 = DAT_140103510 ^ (ulonglong)auStack_98;
  iVar1 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),0x11)
  ;
  if (iVar1 != 0) {
    uVar2 = (**(code **)(**(longlong **)(param_1 + 0x38) + 0x10))(*(longlong **)(param_1 + 0x38),9);
    local_68 = (undefined8 *)operator_new(0x18);
    if (local_68 == (undefined8 *)0x0) {
      puVar3 = (undefined8 *)0x0;
    }
    else {
      *local_68 = IGameData::vftable;
      *local_68 = CGameData<&char*_szMonsterClusterTable,&char*_szID>::vftable;
      *(undefined1 *)(local_68 + 2) = 0;
      local_68[1] = 0;
      puVar3 = local_68;
    }
    *(undefined8 **)(param_1 + 0x40) = puVar3;
    if (puVar3 == (undefined8 *)0x0) {
      local_78 = 0x1d8;
      log_InlineLogERROR(&DAT_1400be0b0);
    }
    else {
      local_78 = uVar2;
      _snprintf(local_58,0x40,"SELECT * FROM %s WHERE id = %d LIMIT 1");
      plVar4 = (longlong *)InstanceGet();
      plVar4 = (longlong *)(**(code **)(*plVar4 + 0x10))(plVar4,local_58,2);
      if (plVar4 == (longlong *)0x0) {
        local_78 = 0x1e2;
        log_InlineLogERROR(&DAT_1400be0b0);
        (**(code **)(**(longlong **)(param_1 + 0x40) + 0x58))();
        *(undefined8 *)(param_1 + 0x40) = 0;
      }
      else {
        lVar5 = (**(code **)(*plVar4 + 0x40))(plVar4);
        if (lVar5 == 0) {
          local_78 = 0x1ea;
          log_InlineLogERROR(&DAT_1400be0b0);
          (**(code **)(**(longlong **)(param_1 + 0x40) + 0x58))();
          *(undefined8 *)(param_1 + 0x40) = 0;
          (**(code **)*plVar4)(plVar4);
        }
        else {
          (**(code **)(**(longlong **)(param_1 + 0x40) + 0x30))
                    (*(longlong **)(param_1 + 0x40),plVar4);
          (**(code **)*plVar4)(plVar4);
        }
      }
    }
  }
  __security_check_cookie(local_18 ^ (ulonglong)auStack_98);
  return;
}


// ==== FUN_140061040 @ 140061040  undefined8 FUN_140061040(longlong * param_1, longlong * param_2, int param_3)

ulonglong FUN_140061040(longlong *param_1,longlong *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  ulong uVar3;
  int iVar4;
  undefined4 uVar5;
  longlong *plVar6;
  ulonglong uVar7;
  longlong lVar8;
  ulonglong extraout_RAX;
  undefined8 uVar9;
  
  plVar6 = (longlong *)(**(code **)(*param_2 + 0x28))(param_2);
  iVar1 = (**(code **)(*plVar6 + 0x40))(plVar6);
  uVar7 = FUN_14005f9d0(param_1[7],param_2,iVar1);
  if ((char)uVar7 == '\0') goto LAB_1400611cb;
  uVar7 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],0x12);
  if ((uVar7 & 1) == 0) {
    plVar6 = (longlong *)
             (**(code **)(**(longlong **)(param_1[7] + 8) + 0x20))
                       (*(longlong **)(param_1[7] + 8),&DAT_140102d90);
    uVar5 = (**(code **)(*plVar6 + 0x40))(plVar6);
    *(undefined4 *)(param_1 + 10) = uVar5;
    uVar5 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],1);
    *(undefined4 *)((longlong)param_1 + 0x54) = uVar5;
  }
  else {
    if (param_3 == 0) goto LAB_1400611cb;
    lVar8 = FUN_14001c7a0();
    iVar1 = FUN_14002b2d0(lVar8);
    *(int *)((longlong)param_1 + 0x54) = param_3;
    *(int *)(param_1 + 10) = iVar1;
  }
  iVar1 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],7);
  iVar2 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],7);
  iVar2 = tq::RandGet(iVar2);
  *(int *)(param_1 + 6) = iVar2 + iVar1;
  uVar3 = tq::TimeGet(0);
  *(uint *)((longlong)param_1 + 0x34) = uVar3 / 1000;
  iVar1 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],8);
  if (iVar1 == 0) {
    *(undefined4 *)((longlong)param_1 + 0x1c) = 0;
  }
  else {
    iVar1 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],6);
    if (0 < iVar1) {
      iVar2 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],4);
      iVar4 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],5);
      iVar1 = (iVar4 / iVar1) * (iVar2 / iVar1);
      *(int *)((longlong)param_1 + 0x1c) = iVar1;
      if (0 < iVar1) goto LAB_140061196;
    }
    *(undefined4 *)((longlong)param_1 + 0x1c) = 1;
  }
LAB_140061196:
  lVar8 = FUN_14001c790();
  lVar8 = FUN_14003ca10(lVar8,*(int *)((longlong)param_1 + 0x54));
  param_1[5] = lVar8;
  if (lVar8 != 0) {
    FUN_140060e60((longlong)param_1);
    uVar5 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],0xf);
    *(undefined4 *)(param_1 + 9) = uVar5;
    uVar9 = (**(code **)(*(longlong *)param_1[7] + 0x10))((longlong *)param_1[7],0x10);
    *(char *)((longlong)param_1 + 0x4c) = (char)uVar9;
    return CONCAT71((int7)((ulonglong)uVar9 >> 8),1);
  }
  (**(code **)(*param_1 + 8))();
  log_InlineLogERROR("Error: npc generator [%u] got invalid map [%u]!");
  uVar7 = extraout_RAX;
LAB_1400611cb:
  return uVar7 & 0xffffffffffffff00;
}


// ==== FUN_140061220 @ 140061220  undefined8 * FUN_140061220(undefined8 * param_1)

undefined8 * FUN_140061220(undefined8 *param_1)

{
  FUN_140034920(param_1);
  *param_1 = CMsgAiNpcInfo::vftable;
  FUN_140034820((longlong)param_1);
  param_1[0x83] = param_1 + 2;
  return param_1;
}


// ==== FUN_140061270 @ 140061270  undefined FUN_140061270(undefined8 * param_1)

void FUN_140061270(undefined8 *param_1)

{
  *param_1 = CMsgAiNpcInfo::vftable;
  FUN_140034810(param_1);
  return;
}


// ==== FUN_1400612a0 @ 1400612a0  undefined8 FUN_1400612a0(longlong param_1, int param_2, undefined4 param_3, undefined4 param_4, undefined2 param_5, undefined4 param_6, undefined2 param_7, undefined2 param_8, undefined4 param_9, undefined4 param_10, undefined1 param_11, undefined4 param_12, undefined4 param_13)

undefined8
FUN_1400612a0(longlong param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined2 param_5,
             undefined4 param_6,undefined2 param_7,undefined2 param_8,undefined4 param_9,
             undefined4 param_10,undefined1 param_11,undefined4 param_12,undefined4 param_13)

{
  undefined4 *puVar1;
  
  if (param_2 != 1) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return 0;
  }
  FUN_140034820(param_1);
  puVar1 = *(undefined4 **)(param_1 + 0x418);
  *(undefined4 *)(param_1 + 0xc) = 0x38;
  *(undefined4 *)(param_1 + 8) = 0x4e21;
  *(undefined2 *)((longlong)puVar1 + 0x1a) = param_5;
  puVar1[3] = 0;
  *(undefined2 *)(puVar1 + 7) = 0;
  puVar1[4] = 0;
  puVar1[1] = param_6;
  puVar1[8] = param_9;
  *(undefined2 *)(puVar1 + 5) = param_7;
  puVar1[9] = param_10;
  puVar1[10] = param_12;
  *(undefined1 *)(puVar1 + 0xb) = param_11;
  *puVar1 = param_3;
  *(undefined2 *)((longlong)puVar1 + 0x16) = param_8;
  *(undefined2 *)(puVar1 + 6) = 1;
  puVar1[0xd] = param_13;
  puVar1[2] = param_4;
  return 1;
}


// ==== FUN_1400613a0 @ 1400613a0  undefined8 FUN_1400613a0(longlong param_1, void * param_2)

undefined8 FUN_1400613a0(longlong param_1,void *param_2)

{
  if (*(short *)((longlong)param_2 + 0x18) != 1) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return 0;
  }
  FUN_140034820(param_1);
  *(undefined4 *)(param_1 + 0xc) = 0x38;
  *(undefined4 *)(param_1 + 8) = 0x4e21;
  memcpy(*(void **)(param_1 + 0x418),param_2,0x38);
  return 1;
}


// ==== FUN_140061610 @ 140061610  undefined8 * FUN_140061610(undefined8 * param_1)

undefined8 * FUN_140061610(undefined8 *param_1)

{
  FUN_140034920(param_1);
  *param_1 = CMsgMonsterJump::vftable;
  FUN_140034820((longlong)param_1);
  param_1[0x83] = param_1 + 2;
  return param_1;
}


// ==== FUN_140061660 @ 140061660  undefined FUN_140061660(undefined8 * param_1)

void FUN_140061660(undefined8 *param_1)

{
  *param_1 = CMsgMonsterJump::vftable;
  FUN_140034810(param_1);
  return;
}


// ==== FUN_1400616c0 @ 1400616c0  undefined8 FUN_1400616c0(longlong param_1, undefined4 param_2, undefined2 param_3, undefined2 param_4, undefined2 param_5)

undefined8
FUN_1400616c0(longlong param_1,undefined4 param_2,undefined2 param_3,undefined2 param_4,
             undefined2 param_5)

{
  FUN_140034820(param_1);
  **(undefined4 **)(param_1 + 0x418) = param_2;
  *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 4) = param_3;
  *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 6) = param_4;
  *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 8) = param_5;
  *(undefined4 *)(param_1 + 8) = 0x4e22;
  *(undefined4 *)(param_1 + 0xc) = 0xc;
  return 1;
}


// ==== FUN_1400617f0 @ 1400617f0  undefined8 * FUN_1400617f0(undefined8 * param_1)

undefined8 * FUN_1400617f0(undefined8 *param_1)

{
  FUN_140034920(param_1);
  *param_1 = CMsgDynaGenerator::vftable;
  FUN_140034820((longlong)param_1);
  param_1[0x83] = param_1 + 2;
  return param_1;
}


// ==== FUN_140061840 @ 140061840  undefined FUN_140061840(undefined8 * param_1)

void FUN_140061840(undefined8 *param_1)

{
  *param_1 = CMsgDynaGenerator::vftable;
  FUN_140034810(param_1);
  return;
}


// ==== FUN_140061930 @ 140061930  undefined8 * FUN_140061930(undefined8 * param_1)

undefined8 * FUN_140061930(undefined8 *param_1)

{
  FUN_140034920(param_1);
  *param_1 = CMsgUserAttrib::vftable;
  FUN_140034820((longlong)param_1);
  param_1[0x83] = param_1 + 2;
  return param_1;
}


// ==== FUN_140061980 @ 140061980  undefined FUN_140061980(undefined8 * param_1)

void FUN_140061980(undefined8 *param_1)

{
  *param_1 = CMsgUserAttrib::vftable;
  FUN_140034810(param_1);
  return;
}


// ==== FUN_1400619b0 @ 1400619b0  undefined8 FUN_1400619b0(longlong param_1, undefined4 param_2, uint param_3, undefined4 param_4)

undefined8 FUN_1400619b0(longlong param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  int *piVar1;
  ulong uVar2;
  
  FUN_140034820(param_1);
  *(undefined4 *)(param_1 + 0xc) = 0x28;
  *(undefined4 *)(param_1 + 8) = 0x2721;
  uVar2 = tq::TimeGet(0);
  **(ulong **)(param_1 + 0x418) = uVar2;
  *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 4) = param_2;
  *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 8) = 0;
  if (param_3 < 0x20) {
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 0x1c;
    *(uint *)((ulonglong)*(uint *)(*(longlong *)(param_1 + 0x418) + 8) * 0x1c + 0xc +
             *(longlong *)(param_1 + 0x418)) = param_3;
    *(undefined4 *)
     ((ulonglong)*(uint *)(*(longlong *)(param_1 + 0x418) + 8) * 0x1c + 0x10 +
     *(longlong *)(param_1 + 0x418)) = param_4;
    piVar1 = (int *)(*(longlong *)(param_1 + 0x418) + 8);
    *piVar1 = *piVar1 + 1;
  }
  return 1;
}


// ==== FUN_140061a60 @ 140061a60  undefined8 FUN_140061a60(longlong param_1, uint param_2, undefined4 param_3)

undefined8 FUN_140061a60(longlong param_1,uint param_2,undefined4 param_3)

{
  int *piVar1;
  
  if (param_2 < 0x20) {
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 0x1c;
    *(uint *)((ulonglong)*(uint *)(*(longlong *)(param_1 + 0x418) + 8) * 0x1c + 0xc +
             *(longlong *)(param_1 + 0x418)) = param_2;
    *(undefined4 *)
     ((ulonglong)*(uint *)(*(longlong *)(param_1 + 0x418) + 8) * 0x1c + 0x10 +
     *(longlong *)(param_1 + 0x418)) = param_3;
    piVar1 = (int *)(*(longlong *)(param_1 + 0x418) + 8);
    *piVar1 = *piVar1 + 1;
    return 1;
  }
  log_InlineLogERROR(&DAT_1400be0b0);
  return 0;
}


// ==== FUN_140061b60 @ 140061b60  longlong FUN_140061b60(longlong param_1, ulonglong param_2, char param_3)

longlong FUN_140061b60(longlong param_1,ulonglong param_2,char param_3)

{
  uint *puVar1;
  code *pcVar2;
  byte bVar3;
  longlong lVar4;
  
  if (0xbf < param_2) {
    FUN_1400496c0();
    pcVar2 = (code *)swi(3);
    lVar4 = (*pcVar2)();
    return lVar4;
  }
  bVar3 = (byte)param_2 & 0x1f;
  if (param_3 != '\0') {
    puVar1 = (uint *)(param_1 + (param_2 >> 5) * 4);
    *puVar1 = *puVar1 | 1 << bVar3;
    return param_1;
  }
  puVar1 = (uint *)(param_1 + (param_2 >> 5) * 4);
  *puVar1 = *puVar1 & ~(1 << bVar3);
  return param_1;
}


// ==== FUN_140061bb0 @ 140061bb0  undefined FUN_140061bb0(longlong param_1, longlong param_2)

void FUN_140061bb0(longlong param_1,longlong param_2)

{
  uint *puVar1;
  code *pcVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  if (param_2 != 0) {
    iVar5 = 0;
    do {
      if (0xbf < (ulonglong)(longlong)iVar5) {
        FUN_1400496c0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      if ((*(uint *)(param_1 + ((ulonglong)(longlong)iVar5 >> 5) * 4) >> ((byte)iVar5 & 0x1f) & 1)
          != 0) {
        uVar4 = iVar5 >> 0x1f & 0x1f;
        iVar3 = iVar5 + uVar4;
        puVar1 = (uint *)(param_2 + (longlong)(iVar3 >> 5) * 4);
        *puVar1 = *puVar1 | 1 << (((byte)iVar3 & 0x1f) - (char)uVar4 & 0x1f);
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0xc0);
  }
  return;
}


// ==== FUN_140061c20 @ 140061c20  undefined8 FUN_140061c20(longlong param_1, undefined4 param_2, undefined4 param_3, longlong param_4)

undefined8 FUN_140061c20(longlong param_1,undefined4 param_2,undefined4 param_3,longlong param_4)

{
  int *piVar1;
  ulong uVar2;
  
  FUN_140034820(param_1);
  *(undefined4 *)(param_1 + 0xc) = 0x28;
  *(undefined4 *)(param_1 + 8) = 0x2721;
  uVar2 = tq::TimeGet(0);
  **(ulong **)(param_1 + 0x418) = uVar2;
  *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 4) = param_2;
  *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 8) = 0;
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 0x1c;
  *(undefined4 *)
   ((ulonglong)*(uint *)(*(longlong *)(param_1 + 0x418) + 8) * 0x1c + 0xc +
   *(longlong *)(param_1 + 0x418)) = param_3;
  FUN_140061bb0(param_4,(ulonglong)*(uint *)(*(longlong *)(param_1 + 0x418) + 8) * 0x1c + 0x10 +
                        *(longlong *)(param_1 + 0x418));
  piVar1 = (int *)(*(longlong *)(param_1 + 0x418) + 8);
  *piVar1 = *piVar1 + 1;
  return 1;
}


// ==== FUN_140061ce0 @ 140061ce0  undefined8 FUN_140061ce0(longlong param_1, undefined4 param_2, longlong param_3)

undefined8 FUN_140061ce0(longlong param_1,undefined4 param_2,longlong param_3)

{
  int *piVar1;
  
  if (0x3ff < (longlong)*(int *)(param_1 + 0xc) + 0x1cU) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return 0;
  }
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 0x1c;
  *(undefined4 *)
   ((ulonglong)*(uint *)(*(longlong *)(param_1 + 0x418) + 8) * 0x1c + 0xc +
   *(longlong *)(param_1 + 0x418)) = param_2;
  FUN_140061bb0(param_3,(ulonglong)*(uint *)(*(longlong *)(param_1 + 0x418) + 8) * 0x1c + 0x10 +
                        *(longlong *)(param_1 + 0x418));
  piVar1 = (int *)(*(longlong *)(param_1 + 0x418) + 8);
  *piVar1 = *piVar1 + 1;
  return 1;
}


// ==== FUN_140061d80 @ 140061d80  undefined FUN_140061d80(longlong param_1, longlong param_2)

void FUN_140061d80(longlong param_1,longlong param_2)

{
  uint *puVar1;
  code *pcVar2;
  uint uVar3;
  longlong lVar4;
  uint uVar5;
  int iVar6;
  
  lVar4 = 5;
  iVar6 = 0;
  do {
    *(undefined4 *)(param_2 + lVar4 * 4) = 0;
    lVar4 = lVar4 + -1;
  } while (-1 < lVar4);
  if (param_1 != 0) {
    do {
      uVar5 = iVar6 >> 0x1f & 0x1f;
      uVar3 = iVar6 + uVar5;
      if ((*(uint *)(param_1 + (longlong)((int)uVar3 >> 5) * 4) >> ((uVar3 & 0x1f) - uVar5 & 0x1f) &
          1) != 0) {
        if (0xbf < (ulonglong)(longlong)iVar6) {
          FUN_1400496c0();
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        puVar1 = (uint *)(param_2 + ((ulonglong)(longlong)iVar6 >> 5) * 4);
        *puVar1 = *puVar1 | 1 << ((byte)iVar6 & 0x1f);
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < 0xc0);
  }
  return;
}


// ==== FUN_140062030 @ 140062030  undefined8 * FUN_140062030(undefined8 * param_1)

undefined8 * FUN_140062030(undefined8 *param_1)

{
  FUN_140034920(param_1);
  *param_1 = CMsgWalk::vftable;
  FUN_1400977d0(param_1 + 0x83);
  FUN_140034820((longlong)param_1);
  return param_1;
}


// ==== FUN_140062080 @ 140062080  undefined FUN_140062080(undefined8 * param_1)

void FUN_140062080(undefined8 *param_1)

{
  *param_1 = CMsgWalk::vftable;
  FUN_1400978b0(param_1 + 0x83);
  FUN_140034810(param_1);
  return;
}


// ==== FUN_1400620c0 @ 1400620c0  undefined8 FUN_1400620c0(longlong param_1, int param_2, undefined4 param_3, undefined4 param_4)

undefined8 FUN_1400620c0(longlong param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  longlong lVar3;
  undefined8 uVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [40];
  
  if (param_2 == 0) {
    uVar4 = 0;
  }
  else {
    FUN_140034820(param_1);
    *(uint *)(param_1 + 0x448) = *(uint *)(param_1 + 0x448) | 1;
    *(undefined4 *)(param_1 + 0x450) = param_3;
    *(uint *)(param_1 + 0x448) = *(uint *)(param_1 + 0x448) | 2;
    *(int *)(param_1 + 0x454) = param_2;
    *(uint *)(param_1 + 0x448) = *(uint *)(param_1 + 0x448) | 4;
    *(undefined4 *)(param_1 + 0x458) = param_4;
    *(uint *)(param_1 + 0x448) = *(uint *)(param_1 + 0x448) | 8;
    *(undefined4 *)(param_1 + 0x45c) = 0;
    cVar1 = FUN_140076f80((longlong *)(param_1 + 0x418),param_1 + 0x10,0x400);
    if (cVar1 == '\0') {
      cVar1 = (**(code **)(*(longlong *)(param_1 + 0x418) + 0x20))(param_1 + 0x418);
      if (cVar1 == '\0') {
        lVar3 = (**(code **)(*(longlong *)(param_1 + 0x418) + 0x28))(param_1 + 0x418,local_30);
        if (*(ulonglong *)(lVar3 + 0x20) < 0x10) {
          lVar3 = lVar3 + 8;
        }
        else {
          lVar3 = *(longlong *)(lVar3 + 8);
        }
        log_InlineLogERROR(&DAT_1400ca370,lVar3);
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30);
      }
      else {
        log_InlineLogERROR("CMsgWalk_pb::CreateBufMsg SerializeToArray failed.");
      }
      uVar4 = 0;
    }
    else {
      *(undefined4 *)(param_1 + 8) = 0x2715;
      uVar2 = (**(code **)(*(longlong *)(param_1 + 0x418) + 0x40))(param_1 + 0x418);
      *(undefined4 *)(param_1 + 0xc) = uVar2;
      uVar4 = 1;
    }
  }
  return uVar4;
}


// ==== FUN_1400623e0 @ 1400623e0  undefined8 * FUN_1400623e0(undefined8 * param_1)

undefined8 * FUN_1400623e0(undefined8 *param_1)

{
  FUN_140034920(param_1);
  *param_1 = CMsgAction::vftable;
  FUN_140034820((longlong)param_1);
  param_1[0x83] = param_1 + 2;
  return param_1;
}


// ==== FUN_140062430 @ 140062430  undefined FUN_140062430(undefined8 * param_1)

void FUN_140062430(undefined8 *param_1)

{
  *param_1 = CMsgAction::vftable;
  FUN_140034810(param_1);
  return;
}


// ==== FUN_140062460 @ 140062460  bool FUN_140062460(longlong param_1, int param_2, undefined2 param_3, undefined2 param_4, undefined2 param_5, undefined2 param_6, undefined4 param_7)

bool FUN_140062460(longlong param_1,int param_2,undefined2 param_3,undefined2 param_4,
                  undefined2 param_5,undefined2 param_6,undefined4 param_7)

{
  ulong uVar1;
  
  if (param_2 != 0) {
    FUN_140034820(param_1);
    *(undefined4 *)(param_1 + 0xc) = 0x26;
    *(undefined4 *)(param_1 + 8) = 0x271a;
    uVar1 = tq::TimeGet(0);
    **(ulong **)(param_1 + 0x418) = uVar1;
    uVar1 = tq::TimeGet(0);
    *(ulong *)(*(longlong *)(param_1 + 0x418) + 0x10) = uVar1;
    *(int *)(*(longlong *)(param_1 + 0x418) + 4) = param_2;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 0x18) = param_3;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 0x1a) = param_4;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 0x16) = param_5;
    *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 8) = param_7;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 0x14) = param_6;
  }
  return param_2 != 0;
}


// ==== FUN_140062530 @ 140062530  bool FUN_140062530(longlong param_1, int param_2, undefined2 param_3, undefined2 param_4, undefined2 param_5, undefined2 param_6, undefined2 param_7, undefined2 param_8, undefined4 param_9)

bool FUN_140062530(longlong param_1,int param_2,undefined2 param_3,undefined2 param_4,
                  undefined2 param_5,undefined2 param_6,undefined2 param_7,undefined2 param_8,
                  undefined4 param_9)

{
  ulong uVar1;
  
  if (param_2 != 0) {
    FUN_140034820(param_1);
    *(undefined4 *)(param_1 + 0xc) = 0x26;
    *(undefined4 *)(param_1 + 8) = 0x271a;
    uVar1 = tq::TimeGet(0);
    **(ulong **)(param_1 + 0x418) = uVar1;
    uVar1 = tq::TimeGet(0);
    *(ulong *)(*(longlong *)(param_1 + 0x418) + 0x10) = uVar1;
    *(int *)(*(longlong *)(param_1 + 0x418) + 4) = param_2;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 0x18) = param_3;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 0x1a) = param_4;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 0x16) = param_5;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 0x14) = param_6;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 8) = param_7;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 10) = param_8;
    *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 0x1c) = param_9;
  }
  return param_2 != 0;
}


// ==== FUN_140062f80 @ 140062f80  undefined8 * FUN_140062f80(undefined8 * param_1)

undefined8 * FUN_140062f80(undefined8 *param_1)

{
  FUN_140034920(param_1);
  *param_1 = CMsgPlayer::vftable;
  tq::CStringPacker::CStringPacker((CStringPacker *)(param_1 + 0x84));
  FUN_140034820((longlong)param_1);
  param_1[0x83] = param_1 + 2;
  tq::CStringPacker::SetBuf((CStringPacker *)(param_1 + 0x84),(char *)(param_1 + 0x25),0x2e8,true);
  return param_1;
}


// ==== FUN_140063000 @ 140063000  undefined FUN_140063000(undefined8 * param_1)

void FUN_140063000(undefined8 *param_1)

{
  *param_1 = CMsgPlayer::vftable;
  tq::CStringPacker::~CStringPacker((CStringPacker *)(param_1 + 0x84));
  FUN_140034810(param_1);
  return;
}


// ==== FUN_140063490 @ 140063490  undefined8 * FUN_140063490(undefined8 * param_1)

undefined8 * FUN_140063490(undefined8 *param_1)

{
  FUN_140034920(param_1);
  *param_1 = CMsgInstance::vftable;
  tq::CStringPacker::CStringPacker((CStringPacker *)(param_1 + 0x84));
  FUN_140034820((longlong)param_1);
  param_1[0x83] = param_1 + 2;
  tq::CStringPacker::SetBuf((CStringPacker *)(param_1 + 0x84),(char *)(param_1 + 5),0x3e5,true);
  return param_1;
}


// ==== FUN_140063510 @ 140063510  undefined FUN_140063510(undefined8 * param_1)

void FUN_140063510(undefined8 *param_1)

{
  *param_1 = CMsgInstance::vftable;
  tq::CStringPacker::~CStringPacker((CStringPacker *)(param_1 + 0x84));
  FUN_140034810(param_1);
  return;
}


// ==== FUN_140063630 @ 140063630  undefined8 * FUN_140063630(undefined8 * param_1)

undefined8 * FUN_140063630(undefined8 *param_1)

{
  FUN_140034920(param_1);
  *param_1 = CMsgSyncAction::vftable;
  FUN_140034820((longlong)param_1);
  param_1[0x83] = param_1 + 2;
  return param_1;
}


// ==== FUN_140063680 @ 140063680  undefined FUN_140063680(undefined8 * param_1)

void FUN_140063680(undefined8 *param_1)

{
  *param_1 = CMsgSyncAction::vftable;
  FUN_140034810(param_1);
  return;
}


// ==== FUN_1400638a0 @ 1400638a0  undefined8 * FUN_1400638a0(undefined8 * param_1)

undefined8 * FUN_1400638a0(undefined8 *param_1)

{
  FUN_140034920(param_1);
  *param_1 = CMsgMapInfo::vftable;
  FUN_140034820((longlong)param_1);
  param_1[0x83] = param_1 + 2;
  return param_1;
}


// ==== FUN_1400638f0 @ 1400638f0  undefined FUN_1400638f0(undefined8 * param_1)

void FUN_1400638f0(undefined8 *param_1)

{
  *param_1 = CMsgMapInfo::vftable;
  FUN_140034810(param_1);
  return;
}


// ==== FUN_140063a10 @ 140063a10  undefined8 * FUN_140063a10(undefined8 * param_1)

undefined8 * FUN_140063a10(undefined8 *param_1)

{
  FUN_140034920(param_1);
  *param_1 = CMsgMonsterTransform::vftable;
  FUN_140034820((longlong)param_1);
  param_1[0x83] = param_1 + 2;
  return param_1;
}


// ==== FUN_140063a60 @ 140063a60  undefined FUN_140063a60(undefined8 * param_1)

void FUN_140063a60(undefined8 *param_1)

{
  *param_1 = CMsgMonsterTransform::vftable;
  FUN_140034810(param_1);
  return;
}


// ==== FUN_140063a90 @ 140063a90  undefined8 FUN_140063a90(longlong param_1, undefined4 * param_2)

undefined8 FUN_140063a90(longlong param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  
  FUN_140034820(param_1);
  puVar1 = *(undefined4 **)(param_1 + 0x418);
  *(undefined4 *)(param_1 + 0xc) = 0x24;
  *(undefined4 *)(param_1 + 8) = 0x412;
  *puVar1 = *param_2;
  puVar1[1] = param_2[1];
  puVar1[2] = param_2[2];
  puVar1[3] = param_2[3];
  puVar1[4] = param_2[4];
  puVar1[5] = param_2[5];
  puVar1[6] = param_2[6];
  puVar1[7] = param_2[7];
  puVar1[8] = param_2[8];
  return 1;
}


// ==== FUN_140063b90 @ 140063b90  undefined8 * FUN_140063b90(undefined8 * param_1)

undefined8 * FUN_140063b90(undefined8 *param_1)

{
  FUN_140034920(param_1);
  *param_1 = CMsgNpcPath::vftable;
  tq::CStringPacker::CStringPacker((CStringPacker *)(param_1 + 0x84));
  FUN_140034820((longlong)param_1);
  param_1[0x83] = param_1 + 2;
  *(undefined4 *)((longlong)param_1 + 0x34) = 3;
  tq::CStringPacker::SetBuf
            ((CStringPacker *)(param_1 + 0x84),(char *)(param_1[0x83] + 0x38),0x3c5,true);
  return param_1;
}


// ==== FUN_140063c20 @ 140063c20  undefined FUN_140063c20(undefined8 * param_1)

void FUN_140063c20(undefined8 *param_1)

{
  *param_1 = CMsgNpcPath::vftable;
  tq::CStringPacker::~CStringPacker((CStringPacker *)(param_1 + 0x84));
  FUN_140034810(param_1);
  return;
}


// ==== FUN_140063c60 @ 140063c60  undefined8 FUN_140063c60(longlong param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8)

undefined8
FUN_140063c60(longlong param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
             undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  FUN_140034820(param_1);
  *(undefined4 *)(param_1 + 0xc) = 0x3c;
  *(undefined4 *)(param_1 + 8) = 0x40f;
  **(undefined4 **)(param_1 + 0x418) = param_2;
  *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 4) = param_3;
  *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 8) = param_4;
  *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 0xc) = param_5;
  *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 0x10) = param_6;
  *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 0x18) = param_7;
  *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 0x14) = param_8;
  *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 0x1c) = 0;
  *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 0x24) = 3;
  *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 0x34) = 0;
  return 1;
}


// ==== FUN_140063d80 @ 140063d80  undefined FUN_140063d80(longlong param_1, int param_2)

void FUN_140063d80(longlong param_1,int param_2)

{
  if (0xd < param_2) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return;
  }
  *(int *)(*(longlong *)(param_1 + 0x418) + 0x1c) = param_2;
  return;
}


// ==== FUN_140063dd0 @ 140063dd0  undefined FUN_140063dd0(longlong param_1, undefined4 param_2)

void FUN_140063dd0(longlong param_1,undefined4 param_2)

{
  *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 0x34) = param_2;
  return;
}


// ==== FUN_140063ee0 @ 140063ee0  undefined8 * FUN_140063ee0(undefined8 * param_1)

undefined8 * FUN_140063ee0(undefined8 *param_1)

{
  FUN_140034920(param_1);
  *param_1 = CMsgMagicEffect::vftable;
  FUN_140034820((longlong)param_1);
  param_1[0x83] = param_1 + 2;
  return param_1;
}


// ==== FUN_140063f30 @ 140063f30  undefined FUN_140063f30(undefined8 * param_1)

void FUN_140063f30(undefined8 *param_1)

{
  *param_1 = CMsgMagicEffect::vftable;
  FUN_140034810(param_1);
  return;
}


// ==== FUN_140063f60 @ 140063f60  undefined8 FUN_140063f60(longlong param_1, int param_2, undefined2 param_3, undefined2 param_4, undefined1 param_5, int param_6, undefined4 param_7)

undefined8
FUN_140063f60(longlong param_1,int param_2,undefined2 param_3,undefined2 param_4,undefined1 param_5,
             int param_6,undefined4 param_7)

{
  char *pcVar1;
  undefined8 uVar2;
  
  if ((param_2 == 0) || (param_6 == 0)) {
    log_InlineLogERROR(&DAT_1400be0b0);
    uVar2 = 0;
  }
  else {
    FUN_140034820(param_1);
    *(undefined4 *)(param_1 + 0xc) = 0x30;
    *(undefined4 *)(param_1 + 8) = 0x451;
    **(int **)(param_1 + 0x418) = param_2;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 8) = param_3;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 10) = param_4;
    *(undefined1 *)(*(longlong *)(param_1 + 0x418) + 0xc) = param_5;
    *(int *)(*(longlong *)(param_1 + 0x418) + 4) = param_6;
    *(undefined1 *)(*(longlong *)(param_1 + 0x418) + 0xd) = 0;
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 0x20;
    *(int *)((ulonglong)*(byte *)(*(longlong *)(param_1 + 0x418) + 0xd) * 0x20 + 0x10 +
            *(longlong *)(param_1 + 0x418)) = param_6;
    *(undefined4 *)
     ((ulonglong)*(byte *)(*(longlong *)(param_1 + 0x418) + 0xd) * 0x20 + 0x14 +
     *(longlong *)(param_1 + 0x418)) = param_7;
    pcVar1 = (char *)(*(longlong *)(param_1 + 0x418) + 0xd);
    *pcVar1 = *pcVar1 + '\x01';
    uVar2 = 1;
  }
  return uVar2;
}


// ==== FUN_140064080 @ 140064080  undefined8 FUN_140064080(longlong param_1, int param_2, undefined2 param_3, undefined2 param_4, undefined1 param_5, undefined2 param_6, undefined2 param_7, int param_8, undefined4 param_9)

undefined8
FUN_140064080(longlong param_1,int param_2,undefined2 param_3,undefined2 param_4,undefined1 param_5,
             undefined2 param_6,undefined2 param_7,int param_8,undefined4 param_9)

{
  char *pcVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    uVar2 = 0;
  }
  else {
    FUN_140034820(param_1);
    *(undefined4 *)(param_1 + 0xc) = 0x30;
    *(undefined4 *)(param_1 + 8) = 0x451;
    **(int **)(param_1 + 0x418) = param_2;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 8) = param_3;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 10) = param_4;
    *(undefined1 *)(*(longlong *)(param_1 + 0x418) + 0xc) = param_5;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 4) = param_6;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 6) = param_7;
    *(undefined1 *)(*(longlong *)(param_1 + 0x418) + 0xd) = 0;
    if (param_8 != 0) {
      *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 0x20;
      *(int *)((ulonglong)*(byte *)(*(longlong *)(param_1 + 0x418) + 0xd) * 0x20 + 0x10 +
              *(longlong *)(param_1 + 0x418)) = param_8;
      *(undefined4 *)
       ((ulonglong)*(byte *)(*(longlong *)(param_1 + 0x418) + 0xd) * 0x20 + 0x14 +
       *(longlong *)(param_1 + 0x418)) = param_9;
      pcVar1 = (char *)(*(longlong *)(param_1 + 0x418) + 0xd);
      *pcVar1 = *pcVar1 + '\x01';
    }
    uVar2 = 1;
  }
  return uVar2;
}


// ==== FUN_1400641a0 @ 1400641a0  undefined8 FUN_1400641a0(longlong param_1, int param_2, undefined2 param_3, undefined2 param_4, undefined1 param_5, int param_6, undefined4 param_7, undefined1 param_8)

undefined8
FUN_1400641a0(longlong param_1,int param_2,undefined2 param_3,undefined2 param_4,undefined1 param_5,
             int param_6,undefined4 param_7,undefined1 param_8)

{
  char *pcVar1;
  undefined8 uVar2;
  
  if ((param_2 == 0) || (param_6 == 0)) {
    log_InlineLogERROR(&DAT_1400be0b0);
    uVar2 = 0;
  }
  else {
    FUN_140034820(param_1);
    *(undefined4 *)(param_1 + 0xc) = 0x30;
    *(undefined4 *)(param_1 + 8) = 0x451;
    **(int **)(param_1 + 0x418) = param_2;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 8) = param_3;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 10) = param_4;
    *(undefined1 *)(*(longlong *)(param_1 + 0x418) + 0xc) = param_5;
    *(undefined1 *)(*(longlong *)(param_1 + 0x418) + 4) = param_8;
    *(undefined1 *)(*(longlong *)(param_1 + 0x418) + 0xd) = 0;
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 0x20;
    *(int *)((ulonglong)*(byte *)(*(longlong *)(param_1 + 0x418) + 0xd) * 0x20 + 0x10 +
            *(longlong *)(param_1 + 0x418)) = param_6;
    *(undefined4 *)
     ((ulonglong)*(byte *)(*(longlong *)(param_1 + 0x418) + 0xd) * 0x20 + 0x14 +
     *(longlong *)(param_1 + 0x418)) = param_7;
    pcVar1 = (char *)(*(longlong *)(param_1 + 0x418) + 0xd);
    *pcVar1 = *pcVar1 + '\x01';
    uVar2 = 1;
  }
  return uVar2;
}


// ==== FUN_1400642c0 @ 1400642c0  undefined8 FUN_1400642c0(longlong param_1, int param_2, undefined4 param_3)

undefined8 FUN_1400642c0(longlong param_1,int param_2,undefined4 param_3)

{
  char *pcVar1;
  
  if (param_2 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  if ((longlong)*(int *)(param_1 + 0xc) + 0x20U < 0x400) {
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 0x20;
    *(int *)((ulonglong)*(byte *)(*(longlong *)(param_1 + 0x418) + 0xd) * 0x20 + 0x10 +
            *(longlong *)(param_1 + 0x418)) = param_2;
    *(undefined4 *)
     ((ulonglong)*(byte *)(*(longlong *)(param_1 + 0x418) + 0xd) * 0x20 + 0x14 +
     *(longlong *)(param_1 + 0x418)) = param_3;
    pcVar1 = (char *)(*(longlong *)(param_1 + 0x418) + 0xd);
    *pcVar1 = *pcVar1 + '\x01';
    return 1;
  }
  return 0;
}


// ==== FUN_140064650 @ 140064650  undefined8 * FUN_140064650(undefined8 * param_1)

undefined8 * FUN_140064650(undefined8 *param_1)

{
  FUN_140034920(param_1);
  *param_1 = CMsgInteract::vftable;
  FUN_140034820((longlong)param_1);
  param_1[0x83] = param_1 + 2;
  return param_1;
}


// ==== FUN_1400646a0 @ 1400646a0  undefined FUN_1400646a0(undefined8 * param_1)

void FUN_1400646a0(undefined8 *param_1)

{
  *param_1 = CMsgInteract::vftable;
  FUN_140034810(param_1);
  return;
}


// ==== FUN_140064700 @ 140064700  undefined8 FUN_140064700(longlong param_1, short param_2, int param_3, int param_4, undefined2 param_5, undefined2 param_6, undefined4 param_7)

undefined8
FUN_140064700(longlong param_1,short param_2,int param_3,int param_4,undefined2 param_5,
             undefined2 param_6,undefined4 param_7)

{
  ulong uVar1;
  undefined8 uVar2;
  
  if (((param_2 == 0) || (param_3 == 0)) || (param_4 == 0)) {
    log_InlineLogERROR(&DAT_1400be0b0);
    uVar2 = 0;
  }
  else {
    FUN_140034820(param_1);
    *(short *)(*(longlong *)(param_1 + 0x418) + 0x14) = param_2;
    *(int *)(*(longlong *)(param_1 + 0x418) + 8) = param_3;
    *(int *)(*(longlong *)(param_1 + 0x418) + 0xc) = param_4;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 0x10) = param_5;
    *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 0x12) = param_6;
    *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 0x18) = param_7;
    uVar1 = tq::TimeGet(0);
    **(ulong **)(param_1 + 0x418) = uVar1;
    *(undefined4 *)(param_1 + 8) = 0x3fe;
    *(undefined4 *)(param_1 + 0xc) = 0x28;
    uVar2 = 1;
  }
  return uVar2;
}


// ==== FUN_140064d20 @ 140064d20  undefined8 * FUN_140064d20(undefined8 * param_1)

undefined8 * FUN_140064d20(undefined8 *param_1)

{
  FUN_140034920(param_1);
  *param_1 = CMsgTalk::vftable;
  tq::CStringPacker::CStringPacker((CStringPacker *)(param_1 + 0x84));
  FUN_140034820((longlong)param_1);
  param_1[0x83] = param_1 + 2;
  tq::CStringPacker::SetBuf
            ((CStringPacker *)(param_1 + 0x84),(char *)((longlong)param_1 + 0x2d),0x3e1,true);
  return param_1;
}


// ==== FUN_140064da0 @ 140064da0  undefined FUN_140064da0(undefined8 * param_1)

void FUN_140064da0(undefined8 *param_1)

{
  *param_1 = CMsgTalk::vftable;
  tq::CStringPacker::~CStringPacker((CStringPacker *)(param_1 + 0x84));
  FUN_140034810(param_1);
  return;
}


// ==== FUN_140064de0 @ 140064de0  bool FUN_140064de0(longlong param_1, char * param_2, char * param_3, char * param_4, char * param_5, undefined4 param_6, undefined2 param_7, undefined2 param_8, undefined4 param_9, undefined1 param_10)

bool FUN_140064de0(longlong param_1,char *param_2,char *param_3,char *param_4,char *param_5,
                  undefined4 param_6,undefined2 param_7,undefined2 param_8,undefined4 param_9,
                  undefined1 param_10)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  ulong uVar6;
  uint uVar7;
  ulonglong uVar8;
  char *pcVar9;
  
  if (param_2 != (char *)0x0) {
    uVar8 = 0xffffffffffffffff;
    pcVar9 = param_2;
    do {
      if (uVar8 == 0) break;
      uVar8 = uVar8 - 1;
      cVar1 = *pcVar9;
      pcVar9 = pcVar9 + 1;
    } while (cVar1 != '\0');
    if ((~uVar8 - 1 < 0x24) && (param_3 != (char *)0x0)) {
      uVar8 = 0xffffffffffffffff;
      pcVar9 = param_3;
      do {
        if (uVar8 == 0) break;
        uVar8 = uVar8 - 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar9 + 1;
      } while (cVar1 != '\0');
      if ((~uVar8 - 1 < 0x10) && (param_4 != (char *)0x0)) {
        uVar8 = 0xffffffffffffffff;
        pcVar9 = param_4;
        do {
          if (uVar8 == 0) break;
          uVar8 = uVar8 - 1;
          cVar1 = *pcVar9;
          pcVar9 = pcVar9 + 1;
        } while (cVar1 != '\0');
        if (~uVar8 - 1 < 0x100) {
          if (param_5 != (char *)0x0) {
            uVar8 = 0xffffffffffffffff;
            pcVar9 = param_5;
            do {
              if (uVar8 == 0) break;
              uVar8 = uVar8 - 1;
              cVar1 = *pcVar9;
              pcVar9 = pcVar9 + 1;
            } while (cVar1 != '\0');
            if (0xf < ~uVar8 - 1) {
              return false;
            }
          }
          FUN_140034820(param_1);
          *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 4) = param_6;
          *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 8) = param_7;
          *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 10) = param_8;
          *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 0x18) = param_9;
          *(undefined1 *)(*(longlong *)(param_1 + 0x418) + 0x1c) = param_10;
          uVar6 = tq::SysTimeGet();
          *(ulong *)(*(longlong *)(param_1 + 0x418) + 0xc) = uVar6;
          bVar2 = tq::CStringPacker::AddString((CStringPacker *)(param_1 + 0x420),param_2);
          bVar3 = tq::CStringPacker::AddString((CStringPacker *)(param_1 + 0x420),param_3);
          bVar4 = tq::CStringPacker::AddString((CStringPacker *)(param_1 + 0x420),param_5);
          bVar5 = tq::CStringPacker::AddString((CStringPacker *)(param_1 + 0x420),param_4);
          uVar6 = tq::TimeGet(0);
          **(ulong **)(param_1 + 0x418) = uVar6;
          *(undefined4 *)(param_1 + 8) = 0x3ec;
          uVar7 = tq::CStringPacker::GetSize((CStringPacker *)(param_1 + 0x420));
          *(uint *)(param_1 + 0xc) = uVar7 + 0x1f;
          return ((bVar2 && bVar3) && bVar4) && bVar5;
        }
      }
    }
  }
  return false;
}


// ==== FUN_140065410 @ 140065410  undefined FUN_140065410(undefined8 * param_1)

void FUN_140065410(undefined8 *param_1)

{
  *param_1 = CNpcPath::vftable;
  if ((longlong *)param_1[0xc] != (longlong *)0x0) {
    (**(code **)(*(longlong *)param_1[0xc] + 0x58))();
    param_1[0xc] = 0;
  }
  return;
}


// ==== FUN_140065490 @ 140065490  undefined4 FUN_140065490(longlong param_1)

undefined4 FUN_140065490(longlong param_1)

{
  return *(undefined4 *)(param_1 + 8);
}


// ==== FUN_1400654a0 @ 1400654a0  undefined4 FUN_1400654a0(longlong param_1)

undefined4 FUN_1400654a0(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0xc);
}


// ==== FUN_1400654b0 @ 1400654b0  undefined8 FUN_1400654b0(void)

undefined8 FUN_1400654b0(void)

{
  longlong lVar1;
  longlong *plVar2;
  undefined8 uVar3;
  
  lVar1 = FUN_14001c200();
  plVar2 = (longlong *)FUN_14001c130(lVar1);
  if (plVar2 == (longlong *)0x0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return 0;
  }
  uVar3 = FUN_140034e00(plVar2);
  return uVar3;
}


// ==== FUN_140065510 @ 140065510  undefined8 * FUN_140065510(longlong param_1, undefined8 * param_2)

undefined8 * FUN_140065510(longlong param_1,undefined8 *param_2)

{
  *param_2 = *(undefined8 *)(param_1 + 0x10);
  return param_2;
}


// ==== FUN_140065540 @ 140065540  undefined4 FUN_140065540(longlong param_1)

undefined4 FUN_140065540(longlong param_1)

{
  return *(undefined4 *)(param_1 + 8);
}


// ==== FUN_140065550 @ 140065550  undefined FUN_140065550(undefined8 * param_1)

void FUN_140065550(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    (**(code **)*param_1)(param_1,1);
  }
  return;
}


// ==== FUN_140065570 @ 140065570  undefined8 FUN_140065570(longlong param_1, longlong * param_2)

undefined8 FUN_140065570(longlong param_1,longlong *param_2)

{
  undefined2 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  longlong lVar7;
  ulonglong uVar8;
  longlong *plVar9;
  char *pcVar10;
  ulonglong extraout_RAX;
  
  if (param_2 != (longlong *)0x0) {
    lVar7 = (**(code **)(*param_2 + 0x40))(param_2);
    if (lVar7 != 0) {
      uVar8 = (**(code **)(**(longlong **)(param_1 + 0x60) + 0x30))
                        (*(longlong **)(param_1 + 0x60),param_2);
      if ((char)uVar8 != '\0') {
        plVar9 = (longlong *)(**(code **)(*param_2 + 0x20))(param_2,0);
        uVar2 = (**(code **)(*plVar9 + 0x40))(plVar9);
        plVar9 = (longlong *)(**(code **)(*param_2 + 0x20))(param_2,1);
        uVar3 = (**(code **)(*plVar9 + 0x40))(plVar9);
        plVar9 = (longlong *)(**(code **)(*param_2 + 0x20))(param_2,4);
        uVar4 = (**(code **)(*plVar9 + 0x40))(plVar9);
        plVar9 = (longlong *)(**(code **)(*param_2 + 0x20))(param_2,6);
        uVar1 = (**(code **)(*plVar9 + 0x30))(plVar9);
        plVar9 = (longlong *)(**(code **)(*param_2 + 0x20))(param_2,2);
        uVar5 = (**(code **)(*plVar9 + 0x38))(plVar9);
        plVar9 = (longlong *)(**(code **)(*param_2 + 0x20))(param_2,3);
        uVar6 = (**(code **)(*plVar9 + 0x38))(plVar9);
        plVar9 = (longlong *)(**(code **)(*param_2 + 0x20))(param_2,5);
        pcVar10 = (char *)(**(code **)(*plVar9 + 0x78))(plVar9);
        *(ulonglong *)(param_1 + 0x10) = CONCAT44(uVar6,uVar5);
        *(undefined4 *)(param_1 + 8) = uVar2;
        *(undefined4 *)(param_1 + 0xc) = uVar3;
        *(undefined4 *)(param_1 + 0x18) = uVar4;
        *(undefined2 *)(param_1 + 0x5c) = uVar1;
        pcVar10 = strncpy((char *)(param_1 + 0x1c),pcVar10,0x40);
        return CONCAT71((int7)((ulonglong)pcVar10 >> 8),1);
      }
      goto LAB_1400656f3;
    }
  }
  log_InlineLogERROR(&DAT_1400be0b0);
  uVar8 = extraout_RAX;
LAB_1400656f3:
  return uVar8 & 0xffffffffffffff00;
}


// ==== FUN_140065700 @ 140065700  undefined2 FUN_140065700(longlong param_1)

undefined2 FUN_140065700(longlong param_1)

{
  return *(undefined2 *)(param_1 + 0x5c);
}


// ==== FUN_140065710 @ 140065710  undefined8 FUN_140065710(longlong param_1, int param_2)

undefined8 FUN_140065710(longlong param_1,int param_2)

{
  undefined8 in_RAX;
  
  if (param_2 == 0) {
    *(undefined4 *)(param_1 + 0x68) = 0;
    *(undefined4 *)(param_1 + 0x6c) = 0;
    *(undefined4 *)(param_1 + 0x70) = 0;
    return 1;
  }
  *(int *)(param_1 + 0x68) = param_2;
  return CONCAT71((int7)((ulonglong)in_RAX >> 8),1);
}


// ==== FUN_140065730 @ 140065730  undefined FUN_140065730(longlong param_1, undefined8 * param_2)

void FUN_140065730(longlong param_1,undefined8 *param_2)

{
  *(undefined8 *)(param_1 + 0x6c) = *param_2;
  return;
}


// ==== FUN_140065750 @ 140065750  undefined8 FUN_140065750(longlong param_1)

undefined8 FUN_140065750(longlong param_1)

{
  longlong lVar1;
  longlong *plVar2;
  undefined8 uVar3;
  
  if (*(int *)(param_1 + 0x68) != 0) {
    lVar1 = FUN_14001c200();
    plVar2 = (longlong *)FUN_14001c130(lVar1);
    if (plVar2 != (longlong *)0x0) {
      uVar3 = FUN_140034e00(plVar2);
      return uVar3;
    }
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  return 0;
}


// ==== FUN_1400657c0 @ 1400657c0  undefined8 * FUN_1400657c0(longlong param_1, undefined8 * param_2)

undefined8 * FUN_1400657c0(longlong param_1,undefined8 *param_2)

{
  *param_2 = *(undefined8 *)(param_1 + 0x6c);
  return param_2;
}


// ==== FUN_140065820 @ 140065820  undefined8 * FUN_140065820(undefined8 * param_1, undefined1 param_2)

undefined8 * FUN_140065820(undefined8 *param_1,undefined1 param_2)

{
  *param_1 = IGameData::vftable;
  *param_1 = CGameData<&char*_szNpcPath,&char*_szID>::vftable;
  *(undefined1 *)(param_1 + 2) = param_2;
  param_1[1] = 0;
  return param_1;
}


// ==== FUN_140065860 @ 140065860  undefined FUN_140065860(undefined8 * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_140065860(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 *puVar1;
  
  *param_1 = CGameData<&char*_szNpcPath,&char*_szID>::vftable;
  puVar1 = (undefined8 *)param_1[1];
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,*(char *)(param_1 + 2) == '\0',param_3,param_4,0xfffffffffffffffe);
  }
  *param_1 = IGameData::vftable;
  return;
}


// ==== FUN_140065ce0 @ 140065ce0  undefined8 * FUN_140065ce0(undefined1 param_1)

undefined8 * FUN_140065ce0(undefined1 param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x18);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = IGameData::vftable;
    *puVar1 = CGameData<&char*_szNpcPath,&char*_szID>::vftable;
    *(undefined1 *)(puVar1 + 2) = param_1;
    puVar1[1] = 0;
  }
  return puVar1;
}


// ==== FUN_140065d30 @ 140065d30  undefined8 * FUN_140065d30(undefined8 * param_1)

undefined8 * FUN_140065d30(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  *param_1 = CNpcPath::vftable;
  puVar2 = (undefined8 *)0x0;
  *(undefined4 *)(param_1 + 1) = 0;
  *(undefined4 *)((longlong)param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 3) = 0;
  *(undefined2 *)((longlong)param_1 + 0x5c) = 0;
  param_1[0xc] = 0;
  *(undefined4 *)(param_1 + 0xd) = 0;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14) = 0;
  *(undefined8 *)((longlong)param_1 + 0x1c) = 0;
  *(undefined8 *)((longlong)param_1 + 0x24) = 0;
  *(undefined8 *)((longlong)param_1 + 0x2c) = 0;
  *(undefined8 *)((longlong)param_1 + 0x34) = 0;
  *(undefined8 *)((longlong)param_1 + 0x3c) = 0;
  *(undefined8 *)((longlong)param_1 + 0x44) = 0;
  *(undefined8 *)((longlong)param_1 + 0x4c) = 0;
  *(undefined8 *)((longlong)param_1 + 0x54) = 0;
  puVar1 = (undefined8 *)operator_new(0x18);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = IGameData::vftable;
    *puVar1 = CGameData<&char*_szNpcPath,&char*_szID>::vftable;
    *(undefined1 *)(puVar1 + 2) = 0;
    puVar1[1] = 0;
    puVar2 = puVar1;
  }
  param_1[0xc] = puVar2;
  return param_1;
}


// ==== FUN_140065df0 @ 140065df0  undefined FUN_140065df0(longlong * param_1)

void FUN_140065df0(longlong *param_1)

{
  if ((longlong *)param_1[3] != (longlong *)0x0) {
    FUN_14004c6f0((longlong *)param_1[3],param_1);
  }
  return;
}


// ==== FUN_140065e20 @ 140065e20  undefined2 FUN_140065e20(longlong param_1)

undefined2 FUN_140065e20(longlong param_1)

{
  return *(undefined2 *)(param_1 + 0x9c);
}


// ==== FUN_140065eb0 @ 140065eb0  undefined FUN_140065eb0(longlong * param_1, int param_2, int param_3)

void FUN_140065eb0(longlong *param_1,int param_2,int param_3)

{
  if (param_1[3] != 0) {
    FUN_14004df30(param_1[3],param_1,param_2,param_3);
    *(short *)((longlong)param_1 + 0x8e) = (short)param_2;
    *(short *)(param_1 + 0x12) = (short)param_3;
    return;
  }
  *(short *)((longlong)param_1 + 0x8e) = (short)param_2;
  *(short *)(param_1 + 0x12) = (short)param_3;
  return;
}


// ==== FUN_140065f30 @ 140065f30  undefined FUN_140065f30(undefined8 * param_1)

void FUN_140065f30(undefined8 *param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(**(code **)(*(longlong *)*param_1 + 0x10))();
                    /* WARNING: Could not recover jumptable at 0x000140065f47. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x48))(plVar1);
  return;
}


// ==== FUN_140065f80 @ 140065f80  undefined8 FUN_140065f80(longlong * param_1, void * param_2, int param_3)

undefined8 FUN_140065f80(longlong *param_1,void *param_2,int param_3)

{
  bool bVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  longlong *plVar6;
  undefined7 extraout_var;
  undefined7 extraout_var_00;
  undefined7 uVar7;
  
  memcpy(param_1 + 4,param_2,0x80);
  lVar5 = FUN_14001c790();
  plVar6 = (longlong *)FUN_14003ca10(lVar5,param_3);
  param_1[3] = (longlong)plVar6;
  if (plVar6 == (longlong *)0x0) {
    return 0;
  }
  FUN_14004dba0(plVar6,param_1);
  *(undefined4 *)(param_1 + 0x14) = 0x1e;
  uVar2 = tq::TimeGet(0);
  *(uint *)((longlong)param_1 + 0xa4) = uVar2 / 1000;
  iVar3 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
  iVar4 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
  bVar1 = FUN_140049310(param_1[3],iVar4,iVar3);
  uVar7 = extraout_var;
  if (!bVar1) {
    plVar6 = (longlong *)
             (**(code **)(*(longlong *)**(undefined8 **)(param_1[3] + 0x48) + 0x10))
                       ((longlong *)**(undefined8 **)(param_1[3] + 0x48),3);
    (**(code **)(*plVar6 + 0x48))(plVar6);
    plVar6 = (longlong *)param_1[3];
    FUN_140049430((longlong)plVar6);
    FUN_140049480(param_1[3]);
    (**(code **)(*plVar6 + 8))(plVar6);
    (**(code **)(param_1[2] + 0x40))(param_1 + 2);
    (**(code **)(param_1[2] + 0x38))(param_1 + 2);
    (**(code **)(*param_1 + 8))(param_1);
    log_InlineLogWARNING
              ("CUser::Create. NotStandEnable User[%u][%d, %d], MapID[%u][%d, %d], MapDoc[%d]");
    uVar7 = extraout_var_00;
  }
  return CONCAT71(uVar7,1);
}


// ==== FUN_140066100 @ 140066100  undefined FUN_140066100(longlong * param_1, int param_2, int param_3, int param_4)

void FUN_140066100(longlong *param_1,int param_2,int param_3,int param_4)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  
  lVar4 = FUN_14001c790();
  plVar5 = (longlong *)FUN_14003ca10(lVar4,param_2);
  if (plVar5 == (longlong *)0x0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return;
  }
  if (-1 < param_3) {
    iVar2 = FUN_140049480((longlong)plVar5);
    if ((param_3 < iVar2) && (-1 < param_4)) {
      iVar2 = FUN_140049430((longlong)plVar5);
      if (param_4 < iVar2) {
        if ((longlong *)param_1[3] != (longlong *)0x0) {
          FUN_14004c6f0((longlong *)param_1[3],param_1);
        }
        param_1[3] = (longlong)plVar5;
        FUN_140065eb0(param_1,param_3,param_4);
        FUN_14004dba0(plVar5,param_1);
        iVar2 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
        iVar3 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
        bVar1 = FUN_140049310(param_1[3],iVar3,iVar2);
        if (!bVar1) {
          plVar5 = (longlong *)
                   (**(code **)(*(longlong *)**(undefined8 **)(param_1[3] + 0x48) + 0x10))
                             ((longlong *)**(undefined8 **)(param_1[3] + 0x48),3);
          (**(code **)(*plVar5 + 0x48))(plVar5);
          plVar5 = (longlong *)param_1[3];
          FUN_140049430((longlong)plVar5);
          FUN_140049480(param_1[3]);
          (**(code **)(*plVar5 + 8))(plVar5);
          (**(code **)(param_1[2] + 0x40))(param_1 + 2);
          (**(code **)(param_1[2] + 0x38))(param_1 + 2);
          (**(code **)(*param_1 + 8))(param_1);
          log_InlineLogWARNING
                    ("CUser::FlyMap. NotStandEnable User[%u][%d, %d], MapID[%u][%d, %d], MapDoc[%d]"
                    );
        }
        return;
      }
    }
  }
  log_InlineLogERROR(&DAT_1400be0b0);
  return;
}


// ==== FUN_140066300 @ 140066300  undefined8 FUN_140066300(longlong * param_1, int param_2, int param_3)

ulonglong FUN_140066300(longlong *param_1,int param_2,int param_3)

{
  longlong lVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  ulonglong extraout_RAX;
  undefined8 uVar6;
  longlong *plVar7;
  ulonglong extraout_RAX_00;
  
  if (param_1[3] == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return extraout_RAX & 0xffffffffffffff00;
  }
  bVar2 = (byte)(param_2 >> 0x1f) & 7;
  *(byte *)((longlong)param_1 + 0x92) = ((char)param_2 + bVar2 & 7) - bVar2;
  iVar3 = (**(code **)(param_1[2] + 0x18))();
  iVar3 = *(int *)(&DAT_1400cb320 + (longlong)iVar3 * 4);
  iVar4 = (**(code **)(param_1[2] + 0x18))(param_1 + 2);
  iVar4 = *(int *)(&DAT_1400cb340 + (longlong)iVar4 * 4);
  iVar5 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
  iVar3 = iVar3 + iVar5;
  iVar5 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
  iVar4 = iVar4 + iVar5;
  if (param_3 == 9) {
    *(char *)((longlong)param_1 + 0x92) = (char)param_2 + (char)(param_2 / 0x18) * -0x18;
    iVar3 = (**(code **)(param_1[2] + 0x18))(param_1 + 2);
    iVar3 = *(int *)(&DAT_1400cb360 + (longlong)iVar3 * 4);
    iVar4 = (**(code **)(param_1[2] + 0x18))(param_1 + 2);
    iVar4 = *(int *)(&DAT_1400cb3c0 + (longlong)iVar4 * 4);
    iVar5 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
    iVar3 = iVar3 + iVar5;
    iVar5 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
    iVar4 = iVar4 + iVar5;
  }
  lVar1 = param_1[3];
  if ((((-1 < iVar3) && (iVar5 = FUN_140049480(lVar1), iVar3 < iVar5)) && (-1 < iVar4)) &&
     (iVar5 = FUN_140049430(lVar1), iVar4 < iVar5)) {
    uVar6 = FUN_140065eb0(param_1,iVar3,iVar4);
    return CONCAT71((int7)((ulonglong)uVar6 >> 8),1);
  }
  plVar7 = (longlong *)
           (**(code **)(*(longlong *)**(undefined8 **)(param_1[3] + 0x48) + 0x10))
                     ((longlong *)**(undefined8 **)(param_1[3] + 0x48),3);
  (**(code **)(*plVar7 + 0x48))(plVar7);
  plVar7 = (longlong *)param_1[3];
  FUN_140049430((longlong)plVar7);
  FUN_140049480(param_1[3]);
  (**(code **)(*plVar7 + 8))(plVar7);
  (**(code **)(param_1[2] + 0x40))(param_1 + 2);
  (**(code **)(param_1[2] + 0x38))(param_1 + 2);
  (**(code **)(*param_1 + 8))(param_1);
  log_InlineLogERROR(
                    "CUser::MoveForward. User[%u][%d, %d] NewPos[%d, %d], MapID[%u][%d, %d], MapDoc[%d]"
                    );
  return extraout_RAX_00 & 0xffffffffffffff00;
}


// ==== FUN_140066560 @ 140066560  undefined FUN_140066560(longlong * param_1, int param_2, int param_3, undefined1 param_4)

void FUN_140066560(longlong *param_1,int param_2,int param_3,undefined1 param_4)

{
  longlong lVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  longlong *plVar5;
  
  lVar1 = param_1[3];
  if (lVar1 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return;
  }
  if ((((-1 < param_2) && (iVar3 = FUN_140049480(lVar1), param_2 < iVar3)) && (-1 < param_3)) &&
     (iVar3 = FUN_140049430(lVar1), param_3 < iVar3)) {
    FUN_140065eb0(param_1,param_2,param_3);
    *(undefined1 *)((longlong)param_1 + 0x92) = param_4;
    iVar3 = (**(code **)(param_1[2] + 0x40))(param_1 + 2);
    iVar4 = (**(code **)(param_1[2] + 0x38))(param_1 + 2);
    bVar2 = FUN_140049310(param_1[3],iVar4,iVar3);
    if (bVar2) {
      return;
    }
    plVar5 = (longlong *)
             (**(code **)(*(longlong *)**(undefined8 **)(param_1[3] + 0x48) + 0x10))
                       ((longlong *)**(undefined8 **)(param_1[3] + 0x48),3);
    (**(code **)(*plVar5 + 0x48))(plVar5);
    plVar5 = (longlong *)param_1[3];
    FUN_140049430((longlong)plVar5);
    FUN_140049480(param_1[3]);
    (**(code **)(*plVar5 + 8))(plVar5);
    (**(code **)(param_1[2] + 0x40))(param_1 + 2);
    (**(code **)(param_1[2] + 0x38))(param_1 + 2);
    (**(code **)(*param_1 + 8))(param_1);
    log_InlineLogWARNING
              ("CUser::JumpPos. NotStandEnable User[%u][%d, %d], MapID[%u][%d, %d], MapDoc[%d]");
    return;
  }
  plVar5 = (longlong *)param_1[3];
  FUN_140049430((longlong)plVar5);
  FUN_140049480(param_1[3]);
  (**(code **)(*plVar5 + 8))(plVar5);
  (**(code **)(param_1[2] + 0x40))(param_1 + 2);
  (**(code **)(param_1[2] + 0x38))(param_1 + 2);
  (**(code **)(*param_1 + 8))(param_1);
  log_InlineLogERROR("CUser::JumpPos. User[%u][%d, %d] NewPos[%d, %d], MapID[%u][%d, %d]");
  return;
}


// ==== FUN_140066820 @ 140066820  ulonglong FUN_140066820(longlong * param_1)

ulonglong FUN_140066820(longlong *param_1)

{
  char cVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  longlong lVar7;
  longlong *plVar8;
  ulonglong uVar9;
  longlong *plVar10;
  ulonglong uVar11;
  int local_res10;
  int iVar12;
  ulonglong uVar13;
  
  uVar2 = tq::TimeGet(0);
  uVar13 = (ulonglong)uVar2 * 0x10624dd3 & 0xffffffff;
  if ((uint)((int)param_1[0x14] + *(int *)((longlong)param_1 + 0xa4)) <= uVar2 / 1000) {
    uVar2 = tq::TimeGet(0);
    *(uint *)((longlong)param_1 + 0xa4) = uVar2 / 1000;
    if (param_1[3] != 0) {
      plVar8 = param_1 + 2;
      iVar3 = (**(code **)(*plVar8 + 0x38))(plVar8);
      if (iVar3 / 0x12 + -1 < 1) {
        local_res10 = 0;
      }
      else {
        iVar3 = (**(code **)(*plVar8 + 0x38))(plVar8);
        local_res10 = iVar3 / 0x12 + -1;
      }
      while( true ) {
        plVar8 = param_1 + 2;
        iVar3 = (**(code **)(*plVar8 + 0x38))(plVar8);
        if ((iVar3 / 0x12 + 1 < local_res10) ||
           (iVar3 = FUN_140049490(param_1[3]), iVar3 <= local_res10)) break;
        iVar3 = (**(code **)(*plVar8 + 0x40))(plVar8);
        if (iVar3 / 0x12 + -1 < 1) {
          iVar3 = 0;
        }
        else {
          iVar3 = (**(code **)(*plVar8 + 0x40))(plVar8);
          iVar3 = iVar3 / 0x12 + -1;
        }
        for (; (iVar12 = iVar3, iVar4 = (**(code **)(param_1[2] + 0x40))(param_1 + 2),
               iVar3 <= iVar4 / 0x12 + 1 && (iVar4 = FUN_140049440(param_1[3]), iVar3 < iVar4));
            iVar3 = iVar3 + 1) {
          lVar7 = FUN_14004ac70(param_1[3],local_res10,iVar3);
          plVar8 = (longlong *)FUN_1400678a0(lVar7);
          for (uVar13 = 0; uVar11 = uVar13, uVar9 = (**(code **)(*plVar8 + 0x10))(plVar8),
              uVar13 < uVar9; uVar13 = uVar13 + 1) {
            plVar10 = (longlong *)
                      (**(code **)(*plVar8 + 0x18))
                                (plVar8,uVar13,
                                 "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\user.cpp"
                                 ,0x57,iVar12,uVar11);
            if ((plVar10 != (longlong *)0x0) &&
               (cVar1 = (**(code **)(*plVar10 + 0x50))(plVar10), cVar1 != '\0')) {
              lVar7 = param_1[2];
              uVar5 = (**(code **)(*plVar10 + 0x40))(plVar10);
              uVar6 = (**(code **)(*plVar10 + 0x38))(plVar10);
              uVar11 = (**(code **)(lVar7 + 8))(param_1 + 2,uVar6,uVar5);
              if ((int)uVar11 < 0x13) {
                return uVar11;
              }
            }
          }
        }
        local_res10 = local_res10 + 1;
      }
    }
    plVar8 = (longlong *)FUN_14001c210();
    plVar8 = (longlong *)(**(code **)(*plVar8 + 0x10))(plVar8);
    lVar7 = *plVar8;
    uVar5 = (**(code **)(*param_1 + 8))(param_1);
    uVar13 = (**(code **)(lVar7 + 0x28))(plVar8,uVar5);
  }
  return uVar13;
}


// ==== FUN_140066ba0 @ 140066ba0  undefined FUN_140066ba0(undefined8 * param_1)

void FUN_140066ba0(undefined8 *param_1)

{
  *param_1 = CUser::vftable;
  param_1[2] = CUser::vftable;
  FUN_14005a970(param_1 + 0x15);
  param_1[2] = IRole::vftable;
  FUN_1400695e0(param_1);
  return;
}


// ==== FUN_140066e60 @ 140066e60  undefined8 * FUN_140066e60(undefined8 * param_1)

undefined8 * FUN_140066e60(undefined8 *param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  
  FUN_1400695c0(param_1);
  puVar1 = param_1 + 2;
  *puVar1 = IRole::vftable;
  *param_1 = CUser::vftable;
  *puVar1 = CUser::vftable;
  lVar2 = 5;
  do {
    *(undefined4 *)((longlong)param_1 + lVar2 * 4 + 0x50) = 0;
    lVar2 = lVar2 + -1;
  } while (-1 < lVar2);
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)((longlong)param_1 + 0xa4) = 0;
  param_1[0x15] = 0;
  param_1[0x16] = 0;
  param_1[0x17] = 0;
  memset(param_1 + 4,0,0x80);
  CGameMap::vf_0x18((longlong)param_1,0x1001);
  param_1[3] = 0;
  if ((param_1[0x15] != 0) || (puVar1 == (undefined8 *)0x0)) {
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  param_1[0x15] = puVar1;
  return param_1;
}


// ==== FUN_140066fd0 @ 140066fd0  undefined8 * FUN_140066fd0(void)

undefined8 * FUN_140066fd0(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0xc0);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    puVar1 = FUN_140066e60(puVar1);
  }
  return puVar1;
}


// ==== FUN_140067010 @ 140067010  undefined FUN_140067010(undefined8 * param_1)

void FUN_140067010(undefined8 *param_1)

{
  *param_1 = CDefaultAIStrategy::vftable;
  *param_1 = IAIStrategy::vftable;
  return;
}


// ==== FUN_1400670c0 @ 1400670c0  undefined FUN_1400670c0(longlong param_1, longlong param_2)

void FUN_1400670c0(longlong param_1,longlong param_2)

{
  FUN_14006ae30(param_1 + 0x18,param_2);
  return;
}


// ==== FUN_1400670d0 @ 1400670d0  undefined FUN_1400670d0(longlong param_1)

void FUN_1400670d0(longlong param_1)

{
  *(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + 1;
  return;
}


// ==== FUN_1400670e0 @ 1400670e0  undefined4 FUN_1400670e0(longlong param_1)

undefined4 FUN_1400670e0(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x58);
}


// ==== FUN_1400670f0 @ 1400670f0  longlong * FUN_1400670f0(longlong * param_1)

longlong * FUN_1400670f0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140067112;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140067112:
  if ((ulonglong)param_1[1] <= (ulonglong)puVar1[3]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + -8;
  return param_1;
}


// ==== FUN_140067170 @ 140067170  longlong * FUN_140067170(longlong * param_1)

longlong * FUN_140067170(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140067192;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140067192:
  if ((ulonglong)param_1[1] <= (ulonglong)puVar1[3]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + -8;
  return param_1;
}


// ==== FUN_1400671b0 @ 1400671b0  longlong * FUN_1400671b0(longlong * param_1)

longlong * FUN_1400671b0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_1400671d2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_1400671d2:
  if ((ulonglong)param_1[1] <= (ulonglong)puVar1[3]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + -8;
  return param_1;
}


// ==== FUN_1400671f0 @ 1400671f0  longlong * FUN_1400671f0(longlong * param_1)

longlong * FUN_1400671f0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140067212;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140067212:
  if ((ulonglong)param_1[1] <= (ulonglong)puVar1[3]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + -8;
  return param_1;
}


// ==== FUN_140067230 @ 140067230  ulonglong FUN_140067230(longlong * param_1)

ulonglong FUN_140067230(longlong *param_1)

{
  longlong *plVar1;
  ulonglong uVar2;
  longlong lVar3;
  longlong lVar4;
  
  plVar1 = (longlong *)*param_1;
  lVar3 = 0;
  uVar2 = param_1[1];
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar4 = lVar3;
  }
  else {
    lVar4 = *plVar1;
  }
  if (uVar2 <= *(ulonglong *)(lVar4 + 0x18)) {
    _invalid_parameter_noinfo();
  }
  uVar2 = uVar2 - 8;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  else {
    lVar3 = *plVar1;
  }
  if (*(ulonglong *)(lVar3 + 0x20) <= uVar2) {
    _invalid_parameter_noinfo();
  }
  return uVar2;
}


// ==== FUN_1400672b0 @ 1400672b0  longlong * FUN_1400672b0(longlong param_1, longlong * param_2)

longlong * FUN_1400672b0(longlong param_1,longlong *param_2)

{
  FUN_14006b870(param_1 + 0x18,param_2);
  return param_2;
}


// ==== FUN_1400672f0 @ 1400672f0  longlong * FUN_1400672f0(longlong param_1, longlong * param_2)

longlong * FUN_1400672f0(longlong param_1,longlong *param_2)

{
  FUN_14006bba0(param_1 + 0x18,param_2);
  return param_2;
}


// ==== FUN_140067330 @ 140067330  undefined8 * FUN_140067330(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140067330(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  
  uVar1 = param_1[4];
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  *param_2 = *param_1;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_1400676a0 @ 1400676a0  undefined8 * FUN_1400676a0(undefined8 * param_1, longlong param_2)

undefined8 * FUN_1400676a0(undefined8 *param_1,longlong param_2)

{
  *param_1 = IAIStrategy::vftable;
  *param_1 = CNeuralAIStrategy::vftable;
  FUN_14006d9d0((uint *)(param_1 + 3),4,4,1,8);
  param_1[1] = 0x3ff0000000000000;
  param_1[2] = 0;
  *(undefined4 *)(param_1 + 0xb) = 0;
  FUN_14006ae30((longlong)(param_1 + 3),param_2);
  return param_1;
}


// ==== FUN_140067730 @ 140067730  undefined FUN_140067730(undefined8 * param_1)

void FUN_140067730(undefined8 *param_1)

{
  *param_1 = CNeuralAIStrategy::vftable;
  if (param_1[8] != 0) {
    FUN_140046b40(param_1[8],param_1[9]);
    operator_delete((void *)param_1[8]);
  }
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  operator_delete((void *)param_1[5]);
  *param_1 = IAIStrategy::vftable;
  return;
}


// ==== FUN_1400677c0 @ 1400677c0  undefined8 * FUN_1400677c0(undefined8 * param_1)

undefined8 * FUN_1400677c0(undefined8 *param_1)

{
  *param_1 = IAIStrategy::vftable;
  *param_1 = CNeuralAIStrategy::vftable;
  FUN_14006d9d0((uint *)(param_1 + 3),4,4,1,8);
  param_1[1] = 0x3ff0000000000000;
  param_1[2] = 0;
  *(undefined4 *)(param_1 + 0xb) = 0;
  return param_1;
}


// ==== FUN_140067830 @ 140067830  undefined1 * FUN_140067830(undefined1 * param_1)

undefined1 * FUN_140067830(undefined1 *param_1)

{
  *param_1 = 1;
  *(undefined8 *)(param_1 + 0x10) = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  return param_1;
}


// ==== FUN_140067850 @ 140067850  undefined FUN_140067850(longlong param_1)

void FUN_140067850(longlong param_1)

{
  if (*(longlong *)(param_1 + 0x10) != 0) {
    (**(code **)(**(longlong **)(param_1 + 0x10) + 8))();
  }
  if (*(longlong *)(param_1 + 8) != 0) {
    (**(code **)(**(longlong **)(param_1 + 8) + 8))();
  }
  return;
}


// ==== FUN_140067890 @ 140067890  undefined1 FUN_140067890(undefined1 * param_1)

undefined1 FUN_140067890(undefined1 *param_1)

{
  return *param_1;
}


// ==== FUN_1400678a0 @ 1400678a0  undefined8 FUN_1400678a0(longlong param_1)

undefined8 FUN_1400678a0(longlong param_1)

{
  return *(undefined8 *)(param_1 + 8);
}


// ==== FUN_1400678b0 @ 1400678b0  undefined8 FUN_1400678b0(longlong param_1)

undefined8 FUN_1400678b0(longlong param_1)

{
  return *(undefined8 *)(param_1 + 0x10);
}


// ==== FUN_1400678c0 @ 1400678c0  undefined FUN_1400678c0(undefined1 * param_1, undefined1 param_2)

void FUN_1400678c0(undefined1 *param_1,undefined1 param_2)

{
  *param_1 = param_2;
  return;
}


// ==== FUN_1400678d0 @ 1400678d0  undefined FUN_1400678d0(undefined8 * param_1)

void FUN_1400678d0(undefined8 *param_1)

{
  *param_1 = IGameObjSet<class_INpc>::vftable;
  return;
}


// ==== FUN_140067af0 @ 140067af0  undefined FUN_140067af0(void)

void FUN_140067af0(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [48];
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_70,"vector<T> too long");
  std::exception::exception((exception *)local_48);
  local_48[0] = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
  local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
}


// ==== FUN_140067ba0 @ 140067ba0  undefined FUN_140067ba0(ulonglong param_1)

void FUN_140067ba0(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 8)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 << 3);
  return;
}


// ==== FUN_140067c30 @ 140067c30  undefined FUN_140067c30(undefined8 * param_1)

void FUN_140067c30(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140067c50 @ 140067c50  undefined FUN_140067c50(undefined8 param_1, ulonglong param_2)

void FUN_140067c50(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 8)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 8);
  return;
}


// ==== FUN_140067cd0 @ 140067cd0  undefined FUN_140067cd0(undefined8 * param_1)

void FUN_140067cd0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140067cf0 @ 140067cf0  undefined8 FUN_140067cf0(longlong param_1, ulonglong param_2)

undefined8 FUN_140067cf0(longlong param_1,ulonglong param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  longlong lVar3;
  
  uVar2 = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  if (param_2 != 0) {
    if (0x1fffffffffffffff < param_2) {
      FUN_140067af0();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_140067c50(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    lVar3 = lVar3 + param_2 * 8;
    *(longlong *)(param_1 + 0x28) = lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
  }
  return uVar2;
}


// ==== FUN_140067d60 @ 140067d60  undefined8 * FUN_140067d60(undefined8 * param_1)

undefined8 * FUN_140067d60(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140067da0 @ 140067da0  undefined FUN_140067da0(longlong param_1)

void FUN_140067da0(longlong param_1)

{
  if (*(void **)(param_1 + 0x18) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_140067dd0 @ 140067dd0  undefined8 * FUN_140067dd0(undefined8 * param_1)

undefined8 * FUN_140067dd0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140067e20 @ 140067e20  undefined8 * FUN_140067e20(undefined8 * param_1)

undefined8 * FUN_140067e20(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  puVar2 = (undefined8 *)0x0;
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_1;
    puVar2 = puVar1;
  }
  *param_1 = puVar2;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  return param_1;
}


// ==== FUN_140067e80 @ 140067e80  undefined FUN_140067e80(undefined8 * param_1)

void FUN_140067e80(undefined8 *param_1)

{
  if ((void *)param_1[3] != (void *)0x0) {
    operator_delete((void *)param_1[3]);
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140067ec0 @ 140067ec0  undefined8 * FUN_140067ec0(undefined8 * param_1, undefined1 param_2)

undefined8 * FUN_140067ec0(undefined8 *param_1,undefined1 param_2)

{
  longlong *plVar1;
  longlong *plVar2;
  
  *param_1 = IGameObjSet<class_INpc>::vftable;
  *param_1 = CGameObjSet<class_INpc>::vftable;
  plVar1 = (longlong *)operator_new(8);
  plVar2 = (longlong *)0x0;
  if (plVar1 != (longlong *)0x0) {
    *plVar1 = (longlong)(param_1 + 1);
    plVar2 = plVar1;
  }
  param_1[1] = plVar2;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  *(undefined1 *)(param_1 + 7) = param_2;
  return param_1;
}


// ==== FUN_140067f70 @ 140067f70  longlong FUN_140067f70(longlong param_1, ulonglong param_2)

longlong FUN_140067f70(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)(*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18) >> 3) <= param_2) {
    _invalid_parameter_noinfo();
  }
  return *(longlong *)(param_1 + 0x18) + param_2 * 8;
}


// ==== FUN_140068070 @ 140068070  longlong * FUN_140068070(longlong * param_1, longlong param_2)

longlong * FUN_140068070(longlong *param_1,longlong param_2)

{
  longlong *plVar1;
  ulonglong uVar2;
  longlong lVar3;
  longlong lVar4;
  
  plVar1 = (longlong *)*param_1;
  lVar3 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar1 = (longlong *)*param_1;
    lVar4 = lVar3;
    if (plVar1 != (longlong *)0x0) goto LAB_1400680a0;
  }
  else {
LAB_1400680a0:
    lVar4 = *plVar1;
  }
  uVar2 = param_1[1] + param_2 * 8;
  if (uVar2 <= *(ulonglong *)(lVar4 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar2) goto LAB_1400680c8;
  }
  _invalid_parameter_noinfo();
LAB_1400680c8:
  param_1[1] = param_1[1] + param_2 * 8;
  return param_1;
}


// ==== FUN_1400680e0 @ 1400680e0  longlong FUN_1400680e0(longlong * param_1, longlong * param_2)

longlong FUN_1400680e0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] - param_2[1] >> 3;
}


// ==== FUN_140068130 @ 140068130  bool FUN_140068130(longlong * param_1, longlong * param_2)

bool FUN_140068130(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_140068180 @ 140068180  void * FUN_140068180(void * param_1, longlong param_2, void * param_3)

void * FUN_140068180(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (0 < lVar1) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_140068210 @ 140068210  void * FUN_140068210(void * param_1, longlong param_2, longlong param_3)

void * FUN_140068210(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _Dst = (void *)(param_3 + lVar1 * -8);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 8,param_1,lVar1 * 8);
  }
  return _Dst;
}


// ==== FUN_140068290 @ 140068290  void * FUN_140068290(void * param_1, longlong param_2, void * param_3)

void * FUN_140068290(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_140068390 @ 140068390  longlong * FUN_140068390(longlong * param_1, longlong param_2)

longlong * FUN_140068390(longlong *param_1,longlong param_2)

{
  FUN_140068070(param_1,param_2);
  return param_1;
}


// ==== FUN_1400683c0 @ 1400683c0  bool FUN_1400683c0(longlong * param_1, longlong * param_2)

bool FUN_1400683c0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_140068410 @ 140068410  void * FUN_140068410(void * param_1, longlong param_2, longlong param_3)

void * FUN_140068410(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _Dst = (void *)(param_3 + lVar1 * -8);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 8,param_1,lVar1 * 8);
  }
  return _Dst;
}


// ==== FUN_140068480 @ 140068480  void * FUN_140068480(void * param_1, longlong param_2, void * param_3)

void * FUN_140068480(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_1400684c0 @ 1400684c0  longlong * FUN_1400684c0(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_1400684c0(longlong *param_1,longlong *param_2,longlong param_3)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  
  plVar2 = (longlong *)*param_1;
  lVar3 = param_1[1];
  lVar4 = 0;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar4;
  }
  else {
    lVar5 = *plVar2;
  }
  uVar1 = lVar3 + param_3 * 8;
  if (uVar1 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar2 != (longlong *)0x0) {
      lVar4 = *plVar2;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar1) goto LAB_14006852a;
  }
  _invalid_parameter_noinfo();
LAB_14006852a:
  *param_2 = (longlong)plVar2;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_140068560 @ 140068560  undefined8 * FUN_140068560(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140068560(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_1400685c0 @ 1400685c0  void * FUN_1400685c0(void * param_1, longlong param_2, void * param_3)

void * FUN_1400685c0(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (0 < lVar1) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_140068630 @ 140068630  void * FUN_140068630(void * param_1, longlong param_2, longlong param_3)

void * FUN_140068630(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _Dst = (void *)(param_3 + lVar1 * -8);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 8,param_1,lVar1 * 8);
  }
  return _Dst;
}


// ==== FUN_1400686a0 @ 1400686a0  void * FUN_1400686a0(void * param_1, longlong param_2, void * param_3)

void * FUN_1400686a0(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_1400686e0 @ 1400686e0  undefined8 * FUN_1400686e0(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_1400686e0(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_140068770 @ 140068770  void * FUN_140068770(void * param_1, longlong param_2, void * param_3)

void * FUN_140068770(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_1400687b0 @ 1400687b0  undefined8 * FUN_1400687b0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_1400687b0(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[3];
  *param_2 = 0;
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_140068800 @ 140068800  undefined8 * FUN_140068800(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140068800(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[4];
  *param_2 = 0;
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_140068850 @ 140068850  undefined8 * FUN_140068850(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_140068850(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (undefined8 *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_1400688e0 @ 1400688e0  void * FUN_1400688e0(undefined8 param_1, void * param_2, longlong param_3, void * param_4)

void * FUN_1400688e0(undefined8 param_1,void *param_2,longlong param_3,void *param_4)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_3 - (longlong)param_2 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_4,_DstSize,param_2,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_4);
}


// ==== FUN_140068920 @ 140068920  longlong * FUN_140068920(longlong * param_1, longlong * param_2, longlong param_3, longlong param_4)

longlong * FUN_140068920(longlong *param_1,longlong *param_2,longlong param_3,longlong param_4)

{
  rsize_t _DstSize;
  ulonglong uVar1;
  void *_Src;
  void *_Dst;
  longlong lVar2;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (longlong *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  lVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = lVar2;
  _Src = *(void **)(param_4 + 8);
  if ((_Src < (void *)param_1[3]) || ((void *)param_1[4] < _Src)) {
    _invalid_parameter_noinfo();
  }
  if ((*param_2 == 0) || (*param_2 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  _Dst = (void *)param_2[1];
  if (_Dst != _Src) {
    lVar2 = param_1[4] - (longlong)_Src >> 3;
    _DstSize = lVar2 * 8;
    if (0 < lVar2) {
      memmove_s(_Dst,_DstSize,_Src,_DstSize);
    }
    param_1[4] = (longlong)(_DstSize + (longlong)_Dst);
  }
  return param_2;
}


// ==== FUN_140068a10 @ 140068a10  undefined8 * FUN_140068a10(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_140068a10(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  void *_Src;
  ulonglong uVar1;
  undefined8 uVar2;
  longlong lVar3;
  rsize_t _DstSize;
  
  _Src = (void *)((longlong)*(void **)(param_3 + 8) + 8);
  lVar3 = param_1[4] - (longlong)_Src >> 3;
  if (0 < lVar3) {
    _DstSize = lVar3 << 3;
    memmove_s(*(void **)(param_3 + 8),_DstSize,_Src,_DstSize);
  }
  param_1[4] = param_1[4] + -8;
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if ((uVar1 < (ulonglong)param_1[3]) || ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_140068ad0 @ 140068ad0  undefined FUN_140068ad0(longlong param_1, longlong param_2, ulonglong param_3, undefined8 * param_4)

void FUN_140068ad0(longlong param_1,longlong param_2,ulonglong param_3,undefined8 *param_4)

{
  undefined8 uVar1;
  code *pcVar2;
  void *pvVar3;
  longlong lVar4;
  ulonglong uVar5;
  undefined8 *puVar6;
  longlong lVar7;
  rsize_t rVar8;
  ulonglong uVar9;
  void *pvVar10;
  ulonglong uVar11;
  undefined8 *puVar12;
  
  lVar4 = *(longlong *)(param_1 + 0x18);
  if (lVar4 == 0) {
    uVar5 = 0;
  }
  else {
    uVar5 = *(longlong *)(param_1 + 0x28) - lVar4 >> 3;
  }
  uVar9 = 0;
  if (param_3 != 0) {
    lVar7 = *(longlong *)(param_1 + 0x20);
    lVar4 = lVar7 - lVar4 >> 3;
    if (0x1fffffffffffffffU - lVar4 < param_3) {
      FUN_140067af0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    uVar11 = param_3 + lVar4;
    if (uVar5 < uVar11) {
      if (uVar5 <= 0x1fffffffffffffff - (uVar5 >> 1)) {
        uVar9 = uVar5 + (uVar5 >> 1);
      }
      if (uVar9 < uVar11) {
        uVar9 = uVar11;
      }
      pvVar3 = (void *)FUN_140067c50(param_1 + 0x10,uVar9);
      lVar4 = *(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18) >> 3;
      puVar6 = (undefined8 *)((longlong)pvVar3 + lVar4 * 8);
      for (uVar5 = param_3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *puVar6 = *param_4;
        puVar6 = puVar6 + 1;
      }
      lVar7 = *(longlong *)(param_2 + 8) - (longlong)*(void **)(param_1 + 0x18) >> 3;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 3;
        memmove_s(pvVar3,rVar8,*(void **)(param_1 + 0x18),rVar8);
      }
      lVar7 = *(longlong *)(param_1 + 0x20) - (longlong)*(void **)(param_2 + 8) >> 3;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 3;
        memmove_s((void *)((longlong)pvVar3 + (lVar4 + param_3) * 8),rVar8,*(void **)(param_2 + 8),
                  rVar8);
      }
      pvVar10 = *(void **)(param_1 + 0x18);
      lVar4 = *(longlong *)(param_1 + 0x20);
      if (pvVar10 != (void *)0x0) {
        operator_delete(pvVar10);
      }
      *(void **)(param_1 + 0x28) = (void *)((longlong)pvVar3 + uVar9 * 8);
      *(void **)(param_1 + 0x20) =
           (void *)((longlong)pvVar3 + (param_3 + (lVar4 - (longlong)pvVar10 >> 3)) * 8);
      *(void **)(param_1 + 0x18) = pvVar3;
    }
    else if ((ulonglong)(lVar7 - *(longlong *)(param_2 + 8) >> 3) < param_3) {
      uVar1 = *param_4;
      FUN_1400688e0(param_1,*(void **)(param_2 + 8),lVar7,
                    (void *)((longlong)*(void **)(param_2 + 8) + param_3 * 8));
      puVar6 = *(undefined8 **)(param_1 + 0x20);
      for (lVar4 = param_3 - ((longlong)puVar6 - *(longlong *)(param_2 + 8) >> 3); lVar4 != 0;
          lVar4 = lVar4 + -1) {
        *puVar6 = uVar1;
        puVar6 = puVar6 + 1;
      }
      *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + param_3 * 8;
      lVar4 = *(longlong *)(param_1 + 0x20);
      for (puVar6 = *(undefined8 **)(param_2 + 8); puVar6 != (undefined8 *)(lVar4 + param_3 * -8);
          puVar6 = puVar6 + 1) {
        *puVar6 = uVar1;
      }
    }
    else {
      uVar1 = *param_4;
      pvVar10 = (void *)(lVar7 + param_3 * -8);
      pvVar3 = FUN_1400688e0(param_1,pvVar10,lVar7,(void *)lVar7);
      *(void **)(param_1 + 0x20) = pvVar3;
      FUN_140068630(*(void **)(param_2 + 8),(longlong)pvVar10,lVar7);
      puVar12 = *(undefined8 **)(param_2 + 8);
      puVar6 = puVar12 + param_3;
      for (; puVar12 != puVar6; puVar12 = puVar12 + 1) {
        *puVar12 = uVar1;
      }
    }
  }
  return;
}


// ==== FUN_140068d80 @ 140068d80  undefined FUN_140068d80(longlong * param_1)

void FUN_140068d80(longlong *param_1)

{
  rsize_t _DstSize;
  void *_Src;
  void *_Dst;
  longlong lVar1;
  
  _Src = (void *)param_1[4];
  if (_Src < (void *)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  _Dst = (void *)param_1[3];
  if ((void *)param_1[4] < _Dst) {
    _invalid_parameter_noinfo();
  }
  if ((_Dst < (void *)param_1[3]) || ((void *)param_1[4] < _Dst)) {
    _invalid_parameter_noinfo();
  }
  lVar1 = *param_1;
  if ((_Src < (void *)param_1[3]) || ((void *)param_1[4] < _Src)) {
    _invalid_parameter_noinfo();
  }
  if ((lVar1 == 0) || (lVar1 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (_Dst != _Src) {
    lVar1 = param_1[4] - (longlong)_Src >> 3;
    _DstSize = lVar1 * 8;
    if (0 < lVar1) {
      memmove_s(_Dst,_DstSize,_Src,_DstSize);
    }
    param_1[4] = (longlong)(_DstSize + (longlong)_Dst);
  }
  return;
}


// ==== FUN_140068e40 @ 140068e40  undefined8 * FUN_140068e40(undefined1 param_1)

undefined8 * FUN_140068e40(undefined1 param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x40);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    puVar1 = FUN_140067ec0(puVar1,param_1);
  }
  return puVar1;
}


// ==== FUN_140069150 @ 140069150  longlong * FUN_140069150(longlong * param_1, longlong * param_2, longlong * param_3, undefined8 * param_4)

longlong * FUN_140069150(longlong *param_1,longlong *param_2,longlong *param_3,undefined8 *param_4)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  longlong *local_28;
  ulonglong uStack_20;
  
  lVar3 = 0;
  uVar1 = param_1[3];
  lVar4 = lVar3;
  if ((param_1[4] - uVar1 & 0xfffffffffffffff8) != 0) {
    if ((ulonglong)param_1[4] < uVar1) {
      _invalid_parameter_noinfo();
    }
    if ((*param_3 == 0) || (*param_3 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    lVar4 = (longlong)(param_3[1] - uVar1) >> 3;
  }
  local_28 = (longlong *)*param_3;
  uStack_20 = param_3[1];
  FUN_140068ad0((longlong)param_1,(longlong)&local_28,1,param_4);
  uVar1 = param_1[3];
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)*param_1;
  local_28 = plVar2;
  uStack_20 = uVar1;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar3;
  }
  else {
    lVar5 = *plVar2;
  }
  uVar1 = uVar1 + lVar4 * 8;
  if (uVar1 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar2 != (longlong *)0x0) {
      lVar3 = *plVar2;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar1) goto LAB_140069244;
  }
  _invalid_parameter_noinfo();
LAB_140069244:
  *param_2 = (longlong)local_28;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_140069280 @ 140069280  undefined FUN_140069280(longlong param_1)

void FUN_140069280(longlong param_1)

{
  longlong *plVar1;
  ulonglong uVar2;
  
  if ((*(char *)(param_1 + 0x38) != '\0') &&
     (uVar2 = 0, *(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3 != 0)) {
    do {
      if ((ulonglong)(*(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3) <= uVar2)
      {
        _invalid_parameter_noinfo();
      }
      plVar1 = *(longlong **)(*(longlong *)(param_1 + 0x20) + uVar2 * 8);
      if (plVar1 != (longlong *)0x0) {
        (**(code **)(*plVar1 + 0xf0))();
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < (ulonglong)(*(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3)
            );
  }
  FUN_140068d80((longlong *)(param_1 + 8));
  return;
}


// ==== FUN_140069310 @ 140069310  undefined8 FUN_140069310(longlong param_1)

longlong FUN_140069310(longlong param_1)

{
  undefined8 in_RAX;
  longlong lVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  uint7 uVar4;
  
  if (*(longlong *)(param_1 + 0x10) == 0) {
    puVar2 = (undefined8 *)operator_new(0x40);
    puVar3 = (undefined8 *)0x0;
    if (puVar2 != (undefined8 *)0x0) {
      puVar3 = FUN_14003a770(puVar2,0);
    }
    *(undefined8 **)(param_1 + 0x10) = puVar3;
    puVar2 = (undefined8 *)operator_new(0x40);
    puVar3 = (undefined8 *)0x0;
    if (puVar2 != (undefined8 *)0x0) {
      puVar2 = FUN_140067ec0(puVar2,0);
      puVar3 = puVar2;
    }
    *(undefined8 **)(param_1 + 8) = puVar3;
    uVar4 = (uint7)((ulonglong)puVar2 >> 8);
    if ((*(longlong *)(param_1 + 0x10) == 0) || (puVar3 == (undefined8 *)0x0)) {
      lVar1 = (ulonglong)uVar4 << 8;
    }
    else {
      lVar1 = CONCAT71(uVar4,1);
    }
  }
  else {
    lVar1 = CONCAT71((int7)((ulonglong)in_RAX >> 8),1);
  }
  return lVar1;
}


// ==== FUN_1400693a0 @ 1400693a0  undefined FUN_1400693a0(undefined8 * param_1)

void FUN_1400693a0(undefined8 *param_1)

{
  *param_1 = CGameObjSet<class_INpc>::vftable;
  FUN_140069280((longlong)param_1);
  if ((void *)param_1[4] != (void *)0x0) {
    operator_delete((void *)param_1[4]);
  }
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  operator_delete((void *)param_1[1]);
  *param_1 = IGameObjSet<class_INpc>::vftable;
  return;
}


// ==== FUN_140069410 @ 140069410  undefined FUN_140069410(longlong * param_1, undefined8 * param_2)

void FUN_140069410(longlong *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  ulonglong uVar3;
  longlong local_28;
  undefined8 *puStack_20;
  longlong local_18 [2];
  
  puVar1 = (undefined8 *)param_1[3];
  if (puVar1 == (undefined8 *)0x0) {
    uVar3 = 0;
  }
  else {
    uVar3 = param_1[5] - (longlong)puVar1 >> 3;
  }
  puVar2 = (undefined8 *)param_1[4];
  if ((ulonglong)((longlong)puVar2 - (longlong)puVar1 >> 3) < uVar3) {
    *puVar2 = *param_2;
    param_1[4] = (longlong)(puVar2 + 1);
    return;
  }
  if (puVar2 < puVar1) {
    _invalid_parameter_noinfo();
  }
  local_28 = *param_1;
  puStack_20 = puVar2;
  FUN_140069150(param_1,local_18,&local_28,param_2);
  return;
}


// ==== FUN_1400695c0 @ 1400695c0  undefined8 * FUN_1400695c0(undefined8 * param_1)

undefined8 * FUN_1400695c0(undefined8 *param_1)

{
  *(undefined4 *)(param_1 + 1) = 0;
  *param_1 = CGameObj::vftable;
  return param_1;
}


// ==== FUN_1400695e0 @ 1400695e0  undefined FUN_1400695e0(undefined8 * param_1)

void FUN_1400695e0(undefined8 *param_1)

{
  *param_1 = CGameObj::vftable;
  return;
}


// ==== FUN_140069610 @ 140069610  undefined FUN_140069610(void)

void FUN_140069610(void)

{
  return;
}


// ==== FUN_140069620 @ 140069620  ulonglong FUN_140069620(undefined4 * param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined1 param_5, undefined4 param_6, undefined4 param_7)

ulonglong FUN_140069620(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4
                       ,undefined1 param_5,undefined4 param_6,undefined4 param_7)

{
  longlong *plVar1;
  longlong lVar2;
  ulonglong extraout_RAX;
  ulonglong uVar3;
  
  plVar1 = (longlong *)FUN_14001c250();
  lVar2 = FUN_140034e00(plVar1);
  if (lVar2 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    param_1[2] = 0;
    uVar3 = extraout_RAX & 0xffffffffffffff00;
  }
  else {
    param_1[1] = param_2;
    *param_1 = param_3;
    *(undefined1 *)(param_1 + 10) = param_5;
    param_1[2] = param_4;
    param_1[3] = param_6;
    param_1[4] = 0;
    param_1[5] = param_7;
    uVar3 = CONCAT71((uint7)(uint3)((uint)param_7 >> 8),1);
  }
  return uVar3;
}


// ==== FUN_1400696d0 @ 1400696d0  undefined4 FUN_1400696d0(longlong param_1)

undefined4 FUN_1400696d0(longlong param_1)

{
  return *(undefined4 *)(param_1 + 8);
}


// ==== FUN_1400696e0 @ 1400696e0  undefined4 FUN_1400696e0(longlong param_1)

undefined4 FUN_1400696e0(longlong param_1)

{
  if (*(int *)(param_1 + 8) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return 0;
  }
  return *(undefined4 *)(param_1 + 0x10);
}


// ==== FUN_140069740 @ 140069740  bool FUN_140069740(longlong param_1)

bool FUN_140069740(longlong param_1)

{
  return *(int *)(param_1 + 0x10) == 4;
}


// ==== FUN_140069750 @ 140069750  bool FUN_140069750(longlong param_1)

bool FUN_140069750(longlong param_1)

{
  if (*(int *)(param_1 + 8) == 0) {
    return false;
  }
  return *(int *)(param_1 + 0x10) != 0;
}


// ==== FUN_140069770 @ 140069770  undefined4 FUN_140069770(longlong param_1)

undefined4 FUN_140069770(longlong param_1)

{
  return *(undefined4 *)(param_1 + 4);
}


// ==== FUN_140069780 @ 140069780  undefined FUN_140069780(undefined4 * param_1, longlong param_2)

void FUN_140069780(undefined4 *param_1,longlong param_2)

{
  longlong lVar1;
  
  lVar1 = FUN_14001c200();
  FUN_14001c5f0(lVar1,*param_1,param_2);
  return;
}


// ==== FUN_1400697b0 @ 1400697b0  undefined FUN_1400697b0(undefined4 * param_1)

void FUN_1400697b0(undefined4 *param_1)

{
  longlong lVar1;
  undefined1 auStackY_4a8 [32];
  undefined8 local_458 [136];
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStackY_4a8;
  FUN_140063b90(local_458);
  FUN_140063c60((longlong)local_458,8,param_1[1],0,*param_1,param_1[2],param_1[4],param_1[3]);
  lVar1 = FUN_14001c200();
  FUN_14001c5f0(lVar1,*param_1,(longlong)local_458);
  FUN_140063c20(local_458);
  __security_check_cookie(local_18 ^ (ulonglong)auStackY_4a8);
  return;
}


// ==== FUN_140069850 @ 140069850  undefined FUN_140069850(undefined4 * param_1, int param_2)

void FUN_140069850(undefined4 *param_1,int param_2)

{
  longlong lVar1;
  undefined1 auStackY_4a8 [32];
  undefined8 local_458 [136];
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStackY_4a8;
  FUN_140063b90(local_458);
  FUN_140063c60((longlong)local_458,6,param_1[1],0,*param_1,param_1[2],0,param_1[3]);
  FUN_140063d80((longlong)local_458,param_2);
  lVar1 = FUN_14001c200();
  FUN_14001c5f0(lVar1,*param_1,(longlong)local_458);
  FUN_140063c20(local_458);
  __security_check_cookie(local_18 ^ (ulonglong)auStackY_4a8);
  return;
}


// ==== FUN_140069910 @ 140069910  bool FUN_140069910(longlong param_1)

bool FUN_140069910(longlong param_1)

{
  return *(int *)(param_1 + 0x10) == 5;
}


// ==== FUN_140069920 @ 140069920  undefined4 FUN_140069920(longlong param_1)

undefined4 FUN_140069920(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0xc);
}


// ==== FUN_140069930 @ 140069930  undefined4 * FUN_140069930(undefined4 * param_1)

undefined4 * FUN_140069930(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  *(undefined1 *)(param_1 + 10) = 1;
  return param_1;
}


// ==== FUN_140069960 @ 140069960  undefined FUN_140069960(undefined4 * param_1, undefined4 param_2)

void FUN_140069960(undefined4 *param_1,undefined4 param_2)

{
  longlong lVar1;
  undefined1 auStackY_4a8 [32];
  undefined8 local_458 [136];
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStackY_4a8;
  param_1[2] = param_2;
  FUN_140063b90(local_458);
  FUN_140063c60((longlong)local_458,7,param_1[1],0,*param_1,param_1[2],param_1[4],param_1[3]);
  lVar1 = FUN_14001c200();
  FUN_14001c5f0(lVar1,*param_1,(longlong)local_458);
  FUN_140063c20(local_458);
  __security_check_cookie(local_18 ^ (ulonglong)auStackY_4a8);
  return;
}


// ==== FUN_140069a00 @ 140069a00  undefined FUN_140069a00(undefined4 * param_1, int param_2)

void FUN_140069a00(undefined4 *param_1,int param_2)

{
  if (param_2 < 6) {
    param_1[4] = param_2;
    FUN_1400697b0(param_1);
  }
  return;
}


// ==== FUN_140069a20 @ 140069a20  undefined4 FUN_140069a20(longlong param_1, int param_2)

undefined4 FUN_140069a20(longlong param_1,int param_2)

{
  ulong uVar1;
  
  uVar1 = tq::TimeGet(0);
  return CONCAT31((int3)((uint)*(int *)(param_1 + 0x1c) >> 8),
                  (uint)(param_2 + *(int *)(param_1 + 0x1c)) <= uVar1 / 1000);
}


// ==== FUN_140069a60 @ 140069a60  undefined FUN_140069a60(undefined4 * param_1)

void FUN_140069a60(undefined4 *param_1)

{
  ulong uVar1;
  longlong lVar2;
  undefined1 auStackY_4a8 [32];
  undefined8 local_458 [136];
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStackY_4a8;
  if (param_1[2] == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  else {
    uVar1 = tq::TimeGet(0);
    param_1[7] = uVar1 / 1000;
    param_1[4] = 1;
    FUN_140063b90(local_458);
    FUN_140063c60((longlong)local_458,3,param_1[1],0,*param_1,param_1[2],param_1[4],param_1[3]);
    FUN_140063dd0((longlong)local_458,param_1[5]);
    lVar2 = FUN_14001c200();
    FUN_14001c5f0(lVar2,*param_1,(longlong)local_458);
    FUN_140063c20(local_458);
  }
  __security_check_cookie(local_18 ^ (ulonglong)auStackY_4a8);
  return;
}


// ==== FUN_140069b60 @ 140069b60  undefined FUN_140069b60(undefined4 * param_1)

void FUN_140069b60(undefined4 *param_1)

{
  ulong uVar1;
  
  if (param_1[2] == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return;
  }
  uVar1 = tq::TimeGet(0);
  param_1[4] = 2;
  param_1[9] = uVar1 / 1000;
  FUN_1400697b0(param_1);
  return;
}


// ==== FUN_140069bd0 @ 140069bd0  bool FUN_140069bd0(longlong param_1, int param_2)

bool FUN_140069bd0(longlong param_1,int param_2)

{
  ulong uVar1;
  
  if ((*(int *)(param_1 + 8) != 0) && (*(int *)(param_1 + 0x10) == 2)) {
    uVar1 = tq::TimeGet(0);
    return (uint)(param_2 + *(int *)(param_1 + 0x24)) <= uVar1 / 1000;
  }
  return true;
}


// ==== FUN_140069c30 @ 140069c30  undefined FUN_140069c30(undefined4 * param_1)

void FUN_140069c30(undefined4 *param_1)

{
  if (param_1[2] == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return;
  }
  param_1[4] = 3;
  FUN_1400697b0(param_1);
  return;
}


// ==== FUN_140069c80 @ 140069c80  undefined FUN_140069c80(undefined4 * param_1)

void FUN_140069c80(undefined4 *param_1)

{
  if (param_1[2] == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return;
  }
  param_1[9] = 0;
  param_1[8] = 0;
  param_1[4] = 1;
  FUN_1400697b0(param_1);
  return;
}


// ==== FUN_140069ce0 @ 140069ce0  undefined FUN_140069ce0(undefined4 * param_1)

void FUN_140069ce0(undefined4 *param_1)

{
  if (param_1[2] == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return;
  }
  param_1[7] = 0;
  param_1[6] = 0;
  param_1[9] = 0;
  param_1[8] = 0;
  param_1[4] = 4;
  FUN_1400697b0(param_1);
  return;
}


// ==== FUN_140069d40 @ 140069d40  undefined FUN_140069d40(undefined4 * param_1)

void FUN_140069d40(undefined4 *param_1)

{
  longlong lVar1;
  longlong *plVar2;
  longlong *local_res10 [3];
  
  local_res10[0] = (longlong *)0x0;
  lVar1 = FUN_14001c7a0();
  plVar2 = (longlong *)FUN_140027a40(lVar1,*param_1);
  if (plVar2 != (longlong *)0x0) {
    (**(code **)(*plVar2 + 0xb0))(plVar2,0x1040,local_res10);
    if (local_res10[0] == (longlong *)0x0) {
      log_InlineLogERROR(&DAT_1400be0b0);
      return;
    }
    FUN_14005b0f0(local_res10[0],(uint)*(byte *)(param_1 + 10));
  }
  return;
}


// ==== FUN_140069dd0 @ 140069dd0  undefined FUN_140069dd0(undefined4 * param_1)

void FUN_140069dd0(undefined4 *param_1)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  
  if (param_1[2] == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return;
  }
  param_1[7] = 0;
  param_1[6] = 0;
  param_1[9] = 0;
  param_1[8] = 0;
  lVar2 = FUN_14001c7a0();
  plVar3 = (longlong *)FUN_140027a40(lVar2,*param_1);
  if (plVar3 == (longlong *)0x0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return;
  }
  if (*(char *)(param_1 + 10) == '\0') {
    cVar1 = (**(code **)(*plVar3 + 0x50))(plVar3);
    if (cVar1 != '\0') {
      param_1[4] = 5;
      goto LAB_140069e8a;
    }
  }
  param_1[4] = 0;
LAB_140069e8a:
  FUN_1400697b0(param_1);
  FUN_140069d40(param_1);
  return;
}


// ==== FUN_14006a100 @ 14006a100  void * FUN_14006a100(void * param_1, longlong param_2, void * param_3)

void * FUN_14006a100(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _DstSize = lVar1 * 4;
  if (0 < lVar1) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14006a170 @ 14006a170  void * FUN_14006a170(void * param_1, longlong param_2, void * param_3)

void * FUN_14006a170(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _DstSize = lVar1 * 4;
  if (0 < lVar1) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14006a1c0 @ 14006a1c0  undefined8 * FUN_14006a1c0(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14006a1c0(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (undefined8 *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14006a220 @ 14006a220  undefined FUN_14006a220(undefined8 * param_1)

void FUN_14006a220(undefined8 *param_1)

{
  *param_1 = CEmptyNpcGen::vftable;
  if ((void *)param_1[9] != (void *)0x0) {
    operator_delete((void *)param_1[9]);
  }
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  operator_delete((void *)param_1[6]);
  FUN_14005f480(param_1);
  return;
}


// ==== FUN_14006a290 @ 14006a290  undefined8 * FUN_14006a290(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14006a290(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  void *_Src;
  ulonglong uVar1;
  undefined8 uVar2;
  longlong lVar3;
  rsize_t _DstSize;
  
  _Src = (void *)((longlong)*(void **)(param_3 + 8) + 4);
  lVar3 = param_1[4] - (longlong)_Src >> 2;
  if (0 < lVar3) {
    _DstSize = lVar3 << 2;
    memmove_s(*(void **)(param_3 + 8),_DstSize,_Src,_DstSize);
  }
  param_1[4] = param_1[4] + -4;
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if ((uVar1 < (ulonglong)param_1[3]) || ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14006a320 @ 14006a320  undefined8 * FUN_14006a320(undefined8 * param_1)

undefined8 * FUN_14006a320(undefined8 *param_1)

{
  longlong *plVar1;
  longlong *plVar2;
  
  FUN_1400695c0(param_1);
  *param_1 = IGenerator::vftable;
  *param_1 = CEmptyNpcGen::vftable;
  plVar2 = (longlong *)0x0;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14) = 5;
  *(undefined4 *)(param_1 + 3) = 0;
  *(undefined4 *)((longlong)param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
  plVar1 = (longlong *)operator_new(8);
  if (plVar1 != (longlong *)0x0) {
    *plVar1 = (longlong)(param_1 + 6);
    plVar2 = plVar1;
  }
  param_1[6] = plVar2;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  *(undefined4 *)(param_1 + 5) = 0;
  *(undefined4 *)((longlong)param_1 + 0x24) = 0;
  return param_1;
}


// ==== FUN_14006a3f0 @ 14006a3f0  undefined8 * FUN_14006a3f0(undefined8 * param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined8 param_5, undefined4 param_6, undefined4 param_7)

undefined8 *
FUN_14006a3f0(undefined8 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
             undefined8 param_5,undefined4 param_6,undefined4 param_7)

{
  longlong *plVar1;
  longlong *plVar2;
  
  FUN_1400695c0(param_1);
  *param_1 = IGenerator::vftable;
  *param_1 = CEmptyNpcGen::vftable;
  *(undefined4 *)(param_1 + 2) = param_7;
  *(undefined4 *)((longlong)param_1 + 0x14) = 5;
  *(undefined4 *)(param_1 + 3) = param_6;
  *(undefined4 *)((longlong)param_1 + 0x1c) = param_2;
  *(undefined4 *)(param_1 + 4) = param_4;
  *(undefined8 *)((longlong)param_1 + 0x24) = param_5;
  *(undefined4 *)((longlong)param_1 + 0x2c) = param_3;
  plVar1 = (longlong *)operator_new(8);
  plVar2 = (longlong *)0x0;
  if (plVar1 != (longlong *)0x0) {
    *plVar1 = (longlong)(param_1 + 6);
    plVar2 = plVar1;
  }
  param_1[6] = plVar2;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  return param_1;
}


// ==== FUN_14006a4c0 @ 14006a4c0  longlong * FUN_14006a4c0(undefined4 param_1, int param_2, int param_3, int param_4, undefined4 param_5, undefined4 param_6)

longlong *
FUN_14006a4c0(undefined4 param_1,int param_2,int param_3,int param_4,undefined4 param_5,
             undefined4 param_6)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  longlong *plVar4;
  longlong *plVar5;
  undefined8 *puVar6;
  longlong *plVar7;
  
  plVar7 = (longlong *)0x0;
  lVar3 = FUN_14001c7a0();
  plVar4 = (longlong *)FUN_140025ba0(lVar3);
  lVar3 = (**(code **)(*plVar4 + 0x10))(plVar4);
  plVar4 = plVar7;
  if (lVar3 != 0) {
    do {
      lVar3 = FUN_14001c7a0();
      plVar5 = (longlong *)FUN_140025ba0(lVar3);
      plVar5 = (longlong *)
               (**(code **)(*plVar5 + 0x18))
                         (plVar5,plVar4,
                          "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\emptynpcgen.cpp"
                          ,0x34);
      if ((((plVar5 != (longlong *)0x0) &&
           (iVar1 = (**(code **)(*plVar5 + 0x50))(plVar5), iVar1 == param_3)) &&
          (iVar1 = (**(code **)(*plVar5 + 0x58))(plVar5), iVar1 == param_4)) &&
         (iVar1 = (**(code **)(*plVar5 + 0x40))(plVar5), iVar1 == param_2)) {
        iVar1 = (**(code **)(*plVar5 + 0x48))(plVar5);
        iVar2 = (**(code **)(*plVar5 + 0x20))(plVar5);
        if (iVar2 < iVar1) {
          return plVar5;
        }
      }
      plVar4 = (longlong *)((longlong)plVar4 + 1);
      lVar3 = FUN_14001c7a0();
      plVar5 = (longlong *)FUN_140025ba0(lVar3);
      plVar5 = (longlong *)(**(code **)(*plVar5 + 0x10))(plVar5);
    } while (plVar4 < plVar5);
  }
  DAT_140104670 = DAT_140104670 + 1;
  puVar6 = (undefined8 *)operator_new(0x60);
  if (puVar6 != (undefined8 *)0x0) {
    plVar7 = FUN_14006a3f0(puVar6,DAT_140104670,param_1,param_2,CONCAT44(param_4,param_3),param_5,
                           param_6);
  }
  if (plVar7 == (longlong *)0x0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    plVar7 = (longlong *)0x0;
  }
  else {
    lVar3 = FUN_14001c7a0();
    plVar4 = (longlong *)FUN_140025ba0(lVar3);
    (**(code **)(*plVar4 + 0x20))(plVar4,plVar7);
  }
  return plVar7;
}


// ==== FUN_14006a850 @ 14006a850  double FUN_14006a850(double param_1, double param_2)

double FUN_14006a850(double param_1,double param_2)

{
  double dVar1;
  
  dVar1 = exp(-(param_1 / param_2));
  return 1.0 / (dVar1 + 1.0);
}


// ==== FUN_14006a880 @ 14006a880  longlong FUN_14006a880(longlong param_1, ulonglong param_2)

longlong FUN_14006a880(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)(*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18) >> 3) <= param_2) {
    _invalid_parameter_noinfo();
  }
  return *(longlong *)(param_1 + 0x18) + param_2 * 8;
}


// ==== FUN_14006a8e0 @ 14006a8e0  longlong FUN_14006a8e0(longlong * param_1, longlong * param_2)

longlong FUN_14006a8e0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return (param_1[1] - param_2[1]) / 0x38;
}


// ==== FUN_14006a940 @ 14006a940  longlong FUN_14006a940(longlong * param_1, longlong * param_2)

longlong FUN_14006a940(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return (param_1[1] - param_2[1]) / 0x38;
}


// ==== FUN_14006a9a0 @ 14006a9a0  longlong FUN_14006a9a0(longlong * param_1, longlong * param_2)

longlong FUN_14006a9a0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] - param_2[1] >> 2;
}


// ==== FUN_14006a9e0 @ 14006a9e0  longlong * FUN_14006a9e0(longlong * param_1, longlong param_2)

longlong * FUN_14006a9e0(longlong *param_1,longlong param_2)

{
  longlong *plVar1;
  longlong lVar2;
  longlong lVar3;
  ulonglong uVar4;
  
  plVar1 = (longlong *)*param_1;
  lVar3 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar1 = (longlong *)*param_1;
    lVar2 = lVar3;
    if (plVar1 != (longlong *)0x0) goto LAB_14006aa10;
  }
  else {
LAB_14006aa10:
    lVar2 = *plVar1;
  }
  uVar4 = param_1[1] + param_2 * 0x38;
  if (uVar4 <= *(ulonglong *)(lVar2 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar4) goto LAB_14006aa38;
  }
  _invalid_parameter_noinfo();
LAB_14006aa38:
  param_1[1] = param_1[1] + param_2 * 0x38;
  return param_1;
}


// ==== FUN_14006aa50 @ 14006aa50  longlong * FUN_14006aa50(longlong * param_1, longlong param_2)

longlong * FUN_14006aa50(longlong *param_1,longlong param_2)

{
  longlong *plVar1;
  longlong lVar2;
  longlong lVar3;
  ulonglong uVar4;
  
  plVar1 = (longlong *)*param_1;
  lVar3 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar1 = (longlong *)*param_1;
    lVar2 = lVar3;
    if (plVar1 != (longlong *)0x0) goto LAB_14006aa80;
  }
  else {
LAB_14006aa80:
    lVar2 = *plVar1;
  }
  uVar4 = param_1[1] + param_2 * 0x38;
  if (uVar4 <= *(ulonglong *)(lVar2 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar4) goto LAB_14006aaa8;
  }
  _invalid_parameter_noinfo();
LAB_14006aaa8:
  param_1[1] = param_1[1] + param_2 * 0x38;
  return param_1;
}


// ==== FUN_14006aae0 @ 14006aae0  longlong FUN_14006aae0(longlong param_1, ulonglong param_2)

longlong FUN_14006aae0(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18)) / 0x38) <= param_2
     ) {
    _invalid_parameter_noinfo();
  }
  return param_2 * 0x38 + *(longlong *)(param_1 + 0x18);
}


// ==== FUN_14006ab40 @ 14006ab40  longlong FUN_14006ab40(longlong param_1, ulonglong param_2)

longlong FUN_14006ab40(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18)) / 0x38) <= param_2
     ) {
    _invalid_parameter_noinfo();
  }
  return param_2 * 0x38 + *(longlong *)(param_1 + 0x18);
}


// ==== FUN_14006aba0 @ 14006aba0  longlong FUN_14006aba0(longlong param_1, ulonglong param_2)

longlong FUN_14006aba0(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18)) / 0x38) <= param_2
     ) {
    _invalid_parameter_noinfo();
  }
  return param_2 * 0x38 + *(longlong *)(param_1 + 0x18);
}


// ==== FUN_14006ac00 @ 14006ac00  longlong FUN_14006ac00(longlong param_1, ulonglong param_2)

longlong FUN_14006ac00(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18)) / 0x38) <= param_2
     ) {
    _invalid_parameter_noinfo();
  }
  return param_2 * 0x38 + *(longlong *)(param_1 + 0x18);
}


// ==== FUN_14006ac60 @ 14006ac60  longlong * FUN_14006ac60(longlong * param_1, longlong param_2)

longlong * FUN_14006ac60(longlong *param_1,longlong param_2)

{
  FUN_14006a9e0(param_1,param_2);
  return param_1;
}


// ==== FUN_14006ac80 @ 14006ac80  longlong * FUN_14006ac80(longlong * param_1, longlong param_2)

longlong * FUN_14006ac80(longlong *param_1,longlong param_2)

{
  FUN_14006aa50(param_1,param_2);
  return param_1;
}


// ==== FUN_14006aca0 @ 14006aca0  int FUN_14006aca0(longlong param_1)

int FUN_14006aca0(longlong param_1)

{
  longlong lVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  longlong lVar5;
  ulonglong uVar6;
  undefined4 local_res8;
  undefined4 local_res10;
  undefined8 local_res18;
  
  iVar3 = 0;
  local_res10 = 0;
  local_res18 = 0;
  if (0 < *(int *)(param_1 + 4) + 1) {
    lVar4 = 0;
    do {
      uVar6 = 0;
      lVar5 = 0;
      local_res8 = 0;
      while( true ) {
        if ((ulonglong)((*(longlong *)(param_1 + 0x30) - *(longlong *)(param_1 + 0x28)) / 0x38) <=
            local_res18) {
          _invalid_parameter_noinfo();
        }
        if (*(int *)(lVar4 + *(longlong *)(param_1 + 0x28)) <= local_res8) break;
        iVar2 = 0;
        while( true ) {
          if ((ulonglong)((*(longlong *)(param_1 + 0x30) - *(longlong *)(param_1 + 0x28)) / 0x38) <=
              local_res18) {
            _invalid_parameter_noinfo();
          }
          lVar1 = *(longlong *)(param_1 + 0x28);
          if ((ulonglong)
              ((*(longlong *)(lVar1 + 0x28 + lVar4) - *(longlong *)(lVar1 + 0x20 + lVar4)) / 0x38)
              <= uVar6) {
            _invalid_parameter_noinfo();
          }
          if (*(int *)(lVar5 + *(longlong *)(lVar1 + 0x20 + lVar4)) <= iVar2) break;
          iVar3 = iVar3 + 1;
          iVar2 = iVar2 + 1;
        }
        uVar6 = uVar6 + 1;
        local_res8 = local_res8 + 1;
        lVar5 = lVar5 + 0x38;
      }
      local_res18 = local_res18 + 1;
      local_res10 = local_res10 + 1;
      lVar4 = lVar4 + 0x38;
    } while (local_res10 < *(int *)(param_1 + 4) + 1);
  }
  return iVar3;
}


// ==== FUN_14006ae30 @ 14006ae30  undefined FUN_14006ae30(longlong param_1, longlong param_2)

void FUN_14006ae30(longlong param_1,longlong param_2)

{
  longlong lVar1;
  longlong lVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  longlong lVar5;
  int iVar6;
  longlong lVar7;
  undefined4 local_res8;
  undefined4 local_res18;
  undefined8 local_res20;
  undefined8 local_58;
  
  uVar3 = 0;
  local_res18 = 0;
  local_58 = 0;
  if (0 < *(int *)(param_1 + 4) + 1) {
    lVar7 = 0;
    do {
      lVar5 = 0;
      local_res8 = 0;
      local_res20 = 0;
      while( true ) {
        if ((ulonglong)((*(longlong *)(param_1 + 0x30) - *(longlong *)(param_1 + 0x28)) / 0x38) <=
            local_58) {
          _invalid_parameter_noinfo();
        }
        if (*(int *)(lVar7 + *(longlong *)(param_1 + 0x28)) <= local_res8) break;
        iVar6 = 0;
        uVar4 = 0;
        while( true ) {
          if ((ulonglong)((*(longlong *)(param_1 + 0x30) - *(longlong *)(param_1 + 0x28)) / 0x38) <=
              local_58) {
            _invalid_parameter_noinfo();
          }
          lVar1 = *(longlong *)(param_1 + 0x28);
          if ((ulonglong)
              ((*(longlong *)(lVar1 + 0x28 + lVar7) - *(longlong *)(lVar1 + 0x20 + lVar7)) / 0x38)
              <= local_res20) {
            _invalid_parameter_noinfo();
          }
          if (*(int *)(lVar5 + *(longlong *)(lVar1 + 0x20 + lVar7)) <= iVar6) break;
          if ((ulonglong)(*(longlong *)(param_2 + 0x20) - *(longlong *)(param_2 + 0x18) >> 3) <=
              uVar3) {
            _invalid_parameter_noinfo();
          }
          lVar1 = *(longlong *)(param_2 + 0x18);
          if ((ulonglong)((*(longlong *)(param_1 + 0x30) - *(longlong *)(param_1 + 0x28)) / 0x38) <=
              local_58) {
            _invalid_parameter_noinfo();
          }
          lVar2 = *(longlong *)(param_1 + 0x28);
          if ((ulonglong)
              ((*(longlong *)(lVar7 + 0x28 + lVar2) - *(longlong *)(lVar7 + 0x20 + lVar2)) / 0x38)
              <= local_res20) {
            _invalid_parameter_noinfo();
          }
          lVar2 = *(longlong *)(lVar7 + 0x20 + lVar2);
          if ((ulonglong)
              (*(longlong *)(lVar5 + 0x28 + lVar2) - *(longlong *)(lVar5 + 0x20 + lVar2) >> 3) <=
              uVar4) {
            _invalid_parameter_noinfo();
          }
          *(undefined8 *)(*(longlong *)(lVar5 + 0x20 + lVar2) + uVar4 * 8) =
               *(undefined8 *)(lVar1 + uVar3 * 8);
          uVar3 = uVar3 + 1;
          iVar6 = iVar6 + 1;
          uVar4 = uVar4 + 1;
        }
        local_res20 = local_res20 + 1;
        local_res8 = local_res8 + 1;
        lVar5 = lVar5 + 0x38;
      }
      local_58 = local_58 + 1;
      local_res18 = local_res18 + 1;
      lVar7 = lVar7 + 0x38;
    } while (local_res18 < *(int *)(param_1 + 4) + 1);
  }
  return;
}


// ==== FUN_14006b0e0 @ 14006b0e0  longlong * FUN_14006b0e0(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_14006b0e0(longlong *param_1,longlong *param_2,longlong param_3)

{
  longlong *plVar1;
  longlong lVar2;
  ulonglong uVar3;
  longlong lVar4;
  longlong lVar5;
  
  plVar1 = (longlong *)*param_1;
  lVar2 = param_1[1];
  lVar4 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar4;
  }
  else {
    lVar5 = *plVar1;
  }
  uVar3 = param_3 * 0x38 + lVar2;
  if (uVar3 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar4 = *plVar1;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar3) goto LAB_14006b14d;
  }
  _invalid_parameter_noinfo();
LAB_14006b14d:
  *param_2 = (longlong)plVar1;
  param_2[1] = uVar3;
  return param_2;
}


// ==== FUN_14006b180 @ 14006b180  longlong * FUN_14006b180(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_14006b180(longlong *param_1,longlong *param_2,longlong param_3)

{
  longlong *plVar1;
  longlong lVar2;
  ulonglong uVar3;
  longlong lVar4;
  longlong lVar5;
  
  plVar1 = (longlong *)*param_1;
  lVar2 = param_1[1];
  lVar4 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar4;
  }
  else {
    lVar5 = *plVar1;
  }
  uVar3 = param_3 * 0x38 + lVar2;
  if (uVar3 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar4 = *plVar1;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar3) goto LAB_14006b1ed;
  }
  _invalid_parameter_noinfo();
LAB_14006b1ed:
  *param_2 = (longlong)plVar1;
  param_2[1] = uVar3;
  return param_2;
}


// ==== FUN_14006b220 @ 14006b220  undefined8 * FUN_14006b220(undefined8 * param_1)

undefined8 * FUN_14006b220(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  puVar2 = (undefined8 *)0x0;
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_1;
    puVar2 = puVar1;
  }
  *param_1 = puVar2;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  return param_1;
}


// ==== FUN_14006b280 @ 14006b280  undefined8 * FUN_14006b280(undefined8 * param_1)

undefined8 * FUN_14006b280(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  puVar2 = (undefined8 *)0x0;
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_1;
    puVar2 = puVar1;
  }
  *param_1 = puVar2;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  return param_1;
}


// ==== FUN_14006b2e0 @ 14006b2e0  longlong * FUN_14006b2e0(longlong * param_1, longlong * param_2, longlong * param_3, undefined4 * param_4)

longlong * FUN_14006b2e0(longlong *param_1,longlong *param_2,longlong *param_3,undefined4 *param_4)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  longlong *local_28;
  ulonglong uStack_20;
  
  lVar3 = 0;
  uVar1 = param_1[3];
  lVar4 = lVar3;
  if ((param_1[4] - uVar1 & 0xfffffffffffffffc) != 0) {
    if ((ulonglong)param_1[4] < uVar1) {
      _invalid_parameter_noinfo();
    }
    if ((*param_3 == 0) || (*param_3 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    lVar4 = (longlong)(param_3[1] - uVar1) >> 2;
  }
  local_28 = (longlong *)*param_3;
  uStack_20 = param_3[1];
  FUN_140050ac0((longlong)param_1,(longlong)&local_28,1,param_4);
  uVar1 = param_1[3];
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)*param_1;
  local_28 = plVar2;
  uStack_20 = uVar1;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar3;
  }
  else {
    lVar5 = *plVar2;
  }
  uVar1 = uVar1 + lVar4 * 4;
  if (uVar1 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar2 != (longlong *)0x0) {
      lVar3 = *plVar2;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar1) goto LAB_14006b3d4;
  }
  _invalid_parameter_noinfo();
LAB_14006b3d4:
  *param_2 = (longlong)local_28;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_14006b410 @ 14006b410  undefined4 * FUN_14006b410(longlong param_1, longlong param_2, undefined4 * param_3)

undefined4 * FUN_14006b410(longlong param_1,longlong param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  longlong lVar2;
  
  puVar1 = param_3;
  if (param_1 != param_2) {
    do {
      lVar2 = param_2 + -0x38;
      param_3 = puVar1 + -0xe;
      *param_3 = *(undefined4 *)(param_2 + -0x38);
      FUN_1400441e0((longlong *)(puVar1 + -0xc),(longlong *)(param_2 + -0x30));
      puVar1 = param_3;
      param_2 = lVar2;
    } while (lVar2 != param_1);
  }
  return param_3;
}


// ==== FUN_14006b470 @ 14006b470  undefined FUN_14006b470(longlong * param_1, undefined4 * param_2)

void FUN_14006b470(longlong *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  ulonglong uVar3;
  longlong local_28;
  undefined4 *puStack_20;
  longlong local_18 [2];
  
  puVar1 = (undefined4 *)param_1[3];
  if (puVar1 == (undefined4 *)0x0) {
    uVar3 = 0;
  }
  else {
    uVar3 = param_1[5] - (longlong)puVar1 >> 2;
  }
  puVar2 = (undefined4 *)param_1[4];
  if ((ulonglong)((longlong)puVar2 - (longlong)puVar1 >> 2) < uVar3) {
    *puVar2 = *param_2;
    param_1[4] = (longlong)(puVar2 + 1);
    return;
  }
  if (puVar2 < puVar1) {
    _invalid_parameter_noinfo();
  }
  local_28 = *param_1;
  puStack_20 = puVar2;
  FUN_14006b2e0(param_1,local_18,&local_28,param_2);
  return;
}


// ==== FUN_14006b520 @ 14006b520  undefined FUN_14006b520(undefined4 * param_1, longlong param_2, undefined4 * param_3)

void FUN_14006b520(undefined4 *param_1,longlong param_2,undefined4 *param_3)

{
  for (; param_2 != 0; param_2 = param_2 + -1) {
    if (param_1 != (undefined4 *)0x0) {
      *param_1 = *param_3;
      FUN_140043490((undefined8 *)(param_1 + 2),(undefined8 *)(param_3 + 2));
    }
    param_1 = param_1 + 0xe;
  }
  return;
}


// ==== FUN_14006b590 @ 14006b590  undefined FUN_14006b590(undefined4 * param_1, undefined4 * param_2, undefined4 * param_3)

void FUN_14006b590(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  if (param_1 != param_2) {
    do {
      *param_1 = *param_3;
      FUN_1400441e0((longlong *)(param_1 + 2),(longlong *)(param_3 + 2));
      param_1 = param_1 + 0xe;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_14006b5f0 @ 14006b5f0  longlong FUN_14006b5f0(longlong param_1, longlong param_2, longlong param_3)

longlong FUN_14006b5f0(longlong param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  longlong lVar2;
  
  if (param_1 != param_2) {
    lVar1 = param_2;
    do {
      lVar2 = lVar1 + -0x38;
      *(undefined4 *)((param_3 - param_2) + lVar2) = *(undefined4 *)(lVar1 + -0x38);
      FUN_1400441e0((longlong *)((param_3 - param_2) + lVar1 + -0x30),(longlong *)(lVar1 + -0x30));
      lVar1 = lVar2;
    } while (lVar2 != param_1);
  }
  return param_3 + ((param_2 - param_1) / 0x38) * -0x38;
}


// ==== FUN_14006b680 @ 14006b680  uint * FUN_14006b680(uint * param_1, int param_2)

uint * FUN_14006b680(uint *param_1,int param_2)

{
  uint uVar1;
  uint *puVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  int iVar5;
  int iVar6;
  longlong *plVar7;
  longlong lVar8;
  ulonglong uVar9;
  longlong lVar10;
  ulonglong uVar11;
  uint *local_res18;
  longlong *local_res20;
  longlong local_58;
  undefined8 *puStack_50;
  
  puVar2 = param_1 + 2;
  local_res18 = puVar2;
  local_res20 = (longlong *)operator_new(8);
  if (local_res20 == (longlong *)0x0) {
    plVar7 = (longlong *)0x0;
  }
  else {
    *local_res20 = (longlong)puVar2;
    plVar7 = local_res20;
  }
  *(longlong **)puVar2 = plVar7;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  uVar1 = param_2 + 1;
  *param_1 = uVar1;
  if (0 < (int)uVar1) {
    uVar11 = (ulonglong)uVar1;
    do {
      iVar5 = rand();
      iVar6 = rand();
      local_res18 = (uint *)((double)iVar5 * 3.0517578125e-05 - (double)iVar6 * 3.0517578125e-05);
      puVar3 = *(undefined8 **)(param_1 + 8);
      if (puVar3 == (undefined8 *)0x0) {
        uVar9 = 0;
      }
      else {
        uVar9 = *(longlong *)(param_1 + 0xc) - (longlong)puVar3 >> 3;
      }
      puVar4 = *(undefined8 **)(param_1 + 10);
      if ((ulonglong)((longlong)puVar4 - (longlong)puVar3 >> 3) < uVar9) {
        *puVar4 = local_res18;
        *(undefined8 **)(param_1 + 10) = puVar4 + 1;
      }
      else {
        if (puVar4 < puVar3) {
          _invalid_parameter_noinfo();
        }
        lVar8 = *(longlong *)puVar2;
        uVar9 = *(ulonglong *)(param_1 + 8);
        if ((*(ulonglong *)(param_1 + 10) - uVar9 & 0xfffffffffffffff8) == 0) {
          lVar10 = 0;
        }
        else {
          if (*(ulonglong *)(param_1 + 10) < uVar9) {
            _invalid_parameter_noinfo();
          }
          if ((lVar8 == 0) || (lVar8 != *(longlong *)puVar2)) {
            _invalid_parameter_noinfo();
          }
          lVar10 = (longlong)((longlong)puVar4 - uVar9) >> 3;
        }
        local_58 = lVar8;
        puStack_50 = puVar4;
        FUN_140043b40((longlong)puVar2,(longlong)&local_58,1,&local_res18);
        uVar9 = *(ulonglong *)(param_1 + 8);
        if (*(ulonglong *)(param_1 + 10) < uVar9) {
          _invalid_parameter_noinfo();
        }
        plVar7 = *(longlong **)puVar2;
        if (plVar7 == (longlong *)0x0) {
          _invalid_parameter_noinfo();
          lVar8 = 0;
        }
        else {
          lVar8 = *plVar7;
        }
        uVar9 = uVar9 + lVar10 * 8;
        if (uVar9 <= *(ulonglong *)(lVar8 + 0x20)) {
          if (plVar7 == (longlong *)0x0) {
            lVar8 = 0;
          }
          else {
            lVar8 = *plVar7;
          }
          if (*(ulonglong *)(lVar8 + 0x18) <= uVar9) goto LAB_14006b840;
        }
        _invalid_parameter_noinfo();
      }
LAB_14006b840:
      uVar11 = uVar11 - 1;
    } while (uVar11 != 0);
  }
  return param_1;
}


// ==== FUN_14006b870 @ 14006b870  longlong * FUN_14006b870(longlong param_1, longlong * param_2)

longlong * FUN_14006b870(longlong param_1,longlong *param_2)

{
  int *piVar1;
  int *piVar2;
  ulonglong uVar3;
  longlong *plVar4;
  longlong *plVar5;
  undefined8 *puVar6;
  int iVar7;
  ulonglong uVar8;
  longlong *plVar9;
  int iVar10;
  int iVar11;
  longlong lVar12;
  longlong lVar13;
  int iVar14;
  longlong lVar15;
  longlong lVar16;
  int local_74;
  longlong *local_70;
  ulonglong local_68;
  undefined8 local_60;
  longlong local_58;
  int *piStack_50;
  longlong local_48;
  int *piStack_40;
  
  local_60 = 0xfffffffffffffffe;
  iVar14 = 0;
  plVar9 = param_2;
  puVar6 = (undefined8 *)operator_new(8);
  if (puVar6 == (undefined8 *)0x0) {
    puVar6 = (undefined8 *)0x0;
  }
  else {
    *puVar6 = param_2;
  }
  *param_2 = (longlong)puVar6;
  param_2[3] = 0;
  param_2[4] = 0;
  param_2[5] = 0;
  iVar7 = 0;
  local_70 = (longlong *)0x0;
  if (0 < *(int *)(param_1 + 4) + 1) {
    lVar15 = 0;
    do {
      iVar11 = 0;
      local_68 = 0;
      lVar16 = 0;
      while( true ) {
        uVar3 = local_68;
        plVar4 = local_70;
        plVar9 = (longlong *)
                 ((*(longlong *)(param_1 + 0x30) - *(longlong *)(param_1 + 0x28)) / 0x38);
        if (plVar9 <= local_70) {
          _invalid_parameter_noinfo();
        }
        plVar5 = local_70;
        if (*(int *)(lVar15 + *(longlong *)(param_1 + 0x28)) <= iVar11) break;
        iVar10 = 0;
        while( true ) {
          if ((longlong *)((*(longlong *)(param_1 + 0x30) - *(longlong *)(param_1 + 0x28)) / 0x38)
              <= plVar5) {
            _invalid_parameter_noinfo();
          }
          lVar12 = *(longlong *)(param_1 + 0x28);
          if ((ulonglong)
              ((*(longlong *)(lVar15 + 0x28 + lVar12) - *(longlong *)(lVar15 + 0x20 + lVar12)) /
              0x38) <= uVar3) {
            _invalid_parameter_noinfo();
          }
          if (*(int *)(lVar16 + *(longlong *)(lVar15 + 0x20 + lVar12)) <= iVar10) break;
          iVar14 = iVar14 + 1;
          iVar10 = iVar10 + 1;
        }
        local_74 = iVar14 + -1;
        piVar1 = (int *)param_2[3];
        if (piVar1 == (int *)0x0) {
          uVar8 = 0;
        }
        else {
          uVar8 = param_2[5] - (longlong)piVar1 >> 2;
        }
        piVar2 = (int *)param_2[4];
        if ((ulonglong)((longlong)piVar2 - (longlong)piVar1 >> 2) < uVar8) {
          *piVar2 = local_74;
          param_2[4] = (longlong)(piVar2 + 1);
          local_68 = uVar3;
        }
        else {
          if (piVar2 < piVar1) {
            _invalid_parameter_noinfo();
          }
          lVar12 = *param_2;
          uVar3 = param_2[3];
          local_58 = lVar12;
          piStack_50 = piVar2;
          if ((param_2[4] - uVar3 & 0xfffffffffffffffc) == 0) {
            lVar12 = 0;
          }
          else {
            if ((ulonglong)param_2[4] < uVar3) {
              _invalid_parameter_noinfo();
            }
            if ((lVar12 == 0) || (lVar12 != *param_2)) {
              _invalid_parameter_noinfo();
            }
            lVar12 = (longlong)((longlong)piVar2 - uVar3) >> 2;
          }
          local_48 = local_58;
          piStack_40 = piStack_50;
          FUN_140050ac0((longlong)param_2,(longlong)&local_48,1,&local_74);
          uVar3 = param_2[3];
          if ((ulonglong)param_2[4] < uVar3) {
            _invalid_parameter_noinfo();
          }
          plVar9 = (longlong *)*param_2;
          if (plVar9 == (longlong *)0x0) {
            _invalid_parameter_noinfo();
            lVar13 = 0;
          }
          else {
            lVar13 = *plVar9;
          }
          uVar3 = uVar3 + lVar12 * 4;
          if (uVar3 <= *(ulonglong *)(lVar13 + 0x20)) {
            if (plVar9 == (longlong *)0x0) {
              lVar12 = 0;
            }
            else {
              lVar12 = *plVar9;
            }
            if (*(ulonglong *)(lVar12 + 0x18) <= uVar3) goto LAB_14006bb1e;
          }
          _invalid_parameter_noinfo();
        }
LAB_14006bb1e:
        iVar11 = iVar11 + 1;
        local_68 = local_68 + 1;
        lVar16 = lVar16 + 0x38;
      }
      iVar7 = iVar7 + 1;
      local_70 = (longlong *)((longlong)plVar4 + 1);
      lVar15 = lVar15 + 0x38;
    } while (iVar7 < *(int *)(param_1 + 4) + 1);
  }
  return plVar9;
}


// ==== FUN_14006bba0 @ 14006bba0  longlong * FUN_14006bba0(longlong param_1, longlong * param_2)

longlong * FUN_14006bba0(longlong param_1,longlong *param_2)

{
  longlong lVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  longlong lVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  ulonglong uVar9;
  longlong *plVar10;
  
  plVar3 = param_2;
  puVar2 = (undefined8 *)operator_new(8);
  if (puVar2 == (undefined8 *)0x0) {
    puVar2 = (undefined8 *)0x0;
  }
  else {
    *puVar2 = param_2;
  }
  *param_2 = (longlong)puVar2;
  param_2[3] = 0;
  param_2[4] = 0;
  param_2[5] = 0;
  iVar6 = 0;
  plVar10 = (longlong *)0x0;
  if (0 < *(int *)(param_1 + 4) + 1) {
    lVar8 = 0;
    do {
      iVar7 = 0;
      uVar9 = 0;
      lVar4 = 0;
      while( true ) {
        plVar3 = (longlong *)
                 ((*(longlong *)(param_1 + 0x30) - *(longlong *)(param_1 + 0x28)) / 0x38);
        if (plVar3 <= plVar10) {
          _invalid_parameter_noinfo();
        }
        if (*(int *)(lVar8 + *(longlong *)(param_1 + 0x28)) <= iVar7) break;
        iVar5 = 0;
        while( true ) {
          if ((longlong *)((*(longlong *)(param_1 + 0x30) - *(longlong *)(param_1 + 0x28)) / 0x38)
              <= plVar10) {
            _invalid_parameter_noinfo();
          }
          lVar1 = *(longlong *)(param_1 + 0x28);
          if ((ulonglong)
              ((*(longlong *)(lVar8 + 0x28 + lVar1) - *(longlong *)(lVar8 + 0x20 + lVar1)) / 0x38)
              <= uVar9) {
            _invalid_parameter_noinfo();
          }
          if (*(int *)(*(longlong *)(lVar8 + 0x20 + lVar1) + lVar4) <= iVar5) break;
          if ((longlong *)((*(longlong *)(param_1 + 0x30) - *(longlong *)(param_1 + 0x28)) / 0x38)
              <= plVar10) {
            _invalid_parameter_noinfo();
          }
          lVar1 = *(longlong *)(param_1 + 0x28);
          if ((ulonglong)
              ((*(longlong *)(lVar8 + 0x28 + lVar1) - *(longlong *)(lVar8 + 0x20 + lVar1)) / 0x38)
              <= uVar9) {
            _invalid_parameter_noinfo();
          }
          lVar1 = *(longlong *)(lVar8 + 0x20 + lVar1);
          if ((ulonglong)
              (*(longlong *)(lVar1 + 0x28 + lVar4) - *(longlong *)(lVar1 + 0x20 + lVar4) >> 3) <=
              (ulonglong)(longlong)iVar5) {
            _invalid_parameter_noinfo();
          }
          FUN_140044700(param_2,(undefined8 *)
                                (*(longlong *)(lVar1 + 0x20 + lVar4) + (longlong)iVar5 * 8));
          iVar5 = iVar5 + 1;
        }
        iVar7 = iVar7 + 1;
        uVar9 = uVar9 + 1;
        lVar4 = lVar4 + 0x38;
      }
      iVar6 = iVar6 + 1;
      plVar10 = (longlong *)((longlong)plVar10 + 1);
      lVar8 = lVar8 + 0x38;
    } while (iVar6 < *(int *)(param_1 + 4) + 1);
  }
  return plVar3;
}


// ==== FUN_14006bdf0 @ 14006bdf0  undefined8 * FUN_14006bdf0(longlong param_1, undefined8 * param_2, longlong * param_3)

undefined8 * FUN_14006bdf0(longlong param_1,undefined8 *param_2,longlong *param_3)

{
  double dVar1;
  longlong *plVar2;
  double *pdVar3;
  double *pdVar4;
  uint uVar5;
  double *pdVar6;
  longlong lVar7;
  longlong lVar8;
  longlong **pplVar9;
  ulonglong uVar10;
  ulonglong uVar11;
  longlong *plVar12;
  uint uVar13;
  longlong *plVar15;
  ulonglong uVar16;
  longlong *local_f8 [3];
  double *local_e0;
  double *local_d8;
  longlong local_d0;
  longlong *local_c8;
  int local_c0;
  undefined4 local_bc;
  ulonglong local_b8;
  uint local_b0;
  longlong *local_a8;
  double *pdStack_a0;
  undefined8 local_98;
  longlong *local_88;
  double *pdStack_80;
  ulonglong uVar14;
  
  local_98 = 0xfffffffffffffffe;
  plVar15 = (longlong *)0x0;
  local_bc = 0;
  local_c8 = (longlong *)operator_new(8);
  local_f8[0] = plVar15;
  if (local_c8 != (longlong *)0x0) {
    *local_c8 = (longlong)local_f8;
    local_f8[0] = local_c8;
  }
  local_e0 = (double *)0x0;
  local_d8 = (double *)0x0;
  local_d0 = 0;
  if ((int)(param_3[4] - param_3[3] >> 3) == *(int *)(param_1 + 8)) {
    local_c0 = 0;
    local_b8 = 0;
    if (0 < *(int *)(param_1 + 4) + 1) {
      do {
        uVar11 = local_b8;
        uVar14 = 0;
        if (0 < (longlong)local_b8) {
          FUN_1400441e0(param_3,(longlong *)local_f8);
        }
        pdVar4 = local_d8;
        if (local_d8 < local_e0) {
          _invalid_parameter_noinfo();
        }
        pdVar3 = local_e0;
        if ((local_d8 < local_e0) &&
           ((_invalid_parameter_noinfo(), pdVar3 < local_e0 || (local_d8 < pdVar3)))) {
          _invalid_parameter_noinfo();
        }
        plVar12 = local_f8[0];
        if ((pdVar4 < local_e0) || (local_d8 < pdVar4)) {
          _invalid_parameter_noinfo();
        }
        if ((plVar12 == (longlong *)0x0) || (plVar12 != local_f8[0])) {
          _invalid_parameter_noinfo();
        }
        pdVar6 = local_d8;
        if (pdVar3 != pdVar4) {
          lVar7 = (longlong)local_d8 - (longlong)pdVar4 >> 3;
          pdVar6 = pdVar3 + lVar7;
          if (0 < lVar7) {
            memmove_s(pdVar3,lVar7 * 8,pdVar4,lVar7 * 8);
          }
        }
        local_d8 = pdVar6;
        uVar13 = 0;
        local_c8 = (longlong *)0x0;
        uVar16 = uVar14;
        while( true ) {
          plVar12 = local_c8;
          uVar10 = 0;
          if ((ulonglong)((*(longlong *)(param_1 + 0x30) - *(longlong *)(param_1 + 0x28)) / 0x38) <=
              uVar11) {
            _invalid_parameter_noinfo();
          }
          if (*(int *)((longlong)plVar15 + *(longlong *)(param_1 + 0x28)) <= (int)uVar14) break;
          if ((ulonglong)((*(longlong *)(param_1 + 0x30) - *(longlong *)(param_1 + 0x28)) / 0x38) <=
              uVar11) {
            _invalid_parameter_noinfo();
          }
          lVar7 = *(longlong *)(param_1 + 0x28);
          if ((longlong *)
              ((*(longlong *)(lVar7 + 0x28 + (longlong)plVar15) -
               *(longlong *)(lVar7 + 0x20 + (longlong)plVar15)) / 0x38) <= plVar12) {
            _invalid_parameter_noinfo();
          }
          local_b0 = *(int *)(uVar16 + *(longlong *)(lVar7 + 0x20 + (longlong)plVar15)) - 1;
          dVar1 = 0.0;
          if (0 < (int)local_b0) {
            uVar11 = (ulonglong)local_b0;
            dVar1 = 0.0;
            do {
              if ((ulonglong)(param_3[4] - param_3[3] >> 3) <= uVar10) {
                _invalid_parameter_noinfo();
              }
              lVar7 = param_3[3];
              if ((ulonglong)
                  ((*(longlong *)(param_1 + 0x30) - *(longlong *)(param_1 + 0x28)) / 0x38) <=
                  local_b8) {
                _invalid_parameter_noinfo();
              }
              lVar8 = *(longlong *)(param_1 + 0x28);
              if ((longlong *)
                  ((*(longlong *)(lVar8 + 0x28 + (longlong)plVar15) -
                   *(longlong *)(lVar8 + 0x20 + (longlong)plVar15)) / 0x38) <= local_c8) {
                _invalid_parameter_noinfo();
              }
              lVar8 = *(longlong *)(lVar8 + 0x20 + (longlong)plVar15);
              if ((ulonglong)
                  (*(longlong *)(uVar16 + 0x28 + lVar8) - *(longlong *)(uVar16 + 0x20 + lVar8) >> 3)
                  <= uVar10) {
                _invalid_parameter_noinfo();
              }
              dVar1 = dVar1 + *(double *)(*(longlong *)(uVar16 + 0x20 + lVar8) + uVar10 * 8) *
                              *(double *)(lVar7 + uVar10 * 8);
              uVar10 = uVar10 + 1;
              uVar11 = uVar11 - 1;
              plVar12 = local_c8;
            } while (uVar11 != 0);
          }
          uVar5 = local_b0;
          if ((ulonglong)((*(longlong *)(param_1 + 0x30) - *(longlong *)(param_1 + 0x28)) / 0x38) <=
              local_b8) {
            _invalid_parameter_noinfo();
          }
          lVar7 = *(longlong *)(param_1 + 0x28);
          if ((longlong *)
              ((*(longlong *)((longlong)plVar15 + lVar7 + 0x28) -
               *(longlong *)((longlong)plVar15 + lVar7 + 0x20)) / 0x38) <= plVar12) {
            _invalid_parameter_noinfo();
          }
          lVar7 = *(longlong *)((longlong)plVar15 + lVar7 + 0x20);
          if ((ulonglong)
              (*(longlong *)(uVar16 + 0x28 + lVar7) - *(longlong *)(uVar16 + 0x20 + lVar7) >> 3) <=
              (ulonglong)(longlong)(int)uVar5) {
            _invalid_parameter_noinfo();
          }
          dVar1 = exp(-(dVar1 - *(double *)
                                 (*(longlong *)(uVar16 + 0x20 + lVar7) + (longlong)(int)uVar5 * 8)))
          ;
          pdVar4 = local_d8;
          local_c8 = (longlong *)(1.0 / (dVar1 + 1.0));
          if (local_e0 == (double *)0x0) {
            uVar11 = 0;
          }
          else {
            uVar11 = local_d0 - (longlong)local_e0 >> 3;
          }
          if ((ulonglong)((longlong)local_d8 - (longlong)local_e0 >> 3) < uVar11) {
            *local_d8 = (double)local_c8;
            local_d8 = local_d8 + 1;
          }
          else {
            if (local_d8 < local_e0) {
              _invalid_parameter_noinfo();
            }
            pdVar3 = local_e0;
            plVar2 = local_f8[0];
            local_a8 = local_f8[0];
            pdStack_a0 = pdVar4;
            if (((longlong)local_d8 - (longlong)local_e0 & 0xfffffffffffffff8U) == 0) {
              lVar7 = 0;
            }
            else {
              if (local_d8 < local_e0) {
                _invalid_parameter_noinfo();
              }
              if ((plVar2 == (longlong *)0x0) || (plVar2 != local_f8[0])) {
                _invalid_parameter_noinfo();
              }
              lVar7 = (longlong)pdVar4 - (longlong)pdVar3 >> 3;
            }
            local_88 = local_a8;
            pdStack_80 = pdStack_a0;
            FUN_140043b40((longlong)local_f8,(longlong)&local_88,1,&local_c8);
            pdVar4 = local_e0;
            if (local_d8 < local_e0) {
              _invalid_parameter_noinfo();
            }
            plVar2 = local_f8[0];
            if (local_f8[0] == (longlong *)0x0) {
              _invalid_parameter_noinfo();
              lVar8 = 0;
            }
            else {
              lVar8 = *local_f8[0];
            }
            if (pdVar4 + lVar7 <= *(double **)(lVar8 + 0x20)) {
              if (plVar2 == (longlong *)0x0) {
                lVar8 = 0;
              }
              else {
                lVar8 = *plVar2;
              }
              if (*(double **)(lVar8 + 0x18) <= pdVar4 + lVar7) goto LAB_14006c34a;
            }
            _invalid_parameter_noinfo();
          }
LAB_14006c34a:
          uVar13 = uVar13 + 1;
          uVar14 = (ulonglong)uVar13;
          local_c8 = (longlong *)((longlong)plVar12 + 1);
          uVar16 = uVar16 + 0x38;
          uVar11 = local_b8;
        }
        local_c0 = local_c0 + 1;
        local_b8 = uVar11 + 1;
        plVar15 = plVar15 + 7;
      } while (local_c0 < *(int *)(param_1 + 4) + 1);
    }
    pplVar9 = local_f8;
    FUN_140043490(param_2,pplVar9);
    local_bc = 1;
    if (local_e0 != (double *)0x0) {
      operator_delete(local_e0);
    }
    local_e0 = (double *)0x0;
    local_d8 = (double *)0x0;
    local_d0 = 0;
    operator_delete(local_f8[0]);
  }
  else {
    pplVar9 = local_f8;
    FUN_140043490(param_2,pplVar9);
    local_bc = 1;
    if (local_e0 != (double *)0x0) {
      operator_delete(local_e0);
    }
    local_e0 = (double *)0x0;
    local_d8 = (double *)0x0;
    local_d0 = 0;
    operator_delete(local_f8[0]);
  }
  return pplVar9;
}


// ==== FUN_14006c420 @ 14006c420  undefined FUN_14006c420(undefined4 * param_1, longlong param_2, undefined4 * param_3)

void FUN_14006c420(undefined4 *param_1,longlong param_2,undefined4 *param_3)

{
  FUN_14006b520(param_1,param_2,param_3);
  return;
}


// ==== FUN_14006c440 @ 14006c440  undefined FUN_14006c440(undefined4 * param_1, undefined4 * param_2, undefined4 * param_3)

void FUN_14006c440(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  if (param_1 != param_2) {
    do {
      *param_1 = *param_3;
      FUN_1400441e0((longlong *)(param_1 + 2),(longlong *)(param_3 + 2));
      param_1 = param_1 + 0xe;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_14006c4a0 @ 14006c4a0  undefined FUN_14006c4a0(longlong param_1, longlong param_2, longlong param_3)

void FUN_14006c4a0(longlong param_1,longlong param_2,longlong param_3)

{
  FUN_14006b5f0(param_1,param_2,param_3);
  return;
}


// ==== FUN_14006c4c0 @ 14006c4c0  undefined FUN_14006c4c0(undefined4 * param_1, undefined4 * param_2, undefined4 * param_3)

void FUN_14006c4c0(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  FUN_140045400(param_1,param_2,param_3);
  return;
}


// ==== FUN_14006c4e0 @ 14006c4e0  undefined4 * FUN_14006c4e0(undefined8 param_1, undefined4 * param_2, longlong param_3, undefined4 * param_4)

undefined4 *
FUN_14006c4e0(undefined8 param_1,undefined4 *param_2,longlong param_3,undefined4 *param_4)

{
  FUN_14006b520(param_2,param_3,param_4);
  return param_2 + param_3 * 0xe;
}


// ==== FUN_14006c530 @ 14006c530  undefined FUN_14006c530(longlong param_1, longlong param_2, longlong param_3)

void FUN_14006c530(longlong param_1,longlong param_2,longlong param_3)

{
  FUN_14006b5f0(param_1,param_2,param_3);
  return;
}


// ==== FUN_14006c560 @ 14006c560  undefined FUN_14006c560(undefined4 * param_1, undefined4 * param_2, undefined4 * param_3)

void FUN_14006c560(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  FUN_140045400(param_1,param_2,param_3);
  return;
}


// ==== FUN_14006c580 @ 14006c580  undefined FUN_14006c580(undefined8 param_1, undefined4 * param_2, undefined4 * param_3, undefined4 * param_4)

void FUN_14006c580(undefined8 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  FUN_140045400(param_2,param_3,param_4);
  return;
}


// ==== FUN_14006c5c0 @ 14006c5c0  undefined FUN_14006c5c0(longlong param_1, longlong param_2, ulonglong param_3, undefined4 * param_4)

void FUN_14006c5c0(longlong param_1,longlong param_2,ulonglong param_3,undefined4 *param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  longlong lVar3;
  code *pcVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  undefined4 local_78 [2];
  void *local_70 [3];
  void *local_58;
  undefined8 local_50;
  undefined8 local_48;
  
  lVar2 = *(longlong *)(param_1 + 0x18);
  if (lVar2 == 0) {
    uVar7 = 0;
  }
  else {
    uVar7 = (*(longlong *)(param_1 + 0x28) - lVar2) / 0x38;
  }
  uVar8 = 0;
  if (param_3 != 0) {
    lVar2 = (*(longlong *)(param_1 + 0x20) - lVar2) / 0x38;
    if (0x492492492492492U - lVar2 < param_3) {
      FUN_14003fa00();
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    uVar1 = lVar2 + param_3;
    if (uVar7 < uVar1) {
      if (uVar7 <= 0x492492492492492 - (uVar7 >> 1)) {
        uVar8 = uVar7 + (uVar7 >> 1);
      }
      if (uVar8 < uVar1) {
        uVar8 = uVar1;
      }
      puVar5 = (undefined4 *)FUN_140040d80(param_1 + 0x10,uVar8);
      lVar2 = (*(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18)) / 0x38;
      FUN_14006b520(puVar5 + lVar2 * 0xe,param_3,param_4);
      FUN_140045400(*(undefined4 **)(param_1 + 0x18),*(undefined4 **)(param_2 + 8),puVar5);
      FUN_140045400(*(undefined4 **)(param_2 + 8),*(undefined4 **)(param_1 + 0x20),
                    puVar5 + (lVar2 + param_3) * 0xe);
      lVar2 = *(longlong *)(param_1 + 0x18);
      lVar3 = *(longlong *)(param_1 + 0x20);
      if (lVar2 != 0) {
        FUN_140044a90(lVar2,*(longlong *)(param_1 + 0x20));
        operator_delete(*(void **)(param_1 + 0x18));
      }
      *(undefined4 **)(param_1 + 0x28) = puVar5 + uVar8 * 0xe;
      *(undefined4 **)(param_1 + 0x20) = puVar5 + (param_3 + (lVar3 - lVar2) / 0x38) * 0xe;
      *(undefined4 **)(param_1 + 0x18) = puVar5;
    }
    else if ((ulonglong)((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_2 + 8)) / 0x38) <
             param_3) {
      local_78[0] = *param_4;
      FUN_140043490(local_70,(undefined8 *)(param_4 + 2));
      FUN_140045400(*(undefined4 **)(param_2 + 8),*(undefined4 **)(param_1 + 0x20),
                    *(undefined4 **)(param_2 + 8) + param_3 * 0xe);
      FUN_14006b520(*(undefined4 **)(param_1 + 0x20),
                    param_3 - ((longlong)*(undefined4 **)(param_1 + 0x20) -
                              *(longlong *)(param_2 + 8)) / 0x38,local_78);
      *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + param_3 * 0x38;
      lVar2 = *(longlong *)(param_1 + 0x20);
      for (puVar5 = *(undefined4 **)(param_2 + 8); puVar5 != (undefined4 *)(lVar2 + param_3 * -0x38)
          ; puVar5 = puVar5 + 0xe) {
        *puVar5 = local_78[0];
        FUN_1400441e0((longlong *)(puVar5 + 2),(longlong *)local_70);
      }
      if (local_58 != (void *)0x0) {
        operator_delete(local_58);
      }
      local_58 = (void *)0x0;
      local_50 = 0;
      local_48 = 0;
      operator_delete(local_70[0]);
    }
    else {
      local_78[0] = *param_4;
      FUN_140043490(local_70,(undefined8 *)(param_4 + 2));
      puVar5 = *(undefined4 **)(param_1 + 0x20);
      puVar6 = FUN_140045400(puVar5 + param_3 * -0xe,puVar5,puVar5);
      *(undefined4 **)(param_1 + 0x20) = puVar6;
      FUN_14006b5f0(*(longlong *)(param_2 + 8),(longlong)(puVar5 + param_3 * -0xe),(longlong)puVar5)
      ;
      puVar6 = *(undefined4 **)(param_2 + 8);
      puVar5 = puVar6 + param_3 * 0xe;
      for (; puVar6 != puVar5; puVar6 = puVar6 + 0xe) {
        *puVar6 = local_78[0];
        FUN_1400441e0((longlong *)(puVar6 + 2),(longlong *)local_70);
      }
      if (local_58 != (void *)0x0) {
        operator_delete(local_58);
      }
      local_58 = (void *)0x0;
      local_50 = 0;
      local_48 = 0;
      operator_delete(local_70[0]);
    }
  }
  return;
}


// ==== FUN_14006ca00 @ 14006ca00  longlong * FUN_14006ca00(longlong * param_1, longlong * param_2, longlong * param_3, undefined4 * param_4)

longlong * FUN_14006ca00(longlong *param_1,longlong *param_2,longlong *param_3,undefined4 *param_4)

{
  longlong *plVar1;
  longlong lVar2;
  longlong lVar3;
  ulonglong uVar4;
  longlong lVar5;
  longlong lVar6;
  longlong *local_28;
  ulonglong uStack_20;
  
  uVar4 = param_1[3];
  lVar5 = param_1[4] - uVar4;
  lVar2 = 0;
  lVar6 = lVar5 >> 0x3f;
  lVar3 = lVar2;
  if (lVar5 / 0x38 + lVar6 != lVar6) {
    if ((ulonglong)param_1[4] < uVar4) {
      _invalid_parameter_noinfo();
    }
    if ((*param_3 == 0) || (*param_3 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    lVar3 = (longlong)(param_3[1] - uVar4) / 0x38;
  }
  local_28 = (longlong *)*param_3;
  uStack_20 = param_3[1];
  FUN_14006c5c0((longlong)param_1,(longlong)&local_28,1,param_4);
  uVar4 = param_1[3];
  if ((ulonglong)param_1[4] < uVar4) {
    _invalid_parameter_noinfo();
  }
  plVar1 = (longlong *)*param_1;
  local_28 = plVar1;
  uStack_20 = uVar4;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar6 = lVar2;
  }
  else {
    lVar6 = *plVar1;
  }
  uVar4 = lVar3 * 0x38 + uVar4;
  if (uVar4 <= *(ulonglong *)(lVar6 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar2 = *plVar1;
    }
    if (*(ulonglong *)(lVar2 + 0x18) <= uVar4) goto LAB_14006cb22;
  }
  _invalid_parameter_noinfo();
LAB_14006cb22:
  *param_2 = (longlong)local_28;
  param_2[1] = uVar4;
  return param_2;
}


// ==== FUN_14006cb60 @ 14006cb60  undefined4 * FUN_14006cb60(longlong param_1, longlong param_2, undefined4 * param_3)

undefined4 * FUN_14006cb60(longlong param_1,longlong param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  longlong lVar2;
  
  puVar1 = param_3;
  if (param_1 != param_2) {
    do {
      lVar2 = param_2 + -0x38;
      param_3 = puVar1 + -0xe;
      *param_3 = *(undefined4 *)(param_2 + -0x38);
      FUN_1400465d0((longlong *)(puVar1 + -0xc),(longlong *)(param_2 + -0x30));
      puVar1 = param_3;
      param_2 = lVar2;
    } while (lVar2 != param_1);
  }
  return param_3;
}


// ==== FUN_14006cbc0 @ 14006cbc0  undefined FUN_14006cbc0(longlong * param_1, undefined4 * param_2)

void FUN_14006cbc0(longlong *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  ulonglong uVar3;
  longlong local_28;
  undefined4 *puStack_20;
  longlong local_18 [2];
  
  puVar1 = (undefined4 *)param_1[3];
  if (puVar1 == (undefined4 *)0x0) {
    uVar3 = 0;
  }
  else {
    uVar3 = (param_1[5] - (longlong)puVar1) / 0x38;
  }
  puVar2 = (undefined4 *)param_1[4];
  if ((ulonglong)(((longlong)puVar2 - (longlong)puVar1) / 0x38) < uVar3) {
    FUN_14006b520(puVar2,1,param_2);
    param_1[4] = (longlong)(puVar2 + 0xe);
    return;
  }
  if (puVar2 < puVar1) {
    _invalid_parameter_noinfo();
  }
  local_28 = *param_1;
  puStack_20 = puVar2;
  FUN_14006ca00(param_1,local_18,&local_28,param_2);
  return;
}


// ==== FUN_14006ccc0 @ 14006ccc0  undefined FUN_14006ccc0(undefined4 * param_1, undefined4 * param_2, undefined4 * param_3)

void FUN_14006ccc0(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  if (param_1 != param_2) {
    do {
      *param_1 = *param_3;
      FUN_1400465d0((longlong *)(param_1 + 2),(longlong *)(param_3 + 2));
      param_1 = param_1 + 0xe;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_14006cd20 @ 14006cd20  longlong FUN_14006cd20(longlong param_1, longlong param_2, longlong param_3)

longlong FUN_14006cd20(longlong param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  longlong lVar2;
  
  if (param_1 != param_2) {
    lVar1 = param_2;
    do {
      lVar2 = lVar1 + -0x38;
      *(undefined4 *)((param_3 - param_2) + lVar2) = *(undefined4 *)(lVar1 + -0x38);
      FUN_1400465d0((longlong *)((param_3 - param_2) + lVar1 + -0x30),(longlong *)(lVar1 + -0x30));
      lVar1 = lVar2;
    } while (lVar2 != param_1);
  }
  return param_3 + ((param_2 - param_1) / 0x38) * -0x38;
}


// ==== FUN_14006cdb0 @ 14006cdb0  uint * FUN_14006cdb0(uint * param_1, uint param_2, int param_3)

uint * FUN_14006cdb0(uint *param_1,uint param_2,int param_3)

{
  uint *puVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  uint *puVar4;
  ulonglong uVar5;
  uint local_50 [2];
  void *local_48;
  void *local_30;
  undefined8 local_28;
  undefined8 local_20;
  
  uVar5 = (ulonglong)param_2;
  puVar1 = param_1 + 2;
  puVar2 = (undefined8 *)operator_new(8);
  puVar3 = (undefined8 *)0x0;
  if (puVar2 != (undefined8 *)0x0) {
    *puVar2 = puVar1;
    puVar3 = puVar2;
  }
  *(undefined8 **)puVar1 = puVar3;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  *param_1 = param_2;
  if (0 < (int)param_2) {
    do {
      puVar4 = FUN_14006b680(local_50,param_3);
      FUN_14006cbc0((longlong *)puVar1,puVar4);
      if (local_30 != (void *)0x0) {
        operator_delete(local_30);
      }
      local_30 = (void *)0x0;
      local_28 = 0;
      local_20 = 0;
      operator_delete(local_48);
      uVar5 = uVar5 - 1;
    } while (uVar5 != 0);
  }
  return param_1;
}


// ==== FUN_14006cea0 @ 14006cea0  undefined FUN_14006cea0(undefined4 * param_1, undefined4 * param_2, undefined4 * param_3)

void FUN_14006cea0(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  if (param_1 != param_2) {
    do {
      *param_1 = *param_3;
      FUN_1400465d0((longlong *)(param_1 + 2),(longlong *)(param_3 + 2));
      param_1 = param_1 + 0xe;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_14006cf00 @ 14006cf00  undefined FUN_14006cf00(longlong param_1, longlong param_2, longlong param_3)

void FUN_14006cf00(longlong param_1,longlong param_2,longlong param_3)

{
  FUN_14006cd20(param_1,param_2,param_3);
  return;
}


// ==== FUN_14006cf20 @ 14006cf20  undefined FUN_14006cf20(longlong param_1, longlong param_2, longlong param_3)

void FUN_14006cf20(longlong param_1,longlong param_2,longlong param_3)

{
  FUN_14006cd20(param_1,param_2,param_3);
  return;
}


// ==== FUN_14006cf50 @ 14006cf50  undefined FUN_14006cf50(undefined4 * param_1, longlong param_2, undefined4 * param_3)

void FUN_14006cf50(undefined4 *param_1,longlong param_2,undefined4 *param_3)

{
  for (; param_2 != 0; param_2 = param_2 + -1) {
    if (param_1 != (undefined4 *)0x0) {
      *param_1 = *param_3;
      FUN_140045e80((undefined8 *)(param_1 + 2),(longlong)(param_3 + 2));
    }
    param_1 = param_1 + 0xe;
  }
  return;
}


// ==== FUN_14006cfc0 @ 14006cfc0  undefined FUN_14006cfc0(undefined4 * param_1, longlong param_2, undefined4 * param_3)

void FUN_14006cfc0(undefined4 *param_1,longlong param_2,undefined4 *param_3)

{
  FUN_14006cf50(param_1,param_2,param_3);
  return;
}


// ==== FUN_14006cfe0 @ 14006cfe0  undefined FUN_14006cfe0(undefined4 * param_1, undefined4 * param_2, undefined4 * param_3)

void FUN_14006cfe0(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  FUN_1400469b0(param_1,param_2,param_3);
  return;
}


// ==== FUN_14006d000 @ 14006d000  undefined4 * FUN_14006d000(undefined8 param_1, undefined4 * param_2, longlong param_3, undefined4 * param_4)

undefined4 *
FUN_14006d000(undefined8 param_1,undefined4 *param_2,longlong param_3,undefined4 *param_4)

{
  FUN_14006cf50(param_2,param_3,param_4);
  return param_2 + param_3 * 0xe;
}


// ==== FUN_14006d050 @ 14006d050  undefined FUN_14006d050(undefined4 * param_1, undefined4 * param_2, undefined4 * param_3)

void FUN_14006d050(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  FUN_1400469b0(param_1,param_2,param_3);
  return;
}


// ==== FUN_14006d070 @ 14006d070  undefined FUN_14006d070(undefined8 param_1, undefined4 * param_2, undefined4 * param_3, undefined4 * param_4)

void FUN_14006d070(undefined8 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  FUN_1400469b0(param_2,param_3,param_4);
  return;
}


// ==== FUN_14006d0b0 @ 14006d0b0  undefined FUN_14006d0b0(longlong param_1, longlong param_2, ulonglong param_3, undefined4 * param_4)

void FUN_14006d0b0(longlong param_1,longlong param_2,ulonglong param_3,undefined4 *param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  longlong lVar3;
  code *pcVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  undefined4 local_78 [2];
  void *local_70 [3];
  void *local_58;
  longlong local_50;
  undefined8 local_48;
  
  lVar2 = *(longlong *)(param_1 + 0x18);
  if (lVar2 == 0) {
    uVar7 = 0;
  }
  else {
    uVar7 = (*(longlong *)(param_1 + 0x28) - lVar2) / 0x38;
  }
  uVar8 = 0;
  if (param_3 != 0) {
    lVar2 = (*(longlong *)(param_1 + 0x20) - lVar2) / 0x38;
    if (0x492492492492492U - lVar2 < param_3) {
      FUN_14003ed30();
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    uVar1 = lVar2 + param_3;
    if (uVar7 < uVar1) {
      if (uVar7 <= 0x492492492492492 - (uVar7 >> 1)) {
        uVar8 = uVar7 + (uVar7 >> 1);
      }
      if (uVar8 < uVar1) {
        uVar8 = uVar1;
      }
      puVar5 = (undefined4 *)FUN_140040260(param_1 + 0x10,uVar8);
      lVar2 = (*(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18)) / 0x38;
      FUN_14006cf50(puVar5 + lVar2 * 0xe,param_3,param_4);
      FUN_1400469b0(*(undefined4 **)(param_1 + 0x18),*(undefined4 **)(param_2 + 8),puVar5);
      FUN_1400469b0(*(undefined4 **)(param_2 + 8),*(undefined4 **)(param_1 + 0x20),
                    puVar5 + (lVar2 + param_3) * 0xe);
      lVar2 = *(longlong *)(param_1 + 0x18);
      lVar3 = *(longlong *)(param_1 + 0x20);
      if (lVar2 != 0) {
        FUN_140046b40(lVar2,*(longlong *)(param_1 + 0x20));
        operator_delete(*(void **)(param_1 + 0x18));
      }
      *(undefined4 **)(param_1 + 0x28) = puVar5 + uVar8 * 0xe;
      *(undefined4 **)(param_1 + 0x20) = puVar5 + (param_3 + (lVar3 - lVar2) / 0x38) * 0xe;
      *(undefined4 **)(param_1 + 0x18) = puVar5;
    }
    else if ((ulonglong)((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_2 + 8)) / 0x38) <
             param_3) {
      local_78[0] = *param_4;
      FUN_140045e80(local_70,(longlong)(param_4 + 2));
      FUN_1400469b0(*(undefined4 **)(param_2 + 8),*(undefined4 **)(param_1 + 0x20),
                    *(undefined4 **)(param_2 + 8) + param_3 * 0xe);
      FUN_14006cf50(*(undefined4 **)(param_1 + 0x20),
                    param_3 - ((longlong)*(undefined4 **)(param_1 + 0x20) -
                              *(longlong *)(param_2 + 8)) / 0x38,local_78);
      *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + param_3 * 0x38;
      lVar2 = *(longlong *)(param_1 + 0x20);
      for (puVar5 = *(undefined4 **)(param_2 + 8); puVar5 != (undefined4 *)(lVar2 + param_3 * -0x38)
          ; puVar5 = puVar5 + 0xe) {
        *puVar5 = local_78[0];
        FUN_1400465d0((longlong *)(puVar5 + 2),(longlong *)local_70);
      }
      if (local_58 != (void *)0x0) {
        FUN_140044a90((longlong)local_58,local_50);
        operator_delete(local_58);
      }
      local_58 = (void *)0x0;
      local_50 = 0;
      local_48 = 0;
      operator_delete(local_70[0]);
    }
    else {
      local_78[0] = *param_4;
      FUN_140045e80(local_70,(longlong)(param_4 + 2));
      puVar5 = *(undefined4 **)(param_1 + 0x20);
      puVar6 = FUN_1400469b0(puVar5 + param_3 * -0xe,puVar5,puVar5);
      *(undefined4 **)(param_1 + 0x20) = puVar6;
      FUN_14006cd20(*(longlong *)(param_2 + 8),(longlong)(puVar5 + param_3 * -0xe),(longlong)puVar5)
      ;
      puVar6 = *(undefined4 **)(param_2 + 8);
      puVar5 = puVar6 + param_3 * 0xe;
      for (; puVar6 != puVar5; puVar6 = puVar6 + 0xe) {
        *puVar6 = local_78[0];
        FUN_1400465d0((longlong *)(puVar6 + 2),(longlong *)local_70);
      }
      if (local_58 != (void *)0x0) {
        FUN_140044a90((longlong)local_58,local_50);
        operator_delete(local_58);
      }
      local_58 = (void *)0x0;
      local_50 = 0;
      local_48 = 0;
      operator_delete(local_70[0]);
    }
  }
  return;
}


// ==== FUN_14006d530 @ 14006d530  longlong * FUN_14006d530(longlong * param_1, longlong * param_2, longlong * param_3, undefined4 * param_4)

longlong * FUN_14006d530(longlong *param_1,longlong *param_2,longlong *param_3,undefined4 *param_4)

{
  longlong *plVar1;
  longlong lVar2;
  longlong lVar3;
  ulonglong uVar4;
  longlong lVar5;
  longlong lVar6;
  longlong *local_28;
  ulonglong uStack_20;
  
  uVar4 = param_1[3];
  lVar5 = param_1[4] - uVar4;
  lVar2 = 0;
  lVar6 = lVar5 >> 0x3f;
  lVar3 = lVar2;
  if (lVar5 / 0x38 + lVar6 != lVar6) {
    if ((ulonglong)param_1[4] < uVar4) {
      _invalid_parameter_noinfo();
    }
    if ((*param_3 == 0) || (*param_3 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    lVar3 = (longlong)(param_3[1] - uVar4) / 0x38;
  }
  local_28 = (longlong *)*param_3;
  uStack_20 = param_3[1];
  FUN_14006d0b0((longlong)param_1,(longlong)&local_28,1,param_4);
  uVar4 = param_1[3];
  if ((ulonglong)param_1[4] < uVar4) {
    _invalid_parameter_noinfo();
  }
  plVar1 = (longlong *)*param_1;
  local_28 = plVar1;
  uStack_20 = uVar4;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar6 = lVar2;
  }
  else {
    lVar6 = *plVar1;
  }
  uVar4 = lVar3 * 0x38 + uVar4;
  if (uVar4 <= *(ulonglong *)(lVar6 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar2 = *plVar1;
    }
    if (*(ulonglong *)(lVar2 + 0x18) <= uVar4) goto LAB_14006d652;
  }
  _invalid_parameter_noinfo();
LAB_14006d652:
  *param_2 = (longlong)local_28;
  param_2[1] = uVar4;
  return param_2;
}


// ==== FUN_14006d690 @ 14006d690  undefined FUN_14006d690(longlong * param_1, undefined4 * param_2)

void FUN_14006d690(longlong *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  ulonglong uVar3;
  longlong local_28;
  undefined4 *puStack_20;
  longlong local_18 [2];
  
  puVar1 = (undefined4 *)param_1[3];
  if (puVar1 == (undefined4 *)0x0) {
    uVar3 = 0;
  }
  else {
    uVar3 = (param_1[5] - (longlong)puVar1) / 0x38;
  }
  puVar2 = (undefined4 *)param_1[4];
  if ((ulonglong)(((longlong)puVar2 - (longlong)puVar1) / 0x38) < uVar3) {
    FUN_14006cf50(puVar2,1,param_2);
    param_1[4] = (longlong)(puVar2 + 0xe);
    return;
  }
  if (puVar2 < puVar1) {
    _invalid_parameter_noinfo();
  }
  local_28 = *param_1;
  puStack_20 = puVar2;
  FUN_14006d530(param_1,local_18,&local_28,param_2);
  return;
}


// ==== FUN_14006d790 @ 14006d790  undefined FUN_14006d790(uint * param_1)

void FUN_14006d790(uint *param_1)

{
  uint *puVar1;
  int iVar2;
  uint local_50 [2];
  void *local_48;
  void *local_30;
  longlong local_28;
  undefined8 local_20;
  
  FUN_140046ea0((longlong *)(param_1 + 4));
  if ((int)param_1[1] < 1) {
    puVar1 = FUN_14006cdb0(local_50,param_1[3],param_1[2]);
    FUN_14006d690((longlong *)(param_1 + 4),puVar1);
    if (local_30 != (void *)0x0) {
      FUN_140044a90((longlong)local_30,local_28);
      operator_delete(local_30);
    }
    local_30 = (void *)0x0;
    local_28 = 0;
    local_20 = 0;
    operator_delete(local_48);
  }
  else {
    puVar1 = FUN_14006cdb0(local_50,*param_1,param_1[2]);
    FUN_14006d690((longlong *)(param_1 + 4),puVar1);
    if (local_30 != (void *)0x0) {
      FUN_140044a90((longlong)local_30,local_28);
      operator_delete(local_30);
    }
    iVar2 = 0;
    local_30 = (void *)0x0;
    local_28 = 0;
    local_20 = 0;
    operator_delete(local_48);
    if (0 < (int)(param_1[1] - 1)) {
      do {
        puVar1 = FUN_14006cdb0(local_50,*param_1,*param_1);
        FUN_14006d690((longlong *)(param_1 + 4),puVar1);
        if (local_30 != (void *)0x0) {
          FUN_140044a90((longlong)local_30,local_28);
          operator_delete(local_30);
        }
        local_30 = (void *)0x0;
        local_28 = 0;
        local_20 = 0;
        operator_delete(local_48);
        iVar2 = iVar2 + 1;
      } while (iVar2 < (int)(param_1[1] - 1));
    }
    puVar1 = FUN_14006cdb0(local_50,param_1[3],*param_1);
    FUN_14006d690((longlong *)(param_1 + 4),puVar1);
    if (local_30 != (void *)0x0) {
      FUN_140044a90((longlong)local_30,local_28);
      operator_delete(local_30);
    }
    local_30 = (void *)0x0;
    local_28 = 0;
    local_20 = 0;
    operator_delete(local_48);
  }
  return;
}


// ==== FUN_14006d9d0 @ 14006d9d0  uint * FUN_14006d9d0(uint * param_1, uint param_2, uint param_3, uint param_4, uint param_5)

uint * FUN_14006d9d0(uint *param_1,uint param_2,uint param_3,uint param_4,uint param_5)

{
  longlong *plVar1;
  longlong *plVar2;
  
  plVar1 = (longlong *)operator_new(8);
  plVar2 = (longlong *)0x0;
  if (plVar1 != (longlong *)0x0) {
    *plVar1 = (longlong)(param_1 + 4);
    plVar2 = plVar1;
  }
  *(longlong **)(param_1 + 4) = plVar2;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  *param_1 = param_5;
  param_1[1] = param_4;
  param_1[2] = param_2;
  param_1[3] = param_3;
  FUN_14006d790(param_1);
  return param_1;
}


// ==== FUN_14006da90 @ 14006da90  undefined FUN_14006da90(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_1)

void FUN_14006da90(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                   *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00014006daa6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(param_1);
  return;
}


// ==== FUN_14006dab0 @ 14006dab0  undefined FUN_14006dab0(undefined8 * param_1)

void FUN_14006dab0(undefined8 *param_1)

{
  *param_1 = IMessagePort::vftable;
  return;
}


// ==== FUN_14006dd80 @ 14006dd80  uint FUN_14006dd80(uint param_1)

uint FUN_14006dd80(uint param_1)

{
  uint local_28 [10];
  
  if (param_1 < 60000) {
    return param_1;
  }
  if (param_1 == 0xea65) {
    return 4;
  }
  local_28[0] = 1;
  local_28[1] = 1;
  local_28[2] = 2;
  local_28[3] = 2;
  local_28[4] = 4;
  local_28[5] = 4;
  local_28[6] = 4;
  local_28[7] = 8;
  if (param_1 - 0xea61 < 8) {
    return local_28[(int)(param_1 - 0xea61)];
  }
  log_InlineLogERROR("IMessagePort::SIZE_OF_TYPE() has a bad type=%d");
  return 0;
}


// ==== FUN_14006de90 @ 14006de90  longlong FUN_14006de90(longlong param_1, ulonglong param_2)

longlong FUN_14006de90(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)(*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18) >> 3) <= param_2) {
    _invalid_parameter_noinfo();
  }
  return *(longlong *)(param_1 + 0x18) + param_2 * 8;
}


// ==== FUN_14006df30 @ 14006df30  longlong FUN_14006df30(longlong * param_1)

longlong FUN_14006df30(longlong *param_1)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  ulonglong uVar6;
  
  uVar1 = param_1[1];
  plVar2 = (longlong *)*param_1;
  lVar5 = 0;
  uVar6 = uVar1 >> 1;
  lVar3 = lVar5;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar2 = (longlong *)*param_1;
    lVar4 = lVar5;
    if (plVar2 == (longlong *)0x0) goto LAB_14006df7f;
  }
  lVar4 = *plVar2;
  if (plVar2 != (longlong *)0x0) {
    lVar3 = lVar4;
  }
LAB_14006df7f:
  if ((ulonglong)(*(longlong *)(lVar3 + 0x38) + *(longlong *)(lVar4 + 0x30)) <=
      (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)*param_1;
  lVar3 = lVar5;
  if (plVar2 != (longlong *)0x0) {
    lVar3 = *plVar2;
  }
  if (*(ulonglong *)(lVar3 + 0x28) <= uVar6) {
    lVar3 = lVar5;
    if (plVar2 != (longlong *)0x0) {
      lVar3 = *plVar2;
    }
    uVar6 = uVar6 - *(longlong *)(lVar3 + 0x28);
  }
  if (plVar2 != (longlong *)0x0) {
    lVar5 = *plVar2;
  }
  return *(longlong *)(*(longlong *)(lVar5 + 0x20) + uVar6 * 8) + (ulonglong)((uint)uVar1 & 1) * 8;
}


// ==== FUN_14006dff0 @ 14006dff0  longlong * FUN_14006dff0(longlong * param_1)

longlong * FUN_14006dff0(longlong *param_1)

{
  longlong *plVar1;
  longlong lVar2;
  longlong lVar3;
  
  plVar1 = (longlong *)*param_1;
  lVar3 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar1 = (longlong *)*param_1;
    lVar2 = lVar3;
    if (plVar1 == (longlong *)0x0) goto LAB_14006e023;
  }
  lVar2 = *plVar1;
  if (plVar1 != (longlong *)0x0) {
    lVar3 = lVar2;
  }
LAB_14006e023:
  if ((ulonglong)(*(longlong *)(lVar3 + 0x38) + *(longlong *)(lVar2 + 0x30)) <=
      (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + 1;
  return param_1;
}


// ==== FUN_14006e050 @ 14006e050  bool FUN_14006e050(longlong * param_1, longlong * param_2)

bool FUN_14006e050(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_14006e090 @ 14006e090  longlong FUN_14006e090(longlong * param_1)

longlong FUN_14006e090(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14006e0b2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14006e0b2:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_14006e0d0 @ 14006e0d0  longlong * FUN_14006e0d0(longlong * param_1)

longlong * FUN_14006e0d0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14006e0f2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14006e0f2:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + 8;
  return param_1;
}


// ==== FUN_14006e110 @ 14006e110  bool FUN_14006e110(longlong * param_1, longlong * param_2)

bool FUN_14006e110(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_14006e150 @ 14006e150  undefined FUN_14006e150(void)

void FUN_14006e150(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [48];
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_70,"deque<T> too long");
  std::exception::exception((exception *)local_48);
  local_48[0] = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
  local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
}


// ==== FUN_14006e1f0 @ 14006e1f0  undefined FUN_14006e1f0(void)

void FUN_14006e1f0(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [48];
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_70,"vector<T> too long");
  std::exception::exception((exception *)local_48);
  local_48[0] = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
  local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
}


// ==== FUN_14006e280 @ 14006e280  longlong * FUN_14006e280(longlong * param_1, longlong param_2)

longlong * FUN_14006e280(longlong *param_1,longlong param_2)

{
  longlong *plVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  
  plVar1 = (longlong *)*param_1;
  lVar3 = 0;
  lVar2 = lVar3;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar1 = (longlong *)*param_1;
    lVar4 = lVar3;
    if (plVar1 != (longlong *)0x0) goto LAB_14006e2b0;
  }
  else {
LAB_14006e2b0:
    lVar4 = *plVar1;
    if (plVar1 != (longlong *)0x0) {
      lVar2 = lVar4;
    }
  }
  if ((ulonglong)(param_1[1] + param_2) <=
      (ulonglong)(*(longlong *)(lVar2 + 0x38) + *(longlong *)(lVar4 + 0x30))) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x30) <= (ulonglong)(param_1[1] + param_2)) goto LAB_14006e2e8;
  }
  _invalid_parameter_noinfo();
LAB_14006e2e8:
  param_1[1] = param_1[1] + param_2;
  return param_1;
}


// ==== FUN_14006e300 @ 14006e300  longlong FUN_14006e300(longlong * param_1, longlong * param_2)

longlong FUN_14006e300(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] - param_2[1] >> 3;
}


// ==== FUN_14006e380 @ 14006e380  longlong * FUN_14006e380(longlong * param_1, longlong param_2)

longlong * FUN_14006e380(longlong *param_1,longlong param_2)

{
  FUN_14006e280(param_1,param_2);
  return param_1;
}


// ==== FUN_14006e3a0 @ 14006e3a0  longlong FUN_14006e3a0(longlong * param_1, longlong * param_2)

longlong FUN_14006e3a0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] - param_2[1];
}


// ==== FUN_14006e3e0 @ 14006e3e0  longlong * FUN_14006e3e0(longlong * param_1, longlong param_2)

longlong * FUN_14006e3e0(longlong *param_1,longlong param_2)

{
  longlong *plVar1;
  ulonglong uVar2;
  longlong lVar3;
  longlong lVar4;
  
  plVar1 = (longlong *)*param_1;
  lVar3 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar1 = (longlong *)*param_1;
    lVar4 = lVar3;
    if (plVar1 != (longlong *)0x0) goto LAB_14006e410;
  }
  else {
LAB_14006e410:
    lVar4 = *plVar1;
  }
  uVar2 = param_1[1] + param_2 * 8;
  if (uVar2 <= *(ulonglong *)(lVar4 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar2) goto LAB_14006e438;
  }
  _invalid_parameter_noinfo();
LAB_14006e438:
  param_1[1] = param_1[1] + param_2 * 8;
  return param_1;
}


// ==== FUN_14006e450 @ 14006e450  undefined FUN_14006e450(ulonglong param_1)

void FUN_14006e450(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 8)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 << 3);
  return;
}


