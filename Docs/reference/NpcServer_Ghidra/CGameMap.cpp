// NpcServer.exe :: CGameMap  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CGameMap::vf_0x30 @ 1400525d0  undefined8 vf_0x30(longlong param_1)

undefined8 CGameMap::vf_0x30(longlong param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  longlong *plVar3;
  longlong lVar4;
  longlong *plVar5;
  ulonglong uVar6;
  longlong *plVar7;
  undefined8 extraout_RAX;
  int iVar8;
  ulonglong uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  longlong lVar12;
  ulonglong uVar13;
  int iVar14;
  longlong *local_res18;
  ulonglong local_res20;
  longlong *local_f8 [3];
  undefined4 *local_e0;
  undefined4 *local_d8;
  longlong local_d0;
  longlong *local_c8 [3];
  undefined4 *local_b0;
  undefined4 *local_a8;
  longlong local_a0;
  longlong local_98;
  longlong *local_88;
  undefined4 *puStack_80;
  longlong *local_78;
  undefined4 *puStack_70;
  longlong *local_68;
  undefined4 *puStack_60;
  longlong *local_58;
  undefined4 *puStack_50;
  undefined8 local_48;
  
  local_48 = 0xfffffffffffffffe;
  local_res18 = (longlong *)operator_new(8);
  if (local_res18 == (longlong *)0x0) {
    local_c8[0] = (longlong *)0x0;
  }
  else {
    *local_res18 = (longlong)local_c8;
    local_c8[0] = local_res18;
  }
  local_b0 = (undefined4 *)0x0;
  local_a8 = (undefined4 *)0x0;
  local_a0 = 0;
  local_res18 = (longlong *)operator_new(8);
  if (local_res18 == (longlong *)0x0) {
    local_f8[0] = (longlong *)0x0;
  }
  else {
    *local_res18 = (longlong)local_f8;
    local_f8[0] = local_res18;
  }
  local_e0 = (undefined4 *)0x0;
  local_d8 = (undefined4 *)0x0;
  local_d0 = 0;
  iVar8 = 0;
  local_res20 = 0;
  if (0 < (int)((*(longlong *)(param_1 + 0x38) - *(longlong *)(param_1 + 0x30)) / 0x30)) {
    local_98 = 0;
    do {
      iVar14 = 0;
      lVar12 = local_98;
      while( true ) {
        if ((ulonglong)((*(longlong *)(param_1 + 0x38) - *(longlong *)(param_1 + 0x30)) / 0x30) <=
            local_res20) {
          _invalid_parameter_noinfo();
        }
        if ((int)((*(longlong *)(lVar12 + 0x20 + *(longlong *)(param_1 + 0x30)) -
                  *(longlong *)(lVar12 + 0x18 + *(longlong *)(param_1 + 0x30))) / 0x18) <= iVar14)
        break;
        if ((ulonglong)((*(longlong *)(param_1 + 0x38) - *(longlong *)(param_1 + 0x30)) / 0x30) <=
            local_res20) {
          _invalid_parameter_noinfo();
        }
        lVar4 = *(longlong *)(param_1 + 0x30);
        uVar13 = (ulonglong)iVar14;
        if ((ulonglong)
            ((*(longlong *)(lVar12 + 0x20 + lVar4) - *(longlong *)(lVar12 + 0x18 + lVar4)) / 0x18)
            <= uVar13) {
          _invalid_parameter_noinfo();
        }
        plVar3 = (longlong *)FUN_1400678a0(*(longlong *)(lVar12 + 0x18 + lVar4) + uVar13 * 0x18);
        uVar9 = 0;
        lVar4 = (**(code **)(*plVar3 + 0x10))(plVar3);
        if (lVar4 != 0) {
          do {
            plVar5 = (longlong *)
                     (**(code **)(*plVar3 + 0x18))
                               (plVar3,uVar9,
                                "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\gamemap.cpp"
                                ,0x2ec);
            if (plVar5 != (longlong *)0x0) {
              uVar2 = (**(code **)(*plVar5 + 0x28))(plVar5);
              puVar10 = local_a8;
              local_res18 = (longlong *)CONCAT44(local_res18._4_4_,uVar2);
              if (local_b0 == (undefined4 *)0x0) {
                uVar6 = 0;
              }
              else {
                uVar6 = local_a0 - (longlong)local_b0 >> 2;
              }
              if ((ulonglong)((longlong)local_a8 - (longlong)local_b0 >> 2) < uVar6) {
                *local_a8 = uVar2;
                local_a8 = local_a8 + 1;
              }
              else {
                if (local_a8 < local_b0) {
                  _invalid_parameter_noinfo();
                }
                puVar1 = local_b0;
                plVar5 = local_c8[0];
                local_78 = local_c8[0];
                puStack_70 = puVar10;
                if (((longlong)local_a8 - (longlong)local_b0 & 0xfffffffffffffffcU) == 0) {
                  lVar12 = 0;
                }
                else {
                  if (local_a8 < local_b0) {
                    _invalid_parameter_noinfo();
                  }
                  if ((plVar5 == (longlong *)0x0) || (plVar5 != local_c8[0])) {
                    _invalid_parameter_noinfo();
                  }
                  lVar12 = (longlong)puVar10 - (longlong)puVar1 >> 2;
                }
                local_58 = local_78;
                puStack_50 = puStack_70;
                FUN_14002d450((longlong)local_c8,(longlong)&local_58,1,(undefined4 *)&local_res18);
                puVar10 = local_b0;
                if (local_a8 < local_b0) {
                  _invalid_parameter_noinfo();
                }
                plVar5 = local_c8[0];
                if (local_c8[0] == (longlong *)0x0) {
                  _invalid_parameter_noinfo();
                  lVar4 = 0;
                }
                else {
                  lVar4 = *local_c8[0];
                }
                if (puVar10 + lVar12 <= *(undefined4 **)(lVar4 + 0x20)) {
                  if (plVar5 == (longlong *)0x0) {
                    lVar4 = 0;
                  }
                  else {
                    lVar4 = *plVar5;
                  }
                  if (*(undefined4 **)(lVar4 + 0x18) <= puVar10 + lVar12) goto LAB_14005292c;
                }
                _invalid_parameter_noinfo();
              }
            }
LAB_14005292c:
            uVar9 = uVar9 + 1;
            uVar6 = (**(code **)(*plVar3 + 0x10))(plVar3);
            lVar12 = local_98;
          } while (uVar9 < uVar6);
        }
        if ((ulonglong)((*(longlong *)(param_1 + 0x38) - *(longlong *)(param_1 + 0x30)) / 0x30) <=
            local_res20) {
          _invalid_parameter_noinfo();
        }
        lVar4 = *(longlong *)(param_1 + 0x30);
        if ((ulonglong)
            ((*(longlong *)(lVar12 + 0x20 + lVar4) - *(longlong *)(lVar12 + 0x18 + lVar4)) / 0x18)
            <= uVar13) {
          _invalid_parameter_noinfo();
        }
        plVar3 = (longlong *)FUN_1400678b0(*(longlong *)(lVar12 + 0x18 + lVar4) + uVar13 * 0x18);
        uVar13 = 0;
        lVar4 = (**(code **)(*plVar3 + 0x10))(plVar3);
        if (lVar4 != 0) {
          do {
            plVar5 = (longlong *)
                     (**(code **)(*plVar3 + 0x18))
                               (plVar3,uVar13,
                                "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\gamemap.cpp"
                                ,0x2f8);
            if (plVar5 != (longlong *)0x0) {
              uVar2 = (**(code **)(*plVar5 + 8))(plVar5);
              puVar10 = local_d8;
              local_res18 = (longlong *)CONCAT44(local_res18._4_4_,uVar2);
              if (local_e0 == (undefined4 *)0x0) {
                uVar9 = 0;
              }
              else {
                uVar9 = local_d0 - (longlong)local_e0 >> 2;
              }
              if ((ulonglong)((longlong)local_d8 - (longlong)local_e0 >> 2) < uVar9) {
                *local_d8 = uVar2;
                local_d8 = local_d8 + 1;
              }
              else {
                if (local_d8 < local_e0) {
                  _invalid_parameter_noinfo();
                }
                puVar1 = local_e0;
                plVar5 = local_f8[0];
                local_88 = local_f8[0];
                puStack_80 = puVar10;
                if (((longlong)local_d8 - (longlong)local_e0 & 0xfffffffffffffffcU) == 0) {
                  lVar12 = 0;
                }
                else {
                  if (local_d8 < local_e0) {
                    _invalid_parameter_noinfo();
                  }
                  if ((plVar5 == (longlong *)0x0) || (plVar5 != local_f8[0])) {
                    _invalid_parameter_noinfo();
                  }
                  lVar12 = (longlong)puVar10 - (longlong)puVar1 >> 2;
                }
                local_68 = local_88;
                puStack_60 = puStack_80;
                FUN_14002d450((longlong)local_f8,(longlong)&local_68,1,(undefined4 *)&local_res18);
                puVar10 = local_e0;
                if (local_d8 < local_e0) {
                  _invalid_parameter_noinfo();
                }
                plVar5 = local_f8[0];
                if (local_f8[0] == (longlong *)0x0) {
                  _invalid_parameter_noinfo();
                  lVar4 = 0;
                }
                else {
                  lVar4 = *local_f8[0];
                }
                if (puVar10 + lVar12 <= *(undefined4 **)(lVar4 + 0x20)) {
                  if (plVar5 == (longlong *)0x0) {
                    lVar4 = 0;
                  }
                  else {
                    lVar4 = *plVar5;
                  }
                  if (*(undefined4 **)(lVar4 + 0x18) <= puVar10 + lVar12) goto LAB_140052b3c;
                }
                _invalid_parameter_noinfo();
              }
            }
LAB_140052b3c:
            uVar13 = uVar13 + 1;
            uVar9 = (**(code **)(*plVar3 + 0x10))(plVar3);
            lVar12 = local_98;
          } while (uVar13 < uVar9);
        }
        iVar14 = iVar14 + 1;
      }
      iVar8 = iVar8 + 1;
      local_res20 = local_res20 + 1;
      local_98 = lVar12 + 0x30;
    } while (iVar8 < (int)((*(longlong *)(param_1 + 0x38) - *(longlong *)(param_1 + 0x30)) / 0x30));
  }
  puVar10 = local_b0;
  if (local_a8 < local_b0) {
    _invalid_parameter_noinfo();
  }
  puVar1 = local_a8;
  plVar3 = local_c8[0];
  plVar5 = local_c8[0];
  if (local_a8 < local_b0) {
    _invalid_parameter_noinfo();
    plVar5 = local_c8[0];
  }
  while( true ) {
    if ((plVar3 == (longlong *)0x0) || (plVar3 != plVar5)) {
      _invalid_parameter_noinfo();
    }
    puVar11 = local_e0;
    if (puVar10 == puVar1) break;
    if (plVar3 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar12 = 0;
    }
    else {
      lVar12 = *plVar3;
    }
    if (*(undefined4 **)(lVar12 + 0x20) <= puVar10) {
      _invalid_parameter_noinfo();
    }
    uVar2 = *puVar10;
    lVar12 = FUN_14001c7a0();
    plVar7 = (longlong *)FUN_140025c40(lVar12);
    (**(code **)(*plVar7 + 0x30))(plVar7,uVar2);
    if (plVar3 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar12 = 0;
    }
    else {
      lVar12 = *plVar3;
    }
    if (*(undefined4 **)(lVar12 + 0x20) <= puVar10) {
      _invalid_parameter_noinfo();
    }
    puVar10 = puVar10 + 1;
  }
  if (local_d8 < local_e0) {
    _invalid_parameter_noinfo();
  }
  puVar10 = local_d8;
  plVar3 = local_f8[0];
  plVar5 = local_f8[0];
  if (local_d8 < local_e0) {
    _invalid_parameter_noinfo();
    plVar5 = local_f8[0];
  }
  while( true ) {
    if ((plVar3 == (longlong *)0x0) || (plVar3 != plVar5)) {
      _invalid_parameter_noinfo();
    }
    if (puVar11 == puVar10) break;
    if (plVar3 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar12 = 0;
    }
    else {
      lVar12 = *plVar3;
    }
    if (*(undefined4 **)(lVar12 + 0x20) <= puVar11) {
      _invalid_parameter_noinfo();
    }
    uVar2 = *puVar11;
    plVar7 = (longlong *)FUN_14001c210();
    plVar7 = (longlong *)(**(code **)(*plVar7 + 0x10))(plVar7);
    (**(code **)(*plVar7 + 0x28))(plVar7,uVar2);
    if (plVar3 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar12 = 0;
    }
    else {
      lVar12 = *plVar3;
    }
    if (*(undefined4 **)(lVar12 + 0x20) <= puVar11) {
      _invalid_parameter_noinfo();
    }
    puVar11 = puVar11 + 1;
  }
  if (local_e0 != (undefined4 *)0x0) {
    operator_delete(local_e0);
  }
  local_e0 = (undefined4 *)0x0;
  local_d8 = (undefined4 *)0x0;
  local_d0 = 0;
  operator_delete(local_f8[0]);
  if (local_b0 != (undefined4 *)0x0) {
    operator_delete(local_b0);
  }
  local_b0 = (undefined4 *)0x0;
  local_a8 = (undefined4 *)0x0;
  local_a0 = 0;
  operator_delete(local_c8[0]);
  return CONCAT71((int7)((ulonglong)extraout_RAX >> 8),1);
}


