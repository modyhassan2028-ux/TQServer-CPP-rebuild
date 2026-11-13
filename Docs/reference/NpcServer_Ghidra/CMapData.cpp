// NpcServer.exe :: CMapData  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMapData::vf_0x60 @ 14007fa90  undefined vf_0x60(undefined8 * param_1)

void CMapData::vf_0x60(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    (**(code **)*param_1)(param_1,1);
  }
  return;
}


// ==== CMapData::vf_0x20 @ 140081d50  undefined vf_0x20(longlong param_1)

void CMapData::vf_0x20(longlong param_1)

{
  FUN_14008d7a0(*(longlong *)(param_1 + 0x100));
  return;
}


// ==== CMapData::vf_0x28 @ 140081d60  undefined vf_0x28(longlong param_1)

void CMapData::vf_0x28(longlong param_1)

{
  FUN_14008d7b0(*(undefined4 **)(param_1 + 0x100));
  return;
}


// ==== CMapData::vf_0x30 @ 140081d70  undefined vf_0x30(longlong param_1, int param_2, int param_3)

void CMapData::vf_0x30(longlong param_1,int param_2,int param_3)

{
  FUN_1400905d0(*(longlong *)(param_1 + 0x100),param_2,param_3);
  return;
}


// ==== CMapData::vf_0x38 @ 140081d80  undefined vf_0x38(longlong param_1, int param_2, int param_3)

void CMapData::vf_0x38(longlong param_1,int param_2,int param_3)

{
  FUN_14008e0a0(*(int **)(param_1 + 0x100),param_2,param_3);
  return;
}


// ==== CMapData::vf_0x40 @ 140081d90  undefined vf_0x40(longlong param_1, int param_2, int param_3)

void CMapData::vf_0x40(longlong param_1,int param_2,int param_3)

{
  FUN_1400906e0(*(longlong *)(param_1 + 0x100),param_2,param_3);
  return;
}


// ==== CMapData::vf_0x8 @ 140084a00  ushort vf_0x8(longlong param_1, int param_2, int param_3)

ushort CMapData::vf_0x8(longlong param_1,int param_2,int param_3)

{
  longlong *plVar1;
  undefined8 *puVar2;
  longlong lVar3;
  char cVar4;
  ushort uVar5;
  int iVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  longlong *plVar9;
  ulonglong uVar10;
  longlong lVar11;
  longlong local_48;
  undefined8 *local_40;
  longlong local_38;
  undefined8 local_30;
  longlong *local_28;
  longlong local_20;
  
  cVar4 = FUN_14008d7c0(*(int **)(param_1 + 0x100),param_2,param_3);
  if (cVar4 != '\0') {
    iVar6 = FUN_14008d7e0(*(int **)(param_1 + 0x100),param_2,param_3);
    puVar7 = (undefined8 *)(*(undefined8 **)(param_1 + 0x1c0))[1];
    cVar4 = *(char *)((longlong)puVar7 + 0x21);
    puVar2 = *(undefined8 **)(param_1 + 0x1c0);
    while (cVar4 == '\0') {
      if (*(int *)(puVar7 + 3) < iVar6) {
        puVar8 = (undefined8 *)puVar7[2];
        puVar7 = puVar2;
      }
      else {
        puVar8 = (undefined8 *)*puVar7;
      }
      puVar2 = puVar7;
      puVar7 = puVar8;
      cVar4 = *(char *)((longlong)puVar8 + 0x21);
    }
    puVar7 = *(undefined8 **)(param_1 + 0x1c0);
    local_40 = puVar2;
    local_48 = *(longlong *)(param_1 + 400);
    if (*(longlong *)(param_1 + 400) == 0) {
      _invalid_parameter_noinfo();
    }
    if ((puVar2 == puVar7) || (iVar6 < *(int *)(puVar2 + 3))) {
      plVar9 = &local_38;
      local_30 = *(undefined8 *)(param_1 + 0x1c0);
      local_38 = *(longlong *)(param_1 + 400);
    }
    else {
      plVar9 = &local_48;
    }
    plVar1 = (longlong *)*plVar9;
    lVar11 = *(longlong *)(param_1 + 0x1c0);
    local_28 = plVar1;
    local_20 = plVar9[1];
    if ((plVar1 == (longlong *)0x0) || (plVar1 != *(longlong **)(param_1 + 400))) {
      _invalid_parameter_noinfo();
    }
    lVar3 = local_20;
    if (local_20 == lVar11) {
      uVar5 = FUN_1400902e0(*(int **)(param_1 + 0x100),param_2,param_3);
    }
    else {
      if (plVar1 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar11 = 0;
      }
      else {
        lVar11 = *plVar1;
      }
      if (lVar3 == *(longlong *)(lVar11 + 0x30)) {
        _invalid_parameter_noinfo();
      }
      uVar10 = (ulonglong)*(int *)(lVar3 + 0x1c);
      if ((ulonglong)((*(longlong *)(param_1 + 0xc0) - *(longlong *)(param_1 + 0xb8)) / 0x30) <=
          uVar10) {
        _invalid_parameter_noinfo();
      }
      puVar7 = (undefined8 *)
               FUN_140083f00((longlong *)(uVar10 * 0x30 + *(longlong *)(param_1 + 0xb8)));
      uVar5 = FUN_140093910((undefined2 *)*puVar7);
    }
    return uVar5;
  }
  return 0x7fff;
}


// ==== CMapData::vf_0x10 @ 140084bc0  undefined2 vf_0x10(longlong param_1, int param_2, int param_3)

undefined2 CMapData::vf_0x10(longlong param_1,int param_2,int param_3)

{
  longlong *plVar1;
  undefined8 *puVar2;
  longlong lVar3;
  char cVar4;
  undefined2 uVar5;
  int iVar6;
  longlong *plVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  ulonglong uVar10;
  longlong lVar11;
  longlong local_48;
  undefined8 *local_40;
  longlong local_38;
  undefined8 local_30;
  longlong *local_28;
  longlong local_20;
  
  cVar4 = FUN_14008d7c0(*(int **)(param_1 + 0x100),param_2,param_3);
  if (cVar4 != '\0') {
    iVar6 = FUN_14008d7e0(*(int **)(param_1 + 0x100),param_2,param_3);
    puVar9 = (undefined8 *)(*(undefined8 **)(param_1 + 0x1c0))[1];
    cVar4 = *(char *)((longlong)puVar9 + 0x21);
    puVar2 = *(undefined8 **)(param_1 + 0x1c0);
    while (cVar4 == '\0') {
      if (*(int *)(puVar9 + 3) < iVar6) {
        puVar8 = (undefined8 *)puVar9[2];
        puVar9 = puVar2;
      }
      else {
        puVar8 = (undefined8 *)*puVar9;
      }
      puVar2 = puVar9;
      puVar9 = puVar8;
      cVar4 = *(char *)((longlong)puVar8 + 0x21);
    }
    puVar9 = *(undefined8 **)(param_1 + 0x1c0);
    local_40 = puVar2;
    local_48 = *(longlong *)(param_1 + 400);
    if (*(longlong *)(param_1 + 400) == 0) {
      _invalid_parameter_noinfo();
    }
    if ((puVar2 == puVar9) || (iVar6 < *(int *)(puVar2 + 3))) {
      plVar7 = &local_38;
      local_30 = *(undefined8 *)(param_1 + 0x1c0);
      local_38 = *(longlong *)(param_1 + 400);
    }
    else {
      plVar7 = &local_48;
    }
    plVar1 = (longlong *)*plVar7;
    lVar11 = *(longlong *)(param_1 + 0x1c0);
    local_28 = plVar1;
    local_20 = plVar7[1];
    if ((plVar1 == (longlong *)0x0) || (plVar1 != *(longlong **)(param_1 + 400))) {
      _invalid_parameter_noinfo();
    }
    lVar3 = local_20;
    if (local_20 == lVar11) {
      uVar5 = FUN_1400903e0(*(int **)(param_1 + 0x100),param_2,param_3);
    }
    else {
      if (plVar1 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar11 = 0;
      }
      else {
        lVar11 = *plVar1;
      }
      if (lVar3 == *(longlong *)(lVar11 + 0x30)) {
        _invalid_parameter_noinfo();
      }
      uVar10 = (ulonglong)*(int *)(lVar3 + 0x1c);
      if ((ulonglong)((*(longlong *)(param_1 + 0xc0) - *(longlong *)(param_1 + 0xb8)) / 0x30) <=
          uVar10) {
        _invalid_parameter_noinfo();
      }
      plVar7 = (longlong *)
               FUN_140083f00((longlong *)(uVar10 * 0x30 + *(longlong *)(param_1 + 0xb8)));
      uVar5 = FUN_140093930(*plVar7);
    }
    return uVar5;
  }
  return 0;
}


// ==== CMapData::vf_0x18 @ 140084d80  ushort vf_0x18(longlong param_1, int param_2, int param_3)

ushort CMapData::vf_0x18(longlong param_1,int param_2,int param_3)

