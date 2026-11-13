// NpcServer.exe :: _unnamed  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== FUN_1400148f0 @ 1400148f0  undefined FUN_1400148f0(longlong param_1, longlong * param_2)

void FUN_1400148f0(longlong param_1,longlong *param_2)

{
  if (param_1 == 0) {
    param_1 = DAT_140103f80;
  }
  FUN_140014860(param_1,param_2);
  return;
}


// ==== FUN_140014900 @ 140014900  undefined8 * FUN_140014900(longlong * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

undefined8 *
FUN_140014900(longlong *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  longlong *plVar2;
  undefined8 *puVar3;
  
  if (param_1[0x53] != 0) {
    return (undefined8 *)0x0;
  }
  iVar1 = FUN_14000acb0((ulonglong *)(param_1 + 0x42),param_2,param_3,param_4);
  if (iVar1 == 0) {
    param_1[0x53] = (longlong)FUN_1400111c0;
    param_1[0x4b] = param_1[0x42];
    param_1[0x4c] = (longlong)param_1;
    *(undefined1 *)((longlong)param_1 + 0x233) = 2;
    *(undefined4 *)(param_1 + 0x49) = 0xffffffff;
    plVar2 = param_1;
    if (param_1 == (longlong *)&DAT_140103f88) {
      plVar2 = param_1 + 0x44;
    }
    param_1[0x47] = (longlong)FUN_140011a00;
    param_1[0x48] = (longlong)plVar2;
    *(undefined2 *)((longlong)param_1 + 0x28a) = 0;
    param_1[0x50] = 0;
    *(undefined4 *)((longlong)param_1 + 0x27c) = 0;
    *(undefined4 *)(param_1 + 0x4f) = 0;
    *(undefined2 *)(param_1 + 0x51) = 0x12;
    *(undefined2 *)(param_1 + 0x46) = 0x80;
    *(char *)((longlong)param_1 + 0x232) = (char)((int)param_1[0x20] / 2);
    *(ushort *)(param_1 + 0x46) = *(ushort *)(param_1 + 0x46) | 0x10;
    if (((*(byte *)(param_1 + 0x46) & 8) == 0) && (0 < *(int *)(param_1[0x4c] + 0x100))) {
      *(undefined1 *)((longlong)param_1 + 0x232) = 0;
    }
    puVar3 = FUN_140013f70(param_1 + 0x44,(ulonglong *)0x0,0);
    return puVar3;
  }
  return (undefined8 *)0xffffffff;
}


// ==== FUN_140014a00 @ 140014a00  undefined8 FUN_140014a00(longlong param_1, longlong * param_2, int param_3)

undefined8 FUN_140014a00(longlong param_1,longlong *param_2,int param_3)

{
  ushort uVar1;
  longlong lVar2;
  undefined8 uVar3;
  
  uVar3 = 0;
  if ((char)*(ushort *)(param_2 + 2) < '\0') {
    if ((*(ushort *)(param_2 + 2) & 0x10) != 0) goto LAB_140014ac9;
    if (*(longlong *)(param_2[8] + 0x1d0) != 0) {
      FUN_140016e30();
    }
    FUN_140012f60(param_2,3);
    lVar2 = *(longlong *)(param_2[8] + 0x1d0);
  }
  else {
    if (*(longlong *)(param_1 + 0x1d0) != 0) {
      FUN_140016e30();
    }
    uVar1 = *(ushort *)(param_2 + 2);
    if ((char)uVar1 < '\0') {
      FUN_140012f60(param_2,3);
    }
    else if ((uVar1 & 0x28) != 0) {
      if ((uVar1 & 0x28) == 8) {
        FUN_1400113e0(param_1,param_2);
      }
      else if ((uVar1 & 0x28) == 0x20) {
        FUN_140011460(param_1,param_2);
      }
    }
    lVar2 = *(longlong *)(param_1 + 0x1d0);
  }
  if (lVar2 != 0) {
    FUN_140016e50();
  }
  uVar3 = 1;
LAB_140014ac9:
  if ((param_3 != 0) && ((*(byte *)(param_2 + 2) & 0x40) != 0)) {
    if (*(char *)((longlong)param_2 + 0x13) == '\x04') {
      (*(code *)param_2[3])(param_2,param_2[4]);
    }
    else if ((byte)(*(char *)((longlong)param_2 + 0x13) - 5U) < 2) {
      (*(code *)param_2[3])(param_2,param_2[4]);
      if (*(char *)((longlong)param_2 + 0x13) == '\x06') {
        if (DAT_140103fa8 == (code *)0x0) {
          free(param_2);
        }
        else {
          (*DAT_140103fa8)();
        }
      }
    }
  }
  return uVar3;
}


// ==== FUN_140014b30 @ 140014b30  undefined FUN_140014b30(longlong * param_1, int param_2, undefined8 param_3, undefined8 param_4)

void FUN_140014b30(longlong *param_1,int param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 *_Memory;
  longlong *plVar1;
  longlong *plVar2;
  longlong lVar3;
  code *pcVar4;
  code *pcVar5;
  longlong *plVar6;
  uint uVar7;
  longlong *plVar8;
  longlong *plVar9;
  
  if ((param_1 == (longlong *)0x0) &&
     ((DAT_140103f80 == (longlong *)0x0 ||
      (param_1 = DAT_140103f80, DAT_140103f80 == (longlong *)0x0)))) {
    FUN_1400191c0("%s: no base to free","event_base_free_",param_3,param_4);
    return;
  }
  plVar9 = (longlong *)0x0;
  if ((undefined8 *)param_1[0x3e] != (undefined8 *)0x0) {
    FUN_140074d90((undefined8 *)param_1[0x3e],0xffffffff);
    param_1[0x3e] = 0;
  }
  if (param_1[0x42] != -1) {
    FUN_140014300(param_1 + 0x44);
    Ordinal_3(param_1[0x42]);
    if (param_1[0x43] != -1) {
      Ordinal_3();
    }
    param_1[0x42] = -1;
    param_1[0x43] = -1;
    *(ushort *)(param_1 + 0x46) = *(ushort *)(param_1 + 0x46) & 0xff7f;
  }
  FUN_14001acc0((longlong)param_1);
  while (((int)param_1[0x2b] != 0 && (*(longlong **)param_1[0x2a] != (longlong *)0x0))) {
    FUN_140014300(*(longlong **)param_1[0x2a]);
  }
  pcVar5 = DAT_140103fa8;
  plVar6 = plVar9;
  plVar8 = plVar9;
  if (0 < (int)param_1[0x24]) {
    do {
      _Memory = *(undefined8 **)(param_1[0x23] + (longlong)plVar6);
      FUN_140014300(_Memory + 3);
      *(ushort *)(_Memory + 5) = *(ushort *)(_Memory + 5) & 0xff7f;
      plVar1 = (longlong *)*_Memory;
      pcVar5 = DAT_140103fa8;
      while (plVar2 = plVar1, DAT_140103fa8 = pcVar5, plVar2 != (longlong *)0x0) {
        plVar1 = (longlong *)plVar2[5];
        if ((*(byte *)(plVar2 + 2) & 0x10) == 0) {
          FUN_140014300(plVar2);
          pcVar5 = DAT_140103fa8;
        }
      }
      if (pcVar5 == (code *)0x0) {
        free(_Memory);
      }
      else {
        (*pcVar5)(_Memory);
        pcVar5 = DAT_140103fa8;
      }
      uVar7 = (int)plVar8 + 1;
      plVar6 = plVar6 + 1;
      plVar8 = (longlong *)(ulonglong)uVar7;
    } while ((int)uVar7 < (int)param_1[0x24]);
  }
  if ((void *)param_1[0x23] != (void *)0x0) {
    if (pcVar5 == (code *)0x0) {
      free((void *)param_1[0x23]);
    }
    else {
      (*pcVar5)();
      pcVar5 = DAT_140103fa8;
    }
  }
  plVar6 = plVar9;
  plVar8 = plVar9;
  if (0 < (int)param_1[0x20]) {
    do {
      plVar1 = *(longlong **)(param_1[0x1f] + (longlong)plVar6);
      pcVar5 = DAT_140103fa8;
      while (DAT_140103fa8 = pcVar5, plVar1 != (longlong *)0x0) {
        plVar2 = (longlong *)*plVar1;
        FUN_140014a00((longlong)param_1,plVar1,param_2);
        plVar1 = plVar2;
        pcVar5 = DAT_140103fa8;
      }
      uVar7 = (int)plVar8 + 1;
      plVar6 = plVar6 + 2;
      plVar8 = (longlong *)(ulonglong)uVar7;
    } while ((int)uVar7 < (int)param_1[0x20]);
  }
  plVar6 = (longlong *)param_1[0x21];
  while (plVar6 != (longlong *)0x0) {
    FUN_140014a00((longlong)param_1,plVar6,param_2);
    pcVar5 = DAT_140103fa8;
    plVar6 = (longlong *)param_1[0x21];
  }
  lVar3 = param_1[0x55];
  while (lVar3 != 0) {
    plVar6 = (longlong *)param_1[0x55];
    if (*plVar6 != 0) {
      *(longlong *)(*plVar6 + 8) = plVar6[1];
    }
    *(longlong *)plVar6[1] = *plVar6;
    if (pcVar5 == (code *)0x0) {
      free(plVar6);
      pcVar5 = (code *)0x0;
    }
    else {
      (*pcVar5)();
      pcVar5 = DAT_140103fa8;
    }
    lVar3 = param_1[0x55];
  }
  if ((*param_1 != 0) && (pcVar4 = *(code **)(*param_1 + 0x28), pcVar4 != (code *)0x0)) {
    (*pcVar4)(param_1);
    pcVar5 = DAT_140103fa8;
  }
  if ((void *)param_1[0x2a] != (void *)0x0) {
    if (pcVar5 == (code *)0x0) {
      free((void *)param_1[0x2a]);
    }
    else {
      (*pcVar5)();
      pcVar5 = DAT_140103fa8;
    }
  }
  if (pcVar5 == (code *)0x0) {
    free((void *)param_1[0x1f]);
  }
  else {
    (*pcVar5)();
  }
  FUN_14001a030(param_1 + 0x25);
  FUN_14001a1a0(param_1 + 0x28);
  FUN_14001af30(param_1 + 2);
  if (param_1[0x3a] != 0) {
    FUN_140016e10();
  }
  if (param_1[0x3b] != 0) {
    FUN_140016e90();
  }
  if (param_1 == DAT_140103f80) {
    DAT_140103f80 = plVar9;
  }
  if (DAT_140103fa8 == (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000140014e8c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    free(param_1);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000140014e7f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_140103fa8)(param_1);
  return;
}


// ==== FUN_140014eb0 @ 140014eb0  undefined FUN_140014eb0(longlong * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_140014eb0(longlong *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  FUN_140014b30(param_1,1,param_3,param_4);
  return;
}


// ==== FUN_140014ec0 @ 140014ec0  ulonglong FUN_140014ec0(longlong * param_1, undefined8 param_2, longlong * param_3, undefined8 param_4)

ulonglong FUN_140014ec0(longlong *param_1,undefined8 param_2,longlong *param_3,undefined8 param_4)

{
  longlong *plVar1;
  bool bVar2;
  int iVar3;
  undefined8 uVar4;
  longlong lVar5;
  longlong lVar6;
  longlong lVar7;
  undefined8 *puVar8;
  longlong *plVar9;
  ulonglong uVar10;
  longlong *plVar11;
  
  plVar9 = (longlong *)param_1[0x3a];
  uVar10 = 0;
  bVar2 = false;
  if (plVar9 != (longlong *)0x0) {
    FUN_140016e30();
  }
  lVar7 = *param_1;
  if (*(int *)(lVar7 + 0x30) != 0) {
    *param_1 = (longlong)&PTR_DAT_1400c0d30;
  }
  if ((int)param_1[0x16] != 0) {
    plVar11 = param_1 + 5;
    if (param_1[0xd] != 0) {
      if (*(longlong *)(param_1[0xd] + 0x1d0) != 0) {
        FUN_140016ef0();
      }
      if ((*(byte *)(param_1 + 7) & 0x40) == 0) {
        plVar9 = (longlong *)param_1[0xd];
        if ((longlong *)plVar9[0x3d] == plVar11) {
          uVar4 = FUN_140016dd0();
          if ((((int)plVar9[0x39] != (int)uVar4) && ((*(byte *)(param_1 + 0x12) & 0x40) == 0)) &&
             (*(int *)(plVar9 + 0x3c) = (int)plVar9[0x3c] + 1, plVar9[0x3b] != 0)) {
            FUN_140016ed0();
          }
        }
        if ((((*(byte *)(param_1 + 0x12) & 8) != 0) && ((short)param_1[0x10] != 0)) &&
           ((undefined2 *)param_1[0x11] != (undefined2 *)0x0)) {
          *(undefined2 *)param_1[0x11] = 0;
        }
        if ((*(byte *)(param_1 + 7) & 1) != 0) {
          FUN_140012cc0((longlong)plVar9,(longlong)plVar11);
        }
        if ((*(ushort *)(param_1 + 7) & 8) == 0) {
          if ((*(ushort *)(param_1 + 7) & 0x20) != 0) {
            FUN_140011460((longlong)plVar9,plVar11);
          }
        }
        else {
          FUN_1400113e0((longlong)plVar9,plVar11);
        }
        if ((*(byte *)(param_1 + 7) & 2) != 0) {
          if (plVar9[0x3a] != 0) {
            FUN_140016ef0();
          }
          *(uint *)(plVar9 + 0x1a) = (int)plVar9[0x1a] - (~((int)(short)param_1[7] >> 4) & 1U);
          *(ushort *)(param_1 + 7) = *(ushort *)(param_1 + 7) & 0xfffd;
          if ((*(byte *)(param_1 + 0x12) & 0x86) == 0) {
            uVar4 = FUN_14001a790((longlong)plVar9,(int)param_1[0xc],(longlong)plVar11);
            iVar3 = (int)uVar4;
          }
          else {
            lVar5 = FUN_14001a460(plVar9,param_1[0xc],(longlong)plVar11);
            iVar3 = (int)lVar5;
          }
          if ((iVar3 == 1) && ((int)plVar9[0x1e] != 0)) {
            uVar4 = FUN_140016dd0();
            if ((int)plVar9[0x39] != (int)uVar4) {
              FUN_140011210((longlong)plVar9);
            }
          }
        }
      }
    }
    *(ushort *)(param_1 + 7) = *(ushort *)(param_1 + 7) & 0xff7f;
    plVar9 = (longlong *)0x0;
    param_3 = (longlong *)0x78;
    memset(plVar11,0,0x78);
    if (param_1[0x14] != -1) {
      Ordinal_3();
    }
    if (param_1[0x15] != -1) {
      Ordinal_3();
    }
    bVar2 = true;
    *(undefined4 *)(param_1 + 0x16) = 0;
  }
  lVar5 = param_1[0x53];
  if (lVar5 != 0) {
    param_1[0x53] = 0;
  }
  if (param_1[0x42] != -1) {
    plVar11 = param_1 + 0x44;
    if (param_1[0x4c] != 0) {
      if (*(longlong *)(param_1[0x4c] + 0x1d0) != 0) {
        FUN_140016ef0();
      }
      if ((*(byte *)(param_1 + 0x46) & 0x40) == 0) {
        plVar1 = (longlong *)param_1[0x4c];
        if ((longlong *)plVar1[0x3d] == plVar11) {
          uVar4 = FUN_140016dd0();
          if ((((int)plVar1[0x39] != (int)uVar4) && ((*(byte *)(param_1 + 0x51) & 0x40) == 0)) &&
             (*(int *)(plVar1 + 0x3c) = (int)plVar1[0x3c] + 1, plVar1[0x3b] != 0)) {
            plVar9 = (longlong *)plVar1[0x3a];
            param_3 = (longlong *)0x0;
            FUN_140016ed0();
          }
        }
        if ((((*(byte *)(param_1 + 0x51) & 8) != 0) && ((short)param_1[0x4f] != 0)) &&
           ((undefined2 *)param_1[0x50] != (undefined2 *)0x0)) {
          *(undefined2 *)param_1[0x50] = 0;
        }
        if ((*(byte *)(param_1 + 0x46) & 1) != 0) {
          plVar9 = plVar11;
          FUN_140012cc0((longlong)plVar1,(longlong)plVar11);
        }
        if ((*(ushort *)(param_1 + 0x46) & 8) == 0) {
          if ((*(ushort *)(param_1 + 0x46) & 0x20) != 0) {
            plVar9 = plVar11;
            FUN_140011460((longlong)plVar1,plVar11);
          }
        }
        else {
          plVar9 = plVar11;
          FUN_1400113e0((longlong)plVar1,plVar11);
        }
        if ((*(byte *)(param_1 + 0x46) & 2) != 0) {
          if (plVar1[0x3a] != 0) {
            FUN_140016ef0();
          }
          *(uint *)(plVar1 + 0x1a) = (int)plVar1[0x1a] - (~((int)(short)param_1[0x46] >> 4) & 1U);
          *(ushort *)(param_1 + 0x46) = *(ushort *)(param_1 + 0x46) & 0xfffd;
          if ((*(byte *)(param_1 + 0x51) & 0x86) == 0) {
            plVar9 = (longlong *)(ulonglong)*(uint *)(param_1 + 0x4b);
            uVar4 = FUN_14001a790((longlong)plVar1,*(uint *)(param_1 + 0x4b),(longlong)plVar11);
            iVar3 = (int)uVar4;
            param_3 = plVar11;
          }
          else {
            plVar9 = (longlong *)param_1[0x4b];
            lVar6 = FUN_14001a460(plVar1,(longlong)plVar9,(longlong)plVar11);
            iVar3 = (int)lVar6;
            param_3 = plVar11;
          }
          if ((iVar3 == 1) && ((int)plVar1[0x1e] != 0)) {
            uVar4 = FUN_140016dd0();
            if ((int)plVar1[0x39] != (int)uVar4) {
              FUN_140011210((longlong)plVar1);
            }
          }
        }
      }
    }
    Ordinal_3(param_1[0x42]);
    if (param_1[0x43] != -1) {
      Ordinal_3();
    }
    param_1[0x42] = -1;
    param_1[0x43] = -1;
    *(ushort *)(param_1 + 0x46) = *(ushort *)(param_1 + 0x46) & 0xff7f;
  }
  *param_1 = lVar7;
  if (*(int *)(lVar7 + 0x30) == 0) {
    if (bVar2) {
      uVar10 = FUN_14001b590((longlong)param_1,plVar9,param_3,param_4);
      uVar10 = uVar10 & 0xffffffff;
    }
  }
  else {
    if (*(code **)(lVar7 + 0x28) != (code *)0x0) {
      (**(code **)(lVar7 + 0x28))(param_1);
    }
    lVar7 = (**(code **)(lVar7 + 8))(param_1);
    param_1[1] = lVar7;
    if (lVar7 == 0) {
      FUN_140019160(1,"%s: could not reinitialize event mechanism","event_reinit",param_4);
      uVar10 = 0xffffffff;
      goto LAB_1400152ae;
    }
    FUN_14001af30(param_1 + 2);
    iVar3 = FUN_14001ab60((longlong)param_1);
    if (iVar3 < 0) {
      uVar10 = 0xffffffff;
    }
  }
  if ((lVar5 != 0) && ((int)uVar10 == 0)) {
    puVar8 = FUN_140014900(param_1,plVar9,param_3,param_4);
    uVar10 = (ulonglong)puVar8 & 0xffffffff;
  }
LAB_1400152ae:
  if (param_1[0x3a] != 0) {
    FUN_140016e50();
  }
  return uVar10;
}


// ==== FUN_1400152e0 @ 1400152e0  undefined FUN_1400152e0(longlong param_1, longlong * param_2)

void FUN_1400152e0(longlong param_1,longlong *param_2)

