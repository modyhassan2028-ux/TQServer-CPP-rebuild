// NpcServer.exe :: CMsgNpcPath  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMsgNpcPath::vf_0x8 @ 140063d30  undefined8 vf_0x8(longlong param_1, void * param_2, uint param_3)

undefined8 CMsgNpcPath::vf_0x8(longlong param_1,void *param_2,uint param_3)

{
  if (param_2 == (void *)0x0) {
    return 0;
  }
  memcpy((void *)(param_1 + 0x10),param_2,(ulonglong)param_3);
  return 1;
}


// ==== CMsgNpcPath::vf_0x0 @ 140063de0  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMsgNpcPath::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  tq::CStringPacker::~CStringPacker((CStringPacker *)(param_1 + 0x84));
  FUN_140034810(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CMsgNpcPath::vf_0x18 @ 140063e40  undefined vf_0x18(longlong param_1, longlong param_2)

void CMsgNpcPath::vf_0x18(longlong param_1,longlong param_2)

{
  int iVar1;
  int *piVar2;
  longlong lVar3;
  longlong *plVar4;
  longlong local_res10 [3];
  
  if (param_2 != 0) {
    piVar2 = *(int **)(param_1 + 0x418);
    local_res10[0] = 0;
    if (*piVar2 != 2) {
      lVar3 = FUN_14001c7a0();
      plVar4 = (longlong *)FUN_140027a40(lVar3,piVar2[3]);
      if (((plVar4 != (longlong *)0x0) &&
          (local_res10[0] = (**(code **)(*plVar4 + 0xb0))(plVar4,0x1040,local_res10),
          local_res10[0] != 0)) &&
         ((iVar1 = **(int **)(param_1 + 0x418), iVar1 == 4 ||
          (((iVar1 == 5 || (iVar1 == 6)) || (iVar1 == 0xc)))))) {
        FUN_14005df30(local_res10[0]);
      }
    }
  }
  return;
}