{
  longlong *plVar1;
  undefined8 *puVar2;
  longlong lVar3;
  char cVar4;
  ushort uVar5;
  int iVar6;
  longlong *plVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  ulonglong uVar10;
  longlong lVar11;
  longlong local_48;
  undefined8 *local_40;
  longlong local_38;
  undefined8 local_30;
  longlong *local_28;
  longlong local_20;
  
  cVar4 = FUN_14008d7c0(*(int **)(param_1 + 0x100),param_2,param_3);
  if (cVar4 != '\0') {
    iVar6 = FUN_14008d7e0(*(int **)(param_1 + 0x100),param_2,param_3);
    puVar9 = (undefined8 *)(*(undefined8 **)(param_1 + 0x1c0))[1];
    cVar4 = *(char *)((longlong)puVar9 + 0x21);
    puVar2 = *(undefined8 **)(param_1 + 0x1c0);
    while (cVar4 == '\0') {
      if (*(int *)(puVar9 + 3) < iVar6) {
        puVar8 = (undefined8 *)puVar9[2];
        puVar9 = puVar2;
      }
      else {
        puVar8 = (undefined8 *)*puVar9;
      }
      puVar2 = puVar9;
      puVar9 = puVar8;
      cVar4 = *(char *)((longlong)puVar8 + 0x21);
    }
    puVar9 = *(undefined8 **)(param_1 + 0x1c0);
    local_40 = puVar2;
    local_48 = *(longlong *)(param_1 + 400);
    if (*(longlong *)(param_1 + 400) == 0) {
      _invalid_parameter_noinfo();
    }
    if ((puVar2 == puVar9) || (iVar6 < *(int *)(puVar2 + 3))) {
      plVar7 = &local_38;
      local_30 = *(undefined8 *)(param_1 + 0x1c0);
      local_38 = *(longlong *)(param_1 + 400);
    }
    else {
      plVar7 = &local_48;
    }
    plVar1 = (longlong *)*plVar7;
    lVar11 = *(longlong *)(param_1 + 0x1c0);
    local_28 = plVar1;
    local_20 = plVar7[1];
    if ((plVar1 == (longlong *)0x0) || (plVar1 != *(longlong **)(param_1 + 400))) {
      _invalid_parameter_noinfo();
    }
    lVar3 = local_20;
    if (local_20 == lVar11) {
      uVar5 = FUN_1400904d0(*(int **)(param_1 + 0x100),param_2,param_3);
    }
    else {
      if (plVar1 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar11 = 0;
      }
      else {
        lVar11 = *plVar1;
      }
      if (lVar3 == *(longlong *)(lVar11 + 0x30)) {
        _invalid_parameter_noinfo();
      }
      uVar10 = (ulonglong)*(int *)(lVar3 + 0x1c);
      if ((ulonglong)((*(longlong *)(param_1 + 0xc0) - *(longlong *)(param_1 + 0xb8)) / 0x30) <=
          uVar10) {
        _invalid_parameter_noinfo();
      }
      plVar7 = (longlong *)
               FUN_140083f00((longlong *)(uVar10 * 0x30 + *(longlong *)(param_1 + 0xb8)));
      uVar5 = FUN_140093920(*plVar7);
    }
    return uVar5;
  }
  return 1;
}


// ==== CMapData::vf_0x50 @ 140088310  undefined8 vf_0x50(longlong param_1, int param_2)

undefined8 CMapData::vf_0x50(longlong param_1,int param_2)

{
  int *piVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong *plVar4;
  longlong *plVar5;
  undefined8 *puVar6;
  longlong lVar7;
  char cVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  ulonglong *extraout_RAX;
  undefined4 extraout_var;
  ulonglong *extraout_RAX_00;
  ulonglong *extraout_RAX_01;
  ulonglong *puVar12;
  longlong lVar13;
  ulonglong *puVar14;
  ulonglong uVar15;
  undefined8 *puVar16;
  undefined8 *puVar17;
  longlong *plVar18;
  longlong *plVar19;
  ulonglong uVar20;
  longlong lVar21;
  uint uVar22;
  ulonglong uVar23;
  longlong *plVar24;
  uint local_res20;
  longlong *local_148;
  ulonglong *local_138;
  ulonglong local_128;
  longlong local_e0;
  longlong *local_d8;
  undefined8 local_d0;
  longlong *local_c8;
  longlong local_c0;
  undefined8 *local_b8;
  longlong local_b0;
  undefined8 local_a8;
  ulonglong *local_98;
  longlong *plStack_90;
  longlong *local_88;
  longlong local_80;
  undefined8 local_78;
  longlong local_68;
  longlong local_60;
  undefined8 local_58 [3];
  
  local_78 = 0xfffffffffffffffe;
  puVar14 = *(ulonglong **)(param_1 + 0x158);
  puVar12 = *(ulonglong **)(param_1 + 0x180);
  local_148 = (longlong *)**(ulonglong **)(param_1 + 0x180);
  local_138 = puVar14;
  while( true ) {
    uVar15 = 0;
    plVar18 = *(longlong **)(param_1 + 0x180);
    if ((puVar14 == (ulonglong *)0x0) || (puVar14 != *(ulonglong **)(param_1 + 0x158))) {
      _invalid_parameter_noinfo();
      puVar12 = extraout_RAX;
    }
    if (local_148 == plVar18) break;
    if (puVar14 == (ulonglong *)0x0) {
      _invalid_parameter_noinfo();
      uVar20 = uVar15;
    }
    else {
      uVar20 = *puVar14;
    }
    if (local_148 == *(longlong **)(uVar20 + 0x28)) {
      _invalid_parameter_noinfo();
    }
    plVar18 = (longlong *)local_148[3];
    lVar3 = local_148[2];
    if (plVar18 != (longlong *)0x0) {
      LOCK();
      *(int *)(plVar18 + 2) = (int)plVar18[2] + 1;
      UNLOCK();
    }
    local_c8 = plVar18;
    iVar9 = FUN_140094620(lVar3);
    puVar12 = (ulonglong *)CONCAT44(extraout_var,iVar9);
    if (iVar9 == param_2) {
      lVar13 = FUN_140094a50(lVar3);
      local_res20 = 0;
      if (0 < (int)lVar13) {
        do {
          FUN_140095250(lVar3,&local_e0,(uint)uVar15);
          puVar14 = (ulonglong *)FUN_140093bc0(local_e0);
          uVar20 = *puVar14;
          puVar14 = (ulonglong *)FUN_140093ba0(local_e0);
          uVar23 = *puVar14;
          uVar22 = (uint)uVar15;
          local_d0 = uVar23;
          if (0 < (int)uVar20) {
            uVar15 = uVar20 & 0xffffffff;
            do {
              local_128 = uVar20 >> 0x20;
              iVar9 = (int)uVar23;
              if (0 < (int)(uVar20 >> 0x20)) {
                iVar11 = local_d0._4_4_;
                do {
                  cVar8 = FUN_14008d7c0(*(int **)(param_1 + 0x100),iVar9,iVar11);
                  if (cVar8 != '\0') {
                    iVar10 = FUN_14008d7e0(*(int **)(param_1 + 0x100),iVar9,iVar11);
                    plVar18 = (longlong *)(param_1 + 400);
                    puVar17 = (undefined8 *)(*(undefined8 **)(param_1 + 0x1c0))[1];
                    cVar8 = *(char *)((longlong)puVar17 + 0x21);
                    puVar6 = *(undefined8 **)(param_1 + 0x1c0);
                    while (cVar8 == '\0') {
                      if (*(int *)(puVar17 + 3) < iVar10) {
                        puVar16 = (undefined8 *)puVar17[2];
                        puVar17 = puVar6;
                      }
                      else {
                        puVar16 = (undefined8 *)*puVar17;
                      }
                      puVar6 = puVar17;
                      puVar17 = puVar16;
                      cVar8 = *(char *)((longlong)puVar16 + 0x21);
                    }
                    local_b8 = puVar6;
                    local_c0 = *plVar18;
                    puVar17 = *(undefined8 **)(param_1 + 0x1c0);
                    if (*plVar18 == 0) {
                      _invalid_parameter_noinfo();
                    }
                    if ((puVar6 == puVar17) || (iVar10 < *(int *)(puVar6 + 3))) {
                      local_a8 = *(undefined8 *)(param_1 + 0x1c0);
                      local_b0 = *plVar18;
                      plVar24 = &local_b0;
                    }
                    else {
                      plVar24 = &local_c0;
                    }
                    plVar4 = (longlong *)*plVar24;
                    local_80 = plVar24[1];
                    lVar21 = *(longlong *)(param_1 + 0x1c0);
                    local_88 = plVar4;
                    if ((plVar4 == (longlong *)0x0) || (plVar4 != (longlong *)*plVar18)) {
                      _invalid_parameter_noinfo();
                    }
                    lVar7 = local_80;
                    if (local_80 != lVar21) {
                      if (plVar4 == (longlong *)0x0) {
                        _invalid_parameter_noinfo();
                        lVar21 = 0;
                      }
                      else {
                        lVar21 = *plVar4;
                      }
                      if (lVar7 == *(longlong *)(lVar21 + 0x30)) {
                        _invalid_parameter_noinfo();
                      }
                      uVar23 = (ulonglong)*(int *)(lVar7 + 0x1c);
                      if ((ulonglong)
                          ((*(longlong *)(param_1 + 0xc0) - *(longlong *)(param_1 + 0xb8)) / 0x30)
                          <= uVar23) {
                        _invalid_parameter_noinfo();
                      }
                      lVar21 = uVar23 * 0x30 + *(longlong *)(param_1 + 0xb8);
                      plVar4 = *(longlong **)(lVar21 + 0x20);
                      if (((longlong)plVar4 - *(longlong *)(lVar21 + 0x18) & 0xfffffffffffffff0U) !=
                          0) {
                        if (plVar4 + -2 != plVar4) {
                          plVar19 = plVar4 + -1;
                          do {
                            plVar5 = (longlong *)*plVar19;
                            if (plVar5 != (longlong *)0x0) {
                              LOCK();
                              plVar2 = plVar5 + 2;
                              *(int *)plVar2 = (int)*plVar2 + -1;
                              UNLOCK();
                              if ((int)*plVar2 == 0) {
                                (**(code **)*plVar5)(plVar5);
                                LOCK();
                                piVar1 = (int *)((longlong)plVar5 + 0x14);
                                *piVar1 = *piVar1 + -1;
                                UNLOCK();
                                if (*piVar1 == 0) {
                                  (**(code **)(*plVar5 + 8))(plVar5);
                                }
                              }
                            }
                            plVar5 = plVar19 + 1;
                            plVar19 = plVar19 + 2;
                          } while (plVar5 != plVar4);
                        }
                        *(longlong *)(lVar21 + 0x20) = *(longlong *)(lVar21 + 0x20) + -0x10;
                      }
                      if ((ulonglong)
                          ((*(longlong *)(param_1 + 0xc0) - *(longlong *)(param_1 + 0xb8)) / 0x30)
                          <= uVar23) {
                        _invalid_parameter_noinfo();
                      }
                      lVar21 = uVar23 * 0x30 + *(longlong *)(param_1 + 0xb8);
                      if ((*(longlong *)(lVar21 + 0x20) - *(longlong *)(lVar21 + 0x18) &
                          0xfffffffffffffff0U) == 0) {
                        local_68 = *plVar24;
                        local_60 = plVar24[1];
                        FUN_1400397c0(plVar18,local_58,&local_68);
                      }
                    }
                  }
                  iVar11 = iVar11 + -1;
                  local_128 = local_128 - 1;
                } while (local_128 != 0);
              }
              uVar23 = (ulonglong)(iVar9 - 1);
              uVar15 = uVar15 - 1;
              uVar22 = local_res20;
            } while (uVar15 != 0);
          }
          plVar18 = local_d8;
          if (local_d8 != (longlong *)0x0) {
            LOCK();
            plVar24 = local_d8 + 2;
            *(int *)plVar24 = (int)*plVar24 + -1;
            UNLOCK();
            if ((int)*plVar24 == 0) {
              (**(code **)*local_d8)(local_d8);
              LOCK();
              piVar1 = (int *)((longlong)plVar18 + 0x14);
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (*piVar1 == 0) {
                (**(code **)(*plVar18 + 8))(plVar18);
              }
            }
          }
          local_res20 = uVar22 + 1;
          uVar15 = (ulonglong)local_res20;
          plVar18 = local_c8;
          puVar14 = local_138;
        } while ((int)local_res20 < (int)lVar13);
      }
      uVar15 = 0;
      if (puVar14 == (ulonglong *)0x0) {
        _invalid_parameter_noinfo();
      }
      else {
        uVar15 = *puVar14;
      }
      if (local_148 == *(longlong **)(uVar15 + 0x28)) {
        _invalid_parameter_noinfo();
      }
      plVar24 = (longlong *)*local_148;
      if (local_148 != *(longlong **)(param_1 + 0x180)) {
        *(longlong **)local_148[1] = plVar24;
        *(longlong *)(*local_148 + 8) = local_148[1];
        plVar4 = (longlong *)local_148[3];
        if (plVar4 != (longlong *)0x0) {
          LOCK();
          plVar19 = plVar4 + 2;
          *(int *)plVar19 = (int)*plVar19 + -1;
          UNLOCK();
          if ((int)*plVar19 == 0) {
            (**(code **)*plVar4)(plVar4);
            LOCK();
            piVar1 = (int *)((longlong)plVar4 + 0x14);
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (*piVar1 == 0) {
              (**(code **)(*plVar4 + 8))(plVar4);
            }
          }
        }
        operator_delete(local_148);
        *(longlong *)(param_1 + 0x188) = *(longlong *)(param_1 + 0x188) + -1;
      }
      puVar14 = *(ulonglong **)(param_1 + 0x158);
      puVar12 = puVar14;
      local_148 = plVar24;
      local_138 = puVar14;
      local_98 = puVar14;
      plStack_90 = plVar24;
      if (plVar18 != (longlong *)0x0) {
        LOCK();
        plVar24 = plVar18 + 2;
        *(int *)plVar24 = (int)*plVar24 + -1;
        UNLOCK();
        if ((int)*plVar24 == 0) {
          puVar12 = (ulonglong *)(**(code **)*plVar18)(plVar18);
          LOCK();
          piVar1 = (int *)((longlong)plVar18 + 0x14);
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (*piVar1 == 0) {
            puVar12 = (ulonglong *)(**(code **)(*plVar18 + 8))(plVar18);
          }
        }
      }
    }
    else {
      if (puVar14 == (ulonglong *)0x0) {
        _invalid_parameter_noinfo();
        puVar12 = extraout_RAX_00;
      }
      else {
        uVar15 = *puVar14;
      }
      if (local_148 == *(longlong **)(uVar15 + 0x28)) {
        _invalid_parameter_noinfo();
        puVar12 = extraout_RAX_01;
      }
      local_148 = (longlong *)*local_148;
      if (plVar18 != (longlong *)0x0) {
        LOCK();
        plVar24 = plVar18 + 2;
        *(int *)plVar24 = (int)*plVar24 + -1;
        UNLOCK();
        if ((int)*plVar24 == 0) {
          puVar12 = (ulonglong *)(**(code **)*plVar18)(plVar18);
          LOCK();
          piVar1 = (int *)((longlong)plVar18 + 0x14);
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (*piVar1 == 0) {
            puVar12 = (ulonglong *)(**(code **)(*plVar18 + 8))(plVar18);
          }
        }
      }
    }
  }
  return CONCAT71((int7)((ulonglong)puVar12 >> 8),1);
}