{
  undefined2 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  longlong lVar2;
  longlong lVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  undefined8 local_res8;
  ulonglong local_res10;
  int local_res18;
  int iStackX_1c;
  
  if (((int)param_2[0xb] != 0) || (*(int *)((longlong)param_2 + 0x5c) != 0)) {
    uVar6 = 0;
    FUN_1400105b0(param_1,&local_res18);
    local_res8 = CONCAT44(iStackX_1c,local_res18);
    if (((*(uint *)(param_2 + 0xe) & 0xf0000000) == 0x50000000) &&
       ((int)((int)*(uint *)(param_2 + 0xe) >> 0x14 & 0xffU) < *(int *)(param_1 + 0x120))) {
      uVar6 = (uint)((ulonglong)param_2[0xb] >> 0x20) & 0xfff00000;
      local_res10 = param_2[0xb] & 0xfffffffffffff;
      if ((*(byte *)((longlong)param_2 + 0x6a) & 1) != 0) {
        local_res8 = *(ulonglong *)((longlong)param_2 + 0x6c) & 0xfffffffffffff;
      }
    }
    else {
      local_res10 = param_2[0xb];
      if ((*(byte *)((longlong)param_2 + 0x6a) & 1) != 0) {
        local_res8 = *(ulonglong *)((longlong)param_2 + 0x6c);
        uVar6 = 0;
      }
    }
    iVar7 = (int)local_res10 + (int)local_res8;
    iVar8 = (int)(local_res10 >> 0x20);
    uVar5 = (int)(local_res8 >> 0x20) + iVar8;
    if (999999 < (int)uVar5) {
      iVar7 = iVar7 + 1;
      uVar5 = uVar5 - 1000000;
    }
    bVar9 = SBORROW4(iVar7,local_res18);
    iVar4 = iVar7 - local_res18;
    if (iVar7 == local_res18) {
      bVar9 = SBORROW4(uVar5,iStackX_1c);
      iVar4 = uVar5 - iStackX_1c;
    }
    if (bVar9 != iVar4 < 0) {
      uVar5 = iVar8 + iStackX_1c;
      iVar7 = local_res18 + (int)local_res10;
      if (999999 < (int)uVar5) {
        iVar7 = iVar7 + 1;
        uVar5 = uVar5 - 1000000;
      }
    }
    local_res8 = CONCAT44(uVar5 | uVar6,iVar7);
    FUN_140013f70(param_2,&local_res8,1);
  }
  UNRECOVERED_JUMPTABLE = (code *)param_2[3];
  lVar2 = param_2[7];
  uVar1 = *(undefined2 *)((longlong)param_2 + 0x6a);
  lVar3 = param_2[4];
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
                    /* WARNING: Could not recover jumptable at 0x00014001545b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(lVar2,uVar1,lVar3);
  return;
}


// ==== FUN_140015460 @ 140015460  int FUN_140015460(longlong param_1, undefined8 * param_2, int param_3, int * param_4)

int FUN_140015460(longlong param_1,undefined8 *param_2,int param_3,int *param_4)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  code *pcVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar8;
  longlong *_Memory;
  int iVar9;
  bool bVar10;
  int local_res10;
  int iStackX_14;
  longlong lVar7;
  
  plVar2 = (longlong *)*param_2;
  iVar9 = 0;
  do {
    if (plVar2 == (longlong *)0x0) {
      return iVar9;
    }
    _Memory = (longlong *)0x0;
    if ((((char)*(ushort *)(plVar2 + 2) < '\0') &&
        (_Memory = plVar2, (*(byte *)(plVar2 + 0xd) & 0x10) == 0)) &&
       ((*(ushort *)(plVar2 + 2) & 0x40) == 0)) {
      if (plVar2[8] != 0) {
        if (*(longlong *)(plVar2[8] + 0x1d0) != 0) {
          FUN_140016ef0();
        }
        if ((*(byte *)(plVar2 + 2) & 0x40) == 0) {
          plVar3 = (longlong *)plVar2[8];
          if ((((*(byte *)(plVar2 + 0xd) & 8) != 0) && ((short)plVar2[0xb] != 0)) &&
             ((undefined2 *)plVar2[0xc] != (undefined2 *)0x0)) {
            *(undefined2 *)plVar2[0xc] = 0;
          }
          if ((*(byte *)(plVar2 + 2) & 1) != 0) {
            FUN_140012cc0((longlong)plVar3,(longlong)plVar2);
          }
          if ((*(ushort *)(plVar2 + 2) & 8) == 0) {
            if ((*(ushort *)(plVar2 + 2) & 0x20) != 0) {
              FUN_140011460((longlong)plVar3,plVar2);
            }
          }
          else {
            FUN_1400113e0((longlong)plVar3,plVar2);
          }
          if ((*(byte *)(plVar2 + 2) & 2) != 0) {
            if (plVar3[0x3a] != 0) {
              FUN_140016ef0();
            }
            *(uint *)(plVar3 + 0x1a) = (int)plVar3[0x1a] - (~((int)(short)plVar2[2] >> 4) & 1U);
            *(ushort *)(plVar2 + 2) = *(ushort *)(plVar2 + 2) & 0xfffd;
            if ((*(byte *)(plVar2 + 0xd) & 0x86) == 0) {
              uVar8 = FUN_14001a790((longlong)plVar3,(int)plVar2[7],(longlong)plVar2);
              iVar6 = (int)uVar8;
            }
            else {
              lVar7 = FUN_14001a460(plVar3,plVar2[7],(longlong)plVar2);
              iVar6 = (int)lVar7;
            }
            if (((iVar6 == 1) && ((int)plVar3[0x1e] != 0)) &&
               (uVar8 = FUN_140016dd0(), (int)plVar3[0x39] != (int)uVar8)) {
              FUN_140011210((longlong)plVar3);
            }
          }
        }
      }
    }
    else {
      if (*(longlong *)(param_1 + 0x1d0) != 0) {
        FUN_140016ef0();
      }
      *(int *)(param_1 + 0xd0) = *(int *)(param_1 + 0xd0) - (~((int)(short)plVar2[2] >> 4) & 1U);
      *(ushort *)(plVar2 + 2) = *(ushort *)(plVar2 + 2) & 0xfff7;
      *(int *)(param_1 + 0xd8) = *(int *)(param_1 + 0xd8) + -1;
      if (*plVar2 == 0) {
        *(longlong *)
         (*(longlong *)(param_1 + 0xf8) + 8 + (ulonglong)*(byte *)((longlong)plVar2 + 0x12) * 0x10)
             = plVar2[1];
        *(longlong *)plVar2[1] = *plVar2;
      }
      else {
        *(longlong *)(*plVar2 + 8) = plVar2[1];
        *(longlong *)plVar2[1] = *plVar2;
      }
    }
    if ((*(byte *)(plVar2 + 2) & 0x10) == 0) {
      iVar9 = iVar9 + 1;
    }
    *(longlong **)(param_1 + 0x1e8) = plVar2;
    *(undefined4 *)(param_1 + 0x1e0) = 0;
    cVar1 = *(char *)((longlong)plVar2 + 0x13);
    switch(cVar1) {
    case '\0':
      pcVar4 = (code *)_Memory[3];
      if (*(longlong *)(param_1 + 0x1d0) != 0) {
        FUN_140016e50();
      }
      (*pcVar4)(_Memory[7],*(undefined2 *)((longlong)_Memory + 0x6a),_Memory[4]);
      break;
    case '\x01':
      FUN_140010c20(param_1,(longlong)_Memory);
      break;
    case '\x02':
      FUN_1400152e0(param_1,_Memory);
      break;
    case '\x03':
      lVar7 = *(longlong *)(param_1 + 0x1d0);
      pcVar4 = (code *)plVar2[3];
      goto joined_r0x000140015710;
    case '\x04':
      lVar7 = *(longlong *)(param_1 + 0x1d0);
      pcVar4 = (code *)plVar2[3];
      *(undefined8 *)(param_1 + 0x1e8) = 0;
joined_r0x000140015710:
      if (lVar7 != 0) {
        FUN_140016e50();
      }
      (*pcVar4)(plVar2,plVar2[4]);
      break;
    case '\x05':
    case '\x06':
      *(undefined8 *)(param_1 + 0x1e8) = 0;
      pcVar4 = (code *)_Memory[3];
      if (*(longlong *)(param_1 + 0x1d0) != 0) {
        FUN_140016e50();
      }
      (*pcVar4)(_Memory,_Memory[4]);
      if (cVar1 == '\x06') {
        if (DAT_140103fa8 == (code *)0x0) {
          free(_Memory);
        }
        else {
          (*DAT_140103fa8)();
        }
      }
    }
    if (*(longlong *)(param_1 + 0x1d0) != 0) {
      FUN_140016e30();
    }
    *(undefined8 *)(param_1 + 0x1e8) = 0;
    if ((*(int *)(param_1 + 0x1e0) != 0) &&
       (*(undefined4 *)(param_1 + 0x1e0) = 0, *(longlong *)(param_1 + 0x1d8) != 0)) {
      FUN_140016eb0();
    }
    if (*(int *)(param_1 + 0xe4) != 0) {
      return -1;
    }
    if (param_3 <= iVar9) {
      return iVar9;
    }
    if ((iVar9 != 0) && (param_4 != (int *)0x0)) {
      *(int *)(param_1 + 0x160) = 0;
      if ((*(byte *)(param_1 + 0x1f8) & 8) == 0) {
        FUN_1400105b0(param_1,(int *)(param_1 + 0x160));
      }
      FUN_1400105b0(param_1,&local_res10);
      iVar6 = *param_4;
      bVar10 = SBORROW4(local_res10,iVar6);
      iVar5 = local_res10 - iVar6;
      if (local_res10 == iVar6) {
        bVar10 = SBORROW4(iStackX_14,param_4[1]);
        iVar5 = iStackX_14 - param_4[1];
      }
      if (bVar10 == iVar5 < 0) {
        return iVar9;
      }
    }
    if (*(int *)(param_1 + 0xe8) != 0) {
      return iVar9;
    }
    plVar2 = (longlong *)*param_2;
  } while( true );
}


// ==== FUN_140015820 @ 140015820  int * FUN_140015820(longlong param_1)

int * FUN_140015820(longlong param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int iVar8;
  int *piVar9;
  int *piVar10;
  int local_res8;
  int local_resc;
  
  iVar1 = *(int *)(param_1 + 0x204);
  iVar2 = *(int *)(param_1 + 0x208);
  piVar4 = (int *)0x0;
  piVar10 = piVar4;
  if (-1 < *(int *)(param_1 + 0x1fc)) {
    *(int *)(param_1 + 0x160) = 0;
    if ((*(byte *)(param_1 + 0x1f8) & 8) == 0) {
      FUN_1400105b0(param_1,(int *)(param_1 + 0x160));
    }
    FUN_1400105b0(param_1,&local_res8);
    local_resc = local_resc + *(int *)(param_1 + 0x200);
    local_res8 = local_res8 + *(int *)(param_1 + 0x1fc);
    if (999999 < local_resc) {
      local_res8 = local_res8 + 1;
      local_resc = local_resc + -1000000;
    }
    piVar10 = &local_res8;
  }
  piVar6 = piVar4;
  piVar7 = piVar4;
  piVar9 = piVar4;
  if (0 < *(int *)(param_1 + 0x100)) {
    do {
      iVar5 = (int)piVar6;
      if (*(longlong *)(*(longlong *)(param_1 + 0xf8) + (longlong)piVar4) != 0) {
        *(int *)(param_1 + 0xec) = iVar5;
        piVar6 = piVar10;
        iVar8 = iVar1;
        if ((longlong)piVar9 < (longlong)iVar2) {
          piVar6 = (int *)0x0;
          iVar8 = 0x7fffffff;
        }
        uVar3 = FUN_140015460(param_1,(undefined8 *)
                                      ((longlong)iVar5 * 0x10 + *(longlong *)(param_1 + 0xf8)),iVar8
                              ,piVar6);
        piVar7 = (int *)(ulonglong)uVar3;
        if (uVar3 != 0) break;
      }
      piVar4 = piVar4 + 4;
      piVar6 = (int *)(ulonglong)(iVar5 + 1U);
      piVar9 = (int *)((longlong)piVar9 + 1);
    } while ((int)(iVar5 + 1U) < *(int *)(param_1 + 0x100));
  }
  *(undefined4 *)(param_1 + 0xec) = 0xffffffff;
  return piVar7;
}


// ==== FUN_140015950 @ 140015950  undefined4 FUN_140015950(longlong * param_1, uint param_2, undefined8 param_3, undefined8 param_4)

undefined4 FUN_140015950(longlong *param_1,uint param_2,undefined8 param_3,undefined8 param_4)

{
  longlong lVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined8 uVar4;
  int *piVar5;
  undefined4 uVar6;
  undefined4 *local_res8;
  undefined4 local_res18;
  undefined4 local_res1c;
  
  lVar1 = *param_1;
  uVar6 = 0;
  if (param_1[0x3a] != 0) {
    FUN_140016e30();
  }
  if ((int)param_1[0x1e] != 0) {
    FUN_1400191c0("%s: reentrant invocation.  Only one event_base_loop can run on each event_base at once."
                  ,"event_base_loop",param_3,param_4);
    if (param_1[0x3a] != 0) {
      FUN_140016e50();
    }
    return 0xffffffff;
  }
  *(undefined4 *)(param_1 + 0x1e) = 1;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  if (((int)param_1[0x16] != 0) && (*(int *)((longlong)param_1 + 0xb4) != 0)) {
    FUN_14001b3f0((longlong)param_1);
  }
  uVar4 = FUN_140016dd0();
  *(undefined4 *)((longlong)param_1 + 0xe4) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(int *)(param_1 + 0x39) = (int)uVar4;
  do {
    while( true ) {
      *(undefined4 *)(param_1 + 0x1d) = 0;
      *(undefined4 *)((longlong)param_1 + 0xf4) = 0;
      if (((int)param_1[0x1c] != 0) || (*(int *)((longlong)param_1 + 0xe4) != 0))
      goto LAB_140015b20;
      local_res8 = &local_res18;
      if (((int)param_1[0x1b] == 0) && ((param_2 & 2) == 0)) {
        FUN_1400112d0((longlong)param_1,&local_res8);
      }
      else {
        local_res1c = 0;
        local_res18 = 0;
      }
      puVar2 = local_res8;
      if ((((param_2 & 4) == 0) && (uVar4 = FUN_140010c00((longlong)param_1), (int)uVar4 == 0)) &&
         ((int)param_1[0x1b] == 0)) {
        uVar6 = 1;
        goto LAB_140015b20;
      }
      FUN_140011730((longlong)param_1);
      *(undefined4 *)(param_1 + 0x2c) = 0;
      iVar3 = (**(code **)(lVar1 + 0x20))(param_1,puVar2);
      if (iVar3 == -1) {
        uVar6 = 0xffffffff;
        goto LAB_140015b20;
      }
      *(undefined4 *)(param_1 + 0x2c) = 0;
      if ((*(byte *)(param_1 + 0x3f) & 8) == 0) {
        FUN_1400105b0((longlong)param_1,(int *)(param_1 + 0x2c));
      }
      FUN_140013300((longlong)param_1);
      if ((int)param_1[0x1b] == 0) break;
      piVar5 = FUN_140015820((longlong)param_1);
      if ((((param_2 & 1) != 0) && ((int)param_1[0x1b] == 0)) && ((int)piVar5 != 0))
      goto LAB_140015b20;
    }
  } while ((param_2 & 2) == 0);
LAB_140015b20:
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x1e) = 0;
  if (param_1[0x3a] != 0) {
    FUN_140016e50();
  }
  return uVar6;
}


// ==== FUN_140015b60 @ 140015b60  ulonglong FUN_140015b60(longlong param_1, undefined8 param_2, ushort param_3, longlong param_4, longlong param_5, ulonglong * param_6)

ulonglong FUN_140015b60(longlong param_1,undefined8 param_2,ushort param_3,longlong param_4,
                       longlong param_5,ulonglong *param_6)

{
  bool bVar1;
  longlong *_Dst;
  longlong *plVar2;
  int *piVar3;
  undefined8 *puVar4;
  longlong lVar5;
  
  bVar1 = false;
  if ((param_3 & 0x18) != 0) {
    return 0xffffffff;
  }
  if (DAT_140103f98 == (code *)0x0) {
    _Dst = (longlong *)calloc(1,0x98);
    if (_Dst == (longlong *)0x0) goto LAB_140015cad;
  }
  else {
    _Dst = (longlong *)(*DAT_140103f98)(0x98);
    if (_Dst == (longlong *)0x0) {
LAB_140015cad:
      piVar3 = _errno();
      *piVar3 = 0xc;
      return 0xffffffff;
    }
    memset(_Dst,0,0x98);
  }
  if (_Dst == (longlong *)0x0) {
    return 0xffffffff;
  }
  _Dst[0x11] = param_4;
  _Dst[0x12] = param_5;
  if (((byte)param_3 & 0x8f) == 1) {
    lVar5 = param_1;
    if (param_1 == 0) {
      lVar5 = DAT_140103f80;
    }
    plVar2 = _Dst;
    if (_Dst == (longlong *)&DAT_140103f88) {
      plVar2 = _Dst + 2;
    }
    _Dst[9] = -1;
    *(undefined2 *)(_Dst + 0xf) = 0;
    _Dst[6] = (longlong)plVar2;
    _Dst[10] = lVar5;
    _Dst[5] = (longlong)FUN_140012a10;
    *(undefined2 *)((longlong)_Dst + 0x7a) = 0;
    *(undefined2 *)(_Dst + 0xd) = 0;
    *(undefined2 *)(_Dst + 4) = 0x80;
    _Dst[0xe] = 0;
    *(undefined1 *)((longlong)_Dst + 0x23) = 0;
    *(undefined4 *)(_Dst + 7) = 0xffffffff;
    if (lVar5 != 0) {
      *(char *)((longlong)_Dst + 0x22) = (char)(*(int *)(lVar5 + 0x100) / 2);
    }
    if ((param_6 == (ulonglong *)0x0) ||
       (((int)*param_6 == 0 && (*(int *)((longlong)param_6 + 4) == 0)))) {
      bVar1 = true;
    }
  }
  else {
    if ((param_3 & 0x86) == 0) {
      if (DAT_140103fa8 != (code *)0x0) {
        (*DAT_140103fa8)(_Dst);
        return 0xffffffff;
      }
      free(_Dst);
      return 0xffffffff;
    }
    FUN_140010e40((undefined *)(_Dst + 2),param_1,param_2,(ulonglong)(param_3 & 0x86),FUN_140012a10,
                  (undefined *)_Dst);
  }
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  if (bVar1) {
    FUN_1400130f0(_Dst + 2,1,1);
  }
  else {
    puVar4 = FUN_140013f70(_Dst + 2,param_6,0);
    if ((int)puVar4 != 0) {
      if (DAT_140103fa8 == (code *)0x0) {
        free(_Dst);
        return (ulonglong)puVar4 & 0xffffffff;
      }
      (*DAT_140103fa8)(_Dst);
      return (ulonglong)puVar4 & 0xffffffff;
    }
  }
  plVar2 = (longlong *)(param_1 + 0x2a8);
  lVar5 = *plVar2;
  *_Dst = lVar5;
  if (lVar5 != 0) {
    *(longlong **)(*plVar2 + 8) = _Dst;
  }
  *plVar2 = (longlong)_Dst;
  _Dst[1] = (longlong)plVar2;
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return 0;
}


// ==== FUN_140015dd0 @ 140015dd0  undefined FUN_140015dd0(longlong * param_1)

void FUN_140015dd0(longlong *param_1)

{
  FUN_140014300(param_1);
  if (DAT_140103fa8 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000140015df2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*DAT_140103fa8)();
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000140015dfa. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  free(param_1);
  return;
}


// ==== FUN_140015e10 @ 140015e10  undefined8 * FUN_140015e10(longlong * param_1, ulonglong * param_2)

undefined8 * FUN_140015e10(longlong *param_1,ulonglong *param_2)

{
  undefined8 *puVar1;
  
  if (*(longlong *)(param_1[8] + 0x1d0) != 0) {
    FUN_140016e30();
  }
  puVar1 = FUN_140013f70(param_1,param_2,0);
  if (*(longlong *)(param_1[8] + 0x1d0) != 0) {
    FUN_140016e50();
    puVar1 = (undefined8 *)((ulonglong)puVar1 & 0xffffffff);
  }
  return puVar1;
}


// ==== FUN_140015e70 @ 140015e70  ulonglong FUN_140015e70(longlong * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

ulonglong FUN_140015e70(longlong *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 *puVar1;
  longlong lVar2;
  
  if (param_1 == (longlong *)0x0) {
    return 0xffffffff;
  }
  lVar2 = param_1[0x3a];
  if (lVar2 != 0) {
    FUN_140016e30();
  }
  puVar1 = FUN_140014900(param_1,lVar2,param_3,param_4);
  if (param_1[0x3a] != 0) {
    FUN_140016e50();
  }
  return (ulonglong)puVar1 & 0xffffffff;
}


// ==== FUN_140015ed0 @ 140015ed0  longlong * FUN_140015ed0(undefined8 * param_1, undefined8 param_2, longlong param_3, undefined8 * param_4)

longlong *
FUN_140015ed0(undefined8 *param_1,undefined8 param_2,longlong param_3,undefined8 *param_4)

{
  char cVar1;
  char cVar2;
  undefined *puVar3;
  bool bVar4;
  int iVar5;
  longlong *_Dst;
  int *piVar6;
  char *pcVar7;
  longlong lVar8;
  ulonglong uVar9;
  undefined7 extraout_var;
  undefined8 *puVar10;
  undefined8 uVar11;
  undefined **ppuVar12;
  bool bVar13;
  int local_res10 [2];
  
  if (DAT_140103f98 == (code *)0x0) {
    _Dst = (longlong *)calloc(1,0x2b0);
    if (_Dst == (longlong *)0x0) goto LAB_140015f43;
  }
  else {
    _Dst = (longlong *)(*DAT_140103f98)(0x2b0);
    if (_Dst == (longlong *)0x0) {
LAB_140015f43:
      piVar6 = _errno();
      *piVar6 = 0xc;
      goto LAB_140015f0e;
    }
    param_3 = 0x2b0;
    memset(_Dst,0,0x2b0);
  }
  if (_Dst == (longlong *)0x0) {
LAB_140015f0e:
    FUN_140019050("%s: calloc","event_base_new_with_config",param_3,param_4);
    return (longlong *)0x0;
  }
  bVar13 = false;
  if ((param_1 == (undefined8 *)0x0) ||
     (*(undefined4 *)(_Dst + 0x3f) = *(undefined4 *)(param_1 + 5), bVar4 = bVar13,
     (*(byte *)(param_1 + 5) & 2) == 0)) {
    bVar4 = true;
  }
  if ((param_1 != (undefined8 *)0x0) && ((*(byte *)(param_1 + 5) & 0x20) != 0)) {
    bVar13 = true;
  }
  if ((bVar4) && (!bVar13)) {
    pcVar7 = getenv("EVENT_PRECISE_TIMER");
    bVar13 = pcVar7 != (char *)0x0;
    *(uint *)(_Dst + 0x3f) = *(uint *)(_Dst + 0x3f) | 0x20;
  }
  FUN_140016640(_Dst + 0x2d,(uint)bVar13);
  FUN_1400105b0((longlong)_Dst,local_res10);
  _Dst[0x2a] = 0;
  *(undefined4 *)(_Dst + 0x2b) = 0;
  *(undefined4 *)((longlong)_Dst + 0x15c) = 0;
  _Dst[0x14] = -1;
  _Dst[0x15] = -1;
  _Dst[0x42] = -1;
  _Dst[0x21] = 0;
  _Dst[0x43] = -1;
  _Dst[0x22] = (longlong)(_Dst + 0x21);
  FUN_14001a010(_Dst + 0x25);
  FUN_14001a190(_Dst + 0x28);
  FUN_14001ad50(_Dst + 2);
  _Dst[1] = 0;
  if (param_1 == (undefined8 *)0x0) {
    *(undefined4 *)((longlong)_Dst + 0x1fc) = 0xffffffff;
    *(undefined4 *)(_Dst + 0x41) = 1;
LAB_140016084:
    *(undefined4 *)((longlong)_Dst + 0x204) = 0x7fffffff;
  }
  else {
    *(undefined8 *)((longlong)_Dst + 0x1fc) = *(undefined8 *)((longlong)param_1 + 0x14);
    *(undefined4 *)(_Dst + 0x41) = *(undefined4 *)(param_1 + 4);
    if (*(int *)((longlong)param_1 + 0x1c) < 0) goto LAB_140016084;
    *(int *)((longlong)_Dst + 0x204) = *(int *)((longlong)param_1 + 0x1c);
  }
  if ((*(int *)((longlong)_Dst + 0x204) == 0x7fffffff) && (*(int *)((longlong)_Dst + 0x1fc) == -1))
  {
    *(undefined4 *)(_Dst + 0x41) = 0x7fffffff;
  }
  if (PTR_PTR_140102480 != (undefined *)0x0) {
    ppuVar12 = &PTR_PTR_140102480;
    do {
      if (_Dst[1] != 0) break;
      if (param_1 == (undefined8 *)0x0) {
LAB_14001612c:
        if ((!bVar4) || (iVar5 = FUN_140010860(*(undefined8 *)*ppuVar12), iVar5 == 0)) {
          puVar3 = *ppuVar12;
          *_Dst = (longlong)puVar3;
          lVar8 = (**(code **)(puVar3 + 8))(_Dst);
          _Dst[1] = lVar8;
        }
      }
      else {
        for (param_4 = (undefined8 *)*param_1; param_4 != (undefined8 *)0x0;
            param_4 = (undefined8 *)*param_4) {
          pcVar7 = (char *)param_4[2];
          if (pcVar7 != (char *)0x0) {
            param_3 = *(longlong *)*ppuVar12 - (longlong)pcVar7;
            do {
              cVar1 = *pcVar7;
              cVar2 = pcVar7[param_3];
              if (cVar1 != cVar2) break;
              pcVar7 = pcVar7 + 1;
            } while (cVar2 != '\0');
            if (cVar1 == cVar2) goto LAB_140016150;
          }
        }
        if ((*(uint *)((longlong)*ppuVar12 + 0x34) & *(uint *)((longlong)param_1 + 0x24)) ==
            *(uint *)((longlong)param_1 + 0x24)) goto LAB_14001612c;
      }
LAB_140016150:
      ppuVar12 = ppuVar12 + 1;
    } while (*ppuVar12 != (undefined *)0x0);
  }
  if (_Dst[1] == 0) {
    FUN_1400191c0("%s: no event mechanism available","event_base_new_with_config",param_3,param_4);
    *_Dst = 0;
  }
  else {
    pcVar7 = getenv("EVENT_SHOW_METHOD");
    if (pcVar7 != (char *)0x0) {
      FUN_1400191f0("libevent using: %s",*(undefined8 *)*_Dst,param_3,param_4);
    }
    uVar11 = 1;
    uVar9 = FUN_1400127e0((longlong)_Dst,1,param_3,param_4);
    if (-1 < (int)uVar9) {
      bVar13 = FUN_140016f00();
      if (((int)CONCAT71(extraout_var,bVar13) != 0) &&
         ((param_1 == (undefined8 *)0x0 || ((*(byte *)(param_1 + 5) & 1) == 0)))) {
        lVar8 = FUN_140016df0();
        _Dst[0x3a] = lVar8;
        lVar8 = FUN_140016e70();
        _Dst[0x3b] = lVar8;
        uVar9 = FUN_140015e70(_Dst,uVar11,param_3,param_4);
        if ((int)uVar9 < 0) {
          FUN_1400191c0("%s: Unable to make base notifiable.","event_base_new_with_config",param_3,
                        param_4);
          goto LAB_140016206;
        }
      }
      if (((param_1 != (undefined8 *)0x0) && ((*(byte *)(param_1 + 5) & 4) != 0)) &&
         (_Dst[0x3e] == 0)) {
        puVar10 = FUN_140074b80(*(DWORD *)(param_1 + 2));
        _Dst[0x3e] = (longlong)puVar10;
        if (puVar10 == (undefined8 *)0x0) {
          FUN_1400191c0("%s: Couldn\'t launch IOCP","event_base_start_iocp_",param_3,param_4);
        }
      }
      return _Dst;
    }
  }
LAB_140016206:
  FUN_140014b30(_Dst,1,param_3,param_4);
  return (longlong *)0x0;
}


// ==== FUN_140016270 @ 140016270  undefined FUN_140016270(longlong * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_140016270(longlong *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  FUN_140015950(param_1,0,param_3,param_4);
  return;
}


// ==== FUN_140016280 @ 140016280  undefined FUN_140016280(longlong param_1, ulonglong * param_2)

void FUN_140016280(longlong param_1,ulonglong *param_2)

{
  FUN_140015b60(param_1,0xffffffffffffffff,1,0x140010d90,param_1,param_2);
  return;
}


// ==== FUN_1400162c0 @ 1400162c0  undefined FUN_1400162c0(undefined8 param_1, ushort param_2, longlong param_3, longlong param_4, ulonglong * param_5)

void FUN_1400162c0(undefined8 param_1,ushort param_2,longlong param_3,longlong param_4,
                  ulonglong *param_5)

{
  FUN_140015b60(DAT_140103f80,param_1,param_2,param_3,param_4,param_5);
  return;
}


// ==== FUN_1400162f0 @ 1400162f0  longlong * FUN_1400162f0(undefined8 param_1, undefined8 param_2, longlong param_3, undefined8 * param_4)

longlong * FUN_1400162f0(undefined8 param_1,undefined8 param_2,longlong param_3,undefined8 *param_4)

{
  longlong *plVar1;
  
  plVar1 = FUN_140015ed0((undefined8 *)0x0,param_2,param_3,param_4);
  if (plVar1 == (longlong *)0x0) {
    FUN_140019160(1,"%s: Unable to construct event_base","event_init",param_4);
    return (longlong *)0x0;
  }
  DAT_140103f80 = plVar1;
  return plVar1;
}


// ==== FUN_140016330 @ 140016330  longlong * FUN_140016330(undefined8 param_1, undefined8 param_2, longlong param_3, undefined8 * param_4)

longlong * FUN_140016330(undefined8 param_1,undefined8 param_2,longlong param_3,undefined8 *param_4)

{
  undefined8 *puVar1;
  longlong *plVar2;
  
  puVar1 = FUN_140012580();
  if (puVar1 != (undefined8 *)0x0) {
    plVar2 = FUN_140015ed0(puVar1,param_2,param_3,param_4);
    FUN_140012660(puVar1);
    return plVar2;
  }
  return (longlong *)0x0;
}


// ==== FUN_140016390 @ 140016390  undefined FUN_140016390(ulonglong * param_1)

void FUN_140016390(ulonglong *param_1)

{
  FUN_140015b60(DAT_140103f80,0xffffffffffffffff,1,0x140010d90,DAT_140103f80,param_1);
  return;
}


// ==== FUN_1400163c0 @ 1400163c0  undefined8 FUN_1400163c0(undefined4 * param_1)

undefined8 FUN_1400163c0(undefined4 *param_1)

{
  ulonglong uVar1;
  _FILETIME local_res8 [4];
  
  if (param_1 != (undefined4 *)0x0) {
    GetSystemTimeAsFileTime(local_res8);
    if (0x19db1ded53e7fff < (ulonglong)local_res8[0]) {
      *param_1 = (int)(((longlong)local_res8[0] + 0xfe624e212ac18000U) / 10000000);
      uVar1 = ((longlong)local_res8[0] + 0xfe624e212ac18000U) / 10;
      param_1[1] = (int)uVar1 + (int)(uVar1 / 1000000) * -1000000;
      return 0;
    }
  }
  return 0xffffffff;
}


// ==== FUN_140016450 @ 140016450  int FUN_140016450(int * param_1)

int FUN_140016450(int *param_1)

{
  if ((param_1[1] < 0xf4241) && (*param_1 < 0x20c49b)) {
    return (param_1[1] + 999) / 1000 + *param_1 * 1000;
  }
  return -1;
}


// ==== FUN_140016490 @ 140016490  undefined FUN_140016490(int * param_1)

void FUN_140016490(int *param_1)

{
  if (param_1 != (int *)0x0) {
    if ((param_1[1] < 0xf4241) && (*param_1 < 0x20c49b)) {
                    /* WARNING: Could not recover jumptable at 0x0001400164d6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      Sleep((param_1[1] + 999) / 1000 + *param_1 * 1000);
      return;
    }
    Sleep(0xffffffff);
  }
  return;
}


// ==== FUN_1400164f0 @ 1400164f0  undefined FUN_1400164f0(longlong param_1, int * param_2)

void FUN_1400164f0(longlong param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  *param_2 = *param_2 + *(int *)(param_1 + 0x3c);
  param_2[1] = param_2[1] + *(int *)(param_1 + 0x40);
  if (999999 < param_2[1]) {
    *param_2 = *param_2 + 1;
    param_2[1] = param_2[1] + -1000000;
  }
  iVar2 = *param_2;
  iVar3 = *(int *)(param_1 + 0x44);
  bVar4 = SBORROW4(iVar2,iVar3);
  iVar1 = iVar2 - iVar3;
  if (iVar2 == iVar3) {
    bVar4 = SBORROW4(param_2[1],*(int *)(param_1 + 0x48));
    iVar1 = param_2[1] - *(int *)(param_1 + 0x48);
  }
  if (bVar4 != iVar1 < 0) {
    iVar3 = iVar3 - iVar2;
    iVar2 = *(int *)(param_1 + 0x48) - param_2[1];
    if (iVar2 < 0) {
      iVar3 = iVar3 + -1;
      iVar2 = iVar2 + 1000000;
    }
    *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + iVar3;
    *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + iVar2;
    if (999999 < *(int *)(param_1 + 0x40)) {
      *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + 1;
      *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + -1000000;
    }
    *(undefined8 *)param_2 = *(undefined8 *)(param_1 + 0x44);
  }
  *(undefined8 *)(param_1 + 0x44) = *(undefined8 *)param_2;
  return;
}


// ==== FUN_140016580 @ 140016580  void * FUN_140016580(void)

void * FUN_140016580(void)

{
  void *_Dst;
  
  _Dst = FUN_140011830(0x50);
  if (_Dst != (void *)0x0) {
    memset(_Dst,0,0x50);
  }
  return _Dst;
}


// ==== FUN_1400165b0 @ 1400165b0  undefined FUN_1400165b0(void * param_1)

void FUN_1400165b0(void *param_1)

{
  if (param_1 != (void *)0x0) {
    FUN_1400119c0(param_1);
  }
  return;
}


// ==== FUN_1400165d0 @ 1400165d0  ulonglong FUN_1400165d0(undefined8 * param_1)

ulonglong FUN_1400165d0(undefined8 *param_1)

{
  DWORD DVar1;
  ulonglong uVar2;
  
  if ((code *)*param_1 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0001400165e6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar2 = (*(code *)*param_1)();
    return uVar2;
  }
  if ((code *)param_1[1] != (code *)0x0) {
    uVar2 = (*(code *)param_1[1])();
    return uVar2 & 0xffffffff | uVar2 >> 0x12 & 0x3fff00000000;
  }
  DVar1 = GetTickCount();
  uVar2 = (ulonglong)DVar1;
  if (uVar2 < (ulonglong)param_1[2]) {
    param_1[3] = param_1[3] + 0x100000000;
  }
  param_1[2] = uVar2;
  return param_1[3] + uVar2;
}


// ==== FUN_140016640 @ 140016640  undefined8 FUN_140016640(undefined8 * param_1, uint param_2)

undefined8 FUN_140016640(undefined8 *param_1,uint param_2)

{
  BOOL BVar1;
  HMODULE hModule;
  FARPROC pFVar2;
  ulonglong uVar3;
  LARGE_INTEGER local_res8;
  LARGE_INTEGER local_res18 [2];
  
  memset(param_1,0,0x50);
  hModule = (HMODULE)FUN_140008b90("kernel32.dll");
  if ((hModule != (HMODULE)0x0) && ((param_2 & 2) == 0)) {
    pFVar2 = GetProcAddress(hModule,"GetTickCount64");
    *param_1 = pFVar2;
    pFVar2 = GetProcAddress(hModule,"GetTickCount");
    param_1[1] = pFVar2;
  }
  uVar3 = FUN_1400165d0(param_1);
  param_1[2] = uVar3;
  param_1[4] = uVar3;
  if (((param_2 & 1) != 0) && ((param_2 & 2) == 0)) {
    BVar1 = QueryPerformanceFrequency(local_res18);
    if (BVar1 != 0) {
      QueryPerformanceCounter(&local_res8);
      *(undefined4 *)(param_1 + 7) = 1;
      *(LARGE_INTEGER *)(param_1 + 5) = local_res8;
      param_1[6] = 1000000.0 / (double)local_res18[0].QuadPart;
    }
  }
  return 0;
}


// ==== FUN_140016720 @ 140016720  undefined8 FUN_140016720(undefined8 * param_1, int * param_2)

undefined8 FUN_140016720(undefined8 *param_1,int *param_2)

{
  undefined1 auVar1 [16];
  int iVar2;
  ulonglong uVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  double dVar7;
  LARGE_INTEGER local_res8;
  
  uVar3 = FUN_1400165d0(param_1);
  if (*(int *)(param_1 + 7) == 0) {
    auVar1._8_8_ = 0;
    auVar1._0_8_ = uVar3;
    lVar6 = SUB168(ZEXT816(0x624dd2f1a9fbe77) * auVar1,8);
    iVar2 = (int)((uVar3 - lVar6 >> 1) + lVar6 >> 9);
    *param_2 = iVar2;
    param_2[1] = ((int)uVar3 + iVar2 * -1000) * 1000;
  }
  else {
    QueryPerformanceCounter(&local_res8);
    lVar5 = (uVar3 - param_1[4]) * 1000;
    lVar6 = (longlong)((double)(local_res8.QuadPart - param_1[5]) * (double)param_1[6]);
    lVar4 = lVar5 - lVar6;
    if (lVar4 < 0) {
      lVar4 = -lVar4;
    }
    if (1000000 < lVar4) {
      lVar6 = 0;
      dVar7 = (double)local_res8.QuadPart - (double)lVar5 / (double)param_1[6];
      if ((9.223372036854776e+18 < dVar7) &&
         (dVar7 = dVar7 - 9.223372036854776e+18, dVar7 < 9.223372036854776e+18)) {
        lVar6 = -0x8000000000000000;
      }
      param_1[5] = (longlong)dVar7 + lVar6;
      lVar6 = lVar5;
    }
    iVar2 = (int)(lVar6 / 1000000);
    *param_2 = iVar2;
    param_2[1] = (int)lVar6 + iVar2 * -1000000;
  }
  FUN_1400164f0((longlong)param_1,param_2);
  return 0;
}


// ==== FUN_140016880 @ 140016880  undefined FUN_140016880(undefined8 param_1)

void FUN_140016880(undefined8 param_1)

{
  DAT_140103fe0 = param_1;
  return;
}


// ==== FUN_140016890 @ 140016890  int FUN_140016890(int * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

int FUN_140016890(int *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  longlong lVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = (int *)&DAT_140103fb8;
  if (DAT_140103fb0 != 0) {
    piVar3 = (int *)&DAT_140104010;
  }
  if (param_1 == (int *)0x0) {
    if (*(longlong *)(piVar3 + 2) != 0) {
      FUN_1400191c0("Trying to disable lock functions after they have been set up will probaby not work."
                    ,param_2,param_3,param_4);
    }
    piVar3[0] = 0;
    piVar3[1] = 0;
    piVar3[2] = 0;
    piVar3[3] = 0;
    piVar3[4] = 0;
    piVar3[5] = 0;
    piVar3[6] = 0;
    piVar3[7] = 0;
    piVar3[8] = 0;
    piVar3[9] = 0;
    return 0;
  }
  lVar1 = *(longlong *)(piVar3 + 2);
  if (lVar1 == 0) {
    if ((((*(longlong *)(param_1 + 2) != 0) && (*(longlong *)(param_1 + 4) != 0)) &&
        (*(longlong *)(param_1 + 6) != 0)) && (*(longlong *)(param_1 + 8) != 0)) {
      *(undefined8 *)piVar3 = *(undefined8 *)param_1;
      *(undefined8 *)(piVar3 + 2) = *(undefined8 *)(param_1 + 2);
      *(undefined8 *)(piVar3 + 4) = *(undefined8 *)(param_1 + 4);
      *(undefined8 *)(piVar3 + 6) = *(undefined8 *)(param_1 + 6);
      *(undefined8 *)(piVar3 + 8) = *(undefined8 *)(param_1 + 8);
      iVar2 = FUN_1400121b0(1,0,param_3,param_4);
      return iVar2;
    }
  }
  else {
    if ((((*piVar3 == *param_1) && (piVar3[1] == param_1[1])) &&
        ((lVar1 == *(longlong *)(param_1 + 2) &&
         ((*(longlong *)(piVar3 + 4) == *(longlong *)(param_1 + 4) &&
          (*(longlong *)(piVar3 + 6) == *(longlong *)(param_1 + 6))))))) &&
       (*(longlong *)(piVar3 + 8) == *(longlong *)(param_1 + 8))) {
      return 0;
    }
    FUN_1400191c0("Can\'t change lock callbacks once they have been initialized.",lVar1,param_3,
                  param_4);
  }
  return -1;
}


// ==== FUN_140016990 @ 140016990  undefined8 FUN_140016990(int * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

undefined8 FUN_140016990(int *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  longlong lVar1;
  uint uVar2;
  int *piVar3;
  
  uVar2 = DAT_140103fb0;
  piVar3 = (int *)&DAT_140103fe8;
  if (DAT_140103fb0 != 0) {
    piVar3 = (int *)&DAT_140104038;
  }
  if (param_1 == (int *)0x0) {
    if (*(longlong *)(piVar3 + 2) != 0) {
      FUN_1400191c0("Trying to disable condition functions after they have been set up will probaby not work."
                    ,param_2,(ulonglong)DAT_140103fb0,param_4);
    }
    piVar3[0] = 0;
    piVar3[1] = 0;
    piVar3[2] = 0;
    piVar3[3] = 0;
    piVar3[4] = 0;
    piVar3[5] = 0;
    piVar3[6] = 0;
    piVar3[7] = 0;
    piVar3[8] = 0;
    piVar3[9] = 0;
    return 0;
  }
  lVar1 = *(longlong *)(piVar3 + 2);
  if (lVar1 == 0) {
    if ((((*(longlong *)(param_1 + 2) != 0) && (*(longlong *)(param_1 + 4) != 0)) &&
        (*(longlong *)(param_1 + 6) != 0)) && (*(longlong *)(param_1 + 8) != 0)) {
      *(undefined8 *)piVar3 = *(undefined8 *)param_1;
      *(undefined8 *)(piVar3 + 2) = *(undefined8 *)(param_1 + 2);
      *(undefined8 *)(piVar3 + 4) = *(undefined8 *)(param_1 + 4);
      *(undefined8 *)(piVar3 + 6) = *(undefined8 *)(param_1 + 6);
      *(undefined8 *)(piVar3 + 8) = *(undefined8 *)(param_1 + 8);
    }
    if (uVar2 != 0) {
      DAT_140103ff0 = *(undefined8 *)(param_1 + 2);
      DAT_140103ff8 = *(undefined8 *)(param_1 + 4);
      DAT_140104000 = *(undefined8 *)(param_1 + 6);
    }
  }
  else if (((*piVar3 != *param_1) || (lVar1 != *(longlong *)(param_1 + 2))) ||
          ((*(longlong *)(piVar3 + 4) != *(longlong *)(param_1 + 4) ||
           ((*(longlong *)(piVar3 + 6) != *(longlong *)(param_1 + 6) ||
            (*(longlong *)(piVar3 + 8) != *(longlong *)(param_1 + 8))))))) {
    FUN_1400191c0("Can\'t change condition callbacks once they have been initialized.",lVar1,
                  (ulonglong)DAT_140103fb0,param_4);
    return 0xffffffff;
  }
  return 0;
}


// ==== FUN_140016aa0 @ 140016aa0  undefined4 * FUN_140016aa0(uint param_1)

undefined4 * FUN_140016aa0(uint param_1)

{
  undefined4 *puVar1;
  longlong lVar2;
  
  puVar1 = (undefined4 *)FUN_140011830(0x18);
  if (puVar1 == (undefined4 *)0x0) {
    return (undefined4 *)0x0;
  }
  if (DAT_140104018 == (code *)0x0) {
    *(undefined8 *)(puVar1 + 4) = 0;
  }
  else {
    lVar2 = (*DAT_140104018)(param_1 | 1);
    *(longlong *)(puVar1 + 4) = lVar2;
    if (lVar2 == 0) {
      FUN_1400119c0(puVar1);
      return (undefined4 *)0x0;
    }
  }
  *puVar1 = 0xdeb0b10c;
  puVar1[1] = param_1;
  puVar1[3] = 0;
  puVar1[2] = 0;
  return puVar1;
}


// ==== FUN_140016b20 @ 140016b20  undefined FUN_140016b20(undefined4 * param_1)

void FUN_140016b20(undefined4 *param_1)

{
  if (DAT_140104020 != (code *)0x0) {
    (*DAT_140104020)(*(undefined8 *)(param_1 + 4),param_1[1] | 1);
  }
  *(undefined8 *)(param_1 + 4) = 0;
  param_1[3] = 0xffffff9c;
  *param_1 = 0x12300fda;
  FUN_1400119c0(param_1);
  return;
}


// ==== FUN_140016b70 @ 140016b70  undefined FUN_140016b70(undefined8 param_1, longlong param_2)

void FUN_140016b70(undefined8 param_1,longlong param_2)

{
  code *pcVar1;
  undefined4 uVar2;
  
  pcVar1 = DAT_140103fe0;
  *(int *)(param_2 + 0xc) = *(int *)(param_2 + 0xc) + 1;
  if (pcVar1 != (code *)0x0) {
    uVar2 = (*pcVar1)();
    *(undefined4 *)(param_2 + 8) = uVar2;
  }
  return;
}


// ==== FUN_140016ba0 @ 140016ba0  ulonglong FUN_140016ba0(undefined8 param_1, longlong param_2)

ulonglong FUN_140016ba0(undefined8 param_1,longlong param_2)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  ulonglong unaff_RBX;
  
  if (((DAT_140104028 == (code *)0x0) ||
      (iVar2 = (*DAT_140104028)(param_1,*(undefined8 *)(param_2 + 0x10)), iVar2 == 0)) &&
     (pcVar1 = DAT_140103fe0, *(int *)(param_2 + 0xc) = *(int *)(param_2 + 0xc) + 1,
     pcVar1 != (code *)0x0)) {
    uVar3 = (*pcVar1)();
    *(undefined4 *)(param_2 + 8) = uVar3;
  }
  return unaff_RBX;
}


// ==== FUN_140016bf0 @ 140016bf0  undefined FUN_140016bf0(undefined8 param_1, longlong param_2)

void FUN_140016bf0(undefined8 param_1,longlong param_2)

{
  if (DAT_140103fe0 != (code *)0x0) {
    (*DAT_140103fe0)();
    if (*(int *)(param_2 + 0xc) == 1) {
      *(undefined4 *)(param_2 + 8) = 0;
    }
    *(int *)(param_2 + 0xc) = *(int *)(param_2 + 0xc) + -1;
    return;
  }
  *(int *)(param_2 + 0xc) = *(int *)(param_2 + 0xc) + -1;
  return;
}


// ==== FUN_140016c30 @ 140016c30  undefined8 FUN_140016c30(undefined4 param_1, longlong param_2)

undefined8 FUN_140016c30(undefined4 param_1,longlong param_2)

{
  undefined8 uVar1;
  
  if (DAT_140103fe0 != (code *)0x0) {
    (*DAT_140103fe0)();
    if (*(int *)(param_2 + 0xc) == 1) {
      *(undefined4 *)(param_2 + 8) = 0;
    }
  }
  *(int *)(param_2 + 0xc) = *(int *)(param_2 + 0xc) + -1;
  if (DAT_140104030 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000140016c79. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*DAT_140104030)(param_1,*(undefined8 *)(param_2 + 0x10));
    return uVar1;
  }
  return 0;
}


// ==== FUN_140016c90 @ 140016c90  undefined8 FUN_140016c90(longlong param_1)

undefined8 FUN_140016c90(longlong param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0xc) == 0) {
    return 0;
  }
  if ((DAT_140103fe0 != (code *)0x0) && (iVar1 = (*DAT_140103fe0)(), *(int *)(param_1 + 8) != iVar1)
     ) {
    return 0;
  }
  return 1;
}


// ==== FUN_140016ce0 @ 140016ce0  undefined4 * FUN_140016ce0(undefined4 * param_1, uint param_2, int param_3)

undefined4 * FUN_140016ce0(undefined4 *param_1,uint param_2,int param_3)

{
  undefined4 *puVar1;
  longlong lVar2;
  
  if (param_3 != 0) {
    if (DAT_140103fb0 == 0) {
                    /* WARNING: Could not recover jumptable at 0x000140016d81. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      puVar1 = (undefined4 *)(*DAT_140103fc0)(param_2);
      return puVar1;
    }
    lVar2 = (*DAT_140104018)(param_2 | 1);
    *(longlong *)(param_1 + 4) = lVar2;
    if (lVar2 == 0) {
      param_1[3] = 0xffffff38;
      FUN_1400119c0(param_1);
      return (undefined4 *)0x0;
    }
    return param_1;
  }
  if (DAT_140104018 == (code *)0x0) {
    puVar1 = FUN_140016aa0(param_2);
    return puVar1;
  }
  if ((param_2 & 1) == 0) {
    (*DAT_140104020)();
    puVar1 = FUN_140016aa0(param_2);
    return puVar1;
  }
  puVar1 = (undefined4 *)FUN_140011830(0x18);
  if (puVar1 == (undefined4 *)0x0) {
    (*DAT_140104020)(param_1,param_2);
    return (undefined4 *)0x0;
  }
  *(undefined4 **)(puVar1 + 4) = param_1;
  puVar1[1] = param_2;
  puVar1[3] = 0;
  puVar1[2] = 0;
  return puVar1;
}


// ==== FUN_140016dd0 @ 140016dd0  undefined8 FUN_140016dd0(void)

undefined8 FUN_140016dd0(void)

{
  undefined8 uVar1;
  
  if (DAT_140103fe0 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000140016ddc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*DAT_140103fe0)();
    return uVar1;
  }
  return 1;
}


// ==== FUN_140016df0 @ 140016df0  undefined8 FUN_140016df0(void)

undefined8 FUN_140016df0(void)

{
  undefined8 uVar1;
  
  if (DAT_140103fc0 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000140016dfc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*DAT_140103fc0)();
    return uVar1;
  }
  return 0;
}


// ==== FUN_140016e10 @ 140016e10  undefined FUN_140016e10(void)

void FUN_140016e10(void)

{
  if (DAT_140103fc8 != (code *)0x0) {
    (*DAT_140103fc8)();
  }
  return;
}


// ==== FUN_140016e30 @ 140016e30  undefined8 FUN_140016e30(void)

undefined8 FUN_140016e30(void)

{
  undefined8 uVar1;
  
  if (DAT_140103fd0 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000140016e3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*DAT_140103fd0)();
    return uVar1;
  }
  return 0;
}


// ==== FUN_140016e50 @ 140016e50  undefined8 FUN_140016e50(void)

undefined8 FUN_140016e50(void)

{
  undefined8 uVar1;
  
  if (DAT_140103fd8 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000140016e5c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*DAT_140103fd8)();
    return uVar1;
  }
  return 0;
}


// ==== FUN_140016e70 @ 140016e70  undefined8 FUN_140016e70(void)

undefined8 FUN_140016e70(void)

{
  undefined8 uVar1;
  
  if (DAT_140103ff0 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000140016e7c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*DAT_140103ff0)();
    return uVar1;
  }
  return 0;
}


// ==== FUN_140016e90 @ 140016e90  undefined FUN_140016e90(void)

void FUN_140016e90(void)

{
  if (DAT_140103ff8 != (code *)0x0) {
    (*DAT_140103ff8)();
  }
  return;
}


// ==== FUN_140016eb0 @ 140016eb0  undefined8 FUN_140016eb0(void)

undefined8 FUN_140016eb0(void)

{
  undefined8 uVar1;
  
  if (DAT_140104000 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000140016ebc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*DAT_140104000)();
    return uVar1;
  }
  return 0;
}


// ==== FUN_140016ed0 @ 140016ed0  undefined8 FUN_140016ed0(void)

undefined8 FUN_140016ed0(void)

{
  undefined8 uVar1;
  
  if (DAT_140104008 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000140016edc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*DAT_140104008)();
    return uVar1;
  }
  return 0;
}


// ==== FUN_140016ef0 @ 140016ef0  undefined4 FUN_140016ef0(void)

undefined4 FUN_140016ef0(void)

{
  return DAT_140103fb0;
}


// ==== FUN_140016f00 @ 140016f00  bool FUN_140016f00(void)

bool FUN_140016f00(void)

{
  return DAT_140103fd0 != 0;
}


// ==== FUN_140016f10 @ 140016f10  undefined4 FUN_140016f10(undefined8 param_1, longlong param_2, undefined8 param_3)

undefined4 FUN_140016f10(undefined8 param_1,longlong param_2,undefined8 param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  if (DAT_140103fe0 != (code *)0x0) {
    (*DAT_140103fe0)();
    if (*(int *)(param_2 + 0xc) == 1) {
      *(undefined4 *)(param_2 + 8) = 0;
    }
  }
  *(int *)(param_2 + 0xc) = *(int *)(param_2 + 0xc) + -1;
  uVar1 = (*DAT_140104058)(param_1,*(undefined8 *)(param_2 + 0x10),param_3);
  *(int *)(param_2 + 0xc) = *(int *)(param_2 + 0xc) + 1;
  if (DAT_140103fe0 != (code *)0x0) {
    uVar2 = (*DAT_140103fe0)();
    *(undefined4 *)(param_2 + 8) = uVar2;
  }
  return uVar1;
}


// ==== FUN_140016f80 @ 140016f80  undefined FUN_140016f80(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_140016f80(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  if (DAT_140103fb0 == 0) {
    DAT_140103fb0 = 1;
    DAT_140104010 = DAT_140103fb8;
    DAT_140104018 = DAT_140103fc0;
    DAT_140104020 = DAT_140103fc8;
    DAT_140104028 = DAT_140103fd0;
    DAT_140104030 = DAT_140103fd8;
    DAT_140103fb8 = 0x100000001;
    DAT_140103fc0 = FUN_140016aa0;
    DAT_140103fc8 = FUN_140016b20;
    DAT_140103fd0 = FUN_140016ba0;
    DAT_140103fd8 = FUN_140016c30;
    DAT_140104038 = DAT_140103fe8;
    DAT_140104040 = DAT_140103ff0;
    DAT_140104048 = DAT_140103ff8;
    DAT_140104050 = DAT_140104000;
    DAT_140104058 = DAT_140104008;
    DAT_140104008 = FUN_140016f10;
    FUN_1400121b0(0,&IMAGE_DOS_HEADER_140000000,param_3,param_4);
  }
  return;
}


// ==== FUN_1400170e0 @ 1400170e0  bool FUN_1400170e0(longlong param_1)

bool FUN_1400170e0(longlong param_1)

{
  undefined8 uVar1;
  
  if (param_1 != 0) {
    uVar1 = FUN_140016e30();
    return (int)uVar1 == 0;
  }
  return true;
}


// ==== FUN_140017150 @ 140017150  undefined8 FUN_140017150(ulonglong * param_1, ulonglong * param_2, int param_3)

undefined8 FUN_140017150(ulonglong *param_1,ulonglong *param_2,int param_3)

{
  ulonglong uVar1;
  uint uVar2;
  ulonglong uVar3;
  
  uVar2 = param_3 - (int)param_1[2];
  if ((uVar2 == 0) || (0x7fffffff < uVar2)) {
    return 0;
  }
  uVar3 = (ulonglong)uVar2;
  if ((param_2[1] - *param_1) / uVar3 < *param_2) {
    *param_1 = param_2[1];
  }
  else {
    *param_1 = *param_2 * uVar3 + *param_1;
  }
  uVar1 = param_2[2];
  if ((param_2[3] - param_1[1]) / uVar3 < uVar1) {
    param_1[1] = param_2[3];
    *(int *)(param_1 + 2) = param_3;
    return 1;
  }
  *(int *)(param_1 + 2) = param_3;
  param_1[1] = uVar1 * uVar3 + param_1[1];
  return 1;
}


// ==== FUN_140017220 @ 140017220  ulonglong * FUN_140017220(ulonglong param_1, ulonglong param_2, ulonglong param_3, ulonglong param_4, ulonglong * param_5)

ulonglong *
FUN_140017220(ulonglong param_1,ulonglong param_2,ulonglong param_3,ulonglong param_4,
             ulonglong *param_5)

{
  ulonglong *puVar1;
  ulonglong **ppuVar2;
  
  ppuVar2 = (ulonglong **)param_5;
  if (param_5 == (ulonglong *)0x0) {
    param_5 = (ulonglong *)0x1;
    ppuVar2 = &param_5;
  }
  if (((((param_1 <= param_2) && (param_3 <= param_4)) && (param_1 != 0)) &&
      ((param_3 != 0 && (param_1 < 0x8000000000000000)))) &&
     ((param_3 < 0x8000000000000000 &&
      ((param_2 < 0x8000000000000000 && (param_4 < 0x8000000000000000)))))) {
    puVar1 = (ulonglong *)FUN_140011850(1,0x30);
    if (puVar1 != (ulonglong *)0x0) {
      *puVar1 = param_1;
      puVar1[2] = param_3;
      puVar1[1] = param_2;
      puVar1[3] = param_4;
      puVar1[4] = (ulonglong)*ppuVar2;
      *(uint *)(puVar1 + 5) =
           (*(uint *)((longlong)ppuVar2 + 4) & 0xfffff) / 1000 + *(int *)ppuVar2 * 1000;
      return puVar1;
    }
  }
  return (ulonglong *)0x0;
}


// ==== FUN_140017330 @ 140017330  undefined8 FUN_140017330(longlong * param_1)

undefined8 FUN_140017330(longlong *param_1)

{
  longlong lVar1;
  undefined8 uVar2;
  
  lVar1 = *param_1;
  *(uint *)(param_1 + 10) = *(uint *)(param_1 + 10) & 0xfffffffb | 1;
  for (; lVar1 != 0; lVar1 = **(longlong **)(lVar1 + 0x1d0)) {
    if (((*(longlong *)(lVar1 + 0x1b8) == 0) || (uVar2 = FUN_140016e30(), (int)uVar2 == 0)) &&
       (FUN_1400057f0(lVar1,4), *(longlong *)(lVar1 + 0x1b8) != 0)) {
      FUN_140016e50();
    }
  }
  return 0;
}


// ==== FUN_1400173b0 @ 1400173b0  undefined8 FUN_1400173b0(longlong * param_1)

undefined8 FUN_1400173b0(longlong *param_1)

{
  longlong lVar1;
  undefined8 uVar2;
  
  lVar1 = *param_1;
  *(uint *)(param_1 + 10) = *(uint *)(param_1 + 10) & 0xfffffff7 | 2;
  for (; lVar1 != 0; lVar1 = **(longlong **)(lVar1 + 0x1d0)) {
    if (((*(longlong *)(lVar1 + 0x1b8) == 0) || (uVar2 = FUN_140016e30(), (int)uVar2 == 0)) &&
       (FUN_1400058d0(lVar1,4), *(longlong *)(lVar1 + 0x1b8) != 0)) {
      FUN_140016e50();
    }
  }
  return 0;
}


// ==== FUN_140017430 @ 140017430  undefined FUN_140017430(undefined8 param_1, undefined8 param_2, longlong * param_3)

void FUN_140017430(undefined8 param_1,undefined8 param_2,longlong *param_3)

{
  ulonglong *puVar1;
  bool bVar2;
  int local_res18;
  int local_res1c;
  
  bVar2 = false;
  if (param_3[0x37] != 0) {
    FUN_140016e30();
  }
  if ((param_3[0x3a] == 0) || (*(longlong *)(param_3[0x3a] + 0x30) == 0)) goto LAB_14001752a;
  FUN_140010680(*param_3,&local_res18);
  puVar1 = *(ulonglong **)(param_3[0x3a] + 0x30);
  FUN_140017150((ulonglong *)(param_3[0x3a] + 0x18),puVar1,
                (int)((ulonglong)((longlong)(local_res1c / 1000) + (longlong)local_res18 * 1000) /
                     (ulonglong)(uint)puVar1[5]));
  if ((*(byte *)((longlong)param_3 + 0x176) & 2) != 0) {
    if (*(longlong *)(param_3[0x3a] + 0x18) < 1) {
      bVar2 = true;
    }
    else {
      FUN_140005860((longlong)param_3,2);
    }
  }
  if ((*(byte *)(param_3 + 0x2f) & 2) == 0) {
LAB_14001750e:
    if (!bVar2) goto LAB_14001752a;
  }
  else if (0 < *(longlong *)(param_3[0x3a] + 0x20)) {
    FUN_140005940((longlong)param_3,2);
    goto LAB_14001750e;
  }
  FUN_140015e10((longlong *)(param_3[0x3a] + 0x38),
                (ulonglong *)(*(longlong *)(param_3[0x3a] + 0x30) + 0x20));
LAB_14001752a:
  if (param_3[0x37] != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_140017550 @ 140017550  longlong FUN_140017550(longlong * param_1)

longlong FUN_140017550(longlong *param_1)

{
  longlong lVar1;
  int iVar2;
  
  if ((int)param_1[0xd] != 0) {
    iVar2 = FUN_1400089a0((uint *)(param_1 + 0x1f),(int)param_1[0xd]);
    lVar1 = *param_1;
    for (; iVar2 != 0; iVar2 = iVar2 + -1) {
      lVar1 = **(longlong **)(lVar1 + 0x1d0);
    }
    return lVar1;
  }
  return 0;
}


// ==== FUN_1400175a0 @ 1400175a0  undefined FUN_1400175a0(longlong * param_1)

void FUN_1400175a0(longlong *param_1)

{
  int iVar1;
  undefined8 uVar2;
  longlong lVar3;
  longlong lVar4;
  uint uVar5;
  bool bVar6;
  
  *(uint *)(param_1 + 10) = *(uint *)(param_1 + 10) & 0xfffffffe;
  uVar5 = 0;
  if ((int)param_1[0xd] == 0) {
    lVar3 = 0;
    lVar4 = lVar3;
  }
  else {
    iVar1 = FUN_1400089a0((uint *)(param_1 + 0x1f),(int)param_1[0xd]);
    lVar3 = *param_1;
    for (; lVar4 = lVar3, iVar1 != 0; iVar1 = iVar1 + -1) {
      lVar3 = **(longlong **)(lVar3 + 0x1d0);
    }
  }
  for (; lVar3 != 0; lVar3 = **(longlong **)(lVar3 + 0x1d0)) {
    if (*(longlong *)(lVar3 + 0x1b8) == 0) {
LAB_140017626:
      FUN_140005860(lVar3,4);
      if (*(longlong *)(lVar3 + 0x1b8) != 0) {
        FUN_140016e50();
      }
    }
    else {
      uVar2 = FUN_140016e30();
      bVar6 = (int)uVar2 == 0;
      if (bVar6) goto LAB_140017626;
      uVar5 = bVar6 + 1;
    }
  }
  lVar3 = *param_1;
  do {
    if ((lVar3 == 0) || (lVar3 == lVar4)) {
      *(uint *)(param_1 + 10) = *(uint *)(param_1 + 10) & 0xfffffffb;
      *(uint *)(param_1 + 10) = *(uint *)(param_1 + 10) | (uVar5 & 1) << 2;
      return;
    }
    if (*(longlong *)(lVar3 + 0x1b8) == 0) {
LAB_14001768b:
      FUN_140005860(lVar3,4);
      if (*(longlong *)(lVar3 + 0x1b8) != 0) {
        FUN_140016e50();
      }
    }
    else {
      uVar2 = FUN_140016e30();
      bVar6 = (int)uVar2 == 0;
      if (bVar6) goto LAB_14001768b;
      uVar5 = bVar6 + 1;
    }
    lVar3 = **(longlong **)(lVar3 + 0x1d0);
  } while( true );
}


// ==== FUN_1400176e0 @ 1400176e0  undefined FUN_1400176e0(longlong * param_1)

void FUN_1400176e0(longlong *param_1)

{
  int iVar1;
  undefined8 uVar2;
  longlong lVar3;
  longlong lVar4;
  uint uVar5;
  bool bVar6;
  
  *(uint *)(param_1 + 10) = *(uint *)(param_1 + 10) & 0xfffffffd;
  uVar5 = 0;
  if ((int)param_1[0xd] == 0) {
    lVar3 = 0;
    lVar4 = lVar3;
  }
  else {
    iVar1 = FUN_1400089a0((uint *)(param_1 + 0x1f),(int)param_1[0xd]);
    lVar3 = *param_1;
    for (; lVar4 = lVar3, iVar1 != 0; iVar1 = iVar1 + -1) {
      lVar3 = **(longlong **)(lVar3 + 0x1d0);
    }
  }
  for (; lVar3 != 0; lVar3 = **(longlong **)(lVar3 + 0x1d0)) {
    if (*(longlong *)(lVar3 + 0x1b8) == 0) {
LAB_140017766:
      FUN_140005940(lVar3,4);
      if (*(longlong *)(lVar3 + 0x1b8) != 0) {
        FUN_140016e50();
      }
    }
    else {
      uVar2 = FUN_140016e30();
      bVar6 = (int)uVar2 == 0;
      if (bVar6) goto LAB_140017766;
      uVar5 = bVar6 + 1;
    }
  }
  lVar3 = *param_1;
  do {
    if ((lVar3 == 0) || (lVar3 == lVar4)) {
      *(uint *)(param_1 + 10) = *(uint *)(param_1 + 10) & 0xfffffff7;
      *(uint *)(param_1 + 10) = *(uint *)(param_1 + 10) | (uVar5 & 1) << 3;
      return;
    }
    if (*(longlong *)(lVar3 + 0x1b8) == 0) {
LAB_1400177cb:
      FUN_140005940(lVar3,4);
      if (*(longlong *)(lVar3 + 0x1b8) != 0) {
        FUN_140016e50();
      }
    }
    else {
      uVar2 = FUN_140016e30();
      bVar6 = (int)uVar2 == 0;
      if (bVar6) goto LAB_1400177cb;
      uVar5 = bVar6 + 1;
    }
    lVar3 = **(longlong **)(lVar3 + 0x1d0);
  } while( true );
}


// ==== FUN_140017820 @ 140017820  undefined FUN_140017820(undefined8 param_1, undefined8 param_2, longlong * param_3)

void FUN_140017820(undefined8 param_1,undefined8 param_2,longlong *param_3)

{
  longlong lVar1;
  int local_res18;
  int local_res1c;
  
  lVar1 = FUN_140011170((longlong)(param_3 + 0x10));
  FUN_140010680(lVar1,&local_res18);
  if (param_3[0x20] != 0) {
    FUN_140016e30();
  }
  FUN_140017150((ulonglong *)(param_3 + 1),(ulonglong *)(param_3 + 4),
                (int)((ulonglong)((longlong)(local_res1c / 1000) + (longlong)local_res18 * 1000) /
                     (ulonglong)*(uint *)(param_3 + 9)));
  if (((*(uint *)(param_3 + 10) & 4) != 0) ||
     (((*(uint *)(param_3 + 10) & 1) != 0 && (param_3[0xe] <= param_3[1])))) {
    FUN_1400175a0(param_3);
  }
  if (((*(uint *)(param_3 + 10) & 8) != 0) ||
     (((*(uint *)(param_3 + 10) & 2) != 0 && (param_3[0xe] <= param_3[2])))) {
    FUN_1400176e0(param_3);
  }
  if (param_3[0x20] != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_1400178f0 @ 1400178f0  undefined4 FUN_1400178f0(longlong * param_1, undefined8 * param_2)

undefined4 FUN_1400178f0(longlong *param_1,undefined8 *param_2)

{
  uint uVar1;
  longlong lVar2;
  undefined8 uVar3;
  bool bVar4;
  undefined7 extraout_var;
  void *pvVar5;
  undefined4 uVar6;
  int local_res8;
  int local_resc;
  
  uVar6 = 0xffffffff;
  if (param_1[0x37] != 0) {
    FUN_140016e30();
  }
  if (param_2 == (undefined8 *)0x0) {
    lVar2 = param_1[0x3a];
    if (lVar2 != 0) {
      *(undefined8 *)(lVar2 + 0x30) = 0;
      FUN_140005860((longlong)param_1,2);
      FUN_140005940((longlong)param_1,2);
      bVar4 = FUN_1400110f0(lVar2 + 0x38);
      if ((int)CONCAT71(extraout_var,bVar4) != 0) {
        FUN_140014300((longlong *)(lVar2 + 0x38));
      }
    }
    uVar6 = 0;
    goto LAB_140017ac6;
  }
  FUN_140010680(*param_1,&local_res8);
  uVar1 = *(uint *)(param_2 + 5);
  pvVar5 = (void *)param_1[0x3a];
  if ((pvVar5 != (void *)0x0) && (*(undefined8 **)((longlong)pvVar5 + 0x30) == param_2)) {
    uVar6 = 0;
    goto LAB_140017ac6;
  }
  if (pvVar5 == (void *)0x0) {
    pvVar5 = FUN_140011850(1,0xb0);
    if (pvVar5 == (void *)0x0) goto LAB_140017ac6;
    param_1[0x3a] = (longlong)pvVar5;
  }
  lVar2 = *(longlong *)((longlong)pvVar5 + 0x30);
  *(undefined8 **)((longlong)pvVar5 + 0x30) = param_2;
  if (lVar2 == 0) {
    *(undefined8 *)((longlong)pvVar5 + 0x18) = *param_2;
    uVar3 = param_2[2];
    *(int *)((longlong)pvVar5 + 0x28) =
         (int)((ulonglong)((longlong)(local_resc / 1000) + (longlong)local_res8 * 1000) /
              (ulonglong)uVar1);
    *(undefined8 *)((longlong)pvVar5 + 0x20) = uVar3;
  }
  else {
    if ((longlong)param_2[1] < *(longlong *)((longlong)pvVar5 + 0x18)) {
      *(undefined8 *)((longlong)pvVar5 + 0x18) = param_2[1];
    }
    if ((longlong)param_2[3] < *(longlong *)((longlong)pvVar5 + 0x20)) {
      *(undefined8 *)((longlong)pvVar5 + 0x20) = param_2[3];
    }
    FUN_140014300((longlong *)((longlong)pvVar5 + 0x38));
  }
  FUN_140010e40((undefined *)((longlong)pvVar5 + 0x38),*param_1,0xffffffffffffffff,0x40,
                FUN_140017430,(undefined *)param_1);
  bVar4 = *(longlong *)((longlong)pvVar5 + 0x18) < 1;
  if (bVar4) {
    FUN_1400057f0((longlong)param_1,2);
  }
  else {
    FUN_140005860((longlong)param_1,2);
  }
  if (*(longlong *)((longlong)pvVar5 + 0x20) < 1) {
    FUN_1400058d0((longlong)param_1,2);
LAB_140017ab2:
    FUN_140015e10((longlong *)((longlong)pvVar5 + 0x38),param_2 + 4);
  }
  else {
    FUN_140005940((longlong)param_1,2);
    if (bVar4) goto LAB_140017ab2;
  }
  uVar6 = 0;
LAB_140017ac6:
  if (param_1[0x37] != 0) {
    FUN_140016e50();
  }
  return uVar6;
}


// ==== FUN_140017b40 @ 140017b40  undefined FUN_140017b40(void * param_1)

void FUN_140017b40(void *param_1)

{
  if (*(longlong *)((longlong)param_1 + 0x100) != 0) {
    FUN_140016e30();
  }
  FUN_140014300((longlong *)((longlong)param_1 + 0x80));
  if (*(longlong *)((longlong)param_1 + 0x100) != 0) {
    FUN_140016e50();
  }
  if (*(longlong *)((longlong)param_1 + 0x100) != 0) {
    FUN_140016e10();
  }
  FUN_1400119c0(param_1);
  return;
}


// ==== FUN_140017ba0 @ 140017ba0  undefined8 FUN_140017ba0(longlong param_1, int param_2)

undefined8 FUN_140017ba0(longlong param_1,int param_2)

{
  longlong lVar1;
  longlong *plVar2;
  
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  if ((*(longlong *)(param_1 + 0x1d0) != 0) &&
     (lVar1 = *(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x10), lVar1 != 0)) {
    if (*(longlong *)(lVar1 + 0x100) != 0) {
      FUN_140016e30();
    }
    *(undefined8 *)(*(longlong *)(param_1 + 0x1d0) + 0x10) = 0;
    *(int *)(lVar1 + 0x68) = *(int *)(lVar1 + 0x68) + -1;
    plVar2 = *(longlong **)(param_1 + 0x1d0);
    if (*plVar2 != 0) {
      *(longlong *)(*(longlong *)(*plVar2 + 0x1d0) + 8) = plVar2[1];
    }
    *(undefined8 *)(*(undefined8 **)(param_1 + 0x1d0))[1] = **(undefined8 **)(param_1 + 0x1d0);
    if (*(longlong *)(lVar1 + 0x100) != 0) {
      FUN_140016e50();
    }
  }
  if (param_2 != 0) {
    FUN_140005860(param_1,4);
    FUN_140005940(param_1,4);
  }
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return 0;
}


// ==== FUN_140017ca0 @ 140017ca0  undefined8 FUN_140017ca0(longlong param_1, ulonglong param_2)

undefined8 FUN_140017ca0(longlong param_1,ulonglong param_2)

{
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  if ((param_2 == 0) || (0x7fffffffffffffff < param_2)) {
    *(undefined8 *)(param_1 + 0x1c0) = 0x4000;
  }
  else {
    *(ulonglong *)(param_1 + 0x1c0) = param_2;
  }
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return 0;
}


// ==== FUN_140017d10 @ 140017d10  undefined8 FUN_140017d10(longlong param_1, ulonglong param_2)

undefined8 FUN_140017d10(longlong param_1,ulonglong param_2)

{
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  if ((param_2 == 0) || (0x7fffffffffffffff < param_2)) {
    *(undefined8 *)(param_1 + 0x1c8) = 0x4000;
  }
  else {
    *(ulonglong *)(param_1 + 0x1c8) = param_2;
  }
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return 0;
}


// ==== FUN_140017d80 @ 140017d80  undefined8 FUN_140017d80(longlong param_1)

undefined8 FUN_140017d80(longlong param_1)

{
  undefined8 uVar1;
  
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  uVar1 = *(undefined8 *)(param_1 + 0x1c0);
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return uVar1;
}


// ==== FUN_140017dd0 @ 140017dd0  undefined8 FUN_140017dd0(longlong param_1)

undefined8 FUN_140017dd0(longlong param_1)

{
  undefined8 uVar1;
  
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  uVar1 = *(undefined8 *)(param_1 + 0x1c8);
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return uVar1;
}


// ==== FUN_140017e20 @ 140017e20  undefined8 FUN_140017e20(longlong param_1)

undefined8 FUN_140017e20(longlong param_1)

{
  undefined8 uVar1;
  
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  if (*(longlong *)(param_1 + 0x1d0) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined8 *)(*(longlong *)(param_1 + 0x1d0) + 0x30);
  }
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return uVar1;
}


// ==== FUN_140017e80 @ 140017e80  undefined8 FUN_140017e80(longlong param_1)

undefined8 FUN_140017e80(longlong param_1)

{
  undefined8 uVar1;
  
  if (*(longlong *)(param_1 + 0x100) != 0) {
    FUN_140016e30();
  }
  uVar1 = *(undefined8 *)(param_1 + 8);
  if (*(longlong *)(param_1 + 0x100) != 0) {
    FUN_140016e50();
  }
  return uVar1;
}


// ==== FUN_140017ed0 @ 140017ed0  undefined8 FUN_140017ed0(longlong param_1)

undefined8 FUN_140017ed0(longlong param_1)

{
  undefined8 uVar1;
  
  if (*(longlong *)(param_1 + 0x100) != 0) {
    FUN_140016e30();
  }
  uVar1 = *(undefined8 *)(param_1 + 0x10);
  if (*(longlong *)(param_1 + 0x100) != 0) {
    FUN_140016e50();
  }
  return uVar1;
}


// ==== FUN_140017f20 @ 140017f20  undefined8 FUN_140017f20(longlong param_1, longlong param_2)

undefined8 FUN_140017f20(longlong param_1,longlong param_2)

{
  longlong lVar1;
  longlong lVar2;
  undefined8 *puVar3;
  undefined8 uVar4;
  
  uVar4 = 0;
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  lVar1 = *(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x18);
  *(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x18) = lVar1 - param_2;
  lVar2 = *(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x18);
  if (lVar1 < 1) {
    if (0 < lVar2) {
      if ((*(byte *)(param_1 + 0x178) & 2) == 0) {
        FUN_140014300((longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x38));
      }
      FUN_140005860(param_1,2);
      uVar4 = 0;
    }
  }
  else if (lVar2 < 1) {
    FUN_1400057f0(param_1,2);
    puVar3 = FUN_140015e10((longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x38),
                           (ulonglong *)
                           (*(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x30) + 0x20));
    if ((int)puVar3 < 0) {
      uVar4 = 0xffffffff;
    }
  }
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return uVar4;
}


// ==== FUN_140017ff0 @ 140017ff0  undefined8 FUN_140017ff0(longlong param_1, longlong param_2)

undefined8 FUN_140017ff0(longlong param_1,longlong param_2)

{
  longlong lVar1;
  longlong lVar2;
  undefined8 *puVar3;
  undefined8 uVar4;
  
  uVar4 = 0;
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  lVar1 = *(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x20);
  *(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x20) = lVar1 - param_2;
  lVar2 = *(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x20);
  if (lVar1 < 1) {
    if (0 < lVar2) {
      if ((*(byte *)(param_1 + 0x176) & 2) == 0) {
        FUN_140014300((longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x38));
      }
      FUN_140005940(param_1,2);
      uVar4 = 0;
    }
  }
  else if (lVar2 < 1) {
    FUN_1400058d0(param_1,2);
    puVar3 = FUN_140015e10((longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x38),
                           (ulonglong *)
                           (*(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x30) + 0x20));
    if ((int)puVar3 < 0) {
      uVar4 = 0xffffffff;
    }
  }
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return uVar4;
}


// ==== FUN_1400180c0 @ 1400180c0  undefined8 FUN_1400180c0(longlong * param_1, longlong param_2)

undefined8 FUN_1400180c0(longlong *param_1,longlong param_2)

{
  longlong lVar1;
  longlong lVar2;
  
  if (param_1[0x20] != 0) {
    FUN_140016e30();
  }
  lVar1 = param_1[1];
  lVar2 = lVar1 - param_2;
  param_1[1] = lVar2;
  if (lVar1 < 1) {
    if (0 < lVar2) {
      FUN_1400175a0(param_1);
    }
  }
  else if (lVar2 < 1) {
    FUN_140017330(param_1);
  }
  if (param_1[0x20] != 0) {
    FUN_140016e50();
  }
  return 0;
}


// ==== FUN_140018140 @ 140018140  undefined8 FUN_140018140(longlong * param_1, longlong param_2)

undefined8 FUN_140018140(longlong *param_1,longlong param_2)

{
  longlong lVar1;
  longlong lVar2;
  
  if (param_1[0x20] != 0) {
    FUN_140016e30();
  }
  lVar1 = param_1[2];
  lVar2 = lVar1 - param_2;
  param_1[2] = lVar2;
  if (lVar1 < 1) {
    if (0 < lVar2) {
      FUN_1400176e0(param_1);
    }
  }
  else if (lVar2 < 1) {
    FUN_1400173b0(param_1);
  }
  if (param_1[0x20] != 0) {
    FUN_140016e50();
  }
  return 0;
}


// ==== FUN_1400181f0 @ 1400181f0  undefined8 FUN_1400181f0(longlong param_1)

undefined8 FUN_1400181f0(longlong param_1)

{
  *(undefined8 *)(param_1 + 0x1d0) = 0;
  *(undefined8 *)(param_1 + 0x1c0) = 0x4000;
  *(undefined8 *)(param_1 + 0x1c8) = 0x4000;
  return 0;
}


// ==== FUN_140018220 @ 140018220  undefined FUN_140018220(longlong * param_1)

void FUN_140018220(longlong *param_1)

{
  longlong lVar1;
  int iVar2;
  int local_res8;
  int local_resc;
  
  FUN_140010680(*param_1,&local_res8);
  lVar1 = param_1[0x3a];
  iVar2 = (int)((ulonglong)((longlong)(local_resc / 1000) + (longlong)local_res8 * 1000) /
               (ulonglong)*(uint *)(*(longlong *)(lVar1 + 0x30) + 0x28));
  if (iVar2 != *(int *)(lVar1 + 0x28)) {
    FUN_140017150((ulonglong *)(lVar1 + 0x18),*(ulonglong **)(lVar1 + 0x30),iVar2);
  }
  return;
}


// ==== FUN_140018290 @ 140018290  longlong FUN_140018290(longlong * param_1, int param_2)

longlong FUN_140018290(longlong *param_1,int param_2)

{
  uint uVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  
  if (param_2 == 0) {
    lVar4 = param_1[0x38];
  }
  else {
    lVar4 = param_1[0x39];
  }
  lVar2 = param_1[0x3a];
  if (lVar2 != 0) {
    if (*(longlong *)(lVar2 + 0x30) != 0) {
      FUN_140018220(param_1);
      if (param_2 == 0) {
        lVar2 = param_1[0x3a];
        lVar4 = *(longlong *)(lVar2 + 0x18);
      }
      else {
        lVar2 = param_1[0x3a];
        lVar4 = *(longlong *)(lVar2 + 0x20);
      }
    }
    lVar2 = *(longlong *)(lVar2 + 0x10);
    lVar5 = 0;
    if (lVar2 != 0) {
      if (*(longlong *)(lVar2 + 0x100) != 0) {
        FUN_140016e30();
      }
      if (param_2 == 0) {
        uVar1 = *(uint *)(lVar2 + 0x50);
      }
      else {
        uVar1 = *(uint *)(lVar2 + 0x50) >> 1;
      }
      if ((uVar1 & 1) == 0) {
        if (param_2 == 0) {
          lVar3 = *(longlong *)(lVar2 + 8);
        }
        else {
          lVar3 = *(longlong *)(lVar2 + 0x10);
        }
        lVar3 = lVar3 / (longlong)*(int *)(lVar2 + 0x68);
        if (lVar3 < *(longlong *)(lVar2 + 0x70)) {
          lVar3 = *(longlong *)(lVar2 + 0x70);
        }
      }
      else {
        lVar3 = lVar5;
        if (param_2 == 0) {
          FUN_1400057f0((longlong)param_1,4);
        }
        else {
          FUN_1400058d0((longlong)param_1,4);
        }
      }
      if (*(longlong *)(lVar2 + 0x100) != 0) {
        FUN_140016e50();
      }
      if (lVar3 < lVar4) {
        lVar4 = lVar3;
      }
    }
    if (lVar4 < 0) {
      lVar4 = lVar5;
    }
  }
  return lVar4;
}


// ==== FUN_1400183c0 @ 1400183c0  longlong FUN_1400183c0(longlong * param_1)

longlong FUN_1400183c0(longlong *param_1)

{
  longlong lVar1;
  longlong lVar2;
  longlong lVar3;
  
  lVar1 = param_1[0x3a];
  lVar3 = param_1[0x38];
  if (lVar1 != 0) {
    if (*(longlong *)(lVar1 + 0x30) != 0) {
      FUN_140018220(param_1);
      lVar1 = param_1[0x3a];
      lVar3 = *(longlong *)(lVar1 + 0x18);
    }
    lVar1 = *(longlong *)(lVar1 + 0x10);
    if (lVar1 != 0) {
      if (*(longlong *)(lVar1 + 0x100) != 0) {
        FUN_140016e30();
      }
      if ((*(byte *)(lVar1 + 0x50) & 1) == 0) {
        lVar2 = *(longlong *)(lVar1 + 8) / (longlong)*(int *)(lVar1 + 0x68);
        if (lVar2 < *(longlong *)(lVar1 + 0x70)) {
          lVar2 = *(longlong *)(lVar1 + 0x70);
        }
      }
      else {
        FUN_1400057f0((longlong)param_1,4);
        lVar2 = 0;
      }
      if (*(longlong *)(lVar1 + 0x100) != 0) {
        FUN_140016e50();
      }
      if (lVar2 < lVar3) {
        lVar3 = lVar2;
      }
    }
    if (lVar3 < 0) {
      lVar3 = 0;
    }
  }
  return lVar3;
}


// ==== FUN_140018490 @ 140018490  longlong FUN_140018490(longlong * param_1)

longlong FUN_140018490(longlong *param_1)

{
  longlong lVar1;
  longlong lVar2;
  longlong lVar3;
  
  lVar1 = param_1[0x3a];
  lVar3 = param_1[0x39];
  if (lVar1 != 0) {
    if (*(longlong *)(lVar1 + 0x30) != 0) {
      FUN_140018220(param_1);
      lVar1 = param_1[0x3a];
      lVar3 = *(longlong *)(lVar1 + 0x20);
    }
    lVar1 = *(longlong *)(lVar1 + 0x10);
    if (lVar1 != 0) {
      if (*(longlong *)(lVar1 + 0x100) != 0) {
        FUN_140016e30();
      }
      if ((*(byte *)(lVar1 + 0x50) & 2) == 0) {
        lVar2 = *(longlong *)(lVar1 + 0x10) / (longlong)*(int *)(lVar1 + 0x68);
        if (lVar2 < *(longlong *)(lVar1 + 0x70)) {
          lVar2 = *(longlong *)(lVar1 + 0x70);
        }
      }
      else {
        FUN_1400058d0((longlong)param_1,4);
        lVar2 = 0;
      }
      if (*(longlong *)(lVar1 + 0x100) != 0) {
        FUN_140016e50();
      }
      if (lVar2 < lVar3) {
        lVar3 = lVar2;
      }
    }
    if (lVar3 < 0) {
      lVar3 = 0;
    }
  }
  return lVar3;
}


// ==== FUN_140018560 @ 140018560  longlong FUN_140018560(longlong param_1, longlong param_2)

longlong FUN_140018560(longlong param_1,longlong param_2)

{
  longlong *plVar1;
  longlong lVar2;
  undefined8 *puVar3;
  longlong lVar4;
  
  lVar2 = *(longlong *)(param_1 + 0x1d0);
  lVar4 = 0;
  if (lVar2 == 0) {
    return lVar2;
  }
  if (*(longlong *)(lVar2 + 0x30) != 0) {
    *(longlong *)(lVar2 + 0x18) = *(longlong *)(lVar2 + 0x18) - param_2;
    if (*(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x18) < 1) {
      FUN_1400057f0(param_1,2);
      puVar3 = FUN_140015e10((longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x38),
                             (ulonglong *)
                             (*(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x30) + 0x20));
      if ((int)puVar3 < 0) {
        lVar4 = 0xffffffff;
      }
    }
    else if ((*(byte *)(param_1 + 0x176) & 2) != 0) {
      if ((*(byte *)(param_1 + 0x178) & 2) == 0) {
        FUN_140014300((longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x38));
      }
      FUN_140005860(param_1,2);
      lVar4 = 0;
    }
  }
  lVar2 = *(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x10);
  if (lVar2 != 0) {
    if (*(longlong *)(lVar2 + 0x100) != 0) {
      FUN_140016e30();
    }
    plVar1 = (longlong *)(*(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x10) + 8);
    *plVar1 = *plVar1 - param_2;
    plVar1 = (longlong *)(*(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x10) + 0x58);
    *plVar1 = *plVar1 + param_2;
    plVar1 = *(longlong **)(*(longlong *)(param_1 + 0x1d0) + 0x10);
    if (plVar1[1] < 1) {
      FUN_140017330(plVar1);
    }
    else if ((*(byte *)(plVar1 + 10) & 1) != 0) {
      FUN_1400175a0(plVar1);
    }
    if (*(longlong *)(*(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x10) + 0x100) != 0) {
      FUN_140016e50();
    }
  }
  return lVar4;
}


// ==== FUN_1400186a0 @ 1400186a0  longlong FUN_1400186a0(longlong param_1, longlong param_2)

longlong FUN_1400186a0(longlong param_1,longlong param_2)

{
  longlong *plVar1;
  longlong lVar2;
  undefined8 *puVar3;
  longlong lVar4;
  
  lVar2 = *(longlong *)(param_1 + 0x1d0);
  lVar4 = 0;
  if (lVar2 == 0) {
    return lVar2;
  }
  if (*(longlong *)(lVar2 + 0x30) != 0) {
    *(longlong *)(lVar2 + 0x20) = *(longlong *)(lVar2 + 0x20) - param_2;
    if (*(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x20) < 1) {
      FUN_1400058d0(param_1,2);
      puVar3 = FUN_140015e10((longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x38),
                             (ulonglong *)
                             (*(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x30) + 0x20));
      if ((int)puVar3 < 0) {
        lVar4 = 0xffffffff;
      }
    }
    else if ((*(byte *)(param_1 + 0x178) & 2) != 0) {
      if ((*(byte *)(param_1 + 0x176) & 2) == 0) {
        FUN_140014300((longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x38));
      }
      FUN_140005940(param_1,2);
      lVar4 = 0;
    }
  }
  lVar2 = *(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x10);
  if (lVar2 != 0) {
    if (*(longlong *)(lVar2 + 0x100) != 0) {
      FUN_140016e30();
    }
    plVar1 = (longlong *)(*(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x10) + 0x10);
    *plVar1 = *plVar1 - param_2;
    plVar1 = (longlong *)(*(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x10) + 0x60);
    *plVar1 = *plVar1 + param_2;
    plVar1 = *(longlong **)(*(longlong *)(param_1 + 0x1d0) + 0x10);
    if (plVar1[2] < 1) {
      FUN_1400173b0(plVar1);
    }
    else if ((*(byte *)(plVar1 + 10) & 2) != 0) {
      FUN_1400176e0(plVar1);
    }
    if (*(longlong *)(*(longlong *)(*(longlong *)(param_1 + 0x1d0) + 0x10) + 0x100) != 0) {
      FUN_140016e50();
    }
  }
  return lVar4;
}


// ==== FUN_1400187e0 @ 1400187e0  undefined8 * FUN_1400187e0(longlong param_1, undefined8 * param_2)

undefined8 * FUN_1400187e0(longlong param_1,undefined8 *param_2)

{
  uint uVar1;
  int iVar2;
  undefined8 *puVar3;
  undefined8 uVar4;
  longlong lVar5;
  ulonglong uVar6;
  int local_res10;
  int local_res14;
  
  FUN_140010680(param_1,&local_res10);
  lVar5 = (longlong)local_res10;
  iVar2 = local_res14 / 1000;
  uVar1 = *(uint *)(param_2 + 5);
  puVar3 = (undefined8 *)FUN_140011850(1,0x108);
  if (puVar3 != (undefined8 *)0x0) {
    puVar3[4] = *param_2;
    puVar3[5] = param_2[1];
    puVar3[6] = param_2[2];
    puVar3[7] = param_2[3];
    puVar3[8] = param_2[4];
    uVar4 = param_2[5];
    *puVar3 = 0;
    puVar3[9] = uVar4;
    puVar3[1] = *param_2;
    uVar4 = param_2[2];
    *(int *)(puVar3 + 3) = (int)((ulonglong)((longlong)iVar2 + lVar5 * 1000) / (ulonglong)uVar1);
    puVar3[2] = uVar4;
    FUN_140010e40((undefined *)(puVar3 + 0x10),param_1,0xffffffffffffffff,0x50,FUN_140017820,
                  (undefined *)puVar3);
    FUN_140015e10(puVar3 + 0x10,param_2 + 4);
    uVar4 = FUN_140016df0();
    puVar3[0xf] = 0x40;
    puVar3[0x20] = uVar4;
    uVar6 = 0x40;
    if ((ulonglong)puVar3[4] < 0x40) {
      uVar6 = puVar3[4];
    }
    if ((ulonglong)puVar3[6] < uVar6) {
      uVar6 = puVar3[6];
    }
    puVar3[0xe] = uVar6;
    FUN_140008930((int *)(puVar3 + 0x1f),(int)puVar3 + local_res14 + local_res10);
  }
  return puVar3;
}


// ==== FUN_140018940 @ 140018940  undefined8 FUN_140018940(longlong param_1, undefined8 * param_2)

undefined8 FUN_140018940(longlong param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  bool bVar2;
  
  if ((param_1 != 0) && (param_2 != (undefined8 *)0x0)) {
    if (*(longlong *)(param_1 + 0x100) != 0) {
      FUN_140016e30();
    }
    bVar2 = false;
    if (*(int *)(param_1 + 0x40) == *(int *)(param_2 + 4)) {
      bVar2 = *(int *)(param_1 + 0x44) == *(int *)((longlong)param_2 + 0x24);
    }
    *(undefined8 *)(param_1 + 0x20) = *param_2;
    *(undefined8 *)(param_1 + 0x28) = param_2[1];
    *(undefined8 *)(param_1 + 0x30) = param_2[2];
    *(undefined8 *)(param_1 + 0x38) = param_2[3];
    *(undefined8 *)(param_1 + 0x40) = param_2[4];
    *(undefined8 *)(param_1 + 0x48) = param_2[5];
    if ((longlong)param_2[1] < *(longlong *)(param_1 + 8)) {
      *(undefined8 *)(param_1 + 8) = param_2[1];
    }
    if ((longlong)param_2[3] < *(longlong *)(param_1 + 0x10)) {
      *(undefined8 *)(param_1 + 0x10) = param_2[3];
    }
    if (!bVar2) {
      FUN_140015e10((longlong *)(param_1 + 0x80),param_2 + 4);
    }
    uVar1 = *(ulonglong *)(param_1 + 0x78);
    if (uVar1 < 0x8000000000000000) {
      if (*(ulonglong *)(param_1 + 0x20) < uVar1) {
        uVar1 = *(ulonglong *)(param_1 + 0x20);
      }
      if (*(ulonglong *)(param_1 + 0x30) < uVar1) {
        uVar1 = *(ulonglong *)(param_1 + 0x30);
      }
      *(ulonglong *)(param_1 + 0x70) = uVar1;
    }
    if (*(longlong *)(param_1 + 0x100) != 0) {
      FUN_140016e50();
    }
    return 0;
  }
  return 0xffffffff;
}


// ==== FUN_140018a60 @ 140018a60  undefined8 FUN_140018a60(longlong * param_1)

undefined8 FUN_140018a60(longlong *param_1)

{
  undefined8 uVar1;
  
  if (param_1[0x37] != 0) {
    FUN_140016e30();
  }
  if ((param_1[0x3a] == 0) || (*(longlong *)(param_1[0x3a] + 0x30) == 0)) {
    uVar1 = 0x7fffffffffffffff;
  }
  else {
    FUN_140018220(param_1);
    uVar1 = *(undefined8 *)(param_1[0x3a] + 0x18);
  }
  if (param_1[0x37] != 0) {
    FUN_140016e50();
  }
  return uVar1;
}


// ==== FUN_140018ae0 @ 140018ae0  undefined8 FUN_140018ae0(longlong * param_1)

undefined8 FUN_140018ae0(longlong *param_1)

{
  undefined8 uVar1;
  
  if (param_1[0x37] != 0) {
    FUN_140016e30();
  }
  if ((param_1[0x3a] == 0) || (*(longlong *)(param_1[0x3a] + 0x30) == 0)) {
    uVar1 = 0x7fffffffffffffff;
  }
  else {
    FUN_140018220(param_1);
    uVar1 = *(undefined8 *)(param_1[0x3a] + 0x20);
  }
  if (param_1[0x37] != 0) {
    FUN_140016e50();
  }
  return uVar1;
}


// ==== FUN_140018b60 @ 140018b60  longlong FUN_140018b60(longlong * param_1)

longlong FUN_140018b60(longlong *param_1)

{
  longlong lVar1;
  
  if (param_1[0x37] != 0) {
    FUN_140016e30();
  }
  lVar1 = FUN_1400183c0(param_1);
  if (param_1[0x37] != 0) {
    FUN_140016e50();
  }
  return lVar1;
}


// ==== FUN_140018bb0 @ 140018bb0  longlong FUN_140018bb0(longlong * param_1)

longlong FUN_140018bb0(longlong *param_1)

{
  longlong lVar1;
  
  if (param_1[0x37] != 0) {
    FUN_140016e30();
  }
  lVar1 = FUN_140018490(param_1);
  if (param_1[0x37] != 0) {
    FUN_140016e50();
  }
  return lVar1;
}


// ==== FUN_140018c00 @ 140018c00  undefined8 FUN_140018c00(longlong * param_1, longlong * param_2)

undefined8 FUN_140018c00(longlong *param_1,longlong *param_2)

{
  uint uVar1;
  longlong lVar2;
  void *pvVar3;
  
  if (param_1[0x37] != 0) {
    FUN_140016e30();
  }
  if (param_1[0x3a] == 0) {
    pvVar3 = FUN_140011850(1,0xb0);
    if (pvVar3 == (void *)0x0) {
      if (param_1[0x37] != 0) {
        FUN_140016e50();
      }
      return 0xffffffff;
    }
    FUN_140010e40((undefined *)((longlong)pvVar3 + 0x38),*param_1,0xffffffffffffffff,0x40,
                  FUN_140017430,(undefined *)param_1);
    param_1[0x3a] = (longlong)pvVar3;
  }
  if (*(longlong **)(param_1[0x3a] + 0x10) == param_2) {
    lVar2 = param_1[0x37];
  }
  else {
    if (*(longlong **)(param_1[0x3a] + 0x10) != (longlong *)0x0) {
      FUN_140017ba0((longlong)param_1,1);
    }
    if (param_2[0x20] != 0) {
      FUN_140016e30();
    }
    *(longlong **)(param_1[0x3a] + 0x10) = param_2;
    *(int *)(param_2 + 0xd) = (int)param_2[0xd] + 1;
    *(longlong *)param_1[0x3a] = *param_2;
    if (*(longlong *)param_1[0x3a] != 0) {
      *(longlong **)(*(longlong *)(*param_2 + 0x1d0) + 8) = (longlong *)param_1[0x3a];
    }
    *param_2 = (longlong)param_1;
    *(longlong **)(param_1[0x3a] + 8) = param_2;
    uVar1 = *(uint *)(param_2 + 10);
    if (param_2[0x20] != 0) {
      FUN_140016e50();
    }
    if ((uVar1 & 1) != 0) {
      FUN_1400057f0((longlong)param_1,4);
    }
    if ((uVar1 >> 1 & 1) != 0) {
      FUN_1400058d0((longlong)param_1,4);
    }
    lVar2 = param_1[0x37];
  }
  if (lVar2 != 0) {
    FUN_140016e50();
  }
  return 0;
}


// ==== FUN_140018dc0 @ 140018dc0  undefined FUN_140018dc0(int param_1)

void FUN_140018dc0(int param_1)

{
  if (DAT_140104060 != (code *)0x0) {
    (*DAT_140104060)();
                    /* WARNING: Subroutine does not return */
    exit(param_1);
  }
  if (param_1 == -0x21522153) {
                    /* WARNING: Could not recover jumptable at 0x000140018dec. Too many branches */
                    /* WARNING: Subroutine does not return */
                    /* WARNING: Treating indirect jump as call */
    abort();
    return;
  }
                    /* WARNING: Subroutine does not return */
  exit(param_1);
}


