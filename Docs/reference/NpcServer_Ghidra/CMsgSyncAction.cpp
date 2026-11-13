// NpcServer.exe :: CMsgSyncAction  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMsgSyncAction::vf_0x8 @ 1400636b0  ulonglong vf_0x8(longlong param_1, void * param_2, uint param_3)

ulonglong CMsgSyncAction::vf_0x8(longlong param_1,void *param_2,uint param_3)

{
  ulonglong uVar1;
  
  uVar1 = CNetMsg::vf_0x8(param_1,param_2,param_3);
  if ((int)uVar1 == 0) {
    return uVar1;
  }
  return (ulonglong)(*(int *)(param_1 + 8) == 0x45a);
}


// ==== CMsgSyncAction::vf_0x18 @ 1400636e0  undefined vf_0x18(longlong param_1)

void CMsgSyncAction::vf_0x18(longlong param_1)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  bool bVar5;
  char *pcVar6;
  longlong lVar7;
  longlong *plVar8;
  longlong lVar9;
  int iVar10;
  
  pcVar6 = *(char **)(param_1 + 0x418);
  cVar1 = *pcVar6;
  if (((cVar1 == '\0') || (cVar1 == '\x01')) || (cVar1 == '\x02')) {
    if (*(int *)(pcVar6 + 8) < 2) {
      log_InlineLogERROR(&DAT_1400be0b0);
      return;
    }
    iVar10 = 0;
    if (0 < *(int *)(pcVar6 + 8)) {
      lVar9 = 0xc;
      do {
        iVar3 = *(int *)(pcVar6 + lVar9);
        if (iVar3 != 0) {
          bVar5 = FUN_14001c1e0(iVar3);
          if (bVar5) {
            log_InlineLogERROR(&DAT_1400be0b0);
          }
          else {
            bVar5 = FUN_14001c1d0(iVar3);
            if (!bVar5) {
              lVar7 = FUN_14001c210();
              plVar8 = (longlong *)
                       (**(code **)(**(longlong **)(lVar7 + 8) + 0x30))
                                 (*(longlong **)(lVar7 + 8),iVar3);
              if (plVar8 != (longlong *)0x0) {
                pbVar4 = *(byte **)(param_1 + 0x418);
                bVar2 = *pbVar4;
                if (bVar2 < 2) {
                  FUN_140066300(plVar8,(uint)pbVar4[2],(uint)pbVar4[3]);
                }
                else if (bVar2 == 2) {
                  FUN_140066560(plVar8,(uint)*(ushort *)(pbVar4 + 2),(uint)*(ushort *)(pbVar4 + 4),0
                               );
                }
                else if ((byte)(bVar2 - 3) < 4) {
                  FUN_140066560(plVar8,(uint)*(ushort *)(pbVar4 + 2),(uint)*(ushort *)(pbVar4 + 4),0
                               );
                }
              }
            }
          }
        }
        pcVar6 = *(char **)(param_1 + 0x418);
        iVar10 = iVar10 + 1;
        lVar9 = lVar9 + 4;
      } while (iVar10 < *(int *)(pcVar6 + 8));
    }
  }
  return;
}


// ==== CMsgSyncAction::vf_0x0 @ 140063850  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMsgSyncAction::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  FUN_140034810(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


