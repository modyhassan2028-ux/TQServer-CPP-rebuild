// NpcServer.exe :: _unnamed  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== FUN_140080100 @ 140080100  undefined FUN_140080100(undefined8 * param_1)

void FUN_140080100(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140080130 @ 140080130  undefined FUN_140080130(undefined8 * param_1)

void FUN_140080130(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140080170 @ 140080170  longlong FUN_140080170(longlong * param_1)

longlong FUN_140080170(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140080192;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140080192:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_1400801b0 @ 1400801b0  longlong FUN_1400801b0(longlong * param_1, longlong * param_2)

longlong FUN_1400801b0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] - param_2[1] >> 4;
}


// ==== FUN_140080260 @ 140080260  undefined FUN_140080260(void)

void FUN_140080260(void)

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


// ==== FUN_140080300 @ 140080300  undefined FUN_140080300(void)

void FUN_140080300(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [48];
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_70,"vector<bool> too long");
  std::exception::exception((exception *)local_48);
  local_48[0] = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
  local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
}


// ==== FUN_140080380 @ 140080380  longlong FUN_140080380(longlong param_1, ulonglong param_2)

longlong FUN_140080380(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)(*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18) >> 2) <= param_2) {
    _invalid_parameter_noinfo();
  }
  return *(longlong *)(param_1 + 0x18) + param_2 * 4;
}


// ==== FUN_1400803c0 @ 1400803c0  undefined FUN_1400803c0(void)

void FUN_1400803c0(void)

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


// ==== FUN_140080450 @ 140080450  longlong * FUN_140080450(longlong * param_1, longlong param_2)

longlong * FUN_140080450(longlong *param_1,longlong param_2)

{
  longlong *plVar1;
  longlong lVar2;
  longlong lVar3;
  ulonglong uVar4;
  
  plVar1 = (longlong *)*param_1;
  lVar3 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar1 = (longlong *)*param_1;
    lVar2 = lVar3;
    if (plVar1 != (longlong *)0x0) goto LAB_140080480;
  }
  else {
LAB_140080480:
    lVar2 = *plVar1;
  }
  uVar4 = param_1[1] + param_2 * 0x10;
  if (uVar4 <= *(ulonglong *)(lVar2 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar4) goto LAB_1400804a8;
  }
  _invalid_parameter_noinfo();
LAB_1400804a8:
  param_1[1] = param_1[1] + param_2 * 0x10;
  return param_1;
}


// ==== FUN_1400804c0 @ 1400804c0  longlong * FUN_1400804c0(longlong * param_1, longlong param_2)

longlong * FUN_1400804c0(longlong *param_1,longlong param_2)

{
  FUN_140080450(param_1,param_2);
  return param_1;
}


// ==== FUN_140080560 @ 140080560  longlong * FUN_140080560(longlong * param_1, longlong param_2)

longlong * FUN_140080560(longlong *param_1,longlong param_2)

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
    if (plVar1 != (longlong *)0x0) goto LAB_140080590;
  }
  else {
LAB_140080590:
    lVar4 = *plVar1;
  }
  uVar2 = param_1[1] + param_2 * 0x30;
  if (uVar2 <= *(ulonglong *)(lVar4 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar2) goto LAB_1400805bc;
  }
  _invalid_parameter_noinfo();
LAB_1400805bc:
  param_1[1] = param_1[1] + param_2 * 0x30;
  return param_1;
}


// ==== FUN_140080610 @ 140080610  longlong * FUN_140080610(longlong * param_1, longlong param_2)

longlong * FUN_140080610(longlong *param_1,longlong param_2)

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
    if (plVar1 != (longlong *)0x0) goto LAB_140080640;
  }
  else {
LAB_140080640:
    lVar4 = *plVar1;
  }
  uVar2 = param_1[1] + param_2 * 4;
  if (uVar2 <= *(ulonglong *)(lVar4 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar2) goto LAB_140080668;
  }
  _invalid_parameter_noinfo();
LAB_140080668:
  param_1[1] = param_1[1] + param_2 * 4;
  return param_1;
}


// ==== FUN_140080680 @ 140080680  bool FUN_140080680(longlong * param_1, longlong * param_2)

bool FUN_140080680(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_1400806e0 @ 1400806e0  undefined FUN_1400806e0(ulonglong param_1)

void FUN_1400806e0(ulonglong param_1)

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


// ==== FUN_140080760 @ 140080760  undefined FUN_140080760(ulonglong param_1)

void FUN_140080760(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x20)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 << 5);
  return;
}


// ==== FUN_140080800 @ 140080800  undefined FUN_140080800(ulonglong param_1)

void FUN_140080800(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x20)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 << 5);
  return;
}


// ==== FUN_1400808a0 @ 1400808a0  undefined FUN_1400808a0(ulonglong param_1)

void FUN_1400808a0(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x10)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 << 4);
  return;
}


// ==== FUN_140080930 @ 140080930  undefined FUN_140080930(ulonglong param_1)

void FUN_140080930(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 4)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 << 2);
  return;
}


// ==== FUN_140080a70 @ 140080a70  void * FUN_140080a70(void * param_1, longlong param_2, void * param_3)

void * FUN_140080a70(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _DstSize = lVar1 * 4;
  if (0 < lVar1) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_140080b00 @ 140080b00  undefined8 * FUN_140080b00(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_140080b00(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  param_1[1] = param_2;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14) = 1;
  *param_1 = std::tr1::_Ref_count<struct_NodeInfo>::vftable;
  return param_1;
}


// ==== FUN_140080b60 @ 140080b60  undefined FUN_140080b60(undefined8 * param_1)

void FUN_140080b60(undefined8 *param_1)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  return;
}


// ==== FUN_140080ba0 @ 140080ba0  bool FUN_140080ba0(longlong * param_1, longlong * param_2)

bool FUN_140080ba0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_140080c40 @ 140080c40  void * FUN_140080c40(void * param_1, longlong param_2, longlong param_3)

void * FUN_140080c40(void *param_1,longlong param_2,longlong param_3)

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


// ==== FUN_140080ca0 @ 140080ca0  void * FUN_140080ca0(void * param_1, longlong param_2, void * param_3)

void * FUN_140080ca0(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_140080e10 @ 140080e10  longlong * FUN_140080e10(longlong * param_1)

longlong * FUN_140080e10(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140080e32;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140080e32:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + 0x30;
  return param_1;
}


// ==== FUN_140080e50 @ 140080e50  longlong FUN_140080e50(longlong * param_1, longlong * param_2)

longlong FUN_140080e50(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return (param_1[1] - param_2[1]) / 0x30;
}


// ==== FUN_140080eb0 @ 140080eb0  longlong * FUN_140080eb0(longlong * param_1)

longlong * FUN_140080eb0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140080ed2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140080ed2:
  if (param_1[1] == puVar1[5]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = *(longlong *)param_1[1];
  return param_1;
}


// ==== FUN_140080f00 @ 140080f00  bool FUN_140080f00(longlong * param_1, longlong * param_2)

bool FUN_140080f00(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_140080f40 @ 140080f40  longlong FUN_140080f40(longlong * param_1)

longlong FUN_140080f40(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140080f62;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140080f62:
  if (param_1[1] == puVar1[5]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x10;
}


// ==== FUN_140080f80 @ 140080f80  longlong * FUN_140080f80(longlong * param_1)

longlong * FUN_140080f80(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140080fa2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140080fa2:
  if (param_1[1] == puVar1[5]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = *(longlong *)param_1[1];
  return param_1;
}


// ==== FUN_140080fd0 @ 140080fd0  bool FUN_140080fd0(longlong * param_1, longlong * param_2)

bool FUN_140080fd0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_140081010 @ 140081010  undefined FUN_140081010(undefined8 * param_1)

void FUN_140081010(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140081020 @ 140081020  undefined FUN_140081020(undefined8 * param_1)

void FUN_140081020(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140081030 @ 140081030  undefined FUN_140081030(longlong param_1)

void FUN_140081030(longlong param_1)

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


// ==== FUN_140081070 @ 140081070  undefined FUN_140081070(undefined8 * param_1)

void FUN_140081070(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140081080 @ 140081080  undefined FUN_140081080(undefined8 * param_1)

void FUN_140081080(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140081090 @ 140081090  undefined FUN_140081090(longlong param_1)

void FUN_140081090(longlong param_1)

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


// ==== FUN_1400810d0 @ 1400810d0  undefined FUN_1400810d0(longlong param_1)

void FUN_1400810d0(longlong param_1)

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


// ==== FUN_140081110 @ 140081110  undefined FUN_140081110(longlong param_1)

void FUN_140081110(longlong param_1)

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


// ==== FUN_140081150 @ 140081150  undefined FUN_140081150(longlong param_1)

void FUN_140081150(longlong param_1)

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


// ==== FUN_140081190 @ 140081190  longlong FUN_140081190(longlong * param_1)

longlong FUN_140081190(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_1400811b2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_1400811b2:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_1400811d0 @ 1400811d0  longlong FUN_1400811d0(longlong * param_1)

longlong FUN_1400811d0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_1400811f2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_1400811f2:
  if (param_1[1] == puVar1[5]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x10;
}


// ==== FUN_140081210 @ 140081210  longlong * FUN_140081210(longlong * param_1, longlong * param_2)

longlong * FUN_140081210(longlong *param_1,longlong *param_2)

{
  undefined8 *puVar1;
  
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140081247;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140081247:
  if (param_1[1] == puVar1[5]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = *(longlong *)param_1[1];
  return param_2;
}


// ==== FUN_140081270 @ 140081270  undefined FUN_140081270(undefined8 * param_1)

void FUN_140081270(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140081290 @ 140081290  undefined FUN_140081290(undefined8 * param_1)

void FUN_140081290(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_1400812d0 @ 1400812d0  undefined8 * FUN_1400812d0(undefined8 * param_1)

undefined8 * FUN_1400812d0(undefined8 *param_1)

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


// ==== FUN_140081310 @ 140081310  undefined FUN_140081310(undefined8 param_1, ulonglong param_2)

void FUN_140081310(undefined8 param_1,ulonglong param_2)

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


// ==== FUN_140081380 @ 140081380  undefined FUN_140081380(undefined8 param_1, ulonglong param_2)

void FUN_140081380(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x20)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 << 5);
  return;
}


// ==== FUN_140081410 @ 140081410  undefined FUN_140081410(undefined8 param_1, ulonglong param_2)

void FUN_140081410(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x20)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 << 5);
  return;
}


// ==== FUN_1400814a0 @ 1400814a0  undefined FUN_1400814a0(undefined8 * param_1, undefined8 param_2, longlong param_3)

void FUN_1400814a0(undefined8 *param_1,undefined8 param_2,longlong param_3)

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


// ==== FUN_140081540 @ 140081540  longlong * FUN_140081540(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_140081540(longlong *param_1,longlong *param_2,longlong param_3)

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
  uVar3 = param_3 * 0x10 + lVar2;
  if (uVar3 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar4 = *plVar1;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar3) goto LAB_1400815ad;
  }
  _invalid_parameter_noinfo();
LAB_1400815ad:
  *param_2 = (longlong)plVar1;
  param_2[1] = uVar3;
  return param_2;
}


// ==== FUN_140081640 @ 140081640  undefined8 * FUN_140081640(undefined8 * param_1)

undefined8 * FUN_140081640(undefined8 *param_1)

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


// ==== FUN_140081680 @ 140081680  undefined FUN_140081680(undefined8 param_1, ulonglong param_2)

void FUN_140081680(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x10)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 << 4);
  return;
}


// ==== FUN_140081710 @ 140081710  undefined8 * FUN_140081710(undefined8 * param_1)

undefined8 * FUN_140081710(undefined8 *param_1)

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


// ==== FUN_140081750 @ 140081750  undefined FUN_140081750(undefined8 param_1, ulonglong param_2)

void FUN_140081750(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 4)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 4);
  return;
}


// ==== FUN_1400817d0 @ 1400817d0  longlong * FUN_1400817d0(longlong * param_1, longlong param_2)

longlong * FUN_1400817d0(longlong *param_1,longlong param_2)

{
  FUN_140080560(param_1,param_2);
  return param_1;
}


// ==== FUN_140081800 @ 140081800  undefined8 * FUN_140081800(undefined8 * param_1)

undefined8 * FUN_140081800(undefined8 *param_1)

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


// ==== FUN_140081840 @ 140081840  undefined8 * FUN_140081840(undefined8 * param_1)

undefined8 * FUN_140081840(undefined8 *param_1)

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


// ==== FUN_140081880 @ 140081880  longlong * FUN_140081880(longlong * param_1, longlong param_2)

longlong * FUN_140081880(longlong *param_1,longlong param_2)

{
  FUN_140080610(param_1,param_2);
  return param_1;
}


// ==== FUN_1400818a0 @ 1400818a0  bool FUN_1400818a0(longlong * param_1, longlong * param_2)

bool FUN_1400818a0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_140081910 @ 140081910  undefined FUN_140081910(undefined8 * param_1, undefined8 param_2, longlong param_3)

void FUN_140081910(undefined8 *param_1,undefined8 param_2,longlong param_3)

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


// ==== FUN_1400819a0 @ 1400819a0  undefined FUN_1400819a0(undefined8 * param_1, undefined8 param_2, longlong param_3)

void FUN_1400819a0(undefined8 *param_1,undefined8 param_2,longlong param_3)

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


// ==== FUN_140081a30 @ 140081a30  undefined FUN_140081a30(undefined8 * param_1, undefined8 param_2, longlong param_3)

void FUN_140081a30(undefined8 *param_1,undefined8 param_2,longlong param_3)

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


// ==== FUN_140081b10 @ 140081b10  void * FUN_140081b10(void * param_1, longlong param_2, longlong param_3)

void * FUN_140081b10(void *param_1,longlong param_2,longlong param_3)

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


// ==== FUN_140081b50 @ 140081b50  bool FUN_140081b50(longlong param_1, longlong param_2)

bool FUN_140081b50(longlong param_1,longlong param_2)

{
  bool bVar1;
  
  if ((*(longlong *)(param_1 + 8) != *(longlong *)(param_2 + 8)) ||
     (bVar1 = true, *(longlong *)(param_1 + 0x10) != *(longlong *)(param_2 + 0x10))) {
    bVar1 = false;
  }
  return !bVar1;
}


// ==== FUN_140081bc0 @ 140081bc0  bool FUN_140081bc0(longlong * param_1, longlong * param_2)

bool FUN_140081bc0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_140081c10 @ 140081c10  undefined FUN_140081c10(undefined8 * param_1)

void FUN_140081c10(undefined8 *param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = (longlong *)param_1[1];
  if (plVar3 == (longlong *)0x0) {
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
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
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
  param_1[1] = 0;
  *param_1 = 0;
  return;
}


// ==== FUN_140081cb0 @ 140081cb0  void * FUN_140081cb0(void * param_1, longlong param_2, void * param_3)

void * FUN_140081cb0(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_140081dc0 @ 140081dc0  undefined FUN_140081dc0(longlong param_1)

void FUN_140081dc0(longlong param_1)

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


// ==== FUN_140081e00 @ 140081e00  undefined8 * FUN_140081e00(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140081e00(undefined8 *param_1,undefined8 *param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_1400814a0(param_1,*param_2,param_2[1]);
  return param_1;
}


// ==== FUN_140081e30 @ 140081e30  undefined FUN_140081e30(longlong param_1)

void FUN_140081e30(longlong param_1)

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


// ==== FUN_140081e70 @ 140081e70  undefined8 * FUN_140081e70(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140081e70(undefined8 *param_1,undefined8 *param_2)

{
  FUN_1400814a0(param_1,*param_2,param_2[1]);
  return param_1;
}


// ==== FUN_140081e90 @ 140081e90  undefined FUN_140081e90(longlong param_1)

void FUN_140081e90(longlong param_1)

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


// ==== FUN_140081ed0 @ 140081ed0  undefined FUN_140081ed0(longlong param_1)

void FUN_140081ed0(longlong param_1)

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


// ==== FUN_140081f10 @ 140081f10  undefined FUN_140081f10(longlong param_1)

void FUN_140081f10(longlong param_1)

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


// ==== FUN_140081f50 @ 140081f50  longlong FUN_140081f50(longlong * param_1)

longlong FUN_140081f50(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140081f72;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140081f72:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_140081f90 @ 140081f90  longlong FUN_140081f90(longlong * param_1)

longlong FUN_140081f90(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140081fb2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140081fb2:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_140081fd0 @ 140081fd0  longlong FUN_140081fd0(longlong * param_1)

longlong FUN_140081fd0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140081ff2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140081ff2:
  if (param_1[1] == puVar1[5]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x10;
}


// ==== FUN_140082010 @ 140082010  longlong FUN_140082010(longlong * param_1)

longlong FUN_140082010(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140082032;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140082032:
  if (param_1[1] == puVar1[5]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x10;
}


// ==== FUN_140082050 @ 140082050  longlong * FUN_140082050(longlong * param_1)

longlong * FUN_140082050(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140082072;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140082072:
  if (param_1[1] == puVar1[5]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = *(longlong *)param_1[1];
  return param_1;
}


// ==== FUN_1400820a0 @ 1400820a0  undefined FUN_1400820a0(undefined8 * param_1)

void FUN_1400820a0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_1400820c0 @ 1400820c0  undefined FUN_1400820c0(undefined8 * param_1)

void FUN_1400820c0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_1400820e0 @ 1400820e0  undefined FUN_1400820e0(undefined8 * param_1)

void FUN_1400820e0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140082100 @ 140082100  undefined8 FUN_140082100(longlong param_1, ulonglong param_2)

undefined8 FUN_140082100(longlong param_1,ulonglong param_2)

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
      FUN_140080070();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_140081310(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
    *(ulonglong *)(param_1 + 0x28) = param_2 * 0x30 + lVar3;
  }
  return uVar2;
}


// ==== FUN_140082170 @ 140082170  undefined8 * FUN_140082170(undefined8 * param_1)

undefined8 * FUN_140082170(undefined8 *param_1)

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


// ==== FUN_1400821c0 @ 1400821c0  undefined FUN_1400821c0(void)

void FUN_1400821c0(void)

{
  void *pvVar1;
  
  pvVar1 = operator_new(0x20);
  if (pvVar1 != (void *)0x0) {
    *(void **)pvVar1 = pvVar1;
  }
  if ((undefined8 *)((longlong)pvVar1 + 8) != (undefined8 *)0x0) {
    *(undefined8 *)((longlong)pvVar1 + 8) = pvVar1;
  }
  return;
}


// ==== FUN_140082200 @ 140082200  undefined8 * FUN_140082200(undefined8 * param_1)

undefined8 * FUN_140082200(undefined8 *param_1)

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


// ==== FUN_140082240 @ 140082240  undefined FUN_140082240(void)

void FUN_140082240(void)

{
  void *pvVar1;
  
  pvVar1 = operator_new(0x20);
  if (pvVar1 != (void *)0x0) {
    *(void **)pvVar1 = pvVar1;
  }
  if ((undefined8 *)((longlong)pvVar1 + 8) != (undefined8 *)0x0) {
    *(undefined8 *)((longlong)pvVar1 + 8) = pvVar1;
  }
  return;
}


// ==== FUN_140082280 @ 140082280  undefined FUN_140082280(undefined8 * param_1)

void FUN_140082280(undefined8 *param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = (longlong *)param_1[1];
  if (plVar3 == (longlong *)0x0) {
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
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
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
  param_1[1] = 0;
  *param_1 = 0;
  return;
}


// ==== FUN_140082310 @ 140082310  undefined8 * FUN_140082310(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_140082310(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_140082350 @ 140082350  longlong * FUN_140082350(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_140082350(longlong *param_1,longlong *param_2,longlong param_3)

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
  uVar3 = param_3 * -0x10 + lVar2;
  if (uVar3 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar4 = *plVar1;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar3) goto LAB_1400823c0;
  }
  _invalid_parameter_noinfo();
LAB_1400823c0:
  *param_2 = (longlong)plVar1;
  param_2[1] = uVar3;
  return param_2;
}


// ==== FUN_140082400 @ 140082400  undefined8 FUN_140082400(longlong param_1, ulonglong param_2)

undefined8 FUN_140082400(longlong param_1,ulonglong param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  longlong lVar3;
  
  uVar2 = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  if (param_2 != 0) {
    if (0xfffffffffffffff < param_2) {
      FUN_140080260();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_140081680(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    *(ulonglong *)(param_1 + 0x28) = param_2 * 0x10 + lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
  }
  return uVar2;
}


// ==== FUN_140082470 @ 140082470  undefined8 * FUN_140082470(undefined8 * param_1)

undefined8 * FUN_140082470(undefined8 *param_1)

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


// ==== FUN_1400824c0 @ 1400824c0  undefined FUN_1400824c0(longlong param_1, ulonglong param_2)

void FUN_1400824c0(longlong param_1,ulonglong param_2)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [48];
  
  if (0xfffffffffffffffU - *(longlong *)(param_1 + 0x30) < param_2) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_70,"list<T> too long");
    std::exception::exception((exception *)local_48);
    local_48[0] = std::logic_error::vftable;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
    local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
  }
  *(ulonglong *)(param_1 + 0x30) = *(longlong *)(param_1 + 0x30) + param_2;
  return;
}


// ==== FUN_140082550 @ 140082550  undefined8 FUN_140082550(longlong param_1, ulonglong param_2)

undefined8 FUN_140082550(longlong param_1,ulonglong param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  longlong lVar3;
  
  uVar2 = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  if (param_2 != 0) {
    if (0x3fffffffffffffff < param_2) {
      FUN_1400803c0();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_140081750(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    lVar3 = lVar3 + param_2 * 4;
    *(longlong *)(param_1 + 0x28) = lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
  }
  return uVar2;
}


// ==== FUN_1400825b0 @ 1400825b0  undefined8 * FUN_1400825b0(undefined8 * param_1)

undefined8 * FUN_1400825b0(undefined8 *param_1)

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


// ==== FUN_140082600 @ 140082600  undefined FUN_140082600(longlong param_1, ulonglong param_2)

void FUN_140082600(longlong param_1,ulonglong param_2)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [48];
  
  if (0xfffffffffffffffU - *(longlong *)(param_1 + 0x30) < param_2) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_70,"list<T> too long");
    std::exception::exception((exception *)local_48);
    local_48[0] = std::logic_error::vftable;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
    local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
  }
  *(ulonglong *)(param_1 + 0x30) = *(longlong *)(param_1 + 0x30) + param_2;
  return;
}


// ==== FUN_140082690 @ 140082690  longlong * FUN_140082690(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_140082690(longlong *param_1,longlong *param_2,longlong param_3)

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
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar3) goto LAB_140082701;
  }
  _invalid_parameter_noinfo();
LAB_140082701:
  *param_2 = (longlong)plVar1;
  param_2[1] = uVar3;
  return param_2;
}


// ==== FUN_140082740 @ 140082740  longlong * FUN_140082740(longlong * param_1, longlong param_2)

longlong * FUN_140082740(longlong *param_1,longlong param_2)

{
  FUN_140080560(param_1,-param_2);
  return param_1;
}


// ==== FUN_140082760 @ 140082760  undefined8 * FUN_140082760(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140082760(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_1400827c0 @ 1400827c0  undefined8 * FUN_1400827c0(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_1400827c0(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_140082800 @ 140082800  undefined8 * FUN_140082800(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140082800(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_140082860 @ 140082860  undefined8 * FUN_140082860(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140082860(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_1400828c0 @ 1400828c0  undefined8 * FUN_1400828c0(undefined8 * param_1)

undefined8 * FUN_1400828c0(undefined8 *param_1)

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


// ==== FUN_140082930 @ 140082930  undefined8 * FUN_140082930(undefined8 * param_1)

undefined8 * FUN_140082930(undefined8 *param_1)

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


// ==== FUN_140082980 @ 140082980  undefined8 * FUN_140082980(undefined8 * param_1, undefined8 param_2, undefined8 param_3, undefined8 * param_4)

undefined8 *
FUN_140082980(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 *param_4)

{
  *param_1 = 0;
  param_1[1] = param_2;
  param_1[2] = param_3;
  if (param_4 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_4;
  return param_1;
}


// ==== FUN_1400829c0 @ 1400829c0  undefined8 * FUN_1400829c0(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_1400829c0(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  param_1[1] = param_2;
  *param_1 = 0;
  param_1[2] = 0;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_140082a00 @ 140082a00  longlong * FUN_140082a00(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_140082a00(longlong *param_1,longlong *param_2,longlong param_3)

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
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar1) goto LAB_140082a6a;
  }
  _invalid_parameter_noinfo();
LAB_140082a6a:
  *param_2 = (longlong)plVar2;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_140082aa0 @ 140082aa0  undefined8 * FUN_140082aa0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140082aa0(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_140082af0 @ 140082af0  undefined8 * FUN_140082af0(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140082af0(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_140082b70 @ 140082b70  undefined FUN_140082b70(undefined8 * param_1, undefined8 * param_2)

void FUN_140082b70(undefined8 *param_1,undefined8 *param_2)

{
  if (param_1 != (undefined8 *)0x0) {
    *param_1 = 0;
    param_1[1] = 0;
    FUN_1400814a0(param_1,*param_2,param_2[1]);
  }
  return;
}


// ==== FUN_140082bb0 @ 140082bb0  void * FUN_140082bb0(void * param_1, longlong param_2, void * param_3)

void * FUN_140082bb0(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _DstSize = lVar1 * 4;
  if (0 < lVar1) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_140082c30 @ 140082c30  void * FUN_140082c30(void * param_1, longlong param_2, longlong param_3)

void * FUN_140082c30(void *param_1,longlong param_2,longlong param_3)

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


// ==== FUN_140082c70 @ 140082c70  undefined FUN_140082c70(longlong param_1)

void FUN_140082c70(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_1 + 0x18);
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


// ==== FUN_140082cc0 @ 140082cc0  undefined FUN_140082cc0(longlong param_1)

void FUN_140082cc0(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_1 + 0x18);
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


// ==== FUN_140082d10 @ 140082d10  undefined FUN_140082d10(longlong param_1)

void FUN_140082d10(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_1 + 0x20);
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


// ==== FUN_140082d60 @ 140082d60  undefined8 * FUN_140082d60(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140082d60(undefined8 *param_1,undefined8 *param_2)

{
  FUN_140081a30(param_1,*param_2,param_2[1]);
  return param_1;
}


// ==== FUN_140082d80 @ 140082d80  undefined8 * FUN_140082d80(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_140082d80(undefined8 *param_1,undefined8 *param_2,longlong param_3)

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


// ==== FUN_140082df0 @ 140082df0  void * FUN_140082df0(void * param_1, longlong param_2, void * param_3)

void * FUN_140082df0(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_140082e60 @ 140082e60  void * FUN_140082e60(void * param_1, uint param_2)

void * FUN_140082e60(void *param_1,uint param_2)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)((longlong)param_1 + 8);
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
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_140082ed0 @ 140082ed0  undefined8 * FUN_140082ed0(undefined8 * param_1)

undefined8 * FUN_140082ed0(undefined8 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_140081c10(param_1);
  return param_1;
}


// ==== FUN_140082ef0 @ 140082ef0  undefined8 * FUN_140082ef0(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

undefined8 * FUN_140082ef0(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  longlong *plVar1;
  int *piVar2;
  longlong lVar3;
  undefined8 uVar4;
  longlong *plVar5;
  
  if (param_1 != param_2) {
    do {
      lVar3 = param_1[1];
      uVar4 = *param_1;
      if (lVar3 != 0) {
        LOCK();
        *(int *)(lVar3 + 0x10) = *(int *)(lVar3 + 0x10) + 1;
        UNLOCK();
      }
      plVar5 = (longlong *)param_3[1];
      if (plVar5 != (longlong *)0x0) {
        LOCK();
        plVar1 = plVar5 + 2;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)*plVar1 == 0) {
          (**(code **)*plVar5)(plVar5);
          LOCK();
          piVar2 = (int *)((longlong)plVar5 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*plVar5 + 8))(plVar5);
          }
        }
      }
      param_1 = param_1 + 2;
      param_3[1] = lVar3;
      *param_3 = uVar4;
      param_3 = param_3 + 2;
    } while (param_1 != param_2);
  }
  return param_3;
}


// ==== FUN_140082fc0 @ 140082fc0  undefined8 * FUN_140082fc0(undefined8 * param_1)

undefined8 * FUN_140082fc0(undefined8 *param_1)

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


// ==== FUN_140083060 @ 140083060  undefined8 * FUN_140083060(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140083060(undefined8 *param_1,undefined8 *param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_140081910(param_1,*param_2,param_2[1]);
  return param_1;
}


// ==== FUN_1400830b0 @ 1400830b0  undefined8 * FUN_1400830b0(undefined8 * param_1)

undefined8 * FUN_1400830b0(undefined8 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_140082280(param_1);
  return param_1;
}


// ==== FUN_1400830d0 @ 1400830d0  undefined8 * FUN_1400830d0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_1400830d0(undefined8 *param_1,undefined8 *param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_1400819a0(param_1,*param_2,param_2[1]);
  return param_1;
}


// ==== FUN_140083100 @ 140083100  undefined FUN_140083100(undefined8 * param_1)

void FUN_140083100(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140083120 @ 140083120  undefined FUN_140083120(undefined8 * param_1)

void FUN_140083120(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140083140 @ 140083140  undefined8 * FUN_140083140(undefined8 * param_1)

undefined8 * FUN_140083140(undefined8 *param_1)

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


// ==== FUN_1400831a0 @ 1400831a0  undefined8 * FUN_1400831a0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_1400831a0(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_1400831f0 @ 1400831f0  undefined8 * FUN_1400831f0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_1400831f0(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_140083240 @ 140083240  undefined8 * FUN_140083240(undefined8 * param_1)

undefined8 * FUN_140083240(undefined8 *param_1)

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


// ==== FUN_1400832e0 @ 1400832e0  undefined8 * FUN_1400832e0(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_1400832e0(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_140083340 @ 140083340  longlong * FUN_140083340(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_140083340(longlong *param_1,longlong *param_2,longlong param_3)

{
  longlong *plVar1;
  longlong lVar2;
  longlong lVar3;
  ulonglong uVar4;
  longlong lVar5;
  
  plVar1 = (longlong *)*param_1;
  lVar2 = param_1[1];
  lVar3 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar3;
  }
  else {
    lVar5 = *plVar1;
  }
  uVar4 = param_3 * -0x30 + lVar2;
  if (uVar4 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar4) goto LAB_1400833b4;
  }
  _invalid_parameter_noinfo();
LAB_1400833b4:
  *param_2 = (longlong)plVar1;
  param_2[1] = uVar4;
  return param_2;
}


// ==== FUN_1400833f0 @ 1400833f0  undefined8 * FUN_1400833f0(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_1400833f0(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_140083430 @ 140083430  undefined8 * FUN_140083430(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_140083430(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_140083470 @ 140083470  undefined8 * FUN_140083470(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140083470(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_1400834c0 @ 1400834c0  undefined8 * FUN_1400834c0(undefined8 * param_1)

undefined8 * FUN_1400834c0(undefined8 *param_1)

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


// ==== FUN_140083510 @ 140083510  undefined FUN_140083510(longlong param_1)

void FUN_140083510(longlong param_1)