// ==== FUN_140018e10 @ 140018e10  undefined FUN_140018e10(void)

void FUN_140018e10(void)

{
  FILE *pFVar1;
  
  if (DAT_140104068 == (code *)0x0) {
    pFVar1 = __iob_func();
                    /* WARNING: Could not recover jumptable at 0x000140018e91. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    fprintf(pFVar1 + 2,"[%s] %s\n");
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000140018e2a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*DAT_140104068)();
  return;
}


// ==== FUN_140018ea0 @ 140018ea0  undefined FUN_140018ea0(int param_1, longlong param_2, char * param_3, va_list param_4)

void FUN_140018ea0(int param_1,longlong param_2,char *param_3,va_list param_4)

{
  FILE *pFVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  char *pcVar4;
  undefined1 auStack_458 [31];
  char acStack_439 [1025];
  ulonglong local_38;
  
  if (param_1 != 0) {
    local_38 = DAT_140103510 ^ (ulonglong)auStack_458;
    if (param_3 == (char *)0x0) {
      acStack_439[1] = 0;
    }
    else {
      FUN_1400085e0(acStack_439 + 1,0x400,param_3,param_4);
    }
    if (param_2 != 0) {
      uVar2 = 0xffffffffffffffff;
      pcVar4 = acStack_439;
      do {
        pcVar4 = pcVar4 + 1;
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
      } while (*pcVar4 != '\0');
      uVar3 = ~uVar2 - 1;
      if (uVar3 < 0x3fd) {
        FUN_140009250(acStack_439 + ~uVar2,0x400 - uVar3,": %s",param_2);
      }
    }
    if (DAT_140104068 == (code *)0x0) {
      pFVar1 = __iob_func();
      fprintf(pFVar1 + 2,"[%s] %s\n");
    }
    else {
      (*DAT_140104068)(param_1,acStack_439 + 1);
    }
    __security_check_cookie(local_38 ^ (ulonglong)auStack_458);
  }
  return;
}


// ==== FUN_140018fd0 @ 140018fd0  undefined FUN_140018fd0(int param_1, char * param_2, undefined8 param_3, undefined8 param_4)

void FUN_140018fd0(int param_1,char *param_2,undefined8 param_3,undefined8 param_4)

{
  int *piVar1;
  char *pcVar2;
  undefined8 local_res18;
  undefined8 local_res20;
  
  local_res18 = param_3;
  local_res20 = param_4;
  piVar1 = _errno();
  pcVar2 = strerror(*piVar1);
  FUN_140018ea0(3,(longlong)pcVar2,param_2,(va_list)&local_res18);
  if (DAT_140104060 != (code *)0x0) {
    (*DAT_140104060)(param_1);
                    /* WARNING: Subroutine does not return */
    exit(param_1);
  }
  if (param_1 == -0x21522153) {
                    /* WARNING: Subroutine does not return */
    abort();
  }
                    /* WARNING: Subroutine does not return */
  exit(param_1);
}


