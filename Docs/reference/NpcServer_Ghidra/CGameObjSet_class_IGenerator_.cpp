// NpcServer.exe :: CGameObjSet<class_IGenerator>  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CGameObjSet<class_IGenerator>::vf_0x8 @ 14002bad0  undefined vf_0x8(undefined8 * param_1)

void CGameObjSet<class_IGenerator>::vf_0x8(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    (**(code **)*param_1)(param_1,1);
  }
  return;
}


// ==== CGameObjSet<class_IGenerator>::vf_0x30 @ 14002bb40  longlong * vf_0x30(longlong param_1, int param_2)

longlong * CGameObjSet<class_IGenerator>::vf_0x30(longlong param_1,int param_2)

{
  longlong *plVar1;
  int iVar2;
  ulonglong uVar3;
  
  uVar3 = 0;
  if (*(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3 != 0) {
    do {
      if ((ulonglong)(*(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3) <= uVar3)
      {
        _invalid_parameter_noinfo();
      }
      plVar1 = *(longlong **)(*(longlong *)(param_1 + 0x20) + uVar3 * 8);
      if ((plVar1 != (longlong *)0x0) &&
         (iVar2 = (**(code **)(*plVar1 + 8))(plVar1), iVar2 == param_2)) {
        return plVar1;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < (ulonglong)(*(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3)
            );
  }
  return (longlong *)0x0;
}


// ==== CGameObjSet<class_IGenerator>::vf_0x10 @ 14002be60  longlong vf_0x10(longlong param_1)

longlong CGameObjSet<class_IGenerator>::vf_0x10(longlong param_1)

{
  return *(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3;
}


// ==== CGameObjSet<class_IGenerator>::vf_0x18 @ 14002be70  undefined8 vf_0x18(longlong param_1, ulonglong param_2, longlong param_3)

undefined8
CGameObjSet<class_IGenerator>::vf_0x18(longlong param_1,ulonglong param_2,longlong param_3)

{
  if (param_2 < (ulonglong)(*(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3)) {
    if ((ulonglong)(*(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3) <= param_2)
    {
      _invalid_parameter_noinfo();
    }
    return *(undefined8 *)(*(longlong *)(param_1 + 0x20) + param_2 * 8);
  }
  if (param_3 != 0) {
    log_InlineLogWARNING("CGameObjSet GetObjByIndex index oversize idx=%d, size=%u, in %s, %d");
    return 0;
  }
  log_InlineLogWARNING("CGameObjSet GetObjByIndex index oversize idx=%d, size=%u, in line %d");
  return 0;
}


// ==== CGameObjSet<class_IGenerator>::vf_0x28 @ 14002e990  undefined8 vf_0x28(longlong param_1, int param_2)

ulonglong CGameObjSet<class_IGenerator>::vf_0x28(longlong param_1,int param_2)

{
  void *_Dst;
  longlong *plVar1;
  ulonglong *puVar2;
  errno_t eVar3;
  ulonglong extraout_RAX;
  ulonglong uVar4;
  undefined8 uVar5;
  undefined8 extraout_RAX_00;
  undefined8 extraout_RAX_01;
  undefined8 extraout_RAX_02;
  undefined4 extraout_var;
  undefined8 extraout_RAX_03;
  longlong lVar6;
  rsize_t _DstSize;
  ulonglong uVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  
  if (param_2 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return extraout_RAX & 0xffffffffffffff00;
  }
  uVar9 = 0;
  uVar4 = *(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3;
  uVar7 = uVar9;
  if (uVar4 != 0) {
    do {
      if ((ulonglong)(*(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3) <= uVar7)
      {
        _invalid_parameter_noinfo();
      }
      plVar1 = *(longlong **)(*(longlong *)(param_1 + 0x20) + uVar7 * 8);
      if ((plVar1 != (longlong *)0x0) &&
         (uVar5 = (**(code **)(*plVar1 + 8))(plVar1), (int)uVar5 == param_2)) {
        if (*(char *)(param_1 + 0x38) != '\0') {
          uVar5 = (**(code **)(*plVar1 + 0xa0))(plVar1);
        }
        uVar4 = *(ulonglong *)(param_1 + 0x20);
        if (*(ulonglong *)(param_1 + 0x28) < uVar4) {
          _invalid_parameter_noinfo();
          uVar5 = extraout_RAX_00;
        }
        puVar2 = *(ulonglong **)(param_1 + 8);
        if (puVar2 == (ulonglong *)0x0) {
          _invalid_parameter_noinfo();
          uVar5 = extraout_RAX_01;
          uVar8 = uVar9;
        }
        else {
          uVar8 = *puVar2;
        }
        _Dst = (void *)(uVar4 + uVar7 * 8);
        if (_Dst <= *(void **)(uVar8 + 0x20)) {
          if (puVar2 != (ulonglong *)0x0) {
            uVar9 = *puVar2;
          }
          if (*(void **)(uVar9 + 0x18) <= _Dst) goto LAB_14002eabb;
        }
        _invalid_parameter_noinfo();
        uVar5 = extraout_RAX_02;
LAB_14002eabb:
        lVar6 = *(longlong *)(param_1 + 0x28) - ((longlong)_Dst + 8) >> 3;
        if (0 < lVar6) {
          _DstSize = lVar6 << 3;
          eVar3 = memmove_s(_Dst,_DstSize,(void *)((longlong)_Dst + 8),_DstSize);
          uVar5 = CONCAT44(extraout_var,eVar3);
        }
        *(longlong *)(param_1 + 0x28) = *(longlong *)(param_1 + 0x28) + -8;
        if ((_Dst < *(void **)(param_1 + 0x20)) || (*(void **)(param_1 + 0x28) < _Dst)) {
          _invalid_parameter_noinfo();
          uVar5 = extraout_RAX_03;
        }
        return CONCAT71((int7)((ulonglong)uVar5 >> 8),1);
      }
      uVar7 = uVar7 + 1;
      uVar4 = *(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3;
    } while (uVar7 < uVar4);
  }
  return uVar4 & 0xffffffffffffff00;
}


// ==== CGameObjSet<class_IGenerator>::vf_0x38 @ 14002eb00  longlong * vf_0x38(longlong param_1, int param_2)

longlong * CGameObjSet<class_IGenerator>::vf_0x38(longlong param_1,int param_2)

{
  void *_Dst;
  longlong *plVar1;
  ulonglong uVar2;
  ulonglong *puVar3;
  int iVar4;
  longlong lVar5;
  rsize_t _DstSize;
  ulonglong uVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  
  if (*(char *)(param_1 + 0x38) == '\0') {
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  uVar8 = 0;
  uVar6 = uVar8;
  if (*(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3 != 0) {
    do {
      if ((ulonglong)(*(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3) <= uVar6)
      {
        _invalid_parameter_noinfo();
      }
      plVar1 = *(longlong **)(*(longlong *)(param_1 + 0x20) + uVar6 * 8);
      if ((plVar1 != (longlong *)0x0) &&
         (iVar4 = (**(code **)(*plVar1 + 8))(plVar1), iVar4 == param_2)) {
        if (*(char *)(param_1 + 0x38) == '\0') {
          return plVar1;
        }
        uVar2 = *(ulonglong *)(param_1 + 0x20);
        if (*(ulonglong *)(param_1 + 0x28) < uVar2) {
          _invalid_parameter_noinfo();
        }
        puVar3 = *(ulonglong **)(param_1 + 8);
        if (puVar3 == (ulonglong *)0x0) {
          _invalid_parameter_noinfo();
          uVar7 = uVar8;
        }
        else {
          uVar7 = *puVar3;
        }
        _Dst = (void *)(uVar2 + uVar6 * 8);
        if (_Dst <= *(void **)(uVar7 + 0x20)) {
          if (puVar3 != (ulonglong *)0x0) {
            uVar8 = *puVar3;
          }
          if (*(void **)(uVar8 + 0x18) <= _Dst) goto LAB_14002ec15;
        }
        _invalid_parameter_noinfo();
LAB_14002ec15:
        lVar5 = *(longlong *)(param_1 + 0x28) - ((longlong)_Dst + 8) >> 3;
        if (0 < lVar5) {
          _DstSize = lVar5 << 3;
          memmove_s(_Dst,_DstSize,(void *)((longlong)_Dst + 8),_DstSize);
        }
        *(longlong *)(param_1 + 0x28) = *(longlong *)(param_1 + 0x28) + -8;
        if ((*(void **)(param_1 + 0x20) <= _Dst) && (_Dst <= *(void **)(param_1 + 0x28))) {
          return plVar1;
        }
        _invalid_parameter_noinfo();
        return plVar1;
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < (ulonglong)(*(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3)
            );
  }
  return (longlong *)0x0;
}


// ==== CGameObjSet<class_IGenerator>::vf_0x0 @ 140031860  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CGameObjSet<class_IGenerator>::vf_0x0(undefined8 *param_1,uint param_2)

{
  FUN_14002f700(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CGameObjSet<class_IGenerator>::vf_0x20 @ 1400319c0  undefined8 vf_0x20(longlong * param_1, longlong * param_2)

undefined8 CGameObjSet<class_IGenerator>::vf_0x20(longlong *param_1,longlong *param_2)

{
  longlong lVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  ulonglong extraout_RAX;
  longlong *local_res10;
  
  local_res10 = param_2;
  if (param_2 != (longlong *)0x0) {
    iVar3 = (**(code **)(*param_2 + 8))(param_2);
    if (iVar3 != 0) {
      lVar1 = *param_1;
      uVar4 = (**(code **)(*param_2 + 8))(param_2);
      cVar2 = (**(code **)(lVar1 + 0x28))(param_1,uVar4);
      if (cVar2 != '\0') {
        log_InlineLogERROR(&DAT_1400be0b0);
      }
      uVar5 = FUN_14002f880(param_1 + 1,&local_res10);
      return CONCAT71((int7)((ulonglong)uVar5 >> 8),1);
    }
  }
  log_InlineLogERROR(&DAT_1400be0b0);
  return extraout_RAX & 0xffffffffffffff00;
}


