// NpcServer.exe :: CEmptyNpcGen  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CEmptyNpcGen::vf_0x28 @ 140069eb0  int * vf_0x28(longlong * param_1, int * param_2)

int * CEmptyNpcGen::vf_0x28(longlong *param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_1 + 0x60))();
  *param_2 = iVar1 / 2 + *(int *)((longlong)param_1 + 0x24);
  iVar1 = (**(code **)(*param_1 + 0x38))(param_1);
  param_2[1] = iVar1 / 2 + (int)param_1[5];
  return param_2;
}


// ==== CEmptyNpcGen::vf_0x38 @ 140069f00  undefined4 vf_0x38(longlong param_1)

undefined4 CEmptyNpcGen::vf_0x38(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x10);
}


// ==== CEmptyNpcGen::vf_0x50 @ 140069f10  undefined4 vf_0x50(longlong param_1)

undefined4 CEmptyNpcGen::vf_0x50(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x24);
}


// ==== CEmptyNpcGen::vf_0x58 @ 140069f20  undefined4 vf_0x58(longlong param_1)

undefined4 CEmptyNpcGen::vf_0x58(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x28);
}


// ==== CEmptyNpcGen::vf_0x60 @ 140069f30  undefined4 vf_0x60(longlong param_1)

undefined4 CEmptyNpcGen::vf_0x60(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x18);
}


// ==== CEmptyNpcGen::vf_0x68 @ 140069f40  undefined8 vf_0x68(longlong * param_1, int param_2, int param_3)

ulonglong CEmptyNpcGen::vf_0x68(longlong *param_1,int param_2,int param_3)

{
  int iVar1;
  ulonglong uVar2;
  
  uVar2 = (**(code **)(*param_1 + 0x50))();
  if ((int)uVar2 <= param_2) {
    iVar1 = (**(code **)(*param_1 + 0x60))(param_1);
    uVar2 = (**(code **)(*param_1 + 0x50))(param_1);
    if ((param_2 < iVar1 + (int)uVar2) &&
       (uVar2 = (**(code **)(*param_1 + 0x58))(param_1), (int)uVar2 <= param_3)) {
      iVar1 = (**(code **)(*param_1 + 0x58))(param_1);
      uVar2 = (**(code **)(*param_1 + 0x38))(param_1);
      if (param_3 < iVar1 + (int)uVar2) {
        return CONCAT71((int7)(uVar2 >> 8),1);
      }
    }
  }
  return uVar2 & 0xffffffffffffff00;
}


// ==== CEmptyNpcGen::vf_0x70 @ 140069fd0  undefined8 vf_0x70(longlong * param_1, int param_2, int param_3, int param_4, int param_5)

undefined8 CEmptyNpcGen::vf_0x70(longlong *param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  ulonglong in_RAX;
  
  if ((int)param_1[4] == param_2) {
    iVar1 = (**(code **)(*param_1 + 0x50))();
    in_RAX = (ulonglong)(uint)(iVar1 - param_5);
    if (iVar1 - param_5 <= param_3) {
      iVar1 = (**(code **)(*param_1 + 0x58))(param_1);
      in_RAX = (ulonglong)(uint)(iVar1 - param_5);
      if (iVar1 - param_5 <= param_4) {
        iVar1 = (**(code **)(*param_1 + 0x60))(param_1);
        iVar2 = (**(code **)(*param_1 + 0x50))(param_1);
        uVar3 = iVar2 + param_5 + iVar1;
        in_RAX = (ulonglong)uVar3;
        if (param_3 < (int)uVar3) {
          iVar1 = (**(code **)(*param_1 + 0x58))(param_1);
          iVar2 = (**(code **)(*param_1 + 0x38))(param_1);
          uVar3 = iVar2 + param_5 + iVar1;
          in_RAX = (ulonglong)uVar3;
          if (param_4 < (int)uVar3) {
            return (ulonglong)(uint3)(uVar3 >> 8) << 8;
          }
        }
      }
    }
  }
  return CONCAT71((int7)(in_RAX >> 8),1);
}


// ==== CEmptyNpcGen::vf_0x98 @ 14006a080  undefined vf_0x98(longlong * param_1)

void CEmptyNpcGen::vf_0x98(longlong *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00014006a083. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0xa0))();
  return;
}


// ==== CEmptyNpcGen::vf_0x80 @ 14006a090  undefined8 vf_0x80(void)

undefined8 CEmptyNpcGen::vf_0x80(void)

{
  return 0;
}


// ==== CEmptyNpcGen::vf_0xa0 @ 14006a0a0  undefined8 vf_0xa0(undefined8 * param_1)

undefined8 CEmptyNpcGen::vf_0xa0(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    (**(code **)*param_1)(param_1,1);
  }
  return 0;
}