// ==== FUN_140019050 @ 140019050  undefined FUN_140019050(char * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_140019050(char *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  int *piVar1;
  char *pcVar2;
  undefined8 local_res10;
  undefined8 local_res18;
  undefined8 local_res20;
  
  local_res10 = param_2;
  local_res18 = param_3;
  local_res20 = param_4;
  piVar1 = _errno();
  pcVar2 = strerror(*piVar1);
  FUN_140018ea0(2,(longlong)pcVar2,param_1,(va_list)&local_res10);
  return;
}


// ==== FUN_1400190a0 @ 1400190a0  undefined FUN_1400190a0(int param_1, longlong param_2, char * param_3, undefined8 param_4)

void FUN_1400190a0(int param_1,longlong param_2,char *param_3,undefined8 param_4)

{
  uint uVar1;
  char *pcVar2;
  undefined8 local_res20;
  
  local_res20 = param_4;
  uVar1 = FUN_140007540(param_2);
  pcVar2 = FUN_14000aa90(uVar1);
  FUN_140018ea0(3,(longlong)pcVar2,param_3,(va_list)&local_res20);
  if (DAT_140104060 != (code *)0x0) {
    (*DAT_140104060)(param_1);
                    /* WARNING: Subroutine does not return */
    exit(param_1);
  }
  if (param_1 == -0x21522153) {
                    /* WARNING: Subroutine does not return */
    abort();
  }
                    /* WARNING: Subroutine does not return */
  exit(param_1);
}


// ==== FUN_140019120 @ 140019120  undefined FUN_140019120(longlong param_1, char * param_2, undefined8 param_3, undefined8 param_4)

void FUN_140019120(longlong param_1,char *param_2,undefined8 param_3,undefined8 param_4)

{
  uint uVar1;
  char *pcVar2;
  undefined8 local_res18;
  undefined8 local_res20;
  
  local_res18 = param_3;
  local_res20 = param_4;
  uVar1 = FUN_140007540(param_1);
  pcVar2 = FUN_14000aa90(uVar1);
  FUN_140018ea0(2,(longlong)pcVar2,param_2,(va_list)&local_res18);
  return;
}


// ==== FUN_140019160 @ 140019160  undefined FUN_140019160(int param_1, char * param_2, undefined8 param_3, undefined8 param_4)

void FUN_140019160(int param_1,char *param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 local_res18;
  undefined8 local_res20;
  
  local_res18 = param_3;
  local_res20 = param_4;
  FUN_140018ea0(3,0,param_2,(va_list)&local_res18);
  if (DAT_140104060 != (code *)0x0) {
    (*DAT_140104060)(param_1);
                    /* WARNING: Subroutine does not return */
    exit(param_1);
  }
  if (param_1 == -0x21522153) {
                    /* WARNING: Subroutine does not return */
    abort();
  }
                    /* WARNING: Subroutine does not return */
  exit(param_1);
}


// ==== FUN_1400191c0 @ 1400191c0  undefined FUN_1400191c0(char * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_1400191c0(char *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 local_res10;
  undefined8 local_res18;
  undefined8 local_res20;
  
  local_res10 = param_2;
  local_res18 = param_3;
  local_res20 = param_4;
  FUN_140018ea0(2,0,param_1,(va_list)&local_res10);
  return;
}


// ==== FUN_1400191f0 @ 1400191f0  undefined FUN_1400191f0(char * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_1400191f0(char *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 local_res10;
  undefined8 local_res18;
  undefined8 local_res20;
  
  local_res10 = param_2;
  local_res18 = param_3;
  local_res20 = param_4;
  FUN_140018ea0(1,0,param_1,(va_list)&local_res10);
  return;
}


// ==== FUN_140019220 @ 140019220  undefined FUN_140019220(char * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_140019220(char *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 local_res10;
  undefined8 local_res18;
  undefined8 local_res20;
  
  local_res10 = param_2;
  local_res18 = param_3;
  local_res20 = param_4;
  FUN_140018ea0(0,0,param_1,(va_list)&local_res10);
  return;
}


// ==== FUN_140019280 @ 140019280  undefined FUN_140019280(longlong param_1, int param_2)

void FUN_140019280(longlong param_1,int param_2)

{
  int iVar1;
  char cVar2;
  int iVar3;
  
  DAT_140104090 = DAT_140104090 - 1;
  iVar3 = 2;
  do {
    DAT_140104090 = DAT_140104090 + 1;
    cVar2 = (&DAT_140104092)[DAT_140104090];
    DAT_140104091 = DAT_140104091 + *(char *)((iVar3 + -2) % param_2 + param_1) + cVar2;
    (&DAT_140104092)[DAT_140104090] = (&DAT_140104092)[DAT_140104091];
    (&DAT_140104092)[DAT_140104091] = cVar2;
    DAT_140104090 = DAT_140104090 + 1;
    cVar2 = (&DAT_140104092)[DAT_140104090];
    DAT_140104091 = DAT_140104091 + *(char *)((iVar3 + -1) % param_2 + param_1) + cVar2;
    (&DAT_140104092)[DAT_140104090] = (&DAT_140104092)[DAT_140104091];
    (&DAT_140104092)[DAT_140104091] = cVar2;
    DAT_140104090 = DAT_140104090 + 1;
    cVar2 = (&DAT_140104092)[DAT_140104090];
    DAT_140104091 = DAT_140104091 + *(char *)(iVar3 % param_2 + param_1) + cVar2;
    (&DAT_140104092)[DAT_140104090] = (&DAT_140104092)[DAT_140104091];
    (&DAT_140104092)[DAT_140104091] = cVar2;
    DAT_140104090 = DAT_140104090 + 1;
    cVar2 = (&DAT_140104092)[DAT_140104090];
    DAT_140104091 = DAT_140104091 + *(char *)((iVar3 + 1) % param_2 + param_1) + cVar2;
    (&DAT_140104092)[DAT_140104090] = (&DAT_140104092)[DAT_140104091];
    (&DAT_140104092)[DAT_140104091] = cVar2;
    iVar1 = iVar3 + 2;
    iVar3 = iVar3 + 4;
  } while (iVar1 < 0x100);
  DAT_140104091 = DAT_140104090;
  return;
}


// ==== FUN_140019420 @ 140019420  undefined FUN_140019420(void)

void FUN_140019420(void)

{
  BOOL BVar1;
  DWORD DVar2;
  undefined1 auStackY_68 [32];
  BYTE local_38 [32];
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStackY_68;
  if (DAT_140104194 == 0) {
    BVar1 = CryptAcquireContextA(&DAT_140104088,(LPCSTR)0x0,(LPCSTR)0x0,1,0xf0000000);
    if (BVar1 == 0) {
      DVar2 = GetLastError();
      if (DVar2 != 0x80090016) goto LAB_14001946d;
    }
    DAT_140104194 = 1;
  }
  BVar1 = CryptGenRandom(DAT_140104088,0x20,local_38);
  if (BVar1 != 0) {
    FUN_140019280((longlong)local_38,0x20);
    FUN_1400089f0(local_38,0x20);
    DAT_140104080 = 1;
    __security_check_cookie(local_18 ^ (ulonglong)auStackY_68);
    return;
  }
LAB_14001946d:
  __security_check_cookie(local_18 ^ (ulonglong)auStackY_68);
  return;
}


// ==== FUN_1400194f0 @ 1400194f0  int FUN_1400194f0(void)

int FUN_1400194f0(void)

{
  int iVar1;
  
  iVar1 = FUN_140019420();
  return (iVar1 == 0) - 1;
}


// ==== FUN_140019580 @ 140019580  undefined8 FUN_140019580(uint param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

undefined8 FUN_140019580(uint param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  ulonglong uVar1;
  
  uVar1 = (ulonglong)param_1;
  DAT_140104078 = FUN_140016ce0(DAT_140104078,0,param_1);
  if (DAT_140104078 == (undefined4 *)0x0) {
    FUN_140019050("Couldn\'t allocate %s","arc4rand_lock",uVar1,param_4);
    return 0xffffffff;
  }
  return 0;
}


// ==== FUN_1400195d0 @ 1400195d0  undefined FUN_1400195d0(void)

void FUN_1400195d0(void)

{
  if (DAT_140104078 != 0) {
    FUN_140016e10();
    DAT_140104078 = 0;
  }
  return;
}


// ==== FUN_140019610 @ 140019610  undefined FUN_140019610(void)

void FUN_140019610(void)

{
  if (DAT_140104078 != 0) {
    FUN_140016e10();
    DAT_140104078 = 0;
  }
  return;
}


// ==== FUN_140019640 @ 140019640  undefined8 FUN_140019640(void)

undefined8 FUN_140019640(void)

{
  char cVar1;
  int iVar2;
  undefined1 *puVar3;
  longlong lVar4;
  
  if (DAT_140104084 == 0) {
    iVar2 = 0;
    puVar3 = &DAT_140104092;
    do {
      *puVar3 = (char)iVar2;
      iVar2 = iVar2 + 1;
      puVar3 = puVar3 + 1;
    } while (iVar2 < 0x100);
    DAT_140104090 = 0;
    DAT_140104091 = 0;
    DAT_140104084 = 1;
  }
  FUN_140019420();
  if (DAT_140104080 == 0) {
    return 0xffffffff;
  }
  lVar4 = 0x400;
  do {
    DAT_140104090 = DAT_140104090 + 1;
    cVar1 = (&DAT_140104092)[DAT_140104090];
    DAT_140104091 = DAT_140104091 + cVar1;
    (&DAT_140104092)[DAT_140104090] = (&DAT_140104092)[DAT_140104091];
    (&DAT_140104092)[DAT_140104091] = cVar1;
    DAT_140104090 = DAT_140104090 + 1;
    cVar1 = (&DAT_140104092)[DAT_140104090];
    DAT_140104091 = DAT_140104091 + cVar1;
    (&DAT_140104092)[DAT_140104090] = (&DAT_140104092)[DAT_140104091];
    (&DAT_140104092)[DAT_140104091] = cVar1;
    DAT_140104090 = DAT_140104090 + 1;
    cVar1 = (&DAT_140104092)[DAT_140104090];
    DAT_140104091 = DAT_140104091 + cVar1;
    lVar4 = lVar4 + -1;
    (&DAT_140104092)[DAT_140104090] = (&DAT_140104092)[DAT_140104091];
    (&DAT_140104092)[DAT_140104091] = cVar1;
  } while (lVar4 != 0);
  DAT_140104074 = 1600000;
  return 0;
}


// ==== FUN_1400197a0 @ 1400197a0  undefined FUN_1400197a0(void)

void FUN_1400197a0(void)

{
  int iVar1;
  
  iVar1 = _getpid();
  if (((DAT_140104074 < 1) || (DAT_140104084 == 0)) || (DAT_140104070 != iVar1)) {
    DAT_140104070 = iVar1;
    FUN_140019640();
  }
  return;
}


// ==== FUN_1400197e0 @ 1400197e0  undefined FUN_1400197e0(longlong param_1, int param_2)

void FUN_1400197e0(longlong param_1,int param_2)

