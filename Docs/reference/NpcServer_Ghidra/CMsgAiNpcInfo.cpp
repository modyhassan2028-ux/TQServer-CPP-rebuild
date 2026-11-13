// NpcServer.exe :: CMsgAiNpcInfo  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMsgAiNpcInfo::vf_0x8 @ 140061430  undefined8 vf_0x8(longlong param_1, void * param_2, uint param_3)

undefined8 CMsgAiNpcInfo::vf_0x8(longlong param_1,void *param_2,uint param_3)

{
  if (param_2 == (void *)0x0) {
    return 0;
  }
  memcpy((void *)(param_1 + 0x10),param_2,(ulonglong)param_3);
  return 1;
}


// ==== CMsgAiNpcInfo::vf_0x0 @ 140061490  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMsgAiNpcInfo::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  FUN_140034810(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CMsgAiNpcInfo::vf_0x18 @ 1400614f0  undefined vf_0x18(longlong param_1, longlong param_2)

void CMsgAiNpcInfo::vf_0x18(longlong param_1,longlong param_2)

{
  int *piVar1;
  char cVar2;
  longlong lVar3;
  longlong *plVar4;
  longlong *plVar5;
  
  if (param_2 != 0) {
    piVar1 = *(int **)(param_1 + 0x418);
    lVar3 = FUN_14001c7a0();
    plVar4 = (longlong *)FUN_140025c40(lVar3);
    lVar3 = (**(code **)(*plVar4 + 0x40))(plVar4,*piVar1);
    if ((lVar3 == 0) && (plVar4 = FUN_14005d9c0(), plVar4 != (longlong *)0x0)) {
      cVar2 = FUN_14005e2e0(plVar4,*piVar1,(uint)*(ushort *)((longlong)piVar1 + 0x1a),piVar1[1],
                            (uint)*(ushort *)(piVar1 + 5),(uint)*(ushort *)((longlong)piVar1 + 0x16)
                            ,piVar1[2],piVar1[3],(uint)*(ushort *)(piVar1 + 7),piVar1[4],piVar1[9],
                            piVar1[8],(char)piVar1[0xb],piVar1[10],piVar1[0xc]);
      if (cVar2 == '\0') {
        (**(code **)(plVar4[2] + 0xf0))(plVar4 + 2);
      }
      else {
        lVar3 = FUN_14001c7a0();
        plVar5 = (longlong *)FUN_140025c40(lVar3);
        (**(code **)(*plVar5 + 0x28))(plVar5,plVar4 + 2);
        if (piVar1[0xd] != 0) {
          (**(code **)(plVar4[2] + 0x98))(plVar4 + 2);
        }
      }
    }
  }
  return;
}


