// NpcServer.exe :: CMsgInteract  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMsgInteract::vf_0x8 @ 1400646d0  ulonglong vf_0x8(longlong param_1, void * param_2, uint param_3)

ulonglong CMsgInteract::vf_0x8(longlong param_1,void *param_2,uint param_3)

{
  ulonglong uVar1;
  
  uVar1 = CNetMsg::vf_0x8(param_1,param_2,param_3);
  if ((int)uVar1 == 0) {
    return uVar1;
  }
  return (ulonglong)(*(int *)(param_1 + 8) == 0x3fe);
}


// ==== CMsgInteract::vf_0x0 @ 1400647f0  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMsgInteract::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  FUN_140034810(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CMsgInteract::vf_0x18 @ 140064840  undefined vf_0x18(longlong param_1)

void CMsgInteract::vf_0x18(longlong param_1)

{
  ushort uVar1;
  ushort uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  bool bVar6;
  char cVar7;
  longlong lVar8;
  longlong lVar9;
  longlong lVar10;
  longlong *plVar11;
  uint uVar12;
  
  lVar9 = *(longlong *)(param_1 + 0x418);
  lVar8 = FUN_14001c210();
  lVar9 = FUN_140038010(lVar8,*(int *)(lVar9 + 8));
  if (lVar9 == 0) {
    return;
  }
  lVar8 = *(longlong *)(param_1 + 0x418);
  switch(*(undefined2 *)(lVar8 + 0x14)) {
  case 1:
  case 4:
  case 5:
  case 6:
    lVar10 = FUN_14001c7a0();
    plVar11 = (longlong *)FUN_140027a40(lVar10,*(undefined4 *)(lVar8 + 0xc));
    if (plVar11 != (longlong *)0x0) {
      (**(code **)(*plVar11 + 200))(plVar11,lVar9);
    }
    break;
  case 2:
  case 0x1c:
    lVar10 = FUN_14001c7a0();
    plVar11 = (longlong *)FUN_140027a40(lVar10,*(undefined4 *)(lVar8 + 8));
    if (plVar11 == (longlong *)0x0) {
LAB_140064969:
      lVar8 = *(longlong *)(param_1 + 0x418);
      lVar10 = FUN_14001c7a0();
      plVar11 = (longlong *)FUN_140027a40(lVar10,*(undefined4 *)(lVar8 + 0xc));
      if (plVar11 != (longlong *)0x0) {
        (**(code **)(*plVar11 + 200))(plVar11,lVar9);
        uVar5 = *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 8);
        lVar9 = FUN_14001c210();
        lVar9 = (**(code **)(**(longlong **)(lVar9 + 8) + 0x30))(*(longlong **)(lVar9 + 8),uVar5);
        if ((lVar9 != 0) && (*(int *)(*(longlong *)(param_1 + 0x418) + 0x18) != 0)) {
          lVar9 = (**(code **)(*plVar11 + 0xb0))(plVar11,0x1040,0);
          if (lVar9 == 0) goto LAB_1400649f8;
          FUN_14005abc0(lVar9,*(int *)(*(longlong *)(param_1 + 0x418) + 0x18));
        }
      }
    }
    else {
      (**(code **)(*plVar11 + 0xc0))(plVar11);
      uVar5 = *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 0xc);
      lVar8 = FUN_14001c210();
      lVar8 = (**(code **)(**(longlong **)(lVar8 + 8) + 0x30))(*(longlong **)(lVar8 + 8),uVar5);
      if ((lVar8 == 0) || (*(int *)(*(longlong *)(param_1 + 0x418) + 0x18) == 0))
      goto LAB_140064969;
      lVar8 = (**(code **)(*plVar11 + 0xb0))(plVar11,0x1040,0);
      if (lVar8 != 0) {
        FUN_14005abf0(lVar8,*(int *)(*(longlong *)(param_1 + 0x418) + 0x18));
        goto LAB_140064969;
      }
LAB_1400649f8:
      log_InlineLogERROR(&DAT_1400be0b0);
    }
    break;
  case 3:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x17:
  case 0x18:
  case 0x1a:
  case 0x1d:
  case 0x1e:
  case 0x1f:
  case 0x20:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
  case 0x26:
  case 0x27:
  case 0x28:
  case 0x29:
  case 0x2a:
  case 0x2b:
  case 0x2c:
  case 0x2d:
  case 0x2e:
  case 0x2f:
  case 0x30:
  case 0x31:
  case 0x32:
  case 0x33:
  case 0x34:
    break;
  case 0xe:
    bVar6 = FUN_14001c1e0(*(int *)(lVar8 + 0xc));
    if (!bVar6) {
      lVar8 = *(longlong *)(param_1 + 0x418);
      lVar10 = FUN_14001c7a0();
      plVar11 = (longlong *)FUN_140027a40(lVar10,*(undefined4 *)(lVar8 + 0xc));
      if (plVar11 != (longlong *)0x0) {
        (**(code **)(*plVar11 + 0xd0))(plVar11,lVar9);
      }
    }
    break;
  case 0x15:
    log_InlineLogERROR(&DAT_1400be0b0);
    break;
  case 0x16:
    lVar10 = FUN_14001c7a0();
    plVar11 = (longlong *)FUN_140027a40(lVar10,*(undefined4 *)(lVar8 + 0xc));
    if (plVar11 != (longlong *)0x0) {
      (**(code **)(*plVar11 + 200))(plVar11,lVar9);
    }
    uVar5 = *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 8);
    lVar9 = FUN_14001c210();
    plVar11 = (longlong *)
              (**(code **)(**(longlong **)(lVar9 + 8) + 0x30))(*(longlong **)(lVar9 + 8),uVar5);
    if (plVar11 != (longlong *)0x0) {
      lVar9 = *(longlong *)(param_1 + 0x418);
      FUN_140066560(plVar11,(uint)*(ushort *)(lVar9 + 0x10),(uint)*(ushort *)(lVar9 + 0x12),
                    (char)*(undefined4 *)(lVar9 + 0x18));
    }
    break;
  case 0x19:
    log_InlineLogERROR(&DAT_1400be0b0);
    break;
  case 0x1b:
    uVar5 = *(undefined4 *)(lVar8 + 0x18);
    uVar3 = *(undefined4 *)(lVar8 + 8);
    lVar8 = FUN_14001c210();
    plVar11 = (longlong *)
              (**(code **)(**(longlong **)(lVar8 + 8) + 0x30))(*(longlong **)(lVar8 + 8),uVar3);
    if ((plVar11 != (longlong *)0x0) && ((~(byte)((uint)uVar5 >> 0x1c) & 1) != 0)) {
      FUN_140065eb0(plVar11,(uint)*(ushort *)(*(longlong *)(param_1 + 0x418) + 0x10),
                    (uint)*(ushort *)(*(longlong *)(param_1 + 0x418) + 0x12));
    }
    uVar12 = *(byte *)(*(longlong *)(param_1 + 0x418) + 0x1b) & 0xf;
    if (uVar12 < 8) {
      iVar4 = *(int *)(*(longlong *)(param_1 + 0x418) + 0xc);
      bVar6 = FUN_14001c1e0(iVar4);
      if (!bVar6) {
        bVar6 = FUN_14001c1d0(iVar4);
        if (!bVar6) {
          lVar8 = FUN_14001c210();
          plVar11 = (longlong *)
                    (**(code **)(**(longlong **)(lVar8 + 8) + 0x30))
                              (*(longlong **)(lVar8 + 8),iVar4);
          if (plVar11 != (longlong *)0x0) {
            cVar7 = (**(code **)(plVar11[2] + 0x50))(plVar11 + 2);
            if (cVar7 != '\0') {
              FUN_140066300(plVar11,uVar12,0);
            }
            break;
          }
        }
        lVar8 = FUN_14001c7a0();
        plVar11 = (longlong *)FUN_140027a40(lVar8,iVar4);
        if ((plVar11 != (longlong *)0x0) &&
           (cVar7 = (**(code **)(*plVar11 + 0x50))(plVar11), cVar7 != '\0')) {
          uVar1 = *(ushort *)(*(longlong *)(param_1 + 0x418) + 0x10);
          uVar2 = *(ushort *)(*(longlong *)(param_1 + 0x418) + 0x12);
          (**(code **)(*plVar11 + 0x100))
                    (plVar11,uVar1,uVar2,
                     (uint)uVar1 + *(int *)(&DAT_1400cae08 + (longlong)(int)uVar12 * 4),
                     (uint)uVar2 + *(int *)(&DAT_1400cae28 + (longlong)(int)uVar12 * 4));
          (**(code **)(*plVar11 + 200))(plVar11,lVar9);
        }
      }
    }
    break;
  case 0x35:
    uVar5 = *(undefined4 *)(lVar8 + 8);
    lVar9 = FUN_14001c210();
    plVar11 = (longlong *)
              (**(code **)(**(longlong **)(lVar9 + 8) + 0x30))(*(longlong **)(lVar9 + 8),uVar5);
    if (plVar11 != (longlong *)0x0) {
      FUN_140066560(plVar11,(uint)*(ushort *)(*(longlong *)(param_1 + 0x418) + 0x10),
                    (uint)*(ushort *)(*(longlong *)(param_1 + 0x418) + 0x12),0);
    }
    break;
  default:
    goto switchD_1400648ac_default;
  }
switchD_1400648ac_default:
  return;
}