{
  longlong lVar1;
  ulonglong uVar2;
  
  if (DAT_140104078 != 0) {
    FUN_140016e30();
  }
  if (DAT_140104084 == 0) {
    FUN_140019640();
  }
  lVar1 = DAT_140104078;
  if (0 < param_2) {
    uVar2 = (ulonglong)((param_2 - 1U >> 8) + 1);
    do {
      FUN_140019280(param_1,param_2);
      param_2 = param_2 + -0x100;
      param_1 = param_1 + 0x100;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  if (lVar1 != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_140019890 @ 140019890  undefined FUN_140019890(longlong param_1, longlong param_2)

void FUN_140019890(longlong param_1,longlong param_2)

{
  char cVar1;
  char cVar2;
  int iVar3;
  
  if (DAT_140104078 != 0) {
    FUN_140016e30();
  }
  iVar3 = _getpid();
  if (((DAT_140104074 < 1) || (DAT_140104084 == 0)) || (DAT_140104070 != iVar3)) {
    DAT_140104070 = iVar3;
    FUN_140019640();
  }
  iVar3 = DAT_140104074;
  if (param_2 != 0) {
    do {
      DAT_140104074 = iVar3 + -1;
      param_2 = param_2 + -1;
      if (DAT_140104074 < 1) {
        FUN_140019640();
      }
      iVar3 = DAT_140104074;
      DAT_140104090 = DAT_140104090 + 1;
      cVar1 = (&DAT_140104092)[DAT_140104090];
      DAT_140104091 = DAT_140104091 + cVar1;
      cVar2 = (&DAT_140104092)[DAT_140104091];
      (&DAT_140104092)[DAT_140104090] = cVar2;
      (&DAT_140104092)[DAT_140104091] = cVar1;
      *(undefined1 *)(param_1 + param_2) = (&DAT_140104092)[(byte)(cVar1 + cVar2)];
    } while (param_2 != 0);
  }
  if (DAT_140104078 != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_1400199b0 @ 1400199b0  int FUN_1400199b0(void)

int FUN_1400199b0(void)

{
  bool bVar1;
  
  if (DAT_140104078 != 0) {
    FUN_140016e30();
  }
  if (DAT_140104080 == 0) {
    FUN_140019640();
  }
  bVar1 = DAT_140104080 != 0;
  if (DAT_140104078 != 0) {
    FUN_140016e50();
  }
  return bVar1 - 1;
}


// ==== FUN_140019a40 @ 140019a40  char * FUN_140019a40(char * param_1, char * param_2, longlong param_3)

char * FUN_140019a40(char *param_1,char *param_2,longlong param_3)

{
  char cVar1;
  char *pcVar2;
  longlong lVar3;
  char *pcVar4;
  
  pcVar4 = param_2;
  if (param_3 != 0) {
    for (lVar3 = param_3 + -1; pcVar2 = param_1, lVar3 != 0; lVar3 = lVar3 + -1) {
      cVar1 = *pcVar4;
      pcVar2 = param_1 + 1;
      pcVar4 = pcVar4 + 1;
      *param_1 = cVar1;
      if (cVar1 == '\0') {
        if (lVar3 != 0) goto LAB_140019a7b;
        break;
      }
      param_1 = pcVar2;
    }
    *pcVar2 = '\0';
  }
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
LAB_140019a7b:
  return pcVar4 + (-1 - (longlong)param_2);
}


// ==== FUN_140019c50 @ 140019c50  undefined8 FUN_140019c50(longlong * param_1, uint param_2)

undefined8 FUN_140019c50(longlong *param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  ulonglong uVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  void *_Dst;
  undefined8 *puVar6;
  longlong lVar7;
  size_t _Size;
  ulonglong uVar8;
  undefined8 *puVar9;
  ulonglong uVar10;
  undefined8 *puVar11;
  uint uVar12;
  uint uVar13;
  ulonglong uVar14;
  uint uVar15;
  
  uVar14 = (ulonglong)*(int *)((longlong)param_1 + 0x14);
  if ((*(int *)((longlong)param_1 + 0x14) == DAT_1401024f8 + -1) ||
     (param_2 < *(uint *)(param_1 + 2))) {
    return 0;
  }
  lVar7 = (longlong)&DAT_140102490 + uVar14 * 4;
  do {
    uVar1 = *(uint *)(lVar7 + 4);
    uVar8 = (ulonglong)uVar1;
    lVar7 = lVar7 + 4;
    uVar13 = (int)uVar14 + 1;
    uVar14 = (ulonglong)uVar13;
    uVar15 = (uint)(longlong)((double)uVar8 * 0.5);
    if (param_2 < uVar15) break;
  } while ((int)uVar13 < DAT_1401024f8);
  _Size = uVar8 << 3;
  _Dst = FUN_140011830(_Size);
  if (_Dst == (void *)0x0) {
    puVar6 = (undefined8 *)FUN_1400119a0((void *)*param_1,_Size);
    if (puVar6 == (undefined8 *)0x0) {
      return 0xffffffff;
    }
    memset(puVar6 + *(uint *)(param_1 + 1),0,(ulonglong)(uVar1 - *(uint *)(param_1 + 1)) << 3);
    uVar12 = 0;
    puVar11 = puVar6;
    if ((int)param_1[1] != 0) {
      do {
        puVar5 = (undefined8 *)*puVar11;
        puVar4 = puVar11;
        while (puVar9 = puVar5, puVar9 != (undefined8 *)0x0) {
          uVar2 = *(uint *)(puVar9 + 1);
          uVar14 = (ulonglong)((uVar2 >> 2 | uVar2 << 0x1e) + uVar2) % (ulonglong)uVar1;
          if ((uint)uVar14 != uVar12) {
            *puVar4 = *puVar9;
            *puVar9 = puVar6[uVar14];
            puVar6[uVar14] = puVar9;
            puVar9 = puVar4;
          }
          puVar4 = puVar9;
          puVar5 = (undefined8 *)*puVar9;
        }
        uVar12 = uVar12 + 1;
        puVar11 = puVar11 + 1;
      } while (uVar12 < *(uint *)(param_1 + 1));
    }
    *param_1 = (longlong)puVar6;
  }
  else {
    memset(_Dst,0,_Size);
    uVar10 = 0;
    uVar14 = uVar10;
    if ((int)param_1[1] != 0) {
      do {
        puVar6 = *(undefined8 **)(uVar10 + *param_1);
        while (puVar6 != (undefined8 *)0x0) {
          uVar12 = *(uint *)(puVar6 + 1);
          puVar11 = (undefined8 *)*puVar6;
          uVar3 = (ulonglong)((uVar12 >> 2 | uVar12 << 0x1e) + uVar12) % uVar8;
          *puVar6 = *(undefined8 *)((longlong)_Dst + uVar3 * 8);
          *(undefined8 **)((longlong)_Dst + uVar3 * 8) = puVar6;
          puVar6 = puVar11;
        }
        uVar12 = (int)uVar14 + 1;
        uVar10 = uVar10 + 8;
        uVar14 = (ulonglong)uVar12;
      } while (uVar12 < *(uint *)(param_1 + 1));
    }
    if ((void *)*param_1 != (void *)0x0) {
      FUN_1400119c0((void *)*param_1);
    }
    *param_1 = (longlong)_Dst;
  }
  *(uint *)(param_1 + 1) = uVar1;
  *(uint *)((longlong)param_1 + 0x14) = uVar13;
  *(uint *)(param_1 + 2) = uVar15;
  return 0;
}


// ==== FUN_140019e30 @ 140019e30  undefined FUN_140019e30(undefined8 * param_1)

void FUN_140019e30(undefined8 *param_1)

{
  if ((void *)*param_1 != (void *)0x0) {
    FUN_1400119c0((void *)*param_1);
  }
  *(undefined4 *)((longlong)param_1 + 0x14) = 0xffffffff;
  *(undefined4 *)(param_1 + 1) = 0;
  *param_1 = 0;
  *(undefined4 *)((longlong)param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 2) = 0;
  return;
}


// ==== FUN_140019e70 @ 140019e70  int FUN_140019e70(longlong * param_1)

int FUN_140019e70(longlong *param_1)

{
  uint uVar1;
  uint uVar2;
  undefined8 *puVar3;
  int iVar4;
  undefined8 *puVar5;
  uint uVar6;
  uint uVar7;
  
  uVar1 = *(uint *)(param_1 + 1);
  if (uVar1 == 0) {
    if ((((*param_1 == 0) && (*(int *)((longlong)param_1 + 0xc) == 0)) && ((int)param_1[2] == 0)) &&
       (*(int *)((longlong)param_1 + 0x14) == -1)) {
      return 0;
    }
    return 1;
  }
  puVar5 = (undefined8 *)*param_1;
  if (((puVar5 == (undefined8 *)0x0) || (*(int *)((longlong)param_1 + 0x14) < 0)) ||
     (uVar6 = *(uint *)(param_1 + 2), uVar6 == 0)) {
    return 2;
  }
  if (uVar6 < *(uint *)((longlong)param_1 + 0xc)) {
    return 3;
  }
  if (uVar1 != *(uint *)((longlong)&DAT_140102490 + (longlong)*(int *)((longlong)param_1 + 0x14) * 4
                        )) {
    return 4;
  }
  if (uVar6 != (uint)(longlong)((double)uVar1 * 0.5)) {
    return 5;
  }
  uVar7 = 0;
  uVar6 = 0;
  if (uVar1 != 0) {
    do {
      for (puVar3 = (undefined8 *)*puVar5; puVar3 != (undefined8 *)0x0;
          puVar3 = (undefined8 *)*puVar3) {
        uVar2 = *(uint *)(puVar3 + 1);
        if ((uVar2 >> 2 | uVar2 << 0x1e) + uVar2 != (uVar2 >> 2 | uVar2 << 0x1e) + uVar2) {
          return uVar7 + 1000;
        }
        if (((uVar2 >> 2 | uVar2 << 0x1e) + uVar2) % uVar1 != uVar7) {
          return uVar7 + 10000;
        }
        uVar6 = uVar6 + 1;
      }
      uVar7 = uVar7 + 1;
      puVar5 = puVar5 + 1;
    } while (uVar7 < uVar1);
  }
  iVar4 = 0;
  if (uVar6 != *(uint *)((longlong)param_1 + 0xc)) {
    iVar4 = 6;
  }
  return iVar4;
}


// ==== FUN_14001a010 @ 14001a010  undefined FUN_14001a010(undefined8 * param_1)

void FUN_14001a010(undefined8 *param_1)

{
  *(undefined4 *)((longlong)param_1 + 0x14) = 0xffffffff;
  *(undefined4 *)(param_1 + 1) = 0;
  *param_1 = 0;
  *(undefined4 *)((longlong)param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 2) = 0;
  return;
}


// ==== FUN_14001a030 @ 14001a030  undefined FUN_14001a030(longlong * param_1)

void FUN_14001a030(longlong *param_1)

{
  uint uVar1;
  longlong *plVar3;
  longlong *plVar4;
  longlong *plVar5;
  longlong *plVar2;
  
  plVar5 = (longlong *)0x0;
  if ((int)param_1[1] != 0) {
    plVar2 = plVar5;
    plVar4 = (longlong *)*param_1;
    do {
      if (*plVar4 != 0) {
        plVar2 = (longlong *)*param_1 + (longlong)plVar2;
        while (plVar2 != (longlong *)0x0) {
          plVar4 = (longlong *)*plVar2;
          uVar1 = *(uint *)(plVar4 + 1);
          *plVar2 = *plVar4;
          *(int *)((longlong)param_1 + 0xc) = *(int *)((longlong)param_1 + 0xc) + -1;
          if (*plVar2 == 0) {
            uVar1 = ((uVar1 >> 2 | uVar1 << 0x1e) + uVar1) % *(uint *)(param_1 + 1) + 1;
            plVar2 = plVar5;
            if (uVar1 < *(uint *)(param_1 + 1)) {
              plVar3 = (longlong *)(*param_1 + (longlong)(int)uVar1 * 8);
              do {
                if (*plVar3 != 0) {
                  plVar2 = (longlong *)(*param_1 + (ulonglong)uVar1 * 8);
                  break;
                }
                uVar1 = uVar1 + 1;
                plVar3 = plVar3 + 1;
              } while (uVar1 < *(uint *)(param_1 + 1));
            }
          }
          FUN_1400119c0(plVar4);
        }
        break;
      }
      uVar1 = (int)plVar2 + 1;
      plVar2 = (longlong *)(ulonglong)uVar1;
      plVar4 = plVar4 + 1;
    } while (uVar1 < *(uint *)(param_1 + 1));
  }
  if ((void *)*param_1 != (void *)0x0) {
    FUN_1400119c0((void *)*param_1);
  }
  *(undefined4 *)(param_1 + 1) = 0;
  *param_1 = 0;
  *(undefined4 *)((longlong)param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14) = 0xffffffff;
  return;
}


// ==== FUN_14001a100 @ 14001a100  undefined8 FUN_14001a100(longlong * param_1, int param_2, int param_3)

undefined8 FUN_14001a100(longlong *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  iVar1 = (int)param_1[1];
  if (iVar1 <= param_2) {
    iVar2 = 0x20;
    if (iVar1 != 0) {
      iVar2 = iVar1;
    }
    for (; iVar2 <= param_2; iVar2 = iVar2 * 2) {
    }
    lVar3 = FUN_1400119a0((void *)*param_1,(longlong)(iVar2 * param_3));
    if (lVar3 == 0) {
      return 0xffffffff;
    }
    memset((void *)(lVar3 + (longlong)(int)param_1[1] * 8),0,
           (longlong)((iVar2 - (int)param_1[1]) * param_3));
    *(int *)(param_1 + 1) = iVar2;
    *param_1 = lVar3;
  }
  return 0;
}


// ==== FUN_14001a190 @ 14001a190  undefined FUN_14001a190(undefined8 * param_1)

void FUN_14001a190(undefined8 *param_1)

{
  *(undefined4 *)(param_1 + 1) = 0;
  *param_1 = 0;
  return;
}


// ==== FUN_14001a1a0 @ 14001a1a0  undefined FUN_14001a1a0(longlong * param_1)

void FUN_14001a1a0(longlong *param_1)

{
  int iVar1;
  longlong lVar2;
  
  if (*param_1 == 0) {
    *(undefined4 *)(param_1 + 1) = 0;
    return;
  }
  iVar1 = 0;
  if (0 < (int)param_1[1]) {
    lVar2 = 0;
    do {
      if (*(longlong *)(lVar2 + *param_1) != 0) {
        FUN_1400119c0(*(void **)(lVar2 + *param_1));
      }
      iVar1 = iVar1 + 1;
      lVar2 = lVar2 + 8;
    } while (iVar1 < (int)param_1[1]);
  }
  FUN_1400119c0((void *)*param_1);
  *param_1 = 0;
  *(undefined4 *)(param_1 + 1) = 0;
  return;
}


// ==== FUN_14001a240 @ 14001a240  undefined8 * FUN_14001a240(longlong * param_1, ulonglong param_2, longlong param_3)

undefined8 * FUN_14001a240(longlong *param_1,ulonglong param_2,longlong param_3)

{
  longlong *plVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  longlong lVar6;
  ulonglong uVar7;
  undefined8 *puVar8;
  int iVar9;
  undefined8 *puVar10;
  undefined8 *puVar11;
  undefined8 *puVar12;
  uint uVar13;
  longlong lVar14;
  uint uVar15;
  uint uVar16;
  ushort uVar17;
  ushort local_res10;
  
  lVar6 = *param_1;
  puVar12 = (undefined8 *)0x0;
  plVar1 = param_1 + 0x25;
  uVar17 = 0;
  local_res10 = 0;
  if ((longlong)param_2 < 0) {
    return (undefined8 *)0x0;
  }
  if ((*plVar1 == 0) || (*(uint *)(param_1 + 0x27) <= *(uint *)((longlong)param_1 + 0x134))) {
    FUN_140019c50(plVar1,*(int *)((longlong)param_1 + 0x134) + 1);
  }
  lVar14 = *plVar1;
  puVar11 = puVar12;
  if (lVar14 != 0) {
    uVar13 = (uint)param_2;
    uVar7 = (ulonglong)((uVar13 >> 2 | uVar13 << 0x1e) + uVar13) %
            (ulonglong)*(uint *)(param_1 + 0x26);
    puVar10 = *(undefined8 **)(lVar14 + uVar7 * 8);
    puVar11 = (undefined8 *)(lVar14 + uVar7 * 8);
    while ((puVar8 = puVar10, puVar8 != (undefined8 *)0x0 && (puVar8[1] != param_2))) {
      puVar11 = puVar8;
      puVar10 = (undefined8 *)*puVar8;
    }
  }
  puVar10 = (undefined8 *)*puVar11;
  if (puVar10 == (undefined8 *)0x0) {
    puVar10 = (undefined8 *)FUN_140011850(1,*(longlong *)(lVar6 + 0x38) + 0x20);
    if (puVar10 == (undefined8 *)0x0) {
      return (undefined8 *)0xffffffff;
    }
    puVar10[1] = param_2;
    puVar10[2] = 0;
    *(undefined2 *)(puVar10 + 3) = 0;
    *(undefined2 *)((longlong)puVar10 + 0x1a) = 0;
    *(undefined2 *)((longlong)puVar10 + 0x1c) = 0;
    *puVar10 = 0;
    *puVar11 = puVar10;
    *(int *)((longlong)param_1 + 0x134) = *(int *)((longlong)param_1 + 0x134) + 1;
  }
  uVar2 = *(ushort *)((longlong)puVar10 + 0x1a);
  uVar13 = (uint)uVar2;
  plVar1 = puVar10 + 2;
  uVar3 = *(ushort *)((longlong)puVar10 + 0x1c);
  uVar15 = (uint)uVar3;
  uVar4 = *(ushort *)(puVar10 + 3);
  uVar16 = (uint)uVar4;
  if (uVar4 != 0) {
    local_res10 = 2;
  }
  if (uVar2 != 0) {
    local_res10 = local_res10 | 4;
  }
  if (uVar3 != 0) {
    local_res10 = local_res10 | 0x80;
  }
  uVar5 = *(ushort *)(param_3 + 0x68);
  if (((uVar5 & 2) != 0) && (uVar16 = uVar4 + 1, uVar16 == 1)) {
    uVar17 = uVar4 + 2;
  }
  if (((uVar5 & 4) != 0) && (uVar13 = uVar2 + 1, uVar13 == 1)) {
    uVar17 = uVar17 | 4;
  }
  if (((char)uVar5 < '\0') && (uVar15 = uVar3 + 1, uVar15 == 1)) {
    uVar17 = uVar17 | 0x80;
  }
  if (((uVar16 < 0x10000) && (uVar13 < 0x10000)) && (uVar15 < 0x10000)) {
    if (uVar17 != 0) {
      iVar9 = (**(code **)(lVar6 + 0x10))
                        (param_1,*(undefined8 *)(param_3 + 0x38),local_res10,uVar5 & 0x20 | uVar17,
                         puVar10 + 4);
      if (iVar9 == -1) goto LAB_14001a437;
      puVar12 = (undefined8 *)0x1;
    }
    lVar6 = *plVar1;
    *(short *)(puVar10 + 3) = (short)uVar16;
    *(short *)((longlong)puVar10 + 0x1a) = (short)uVar13;
    *(short *)((longlong)puVar10 + 0x1c) = (short)uVar15;
    *(longlong *)(param_3 + 0x48) = lVar6;
    if (lVar6 != 0) {
      *(longlong **)(*plVar1 + 0x50) = (longlong *)(param_3 + 0x48);
    }
    *plVar1 = param_3;
    *(longlong **)(param_3 + 0x50) = plVar1;
  }
  else {
    FUN_1400191c0("Too many events reading or writing on fd %d",param_2 & 0xffffffff,lVar14,
                  (ulonglong)uVar5);
LAB_14001a437:
    puVar12 = (undefined8 *)0xffffffff;
  }
  return puVar12;
}


// ==== FUN_14001a460 @ 14001a460  longlong FUN_14001a460(longlong * param_1, longlong param_2, longlong param_3)

longlong FUN_14001a460(longlong *param_1,longlong param_2,longlong param_3)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  longlong lVar5;
  ulonglong uVar6;
  longlong *plVar7;
  longlong *plVar8;
  longlong *plVar9;
  int iVar10;
  longlong lVar11;
  uint uVar12;
  uint uVar13;
  ushort uVar14;
  longlong lVar15;
  uint uVar16;
  ushort uVar17;
  
  lVar15 = 0;
  uVar14 = 0;
  uVar17 = 0;
  if (-1 < param_2) {
    lVar5 = param_1[0x25];
    lVar11 = lVar15;
    if (lVar5 != 0) {
      uVar12 = (uint)param_2;
      uVar6 = (ulonglong)((uVar12 >> 2 | uVar12 << 0x1e) + uVar12) %
              (ulonglong)*(uint *)(param_1 + 0x26);
      plVar9 = *(longlong **)(lVar5 + uVar6 * 8);
      plVar8 = (longlong *)(lVar5 + uVar6 * 8);
      while ((plVar7 = plVar9, plVar7 != (longlong *)0x0 && (plVar7[1] != param_2))) {
        plVar8 = plVar7;
        plVar9 = (longlong *)*plVar7;
      }
      if (*plVar8 != 0) {
        lVar11 = *plVar8 + 0x10;
      }
    }
    uVar1 = *(ushort *)(lVar11 + 8);
    uVar16 = (uint)uVar1;
    uVar2 = *(ushort *)(lVar11 + 10);
    uVar12 = (uint)uVar2;
    uVar3 = *(ushort *)(lVar11 + 0xc);
    uVar13 = (uint)uVar3;
    if (uVar1 != 0) {
      uVar17 = 2;
    }
    if (uVar2 != 0) {
      uVar17 = uVar17 | 4;
    }
    if (uVar3 != 0) {
      uVar17 = uVar17 | 0x80;
    }
    uVar4 = *(ushort *)(param_3 + 0x68);
    if (((uVar4 & 2) != 0) && (uVar16 = uVar1 - 1, uVar16 == 0)) {
      uVar14 = uVar1 + 1;
    }
    if (((uVar4 & 4) != 0) && (uVar12 = uVar2 - 1, uVar12 == 0)) {
      uVar14 = uVar14 | 4;
    }
    if (((char)uVar4 < '\0') && (uVar13 = uVar3 - 1, uVar13 == 0)) {
      uVar14 = uVar14 | 0x80;
    }
    if (uVar14 != 0) {
      iVar10 = (**(code **)(*param_1 + 0x18))
                         (param_1,*(undefined8 *)(param_3 + 0x38),uVar17,uVar14,lVar11 + 0x10);
      lVar15 = 1;
      if (iVar10 == -1) {
        lVar15 = 0xffffffff;
      }
    }
    *(short *)(lVar11 + 8) = (short)uVar16;
    *(short *)(lVar11 + 10) = (short)uVar12;
    *(short *)(lVar11 + 0xc) = (short)uVar13;
    if (*(longlong *)(param_3 + 0x48) != 0) {
      *(undefined8 *)(*(longlong *)(param_3 + 0x48) + 0x50) = *(undefined8 *)(param_3 + 0x50);
    }
    **(undefined8 **)(param_3 + 0x50) = *(undefined8 *)(param_3 + 0x48);
    return lVar15;
  }
  return 0;
}


// ==== FUN_14001a5d0 @ 14001a5d0  undefined FUN_14001a5d0(longlong param_1, longlong param_2, ushort param_3)

void FUN_14001a5d0(longlong param_1,longlong param_2,ushort param_3)

{
  undefined8 *puVar1;
  longlong lVar2;
  longlong *plVar3;
  ulonglong uVar4;
  longlong *plVar5;
  longlong *plVar6;
  uint uVar7;
  
  lVar2 = *(longlong *)(param_1 + 0x128);
  if (lVar2 != 0) {
    uVar7 = (uint)param_2;
    uVar4 = (ulonglong)((uVar7 >> 2 | uVar7 << 0x1e) + uVar7) %
            (ulonglong)*(uint *)(param_1 + 0x130);
    plVar6 = *(longlong **)(lVar2 + uVar4 * 8);
    plVar3 = (longlong *)(lVar2 + uVar4 * 8);
    while ((plVar5 = plVar6, plVar5 != (longlong *)0x0 && (plVar5[1] != param_2))) {
      plVar3 = plVar5;
      plVar6 = (longlong *)*plVar5;
    }
    if ((*plVar3 != 0) && (puVar1 = (undefined8 *)(*plVar3 + 0x10), puVar1 != (undefined8 *)0x0)) {
      for (plVar3 = (longlong *)*puVar1; plVar3 != (longlong *)0x0; plVar3 = (longlong *)plVar3[9])
      {
        if ((param_3 & *(ushort *)(plVar3 + 0xd)) != 0) {
          FUN_1400130f0(plVar3,*(ushort *)(plVar3 + 0xd) & param_3,1);
        }
      }
    }
  }
  return;
}


// ==== FUN_14001a680 @ 14001a680  undefined8 FUN_14001a680(longlong param_1, int param_2, longlong param_3)

undefined8 FUN_14001a680(longlong param_1,int param_2,longlong param_3)

{
  longlong lVar1;
  longlong *plVar2;
  int iVar3;
  undefined8 uVar4;
  void *pvVar5;
  longlong lVar6;
  
  lVar1 = *(longlong *)(param_1 + 0x20);
  lVar6 = (longlong)param_2;
  if (param_2 < *(int *)(param_1 + 0x148)) {
LAB_14001a6d0:
    if (*(longlong *)(*(longlong *)(param_1 + 0x140) + lVar6 * 8) == 0) {
      pvVar5 = FUN_140011850(1,*(longlong *)(*(longlong *)(param_1 + 0x20) + 0x38) + 8);
      *(void **)(*(longlong *)(param_1 + 0x140) + lVar6 * 8) = pvVar5;
      if (*(longlong *)(*(longlong *)(param_1 + 0x140) + lVar6 * 8) == 0) goto LAB_14001a6c8;
      **(undefined8 **)(*(longlong *)(param_1 + 0x140) + lVar6 * 8) = 0;
    }
    plVar2 = *(longlong **)(*(longlong *)(param_1 + 0x140) + lVar6 * 8);
    if (*plVar2 == 0) {
      iVar3 = (**(code **)(lVar1 + 0x10))(param_1,*(undefined8 *)(param_3 + 0x38),0,8,0);
      if (iVar3 == -1) goto LAB_14001a6c8;
    }
    lVar1 = *plVar2;
    *(longlong *)(param_3 + 0x48) = lVar1;
    if (lVar1 != 0) {
      *(longlong **)(*plVar2 + 0x50) = (longlong *)(param_3 + 0x48);
    }
    *plVar2 = param_3;
    uVar4 = 1;
    *(longlong **)(param_3 + 0x50) = plVar2;
  }
  else {
    uVar4 = FUN_14001a100((longlong *)(param_1 + 0x140),param_2,8);
    if ((int)uVar4 != -1) goto LAB_14001a6d0;
LAB_14001a6c8:
    uVar4 = 0xffffffff;
  }
  return uVar4;
}


// ==== FUN_14001a790 @ 14001a790  undefined8 FUN_14001a790(longlong param_1, int param_2, longlong param_3)

undefined8 FUN_14001a790(longlong param_1,int param_2,longlong param_3)

{
  longlong lVar1;
  longlong *plVar2;
  int iVar3;
  
  lVar1 = *(longlong *)(param_1 + 0x20);
  if (*(int *)(param_1 + 0x148) <= param_2) {
    return 0xffffffff;
  }
  plVar2 = *(longlong **)(*(longlong *)(param_1 + 0x140) + (longlong)param_2 * 8);
  if (*(longlong *)(param_3 + 0x48) != 0) {
    *(undefined8 *)(*(longlong *)(param_3 + 0x48) + 0x50) = *(undefined8 *)(param_3 + 0x50);
  }
  **(undefined8 **)(param_3 + 0x50) = *(undefined8 *)(param_3 + 0x48);
  if ((*plVar2 == 0) &&
     (iVar3 = (**(code **)(lVar1 + 0x18))(param_1,*(undefined8 *)(param_3 + 0x38),0,8,0),
     iVar3 == -1)) {
    return 0xffffffff;
  }
  return 1;
}


// ==== FUN_14001a810 @ 14001a810  undefined FUN_14001a810(longlong param_1, longlong param_2, undefined2 param_3)

void FUN_14001a810(longlong param_1,longlong param_2,undefined2 param_3)

{
  undefined8 *puVar1;
  longlong *plVar2;
  
  if (((-1 < param_2) && (param_2 < *(int *)(param_1 + 0x148))) &&
     (puVar1 = *(undefined8 **)(*(longlong *)(param_1 + 0x140) + param_2 * 8),
     puVar1 != (undefined8 *)0x0)) {
    for (plVar2 = (longlong *)*puVar1; plVar2 != (longlong *)0x0; plVar2 = (longlong *)plVar2[9]) {
      FUN_1400130f0(plVar2,8,param_3);
    }
  }
  return;
}


// ==== FUN_14001a880 @ 14001a880  longlong FUN_14001a880(longlong * param_1, longlong param_2)

longlong FUN_14001a880(longlong *param_1,longlong param_2)

{
  longlong lVar1;
  ulonglong uVar2;
  longlong *plVar3;
  longlong *plVar4;
  longlong *plVar5;
  uint uVar6;
  
  lVar1 = *param_1;
  if (lVar1 != 0) {
    uVar6 = (uint)param_2;
    uVar2 = (ulonglong)((uVar6 >> 2 | uVar6 << 0x1e) + uVar6) % (ulonglong)*(uint *)(param_1 + 1);
    plVar5 = *(longlong **)(lVar1 + uVar2 * 8);
    plVar4 = (longlong *)(lVar1 + uVar2 * 8);
    while ((plVar3 = plVar5, plVar3 != (longlong *)0x0 && (plVar3[1] != param_2))) {
      plVar4 = plVar3;
      plVar5 = (longlong *)*plVar3;
    }
    lVar1 = *plVar4;
    if ((lVar1 != 0) && (lVar1 != -0x10)) {
      return lVar1 + 0x20;
    }
  }
  return 0;
}


// ==== FUN_14001a8d0 @ 14001a8d0  ulonglong FUN_14001a8d0(longlong param_1, undefined * param_2, undefined8 param_3)

ulonglong FUN_14001a8d0(longlong param_1,undefined *param_2,undefined8 param_3)

{
  uint uVar1;
  ulonglong uVar2;
  longlong *plVar3;
  uint uVar4;
  ulonglong uVar5;
  
  uVar2 = 0;
  if (*(uint *)(param_1 + 0x130) != 0) {
    plVar3 = *(longlong **)(param_1 + 0x128);
    do {
      if (*plVar3 != 0) {
        plVar3 = *(longlong **)(param_1 + 0x128) + uVar2;
        if (plVar3 == (longlong *)0x0) {
          return 0;
        }
        do {
          uVar2 = (*(code *)param_2)(param_1,*(undefined8 *)(*plVar3 + 8),*plVar3 + 0x10,param_3);
          uVar5 = uVar2 & 0xffffffff;
          if ((int)uVar2 != 0) {
            return uVar2;
          }
          plVar3 = (longlong *)*plVar3;
          if (*plVar3 == 0) {
            uVar4 = *(uint *)(plVar3 + 1);
            uVar1 = *(uint *)(param_1 + 0x130);
            uVar4 = ((uVar4 >> 2 | uVar4 << 0x1e) + uVar4) % uVar1 + 1;
            if (uVar1 <= uVar4) {
              return uVar5;
            }
            plVar3 = (longlong *)(*(longlong *)(param_1 + 0x128) + (longlong)(int)uVar4 * 8);
            while (*plVar3 == 0) {
              uVar4 = uVar4 + 1;
              plVar3 = plVar3 + 1;
              if (uVar1 <= uVar4) {
                return uVar5;
              }
            }
            plVar3 = (longlong *)(*(longlong *)(param_1 + 0x128) + (ulonglong)uVar4 * 8);
          }
        } while (plVar3 != (longlong *)0x0);
        return uVar5;
      }
      uVar4 = (int)uVar2 + 1;
      uVar2 = (ulonglong)uVar4;
      plVar3 = plVar3 + 1;
    } while (uVar4 < *(uint *)(param_1 + 0x130));
  }
  return 0;
}


// ==== FUN_14001a9c0 @ 14001a9c0  ulonglong FUN_14001a9c0(longlong param_1, undefined * param_2, undefined8 param_3)

ulonglong FUN_14001a9c0(longlong param_1,undefined *param_2,undefined8 param_3)

{
  longlong lVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  uint uVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  
  uVar3 = 0;
  uVar5 = uVar3;
  uVar6 = uVar3;
  if (0 < *(int *)(param_1 + 0x148)) {
    do {
      lVar1 = *(longlong *)(uVar6 + *(longlong *)(param_1 + 0x140));
      if (lVar1 != 0) {
        uVar2 = (*(code *)param_2)(param_1,uVar5,lVar1,param_3);
        uVar3 = uVar2 & 0xffffffff;
        if ((int)uVar2 != 0) {
          return uVar2;
        }
      }
      uVar4 = (int)uVar5 + 1;
      uVar5 = (ulonglong)uVar4;
      uVar6 = uVar6 + 8;
    } while ((int)uVar4 < *(int *)(param_1 + 0x148));
  }
  return uVar3;
}


// ==== FUN_14001aa50 @ 14001aa50  undefined8 FUN_14001aa50(longlong * param_1, undefined8 param_2, longlong * param_3, undefined4 * param_4)

undefined8 FUN_14001aa50(longlong *param_1,undefined8 param_2,longlong *param_3,undefined4 *param_4)

{
  longlong lVar1;
  size_t _Size;
  int iVar2;
  ushort uVar3;
  
  lVar1 = *param_1;
  uVar3 = 0;
  if ((short)param_3[1] != 0) {
    uVar3 = 2;
  }
  if (*(short *)((longlong)param_3 + 10) != 0) {
    uVar3 = uVar3 | 4;
  }
  if (*(short *)((longlong)param_3 + 0xc) != 0) {
    uVar3 = uVar3 | 0x80;
  }
  _Size = *(size_t *)(lVar1 + 0x38);
  if (_Size != 0) {
    memset(param_3 + 2,0,_Size);
  }
  if (((uVar3 != 0) && (*param_3 != 0)) && ((*(byte *)(*param_3 + 0x68) & 0x20) != 0)) {
    uVar3 = uVar3 | 0x20;
  }
  iVar2 = (**(code **)(lVar1 + 0x10))(param_1,param_2,0,uVar3,param_3 + 2);
  if (iVar2 == -1) {
    *param_4 = 0xffffffff;
  }
  return 0;
}


// ==== FUN_14001ab20 @ 14001ab20  undefined8 FUN_14001ab20(longlong param_1, int param_2, longlong * param_3, undefined4 * param_4)

undefined8 FUN_14001ab20(longlong param_1,int param_2,longlong *param_3,undefined4 *param_4)

{
  int iVar1;
  
  if (*param_3 != 0) {
    iVar1 = (**(code **)(*(longlong *)(param_1 + 0x20) + 0x10))(param_1,(longlong)param_2,0,8,0);
    if (iVar1 == -1) {
      *param_4 = 0xffffffff;
    }
  }
  return 0;
}


// ==== FUN_14001ab60 @ 14001ab60  int FUN_14001ab60(longlong param_1)

int FUN_14001ab60(longlong param_1)

{
  longlong *plVar1;
  int iVar2;
  ulonglong uVar3;
  uint uVar4;
  int iVar6;
  int local_res10 [2];
  ulonglong uVar5;
  
  uVar3 = 0;
  local_res10[0] = 0;
  FUN_14001a8d0(param_1,FUN_14001aa50,local_res10);
  if (-1 < local_res10[0]) {
    iVar6 = local_res10[0];
    if (0 < *(int *)(param_1 + 0x148)) {
      uVar5 = uVar3;
      do {
        plVar1 = *(longlong **)(uVar3 + *(longlong *)(param_1 + 0x140));
        if (((plVar1 != (longlong *)0x0) && (*plVar1 != 0)) &&
           (iVar2 = (**(code **)(*(longlong *)(param_1 + 0x20) + 0x10))
                              (param_1,(longlong)(int)uVar5,0,8,0), iVar6 = local_res10[0],
           iVar2 == -1)) {
          iVar6 = -1;
          local_res10[0] = -1;
        }
        uVar4 = (int)uVar5 + 1;
        uVar5 = (ulonglong)uVar4;
        uVar3 = uVar3 + 8;
      } while ((int)uVar4 < *(int *)(param_1 + 0x148));
    }
    return (-1 < iVar6) - 1;
  }
  return -1;
}


// ==== FUN_14001ac30 @ 14001ac30  undefined8 FUN_14001ac30(undefined8 * param_1)

undefined8 FUN_14001ac30(undefined8 *param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)*param_1;
  while (plVar1 != (longlong *)0x0) {
    FUN_140014300(plVar1);
    plVar1 = (longlong *)*param_1;
  }
  return 0;
}


// ==== FUN_14001ac60 @ 14001ac60  undefined8 FUN_14001ac60(undefined8 param_1, undefined8 param_2, undefined8 * param_3)

undefined8 FUN_14001ac60(undefined8 param_1,undefined8 param_2,undefined8 *param_3)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)*param_3;
  while (plVar1 != (longlong *)0x0) {
    FUN_140014300(plVar1);
    plVar1 = (longlong *)*param_3;
  }
  return 0;
}


// ==== FUN_14001ac90 @ 14001ac90  undefined8 FUN_14001ac90(undefined8 param_1, undefined8 param_2, undefined8 * param_3)

undefined8 FUN_14001ac90(undefined8 param_1,undefined8 param_2,undefined8 *param_3)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)*param_3;
  while (plVar1 != (longlong *)0x0) {
    FUN_140014300(plVar1);
    plVar1 = (longlong *)*param_3;
  }
  return 0;
}


// ==== FUN_14001acc0 @ 14001acc0  undefined FUN_14001acc0(longlong param_1)

void FUN_14001acc0(longlong param_1)

{
  undefined8 *puVar1;
  longlong *plVar2;
  ulonglong uVar3;
  uint uVar4;
  ulonglong uVar5;
  
  uVar3 = 0;
  uVar5 = uVar3;
  if (0 < *(int *)(param_1 + 0x148)) {
    do {
      puVar1 = *(undefined8 **)(uVar3 + *(longlong *)(param_1 + 0x140));
      if (puVar1 != (undefined8 *)0x0) {
        plVar2 = (longlong *)*puVar1;
        while (plVar2 != (longlong *)0x0) {
          FUN_140014300(plVar2);
          plVar2 = (longlong *)*puVar1;
        }
      }
      uVar4 = (int)uVar5 + 1;
      uVar3 = uVar3 + 8;
      uVar5 = (ulonglong)uVar4;
    } while ((int)uVar4 < *(int *)(param_1 + 0x148));
  }
  FUN_14001a8d0(param_1,FUN_14001ac60,0);
  return;
}


// ==== FUN_14001ad50 @ 14001ad50  undefined FUN_14001ad50(undefined8 * param_1)

void FUN_14001ad50(undefined8 *param_1)

{
  *param_1 = 0;
  *(undefined4 *)((longlong)param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 1) = 0;
  return;
}


// ==== FUN_14001ade0 @ 14001ade0  undefined FUN_14001ade0(longlong param_1)

void FUN_14001ade0(longlong param_1)

