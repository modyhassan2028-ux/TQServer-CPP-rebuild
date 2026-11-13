// NpcServer.exe :: CMsgMapInfo  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMsgMapInfo::vf_0x8 @ 140063920  ulonglong vf_0x8(longlong param_1, void * param_2, uint param_3)

ulonglong CMsgMapInfo::vf_0x8(longlong param_1,void *param_2,uint param_3)

{
  ulonglong uVar1;
  
  uVar1 = CNetMsg::vf_0x8(param_1,param_2,param_3);
  if ((int)uVar1 == 0) {
    return uVar1;
  }
  return (ulonglong)(*(int *)(param_1 + 8) == 0x456);
}


// ==== CMsgMapInfo::vf_0x0 @ 140063950  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMsgMapInfo::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  FUN_140034810(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CMsgMapInfo::vf_0x18 @ 1400639a0  undefined vf_0x18(longlong param_1)

void CMsgMapInfo::vf_0x18(longlong param_1)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  
  piVar2 = *(int **)(param_1 + 0x418);
  lVar4 = FUN_14001c790();
  plVar5 = (longlong *)FUN_14003ca10(lVar4,*piVar2);
  if (plVar5 != (longlong *)0x0) {
    plVar6 = (longlong *)(**(code **)(**(longlong **)plVar5[9] + 0x10))(*(longlong **)plVar5[9],3);
    uVar3 = (**(code **)(*plVar6 + 0x48))(plVar6);
    uVar1 = *(uint *)(*(longlong *)(param_1 + 0x418) + 4);
    if (uVar3 != uVar1) {
      FUN_140056060(plVar5,uVar1);
    }
  }
  return;
}


