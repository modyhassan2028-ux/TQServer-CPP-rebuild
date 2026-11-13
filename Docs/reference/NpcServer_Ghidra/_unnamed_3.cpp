// NpcServer.exe :: _unnamed  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== FUN_140034000 @ 140034000  undefined FUN_140034000(longlong * param_1)

void FUN_140034000(longlong *param_1)

{
  FUN_140033f60(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140034030 @ 140034030  undefined8 * FUN_140034030(undefined8 * param_1)

undefined8 * FUN_140034030(undefined8 *param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  lVar2 = FUN_140029270();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x51) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_1400340b0 @ 1400340b0  undefined FUN_1400340b0(longlong * param_1)

void FUN_1400340b0(longlong *param_1)

{
  FUN_140033f60(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_1400340e0 @ 1400340e0  undefined FUN_1400340e0(longlong param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_1400340e0(longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong *plVar4;
  undefined8 *puVar5;
  longlong *plVar6;
  longlong *plVar7;
  longlong lVar8;
  longlong *local_58;
  longlong *plStack_50;
  longlong *local_48;
  longlong *plStack_40;
  longlong local_38 [2];
  
  if (*(longlong *)(param_1 + 8) != 0) {
    (**(code **)(**(longlong **)(param_1 + 8) + 8))
              (*(longlong **)(param_1 + 8),param_2,param_3,param_4,0xfffffffffffffffe);
  }
  if (*(longlong *)(param_1 + 0x120) != 0) {
    plVar6 = (longlong *)**(undefined8 **)(param_1 + 0x118);
    plVar2 = *(longlong **)(param_1 + 0xe8);
    while( true ) {
      plVar7 = *(longlong **)(param_1 + 0x118);
      if ((plVar2 == (longlong *)0x0) || (plVar2 != *(longlong **)(param_1 + 0xe8))) {
        _invalid_parameter_noinfo();
      }
      if (plVar6 == plVar7) break;
      if (plVar2 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar8 = 0;
      }
      else {
        lVar8 = *plVar2;
      }
      if (plVar6 == *(longlong **)(lVar8 + 0x30)) {
        _invalid_parameter_noinfo();
      }
      log_InlineLogERROR("CNpcManager::~CNpcManager. DynaGen[%u] not release");
      if (plVar2 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
      }
      if (*(char *)((longlong)plVar6 + 0x51) == '\0') {
        plVar7 = (longlong *)plVar6[2];
        if (*(char *)((longlong)plVar7 + 0x51) == '\0') {
          cVar1 = *(char *)(*plVar7 + 0x51);
          plVar6 = plVar7;
          plVar7 = (longlong *)*plVar7;
          while (cVar1 == '\0') {
            cVar1 = *(char *)(*plVar7 + 0x51);
            plVar6 = plVar7;
            plVar7 = (longlong *)*plVar7;
          }
        }
        else {
          cVar1 = *(char *)(plVar6[1] + 0x51);
          plVar3 = (longlong *)plVar6[1];
          plVar7 = plVar6;
          while ((plVar6 = plVar3, cVar1 == '\0' && (plVar7 == (longlong *)plVar6[2]))) {
            cVar1 = *(char *)(plVar6[1] + 0x51);
            plVar3 = (longlong *)plVar6[1];
            plVar7 = plVar6;
          }
        }
      }
      else {
        _invalid_parameter_noinfo();
      }
    }
  }
  if (*(longlong *)(param_1 + 0x10) != 0) {
    (**(code **)(**(longlong **)(param_1 + 0x10) + 8))();
  }
  if (*(longlong *)(param_1 + 0x18) != 0) {
    (**(code **)(**(longlong **)(param_1 + 0x18) + 8))();
  }
  if (*(longlong *)(param_1 + 0x20) != 0) {
    (**(code **)(**(longlong **)(param_1 + 0x20) + 8))();
  }
  plVar6 = (longlong *)**(longlong **)(param_1 + 0xd8);
  plVar2 = *(longlong **)(param_1 + 0xa8);
  local_58 = plVar2;
  plStack_50 = plVar6;
  while( true ) {
    plVar7 = *(longlong **)(param_1 + 0xd8);
    if ((*(longlong **)(param_1 + 0xa8) == (longlong *)0x0) ||
       (*(longlong **)(param_1 + 0xa8) != plVar2)) {
      _invalid_parameter_noinfo();
    }
    if (plVar7 == plVar6) break;
    if (plVar2 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar8 = 0;
    }
    else {
      lVar8 = *plVar2;
    }
    if (plVar6 == *(longlong **)(lVar8 + 0x30)) {
      _invalid_parameter_noinfo();
    }
    plVar7 = (longlong *)plVar6[7];
    if ((longlong *)plVar6[8] < plVar7) {
      _invalid_parameter_noinfo();
    }
    plVar3 = (longlong *)plVar6[4];
    local_48 = plVar3;
    while( true ) {
      plStack_40 = plVar7;
      if (plVar2 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar8 = 0;
      }
      else {
        lVar8 = *plVar2;
      }
      if (plVar6 == *(longlong **)(lVar8 + 0x30)) {
        _invalid_parameter_noinfo();
      }
      plVar4 = (longlong *)plVar6[8];
      if (plVar4 < (longlong *)plVar6[7]) {
        _invalid_parameter_noinfo();
      }
      if ((plVar3 == (longlong *)0x0) || (plVar3 != (longlong *)plVar6[4])) {
        _invalid_parameter_noinfo();
      }
      if (plVar7 == plVar4) break;
      if (plVar3 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar8 = 0;
      }
      else {
        lVar8 = *plVar3;
      }
      if (*(longlong **)(lVar8 + 0x20) <= plVar7) {
        _invalid_parameter_noinfo();
      }
      puVar5 = (undefined8 *)*plVar7;
      if (puVar5 != (undefined8 *)0x0) {
        (**(code **)*puVar5)(puVar5,1);
      }
      if (plVar3 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar8 = 0;
      }
      else {
        lVar8 = *plVar3;
      }
      if (*(longlong **)(lVar8 + 0x20) <= plVar7) {
        _invalid_parameter_noinfo();
      }
      plVar7 = plVar7 + 1;
    }
    if (plVar2 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
    }
    if (*(char *)((longlong)plVar6 + 0x51) == '\0') {
      plVar7 = (longlong *)plVar6[2];
      if (*(char *)((longlong)plVar7 + 0x51) == '\0') {
        cVar1 = *(char *)(*plVar7 + 0x51);
        plVar6 = plVar7;
        plVar7 = (longlong *)*plVar7;
        while (plStack_50 = plVar6, cVar1 == '\0') {
          cVar1 = *(char *)(*plVar7 + 0x51);
          plVar6 = plVar7;
          plVar7 = (longlong *)*plVar7;
        }
      }
      else {
        cVar1 = *(char *)(plVar6[1] + 0x51);
        plVar3 = (longlong *)plVar6[1];
        plVar7 = plVar6;
        while ((plVar6 = plVar3, plStack_50 = plVar6, cVar1 == '\0' &&
               (plVar7 == (longlong *)plVar6[2]))) {
          cVar1 = *(char *)(plVar6[1] + 0x51);
          plVar3 = (longlong *)plVar6[1];
          plVar7 = plVar6;
        }
      }
    }
    else {
      _invalid_parameter_noinfo();
    }
  }
  plVar6 = (longlong *)(param_1 + 0xe8);
  plStack_40 = *(longlong **)(param_1 + 0x118);
  local_58 = (longlong *)*plVar6;
  plStack_50 = (longlong *)*plStack_40;
  local_48 = local_58;
  FUN_140033aa0(plVar6,local_38,(longlong *)&local_58,(longlong *)&local_48);
  operator_delete(*(void **)(param_1 + 0x118));
  *(undefined8 *)(param_1 + 0x118) = 0;
  *(undefined8 *)(param_1 + 0x120) = 0;
  operator_delete((void *)*plVar6);
  plVar6 = (longlong *)(param_1 + 0xa8);
  plStack_40 = *(longlong **)(param_1 + 0xd8);
  local_58 = (longlong *)*plVar6;
  plStack_50 = (longlong *)*plStack_40;
  local_48 = local_58;
  FUN_140033d50(plVar6,local_38,(longlong *)&local_58,(longlong *)&local_48);
  operator_delete(*(void **)(param_1 + 0xd8));
  *(undefined8 *)(param_1 + 0xd8) = 0;
  *(undefined8 *)(param_1 + 0xe0) = 0;
  operator_delete((void *)*plVar6);
  FUN_140028bf0(param_1 + 0x68);
  operator_delete(*(void **)(param_1 + 0x68));
  FUN_140028bf0(param_1 + 0x28);
  operator_delete(*(void **)(param_1 + 0x28));
  return;
}


// ==== FUN_140034550 @ 140034550  undefined8 * FUN_140034550(undefined8 * param_1)

undefined8 * FUN_140034550(undefined8 *param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  lVar2 = FUN_140029210();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x51) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_1400345d0 @ 1400345d0  undefined4 * FUN_1400345d0(undefined4 * param_1)

undefined4 * FUN_1400345d0(undefined4 *param_1)

{
  longlong *plVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  longlong *plVar4;
  CIniFile *this;
  CIniFile local_420 [1032];
  
  plVar1 = (longlong *)operator_new(8);
  plVar4 = (longlong *)0x0;
  plVar3 = plVar4;
  if (plVar1 != (longlong *)0x0) {
    *plVar1 = (longlong)(param_1 + 10);
    plVar3 = plVar1;
  }
  *(longlong **)(param_1 + 10) = plVar3;
  *(undefined8 *)(param_1 + 0x12) = 0;
  *(undefined8 *)(param_1 + 0x14) = 0;
  *(undefined8 *)(param_1 + 0x16) = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  plVar1 = (longlong *)operator_new(8);
  plVar3 = plVar4;
  if (plVar1 != (longlong *)0x0) {
    *plVar1 = (longlong)(param_1 + 0x1a);
    plVar3 = plVar1;
  }
  *(longlong **)(param_1 + 0x1a) = plVar3;
  *(undefined8 *)(param_1 + 0x22) = 0;
  *(undefined8 *)(param_1 + 0x24) = 0;
  *(undefined8 *)(param_1 + 0x26) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  FUN_140034550((undefined8 *)(param_1 + 0x2a));
  FUN_140034030((undefined8 *)(param_1 + 0x3a));
  plVar1 = (longlong *)operator_new(0x50);
  plVar3 = plVar4;
  if (plVar1 != (longlong *)0x0) {
    *plVar1 = (longlong)ISingleMap<class_INpc>::vftable;
    *plVar1 = (longlong)CSingleMap<class_INpc>::vftable;
    FUN_14002f680(plVar1 + 2);
    *(undefined1 *)(plVar1 + 1) = 1;
    plVar3 = plVar1;
  }
  *(longlong **)(param_1 + 2) = plVar3;
  puVar2 = (undefined8 *)operator_new(0x40);
  plVar3 = plVar4;
  if (puVar2 != (undefined8 *)0x0) {
    plVar3 = FUN_14002ba50(puVar2,1);
  }
  *(longlong **)(param_1 + 4) = plVar3;
  puVar2 = (undefined8 *)operator_new(0x40);
  plVar3 = plVar4;
  if (puVar2 != (undefined8 *)0x0) {
    plVar3 = FUN_14002ba50(puVar2,1);
  }
  *(longlong **)(param_1 + 6) = plVar3;
  puVar2 = (undefined8 *)operator_new(0x40);
  if (puVar2 != (undefined8 *)0x0) {
    plVar4 = FUN_14002c5a0(puVar2,1);
  }
  *(longlong **)(param_1 + 8) = plVar4;
  *param_1 = 400000;
  param_1[1] = 100000000;
  this = (CIniFile *)CIniFile::CIniFile(local_420,"config.ini","GameServer");
  DAT_1401028c0 = CIniFile::GetInt(this,"MaxNpcPerTimer");
  CIniFile::~CIniFile(local_420);
  if (DAT_1401028c0 < 1) {
    DAT_1401028c0 = 0x14;
  }
  return param_1;
}


// ==== FUN_1400347d0 @ 1400347d0  undefined8 FUN_1400347d0(void * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

undefined8 FUN_1400347d0(void *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  if (param_1 != (void *)0x0) {
    FUN_1400340e0((longlong)param_1,param_2,param_3,param_4);
    operator_delete(param_1);
  }
  return 0;
}


// ==== FUN_140034810 @ 140034810  undefined FUN_140034810(undefined8 * param_1)

void FUN_140034810(undefined8 *param_1)

{
  *param_1 = CNetMsg::vftable;
  return;
}


// ==== FUN_140034820 @ 140034820  undefined FUN_140034820(longlong param_1)

void FUN_140034820(longlong param_1)

{
  memset((void *)(param_1 + 0x10),0,0x400);
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  return;
}


// ==== FUN_140034920 @ 140034920  undefined8 * FUN_140034920(undefined8 * param_1)

undefined8 * FUN_140034920(undefined8 *param_1)

{
  *(undefined4 *)(param_1 + 0x82) = 0;
  *param_1 = CNetMsg::vftable;
  memset(param_1 + 2,0,0x400);
  *(undefined4 *)((longlong)param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 1) = 0;
  return param_1;
}


// ==== FUN_1400349a0 @ 1400349a0  longlong * FUN_1400349a0(undefined4 param_1, uint param_2, longlong param_3, int param_4)

longlong * FUN_1400349a0(undefined4 param_1,uint param_2,longlong param_3,int param_4)

{
  int iVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  
  if (((param_2 == 0) || (param_3 == 0)) || (0x400 < param_4)) {
    return (longlong *)0x0;
  }
  if (0x961 < param_2) {
    if (param_2 < 0x2722) {
      if (param_2 == 0x2721) {
        puVar2 = (undefined8 *)operator_new(0x420);
        if (puVar2 == (undefined8 *)0x0) {
          plVar3 = (longlong *)0x0;
        }
        else {
          plVar3 = FUN_140061930(puVar2);
        }
      }
      else if (param_2 == 0x2715) {
        puVar2 = (undefined8 *)operator_new(0x468);
        if (puVar2 == (undefined8 *)0x0) {
          plVar3 = (longlong *)0x0;
        }
        else {
          plVar3 = FUN_140062030(puVar2);
        }
      }
      else if (param_2 == 0x271a) {
        puVar2 = (undefined8 *)operator_new(0x420);
        if (puVar2 == (undefined8 *)0x0) {
          plVar3 = (longlong *)0x0;
        }
        else {
          plVar3 = FUN_1400623e0(puVar2);
        }
      }
      else {
        if (param_2 != 0x271e) goto switchD_140034a2c_caseD_3eb;
        puVar2 = (undefined8 *)operator_new(0x438);
        if (puVar2 == (undefined8 *)0x0) {
          plVar3 = (longlong *)0x0;
        }
        else {
          plVar3 = FUN_140062f80(puVar2);
        }
      }
    }
    else if (param_2 == 0x4e21) {
      puVar2 = (undefined8 *)operator_new(0x420);
      if (puVar2 == (undefined8 *)0x0) {
        plVar3 = (longlong *)0x0;
      }
      else {
        plVar3 = FUN_140061220(puVar2);
      }
    }
    else if (param_2 == 0x4e22) {
      puVar2 = (undefined8 *)operator_new(0x420);
      if (puVar2 == (undefined8 *)0x0) {
        plVar3 = (longlong *)0x0;
      }
      else {
        plVar3 = FUN_140061610(puVar2);
      }
    }
    else {
      if (param_2 != 0x4e23) goto switchD_140034a2c_caseD_3eb;
      puVar2 = (undefined8 *)operator_new(0x420);
      if (puVar2 == (undefined8 *)0x0) {
        plVar3 = (longlong *)0x0;
      }
      else {
        plVar3 = FUN_1400617f0(puVar2);
      }
    }
    goto LAB_140034ce5;
  }
  if (param_2 == 0x961) {
    puVar2 = (undefined8 *)operator_new(0x438);
    if (puVar2 == (undefined8 *)0x0) {
      plVar3 = (longlong *)0x0;
    }
    else {
      plVar3 = FUN_140063490(puVar2);
    }
    goto LAB_140034ce5;
  }
  switch(param_2) {
  case 0x3ea:
    puVar2 = (undefined8 *)operator_new(0x420);
    if (puVar2 == (undefined8 *)0x0) {
      plVar3 = (longlong *)0x0;
    }
    else {
      plVar3 = FUN_140048d20(puVar2);
    }
    break;
  default:
    goto switchD_140034a2c_caseD_3eb;
  case 0x3ec:
    puVar2 = (undefined8 *)operator_new(0x438);
    if (puVar2 == (undefined8 *)0x0) {
      plVar3 = (longlong *)0x0;
    }
    else {
      plVar3 = FUN_140064d20(puVar2);
    }
    break;
  case 0x3fe:
    puVar2 = (undefined8 *)operator_new(0x420);
    if (puVar2 == (undefined8 *)0x0) {
      plVar3 = (longlong *)0x0;
    }
    else {
      plVar3 = FUN_140064650(puVar2);
    }
    break;
  case 0x40f:
    puVar2 = (undefined8 *)operator_new(0x438);
    if (puVar2 == (undefined8 *)0x0) {
      plVar3 = (longlong *)0x0;
    }
    else {
      plVar3 = FUN_140063b90(puVar2);
    }
    break;
  case 0x412:
    puVar2 = (undefined8 *)operator_new(0x420);
    if (puVar2 == (undefined8 *)0x0) {
      plVar3 = (longlong *)0x0;
    }
    else {
      plVar3 = FUN_140063a10(puVar2);
    }
    break;
  case 0x451:
    puVar2 = (undefined8 *)operator_new(0x420);
    if (puVar2 == (undefined8 *)0x0) {
      plVar3 = (longlong *)0x0;
    }
    else {
      plVar3 = FUN_140063ee0(puVar2);
    }
    break;
  case 0x456:
    puVar2 = (undefined8 *)operator_new(0x420);
    if (puVar2 == (undefined8 *)0x0) {
      plVar3 = (longlong *)0x0;
    }
    else {
      plVar3 = FUN_1400638a0(puVar2);
    }
    break;
  case 0x45a:
    puVar2 = (undefined8 *)operator_new(0x420);
    if (puVar2 == (undefined8 *)0x0) {
      plVar3 = (longlong *)0x0;
    }
    else {
      plVar3 = FUN_140063630(puVar2);
    }
  }
LAB_140034ce5:
  if (plVar3 == (longlong *)0x0) {
switchD_140034a2c_caseD_3eb:
    plVar3 = (longlong *)0x0;
  }
  else {
    *(undefined4 *)(plVar3 + 0x82) = param_1;
    *(uint *)(plVar3 + 1) = param_2;
    *(int *)((longlong)plVar3 + 0xc) = param_4;
    iVar1 = (**(code **)(*plVar3 + 8))(plVar3,param_3,param_4);
    if (iVar1 == 0) {
      (**(code **)*plVar3)(plVar3,1);
      plVar3 = (longlong *)0x0;
    }
  }
  return plVar3;
}


// ==== FUN_140034de0 @ 140034de0  undefined FUN_140034de0(longlong * param_1)

void FUN_140034de0(longlong *param_1)

{
  if ((longlong *)*param_1 != (longlong *)0x0) {
    (**(code **)(*(longlong *)*param_1 + 8))();
  }
  return;
}


// ==== FUN_140034e00 @ 140034e00  undefined8 FUN_140034e00(longlong * param_1)

undefined8 FUN_140034e00(longlong *param_1)

{
  undefined8 uVar1;
  
  if ((longlong *)*param_1 == (longlong *)0x0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return 0;
  }
                    /* WARNING: Could not recover jumptable at 0x000140034e44. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (**(code **)(*(longlong *)*param_1 + 0x40))();
  return uVar1;
}


// ==== FUN_140034e50 @ 140034e50  longlong * FUN_140034e50(longlong * param_1, uint param_2)

longlong * FUN_140034e50(longlong *param_1,uint param_2)

{
  if ((longlong *)*param_1 != (longlong *)0x0) {
    (**(code **)(*(longlong *)*param_1 + 8))();
  }
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_140034e90 @ 140034e90  undefined FUN_140034e90(void)

void FUN_140034e90(void)

{
  longlong *plVar1;
  
  plVar1 = DAT_1401045d0;
  if (DAT_1401045d0 != (longlong *)0x0) {
    if ((longlong *)*DAT_1401045d0 != (longlong *)0x0) {
      (**(code **)(*(longlong *)*DAT_1401045d0 + 8))();
    }
    operator_delete(plVar1);
    DAT_1401045d0 = (longlong *)0x0;
  }
  return;
}


// ==== FUN_140034ed0 @ 140034ed0  undefined FUN_140034ed0(undefined8 * param_1)

void FUN_140034ed0(undefined8 *param_1)

{
  *param_1 = ISingleMap<class_CNpcPath>::vftable;
  return;
}


// ==== FUN_1400350d0 @ 1400350d0  bool FUN_1400350d0(longlong * param_1, longlong * param_2)

bool FUN_1400350d0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_1400351f0 @ 1400351f0  undefined FUN_1400351f0(longlong param_1, longlong param_2)

void FUN_1400351f0(longlong param_1,longlong param_2)

{
  longlong *plVar1;
  longlong *plVar2;
  
  plVar1 = *(longlong **)(param_2 + 0x10);
  *(longlong *)(param_2 + 0x10) = *plVar1;
  if (*(char *)(*plVar1 + 0x29) == '\0') {
    *(longlong *)(*plVar1 + 8) = param_2;
  }
  plVar1[1] = *(longlong *)(param_2 + 8);
  if (param_2 == *(longlong *)(*(longlong *)(param_1 + 0x30) + 8)) {
    *(longlong **)(*(longlong *)(param_1 + 0x30) + 8) = plVar1;
    *plVar1 = param_2;
    *(longlong **)(param_2 + 8) = plVar1;
    return;
  }
  plVar2 = *(longlong **)(param_2 + 8);
  if (param_2 == *plVar2) {
    *plVar2 = (longlong)plVar1;
    *plVar1 = param_2;
    *(longlong **)(param_2 + 8) = plVar1;
    return;
  }
  plVar2[2] = (longlong)plVar1;
  *plVar1 = param_2;
  *(longlong **)(param_2 + 8) = plVar1;
  return;
}


// ==== FUN_140035280 @ 140035280  undefined FUN_140035280(longlong param_1, longlong * param_2)

void FUN_140035280(longlong param_1,longlong *param_2)

{
  longlong lVar1;
  longlong *plVar2;
  
  lVar1 = *param_2;
  *param_2 = *(longlong *)(lVar1 + 0x10);
  if (*(char *)(*(longlong *)(lVar1 + 0x10) + 0x29) == '\0') {
    *(longlong **)(*(longlong *)(lVar1 + 0x10) + 8) = param_2;
  }
  *(longlong *)(lVar1 + 8) = param_2[1];
  if (param_2 == *(longlong **)(*(longlong *)(param_1 + 0x30) + 8)) {
    *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = lVar1;
    *(longlong **)(lVar1 + 0x10) = param_2;
    param_2[1] = lVar1;
    return;
  }
  plVar2 = (longlong *)param_2[1];
  if (param_2 == (longlong *)plVar2[2]) {
    plVar2[2] = lVar1;
    *(longlong **)(lVar1 + 0x10) = param_2;
    param_2[1] = lVar1;
    return;
  }
  *plVar2 = lVar1;
  *(longlong **)(lVar1 + 0x10) = param_2;
  param_2[1] = lVar1;
  return;
}


// ==== FUN_140035320 @ 140035320  undefined FUN_140035320(ulonglong param_1)

void FUN_140035320(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x30)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 * 0x30);
  return;
}


// ==== FUN_1400353c0 @ 1400353c0  bool FUN_1400353c0(longlong * param_1, longlong * param_2)

bool FUN_1400353c0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_140035420 @ 140035420  undefined FUN_140035420(longlong * param_1)

void FUN_140035420(longlong *param_1)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *plVar4;
  
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  lVar2 = param_1[1];
  if (*(char *)(lVar2 + 0x29) == '\0') {
    plVar3 = *(longlong **)(lVar2 + 0x10);
    if (*(char *)((longlong)plVar3 + 0x29) != '\0') {
      lVar2 = *(longlong *)(lVar2 + 8);
      cVar1 = *(char *)(lVar2 + 0x29);
      while ((cVar1 == '\0' && (param_1[1] == *(longlong *)(lVar2 + 0x10)))) {
        param_1[1] = lVar2;
        lVar2 = *(longlong *)(lVar2 + 8);
        cVar1 = *(char *)(lVar2 + 0x29);
      }
      param_1[1] = lVar2;
      return;
    }
    cVar1 = *(char *)(*plVar3 + 0x29);
    plVar4 = (longlong *)*plVar3;
    while (cVar1 == '\0') {
      cVar1 = *(char *)(*plVar4 + 0x29);
      plVar3 = plVar4;
      plVar4 = (longlong *)*plVar4;
    }
    param_1[1] = (longlong)plVar3;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000140035444. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_1400354b0 @ 1400354b0  undefined FUN_1400354b0(undefined8 * param_1)

void FUN_1400354b0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_1400354c0 @ 1400354c0  undefined8 * FUN_1400354c0(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_1400354c0(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_140035510 @ 140035510  undefined FUN_140035510(undefined8 param_1, ulonglong param_2)

void FUN_140035510(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x30)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 0x30);
  return;
}


// ==== FUN_1400355b0 @ 1400355b0  longlong * FUN_1400355b0(longlong * param_1)

longlong * FUN_1400355b0(longlong *param_1)

{
  FUN_140035420(param_1);
  return param_1;
}


// ==== FUN_1400355d0 @ 1400355d0  undefined8 * FUN_1400355d0(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_1400355d0(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_140035610 @ 140035610  undefined FUN_140035610(undefined8 * param_1)

void FUN_140035610(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140035630 @ 140035630  undefined8 * FUN_140035630(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_140035630(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  undefined8 uVar1;
  
  uVar1 = *(undefined8 *)(param_3 + 8);
  if (param_1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_2 = *param_1;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_140035680 @ 140035680  undefined8 * FUN_140035680(undefined8 * param_1, undefined8 * param_2, longlong * param_3)

undefined8 * FUN_140035680(undefined8 *param_1,undefined8 *param_2,longlong *param_3)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong lVar5;
  longlong *plVar6;
  longlong *plVar7;
  longlong *plVar8;
  longlong *plVar9;
  undefined **local_80 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_68 [40];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_40 [40];
  
  plVar2 = (longlong *)param_3[1];
  if (*(char *)((longlong)plVar2 + 0x29) != '\0') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_40,"invalid map/set<T> iterator");
    std::exception::exception((exception *)local_80);
    local_80[0] = std::logic_error::vftable;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_68,local_40);
    local_80[0] = std::out_of_range::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_80,(ThrowInfo *)&DAT_1400feda0);
  }
  FUN_140035420(param_3);
  plVar8 = (longlong *)*plVar2;
  if (*(char *)((longlong)plVar8 + 0x29) == '\0') {
    plVar9 = plVar8;
    if (*(char *)(plVar2[2] + 0x29) == '\0') {
      plVar7 = (longlong *)param_3[1];
      plVar9 = (longlong *)plVar7[2];
      if (plVar7 != plVar2) {
        plVar8[1] = (longlong)plVar7;
        *plVar7 = *plVar2;
        plVar8 = plVar7;
        if (plVar7 != (longlong *)plVar2[2]) {
          plVar8 = (longlong *)plVar7[1];
          if (*(char *)((longlong)plVar9 + 0x29) == '\0') {
            plVar9[1] = (longlong)plVar8;
          }
          *plVar8 = (longlong)plVar9;
          plVar7[2] = plVar2[2];
          *(longlong **)(plVar2[2] + 8) = plVar7;
        }
        if (*(longlong **)(param_1[6] + 8) == plVar2) {
          *(longlong **)(param_1[6] + 8) = plVar7;
        }
        else {
          puVar4 = (undefined8 *)plVar2[1];
          if ((longlong *)*puVar4 == plVar2) {
            *puVar4 = plVar7;
          }
          else {
            puVar4[2] = plVar7;
          }
        }
        plVar7[1] = plVar2[1];
        plVar3 = plVar2 + 5;
        plVar7 = plVar7 + 5;
        if (plVar7 != plVar3) {
          lVar5 = *plVar7;
          *(char *)plVar7 = (char)*plVar3;
          *(char *)plVar3 = (char)lVar5;
        }
        goto LAB_14003586c;
      }
    }
  }
  else {
    plVar9 = (longlong *)plVar2[2];
  }
  plVar8 = (longlong *)plVar2[1];
  if (*(char *)((longlong)plVar9 + 0x29) == '\0') {
    plVar9[1] = (longlong)plVar8;
  }
  if (*(longlong **)(param_1[6] + 8) == plVar2) {
    *(longlong **)(param_1[6] + 8) = plVar9;
  }
  else if ((longlong *)*plVar8 == plVar2) {
    *plVar8 = (longlong)plVar9;
  }
  else {
    plVar8[2] = (longlong)plVar9;
  }
  if (*(longlong **)param_1[6] == plVar2) {
    plVar7 = plVar8;
    if (*(char *)((longlong)plVar9 + 0x29) == '\0') {
      cVar1 = *(char *)(*plVar9 + 0x29);
      plVar3 = (longlong *)*plVar9;
      plVar7 = plVar9;
      while (plVar6 = plVar3, cVar1 == '\0') {
        plVar3 = (longlong *)*plVar6;
        cVar1 = *(char *)((longlong)plVar3 + 0x29);
        plVar7 = plVar6;
      }
    }
    *(longlong **)param_1[6] = plVar7;
  }
  if (*(longlong **)(param_1[6] + 0x10) == plVar2) {
    plVar7 = plVar8;
    if (*(char *)((longlong)plVar9 + 0x29) == '\0') {
      cVar1 = *(char *)(plVar9[2] + 0x29);
      plVar3 = (longlong *)plVar9[2];
      plVar7 = plVar9;
      while (plVar6 = plVar3, cVar1 == '\0') {
        plVar3 = (longlong *)plVar6[2];
        cVar1 = *(char *)((longlong)plVar3 + 0x29);
        plVar7 = plVar6;
      }
    }
    *(longlong **)(param_1[6] + 0x10) = plVar7;
  }
LAB_14003586c:
  if ((char)plVar2[5] == '\x01') {
    if (plVar9 != *(longlong **)(param_1[6] + 8)) {
      do {
        plVar7 = plVar8;
        if ((char)plVar9[5] != '\x01') break;
        plVar8 = (longlong *)*plVar7;
        if (plVar9 == plVar8) {
          plVar8 = (longlong *)plVar7[2];
          if ((char)plVar8[5] == '\0') {
            *(undefined1 *)(plVar8 + 5) = 1;
            *(undefined1 *)(plVar7 + 5) = 0;
            FUN_1400351f0((longlong)param_1,(longlong)plVar7);
            plVar8 = (longlong *)plVar7[2];
          }
          if (*(char *)((longlong)plVar8 + 0x29) == '\0') {
            if ((*(char *)(*plVar8 + 0x28) != '\x01') || (*(char *)(plVar8[2] + 0x28) != '\x01')) {
              if (*(char *)(plVar8[2] + 0x28) == '\x01') {
                *(undefined1 *)(*plVar8 + 0x28) = 1;
                *(undefined1 *)(plVar8 + 5) = 0;
                FUN_140035280((longlong)param_1,plVar8);
                plVar8 = (longlong *)plVar7[2];
              }
              *(char *)(plVar8 + 5) = (char)plVar7[5];
              *(undefined1 *)(plVar7 + 5) = 1;
              *(undefined1 *)(plVar8[2] + 0x28) = 1;
              FUN_1400351f0((longlong)param_1,(longlong)plVar7);
              break;
            }
            *(undefined1 *)(plVar8 + 5) = 0;
          }
        }
        else {
          if ((char)plVar8[5] == '\0') {
            *(undefined1 *)(plVar8 + 5) = 1;
            *(undefined1 *)(plVar7 + 5) = 0;
            FUN_140035280((longlong)param_1,plVar7);
            plVar8 = (longlong *)*plVar7;
          }
          if (*(char *)((longlong)plVar8 + 0x29) == '\0') {
            if ((*(char *)(plVar8[2] + 0x28) != '\x01') || (*(char *)(*plVar8 + 0x28) != '\x01')) {
              if (*(char *)(*plVar8 + 0x28) == '\x01') {
                *(undefined1 *)(plVar8[2] + 0x28) = 1;
                *(undefined1 *)(plVar8 + 5) = 0;
                FUN_1400351f0((longlong)param_1,(longlong)plVar8);
                plVar8 = (longlong *)*plVar7;
              }
              *(char *)(plVar8 + 5) = (char)plVar7[5];
              *(undefined1 *)(plVar7 + 5) = 1;
              *(undefined1 *)(*plVar8 + 0x28) = 1;
              FUN_140035280((longlong)param_1,plVar7);
              break;
            }
            *(undefined1 *)(plVar8 + 5) = 0;
          }
        }
        plVar8 = (longlong *)plVar7[1];
        plVar9 = plVar7;
      } while (plVar7 != *(longlong **)(param_1[6] + 8));
    }
    *(undefined1 *)(plVar9 + 5) = 1;
  }
  operator_delete(plVar2);
  if (param_1[7] != 0) {
    param_1[7] = param_1[7] + -1;
  }
  lVar5 = param_3[1];
  *param_2 = *param_1;
  param_2[1] = lVar5;
  return param_2;
}


// ==== FUN_140035a40 @ 140035a40  undefined FUN_140035a40(void)

void FUN_140035a40(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x30);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = 0;
  }
  if (puVar1 + 1 != (undefined8 *)0x0) {
    puVar1[1] = 0;
  }
  if (puVar1 + 2 != (undefined8 *)0x0) {
    puVar1[2] = 0;
  }
  *(undefined1 *)(puVar1 + 5) = 1;
  *(undefined1 *)((longlong)puVar1 + 0x29) = 0;
  return;
}


// ==== FUN_140035aa0 @ 140035aa0  longlong * FUN_140035aa0(longlong * param_1, longlong * param_2)

longlong * FUN_140035aa0(longlong *param_1,longlong *param_2)

{
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  FUN_140035420(param_1);
  return param_2;
}


// ==== FUN_140035ad0 @ 140035ad0  undefined FUN_140035ad0(undefined8 param_1, longlong * param_2)

void FUN_140035ad0(undefined8 param_1,longlong *param_2)

{
  char cVar1;
  longlong *plVar2;
  
  cVar1 = *(char *)((longlong)param_2 + 0x29);
  while (cVar1 == '\0') {
    FUN_140035ad0(param_1,(longlong *)param_2[2]);
    plVar2 = (longlong *)*param_2;
    operator_delete(param_2);
    param_2 = plVar2;
    cVar1 = *(char *)((longlong)plVar2 + 0x29);
  }
  return;
}


// ==== FUN_140035b20 @ 140035b20  undefined8 * FUN_140035b20(undefined8 * param_1)

undefined8 * FUN_140035b20(undefined8 *param_1)

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


// ==== FUN_140035b70 @ 140035b70  longlong * FUN_140035b70(longlong * param_1)

longlong * FUN_140035b70(longlong *param_1)

{
  FUN_140035420(param_1);
  return param_1;
}


// ==== FUN_140035bd0 @ 140035bd0  undefined FUN_140035bd0(undefined8 * param_1)

void FUN_140035bd0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140035bf0 @ 140035bf0  undefined FUN_140035bf0(longlong param_1)

void FUN_140035bf0(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = FUN_140035a40();
  *(longlong *)(param_1 + 0x30) = lVar1;
  *(undefined1 *)(lVar1 + 0x29) = 1;
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)*(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x30);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 0x10) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = 0;
  return;
}


// ==== FUN_140035c30 @ 140035c30  undefined FUN_140035c30(longlong param_1)

void FUN_140035c30(longlong param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  
  plVar2 = *(longlong **)(*(longlong *)(param_1 + 0x30) + 8);
  cVar1 = *(char *)((longlong)plVar2 + 0x29);
  while (cVar1 == '\0') {
    FUN_140035ad0(param_1,(longlong *)plVar2[2]);
    plVar3 = (longlong *)*plVar2;
    operator_delete(plVar2);
    plVar2 = plVar3;
    cVar1 = *(char *)((longlong)plVar3 + 0x29);
  }
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)*(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x30);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 0x10) = *(longlong *)(param_1 + 0x30);
  return;
}


// ==== FUN_140035cb0 @ 140035cb0  undefined8 * FUN_140035cb0(undefined8 * param_1)

undefined8 * FUN_140035cb0(undefined8 *param_1)

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


// ==== FUN_140035d00 @ 140035d00  undefined FUN_140035d00(undefined8 * param_1)

void FUN_140035d00(undefined8 *param_1)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  undefined4 uVar4;
  int iVar5;
  longlong *plVar6;
  longlong *plVar7;
  longlong lVar8;
  longlong lVar9;
  undefined8 local_res8;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined8 uStack_50;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined1 local_38 [16];
  undefined1 local_28 [16];
  
  plVar6 = (longlong *)(**(code **)(*(longlong *)*param_1 + 0x10))((longlong *)*param_1,local_38);
  lVar2 = *plVar6;
  plVar6 = (longlong *)plVar6[1];
  uStack_50 = plVar6;
  while( true ) {
    plVar7 = (longlong *)(**(code **)(*(longlong *)*param_1 + 0x18))((longlong *)*param_1,local_28);
    if ((lVar2 == 0) || (lVar2 != *plVar7)) {
      _invalid_parameter_noinfo();
    }
    if (plVar6 == (longlong *)plVar7[1]) break;
    local_58 = (undefined4)lVar2;
    uStack_54 = (undefined4)((ulonglong)lVar2 >> 0x20);
    local_48 = local_58;
    uStack_44 = uStack_54;
    uStack_40 = (undefined4)uStack_50;
    uStack_3c = uStack_50._4_4_;
    lVar8 = (**(code **)(*(longlong *)*param_1 + 0x20))((longlong *)*param_1,&local_48);
    if (lVar8 == 0) {
      log_InlineLogERROR(&DAT_1400be0b0);
    }
    else {
      lVar9 = *(longlong *)*param_1;
      uVar4 = FUN_1400654a0(lVar8);
      lVar9 = (**(code **)(lVar9 + 0x40))(*param_1,uVar4);
      if (lVar9 != 0) {
        iVar5 = FUN_140065540(lVar8);
        FUN_140065710(lVar9,iVar5);
        FUN_140065510(lVar8,&local_res8);
        FUN_140065730(lVar9,&local_res8);
      }
    }
    if (lVar2 == 0) {
      _invalid_parameter_noinfo();
    }
    if (*(char *)((longlong)plVar6 + 0x29) == '\0') {
      plVar7 = (longlong *)plVar6[2];
      if (*(char *)((longlong)plVar7 + 0x29) == '\0') {
        cVar1 = *(char *)(*plVar7 + 0x29);
        plVar6 = plVar7;
        plVar7 = (longlong *)*plVar7;
        while (uStack_50 = plVar6, cVar1 == '\0') {
          cVar1 = *(char *)(*plVar7 + 0x29);
          plVar6 = plVar7;
          plVar7 = (longlong *)*plVar7;
        }
      }
      else {
        cVar1 = *(char *)(plVar6[1] + 0x29);
        plVar3 = (longlong *)plVar6[1];
        plVar7 = plVar6;
        while ((plVar6 = plVar3, uStack_50 = plVar6, cVar1 == '\0' &&
               (plVar7 == (longlong *)plVar6[2]))) {
          cVar1 = *(char *)(plVar6[1] + 0x29);
          plVar3 = (longlong *)plVar6[1];
          plVar7 = plVar6;
        }
      }
    }
    else {
      _invalid_parameter_noinfo();
    }
  }
  return;
}


// ==== FUN_140035f50 @ 140035f50  undefined FUN_140035f50(undefined8 * param_1)

void FUN_140035f50(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140035f70 @ 140035f70  longlong * FUN_140035f70(longlong * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_140035f70(longlong *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  char cVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong local_28;
  longlong lStack_20;
  undefined8 local_18 [2];
  
  lVar2 = *(longlong *)param_1[6];
  if ((*param_3 == 0) || (*param_3 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (param_3[1] == lVar2) {
    lVar2 = param_1[6];
    if ((*param_4 == 0) || (*param_4 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    if (param_4[1] == lVar2) {
      FUN_140035c30((longlong)param_1);
      param_2[1] = *(longlong *)param_1[6];
      *param_2 = *param_1;
      return param_2;
    }
  }
  while( true ) {
    if ((*param_3 == 0) || (*param_3 != *param_4)) {
      _invalid_parameter_noinfo();
    }
    lVar2 = *param_3;
    if (param_3[1] == param_4[1]) break;
    lVar3 = param_3[1];
    if (*param_3 == 0) {
      _invalid_parameter_noinfo();
    }
    lVar4 = param_3[1];
    if (*(char *)(lVar4 + 0x29) == '\0') {
      plVar6 = *(longlong **)(lVar4 + 0x10);
      if (*(char *)((longlong)plVar6 + 0x29) == '\0') {
        cVar1 = *(char *)(*plVar6 + 0x29);
        plVar5 = (longlong *)*plVar6;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar5 + 0x29);
          plVar6 = plVar5;
          plVar5 = (longlong *)*plVar5;
        }
      }
      else {
        plVar6 = *(longlong **)(lVar4 + 8);
        cVar1 = *(char *)((longlong)plVar6 + 0x29);
        while ((cVar1 == '\0' && (param_3[1] == plVar6[2]))) {
          param_3[1] = (longlong)plVar6;
          plVar6 = (longlong *)plVar6[1];
          cVar1 = *(char *)((longlong)plVar6 + 0x29);
        }
      }
      param_3[1] = (longlong)plVar6;
    }
    else {
      _invalid_parameter_noinfo();
    }
    local_28 = lVar2;
    lStack_20 = lVar3;
    FUN_140035680(param_1,local_18,&local_28);
  }
  lVar2 = param_3[1];
  *param_2 = *param_1;
  param_2[1] = lVar2;
  return param_2;
}


// ==== FUN_140036120 @ 140036120  undefined8 * FUN_140036120(undefined8 * param_1)

undefined8 * FUN_140036120(undefined8 *param_1)

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


// ==== FUN_140036170 @ 140036170  longlong * FUN_140036170(longlong * param_1)

longlong * FUN_140036170(longlong *param_1)

{
  int iVar1;
  ulonglong extraout_RAX;
  undefined8 uVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  int iVar5;
  
  if (*param_1 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    plVar3 = (longlong *)(extraout_RAX & 0xffffffffffffff00);
  }
  else {
    uVar2 = FUN_14001c200();
    plVar3 = (longlong *)InstanceGet(uVar2);
    plVar3 = (longlong *)(**(code **)(*plVar3 + 0x10))(plVar3,"SELECT * FROM cq_protect_path",2);
    if (plVar3 != (longlong *)0x0) {
      iVar5 = 0;
      iVar1 = (**(code **)(*plVar3 + 0x40))(plVar3);
      if (0 < iVar1) {
        do {
          (**(code **)(*plVar3 + 0x30))(plVar3,(longlong)iVar5);
          puVar4 = (undefined8 *)operator_new(0x78);
          if (puVar4 == (undefined8 *)0x0) {
            puVar4 = (undefined8 *)0x0;
          }
          else {
            puVar4 = FUN_140065d30(puVar4);
          }
          uVar2 = FUN_140065570((longlong)puVar4,plVar3);
          if ((char)uVar2 == '\0') {
            FUN_140065550(puVar4);
          }
          else {
            (**(code **)(*(longlong *)*param_1 + 0x28))((longlong *)*param_1,puVar4);
          }
          iVar5 = iVar5 + 1;
          iVar1 = (**(code **)(*plVar3 + 0x40))(plVar3);
        } while (iVar5 < iVar1);
      }
      (**(code **)*plVar3)(plVar3);
      uVar2 = FUN_140035d00(param_1);
      plVar3 = (longlong *)CONCAT71((int7)((ulonglong)uVar2 >> 8),1);
    }
  }
  return plVar3;
}


// ==== FUN_1400362a0 @ 1400362a0  undefined FUN_1400362a0(undefined8 * param_1)

void FUN_1400362a0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_1400362c0 @ 1400362c0  undefined FUN_1400362c0(longlong * param_1)

void FUN_1400362c0(longlong *param_1)

{
  longlong local_38;
  undefined8 *puStack_30;
  longlong local_28;
  undefined8 uStack_20;
  longlong local_18 [2];
  
  local_38 = *param_1;
  puStack_30 = (undefined8 *)param_1[6];
  uStack_20 = *puStack_30;
  local_28 = local_38;
  FUN_140035f70(param_1,local_18,&local_28,&local_38);
  operator_delete((void *)param_1[6]);
  param_1[6] = 0;
  param_1[7] = 0;
  return;
}


// ==== FUN_140036330 @ 140036330  undefined8 * FUN_140036330(undefined8 * param_1)

undefined8 * FUN_140036330(undefined8 *param_1)

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


// ==== FUN_140036380 @ 140036380  undefined FUN_140036380(longlong * param_1)

void FUN_140036380(longlong *param_1)

{
  FUN_1400362c0(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_1400363b0 @ 1400363b0  undefined8 * FUN_1400363b0(undefined8 * param_1)

undefined8 * FUN_1400363b0(undefined8 *param_1)

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


// ==== FUN_140036400 @ 140036400  undefined FUN_140036400(longlong * param_1)

void FUN_140036400(longlong *param_1)

{
  FUN_1400362c0(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140036430 @ 140036430  undefined8 * FUN_140036430(undefined8 * param_1)

undefined8 * FUN_140036430(undefined8 *param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  lVar2 = FUN_140035a40();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x29) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_1400364b0 @ 1400364b0  undefined8 * FUN_1400364b0(undefined8 * param_1)

undefined8 * FUN_1400364b0(undefined8 *param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  lVar2 = FUN_140035a40();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x29) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_140036530 @ 140036530  undefined8 * FUN_140036530(undefined8 * param_1, undefined1 param_2)

undefined8 * FUN_140036530(undefined8 *param_1,undefined1 param_2)

{
  *param_1 = ISingleMap<class_CNpcPath>::vftable;
  *param_1 = CSingleMap<class_CNpcPath>::vftable;
  FUN_1400364b0(param_1 + 2);
  *(undefined1 *)(param_1 + 1) = param_2;
  return param_1;
}


// ==== FUN_1400365e0 @ 1400365e0  undefined FUN_1400365e0(longlong * param_1)

void FUN_1400365e0(longlong *param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)param_1[1];
  if (*(char *)((longlong)plVar2 + 0x29) == '\0') {
    lVar3 = *plVar2;
    if (*(char *)(lVar3 + 0x29) == '\0') {
      cVar1 = *(char *)(*(longlong *)(lVar3 + 0x10) + 0x29);
      lVar4 = *(longlong *)(lVar3 + 0x10);
      while (lVar5 = lVar4, cVar1 == '\0') {
        lVar4 = *(longlong *)(lVar5 + 0x10);
        cVar1 = *(char *)(lVar4 + 0x29);
        lVar3 = lVar5;
      }
      param_1[1] = lVar3;
      return;
    }
    plVar2 = (longlong *)plVar2[1];
    cVar1 = *(char *)((longlong)plVar2 + 0x29);
    while ((cVar1 == '\0' && (param_1[1] == *plVar2))) {
      param_1[1] = (longlong)plVar2;
      plVar2 = (longlong *)plVar2[1];
      cVar1 = *(char *)((longlong)plVar2 + 0x29);
    }
    if (*(char *)(param_1[1] + 0x29) == '\0') {
      param_1[1] = (longlong)plVar2;
      return;
    }
  }
  else {
    lVar3 = plVar2[2];
    param_1[1] = lVar3;
    if (*(char *)(lVar3 + 0x29) == '\0') {
      return;
    }
  }
                    /* WARNING: Could not recover jumptable at 0x000140036612. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_140036730 @ 140036730  longlong FUN_140036730(longlong * param_1)

longlong FUN_140036730(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140036752;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140036752:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_1400367b0 @ 1400367b0  longlong * FUN_1400367b0(longlong * param_1)

longlong * FUN_1400367b0(longlong *param_1)

{
  FUN_1400365e0(param_1);
  return param_1;
}


// ==== FUN_1400367e0 @ 1400367e0  undefined8 * FUN_1400367e0(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, undefined8 * param_5, undefined1 param_6)

undefined8 *
FUN_1400367e0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             undefined8 *param_5,undefined1 param_6)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x30);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_2;
    puVar1[1] = param_3;
    puVar1[2] = param_4;
    puVar1[3] = *param_5;
    puVar1[4] = param_5[1];
    *(undefined1 *)(puVar1 + 5) = param_6;
    *(undefined1 *)((longlong)puVar1 + 0x29) = 0;
  }
  return puVar1;
}


// ==== FUN_140036860 @ 140036860  longlong * FUN_140036860(longlong * param_1)

longlong * FUN_140036860(longlong *param_1)

{
  FUN_1400365e0(param_1);
  return param_1;
}


// ==== FUN_140036880 @ 140036880  longlong FUN_140036880(longlong * param_1)

longlong FUN_140036880(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_1400368a2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_1400368a2:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_140036900 @ 140036900  undefined8 * FUN_140036900(undefined8 * param_1, undefined8 * param_2, uint * param_3)

undefined8 * FUN_140036900(undefined8 *param_1,undefined8 *param_2,uint *param_3)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  
  puVar4 = (undefined8 *)param_1[6];
  puVar5 = puVar4;
  if (*(char *)((longlong)puVar4[1] + 0x29) == '\0') {
    puVar2 = (undefined8 *)puVar4[1];
    do {
      if (*(uint *)(puVar2 + 3) < *param_3) {
        puVar3 = (undefined8 *)puVar2[2];
      }
      else {
        if ((*(char *)((longlong)puVar4 + 0x29) != '\0') && (*param_3 < *(uint *)(puVar2 + 3))) {
          puVar4 = puVar2;
        }
        puVar3 = (undefined8 *)*puVar2;
        puVar5 = puVar2;
      }
      puVar2 = puVar3;
    } while (*(char *)((longlong)puVar3 + 0x29) == '\0');
  }
  if (*(char *)((longlong)puVar4 + 0x29) == '\0') {
    puVar2 = (undefined8 *)*puVar4;
  }
  else {
    puVar2 = *(undefined8 **)(param_1[6] + 8);
  }
  if (*(char *)((longlong)puVar2 + 0x29) == '\0') {
    do {
      if (*param_3 < *(uint *)(puVar2 + 3)) {
        puVar3 = (undefined8 *)*puVar2;
        puVar4 = puVar2;
      }
      else {
        puVar3 = (undefined8 *)puVar2[2];
      }
      puVar2 = puVar3;
    } while (*(char *)((longlong)puVar3 + 0x29) == '\0');
  }
  uVar1 = *param_1;
  *param_2 = uVar1;
  param_2[1] = puVar5;
  param_2[2] = uVar1;
  param_2[3] = puVar4;
  return param_2;
}


// ==== FUN_1400369e0 @ 1400369e0  undefined8 * FUN_1400369e0(undefined8 * param_1, undefined8 * param_2, char param_3, undefined8 * param_4, undefined8 * param_5)

undefined8 *
FUN_1400369e0(undefined8 *param_1,undefined8 *param_2,char param_3,undefined8 *param_4,
             undefined8 *param_5)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [40];
  
  if (0xffffffffffffffd < (ulonglong)param_1[7]) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_70,"map/set<T> too long");
    std::exception::exception((exception *)local_48);
    local_48[0] = std::logic_error::vftable;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
    local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
  }
  plVar5 = FUN_1400367e0(param_1,param_1[6],param_4,param_1[6],param_5,0);
  param_1[7] = param_1[7] + 1;
  if (param_4 == (undefined8 *)param_1[6]) {
    ((undefined8 *)param_1[6])[1] = plVar5;
    *(longlong **)param_1[6] = plVar5;
    *(longlong **)(param_1[6] + 0x10) = plVar5;
  }
  else if (param_3 == '\0') {
    param_4[2] = plVar5;
    if (param_4 == *(undefined8 **)(param_1[6] + 0x10)) {
      *(longlong **)(param_1[6] + 0x10) = plVar5;
    }
  }
  else {
    *param_4 = plVar5;
    if (param_4 == *(undefined8 **)param_1[6]) {
      *(longlong **)param_1[6] = plVar5;
    }
  }
  plVar7 = plVar5 + 1;
  cVar1 = *(char *)(*plVar7 + 0x28);
  plVar6 = plVar5;
  while (cVar1 == '\0') {
    plVar2 = (longlong *)*plVar7;
    plVar3 = (longlong *)plVar2[1];
    if (plVar2 == (longlong *)*plVar3) {
      lVar4 = plVar3[2];
      if (*(char *)(lVar4 + 0x28) == '\0') {
        *(undefined1 *)(plVar2 + 5) = 1;
        *(undefined1 *)(lVar4 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        plVar6 = *(longlong **)(*plVar7 + 8);
      }
      else {
        if (plVar6 == (longlong *)plVar2[2]) {
          plVar6 = (longlong *)plVar2[2];
          plVar2[2] = *plVar6;
          if (*(char *)(*plVar6 + 0x29) == '\0') {
            *(longlong **)(*plVar6 + 8) = plVar2;
          }
          plVar7 = plVar2 + 1;
          plVar6[1] = *plVar7;
          if (plVar2 == *(longlong **)(param_1[6] + 8)) {
            *(longlong **)(param_1[6] + 8) = plVar6;
          }
          else {
            plVar3 = (longlong *)*plVar7;
            if (plVar2 == (longlong *)*plVar3) {
              *plVar3 = (longlong)plVar6;
            }
            else {
              plVar3[2] = (longlong)plVar6;
            }
          }
          *plVar6 = (longlong)plVar2;
          *plVar7 = (longlong)plVar6;
          plVar6 = plVar2;
        }
        *(undefined1 *)(*plVar7 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        plVar7 = *(longlong **)(*plVar7 + 8);
        lVar4 = *plVar7;
        *plVar7 = *(longlong *)(lVar4 + 0x10);
        if (*(char *)(*(longlong *)(lVar4 + 0x10) + 0x29) == '\0') {
          *(longlong **)(*(longlong *)(lVar4 + 0x10) + 8) = plVar7;
        }
        *(longlong *)(lVar4 + 8) = plVar7[1];
        if (plVar7 == *(longlong **)(param_1[6] + 8)) {
          *(longlong *)(param_1[6] + 8) = lVar4;
        }
        else {
          plVar2 = (longlong *)plVar7[1];
          if (plVar7 == (longlong *)plVar2[2]) {
            plVar2[2] = lVar4;
          }
          else {
            *plVar2 = lVar4;
          }
        }
        *(longlong **)(lVar4 + 0x10) = plVar7;
        plVar7[1] = lVar4;
      }
    }
    else {
      lVar4 = *plVar3;
      if (*(char *)(lVar4 + 0x28) == '\0') {
        *(undefined1 *)(plVar2 + 5) = 1;
        *(undefined1 *)(lVar4 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        plVar6 = *(longlong **)(*plVar7 + 8);
      }
      else {
        if (plVar6 == (longlong *)*plVar2) {
          lVar4 = *plVar2;
          *plVar2 = *(longlong *)(lVar4 + 0x10);
          if (*(char *)(*(longlong *)(lVar4 + 0x10) + 0x29) == '\0') {
            *(longlong **)(*(longlong *)(lVar4 + 0x10) + 8) = plVar2;
          }
          plVar7 = plVar2 + 1;
          *(longlong *)(lVar4 + 8) = *plVar7;
          if (plVar2 == *(longlong **)(param_1[6] + 8)) {
            *(longlong *)(param_1[6] + 8) = lVar4;
          }
          else {
            plVar6 = (longlong *)*plVar7;
            if (plVar2 == (longlong *)plVar6[2]) {
              plVar6[2] = lVar4;
            }
            else {
              *plVar6 = lVar4;
            }
          }
          *(longlong **)(lVar4 + 0x10) = plVar2;
          *plVar7 = lVar4;
          plVar6 = plVar2;
        }
        *(undefined1 *)(*plVar7 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        lVar4 = *(longlong *)(*plVar7 + 8);
        plVar7 = *(longlong **)(lVar4 + 0x10);
        *(longlong *)(lVar4 + 0x10) = *plVar7;
        if (*(char *)(*plVar7 + 0x29) == '\0') {
          *(longlong *)(*plVar7 + 8) = lVar4;
        }
        plVar7[1] = *(longlong *)(lVar4 + 8);
        if (lVar4 == *(longlong *)(param_1[6] + 8)) {
          *(longlong **)(param_1[6] + 8) = plVar7;
        }
        else {
          plVar2 = *(longlong **)(lVar4 + 8);
          if (lVar4 == *plVar2) {
            *plVar2 = (longlong)plVar7;
          }
          else {
            plVar2[2] = (longlong)plVar7;
          }
        }
        *plVar7 = lVar4;
        *(longlong **)(lVar4 + 8) = plVar7;
      }
    }
    plVar7 = plVar6 + 1;
    cVar1 = *(char *)(*plVar7 + 0x28);
  }
  *(undefined1 *)(*(longlong *)(param_1[6] + 8) + 0x28) = 1;
  param_2[1] = plVar5;
  *param_2 = *param_1;
  return param_2;
}


// ==== FUN_140036d20 @ 140036d20  longlong FUN_140036d20(longlong * param_1)

longlong FUN_140036d20(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140036d42;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140036d42:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_140036d60 @ 140036d60  longlong * FUN_140036d60(longlong * param_1, longlong * param_2, uint * param_3)

longlong * FUN_140036d60(longlong *param_1,longlong *param_2,uint *param_3)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong local_28;
  undefined8 *local_20;
  longlong local_18;
  longlong local_10;
  
  puVar4 = (undefined8 *)param_1[6];
  if (*(char *)((longlong)puVar4[1] + 0x29) == '\0') {
    puVar1 = (undefined8 *)puVar4[1];
    do {
      if (*(uint *)(puVar1 + 3) < *param_3) {
        puVar2 = (undefined8 *)puVar1[2];
      }
      else {
        puVar2 = (undefined8 *)*puVar1;
        puVar4 = puVar1;
      }
      puVar1 = puVar2;
    } while (*(char *)((longlong)puVar2 + 0x29) == '\0');
  }
  puVar1 = (undefined8 *)param_1[6];
  local_20 = puVar4;
  local_28 = *param_1;
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  if ((puVar4 == puVar1) || (*param_3 < *(uint *)(puVar4 + 3))) {
    plVar3 = &local_18;
    local_10 = param_1[6];
    local_18 = *param_1;
  }
  else {
    plVar3 = &local_28;
  }
  *param_2 = *plVar3;
  param_2[1] = plVar3[1];
  return param_2;
}


// ==== FUN_140036e30 @ 140036e30  undefined8 * FUN_140036e30(undefined8 * param_1, undefined8 * param_2, uint * param_3)

undefined8 * FUN_140036e30(undefined8 *param_1,undefined8 *param_2,uint *param_3)

{
  FUN_140036900(param_1,param_2,param_3);
  return param_2;
}


// ==== FUN_140036e50 @ 140036e50  longlong * FUN_140036e50(longlong * param_1, longlong * param_2, uint * param_3)

longlong * FUN_140036e50(longlong *param_1,longlong *param_2,uint *param_3)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *plVar4;
  longlong *plVar5;
  longlong *plVar6;
  bool bVar7;
  longlong local_38;
  longlong *local_30;
  
  plVar6 = (longlong *)param_1[6];
  bVar7 = true;
  if (*(char *)(plVar6[1] + 0x29) == '\0') {
    plVar5 = (longlong *)plVar6[1];
    do {
      plVar6 = plVar5;
      bVar7 = *param_3 < *(uint *)(plVar6 + 3);
      if (bVar7) {
        plVar5 = (longlong *)*plVar6;
      }
      else {
        plVar5 = (longlong *)plVar6[2];
      }
    } while (*(char *)((longlong)plVar5 + 0x29) == '\0');
  }
  lVar2 = *param_1;
  plVar5 = plVar6;
  local_38 = lVar2;
  plVar4 = plVar6;
  if (bVar7 == false) {
LAB_140036fad:
    local_30 = plVar4;
    if (*param_3 <= *(uint *)(plVar5 + 3)) {
      *(undefined1 *)(param_2 + 2) = 0;
      *param_2 = local_38;
      goto LAB_140036fdc;
    }
  }
  else {
    plVar5 = *(longlong **)param_1[6];
    local_30 = plVar6;
    if (lVar2 == 0) {
      _invalid_parameter_noinfo();
    }
    if (plVar6 != plVar5) {
      if (lVar2 == 0) {
        _invalid_parameter_noinfo();
      }
      if (*(char *)((longlong)plVar6 + 0x29) == '\0') {
        plVar5 = (longlong *)*plVar6;
        if (*(char *)((longlong)plVar5 + 0x29) == '\0') {
          cVar1 = *(char *)(plVar5[2] + 0x29);
          plVar3 = (longlong *)plVar5[2];
          while (plVar4 = plVar5, cVar1 == '\0') {
            cVar1 = *(char *)(plVar3[2] + 0x29);
            plVar5 = plVar3;
            plVar3 = (longlong *)plVar3[2];
          }
        }
        else {
          cVar1 = *(char *)(plVar6[1] + 0x29);
          plVar4 = (longlong *)plVar6[1];
          plVar3 = plVar6;
          while ((plVar5 = plVar4, cVar1 == '\0' && (plVar3 == (longlong *)*plVar5))) {
            cVar1 = *(char *)(plVar5[1] + 0x29);
            plVar4 = (longlong *)plVar5[1];
            plVar3 = plVar5;
            local_30 = plVar5;
          }
          plVar4 = plVar5;
          if (*(char *)((longlong)plVar3 + 0x29) != '\0') {
            _invalid_parameter_noinfo();
            plVar5 = plVar3;
            plVar4 = local_30;
          }
        }
      }
      else {
        plVar5 = (longlong *)plVar6[2];
        plVar4 = plVar5;
        if (*(char *)((longlong)plVar5 + 0x29) != '\0') {
          local_30 = plVar5;
          _invalid_parameter_noinfo();
          plVar4 = local_30;
        }
      }
      goto LAB_140036fad;
    }
    bVar7 = true;
  }
  plVar6 = FUN_1400369e0(param_1,&local_38,bVar7,plVar6,(undefined8 *)param_3);
  *(undefined1 *)(param_2 + 2) = 1;
  local_30 = (longlong *)plVar6[1];
  *param_2 = *plVar6;
LAB_140036fdc:
  param_2[1] = (longlong)local_30;
  return param_2;
}


// ==== FUN_140037000 @ 140037000  longlong * FUN_140037000(longlong * param_1, longlong * param_2)

longlong * FUN_140037000(longlong *param_1,longlong *param_2)

{
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  FUN_140035420(param_1);
  return param_2;
}


// ==== FUN_140037030 @ 140037030  undefined FUN_140037030(longlong * param_1, longlong * param_2, longlong * param_3)

void FUN_140037030(longlong *param_1,longlong *param_2,longlong *param_3)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *plVar4;
  
  while( true ) {
    if ((*param_1 == 0) || (*param_1 != *param_2)) {
      _invalid_parameter_noinfo();
    }
    if (param_1[1] == param_2[1]) break;
    *param_3 = *param_3 + 1;
    if (*param_1 == 0) {
      _invalid_parameter_noinfo();
    }
    lVar2 = param_1[1];
    if (*(char *)(lVar2 + 0x29) == '\0') {
      plVar3 = *(longlong **)(lVar2 + 0x10);
      if (*(char *)((longlong)plVar3 + 0x29) == '\0') {
        cVar1 = *(char *)(*plVar3 + 0x29);
        plVar4 = (longlong *)*plVar3;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar4 + 0x29);
          plVar3 = plVar4;
          plVar4 = (longlong *)*plVar4;
        }
        param_1[1] = (longlong)plVar3;
      }
      else {
        lVar2 = *(longlong *)(lVar2 + 8);
        cVar1 = *(char *)(lVar2 + 0x29);
        while ((cVar1 == '\0' && (param_1[1] == *(longlong *)(lVar2 + 0x10)))) {
          param_1[1] = lVar2;
          lVar2 = *(longlong *)(lVar2 + 8);
          cVar1 = *(char *)(lVar2 + 0x29);
        }
        param_1[1] = lVar2;
      }
    }
    else {
      _invalid_parameter_noinfo();
    }
  }
  return;
}


// ==== FUN_140037280 @ 140037280  longlong * FUN_140037280(longlong * param_1, longlong * param_2, longlong * param_3, uint * param_4)

longlong * FUN_140037280(longlong *param_1,longlong *param_2,longlong *param_3,uint *param_4)

{
  char cVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  uint uVar8;
  longlong *plVar9;
  longlong local_38;
  longlong *local_30;
  
  if (param_1[7] == 0) {
    FUN_1400369e0(param_1,param_2,'\x01',(undefined8 *)param_1[6],(undefined8 *)param_4);
  }
  else {
    puVar2 = *(undefined8 **)param_1[6];
    if ((*param_3 == 0) || (*param_3 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    puVar3 = (undefined8 *)param_3[1];
    if (puVar3 == puVar2) {
      if (*param_4 < *(uint *)(puVar3 + 3)) {
        FUN_1400369e0(param_1,param_2,'\x01',puVar3,(undefined8 *)param_4);
        return param_2;
      }
    }
    else {
      lVar4 = param_1[6];
      if ((*param_3 == 0) || (*param_3 != *param_1)) {
        _invalid_parameter_noinfo();
      }
      if (param_3[1] == lVar4) {
        if (*(uint *)(*(undefined8 **)(param_1[6] + 0x10) + 3) < *param_4) {
          FUN_1400369e0(param_1,param_2,'\0',*(undefined8 **)(param_1[6] + 0x10),
                        (undefined8 *)param_4);
          return param_2;
        }
      }
      else {
        uVar8 = *param_4;
        if (uVar8 < *(uint *)(param_3[1] + 0x18)) {
          local_38 = *param_3;
          local_30 = (longlong *)param_3[1];
          if (local_38 == 0) {
            _invalid_parameter_noinfo();
          }
          if (*(char *)((longlong)local_30 + 0x29) == '\0') {
            plVar7 = (longlong *)*local_30;
            if (*(char *)((longlong)plVar7 + 0x29) == '\0') {
              cVar1 = *(char *)(plVar7[2] + 0x29);
              plVar9 = (longlong *)plVar7[2];
              while (local_30 = plVar7, cVar1 == '\0') {
                cVar1 = *(char *)(plVar9[2] + 0x29);
                plVar7 = plVar9;
                plVar9 = (longlong *)plVar9[2];
              }
            }
            else {
              cVar1 = *(char *)(local_30[1] + 0x29);
              plVar5 = (longlong *)local_30[1];
              plVar9 = local_30;
              while ((plVar7 = plVar5, cVar1 == '\0' && (plVar9 == (longlong *)*plVar7))) {
                cVar1 = *(char *)(plVar7[1] + 0x29);
                plVar5 = (longlong *)plVar7[1];
                plVar9 = plVar7;
              }
              local_30 = plVar7;
              if (*(char *)((longlong)plVar9 + 0x29) != '\0') {
                local_30 = plVar9;
                _invalid_parameter_noinfo();
                plVar7 = plVar9;
              }
            }
          }
          else {
            plVar7 = (longlong *)local_30[2];
            local_30 = plVar7;
            if (*(char *)((longlong)plVar7 + 0x29) != '\0') {
              _invalid_parameter_noinfo();
            }
          }
          uVar8 = *param_4;
          if (*(uint *)(plVar7 + 3) < uVar8) {
            if (*(char *)(plVar7[2] + 0x29) != '\0') {
              FUN_1400369e0(param_1,param_2,'\0',plVar7,(undefined8 *)param_4);
              return param_2;
            }
            FUN_1400369e0(param_1,param_2,'\x01',(undefined8 *)param_3[1],(undefined8 *)param_4);
            return param_2;
          }
        }
        if (*(uint *)(param_3[1] + 0x18) < uVar8) {
          local_38 = *param_3;
          plVar7 = (longlong *)param_1[6];
          local_30 = (longlong *)param_3[1];
          lVar4 = *param_1;
          if (local_38 == 0) {
            _invalid_parameter_noinfo();
          }
          plVar9 = local_30;
          if (*(char *)((longlong)local_30 + 0x29) == '\0') {
            plVar9 = (longlong *)local_30[2];
            if (*(char *)((longlong)plVar9 + 0x29) == '\0') {
              cVar1 = *(char *)(*plVar9 + 0x29);
              plVar5 = (longlong *)*plVar9;
              while (cVar1 == '\0') {
                cVar1 = *(char *)(*plVar5 + 0x29);
                plVar9 = plVar5;
                plVar5 = (longlong *)*plVar5;
              }
            }
            else {
              cVar1 = *(char *)(local_30[1] + 0x29);
              plVar6 = (longlong *)local_30[1];
              plVar5 = local_30;
              while ((plVar9 = plVar6, cVar1 == '\0' && (plVar5 == (longlong *)plVar9[2]))) {
                cVar1 = *(char *)(plVar9[1] + 0x29);
                plVar6 = (longlong *)plVar9[1];
                plVar5 = plVar9;
              }
            }
          }
          else {
            _invalid_parameter_noinfo();
          }
          if ((local_38 == 0) || (local_38 != lVar4)) {
            _invalid_parameter_noinfo();
          }
          if ((plVar9 == plVar7) || (*param_4 < *(uint *)(plVar9 + 3))) {
            if (*(char *)(((undefined8 *)param_3[1])[2] + 0x29) != '\0') {
              FUN_1400369e0(param_1,param_2,'\0',(undefined8 *)param_3[1],(undefined8 *)param_4);
              return param_2;
            }
            FUN_1400369e0(param_1,param_2,'\x01',plVar9,(undefined8 *)param_4);
            return param_2;
          }
        }
      }
    }
    plVar7 = FUN_140036e50(param_1,&local_38,param_4);
    *param_2 = *plVar7;
    param_2[1] = plVar7[1];
  }
  return param_2;
}


// ==== FUN_1400375a0 @ 1400375a0  undefined FUN_1400375a0(longlong * param_1)

void FUN_1400375a0(longlong *param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined8 uStack_30;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined1 local_18 [16];
  
  if (((char)param_1[1] != '\0') && (param_1[9] != 0)) {
    (**(code **)(*param_1 + 0x10))(param_1,&local_38);
    while( true ) {
      plVar3 = (longlong *)(**(code **)(*param_1 + 0x18))(param_1,local_18);
      if ((CONCAT44(uStack_34,local_38) == 0) || (CONCAT44(uStack_34,local_38) != *plVar3)) {
        _invalid_parameter_noinfo();
      }
      if (uStack_30 == (longlong *)plVar3[1]) break;
      local_28 = local_38;
      uStack_24 = uStack_34;
      uStack_20 = (undefined4)uStack_30;
      uStack_1c = uStack_30._4_4_;
      puVar4 = (undefined8 *)(**(code **)(*param_1 + 0x20))(param_1,&local_28);
      FUN_140065550(puVar4);
      if (CONCAT44(uStack_34,local_38) == 0) {
        _invalid_parameter_noinfo();
      }
      if (*(char *)((longlong)uStack_30 + 0x29) == '\0') {
        plVar3 = (longlong *)uStack_30[2];
        if (*(char *)((longlong)plVar3 + 0x29) == '\0') {
          cVar1 = *(char *)(*plVar3 + 0x29);
          uStack_30 = plVar3;
          plVar3 = (longlong *)*plVar3;
          while (cVar1 == '\0') {
            cVar1 = *(char *)(*plVar3 + 0x29);
            uStack_30 = plVar3;
            plVar3 = (longlong *)*plVar3;
          }
        }
        else {
          cVar1 = *(char *)(uStack_30[1] + 0x29);
          plVar2 = (longlong *)uStack_30[1];
          plVar3 = uStack_30;
          while ((uStack_30 = plVar2, cVar1 == '\0' && (plVar3 == (longlong *)uStack_30[2]))) {
            cVar1 = *(char *)(uStack_30[1] + 0x29);
            plVar2 = (longlong *)uStack_30[1];
            plVar3 = uStack_30;
          }
        }
      }
      else {
        _invalid_parameter_noinfo();
      }
    }
  }
  cVar1 = *(char *)((longlong)*(longlong **)(param_1[8] + 8) + 0x29);
  plVar3 = *(longlong **)(param_1[8] + 8);
  while (cVar1 == '\0') {
    FUN_140035ad0(param_1 + 2,(longlong *)plVar3[2]);
    plVar2 = (longlong *)*plVar3;
    operator_delete(plVar3);
    plVar3 = plVar2;
    cVar1 = *(char *)((longlong)plVar2 + 0x29);
  }
  *(longlong *)(param_1[8] + 8) = param_1[8];
  param_1[9] = 0;
  *(longlong *)param_1[8] = param_1[8];
  *(longlong *)(param_1[8] + 0x10) = param_1[8];
  return;
}


// ==== FUN_140037710 @ 140037710  undefined FUN_140037710(longlong * param_1, longlong * param_2, longlong * param_3)

void FUN_140037710(longlong *param_1,longlong *param_2,longlong *param_3)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  
  lVar2 = *param_2;
  plVar3 = (longlong *)param_2[1];
  lVar4 = *param_1;
  plVar7 = (longlong *)param_1[1];
  while( true ) {
    if ((lVar4 == 0) || (lVar4 != lVar2)) {
      _invalid_parameter_noinfo();
    }
    if (plVar7 == plVar3) break;
    *param_3 = *param_3 + 1;
    if (lVar4 == 0) {
      _invalid_parameter_noinfo();
    }
    if (*(char *)((longlong)plVar7 + 0x29) == '\0') {
      plVar5 = (longlong *)plVar7[2];
      if (*(char *)((longlong)plVar5 + 0x29) == '\0') {
        cVar1 = *(char *)(*plVar5 + 0x29);
        plVar7 = plVar5;
        plVar5 = (longlong *)*plVar5;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar5 + 0x29);
          plVar7 = plVar5;
          plVar5 = (longlong *)*plVar5;
        }
      }
      else {
        cVar1 = *(char *)(plVar7[1] + 0x29);
        plVar6 = (longlong *)plVar7[1];
        plVar5 = plVar7;
        while ((plVar7 = plVar6, cVar1 == '\0' && (plVar5 == (longlong *)plVar7[2]))) {
          cVar1 = *(char *)(plVar7[1] + 0x29);
          plVar6 = (longlong *)plVar7[1];
          plVar5 = plVar7;
        }
      }
    }
    else {
      _invalid_parameter_noinfo();
    }
  }
  return;
}


// ==== FUN_140037800 @ 140037800  undefined8 * FUN_140037800(longlong * param_1, uint * param_2)

undefined8 * FUN_140037800(longlong *param_1,uint *param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong lVar5;
  longlong *plVar6;
  uint local_48 [2];
  undefined8 local_40;
  longlong *local_38;
  undefined8 *puStack_30;
  longlong local_28 [2];
  
  puVar4 = (undefined8 *)param_1[6];
  if (*(char *)((longlong)puVar4[1] + 0x29) == '\0') {
    puVar1 = (undefined8 *)puVar4[1];
    do {
      if (*(uint *)(puVar1 + 3) < *param_2) {
        puVar2 = (undefined8 *)puVar1[2];
      }
      else {
        puVar2 = (undefined8 *)*puVar1;
        puVar4 = puVar1;
      }
      puVar1 = puVar2;
    } while (*(char *)((longlong)puVar2 + 0x29) == '\0');
  }
  plVar6 = (longlong *)*param_1;
  puVar1 = (undefined8 *)param_1[6];
  if (plVar6 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  lVar5 = 0;
  if ((puVar4 == puVar1) || (*param_2 < *(uint *)(puVar4 + 3))) {
    local_48[0] = *param_2;
    local_40 = 0;
    local_38 = plVar6;
    puStack_30 = puVar4;
    plVar3 = FUN_140037280(param_1,local_28,(longlong *)&local_38,local_48);
    plVar6 = (longlong *)*plVar3;
    puVar4 = (undefined8 *)plVar3[1];
  }
  if (plVar6 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  else {
    lVar5 = *plVar6;
  }
  if (puVar4 == *(undefined8 **)(lVar5 + 0x30)) {
    _invalid_parameter_noinfo();
  }
  return puVar4 + 4;
}


// ==== FUN_140037900 @ 140037900  longlong FUN_140037900(longlong * param_1, uint * param_2)

longlong FUN_140037900(longlong *param_1,uint *param_2)

{
  char cVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  longlong lVar8;
  longlong local_58;
  longlong *local_50;
  longlong local_48;
  longlong *local_40;
  longlong local_38;
  longlong *local_30;
  longlong local_28;
  longlong *local_20;
  
  FUN_140036900(param_1,&local_38,param_2);
  plVar5 = local_20;
  lVar4 = local_28;
  lVar3 = local_38;
  lVar8 = 0;
  local_58 = local_38;
  local_50 = local_30;
  plVar7 = local_30;
  while( true ) {
    if ((lVar3 == 0) || (lVar3 != lVar4)) {
      _invalid_parameter_noinfo();
    }
    if (plVar7 == plVar5) break;
    lVar8 = lVar8 + 1;
    if (lVar3 == 0) {
      _invalid_parameter_noinfo();
    }
    if (*(char *)((longlong)plVar7 + 0x29) == '\0') {
      plVar2 = (longlong *)plVar7[2];
      if (*(char *)((longlong)plVar2 + 0x29) == '\0') {
        cVar1 = *(char *)(*plVar2 + 0x29);
        plVar7 = plVar2;
        plVar2 = (longlong *)*plVar2;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar2 + 0x29);
          plVar7 = plVar2;
          plVar2 = (longlong *)*plVar2;
        }
      }
      else {
        cVar1 = *(char *)(plVar7[1] + 0x29);
        plVar6 = (longlong *)plVar7[1];
        plVar2 = plVar7;
        while ((plVar7 = plVar6, cVar1 == '\0' && (plVar2 == (longlong *)plVar7[2]))) {
          cVar1 = *(char *)(plVar7[1] + 0x29);
          plVar6 = (longlong *)plVar7[1];
          plVar2 = plVar7;
        }
      }
    }
    else {
      _invalid_parameter_noinfo();
    }
  }
  local_58 = local_28;
  local_50 = local_20;
  local_48 = local_38;
  local_40 = local_30;
  FUN_140035f70(param_1,&local_38,&local_48,&local_58);
  return lVar8;
}


// ==== FUN_140037c30 @ 140037c30  undefined FUN_140037c30(longlong * param_1)

void FUN_140037c30(longlong *param_1)

{
  *param_1 = (longlong)CSingleMap<class_CNpcPath>::vftable;
  FUN_1400375a0(param_1);
  FUN_1400362c0(param_1 + 2);
  operator_delete((void *)param_1[2]);
  *param_1 = (longlong)ISingleMap<class_CNpcPath>::vftable;
  return;
}


// ==== FUN_140037d10 @ 140037d10  undefined8 * FUN_140037d10(undefined1 param_1)

undefined8 * FUN_140037d10(undefined1 param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x50);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = ISingleMap<class_CNpcPath>::vftable;
    *puVar1 = CSingleMap<class_CNpcPath>::vftable;
    FUN_1400364b0(puVar1 + 2);
    *(undefined1 *)(puVar1 + 1) = param_1;
  }
  return puVar1;
}


// ==== FUN_140037d80 @ 140037d80  undefined8 * FUN_140037d80(undefined8 * param_1)

undefined8 * FUN_140037d80(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  *param_1 = 0;
  puVar1 = (undefined8 *)operator_new(0x50);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = ISingleMap<class_CNpcPath>::vftable;
    *puVar1 = CSingleMap<class_CNpcPath>::vftable;
    FUN_1400364b0(puVar1 + 2);
    *(undefined1 *)(puVar1 + 1) = 1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140037df0 @ 140037df0  longlong * FUN_140037df0(void)

longlong * FUN_140037df0(void)

{
  undefined8 *puVar1;
  longlong *plVar2;
  longlong *plVar3;
  
  plVar3 = DAT_1401045d0;
  if (DAT_1401045d0 == (longlong *)0x0) {
    puVar1 = (undefined8 *)operator_new(8);
    if (puVar1 == (undefined8 *)0x0) {
      DAT_1401045d0 = (longlong *)0x0;
    }
    else {
      DAT_1401045d0 = FUN_140037d80(puVar1);
    }
    if (DAT_1401045d0 == (longlong *)0x0) {
      log_InlineLogERROR(&DAT_1400be0b0);
      plVar3 = (longlong *)0x0;
    }
    else {
      plVar2 = FUN_140036170(DAT_1401045d0);
      plVar3 = DAT_1401045d0;
      if ((char)plVar2 == '\0') {
        if (DAT_1401045d0 != (longlong *)0x0) {
          if ((longlong *)*DAT_1401045d0 != (longlong *)0x0) {
            (**(code **)(*(longlong *)*DAT_1401045d0 + 8))();
          }
          operator_delete(plVar3);
        }
        DAT_1401045d0 = (longlong *)0x0;
        plVar3 = (longlong *)0x0;
      }
    }
  }
  return plVar3;
}


// ==== FUN_140037ef0 @ 140037ef0  undefined FUN_140037ef0(undefined8 * param_1)

void FUN_140037ef0(undefined8 *param_1)

{
  *param_1 = CUserManager::vftable;
  if ((longlong *)param_1[1] != (longlong *)0x0) {
    (**(code **)(*(longlong *)param_1[1] + 8))();
  }
  return;
}


// ==== FUN_140037f80 @ 140037f80  undefined FUN_140037f80(longlong * param_1)

void FUN_140037f80(longlong *param_1)

{
  longlong *plVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  
  plVar1 = (longlong *)(**(code **)(*param_1 + 0x10))();
  uVar2 = (**(code **)(*plVar1 + 0x10))(plVar1);
  while( true ) {
    uVar2 = uVar2 - 1;
    uVar4 = uVar2;
    plVar1 = (longlong *)(**(code **)(*param_1 + 0x10))(param_1);
    uVar3 = (**(code **)(*plVar1 + 0x10))(plVar1);
    if (uVar3 <= uVar2) break;
    plVar1 = (longlong *)(**(code **)(*param_1 + 0x10))(param_1);
    plVar1 = (longlong *)
             (**(code **)(*plVar1 + 0x18))
                       (plVar1,uVar2,
                        "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\usermanager.cpp",
                        0x3a,uVar4);
    if (plVar1 != (longlong *)0x0) {
      FUN_140066820(plVar1);
    }
  }
  return;
}


// ==== FUN_140038010 @ 140038010  longlong FUN_140038010(longlong param_1, int param_2)

longlong FUN_140038010(longlong param_1,int param_2)

{
  bool bVar1;
  longlong lVar2;
  longlong *plVar3;
  
  bVar1 = FUN_14001c1e0(param_2);
  if (!bVar1) {
    bVar1 = FUN_14001c1d0(param_2);
    if (!bVar1) {
      lVar2 = (**(code **)(**(longlong **)(param_1 + 8) + 0x30))
                        (*(longlong **)(param_1 + 8),param_2);
      if (lVar2 != 0) {
        return lVar2 + 0x10;
      }
    }
    lVar2 = FUN_14001c7a0();
    plVar3 = (longlong *)FUN_140027a40(lVar2,param_2);
    if (plVar3 != (longlong *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000140038059. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      lVar2 = (**(code **)(*plVar3 + 0xe8))(plVar3);
      return lVar2;
    }
  }
  return 0;
}


// ==== FUN_140038090 @ 140038090  undefined FUN_140038090(longlong param_1, int * param_2, int * param_3, int * param_4)

void FUN_140038090(longlong param_1,int *param_2,int *param_3,int *param_4)

{
  int iVar1;
  longlong lVar2;
  longlong *plVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  
  if ((param_2 == (int *)0x0) || (param_3 == (int *)0x0)) {
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  else {
    uVar5 = 0;
    *param_2 = 0;
    *param_3 = 0;
    if ((*(longlong *)(param_1 + 8) != 0) &&
       (lVar2 = (**(code **)(**(longlong **)(param_1 + 8) + 0x10))(), lVar2 != 0)) {
      do {
        plVar3 = (longlong *)
                 (**(code **)(**(longlong **)(param_1 + 8) + 0x18))
                           (*(longlong **)(param_1 + 8),uVar5,
                            "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\usermanager.cpp"
                            ,0x6a);
        if (plVar3 != (longlong *)0x0) {
          iVar1 = (**(code **)(*plVar3 + 8))(plVar3);
          if (iVar1 - 0xaae61U < 99999) {
            *param_3 = *param_3 + 1;
          }
          else if (iVar1 - 1000000U < 0xee5be5c0) {
            *param_2 = *param_2 + 1;
          }
          else {
            *param_4 = *param_4 + 1;
          }
        }
        uVar5 = uVar5 + 1;
        uVar4 = (**(code **)(**(longlong **)(param_1 + 8) + 0x10))();
      } while (uVar5 < uVar4);
    }
  }
  return;
}


// ==== FUN_140038190 @ 140038190  undefined FUN_140038190(undefined8 * param_1)

void FUN_140038190(undefined8 *param_1)

{
  *param_1 = IGameObjSet<class_CUser>::vftable;
  return;
}


// ==== FUN_1400383e0 @ 1400383e0  bool FUN_1400383e0(longlong * param_1, longlong * param_2)

bool FUN_1400383e0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_140038520 @ 140038520  undefined FUN_140038520(void)

void FUN_140038520(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [48];
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_70,"invalid vector<T> subscript");
  std::exception::exception((exception *)local_48);
  local_48[0] = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
  local_48[0] = std::out_of_range::vftable;
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400feda0);
}


// ==== FUN_140038590 @ 140038590  longlong FUN_140038590(longlong * param_1)

longlong FUN_140038590(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_1400385b2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_1400385b2:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_1400385d0 @ 1400385d0  longlong FUN_1400385d0(longlong * param_1)

longlong FUN_1400385d0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_1400385f2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_1400385f2:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_140038650 @ 140038650  undefined FUN_140038650(longlong param_1, longlong * param_2)

void FUN_140038650(longlong param_1,longlong *param_2)

{
  longlong lVar1;
  longlong *plVar2;
  
  lVar1 = *param_2;
  *param_2 = *(longlong *)(lVar1 + 0x10);
  if (*(char *)(*(longlong *)(lVar1 + 0x10) + 0x21) == '\0') {
    *(longlong **)(*(longlong *)(lVar1 + 0x10) + 8) = param_2;
  }
  *(longlong *)(lVar1 + 8) = param_2[1];
  if (param_2 == *(longlong **)(*(longlong *)(param_1 + 0x30) + 8)) {
    *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = lVar1;
    *(longlong **)(lVar1 + 0x10) = param_2;
    param_2[1] = lVar1;
    return;
  }
  plVar2 = (longlong *)param_2[1];
  if (param_2 == (longlong *)plVar2[2]) {
    plVar2[2] = lVar1;
    *(longlong **)(lVar1 + 0x10) = param_2;
    param_2[1] = lVar1;
    return;
  }
  *plVar2 = lVar1;
  *(longlong **)(lVar1 + 0x10) = param_2;
  param_2[1] = lVar1;
  return;
}


// ==== FUN_1400386b0 @ 1400386b0  undefined FUN_1400386b0(undefined8 * param_1)

void FUN_1400386b0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_1400386f0 @ 1400386f0  longlong * FUN_1400386f0(longlong * param_1, longlong param_2)

longlong * FUN_1400386f0(longlong *param_1,longlong param_2)

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
    if (plVar1 != (longlong *)0x0) goto LAB_140038720;
  }
  else {
LAB_140038720:
    lVar4 = *plVar1;
  }
  uVar2 = param_1[1] + param_2 * 8;
  if (uVar2 <= *(ulonglong *)(lVar4 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar2) goto LAB_140038748;
  }
  _invalid_parameter_noinfo();
LAB_140038748:
  param_1[1] = param_1[1] + param_2 * 8;
  return param_1;
}


// ==== FUN_1400387d0 @ 1400387d0  undefined FUN_1400387d0(void)

void FUN_1400387d0(void)

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


// ==== FUN_1400388d0 @ 1400388d0  undefined FUN_1400388d0(ulonglong param_1)

void FUN_1400388d0(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x28)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 * 0x28);
  return;
}


// ==== FUN_140038970 @ 140038970  undefined FUN_140038970(ulonglong param_1)

void FUN_140038970(ulonglong param_1)

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


// ==== FUN_140038a90 @ 140038a90  bool FUN_140038a90(longlong * param_1, longlong * param_2)

bool FUN_140038a90(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_140038ae0 @ 140038ae0  undefined FUN_140038ae0(undefined8 * param_1)

void FUN_140038ae0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140038af0 @ 140038af0  longlong FUN_140038af0(longlong * param_1)

longlong FUN_140038af0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140038b12;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140038b12:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_140038b70 @ 140038b70  longlong * FUN_140038b70(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_140038b70(longlong *param_1,longlong *param_2,longlong param_3)

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
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar1) goto LAB_140038bda;
  }
  _invalid_parameter_noinfo();
LAB_140038bda:
  *param_2 = (longlong)plVar2;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_140038c10 @ 140038c10  undefined FUN_140038c10(undefined8 * param_1)

void FUN_140038c10(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140038c50 @ 140038c50  undefined FUN_140038c50(longlong param_1, longlong param_2)

void FUN_140038c50(longlong param_1,longlong param_2)

{
  longlong *plVar1;
  longlong *plVar2;
  
  plVar1 = *(longlong **)(param_2 + 0x10);
  *(longlong *)(param_2 + 0x10) = *plVar1;
  if (*(char *)(*plVar1 + 0x21) == '\0') {
    *(longlong *)(*plVar1 + 8) = param_2;
  }
  plVar1[1] = *(longlong *)(param_2 + 8);
  if (param_2 == *(longlong *)(*(longlong *)(param_1 + 0x30) + 8)) {
    *(longlong **)(*(longlong *)(param_1 + 0x30) + 8) = plVar1;
    *plVar1 = param_2;
    *(longlong **)(param_2 + 8) = plVar1;
    return;
  }
  plVar2 = *(longlong **)(param_2 + 8);
  if (param_2 == *plVar2) {
    *plVar2 = (longlong)plVar1;
    *plVar1 = param_2;
    *(longlong **)(param_2 + 8) = plVar1;
    return;
  }
  plVar2[2] = (longlong)plVar1;
  *plVar1 = param_2;
  *(longlong **)(param_2 + 8) = plVar1;
  return;
}


// ==== FUN_140038cb0 @ 140038cb0  undefined FUN_140038cb0(longlong * param_1)

void FUN_140038cb0(longlong *param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)param_1[1];
  if (*(char *)((longlong)plVar2 + 0x21) == '\0') {
    lVar3 = *plVar2;
    if (*(char *)(lVar3 + 0x21) == '\0') {
      cVar1 = *(char *)(*(longlong *)(lVar3 + 0x10) + 0x21);
      lVar4 = *(longlong *)(lVar3 + 0x10);
      while (lVar5 = lVar4, cVar1 == '\0') {
        lVar4 = *(longlong *)(lVar5 + 0x10);
        cVar1 = *(char *)(lVar4 + 0x21);
        lVar3 = lVar5;
      }
      param_1[1] = lVar3;
      return;
    }
    plVar2 = (longlong *)plVar2[1];
    cVar1 = *(char *)((longlong)plVar2 + 0x21);
    while ((cVar1 == '\0' && (param_1[1] == *plVar2))) {
      param_1[1] = (longlong)plVar2;
      plVar2 = (longlong *)plVar2[1];
      cVar1 = *(char *)((longlong)plVar2 + 0x21);
    }
    if (*(char *)(param_1[1] + 0x21) == '\0') {
      param_1[1] = (longlong)plVar2;
      return;
    }
  }
  else {
    lVar3 = plVar2[2];
    param_1[1] = lVar3;
    if (*(char *)(lVar3 + 0x21) == '\0') {
      return;
    }
  }
                    /* WARNING: Could not recover jumptable at 0x000140038ce2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_140038d50 @ 140038d50  undefined FUN_140038d50(longlong * param_1)

void FUN_140038d50(longlong *param_1)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *plVar4;
  
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  lVar2 = param_1[1];
  if (*(char *)(lVar2 + 0x21) == '\0') {
    plVar3 = *(longlong **)(lVar2 + 0x10);
    if (*(char *)((longlong)plVar3 + 0x21) != '\0') {
      lVar2 = *(longlong *)(lVar2 + 8);
      cVar1 = *(char *)(lVar2 + 0x21);
      while ((cVar1 == '\0' && (param_1[1] == *(longlong *)(lVar2 + 0x10)))) {
        param_1[1] = lVar2;
        lVar2 = *(longlong *)(lVar2 + 8);
        cVar1 = *(char *)(lVar2 + 0x21);
      }
      param_1[1] = lVar2;
      return;
    }
    cVar1 = *(char *)(*plVar3 + 0x21);
    plVar4 = (longlong *)*plVar3;
    while (cVar1 == '\0') {
      cVar1 = *(char *)(*plVar4 + 0x21);
      plVar3 = plVar4;
      plVar4 = (longlong *)*plVar4;
    }
    param_1[1] = (longlong)plVar3;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000140038d74. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_140038df0 @ 140038df0  undefined FUN_140038df0(undefined8 param_1, ulonglong param_2)

void FUN_140038df0(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x28)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 0x28);
  return;
}


// ==== FUN_140038e90 @ 140038e90  undefined FUN_140038e90(undefined8 param_1, ulonglong param_2)

void FUN_140038e90(undefined8 param_1,ulonglong param_2)

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


// ==== FUN_140038f00 @ 140038f00  undefined8 * FUN_140038f00(undefined8 * param_1)

undefined8 * FUN_140038f00(undefined8 *param_1)

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


// ==== FUN_140038f50 @ 140038f50  longlong FUN_140038f50(longlong * param_1)

longlong FUN_140038f50(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140038f72;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140038f72:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_140038f90 @ 140038f90  undefined FUN_140038f90(undefined8 * param_1)

void FUN_140038f90(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140038fc0 @ 140038fc0  undefined8 * FUN_140038fc0(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_140038fc0(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_140039000 @ 140039000  longlong * FUN_140039000(longlong * param_1)

longlong * FUN_140039000(longlong *param_1)

{
  FUN_140038d50(param_1);
  return param_1;
}


// ==== FUN_140039020 @ 140039020  longlong * FUN_140039020(longlong * param_1)

longlong * FUN_140039020(longlong *param_1)

{
  FUN_140038cb0(param_1);
  return param_1;
}


// ==== FUN_140039040 @ 140039040  undefined FUN_140039040(void)

void FUN_140039040(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x28);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = 0;
  }
  if (puVar1 + 1 != (undefined8 *)0x0) {
    puVar1[1] = 0;
  }
  if (puVar1 + 2 != (undefined8 *)0x0) {
    puVar1[2] = 0;
  }
  *(undefined1 *)(puVar1 + 4) = 1;
  *(undefined1 *)((longlong)puVar1 + 0x21) = 0;
  return;
}


// ==== FUN_1400390a0 @ 1400390a0  undefined8 * FUN_1400390a0(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, undefined8 * param_5, undefined1 param_6)

undefined8 *
FUN_1400390a0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             undefined8 *param_5,undefined1 param_6)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x28);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_2;
    puVar1[1] = param_3;
    puVar1[2] = param_4;
    puVar1[3] = *param_5;
    *(undefined1 *)(puVar1 + 4) = param_6;
    *(undefined1 *)((longlong)puVar1 + 0x21) = 0;
  }
  return puVar1;
}


// ==== FUN_140039120 @ 140039120  undefined8 FUN_140039120(longlong param_1, ulonglong param_2)

undefined8 FUN_140039120(longlong param_1,ulonglong param_2)

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
      FUN_1400387d0();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_140038e90(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    lVar3 = lVar3 + param_2 * 8;
    *(longlong *)(param_1 + 0x28) = lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
  }
  return uVar2;
}


// ==== FUN_140039180 @ 140039180  longlong * FUN_140039180(longlong * param_1)

longlong * FUN_140039180(longlong *param_1)

{
  FUN_140038cb0(param_1);
  return param_1;
}


// ==== FUN_1400391a0 @ 1400391a0  longlong * FUN_1400391a0(longlong * param_1, longlong * param_2)

longlong * FUN_1400391a0(longlong *param_1,longlong *param_2)

{
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  FUN_140038d50(param_1);
  return param_2;
}


// ==== FUN_1400391d0 @ 1400391d0  undefined8 * FUN_1400391d0(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_1400391d0(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_140039230 @ 140039230  undefined FUN_140039230(undefined8 param_1, longlong * param_2)

void FUN_140039230(undefined8 param_1,longlong *param_2)

{
  char cVar1;
  longlong *plVar2;
  
  cVar1 = *(char *)((longlong)param_2 + 0x21);
  while (cVar1 == '\0') {
    FUN_140039230(param_1,(longlong *)param_2[2]);
    plVar2 = (longlong *)*param_2;
    operator_delete(param_2);
    param_2 = plVar2;
    cVar1 = *(char *)((longlong)plVar2 + 0x21);
  }
  return;
}


// ==== FUN_140039290 @ 140039290  undefined8 * FUN_140039290(undefined8 * param_1)

undefined8 * FUN_140039290(undefined8 *param_1)

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


// ==== FUN_1400392d0 @ 1400392d0  undefined8 * FUN_1400392d0(undefined8 * param_1)

undefined8 * FUN_1400392d0(undefined8 *param_1)

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


// ==== FUN_140039320 @ 140039320  undefined FUN_140039320(undefined8 * param_1)

void FUN_140039320(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140039340 @ 140039340  undefined8 * FUN_140039340(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_140039340(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_1400393a0 @ 1400393a0  undefined FUN_1400393a0(longlong param_1)

void FUN_1400393a0(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = FUN_140039040();
  *(longlong *)(param_1 + 0x30) = lVar1;
  *(undefined1 *)(lVar1 + 0x21) = 1;
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)*(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x30);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 0x10) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = 0;
  return;
}


// ==== FUN_1400393e0 @ 1400393e0  undefined8 * FUN_1400393e0(undefined8 * param_1, undefined8 * param_2, char param_3, undefined8 * param_4, undefined8 * param_5)

undefined8 *
FUN_1400393e0(undefined8 *param_1,undefined8 *param_2,char param_3,undefined8 *param_4,
             undefined8 *param_5)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [40];
  
  if (0x1ffffffffffffffd < (ulonglong)param_1[7]) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_70,"map/set<T> too long");
    std::exception::exception((exception *)local_48);
    local_48[0] = std::logic_error::vftable;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
    local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
  }
  plVar5 = FUN_1400390a0(param_1,param_1[6],param_4,param_1[6],param_5,0);
  param_1[7] = param_1[7] + 1;
  if (param_4 == (undefined8 *)param_1[6]) {
    ((undefined8 *)param_1[6])[1] = plVar5;
    *(longlong **)param_1[6] = plVar5;
    *(longlong **)(param_1[6] + 0x10) = plVar5;
  }
  else if (param_3 == '\0') {
    param_4[2] = plVar5;
    if (param_4 == *(undefined8 **)(param_1[6] + 0x10)) {
      *(longlong **)(param_1[6] + 0x10) = plVar5;
    }
  }
  else {
    *param_4 = plVar5;
    if (param_4 == *(undefined8 **)param_1[6]) {
      *(longlong **)param_1[6] = plVar5;
    }
  }
  plVar7 = plVar5 + 1;
  cVar1 = *(char *)(*plVar7 + 0x20);
  plVar6 = plVar5;
  while (cVar1 == '\0') {
    plVar2 = (longlong *)*plVar7;
    plVar3 = (longlong *)plVar2[1];
    if (plVar2 == (longlong *)*plVar3) {
      lVar4 = plVar3[2];
      if (*(char *)(lVar4 + 0x20) == '\0') {
        *(undefined1 *)(plVar2 + 4) = 1;
        *(undefined1 *)(lVar4 + 0x20) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x20) = 0;
        plVar6 = *(longlong **)(*plVar7 + 8);
      }
      else {
        if (plVar6 == (longlong *)plVar2[2]) {
          plVar6 = (longlong *)plVar2[2];
          plVar2[2] = *plVar6;
          if (*(char *)(*plVar6 + 0x21) == '\0') {
            *(longlong **)(*plVar6 + 8) = plVar2;
          }
          plVar7 = plVar2 + 1;
          plVar6[1] = *plVar7;
          if (plVar2 == *(longlong **)(param_1[6] + 8)) {
            *(longlong **)(param_1[6] + 8) = plVar6;
          }
          else {
            plVar3 = (longlong *)*plVar7;
            if (plVar2 == (longlong *)*plVar3) {
              *plVar3 = (longlong)plVar6;
            }
            else {
              plVar3[2] = (longlong)plVar6;
            }
          }
          *plVar6 = (longlong)plVar2;
          *plVar7 = (longlong)plVar6;
          plVar6 = plVar2;
        }
        *(undefined1 *)(*plVar7 + 0x20) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x20) = 0;
        plVar7 = *(longlong **)(*plVar7 + 8);
        lVar4 = *plVar7;
        *plVar7 = *(longlong *)(lVar4 + 0x10);
        if (*(char *)(*(longlong *)(lVar4 + 0x10) + 0x21) == '\0') {
          *(longlong **)(*(longlong *)(lVar4 + 0x10) + 8) = plVar7;
        }
        *(longlong *)(lVar4 + 8) = plVar7[1];
        if (plVar7 == *(longlong **)(param_1[6] + 8)) {
          *(longlong *)(param_1[6] + 8) = lVar4;
        }
        else {
          plVar2 = (longlong *)plVar7[1];
          if (plVar7 == (longlong *)plVar2[2]) {
            plVar2[2] = lVar4;
          }
          else {
            *plVar2 = lVar4;
          }
        }
        *(longlong **)(lVar4 + 0x10) = plVar7;
        plVar7[1] = lVar4;
      }
    }
    else {
      lVar4 = *plVar3;
      if (*(char *)(lVar4 + 0x20) == '\0') {
        *(undefined1 *)(plVar2 + 4) = 1;
        *(undefined1 *)(lVar4 + 0x20) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x20) = 0;
        plVar6 = *(longlong **)(*plVar7 + 8);
      }
      else {
        if (plVar6 == (longlong *)*plVar2) {
          lVar4 = *plVar2;
          *plVar2 = *(longlong *)(lVar4 + 0x10);
          if (*(char *)(*(longlong *)(lVar4 + 0x10) + 0x21) == '\0') {
            *(longlong **)(*(longlong *)(lVar4 + 0x10) + 8) = plVar2;
          }
          plVar7 = plVar2 + 1;
          *(longlong *)(lVar4 + 8) = *plVar7;
          if (plVar2 == *(longlong **)(param_1[6] + 8)) {
            *(longlong *)(param_1[6] + 8) = lVar4;
          }
          else {
            plVar6 = (longlong *)*plVar7;
            if (plVar2 == (longlong *)plVar6[2]) {
              plVar6[2] = lVar4;
            }
            else {
              *plVar6 = lVar4;
            }
          }
          *(longlong **)(lVar4 + 0x10) = plVar2;
          *plVar7 = lVar4;
          plVar6 = plVar2;
        }
        *(undefined1 *)(*plVar7 + 0x20) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x20) = 0;
        lVar4 = *(longlong *)(*plVar7 + 8);
        plVar7 = *(longlong **)(lVar4 + 0x10);
        *(longlong *)(lVar4 + 0x10) = *plVar7;
        if (*(char *)(*plVar7 + 0x21) == '\0') {
          *(longlong *)(*plVar7 + 8) = lVar4;
        }
        plVar7[1] = *(longlong *)(lVar4 + 8);
        if (lVar4 == *(longlong *)(param_1[6] + 8)) {
          *(longlong **)(param_1[6] + 8) = plVar7;
        }
        else {
          plVar2 = *(longlong **)(lVar4 + 8);
          if (lVar4 == *plVar2) {
            *plVar2 = (longlong)plVar7;
          }
          else {
            plVar2[2] = (longlong)plVar7;
          }
        }
        *plVar7 = lVar4;
        *(longlong **)(lVar4 + 8) = plVar7;
      }
    }
    plVar7 = plVar6 + 1;
    cVar1 = *(char *)(*plVar7 + 0x20);
  }
  *(undefined1 *)(*(longlong *)(param_1[6] + 8) + 0x20) = 1;
  param_2[1] = plVar5;
  *param_2 = *param_1;
  return param_2;
}


// ==== FUN_140039720 @ 140039720  undefined8 * FUN_140039720(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140039720(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_140039770 @ 140039770  undefined8 * FUN_140039770(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_140039770(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  undefined8 uVar1;
  
  uVar1 = *(undefined8 *)(param_3 + 8);
  if (param_1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_2 = *param_1;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_1400397c0 @ 1400397c0  undefined8 * FUN_1400397c0(undefined8 * param_1, undefined8 * param_2, longlong * param_3)

undefined8 * FUN_1400397c0(undefined8 *param_1,undefined8 *param_2,longlong *param_3)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong lVar5;
  longlong *plVar6;
  longlong *plVar7;
  longlong *plVar8;
  longlong *plVar9;
  undefined **local_80 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_68 [40];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_40 [40];
  
  plVar2 = (longlong *)param_3[1];
  if (*(char *)((longlong)plVar2 + 0x21) != '\0') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_40,"invalid map/set<T> iterator");
    std::exception::exception((exception *)local_80);
    local_80[0] = std::logic_error::vftable;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_68,local_40);
    local_80[0] = std::out_of_range::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_80,(ThrowInfo *)&DAT_1400feda0);
  }
  FUN_140038d50(param_3);
  plVar8 = (longlong *)*plVar2;
  if (*(char *)((longlong)plVar8 + 0x21) == '\0') {
    plVar9 = plVar8;
    if (*(char *)(plVar2[2] + 0x21) == '\0') {
      plVar7 = (longlong *)param_3[1];
      plVar9 = (longlong *)plVar7[2];
      if (plVar7 != plVar2) {
        plVar8[1] = (longlong)plVar7;
        *plVar7 = *plVar2;
        plVar8 = plVar7;
        if (plVar7 != (longlong *)plVar2[2]) {
          plVar8 = (longlong *)plVar7[1];
          if (*(char *)((longlong)plVar9 + 0x21) == '\0') {
            plVar9[1] = (longlong)plVar8;
          }
          *plVar8 = (longlong)plVar9;
          plVar7[2] = plVar2[2];
          *(longlong **)(plVar2[2] + 8) = plVar7;
        }
        if (*(longlong **)(param_1[6] + 8) == plVar2) {
          *(longlong **)(param_1[6] + 8) = plVar7;
        }
        else {
          puVar4 = (undefined8 *)plVar2[1];
          if ((longlong *)*puVar4 == plVar2) {
            *puVar4 = plVar7;
          }
          else {
            puVar4[2] = plVar7;
          }
        }
        plVar7[1] = plVar2[1];
        plVar3 = plVar2 + 4;
        plVar7 = plVar7 + 4;
        if (plVar7 != plVar3) {
          lVar5 = *plVar7;
          *(char *)plVar7 = (char)*plVar3;
          *(char *)plVar3 = (char)lVar5;
        }
        goto LAB_1400399ac;
      }
    }
  }
  else {
    plVar9 = (longlong *)plVar2[2];
  }
  plVar8 = (longlong *)plVar2[1];
  if (*(char *)((longlong)plVar9 + 0x21) == '\0') {
    plVar9[1] = (longlong)plVar8;
  }
  if (*(longlong **)(param_1[6] + 8) == plVar2) {
    *(longlong **)(param_1[6] + 8) = plVar9;
  }
  else if ((longlong *)*plVar8 == plVar2) {
    *plVar8 = (longlong)plVar9;
  }
  else {
    plVar8[2] = (longlong)plVar9;
  }
  if (*(longlong **)param_1[6] == plVar2) {
    plVar7 = plVar8;
    if (*(char *)((longlong)plVar9 + 0x21) == '\0') {
      cVar1 = *(char *)(*plVar9 + 0x21);
      plVar3 = (longlong *)*plVar9;
      plVar7 = plVar9;
      while (plVar6 = plVar3, cVar1 == '\0') {
        plVar3 = (longlong *)*plVar6;
        cVar1 = *(char *)((longlong)plVar3 + 0x21);
        plVar7 = plVar6;
      }
    }
    *(longlong **)param_1[6] = plVar7;
  }
  if (*(longlong **)(param_1[6] + 0x10) == plVar2) {
    plVar7 = plVar8;
    if (*(char *)((longlong)plVar9 + 0x21) == '\0') {
      cVar1 = *(char *)(plVar9[2] + 0x21);
      plVar3 = (longlong *)plVar9[2];
      plVar7 = plVar9;
      while (plVar6 = plVar3, cVar1 == '\0') {
        plVar3 = (longlong *)plVar6[2];
        cVar1 = *(char *)((longlong)plVar3 + 0x21);
        plVar7 = plVar6;
      }
    }
    *(longlong **)(param_1[6] + 0x10) = plVar7;
  }
LAB_1400399ac:
  if ((char)plVar2[4] == '\x01') {
    if (plVar9 != *(longlong **)(param_1[6] + 8)) {
      do {
        plVar7 = plVar8;
        if ((char)plVar9[4] != '\x01') break;
        plVar8 = (longlong *)*plVar7;
        if (plVar9 == plVar8) {
          plVar8 = (longlong *)plVar7[2];
          if ((char)plVar8[4] == '\0') {
            *(undefined1 *)(plVar8 + 4) = 1;
            *(undefined1 *)(plVar7 + 4) = 0;
            FUN_140038c50((longlong)param_1,(longlong)plVar7);
            plVar8 = (longlong *)plVar7[2];
          }
          if (*(char *)((longlong)plVar8 + 0x21) == '\0') {
            if ((*(char *)(*plVar8 + 0x20) != '\x01') || (*(char *)(plVar8[2] + 0x20) != '\x01')) {
              if (*(char *)(plVar8[2] + 0x20) == '\x01') {
                *(undefined1 *)(*plVar8 + 0x20) = 1;
                *(undefined1 *)(plVar8 + 4) = 0;
                FUN_140038650((longlong)param_1,plVar8);
                plVar8 = (longlong *)plVar7[2];
              }
              *(char *)(plVar8 + 4) = (char)plVar7[4];
              *(undefined1 *)(plVar7 + 4) = 1;
              *(undefined1 *)(plVar8[2] + 0x20) = 1;
              FUN_140038c50((longlong)param_1,(longlong)plVar7);
              break;
            }
            *(undefined1 *)(plVar8 + 4) = 0;
          }
        }
        else {
          if ((char)plVar8[4] == '\0') {
            *(undefined1 *)(plVar8 + 4) = 1;
            *(undefined1 *)(plVar7 + 4) = 0;
            FUN_140038650((longlong)param_1,plVar7);
            plVar8 = (longlong *)*plVar7;
          }
          if (*(char *)((longlong)plVar8 + 0x21) == '\0') {
            if ((*(char *)(plVar8[2] + 0x20) != '\x01') || (*(char *)(*plVar8 + 0x20) != '\x01')) {
              if (*(char *)(*plVar8 + 0x20) == '\x01') {
                *(undefined1 *)(plVar8[2] + 0x20) = 1;
                *(undefined1 *)(plVar8 + 4) = 0;
                FUN_140038c50((longlong)param_1,(longlong)plVar8);
                plVar8 = (longlong *)*plVar7;
              }
              *(char *)(plVar8 + 4) = (char)plVar7[4];
              *(undefined1 *)(plVar7 + 4) = 1;
              *(undefined1 *)(*plVar8 + 0x20) = 1;
              FUN_140038650((longlong)param_1,plVar7);
              break;
            }
            *(undefined1 *)(plVar8 + 4) = 0;
          }
        }
        plVar8 = (longlong *)plVar7[1];
        plVar9 = plVar7;
      } while (plVar7 != *(longlong **)(param_1[6] + 8));
    }
    *(undefined1 *)(plVar9 + 4) = 1;
  }
  operator_delete(plVar2);
  if (param_1[7] != 0) {
    param_1[7] = param_1[7] + -1;
  }
  lVar5 = param_3[1];
  *param_2 = *param_1;
  param_2[1] = lVar5;
  return param_2;
}


// ==== FUN_140039b80 @ 140039b80  undefined FUN_140039b80(longlong param_1)

void FUN_140039b80(longlong param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  
  plVar2 = *(longlong **)(*(longlong *)(param_1 + 0x30) + 8);
  cVar1 = *(char *)((longlong)plVar2 + 0x21);
  while (cVar1 == '\0') {
    FUN_140039230(param_1,(longlong *)plVar2[2]);
    plVar3 = (longlong *)*plVar2;
    operator_delete(plVar2);
    plVar2 = plVar3;
    cVar1 = *(char *)((longlong)plVar3 + 0x21);
  }
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)*(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x30);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 0x10) = *(longlong *)(param_1 + 0x30);
  return;
}


// ==== FUN_140039c00 @ 140039c00  undefined FUN_140039c00(longlong param_1)

void FUN_140039c00(longlong param_1)

{
  if (*(void **)(param_1 + 0x18) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_140039c30 @ 140039c30  undefined8 * FUN_140039c30(undefined8 * param_1)

undefined8 * FUN_140039c30(undefined8 *param_1)

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


// ==== FUN_140039c80 @ 140039c80  undefined8 * FUN_140039c80(undefined8 * param_1)

undefined8 * FUN_140039c80(undefined8 *param_1)

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


// ==== FUN_140039cf0 @ 140039cf0  undefined FUN_140039cf0(undefined8 * param_1)

void FUN_140039cf0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140039d50 @ 140039d50  ulonglong FUN_140039d50(longlong * param_1, ulonglong param_2)

ulonglong FUN_140039d50(longlong *param_1,ulonglong param_2)

{
  longlong *plVar1;
  code *pcVar2;
  ulonglong uVar3;
  longlong lVar4;
  longlong lVar5;
  
  uVar3 = param_1[3];
  if ((ulonglong)((longlong)(param_1[4] - uVar3) >> 3) <= param_2) {
    FUN_140038520();
    pcVar2 = (code *)swi(3);
    uVar3 = (*pcVar2)();
    return uVar3;
  }
  if ((ulonglong)param_1[4] < uVar3) {
    _invalid_parameter_noinfo();
  }
  plVar1 = (longlong *)*param_1;
  lVar5 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar4 = lVar5;
  }
  else {
    lVar4 = *plVar1;
  }
  uVar3 = uVar3 + param_2 * 8;
  if (uVar3 <= *(ulonglong *)(lVar4 + 0x20)) {
    lVar4 = lVar5;
    if (plVar1 != (longlong *)0x0) {
      lVar4 = *plVar1;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar3) goto LAB_140039de2;
  }
  _invalid_parameter_noinfo();
LAB_140039de2:
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  else {
    lVar5 = *plVar1;
  }
  if (*(ulonglong *)(lVar5 + 0x20) <= uVar3) {
    _invalid_parameter_noinfo();
  }
  return uVar3;
}


// ==== FUN_140039e20 @ 140039e20  longlong * FUN_140039e20(longlong * param_1, longlong * param_2, int * param_3)

longlong * FUN_140039e20(longlong *param_1,longlong *param_2,int *param_3)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *plVar4;
  longlong *plVar5;
  longlong *plVar6;
  bool bVar7;
  longlong local_38;
  longlong *local_30;
  
  plVar6 = (longlong *)param_1[6];
  bVar7 = true;
  if (*(char *)(plVar6[1] + 0x21) == '\0') {
    plVar5 = (longlong *)plVar6[1];
    do {
      plVar6 = plVar5;
      bVar7 = *param_3 < (int)plVar6[3];
      if (bVar7) {
        plVar5 = (longlong *)*plVar6;
      }
      else {
        plVar5 = (longlong *)plVar6[2];
      }
    } while (*(char *)((longlong)plVar5 + 0x21) == '\0');
  }
  lVar2 = *param_1;
  plVar5 = plVar6;
  local_38 = lVar2;
  plVar4 = plVar6;
  if (bVar7 == false) {
LAB_140039f7d:
    local_30 = plVar4;
    if (*param_3 <= (int)plVar5[3]) {
      *(undefined1 *)(param_2 + 2) = 0;
      *param_2 = local_38;
      goto LAB_140039fac;
    }
  }
  else {
    plVar5 = *(longlong **)param_1[6];
    local_30 = plVar6;
    if (lVar2 == 0) {
      _invalid_parameter_noinfo();
    }
    if (plVar6 != plVar5) {
      if (lVar2 == 0) {
        _invalid_parameter_noinfo();
      }
      if (*(char *)((longlong)plVar6 + 0x21) == '\0') {
        plVar5 = (longlong *)*plVar6;
        if (*(char *)((longlong)plVar5 + 0x21) == '\0') {
          cVar1 = *(char *)(plVar5[2] + 0x21);
          plVar3 = (longlong *)plVar5[2];
          while (plVar4 = plVar5, cVar1 == '\0') {
            cVar1 = *(char *)(plVar3[2] + 0x21);
            plVar5 = plVar3;
            plVar3 = (longlong *)plVar3[2];
          }
        }
        else {
          cVar1 = *(char *)(plVar6[1] + 0x21);
          plVar4 = (longlong *)plVar6[1];
          plVar3 = plVar6;
          while ((plVar5 = plVar4, cVar1 == '\0' && (plVar3 == (longlong *)*plVar5))) {
            cVar1 = *(char *)(plVar5[1] + 0x21);
            plVar4 = (longlong *)plVar5[1];
            plVar3 = plVar5;
            local_30 = plVar5;
          }
          plVar4 = plVar5;
          if (*(char *)((longlong)plVar3 + 0x21) != '\0') {
            _invalid_parameter_noinfo();
            plVar5 = plVar3;
            plVar4 = local_30;
          }
        }
      }
      else {
        plVar5 = (longlong *)plVar6[2];
        plVar4 = plVar5;
        if (*(char *)((longlong)plVar5 + 0x21) != '\0') {
          local_30 = plVar5;
          _invalid_parameter_noinfo();
          plVar4 = local_30;
        }
      }
      goto LAB_140039f7d;
    }
    bVar7 = true;
  }
  plVar6 = FUN_1400393e0(param_1,&local_38,bVar7,plVar6,(undefined8 *)param_3);
  *(undefined1 *)(param_2 + 2) = 1;
  local_30 = (longlong *)plVar6[1];
  *param_2 = *plVar6;
LAB_140039fac:
  param_2[1] = (longlong)local_30;
  return param_2;
}


// ==== FUN_140039fd0 @ 140039fd0  longlong * FUN_140039fd0(longlong * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_140039fd0(longlong *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  char cVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong local_28;
  longlong lStack_20;
  undefined8 local_18 [2];
  
  lVar2 = *(longlong *)param_1[6];
  if ((*param_3 == 0) || (*param_3 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (param_3[1] == lVar2) {
    lVar2 = param_1[6];
    if ((*param_4 == 0) || (*param_4 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    if (param_4[1] == lVar2) {
      FUN_140039b80((longlong)param_1);
      param_2[1] = *(longlong *)param_1[6];
      *param_2 = *param_1;
      return param_2;
    }
  }
  while( true ) {
    if ((*param_3 == 0) || (*param_3 != *param_4)) {
      _invalid_parameter_noinfo();
    }
    lVar2 = *param_3;
    if (param_3[1] == param_4[1]) break;
    lVar3 = param_3[1];
    if (*param_3 == 0) {
      _invalid_parameter_noinfo();
    }
    lVar4 = param_3[1];
    if (*(char *)(lVar4 + 0x21) == '\0') {
      plVar6 = *(longlong **)(lVar4 + 0x10);
      if (*(char *)((longlong)plVar6 + 0x21) == '\0') {
        cVar1 = *(char *)(*plVar6 + 0x21);
        plVar5 = (longlong *)*plVar6;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar5 + 0x21);
          plVar6 = plVar5;
          plVar5 = (longlong *)*plVar5;
        }
      }
      else {
        plVar6 = *(longlong **)(lVar4 + 8);
        cVar1 = *(char *)((longlong)plVar6 + 0x21);
        while ((cVar1 == '\0' && (param_3[1] == plVar6[2]))) {
          param_3[1] = (longlong)plVar6;
          plVar6 = (longlong *)plVar6[1];
          cVar1 = *(char *)((longlong)plVar6 + 0x21);
        }
      }
      param_3[1] = (longlong)plVar6;
    }
    else {
      _invalid_parameter_noinfo();
    }
    local_28 = lVar2;
    lStack_20 = lVar3;
    FUN_1400397c0(param_1,local_18,&local_28);
  }
  lVar2 = param_3[1];
  *param_2 = *param_1;
  param_2[1] = lVar2;
  return param_2;
}


// ==== FUN_14003a180 @ 14003a180  undefined8 * FUN_14003a180(undefined8 * param_1)

undefined8 * FUN_14003a180(undefined8 *param_1)

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


// ==== FUN_14003a1e0 @ 14003a1e0  undefined FUN_14003a1e0(undefined8 * param_1)

void FUN_14003a1e0(undefined8 *param_1)

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


// ==== FUN_14003a220 @ 14003a220  undefined8 * FUN_14003a220(undefined8 * param_1)

undefined8 * FUN_14003a220(undefined8 *param_1)

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


// ==== FUN_14003a270 @ 14003a270  longlong * FUN_14003a270(longlong * param_1, longlong * param_2, int * param_3)

longlong * FUN_14003a270(longlong *param_1,longlong *param_2,int *param_3)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong local_28;
  undefined8 *local_20;
  longlong local_18;
  longlong local_10;
  
  puVar4 = (undefined8 *)param_1[6];
  if (*(char *)((longlong)puVar4[1] + 0x21) == '\0') {
    puVar1 = (undefined8 *)puVar4[1];
    do {
      if (*(int *)(puVar1 + 3) < *param_3) {
        puVar2 = (undefined8 *)puVar1[2];
      }
      else {
        puVar2 = (undefined8 *)*puVar1;
        puVar4 = puVar1;
      }
      puVar1 = puVar2;
    } while (*(char *)((longlong)puVar2 + 0x21) == '\0');
  }
  puVar1 = (undefined8 *)param_1[6];
  local_20 = puVar4;
  local_28 = *param_1;
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  if ((puVar4 == puVar1) || (*param_3 < *(int *)(puVar4 + 3))) {
    plVar3 = &local_18;
    local_10 = param_1[6];
    local_18 = *param_1;
  }
  else {
    plVar3 = &local_28;
  }
  *param_2 = *plVar3;
  param_2[1] = plVar3[1];
  return param_2;
}


// ==== FUN_14003a340 @ 14003a340  undefined8 FUN_14003a340(undefined8 * param_1)

longlong FUN_14003a340(undefined8 *param_1)

{
  longlong lVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *extraout_RAX;
  
  plVar3 = (longlong *)*param_1;
  lVar1 = plVar3[4];
  lVar2 = plVar3[3];
  if ((ulonglong)(lVar1 - lVar2 >> 3) <= (ulonglong)param_1[1]) {
    param_1[2] = 0;
    return (ulonglong)(uint7)(lVar1 - lVar2 >> 0xb) << 8;
  }
  plVar3 = (longlong *)FUN_140039d50(plVar3,param_1[1]);
  lVar1 = *plVar3;
  param_1[2] = lVar1;
  if (lVar1 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    plVar3 = extraout_RAX;
  }
  param_1[1] = param_1[1] + -1;
  return CONCAT71((int7)((ulonglong)plVar3 >> 8),1);
}


// ==== FUN_14003a3c0 @ 14003a3c0  undefined FUN_14003a3c0(undefined8 * param_1)

void FUN_14003a3c0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14003a3e0 @ 14003a3e0  longlong * FUN_14003a3e0(longlong * param_1, longlong * param_2, longlong * param_3, int * param_4)

longlong * FUN_14003a3e0(longlong *param_1,longlong *param_2,longlong *param_3,int *param_4)

{
  char cVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  int iVar8;
  longlong *plVar9;
  longlong local_38;
  longlong *local_30;
  
  if (param_1[7] == 0) {
    FUN_1400393e0(param_1,param_2,'\x01',(undefined8 *)param_1[6],(undefined8 *)param_4);
  }
  else {
    puVar2 = *(undefined8 **)param_1[6];
    if ((*param_3 == 0) || (*param_3 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    puVar3 = (undefined8 *)param_3[1];
    if (puVar3 == puVar2) {
      if (*param_4 < *(int *)(puVar3 + 3)) {
        FUN_1400393e0(param_1,param_2,'\x01',puVar3,(undefined8 *)param_4);
        return param_2;
      }
    }
    else {
      lVar4 = param_1[6];
      if ((*param_3 == 0) || (*param_3 != *param_1)) {
        _invalid_parameter_noinfo();
      }
      if (param_3[1] == lVar4) {
        if (*(int *)(*(undefined8 **)(param_1[6] + 0x10) + 3) < *param_4) {
          FUN_1400393e0(param_1,param_2,'\0',*(undefined8 **)(param_1[6] + 0x10),
                        (undefined8 *)param_4);
          return param_2;
        }
      }
      else {
        iVar8 = *param_4;
        if (iVar8 < *(int *)(param_3[1] + 0x18)) {
          local_38 = *param_3;
          local_30 = (longlong *)param_3[1];
          if (local_38 == 0) {
            _invalid_parameter_noinfo();
          }
          if (*(char *)((longlong)local_30 + 0x21) == '\0') {
            plVar7 = (longlong *)*local_30;
            if (*(char *)((longlong)plVar7 + 0x21) == '\0') {
              cVar1 = *(char *)(plVar7[2] + 0x21);
              plVar9 = (longlong *)plVar7[2];
              while (local_30 = plVar7, cVar1 == '\0') {
                cVar1 = *(char *)(plVar9[2] + 0x21);
                plVar7 = plVar9;
                plVar9 = (longlong *)plVar9[2];
              }
            }
            else {
              cVar1 = *(char *)(local_30[1] + 0x21);
              plVar5 = (longlong *)local_30[1];
              plVar9 = local_30;
              while ((plVar7 = plVar5, cVar1 == '\0' && (plVar9 == (longlong *)*plVar7))) {
                cVar1 = *(char *)(plVar7[1] + 0x21);
                plVar5 = (longlong *)plVar7[1];
                plVar9 = plVar7;
              }
              local_30 = plVar7;
              if (*(char *)((longlong)plVar9 + 0x21) != '\0') {
                local_30 = plVar9;
                _invalid_parameter_noinfo();
                plVar7 = plVar9;
              }
            }
          }
          else {
            plVar7 = (longlong *)local_30[2];
            local_30 = plVar7;
            if (*(char *)((longlong)plVar7 + 0x21) != '\0') {
              _invalid_parameter_noinfo();
            }
          }
          iVar8 = *param_4;
          if ((int)plVar7[3] < iVar8) {
            if (*(char *)(plVar7[2] + 0x21) != '\0') {
              FUN_1400393e0(param_1,param_2,'\0',plVar7,(undefined8 *)param_4);
              return param_2;
            }
            FUN_1400393e0(param_1,param_2,'\x01',(undefined8 *)param_3[1],(undefined8 *)param_4);
            return param_2;
          }
        }
        if (*(int *)(param_3[1] + 0x18) < iVar8) {
          local_38 = *param_3;
          plVar7 = (longlong *)param_1[6];
          local_30 = (longlong *)param_3[1];
          lVar4 = *param_1;
          if (local_38 == 0) {
            _invalid_parameter_noinfo();
          }
          plVar9 = local_30;
          if (*(char *)((longlong)local_30 + 0x21) == '\0') {
            plVar9 = (longlong *)local_30[2];
            if (*(char *)((longlong)plVar9 + 0x21) == '\0') {
              cVar1 = *(char *)(*plVar9 + 0x21);
              plVar5 = (longlong *)*plVar9;
              while (cVar1 == '\0') {
                cVar1 = *(char *)(*plVar5 + 0x21);
                plVar9 = plVar5;
                plVar5 = (longlong *)*plVar5;
              }
            }
            else {
              cVar1 = *(char *)(local_30[1] + 0x21);
              plVar6 = (longlong *)local_30[1];
              plVar5 = local_30;
              while ((plVar9 = plVar6, cVar1 == '\0' && (plVar5 == (longlong *)plVar9[2]))) {
                cVar1 = *(char *)(plVar9[1] + 0x21);
                plVar6 = (longlong *)plVar9[1];
                plVar5 = plVar9;
              }
            }
          }
          else {
            _invalid_parameter_noinfo();
          }
          if ((local_38 == 0) || (local_38 != lVar4)) {
            _invalid_parameter_noinfo();
          }
          if ((plVar9 == plVar7) || (*param_4 < (int)plVar9[3])) {
            if (*(char *)(((undefined8 *)param_3[1])[2] + 0x21) != '\0') {
              FUN_1400393e0(param_1,param_2,'\0',(undefined8 *)param_3[1],(undefined8 *)param_4);
              return param_2;
            }
            FUN_1400393e0(param_1,param_2,'\x01',plVar9,(undefined8 *)param_4);
            return param_2;
          }
        }
      }
    }
    plVar7 = FUN_140039e20(param_1,&local_38,param_4);
    *param_2 = *plVar7;
    param_2[1] = plVar7[1];
  }
  return param_2;
}


// ==== FUN_14003a700 @ 14003a700  undefined FUN_14003a700(longlong * param_1)

void FUN_14003a700(longlong *param_1)

{
  longlong local_38;
  undefined8 *puStack_30;
  longlong local_28;
  undefined8 uStack_20;
  longlong local_18 [2];
  
  local_38 = *param_1;
  puStack_30 = (undefined8 *)param_1[6];
  uStack_20 = *puStack_30;
  local_28 = local_38;
  FUN_140039fd0(param_1,local_18,&local_28,&local_38);
  operator_delete((void *)param_1[6]);
  param_1[6] = 0;
  param_1[7] = 0;
  return;
}


// ==== FUN_14003a770 @ 14003a770  undefined8 * FUN_14003a770(undefined8 * param_1, undefined1 param_2)

undefined8 * FUN_14003a770(undefined8 *param_1,undefined1 param_2)

{
  longlong *plVar1;
  longlong *plVar2;
  
  *param_1 = IGameObjSet<class_CUser>::vftable;
  *param_1 = CGameObjSet<class_CUser>::vftable;
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


// ==== FUN_14003a810 @ 14003a810  longlong FUN_14003a810(longlong param_1, ulonglong param_2)

longlong FUN_14003a810(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)(*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18) >> 3) <= param_2) {
    _invalid_parameter_noinfo();
  }
  return *(longlong *)(param_1 + 0x18) + param_2 * 8;
}


// ==== FUN_14003a910 @ 14003a910  longlong * FUN_14003a910(longlong * param_1, longlong param_2)

longlong * FUN_14003a910(longlong *param_1,longlong param_2)

{
  FUN_1400386f0(param_1,param_2);
  return param_1;
}


// ==== FUN_14003a930 @ 14003a930  longlong FUN_14003a930(longlong * param_1, longlong * param_2)

longlong FUN_14003a930(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] - param_2[1] >> 3;
}


// ==== FUN_14003a970 @ 14003a970  bool FUN_14003a970(longlong * param_1, longlong * param_2)

bool FUN_14003a970(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_14003a9c0 @ 14003a9c0  void * FUN_14003a9c0(void * param_1, longlong param_2, void * param_3)

void * FUN_14003a9c0(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14003aa50 @ 14003aa50  void * FUN_14003aa50(void * param_1, longlong param_2, longlong param_3)

void * FUN_14003aa50(void *param_1,longlong param_2,longlong param_3)

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


// ==== FUN_14003aad0 @ 14003aad0  void * FUN_14003aad0(void * param_1, longlong param_2, void * param_3)

void * FUN_14003aad0(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14003abd0 @ 14003abd0  longlong * FUN_14003abd0(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_14003abd0(longlong *param_1,longlong *param_2,longlong param_3)

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
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar1) goto LAB_14003ac3a;
  }
  _invalid_parameter_noinfo();
LAB_14003ac3a:
  *param_2 = (longlong)plVar2;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_14003ac70 @ 14003ac70  bool FUN_14003ac70(longlong * param_1, longlong * param_2)

bool FUN_14003ac70(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_14003acc0 @ 14003acc0  void * FUN_14003acc0(void * param_1, longlong param_2, longlong param_3)

void * FUN_14003acc0(void *param_1,longlong param_2,longlong param_3)

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


// ==== FUN_14003ad30 @ 14003ad30  void * FUN_14003ad30(void * param_1, longlong param_2, void * param_3)

void * FUN_14003ad30(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14003ad70 @ 14003ad70  undefined8 * FUN_14003ad70(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_14003ad70(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_14003add0 @ 14003add0  void * FUN_14003add0(void * param_1, longlong param_2, void * param_3)

void * FUN_14003add0(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14003ae40 @ 14003ae40  void * FUN_14003ae40(void * param_1, longlong param_2, longlong param_3)

void * FUN_14003ae40(void *param_1,longlong param_2,longlong param_3)

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


// ==== FUN_14003aeb0 @ 14003aeb0  void * FUN_14003aeb0(void * param_1, longlong param_2, void * param_3)

void * FUN_14003aeb0(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14003aef0 @ 14003aef0  undefined8 * FUN_14003aef0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14003aef0(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_14003af40 @ 14003af40  undefined8 * FUN_14003af40(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14003af40(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_14003af90 @ 14003af90  undefined8 * FUN_14003af90(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14003af90(undefined8 *param_1,undefined8 *param_2,longlong param_3)

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


// ==== FUN_14003aff0 @ 14003aff0  longlong * FUN_14003aff0(longlong * param_1, longlong * param_2, longlong param_3, longlong param_4)

longlong * FUN_14003aff0(longlong *param_1,longlong *param_2,longlong param_3,longlong param_4)

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


// ==== FUN_14003b110 @ 14003b110  void * FUN_14003b110(void * param_1, longlong param_2, void * param_3)

void * FUN_14003b110(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14003b150 @ 14003b150  undefined8 * FUN_14003b150(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14003b150(undefined8 *param_1,undefined8 *param_2,longlong param_3)

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


// ==== FUN_14003b210 @ 14003b210  void * FUN_14003b210(undefined8 param_1, void * param_2, longlong param_3, void * param_4)

void * FUN_14003b210(undefined8 param_1,void *param_2,longlong param_3,void *param_4)

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


// ==== FUN_14003b250 @ 14003b250  undefined FUN_14003b250(longlong * param_1)

void FUN_14003b250(longlong *param_1)

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


// ==== FUN_14003b310 @ 14003b310  undefined8 * FUN_14003b310(undefined8 * param_1)

undefined8 * FUN_14003b310(undefined8 *param_1)

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


// ==== FUN_14003b660 @ 14003b660  undefined FUN_14003b660(longlong param_1, longlong param_2, ulonglong param_3, undefined8 * param_4)

void FUN_14003b660(longlong param_1,longlong param_2,ulonglong param_3,undefined8 *param_4)

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
      FUN_1400387d0();
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
      pvVar3 = (void *)FUN_140038e90(param_1 + 0x10,uVar9);
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
      FUN_14003b210(param_1,*(void **)(param_2 + 8),lVar7,
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
      pvVar3 = FUN_14003b210(param_1,pvVar10,lVar7,(void *)lVar7);
      *(void **)(param_1 + 0x20) = pvVar3;
      FUN_14003ae40(*(void **)(param_2 + 8),(longlong)pvVar10,lVar7);
      puVar12 = *(undefined8 **)(param_2 + 8);
      puVar6 = puVar12 + param_3;
      for (; puVar12 != puVar6; puVar12 = puVar12 + 1) {
        *puVar12 = uVar1;
      }
    }
  }
  return;
}


// ==== FUN_14003b910 @ 14003b910  undefined FUN_14003b910(longlong param_1)

void FUN_14003b910(longlong param_1)

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
        (**(code **)(*plVar1 + 0x20))();
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < (ulonglong)(*(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3)
            );
  }
  FUN_14003b250((longlong *)(param_1 + 8));
  return;
}


// ==== FUN_14003b9a0 @ 14003b9a0  undefined4 FUN_14003b9a0(int param_1)

undefined4 FUN_14003b9a0(int param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  undefined4 uVar4;
  longlong *plVar5;
  longlong **pplVar6;
  longlong *plVar7;
  longlong lVar8;
  longlong *local_38;
  longlong *local_30;
  longlong *local_28;
  longlong *local_20;
  longlong *local_18;
  longlong *local_10;
  
  plVar3 = DAT_140104610;
  cVar1 = *(char *)(DAT_140104610[1] + 0x21);
  plVar5 = (longlong *)DAT_140104610[1];
  plVar2 = DAT_140104610;
  while (plVar7 = plVar5, cVar1 == '\0') {
    if ((int)plVar7[3] < param_1) {
      plVar5 = (longlong *)plVar7[2];
      plVar7 = plVar2;
    }
    else {
      plVar5 = (longlong *)*plVar7;
    }
    cVar1 = *(char *)((longlong)plVar5 + 0x21);
    plVar2 = plVar7;
  }
  local_30 = plVar2;
  local_38 = DAT_1401045e0;
  if (DAT_1401045e0 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  plVar5 = DAT_140104610;
  if ((plVar2 == plVar3) || (param_1 < (int)plVar2[3])) {
    local_20 = DAT_140104610;
    local_28 = DAT_1401045e0;
    pplVar6 = &local_28;
  }
  else {
    pplVar6 = &local_38;
  }
  plVar2 = *pplVar6;
  local_18 = plVar2;
  local_10 = pplVar6[1];
  if ((plVar2 == (longlong *)0x0) || (plVar2 != DAT_1401045e0)) {
    _invalid_parameter_noinfo();
  }
  plVar3 = local_10;
  if (local_10 == plVar5) {
    uVar4 = 0;
  }
  else {
    if (plVar2 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar8 = 0;
    }
    else {
      lVar8 = *plVar2;
    }
    if (plVar3 == *(longlong **)(lVar8 + 0x30)) {
      _invalid_parameter_noinfo();
    }
    uVar4 = *(undefined4 *)((longlong)plVar3 + 0x1c);
  }
  return uVar4;
}


// ==== FUN_14003bab0 @ 14003bab0  longlong FUN_14003bab0(longlong param_1, longlong param_2)

longlong FUN_14003bab0(longlong param_1,longlong param_2)

{
  char cVar1;
  char cVar2;
  longlong lVar3;
  longlong lVar4;
  longlong *plVar5;
  char *pcVar6;
  ulonglong uVar7;
  longlong lVar8;
  
  lVar3 = *(longlong *)(param_1 + 8);
  uVar7 = (*(longlong *)(lVar3 + 0x28) - *(longlong *)(lVar3 + 0x20) >> 3) - 1;
  do {
    do {
      if ((ulonglong)(*(longlong *)(lVar3 + 0x28) - *(longlong *)(lVar3 + 0x20) >> 3) <= uVar7) {
        return 0;
      }
      plVar5 = (longlong *)FUN_140039d50((longlong *)(lVar3 + 8),uVar7);
      lVar4 = *plVar5;
      if (lVar4 == 0) {
        log_InlineLogERROR(&DAT_1400be0b0);
      }
      uVar7 = uVar7 - 1;
    } while (lVar4 == 0);
    pcVar6 = (char *)(lVar4 + 0x24);
    lVar8 = param_2 - (longlong)pcVar6;
    do {
      cVar1 = *pcVar6;
      cVar2 = pcVar6[lVar8];
      if (cVar1 != cVar2) break;
      pcVar6 = pcVar6 + 1;
    } while (cVar2 != '\0');
    if (cVar1 == cVar2) {
      return lVar4;
    }
  } while( true );
}


// ==== FUN_14003bb80 @ 14003bb80  longlong FUN_14003bb80(longlong * param_1, int * param_2)

longlong FUN_14003bb80(longlong *param_1,int *param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong lVar5;
  longlong *plVar6;
  int local_res8 [2];
  longlong *local_38;
  undefined8 *puStack_30;
  longlong local_28 [2];
  
  puVar4 = (undefined8 *)param_1[6];
  if (*(char *)((longlong)puVar4[1] + 0x21) == '\0') {
    puVar1 = (undefined8 *)puVar4[1];
    do {
      if (*(int *)(puVar1 + 3) < *param_2) {
        puVar2 = (undefined8 *)puVar1[2];
      }
      else {
        puVar2 = (undefined8 *)*puVar1;
        puVar4 = puVar1;
      }
      puVar1 = puVar2;
    } while (*(char *)((longlong)puVar2 + 0x21) == '\0');
  }
  plVar6 = (longlong *)*param_1;
  puVar1 = (undefined8 *)param_1[6];
  if (plVar6 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  lVar5 = 0;
  if ((puVar4 == puVar1) || (*param_2 < *(int *)(puVar4 + 3))) {
    local_res8[0] = *param_2;
    local_res8[1] = 0;
    local_38 = plVar6;
    puStack_30 = puVar4;
    plVar3 = FUN_14003a3e0(param_1,local_28,(longlong *)&local_38,local_res8);
    plVar6 = (longlong *)*plVar3;
    puVar4 = (undefined8 *)plVar3[1];
  }
  if (plVar6 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  else {
    lVar5 = *plVar6;
  }
  if (puVar4 == *(undefined8 **)(lVar5 + 0x30)) {
    _invalid_parameter_noinfo();
  }
  return (longlong)puVar4 + 0x1c;
}


// ==== FUN_14003bc80 @ 14003bc80  undefined FUN_14003bc80(longlong * param_1)

void FUN_14003bc80(longlong *param_1)

{
  FUN_14003a700(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14003bcb0 @ 14003bcb0  undefined8 * FUN_14003bcb0(undefined1 param_1)

undefined8 * FUN_14003bcb0(undefined1 param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x40);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    puVar1 = FUN_14003a770(puVar1,param_1);
  }
  return puVar1;
}


// ==== FUN_14003bcf0 @ 14003bcf0  undefined8 * FUN_14003bcf0(undefined8 * param_1)

undefined8 * FUN_14003bcf0(undefined8 *param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  lVar2 = FUN_140039040();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x21) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_14003bd70 @ 14003bd70  undefined FUN_14003bd70(undefined8 * param_1)

void FUN_14003bd70(undefined8 *param_1)

{
  *param_1 = CGameObjSet<class_CUser>::vftable;
  FUN_14003b910((longlong)param_1);
  if ((void *)param_1[4] != (void *)0x0) {
    operator_delete((void *)param_1[4]);
  }
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  operator_delete((void *)param_1[1]);
  *param_1 = IGameObjSet<class_CUser>::vftable;
  return;
}


// ==== FUN_14003bde0 @ 14003bde0  longlong * FUN_14003bde0(longlong * param_1, longlong * param_2, longlong * param_3, undefined8 * param_4)

longlong * FUN_14003bde0(longlong *param_1,longlong *param_2,longlong *param_3,undefined8 *param_4)

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
  FUN_14003b660((longlong)param_1,(longlong)&local_28,1,param_4);
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
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar1) goto LAB_14003bed4;
  }
  _invalid_parameter_noinfo();
LAB_14003bed4:
  *param_2 = (longlong)local_28;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_14003bf10 @ 14003bf10  undefined FUN_14003bf10(longlong * param_1)

void FUN_14003bf10(longlong *param_1)

{
  FUN_14003a700(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14003bf40 @ 14003bf40  undefined8 * FUN_14003bf40(undefined8 * param_1)

undefined8 * FUN_14003bf40(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  *param_1 = CUserManager::vftable;
  puVar1 = (undefined8 *)operator_new(0x40);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    puVar1 = FUN_14003a770(puVar1,1);
  }
  param_1[1] = puVar1;
  return param_1;
}


// ==== FUN_14003bf90 @ 14003bf90  undefined FUN_14003bf90(longlong param_1)

void FUN_14003bf90(longlong param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  undefined1 auStack_658 [32];
  undefined4 local_638;
  uint local_628 [2];
  undefined8 local_620;
  CIniFile local_618 [1024];
  char local_218 [256];
  char local_118 [256];
  ulonglong local_18;
  
  local_620 = 0xfffffffffffffffe;
  local_18 = DAT_140103510 ^ (ulonglong)auStack_658;
  if (*(longlong *)(param_1 + 8) == 0) {
    local_638 = 0x1d;
    log_InlineLogERROR(&DAT_1400be0b0,"CHECKF","m_pUserSet",
                       "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\usermanager.cpp");
  }
  else {
    CIniFile::CIniFile(local_618,"ini\\AdditiveSize.ini","Header");
    iVar1 = CIniFile::GetInt(local_618,"Amount");
    uVar4 = 0;
    if (0 < iVar1) {
      do {
        sprintf(local_218,"Index%d",(ulonglong)uVar4);
        CIniFile::SetSection(local_618,"Header");
        local_628[0] = CIniFile::GetInt(local_618,local_218);
        if (local_628[0] != 0) {
          sprintf(local_118,"Transform%d",(ulonglong)local_628[0]);
          CIniFile::SetSection(local_618,local_118);
          iVar2 = CIniFile::GetInt(local_618,"AdditiveSize");
          piVar3 = (int *)FUN_14003bb80(&DAT_1401045e0,(int *)local_628);
          *piVar3 = iVar2;
        }
        uVar4 = uVar4 + 1;
      } while ((int)uVar4 < iVar1);
    }
    CIniFile::~CIniFile(local_618);
  }
  __security_check_cookie(local_18 ^ (ulonglong)auStack_658);
  return;
}


// ==== FUN_14003c110 @ 14003c110  undefined8 * FUN_14003c110(undefined8 * param_1)

undefined8 * FUN_14003c110(undefined8 *param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  lVar2 = FUN_140039040();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x21) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_14003c1c0 @ 14003c1c0  undefined FUN_14003c1c0(longlong * param_1, undefined8 * param_2)

void FUN_14003c1c0(longlong *param_1,undefined8 *param_2)

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
  FUN_14003bde0(param_1,local_18,&local_28,param_2);
  return;
}


// ==== FUN_14003c340 @ 14003c340  undefined8 * FUN_14003c340(void)

undefined8 * FUN_14003c340(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x90);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    puVar1 = FUN_1400550f0(puVar1);
  }
  return puVar1;
}


// ==== FUN_14003c390 @ 14003c390  longlong * FUN_14003c390(longlong param_1)

longlong * FUN_14003c390(longlong param_1)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  ulonglong extraout_RAX;
  ITerrainObjInfoMgr *pIVar4;
  ulonglong extraout_RAX_00;
  ulonglong extraout_RAX_01;
  undefined8 uVar5;
  longlong *plVar6;
  undefined8 *puVar7;
  longlong *plVar8;
  ulonglong uVar9;
  int iVar10;
  
  if (*(longlong *)(param_1 + 8) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    plVar6 = (longlong *)(extraout_RAX & 0xffffffffffffff00);
  }
  else {
    pIVar4 = ITerrainObjInfoMgr::CreateNew();
    *(ITerrainObjInfoMgr **)(param_1 + 0x10) = pIVar4;
    if (pIVar4 == (ITerrainObjInfoMgr *)0x0) {
      log_InlineLogERROR("CMapManager::Create ITerrainObjInfoMgr::CreateNew failed.");
      plVar6 = (longlong *)(extraout_RAX_00 & 0xffffffffffffff00);
    }
    else {
      cVar2 = (*(code *)**(undefined8 **)pIVar4)(pIVar4);
      if (cVar2 == '\0') {
        log_InlineLogERROR("CMapManager::Create m_pTerrainObjInfoMgr init failed.");
        plVar6 = (longlong *)(extraout_RAX_01 & 0xffffffffffffff00);
      }
      else {
        uVar5 = FUN_14001c200();
        plVar6 = (longlong *)InstanceGet(uVar5);
        plVar6 = (longlong *)
                 (**(code **)(*plVar6 + 0x10))(plVar6,"SELECT * FROM cq_map LIMIT 1234567890",2);
        if (plVar6 != (longlong *)0x0) {
          bVar1 = false;
          iVar10 = 0;
          iVar3 = (**(code **)(*plVar6 + 0x40))(plVar6);
          if (0 < iVar3) {
            do {
              (**(code **)(*plVar6 + 0x30))(plVar6,(longlong)iVar10);
              puVar7 = (undefined8 *)operator_new(0x90);
              if (puVar7 == (undefined8 *)0x0) {
                plVar8 = (longlong *)0x0;
              }
              else {
                plVar8 = FUN_1400550f0(puVar7);
              }
              if (plVar8 == (longlong *)0x0) {
                uVar9 = (**(code **)*plVar6)(plVar6);
                return (longlong *)(uVar9 & 0xffffffffffffff00);
              }
              cVar2 = (**(code **)(*plVar8 + 0x20))(plVar8,plVar6,0);
              if (cVar2 == '\0') {
                (**(code **)(*plVar8 + 0x38))(plVar8);
                if (!bVar1) {
                  bVar1 = true;
                }
              }
              else {
                (**(code **)(**(longlong **)(param_1 + 8) + 0x20))
                          (*(longlong **)(param_1 + 8),plVar8);
              }
              iVar10 = iVar10 + 1;
              iVar3 = (**(code **)(*plVar6 + 0x40))(plVar6);
            } while (iVar10 < iVar3);
          }
          uVar5 = (**(code **)*plVar6)(plVar6);
          plVar6 = (longlong *)CONCAT71((int7)((ulonglong)uVar5 >> 8),!bVar1);
        }
      }
    }
  }
  return plVar6;
}


// ==== FUN_14003c520 @ 14003c520  undefined FUN_14003c520(void)

void FUN_14003c520(void)

{
  return;
}


// ==== FUN_14003c530 @ 14003c530  undefined8 FUN_14003c530(longlong param_1, int param_2)

undefined8 FUN_14003c530(longlong param_1,int param_2)

{
  undefined8 uVar1;
  
  if (*(longlong *)(param_1 + 0x10) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return 0;
  }
  if (param_2 == 0) {
    log_InlineLogERROR("CMapManager::GetTerrainObjFileName idTerrainObj is 0.");
    return 0;
  }
                    /* WARNING: Could not recover jumptable at 0x00014003c58f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (**(code **)(**(longlong **)(param_1 + 0x10) + 8))();
  return uVar1;
}


// ==== FUN_14003c5a0 @ 14003c5a0  undefined FUN_14003c5a0(undefined8 * param_1)

void FUN_14003c5a0(undefined8 *param_1)

{
  *param_1 = IGameObjSet<class_CGameMap>::vftable;
  return;
}


// ==== FUN_14003c780 @ 14003c780  undefined FUN_14003c780(longlong * param_1)

void FUN_14003c780(longlong *param_1)

{
  if ((undefined8 *)*param_1 != (undefined8 *)0x0) {
    (*(code *)**(undefined8 **)*param_1)();
  }
  return;
}


// ==== FUN_14003c7b0 @ 14003c7b0  longlong FUN_14003c7b0(longlong * param_1)

longlong FUN_14003c7b0(longlong *param_1)

{
  if (*param_1 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return *param_1;
  }
  return *param_1;
}


// ==== FUN_14003c850 @ 14003c850  undefined FUN_14003c850(void)

void FUN_14003c850(void)

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


// ==== FUN_14003c8f0 @ 14003c8f0  undefined FUN_14003c8f0(longlong * param_1)

void FUN_14003c8f0(longlong *param_1)

{
  if ((longlong *)*param_1 != (longlong *)0x0) {
    (**(code **)(*(longlong *)*param_1 + 0x10))();
    *param_1 = 0;
  }
  return;
}


// ==== FUN_14003c930 @ 14003c930  undefined FUN_14003c930(ulonglong param_1)

void FUN_14003c930(ulonglong param_1)

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


// ==== FUN_14003c9c0 @ 14003c9c0  undefined FUN_14003c9c0(undefined8 * param_1)

void FUN_14003c9c0(undefined8 *param_1)

{
  *param_1 = CMapManager::vftable;
  if ((longlong *)param_1[1] != (longlong *)0x0) {
    (**(code **)(*(longlong *)param_1[1] + 8))();
  }
  if (param_1[2] != 0) {
    (**(code **)(*(longlong *)param_1[2] + 0x10))();
    param_1[2] = 0;
  }
  return;
}


// ==== FUN_14003ca10 @ 14003ca10  undefined FUN_14003ca10(longlong param_1, int param_2)

void FUN_14003ca10(longlong param_1,int param_2)

{
  char cVar1;
  int iVar2;
  longlong lVar3;
  longlong *plVar4;
  undefined8 uVar5;
  longlong *plVar6;
  longlong *plVar7;
  undefined1 auStack_478 [32];
  undefined4 local_458;
  longlong *local_448;
  undefined8 *local_440;
  undefined8 local_438;
  char local_428 [1024];
  ulonglong local_28;
  
  local_438 = 0xfffffffffffffffe;
  local_28 = DAT_140103510 ^ (ulonglong)auStack_478;
  if (param_2 == 0) {
    local_458 = 0x6e;
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  else {
    plVar6 = (longlong *)0x0;
    lVar3 = (**(code **)(**(longlong **)(param_1 + 8) + 0x10))();
    plVar7 = plVar6;
    if (lVar3 != 0) {
      do {
        plVar4 = (longlong *)
                 (**(code **)(**(longlong **)(param_1 + 8) + 0x18))
                           (*(longlong **)(param_1 + 8),plVar7,
                            "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\mapmanager.cpp"
                            ,0x72);
        if ((plVar4 != (longlong *)0x0) &&
           (iVar2 = (**(code **)(*plVar4 + 8))(plVar4), iVar2 == param_2)) goto LAB_14003cbe7;
        plVar7 = (longlong *)((longlong)plVar7 + 1);
        plVar4 = (longlong *)(**(code **)(**(longlong **)(param_1 + 8) + 0x10))();
      } while (plVar7 < plVar4);
    }
    sprintf(local_428,"SELECT * FROM cq_dynamap WHERE id=%u && del_flag=0 LIMIT 1");
    uVar5 = FUN_14001c200();
    plVar7 = (longlong *)InstanceGet(uVar5);
    plVar7 = (longlong *)(**(code **)(*plVar7 + 0x10))(plVar7,local_428,2);
    local_448 = plVar7;
    if ((plVar7 == (longlong *)0x0) || (lVar3 = (**(code **)(*plVar7 + 0x40))(plVar7), lVar3 == 0))
    {
      if (plVar7 != (longlong *)0x0) {
        (**(code **)*plVar7)(plVar7);
      }
    }
    else {
      local_440 = (undefined8 *)operator_new(0x90);
      if (local_440 != (undefined8 *)0x0) {
        plVar6 = FUN_1400550f0(local_440);
      }
      if (plVar6 == (longlong *)0x0) {
        (**(code **)*plVar7)(plVar7);
      }
      else {
        cVar1 = (**(code **)(*plVar6 + 0x20))(plVar6,plVar7,1);
        if (cVar1 == '\0') {
          local_458 = 0x85;
          log_InlineLogERROR(&DAT_1400be0b0);
          (**(code **)(*plVar6 + 0x38))(plVar6);
          (**(code **)*plVar7)(plVar7);
        }
        else {
          (**(code **)(**(longlong **)(param_1 + 8) + 0x20))(*(longlong **)(param_1 + 8),plVar6);
          (**(code **)*plVar7)(plVar7);
        }
      }
    }
  }
LAB_14003cbe7:
  __security_check_cookie(local_28 ^ (ulonglong)auStack_478);
  return;
}


// ==== FUN_14003cc10 @ 14003cc10  undefined8 FUN_14003cc10(longlong param_1, uint param_2)

ulonglong FUN_14003cc10(longlong param_1,uint param_2)

{
  ulonglong in_RAX;
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  undefined8 uVar4;
  
  if (param_2 == 0) {
    uVar1 = in_RAX & 0xffffffffffffff00;
  }
  else {
    plVar2 = (longlong *)FUN_14003ca10(param_1,param_2);
    if ((plVar2 == (longlong *)0x0) || ((char)plVar2[0x11] == '\0')) {
      uVar1 = (ulonglong)plVar2 & 0xffffffffffffff00;
    }
    else {
      (**(code **)(*plVar2 + 0x30))(plVar2);
      lVar3 = FUN_14001c7a0();
      FUN_140033860(lVar3,param_2);
      lVar3 = FUN_14001c790();
      if (*(longlong *)(lVar3 + 8) == 0) {
        log_InlineLogERROR(&DAT_1400be0b0);
        plVar2 = (longlong *)0x0;
      }
      else {
        plVar2 = *(longlong **)(lVar3 + 8);
      }
      uVar4 = (**(code **)(*plVar2 + 0x28))(plVar2,param_2);
      uVar1 = CONCAT71((int7)((ulonglong)uVar4 >> 8),1);
    }
  }
  return uVar1;
}


// ==== FUN_14003ccb0 @ 14003ccb0  undefined FUN_14003ccb0(undefined8 * param_1)

void FUN_14003ccb0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14003ccd0 @ 14003ccd0  undefined FUN_14003ccd0(undefined8 param_1, ulonglong param_2)

void FUN_14003ccd0(undefined8 param_1,ulonglong param_2)

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


// ==== FUN_14003cd80 @ 14003cd80  longlong * FUN_14003cd80(longlong param_1, uint param_2, uint param_3)

longlong * FUN_14003cd80(longlong param_1,uint param_2,uint param_3)

{
  char cVar1;
  longlong lVar2;
  undefined8 *puVar3;
  longlong *plVar4;
  
  lVar2 = FUN_14003ca10(param_1,param_2);
  if (lVar2 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    plVar4 = (longlong *)0x0;
  }
  else {
    puVar3 = (undefined8 *)operator_new(0x90);
    if (puVar3 == (undefined8 *)0x0) {
      plVar4 = (longlong *)0x0;
    }
    else {
      plVar4 = FUN_1400550f0(puVar3);
    }
    if (plVar4 == (longlong *)0x0) {
      log_InlineLogERROR(&DAT_1400be0b0);
      plVar4 = (longlong *)0x0;
    }
    else {
      cVar1 = (**(code **)(*plVar4 + 0x28))(plVar4,lVar2,param_3);
      if (cVar1 == '\0') {
        log_InlineLogERROR("CMapManager::CreateNewInstanceMap error %u");
        (**(code **)(*plVar4 + 0x38))(plVar4);
        plVar4 = (longlong *)0x0;
      }
      else {
        (**(code **)(**(longlong **)(param_1 + 8) + 0x20))(*(longlong **)(param_1 + 8),plVar4);
        lVar2 = FUN_14001c7a0();
        FUN_140032e20(lVar2,param_2,param_3);
      }
    }
  }
  return plVar4;
}


// ==== FUN_14003cea0 @ 14003cea0  undefined FUN_14003cea0(undefined8 * param_1)

void FUN_14003cea0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14003cec0 @ 14003cec0  undefined8 FUN_14003cec0(longlong param_1, ulonglong param_2)

undefined8 FUN_14003cec0(longlong param_1,ulonglong param_2)

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
      FUN_14003c850();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_14003ccd0(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    lVar3 = lVar3 + param_2 * 8;
    *(longlong *)(param_1 + 0x28) = lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
  }
  return uVar2;
}


// ==== FUN_14003cf30 @ 14003cf30  undefined8 * FUN_14003cf30(undefined8 * param_1)

undefined8 * FUN_14003cf30(undefined8 *param_1)

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


// ==== FUN_14003cf70 @ 14003cf70  undefined FUN_14003cf70(longlong param_1)

void FUN_14003cf70(longlong param_1)

{
  if (*(void **)(param_1 + 0x18) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_14003cfa0 @ 14003cfa0  undefined8 * FUN_14003cfa0(undefined8 * param_1)

undefined8 * FUN_14003cfa0(undefined8 *param_1)

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


// ==== FUN_14003cff0 @ 14003cff0  undefined8 * FUN_14003cff0(undefined8 * param_1)

undefined8 * FUN_14003cff0(undefined8 *param_1)

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


// ==== FUN_14003d050 @ 14003d050  undefined FUN_14003d050(undefined8 * param_1)

void FUN_14003d050(undefined8 *param_1)

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


// ==== FUN_14003d090 @ 14003d090  undefined8 * FUN_14003d090(undefined8 * param_1, undefined1 param_2)

undefined8 * FUN_14003d090(undefined8 *param_1,undefined1 param_2)

{
  longlong *plVar1;
  longlong *plVar2;
  
  *param_1 = IGameObjSet<class_CGameMap>::vftable;
  *param_1 = CGameObjSet<class_CGameMap>::vftable;
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


// ==== FUN_14003d140 @ 14003d140  longlong FUN_14003d140(longlong param_1, ulonglong param_2)

longlong FUN_14003d140(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)(*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18) >> 3) <= param_2) {
    _invalid_parameter_noinfo();
  }
  return *(longlong *)(param_1 + 0x18) + param_2 * 8;
}


// ==== FUN_14003d240 @ 14003d240  longlong * FUN_14003d240(longlong * param_1, longlong param_2)

longlong * FUN_14003d240(longlong *param_1,longlong param_2)

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
    if (plVar1 != (longlong *)0x0) goto LAB_14003d270;
  }
  else {
LAB_14003d270:
    lVar4 = *plVar1;
  }
  uVar2 = param_1[1] + param_2 * 8;
  if (uVar2 <= *(ulonglong *)(lVar4 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar2) goto LAB_14003d298;
  }
  _invalid_parameter_noinfo();
LAB_14003d298:
  param_1[1] = param_1[1] + param_2 * 8;
  return param_1;
}


// ==== FUN_14003d2b0 @ 14003d2b0  longlong FUN_14003d2b0(longlong * param_1, longlong * param_2)

longlong FUN_14003d2b0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] - param_2[1] >> 3;
}


// ==== FUN_14003d300 @ 14003d300  bool FUN_14003d300(longlong * param_1, longlong * param_2)

bool FUN_14003d300(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_14003d350 @ 14003d350  void * FUN_14003d350(void * param_1, longlong param_2, void * param_3)

void * FUN_14003d350(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14003d3e0 @ 14003d3e0  void * FUN_14003d3e0(void * param_1, longlong param_2, longlong param_3)

void * FUN_14003d3e0(void *param_1,longlong param_2,longlong param_3)

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


// ==== FUN_14003d460 @ 14003d460  void * FUN_14003d460(void * param_1, longlong param_2, void * param_3)

void * FUN_14003d460(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14003d560 @ 14003d560  longlong * FUN_14003d560(longlong * param_1, longlong param_2)

longlong * FUN_14003d560(longlong *param_1,longlong param_2)

{
  FUN_14003d240(param_1,param_2);
  return param_1;
}


// ==== FUN_14003d590 @ 14003d590  bool FUN_14003d590(longlong * param_1, longlong * param_2)

bool FUN_14003d590(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_14003d5e0 @ 14003d5e0  void * FUN_14003d5e0(void * param_1, longlong param_2, longlong param_3)

void * FUN_14003d5e0(void *param_1,longlong param_2,longlong param_3)

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


// ==== FUN_14003d650 @ 14003d650  void * FUN_14003d650(void * param_1, longlong param_2, void * param_3)

void * FUN_14003d650(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14003d690 @ 14003d690  longlong * FUN_14003d690(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_14003d690(longlong *param_1,longlong *param_2,longlong param_3)

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
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar1) goto LAB_14003d6fa;
  }
  _invalid_parameter_noinfo();
LAB_14003d6fa:
  *param_2 = (longlong)plVar2;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_14003d730 @ 14003d730  undefined8 * FUN_14003d730(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_14003d730(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_14003d790 @ 14003d790  void * FUN_14003d790(void * param_1, longlong param_2, void * param_3)

void * FUN_14003d790(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14003d800 @ 14003d800  void * FUN_14003d800(void * param_1, longlong param_2, longlong param_3)

void * FUN_14003d800(void *param_1,longlong param_2,longlong param_3)

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


// ==== FUN_14003d870 @ 14003d870  void * FUN_14003d870(void * param_1, longlong param_2, void * param_3)

void * FUN_14003d870(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14003d8b0 @ 14003d8b0  undefined8 * FUN_14003d8b0(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_14003d8b0(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_14003d940 @ 14003d940  void * FUN_14003d940(void * param_1, longlong param_2, void * param_3)

void * FUN_14003d940(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14003d980 @ 14003d980  undefined8 * FUN_14003d980(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14003d980(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_14003d9d0 @ 14003d9d0  undefined8 * FUN_14003d9d0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14003d9d0(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_14003da20 @ 14003da20  undefined8 * FUN_14003da20(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14003da20(undefined8 *param_1,undefined8 *param_2,longlong param_3)

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


// ==== FUN_14003dab0 @ 14003dab0  void * FUN_14003dab0(undefined8 param_1, void * param_2, longlong param_3, void * param_4)

void * FUN_14003dab0(undefined8 param_1,void *param_2,longlong param_3,void *param_4)

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


// ==== FUN_14003daf0 @ 14003daf0  longlong * FUN_14003daf0(longlong * param_1, longlong * param_2, longlong param_3, longlong param_4)

longlong * FUN_14003daf0(longlong *param_1,longlong *param_2,longlong param_3,longlong param_4)

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


// ==== FUN_14003dbe0 @ 14003dbe0  undefined8 * FUN_14003dbe0(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14003dbe0(undefined8 *param_1,undefined8 *param_2,longlong param_3)

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


// ==== FUN_14003dca0 @ 14003dca0  undefined FUN_14003dca0(longlong param_1, longlong param_2, ulonglong param_3, undefined8 * param_4)

void FUN_14003dca0(longlong param_1,longlong param_2,ulonglong param_3,undefined8 *param_4)

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
      FUN_14003c850();
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
      pvVar3 = (void *)FUN_14003ccd0(param_1 + 0x10,uVar9);
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
      FUN_14003dab0(param_1,*(void **)(param_2 + 8),lVar7,
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
      pvVar3 = FUN_14003dab0(param_1,pvVar10,lVar7,(void *)lVar7);
      *(void **)(param_1 + 0x20) = pvVar3;
      FUN_14003d800(*(void **)(param_2 + 8),(longlong)pvVar10,lVar7);
      puVar12 = *(undefined8 **)(param_2 + 8);
      puVar6 = puVar12 + param_3;
      for (; puVar12 != puVar6; puVar12 = puVar12 + 1) {
        *puVar12 = uVar1;
      }
    }
  }
  return;
}


// ==== FUN_14003df50 @ 14003df50  undefined FUN_14003df50(longlong * param_1)

void FUN_14003df50(longlong *param_1)

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


// ==== FUN_14003e010 @ 14003e010  undefined8 * FUN_14003e010(undefined1 param_1)

undefined8 * FUN_14003e010(undefined1 param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x40);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    puVar1 = FUN_14003d090(puVar1,param_1);
  }
  return puVar1;
}


// ==== FUN_14003e320 @ 14003e320  longlong * FUN_14003e320(longlong * param_1, longlong * param_2, longlong * param_3, undefined8 * param_4)

longlong * FUN_14003e320(longlong *param_1,longlong *param_2,longlong *param_3,undefined8 *param_4)

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
  FUN_14003dca0((longlong)param_1,(longlong)&local_28,1,param_4);
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
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar1) goto LAB_14003e414;
  }
  _invalid_parameter_noinfo();
LAB_14003e414:
  *param_2 = (longlong)local_28;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_14003e450 @ 14003e450  undefined FUN_14003e450(longlong param_1)

void FUN_14003e450(longlong param_1)

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
        (**(code **)(*plVar1 + 0x38))();
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < (ulonglong)(*(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3)
            );
  }
  FUN_14003df50((longlong *)(param_1 + 8));
  return;
}


// ==== FUN_14003e4e0 @ 14003e4e0  undefined8 * FUN_14003e4e0(undefined8 * param_1)

undefined8 * FUN_14003e4e0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  *param_1 = CMapManager::vftable;
  puVar1 = (undefined8 *)operator_new(0x40);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    puVar1 = FUN_14003d090(puVar1,1);
  }
  param_1[1] = puVar1;
  param_1[2] = 0;
  return param_1;
}


// ==== FUN_14003e540 @ 14003e540  undefined FUN_14003e540(undefined8 * param_1)

void FUN_14003e540(undefined8 *param_1)

{
  *param_1 = CGameObjSet<class_CGameMap>::vftable;
  FUN_14003e450((longlong)param_1);
  if ((void *)param_1[4] != (void *)0x0) {
    operator_delete((void *)param_1[4]);
  }
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  operator_delete((void *)param_1[1]);
  *param_1 = IGameObjSet<class_CGameMap>::vftable;
  return;
}


// ==== FUN_14003e5b0 @ 14003e5b0  undefined FUN_14003e5b0(longlong * param_1, undefined8 * param_2)

void FUN_14003e5b0(longlong *param_1,undefined8 *param_2)

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
  FUN_14003e320(param_1,local_18,&local_28,param_2);
  return;
}


// ==== FUN_14003e760 @ 14003e760  undefined FUN_14003e760(undefined8 * param_1)

void FUN_14003e760(undefined8 *param_1)

{
  *param_1 = IAIStrategy::vftable;
  return;
}


// ==== FUN_14003e770 @ 14003e770  double FUN_14003e770(void)

double FUN_14003e770(void)

{
  int iVar1;
  
  iVar1 = rand();
  return (double)iVar1 * 3.0517578125e-05;
}


// ==== FUN_14003e790 @ 14003e790  int FUN_14003e790(int param_1, int param_2)

int FUN_14003e790(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = rand();
  return param_1 + iVar1 % ((param_2 - param_1) + 1);
}


// ==== FUN_14003e7c0 @ 14003e7c0  double FUN_14003e7c0(void)

double FUN_14003e7c0(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = rand();
  iVar2 = rand();
  return (double)iVar1 * 3.0517578125e-05 - (double)iVar2 * 3.0517578125e-05;
}


// ==== FUN_14003e840 @ 14003e840  longlong FUN_14003e840(longlong param_1, ulonglong param_2)

longlong FUN_14003e840(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)(*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18) >> 3) <= param_2) {
    _invalid_parameter_noinfo();
  }
  return *(longlong *)(param_1 + 0x18) + param_2 * 8;
}


// ==== FUN_14003e890 @ 14003e890  longlong FUN_14003e890(longlong param_1, ulonglong param_2)

longlong FUN_14003e890(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)(*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18) >> 2) <= param_2) {
    _invalid_parameter_noinfo();
  }
  return *(longlong *)(param_1 + 0x18) + param_2 * 4;
}


// ==== FUN_14003e8e0 @ 14003e8e0  longlong FUN_14003e8e0(longlong * param_1)

longlong FUN_14003e8e0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14003e902;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14003e902:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_14003e920 @ 14003e920  longlong * FUN_14003e920(longlong * param_1)

longlong * FUN_14003e920(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14003e942;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14003e942:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + 0x10;
  return param_1;
}


// ==== FUN_14003e960 @ 14003e960  longlong FUN_14003e960(longlong * param_1)

longlong FUN_14003e960(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14003e982;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14003e982:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_14003eaf0 @ 14003eaf0  undefined FUN_14003eaf0(void)

void FUN_14003eaf0(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [48];
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_70,"invalid vector<T> subscript");
  std::exception::exception((exception *)local_48);
  local_48[0] = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
  local_48[0] = std::out_of_range::vftable;
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400feda0);
}


// ==== FUN_14003eb90 @ 14003eb90  bool FUN_14003eb90(longlong * param_1, longlong * param_2)

bool FUN_14003eb90(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_14003ebd0 @ 14003ebd0  longlong * FUN_14003ebd0(longlong * param_1)

longlong * FUN_14003ebd0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14003ebf2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14003ebf2:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + 8;
  return param_1;
}


// ==== FUN_14003ec10 @ 14003ec10  bool FUN_14003ec10(longlong * param_1, longlong * param_2)

bool FUN_14003ec10(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_14003ec50 @ 14003ec50  undefined FUN_14003ec50(undefined8 * param_1)

void FUN_14003ec50(undefined8 *param_1)

{
  basic_istream<char,struct_std::char_traits<char>_> *pbVar1;
  
  if ((basic_istream<char,struct_std::char_traits<char>_> *)*param_1 !=
      (basic_istream<char,struct_std::char_traits<char>_> *)0x0) {
    pbVar1 = std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
                       ((basic_istream<char,struct_std::char_traits<char>_> *)*param_1,
                        (double *)(param_1 + 1));
    if (((byte)pbVar1[(longlong)*(int *)(*(longlong *)pbVar1 + 4) + 0x10] & 6) != 0) {
      *param_1 = 0;
    }
  }
  return;
}


// ==== FUN_14003ecb0 @ 14003ecb0  undefined FUN_14003ecb0(void)

void FUN_14003ecb0(void)

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


// ==== FUN_14003ed30 @ 14003ed30  undefined FUN_14003ed30(void)

void FUN_14003ed30(void)

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


// ==== FUN_14003eda0 @ 14003eda0  undefined FUN_14003eda0(void)

void FUN_14003eda0(void)

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


// ==== FUN_14003ee20 @ 14003ee20  undefined FUN_14003ee20(void)

void FUN_14003ee20(void)

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


// ==== FUN_14003eeb0 @ 14003eeb0  longlong * FUN_14003eeb0(longlong * param_1, longlong param_2)

longlong * FUN_14003eeb0(longlong *param_1,longlong param_2)

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
    if (plVar1 != (longlong *)0x0) goto LAB_14003eee0;
  }
  else {
LAB_14003eee0:
    lVar2 = *plVar1;
  }
  uVar4 = param_1[1] + param_2 * 0x10;
  if (uVar4 <= *(ulonglong *)(lVar2 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar4) goto LAB_14003ef08;
  }
  _invalid_parameter_noinfo();
LAB_14003ef08:
  param_1[1] = param_1[1] + param_2 * 0x10;
  return param_1;
}


// ==== FUN_14003ef20 @ 14003ef20  longlong FUN_14003ef20(longlong * param_1, longlong * param_2)

longlong FUN_14003ef20(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] - param_2[1] >> 4;
}


// ==== FUN_14003ef60 @ 14003ef60  longlong FUN_14003ef60(longlong * param_1, longlong * param_2)

longlong FUN_14003ef60(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] - param_2[1] >> 3;
}


// ==== FUN_14003efa0 @ 14003efa0  undefined8 * FUN_14003efa0(undefined8 * param_1, longlong * param_2)

undefined8 * FUN_14003efa0(undefined8 *param_1,longlong *param_2)

{
  longlong lVar1;
  
  *param_1 = param_2;
  lVar1 = *(longlong *)((longlong)*(int *)(*param_2 + 4) + 0x48 + (longlong)param_2);
  if (lVar1 != 0) {
    std::_Mutex::_Lock((_Mutex *)(lVar1 + 8));
  }
  return param_1;
}


// ==== FUN_14003efd0 @ 14003efd0  undefined FUN_14003efd0(longlong * param_1)

void FUN_14003efd0(longlong *param_1)

{
  longlong lVar1;
  
  lVar1 = *(longlong *)((longlong)*(int *)(*(longlong *)*param_1 + 4) + 0x48 + *param_1);
  if (lVar1 != 0) {
    std::_Mutex::_Unlock((_Mutex *)(lVar1 + 8));
  }
  return;
}


// ==== FUN_14003f050 @ 14003f050  longlong * FUN_14003f050(longlong * param_1, longlong param_2)

longlong * FUN_14003f050(longlong *param_1,longlong param_2)

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
    if (plVar1 != (longlong *)0x0) goto LAB_14003f080;
  }
  else {
LAB_14003f080:
    lVar4 = *plVar1;
  }
  uVar2 = param_1[1] + param_2 * 8;
  if (uVar2 <= *(ulonglong *)(lVar4 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar2) goto LAB_14003f0a8;
  }
  _invalid_parameter_noinfo();
LAB_14003f0a8:
  param_1[1] = param_1[1] + param_2 * 8;
  return param_1;
}


// ==== FUN_14003f0c0 @ 14003f0c0  bool FUN_14003f0c0(longlong * param_1, longlong * param_2)

bool FUN_14003f0c0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_14003f100 @ 14003f100  bool FUN_14003f100(longlong * param_1, longlong * param_2)

bool FUN_14003f100(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_14003f170 @ 14003f170  undefined FUN_14003f170(undefined8 * param_1)

void FUN_14003f170(undefined8 *param_1)

{
  *param_1 = tq::Singleton<class_CAIStrategyMgr>::vftable;
  return;
}


// ==== FUN_14003f190 @ 14003f190  undefined FUN_14003f190(ulonglong param_1)

void FUN_14003f190(ulonglong param_1)

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


// ==== FUN_14003f200 @ 14003f200  undefined FUN_14003f200(ulonglong param_1)

void FUN_14003f200(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x38)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 * 0x38);
  return;
}


// ==== FUN_14003f280 @ 14003f280  undefined FUN_14003f280(ulonglong param_1)

void FUN_14003f280(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 4)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 << 2);
  return;
}


// ==== FUN_14003f300 @ 14003f300  undefined FUN_14003f300(ulonglong param_1)

void FUN_14003f300(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x10)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 << 4);
  return;
}


// ==== FUN_14003f3c0 @ 14003f3c0  undefined FUN_14003f3c0(undefined8 * param_1)

void FUN_14003f3c0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14003f440 @ 14003f440  void * FUN_14003f440(void * param_1, longlong param_2, void * param_3)

void * FUN_14003f440(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14003f4c0 @ 14003f4c0  void * FUN_14003f4c0(void * param_1, longlong param_2, void * param_3)

void * FUN_14003f4c0(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14003f5a0 @ 14003f5a0  longlong * FUN_14003f5a0(longlong * param_1)

longlong * FUN_14003f5a0(longlong *param_1)

{
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
    return param_1 + 1;
  }
  return param_1 + 1;
}


// ==== FUN_14003f5d0 @ 14003f5d0  longlong * FUN_14003f5d0(longlong * param_1)

longlong * FUN_14003f5d0(longlong *param_1)

{
  basic_istream<char,struct_std::char_traits<char>_> *pbVar1;
  
  pbVar1 = (basic_istream<char,struct_std::char_traits<char>_> *)*param_1;
  if (pbVar1 == (basic_istream<char,struct_std::char_traits<char>_> *)0x0) {
    _invalid_parameter_noinfo();
    pbVar1 = (basic_istream<char,struct_std::char_traits<char>_> *)*param_1;
    if (pbVar1 == (basic_istream<char,struct_std::char_traits<char>_> *)0x0) {
      return param_1;
    }
  }
  pbVar1 = std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
                     (pbVar1,(double *)(param_1 + 1));
  if (((byte)pbVar1[(longlong)*(int *)(*(longlong *)pbVar1 + 4) + 0x10] & 6) != 0) {
    *param_1 = 0;
  }
  return param_1;
}


// ==== FUN_14003f660 @ 14003f660  undefined8 * FUN_14003f660(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_14003f660(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  param_1[1] = param_2;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14) = 1;
  *param_1 = std::tr1::_Ref_count<class_CNeuralAIStrategy>::vftable;
  return param_1;
}


// ==== FUN_14003f6e0 @ 14003f6e0  undefined8 * FUN_14003f6e0(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_14003f6e0(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  param_1[1] = param_2;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14) = 1;
  *param_1 = std::tr1::_Ref_count<class_CDefaultAIStrategy>::vftable;
  return param_1;
}


// ==== FUN_14003f760 @ 14003f760  undefined FUN_14003f760(undefined8 * param_1)

void FUN_14003f760(undefined8 *param_1)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  return;
}


// ==== FUN_14003f780 @ 14003f780  undefined FUN_14003f780(undefined8 * param_1)

void FUN_14003f780(undefined8 *param_1)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  return;
}


// ==== FUN_14003f7e0 @ 14003f7e0  void * FUN_14003f7e0(void * param_1, longlong param_2, void * param_3)

void * FUN_14003f7e0(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14003f840 @ 14003f840  void * FUN_14003f840(void * param_1, longlong param_2, void * param_3)

void * FUN_14003f840(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _DstSize = lVar1 * 4;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14003f880 @ 14003f880  void * FUN_14003f880(void * param_1, longlong param_2, longlong param_3)

void * FUN_14003f880(void *param_1,longlong param_2,longlong param_3)

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


// ==== FUN_14003f8e0 @ 14003f8e0  longlong * FUN_14003f8e0(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_14003f8e0(longlong *param_1,longlong *param_2,longlong param_3)

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
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar1) goto LAB_14003f94a;
  }
  _invalid_parameter_noinfo();
LAB_14003f94a:
  *param_2 = (longlong)plVar2;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_14003f9e0 @ 14003f9e0  undefined FUN_14003f9e0(undefined8 * param_1)

void FUN_14003f9e0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14003fa00 @ 14003fa00  undefined FUN_14003fa00(void)

void FUN_14003fa00(void)

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


// ==== FUN_14003fa80 @ 14003fa80  bool FUN_14003fa80(longlong * param_1, longlong * param_2)

bool FUN_14003fa80(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_14003fb20 @ 14003fb20  undefined FUN_14003fb20(ulonglong param_1)

void FUN_14003fb20(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x38)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 * 0x38);
  return;
}


// ==== FUN_14003fcb0 @ 14003fcb0  void * FUN_14003fcb0(void * param_1, longlong param_2, void * param_3)

void * FUN_14003fcb0(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14003fcf0 @ 14003fcf0  undefined8 * FUN_14003fcf0(undefined8 * param_1)

undefined8 * FUN_14003fcf0(undefined8 *param_1)

{
  *param_1 = IAIStrategy::vftable;
  *param_1 = CDefaultAIStrategy::vftable;
  return param_1;
}


// ==== FUN_14003fd90 @ 14003fd90  longlong FUN_14003fd90(longlong * param_1)

longlong FUN_14003fd90(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14003fdb2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14003fdb2:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_14003fdd0 @ 14003fdd0  longlong * FUN_14003fdd0(longlong * param_1)

longlong * FUN_14003fdd0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14003fdf2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14003fdf2:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + 0x10;
  return param_1;
}


// ==== FUN_14003fe10 @ 14003fe10  longlong * FUN_14003fe10(longlong * param_1, longlong * param_2)

longlong * FUN_14003fe10(longlong *param_1,longlong *param_2)

{
  undefined8 *puVar1;
  
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14003fe47;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14003fe47:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + 0x10;
  return param_2;
}


// ==== FUN_14003fe70 @ 14003fe70  bool FUN_14003fe70(longlong * param_1, longlong * param_2)

bool FUN_14003fe70(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_14003feb0 @ 14003feb0  longlong FUN_14003feb0(longlong * param_1)

longlong FUN_14003feb0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14003fed2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14003fed2:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_14003fef0 @ 14003fef0  longlong * FUN_14003fef0(longlong * param_1)

longlong * FUN_14003fef0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14003ff12;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14003ff12:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + 8;
  return param_1;
}


// ==== FUN_14003ff30 @ 14003ff30  longlong * FUN_14003ff30(longlong * param_1, longlong * param_2)

longlong * FUN_14003ff30(longlong *param_1,longlong *param_2)

{
  undefined8 *puVar1;
  
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14003ff67;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14003ff67:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + 8;
  return param_2;
}


// ==== FUN_14003ff90 @ 14003ff90  bool FUN_14003ff90(longlong * param_1, longlong * param_2)

bool FUN_14003ff90(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_14003ffd0 @ 14003ffd0  undefined8 * FUN_14003ffd0(undefined8 * param_1, basic_istream<char,struct_std::char_traits<char>_> * param_2)

undefined8 *
FUN_14003ffd0(undefined8 *param_1,basic_istream<char,struct_std::char_traits<char>_> *param_2)

{
  basic_istream<char,struct_std::char_traits<char>_> *pbVar1;
  
  *param_1 = param_2;
  if (param_2 != (basic_istream<char,struct_std::char_traits<char>_> *)0x0) {
    pbVar1 = std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
                       (param_2,(double *)(param_1 + 1));
    if (((byte)pbVar1[(longlong)*(int *)(*(longlong *)pbVar1 + 4) + 0x10] & 6) != 0) {
      *param_1 = 0;
      return param_1;
    }
  }
  return param_1;
}


// ==== FUN_140040020 @ 140040020  undefined FUN_140040020(undefined8 * param_1)

void FUN_140040020(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140040030 @ 140040030  undefined FUN_140040030(longlong param_1)

void FUN_140040030(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_1 + 8);
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
  return;
}


// ==== FUN_140040070 @ 140040070  undefined FUN_140040070(undefined8 * param_1)

void FUN_140040070(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140040080 @ 140040080  undefined FUN_140040080(undefined8 * param_1)

void FUN_140040080(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140040090 @ 140040090  undefined FUN_140040090(longlong param_1)

void FUN_140040090(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_1 + 8);
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
  return;
}


// ==== FUN_1400400d0 @ 1400400d0  longlong * FUN_1400400d0(longlong * param_1, longlong param_2)

longlong * FUN_1400400d0(longlong *param_1,longlong param_2)

{
  FUN_14003eeb0(param_1,param_2);
  return param_1;
}


// ==== FUN_1400400f0 @ 1400400f0  undefined8 * FUN_1400400f0(undefined8 * param_1, longlong * param_2)

undefined8 * FUN_1400400f0(undefined8 *param_1,longlong *param_2)

{
  longlong lVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  
  *param_1 = param_2;
  lVar1 = *(longlong *)((longlong)*(int *)(*param_2 + 4) + 0x48 + (longlong)param_2);
  if (lVar1 != 0) {
    std::_Mutex::_Lock((_Mutex *)(lVar1 + 8));
  }
  if ((*(int *)((longlong)*(int *)(*param_2 + 4) + 0x10 + (longlong)param_2) == 0) &&
     (this = *(basic_ostream<char,struct_std::char_traits<char>_> **)
              ((longlong)*(int *)(*param_2 + 4) + 0x50 + (longlong)param_2),
     this != (basic_ostream<char,struct_std::char_traits<char>_> *)0x0)) {
    std::basic_ostream<char,struct_std::char_traits<char>_>::flush(this);
  }
  *(bool *)(param_1 + 1) =
       *(int *)((longlong)*(int *)(*param_2 + 4) + 0x10 + (longlong)param_2) == 0;
  return param_1;
}


// ==== FUN_140040170 @ 140040170  undefined FUN_140040170(longlong * param_1)

void FUN_140040170(longlong *param_1)

{
  longlong lVar1;
  bool bVar2;
  
  bVar2 = std::uncaught_exception();
  if (!bVar2) {
    std::basic_ostream<char,struct_std::char_traits<char>_>::_Osfx
              ((basic_ostream<char,struct_std::char_traits<char>_> *)*param_1);
  }
  lVar1 = *(longlong *)((longlong)*(int *)(*(longlong *)*param_1 + 4) + 0x48 + *param_1);
  if (lVar1 != 0) {
    std::_Mutex::_Unlock((_Mutex *)(lVar1 + 8));
  }
  return;
}


// ==== FUN_1400401e0 @ 1400401e0  undefined FUN_1400401e0(undefined8 param_1, ulonglong param_2)

void FUN_1400401e0(undefined8 param_1,ulonglong param_2)

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


// ==== FUN_140040260 @ 140040260  undefined FUN_140040260(undefined8 param_1, ulonglong param_2)

void FUN_140040260(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x38)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 0x38);
  return;
}


// ==== FUN_1400402d0 @ 1400402d0  undefined FUN_1400402d0(undefined8 * param_1, undefined8 param_2, longlong param_3)

void FUN_1400402d0(undefined8 *param_1,undefined8 param_2,longlong param_3)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  if (param_3 != 0) {
    LOCK();
    *(int *)(param_3 + 0x10) = *(int *)(param_3 + 0x10) + 1;
    UNLOCK();
  }
  plVar3 = (longlong *)param_1[1];
  if (plVar3 == (longlong *)0x0) {
    param_1[1] = param_3;
    *param_1 = param_2;
  }
  else {
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
      param_1[1] = param_3;
      *param_1 = param_2;
    }
    else {
      param_1[1] = param_3;
      *param_1 = param_2;
    }
  }
  return;
}


// ==== FUN_140040370 @ 140040370  undefined FUN_140040370(undefined8 param_1, ulonglong param_2)

void FUN_140040370(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 4)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 4);
  return;
}


// ==== FUN_1400403f0 @ 1400403f0  undefined FUN_1400403f0(undefined8 param_1, ulonglong param_2)

void FUN_1400403f0(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x10)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 << 4);
  return;
}


// ==== FUN_140040460 @ 140040460  undefined FUN_140040460(undefined8 * param_1, undefined8 param_2, longlong param_3)

void FUN_140040460(undefined8 *param_1,undefined8 param_2,longlong param_3)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  if (param_3 != 0) {
    LOCK();
    *(int *)(param_3 + 0x10) = *(int *)(param_3 + 0x10) + 1;
    UNLOCK();
  }
  plVar3 = (longlong *)param_1[1];
  if (plVar3 == (longlong *)0x0) {
    param_1[1] = param_3;
    *param_1 = param_2;
  }
  else {
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
      param_1[1] = param_3;
      *param_1 = param_2;
    }
    else {
      param_1[1] = param_3;
      *param_1 = param_2;
    }
  }
  return;
}


// ==== FUN_1400404f0 @ 1400404f0  longlong * FUN_1400404f0(longlong * param_1, longlong param_2)

longlong * FUN_1400404f0(longlong *param_1,longlong param_2)

{
  FUN_14003eeb0(param_1,-param_2);
  return param_1;
}


// ==== FUN_140040510 @ 140040510  undefined8 * FUN_140040510(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140040510(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_140040580 @ 140040580  longlong * FUN_140040580(longlong * param_1, longlong param_2)

longlong * FUN_140040580(longlong *param_1,longlong param_2)

{
  FUN_14003f050(param_1,param_2);
  return param_1;
}


// ==== FUN_1400405a0 @ 1400405a0  bool FUN_1400405a0(longlong * param_1, longlong * param_2)

bool FUN_1400405a0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_1400405e0 @ 1400405e0  bool FUN_1400405e0(longlong * param_1, longlong * param_2)

bool FUN_1400405e0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_140040650 @ 140040650  basic_ostream<char,struct_std::char_traits<char>_> * FUN_140040650(basic_ostream<char,struct_std::char_traits<char>_> * param_1, char param_2)

basic_ostream<char,struct_std::char_traits<char>_> *
FUN_140040650(basic_ostream<char,struct_std::char_traits<char>_> *param_1,char param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  int iVar5;
  
  iVar3 = 0;
  iVar5 = 0;
  if (*(longlong *)(param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x48) != 0) {
    std::_Mutex::_Lock((_Mutex *)
                       (*(longlong *)(param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x48)
                       + 8));
  }
  if ((*(int *)(param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x10) == 0) &&
     (*(basic_ostream<char,struct_std::char_traits<char>_> **)
       (param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x50) !=
      (basic_ostream<char,struct_std::char_traits<char>_> *)0x0)) {
    std::basic_ostream<char,struct_std::char_traits<char>_>::flush
              (*(basic_ostream<char,struct_std::char_traits<char>_> **)
                (param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x50));
  }
  if (*(int *)(param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x10) == 0) {
    if (*(longlong *)(param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x28) < 2) {
      lVar4 = 0;
    }
    else {
      lVar4 = *(longlong *)(param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x28) + -1;
    }
    iVar2 = 0;
    if ((*(uint *)(param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x18) & 0x1c0) == 0x40)
    {
LAB_140040752:
      iVar5 = iVar2;
      iVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::sputc
                        (*(basic_streambuf<char,struct_std::char_traits<char>_> **)
                          (param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x48),param_2);
      if (iVar3 == -1) {
        iVar5 = 4;
      }
      for (; (iVar5 == 0 && (0 < lVar4)); lVar4 = lVar4 + -1) {
        iVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::sputc
                          (*(basic_streambuf<char,struct_std::char_traits<char>_> **)
                            (param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x48),
                           (char)param_1[(longlong)*(int *)(*(longlong *)param_1 + 4) + 0x58]);
        if (iVar3 == -1) {
          iVar5 = 4;
        }
      }
    }
    else {
      while (iVar5 == 0) {
        iVar2 = iVar3;
        if (lVar4 < 1) goto LAB_140040752;
        iVar2 = std::basic_streambuf<char,struct_std::char_traits<char>_>::sputc
                          (*(basic_streambuf<char,struct_std::char_traits<char>_> **)
                            (param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x48),
                           (char)param_1[(longlong)*(int *)(*(longlong *)param_1 + 4) + 0x58]);
        iVar3 = 0;
        if (iVar2 == -1) {
          iVar3 = 4;
          iVar5 = 4;
        }
        lVar4 = lVar4 + -1;
      }
    }
  }
  *(undefined8 *)(param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x28) = 0;
  std::basic_ios<char,struct_std::char_traits<char>_>::setstate
            ((basic_ios<char,struct_std::char_traits<char>_> *)
             (param_1 + *(int *)(*(longlong *)param_1 + 4)),iVar5,false);
  bVar1 = std::uncaught_exception();
  if (!bVar1) {
    std::basic_ostream<char,struct_std::char_traits<char>_>::_Osfx(param_1);
  }
  if (*(longlong *)(param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x48) != 0) {
    std::_Mutex::_Unlock
              ((_Mutex *)
               (*(longlong *)(param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x48) + 8));
  }
  return param_1;
}


// ==== FUN_140040840 @ 140040840  basic_ostream<char,struct_std::char_traits<char>_> * FUN_140040840(basic_ostream<char,struct_std::char_traits<char>_> * param_1, char * param_2)

basic_ostream<char,struct_std::char_traits<char>_> *
FUN_140040840(basic_ostream<char,struct_std::char_traits<char>_> *param_1,char *param_2)

{
  longlong lVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  __int64 _Var5;
  ulonglong uVar6;
  int iVar7;
  char *pcVar8;
  longlong lVar9;
  
  iVar7 = 0;
  uVar6 = 0xffffffffffffffff;
  pcVar8 = param_2;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    cVar2 = *pcVar8;
    pcVar8 = pcVar8 + 1;
  } while (cVar2 != '\0');
  lVar1 = ~uVar6 - 1;
  lVar9 = *(longlong *)(param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x28);
  if ((lVar9 < 1) || (lVar9 <= lVar1)) {
    lVar9 = 0;
  }
  else {
    lVar9 = lVar9 - lVar1;
  }
  if (*(longlong *)(param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x48) != 0) {
    std::_Mutex::_Lock((_Mutex *)
                       (*(longlong *)(param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x48)
                       + 8));
  }
  if ((*(int *)(param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x10) == 0) &&
     (*(basic_ostream<char,struct_std::char_traits<char>_> **)
       (param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x50) !=
      (basic_ostream<char,struct_std::char_traits<char>_> *)0x0)) {
    std::basic_ostream<char,struct_std::char_traits<char>_>::flush
              (*(basic_ostream<char,struct_std::char_traits<char>_> **)
                (param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x50));
  }
  if (*(int *)(param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x10) != 0) {
    iVar7 = 4;
    goto LAB_1400409c6;
  }
  if ((*(uint *)(param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x18) & 0x1c0) == 0x40) {
LAB_14004094a:
    _Var5 = std::basic_streambuf<char,struct_std::char_traits<char>_>::sputn
                      (*(basic_streambuf<char,struct_std::char_traits<char>_> **)
                        (param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x48),param_2,
                       lVar1);
    if (_Var5 == lVar1) {
      for (; 0 < lVar9; lVar9 = lVar9 + -1) {
        iVar4 = std::basic_streambuf<char,struct_std::char_traits<char>_>::sputc
                          (*(basic_streambuf<char,struct_std::char_traits<char>_> **)
                            (param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x48),
                           (char)param_1[(longlong)*(int *)(*(longlong *)param_1 + 4) + 0x58]);
        if (iVar4 == -1) {
          iVar7 = 4;
          break;
        }
      }
    }
    else {
      iVar7 = 4;
    }
  }
  else {
    for (; 0 < lVar9; lVar9 = lVar9 + -1) {
      iVar4 = std::basic_streambuf<char,struct_std::char_traits<char>_>::sputc
                        (*(basic_streambuf<char,struct_std::char_traits<char>_> **)
                          (param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x48),
                         (char)param_1[(longlong)*(int *)(*(longlong *)param_1 + 4) + 0x58]);
      if (iVar4 == -1) {
        iVar7 = 4;
        break;
      }
    }
    if (iVar7 == 0) goto LAB_14004094a;
  }
  *(undefined8 *)(param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x28) = 0;
LAB_1400409c6:
  std::basic_ios<char,struct_std::char_traits<char>_>::setstate
            ((basic_ios<char,struct_std::char_traits<char>_> *)
             (param_1 + *(int *)(*(longlong *)param_1 + 4)),iVar7,false);
  bVar3 = std::uncaught_exception();
  if (!bVar3) {
    std::basic_ostream<char,struct_std::char_traits<char>_>::_Osfx(param_1);
  }
  if (*(longlong *)(param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x48) != 0) {
    std::_Mutex::_Unlock
              ((_Mutex *)
               (*(longlong *)(param_1 + (longlong)*(int *)(*(longlong *)param_1 + 4) + 0x48) + 8));
  }
  return param_1;
}


// ==== FUN_140040a70 @ 140040a70  undefined FUN_140040a70(undefined8 * param_1)

void FUN_140040a70(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140040a90 @ 140040a90  undefined8 * FUN_140040a90(undefined8 * param_1)

undefined8 * FUN_140040a90(undefined8 *param_1)

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


// ==== FUN_140040b10 @ 140040b10  void * FUN_140040b10(void * param_1, longlong param_2, void * param_3)

void * FUN_140040b10(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_140040b70 @ 140040b70  void * FUN_140040b70(void * param_1, longlong param_2, void * param_3)

void * FUN_140040b70(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _DstSize = lVar1 * 4;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_140040bb0 @ 140040bb0  void * FUN_140040bb0(void * param_1, longlong param_2, longlong param_3)

void * FUN_140040bb0(void *param_1,longlong param_2,longlong param_3)

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


// ==== FUN_140040c00 @ 140040c00  undefined8 * FUN_140040c00(undefined8 * param_1, double * param_2)

undefined8 * FUN_140040c00(undefined8 *param_1,double *param_2)

{
  longlong lVar1;
  
  std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
            ((basic_ostream<char,struct_std::char_traits<char>_> *)param_1[1],*param_2);
  if ((char *)*param_1 != (char *)0x0) {
    FUN_140040840((basic_ostream<char,struct_std::char_traits<char>_> *)param_1[1],(char *)*param_1)
    ;
  }
  lVar1 = (longlong)*(int *)(*(longlong *)param_1[1] + 4) + (longlong)param_1[1];
  if ((*(byte *)(lVar1 + 0x10) & 6) != 0) {
    lVar1 = 0;
  }
  if (lVar1 == 0) {
    _invalid_parameter_noinfo();
  }
  return param_1;
}


// ==== FUN_140040d10 @ 140040d10  void * FUN_140040d10(void * param_1, longlong param_2, void * param_3)

void * FUN_140040d10(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_140040d50 @ 140040d50  undefined FUN_140040d50(undefined8 * param_1)

void FUN_140040d50(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140040d80 @ 140040d80  undefined FUN_140040d80(undefined8 param_1, ulonglong param_2)

void FUN_140040d80(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x38)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 0x38);
  return;
}


// ==== FUN_140040df0 @ 140040df0  bool FUN_140040df0(longlong * param_1, longlong * param_2)

bool FUN_140040df0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_140040e90 @ 140040e90  undefined8 * FUN_140040e90(undefined8 * param_1)

undefined8 * FUN_140040e90(undefined8 *param_1)

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


// ==== FUN_140040f30 @ 140040f30  undefined8 * FUN_140040f30(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140040f30(undefined8 *param_1,undefined8 *param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_1400402d0(param_1,*param_2,param_2[1]);
  return param_1;
}


// ==== FUN_140040f60 @ 140040f60  undefined FUN_140040f60(longlong param_1)

void FUN_140040f60(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_1 + 8);
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
  return;
}


// ==== FUN_140040fa0 @ 140040fa0  undefined8 * FUN_140040fa0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140040fa0(undefined8 *param_1,undefined8 *param_2)

{
  FUN_1400402d0(param_1,*param_2,param_2[1]);
  return param_1;
}


// ==== FUN_140040fc0 @ 140040fc0  undefined FUN_140040fc0(longlong param_1)

void FUN_140040fc0(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_1 + 8);
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
  return;
}


// ==== FUN_140041000 @ 140041000  undefined8 * FUN_140041000(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140041000(undefined8 *param_1,undefined8 *param_2)

{
  FUN_140040460(param_1,*param_2,param_2[1]);
  return param_1;
}


// ==== FUN_140041020 @ 140041020  longlong * FUN_140041020(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_140041020(longlong *param_1,longlong *param_2,longlong param_3)

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
  uVar3 = param_3 * 0x10 + lVar2;
  if (uVar3 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar4 = *plVar1;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar3) goto LAB_14004108d;
  }
  _invalid_parameter_noinfo();
LAB_14004108d:
  *param_2 = (longlong)plVar1;
  param_2[1] = uVar3;
  return param_2;
}


// ==== FUN_1400410c0 @ 1400410c0  undefined FUN_1400410c0(undefined8 * param_1)

void FUN_1400410c0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_1400410e0 @ 1400410e0  undefined FUN_1400410e0(undefined8 * param_1)

void FUN_1400410e0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140041100 @ 140041100  undefined FUN_140041100(undefined8 * param_1)

void FUN_140041100(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140041120 @ 140041120  undefined8 FUN_140041120(longlong param_1, ulonglong param_2)

undefined8 FUN_140041120(longlong param_1,ulonglong param_2)

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
      FUN_14003ecb0();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_1400401e0(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    lVar3 = lVar3 + param_2 * 8;
    *(longlong *)(param_1 + 0x28) = lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
  }
  return uVar2;
}


// ==== FUN_140041190 @ 140041190  undefined FUN_140041190(longlong param_1)

void FUN_140041190(longlong param_1)

{
  if (*(void **)(param_1 + 0x18) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_1400411c0 @ 1400411c0  undefined8 FUN_1400411c0(longlong param_1, ulonglong param_2)

undefined8 FUN_1400411c0(longlong param_1,ulonglong param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  longlong lVar3;
  
  uVar2 = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  if (param_2 != 0) {
    if (0x492492492492492 < param_2) {
      FUN_14003ed30();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_140040260(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
    *(ulonglong *)(param_1 + 0x28) = param_2 * 0x38 + lVar3;
  }
  return uVar2;
}


// ==== FUN_140041230 @ 140041230  undefined FUN_140041230(undefined8 * param_1)

void FUN_140041230(undefined8 *param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = (longlong *)param_1[1];
  if (plVar3 == (longlong *)0x0) {
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
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
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
  param_1[1] = 0;
  *param_1 = 0;
  return;
}


// ==== FUN_1400412c0 @ 1400412c0  undefined8 FUN_1400412c0(longlong param_1, ulonglong param_2)

undefined8 FUN_1400412c0(longlong param_1,ulonglong param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  longlong lVar3;
  
  uVar2 = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  if (param_2 != 0) {
    if (0x3fffffffffffffff < param_2) {
      FUN_14003eda0();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_140040370(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    lVar3 = lVar3 + param_2 * 4;
    *(longlong *)(param_1 + 0x28) = lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
  }
  return uVar2;
}


// ==== FUN_140041330 @ 140041330  undefined FUN_140041330(longlong param_1)

void FUN_140041330(longlong param_1)

{
  if (*(void **)(param_1 + 0x18) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_140041360 @ 140041360  undefined8 FUN_140041360(longlong param_1, ulonglong param_2)

undefined8 FUN_140041360(longlong param_1,ulonglong param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  longlong lVar3;
  
  uVar2 = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  if (param_2 != 0) {
    if (0xfffffffffffffff < param_2) {
      FUN_14003ee20();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_1400403f0(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    *(ulonglong *)(param_1 + 0x28) = param_2 * 0x10 + lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
  }
  return uVar2;
}


// ==== FUN_1400413d0 @ 1400413d0  undefined FUN_1400413d0(undefined8 * param_1)

void FUN_1400413d0(undefined8 *param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = (longlong *)param_1[1];
  if (plVar3 == (longlong *)0x0) {
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
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
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
  param_1[1] = 0;
  *param_1 = 0;
  return;
}


// ==== FUN_140041460 @ 140041460  undefined8 * FUN_140041460(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140041460(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_1400414c0 @ 1400414c0  longlong * FUN_1400414c0(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_1400414c0(longlong *param_1,longlong *param_2,longlong param_3)

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
  uVar3 = param_3 * -0x10 + lVar2;
  if (uVar3 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar4 = *plVar1;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar3) goto LAB_140041530;
  }
  _invalid_parameter_noinfo();
LAB_140041530:
  *param_2 = (longlong)plVar1;
  param_2[1] = uVar3;
  return param_2;
}


// ==== FUN_140041580 @ 140041580  undefined8 * FUN_140041580(undefined8 * param_1)

undefined8 * FUN_140041580(undefined8 *param_1)

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


// ==== FUN_1400415c0 @ 1400415c0  undefined8 * FUN_1400415c0(undefined8 * param_1)

undefined8 * FUN_1400415c0(undefined8 *param_1)

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


// ==== FUN_140041600 @ 140041600  undefined8 * FUN_140041600(undefined8 * param_1)

undefined8 * FUN_140041600(undefined8 *param_1)

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


// ==== FUN_140041640 @ 140041640  longlong * FUN_140041640(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_140041640(longlong *param_1,longlong *param_2,longlong param_3)

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
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar1) goto LAB_1400416aa;
  }
  _invalid_parameter_noinfo();
LAB_1400416aa:
  *param_2 = (longlong)plVar2;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_1400416e0 @ 1400416e0  undefined8 * FUN_1400416e0(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_1400416e0(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_140041740 @ 140041740  undefined8 * FUN_140041740(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140041740(undefined8 *param_1,undefined8 *param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_140040460(param_1,*param_2,param_2[1]);
  return param_1;
}


// ==== FUN_140041770 @ 140041770  undefined8 * FUN_140041770(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140041770(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_1400417d0 @ 1400417d0  undefined8 * FUN_1400417d0(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_1400417d0(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_140041830 @ 140041830  undefined8 * FUN_140041830(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140041830(undefined8 *param_1,undefined8 *param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_1400402d0(param_1,*param_2,param_2[1]);
  return param_1;
}


// ==== FUN_140041860 @ 140041860  void * FUN_140041860(void * param_1, longlong param_2, void * param_3)

void * FUN_140041860(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_1400418a0 @ 1400418a0  void * FUN_1400418a0(undefined8 param_1, void * param_2, longlong param_3, void * param_4)

void * FUN_1400418a0(undefined8 param_1,void *param_2,longlong param_3,void *param_4)

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


// ==== FUN_1400418e0 @ 1400418e0  void * FUN_1400418e0(void * param_1, longlong param_2, void * param_3)

void * FUN_1400418e0(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_140041920 @ 140041920  void * FUN_140041920(undefined8 param_1, void * param_2, longlong param_3, void * param_4)

void * FUN_140041920(undefined8 param_1,void *param_2,longlong param_3,void *param_4)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_3 - (longlong)param_2 >> 2;
  _DstSize = lVar1 * 4;
  if (lVar1 != 0) {
    memmove_s(param_4,_DstSize,param_2,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_4);
}


// ==== FUN_140041990 @ 140041990  void * FUN_140041990(void * param_1, longlong param_2, longlong param_3)

void * FUN_140041990(void *param_1,longlong param_2,longlong param_3)

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


// ==== FUN_1400419d0 @ 1400419d0  undefined8 * FUN_1400419d0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_1400419d0(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_140041a20 @ 140041a20  undefined8 * FUN_140041a20(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140041a20(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_140041a70 @ 140041a70  undefined8 * FUN_140041a70(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140041a70(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_140041ac0 @ 140041ac0  undefined8 * FUN_140041ac0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140041ac0(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_140041b10 @ 140041b10  undefined8 * FUN_140041b10(undefined8 * param_1)

undefined8 * FUN_140041b10(undefined8 *param_1)

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


// ==== FUN_140041b60 @ 140041b60  undefined FUN_140041b60(undefined8 * param_1, undefined8 param_2)

void FUN_140041b60(undefined8 *param_1,undefined8 param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x18);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = std::tr1::_Ref_count_base::vftable;
    puVar1[1] = param_2;
    *(undefined4 *)(puVar1 + 2) = 0;
    *(undefined4 *)((longlong)puVar1 + 0x14) = 1;
    *puVar1 = std::tr1::_Ref_count<class_CNeuralAIStrategy>::vftable;
  }
  FUN_140040460(param_1,param_2,(longlong)puVar1);
  return;
}


// ==== FUN_140041be0 @ 140041be0  undefined FUN_140041be0(undefined8 * param_1, undefined8 param_2)

void FUN_140041be0(undefined8 *param_1,undefined8 param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x18);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = std::tr1::_Ref_count_base::vftable;
    puVar1[1] = param_2;
    *(undefined4 *)(puVar1 + 2) = 0;
    *(undefined4 *)((longlong)puVar1 + 0x14) = 1;
    *puVar1 = std::tr1::_Ref_count<class_CDefaultAIStrategy>::vftable;
  }
  FUN_1400402d0(param_1,param_2,(longlong)puVar1);
  return;
}


// ==== FUN_140041c70 @ 140041c70  undefined8 * FUN_140041c70(undefined8 * param_1, double * param_2, double * param_3, undefined8 * param_4)

undefined8 * FUN_140041c70(undefined8 *param_1,double *param_2,double *param_3,undefined8 *param_4)

{
  longlong lVar1;
  
  if (param_2 != param_3) {
    do {
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                ((basic_ostream<char,struct_std::char_traits<char>_> *)param_4[1],*param_2);
      if ((char *)*param_4 != (char *)0x0) {
        FUN_140040840((basic_ostream<char,struct_std::char_traits<char>_> *)param_4[1],
                      (char *)*param_4);
      }
      lVar1 = (longlong)*(int *)(*(longlong *)param_4[1] + 4) + (longlong)param_4[1];
      if ((*(byte *)(lVar1 + 0x10) & 6) != 0) {
        lVar1 = 0;
      }
      if (lVar1 == 0) {
        _invalid_parameter_noinfo();
      }
      param_2 = param_2 + 1;
    } while (param_2 != param_3);
  }
  *param_1 = *param_4;
  param_1[1] = param_4[1];
  return param_1;
}


// ==== FUN_140041d20 @ 140041d20  void * FUN_140041d20(void * param_1, longlong param_2, void * param_3)

void * FUN_140041d20(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_140041d60 @ 140041d60  undefined FUN_140041d60(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

void FUN_140041d60(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  longlong *plVar1;
  int *piVar2;
  longlong lVar3;
  undefined8 uVar4;
  longlong *plVar5;
  
  if (param_1 != param_2) {
    do {
      lVar3 = param_3[1];
      uVar4 = *param_3;
      if (lVar3 != 0) {
        LOCK();
        *(int *)(lVar3 + 0x10) = *(int *)(lVar3 + 0x10) + 1;
        UNLOCK();
      }
      plVar5 = (longlong *)param_1[1];
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
      param_1[1] = lVar3;
      *param_1 = uVar4;
      param_1 = param_1 + 2;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_140041e10 @ 140041e10  ulonglong FUN_140041e10(double * param_1, double * param_2, longlong * param_3)

ulonglong FUN_140041e10(double *param_1,double *param_2,longlong *param_3)

{
  longlong *plVar1;
  longlong lVar2;
  ulonglong uVar3;
  longlong lVar4;
  longlong lVar5;
  
  plVar1 = (longlong *)*param_3;
  lVar4 = 0;
  lVar2 = param_3[1];
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar4;
  }
  else {
    lVar5 = *plVar1;
  }
  uVar3 = lVar2 + ((longlong)param_2 - (longlong)param_1 >> 3) * 8;
  if (uVar3 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar4 = *plVar1;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar3) goto LAB_140041e8b;
  }
  _invalid_parameter_noinfo();
LAB_140041e8b:
  uVar3 = param_3[1];
  if (param_1 != param_2) {
    uVar3 = uVar3 - (longlong)param_1;
    do {
      if (*param_1 != *(double *)(uVar3 + (longlong)param_1)) {
        return uVar3 & 0xffffffffffffff00;
      }
      param_1 = param_1 + 1;
    } while (param_1 != param_2);
  }
  return CONCAT71((int7)(uVar3 >> 8),1);
}


// ==== FUN_140041f20 @ 140041f20  undefined FUN_140041f20(undefined8 * param_1, undefined8 * param_2)

void FUN_140041f20(undefined8 *param_1,undefined8 *param_2)

{
  if (param_1 != (undefined8 *)0x0) {
    *param_1 = 0;
    param_1[1] = 0;
    FUN_140040460(param_1,*param_2,param_2[1]);
  }
  return;
}


// ==== FUN_140041f60 @ 140041f60  void * FUN_140041f60(void * param_1, uint param_2)

void * FUN_140041f60(void *param_1,uint param_2)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)((longlong)param_1 + 8);
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
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_140041fd0 @ 140041fd0  undefined8 FUN_140041fd0(longlong param_1, ulonglong param_2)

undefined8 FUN_140041fd0(longlong param_1,ulonglong param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  longlong lVar3;
  
  uVar2 = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  if (param_2 != 0) {
    if (0x492492492492492 < param_2) {
      FUN_14003fa00();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_140040d80(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
    *(ulonglong *)(param_1 + 0x28) = param_2 * 0x38 + lVar3;
  }
  return uVar2;
}


// ==== FUN_140042040 @ 140042040  undefined8 * FUN_140042040(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140042040(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_1400420b0 @ 1400420b0  undefined8 * FUN_1400420b0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_1400420b0(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_140042100 @ 140042100  undefined8 * FUN_140042100(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140042100(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_140042150 @ 140042150  undefined8 * FUN_140042150(undefined8 * param_1)

undefined8 * FUN_140042150(undefined8 *param_1)

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


// ==== FUN_1400421e0 @ 1400421e0  void * FUN_1400421e0(longlong param_1, longlong param_2, void * param_3)

void * FUN_1400421e0(longlong param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = *(longlong *)(param_2 + 8) - (longlong)*(void **)(param_1 + 8) >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,*(void **)(param_1 + 8),_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_140042220 @ 140042220  undefined FUN_140042220(undefined8 * param_1)

void FUN_140042220(undefined8 *param_1)

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


// ==== FUN_140042260 @ 140042260  undefined8 * FUN_140042260(undefined8 * param_1)

undefined8 * FUN_140042260(undefined8 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_140041230(param_1);
  return param_1;
}


// ==== FUN_140042280 @ 140042280  undefined FUN_140042280(undefined8 * param_1)

void FUN_140042280(undefined8 *param_1)

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


// ==== FUN_1400422c0 @ 1400422c0  undefined8 * FUN_1400422c0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_1400422c0(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_140042310 @ 140042310  undefined8 * FUN_140042310(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140042310(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_140042360 @ 140042360  ulonglong FUN_140042360(longlong * param_1, ulonglong param_2)

ulonglong FUN_140042360(longlong *param_1,ulonglong param_2)

{
  longlong *plVar1;
  code *pcVar2;
  ulonglong uVar3;
  longlong lVar4;
  longlong lVar5;
  
  uVar3 = param_1[3];
  if ((ulonglong)((longlong)(param_1[4] - uVar3) >> 4) <= param_2) {
    FUN_14003eaf0();
    pcVar2 = (code *)swi(3);
    uVar3 = (*pcVar2)();
    return uVar3;
  }
  if ((ulonglong)param_1[4] < uVar3) {
    _invalid_parameter_noinfo();
  }
  plVar1 = (longlong *)*param_1;
  lVar5 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar4 = lVar5;
  }
  else {
    lVar4 = *plVar1;
  }
  uVar3 = uVar3 + param_2 * 0x10;
  if (uVar3 <= *(ulonglong *)(lVar4 + 0x20)) {
    lVar4 = lVar5;
    if (plVar1 != (longlong *)0x0) {
      lVar4 = *plVar1;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar3) goto LAB_1400423f5;
  }
  _invalid_parameter_noinfo();
LAB_1400423f5:
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  else {
    lVar5 = *plVar1;
  }
  if (*(ulonglong *)(lVar5 + 0x20) <= uVar3) {
    _invalid_parameter_noinfo();
  }
  return uVar3;
}


// ==== FUN_140042430 @ 140042430  ulonglong FUN_140042430(longlong * param_1)

ulonglong FUN_140042430(longlong *param_1)

{
  ulonglong uVar1;
  longlong lVar2;
  
  uVar1 = param_1[3];
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  if ((longlong *)*param_1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar2 = 0;
  }
  else {
    lVar2 = *(longlong *)*param_1;
  }
  if (*(ulonglong *)(lVar2 + 0x20) <= uVar1) {
    _invalid_parameter_noinfo();
  }
  return uVar1;
}


// ==== FUN_140042480 @ 140042480  ulonglong FUN_140042480(longlong * param_1)

ulonglong FUN_140042480(longlong *param_1)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  
  uVar1 = param_1[4];
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)*param_1;
  lVar4 = 0;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar3 = lVar4;
  }
  else {
    lVar3 = *plVar2;
  }
  uVar1 = uVar1 - 0x10;
  if (uVar1 <= *(ulonglong *)(lVar3 + 0x20)) {
    lVar3 = lVar4;
    if (plVar2 != (longlong *)0x0) {
      lVar3 = *plVar2;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar1) goto LAB_1400424f7;
  }
  _invalid_parameter_noinfo();
LAB_1400424f7:
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  else {
    lVar4 = *plVar2;
  }
  if (*(ulonglong *)(lVar4 + 0x20) <= uVar1) {
    _invalid_parameter_noinfo();
  }
  return uVar1;
}


// ==== FUN_140042530 @ 140042530  undefined8 * FUN_140042530(undefined8 * param_1)

undefined8 * FUN_140042530(undefined8 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_1400413d0(param_1);
  return param_1;
}


// ==== FUN_140042560 @ 140042560  undefined8 * FUN_140042560(undefined8 * param_1)

undefined8 * FUN_140042560(undefined8 *param_1)

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


// ==== FUN_1400425b0 @ 1400425b0  undefined8 * FUN_1400425b0(undefined8 * param_1)

undefined8 * FUN_1400425b0(undefined8 *param_1)

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


// ==== FUN_140042600 @ 140042600  undefined8 * FUN_140042600(undefined8 * param_1)

undefined8 * FUN_140042600(undefined8 *param_1)

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


// ==== FUN_140042650 @ 140042650  undefined8 * FUN_140042650(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140042650(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_1400426b0 @ 1400426b0  undefined8 * FUN_1400426b0(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_1400426b0(undefined8 *param_1,undefined8 *param_2,longlong param_3)

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


// ==== FUN_140042710 @ 140042710  undefined8 * FUN_140042710(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140042710(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_140042770 @ 140042770  undefined8 * FUN_140042770(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140042770(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_1400427d0 @ 1400427d0  undefined8 * FUN_1400427d0(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_1400427d0(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_140041b60(param_1,param_2);
  return param_1;
}


// ==== FUN_1400427f0 @ 1400427f0  undefined8 * FUN_1400427f0(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_1400427f0(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_140041be0(param_1,param_2);
  return param_1;
}


// ==== FUN_140042810 @ 140042810  undefined8 * FUN_140042810(undefined8 * param_1, longlong param_2, longlong param_3, undefined8 * param_4)

undefined8 *
FUN_140042810(undefined8 *param_1,longlong param_2,longlong param_3,undefined8 *param_4)

{
  char *pcVar1;
  double *pdVar2;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar3;
  double *pdVar4;
  
  pcVar1 = (char *)*param_4;
  pdVar2 = *(double **)(param_3 + 8);
  pdVar4 = *(double **)(param_2 + 8);
  this = (basic_ostream<char,struct_std::char_traits<char>_> *)param_4[1];
  if (pdVar4 != pdVar2) {
    do {
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,*pdVar4);
      if (pcVar1 != (char *)0x0) {
        FUN_140040840(this,pcVar1);
      }
      pbVar3 = this + *(int *)(*(longlong *)this + 4);
      if (((byte)(this + *(int *)(*(longlong *)this + 4))[0x10] & 6) != 0) {
        pbVar3 = (basic_ostream<char,struct_std::char_traits<char>_> *)0x0;
      }
      if (pbVar3 == (basic_ostream<char,struct_std::char_traits<char>_> *)0x0) {
        _invalid_parameter_noinfo();
      }
      pdVar4 = pdVar4 + 1;
    } while (pdVar4 != pdVar2);
  }
  *param_1 = pcVar1;
  param_1[1] = this;
  return param_1;
}


// ==== FUN_1400428e0 @ 1400428e0  void * FUN_1400428e0(undefined8 param_1, void * param_2, longlong param_3, void * param_4)

void * FUN_1400428e0(undefined8 param_1,void *param_2,longlong param_3,void *param_4)

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


// ==== FUN_140042930 @ 140042930  undefined FUN_140042930(longlong param_1, longlong param_2, longlong * param_3)

void FUN_140042930(longlong param_1,longlong param_2,longlong *param_3)

{
  longlong local_18;
  longlong local_10;
  
  local_18 = *param_3;
  local_10 = param_3[1];
  FUN_140041e10(*(double **)(param_1 + 8),*(double **)(param_2 + 8),&local_18);
  return;
}


// ==== FUN_1400429a0 @ 1400429a0  undefined FUN_1400429a0(undefined8 param_1, undefined8 * param_2, undefined8 * param_3)

void FUN_1400429a0(undefined8 param_1,undefined8 *param_2,undefined8 *param_3)

{
  if (param_2 != (undefined8 *)0x0) {
    *param_2 = 0;
    param_2[1] = 0;
    FUN_140040460(param_2,*param_3,param_3[1]);
  }
  return;
}