{
  undefined8 *puVar1;
  uint uVar2;
  longlong *plVar3;
  ulonglong uVar4;
  
  uVar4 = (ulonglong)*(uint *)(param_1 + 0x18);
  if (0 < (int)*(uint *)(param_1 + 0x18)) {
    plVar3 = *(longlong **)(param_1 + 0x10);
    do {
      if ((*(byte *)((longlong)plVar3 + 10) & 8) == 0) {
        if (*(longlong *)(param_1 + 0x128) != 0) {
          uVar2 = (uint)*plVar3;
          for (puVar1 = *(undefined8 **)
                         (*(longlong *)(param_1 + 0x128) +
                         ((ulonglong)((uVar2 >> 2 | uVar2 << 0x1e) + uVar2) %
                         (ulonglong)*(uint *)(param_1 + 0x130)) * 8);
              (puVar1 != (undefined8 *)0x0 && (puVar1[1] != *plVar3));
              puVar1 = (undefined8 *)*puVar1) {
          }
        }
      }
      plVar3 = plVar3 + 2;
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
  }
  FUN_14001a8d0(param_1,&LAB_14001add0,0);
  return;
}


// ==== FUN_14001ae50 @ 14001ae50  undefined FUN_14001ae50(longlong * param_1, longlong param_2)

void FUN_14001ae50(longlong *param_1,longlong param_2)

{
  longlong lVar1;
  longlong lVar2;
  ulonglong uVar3;
  longlong *plVar4;
  longlong *plVar5;
  longlong *plVar6;
  undefined4 *puVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  ulonglong uVar10;
  uint uVar11;
  ulonglong uVar12;
  
  uVar9 = 0;
  uVar10 = uVar9;
  uVar12 = uVar9;
  if (0 < (int)param_1[1]) {
    do {
      lVar1 = *param_1;
      if ((*(byte *)(uVar10 + 10 + lVar1) & 8) == 0) {
        lVar2 = *(longlong *)(param_2 + 0x128);
        uVar8 = uVar9;
        if (lVar2 != 0) {
          uVar11 = (uint)*(longlong *)(uVar10 + lVar1);
          uVar3 = (ulonglong)((uVar11 >> 2 | uVar11 << 0x1e) + uVar11) %
                  (ulonglong)*(uint *)(param_2 + 0x130);
          plVar6 = *(longlong **)(lVar2 + uVar3 * 8);
          plVar5 = (longlong *)(lVar2 + uVar3 * 8);
          while ((plVar4 = plVar6, plVar4 != (longlong *)0x0 &&
                 (plVar4[1] != *(longlong *)(uVar10 + lVar1)))) {
            plVar5 = plVar4;
            plVar6 = (longlong *)*plVar4;
          }
          if (*plVar5 != 0) {
            uVar8 = *plVar5 + 0x10;
          }
        }
        puVar7 = (undefined4 *)(uVar8 + 0x10);
      }
      else {
        puVar7 = (undefined4 *)
                 (*(longlong *)(*(longlong *)(param_2 + 0x140) + *(longlong *)(uVar10 + lVar1) * 8)
                 + 8);
      }
      uVar11 = (int)uVar12 + 1;
      *puVar7 = 0;
      uVar10 = uVar10 + 0x10;
      uVar12 = (ulonglong)uVar11;
    } while ((int)uVar11 < (int)param_1[1]);
    *(undefined4 *)(param_1 + 1) = 0;
    return;
  }
  *(undefined4 *)(param_1 + 1) = 0;
  return;
}


// ==== FUN_14001af30 @ 14001af30  undefined FUN_14001af30(undefined8 * param_1)

void FUN_14001af30(undefined8 *param_1)

{
  if ((void *)*param_1 != (void *)0x0) {
    FUN_1400119c0((void *)*param_1);
  }
  *param_1 = 0;
  *(undefined4 *)((longlong)param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 1) = 0;
  return;
}


// ==== FUN_14001af60 @ 14001af60  undefined8 FUN_14001af60(longlong * param_1)

undefined8 FUN_14001af60(longlong *param_1)

{
  longlong lVar1;
  int iVar2;
  
  if (*(int *)((longlong)param_1 + 0xc) < 0x40) {
    iVar2 = 0x40;
  }
  else {
    iVar2 = *(int *)((longlong)param_1 + 0xc) * 2;
  }
  lVar1 = FUN_1400119a0((void *)*param_1,(longlong)iVar2 << 4);
  if (lVar1 == 0) {
    return 0xffffffff;
  }
  *param_1 = lVar1;
  *(int *)((longlong)param_1 + 0xc) = iVar2;
  return 0;
}


// ==== FUN_14001afc0 @ 14001afc0  undefined8 * FUN_14001afc0(longlong * param_1, undefined8 param_2, undefined2 param_3, int * param_4)

undefined8 * FUN_14001afc0(longlong *param_1,undefined8 param_2,undefined2 param_3,int *param_4)

{
  longlong lVar1;
  undefined8 *puVar2;
  int iVar3;
  int iVar4;
  
  if (*param_4 == 0) {
    iVar3 = *(int *)((longlong)param_1 + 0xc);
    if ((int)param_1[1] == iVar3) {
      iVar4 = 0x40;
      if (0x3f < iVar3) {
        iVar4 = iVar3 * 2;
      }
      lVar1 = FUN_1400119a0((void *)*param_1,(longlong)iVar4 << 4);
      if (lVar1 == 0) {
        return (undefined8 *)0x0;
      }
      *param_1 = lVar1;
      *(int *)((longlong)param_1 + 0xc) = iVar4;
    }
    iVar3 = (int)param_1[1] + 1;
    puVar2 = (undefined8 *)((longlong)(int)param_1[1] * 0x10 + *param_1);
    *(int *)(param_1 + 1) = iVar3;
    *param_4 = iVar3;
    puVar2[1] = 0;
    *puVar2 = param_2;
    *(undefined2 *)(puVar2 + 1) = param_3;
  }
  else {
    puVar2 = (undefined8 *)((longlong)(*param_4 + -1) * 0x10 + *param_1);
  }
  return puVar2;
}


// ==== FUN_14001b070 @ 14001b070  undefined8 FUN_14001b070(longlong param_1, undefined8 param_2, undefined2 param_3, byte param_4, int * param_5)

undefined8
FUN_14001b070(longlong param_1,undefined8 param_2,undefined2 param_3,byte param_4,int *param_5)

{
  undefined8 *puVar1;
  
  puVar1 = FUN_14001afc0((longlong *)(param_1 + 0x10),param_2,param_3,param_5);
  if (puVar1 == (undefined8 *)0x0) {
    return 0xffffffff;
  }
  if ((param_4 & 10) != 0) {
    *(byte *)((longlong)puVar1 + 10) = param_4 & 0x38 | 1;
  }
  if ((param_4 & 4) != 0) {
    *(byte *)((longlong)puVar1 + 0xb) = param_4 & 0x38 | 1;
  }
  if ((char)param_4 < '\0') {
    *(byte *)((longlong)puVar1 + 0xc) = param_4 & 0x38 | 1;
  }
  return 0;
}


// ==== FUN_14001b0d0 @ 14001b0d0  undefined8 FUN_14001b0d0(longlong param_1, undefined8 param_2, undefined2 param_3, byte param_4, int * param_5)

undefined8
FUN_14001b0d0(longlong param_1,undefined8 param_2,undefined2 param_3,byte param_4,int *param_5)

{
  undefined8 *puVar1;
  
  puVar1 = FUN_14001afc0((longlong *)(param_1 + 0x10),param_2,param_3,param_5);
  if (puVar1 == (undefined8 *)0x0) {
    return 0xffffffff;
  }
  if ((param_4 & 10) != 0) {
    *(byte *)((longlong)puVar1 + 10) = -((*(byte *)(puVar1 + 1) & 10) != 0) & 2;
  }
  if ((param_4 & 4) != 0) {
    *(byte *)((longlong)puVar1 + 0xb) = *(byte *)(puVar1 + 1) >> 1 & 2;
  }
  if ((char)param_4 < '\0') {
    *(byte *)((longlong)puVar1 + 0xc) = -((*(byte *)(puVar1 + 1) & 0x80) != 0) & 2;
  }
  return 0;
}


// ==== FUN_14001b1e0 @ 14001b1e0  undefined FUN_14001b1e0(longlong * param_1)

void FUN_14001b1e0(longlong *param_1)

{
  longlong *plVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  longlong *plVar6;
  ulonglong uVar7;
  
  FUN_14001a8d0((longlong)param_1,&LAB_14001b140,0);
  uVar7 = (ulonglong)*(uint *)(param_1 + 0x29);
  if (0 < (int)*(uint *)(param_1 + 0x29)) {
    plVar6 = (longlong *)param_1[0x28];
    do {
      if (((longlong *)*plVar6 != (longlong *)0x0) && (lVar2 = *(longlong *)*plVar6, lVar2 != 0)) {
        lVar3 = *(longlong *)(lVar2 + 0x48);
        lVar5 = lVar2;
        while (lVar4 = lVar2, lVar3 != 0) {
          lVar5 = *(longlong *)(lVar5 + 0x48);
          if ((*(longlong *)(lVar3 + 0x48) == 0) ||
             (lVar3 = *(longlong *)(*(longlong *)(lVar3 + 0x48) + 0x48), lVar5 == 0)) break;
        }
        do {
          plVar1 = (longlong *)(lVar4 + 0x48);
          lVar4 = *plVar1;
        } while (*plVar1 != 0);
        for (; lVar2 != 0; lVar2 = *(longlong *)(lVar2 + 0x48)) {
        }
      }
      plVar6 = plVar6 + 1;
      uVar7 = uVar7 - 1;
    } while (uVar7 != 0);
  }
  if (*(code **)(*param_1 + 0x10) == FUN_14001b070) {
    FUN_14001ade0((longlong)param_1);
  }
  return;
}


// ==== FUN_14001b290 @ 14001b290  undefined8 FUN_14001b290(undefined8 param_1, undefined8 param_2, longlong * param_3, undefined8 * param_4)

undefined8
FUN_14001b290(undefined8 param_1,undefined8 param_2,longlong *param_3,undefined8 *param_4)

{
  longlong lVar1;
  undefined8 uVar2;
  
  lVar1 = *param_3;
  while( true ) {
    if (lVar1 == 0) {
      return 0;
    }
    uVar2 = (*(code *)*param_4)(param_1,lVar1,param_4[1]);
    if ((int)uVar2 != 0) break;
    lVar1 = *(longlong *)(lVar1 + 0x48);
  }
  return uVar2;
}


// ==== FUN_14001b2e0 @ 14001b2e0  undefined8 FUN_14001b2e0(undefined8 param_1, undefined8 param_2, longlong * param_3, undefined8 * param_4)

undefined8
FUN_14001b2e0(undefined8 param_1,undefined8 param_2,longlong *param_3,undefined8 *param_4)

{
  longlong lVar1;
  undefined8 uVar2;
  
  lVar1 = *param_3;
  while( true ) {
    if (lVar1 == 0) {
      return 0;
    }
    uVar2 = (*(code *)*param_4)(param_1,lVar1,param_4[1]);
    if ((int)uVar2 != 0) break;
    lVar1 = *(longlong *)(lVar1 + 0x48);
  }
  return uVar2;
}


// ==== FUN_14001b330 @ 14001b330  ulonglong FUN_14001b330(longlong param_1, undefined * param_2, undefined8 param_3)

ulonglong FUN_14001b330(longlong param_1,undefined *param_2,undefined8 param_3)

{
  longlong *plVar1;
  longlong lVar2;
  uint uVar3;
  ulonglong uVar4;
  longlong lVar5;
  int iVar6;
  code *local_18;
  undefined8 local_10;
  
  local_18 = (code *)param_2;
  local_10 = param_3;
  uVar4 = FUN_14001a8d0(param_1,FUN_14001b290,&local_18);
  if ((int)uVar4 == 0) {
    uVar3 = 0;
    iVar6 = 0;
    if (0 < *(int *)(param_1 + 0x148)) {
      lVar5 = 0;
      do {
        plVar1 = *(longlong **)(*(longlong *)(param_1 + 0x140) + lVar5);
        if (plVar1 != (longlong *)0x0) {
          for (lVar2 = *plVar1; lVar2 != 0; lVar2 = *(longlong *)(lVar2 + 0x48)) {
            uVar3 = (*local_18)(param_1,lVar2,local_10);
            if (uVar3 != 0) goto LAB_14001b3d8;
          }
        }
        uVar3 = 0;
        iVar6 = iVar6 + 1;
        lVar5 = lVar5 + 8;
      } while (iVar6 < *(int *)(param_1 + 0x148));
    }
LAB_14001b3d8:
    uVar4 = (ulonglong)uVar3;
  }
  return uVar4;
}


// ==== FUN_14001b3f0 @ 14001b3f0  undefined FUN_14001b3f0(longlong param_1)

void FUN_14001b3f0(longlong param_1)

{
  if (DAT_1401045a0 != 0) {
    FUN_140016e30();
  }
  DAT_1401045b0 = *(undefined4 *)(param_1 + 0xb4);
  DAT_140102500 = *(undefined8 *)(param_1 + 0xa8);
  DAT_1401045a8 = param_1;
  if (DAT_1401045a0 != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_14001b450 @ 14001b450  undefined FUN_14001b450(longlong param_1, undefined8 param_2, longlong param_3)

void FUN_14001b450(longlong param_1,undefined8 param_2,longlong param_3)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  int *piVar5;
  ulonglong uVar6;
  longlong lVar7;
  int local_68 [24];
  ulonglong uVar4;
  
  memset(local_68,0,0x5c);
  iVar1 = Ordinal_16(param_1,&DAT_1401041a0,0x400,0);
  uVar6 = 0;
  while (iVar1 != -1) {
    if (iVar1 == 0) goto LAB_14001b51a;
    if (0 < iVar1) {
      pbVar2 = &DAT_1401041a0;
      uVar4 = uVar6;
      do {
        if (*pbVar2 < 0x17) {
          local_68[*pbVar2] = local_68[*pbVar2] + 1;
        }
        uVar3 = (int)uVar4 + 1;
        uVar4 = (ulonglong)uVar3;
        pbVar2 = pbVar2 + 1;
      } while ((int)uVar3 < iVar1);
    }
    iVar1 = Ordinal_16(param_1,&DAT_1401041a0,0x400,0);
  }
  iVar1 = FUN_140007540(param_1);
  if ((iVar1 != 0x2733) && (iVar1 != 0x2714)) {
    FUN_1400190a0(1,param_1,"%s: recv","evsig_cb");
  }
LAB_14001b51a:
  if (*(longlong *)(param_3 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  piVar5 = local_68;
  lVar7 = 0x17;
  do {
    if (*piVar5 != 0) {
      FUN_14001a810(param_3,uVar6,(short)*piVar5);
    }
    uVar6 = uVar6 + 1;
    piVar5 = piVar5 + 1;
    lVar7 = lVar7 + -1;
  } while (lVar7 != 0);
  if (*(longlong *)(param_3 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_14001b590 @ 14001b590  undefined8 FUN_14001b590(longlong param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

undefined8 FUN_14001b590(longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  
  iVar1 = FUN_14000acb0((ulonglong *)(param_1 + 0xa0),param_2,param_3,param_4);
  if (iVar1 == -1) {
    FUN_140019120(-1,"%s: socketpair","evsig_init_",param_4);
    return 0xffffffff;
  }
  if (*(void **)(param_1 + 0xb8) != (void *)0x0) {
    FUN_1400119c0(*(void **)(param_1 + 0xb8));
  }
  *(undefined8 *)(param_1 + 0xb8) = 0;
  *(undefined4 *)(param_1 + 0xc0) = 0;
  FUN_140010e40((undefined *)(param_1 + 0x28),param_1,*(undefined8 *)(param_1 + 0xa0),0x12,
                FUN_14001b450,(undefined *)param_1);
  *(ushort *)(param_1 + 0x38) = *(ushort *)(param_1 + 0x38) | 0x10;
  FUN_140010fe0(param_1 + 0x28,0);
  *(undefined ***)(param_1 + 0x20) = &PTR_s_signal_1400c13d0;
  return 0;
}


// ==== FUN_14001b650 @ 14001b650  undefined8 FUN_14001b650(longlong param_1, undefined8 param_2, size_t param_3, undefined8 param_4)

undefined8 FUN_14001b650(longlong param_1,undefined8 param_2,size_t param_3,undefined8 param_4)

{
  longlong lVar1;
  void *pvVar2;
  undefined8 uVar3;
  longlong extraout_RAX;
  int iVar4;
  size_t sVar5;
  longlong lVar6;
  int iVar7;
  size_t sVar8;
  
  iVar4 = (int)param_2;
  lVar6 = (longlong)iVar4;
  sVar8 = param_3;
  if (*(int *)(param_1 + 0xc0) <= iVar4) {
    iVar7 = iVar4 + 1;
    sVar5 = (longlong)iVar7 << 3;
    lVar1 = FUN_1400119a0(*(void **)(param_1 + 0xb8),sVar5);
    if (lVar1 == 0) {
      FUN_140019050("realloc",sVar5,sVar8,param_4);
      return 0xffffffff;
    }
    param_2 = 0;
    sVar8 = (longlong)(iVar7 - *(int *)(param_1 + 0xc0)) << 3;
    memset((void *)(lVar1 + (longlong)*(int *)(param_1 + 0xc0) * 8),0,sVar8);
    *(int *)(param_1 + 0xc0) = iVar7;
    *(longlong *)(param_1 + 0xb8) = lVar1;
  }
  pvVar2 = FUN_140011830(8);
  *(void **)(*(longlong *)(param_1 + 0xb8) + lVar6 * 8) = pvVar2;
  if (*(longlong *)(*(longlong *)(param_1 + 0xb8) + lVar6 * 8) == 0) {
    FUN_140019050("malloc",param_2,sVar8,param_4);
    uVar3 = 0xffffffff;
  }
  else {
    signal(iVar4);
    if (extraout_RAX == -1) {
      FUN_140019050("signal",param_3,sVar8,param_4);
      FUN_1400119c0(*(void **)(*(longlong *)(param_1 + 0xb8) + lVar6 * 8));
      uVar3 = 0xffffffff;
      *(undefined8 *)(*(longlong *)(param_1 + 0xb8) + lVar6 * 8) = 0;
    }
    else {
      uVar3 = 0;
      **(longlong **)(*(longlong *)(param_1 + 0xb8) + lVar6 * 8) = extraout_RAX;
    }
  }
  return uVar3;
}


// ==== FUN_14001b780 @ 14001b780  undefined8 FUN_14001b780(longlong param_1, int param_2, undefined8 param_3, undefined8 param_4)

undefined8 FUN_14001b780(longlong param_1,int param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 *puVar1;
  longlong extraout_RAX;
  undefined8 uVar2;
  undefined8 uVar3;
  longlong lVar4;
  
  lVar4 = (longlong)param_2;
  uVar3 = 0;
  if (*(int *)(param_1 + 0xc0) <= param_2) {
    return 0;
  }
  puVar1 = *(undefined8 **)(*(longlong *)(param_1 + 0xb8) + lVar4 * 8);
  *(undefined8 *)(*(longlong *)(param_1 + 0xb8) + lVar4 * 8) = 0;
  uVar2 = *puVar1;
  signal(param_2);
  if (extraout_RAX == -1) {
    FUN_140019050("signal",uVar2,lVar4,param_4);
    uVar3 = 0xffffffff;
  }
  FUN_1400119c0(puVar1);
  return uVar3;
}


// ==== FUN_14001b7f0 @ 14001b7f0  undefined8 FUN_14001b7f0(longlong param_1, int param_2, undefined8 param_3, undefined8 param_4)

undefined8 FUN_14001b7f0(longlong param_1,int param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 *puVar1;
  longlong lVar2;
  longlong extraout_RAX;
  undefined8 uVar3;
  undefined8 uVar4;
  
  if (DAT_1401045a0 != 0) {
    FUN_140016e30();
  }
  lVar2 = DAT_1401045a0;
  DAT_1401045b0 = DAT_1401045b0 + -1;
  *(int *)(param_1 + 0xb4) = *(int *)(param_1 + 0xb4) + -1;
  if (lVar2 != 0) {
    FUN_140016e50();
  }
  uVar4 = 0;
  if (param_2 < *(int *)(param_1 + 0xc0)) {
    puVar1 = *(undefined8 **)(*(longlong *)(param_1 + 0xb8) + (longlong)param_2 * 8);
    *(undefined8 *)(*(longlong *)(param_1 + 0xb8) + (longlong)param_2 * 8) = 0;
    uVar3 = *puVar1;
    signal(param_2);
    if (extraout_RAX == -1) {
      FUN_140019050("signal",uVar3,param_3,param_4);
      uVar4 = 0xffffffff;
    }
    FUN_1400119c0(puVar1);
  }
  return uVar4;
}


// ==== FUN_14001b890 @ 14001b890  undefined FUN_14001b890(uint param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_14001b890(uint param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined1 local_res10 [8];
  
  piVar3 = _errno();
  iVar1 = *piVar3;
  uVar2 = Ordinal_111();
  if (DAT_1401045a8 == 0) {
    FUN_1400191c0("%s: received signal %d, but have no base configured","evsig_handler",
                  (ulonglong)param_1,param_4);
    return;
  }
  signal(param_1);
  local_res10[0] = (undefined1)param_1;
  Ordinal_19(DAT_140102500,local_res10,1);
  piVar3 = _errno();
  *piVar3 = iVar1;
  Ordinal_112(uVar2);
  return;
}


// ==== FUN_14001b930 @ 14001b930  undefined FUN_14001b930(longlong param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_14001b930(longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  longlong lVar1;
  undefined8 *puVar2;
  longlong extraout_RAX;
  undefined8 uVar3;
  ulonglong uVar4;
  int iVar5;
  ulonglong uVar6;
  
  uVar4 = 0;
  if (*(int *)(param_1 + 0xb0) != 0) {
    FUN_140014300((longlong *)(param_1 + 0x28));
    *(undefined4 *)(param_1 + 0xb0) = 0;
  }
  FUN_140010fd0(param_1 + 0x28);
  uVar6 = uVar4;
  do {
    iVar5 = (int)uVar6;
    if (((iVar5 < *(int *)(param_1 + 0xc0)) &&
        (lVar1 = *(longlong *)(param_1 + 0xb8), *(longlong *)(uVar4 + lVar1) != 0)) &&
       (iVar5 < *(int *)(param_1 + 0xc0))) {
      puVar2 = *(undefined8 **)(lVar1 + uVar4);
      *(undefined8 *)(lVar1 + uVar4) = 0;
      uVar3 = *puVar2;
      signal(iVar5);
      if (extraout_RAX == -1) {
        FUN_140019050("signal",uVar3,param_3,param_4);
      }
      FUN_1400119c0(puVar2);
    }
    uVar6 = (ulonglong)(iVar5 + 1U);
    uVar4 = uVar4 + 8;
  } while ((int)(iVar5 + 1U) < 0x17);
  if (DAT_1401045a0 != 0) {
    FUN_140016e30();
  }
  if (param_1 == DAT_1401045a8) {
    DAT_1401045a8 = 0;
    DAT_1401045b0 = 0;
    DAT_140102500 = 0xffffffffffffffff;
  }
  if (DAT_1401045a0 != 0) {
    FUN_140016e50();
  }
  if (*(longlong *)(param_1 + 0xa0) != -1) {
    Ordinal_3();
    *(undefined8 *)(param_1 + 0xa0) = 0xffffffffffffffff;
  }
  if (*(longlong *)(param_1 + 0xa8) != -1) {
    Ordinal_3();
    *(undefined8 *)(param_1 + 0xa8) = 0xffffffffffffffff;
  }
  *(undefined4 *)(param_1 + 0xc0) = 0;
  if (*(void **)(param_1 + 0xb8) != (void *)0x0) {
    FUN_1400119c0(*(void **)(param_1 + 0xb8));
    *(undefined8 *)(param_1 + 0xb8) = 0;
  }
  return;
}


// ==== FUN_14001baa0 @ 14001baa0  undefined FUN_14001baa0(void)

void FUN_14001baa0(void)

{
  if (DAT_1401045a0 != 0) {
    FUN_140016e10();
    DAT_1401045a0 = 0;
  }
  return;
}


// ==== FUN_14001bad0 @ 14001bad0  undefined FUN_14001bad0(void)

void FUN_14001bad0(void)

{
  if (DAT_1401045a0 != 0) {
    FUN_140016e10();
    DAT_1401045a0 = 0;
  }
  return;
}


// ==== FUN_14001bb00 @ 14001bb00  undefined8 FUN_14001bb00(uint param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

undefined8 FUN_14001bb00(uint param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  ulonglong uVar1;
  
  uVar1 = (ulonglong)param_1;
  DAT_1401045a0 = FUN_140016ce0(DAT_1401045a0,0,param_1);
  if (DAT_1401045a0 == (undefined4 *)0x0) {
    FUN_140019050("Couldn\'t allocate %s","evsig_base_lock",uVar1,param_4);
    return 0xffffffff;
  }
  return 0;
}


// ==== FUN_14001bb50 @ 14001bb50  undefined8 FUN_14001bb50(undefined8 * param_1, ulonglong param_2, undefined8 param_3, undefined8 param_4)

undefined8
FUN_14001bb50(undefined8 *param_1,ulonglong param_2,undefined8 param_3,undefined8 param_4)

{
  longlong lVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  
  if (DAT_1401045a0 != 0) {
    FUN_140016e30();
  }
  if ((DAT_1401045a8 != param_1) && (DAT_1401045b0 != 0)) {
    param_4 = *(undefined8 *)*param_1;
    FUN_1400191c0("Added a signal to event base %p with signals already added to event_base %p.  Only one can have signals at a time with the %s backend.  The base with the most recently added signal or the most recent event_base_loop() call gets preference; do not rely on this behavior in future Libevent versions."
                  ,param_1,DAT_1401045a8,param_4);
  }
  lVar1 = DAT_1401045a0;
  *(int *)((longlong)param_1 + 0xb4) = *(int *)((longlong)param_1 + 0xb4) + 1;
  DAT_1401045b0 = *(int *)((longlong)param_1 + 0xb4);
  DAT_140102500 = param_1[0x15];
  DAT_1401045a8 = param_1;
  if (lVar1 != 0) {
    FUN_140016e50();
  }
  uVar2 = FUN_14001b650((longlong)param_1,param_2 & 0xffffffff,0x14001b890,param_4);
  if ((int)uVar2 != -1) {
    if (*(int *)(param_1 + 0x16) == 0) {
      puVar3 = FUN_140013f70(param_1 + 5,(ulonglong *)0x0,0);
      if ((int)puVar3 != 0) goto LAB_14001bc30;
      *(undefined4 *)(param_1 + 0x16) = 1;
    }
    return 0;
  }
LAB_14001bc30:
  if (DAT_1401045a0 != 0) {
    FUN_140016e30();
  }
  lVar1 = DAT_1401045a0;
  DAT_1401045b0 = DAT_1401045b0 + -1;
  *(int *)((longlong)param_1 + 0xb4) = *(int *)((longlong)param_1 + 0xb4) + -1;
  if (lVar1 != 0) {
    FUN_140016e50();
  }
  return 0xffffffff;
}


// ==== FUN_14001beb0 @ 14001beb0  undefined8 * FUN_14001beb0(void)

undefined8 * FUN_14001beb0(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)FUN_14001e450(0x10);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    puVar1 = FUN_14001dd40(puVar1);
  }
  return puVar1;
}


// ==== FUN_14001bef0 @ 14001bef0  undefined8 FUN_14001bef0(undefined8 * param_1)

undefined8 FUN_14001bef0(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    (**(code **)*param_1)(param_1,1);
  }
  return 0;
}


// ==== FUN_14001bf10 @ 14001bf10  short FUN_14001bf10(short * param_1, int param_2, short param_3, void * param_4, int param_5, undefined4 param_6)

short FUN_14001bf10(short *param_1,int param_2,short param_3,void *param_4,int param_5,
                   undefined4 param_6)

{
  if (param_5 + 8 <= param_2) {
    param_1[1] = param_3;
    *param_1 = (short)param_5 + 8;
    *(undefined4 *)(param_1 + 2) = param_6;
    memcpy(param_1 + 4,param_4,(longlong)param_5);
    return *param_1;
  }
  return 0;
}


// ==== FUN_14001c100 @ 14001c100  undefined FUN_14001c100(longlong param_1)

void FUN_14001c100(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00014001c107. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(longlong **)(param_1 + 0x10) + 8))();
  return;
}


// ==== FUN_14001c120 @ 14001c120  undefined FUN_14001c120(longlong param_1)

void FUN_14001c120(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00014001c127. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)**(undefined8 **)(param_1 + 0x10))();
  return;
}


// ==== FUN_14001c130 @ 14001c130  undefined8 FUN_14001c130(longlong param_1)

undefined8 FUN_14001c130(longlong param_1)

{
  return *(undefined8 *)(param_1 + 0x50);
}


// ==== FUN_14001c1c0 @ 14001c1c0  bool FUN_14001c1c0(int param_1)

bool FUN_14001c1c0(int param_1)

{
  return param_1 - 0x61a81U < 99999;
}


// ==== FUN_14001c1d0 @ 14001c1d0  bool FUN_14001c1d0(int param_1)

bool FUN_14001c1d0(int param_1)

{
  return param_1 - 0x61a81U < 299999;
}


// ==== FUN_14001c1e0 @ 14001c1e0  bool FUN_14001c1e0(int param_1)

bool FUN_14001c1e0(int param_1)

{
  return param_1 - 1U < 299999;
}


// ==== FUN_14001c200 @ 14001c200  undefined8 FUN_14001c200(void)

undefined8 FUN_14001c200(void)

{
  return DAT_1401045b8;
}


// ==== FUN_14001c210 @ 14001c210  undefined8 FUN_14001c210(void)

undefined8 FUN_14001c210(void)

{
  return *(undefined8 *)(DAT_1401045b8 + 0x38);
}


// ==== FUN_14001c220 @ 14001c220  undefined FUN_14001c220(longlong param_1)

void FUN_14001c220(longlong param_1)

{
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
  return;
}


// ==== FUN_14001c230 @ 14001c230  undefined FUN_14001c230(longlong param_1)

void FUN_14001c230(longlong param_1)

{
  if (0 < *(int *)(param_1 + 0xc)) {
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + -1;
  }
  return;
}


// ==== FUN_14001c250 @ 14001c250  undefined8 FUN_14001c250(void)

undefined8 FUN_14001c250(void)

{
  return *(undefined8 *)(DAT_1401045b8 + 0x50);
}


// ==== FUN_14001c280 @ 14001c280  undefined4 FUN_14001c280(longlong param_1, int param_2)

undefined4 FUN_14001c280(longlong param_1,int param_2)

{
  ulong uVar1;
  
  uVar1 = tq::TimeGet(0);
  return CONCAT31((int3)((uint)*(int *)(param_1 + 4) >> 8),
                  (uint)(param_2 + *(int *)(param_1 + 4)) <= uVar1 / 1000);
}


// ==== FUN_14001c2c0 @ 14001c2c0  ulonglong FUN_14001c2c0(longlong param_1, int param_2)

ulonglong FUN_14001c2c0(longlong param_1,int param_2)

{
  ulong uVar1;
  
  uVar1 = tq::TimeGet(0);
  if ((uint)(param_2 + *(int *)(param_1 + 4)) <= uVar1 / 1000) {
    uVar1 = tq::TimeGet(0);
    *(uint *)(param_1 + 4) = uVar1 / 1000;
    return CONCAT71((uint7)((ulonglong)uVar1 * 0x10624dd3 >> 8) & 0xffffff,1);
  }
  return (ulonglong)uVar1 * 0x10624dd3 & 0xffffff00;
}


// ==== FUN_14001c350 @ 14001c350  undefined FUN_14001c350(undefined8 * param_1)

void FUN_14001c350(undefined8 *param_1)

{
  if ((undefined8 *)*param_1 != (undefined8 *)0x0) {
    FUN_1400214c0((undefined8 *)*param_1);
    *param_1 = 0;
  }
  return;
}


// ==== FUN_14001c380 @ 14001c380  undefined FUN_14001c380(longlong * param_1)

void FUN_14001c380(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
    *param_1 = 0;
  }
  return;
}


// ==== FUN_14001c3b0 @ 14001c3b0  undefined FUN_14001c3b0(longlong * param_1)

void FUN_14001c3b0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
    *param_1 = 0;
  }
  return;
}


// ==== FUN_14001c3e0 @ 14001c3e0  undefined FUN_14001c3e0(longlong * param_1)

void FUN_14001c3e0(longlong *param_1)

{
  if ((undefined8 *)*param_1 != (undefined8 *)0x0) {
    (*(code *)**(undefined8 **)*param_1)();
    *param_1 = 0;
  }
  return;
}


// ==== FUN_14001c410 @ 14001c410  undefined FUN_14001c410(longlong * param_1)

void FUN_14001c410(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
    *param_1 = 0;
  }
  return;
}


// ==== FUN_14001c440 @ 14001c440  void * FUN_14001c440(void * param_1, ulonglong param_2, undefined8 param_3, undefined8 param_4)

void * FUN_14001c440(void *param_1,ulonglong param_2,undefined8 param_3,undefined8 param_4)

{
  FUN_1400340e0((longlong)param_1,param_2,param_3,param_4);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_14001c480 @ 14001c480  undefined FUN_14001c480(undefined8 param_1, undefined8 * param_2, undefined8 param_3, undefined8 param_4)

void FUN_14001c480(undefined8 param_1,undefined8 *param_2,undefined8 param_3,undefined8 param_4)

{
  if (param_2 != (undefined8 *)0x0) {
    (**(code **)*param_2)(param_2,1,param_2,param_4,0xfffffffffffffffe);
  }
  return;
}


// ==== FUN_14001c4d0 @ 14001c4d0  undefined8 * FUN_14001c4d0(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_14001c4d0(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  param_1[1] = param_2;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14) = 1;
  *param_1 = std::tr1::_Ref_count<class_CAIStrategyMgr>::vftable;
  return param_1;
}


// ==== FUN_14001c550 @ 14001c550  undefined FUN_14001c550(undefined8 * param_1)

void FUN_14001c550(undefined8 *param_1)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  return;
}


// ==== FUN_14001c5f0 @ 14001c5f0  undefined FUN_14001c5f0(longlong param_1, undefined4 param_2, longlong param_3)

void FUN_14001c5f0(longlong param_1,undefined4 param_2,longlong param_3)

{
  int iVar1;
  short sVar2;
  char cVar3;
  undefined1 auStack_468 [32];
  undefined4 local_448;
  undefined8 local_438;
  CTickAnalyst local_430 [24];
  short local_418;
  undefined2 local_416;
  undefined4 local_414;
  undefined1 local_410 [1016];
  ulonglong local_18;
  
  local_438 = 0xfffffffffffffffe;
  local_18 = DAT_140103510 ^ (ulonglong)auStack_468;
  if (param_3 != 0) {
    iVar1 = *(int *)(param_3 + 0xc);
    if (iVar1 + 8 < 0x401) {
      local_416 = (undefined2)*(undefined4 *)(param_3 + 8);
      local_418 = (short)iVar1 + 8;
      local_414 = param_2;
      memcpy(local_410,(void *)(param_3 + 0x10),(longlong)iVar1);
      sVar2 = local_418;
      if (local_418 != 0) {
        CTickAnalyst::CTickAnalyst(local_430,0x55);
        cVar3 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))
                          (*(longlong **)(param_1 + 0x10),&local_418,sVar2,0);
        if (cVar3 == '\0') {
          *(undefined4 *)(param_1 + 8) = 3;
        }
        CTickAnalyst::~CTickAnalyst(local_430);
        goto LAB_14001c6dc;
      }
    }
    local_448 = 0x180;
    log_InlineLogERROR(&DAT_1400be0b0,"MYASSERT","nNetPacketSize",
                       "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\npcworld.cpp");
  }
LAB_14001c6dc:
  __security_check_cookie(local_18 ^ (ulonglong)auStack_468);
  return;
}


// ==== FUN_14001c700 @ 14001c700  undefined FUN_14001c700(longlong param_1)

void FUN_14001c700(longlong param_1)

{
  ulong uVar1;
  undefined1 auStack_438 [32];
  char local_418 [1024];
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_438;
  *(undefined4 *)(param_1 + 8) = 2;
  uVar1 = tq::TimeGet(0);
  *(uint *)(param_1 + 0x1c) = uVar1 / 1000;
  sprintf(local_418,"Login OK. generator monster after %d secs");
  (**(code **)**(undefined8 **)(param_1 + 0x10))(*(undefined8 **)(param_1 + 0x10),local_418);
  __security_check_cookie(local_18 ^ (ulonglong)auStack_438);
  return;
}


// ==== FUN_14001c790 @ 14001c790  undefined8 FUN_14001c790(void)

undefined8 FUN_14001c790(void)

{
  return *(undefined8 *)(DAT_1401045b8 + 0x28);
}


// ==== FUN_14001c7a0 @ 14001c7a0  undefined8 FUN_14001c7a0(void)

undefined8 FUN_14001c7a0(void)

{
  return *(undefined8 *)(DAT_1401045b8 + 0x30);
}


// ==== FUN_14001c7b0 @ 14001c7b0  undefined8 FUN_14001c7b0(void)

undefined8 FUN_14001c7b0(void)

{
  return *(undefined8 *)(DAT_1401045b8 + 0x40);
}


// ==== FUN_14001c7f0 @ 14001c7f0  undefined FUN_14001c7f0(longlong param_1)

void FUN_14001c7f0(longlong param_1)

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


// ==== FUN_14001c830 @ 14001c830  undefined FUN_14001c830(undefined8 * param_1, undefined8 param_2, longlong param_3)

void FUN_14001c830(undefined8 *param_1,undefined8 param_2,longlong param_3)

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


// ==== FUN_14001c8c0 @ 14001c8c0  undefined FUN_14001c8c0(undefined8 * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_14001c8c0(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  void *pvVar1;
  
  pvVar1 = (void *)*param_1;
  if (pvVar1 != (void *)0x0) {
    FUN_1400340e0((longlong)pvVar1,param_2,param_3,param_4);
    operator_delete(pvVar1);
    *param_1 = 0;
  }
  return;
}


// ==== FUN_14001c930 @ 14001c930  undefined8 * FUN_14001c930(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_14001c930(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  param_1[1] = param_2;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14) = 1;
  *param_1 = std::tr1::
             _Ref_count_d<class_CItemType,class_TReleaseDeleter<class_CItemType>,class_std::allocator<int>_>
             ::vftable;
  return param_1;
}


// ==== FUN_14001c9c0 @ 14001c9c0  undefined FUN_14001c9c0(undefined8 * param_1)

void FUN_14001c9c0(undefined8 *param_1)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  return;
}


// ==== FUN_14001cab0 @ 14001cab0  undefined8 FUN_14001cab0(longlong param_1)

undefined8 FUN_14001cab0(longlong param_1)

{
  return *(undefined8 *)(param_1 + 0x58);
}


// ==== FUN_14001cac0 @ 14001cac0  undefined FUN_14001cac0(longlong param_1)

void FUN_14001cac0(longlong param_1)

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


// ==== FUN_14001cb00 @ 14001cb00  undefined8 * FUN_14001cb00(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14001cb00(undefined8 *param_1,undefined8 *param_2)

{
  FUN_14001c830(param_1,*param_2,param_2[1]);
  return param_1;
}


// ==== FUN_14001cb20 @ 14001cb20  undefined FUN_14001cb20(undefined8 * param_1)

void FUN_14001cb20(undefined8 *param_1)

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


// ==== FUN_14001cbb0 @ 14001cbb0  undefined FUN_14001cbb0(undefined8 * param_1, undefined8 param_2)

void FUN_14001cbb0(undefined8 *param_1,undefined8 param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x20);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = std::tr1::_Ref_count_base::vftable;
    puVar1[1] = param_2;
    *(undefined4 *)(puVar1 + 2) = 0;
    *(undefined4 *)((longlong)puVar1 + 0x14) = 1;
    *puVar1 = std::tr1::
              _Ref_count_d<class_CItemType,class_TReleaseDeleter<class_CItemType>,class_std::allocator<int>_>
              ::vftable;
  }
  FUN_14001c830(param_1,param_2,(longlong)puVar1);
  return;
}


// ==== FUN_14001cc60 @ 14001cc60  undefined FUN_14001cc60(undefined8 * param_1, undefined8 param_2)

void FUN_14001cc60(undefined8 *param_1,undefined8 param_2)

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
    *puVar1 = std::tr1::_Ref_count<class_CAIStrategyMgr>::vftable;
  }
  FUN_140003480(param_1,param_2,(longlong)puVar1);
  return;
}