{
  if (*(void **)(param_1 + 0x18) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_140083540 @ 140083540  undefined8 * FUN_140083540(undefined8 * param_1)

undefined8 * FUN_140083540(undefined8 *param_1)

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


// ==== FUN_140083590 @ 140083590  undefined8 * FUN_140083590(undefined8 * param_1, longlong * param_2)

undefined8 * FUN_140083590(undefined8 *param_1,longlong *param_2)

{
  longlong lVar1;
  longlong lVar2;
  undefined8 *puVar3;
  
  if ((undefined8 *)*param_2 == (undefined8 *)0x0) {
    puVar3 = (undefined8 *)0x0;
  }
  else {
    puVar3 = *(undefined8 **)*param_2;
  }
  lVar1 = param_2[2];
  lVar2 = param_2[1];
  *param_1 = 0;
  param_1[1] = lVar2;
  param_1[2] = lVar1;
  if (puVar3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *puVar3;
  return param_1;
}


// ==== FUN_1400835f0 @ 1400835f0  undefined8 * FUN_1400835f0(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_1400835f0(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  param_1[1] = param_2;
  *param_1 = 0;
  param_1[2] = 0;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_140083630 @ 140083630  undefined8 * FUN_140083630(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_140083630(undefined8 *param_1,undefined8 *param_2,longlong param_3)

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


// ==== FUN_140083690 @ 140083690  undefined FUN_140083690(undefined8 param_1, undefined8 * param_2, undefined8 * param_3)

void FUN_140083690(undefined8 param_1,undefined8 *param_2,undefined8 *param_3)

{
  if (param_2 != (undefined8 *)0x0) {
    *param_2 = 0;
    param_2[1] = 0;
    FUN_1400814a0(param_2,*param_3,param_3[1]);
  }
  return;
}


// ==== FUN_1400836e0 @ 1400836e0  undefined8 * FUN_1400836e0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_1400836e0(undefined8 *param_1,undefined8 *param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_140081a30(param_1,*param_2,param_2[1]);
  return param_1;
}


// ==== FUN_140083710 @ 140083710  undefined8 * FUN_140083710(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140083710(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_140083770 @ 140083770  undefined8 * FUN_140083770(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_140083770(undefined8 *param_1,undefined8 *param_2,longlong param_3)

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


// ==== FUN_1400837d0 @ 1400837d0  undefined FUN_1400837d0(undefined8 * param_1, undefined8 * param_2)

void FUN_1400837d0(undefined8 *param_1,undefined8 *param_2)

{
  if (param_1 != (undefined8 *)0x0) {
    *param_1 = 0;
    param_1[1] = 0;
    FUN_1400819a0(param_1,*param_2,param_2[1]);
  }
  return;
}


// ==== FUN_140083810 @ 140083810  void * FUN_140083810(void * param_1, uint param_2)

void * FUN_140083810(void *param_1,uint param_2)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)((longlong)param_1 + 0x18);
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
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_140083890 @ 140083890  void * FUN_140083890(void * param_1, uint param_2)

void * FUN_140083890(void *param_1,uint param_2)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)((longlong)param_1 + 0x18);
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
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_140083910 @ 140083910  undefined FUN_140083910(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

void FUN_140083910(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  longlong *plVar1;
  int *piVar2;
  longlong lVar3;
  undefined8 uVar4;
  longlong *plVar5;
  
  if (param_1 != param_2) {
    do {
      lVar3 = param_3[1];
      uVar4 = *param_3;
      if (lVar3 != 0) {
        LOCK();
        *(int *)(lVar3 + 0x10) = *(int *)(lVar3 + 0x10) + 1;
        UNLOCK();
      }
      plVar5 = (longlong *)param_1[1];
      if (plVar5 != (longlong *)0x0) {
        LOCK();
        plVar1 = plVar5 + 2;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)*plVar1 == 0) {
          (**(code **)*plVar5)(plVar5);
          LOCK();
          piVar2 = (int *)((longlong)plVar5 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*plVar5 + 8))(plVar5);
          }
        }
      }
      param_1[1] = lVar3;
      *param_1 = uVar4;
      param_1 = param_1 + 2;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_1400839b0 @ 1400839b0  void * FUN_1400839b0(void * param_1, longlong param_2, void * param_3)

void * FUN_1400839b0(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_140083a20 @ 140083a20  void * FUN_140083a20(void * param_1, uint param_2)

void * FUN_140083a20(void *param_1,uint param_2)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)((longlong)param_1 + 0x20);
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
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_140083b10 @ 140083b10  undefined FUN_140083b10(undefined8 * param_1, undefined8 * param_2)

void FUN_140083b10(undefined8 *param_1,undefined8 *param_2)

{
  if (param_1 != (undefined8 *)0x0) {
    *param_1 = 0;
    param_1[1] = 0;
    FUN_140081a30(param_1,*param_2,param_2[1]);
  }
  return;
}


// ==== FUN_140083b50 @ 140083b50  undefined FUN_140083b50(longlong param_1)

void FUN_140083b50(longlong param_1)

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


// ==== FUN_140083b90 @ 140083b90  longlong FUN_140083b90(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

longlong FUN_140083b90(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  FUN_140082ef0(param_1,param_2,param_3);
  return (longlong)param_3 + ((longlong)param_2 - (longlong)param_1 & 0xfffffffffffffff0U);
}


// ==== FUN_140083c10 @ 140083c10  longlong FUN_140083c10(longlong param_1)

longlong FUN_140083c10(longlong param_1)

{
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  FUN_140082280((undefined8 *)(param_1 + 0x18));
  return param_1;
}


// ==== FUN_140083c50 @ 140083c50  undefined FUN_140083c50(void)

int FUN_140083c50(longlong param_1,int *param_2)

{
  longlong *plVar1;
  int iVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong *plVar5;
  int *piVar6;
  undefined8 *puVar7;
  longlong lVar8;
  
  puVar7 = (undefined8 *)**(undefined8 **)(param_1 + 0x90);
  plVar3 = *(longlong **)(param_1 + 0x68);
  while( true ) {
    puVar4 = *(undefined8 **)(param_1 + 0x90);
    if ((plVar3 == (longlong *)0x0) || (plVar3 != *(longlong **)(param_1 + 0x68))) {
      _invalid_parameter_noinfo();
    }
    if (puVar7 == puVar4) break;
    if (plVar3 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar8 = 0;
    }
    else {
      lVar8 = *plVar3;
    }
    if (puVar7 == *(undefined8 **)(lVar8 + 0x28)) {
      _invalid_parameter_noinfo();
    }
    plVar5 = (longlong *)puVar7[3];
    piVar6 = (int *)puVar7[2];
    if (plVar5 != (longlong *)0x0) {
      LOCK();
      *(int *)(plVar5 + 2) = (int)plVar5[2] + 1;
      UNLOCK();
    }
    if ((*piVar6 == *param_2) && (piVar6[1] == param_2[1])) {
      iVar2 = piVar6[4];
      if (plVar5 != (longlong *)0x0) {
        LOCK();
        plVar3 = plVar5 + 2;
        *(int *)plVar3 = (int)*plVar3 + -1;
        UNLOCK();
        if ((int)*plVar3 == 0) {
          (**(code **)*plVar5)(plVar5);
          LOCK();
          piVar6 = (int *)((longlong)plVar5 + 0x14);
          *piVar6 = *piVar6 + -1;
          UNLOCK();
          if (*piVar6 == 0) {
            (**(code **)(*plVar5 + 8))(plVar5);
          }
        }
      }
      return iVar2;
    }
    if (plVar5 != (longlong *)0x0) {
      LOCK();
      plVar1 = plVar5 + 2;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)*plVar1 == 0) {
        (**(code **)*plVar5)(plVar5);
        LOCK();
        piVar6 = (int *)((longlong)plVar5 + 0x14);
        *piVar6 = *piVar6 + -1;
        UNLOCK();
        if (*piVar6 == 0) {
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
    }
    if (plVar3 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar8 = 0;
    }
    else {
      lVar8 = *plVar3;
    }
    if (puVar7 == *(undefined8 **)(lVar8 + 0x28)) {
      _invalid_parameter_noinfo();
    }
    puVar7 = (undefined8 *)*puVar7;
  }
  return -1;
}


// ==== FUN_140083db0 @ 140083db0  undefined8 * FUN_140083db0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140083db0(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_140083e00 @ 140083e00  undefined8 * FUN_140083e00(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140083e00(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_140083e50 @ 140083e50  ulonglong FUN_140083e50(longlong * param_1)

ulonglong FUN_140083e50(longlong *param_1)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  
  uVar1 = param_1[4];
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)*param_1;
  lVar4 = 0;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar3 = lVar4;
  }
  else {
    lVar3 = *plVar2;
  }
  uVar1 = uVar1 - 0x30;
  if (uVar1 <= *(ulonglong *)(lVar3 + 0x20)) {
    lVar3 = lVar4;
    if (plVar2 != (longlong *)0x0) {
      lVar3 = *plVar2;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar1) goto LAB_140083ec7;
  }
  _invalid_parameter_noinfo();
LAB_140083ec7:
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  else {
    lVar4 = *plVar2;
  }
  if (*(ulonglong *)(lVar4 + 0x20) <= uVar1) {
    _invalid_parameter_noinfo();
  }
  return uVar1;
}


// ==== FUN_140083f00 @ 140083f00  ulonglong FUN_140083f00(longlong * param_1)

ulonglong FUN_140083f00(longlong *param_1)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  
  uVar1 = param_1[4];
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)*param_1;
  lVar4 = 0;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar3 = lVar4;
  }
  else {
    lVar3 = *plVar2;
  }
  uVar1 = uVar1 - 0x10;
  if (uVar1 <= *(ulonglong *)(lVar3 + 0x20)) {
    lVar3 = lVar4;
    if (plVar2 != (longlong *)0x0) {
      lVar3 = *plVar2;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar1) goto LAB_140083f77;
  }
  _invalid_parameter_noinfo();
LAB_140083f77:
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  else {
    lVar4 = *plVar2;
  }
  if (*(ulonglong *)(lVar4 + 0x20) <= uVar1) {
    _invalid_parameter_noinfo();
  }
  return uVar1;
}


// ==== FUN_140084030 @ 140084030  longlong * FUN_140084030(longlong * param_1, longlong * param_2, int * param_3)

longlong * FUN_140084030(longlong *param_1,longlong *param_2,int *param_3)

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
  if (*(char *)((longlong)puVar4[1] + 0x21) == '\0') {
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
    } while (*(char *)((longlong)puVar2 + 0x21) == '\0');
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


// ==== FUN_140084100 @ 140084100  undefined FUN_140084100(undefined8 * param_1)

void FUN_140084100(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140084120 @ 140084120  undefined FUN_140084120(undefined8 * param_1)

void FUN_140084120(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140084140 @ 140084140  undefined8 * FUN_140084140(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_140084140(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  undefined8 uVar1;
  
  uVar1 = *(undefined8 *)(param_3 + 8);
  *param_2 = 0;
  param_2[1] = uVar1;
  if (param_1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_2 = *param_1;
  return param_2;
}


// ==== FUN_140084180 @ 140084180  undefined8 * FUN_140084180(undefined8 * param_1)

undefined8 * FUN_140084180(undefined8 *param_1)

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


// ==== FUN_1400841d0 @ 1400841d0  undefined FUN_1400841d0(undefined8 * param_1)

void FUN_1400841d0(undefined8 *param_1)

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


// ==== FUN_140084210 @ 140084210  undefined8 * FUN_140084210(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_140084210(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  undefined8 uVar1;
  
  uVar1 = *(undefined8 *)(param_3 + 8);
  *param_2 = 0;
  param_2[1] = uVar1;
  if (param_1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_2 = *param_1;
  return param_2;
}


// ==== FUN_140084250 @ 140084250  undefined8 * FUN_140084250(undefined8 * param_1)

undefined8 * FUN_140084250(undefined8 *param_1)

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


// ==== FUN_1400842a0 @ 1400842a0  undefined8 * FUN_1400842a0(longlong * param_1, undefined8 * param_2)

undefined8 * FUN_1400842a0(longlong *param_1,undefined8 *param_2)

{
  longlong lVar1;
  undefined8 *puVar2;
  
  if ((undefined8 *)*param_1 == (undefined8 *)0x0) {
    puVar2 = (undefined8 *)0x0;
  }
  else {
    puVar2 = *(undefined8 **)*param_1;
  }
  lVar1 = param_1[1];
  *param_2 = 0;
  param_2[1] = lVar1;
  param_2[2] = param_1[2];
  if (puVar2 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_2 = *puVar2;
  return param_2;
}


// ==== FUN_140084300 @ 140084300  undefined8 * FUN_140084300(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 * param_4)

undefined8 *
FUN_140084300(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 *param_4)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar2 = (undefined8 *)operator_new(0x20);
  if (puVar2 != (undefined8 *)0x0) {
    *puVar2 = param_2;
  }
  if (puVar2 + 1 != (undefined8 *)0x0) {
    puVar2[1] = param_3;
  }
  puVar1 = puVar2 + 2;
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = 0;
    puVar2[3] = 0;
    FUN_1400814a0(puVar1,*param_4,param_4[1]);
  }
  return puVar2;
}


// ==== FUN_1400843a0 @ 1400843a0  undefined8 * FUN_1400843a0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_1400843a0(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_1400843f0 @ 1400843f0  undefined8 * FUN_1400843f0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_1400843f0(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_140084440 @ 140084440  longlong * FUN_140084440(longlong * param_1, longlong * param_2, longlong param_3, longlong param_4)

longlong * FUN_140084440(longlong *param_1,longlong *param_2,longlong param_3,longlong param_4)

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


// ==== FUN_140084530 @ 140084530  undefined FUN_140084530(undefined8 param_1, undefined8 * param_2, undefined8 * param_3)

void FUN_140084530(undefined8 param_1,undefined8 *param_2,undefined8 *param_3)

{
  if (param_2 != (undefined8 *)0x0) {
    *param_2 = 0;
    param_2[1] = 0;
    FUN_1400819a0(param_2,*param_3,param_3[1]);
  }
  return;
}


// ==== FUN_140084580 @ 140084580  ulonglong FUN_140084580(longlong * param_1)

ulonglong FUN_140084580(longlong *param_1)

{
  ulonglong uVar1;
  longlong lVar2;
  
  if ((longlong *)*param_1 == (longlong *)0x0) {
    lVar2 = 0;
  }
  else {
    lVar2 = *(longlong *)*param_1;
  }
  uVar1 = *(ulonglong *)(lVar2 + 0x30);
  if (*(ulonglong *)(lVar2 + 0x38) < uVar1) {
    _invalid_parameter_noinfo();
  }
  return uVar1;
}


// ==== FUN_1400845b0 @ 1400845b0  undefined FUN_1400845b0(longlong param_1)

void FUN_1400845b0(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_1 + 0x18);
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


// ==== FUN_140084600 @ 140084600  undefined FUN_140084600(longlong param_1)

void FUN_140084600(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_1 + 0x18);
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


// ==== FUN_140084660 @ 140084660  void * FUN_140084660(undefined8 param_1, void * param_2, longlong param_3, void * param_4)

void * FUN_140084660(undefined8 param_1,void *param_2,longlong param_3,void *param_4)

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


// ==== FUN_1400846d0 @ 1400846d0  undefined FUN_1400846d0(undefined8 * param_1, undefined8 param_2)

void FUN_1400846d0(undefined8 *param_1,undefined8 param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x18);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = std::tr1::_Ref_count_base::vftable;
    puVar1[1] = param_2;
    *(undefined4 *)(puVar1 + 2) = 0;
    *(undefined4 *)((longlong)puVar1 + 0x14) = 1;
    *puVar1 = std::tr1::_Ref_count<struct_NodeInfo>::vftable;
  }
  FUN_1400814a0(param_1,param_2,(longlong)puVar1);
  return;
}


// ==== FUN_140084750 @ 140084750  undefined FUN_140084750(undefined8 param_1, undefined8 * param_2, undefined8 * param_3)

void FUN_140084750(undefined8 param_1,undefined8 *param_2,undefined8 *param_3)

{
  if (param_2 != (undefined8 *)0x0) {
    *param_2 = 0;
    param_2[1] = 0;
    FUN_140081a30(param_2,*param_3,param_3[1]);
  }
  return;
}


// ==== FUN_1400847a0 @ 1400847a0  undefined FUN_1400847a0(undefined8 param_1, longlong param_2)

void FUN_1400847a0(undefined8 param_1,longlong param_2)

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


// ==== FUN_1400847e0 @ 1400847e0  undefined8 * FUN_1400847e0(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

undefined8 * FUN_1400847e0(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 2) {
    if (param_3 != (undefined8 *)0x0) {
      *param_3 = 0;
      param_3[1] = 0;
      FUN_140081a30(param_3,*param_1,param_1[1]);
    }
    param_3 = param_3 + 2;
  }
  return param_3;
}


// ==== FUN_140084870 @ 140084870  longlong FUN_140084870(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

longlong FUN_140084870(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  FUN_140082ef0(param_1,param_2,param_3);
  return (longlong)param_3 + ((longlong)param_2 - (longlong)param_1 & 0xfffffffffffffff0U);
}


// ==== FUN_1400848c0 @ 1400848c0  undefined FUN_1400848c0(longlong * param_1)

void FUN_1400848c0(longlong *param_1)

{
  ulonglong uVar1;
  longlong lVar2;
  
  if (param_1[2] != 0) {
    param_1[2] = param_1[2] + -1;
    return;
  }
  if ((*param_1 == 0) || (param_1[1] == 0)) {
    _invalid_parameter_noinfo();
  }
  if ((longlong *)*param_1 == (longlong *)0x0) {
    lVar2 = 0;
  }
  else {
    lVar2 = *(longlong *)*param_1;
  }
  uVar1 = *(ulonglong *)(lVar2 + 0x30);
  if (*(ulonglong *)(lVar2 + 0x38) < uVar1) {
    _invalid_parameter_noinfo();
  }
  if ((ulonglong)param_1[1] <= uVar1) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + -4;
  param_1[2] = 0x1f;
  return;
}


// ==== FUN_140084970 @ 140084970  undefined8 * FUN_140084970(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

undefined8 * FUN_140084970(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 2) {
    if (param_3 != (undefined8 *)0x0) {
      *param_3 = 0;
      param_3[1] = 0;
      FUN_140081a30(param_3,*param_1,param_1[1]);
    }
    param_3 = param_3 + 2;
  }
  return param_3;
}


// ==== FUN_140084f40 @ 140084f40  undefined8 * FUN_140084f40(undefined8 * param_1)

undefined8 * FUN_140084f40(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  uVar2 = FUN_1400821c0();
  param_1[5] = uVar2;
  param_1[6] = 0;
  return param_1;
}


// ==== FUN_140084fa0 @ 140084fa0  undefined8 * FUN_140084fa0(undefined8 * param_1)

undefined8 * FUN_140084fa0(undefined8 *param_1)

{
  longlong *plVar1;
  longlong *plVar2;
  longlong *plVar3;
  
  plVar1 = (longlong *)operator_new(8);
  plVar3 = (longlong *)0x0;
  plVar2 = plVar3;
  if (plVar1 != (longlong *)0x0) {
    *plVar1 = (longlong)param_1;
    plVar2 = plVar1;
  }
  *param_1 = plVar2;
  param_1[2] = 0;
  plVar2 = (longlong *)operator_new(8);
  if (plVar2 != (longlong *)0x0) {
    *plVar2 = (longlong)(param_1 + 3);
    plVar3 = plVar2;
  }
  param_1[3] = plVar3;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  return param_1;
}


// ==== FUN_140085030 @ 140085030  undefined FUN_140085030(undefined8 * param_1)

void FUN_140085030(undefined8 *param_1)

{
  param_1[2] = 0;
  if ((void *)param_1[6] != (void *)0x0) {
    operator_delete((void *)param_1[6]);
  }
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  operator_delete((void *)param_1[3]);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_1400850a0 @ 1400850a0  undefined8 * FUN_1400850a0(undefined8 * param_1)

undefined8 * FUN_1400850a0(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  uVar2 = FUN_140082240();
  param_1[5] = uVar2;
  param_1[6] = 0;
  return param_1;
}


// ==== FUN_140085100 @ 140085100  undefined FUN_140085100(longlong param_1, longlong param_2, undefined8 * param_3)

void FUN_140085100(longlong param_1,longlong param_2,undefined8 *param_3)

{
  longlong lVar1;
  undefined8 *puVar2;
  
  lVar1 = *(longlong *)(param_2 + 8);
  puVar2 = FUN_140084300(param_1,lVar1,*(undefined8 *)(lVar1 + 8),param_3);
  FUN_1400824c0(param_1,1);
  *(undefined8 **)(lVar1 + 8) = puVar2;
  *(undefined8 **)puVar2[1] = puVar2;
  return;
}


// ==== FUN_140085150 @ 140085150  undefined FUN_140085150(undefined8 param_1, longlong param_2)

void FUN_140085150(undefined8 param_1,longlong param_2)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_2 + 0x18);
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


// ==== FUN_1400851a0 @ 1400851a0  undefined8 * FUN_1400851a0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_1400851a0(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  
  uVar1 = param_1[6];
  if ((ulonglong)param_1[7] < uVar1) {
    _invalid_parameter_noinfo();
  }
  param_2[1] = uVar1;
  *param_2 = 0;
  param_2[2] = 0;
  if (param_1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_2 = *param_1;
  return param_2;
}


// ==== FUN_140085200 @ 140085200  undefined FUN_140085200(undefined8 param_1, longlong param_2)

void FUN_140085200(undefined8 param_1,longlong param_2)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_2 + 0x18);
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


// ==== FUN_140085250 @ 140085250  undefined FUN_140085250(longlong param_1, ulonglong param_2)

/* WARNING: Removing unreachable block (ram,0x000140085264) */

void FUN_140085250(longlong param_1,ulonglong param_2)

{
  longlong *plVar1;
  void *_Dst;
  uint *puVar2;
  rsize_t _DstSize;
  void *_Src;
  ulonglong uVar3;
  longlong *plVar4;
  longlong lVar5;
  longlong lVar6;
  ulonglong uVar7;
  
  plVar1 = (longlong *)(param_1 + 0x18);
  uVar7 = param_2 + 0x1f >> 5;
  if ((ulonglong)(*(longlong *)(param_1 + 0x38) - *(longlong *)(param_1 + 0x30) >> 2) <= uVar7)
  goto LAB_140085382;
  _Src = *(void **)(param_1 + 0x38);
  if (_Src < *(void **)(param_1 + 0x30)) {
    _invalid_parameter_noinfo();
  }
  uVar3 = *(ulonglong *)(param_1 + 0x30);
  if (*(ulonglong *)(param_1 + 0x38) < uVar3) {
    _invalid_parameter_noinfo();
  }
  plVar4 = (longlong *)*plVar1;
  lVar5 = 0;
  if (plVar4 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar6 = lVar5;
  }
  else {
    lVar6 = *plVar4;
  }
  _Dst = (void *)(uVar3 + uVar7 * 4);
  if (*(void **)(lVar6 + 0x20) < _Dst) {
LAB_1400852fd:
    _invalid_parameter_noinfo();
  }
  else {
    if (plVar4 != (longlong *)0x0) {
      lVar5 = *plVar4;
    }
    if (_Dst < *(void **)(lVar5 + 0x18)) goto LAB_1400852fd;
  }
  if (((plVar1 == (longlong *)0x0) || (_Dst < *(void **)(param_1 + 0x30))) ||
     (*(void **)(param_1 + 0x38) < _Dst)) {
    _invalid_parameter_noinfo();
  }
  lVar5 = *plVar1;
  if ((_Src < *(void **)(param_1 + 0x30)) || (*(void **)(param_1 + 0x38) < _Src)) {
    _invalid_parameter_noinfo();
  }
  if ((lVar5 == 0) || (lVar5 != *plVar1)) {
    _invalid_parameter_noinfo();
  }
  if (_Dst != _Src) {
    lVar5 = *(longlong *)(param_1 + 0x38) - (longlong)_Src >> 2;
    _DstSize = lVar5 * 4;
    if (0 < lVar5) {
      memmove_s(_Dst,_DstSize,_Src,_DstSize);
    }
    *(void **)(param_1 + 0x38) = (void *)(_DstSize + (longlong)_Dst);
  }
LAB_140085382:
  *(ulonglong *)(param_1 + 0x10) = param_2;
  if ((param_2 & 0x1f) != 0) {
    if ((ulonglong)(*(longlong *)(param_1 + 0x38) - *(longlong *)(param_1 + 0x30) >> 2) <= uVar7 - 1
       ) {
      _invalid_parameter_noinfo();
    }
    puVar2 = (uint *)(*(longlong *)(param_1 + 0x30) + (uVar7 - 1) * 4);
    *puVar2 = *puVar2 & (1 << ((byte)param_2 & 0x1f)) - 1U;
  }
  return;
}


// ==== FUN_1400853d0 @ 1400853d0  undefined FUN_1400853d0(longlong param_1)

void FUN_1400853d0(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  longlong *plVar4;
  longlong *plVar5;
  
  plVar3 = *(longlong **)(param_1 + 0x28);
  plVar5 = (longlong *)*plVar3;
  *plVar3 = (longlong)plVar3;
  *(longlong *)(*(longlong *)(param_1 + 0x28) + 8) = *(longlong *)(param_1 + 0x28);
  *(undefined8 *)(param_1 + 0x30) = 0;
  if (plVar5 != *(longlong **)(param_1 + 0x28)) {
    do {
      plVar3 = (longlong *)*plVar5;
      plVar4 = (longlong *)plVar5[3];
      if (plVar4 != (longlong *)0x0) {
        LOCK();
        plVar1 = plVar4 + 2;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)*plVar1 == 0) {
          (**(code **)*plVar4)(plVar4);
          LOCK();
          piVar2 = (int *)((longlong)plVar4 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*plVar4 + 8))(plVar4);
          }
        }
      }
      operator_delete(plVar5);
      plVar5 = plVar3;
    } while (plVar3 != (longlong *)*(longlong *)(param_1 + 0x28));
  }
  return;
}


// ==== FUN_140085480 @ 140085480  undefined8 * FUN_140085480(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 * param_4)

undefined8 *
FUN_140085480(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 *param_4)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar2 = (undefined8 *)operator_new(0x20);
  if (puVar2 != (undefined8 *)0x0) {
    *puVar2 = param_2;
  }
  if (puVar2 + 1 != (undefined8 *)0x0) {
    puVar2[1] = param_3;
  }
  puVar1 = puVar2 + 2;
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = 0;
    puVar2[3] = 0;
    FUN_1400819a0(puVar1,*param_4,param_4[1]);
  }
  return puVar2;
}


// ==== FUN_140085520 @ 140085520  longlong FUN_140085520(longlong * param_1)

longlong FUN_140085520(longlong *param_1)

{
  longlong lVar1;
  ulonglong uVar2;
  longlong lVar3;
  
  lVar1 = param_1[2];
  if ((longlong *)*param_1 == (longlong *)0x0) {
    lVar3 = 0;
  }
  else {
    lVar3 = *(longlong *)*param_1;
  }
  uVar2 = *(ulonglong *)(lVar3 + 0x30);
  if (*(ulonglong *)(lVar3 + 0x38) < uVar2) {
    _invalid_parameter_noinfo();
  }
  return ((longlong)(param_1[1] - uVar2) >> 2) * 0x20 + lVar1;
}


// ==== FUN_140085580 @ 140085580  longlong * FUN_140085580(longlong * param_1, longlong param_2)

longlong * FUN_140085580(longlong *param_1,longlong param_2)

{
  ulonglong uVar1;
  longlong lVar2;
  longlong lVar3;
  
  if (param_2 != 0) {
    if ((*param_1 == 0) || (param_1[1] == 0)) {
      _invalid_parameter_noinfo();
    }
    if (param_2 < 0) {
      uVar1 = FUN_140085520(param_1);
      if (uVar1 < (ulonglong)-param_2) {
        _invalid_parameter_noinfo();
      }
    }
    else {
      if ((longlong *)*param_1 == (longlong *)0x0) {
        lVar3 = 0;
      }
      else {
        lVar3 = *(longlong *)*param_1;
      }
      lVar2 = FUN_140085520(param_1);
      if (*(ulonglong *)(lVar3 + 0x10) < (ulonglong)(lVar2 + param_2)) {
        _invalid_parameter_noinfo();
      }
    }
    if ((param_2 < 0) && ((ulonglong)param_1[2] < (ulonglong)-param_2)) {
      lVar3 = param_1[2] + param_2;
      param_1[1] = param_1[1] + (-lVar3 - 1U >> 5) * -4 + -4;
      param_1[2] = (ulonglong)((uint)lVar3 & 0x1f);
      return param_1;
    }
    param_1[1] = param_1[1] + ((ulonglong)(param_1[2] + param_2) >> 5) * 4;
    param_1[2] = (ulonglong)((uint)(param_1[2] + param_2) & 0x1f);
  }
  return param_1;
}


// ==== FUN_1400856b0 @ 1400856b0  undefined8 * FUN_1400856b0(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_1400856b0(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_1400846d0(param_1,param_2);
  return param_1;
}


// ==== FUN_1400856d0 @ 1400856d0  undefined FUN_1400856d0(longlong param_1, longlong param_2)

void FUN_1400856d0(longlong param_1,longlong param_2)

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


// ==== FUN_140085740 @ 140085740  undefined FUN_140085740(undefined8 * param_1, longlong param_2, undefined8 * param_3)

void FUN_140085740(undefined8 *param_1,longlong param_2,undefined8 *param_3)

{
  for (; param_2 != 0; param_2 = param_2 + -1) {
    if (param_1 != (undefined8 *)0x0) {
      *param_1 = 0;
      param_1[1] = 0;
      FUN_140081a30(param_1,*param_3,param_3[1]);
    }
    param_1 = param_1 + 2;
  }
  return;
}


// ==== FUN_1400857c0 @ 1400857c0  undefined FUN_1400857c0(longlong param_1, longlong param_2, undefined8 * param_3)

void FUN_1400857c0(longlong param_1,longlong param_2,undefined8 *param_3)

{
  FUN_1400847e0(*(undefined8 **)(param_1 + 8),*(undefined8 **)(param_2 + 8),param_3);
  return;
}


// ==== FUN_1400857f0 @ 1400857f0  undefined FUN_1400857f0(longlong * param_1)

void FUN_1400857f0(longlong *param_1)

{
  longlong lVar1;
  ulonglong uVar2;
  longlong lVar3;
  
  if ((*param_1 == 0) || (param_1[1] == 0)) {
    _invalid_parameter_noinfo();
  }
  lVar1 = param_1[2];
  if ((longlong *)*param_1 == (longlong *)0x0) {
    lVar3 = 0;
  }
  else {
    lVar3 = *(longlong *)*param_1;
  }
  uVar2 = *(ulonglong *)(lVar3 + 0x30);
  if (*(ulonglong *)(lVar3 + 0x38) < uVar2) {
    _invalid_parameter_noinfo();
  }
  if ((longlong *)*param_1 == (longlong *)0x0) {
    lVar3 = 0;
  }
  else {
    lVar3 = *(longlong *)*param_1;
  }
  if (*(ulonglong *)(lVar3 + 0x10) <
      (ulonglong)(lVar1 + 1 + ((longlong)(param_1[1] - uVar2) >> 2) * 0x20)) {
    _invalid_parameter_noinfo();
  }
  if ((ulonglong)param_1[2] < 0x1f) {
    param_1[2] = param_1[2] + 1;
    return;
  }
  param_1[1] = param_1[1] + 4;
  param_1[2] = 0;
  return;
}


// ==== FUN_1400858b0 @ 1400858b0  undefined8 * FUN_1400858b0(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

/* WARNING: Removing unreachable block (ram,0x000140085983) */
/* WARNING: Removing unreachable block (ram,0x00014008598c) */
/* WARNING: Removing unreachable block (ram,0x0001400859a0) */
/* WARNING: Removing unreachable block (ram,0x0001400859b5) */