// ==== CGameMap::vf_0x38 @ 1400551e0  undefined8 vf_0x38(undefined8 * param_1)

undefined8 CGameMap::vf_0x38(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    (**(code **)*param_1)(param_1,1);
  }
  return 0;
}


// ==== CGameMap::vf_0x8 @ 140055200  undefined vf_0x8(longlong param_1)

void CGameMap::vf_0x8(longlong param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)
           (**(code **)(*(longlong *)**(undefined8 **)(param_1 + 0x48) + 0x20))
                     ((longlong *)**(undefined8 **)(param_1 + 0x48),&DAT_140102d90);
                    /* WARNING: Could not recover jumptable at 0x000140055222. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x40))(plVar1);
  return;
}


// ==== CGameMap::vf_0x0 @ 1400553c0  undefined8 * vf_0x0(undefined8 * param_1, ulonglong param_2, undefined8 param_3, undefined8 param_4)

undefined8 *
CGameMap::vf_0x0(undefined8 *param_1,ulonglong param_2,undefined8 param_3,undefined8 param_4)

{
  FUN_140055230(param_1,param_2,param_3,param_4);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CGameMap::vf_0x20 @ 1400553f0  undefined vf_0x20(longlong * param_1, longlong * param_2, undefined1 param_3)

void CGameMap::vf_0x20(longlong *param_1,longlong *param_2,undefined1 param_3)

{
  longlong lVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  longlong lVar5;
  longlong *plVar6;
  undefined8 *puVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  ulonglong uVar10;
  longlong lVar11;
  ulonglong uVar12;
  undefined1 auStack_4c8 [32];
  undefined4 local_4a8;
  undefined1 local_498;
  undefined8 local_490;
  undefined8 local_488;
  undefined8 local_480;
  undefined8 local_478;
  undefined1 local_468 [32];
  char local_448 [1024];
  ulonglong local_48;
  
  local_490 = 0xfffffffffffffffe;
  local_48 = DAT_140103510 ^ (ulonglong)auStack_4c8;
  plVar6 = (longlong *)param_1[9];
  local_498 = param_3;
  if (plVar6 == (longlong *)0x0) {
    local_4a8 = 0x7c;
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  else {
    lVar5 = (**(code **)(*param_2 + 0x38))(param_2);
    *plVar6 = lVar5;
    if (lVar5 != 0) {
      plVar6 = (longlong *)
               (**(code **)(**(longlong **)param_1[9] + 0x10))(*(longlong **)param_1[9],3);
      uVar2 = (**(code **)(*plVar6 + 0x48))(plVar6);
      plVar6 = (longlong *)FUN_1400515a0(uVar2);
      param_1[2] = (longlong)plVar6;
      if (plVar6 == (longlong *)0x0) {
        (**(code **)(*param_1 + 8))(param_1);
        sprintf(local_448,&DAT_1400c86b0);
        lVar5 = FUN_14001c200();
        FUN_14001c120(lVar5);
      }
      else {
        iVar3 = (**(code **)(*plVar6 + 0x28))(plVar6);
        FUN_140054e90(param_1 + 0xb,(longlong)iVar3);
        uVar12 = 0;
        uVar8 = uVar12;
        uVar10 = uVar12;
        if ((param_1[0xf] - param_1[0xe]) / 0x30 != 0) {
          do {
            iVar3 = (**(code **)(*(longlong *)param_1[2] + 0x20))();
            if ((ulonglong)((param_1[0xf] - param_1[0xe]) / 0x30) <= uVar10) {
              _invalid_parameter_noinfo();
            }
            FUN_140051960((longlong *)(uVar8 + param_1[0xe]),(longlong)iVar3,0);
            uVar9 = uVar12;
            while( true ) {
              if ((ulonglong)((param_1[0xf] - param_1[0xe]) / 0x30) <= uVar10) {
                _invalid_parameter_noinfo();
              }
              lVar5 = param_1[0xe];
              if ((ulonglong)
                  (*(longlong *)(uVar8 + 0x20 + lVar5) - *(longlong *)(uVar8 + 0x18 + lVar5) >> 2)
                  <= uVar9) break;
              if ((ulonglong)((param_1[0xf] - lVar5) / 0x30) <= uVar10) {
                _invalid_parameter_noinfo();
              }
              lVar5 = param_1[0xe];
              if ((ulonglong)
                  (*(longlong *)(uVar8 + 0x20 + lVar5) - *(longlong *)(uVar8 + 0x18 + lVar5) >> 2)
                  <= uVar9) {
                _invalid_parameter_noinfo();
              }
              *(undefined4 *)(*(longlong *)(uVar8 + 0x18 + lVar5) + uVar9 * 4) = 0;
              uVar9 = uVar9 + 1;
            }
            uVar10 = uVar10 + 1;
            uVar8 = uVar8 + 0x30;
            param_3 = local_498;
          } while (uVar10 < (ulonglong)((param_1[0xf] - lVar5) / 0x30));
        }
        iVar3 = (**(code **)(*(longlong *)param_1[2] + 0x28))();
        FUN_140055330(param_1 + 3,(longlong)((iVar3 + -1) / 0x12 + 1));
        if ((param_1[7] - param_1[6]) / 0x30 != 0) {
          lVar5 = 0;
          do {
            iVar3 = (**(code **)(*(longlong *)param_1[2] + 0x20))();
            if ((ulonglong)((param_1[7] - param_1[6]) / 0x30) <= uVar12) {
              _invalid_parameter_noinfo();
            }
            lVar11 = param_1[6];
            puVar7 = (undefined8 *)FUN_140067830(local_468);
            local_488 = *puVar7;
            local_480 = puVar7[1];
            local_478 = puVar7[2];
            FUN_140052dd0((longlong *)(lVar5 + lVar11),(longlong)((iVar3 + -1) / 0x12 + 1),
                          &local_488);
            FUN_140067850((longlong)local_468);
            uVar8 = 0;
            lVar11 = 0;
            while( true ) {
              if ((ulonglong)((param_1[7] - param_1[6]) / 0x30) <= uVar12) {
                _invalid_parameter_noinfo();
              }
              if ((ulonglong)
                  ((*(longlong *)(lVar5 + 0x20 + param_1[6]) -
                   *(longlong *)(lVar5 + 0x18 + param_1[6])) / 0x18) <= uVar8) break;
              if ((ulonglong)((param_1[7] - param_1[6]) / 0x30) <= uVar12) {
                _invalid_parameter_noinfo();
              }
              lVar1 = param_1[6];
              if ((ulonglong)
                  ((*(longlong *)(lVar5 + 0x20 + lVar1) - *(longlong *)(lVar5 + 0x18 + lVar1)) /
                  0x18) <= uVar8) {
                _invalid_parameter_noinfo();
              }
              FUN_140069310(lVar11 + *(longlong *)(lVar5 + 0x18 + lVar1));
              uVar8 = uVar8 + 1;
              lVar11 = lVar11 + 0x18;
            }
            uVar12 = uVar12 + 1;
            lVar5 = lVar5 + 0x30;
            param_3 = local_498;
          } while (uVar12 < (ulonglong)((param_1[7] - param_1[6]) / 0x30));
        }
        *(undefined1 *)(param_1 + 0x11) = param_3;
        plVar6 = (longlong *)
                 (**(code **)(**(longlong **)param_1[9] + 0x20))
                           (*(longlong **)param_1[9],&DAT_140102d90);
        uVar4 = (**(code **)(*plVar6 + 0x40))(plVar6);
        *(undefined4 *)((longlong)param_1 + 0x8c) = uVar4;
      }
    }
  }
  __security_check_cookie(local_48 ^ (ulonglong)auStack_4c8);
  return;
}


// ==== CGameMap::vf_0x28 @ 1400558b0  undefined vf_0x28(longlong * param_1, longlong param_2, undefined4 param_3)

void CGameMap::vf_0x28(longlong *param_1,longlong param_2,undefined4 param_3)

{
  longlong lVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  longlong *plVar6;
  longlong lVar7;
  longlong *plVar8;
  undefined8 uVar9;
  ulonglong uVar10;
  undefined8 *puVar11;
  ulonglong uVar12;
  undefined1 auStack_488 [32];
  undefined4 local_468;
  undefined8 *local_458;
  longlong *local_450;
  char local_448 [1024];
  ulonglong local_48;
  
  local_48 = DAT_140103510 ^ (ulonglong)auStack_488;
  local_450 = param_1;
  if (param_2 == 0) {
    local_468 = 0xa7;
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  else {
    plVar8 = (longlong *)param_1[9];
    if (plVar8 == (longlong *)0x0) {
      local_468 = 0xa8;
      log_InlineLogERROR(&DAT_1400be0b0);
    }
    else {
      plVar6 = (longlong *)InstanceGet();
      lVar7 = (**(code **)(*plVar6 + 0x20))(plVar6,s_cq_map_140102d94);
      *plVar8 = lVar7;
      if ((lVar7 != 0) &&
         (puVar11 = *(undefined8 **)(param_2 + 0x48), local_458 = puVar11,
         puVar11 != (undefined8 *)0x0)) {
        plVar8 = (longlong *)
                 (**(code **)(**(longlong **)param_1[9] + 0x10))(*(longlong **)param_1[9],0);
        (**(code **)(*plVar8 + 0xb0))(plVar8,param_3);
        plVar8 = (longlong *)(**(code **)(*(longlong *)*puVar11 + 0x10))((longlong *)*puVar11,1);
        uVar9 = (**(code **)(*plVar8 + 0x78))(plVar8);
        plVar8 = (longlong *)
                 (**(code **)(**(longlong **)param_1[9] + 0x10))(*(longlong **)param_1[9],1);
        (**(code **)(*plVar8 + 0x80))(plVar8,uVar9);
        plVar8 = (longlong *)(**(code **)(*(longlong *)*puVar11 + 0x10))((longlong *)*puVar11,0x10);
        uVar2 = (**(code **)(*plVar8 + 0x48))(plVar8);
        plVar8 = (longlong *)
                 (**(code **)(**(longlong **)param_1[9] + 0x10))(*(longlong **)param_1[9],0x10);
        (**(code **)(*plVar8 + 0xb0))(plVar8,uVar2);
        plVar8 = (longlong *)(**(code **)(*(longlong *)*puVar11 + 0x10))((longlong *)*puVar11,5);
        uVar2 = (**(code **)(*plVar8 + 0x48))(plVar8);
        plVar8 = (longlong *)
                 (**(code **)(**(longlong **)param_1[9] + 0x10))(*(longlong **)param_1[9],5);
        (**(code **)(*plVar8 + 0xb0))(plVar8,uVar2);
        plVar8 = (longlong *)(**(code **)(*(longlong *)*puVar11 + 0x10))((longlong *)*puVar11,3);
        uVar2 = (**(code **)(*plVar8 + 0x48))(plVar8);
        plVar8 = (longlong *)
                 (**(code **)(**(longlong **)param_1[9] + 0x10))(*(longlong **)param_1[9],3);
        (**(code **)(*plVar8 + 0xb0))(plVar8,uVar2);
        plVar8 = (longlong *)(**(code **)(*(longlong *)*puVar11 + 0x10))((longlong *)*puVar11,4);
        uVar9 = (**(code **)(*plVar8 + 0x58))(plVar8);
        plVar8 = (longlong *)
                 (**(code **)(**(longlong **)param_1[9] + 0x10))(*(longlong **)param_1[9],4);
        (**(code **)(*plVar8 + 0xa0))(plVar8,uVar9);
        plVar8 = (longlong *)(**(code **)(*(longlong *)*puVar11 + 0x10))((longlong *)*puVar11,0x11);
        uVar2 = (**(code **)(*plVar8 + 0x48))(plVar8);
        plVar8 = (longlong *)
                 (**(code **)(**(longlong **)param_1[9] + 0x10))(*(longlong **)param_1[9],0x11);
        (**(code **)(*plVar8 + 0xb0))(plVar8,uVar2);
        plVar8 = (longlong *)(**(code **)(*(longlong *)*puVar11 + 0x10))((longlong *)*puVar11,0x12);
        uVar2 = (**(code **)(*plVar8 + 0x48))(plVar8);
        plVar8 = (longlong *)
                 (**(code **)(**(longlong **)param_1[9] + 0x10))(*(longlong **)param_1[9],0x12);
        (**(code **)(*plVar8 + 0xb0))(plVar8,uVar2);
        plVar8 = (longlong *)(**(code **)(*(longlong *)*puVar11 + 0x10))((longlong *)*puVar11,0x13);
        uVar2 = (**(code **)(*plVar8 + 0x48))(plVar8);
        plVar8 = (longlong *)
                 (**(code **)(**(longlong **)param_1[9] + 0x10))(*(longlong **)param_1[9],0x13);
        (**(code **)(*plVar8 + 0xb0))(plVar8,uVar2);
        plVar8 = (longlong *)(**(code **)(*(longlong *)*puVar11 + 0x10))((longlong *)*puVar11,0xb);
        uVar2 = (**(code **)(*plVar8 + 0x48))(plVar8);
        plVar8 = (longlong *)
                 (**(code **)(**(longlong **)param_1[9] + 0x10))(*(longlong **)param_1[9],0xb);
        (**(code **)(*plVar8 + 0xb0))(plVar8,uVar2);
        plVar8 = (longlong *)(**(code **)(*(longlong *)*puVar11 + 0x10))((longlong *)*puVar11,0xc);
        uVar2 = (**(code **)(*plVar8 + 0x48))(plVar8);
        plVar8 = (longlong *)
                 (**(code **)(**(longlong **)param_1[9] + 0x10))(*(longlong **)param_1[9],0xc);
        (**(code **)(*plVar8 + 0xb0))(plVar8,uVar2);
        plVar8 = (longlong *)(**(code **)(*(longlong *)*puVar11 + 0x10))((longlong *)*puVar11,0xf);
        uVar2 = (**(code **)(*plVar8 + 0x48))(plVar8);
        plVar8 = (longlong *)
                 (**(code **)(**(longlong **)param_1[9] + 0x10))(*(longlong **)param_1[9],0xf);
        (**(code **)(*plVar8 + 0xb0))(plVar8,uVar2);
        plVar8 = (longlong *)
                 (**(code **)(**(longlong **)param_1[9] + 0x10))(*(longlong **)param_1[9],3);
        uVar3 = (**(code **)(*plVar8 + 0x48))(plVar8);
        plVar8 = (longlong *)FUN_1400515a0(uVar3);
        param_1[2] = (longlong)plVar8;
        if (plVar8 == (longlong *)0x0) {
          (**(code **)(*param_1 + 8))(param_1);
          sprintf(local_448,&DAT_1400c86b0);
          lVar7 = FUN_14001c200();
          FUN_14001c120(lVar7);
        }
        else {
          iVar4 = (**(code **)(*plVar8 + 0x28))(plVar8);
          FUN_140054e90(param_1 + 0xb,(longlong)iVar4);
          iVar4 = 0;
          uVar12 = 0;
          plVar8 = param_1;
          if (0 < (int)((param_1[0xf] - param_1[0xe]) / 0x30)) {
            lVar7 = 0;
            do {
              iVar5 = (**(code **)(*(longlong *)plVar8[2] + 0x20))();
              plVar8 = (longlong *)FUN_140049580((longlong)(param_1 + 0xb),(longlong)iVar4);
              FUN_140051960(plVar8,(longlong)iVar5,0);
              iVar5 = 0;
              uVar10 = 0;
              while( true ) {
                if ((ulonglong)((param_1[0xf] - param_1[0xe]) / 0x30) <= uVar12) {
                  _invalid_parameter_noinfo();
                }
                lVar1 = param_1[0xe];
                if ((int)(*(longlong *)(lVar7 + 0x20 + lVar1) - *(longlong *)(lVar7 + 0x18 + lVar1)
                         >> 2) <= iVar5) break;
                if ((ulonglong)((param_1[0xf] - lVar1) / 0x30) <= uVar12) {
                  _invalid_parameter_noinfo();
                }
                lVar1 = param_1[0xe];
                if ((ulonglong)
                    (*(longlong *)(lVar7 + 0x20 + lVar1) - *(longlong *)(lVar7 + 0x18 + lVar1) >> 2)
                    <= uVar10) {
                  _invalid_parameter_noinfo();
                }
                iVar5 = iVar5 + 1;
                uVar10 = uVar10 + 1;
                *(undefined4 *)(*(longlong *)(lVar7 + 0x18 + lVar1) + -4 + uVar10 * 4) = 0;
              }
              iVar4 = iVar4 + 1;
              uVar12 = uVar12 + 1;
              lVar7 = lVar7 + 0x30;
              puVar11 = local_458;
              plVar8 = local_450;
            } while (iVar4 < (int)((param_1[0xf] - lVar1) / 0x30));
          }
          iVar4 = (**(code **)(*(longlong *)plVar8[2] + 0x28))();
          FUN_140055330(plVar8 + 3,(longlong)((iVar4 + -1) / 0x12 + 1));
          iVar4 = 0;
          uVar12 = 0;
          plVar6 = plVar8;
          if (0 < (int)((plVar8[7] - plVar8[6]) / 0x30)) {
            lVar7 = 0;
            do {
              iVar5 = (**(code **)(*(longlong *)plVar6[2] + 0x20))();
              if ((ulonglong)((plVar8[7] - plVar8[6]) / 0x30) <= (ulonglong)(longlong)iVar4) {
                _invalid_parameter_noinfo();
              }
              FUN_140053570((longlong *)((longlong)iVar4 * 0x30 + plVar8[6]),
                            (longlong)((iVar5 + -1) / 0x12 + 1));
              iVar5 = 0;
              while( true ) {
                if ((ulonglong)((plVar8[7] - plVar8[6]) / 0x30) <= uVar12) {
                  _invalid_parameter_noinfo();
                }
                if ((int)((*(longlong *)(lVar7 + 0x20 + plVar8[6]) -
                          *(longlong *)(lVar7 + 0x18 + plVar8[6])) / 0x18) <= iVar5) break;
                if ((ulonglong)((plVar8[7] - plVar8[6]) / 0x30) <= uVar12) {
                  _invalid_parameter_noinfo();
                }
                lVar1 = plVar8[6];
                if ((ulonglong)
                    ((*(longlong *)(lVar7 + 0x20 + lVar1) - *(longlong *)(lVar7 + 0x18 + lVar1)) /
                    0x18) <= (ulonglong)(longlong)iVar5) {
                  _invalid_parameter_noinfo();
                }
                FUN_140069310(*(longlong *)(lVar7 + 0x18 + lVar1) + (longlong)iVar5 * 0x18);
                iVar5 = iVar5 + 1;
              }
              iVar4 = iVar4 + 1;
              uVar12 = uVar12 + 1;
              lVar7 = lVar7 + 0x30;
              puVar11 = local_458;
              plVar6 = local_450;
            } while (iVar4 < (int)((plVar8[7] - plVar8[6]) / 0x30));
          }
          plVar8 = (longlong *)(**(code **)(*(longlong *)*puVar11 + 0x10))((longlong *)*puVar11,0);
          uVar2 = (**(code **)(*plVar8 + 0x48))(plVar8);
          *(undefined4 *)((longlong)plVar6 + 0x8c) = uVar2;
        }
      }
    }
  }
  __security_check_cookie(local_48 ^ (ulonglong)auStack_488);
  return;
}


// ==== CGameMap::vf_0x10 @ 1400695f0  undefined4 vf_0x10(longlong param_1)

undefined4 CGameMap::vf_0x10(longlong param_1)

{
  return *(undefined4 *)(param_1 + 8);
}


// ==== CGameMap::vf_0x18 @ 140069600  undefined vf_0x18(longlong param_1, undefined4 param_2)

void CGameMap::vf_0x18(longlong param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 8) = param_2;
  return;
}