// ==== FUN_14001cce0 @ 14001cce0  undefined FUN_14001cce0(undefined8 * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_14001cce0(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  
  *param_1 = CNpcWorld::vftable;
  plVar3 = param_1 + 8;
  puVar4 = param_1;
  if ((*plVar3 != 0) && (*plVar3 != 0)) {
    puVar4 = (undefined8 *)*plVar3;
    FUN_1400214c0(puVar4);
    *plVar3 = 0;
  }
  plVar3 = param_1 + 6;
  if ((*plVar3 != 0) && (*plVar3 != 0)) {
    puVar5 = (undefined8 *)*plVar3;
    if (puVar5 != (undefined8 *)0x0) {
      FUN_1400340e0((longlong)puVar5,param_2,param_3,param_4);
      operator_delete(puVar5);
      puVar4 = puVar5;
    }
    *plVar3 = 0;
  }
  plVar3 = param_1 + 7;
  if ((*plVar3 != 0) && (*plVar3 != 0)) {
    puVar4 = (undefined8 *)*plVar3;
    if (puVar4 != (undefined8 *)0x0) {
      param_2 = 1;
      (**(code **)*puVar4)();
    }
    *plVar3 = 0;
  }
  plVar3 = param_1 + 5;
  if ((*plVar3 != 0) && (*plVar3 != 0)) {
    puVar4 = (undefined8 *)*plVar3;
    if (puVar4 != (undefined8 *)0x0) {
      param_2 = 1;
      (**(code **)*puVar4)();
    }
    *plVar3 = 0;
  }
  thunk_FUN_140092030(puVar4,param_2,param_3,param_4);
  plVar3 = param_1 + 9;
  if (*plVar3 != 0) {
    (*(code *)**(undefined8 **)*plVar3)();
    *plVar3 = 0;
  }
  FUN_140034e90();
  plVar3 = (longlong *)param_1[0xc];
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


// ==== FUN_14001ce50 @ 14001ce50  undefined8 * FUN_14001ce50(undefined8 * param_1)

undefined8 * FUN_14001ce50(undefined8 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_14001cb20(param_1);
  return param_1;
}


// ==== FUN_14001ce70 @ 14001ce70  undefined8 * FUN_14001ce70(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_14001ce70(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_14001cbb0(param_1,param_2);
  return param_1;
}


// ==== FUN_14001ce90 @ 14001ce90  undefined8 * FUN_14001ce90(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14001ce90(undefined8 *param_1,undefined8 *param_2)

{
  FUN_140003480(param_1,*param_2,param_2[1]);
  return param_1;
}


// ==== FUN_14001ceb0 @ 14001ceb0  undefined8 * FUN_14001ceb0(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_14001ceb0(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_14001cc60(param_1,param_2);
  return param_1;
}


// ==== FUN_14001ced0 @ 14001ced0  undefined8 * FUN_14001ced0(undefined8 * param_1)

undefined8 * FUN_14001ced0(undefined8 *param_1)

{
  *param_1 = CNpcWorld::vftable;
  *(undefined4 *)(param_1 + 1) = 0;
  *(undefined4 *)((longlong)param_1 + 0xc) = 0;
  param_1[2] = 0;
  *(undefined4 *)(param_1 + 3) = 0;
  *(undefined4 *)((longlong)param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)((longlong)param_1 + 0x24) = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  FUN_14001cb20(param_1 + 0xb);
  *(undefined4 *)(param_1 + 1) = 0;
  return param_1;
}


// ==== FUN_14001d230 @ 14001d230  longlong FUN_14001d230(void)

longlong FUN_14001d230(void)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  longlong local_20;
  longlong *local_18;
  
  if (DAT_140103c70 == 0) {
    puVar4 = (undefined8 *)operator_new(0x98);
    puVar5 = (undefined8 *)0x0;
    if (puVar4 != (undefined8 *)0x0) {
      puVar5 = FUN_140045ff0(puVar4);
    }
    local_20 = 0;
    local_18 = (longlong *)0x0;
    FUN_14001cc60(&local_20,puVar5);
    if (local_18 != (longlong *)0x0) {
      LOCK();
      *(int *)(local_18 + 2) = (int)local_18[2] + 1;
      UNLOCK();
    }
    plVar3 = DAT_140103c78;
    if (DAT_140103c78 != (longlong *)0x0) {
      LOCK();
      plVar1 = DAT_140103c78 + 2;
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
    plVar3 = local_18;
    DAT_140103c70 = local_20;
    DAT_140103c78 = local_18;
    if (local_18 != (longlong *)0x0) {
      LOCK();
      plVar1 = local_18 + 2;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)*plVar1 == 0) {
        (**(code **)*local_18)(local_18);
        LOCK();
        piVar2 = (int *)((longlong)plVar3 + 0x14);
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (*piVar2 == 0) {
          (**(code **)(*local_18 + 8))();
        }
      }
    }
  }
  return DAT_140103c70;
}


// ==== FUN_14001d350 @ 14001d350  undefined8 * FUN_14001d350(void)

undefined8 * FUN_14001d350(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x68);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    puVar1 = FUN_14001ced0(puVar1);
  }
  return puVar1;
}


// ==== FUN_14001d9c0 @ 14001d9c0  undefined8 FUN_14001d9c0(undefined8 param_1, undefined8 param_2)

undefined8 FUN_14001d9c0(undefined8 param_1,undefined8 param_2)

{
  return param_2;
}


// ==== FUN_14001d9d0 @ 14001d9d0  undefined FUN_14001d9d0(void)

void FUN_14001d9d0(void)

{
  return;
}


// ==== FUN_14001d9e0 @ 14001d9e0  undefined8 * FUN_14001d9e0(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_14001d9e0(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = param_2;
  return param_1;
}


// ==== FUN_14001d9f0 @ 14001d9f0  undefined8 FUN_14001d9f0(undefined8 param_1)

undefined8 FUN_14001d9f0(undefined8 param_1)

{
  return param_1;
}


// ==== FUN_14001da00 @ 14001da00  undefined FUN_14001da00(void)

void FUN_14001da00(void)

{
  return;
}


// ==== FUN_14001da10 @ 14001da10  undefined8 * FUN_14001da10(undefined8 * param_1)

undefined8 * FUN_14001da10(undefined8 *param_1)

{
  *param_1 = 0;
  return param_1;
}


// ==== FUN_14001da20 @ 14001da20  undefined FUN_14001da20(undefined8 * param_1, undefined8 * param_2)

void FUN_14001da20(undefined8 *param_1,undefined8 *param_2)

{
  *param_1 = *param_2;
  return;
}


// ==== FUN_14001da30 @ 14001da30  bool FUN_14001da30(longlong * param_1, longlong * param_2)

bool FUN_14001da30(longlong *param_1,longlong *param_2)

{
  return *param_1 == *param_2;
}


// ==== FUN_14001da40 @ 14001da40  bool FUN_14001da40(longlong * param_1)

bool FUN_14001da40(longlong *param_1)

{
  return *param_1 != 0;
}


// ==== FUN_14001da50 @ 14001da50  exception * FUN_14001da50(exception * param_1, char * param_2)

exception * FUN_14001da50(exception *param_1,char *param_2)

{
  char *local_res10 [3];
  
  local_res10[0] = param_2;
  std::exception::exception(param_1,local_res10);
  *(undefined ***)param_1 = std::bad_alloc::vftable;
  return param_1;
}


// ==== FUN_14001da90 @ 14001da90  undefined FUN_14001da90(exception * param_1)

void FUN_14001da90(exception *param_1)

{
  *(undefined ***)param_1 = std::bad_alloc::vftable;
                    /* WARNING: Could not recover jumptable at 0x00014001dab0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  std::exception::~exception(param_1);
  return;
}


// ==== FUN_14001db10 @ 14001db10  exception * FUN_14001db10(exception * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

exception *
FUN_14001db10(exception *param_1,
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  std::exception::exception(param_1);
  *(undefined ***)param_1 = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18),param_2);
  return param_1;
}


// ==== FUN_14001db60 @ 14001db60  undefined FUN_14001db60(exception * param_1)

void FUN_14001db60(exception *param_1)

{
  *(undefined ***)param_1 = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18));
                    /* WARNING: Could not recover jumptable at 0x00014001db93. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  std::exception::~exception(param_1);
  return;
}


// ==== FUN_14001dc20 @ 14001dc20  exception * FUN_14001dc20(exception * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

exception *
FUN_14001dc20(exception *param_1,
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  std::exception::exception(param_1);
  *(undefined ***)param_1 = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18),param_2);
  *(undefined ***)param_1 = std::out_of_range::vftable;
  return param_1;
}


// ==== FUN_14001dc80 @ 14001dc80  undefined FUN_14001dc80(exception * param_1)

void FUN_14001dc80(exception *param_1)

{
  *(undefined ***)param_1 = std::out_of_range::vftable;
  *(undefined ***)param_1 = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18));
                    /* WARNING: Could not recover jumptable at 0x00014001dcbd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  std::exception::~exception(param_1);
  return;
}


// ==== FUN_14001dd40 @ 14001dd40  undefined8 * FUN_14001dd40(undefined8 * param_1)

undefined8 * FUN_14001dd40(undefined8 *param_1)

{
  param_1[1] = 0;
  *param_1 = CItemType::vftable;
  return param_1;
}


// ==== FUN_14001dd60 @ 14001dd60  undefined FUN_14001dd60(undefined8 * param_1)

void FUN_14001dd60(undefined8 *param_1)

{
  *param_1 = CItemType::vftable;
  if ((longlong *)param_1[1] != (longlong *)0x0) {
    (**(code **)(*(longlong *)param_1[1] + 0x10))();
  }
  return;
}


// ==== FUN_14001dd90 @ 14001dd90  undefined FUN_14001dd90(longlong param_1)

void FUN_14001dd90(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00014001dd97. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(longlong **)(param_1 + 8) + 0x40))();
  return;
}


// ==== FUN_14001dda0 @ 14001dda0  undefined FUN_14001dda0(undefined8 * param_1)

void FUN_14001dda0(undefined8 *param_1)

{
  *param_1 = ISingleMap2<class_CConstGameData<&char*_szItemTypeTable,&char*_szItemTypeTableID>_>::
             vftable;
  return;
}


// ==== FUN_14001dfd0 @ 14001dfd0  undefined FUN_14001dfd0(undefined8 param_1, void * param_2)

void FUN_14001dfd0(undefined8 param_1,void *param_2)

{
  operator_delete(param_2);
  return;
}


// ==== FUN_14001e020 @ 14001e020  bool FUN_14001e020(longlong * param_1, longlong * param_2)

bool FUN_14001e020(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_14001e060 @ 14001e060  bool FUN_14001e060(longlong * param_1, longlong * param_2)

bool FUN_14001e060(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_14001e0b0 @ 14001e0b0  undefined FUN_14001e0b0(longlong param_1, longlong param_2)

void FUN_14001e0b0(longlong param_1,longlong param_2)

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


// ==== FUN_14001e160 @ 14001e160  undefined FUN_14001e160(longlong param_1, longlong * param_2)

void FUN_14001e160(longlong param_1,longlong *param_2)

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


// ==== FUN_14001e1d0 @ 14001e1d0  undefined FUN_14001e1d0(longlong * param_1)

void FUN_14001e1d0(longlong *param_1)

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
                    /* WARNING: Could not recover jumptable at 0x00014001e1f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_14001e2b0 @ 14001e2b0  undefined FUN_14001e2b0(ulonglong param_1)

void FUN_14001e2b0(ulonglong param_1)

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


// ==== FUN_14001e350 @ 14001e350  undefined FUN_14001e350(ulonglong param_1)

void FUN_14001e350(ulonglong param_1)

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


// ==== FUN_14001e3c0 @ 14001e3c0  exception * FUN_14001e3c0(exception * param_1, exception * param_2)

exception * FUN_14001e3c0(exception *param_1,exception *param_2)

{
  std::exception::exception(param_1,param_2);
  *(undefined ***)param_1 = std::bad_alloc::vftable;
  return param_1;
}


// ==== FUN_14001e3f0 @ 14001e3f0  undefined * FUN_14001e3f0(void)

undefined * FUN_14001e3f0(void)

{
  if ((DAT_1401045c8 & 1) == 0) {
    DAT_1401045c8 = DAT_1401045c8 | 1;
    CMyHeap::CMyHeap((CMyHeap *)&DAT_1401045c0,"CItemType");
    atexit((_func_5014 *)&LAB_1400bbfd0);
  }
  return &DAT_1401045c0;
}


// ==== FUN_14001e450 @ 14001e450  undefined FUN_14001e450(__uint64 param_1)

void FUN_14001e450(__uint64 param_1)

{
  if ((DAT_1401045c8 & 1) == 0) {
    DAT_1401045c8 = DAT_1401045c8 | 1;
    CMyHeap::CMyHeap((CMyHeap *)&DAT_1401045c0,"CItemType");
    atexit((_func_5014 *)&LAB_1400bbfd0);
  }
                    /* WARNING: Could not recover jumptable at 0x00014001e4a5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  CMyHeap::Alloc((CMyHeap *)&DAT_1401045c0,param_1);
  return;
}


// ==== FUN_14001e4b0 @ 14001e4b0  undefined FUN_14001e4b0(void * param_1)

void FUN_14001e4b0(void *param_1)

{
  if ((DAT_1401045c8 & 1) == 0) {
    DAT_1401045c8 = DAT_1401045c8 | 1;
    CMyHeap::CMyHeap((CMyHeap *)&DAT_1401045c0,"CItemType");
    atexit((_func_5014 *)&LAB_1400bbfd0);
  }
                    /* WARNING: Could not recover jumptable at 0x00014001e505. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  CMyHeap::Free((CMyHeap *)&DAT_1401045c0,param_1);
  return;
}


// ==== FUN_14001e510 @ 14001e510  undefined FUN_14001e510(void * param_1)

void FUN_14001e510(void *param_1)

{
  if ((DAT_1401045c8 & 1) == 0) {
    DAT_1401045c8 = DAT_1401045c8 | 1;
    CMyHeap::CMyHeap((CMyHeap *)&DAT_1401045c0,"CItemType");
    atexit((_func_5014 *)&LAB_1400bbfd0);
  }
                    /* WARNING: Could not recover jumptable at 0x00014001e565. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  CMyHeap::IsValidPt((CMyHeap *)&DAT_1401045c0,param_1);
  return;
}


// ==== FUN_14001e5e0 @ 14001e5e0  undefined FUN_14001e5e0(undefined8 * param_1)

void FUN_14001e5e0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14001e5f0 @ 14001e5f0  undefined8 * FUN_14001e5f0(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_14001e5f0(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_14001e640 @ 14001e640  undefined FUN_14001e640(undefined8 param_1, ulonglong param_2)

void FUN_14001e640(undefined8 param_1,ulonglong param_2)

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


// ==== FUN_14001e6d0 @ 14001e6d0  longlong * FUN_14001e6d0(longlong * param_1)

longlong * FUN_14001e6d0(longlong *param_1)

{
  FUN_14001e1d0(param_1);
  return param_1;
}


// ==== FUN_14001e6f0 @ 14001e6f0  undefined FUN_14001e6f0(undefined8 param_1, ulonglong param_2)

void FUN_14001e6f0(undefined8 param_1,ulonglong param_2)

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


// ==== FUN_14001e760 @ 14001e760  undefined8 * FUN_14001e760(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_14001e760(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_14001e7b0 @ 14001e7b0  undefined FUN_14001e7b0(undefined8 * param_1)

void FUN_14001e7b0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14001e7d0 @ 14001e7d0  undefined8 * FUN_14001e7d0(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14001e7d0(undefined8 *param_1,undefined8 *param_2,longlong param_3)

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


// ==== FUN_14001e820 @ 14001e820  undefined8 * FUN_14001e820(undefined8 * param_1, undefined8 * param_2, longlong * param_3)

undefined8 * FUN_14001e820(undefined8 *param_1,undefined8 *param_2,longlong *param_3)

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
  FUN_14001e1d0(param_3);
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
        goto LAB_14001ea0c;
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
LAB_14001ea0c:
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
            FUN_14001e0b0((longlong)param_1,(longlong)plVar7);
            plVar8 = (longlong *)plVar7[2];
          }
          if (*(char *)((longlong)plVar8 + 0x29) == '\0') {
            if ((*(char *)(*plVar8 + 0x28) != '\x01') || (*(char *)(plVar8[2] + 0x28) != '\x01')) {
              if (*(char *)(plVar8[2] + 0x28) == '\x01') {
                *(undefined1 *)(*plVar8 + 0x28) = 1;
                *(undefined1 *)(plVar8 + 5) = 0;
                FUN_14001e160((longlong)param_1,plVar8);
                plVar8 = (longlong *)plVar7[2];
              }
              *(char *)(plVar8 + 5) = (char)plVar7[5];
              *(undefined1 *)(plVar7 + 5) = 1;
              *(undefined1 *)(plVar8[2] + 0x28) = 1;
              FUN_14001e0b0((longlong)param_1,(longlong)plVar7);
              break;
            }
            *(undefined1 *)(plVar8 + 5) = 0;
          }
        }
        else {
          if ((char)plVar8[5] == '\0') {
            *(undefined1 *)(plVar8 + 5) = 1;
            *(undefined1 *)(plVar7 + 5) = 0;
            FUN_14001e160((longlong)param_1,plVar7);
            plVar8 = (longlong *)*plVar7;
          }
          if (*(char *)((longlong)plVar8 + 0x29) == '\0') {
            if ((*(char *)(plVar8[2] + 0x28) != '\x01') || (*(char *)(*plVar8 + 0x28) != '\x01')) {
              if (*(char *)(*plVar8 + 0x28) == '\x01') {
                *(undefined1 *)(plVar8[2] + 0x28) = 1;
                *(undefined1 *)(plVar8 + 5) = 0;
                FUN_14001e0b0((longlong)param_1,(longlong)plVar8);
                plVar8 = (longlong *)*plVar7;
              }
              *(char *)(plVar8 + 5) = (char)plVar7[5];
              *(undefined1 *)(plVar7 + 5) = 1;
              *(undefined1 *)(*plVar8 + 0x28) = 1;
              FUN_14001e160((longlong)param_1,plVar7);
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


// ==== FUN_14001ebe0 @ 14001ebe0  exception * FUN_14001ebe0(exception * param_1, exception * param_2)

exception * FUN_14001ebe0(exception *param_1,exception *param_2)

{
  std::exception::exception(param_1,param_2);
  *(undefined ***)param_1 = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 0x18));
  return param_1;
}


// ==== FUN_14001ec30 @ 14001ec30  exception * FUN_14001ec30(exception * param_1, exception * param_2)

exception * FUN_14001ec30(exception *param_1,exception *param_2)

{
  std::exception::exception(param_1,param_2);
  *(undefined ***)param_1 = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 0x18));
  *(undefined ***)param_1 = std::out_of_range::vftable;
  return param_1;
}


// ==== FUN_14001ec90 @ 14001ec90  undefined FUN_14001ec90(void)

void FUN_14001ec90(void)

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


// ==== FUN_14001ecf0 @ 14001ecf0  longlong * FUN_14001ecf0(longlong * param_1, longlong * param_2)

longlong * FUN_14001ecf0(longlong *param_1,longlong *param_2)

{
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  FUN_14001e1d0(param_1);
  return param_2;
}


// ==== FUN_14001ed20 @ 14001ed20  undefined FUN_14001ed20(undefined8 param_1, longlong * param_2)

void FUN_14001ed20(undefined8 param_1,longlong *param_2)

{
  char cVar1;
  longlong *plVar2;
  
  cVar1 = *(char *)((longlong)param_2 + 0x29);
  while (cVar1 == '\0') {
    FUN_14001ed20(param_1,(longlong *)param_2[2]);
    plVar2 = (longlong *)*param_2;
    operator_delete(param_2);
    param_2 = plVar2;
    cVar1 = *(char *)((longlong)plVar2 + 0x29);
  }
  return;
}


// ==== FUN_14001ed70 @ 14001ed70  undefined8 * FUN_14001ed70(undefined8 * param_1)

undefined8 * FUN_14001ed70(undefined8 *param_1)

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


// ==== FUN_14001ee00 @ 14001ee00  undefined FUN_14001ee00(undefined8 * param_1)

void FUN_14001ee00(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14001ee20 @ 14001ee20  undefined FUN_14001ee20(longlong param_1)

void FUN_14001ee20(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = FUN_14001ec90();
  *(longlong *)(param_1 + 0x30) = lVar1;
  *(undefined1 *)(lVar1 + 0x29) = 1;
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)*(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x30);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 0x10) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = 0;
  return;
}


// ==== FUN_14001ee60 @ 14001ee60  undefined FUN_14001ee60(longlong param_1)

void FUN_14001ee60(longlong param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  
  plVar2 = *(longlong **)(*(longlong *)(param_1 + 0x30) + 8);
  cVar1 = *(char *)((longlong)plVar2 + 0x29);
  while (cVar1 == '\0') {
    FUN_14001ed20(param_1,(longlong *)plVar2[2]);
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


// ==== FUN_14001eee0 @ 14001eee0  undefined8 * FUN_14001eee0(undefined8 * param_1)

undefined8 * FUN_14001eee0(undefined8 *param_1)

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


// ==== FUN_14001efd0 @ 14001efd0  undefined FUN_14001efd0(undefined8 * param_1)

void FUN_14001efd0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14001eff0 @ 14001eff0  longlong * FUN_14001eff0(longlong * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_14001eff0(longlong *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

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
      FUN_14001ee60((longlong)param_1);
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
    FUN_14001e820(param_1,local_18,&local_28);
  }
  lVar2 = param_3[1];
  *param_2 = *param_1;
  param_2[1] = lVar2;
  return param_2;
}


// ==== FUN_14001f1a0 @ 14001f1a0  undefined8 * FUN_14001f1a0(undefined8 * param_1)

undefined8 * FUN_14001f1a0(undefined8 *param_1)

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


// ==== FUN_14001f1f0 @ 14001f1f0  undefined FUN_14001f1f0(undefined8 * param_1)

void FUN_14001f1f0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14001f210 @ 14001f210  undefined FUN_14001f210(longlong * param_1)

void FUN_14001f210(longlong *param_1)

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
  FUN_14001eff0(param_1,local_18,&local_28,&local_38);
  operator_delete((void *)param_1[6]);
  param_1[6] = 0;
  param_1[7] = 0;
  return;
}


// ==== FUN_14001f280 @ 14001f280  undefined8 * FUN_14001f280(undefined8 * param_1)

undefined8 * FUN_14001f280(undefined8 *param_1)

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


// ==== FUN_14001f2d0 @ 14001f2d0  undefined FUN_14001f2d0(longlong * param_1)

void FUN_14001f2d0(longlong *param_1)

{
  FUN_14001f210(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14001f300 @ 14001f300  undefined8 * FUN_14001f300(undefined8 * param_1)

undefined8 * FUN_14001f300(undefined8 *param_1)

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


// ==== FUN_14001f350 @ 14001f350  undefined FUN_14001f350(longlong * param_1)

void FUN_14001f350(longlong *param_1)

{
  FUN_14001f210(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14001f380 @ 14001f380  undefined8 * FUN_14001f380(undefined8 * param_1)

undefined8 * FUN_14001f380(undefined8 *param_1)

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
  lVar2 = FUN_14001ec90();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x29) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_14001f400 @ 14001f400  undefined8 * FUN_14001f400(undefined8 * param_1)

undefined8 * FUN_14001f400(undefined8 *param_1)

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
  lVar2 = FUN_14001ec90();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x29) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_14001f480 @ 14001f480  undefined8 * FUN_14001f480(undefined8 * param_1, undefined1 param_2)

undefined8 * FUN_14001f480(undefined8 *param_1,undefined1 param_2)

{
  *param_1 = ISingleMap2<class_CConstGameData<&char*_szItemTypeTable,&char*_szItemTypeTableID>_>::
             vftable;
  *param_1 = CSingleMap2<class_CConstGameData<&char*_szItemTypeTable,&char*_szItemTypeTableID>_>::
             vftable;
  FUN_14001f400(param_1 + 2);
  *(undefined1 *)(param_1 + 1) = param_2;
  return param_1;
}


// ==== FUN_14001f4e0 @ 14001f4e0  undefined8 FUN_14001f4e0(longlong * param_1)

undefined8 FUN_14001f4e0(longlong *param_1)

{
  if ((undefined8 *)*param_1 != (undefined8 *)0x0) {
    return *(undefined8 *)*param_1;
  }
  return 0;
}


// ==== FUN_14001f4f0 @ 14001f4f0  exception * FUN_14001f4f0(exception * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

exception *
FUN_14001f4f0(exception *param_1,
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  std::exception::exception(param_1);
  *(undefined ***)param_1 = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18),param_2);
  *(undefined ***)param_1 = std::length_error::vftable;
  return param_1;
}


// ==== FUN_14001f550 @ 14001f550  undefined FUN_14001f550(exception * param_1)

void FUN_14001f550(exception *param_1)

{
  *(undefined ***)param_1 = std::length_error::vftable;
  *(undefined ***)param_1 = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18));
                    /* WARNING: Could not recover jumptable at 0x00014001f58d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  std::exception::~exception(param_1);
  return;
}


// ==== FUN_14001f610 @ 14001f610  undefined8 FUN_14001f610(undefined8 * param_1)

undefined8 FUN_14001f610(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    (**(code **)*param_1)(param_1,1);
  }
  return 0;
}


// ==== FUN_14001f680 @ 14001f680  undefined FUN_14001f680(longlong * param_1)

void FUN_14001f680(longlong *param_1)

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
                    /* WARNING: Could not recover jumptable at 0x00014001f6b2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_14001f7b0 @ 14001f7b0  undefined FUN_14001f7b0(undefined8 * param_1)

void FUN_14001f7b0(undefined8 *param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)
           (**(code **)(*(longlong *)*param_1 + 0x20))((longlong *)*param_1,&DAT_14010264c);
                    /* WARNING: Could not recover jumptable at 0x00014001f7ce. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x40))(plVar1);
  return;
}


// ==== FUN_14001f7e0 @ 14001f7e0  bool FUN_14001f7e0(longlong * param_1, longlong * param_2)

bool FUN_14001f7e0(longlong *param_1,longlong *param_2)

{
  longlong lVar1;
  
  lVar1 = (**(code **)(*param_2 + 0x38))(param_2);
  *param_1 = lVar1;
  return lVar1 != 0;
}


// ==== FUN_14001f820 @ 14001f820  undefined FUN_14001f820(longlong * param_1)

void FUN_14001f820(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,0);
  }
  return;
}


// ==== FUN_14001f850 @ 14001f850  longlong FUN_14001f850(longlong * param_1)

longlong FUN_14001f850(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14001f872;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14001f872:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_14001f8a0 @ 14001f8a0  longlong * FUN_14001f8a0(longlong * param_1)

longlong * FUN_14001f8a0(longlong *param_1)

{
  FUN_14001e1d0(param_1);
  return param_1;
}


// ==== FUN_14001f8f0 @ 14001f8f0  longlong * FUN_14001f8f0(longlong * param_1)

longlong * FUN_14001f8f0(longlong *param_1)

{
  FUN_14001f680(param_1);
  return param_1;
}


// ==== FUN_14001f920 @ 14001f920  undefined8 * FUN_14001f920(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, undefined8 * param_5, undefined1 param_6)

undefined8 *
FUN_14001f920(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
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


// ==== FUN_14001f9a0 @ 14001f9a0  longlong * FUN_14001f9a0(longlong * param_1)

longlong * FUN_14001f9a0(longlong *param_1)

{
  FUN_14001f680(param_1);
  return param_1;
}


// ==== FUN_14001f9c0 @ 14001f9c0  undefined8 * FUN_14001f9c0(void)

undefined8 * FUN_14001f9c0(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = 0;
  }
  return puVar1;
}


// ==== FUN_14001fa00 @ 14001fa00  longlong * FUN_14001fa00(longlong * param_1, uint param_2)

longlong * FUN_14001fa00(longlong *param_1,uint param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,0);
  }
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_14001fa40 @ 14001fa40  undefined FUN_14001fa40(longlong * param_1, longlong * param_2, longlong * param_3)

void FUN_14001fa40(longlong *param_1,longlong *param_2,longlong *param_3)

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


// ==== FUN_14001fb10 @ 14001fb10  longlong FUN_14001fb10(longlong * param_1)

longlong FUN_14001fb10(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14001fb32;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14001fb32:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_14001fb50 @ 14001fb50  longlong * FUN_14001fb50(longlong * param_1, longlong * param_2)

longlong * FUN_14001fb50(longlong *param_1,longlong *param_2)

{
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  FUN_14001e1d0(param_1);
  return param_2;
}


// ==== FUN_14001fbc0 @ 14001fbc0  undefined8 * FUN_14001fbc0(undefined8 * param_1, undefined8 * param_2, uint * param_3)

undefined8 * FUN_14001fbc0(undefined8 *param_1,undefined8 *param_2,uint *param_3)

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


// ==== FUN_14001fca0 @ 14001fca0  undefined8 * FUN_14001fca0(undefined8 * param_1, undefined8 * param_2, char param_3, undefined8 * param_4, undefined8 * param_5)

undefined8 *
FUN_14001fca0(undefined8 *param_1,undefined8 *param_2,char param_3,undefined8 *param_4,
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
  plVar5 = FUN_14001f920(param_1,param_1[6],param_4,param_1[6],param_5,0);
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


// ==== FUN_14001ffe0 @ 14001ffe0  exception * FUN_14001ffe0(exception * param_1, exception * param_2)

exception * FUN_14001ffe0(exception *param_1,exception *param_2)

{
  std::exception::exception(param_1,param_2);
  *(undefined ***)param_1 = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 0x18));
  *(undefined ***)param_1 = std::length_error::vftable;
  return param_1;
}


// ==== FUN_140020040 @ 140020040  undefined FUN_140020040(longlong * param_1)

void FUN_140020040(longlong *param_1)

{
  undefined8 *puVar1;
  
  if (param_1 != (longlong *)0x0) {
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 != (undefined8 *)0x0) {
      (**(code **)*puVar1)(puVar1,0);
    }
    operator_delete(param_1);
  }
  return;
}


// ==== FUN_140020070 @ 140020070  undefined FUN_140020070(longlong * param_1, longlong * param_2, longlong * param_3)

void FUN_140020070(longlong *param_1,longlong *param_2,longlong *param_3)

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


// ==== FUN_140020160 @ 140020160  longlong FUN_140020160(longlong * param_1)

longlong FUN_140020160(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140020182;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140020182:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_1400201a0 @ 1400201a0  longlong * FUN_1400201a0(longlong * param_1, undefined8 param_2)

/* WARNING: Removing unreachable block (ram,0x000140020267) */

longlong * FUN_1400201a0(longlong *param_1,undefined8 param_2)

{
  int iVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong lVar4;
  ulonglong uVar5;
  longlong *plVar6;
  uint uVar7;
  undefined8 uVar9;
  longlong *plVar8;
  
  uVar9 = 0xfffffffffffffffe;
  plVar2 = (longlong *)InstanceGet();
  plVar2 = (longlong *)(**(code **)(*plVar2 + 0x10))(plVar2,param_2,2,*plVar2,uVar9);
  if (plVar2 != (longlong *)0x0) {
    iVar1 = (**(code **)(*plVar2 + 0x40))(plVar2);
    plVar8 = (longlong *)0x0;
    if (0 < iVar1) {
      do {
        (**(code **)(*plVar2 + 0x30))(plVar2,(longlong)(int)plVar8);
        plVar3 = (longlong *)operator_new(8);
        plVar6 = (longlong *)0x0;
        if (plVar3 != (longlong *)0x0) {
          *plVar3 = 0;
          plVar6 = plVar3;
        }
        if (plVar6 == (longlong *)0x0) {
          uVar5 = (**(code **)*plVar2)(plVar2);
          return (longlong *)(uVar5 & 0xffffffffffffff00);
        }
        lVar4 = (**(code **)(*plVar2 + 0x38))(plVar2);
        *plVar6 = lVar4;
        if (lVar4 == 0) {
          operator_delete(plVar6);
          uVar5 = (**(code **)*plVar2)(plVar2);
          return (longlong *)(uVar5 & 0xffffffffffffff00);
        }
        (**(code **)(*param_1 + 0x30))(param_1,plVar6);
        uVar7 = (int)plVar8 + 1;
        plVar8 = (longlong *)(ulonglong)uVar7;
        iVar1 = (**(code **)(*plVar2 + 0x40))(plVar2);
      } while ((int)uVar7 < iVar1);
    }
    uVar9 = (**(code **)*plVar2)(plVar2);
    plVar2 = (longlong *)CONCAT71((int7)((ulonglong)uVar9 >> 8),1);
  }
  return plVar2;
}


// ==== FUN_1400202b0 @ 1400202b0  longlong * FUN_1400202b0(longlong * param_1, longlong * param_2, uint * param_3)

longlong * FUN_1400202b0(longlong *param_1,longlong *param_2,uint *param_3)

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


// ==== FUN_140020380 @ 140020380  undefined8 * FUN_140020380(undefined8 * param_1, undefined8 * param_2, uint * param_3)

undefined8 * FUN_140020380(undefined8 *param_1,undefined8 *param_2,uint *param_3)

{
  FUN_14001fbc0(param_1,param_2,param_3);
  return param_2;
}


// ==== FUN_1400203a0 @ 1400203a0  longlong * FUN_1400203a0(longlong * param_1, longlong * param_2, uint * param_3)

longlong * FUN_1400203a0(longlong *param_1,longlong *param_2,uint *param_3)

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
LAB_1400204fd:
    local_30 = plVar4;
    if (*param_3 <= *(uint *)(plVar5 + 3)) {
      *(undefined1 *)(param_2 + 2) = 0;
      *param_2 = local_38;
      goto LAB_14002052c;
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
      goto LAB_1400204fd;
    }
    bVar7 = true;
  }
  plVar6 = FUN_14001fca0(param_1,&local_38,bVar7,plVar6,(undefined8 *)param_3);
  *(undefined1 *)(param_2 + 2) = 1;
  local_30 = (longlong *)plVar6[1];
  *param_2 = *plVar6;
LAB_14002052c:
  param_2[1] = (longlong)local_30;
  return param_2;
}


// ==== FUN_140020550 @ 140020550  undefined8 * FUN_140020550(longlong param_1, undefined8 * param_2)

undefined8 * FUN_140020550(longlong param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  
  uVar1 = **(undefined8 **)(param_1 + 0x40);
  *param_2 = *(undefined8 *)(param_1 + 0x10);
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_140020570 @ 140020570  undefined8 * FUN_140020570(longlong param_1, undefined8 * param_2)

undefined8 * FUN_140020570(longlong param_1,undefined8 *param_2)

{
  param_2[1] = *(undefined8 *)(param_1 + 0x40);
  *param_2 = *(undefined8 *)(param_1 + 0x10);
  return param_2;
}


// ==== FUN_140020590 @ 140020590  undefined8 FUN_140020590(undefined8 param_1, longlong * param_2)

undefined8 FUN_140020590(undefined8 param_1,longlong *param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_2;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_2;
    if (puVar1 == (undefined8 *)0x0) goto LAB_1400205b2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_1400205b2:
  if (param_2[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return *(undefined8 *)(param_2[1] + 0x20);
}


// ==== FUN_1400205d0 @ 1400205d0  undefined8 FUN_1400205d0(longlong param_1, uint param_2)

undefined8 FUN_1400205d0(longlong param_1,uint param_2)

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


// ==== FUN_1400206d0 @ 1400206d0  longlong FUN_1400206d0(longlong * param_1, uint * param_2)

longlong FUN_1400206d0(longlong *param_1,uint *param_2)

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
  
  FUN_14001fbc0(param_1,&local_38,param_2);
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
  FUN_14001eff0(param_1,&local_38,&local_48,&local_58);
  return lVar8;
}


// ==== FUN_140020810 @ 140020810  longlong * FUN_140020810(longlong * param_1, longlong * param_2, longlong * param_3, uint * param_4)

longlong * FUN_140020810(longlong *param_1,longlong *param_2,longlong *param_3,uint *param_4)

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
    FUN_14001fca0(param_1,param_2,'\x01',(undefined8 *)param_1[6],(undefined8 *)param_4);
  }
  else {
    puVar2 = *(undefined8 **)param_1[6];
    if ((*param_3 == 0) || (*param_3 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    puVar3 = (undefined8 *)param_3[1];
    if (puVar3 == puVar2) {
      if (*param_4 < *(uint *)(puVar3 + 3)) {
        FUN_14001fca0(param_1,param_2,'\x01',puVar3,(undefined8 *)param_4);
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
          FUN_14001fca0(param_1,param_2,'\0',*(undefined8 **)(param_1[6] + 0x10),
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
              FUN_14001fca0(param_1,param_2,'\0',plVar7,(undefined8 *)param_4);
              return param_2;
            }
            FUN_14001fca0(param_1,param_2,'\x01',(undefined8 *)param_3[1],(undefined8 *)param_4);
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
              FUN_14001fca0(param_1,param_2,'\0',(undefined8 *)param_3[1],(undefined8 *)param_4);
              return param_2;
            }
            FUN_14001fca0(param_1,param_2,'\x01',plVar9,(undefined8 *)param_4);
            return param_2;
          }
        }
      }
    }
    plVar7 = FUN_1400203a0(param_1,&local_38,param_4);
    *param_2 = *plVar7;
    param_2[1] = plVar7[1];
  }
  return param_2;
}