undefined8 * FUN_1400858b0(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  
  for (; param_1 != param_2; param_1 = param_1 + 2) {
    if (param_3 != (undefined8 *)0x0) {
      *param_3 = 0;
      param_3[1] = 0;
      FUN_140081a30(param_3,0,0);
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


// ==== FUN_140085a30 @ 140085a30  longlong * FUN_140085a30(longlong * param_1)

longlong * FUN_140085a30(longlong *param_1)

{
  FUN_1400848c0(param_1);
  return param_1;
}


// ==== FUN_140085a50 @ 140085a50  undefined FUN_140085a50(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

void FUN_140085a50(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  FUN_140084970(param_1,param_2,param_3);
  return;
}


// ==== FUN_140085a70 @ 140085a70  undefined FUN_140085a70(longlong param_1, undefined8 * param_2)

void FUN_140085a70(longlong param_1,undefined8 *param_2)

{
  longlong lVar1;
  undefined8 *puVar2;
  
  lVar1 = **(longlong **)(param_1 + 0x28);
  puVar2 = FUN_140084300(param_1,lVar1,*(undefined8 *)(lVar1 + 8),param_2);
  FUN_1400824c0(param_1,1);
  *(undefined8 **)(lVar1 + 8) = puVar2;
  *(undefined8 **)puVar2[1] = puVar2;
  return;
}


// ==== FUN_140085ad0 @ 140085ad0  undefined FUN_140085ad0(longlong param_1, undefined8 * param_2)

void FUN_140085ad0(longlong param_1,undefined8 *param_2)

{
  longlong lVar1;
  undefined8 *puVar2;
  
  lVar1 = *(longlong *)(param_1 + 0x28);
  puVar2 = FUN_140084300(param_1,lVar1,*(undefined8 *)(lVar1 + 8),param_2);
  FUN_1400824c0(param_1,1);
  *(undefined8 **)(lVar1 + 8) = puVar2;
  *(undefined8 **)puVar2[1] = puVar2;
  return;
}


// ==== FUN_140085b20 @ 140085b20  undefined8 * FUN_140085b20(undefined8 * param_1, undefined8 * param_2, longlong * param_3)

undefined8 * FUN_140085b20(undefined8 *param_1,undefined8 *param_2,longlong *param_3)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  longlong *plVar4;
  undefined8 *puVar5;
  
  plVar3 = (longlong *)param_3[1];
  puVar5 = (undefined8 *)*param_3;
  if (puVar5 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar5 = (undefined8 *)*param_3;
    if (puVar5 == (undefined8 *)0x0) goto LAB_140085b77;
  }
  puVar5 = (undefined8 *)*puVar5;
LAB_140085b77:
  if (param_3[1] == puVar5[5]) {
    _invalid_parameter_noinfo();
  }
  param_3[1] = *(longlong *)param_3[1];
  if (plVar3 != (longlong *)param_1[5]) {
    *(longlong *)plVar3[1] = *plVar3;
    *(longlong *)(*plVar3 + 8) = plVar3[1];
    plVar4 = (longlong *)plVar3[3];
    if (plVar4 != (longlong *)0x0) {
      LOCK();
      plVar1 = plVar4 + 2;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)*plVar1 == 0) {
        (**(code **)*plVar4)(plVar4);
        LOCK();
        piVar2 = (int *)((longlong)plVar4 + 0x14);
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (*piVar2 == 0) {
          (**(code **)(*plVar4 + 8))(plVar4);
        }
      }
    }
    operator_delete(plVar3);
    param_1[6] = param_1[6] + -1;
  }
  param_2[1] = param_3[1];
  *param_2 = *param_1;
  return param_2;
}


// ==== FUN_140085c30 @ 140085c30  undefined FUN_140085c30(longlong param_1)

void FUN_140085c30(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  longlong *plVar4;
  longlong *plVar5;
  
  plVar3 = *(longlong **)(param_1 + 0x28);
  plVar5 = (longlong *)*plVar3;
  *plVar3 = (longlong)plVar3;
  *(longlong *)(*(longlong *)(param_1 + 0x28) + 8) = *(longlong *)(param_1 + 0x28);
  *(undefined8 *)(param_1 + 0x30) = 0;
  if (plVar5 != *(longlong **)(param_1 + 0x28)) {
    do {
      plVar3 = (longlong *)*plVar5;
      plVar4 = (longlong *)plVar5[3];
      if (plVar4 != (longlong *)0x0) {
        LOCK();
        plVar1 = plVar4 + 2;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)*plVar1 == 0) {
          (**(code **)*plVar4)(plVar4);
          LOCK();
          piVar2 = (int *)((longlong)plVar4 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*plVar4 + 8))(plVar4);
          }
        }
      }
      operator_delete(plVar5);
      plVar5 = plVar3;
    } while (plVar3 != (longlong *)*(longlong *)(param_1 + 0x28));
  }
  return;
}


// ==== FUN_140085ce0 @ 140085ce0  undefined8 * FUN_140085ce0(undefined8 * param_1, undefined8 * param_2, longlong * param_3)

undefined8 * FUN_140085ce0(undefined8 *param_1,undefined8 *param_2,longlong *param_3)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  longlong *plVar4;
  undefined8 *puVar5;
  
  plVar3 = (longlong *)param_3[1];
  puVar5 = (undefined8 *)*param_3;
  if (puVar5 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar5 = (undefined8 *)*param_3;
    if (puVar5 == (undefined8 *)0x0) goto LAB_140085d37;
  }
  puVar5 = (undefined8 *)*puVar5;
LAB_140085d37:
  if (param_3[1] == puVar5[5]) {
    _invalid_parameter_noinfo();
  }
  param_3[1] = *(longlong *)param_3[1];
  if (plVar3 != (longlong *)param_1[5]) {
    *(longlong *)plVar3[1] = *plVar3;
    *(longlong *)(*plVar3 + 8) = plVar3[1];
    plVar4 = (longlong *)plVar3[3];
    if (plVar4 != (longlong *)0x0) {
      LOCK();
      plVar1 = plVar4 + 2;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)*plVar1 == 0) {
        (**(code **)*plVar4)(plVar4);
        LOCK();
        piVar2 = (int *)((longlong)plVar4 + 0x14);
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (*piVar2 == 0) {
          (**(code **)(*plVar4 + 8))(plVar4);
        }
      }
    }
    operator_delete(plVar3);
    param_1[6] = param_1[6] + -1;
  }
  param_2[1] = param_3[1];
  *param_2 = *param_1;
  return param_2;
}


// ==== FUN_140085df0 @ 140085df0  undefined FUN_140085df0(longlong param_1)

void FUN_140085df0(longlong param_1)

