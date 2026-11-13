// NpcServer.exe :: CMsgMonsterJump  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMsgMonsterJump::vf_0x8 @ 140061690  ulonglong vf_0x8(longlong param_1, void * param_2, uint param_3)

ulonglong CMsgMonsterJump::vf_0x8(longlong param_1,void *param_2,uint param_3)

{
  ulonglong uVar1;
  
  uVar1 = CNetMsg::vf_0x8(param_1,param_2,param_3);
  if ((int)uVar1 == 0) {
    return uVar1;
  }
  return (ulonglong)(*(int *)(param_1 + 8) == 0x4e22);
}


// ==== CMsgMonsterJump::vf_0x18 @ 140061740  undefined vf_0x18(longlong param_1)

void CMsgMonsterJump::vf_0x18(longlong param_1)

{
  undefined4 *puVar1;
  longlong lVar2;
  longlong *plVar3;
  
  puVar1 = *(undefined4 **)(param_1 + 0x418);
  if (puVar1 != (undefined4 *)0x0) {
    lVar2 = FUN_14001c7a0();
    plVar3 = (longlong *)FUN_140027a40(lVar2,*puVar1);
    if (plVar3 != (longlong *)0x0) {
      lVar2 = *(longlong *)(param_1 + 0x418);
      (**(code **)(*plVar3 + 0x118))
                (plVar3,*(undefined2 *)(lVar2 + 4),*(undefined2 *)(lVar2 + 6),
                 *(undefined2 *)(lVar2 + 8));
    }
  }
  return;
}


// ==== CMsgMonsterJump::vf_0x0 @ 1400617a0  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMsgMonsterJump::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  FUN_140034810(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


