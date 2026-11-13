// NpcServer.exe :: _unnamed  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== FUN_1400429f0 @ 1400429f0  undefined FUN_1400429f0(longlong param_1)

void FUN_1400429f0(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_1 + 8);
  if (plVar3 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar3 + 2;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)*plVar1 == 0) {
      (**(code **)*plVar3)(plVar3);
      LOCK();
      piVar2 = (int *)((longlong)plVar3 + 0x14);
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (*piVar2 == 0) {
        (**(code **)(*plVar3 + 8))(plVar3);
      }
    }
  }
  return;
}


// ==== FUN_140042a30 @ 140042a30  undefined8 * FUN_140042a30(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140042a30(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_140042ac0 @ 140042ac0  undefined FUN_140042ac0(longlong param_1)

void FUN_140042ac0(longlong param_1)

{
  if (*(void **)(param_1 + 0x20) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x20));
  }
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x30) = 0;
  operator_delete(*(void **)(param_1 + 8));
  return;
}


// ==== FUN_140042b10 @ 140042b10  void * FUN_140042b10(undefined8 param_1, longlong param_2, longlong param_3, void * param_4)

void * FUN_140042b10(undefined8 param_1,longlong param_2,longlong param_3,void *param_4)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = *(longlong *)(param_3 + 8) - (longlong)*(void **)(param_2 + 8) >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_4,_DstSize,*(void **)(param_2 + 8),_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_4);
}


// ==== FUN_140042b80 @ 140042b80  undefined8 * FUN_140042b80(longlong param_1, undefined8 * param_2, int param_3)

undefined8 * FUN_140042b80(longlong param_1,undefined8 *param_2,int param_3)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  int iVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  uint uVar7;
  undefined8 local_28;
  longlong *local_20;
  
  puVar5 = (undefined8 *)0x0;
  if (param_3 == 0) {
    if (*(longlong *)(param_1 + 0x28) == 0) {
      puVar6 = (undefined8 *)operator_new(8);
      if (puVar6 != (undefined8 *)0x0) {
        *puVar6 = IAIStrategy::vftable;
        *puVar6 = CDefaultAIStrategy::vftable;
        puVar5 = puVar6;
      }
      local_28 = 0;
      local_20 = (longlong *)0x0;
      FUN_140041be0(&local_28,puVar5);
      plVar1 = local_20;
      FUN_1400402d0((undefined8 *)(param_1 + 0x28),local_28,(longlong)local_20);
      plVar3 = local_20;
      if (plVar1 != (longlong *)0x0) {
        LOCK();
        plVar1 = plVar1 + 2;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)*plVar1 == 0) {
          (**(code **)*local_20)(local_20);
          LOCK();
          piVar2 = (int *)((longlong)plVar3 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*local_20 + 8))();
          }
        }
      }
    }
    *param_2 = 0;
    param_2[1] = 0;
    FUN_1400402d0(param_2,*(undefined8 *)(param_1 + 0x28),*(longlong *)(param_1 + 0x30));
  }
  else if (param_3 == 1) {
    iVar4 = rand();
    uVar7 = iVar4 >> 0x1f & 0x3f;
    puVar5 = (undefined8 *)
             FUN_140042360((longlong *)(param_1 + 0x68),
                           (longlong)(int)((iVar4 + uVar7 & 0x3f) - uVar7));
    *param_2 = 0;
    param_2[1] = 0;
    FUN_1400402d0(param_2,*puVar5,puVar5[1]);
  }
  else {
    log_InlineLogERROR("CAIStrategyMgr::GetAIStrategy(%d) bad parameter.");
    *param_2 = 0;
    param_2[1] = 0;
    FUN_1400402d0(param_2,*(undefined8 *)(param_1 + 0x28),*(longlong *)(param_1 + 0x30));
  }
  return param_2;
}


// ==== FUN_140042d00 @ 140042d00  undefined8 * FUN_140042d00(undefined8 * param_1)

undefined8 * FUN_140042d00(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  puVar2 = (undefined8 *)0x0;
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_1;
    puVar2 = puVar1;
  }
  *param_1 = puVar2;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  return param_1;
}


// ==== FUN_140042d60 @ 140042d60  undefined8 * FUN_140042d60(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140042d60(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[3];
  *param_2 = 0;
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_140042db0 @ 140042db0  undefined8 * FUN_140042db0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140042db0(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[4];
  *param_2 = 0;
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_140042e00 @ 140042e00  undefined8 * FUN_140042e00(undefined8 * param_1)

undefined8 * FUN_140042e00(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  puVar2 = (undefined8 *)0x0;
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_1;
    puVar2 = puVar1;
  }
  *param_1 = puVar2;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  return param_1;
}


// ==== FUN_140042e60 @ 140042e60  undefined8 * FUN_140042e60(undefined8 * param_1)

undefined8 * FUN_140042e60(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  puVar2 = (undefined8 *)0x0;
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_1;
    puVar2 = puVar1;
  }
  *param_1 = puVar2;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  return param_1;
}


// ==== FUN_140042ec0 @ 140042ec0  longlong * FUN_140042ec0(longlong * param_1, longlong * param_2, longlong param_3, longlong param_4)

longlong * FUN_140042ec0(longlong *param_1,longlong *param_2,longlong param_3,longlong param_4)

{
  rsize_t _DstSize;
  ulonglong uVar1;
  void *_Src;
  void *_Dst;
  longlong lVar2;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (longlong *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  lVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = lVar2;
  _Src = *(void **)(param_4 + 8);
  if ((_Src < (void *)param_1[3]) || ((void *)param_1[4] < _Src)) {
    _invalid_parameter_noinfo();
  }
  if ((*param_2 == 0) || (*param_2 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  _Dst = (void *)param_2[1];
  if (_Dst != _Src) {
    lVar2 = param_1[4] - (longlong)_Src >> 3;
    _DstSize = lVar2 * 8;
    if (0 < lVar2) {
      memmove_s(_Dst,_DstSize,_Src,_DstSize);
    }
    param_1[4] = (longlong)(_DstSize + (longlong)_Dst);
  }
  return param_2;
}


// ==== FUN_140042fb0 @ 140042fb0  undefined8 * FUN_140042fb0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140042fb0(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[3];
  *param_2 = 0;
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_140043000 @ 140043000  undefined8 * FUN_140043000(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140043000(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[4];
  *param_2 = 0;
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_140043050 @ 140043050  undefined8 * FUN_140043050(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140043050(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[3];
  *param_2 = 0;
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_1400430a0 @ 1400430a0  undefined8 * FUN_1400430a0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_1400430a0(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[4];
  *param_2 = 0;
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_1400430f0 @ 1400430f0  undefined8 * FUN_1400430f0(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_1400430f0(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (undefined8 *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_140043150 @ 140043150  undefined8 * FUN_140043150(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_140043150(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (undefined8 *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_1400431b0 @ 1400431b0  undefined8 FUN_1400431b0(longlong param_1, longlong * param_2)

undefined8 FUN_1400431b0(longlong param_1,longlong *param_2)

{
  ulonglong uVar1;
  double *pdVar2;
  double *pdVar3;
  ulonglong uVar4;
  longlong local_18;
  ulonglong uStack_10;
  
  uVar1 = param_2[3];
  uVar4 = *(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18);
  if (((param_2[4] - uVar1 ^ uVar4) & 0xfffffffffffffff8) == 0) {
    if ((ulonglong)param_2[4] < uVar1) {
      _invalid_parameter_noinfo();
    }
    local_18 = *param_2;
    pdVar2 = *(double **)(param_1 + 0x20);
    uStack_10 = uVar1;
    if (pdVar2 < *(double **)(param_1 + 0x18)) {
      _invalid_parameter_noinfo();
    }
    pdVar3 = *(double **)(param_1 + 0x18);
    if (*(double **)(param_1 + 0x20) < pdVar3) {
      _invalid_parameter_noinfo();
    }
    uVar4 = FUN_140041e10(pdVar3,pdVar2,&local_18);
    if ((char)uVar4 != '\0') {
      return CONCAT71((int7)(uVar4 >> 8),1);
    }
  }
  return uVar4 & 0xffffffffffffff00;
}


// ==== FUN_1400432a0 @ 1400432a0  undefined FUN_1400432a0(undefined8 param_1, longlong param_2)

void FUN_1400432a0(undefined8 param_1,longlong param_2)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_2 + 8);
  if (plVar3 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar3 + 2;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)*plVar1 == 0) {
      (**(code **)*plVar3)(plVar3);
      LOCK();
      piVar2 = (int *)((longlong)plVar3 + 0x14);
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (*piVar2 == 0) {
        (**(code **)(*plVar3 + 8))(plVar3);
      }
    }
  }
  return;
}


// ==== FUN_1400432e0 @ 1400432e0  undefined8 * FUN_1400432e0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_1400432e0(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[3];
  *param_2 = 0;
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_140043330 @ 140043330  undefined8 * FUN_140043330(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140043330(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[4];
  *param_2 = 0;
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_140043380 @ 140043380  undefined8 * FUN_140043380(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_140043380(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (undefined8 *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_140043410 @ 140043410  void * FUN_140043410(void * param_1, uint param_2)

void * FUN_140043410(void *param_1,uint param_2)

{
  if (*(void **)((longlong)param_1 + 0x20) != (void *)0x0) {
    operator_delete(*(void **)((longlong)param_1 + 0x20));
  }
  *(undefined8 *)((longlong)param_1 + 0x20) = 0;
  *(undefined8 *)((longlong)param_1 + 0x28) = 0;
  *(undefined8 *)((longlong)param_1 + 0x30) = 0;
  operator_delete(*(void **)((longlong)param_1 + 8));
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_140043490 @ 140043490  undefined8 * FUN_140043490(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140043490(undefined8 *param_1,undefined8 *param_2)

{
  code *pcVar1;
  undefined8 *puVar2;
  longlong lVar3;
  void *pvVar4;
  ulonglong uVar5;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined8 local_28;
  ulonglong uStack_20;
  
  puVar2 = (undefined8 *)operator_new(8);
  if (puVar2 == (undefined8 *)0x0) {
    puVar2 = (undefined8 *)0x0;
  }
  else {
    *puVar2 = param_1;
  }
  *param_1 = puVar2;
  uVar5 = (longlong)(param_2[4] - param_2[3]) >> 3;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  if (uVar5 != 0) {
    if (0x1fffffffffffffff < uVar5) {
      FUN_14003ecb0();
      pcVar1 = (code *)swi(3);
      puVar2 = (undefined8 *)(*pcVar1)();
      return puVar2;
    }
    lVar3 = FUN_1400401e0(param_1 + 2,uVar5);
    param_1[3] = lVar3;
    param_1[4] = lVar3;
    param_1[5] = lVar3 + uVar5 * 8;
    uVar5 = param_2[4];
    if (uVar5 < (ulonglong)param_2[3]) {
      _invalid_parameter_noinfo();
    }
    local_58 = (undefined4)*param_2;
    uStack_54 = (undefined4)((ulonglong)*param_2 >> 0x20);
    uStack_50 = (undefined4)uVar5;
    uStack_4c = (undefined4)(uVar5 >> 0x20);
    local_38 = local_58;
    uStack_34 = uStack_54;
    uStack_30 = uStack_50;
    uStack_2c = uStack_4c;
    uVar5 = param_2[3];
    if ((ulonglong)param_2[4] < uVar5) {
      _invalid_parameter_noinfo();
    }
    local_28 = *param_2;
    uStack_20 = uVar5;
    pvVar4 = FUN_140042b10(param_1,(longlong)&local_28,(longlong)&local_38,(void *)param_1[3]);
    param_1[4] = pvVar4;
  }
  return param_1;
}


// ==== FUN_1400435c0 @ 1400435c0  undefined FUN_1400435c0(longlong param_1, longlong * param_2)

void FUN_1400435c0(longlong param_1,longlong *param_2)

{
  longlong *plVar1;
  double *pdVar2;
  int iVar3;
  int iVar4;
  double *pdVar5;
  longlong lVar6;
  
  pdVar5 = (double *)param_2[3];
  if ((double *)param_2[4] < pdVar5) {
    _invalid_parameter_noinfo();
  }
  plVar1 = (longlong *)*param_2;
  while( true ) {
    pdVar2 = (double *)param_2[4];
    if (pdVar2 < (double *)param_2[3]) {
      _invalid_parameter_noinfo();
    }
    if ((plVar1 == (longlong *)0x0) || (plVar1 != (longlong *)*param_2)) {
      _invalid_parameter_noinfo();
    }
    if (pdVar5 == pdVar2) break;
    iVar3 = rand();
    if ((double)iVar3 * 3.0517578125e-05 < *(double *)(param_1 + 0x20)) {
      if (plVar1 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar6 = 0;
      }
      else {
        lVar6 = *plVar1;
      }
      if (*(double **)(lVar6 + 0x20) <= pdVar5) {
        _invalid_parameter_noinfo();
      }
      iVar3 = rand();
      iVar4 = rand();
      *pdVar5 = ((double)iVar3 * 3.0517578125e-05 - (double)iVar4 * 3.0517578125e-05) *
                *(double *)(param_1 + 0x18) + *pdVar5;
    }
    if (plVar1 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar6 = 0;
    }
    else {
      lVar6 = *plVar1;
    }
    if (*(double **)(lVar6 + 0x20) <= pdVar5) {
      _invalid_parameter_noinfo();
    }
    pdVar5 = pdVar5 + 1;
  }
  return;
}


// ==== FUN_140043700 @ 140043700  undefined FUN_140043700(longlong param_1)

void FUN_140043700(longlong param_1)

{
  longlong *plVar1;
  longlong *plVar2;
  double *pdVar3;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  tm *ptVar4;
  longlong lVar5;
  double *pdVar6;
  longlong *plVar7;
  longlong lVar8;
  undefined1 auStack_1e8 [32];
  int local_1c8;
  int local_1c0;
  int local_1b8;
  int local_1b0;
  int local_1a8;
  __time32_t local_198 [4];
  longlong *local_188;
  longlong *plStack_180;
  void *local_178 [3];
  double *local_160;
  double *local_158;
  undefined8 local_150;
  undefined8 local_148;
  longlong local_138 [2];
  byte abStack_128 [128];
  longlong local_a8;
  char local_38 [24];
  ulonglong local_20;
  
  local_148 = 0xfffffffffffffffe;
  local_20 = DAT_140103510 ^ (ulonglong)auStack_1e8;
  local_1c8 = 1;
  std::basic_ofstream<char,struct_std::char_traits<char>_>::
  basic_ofstream<char,struct_std::char_traits<char>_>
            ((basic_ofstream<char,struct_std::char_traits<char>_> *)local_138,".\\AIStrategy.dat",2,
             0x40);
  if (local_a8 == 0) {
    std::basic_ofstream<char,struct_std::char_traits<char>_>::_vbase_destructor_
              ((basic_ofstream<char,struct_std::char_traits<char>_> *)local_138);
  }
  else {
    plVar7 = *(longlong **)(param_1 + 0x80);
    if (*(longlong **)(param_1 + 0x88) < plVar7) {
      _invalid_parameter_noinfo();
    }
    plVar1 = *(longlong **)(param_1 + 0x68);
    lVar8 = 0;
    local_188 = plVar1;
    plStack_180 = plVar7;
    while( true ) {
      plVar2 = *(longlong **)(param_1 + 0x88);
      if (plVar2 < *(longlong **)(param_1 + 0x80)) {
        _invalid_parameter_noinfo();
      }
      if ((plVar1 == (longlong *)0x0) || (plVar1 != *(longlong **)(param_1 + 0x68))) {
        _invalid_parameter_noinfo();
      }
      if (plVar7 == plVar2) break;
      if (plVar1 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar5 = lVar8;
      }
      else {
        lVar5 = *plVar1;
      }
      if (*(longlong **)(lVar5 + 0x20) <= plVar7) {
        _invalid_parameter_noinfo();
      }
      FUN_1400672f0(*plVar7,(longlong *)local_178);
      pdVar3 = local_158;
      if (local_158 < local_160) {
        _invalid_parameter_noinfo();
      }
      pdVar6 = local_160;
      if (local_158 < local_160) {
        _invalid_parameter_noinfo();
      }
      for (; pdVar6 != pdVar3; pdVar6 = pdVar6 + 1) {
        std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<
                  ((basic_ostream<char,struct_std::char_traits<char>_> *)local_138,*pdVar6);
        FUN_140040840((basic_ostream<char,struct_std::char_traits<char>_> *)local_138," ");
        lVar5 = (longlong)local_138 + (longlong)*(int *)(local_138[0] + 4);
        if ((abStack_128[*(int *)(local_138[0] + 4)] & 6) != 0) {
          lVar5 = lVar8;
        }
        if (lVar5 == 0) {
          _invalid_parameter_noinfo();
        }
      }
      this = FUN_140040650((basic_ostream<char,struct_std::char_traits<char>_> *)local_138,'*');
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,endl_exref);
      if (local_160 != (double *)0x0) {
        operator_delete(local_160);
      }
      local_160 = (double *)0x0;
      local_158 = (double *)0x0;
      local_150 = 0;
      operator_delete(local_178[0]);
      if (plVar1 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar5 = lVar8;
      }
      else {
        lVar5 = *plVar1;
      }
      if (*(longlong **)(lVar5 + 0x20) <= plVar7) {
        _invalid_parameter_noinfo();
      }
      plVar7 = plVar7 + 2;
    }
    local_38[0] = '\0';
    local_38[1] = '\0';
    local_38[2] = '\0';
    local_38[3] = '\0';
    local_38[4] = '\0';
    local_38[5] = '\0';
    local_38[6] = '\0';
    local_38[7] = '\0';
    local_38[8] = '\0';
    local_38[9] = '\0';
    local_38[10] = '\0';
    local_38[0xb] = '\0';
    local_38[0xc] = '\0';
    local_38[0xd] = '\0';
    local_38[0xe] = '\0';
    local_38[0xf] = '\0';
    local_38[0x10] = '\0';
    local_38[0x11] = '\0';
    local_38[0x12] = '\0';
    local_38[0x13] = 0;
    local_198[0] = _time32((__time32_t *)0x0);
    ptVar4 = _localtime32(local_198);
    if (ptVar4 == (tm *)0x0) {
      std::basic_ofstream<char,struct_std::char_traits<char>_>::_vbase_destructor_
                ((basic_ofstream<char,struct_std::char_traits<char>_> *)local_138);
    }
    else {
      local_1c8 = ptVar4->tm_mon + 1;
      local_1a8 = ptVar4->tm_sec;
      local_1b0 = ptVar4->tm_min;
      local_1b8 = ptVar4->tm_hour;
      local_1c0 = ptVar4->tm_mday;
      _snprintf(local_38,0x14,"%04d-%02d-%02d %02d:%02d:%02d",(ulonglong)(ptVar4->tm_year + 0x76c));
      FUN_140040840((basic_ostream<char,struct_std::char_traits<char>_> *)local_138,local_38);
      std::basic_ofstream<char,struct_std::char_traits<char>_>::close
                ((basic_ofstream<char,struct_std::char_traits<char>_> *)local_138);
      std::basic_ofstream<char,struct_std::char_traits<char>_>::_vbase_destructor_
                ((basic_ofstream<char,struct_std::char_traits<char>_> *)local_138);
    }
  }
  __security_check_cookie(local_20 ^ (ulonglong)auStack_1e8);
  return;
}


// ==== FUN_140043a50 @ 140043a50  undefined FUN_140043a50(longlong * param_1)

void FUN_140043a50(longlong *param_1)

{
  rsize_t _DstSize;
  void *_Src;
  void *_Dst;
  longlong lVar1;
  
  _Src = (void *)param_1[4];
  if (_Src < (void *)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  _Dst = (void *)param_1[3];
  if ((void *)param_1[4] < _Dst) {
    _invalid_parameter_noinfo();
  }
  if ((_Dst < (void *)param_1[3]) || ((void *)param_1[4] < _Dst)) {
    _invalid_parameter_noinfo();
  }
  lVar1 = *param_1;
  if ((_Src < (void *)param_1[3]) || ((void *)param_1[4] < _Src)) {
    _invalid_parameter_noinfo();
  }
  if ((lVar1 == 0) || (lVar1 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (_Dst != _Src) {
    lVar1 = param_1[4] - (longlong)_Src >> 3;
    _DstSize = lVar1 * 8;
    if (0 < lVar1) {
      memmove_s(_Dst,_DstSize,_Src,_DstSize);
    }
    param_1[4] = (longlong)(_DstSize + (longlong)_Dst);
  }
  return;
}


// ==== FUN_140043b40 @ 140043b40  undefined FUN_140043b40(longlong param_1, longlong param_2, ulonglong param_3, undefined8 * param_4)

void FUN_140043b40(longlong param_1,longlong param_2,ulonglong param_3,undefined8 *param_4)

{
  undefined8 uVar1;
  code *pcVar2;
  void *pvVar3;
  longlong lVar4;
  ulonglong uVar5;
  undefined8 *puVar6;
  longlong lVar7;
  rsize_t rVar8;
  ulonglong uVar9;
  void *pvVar10;
  ulonglong uVar11;
  undefined8 *puVar12;
  
  lVar4 = *(longlong *)(param_1 + 0x18);
  if (lVar4 == 0) {
    uVar5 = 0;
  }
  else {
    uVar5 = *(longlong *)(param_1 + 0x28) - lVar4 >> 3;
  }
  uVar9 = 0;
  if (param_3 != 0) {
    lVar7 = *(longlong *)(param_1 + 0x20);
    lVar4 = lVar7 - lVar4 >> 3;
    if (0x1fffffffffffffffU - lVar4 < param_3) {
      FUN_14003ecb0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    uVar11 = param_3 + lVar4;
    if (uVar5 < uVar11) {
      if (uVar5 <= 0x1fffffffffffffff - (uVar5 >> 1)) {
        uVar9 = uVar5 + (uVar5 >> 1);
      }
      if (uVar9 < uVar11) {
        uVar9 = uVar11;
      }
      pvVar3 = (void *)FUN_1400401e0(param_1 + 0x10,uVar9);
      lVar4 = *(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18) >> 3;
      puVar6 = (undefined8 *)((longlong)pvVar3 + lVar4 * 8);
      for (uVar5 = param_3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *puVar6 = *param_4;
        puVar6 = puVar6 + 1;
      }
      lVar7 = *(longlong *)(param_2 + 8) - (longlong)*(void **)(param_1 + 0x18) >> 3;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 3;
        memmove_s(pvVar3,rVar8,*(void **)(param_1 + 0x18),rVar8);
      }
      lVar7 = *(longlong *)(param_1 + 0x20) - (longlong)*(void **)(param_2 + 8) >> 3;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 3;
        memmove_s((void *)((longlong)pvVar3 + (lVar4 + param_3) * 8),rVar8,*(void **)(param_2 + 8),
                  rVar8);
      }
      pvVar10 = *(void **)(param_1 + 0x18);
      lVar4 = *(longlong *)(param_1 + 0x20);
      if (pvVar10 != (void *)0x0) {
        operator_delete(pvVar10);
      }
      *(void **)(param_1 + 0x28) = (void *)((longlong)pvVar3 + uVar9 * 8);
      *(void **)(param_1 + 0x20) =
           (void *)((longlong)pvVar3 + (param_3 + (lVar4 - (longlong)pvVar10 >> 3)) * 8);
      *(void **)(param_1 + 0x18) = pvVar3;
    }
    else if ((ulonglong)(lVar7 - *(longlong *)(param_2 + 8) >> 3) < param_3) {
      uVar1 = *param_4;
      FUN_1400428e0(param_1,*(void **)(param_2 + 8),lVar7,
                    (void *)((longlong)*(void **)(param_2 + 8) + param_3 * 8));
      puVar6 = *(undefined8 **)(param_1 + 0x20);
      for (lVar4 = param_3 - ((longlong)puVar6 - *(longlong *)(param_2 + 8) >> 3); lVar4 != 0;
          lVar4 = lVar4 + -1) {
        *puVar6 = uVar1;
        puVar6 = puVar6 + 1;
      }
      *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + param_3 * 8;
      lVar4 = *(longlong *)(param_1 + 0x20);
      for (puVar6 = *(undefined8 **)(param_2 + 8); puVar6 != (undefined8 *)(lVar4 + param_3 * -8);
          puVar6 = puVar6 + 1) {
        *puVar6 = uVar1;
      }
    }
    else {
      uVar1 = *param_4;
      pvVar10 = (void *)(lVar7 + param_3 * -8);
      pvVar3 = FUN_1400428e0(param_1,pvVar10,lVar7,(void *)lVar7);
      *(void **)(param_1 + 0x20) = pvVar3;
      FUN_140041990(*(void **)(param_2 + 8),(longlong)pvVar10,lVar7);
      puVar12 = *(undefined8 **)(param_2 + 8);
      puVar6 = puVar12 + param_3;
      for (; puVar12 != puVar6; puVar12 = puVar12 + 1) {
        *puVar12 = uVar1;
      }
    }
  }
  return;
}


// ==== FUN_140043df0 @ 140043df0  longlong * FUN_140043df0(longlong * param_1, longlong * param_2, longlong param_3, longlong param_4)

longlong * FUN_140043df0(longlong *param_1,longlong *param_2,longlong param_3,longlong param_4)

{
  rsize_t _DstSize;
  ulonglong uVar1;
  void *_Src;
  void *_Dst;
  longlong lVar2;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (longlong *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  lVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = lVar2;
  _Src = *(void **)(param_4 + 8);
  if ((_Src < (void *)param_1[3]) || ((void *)param_1[4] < _Src)) {
    _invalid_parameter_noinfo();
  }
  if ((*param_2 == 0) || (*param_2 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  _Dst = (void *)param_2[1];
  if (_Dst != _Src) {
    lVar2 = param_1[4] - (longlong)_Src >> 2;
    _DstSize = lVar2 * 4;
    if (0 < lVar2) {
      memmove_s(_Dst,_DstSize,_Src,_DstSize);
    }
    param_1[4] = (longlong)(_DstSize + (longlong)_Dst);
  }
  return param_2;
}


// ==== FUN_140043ee0 @ 140043ee0  undefined FUN_140043ee0(undefined8 * param_1, longlong param_2, undefined8 * param_3)

void FUN_140043ee0(undefined8 *param_1,longlong param_2,undefined8 *param_3)

{
  for (; param_2 != 0; param_2 = param_2 + -1) {
    if (param_1 != (undefined8 *)0x0) {
      *param_1 = 0;
      param_1[1] = 0;
      FUN_140040460(param_1,*param_3,param_3[1]);
    }
    param_1 = param_1 + 2;
  }
  return;
}


// ==== FUN_140043f60 @ 140043f60  undefined FUN_140043f60(longlong param_1, longlong param_2)

void FUN_140043f60(longlong param_1,longlong param_2)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  if (param_1 != param_2) {
    do {
      plVar3 = *(longlong **)(param_1 + 8);
      if (plVar3 != (longlong *)0x0) {
        LOCK();
        plVar1 = plVar3 + 2;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)*plVar1 == 0) {
          (**(code **)*plVar3)(plVar3);
          LOCK();
          piVar2 = (int *)((longlong)plVar3 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*plVar3 + 8))(plVar3);
          }
        }
      }
      param_1 = param_1 + 0x10;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_140043fd0 @ 140043fd0  undefined8 * FUN_140043fd0(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

/* WARNING: Removing unreachable block (ram,0x0001400440a3) */
/* WARNING: Removing unreachable block (ram,0x0001400440ac) */
/* WARNING: Removing unreachable block (ram,0x0001400440c0) */
/* WARNING: Removing unreachable block (ram,0x0001400440d5) */

undefined8 * FUN_140043fd0(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  
  for (; param_1 != param_2; param_1 = param_1 + 2) {
    if (param_3 != (undefined8 *)0x0) {
      *param_3 = 0;
      param_3[1] = 0;
      FUN_140040460(param_3,0,0);
    }
    puVar1 = param_1 + 1;
    puVar2 = param_3 + 1;
    if (puVar2 != puVar1) {
      uVar3 = *puVar2;
      *puVar2 = *puVar1;
      *puVar1 = uVar3;
    }
    if (param_3 != param_1) {
      uVar3 = *param_3;
      *param_3 = *param_1;
      *param_1 = uVar3;
    }
    param_3 = param_3 + 2;
  }
  return param_3;
}


// ==== FUN_140044150 @ 140044150  undefined FUN_140044150(longlong param_1)

void FUN_140044150(longlong param_1)

{
  if (*(void **)(param_1 + 0x20) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x20));
  }
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x30) = 0;
  operator_delete(*(void **)(param_1 + 8));
  return;
}


// ==== FUN_1400441a0 @ 1400441a0  undefined4 * FUN_1400441a0(undefined4 * param_1, undefined4 * param_2)

undefined4 * FUN_1400441a0(undefined4 *param_1,undefined4 *param_2)

{
  *param_1 = *param_2;
  FUN_140043490((undefined8 *)(param_1 + 2),(undefined8 *)(param_2 + 2));
  return param_1;
}


// ==== FUN_1400441e0 @ 1400441e0  longlong * FUN_1400441e0(longlong * param_1, longlong * param_2)

longlong * FUN_1400441e0(longlong *param_1,longlong *param_2)

{
  void *pvVar1;
  void *_Dst;
  ulonglong uVar2;
  void *pvVar3;
  undefined8 uVar4;
  ulonglong uVar5;
  longlong lVar6;
  rsize_t _DstSize;
  ulonglong uVar7;
  
  if (param_1 != param_2) {
    pvVar3 = (void *)param_2[3];
    uVar2 = param_2[4] - (longlong)pvVar3 >> 3;
    if (uVar2 == 0) {
      FUN_140043a50(param_1);
      return param_1;
    }
    _Dst = (void *)param_1[3];
    uVar7 = param_1[4] - (longlong)_Dst >> 3;
    if (uVar2 <= uVar7) {
      lVar6 = param_2[4] - (longlong)pvVar3 >> 3;
      if (0 < lVar6) {
        _DstSize = lVar6 << 3;
        memmove_s(_Dst,_DstSize,pvVar3,_DstSize);
      }
      param_1[4] = param_1[3] + (param_2[4] - param_2[3] >> 3) * 8;
      return param_1;
    }
    if (_Dst == (void *)0x0) {
      uVar5 = 0;
    }
    else {
      uVar5 = param_1[5] - (longlong)_Dst >> 3;
    }
    if (uVar2 <= uVar5) {
      pvVar1 = (void *)((longlong)pvVar3 + uVar7 * 8);
      FUN_140041860(pvVar3,(longlong)pvVar1,_Dst);
      pvVar3 = FUN_1400418a0(param_1,pvVar1,param_2[4],(void *)param_1[4]);
      param_1[4] = (longlong)pvVar3;
      return param_1;
    }
    if (_Dst != (void *)0x0) {
      operator_delete(_Dst);
    }
    uVar4 = FUN_140041120((longlong)param_1,param_2[4] - param_2[3] >> 3);
    if ((char)uVar4 != '\0') {
      pvVar3 = FUN_1400418a0(param_1,(void *)param_2[3],param_2[4],(void *)param_1[3]);
      param_1[4] = (longlong)pvVar3;
    }
  }
  return param_1;
}


// ==== FUN_140044320 @ 140044320  longlong * FUN_140044320(longlong * param_1, longlong * param_2, longlong * param_3, undefined8 * param_4)

longlong * FUN_140044320(longlong *param_1,longlong *param_2,longlong *param_3,undefined8 *param_4)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  longlong *local_28;
  ulonglong uStack_20;
  
  lVar3 = 0;
  uVar1 = param_1[3];
  lVar4 = lVar3;
  if ((param_1[4] - uVar1 & 0xfffffffffffffff8) != 0) {
    if ((ulonglong)param_1[4] < uVar1) {
      _invalid_parameter_noinfo();
    }
    if ((*param_3 == 0) || (*param_3 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    lVar4 = (longlong)(param_3[1] - uVar1) >> 3;
  }
  local_28 = (longlong *)*param_3;
  uStack_20 = param_3[1];
  FUN_140043b40((longlong)param_1,(longlong)&local_28,1,param_4);
  uVar1 = param_1[3];
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)*param_1;
  local_28 = plVar2;
  uStack_20 = uVar1;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar3;
  }
  else {
    lVar5 = *plVar2;
  }
  uVar1 = uVar1 + lVar4 * 8;
  if (uVar1 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar2 != (longlong *)0x0) {
      lVar3 = *plVar2;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar1) goto LAB_140044414;
  }
  _invalid_parameter_noinfo();
LAB_140044414:
  *param_2 = (longlong)local_28;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_140044450 @ 140044450  undefined FUN_140044450(longlong * param_1)

void FUN_140044450(longlong *param_1)

{
  rsize_t _DstSize;
  void *_Src;
  void *_Dst;
  longlong lVar1;
  
  _Src = (void *)param_1[4];
  if (_Src < (void *)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  _Dst = (void *)param_1[3];
  if ((void *)param_1[4] < _Dst) {
    _invalid_parameter_noinfo();
  }
  if ((_Dst < (void *)param_1[3]) || ((void *)param_1[4] < _Dst)) {
    _invalid_parameter_noinfo();
  }
  lVar1 = *param_1;
  if ((_Src < (void *)param_1[3]) || ((void *)param_1[4] < _Src)) {
    _invalid_parameter_noinfo();
  }
  if ((lVar1 == 0) || (lVar1 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (_Dst != _Src) {
    lVar1 = param_1[4] - (longlong)_Src >> 2;
    _DstSize = lVar1 * 4;
    if (0 < lVar1) {
      memmove_s(_Dst,_DstSize,_Src,_DstSize);
    }
    param_1[4] = (longlong)(_DstSize + (longlong)_Dst);
  }
  return;
}


// ==== FUN_140044510 @ 140044510  undefined FUN_140044510(undefined8 * param_1, longlong param_2, undefined8 * param_3)

void FUN_140044510(undefined8 *param_1,longlong param_2,undefined8 *param_3)

{
  FUN_140043ee0(param_1,param_2,param_3);
  return;
}


// ==== FUN_140044530 @ 140044530  undefined FUN_140044530(longlong * param_1, longlong * param_2)

void FUN_140044530(longlong *param_1,longlong *param_2)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  longlong *plVar4;
  
  if (param_1 != param_2) {
    plVar4 = param_1 + 1;
    do {
      plVar3 = (longlong *)*plVar4;
      if (plVar3 != (longlong *)0x0) {
        LOCK();
        plVar1 = plVar3 + 2;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)*plVar1 == 0) {
          (**(code **)*plVar3)(plVar3);
          LOCK();
          piVar2 = (int *)((longlong)plVar3 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*plVar3 + 8))(plVar3);
          }
        }
      }
      plVar3 = plVar4 + 1;
      plVar4 = plVar4 + 2;
    } while (plVar3 != param_2);
  }
  return;
}


// ==== FUN_1400445a0 @ 1400445a0  undefined FUN_1400445a0(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

void FUN_1400445a0(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  FUN_140043fd0(param_1,param_2,param_3);
  return;
}


// ==== FUN_1400445c0 @ 1400445c0  longlong FUN_1400445c0(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

longlong FUN_1400445c0(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  longlong lVar3;
  undefined8 *puVar4;
  longlong lVar6;
  undefined8 *puVar5;
  
  lVar3 = (longlong)param_3 - ((longlong)param_2 - (longlong)param_1 & 0xfffffffffffffff0U);
  if (param_1 != param_2) {
    lVar6 = (longlong)param_3 - (longlong)param_2;
    puVar4 = param_2 + 1;
    do {
      puVar5 = puVar4 + -2;
      param_3 = param_3 + -2;
      puVar1 = (undefined8 *)((longlong)puVar5 + lVar6);
      if (puVar1 != puVar5) {
        uVar2 = *puVar1;
        *puVar1 = *puVar5;
        *puVar5 = uVar2;
      }
      puVar1 = puVar4 + -3;
      if (param_3 != puVar1) {
        uVar2 = *param_3;
        *param_3 = *puVar1;
        *puVar1 = uVar2;
      }
      puVar4 = puVar5;
    } while (puVar1 != param_1);
  }
  return lVar3;
}


// ==== FUN_140044640 @ 140044640  undefined FUN_140044640(undefined8 param_1, longlong param_2)

void FUN_140044640(undefined8 param_1,longlong param_2)

{
  if (*(void **)(param_2 + 0x20) != (void *)0x0) {
    operator_delete(*(void **)(param_2 + 0x20));
  }
  *(undefined8 *)(param_2 + 0x20) = 0;
  *(undefined8 *)(param_2 + 0x28) = 0;
  *(undefined8 *)(param_2 + 0x30) = 0;
  operator_delete(*(void **)(param_2 + 8));
  return;
}


// ==== FUN_140044690 @ 140044690  undefined4 * FUN_140044690(undefined4 * param_1, undefined4 * param_2)

undefined4 * FUN_140044690(undefined4 *param_1,undefined4 *param_2)

{
  *param_1 = *param_2;
  FUN_1400441e0((longlong *)(param_1 + 2),(longlong *)(param_2 + 2));
  return param_1;
}


// ==== FUN_1400446c0 @ 1400446c0  undefined FUN_1400446c0(undefined4 * param_1, undefined4 * param_2)

void FUN_1400446c0(undefined4 *param_1,undefined4 *param_2)

{
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = *param_2;
    FUN_140043490((undefined8 *)(param_1 + 2),(undefined8 *)(param_2 + 2));
  }
  return;
}


// ==== FUN_140044700 @ 140044700  undefined FUN_140044700(longlong * param_1, undefined8 * param_2)

void FUN_140044700(longlong *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  ulonglong uVar3;
  longlong local_28;
  undefined8 *puStack_20;
  longlong local_18 [2];
  
  puVar1 = (undefined8 *)param_1[3];
  if (puVar1 == (undefined8 *)0x0) {
    uVar3 = 0;
  }
  else {
    uVar3 = param_1[5] - (longlong)puVar1 >> 3;
  }
  puVar2 = (undefined8 *)param_1[4];
  if ((ulonglong)((longlong)puVar2 - (longlong)puVar1 >> 3) < uVar3) {
    *puVar2 = *param_2;
    param_1[4] = (longlong)(puVar2 + 1);
    return;
  }
  if (puVar2 < puVar1) {
    _invalid_parameter_noinfo();
  }
  local_28 = *param_1;
  puStack_20 = puVar2;
  FUN_140044320(param_1,local_18,&local_28,param_2);
  return;
}


// ==== FUN_1400447b0 @ 1400447b0  longlong * FUN_1400447b0(longlong * param_1, longlong * param_2)

longlong * FUN_1400447b0(longlong *param_1,longlong *param_2)

{
  void *pvVar1;
  void *_Dst;
  ulonglong uVar2;
  void *pvVar3;
  undefined8 uVar4;
  ulonglong uVar5;
  longlong lVar6;
  rsize_t _DstSize;
  ulonglong uVar7;
  
  if (param_1 != param_2) {
    pvVar3 = (void *)param_2[3];
    uVar2 = param_2[4] - (longlong)pvVar3 >> 2;
    if (uVar2 == 0) {
      FUN_140044450(param_1);
      return param_1;
    }
    _Dst = (void *)param_1[3];
    uVar7 = param_1[4] - (longlong)_Dst >> 2;
    if (uVar2 <= uVar7) {
      lVar6 = param_2[4] - (longlong)pvVar3 >> 2;
      if (0 < lVar6) {
        _DstSize = lVar6 << 2;
        memmove_s(_Dst,_DstSize,pvVar3,_DstSize);
      }
      param_1[4] = param_1[3] + (param_2[4] - param_2[3] >> 2) * 4;
      return param_1;
    }
    if (_Dst == (void *)0x0) {
      uVar5 = 0;
    }
    else {
      uVar5 = param_1[5] - (longlong)_Dst >> 2;
    }
    if (uVar2 <= uVar5) {
      pvVar1 = (void *)((longlong)pvVar3 + uVar7 * 4);
      FUN_1400418e0(pvVar3,(longlong)pvVar1,_Dst);
      pvVar3 = FUN_140041920(param_1,pvVar1,param_2[4],(void *)param_1[4]);
      param_1[4] = (longlong)pvVar3;
      return param_1;
    }
    if (_Dst != (void *)0x0) {
      operator_delete(_Dst);
    }
    uVar4 = FUN_1400412c0((longlong)param_1,param_2[4] - param_2[3] >> 2);
    if ((char)uVar4 != '\0') {
      pvVar3 = FUN_140041920(param_1,(void *)param_2[3],param_2[4],(void *)param_1[3]);
      param_1[4] = (longlong)pvVar3;
    }
  }
  return param_1;
}


// ==== FUN_1400448f0 @ 1400448f0  undefined8 * FUN_1400448f0(undefined8 param_1, undefined8 * param_2, longlong param_3, undefined8 * param_4)

undefined8 *
FUN_1400448f0(undefined8 param_1,undefined8 *param_2,longlong param_3,undefined8 *param_4)

{
  FUN_140043ee0(param_2,param_3,param_4);
  return param_2 + param_3 * 2;
}


// ==== FUN_140044940 @ 140044940  undefined FUN_140044940(undefined8 param_1, longlong * param_2, longlong * param_3)

void FUN_140044940(undefined8 param_1,longlong *param_2,longlong *param_3)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  longlong *plVar4;
  
  if (param_2 != param_3) {
    plVar4 = param_2 + 1;
    do {
      plVar3 = (longlong *)*plVar4;
      if (plVar3 != (longlong *)0x0) {
        LOCK();
        plVar1 = plVar3 + 2;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)*plVar1 == 0) {
          (**(code **)*plVar3)(plVar3);
          LOCK();
          piVar2 = (int *)((longlong)plVar3 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*plVar3 + 8))(plVar3);
          }
        }
      }
      plVar3 = plVar4 + 1;
      plVar4 = plVar4 + 2;
    } while (plVar3 != param_3);
  }
  return;
}


// ==== FUN_1400449b0 @ 1400449b0  undefined FUN_1400449b0(undefined8 param_1, undefined8 * param_2, undefined8 * param_3, undefined8 * param_4)

void FUN_1400449b0(undefined8 param_1,undefined8 *param_2,undefined8 *param_3,undefined8 *param_4)

{
  FUN_140043fd0(param_2,param_3,param_4);
  return;
}


// ==== FUN_1400449f0 @ 1400449f0  longlong FUN_1400449f0(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

longlong FUN_1400449f0(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  longlong lVar3;
  undefined8 *puVar4;
  longlong lVar6;
  undefined8 *puVar5;
  
  lVar3 = (longlong)param_3 - ((longlong)param_2 - (longlong)param_1 & 0xfffffffffffffff0U);
  if (param_1 != param_2) {
    lVar6 = (longlong)param_3 - (longlong)param_2;
    puVar4 = param_2 + 1;
    do {
      puVar5 = puVar4 + -2;
      param_3 = param_3 + -2;
      puVar1 = (undefined8 *)((longlong)puVar5 + lVar6);
      if (puVar1 != puVar5) {
        uVar2 = *puVar1;
        *puVar1 = *puVar5;
        *puVar5 = uVar2;
      }
      puVar1 = puVar4 + -3;
      if (param_3 != puVar1) {
        uVar2 = *param_3;
        *param_3 = *puVar1;
        *puVar1 = uVar2;
      }
      puVar4 = puVar5;
    } while (puVar1 != param_1);
  }
  return lVar3;
}


// ==== FUN_140044a70 @ 140044a70  undefined8 * FUN_140044a70(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140044a70(undefined8 *param_1,undefined8 *param_2)

{
  FUN_140044700((longlong *)*param_1,param_2);
  return param_1;
}


// ==== FUN_140044a90 @ 140044a90  undefined FUN_140044a90(longlong param_1, longlong param_2)

void FUN_140044a90(longlong param_1,longlong param_2)

{
  if (param_1 != param_2) {
    do {
      if (*(void **)(param_1 + 0x20) != (void *)0x0) {
        operator_delete(*(void **)(param_1 + 0x20));
      }
      *(undefined8 *)(param_1 + 0x20) = 0;
      *(undefined8 *)(param_1 + 0x28) = 0;
      *(undefined8 *)(param_1 + 0x30) = 0;
      operator_delete(*(void **)(param_1 + 8));
      param_1 = param_1 + 0x38;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_140044b10 @ 140044b10  undefined4 * FUN_140044b10(undefined4 * param_1, undefined4 * param_2, undefined4 * param_3)

undefined4 * FUN_140044b10(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  if (param_1 != param_2) {
    do {
      *param_3 = *param_1;
      FUN_1400441e0((longlong *)(param_3 + 2),(longlong *)(param_1 + 2));
      param_1 = param_1 + 0xe;
      param_3 = param_3 + 0xe;
    } while (param_1 != param_2);
  }
  return param_3;
}


// ==== FUN_140044b70 @ 140044b70  undefined FUN_140044b70(undefined8 param_1, undefined4 * param_2, undefined4 * param_3)

void FUN_140044b70(undefined8 param_1,undefined4 *param_2,undefined4 *param_3)

{
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = *param_3;
    FUN_140043490((undefined8 *)(param_2 + 2),(undefined8 *)(param_3 + 2));
  }
  return;
}


// ==== FUN_140044bb0 @ 140044bb0  undefined4 * FUN_140044bb0(undefined4 * param_1, undefined4 * param_2, undefined4 * param_3)

undefined4 * FUN_140044bb0(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 0xe) {
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = *param_1;
      FUN_140043490((undefined8 *)(param_3 + 2),(undefined8 *)(param_1 + 2));
    }
    param_3 = param_3 + 0xe;
  }
  return param_3;
}


// ==== FUN_140044c20 @ 140044c20  undefined FUN_140044c20(longlong param_1, longlong * param_2, longlong * param_3, longlong * param_4, longlong * param_5)

void FUN_140044c20(longlong param_1,longlong *param_2,longlong *param_3,longlong *param_4,
                  longlong *param_5)

{
  longlong lVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  int iVar8;
  ulonglong uVar9;
  ulonglong uVar10;
  
  iVar5 = rand();
  if ((double)iVar5 * 3.0517578125e-05 < *(double *)(param_1 + 0x10) ||
      (double)iVar5 * 3.0517578125e-05 == *(double *)(param_1 + 0x10)) {
    uVar7 = FUN_1400431b0((longlong)param_3,param_2);
    if ((char)uVar7 == '\0') {
      lVar1 = *(longlong *)(param_1 + 0x58);
      lVar2 = *(longlong *)(param_1 + 0x50);
      iVar5 = rand();
      lVar3 = *(longlong *)(param_1 + 0x58);
      lVar4 = *(longlong *)(param_1 + 0x50);
      iVar5 = iVar5 % ((int)(lVar1 - lVar2 >> 2) + -1);
      iVar6 = rand();
      if ((ulonglong)(*(longlong *)(param_1 + 0x58) - *(longlong *)(param_1 + 0x50) >> 2) <=
          (ulonglong)(longlong)iVar5) {
        _invalid_parameter_noinfo();
      }
      uVar9 = (ulonglong)(iVar5 + iVar6 % ((int)(lVar3 - lVar4 >> 2) - iVar5));
      iVar5 = *(int *)(*(longlong *)(param_1 + 0x50) + (longlong)iVar5 * 4);
      if ((ulonglong)(*(longlong *)(param_1 + 0x58) - *(longlong *)(param_1 + 0x50) >> 2) <= uVar9)
      {
        _invalid_parameter_noinfo();
      }
      iVar6 = *(int *)(*(longlong *)(param_1 + 0x50) + uVar9 * 4);
      FUN_140043a50(param_4);
      FUN_140043a50(param_5);
      iVar8 = 0;
      uVar9 = param_3[4] - param_3[3] >> 3;
      if (0 < (int)uVar9) {
        do {
          if ((iVar8 < iVar5) || (iVar6 <= iVar8)) {
            uVar10 = (ulonglong)iVar8;
            if (uVar9 <= uVar10) {
              _invalid_parameter_noinfo();
            }
            FUN_140044700(param_4,(undefined8 *)(param_3[3] + uVar10 * 8));
            if ((ulonglong)(param_2[4] - param_2[3] >> 3) <= uVar10) {
              _invalid_parameter_noinfo();
            }
            FUN_140044700(param_5,(undefined8 *)(param_2[3] + uVar10 * 8));
          }
          else {
            uVar9 = (ulonglong)iVar8;
            if ((ulonglong)(param_2[4] - param_2[3] >> 3) <= uVar9) {
              _invalid_parameter_noinfo();
            }
            FUN_140044700(param_4,(undefined8 *)(param_2[3] + uVar9 * 8));
            if ((ulonglong)(param_3[4] - param_3[3] >> 3) <= uVar9) {
              _invalid_parameter_noinfo();
            }
            FUN_140044700(param_5,(undefined8 *)(param_3[3] + uVar9 * 8));
          }
          iVar8 = iVar8 + 1;
          uVar9 = param_3[4] - param_3[3] >> 3;
        } while (iVar8 < (int)uVar9);
      }
      return;
    }
  }
  FUN_1400441e0(param_4,param_3);
  FUN_1400441e0(param_5,param_2);
  return;
}


// ==== FUN_140044e30 @ 140044e30  undefined FUN_140044e30(longlong param_1)

void FUN_140044e30(longlong param_1)

{
  if (*(longlong **)(param_1 + 0x18) != (longlong *)0x0) {
    FUN_140044940(param_1,*(longlong **)(param_1 + 0x18),*(longlong **)(param_1 + 0x20));
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_140044e70 @ 140044e70  undefined FUN_140044e70(longlong param_1, longlong param_2, ulonglong param_3, longlong * param_4)

void FUN_140044e70(longlong param_1,longlong param_2,ulonglong param_3,longlong *param_4)

{
  int *piVar1;
  longlong *plVar2;
  ulonglong uVar3;
  int iVar4;
  longlong *plVar5;
  longlong lVar6;
  longlong *plVar7;
  code *pcVar8;
  undefined8 *puVar9;
  undefined8 *puVar10;
  longlong lVar11;
  ulonglong uVar12;
  ulonglong uVar13;
  longlong *plVar14;
  longlong *plVar15;
  longlong local_60;
  longlong *local_58;
  longlong local_50;
  longlong *local_48;
  undefined8 local_40;
  
  local_40 = 0xfffffffffffffffe;
  lVar11 = *(longlong *)(param_1 + 0x18);
  if (lVar11 == 0) {
    uVar12 = 0;
  }
  else {
    uVar12 = *(longlong *)(param_1 + 0x28) - lVar11 >> 4;
  }
  uVar13 = 0;
  if (param_3 != 0) {
    lVar11 = *(longlong *)(param_1 + 0x20) - lVar11 >> 4;
    if (0xfffffffffffffffU - lVar11 < param_3) {
      FUN_14003ee20();
      pcVar8 = (code *)swi(3);
      (*pcVar8)();
      return;
    }
    uVar3 = lVar11 + param_3;
    if (uVar12 < uVar3) {
      if (uVar12 <= 0xfffffffffffffff - (uVar12 >> 1)) {
        uVar13 = uVar12 + (uVar12 >> 1);
      }
      if (uVar13 < uVar3) {
        uVar13 = uVar3;
      }
      puVar9 = (undefined8 *)FUN_1400403f0(param_1 + 0x10,uVar13);
      lVar11 = *(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18) >> 4;
      FUN_140043ee0(puVar9 + lVar11 * 2,param_3,param_4);
      FUN_140043fd0(*(undefined8 **)(param_1 + 0x18),*(undefined8 **)(param_2 + 8),puVar9);
      FUN_140043fd0(*(undefined8 **)(param_2 + 8),*(undefined8 **)(param_1 + 0x20),
                    puVar9 + (lVar11 + param_3) * 2);
      plVar5 = *(longlong **)(param_1 + 0x18);
      lVar11 = *(longlong *)(param_1 + 0x20);
      if (plVar5 != (longlong *)0x0) {
        FUN_140044940(param_1,plVar5,*(longlong **)(param_1 + 0x20));
        operator_delete(*(void **)(param_1 + 0x18));
      }
      *(undefined8 **)(param_1 + 0x28) = puVar9 + uVar13 * 2;
      *(undefined8 **)(param_1 + 0x20) = puVar9 + (param_3 + (lVar11 - (longlong)plVar5 >> 4)) * 2;
      *(undefined8 **)(param_1 + 0x18) = puVar9;
    }
    else if ((ulonglong)(*(longlong *)(param_1 + 0x20) - *(longlong *)(param_2 + 8) >> 4) < param_3)
    {
      plVar5 = (longlong *)param_4[1];
      lVar11 = *param_4;
      if (plVar5 != (longlong *)0x0) {
        LOCK();
        *(int *)(plVar5 + 2) = (int)plVar5[2] + 1;
        UNLOCK();
      }
      local_60 = lVar11;
      local_58 = plVar5;
      FUN_140043fd0(*(undefined8 **)(param_2 + 8),*(undefined8 **)(param_1 + 0x20),
                    *(undefined8 **)(param_2 + 8) + param_3 * 2);
      FUN_140043ee0(*(undefined8 **)(param_1 + 0x20),
                    param_3 - ((longlong)*(undefined8 **)(param_1 + 0x20) -
                               *(longlong *)(param_2 + 8) >> 4),&local_60);
      *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + param_3 * 0x10;
      lVar6 = *(longlong *)(param_1 + 0x20);
      for (plVar14 = *(longlong **)(param_2 + 8); plVar14 != (longlong *)(lVar6 + param_3 * -0x10);
          plVar14 = plVar14 + 2) {
        if (plVar5 != (longlong *)0x0) {
          LOCK();
          *(int *)(plVar5 + 2) = (int)plVar5[2] + 1;
          UNLOCK();
        }
        plVar15 = (longlong *)plVar14[1];
        if (plVar15 != (longlong *)0x0) {
          LOCK();
          plVar7 = plVar15 + 2;
          *(int *)plVar7 = (int)*plVar7 + -1;
          UNLOCK();
          if ((int)*plVar7 == 0) {
            (**(code **)*plVar15)(plVar15);
            LOCK();
            piVar1 = (int *)((longlong)plVar15 + 0x14);
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (*piVar1 == 0) {
              (**(code **)(*plVar15 + 8))(plVar15);
            }
          }
        }
        plVar14[1] = (longlong)plVar5;
        *plVar14 = lVar11;
      }
      if (plVar5 != (longlong *)0x0) {
        LOCK();
        plVar14 = plVar5 + 2;
        lVar11 = *plVar14;
        *(int *)plVar14 = (int)*plVar14 + -1;
        UNLOCK();
        if ((int)lVar11 == 1) {
          (**(code **)*plVar5)(plVar5);
          LOCK();
          piVar1 = (int *)((longlong)plVar5 + 0x14);
          iVar4 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar4 == 1) {
            (**(code **)(*plVar5 + 8))(plVar5);
          }
        }
      }
    }
    else {
      plVar5 = (longlong *)param_4[1];
      lVar11 = *param_4;
      if (plVar5 != (longlong *)0x0) {
        LOCK();
        *(int *)(plVar5 + 2) = (int)plVar5[2] + 1;
        UNLOCK();
      }
      puVar9 = *(undefined8 **)(param_1 + 0x20);
      local_50 = lVar11;
      local_48 = plVar5;
      puVar10 = FUN_140043fd0(puVar9 + param_3 * -2,puVar9,puVar9);
      *(undefined8 **)(param_1 + 0x20) = puVar10;
      FUN_1400449f0(*(undefined8 **)(param_2 + 8),puVar9 + param_3 * -2,puVar9);
      plVar14 = *(longlong **)(param_2 + 8);
      if (plVar14 != plVar14 + param_3 * 2) {
        plVar15 = plVar14 + 1;
        do {
          if (plVar5 != (longlong *)0x0) {
            LOCK();
            *(int *)(plVar5 + 2) = (int)plVar5[2] + 1;
            UNLOCK();
          }
          plVar7 = (longlong *)*plVar15;
          if (plVar7 != (longlong *)0x0) {
            LOCK();
            plVar2 = plVar7 + 2;
            *(int *)plVar2 = (int)*plVar2 + -1;
            UNLOCK();
            if ((int)*plVar2 == 0) {
              (**(code **)*plVar7)(plVar7);
              LOCK();
              piVar1 = (int *)((longlong)plVar7 + 0x14);
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (*piVar1 == 0) {
                (**(code **)(*plVar7 + 8))(plVar7);
              }
            }
          }
          *plVar15 = (longlong)plVar5;
          plVar15[-1] = lVar11;
          plVar7 = plVar15 + 1;
          plVar15 = plVar15 + 2;
        } while (plVar7 != plVar14 + param_3 * 2);
      }
      if (plVar5 != (longlong *)0x0) {
        LOCK();
        plVar14 = plVar5 + 2;
        lVar11 = *plVar14;
        *(int *)plVar14 = (int)*plVar14 + -1;
        UNLOCK();
        if ((int)lVar11 == 1) {
          (**(code **)*plVar5)(plVar5);
          LOCK();
          piVar1 = (int *)((longlong)plVar5 + 0x14);
          iVar4 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar4 == 1) {
            (**(code **)(*plVar5 + 8))(plVar5);
          }
        }
      }
    }
  }
  return;
}


// ==== FUN_1400452a0 @ 1400452a0  undefined8 * FUN_1400452a0(undefined8 * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

undefined8 *
FUN_1400452a0(undefined8 *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  basic_istream<char,struct_std::char_traits<char>_> *pbVar1;
  
  if (*param_2 == *param_3) {
    *param_1 = param_4;
    return param_1;
  }
  do {
    if (*param_2 == 0) {
      _invalid_parameter_noinfo();
    }
    FUN_140044700(param_4,param_2 + 1);
    pbVar1 = (basic_istream<char,struct_std::char_traits<char>_> *)*param_2;
    if (pbVar1 == (basic_istream<char,struct_std::char_traits<char>_> *)0x0) {
      _invalid_parameter_noinfo();
      pbVar1 = (basic_istream<char,struct_std::char_traits<char>_> *)*param_2;
      if (pbVar1 != (basic_istream<char,struct_std::char_traits<char>_> *)0x0) goto LAB_1400452ff;
    }
    else {
LAB_1400452ff:
      pbVar1 = std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
                         (pbVar1,(double *)(param_2 + 1));
      if (((byte)pbVar1[(longlong)*(int *)(*(longlong *)pbVar1 + 4) + 0x10] & 6) != 0) {
        *param_2 = 0;
      }
    }
    if (*param_2 == *param_3) {
      *param_1 = param_4;
      return param_1;
    }
  } while( true );
}


// ==== FUN_140045370 @ 140045370  longlong FUN_140045370(undefined4 * param_1, undefined4 * param_2, longlong param_3)

longlong FUN_140045370(undefined4 *param_1,undefined4 *param_2,longlong param_3)

{
  longlong lVar1;
  longlong lVar2;
  
  lVar2 = (longlong)param_2 - (longlong)param_1;
  if (param_1 != param_2) {
    lVar1 = param_3 - (longlong)param_1;
    do {
      *(undefined4 *)(lVar1 + (longlong)param_1) = *param_1;
      FUN_1400441e0((longlong *)(lVar1 + (longlong)(param_1 + 2)),(longlong *)(param_1 + 2));
      param_1 = param_1 + 0xe;
    } while (param_1 != param_2);
  }
  return (lVar2 / 0x38) * 0x38 + param_3;
}


// ==== FUN_140045400 @ 140045400  undefined4 * FUN_140045400(undefined4 * param_1, undefined4 * param_2, undefined4 * param_3)

undefined4 * FUN_140045400(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 0xe) {
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = *param_1;
      FUN_140043490((undefined8 *)(param_3 + 2),(undefined8 *)(param_1 + 2));
    }
    param_3 = param_3 + 0xe;
  }
  return param_3;
}


// ==== FUN_140045470 @ 140045470  undefined FUN_140045470(longlong param_1, longlong param_2, undefined4 * param_3)

void FUN_140045470(longlong param_1,longlong param_2,undefined4 *param_3)

{
  FUN_140044bb0(*(undefined4 **)(param_1 + 8),*(undefined4 **)(param_2 + 8),param_3);
  return;
}


// ==== FUN_1400454a0 @ 1400454a0  undefined FUN_1400454a0(undefined8 * param_1)

void FUN_1400454a0(undefined8 *param_1)

{
  if ((longlong *)param_1[3] != (longlong *)0x0) {
    FUN_140044940(param_1,(longlong *)param_1[3],(longlong *)param_1[4]);
    operator_delete((void *)param_1[3]);
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_1400454f0 @ 1400454f0  longlong * FUN_1400454f0(longlong * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_1400454f0(longlong *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  longlong *plVar1;
  longlong lVar2;
  longlong lVar3;
  ulonglong uVar4;
  longlong lVar5;
  longlong *local_28;
  ulonglong uStack_20;
  
  lVar2 = 0;
  uVar4 = param_1[3];
  lVar3 = lVar2;
  if ((param_1[4] - uVar4 & 0xfffffffffffffff0) != 0) {
    if ((ulonglong)param_1[4] < uVar4) {
      _invalid_parameter_noinfo();
    }
    if ((*param_3 == 0) || (*param_3 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    lVar3 = (longlong)(param_3[1] - uVar4) >> 4;
  }
  local_28 = (longlong *)*param_3;
  uStack_20 = param_3[1];
  FUN_140044e70((longlong)param_1,(longlong)&local_28,1,param_4);
  uVar4 = param_1[3];
  if ((ulonglong)param_1[4] < uVar4) {
    _invalid_parameter_noinfo();
  }
  plVar1 = (longlong *)*param_1;
  local_28 = plVar1;
  uStack_20 = uVar4;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar2;
  }
  else {
    lVar5 = *plVar1;
  }
  uVar4 = lVar3 * 0x10 + uVar4;
  if (uVar4 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar2 = *plVar1;
    }
    if (*(ulonglong *)(lVar2 + 0x18) <= uVar4) goto LAB_1400455e7;
  }
  _invalid_parameter_noinfo();
LAB_1400455e7:
  *param_2 = (longlong)local_28;
  param_2[1] = uVar4;
  return param_2;
}


// ==== FUN_140045630 @ 140045630  undefined8 * FUN_140045630(undefined8 * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

undefined8 *
FUN_140045630(undefined8 *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  basic_istream<char,struct_std::char_traits<char>_> *pbVar1;
  basic_istream<char,struct_std::char_traits<char>_> *pbVar2;
  basic_istream<char,struct_std::char_traits<char>_> *local_28;
  double local_20;
  basic_istream<char,struct_std::char_traits<char>_> *local_18;
  longlong local_10;
  
  pbVar1 = (basic_istream<char,struct_std::char_traits<char>_> *)*param_3;
  local_10 = param_3[1];
  local_28 = (basic_istream<char,struct_std::char_traits<char>_> *)*param_2;
  local_20 = (double)param_2[1];
  if (local_28 != pbVar1) {
    local_18 = pbVar1;
    do {
      if (local_28 == (basic_istream<char,struct_std::char_traits<char>_> *)0x0) {
        _invalid_parameter_noinfo();
      }
      FUN_140044700(param_4,&local_20);
      if (local_28 == (basic_istream<char,struct_std::char_traits<char>_> *)0x0) {
        _invalid_parameter_noinfo();
      }
      else {
        pbVar2 = std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
                           (local_28,&local_20);
        if (((byte)pbVar2[(longlong)*(int *)(*(longlong *)pbVar2 + 4) + 0x10] & 6) != 0) {
          local_28 = (basic_istream<char,struct_std::char_traits<char>_> *)0x0;
        }
      }
    } while (local_28 != pbVar1);
  }
  *param_1 = param_4;
  return param_1;
}


// ==== FUN_140045720 @ 140045720  undefined FUN_140045720(longlong param_1)

void FUN_140045720(longlong param_1)

{
  if (*(longlong *)(param_1 + 0x18) != 0) {
    FUN_140044a90(*(longlong *)(param_1 + 0x18),*(longlong *)(param_1 + 0x20));
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_140045770 @ 140045770  undefined FUN_140045770(undefined4 * param_1, undefined4 * param_2, longlong param_3)

void FUN_140045770(undefined4 *param_1,undefined4 *param_2,longlong param_3)

{
  FUN_140045370(param_1,param_2,param_3);
  return;
}


// ==== FUN_1400457a0 @ 1400457a0  undefined FUN_1400457a0(undefined4 * param_1, undefined4 * param_2, undefined4 * param_3)

void FUN_1400457a0(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  FUN_140045400(param_1,param_2,param_3);
  return;
}


// ==== FUN_1400457c0 @ 1400457c0  undefined FUN_1400457c0(undefined8 param_1, longlong param_2, longlong param_3, undefined4 * param_4)

void FUN_1400457c0(undefined8 param_1,longlong param_2,longlong param_3,undefined4 *param_4)

{
  FUN_140044bb0(*(undefined4 **)(param_2 + 8),*(undefined4 **)(param_3 + 8),param_4);
  return;
}


// ==== FUN_140045820 @ 140045820  undefined FUN_140045820(undefined8 * param_1)

void FUN_140045820(undefined8 *param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  *param_1 = CAIStrategyMgr::vftable;
  FUN_140043700((longlong)param_1);
  if ((longlong *)param_1[0x10] != (longlong *)0x0) {
    FUN_140044940(param_1 + 0xd,(longlong *)param_1[0x10],(longlong *)param_1[0x11]);
    operator_delete((void *)param_1[0x10]);
  }
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  operator_delete((void *)param_1[0xd]);
  if ((void *)param_1[10] != (void *)0x0) {
    operator_delete((void *)param_1[10]);
  }
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  operator_delete((void *)param_1[7]);
  plVar3 = (longlong *)param_1[6];
  if (plVar3 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar3 + 2;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)*plVar1 == 0) {
      (**(code **)*plVar3)(plVar3);
      LOCK();
      piVar2 = (int *)((longlong)plVar3 + 0x14);
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (*piVar2 == 0) {
        (**(code **)(*plVar3 + 8))(plVar3);
      }
    }
  }
  *param_1 = tq::Singleton<class_CAIStrategyMgr>::vftable;
  return;
}


// ==== FUN_140045900 @ 140045900  undefined8 FUN_140045900(longlong param_1)

ulonglong FUN_140045900(longlong param_1)

{
  undefined8 *puVar1;
  longlong *plVar2;
  ulonglong extraout_RAX;
  basic_istream<char,struct_std::char_traits<char>_> *pbVar3;
  ulonglong extraout_RAX_00;
  undefined8 extraout_RAX_01;
  longlong *plVar4;
  basic_istream<char,struct_std::char_traits<char>_> *pbVar5;
  longlong *plStack_170;
  basic_istream<char,struct_std::char_traits<char>_> *local_168;
  longlong *plStack_160;
  basic_istream<char,struct_std::char_traits<char>_> *local_158 [3];
  void *local_140;
  longlong local_138;
  undefined8 local_130;
  undefined8 local_128;
  longlong local_118 [19];
  longlong local_80;
  
  local_128 = 0xfffffffffffffffe;
  std::basic_ifstream<char,struct_std::char_traits<char>_>::
  basic_ifstream<char,struct_std::char_traits<char>_>
            ((basic_ifstream<char,struct_std::char_traits<char>_> *)local_118,".\\AIStrategy.dat",1,
             0x40);
  if (local_80 == 0) {
    std::basic_ifstream<char,struct_std::char_traits<char>_>::_vbase_destructor_
              ((basic_ifstream<char,struct_std::char_traits<char>_> *)local_118);
    return extraout_RAX & 0xffffffffffffff00;
  }
  plVar4 = *(longlong **)(param_1 + 0x80);
  if (*(longlong **)(param_1 + 0x88) < plVar4) {
    _invalid_parameter_noinfo();
  }
  puVar1 = *(undefined8 **)(param_1 + 0x68);
  pbVar5 = (basic_istream<char,struct_std::char_traits<char>_> *)0x0;
  plStack_170 = plVar4;
  do {
    plVar2 = *(longlong **)(param_1 + 0x88);
    if (plVar2 < *(longlong **)(param_1 + 0x80)) {
      _invalid_parameter_noinfo();
    }
    if ((puVar1 == (undefined8 *)0x0) || (puVar1 != *(undefined8 **)(param_1 + 0x68))) {
      _invalid_parameter_noinfo();
    }
    if (plVar4 == plVar2) {
      std::basic_ifstream<char,struct_std::char_traits<char>_>::close
                ((basic_ifstream<char,struct_std::char_traits<char>_> *)local_118);
      std::basic_ifstream<char,struct_std::char_traits<char>_>::_vbase_destructor_
                ((basic_ifstream<char,struct_std::char_traits<char>_> *)local_118);
      return CONCAT71((int7)((ulonglong)extraout_RAX_01 >> 8),1);
    }
    pbVar3 = (basic_istream<char,struct_std::char_traits<char>_> *)operator_new(8);
    local_158[0] = pbVar5;
    if (pbVar3 != (basic_istream<char,struct_std::char_traits<char>_> *)0x0) {
      *(basic_istream<char,struct_std::char_traits<char>_> ***)pbVar3 = local_158;
      local_158[0] = pbVar3;
    }
    local_140 = (void *)0x0;
    local_138 = 0;
    local_130 = 0;
    pbVar3 = std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
                       ((basic_istream<char,struct_std::char_traits<char>_> *)local_118,
                        (double *)&plStack_170);
    local_168 = (basic_istream<char,struct_std::char_traits<char>_> *)local_118;
    plStack_160 = plStack_170;
    if (((byte)pbVar3[(longlong)*(int *)(*(longlong *)pbVar3 + 4) + 0x10] & 6) != 0) {
      local_168 = pbVar5;
    }
    while (local_168 != (basic_istream<char,struct_std::char_traits<char>_> *)0x0) {
      if (local_168 == (basic_istream<char,struct_std::char_traits<char>_> *)0x0) {
        _invalid_parameter_noinfo();
      }
      FUN_140044700((longlong *)local_158,&plStack_160);
      if (((local_168 == (basic_istream<char,struct_std::char_traits<char>_> *)0x0) &&
          (_invalid_parameter_noinfo(),
          local_168 == (basic_istream<char,struct_std::char_traits<char>_> *)0x0)) ||
         (pbVar3 = std::basic_istream<char,struct_std::char_traits<char>_>::operator>>
                             (local_168,(double *)&plStack_160),
         ((byte)pbVar3[(longlong)*(int *)(*(longlong *)pbVar3 + 4) + 0x10] & 6) != 0)) break;
    }
    std::basic_ios<char,struct_std::char_traits<char>_>::clear
              ((basic_ios<char,struct_std::char_traits<char>_> *)
               ((longlong)local_118 + (longlong)*(int *)(local_118[0] + 4)),0,false);
    std::basic_istream<char,struct_std::char_traits<char>_>::ignore
              ((basic_istream<char,struct_std::char_traits<char>_> *)local_118,0xf,0x2a);
    if (*(int *)(param_1 + 0xc) != (int)(local_138 - (longlong)local_140 >> 3)) {
      std::basic_ifstream<char,struct_std::char_traits<char>_>::close
                ((basic_ifstream<char,struct_std::char_traits<char>_> *)local_118);
      if (local_140 != (void *)0x0) {
        operator_delete(local_140);
      }
      local_140 = (void *)0x0;
      local_138 = 0;
      local_130 = 0;
      operator_delete(local_158[0]);
      std::basic_ifstream<char,struct_std::char_traits<char>_>::_vbase_destructor_
                ((basic_ifstream<char,struct_std::char_traits<char>_> *)local_118);
      return extraout_RAX_00 & 0xffffffffffffff00;
    }
    if (puVar1 == (undefined8 *)0x0) {
      _invalid_parameter_noinfo();
      pbVar3 = pbVar5;
    }
    else {
      pbVar3 = (basic_istream<char,struct_std::char_traits<char>_> *)*puVar1;
    }
    if (*(longlong **)(pbVar3 + 0x20) <= plVar4) {
      _invalid_parameter_noinfo();
    }
    FUN_1400670c0(*plVar4,(longlong)local_158);
    if (local_140 != (void *)0x0) {
      operator_delete(local_140);
    }
    local_140 = (void *)0x0;
    local_138 = 0;
    local_130 = 0;
    operator_delete(local_158[0]);
    if (puVar1 == (undefined8 *)0x0) {
      _invalid_parameter_noinfo();
      pbVar3 = pbVar5;
    }
    else {
      pbVar3 = (basic_istream<char,struct_std::char_traits<char>_> *)*puVar1;
    }
    if (*(longlong **)(pbVar3 + 0x20) <= plVar4) {
      _invalid_parameter_noinfo();
    }
    plVar4 = plVar4 + 2;
  } while( true );
}


// ==== FUN_140045c10 @ 140045c10  undefined FUN_140045c10(longlong * param_1, longlong * param_2)

void FUN_140045c10(longlong *param_1,longlong *param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  ulonglong uVar3;
  longlong local_28;
  undefined8 *puStack_20;
  longlong local_18 [2];
  
  puVar1 = (undefined8 *)param_1[3];
  if (puVar1 == (undefined8 *)0x0) {
    uVar3 = 0;
  }
  else {
    uVar3 = param_1[5] - (longlong)puVar1 >> 4;
  }
  puVar2 = (undefined8 *)param_1[4];
  if ((ulonglong)((longlong)puVar2 - (longlong)puVar1 >> 4) < uVar3) {
    FUN_140043ee0(puVar2,1,param_2);
    param_1[4] = (longlong)(puVar2 + 2);
    return;
  }
  if (puVar2 < puVar1) {
    _invalid_parameter_noinfo();
  }
  local_28 = *param_1;
  puStack_20 = puVar2;
  FUN_1400454f0(param_1,local_18,&local_28,param_2);
  return;
}


// ==== FUN_140045ce0 @ 140045ce0  undefined FUN_140045ce0(undefined8 * param_1)

void FUN_140045ce0(undefined8 *param_1)

{
  if (param_1[3] != 0) {
    FUN_140044a90(param_1[3],param_1[4]);
    operator_delete((void *)param_1[3]);
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140045d40 @ 140045d40  longlong * FUN_140045d40(longlong * param_1, longlong * param_2, longlong param_3, longlong param_4)

longlong * FUN_140045d40(longlong *param_1,longlong *param_2,longlong param_3,longlong param_4)

{
  ulonglong uVar1;
  undefined4 *puVar2;
  longlong lVar3;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (longlong *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  lVar3 = *param_1;
  param_2[1] = uVar1;
  *param_2 = lVar3;
  puVar2 = *(undefined4 **)(param_4 + 8);
  if ((puVar2 < (undefined4 *)param_1[3]) || ((undefined4 *)param_1[4] < puVar2)) {
    _invalid_parameter_noinfo();
  }
  if ((*param_2 == 0) || (*param_2 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if ((undefined4 *)param_2[1] != puVar2) {
    lVar3 = FUN_140045370(puVar2,(undefined4 *)param_1[4],param_2[1]);
    FUN_140044a90(lVar3,param_1[4]);
    param_1[4] = lVar3;
  }
  return param_2;
}


// ==== FUN_140045e40 @ 140045e40  undefined FUN_140045e40(undefined8 param_1, undefined4 * param_2, undefined4 * param_3, undefined4 * param_4)

void FUN_140045e40(undefined8 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  FUN_140045400(param_2,param_3,param_4);
  return;
}


// ==== FUN_140045e80 @ 140045e80  undefined8 * FUN_140045e80(undefined8 * param_1, longlong param_2)

undefined8 * FUN_140045e80(undefined8 *param_1,longlong param_2)

{
  undefined4 *puVar1;
  code *pcVar2;
  ulonglong uVar3;
  undefined8 *puVar4;
  longlong lVar5;
  undefined4 *puVar6;
  
  puVar4 = (undefined8 *)operator_new(8);
  if (puVar4 == (undefined8 *)0x0) {
    puVar4 = (undefined8 *)0x0;
  }
  else {
    *puVar4 = param_1;
  }
  *param_1 = puVar4;
  uVar3 = (*(longlong *)(param_2 + 0x20) - *(longlong *)(param_2 + 0x18)) / 0x38;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  if (uVar3 != 0) {
    if (0x492492492492492 < uVar3) {
      FUN_14003fa00();
      pcVar2 = (code *)swi(3);
      puVar4 = (undefined8 *)(*pcVar2)();
      return puVar4;
    }
    lVar5 = FUN_140040d80(param_1 + 2,uVar3);
    param_1[3] = lVar5;
    param_1[4] = lVar5;
    param_1[5] = uVar3 * 0x38 + lVar5;
    puVar6 = *(undefined4 **)(param_2 + 0x20);
    if (puVar6 < *(undefined4 **)(param_2 + 0x18)) {
      _invalid_parameter_noinfo();
    }
    puVar1 = *(undefined4 **)(param_2 + 0x18);
    if (*(undefined4 **)(param_2 + 0x20) < puVar1) {
      _invalid_parameter_noinfo();
    }
    puVar6 = FUN_140044bb0(puVar1,puVar6,(undefined4 *)param_1[3]);
    param_1[4] = puVar6;
  }
  return param_1;
}


// ==== FUN_140045ff0 @ 140045ff0  undefined8 * FUN_140045ff0(undefined8 * param_1)

undefined8 * FUN_140045ff0(undefined8 *param_1)

{
  longlong *plVar1;
  longlong *plVar2;
  int *piVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  longlong *plVar6;
  longlong *plVar7;
  longlong lVar8;
  undefined8 *puVar9;
  longlong local_b0;
  longlong *local_a8;
  void *local_a0 [3];
  void *local_88;
  undefined8 local_80;
  undefined8 local_78;
  void *local_70 [3];
  void *local_58;
  undefined8 local_50;
  undefined8 local_48;
  
  *param_1 = tq::Singleton<class_CAIStrategyMgr>::vftable;
  *param_1 = CAIStrategyMgr::vftable;
  puVar9 = (undefined8 *)0x0;
  param_1[5] = 0;
  param_1[6] = 0;
  FUN_140041230(param_1 + 5);
  plVar7 = param_1 + 7;
  puVar4 = (undefined8 *)operator_new(8);
  puVar5 = puVar9;
  if (puVar4 != (undefined8 *)0x0) {
    *puVar4 = plVar7;
    puVar5 = puVar4;
  }
  *plVar7 = (longlong)puVar5;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  plVar1 = param_1 + 0xd;
  puVar4 = (undefined8 *)operator_new(8);
  puVar5 = puVar9;
  if (puVar4 != (undefined8 *)0x0) {
    *puVar4 = plVar1;
    puVar5 = puVar4;
  }
  *plVar1 = (longlong)puVar5;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[2] = 0x3fe6666666666666;
  param_1[3] = 0x3fd3333333333333;
  param_1[4] = 0x3fb999999999999a;
  *(undefined4 *)(param_1 + 1) = 0;
  lVar8 = 0x40;
  do {
    puVar4 = (undefined8 *)operator_new(0x60);
    puVar5 = puVar9;
    if (puVar4 != (undefined8 *)0x0) {
      puVar5 = FUN_1400677c0(puVar4);
    }
    local_b0 = 0;
    local_a8 = (longlong *)0x0;
    FUN_140041b60(&local_b0,puVar5);
    FUN_140045c10(plVar1,&local_b0);
    plVar6 = local_a8;
    if (local_a8 != (longlong *)0x0) {
      LOCK();
      plVar2 = local_a8 + 2;
      *(int *)plVar2 = (int)*plVar2 + -1;
      UNLOCK();
      if ((int)*plVar2 == 0) {
        (**(code **)*local_a8)(local_a8);
        LOCK();
        piVar3 = (int *)((longlong)plVar6 + 0x14);
        *piVar3 = *piVar3 + -1;
        UNLOCK();
        if (*piVar3 == 0) {
          (**(code **)(*local_a8 + 8))();
        }
      }
    }
    lVar8 = lVar8 + -1;
  } while (lVar8 != 0);
  plVar6 = (longlong *)param_1[0x10];
  if ((longlong *)param_1[0x11] < plVar6) {
    _invalid_parameter_noinfo();
  }
  if ((undefined8 *)*plVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar5 = puVar9;
  }
  else {
    puVar5 = *(undefined8 **)*plVar1;
  }
  if ((longlong *)puVar5[4] <= plVar6) {
    _invalid_parameter_noinfo();
  }
  plVar6 = FUN_1400672b0(*plVar6,(longlong *)local_a0);
  FUN_1400447b0(plVar7,plVar6);
  if (local_88 != (void *)0x0) {
    operator_delete(local_88);
  }
  local_88 = (void *)0x0;
  local_80 = 0;
  local_78 = 0;
  operator_delete(local_a0[0]);
  plVar7 = (longlong *)param_1[0x10];
  if ((longlong *)param_1[0x11] < plVar7) {
    _invalid_parameter_noinfo();
  }
  if ((undefined8 *)*plVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  else {
    puVar9 = *(undefined8 **)*plVar1;
  }
  if ((longlong *)puVar9[4] <= plVar7) {
    _invalid_parameter_noinfo();
  }
  plVar7 = FUN_1400672f0(*plVar7,(longlong *)local_70);
  *(int *)((longlong)param_1 + 0xc) = (int)(plVar7[4] - plVar7[3] >> 3);
  if (local_58 != (void *)0x0) {
    operator_delete(local_58);
  }
  local_58 = (void *)0x0;
  local_50 = 0;
  local_48 = 0;
  operator_delete(local_70[0]);
  FUN_140045900((longlong)param_1);
  return param_1;
}


// ==== FUN_1400462c0 @ 1400462c0  undefined FUN_1400462c0(longlong param_1, int param_2, longlong * param_3)

void FUN_1400462c0(longlong param_1,int param_2,longlong *param_3)

{
  longlong *plVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong *plStack_30;
  
  plStack_30 = *(longlong **)(param_1 + 0x80);
  if (*(longlong **)(param_1 + 0x88) < plStack_30) {
    _invalid_parameter_noinfo();
  }
  plVar1 = *(longlong **)(param_1 + 0x68);
  if (0 < param_2) {
    do {
      plVar2 = *(longlong **)(param_1 + 0x88);
      if (plVar2 < *(longlong **)(param_1 + 0x80)) {
        _invalid_parameter_noinfo();
      }
      if ((plVar1 == (longlong *)0x0) || (plVar1 != *(longlong **)(param_1 + 0x68))) {
        _invalid_parameter_noinfo();
      }
      if (plStack_30 == plVar2) {
        return;
      }
      if (plVar1 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar3 = 0;
      }
      else {
        lVar3 = *plVar1;
      }
      if (*(longlong **)(lVar3 + 0x20) <= plStack_30) {
        _invalid_parameter_noinfo();
      }
      if (plVar1 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar3 = 0;
      }
      else {
        lVar3 = *plVar1;
      }
      if (*(longlong **)(lVar3 + 0x20) <= plStack_30) {
        _invalid_parameter_noinfo();
      }
      FUN_140045c10(param_3,plStack_30);
      param_2 = param_2 + -1;
      plStack_30 = plStack_30 + 2;
    } while (0 < param_2);
  }
  return;
}


// ==== FUN_1400463d0 @ 1400463d0  undefined FUN_1400463d0(longlong param_1)

void FUN_1400463d0(longlong param_1)

{
  if (*(longlong *)(param_1 + 0x20) != 0) {
    FUN_140044a90(*(longlong *)(param_1 + 0x20),*(longlong *)(param_1 + 0x28));
    operator_delete(*(void **)(param_1 + 0x20));
  }
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x30) = 0;
  operator_delete(*(void **)(param_1 + 8));
  return;
}


// ==== FUN_140046430 @ 140046430  undefined FUN_140046430(longlong * param_1)

void FUN_140046430(longlong *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  longlong lVar3;
  
  puVar1 = (undefined4 *)param_1[4];
  if (puVar1 < (undefined4 *)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  puVar2 = (undefined4 *)param_1[3];
  if ((undefined4 *)param_1[4] < puVar2) {
    _invalid_parameter_noinfo();
  }
  if ((puVar2 < (undefined4 *)param_1[3]) || ((undefined4 *)param_1[4] < puVar2)) {
    _invalid_parameter_noinfo();
  }
  lVar3 = *param_1;
  if ((puVar1 < (undefined4 *)param_1[3]) || ((undefined4 *)param_1[4] < puVar1)) {
    _invalid_parameter_noinfo();
  }
  if ((lVar3 == 0) || (lVar3 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (puVar2 != puVar1) {
    lVar3 = FUN_140045370(puVar1,(undefined4 *)param_1[4],(longlong)puVar2);
    FUN_140044a90(lVar3,param_1[4]);
    param_1[4] = lVar3;
  }
  return;
}


// ==== FUN_140046500 @ 140046500  undefined4 * FUN_140046500(undefined4 * param_1, undefined4 * param_2)

undefined4 * FUN_140046500(undefined4 *param_1,undefined4 *param_2)

{
  *param_1 = *param_2;
  FUN_140045e80((undefined8 *)(param_1 + 2),(longlong)(param_2 + 2));
  return param_1;
}


// ==== FUN_140046540 @ 140046540  void * FUN_140046540(void * param_1, uint param_2)

void * FUN_140046540(void *param_1,uint param_2)

{
  if (*(longlong *)((longlong)param_1 + 0x20) != 0) {
    FUN_140044a90(*(longlong *)((longlong)param_1 + 0x20),*(longlong *)((longlong)param_1 + 0x28));
    operator_delete(*(void **)((longlong)param_1 + 0x20));
  }
  *(undefined8 *)((longlong)param_1 + 0x20) = 0;
  *(undefined8 *)((longlong)param_1 + 0x28) = 0;
  *(undefined8 *)((longlong)param_1 + 0x30) = 0;
  operator_delete(*(void **)((longlong)param_1 + 8));
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_1400465d0 @ 1400465d0  longlong * FUN_1400465d0(longlong * param_1, longlong * param_2)

longlong * FUN_1400465d0(longlong *param_1,longlong *param_2)

{
  ulonglong uVar1;
  longlong lVar2;
  undefined4 *puVar3;
  undefined8 uVar4;
  ulonglong uVar5;
  longlong lVar6;
  ulonglong uVar7;
  
  if (param_1 == param_2) {
    return param_1;
  }
  lVar2 = param_2[4] - param_2[3] >> 0x3f;
  lVar6 = (param_2[4] - param_2[3]) / 0x38 + lVar2;
  uVar7 = lVar6 - lVar2;
  if (lVar6 != lVar2) {
    lVar2 = param_1[3];
    uVar1 = (param_1[4] - lVar2) / 0x38;
    if (uVar1 < uVar7) {
      if (lVar2 == 0) {
        uVar5 = 0;
      }
      else {
        uVar5 = (param_1[5] - lVar2) / 0x38;
      }
      if (uVar5 < uVar7) {
        if (lVar2 != 0) {
          FUN_140044a90(lVar2,param_1[4]);
          operator_delete((void *)param_1[3]);
        }
        uVar4 = FUN_140041fd0((longlong)param_1,(param_2[4] - param_2[3]) / 0x38);
        if ((char)uVar4 != '\0') {
          lVar2 = FUN_140045e40(param_1,(undefined4 *)param_2[3],(undefined4 *)param_2[4],
                                (undefined4 *)param_1[3]);
          param_1[4] = lVar2;
        }
      }
      else {
        puVar3 = (undefined4 *)param_2[3] + uVar1 * 0xe;
        FUN_140045370((undefined4 *)param_2[3],puVar3,lVar2);
        puVar3 = FUN_140045400(puVar3,(undefined4 *)param_2[4],(undefined4 *)param_1[4]);
        param_1[4] = (longlong)puVar3;
      }
    }
    else {
      lVar2 = FUN_140045370((undefined4 *)param_2[3],(undefined4 *)param_2[4],lVar2);
      FUN_140044a90(lVar2,param_1[4]);
      param_1[4] = ((param_2[4] - param_2[3]) / 0x38) * 0x38 + param_1[3];
    }
    return param_1;
  }
  FUN_140046430(param_1);
  return param_1;
}


// ==== FUN_1400467e0 @ 1400467e0  undefined FUN_1400467e0(undefined4 * param_1, undefined4 * param_2)

void FUN_1400467e0(undefined4 *param_1,undefined4 *param_2)

{
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = *param_2;
    FUN_140045e80((undefined8 *)(param_1 + 2),(longlong)(param_2 + 2));
  }
  return;
}


// ==== FUN_140046820 @ 140046820  undefined FUN_140046820(longlong param_1)

void FUN_140046820(longlong param_1)

{
  if (*(longlong *)(param_1 + 0x20) != 0) {
    FUN_140044a90(*(longlong *)(param_1 + 0x20),*(longlong *)(param_1 + 0x28));
    operator_delete(*(void **)(param_1 + 0x20));
  }
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x30) = 0;
  operator_delete(*(void **)(param_1 + 8));
  return;
}


// ==== FUN_140046880 @ 140046880  undefined4 * FUN_140046880(undefined4 * param_1, undefined4 * param_2)

undefined4 * FUN_140046880(undefined4 *param_1,undefined4 *param_2)

{
  *param_1 = *param_2;
  FUN_1400465d0((longlong *)(param_1 + 2),(longlong *)(param_2 + 2));
  return param_1;
}


// ==== FUN_1400468b0 @ 1400468b0  undefined FUN_1400468b0(undefined8 param_1, undefined4 * param_2, undefined4 * param_3)

void FUN_1400468b0(undefined8 param_1,undefined4 *param_2,undefined4 *param_3)

{
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = *param_3;
    FUN_140045e80((undefined8 *)(param_2 + 2),(longlong)(param_3 + 2));
  }
  return;
}


// ==== FUN_1400468f0 @ 1400468f0  undefined FUN_1400468f0(undefined8 param_1, longlong param_2)

void FUN_1400468f0(undefined8 param_1,longlong param_2)

{
  if (*(longlong *)(param_2 + 0x20) != 0) {
    FUN_140044a90(*(longlong *)(param_2 + 0x20),*(longlong *)(param_2 + 0x28));
    operator_delete(*(void **)(param_2 + 0x20));
  }
  *(undefined8 *)(param_2 + 0x20) = 0;
  *(undefined8 *)(param_2 + 0x28) = 0;
  *(undefined8 *)(param_2 + 0x30) = 0;
  operator_delete(*(void **)(param_2 + 8));
  return;
}


// ==== FUN_140046950 @ 140046950  undefined4 * FUN_140046950(undefined4 * param_1, undefined4 * param_2, undefined4 * param_3)

undefined4 * FUN_140046950(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  if (param_1 != param_2) {
    do {
      *param_3 = *param_1;
      FUN_1400465d0((longlong *)(param_3 + 2),(longlong *)(param_1 + 2));
      param_1 = param_1 + 0xe;
      param_3 = param_3 + 0xe;
    } while (param_1 != param_2);
  }
  return param_3;
}


// ==== FUN_1400469b0 @ 1400469b0  undefined4 * FUN_1400469b0(undefined4 * param_1, undefined4 * param_2, undefined4 * param_3)

undefined4 * FUN_1400469b0(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 0xe) {
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = *param_1;
      FUN_140045e80((undefined8 *)(param_3 + 2),(longlong)(param_1 + 2));
    }
    param_3 = param_3 + 0xe;
  }
  return param_3;
}


// ==== FUN_140046a20 @ 140046a20  undefined4 * FUN_140046a20(undefined4 * param_1, undefined4 * param_2, undefined4 * param_3)

undefined4 * FUN_140046a20(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 0xe) {
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = *param_1;
      FUN_140045e80((undefined8 *)(param_3 + 2),(longlong)(param_1 + 2));
    }
    param_3 = param_3 + 0xe;
  }
  return param_3;
}


// ==== FUN_140046a90 @ 140046a90  longlong FUN_140046a90(undefined4 * param_1, undefined4 * param_2, longlong param_3)

longlong FUN_140046a90(undefined4 *param_1,undefined4 *param_2,longlong param_3)

{
  longlong lVar1;
  longlong lVar2;
  
  lVar2 = (longlong)param_2 - (longlong)param_1;
  if (param_1 != param_2) {
    lVar1 = param_3 - (longlong)param_1;
    do {
      *(undefined4 *)(lVar1 + (longlong)param_1) = *param_1;
      FUN_1400465d0((longlong *)(lVar1 + (longlong)(param_1 + 2)),(longlong *)(param_1 + 2));
      param_1 = param_1 + 0xe;
    } while (param_1 != param_2);
  }
  return (lVar2 / 0x38) * 0x38 + param_3;
}


// ==== FUN_140046b20 @ 140046b20  undefined FUN_140046b20(undefined4 * param_1, undefined4 * param_2, undefined4 * param_3)

void FUN_140046b20(undefined4 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  FUN_1400469b0(param_1,param_2,param_3);
  return;
}


// ==== FUN_140046b40 @ 140046b40  undefined FUN_140046b40(longlong param_1, longlong param_2)

void FUN_140046b40(longlong param_1,longlong param_2)

{
  longlong lVar1;
  longlong lVar2;
  
  if (param_1 != param_2) {
    do {
      lVar2 = *(longlong *)(param_1 + 0x20);
      if (lVar2 != 0) {
        lVar1 = *(longlong *)(param_1 + 0x28);
        for (; lVar2 != lVar1; lVar2 = lVar2 + 0x38) {
          if (*(void **)(lVar2 + 0x20) != (void *)0x0) {
            operator_delete(*(void **)(lVar2 + 0x20));
          }
          *(undefined8 *)(lVar2 + 0x20) = 0;
          *(undefined8 *)(lVar2 + 0x28) = 0;
          *(undefined8 *)(lVar2 + 0x30) = 0;
          operator_delete(*(void **)(lVar2 + 8));
        }
        operator_delete(*(void **)(param_1 + 0x20));
      }
      *(undefined8 *)(param_1 + 0x20) = 0;
      *(undefined8 *)(param_1 + 0x28) = 0;
      *(undefined8 *)(param_1 + 0x30) = 0;
      operator_delete(*(void **)(param_1 + 8));
      param_1 = param_1 + 0x38;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_140046c20 @ 140046c20  undefined FUN_140046c20(longlong param_1, longlong param_2, undefined4 * param_3)

void FUN_140046c20(longlong param_1,longlong param_2,undefined4 *param_3)

{
  FUN_140046a20(*(undefined4 **)(param_1 + 8),*(undefined4 **)(param_2 + 8),param_3);
  return;
}


// ==== FUN_140046c50 @ 140046c50  undefined FUN_140046c50(undefined4 * param_1, undefined4 * param_2, longlong param_3)

void FUN_140046c50(undefined4 *param_1,undefined4 *param_2,longlong param_3)

{
  FUN_140046a90(param_1,param_2,param_3);
  return;
}


// ==== FUN_140046c80 @ 140046c80  undefined FUN_140046c80(undefined8 param_1, undefined4 * param_2, undefined4 * param_3, undefined4 * param_4)

void FUN_140046c80(undefined8 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  FUN_1400469b0(param_2,param_3,param_4);
  return;
}


// ==== FUN_140046cd0 @ 140046cd0  undefined FUN_140046cd0(undefined8 param_1, longlong param_2, longlong param_3, undefined4 * param_4)

void FUN_140046cd0(undefined8 param_1,longlong param_2,longlong param_3,undefined4 *param_4)

{
  FUN_140046a20(*(undefined4 **)(param_2 + 8),*(undefined4 **)(param_3 + 8),param_4);
  return;
}


// ==== FUN_140046d50 @ 140046d50  longlong * FUN_140046d50(longlong * param_1, longlong * param_2, longlong param_3, longlong param_4)

longlong * FUN_140046d50(longlong *param_1,longlong *param_2,longlong param_3,longlong param_4)

{
  ulonglong uVar1;
  undefined4 *puVar2;
  longlong lVar3;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (longlong *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  lVar3 = *param_1;
  param_2[1] = uVar1;
  *param_2 = lVar3;
  puVar2 = *(undefined4 **)(param_4 + 8);
  if ((puVar2 < (undefined4 *)param_1[3]) || ((undefined4 *)param_1[4] < puVar2)) {
    _invalid_parameter_noinfo();
  }
  if ((*param_2 == 0) || (*param_2 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if ((undefined4 *)param_2[1] != puVar2) {
    lVar3 = FUN_140046a90(puVar2,(undefined4 *)param_1[4],param_2[1]);
    FUN_140046b40(lVar3,param_1[4]);
    param_1[4] = lVar3;
  }
  return param_2;
}


// ==== FUN_140046e50 @ 140046e50  undefined FUN_140046e50(longlong param_1)

void FUN_140046e50(longlong param_1)

{
  if (*(longlong *)(param_1 + 0x18) != 0) {
    FUN_140046b40(*(longlong *)(param_1 + 0x18),*(longlong *)(param_1 + 0x20));
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_140046ea0 @ 140046ea0  undefined FUN_140046ea0(longlong * param_1)

void FUN_140046ea0(longlong *param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  longlong lVar3;
  
  puVar1 = (undefined4 *)param_1[4];
  if (puVar1 < (undefined4 *)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  puVar2 = (undefined4 *)param_1[3];
  if ((undefined4 *)param_1[4] < puVar2) {
    _invalid_parameter_noinfo();
  }
  if ((puVar2 < (undefined4 *)param_1[3]) || ((undefined4 *)param_1[4] < puVar2)) {
    _invalid_parameter_noinfo();
  }
  lVar3 = *param_1;
  if ((puVar1 < (undefined4 *)param_1[3]) || ((undefined4 *)param_1[4] < puVar1)) {
    _invalid_parameter_noinfo();
  }
  if ((lVar3 == 0) || (lVar3 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (puVar2 != puVar1) {
    lVar3 = FUN_140046a90(puVar1,(undefined4 *)param_1[4],(longlong)puVar2);
    FUN_140046b40(lVar3,param_1[4]);
    param_1[4] = lVar3;
  }
  return;
}


// ==== FUN_140046f70 @ 140046f70  undefined8 * FUN_140046f70(undefined8 * param_1, longlong param_2)

undefined8 * FUN_140046f70(undefined8 *param_1,longlong param_2)

{
  undefined4 *puVar1;
  code *pcVar2;
  ulonglong uVar3;
  undefined8 *puVar4;
  longlong lVar5;
  undefined4 *puVar6;
  
  puVar4 = (undefined8 *)operator_new(8);
  if (puVar4 == (undefined8 *)0x0) {
    puVar4 = (undefined8 *)0x0;
  }
  else {
    *puVar4 = param_1;
  }
  *param_1 = puVar4;
  uVar3 = (*(longlong *)(param_2 + 0x20) - *(longlong *)(param_2 + 0x18)) / 0x38;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  if (uVar3 != 0) {
    if (0x492492492492492 < uVar3) {
      FUN_14003ed30();
      pcVar2 = (code *)swi(3);
      puVar4 = (undefined8 *)(*pcVar2)();
      return puVar4;
    }
    lVar5 = FUN_140040260(param_1 + 2,uVar3);
    param_1[3] = lVar5;
    param_1[4] = lVar5;
    param_1[5] = uVar3 * 0x38 + lVar5;
    puVar6 = *(undefined4 **)(param_2 + 0x20);
    if (puVar6 < *(undefined4 **)(param_2 + 0x18)) {
      _invalid_parameter_noinfo();
    }
    puVar1 = *(undefined4 **)(param_2 + 0x18);
    if (*(undefined4 **)(param_2 + 0x20) < puVar1) {
      _invalid_parameter_noinfo();
    }
    puVar6 = FUN_140046a20(puVar1,puVar6,(undefined4 *)param_1[3]);
    param_1[4] = puVar6;
  }
  return param_1;
}


// ==== FUN_1400470e0 @ 1400470e0  undefined FUN_1400470e0(undefined8 * param_1)

void FUN_1400470e0(undefined8 *param_1)

{
  if (param_1[3] != 0) {
    FUN_140046b40(param_1[3],param_1[4]);
    operator_delete((void *)param_1[3]);
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140047140 @ 140047140  longlong * FUN_140047140(longlong * param_1, longlong * param_2)

longlong * FUN_140047140(longlong *param_1,longlong *param_2)

{
  ulonglong uVar1;
  longlong lVar2;
  undefined4 *puVar3;
  undefined8 uVar4;
  ulonglong uVar5;
  longlong lVar6;
  ulonglong uVar7;
  
  if (param_1 == param_2) {
    return param_1;
  }
  lVar2 = param_2[4] - param_2[3] >> 0x3f;
  lVar6 = (param_2[4] - param_2[3]) / 0x38 + lVar2;
  uVar7 = lVar6 - lVar2;
  if (lVar6 != lVar2) {
    lVar2 = param_1[3];
    uVar1 = (param_1[4] - lVar2) / 0x38;
    if (uVar1 < uVar7) {
      if (lVar2 == 0) {
        uVar5 = 0;
      }
      else {
        uVar5 = (param_1[5] - lVar2) / 0x38;
      }
      if (uVar5 < uVar7) {
        if (lVar2 != 0) {
          FUN_140046b40(lVar2,param_1[4]);
          operator_delete((void *)param_1[3]);
        }
        uVar4 = FUN_1400411c0((longlong)param_1,(param_2[4] - param_2[3]) / 0x38);
        if ((char)uVar4 != '\0') {
          lVar2 = FUN_140046c80(param_1,(undefined4 *)param_2[3],(undefined4 *)param_2[4],
                                (undefined4 *)param_1[3]);
          param_1[4] = lVar2;
        }
      }
      else {
        puVar3 = (undefined4 *)param_2[3] + uVar1 * 0xe;
        FUN_140046a90((undefined4 *)param_2[3],puVar3,lVar2);
        puVar3 = FUN_1400469b0(puVar3,(undefined4 *)param_2[4],(undefined4 *)param_1[4]);
        param_1[4] = (longlong)puVar3;
      }
    }
    else {
      lVar2 = FUN_140046a90((undefined4 *)param_2[3],(undefined4 *)param_2[4],lVar2);
      FUN_140046b40(lVar2,param_1[4]);
      param_1[4] = ((param_2[4] - param_2[3]) / 0x38) * 0x38 + param_1[3];
    }
    return param_1;
  }
  FUN_140046ea0(param_1);
  return param_1;
}


// ==== FUN_140047350 @ 140047350  undefined4 * FUN_140047350(undefined4 * param_1, undefined4 * param_2)

undefined4 * FUN_140047350(undefined4 *param_1,undefined4 *param_2)

{
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  param_1[3] = param_2[3];
  FUN_140046f70((undefined8 *)(param_1 + 4),(longlong)(param_2 + 4));
  return param_1;
}


// ==== FUN_1400473a0 @ 1400473a0  undefined FUN_1400473a0(longlong param_1)

void FUN_1400473a0(longlong param_1)

{
  if (*(longlong *)(param_1 + 0x28) != 0) {
    FUN_140046b40(*(longlong *)(param_1 + 0x28),*(longlong *)(param_1 + 0x30));
    operator_delete(*(void **)(param_1 + 0x28));
  }
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined8 *)(param_1 + 0x38) = 0;
  operator_delete(*(void **)(param_1 + 0x10));
  return;
}


// ==== FUN_140047400 @ 140047400  undefined4 * FUN_140047400(undefined4 * param_1, undefined4 * param_2)

undefined4 * FUN_140047400(undefined4 *param_1,undefined4 *param_2)

{
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  param_1[3] = param_2[3];
  FUN_140047140((longlong *)(param_1 + 4),(longlong *)(param_2 + 4));
  return param_1;
}


// ==== FUN_140047440 @ 140047440  undefined8 * FUN_140047440(undefined8 * param_1, longlong param_2)

undefined8 * FUN_140047440(undefined8 *param_1,longlong param_2)

{
  *param_1 = IAIStrategy::vftable;
  *param_1 = CNeuralAIStrategy::vftable;
  param_1[1] = *(undefined8 *)(param_2 + 8);
  param_1[2] = *(undefined8 *)(param_2 + 0x10);
  *(undefined4 *)(param_1 + 3) = *(undefined4 *)(param_2 + 0x18);
  *(undefined4 *)((longlong)param_1 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
  *(undefined4 *)(param_1 + 4) = *(undefined4 *)(param_2 + 0x20);
  *(undefined4 *)((longlong)param_1 + 0x24) = *(undefined4 *)(param_2 + 0x24);
  FUN_140046f70(param_1 + 5,param_2 + 0x28);
  *(undefined4 *)(param_1 + 0xb) = *(undefined4 *)(param_2 + 0x58);
  return param_1;
}


// ==== FUN_140047500 @ 140047500  longlong FUN_140047500(longlong param_1, longlong param_2)

longlong FUN_140047500(longlong param_1,longlong param_2)

{
  *(undefined8 *)(param_1 + 8) = *(undefined8 *)(param_2 + 8);
  *(undefined8 *)(param_1 + 0x10) = *(undefined8 *)(param_2 + 0x10);
  *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_2 + 0x18);
  *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_2 + 0x20);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_2 + 0x24);
  FUN_140047140((longlong *)(param_1 + 0x28),(longlong *)(param_2 + 0x28));
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_2 + 0x58);
  return param_1;
}


// ==== FUN_140047560 @ 140047560  undefined FUN_140047560(longlong param_1, longlong param_2)

void FUN_140047560(longlong param_1,longlong param_2)

{
  undefined **local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  longlong local_40 [6];
  undefined4 local_10;
  
  if (param_1 != param_2) {
    local_68 = CNeuralAIStrategy::vftable;
    local_60 = *(undefined8 *)(param_1 + 8);
    local_58 = *(undefined8 *)(param_1 + 0x10);
    local_50 = *(undefined4 *)(param_1 + 0x18);
    local_4c = *(undefined4 *)(param_1 + 0x1c);
    local_48 = *(undefined4 *)(param_1 + 0x20);
    local_44 = *(undefined4 *)(param_1 + 0x24);
    FUN_140046f70(local_40,param_1 + 0x28);
    local_10 = *(undefined4 *)(param_1 + 0x58);
    *(undefined8 *)(param_1 + 8) = *(undefined8 *)(param_2 + 8);
    *(undefined8 *)(param_1 + 0x10) = *(undefined8 *)(param_2 + 0x10);
    *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_2 + 0x18);
    *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_2 + 0x1c);
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_2 + 0x20);
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_2 + 0x24);
    FUN_140047140((longlong *)(param_1 + 0x28),(longlong *)(param_2 + 0x28));
    *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_2 + 0x58);
    *(undefined8 *)(param_2 + 8) = local_60;
    *(undefined8 *)(param_2 + 0x10) = local_58;
    *(undefined4 *)(param_2 + 0x18) = local_50;
    *(undefined4 *)(param_2 + 0x1c) = local_4c;
    *(undefined4 *)(param_2 + 0x20) = local_48;
    *(undefined4 *)(param_2 + 0x24) = local_44;
    FUN_140047140((longlong *)(param_2 + 0x28),local_40);
    *(undefined4 *)(param_2 + 0x58) = local_10;
    FUN_140067730(&local_68);
  }
  return;
}


// ==== FUN_1400476a0 @ 1400476a0  undefined FUN_1400476a0(longlong param_1)

void FUN_1400476a0(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  longlong *plVar4;
  double *pdVar5;
  ulonglong uVar6;
  double *pdVar7;
  int iVar8;
  longlong *plVar9;
  longlong *plVar10;
  longlong *plVar11;
  longlong *plVar12;
  longlong *plVar13;
  undefined8 *puVar14;
  longlong lVar15;
  undefined8 *puVar16;
  double *pdVar17;
  longlong lVar18;
  longlong lVar19;
  bool bVar20;
  double dVar21;
  double dVar22;
  undefined4 uVar23;
  undefined4 uVar24;
  undefined4 uVar25;
  undefined4 uVar26;
  double local_res20;
  undefined8 local_2f8;
  undefined8 uStack_2f0;
  longlong *local_2e8 [3];
  longlong *local_2d0;
  longlong *local_2c8;
  longlong local_2c0;
  longlong local_2b8;
  longlong *local_2b0;
  undefined8 local_2a8;
  undefined8 uStack_2a0;
  longlong local_298;
  longlong *local_290;
  longlong *local_288 [3];
  double *local_270;
  double *local_268;
  longlong local_260;
  undefined4 local_258;
  undefined4 uStack_254;
  undefined8 uStack_250;
  undefined8 local_248;
  undefined8 uStack_240;
  undefined4 local_238;
  undefined4 uStack_234;
  undefined4 uStack_230;
  undefined4 uStack_22c;
  longlong *local_228;
  longlong *local_218;
  longlong *plStack_210;
  longlong local_208;
  longlong *local_200;
  longlong *local_1f8;
  longlong *plStack_1f0;
  longlong *local_1e8 [3];
  void *local_1d0;
  undefined8 local_1c8;
  undefined8 local_1c0;
  longlong *local_1b8 [3];
  void *local_1a0;
  undefined8 local_198;
  undefined8 local_190;
  longlong *local_188;
  undefined4 local_178;
  undefined4 uStack_174;
  undefined4 uStack_170;
  undefined4 uStack_16c;
  undefined8 local_168;
  undefined8 uStack_160;
  undefined4 local_158;
  undefined4 uStack_154;
  undefined4 uStack_150;
  undefined4 uStack_14c;
  undefined8 local_148;
  undefined8 uStack_140;
  undefined8 local_138;
  undefined8 uStack_130;
  undefined8 local_128;
  undefined8 uStack_120;
  undefined8 local_118;
  longlong *local_108;
  double *pdStack_100;
  longlong *local_f8;
  longlong *plStack_f0;
  void *local_e8 [3];
  void *local_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  longlong *local_b8;
  longlong *plStack_b0;
  void *local_a8 [3];
  void *local_90;
  undefined8 local_88;
  undefined8 local_80;
  
  local_118 = 0xfffffffffffffffe;
  plVar1 = (longlong *)(param_1 + 0x68);
  plVar9 = *(longlong **)(param_1 + 0x80);
  if (*(longlong **)(param_1 + 0x88) < plVar9) {
    _invalid_parameter_noinfo();
  }
  plVar13 = (longlong *)*plVar1;
  local_248 = plVar13;
  while( true ) {
    plVar11 = (longlong *)0x0;
    plVar12 = *(longlong **)(param_1 + 0x88);
    uStack_240 = plVar9;
    if (plVar12 < *(longlong **)(param_1 + 0x80)) {
      _invalid_parameter_noinfo();
    }
    if ((plVar13 == (longlong *)0x0) || (plVar13 != (longlong *)*plVar1)) {
      _invalid_parameter_noinfo();
    }
    if (plVar9 == plVar12) break;
    local_2f8 = local_248;
    uStack_2f0 = (double *)uStack_240;
    if (plVar13 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      plVar12 = plVar11;
    }
    else {
      plVar12 = (longlong *)*plVar13;
    }
    plVar10 = plVar9 + 2;
    if ((longlong *)plVar12[4] < plVar10) {
LAB_14004776a:
      _invalid_parameter_noinfo();
    }
    else {
      if (plVar13 != (longlong *)0x0) {
        plVar11 = (longlong *)*plVar13;
      }
      if (plVar10 < (longlong *)plVar11[3]) goto LAB_14004776a;
    }
    plVar12 = local_2f8;
    local_218 = local_2f8;
    plVar11 = plVar10;
    uStack_2f0 = (double *)plVar10;
    plStack_210 = plVar10;
    while( true ) {
      lVar19 = 0;
      plVar3 = *(longlong **)(param_1 + 0x88);
      if (plVar3 < *(longlong **)(param_1 + 0x80)) {
        _invalid_parameter_noinfo();
      }
      if ((plVar12 == (longlong *)0x0) || (plVar12 != (longlong *)*plVar1)) {
        _invalid_parameter_noinfo();
      }
      if (plVar11 == plVar3) break;
      if (plVar13 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
      }
      else {
        lVar19 = *plVar13;
      }
      if (*(longlong **)(lVar19 + 0x20) <= plVar9) {
        _invalid_parameter_noinfo();
      }
      plVar3 = (longlong *)*plVar9;
      if (plVar12 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar19 = 0;
      }
      else {
        lVar19 = *plVar12;
      }
      if (*(longlong **)(lVar19 + 0x20) <= plVar11) {
        _invalid_parameter_noinfo();
      }
      plVar4 = (longlong *)*plVar11;
      dVar21 = (double)(**(code **)(*plVar3 + 8))(plVar3);
      dVar22 = (double)(**(code **)(*plVar4 + 8))(plVar4);
      if (dVar21 < dVar22) {
        if (plVar12 == (longlong *)0x0) {
          _invalid_parameter_noinfo();
          lVar19 = 0;
        }
        else {
          lVar19 = *plVar12;
        }
        if (*(longlong **)(lVar19 + 0x20) <= plVar11) {
          _invalid_parameter_noinfo();
        }
        lVar19 = *plVar11;
        if (plVar13 == (longlong *)0x0) {
          _invalid_parameter_noinfo();
          lVar15 = 0;
        }
        else {
          lVar15 = *plVar13;
        }
        if (*(longlong **)(lVar15 + 0x20) <= plVar9) {
          _invalid_parameter_noinfo();
        }
        FUN_140047560(*plVar9,lVar19);
      }
      if (plVar12 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar19 = 0;
      }
      else {
        lVar19 = *plVar12;
      }
      if (*(longlong **)(lVar19 + 0x20) <= plVar11) {
        _invalid_parameter_noinfo();
      }
      plVar11 = plVar11 + 2;
    }
    if (plVar13 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
    }
    else {
      lVar19 = *plVar13;
    }
    bVar20 = *(longlong **)(lVar19 + 0x20) <= plVar9;
    plVar9 = plVar10;
    if (bVar20) {
      _invalid_parameter_noinfo();
    }
  }
  local_res20 = 0.0;
  plVar9 = (longlong *)operator_new(8);
  local_288[0] = plVar11;
  if (plVar9 != (longlong *)0x0) {
    *plVar9 = (longlong)local_288;
    local_288[0] = plVar9;
  }
  local_270 = (double *)0x0;
  local_268 = (double *)0x0;
  local_260 = 0;
  pdVar17 = *(double **)(param_1 + 0x80);
  if (*(double **)(param_1 + 0x88) < pdVar17) {
    _invalid_parameter_noinfo();
  }
  plVar9 = (longlong *)*plVar1;
  local_2f8._0_4_ = SUB84(plVar9,0);
  local_2f8._4_4_ = (undefined4)((ulonglong)plVar9 >> 0x20);
  uStack_2f0._0_4_ = SUB84(pdVar17,0);
  uStack_2f0._4_4_ = (undefined4)((ulonglong)pdVar17 >> 0x20);
  local_238 = (undefined4)local_2f8;
  uStack_234 = local_2f8._4_4_;
  uStack_230 = (undefined4)uStack_2f0;
  uStack_22c = uStack_2f0._4_4_;
  local_2f8 = plVar9;
  uStack_2f0 = pdVar17;
  while( true ) {
    pdVar5 = *(double **)(param_1 + 0x88);
    if (pdVar5 < *(double **)(param_1 + 0x80)) {
      _invalid_parameter_noinfo();
    }
    if ((plVar9 == (longlong *)0x0) || (plVar9 != (longlong *)*plVar1)) {
      _invalid_parameter_noinfo();
    }
    if (pdVar17 == pdVar5) break;
    if (plVar9 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      plVar13 = plVar11;
    }
    else {
      plVar13 = (longlong *)*plVar9;
    }
    if ((double *)plVar13[4] <= pdVar17) {
      _invalid_parameter_noinfo();
    }
    dVar21 = (double)(**(code **)(*(longlong *)*pdVar17 + 8))();
    pdVar5 = local_268;
    local_res20 = local_res20 + dVar21;
    plVar13 = plVar11;
    if (local_270 != (double *)0x0) {
      plVar13 = (longlong *)(local_260 - (longlong)local_270 >> 3);
    }
    if ((longlong *)((longlong)local_268 - (longlong)local_270 >> 3) < plVar13) {
      *local_268 = local_res20;
      local_268 = local_268 + 1;
    }
    else {
      if (local_268 < local_270) {
        _invalid_parameter_noinfo();
      }
      pdVar7 = local_270;
      plVar13 = local_288[0];
      local_2f8 = local_288[0];
      uStack_2f0 = pdVar5;
      plVar12 = plVar11;
      if (((longlong)local_268 - (longlong)local_270 & 0xfffffffffffffff8U) != 0) {
        if (local_268 < local_270) {
          _invalid_parameter_noinfo();
        }
        if ((plVar13 == (longlong *)0x0) || (plVar13 != local_288[0])) {
          _invalid_parameter_noinfo();
        }
        plVar12 = (longlong *)((longlong)pdVar5 - (longlong)pdVar7 >> 3);
      }
      local_108 = local_2f8;
      pdStack_100 = uStack_2f0;
      FUN_140043b40((longlong)local_288,(longlong)&local_108,1,&local_res20);
      pdVar5 = local_270;
      if (local_268 < local_270) {
        _invalid_parameter_noinfo();
      }
      plVar13 = local_288[0];
      if (local_288[0] == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        plVar10 = plVar11;
      }
      else {
        plVar10 = (longlong *)*local_288[0];
      }
      if (pdVar5 + (longlong)plVar12 <= (double *)plVar10[4]) {
        plVar10 = plVar11;
        if (plVar13 != (longlong *)0x0) {
          plVar10 = (longlong *)*plVar13;
        }
        if ((double *)plVar10[3] <= pdVar5 + (longlong)plVar12) goto LAB_140047b18;
      }
      _invalid_parameter_noinfo();
    }
LAB_140047b18:
    if (plVar9 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      plVar13 = plVar11;
    }
    else {
      plVar13 = (longlong *)*plVar9;
    }
    if ((double *)plVar13[4] <= pdVar17) {
      _invalid_parameter_noinfo();
    }
    pdVar17 = pdVar17 + 2;
  }
  plVar9 = (longlong *)operator_new(8);
  if (plVar9 != (longlong *)0x0) {
    *plVar9 = (longlong)local_2e8;
    plVar11 = plVar9;
  }
  local_2d0 = (longlong *)0x0;
  local_2c8 = (longlong *)0x0;
  local_2c0 = 0;
  local_2e8[0] = plVar11;
  do {
    pdVar17 = local_270;
    local_2b0 = (longlong *)0x0;
    local_2b8 = 0;
    if (local_268 < local_270) {
      _invalid_parameter_noinfo();
    }
    local_168 = local_288[0];
    plVar9 = local_168;
    uStack_160 = pdVar17;
    local_168._0_4_ = SUB84(local_288[0],0);
    uVar23 = (undefined4)local_168;
    local_168._4_4_ = (undefined4)((ulonglong)local_288[0] >> 0x20);
    uVar24 = local_168._4_4_;
    uStack_160._0_4_ = SUB84(pdVar17,0);
    uVar25 = (undefined4)uStack_160;
    uStack_160._4_4_ = (undefined4)((ulonglong)pdVar17 >> 0x20);
    uVar26 = uStack_160._4_4_;
    local_258 = (undefined4)local_168;
    uStack_254 = local_168._4_4_;
    uStack_250 = pdVar17;
    local_168 = plVar9;
    uStack_160 = pdVar17;
    iVar8 = rand();
    dVar21 = (double)iVar8 * 3.0517578125e-05 * local_res20;
    plVar9 = *(longlong **)(param_1 + 0x80);
    if (*(longlong **)(param_1 + 0x88) < plVar9) {
      _invalid_parameter_noinfo();
    }
    plVar13 = (longlong *)*plVar1;
    local_138._0_4_ = SUB84(plVar13,0);
    local_138._4_4_ = (undefined4)((ulonglong)plVar13 >> 0x20);
    uStack_130._0_4_ = SUB84(plVar9,0);
    uStack_130._4_4_ = (undefined4)((ulonglong)plVar9 >> 0x20);
    local_238 = (undefined4)local_138;
    uStack_234 = local_138._4_4_;
    uStack_230 = (undefined4)uStack_130;
    uStack_22c = uStack_130._4_4_;
    plVar12 = (longlong *)CONCAT44(uStack_254,local_258);
    pdVar17 = uStack_250;
    local_138 = plVar13;
    uStack_130 = plVar9;
    while( true ) {
      plVar11 = *(longlong **)(param_1 + 0x88);
      if (plVar11 < *(longlong **)(param_1 + 0x80)) {
        _invalid_parameter_noinfo();
      }
      if ((plVar13 == (longlong *)0x0) || (plVar13 != (longlong *)*plVar1)) {
        _invalid_parameter_noinfo();
      }
      pdVar5 = local_268;
      if (plVar9 == plVar11) goto LAB_140047dc2;
      if (local_268 < local_270) {
        _invalid_parameter_noinfo();
      }
      if ((plVar12 == (longlong *)0x0) || (plVar12 != local_288[0])) {
        _invalid_parameter_noinfo();
      }
      if (pdVar17 == pdVar5) goto LAB_140047dc2;
      local_178 = uVar23;
      uStack_174 = uVar24;
      uStack_170 = uVar25;
      uStack_16c = uVar26;
      if (plVar12 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar19 = 0;
      }
      else {
        lVar19 = *plVar12;
      }
      if (*(double **)(lVar19 + 0x20) <= pdVar17) {
        _invalid_parameter_noinfo();
      }
      pdVar17 = pdVar17 + 1;
      uStack_250 = pdVar17;
      if ((longlong *)CONCAT44(uStack_174,local_178) == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar19 = 0;
      }
      else {
        lVar19 = *(longlong *)CONCAT44(uStack_174,local_178);
      }
      pdVar5 = (double *)CONCAT44(uStack_16c,uStack_170);
      if (*(double **)(lVar19 + 0x20) <= pdVar5) {
        _invalid_parameter_noinfo();
      }
      if (dVar21 <= *pdVar5) break;
      if (plVar13 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar19 = 0;
      }
      else {
        lVar19 = *plVar13;
      }
      if (*(longlong **)(lVar19 + 0x20) <= plVar9) {
        _invalid_parameter_noinfo();
      }
      plVar9 = plVar9 + 2;
      uVar23 = local_258;
      uVar24 = uStack_254;
      uVar25 = (undefined4)uStack_250;
      uVar26 = uStack_250._4_4_;
    }
    if (plVar13 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar19 = 0;
    }
    else {
      lVar19 = *plVar13;
    }
    if (*(longlong **)(lVar19 + 0x20) <= plVar9) {
      _invalid_parameter_noinfo();
    }
    local_2b0 = (longlong *)plVar9[1];
    local_2b8 = *plVar9;
    if (local_2b0 != (longlong *)0x0) {
      LOCK();
      *(int *)(local_2b0 + 2) = (int)local_2b0[2] + 1;
      UNLOCK();
    }
    lVar19 = local_2b8;
    plVar9 = local_2b0;
    if (local_2b8 == 0) {
LAB_140047dc2:
      plVar12 = (longlong *)FUN_140042480(plVar1);
      plVar13 = local_2b0;
      plVar9 = (longlong *)plVar12[1];
      lVar19 = *plVar12;
      if (plVar9 != (longlong *)0x0) {
        LOCK();
        *(int *)(plVar9 + 2) = (int)plVar9[2] + 1;
        UNLOCK();
      }
      if (local_2b0 != (longlong *)0x0) {
        LOCK();
        plVar12 = local_2b0 + 2;
        *(int *)plVar12 = (int)*plVar12 + -1;
        UNLOCK();
        if ((int)*plVar12 == 0) {
          (**(code **)*local_2b0)(local_2b0);
          LOCK();
          piVar2 = (int *)((longlong)plVar13 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*local_2b0 + 8))();
          }
        }
      }
    }
    local_2b0 = plVar9;
    local_2b8 = lVar19;
    local_290 = (longlong *)0x0;
    local_298 = 0;
    iVar8 = rand();
    pdVar17 = local_270;
    dVar21 = (double)iVar8 * 3.0517578125e-05 * local_res20;
    if (local_268 < local_270) {
      _invalid_parameter_noinfo();
    }
    local_148 = local_288[0];
    plVar13 = local_148;
    uStack_140 = pdVar17;
    local_148._0_4_ = SUB84(local_288[0],0);
    uVar23 = (undefined4)local_148;
    local_148._4_4_ = (undefined4)((ulonglong)local_288[0] >> 0x20);
    uVar24 = local_148._4_4_;
    uStack_140._0_4_ = SUB84(pdVar17,0);
    uVar25 = (undefined4)uStack_140;
    uStack_140._4_4_ = (undefined4)((ulonglong)pdVar17 >> 0x20);
    uVar26 = uStack_140._4_4_;
    local_258 = (undefined4)local_148;
    uStack_254 = local_148._4_4_;
    uStack_250 = pdVar17;
    plVar9 = *(longlong **)(param_1 + 0x80);
    local_148 = plVar13;
    uStack_140 = pdVar17;
    if (*(longlong **)(param_1 + 0x88) < plVar9) {
      _invalid_parameter_noinfo();
    }
    plVar13 = (longlong *)*plVar1;
    local_128._0_4_ = SUB84(plVar13,0);
    local_128._4_4_ = (undefined4)((ulonglong)plVar13 >> 0x20);
    uStack_120._0_4_ = SUB84(plVar9,0);
    uStack_120._4_4_ = (undefined4)((ulonglong)plVar9 >> 0x20);
    local_238 = (undefined4)local_128;
    uStack_234 = local_128._4_4_;
    uStack_230 = (undefined4)uStack_120;
    uStack_22c = uStack_120._4_4_;
    plVar12 = (longlong *)CONCAT44(uStack_254,local_258);
    pdVar17 = uStack_250;
    local_128 = plVar13;
    uStack_120 = plVar9;
    while( true ) {
      plVar11 = *(longlong **)(param_1 + 0x88);
      if (plVar11 < *(longlong **)(param_1 + 0x80)) {
        _invalid_parameter_noinfo();
      }
      if ((plVar13 == (longlong *)0x0) || (plVar13 != (longlong *)*plVar1)) {
        _invalid_parameter_noinfo();
      }
      pdVar5 = local_268;
      if (plVar9 == plVar11) goto LAB_140048035;
      if (local_268 < local_270) {
        _invalid_parameter_noinfo();
      }
      if ((plVar12 == (longlong *)0x0) || (plVar12 != local_288[0])) {
        _invalid_parameter_noinfo();
      }
      if (pdVar17 == pdVar5) goto LAB_140048035;
      local_158 = uVar23;
      uStack_154 = uVar24;
      uStack_150 = uVar25;
      uStack_14c = uVar26;
      if (plVar12 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar19 = 0;
      }
      else {
        lVar19 = *plVar12;
      }
      if (*(double **)(lVar19 + 0x20) <= pdVar17) {
        _invalid_parameter_noinfo();
      }
      pdVar17 = pdVar17 + 1;
      uStack_250 = pdVar17;
      if ((longlong *)CONCAT44(uStack_154,local_158) == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar19 = 0;
      }
      else {
        lVar19 = *(longlong *)CONCAT44(uStack_154,local_158);
      }
      pdVar5 = (double *)CONCAT44(uStack_14c,uStack_150);
      if (*(double **)(lVar19 + 0x20) <= pdVar5) {
        _invalid_parameter_noinfo();
      }
      if (dVar21 <= *pdVar5) break;
      if (plVar13 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar19 = 0;
      }
      else {
        lVar19 = *plVar13;
      }
      if (*(longlong **)(lVar19 + 0x20) <= plVar9) {
        _invalid_parameter_noinfo();
      }
      plVar9 = plVar9 + 2;
      uVar23 = local_258;
      uVar24 = uStack_254;
      uVar25 = (undefined4)uStack_250;
      uVar26 = uStack_250._4_4_;
    }
    if (plVar13 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar19 = 0;
    }
    else {
      lVar19 = *plVar13;
    }
    if (*(longlong **)(lVar19 + 0x20) <= plVar9) {
      _invalid_parameter_noinfo();
    }
    local_290 = (longlong *)plVar9[1];
    lVar19 = *plVar9;
    if (local_290 != (longlong *)0x0) {
      LOCK();
      *(int *)(local_290 + 2) = (int)local_290[2] + 1;
      UNLOCK();
    }
    local_298 = lVar19;
    plVar9 = local_290;
    if (lVar19 == 0) {
LAB_140048035:
      plVar12 = (longlong *)FUN_140042480(plVar1);
      plVar13 = local_290;
      plVar9 = (longlong *)plVar12[1];
      lVar19 = *plVar12;
      if (plVar9 != (longlong *)0x0) {
        LOCK();
        *(int *)(plVar9 + 2) = (int)plVar9[2] + 1;
        UNLOCK();
      }
      if (local_290 != (longlong *)0x0) {
        LOCK();
        plVar12 = local_290 + 2;
        *(int *)plVar12 = (int)*plVar12 + -1;
        UNLOCK();
        if ((int)*plVar12 == 0) {
          (**(code **)*local_290)(local_290);
          LOCK();
          piVar2 = (int *)((longlong)plVar13 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*local_290 + 8))();
          }
        }
      }
    }
    local_290 = plVar9;
    local_298 = lVar19;
    local_228 = (longlong *)operator_new(8);
    if (local_228 == (longlong *)0x0) {
      local_1e8[0] = (longlong *)0x0;
    }
    else {
      *local_228 = (longlong)local_1e8;
      local_1e8[0] = local_228;
    }
    plVar9 = (longlong *)0x0;
    local_1d0 = (void *)0x0;
    local_1c8 = 0;
    local_1c0 = 0;
    local_188 = local_228;
    local_228 = (longlong *)operator_new(8);
    local_1b8[0] = plVar9;
    if (local_228 != (longlong *)0x0) {
      *local_228 = (longlong)local_1b8;
      local_1b8[0] = local_228;
    }
    local_1a0 = (void *)0x0;
    local_198 = 0;
    local_190 = 0;
    local_188 = local_228;
    plVar13 = FUN_1400672f0(local_2b8,(longlong *)local_a8);
    plVar12 = FUN_1400672f0(lVar19,(longlong *)local_e8);
    FUN_140044c20(param_1,plVar12,plVar13,(longlong *)local_1e8,(longlong *)local_1b8);
    if (local_d0 != (void *)0x0) {
      operator_delete(local_d0);
    }
    local_d0 = (void *)0x0;
    local_c8 = 0;
    local_c0 = 0;
    operator_delete(local_e8[0]);
    if (local_90 != (void *)0x0) {
      operator_delete(local_90);
    }
    local_90 = (void *)0x0;
    local_88 = 0;
    local_80 = 0;
    operator_delete(local_a8[0]);
    FUN_1400435c0(param_1,(longlong *)local_1e8);
    FUN_1400435c0(param_1,(longlong *)local_1b8);
    local_228 = (longlong *)operator_new(0x60);
    plVar13 = plVar9;
    if (local_228 != (undefined8 *)0x0) {
      plVar13 = FUN_1400676a0(local_228,(longlong)local_1e8);
    }
    local_208 = 0;
    local_200 = (longlong *)0x0;
    FUN_140041b60(&local_208,plVar13);
    plVar13 = local_2c8;
    if (local_2d0 != (longlong *)0x0) {
      plVar9 = (longlong *)(local_2c0 - (longlong)local_2d0 >> 4);
    }
    if ((longlong *)((longlong)local_2c8 - (longlong)local_2d0 >> 4) < plVar9) {
      FUN_140043ee0(local_2c8,1,&local_208);
      local_2c8 = plVar13 + 2;
    }
    else {
      if (local_2c8 < local_2d0) {
        _invalid_parameter_noinfo();
      }
      plVar12 = local_2d0;
      plVar9 = local_2e8[0];
      local_1f8 = local_2e8[0];
      plStack_1f0 = plVar13;
      if (((longlong)local_2c8 - (longlong)local_2d0 & 0xfffffffffffffff0U) == 0) {
        lVar19 = 0;
      }
      else {
        if (local_2c8 < local_2d0) {
          _invalid_parameter_noinfo();
        }
        if ((plVar9 == (longlong *)0x0) || (plVar9 != local_2e8[0])) {
          _invalid_parameter_noinfo();
        }
        lVar19 = (longlong)plVar13 - (longlong)plVar12 >> 4;
      }
      lVar15 = 0;
      local_f8 = local_1f8;
      plStack_f0 = plStack_1f0;
      FUN_140044e70((longlong)local_2e8,(longlong)&local_f8,1,&local_208);
      plVar9 = local_2d0;
      if (local_2c8 < local_2d0) {
        _invalid_parameter_noinfo();
      }
      plVar13 = local_2e8[0];
      if (local_2e8[0] == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar18 = lVar15;
      }
      else {
        lVar18 = *local_2e8[0];
      }
      if (plVar9 + lVar19 * 2 <= *(longlong **)(lVar18 + 0x20)) {
        if (plVar13 != (longlong *)0x0) {
          lVar15 = *plVar13;
        }
        if (*(longlong **)(lVar15 + 0x18) <= plVar9 + lVar19 * 2) goto LAB_1400483c2;
      }
      _invalid_parameter_noinfo();
    }
LAB_1400483c2:
    plVar9 = local_200;
    puVar16 = (undefined8 *)0x0;
    if (local_200 != (longlong *)0x0) {
      LOCK();
      plVar13 = local_200 + 2;
      *(int *)plVar13 = (int)*plVar13 + -1;
      UNLOCK();
      if ((int)*plVar13 == 0) {
        (**(code **)*local_200)(local_200);
        LOCK();
        piVar2 = (int *)((longlong)plVar9 + 0x14);
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (*piVar2 == 0) {
          (**(code **)(*local_200 + 8))();
        }
      }
    }
    local_228 = (longlong *)operator_new(0x60);
    puVar14 = puVar16;
    if (local_228 != (undefined8 *)0x0) {
      puVar14 = FUN_1400676a0(local_228,(longlong)local_1b8);
    }
    local_2f8 = (longlong *)0x0;
    uStack_2f0 = (double *)0x0;
    FUN_140041b60(&local_2f8,puVar14);
    plVar9 = local_2c8;
    if (local_2d0 != (longlong *)0x0) {
      puVar16 = (undefined8 *)(local_2c0 - (longlong)local_2d0 >> 4);
    }
    if ((undefined8 *)((longlong)local_2c8 - (longlong)local_2d0 >> 4) < puVar16) {
      FUN_140043ee0(local_2c8,1,&local_2f8);
      local_2c8 = plVar9 + 2;
    }
    else {
      if (local_2c8 < local_2d0) {
        _invalid_parameter_noinfo();
      }
      plVar12 = local_2d0;
      plVar13 = local_2e8[0];
      local_2a8 = local_2e8[0];
      uStack_2a0 = plVar9;
      if (((longlong)local_2c8 - (longlong)local_2d0 & 0xfffffffffffffff0U) == 0) {
        lVar19 = 0;
      }
      else {
        if (local_2c8 < local_2d0) {
          _invalid_parameter_noinfo();
        }
        if ((plVar13 == (longlong *)0x0) || (plVar13 != local_2e8[0])) {
          _invalid_parameter_noinfo();
        }
        lVar19 = (longlong)plVar9 - (longlong)plVar12 >> 4;
      }
      lVar15 = 0;
      local_b8 = local_2a8;
      plStack_b0 = uStack_2a0;
      FUN_140044e70((longlong)local_2e8,(longlong)&local_b8,1,&local_2f8);
      plVar9 = local_2d0;
      if (local_2c8 < local_2d0) {
        _invalid_parameter_noinfo();
      }
      plVar13 = local_2e8[0];
      if (local_2e8[0] == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar18 = lVar15;
      }
      else {
        lVar18 = *local_2e8[0];
      }
      if (plVar9 + lVar19 * 2 <= *(longlong **)(lVar18 + 0x20)) {
        if (plVar13 != (longlong *)0x0) {
          lVar15 = *plVar13;
        }
        if (*(longlong **)(lVar15 + 0x18) <= plVar9 + lVar19 * 2) goto LAB_140048593;
      }
      _invalid_parameter_noinfo();
    }
LAB_140048593:
    pdVar17 = uStack_2f0;
    if (uStack_2f0 != (double *)0x0) {
      LOCK();
      pdVar5 = uStack_2f0 + 2;
      *(int *)pdVar5 = *(int *)pdVar5 + -1;
      UNLOCK();
      if (*(int *)pdVar5 == 0) {
        (**(code **)*uStack_2f0)(uStack_2f0);
        LOCK();
        piVar2 = (int *)((longlong)pdVar17 + 0x14);
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (*piVar2 == 0) {
          (**(code **)((longlong)*uStack_2f0 + 8))();
        }
      }
    }
    if (local_1a0 != (void *)0x0) {
      operator_delete(local_1a0);
    }
    local_1a0 = (void *)0x0;
    local_198 = 0;
    local_190 = 0;
    operator_delete(local_1b8[0]);
    if (local_1d0 != (void *)0x0) {
      operator_delete(local_1d0);
    }
    local_1d0 = (void *)0x0;
    local_1c8 = 0;
    local_1c0 = 0;
    operator_delete(local_1e8[0]);
    plVar9 = local_290;
    if (local_290 != (longlong *)0x0) {
      LOCK();
      plVar13 = local_290 + 2;
      *(int *)plVar13 = (int)*plVar13 + -1;
      UNLOCK();
      if ((int)*plVar13 == 0) {
        (**(code **)*local_290)(local_290);
        LOCK();
        piVar2 = (int *)((longlong)plVar9 + 0x14);
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (*piVar2 == 0) {
          (**(code **)(*local_290 + 8))();
        }
      }
    }
    plVar9 = local_2b0;
    if (local_2b0 != (longlong *)0x0) {
      LOCK();
      plVar13 = local_2b0 + 2;
      *(int *)plVar13 = (int)*plVar13 + -1;
      UNLOCK();
      if ((int)*plVar13 == 0) {
        (**(code **)*local_2b0)(local_2b0);
        LOCK();
        piVar2 = (int *)((longlong)plVar9 + 0x14);
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (*piVar2 == 0) {
          (**(code **)(*local_2b0 + 8))();
        }
      }
    }
    plVar9 = local_2d0;
  } while ((ulonglong)((longlong)local_2c8 - (longlong)local_2d0 >> 4) < 0x3c);
  lVar19 = 0;
  if (local_2c8 < local_2d0) {
    _invalid_parameter_noinfo();
  }
  local_2a8 = local_2e8[0];
  plVar13 = local_2a8;
  uStack_2a0 = plVar9;
  local_2a8._0_4_ = SUB84(local_2e8[0],0);
  uVar23 = (undefined4)local_2a8;
  local_2a8._4_4_ = (undefined4)((ulonglong)local_2e8[0] >> 0x20);
  uVar24 = local_2a8._4_4_;
  uStack_2a0._0_4_ = SUB84(plVar9,0);
  uVar25 = (undefined4)uStack_2a0;
  uStack_2a0._4_4_ = (undefined4)((ulonglong)plVar9 >> 0x20);
  uVar26 = uStack_2a0._4_4_;
  local_248 = local_2e8[0];
  uStack_240 = plVar9;
  uVar6 = *(ulonglong *)(param_1 + 0x80);
  if (*(ulonglong *)(param_1 + 0x88) < uVar6) {
    local_2a8 = plVar13;
    uStack_2a0 = plVar9;
    _invalid_parameter_noinfo();
  }
  plVar9 = (longlong *)*plVar1;
  local_2a8 = plVar9;
  uStack_2a0 = (longlong *)uVar6;
  if (plVar9 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar15 = lVar19;
  }
  else {
    lVar15 = *plVar9;
  }
  plVar13 = (longlong *)(uVar6 + 0x40);
  if (plVar13 <= *(longlong **)(lVar15 + 0x20)) {
    if (plVar9 != (longlong *)0x0) {
      lVar19 = *plVar9;
    }
    if (*(longlong **)(lVar19 + 0x18) <= plVar13) goto LAB_140048757;
  }
  _invalid_parameter_noinfo();
LAB_140048757:
  plVar12 = local_248;
  plVar9 = local_2a8;
  local_218 = local_2a8;
  plVar11 = uStack_240;
  uStack_2a0 = plVar13;
  plStack_210 = plVar13;
  while( true ) {
    plVar4 = plStack_210;
    plVar3 = local_218;
    plVar10 = local_2c8;
    if (local_2c8 < local_2d0) {
      _invalid_parameter_noinfo();
    }
    if ((plVar12 == (longlong *)0x0) || (plVar12 != local_2e8[0])) {
      _invalid_parameter_noinfo();
    }
    if (plVar11 == plVar10) break;
    plVar10 = *(longlong **)(param_1 + 0x88);
    if (plVar10 < *(longlong **)(param_1 + 0x80)) {
      _invalid_parameter_noinfo();
    }
    if ((plVar9 == (longlong *)0x0) || (plVar9 != (longlong *)*plVar1)) {
      _invalid_parameter_noinfo();
    }
    if (plVar13 == plVar10) break;
    local_2a8 = (longlong *)CONCAT44(uVar24,uVar23);
    uStack_2a0 = (longlong *)CONCAT44(uVar26,uVar25);
    if (plVar12 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar19 = 0;
    }
    else {
      lVar19 = *plVar12;
    }
    if (*(longlong **)(lVar19 + 0x20) <= plVar11) {
      _invalid_parameter_noinfo();
    }
    plVar11 = plVar11 + 2;
    uStack_240 = plVar11;
    if (local_2a8 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar19 = 0;
    }
    else {
      lVar19 = *local_2a8;
    }
    plVar10 = uStack_2a0;
    if (*(longlong **)(lVar19 + 0x20) <= uStack_2a0) {
      _invalid_parameter_noinfo();
    }
    lVar19 = *plVar10;
    local_1f8 = plVar3;
    plStack_1f0 = plVar4;
    if (plVar9 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar15 = 0;
    }
    else {
      lVar15 = *plVar9;
    }
    if (*(longlong **)(lVar15 + 0x20) <= plVar13) {
      _invalid_parameter_noinfo();
    }
    plVar13 = plVar13 + 2;
    plStack_210 = plVar13;
    if (local_1f8 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar15 = 0;
    }
    else {
      lVar15 = *local_1f8;
    }
    plVar10 = plStack_1f0;
    if (*(longlong **)(lVar15 + 0x20) <= plStack_1f0) {
      _invalid_parameter_noinfo();
    }
    lVar15 = *plVar10;
    *(undefined8 *)(lVar15 + 8) = *(undefined8 *)(lVar19 + 8);
    *(undefined8 *)(lVar15 + 0x10) = *(undefined8 *)(lVar19 + 0x10);
    *(undefined4 *)(lVar15 + 0x18) = *(undefined4 *)(lVar19 + 0x18);
    *(undefined4 *)(lVar15 + 0x1c) = *(undefined4 *)(lVar19 + 0x1c);
    *(undefined4 *)(lVar15 + 0x20) = *(undefined4 *)(lVar19 + 0x20);
    *(undefined4 *)(lVar15 + 0x24) = *(undefined4 *)(lVar19 + 0x24);
    FUN_140047140((longlong *)(lVar15 + 0x28),(longlong *)(lVar19 + 0x28));
    *(undefined4 *)(lVar15 + 0x58) = *(undefined4 *)(lVar19 + 0x58);
    uVar23 = (undefined4)local_248;
    uVar24 = local_248._4_4_;
    uVar25 = (undefined4)uStack_240;
    uVar26 = uStack_240._4_4_;
  }
  if (local_2d0 != (longlong *)0x0) {
    FUN_140044530(local_2d0,local_2c8);
    operator_delete(local_2d0);
  }
  local_2d0 = (longlong *)0x0;
  local_2c8 = (longlong *)0x0;
  local_2c0 = 0;
  operator_delete(local_2e8[0]);
  if (local_270 != (double *)0x0) {
    operator_delete(local_270);
  }
  local_270 = (double *)0x0;
  local_268 = (double *)0x0;
  local_260 = 0;
  operator_delete(local_288[0]);
  return;
}


// ==== FUN_1400489b0 @ 1400489b0  undefined FUN_1400489b0(longlong param_1)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: register */

void FUN_1400489b0(longlong param_1)

{
  undefined8 *puVar1;
  longlong *plVar2;
  longlong *plVar3;
  double dVar4;
  DWORD DVar5;
  DWORD DVar6;
  int iVar7;
  undefined4 uVar8;
  longlong *plVar9;
  undefined8 *puVar10;
  longlong lVar11;
  longlong lVar12;
  
  if ((DAT_140104628 & 1) == 0) {
    DAT_140104628 = DAT_140104628 | 1;
    _DAT_140104624 = timeGetTime();
  }
  if ((DAT_140104628 & 2) == 0) {
    DAT_140104628 = DAT_140104628 | 2;
    _DAT_140104620 = timeGetTime();
  }
  DVar6 = timeGetTime();
  DVar5 = _DAT_140104624;
  if (599999 < DVar6 - _DAT_140104624) {
    lVar12 = 0;
    puVar10 = *(undefined8 **)(param_1 + 0x80);
    if (*(undefined8 **)(param_1 + 0x88) < puVar10) {
      _invalid_parameter_noinfo();
    }
    plVar9 = *(longlong **)(param_1 + 0x68);
    while( true ) {
      puVar1 = *(undefined8 **)(param_1 + 0x88);
      if (puVar1 < *(undefined8 **)(param_1 + 0x80)) {
        _invalid_parameter_noinfo();
      }
      if ((plVar9 == (longlong *)0x0) || (plVar9 != *(longlong **)(param_1 + 0x68))) {
        _invalid_parameter_noinfo();
      }
      if (puVar10 == puVar1) break;
      if (plVar9 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar11 = 0;
      }
      else {
        lVar11 = *plVar9;
      }
      if (*(undefined8 **)(lVar11 + 0x20) <= puVar10) {
        _invalid_parameter_noinfo();
      }
      dVar4 = (double)(**(code **)(*(longlong *)*puVar10 + 8))();
      if (dVar4 <= 2.220446049250313e-16) {
        lVar12 = lVar12 + 1;
      }
      if (plVar9 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar11 = 0;
      }
      else {
        lVar11 = *plVar9;
      }
      if (*(undefined8 **)(lVar11 + 0x20) <= puVar10) {
        _invalid_parameter_noinfo();
      }
      puVar10 = puVar10 + 2;
    }
    DVar5 = DVar6;
    if ((ulonglong)(lVar12 * 8) <
        (ulonglong)(*(longlong *)(param_1 + 0x88) - *(longlong *)(param_1 + 0x80) >> 4)) {
      if (10800000 < DVar6 - _DAT_140104620) {
        FUN_140043700(param_1);
        _DAT_140104620 = DVar6;
      }
      *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
      lVar12 = 0;
      plVar9 = *(longlong **)(param_1 + 0x80);
      if (*(longlong **)(param_1 + 0x88) < plVar9) {
        _invalid_parameter_noinfo();
      }
      plVar2 = *(longlong **)(param_1 + 0x68);
      while( true ) {
        plVar3 = *(longlong **)(param_1 + 0x88);
        if (plVar3 < *(longlong **)(param_1 + 0x80)) {
          _invalid_parameter_noinfo();
        }
        if ((plVar2 == (longlong *)0x0) || (plVar2 != *(longlong **)(param_1 + 0x68))) {
          _invalid_parameter_noinfo();
        }
        if (plVar9 == plVar3) break;
        if (plVar2 == (longlong *)0x0) {
          _invalid_parameter_noinfo();
          lVar11 = 0;
        }
        else {
          lVar11 = *plVar2;
        }
        if (*(longlong **)(lVar11 + 0x20) <= plVar9) {
          _invalid_parameter_noinfo();
        }
        FUN_1400670d0(*plVar9);
        if (plVar2 == (longlong *)0x0) {
          _invalid_parameter_noinfo();
          lVar11 = 0;
        }
        else {
          lVar11 = *plVar2;
        }
        if (*(longlong **)(lVar11 + 0x20) <= plVar9) {
          _invalid_parameter_noinfo();
        }
        iVar7 = FUN_1400670e0(*plVar9);
        if (1 < iVar7) {
          if (plVar2 == (longlong *)0x0) {
            _invalid_parameter_noinfo();
            lVar11 = 0;
          }
          else {
            lVar11 = *plVar2;
          }
          if (*(longlong **)(lVar11 + 0x20) <= plVar9) {
            _invalid_parameter_noinfo();
          }
          plVar3 = (longlong *)*plVar9;
          if (plVar2 == (longlong *)0x0) {
            _invalid_parameter_noinfo();
            lVar11 = 0;
          }
          else {
            lVar11 = *plVar2;
          }
          if (*(longlong **)(lVar11 + 0x20) <= plVar9) {
            _invalid_parameter_noinfo();
          }
          lVar11 = *plVar9;
          (**(code **)(*plVar3 + 8))(plVar3);
          uVar8 = FUN_1400670e0(lVar11);
          tq::SysLogSave("ainpc","Gene[%d]\tGeneration[%d]\tFitness[%d]",lVar12,uVar8);
        }
        if (plVar2 == (longlong *)0x0) {
          _invalid_parameter_noinfo();
          lVar11 = 0;
        }
        else {
          lVar11 = *plVar2;
        }
        if (*(longlong **)(lVar11 + 0x20) <= plVar9) {
          _invalid_parameter_noinfo();
        }
        plVar9 = plVar9 + 2;
        lVar12 = lVar12 + 1;
      }
      tq::SysLogSave("ainpc","Epoch neural AI generation %d",*(undefined4 *)(param_1 + 8));
      FUN_1400476a0(param_1);
      _DAT_140104624 = DVar6;
      log_InlineLogMessage
                ("CAIStrategyMgr::Process() update neural AI generation %d.",
                 *(undefined4 *)(param_1 + 8));
      DVar5 = _DAT_140104624;
    }
  }
  _DAT_140104624 = DVar5;
  return;
}


// ==== FUN_140048d20 @ 140048d20  undefined8 * FUN_140048d20(undefined8 * param_1)

undefined8 * FUN_140048d20(undefined8 *param_1)

{
  FUN_140034920(param_1);
  *param_1 = CMsgLogin::vftable;
  FUN_140034820((longlong)param_1);
  param_1[0x83] = param_1 + 2;
  return param_1;
}


// ==== FUN_140048d70 @ 140048d70  undefined FUN_140048d70(undefined8 * param_1)

void FUN_140048d70(undefined8 *param_1)

{
  *param_1 = CMsgLogin::vftable;
  FUN_140034810(param_1);
  return;
}


// ==== FUN_140048da0 @ 140048da0  undefined8 FUN_140048da0(longlong param_1, undefined4 param_2, char * param_3, char * param_4)

undefined8 FUN_140048da0(longlong param_1,undefined4 param_2,char *param_3,char *param_4)

{
  char cVar1;
  ulonglong uVar2;
  char *pcVar3;
  
  if (param_3 != (char *)0x0) {
    uVar2 = 0xffffffffffffffff;
    pcVar3 = param_3;
    do {
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    if ((~uVar2 - 1 < 0x10) && (param_4 != (char *)0x0)) {
      uVar2 = 0xffffffffffffffff;
      pcVar3 = param_4;
      do {
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        cVar1 = *pcVar3;
        pcVar3 = pcVar3 + 1;
      } while (cVar1 != '\0');
      if (~uVar2 - 1 < 0x10) {
        FUN_140034820(param_1);
        *(undefined4 *)(param_1 + 8) = 0x3ea;
        *(undefined4 *)(param_1 + 0xc) = 0x24;
        **(undefined4 **)(param_1 + 0x418) = param_2;
        pcVar3 = (char *)(*(longlong *)(param_1 + 0x418) + 4);
        do {
          cVar1 = *param_3;
          param_3 = param_3 + 1;
          *pcVar3 = cVar1;
          pcVar3 = pcVar3 + 1;
        } while (cVar1 != '\0');
        pcVar3 = (char *)(*(longlong *)(param_1 + 0x418) + 0x14);
        do {
          cVar1 = *param_4;
          param_4 = param_4 + 1;
          *pcVar3 = cVar1;
          pcVar3 = pcVar3 + 1;
        } while (cVar1 != '\0');
        return 1;
      }
    }
  }
  return 0;
}


// ==== FUN_140048f90 @ 140048f90  undefined FUN_140048f90(undefined8 * param_1)

void FUN_140048f90(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    (**(code **)*param_1)(param_1,1);
  }
  return;
}


// ==== FUN_140048fb0 @ 140048fb0  undefined8 FUN_140048fb0(longlong param_1)

ulonglong FUN_140048fb0(longlong param_1)

{
  uint uVar1;
  ulonglong extraout_RAX;
  longlong lVar2;
  longlong *plVar3;
  ulonglong extraout_RAX_00;
  
  if (*(longlong *)(param_1 + 0x10) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return extraout_RAX & 0xffffffffffffff00;
  }
  uVar1 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x10))(*(longlong **)(param_1 + 0x10),2);
  lVar2 = FUN_14001c790();
  plVar3 = FUN_14003cd80(lVar2,uVar1,*(uint *)(param_1 + 0xc));
  if (plVar3 == (longlong *)0x0) {
    log_InlineLogERROR("CInstance::Create NPCServer Map Create Error, map:%u");
    return extraout_RAX_00 & 0xffffffffffffff00;
  }
  return CONCAT71((int7)((ulonglong)plVar3 >> 8),1);
}


// ==== FUN_140049050 @ 140049050  undefined FUN_140049050(longlong param_1)

void FUN_140049050(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = FUN_14001c790();
  FUN_14003cc10(lVar1,*(uint *)(param_1 + 0xc));
  return;
}


// ==== FUN_140049070 @ 140049070  undefined4 FUN_140049070(longlong param_1)

undefined4 FUN_140049070(longlong param_1)

{
  return *(undefined4 *)(param_1 + 8);
}


// ==== FUN_140049090 @ 140049090  undefined FUN_140049090(longlong param_1)

void FUN_140049090(longlong param_1)

{
  if (*(longlong *)(param_1 + 0x10) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0001400490d5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(longlong **)(param_1 + 0x10) + 0x60))();
  return;
}


// ==== FUN_1400490e0 @ 1400490e0  undefined8 FUN_1400490e0(longlong param_1)

undefined8 FUN_1400490e0(longlong param_1)

{
  undefined8 uVar1;
  
  if (*(longlong *)(param_1 + 0x10) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return 0;
  }
                    /* WARNING: Could not recover jumptable at 0x000140049127. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x10))();
  return uVar1;
}


// ==== FUN_140049130 @ 140049130  undefined8 FUN_140049130(longlong param_1)

undefined8 FUN_140049130(longlong param_1)

{
  undefined8 uVar1;
  
  if (*(longlong *)(param_1 + 0x10) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return 0;
  }
                    /* WARNING: Could not recover jumptable at 0x000140049177. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x18))();
  return uVar1;
}


// ==== FUN_1400491b0 @ 1400491b0  undefined8 * FUN_1400491b0(undefined4 param_1, longlong param_2, undefined4 param_3)

undefined8 * FUN_1400491b0(undefined4 param_1,longlong param_2,undefined4 param_3)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  
  if (param_2 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    puVar3 = (undefined8 *)0x0;
  }
  else {
    puVar1 = (undefined8 *)operator_new(0x18);
    puVar3 = (undefined8 *)0x0;
    if (puVar1 != (undefined8 *)0x0) {
      *puVar1 = CInstance::vftable;
      *(undefined4 *)(puVar1 + 1) = param_1;
      puVar1[2] = param_2;
      *(undefined4 *)((longlong)puVar1 + 0xc) = param_3;
      puVar3 = puVar1;
    }
    if (puVar3 == (undefined8 *)0x0) {
      log_InlineLogERROR(&DAT_1400be0b0);
      puVar3 = (undefined8 *)0x0;
    }
    else {
      uVar2 = FUN_140048fb0((longlong)puVar3);
      if ((char)uVar2 == '\0') {
        puVar3 = (undefined8 *)0x0;
      }
    }
  }
  return puVar3;
}


// ==== FUN_140049310 @ 140049310  bool FUN_140049310(longlong param_1, int param_2, int param_3)

bool FUN_140049310(longlong param_1,int param_2,int param_3)

{
  int iVar1;
  
  if (-1 < param_2) {
    iVar1 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))();
    if ((param_2 < iVar1) && (-1 < param_3)) {
      iVar1 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))();
      if (param_3 < iVar1) {
        iVar1 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x18))
                          (*(longlong **)(param_1 + 0x10),param_2,param_3);
        return iVar1 == 0;
      }
    }
  }
  return false;
}


// ==== FUN_140049390 @ 140049390  undefined FUN_140049390(longlong param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4, int param_5)

void FUN_140049390(longlong param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                  int param_5)

{
  longlong lVar1;
  
  lVar1 = FUN_14001c790();
  lVar1 = FUN_14003c530(lVar1,param_5);
  if (lVar1 == 0) {
    log_InlineLogERROR(
                      "CGameMap::AddTerrainObj GetTerrainNpcFileName failed, item type:%u at %s, %d."
                      );
  }
  else {
    (**(code **)(**(longlong **)(param_1 + 0x10) + 0x68))
              (*(longlong **)(param_1 + 0x10),param_2,param_3,param_4,lVar1);
  }
  return;
}


// ==== FUN_140049420 @ 140049420  undefined FUN_140049420(longlong param_1)

void FUN_140049420(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x000140049427. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(longlong **)(param_1 + 0x10) + 0x50))();
  return;
}


// ==== FUN_140049430 @ 140049430  undefined FUN_140049430(longlong param_1)

void FUN_140049430(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x000140049437. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))();
  return;
}


// ==== FUN_140049440 @ 140049440  int FUN_140049440(longlong param_1)

int FUN_140049440(longlong param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))();
  return (iVar1 + -1) / 0x12 + 1;
}


// ==== FUN_140049480 @ 140049480  undefined FUN_140049480(longlong param_1)

void FUN_140049480(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x000140049487. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))();
  return;
}


// ==== FUN_140049490 @ 140049490  int FUN_140049490(longlong param_1)

int FUN_140049490(longlong param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))();
  return (iVar1 + -1) / 0x12 + 1;
}


// ==== FUN_1400494f0 @ 1400494f0  longlong FUN_1400494f0(longlong param_1, ulonglong param_2)

longlong FUN_1400494f0(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18)) / 0x30) <= param_2
     ) {
    _invalid_parameter_noinfo();
  }
  return param_2 * 0x30 + *(longlong *)(param_1 + 0x18);
}


// ==== FUN_140049580 @ 140049580  longlong FUN_140049580(longlong param_1, ulonglong param_2)

longlong FUN_140049580(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18)) / 0x30) <= param_2
     ) {
    _invalid_parameter_noinfo();
  }
  return param_2 * 0x30 + *(longlong *)(param_1 + 0x18);
}


// ==== FUN_140049610 @ 140049610  longlong FUN_140049610(longlong param_1, ulonglong param_2)

longlong FUN_140049610(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18)) / 0x18) <= param_2
     ) {
    _invalid_parameter_noinfo();
  }
  return *(longlong *)(param_1 + 0x18) + param_2 * 0x18;
}


// ==== FUN_140049670 @ 140049670  bool FUN_140049670(longlong * param_1, longlong * param_2)

bool FUN_140049670(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_1400496c0 @ 1400496c0  undefined FUN_1400496c0(void)

void FUN_1400496c0(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [48];
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_70,"invalid bitset<N> position");
  std::exception::exception((exception *)local_48);
  local_48[0] = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
  local_48[0] = std::out_of_range::vftable;
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400feda0);
}


// ==== FUN_140049780 @ 140049780  undefined4 * FUN_140049780(undefined4 * param_1, undefined4 * param_2, void * param_3)

undefined4 * FUN_140049780(undefined4 *param_1,undefined4 *param_2,void *param_3)

{
  *param_1 = *param_2;
  memcpy(param_1 + 1,param_3,0x108);
  return param_1;
}


// ==== FUN_1400497c0 @ 1400497c0  undefined FUN_1400497c0(void)

void FUN_1400497c0(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [48];
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_70,"vector<T> too long");
  std::exception::exception((exception *)local_48);
  local_48[0] = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
  local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
}


// ==== FUN_140049850 @ 140049850  undefined FUN_140049850(void)

void FUN_140049850(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [48];
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_70,"vector<T> too long");
  std::exception::exception((exception *)local_48);
  local_48[0] = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
  local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
}


// ==== FUN_1400498e0 @ 1400498e0  undefined FUN_1400498e0(undefined8 * param_1)

void FUN_1400498e0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140049a50 @ 140049a50  undefined FUN_140049a50(void)

void FUN_140049a50(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [48];
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_70,"vector<T> too long");
  std::exception::exception((exception *)local_48);
  local_48[0] = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
  local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
}


// ==== FUN_140049b10 @ 140049b10  undefined FUN_140049b10(longlong param_1, longlong * param_2)

void FUN_140049b10(longlong param_1,longlong *param_2)

{
  longlong lVar1;
  longlong *plVar2;
  
  lVar1 = *param_2;
  *param_2 = *(longlong *)(lVar1 + 0x10);
  if (*(char *)(*(longlong *)(lVar1 + 0x10) + 0x125) == '\0') {
    *(longlong **)(*(longlong *)(lVar1 + 0x10) + 8) = param_2;
  }
  *(longlong *)(lVar1 + 8) = param_2[1];
  if (param_2 == *(longlong **)(*(longlong *)(param_1 + 0x30) + 8)) {
    *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = lVar1;
    *(longlong **)(lVar1 + 0x10) = param_2;
    param_2[1] = lVar1;
    return;
  }
  plVar2 = (longlong *)param_2[1];
  if (param_2 == (longlong *)plVar2[2]) {
    plVar2[2] = lVar1;
    *(longlong **)(lVar1 + 0x10) = param_2;
    param_2[1] = lVar1;
    return;
  }
  *plVar2 = lVar1;
  *(longlong **)(lVar1 + 0x10) = param_2;
  param_2[1] = lVar1;
  return;
}


// ==== FUN_140049b70 @ 140049b70  bool FUN_140049b70(longlong * param_1, longlong * param_2)

bool FUN_140049b70(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_140049bd0 @ 140049bd0  undefined FUN_140049bd0(void)

void FUN_140049bd0(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [48];
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_70,"vector<T> too long");
  std::exception::exception((exception *)local_48);
  local_48[0] = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
  local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
}


// ==== FUN_140049c50 @ 140049c50  bool FUN_140049c50(longlong * param_1, longlong * param_2)

bool FUN_140049c50(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_140049c90 @ 140049c90  bool FUN_140049c90(longlong * param_1, longlong * param_2)

bool FUN_140049c90(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_140049da0 @ 140049da0  longlong * FUN_140049da0(longlong * param_1, longlong param_2)

longlong * FUN_140049da0(longlong *param_1,longlong param_2)

{
  longlong *plVar1;
  ulonglong uVar2;
  longlong lVar3;
  longlong lVar4;
  
  plVar1 = (longlong *)*param_1;
  lVar3 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar1 = (longlong *)*param_1;
    lVar4 = lVar3;
    if (plVar1 != (longlong *)0x0) goto LAB_140049dd0;
  }
  else {
LAB_140049dd0:
    lVar4 = *plVar1;
  }
  uVar2 = param_1[1] + param_2 * 0x30;
  if (uVar2 <= *(ulonglong *)(lVar4 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar2) goto LAB_140049dfc;
  }
  _invalid_parameter_noinfo();
LAB_140049dfc:
  param_1[1] = param_1[1] + param_2 * 0x30;
  return param_1;
}


// ==== FUN_140049e20 @ 140049e20  longlong * FUN_140049e20(longlong * param_1, longlong param_2)

longlong * FUN_140049e20(longlong *param_1,longlong param_2)

{
  longlong *plVar1;
  ulonglong uVar2;
  longlong lVar3;
  longlong lVar4;
  
  plVar1 = (longlong *)*param_1;
  lVar3 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar1 = (longlong *)*param_1;
    lVar4 = lVar3;
    if (plVar1 != (longlong *)0x0) goto LAB_140049e50;
  }
  else {
LAB_140049e50:
    lVar4 = *plVar1;
  }
  uVar2 = param_1[1] + param_2 * 0x30;
  if (uVar2 <= *(ulonglong *)(lVar4 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar2) goto LAB_140049e7c;
  }
  _invalid_parameter_noinfo();
LAB_140049e7c:
  param_1[1] = param_1[1] + param_2 * 0x30;
  return param_1;
}


// ==== FUN_140049ea0 @ 140049ea0  longlong * FUN_140049ea0(longlong * param_1, longlong param_2)

longlong * FUN_140049ea0(longlong *param_1,longlong param_2)

{
  longlong *plVar1;
  ulonglong uVar2;
  longlong lVar3;
  longlong lVar4;
  
  plVar1 = (longlong *)*param_1;
  lVar3 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar1 = (longlong *)*param_1;
    lVar4 = lVar3;
    if (plVar1 != (longlong *)0x0) goto LAB_140049ed0;
  }
  else {
LAB_140049ed0:
    lVar4 = *plVar1;
  }
  uVar2 = param_1[1] + param_2 * 4;
  if (uVar2 <= *(ulonglong *)(lVar4 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar2) goto LAB_140049ef8;
  }
  _invalid_parameter_noinfo();
LAB_140049ef8:
  param_1[1] = param_1[1] + param_2 * 4;
  return param_1;
}


// ==== FUN_140049f10 @ 140049f10  longlong * FUN_140049f10(longlong * param_1, longlong param_2)

longlong * FUN_140049f10(longlong *param_1,longlong param_2)

{
  longlong *plVar1;
  ulonglong uVar2;
  longlong lVar3;
  longlong lVar4;
  
  plVar1 = (longlong *)*param_1;
  lVar3 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar1 = (longlong *)*param_1;
    lVar4 = lVar3;
    if (plVar1 != (longlong *)0x0) goto LAB_140049f40;
  }
  else {
LAB_140049f40:
    lVar4 = *plVar1;
  }
  uVar2 = param_1[1] + param_2 * 0x18;
  if (uVar2 <= *(ulonglong *)(lVar4 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar2) goto LAB_140049f70;
  }
  _invalid_parameter_noinfo();
LAB_140049f70:
  param_1[1] = param_1[1] + param_2 * 0x18;
  return param_1;
}


// ==== FUN_140049f90 @ 140049f90  bool FUN_140049f90(longlong * param_1, longlong * param_2)

bool FUN_140049f90(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_140049fd0 @ 140049fd0  longlong * FUN_140049fd0(longlong * param_1, longlong param_2)

longlong * FUN_140049fd0(longlong *param_1,longlong param_2)

{
  longlong *plVar1;
  ulonglong uVar2;
  longlong lVar3;
  longlong lVar4;
  
  plVar1 = (longlong *)*param_1;
  lVar3 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar1 = (longlong *)*param_1;
    lVar4 = lVar3;
    if (plVar1 != (longlong *)0x0) goto LAB_14004a000;
  }
  else {
LAB_14004a000:
    lVar4 = *plVar1;
  }
  uVar2 = param_1[1] + param_2 * 8;
  if (uVar2 <= *(ulonglong *)(lVar4 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar2) goto LAB_14004a028;
  }
  _invalid_parameter_noinfo();
LAB_14004a028:
  param_1[1] = param_1[1] + param_2 * 8;
  return param_1;
}


// ==== FUN_14004a040 @ 14004a040  bool FUN_14004a040(longlong * param_1, longlong * param_2)

bool FUN_14004a040(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_14004a080 @ 14004a080  undefined8 * FUN_14004a080(undefined8 * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, void * param_5, undefined1 param_6)

undefined8 *
FUN_14004a080(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             void *param_5,undefined1 param_6)

{
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  memcpy(param_1 + 3,param_5,0x10c);
  *(undefined1 *)((longlong)param_1 + 0x125) = 0;
  *(undefined1 *)((longlong)param_1 + 0x124) = param_6;
  return param_1;
}


// ==== FUN_14004a130 @ 14004a130  undefined FUN_14004a130(undefined8 * param_1)

void FUN_14004a130(undefined8 *param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(**(code **)(*(longlong *)*param_1 + 0x10))();
                    /* WARNING: Could not recover jumptable at 0x00014004a147. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x48))(plVar1);
  return;
}


// ==== FUN_14004a150 @ 14004a150  undefined FUN_14004a150(undefined8 * param_1)

void FUN_14004a150(undefined8 *param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)
           (**(code **)(*(longlong *)*param_1 + 0x20))((longlong *)*param_1,&DAT_140102d90);
                    /* WARNING: Could not recover jumptable at 0x00014004a16e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x40))(plVar1);
  return;
}


// ==== FUN_14004a180 @ 14004a180  undefined FUN_14004a180(undefined8 * param_1)

void FUN_14004a180(undefined8 *param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(**(code **)(*(longlong *)*param_1 + 0x10))();
                    /* WARNING: Could not recover jumptable at 0x00014004a197. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x78))(plVar1);
  return;
}


// ==== FUN_14004a1a0 @ 14004a1a0  undefined FUN_14004a1a0(undefined8 * param_1)

void FUN_14004a1a0(undefined8 *param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(**(code **)(*(longlong *)*param_1 + 0x10))();
                    /* WARNING: Could not recover jumptable at 0x00014004a1b7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x58))(plVar1);
  return;
}


// ==== FUN_14004a1c0 @ 14004a1c0  bool FUN_14004a1c0(longlong * param_1, longlong * param_2)

bool FUN_14004a1c0(longlong *param_1,longlong *param_2)

{
  longlong lVar1;
  
  lVar1 = (**(code **)(*param_2 + 0x38))(param_2);
  *param_1 = lVar1;
  return lVar1 != 0;
}


// ==== FUN_14004a200 @ 14004a200  undefined FUN_14004a200(undefined8 * param_1, undefined8 param_2, undefined4 param_3)

void FUN_14004a200(undefined8 *param_1,undefined8 param_2,undefined4 param_3)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(**(code **)(*(longlong *)*param_1 + 0x10))();
                    /* WARNING: Could not recover jumptable at 0x00014004a21f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0xb0))(plVar1,param_3);
  return;
}


// ==== FUN_14004a230 @ 14004a230  undefined FUN_14004a230(undefined8 * param_1, undefined8 param_2, undefined8 param_3)

void FUN_14004a230(undefined8 *param_1,undefined8 param_2,undefined8 param_3)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(**(code **)(*(longlong *)*param_1 + 0x10))();
                    /* WARNING: Could not recover jumptable at 0x00014004a250. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x80))(plVar1,param_3);
  return;
}


// ==== FUN_14004a260 @ 14004a260  undefined FUN_14004a260(undefined8 * param_1, undefined8 param_2, undefined8 param_3)

void FUN_14004a260(undefined8 *param_1,undefined8 param_2,undefined8 param_3)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(**(code **)(*(longlong *)*param_1 + 0x10))();
                    /* WARNING: Could not recover jumptable at 0x00014004a280. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0xa0))(plVar1,param_3);
  return;
}


// ==== FUN_14004a290 @ 14004a290  bool FUN_14004a290(longlong * param_1)

bool FUN_14004a290(longlong *param_1)

{
  longlong *plVar1;
  longlong lVar2;
  
  plVar1 = (longlong *)InstanceGet();
  lVar2 = (**(code **)(*plVar1 + 0x20))(plVar1,s_cq_map_140102d94);
  *param_1 = lVar2;
  return lVar2 != 0;
}


// ==== FUN_14004a2e0 @ 14004a2e0  undefined FUN_14004a2e0(ulonglong param_1)

void FUN_14004a2e0(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x30)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 * 0x30);
  return;
}


// ==== FUN_14004a360 @ 14004a360  undefined FUN_14004a360(ulonglong param_1)

void FUN_14004a360(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x30)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 * 0x30);
  return;
}


// ==== FUN_14004a3f0 @ 14004a3f0  undefined FUN_14004a3f0(ulonglong param_1)

void FUN_14004a3f0(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x18)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 * 0x18);
  return;
}


// ==== FUN_14004a470 @ 14004a470  undefined FUN_14004a470(ulonglong param_1)

void FUN_14004a470(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 8)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 << 3);
  return;
}


// ==== FUN_14004a4f0 @ 14004a4f0  undefined FUN_14004a4f0(ulonglong param_1)

void FUN_14004a4f0(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x128)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 * 0x128);
  return;
}


// ==== FUN_14004a5b0 @ 14004a5b0  undefined FUN_14004a5b0(longlong * param_1)

void FUN_14004a5b0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,0);
  }
  return;
}


// ==== FUN_14004a730 @ 14004a730  void * FUN_14004a730(void * param_1, longlong param_2, void * param_3)

void * FUN_14004a730(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (0 < lVar1) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14004a800 @ 14004a800  void * FUN_14004a800(void * param_1, longlong param_2, longlong param_3)

void * FUN_14004a800(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _Dst = (void *)(param_3 + lVar1 * -4);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 4,param_1,lVar1 * 4);
  }
  return _Dst;
}


// ==== FUN_14004a8a0 @ 14004a8a0  void * FUN_14004a8a0(void * param_1, longlong param_2, longlong param_3)

void * FUN_14004a8a0(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _Dst = (void *)(param_3 + lVar1 * -8);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 8,param_1,lVar1 * 8);
  }
  return _Dst;
}


// ==== FUN_14004a8f0 @ 14004a8f0  void * FUN_14004a8f0(void * param_1, longlong param_2, void * param_3)

void * FUN_14004a8f0(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _DstSize = lVar1 * 4;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14004a960 @ 14004a960  void * FUN_14004a960(void * param_1, uint param_2)

void * FUN_14004a960(void *param_1,uint param_2)

{
  FUN_140067850((longlong)param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_14004aa10 @ 14004aa10  void * FUN_14004aa10(void * param_1, longlong param_2, void * param_3)

void * FUN_14004aa10(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14004ab40 @ 14004ab40  undefined8 FUN_14004ab40(longlong param_1, int param_2, int param_3)

undefined8 FUN_14004ab40(longlong param_1,int param_2,int param_3)

{
  ulonglong in_RAX;
  
  if (-1 < param_2) {
    in_RAX = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))();
    if ((param_2 < (int)in_RAX) && (-1 < param_3)) {
      in_RAX = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))();
      if (param_3 < (int)in_RAX) {
        return CONCAT71((int7)(in_RAX >> 8),1);
      }
    }
  }
  return in_RAX & 0xffffffffffffff00;
}


// ==== FUN_14004aba0 @ 14004aba0  longlong FUN_14004aba0(longlong param_1, int param_2, int param_3)

longlong FUN_14004aba0(longlong param_1,int param_2,int param_3)

{
  longlong lVar1;
  
  if ((ulonglong)((*(longlong *)(param_1 + 0x38) - *(longlong *)(param_1 + 0x30)) / 0x30) <=
      (ulonglong)(longlong)(param_2 / 0x12)) {
    _invalid_parameter_noinfo();
  }
  lVar1 = (longlong)(param_2 / 0x12) * 0x30 + *(longlong *)(param_1 + 0x30);
  if ((ulonglong)((*(longlong *)(lVar1 + 0x20) - *(longlong *)(lVar1 + 0x18)) / 0x18) <=
      (ulonglong)(longlong)(param_3 / 0x12)) {
    _invalid_parameter_noinfo();
  }
  return *(longlong *)(lVar1 + 0x18) + (longlong)(param_3 / 0x12) * 0x18;
}


// ==== FUN_14004ac70 @ 14004ac70  longlong FUN_14004ac70(longlong param_1, int param_2, int param_3)

longlong FUN_14004ac70(longlong param_1,int param_2,int param_3)

{
  longlong lVar1;
  
  if ((ulonglong)((*(longlong *)(param_1 + 0x38) - *(longlong *)(param_1 + 0x30)) / 0x30) <=
      (ulonglong)(longlong)param_2) {
    _invalid_parameter_noinfo();
  }
  lVar1 = (longlong)param_2 * 0x30 + *(longlong *)(param_1 + 0x30);
  if ((ulonglong)((*(longlong *)(lVar1 + 0x20) - *(longlong *)(lVar1 + 0x18)) / 0x18) <=
      (ulonglong)(longlong)param_3) {
    _invalid_parameter_noinfo();
  }
  return *(longlong *)(lVar1 + 0x18) + (longlong)param_3 * 0x18;
}


// ==== FUN_14004ad20 @ 14004ad20  undefined8 FUN_14004ad20(longlong param_1, longlong * param_2)

ulonglong FUN_14004ad20(longlong param_1,longlong *param_2)

{
  int iVar1;
  int iVar2;
  ulonglong in_RAX;
  longlong lVar3;
  longlong *plVar4;
  ulonglong uVar5;
  longlong lVar6;
  undefined8 uVar7;
  ulonglong uVar8;
  
  if (param_2 == (longlong *)0x0) {
    return in_RAX & 0xffffffffffffff00;
  }
  iVar1 = (**(code **)(*param_2 + 0x40))(param_2);
  iVar2 = (**(code **)(*param_2 + 0x38))(param_2);
  lVar3 = FUN_14004aba0(param_1,iVar2,iVar1);
  uVar8 = 0;
  plVar4 = (longlong *)FUN_1400678b0(lVar3);
  uVar5 = (**(code **)(*plVar4 + 0x10))(plVar4);
  if (uVar5 != 0) {
    do {
      plVar4 = (longlong *)FUN_1400678b0(lVar3);
      lVar6 = (**(code **)(*plVar4 + 0x18))
                        (plVar4,uVar8,
                         "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\gamemap.cpp",
                         0x129);
      if (lVar6 != 0) {
        plVar4 = (longlong *)(lVar6 + 0x10);
        iVar1 = (**(code **)(*plVar4 + 0x38))(plVar4);
        iVar2 = (**(code **)(*param_2 + 0x38))(param_2);
        if (iVar1 == iVar2) {
          iVar1 = (**(code **)(*plVar4 + 0x40))(plVar4);
          uVar7 = (**(code **)(*param_2 + 0x40))(param_2);
          if (iVar1 == (int)uVar7) {
            return CONCAT71((int7)((ulonglong)uVar7 >> 8),1);
          }
        }
      }
      uVar8 = uVar8 + 1;
      plVar4 = (longlong *)FUN_1400678b0(lVar3);
      uVar5 = (**(code **)(*plVar4 + 0x10))(plVar4);
    } while (uVar8 < uVar5);
  }
  return uVar5 & 0xffffffffffffff00;
}


// ==== FUN_14004ae30 @ 14004ae30  undefined8 FUN_14004ae30(longlong param_1, int param_2, int param_3)

undefined8 FUN_14004ae30(longlong param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined7 extraout_var;
  longlong lVar6;
  longlong *plVar7;
  ulonglong uVar8;
  undefined8 uVar9;
  ulonglong extraout_RAX;
  ulonglong extraout_RAX_00;
  
  if ((param_2 < 0) ||
     (iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))(), iVar4 <= param_2)) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return extraout_RAX_00 & 0xffffffffffffff00;
  }
  if ((-1 < param_3) &&
     (iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))(), param_3 < iVar4)) {
    puVar5 = (undefined1 *)FUN_14004aba0(param_1,param_2,param_3);
    cVar3 = FUN_140067890(puVar5);
    if (cVar3 != '\0') {
      return CONCAT71(extraout_var,1);
    }
    iVar4 = param_2 / 0x12 + -1;
    iVar2 = 0;
    if (0 < iVar4) {
      iVar2 = iVar4;
    }
    for (; (iVar2 <= param_2 / 0x12 + 1 &&
           (iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))(),
           iVar2 < (iVar4 + -1) / 0x12 + 1)); iVar2 = iVar2 + 1) {
      iVar4 = param_3 / 0x12 + -1;
      iVar1 = 0;
      if (0 < iVar4) {
        iVar1 = iVar4;
      }
      for (; (iVar1 <= param_3 / 0x12 + 1 &&
             (iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))(),
             iVar1 < (iVar4 + -1) / 0x12 + 1)); iVar1 = iVar1 + 1) {
        lVar6 = FUN_14004ac70(param_1,iVar2,iVar1);
        plVar7 = (longlong *)FUN_1400678b0(lVar6);
        uVar8 = (**(code **)(*plVar7 + 0x10))(plVar7);
        if (uVar8 != 0) {
          return uVar8 & 0xffffffffffffff00;
        }
      }
    }
    puVar5 = (undefined1 *)FUN_14004aba0(param_1,param_2,param_3);
    uVar9 = FUN_1400678c0(puVar5,1);
    return CONCAT71((int7)((ulonglong)uVar9 >> 8),1);
  }
  log_InlineLogERROR(&DAT_1400be0b0);
  return extraout_RAX & 0xffffffffffffff00;
}


// ==== FUN_14004b040 @ 14004b040  undefined FUN_14004b040(longlong param_1, int param_2, int param_3, int param_4)

void FUN_14004b040(longlong param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  longlong lVar2;
  int *piVar3;
  
  if (-1 < param_2) {
    if (((-1 < param_3) &&
        (iVar1 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))(), param_2 < iVar1)) &&
       (iVar1 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))(), param_3 < iVar1)) {
      lVar2 = FUN_140049580(param_1 + 0x58,(longlong)param_2);
      piVar3 = (int *)FUN_14003e890(lVar2,(longlong)param_3);
      *piVar3 = *piVar3 + param_4;
    }
  }
  return;
}


// ==== FUN_14004b0c0 @ 14004b0c0  undefined FUN_14004b0c0(longlong param_1, int param_2, int param_3, int param_4)

void FUN_14004b0c0(longlong param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  longlong lVar2;
  int *piVar3;
  
  if (-1 < param_2) {
    if (((-1 < param_3) &&
        (iVar1 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))(), param_2 < iVar1)) &&
       (iVar1 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))(), param_3 < iVar1)) {
      lVar2 = FUN_140049580(param_1 + 0x58,(longlong)param_2);
      piVar3 = (int *)FUN_14003e890(lVar2,(longlong)param_3);
      *piVar3 = *piVar3 - param_4;
    }
  }
  return;
}


// ==== FUN_14004b140 @ 14004b140  undefined4 FUN_14004b140(longlong param_1, int param_2, int param_3)

undefined4 FUN_14004b140(longlong param_1,int param_2,int param_3)

{
  int iVar1;
  longlong lVar2;
  undefined4 *puVar3;
  
  if ((-1 < param_2) && (-1 < param_3)) {
    iVar1 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))();
    if (param_2 < iVar1) {
      iVar1 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))();
      if (param_3 < iVar1) {
        lVar2 = FUN_140049580(param_1 + 0x58,(longlong)param_2);
        puVar3 = (undefined4 *)FUN_14003e890(lVar2,(longlong)param_3);
        return *puVar3;
      }
    }
  }
  return 0;
}


// ==== FUN_14004b1c0 @ 14004b1c0  undefined1 FUN_14004b1c0(longlong param_1, ulonglong param_2)

undefined1 FUN_14004b1c0(longlong param_1,ulonglong param_2)

{
  code *pcVar1;
  undefined1 uVar2;
  
  if (0xbf < param_2) {
    FUN_1400496c0();
    pcVar1 = (code *)swi(3);
    uVar2 = (*pcVar1)();
    return uVar2;
  }
  return (*(uint *)(param_1 + (param_2 >> 5) * 4) >> ((byte)param_2 & 0x1f) & 1) != 0;
}


// ==== FUN_14004b200 @ 14004b200  longlong FUN_14004b200(longlong param_1, ulonglong param_2)

longlong FUN_14004b200(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)(*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18) >> 3) <= param_2) {
    _invalid_parameter_noinfo();
  }
  return *(longlong *)(param_1 + 0x18) + param_2 * 8;
}


// ==== FUN_14004b240 @ 14004b240  undefined FUN_14004b240(undefined8 * param_1)

void FUN_14004b240(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14004b250 @ 14004b250  undefined FUN_14004b250(undefined8 * param_1)

void FUN_14004b250(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14004b270 @ 14004b270  undefined FUN_14004b270(undefined8 * param_1)

void FUN_14004b270(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14004b280 @ 14004b280  undefined FUN_14004b280(longlong param_1)

void FUN_14004b280(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_1 + 8);
  if (plVar3 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar3 + 2;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)*plVar1 == 0) {
      (**(code **)*plVar3)(plVar3);
      LOCK();
      piVar2 = (int *)((longlong)plVar3 + 0x14);
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (*piVar2 == 0) {
        (**(code **)(*plVar3 + 8))(plVar3);
      }
    }
  }
  return;
}


// ==== FUN_14004b2c0 @ 14004b2c0  longlong FUN_14004b2c0(longlong * param_1)

longlong FUN_14004b2c0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14004b2e2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14004b2e2:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_14004b300 @ 14004b300  longlong FUN_14004b300(longlong * param_1)

longlong FUN_14004b300(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14004b322;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14004b322:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_14004b340 @ 14004b340  undefined FUN_14004b340(undefined8 * param_1)

void FUN_14004b340(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14004b370 @ 14004b370  undefined FUN_14004b370(undefined8 param_1, ulonglong param_2)

void FUN_14004b370(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x30)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 0x30);
  return;
}


// ==== FUN_14004b3f0 @ 14004b3f0  undefined FUN_14004b3f0(undefined8 param_1, ulonglong param_2)

void FUN_14004b3f0(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x30)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 0x30);
  return;
}


// ==== FUN_14004b4b0 @ 14004b4b0  bool FUN_14004b4b0(longlong * param_1, longlong * param_2)

bool FUN_14004b4b0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_14004b4f0 @ 14004b4f0  bool FUN_14004b4f0(longlong * param_1, longlong * param_2)

bool FUN_14004b4f0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_14004b550 @ 14004b550  undefined8 * FUN_14004b550(undefined8 * param_1)

undefined8 * FUN_14004b550(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_14004b590 @ 14004b590  undefined FUN_14004b590(undefined8 param_1, ulonglong param_2)

void FUN_14004b590(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x18)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 0x18);
  return;
}


// ==== FUN_14004b610 @ 14004b610  undefined FUN_14004b610(longlong param_1, longlong param_2)

void FUN_14004b610(longlong param_1,longlong param_2)

{
  longlong *plVar1;
  longlong *plVar2;
  
  plVar1 = *(longlong **)(param_2 + 0x10);
  *(longlong *)(param_2 + 0x10) = *plVar1;
  if (*(char *)(*plVar1 + 0x125) == '\0') {
    *(longlong *)(*plVar1 + 8) = param_2;
  }
  plVar1[1] = *(longlong *)(param_2 + 8);
  if (param_2 == *(longlong *)(*(longlong *)(param_1 + 0x30) + 8)) {
    *(longlong **)(*(longlong *)(param_1 + 0x30) + 8) = plVar1;
    *plVar1 = param_2;
    *(longlong **)(param_2 + 8) = plVar1;
    return;
  }
  plVar2 = *(longlong **)(param_2 + 8);
  if (param_2 == *plVar2) {
    *plVar2 = (longlong)plVar1;
    *plVar1 = param_2;
    *(longlong **)(param_2 + 8) = plVar1;
    return;
  }
  plVar2[2] = (longlong)plVar1;
  *plVar1 = param_2;
  *(longlong **)(param_2 + 8) = plVar1;
  return;
}


// ==== FUN_14004b670 @ 14004b670  undefined FUN_14004b670(longlong * param_1)

void FUN_14004b670(longlong *param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)param_1[1];
  if (*(char *)((longlong)plVar2 + 0x125) == '\0') {
    lVar3 = *plVar2;
    if (*(char *)(lVar3 + 0x125) == '\0') {
      cVar1 = *(char *)(*(longlong *)(lVar3 + 0x10) + 0x125);
      lVar4 = *(longlong *)(lVar3 + 0x10);
      while (cVar1 == '\0') {
        cVar1 = *(char *)(*(longlong *)(lVar4 + 0x10) + 0x125);
        lVar3 = lVar4;
        lVar4 = *(longlong *)(lVar4 + 0x10);
      }
      param_1[1] = lVar3;
      return;
    }
    plVar2 = (longlong *)plVar2[1];
    cVar1 = *(char *)((longlong)plVar2 + 0x125);
    while ((cVar1 == '\0' && (param_1[1] == *plVar2))) {
      param_1[1] = (longlong)plVar2;
      plVar2 = (longlong *)plVar2[1];
      cVar1 = *(char *)((longlong)plVar2 + 0x125);
    }
    if (*(char *)(param_1[1] + 0x125) == '\0') {
      param_1[1] = (longlong)plVar2;
      return;
    }
  }
  else {
    lVar3 = plVar2[2];
    param_1[1] = lVar3;
    if (*(char *)(lVar3 + 0x125) == '\0') {
      return;
    }
  }
                    /* WARNING: Could not recover jumptable at 0x00014004b6a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_14004b730 @ 14004b730  undefined FUN_14004b730(longlong * param_1)

void FUN_14004b730(longlong *param_1)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *plVar4;
  
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  lVar2 = param_1[1];
  if (*(char *)(lVar2 + 0x125) == '\0') {
    plVar3 = *(longlong **)(lVar2 + 0x10);
    if (*(char *)((longlong)plVar3 + 0x125) != '\0') {
      lVar2 = *(longlong *)(lVar2 + 8);
      cVar1 = *(char *)(lVar2 + 0x125);
      while ((cVar1 == '\0' && (param_1[1] == *(longlong *)(lVar2 + 0x10)))) {
        param_1[1] = lVar2;
        lVar2 = *(longlong *)(lVar2 + 8);
        cVar1 = *(char *)(lVar2 + 0x125);
      }
      param_1[1] = lVar2;
      return;
    }
    cVar1 = *(char *)(*plVar3 + 0x125);
    plVar4 = (longlong *)*plVar3;
    while (cVar1 == '\0') {
      cVar1 = *(char *)(*plVar4 + 0x125);
      plVar3 = plVar4;
      plVar4 = (longlong *)*plVar4;
    }
    param_1[1] = (longlong)plVar3;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00014004b757. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_14004b7e0 @ 14004b7e0  undefined FUN_14004b7e0(undefined8 param_1, ulonglong param_2)

void FUN_14004b7e0(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 8)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 8);
  return;
}


// ==== FUN_14004b850 @ 14004b850  longlong * FUN_14004b850(longlong * param_1, longlong param_2)

longlong * FUN_14004b850(longlong *param_1,longlong param_2)

{
  FUN_140049da0(param_1,param_2);
  return param_1;
}


// ==== FUN_14004b870 @ 14004b870  longlong * FUN_14004b870(longlong * param_1, longlong param_2)

longlong * FUN_14004b870(longlong *param_1,longlong param_2)

{
  FUN_140049e20(param_1,param_2);
  return param_1;
}


// ==== FUN_14004b890 @ 14004b890  longlong * FUN_14004b890(longlong * param_1, longlong param_2)

longlong * FUN_14004b890(longlong *param_1,longlong param_2)

{
  FUN_140049ea0(param_1,param_2);
  return param_1;
}


// ==== FUN_14004b8b0 @ 14004b8b0  longlong * FUN_14004b8b0(longlong * param_1, longlong param_2)

longlong * FUN_14004b8b0(longlong *param_1,longlong param_2)

{
  FUN_140049f10(param_1,param_2);
  return param_1;
}


// ==== FUN_14004b8d0 @ 14004b8d0  bool FUN_14004b8d0(longlong * param_1, longlong * param_2)

bool FUN_14004b8d0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_14004b910 @ 14004b910  longlong * FUN_14004b910(longlong * param_1, longlong param_2)

longlong * FUN_14004b910(longlong *param_1,longlong param_2)

{
  FUN_140049fd0(param_1,param_2);
  return param_1;
}


// ==== FUN_14004b930 @ 14004b930  bool FUN_14004b930(longlong * param_1, longlong * param_2)

bool FUN_14004b930(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_14004b990 @ 14004b990  undefined FUN_14004b990(undefined8 param_1, ulonglong param_2)

void FUN_14004b990(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x128)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 0x128);
  return;
}


// ==== FUN_14004ba50 @ 14004ba50  undefined8 * FUN_14004ba50(undefined8 * param_1)

undefined8 * FUN_14004ba50(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_14004ba90 @ 14004ba90  undefined8 * FUN_14004ba90(void)

undefined8 * FUN_14004ba90(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = 0;
  }
  return puVar1;
}


// ==== FUN_14004bb10 @ 14004bb10  longlong * FUN_14004bb10(longlong * param_1, uint param_2)

longlong * FUN_14004bb10(longlong *param_1,uint param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,0);
  }
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_14004bb70 @ 14004bb70  void * FUN_14004bb70(void * param_1, longlong param_2, longlong param_3)

void * FUN_14004bb70(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _Dst = (void *)(param_3 + lVar1 * -4);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 4,param_1,lVar1 * 4);
  }
  return _Dst;
}


// ==== FUN_14004bc40 @ 14004bc40  void * FUN_14004bc40(void * param_1, longlong param_2, longlong param_3)

void * FUN_14004bc40(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _Dst = (void *)(param_3 + lVar1 * -8);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 8,param_1,lVar1 * 8);
  }
  return _Dst;
}


// ==== FUN_14004bca0 @ 14004bca0  undefined8 * FUN_14004bca0(undefined8 * param_1, undefined8 param_2, undefined8 param_3)

undefined8 * FUN_14004bca0(undefined8 *param_1,undefined8 param_2,undefined8 param_3)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  param_1[1] = param_2;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14) = 1;
  *param_1 = std::tr1::
             _Ref_count_d<struct__iobuf,int_(__cdecl*)(struct__iobuf*___ptr64),class_std::allocator<int>_>
             ::vftable;
  param_1[4] = param_3;
  return param_1;
}


// ==== FUN_14004bd40 @ 14004bd40  undefined FUN_14004bd40(undefined8 * param_1)

void FUN_14004bd40(undefined8 *param_1)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  return;
}


// ==== FUN_14004be50 @ 14004be50  undefined FUN_14004be50(undefined8 * param_1, undefined8 param_2, longlong param_3)

void FUN_14004be50(undefined8 *param_1,undefined8 param_2,longlong param_3)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  if (param_3 != 0) {
    LOCK();
    *(int *)(param_3 + 0x10) = *(int *)(param_3 + 0x10) + 1;
    UNLOCK();
  }
  plVar3 = (longlong *)param_1[1];
  if (plVar3 == (longlong *)0x0) {
    param_1[1] = param_3;
    *param_1 = param_2;
  }
  else {
    LOCK();
    plVar1 = plVar3 + 2;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)*plVar1 == 0) {
      (**(code **)*plVar3)(plVar3);
      LOCK();
      piVar2 = (int *)((longlong)plVar3 + 0x14);
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (*piVar2 == 0) {
        (**(code **)(*plVar3 + 8))(plVar3);
      }
      param_1[1] = param_3;
      *param_1 = param_2;
    }
    else {
      param_1[1] = param_3;
      *param_1 = param_2;
    }
  }
  return;
}


// ==== FUN_14004bee0 @ 14004bee0  void * FUN_14004bee0(void * param_1, longlong param_2, void * param_3)

void * FUN_14004bee0(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14004bfa0 @ 14004bfa0  undefined8 FUN_14004bfa0(longlong param_1)

undefined8 FUN_14004bfa0(longlong param_1)

{
  longlong *plVar1;
  uint *puVar2;
  undefined1 local_38 [24];
  undefined1 local_20 [24];
  
  plVar1 = (longlong *)(param_1 + 0x10);
  puVar2 = (uint *)(**(code **)(*(longlong *)(param_1 + 0x10) + 0x20))(plVar1,local_38);
  if ((*puVar2 >> 10 & 1) == 0) {
    puVar2 = (uint *)(**(code **)(*plVar1 + 0x20))(plVar1,local_20);
    if ((*puVar2 >> 0x1b & 1) == 0) {
      return CONCAT71((int7)((ulonglong)puVar2 >> 8),1);
    }
  }
  return (ulonglong)puVar2 & 0xffffffffffffff00;
}


// ==== FUN_14004bff0 @ 14004bff0  undefined8 FUN_14004bff0(longlong param_1, int param_2, int param_3, int param_4, uint param_5, int param_6)

ulonglong FUN_14004bff0(longlong param_1,int param_2,int param_3,int param_4,uint param_5,
                       int param_6)

{
  int iVar1;
  longlong *plVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  ulonglong uVar7;
  undefined4 extraout_var;
  undefined4 extraout_var_00;
  undefined4 extraout_var_01;
  longlong lVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  
  if (4 < (int)param_5) {
    param_5 = 4;
  }
  iVar14 = param_2 + *(int *)(&DAT_1400c7428 + (longlong)param_4 * 4);
  uVar7 = (ulonglong)*(uint *)(&DAT_1400c7448 + (longlong)param_4 * 4);
  iVar13 = param_3 + *(uint *)(&DAT_1400c7448 + (longlong)param_4 * 4);
  if ((((iVar14 < 0) ||
       (uVar7 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))(), (int)uVar7 <= iVar14)) ||
      (iVar13 < 0)) ||
     ((uVar7 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))(), (int)uVar7 <= iVar13 ||
      (uVar7 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x18))
                         (*(longlong **)(param_1 + 0x10),iVar14,iVar13), (int)uVar7 != 0)))) {
LAB_14004c07a:
    return uVar7 & 0xffffffffffffff00;
  }
  if ((int)param_5 < 3) {
    iVar3 = FUN_14004b140(param_1,iVar14,iVar13);
    uVar7 = CONCAT44(extraout_var,iVar3);
    if ((int)param_5 < iVar3) goto LAB_14004c07a;
  }
  if (param_6 != 0) {
    plVar2 = *(longlong **)(param_1 + 0x10);
    iVar3 = (**(code **)(*plVar2 + 8))(plVar2,iVar14,iVar13);
    uVar7 = (**(code **)(*plVar2 + 8))(plVar2,param_2,param_3);
    if (param_6 < iVar3 - (int)uVar7) {
LAB_14004c284:
      return uVar7 & 0xffffffffffffff00;
    }
  }
  uVar4 = (param_5 & 1 ^ (int)param_5 >> 0x1f) - ((int)param_5 >> 0x1f);
  uVar7 = (ulonglong)uVar4;
  if ((int)param_5 < 1) {
    if ((int)param_5 < 3) goto LAB_14004c17d;
  }
  else if ((int)param_5 < 3) {
    iVar12 = param_4 + 7;
    iVar3 = -1;
    do {
      uVar9 = iVar12 >> 0x1f & 7;
      lVar8 = (longlong)(int)((iVar12 + uVar9 & 7) - uVar9);
      iVar5 = *(int *)(&DAT_1400c7428 + lVar8 * 4);
      iVar1 = *(int *)(&DAT_1400c7448 + lVar8 * 4);
      uVar7 = FUN_14004ab40(param_1,iVar14 + iVar5,iVar13 + iVar1);
      if ((char)uVar7 != '\0') {
        iVar5 = FUN_14004b140(param_1,iVar14 + iVar5,iVar13 + iVar1);
        uVar7 = CONCAT44(extraout_var_00,iVar5);
        if ((int)uVar4 < iVar5) goto LAB_14004c284;
      }
      iVar3 = iVar3 + 1;
      iVar12 = iVar12 + 1;
    } while (iVar3 < 2);
    goto LAB_14004c17d;
  }
  iVar3 = (int)(param_5 + 1) / 2;
  iVar12 = iVar14 - iVar3;
  uVar9 = iVar3 + iVar14;
  uVar7 = (ulonglong)uVar9;
  if (iVar12 <= (int)uVar9) {
    uVar6 = iVar13 - iVar3;
    uVar15 = iVar12 - param_2;
    do {
      if ((int)uVar6 <= iVar3 + iVar13) {
        iVar14 = (uVar15 ^ (int)uVar15 >> 0x1f) - ((int)uVar15 >> 0x1f);
        uVar11 = uVar6 - param_3;
        uVar10 = uVar6;
        do {
          iVar5 = (uVar11 ^ (int)uVar11 >> 0x1f) - ((int)uVar11 >> 0x1f);
          if (iVar5 < iVar14) {
            iVar5 = iVar14;
          }
          if (((iVar3 < iVar5) && (-1 < iVar12)) &&
             ((iVar5 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))(), iVar12 < iVar5 &&
              ((-1 < (int)uVar10 &&
               (iVar5 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))(), (int)uVar10 < iVar5
               )))))) {
            iVar5 = FUN_14004b140(param_1,iVar12,uVar10);
            uVar7 = CONCAT44(extraout_var_01,iVar5);
            if ((int)uVar4 < iVar5) goto LAB_14004c284;
          }
          uVar10 = uVar10 + 1;
          uVar11 = uVar11 + 1;
        } while ((int)uVar10 <= iVar3 + iVar13);
      }
      uVar7 = (ulonglong)uVar6;
      iVar12 = iVar12 + 1;
      uVar15 = uVar15 + 1;
    } while (iVar12 <= (int)uVar9);
  }
LAB_14004c17d:
  return CONCAT71((int7)(uVar7 >> 8),1);
}


// ==== FUN_14004c290 @ 14004c290  undefined FUN_14004c290(longlong param_1, int param_2, int param_3, uint param_4)

void FUN_14004c290(longlong param_1,int param_2,int param_3,uint param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  ulonglong uVar9;
  ulonglong uVar10;
  
  if ((int)param_4 < 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return;
  }
  if (4 < (int)param_4) {
    param_4 = 4;
  }
  iVar2 = (int)(param_4 + 1) / 2;
  iVar7 = iVar2 + param_2;
  iVar3 = param_2 - iVar2;
  uVar9 = (ulonglong)iVar3;
  if (iVar3 <= iVar7) {
    uVar10 = uVar9;
    do {
      iVar8 = (int)uVar9;
      uVar9 = (longlong)param_3 - (longlong)iVar2;
      for (iVar6 = param_3 - iVar2; iVar6 <= iVar2 + param_3; iVar6 = iVar6 + 1) {
        if ((((-1 < iVar8) &&
             (iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))(), iVar8 < iVar4)) &&
            (-1 < (longlong)uVar9)) &&
           (iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))(), iVar6 < iVar4)) {
          if (((param_4 & 1 ^ (int)param_4 >> 0x1f) == (int)param_4 >> 0x1f) ||
             (((iVar8 != iVar3 && (iVar8 != iVar7)) &&
              ((iVar6 != param_3 - iVar2 && (iVar6 != iVar2 + param_3)))))) {
            iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))();
            if ((iVar8 < iVar4) &&
               (iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))(), iVar6 < iVar4)) {
              lVar5 = FUN_140049580(param_1 + 0x58,uVar10);
              if ((ulonglong)(*(longlong *)(lVar5 + 0x20) - *(longlong *)(lVar5 + 0x18) >> 2) <=
                  uVar9) {
                _invalid_parameter_noinfo();
              }
              piVar1 = (int *)(*(longlong *)(lVar5 + 0x18) + uVar9 * 4);
              *piVar1 = *piVar1 + 2;
            }
          }
          else {
            iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))();
            if ((iVar8 < iVar4) &&
               (iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))(), iVar6 < iVar4)) {
              lVar5 = FUN_140049580(param_1 + 0x58,uVar10);
              if ((ulonglong)(*(longlong *)(lVar5 + 0x20) - *(longlong *)(lVar5 + 0x18) >> 2) <=
                  uVar9) {
                _invalid_parameter_noinfo();
              }
              piVar1 = (int *)(*(longlong *)(lVar5 + 0x18) + uVar9 * 4);
              *piVar1 = *piVar1 + 1;
            }
          }
        }
        uVar9 = uVar9 + 1;
      }
      uVar9 = (ulonglong)(iVar8 + 1U);
      uVar10 = uVar10 + 1;
    } while ((int)(iVar8 + 1U) <= iVar7);
  }
  return;
}


// ==== FUN_14004c4c0 @ 14004c4c0  undefined FUN_14004c4c0(longlong param_1, int param_2, int param_3, uint param_4)

void FUN_14004c4c0(longlong param_1,int param_2,int param_3,uint param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  ulonglong uVar9;
  ulonglong uVar10;
  
  if ((int)param_4 < 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return;
  }
  if (4 < (int)param_4) {
    param_4 = 4;
  }
  iVar2 = (int)(param_4 + 1) / 2;
  iVar7 = iVar2 + param_2;
  iVar3 = param_2 - iVar2;
  uVar9 = (ulonglong)iVar3;
  if (iVar3 <= iVar7) {
    uVar10 = uVar9;
    do {
      iVar8 = (int)uVar9;
      uVar9 = (longlong)param_3 - (longlong)iVar2;
      for (iVar6 = param_3 - iVar2; iVar6 <= iVar2 + param_3; iVar6 = iVar6 + 1) {
        if ((((-1 < iVar8) &&
             (iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))(), iVar8 < iVar4)) &&
            (-1 < (longlong)uVar9)) &&
           (iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))(), iVar6 < iVar4)) {
          if (((param_4 & 1 ^ (int)param_4 >> 0x1f) == (int)param_4 >> 0x1f) ||
             (((iVar8 != iVar3 && (iVar8 != iVar7)) &&
              ((iVar6 != param_3 - iVar2 && (iVar6 != iVar2 + param_3)))))) {
            iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))();
            if ((iVar8 < iVar4) &&
               (iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))(), iVar6 < iVar4)) {
              lVar5 = FUN_140049580(param_1 + 0x58,uVar10);
              if ((ulonglong)(*(longlong *)(lVar5 + 0x20) - *(longlong *)(lVar5 + 0x18) >> 2) <=
                  uVar9) {
                _invalid_parameter_noinfo();
              }
              piVar1 = (int *)(*(longlong *)(lVar5 + 0x18) + uVar9 * 4);
              *piVar1 = *piVar1 + -2;
            }
          }
          else {
            iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))();
            if ((iVar8 < iVar4) &&
               (iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))(), iVar6 < iVar4)) {
              lVar5 = FUN_140049580(param_1 + 0x58,uVar10);
              if ((ulonglong)(*(longlong *)(lVar5 + 0x20) - *(longlong *)(lVar5 + 0x18) >> 2) <=
                  uVar9) {
                _invalid_parameter_noinfo();
              }
              piVar1 = (int *)(*(longlong *)(lVar5 + 0x18) + uVar9 * 4);
              *piVar1 = *piVar1 + -1;
            }
          }
        }
        uVar9 = uVar9 + 1;
      }
      uVar9 = (ulonglong)(iVar8 + 1U);
      uVar10 = uVar10 + 1;
    } while ((int)(iVar8 + 1U) <= iVar7);
  }
  return;
}


// ==== FUN_14004c6f0 @ 14004c6f0  undefined FUN_14004c6f0(longlong * param_1, longlong * param_2)

void FUN_14004c6f0(longlong *param_1,longlong *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  longlong lVar5;
  longlong *plVar6;
  
  if (param_2 != (longlong *)0x0) {
    iVar1 = (**(code **)(param_2[2] + 0x38))(param_2 + 2);
    if (-1 < iVar1) {
      plVar6 = (longlong *)param_1[2];
      iVar1 = (**(code **)(param_2[2] + 0x38))(param_2 + 2);
      iVar2 = (**(code **)(*plVar6 + 0x28))(plVar6);
      if (iVar1 < iVar2) {
        iVar1 = (**(code **)(param_2[2] + 0x40))(param_2 + 2);
        if (-1 < iVar1) {
          plVar6 = (longlong *)param_1[2];
          iVar1 = (**(code **)(param_2[2] + 0x40))(param_2 + 2);
          iVar2 = (**(code **)(*plVar6 + 0x20))(plVar6);
          if (iVar1 < iVar2) {
            uVar4 = FUN_14004bfa0((longlong)param_2);
            if ((char)uVar4 != '\0') {
              iVar1 = (**(code **)(param_2[2] + 0x40))(param_2 + 2);
              iVar2 = (**(code **)(param_2[2] + 0x38))(param_2 + 2);
              FUN_14004c4c0((longlong)param_1,iVar2,iVar1,0);
            }
            iVar1 = (**(code **)(param_2[2] + 0x40))(param_2 + 2);
            iVar2 = (**(code **)(param_2[2] + 0x38))(param_2 + 2);
            lVar5 = FUN_14004aba0((longlong)param_1,iVar2,iVar1);
            plVar6 = (longlong *)FUN_1400678b0(lVar5);
            lVar5 = *plVar6;
            uVar3 = (**(code **)(*param_2 + 8))(param_2);
            (**(code **)(lVar5 + 0x28))(plVar6,uVar3);
            return;
          }
        }
        log_InlineLogERROR(&DAT_1400be0b0);
        return;
      }
    }
    plVar6 = (longlong *)param_1[2];
    (**(code **)(*plVar6 + 0x20))();
    (**(code **)(*plVar6 + 0x28))(plVar6);
    (**(code **)(*param_1 + 8))(param_1);
    (**(code **)(param_2[2] + 0x40))(param_2 + 2);
    (**(code **)(param_2[2] + 0x38))(param_2 + 2);
    (**(code **)(param_2[2] + 0x30))(param_2 + 2);
    (**(code **)(*param_2 + 8))(param_2);
    log_InlineLogERROR("CGameMap::LeaveMap. Flag[%d] User[%u][%u, %d, %d] MapID[%u][%d, %d]");
  }
  return;
}


// ==== FUN_14004c900 @ 14004c900  undefined FUN_14004c900(longlong param_1, longlong * param_2)

void FUN_14004c900(longlong param_1,longlong *param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  longlong lVar6;
  longlong *plVar7;
  
  if (param_2 != (longlong *)0x0) {
    iVar2 = (**(code **)(*param_2 + 0x38))(param_2);
    if (-1 < iVar2) {
      iVar2 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))();
      iVar3 = (**(code **)(*param_2 + 0x38))(param_2);
      if ((iVar3 < iVar2) && (iVar2 = (**(code **)(*param_2 + 0x40))(param_2), -1 < iVar2)) {
        iVar2 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))();
        iVar3 = (**(code **)(*param_2 + 0x40))(param_2);
        if (iVar3 < iVar2) {
          cVar1 = (**(code **)(*param_2 + 0xb8))(param_2);
          if (cVar1 != '\0') {
            uVar4 = (**(code **)(*param_2 + 0x48))(param_2);
            iVar2 = (**(code **)(*param_2 + 0x40))(param_2);
            iVar3 = (**(code **)(*param_2 + 0x38))(param_2);
            FUN_14004c4c0(param_1,iVar3,iVar2,uVar4);
          }
          iVar2 = (**(code **)(*param_2 + 0x40))(param_2);
          iVar3 = (**(code **)(*param_2 + 0x38))(param_2);
          lVar6 = FUN_14004aba0(param_1,iVar3,iVar2);
          plVar7 = (longlong *)FUN_1400678a0(lVar6);
          lVar6 = *plVar7;
          uVar5 = (**(code **)(*param_2 + 0x28))(param_2);
                    /* WARNING: Could not recover jumptable at 0x00014004ca13. Too many branches */
                    /* WARNING: Treating indirect jump as call */
          (**(code **)(lVar6 + 0x28))(plVar7,uVar5);
          return;
        }
      }
    }
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  return;
}


// ==== FUN_14004ca70 @ 14004ca70  undefined FUN_14004ca70(longlong param_1, int param_2, int param_3)

void FUN_14004ca70(longlong param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  undefined1 *puVar5;
  longlong lVar6;
  longlong *plVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  
  iVar4 = param_2 / 0x12 + -1;
  iVar2 = 0;
  if (0 < iVar4) {
    iVar2 = iVar4;
  }
  for (; (iVar2 <= param_2 / 0x12 + 1 &&
         (iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))(),
         iVar2 < (iVar4 + -1) / 0x12 + 1)); iVar2 = iVar2 + 1) {
    iVar4 = param_3 / 0x12 + -1;
    iVar1 = 0;
    if (0 < iVar4) {
      iVar1 = iVar4;
    }
    for (; (iVar1 <= param_3 / 0x12 + 1 &&
           (iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))(),
           iVar1 < (iVar4 + -1) / 0x12 + 1)); iVar1 = iVar1 + 1) {
      puVar5 = (undefined1 *)FUN_14004ac70(param_1,iVar2,iVar1);
      cVar3 = FUN_140067890(puVar5);
      if (cVar3 != '\0') {
        puVar5 = (undefined1 *)FUN_14004ac70(param_1,iVar2,iVar1);
        FUN_1400678c0(puVar5,0);
        uVar9 = 0;
        lVar6 = FUN_14004ac70(param_1,iVar2,iVar1);
        plVar7 = (longlong *)FUN_1400678a0(lVar6);
        lVar6 = (**(code **)(*plVar7 + 0x10))(plVar7);
        if (lVar6 != 0) {
          do {
            lVar6 = FUN_14004ac70(param_1,iVar2,iVar1);
            plVar7 = (longlong *)FUN_1400678a0(lVar6);
            plVar7 = (longlong *)
                     (**(code **)(*plVar7 + 0x18))
                               (plVar7,uVar9,
                                "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\gamemap.cpp"
                                ,0x233);
            if ((plVar7 != (longlong *)0x0) &&
               (lVar6 = (**(code **)(*plVar7 + 0xb0))(plVar7,0x1040,0), lVar6 != 0)) {
              lVar6 = (**(code **)(*plVar7 + 0xb0))(plVar7,0x1040,0);
              FUN_14005b580(lVar6);
            }
            uVar9 = uVar9 + 1;
            lVar6 = FUN_14004ac70(param_1,iVar2,iVar1);
            plVar7 = (longlong *)FUN_1400678a0(lVar6);
            uVar8 = (**(code **)(*plVar7 + 0x10))(plVar7);
          } while (uVar9 < uVar8);
        }
      }
    }
  }
  return;
}


// ==== FUN_14004cc70 @ 14004cc70  undefined4 FUN_14004cc70(longlong param_1, int param_2, int param_3)

undefined4 FUN_14004cc70(longlong param_1,int param_2,int param_3)

{
  bool bVar1;
  undefined3 extraout_var;
  uint uVar2;
  
  bVar1 = FUN_140049310(param_1,param_2,param_3);
  uVar2 = CONCAT31(extraout_var,bVar1);
  if (bVar1) {
    uVar2 = FUN_14004b140(param_1,param_2,param_3);
    if (uVar2 == 0) {
      return 1;
    }
  }
  return uVar2 & 0xffffff00;
}


// ==== FUN_14004ccd0 @ 14004ccd0  undefined FUN_14004ccd0(longlong param_1)

void FUN_14004ccd0(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_1 + 8);
  if (plVar3 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar3 + 2;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)*plVar1 == 0) {
      (**(code **)*plVar3)(plVar3);
      LOCK();
      piVar2 = (int *)((longlong)plVar3 + 0x14);
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (*piVar2 == 0) {
        (**(code **)(*plVar3 + 8))(plVar3);
      }
    }
  }
  return;
}


// ==== FUN_14004cd10 @ 14004cd10  longlong FUN_14004cd10(longlong * param_1)

longlong FUN_14004cd10(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14004cd32;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14004cd32:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_14004cd50 @ 14004cd50  undefined FUN_14004cd50(undefined8 * param_1)

void FUN_14004cd50(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14004cd70 @ 14004cd70  undefined FUN_14004cd70(undefined8 * param_1)

void FUN_14004cd70(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14004cd90 @ 14004cd90  undefined FUN_14004cd90(undefined8 * param_1)

void FUN_14004cd90(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14004cdb0 @ 14004cdb0  undefined8 FUN_14004cdb0(longlong param_1, ulonglong param_2)

undefined8 FUN_14004cdb0(longlong param_1,ulonglong param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  longlong lVar3;
  
  uVar2 = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  if (param_2 != 0) {
    if (0x555555555555555 < param_2) {
      FUN_1400497c0();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_14004b370(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
    *(ulonglong *)(param_1 + 0x28) = param_2 * 0x30 + lVar3;
  }
  return uVar2;
}


// ==== FUN_14004ce20 @ 14004ce20  undefined8 FUN_14004ce20(longlong param_1, ulonglong param_2)

undefined8 FUN_14004ce20(longlong param_1,ulonglong param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  longlong lVar3;
  
  uVar2 = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  if (param_2 != 0) {
    if (0x555555555555555 < param_2) {
      FUN_140049850();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_14004b3f0(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
    *(ulonglong *)(param_1 + 0x28) = param_2 * 0x30 + lVar3;
  }
  return uVar2;
}


// ==== FUN_14004ce90 @ 14004ce90  undefined8 * FUN_14004ce90(undefined8 * param_1)

undefined8 * FUN_14004ce90(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_14004ced0 @ 14004ced0  undefined8 * FUN_14004ced0(undefined8 * param_1)

undefined8 * FUN_14004ced0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_14004cf10 @ 14004cf10  undefined8 FUN_14004cf10(longlong param_1, ulonglong param_2)

undefined8 FUN_14004cf10(longlong param_1,ulonglong param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  longlong lVar3;
  
  uVar2 = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  if (param_2 != 0) {
    if (0xaaaaaaaaaaaaaaa < param_2) {
      FUN_140049a50();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_14004b590(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    lVar3 = lVar3 + param_2 * 0x18;
    *(longlong *)(param_1 + 0x28) = lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
  }
  return uVar2;
}


// ==== FUN_14004cf80 @ 14004cf80  undefined8 * FUN_14004cf80(undefined8 * param_1)

undefined8 * FUN_14004cf80(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_14004cfe0 @ 14004cfe0  undefined8 * FUN_14004cfe0(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_14004cfe0(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_14004d020 @ 14004d020  longlong * FUN_14004d020(longlong * param_1)

longlong * FUN_14004d020(longlong *param_1)

{
  FUN_14004b730(param_1);
  return param_1;
}


// ==== FUN_14004d040 @ 14004d040  longlong * FUN_14004d040(longlong * param_1)

longlong * FUN_14004d040(longlong *param_1)

{
  FUN_14004b670(param_1);
  return param_1;
}


// ==== FUN_14004d060 @ 14004d060  longlong * FUN_14004d060(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_14004d060(longlong *param_1,longlong *param_2,longlong param_3)

{
  longlong *plVar1;
  longlong lVar2;
  ulonglong uVar3;
  longlong lVar4;
  longlong lVar5;
  
  plVar1 = (longlong *)*param_1;
  lVar2 = param_1[1];
  lVar4 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar4;
  }
  else {
    lVar5 = *plVar1;
  }
  uVar3 = param_3 * 0x30 + lVar2;
  if (uVar3 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar4 = *plVar1;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar3) goto LAB_14004d0d1;
  }
  _invalid_parameter_noinfo();
LAB_14004d0d1:
  *param_2 = (longlong)plVar1;
  param_2[1] = uVar3;
  return param_2;
}


// ==== FUN_14004d110 @ 14004d110  longlong * FUN_14004d110(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_14004d110(longlong *param_1,longlong *param_2,longlong param_3)

{
  longlong *plVar1;
  longlong lVar2;
  ulonglong uVar3;
  longlong lVar4;
  longlong lVar5;
  
  plVar1 = (longlong *)*param_1;
  lVar2 = param_1[1];
  lVar4 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar4;
  }
  else {
    lVar5 = *plVar1;
  }
  uVar3 = param_3 * 0x30 + lVar2;
  if (uVar3 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar4 = *plVar1;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar3) goto LAB_14004d181;
  }
  _invalid_parameter_noinfo();
LAB_14004d181:
  *param_2 = (longlong)plVar1;
  param_2[1] = uVar3;
  return param_2;
}


// ==== FUN_14004d1c0 @ 14004d1c0  longlong * FUN_14004d1c0(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_14004d1c0(longlong *param_1,longlong *param_2,longlong param_3)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  
  plVar2 = (longlong *)*param_1;
  lVar3 = param_1[1];
  lVar4 = 0;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar4;
  }
  else {
    lVar5 = *plVar2;
  }
  uVar1 = lVar3 + param_3 * 4;
  if (uVar1 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar2 != (longlong *)0x0) {
      lVar4 = *plVar2;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar1) goto LAB_14004d22a;
  }
  _invalid_parameter_noinfo();
LAB_14004d22a:
  *param_2 = (longlong)plVar2;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_14004d260 @ 14004d260  longlong * FUN_14004d260(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_14004d260(longlong *param_1,longlong *param_2,longlong param_3)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  
  plVar2 = (longlong *)*param_1;
  lVar3 = param_1[1];
  lVar4 = 0;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar4;
  }
  else {
    lVar5 = *plVar2;
  }
  uVar1 = lVar3 + param_3 * 0x18;
  if (uVar1 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar2 != (longlong *)0x0) {
      lVar4 = *plVar2;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar1) goto LAB_14004d2ce;
  }
  _invalid_parameter_noinfo();
LAB_14004d2ce:
  *param_2 = (longlong)plVar2;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_14004d300 @ 14004d300  longlong * FUN_14004d300(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_14004d300(longlong *param_1,longlong *param_2,longlong param_3)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  
  plVar2 = (longlong *)*param_1;
  lVar3 = param_1[1];
  lVar4 = 0;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar4;
  }
  else {
    lVar5 = *plVar2;
  }
  uVar1 = lVar3 + param_3 * 8;
  if (uVar1 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar2 != (longlong *)0x0) {
      lVar4 = *plVar2;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar1) goto LAB_14004d36a;
  }
  _invalid_parameter_noinfo();
LAB_14004d36a:
  *param_2 = (longlong)plVar2;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_14004d3a0 @ 14004d3a0  undefined FUN_14004d3a0(void)

void FUN_14004d3a0(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x128);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = 0;
  }
  if (puVar1 + 1 != (undefined8 *)0x0) {
    puVar1[1] = 0;
  }
  if (puVar1 + 2 != (undefined8 *)0x0) {
    puVar1[2] = 0;
  }
  *(undefined1 *)((longlong)puVar1 + 0x124) = 1;
  *(undefined1 *)((longlong)puVar1 + 0x125) = 0;
  return;
}


// ==== FUN_14004d410 @ 14004d410  undefined8 * FUN_14004d410(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, void * param_5, undefined1 param_6)

undefined8 *
FUN_14004d410(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             void *param_5,undefined1 param_6)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x128);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_2;
    puVar1[1] = param_3;
    puVar1[2] = param_4;
    memcpy(puVar1 + 3,param_5,0x10c);
    *(undefined1 *)((longlong)puVar1 + 0x124) = param_6;
    *(undefined1 *)((longlong)puVar1 + 0x125) = 0;
  }
  return puVar1;
}


// ==== FUN_14004d4a0 @ 14004d4a0  longlong * FUN_14004d4a0(longlong * param_1, longlong * param_2)

longlong * FUN_14004d4a0(longlong *param_1,longlong *param_2)

{
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  FUN_14004b730(param_1);
  return param_2;
}


// ==== FUN_14004d4d0 @ 14004d4d0  longlong * FUN_14004d4d0(longlong * param_1)

longlong * FUN_14004d4d0(longlong *param_1)

{
  FUN_14004b670(param_1);
  return param_1;
}


// ==== FUN_14004d500 @ 14004d500  undefined8 * FUN_14004d500(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_14004d500(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_14004d560 @ 14004d560  undefined8 * FUN_14004d560(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_14004d560(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_14004d5c0 @ 14004d5c0  undefined FUN_14004d5c0(undefined8 param_1, longlong * param_2)

void FUN_14004d5c0(undefined8 param_1,longlong *param_2)

{
  char cVar1;
  longlong *plVar2;
  
  cVar1 = *(char *)((longlong)param_2 + 0x125);
  while (cVar1 == '\0') {
    FUN_14004d5c0(param_1,(longlong *)param_2[2]);
    plVar2 = (longlong *)*param_2;
    operator_delete(param_2);
    param_2 = plVar2;
    cVar1 = *(char *)((longlong)plVar2 + 0x125);
  }
  return;
}


// ==== FUN_14004d620 @ 14004d620  undefined8 * FUN_14004d620(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_14004d620(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_14004d680 @ 14004d680  undefined8 * FUN_14004d680(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_14004d680(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_14004d6e0 @ 14004d6e0  undefined8 * FUN_14004d6e0(undefined8 * param_1)

undefined8 * FUN_14004d6e0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_14004d730 @ 14004d730  undefined FUN_14004d730(longlong * param_1)

void FUN_14004d730(longlong *param_1)

{
  undefined8 *puVar1;
  
  if (param_1 != (longlong *)0x0) {
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 != (undefined8 *)0x0) {
      (**(code **)*puVar1)(puVar1,0);
    }
    operator_delete(param_1);
  }
  return;
}


// ==== FUN_14004d790 @ 14004d790  void * FUN_14004d790(void * param_1, longlong param_2, longlong param_3)

void * FUN_14004d790(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _Dst = (void *)(param_3 + lVar1 * -4);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 4,param_1,lVar1 * 4);
  }
  return _Dst;
}


// ==== FUN_14004d7d0 @ 14004d7d0  longlong FUN_14004d7d0(undefined8 * param_1, undefined8 * param_2, longlong param_3)

longlong FUN_14004d7d0(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  longlong lVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  
  if (param_1 != param_2) {
    lVar1 = param_3 - (longlong)param_1;
    puVar2 = param_1;
    do {
      puVar3 = puVar2 + 3;
      *(undefined8 *)(lVar1 + -0x18 + (longlong)puVar3) = *puVar2;
      *(undefined8 *)(lVar1 + -0x10 + (longlong)puVar3) = puVar2[1];
      *(undefined8 *)(lVar1 + -8 + (longlong)puVar3) = puVar2[2];
      puVar2 = puVar3;
    } while (puVar3 != param_2);
  }
  return param_3 + (((longlong)param_2 - (longlong)param_1) / 0x18) * 0x18;
}


// ==== FUN_14004d880 @ 14004d880  void * FUN_14004d880(void * param_1, longlong param_2, void * param_3)

void * FUN_14004d880(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (0 < lVar1) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14004d8f0 @ 14004d8f0  void * FUN_14004d8f0(void * param_1, longlong param_2, longlong param_3)

void * FUN_14004d8f0(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _Dst = (void *)(param_3 + lVar1 * -8);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 8,param_1,lVar1 * 8);
  }
  return _Dst;
}


// ==== FUN_14004d9e0 @ 14004d9e0  void * FUN_14004d9e0(void * param_1, longlong param_2, void * param_3)

void * FUN_14004d9e0(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _DstSize = lVar1 * 4;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14004da20 @ 14004da20  void * FUN_14004da20(void * param_1, longlong param_2, void * param_3)

void * FUN_14004da20(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14004dab0 @ 14004dab0  undefined8 * FUN_14004dab0(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

undefined8 * FUN_14004dab0(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 3) {
    if (param_3 != (undefined8 *)0x0) {
      *param_3 = *param_1;
      param_3[1] = param_1[1];
      param_3[2] = param_1[2];
    }
    param_3 = param_3 + 3;
  }
  return param_3;
}


// ==== FUN_14004db40 @ 14004db40  undefined8 * FUN_14004db40(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

undefined8 * FUN_14004db40(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 3) {
    if (param_3 != (undefined8 *)0x0) {
      *param_3 = *param_1;
      param_3[1] = param_1[1];
      param_3[2] = param_1[2];
    }
    param_3 = param_3 + 3;
  }
  return param_3;
}


// ==== FUN_14004dba0 @ 14004dba0  undefined FUN_14004dba0(longlong * param_1, longlong * param_2)

void FUN_14004dba0(longlong *param_1,longlong *param_2)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  longlong lVar4;
  longlong *plVar5;
  
  if (param_2 != (longlong *)0x0) {
    iVar1 = (**(code **)(param_2[2] + 0x38))(param_2 + 2);
    if (-1 < iVar1) {
      plVar5 = (longlong *)param_1[2];
      iVar1 = (**(code **)(param_2[2] + 0x38))(param_2 + 2);
      iVar2 = (**(code **)(*plVar5 + 0x28))(plVar5);
      if (iVar1 < iVar2) {
        iVar1 = (**(code **)(param_2[2] + 0x40))(param_2 + 2);
        if (-1 < iVar1) {
          plVar5 = (longlong *)param_1[2];
          iVar1 = (**(code **)(param_2[2] + 0x40))(param_2 + 2);
          iVar2 = (**(code **)(*plVar5 + 0x20))(plVar5);
          if (iVar1 < iVar2) {
            uVar3 = FUN_14004bfa0((longlong)param_2);
            if ((char)uVar3 != '\0') {
              iVar1 = (**(code **)(param_2[2] + 0x40))(param_2 + 2);
              iVar2 = (**(code **)(param_2[2] + 0x38))(param_2 + 2);
              FUN_14004c290((longlong)param_1,iVar2,iVar1,0);
            }
            iVar1 = (**(code **)(param_2[2] + 0x40))(param_2 + 2);
            iVar2 = (**(code **)(param_2[2] + 0x38))(param_2 + 2);
            lVar4 = FUN_14004aba0((longlong)param_1,iVar2,iVar1);
            plVar5 = (longlong *)FUN_1400678b0(lVar4);
            (**(code **)(*plVar5 + 0x20))(plVar5,param_2);
            iVar1 = (**(code **)(param_2[2] + 0x40))(param_2 + 2);
            iVar2 = (**(code **)(param_2[2] + 0x38))(param_2 + 2);
            FUN_14004ca70((longlong)param_1,iVar2,iVar1);
            return;
          }
        }
        log_InlineLogERROR(&DAT_1400be0b0);
        return;
      }
    }
    plVar5 = (longlong *)param_1[2];
    (**(code **)(*plVar5 + 0x20))();
    (**(code **)(*plVar5 + 0x28))(plVar5);
    (**(code **)(*param_1 + 8))(param_1);
    (**(code **)(param_2[2] + 0x40))(param_2 + 2);
    (**(code **)(param_2[2] + 0x38))(param_2 + 2);
    (**(code **)(param_2[2] + 0x30))(param_2 + 2);
    (**(code **)(*param_2 + 8))(param_2);
    log_InlineLogERROR("CGameMap::EnterMap. Npc[%u] Flag[%d] User[%u][%u, %d, %d] MapID[%u][%d, %d]"
                      );
  }
  return;
}


// ==== FUN_14004ddd0 @ 14004ddd0  undefined FUN_14004ddd0(longlong param_1, longlong * param_2)

void FUN_14004ddd0(longlong param_1,longlong *param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  longlong lVar5;
  longlong *plVar6;
  
  if (param_2 != (longlong *)0x0) {
    iVar2 = (**(code **)(*param_2 + 0x38))(param_2);
    if (-1 < iVar2) {
      iVar2 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))();
      iVar3 = (**(code **)(*param_2 + 0x38))(param_2);
      if ((iVar3 < iVar2) && (iVar2 = (**(code **)(*param_2 + 0x40))(param_2), -1 < iVar2)) {
        iVar2 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))();
        iVar3 = (**(code **)(*param_2 + 0x40))(param_2);
        if (iVar3 < iVar2) {
          cVar1 = (**(code **)(*param_2 + 0xb8))(param_2);
          if (cVar1 != '\0') {
            uVar4 = (**(code **)(*param_2 + 0x48))(param_2);
            iVar2 = (**(code **)(*param_2 + 0x40))(param_2);
            iVar3 = (**(code **)(*param_2 + 0x38))(param_2);
            FUN_14004c290(param_1,iVar3,iVar2,uVar4);
          }
          iVar2 = (**(code **)(*param_2 + 0x40))(param_2);
          iVar3 = (**(code **)(*param_2 + 0x38))(param_2);
          lVar5 = FUN_14004aba0(param_1,iVar3,iVar2);
          plVar6 = (longlong *)FUN_1400678a0(lVar5);
                    /* WARNING: Could not recover jumptable at 0x00014004ded4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
          (**(code **)(*plVar6 + 0x20))(plVar6,param_2);
          return;
        }
      }
    }
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  return;
}


// ==== FUN_14004df30 @ 14004df30  undefined FUN_14004df30(longlong param_1, longlong * param_2, int param_3, int param_4)

void FUN_14004df30(longlong param_1,longlong *param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  longlong lVar6;
  longlong *plVar7;
  
  if (param_2 != (longlong *)0x0) {
    iVar1 = (**(code **)(param_2[2] + 0x38))(param_2 + 2);
    iVar2 = (**(code **)(param_2[2] + 0x40))(param_2 + 2);
    if (((((iVar1 < 0) ||
          (iVar3 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))(), iVar3 <= iVar1)) ||
         (iVar2 < 0)) ||
        ((iVar3 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))(), iVar3 <= iVar2 ||
         (param_3 < 0)))) ||
       ((iVar3 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))(), iVar3 <= param_3 ||
        ((param_4 < 0 ||
         (iVar3 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))(), iVar3 <= param_4)))))) {
      log_InlineLogERROR(&DAT_1400be0b0);
    }
    else {
      uVar5 = FUN_14004bfa0((longlong)param_2);
      if ((char)uVar5 != '\0') {
        FUN_14004c4c0(param_1,iVar1,iVar2,0);
        FUN_14004c290(param_1,param_3,param_4,0);
      }
      if ((iVar1 / 0x12 != param_3 / 0x12) || (iVar2 / 0x12 != param_4 / 0x12)) {
        lVar6 = FUN_14004aba0(param_1,iVar1,iVar2);
        plVar7 = (longlong *)FUN_1400678b0(lVar6);
        lVar6 = *plVar7;
        uVar4 = (**(code **)(*param_2 + 8))(param_2);
        (**(code **)(lVar6 + 0x28))(plVar7,uVar4);
        lVar6 = FUN_14004aba0(param_1,param_3,param_4);
        plVar7 = (longlong *)FUN_1400678b0(lVar6);
        (**(code **)(*plVar7 + 0x20))(plVar7,param_2);
        FUN_14004ca70(param_1,param_3,param_4);
      }
    }
  }
  return;
}


// ==== FUN_14004e140 @ 14004e140  undefined FUN_14004e140(longlong param_1, longlong * param_2, int param_3, int param_4)

void FUN_14004e140(longlong param_1,longlong *param_2,int param_3,int param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  longlong lVar7;
  longlong *plVar8;
  
  if (param_2 != (longlong *)0x0) {
    iVar2 = (**(code **)(*param_2 + 0x38))(param_2);
    iVar3 = (**(code **)(*param_2 + 0x40))(param_2);
    if (((((iVar2 < 0) ||
          (iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))(), iVar4 <= iVar2)) ||
         (iVar3 < 0)) ||
        ((iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))(), iVar4 <= iVar3 ||
         (param_3 < 0)))) ||
       ((iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))(), iVar4 <= param_3 ||
        ((param_4 < 0 ||
         (iVar4 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))(), iVar4 <= param_4)))))) {
      log_InlineLogERROR(&DAT_1400be0b0);
    }
    else {
      cVar1 = (**(code **)(*param_2 + 0xb8))(param_2);
      if (cVar1 != '\0') {
        uVar5 = (**(code **)(*param_2 + 0x48))(param_2);
        FUN_14004c4c0(param_1,iVar2,iVar3,uVar5);
        uVar5 = (**(code **)(*param_2 + 0x48))(param_2);
        FUN_14004c290(param_1,param_3,param_4,uVar5);
      }
      if ((iVar2 / 0x12 != param_3 / 0x12) || (iVar3 / 0x12 != param_4 / 0x12)) {
        lVar7 = FUN_14004aba0(param_1,iVar2,iVar3);
        plVar8 = (longlong *)FUN_1400678a0(lVar7);
        lVar7 = *plVar8;
        uVar6 = (**(code **)(*param_2 + 0x28))(param_2);
        (**(code **)(lVar7 + 0x28))(plVar8,uVar6);
        lVar7 = FUN_14004aba0(param_1,param_3,param_4);
        plVar8 = (longlong *)FUN_1400678a0(lVar7);
        (**(code **)(*plVar8 + 0x20))(plVar8,param_2);
      }
    }
  }
  return;
}


// ==== FUN_14004e360 @ 14004e360  undefined FUN_14004e360(undefined8 * param_1)

void FUN_14004e360(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14004e380 @ 14004e380  undefined8 * FUN_14004e380(undefined8 * param_1)

undefined8 * FUN_14004e380(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_14004e3d0 @ 14004e3d0  undefined8 * FUN_14004e3d0(undefined8 * param_1)

undefined8 * FUN_14004e3d0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_14004e420 @ 14004e420  undefined8 * FUN_14004e420(undefined8 * param_1)

undefined8 * FUN_14004e420(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  puVar2 = (undefined8 *)0x0;
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_1;
    puVar2 = puVar1;
  }
  *param_1 = puVar2;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  return param_1;
}


// ==== FUN_14004e480 @ 14004e480  undefined8 * FUN_14004e480(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_14004e480(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_14004e510 @ 14004e510  undefined FUN_14004e510(longlong param_1)

void FUN_14004e510(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = FUN_14004d3a0();
  *(longlong *)(param_1 + 0x30) = lVar1;
  *(undefined1 *)(lVar1 + 0x125) = 1;
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)*(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x30);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 0x10) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = 0;
  return;
}


// ==== FUN_14004e550 @ 14004e550  undefined8 * FUN_14004e550(undefined8 * param_1, undefined8 * param_2, char param_3, undefined8 * param_4, void * param_5)

undefined8 *
FUN_14004e550(undefined8 *param_1,undefined8 *param_2,char param_3,undefined8 *param_4,void *param_5
             )

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [40];
  
  if (0xf4898d5f85bb37 < (ulonglong)param_1[7]) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_70,"map/set<T> too long");
    std::exception::exception((exception *)local_48);
    local_48[0] = std::logic_error::vftable;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
    local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
  }
  plVar5 = FUN_14004d410(param_1,param_1[6],param_4,param_1[6],param_5,0);
  param_1[7] = param_1[7] + 1;
  if (param_4 == (undefined8 *)param_1[6]) {
    ((undefined8 *)param_1[6])[1] = plVar5;
    *(longlong **)param_1[6] = plVar5;
    *(longlong **)(param_1[6] + 0x10) = plVar5;
  }
  else if (param_3 == '\0') {
    param_4[2] = plVar5;
    if (param_4 == *(undefined8 **)(param_1[6] + 0x10)) {
      *(longlong **)(param_1[6] + 0x10) = plVar5;
    }
  }
  else {
    *param_4 = plVar5;
    if (param_4 == *(undefined8 **)param_1[6]) {
      *(longlong **)param_1[6] = plVar5;
    }
  }
  plVar7 = plVar5 + 1;
  cVar1 = *(char *)(*plVar7 + 0x124);
  plVar6 = plVar5;
  while (cVar1 == '\0') {
    plVar2 = (longlong *)*plVar7;
    plVar3 = (longlong *)plVar2[1];
    if (plVar2 == (longlong *)*plVar3) {
      lVar4 = plVar3[2];
      if (*(char *)(lVar4 + 0x124) == '\0') {
        *(undefined1 *)((longlong)plVar2 + 0x124) = 1;
        *(undefined1 *)(lVar4 + 0x124) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x124) = 0;
        plVar6 = *(longlong **)(*plVar7 + 8);
      }
      else {
        if (plVar6 == (longlong *)plVar2[2]) {
          plVar6 = (longlong *)plVar2[2];
          plVar2[2] = *plVar6;
          if (*(char *)(*plVar6 + 0x125) == '\0') {
            *(longlong **)(*plVar6 + 8) = plVar2;
          }
          plVar7 = plVar2 + 1;
          plVar6[1] = *plVar7;
          if (plVar2 == *(longlong **)(param_1[6] + 8)) {
            *(longlong **)(param_1[6] + 8) = plVar6;
          }
          else {
            plVar3 = (longlong *)*plVar7;
            if (plVar2 == (longlong *)*plVar3) {
              *plVar3 = (longlong)plVar6;
            }
            else {
              plVar3[2] = (longlong)plVar6;
            }
          }
          *plVar6 = (longlong)plVar2;
          *plVar7 = (longlong)plVar6;
          plVar6 = plVar2;
        }
        *(undefined1 *)(*plVar7 + 0x124) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x124) = 0;
        plVar7 = *(longlong **)(*plVar7 + 8);
        lVar4 = *plVar7;
        *plVar7 = *(longlong *)(lVar4 + 0x10);
        if (*(char *)(*(longlong *)(lVar4 + 0x10) + 0x125) == '\0') {
          *(longlong **)(*(longlong *)(lVar4 + 0x10) + 8) = plVar7;
        }
        *(longlong *)(lVar4 + 8) = plVar7[1];
        if (plVar7 == *(longlong **)(param_1[6] + 8)) {
          *(longlong *)(param_1[6] + 8) = lVar4;
        }
        else {
          plVar2 = (longlong *)plVar7[1];
          if (plVar7 == (longlong *)plVar2[2]) {
            plVar2[2] = lVar4;
          }
          else {
            *plVar2 = lVar4;
          }
        }
        *(longlong **)(lVar4 + 0x10) = plVar7;
        plVar7[1] = lVar4;
      }
    }
    else {
      lVar4 = *plVar3;
      if (*(char *)(lVar4 + 0x124) == '\0') {
        *(undefined1 *)((longlong)plVar2 + 0x124) = 1;
        *(undefined1 *)(lVar4 + 0x124) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x124) = 0;
        plVar6 = *(longlong **)(*plVar7 + 8);
      }
      else {
        if (plVar6 == (longlong *)*plVar2) {
          lVar4 = *plVar2;
          *plVar2 = *(longlong *)(lVar4 + 0x10);
          if (*(char *)(*(longlong *)(lVar4 + 0x10) + 0x125) == '\0') {
            *(longlong **)(*(longlong *)(lVar4 + 0x10) + 8) = plVar2;
          }
          plVar7 = plVar2 + 1;
          *(longlong *)(lVar4 + 8) = *plVar7;
          if (plVar2 == *(longlong **)(param_1[6] + 8)) {
            *(longlong *)(param_1[6] + 8) = lVar4;
          }
          else {
            plVar6 = (longlong *)*plVar7;
            if (plVar2 == (longlong *)plVar6[2]) {
              plVar6[2] = lVar4;
            }
            else {
              *plVar6 = lVar4;
            }
          }
          *(longlong **)(lVar4 + 0x10) = plVar2;
          *plVar7 = lVar4;
          plVar6 = plVar2;
        }
        *(undefined1 *)(*plVar7 + 0x124) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x124) = 0;
        lVar4 = *(longlong *)(*plVar7 + 8);
        plVar7 = *(longlong **)(lVar4 + 0x10);
        *(longlong *)(lVar4 + 0x10) = *plVar7;
        if (*(char *)(*plVar7 + 0x125) == '\0') {
          *(longlong *)(*plVar7 + 8) = lVar4;
        }
        plVar7[1] = *(longlong *)(lVar4 + 8);
        if (lVar4 == *(longlong *)(param_1[6] + 8)) {
          *(longlong **)(param_1[6] + 8) = plVar7;
        }
        else {
          plVar2 = *(longlong **)(lVar4 + 8);
          if (lVar4 == *plVar2) {
            *plVar2 = (longlong)plVar7;
          }
          else {
            plVar2[2] = (longlong)plVar7;
          }
        }
        *plVar7 = lVar4;
        *(longlong **)(lVar4 + 8) = plVar7;
      }
    }
    plVar7 = plVar6 + 1;
    cVar1 = *(char *)(*plVar7 + 0x124);
  }
  *(undefined1 *)(*(longlong *)(param_1[6] + 8) + 0x124) = 1;
  param_2[1] = plVar5;
  *param_2 = *param_1;
  return param_2;
}


// ==== FUN_14004e8d0 @ 14004e8d0  undefined8 * FUN_14004e8d0(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_14004e8d0(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_14004e930 @ 14004e930  undefined8 * FUN_14004e930(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_14004e930(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_14004e990 @ 14004e990  undefined8 * FUN_14004e990(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14004e990(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  undefined8 uVar1;
  
  uVar1 = *(undefined8 *)(param_3 + 8);
  if (param_1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_2 = *param_1;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_14004e9e0 @ 14004e9e0  undefined8 * FUN_14004e9e0(undefined8 * param_1, undefined8 * param_2, longlong * param_3)

undefined8 * FUN_14004e9e0(undefined8 *param_1,undefined8 *param_2,longlong *param_3)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  char cVar3;
  undefined1 uVar4;
  longlong *plVar5;
  longlong *plVar6;
  undefined8 *puVar7;
  longlong lVar8;
  longlong *plVar9;
  longlong *plVar10;
  longlong *plVar11;
  longlong *plVar12;
  undefined **local_80 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_68 [40];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_40 [40];
  
  plVar5 = (longlong *)param_3[1];
  if (*(char *)((longlong)plVar5 + 0x125) != '\0') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_40,"invalid map/set<T> iterator");
    std::exception::exception((exception *)local_80);
    local_80[0] = std::logic_error::vftable;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_68,local_40);
    local_80[0] = std::out_of_range::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_80,(ThrowInfo *)&DAT_1400feda0);
  }
  FUN_14004b730(param_3);
  plVar11 = (longlong *)*plVar5;
  if (*(char *)((longlong)plVar11 + 0x125) == '\0') {
    plVar12 = plVar11;
    if (*(char *)(plVar5[2] + 0x125) == '\0') {
      plVar10 = (longlong *)param_3[1];
      plVar12 = (longlong *)plVar10[2];
      if (plVar10 != plVar5) {
        plVar11[1] = (longlong)plVar10;
        *plVar10 = *plVar5;
        plVar11 = plVar10;
        if (plVar10 != (longlong *)plVar5[2]) {
          plVar11 = (longlong *)plVar10[1];
          if (*(char *)((longlong)plVar12 + 0x125) == '\0') {
            plVar12[1] = (longlong)plVar11;
          }
          *plVar11 = (longlong)plVar12;
          plVar10[2] = plVar5[2];
          *(longlong **)(plVar5[2] + 8) = plVar10;
        }
        if (*(longlong **)(param_1[6] + 8) == plVar5) {
          *(longlong **)(param_1[6] + 8) = plVar10;
        }
        else {
          puVar7 = (undefined8 *)plVar5[1];
          if ((longlong *)*puVar7 == plVar5) {
            *puVar7 = plVar10;
          }
          else {
            puVar7[2] = plVar10;
          }
        }
        plVar10[1] = plVar5[1];
        puVar1 = (undefined1 *)((longlong)plVar5 + 0x124);
        puVar2 = (undefined1 *)((longlong)plVar10 + 0x124);
        if (puVar2 != puVar1) {
          uVar4 = *puVar2;
          *puVar2 = *puVar1;
          *puVar1 = uVar4;
        }
        goto LAB_14004ebeb;
      }
    }
  }
  else {
    plVar12 = (longlong *)plVar5[2];
  }
  plVar11 = (longlong *)plVar5[1];
  if (*(char *)((longlong)plVar12 + 0x125) == '\0') {
    plVar12[1] = (longlong)plVar11;
  }
  if (*(longlong **)(param_1[6] + 8) == plVar5) {
    *(longlong **)(param_1[6] + 8) = plVar12;
  }
  else if ((longlong *)*plVar11 == plVar5) {
    *plVar11 = (longlong)plVar12;
  }
  else {
    plVar11[2] = (longlong)plVar12;
  }
  if (*(longlong **)param_1[6] == plVar5) {
    plVar10 = plVar11;
    if (*(char *)((longlong)plVar12 + 0x125) == '\0') {
      cVar3 = *(char *)(*plVar12 + 0x125);
      plVar6 = (longlong *)*plVar12;
      plVar10 = plVar12;
      while (plVar9 = plVar6, cVar3 == '\0') {
        plVar6 = (longlong *)*plVar9;
        cVar3 = *(char *)((longlong)plVar6 + 0x125);
        plVar10 = plVar9;
      }
    }
    *(longlong **)param_1[6] = plVar10;
  }
  if (*(longlong **)(param_1[6] + 0x10) == plVar5) {
    plVar10 = plVar11;
    if (*(char *)((longlong)plVar12 + 0x125) == '\0') {
      cVar3 = *(char *)(plVar12[2] + 0x125);
      plVar6 = (longlong *)plVar12[2];
      plVar10 = plVar12;
      while (plVar9 = plVar6, cVar3 == '\0') {
        plVar6 = (longlong *)plVar9[2];
        cVar3 = *(char *)((longlong)plVar6 + 0x125);
        plVar10 = plVar9;
      }
    }
    *(longlong **)(param_1[6] + 0x10) = plVar10;
  }
LAB_14004ebeb:
  if (*(char *)((longlong)plVar5 + 0x124) == '\x01') {
    if (plVar12 != *(longlong **)(param_1[6] + 8)) {
      do {
        plVar10 = plVar11;
        if (*(char *)((longlong)plVar12 + 0x124) != '\x01') break;
        plVar11 = (longlong *)*plVar10;
        if (plVar12 == plVar11) {
          plVar11 = (longlong *)plVar10[2];
          if (*(char *)((longlong)plVar11 + 0x124) == '\0') {
            *(undefined1 *)((longlong)plVar11 + 0x124) = 1;
            *(undefined1 *)((longlong)plVar10 + 0x124) = 0;
            FUN_14004b610((longlong)param_1,(longlong)plVar10);
            plVar11 = (longlong *)plVar10[2];
          }
          if (*(char *)((longlong)plVar11 + 0x125) == '\0') {
            if ((*(char *)(*plVar11 + 0x124) != '\x01') || (*(char *)(plVar11[2] + 0x124) != '\x01')
               ) {
              if (*(char *)(plVar11[2] + 0x124) == '\x01') {
                *(undefined1 *)(*plVar11 + 0x124) = 1;
                *(undefined1 *)((longlong)plVar11 + 0x124) = 0;
                FUN_140049b10((longlong)param_1,plVar11);
                plVar11 = (longlong *)plVar10[2];
              }
              *(undefined1 *)((longlong)plVar11 + 0x124) =
                   *(undefined1 *)((longlong)plVar10 + 0x124);
              *(undefined1 *)((longlong)plVar10 + 0x124) = 1;
              *(undefined1 *)(plVar11[2] + 0x124) = 1;
              FUN_14004b610((longlong)param_1,(longlong)plVar10);
              break;
            }
            *(undefined1 *)((longlong)plVar11 + 0x124) = 0;
          }
        }
        else {
          if (*(char *)((longlong)plVar11 + 0x124) == '\0') {
            *(undefined1 *)((longlong)plVar11 + 0x124) = 1;
            *(undefined1 *)((longlong)plVar10 + 0x124) = 0;
            FUN_140049b10((longlong)param_1,plVar10);
            plVar11 = (longlong *)*plVar10;
          }
          if (*(char *)((longlong)plVar11 + 0x125) == '\0') {
            if ((*(char *)(plVar11[2] + 0x124) != '\x01') || (*(char *)(*plVar11 + 0x124) != '\x01')
               ) {
              if (*(char *)(*plVar11 + 0x124) == '\x01') {
                *(undefined1 *)(plVar11[2] + 0x124) = 1;
                *(undefined1 *)((longlong)plVar11 + 0x124) = 0;
                FUN_14004b610((longlong)param_1,(longlong)plVar11);
                plVar11 = (longlong *)*plVar10;
              }
              *(undefined1 *)((longlong)plVar11 + 0x124) =
                   *(undefined1 *)((longlong)plVar10 + 0x124);
              *(undefined1 *)((longlong)plVar10 + 0x124) = 1;
              *(undefined1 *)(*plVar11 + 0x124) = 1;
              FUN_140049b10((longlong)param_1,plVar10);
              break;
            }
            *(undefined1 *)((longlong)plVar11 + 0x124) = 0;
          }
        }
        plVar11 = (longlong *)plVar10[1];
        plVar12 = plVar10;
      } while (plVar10 != *(longlong **)(param_1[6] + 8));
    }
    *(undefined1 *)((longlong)plVar12 + 0x124) = 1;
  }
  operator_delete(plVar5);
  if (param_1[7] != 0) {
    param_1[7] = param_1[7] + -1;
  }
  lVar8 = param_3[1];
  *param_2 = *param_1;
  param_2[1] = lVar8;
  return param_2;
}


// ==== FUN_14004ee30 @ 14004ee30  undefined FUN_14004ee30(longlong param_1)

void FUN_14004ee30(longlong param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  
  plVar2 = *(longlong **)(*(longlong *)(param_1 + 0x30) + 8);
  cVar1 = *(char *)((longlong)plVar2 + 0x125);
  while (cVar1 == '\0') {
    FUN_14004d5c0(param_1,(longlong *)plVar2[2]);
    plVar3 = (longlong *)*plVar2;
    operator_delete(plVar2);
    plVar2 = plVar3;
    cVar1 = *(char *)((longlong)plVar3 + 0x125);
  }
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)*(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x30);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 0x10) = *(longlong *)(param_1 + 0x30);
  return;
}


// ==== FUN_14004eec0 @ 14004eec0  undefined8 * FUN_14004eec0(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_14004eec0(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_14004ef20 @ 14004ef20  undefined8 * FUN_14004ef20(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_14004ef20(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_14004ef80 @ 14004ef80  undefined8 * FUN_14004ef80(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14004ef80(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[3];
  *param_2 = 0;
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14004efd0 @ 14004efd0  undefined8 * FUN_14004efd0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14004efd0(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[4];
  *param_2 = 0;
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14004f020 @ 14004f020  undefined8 * FUN_14004f020(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14004f020(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[3];
  *param_2 = 0;
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14004f070 @ 14004f070  undefined8 * FUN_14004f070(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14004f070(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[4];
  *param_2 = 0;
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14004f0c0 @ 14004f0c0  undefined8 * FUN_14004f0c0(undefined8 * param_1)

undefined8 * FUN_14004f0c0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_14004f110 @ 14004f110  longlong FUN_14004f110(longlong param_1, longlong param_2, longlong param_3)

longlong FUN_14004f110(longlong param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  longlong lVar2;
  longlong lVar3;
  
  if (param_1 != param_2) {
    lVar1 = param_3 - param_2;
    lVar2 = param_2;
    do {
      lVar3 = lVar2 + -0x18;
      *(undefined8 *)(lVar1 + lVar3) = *(undefined8 *)(lVar2 + -0x18);
      *(undefined8 *)(lVar1 + 8 + lVar3) = *(undefined8 *)(lVar2 + -0x10);
      *(undefined8 *)(lVar1 + 0x10 + lVar3) = *(undefined8 *)(lVar2 + -8);
      lVar2 = lVar3;
    } while (lVar3 != param_1);
  }
  return param_3 + ((param_2 - param_1) / 0x18) * -0x18;
}


// ==== FUN_14004f180 @ 14004f180  undefined FUN_14004f180(undefined8 * param_1, undefined8 param_2, undefined8 param_3)

void FUN_14004f180(undefined8 *param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x28);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = std::tr1::_Ref_count_base::vftable;
    puVar1[1] = param_2;
    *(undefined4 *)(puVar1 + 2) = 0;
    *(undefined4 *)((longlong)puVar1 + 0x14) = 1;
    *puVar1 = std::tr1::
              _Ref_count_d<struct__iobuf,int_(__cdecl*)(struct__iobuf*___ptr64),class_std::allocator<int>_>
              ::vftable;
    puVar1[4] = param_3;
  }
  FUN_14004be50(param_1,param_2,(longlong)puVar1);
  return;
}


// ==== FUN_14004f200 @ 14004f200  void * FUN_14004f200(void * param_1, longlong param_2, void * param_3)

void * FUN_14004f200(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _DstSize = lVar1 * 4;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14004f240 @ 14004f240  void * FUN_14004f240(void * param_1, longlong param_2, void * param_3)

void * FUN_14004f240(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14004f280 @ 14004f280  void * FUN_14004f280(longlong param_1, longlong param_2, void * param_3)

void * FUN_14004f280(longlong param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = *(longlong *)(param_2 + 8) - (longlong)*(void **)(param_1 + 8) >> 2;
  _DstSize = lVar1 * 4;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,*(void **)(param_1 + 8),_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14004f2f0 @ 14004f2f0  undefined FUN_14004f2f0(longlong param_1, longlong param_2, undefined8 * param_3)

void FUN_14004f2f0(longlong param_1,longlong param_2,undefined8 *param_3)

{
  FUN_14004dab0(*(undefined8 **)(param_1 + 8),*(undefined8 **)(param_2 + 8),param_3);
  return;
}


// ==== FUN_14004f320 @ 14004f320  undefined FUN_14004f320(longlong param_1, longlong param_2)

void FUN_14004f320(longlong param_1,longlong param_2)

{
  if (param_1 != param_2) {
    do {
      FUN_140067850(param_1);
      param_1 = param_1 + 0x18;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_14004f360 @ 14004f360  undefined FUN_14004f360(undefined8 * param_1, longlong param_2, undefined8 * param_3)

void FUN_14004f360(undefined8 *param_1,longlong param_2,undefined8 *param_3)

{
  for (; param_2 != 0; param_2 = param_2 + -1) {
    if (param_1 != (undefined8 *)0x0) {
      *param_1 = *param_3;
      param_1[1] = param_3[1];
      param_1[2] = param_3[2];
    }
    param_1 = param_1 + 3;
  }
  return;
}


// ==== FUN_14004f3e0 @ 14004f3e0  undefined FUN_14004f3e0(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

void FUN_14004f3e0(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  FUN_14004db40(param_1,param_2,param_3);
  return;
}


// ==== FUN_14004f400 @ 14004f400  undefined8 * FUN_14004f400(undefined8 * param_1)

undefined8 * FUN_14004f400(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  puVar2 = (undefined8 *)0x0;
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_1;
    puVar2 = puVar1;
  }
  *param_1 = puVar2;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  return param_1;
}


// ==== FUN_14004f460 @ 14004f460  undefined8 * FUN_14004f460(undefined8 * param_1)

undefined8 * FUN_14004f460(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  puVar2 = (undefined8 *)0x0;
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_1;
    puVar2 = puVar1;
  }
  *param_1 = puVar2;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  return param_1;
}


// ==== FUN_14004f510 @ 14004f510  undefined8 FUN_14004f510(longlong * param_1)

undefined8 FUN_14004f510(longlong *param_1)

{
  longlong lVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  
  lVar1 = ((longlong *)*param_1)[6];
  if ((param_1[1] == 0) || (param_1[1] != *(longlong *)*param_1)) {
    _invalid_parameter_noinfo();
  }
  if (param_1[2] == lVar1) {
    param_1[3] = 0;
    return 0;
  }
  puVar2 = (undefined8 *)param_1[1];
  if (puVar2 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar2 = (undefined8 *)param_1[1];
    if (puVar2 == (undefined8 *)0x0) goto LAB_14004f577;
  }
  puVar2 = (undefined8 *)*puVar2;
LAB_14004f577:
  if (param_1[2] == puVar2[6]) {
    _invalid_parameter_noinfo();
  }
  lVar1 = *(longlong *)(param_1[2] + 0x20);
  param_1[3] = lVar1;
  if (lVar1 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  uVar3 = FUN_140028430(param_1 + 1);
  return CONCAT71((int7)((ulonglong)uVar3 >> 8),1);
}


// ==== FUN_14004f5e0 @ 14004f5e0  undefined FUN_14004f5e0(undefined8 * param_1)

void FUN_14004f5e0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14004f600 @ 14004f600  undefined8 * FUN_14004f600(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14004f600(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[3];
  *param_2 = 0;
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14004f650 @ 14004f650  undefined8 * FUN_14004f650(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14004f650(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[4];
  *param_2 = 0;
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14004f6a0 @ 14004f6a0  undefined8 * FUN_14004f6a0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14004f6a0(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[3];
  *param_2 = 0;
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14004f6f0 @ 14004f6f0  undefined8 * FUN_14004f6f0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14004f6f0(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[4];
  *param_2 = 0;
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14004f780 @ 14004f780  undefined8 * FUN_14004f780(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14004f780(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (undefined8 *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14004f7e0 @ 14004f7e0  undefined8 * FUN_14004f7e0(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14004f7e0(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (undefined8 *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14004f840 @ 14004f840  undefined8 * FUN_14004f840(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14004f840(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[3];
  *param_2 = 0;
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14004f890 @ 14004f890  undefined8 * FUN_14004f890(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14004f890(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[4];
  *param_2 = 0;
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14004f8e0 @ 14004f8e0  longlong * FUN_14004f8e0(longlong * param_1, longlong * param_2, int * param_3)

longlong * FUN_14004f8e0(longlong *param_1,longlong *param_2,int *param_3)

{
  undefined8 *puVar1;
  longlong *plVar2;
  bool bVar3;
  undefined8 *puVar4;
  longlong local_28;
  undefined8 *local_20;
  
  puVar4 = (undefined8 *)param_1[6];
  bVar3 = true;
  if (*(char *)((longlong)puVar4[1] + 0x125) == '\0') {
    puVar1 = (undefined8 *)puVar4[1];
    do {
      puVar4 = puVar1;
      bVar3 = *param_3 < *(int *)(puVar4 + 3);
      if (bVar3) {
        puVar1 = (undefined8 *)*puVar4;
      }
      else {
        puVar1 = (undefined8 *)puVar4[2];
      }
    } while (*(char *)((longlong)puVar1 + 0x125) == '\0');
  }
  local_28 = *param_1;
  local_20 = puVar4;
  if (bVar3 == false) {
LAB_14004f9a2:
    if (*param_3 <= *(int *)(local_20 + 3)) {
      *(undefined1 *)(param_2 + 2) = 0;
      *param_2 = local_28;
      goto LAB_14004f9cc;
    }
  }
  else {
    puVar1 = *(undefined8 **)param_1[6];
    if (local_28 == 0) {
      _invalid_parameter_noinfo();
    }
    if (puVar4 != puVar1) {
      FUN_14004b670(&local_28);
      goto LAB_14004f9a2;
    }
    bVar3 = true;
  }
  plVar2 = FUN_14004e550(param_1,&local_28,bVar3,puVar4,param_3);
  *(undefined1 *)(param_2 + 2) = 1;
  local_20 = (undefined8 *)plVar2[1];
  *param_2 = *plVar2;
LAB_14004f9cc:
  param_2[1] = (longlong)local_20;
  return param_2;
}


// ==== FUN_14004f9f0 @ 14004f9f0  longlong * FUN_14004f9f0(longlong * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_14004f9f0(longlong *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  longlong lVar1;
  longlong lVar2;
  longlong local_28;
  longlong lStack_20;
  undefined8 local_18 [2];
  
  lVar1 = *(longlong *)param_1[6];
  if ((*param_3 == 0) || (*param_3 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (param_3[1] == lVar1) {
    lVar1 = param_1[6];
    if ((*param_4 == 0) || (*param_4 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    if (param_4[1] == lVar1) {
      FUN_14004ee30((longlong)param_1);
      param_2[1] = *(longlong *)param_1[6];
      *param_2 = *param_1;
      return param_2;
    }
  }
  while( true ) {
    if ((*param_3 == 0) || (*param_3 != *param_4)) {
      _invalid_parameter_noinfo();
    }
    lVar1 = *param_3;
    if (param_3[1] == param_4[1]) break;
    lVar2 = param_3[1];
    FUN_14004b730(param_3);
    local_28 = lVar1;
    lStack_20 = lVar2;
    FUN_14004e9e0(param_1,local_18,&local_28);
  }
  lVar1 = param_3[1];
  *param_2 = *param_1;
  param_2[1] = lVar1;
  return param_2;
}


// ==== FUN_14004fb20 @ 14004fb20  undefined8 * FUN_14004fb20(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14004fb20(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[3];
  *param_2 = 0;
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14004fb70 @ 14004fb70  undefined8 * FUN_14004fb70(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14004fb70(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[4];
  *param_2 = 0;
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14004fbc0 @ 14004fbc0  undefined8 * FUN_14004fbc0(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14004fbc0(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (undefined8 *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14004fc20 @ 14004fc20  undefined8 * FUN_14004fc20(undefined8 * param_1)

undefined8 * FUN_14004fc20(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_14004fc70 @ 14004fc70  undefined8 * FUN_14004fc70(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14004fc70(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (undefined8 *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14004fcd0 @ 14004fcd0  undefined8 * FUN_14004fcd0(undefined8 * param_1, undefined8 param_2, undefined8 param_3)

undefined8 * FUN_14004fcd0(undefined8 *param_1,undefined8 param_2,undefined8 param_3)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_14004f180(param_1,param_2,param_3);
  return param_1;
}


// ==== FUN_14004fcf0 @ 14004fcf0  void * FUN_14004fcf0(undefined8 param_1, void * param_2, longlong param_3, void * param_4)

void * FUN_14004fcf0(undefined8 param_1,void *param_2,longlong param_3,void *param_4)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_3 - (longlong)param_2 >> 2;
  _DstSize = lVar1 * 4;
  if (lVar1 != 0) {
    memmove_s(param_4,_DstSize,param_2,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_4);
}


// ==== FUN_14004fd30 @ 14004fd30  void * FUN_14004fd30(undefined8 param_1, void * param_2, longlong param_3, void * param_4)

void * FUN_14004fd30(undefined8 param_1,void *param_2,longlong param_3,void *param_4)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_3 - (longlong)param_2 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_4,_DstSize,param_2,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_4);
}


// ==== FUN_14004fd70 @ 14004fd70  void * FUN_14004fd70(undefined8 param_1, longlong param_2, longlong param_3, void * param_4)

void * FUN_14004fd70(undefined8 param_1,longlong param_2,longlong param_3,void *param_4)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = *(longlong *)(param_3 + 8) - (longlong)*(void **)(param_2 + 8) >> 2;
  _DstSize = lVar1 * 4;
  if (lVar1 != 0) {
    memmove_s(param_4,_DstSize,*(void **)(param_2 + 8),_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_4);
}


// ==== FUN_14004fe10 @ 14004fe10  undefined FUN_14004fe10(undefined8 param_1, longlong param_2, longlong param_3, undefined8 * param_4)

void FUN_14004fe10(undefined8 param_1,longlong param_2,longlong param_3,undefined8 *param_4)

{
  FUN_14004dab0(*(undefined8 **)(param_2 + 8),*(undefined8 **)(param_3 + 8),param_4);
  return;
}


// ==== FUN_14004fe70 @ 14004fe70  undefined FUN_14004fe70(longlong param_1, longlong param_2)

void FUN_14004fe70(longlong param_1,longlong param_2)

{
  if (param_1 != param_2) {
    do {
      FUN_140067850(param_1);
      param_1 = param_1 + 0x18;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_14004feb0 @ 14004feb0  undefined FUN_14004feb0(undefined8 * param_1, longlong param_2, undefined8 * param_3)

void FUN_14004feb0(undefined8 *param_1,longlong param_2,undefined8 *param_3)

{
  FUN_14004f360(param_1,param_2,param_3);
  return;
}


// ==== FUN_14004ff00 @ 14004ff00  undefined FUN_14004ff00(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

void FUN_14004ff00(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  FUN_14004db40(param_1,param_2,param_3);
  return;
}


// ==== FUN_14004ff20 @ 14004ff20  undefined FUN_14004ff20(undefined8 param_1, undefined8 * param_2, undefined8 * param_3, undefined8 * param_4)

void FUN_14004ff20(undefined8 param_1,undefined8 *param_2,undefined8 *param_3,undefined8 *param_4)

{
  FUN_14004db40(param_2,param_3,param_4);
  return;
}


// ==== FUN_14004ff60 @ 14004ff60  undefined8 * FUN_14004ff60(undefined8 * param_1, uint param_2)

undefined8 * FUN_14004ff60(undefined8 *param_1,uint param_2)

{
  if ((void *)param_1[3] != (void *)0x0) {
    operator_delete((void *)param_1[3]);
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  operator_delete((void *)*param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_14004ffd0 @ 14004ffd0  longlong * FUN_14004ffd0(longlong * param_1, longlong * param_2, int * param_3)

longlong * FUN_14004ffd0(longlong *param_1,longlong *param_2,int *param_3)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong local_28;
  undefined8 *local_20;
  longlong local_18;
  longlong local_10;
  
  puVar4 = (undefined8 *)param_1[6];
  if (*(char *)((longlong)puVar4[1] + 0x125) == '\0') {
    puVar1 = (undefined8 *)puVar4[1];
    do {
      if (*(int *)(puVar1 + 3) < *param_3) {
        puVar2 = (undefined8 *)puVar1[2];
      }
      else {
        puVar2 = (undefined8 *)*puVar1;
        puVar4 = puVar1;
      }
      puVar1 = puVar2;
    } while (*(char *)((longlong)puVar2 + 0x125) == '\0');
  }
  puVar1 = (undefined8 *)param_1[6];
  local_20 = puVar4;
  local_28 = *param_1;
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  if ((puVar4 == puVar1) || (*param_3 < *(int *)(puVar4 + 3))) {
    plVar3 = &local_18;
    local_10 = param_1[6];
    local_18 = *param_1;
  }
  else {
    plVar3 = &local_28;
  }
  *param_2 = *plVar3;
  param_2[1] = plVar3[1];
  return param_2;
}


// ==== FUN_1400500a0 @ 1400500a0  undefined FUN_1400500a0(undefined8 * param_1)

void FUN_1400500a0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_1400500c0 @ 1400500c0  longlong * FUN_1400500c0(longlong * param_1, longlong * param_2, longlong * param_3, int * param_4)

longlong * FUN_1400500c0(longlong *param_1,longlong *param_2,longlong *param_3,int *param_4)

{
  char cVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  int iVar8;
  longlong *plVar9;
  longlong local_38;
  longlong *local_30;
  
  if (param_1[7] == 0) {
    FUN_14004e550(param_1,param_2,'\x01',(undefined8 *)param_1[6],param_4);
  }
  else {
    puVar2 = *(undefined8 **)param_1[6];
    if ((*param_3 == 0) || (*param_3 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    puVar3 = (undefined8 *)param_3[1];
    if (puVar3 == puVar2) {
      if (*param_4 < *(int *)(puVar3 + 3)) {
        FUN_14004e550(param_1,param_2,'\x01',puVar3,param_4);
        return param_2;
      }
    }
    else {
      lVar4 = param_1[6];
      if ((*param_3 == 0) || (*param_3 != *param_1)) {
        _invalid_parameter_noinfo();
      }
      if (param_3[1] == lVar4) {
        if (*(int *)(*(undefined8 **)(param_1[6] + 0x10) + 3) < *param_4) {
          FUN_14004e550(param_1,param_2,'\0',*(undefined8 **)(param_1[6] + 0x10),param_4);
          return param_2;
        }
      }
      else {
        iVar8 = *param_4;
        if (iVar8 < *(int *)(param_3[1] + 0x18)) {
          local_38 = *param_3;
          local_30 = (longlong *)param_3[1];
          FUN_14004b670(&local_38);
          iVar8 = *param_4;
          if ((int)local_30[3] < iVar8) {
            if (*(char *)(local_30[2] + 0x125) != '\0') {
              FUN_14004e550(param_1,param_2,'\0',local_30,param_4);
              return param_2;
            }
            FUN_14004e550(param_1,param_2,'\x01',(undefined8 *)param_3[1],param_4);
            return param_2;
          }
        }
        if (*(int *)(param_3[1] + 0x18) < iVar8) {
          local_38 = *param_3;
          plVar7 = (longlong *)param_1[6];
          local_30 = (longlong *)param_3[1];
          lVar4 = *param_1;
          if (local_38 == 0) {
            _invalid_parameter_noinfo();
          }
          plVar9 = local_30;
          if (*(char *)((longlong)local_30 + 0x125) == '\0') {
            plVar9 = (longlong *)local_30[2];
            if (*(char *)((longlong)plVar9 + 0x125) == '\0') {
              cVar1 = *(char *)(*plVar9 + 0x125);
              plVar5 = (longlong *)*plVar9;
              while (cVar1 == '\0') {
                cVar1 = *(char *)(*plVar5 + 0x125);
                plVar9 = plVar5;
                plVar5 = (longlong *)*plVar5;
              }
            }
            else {
              cVar1 = *(char *)(local_30[1] + 0x125);
              plVar6 = (longlong *)local_30[1];
              plVar5 = local_30;
              while ((plVar9 = plVar6, cVar1 == '\0' && (plVar5 == (longlong *)plVar9[2]))) {
                cVar1 = *(char *)(plVar9[1] + 0x125);
                plVar6 = (longlong *)plVar9[1];
                plVar5 = plVar9;
              }
            }
          }
          else {
            _invalid_parameter_noinfo();
          }
          if ((local_38 == 0) || (local_38 != lVar4)) {
            _invalid_parameter_noinfo();
          }
          if ((plVar9 == plVar7) || (*param_4 < (int)plVar9[3])) {
            if (*(char *)(((undefined8 *)param_3[1])[2] + 0x125) != '\0') {
              FUN_14004e550(param_1,param_2,'\0',(undefined8 *)param_3[1],param_4);
              return param_2;
            }
            FUN_14004e550(param_1,param_2,'\x01',plVar9,param_4);
            return param_2;
          }
        }
      }
    }
    plVar7 = FUN_14004f8e0(param_1,&local_38,param_4);
    *param_2 = *plVar7;
    param_2[1] = plVar7[1];
  }
  return param_2;
}


// ==== FUN_140050360 @ 140050360  undefined FUN_140050360(longlong * param_1)

void FUN_140050360(longlong *param_1)

{
  char cVar1;
  longlong lVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  undefined8 *puStack_40;
  longlong local_38;
  undefined8 *puStack_30;
  undefined8 local_28 [4];
  
  lVar2 = *param_1;
  puVar3 = (undefined8 *)param_1[6];
  puVar7 = (undefined8 *)*puVar3;
  if (lVar2 == 0) {
    _invalid_parameter_noinfo();
  }
  puVar4 = (undefined8 *)param_1[6];
  if ((lVar2 == 0) || (lVar2 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  puStack_40 = puVar7;
  if (puVar3 == puVar4) {
    FUN_14004ee30((longlong)param_1);
  }
  else {
    while( true ) {
      puVar4 = puStack_40;
      if (lVar2 == 0) {
        _invalid_parameter_noinfo();
      }
      if (puVar7 == puVar3) break;
      if (lVar2 == 0) {
        _invalid_parameter_noinfo();
      }
      if (*(char *)((longlong)puVar7 + 0x125) == '\0') {
        puVar5 = (undefined8 *)puVar7[2];
        if (*(char *)((longlong)puVar5 + 0x125) == '\0') {
          cVar1 = *(char *)((longlong)*puVar5 + 0x125);
          puVar7 = puVar5;
          puVar5 = (undefined8 *)*puVar5;
          while (puStack_40 = puVar7, cVar1 == '\0') {
            cVar1 = *(char *)((longlong)*puVar5 + 0x125);
            puVar7 = puVar5;
            puVar5 = (undefined8 *)*puVar5;
          }
        }
        else {
          cVar1 = *(char *)((longlong)puVar7[1] + 0x125);
          puVar6 = (undefined8 *)puVar7[1];
          puVar5 = puVar7;
          while ((puVar7 = puVar6, puStack_40 = puVar7, cVar1 == '\0' &&
                 (puVar5 == (undefined8 *)puVar7[2]))) {
            cVar1 = *(char *)((longlong)puVar7[1] + 0x125);
            puVar6 = (undefined8 *)puVar7[1];
            puVar5 = puVar7;
          }
        }
      }
      else {
        _invalid_parameter_noinfo();
      }
      puStack_30 = puVar4;
      local_38 = lVar2;
      FUN_14004e9e0(param_1,local_28,&local_38);
    }
  }
  operator_delete((void *)param_1[6]);
  param_1[6] = 0;
  param_1[7] = 0;
  return;
}


// ==== FUN_1400504e0 @ 1400504e0  undefined8 * FUN_1400504e0(undefined8 * param_1)

undefined8 * FUN_1400504e0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140050530 @ 140050530  longlong * FUN_140050530(longlong * param_1, longlong * param_2, longlong param_3, longlong param_4)

longlong * FUN_140050530(longlong *param_1,longlong *param_2,longlong param_3,longlong param_4)

{
  rsize_t _DstSize;
  ulonglong uVar1;
  void *_Src;
  void *_Dst;
  longlong lVar2;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (longlong *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  lVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = lVar2;
  _Src = *(void **)(param_4 + 8);
  if ((_Src < (void *)param_1[3]) || ((void *)param_1[4] < _Src)) {
    _invalid_parameter_noinfo();
  }
  if ((*param_2 == 0) || (*param_2 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  _Dst = (void *)param_2[1];
  if (_Dst != _Src) {
    lVar2 = param_1[4] - (longlong)_Src >> 3;
    _DstSize = lVar2 * 8;
    if (0 < lVar2) {
      memmove_s(_Dst,_DstSize,_Src,_DstSize);
    }
    param_1[4] = (longlong)(_DstSize + (longlong)_Dst);
  }
  return param_2;
}


// ==== FUN_140050620 @ 140050620  undefined8 * FUN_140050620(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140050620(undefined8 *param_1,undefined8 *param_2)

{
  code *pcVar1;
  undefined8 *puVar2;
  longlong lVar3;
  void *pvVar4;
  ulonglong uVar5;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined8 local_28;
  ulonglong uStack_20;
  
  puVar2 = (undefined8 *)operator_new(8);
  if (puVar2 == (undefined8 *)0x0) {
    puVar2 = (undefined8 *)0x0;
  }
  else {
    *puVar2 = param_1;
  }
  *param_1 = puVar2;
  uVar5 = (longlong)(param_2[4] - param_2[3]) >> 2;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  if (uVar5 != 0) {
    if (0x3fffffffffffffff < uVar5) {
      FUN_14003eda0();
      pcVar1 = (code *)swi(3);
      puVar2 = (undefined8 *)(*pcVar1)();
      return puVar2;
    }
    lVar3 = FUN_140040370(param_1 + 2,uVar5);
    param_1[3] = lVar3;
    param_1[4] = lVar3;
    param_1[5] = lVar3 + uVar5 * 4;
    uVar5 = param_2[4];
    if (uVar5 < (ulonglong)param_2[3]) {
      _invalid_parameter_noinfo();
    }
    local_58 = (undefined4)*param_2;
    uStack_54 = (undefined4)((ulonglong)*param_2 >> 0x20);
    uStack_50 = (undefined4)uVar5;
    uStack_4c = (undefined4)(uVar5 >> 0x20);
    local_38 = local_58;
    uStack_34 = uStack_54;
    uStack_30 = uStack_50;
    uStack_2c = uStack_4c;
    uVar5 = param_2[3];
    if ((ulonglong)param_2[4] < uVar5) {
      _invalid_parameter_noinfo();
    }
    local_28 = *param_2;
    uStack_20 = uVar5;
    pvVar4 = FUN_14004fd70(param_1,(longlong)&local_28,(longlong)&local_38,(void *)param_1[3]);
    param_1[4] = pvVar4;
  }
  return param_1;
}


// ==== FUN_140050780 @ 140050780  undefined FUN_140050780(undefined8 param_1, longlong param_2, longlong param_3)

void FUN_140050780(undefined8 param_1,longlong param_2,longlong param_3)

{
  if (param_2 != param_3) {
    do {
      FUN_140067850(param_2);
      param_2 = param_2 + 0x18;
    } while (param_2 != param_3);
  }
  return;
}


// ==== FUN_1400507c0 @ 1400507c0  undefined8 * FUN_1400507c0(undefined8 param_1, undefined8 * param_2, longlong param_3, undefined8 * param_4)

undefined8 *
FUN_1400507c0(undefined8 param_1,undefined8 *param_2,longlong param_3,undefined8 *param_4)

{
  FUN_14004f360(param_2,param_3,param_4);
  return param_2 + param_3 * 3;
}


// ==== FUN_140050840 @ 140050840  undefined FUN_140050840(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

void FUN_140050840(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  FUN_14004db40(param_1,param_2,param_3);
  return;
}


// ==== FUN_140050860 @ 140050860  undefined FUN_140050860(undefined8 * param_1, undefined8 * param_2)

void FUN_140050860(undefined8 *param_1,undefined8 *param_2)

{
  if (param_1 != (undefined8 *)0x0) {
    FUN_140050620(param_1,param_2);
  }
  return;
}


// ==== FUN_140050890 @ 140050890  undefined FUN_140050890(undefined8 * param_1)

void FUN_140050890(undefined8 *param_1)

{
  if ((void *)param_1[3] != (void *)0x0) {
    operator_delete((void *)param_1[3]);
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_1400508d0 @ 1400508d0  longlong FUN_1400508d0(longlong * param_1, int * param_2)

longlong FUN_1400508d0(longlong *param_1,int *param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong *plVar5;
  longlong lVar6;
  longlong *local_248;
  undefined8 *puStack_240;
  longlong local_238 [2];
  int local_228;
  undefined1 local_224 [264];
  undefined1 local_11c [276];
  
  puVar4 = (undefined8 *)param_1[6];
  if (*(char *)((longlong)puVar4[1] + 0x125) == '\0') {
    puVar1 = (undefined8 *)puVar4[1];
    do {
      if (*(int *)(puVar1 + 3) < *param_2) {
        puVar2 = (undefined8 *)puVar1[2];
      }
      else {
        puVar2 = (undefined8 *)*puVar1;
        puVar4 = puVar1;
      }
      puVar1 = puVar2;
    } while (*(char *)((longlong)puVar2 + 0x125) == '\0');
  }
  plVar5 = (longlong *)*param_1;
  puVar1 = (undefined8 *)param_1[6];
  if (plVar5 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  if ((puVar4 == puVar1) || (*param_2 < *(int *)(puVar4 + 3))) {
    memset(local_11c,0,0x108);
    local_228 = *param_2;
    local_248 = plVar5;
    puStack_240 = puVar4;
    memcpy(local_224,local_11c,0x108);
    plVar3 = FUN_1400500c0(param_1,local_238,(longlong *)&local_248,&local_228);
    plVar5 = (longlong *)*plVar3;
    puVar4 = (undefined8 *)plVar3[1];
  }
  if (plVar5 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar6 = 0;
  }
  else {
    lVar6 = *plVar5;
  }
  if (puVar4 == *(undefined8 **)(lVar6 + 0x30)) {
    _invalid_parameter_noinfo();
  }
  return (longlong)puVar4 + 0x1c;
}


// ==== FUN_140050a10 @ 140050a10  undefined FUN_140050a10(longlong * param_1)

void FUN_140050a10(longlong *param_1)

{
  FUN_140050360(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140050a40 @ 140050a40  undefined8 * FUN_140050a40(undefined8 * param_1)

undefined8 * FUN_140050a40(undefined8 *param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  lVar2 = FUN_14004d3a0();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x125) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_140050ac0 @ 140050ac0  undefined FUN_140050ac0(longlong param_1, longlong param_2, ulonglong param_3, undefined4 * param_4)

void FUN_140050ac0(longlong param_1,longlong param_2,ulonglong param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  code *pcVar2;
  void *pvVar3;
  longlong lVar4;
  ulonglong uVar5;
  undefined4 *puVar6;
  longlong lVar7;
  rsize_t rVar8;
  ulonglong uVar9;
  void *pvVar10;
  ulonglong uVar11;
  undefined4 *puVar12;
  
  lVar4 = *(longlong *)(param_1 + 0x18);
  if (lVar4 == 0) {
    uVar5 = 0;
  }
  else {
    uVar5 = *(longlong *)(param_1 + 0x28) - lVar4 >> 2;
  }
  uVar9 = 0;
  if (param_3 != 0) {
    lVar7 = *(longlong *)(param_1 + 0x20);
    lVar4 = lVar7 - lVar4 >> 2;
    if (0x3fffffffffffffffU - lVar4 < param_3) {
      FUN_14003eda0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    uVar11 = param_3 + lVar4;
    if (uVar5 < uVar11) {
      if (uVar5 <= 0x3fffffffffffffff - (uVar5 >> 1)) {
        uVar9 = uVar5 + (uVar5 >> 1);
      }
      if (uVar9 < uVar11) {
        uVar9 = uVar11;
      }
      pvVar3 = (void *)FUN_140040370(param_1 + 0x10,uVar9);
      lVar4 = *(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18) >> 2;
      puVar6 = (undefined4 *)((longlong)pvVar3 + lVar4 * 4);
      for (uVar5 = param_3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *puVar6 = *param_4;
        puVar6 = puVar6 + 1;
      }
      lVar7 = *(longlong *)(param_2 + 8) - (longlong)*(void **)(param_1 + 0x18) >> 2;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 2;
        memmove_s(pvVar3,rVar8,*(void **)(param_1 + 0x18),rVar8);
      }
      lVar7 = *(longlong *)(param_1 + 0x20) - (longlong)*(void **)(param_2 + 8) >> 2;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 2;
        memmove_s((void *)((longlong)pvVar3 + (lVar4 + param_3) * 4),rVar8,*(void **)(param_2 + 8),
                  rVar8);
      }
      pvVar10 = *(void **)(param_1 + 0x18);
      lVar4 = *(longlong *)(param_1 + 0x20);
      if (pvVar10 != (void *)0x0) {
        operator_delete(pvVar10);
      }
      *(void **)(param_1 + 0x28) = (void *)((longlong)pvVar3 + uVar9 * 4);
      *(void **)(param_1 + 0x20) =
           (void *)((longlong)pvVar3 + (param_3 + (lVar4 - (longlong)pvVar10 >> 2)) * 4);
      *(void **)(param_1 + 0x18) = pvVar3;
    }
    else if ((ulonglong)(lVar7 - *(longlong *)(param_2 + 8) >> 2) < param_3) {
      uVar1 = *param_4;
      FUN_14004fcf0(param_1,*(void **)(param_2 + 8),lVar7,
                    (void *)((longlong)*(void **)(param_2 + 8) + param_3 * 4));
      puVar6 = *(undefined4 **)(param_1 + 0x20);
      for (lVar4 = param_3 - ((longlong)puVar6 - *(longlong *)(param_2 + 8) >> 2); lVar4 != 0;
          lVar4 = lVar4 + -1) {
        *puVar6 = uVar1;
        puVar6 = puVar6 + 1;
      }
      *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + param_3 * 4;
      lVar4 = *(longlong *)(param_1 + 0x20);
      for (puVar6 = *(undefined4 **)(param_2 + 8); puVar6 != (undefined4 *)(lVar4 + param_3 * -4);
          puVar6 = puVar6 + 1) {
        *puVar6 = uVar1;
      }
    }
    else {
      uVar1 = *param_4;
      pvVar10 = (void *)(lVar7 + param_3 * -4);
      pvVar3 = FUN_14004fcf0(param_1,pvVar10,lVar7,(void *)lVar7);
      *(void **)(param_1 + 0x20) = pvVar3;
      FUN_14004d790(*(void **)(param_2 + 8),(longlong)pvVar10,lVar7);
      puVar12 = *(undefined4 **)(param_2 + 8);
      puVar6 = puVar12 + param_3;
      for (; puVar12 != puVar6; puVar12 = puVar12 + 1) {
        *puVar12 = uVar1;
      }
    }
  }
  return;
}


// ==== FUN_140050d60 @ 140050d60  longlong * FUN_140050d60(longlong * param_1, longlong * param_2, longlong param_3, longlong param_4)

longlong * FUN_140050d60(longlong *param_1,longlong *param_2,longlong param_3,longlong param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  undefined8 *puVar3;
  longlong lVar4;
  longlong lVar5;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (longlong *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  lVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = lVar2;
  puVar3 = *(undefined8 **)(param_4 + 8);
  if ((puVar3 < (undefined8 *)param_1[3]) || ((undefined8 *)param_1[4] < puVar3)) {
    _invalid_parameter_noinfo();
  }
  if ((*param_2 == 0) || (*param_2 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if ((undefined8 *)param_2[1] != puVar3) {
    lVar4 = FUN_14004d7d0(puVar3,(undefined8 *)param_1[4],param_2[1]);
    lVar2 = param_1[4];
    for (lVar5 = lVar4; lVar5 != lVar2; lVar5 = lVar5 + 0x18) {
      FUN_140067850(lVar5);
    }
    param_1[4] = lVar4;
  }
  return param_2;
}


// ==== FUN_140050e60 @ 140050e60  undefined FUN_140050e60(longlong param_1)

void FUN_140050e60(longlong param_1)

{
  longlong lVar1;
  longlong lVar2;
  
  lVar2 = *(longlong *)(param_1 + 0x18);
  if (lVar2 != 0) {
    lVar1 = *(longlong *)(param_1 + 0x20);
    for (; lVar2 != lVar1; lVar2 = lVar2 + 0x18) {
      FUN_140067850(lVar2);
    }
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_140050ec0 @ 140050ec0  undefined FUN_140050ec0(longlong param_1, longlong param_2, ulonglong param_3, undefined8 * param_4)

void FUN_140050ec0(longlong param_1,longlong param_2,ulonglong param_3,undefined8 *param_4)

{
  undefined8 uVar1;
  code *pcVar2;
  void *pvVar3;
  longlong lVar4;
  ulonglong uVar5;
  undefined8 *puVar6;
  longlong lVar7;
  rsize_t rVar8;
  ulonglong uVar9;
  void *pvVar10;
  ulonglong uVar11;
  undefined8 *puVar12;
  
  lVar4 = *(longlong *)(param_1 + 0x18);
  if (lVar4 == 0) {
    uVar5 = 0;
  }
  else {
    uVar5 = *(longlong *)(param_1 + 0x28) - lVar4 >> 3;
  }
  uVar9 = 0;
  if (param_3 != 0) {
    lVar7 = *(longlong *)(param_1 + 0x20);
    lVar4 = lVar7 - lVar4 >> 3;
    if (0x1fffffffffffffffU - lVar4 < param_3) {
      FUN_140049bd0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    uVar11 = param_3 + lVar4;
    if (uVar5 < uVar11) {
      if (uVar5 <= 0x1fffffffffffffff - (uVar5 >> 1)) {
        uVar9 = uVar5 + (uVar5 >> 1);
      }
      if (uVar9 < uVar11) {
        uVar9 = uVar11;
      }
      pvVar3 = (void *)FUN_14004b7e0(param_1 + 0x10,uVar9);
      lVar4 = *(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18) >> 3;
      puVar6 = (undefined8 *)((longlong)pvVar3 + lVar4 * 8);
      for (uVar5 = param_3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *puVar6 = *param_4;
        puVar6 = puVar6 + 1;
      }
      lVar7 = *(longlong *)(param_2 + 8) - (longlong)*(void **)(param_1 + 0x18) >> 3;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 3;
        memmove_s(pvVar3,rVar8,*(void **)(param_1 + 0x18),rVar8);
      }
      lVar7 = *(longlong *)(param_1 + 0x20) - (longlong)*(void **)(param_2 + 8) >> 3;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 3;
        memmove_s((void *)((longlong)pvVar3 + (lVar4 + param_3) * 8),rVar8,*(void **)(param_2 + 8),
                  rVar8);
      }
      pvVar10 = *(void **)(param_1 + 0x18);
      lVar4 = *(longlong *)(param_1 + 0x20);
      if (pvVar10 != (void *)0x0) {
        operator_delete(pvVar10);
      }
      *(void **)(param_1 + 0x28) = (void *)((longlong)pvVar3 + uVar9 * 8);
      *(void **)(param_1 + 0x20) =
           (void *)((longlong)pvVar3 + (param_3 + (lVar4 - (longlong)pvVar10 >> 3)) * 8);
      *(void **)(param_1 + 0x18) = pvVar3;
    }
    else if ((ulonglong)(lVar7 - *(longlong *)(param_2 + 8) >> 3) < param_3) {
      uVar1 = *param_4;
      FUN_14004fd30(param_1,*(void **)(param_2 + 8),lVar7,
                    (void *)((longlong)*(void **)(param_2 + 8) + param_3 * 8));
      puVar6 = *(undefined8 **)(param_1 + 0x20);
      for (lVar4 = param_3 - ((longlong)puVar6 - *(longlong *)(param_2 + 8) >> 3); lVar4 != 0;
          lVar4 = lVar4 + -1) {
        *puVar6 = uVar1;
        puVar6 = puVar6 + 1;
      }
      *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + param_3 * 8;
      lVar4 = *(longlong *)(param_1 + 0x20);
      for (puVar6 = *(undefined8 **)(param_2 + 8); puVar6 != (undefined8 *)(lVar4 + param_3 * -8);
          puVar6 = puVar6 + 1) {
        *puVar6 = uVar1;
      }
    }
    else {
      uVar1 = *param_4;
      pvVar10 = (void *)(lVar7 + param_3 * -8);
      pvVar3 = FUN_14004fd30(param_1,pvVar10,lVar7,(void *)lVar7);
      *(void **)(param_1 + 0x20) = pvVar3;
      FUN_14004d8f0(*(void **)(param_2 + 8),(longlong)pvVar10,lVar7);
      puVar12 = *(undefined8 **)(param_2 + 8);
      puVar6 = puVar12 + param_3;
      for (; puVar12 != puVar6; puVar12 = puVar12 + 1) {
        *puVar12 = uVar1;
      }
    }
  }
  return;
}


// ==== FUN_140051170 @ 140051170  undefined8 * FUN_140051170(undefined8 * param_1, longlong param_2)

undefined8 * FUN_140051170(undefined8 *param_1,longlong param_2)

{
  undefined8 *puVar1;
  code *pcVar2;
  undefined8 *puVar3;
  longlong lVar4;
  ulonglong uVar5;
  
  puVar3 = (undefined8 *)operator_new(8);
  if (puVar3 == (undefined8 *)0x0) {
    puVar3 = (undefined8 *)0x0;
  }
  else {
    *puVar3 = param_1;
  }
  *param_1 = puVar3;
  lVar4 = *(longlong *)(param_2 + 0x20) - *(longlong *)(param_2 + 0x18);
  lVar4 = lVar4 / 6 + (lVar4 >> 0x3f);
  uVar5 = (lVar4 >> 2) - (lVar4 >> 0x3f);
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  if (uVar5 != 0) {
    if (0xaaaaaaaaaaaaaaa < uVar5) {
      FUN_140049a50();
      pcVar2 = (code *)swi(3);
      puVar3 = (undefined8 *)(*pcVar2)();
      return puVar3;
    }
    lVar4 = FUN_14004b590(param_1 + 2,uVar5);
    param_1[3] = lVar4;
    param_1[4] = lVar4;
    param_1[5] = lVar4 + uVar5 * 0x18;
    puVar3 = *(undefined8 **)(param_2 + 0x20);
    if (puVar3 < *(undefined8 **)(param_2 + 0x18)) {
      _invalid_parameter_noinfo();
    }
    puVar1 = *(undefined8 **)(param_2 + 0x18);
    if (*(undefined8 **)(param_2 + 0x20) < puVar1) {
      _invalid_parameter_noinfo();
    }
    puVar3 = FUN_14004dab0(puVar1,puVar3,(undefined8 *)param_1[3]);
    param_1[4] = puVar3;
  }
  return param_1;
}


// ==== FUN_1400512e0 @ 1400512e0  undefined FUN_1400512e0(undefined8 param_1, undefined8 * param_2, undefined8 * param_3, undefined8 * param_4)

void FUN_1400512e0(undefined8 param_1,undefined8 *param_2,undefined8 *param_3,undefined8 *param_4)

{
  FUN_14004db40(param_2,param_3,param_4);
  return;
}


// ==== FUN_140051320 @ 140051320  undefined FUN_140051320(undefined8 param_1, undefined8 * param_2, undefined8 * param_3)

void FUN_140051320(undefined8 param_1,undefined8 *param_2,undefined8 *param_3)

{
  if (param_2 != (undefined8 *)0x0) {
    FUN_140050620(param_2,param_3);
  }
  return;
}


// ==== FUN_140051360 @ 140051360  undefined FUN_140051360(undefined8 param_1, undefined8 * param_2)

void FUN_140051360(undefined8 param_1,undefined8 *param_2)

{
  if ((void *)param_2[3] != (void *)0x0) {
    operator_delete((void *)param_2[3]);
  }
  param_2[3] = 0;
  param_2[4] = 0;
  param_2[5] = 0;
  operator_delete((void *)*param_2);
  return;
}


// ==== FUN_1400513a0 @ 1400513a0  undefined FUN_1400513a0(longlong * param_1)

void FUN_1400513a0(longlong *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  
  puVar1 = (undefined8 *)param_1[4];
  if (puVar1 < (undefined8 *)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  puVar2 = (undefined8 *)param_1[3];
  if ((undefined8 *)param_1[4] < puVar2) {
    _invalid_parameter_noinfo();
  }
  if ((puVar2 < (undefined8 *)param_1[3]) || ((undefined8 *)param_1[4] < puVar2)) {
    _invalid_parameter_noinfo();
  }
  lVar3 = *param_1;
  if ((puVar1 < (undefined8 *)param_1[3]) || ((undefined8 *)param_1[4] < puVar1)) {
    _invalid_parameter_noinfo();
  }
  if ((lVar3 == 0) || (lVar3 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (puVar2 != puVar1) {
    lVar4 = FUN_14004d7d0(puVar1,(undefined8 *)param_1[4],(longlong)puVar2);
    lVar3 = param_1[4];
    for (lVar5 = lVar4; lVar5 != lVar3; lVar5 = lVar5 + 0x18) {
      FUN_140067850(lVar5);
    }
    param_1[4] = lVar4;
  }
  return;
}


// ==== FUN_1400514b0 @ 1400514b0  undefined FUN_1400514b0(undefined8 * param_1, longlong param_2)

void FUN_1400514b0(undefined8 *param_1,longlong param_2)

{
  if (param_1 != (undefined8 *)0x0) {
    FUN_140051170(param_1,param_2);
  }
  return;
}


// ==== FUN_1400514e0 @ 1400514e0  undefined FUN_1400514e0(longlong * param_1, longlong * param_2)

void FUN_1400514e0(longlong *param_1,longlong *param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  
  if (param_1 != param_2) {
    puVar1 = (undefined8 *)*param_1;
    *param_1 = *param_2;
    *param_2 = (longlong)puVar1;
    puVar2 = (undefined8 *)*param_1;
    if (puVar2 != puVar1) {
      uVar3 = *puVar2;
      *puVar2 = *puVar1;
      *puVar1 = uVar3;
    }
    plVar5 = param_2 + 3;
    plVar6 = param_1 + 3;
    if (plVar6 != plVar5) {
      lVar4 = *plVar6;
      *plVar6 = *plVar5;
      *plVar5 = lVar4;
    }
    plVar5 = param_2 + 4;
    plVar6 = param_1 + 4;
    if (plVar6 != plVar5) {
      lVar4 = *plVar6;
      *plVar6 = *plVar5;
      *plVar5 = lVar4;
    }
    plVar6 = param_2 + 5;
    plVar5 = param_1 + 5;
    if (plVar5 != plVar6) {
      lVar4 = *plVar5;
      *plVar5 = *plVar6;
      *plVar6 = lVar4;
    }
  }
  return;
}


// ==== FUN_140051570 @ 140051570  undefined FUN_140051570(longlong * param_1)

void FUN_140051570(longlong *param_1)

{
  FUN_140050360(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_1400515a0 @ 1400515a0  undefined FUN_1400515a0(uint param_1)

/* WARNING: Type propagation algorithm not settling */

void FUN_1400515a0(uint param_1)

{
  int *piVar1;
  char cVar2;
  ulonglong *puVar3;
  ulonglong *puVar4;
  FILE *_File;
  void *_Dst;
  ulonglong *puVar5;
  undefined8 *puVar6;
  ulonglong **ppuVar7;
  ulonglong *puVar8;
  uint uVar9;
  ulonglong uVar11;
  undefined1 auStack_1a8 [32];
  int local_188;
  int local_184 [3];
  ulonglong *local_178;
  ulonglong *local_170;
  ulonglong *local_168;
  ulonglong *local_160;
  ulonglong *local_158;
  ulonglong *local_150;
  undefined8 local_148;
  undefined1 local_138 [4];
  undefined1 local_134 [268];
  ulonglong local_28;
  ulonglong uVar10;
  
  local_148 = 0xfffffffffffffffe;
  local_28 = DAT_140103510 ^ (ulonglong)auStack_1a8;
  uVar11 = 0;
  if (DAT_140104668 == 0) {
    _File = fopen("ini/GameMap.dat","rb");
    if (_File == (FILE *)0x0) {
      log_InlineLogERROR("IMapData cannot open file %s");
      goto LAB_1400518ae;
    }
    local_178 = (ulonglong *)0x0;
    local_170 = (ulonglong *)0x0;
    FUN_14004f180(&local_178,_File,fclose_exref);
    local_184[0] = 0;
    local_184[1] = 0;
    local_188 = 0;
    fread(local_184,4,1,_File);
    uVar10 = uVar11;
    if (0 < local_184[0]) {
      do {
        fread(local_184 + 1,4,1,_File);
        fread(&local_188,4,1,_File);
        fread(local_134,1,(longlong)local_188,_File);
        local_134[local_188] = 0;
        fread(local_138,4,1,_File);
        _Dst = (void *)FUN_1400508d0((longlong *)&DAT_140104630,local_184 + 1);
        memcpy(_Dst,local_138,0x108);
        uVar9 = (int)uVar10 + 1;
        uVar10 = (ulonglong)uVar9;
      } while ((int)uVar9 < local_184[0]);
    }
    puVar5 = local_170;
    if (local_170 != (ulonglong *)0x0) {
      LOCK();
      puVar3 = local_170 + 2;
      *(int *)puVar3 = (int)*puVar3 + -1;
      UNLOCK();
      if ((int)*puVar3 == 0) {
        (**(code **)*local_170)(local_170);
        LOCK();
        piVar1 = (int *)((longlong)puVar5 + 0x14);
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (*piVar1 == 0) {
          (**(code **)(*local_170 + 8))();
        }
      }
    }
  }
  puVar4 = DAT_140104660;
  cVar2 = *(char *)((longlong)DAT_140104660[1] + 0x125);
  puVar5 = (ulonglong *)DAT_140104660[1];
  puVar3 = DAT_140104660;
  while (puVar8 = puVar5, cVar2 == '\0') {
    if ((int)puVar8[3] < (int)param_1) {
      puVar5 = (ulonglong *)puVar8[2];
      puVar8 = puVar3;
    }
    else {
      puVar5 = (ulonglong *)*puVar8;
    }
    cVar2 = *(char *)((longlong)puVar5 + 0x125);
    puVar3 = puVar8;
  }
  local_150 = puVar3;
  local_158 = DAT_140104630;
  if (DAT_140104630 == (ulonglong *)0x0) {
    _invalid_parameter_noinfo();
  }
  puVar5 = DAT_140104660;
  if ((puVar3 == puVar4) || ((int)param_1 < (int)puVar3[3])) {
    local_160 = DAT_140104660;
    local_168 = DAT_140104630;
    ppuVar7 = &local_168;
  }
  else {
    ppuVar7 = &local_158;
  }
  puVar3 = *ppuVar7;
  local_170 = ppuVar7[1];
  local_178 = puVar3;
  if ((puVar3 == (ulonglong *)0x0) || (puVar3 != DAT_140104630)) {
    _invalid_parameter_noinfo();
  }
  puVar4 = local_170;
  if (local_170 == puVar5) {
    log_InlineLogERROR("IMapData cannot find map %d");
  }
  else {
    if (puVar3 == (ulonglong *)0x0) {
      _invalid_parameter_noinfo();
      uVar10 = uVar11;
    }
    else {
      uVar10 = *puVar3;
    }
    if (puVar4 == *(ulonglong **)(uVar10 + 0x30)) {
      _invalid_parameter_noinfo();
    }
    if (puVar3 == (ulonglong *)0x0) {
      _invalid_parameter_noinfo();
      uVar10 = uVar11;
    }
    else {
      uVar10 = *puVar3;
    }
    if (puVar4 == *(ulonglong **)(uVar10 + 0x30)) {
      _invalid_parameter_noinfo();
    }
    puVar6 = FUN_14008ba00(param_1,(char *)(puVar4 + 4),*(int *)((longlong)puVar4 + 0x1c));
    if (puVar6 == (undefined8 *)0x0) {
      if (puVar3 == (ulonglong *)0x0) {
        _invalid_parameter_noinfo();
        uVar10 = uVar11;
      }
      else {
        uVar10 = *puVar3;
      }
      if (puVar4 == *(ulonglong **)(uVar10 + 0x30)) {
        _invalid_parameter_noinfo();
      }
      if (puVar3 == (ulonglong *)0x0) {
        _invalid_parameter_noinfo();
      }
      else {
        uVar11 = *puVar3;
      }
      if (puVar4 == *(ulonglong **)(uVar11 + 0x30)) {
        _invalid_parameter_noinfo();
      }
      log_InlineLogERROR("IMapData cannot create map %d from file %s, gridsize=%d");
    }
  }
LAB_1400518ae:
  __security_check_cookie(local_28 ^ (ulonglong)auStack_1a8);
  return;
}


// ==== FUN_1400518e0 @ 1400518e0  undefined8 * FUN_1400518e0(undefined8 * param_1)

undefined8 * FUN_1400518e0(undefined8 *param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  lVar2 = FUN_14004d3a0();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x125) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_140051960 @ 140051960  undefined FUN_140051960(longlong * param_1, ulonglong param_2, undefined4 param_3)

void FUN_140051960(longlong *param_1,ulonglong param_2,undefined4 param_3)

{
  rsize_t _DstSize;
  void *_Src;
  void *pvVar1;
  longlong *plVar2;
  ulonglong uVar3;
  longlong lVar4;
  longlong lVar5;
  undefined4 local_res18 [2];
  longlong local_28;
  void *pvStack_20;
  
  _Src = (void *)param_1[4];
  pvVar1 = (void *)param_1[3];
  uVar3 = (longlong)_Src - (longlong)pvVar1 >> 2;
  local_res18[0] = param_3;
  if (uVar3 < param_2) {
    if (_Src < pvVar1) {
      _invalid_parameter_noinfo();
    }
    local_28 = *param_1;
    pvStack_20 = _Src;
    FUN_140050ac0((longlong)param_1,(longlong)&local_28,param_2 - (param_1[4] - param_1[3] >> 2),
                  local_res18);
    return;
  }
  if (uVar3 <= param_2) {
    return;
  }
  if (_Src < pvVar1) {
    _invalid_parameter_noinfo();
  }
  uVar3 = param_1[3];
  if ((ulonglong)param_1[4] < uVar3) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)*param_1;
  lVar4 = 0;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar4;
  }
  else {
    lVar5 = *plVar2;
  }
  pvVar1 = (void *)(uVar3 + param_2 * 4);
  if (pvVar1 <= *(void **)(lVar5 + 0x20)) {
    if (plVar2 != (longlong *)0x0) {
      lVar4 = *plVar2;
    }
    if (*(void **)(lVar4 + 0x18) <= pvVar1) goto LAB_140051a47;
  }
  _invalid_parameter_noinfo();
LAB_140051a47:
  if ((pvVar1 < (void *)param_1[3]) || ((void *)param_1[4] < pvVar1)) {
    _invalid_parameter_noinfo();
  }
  lVar4 = *param_1;
  if ((_Src < (void *)param_1[3]) || ((void *)param_1[4] < _Src)) {
    _invalid_parameter_noinfo();
  }
  if ((lVar4 == 0) || (lVar4 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (pvVar1 != _Src) {
    lVar4 = param_1[4] - (longlong)_Src >> 2;
    _DstSize = lVar4 * 4;
    if (0 < lVar4) {
      memmove_s(pvVar1,_DstSize,_Src,_DstSize);
    }
    param_1[4] = (longlong)(_DstSize + (longlong)pvVar1);
  }
  return;
}


// ==== FUN_140051ad0 @ 140051ad0  undefined FUN_140051ad0(undefined8 * param_1)

void FUN_140051ad0(undefined8 *param_1)

{
  longlong lVar1;
  longlong lVar2;
  
  lVar2 = param_1[3];
  if (lVar2 != 0) {
    lVar1 = param_1[4];
    for (; lVar2 != lVar1; lVar2 = lVar2 + 0x18) {
      FUN_140067850(lVar2);
    }
    operator_delete((void *)param_1[3]);
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140051b50 @ 140051b50  undefined FUN_140051b50(longlong * param_1, ulonglong param_2, undefined8 param_3)

void FUN_140051b50(longlong *param_1,ulonglong param_2,undefined8 param_3)

{
  rsize_t _DstSize;
  void *_Src;
  void *pvVar1;
  longlong *plVar2;
  ulonglong uVar3;
  longlong lVar4;
  longlong lVar5;
  undefined8 local_res18;
  longlong local_28;
  void *pvStack_20;
  
  _Src = (void *)param_1[4];
  pvVar1 = (void *)param_1[3];
  uVar3 = (longlong)_Src - (longlong)pvVar1 >> 3;
  local_res18 = param_3;
  if (uVar3 < param_2) {
    if (_Src < pvVar1) {
      _invalid_parameter_noinfo();
    }
    local_28 = *param_1;
    pvStack_20 = _Src;
    FUN_140050ec0((longlong)param_1,(longlong)&local_28,param_2 - (param_1[4] - param_1[3] >> 3),
                  &local_res18);
    return;
  }
  if (uVar3 <= param_2) {
    return;
  }
  if (_Src < pvVar1) {
    _invalid_parameter_noinfo();
  }
  uVar3 = param_1[3];
  if ((ulonglong)param_1[4] < uVar3) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)*param_1;
  lVar4 = 0;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar4;
  }
  else {
    lVar5 = *plVar2;
  }
  pvVar1 = (void *)(uVar3 + param_2 * 8);
  if (pvVar1 <= *(void **)(lVar5 + 0x20)) {
    if (plVar2 != (longlong *)0x0) {
      lVar4 = *plVar2;
    }
    if (*(void **)(lVar4 + 0x18) <= pvVar1) goto LAB_140051c37;
  }
  _invalid_parameter_noinfo();
LAB_140051c37:
  if ((pvVar1 < (void *)param_1[3]) || ((void *)param_1[4] < pvVar1)) {
    _invalid_parameter_noinfo();
  }
  lVar4 = *param_1;
  if ((_Src < (void *)param_1[3]) || ((void *)param_1[4] < _Src)) {
    _invalid_parameter_noinfo();
  }
  if ((lVar4 == 0) || (lVar4 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (pvVar1 != _Src) {
    lVar4 = param_1[4] - (longlong)_Src >> 3;
    _DstSize = lVar4 * 8;
    if (0 < lVar4) {
      memmove_s(pvVar1,_DstSize,_Src,_DstSize);
    }
    param_1[4] = (longlong)(_DstSize + (longlong)pvVar1);
  }
  return;
}


// ==== FUN_140051cc0 @ 140051cc0  undefined FUN_140051cc0(longlong param_1, longlong param_2, ulonglong param_3, undefined8 * param_4)

void FUN_140051cc0(longlong param_1,longlong param_2,ulonglong param_3,undefined8 *param_4)

{
  ulonglong uVar1;
  code *pcVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  longlong lVar5;
  longlong lVar6;
  ulonglong uVar7;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  
  lVar6 = *(longlong *)(param_1 + 0x18);
  if (lVar6 == 0) {
    uVar7 = 0;
  }
  else {
    lVar5 = *(longlong *)(param_1 + 0x28) - lVar6;
    lVar5 = lVar5 / 6 + (lVar5 >> 0x3f);
    uVar7 = (lVar5 >> 2) - (lVar5 >> 0x3f);
  }
  if (param_3 != 0) {
    lVar6 = (*(longlong *)(param_1 + 0x20) - lVar6) / 0x18;
    if (0xaaaaaaaaaaaaaaaU - lVar6 < param_3) {
      FUN_140049a50();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    uVar1 = lVar6 + param_3;
    if (uVar7 < uVar1) {
      if (0xaaaaaaaaaaaaaaa - (uVar7 >> 1) < uVar7) {
        uVar7 = 0;
      }
      else {
        uVar7 = uVar7 + (uVar7 >> 1);
      }
      if (uVar7 < uVar1) {
        uVar7 = uVar1;
      }
      puVar3 = (undefined8 *)FUN_14004b590(param_1 + 0x10,uVar7);
      lVar6 = *(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18);
      lVar6 = lVar6 / 6 + (lVar6 >> 0x3f);
      lVar6 = (lVar6 >> 2) - (lVar6 >> 0x3f);
      FUN_14004f360(puVar3 + lVar6 * 3,param_3,param_4);
      FUN_14004db40(*(undefined8 **)(param_1 + 0x18),*(undefined8 **)(param_2 + 8),puVar3);
      FUN_14004db40(*(undefined8 **)(param_2 + 8),*(undefined8 **)(param_1 + 0x20),
                    puVar3 + (lVar6 + param_3) * 3);
      lVar6 = *(longlong *)(param_1 + 0x18);
      lVar5 = *(longlong *)(param_1 + 0x20);
      if (lVar6 != 0) {
        FUN_140050780(param_1,lVar6,*(longlong *)(param_1 + 0x20));
        operator_delete(*(void **)(param_1 + 0x18));
      }
      *(undefined8 **)(param_1 + 0x28) = puVar3 + uVar7 * 3;
      *(undefined8 **)(param_1 + 0x20) = puVar3 + (param_3 + (lVar5 - lVar6) / 0x18) * 3;
      *(undefined8 **)(param_1 + 0x18) = puVar3;
    }
    else if ((ulonglong)((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_2 + 8)) / 0x18) <
             param_3) {
      local_58 = *param_4;
      local_50 = param_4[1];
      local_48 = param_4[2];
      FUN_14004db40(*(undefined8 **)(param_2 + 8),*(undefined8 **)(param_1 + 0x20),
                    *(undefined8 **)(param_2 + 8) + param_3 * 3);
      FUN_14004f360(*(undefined8 **)(param_1 + 0x20),
                    param_3 - ((longlong)*(undefined8 **)(param_1 + 0x20) -
                              *(longlong *)(param_2 + 8)) / 0x18,&local_58);
      *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + param_3 * 0x18;
      lVar6 = *(longlong *)(param_1 + 0x20);
      for (puVar3 = *(undefined8 **)(param_2 + 8); puVar3 != (undefined8 *)(lVar6 + param_3 * -0x18)
          ; puVar3 = puVar3 + 3) {
        *puVar3 = local_58;
        puVar3[1] = local_50;
        puVar3[2] = local_48;
      }
      FUN_140067850((longlong)&local_58);
    }
    else {
      local_58 = *param_4;
      local_50 = param_4[1];
      local_48 = param_4[2];
      puVar3 = *(undefined8 **)(param_1 + 0x20);
      puVar4 = FUN_14004db40(puVar3 + param_3 * -3,puVar3,puVar3);
      *(undefined8 **)(param_1 + 0x20) = puVar4;
      FUN_14004f110(*(longlong *)(param_2 + 8),(longlong)(puVar3 + param_3 * -3),(longlong)puVar3);
      puVar4 = *(undefined8 **)(param_2 + 8);
      puVar3 = puVar4 + param_3 * 3;
      for (; puVar4 != puVar3; puVar4 = puVar4 + 3) {
        *puVar4 = local_58;
        puVar4[1] = local_50;
        puVar4[2] = local_48;
      }
      FUN_140067850((longlong)&local_58);
    }
  }
  return;
}


// ==== FUN_1400520b0 @ 1400520b0  longlong FUN_1400520b0(longlong * param_1, longlong * param_2, longlong param_3)

longlong FUN_1400520b0(longlong *param_1,longlong *param_2,longlong param_3)

{
  longlong lVar1;
  longlong lVar2;
  
  lVar2 = (longlong)param_2 - (longlong)param_1;
  if (param_1 != param_2) {
    lVar1 = param_3 - (longlong)param_1;
    do {
      FUN_1400447b0((longlong *)(lVar1 + (longlong)param_1),param_1);
      param_1 = param_1 + 6;
    } while (param_1 != param_2);
  }
  return (lVar2 / 0x30) * 0x30 + param_3;
}


// ==== FUN_140052130 @ 140052130  undefined FUN_140052130(undefined8 * param_1, undefined8 * param_2)

void FUN_140052130(undefined8 *param_1,undefined8 *param_2)

{
  if (param_1 != param_2) {
    do {
      if ((void *)param_1[3] != (void *)0x0) {
        operator_delete((void *)param_1[3]);
      }
      param_1[3] = 0;
      param_1[4] = 0;
      param_1[5] = 0;
      operator_delete((void *)*param_1);
      param_1 = param_1 + 6;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_1400521b0 @ 1400521b0  undefined FUN_1400521b0(longlong * param_1, longlong * param_2, longlong * param_3)

void FUN_1400521b0(longlong *param_1,longlong *param_2,longlong *param_3)

{
  if (param_1 != param_2) {
    do {
      FUN_1400447b0(param_1,param_3);
      param_1 = param_1 + 6;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_140052200 @ 140052200  undefined FUN_140052200(undefined8 * param_1, longlong param_2, undefined8 * param_3)

void FUN_140052200(undefined8 *param_1,longlong param_2,undefined8 *param_3)

{
  for (; param_2 != 0; param_2 = param_2 + -1) {
    if (param_1 != (undefined8 *)0x0) {
      FUN_140050620(param_1,param_3);
    }
    param_1 = param_1 + 6;
  }
  return;
}


// ==== FUN_140052270 @ 140052270  undefined FUN_140052270(undefined8 param_1, undefined8 * param_2, longlong param_3)

void FUN_140052270(undefined8 param_1,undefined8 *param_2,longlong param_3)

{
  if (param_2 != (undefined8 *)0x0) {
    FUN_140051170(param_2,param_3);
  }
  return;
}


// ==== FUN_1400522b0 @ 1400522b0  longlong * FUN_1400522b0(longlong * param_1, longlong * param_2)

longlong * FUN_1400522b0(longlong *param_1,longlong *param_2)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  ulonglong uVar3;
  longlong lVar4;
  ulonglong uVar5;
  longlong lVar6;
  ulonglong uVar7;
  
  if (param_1 == param_2) {
    return param_1;
  }
  puVar1 = (undefined8 *)param_2[3];
  lVar4 = param_2[4] - (longlong)puVar1;
  lVar4 = lVar4 / 6 + (lVar4 >> 0x3f);
  lVar6 = lVar4 >> 2;
  lVar4 = lVar4 >> 0x3f;
  uVar7 = lVar6 - lVar4;
  if (lVar6 == lVar4) {
    FUN_1400513a0(param_1);
    return param_1;
  }
  lVar4 = param_1[3];
  lVar6 = param_1[4] - lVar4;
  lVar6 = lVar6 / 6 + (lVar6 >> 0x3f);
  uVar5 = (lVar6 >> 2) - (lVar6 >> 0x3f);
  if (uVar7 <= uVar5) {
    lVar6 = FUN_14004d7d0(puVar1,(undefined8 *)param_2[4],lVar4);
    lVar4 = param_1[4];
    for (; lVar6 != lVar4; lVar6 = lVar6 + 0x18) {
      FUN_140067850(lVar6);
    }
    param_1[4] = param_1[3] + ((param_2[4] - param_2[3]) / 0x18) * 0x18;
    return param_1;
  }
  if (lVar4 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = (param_1[5] - lVar4) / 0x18;
  }
  if (uVar3 < uVar7) {
    if (lVar4 != 0) {
      FUN_140050780(param_1,lVar4,param_1[4]);
      operator_delete((void *)param_1[3]);
    }
    uVar2 = FUN_14004cf10((longlong)param_1,(param_2[4] - param_2[3]) / 0x18);
    if ((char)uVar2 != '\0') {
      lVar4 = FUN_14004ff20(param_1,(undefined8 *)param_2[3],(undefined8 *)param_2[4],
                            (undefined8 *)param_1[3]);
      param_1[4] = lVar4;
    }
    return param_1;
  }
  FUN_14004d7d0(puVar1,puVar1 + uVar5 * 3,lVar4);
  puVar1 = FUN_14004db40(puVar1 + uVar5 * 3,(undefined8 *)param_2[4],(undefined8 *)param_1[4]);
  param_1[4] = (longlong)puVar1;
  return param_1;
}


// ==== FUN_140052500 @ 140052500  undefined8 * FUN_140052500(undefined8 * param_1, uint param_2)

undefined8 * FUN_140052500(undefined8 *param_1,uint param_2)

{
  FUN_140051ad0(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_140052540 @ 140052540  undefined FUN_140052540(longlong * param_1, longlong * param_2)

void FUN_140052540(longlong *param_1,longlong *param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  
  if (param_1 != param_2) {
    puVar1 = (undefined8 *)*param_1;
    *param_1 = *param_2;
    *param_2 = (longlong)puVar1;
    puVar2 = (undefined8 *)*param_1;
    if (puVar2 != puVar1) {
      uVar3 = *puVar2;
      *puVar2 = *puVar1;
      *puVar1 = uVar3;
    }
    plVar5 = param_2 + 3;
    plVar6 = param_1 + 3;
    if (plVar6 != plVar5) {
      lVar4 = *plVar6;
      *plVar6 = *plVar5;
      *plVar5 = lVar4;
    }
    plVar5 = param_2 + 4;
    plVar6 = param_1 + 4;
    if (plVar6 != plVar5) {
      lVar4 = *plVar6;
      *plVar6 = *plVar5;
      *plVar5 = lVar4;
    }
    plVar6 = param_2 + 5;
    plVar5 = param_1 + 5;
    if (plVar5 != plVar6) {
      lVar4 = *plVar5;
      *plVar5 = *plVar6;
      *plVar6 = lVar4;
    }
  }
  return;
}


// ==== FUN_140052dd0 @ 140052dd0  undefined FUN_140052dd0(longlong * param_1, ulonglong param_2, undefined8 * param_3)

void FUN_140052dd0(longlong *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  ulonglong uVar3;
  longlong *plVar4;
  longlong lVar5;
  longlong lVar6;
  longlong lVar7;
  longlong local_38;
  undefined8 *puStack_30;
  
  puVar1 = (undefined8 *)param_1[4];
  puVar2 = (undefined8 *)param_1[3];
  uVar3 = ((longlong)puVar1 - (longlong)puVar2) / 0x18;
  if (uVar3 < param_2) {
    if (puVar1 < puVar2) {
      _invalid_parameter_noinfo();
    }
    local_38 = *param_1;
    puStack_30 = puVar1;
    FUN_140051cc0((longlong)param_1,(longlong)&local_38,param_2 - (param_1[4] - param_1[3]) / 0x18,
                  param_3);
    goto LAB_140052f5a;
  }
  if (uVar3 <= param_2) goto LAB_140052f5a;
  if (puVar1 < puVar2) {
    _invalid_parameter_noinfo();
  }
  uVar3 = param_1[3];
  if ((ulonglong)param_1[4] < uVar3) {
    _invalid_parameter_noinfo();
  }
  plVar4 = (longlong *)*param_1;
  lVar7 = 0;
  if (plVar4 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar6 = lVar7;
  }
  else {
    lVar6 = *plVar4;
  }
  puVar2 = (undefined8 *)(uVar3 + param_2 * 0x18);
  if (*(undefined8 **)(lVar6 + 0x20) < puVar2) {
LAB_140052ee5:
    _invalid_parameter_noinfo();
  }
  else {
    if (plVar4 != (longlong *)0x0) {
      lVar7 = *plVar4;
    }
    if (puVar2 < *(undefined8 **)(lVar7 + 0x18)) goto LAB_140052ee5;
  }
  if ((puVar2 < (undefined8 *)param_1[3]) || ((undefined8 *)param_1[4] < puVar2)) {
    _invalid_parameter_noinfo();
  }
  lVar7 = *param_1;
  if ((puVar1 < (undefined8 *)param_1[3]) || ((undefined8 *)param_1[4] < puVar1)) {
    _invalid_parameter_noinfo();
  }
  if ((lVar7 == 0) || (lVar7 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (puVar2 != puVar1) {
    lVar5 = FUN_14004d7d0(puVar1,(undefined8 *)param_1[4],(longlong)puVar2);
    lVar7 = param_1[4];
    for (lVar6 = lVar5; lVar6 != lVar7; lVar6 = lVar6 + 0x18) {
      FUN_140067850(lVar6);
    }
    param_1[4] = lVar5;
  }
LAB_140052f5a:
  FUN_140067850((longlong)param_3);
  return;
}


// ==== FUN_140052f80 @ 140052f80  undefined FUN_140052f80(longlong * param_1, longlong * param_2, longlong param_3)

void FUN_140052f80(longlong *param_1,longlong *param_2,longlong param_3)

{
  FUN_1400520b0(param_1,param_2,param_3);
  return;
}


// ==== FUN_140052fc0 @ 140052fc0  undefined FUN_140052fc0(longlong * param_1, longlong * param_2, longlong * param_3)

void FUN_140052fc0(longlong *param_1,longlong *param_2,longlong *param_3)

{
  if (param_1 != param_2) {
    do {
      FUN_1400447b0(param_1,param_3);
      param_1 = param_1 + 6;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_140053010 @ 140053010  undefined FUN_140053010(undefined8 * param_1, longlong param_2, undefined8 * param_3)

void FUN_140053010(undefined8 *param_1,longlong param_2,undefined8 *param_3)

{
  FUN_140052200(param_1,param_2,param_3);
  return;
}


// ==== FUN_140053030 @ 140053030  longlong FUN_140053030(longlong * param_1, longlong * param_2, longlong param_3)

longlong FUN_140053030(longlong *param_1,longlong *param_2,longlong param_3)

{
  longlong lVar1;
  longlong lVar2;
  
  lVar2 = (longlong)param_2 - (longlong)param_1;
  if (param_1 != param_2) {
    lVar1 = param_3 - (longlong)param_1;
    do {
      FUN_1400522b0((longlong *)(lVar1 + (longlong)param_1),param_1);
      param_1 = param_1 + 6;
    } while (param_1 != param_2);
  }
  return (lVar2 / 0x30) * 0x30 + param_3;
}


// ==== FUN_1400530b0 @ 1400530b0  undefined FUN_1400530b0(longlong * param_1, longlong * param_2, longlong * param_3)

void FUN_1400530b0(longlong *param_1,longlong *param_2,longlong *param_3)

{
  if (param_1 != param_2) {
    do {
      FUN_1400522b0(param_1,param_3);
      param_1 = param_1 + 6;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_140053130 @ 140053130  undefined FUN_140053130(longlong param_1, longlong * param_2, undefined8 param_3, int param_4)

void FUN_140053130(longlong param_1,longlong *param_2,undefined8 param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  longlong *plVar6;
  ulonglong uVar7;
  uint uVar8;
  ulonglong uVar9;
  int iVar10;
  int local_res18;
  int iStackX_1c;
  
  iVar1 = param_4 * 2 + 1;
  iVar1 = iVar1 * iVar1;
  FUN_140051b50(param_2,(longlong)iVar1,0);
  local_res18 = (int)param_3;
  iVar2 = local_res18 / 0x12 + -1;
  iVar10 = 0;
  if (0 < iVar2) {
    iVar10 = iVar2;
  }
  if (iVar10 <= local_res18 / 0x12 + 1) {
    do {
      iVar2 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))();
      if ((iVar2 + -1) / 0x12 + 1 <= iVar10) {
        return;
      }
      iStackX_1c = (int)((ulonglong)param_3 >> 0x20);
      iVar3 = iStackX_1c / 0x12 + -1;
      iVar2 = 0;
      if (0 < iVar3) {
        iVar2 = iVar3;
      }
      if (iVar2 <= iStackX_1c / 0x12 + 1) {
        do {
          iVar3 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x20))();
          if ((iVar3 + -1) / 0x12 + 1 <= iVar2) break;
          uVar9 = 0;
          lVar5 = FUN_14004ac70(param_1,iVar10,iVar2);
          plVar6 = (longlong *)FUN_1400678a0(lVar5);
          lVar5 = (**(code **)(*plVar6 + 0x10))(plVar6);
          if (lVar5 != 0) {
            do {
              lVar5 = FUN_14004ac70(param_1,iVar10,iVar2);
              plVar6 = (longlong *)FUN_1400678a0(lVar5);
              plVar6 = (longlong *)
                       (**(code **)(*plVar6 + 0x18))
                                 (plVar6,uVar9,
                                  "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\gamemap.cpp"
                                  ,0x211);
              if (plVar6 != (longlong *)0x0) {
                iVar3 = (**(code **)(*plVar6 + 0x40))(plVar6);
                iVar4 = (**(code **)(*plVar6 + 0x38))(plVar6);
                uVar8 = iVar3 - iStackX_1c >> 0x1f;
                iVar3 = (iVar3 - iStackX_1c ^ uVar8) - uVar8;
                uVar8 = iVar4 - local_res18 >> 0x1f;
                iVar4 = (iVar4 - local_res18 ^ uVar8) - uVar8;
                if (iVar3 < iVar4) {
                  iVar3 = iVar4;
                }
                if (iVar3 <= param_4) {
                  iVar3 = (**(code **)(*plVar6 + 0x40))(plVar6);
                  iVar4 = (**(code **)(*plVar6 + 0x38))(plVar6);
                  iVar3 = (((param_4 - iStackX_1c) + iVar3) * (param_4 * 2 + 1) - local_res18) +
                          param_4 + iVar4;
                  if ((iVar3 < 0) || (iVar1 <= iVar3)) {
                    log_InlineLogERROR(&DAT_1400be0b0);
                  }
                  else {
                    if ((ulonglong)(param_2[4] - param_2[3] >> 3) <= (ulonglong)(longlong)iVar3) {
                      _invalid_parameter_noinfo();
                    }
                    *(longlong **)(param_2[3] + (longlong)iVar3 * 8) = plVar6;
                  }
                }
              }
              uVar9 = uVar9 + 1;
              lVar5 = FUN_14004ac70(param_1,iVar10,iVar2);
              plVar6 = (longlong *)FUN_1400678a0(lVar5);
              uVar7 = (**(code **)(*plVar6 + 0x10))(plVar6);
            } while (uVar9 < uVar7);
          }
          uVar9 = 0;
          lVar5 = FUN_14004ac70(param_1,iVar10,iVar2);
          plVar6 = (longlong *)FUN_1400678b0(lVar5);
          lVar5 = (**(code **)(*plVar6 + 0x10))(plVar6);
          if (lVar5 != 0) {
            do {
              lVar5 = FUN_14004ac70(param_1,iVar10,iVar2);
              plVar6 = (longlong *)FUN_1400678b0(lVar5);
              lVar5 = (**(code **)(*plVar6 + 0x18))
                                (plVar6,uVar9,
                                 "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\gamemap.cpp"
                                 ,0x21c);
              if (lVar5 != 0) {
                plVar6 = (longlong *)(lVar5 + 0x10);
                iVar3 = (**(code **)(*plVar6 + 0x40))(plVar6);
                iVar4 = (**(code **)(*plVar6 + 0x38))(plVar6);
                uVar8 = iVar3 - iStackX_1c >> 0x1f;
                iVar3 = (iVar3 - iStackX_1c ^ uVar8) - uVar8;
                uVar8 = iVar4 - local_res18 >> 0x1f;
                iVar4 = (iVar4 - local_res18 ^ uVar8) - uVar8;
                if (iVar3 < iVar4) {
                  iVar3 = iVar4;
                }
                if (iVar3 <= param_4) {
                  iVar3 = (**(code **)(*plVar6 + 0x40))(plVar6);
                  iVar4 = (**(code **)(*plVar6 + 0x38))(plVar6);
                  iVar3 = (((param_4 - iStackX_1c) + iVar3) * (param_4 * 2 + 1) - local_res18) +
                          param_4 + iVar4;
                  if ((iVar3 < 0) || (iVar1 <= iVar3)) {
                    log_InlineLogERROR(&DAT_1400be0b0);
                  }
                  else {
                    if ((ulonglong)(param_2[4] - param_2[3] >> 3) <= (ulonglong)(longlong)iVar3) {
                      _invalid_parameter_noinfo();
                    }
                    *(longlong **)(param_2[3] + (longlong)iVar3 * 8) = plVar6;
                  }
                }
              }
              uVar9 = uVar9 + 1;
              lVar5 = FUN_14004ac70(param_1,iVar10,iVar2);
              plVar6 = (longlong *)FUN_1400678b0(lVar5);
              uVar7 = (**(code **)(*plVar6 + 0x10))(plVar6);
            } while (uVar9 < uVar7);
          }
          iVar2 = iVar2 + 1;
        } while (iVar2 <= iStackX_1c / 0x12 + 1);
      }
      iVar10 = iVar10 + 1;
    } while (iVar10 <= local_res18 / 0x12 + 1);
  }
  return;
}


// ==== FUN_140053570 @ 140053570  undefined FUN_140053570(longlong * param_1, ulonglong param_2)

void FUN_140053570(longlong *param_1,ulonglong param_2)

{
  undefined8 *puVar1;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined1 local_28 [32];
  
  puVar1 = (undefined8 *)FUN_140067830(local_28);
  local_48 = *puVar1;
  local_40 = puVar1[1];
  local_38 = puVar1[2];
  FUN_140052dd0(param_1,param_2,&local_48);
  FUN_140067850((longlong)local_28);
  return;
}


// ==== FUN_140053600 @ 140053600  undefined8 * FUN_140053600(undefined8 param_1, undefined8 * param_2, longlong param_3, undefined8 * param_4)

undefined8 *
FUN_140053600(undefined8 param_1,undefined8 *param_2,longlong param_3,undefined8 *param_4)

{
  FUN_140052200(param_2,param_3,param_4);
  return param_2 + param_3 * 6;
}


// ==== FUN_140053650 @ 140053650  undefined FUN_140053650(longlong * param_1, longlong * param_2, longlong param_3)

void FUN_140053650(longlong *param_1,longlong *param_2,longlong param_3)

{
  FUN_140053030(param_1,param_2,param_3);
  return;
}


// ==== FUN_140053680 @ 140053680  undefined FUN_140053680(longlong * param_1, longlong * param_2, longlong * param_3)

void FUN_140053680(longlong *param_1,longlong *param_2,longlong *param_3)

{
  if (param_1 != param_2) {
    do {
      FUN_1400522b0(param_1,param_3);
      param_1 = param_1 + 6;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_1400536e0 @ 1400536e0  longlong * FUN_1400536e0(longlong * param_1, longlong * param_2, longlong * param_3)

longlong * FUN_1400536e0(longlong *param_1,longlong *param_2,longlong *param_3)

{
  longlong *plVar1;
  longlong *plVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  longlong lVar6;
  longlong *local_48 [3];
  void *local_30;
  undefined8 local_28;
  undefined8 local_20;
  
  local_48[0] = (longlong *)operator_new(8);
  if (local_48[0] == (longlong *)0x0) {
    local_48[0] = (longlong *)0x0;
  }
  else {
    *local_48[0] = (longlong)local_48;
  }
  local_30 = (void *)0x0;
  local_28 = 0;
  local_20 = 0;
  for (; param_1 != param_2; param_1 = param_1 + 6) {
    if (param_3 != (longlong *)0x0) {
      FUN_140050620(param_3,local_48);
    }
    if (param_3 != param_1) {
      puVar3 = (undefined8 *)*param_3;
      *param_3 = *param_1;
      *param_1 = (longlong)puVar3;
      puVar4 = (undefined8 *)*param_3;
      if (puVar4 != puVar3) {
        uVar5 = *puVar4;
        *puVar4 = *puVar3;
        *puVar3 = uVar5;
      }
      plVar1 = param_1 + 3;
      plVar2 = param_3 + 3;
      if (plVar2 != plVar1) {
        lVar6 = *plVar2;
        *plVar2 = *plVar1;
        *plVar1 = lVar6;
      }
      plVar1 = param_1 + 4;
      plVar2 = param_3 + 4;
      if (plVar2 != plVar1) {
        lVar6 = *plVar2;
        *plVar2 = *plVar1;
        *plVar1 = lVar6;
      }
      plVar1 = param_1 + 5;
      plVar2 = param_3 + 5;
      if (plVar2 != plVar1) {
        lVar6 = *plVar2;
        *plVar2 = *plVar1;
        *plVar1 = lVar6;
      }
    }
    param_3 = param_3 + 6;
  }
  if (local_30 != (void *)0x0) {
    operator_delete(local_30);
  }
  local_30 = (void *)0x0;
  local_28 = 0;
  local_20 = 0;
  operator_delete(local_48[0]);
  return param_3;
}


// ==== FUN_140053850 @ 140053850  longlong * FUN_140053850(longlong * param_1, longlong * param_2, longlong * param_3)

longlong * FUN_140053850(longlong *param_1,longlong *param_2,longlong *param_3)

{
  longlong *plVar1;
  longlong *plVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  longlong lVar6;
  longlong *plVar7;
  longlong *plVar8;
  longlong *plVar9;
  longlong *plVar10;
  
  if (param_1 != param_2) {
    plVar7 = param_3 + 4;
    plVar9 = param_2 + 4;
    do {
      param_2 = param_2 + -6;
      plVar10 = plVar9 + -6;
      param_3 = param_3 + -6;
      plVar8 = plVar7 + -6;
      if (param_3 != param_2) {
        puVar3 = (undefined8 *)*param_3;
        *param_3 = *param_2;
        *param_2 = (longlong)puVar3;
        puVar4 = (undefined8 *)*param_3;
        if (puVar4 != puVar3) {
          uVar5 = *puVar4;
          *puVar4 = *puVar3;
          *puVar3 = uVar5;
        }
        plVar1 = plVar9 + -7;
        plVar2 = plVar7 + -7;
        if (plVar2 != plVar1) {
          lVar6 = *plVar2;
          *plVar2 = *plVar1;
          *plVar1 = lVar6;
        }
        if (plVar8 != plVar10) {
          lVar6 = *plVar8;
          *plVar8 = *plVar10;
          *plVar10 = lVar6;
        }
        plVar9 = plVar9 + -5;
        plVar7 = plVar7 + -5;
        if (plVar7 != plVar9) {
          lVar6 = *plVar7;
          *plVar7 = *plVar9;
          *plVar9 = lVar6;
        }
      }
      plVar7 = plVar8;
      plVar9 = plVar10;
    } while (param_2 != param_1);
  }
  return param_3;
}


// ==== FUN_140053920 @ 140053920  longlong * FUN_140053920(longlong * param_1, longlong * param_2, longlong param_3, longlong param_4)

longlong * FUN_140053920(longlong *param_1,longlong *param_2,longlong param_3,longlong param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (longlong *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  lVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = lVar2;
  plVar3 = *(longlong **)(param_4 + 8);
  if ((plVar3 < (longlong *)param_1[3]) || ((longlong *)param_1[4] < plVar3)) {
    _invalid_parameter_noinfo();
  }
  if ((*param_2 == 0) || (*param_2 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if ((longlong *)param_2[1] != plVar3) {
    puVar4 = (undefined8 *)FUN_1400520b0(plVar3,(longlong *)param_1[4],param_2[1]);
    FUN_140052130(puVar4,(undefined8 *)param_1[4]);
    param_1[4] = (longlong)puVar4;
  }
  return param_2;
}


// ==== FUN_140053a20 @ 140053a20  undefined FUN_140053a20(longlong param_1)

void FUN_140053a20(longlong param_1)

{
  if (*(undefined8 **)(param_1 + 0x18) != (undefined8 *)0x0) {
    FUN_140052130(*(undefined8 **)(param_1 + 0x18),*(undefined8 **)(param_1 + 0x20));
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_140053a70 @ 140053a70  undefined FUN_140053a70(undefined8 * param_1, undefined8 * param_2)

void FUN_140053a70(undefined8 *param_1,undefined8 *param_2)

{
  longlong lVar1;
  longlong lVar2;
  
  if (param_1 != param_2) {
    do {
      lVar2 = param_1[3];
      if (lVar2 != 0) {
        lVar1 = param_1[4];
        for (; lVar2 != lVar1; lVar2 = lVar2 + 0x18) {
          FUN_140067850(lVar2);
        }
        operator_delete((void *)param_1[3]);
      }
      param_1[3] = 0;
      param_1[4] = 0;
      param_1[5] = 0;
      operator_delete((void *)*param_1);
      param_1 = param_1 + 6;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_140053b10 @ 140053b10  undefined FUN_140053b10(longlong * param_1, longlong * param_2, longlong * param_3)

void FUN_140053b10(longlong *param_1,longlong *param_2,longlong *param_3)

{
  FUN_1400536e0(param_1,param_2,param_3);
  return;
}


// ==== FUN_140053b30 @ 140053b30  longlong * FUN_140053b30(longlong * param_1, longlong * param_2, longlong * param_3)

longlong * FUN_140053b30(longlong *param_1,longlong *param_2,longlong *param_3)

{
  FUN_140053850(param_1,param_2,param_3);
  return param_3 + (((longlong)param_2 - (longlong)param_1) / 0x30) * -6;
}


// ==== FUN_140053ba0 @ 140053ba0  undefined FUN_140053ba0(undefined8 * param_1, longlong param_2, longlong param_3)

void FUN_140053ba0(undefined8 *param_1,longlong param_2,longlong param_3)

{
  for (; param_2 != 0; param_2 = param_2 + -1) {
    if (param_1 != (undefined8 *)0x0) {
      FUN_140051170(param_1,param_3);
    }
    param_1 = param_1 + 6;
  }
  return;
}


// ==== FUN_140053c20 @ 140053c20  longlong * FUN_140053c20(longlong * param_1, longlong * param_2, longlong * param_3)

longlong * FUN_140053c20(longlong *param_1,longlong *param_2,longlong *param_3)

{
  longlong *plVar1;
  longlong *plVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  longlong lVar6;
  void *pvVar7;
  void *pvVar8;
  longlong *local_48 [3];
  void *local_30;
  void *local_28;
  undefined8 local_20;
  
  local_48[0] = (longlong *)operator_new(8);
  if (local_48[0] == (longlong *)0x0) {
    local_48[0] = (longlong *)0x0;
  }
  else {
    *local_48[0] = (longlong)local_48;
  }
  local_30 = (void *)0x0;
  local_28 = (void *)0x0;
  local_20 = 0;
  for (; pvVar8 = local_28, param_1 != param_2; param_1 = param_1 + 6) {
    if (param_3 != (longlong *)0x0) {
      FUN_140051170(param_3,(longlong)local_48);
    }
    if (param_3 != param_1) {
      puVar3 = (undefined8 *)*param_3;
      *param_3 = *param_1;
      *param_1 = (longlong)puVar3;
      puVar4 = (undefined8 *)*param_3;
      if (puVar4 != puVar3) {
        uVar5 = *puVar4;
        *puVar4 = *puVar3;
        *puVar3 = uVar5;
      }
      plVar1 = param_1 + 3;
      plVar2 = param_3 + 3;
      if (plVar2 != plVar1) {
        lVar6 = *plVar2;
        *plVar2 = *plVar1;
        *plVar1 = lVar6;
      }
      plVar1 = param_1 + 4;
      plVar2 = param_3 + 4;
      if (plVar2 != plVar1) {
        lVar6 = *plVar2;
        *plVar2 = *plVar1;
        *plVar1 = lVar6;
      }
      plVar1 = param_1 + 5;
      plVar2 = param_3 + 5;
      if (plVar2 != plVar1) {
        lVar6 = *plVar2;
        *plVar2 = *plVar1;
        *plVar1 = lVar6;
      }
    }
    param_3 = param_3 + 6;
  }
  pvVar7 = local_30;
  if (local_30 != (void *)0x0) {
    for (; pvVar7 != pvVar8; pvVar7 = (void *)((longlong)pvVar7 + 0x18)) {
      FUN_140067850((longlong)pvVar7);
    }
    operator_delete(local_30);
  }
  local_30 = (void *)0x0;
  local_28 = (void *)0x0;
  local_20 = 0;
  operator_delete(local_48[0]);
  return param_3;
}


// ==== FUN_140053db0 @ 140053db0  longlong * FUN_140053db0(longlong * param_1, longlong * param_2, longlong * param_3)

longlong * FUN_140053db0(longlong *param_1,longlong *param_2,longlong *param_3)

{
  longlong *plVar1;
  longlong *plVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  longlong lVar6;
  longlong *plVar7;
  longlong *plVar8;
  longlong *plVar9;
  longlong *plVar10;
  
  if (param_1 != param_2) {
    plVar7 = param_3 + 4;
    plVar9 = param_2 + 4;
    do {
      param_2 = param_2 + -6;
      plVar10 = plVar9 + -6;
      param_3 = param_3 + -6;
      plVar8 = plVar7 + -6;
      if (param_3 != param_2) {
        puVar3 = (undefined8 *)*param_3;
        *param_3 = *param_2;
        *param_2 = (longlong)puVar3;
        puVar4 = (undefined8 *)*param_3;
        if (puVar4 != puVar3) {
          uVar5 = *puVar4;
          *puVar4 = *puVar3;
          *puVar3 = uVar5;
        }
        plVar1 = plVar9 + -7;
        plVar2 = plVar7 + -7;
        if (plVar2 != plVar1) {
          lVar6 = *plVar2;
          *plVar2 = *plVar1;
          *plVar1 = lVar6;
        }
        if (plVar8 != plVar10) {
          lVar6 = *plVar8;
          *plVar8 = *plVar10;
          *plVar10 = lVar6;
        }
        plVar9 = plVar9 + -5;
        plVar7 = plVar7 + -5;
        if (plVar7 != plVar9) {
          lVar6 = *plVar7;
          *plVar7 = *plVar9;
          *plVar9 = lVar6;
        }
      }
      plVar7 = plVar8;
      plVar9 = plVar10;
    } while (param_2 != param_1);
  }
  return param_3;
}


// ==== FUN_140053e70 @ 140053e70  undefined FUN_140053e70(undefined8 * param_1)

void FUN_140053e70(undefined8 *param_1)

{
  if ((undefined8 *)param_1[3] != (undefined8 *)0x0) {
    FUN_140052130((undefined8 *)param_1[3],(undefined8 *)param_1[4]);
    operator_delete((void *)param_1[3]);
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140053ed0 @ 140053ed0  undefined FUN_140053ed0(longlong * param_1)

void FUN_140053ed0(longlong *param_1)

{
  longlong *plVar1;
  longlong *plVar2;
  longlong lVar3;
  undefined8 *puVar4;
  
  plVar1 = (longlong *)param_1[4];
  if (plVar1 < (longlong *)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)param_1[3];
  if ((longlong *)param_1[4] < plVar2) {
    _invalid_parameter_noinfo();
  }
  if ((plVar2 < (longlong *)param_1[3]) || ((longlong *)param_1[4] < plVar2)) {
    _invalid_parameter_noinfo();
  }
  lVar3 = *param_1;
  if ((plVar1 < (longlong *)param_1[3]) || ((longlong *)param_1[4] < plVar1)) {
    _invalid_parameter_noinfo();
  }
  if ((lVar3 == 0) || (lVar3 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (plVar2 != plVar1) {
    puVar4 = (undefined8 *)FUN_1400520b0(plVar1,(longlong *)param_1[4],(longlong)plVar2);
    FUN_140052130(puVar4,(undefined8 *)param_1[4]);
    param_1[4] = (longlong)puVar4;
  }
  return;
}


// ==== FUN_140053fb0 @ 140053fb0  undefined FUN_140053fb0(undefined8 param_1, longlong * param_2, longlong * param_3, longlong * param_4)

void FUN_140053fb0(undefined8 param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  FUN_1400536e0(param_2,param_3,param_4);
  return;
}


// ==== FUN_140053ff0 @ 140053ff0  longlong * FUN_140053ff0(longlong * param_1, longlong * param_2, longlong * param_3)

longlong * FUN_140053ff0(longlong *param_1,longlong *param_2,longlong *param_3)

{
  FUN_140053850(param_1,param_2,param_3);
  return param_3 + (((longlong)param_2 - (longlong)param_1) / 0x30) * -6;
}


// ==== FUN_140054060 @ 140054060  undefined FUN_140054060(undefined8 * param_1, longlong param_2, longlong param_3)

void FUN_140054060(undefined8 *param_1,longlong param_2,longlong param_3)

{
  FUN_140053ba0(param_1,param_2,param_3);
  return;
}


// ==== FUN_140054080 @ 140054080  undefined FUN_140054080(longlong * param_1, longlong * param_2, longlong * param_3)

void FUN_140054080(longlong *param_1,longlong *param_2,longlong *param_3)

{
  FUN_140053c20(param_1,param_2,param_3);
  return;
}


// ==== FUN_1400540a0 @ 1400540a0  longlong * FUN_1400540a0(longlong * param_1, longlong * param_2, longlong * param_3)

longlong * FUN_1400540a0(longlong *param_1,longlong *param_2,longlong *param_3)

{
  FUN_140053db0(param_1,param_2,param_3);
  return param_3 + (((longlong)param_2 - (longlong)param_1) / 0x30) * -6;
}


// ==== FUN_140054130 @ 140054130  undefined FUN_140054130(longlong param_1, longlong param_2, ulonglong param_3, undefined8 * param_4)

void FUN_140054130(longlong param_1,longlong param_2,ulonglong param_3,undefined8 *param_4)

{
  ulonglong uVar1;
  undefined8 *puVar2;
  code *pcVar3;
  longlong *plVar4;
  longlong *plVar5;
  longlong lVar6;
  longlong lVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  void *local_68 [3];
  void *local_50;
  undefined8 local_48;
  undefined8 local_40;
  
  lVar7 = *(longlong *)(param_1 + 0x18);
  if (lVar7 == 0) {
    uVar8 = 0;
  }
  else {
    lVar6 = *(longlong *)(param_1 + 0x28) - lVar7;
    lVar6 = lVar6 / 6 + (lVar6 >> 0x3f);
    uVar8 = (lVar6 >> 3) - (lVar6 >> 0x3f);
  }
  uVar9 = 0;
  if (param_3 != 0) {
    lVar7 = (*(longlong *)(param_1 + 0x20) - lVar7) / 0x30;
    if (0x555555555555555U - lVar7 < param_3) {
      FUN_140049850();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    uVar1 = lVar7 + param_3;
    if (uVar8 < uVar1) {
      if (uVar8 <= 0x555555555555555 - (uVar8 >> 1)) {
        uVar9 = uVar8 + (uVar8 >> 1);
      }
      if (uVar9 < uVar1) {
        uVar9 = uVar1;
      }
      plVar4 = (longlong *)FUN_14004b3f0(param_1 + 0x10,uVar9);
      lVar7 = *(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18);
      lVar7 = lVar7 / 6 + (lVar7 >> 0x3f);
      lVar7 = (lVar7 >> 3) - (lVar7 >> 0x3f);
      FUN_140052200(plVar4 + lVar7 * 6,param_3,param_4);
      FUN_1400536e0(*(longlong **)(param_1 + 0x18),*(longlong **)(param_2 + 8),plVar4);
      FUN_1400536e0(*(longlong **)(param_2 + 8),*(longlong **)(param_1 + 0x20),
                    plVar4 + (lVar7 + param_3) * 6);
      puVar2 = *(undefined8 **)(param_1 + 0x18);
      lVar7 = *(longlong *)(param_1 + 0x20);
      if (puVar2 != (undefined8 *)0x0) {
        FUN_140052130(puVar2,*(undefined8 **)(param_1 + 0x20));
        operator_delete(*(void **)(param_1 + 0x18));
      }
      *(longlong **)(param_1 + 0x28) = plVar4 + uVar9 * 6;
      *(longlong **)(param_1 + 0x20) = plVar4 + (param_3 + (lVar7 - (longlong)puVar2) / 0x30) * 6;
      *(longlong **)(param_1 + 0x18) = plVar4;
    }
    else if ((ulonglong)((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_2 + 8)) / 0x30) <
             param_3) {
      FUN_140050620(local_68,param_4);
      FUN_1400536e0(*(longlong **)(param_2 + 8),*(longlong **)(param_1 + 0x20),
                    *(longlong **)(param_2 + 8) + param_3 * 6);
      FUN_140052200(*(undefined8 **)(param_1 + 0x20),
                    param_3 - ((longlong)*(undefined8 **)(param_1 + 0x20) -
                              *(longlong *)(param_2 + 8)) / 0x30,local_68);
      *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + param_3 * 0x30;
      lVar7 = *(longlong *)(param_1 + 0x20);
      for (plVar4 = *(longlong **)(param_2 + 8); plVar4 != (longlong *)(lVar7 + param_3 * -0x30);
          plVar4 = plVar4 + 6) {
        FUN_1400447b0(plVar4,(longlong *)local_68);
      }
      if (local_50 != (void *)0x0) {
        operator_delete(local_50);
      }
      local_50 = (void *)0x0;
      local_48 = 0;
      local_40 = 0;
      operator_delete(local_68[0]);
    }
    else {
      FUN_140050620(local_68,param_4);
      plVar4 = *(longlong **)(param_1 + 0x20);
      plVar5 = FUN_1400536e0(plVar4 + param_3 * -6,plVar4,plVar4);
      *(longlong **)(param_1 + 0x20) = plVar5;
      FUN_140053ff0(*(longlong **)(param_2 + 8),plVar4 + param_3 * -6,plVar4);
      plVar5 = *(longlong **)(param_2 + 8);
      plVar4 = plVar5 + param_3 * 6;
      for (; plVar5 != plVar4; plVar5 = plVar5 + 6) {
        FUN_1400447b0(plVar5,(longlong *)local_68);
      }
      if (local_50 != (void *)0x0) {
        operator_delete(local_50);
      }
      local_50 = (void *)0x0;
      local_48 = 0;
      local_40 = 0;
      operator_delete(local_68[0]);
    }
  }
  return;
}


// ==== FUN_140054550 @ 140054550  undefined8 * FUN_140054550(undefined8 param_1, undefined8 * param_2, longlong param_3, longlong param_4)

undefined8 * FUN_140054550(undefined8 param_1,undefined8 *param_2,longlong param_3,longlong param_4)

{
  FUN_140053ba0(param_2,param_3,param_4);
  return param_2 + param_3 * 6;
}


// ==== FUN_1400545a0 @ 1400545a0  undefined FUN_1400545a0(undefined8 param_1, longlong * param_2, longlong * param_3, longlong * param_4)

void FUN_1400545a0(undefined8 param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  FUN_140053c20(param_2,param_3,param_4);
  return;
}


// ==== FUN_1400545e0 @ 1400545e0  longlong * FUN_1400545e0(longlong * param_1, longlong * param_2, longlong * param_3)

longlong * FUN_1400545e0(longlong *param_1,longlong *param_2,longlong *param_3)

{
  FUN_140053db0(param_1,param_2,param_3);
  return param_3 + (((longlong)param_2 - (longlong)param_1) / 0x30) * -6;
}


// ==== FUN_140054650 @ 140054650  longlong * FUN_140054650(longlong * param_1, longlong * param_2, longlong param_3, longlong param_4)

longlong * FUN_140054650(longlong *param_1,longlong *param_2,longlong param_3,longlong param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (longlong *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  lVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = lVar2;
  plVar3 = *(longlong **)(param_4 + 8);
  if ((plVar3 < (longlong *)param_1[3]) || ((longlong *)param_1[4] < plVar3)) {
    _invalid_parameter_noinfo();
  }
  if ((*param_2 == 0) || (*param_2 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if ((longlong *)param_2[1] != plVar3) {
    puVar4 = (undefined8 *)FUN_140053030(plVar3,(longlong *)param_1[4],param_2[1]);
    FUN_140053a70(puVar4,(undefined8 *)param_1[4]);
    param_1[4] = (longlong)puVar4;
  }
  return param_2;
}


// ==== FUN_140054750 @ 140054750  undefined FUN_140054750(longlong param_1)

void FUN_140054750(longlong param_1)

{
  if (*(undefined8 **)(param_1 + 0x18) != (undefined8 *)0x0) {
    FUN_140053a70(*(undefined8 **)(param_1 + 0x18),*(undefined8 **)(param_1 + 0x20));
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