// ==== FUN_140020b30 @ 140020b30  bool FUN_140020b30(longlong * param_1, uint param_2)

bool FUN_140020b30(longlong *param_1,uint param_2)

{
  longlong *plVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  longlong lVar4;
  uint local_res10 [2];
  longlong local_38;
  longlong lStack_30;
  undefined8 local_28 [4];
  
  local_res10[0] = param_2;
  if ((char)param_1[1] == '\0') {
    lVar4 = FUN_1400206d0(param_1 + 2,local_res10);
    return lVar4 != 0;
  }
  plVar1 = param_1 + 2;
  FUN_1400202b0(plVar1,&local_38,local_res10);
  lVar4 = param_1[8];
  if ((local_38 == 0) || (local_38 != *plVar1)) {
    _invalid_parameter_noinfo();
  }
  if (lStack_30 != lVar4) {
    plVar3 = (longlong *)(**(code **)(*param_1 + 0x28))(param_1,&local_38);
    if (plVar3 != (longlong *)0x0) {
      puVar2 = (undefined8 *)*plVar3;
      if (puVar2 != (undefined8 *)0x0) {
        (**(code **)*puVar2)(puVar2,0);
      }
      operator_delete(plVar3);
    }
    FUN_14001e820(plVar1,local_28,&local_38);
    return true;
  }
  return false;
}


// ==== FUN_140020c20 @ 140020c20  undefined8 * FUN_140020c20(longlong * param_1, uint * param_2)

undefined8 * FUN_140020c20(longlong *param_1,uint *param_2)

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
    plVar3 = FUN_140020810(param_1,local_28,(longlong *)&local_38,local_48);
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


// ==== FUN_140020d20 @ 140020d20  undefined8 FUN_140020d20(longlong * param_1, undefined8 * param_2)

undefined8 FUN_140020d20(longlong *param_1,undefined8 *param_2)

{
  char cVar1;
  undefined4 uVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  uint local_res8 [2];
  
  if ((char)param_1[1] != '\0') {
    plVar3 = (longlong *)
             (**(code **)(*(longlong *)*param_2 + 0x20))((longlong *)*param_2,&DAT_14010264c);
    uVar2 = (**(code **)(*plVar3 + 0x40))(plVar3);
    cVar1 = (**(code **)(*param_1 + 0x38))(param_1,uVar2);
    if (cVar1 != '\0') {
      log_InlineLogERROR(&DAT_1400be0b0);
    }
  }
  plVar3 = (longlong *)
           (**(code **)(*(longlong *)*param_2 + 0x20))((longlong *)*param_2,&DAT_14010264c);
  local_res8[0] = (**(code **)(*plVar3 + 0x40))(plVar3);
  puVar4 = FUN_140020c20(param_1 + 2,local_res8);
  *puVar4 = param_2;
  return CONCAT71((int7)((ulonglong)puVar4 >> 8),1);
}


// ==== FUN_140020dd0 @ 140020dd0  undefined FUN_140020dd0(undefined8 * param_1)

void FUN_140020dd0(undefined8 *param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong lVar7;
  longlong local_48;
  undefined8 *puStack_40;
  longlong local_38;
  undefined8 uStack_30;
  longlong local_28 [2];
  
  *param_1 = CSingleMap2<class_CConstGameData<&char*_szItemTypeTable,&char*_szItemTypeTableID>_>::
             vftable;
  if ((*(char *)(param_1 + 1) != '\0') && (param_1[9] != 0)) {
    plVar6 = *(longlong **)param_1[8];
    plVar2 = (longlong *)param_1[2];
    while( true ) {
      plVar3 = (longlong *)param_1[8];
      if ((plVar2 == (longlong *)0x0) || (plVar2 != (longlong *)param_1[2])) {
        _invalid_parameter_noinfo();
      }
      if (plVar6 == plVar3) break;
      if (plVar2 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar7 = 0;
      }
      else {
        lVar7 = *plVar2;
      }
      if (plVar6 == *(longlong **)(lVar7 + 0x30)) {
        _invalid_parameter_noinfo();
      }
      plVar3 = (longlong *)plVar6[4];
      if (plVar3 != (longlong *)0x0) {
        puVar4 = (undefined8 *)*plVar3;
        if (puVar4 != (undefined8 *)0x0) {
          (**(code **)*puVar4)(puVar4,0);
        }
        operator_delete(plVar3);
      }
      if (plVar2 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
      }
      if (*(char *)((longlong)plVar6 + 0x29) == '\0') {
        plVar3 = (longlong *)plVar6[2];
        if (*(char *)((longlong)plVar3 + 0x29) == '\0') {
          cVar1 = *(char *)(*plVar3 + 0x29);
          plVar6 = plVar3;
          plVar3 = (longlong *)*plVar3;
          while (cVar1 == '\0') {
            cVar1 = *(char *)(*plVar3 + 0x29);
            plVar6 = plVar3;
            plVar3 = (longlong *)*plVar3;
          }
        }
        else {
          cVar1 = *(char *)(plVar6[1] + 0x29);
          plVar5 = (longlong *)plVar6[1];
          plVar3 = plVar6;
          while ((plVar6 = plVar5, cVar1 == '\0' && (plVar3 == (longlong *)plVar6[2]))) {
            cVar1 = *(char *)(plVar6[1] + 0x29);
            plVar5 = (longlong *)plVar6[1];
            plVar3 = plVar6;
          }
        }
      }
      else {
        _invalid_parameter_noinfo();
      }
    }
  }
  plVar6 = param_1 + 2;
  puStack_40 = (undefined8 *)param_1[8];
  local_48 = *plVar6;
  uStack_30 = *puStack_40;
  local_38 = local_48;
  FUN_14001eff0(plVar6,local_28,&local_38,&local_48);
  operator_delete((void *)param_1[8]);
  param_1[8] = 0;
  param_1[9] = 0;
  operator_delete((void *)*plVar6);
  *param_1 = ISingleMap2<class_CConstGameData<&char*_szItemTypeTable,&char*_szItemTypeTableID>_>::
             vftable;
  return;
}


// ==== FUN_140020fb0 @ 140020fb0  undefined8 * FUN_140020fb0(undefined1 param_1)

undefined8 * FUN_140020fb0(undefined1 param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x50);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = ISingleMap2<class_CConstGameData<&char*_szItemTypeTable,&char*_szItemTypeTableID>_>::
              vftable;
    *puVar1 = CSingleMap2<class_CConstGameData<&char*_szItemTypeTable,&char*_szItemTypeTableID>_>::
              vftable;
    FUN_14001f400(puVar1 + 2);
    *(undefined1 *)(puVar1 + 1) = param_1;
  }
  return puVar1;
}


// ==== FUN_140021020 @ 140021020  undefined8 FUN_140021020(longlong param_1)

ulonglong FUN_140021020(longlong param_1)

{
  longlong *plVar1;
  ulonglong extraout_RAX;
  ulonglong uVar2;
  undefined8 uVar3;
  ulonglong extraout_RAX_00;
  
  plVar1 = (longlong *)operator_new(0x50);
  if (plVar1 == (longlong *)0x0) {
    plVar1 = (longlong *)0x0;
  }
  else {
    *plVar1 = (longlong)
              ISingleMap2<class_CConstGameData<&char*_szItemTypeTable,&char*_szItemTypeTableID>_>::
              vftable;
    *plVar1 = (longlong)
              CSingleMap2<class_CConstGameData<&char*_szItemTypeTable,&char*_szItemTypeTableID>_>::
              vftable;
    FUN_14001f400(plVar1 + 2);
    *(undefined1 *)(plVar1 + 1) = 1;
  }
  *(longlong **)(param_1 + 8) = plVar1;
  if (plVar1 == (longlong *)0x0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    uVar2 = extraout_RAX & 0xffffffffffffff00;
  }
  else {
    uVar3 = (**(code **)(*plVar1 + 8))(plVar1,"SELECT * FROM cq_itemtype");
    if ((char)uVar3 == '\0') {
      log_InlineLogERROR(&DAT_1400be0b0);
      uVar2 = extraout_RAX_00 & 0xffffffffffffff00;
    }
    else {
      uVar2 = CONCAT71((int7)((ulonglong)uVar3 >> 8),1);
    }
  }
  return uVar2;
}


// ==== FUN_140021100 @ 140021100  undefined FUN_140021100(undefined8 * param_1)

void FUN_140021100(undefined8 *param_1)

{
  *param_1 = IGameData::vftable;
  return;
}


// ==== FUN_1400214c0 @ 1400214c0  undefined FUN_1400214c0(undefined8 * param_1)

void FUN_1400214c0(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    (**(code **)*param_1)(param_1,1);
  }
  return;
}


// ==== FUN_1400214e0 @ 1400214e0  bool FUN_1400214e0(longlong * param_1, longlong * param_2)

bool FUN_1400214e0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_140021520 @ 140021520  bool FUN_140021520(longlong * param_1, longlong * param_2)

bool FUN_140021520(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_140021570 @ 140021570  bool FUN_140021570(longlong * param_1, longlong * param_2)

bool FUN_140021570(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_1400215b0 @ 1400215b0  bool FUN_1400215b0(longlong * param_1, longlong * param_2)

bool FUN_1400215b0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_140021890 @ 140021890  undefined FUN_140021890(longlong * param_1)

void FUN_140021890(longlong *param_1)

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
                    /* WARNING: Could not recover jumptable at 0x0001400218c2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_1400219f0 @ 1400219f0  undefined FUN_1400219f0(undefined8 * param_1)

void FUN_1400219f0(undefined8 *param_1)

{
  if ((undefined8 *)*param_1 != (undefined8 *)0x0) {
    FUN_140048f90((undefined8 *)*param_1);
    *param_1 = 0;
  }
  return;
}


// ==== FUN_140021a20 @ 140021a20  undefined FUN_140021a20(undefined8 * param_1)

void FUN_140021a20(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    (**(code **)*param_1)(param_1,1);
  }
  return;
}


// ==== FUN_140021a40 @ 140021a40  undefined FUN_140021a40(longlong * param_1)

void FUN_140021a40(longlong *param_1)

{
  if ((longlong *)*param_1 != (longlong *)0x0) {
    (**(code **)(*(longlong *)*param_1 + 0x58))();
    *param_1 = 0;
  }
  return;
}


// ==== FUN_140021aa0 @ 140021aa0  undefined FUN_140021aa0(ulonglong param_1)

void FUN_140021aa0(ulonglong param_1)

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


// ==== FUN_140021b20 @ 140021b20  undefined FUN_140021b20(ulonglong param_1)

void FUN_140021b20(ulonglong param_1)

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


// ==== FUN_140021c50 @ 140021c50  undefined FUN_140021c50(undefined8 * param_1)

void FUN_140021c50(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140021c80 @ 140021c80  undefined FUN_140021c80(undefined8 * param_1)

void FUN_140021c80(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140021c90 @ 140021c90  longlong FUN_140021c90(longlong * param_1)

longlong FUN_140021c90(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140021cb2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140021cb2:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_140021cd0 @ 140021cd0  longlong FUN_140021cd0(longlong * param_1)

longlong FUN_140021cd0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140021cf2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140021cf2:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_140021d50 @ 140021d50  undefined FUN_140021d50(longlong param_1, longlong param_2)

void FUN_140021d50(longlong param_1,longlong param_2)

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


// ==== FUN_140021db0 @ 140021db0  undefined FUN_140021db0(longlong param_1, longlong * param_2)

void FUN_140021db0(longlong param_1,longlong *param_2)

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


// ==== FUN_140021e60 @ 140021e60  undefined FUN_140021e60(longlong param_1, longlong param_2)

void FUN_140021e60(longlong param_1,longlong param_2)

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


// ==== FUN_140021ec0 @ 140021ec0  undefined FUN_140021ec0(longlong param_1, longlong * param_2)

void FUN_140021ec0(longlong param_1,longlong *param_2)

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


// ==== FUN_140021f30 @ 140021f30  longlong * FUN_140021f30(longlong * param_1)

longlong * FUN_140021f30(longlong *param_1)

{
  FUN_140021890(param_1);
  return param_1;
}


// ==== FUN_140021f50 @ 140021f50  undefined FUN_140021f50(longlong * param_1)

void FUN_140021f50(longlong *param_1)

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
                    /* WARNING: Could not recover jumptable at 0x000140021f74. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_140021fe0 @ 140021fe0  undefined FUN_140021fe0(longlong * param_1)

void FUN_140021fe0(longlong *param_1)

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
                    /* WARNING: Could not recover jumptable at 0x000140022004. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_140022090 @ 140022090  undefined FUN_140022090(undefined8 param_1, ulonglong param_2)

void FUN_140022090(undefined8 param_1,ulonglong param_2)

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


// ==== FUN_140022100 @ 140022100  undefined FUN_140022100(undefined8 param_1, ulonglong param_2)

void FUN_140022100(undefined8 param_1,ulonglong param_2)

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


// ==== FUN_140022180 @ 140022180  undefined FUN_140022180(longlong * param_1)

void FUN_140022180(longlong *param_1)

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
                    /* WARNING: Could not recover jumptable at 0x0001400221b2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_140022250 @ 140022250  undefined8 * FUN_140022250(undefined8 * param_1, undefined1 param_2)

undefined8 * FUN_140022250(undefined8 *param_1,undefined1 param_2)

{
  *param_1 = IGameData::vftable;
  *param_1 = CGameData<&char*_szInstanceTypeTable,&char*_szID>::vftable;
  *(undefined1 *)(param_1 + 2) = param_2;
  param_1[1] = 0;
  return param_1;
}


// ==== FUN_140022290 @ 140022290  undefined FUN_140022290(undefined8 * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_140022290(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 *puVar1;
  
  *param_1 = CGameData<&char*_szInstanceTypeTable,&char*_szID>::vftable;
  puVar1 = (undefined8 *)param_1[1];
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,*(char *)(param_1 + 2) == '\0',param_3,param_4,0xfffffffffffffffe);
  }
  *param_1 = IGameData::vftable;
  return;
}


// ==== FUN_1400222e0 @ 1400222e0  undefined FUN_1400222e0(longlong param_1)

void FUN_1400222e0(longlong param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)
           (**(code **)(**(longlong **)(param_1 + 8) + 0x20))
                     (*(longlong **)(param_1 + 8),&DAT_140102d90);
                    /* WARNING: Could not recover jumptable at 0x0001400222ff. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x40))(plVar1);
  return;
}


// ==== FUN_140022310 @ 140022310  undefined FUN_140022310(longlong param_1)

void FUN_140022310(longlong param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(**(code **)(**(longlong **)(param_1 + 8) + 0x10))();
                    /* WARNING: Could not recover jumptable at 0x000140022328. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x48))(plVar1);
  return;
}


// ==== FUN_140022330 @ 140022330  undefined FUN_140022330(longlong param_1)

void FUN_140022330(longlong param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(**(code **)(**(longlong **)(param_1 + 8) + 0x10))();
                    /* WARNING: Could not recover jumptable at 0x000140022348. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x78))(plVar1);
  return;
}


// ==== FUN_140022350 @ 140022350  undefined FUN_140022350(longlong param_1)

void FUN_140022350(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x000140022357. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(longlong **)(param_1 + 8) + 0x58))();
  return;
}


// ==== FUN_140022360 @ 140022360  undefined FUN_140022360(longlong param_1, undefined4 param_2, longlong * param_3)

void FUN_140022360(longlong param_1,undefined4 param_2,longlong *param_3)

{
  longlong *plVar1;
  longlong lVar2;
  undefined8 uVar3;
  undefined1 auStack_458 [32];
  undefined4 local_438;
  char local_428 [1024];
  ulonglong local_28;
  
  local_28 = DAT_140103510 ^ (ulonglong)auStack_458;
  if (param_3 == (longlong *)0x0) {
    local_438 = 0x5c;
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  else if (*(char *)(param_1 + 0x10) == '\0') {
    local_438 = param_2;
    sprintf(local_428,"SELECT * FROM %s WHERE %s=%lu LIMIT 1");
    plVar1 = (longlong *)(**(code **)(*param_3 + 0x10))(param_3,local_428,2);
    if (plVar1 != (longlong *)0x0) {
      lVar2 = (**(code **)(*plVar1 + 0x40))(plVar1);
      if (lVar2 == 0) {
        uVar3 = (**(code **)(*param_3 + 0x20))(param_3,s_cq_instancetype_140102d58);
      }
      else {
        uVar3 = (**(code **)(*plVar1 + 0x38))(plVar1);
      }
      *(undefined8 *)(param_1 + 8) = uVar3;
      (**(code **)*plVar1)(plVar1);
    }
  }
  else {
    local_438 = 0x5e;
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  __security_check_cookie(local_28 ^ (ulonglong)auStack_458);
  return;
}


// ==== FUN_1400224a0 @ 1400224a0  bool FUN_1400224a0(longlong param_1, longlong * param_2)

bool FUN_1400224a0(longlong param_1,longlong *param_2)

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


// ==== FUN_140022500 @ 140022500  bool FUN_140022500(longlong param_1, undefined8 param_2)

bool FUN_140022500(longlong param_1,undefined8 param_2)

{
  longlong *plVar1;
  longlong lVar2;
  
  plVar1 = (longlong *)InstanceGet();
  lVar2 = (**(code **)(*plVar1 + 0x20))(plVar1,param_2);
  *(longlong *)(param_1 + 8) = lVar2;
  return lVar2 != 0;
}


// ==== FUN_140022540 @ 140022540  bool FUN_140022540(longlong param_1)

bool FUN_140022540(longlong param_1)

{
  longlong *plVar1;
  longlong lVar2;
  
  plVar1 = (longlong *)InstanceGet();
  lVar2 = (**(code **)(*plVar1 + 0x20))(plVar1,s_cq_instancetype_140102d58);
  *(longlong *)(param_1 + 8) = lVar2;
  return lVar2 != 0;
}


// ==== FUN_140022570 @ 140022570  ulonglong FUN_140022570(longlong param_1)

ulonglong FUN_140022570(longlong param_1)

{
  ulonglong extraout_RAX;
  ulonglong uVar1;
  
  if (*(char *)(param_1 + 0x10) != '\0') {
    log_InlineLogERROR(&DAT_1400be0b0);
    return extraout_RAX & 0xffffffffffffff00;
  }
                    /* WARNING: Could not recover jumptable at 0x0001400225b6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (**(code **)(**(longlong **)(param_1 + 8) + 0x40))();
  return uVar1;
}


// ==== FUN_1400225c0 @ 1400225c0  undefined FUN_1400225c0(longlong param_1)

void FUN_1400225c0(longlong param_1)

{
  longlong *plVar1;
  
  (**(code **)(**(longlong **)(param_1 + 8) + 0x50))(*(longlong **)(param_1 + 8),1);
  plVar1 = (longlong *)
           (**(code **)(**(longlong **)(param_1 + 8) + 0x20))
                     (*(longlong **)(param_1 + 8),&DAT_140102d90);
                    /* WARNING: Could not recover jumptable at 0x0001400225f1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x40))(plVar1);
  return;
}


// ==== FUN_140022600 @ 140022600  undefined FUN_140022600(undefined8 * param_1)

void FUN_140022600(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    (**(code **)*param_1)(param_1,1);
  }
  return;
}


// ==== FUN_140022620 @ 140022620  undefined FUN_140022620(longlong param_1, undefined8 param_2, undefined4 param_3)

void FUN_140022620(longlong param_1,undefined8 param_2,undefined4 param_3)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(**(code **)(**(longlong **)(param_1 + 8) + 0x10))();
                    /* WARNING: Could not recover jumptable at 0x000140022640. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0xb0))(plVar1,param_3);
  return;
}


// ==== FUN_140022650 @ 140022650  undefined FUN_140022650(longlong param_1, undefined8 param_2, undefined8 param_3)

void FUN_140022650(longlong param_1,undefined8 param_2,undefined8 param_3)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(**(code **)(**(longlong **)(param_1 + 8) + 0x10))();
                    /* WARNING: Could not recover jumptable at 0x000140022671. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x80))(plVar1,param_3);
  return;
}


// ==== FUN_140022680 @ 140022680  undefined8 FUN_140022680(longlong param_1)

undefined8 FUN_140022680(longlong param_1)

{
  undefined8 in_RAX;
  undefined8 uVar1;
  
  if (*(char *)(param_1 + 0x10) == '\0') {
                    /* WARNING: Could not recover jumptable at 0x00014002268f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(**(longlong **)(param_1 + 8) + 0x38))(*(longlong **)(param_1 + 8),0);
    return uVar1;
  }
  return CONCAT71((int7)((ulonglong)in_RAX >> 8),1);
}


// ==== FUN_140022710 @ 140022710  longlong FUN_140022710(longlong * param_1)

longlong FUN_140022710(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140022732;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140022732:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_140022750 @ 140022750  longlong FUN_140022750(longlong * param_1)

longlong FUN_140022750(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140022772;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140022772:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_140022790 @ 140022790  longlong FUN_140022790(longlong * param_1)

longlong FUN_140022790(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_1400227b2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_1400227b2:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_1400227d0 @ 1400227d0  undefined FUN_1400227d0(undefined8 * param_1)

void FUN_1400227d0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_1400227f0 @ 1400227f0  undefined FUN_1400227f0(undefined8 * param_1)

void FUN_1400227f0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140022810 @ 140022810  longlong * FUN_140022810(longlong * param_1)

longlong * FUN_140022810(longlong *param_1)

{
  FUN_140021890(param_1);
  return param_1;
}


// ==== FUN_140022830 @ 140022830  longlong * FUN_140022830(longlong * param_1)

longlong * FUN_140022830(longlong *param_1)

{
  FUN_140021f50(param_1);
  return param_1;
}


// ==== FUN_140022850 @ 140022850  longlong * FUN_140022850(longlong * param_1)

longlong * FUN_140022850(longlong *param_1)

{
  FUN_140021fe0(param_1);
  return param_1;
}


// ==== FUN_140022870 @ 140022870  undefined8 * FUN_140022870(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, undefined8 * param_5, undefined1 param_6)

undefined8 *
FUN_140022870(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
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


// ==== FUN_1400228f0 @ 1400228f0  undefined8 * FUN_1400228f0(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, undefined8 * param_5, undefined1 param_6)

undefined8 *
FUN_1400228f0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
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


// ==== FUN_140022970 @ 140022970  undefined8 * FUN_140022970(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_140022970(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_1400229b0 @ 1400229b0  longlong * FUN_1400229b0(longlong * param_1, longlong * param_2)

longlong * FUN_1400229b0(longlong *param_1,longlong *param_2)

{
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  FUN_140021f50(param_1);
  return param_2;
}


// ==== FUN_1400229e0 @ 1400229e0  undefined8 * FUN_1400229e0(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_1400229e0(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_140022a20 @ 140022a20  longlong * FUN_140022a20(longlong * param_1)

longlong * FUN_140022a20(longlong *param_1)

{
  FUN_140022180(param_1);
  return param_1;
}


// ==== FUN_140022a40 @ 140022a40  undefined FUN_140022a40(void)

void FUN_140022a40(void)

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


// ==== FUN_140022aa0 @ 140022aa0  undefined FUN_140022aa0(undefined8 param_1, longlong * param_2)

void FUN_140022aa0(undefined8 param_1,longlong *param_2)

{
  char cVar1;
  longlong *plVar2;
  
  cVar1 = *(char *)((longlong)param_2 + 0x29);
  while (cVar1 == '\0') {
    FUN_140022aa0(param_1,(longlong *)param_2[2]);
    plVar2 = (longlong *)*param_2;
    operator_delete(param_2);
    param_2 = plVar2;
    cVar1 = *(char *)((longlong)plVar2 + 0x29);
  }
  return;
}


// ==== FUN_140022af0 @ 140022af0  undefined FUN_140022af0(void)

void FUN_140022af0(void)

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


// ==== FUN_140022b50 @ 140022b50  longlong * FUN_140022b50(longlong * param_1, longlong * param_2)

longlong * FUN_140022b50(longlong *param_1,longlong *param_2)

{
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  FUN_140021fe0(param_1);
  return param_2;
}


// ==== FUN_140022b80 @ 140022b80  undefined FUN_140022b80(undefined8 param_1, longlong * param_2)

void FUN_140022b80(undefined8 param_1,longlong *param_2)

{
  char cVar1;
  longlong *plVar2;
  
  cVar1 = *(char *)((longlong)param_2 + 0x29);
  while (cVar1 == '\0') {
    FUN_140022b80(param_1,(longlong *)param_2[2]);
    plVar2 = (longlong *)*param_2;
    operator_delete(param_2);
    param_2 = plVar2;
    cVar1 = *(char *)((longlong)plVar2 + 0x29);
  }
  return;
}


// ==== FUN_140022bd0 @ 140022bd0  undefined8 * FUN_140022bd0(undefined8 * param_1)

undefined8 * FUN_140022bd0(undefined8 *param_1)

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


// ==== FUN_140022c10 @ 140022c10  undefined8 * FUN_140022c10(undefined8 * param_1)

undefined8 * FUN_140022c10(undefined8 *param_1)

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


// ==== FUN_140022c50 @ 140022c50  undefined8 * FUN_140022c50(undefined1 param_1)

undefined8 * FUN_140022c50(undefined1 param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x18);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = IGameData::vftable;
    *puVar1 = CGameData<&char*_szInstanceTypeTable,&char*_szID>::vftable;
    *(undefined1 *)(puVar1 + 2) = param_1;
    puVar1[1] = 0;
  }
  return puVar1;
}


// ==== FUN_140022ca0 @ 140022ca0  longlong * FUN_140022ca0(longlong * param_1)

longlong * FUN_140022ca0(longlong *param_1)

{
  FUN_140021f50(param_1);
  return param_1;
}


// ==== FUN_140022cc0 @ 140022cc0  longlong * FUN_140022cc0(longlong * param_1)

longlong * FUN_140022cc0(longlong *param_1)

{
  FUN_140021fe0(param_1);
  return param_1;
}


// ==== FUN_140022ce0 @ 140022ce0  undefined FUN_140022ce0(undefined8 * param_1)

void FUN_140022ce0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140022d00 @ 140022d00  undefined FUN_140022d00(undefined8 * param_1)

void FUN_140022d00(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140022d20 @ 140022d20  undefined8 * FUN_140022d20(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_140022d20(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_140022d60 @ 140022d60  undefined8 * FUN_140022d60(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_140022d60(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_140022da0 @ 140022da0  longlong * FUN_140022da0(longlong * param_1)

longlong * FUN_140022da0(longlong *param_1)

{
  FUN_140022180(param_1);
  return param_1;
}


// ==== FUN_140022dc0 @ 140022dc0  undefined FUN_140022dc0(longlong param_1)

void FUN_140022dc0(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = FUN_140022a40();
  *(longlong *)(param_1 + 0x30) = lVar1;
  *(undefined1 *)(lVar1 + 0x29) = 1;
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)*(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x30);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 0x10) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = 0;
  return;
}


// ==== FUN_140022e00 @ 140022e00  undefined8 * FUN_140022e00(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_140022e00(undefined8 *param_1,undefined8 *param_2,longlong param_3)

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


// ==== FUN_140022e50 @ 140022e50  undefined8 * FUN_140022e50(undefined8 * param_1, undefined8 * param_2, longlong * param_3)

undefined8 * FUN_140022e50(undefined8 *param_1,undefined8 *param_2,longlong *param_3)

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
  FUN_140021f50(param_3);
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
        goto LAB_14002303c;
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
LAB_14002303c:
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
            FUN_140021e60((longlong)param_1,(longlong)plVar7);
            plVar8 = (longlong *)plVar7[2];
          }
          if (*(char *)((longlong)plVar8 + 0x29) == '\0') {
            if ((*(char *)(*plVar8 + 0x28) != '\x01') || (*(char *)(plVar8[2] + 0x28) != '\x01')) {
              if (*(char *)(plVar8[2] + 0x28) == '\x01') {
                *(undefined1 *)(*plVar8 + 0x28) = 1;
                *(undefined1 *)(plVar8 + 5) = 0;
                FUN_140021ec0((longlong)param_1,plVar8);
                plVar8 = (longlong *)plVar7[2];
              }
              *(char *)(plVar8 + 5) = (char)plVar7[5];
              *(undefined1 *)(plVar7 + 5) = 1;
              *(undefined1 *)(plVar8[2] + 0x28) = 1;
              FUN_140021e60((longlong)param_1,(longlong)plVar7);
              break;
            }
            *(undefined1 *)(plVar8 + 5) = 0;
          }
        }
        else {
          if ((char)plVar8[5] == '\0') {
            *(undefined1 *)(plVar8 + 5) = 1;
            *(undefined1 *)(plVar7 + 5) = 0;
            FUN_140021ec0((longlong)param_1,plVar7);
            plVar8 = (longlong *)*plVar7;
          }
          if (*(char *)((longlong)plVar8 + 0x29) == '\0') {
            if ((*(char *)(plVar8[2] + 0x28) != '\x01') || (*(char *)(*plVar8 + 0x28) != '\x01')) {
              if (*(char *)(*plVar8 + 0x28) == '\x01') {
                *(undefined1 *)(plVar8[2] + 0x28) = 1;
                *(undefined1 *)(plVar8 + 5) = 0;
                FUN_140021e60((longlong)param_1,(longlong)plVar8);
                plVar8 = (longlong *)*plVar7;
              }
              *(char *)(plVar8 + 5) = (char)plVar7[5];
              *(undefined1 *)(plVar7 + 5) = 1;
              *(undefined1 *)(*plVar8 + 0x28) = 1;
              FUN_140021ec0((longlong)param_1,plVar7);
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


// ==== FUN_140023210 @ 140023210  undefined FUN_140023210(longlong param_1)

void FUN_140023210(longlong param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  
  plVar2 = *(longlong **)(*(longlong *)(param_1 + 0x30) + 8);
  cVar1 = *(char *)((longlong)plVar2 + 0x29);
  while (cVar1 == '\0') {
    FUN_140022aa0(param_1,(longlong *)plVar2[2]);
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


// ==== FUN_140023290 @ 140023290  undefined8 * FUN_140023290(undefined8 * param_1, undefined8 * param_2, uint * param_3)

undefined8 * FUN_140023290(undefined8 *param_1,undefined8 *param_2,uint *param_3)

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


// ==== FUN_140023370 @ 140023370  undefined FUN_140023370(longlong param_1)

void FUN_140023370(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = FUN_140022af0();
  *(longlong *)(param_1 + 0x30) = lVar1;
  *(undefined1 *)(lVar1 + 0x29) = 1;
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)*(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x30);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 0x10) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = 0;
  return;
}


// ==== FUN_1400233b0 @ 1400233b0  undefined8 * FUN_1400233b0(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_1400233b0(undefined8 *param_1,undefined8 *param_2,longlong param_3)

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


// ==== FUN_140023400 @ 140023400  undefined8 * FUN_140023400(undefined8 * param_1, undefined8 * param_2, longlong * param_3)

undefined8 * FUN_140023400(undefined8 *param_1,undefined8 *param_2,longlong *param_3)

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
  FUN_140021fe0(param_3);
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
        goto LAB_1400235ec;
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
LAB_1400235ec:
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
            FUN_140021d50((longlong)param_1,(longlong)plVar7);
            plVar8 = (longlong *)plVar7[2];
          }
          if (*(char *)((longlong)plVar8 + 0x29) == '\0') {
            if ((*(char *)(*plVar8 + 0x28) != '\x01') || (*(char *)(plVar8[2] + 0x28) != '\x01')) {
              if (*(char *)(plVar8[2] + 0x28) == '\x01') {
                *(undefined1 *)(*plVar8 + 0x28) = 1;
                *(undefined1 *)(plVar8 + 5) = 0;
                FUN_140021db0((longlong)param_1,plVar8);
                plVar8 = (longlong *)plVar7[2];
              }
              *(char *)(plVar8 + 5) = (char)plVar7[5];
              *(undefined1 *)(plVar7 + 5) = 1;
              *(undefined1 *)(plVar8[2] + 0x28) = 1;
              FUN_140021d50((longlong)param_1,(longlong)plVar7);
              break;
            }
            *(undefined1 *)(plVar8 + 5) = 0;
          }
        }
        else {
          if ((char)plVar8[5] == '\0') {
            *(undefined1 *)(plVar8 + 5) = 1;
            *(undefined1 *)(plVar7 + 5) = 0;
            FUN_140021db0((longlong)param_1,plVar7);
            plVar8 = (longlong *)*plVar7;
          }
          if (*(char *)((longlong)plVar8 + 0x29) == '\0') {
            if ((*(char *)(plVar8[2] + 0x28) != '\x01') || (*(char *)(*plVar8 + 0x28) != '\x01')) {
              if (*(char *)(*plVar8 + 0x28) == '\x01') {
                *(undefined1 *)(plVar8[2] + 0x28) = 1;
                *(undefined1 *)(plVar8 + 5) = 0;
                FUN_140021d50((longlong)param_1,(longlong)plVar8);
                plVar8 = (longlong *)*plVar7;
              }
              *(char *)(plVar8 + 5) = (char)plVar7[5];
              *(undefined1 *)(plVar7 + 5) = 1;
              *(undefined1 *)(*plVar8 + 0x28) = 1;
              FUN_140021db0((longlong)param_1,plVar7);
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


// ==== FUN_1400237c0 @ 1400237c0  undefined FUN_1400237c0(longlong param_1)

void FUN_1400237c0(longlong param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  
  plVar2 = *(longlong **)(*(longlong *)(param_1 + 0x30) + 8);
  cVar1 = *(char *)((longlong)plVar2 + 0x29);
  while (cVar1 == '\0') {
    FUN_140022b80(param_1,(longlong *)plVar2[2]);
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


// ==== FUN_140023840 @ 140023840  undefined8 * FUN_140023840(undefined8 * param_1)

undefined8 * FUN_140023840(undefined8 *param_1)

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


// ==== FUN_140023890 @ 140023890  undefined8 * FUN_140023890(undefined8 * param_1)

undefined8 * FUN_140023890(undefined8 *param_1)

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


// ==== FUN_1400238e0 @ 1400238e0  undefined FUN_1400238e0(longlong * param_1, longlong * param_2, longlong * param_3)

void FUN_1400238e0(longlong *param_1,longlong *param_2,longlong *param_3)

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


// ==== FUN_140023a30 @ 140023a30  undefined FUN_140023a30(undefined8 * param_1)

void FUN_140023a30(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140023a50 @ 140023a50  undefined FUN_140023a50(undefined8 * param_1)

void FUN_140023a50(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


