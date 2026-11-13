// NpcServer.exe :: CNeuralAIStrategy  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CNeuralAIStrategy::vf_0x0 @ 1400474d0  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CNeuralAIStrategy::vf_0x0(undefined8 *param_1,uint param_2)

{
  FUN_140067730(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CNeuralAIStrategy::vf_0x10 @ 140067090  undefined vf_0x10(longlong param_1, double param_2)

void CNeuralAIStrategy::vf_0x10(longlong param_1,double param_2)

{
  *(double *)(param_1 + 8) = param_2 + *(double *)(param_1 + 8);
  return;
}


// ==== CNeuralAIStrategy::vf_0x8 @ 1400670a0  double vf_0x8(longlong param_1)

double CNeuralAIStrategy::vf_0x8(longlong param_1)

{
  return *(double *)(param_1 + 0x10) / *(double *)(param_1 + 8);
}


// ==== CNeuralAIStrategy::vf_0x18 @ 1400670b0  undefined vf_0x18(longlong param_1, double param_2)

void CNeuralAIStrategy::vf_0x18(longlong param_1,double param_2)

{
  *(double *)(param_1 + 0x10) = param_2 + *(double *)(param_1 + 0x10);
  return;
}


// ==== CNeuralAIStrategy::vf_0x20 @ 140067390  undefined vf_0x20(longlong param_1, longlong * param_2)

void CNeuralAIStrategy::vf_0x20(longlong param_1,longlong *param_2)

{
  double dVar1;
  char cVar2;
  ulonglong uVar3;
  longlong *plVar4;
  undefined8 uVar5;
  double *pdVar6;
  undefined8 *puVar7;
  undefined8 *puVar8;
  int iVar9;
  longlong *plVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined8 *local_98;
  void *pvStack_90;
  longlong *local_88 [3];
  void *local_70;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 *local_58 [3];
  void *local_40;
  void *local_38;
  undefined8 local_30;
  
  if (param_2 == (longlong *)0x0) {
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  else {
    uVar3 = FUN_14005b5c0((longlong)param_2);
    if (((char)uVar3 == '\0') && (cVar2 = (**(code **)(param_2[2] + 0x50))(), cVar2 != '\0')) {
      iVar9 = 8;
      plVar4 = (longlong *)operator_new(8);
      plVar10 = (longlong *)0x0;
      local_88[0] = plVar10;
      if (plVar4 != (longlong *)0x0) {
        *plVar4 = (longlong)local_88;
        local_88[0] = plVar4;
      }
      local_70 = (void *)0x0;
      local_68 = 0;
      local_60 = 0;
      uVar5 = FUN_14005f1b0((longlong)param_2,(longlong *)local_88);
      if ((char)uVar5 == '\0') {
        FUN_14005e900(param_2);
        if (local_70 != (void *)0x0) {
          operator_delete(local_70);
        }
        local_70 = (void *)0x0;
        local_68 = 0;
        local_60 = 0;
        operator_delete(local_88[0]);
      }
      else {
        FUN_14006bdf0(param_1 + 0x18,local_58,(longlong *)local_88);
        if (local_38 < local_40) {
          _invalid_parameter_noinfo();
        }
        puVar7 = local_58[0];
        local_98 = local_58[0];
        pvStack_90 = local_38;
        pdVar6 = (double *)FUN_140067230((longlong *)&local_98);
        dVar1 = *pdVar6;
        uVar11 = SUB84(dVar1,0);
        uVar12 = (undefined4)((ulonglong)dVar1 >> 0x20);
        if (puVar7 == (undefined8 *)0x0) {
          _invalid_parameter_noinfo();
          plVar4 = plVar10;
        }
        else {
          plVar4 = (longlong *)*puVar7;
        }
        if (local_38 <= (void *)plVar4[3]) {
          _invalid_parameter_noinfo();
        }
        pvStack_90 = (void *)((longlong)local_38 - 8U);
        pdVar6 = (double *)FUN_140067230((longlong *)&local_98);
        if (dVar1 < *pdVar6) {
          puVar7 = (undefined8 *)FUN_140067230((longlong *)&local_98);
          uVar11 = (undefined4)*puVar7;
          uVar12 = (undefined4)((ulonglong)*puVar7 >> 0x20);
          iVar9 = 7;
        }
        puVar7 = local_98;
        if (local_98 == (undefined8 *)0x0) {
          _invalid_parameter_noinfo();
          plVar4 = plVar10;
        }
        else {
          plVar4 = (longlong *)*local_98;
        }
        if ((longlong)local_38 - 8U <= (ulonglong)plVar4[3]) {
          _invalid_parameter_noinfo();
        }
        pvStack_90 = (void *)((longlong)local_38 - 0x10U);
        pdVar6 = (double *)FUN_140067230((longlong *)&local_98);
        if ((double)CONCAT44(uVar12,uVar11) <= *pdVar6 && *pdVar6 != (double)CONCAT44(uVar12,uVar11)
           ) {
          puVar8 = (undefined8 *)FUN_140067230((longlong *)&local_98);
          uVar11 = (undefined4)*puVar8;
          uVar12 = (undefined4)((ulonglong)*puVar8 >> 0x20);
          iVar9 = 6;
        }
        if (puVar7 == (undefined8 *)0x0) {
          _invalid_parameter_noinfo();
        }
        else {
          plVar10 = (longlong *)*puVar7;
        }
        if ((longlong)local_38 - 0x10U <= (ulonglong)plVar10[3]) {
          _invalid_parameter_noinfo();
        }
        pvStack_90 = (void *)((longlong)local_38 + -0x18);
        pdVar6 = (double *)FUN_140067230((longlong *)&local_98);
        if ((double)CONCAT44(uVar12,uVar11) <= *pdVar6 && *pdVar6 != (double)CONCAT44(uVar12,uVar11)
           ) {
          iVar9 = 1;
        }
        if (iVar9 == 1) {
          FUN_14005e900(param_2);
        }
        else if (iVar9 == 6) {
          FUN_14005d140(param_2);
        }
        else if (iVar9 == 7) {
          FUN_14005d550(param_2);
        }
        else if (iVar9 == 8) {
          FUN_14005d330(param_2);
        }
        if (local_40 != (void *)0x0) {
          operator_delete(local_40);
        }
        local_40 = (void *)0x0;
        local_38 = (void *)0x0;
        local_30 = 0;
        operator_delete(local_58[0]);
        if (local_70 != (void *)0x0) {
          operator_delete(local_70);
        }
        local_70 = (void *)0x0;
        local_68 = 0;
        local_60 = 0;
        operator_delete(local_88[0]);
      }
    }
  }
  return;
}


