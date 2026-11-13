// NpcServer.exe :: CMsgAction  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMsgAction::vf_0x8 @ 140062620  ulonglong vf_0x8(longlong param_1, void * param_2, uint param_3)

ulonglong CMsgAction::vf_0x8(longlong param_1,void *param_2,uint param_3)

{
  ulonglong uVar1;
  
  uVar1 = CNetMsg::vf_0x8(param_1,param_2,param_3);
  if ((int)uVar1 == 0) {
    return uVar1;
  }
  return (ulonglong)(*(int *)(param_1 + 8) == 0x271a);
}


// ==== CMsgAction::vf_0x0 @ 140062650  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMsgAction::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  FUN_140034810(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CMsgAction::vf_0x18 @ 1400626a0  undefined vf_0x18(longlong param_1)

void CMsgAction::vf_0x18(longlong param_1)

{
  ushort uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  bool bVar7;
  int iVar8;
  longlong *plVar9;
  undefined8 uVar10;
  longlong lVar11;
  longlong lVar12;
  longlong *plVar13;
  
  lVar12 = *(longlong *)(param_1 + 0x418);
  uVar1 = *(ushort *)(lVar12 + 0x14);
  if (0x195 < uVar1) {
    if (uVar1 != 0x197) {
      return;
    }
    uVar6 = *(undefined4 *)(param_1 + 0x410);
    lVar12 = FUN_14001c7a0();
    plVar13 = (longlong *)FUN_140027a40(lVar12,uVar6);
    if (plVar13 == (longlong *)0x0) {
      return;
    }
    lVar12 = (**(code **)(*plVar13 + 0xb0))(plVar13,0x1040,0);
    if (lVar12 == 0) {
      return;
    }
    lVar12 = (**(code **)(*plVar13 + 0xb0))(plVar13,0x1040,0);
    FUN_14005a370(lVar12,*(undefined4 *)(*(longlong *)(param_1 + 0x418) + 8));
    return;
  }
  if (uVar1 == 0x195) {
    uVar6 = *(undefined4 *)(param_1 + 0x410);
    lVar12 = FUN_14001c7a0();
    plVar13 = (longlong *)FUN_140027a40(lVar12,uVar6);
    if (plVar13 == (longlong *)0x0) {
      return;
    }
    if (*(longlong *)(*(longlong *)(param_1 + 0x418) + 8) == 0) {
                    /* WARNING: Could not recover jumptable at 0x000140062e19. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*plVar13 + 0x110))(plVar13,1);
      return;
    }
                    /* WARNING: Could not recover jumptable at 0x000140062e32. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar13 + 0x110))(plVar13,0);
    return;
  }
  switch(uVar1) {
  case 0x4f:
    uVar6 = *(undefined4 *)(lVar12 + 4);
    lVar12 = FUN_14001c210();
    lVar12 = (**(code **)(**(longlong **)(lVar12 + 8) + 0x30))(*(longlong **)(lVar12 + 8),uVar6);
    if (lVar12 != 0) {
      *(undefined1 *)(lVar12 + 0x92) = *(undefined1 *)(*(longlong *)(param_1 + 0x418) + 0x16);
    }
    break;
  case 0x50:
  case 0x52:
  case 0x57:
  case 0x58:
  case 0x5b:
  case 0x5c:
  case 0x5d:
  case 0x5e:
  case 0x5f:
  case 0x60:
  case 0x61:
  case 0x62:
  case 99:
  case 100:
  case 0x65:
  case 0x66:
  case 0x67:
  case 0x68:
  case 0x6a:
  case 0x6d:
  case 0x6e:
  case 0x6f:
  case 0x70:
  case 0x71:
  case 0x72:
  case 0x73:
  case 0x74:
  case 0x75:
  case 0x76:
  case 0x77:
  case 0x78:
  case 0x79:
  case 0x7a:
  case 0x7b:
  case 0x7c:
  case 0x7d:
  case 0x7e:
  case 0x7f:
  case 0x80:
  case 0x81:
  case 0x82:
  case 0x83:
  case 0x84:
  case 0x85:
  case 0x86:
  case 0x88:
  case 0x8a:
  case 0x8b:
  case 0x8c:
  case 0x8d:
  case 0x8e:
  case 0x8f:
  case 0x90:
  case 0x91:
  case 0x93:
  case 0x94:
  case 0x95:
  case 0x96:
  case 0x97:
  case 0x98:
  case 0x99:
  case 0x9a:
  case 0x9b:
  case 0x9d:
  case 0x9e:
  case 0x9f:
  case 0xa0:
  case 0xa1:
  case 0xa2:
  case 0xa3:
  case 0xa4:
  case 0xa5:
  case 0xa6:
  case 0xa7:
  case 0xa8:
  case 0xa9:
  case 0xaa:
  case 0xab:
  case 0xac:
  case 0xad:
  case 0xae:
  case 0xaf:
  case 0xb0:
  case 0xb1:
  case 0xb2:
  case 0xb3:
  case 0xb4:
  case 0xb5:
  case 0xb6:
  case 0xb7:
  case 0xb8:
  case 0xb9:
  case 0xba:
  case 0xbb:
  case 0xbc:
  case 0xbd:
  case 0xbe:
  case 0xbf:
  case 0xc0:
  case 0xc1:
  case 0xc2:
  case 0xc3:
  case 0xc4:
  case 0xc5:
  case 0xc6:
  case 199:
  case 200:
  case 0xc9:
    break;
  case 0x51:
    uVar6 = *(undefined4 *)(lVar12 + 4);
    lVar12 = FUN_14001c210();
    lVar12 = (**(code **)(**(longlong **)(lVar12 + 8) + 0x30))(*(longlong **)(lVar12 + 8),uVar6);
    if (lVar12 != 0) {
      *(undefined4 *)(lVar12 + 0x94) = *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 8);
    }
    break;
  case 0x53:
    log_InlineLogERROR(&DAT_1400be0b0);
    break;
  case 0x54:
    log_InlineLogERROR(&DAT_1400be0b0);
    break;
  case 0x55:
    log_InlineLogERROR(&DAT_1400be0b0);
    break;
  case 0x56:
    uVar6 = *(undefined4 *)(lVar12 + 4);
    lVar12 = FUN_14001c210();
    plVar13 = (longlong *)
              (**(code **)(**(longlong **)(lVar12 + 8) + 0x30))(*(longlong **)(lVar12 + 8),uVar6);
    if (plVar13 != (longlong *)0x0) {
      lVar12 = *(longlong *)(param_1 + 0x418);
      FUN_140066100(plVar13,*(int *)(lVar12 + 8),(uint)*(ushort *)(lVar12 + 0x18),
                    (uint)*(ushort *)(lVar12 + 0x1a));
    }
    break;
  case 0x59:
    bVar7 = FUN_14001c1e0(*(int *)(lVar12 + 4));
    if (!bVar7) {
      lVar12 = *(longlong *)(param_1 + 0x418);
      lVar11 = FUN_14001c7a0();
      plVar13 = (longlong *)FUN_140027a40(lVar11,*(undefined4 *)(lVar12 + 4));
      if (plVar13 == (longlong *)0x0) goto LAB_140062d71;
      (**(code **)(*plVar13 + 0xf8))(plVar13);
    }
    break;
  case 0x5a:
    log_InlineLogERROR(&DAT_1400be0b0);
    break;
  case 0x69:
    uVar6 = *(undefined4 *)(lVar12 + 8);
    iVar8 = *(int *)(lVar12 + 4);
    lVar12 = FUN_14001c790();
    lVar12 = FUN_14003ca10(lVar12,iVar8);
    if (lVar12 == 0) {
LAB_140062d71:
      log_InlineLogERROR(&DAT_1400be0b0);
    }
    else {
      *(undefined4 *)(lVar12 + 0x50) = uVar6;
    }
    break;
  case 0x6b:
    uVar6 = *(undefined4 *)(param_1 + 0x410);
    lVar12 = FUN_14001c7a0();
    plVar13 = (longlong *)FUN_140027a40(lVar12,uVar6);
    if ((plVar13 != (longlong *)0x0) &&
       (lVar12 = (**(code **)(*plVar13 + 0xb0))(plVar13,0x1040,0), lVar12 != 0)) {
      lVar12 = (**(code **)(*plVar13 + 0xb0))(plVar13,0x1040,0);
      FUN_14005aeb0(lVar12,*(int *)(*(longlong *)(param_1 + 0x418) + 8));
    }
    break;
  case 0x6c:
    lVar11 = FUN_14001c7a0();
    plVar13 = (longlong *)FUN_140027a40(lVar11,*(undefined4 *)(lVar12 + 4));
    if (plVar13 != (longlong *)0x0) {
      plVar9 = (longlong *)(**(code **)(*plVar13 + 0x80))(plVar13);
      if (plVar9 == (longlong *)0x0) {
LAB_140062b79:
        log_InlineLogERROR("NPC idUser=%u has no map at %s, %d");
      }
      else {
        uVar10 = FUN_14004ab40((longlong)plVar9,
                               (uint)*(ushort *)(*(longlong *)(param_1 + 0x418) + 0x18),
                               (uint)*(ushort *)(*(longlong *)(param_1 + 0x418) + 0x1a));
        if ((char)uVar10 == '\0') {
          (**(code **)(*plVar9 + 8))(plVar9);
LAB_140062bdc:
          log_InlineLogERROR("NPC idUser=%u MapID=%d (%u, %u) invalid point at %s, %d");
        }
        else {
          (**(code **)(*plVar13 + 0xd8))
                    (plVar13,*(undefined2 *)(*(longlong *)(param_1 + 0x418) + 0x18),
                     *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 0x1a));
        }
      }
    }
    break;
  case 0x87:
    bVar7 = FUN_14001c1e0(*(int *)(lVar12 + 4));
    if (!bVar7) {
      bVar7 = FUN_14001c1d0(*(int *)(*(longlong *)(param_1 + 0x418) + 4));
      if (bVar7) {
        lVar12 = FUN_14001c7a0();
        plVar13 = (longlong *)FUN_140025c40(lVar12);
        (**(code **)(*plVar13 + 0x30))(plVar13,*(undefined4 *)(*(longlong *)(param_1 + 0x418) + 4));
      }
      else {
        plVar13 = (longlong *)FUN_14001c210();
        plVar13 = (longlong *)(**(code **)(*plVar13 + 0x10))(plVar13);
        (**(code **)(*plVar13 + 0x28))(plVar13,*(undefined4 *)(*(longlong *)(param_1 + 0x418) + 4));
      }
    }
    break;
  case 0x89:
    uVar6 = *(undefined4 *)(lVar12 + 4);
    lVar12 = FUN_14001c210();
    plVar13 = (longlong *)
              (**(code **)(**(longlong **)(lVar12 + 8) + 0x30))(*(longlong **)(lVar12 + 8),uVar6);
    if (plVar13 != (longlong *)0x0) {
      lVar12 = *(longlong *)(param_1 + 0x418);
      FUN_140066560(plVar13,(uint)*(ushort *)(lVar12 + 8),(uint)*(ushort *)(lVar12 + 10),
                    (char)*(undefined2 *)(lVar12 + 0x16));
    }
    break;
  case 0x92:
    uVar6 = *(undefined4 *)(lVar12 + 4);
    lVar12 = FUN_14001c210();
    plVar13 = (longlong *)
              (**(code **)(**(longlong **)(lVar12 + 8) + 0x30))(*(longlong **)(lVar12 + 8),uVar6);
    if (plVar13 == (longlong *)0x0) {
      iVar8 = *(int *)(*(longlong *)(param_1 + 0x418) + 4);
      if (*(int *)(param_1 + 0x410) == iVar8) {
        lVar12 = FUN_14001c7a0();
        plVar13 = (longlong *)FUN_140027a40(lVar12,iVar8);
        if (plVar13 != (longlong *)0x0) {
          plVar9 = (longlong *)(**(code **)(*plVar13 + 0x80))(plVar13);
          if (plVar9 == (longlong *)0x0) goto LAB_140062b79;
          uVar10 = FUN_14004ab40((longlong)plVar9,
                                 (uint)*(ushort *)(*(longlong *)(param_1 + 0x418) + 8),
                                 (uint)*(ushort *)(*(longlong *)(param_1 + 0x418) + 10));
          if ((char)uVar10 == '\0') {
            (**(code **)(*plVar9 + 8))(plVar9);
            goto LAB_140062bdc;
          }
          uVar2 = *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 8);
          uVar3 = *(undefined2 *)(*(longlong *)(param_1 + 0x418) + 10);
          (**(code **)(*plVar13 + 0x100))(plVar13,uVar2,uVar3,uVar2,uVar3);
        }
      }
    }
    else {
      iVar8 = (**(code **)(plVar13[2] + 0x30))(plVar13 + 2);
      if (iVar8 == *(int *)(*(longlong *)(param_1 + 0x418) + 0x1c)) {
        plVar9 = (longlong *)(**(code **)(plVar13[2] + 0x80))(plVar13 + 2);
        if (plVar9 == (longlong *)0x0) {
          (**(code **)(*plVar13 + 8))(plVar13);
          log_InlineLogERROR("UserID=%u has no map at %s, %d");
        }
        else {
          uVar10 = FUN_14004ab40((longlong)plVar9,
                                 (uint)*(ushort *)(*(longlong *)(param_1 + 0x418) + 8),
                                 (uint)*(ushort *)(*(longlong *)(param_1 + 0x418) + 10));
          if ((char)uVar10 == '\0') {
            (**(code **)(*plVar9 + 8))(plVar9);
            (**(code **)(*plVar13 + 8))(plVar13);
            log_InlineLogERROR("UserID=%u MapID=%d (%u, %u) invalid point at %s, %d");
          }
          else {
            FUN_140065eb0(plVar13,(uint)*(ushort *)(*(longlong *)(param_1 + 0x418) + 8),
                          (uint)*(ushort *)(*(longlong *)(param_1 + 0x418) + 10));
          }
        }
      }
    }
    break;
  case 0x9c:
    uVar6 = *(undefined4 *)(lVar12 + 4);
    lVar12 = FUN_14001c210();
    plVar13 = (longlong *)
              (**(code **)(**(longlong **)(lVar12 + 8) + 0x30))(*(longlong **)(lVar12 + 8),uVar6);
    if (plVar13 != (longlong *)0x0) {
      lVar12 = *(longlong *)(param_1 + 0x418);
      FUN_140066560(plVar13,(uint)*(ushort *)(lVar12 + 0x18),(uint)*(ushort *)(lVar12 + 0x1a),
                    (char)*(undefined2 *)(lVar12 + 0x16));
    }
    break;
  case 0xca:
    uVar4 = *(uint *)(lVar12 + 8);
    iVar8 = *(int *)(lVar12 + 4);
    lVar12 = FUN_14001c790();
    plVar13 = (longlong *)FUN_14003ca10(lVar12,iVar8);
    if (plVar13 == (longlong *)0x0) goto LAB_140062d71;
    FUN_140056060(plVar13,uVar4);
    break;
  case 0xcb:
    uVar6 = *(undefined4 *)(lVar12 + 8);
    iVar8 = *(int *)(param_1 + 0x410);
    iVar5 = *(int *)(lVar12 + 4);
    lVar12 = FUN_14001c790();
    lVar12 = FUN_14003ca10(lVar12,iVar5);
    if (lVar12 == 0) goto LAB_140062d71;
    FUN_140049390(lVar12,uVar6,(uint)*(ushort *)(*(longlong *)(param_1 + 0x418) + 0x18),
                  (uint)*(ushort *)(*(longlong *)(param_1 + 0x418) + 0x1a),iVar8);
    break;
  case 0xcc:
    iVar8 = *(int *)(lVar12 + 4);
    lVar12 = FUN_14001c790();
    lVar12 = FUN_14003ca10(lVar12,iVar8);
    if (lVar12 == 0) goto LAB_140062d71;
    FUN_140049420(lVar12);
    break;
  default:
    goto switchD_1400626fb_default;
  }
switchD_1400626fb_default:
  return;
}