{
  FUN_140085c30(param_1);
  operator_delete(*(void **)(param_1 + 0x28));
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_140085e20 @ 140085e20  undefined FUN_140085e20(longlong param_1, longlong param_2, undefined8 * param_3)

void FUN_140085e20(longlong param_1,longlong param_2,undefined8 *param_3)

{
  longlong lVar1;
  undefined8 *puVar2;
  
  lVar1 = *(longlong *)(param_2 + 8);
  puVar2 = FUN_140085480(param_1,lVar1,*(undefined8 *)(lVar1 + 8),param_3);
  FUN_140082600(param_1,1);
  *(undefined8 **)(lVar1 + 8) = puVar2;
  *(undefined8 **)puVar2[1] = puVar2;
  return;
}


// ==== FUN_140085e70 @ 140085e70  undefined FUN_140085e70(longlong param_1)

void FUN_140085e70(longlong param_1)

{
  FUN_1400853d0(param_1);
  operator_delete(*(void **)(param_1 + 0x28));
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_140085ea0 @ 140085ea0  longlong FUN_140085ea0(longlong * param_1)

longlong FUN_140085ea0(longlong *param_1)

{
  longlong lVar1;
  ulonglong uVar2;
  longlong lVar3;
  longlong lVar4;
  
  if ((*param_1 == 0) || (param_1[1] == 0)) {
    _invalid_parameter_noinfo();
  }
  lVar1 = param_1[2];
  lVar4 = 0;
  lVar3 = lVar4;
  if ((longlong *)*param_1 != (longlong *)0x0) {
    lVar3 = *(longlong *)*param_1;
  }
  uVar2 = *(ulonglong *)(lVar3 + 0x30);
  if (*(ulonglong *)(lVar3 + 0x38) < uVar2) {
    _invalid_parameter_noinfo();
  }
  if ((longlong *)*param_1 != (longlong *)0x0) {
    lVar4 = *(longlong *)*param_1;
  }
  if (*(ulonglong *)(lVar4 + 0x10) <=
      (ulonglong)(lVar1 + ((longlong)(param_1[1] - uVar2) >> 2) * 0x20)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_140085f40 @ 140085f40  longlong * FUN_140085f40(longlong * param_1, longlong param_2)

longlong * FUN_140085f40(longlong *param_1,longlong param_2)

{
  FUN_140085580(param_1,param_2);
  return param_1;
}


// ==== FUN_140085f60 @ 140085f60  undefined FUN_140085f60(longlong param_1, longlong param_2, ulonglong param_3, undefined4 * param_4)

void FUN_140085f60(longlong param_1,longlong param_2,ulonglong param_3,undefined4 *param_4)

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
      FUN_1400803c0();
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
      pvVar3 = (void *)FUN_140081750(param_1 + 0x10,uVar9);
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
      FUN_140084660(param_1,*(void **)(param_2 + 8),lVar7,
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
      pvVar3 = FUN_140084660(param_1,pvVar10,lVar7,(void *)lVar7);
      *(void **)(param_1 + 0x20) = pvVar3;
      FUN_140082c30(*(void **)(param_2 + 8),(longlong)pvVar10,lVar7);
      puVar12 = *(undefined4 **)(param_2 + 8);
      puVar6 = puVar12 + param_3;
      for (; puVar12 != puVar6; puVar12 = puVar12 + 1) {
        *puVar12 = uVar1;
      }
    }
  }
  return;
}


// ==== FUN_140086200 @ 140086200  undefined FUN_140086200(longlong * param_1, longlong * param_2)

void FUN_140086200(longlong *param_1,longlong *param_2)

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


// ==== FUN_140086270 @ 140086270  undefined FUN_140086270(undefined8 * param_1, longlong param_2, undefined8 * param_3)

void FUN_140086270(undefined8 *param_1,longlong param_2,undefined8 *param_3)

{
  FUN_140085740(param_1,param_2,param_3);
  return;
}


// ==== FUN_140086290 @ 140086290  undefined FUN_140086290(undefined8 param_1, longlong param_2, longlong param_3, undefined8 * param_4)

void FUN_140086290(undefined8 param_1,longlong param_2,longlong param_3,undefined8 *param_4)

{
  FUN_1400847e0(*(undefined8 **)(param_2 + 8),*(undefined8 **)(param_3 + 8),param_4);
  return;
}


// ==== FUN_1400862f0 @ 1400862f0  undefined FUN_1400862f0(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

void FUN_1400862f0(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  FUN_1400858b0(param_1,param_2,param_3);
  return;
}


// ==== FUN_140086310 @ 140086310  longlong FUN_140086310(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

longlong FUN_140086310(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

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


// ==== FUN_140086390 @ 140086390  longlong * FUN_140086390(longlong * param_1, longlong param_2)

longlong * FUN_140086390(longlong *param_1,longlong param_2)

{
  FUN_140085580(param_1,-param_2);
  return param_1;
}


// ==== FUN_1400863b0 @ 1400863b0  longlong * FUN_1400863b0(longlong * param_1)

longlong * FUN_1400863b0(longlong *param_1)

{
  FUN_1400857f0(param_1);
  return param_1;
}


// ==== FUN_1400863d0 @ 1400863d0  undefined FUN_1400863d0(undefined8 param_1, undefined8 * param_2, undefined8 * param_3, undefined8 * param_4)

void FUN_1400863d0(undefined8 param_1,undefined8 *param_2,undefined8 *param_3,undefined8 *param_4)

{
  FUN_140084970(param_2,param_3,param_4);
  return;
}


// ==== FUN_140086410 @ 140086410  longlong * FUN_140086410(longlong * param_1)

longlong * FUN_140086410(longlong *param_1)

{
  FUN_1400848c0(param_1);
  return param_1;
}


// ==== FUN_140086430 @ 140086430  undefined FUN_140086430(longlong param_1, longlong * param_2)

void FUN_140086430(longlong param_1,longlong *param_2)

{
  int *piVar1;
  longlong lVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong lVar7;
  uint uVar8;
  longlong local_a8;
  longlong *local_a0;
  undefined8 local_98;
  undefined **local_90 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_78 [40];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_50 [40];
  
  local_98 = 0xfffffffffffffffe;
  plVar5 = (longlong *)param_2[1];
  lVar7 = *param_2;
  if (plVar5 != (longlong *)0x0) {
    LOCK();
    *(int *)(plVar5 + 2) = (int)plVar5[2] + 1;
    UNLOCK();
  }
  uVar8 = 1;
  do {
    plVar6 = plVar5;
    local_a8 = lVar7;
    local_a0 = plVar5;
    if (*(longlong *)(lVar7 + 0x18) == 0) goto LAB_1400865d9;
    lVar2 = **(longlong **)(param_1 + 0x90);
    puVar4 = FUN_140084300(param_1 + 0x68,lVar2,*(undefined8 *)(lVar2 + 8),&local_a8);
    plVar3 = local_a0;
    if (*(longlong *)(param_1 + 0x98) == 0xfffffffffffffff) {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (local_50,"list<T> too long");
      std::exception::exception((exception *)local_90);
      local_90[0] = std::logic_error::vftable;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (local_78,local_50);
      local_90[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
      _CxxThrowException(local_90,(ThrowInfo *)&DAT_1400fee30);
    }
    *(longlong *)(param_1 + 0x98) = *(longlong *)(param_1 + 0x98) + 1;
    *(undefined8 **)(lVar2 + 8) = puVar4;
    *(undefined8 **)puVar4[1] = puVar4;
    plVar6 = *(longlong **)(lVar7 + 0x20);
    lVar7 = *(longlong *)(lVar7 + 0x18);
    if (plVar6 != (longlong *)0x0) {
      LOCK();
      *(int *)(plVar6 + 2) = (int)plVar6[2] + 1;
      UNLOCK();
      plVar5 = local_a0;
    }
    if (plVar5 != (longlong *)0x0) {
      LOCK();
      plVar5 = plVar5 + 2;
      *(int *)plVar5 = (int)*plVar5 + -1;
      UNLOCK();
      if ((int)*plVar5 == 0) {
        (**(code **)*local_a0)(local_a0);
        LOCK();
        piVar1 = (int *)((longlong)plVar3 + 0x14);
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (*piVar1 == 0) {
          (**(code **)(*local_a0 + 8))();
        }
      }
    }
    uVar8 = uVar8 + 1;
    plVar5 = plVar6;
  } while (uVar8 < 0x10000);
  local_a8 = lVar7;
  local_a0 = plVar6;
  log_InlineLogERROR(&DAT_1400be0b0,"DEAD_LOOP_BREAK","uLoopCount",
                     "f:\\version\\cqserver-78.0.11-1204\\mapdata\\source\\mapdata.cpp",0x275);
LAB_1400865d9:
  plVar5 = local_a0;
  if (plVar6 != (longlong *)0x0) {
    LOCK();
    plVar6 = plVar6 + 2;
    *(int *)plVar6 = (int)*plVar6 + -1;
    UNLOCK();
    if ((int)*plVar6 == 0) {
      (**(code **)*local_a0)(local_a0);
      LOCK();
      piVar1 = (int *)((longlong)plVar5 + 0x14);
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (*piVar1 == 0) {
        (**(code **)(*local_a0 + 8))();
      }
    }
  }
  plVar5 = (longlong *)param_2[1];
  if (plVar5 != (longlong *)0x0) {
    LOCK();
    plVar6 = plVar5 + 2;
    *(int *)plVar6 = (int)*plVar6 + -1;
    UNLOCK();
    if ((int)*plVar6 == 0) {
      (**(code **)*plVar5)(plVar5);
      LOCK();
      piVar1 = (int *)((longlong)plVar5 + 0x14);
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (*piVar1 == 0) {
        (**(code **)(*plVar5 + 8))(plVar5);
      }
    }
  }
  return;
}


// ==== FUN_140086650 @ 140086650  undefined FUN_140086650(undefined8 * param_1)

void FUN_140086650(undefined8 *param_1)

{
  FUN_140085c30((longlong)param_1);
  operator_delete((void *)param_1[5]);
  param_1[5] = 0;
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140086690 @ 140086690  undefined FUN_140086690(undefined8 * param_1)

void FUN_140086690(undefined8 *param_1)

{
  FUN_1400853d0((longlong)param_1);
  operator_delete((void *)param_1[5]);
  param_1[5] = 0;
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_1400866d0 @ 1400866d0  undefined FUN_1400866d0(longlong param_1, undefined8 * param_2)

void FUN_1400866d0(longlong param_1,undefined8 *param_2)

{
  longlong lVar1;
  undefined8 *puVar2;
  
  lVar1 = *(longlong *)(param_1 + 0x28);
  puVar2 = FUN_140085480(param_1,lVar1,*(undefined8 *)(lVar1 + 8),param_2);
  FUN_140082600(param_1,1);
  *(undefined8 **)(lVar1 + 8) = puVar2;
  *(undefined8 **)puVar2[1] = puVar2;
  return;
}


// ==== FUN_140086720 @ 140086720  longlong * FUN_140086720(longlong * param_1, char param_2)

longlong * FUN_140086720(longlong *param_1,char param_2)

{
  uint *puVar1;
  
  if (param_2 != '\0') {
    puVar1 = (uint *)FUN_140085ea0(param_1);
    *puVar1 = *puVar1 | 1 << ((byte)param_1[2] & 0x1f);
    return param_1;
  }
  puVar1 = (uint *)FUN_140085ea0(param_1);
  *puVar1 = *puVar1 & ~(1 << ((byte)param_1[2] & 0x1f));
  return param_1;
}


// ==== FUN_140086770 @ 140086770  bool FUN_140086770(longlong * param_1)

bool FUN_140086770(longlong *param_1)

{
  longlong lVar1;
  uint *puVar2;
  
  lVar1 = param_1[2];
  puVar2 = (uint *)FUN_140085ea0(param_1);
  return (*puVar2 & 1 << ((byte)lVar1 & 0x1f)) != 0;
}


// ==== FUN_1400867a0 @ 1400867a0  undefined FUN_1400867a0(undefined8 param_1, longlong * param_2, longlong * param_3)

void FUN_1400867a0(undefined8 param_1,longlong *param_2,longlong *param_3)

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


// ==== FUN_140086810 @ 140086810  undefined8 * FUN_140086810(undefined8 param_1, undefined8 * param_2, longlong param_3, undefined8 * param_4)

undefined8 *
FUN_140086810(undefined8 param_1,undefined8 *param_2,longlong param_3,undefined8 *param_4)

{
  FUN_140085740(param_2,param_3,param_4);
  return param_2 + param_3 * 2;
}


// ==== FUN_140086860 @ 140086860  longlong * FUN_140086860(longlong * param_1, longlong * param_2)

longlong * FUN_140086860(longlong *param_1,longlong *param_2)

{
  ulonglong uVar1;
  
  uVar1 = param_1[6];
  if ((ulonglong)param_1[7] < uVar1) {
    _invalid_parameter_noinfo();
  }
  param_2[1] = uVar1;
  *param_2 = 0;
  param_2[2] = 0;
  if (param_1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_2 = *param_1;
  if (param_1[2] != 0) {
    FUN_140085580(param_2,param_1[2]);
  }
  return param_2;
}


// ==== FUN_1400868d0 @ 1400868d0  longlong * FUN_1400868d0(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_1400868d0(longlong *param_1,longlong *param_2,longlong param_3)

{
  longlong local_28;
  longlong local_20;
  longlong local_18;
  
  local_28 = *param_1;
  local_20 = param_1[1];
  local_18 = param_1[2];
  FUN_140085580(&local_28,param_3);
  *param_2 = local_28;
  param_2[1] = local_20;
  param_2[2] = local_18;
  return param_2;
}


// ==== FUN_140086930 @ 140086930  undefined FUN_140086930(longlong param_1)

void FUN_140086930(longlong param_1)

{
  if (*(longlong **)(param_1 + 0x18) != (longlong *)0x0) {
    FUN_1400867a0(param_1,*(longlong **)(param_1 + 0x18),*(longlong **)(param_1 + 0x20));
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_140086970 @ 140086970  longlong * FUN_140086970(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_140086970(longlong *param_1,longlong *param_2,longlong param_3)

{
  ulonglong uVar1;
  
  uVar1 = param_1[6];
  if ((ulonglong)param_1[7] < uVar1) {
    _invalid_parameter_noinfo();
  }
  param_2[1] = uVar1;
  *param_2 = 0;
  param_2[2] = 0;
  if (param_1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_2 = *param_1;
  if (param_1[2] != 0) {
    uVar1 = param_1[6];
    if ((ulonglong)param_1[7] < uVar1) {
      _invalid_parameter_noinfo();
    }
    FUN_140085580(param_2,((longlong)(*(longlong *)(param_3 + 8) - uVar1) >> 2) * 0x20 +
                          *(longlong *)(param_3 + 0x10));
  }
  return param_2;
}


// ==== FUN_140086a10 @ 140086a10  undefined8 * FUN_140086a10(undefined8 * param_1, longlong param_2)

undefined8 * FUN_140086a10(undefined8 *param_1,longlong param_2)

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
  uVar5 = *(longlong *)(param_2 + 0x20) - *(longlong *)(param_2 + 0x18) >> 4;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  if (uVar5 != 0) {
    if (0xfffffffffffffff < uVar5) {
      FUN_140080260();
      pcVar2 = (code *)swi(3);
      puVar3 = (undefined8 *)(*pcVar2)();
      return puVar3;
    }
    lVar4 = FUN_140081680(param_1 + 2,uVar5);
    param_1[3] = lVar4;
    param_1[4] = lVar4;
    param_1[5] = uVar5 * 0x10 + lVar4;
    puVar3 = *(undefined8 **)(param_2 + 0x20);
    if (puVar3 < *(undefined8 **)(param_2 + 0x18)) {
      _invalid_parameter_noinfo();
    }
    puVar1 = *(undefined8 **)(param_2 + 0x18);
    if (*(undefined8 **)(param_2 + 0x20) < puVar1) {
      _invalid_parameter_noinfo();
    }
    puVar3 = FUN_1400847e0(puVar1,puVar3,(undefined8 *)param_1[3]);
    param_1[4] = puVar3;
  }
  return param_1;
}


// ==== FUN_140086b70 @ 140086b70  undefined FUN_140086b70(longlong * param_1, ulonglong param_2, undefined4 param_3)

void FUN_140086b70(longlong *param_1,ulonglong param_2,undefined4 param_3)

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
    FUN_140085f60((longlong)param_1,(longlong)&local_28,param_2 - (param_1[4] - param_1[3] >> 2),
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
    if (*(void **)(lVar4 + 0x18) <= pvVar1) goto LAB_140086c57;
  }
  _invalid_parameter_noinfo();
LAB_140086c57:
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


// ==== FUN_140086ce0 @ 140086ce0  undefined FUN_140086ce0(undefined8 param_1, undefined8 * param_2, undefined8 * param_3, undefined8 * param_4)

void FUN_140086ce0(undefined8 param_1,undefined8 *param_2,undefined8 *param_3,undefined8 *param_4)

{
  FUN_1400858b0(param_2,param_3,param_4);
  return;
}


// ==== FUN_140086d20 @ 140086d20  longlong FUN_140086d20(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

longlong FUN_140086d20(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

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


// ==== FUN_140086da0 @ 140086da0  longlong * FUN_140086da0(longlong * param_1)

longlong * FUN_140086da0(longlong *param_1)

{
  FUN_1400857f0(param_1);
  return param_1;
}


// ==== FUN_140086dc0 @ 140086dc0  longlong * FUN_140086dc0(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_140086dc0(longlong *param_1,longlong *param_2,longlong param_3)

{
  longlong local_28;
  longlong local_20;
  longlong local_18;
  
  local_28 = *param_1;
  local_20 = param_1[1];
  local_18 = param_1[2];
  FUN_140085580(&local_28,-param_3);
  *param_2 = local_28;
  param_2[1] = local_20;
  param_2[2] = local_18;
  return param_2;
}


// ==== FUN_140086e20 @ 140086e20  longlong * FUN_140086e20(longlong * param_1, longlong * param_2, longlong param_3, longlong param_4)

longlong * FUN_140086e20(longlong *param_1,longlong *param_2,longlong param_3,longlong param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  longlong *plVar6;
  
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
  puVar4 = (undefined8 *)param_2[1];
  if (puVar4 != puVar3) {
    puVar5 = (undefined8 *)param_1[4];
    FUN_140082ef0(puVar3,puVar5,puVar4);
    plVar6 = (longlong *)
             (((longlong)puVar5 - (longlong)puVar3 & 0xfffffffffffffff0U) + (longlong)puVar4);
    FUN_1400867a0(param_1,plVar6,(longlong *)param_1[4]);
    param_1[4] = (longlong)plVar6;
  }
  return param_2;
}


// ==== FUN_140086f20 @ 140086f20  undefined FUN_140086f20(undefined8 * param_1, longlong param_2)

void FUN_140086f20(undefined8 *param_1,longlong param_2)

{
  if (param_1 != (undefined8 *)0x0) {
    FUN_140086a10(param_1,param_2);
  }
  return;
}


// ==== FUN_140086f50 @ 140086f50  longlong * FUN_140086f50(longlong * param_1, longlong * param_2)

longlong * FUN_140086f50(longlong *param_1,longlong *param_2)

{
  longlong lVar1;
  uint *puVar2;
  
  lVar1 = param_2[2];
  puVar2 = (uint *)FUN_140085ea0(param_2);
  if ((*puVar2 & 1 << ((byte)lVar1 & 0x1f)) != 0) {
    puVar2 = (uint *)FUN_140085ea0(param_1);
    *puVar2 = *puVar2 | 1 << ((byte)param_1[2] & 0x1f);
    return param_1;
  }
  puVar2 = (uint *)FUN_140085ea0(param_1);
  *puVar2 = *puVar2 & ~(1 << ((byte)param_1[2] & 0x1f));
  return param_1;
}


// ==== FUN_140086fc0 @ 140086fc0  undefined FUN_140086fc0(longlong param_1)

void FUN_140086fc0(longlong param_1)

{
  longlong *plVar1;
  
  plVar1 = *(longlong **)(param_1 + 0x20);
  if (((longlong)plVar1 - *(longlong *)(param_1 + 0x18) & 0xfffffffffffffff0U) != 0) {
    FUN_1400867a0(param_1,plVar1 + -2,plVar1);
    *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + -0x10;
  }
  return;
}


// ==== FUN_140086ff0 @ 140086ff0  undefined8 * FUN_140086ff0(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_140086ff0(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  ulonglong uVar1;
  undefined8 *puVar2;
  undefined8 *local_38;
  ulonglong local_30;
  undefined8 local_28;
  undefined8 *local_20;
  ulonglong local_18;
  undefined8 local_10;
  
  uVar1 = param_1[6];
  if ((ulonglong)param_1[7] < uVar1) {
    _invalid_parameter_noinfo();
  }
  puVar2 = (undefined8 *)0x0;
  local_10 = 0;
  local_18 = uVar1;
  if (param_1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  local_38 = (undefined8 *)*param_1;
  local_30 = local_18;
  local_28 = local_10;
  local_20 = local_38;
  FUN_140085580((longlong *)&local_38,param_3);
  if (local_38 != (undefined8 *)0x0) {
    puVar2 = (undefined8 *)*local_38;
  }
  *param_2 = 0;
  param_2[1] = local_30;
  param_2[2] = local_28;
  if (puVar2 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_2 = *puVar2;
  return param_2;
}


// ==== FUN_1400870c0 @ 1400870c0  undefined FUN_1400870c0(undefined8 * param_1)

void FUN_1400870c0(undefined8 *param_1)

{
  if ((longlong *)param_1[3] != (longlong *)0x0) {
    FUN_1400867a0(param_1,(longlong *)param_1[3],(longlong *)param_1[4]);
    operator_delete((void *)param_1[3]);
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140087110 @ 140087110  undefined FUN_140087110(longlong param_1, longlong param_2, ulonglong param_3, longlong * param_4)

void FUN_140087110(longlong param_1,longlong param_2,ulonglong param_3,longlong *param_4)

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
      FUN_140080260();
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
      puVar9 = (undefined8 *)FUN_140081680(param_1 + 0x10,uVar13);
      lVar11 = *(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18) >> 4;
      FUN_140085740(puVar9 + lVar11 * 2,param_3,param_4);
      FUN_1400858b0(*(undefined8 **)(param_1 + 0x18),*(undefined8 **)(param_2 + 8),puVar9);
      FUN_1400858b0(*(undefined8 **)(param_2 + 8),*(undefined8 **)(param_1 + 0x20),
                    puVar9 + (lVar11 + param_3) * 2);
      plVar5 = *(longlong **)(param_1 + 0x18);
      lVar11 = *(longlong *)(param_1 + 0x20);
      if (plVar5 != (longlong *)0x0) {
        FUN_1400867a0(param_1,plVar5,*(longlong **)(param_1 + 0x20));
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
      FUN_1400858b0(*(undefined8 **)(param_2 + 8),*(undefined8 **)(param_1 + 0x20),
                    *(undefined8 **)(param_2 + 8) + param_3 * 2);
      FUN_140085740(*(undefined8 **)(param_1 + 0x20),
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
      puVar10 = FUN_1400858b0(puVar9 + param_3 * -2,puVar9,puVar9);
      *(undefined8 **)(param_1 + 0x20) = puVar10;
      FUN_140086d20(*(undefined8 **)(param_2 + 8),puVar9 + param_3 * -2,puVar9);
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


// ==== FUN_140087540 @ 140087540  undefined FUN_140087540(longlong * param_1, longlong param_2, char * param_3)

void FUN_140087540(longlong *param_1,longlong param_2,char *param_3)

{
  uint *puVar1;
  longlong lVar2;
  ulonglong uVar3;
  bool bVar4;
  longlong lVar5;
  longlong *plVar6;
  
  bVar4 = FUN_140081b50((longlong)param_1,param_2);
  if (bVar4) {
    do {
      if ((undefined8 *)*param_1 == (undefined8 *)0x0) {
        plVar6 = (longlong *)0x0;
      }
      else {
        plVar6 = *(longlong **)*param_1;
      }
      puVar1 = (uint *)param_1[1];
      lVar2 = param_1[2];
      if (plVar6 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
      }
      plVar6 = (longlong *)*plVar6;
      if (*param_3 == '\0') {
        if ((plVar6 == (longlong *)0x0) || (puVar1 == (uint *)0x0)) {
          _invalid_parameter_noinfo();
        }
        if (plVar6 == (longlong *)0x0) {
          lVar5 = 0;
        }
        else {
          lVar5 = *plVar6;
        }
        uVar3 = *(ulonglong *)(lVar5 + 0x30);
        if (*(ulonglong *)(lVar5 + 0x38) < uVar3) {
          _invalid_parameter_noinfo();
        }
        if (plVar6 == (longlong *)0x0) {
          lVar5 = 0;
        }
        else {
          lVar5 = *plVar6;
        }
        if (*(ulonglong *)(lVar5 + 0x10) <=
            (ulonglong)(((longlong)((longlong)puVar1 - uVar3) >> 2) * 0x20 + lVar2)) {
          _invalid_parameter_noinfo();
        }
        *puVar1 = *puVar1 & ~(1 << ((byte)lVar2 & 0x1f));
      }
      else {
        if ((plVar6 == (longlong *)0x0) || (puVar1 == (uint *)0x0)) {
          _invalid_parameter_noinfo();
        }
        if (plVar6 == (longlong *)0x0) {
          lVar5 = 0;
        }
        else {
          lVar5 = *plVar6;
        }
        uVar3 = *(ulonglong *)(lVar5 + 0x30);
        if (*(ulonglong *)(lVar5 + 0x38) < uVar3) {
          _invalid_parameter_noinfo();
        }
        if (plVar6 == (longlong *)0x0) {
          lVar5 = 0;
        }
        else {
          lVar5 = *plVar6;
        }
        if (*(ulonglong *)(lVar5 + 0x10) <=
            (ulonglong)(((longlong)((longlong)puVar1 - uVar3) >> 2) * 0x20 + lVar2)) {
          _invalid_parameter_noinfo();
        }
        *puVar1 = *puVar1 | 1 << ((byte)lVar2 & 0x1f);
      }
      FUN_1400857f0(param_1);
      bVar4 = FUN_140081b50((longlong)param_1,param_2);
    } while (bVar4);
  }
  return;
}


// ==== FUN_1400876a0 @ 1400876a0  undefined FUN_1400876a0(undefined8 param_1, undefined8 * param_2, longlong param_3)

void FUN_1400876a0(undefined8 param_1,undefined8 *param_2,longlong param_3)

{
  if (param_2 != (undefined8 *)0x0) {
    FUN_140086a10(param_2,param_3);
  }
  return;
}


// ==== FUN_1400876e0 @ 1400876e0  undefined FUN_1400876e0(longlong * param_1)

void FUN_1400876e0(longlong *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  longlong lVar3;
  undefined8 *puVar4;
  longlong *plVar5;
  
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
    puVar4 = (undefined8 *)param_1[4];
    FUN_140082ef0(puVar1,puVar4,puVar2);
    plVar5 = (longlong *)
             (((longlong)puVar4 - (longlong)puVar1 & 0xfffffffffffffff0U) + (longlong)puVar2);
    FUN_1400867a0(param_1,plVar5,(longlong *)param_1[4]);
    param_1[4] = (longlong)plVar5;
  }
  return;
}


// ==== FUN_1400877b0 @ 1400877b0  longlong * FUN_1400877b0(longlong * param_1, longlong * param_2, longlong param_3, longlong * param_4)

longlong * FUN_1400877b0(longlong *param_1,longlong *param_2,longlong param_3,longlong *param_4)

{
  uint *puVar1;
  uint *puVar2;
  longlong lVar3;
  ulonglong uVar4;
  bool bVar5;
  longlong lVar6;
  longlong lVar7;
  longlong *plVar8;
  longlong *plVar9;
  
  bVar5 = FUN_140081b50((longlong)param_2,param_3);
  if (bVar5) {
    do {
      if ((undefined8 *)*param_2 == (undefined8 *)0x0) {
        plVar8 = (longlong *)0x0;
      }
      else {
        plVar8 = *(longlong **)*param_2;
      }
      puVar1 = (uint *)param_2[1];
      lVar7 = param_2[2];
      if (plVar8 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
      }
      plVar8 = (longlong *)*plVar8;
      if ((undefined8 *)*param_4 == (undefined8 *)0x0) {
        plVar9 = (longlong *)0x0;
      }
      else {
        plVar9 = *(longlong **)*param_4;
      }
      puVar2 = (uint *)param_4[1];
      lVar3 = param_4[2];
      if (plVar9 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
      }
      plVar9 = (longlong *)*plVar9;
      if ((plVar8 == (longlong *)0x0) || (puVar1 == (uint *)0x0)) {
        _invalid_parameter_noinfo();
      }
      if (plVar8 == (longlong *)0x0) {
        lVar6 = 0;
      }
      else {
        lVar6 = *plVar8;
      }
      uVar4 = *(ulonglong *)(lVar6 + 0x30);
      if (*(ulonglong *)(lVar6 + 0x38) < uVar4) {
        _invalid_parameter_noinfo();
      }
      if (plVar8 == (longlong *)0x0) {
        lVar6 = 0;
      }
      else {
        lVar6 = *plVar8;
      }
      if (*(ulonglong *)(lVar6 + 0x10) <=
          (ulonglong)(((longlong)((longlong)puVar1 - uVar4) >> 2) * 0x20 + lVar7)) {
        _invalid_parameter_noinfo();
      }
      if ((*puVar1 & 1 << ((byte)lVar7 & 0x1f)) == 0) {
        if ((plVar9 == (longlong *)0x0) || (puVar2 == (uint *)0x0)) {
          _invalid_parameter_noinfo();
        }
        if (plVar9 == (longlong *)0x0) {
          lVar7 = 0;
        }
        else {
          lVar7 = *plVar9;
        }
        uVar4 = *(ulonglong *)(lVar7 + 0x30);
        if (*(ulonglong *)(lVar7 + 0x38) < uVar4) {
          _invalid_parameter_noinfo();
        }
        if (plVar9 == (longlong *)0x0) {
          lVar7 = 0;
        }
        else {
          lVar7 = *plVar9;
        }
        if (*(ulonglong *)(lVar7 + 0x10) <=
            (ulonglong)(((longlong)((longlong)puVar2 - uVar4) >> 2) * 0x20 + lVar3)) {
          _invalid_parameter_noinfo();
        }
        *puVar2 = *puVar2 & ~(1 << ((byte)lVar3 & 0x1f));
      }
      else {
        if ((plVar9 == (longlong *)0x0) || (puVar2 == (uint *)0x0)) {
          _invalid_parameter_noinfo();
        }
        if (plVar9 == (longlong *)0x0) {
          lVar7 = 0;
        }
        else {
          lVar7 = *plVar9;
        }
        uVar4 = *(ulonglong *)(lVar7 + 0x30);
        if (*(ulonglong *)(lVar7 + 0x38) < uVar4) {
          _invalid_parameter_noinfo();
        }
        if (plVar9 == (longlong *)0x0) {
          lVar7 = 0;
        }
        else {
          lVar7 = *plVar9;
        }
        if (*(ulonglong *)(lVar7 + 0x10) <=
            (ulonglong)(((longlong)((longlong)puVar2 - uVar4) >> 2) * 0x20 + lVar3)) {
          _invalid_parameter_noinfo();
        }
        *puVar2 = *puVar2 | 1 << ((byte)lVar3 & 0x1f);
      }
      FUN_1400857f0(param_4);
      FUN_1400857f0(param_2);
      bVar5 = FUN_140081b50((longlong)param_2,param_3);
    } while (bVar5);
  }
  *param_1 = *param_4;
  param_1[1] = param_4[1];
  param_1[2] = param_4[2];
  return param_1;
}


// ==== FUN_1400879f0 @ 1400879f0  longlong * FUN_1400879f0(longlong * param_1, longlong param_2, longlong * param_3, longlong * param_4)

longlong * FUN_1400879f0(longlong *param_1,longlong param_2,longlong *param_3,longlong *param_4)

{
  uint *puVar1;
  uint *puVar2;
  ulonglong uVar3;
  bool bVar4;
  longlong lVar5;
  longlong lVar6;
  longlong lVar7;
  longlong *plVar8;
  longlong *plVar9;
  
  bVar4 = FUN_140081b50(param_2,(longlong)param_3);
  if (bVar4) {
    do {
      if (param_3[2] == 0) {
        if ((*param_3 == 0) || (param_3[1] == 0)) {
          _invalid_parameter_noinfo();
        }
        if ((longlong *)*param_3 == (longlong *)0x0) {
          lVar5 = 0;
        }
        else {
          lVar5 = *(longlong *)*param_3;
        }
        uVar3 = *(ulonglong *)(lVar5 + 0x30);
        if (*(ulonglong *)(lVar5 + 0x38) < uVar3) {
          _invalid_parameter_noinfo();
        }
        if ((ulonglong)param_3[1] <= uVar3) {
          _invalid_parameter_noinfo();
        }
        param_3[1] = param_3[1] + -4;
        param_3[2] = 0x1f;
      }
      else {
        param_3[2] = param_3[2] + -1;
      }
      if ((undefined8 *)*param_3 == (undefined8 *)0x0) {
        plVar8 = (longlong *)0x0;
      }
      else {
        plVar8 = *(longlong **)*param_3;
      }
      lVar5 = param_3[2];
      puVar1 = (uint *)param_3[1];
      if (plVar8 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
      }
      plVar8 = (longlong *)*plVar8;
      if (param_4[2] == 0) {
        if ((*param_4 == 0) || (param_4[1] == 0)) {
          _invalid_parameter_noinfo();
        }
        if ((longlong *)*param_4 == (longlong *)0x0) {
          lVar6 = 0;
        }
        else {
          lVar6 = *(longlong *)*param_4;
        }
        uVar3 = *(ulonglong *)(lVar6 + 0x30);
        if (*(ulonglong *)(lVar6 + 0x38) < uVar3) {
          _invalid_parameter_noinfo();
        }
        if ((ulonglong)param_4[1] <= uVar3) {
          _invalid_parameter_noinfo();
        }
        param_4[1] = param_4[1] + -4;
        param_4[2] = 0x1f;
      }
      else {
        param_4[2] = param_4[2] + -1;
      }
      if ((undefined8 *)*param_4 == (undefined8 *)0x0) {
        plVar9 = (longlong *)0x0;
      }
      else {
        plVar9 = *(longlong **)*param_4;
      }
      puVar2 = (uint *)param_4[1];
      lVar6 = param_4[2];
      if (plVar9 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
      }
      plVar9 = (longlong *)*plVar9;
      if ((plVar8 == (longlong *)0x0) || (puVar1 == (uint *)0x0)) {
        _invalid_parameter_noinfo();
      }
      if (plVar8 == (longlong *)0x0) {
        lVar7 = 0;
      }
      else {
        lVar7 = *plVar8;
      }
      uVar3 = *(ulonglong *)(lVar7 + 0x30);
      if (*(ulonglong *)(lVar7 + 0x38) < uVar3) {
        _invalid_parameter_noinfo();
      }
      if (plVar8 == (longlong *)0x0) {
        lVar7 = 0;
      }
      else {
        lVar7 = *plVar8;
      }
      if (*(ulonglong *)(lVar7 + 0x10) <=
          (ulonglong)(((longlong)((longlong)puVar1 - uVar3) >> 2) * 0x20 + lVar5)) {
        _invalid_parameter_noinfo();
      }
      if ((*puVar1 & 1 << ((byte)lVar5 & 0x1f)) == 0) {
        if ((plVar9 == (longlong *)0x0) || (puVar2 == (uint *)0x0)) {
          _invalid_parameter_noinfo();
        }
        if (plVar9 == (longlong *)0x0) {
          lVar5 = 0;
        }
        else {
          lVar5 = *plVar9;
        }
        uVar3 = *(ulonglong *)(lVar5 + 0x30);
        if (*(ulonglong *)(lVar5 + 0x38) < uVar3) {
          _invalid_parameter_noinfo();
        }
        if (plVar9 == (longlong *)0x0) {
          lVar5 = 0;
        }
        else {
          lVar5 = *plVar9;
        }
        if (*(ulonglong *)(lVar5 + 0x10) <=
            (ulonglong)(((longlong)((longlong)puVar2 - uVar3) >> 2) * 0x20 + lVar6)) {
          _invalid_parameter_noinfo();
        }
        *puVar2 = *puVar2 & ~(1 << ((byte)lVar6 & 0x1f));
      }
      else {
        if ((plVar9 == (longlong *)0x0) || (puVar2 == (uint *)0x0)) {
          _invalid_parameter_noinfo();
        }
        if (plVar9 == (longlong *)0x0) {
          lVar5 = 0;
        }
        else {
          lVar5 = *plVar9;
        }
        uVar3 = *(ulonglong *)(lVar5 + 0x30);
        if (*(ulonglong *)(lVar5 + 0x38) < uVar3) {
          _invalid_parameter_noinfo();
        }
        if (plVar9 == (longlong *)0x0) {
          lVar5 = 0;
        }
        else {
          lVar5 = *plVar9;
        }
        if (*(ulonglong *)(lVar5 + 0x10) <=
            (ulonglong)(((longlong)((longlong)puVar2 - uVar3) >> 2) * 0x20 + lVar6)) {
          _invalid_parameter_noinfo();
        }
        *puVar2 = *puVar2 | 1 << ((byte)lVar6 & 0x1f);
      }
      bVar4 = FUN_140081b50(param_2,(longlong)param_3);
    } while (bVar4);
  }
  *param_1 = *param_4;
  param_1[1] = param_4[1];
  param_1[2] = param_4[2];
  return param_1;
}


// ==== FUN_140087ce0 @ 140087ce0  undefined8 * FUN_140087ce0(undefined8 * param_1, uint param_2)

undefined8 * FUN_140087ce0(undefined8 *param_1,uint param_2)

{
  if ((longlong *)param_1[3] != (longlong *)0x0) {
    FUN_1400867a0(param_1,(longlong *)param_1[3],(longlong *)param_1[4]);
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


// ==== FUN_140087d50 @ 140087d50  undefined8 FUN_140087d50(longlong * param_1, longlong * param_2)

ulonglong FUN_140087d50(longlong *param_1,longlong *param_2)

{
  longlong *plVar1;
  int *piVar2;
  longlong lVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  undefined7 extraout_var;
  longlong *plVar7;
  uint *puVar8;
  void *pvVar9;
  ulonglong uVar10;
  undefined8 *puVar11;
  undefined8 uVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  ulonglong uVar19;
  ulonglong uVar20;
  int local_res18 [2];
  longlong local_res20;
  int *local_f8;
  longlong *local_f0;
  longlong local_e8 [4];
  int local_c8 [18];
  void *local_80;
  undefined8 local_78 [3];
  undefined8 local_60 [4];
  
  local_c8[0x10] = -2;
  local_c8[0x11] = -1;
  uVar19 = 0;
  local_c8[0] = 0;
  local_c8[1] = 0xffffffff;
  local_c8[2] = 0xffffffff;
  local_c8[3] = 0xffffffff;
  local_c8[4] = 0;
  local_c8[5] = 1;
  local_c8[6] = 1;
  local_c8[7] = 1;
  local_c8[8] = 1;
  local_c8[9] = 1;
  local_c8[10] = 0;
  local_c8[0xb] = 0xffffffff;
  local_c8[0xc] = 0xffffffff;
  local_c8[0xd] = 0xffffffff;
  local_c8[0xe] = 0;
  local_c8[0xf] = 1;
  iVar5 = (**(code **)(*param_1 + 8))(param_1,*(undefined4 *)*param_2,((undefined4 *)*param_2)[1]);
  uVar20 = uVar19;
  do {
    iVar18 = *(int *)((longlong)local_c8 + uVar20) + *(int *)*param_2;
    iVar17 = *(int *)((longlong)local_c8 + uVar20 + 0x20) + ((int *)*param_2)[1];
    cVar4 = FUN_14008d7c0((int *)param_1[0x20],iVar18,iVar17);
    puVar8 = (uint *)CONCAT71(extraout_var,cVar4);
    if (cVar4 != '\0') {
      local_res18[0] = FUN_14008d7e0((int *)param_1[0x20],iVar18,iVar17);
      local_res20 = (longlong)local_res18[0];
      plVar7 = FUN_140086ff0(param_1 + 0x22,local_78,local_res20);
      lVar3 = plVar7[2];
      puVar8 = (uint *)FUN_140085ea0(plVar7);
      if (((*puVar8 & 1 << ((byte)lVar3 & 0x1f)) == 0) &&
         (puVar8 = (uint *)(**(code **)(*param_1 + 0x18))(param_1,iVar18,iVar17), (int)puVar8 == 0))
      {
        iVar6 = (**(code **)(*param_1 + 8))(param_1,iVar18,iVar17);
        uVar13 = iVar5 - iVar6 >> 0x1f;
        uVar13 = (iVar5 - iVar6 ^ uVar13) - uVar13;
        puVar8 = (uint *)(ulonglong)uVar13;
        if ((int)uVar13 < 0x1a) {
          pvVar9 = operator_new(0x28);
          local_80 = pvVar9;
          if (pvVar9 == (void *)0x0) {
            pvVar9 = (void *)0x0;
          }
          else {
            *(undefined8 *)((longlong)pvVar9 + 0x18) = 0;
            *(undefined8 *)((longlong)pvVar9 + 0x20) = 0;
            FUN_140082280((undefined8 *)((longlong)pvVar9 + 0x18));
          }
          local_f8 = (int *)0x0;
          local_f0 = (longlong *)0x0;
          uVar10 = FUN_1400846d0(&local_f8,pvVar9);
          plVar7 = local_f0;
          piVar2 = local_f8;
          if (local_f8 == (int *)0x0) {
            if (local_f0 != (longlong *)0x0) {
              LOCK();
              plVar1 = local_f0 + 2;
              lVar3 = *plVar1;
              *(int *)plVar1 = (int)*plVar1 + -1;
              UNLOCK();
              uVar13 = (int)lVar3 - 1;
              uVar10 = (ulonglong)uVar13;
              if (uVar13 == 0) {
                (**(code **)*local_f0)(local_f0);
                LOCK();
                piVar2 = (int *)((longlong)plVar7 + 0x14);
                iVar5 = *piVar2;
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                uVar10 = (ulonglong)(iVar5 - 1U);
                if (iVar5 - 1U == 0) {
                  uVar10 = (**(code **)(*local_f0 + 8))();
                }
              }
            }
            plVar7 = (longlong *)param_2[1];
            if (plVar7 != (longlong *)0x0) {
              LOCK();
              plVar1 = plVar7 + 2;
              lVar3 = *plVar1;
              *(int *)plVar1 = (int)*plVar1 + -1;
              UNLOCK();
              uVar13 = (int)lVar3 - 1;
              uVar10 = (ulonglong)uVar13;
              if (uVar13 == 0) {
                uVar10 = (**(code **)*plVar7)(plVar7);
                LOCK();
                piVar2 = (int *)((longlong)plVar7 + 0x14);
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (*piVar2 == 0) {
                  uVar10 = (**(code **)(*plVar7 + 8))(plVar7);
                }
              }
            }
            return uVar10 & 0xffffffffffffff00;
          }
          *local_f8 = iVar18;
          local_f8[1] = iVar17;
          iVar6 = 1000;
          if ((uVar19 & 1) != 0) {
            iVar6 = 0x586;
          }
          local_f8[2] = iVar6 + *(int *)(*param_2 + 8);
          uVar13 = *(int *)((longlong)param_1 + 0x24) - iVar18;
          uVar14 = (int)uVar13 >> 0x1f;
          iVar18 = (uVar13 ^ uVar14) - uVar14;
          uVar13 = (int)param_1[5] - iVar17;
          uVar14 = (int)uVar13 >> 0x1f;
          iVar17 = (uVar13 ^ uVar14) - uVar14;
          if (iVar18 < iVar17) {
            iVar18 = iVar17;
          }
          local_f8[3] = iVar18 * 1000;
          local_f8[4] = *(int *)(*param_2 + 0x10) + 1;
          local_f8[5] = (int)uVar19;
          FUN_1400814a0((undefined8 *)(local_f8 + 6),*param_2,param_2[1]);
          plVar7 = FUN_140086ff0(param_1 + 0x22,local_60,local_res20);
          puVar8 = (uint *)FUN_140085ea0(plVar7);
          *puVar8 = *puVar8 | 1 << ((byte)plVar7[2] & 0x1f);
          FUN_14006b470(param_1 + 0x1a,local_res18);
          lVar3 = param_1[0xb];
          puVar11 = FUN_140084300(param_1 + 6,lVar3,*(undefined8 *)(lVar3 + 8),&local_f8);
          FUN_1400824c0((longlong)(param_1 + 6),1);
          plVar7 = local_f0;
          *(undefined8 **)(lVar3 + 8) = puVar11;
          *(undefined8 **)puVar11[1] = puVar11;
          iVar17 = *(int *)((longlong)param_1 + 0x24);
          iVar6 = *(int *)((longlong)param_1 + 0x14) - iVar17;
          iVar18 = (int)param_1[5];
          iVar15 = (int)param_1[3] - iVar18;
          iVar16 = iVar15 * iVar15 + iVar6 * iVar6;
          iVar6 = *piVar2;
          uVar13 = (iVar6 - iVar17) * (iVar6 - iVar17);
          puVar8 = (uint *)(ulonglong)uVar13;
          iVar15 = (piVar2[1] - iVar18) * (piVar2[1] - iVar18) + uVar13;
          if ((int)param_1[2] == 1) {
            if (iVar15 < iVar16) {
              *(int *)((longlong)param_1 + 0x14) = iVar6;
              puVar8 = (uint *)(ulonglong)(uint)piVar2[1];
              *(int *)(param_1 + 3) = piVar2[1];
            }
            if ((*piVar2 == iVar17) && (piVar2[1] == iVar18)) {
              local_e8[2] = 0;
              local_e8[3] = 0;
              FUN_1400814a0(local_e8 + 2,piVar2,(longlong)local_f0);
              FUN_140086430((longlong)param_1,local_e8 + 2);
              plVar1 = local_f0;
              if (plVar7 != (longlong *)0x0) {
                LOCK();
                plVar7 = plVar7 + 2;
                lVar3 = *plVar7;
                *(int *)plVar7 = (int)*plVar7 + -1;
                UNLOCK();
                if ((int)lVar3 == 1) {
                  (**(code **)*local_f0)(local_f0);
                  LOCK();
                  piVar2 = (int *)((longlong)plVar1 + 0x14);
                  *piVar2 = *piVar2 + -1;
                  UNLOCK();
                  if (*piVar2 == 0) {
                    (**(code **)(*local_f0 + 8))();
                  }
                }
              }
              uVar12 = FUN_140081e30((longlong)param_2);
              return CONCAT71((int7)((ulonglong)uVar12 >> 8),1);
            }
          }
          else if (iVar16 < iVar15) {
            *(int *)((longlong)param_1 + 0x14) = iVar6;
            *(int *)(param_1 + 3) = piVar2[1];
            uVar13 = *(int *)((longlong)param_1 + 0xc) * *(int *)((longlong)param_1 + 0xc);
            puVar8 = (uint *)(ulonglong)uVar13;
            if ((int)uVar13 <= iVar15) {
              local_e8[0] = 0;
              local_e8[1] = 0;
              FUN_1400814a0(local_e8,piVar2,(longlong)local_f0);
              FUN_140086430((longlong)param_1,local_e8);
              plVar1 = local_f0;
              if (plVar7 != (longlong *)0x0) {
                LOCK();
                plVar7 = plVar7 + 2;
                lVar3 = *plVar7;
                *(int *)plVar7 = (int)*plVar7 + -1;
                UNLOCK();
                if ((int)lVar3 == 1) {
                  (**(code **)*local_f0)(local_f0);
                  LOCK();
                  piVar2 = (int *)((longlong)plVar1 + 0x14);
                  *piVar2 = *piVar2 + -1;
                  UNLOCK();
                  if (*piVar2 == 0) {
                    (**(code **)(*local_f0 + 8))();
                  }
                }
              }
              uVar12 = FUN_140081e30((longlong)param_2);
              return CONCAT71((int7)((ulonglong)uVar12 >> 8),1);
            }
          }
          if (local_f0 != (longlong *)0x0) {
            LOCK();
            plVar1 = local_f0 + 2;
            lVar3 = *plVar1;
            *(int *)plVar1 = (int)*plVar1 + -1;
            UNLOCK();
            uVar13 = (int)lVar3 - 1;
            puVar8 = (uint *)(ulonglong)uVar13;
            if (uVar13 == 0) {
              (**(code **)*local_f0)(local_f0);
              LOCK();
              piVar2 = (int *)((longlong)plVar7 + 0x14);
              iVar17 = *piVar2;
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              puVar8 = (uint *)(ulonglong)(iVar17 - 1U);
              if (iVar17 - 1U == 0) {
                puVar8 = (uint *)(**(code **)(*local_f0 + 8))();
              }
            }
          }
        }
      }
    }
    uVar13 = (int)uVar19 + 1;
    uVar19 = (ulonglong)uVar13;
    uVar20 = uVar20 + 4;
    if (7 < (int)uVar13) {
      plVar7 = (longlong *)param_2[1];
      if (plVar7 != (longlong *)0x0) {
        LOCK();
        plVar1 = plVar7 + 2;
        lVar3 = *plVar1;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        uVar13 = (int)lVar3 - 1;
        puVar8 = (uint *)(ulonglong)uVar13;
        if (uVar13 == 0) {
          puVar8 = (uint *)(**(code **)*plVar7)(plVar7);
          LOCK();
          piVar2 = (int *)((longlong)plVar7 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            puVar8 = (uint *)(**(code **)(*plVar7 + 8))(plVar7);
          }
        }
      }
      return (ulonglong)puVar8 & 0xffffffffffffff00;
    }
  } while( true );
}


// ==== FUN_140088910 @ 140088910  undefined FUN_140088910(longlong * param_1, undefined8 param_2, undefined8 param_3)

/* WARNING: Removing unreachable block (ram,0x000140089134) */
/* WARNING: Removing unreachable block (ram,0x00014008913b) */
/* WARNING: Removing unreachable block (ram,0x00014008914a) */

void FUN_140088910(longlong *param_1,undefined8 param_2,undefined8 param_3)

{
  uint *puVar1;
  int *piVar2;
  uint *puVar3;
  ulonglong uVar4;
  longlong **pplVar5;
  char cVar6;
  uint uVar7;
  int iVar8;
  longlong lVar9;
  void *pvVar10;
  undefined8 *puVar11;
  longlong *plVar12;
  uint *puVar13;
  void *pvVar14;
  undefined8 uVar15;
  int iVar16;
  longlong lVar17;
  void *pvVar18;
  uint uVar19;
  longlong *plVar20;
  longlong **pplVar21;
  uint uVar22;
  void *local_res8;
  longlong *local_108;
  uint *local_100;
  undefined4 *local_f8;
  longlong *local_f0;
  longlong *local_e8;
  uint *puStack_e0;
  longlong *local_d8;
  uint *local_d0;
  undefined8 local_c8;
  longlong **pplStack_c0;
  undefined4 local_b8;
  undefined4 uStack_b4;
  longlong **pplStack_b0;
  undefined8 local_a8;
  undefined8 local_a0;
  longlong *local_98;
  uint *puStack_90;
  longlong local_88;
  longlong **local_78;
  longlong *local_70;
  uint *local_68;
  longlong local_60;
  undefined8 local_58;
  undefined8 local_50 [3];
  
  local_58 = 0xfffffffffffffffe;
  *(undefined8 *)((longlong)param_1 + 0x14) = param_2;
  *(undefined8 *)((longlong)param_1 + 0x1c) = param_2;
  *(undefined8 *)((longlong)param_1 + 0x24) = param_3;
  if (((int)param_2 == (int)param_3) &&
     ((int)((ulonglong)param_2 >> 0x20) == (int)((ulonglong)param_3 >> 0x20))) {
    return;
  }
  FUN_140085c30((longlong)(param_1 + 6));
  FUN_140085c30((longlong)(param_1 + 0xd));
  *(undefined4 *)(param_1 + 1) = 0;
  puVar13 = (uint *)param_1[0x1d];
  if ((uint *)param_1[0x1e] < puVar13) {
    _invalid_parameter_noinfo();
  }
  plVar12 = (longlong *)param_1[0x1a];
  uVar22 = 1;
  local_e8 = plVar12;
  puStack_e0 = puVar13;
  while( true ) {
    pvVar14 = (void *)0x0;
    puVar3 = (uint *)param_1[0x1e];
    if (puVar3 < (uint *)param_1[0x1d]) {
      _invalid_parameter_noinfo();
    }
    if ((plVar12 == (longlong *)0x0) || (plVar12 != (longlong *)param_1[0x1a])) {
      _invalid_parameter_noinfo();
    }
    if (puVar13 == puVar3) break;
    if (plVar12 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
    }
    else {
      pvVar14 = (void *)*plVar12;
    }
    if (*(uint **)((longlong)pvVar14 + 0x20) <= puVar13) {
      _invalid_parameter_noinfo();
    }
    uVar7 = *puVar13;
    puVar3 = (uint *)param_1[0x28];
    if ((uint *)param_1[0x29] < puVar3) {
      _invalid_parameter_noinfo();
    }
    local_88 = 0;
    puStack_90 = puVar3;
    if (param_1 + 0x22 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
    }
    local_98 = (longlong *)param_1[0x22];
    local_68 = puStack_90;
    local_60 = local_88;
    local_70 = local_98;
    FUN_140085580((longlong *)&local_70,(longlong)(int)uVar7);
    if (local_70 == (longlong *)0x0) {
      plVar20 = (longlong *)0x0;
LAB_140088ab7:
      _invalid_parameter_noinfo();
    }
    else {
      plVar20 = (longlong *)*local_70;
      if (plVar20 == (longlong *)0x0) goto LAB_140088ab7;
    }
    puVar3 = local_68;
    plVar20 = (longlong *)*plVar20;
    if ((plVar20 == (longlong *)0x0) || (local_68 == (uint *)0x0)) {
      _invalid_parameter_noinfo();
    }
    if (plVar20 == (longlong *)0x0) {
      lVar9 = 0;
    }
    else {
      lVar9 = *plVar20;
    }
    uVar4 = *(ulonglong *)(lVar9 + 0x30);
    if (*(ulonglong *)(lVar9 + 0x38) < uVar4) {
      _invalid_parameter_noinfo();
    }
    lVar9 = local_60;
    if (plVar20 == (longlong *)0x0) {
      lVar17 = 0;
    }
    else {
      lVar17 = *plVar20;
    }
    if (*(ulonglong *)(lVar17 + 0x10) <=
        (ulonglong)(((longlong)((longlong)puVar3 - uVar4) >> 2) * 0x20 + local_60)) {
      _invalid_parameter_noinfo();
    }
    *puVar3 = *puVar3 & ~(1 << ((byte)lVar9 & 0x1f));
    if (plVar12 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar9 = 0;
    }
    else {
      lVar9 = *plVar12;
    }
    if (*(uint **)(lVar9 + 0x20) <= puVar13) {
      _invalid_parameter_noinfo();
    }
    puVar13 = puVar13 + 1;
  }
  FUN_140044450(param_1 + 0x1a);
  pvVar10 = operator_new(0x28);
  pvVar18 = pvVar14;
  local_res8 = pvVar10;
  if (pvVar10 != (void *)0x0) {
    *(undefined8 *)((longlong)pvVar10 + 0x18) = 0;
    *(undefined8 *)((longlong)pvVar10 + 0x20) = 0;
    FUN_140082280((undefined8 *)((longlong)pvVar10 + 0x18));
    pvVar18 = pvVar10;
  }
  local_f8 = (undefined4 *)0x0;
  local_f0 = (longlong *)0x0;
  FUN_1400846d0(&local_f8,pvVar18);
  if (local_f8 != (undefined4 *)0x0) {
    *local_f8 = *(undefined4 *)((longlong)param_1 + 0x1c);
    local_f8[1] = (int)param_1[4];
    local_f8[2] = 0;
    uVar7 = *(int *)((longlong)param_1 + 0x24) - *(int *)((longlong)param_1 + 0x1c);
    uVar19 = (int)uVar7 >> 0x1f;
    iVar16 = (uVar7 ^ uVar19) - uVar19;
    uVar7 = (int)param_1[5] - (int)param_1[4];
    uVar19 = (int)uVar7 >> 0x1f;
    iVar8 = (uVar7 ^ uVar19) - uVar19;
    if (iVar16 < iVar8) {
      iVar16 = iVar8;
    }
    local_f8[3] = iVar16 * 1000;
    local_f8[4] = 0;
    local_a0 = 0;
    local_a8 = 0;
    FUN_1400814a0((undefined8 *)(local_f8 + 6),0,0);
    lVar9 = param_1[0xb];
    puVar11 = FUN_140084300(param_1 + 6,lVar9,*(undefined8 *)(lVar9 + 8),&local_f8);
    FUN_1400824c0((longlong)(param_1 + 6),1);
    *(undefined8 **)(lVar9 + 8) = puVar11;
    *(undefined8 **)puVar11[1] = puVar11;
  }
  cVar6 = FUN_14008d7c0((int *)param_1[0x20],*(int *)((longlong)param_1 + 0x1c),(int)param_1[4]);
  if (cVar6 != '\0') {
    uVar7 = FUN_14008d7e0((int *)param_1[0x20],*(int *)((longlong)param_1 + 0x1c),(int)param_1[4]);
    local_res8 = (void *)CONCAT44(local_res8._4_4_,uVar7);
    plVar12 = FUN_140086ff0(param_1 + 0x22,local_50,(longlong)(int)uVar7);
    puVar13 = (uint *)FUN_140085ea0(plVar12);
    *puVar13 = *puVar13 | 1 << ((byte)plVar12[2] & 0x1f);
    puVar13 = (uint *)param_1[0x1d];
    pvVar18 = pvVar14;
    if (puVar13 != (uint *)0x0) {
      pvVar18 = (void *)(param_1[0x1f] - (longlong)puVar13 >> 2);
    }
    puVar3 = (uint *)param_1[0x1e];
    if ((void *)((longlong)puVar3 - (longlong)puVar13 >> 2) < pvVar18) {
      *puVar3 = uVar7;
      param_1[0x1e] = (longlong)(puVar3 + 1);
    }
    else {
      if (puVar3 < puVar13) {
        _invalid_parameter_noinfo();
      }
      plVar12 = (longlong *)param_1[0x1a];
      uVar4 = param_1[0x1d];
      pvVar18 = pvVar14;
      local_e8 = plVar12;
      puStack_e0 = puVar3;
      if ((param_1[0x1e] - uVar4 & 0xfffffffffffffffc) != 0) {
        if ((ulonglong)param_1[0x1e] < uVar4) {
          _invalid_parameter_noinfo();
        }
        if ((plVar12 == (longlong *)0x0) || (plVar12 != (longlong *)param_1[0x1a])) {
          _invalid_parameter_noinfo();
        }
        pvVar18 = (void *)((longlong)((longlong)puVar3 - uVar4) >> 2);
      }
      local_98 = local_e8;
      puStack_90 = puStack_e0;
      FUN_140050ac0((longlong)(param_1 + 0x1a),(longlong)&local_98,1,(undefined4 *)&local_res8);
      uVar4 = param_1[0x1d];
      if ((ulonglong)param_1[0x1e] < uVar4) {
        _invalid_parameter_noinfo();
      }
      puVar11 = (undefined8 *)param_1[0x1a];
      if (puVar11 == (undefined8 *)0x0) {
        _invalid_parameter_noinfo();
        pvVar10 = pvVar14;
      }
      else {
        pvVar10 = (void *)*puVar11;
      }
      uVar4 = uVar4 + (longlong)pvVar18 * 4;
      if (uVar4 <= *(ulonglong *)((longlong)pvVar10 + 0x20)) {
        if (puVar11 != (undefined8 *)0x0) {
          pvVar14 = (void *)*puVar11;
        }
        if (*(ulonglong *)((longlong)pvVar14 + 0x18) <= uVar4) goto LAB_140088e10;
      }
      _invalid_parameter_noinfo();
    }
  }
LAB_140088e10:
  while( true ) {
    plVar12 = local_f0;
    if (0x3f < (int)param_1[1]) {
      if (local_f0 == (longlong *)0x0) {
        return;
      }
      LOCK();
      plVar20 = local_f0 + 2;
      *(int *)plVar20 = (int)*plVar20 + -1;
      UNLOCK();
      if ((int)*plVar20 != 0) {
        return;
      }
      (**(code **)*local_f0)(local_f0);
      LOCK();
      piVar2 = (int *)((longlong)plVar12 + 0x14);
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (*piVar2 != 0) {
        return;
      }
      (**(code **)(*local_f0 + 8))();
      return;
    }
    if (param_1[0xc] == 0) break;
    pplVar21 = *(longlong ***)param_1[0xb];
    plVar12 = (longlong *)param_1[6];
    local_c8 = plVar12;
    pplStack_c0 = pplVar21;
    if (plVar12 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar9 = 0;
    }
    else {
      lVar9 = *plVar12;
    }
    lVar17 = 0;
    if (pplVar21 == *(longlong ***)(lVar9 + 0x28)) {
      _invalid_parameter_noinfo();
    }
    puVar13 = (uint *)pplVar21[3];
    local_108 = pplVar21[2];
    if (puVar13 != (uint *)0x0) {
      LOCK();
      puVar13[4] = puVar13[4] + 1;
      UNLOCK();
    }
    local_b8 = (undefined4)local_c8;
    uStack_b4 = local_c8._4_4_;
    pplStack_b0 = pplStack_c0;
    if (plVar12 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
    }
    else {
      lVar17 = *plVar12;
    }
    if (pplVar21 == *(longlong ***)(lVar17 + 0x28)) {
      _invalid_parameter_noinfo();
    }
    pplVar21 = (longlong **)*pplVar21;
    plVar12 = (longlong *)CONCAT44(uStack_b4,local_b8);
    local_100 = puVar13;
    while( true ) {
      lVar9 = 0;
      pplVar5 = (longlong **)param_1[0xb];
      pplStack_b0 = pplVar21;
      if ((plVar12 == (longlong *)0x0) || (plVar12 != (longlong *)param_1[6])) {
        _invalid_parameter_noinfo();
      }
      if (pplVar21 == pplVar5) break;
      if (plVar12 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
      }
      else {
        lVar9 = *plVar12;
      }
      if (pplVar21 == *(longlong ***)(lVar9 + 0x28)) {
        _invalid_parameter_noinfo();
      }
      puVar3 = (uint *)pplVar21[3];
      plVar20 = pplVar21[2];
      if (puVar3 != (uint *)0x0) {
        LOCK();
        puVar3[4] = puVar3[4] + 1;
        UNLOCK();
        puVar13 = local_100;
      }
      local_e8 = plVar20;
      puStack_e0 = puVar3;
      if ((int)param_1[2] == 1) {
        if (*(int *)((longlong)plVar20 + 0xc) < *(int *)((longlong)local_108 + 0xc)) {
          if (puVar3 != (uint *)0x0) {
            LOCK();
            puVar3[4] = puVar3[4] + 1;
            UNLOCK();
            puVar13 = local_100;
          }
          if (puVar13 != (uint *)0x0) {
            LOCK();
            puVar13 = puVar13 + 4;
            *puVar13 = *puVar13 - 1;
            UNLOCK();
            if (*puVar13 == 0) {
              (*(code *)**(undefined8 **)local_100)(local_100);
              LOCK();
              puVar13 = local_100 + 5;
              *puVar13 = *puVar13 - 1;
              UNLOCK();
              if (*puVar13 == 0) {
                (**(code **)(*(longlong *)local_100 + 8))();
              }
            }
          }
          local_c8 = (longlong *)CONCAT44(uStack_b4,local_b8);
          pplStack_c0 = pplStack_b0;
          puVar13 = puVar3;
          local_108 = plVar20;
          local_100 = puVar3;
        }
      }
      else if (*(int *)((longlong)local_108 + 0xc) < *(int *)((longlong)plVar20 + 0xc)) {
        if (puVar3 != (uint *)0x0) {
          LOCK();
          puVar3[4] = puVar3[4] + 1;
          UNLOCK();
          puVar13 = local_100;
        }
        if (puVar13 != (uint *)0x0) {
          LOCK();
          puVar13 = puVar13 + 4;
          *puVar13 = *puVar13 - 1;
          UNLOCK();
          if (*puVar13 == 0) {
            (*(code *)**(undefined8 **)local_100)(local_100);
            LOCK();
            puVar13 = local_100 + 5;
            *puVar13 = *puVar13 - 1;
            UNLOCK();
            if (*puVar13 == 0) {
              (**(code **)(*(longlong *)local_100 + 8))();
            }
          }
        }
        local_c8 = (longlong *)CONCAT44(uStack_b4,local_b8);
        pplStack_c0 = pplStack_b0;
        puVar13 = puVar3;
        local_108 = plVar20;
        local_100 = puVar3;
      }
      if (puVar3 != (uint *)0x0) {
        LOCK();
        puVar1 = puVar3 + 4;
        *puVar1 = *puVar1 - 1;
        UNLOCK();
        puVar13 = local_100;
        if (*puVar1 == 0) {
          (*(code *)**(undefined8 **)puVar3)(puVar3);
          LOCK();
          puVar1 = puVar3 + 5;
          *puVar1 = *puVar1 - 1;
          UNLOCK();
          if (*puVar1 == 0) {
            (**(code **)(*(longlong *)puVar3 + 8))(puVar3);
          }
        }
      }
      if (plVar12 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar9 = 0;
      }
      else {
        lVar9 = *plVar12;
      }
      if (pplVar21 == *(longlong ***)(lVar9 + 0x28)) {
        _invalid_parameter_noinfo();
      }
      pplVar21 = (longlong **)*pplVar21;
    }
    if (local_c8 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
    }
    else {
      lVar9 = *local_c8;
    }
    pplVar21 = pplStack_c0;
    if (pplStack_c0 == *(longlong ***)(lVar9 + 0x28)) {
      _invalid_parameter_noinfo();
    }
    local_78 = pplVar21;
    if (pplVar21 != (longlong **)param_1[0xb]) {
      *pplVar21[1] = (longlong)*pplVar21;
      (*pplVar21)[1] = (longlong)pplVar21[1];
      plVar12 = pplVar21[3];
      if (plVar12 != (longlong *)0x0) {
        LOCK();
        plVar20 = plVar12 + 2;
        *(int *)plVar20 = (int)*plVar20 + -1;
        UNLOCK();
        puVar13 = local_100;
        if ((int)*plVar20 == 0) {
          (**(code **)*plVar12)(plVar12);
          LOCK();
          piVar2 = (int *)((longlong)plVar12 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*plVar12 + 8))(plVar12);
          }
        }
      }
      operator_delete(pplVar21);
      param_1[0xc] = param_1[0xc] + -1;
    }
    if ((int)local_108[2] < 0x40) {
      *(int *)(param_1 + 1) = (int)param_1[1] + 1;
      local_78 = &local_d8;
      if (puVar13 != (uint *)0x0) {
        LOCK();
        puVar13[4] = puVar13[4] + 1;
        UNLOCK();
        puVar13 = local_100;
      }
      local_d8 = local_108;
      local_d0 = puVar13;
      uVar15 = FUN_140087d50(param_1,(longlong *)&local_d8);
      if ((char)uVar15 != '\0') {
        if (puVar13 != (uint *)0x0) {
          LOCK();
          puVar13 = puVar13 + 4;
          *puVar13 = *puVar13 - 1;
          UNLOCK();
          if (*puVar13 == 0) {
            (*(code *)**(undefined8 **)local_100)(local_100);
            LOCK();
            puVar13 = local_100 + 5;
            *puVar13 = *puVar13 - 1;
            UNLOCK();
            if (*puVar13 == 0) {
              (**(code **)(*(longlong *)local_100 + 8))();
            }
          }
        }
        plVar12 = local_f0;
        if (local_f0 == (longlong *)0x0) {
          return;
        }
        LOCK();
        plVar20 = local_f0 + 2;
        *(int *)plVar20 = (int)*plVar20 + -1;
        UNLOCK();
        if ((int)*plVar20 != 0) {
          return;
        }
        (**(code **)*local_f0)(local_f0);
        LOCK();
        piVar2 = (int *)((longlong)plVar12 + 0x14);
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (*piVar2 != 0) {
          return;
        }
        (**(code **)(*local_f0 + 8))();
        return;
      }
    }
    if (puVar13 != (uint *)0x0) {
      LOCK();
      puVar13 = puVar13 + 4;
      *puVar13 = *puVar13 - 1;
      UNLOCK();
      if (*puVar13 == 0) {
        (*(code *)**(undefined8 **)local_100)(local_100);
        LOCK();
        puVar13 = local_100 + 5;
        *puVar13 = *puVar13 - 1;
        UNLOCK();
        if (*puVar13 == 0) {
          (**(code **)(*(longlong *)local_100 + 8))();
        }
      }
    }
    uVar22 = uVar22 + 1;
    if (0x10000 < uVar22) {
      log_InlineLogERROR(&DAT_1400be0b0);
      plVar12 = local_f0;
      if (local_f0 != (longlong *)0x0) {
        LOCK();
        plVar20 = local_f0 + 2;
        *(int *)plVar20 = (int)*plVar20 + -1;
        UNLOCK();
        if ((int)*plVar20 == 0) {
          (**(code **)*local_f0)(local_f0);
          LOCK();
          piVar2 = (int *)((longlong)plVar12 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*local_f0 + 8))();
          }
        }
      }
      return;
    }
  }
  if (local_f0 == (longlong *)0x0) {
    return;
  }
  LOCK();
  plVar20 = local_f0 + 2;
  *(int *)plVar20 = (int)*plVar20 + -1;
  UNLOCK();
  if ((int)*plVar20 != 0) {
    return;
  }
  (**(code **)*local_f0)(local_f0);
  LOCK();
  piVar2 = (int *)((longlong)plVar12 + 0x14);
  *piVar2 = *piVar2 + -1;
  UNLOCK();
  if (*piVar2 != 0) {
    return;
  }
  (**(code **)(*local_f0 + 8))();
  return;
}


// ==== FUN_140089520 @ 140089520  longlong * FUN_140089520(longlong * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_140089520(longlong *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

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
  FUN_140087110((longlong)param_1,(longlong)&local_28,1,param_4);
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
    if (*(ulonglong *)(lVar2 + 0x18) <= uVar4) goto LAB_140089617;
  }
  _invalid_parameter_noinfo();
LAB_140089617:
  *param_2 = (longlong)local_28;
  param_2[1] = uVar4;
  return param_2;
}


// ==== FUN_140089660 @ 140089660  undefined FUN_140089660(longlong * param_1, undefined8 * param_2, char * param_3)

void FUN_140089660(longlong *param_1,undefined8 *param_2,char *param_3)

{
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  longlong local_28;
  longlong local_20;
  longlong local_18;
  
  local_48 = *param_2;
  local_40 = param_2[1];
  local_38 = param_2[2];
  local_28 = *param_1;
  local_20 = param_1[1];
  local_18 = param_1[2];
  FUN_140087540(&local_28,(longlong)&local_48,param_3);
  return;
}


// ==== FUN_1400896b0 @ 1400896b0  longlong * FUN_1400896b0(longlong * param_1, longlong * param_2, undefined8 * param_3, longlong * param_4)

longlong * FUN_1400896b0(longlong *param_1,longlong *param_2,undefined8 *param_3,longlong *param_4)

{
  longlong local_88;
  longlong local_80;
  longlong local_78;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  longlong local_48;
  longlong local_40;
  longlong local_38;
  longlong local_28 [4];
  
  local_88 = *param_4;
  local_80 = param_4[1];
  local_78 = param_4[2];
  FUN_140085580(&local_88,((param_3[1] - param_2[1] >> 2) * 0x20 - param_2[2]) + param_3[2]);
  *param_1 = local_88;
  param_1[1] = local_80;
  param_1[2] = local_78;
  local_88 = *param_4;
  local_80 = param_4[1];
  local_78 = param_4[2];
  local_68 = *param_3;
  local_60 = param_3[1];
  local_58 = param_3[2];
  local_48 = *param_2;
  local_40 = param_2[1];
  local_38 = param_2[2];
  FUN_1400877b0(local_28,&local_48,(longlong)&local_68,&local_88);
  return param_1;
}


// ==== FUN_1400897e0 @ 1400897e0  longlong * FUN_1400897e0(longlong * param_1, undefined8 * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_1400897e0(longlong *param_1,undefined8 *param_2,longlong *param_3,longlong *param_4)

{
  longlong local_88;
  longlong local_80;
  longlong local_78;
  longlong local_68;
  longlong local_60;
  longlong local_58;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  longlong local_28 [4];
  
  local_88 = *param_4;
  local_80 = param_4[1];
  local_78 = param_4[2];
  FUN_140085580(&local_88,(param_2[2] + (param_3[1] - param_2[1] >> 2) * -0x20) - param_3[2]);
  *param_1 = local_88;
  param_1[1] = local_80;
  param_1[2] = local_78;
  local_88 = *param_4;
  local_80 = param_4[1];
  local_78 = param_4[2];
  local_68 = *param_3;
  local_60 = param_3[1];
  local_58 = param_3[2];
  local_48 = *param_2;
  local_40 = param_2[1];
  local_38 = param_2[2];
  FUN_1400879f0(local_28,(longlong)&local_48,&local_68,&local_88);
  return param_1;
}


// ==== FUN_140089910 @ 140089910  longlong * FUN_140089910(longlong * param_1, longlong * param_2)

longlong * FUN_140089910(longlong *param_1,longlong *param_2)

{
  ulonglong uVar1;
  longlong *plVar2;
  undefined8 *puVar3;
  undefined8 uVar4;
  longlong lVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  
  if (param_1 == param_2) {
    return param_1;
  }
  puVar3 = (undefined8 *)param_2[3];
  uVar1 = param_2[4] - (longlong)puVar3 >> 4;
  if (uVar1 == 0) {
    FUN_1400876e0(param_1);
    return param_1;
  }
  plVar2 = (longlong *)param_1[3];
  uVar7 = param_1[4] - (longlong)plVar2 >> 4;
  if (uVar1 <= uVar7) {
    plVar2 = (longlong *)FUN_140084870(puVar3,(undefined8 *)param_2[4],plVar2);
    FUN_1400867a0(param_1,plVar2,(longlong *)param_1[4]);
    param_1[4] = (param_2[4] - param_2[3] & 0xfffffffffffffff0U) + param_1[3];
    return param_1;
  }
  if (plVar2 == (longlong *)0x0) {
    uVar6 = 0;
  }
  else {
    uVar6 = param_1[5] - (longlong)plVar2 >> 4;
  }
  if (uVar1 <= uVar6) {
    FUN_140084870(puVar3,puVar3 + uVar7 * 2,plVar2);
    puVar3 = FUN_140084970(puVar3 + uVar7 * 2,(undefined8 *)param_2[4],(undefined8 *)param_1[4]);
    param_1[4] = (longlong)puVar3;
    return param_1;
  }
  if (plVar2 != (longlong *)0x0) {
    FUN_1400867a0(param_1,plVar2,(longlong *)param_1[4]);
    operator_delete((void *)param_1[3]);
  }
  uVar4 = FUN_140082400((longlong)param_1,param_2[4] - param_2[3] >> 4);
  if ((char)uVar4 != '\0') {
    lVar5 = FUN_1400863d0(param_1,(undefined8 *)param_2[3],(undefined8 *)param_2[4],
                          (undefined8 *)param_1[3]);
    param_1[4] = lVar5;
  }
  return param_1;
}


// ==== FUN_140089ae0 @ 140089ae0  undefined FUN_140089ae0(undefined8 * param_1)

void FUN_140089ae0(undefined8 *param_1)

{
  if ((longlong *)param_1[3] != (longlong *)0x0) {
    FUN_1400867a0(param_1,(longlong *)param_1[3],(longlong *)param_1[4]);
    operator_delete((void *)param_1[3]);
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140089b30 @ 140089b30  undefined FUN_140089b30(longlong * param_1, longlong * param_2)

void FUN_140089b30(longlong *param_1,longlong *param_2)

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


// ==== FUN_140089bc0 @ 140089bc0  undefined FUN_140089bc0(longlong * param_1, longlong * param_2)

void FUN_140089bc0(longlong *param_1,longlong *param_2)

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
    FUN_140085740(puVar2,1,param_2);
    param_1[4] = (longlong)(puVar2 + 2);
    return;
  }
  if (puVar2 < puVar1) {
    _invalid_parameter_noinfo();
  }
  local_28 = *param_1;
  puStack_20 = puVar2;
  FUN_140089520(param_1,local_18,&local_28,param_2);
  return;
}


// ==== FUN_140089c90 @ 140089c90  longlong * FUN_140089c90(longlong * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_140089c90(longlong *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  longlong local_88;
  longlong local_80;
  longlong local_78;
  longlong local_68;
  longlong local_60;
  longlong local_58;
  longlong local_48;
  longlong local_40;
  longlong local_38;
  longlong local_28;
  longlong local_20;
  longlong local_18;
  
  local_28 = *param_4;
  local_20 = param_4[1];
  local_18 = param_4[2];
  local_88 = *param_3;
  local_80 = param_3[1];
  local_78 = param_3[2];
  local_68 = *param_2;
  local_60 = param_2[1];
  local_58 = param_2[2];
  local_48 = *param_4;
  local_40 = param_4[1];
  local_38 = param_4[2];
  FUN_140085580(&local_48,((local_80 - local_60 >> 2) * 0x20 - local_58) + local_78);
  *param_1 = local_48;
  param_1[1] = local_40;
  param_1[2] = local_38;
  local_48 = local_28;
  local_40 = local_20;
  local_38 = local_18;
  local_28 = local_88;
  local_20 = local_80;
  local_18 = local_78;
  local_88 = local_68;
  local_80 = local_60;
  local_78 = local_58;
  FUN_1400877b0(&local_68,&local_88,(longlong)&local_28,&local_48);
  return param_1;
}


// ==== FUN_140089e00 @ 140089e00  longlong * FUN_140089e00(longlong * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_140089e00(longlong *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  longlong local_88;
  longlong local_80;
  longlong local_78;
  longlong local_68;
  longlong local_60;
  longlong local_58;
  longlong local_48;
  longlong local_40;
  longlong local_38;
  longlong local_28;
  longlong local_20;
  longlong local_18;
  
  local_28 = *param_4;
  local_20 = param_4[1];
  local_18 = param_4[2];
  local_88 = *param_3;
  local_80 = param_3[1];
  local_78 = param_3[2];
  local_68 = *param_2;
  local_60 = param_2[1];
  local_58 = param_2[2];
  local_48 = *param_4;
  local_40 = param_4[1];
  local_38 = param_4[2];
  FUN_140085580(&local_48,(local_58 + (local_80 - local_60 >> 2) * -0x20) - local_78);
  *param_1 = local_48;
  param_1[1] = local_40;
  param_1[2] = local_38;
  local_48 = local_28;
  local_40 = local_20;
  local_38 = local_18;
  local_28 = local_88;
  local_20 = local_80;
  local_18 = local_78;
  local_88 = local_68;
  local_80 = local_60;
  local_78 = local_58;
  FUN_1400879f0(&local_68,(longlong)&local_88,&local_28,&local_48);
  return param_1;
}


// ==== FUN_140089f70 @ 140089f70  longlong FUN_140089f70(longlong * param_1, longlong * param_2, longlong param_3)

longlong FUN_140089f70(longlong *param_1,longlong *param_2,longlong param_3)

{
  longlong lVar1;
  longlong lVar2;
  
  lVar2 = (longlong)param_2 - (longlong)param_1;
  if (param_1 != param_2) {
    lVar1 = param_3 - (longlong)param_1;
    do {
      FUN_140089910((longlong *)(lVar1 + (longlong)param_1),param_1);
      param_1 = param_1 + 6;
    } while (param_1 != param_2);
  }
  return (lVar2 / 0x30) * 0x30 + param_3;
}


// ==== FUN_140089ff0 @ 140089ff0  undefined FUN_140089ff0(longlong * param_1, longlong * param_2, longlong * param_3)

void FUN_140089ff0(longlong *param_1,longlong *param_2,longlong *param_3)

{
  if (param_1 != param_2) {
    do {
      FUN_140089910(param_1,param_3);
      param_1 = param_1 + 6;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_14008a040 @ 14008a040  undefined FUN_14008a040(undefined8 param_1, undefined8 * param_2)

void FUN_14008a040(undefined8 param_1,undefined8 *param_2)

{
  if ((longlong *)param_2[3] != (longlong *)0x0) {
    FUN_1400867a0(param_2,(longlong *)param_2[3],(longlong *)param_2[4]);
    operator_delete((void *)param_2[3]);
  }
  param_2[3] = 0;
  param_2[4] = 0;
  param_2[5] = 0;
  operator_delete((void *)*param_2);
  return;
}


// ==== FUN_14008a0a0 @ 14008a0a0  longlong * FUN_14008a0a0(longlong * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_14008a0a0(longlong *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  ulonglong uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  longlong lVar4;
  longlong lVar5;
  ulonglong uVar6;
  longlong local_c8;
  ulonglong local_c0;
  longlong local_b8;
  longlong local_a8;
  ulonglong local_a0;
  longlong local_98;
  longlong local_88;
  ulonglong local_80;
  longlong local_78;
  longlong local_68;
  ulonglong local_60;
  longlong local_58;
  longlong local_48;
  ulonglong local_40;
  longlong local_38;
  
  local_c8 = *param_3;
  uVar6 = param_1[6];
  local_c0 = param_3[1];
  local_b8 = param_3[2];
  if ((ulonglong)param_1[7] < uVar6) {
    _invalid_parameter_noinfo();
  }
  local_78 = 0;
  local_80 = uVar6;
  if (param_1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  local_88 = *param_1;
  lVar5 = 0;
  if (param_1[2] != 0) {
    uVar6 = param_1[6];
    if ((ulonglong)param_1[7] < uVar6) {
      _invalid_parameter_noinfo();
    }
    FUN_140085580(&local_88,((longlong)(local_c0 - uVar6) >> 2) * 0x20 + local_b8);
    lVar5 = local_78;
    uVar6 = local_80;
  }
  local_c8 = *param_4;
  local_c0 = param_4[1];
  local_b8 = param_4[2];
  uVar1 = param_1[6];
  if ((ulonglong)param_1[7] < uVar1) {
    _invalid_parameter_noinfo();
  }
  local_a8 = *param_1;
  local_98 = 0;
  local_a0 = uVar1;
  if (param_1[2] != 0) {
    uVar1 = param_1[6];
    if ((ulonglong)param_1[7] < uVar1) {
      _invalid_parameter_noinfo();
    }
    FUN_140085580(&local_a8,((longlong)(local_c0 - uVar1) >> 2) * 0x20 + local_b8);
  }
  lVar4 = local_98;
  uVar3 = local_a0;
  uVar1 = param_1[6];
  if ((ulonglong)param_1[7] < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar2 = param_1[6];
  if ((ulonglong)param_1[7] < uVar2) {
    _invalid_parameter_noinfo();
  }
  local_68 = *param_1;
  local_58 = 0;
  local_60 = uVar2;
  if (param_1[2] != 0) {
    FUN_140085580(&local_68,param_1[2]);
  }
  local_c8 = local_88;
  local_c0 = local_80;
  local_b8 = local_78;
  FUN_140085580(&local_c8,local_58 + (((longlong)(local_60 - uVar3) >> 2) * 0x20 - lVar4));
  local_48 = local_88;
  local_40 = local_80;
  local_38 = local_78;
  local_88 = local_68;
  local_80 = local_60;
  local_78 = local_58;
  local_68 = local_a8;
  local_60 = local_a0;
  local_58 = local_98;
  FUN_1400877b0(&local_a8,&local_68,(longlong)&local_88,&local_48);
  uVar3 = param_1[6];
  if ((ulonglong)param_1[7] < uVar3) {
    _invalid_parameter_noinfo();
  }
  FUN_140085250((longlong)param_1,((longlong)(local_c0 - uVar3) >> 2) * 0x20 + local_b8);
  uVar3 = param_1[6];
  if ((ulonglong)param_1[7] < uVar3) {
    _invalid_parameter_noinfo();
  }
  local_c8 = *param_1;
  local_b8 = 0;
  local_98 = 0;
  local_c0 = uVar3;
  local_a8 = local_c8;
  local_a0 = uVar3;
  FUN_140085580(&local_a8,((longlong)(uVar6 - uVar1) >> 2) * 0x20 + lVar5);
  *param_2 = local_a8;
  param_2[1] = local_a0;
  param_2[2] = local_98;
  return param_2;
}


// ==== FUN_14008a400 @ 14008a400  longlong FUN_14008a400(longlong * param_1, longlong param_2, ulonglong param_3)

longlong FUN_14008a400(longlong *param_1,longlong param_2,ulonglong param_3)

{
  ulonglong uVar1;
  code *pcVar2;
  longlong lVar3;
  longlong local_98;
  ulonglong local_90;
  undefined8 local_88;
  longlong local_78;
  ulonglong local_70;
  undefined8 local_68;
  longlong local_58;
  ulonglong local_50;
  undefined8 local_48;
  longlong local_38;
  ulonglong local_30;
  undefined8 local_28;
  
  uVar1 = param_1[6];
  if ((ulonglong)param_1[7] < uVar1) {
    _invalid_parameter_noinfo();
  }
  if (param_1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  lVar3 = ((longlong)(*(longlong *)(param_2 + 8) - uVar1) >> 2) * 0x20 +
          *(longlong *)(param_2 + 0x10);
  if (param_3 != 0) {
    if (-param_1[2] - 1U < param_3) {
      FUN_140080300();
      pcVar2 = (code *)swi(3);
      lVar3 = (*pcVar2)();
      return lVar3;
    }
    FUN_140086b70(param_1 + 3,param_1[2] + 0x1f + param_3 >> 5,0);
    if (param_1[2] == 0) {
      param_1[2] = param_3;
    }
    else {
      uVar1 = param_1[6];
      if ((ulonglong)param_1[7] < uVar1) {
        _invalid_parameter_noinfo();
      }
      local_78 = *param_1;
      local_68 = 0;
      local_70 = uVar1;
      if (param_1[2] != 0) {
        FUN_140085580(&local_78,param_1[2]);
      }
      param_1[2] = param_1[2] + param_3;
      uVar1 = param_1[6];
      if ((ulonglong)param_1[7] < uVar1) {
        _invalid_parameter_noinfo();
      }
      local_98 = *param_1;
      local_88 = 0;
      local_90 = uVar1;
      if (param_1[2] != 0) {
        FUN_140085580(&local_98,param_1[2]);
      }
      uVar1 = param_1[6];
      local_58 = local_98;
      local_50 = local_90;
      local_48 = local_88;
      local_38 = local_78;
      local_30 = local_70;
      local_28 = local_68;
      if ((ulonglong)param_1[7] < uVar1) {
        _invalid_parameter_noinfo();
      }
      local_98 = *param_1;
      local_68 = 0;
      local_88 = 0;
      local_90 = uVar1;
      local_78 = local_98;
      local_70 = uVar1;
      FUN_140085580(&local_98,lVar3);
      local_78 = local_98;
      local_70 = local_90;
      local_68 = local_88;
      FUN_140089e00(&local_98,&local_78,&local_38,&local_58);
    }
  }
  return lVar3;
}


// ==== FUN_14008a600 @ 14008a600  undefined FUN_14008a600(longlong * param_1, longlong * param_2, longlong param_3)

void FUN_14008a600(longlong *param_1,longlong *param_2,longlong param_3)

{
  FUN_140089f70(param_1,param_2,param_3);
  return;
}


// ==== FUN_14008a630 @ 14008a630  undefined FUN_14008a630(longlong * param_1, longlong * param_2, longlong * param_3)

void FUN_14008a630(longlong *param_1,longlong *param_2,longlong *param_3)

{
  if (param_1 != param_2) {
    do {
      FUN_140089910(param_1,param_3);
      param_1 = param_1 + 6;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_14008a680 @ 14008a680  undefined FUN_14008a680(undefined8 * param_1, undefined8 * param_2)

void FUN_14008a680(undefined8 *param_1,undefined8 *param_2)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  longlong *plVar4;
  longlong *plVar5;
  
  if (param_1 != param_2) {
    do {
      plVar5 = (longlong *)param_1[3];
      if (plVar5 != (longlong *)0x0) {
        plVar3 = (longlong *)param_1[4];
        if (plVar5 != plVar3) {
          plVar5 = plVar5 + 1;
          do {
            plVar4 = (longlong *)*plVar5;
            if (plVar4 != (longlong *)0x0) {
              LOCK();
              plVar1 = plVar4 + 2;
              *(int *)plVar1 = (int)*plVar1 + -1;
              UNLOCK();
              if ((int)*plVar1 == 0) {
                (**(code **)*plVar4)(plVar4);
                LOCK();
                piVar2 = (int *)((longlong)plVar4 + 0x14);
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (*piVar2 == 0) {
                  (**(code **)(*plVar4 + 8))(plVar4);
                }
              }
            }
            plVar4 = plVar5 + 1;
            plVar5 = plVar5 + 2;
          } while (plVar4 != plVar3);
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


// ==== FUN_14008a750 @ 14008a750  undefined FUN_14008a750(undefined8 * param_1, longlong param_2, longlong param_3)

void FUN_14008a750(undefined8 *param_1,longlong param_2,longlong param_3)

{
  for (; param_2 != 0; param_2 = param_2 + -1) {
    if (param_1 != (undefined8 *)0x0) {
      FUN_140086a10(param_1,param_3);
    }
    param_1 = param_1 + 6;
  }
  return;
}


// ==== FUN_14008a7d0 @ 14008a7d0  undefined FUN_14008a7d0(longlong * param_1, longlong * param_2, ulonglong param_3, char param_4)

void FUN_14008a7d0(longlong *param_1,longlong *param_2,ulonglong param_3,char param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  char local_res20 [8];
  longlong local_68;
  ulonglong local_60;
  undefined8 local_58;
  longlong local_48;
  ulonglong local_40;
  undefined8 local_38;
  longlong local_28;
  ulonglong local_20;
  longlong local_18;
  
  local_28 = *param_2;
  local_20 = param_2[1];
  local_18 = param_2[2];
  local_res20[0] = param_4;
  lVar2 = FUN_14008a400(param_1,(longlong)&local_28,param_3);
  local_60 = param_1[6];
  if ((ulonglong)param_1[7] < local_60) {
    _invalid_parameter_noinfo();
  }
  local_58 = 0;
  if (param_1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  local_68 = *param_1;
  local_40 = local_60;
  local_38 = local_58;
  local_48 = local_68;
  FUN_140085580(&local_48,param_3 + lVar2);
  uVar1 = param_1[6];
  if ((ulonglong)param_1[7] < uVar1) {
    _invalid_parameter_noinfo();
  }
  local_68 = *param_1;
  local_58 = 0;
  local_18 = 0;
  local_60 = uVar1;
  local_28 = local_68;
  local_20 = uVar1;
  FUN_140085580(&local_28,lVar2);
  local_68 = local_48;
  local_60 = local_40;
  local_58 = local_38;
  local_48 = local_28;
  local_40 = local_20;
  local_38 = local_18;
  FUN_140087540(&local_48,(longlong)&local_68,local_res20);
  return;
}


// ==== FUN_14008a950 @ 14008a950  undefined FUN_14008a950(undefined8 * param_1, longlong param_2, longlong param_3)

void FUN_14008a950(undefined8 *param_1,longlong param_2,longlong param_3)

{
  FUN_14008a750(param_1,param_2,param_3);
  return;
}


// ==== FUN_14008a970 @ 14008a970  longlong * FUN_14008a970(longlong * param_1, longlong * param_2, longlong * param_3)

longlong * FUN_14008a970(longlong *param_1,longlong *param_2,longlong *param_3)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  void *pvVar4;
  void *pvVar5;
  longlong *local_d8 [3];
  void *local_c0;
  void *local_b8;
  undefined8 local_b0;
  longlong *local_a8;
  longlong *local_a0;
  longlong *local_98;
  longlong *local_90;
  longlong *local_88;
  longlong *local_80;
  undefined8 local_78;
  longlong local_70;
  undefined8 local_68;
  longlong *local_60;
  undefined8 *local_58;
  longlong *local_50;
  longlong local_48;
  longlong local_40;
  longlong *local_38;
  undefined8 *local_30;
  
  local_68 = 0xfffffffffffffffe;
  local_98 = param_3;
  local_a8 = (longlong *)operator_new(8);
  if (local_a8 == (longlong *)0x0) {
    local_d8[0] = (longlong *)0x0;
  }
  else {
    *local_a8 = (longlong)local_d8;
    local_d8[0] = local_a8;
  }
  local_c0 = (void *)0x0;
  local_b8 = (void *)0x0;
  local_b0 = 0;
  local_a0 = local_a8;
  for (; pvVar5 = local_b8, param_1 != param_2; param_1 = param_1 + 6) {
    local_a8 = param_3;
    local_a0 = param_3;
    if (param_3 != (longlong *)0x0) {
      FUN_140086a10(param_3,(longlong)local_d8);
    }
    if (param_3 != param_1) {
      local_30 = (undefined8 *)*param_3;
      *param_3 = *param_1;
      *param_1 = (longlong)local_30;
      local_58 = (undefined8 *)*param_3;
      if (local_58 != local_30) {
        local_78 = *local_58;
        *local_58 = *local_30;
        *local_30 = local_78;
      }
      local_38 = param_1 + 3;
      local_90 = param_3 + 3;
      if (local_90 != local_38) {
        local_48 = *local_90;
        *local_90 = *local_38;
        *local_38 = local_48;
      }
      local_88 = param_1 + 4;
      local_80 = param_3 + 4;
      if (local_80 != local_88) {
        local_70 = *local_80;
        *local_80 = *local_88;
        *local_88 = local_70;
      }
      local_60 = param_1 + 5;
      local_50 = param_3 + 5;
      if (local_50 != local_60) {
        local_40 = *local_50;
        *local_50 = *local_60;
        *local_60 = local_40;
      }
    }
    param_3 = param_3 + 6;
  }
  pvVar4 = local_c0;
  if (local_c0 != (void *)0x0) {
    for (; pvVar4 != pvVar5; pvVar4 = (void *)((longlong)pvVar4 + 0x10)) {
      plVar3 = *(longlong **)((longlong)pvVar4 + 8);
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
    }
    operator_delete(local_c0);
  }
  local_c0 = (void *)0x0;
  local_b8 = (void *)0x0;
  local_b0 = 0;
  operator_delete(local_d8[0]);
  return param_3;
}


// ==== FUN_14008ab80 @ 14008ab80  longlong * FUN_14008ab80(longlong * param_1, longlong * param_2, longlong * param_3)

longlong * FUN_14008ab80(longlong *param_1,longlong *param_2,longlong *param_3)

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


// ==== FUN_14008ac40 @ 14008ac40  undefined FUN_14008ac40(longlong * param_1, ulonglong param_2, char param_3)

void FUN_14008ac40(longlong *param_1,ulonglong param_2,char param_3)

{
  ulonglong uVar1;
  longlong local_68;
  ulonglong local_60;
  undefined8 local_58;
  longlong local_48;
  ulonglong local_40;
  undefined8 local_38;
  longlong local_28;
  ulonglong local_20;
  undefined8 local_18;
  
  if ((ulonglong)param_1[2] < param_2) {
    uVar1 = param_1[6];
    if ((ulonglong)param_1[7] < uVar1) {
      _invalid_parameter_noinfo();
    }
    local_68 = *param_1;
    local_58 = 0;
    local_60 = uVar1;
    if (param_1[2] != 0) {
      FUN_140085580(&local_68,param_1[2]);
    }
    local_28 = local_68;
    local_20 = local_60;
    local_18 = local_58;
    FUN_14008a7d0(param_1,&local_28,param_2 - param_1[2],param_3);
  }
  else if (param_2 < (ulonglong)param_1[2]) {
    uVar1 = param_1[6];
    if ((ulonglong)param_1[7] < uVar1) {
      _invalid_parameter_noinfo();
    }
    local_68 = *param_1;
    local_58 = 0;
    local_60 = uVar1;
    if (param_1[2] != 0) {
      FUN_140085580(&local_68,param_1[2]);
    }
    uVar1 = param_1[6];
    if ((ulonglong)param_1[7] < uVar1) {
      _invalid_parameter_noinfo();
    }
    local_48 = *param_1;
    local_38 = 0;
    local_18 = 0;
    local_40 = uVar1;
    local_28 = local_48;
    local_20 = uVar1;
    FUN_140085580(&local_28,param_2);
    local_48 = local_68;
    local_40 = local_60;
    local_38 = local_58;
    local_68 = local_28;
    local_60 = local_20;
    local_58 = local_18;
    FUN_14008a0a0(param_1,&local_28,&local_68,&local_48);
  }
  return;
}


// ==== FUN_14008ae00 @ 14008ae00  undefined8 * FUN_14008ae00(undefined8 param_1, undefined8 * param_2, longlong param_3, longlong param_4)

undefined8 * FUN_14008ae00(undefined8 param_1,undefined8 *param_2,longlong param_3,longlong param_4)

{
  FUN_14008a750(param_2,param_3,param_4);
  return param_2 + param_3 * 6;
}


// ==== FUN_14008ae50 @ 14008ae50  undefined FUN_14008ae50(longlong * param_1, longlong * param_2, longlong * param_3)

void FUN_14008ae50(longlong *param_1,longlong *param_2,longlong *param_3)

{
  FUN_14008a970(param_1,param_2,param_3);
  return;
}


// ==== FUN_14008ae70 @ 14008ae70  longlong * FUN_14008ae70(longlong * param_1, longlong * param_2, longlong * param_3)

longlong * FUN_14008ae70(longlong *param_1,longlong *param_2,longlong *param_3)

{
  FUN_14008ab80(param_1,param_2,param_3);
  return param_3 + (((longlong)param_2 - (longlong)param_1) / 0x30) * -6;
}


// ==== FUN_14008aee0 @ 14008aee0  undefined FUN_14008aee0(longlong param_1)

void FUN_14008aee0(longlong param_1)

{
  if (*(undefined8 **)(param_1 + 0x18) != (undefined8 *)0x0) {
    FUN_14008a680(*(undefined8 **)(param_1 + 0x18),*(undefined8 **)(param_1 + 0x20));
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_14008af30 @ 14008af30  longlong * FUN_14008af30(longlong * param_1, longlong * param_2, longlong param_3, longlong param_4)

longlong * FUN_14008af30(longlong *param_1,longlong *param_2,longlong param_3,longlong param_4)

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
    puVar4 = (undefined8 *)FUN_140089f70(plVar3,(longlong *)param_1[4],param_2[1]);
    FUN_14008a680(puVar4,(undefined8 *)param_1[4]);
    param_1[4] = (longlong)puVar4;
  }
  return param_2;
}


// ==== FUN_14008b030 @ 14008b030  undefined FUN_14008b030(undefined8 param_1, longlong * param_2, longlong * param_3, longlong * param_4)

void FUN_14008b030(undefined8 param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  FUN_14008a970(param_2,param_3,param_4);
  return;
}


// ==== FUN_14008b070 @ 14008b070  longlong * FUN_14008b070(longlong * param_1, longlong * param_2, longlong * param_3)

longlong * FUN_14008b070(longlong *param_1,longlong *param_2,longlong *param_3)

{
  FUN_14008ab80(param_1,param_2,param_3);
  return param_3 + (((longlong)param_2 - (longlong)param_1) / 0x30) * -6;
}


// ==== FUN_14008b0e0 @ 14008b0e0  undefined FUN_14008b0e0(undefined8 * param_1)

void FUN_14008b0e0(undefined8 *param_1)

{
  if ((undefined8 *)param_1[3] != (undefined8 *)0x0) {
    FUN_14008a680((undefined8 *)param_1[3],(undefined8 *)param_1[4]);
    operator_delete((void *)param_1[3]);
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14008b140 @ 14008b140  undefined FUN_14008b140(longlong param_1, longlong param_2, ulonglong param_3, longlong param_4)

void FUN_14008b140(longlong param_1,longlong param_2,ulonglong param_3,longlong param_4)

{
  int *piVar1;
  longlong *plVar2;
  ulonglong uVar3;
  undefined8 *puVar4;
  code *pcVar5;
  void *pvVar6;
  longlong *plVar7;
  void *pvVar8;
  longlong *plVar9;
  longlong *plVar10;
  longlong lVar11;
  longlong lVar12;
  ulonglong uVar13;
  ulonglong uVar14;
  void *local_a0 [3];
  void *local_88;
  void *local_80;
  undefined8 local_78;
  void *local_70 [3];
  longlong *local_58;
  longlong *local_50;
  undefined8 local_48;
  undefined8 local_40;
  
  local_40 = 0xfffffffffffffffe;
  lVar12 = *(longlong *)(param_1 + 0x18);
  if (lVar12 == 0) {
    uVar13 = 0;
  }
  else {
    lVar11 = *(longlong *)(param_1 + 0x28) - lVar12;
    lVar11 = lVar11 / 6 + (lVar11 >> 0x3f);
    uVar13 = (lVar11 >> 3) - (lVar11 >> 0x3f);
  }
  uVar14 = 0;
  if (param_3 != 0) {
    lVar12 = (*(longlong *)(param_1 + 0x20) - lVar12) / 0x30;
    if (0x555555555555555U - lVar12 < param_3) {
      FUN_140080070();
      pcVar5 = (code *)swi(3);
      (*pcVar5)();
      return;
    }
    uVar3 = lVar12 + param_3;
    if (uVar13 < uVar3) {
      if (uVar13 <= 0x555555555555555 - (uVar13 >> 1)) {
        uVar14 = uVar13 + (uVar13 >> 1);
      }
      if (uVar14 < uVar3) {
        uVar14 = uVar3;
      }
      plVar9 = (longlong *)FUN_140081310(param_1 + 0x10,uVar14);
      lVar12 = *(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18);
      lVar12 = lVar12 / 6 + (lVar12 >> 0x3f);
      lVar12 = (lVar12 >> 3) - (lVar12 >> 0x3f);
      FUN_14008a750(plVar9 + lVar12 * 6,param_3,param_4);
      FUN_14008a970(*(longlong **)(param_1 + 0x18),*(longlong **)(param_2 + 8),plVar9);
      FUN_14008a970(*(longlong **)(param_2 + 8),*(longlong **)(param_1 + 0x20),
                    plVar9 + (lVar12 + param_3) * 6);
      puVar4 = *(undefined8 **)(param_1 + 0x18);
      lVar12 = *(longlong *)(param_1 + 0x20);
      if (puVar4 != (undefined8 *)0x0) {
        FUN_14008a680(puVar4,*(undefined8 **)(param_1 + 0x20));
        operator_delete(*(void **)(param_1 + 0x18));
      }
      *(longlong **)(param_1 + 0x28) = plVar9 + uVar14 * 6;
      *(longlong **)(param_1 + 0x20) = plVar9 + (param_3 + (lVar12 - (longlong)puVar4) / 0x30) * 6;
      *(longlong **)(param_1 + 0x18) = plVar9;
    }
    else if ((ulonglong)((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_2 + 8)) / 0x30) <
             param_3) {
      FUN_140086a10(local_a0,param_4);
      FUN_14008a970(*(longlong **)(param_2 + 8),*(longlong **)(param_1 + 0x20),
                    *(longlong **)(param_2 + 8) + param_3 * 6);
      FUN_14008a750(*(undefined8 **)(param_1 + 0x20),
                    param_3 - ((longlong)*(undefined8 **)(param_1 + 0x20) -
                              *(longlong *)(param_2 + 8)) / 0x30,(longlong)local_a0);
      *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + param_3 * 0x30;
      lVar12 = *(longlong *)(param_1 + 0x20);
      pvVar6 = local_80;
      for (plVar9 = *(longlong **)(param_2 + 8); plVar9 != (longlong *)(lVar12 + param_3 * -0x30);
          plVar9 = plVar9 + 6) {
        local_80 = pvVar6;
        FUN_140089910(plVar9,(longlong *)local_a0);
        pvVar6 = local_80;
      }
      pvVar8 = local_88;
      if (local_88 != (void *)0x0) {
        for (; pvVar8 != pvVar6; pvVar8 = (void *)((longlong)pvVar8 + 0x10)) {
          plVar9 = *(longlong **)((longlong)pvVar8 + 8);
          if (plVar9 != (longlong *)0x0) {
            LOCK();
            plVar10 = plVar9 + 2;
            *(int *)plVar10 = (int)*plVar10 + -1;
            UNLOCK();
            if ((int)*plVar10 == 0) {
              (**(code **)*plVar9)(plVar9);
              LOCK();
              piVar1 = (int *)((longlong)plVar9 + 0x14);
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (*piVar1 == 0) {
                (**(code **)(*plVar9 + 8))(plVar9);
              }
            }
          }
        }
        operator_delete(local_88);
      }
      local_88 = (void *)0x0;
      local_80 = (void *)0x0;
      local_78 = 0;
      operator_delete(local_a0[0]);
    }
    else {
      FUN_140086a10(local_70,param_4);
      plVar9 = *(longlong **)(param_1 + 0x20);
      plVar10 = FUN_14008a970(plVar9 + param_3 * -6,plVar9,plVar9);
      *(longlong **)(param_1 + 0x20) = plVar10;
      FUN_14008b070(*(longlong **)(param_2 + 8),plVar9 + param_3 * -6,plVar9);
      plVar10 = *(longlong **)(param_2 + 8);
      plVar9 = plVar10 + param_3 * 6;
      plVar7 = local_50;
      for (; plVar10 != plVar9; plVar10 = plVar10 + 6) {
        local_50 = plVar7;
        FUN_140089910(plVar10,(longlong *)local_70);
        plVar7 = local_50;
      }
      if (local_58 != (longlong *)0x0) {
        if (local_58 != plVar7) {
          plVar9 = local_58 + 1;
          do {
            plVar10 = (longlong *)*plVar9;
            if (plVar10 != (longlong *)0x0) {
              LOCK();
              plVar2 = plVar10 + 2;
              *(int *)plVar2 = (int)*plVar2 + -1;
              UNLOCK();
              if ((int)*plVar2 == 0) {
                (**(code **)*plVar10)(plVar10);
                LOCK();
                piVar1 = (int *)((longlong)plVar10 + 0x14);
                *piVar1 = *piVar1 + -1;
                UNLOCK();
                if (*piVar1 == 0) {
                  (**(code **)(*plVar10 + 8))(plVar10);
                }
              }
            }
            plVar10 = plVar9 + 1;
            plVar9 = plVar9 + 2;
          } while (plVar10 != plVar7);
        }
        operator_delete(local_58);
      }
      local_58 = (longlong *)0x0;
      local_50 = (longlong *)0x0;
      local_48 = 0;
      operator_delete(local_70[0]);
    }
  }
  return;
}


// ==== FUN_14008b610 @ 14008b610  undefined8 * FUN_14008b610(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14008b610(undefined8 *param_1,undefined8 *param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  longlong *plVar5;
  undefined8 uVar6;
  longlong *plVar7;
  longlong *plVar8;
  
  *param_1 = IMapData::vftable;
  *param_1 = CMapData::vftable;
  plVar5 = (longlong *)operator_new(8);
  plVar8 = (longlong *)0x0;
  plVar7 = plVar8;
  if (plVar5 != (longlong *)0x0) {
    *plVar5 = (longlong)(param_1 + 6);
    plVar7 = plVar5;
  }
  param_1[6] = plVar7;
  uVar6 = FUN_1400821c0();
  param_1[0xb] = uVar6;
  param_1[0xc] = 0;
  plVar5 = (longlong *)operator_new(8);
  plVar7 = plVar8;
  if (plVar5 != (longlong *)0x0) {
    *plVar5 = (longlong)(param_1 + 0xd);
    plVar7 = plVar5;
  }
  param_1[0xd] = plVar7;
  uVar6 = FUN_1400821c0();
  param_1[0x12] = uVar6;
  param_1[0x13] = 0;
  plVar5 = (longlong *)operator_new(8);
  plVar7 = plVar8;
  if (plVar5 != (longlong *)0x0) {
    *plVar5 = (longlong)(param_1 + 0x14);
    plVar7 = plVar5;
  }
  param_1[0x14] = plVar7;
  param_1[0x17] = 0;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  plVar5 = (longlong *)operator_new(8);
  plVar7 = plVar8;
  if (plVar5 != (longlong *)0x0) {
    *plVar5 = (longlong)(param_1 + 0x1a);
    plVar7 = plVar5;
  }
  param_1[0x1a] = plVar7;
  param_1[0x1d] = 0;
  param_1[0x1e] = 0;
  param_1[0x1f] = 0;
  param_1[0x20] = 0;
  param_1[0x21] = 0;
  FUN_140081910(param_1 + 0x20,*param_2,param_2[1]);
  FUN_140084fa0(param_1 + 0x22);
  plVar7 = (longlong *)operator_new(8);
  if (plVar7 != (longlong *)0x0) {
    *plVar7 = (longlong)(param_1 + 0x2b);
    plVar8 = plVar7;
  }
  param_1[0x2b] = plVar8;
  uVar6 = FUN_140082240();
  param_1[0x30] = uVar6;
  param_1[0x31] = 0;
  FUN_14003c110(param_1 + 0x32);
  *(undefined4 *)(param_1 + 1) = 0;
  *(undefined4 *)((longlong)param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 3) = 0;
  *(undefined4 *)((longlong)param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)((longlong)param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 5) = 0;
  puVar2 = (undefined4 *)param_1[0x20];
  iVar3 = FUN_14008d7a0((longlong)puVar2);
  iVar4 = FUN_14008d7b0(puVar2);
  FUN_14008ac40(param_1 + 0x22,(longlong)(iVar3 * iVar4),'\0');
  plVar8 = (longlong *)param_2[1];
  if (plVar8 != (longlong *)0x0) {
    LOCK();
    plVar7 = plVar8 + 2;
    *(int *)plVar7 = (int)*plVar7 + -1;
    UNLOCK();
    if ((int)*plVar7 == 0) {
      (**(code **)*plVar8)(plVar8);
      LOCK();
      piVar1 = (int *)((longlong)plVar8 + 0x14);
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (*piVar1 == 0) {
        (**(code **)(*plVar8 + 8))(plVar8);
      }
    }
  }
  return param_1;
}


// ==== FUN_14008b880 @ 14008b880  undefined FUN_14008b880(undefined8 * param_1)

void FUN_14008b880(undefined8 *param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  FUN_14003a700(param_1 + 0x32);
  operator_delete((void *)param_1[0x32]);
  FUN_1400853d0((longlong)(param_1 + 0x2b));
  operator_delete((void *)param_1[0x30]);
  param_1[0x30] = 0;
  operator_delete((void *)param_1[0x2b]);
  FUN_140085030(param_1 + 0x22);
  plVar3 = (longlong *)param_1[0x21];
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
  if ((void *)param_1[0x1d] != (void *)0x0) {
    operator_delete((void *)param_1[0x1d]);
  }
  param_1[0x1d] = 0;
  param_1[0x1e] = 0;
  param_1[0x1f] = 0;
  operator_delete((void *)param_1[0x1a]);
  if ((undefined8 *)param_1[0x17] != (undefined8 *)0x0) {
    FUN_14008a680((undefined8 *)param_1[0x17],(undefined8 *)param_1[0x18]);
    operator_delete((void *)param_1[0x17]);
  }
  param_1[0x17] = 0;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  operator_delete((void *)param_1[0x14]);
  FUN_140085c30((longlong)(param_1 + 0xd));
  operator_delete((void *)param_1[0x12]);
  param_1[0x12] = 0;
  operator_delete((void *)param_1[0xd]);
  FUN_140085c30((longlong)(param_1 + 6));
  operator_delete((void *)param_1[0xb]);
  param_1[0xb] = 0;
  operator_delete((void *)param_1[6]);
  *param_1 = IMapData::vftable;
  return;
}


// ==== FUN_14008ba00 @ 14008ba00  undefined8 * FUN_14008ba00(uint param_1, char * param_2, int param_3)

undefined8 * FUN_14008ba00(uint param_1,char *param_2,int param_3)

{
  longlong *plVar1;
  int *piVar2;
  undefined8 *puVar3;
  longlong local_28;
  longlong *local_20;
  undefined8 local_18;
  undefined8 local_10;
  
  FUN_1400932d0(&local_28,param_1,param_2,param_3);
  if (local_28 == 0) {
    log_InlineLogERROR("CMapData cannot load map %d from file %s, gridsize=%d");
    if (local_20 != (longlong *)0x0) {
      LOCK();
      plVar1 = local_20 + 2;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)*plVar1 == 0) {
        (**(code **)*local_20)(local_20);
        LOCK();
        piVar2 = (int *)((longlong)local_20 + 0x14);
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (*piVar2 == 0) {
          (**(code **)(*local_20 + 8))(local_20);
        }
      }
    }
    puVar3 = (undefined8 *)0x0;
  }
  else {
    puVar3 = (undefined8 *)operator_new(0x1d0);
    if (puVar3 == (undefined8 *)0x0) {
      puVar3 = (undefined8 *)0x0;
    }
    else {
      local_18 = 0;
      local_10 = 0;
      FUN_140081910(&local_18,local_28,(longlong)local_20);
      puVar3 = FUN_14008b610(puVar3,&local_18);
    }
    if (local_20 != (longlong *)0x0) {
      LOCK();
      plVar1 = local_20 + 2;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)*plVar1 == 0) {
        (**(code **)*local_20)(local_20);
        LOCK();
        piVar2 = (int *)((longlong)local_20 + 0x14);
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (*piVar2 == 0) {
          (**(code **)(*local_20 + 8))(local_20);
        }
      }
    }
  }
  return puVar3;
}


// ==== FUN_14008bb20 @ 14008bb20  undefined FUN_14008bb20(longlong * param_1, ulonglong param_2, undefined8 * param_3)

void FUN_14008bb20(longlong *param_1,ulonglong param_2,undefined8 *param_3)

{
  longlong *plVar1;
  longlong *plVar2;
  ulonglong uVar3;
  longlong lVar4;
  undefined8 *puVar5;
  longlong *plVar6;
  longlong local_28;
  longlong *plStack_20;
  
  plVar1 = (longlong *)param_1[4];
  plVar2 = (longlong *)param_1[3];
  uVar3 = ((longlong)plVar1 - (longlong)plVar2) / 0x30;
  if (uVar3 < param_2) {
    if (plVar1 < plVar2) {
      _invalid_parameter_noinfo();
    }
    local_28 = *param_1;
    plStack_20 = plVar1;
    FUN_14008b140((longlong)param_1,(longlong)&local_28,param_2 - (param_1[4] - param_1[3]) / 0x30,
                  (longlong)param_3);
    goto LAB_14008bcc5;
  }
  if (uVar3 <= param_2) goto LAB_14008bcc5;
  if (plVar1 < plVar2) {
    _invalid_parameter_noinfo();
  }
  uVar3 = param_1[3];
  if ((ulonglong)param_1[4] < uVar3) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)*param_1;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar4 = 0;
  }
  else {
    lVar4 = *plVar2;
  }
  plVar6 = (longlong *)(uVar3 + param_2 * 0x30);
  if (*(longlong **)(lVar4 + 0x20) < plVar6) {
LAB_14008bc39:
    _invalid_parameter_noinfo();
  }
  else {
    if (plVar2 == (longlong *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar2;
    }
    if (plVar6 < *(longlong **)(lVar4 + 0x18)) goto LAB_14008bc39;
  }
  if ((plVar6 < (longlong *)param_1[3]) || ((longlong *)param_1[4] < plVar6)) {
    _invalid_parameter_noinfo();
  }
  lVar4 = *param_1;
  if ((plVar1 < (longlong *)param_1[3]) || ((longlong *)param_1[4] < plVar1)) {
    _invalid_parameter_noinfo();
  }
  if ((lVar4 == 0) || (lVar4 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (plVar6 != plVar1) {
    puVar5 = (undefined8 *)FUN_140089f70(plVar1,(longlong *)param_1[4],(longlong)plVar6);
    FUN_14008a680(puVar5,(undefined8 *)param_1[4]);
    param_1[4] = (longlong)puVar5;
  }
LAB_14008bcc5:
  if ((longlong *)param_3[3] != (longlong *)0x0) {
    FUN_1400867a0(param_3,(longlong *)param_3[3],(longlong *)param_3[4]);
    operator_delete((void *)param_3[3]);
  }
  param_3[3] = 0;
  param_3[4] = 0;
  param_3[5] = 0;
  operator_delete((void *)*param_3);
  return;
}


// ==== FUN_14008bd50 @ 14008bd50  undefined FUN_14008bd50(longlong * param_1, ulonglong param_2)

void FUN_14008bd50(longlong *param_1,ulonglong param_2)

{
  longlong *plVar1;
  longlong *local_38 [3];
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  
  plVar1 = (longlong *)operator_new(8);
  local_38[0] = (longlong *)0x0;
  if (plVar1 != (longlong *)0x0) {
    *plVar1 = (longlong)local_38;
    local_38[0] = plVar1;
  }
  local_20 = 0;
  local_18 = 0;
  local_10 = 0;
  FUN_14008bb20(param_1,param_2,local_38);
  return;
}


// ==== FUN_14008d7a0 @ 14008d7a0  undefined4 FUN_14008d7a0(longlong param_1)

undefined4 FUN_14008d7a0(longlong param_1)

{
  return *(undefined4 *)(param_1 + 4);
}


// ==== FUN_14008d7b0 @ 14008d7b0  undefined4 FUN_14008d7b0(undefined4 * param_1)

undefined4 FUN_14008d7b0(undefined4 *param_1)

{
  return *param_1;
}


// ==== FUN_14008d7c0 @ 14008d7c0  undefined1 FUN_14008d7c0(int * param_1, int param_2, int param_3)

undefined1 FUN_14008d7c0(int *param_1,int param_2,int param_3)

{
  if ((((-1 < param_2) && (-1 < param_3)) && (param_2 < *param_1)) && (param_3 < param_1[1])) {
    return 1;
  }
  return 0;
}


// ==== FUN_14008d7e0 @ 14008d7e0  int FUN_14008d7e0(int * param_1, int param_2, int param_3)

int FUN_14008d7e0(int *param_1,int param_2,int param_3)

{
  return *param_1 * param_3 + param_2;
}


// ==== FUN_14008d800 @ 14008d800  undefined FUN_14008d800(longlong param_1)

void FUN_14008d800(longlong param_1)

{
  if (*(void **)(param_1 + 8) != (void *)0x0) {
    operator_delete__(*(void **)(param_1 + 8));
  }
  return;
}


// ==== FUN_14008d830 @ 14008d830  bool FUN_14008d830(int * param_1, int param_2)

bool FUN_14008d830(int *param_1,int param_2)

{
  void *_Dst;
  
  _Dst = operator_new__((longlong)param_2 << 2);
  *(void **)(param_1 + 2) = _Dst;
  memset(_Dst,0,(longlong)param_2 << 2);
  *param_1 = param_2;
  return *(longlong *)(param_1 + 2) != 0;
}


// ==== FUN_14008d950 @ 14008d950  bool FUN_14008d950(longlong * param_1, longlong * param_2)

bool FUN_14008d950(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_14008d9b0 @ 14008d9b0  bool FUN_14008d9b0(longlong * param_1, longlong * param_2)

bool FUN_14008d9b0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_14008db20 @ 14008db20  longlong FUN_14008db20(longlong * param_1)

longlong FUN_14008db20(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14008db42;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14008db42:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_14008dba0 @ 14008dba0  undefined FUN_14008dba0(longlong param_1, longlong * param_2)

void FUN_14008dba0(longlong param_1,longlong *param_2)

{
  longlong lVar1;
  longlong *plVar2;
  
  lVar1 = *param_2;
  *param_2 = *(longlong *)(lVar1 + 0x10);
  if (*(char *)(*(longlong *)(lVar1 + 0x10) + 0x29) == '\0') {
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


// ==== FUN_14008dd10 @ 14008dd10  undefined FUN_14008dd10(longlong * param_1)

void FUN_14008dd10(longlong *param_1)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *plVar4;
  
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  lVar2 = param_1[1];
  if (*(char *)(lVar2 + 0x51) == '\0') {
    plVar3 = *(longlong **)(lVar2 + 0x10);
    if (*(char *)((longlong)plVar3 + 0x51) != '\0') {
      lVar2 = *(longlong *)(lVar2 + 8);
      cVar1 = *(char *)(lVar2 + 0x51);
      while ((cVar1 == '\0' && (param_1[1] == *(longlong *)(lVar2 + 0x10)))) {
        param_1[1] = lVar2;
        lVar2 = *(longlong *)(lVar2 + 8);
        cVar1 = *(char *)(lVar2 + 0x51);
      }
      param_1[1] = lVar2;
      return;
    }
    cVar1 = *(char *)(*plVar3 + 0x51);
    plVar4 = (longlong *)*plVar3;
    while (cVar1 == '\0') {
      cVar1 = *(char *)(*plVar4 + 0x51);
      plVar3 = plVar4;
      plVar4 = (longlong *)*plVar4;
    }
    param_1[1] = (longlong)plVar3;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00014008dd34. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_14008dde0 @ 14008dde0  undefined FUN_14008dde0(ulonglong param_1)

void FUN_14008dde0(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x58)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 * 0x58);
  return;
}


// ==== FUN_14008de60 @ 14008de60  undefined FUN_14008de60(ulonglong param_1)

void FUN_14008de60(ulonglong param_1)

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


// ==== FUN_14008df40 @ 14008df40  undefined8 * FUN_14008df40(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_14008df40(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  param_1[1] = param_2;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14) = 1;
  *param_1 = std::tr1::_Ref_count<class_CMapStaticData>::vftable;
  return param_1;
}


// ==== FUN_14008dfa0 @ 14008dfa0  undefined FUN_14008dfa0(undefined8 * param_1)

void FUN_14008dfa0(undefined8 *param_1)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  return;
}


// ==== FUN_14008dfc0 @ 14008dfc0  longlong * FUN_14008dfc0(longlong * param_1, longlong param_2)

longlong * FUN_14008dfc0(longlong *param_1,longlong param_2)

{
  longlong lVar1;
  longlong lVar2;
  ulonglong uVar3;
  
  if (*param_1 != -4) {
    if (*param_1 == 0) {
      _invalid_parameter_noinfo();
    }
    lVar1 = *param_1;
    if (*(ulonglong *)(lVar1 + 0x20) < 0x10) {
      lVar2 = lVar1 + 8;
    }
    else {
      lVar2 = *(longlong *)(lVar1 + 8);
    }
    if ((ulonglong)(param_1[1] + param_2) <= (ulonglong)(lVar2 + *(longlong *)(lVar1 + 0x18))) {
      if (*(ulonglong *)(lVar1 + 0x20) < 0x10) {
        uVar3 = lVar1 + 8;
      }
      else {
        uVar3 = *(ulonglong *)(lVar1 + 8);
      }
      if (uVar3 <= (ulonglong)(param_1[1] + param_2)) goto LAB_14008e024;
    }
    _invalid_parameter_noinfo();
  }
LAB_14008e024:
  param_1[1] = param_1[1] + param_2;
  return param_1;
}


// ==== FUN_14008e040 @ 14008e040  undefined1 * FUN_14008e040(char * param_1, char * param_2, undefined1 * param_3, undefined * param_4)

undefined1 * FUN_14008e040(char *param_1,char *param_2,undefined1 *param_3,undefined *param_4)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  
  puVar2 = param_3;
  if (param_1 != param_2) {
    do {
      uVar1 = (*(code *)param_4)((int)*param_1);
      param_1 = param_1 + 1;
      param_3 = puVar2 + 1;
      *puVar2 = uVar1;
      puVar2 = param_3;
    } while (param_1 != param_2);
  }
  return param_3;
}


// ==== FUN_14008e0a0 @ 14008e0a0  undefined FUN_14008e0a0(int * param_1, int param_2, int param_3)

void FUN_14008e0a0(int *param_1,int param_2,int param_3)

{
  FUN_140096790((ushort *)
                (*(longlong *)(param_1 + 4) + (longlong)(*param_1 * param_3 + param_2) * 4));
  return;
}


// ==== FUN_14008e0c0 @ 14008e0c0  bool FUN_14008e0c0(longlong * param_1, longlong * param_2)

bool FUN_14008e0c0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_14008e100 @ 14008e100  bool FUN_14008e100(longlong * param_1, longlong * param_2)

bool FUN_14008e100(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_14008e150 @ 14008e150  undefined FUN_14008e150(undefined8 * param_1)

void FUN_14008e150(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14008e180 @ 14008e180  undefined FUN_14008e180(undefined8 * param_1)

void FUN_14008e180(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14008e190 @ 14008e190  longlong FUN_14008e190(longlong * param_1)

longlong FUN_14008e190(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14008e1b2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14008e1b2:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_14008e1d0 @ 14008e1d0  longlong FUN_14008e1d0(longlong * param_1)

longlong FUN_14008e1d0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14008e1f2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14008e1f2:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_14008e210 @ 14008e210  longlong FUN_14008e210(longlong * param_1)

longlong FUN_14008e210(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14008e232;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14008e232:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_14008e2b0 @ 14008e2b0  undefined8 * FUN_14008e2b0(longlong param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

undefined8 *
FUN_14008e2b0(longlong param_1,
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  char cVar1;
  undefined8 *puVar2;
  bool bVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  
  puVar5 = (undefined8 *)(*(undefined8 **)(param_1 + 0x30))[1];
  cVar1 = *(char *)((longlong)puVar5 + 0x51);
  puVar2 = *(undefined8 **)(param_1 + 0x30);
  while (cVar1 == '\0') {
    bVar3 = std::operator<<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                      ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                        *)(puVar5 + 3),param_2);
    if (bVar3) {
      puVar4 = (undefined8 *)puVar5[2];
      puVar5 = puVar2;
    }
    else {
      puVar4 = (undefined8 *)*puVar5;
    }
    puVar2 = puVar5;
    puVar5 = puVar4;
    cVar1 = *(char *)((longlong)puVar4 + 0x51);
  }
  return puVar2;
}


// ==== FUN_14008e310 @ 14008e310  undefined FUN_14008e310(longlong param_1, longlong param_2)

void FUN_14008e310(longlong param_1,longlong param_2)

{
  longlong *plVar1;
  longlong *plVar2;
  
  plVar1 = *(longlong **)(param_2 + 0x10);
  *(longlong *)(param_2 + 0x10) = *plVar1;
  if (*(char *)(*plVar1 + 0x51) == '\0') {
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


// ==== FUN_14008e370 @ 14008e370  undefined FUN_14008e370(longlong param_1, longlong * param_2)

void FUN_14008e370(longlong param_1,longlong *param_2)

{
  longlong lVar1;
  longlong *plVar2;
  
  lVar1 = *param_2;
  *param_2 = *(longlong *)(lVar1 + 0x10);
  if (*(char *)(*(longlong *)(lVar1 + 0x10) + 0x51) == '\0') {
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


// ==== FUN_14008e410 @ 14008e410  undefined FUN_14008e410(longlong param_1, longlong param_2)

void FUN_14008e410(longlong param_1,longlong param_2)

{
  longlong *plVar1;
  longlong *plVar2;
  
  plVar1 = *(longlong **)(param_2 + 0x10);
  *(longlong *)(param_2 + 0x10) = *plVar1;
  if (*(char *)(*plVar1 + 0x29) == '\0') {
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


// ==== FUN_14008e470 @ 14008e470  undefined FUN_14008e470(undefined8 param_1, ulonglong param_2)

void FUN_14008e470(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x58)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 0x58);
  return;
}


// ==== FUN_14008e4e0 @ 14008e4e0  undefined FUN_14008e4e0(longlong * param_1)

void FUN_14008e4e0(longlong *param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)param_1[1];
  if (*(char *)((longlong)plVar2 + 0x29) == '\0') {
    lVar3 = *plVar2;
    if (*(char *)(lVar3 + 0x29) == '\0') {
      cVar1 = *(char *)(*(longlong *)(lVar3 + 0x10) + 0x29);
      lVar4 = *(longlong *)(lVar3 + 0x10);
      while (lVar5 = lVar4, cVar1 == '\0') {
        lVar4 = *(longlong *)(lVar5 + 0x10);
        cVar1 = *(char *)(lVar4 + 0x29);
        lVar3 = lVar5;
      }
      param_1[1] = lVar3;
      return;
    }
    plVar2 = (longlong *)plVar2[1];
    cVar1 = *(char *)((longlong)plVar2 + 0x29);
    while ((cVar1 == '\0' && (param_1[1] == *plVar2))) {
      param_1[1] = (longlong)plVar2;
      plVar2 = (longlong *)plVar2[1];
      cVar1 = *(char *)((longlong)plVar2 + 0x29);
    }
    if (*(char *)(param_1[1] + 0x29) == '\0') {
      param_1[1] = (longlong)plVar2;
      return;
    }
  }
  else {
    lVar3 = plVar2[2];
    param_1[1] = lVar3;
    if (*(char *)(lVar3 + 0x29) == '\0') {
      return;
    }
  }
                    /* WARNING: Could not recover jumptable at 0x00014008e512. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_14008e580 @ 14008e580  undefined FUN_14008e580(longlong * param_1)

void FUN_14008e580(longlong *param_1)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *plVar4;
  
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  lVar2 = param_1[1];
  if (*(char *)(lVar2 + 0x29) == '\0') {
    plVar3 = *(longlong **)(lVar2 + 0x10);
    if (*(char *)((longlong)plVar3 + 0x29) != '\0') {
      lVar2 = *(longlong *)(lVar2 + 8);
      cVar1 = *(char *)(lVar2 + 0x29);
      while ((cVar1 == '\0' && (param_1[1] == *(longlong *)(lVar2 + 0x10)))) {
        param_1[1] = lVar2;
        lVar2 = *(longlong *)(lVar2 + 8);
        cVar1 = *(char *)(lVar2 + 0x29);
      }
      param_1[1] = lVar2;
      return;
    }
    cVar1 = *(char *)(*plVar3 + 0x29);
    plVar4 = (longlong *)*plVar3;
    while (cVar1 == '\0') {
      cVar1 = *(char *)(*plVar4 + 0x29);
      plVar3 = plVar4;
      plVar4 = (longlong *)*plVar4;
    }
    param_1[1] = (longlong)plVar3;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00014008e5a4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_14008e610 @ 14008e610  undefined FUN_14008e610(longlong * param_1)

void FUN_14008e610(longlong *param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)param_1[1];
  if (*(char *)((longlong)plVar2 + 0x51) == '\0') {
    lVar3 = *plVar2;
    if (*(char *)(lVar3 + 0x51) == '\0') {
      cVar1 = *(char *)(*(longlong *)(lVar3 + 0x10) + 0x51);
      lVar4 = *(longlong *)(lVar3 + 0x10);
      while (lVar5 = lVar4, cVar1 == '\0') {
        lVar4 = *(longlong *)(lVar5 + 0x10);
        cVar1 = *(char *)(lVar4 + 0x51);
        lVar3 = lVar5;
      }
      param_1[1] = lVar3;
      return;
    }
    plVar2 = (longlong *)plVar2[1];
    cVar1 = *(char *)((longlong)plVar2 + 0x51);
    while ((cVar1 == '\0' && (param_1[1] == *plVar2))) {
      param_1[1] = (longlong)plVar2;
      plVar2 = (longlong *)plVar2[1];
      cVar1 = *(char *)((longlong)plVar2 + 0x51);
    }
    if (*(char *)(param_1[1] + 0x51) == '\0') {
      param_1[1] = (longlong)plVar2;
      return;
    }
  }
  else {
    lVar3 = plVar2[2];
    param_1[1] = lVar3;
    if (*(char *)(lVar3 + 0x51) == '\0') {
      return;
    }
  }
                    /* WARNING: Could not recover jumptable at 0x00014008e642. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_14008e6b0 @ 14008e6b0  undefined FUN_14008e6b0(undefined8 param_1, ulonglong param_2)

void FUN_14008e6b0(undefined8 param_1,ulonglong param_2)

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


// ==== FUN_14008e750 @ 14008e750  longlong * FUN_14008e750(longlong * param_1)

longlong * FUN_14008e750(longlong *param_1)

{
  FUN_14008dd10(param_1);
  return param_1;
}


// ==== FUN_14008e770 @ 14008e770  undefined8 * FUN_14008e770(undefined8 * param_1)

undefined8 * FUN_14008e770(undefined8 *param_1)

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


// ==== FUN_14008e7b0 @ 14008e7b0  undefined8 * FUN_14008e7b0(undefined8 * param_1)

undefined8 * FUN_14008e7b0(undefined8 *param_1)

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


// ==== FUN_14008e830 @ 14008e830  longlong * FUN_14008e830(longlong * param_1, longlong param_2)

longlong * FUN_14008e830(longlong *param_1,longlong param_2)

{
  FUN_14008dfc0(param_1,param_2);
  return param_1;
}


// ==== FUN_14008e870 @ 14008e870  longlong FUN_14008e870(longlong * param_1)

longlong FUN_14008e870(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14008e892;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14008e892:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_14008e8b0 @ 14008e8b0  longlong FUN_14008e8b0(longlong * param_1)

longlong FUN_14008e8b0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14008e8d2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14008e8d2:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_14008e8f0 @ 14008e8f0  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * FUN_14008e8f0(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2, undefined8 * param_3)

basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
FUN_14008e8f0(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1,
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2,
             undefined8 *param_3)

{
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(param_1,param_2);
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x30) = 0;
  FUN_140081910((undefined8 *)(param_1 + 0x28),*param_3,param_3[1]);
  return param_1;
}


// ==== FUN_14008e940 @ 14008e940  undefined FUN_14008e940(undefined8 * param_1)

void FUN_14008e940(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14008e960 @ 14008e960  undefined FUN_14008e960(undefined8 * param_1)

void FUN_14008e960(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14008e980 @ 14008e980  undefined8 * FUN_14008e980(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_14008e980(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_14008e9c0 @ 14008e9c0  undefined FUN_14008e9c0(undefined8 * param_1)

void FUN_14008e9c0(undefined8 *param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = (longlong *)param_1[1];
  if (plVar3 == (longlong *)0x0) {
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
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
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
  param_1[1] = 0;
  *param_1 = 0;
  return;
}


// ==== FUN_14008ea50 @ 14008ea50  longlong * FUN_14008ea50(longlong * param_1)

longlong * FUN_14008ea50(longlong *param_1)

{
  FUN_14008e580(param_1);
  return param_1;
}


// ==== FUN_14008ea70 @ 14008ea70  longlong * FUN_14008ea70(longlong * param_1)

longlong * FUN_14008ea70(longlong *param_1)

{
  FUN_14008e4e0(param_1);
  return param_1;
}


// ==== FUN_14008ea90 @ 14008ea90  undefined8 * FUN_14008ea90(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_14008ea90(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_14008ead0 @ 14008ead0  longlong * FUN_14008ead0(longlong * param_1)

longlong * FUN_14008ead0(longlong *param_1)

{
  FUN_14008e610(param_1);
  return param_1;
}


// ==== FUN_14008eaf0 @ 14008eaf0  undefined8 * FUN_14008eaf0(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_14008eaf0(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_14008eb30 @ 14008eb30  undefined8 * FUN_14008eb30(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14008eb30(undefined8 *param_1,undefined8 *param_2,longlong param_3)

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


// ==== FUN_14008eb80 @ 14008eb80  undefined8 * FUN_14008eb80(undefined8 * param_1, undefined8 * param_2, longlong * param_3)

undefined8 * FUN_14008eb80(undefined8 *param_1,undefined8 *param_2,longlong *param_3)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong lVar5;
  longlong *plVar6;
  longlong *plVar7;
  longlong *plVar8;
  longlong *plVar9;
  undefined **local_80 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_68 [40];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_40 [40];
  
  plVar2 = (longlong *)param_3[1];
  if (*(char *)((longlong)plVar2 + 0x29) != '\0') {
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
  FUN_14008e580(param_3);
  plVar8 = (longlong *)*plVar2;
  if (*(char *)((longlong)plVar8 + 0x29) == '\0') {
    plVar9 = plVar8;
    if (*(char *)(plVar2[2] + 0x29) == '\0') {
      plVar7 = (longlong *)param_3[1];
      plVar9 = (longlong *)plVar7[2];
      if (plVar7 != plVar2) {
        plVar8[1] = (longlong)plVar7;
        *plVar7 = *plVar2;
        plVar8 = plVar7;
        if (plVar7 != (longlong *)plVar2[2]) {
          plVar8 = (longlong *)plVar7[1];
          if (*(char *)((longlong)plVar9 + 0x29) == '\0') {
            plVar9[1] = (longlong)plVar8;
          }
          *plVar8 = (longlong)plVar9;
          plVar7[2] = plVar2[2];
          *(longlong **)(plVar2[2] + 8) = plVar7;
        }
        if (*(longlong **)(param_1[6] + 8) == plVar2) {
          *(longlong **)(param_1[6] + 8) = plVar7;
        }
        else {
          puVar4 = (undefined8 *)plVar2[1];
          if ((longlong *)*puVar4 == plVar2) {
            *puVar4 = plVar7;
          }
          else {
            puVar4[2] = plVar7;
          }
        }
        plVar7[1] = plVar2[1];
        plVar3 = plVar2 + 5;
        plVar7 = plVar7 + 5;
        if (plVar7 != plVar3) {
          lVar5 = *plVar7;
          *(char *)plVar7 = (char)*plVar3;
          *(char *)plVar3 = (char)lVar5;
        }
        goto LAB_14008ed6c;
      }
    }
  }
  else {
    plVar9 = (longlong *)plVar2[2];
  }
  plVar8 = (longlong *)plVar2[1];
  if (*(char *)((longlong)plVar9 + 0x29) == '\0') {
    plVar9[1] = (longlong)plVar8;
  }
  if (*(longlong **)(param_1[6] + 8) == plVar2) {
    *(longlong **)(param_1[6] + 8) = plVar9;
  }
  else if ((longlong *)*plVar8 == plVar2) {
    *plVar8 = (longlong)plVar9;
  }
  else {
    plVar8[2] = (longlong)plVar9;
  }
  if (*(longlong **)param_1[6] == plVar2) {
    plVar7 = plVar8;
    if (*(char *)((longlong)plVar9 + 0x29) == '\0') {
      cVar1 = *(char *)(*plVar9 + 0x29);
      plVar3 = (longlong *)*plVar9;
      plVar7 = plVar9;
      while (plVar6 = plVar3, cVar1 == '\0') {
        plVar3 = (longlong *)*plVar6;
        cVar1 = *(char *)((longlong)plVar3 + 0x29);
        plVar7 = plVar6;
      }
    }
    *(longlong **)param_1[6] = plVar7;
  }
  if (*(longlong **)(param_1[6] + 0x10) == plVar2) {
    plVar7 = plVar8;
    if (*(char *)((longlong)plVar9 + 0x29) == '\0') {
      cVar1 = *(char *)(plVar9[2] + 0x29);
      plVar3 = (longlong *)plVar9[2];
      plVar7 = plVar9;
      while (plVar6 = plVar3, cVar1 == '\0') {
        plVar3 = (longlong *)plVar6[2];
        cVar1 = *(char *)((longlong)plVar3 + 0x29);
        plVar7 = plVar6;
      }
    }
    *(longlong **)(param_1[6] + 0x10) = plVar7;
  }
LAB_14008ed6c:
  if ((char)plVar2[5] == '\x01') {
    if (plVar9 != *(longlong **)(param_1[6] + 8)) {
      do {
        plVar7 = plVar8;
        if ((char)plVar9[5] != '\x01') break;
        plVar8 = (longlong *)*plVar7;
        if (plVar9 == plVar8) {
          plVar8 = (longlong *)plVar7[2];
          if ((char)plVar8[5] == '\0') {
            *(undefined1 *)(plVar8 + 5) = 1;
            *(undefined1 *)(plVar7 + 5) = 0;
            FUN_14008e410((longlong)param_1,(longlong)plVar7);
            plVar8 = (longlong *)plVar7[2];
          }
          if (*(char *)((longlong)plVar8 + 0x29) == '\0') {
            if ((*(char *)(*plVar8 + 0x28) != '\x01') || (*(char *)(plVar8[2] + 0x28) != '\x01')) {
              if (*(char *)(plVar8[2] + 0x28) == '\x01') {
                *(undefined1 *)(*plVar8 + 0x28) = 1;
                *(undefined1 *)(plVar8 + 5) = 0;
                FUN_14008dba0((longlong)param_1,plVar8);
                plVar8 = (longlong *)plVar7[2];
              }
              *(char *)(plVar8 + 5) = (char)plVar7[5];
              *(undefined1 *)(plVar7 + 5) = 1;
              *(undefined1 *)(plVar8[2] + 0x28) = 1;
              FUN_14008e410((longlong)param_1,(longlong)plVar7);
              break;
            }
            *(undefined1 *)(plVar8 + 5) = 0;
          }
        }
        else {
          if ((char)plVar8[5] == '\0') {
            *(undefined1 *)(plVar8 + 5) = 1;
            *(undefined1 *)(plVar7 + 5) = 0;
            FUN_14008dba0((longlong)param_1,plVar7);
            plVar8 = (longlong *)*plVar7;
          }
          if (*(char *)((longlong)plVar8 + 0x29) == '\0') {
            if ((*(char *)(plVar8[2] + 0x28) != '\x01') || (*(char *)(*plVar8 + 0x28) != '\x01')) {
              if (*(char *)(*plVar8 + 0x28) == '\x01') {
                *(undefined1 *)(plVar8[2] + 0x28) = 1;
                *(undefined1 *)(plVar8 + 5) = 0;
                FUN_14008e410((longlong)param_1,(longlong)plVar8);
                plVar8 = (longlong *)*plVar7;
              }
              *(char *)(plVar8 + 5) = (char)plVar7[5];
              *(undefined1 *)(plVar7 + 5) = 1;
              *(undefined1 *)(*plVar8 + 0x28) = 1;
              FUN_14008dba0((longlong)param_1,plVar7);
              break;
            }
            *(undefined1 *)(plVar8 + 5) = 0;
          }
        }
        plVar8 = (longlong *)plVar7[1];
        plVar9 = plVar7;
      } while (plVar7 != *(longlong **)(param_1[6] + 8));
    }
    *(undefined1 *)(plVar9 + 5) = 1;
  }
  operator_delete(plVar2);
  if (param_1[7] != 0) {
    param_1[7] = param_1[7] + -1;
  }
  lVar5 = param_3[1];
  *param_2 = *param_1;
  param_2[1] = lVar5;
  return param_2;
}


// ==== FUN_14008ef40 @ 14008ef40  undefined FUN_14008ef40(void)

void FUN_14008ef40(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x30);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = 0;
  }
  if (puVar1 + 1 != (undefined8 *)0x0) {
    puVar1[1] = 0;
  }
  if (puVar1 + 2 != (undefined8 *)0x0) {
    puVar1[2] = 0;
  }
  *(undefined1 *)(puVar1 + 5) = 1;
  *(undefined1 *)((longlong)puVar1 + 0x29) = 0;
  return;
}


// ==== FUN_14008efa0 @ 14008efa0  undefined8 * FUN_14008efa0(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, undefined8 * param_5, undefined1 param_6)

undefined8 *
FUN_14008efa0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             undefined8 *param_5,undefined1 param_6)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x30);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_2;
    puVar1[1] = param_3;
    puVar1[2] = param_4;
    puVar1[3] = *param_5;
    puVar1[4] = param_5[1];
    *(undefined1 *)(puVar1 + 5) = param_6;
    *(undefined1 *)((longlong)puVar1 + 0x29) = 0;
  }
  return puVar1;
}


// ==== FUN_14008f020 @ 14008f020  undefined FUN_14008f020(void)

void FUN_14008f020(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x58);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = 0;
  }
  if (puVar1 + 1 != (undefined8 *)0x0) {
    puVar1[1] = 0;
  }
  if (puVar1 + 2 != (undefined8 *)0x0) {
    puVar1[2] = 0;
  }
  *(undefined1 *)(puVar1 + 10) = 1;
  *(undefined1 *)((longlong)puVar1 + 0x51) = 0;
  return;
}


// ==== FUN_14008f080 @ 14008f080  longlong * FUN_14008f080(longlong * param_1, longlong * param_2)

longlong * FUN_14008f080(longlong *param_1,longlong *param_2)

{
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  FUN_14008e580(param_1);
  return param_2;
}


// ==== FUN_14008f0b0 @ 14008f0b0  longlong * FUN_14008f0b0(longlong * param_1, longlong * param_2)

longlong * FUN_14008f0b0(longlong *param_1,longlong *param_2)

{
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  FUN_14008dd10(param_1);
  return param_2;
}


// ==== FUN_14008f0e0 @ 14008f0e0  longlong * FUN_14008f0e0(longlong * param_1)

longlong * FUN_14008f0e0(longlong *param_1)

{
  FUN_14008e4e0(param_1);
  return param_1;
}


// ==== FUN_14008f100 @ 14008f100  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * FUN_14008f100(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *
FUN_14008f100(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1,
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(param_1,param_2);
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x30) = 0;
  FUN_140081910((undefined8 *)(param_1 + 0x28),*(undefined8 *)(param_2 + 0x28),
                *(longlong *)(param_2 + 0x30));
  return param_1;
}


// ==== FUN_14008f150 @ 14008f150  undefined FUN_14008f150(undefined8 param_1, longlong * param_2)

void FUN_14008f150(undefined8 param_1,longlong *param_2)

{
  char cVar1;
  longlong *plVar2;
  
  cVar1 = *(char *)((longlong)param_2 + 0x29);
  while (cVar1 == '\0') {
    FUN_14008f150(param_1,(longlong *)param_2[2]);
    plVar2 = (longlong *)*param_2;
    operator_delete(param_2);
    param_2 = plVar2;
    cVar1 = *(char *)((longlong)plVar2 + 0x29);
  }
  return;
}


// ==== FUN_14008f1a0 @ 14008f1a0  undefined8 * FUN_14008f1a0(undefined8 * param_1)

undefined8 * FUN_14008f1a0(undefined8 *param_1)

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


// ==== FUN_14008f1f0 @ 14008f1f0  undefined8 * FUN_14008f1f0(undefined8 * param_1)

undefined8 * FUN_14008f1f0(undefined8 *param_1)

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


// ==== FUN_14008f250 @ 14008f250  longlong * FUN_14008f250(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_14008f250(longlong *param_1,longlong *param_2,longlong param_3)

{
  undefined8 *puVar1;
  longlong lVar2;
  longlong lVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  
  lVar2 = *param_1;
  lVar3 = param_1[1];
  if (lVar2 != -4) {
    if (lVar2 == 0) {
      _invalid_parameter_noinfo();
    }
    puVar5 = (undefined8 *)(lVar2 + 8);
    puVar4 = puVar5;
    if (0xf < *(ulonglong *)(lVar2 + 0x20)) {
      puVar4 = (undefined8 *)*puVar5;
    }
    puVar1 = (undefined8 *)(lVar3 + param_3);
    if (puVar1 <= (undefined8 *)((longlong)puVar4 + *(longlong *)(lVar2 + 0x18))) {
      if (0xf < *(ulonglong *)(lVar2 + 0x20)) {
        puVar5 = (undefined8 *)*puVar5;
      }
      if (puVar5 <= puVar1) goto LAB_14008f2cf;
    }
    _invalid_parameter_noinfo();
  }
LAB_14008f2cf:
  *param_2 = lVar2;
  param_2[1] = lVar3 + param_3;
  return param_2;
}


// ==== FUN_14008f310 @ 14008f310  undefined FUN_14008f310(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_1)

void FUN_14008f310(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                   *param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_1 + 0x30);
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
                    /* WARNING: Could not recover jumptable at 0x00014008f36b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(param_1);
  return;
}


// ==== FUN_14008f3a0 @ 14008f3a0  undefined8 * FUN_14008f3a0(undefined8 * param_1)

undefined8 * FUN_14008f3a0(undefined8 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_14008e9c0(param_1);
  return param_1;
}


// ==== FUN_14008f3c0 @ 14008f3c0  undefined FUN_14008f3c0(undefined8 * param_1)

void FUN_14008f3c0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14008f3e0 @ 14008f3e0  undefined FUN_14008f3e0(undefined8 * param_1)

void FUN_14008f3e0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14008f4a0 @ 14008f4a0  undefined8 * FUN_14008f4a0(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_14008f4a0(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_14008f4e0 @ 14008f4e0  longlong * FUN_14008f4e0(longlong * param_1)

longlong * FUN_14008f4e0(longlong *param_1)

{
  FUN_14008e610(param_1);
  return param_1;
}


// ==== FUN_14008f520 @ 14008f520  undefined FUN_14008f520(longlong param_1)

void FUN_14008f520(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = FUN_14008ef40();
  *(longlong *)(param_1 + 0x30) = lVar1;
  *(undefined1 *)(lVar1 + 0x29) = 1;
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)*(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x30);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 0x10) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = 0;
  return;
}


// ==== FUN_14008f560 @ 14008f560  undefined8 * FUN_14008f560(undefined8 * param_1, undefined8 * param_2, char param_3, undefined8 * param_4, undefined8 * param_5)

undefined8 *
FUN_14008f560(undefined8 *param_1,undefined8 *param_2,char param_3,undefined8 *param_4,
             undefined8 *param_5)

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
  
  if (0xffffffffffffffd < (ulonglong)param_1[7]) {
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
  plVar5 = FUN_14008efa0(param_1,param_1[6],param_4,param_1[6],param_5,0);
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
  cVar1 = *(char *)(*plVar7 + 0x28);
  plVar6 = plVar5;
  while (cVar1 == '\0') {
    plVar2 = (longlong *)*plVar7;
    plVar3 = (longlong *)plVar2[1];
    if (plVar2 == (longlong *)*plVar3) {
      lVar4 = plVar3[2];
      if (*(char *)(lVar4 + 0x28) == '\0') {
        *(undefined1 *)(plVar2 + 5) = 1;
        *(undefined1 *)(lVar4 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        plVar6 = *(longlong **)(*plVar7 + 8);
      }
      else {
        if (plVar6 == (longlong *)plVar2[2]) {
          plVar6 = (longlong *)plVar2[2];
          plVar2[2] = *plVar6;
          if (*(char *)(*plVar6 + 0x29) == '\0') {
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
        *(undefined1 *)(*plVar7 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        plVar7 = *(longlong **)(*plVar7 + 8);
        lVar4 = *plVar7;
        *plVar7 = *(longlong *)(lVar4 + 0x10);
        if (*(char *)(*(longlong *)(lVar4 + 0x10) + 0x29) == '\0') {
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
      if (*(char *)(lVar4 + 0x28) == '\0') {
        *(undefined1 *)(plVar2 + 5) = 1;
        *(undefined1 *)(lVar4 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        plVar6 = *(longlong **)(*plVar7 + 8);
      }
      else {
        if (plVar6 == (longlong *)*plVar2) {
          lVar4 = *plVar2;
          *plVar2 = *(longlong *)(lVar4 + 0x10);
          if (*(char *)(*(longlong *)(lVar4 + 0x10) + 0x29) == '\0') {
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
        *(undefined1 *)(*plVar7 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        lVar4 = *(longlong *)(*plVar7 + 8);
        plVar7 = *(longlong **)(lVar4 + 0x10);
        *(longlong *)(lVar4 + 0x10) = *plVar7;
        if (*(char *)(*plVar7 + 0x29) == '\0') {
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
    cVar1 = *(char *)(*plVar7 + 0x28);
  }
  *(undefined1 *)(*(longlong *)(param_1[6] + 8) + 0x28) = 1;
  param_2[1] = plVar5;
  *param_2 = *param_1;
  return param_2;
}


// ==== FUN_14008f8a0 @ 14008f8a0  undefined FUN_14008f8a0(longlong param_1)

void FUN_14008f8a0(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = FUN_14008f020();
  *(longlong *)(param_1 + 0x30) = lVar1;
  *(undefined1 *)(lVar1 + 0x51) = 1;
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)*(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x30);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 0x10) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = 0;
  return;
}


// ==== FUN_14008f8e0 @ 14008f8e0  undefined FUN_14008f8e0(longlong param_1)

void FUN_14008f8e0(longlong param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  
  plVar2 = *(longlong **)(*(longlong *)(param_1 + 0x30) + 8);
  cVar1 = *(char *)((longlong)plVar2 + 0x29);
  while (cVar1 == '\0') {
    FUN_14008f150(param_1,(longlong *)plVar2[2]);
    plVar3 = (longlong *)*plVar2;
    operator_delete(plVar2);
    plVar2 = plVar3;
    cVar1 = *(char *)((longlong)plVar3 + 0x29);
  }
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)*(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x30);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 0x10) = *(longlong *)(param_1 + 0x30);
  return;
}


// ==== FUN_14008f960 @ 14008f960  undefined8 * FUN_14008f960(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14008f960(undefined8 *param_1,undefined8 *param_2,longlong param_3)

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


// ==== FUN_14008f9b0 @ 14008f9b0  undefined8 * FUN_14008f9b0(undefined8 * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_5, undefined1 param_6)

undefined8 *
FUN_14008f9b0(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_5,
             undefined1 param_6)

{
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 3),param_5);
  param_1[8] = 0;
  param_1[9] = 0;
  FUN_140081910(param_1 + 8,*(undefined8 *)(param_5 + 0x28),*(longlong *)(param_5 + 0x30));
  *(undefined1 *)(param_1 + 10) = param_6;
  *(undefined1 *)((longlong)param_1 + 0x51) = 0;
  return param_1;
}


// ==== FUN_14008fa30 @ 14008fa30  undefined8 * FUN_14008fa30(undefined8 * param_1)

undefined8 * FUN_14008fa30(undefined8 *param_1)

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


// ==== FUN_14008fa80 @ 14008fa80  undefined8 * FUN_14008fa80(undefined8 * param_1)

undefined8 * FUN_14008fa80(undefined8 *param_1)

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


// ==== FUN_14008fad0 @ 14008fad0  undefined FUN_14008fad0(longlong param_1)

void FUN_14008fad0(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_1 + 0x48);
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
                    /* WARNING: Could not recover jumptable at 0x00014008fb31. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18));
  return;
}


// ==== FUN_14008fb40 @ 14008fb40  longlong * FUN_14008fb40(longlong * param_1, char * param_2, char * param_3, longlong * param_4, undefined * param_5)

longlong *
FUN_14008fb40(longlong *param_1,char *param_2,char *param_3,longlong *param_4,undefined *param_5)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  
  FUN_14008f250(param_4,param_1,(longlong)param_3 - (longlong)param_2);
  puVar2 = (undefined1 *)param_4[1];
  if (param_2 != param_3) {
    do {
      uVar1 = (*(code *)param_5)((int)*param_2);
      param_2 = param_2 + 1;
      *puVar2 = uVar1;
      puVar2 = puVar2 + 1;
    } while (param_2 != param_3);
  }
  return param_1;
}


// ==== FUN_14008fbc0 @ 14008fbc0  longlong * FUN_14008fbc0(longlong * param_1, longlong * param_2, longlong * param_3)

longlong * FUN_14008fbc0(longlong *param_1,longlong *param_2,longlong *param_3)

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
  if (*(char *)((longlong)puVar4[1] + 0x29) == '\0') {
    puVar1 = (undefined8 *)puVar4[1];
    do {
      if ((longlong)puVar1[3] < *param_3) {
        puVar2 = (undefined8 *)puVar1[2];
      }
      else {
        puVar2 = (undefined8 *)*puVar1;
        puVar4 = puVar1;
      }
      puVar1 = puVar2;
    } while (*(char *)((longlong)puVar2 + 0x29) == '\0');
  }
  puVar1 = (undefined8 *)param_1[6];
  local_20 = puVar4;
  local_28 = *param_1;
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  if ((puVar4 == puVar1) || (*param_3 < (longlong)puVar4[3])) {
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


// ==== FUN_14008fcb0 @ 14008fcb0  undefined FUN_14008fcb0(undefined8 * param_1)

void FUN_14008fcb0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14008fcd0 @ 14008fcd0  undefined FUN_14008fcd0(undefined8 * param_1)

void FUN_14008fcd0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14008fd10 @ 14008fd10  undefined8 * FUN_14008fd10(undefined8 * param_1, undefined8 * param_2, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_3)

undefined8 *
FUN_14008fd10(undefined8 *param_1,undefined8 *param_2,
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_3)

{
  char cVar1;
  undefined8 *puVar2;
  bool bVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  
  puVar5 = (undefined8 *)((undefined8 *)param_1[6])[1];
  cVar1 = *(char *)((longlong)puVar5 + 0x51);
  puVar2 = (undefined8 *)param_1[6];
  while (cVar1 == '\0') {
    bVar3 = std::operator<<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                      ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                        *)(puVar5 + 3),param_3);
    if (bVar3) {
      puVar4 = (undefined8 *)puVar5[2];
      puVar5 = puVar2;
    }
    else {
      puVar4 = (undefined8 *)*puVar5;
    }
    puVar2 = puVar5;
    puVar5 = puVar4;
    cVar1 = *(char *)((longlong)puVar4 + 0x51);
  }
  *param_2 = *param_1;
  param_2[1] = puVar2;
  return param_2;
}


// ==== FUN_14008fd90 @ 14008fd90  longlong * FUN_14008fd90(longlong * param_1, longlong * param_2, longlong * param_3)

longlong * FUN_14008fd90(longlong *param_1,longlong *param_2,longlong *param_3)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *plVar4;
  longlong *plVar5;
  longlong *plVar6;
  bool bVar7;
  longlong local_38;
  longlong *local_30;
  
  plVar6 = (longlong *)param_1[6];
  bVar7 = true;
  if (*(char *)(plVar6[1] + 0x29) == '\0') {
    plVar5 = (longlong *)plVar6[1];
    do {
      plVar6 = plVar5;
      bVar7 = *param_3 < plVar6[3];
      if (bVar7) {
        plVar5 = (longlong *)*plVar6;
      }
      else {
        plVar5 = (longlong *)plVar6[2];
      }
    } while (*(char *)((longlong)plVar5 + 0x29) == '\0');
  }
  lVar2 = *param_1;
  plVar5 = plVar6;
  local_38 = lVar2;
  plVar4 = plVar6;
  if (bVar7 == false) {
LAB_14008feed:
    local_30 = plVar4;
    if (*param_3 <= plVar5[3]) {
      *(undefined1 *)(param_2 + 2) = 0;
      *param_2 = local_38;
      goto LAB_14008ff1d;
    }
  }
  else {
    plVar5 = *(longlong **)param_1[6];
    local_30 = plVar6;
    if (lVar2 == 0) {
      _invalid_parameter_noinfo();
    }
    if (plVar6 != plVar5) {
      if (lVar2 == 0) {
        _invalid_parameter_noinfo();
      }
      if (*(char *)((longlong)plVar6 + 0x29) == '\0') {
        plVar5 = (longlong *)*plVar6;
        if (*(char *)((longlong)plVar5 + 0x29) == '\0') {
          cVar1 = *(char *)(plVar5[2] + 0x29);
          plVar3 = (longlong *)plVar5[2];
          while (plVar4 = plVar5, cVar1 == '\0') {
            cVar1 = *(char *)(plVar3[2] + 0x29);
            plVar5 = plVar3;
            plVar3 = (longlong *)plVar3[2];
          }
        }
        else {
          cVar1 = *(char *)(plVar6[1] + 0x29);
          plVar4 = (longlong *)plVar6[1];
          plVar3 = plVar6;
          while ((plVar5 = plVar4, cVar1 == '\0' && (plVar3 == (longlong *)*plVar5))) {
            cVar1 = *(char *)(plVar5[1] + 0x29);
            plVar4 = (longlong *)plVar5[1];
            plVar3 = plVar5;
            local_30 = plVar5;
          }
          plVar4 = plVar5;
          if (*(char *)((longlong)plVar3 + 0x29) != '\0') {
            _invalid_parameter_noinfo();
            plVar5 = plVar3;
            plVar4 = local_30;
          }
        }
      }
      else {
        plVar5 = (longlong *)plVar6[2];
        plVar4 = plVar5;
        if (*(char *)((longlong)plVar5 + 0x29) != '\0') {
          local_30 = plVar5;
          _invalid_parameter_noinfo();
          plVar4 = local_30;
        }
      }
      goto LAB_14008feed;
    }
    bVar7 = true;
  }
  plVar6 = FUN_14008f560(param_1,&local_38,bVar7,plVar6,param_3);
  *(undefined1 *)(param_2 + 2) = 1;
  local_30 = (longlong *)plVar6[1];
  *param_2 = *plVar6;
LAB_14008ff1d:
  param_2[1] = (longlong)local_30;
  return param_2;
}


// ==== FUN_14008ff40 @ 14008ff40  longlong * FUN_14008ff40(longlong * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_14008ff40(longlong *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  char cVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong local_28;
  longlong lStack_20;
  undefined8 local_18 [2];
  
  lVar2 = *(longlong *)param_1[6];
  if ((*param_3 == 0) || (*param_3 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (param_3[1] == lVar2) {
    lVar2 = param_1[6];
    if ((*param_4 == 0) || (*param_4 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    if (param_4[1] == lVar2) {
      FUN_14008f8e0((longlong)param_1);
      param_2[1] = *(longlong *)param_1[6];
      *param_2 = *param_1;
      return param_2;
    }
  }
  while( true ) {
    if ((*param_3 == 0) || (*param_3 != *param_4)) {
      _invalid_parameter_noinfo();
    }
    lVar2 = *param_3;
    if (param_3[1] == param_4[1]) break;
    lVar3 = param_3[1];
    if (*param_3 == 0) {
      _invalid_parameter_noinfo();
    }
    lVar4 = param_3[1];
    if (*(char *)(lVar4 + 0x29) == '\0') {
      plVar6 = *(longlong **)(lVar4 + 0x10);
      if (*(char *)((longlong)plVar6 + 0x29) == '\0') {
        cVar1 = *(char *)(*plVar6 + 0x29);
        plVar5 = (longlong *)*plVar6;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar5 + 0x29);
          plVar6 = plVar5;
          plVar5 = (longlong *)*plVar5;
        }
      }
      else {
        plVar6 = *(longlong **)(lVar4 + 8);
        cVar1 = *(char *)((longlong)plVar6 + 0x29);
        while ((cVar1 == '\0' && (param_3[1] == plVar6[2]))) {
          param_3[1] = (longlong)plVar6;
          plVar6 = (longlong *)plVar6[1];
          cVar1 = *(char *)((longlong)plVar6 + 0x29);
        }
      }
      param_3[1] = (longlong)plVar6;
    }
    else {
      _invalid_parameter_noinfo();
    }
    local_28 = lVar2;
    lStack_20 = lVar3;
    FUN_14008eb80(param_1,local_18,&local_28);
  }
  lVar2 = param_3[1];
  *param_2 = *param_1;
  param_2[1] = lVar2;
  return param_2;
}


// ==== FUN_1400900f0 @ 1400900f0  undefined8 * FUN_1400900f0(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_5, undefined1 param_6)

undefined8 *
FUN_1400900f0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_5,
             undefined1 param_6)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x58);
  if (puVar1 != (undefined8 *)0x0) {
    FUN_14008f9b0(puVar1,param_2,param_3,param_4,param_5,param_6);
  }
  return puVar1;
}


// ==== FUN_140090180 @ 140090180  undefined8 * FUN_140090180(undefined8 * param_1)

undefined8 * FUN_140090180(undefined8 *param_1)

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


// ==== FUN_1400901d0 @ 1400901d0  undefined8 * FUN_1400901d0(undefined8 * param_1)

undefined8 * FUN_1400901d0(undefined8 *param_1)

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


// ==== FUN_140090220 @ 140090220  longlong * FUN_140090220(longlong * param_1, longlong param_2, longlong param_3, longlong * param_4, undefined * param_5)

longlong *
FUN_140090220(longlong *param_1,longlong param_2,longlong param_3,longlong *param_4,
             undefined *param_5)

{
  char *pcVar1;
  char cVar2;
  char *pcVar3;
  longlong lVar4;
  longlong local_18;
  longlong local_10;
  
  local_18 = *param_4;
  pcVar1 = *(char **)(param_3 + 8);
  pcVar3 = *(char **)(param_2 + 8);
  local_10 = param_4[1];
  FUN_14008f250(&local_18,param_1,(longlong)pcVar1 - (longlong)pcVar3);
  if (pcVar3 != pcVar1) {
    lVar4 = local_10 - (longlong)pcVar3;
    do {
      cVar2 = (*(code *)param_5)((int)*pcVar3);
      pcVar3 = pcVar3 + 1;
      pcVar3[lVar4 + -1] = cVar2;
    } while (pcVar3 != pcVar1);
  }
  return param_1;
}


// ==== FUN_1400902b0 @ 1400902b0  void * FUN_1400902b0(void * param_1, uint param_2)

void * FUN_1400902b0(void *param_1,uint param_2)

{
  FUN_14008fad0((longlong)param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_1400902e0 @ 1400902e0  ushort FUN_1400902e0(int * param_1, int param_2, int param_3)

ushort FUN_1400902e0(int *param_1,int param_2,int param_3)

{
  longlong *plVar1;
  int *piVar2;
  ushort *puVar3;
  longlong *plVar4;
  undefined2 *puVar5;
  undefined2 uVar6;
  ushort uVar7;
  int iVar8;
  undefined6 extraout_var;
  undefined8 *puVar9;
  
  puVar3 = (ushort *)(*(longlong *)(param_1 + 4) + (longlong)(*param_1 * param_3 + param_2) * 4);
  uVar6 = FUN_1400967a0((longlong)puVar3);
  iVar8 = (int)CONCAT62(extraout_var,uVar6);
  if (iVar8 == 0xffff) {
    uVar7 = FUN_140096790(puVar3);
  }
  else {
    if ((ulonglong)((*(longlong *)(param_1 + 0x1e) - *(longlong *)(param_1 + 0x1c)) / 0x30) <=
        (ulonglong)(longlong)iVar8) {
      _invalid_parameter_noinfo();
    }
    puVar9 = (undefined8 *)
             FUN_140083f00((longlong *)((longlong)iVar8 * 0x30 + *(longlong *)(param_1 + 0x1c)));
    plVar4 = (longlong *)puVar9[1];
    puVar5 = (undefined2 *)*puVar9;
    if (plVar4 != (longlong *)0x0) {
      LOCK();
      *(int *)(plVar4 + 2) = (int)plVar4[2] + 1;
      UNLOCK();
    }
    uVar7 = FUN_140093910(puVar5);
    if (plVar4 != (longlong *)0x0) {
      LOCK();
      plVar1 = plVar4 + 2;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)*plVar1 == 0) {
        (**(code **)*plVar4)(plVar4);
        LOCK();
        piVar2 = (int *)((longlong)plVar4 + 0x14);
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (*piVar2 == 0) {
          (**(code **)(*plVar4 + 8))(plVar4);
        }
      }
    }
  }
  return uVar7;
}


// ==== FUN_1400903e0 @ 1400903e0  undefined2 FUN_1400903e0(int * param_1, int param_2, int param_3)

undefined2 FUN_1400903e0(int *param_1,int param_2,int param_3)

{
  int *piVar1;
  longlong *plVar2;
  longlong lVar3;
  undefined2 uVar4;
  int iVar5;
  undefined6 extraout_var;
  longlong *plVar6;
  
  uVar4 = FUN_1400967a0(*(longlong *)(param_1 + 4) + (longlong)(*param_1 * param_3 + param_2) * 4);
  iVar5 = (int)CONCAT62(extraout_var,uVar4);
  if (iVar5 == 0xffff) {
    uVar4 = 0;
  }
  else {
    if ((ulonglong)((*(longlong *)(param_1 + 0x1e) - *(longlong *)(param_1 + 0x1c)) / 0x30) <=
        (ulonglong)(longlong)iVar5) {
      _invalid_parameter_noinfo();
    }
    plVar6 = (longlong *)
             FUN_140083f00((longlong *)((longlong)iVar5 * 0x30 + *(longlong *)(param_1 + 0x1c)));
    plVar2 = (longlong *)plVar6[1];
    lVar3 = *plVar6;
    if (plVar2 != (longlong *)0x0) {
      LOCK();
      *(int *)(plVar2 + 2) = (int)plVar2[2] + 1;
      UNLOCK();
    }
    uVar4 = FUN_140093930(lVar3);
    if (plVar2 != (longlong *)0x0) {
      LOCK();
      plVar6 = plVar2 + 2;
      *(int *)plVar6 = (int)*plVar6 + -1;
      UNLOCK();
      if ((int)*plVar6 == 0) {
        (**(code **)*plVar2)(plVar2);
        LOCK();
        piVar1 = (int *)((longlong)plVar2 + 0x14);
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (*piVar1 == 0) {
          (**(code **)(*plVar2 + 8))(plVar2);
        }
      }
    }
  }
  return uVar4;
}


// ==== FUN_1400904d0 @ 1400904d0  ushort FUN_1400904d0(int * param_1, int param_2, int param_3)

ushort FUN_1400904d0(int *param_1,int param_2,int param_3)

{
  int *piVar1;
  byte *pbVar2;
  longlong *plVar3;
  longlong lVar4;
  bool bVar5;
  undefined2 uVar6;
  ushort uVar7;
  int iVar8;
  undefined6 extraout_var;
  longlong *plVar9;
  
  pbVar2 = (byte *)(*(longlong *)(param_1 + 4) + (longlong)(*param_1 * param_3 + param_2) * 4);
  uVar6 = FUN_1400967a0((longlong)pbVar2);
  iVar8 = (int)CONCAT62(extraout_var,uVar6);
  if (iVar8 == 0xffff) {
    bVar5 = FUN_1400967b0(pbVar2);
    uVar7 = (ushort)bVar5;
  }
  else {
    if ((ulonglong)((*(longlong *)(param_1 + 0x1e) - *(longlong *)(param_1 + 0x1c)) / 0x30) <=
        (ulonglong)(longlong)iVar8) {
      _invalid_parameter_noinfo();
    }
    plVar9 = (longlong *)
             FUN_140083f00((longlong *)((longlong)iVar8 * 0x30 + *(longlong *)(param_1 + 0x1c)));
    plVar3 = (longlong *)plVar9[1];
    lVar4 = *plVar9;
    if (plVar3 != (longlong *)0x0) {
      LOCK();
      *(int *)(plVar3 + 2) = (int)plVar3[2] + 1;
      UNLOCK();
    }
    uVar7 = FUN_140093920(lVar4);
    if (plVar3 != (longlong *)0x0) {
      LOCK();
      plVar9 = plVar3 + 2;
      *(int *)plVar9 = (int)*plVar9 + -1;
      UNLOCK();
      if ((int)*plVar9 == 0) {
        (**(code **)*plVar3)(plVar3);
        LOCK();
        piVar1 = (int *)((longlong)plVar3 + 0x14);
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (*piVar1 == 0) {
          (**(code **)(*plVar3 + 8))(plVar3);
        }
      }
    }
  }
  return uVar7;
}


// ==== FUN_1400905d0 @ 1400905d0  undefined4 FUN_1400905d0(longlong param_1, int param_2, int param_3)

undefined4 FUN_1400905d0(longlong param_1,int param_2,int param_3)

{
  char cVar1;
  longlong *plVar2;
  undefined8 *puVar3;
  longlong lVar4;
  undefined4 uVar5;
  undefined8 *puVar6;
  longlong *plVar7;
  undefined8 *puVar8;
  ulonglong uVar9;
  longlong lVar10;
  longlong local_38;
  undefined8 *local_30;
  longlong local_28;
  undefined8 local_20;
  longlong *local_18;
  longlong local_10;
  
  uVar9 = (longlong)param_3 << 0x20 | (longlong)param_2;
  puVar8 = (undefined8 *)(*(undefined8 **)(param_1 + 0x48))[1];
  cVar1 = *(char *)((longlong)puVar8 + 0x29);
  puVar3 = *(undefined8 **)(param_1 + 0x48);
  while (cVar1 == '\0') {
    if ((longlong)puVar8[3] < (longlong)uVar9) {
      puVar6 = (undefined8 *)puVar8[2];
      puVar8 = puVar3;
    }
    else {
      puVar6 = (undefined8 *)*puVar8;
    }
    puVar3 = puVar8;
    puVar8 = puVar6;
    cVar1 = *(char *)((longlong)puVar6 + 0x29);
  }
  puVar8 = *(undefined8 **)(param_1 + 0x48);
  local_30 = puVar3;
  local_38 = *(longlong *)(param_1 + 0x18);
  if (*(longlong *)(param_1 + 0x18) == 0) {
    _invalid_parameter_noinfo();
  }
  if ((puVar3 == puVar8) || ((longlong)uVar9 < (longlong)puVar3[3])) {
    plVar7 = &local_28;
    local_20 = *(undefined8 *)(param_1 + 0x48);
    local_28 = *(longlong *)(param_1 + 0x18);
  }
  else {
    plVar7 = &local_38;
  }
  plVar2 = (longlong *)*plVar7;
  lVar10 = *(longlong *)(param_1 + 0x48);
  local_18 = plVar2;
  local_10 = plVar7[1];
  if ((plVar2 == (longlong *)0x0) || (plVar2 != *(longlong **)(param_1 + 0x18))) {
    _invalid_parameter_noinfo();
  }
  lVar4 = local_10;
  if (local_10 == lVar10) {
    uVar5 = 0xffffffff;
  }
  else {
    if (plVar2 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar10 = 0;
    }
    else {
      lVar10 = *plVar2;
    }
    if (lVar4 == *(longlong *)(lVar10 + 0x30)) {
      _invalid_parameter_noinfo();
    }
    uVar5 = *(undefined4 *)(lVar4 + 0x20);
  }
  return uVar5;
}


// ==== FUN_1400906e0 @ 1400906e0  undefined8 FUN_1400906e0(longlong param_1, int param_2, int param_3)

longlong FUN_1400906e0(longlong param_1,int param_2,int param_3)

{
  char cVar1;
  undefined8 *puVar2;
  longlong lVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  longlong extraout_RAX;
  longlong lVar6;
  uint7 uVar7;
  longlong *plVar8;
  undefined8 *puVar9;
  longlong lVar10;
  ulonglong uVar11;
  int local_a8 [10];
  int local_80 [10];
  longlong local_58;
  undefined8 *local_50;
  longlong local_48;
  undefined8 local_40;
  longlong local_38;
  undefined8 *local_30;
  
  lVar10 = 0;
  local_a8[1] = 1;
  local_a8[2] = 0xffffffff;
  local_a8[3] = 1;
  local_a8[0] = 0;
  local_a8[4] = 0;
  local_a8[8] = 0;
  local_80[0] = 0;
  local_80[3] = 0;
  local_80[7] = 0;
  local_a8[5] = 1;
  local_a8[6] = 0xffffffff;
  local_a8[7] = 0xffffffff;
  local_80[1] = 1;
  local_80[2] = 0xffffffff;
  local_80[4] = 1;
  local_80[5] = 0xffffffff;
  local_80[6] = 1;
  local_80[8] = 0xffffffff;
  while( true ) {
    puVar2 = *(undefined8 **)(param_1 + 0x48);
    lVar3 = *(longlong *)(param_1 + 0x18);
    uVar11 = (longlong)(*(int *)((longlong)local_80 + lVar10) + param_3) << 0x20 |
             (longlong)(*(int *)((longlong)local_a8 + lVar10) + param_2);
    cVar1 = *(char *)((longlong)puVar2[1] + 0x29);
    puVar4 = puVar2;
    puVar9 = (undefined8 *)puVar2[1];
    while (cVar1 == '\0') {
      if ((longlong)puVar9[3] < (longlong)uVar11) {
        puVar5 = (undefined8 *)puVar9[2];
        puVar9 = puVar4;
      }
      else {
        puVar5 = (undefined8 *)*puVar9;
      }
      puVar4 = puVar9;
      puVar9 = puVar5;
      cVar1 = *(char *)((longlong)puVar5 + 0x29);
    }
    local_30 = puVar4;
    local_38 = lVar3;
    if (lVar3 == 0) {
      _invalid_parameter_noinfo();
    }
    if ((puVar4 == puVar2) || ((longlong)uVar11 < (longlong)puVar4[3])) {
      plVar8 = &local_48;
      local_40 = *(undefined8 *)(param_1 + 0x48);
      local_48 = *(longlong *)(param_1 + 0x18);
    }
    else {
      plVar8 = &local_38;
    }
    lVar6 = *plVar8;
    local_50 = (undefined8 *)plVar8[1];
    local_58 = lVar6;
    if ((lVar6 == 0) || (lVar6 != lVar3)) {
      _invalid_parameter_noinfo();
      lVar6 = extraout_RAX;
    }
    uVar7 = (uint7)((ulonglong)lVar6 >> 8);
    if (local_50 != puVar2) break;
    lVar10 = lVar10 + 4;
    if (0x23 < lVar10) {
      return (ulonglong)uVar7 << 8;
    }
  }
  return CONCAT71(uVar7,1);
}


// ==== FUN_140090890 @ 140090890  undefined FUN_140090890(int * param_1, char * param_2, int param_3)

void FUN_140090890(int *param_1,char *param_2,int param_3)

{
  longlong *plVar1;
  int *piVar2;
  longlong lVar3;
  longlong *plVar4;
  int iVar5;
  FILE *_File;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined1 auStackY_398 [32];
  int local_368;
  int local_364;
  char local_360 [8];
  undefined8 local_358;
  longlong *local_350;
  undefined8 local_348;
  char local_338;
  undefined1 local_337 [255];
  char local_238;
  undefined1 local_237 [255];
  char local_138;
  undefined1 local_137 [255];
  ulonglong local_38;
  
  local_348 = 0xfffffffffffffffe;
  local_38 = DAT_140103510 ^ (ulonglong)auStackY_398;
  _File = fopen(param_2,"rb");
  if (_File == (FILE *)0x0) {
    log_InlineLogERROR("CMapStaticData cannot open puzzle file %s");
  }
  else {
    iVar10 = 0;
    local_358 = 0;
    local_350 = (longlong *)0x0;
    FUN_14004f180(&local_358,_File,fclose_exref);
    local_368 = 0;
    local_364 = 0;
    local_360[0] = '\0';
    local_360[1] = '\0';
    local_360[2] = '\0';
    local_138 = '\0';
    memset(local_137,0,0xff);
    local_238 = '\0';
    memset(local_237,0,0xff);
    local_338 = '\0';
    memset(local_337,0,0xff);
    _splitpath(param_2,local_360,&local_138,&local_238,&local_338);
    iVar5 = _stricmp(&local_338,".PUX");
    if (iVar5 == 0) {
      fseek(_File,0x14,0);
      fread(&local_368,4,1,_File);
      fread(&local_364,4,1,_File);
    }
    else {
      fseek(_File,0x108,0);
      fread(&local_368,4,1,_File);
      fread(&local_364,4,1,_File);
    }
    local_368 = (int)(local_368 * param_3 + (local_368 * param_3 >> 0x1f & 0x3fU)) >> 6;
    local_364 = (int)(local_364 * param_3 + (local_364 * param_3 >> 0x1f & 0x1fU)) >> 5;
    iVar8 = (*param_1 / 2 - local_364) / 2 + local_368 / 2;
    iVar9 = (*param_1 / 2 - local_368) / 2 + local_364 / 2;
    iVar5 = iVar8;
    iVar6 = iVar10;
    if (0 < iVar8) {
      do {
        iVar7 = iVar10;
        if (0 < iVar5) {
          do {
            FUN_1400967d0((ushort *)
                          (*(longlong *)(param_1 + 4) + (longlong)(*param_1 * iVar6 + iVar7) * 4));
            FUN_1400967d0((ushort *)
                          (*(longlong *)(param_1 + 4) +
                          (longlong)(((param_1[1] - iVar6) * *param_1 - iVar7) + -1) * 4));
            iVar7 = iVar7 + 1;
          } while (iVar7 < iVar5);
        }
        iVar6 = iVar6 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar6 < iVar8);
    }
    iVar5 = iVar9;
    iVar6 = iVar10;
    if (0 < iVar9) {
      do {
        iVar8 = iVar10;
        if (0 < iVar5) {
          do {
            FUN_1400967d0((ushort *)
                          (*(longlong *)(param_1 + 4) +
                          (longlong)(((param_1[1] - iVar6) + -1) * *param_1 + iVar8) * 4));
            FUN_1400967d0((ushort *)
                          (*(longlong *)(param_1 + 4) +
                          (longlong)(((iVar6 + 1) * *param_1 - iVar8) + -1) * 4));
            iVar8 = iVar8 + 1;
          } while (iVar8 < iVar5);
        }
        iVar6 = iVar6 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar6 < iVar9);
    }
    plVar4 = local_350;
    if (local_350 != (longlong *)0x0) {
      LOCK();
      plVar1 = local_350 + 2;
      lVar3 = *plVar1;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)lVar3 == 1) {
        (**(code **)*local_350)(local_350);
        LOCK();
        piVar2 = (int *)((longlong)plVar4 + 0x14);
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (*piVar2 == 0) {
          (**(code **)(*local_350 + 8))();
        }
      }
    }
  }
  __security_check_cookie(local_38 ^ (ulonglong)auStackY_398);
  return;
}


// ==== FUN_140090bd0 @ 140090bd0  longlong * FUN_140090bd0(longlong * param_1, longlong * param_2, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_3)

longlong *
FUN_140090bd0(longlong *param_1,longlong *param_2,
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_3)

{
  char cVar1;
  undefined8 *puVar2;
  bool bVar3;
  longlong *plVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  longlong local_28;
  undefined8 *local_20;
  longlong local_18;
  longlong local_10;
  
  puVar6 = (undefined8 *)((undefined8 *)param_1[6])[1];
  cVar1 = *(char *)((longlong)puVar6 + 0x51);
  puVar2 = (undefined8 *)param_1[6];
  while (cVar1 == '\0') {
    bVar3 = std::operator<<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                      ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                        *)(puVar6 + 3),param_3);
    if (bVar3) {
      puVar5 = (undefined8 *)puVar6[2];
      puVar6 = puVar2;
    }
    else {
      puVar5 = (undefined8 *)*puVar6;
    }
    puVar2 = puVar6;
    puVar6 = puVar5;
    cVar1 = *(char *)((longlong)puVar5 + 0x51);
  }
  puVar6 = (undefined8 *)param_1[6];
  local_20 = puVar2;
  local_28 = *param_1;
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  if ((puVar2 == puVar6) ||
     (bVar3 = std::operator<<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                        (param_3,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                  *)(puVar2 + 3)), bVar3)) {
    plVar4 = &local_18;
    local_10 = param_1[6];
    local_18 = *param_1;
  }
  else {
    plVar4 = &local_28;
  }
  *param_2 = *plVar4;
  param_2[1] = plVar4[1];
  return param_2;
}


// ==== FUN_140090cb0 @ 140090cb0  undefined FUN_140090cb0(undefined8 * param_1)

void FUN_140090cb0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140090cd0 @ 140090cd0  undefined FUN_140090cd0(undefined8 * param_1)

void FUN_140090cd0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140090cf0 @ 140090cf0  longlong * FUN_140090cf0(longlong * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_140090cf0(longlong *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  char cVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  longlong *plVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong lVar7;
  longlong *plVar8;
  longlong local_38;
  longlong *local_30;
  
  if (param_1[7] == 0) {
    FUN_14008f560(param_1,param_2,'\x01',(undefined8 *)param_1[6],param_4);
  }
  else {
    puVar2 = *(undefined8 **)param_1[6];
    if ((*param_3 == 0) || (*param_3 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    puVar3 = (undefined8 *)param_3[1];
    if (puVar3 == puVar2) {
      if (*param_4 < (longlong)puVar3[3]) {
        FUN_14008f560(param_1,param_2,'\x01',puVar3,param_4);
        return param_2;
      }
    }
    else {
      lVar7 = param_1[6];
      if ((*param_3 == 0) || (*param_3 != *param_1)) {
        _invalid_parameter_noinfo();
      }
      if (param_3[1] == lVar7) {
        if ((longlong)(*(undefined8 **)(param_1[6] + 0x10))[3] < *param_4) {
          FUN_14008f560(param_1,param_2,'\0',*(undefined8 **)(param_1[6] + 0x10),param_4);
          return param_2;
        }
      }
      else {
        lVar7 = *param_4;
        if (lVar7 < *(longlong *)(param_3[1] + 0x18)) {
          local_38 = *param_3;
          local_30 = (longlong *)param_3[1];
          if (local_38 == 0) {
            _invalid_parameter_noinfo();
          }
          if (*(char *)((longlong)local_30 + 0x29) == '\0') {
            plVar6 = (longlong *)*local_30;
            if (*(char *)((longlong)plVar6 + 0x29) == '\0') {
              cVar1 = *(char *)(plVar6[2] + 0x29);
              plVar8 = (longlong *)plVar6[2];
              while (local_30 = plVar6, cVar1 == '\0') {
                cVar1 = *(char *)(plVar8[2] + 0x29);
                plVar6 = plVar8;
                plVar8 = (longlong *)plVar8[2];
              }
            }
            else {
              cVar1 = *(char *)(local_30[1] + 0x29);
              plVar4 = (longlong *)local_30[1];
              plVar8 = local_30;
              while ((plVar6 = plVar4, cVar1 == '\0' && (plVar8 == (longlong *)*plVar6))) {
                cVar1 = *(char *)(plVar6[1] + 0x29);
                plVar4 = (longlong *)plVar6[1];
                plVar8 = plVar6;
              }
              local_30 = plVar6;
              if (*(char *)((longlong)plVar8 + 0x29) != '\0') {
                local_30 = plVar8;
                _invalid_parameter_noinfo();
                plVar6 = plVar8;
              }
            }
          }
          else {
            plVar6 = (longlong *)local_30[2];
            local_30 = plVar6;
            if (*(char *)((longlong)plVar6 + 0x29) != '\0') {
              _invalid_parameter_noinfo();
            }
          }
          lVar7 = *param_4;
          if (plVar6[3] < lVar7) {
            if (*(char *)(plVar6[2] + 0x29) != '\0') {
              FUN_14008f560(param_1,param_2,'\0',plVar6,param_4);
              return param_2;
            }
            FUN_14008f560(param_1,param_2,'\x01',(undefined8 *)param_3[1],param_4);
            return param_2;
          }
        }
        if (*(longlong *)(param_3[1] + 0x18) < lVar7) {
          local_38 = *param_3;
          plVar6 = (longlong *)param_1[6];
          local_30 = (longlong *)param_3[1];
          lVar7 = *param_1;
          if (local_38 == 0) {
            _invalid_parameter_noinfo();
          }
          plVar8 = local_30;
          if (*(char *)((longlong)local_30 + 0x29) == '\0') {
            plVar8 = (longlong *)local_30[2];
            if (*(char *)((longlong)plVar8 + 0x29) == '\0') {
              cVar1 = *(char *)(*plVar8 + 0x29);
              plVar4 = (longlong *)*plVar8;
              while (cVar1 == '\0') {
                cVar1 = *(char *)(*plVar4 + 0x29);
                plVar8 = plVar4;
                plVar4 = (longlong *)*plVar4;
              }
            }
            else {
              cVar1 = *(char *)(local_30[1] + 0x29);
              plVar5 = (longlong *)local_30[1];
              plVar4 = local_30;
              while ((plVar8 = plVar5, cVar1 == '\0' && (plVar4 == (longlong *)plVar8[2]))) {
                cVar1 = *(char *)(plVar8[1] + 0x29);
                plVar5 = (longlong *)plVar8[1];
                plVar4 = plVar8;
              }
            }
          }
          else {
            _invalid_parameter_noinfo();
          }
          if ((local_38 == 0) || (local_38 != lVar7)) {
            _invalid_parameter_noinfo();
          }
          if ((plVar8 == plVar6) || (*param_4 < plVar8[3])) {
            if (*(char *)(((undefined8 *)param_3[1])[2] + 0x29) != '\0') {
              FUN_14008f560(param_1,param_2,'\0',(undefined8 *)param_3[1],param_4);
              return param_2;
            }
            FUN_14008f560(param_1,param_2,'\x01',plVar8,param_4);
            return param_2;
          }
        }
      }
    }
    plVar6 = FUN_14008fd90(param_1,&local_38,param_4);
    *param_2 = *plVar6;
    param_2[1] = plVar6[1];
  }
  return param_2;
}


// ==== FUN_140091020 @ 140091020  undefined FUN_140091020(longlong * param_1)

void FUN_140091020(longlong *param_1)

{
  longlong local_38;
  undefined8 *puStack_30;
  longlong local_28;
  undefined8 uStack_20;
  longlong local_18 [2];
  
  local_38 = *param_1;
  puStack_30 = (undefined8 *)param_1[6];
  uStack_20 = *puStack_30;
  local_28 = local_38;
  FUN_14008ff40(param_1,local_18,&local_28,&local_38);
  operator_delete((void *)param_1[6]);
  param_1[6] = 0;
  param_1[7] = 0;
  return;
}