// ==== CMapData::vf_0x58 @ 140089320  undefined8 vf_0x58(longlong * param_1, undefined8 * param_2, int param_3, undefined8 * param_4, undefined8 * param_5, int param_6)

undefined8
CMapData::vf_0x58(longlong *param_1,undefined8 *param_2,int param_3,undefined8 *param_4,
                 undefined8 *param_5,int param_6)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong *plVar5;
  undefined8 uVar6;
  undefined8 *puVar7;
  longlong lVar8;
  undefined1 *puVar9;
  int iVar10;
  
  *(int *)((longlong)param_1 + 0xc) = param_6;
  *(uint *)(param_1 + 2) = (param_6 != 0) + 1;
  FUN_140088910(param_1,*param_4,*param_5);
  if ((param_1[0x13] == 0) || ((int)param_1[2] == 2)) {
    if ((int)param_1[2] == 2) {
      *(undefined4 *)(param_1 + 2) = 1;
      FUN_140088910(param_1,*param_4,*(undefined8 *)((longlong)param_1 + 0x14));
      *(undefined4 *)(param_1 + 2) = 2;
    }
    else {
      FUN_140088910(param_1,*param_4,*(undefined8 *)((longlong)param_1 + 0x14));
    }
  }
  puVar9 = (undefined1 *)((longlong)param_2 + 0x14);
  memset(param_2,0,(longlong)param_3);
  iVar10 = param_3 + -0x18;
  puVar7 = *(undefined8 **)param_1[0x12];
  plVar3 = (longlong *)param_1[0xd];
  while( true ) {
    puVar4 = (undefined8 *)param_1[0x12];
    if ((plVar3 == (longlong *)0x0) || (plVar3 != (longlong *)param_1[0xd])) {
      _invalid_parameter_noinfo();
    }
    if ((puVar7 == puVar4) || (iVar10 < 0)) break;
    if (plVar3 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar8 = 0;
    }
    else {
      lVar8 = *plVar3;
    }
    if (puVar7 == *(undefined8 **)(lVar8 + 0x28)) {
      _invalid_parameter_noinfo();
    }
    plVar5 = (longlong *)puVar7[3];
    lVar8 = puVar7[2];
    if (plVar5 != (longlong *)0x0) {
      LOCK();
      *(int *)(plVar5 + 2) = (int)plVar5[2] + 1;
      UNLOCK();
    }
    *puVar9 = *(undefined1 *)(lVar8 + 0x14);
    puVar9 = puVar9 + 1;
    if (plVar5 != (longlong *)0x0) {
      LOCK();
      plVar1 = plVar5 + 2;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)*plVar1 == 0) {
        (**(code **)*plVar5)(plVar5);
        LOCK();
        piVar2 = (int *)((longlong)plVar5 + 0x14);
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (*piVar2 == 0) {
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
    }
    if (plVar3 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar8 = 0;
    }
    else {
      lVar8 = *plVar3;
    }
    if (puVar7 == *(undefined8 **)(lVar8 + 0x28)) {
      _invalid_parameter_noinfo();
    }
    puVar7 = (undefined8 *)*puVar7;
    iVar10 = iVar10 + -1;
  }
  *(int *)(param_2 + 2) = ((int)puVar9 - (int)param_2) + -0x14;
  *param_2 = *param_4;
  uVar6 = *(undefined8 *)((longlong)param_1 + 0x14);
  param_2[1] = uVar6;
  return CONCAT71((int7)((ulonglong)uVar6 >> 8),1);
}


// ==== CMapData::vf_0x0 @ 14008bd20  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMapData::vf_0x0(undefined8 *param_1,uint param_2)