// ==== CEmptyNpcGen::vf_0x8 @ 14006a0c0  undefined4 vf_0x8(longlong param_1)

undefined4 CEmptyNpcGen::vf_0x8(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x1c);
}


// ==== CEmptyNpcGen::vf_0x48 @ 14006a0d0  undefined4 vf_0x48(longlong param_1)

undefined4 CEmptyNpcGen::vf_0x48(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x14);
}


// ==== CEmptyNpcGen::vf_0x40 @ 14006a0e0  undefined4 vf_0x40(longlong param_1)

undefined4 CEmptyNpcGen::vf_0x40(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x20);
}


// ==== CEmptyNpcGen::vf_0x88 @ 14006a0f0  undefined1 vf_0x88(void)

undefined1 CEmptyNpcGen::vf_0x88(void)

{
  return 0;
}


// ==== CEmptyNpcGen::vf_0x20 @ 14006a140  longlong vf_0x20(longlong param_1)

longlong CEmptyNpcGen::vf_0x20(longlong param_1)

{
  return *(longlong *)(param_1 + 0x50) - *(longlong *)(param_1 + 0x48) >> 2;
}


// ==== CEmptyNpcGen::vf_0x30 @ 14006a150  longlong vf_0x30(longlong param_1)

longlong CEmptyNpcGen::vf_0x30(longlong param_1)

{
  return *(longlong *)(param_1 + 0x50) - *(longlong *)(param_1 + 0x48) >> 2;
}


// ==== CEmptyNpcGen::vf_0x0 @ 14006a3c0  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CEmptyNpcGen::vf_0x0(undefined8 *param_1,uint param_2)

{
  FUN_14006a220(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CEmptyNpcGen::vf_0x78 @ 14006a680  undefined vf_0x78(longlong * param_1, int param_2)

void CEmptyNpcGen::vf_0x78(longlong *param_1,int param_2)

{
  longlong *plVar1;
  int *piVar2;
  longlong lVar3;
  rsize_t _DstSize;
  int *_Dst;
  
  _Dst = (int *)param_1[9];
  if ((int *)param_1[10] < _Dst) {
    _invalid_parameter_noinfo();
  }
  plVar1 = (longlong *)param_1[6];
  while( true ) {
    piVar2 = (int *)param_1[10];
    if (piVar2 < (int *)param_1[9]) {
      _invalid_parameter_noinfo();
    }
    if ((plVar1 == (longlong *)0x0) || (plVar1 != (longlong *)param_1[6])) {
      _invalid_parameter_noinfo();
    }
    if (_Dst == piVar2) {
      (**(code **)(*param_1 + 8))(param_1);
      tq::MyLogSave(PTR_s_gmlog_emptynpc_generator_140103460,
                    "ERROR: Can not find NPC: %u in empty generator id: %d");
      return;
    }
    if (plVar1 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar3 = 0;
    }
    else {
      lVar3 = *plVar1;
    }
    if (*(int **)(lVar3 + 0x20) <= _Dst) {
      _invalid_parameter_noinfo();
    }
    if (*_Dst == param_2) break;
    if (plVar1 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar3 = 0;
    }
    else {
      lVar3 = *plVar1;
    }
    if (*(int **)(lVar3 + 0x20) <= _Dst) {
      _invalid_parameter_noinfo();
    }
    _Dst = _Dst + 1;
  }
  lVar3 = param_1[10] - (longlong)(_Dst + 1) >> 2;
  if (0 < lVar3) {
    _DstSize = lVar3 << 2;
    memmove_s(_Dst,_DstSize,_Dst + 1,_DstSize);
  }
  param_1[10] = param_1[10] + -4;
  if ((_Dst < (int *)param_1[9]) || ((int *)param_1[10] < _Dst)) {
    _invalid_parameter_noinfo();
  }
  return;
}


// ==== CEmptyNpcGen::vf_0x90 @ 14006a7d0  undefined vf_0x90(longlong * param_1, undefined4 param_2)

void CEmptyNpcGen::vf_0x90(longlong *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 local_res10 [6];
  
  local_res10[0] = param_2;
  FUN_14002f3b0(param_1 + 6,local_res10);
  iVar1 = (**(code **)(*param_1 + 0x48))(param_1);
  iVar2 = (**(code **)(*param_1 + 0x20))(param_1);
  if (iVar1 < iVar2) {
    (**(code **)(*param_1 + 0x20))(param_1);
    (**(code **)(*param_1 + 8))(param_1);
    tq::MyLogSave(PTR_s_gmlog_emptynpc_generator_140103460,
                  "WARNING: empty generator id: %d, had been overflow, current amount: %d");
  }
  return;
}


