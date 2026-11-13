// NpcServer.exe :: CMsgMagicEffect  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMsgMagicEffect::vf_0x8 @ 140064380  ulonglong vf_0x8(longlong param_1, void * param_2, uint param_3)

ulonglong CMsgMagicEffect::vf_0x8(longlong param_1,void *param_2,uint param_3)

{
  ulonglong uVar1;
  
  uVar1 = CNetMsg::vf_0x8(param_1,param_2,param_3);
  if ((int)uVar1 == 0) {
    return uVar1;
  }
  return (ulonglong)(*(int *)(param_1 + 8) == 0x451);
}


// ==== CMsgMagicEffect::vf_0x18 @ 1400643b0  undefined vf_0x18(longlong param_1)

void CMsgMagicEffect::vf_0x18(longlong param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int *piVar5;
  int iVar6;
  longlong lVar7;
  longlong *plVar8;
  longlong *plVar9;
  ulonglong uVar10;
  ulonglong uVar11;
  uint uVar12;
  ulonglong uVar13;
  
  puVar4 = *(undefined4 **)(param_1 + 0x418);
  lVar7 = FUN_14001c7a0();
  plVar8 = (longlong *)FUN_140027a40(lVar7,*puVar4);
  if (plVar8 != (longlong *)0x0) {
    (**(code **)(*plVar8 + 0xc0))(plVar8);
  }
  piVar5 = *(int **)(param_1 + 0x418);
  lVar7 = FUN_14001c210();
  plVar8 = (longlong *)FUN_140038010(lVar7,*piVar5);
  uVar11 = 0;
  if ((plVar8 != (longlong *)0x0) && (*(short *)(*(longlong *)(param_1 + 0x418) + 8) != 2)) {
    iVar2 = *(int *)(*(longlong *)(param_1 + 0x418) + 4);
    if ((iVar2 != 0) && (iVar6 = (**(code **)(*plVar8 + 0x28))(plVar8), iVar2 != iVar6)) {
      lVar7 = FUN_14001c7a0();
      plVar9 = (longlong *)FUN_140027a40(lVar7,iVar2);
      if (plVar9 != (longlong *)0x0) {
        (**(code **)(*plVar9 + 200))(plVar9,plVar8);
      }
    }
    lVar7 = *(longlong *)(param_1 + 0x418);
    uVar10 = uVar11;
    uVar13 = uVar11;
    if (*(char *)(lVar7 + 0xd) != '\0') {
      do {
        iVar6 = *(int *)(uVar10 + 0x10 + lVar7);
        if (iVar6 != iVar2) {
          lVar7 = FUN_14001c7a0();
          plVar9 = (longlong *)FUN_140027a40(lVar7,iVar6);
          if (plVar9 != (longlong *)0x0) {
            (**(code **)(*plVar9 + 200))(plVar9,plVar8);
          }
        }
        lVar7 = *(longlong *)(param_1 + 0x418);
        uVar12 = (int)uVar13 + 1;
        uVar10 = uVar10 + 0x20;
        uVar13 = (ulonglong)uVar12;
      } while ((int)uVar12 < (int)(uint)*(byte *)(lVar7 + 0xd));
    }
  }
  uVar3 = **(undefined4 **)(param_1 + 0x418);
  lVar7 = FUN_14001c210();
  plVar8 = (longlong *)
           (**(code **)(**(longlong **)(lVar7 + 8) + 0x30))(*(longlong **)(lVar7 + 8),uVar3);
  if (plVar8 == (longlong *)0x0) {
    return;
  }
  lVar7 = *(longlong *)(param_1 + 0x418);
  uVar1 = *(ushort *)(lVar7 + 8);
  if (uVar1 < 0x2bad) {
    if (((uVar1 != 0x2bac) && (uVar1 != 9)) && ((uVar1 != 10 && (uVar1 != 0x2849)))) {
      if (uVar1 == 0x2b3e) {
        uVar10 = uVar11;
        if (*(char *)(lVar7 + 0xd) == '\0') {
          return;
        }
        do {
          if (*(int *)(uVar10 + 0x14 + lVar7) != -1) {
            lVar7 = *(longlong *)(param_1 + 0x418);
            uVar3 = *(undefined4 *)(uVar10 + 0x10 + lVar7);
            iVar2 = *(int *)(uVar10 + 0x24 + lVar7);
            iVar6 = *(int *)(uVar10 + 0x28 + lVar7);
            lVar7 = FUN_14001c210();
            plVar8 = (longlong *)
                     (**(code **)(**(longlong **)(lVar7 + 8) + 0x30))
                               (*(longlong **)(lVar7 + 8),uVar3);
            if (plVar8 != (longlong *)0x0) {
              FUN_140066560(plVar8,iVar2,iVar6,0);
            }
          }
          lVar7 = *(longlong *)(param_1 + 0x418);
          uVar12 = (int)uVar11 + 1;
          uVar11 = (ulonglong)uVar12;
          uVar10 = uVar10 + 0x20;
        } while ((int)uVar12 < (int)(uint)*(byte *)(lVar7 + 0xd));
        return;
      }
      if (uVar1 != 0x2b66) {
        return;
      }
    }
  }
  else if ((((uVar1 != 0x2f58) && (uVar1 != 0x2f62)) && (uVar1 != 0x2f6c)) && (uVar1 != 0x3020)) {
    return;
  }
  FUN_140066560(plVar8,(uint)*(ushort *)(lVar7 + 4),(uint)*(ushort *)(lVar7 + 6),0);
  return;
}


// ==== CMsgMagicEffect::vf_0x0 @ 140064600  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMsgMagicEffect::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  FUN_140034810(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


