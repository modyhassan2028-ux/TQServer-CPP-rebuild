// NpcServer.exe :: CMsgUserAttrib  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMsgUserAttrib::vf_0x8 @ 140061ae0  ulonglong vf_0x8(longlong param_1, void * param_2, uint param_3)

ulonglong CMsgUserAttrib::vf_0x8(longlong param_1,void *param_2,uint param_3)

{
  ulonglong uVar1;
  
  uVar1 = CNetMsg::vf_0x8(param_1,param_2,param_3);
  if ((int)uVar1 == 0) {
    return uVar1;
  }
  return (ulonglong)(*(int *)(param_1 + 8) == 0x2721);
}


// ==== CMsgUserAttrib::vf_0x0 @ 140061b10  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMsgUserAttrib::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  FUN_140034810(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CMsgUserAttrib::vf_0x18 @ 140061e00  undefined vf_0x18(longlong param_1)

void CMsgUserAttrib::vf_0x18(longlong param_1)

{
  code *pcVar1;
  uint uVar2;
  longlong lVar3;
  longlong *plVar4;
  uint uVar5;
  longlong lVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  int iVar9;
  ulonglong uVar11;
  uint local_28 [8];
  ulonglong uVar10;
  
  lVar6 = *(longlong *)(param_1 + 0x418);
  lVar3 = FUN_14001c210();
  plVar4 = (longlong *)FUN_140038010(lVar3,*(int *)(lVar6 + 4));
  if (plVar4 != (longlong *)0x0) {
    lVar6 = *(longlong *)(param_1 + 0x418);
    uVar11 = 0;
    uVar7 = uVar11;
    uVar8 = uVar11;
    if (0 < *(int *)(lVar6 + 8)) {
      do {
        iVar9 = *(int *)(uVar7 + 0xc + lVar6);
        if (iVar9 == 0) {
          (**(code **)(*plVar4 + 0x98))(plVar4,*(undefined4 *)(uVar7 + 0x10 + lVar6));
        }
        else if (iVar9 == 2) {
          (**(code **)(*plVar4 + 0xa0))(plVar4,*(undefined4 *)(uVar7 + 0x10 + lVar6));
        }
        else if (iVar9 == 0x19) {
          lVar3 = 5;
          do {
            local_28[lVar3] = 0;
            lVar3 = lVar3 + -1;
          } while (-1 < lVar3);
          lVar6 = uVar7 + 0x10 + lVar6;
          lVar3 = 5;
          do {
            local_28[lVar3] = 0;
            lVar3 = lVar3 + -1;
          } while (-1 < lVar3);
          uVar10 = uVar11;
          if (lVar6 != 0) {
            do {
              iVar9 = (int)uVar10;
              uVar5 = iVar9 >> 0x1f & 0x1f;
              uVar2 = iVar9 + uVar5;
              if ((*(uint *)(lVar6 + (longlong)((int)uVar2 >> 5) * 4) >>
                   ((uVar2 & 0x1f) - uVar5 & 0x1f) & 1) != 0) {
                if (0xbf < (ulonglong)(longlong)iVar9) {
                  FUN_1400496c0();
                  pcVar1 = (code *)swi(3);
                  (*pcVar1)();
                  return;
                }
                local_28[(ulonglong)(longlong)iVar9 >> 5] =
                     local_28[(ulonglong)(longlong)iVar9 >> 5] | 1 << ((byte)uVar10 & 0x1f);
              }
              uVar10 = (ulonglong)(iVar9 + 1U);
            } while ((int)(iVar9 + 1U) < 0xc0);
          }
          (**(code **)(*plVar4 + 0x90))(plVar4,local_28);
        }
        lVar6 = *(longlong *)(param_1 + 0x418);
        uVar2 = (int)uVar8 + 1;
        uVar7 = uVar7 + 0x1c;
        uVar8 = (ulonglong)uVar2;
      } while ((int)uVar2 < *(int *)(lVar6 + 8));
    }
  }
  return;
}