{
  FUN_14008b880(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CMapData::vf_0x48 @ 14008bde0  undefined vf_0x48(longlong * param_1, uint param_2, undefined4 param_3, undefined4 param_4, uint param_5)

void CMapData::vf_0x48(longlong *param_1,uint param_2,undefined4 param_3,undefined4 param_4,
                      uint param_5)

{
  undefined8 uVar1;
  longlong *plVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  undefined2 *puVar5;
  char cVar6;
  short sVar7;
  short sVar8;
  undefined2 uVar9;
  CIniMgr *this;
  char *pcVar10;
  longlong lVar11;
  undefined8 *puVar12;
  int *piVar13;
  longlong *plVar14;
  undefined8 *puVar15;
  ulonglong uVar16;
  int iVar17;
  int iVar18;
  longlong lVar19;
  undefined8 *puVar20;
  longlong *plVar21;
  int iVar22;
  undefined1 auStack_418 [32];
  longlong local_3d0;
  int local_3c0;
  int local_3b8;
  int local_3b4;
  undefined1 local_3b0;
  undefined1 local_3af;
  longlong *local_3a8;
  int local_3a0;
  longlong *local_398;
  longlong *local_390;
  longlong *local_388;
  int local_380;
  longlong *local_378;
  longlong *local_370;
  longlong local_368;
  longlong *local_360;
  undefined2 *local_358;
  longlong *local_350;
  undefined8 local_348;
  longlong local_338;
  undefined8 *puStack_330;
  undefined8 local_328;
  longlong local_320;
  longlong local_318;
  longlong local_310;
  undefined8 *local_308;
  longlong local_300;
  undefined8 *local_2f8;
  longlong local_2e8;
  undefined8 *puStack_2e0;
  longlong local_2d8;
  undefined8 *puStack_2d0;
  longlong *local_2c8 [3];
  undefined8 local_2b0;
  undefined8 local_2a8;
  undefined8 local_2a0;
  undefined8 local_298;
  longlong local_288;
  undefined8 *puStack_280;
  longlong local_278;
  undefined8 *puStack_270;
  longlong local_268;
  undefined8 *puStack_260;
  char local_258 [255];
  undefined1 local_159;
  char local_158 [255];
  undefined1 local_59;
  ulonglong local_58;
  
  local_298 = 0xfffffffffffffffe;
  local_58 = DAT_140103510 ^ (ulonglong)auStack_418;
  _snprintf(local_158,0x100,"NpcType%lu",(ulonglong)(param_5 / 10));
  local_59 = 0;
  _snprintf(local_258,0x100,"Dir%lu",(ulonglong)(param_5 % 10));
  local_159 = 0;
  this = tq::GetInstance();
  pcVar10 = tq::CIniMgr::GetString(this,"ini\\TerrainNpc.ini",local_158,local_258,false);
  if (pcVar10 == (char *)0x0) {
    log_InlineLogERROR("CMapData cannot find item %d, key %s, field %s",(ulonglong)param_5,local_158
                       ,local_258);
  }
  else {
    FUN_140096390(&local_378,pcVar10,param_2);
    if (local_378 == (longlong *)0x0) {
      log_InlineLogERROR("CMapData cannot create item from file %s for owner %u",pcVar10,
                         (ulonglong)param_2);
      if (local_370 != (longlong *)0x0) {
        LOCK();
        plVar14 = local_370 + 2;
        lVar11 = *plVar14;
        *(int *)plVar14 = (int)*plVar14 + -1;
        UNLOCK();
        if ((int)lVar11 == 1) {
          (**(code **)*local_370)(local_370);
          LOCK();
          piVar13 = (int *)((longlong)local_370 + 0x14);
          *piVar13 = *piVar13 + -1;
          UNLOCK();
          if (*piVar13 == 0) {
            (**(code **)(*local_370 + 8))(local_370);
          }
        }
      }
    }
    else {
      (**(code **)(*local_378 + 8))(local_378,param_3,param_4);
      lVar11 = FUN_140094a50((longlong)local_378);
      local_380 = (int)lVar11;
      local_3a0 = 0;
      if (0 < local_380) {
        do {
          iVar17 = local_3a0;
          FUN_140095250((longlong)local_378,&local_368,local_3a0);
          puVar12 = (undefined8 *)FUN_140093ba0(local_368);
          uVar1 = *puVar12;
          local_328 = uVar1;
          puVar12 = (undefined8 *)FUN_140093bc0(local_368);
          local_348 = *puVar12;
          local_3b8 = 0;
          iVar18 = (int)local_348;
          if (0 < iVar18) {
            do {
              local_3c0 = 0;
              if (0 < local_348._4_4_) {
                iVar17 = (int)uVar1 - local_3b8;
                do {
                  iVar22 = local_328._4_4_ - local_3c0;
                  cVar6 = FUN_14008d7c0((int *)param_1[0x20],iVar17,iVar22);
                  if (cVar6 != '\0') {
                    FUN_140093f60(local_368,&local_358,local_3b8,local_3c0);
                    FUN_140093af0(&local_398);
                    puVar5 = local_358;
                    local_3a8 = local_398;
                    if (local_398 == (longlong *)0x0) {
                      log_InlineLogERROR("CMapData cannot create layer data");
                      if (local_390 != (longlong *)0x0) {
                        LOCK();
                        plVar14 = local_390 + 2;
                        lVar11 = *plVar14;
                        *(int *)plVar14 = (int)*plVar14 + -1;
                        UNLOCK();
                        if ((int)lVar11 == 1) {
                          (**(code **)*local_390)(local_390);
                          LOCK();
                          piVar13 = (int *)((longlong)local_390 + 0x14);
                          iVar17 = *piVar13;
                          *piVar13 = *piVar13 + -1;
                          UNLOCK();
                          if (iVar17 == 1) {
                            (**(code **)(*local_390 + 8))(local_390);
                          }
                        }
                      }
                      if (local_350 != (longlong *)0x0) {
                        LOCK();
                        plVar14 = local_350 + 2;
                        lVar11 = *plVar14;
                        *(int *)plVar14 = (int)*plVar14 + -1;
                        UNLOCK();
                        if ((int)lVar11 == 1) {
                          (**(code **)*local_350)(local_350);
                          LOCK();
                          piVar13 = (int *)((longlong)local_350 + 0x14);
                          iVar17 = *piVar13;
                          *piVar13 = *piVar13 + -1;
                          UNLOCK();
                          if (iVar17 == 1) {
                            (**(code **)(*local_350 + 8))(local_350);
                          }
                        }
                      }
                      if (local_360 != (longlong *)0x0) {
                        LOCK();
                        plVar14 = local_360 + 2;
                        lVar11 = *plVar14;
                        *(int *)plVar14 = (int)*plVar14 + -1;
                        UNLOCK();
                        if ((int)lVar11 == 1) {
                          (**(code **)*local_360)(local_360);
                          LOCK();
                          piVar13 = (int *)((longlong)local_360 + 0x14);
                          iVar17 = *piVar13;
                          *piVar13 = *piVar13 + -1;
                          UNLOCK();
                          if (iVar17 == 1) {
                            (**(code **)(*local_360 + 8))(local_360);
                          }
                        }
                      }
                      if (local_370 != (longlong *)0x0) {
                        LOCK();
                        plVar14 = local_370 + 2;
                        lVar11 = *plVar14;
                        *(int *)plVar14 = (int)*plVar14 + -1;
                        UNLOCK();
                        if ((int)lVar11 == 1) {
                          (**(code **)*local_370)(local_370);
                          LOCK();
                          piVar13 = (int *)((longlong)local_370 + 0x14);
                          iVar17 = *piVar13;
                          *piVar13 = *piVar13 + -1;
                          UNLOCK();
                          if (iVar17 == 1) {
                            (**(code **)(*local_370 + 8))(local_370);
                          }
                        }
                      }
                      goto LAB_14008cae7;
                    }
                    sVar7 = (**(code **)(*param_1 + 8))(param_1,iVar17,iVar22);
                    sVar8 = FUN_140093910(puVar5);
                    FUN_140093940((undefined2 *)local_3a8,sVar8 + sVar7);
                    plVar14 = local_398;
                    uVar9 = FUN_140093920((longlong)local_358);
                    FUN_140093950((longlong)plVar14,uVar9);
                    plVar14 = local_398;
                    uVar9 = FUN_140093930((longlong)local_358);
                    FUN_140093960((longlong)plVar14,uVar9);
                    iVar22 = FUN_14008d7e0((int *)param_1[0x20],iVar17,iVar22);
                    local_3a8 = param_1 + 0x32;
                    puVar12 = (undefined8 *)param_1[0x38];
                    lVar11 = *local_3a8;
                    cVar6 = *(char *)((longlong)puVar12[1] + 0x21);
                    puVar4 = puVar12;
                    puVar20 = (undefined8 *)puVar12[1];
                    while (cVar6 == '\0') {
                      if (*(int *)(puVar20 + 3) < iVar22) {
                        puVar15 = (undefined8 *)puVar20[2];
                        puVar20 = puVar4;
                      }
                      else {
                        puVar15 = (undefined8 *)*puVar20;
                      }
                      puVar4 = puVar20;
                      puVar20 = puVar15;
                      cVar6 = *(char *)((longlong)puVar15 + 0x21);
                    }
                    local_2f8 = puVar4;
                    local_300 = lVar11;
                    local_3b4 = iVar22;
                    if (lVar11 == 0) {
                      _invalid_parameter_noinfo();
                    }
                    if ((puVar4 == puVar12) || (iVar22 < *(int *)(puVar4 + 3))) {
                      local_318 = local_3a8[6];
                      local_320 = *local_3a8;
                      plVar14 = &local_320;
                    }
                    else {
                      plVar14 = &local_300;
                    }
                    local_310 = *plVar14;
                    local_308 = (undefined8 *)plVar14[1];
                    if ((local_310 == 0) || (local_310 != lVar11)) {
                      _invalid_parameter_noinfo();
                    }
                    if (local_308 == puVar12) {
                      plVar21 = param_1 + 0x14;
                      plVar14 = (longlong *)param_1[0x17];
                      if ((longlong *)param_1[0x18] < plVar14) {
                        _invalid_parameter_noinfo();
                      }
                      plVar2 = (longlong *)*plVar21;
                      while( true ) {
                        plVar3 = (longlong *)param_1[0x18];
                        if (plVar3 < (longlong *)param_1[0x17]) {
                          _invalid_parameter_noinfo();
                        }
                        if ((plVar2 == (longlong *)0x0) || (plVar2 != (longlong *)*plVar21)) {
                          _invalid_parameter_noinfo();
                        }
                        if (plVar14 == plVar3) goto LAB_14008c49c;
                        if (plVar2 == (longlong *)0x0) {
                          _invalid_parameter_noinfo();
                          lVar11 = 0;
                        }
                        else {
                          lVar11 = *plVar2;
                        }
                        if (*(longlong **)(lVar11 + 0x20) <= plVar14) {
                          _invalid_parameter_noinfo();
                        }
                        if ((plVar14[4] - plVar14[3] & 0xfffffffffffffff0U) == 0) break;
                        if (plVar2 == (longlong *)0x0) {
                          _invalid_parameter_noinfo();
                          lVar11 = 0;
                        }
                        else {
                          lVar11 = *plVar2;
                        }
                        if (*(longlong **)(lVar11 + 0x20) <= plVar14) {
                          _invalid_parameter_noinfo();
                        }
                        plVar14 = plVar14 + 6;
                      }
                      if (plVar2 == (longlong *)0x0) {
                        _invalid_parameter_noinfo();
                        lVar11 = 0;
                      }
                      else {
                        lVar11 = *plVar2;
                      }
                      if (*(longlong **)(lVar11 + 0x20) <= plVar14) {
                        _invalid_parameter_noinfo();
                      }
                      puVar12 = (undefined8 *)plVar14[3];
                      if (puVar12 == (undefined8 *)0x0) {
                        uVar16 = 0;
                      }
                      else {
                        uVar16 = plVar14[5] - (longlong)puVar12 >> 4;
                      }
                      puVar4 = (undefined8 *)plVar14[4];
                      if ((ulonglong)((longlong)puVar4 - (longlong)puVar12 >> 4) < uVar16) {
                        FUN_140085740(puVar4,1,&local_398);
                        plVar14[4] = (longlong)(puVar4 + 2);
                      }
                      else {
                        if (puVar4 < puVar12) {
                          _invalid_parameter_noinfo();
                        }
                        local_338 = *plVar14;
                        uVar16 = plVar14[3];
                        puStack_330 = puVar4;
                        if ((plVar14[4] - uVar16 & 0xfffffffffffffff0) == 0) {
                          local_3d0 = 0;
                        }
                        else {
                          if ((ulonglong)plVar14[4] < uVar16) {
                            _invalid_parameter_noinfo();
                          }
                          if ((local_338 == 0) || (local_338 != *plVar14)) {
                            _invalid_parameter_noinfo();
                          }
                          local_3d0 = (longlong)((longlong)puVar4 - uVar16) >> 4;
                        }
                        local_288 = local_338;
                        puStack_280 = puStack_330;
                        FUN_140087110((longlong)plVar14,(longlong)&local_288,1,
                                      (longlong *)&local_398);
                        local_388 = (longlong *)plVar14[3];
                        if ((ulonglong)plVar14[4] < local_388) {
                          _invalid_parameter_noinfo();
                        }
                        plVar3 = (longlong *)*plVar14;
                        if (plVar3 == (longlong *)0x0) {
                          _invalid_parameter_noinfo();
                          lVar11 = 0;
                        }
                        else {
                          lVar11 = *plVar3;
                        }
                        uVar16 = (longlong)local_388 + local_3d0 * 0x10;
                        if (uVar16 <= *(ulonglong *)(lVar11 + 0x20)) {
                          if (plVar3 == (longlong *)0x0) {
                            lVar11 = 0;
                          }
                          else {
                            lVar11 = *plVar3;
                          }
                          if (*(ulonglong *)(lVar11 + 0x18) <= uVar16) goto LAB_14008c433;
                        }
                        _invalid_parameter_noinfo();
                      }
LAB_14008c433:
                      local_388 = (longlong *)param_1[0x17];
                      if ((longlong *)param_1[0x18] < local_388) {
                        _invalid_parameter_noinfo();
                      }
                      if ((plVar2 == (longlong *)0x0) || (plVar2 != (longlong *)*plVar21)) {
                        _invalid_parameter_noinfo();
                      }
                      lVar11 = ((longlong)plVar14 - (longlong)local_388) / 6 +
                               ((longlong)plVar14 - (longlong)local_388 >> 0x3f);
                      piVar13 = (int *)FUN_14003bb80(local_3a8,&local_3b4);
                      *piVar13 = (int)(lVar11 >> 3) - (int)(lVar11 >> 0x3f);
LAB_14008c49c:
                      plVar3 = (longlong *)param_1[0x18];
                      if (plVar3 < (longlong *)param_1[0x17]) {
                        _invalid_parameter_noinfo();
                      }
                      if ((plVar2 == (longlong *)0x0) || (plVar2 != (longlong *)*plVar21)) {
                        _invalid_parameter_noinfo();
                      }
                      if (plVar14 == plVar3) {
                        lVar11 = (param_1[0x18] - param_1[0x17]) / 6 +
                                 (param_1[0x18] - param_1[0x17] >> 0x3f);
                        iVar22 = (int)(lVar11 >> 3) - (int)(lVar11 >> 0x3f);
                        piVar13 = (int *)FUN_14003bb80(local_3a8,&local_3b4);
                        *piVar13 = iVar22;
                        local_388 = (longlong *)operator_new(8);
                        if (local_388 == (longlong *)0x0) {
                          local_2c8[0] = (longlong *)0x0;
                        }
                        else {
                          *local_388 = (longlong)local_2c8;
                          local_2c8[0] = local_388;
                        }
                        uVar16 = 0;
                        local_2b0 = 0;
                        local_2a8 = 0;
                        local_2a0 = 0;
                        FUN_14008bb20(plVar21,(longlong)(iVar22 + 1),local_2c8);
                        plVar14 = (longlong *)FUN_140083e50(plVar21);
                        puVar12 = (undefined8 *)plVar14[3];
                        if (puVar12 != (undefined8 *)0x0) {
                          uVar16 = plVar14[5] - (longlong)puVar12 >> 4;
                        }
                        puVar4 = (undefined8 *)plVar14[4];
                        if ((ulonglong)((longlong)puVar4 - (longlong)puVar12 >> 4) < uVar16) {
                          local_3af = 0;
                          FUN_140085740(puVar4,1,&local_398);
                          plVar14[4] = (longlong)(puVar4 + 2);
                        }
                        else {
                          if (puVar4 < puVar12) {
                            _invalid_parameter_noinfo();
                          }
                          lVar11 = *plVar14;
                          uVar16 = plVar14[3];
                          local_2e8 = lVar11;
                          puStack_2e0 = puVar4;
                          if ((plVar14[4] - uVar16 & 0xfffffffffffffff0) == 0) {
                            lVar11 = 0;
                          }
                          else {
                            if ((ulonglong)plVar14[4] < uVar16) {
                              _invalid_parameter_noinfo();
                            }
                            if ((lVar11 == 0) || (lVar11 != *plVar14)) {
                              _invalid_parameter_noinfo();
                            }
                            lVar11 = (longlong)((longlong)puVar4 - uVar16) >> 4;
                          }
                          local_278 = local_2e8;
                          puStack_270 = puStack_2e0;
                          FUN_140087110((longlong)plVar14,(longlong)&local_278,1,
                                        (longlong *)&local_398);
                          uVar16 = plVar14[3];
                          if ((ulonglong)plVar14[4] < uVar16) {
                            _invalid_parameter_noinfo();
                          }
                          plVar14 = (longlong *)*plVar14;
                          if (plVar14 == (longlong *)0x0) {
                            _invalid_parameter_noinfo();
                            lVar19 = 0;
                          }
                          else {
                            lVar19 = *plVar14;
                          }
                          uVar16 = uVar16 + lVar11 * 0x10;
                          if (uVar16 <= *(ulonglong *)(lVar19 + 0x20)) {
                            if (plVar14 == (longlong *)0x0) {
                              lVar11 = 0;
                            }
                            else {
                              lVar11 = *plVar14;
                            }
                            if (*(ulonglong *)(lVar11 + 0x18) <= uVar16) goto LAB_14008c864;
                          }
                          _invalid_parameter_noinfo();
                        }
                      }
                    }
                    else {
                      piVar13 = (int *)FUN_14003bb80(local_3a8,&local_3b4);
                      iVar22 = *piVar13;
                      if ((ulonglong)((param_1[0x18] - param_1[0x17]) / 0x30) <=
                          (ulonglong)(longlong)iVar22) {
                        _invalid_parameter_noinfo();
                      }
                      plVar14 = (longlong *)((longlong)iVar22 * 0x30 + param_1[0x17]);
                      puVar12 = (undefined8 *)plVar14[3];
                      if (puVar12 == (undefined8 *)0x0) {
                        uVar16 = 0;
                      }
                      else {
                        uVar16 = plVar14[5] - (longlong)puVar12 >> 4;
                      }
                      puVar4 = (undefined8 *)plVar14[4];
                      if ((ulonglong)((longlong)puVar4 - (longlong)puVar12 >> 4) < uVar16) {
                        local_3b0 = 0;
                        FUN_140085740(puVar4,1,&local_398);
                        plVar14[4] = (longlong)(puVar4 + 2);
                      }
                      else {
                        if (puVar4 < puVar12) {
                          _invalid_parameter_noinfo();
                        }
                        lVar11 = *plVar14;
                        uVar16 = plVar14[3];
                        local_2d8 = lVar11;
                        puStack_2d0 = puVar4;
                        if ((plVar14[4] - uVar16 & 0xfffffffffffffff0) == 0) {
                          lVar11 = 0;
                        }
                        else {
                          if ((ulonglong)plVar14[4] < uVar16) {
                            _invalid_parameter_noinfo();
                          }
                          if ((lVar11 == 0) || (lVar11 != *plVar14)) {
                            _invalid_parameter_noinfo();
                          }
                          lVar11 = (longlong)((longlong)puVar4 - uVar16) >> 4;
                        }
                        local_268 = local_2d8;
                        puStack_260 = puStack_2d0;
                        FUN_140087110((longlong)plVar14,(longlong)&local_268,1,
                                      (longlong *)&local_398);
                        uVar16 = plVar14[3];
                        if ((ulonglong)plVar14[4] < uVar16) {
                          _invalid_parameter_noinfo();
                        }
                        plVar14 = (longlong *)*plVar14;
                        if (plVar14 == (longlong *)0x0) {
                          _invalid_parameter_noinfo();
                          lVar19 = 0;
                        }
                        else {
                          lVar19 = *plVar14;
                        }
                        uVar16 = uVar16 + lVar11 * 0x10;
                        if (uVar16 <= *(ulonglong *)(lVar19 + 0x20)) {
                          if (plVar14 == (longlong *)0x0) {
                            lVar11 = 0;
                          }
                          else {
                            lVar11 = *plVar14;
                          }
                          if (*(ulonglong *)(lVar11 + 0x18) <= uVar16) goto LAB_14008c864;
                        }
                        _invalid_parameter_noinfo();
                      }
                    }
LAB_14008c864:
                    plVar14 = local_390;
                    if (local_390 != (longlong *)0x0) {
                      LOCK();
                      plVar21 = local_390 + 2;
                      *(int *)plVar21 = (int)*plVar21 + -1;
                      UNLOCK();
                      if ((int)*plVar21 == 0) {
                        (**(code **)*local_390)(local_390);
                        LOCK();
                        piVar13 = (int *)((longlong)plVar14 + 0x14);
                        *piVar13 = *piVar13 + -1;
                        UNLOCK();
                        if (*piVar13 == 0) {
                          (**(code **)(*plVar14 + 8))(plVar14);
                        }
                      }
                    }
                    plVar14 = local_350;
                    if (local_350 != (longlong *)0x0) {
                      LOCK();
                      plVar21 = local_350 + 2;
                      lVar11 = *plVar21;
                      *(int *)plVar21 = (int)*plVar21 + -1;
                      UNLOCK();
                      if ((int)lVar11 == 1) {
                        (**(code **)*local_350)(local_350);
                        LOCK();
                        piVar13 = (int *)((longlong)plVar14 + 0x14);
                        iVar22 = *piVar13;
                        *piVar13 = *piVar13 + -1;
                        UNLOCK();
                        if (iVar22 == 1) {
                          (**(code **)(*plVar14 + 8))(plVar14);
                        }
                      }
                    }
                  }
                  local_3c0 = local_3c0 + 1;
                } while (local_3c0 < local_348._4_4_);
              }
              local_3b8 = local_3b8 + 1;
              iVar17 = local_3a0;
            } while (local_3b8 < iVar18);
          }
          plVar14 = local_360;
          if (local_360 != (longlong *)0x0) {
            LOCK();
            plVar21 = local_360 + 2;
            lVar11 = *plVar21;
            *(int *)plVar21 = (int)*plVar21 + -1;
            UNLOCK();
            if ((int)lVar11 == 1) {
              (**(code **)*local_360)(local_360);
              LOCK();
              piVar13 = (int *)((longlong)plVar14 + 0x14);
              iVar18 = *piVar13;
              *piVar13 = *piVar13 + -1;
              UNLOCK();
              if (iVar18 == 1) {
                (**(code **)(*plVar14 + 8))(plVar14);
              }
            }
          }
          local_3a0 = iVar17 + 1;
        } while (local_3a0 < local_380);
      }
      lVar11 = param_1[0x30];
      puVar12 = FUN_140085480(param_1 + 0x2b,lVar11,*(undefined8 *)(lVar11 + 8),&local_378);
      FUN_140082600((longlong)(param_1 + 0x2b),1);
      *(undefined8 **)(lVar11 + 8) = puVar12;
      *(undefined8 **)puVar12[1] = puVar12;
      if (local_370 != (longlong *)0x0) {
        LOCK();
        plVar14 = local_370 + 2;
        lVar11 = *plVar14;
        *(int *)plVar14 = (int)*plVar14 + -1;
        UNLOCK();
        if ((int)lVar11 == 1) {
          (**(code **)*local_370)(local_370);
          LOCK();
          piVar13 = (int *)((longlong)local_370 + 0x14);
          iVar17 = *piVar13;
          *piVar13 = *piVar13 + -1;
          UNLOCK();
          if (iVar17 == 1) {
            (**(code **)(*local_370 + 8))(local_370);
          }
        }
      }
    }
  }
LAB_14008cae7:
  __security_check_cookie(local_58 ^ (ulonglong)auStack_418);
  return;
}


// ==== CMapData::vf_0x68 @ 14008cb10  undefined8 vf_0x68(longlong * param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, char * param_5)

ulonglong CMapData::vf_0x68(longlong *param_1,undefined4 param_2,undefined4 param_3,
                           undefined4 param_4,char *param_5)

{
  undefined8 uVar1;
  longlong *plVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  undefined2 *puVar5;
  char cVar6;
  short sVar7;
  short sVar8;
  undefined2 uVar9;
  uint uVar10;
  ulonglong extraout_RAX;
  ulonglong extraout_RAX_00;
  ulonglong uVar11;
  longlong lVar12;
  undefined8 *puVar13;
  int *piVar14;
  longlong *plVar15;
  ulonglong extraout_RAX_01;
  undefined8 *puVar16;
  int iVar17;
  longlong lVar18;
  undefined8 *puVar19;
  longlong *plVar20;
  int iVar21;
  longlong local_198;
  int local_190;
  int local_18c;
  int local_188;
  undefined1 local_184;
  undefined1 local_183;
  int local_180;
  longlong *local_178;
  int local_170;
  undefined2 *local_168;
  longlong *local_160;
  longlong *local_158;
  longlong *local_150;
  longlong *local_148;
  int local_140;
  longlong local_138;
  longlong *local_130;
  undefined8 local_128;
  undefined2 *local_120;
  longlong *local_118;
  longlong local_108;
  undefined8 *puStack_100;
  undefined8 local_f8;
  longlong local_f0;
  longlong local_e8;
  longlong local_e0;
  undefined8 *local_d8;
  longlong local_d0;
  undefined8 *local_c8;
  longlong local_b8;
  undefined8 *puStack_b0;
  longlong local_a8;
  undefined8 *puStack_a0;
  longlong *local_98 [3];
  undefined8 local_80;
  undefined8 local_78;
  undefined8 local_70;
  undefined8 local_68;
  longlong local_58;
  undefined8 *puStack_50;
  longlong local_48;
  undefined8 *puStack_40;
  longlong local_38;
  undefined8 *puStack_30;
  
  local_68 = 0xfffffffffffffffe;
  if (param_5 == (char *)0x0) {
    log_InlineLogERROR("CMapData::AddTerrainObj file name is null, owner:%u.");
    uVar11 = extraout_RAX & 0xffffffffffffff00;
  }
  else {
    FUN_140096390(&local_150,param_5,param_2);
    if (local_150 == (longlong *)0x0) {
      log_InlineLogERROR("CMapData::AddTerrainObj cannot create item from file %s for owner %u");
      uVar11 = extraout_RAX_00;
      if (local_148 != (longlong *)0x0) {
        LOCK();
        plVar15 = local_148 + 2;
        lVar12 = *plVar15;
        *(int *)plVar15 = (int)*plVar15 + -1;
        UNLOCK();
        uVar10 = (int)lVar12 - 1;
        uVar11 = (ulonglong)uVar10;
        if (uVar10 == 0) {
          uVar11 = (**(code **)*local_148)(local_148);
          LOCK();
          piVar14 = (int *)((longlong)local_148 + 0x14);
          *piVar14 = *piVar14 + -1;
          UNLOCK();
          if (*piVar14 == 0) {
            uVar11 = (**(code **)(*local_148 + 8))(local_148);
          }
        }
      }
      uVar11 = uVar11 & 0xffffffffffffff00;
    }
    else {
      (**(code **)(*local_150 + 8))(local_150,param_3,param_4);
      lVar12 = FUN_140094a50((longlong)local_150);
      local_140 = (int)lVar12;
      local_170 = 0;
      if (0 < local_140) {
        do {
          iVar21 = local_170;
          FUN_140095250((longlong)local_150,&local_138,local_170);
          puVar13 = (undefined8 *)FUN_140093ba0(local_138);
          uVar1 = *puVar13;
          local_f8 = uVar1;
          puVar13 = (undefined8 *)FUN_140093bc0(local_138);
          local_128 = *puVar13;
          local_190 = 0;
          iVar17 = (int)local_128;
          if (0 < iVar17) {
            do {
              local_180 = 0;
              if (0 < local_128._4_4_) {
                local_188 = (int)uVar1 - local_190;
                do {
                  iVar21 = local_f8._4_4_ - local_180;
                  cVar6 = FUN_14008d7c0((int *)param_1[0x20],local_188,iVar21);
                  if (cVar6 != '\0') {
                    FUN_140093f60(local_138,&local_120,local_190,local_180);
                    FUN_140093af0(&local_168);
                    puVar5 = local_120;
                    local_178 = (longlong *)local_168;
                    if (local_168 == (undefined2 *)0x0) {
                      log_InlineLogERROR("CMapData::AddTerrainObj cannot create layer data");
                      uVar11 = extraout_RAX_01;
                      if (local_160 != (longlong *)0x0) {
                        LOCK();
                        plVar15 = local_160 + 2;
                        lVar12 = *plVar15;
                        *(int *)plVar15 = (int)*plVar15 + -1;
                        UNLOCK();
                        uVar10 = (int)lVar12 - 1;
                        uVar11 = (ulonglong)uVar10;
                        if (uVar10 == 0) {
                          (**(code **)*local_160)(local_160);
                          LOCK();
                          piVar14 = (int *)((longlong)local_160 + 0x14);
                          iVar21 = *piVar14;
                          *piVar14 = *piVar14 + -1;
                          UNLOCK();
                          uVar11 = (ulonglong)(iVar21 - 1U);
                          if (iVar21 - 1U == 0) {
                            uVar11 = (**(code **)(*local_160 + 8))(local_160);
                          }
                        }
                      }
                      if (local_118 != (longlong *)0x0) {
                        LOCK();
                        plVar15 = local_118 + 2;
                        lVar12 = *plVar15;
                        *(int *)plVar15 = (int)*plVar15 + -1;
                        UNLOCK();
                        uVar10 = (int)lVar12 - 1;
                        uVar11 = (ulonglong)uVar10;
                        if (uVar10 == 0) {
                          (**(code **)*local_118)(local_118);
                          LOCK();
                          piVar14 = (int *)((longlong)local_118 + 0x14);
                          iVar21 = *piVar14;
                          *piVar14 = *piVar14 + -1;
                          UNLOCK();
                          uVar11 = (ulonglong)(iVar21 - 1U);
                          if (iVar21 - 1U == 0) {
                            uVar11 = (**(code **)(*local_118 + 8))(local_118);
                          }
                        }
                      }
                      if (local_130 != (longlong *)0x0) {
                        LOCK();
                        plVar15 = local_130 + 2;
                        lVar12 = *plVar15;
                        *(int *)plVar15 = (int)*plVar15 + -1;
                        UNLOCK();
                        uVar10 = (int)lVar12 - 1;
                        uVar11 = (ulonglong)uVar10;
                        if (uVar10 == 0) {
                          (**(code **)*local_130)(local_130);
                          LOCK();
                          piVar14 = (int *)((longlong)local_130 + 0x14);
                          iVar21 = *piVar14;
                          *piVar14 = *piVar14 + -1;
                          UNLOCK();
                          uVar11 = (ulonglong)(iVar21 - 1U);
                          if (iVar21 - 1U == 0) {
                            uVar11 = (**(code **)(*local_130 + 8))(local_130);
                          }
                        }
                      }
                      if (local_148 != (longlong *)0x0) {
                        LOCK();
                        plVar15 = local_148 + 2;
                        lVar12 = *plVar15;
                        *(int *)plVar15 = (int)*plVar15 + -1;
                        UNLOCK();
                        uVar10 = (int)lVar12 - 1;
                        uVar11 = (ulonglong)uVar10;
                        if (uVar10 == 0) {
                          uVar11 = (**(code **)*local_148)(local_148);
                          LOCK();
                          piVar14 = (int *)((longlong)local_148 + 0x14);
                          iVar21 = *piVar14;
                          *piVar14 = *piVar14 + -1;
                          UNLOCK();
                          if (iVar21 == 1) {
                            uVar11 = (**(code **)(*local_148 + 8))(local_148);
                          }
                        }
                      }
                      return uVar11 & 0xffffffffffffff00;
                    }
                    sVar7 = (**(code **)(*param_1 + 8))(param_1,local_188,iVar21);
                    sVar8 = FUN_140093910(puVar5);
                    FUN_140093940((undefined2 *)local_178,sVar8 + sVar7);
                    puVar5 = local_168;
                    uVar9 = FUN_140093920((longlong)local_120);
                    FUN_140093950((longlong)puVar5,uVar9);
                    puVar5 = local_168;
                    uVar9 = FUN_140093930((longlong)local_120);
                    FUN_140093960((longlong)puVar5,uVar9);
                    iVar21 = FUN_14008d7e0((int *)param_1[0x20],local_188,iVar21);
                    local_178 = param_1 + 0x32;
                    puVar13 = (undefined8 *)param_1[0x38];
                    lVar12 = *local_178;
                    cVar6 = *(char *)((longlong)puVar13[1] + 0x21);
                    puVar4 = puVar13;
                    puVar19 = (undefined8 *)puVar13[1];
                    while (cVar6 == '\0') {
                      if (*(int *)(puVar19 + 3) < iVar21) {
                        puVar16 = (undefined8 *)puVar19[2];
                        puVar19 = puVar4;
                      }
                      else {
                        puVar16 = (undefined8 *)*puVar19;
                      }
                      puVar4 = puVar19;
                      puVar19 = puVar16;
                      cVar6 = *(char *)((longlong)puVar16 + 0x21);
                    }
                    local_c8 = puVar4;
                    local_d0 = lVar12;
                    local_18c = iVar21;
                    if (lVar12 == 0) {
                      _invalid_parameter_noinfo();
                    }
                    if ((puVar4 == puVar13) || (iVar21 < *(int *)(puVar4 + 3))) {
                      local_e8 = local_178[6];
                      local_f0 = *local_178;
                      plVar15 = &local_f0;
                    }
                    else {
                      plVar15 = &local_d0;
                    }
                    local_e0 = *plVar15;
                    local_d8 = (undefined8 *)plVar15[1];
                    if ((local_e0 == 0) || (local_e0 != lVar12)) {
                      _invalid_parameter_noinfo();
                    }
                    if (local_d8 == puVar13) {
                      plVar20 = param_1 + 0x14;
                      plVar15 = (longlong *)param_1[0x17];
                      if ((longlong *)param_1[0x18] < plVar15) {
                        _invalid_parameter_noinfo();
                      }
                      plVar2 = (longlong *)*plVar20;
                      while( true ) {
                        plVar3 = (longlong *)param_1[0x18];
                        if (plVar3 < (longlong *)param_1[0x17]) {
                          _invalid_parameter_noinfo();
                        }
                        if ((plVar2 == (longlong *)0x0) || (plVar2 != (longlong *)*plVar20)) {
                          _invalid_parameter_noinfo();
                        }
                        if (plVar15 == plVar3) goto LAB_14008d129;
                        if (plVar2 == (longlong *)0x0) {
                          _invalid_parameter_noinfo();
                          lVar12 = 0;
                        }
                        else {
                          lVar12 = *plVar2;
                        }
                        if (*(longlong **)(lVar12 + 0x20) <= plVar15) {
                          _invalid_parameter_noinfo();
                        }
                        if ((plVar15[4] - plVar15[3] & 0xfffffffffffffff0U) == 0) break;
                        if (plVar2 == (longlong *)0x0) {
                          _invalid_parameter_noinfo();
                          lVar12 = 0;
                        }
                        else {
                          lVar12 = *plVar2;
                        }
                        if (*(longlong **)(lVar12 + 0x20) <= plVar15) {
                          _invalid_parameter_noinfo();
                        }
                        plVar15 = plVar15 + 6;
                      }
                      if (plVar2 == (longlong *)0x0) {
                        _invalid_parameter_noinfo();
                        lVar12 = 0;
                      }
                      else {
                        lVar12 = *plVar2;
                      }
                      if (*(longlong **)(lVar12 + 0x20) <= plVar15) {
                        _invalid_parameter_noinfo();
                      }
                      puVar13 = (undefined8 *)plVar15[3];
                      if (puVar13 == (undefined8 *)0x0) {
                        uVar11 = 0;
                      }
                      else {
                        uVar11 = plVar15[5] - (longlong)puVar13 >> 4;
                      }
                      puVar4 = (undefined8 *)plVar15[4];
                      if ((ulonglong)((longlong)puVar4 - (longlong)puVar13 >> 4) < uVar11) {
                        FUN_140085740(puVar4,1,&local_168);
                        plVar15[4] = (longlong)(puVar4 + 2);
                      }
                      else {
                        if (puVar4 < puVar13) {
                          _invalid_parameter_noinfo();
                        }
                        local_108 = *plVar15;
                        uVar11 = plVar15[3];
                        puStack_100 = puVar4;
                        if ((plVar15[4] - uVar11 & 0xfffffffffffffff0) == 0) {
                          local_198 = 0;
                        }
                        else {
                          if ((ulonglong)plVar15[4] < uVar11) {
                            _invalid_parameter_noinfo();
                          }
                          if ((local_108 == 0) || (local_108 != *plVar15)) {
                            _invalid_parameter_noinfo();
                          }
                          local_198 = (longlong)((longlong)puVar4 - uVar11) >> 4;
                        }
                        local_38 = local_108;
                        puStack_30 = puStack_100;
                        FUN_140087110((longlong)plVar15,(longlong)&local_38,1,(longlong *)&local_168
                                     );
                        local_158 = (longlong *)plVar15[3];
                        if ((ulonglong)plVar15[4] < local_158) {
                          _invalid_parameter_noinfo();
                        }
                        plVar3 = (longlong *)*plVar15;
                        if (plVar3 == (longlong *)0x0) {
                          _invalid_parameter_noinfo();
                          lVar12 = 0;
                        }
                        else {
                          lVar12 = *plVar3;
                        }
                        uVar11 = (longlong)local_158 + local_198 * 0x10;
                        if (uVar11 <= *(ulonglong *)(lVar12 + 0x20)) {
                          if (plVar3 == (longlong *)0x0) {
                            lVar12 = 0;
                          }
                          else {
                            lVar12 = *plVar3;
                          }
                          if (*(ulonglong *)(lVar12 + 0x18) <= uVar11) goto LAB_14008d0c0;
                        }
                        _invalid_parameter_noinfo();
                      }
LAB_14008d0c0:
                      local_158 = (longlong *)param_1[0x17];
                      if ((longlong *)param_1[0x18] < local_158) {
                        _invalid_parameter_noinfo();
                      }
                      if ((plVar2 == (longlong *)0x0) || (plVar2 != (longlong *)*plVar20)) {
                        _invalid_parameter_noinfo();
                      }
                      lVar12 = ((longlong)plVar15 - (longlong)local_158) / 6 +
                               ((longlong)plVar15 - (longlong)local_158 >> 0x3f);
                      piVar14 = (int *)FUN_14003bb80(local_178,&local_18c);
                      *piVar14 = (int)(lVar12 >> 3) - (int)(lVar12 >> 0x3f);
LAB_14008d129:
                      plVar3 = (longlong *)param_1[0x18];
                      if (plVar3 < (longlong *)param_1[0x17]) {
                        _invalid_parameter_noinfo();
                      }
                      if ((plVar2 == (longlong *)0x0) || (plVar2 != (longlong *)*plVar20)) {
                        _invalid_parameter_noinfo();
                      }
                      if (plVar15 == plVar3) {
                        lVar12 = (param_1[0x18] - param_1[0x17]) / 6 +
                                 (param_1[0x18] - param_1[0x17] >> 0x3f);
                        iVar21 = (int)(lVar12 >> 3) - (int)(lVar12 >> 0x3f);
                        piVar14 = (int *)FUN_14003bb80(local_178,&local_18c);
                        *piVar14 = iVar21;
                        local_158 = (longlong *)operator_new(8);
                        if (local_158 == (longlong *)0x0) {
                          local_98[0] = (longlong *)0x0;
                        }
                        else {
                          *local_158 = (longlong)local_98;
                          local_98[0] = local_158;
                        }
                        uVar11 = 0;
                        local_80 = 0;
                        local_78 = 0;
                        local_70 = 0;
                        FUN_14008bb20(plVar20,(longlong)(iVar21 + 1),local_98);
                        plVar15 = (longlong *)FUN_140083e50(plVar20);
                        puVar13 = (undefined8 *)plVar15[3];
                        if (puVar13 != (undefined8 *)0x0) {
                          uVar11 = plVar15[5] - (longlong)puVar13 >> 4;
                        }
                        puVar4 = (undefined8 *)plVar15[4];
                        if ((ulonglong)((longlong)puVar4 - (longlong)puVar13 >> 4) < uVar11) {
                          local_183 = 0;
                          FUN_140085740(puVar4,1,&local_168);
                          plVar15[4] = (longlong)(puVar4 + 2);
                        }
                        else {
                          if (puVar4 < puVar13) {
                            _invalid_parameter_noinfo();
                          }
                          lVar12 = *plVar15;
                          uVar11 = plVar15[3];
                          local_b8 = lVar12;
                          puStack_b0 = puVar4;
                          if ((plVar15[4] - uVar11 & 0xfffffffffffffff0) == 0) {
                            lVar12 = 0;
                          }
                          else {
                            if ((ulonglong)plVar15[4] < uVar11) {
                              _invalid_parameter_noinfo();
                            }
                            if ((lVar12 == 0) || (lVar12 != *plVar15)) {
                              _invalid_parameter_noinfo();
                            }
                            lVar12 = (longlong)((longlong)puVar4 - uVar11) >> 4;
                          }
                          local_48 = local_b8;
                          puStack_40 = puStack_b0;
                          FUN_140087110((longlong)plVar15,(longlong)&local_48,1,
                                        (longlong *)&local_168);
                          uVar11 = plVar15[3];
                          if ((ulonglong)plVar15[4] < uVar11) {
                            _invalid_parameter_noinfo();
                          }
                          plVar15 = (longlong *)*plVar15;
                          if (plVar15 == (longlong *)0x0) {
                            _invalid_parameter_noinfo();
                            lVar18 = 0;
                          }
                          else {
                            lVar18 = *plVar15;
                          }
                          uVar11 = uVar11 + lVar12 * 0x10;
                          if (uVar11 <= *(ulonglong *)(lVar18 + 0x20)) {
                            if (plVar15 == (longlong *)0x0) {
                              lVar12 = 0;
                            }
                            else {
                              lVar12 = *plVar15;
                            }
                            if (*(ulonglong *)(lVar12 + 0x18) <= uVar11) goto LAB_14008d4e8;
                          }
                          _invalid_parameter_noinfo();
                        }
                      }
                    }
                    else {
                      piVar14 = (int *)FUN_14003bb80(local_178,&local_18c);
                      iVar21 = *piVar14;
                      if ((ulonglong)((param_1[0x18] - param_1[0x17]) / 0x30) <=
                          (ulonglong)(longlong)iVar21) {
                        _invalid_parameter_noinfo();
                      }
                      plVar15 = (longlong *)((longlong)iVar21 * 0x30 + param_1[0x17]);
                      puVar13 = (undefined8 *)plVar15[3];
                      if (puVar13 == (undefined8 *)0x0) {
                        uVar11 = 0;
                      }
                      else {
                        uVar11 = plVar15[5] - (longlong)puVar13 >> 4;
                      }
                      puVar4 = (undefined8 *)plVar15[4];
                      if ((ulonglong)((longlong)puVar4 - (longlong)puVar13 >> 4) < uVar11) {
                        local_184 = 0;
                        FUN_140085740(puVar4,1,&local_168);
                        plVar15[4] = (longlong)(puVar4 + 2);
                      }
                      else {
                        if (puVar4 < puVar13) {
                          _invalid_parameter_noinfo();
                        }
                        lVar12 = *plVar15;
                        uVar11 = plVar15[3];
                        local_a8 = lVar12;
                        puStack_a0 = puVar4;
                        if ((plVar15[4] - uVar11 & 0xfffffffffffffff0) == 0) {
                          lVar12 = 0;
                        }
                        else {
                          if ((ulonglong)plVar15[4] < uVar11) {
                            _invalid_parameter_noinfo();
                          }
                          if ((lVar12 == 0) || (lVar12 != *plVar15)) {
                            _invalid_parameter_noinfo();
                          }
                          lVar12 = (longlong)((longlong)puVar4 - uVar11) >> 4;
                        }
                        local_58 = local_a8;
                        puStack_50 = puStack_a0;
                        FUN_140087110((longlong)plVar15,(longlong)&local_58,1,(longlong *)&local_168
                                     );
                        uVar11 = plVar15[3];
                        if ((ulonglong)plVar15[4] < uVar11) {
                          _invalid_parameter_noinfo();
                        }
                        plVar15 = (longlong *)*plVar15;
                        if (plVar15 == (longlong *)0x0) {
                          _invalid_parameter_noinfo();
                          lVar18 = 0;
                        }
                        else {
                          lVar18 = *plVar15;
                        }
                        uVar11 = uVar11 + lVar12 * 0x10;
                        if (uVar11 <= *(ulonglong *)(lVar18 + 0x20)) {
                          if (plVar15 == (longlong *)0x0) {
                            lVar12 = 0;
                          }
                          else {
                            lVar12 = *plVar15;
                          }
                          if (*(ulonglong *)(lVar12 + 0x18) <= uVar11) goto LAB_14008d4e8;
                        }
                        _invalid_parameter_noinfo();
                      }
                    }
LAB_14008d4e8:
                    plVar15 = local_160;
                    if (local_160 != (longlong *)0x0) {
                      LOCK();
                      plVar20 = local_160 + 2;
                      *(int *)plVar20 = (int)*plVar20 + -1;
                      UNLOCK();
                      if ((int)*plVar20 == 0) {
                        (**(code **)*local_160)(local_160);
                        LOCK();
                        piVar14 = (int *)((longlong)plVar15 + 0x14);
                        *piVar14 = *piVar14 + -1;
                        UNLOCK();
                        if (*piVar14 == 0) {
                          (**(code **)(*plVar15 + 8))(plVar15);
                        }
                      }
                    }
                    plVar15 = local_118;
                    if (local_118 != (longlong *)0x0) {
                      LOCK();
                      plVar20 = local_118 + 2;
                      lVar12 = *plVar20;
                      *(int *)plVar20 = (int)*plVar20 + -1;
                      UNLOCK();
                      if ((int)lVar12 == 1) {
                        (**(code **)*local_118)(local_118);
                        LOCK();
                        piVar14 = (int *)((longlong)plVar15 + 0x14);
                        iVar21 = *piVar14;
                        *piVar14 = *piVar14 + -1;
                        UNLOCK();
                        if (iVar21 == 1) {
                          (**(code **)(*plVar15 + 8))(plVar15);
                        }
                      }
                    }
                  }
                  local_180 = local_180 + 1;
                } while (local_180 < local_128._4_4_);
              }
              local_190 = local_190 + 1;
              iVar21 = local_170;
            } while (local_190 < iVar17);
          }
          plVar15 = local_130;
          if (local_130 != (longlong *)0x0) {
            LOCK();
            plVar20 = local_130 + 2;
            lVar12 = *plVar20;
            *(int *)plVar20 = (int)*plVar20 + -1;
            UNLOCK();
            if ((int)lVar12 == 1) {
              (**(code **)*local_130)(local_130);
              LOCK();
              piVar14 = (int *)((longlong)plVar15 + 0x14);
              iVar17 = *piVar14;
              *piVar14 = *piVar14 + -1;
              UNLOCK();
              if (iVar17 == 1) {
                (**(code **)(*plVar15 + 8))(plVar15);
              }
            }
          }
          local_170 = iVar21 + 1;
        } while (local_170 < local_140);
      }
      lVar12 = param_1[0x30];
      puVar13 = FUN_140085480(param_1 + 0x2b,lVar12,*(undefined8 *)(lVar12 + 8),&local_150);
      uVar11 = FUN_140082600((longlong)(param_1 + 0x2b),1);
      *(undefined8 **)(lVar12 + 8) = puVar13;
      *(undefined8 **)puVar13[1] = puVar13;
      if (local_148 != (longlong *)0x0) {
        LOCK();
        plVar15 = local_148 + 2;
        lVar12 = *plVar15;
        *(int *)plVar15 = (int)*plVar15 + -1;
        UNLOCK();
        uVar10 = (int)lVar12 - 1;
        uVar11 = (ulonglong)uVar10;
        if (uVar10 == 0) {
          uVar11 = (**(code **)*local_148)(local_148);
          LOCK();
          piVar14 = (int *)((longlong)local_148 + 0x14);
          iVar21 = *piVar14;
          *piVar14 = *piVar14 + -1;
          UNLOCK();
          if (iVar21 == 1) {
            uVar11 = (**(code **)(*local_148 + 8))(local_148);
          }
        }
      }
      uVar11 = CONCAT71((int7)(uVar11 >> 8),1);
    }
  }
  return uVar11;
}


