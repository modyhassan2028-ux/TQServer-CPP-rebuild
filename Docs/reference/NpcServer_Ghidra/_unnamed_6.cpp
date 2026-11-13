// NpcServer.exe :: _unnamed  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== FUN_14006e4f0 @ 14006e4f0  undefined FUN_14006e4f0(ulonglong param_1)

void FUN_14006e4f0(ulonglong param_1)

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


// ==== FUN_14006e580 @ 14006e580  undefined FUN_14006e580(ulonglong param_1)

void FUN_14006e580(ulonglong param_1)

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


// ==== FUN_14006e630 @ 14006e630  void * FUN_14006e630(void * param_1, longlong param_2, void * param_3)

void * FUN_14006e630(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14006e6a0 @ 14006e6a0  void * FUN_14006e6a0(void * param_1, longlong param_2, void * param_3)

void * FUN_14006e6a0(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14006e730 @ 14006e730  longlong * FUN_14006e730(longlong * param_1, longlong param_2)

longlong * FUN_14006e730(longlong *param_1,longlong param_2)

{
  FUN_14006e280(param_1,-param_2);
  return param_1;
}


// ==== FUN_14006e780 @ 14006e780  void * FUN_14006e780(void * param_1, longlong param_2, longlong param_3)

void * FUN_14006e780(void *param_1,longlong param_2,longlong param_3)

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


// ==== FUN_14006e7c0 @ 14006e7c0  longlong FUN_14006e7c0(longlong * param_1)

longlong FUN_14006e7c0(longlong *param_1)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  ulonglong uVar6;
  
  uVar1 = param_1[1];
  plVar2 = (longlong *)*param_1;
  lVar5 = 0;
  uVar6 = uVar1 >> 1;
  lVar3 = lVar5;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar2 = (longlong *)*param_1;
    lVar4 = lVar5;
    if (plVar2 == (longlong *)0x0) goto LAB_14006e80f;
  }
  lVar4 = *plVar2;
  if (plVar2 != (longlong *)0x0) {
    lVar3 = lVar4;
  }
LAB_14006e80f:
  if ((ulonglong)(*(longlong *)(lVar3 + 0x38) + *(longlong *)(lVar4 + 0x30)) <=
      (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)*param_1;
  lVar3 = lVar5;
  if (plVar2 != (longlong *)0x0) {
    lVar3 = *plVar2;
  }
  if (*(ulonglong *)(lVar3 + 0x28) <= uVar6) {
    lVar3 = lVar5;
    if (plVar2 != (longlong *)0x0) {
      lVar3 = *plVar2;
    }
    uVar6 = uVar6 - *(longlong *)(lVar3 + 0x28);
  }
  if (plVar2 != (longlong *)0x0) {
    lVar5 = *plVar2;
  }
  return *(longlong *)(*(longlong *)(lVar5 + 0x20) + uVar6 * 8) + (ulonglong)((uint)uVar1 & 1) * 8;
}


// ==== FUN_14006e930 @ 14006e930  void * FUN_14006e930(void * param_1, longlong param_2, void * param_3)

void * FUN_14006e930(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14006e9b0 @ 14006e9b0  undefined8 FUN_14006e9b0(int param_1)

undefined8 FUN_14006e9b0(int param_1)

{
  ulonglong uVar1;
  
  if (-1 < param_1) {
    uVar1 = DAT_140104698 - DAT_140104690 >> 3;
    if (param_1 < (int)uVar1) {
      if (uVar1 <= (ulonglong)(longlong)param_1) {
        _invalid_parameter_noinfo();
      }
      return *(undefined8 *)(DAT_140104690 + (longlong)param_1 * 8);
    }
  }
  return 0;
}


// ==== FUN_14006ea00 @ 14006ea00  undefined8 FUN_14006ea00(int param_1)

undefined8 FUN_14006ea00(int param_1)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  if (-1 < param_1) {
    uVar1 = DAT_140104698 - DAT_140104690 >> 3;
    if (param_1 < (int)uVar1) {
      if (uVar1 <= (ulonglong)(longlong)param_1) {
        _invalid_parameter_noinfo();
      }
                    /* WARNING: Could not recover jumptable at 0x00014006ea4b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar2 = (**(code **)(**(longlong **)(DAT_140104690 + (longlong)param_1 * 8) + 0x10))();
      return uVar2;
    }
  }
  return 0xffffffff;
}


// ==== FUN_14006ea80 @ 14006ea80  bool FUN_14006ea80(longlong param_1)

bool FUN_14006ea80(longlong param_1)

{
  HANDLE pvVar1;
  CSingleLock local_20 [24];
  
  CSingleLock::CSingleLock(local_20,(CSyncObject *)(param_1 + 0x68),1);
  pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
  *(HANDLE *)(param_1 + 0x20) = pvVar1;
  if (pvVar1 != (HANDLE)0x0) {
    CSingleLock::Unlock(local_20);
  }
  else {
    GetLastError();
    log_InlineLogERROR("CMessagePort::Init() failed with m_id=%d, error=%u");
    CSingleLock::Unlock(local_20);
  }
  return pvVar1 != (HANDLE)0x0;
}


// ==== FUN_14006ebe0 @ 14006ebe0  longlong * FUN_14006ebe0(longlong * param_1)

longlong * FUN_14006ebe0(longlong *param_1)

{
  longlong *plVar1;
  longlong lVar2;
  longlong lVar3;
  
  plVar1 = (longlong *)*param_1;
  lVar3 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar1 = (longlong *)*param_1;
    lVar2 = lVar3;
    if (plVar1 == (longlong *)0x0) goto LAB_14006ec13;
  }
  lVar2 = *plVar1;
  if (plVar1 != (longlong *)0x0) {
    lVar3 = lVar2;
  }
LAB_14006ec13:
  if ((ulonglong)(*(longlong *)(lVar3 + 0x38) + *(longlong *)(lVar2 + 0x30)) <=
      (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + 1;
  return param_1;
}


// ==== FUN_14006ec40 @ 14006ec40  bool FUN_14006ec40(longlong * param_1, longlong * param_2)

bool FUN_14006ec40(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_14006ec80 @ 14006ec80  longlong FUN_14006ec80(longlong * param_1)

longlong FUN_14006ec80(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14006eca2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14006eca2:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_14006ecc0 @ 14006ecc0  longlong * FUN_14006ecc0(longlong * param_1)

longlong * FUN_14006ecc0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14006ece2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14006ece2:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + 8;
  return param_1;
}


// ==== FUN_14006ed00 @ 14006ed00  bool FUN_14006ed00(longlong * param_1, longlong * param_2)

bool FUN_14006ed00(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_14006ed40 @ 14006ed40  undefined FUN_14006ed40(undefined8 * param_1)

void FUN_14006ed40(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14006ed50 @ 14006ed50  undefined FUN_14006ed50(undefined8 param_1, ulonglong param_2)

void FUN_14006ed50(undefined8 param_1,ulonglong param_2)

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


// ==== FUN_14006edd0 @ 14006edd0  undefined FUN_14006edd0(undefined8 * param_1)

void FUN_14006edd0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14006ede0 @ 14006ede0  longlong * FUN_14006ede0(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_14006ede0(longlong *param_1,longlong *param_2,longlong param_3)

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
  uVar4 = param_3 + lVar2;
  if (uVar4 <= (ulonglong)(*(longlong *)(lVar5 + 0x38) + *(longlong *)(lVar5 + 0x30))) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x30) <= uVar4) goto LAB_14006ee56;
  }
  _invalid_parameter_noinfo();
LAB_14006ee56:
  *param_2 = (longlong)plVar1;
  param_2[1] = uVar4;
  return param_2;
}


// ==== FUN_14006eeb0 @ 14006eeb0  undefined FUN_14006eeb0(undefined8 param_1, ulonglong param_2)

void FUN_14006eeb0(undefined8 param_1,ulonglong param_2)

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


// ==== FUN_14006ef40 @ 14006ef40  undefined FUN_14006ef40(undefined8 param_1, ulonglong param_2)

void FUN_14006ef40(undefined8 param_1,ulonglong param_2)

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


// ==== FUN_14006efb0 @ 14006efb0  longlong * FUN_14006efb0(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_14006efb0(longlong *param_1,longlong *param_2,longlong param_3)

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
  uVar4 = param_3 + lVar2;
  if (uVar4 <= (ulonglong)(*(longlong *)(lVar5 + 0x38) + *(longlong *)(lVar5 + 0x30))) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x30) <= uVar4) goto LAB_14006f026;
  }
  _invalid_parameter_noinfo();
LAB_14006f026:
  *param_2 = (longlong)plVar1;
  param_2[1] = uVar4;
  return param_2;
}


// ==== FUN_14006f060 @ 14006f060  longlong FUN_14006f060(longlong * param_1, longlong * param_2)

longlong FUN_14006f060(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] - param_2[1];
}


// ==== FUN_14006f0c0 @ 14006f0c0  longlong * FUN_14006f0c0(longlong * param_1, longlong param_2)

longlong * FUN_14006f0c0(longlong *param_1,longlong param_2)

{
  FUN_14006e3e0(param_1,param_2);
  return param_1;
}


// ==== FUN_14006f120 @ 14006f120  void * FUN_14006f120(void * param_1, longlong param_2, longlong param_3)

void * FUN_14006f120(void *param_1,longlong param_2,longlong param_3)

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


// ==== FUN_14006f160 @ 14006f160  longlong * FUN_14006f160(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_14006f160(longlong *param_1,longlong *param_2,longlong param_3)

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
  uVar4 = lVar2 - param_3;
  if (uVar4 <= (ulonglong)(*(longlong *)(lVar5 + 0x38) + *(longlong *)(lVar5 + 0x30))) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x30) <= uVar4) goto LAB_14006f1d9;
  }
  _invalid_parameter_noinfo();
LAB_14006f1d9:
  *param_2 = (longlong)plVar1;
  param_2[1] = uVar4;
  return param_2;
}


// ==== FUN_14006f2e0 @ 14006f2e0  void * FUN_14006f2e0(void * param_1, longlong param_2, void * param_3)

void * FUN_14006f2e0(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14006f320 @ 14006f320  undefined FUN_14006f320(undefined8 * param_1)

void FUN_14006f320(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14006f340 @ 14006f340  undefined FUN_14006f340(undefined8 * param_1)

void FUN_14006f340(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14006f3a0 @ 14006f3a0  undefined8 FUN_14006f3a0(longlong param_1, ulonglong param_2)

undefined8 FUN_14006f3a0(longlong param_1,ulonglong param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  longlong lVar3;
  
  uVar2 = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  if (param_2 != 0) {
    if (0x1fffffffffffffff < param_2) {
      FUN_14006e1f0();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_14006ef40(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    lVar3 = lVar3 + param_2 * 8;
    *(longlong *)(param_1 + 0x28) = lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
  }
  return uVar2;
}


// ==== FUN_14006f430 @ 14006f430  undefined8 * FUN_14006f430(undefined8 * param_1)

undefined8 * FUN_14006f430(undefined8 *param_1)

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


// ==== FUN_14006f470 @ 14006f470  undefined8 * FUN_14006f470(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_14006f470(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[6])) ||
     ((ulonglong)(param_3[6] + param_3[7]) < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_14006f4d0 @ 14006f4d0  longlong * FUN_14006f4d0(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_14006f4d0(longlong *param_1,longlong *param_2,longlong param_3)

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
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar1) goto LAB_14006f53a;
  }
  _invalid_parameter_noinfo();
LAB_14006f53a:
  *param_2 = (longlong)plVar2;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_14006f570 @ 14006f570  undefined8 * FUN_14006f570(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_14006f570(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_14006f5d0 @ 14006f5d0  undefined8 * FUN_14006f5d0(undefined8 * param_1)

undefined8 * FUN_14006f5d0(undefined8 *param_1)

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


// ==== FUN_14006f610 @ 14006f610  void * FUN_14006f610(void * param_1, longlong param_2, void * param_3)

void * FUN_14006f610(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14006f650 @ 14006f650  void * FUN_14006f650(void * param_1, longlong param_2, void * param_3)

void * FUN_14006f650(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14006f6c0 @ 14006f6c0  void * FUN_14006f6c0(void * param_1, longlong param_2, longlong param_3)

void * FUN_14006f6c0(void *param_1,longlong param_2,longlong param_3)

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


// ==== FUN_14006f700 @ 14006f700  longlong * FUN_14006f700(longlong * param_1, longlong param_2, longlong * param_3, longlong * param_4)

longlong * FUN_14006f700(longlong *param_1,longlong param_2,longlong *param_3,longlong *param_4)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  while (*(longlong *)(param_2 + 8) != param_3[1]) {
    param_3[1] = param_3[1] + -1;
    puVar1 = (undefined8 *)FUN_14006e7c0(param_3);
    param_4[1] = param_4[1] + -1;
    puVar2 = (undefined8 *)FUN_14006e7c0(param_4);
    *puVar2 = *puVar1;
  }
  *param_1 = *param_4;
  param_1[1] = param_4[1];
  return param_1;
}


// ==== FUN_14006f790 @ 14006f790  longlong * FUN_14006f790(longlong * param_1, longlong * param_2, longlong param_3, longlong * param_4)

longlong * FUN_14006f790(longlong *param_1,longlong *param_2,longlong param_3,longlong *param_4)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  while (param_2[1] != *(longlong *)(param_3 + 8)) {
    puVar1 = (undefined8 *)FUN_14006e7c0(param_2);
    puVar2 = (undefined8 *)FUN_14006e7c0(param_4);
    *puVar2 = *puVar1;
    param_4[1] = param_4[1] + 1;
    param_2[1] = param_2[1] + 1;
  }
  *param_1 = *param_4;
  param_1[1] = param_4[1];
  return param_1;
}


// ==== FUN_14006f880 @ 14006f880  void * FUN_14006f880(void * param_1, longlong param_2, void * param_3)

void * FUN_14006f880(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14006f8e0 @ 14006f8e0  undefined FUN_14006f8e0(undefined8 * param_1)

void FUN_14006f8e0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14006f900 @ 14006f900  undefined FUN_14006f900(longlong param_1)

void FUN_14006f900(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = *(longlong *)(param_1 + 0x38);
  while (lVar1 != 0) {
    if ((*(longlong *)(param_1 + 0x38) != 0) &&
       (lVar1 = *(longlong *)(param_1 + 0x38) + -1, *(longlong *)(param_1 + 0x38) = lVar1,
       lVar1 == 0)) {
      *(undefined8 *)(param_1 + 0x30) = 0;
    }
    lVar1 = *(longlong *)(param_1 + 0x38);
  }
  lVar1 = *(longlong *)(param_1 + 0x28);
  while (lVar1 != 0) {
    lVar1 = lVar1 + -1;
    if (*(longlong *)(*(longlong *)(param_1 + 0x20) + lVar1 * 8) != 0) {
      operator_delete(*(void **)(*(longlong *)(param_1 + 0x20) + lVar1 * 8));
    }
  }
  if (*(void **)(param_1 + 0x20) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x20));
  }
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_14006f9a0 @ 14006f9a0  undefined FUN_14006f9a0(longlong param_1)

void FUN_14006f9a0(longlong param_1)

{
  if (*(void **)(param_1 + 0x18) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_14006f9d0 @ 14006f9d0  undefined8 * FUN_14006f9d0(undefined8 * param_1)

undefined8 * FUN_14006f9d0(undefined8 *param_1)

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


// ==== FUN_14006fa20 @ 14006fa20  undefined8 * FUN_14006fa20(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_14006fa20(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[6])) ||
     ((ulonglong)(param_3[6] + param_3[7]) < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_14006fa80 @ 14006fa80  undefined8 * FUN_14006fa80(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_14006fa80(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_14006fae0 @ 14006fae0  undefined8 * FUN_14006fae0(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14006fae0(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (undefined8 *)0x0) || (uVar1 < (ulonglong)param_1[6])) ||
     ((ulonglong)(param_1[6] + param_1[7]) < uVar1)) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14006fb40 @ 14006fb40  undefined8 * FUN_14006fb40(undefined8 * param_1)

undefined8 * FUN_14006fb40(undefined8 *param_1)

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


// ==== FUN_14006fb90 @ 14006fb90  undefined8 * FUN_14006fb90(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14006fb90(undefined8 *param_1,undefined8 *param_2,longlong param_3)

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


// ==== FUN_14006fc50 @ 14006fc50  void * FUN_14006fc50(void * param_1, longlong param_2, void * param_3)

void * FUN_14006fc50(void *param_1,longlong param_2,void *param_3)

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


// ==== FUN_14006fcd0 @ 14006fcd0  undefined FUN_14006fcd0(undefined8 * param_1)

void FUN_14006fcd0(undefined8 *param_1)

{
  FUN_14006f900((longlong)param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14006fd00 @ 14006fd00  undefined8 * FUN_14006fd00(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14006fd00(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  longlong lVar2;
  undefined8 uVar3;
  
  uVar1 = param_1[6];
  lVar2 = param_1[7];
  *param_2 = 0;
  if (uVar1 + lVar2 < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar3 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar3;
  return param_2;
}


// ==== FUN_14006fd50 @ 14006fd50  undefined8 * FUN_14006fd50(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14006fd50(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  ulonglong uVar2;
  undefined8 uVar3;
  
  uVar2 = param_1[6];
  uVar1 = uVar2 + param_1[7];
  *param_2 = 0;
  if (uVar1 < uVar2) {
    _invalid_parameter_noinfo();
  }
  uVar3 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar3;
  return param_2;
}


// ==== FUN_14006fdb0 @ 14006fdb0  undefined8 FUN_14006fdb0(longlong * param_1)

undefined8 FUN_14006fdb0(longlong *param_1)

{
  longlong lVar1;
  ulonglong uVar2;
  undefined8 *puVar3;
  undefined8 uVar4;
  longlong local_18;
  ulonglong local_10;
  
  if (param_1[7] == 0) {
    uVar4 = 0;
  }
  else {
    uVar2 = param_1[6];
    if (param_1[7] + uVar2 < uVar2) {
      _invalid_parameter_noinfo();
    }
    local_18 = *param_1;
    local_10 = uVar2;
    puVar3 = (undefined8 *)FUN_14006df30(&local_18);
    uVar4 = *puVar3;
    if (param_1[7] != 0) {
      param_1[6] = param_1[6] + 1;
      if ((ulonglong)(param_1[5] * 2) <= (ulonglong)param_1[6]) {
        param_1[6] = 0;
      }
      lVar1 = param_1[7] + -1;
      param_1[7] = lVar1;
      if (lVar1 == 0) {
        param_1[6] = 0;
        return uVar4;
      }
    }
  }
  return uVar4;
}


// ==== FUN_14006fe40 @ 14006fe40  undefined8 * FUN_14006fe40(undefined8 * param_1)

undefined8 * FUN_14006fe40(undefined8 *param_1)

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


// ==== FUN_14006fea0 @ 14006fea0  undefined FUN_14006fea0(undefined8 * param_1)

void FUN_14006fea0(undefined8 *param_1)

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


// ==== FUN_14006fee0 @ 14006fee0  undefined8 * FUN_14006fee0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14006fee0(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_14006ff30 @ 14006ff30  undefined8 * FUN_14006ff30(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14006ff30(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_14006ff80 @ 14006ff80  undefined8 * FUN_14006ff80(undefined8 * param_1)

undefined8 * FUN_14006ff80(undefined8 *param_1)

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


// ==== FUN_14006ffd0 @ 14006ffd0  longlong * FUN_14006ffd0(longlong * param_1, longlong * param_2, longlong param_3, longlong param_4)

longlong * FUN_14006ffd0(longlong *param_1,longlong *param_2,longlong param_3,longlong param_4)

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


// ==== FUN_140070120 @ 140070120  void * FUN_140070120(undefined8 param_1, void * param_2, longlong param_3, void * param_4)

void * FUN_140070120(undefined8 param_1,void *param_2,longlong param_3,void *param_4)

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


// ==== FUN_1400701a0 @ 1400701a0  undefined FUN_1400701a0(undefined8 * param_1)

void FUN_1400701a0(undefined8 *param_1)

{
  FUN_14006f900((longlong)param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140070470 @ 140070470  undefined8 * FUN_140070470(undefined8 * param_1)

undefined8 * FUN_140070470(undefined8 *param_1)

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
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_1400704d0 @ 1400704d0  undefined FUN_1400704d0(longlong * param_1)

void FUN_1400704d0(longlong *param_1)

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


// ==== FUN_140070590 @ 140070590  undefined FUN_140070590(longlong param_1, ulonglong param_2)

void FUN_140070590(longlong param_1,ulonglong param_2)

{
  void *pvVar1;
  void *_Dst;
  ulonglong uVar2;
  code *pcVar3;
  ulonglong uVar4;
  void *_Dst_00;
  rsize_t rVar5;
  longlong lVar6;
  longlong lVar7;
  
  uVar2 = *(ulonglong *)(param_1 + 0x28);
  if (0xfffffffffffffff - uVar2 < param_2) {
    FUN_14006e150();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  uVar4 = uVar2 >> 1;
  if (uVar4 < 8) {
    uVar4 = 8;
  }
  if ((param_2 < uVar4) && (uVar2 <= 0xfffffffffffffff - uVar4)) {
    param_2 = uVar4;
  }
  uVar4 = *(ulonglong *)(param_1 + 0x30) >> 1;
  _Dst_00 = (void *)FUN_14006eeb0(param_1 + 0x10,uVar2 + param_2);
  lVar6 = uVar4 * 8;
  pvVar1 = (void *)(lVar6 + *(longlong *)(param_1 + 0x20));
  lVar7 = (*(longlong *)(param_1 + 0x28) * 8 - (longlong)pvVar1) + *(longlong *)(param_1 + 0x20) >>
          3;
  rVar5 = lVar7 * 8;
  _Dst = (void *)(rVar5 + lVar6 + (longlong)_Dst_00);
  if (lVar7 != 0) {
    memmove_s((void *)(lVar6 + (longlong)_Dst_00),rVar5,pvVar1,rVar5);
  }
  if (param_2 < uVar4) {
    lVar7 = (longlong)(param_2 * 8) >> 3;
    if (lVar7 != 0) {
      rVar5 = lVar7 << 3;
      memmove_s(_Dst,rVar5,*(void **)(param_1 + 0x20),rVar5);
    }
    pvVar1 = (void *)(*(longlong *)(param_1 + 0x20) + param_2 * 8);
    lVar6 = (lVar6 - (longlong)pvVar1) + *(longlong *)(param_1 + 0x20) >> 3;
    rVar5 = lVar6 * 8;
    if (lVar6 != 0) {
      memmove_s(_Dst_00,rVar5,pvVar1,rVar5);
    }
    if (param_2 != 0) {
      memset((void *)(rVar5 + (longlong)_Dst_00),0,param_2 << 3);
    }
  }
  else {
    rVar5 = (lVar6 >> 3) * 8;
    if (lVar6 >> 3 != 0) {
      memmove_s(_Dst,rVar5,*(void **)(param_1 + 0x20),rVar5);
    }
    if (param_2 - uVar4 != 0) {
      memset((void *)(rVar5 + (longlong)_Dst),0,(param_2 - uVar4) * 8);
    }
    if (uVar4 != 0) {
      memset(_Dst_00,0,uVar4 << 3);
    }
  }
  if (*(void **)(param_1 + 0x20) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x20));
  }
  *(longlong *)(param_1 + 0x28) = *(longlong *)(param_1 + 0x28) + param_2;
  *(void **)(param_1 + 0x20) = _Dst_00;
  return;
}


// ==== FUN_140070780 @ 140070780  undefined FUN_140070780(longlong param_1, longlong param_2, ulonglong param_3, undefined8 * param_4)

void FUN_140070780(longlong param_1,longlong param_2,ulonglong param_3,undefined8 *param_4)

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
      FUN_14006e1f0();
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
      pvVar3 = (void *)FUN_14006ef40(param_1 + 0x10,uVar9);
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
      FUN_140070120(param_1,*(void **)(param_2 + 8),lVar7,
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
      pvVar3 = FUN_140070120(param_1,pvVar10,lVar7,(void *)lVar7);
      *(void **)(param_1 + 0x20) = pvVar3;
      FUN_14006f6c0(*(void **)(param_2 + 8),(longlong)pvVar10,lVar7);
      puVar12 = *(undefined8 **)(param_2 + 8);
      puVar6 = puVar12 + param_3;
      for (; puVar12 != puVar6; puVar12 = puVar12 + 1) {
        *puVar12 = uVar1;
      }
    }
  }
  return;
}


// ==== FUN_140070a70 @ 140070a70  longlong * FUN_140070a70(longlong * param_1, longlong param_2, longlong * param_3, longlong * param_4)

longlong * FUN_140070a70(longlong *param_1,longlong param_2,longlong *param_3,longlong *param_4)

{
  longlong *plVar1;
  ulonglong uVar2;
  longlong *plVar3;
  longlong lVar4;
  longlong lVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  
  FUN_14006f160(param_4,param_1,param_3[1] - *(longlong *)(param_2 + 8));
  if ((undefined8 *)*param_4 == (undefined8 *)0x0) {
    plVar3 = (longlong *)0x0;
  }
  else {
    plVar3 = *(longlong **)*param_4;
  }
  plVar3 = (longlong *)*plVar3;
  uVar8 = param_4[1];
  plVar1 = (longlong *)*param_3;
  uVar6 = param_3[1];
  uVar2 = *(ulonglong *)(param_2 + 8);
  while (uVar2 != uVar6) {
    uVar6 = uVar6 - 1;
    uVar7 = uVar6 >> 1;
    if (plVar1 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar1;
    }
    if ((ulonglong)(*(longlong *)(lVar4 + 0x38) + *(longlong *)(lVar4 + 0x30)) <= uVar6) {
      _invalid_parameter_noinfo();
    }
    if (plVar1 == (longlong *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar1;
    }
    if (*(ulonglong *)(lVar4 + 0x28) <= uVar7) {
      if (plVar1 == (longlong *)0x0) {
        lVar4 = 0;
      }
      else {
        lVar4 = *plVar1;
      }
      uVar7 = uVar7 - *(longlong *)(lVar4 + 0x28);
    }
    if (plVar1 == (longlong *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar1;
    }
    uVar8 = uVar8 - 1;
    lVar4 = *(longlong *)(*(longlong *)(lVar4 + 0x20) + uVar7 * 8);
    uVar7 = uVar8 >> 1;
    if (plVar3 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar5 = 0;
    }
    else {
      lVar5 = *plVar3;
    }
    if ((ulonglong)(*(longlong *)(lVar5 + 0x38) + *(longlong *)(lVar5 + 0x30)) <= uVar8) {
      _invalid_parameter_noinfo();
    }
    if (plVar3 == (longlong *)0x0) {
      lVar5 = 0;
    }
    else {
      lVar5 = *plVar3;
    }
    if (*(ulonglong *)(lVar5 + 0x28) <= uVar7) {
      if (plVar3 == (longlong *)0x0) {
        lVar5 = 0;
      }
      else {
        lVar5 = *plVar3;
      }
      uVar7 = uVar7 - *(longlong *)(lVar5 + 0x28);
    }
    if (plVar3 == (longlong *)0x0) {
      lVar5 = 0;
    }
    else {
      lVar5 = *plVar3;
    }
    *(undefined8 *)
     (*(longlong *)(*(longlong *)(lVar5 + 0x20) + uVar7 * 8) + (ulonglong)((uint)uVar8 & 1) * 8) =
         *(undefined8 *)(lVar4 + (ulonglong)((uint)uVar6 & 1) * 8);
  }
  return param_1;
}


// ==== FUN_140070c50 @ 140070c50  longlong * FUN_140070c50(longlong * param_1, longlong * param_2, longlong param_3, longlong * param_4)

longlong * FUN_140070c50(longlong *param_1,longlong *param_2,longlong param_3,longlong *param_4)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong lVar4;
  longlong lVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  uint uVar8;
  ulonglong uVar9;
  
  FUN_14006efb0(param_4,param_1,*(longlong *)(param_3 + 8) - param_2[1]);
  if ((undefined8 *)*param_4 == (undefined8 *)0x0) {
    plVar3 = (longlong *)0x0;
  }
  else {
    plVar3 = *(longlong **)*param_4;
  }
  plVar3 = (longlong *)*plVar3;
  uVar9 = param_4[1];
  uVar1 = *(ulonglong *)(param_3 + 8);
  plVar2 = (longlong *)*param_2;
  for (uVar6 = param_2[1]; uVar6 != uVar1; uVar6 = uVar6 + 1) {
    uVar7 = uVar6 >> 1;
    if (plVar2 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar2;
    }
    if ((ulonglong)(*(longlong *)(lVar4 + 0x38) + *(longlong *)(lVar4 + 0x30)) <= uVar6) {
      _invalid_parameter_noinfo();
    }
    if (plVar2 == (longlong *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar2;
    }
    if (*(ulonglong *)(lVar4 + 0x28) <= uVar7) {
      if (plVar2 == (longlong *)0x0) {
        lVar4 = 0;
      }
      else {
        lVar4 = *plVar2;
      }
      uVar7 = uVar7 - *(longlong *)(lVar4 + 0x28);
    }
    if (plVar2 == (longlong *)0x0) {
      lVar4 = 0;
    }
    else {
      lVar4 = *plVar2;
    }
    lVar4 = *(longlong *)(*(longlong *)(lVar4 + 0x20) + uVar7 * 8);
    uVar8 = (uint)uVar9;
    uVar7 = uVar9 >> 1;
    if (plVar3 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar5 = 0;
    }
    else {
      lVar5 = *plVar3;
    }
    if ((ulonglong)(*(longlong *)(lVar5 + 0x38) + *(longlong *)(lVar5 + 0x30)) <= uVar9) {
      _invalid_parameter_noinfo();
    }
    if (plVar3 == (longlong *)0x0) {
      lVar5 = 0;
    }
    else {
      lVar5 = *plVar3;
    }
    if (*(ulonglong *)(lVar5 + 0x28) <= uVar7) {
      if (plVar3 == (longlong *)0x0) {
        lVar5 = 0;
      }
      else {
        lVar5 = *plVar3;
      }
      uVar7 = uVar7 - *(longlong *)(lVar5 + 0x28);
    }
    if (plVar3 == (longlong *)0x0) {
      lVar5 = 0;
    }
    else {
      lVar5 = *plVar3;
    }
    uVar9 = uVar9 + 1;
    *(undefined8 *)
     (*(longlong *)(*(longlong *)(lVar5 + 0x20) + uVar7 * 8) + (ulonglong)(uVar8 & 1) * 8) =
         *(undefined8 *)(lVar4 + (ulonglong)((uint)uVar6 & 1) * 8);
  }
  return param_1;
}


// ==== FUN_140070e30 @ 140070e30  undefined8 * FUN_140070e30(undefined8 * param_1)

undefined8 * FUN_140070e30(undefined8 *param_1)

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
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_140070e90 @ 140070e90  undefined FUN_140070e90(undefined8 * param_1)

void FUN_140070e90(undefined8 *param_1)

{
  *param_1 = CMessagePort::vftable;
  CMessagePort::vf_0x28((longlong)param_1);
  FUN_14006f900((longlong)(param_1 + 0x14));
  operator_delete((void *)param_1[0x14]);
  *(undefined ***)(param_1 + 0xd) = CCriticalSection::vftable;
  DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 0xf));
  CSyncObject::~CSyncObject((CSyncObject *)(param_1 + 0xd));
  FUN_14006f900((longlong)(param_1 + 5));
  operator_delete((void *)param_1[5]);
  *param_1 = IMessagePort::vftable;
  return;
}


// ==== FUN_140070f30 @ 140070f30  undefined FUN_140070f30(void)

void FUN_140070f30(void)

{
  undefined8 *puVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong *plVar4;
  longlong lVar5;
  
  plVar4 = DAT_140104690;
  plVar2 = DAT_140104678;
  if (DAT_140104698 < DAT_140104690) {
    _invalid_parameter_noinfo();
    plVar2 = DAT_140104678;
  }
  while( true ) {
    plVar3 = DAT_140104698;
    if (DAT_140104698 < DAT_140104690) {
      _invalid_parameter_noinfo();
    }
    if ((plVar2 == (longlong *)0x0) || (plVar2 != DAT_140104678)) {
      _invalid_parameter_noinfo();
    }
    if (plVar4 == plVar3) break;
    if (plVar2 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar5 = 0;
    }
    else {
      lVar5 = *plVar2;
    }
    if (*(longlong **)(lVar5 + 0x20) <= plVar4) {
      _invalid_parameter_noinfo();
    }
    puVar1 = (undefined8 *)*plVar4;
    if (puVar1 != (undefined8 *)0x0) {
      (**(code **)*puVar1)(puVar1,1);
    }
    if (plVar2 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar5 = 0;
    }
    else {
      lVar5 = *plVar2;
    }
    if (*(longlong **)(lVar5 + 0x20) <= plVar4) {
      _invalid_parameter_noinfo();
    }
    plVar4 = plVar4 + 1;
  }
  FUN_1400704d0((longlong *)&DAT_140104678);
  return;
}


// ==== FUN_140071010 @ 140071010  undefined FUN_140071010(longlong param_1, undefined8 * param_2)

void FUN_140071010(longlong param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  void *pvVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  
  if (((*(char *)(param_1 + 0x30) + (char)*(longlong *)(param_1 + 0x38) & 1U) == 0) &&
     (*(ulonglong *)(param_1 + 0x28) <= *(longlong *)(param_1 + 0x38) + 2U >> 1)) {
    FUN_140070590(param_1,1);
  }
  uVar3 = *(longlong *)(param_1 + 0x30) + *(longlong *)(param_1 + 0x38);
  uVar4 = uVar3 >> 1;
  if (*(ulonglong *)(param_1 + 0x28) <= uVar4) {
    uVar4 = uVar4 - *(ulonglong *)(param_1 + 0x28);
  }
  if (*(longlong *)(*(longlong *)(param_1 + 0x20) + uVar4 * 8) == 0) {
    pvVar2 = operator_new(0x10);
    *(void **)(*(longlong *)(param_1 + 0x20) + uVar4 * 8) = pvVar2;
  }
  puVar1 = (undefined8 *)
           (*(longlong *)(*(longlong *)(param_1 + 0x20) + uVar4 * 8) +
           (ulonglong)((uint)uVar3 & 1) * 8);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = *param_2;
  }
  *(longlong *)(param_1 + 0x38) = *(longlong *)(param_1 + 0x38) + 1;
  return;
}


// ==== FUN_1400710c0 @ 1400710c0  undefined FUN_1400710c0(longlong param_1, undefined8 param_2)

void FUN_1400710c0(longlong param_1,undefined8 param_2)

{
  undefined8 local_res10 [3];
  
  local_res10[0] = param_2;
  FUN_140071010(param_1,local_res10);
  return;
}


// ==== FUN_1400710e0 @ 1400710e0  longlong * FUN_1400710e0(longlong * param_1, longlong * param_2, longlong * param_3, undefined8 * param_4)

longlong * FUN_1400710e0(longlong *param_1,longlong *param_2,longlong *param_3,undefined8 *param_4)

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
  FUN_140070780((longlong)param_1,(longlong)&local_28,1,param_4);
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
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar1) goto LAB_1400711d4;
  }
  _invalid_parameter_noinfo();
LAB_1400711d4:
  *param_2 = (longlong)local_28;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_140071210 @ 140071210  longlong * FUN_140071210(longlong * param_1, undefined8 * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_140071210(longlong *param_1,undefined8 *param_2,longlong *param_3,longlong *param_4)

{
  longlong *plVar1;
  longlong *plVar2;
  longlong local_38;
  undefined8 uStack_30;
  longlong local_28;
  longlong local_20;
  longlong local_18;
  longlong lStack_10;
  
  local_28 = *param_4;
  local_20 = param_4[1];
  plVar2 = (longlong *)0x0;
  plVar1 = plVar2;
  if ((undefined8 *)*param_3 != (undefined8 *)0x0) {
    plVar1 = *(longlong **)*param_3;
  }
  local_18 = *plVar1;
  lStack_10 = param_3[1];
  if ((undefined8 *)*param_2 != (undefined8 *)0x0) {
    plVar2 = *(longlong **)*param_2;
  }
  local_38 = *plVar2;
  uStack_30 = param_2[1];
  FUN_140070a70(param_1,(longlong)&local_38,&local_18,&local_28);
  return param_1;
}


// ==== FUN_1400712d0 @ 1400712d0  longlong * FUN_1400712d0(longlong * param_1, undefined8 * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_1400712d0(longlong *param_1,undefined8 *param_2,longlong *param_3,longlong *param_4)

{
  longlong *plVar1;
  longlong *plVar2;
  longlong local_38;
  undefined8 uStack_30;
  longlong local_28;
  longlong local_20;
  longlong local_18;
  longlong lStack_10;
  
  local_28 = *param_4;
  local_20 = param_4[1];
  plVar2 = (longlong *)0x0;
  plVar1 = plVar2;
  if ((undefined8 *)*param_3 != (undefined8 *)0x0) {
    plVar1 = *(longlong **)*param_3;
  }
  local_18 = *plVar1;
  lStack_10 = param_3[1];
  if ((undefined8 *)*param_2 != (undefined8 *)0x0) {
    plVar2 = *(longlong **)*param_2;
  }
  local_38 = *plVar2;
  uStack_30 = param_2[1];
  FUN_140070c50(param_1,&local_38,(longlong)&local_18,&local_28);
  return param_1;
}


// ==== FUN_140071390 @ 140071390  undefined8 * FUN_140071390(undefined8 * param_1, undefined4 param_2)

undefined8 * FUN_140071390(undefined8 *param_1,undefined4 param_2)

{
  CSyncObject *this;
  int iVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong *plVar4;
  
  *param_1 = IMessagePort::vftable;
  *param_1 = CMessagePort::vftable;
  *(undefined4 *)((longlong)param_1 + 0xc) = param_2;
  *(undefined4 *)(param_1 + 3) = 1;
  plVar2 = (longlong *)operator_new(8);
  plVar4 = (longlong *)0x0;
  plVar3 = plVar4;
  if (plVar2 != (longlong *)0x0) {
    *plVar2 = (longlong)(param_1 + 5);
    plVar3 = plVar2;
  }
  param_1[5] = plVar3;
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[0xc] = 0;
  this = (CSyncObject *)(param_1 + 0xd);
  CSyncObject::CSyncObject(this,(char *)0x0);
  *(undefined ***)this = CCriticalSection::vftable;
  iVar1 = CCriticalSection::Init((CCriticalSection *)this);
  if (iVar1 == 0) {
    AfxThrowMemoryException();
  }
  plVar3 = (longlong *)operator_new(8);
  if (plVar3 != (longlong *)0x0) {
    *plVar3 = (longlong)(param_1 + 0x14);
    plVar4 = plVar3;
  }
  param_1[0x14] = plVar4;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  param_1[0x1a] = 0;
  param_1[0x1b] = 0;
  *(undefined4 *)(param_1 + 1) = 0;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14) = 1;
  param_1[4] = 0;
  return param_1;
}


// ==== FUN_1400716f0 @ 1400716f0  ulonglong FUN_1400716f0(longlong param_1, uint param_2, uint param_3, uint param_4, void * param_5)

ulonglong FUN_1400716f0(longlong param_1,uint param_2,uint param_3,uint param_4,void *param_5)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  ulonglong extraout_RAX;
  ulonglong uVar4;
  undefined4 extraout_var;
  undefined4 extraout_var_00;
  longlong lVar5;
  undefined4 extraout_var_01;
  undefined4 extraout_var_02;
  undefined4 extraout_var_03;
  uint *local_58;
  undefined8 local_50;
  CSingleLock local_48 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [40];
  
  local_50 = 0xfffffffffffffffe;
  if (param_5 == (void *)0x0) {
    log_InlineLogERROR(&DAT_1400be0b0,"CHECKF",&DAT_1400cc9b0,
                       "f:\\version\\cqserver-78.0.11-1204\\comm\\source\\messageport.cpp",300);
    uVar4 = extraout_RAX & 0xffffffffffffff00;
  }
  else {
    CSingleLock::CSingleLock(local_48,(CSyncObject *)(param_1 + 0x68),1);
    if (*(int *)(param_1 + 0x14) == 0) {
      if (((int)param_2 < 0) || ((int)(DAT_140104698 - DAT_140104690 >> 3) <= (int)param_2)) {
        log_InlineLogERROR("CMessagePort::PushMsg() with bad port=%d",(ulonglong)param_2);
        iVar1 = CSingleLock::Unlock(local_48);
        uVar4 = CONCAT44(extraout_var_03,iVar1) & 0xffffffffffffff00;
      }
      else {
        uVar2 = FUN_14006dd80(param_4);
        if (uVar2 - 1 < 0x800) {
          local_58 = (uint *)FUN_14006fdb0((longlong *)(param_1 + 0xa0));
          if ((local_58 == (uint *)0x0) &&
             (local_58 = (uint *)operator_new(0x80c), local_58 == (uint *)0x0)) {
            log_InlineLogERROR(&DAT_1400be0b0,"MYASSERT",
                               "!\"CMessagePort::PushMsg() failed to new CMessagePacket\"",
                               "f:\\version\\cqserver-78.0.11-1204\\comm\\source\\messageport.cpp",
                               0x14d);
            iVar1 = CSingleLock::Unlock(local_48);
            uVar4 = CONCAT44(extraout_var_00,iVar1) & 0xffffffffffffff00;
          }
          else {
            *local_58 = param_2;
            local_58[1] = param_3;
            local_58[2] = param_4;
            memcpy(local_58 + 3,param_5,(longlong)(int)uVar2);
            FUN_140071010(param_1 + 0x28,&local_58);
            *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
            SetEvent(*(HANDLE *)(param_1 + 0x20));
            iVar1 = *(int *)(param_1 + 0x10);
            if ((4999 < iVar1) &&
               ((iVar1 == (iVar1 / 1000) * 1000 && (iVar1 != *(int *)(param_1 + 8))))) {
              *(int *)(param_1 + 8) = iVar1;
              lVar5 = tq::DumpBuffer((char *)local_30,(int)param_5);
              if (*(ulonglong *)(lVar5 + 0x20) < 0x10) {
                lVar5 = lVar5 + 8;
              }
              else {
                lVar5 = *(longlong *)(lVar5 + 8);
              }
              log_InlineLogERROR(&DAT_1400cc930,(ulonglong)*(uint *)(param_1 + 0xc),
                                 (ulonglong)*(uint *)(param_1 + 0x10),(ulonglong)param_2,param_3,
                                 lVar5);
              std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
              ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                        (local_30);
            }
            iVar1 = *(int *)(param_1 + 0x10);
            iVar3 = CSingleLock::Unlock(local_48);
            uVar4 = CONCAT71((int7)(CONCAT44(extraout_var_01,iVar3) >> 8),iVar1 < 0x3e9);
          }
        }
        else {
          log_InlineLogERROR("CMessagePort::PushMsg() with bad packet size=%d",(ulonglong)uVar2);
          iVar1 = CSingleLock::Unlock(local_48);
          uVar4 = CONCAT44(extraout_var_02,iVar1) & 0xffffffffffffff00;
        }
      }
    }
    else {
      iVar1 = CSingleLock::Unlock(local_48);
      uVar4 = CONCAT44(extraout_var,iVar1) & 0xffffffffffffff00;
    }
  }
  return uVar4;
}


// ==== FUN_140071ae0 @ 140071ae0  undefined FUN_140071ae0(longlong * param_1, undefined8 * param_2)

void FUN_140071ae0(longlong *param_1,undefined8 *param_2)

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
  FUN_1400710e0(param_1,local_18,&local_28,param_2);
  return;
}


// ==== FUN_140071b90 @ 140071b90  longlong * FUN_140071b90(longlong * param_1, longlong * param_2, undefined8 * param_3, undefined8 * param_4)

longlong *
FUN_140071b90(longlong *param_1,longlong *param_2,undefined8 *param_3,undefined8 *param_4)

{
  ulonglong uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  longlong *plVar4;
  longlong *plVar5;
  longlong lVar6;
  longlong lVar7;
  ulonglong uVar8;
  longlong *local_68;
  ulonglong uStack_60;
  longlong *local_58;
  ulonglong uStack_50;
  longlong *local_48;
  ulonglong uStack_40;
  longlong local_38 [2];
  
  local_58 = (longlong *)*param_3;
  uVar2 = param_3[1];
  if (((param_1 == (longlong *)0x0) || (uVar2 < (ulonglong)param_1[6])) ||
     ((ulonglong)(param_1[6] + param_1[7]) < uVar2)) {
    uStack_50 = uVar2;
    _invalid_parameter_noinfo();
  }
  local_68 = (longlong *)*param_4;
  plVar5 = (longlong *)*param_1;
  uVar8 = param_4[1];
  local_58 = plVar5;
  if ((uVar8 < (ulonglong)param_1[6]) ||
     (uStack_50 = uVar2, (ulonglong)(param_1[6] + param_1[7]) < uVar8)) {
    uStack_60 = uVar8;
    uStack_50 = uVar2;
    _invalid_parameter_noinfo();
  }
  uVar3 = param_1[6];
  plVar4 = (longlong *)*param_1;
  local_68 = plVar4;
  uStack_60 = uVar8;
  if (uVar3 + param_1[7] < uVar3) {
    _invalid_parameter_noinfo();
  }
  if ((plVar5 == (longlong *)0x0) || (plVar5 != (longlong *)*param_1)) {
    _invalid_parameter_noinfo();
  }
  if ((plVar4 == (longlong *)0x0) || (plVar4 != plVar5)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = param_1[6] + param_1[7];
  lVar7 = uVar8 - uVar2;
  if (uVar1 < (ulonglong)param_1[6]) {
    _invalid_parameter_noinfo();
  }
  if (((longlong *)*param_1 == (longlong *)0x0) || ((longlong *)*param_1 != plVar4)) {
    _invalid_parameter_noinfo();
  }
  if (uVar2 - uVar3 < uVar1 - uVar8) {
    uVar8 = param_1[6];
    if (uVar8 + param_1[7] < uVar8) {
      _invalid_parameter_noinfo();
    }
    plVar4 = (longlong *)0x0;
    local_58 = local_68;
    uStack_50 = uStack_60;
    local_48 = plVar4;
    if (plVar5 != (longlong *)0x0) {
      local_48 = (longlong *)*plVar5;
    }
    local_48 = (longlong *)*local_48;
    if ((undefined8 *)*param_1 != (undefined8 *)0x0) {
      plVar4 = *(longlong **)*param_1;
    }
    local_68 = (longlong *)*plVar4;
    uStack_60 = uVar8;
    uStack_40 = uVar2;
    FUN_140070a70(local_38,(longlong)&local_68,(longlong *)&local_48,(longlong *)&local_58);
    if (lVar7 != 0) {
      lVar6 = param_1[7];
      do {
        if (lVar6 != 0) {
          param_1[6] = param_1[6] + 1;
          if ((ulonglong)(param_1[5] * 2) <= (ulonglong)param_1[6]) {
            param_1[6] = 0;
          }
          lVar6 = lVar6 + -1;
          if (lVar6 == 0) {
            param_1[6] = 0;
          }
        }
        lVar7 = lVar7 + -1;
      } while (lVar7 != 0);
      param_1[7] = lVar6;
    }
  }
  else {
    uVar1 = param_1[6] + param_1[7];
    if (uVar1 < (ulonglong)param_1[6]) {
      _invalid_parameter_noinfo();
    }
    plVar5 = (longlong *)0x0;
    local_48 = local_58;
    uStack_40 = uStack_50;
    local_68 = plVar5;
    if ((undefined8 *)*param_1 != (undefined8 *)0x0) {
      local_68 = *(longlong **)*param_1;
    }
    local_68 = (longlong *)*local_68;
    if (plVar4 != (longlong *)0x0) {
      plVar5 = (longlong *)*plVar4;
    }
    local_58 = (longlong *)*plVar5;
    uStack_60 = uVar1;
    uStack_50 = uVar8;
    FUN_140070c50(local_38,(longlong *)&local_58,(longlong)&local_68,(longlong *)&local_48);
    if (lVar7 != 0) {
      lVar6 = param_1[7];
      do {
        if ((lVar6 != 0) && (lVar6 = lVar6 + -1, lVar6 == 0)) {
          param_1[6] = 0;
        }
        lVar7 = lVar7 + -1;
      } while (lVar7 != 0);
      param_1[7] = lVar6;
    }
  }
  lVar7 = 0;
  uVar8 = param_1[6];
  if (uVar8 + param_1[7] < uVar8) {
    _invalid_parameter_noinfo();
  }
  plVar5 = (longlong *)*param_1;
  local_58 = plVar5;
  uStack_50 = uVar8;
  if (plVar5 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar6 = lVar7;
  }
  else {
    lVar6 = *plVar5;
  }
  uVar8 = uVar8 + (uVar2 - uVar3);
  if (uVar8 <= (ulonglong)(*(longlong *)(lVar6 + 0x38) + *(longlong *)(lVar6 + 0x30))) {
    if (plVar5 != (longlong *)0x0) {
      lVar7 = *plVar5;
    }
    if (*(ulonglong *)(lVar7 + 0x30) <= uVar8) goto LAB_140071ecd;
  }
  _invalid_parameter_noinfo();
LAB_140071ecd:
  *param_2 = (longlong)local_58;
  param_2[1] = uVar8;
  return param_2;
}


// ==== FUN_140071f20 @ 140071f20  undefined8 FUN_140071f20(int param_1)

undefined8 FUN_140071f20(int param_1)

{
  longlong *plVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  int iVar4;
  undefined1 *extraout_RAX;
  undefined8 *puVar5;
  longlong lVar6;
  HANDLE pvVar7;
  undefined4 extraout_var;
  undefined4 extraout_var_00;
  ulonglong uVar9;
  longlong lVar10;
  int iVar11;
  undefined8 *local_res10;
  longlong *local_48;
  undefined8 *puStack_40;
  CSingleLock local_38 [32];
  undefined1 *puVar8;
  
  puVar8 = (undefined1 *)register0x00000020;
  if (param_1 < 1) {
    log_InlineLogERROR(&DAT_1400be0b0);
    puVar8 = extraout_RAX;
  }
  iVar11 = 0;
  if (0 < param_1) {
    do {
      local_res10 = (undefined8 *)operator_new(0xe0);
      if (local_res10 == (undefined8 *)0x0) {
        puVar5 = (undefined8 *)0x0;
      }
      else {
        puVar5 = FUN_140071390(local_res10,iVar11);
      }
      puVar3 = DAT_140104698;
      if (puVar5 == (undefined8 *)0x0) {
        return 0;
      }
      if (DAT_140104690 == (undefined8 *)0x0) {
        uVar9 = 0;
      }
      else {
        uVar9 = DAT_1401046a0 - (longlong)DAT_140104690 >> 3;
      }
      local_res10 = puVar5;
      if ((ulonglong)((longlong)DAT_140104698 - (longlong)DAT_140104690 >> 3) < uVar9) {
        *DAT_140104698 = puVar5;
        DAT_140104698 = DAT_140104698 + 1;
      }
      else {
        if (DAT_140104698 < DAT_140104690) {
          _invalid_parameter_noinfo();
        }
        puVar2 = DAT_140104690;
        plVar1 = DAT_140104678;
        if (((longlong)DAT_140104698 - (longlong)DAT_140104690 & 0xfffffffffffffff8U) == 0) {
          lVar10 = 0;
        }
        else {
          if (DAT_140104698 < DAT_140104690) {
            _invalid_parameter_noinfo();
          }
          if ((plVar1 == (longlong *)0x0) || (plVar1 != DAT_140104678)) {
            _invalid_parameter_noinfo();
          }
          lVar10 = (longlong)puVar3 - (longlong)puVar2 >> 3;
        }
        local_48 = plVar1;
        puStack_40 = puVar3;
        FUN_140070780(0x140104678,(longlong)&local_48,1,&local_res10);
        puVar3 = DAT_140104690;
        if (DAT_140104698 < DAT_140104690) {
          _invalid_parameter_noinfo();
        }
        plVar1 = DAT_140104678;
        if (DAT_140104678 == (longlong *)0x0) {
          _invalid_parameter_noinfo();
          lVar6 = 0;
        }
        else {
          lVar6 = *DAT_140104678;
        }
        if (puVar3 + lVar10 <= *(undefined8 **)(lVar6 + 0x20)) {
          if (plVar1 == (longlong *)0x0) {
            lVar6 = 0;
          }
          else {
            lVar6 = *plVar1;
          }
          if (*(undefined8 **)(lVar6 + 0x18) <= puVar3 + lVar10) goto LAB_1400720e9;
        }
        _invalid_parameter_noinfo();
      }
LAB_1400720e9:
      CSingleLock::CSingleLock(local_38,(CSyncObject *)(puVar5 + 0xd),1);
      pvVar7 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
      puVar5[4] = pvVar7;
      if (pvVar7 == (HANDLE)0x0) {
        GetLastError();
        log_InlineLogERROR("CMessagePort::Init() failed with m_id=%d, error=%u");
        iVar11 = CSingleLock::Unlock(local_38);
        return CONCAT44(extraout_var_00,iVar11) & 0xffffffffffffff00;
      }
      iVar4 = CSingleLock::Unlock(local_38);
      puVar8 = (undefined1 *)CONCAT44(extraout_var,iVar4);
      iVar11 = iVar11 + 1;
    } while (iVar11 < param_1);
  }
  return CONCAT71((int7)((ulonglong)puVar8 >> 8),1);
}


// ==== FUN_140072180 @ 140072180  longlong * FUN_140072180(longlong * param_1, longlong * param_2, longlong * param_3)

longlong * FUN_140072180(longlong *param_1,longlong *param_2,longlong *param_3)

{
  longlong *plVar1;
  longlong lVar2;
  ulonglong uVar3;
  longlong lVar4;
  longlong *local_38;
  ulonglong uStack_30;
  longlong local_28;
  longlong local_20;
  
  plVar1 = (longlong *)*param_3;
  uStack_30 = param_3[1];
  lVar2 = 0;
  local_38 = plVar1;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar4 = lVar2;
  }
  else {
    lVar4 = *plVar1;
  }
  uVar3 = uStack_30 + 1;
  if (uVar3 <= (ulonglong)(*(longlong *)(lVar4 + 0x38) + *(longlong *)(lVar4 + 0x30))) {
    if (plVar1 != (longlong *)0x0) {
      lVar2 = *plVar1;
    }
    if (*(ulonglong *)(lVar2 + 0x30) <= uVar3) goto LAB_1400721fd;
  }
  _invalid_parameter_noinfo();
LAB_1400721fd:
  local_28 = *param_3;
  local_20 = param_3[1];
  uStack_30 = uVar3;
  FUN_140071b90(param_1,param_2,&local_28,&local_38);
  return param_2;
}


// ==== FUN_140072260 @ 140072260  undefined8 FUN_140072260(longlong param_1, undefined4 * param_2, undefined4 * param_3, uint * param_4, void * param_5)

undefined8
FUN_140072260(longlong param_1,undefined4 *param_2,undefined4 *param_3,uint *param_4,void *param_5)

{
  ulonglong uVar1;
  undefined4 *puVar2;
  uint uVar3;
  ulonglong in_RAX;
  undefined8 *puVar4;
  longlong *plVar5;
  ulonglong extraout_RAX;
  undefined4 *local_res10;
  longlong local_38;
  ulonglong uStack_30;
  longlong local_28 [2];
  
  if ((((param_2 == (undefined4 *)0x0) || (param_3 == (undefined4 *)0x0)) ||
      (param_4 == (uint *)0x0)) || (param_5 == (void *)0x0)) {
    log_InlineLogERROR(&DAT_1400be0b0);
    in_RAX = extraout_RAX;
  }
  else if ((*(int *)(param_1 + 0x14) == 0) && (0 < *(int *)(param_1 + 0x10))) {
    uVar1 = *(ulonglong *)(param_1 + 0x58);
    if (uVar1 + *(longlong *)(param_1 + 0x60) < uVar1) {
      _invalid_parameter_noinfo();
    }
    local_38 = *(longlong *)(param_1 + 0x28);
    uStack_30 = uVar1;
    puVar4 = (undefined8 *)FUN_14006df30(&local_38);
    puVar2 = (undefined4 *)*puVar4;
    *param_2 = *puVar2;
    *param_3 = puVar2[1];
    uVar3 = puVar2[2];
    *param_4 = uVar3;
    uVar3 = FUN_14006dd80(uVar3);
    if (uVar3 != 0) {
      memcpy(param_5,puVar2 + 3,(longlong)(int)uVar3);
    }
    if (*(int *)(param_1 + 0xd8) < *(int *)(param_1 + 0x18)) {
      local_res10 = puVar2;
      FUN_140071010(param_1 + 0xa0,&local_res10);
    }
    else {
      operator_delete(puVar2);
    }
    plVar5 = FUN_140072180((longlong *)(param_1 + 0x28),local_28,&local_38);
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -1;
    return CONCAT71((int7)((ulonglong)plVar5 >> 8),1);
  }
  return in_RAX & 0xffffffffffffff00;
}


// ==== FUN_140072b48 @ 140072b48  undefined8 FUN_140072b48(longlong param_1, ulonglong param_2, undefined8 param_3, longlong param_4)

undefined8 FUN_140072b48(longlong param_1,ulonglong param_2,undefined8 param_3,longlong param_4)

{
  uint uVar1;
  longlong lVar2;
  uint uVar3;
  
  lVar2 = *(longlong *)(param_4 + 0x38);
  __GSHandlerCheckCommon(param_2,param_4,(uint *)(lVar2 + 4));
  uVar1 = *(uint *)(lVar2 + 4);
  uVar3 = uVar1 & 2;
  if ((*(uint *)(param_1 + 4) & 0x66) == 0) {
    uVar3 = uVar1 & 1;
  }
  if (uVar3 != 0) {
                    /* WARNING: Subroutine does not return */
    __CxxFrameHandler3(param_1,param_2,param_3,param_4);
  }
  return 1;
}


// ==== FUN_140072ce0 @ 140072ce0  undefined FUN_140072ce0(void)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_140072ce0(void)

{
  atexit(FUN_1400734a4);
  _DAT_14010471c = DAT_140104ca4;
  _DAT_140104718 =
       __getmainargs(&DAT_140104700,&DAT_140104710,&DAT_140104708,DAT_140104ca0,&DAT_14010471c);
  if (_DAT_140104718 < 0) {
    _amsg_exit(8);
  }
  return;
}


// ==== FUN_140072fb8 @ 140072fb8  undefined8 FUN_140072fb8(void)

/* WARNING: Removing unreachable block (ram,0x00014007300c) */
/* WARNING: Removing unreachable block (ram,0x000140072fca) */
/* WARNING: Removing unreachable block (ram,0x000140073014) */

undefined8 FUN_140072fb8(void)

{
  DAT_140104704 = 0;
  __set_app_type(2);
  DAT_1401071c0 = _encode_pointer(0xffffffffffffffff);
  DAT_1401071c8 = DAT_1401071c0;
  *(undefined4 *)_fmode_exref = DAT_140104cac;
  *(undefined4 *)_commode_exref = DAT_140104ca8;
  FUN_14007346c();
  FUN_1400735e0();
  if (DAT_140103530 == 0) {
    __setusermatherr(&LAB_1400735dc);
  }
  if (DAT_14010352c == -1) {
    _configthreadlocale(-1);
  }
  return 0;
}


// ==== FUN_1400731d4 @ 1400731d4  undefined8 FUN_1400731d4(undefined8 * param_1)

undefined8 FUN_1400731d4(undefined8 *param_1)

{
  code *pcVar1;
  undefined8 uVar2;
  
  if (*(int *)*param_1 != -0x1f928c9d) {
    return 0;
  }
  terminate();
  pcVar1 = (code *)swi(3);
  uVar2 = (*pcVar1)();
  return uVar2;
}


// ==== FUN_140073448 @ 140073448  undefined8 FUN_140073448(void)

undefined8 FUN_140073448(void)

{
  SetUnhandledExceptionFilter(__CxxUnhandledExceptionFilter);
  return 0;
}


// ==== FUN_14007346c @ 14007346c  undefined FUN_14007346c(void)

void FUN_14007346c(void)

{
  undefined8 *puVar1;
  
  for (puVar1 = &DAT_1400d67a8; puVar1 < &DAT_1400d67a8; puVar1 = puVar1 + 1) {
    if ((code *)*puVar1 != (code *)0x0) {
      (*(code *)*puVar1)();
    }
  }
  return;
}


// ==== FUN_1400734a4 @ 1400734a4  undefined FUN_1400734a4(void)

void FUN_1400734a4(void)

{
  undefined8 *puVar1;
  
  for (puVar1 = &DAT_1400d67b8; puVar1 < &DAT_1400d67b8; puVar1 = puVar1 + 1) {
    if ((code *)*puVar1 != (code *)0x0) {
      (*(code *)*puVar1)();
    }
  }
  return;
}


// ==== FUN_1400735e0 @ 1400735e0  undefined8 FUN_1400735e0(void)

undefined8 FUN_1400735e0(void)

{
  return 0;
}


// ==== FUN_1400737c0 @ 1400737c0  undefined FUN_1400737c0(longlong * param_1, ushort param_2, uint param_3)

void FUN_1400737c0(longlong *param_1,ushort param_2,uint param_3)

{
  ulonglong uVar1;
  
  if (((param_2 & 2) != 0) &&
     (((param_3 >> 0x10 & 1) != 0 ||
      (uVar1 = FUN_14000c370(param_1[0x20]), (ulonglong)param_1[0x22] <= uVar1)))) {
    FUN_140006540(param_1,param_3);
  }
  if ((param_2 & 4) != 0) {
    if (((param_3 >> 0x10 & 1) == 0) &&
       (uVar1 = FUN_14000c370(param_1[0x21]), (ulonglong)param_1[0x24] < uVar1)) {
      return;
    }
    FUN_1400065c0(param_1,param_3);
  }
  return;
}


// ==== FUN_140073890 @ 140073890  undefined FUN_140073890(longlong * param_1)

void FUN_140073890(longlong *param_1)

{
  if ((*(uint *)(param_1 + 0x4c) & 4) != 0) {
    *(uint *)(param_1 + 0x4c) = *(uint *)(param_1 + 0x4c) & 0xfffffffb;
    FUN_1400120d0(*param_1);
  }
  return;
}


// ==== FUN_1400738c0 @ 1400738c0  undefined FUN_1400738c0(longlong * param_1)

void FUN_1400738c0(longlong *param_1)

{
  if ((*(uint *)(param_1 + 0x4c) & 2) != 0) {
    *(uint *)(param_1 + 0x4c) = *(uint *)(param_1 + 0x4c) & 0xfffffffd;
    FUN_1400120d0(*param_1);
  }
  return;
}


// ==== FUN_1400738f0 @ 1400738f0  undefined FUN_1400738f0(longlong * param_1)

void FUN_1400738f0(longlong *param_1)

{
  if ((*(uint *)(param_1 + 0x4c) & 4) == 0) {
    *(uint *)(param_1 + 0x4c) = *(uint *)(param_1 + 0x4c) | 4;
    FUN_140012070(*param_1);
  }
  return;
}


// ==== FUN_140073920 @ 140073920  undefined FUN_140073920(longlong * param_1)

void FUN_140073920(longlong *param_1)

{
  if ((*(uint *)(param_1 + 0x4c) & 2) == 0) {
    *(uint *)(param_1 + 0x4c) = *(uint *)(param_1 + 0x4c) | 2;
    FUN_140012070(*param_1);
  }
  return;
}


// ==== FUN_140073950 @ 140073950  undefined FUN_140073950(longlong * param_1)

void FUN_140073950(longlong *param_1)

{
  int iVar1;
  longlong lVar2;
  ulonglong uVar3;
  undefined8 *puVar4;
  
  if ((param_1[0x4b] == 0) && ((*(byte *)(param_1 + 0x2e) & 8) == 0)) {
    if (((*(byte *)(param_1 + 0x4c) & 1) == 0) ||
       (((*(byte *)(param_1 + 0x2c) & 4) == 0 || (lVar2 = FUN_14000c370(param_1[0x21]), lVar2 == 0))
       )) {
      if ((*(uint *)(param_1 + 0x4c) & 4) != 0) {
        *(uint *)(param_1 + 0x4c) = *(uint *)(param_1 + 0x4c) & 0xfffffffb;
        FUN_1400120d0(*param_1);
        return;
      }
    }
    else {
      uVar3 = FUN_14000c370(param_1[0x21]);
      lVar2 = FUN_140018490(param_1);
      iVar1 = (int)lVar2;
      if (((ulonglong)(longlong)iVar1 <= uVar3) && (-1 < iVar1)) {
        uVar3 = (longlong)iVar1;
      }
      if ((short)param_1[0x2f] == 0) {
        FUN_140006150((longlong)param_1);
        puVar4 = FUN_140075a50((undefined8 *)param_1[0x21],uVar3,param_1 + 0x45);
        if ((int)puVar4 != 0) {
          FUN_140006120(param_1);
          *(uint *)(param_1 + 0x4c) = *(uint *)(param_1 + 0x4c) & 0xfffffffe;
          FUN_140006640(param_1,0x20,0);
          return;
        }
        param_1[0x4b] = uVar3;
        FUN_1400186a0((longlong)param_1,uVar3);
        if ((*(uint *)(param_1 + 0x4c) & 4) == 0) {
          *(uint *)(param_1 + 0x4c) = *(uint *)(param_1 + 0x4c) | 4;
          FUN_140012070(*param_1);
          return;
        }
      }
      else if ((*(uint *)(param_1 + 0x4c) & 4) != 0) {
        *(uint *)(param_1 + 0x4c) = *(uint *)(param_1 + 0x4c) & 0xfffffffb;
        FUN_1400120d0(*param_1);
      }
    }
  }
  return;
}


// ==== FUN_140073ab0 @ 140073ab0  undefined FUN_140073ab0(longlong * param_1)

void FUN_140073ab0(longlong *param_1)

{
  uint uVar1;
  int iVar2;
  ulonglong uVar3;
  longlong lVar4;
  longlong *plVar5;
  ulonglong uVar6;
  
  if (param_1[0x4a] != 0) {
    return;
  }
  if ((*(byte *)(param_1 + 0x2e) & 8) != 0) {
    return;
  }
  uVar1 = *(uint *)(param_1 + 0x4c);
  if (((uVar1 & 1) == 0) || ((*(byte *)(param_1 + 0x2c) & 2) == 0)) {
    if ((uVar1 & 2) == 0) {
      return;
    }
    *(uint *)(param_1 + 0x4c) = uVar1 & 0xfffffffd;
    FUN_1400120d0(*param_1);
    return;
  }
  uVar3 = FUN_14000c370(param_1[0x20]);
  uVar6 = param_1[0x23];
  if (uVar6 == 0) {
    uVar6 = 0x4000;
  }
  else {
    if (uVar6 <= uVar3) goto LAB_140073b3b;
    uVar6 = uVar6 - uVar3;
  }
  lVar4 = FUN_1400183c0(param_1);
  iVar2 = (int)lVar4;
  if (((ulonglong)(longlong)iVar2 <= uVar6) && (-1 < iVar2)) {
    uVar6 = (longlong)iVar2;
  }
  if (*(short *)((longlong)param_1 + 0x176) == 0) {
    FUN_140006150((longlong)param_1);
    plVar5 = FUN_140075c30((longlong *)param_1[0x20],uVar6,param_1 + 0x40);
    if ((int)plVar5 != 0) {
      *(uint *)(param_1 + 0x4c) = *(uint *)(param_1 + 0x4c) & 0xfffffffe;
      FUN_140006640(param_1,0x20,0);
      FUN_140006120(param_1);
      return;
    }
    param_1[0x4a] = uVar6;
    FUN_140018560((longlong)param_1,uVar6);
    if ((*(uint *)(param_1 + 0x4c) & 2) != 0) {
      return;
    }
    *(uint *)(param_1 + 0x4c) = *(uint *)(param_1 + 0x4c) | 2;
    FUN_140012070(*param_1);
    return;
  }
LAB_140073b3b:
  if ((*(uint *)(param_1 + 0x4c) & 2) != 0) {
    *(uint *)(param_1 + 0x4c) = *(uint *)(param_1 + 0x4c) & 0xfffffffd;
    FUN_1400120d0(*param_1);
  }
  return;
}


// ==== FUN_140073c10 @ 140073c10  undefined FUN_140073c10(undefined8 param_1, longlong param_2, longlong * param_3)

void FUN_140073c10(undefined8 param_1,longlong param_2,longlong *param_3)

{
  longlong *plVar1;
  
  plVar1 = param_3;
  if ((undefined **)param_3[1] != &PTR_s_socket_async_1400ccde0) {
    plVar1 = (longlong *)0x0;
  }
  FUN_1400060e0((longlong)param_3);
  if (*(longlong *)(param_2 + 8) != 0) {
    FUN_140073950(plVar1);
  }
  FUN_140006940(param_3);
  return;
}


// ==== FUN_140073c70 @ 140073c70  undefined FUN_140073c70(undefined8 param_1, longlong param_2, longlong * param_3)

void FUN_140073c70(undefined8 param_1,longlong param_2,longlong *param_3)

{
  longlong *plVar1;
  
  plVar1 = param_3;
  if ((undefined **)param_3[1] != &PTR_s_socket_async_1400ccde0) {
    plVar1 = (longlong *)0x0;
  }
  FUN_1400060e0((longlong)param_3);
  if (*(longlong *)(param_2 + 0x10) != 0) {
    FUN_140073ab0(plVar1);
  }
  FUN_140006940(param_3);
  return;
}


// ==== FUN_140073cd0 @ 140073cd0  undefined8 FUN_140073cd0(longlong * param_1, ushort param_2)

undefined8 FUN_140073cd0(longlong *param_1,ushort param_2)

{
  longlong *plVar1;
  
  plVar1 = param_1;
  if ((undefined **)param_1[1] != &PTR_s_socket_async_1400ccde0) {
    plVar1 = (longlong *)0x0;
  }
  if ((*(byte *)(plVar1 + 0x4c) & 1) == 0) {
    return 0xffffffff;
  }
  if ((*(byte *)(plVar1 + 0x2e) & 8) == 0) {
    if (((param_2 & 2) != 0) &&
       (((int)param_1[0x2a] != 0 || (*(int *)((longlong)param_1 + 0x154) != 0)))) {
      FUN_140015e10(param_1 + 2,(ulonglong *)(param_1 + 0x2a));
    }
    if (((param_2 & 4) != 0) &&
       (((int)param_1[0x2b] != 0 || (*(int *)((longlong)param_1 + 0x15c) != 0)))) {
      FUN_140015e10(param_1 + 0x11,(ulonglong *)(param_1 + 0x2b));
    }
    if ((param_2 & 2) != 0) {
      FUN_140073ab0(plVar1);
    }
    if ((param_2 & 4) != 0) {
      FUN_140073950(plVar1);
    }
  }
  return 0;
}


// ==== FUN_140073da0 @ 140073da0  undefined8 FUN_140073da0(longlong * param_1, ushort param_2)

undefined8 FUN_140073da0(longlong *param_1,ushort param_2)

{
  longlong *plVar1;
  
  plVar1 = param_1;
  if ((undefined **)param_1[1] != &PTR_s_socket_async_1400ccde0) {
    plVar1 = (longlong *)0x0;
  }
  if ((param_2 & 2) != 0) {
    FUN_140014300(param_1 + 2);
    if ((*(uint *)(plVar1 + 0x4c) & 2) != 0) {
      *(uint *)(plVar1 + 0x4c) = *(uint *)(plVar1 + 0x4c) & 0xfffffffd;
      FUN_1400120d0(*plVar1);
    }
  }
  if ((param_2 & 4) != 0) {
    FUN_140014300(param_1 + 0x11);
    if ((*(uint *)(plVar1 + 0x4c) & 4) != 0) {
      *(uint *)(plVar1 + 0x4c) = *(uint *)(plVar1 + 0x4c) & 0xfffffffb;
      FUN_1400120d0(*plVar1);
    }
  }
  return 0;
}


// ==== FUN_140073e40 @ 140073e40  undefined FUN_140073e40(longlong * param_1)

void FUN_140073e40(longlong *param_1)

{
  longlong lVar1;
  longlong *plVar2;
  
  plVar2 = param_1;
  if ((undefined **)param_1[1] != &PTR_s_socket_async_1400ccde0) {
    plVar2 = (longlong *)0x0;
  }
  if ((*(uint *)(plVar2 + 0x4c) & 2) != 0) {
    *(uint *)(plVar2 + 0x4c) = *(uint *)(plVar2 + 0x4c) & 0xfffffffd;
    FUN_1400120d0(*plVar2);
  }
  if ((*(uint *)(plVar2 + 0x4c) & 4) != 0) {
    *(uint *)(plVar2 + 0x4c) = *(uint *)(plVar2 + 0x4c) & 0xfffffffb;
    FUN_1400120d0(*plVar2);
  }
  lVar1 = FUN_140075e60(param_1[0x20]);
  if ((lVar1 != -1) && ((*(byte *)(param_1 + 0x36) & 1) != 0)) {
    Ordinal_3(lVar1);
    FUN_140075e80(param_1[0x20],0xffffffffffffffff);
  }
  return;
}


// ==== FUN_140073ee0 @ 140073ee0  undefined FUN_140073ee0(longlong param_1, undefined8 param_2)

void FUN_140073ee0(longlong param_1,undefined8 param_2)

{
  undefined8 uVar1;
  undefined1 local_res8 [16];
  undefined1 local_res18 [16];
  
  uVar1 = FUN_140075e60(*(longlong *)(param_1 + 0x100));
  WSAGetOverlappedResult(uVar1,param_2,local_res18,0,local_res8);
  return;
}


// ==== FUN_140073f30 @ 140073f30  undefined FUN_140073f30(longlong param_1, undefined8 param_2, ulonglong param_3, int param_4)

void FUN_140073f30(longlong param_1,undefined8 param_2,ulonglong param_3,int param_4)

{
  undefined8 uVar1;
  ulonglong uVar2;
  longlong lVar3;
  undefined1 local_res8 [8];
  undefined1 local_res20 [8];
  
  if (*(longlong *)(param_1 + -0x48) != 0) {
    FUN_140016e30();
  }
  lVar3 = *(longlong *)(param_1 + 0x50);
  FUN_140075840(*(undefined8 **)(param_1 + -0x100),param_3);
  lVar3 = lVar3 - param_3;
  *(undefined8 *)(param_1 + 0x50) = 0;
  if (lVar3 != 0) {
    FUN_140018560(param_1 + -0x200,-lVar3);
  }
  if (param_4 == 0) {
    uVar1 = FUN_140075e60(*(longlong *)(param_1 + -0x100));
    WSAGetOverlappedResult(uVar1,param_1,local_res8,0,local_res20);
  }
  if ((*(uint *)(param_1 + 0x60) & 1) != 0) {
    if (param_4 == 0) {
      uVar1 = 0x21;
    }
    else {
      if (param_3 != 0) {
        if ((*(int *)(param_1 + -0xb0) != 0) || (*(int *)(param_1 + -0xac) != 0)) {
          FUN_140015e10((longlong *)(param_1 + -0x1f0),(ulonglong *)(param_1 + -0xb0));
        }
        uVar2 = FUN_14000c370(*(longlong *)(param_1 + -0x100));
        if (*(ulonglong *)(param_1 + -0xf0) <= uVar2) {
          FUN_140006540((longlong *)(param_1 + -0x200),0);
        }
        FUN_140073ab0((longlong *)(param_1 + -0x200));
        goto LAB_140074054;
      }
      uVar1 = 0x11;
    }
    *(uint *)(param_1 + 0x60) = *(uint *)(param_1 + 0x60) & 0xfffffffe;
    FUN_140006640((longlong *)(param_1 + -0x200),uVar1,0);
  }
LAB_140074054:
  FUN_140006940((longlong *)(param_1 + -0x200));
  return;
}


// ==== FUN_140074080 @ 140074080  undefined FUN_140074080(longlong param_1, undefined8 param_2, ulonglong param_3, int param_4)

void FUN_140074080(longlong param_1,undefined8 param_2,ulonglong param_3,int param_4)

{
  undefined8 uVar1;
  ulonglong uVar2;
  longlong lVar3;
  undefined1 local_res8 [8];
  undefined1 local_res20 [8];
  
  if (*(longlong *)(param_1 + -0x70) != 0) {
    FUN_140016e30();
  }
  lVar3 = *(longlong *)(param_1 + 0x30);
  FUN_140075950(*(longlong **)(param_1 + -0x120),param_3);
  lVar3 = lVar3 - param_3;
  *(undefined8 *)(param_1 + 0x30) = 0;
  if (lVar3 != 0) {
    FUN_1400186a0(param_1 + -0x228,-lVar3);
  }
  if (param_4 == 0) {
    uVar1 = FUN_140075e60(*(longlong *)(param_1 + -0x128));
    WSAGetOverlappedResult(uVar1,param_1,local_res8,0,local_res20);
  }
  if ((*(uint *)(param_1 + 0x38) & 1) != 0) {
    if (param_4 == 0) {
      uVar1 = 0x22;
    }
    else {
      if (param_3 != 0) {
        if ((*(int *)(param_1 + -0xd0) != 0) || (*(int *)(param_1 + -0xcc) != 0)) {
          FUN_140015e10((longlong *)(param_1 + -0x1a0),(ulonglong *)(param_1 + -0xd0));
        }
        uVar2 = FUN_14000c370(*(longlong *)(param_1 + -0x120));
        if (uVar2 <= *(ulonglong *)(param_1 + -0x108)) {
          FUN_1400065c0((longlong *)(param_1 + -0x228),0);
        }
        FUN_140073950((longlong *)(param_1 + -0x228));
        goto LAB_1400741a4;
      }
      uVar1 = 0x12;
    }
    *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) & 0xfffffffe;
    FUN_140006640((longlong *)(param_1 + -0x228),uVar1,0);
  }
LAB_1400741a4:
  FUN_140006940((longlong *)(param_1 + -0x228));
  return;
}


// ==== FUN_1400741d0 @ 1400741d0  undefined FUN_1400741d0(longlong * param_1)

void FUN_1400741d0(longlong *param_1)

{
  longlong *plVar1;
  
  plVar1 = param_1;
  if ((undefined **)param_1[1] != &PTR_s_socket_async_1400ccde0) {
    plVar1 = (longlong *)0x0;
  }
  *(uint *)(plVar1 + 0x4c) = *(uint *)(plVar1 + 0x4c) | 1;
  FUN_140006c20(param_1);
  FUN_140073cd0(param_1,*(ushort *)(param_1 + 0x2c));
  return;
}


// ==== FUN_140074210 @ 140074210  undefined8 FUN_140074210(longlong * param_1)

undefined8 FUN_140074210(longlong *param_1)

{
  undefined *puVar1;
  longlong lVar2;
  
  puVar1 = FUN_140074b70();
  if ((undefined **)param_1[1] == &PTR_s_socket_async_1400ccde0) {
    lVar2 = FUN_140074eb0(*param_1);
    if (((lVar2 != 0) && (puVar1 != (undefined *)0x0)) && (*(longlong *)(puVar1 + 8) != 0)) {
      return 1;
    }
  }
  return 0;
}


// ==== FUN_140074270 @ 140074270  undefined FUN_140074270(longlong * param_1, undefined8 param_2, short * param_3, undefined4 param_4)

void FUN_140074270(longlong *param_1,undefined8 param_2,short *param_3,undefined4 param_4)

{
  int iVar1;
  undefined *puVar2;
  longlong *plVar3;
  undefined1 auStack_108 [32];
  undefined4 local_e8;
  undefined8 local_e0;
  longlong *local_d8;
  undefined2 local_c8 [2];
  undefined4 local_c4;
  undefined8 local_c0;
  undefined8 local_b8;
  ulonglong local_48;
  
  local_48 = DAT_140103510 ^ (ulonglong)auStack_108;
  plVar3 = param_1;
  if ((undefined **)param_1[1] != &PTR_s_socket_async_1400ccde0) {
    plVar3 = (longlong *)0x0;
  }
  puVar2 = FUN_140074b70();
  memset(local_c8,0,0x80);
  if (*param_3 == 2) {
    local_c4 = 0;
    local_c8[0] = 2;
  }
  else {
    if (*param_3 != 0x17) goto LAB_14007439a;
    local_c8[0] = 0x17;
    local_c0 = 0;
    local_b8 = 0;
  }
  iVar1 = Ordinal_2(param_2,local_c8,0x80);
  if ((-1 < iVar1) || (iVar1 = Ordinal_111(), iVar1 == 0x2726)) {
    FUN_140012070(*param_1);
    FUN_140006150((longlong)param_1);
    local_d8 = plVar3 + 0x3b;
    local_e0 = 0;
    local_e8 = 0;
    iVar1 = (**(code **)(puVar2 + 8))(param_2,param_3,param_4,0);
    if ((iVar1 == 0) && (iVar1 = Ordinal_111(), iVar1 != 0x3e5)) {
      FUN_1400120d0(*param_1);
      FUN_140006120(param_1);
    }
  }
LAB_14007439a:
  __security_check_cookie(local_48 ^ (ulonglong)auStack_108);
  return;
}


// ==== FUN_1400743c0 @ 1400743c0  undefined8 FUN_1400743c0(longlong * param_1, int param_2, longlong * param_3)

undefined8 FUN_1400743c0(longlong *param_1,int param_2,longlong *param_3)

{
  int iVar1;
  longlong lVar2;
  undefined8 *puVar3;
  longlong *plVar4;
  
  if (param_2 == 0) {
    lVar2 = FUN_140075e60(param_1[0x20]);
    if (*param_3 == lVar2) {
      return 0;
    }
    puVar3 = (undefined8 *)FUN_140074eb0(*param_1);
    if ((puVar3 != (undefined8 *)0x0) &&
       (iVar1 = FUN_1400748b0(puVar3,(HANDLE)*param_3,1), -1 < iVar1)) {
      FUN_140075e80(param_1[0x20],*param_3);
      FUN_140075e80(param_1[0x21],*param_3);
      return 0;
    }
  }
  else {
    if (param_2 == 1) {
      lVar2 = FUN_140075e60(param_1[0x20]);
      *param_3 = lVar2;
      return 0;
    }
    if (param_2 == 3) {
      plVar4 = param_1;
      if ((undefined **)param_1[1] != &PTR_s_socket_async_1400ccde0) {
        plVar4 = (longlong *)0x0;
      }
      lVar2 = FUN_140075e60(param_1[0x20]);
      if ((lVar2 != -1) && ((*(byte *)(plVar4 + 0x36) & 1) != 0)) {
        Ordinal_3(lVar2);
        FUN_140075e80(param_1[0x20],0xffffffffffffffff);
      }
      *(uint *)(plVar4 + 0x4c) = *(uint *)(plVar4 + 0x4c) & 0xfffffffe;
      return 0;
    }
  }
  return 0xffffffff;
}


// ==== FUN_1400744d0 @ 1400744d0  undefined FUN_1400744d0(longlong param_1, undefined8 param_2, undefined8 param_3, int param_4)

void FUN_1400744d0(longlong param_1,undefined8 param_2,undefined8 param_3,int param_4)

{
  undefined8 uVar1;
  longlong lVar2;
  undefined1 local_res8 [8];
  undefined1 local_res20 [8];
  undefined8 in_stack_ffffffffffffffd8;
  uint uVar3;
  
  uVar3 = (uint)((ulonglong)in_stack_ffffffffffffffd8 >> 0x20);
  if (*(longlong *)(param_1 + -0x20) != 0) {
    FUN_140016e30();
  }
  *(uint *)(param_1 + -0x68) = *(uint *)(param_1 + -0x68) & 0xfffffff7;
  uVar1 = FUN_140075e60(*(longlong *)(param_1 + -0xd8));
  Ordinal_21(uVar1,0xffff,0x7010,0,(ulonglong)uVar3 << 0x20);
  if (param_4 == 0) {
    uVar1 = FUN_140075e60(*(longlong *)(param_1 + -0xd8));
    WSAGetOverlappedResult(uVar1,param_1,local_res8,0,local_res20);
  }
  else {
    lVar2 = param_1 + -0x1d8;
    if (*(undefined ***)(param_1 + -0x1d0) != &PTR_s_socket_async_1400ccde0) {
      lVar2 = 0;
    }
    *(uint *)(lVar2 + 0x260) = *(uint *)(lVar2 + 0x260) | 1;
    FUN_140006c20((longlong *)(param_1 + -0x1d8));
    FUN_140073cd0((longlong *)(param_1 + -0x1d8),*(ushort *)(param_1 + -0x78));
  }
  uVar1 = 0x20;
  if (param_4 != 0) {
    uVar1 = 0x80;
  }
  FUN_140006640((longlong *)(param_1 + -0x1d8),uVar1,0);
  FUN_1400120d0(*(longlong *)(param_1 + -0x1d8));
  FUN_140006940((longlong *)(param_1 + -0x1d8));
  return;
}


// ==== FUN_1400745d0 @ 1400745d0  longlong * FUN_1400745d0(longlong param_1, HANDLE param_2, uint param_3)

longlong * FUN_1400745d0(longlong param_1,HANDLE param_2,uint param_3)

{
  int iVar1;
  DWORD DVar2;
  undefined8 *puVar3;
  longlong *plVar4;
  longlong lVar5;
  undefined8 uVar6;
  
  puVar3 = (undefined8 *)FUN_140074eb0(param_1);
  if (puVar3 == (undefined8 *)0x0) {
    return (longlong *)0x0;
  }
  if (((-1 < (longlong)param_2) && (iVar1 = FUN_1400748b0(puVar3,param_2,1), iVar1 < 0)) &&
     (DVar2 = GetLastError(), DVar2 != 0x57)) {
    return (longlong *)0x0;
  }
  plVar4 = (longlong *)FUN_140011850(1,0x268);
  if (plVar4 != (longlong *)0x0) {
    lVar5 = FUN_140075a00(param_2);
    plVar4[0x20] = lVar5;
    if (lVar5 != 0) {
      lVar5 = FUN_140075a00(param_2);
      plVar4[0x21] = lVar5;
      if (lVar5 != 0) {
        uVar6 = FUN_140007020(plVar4,param_1,0x1400ccde0,(ulonglong)(param_3 | 2));
        if ((int)uVar6 < 0) {
          FUN_140006a60(plVar4);
          return (longlong *)0x0;
        }
        FUN_14000d6e0(plVar4[0x20],0x140073c70,(longlong)plVar4);
        FUN_14000d6e0(plVar4[0x21],0x140073c10,(longlong)plVar4);
        FUN_140074750(plVar4 + 0x3b,FUN_1400744d0);
        FUN_140074750(plVar4 + 0x40,FUN_140073f30);
        FUN_140074750(plVar4 + 0x45,FUN_140074080);
        FUN_140006c20(plVar4);
        *(uint *)(plVar4 + 0x4c) = *(uint *)(plVar4 + 0x4c) & 0xfffffffe;
        *(uint *)(plVar4 + 0x4c) = *(uint *)(plVar4 + 0x4c) | (uint)(-1 < (longlong)param_2);
        return plVar4;
      }
      FUN_14000c300((undefined8 *)plVar4[0x20]);
    }
    FUN_1400119c0(plVar4);
  }
  return (longlong *)0x0;
}


// ==== FUN_140074750 @ 140074750  undefined FUN_140074750(undefined8 * param_1, undefined8 param_2)

void FUN_140074750(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = param_2;
  return;
}


// ==== FUN_140074780 @ 140074780  undefined FUN_140074780(undefined8 * param_1)

void FUN_140074780(undefined8 *param_1)

{
  short *psVar1;
  short sVar2;
  HANDLE CompletionPort;
  BOOL BVar3;
  DWORD dwMilliseconds;
  PULONG_PTR lpCompletionKey;
  LPOVERLAPPED *lpOverlapped;
  DWORD local_res8 [2];
  LPOVERLAPPED local_res10;
  ulonglong local_res18;
  
  dwMilliseconds = *(DWORD *)((longlong)param_1 + 0x34);
  CompletionPort = (HANDLE)*param_1;
  lpOverlapped = &local_res10;
  if ((int)dwMilliseconds < 1) {
    dwMilliseconds = 0xffffffff;
  }
  lpCompletionKey = &local_res18;
  local_res10 = (LPOVERLAPPED)0x0;
  local_res18 = 0;
  local_res8[0] = 0;
  BVar3 = GetQueuedCompletionStatus
                    (CompletionPort,local_res8,lpCompletionKey,lpOverlapped,dwMilliseconds);
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
  sVar2 = *(short *)((longlong)param_1 + 0x32);
  do {
    if (sVar2 != 0) {
LAB_14007486e:
      psVar1 = (short *)(param_1 + 8);
      *psVar1 = *psVar1 + -1;
      if (*psVar1 == 0) {
        ReleaseSemaphore((HANDLE)param_1[9],1,(LPLONG)0x0);
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
      return;
    }
    LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
    if (local_res18 == 0xffffffffffffffff) {
      if (local_res10 == (LPOVERLAPPED)0x0) goto LAB_140074858;
    }
    else {
      if (local_res10 == (LPOVERLAPPED)0x0) {
LAB_140074858:
        FUN_1400191c0("GetQueuedCompletionStatus exited with no event.",local_res18,lpCompletionKey,
                      lpOverlapped);
        EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
        goto LAB_14007486e;
      }
      (*(code *)local_res10[1].Internal)(local_res10,local_res18,local_res8[0],BVar3);
    }
    lpOverlapped = &local_res10;
    lpCompletionKey = &local_res18;
    local_res10 = (LPOVERLAPPED)0x0;
    local_res18 = 0;
    local_res8[0] = 0;
    BVar3 = GetQueuedCompletionStatus
                      (CompletionPort,local_res8,lpCompletionKey,lpOverlapped,dwMilliseconds);
    EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
    sVar2 = *(short *)((longlong)param_1 + 0x32);
  } while( true );
}


// ==== FUN_1400748b0 @ 1400748b0  int FUN_1400748b0(undefined8 * param_1, HANDLE param_2, ULONG_PTR param_3)

int FUN_1400748b0(undefined8 *param_1,HANDLE param_2,ULONG_PTR param_3)

{
  HANDLE pvVar1;
  
  pvVar1 = CreateIoCompletionPort(param_2,(HANDLE)*param_1,param_3,(int)*(short *)(param_1 + 6));
  return (pvVar1 != (HANDLE)0x0) - 1;
}


// ==== FUN_1400748e0 @ 1400748e0  undefined8 FUN_1400748e0(undefined8 param_1, undefined8 param_2)

undefined8 FUN_1400748e0(undefined8 param_1,undefined8 param_2)

{
  undefined4 local_res18 [2];
  undefined8 local_res20;
  
  local_res20 = 0;
  local_res18[0] = 0;
  WSAIoctl(param_1,0xc8000006,param_2,0x10,&local_res20,8,local_res18,0,0);
  return local_res20;
}


// ==== FUN_140074930 @ 140074930  undefined FUN_140074930(undefined8 * param_1)

void FUN_140074930(undefined8 *param_1)

{
  longlong lVar1;
  undefined1 auStack_a8 [32];
  undefined8 *local_88;
  undefined4 local_80;
  undefined4 *local_78;
  undefined8 local_70;
  undefined8 local_68;
  undefined4 local_58 [2];
  undefined8 local_50;
  undefined4 local_48;
  undefined2 local_44;
  undefined2 local_42;
  undefined1 local_40;
  undefined1 local_3f;
  undefined1 local_3e;
  undefined1 local_3d;
  undefined1 local_3c;
  undefined1 local_3b;
  undefined1 local_3a;
  undefined1 local_39;
  undefined4 local_38;
  undefined2 local_34;
  undefined2 local_32;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  undefined4 local_28;
  undefined2 local_24;
  undefined2 local_22;
  undefined1 local_20;
  undefined1 local_1f;
  undefined1 local_1e;
  undefined1 local_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_a8;
  local_44 = 0xcbac;
  local_24 = 0xcbac;
  local_42 = 0x11cf;
  local_22 = 0x11cf;
  local_34 = 0xddf3;
  local_48 = 0xb5367df1;
  local_40 = 0x95;
  local_3f = 0xca;
  local_3e = 0;
  local_3d = 0x80;
  local_3c = 0x5f;
  local_3b = 0x48;
  local_3a = 0xa1;
  local_39 = 0x92;
  local_38 = 0x25a207b9;
  local_32 = 0x4660;
  local_30 = 0x8e;
  local_2f = 0xe9;
  local_2e = 0x76;
  local_2d = 0xe5;
  local_2c = 0x8c;
  local_2b = 0x74;
  local_2a = 6;
  local_29 = 0x3e;
  local_28 = 0xb5367df2;
  local_20 = 0x95;
  local_1f = 0xca;
  local_1e = 0;
  local_1d = 0x80;
  local_1c = 0x5f;
  local_1b = 0x48;
  local_1a = 0xa1;
  local_19 = 0x92;
  lVar1 = Ordinal_23(2);
  if (lVar1 != -1) {
    local_78 = local_58;
    local_68 = 0;
    local_70 = 0;
    local_88 = &local_50;
    local_80 = 8;
    local_50 = 0;
    local_58[0] = 0;
    WSAIoctl(lVar1,0xc8000006,&local_48,0x10);
    local_68 = 0;
    local_70 = 0;
    local_78 = local_58;
    local_88 = &local_50;
    local_80 = 8;
    *param_1 = local_50;
    local_50 = 0;
    local_58[0] = 0;
    WSAIoctl(lVar1,0xc8000006,&local_38,0x10);
    local_68 = 0;
    local_70 = 0;
    local_78 = local_58;
    local_88 = &local_50;
    local_80 = 8;
    param_1[1] = local_50;
    local_50 = 0;
    local_58[0] = 0;
    WSAIoctl(lVar1,0xc8000006,&local_28,0x10);
    param_1[2] = local_50;
    Ordinal_3(lVar1);
    DAT_140104cc8 = 1;
  }
  __security_check_cookie(local_18 ^ (ulonglong)auStack_a8);
  return;
}


// ==== FUN_140074b70 @ 140074b70  undefined * FUN_140074b70(void)

undefined * FUN_140074b70(void)

{
  return &DAT_140104cb0;
}


// ==== FUN_140074b80 @ 140074b80  undefined8 * FUN_140074b80(DWORD param_1)

undefined8 * FUN_140074b80(DWORD param_1)

{
  short sVar1;
  undefined8 *_ArgList;
  void *pvVar2;
  HANDLE pvVar3;
  uintptr_t uVar4;
  ulonglong uVar5;
  uint uVar6;
  ulonglong uVar7;
  
  if (DAT_140104cc8 == 0) {
    FUN_140074930((undefined8 *)&DAT_140104cb0);
  }
  _ArgList = (undefined8 *)FUN_140011850(1,0x50);
  if (_ArgList == (undefined8 *)0x0) {
    return (undefined8 *)0x0;
  }
  if ((int)param_1 < 1) {
    param_1 = 2;
  }
  sVar1 = (short)param_1 * 2;
  *(short *)(_ArgList + 6) = sVar1;
  pvVar2 = FUN_140011850((longlong)sVar1,8);
  _ArgList[7] = pvVar2;
  if (pvVar2 != (void *)0x0) {
    pvVar3 = CreateIoCompletionPort((HANDLE)0xffffffffffffffff,(HANDLE)0x0,0,param_1);
    *(undefined4 *)((longlong)_ArgList + 0x34) = 0xffffffff;
    *_ArgList = pvVar3;
    if (pvVar3 == (HANDLE)0x0) goto LAB_140074ca3;
    pvVar3 = CreateSemaphoreA((LPSECURITY_ATTRIBUTES)0x0,0,1,(LPCSTR)0x0);
    _ArgList[9] = pvVar3;
    if (pvVar3 != (HANDLE)0x0) {
      uVar5 = 0;
      uVar7 = uVar5;
      if (0 < *(short *)(_ArgList + 6)) {
        do {
          uVar4 = _beginthread(FUN_140074780,0,_ArgList);
          if (uVar4 == 0xffffffffffffffff) goto LAB_140074c95;
          uVar6 = (int)uVar7 + 1;
          *(uintptr_t *)(uVar5 + _ArgList[7]) = uVar4;
          *(short *)(_ArgList + 8) = *(short *)(_ArgList + 8) + 1;
          uVar5 = uVar5 + 8;
          uVar7 = (ulonglong)uVar6;
        } while ((int)uVar6 < (int)*(short *)(_ArgList + 6));
      }
      InitializeCriticalSectionAndSpinCount((LPCRITICAL_SECTION)(_ArgList + 1),1000);
      return _ArgList;
    }
  }
LAB_140074c95:
  if ((HANDLE)*_ArgList != (HANDLE)0x0) {
    CloseHandle((HANDLE)*_ArgList);
  }
LAB_140074ca3:
  if ((void *)_ArgList[7] != (void *)0x0) {
    FUN_1400119c0((void *)_ArgList[7]);
  }
  if ((HANDLE)_ArgList[9] != (HANDLE)0x0) {
    CloseHandle((HANDLE)_ArgList[9]);
  }
  FUN_1400119c0(_ArgList);
  return (undefined8 *)0x0;
}


// ==== FUN_140074ce0 @ 140074ce0  undefined FUN_140074ce0(undefined8 * param_1)

void FUN_140074ce0(undefined8 *param_1)

{
  DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
  CloseHandle((HANDLE)*param_1);
  CloseHandle((HANDLE)param_1[9]);
  FUN_1400119c0((void *)param_1[7]);
  FUN_1400119c0(param_1);
  return;
}


// ==== FUN_140074d20 @ 140074d20  int FUN_140074d20(undefined8 * param_1)

int FUN_140074d20(undefined8 *param_1)

{
  byte bVar1;
  byte bVar2;
  BOOL BVar3;
  int iVar4;
  
  bVar1 = 1;
  iVar4 = 0;
  bVar2 = 1;
  if (0 < *(short *)(param_1 + 6)) {
    do {
      bVar1 = bVar2;
      BVar3 = PostQueuedCompletionStatus((HANDLE)*param_1,0,0xffffffffffffffff,(LPOVERLAPPED)0x0);
      if (BVar3 == 0) {
        bVar1 = 0;
      }
      iVar4 = iVar4 + 1;
      bVar2 = bVar1;
    } while (iVar4 < *(short *)(param_1 + 6));
  }
  return bVar1 - 1;
}


// ==== FUN_140074d90 @ 140074d90  undefined8 FUN_140074d90(undefined8 * param_1, DWORD param_2)

undefined8 FUN_140074d90(undefined8 *param_1,DWORD param_2)

{
  short sVar1;
  undefined8 uVar2;
  int iVar3;
  DWORD dwMilliseconds;
  
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
  *(undefined2 *)((longlong)param_1 + 0x32) = 1;
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
  iVar3 = 0;
  if (0 < *(short *)(param_1 + 6)) {
    do {
      PostQueuedCompletionStatus((HANDLE)*param_1,0,0xffffffffffffffff,(LPOVERLAPPED)0x0);
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(short *)(param_1 + 6));
  }
  dwMilliseconds = 0xffffffff;
  if (-1 < (int)param_2) {
    dwMilliseconds = param_2;
  }
  WaitForSingleObject((HANDLE)param_1[9],dwMilliseconds);
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
  sVar1 = *(short *)(param_1 + 8);
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
  if (sVar1 == 0) {
    DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
    CloseHandle((HANDLE)*param_1);
    CloseHandle((HANDLE)param_1[9]);
    FUN_1400119c0((void *)param_1[7]);
    FUN_1400119c0(param_1);
    uVar2 = 0;
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


// ==== FUN_140074e80 @ 140074e80  int FUN_140074e80(undefined8 * param_1, LPOVERLAPPED param_2, ULONG_PTR param_3, DWORD param_4)

int FUN_140074e80(undefined8 *param_1,LPOVERLAPPED param_2,ULONG_PTR param_3,DWORD param_4)

{
  BOOL BVar1;
  
  BVar1 = PostQueuedCompletionStatus((HANDLE)*param_1,param_4,param_3,param_2);
  return (BVar1 != 0) - 1;
}


// ==== FUN_140074eb0 @ 140074eb0  undefined8 FUN_140074eb0(longlong param_1)

undefined8 FUN_140074eb0(longlong param_1)

{
  return *(undefined8 *)(param_1 + 0x1f0);
}


// ==== FUN_140074ec0 @ 140074ec0  undefined8 FUN_140074ec0(int * param_1, int param_2)

undefined8 FUN_140074ec0(int *param_1,int param_2)

{
  size_t sVar1;
  longlong lVar2;
  
  sVar1 = (ulonglong)(param_2 - 1) * 8 + 0x10;
  lVar2 = FUN_1400119a0(*(void **)(param_1 + 2),sVar1);
  *(longlong *)(param_1 + 2) = lVar2;
  if (lVar2 != 0) {
    lVar2 = FUN_1400119a0(*(void **)(param_1 + 4),sVar1);
    *(longlong *)(param_1 + 4) = lVar2;
    if (lVar2 != 0) {
      param_1[1] = 1;
      *param_1 = param_2;
      return 0;
    }
  }
  return 0xffffffff;
}


// ==== FUN_140074f40 @ 140074f40  uint FUN_140074f40(uint * param_1, int * param_2, undefined8 param_3, int param_4)

uint FUN_140074f40(uint *param_1,int *param_2,undefined8 param_3,int param_4)

{
  size_t sVar1;
  uint uVar2;
  longlong lVar3;
  uint *puVar4;
  
  if (param_4 == 0) {
    puVar4 = *(uint **)(param_1 + 4);
    if (0 < param_2[1]) {
      return 0;
    }
  }
  else {
    puVar4 = *(uint **)(param_1 + 2);
    if (0 < *param_2) {
      return 0;
    }
  }
  if (*puVar4 == *param_1) {
    uVar2 = *param_1 * 2;
    sVar1 = (ulonglong)(uVar2 - 1) * 8 + 0x10;
    lVar3 = FUN_1400119a0(*(void **)(param_1 + 2),sVar1);
    *(longlong *)(param_1 + 2) = lVar3;
    if (lVar3 != 0) {
      puVar4 = (uint *)FUN_1400119a0(*(void **)(param_1 + 4),sVar1);
      *(uint **)(param_1 + 4) = puVar4;
      if (puVar4 != (uint *)0x0) {
        param_1[1] = 1;
        *param_1 = uVar2;
        if (param_4 != 0) {
          puVar4 = *(uint **)(param_1 + 2);
        }
        goto LAB_140074fef;
      }
    }
    uVar2 = 0xffffffff;
  }
  else {
LAB_140074fef:
    *(undefined8 *)(puVar4 + (ulonglong)*puVar4 * 2 + 2) = param_3;
    if (param_4 == 0) {
      param_2[1] = *puVar4 + 1;
    }
    else {
      *param_2 = *puVar4 + 1;
    }
    uVar2 = *puVar4;
    *puVar4 = uVar2 + 1;
  }
  return uVar2;
}


// ==== FUN_140075040 @ 140075040  undefined8 FUN_140075040(longlong param_1, longlong param_2, int * param_3, int param_4)

undefined8 FUN_140075040(longlong param_1,longlong param_2,int *param_3,int param_4)

{
  longlong lVar1;
  int *piVar2;
  uint uVar3;
  uint *puVar5;
  int iVar4;
  
  if (param_4 == 0) {
    puVar5 = *(uint **)(param_2 + 0x10);
    iVar4 = param_3[1];
    param_3[1] = 0;
  }
  else {
    puVar5 = *(uint **)(param_2 + 8);
    iVar4 = *param_3;
    *param_3 = 0;
  }
  uVar3 = iVar4 - 1;
  if (-1 < (int)uVar3) {
    *puVar5 = *puVar5 - 1;
    if (*puVar5 != uVar3) {
      lVar1 = *(longlong *)(puVar5 + (ulonglong)*puVar5 * 2 + 2);
      *(longlong *)(puVar5 + (longlong)(int)uVar3 * 2 + 2) = lVar1;
      piVar2 = (int *)FUN_14001a880((longlong *)(param_1 + 0x128),lVar1);
      if (piVar2 != (int *)0x0) {
        if (param_4 != 0) {
          *piVar2 = iVar4;
          return 0;
        }
        piVar2[1] = iVar4;
      }
    }
  }
  return 0;
}


// ==== FUN_1400750d0 @ 1400750d0  undefined4 * FUN_1400750d0(longlong param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

undefined4 *
FUN_1400750d0(longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined4 *puVar1;
  void *pvVar2;
  undefined8 uVar3;
  
  uVar3 = 0x38;
  puVar1 = (undefined4 *)FUN_140011850(1,0x38);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = 0x20;
    pvVar2 = FUN_140011830(0x108);
    *(void **)(puVar1 + 2) = pvVar2;
    if (pvVar2 != (void *)0x0) {
      pvVar2 = FUN_140011830(0x108);
      *(void **)(puVar1 + 4) = pvVar2;
      if (pvVar2 != (void *)0x0) {
        pvVar2 = FUN_140011830(0x108);
        *(void **)(puVar1 + 6) = pvVar2;
        if (pvVar2 != (void *)0x0) {
          pvVar2 = FUN_140011830(0x108);
          *(void **)(puVar1 + 8) = pvVar2;
          if (pvVar2 != (void *)0x0) {
            pvVar2 = FUN_140011830(0x108);
            *(void **)(puVar1 + 10) = pvVar2;
            if (pvVar2 != (void *)0x0) {
              **(undefined4 **)(puVar1 + 4) = 0;
              **(undefined4 **)(puVar1 + 2) = 0;
              **(undefined4 **)(puVar1 + 10) = 0;
              **(undefined4 **)(puVar1 + 8) = 0;
              **(undefined4 **)(puVar1 + 6) = 0;
              uVar3 = FUN_14001b590(param_1,uVar3,param_3,param_4);
              if ((int)uVar3 < 0) {
                puVar1[0xc] = puVar1[0xc] | 1;
              }
              FUN_140008930((int *)(param_1 + 0x2a0),0);
              return puVar1;
            }
          }
        }
      }
    }
    if (*(void **)(puVar1 + 2) != (void *)0x0) {
      FUN_1400119c0(*(void **)(puVar1 + 2));
    }
    if (*(void **)(puVar1 + 4) != (void *)0x0) {
      FUN_1400119c0(*(void **)(puVar1 + 4));
    }
    if (*(void **)(puVar1 + 6) != (void *)0x0) {
      FUN_1400119c0(*(void **)(puVar1 + 6));
    }
    if (*(void **)(puVar1 + 8) != (void *)0x0) {
      FUN_1400119c0(*(void **)(puVar1 + 8));
    }
    if (*(void **)(puVar1 + 10) != (void *)0x0) {
      FUN_1400119c0(*(void **)(puVar1 + 10));
    }
    FUN_1400119c0(puVar1);
  }
  return (undefined4 *)0x0;
}


// ==== FUN_140075210 @ 140075210  undefined8 FUN_140075210(longlong param_1, undefined8 param_2, undefined8 param_3, ushort param_4, int * param_5)

undefined8
FUN_140075210(longlong param_1,undefined8 param_2,undefined8 param_3,ushort param_4,int *param_5)

{
  size_t sVar1;
  uint uVar2;
  uint *puVar3;
  longlong lVar4;
  uint *puVar5;
  undefined8 uVar6;
  
  puVar3 = *(uint **)(param_1 + 8);
  if (((param_4 & 8) != 0) && ((puVar3[0xc] & 1) != 0)) {
    return 0xffffffff;
  }
  if ((param_4 & 6) == 0) {
    return 0;
  }
  if (((param_4 & 2) != 0) && (puVar5 = *(uint **)(puVar3 + 2), *param_5 < 1)) {
    if (*puVar5 == *puVar3) {
      uVar2 = *puVar3 * 2;
      sVar1 = (ulonglong)(uVar2 - 1) * 8 + 0x10;
      lVar4 = FUN_1400119a0(puVar5,sVar1);
      *(longlong *)(puVar3 + 2) = lVar4;
      if (lVar4 != 0) {
        lVar4 = FUN_1400119a0(*(void **)(puVar3 + 4),sVar1);
        *(longlong *)(puVar3 + 4) = lVar4;
        if (lVar4 != 0) {
          puVar5 = *(uint **)(puVar3 + 2);
          puVar3[1] = 1;
          *puVar3 = uVar2;
          goto LAB_1400752c3;
        }
      }
    }
    else {
LAB_1400752c3:
      *(undefined8 *)(puVar5 + (ulonglong)*puVar5 * 2 + 2) = param_2;
      *param_5 = *puVar5 + 1;
      uVar2 = *puVar5;
      *puVar5 = uVar2 + 1;
      if (-1 < (int)uVar2) goto LAB_1400752df;
    }
    goto LAB_140075352;
  }
LAB_1400752df:
  if (((param_4 & 4) == 0) || (puVar5 = *(uint **)(puVar3 + 4), 0 < param_5[1])) {
LAB_140075357:
    uVar6 = 0;
  }
  else {
    if (*puVar5 == *puVar3) {
      uVar2 = *puVar3 * 2;
      sVar1 = (ulonglong)(uVar2 - 1) * 8 + 0x10;
      lVar4 = FUN_1400119a0(*(void **)(puVar3 + 2),sVar1);
      *(longlong *)(puVar3 + 2) = lVar4;
      if (lVar4 != 0) {
        puVar5 = (uint *)FUN_1400119a0(*(void **)(puVar3 + 4),sVar1);
        *(uint **)(puVar3 + 4) = puVar5;
        if (puVar5 != (uint *)0x0) {
          puVar3[1] = 1;
          *puVar3 = uVar2;
          goto LAB_140075339;
        }
      }
    }
    else {
LAB_140075339:
      *(undefined8 *)(puVar5 + (ulonglong)*puVar5 * 2 + 2) = param_2;
      param_5[1] = *puVar5 + 1;
      uVar2 = *puVar5;
      *puVar5 = uVar2 + 1;
      if (-1 < (int)uVar2) goto LAB_140075357;
    }
LAB_140075352:
    uVar6 = 0xffffffff;
  }
  return uVar6;
}


// ==== FUN_140075380 @ 140075380  undefined8 FUN_140075380(longlong param_1, undefined8 param_2, undefined8 param_3, ushort param_4, int * param_5)

undefined8
FUN_140075380(longlong param_1,undefined8 param_2,undefined8 param_3,ushort param_4,int *param_5)

{
  int iVar1;
  uint *puVar2;
  longlong lVar3;
  int *piVar4;
  longlong lVar5;
  uint uVar6;
  
  lVar5 = *(longlong *)(param_1 + 8);
  if ((param_4 & 2) != 0) {
    iVar1 = *param_5;
    puVar2 = *(uint **)(lVar5 + 8);
    *param_5 = 0;
    uVar6 = iVar1 - 1;
    if (-1 < (int)uVar6) {
      *puVar2 = *puVar2 - 1;
      if (*puVar2 != uVar6) {
        lVar3 = *(longlong *)(puVar2 + (ulonglong)*puVar2 * 2 + 2);
        *(longlong *)(puVar2 + (longlong)(int)uVar6 * 2 + 2) = lVar3;
        piVar4 = (int *)FUN_14001a880((longlong *)(param_1 + 0x128),lVar3);
        if (piVar4 != (int *)0x0) {
          *piVar4 = iVar1;
        }
      }
    }
  }
  if ((param_4 & 4) != 0) {
    iVar1 = param_5[1];
    puVar2 = *(uint **)(lVar5 + 0x10);
    param_5[1] = 0;
    uVar6 = iVar1 - 1;
    if (-1 < (int)uVar6) {
      *puVar2 = *puVar2 - 1;
      if (*puVar2 != uVar6) {
        lVar5 = *(longlong *)(puVar2 + (ulonglong)*puVar2 * 2 + 2);
        *(longlong *)(puVar2 + (longlong)(int)uVar6 * 2 + 2) = lVar5;
        lVar5 = FUN_14001a880((longlong *)(param_1 + 0x128),lVar5);
        if (lVar5 != 0) {
          *(int *)(lVar5 + 4) = iVar1;
        }
      }
    }
  }
  return 0;
}


// ==== FUN_140075480 @ 140075480  int FUN_140075480(longlong param_1, int * param_2)

int FUN_140075480(longlong param_1,int *param_2)

{
  size_t sVar1;
  int *piVar2;
  uint *puVar3;
  uint *puVar4;
  DWORD dwMilliseconds;
  int iVar5;
  longlong lVar6;
  uint uVar7;
  ulonglong uVar8;
  uint uVar10;
  ulonglong uVar9;
  
  piVar2 = *(int **)(param_1 + 8);
  if (piVar2[1] == 0) {
LAB_1400754fe:
    puVar3 = *(uint **)(piVar2 + 2);
    puVar4 = *(uint **)(piVar2 + 6);
    *puVar4 = *puVar3;
    memcpy(puVar4 + 2,puVar3 + 2,(ulonglong)*puVar3 << 3);
    puVar3 = *(uint **)(piVar2 + 4);
    puVar4 = *(uint **)(piVar2 + 10);
    *puVar4 = *puVar3;
    memcpy(puVar4 + 2,puVar3 + 2,(ulonglong)*puVar3 << 3);
    puVar3 = *(uint **)(piVar2 + 4);
    puVar4 = *(uint **)(piVar2 + 8);
    *puVar4 = *puVar3;
    memcpy(puVar4 + 2,puVar3 + 2,(ulonglong)*puVar3 << 3);
    uVar10 = **(uint **)(piVar2 + 8);
    if (**(uint **)(piVar2 + 8) < **(uint **)(piVar2 + 6)) {
      uVar10 = **(uint **)(piVar2 + 6);
    }
    if (uVar10 == 0) {
      if (param_2 == (int *)0x0) {
        Sleep(0x7fffffff);
      }
      else {
        dwMilliseconds = FUN_140016450(param_2);
        if ((int)dwMilliseconds < 0) {
          dwMilliseconds = 0x7fffffff;
        }
        Sleep(dwMilliseconds);
      }
    }
    else {
      if (*(longlong *)(param_1 + 0x1d0) != 0) {
        FUN_140016e50();
      }
      iVar5 = Ordinal_18(uVar10,*(undefined8 *)(piVar2 + 6),*(undefined8 *)(piVar2 + 8),
                         *(undefined8 *)(piVar2 + 10),param_2);
      if (*(longlong *)(param_1 + 0x1d0) != 0) {
        FUN_140016e30();
      }
      if (iVar5 < 1) {
        return iVar5;
      }
      if (**(int **)(piVar2 + 6) != 0) {
        iVar5 = FUN_1400089a0((uint *)(param_1 + 0x2a0),**(int **)(piVar2 + 6));
        uVar10 = 0;
        uVar8 = (ulonglong)iVar5;
        uVar9 = uVar8;
        if (**(int **)(piVar2 + 6) != 0) {
          do {
            uVar7 = (int)uVar9 + 1;
            uVar9 = (ulonglong)uVar7;
            uVar8 = uVar8 + 1;
            if (**(uint **)(piVar2 + 6) <= uVar7) {
              uVar9 = 0;
              uVar8 = 0;
            }
            FUN_14001a5d0(param_1,*(longlong *)(*(uint **)(piVar2 + 6) + uVar8 * 2 + 2),2);
            uVar10 = uVar10 + 1;
          } while (uVar10 < **(uint **)(piVar2 + 6));
        }
      }
      if (**(int **)(piVar2 + 10) != 0) {
        iVar5 = FUN_1400089a0((uint *)(param_1 + 0x2a0),**(int **)(piVar2 + 10));
        uVar10 = 0;
        uVar8 = (ulonglong)iVar5;
        uVar9 = uVar8;
        if (**(int **)(piVar2 + 10) != 0) {
          do {
            uVar7 = (int)uVar9 + 1;
            uVar9 = (ulonglong)uVar7;
            uVar8 = uVar8 + 1;
            if (**(uint **)(piVar2 + 10) <= uVar7) {
              uVar9 = 0;
              uVar8 = 0;
            }
            FUN_14001a5d0(param_1,*(longlong *)(*(uint **)(piVar2 + 10) + uVar8 * 2 + 2),4);
            uVar10 = uVar10 + 1;
          } while (uVar10 < **(uint **)(piVar2 + 10));
        }
      }
      if (**(int **)(piVar2 + 8) != 0) {
        iVar5 = FUN_1400089a0((uint *)(param_1 + 0x2a0),**(int **)(piVar2 + 8));
        uVar10 = 0;
        uVar8 = (ulonglong)iVar5;
        uVar9 = uVar8;
        if (**(int **)(piVar2 + 8) != 0) {
          do {
            uVar7 = (int)uVar9 + 1;
            uVar9 = (ulonglong)uVar7;
            uVar8 = uVar8 + 1;
            if (**(uint **)(piVar2 + 8) <= uVar7) {
              uVar9 = 0;
              uVar8 = 0;
            }
            FUN_14001a5d0(param_1,*(longlong *)(*(uint **)(piVar2 + 8) + uVar8 * 2 + 2),4);
            uVar10 = uVar10 + 1;
          } while (uVar10 < **(uint **)(piVar2 + 8));
        }
      }
    }
    iVar5 = 0;
  }
  else {
    sVar1 = (ulonglong)(*piVar2 - 1) * 8 + 0x10;
    lVar6 = FUN_1400119a0(*(void **)(piVar2 + 6),sVar1);
    *(longlong *)(piVar2 + 6) = lVar6;
    if (lVar6 != 0) {
      lVar6 = FUN_1400119a0(*(void **)(piVar2 + 10),sVar1);
      *(longlong *)(piVar2 + 10) = lVar6;
      if (lVar6 != 0) {
        lVar6 = FUN_1400119a0(*(void **)(piVar2 + 8),sVar1);
        *(longlong *)(piVar2 + 8) = lVar6;
        if (lVar6 != 0) {
          piVar2[1] = 0;
          goto LAB_1400754fe;
        }
      }
    }
    iVar5 = -1;
  }
  return iVar5;
}


// ==== FUN_140075740 @ 140075740  undefined FUN_140075740(longlong param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_140075740(longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 *puVar1;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  FUN_14001b930(param_1,param_2,param_3,param_4);
  if ((void *)puVar1[1] != (void *)0x0) {
    FUN_1400119c0((void *)puVar1[1]);
  }
  if ((void *)puVar1[2] != (void *)0x0) {
    FUN_1400119c0((void *)puVar1[2]);
  }
  if ((void *)puVar1[3] != (void *)0x0) {
    FUN_1400119c0((void *)puVar1[3]);
  }
  if ((void *)puVar1[4] != (void *)0x0) {
    FUN_1400119c0((void *)puVar1[4]);
  }
  if ((void *)puVar1[5] != (void *)0x0) {
    FUN_1400119c0((void *)puVar1[5]);
  }
  *puVar1 = 0;
  puVar1[1] = 0;
  puVar1[2] = 0;
  puVar1[3] = 0;
  puVar1[4] = 0;
  puVar1[5] = 0;
  puVar1[6] = 0;
  FUN_1400119c0(puVar1);
  return;
}


// ==== FUN_1400757e0 @ 1400757e0  undefined FUN_1400757e0(longlong param_1, uint param_2)

void FUN_1400757e0(longlong param_1,uint param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  int iVar3;
  
  puVar2 = *(undefined8 **)(param_1 + 0x98);
  iVar3 = 0;
  if (0 < *(int *)(param_1 + 0xa0)) {
    do {
      puVar1 = (undefined8 *)*puVar2;
      FUN_14000dcb0(puVar2,param_2);
      iVar3 = iVar3 + 1;
      puVar2 = puVar1;
    } while (iVar3 < *(int *)(param_1 + 0xa0));
  }
  return;
}


// ==== FUN_140075840 @ 140075840  undefined FUN_140075840(undefined8 * param_1, ulonglong param_2)

void FUN_140075840(undefined8 *param_1,ulonglong param_2)

{
  longlong *plVar1;
  undefined8 *puVar2;
  ulonglong uVar3;
  undefined8 *puVar4;
  uint uVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  longlong *plVar8;
  ulonglong uVar9;
  uint *puVar10;
  
  puVar6 = (undefined8 *)0x0;
  puVar7 = puVar6;
  if ((param_1 != (undefined8 *)0x0) && ((*(byte *)(param_1 + 7) & 0x10) != 0)) {
    puVar7 = param_1;
  }
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  FUN_14000d9a0((longlong)param_1,0);
  plVar1 = *(longlong **)param_1[2];
  plVar8 = (longlong *)param_1[2];
  if ((*(byte *)(plVar1 + 4) & 0x10) == 0) {
    plVar8 = plVar1;
  }
  if (param_2 != 0) {
    puVar10 = (uint *)(puVar7 + 0x15);
    puVar4 = puVar6;
    uVar9 = param_2;
    do {
      if (*(uint *)(puVar7 + 0x14) <= (uint)puVar4) break;
      uVar3 = (ulonglong)*puVar10;
      if (uVar9 < *puVar10) {
        uVar3 = uVar9;
      }
      puVar4 = (undefined8 *)(ulonglong)((uint)puVar4 + 1);
      puVar10 = puVar10 + 4;
      *(longlong *)(*plVar8 + 0x18) = *(longlong *)(*plVar8 + 0x18) + uVar3;
      uVar9 = uVar9 - uVar3;
      param_1[2] = plVar8;
      plVar8 = (longlong *)*plVar8;
    } while (uVar9 != 0);
  }
  puVar4 = (undefined8 *)puVar7[0x13];
  if (0 < *(int *)(puVar7 + 0x14)) {
    do {
      puVar2 = (undefined8 *)*puVar4;
      FUN_14000dcb0(puVar4,0x10);
      uVar5 = (int)puVar6 + 1;
      puVar6 = (undefined8 *)(ulonglong)uVar5;
      puVar4 = puVar2;
    } while ((int)uVar5 < *(int *)(puVar7 + 0x14));
  }
  *(uint *)(puVar7 + 0x12) = *(uint *)(puVar7 + 0x12) & 0xfffffffe;
  param_1[3] = param_1[3] + param_2;
  param_1[4] = param_1[4] + param_2;
  FUN_14000c160((longlong)param_1);
  FUN_14000c220(param_1);
  return;
}


// ==== FUN_140075950 @ 140075950  undefined FUN_140075950(longlong * param_1, ulonglong param_2)

void FUN_140075950(longlong *param_1,ulonglong param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  uint uVar3;
  longlong *plVar4;
  longlong *plVar5;
  
  plVar4 = (longlong *)0x0;
  if ((param_1 == (longlong *)0x0) || (plVar5 = param_1, (*(byte *)(param_1 + 7) & 0x10) == 0)) {
    plVar5 = plVar4;
  }
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  FUN_14000d9a0((longlong)param_1,1);
  FUN_14000e2a0(param_1,param_2);
  puVar2 = (undefined8 *)plVar5[0x13];
  if (0 < (int)plVar5[0x14]) {
    do {
      puVar1 = (undefined8 *)*puVar2;
      FUN_14000dcb0(puVar2,0x20);
      uVar3 = (int)plVar4 + 1;
      plVar4 = (longlong *)(ulonglong)uVar3;
      puVar2 = puVar1;
    } while ((int)uVar3 < (int)plVar5[0x14]);
  }
  *(uint *)(plVar5 + 0x12) = *(uint *)(plVar5 + 0x12) & 0xfffffffd;
  FUN_14000c220(param_1);
  return;
}


// ==== FUN_140075a00 @ 140075a00  undefined FUN_140075a00(undefined8 param_1)

void FUN_140075a00(undefined8 param_1)

{
  void *pvVar1;
  
  pvVar1 = FUN_140011850(1,0x1a8);
  if (pvVar1 == (void *)0x0) {
    return;
  }
  *(uint *)((longlong)pvVar1 + 0x38) = *(uint *)((longlong)pvVar1 + 0x38) | 0x10;
  *(undefined8 *)((longlong)pvVar1 + 0x78) = 0;
  *(undefined4 *)((longlong)pvVar1 + 0x48) = 1;
  *(void **)((longlong)pvVar1 + 0x10) = pvVar1;
  *(undefined8 *)((longlong)pvVar1 + 0x88) = param_1;
  return;
}


// ==== FUN_140075a50 @ 140075a50  undefined8 * FUN_140075a50(undefined8 * param_1, ulonglong param_2, undefined8 param_3)

undefined8 * FUN_140075a50(undefined8 *param_1,ulonglong param_2,undefined8 param_3)

{
  ulonglong uVar1;
  int iVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  uint uVar6;
  undefined8 *puVar8;
  undefined8 *puVar9;
  undefined1 local_res8 [8];
  undefined8 *puVar7;
  
  puVar7 = (undefined8 *)0x0;
  puVar5 = puVar7;
  if ((param_1 != (undefined8 *)0x0) && ((*(byte *)(param_1 + 7) & 0x10) != 0)) {
    puVar5 = param_1;
  }
  puVar8 = (undefined8 *)0xffffffff;
  puVar3 = puVar8;
  if (param_1 != (undefined8 *)0x0) {
    if (param_1[6] != 0) {
      FUN_140016e30();
    }
    if ((((*(byte *)(param_1 + 7) & 2) == 0) &&
        (puVar3 = (undefined8 *)0xffffffff, (*(byte *)(puVar5 + 0x12) & 2) == 0)) &&
       (uVar1 = param_1[3], puVar3 = puVar7, uVar1 != 0)) {
      if (((longlong)param_2 < 0) || (uVar1 < param_2)) {
        param_2 = uVar1;
      }
      FUN_14000d950((longlong)param_1,1);
      puVar5[0x13] = 0;
      *(undefined4 *)(puVar5 + 0x14) = 0;
      memset(puVar5 + 0x15,0,0x100);
      puVar3 = (undefined8 *)*param_1;
      puVar5[0x13] = puVar3;
      puVar4 = puVar5 + 0x15;
      puVar9 = puVar7;
      do {
        uVar6 = (uint)puVar7;
        if (puVar3 == (undefined8 *)0x0) break;
        puVar4[1] = puVar3[5] + puVar3[2];
        FUN_14000be60((longlong)puVar3,0x20);
        if (param_2 <= (ulonglong)puVar3[3]) {
          *(int *)puVar4 = (int)param_2;
          uVar6 = uVar6 + 1;
          break;
        }
        puVar9 = (undefined8 *)((longlong)puVar9 + 1);
        *(undefined4 *)puVar4 = *(undefined4 *)(puVar3 + 3);
        param_2 = param_2 - puVar3[3];
        puVar3 = (undefined8 *)*puVar3;
        uVar6 = uVar6 + 1;
        puVar7 = (undefined8 *)(ulonglong)uVar6;
        puVar4 = puVar4 + 2;
      } while ((longlong)puVar9 < 0x10);
      *(uint *)(puVar5 + 0x14) = uVar6;
      FUN_14000bf50((longlong)param_1);
      iVar2 = WSASend(puVar5[0x11],puVar5 + 0x15,uVar6,local_res8,0,param_3,0);
      if ((iVar2 == 0) || (iVar2 = Ordinal_111(), iVar2 == 0x3e5)) {
        *(uint *)(puVar5 + 0x12) = *(uint *)(puVar5 + 0x12) | 2;
        puVar3 = (undefined8 *)0x0;
      }
      else {
        FUN_1400757e0((longlong)puVar5,0x20);
        FUN_14000d9a0((longlong)param_1,1);
        FUN_14000c300(param_1);
        puVar3 = puVar8;
      }
    }
    if (param_1[6] != 0) {
      FUN_140016e50();
    }
  }
  return puVar3;
}


// ==== FUN_140075c30 @ 140075c30  longlong * FUN_140075c30(longlong * param_1, ulonglong param_2, undefined8 param_3)

longlong * FUN_140075c30(longlong *param_1,ulonglong param_2,undefined8 param_3)

{
  undefined8 *puVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 *puVar4;
  undefined4 *puVar5;
  longlong *plVar6;
  uint uVar7;
  longlong *plVar8;
  longlong *plVar9;
  longlong *plVar10;
  longlong lVar11;
  undefined4 local_res8 [2];
  undefined1 local_res20 [8];
  longlong *local_148 [2];
  longlong local_138;
  undefined4 local_130 [62];
  
  plVar8 = (longlong *)0x0;
  plVar6 = plVar8;
  if ((param_1 != (longlong *)0x0) && ((*(byte *)(param_1 + 7) & 0x10) != 0)) {
    plVar6 = param_1;
  }
  plVar10 = (longlong *)0xffffffff;
  local_res8[0] = 0;
  plVar9 = plVar10;
  if (plVar6 != (longlong *)0x0) {
    if (param_1[6] != 0) {
      FUN_140016e30();
    }
    if (((*(byte *)(param_1 + 7) & 4) == 0) &&
       (plVar9 = (longlong *)0xffffffff, (*(byte *)(plVar6 + 0x12) & 1) == 0)) {
      plVar6[0x13] = 0;
      *(undefined4 *)(plVar6 + 0x14) = 0;
      memset(plVar6 + 0x15,0,0x100);
      uVar3 = FUN_14000ebd0(param_1,param_2,0x10);
      plVar9 = plVar10;
      if ((int)uVar3 != -1) {
        FUN_14000d950((longlong)param_1,0);
        iVar2 = FUN_14000cdc0((longlong)param_1,param_2,&local_138,0x10,(longlong *)local_148,1);
        lVar11 = (longlong)iVar2;
        if (0 < iVar2) {
          puVar5 = local_130;
          plVar9 = plVar6 + 0x15;
          do {
            lVar11 = lVar11 + -1;
            plVar9[1] = *(longlong *)(puVar5 + -2);
            *(undefined4 *)plVar9 = *puVar5;
            puVar5 = puVar5 + 4;
            plVar9 = plVar9 + 2;
          } while (lVar11 != 0);
        }
        *(int *)(plVar6 + 0x14) = iVar2;
        puVar4 = (undefined8 *)*local_148[0];
        plVar6[0x13] = (longlong)puVar4;
        for (; puVar4 != (undefined8 *)0x0; puVar4 = (undefined8 *)*puVar4) {
          FUN_14000be60((longlong)puVar4,0x10);
        }
        FUN_14000bf50((longlong)param_1);
        iVar2 = WSARecv(plVar6[0x11],plVar6 + 0x15,iVar2,local_res20,local_res8,param_3,0);
        if ((iVar2 == 0) || (iVar2 = Ordinal_111(), iVar2 == 0x3e5)) {
          *(uint *)(plVar6 + 0x12) = *(uint *)(plVar6 + 0x12) | 1;
          plVar9 = plVar8;
        }
        else {
          puVar4 = (undefined8 *)plVar6[0x13];
          if (0 < (int)plVar6[0x14]) {
            do {
              puVar1 = (undefined8 *)*puVar4;
              FUN_14000dcb0(puVar4,0x10);
              uVar7 = (int)plVar8 + 1;
              plVar8 = (longlong *)(ulonglong)uVar7;
              puVar4 = puVar1;
            } while ((int)uVar7 < (int)plVar6[0x14]);
          }
          FUN_14000d9a0((longlong)param_1,0);
          FUN_14000c300(param_1);
          plVar9 = (longlong *)0xffffffff;
        }
      }
    }
    if (param_1[6] != 0) {
      FUN_140016e50();
    }
  }
  return plVar9;
}


// ==== FUN_140075e60 @ 140075e60  undefined8 FUN_140075e60(longlong param_1)

undefined8 FUN_140075e60(longlong param_1)

{
  if ((param_1 != 0) && ((*(byte *)(param_1 + 0x38) & 0x10) != 0)) {
    return *(undefined8 *)(param_1 + 0x88);
  }
  return 0xffffffffffffffff;
}


// ==== FUN_140075e80 @ 140075e80  undefined FUN_140075e80(longlong param_1, undefined8 param_2)

void FUN_140075e80(longlong param_1,undefined8 param_2)

{
  longlong lVar1;
  
  if ((param_1 == 0) || (lVar1 = param_1, (*(byte *)(param_1 + 0x38) & 0x10) == 0)) {
    lVar1 = 0;
  }
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e30();
  }
  if (lVar1 != 0) {
    *(undefined8 *)(lVar1 + 0x88) = param_2;
  }
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_140075ef0 @ 140075ef0  undefined FUN_140075ef0(undefined8 * param_1)

void FUN_140075ef0(undefined8 *param_1)

{
  *param_1 = google::protobuf::MessageLite::vftable;
  return;
}


// ==== FUN_140075f60 @ 140075f60  undefined FUN_140075f60(int param_1, int param_2, int param_3)

void FUN_140075f60(int param_1,int param_2,int param_3)

{
  int *piVar1;
  longlong lVar2;
  undefined1 *puVar3;
  undefined1 local_128 [8];
  undefined4 local_120 [16];
  undefined1 local_e0 [8];
  undefined4 local_d8 [16];
  undefined1 local_98 [8];
  undefined4 local_90 [16];
  uint local_50;
  undefined8 local_48;
  undefined4 *local_40;
  undefined4 *local_38;
  undefined4 *local_30;
  undefined4 *local_28;
  undefined4 *local_20;
  undefined4 *local_18;
  
  local_48 = 0xfffffffffffffffe;
  local_50 = 0;
  if (param_1 != param_2) {
    puVar3 = local_128;
    for (lVar2 = 1; lVar2 != 0; lVar2 = lVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    local_40 = FUN_1400783d0(local_120,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\message_lite.cc"
                             ,0x3f);
    local_50 = local_50 | 1;
    local_38 = local_40;
    lVar2 = FUN_140078030((longlong)local_40,
                          "CHECK failed: (byte_size_before_serialization) == (byte_size_after_serialization): "
                         );
    piVar1 = (int *)FUN_140078030(lVar2,
                                  "Protocol message was modified concurrently during serialization."
                                 );
    FUN_140078580(local_128,piVar1);
  }
  if ((local_50 & 1) != 0) {
    local_50 = local_50 & 0xfffffffe;
    FUN_140078440((longlong)local_120);
  }
  if (param_3 != param_1) {
    puVar3 = local_e0;
    for (lVar2 = 1; lVar2 != 0; lVar2 = lVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    local_30 = FUN_1400783d0(local_d8,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\message_lite.cc"
                             ,0x41);
    local_50 = local_50 | 2;
    local_28 = local_30;
    lVar2 = FUN_140078030((longlong)local_30,
                          "CHECK failed: (bytes_produced_by_serialization) == (byte_size_before_serialization): "
                         );
    piVar1 = (int *)FUN_140078030(lVar2,
                                  "Byte size calculation and serialization were inconsistent.  This may indicate a bug in protocol buffers or it may be caused by concurrent modification of the message."
                                 );
    FUN_140078580(local_e0,piVar1);
  }
  if ((local_50 & 2) != 0) {
    local_50 = local_50 & 0xfffffffd;
    FUN_140078440((longlong)local_d8);
  }
  puVar3 = local_98;
  for (lVar2 = 1; lVar2 != 0; lVar2 = lVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  local_20 = FUN_1400783d0(local_90,3,
                           "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\message_lite.cc",
                           0x45);
  local_18 = local_20;
  piVar1 = (int *)FUN_140078030((longlong)local_20,
                                "This shouldn\'t be called if all the sizes are equal.");
  FUN_140078580(local_98,piVar1);
  FUN_140078440((longlong)local_90);
  return;
}


// ==== FUN_140076190 @ 140076190  undefined FUN_140076190(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_1, char * param_2, longlong * param_3)

void FUN_140076190(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                   *param_1,char *param_2,longlong *param_3)

{
  undefined1 auStack_e8 [40];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_c0 [40];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_98 [40];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  uint local_48;
  undefined8 local_40;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_38;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_28;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_20;
  ulonglong local_18;
  
  local_40 = 0xfffffffffffffffe;
  local_18 = DAT_140103510 ^ (ulonglong)auStack_e8;
  local_48 = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_c0);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
            (local_c0,"Can\'t ");
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
            (local_c0,param_2);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
            (local_c0," message of type \"");
  local_38 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (**(code **)(*param_3 + 8))(param_3,local_98);
  local_30 = local_38;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
            (local_c0,local_38);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_98);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
            (local_c0,"\" because it is missing required fields: ");
  local_28 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (**(code **)(*param_3 + 0x28))(param_3,local_70);
  local_20 = local_28;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
            (local_c0,local_28);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_70);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(param_1,local_c0);
  local_48 = local_48 | 1;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_c0);
  __security_check_cookie(local_18 ^ (ulonglong)auStack_e8);
  return;
}


// ==== FUN_140076320 @ 140076320  undefined FUN_140076320(longlong * param_1, undefined8 param_2)

void FUN_140076320(longlong *param_1,undefined8 param_2)

{
  FUN_140077370(param_2,param_1);
  return;
}


// ==== FUN_140076350 @ 140076350  undefined FUN_140076350(longlong * param_1, undefined8 param_2)

void FUN_140076350(longlong *param_1,undefined8 param_2)

{
  FUN_1400774a0(param_2,param_1);
  return;
}


// ==== FUN_140076380 @ 140076380  undefined FUN_140076380(longlong * param_1, undefined8 param_2)

void FUN_140076380(longlong *param_1,undefined8 param_2)

{
  FUN_1400774e0(param_2,param_1);
  return;
}


// ==== FUN_1400763b0 @ 1400763b0  undefined1 FUN_1400763b0(longlong * param_1, undefined8 param_2)

undefined1 FUN_1400763b0(longlong *param_1,undefined8 param_2)

{
  char cVar1;
  longlong local_78 [10];
  undefined1 local_28;
  undefined8 local_20;
  undefined4 local_18;
  
  local_20 = 0xfffffffffffffffe;
  FUN_140077530(local_78,param_2);
  cVar1 = FUN_140076350(param_1,local_78);
  if (cVar1 != '\0') {
    cVar1 = FUN_140077520((longlong)local_78);
    if (cVar1 != '\0') {
      local_18 = 1;
      goto LAB_14007641f;
    }
  }
  local_18 = 0;
LAB_14007641f:
  local_28 = (undefined1)local_18;
  FUN_14007a700(local_78);
  return local_28;
}


// ==== FUN_140076450 @ 140076450  undefined1 FUN_140076450(longlong * param_1, undefined8 param_2)

undefined1 FUN_140076450(longlong *param_1,undefined8 param_2)

{
  char cVar1;
  longlong local_78 [10];
  undefined1 local_28;
  undefined8 local_20;
  undefined4 local_18;
  
  local_20 = 0xfffffffffffffffe;
  FUN_140077530(local_78,param_2);
  cVar1 = FUN_140076380(param_1,local_78);
  if (cVar1 != '\0') {
    cVar1 = FUN_140077520((longlong)local_78);
    if (cVar1 != '\0') {
      local_18 = 1;
      goto LAB_1400764bf;
    }
  }
  local_18 = 0;
LAB_1400764bf:
  local_28 = (undefined1)local_18;
  FUN_14007a700(local_78);
  return local_28;
}


// ==== FUN_1400764f0 @ 1400764f0  undefined1 FUN_1400764f0(longlong * param_1, undefined8 param_2, int param_3)

undefined1 FUN_1400764f0(longlong *param_1,undefined8 param_2,int param_3)

{
  char cVar1;
  int iVar2;
  longlong local_78 [10];
  undefined1 local_28;
  undefined8 local_20;
  undefined4 local_18;
  
  local_20 = 0xfffffffffffffffe;
  FUN_140077530(local_78,param_2);
  FUN_14007a8e0((longlong)local_78,param_3);
  cVar1 = FUN_140076350(param_1,local_78);
  if (cVar1 != '\0') {
    cVar1 = FUN_140077520((longlong)local_78);
    if (cVar1 != '\0') {
      iVar2 = FUN_14007a9c0((longlong)local_78);
      if (iVar2 == 0) {
        local_18 = 1;
        goto LAB_140076583;
      }
    }
  }
  local_18 = 0;
LAB_140076583:
  local_28 = (undefined1)local_18;
  FUN_14007a700(local_78);
  return local_28;
}


// ==== FUN_1400765b0 @ 1400765b0  undefined1 FUN_1400765b0(longlong * param_1, undefined8 param_2, int param_3)

undefined1 FUN_1400765b0(longlong *param_1,undefined8 param_2,int param_3)

{
  char cVar1;
  int iVar2;
  longlong local_78 [10];
  undefined1 local_28;
  undefined8 local_20;
  undefined4 local_18;
  
  local_20 = 0xfffffffffffffffe;
  FUN_140077530(local_78,param_2);
  FUN_14007a8e0((longlong)local_78,param_3);
  cVar1 = FUN_140076380(param_1,local_78);
  if (cVar1 != '\0') {
    cVar1 = FUN_140077520((longlong)local_78);
    if (cVar1 != '\0') {
      iVar2 = FUN_14007a9c0((longlong)local_78);
      if (iVar2 == 0) {
        local_18 = 1;
        goto LAB_140076643;
      }
    }
  }
  local_18 = 0;
LAB_140076643:
  local_28 = (undefined1)local_18;
  FUN_14007a700(local_78);
  return local_28;
}


// ==== FUN_140076670 @ 140076670  undefined FUN_140076670(longlong * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

void FUN_140076670(longlong *param_1,
                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_2)

{
  __uint64 _Var1;
  char *pcVar2;
  
  _Var1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (param_2);
  pcVar2 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::data
                     (param_2);
  FUN_140077620((longlong)pcVar2,(int)_Var1,param_1);
  return;
}


// ==== FUN_1400766c0 @ 1400766c0  undefined FUN_1400766c0(longlong * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

void FUN_1400766c0(longlong *param_1,
                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_2)

{
  __uint64 _Var1;
  char *pcVar2;
  
  _Var1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (param_2);
  pcVar2 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::data
                     (param_2);
  FUN_1400777a0((longlong)pcVar2,(int)_Var1,param_1);
  return;
}


// ==== FUN_140076710 @ 140076710  undefined FUN_140076710(longlong * param_1, longlong param_2, int param_3)

void FUN_140076710(longlong *param_1,longlong param_2,int param_3)

{
  FUN_140077620(param_2,param_3,param_1);
  return;
}


// ==== FUN_140076750 @ 140076750  undefined FUN_140076750(longlong * param_1, longlong param_2, int param_3)

void FUN_140076750(longlong *param_1,longlong param_2,int param_3)

{
  FUN_1400777a0(param_2,param_3,param_1);
  return;
}


// ==== FUN_140076910 @ 140076910  undefined FUN_140076910(longlong * param_1, longlong param_2)

/* WARNING: Removing unreachable block (ram,0x000140076943) */
/* WARNING: Removing unreachable block (ram,0x000140076965) */
/* WARNING: Removing unreachable block (ram,0x000140076971) */
/* WARNING: Removing unreachable block (ram,0x000140076973) */
/* WARNING: Removing unreachable block (ram,0x000140076960) */
/* WARNING: Removing unreachable block (ram,0x000140076a2c) */
/* WARNING: Removing unreachable block (ram,0x000140076a3a) */
/* WARNING: Removing unreachable block (ram,0x000140076a4d) */
/* WARNING: Removing unreachable block (ram,0x000140076a5b) */
/* WARNING: Removing unreachable block (ram,0x000140076a6e) */

void FUN_140076910(longlong *param_1,longlong param_2)

{
  FUN_140076aa0(param_1,param_2);
  return;
}


// ==== FUN_140076aa0 @ 140076aa0  undefined8 FUN_140076aa0(longlong * param_1, longlong param_2)

undefined8 FUN_140076aa0(longlong *param_1,longlong param_2)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  longlong lVar7;
  longlong lVar8;
  undefined8 uVar9;
  ulonglong uVar10;
  
  uVar2 = (**(code **)(*param_1 + 0x40))(param_1);
  lVar6 = FUN_140077850(param_2,uVar2);
  if (lVar6 == 0) {
    iVar3 = FUN_1400778a0(param_2);
    (**(code **)(*param_1 + 0x48))(param_1,param_2);
    cVar1 = FUN_140077840(param_2);
    if (cVar1 == '\0') {
      iVar4 = FUN_1400778a0(param_2);
      uVar10 = (ulonglong)(uint)(iVar4 - iVar3);
      if (iVar4 - iVar3 != uVar2) {
        iVar5 = (**(code **)(*param_1 + 0x40))(param_1);
        uVar10 = FUN_140075f60(uVar2,iVar5,iVar4 - iVar3);
      }
      uVar9 = CONCAT71((int7)(uVar10 >> 8),1);
    }
    else {
      uVar9 = 0;
    }
  }
  else {
    lVar7 = (**(code **)(*param_1 + 0x50))(param_1,lVar6);
    lVar8 = (longlong)(int)uVar2;
    if (lVar7 - lVar6 != lVar8) {
      iVar3 = (**(code **)(*param_1 + 0x40))(param_1);
      lVar8 = FUN_140075f60(uVar2,iVar3,(int)lVar7 - (int)lVar6);
    }
    uVar9 = CONCAT71((int7)((ulonglong)lVar8 >> 8),1);
  }
  return uVar9;
}


// ==== FUN_140076be0 @ 140076be0  undefined1 FUN_140076be0(longlong * param_1, undefined8 param_2)

undefined1 FUN_140076be0(longlong *param_1,undefined8 param_2)

{
  undefined8 local_38 [4];
  undefined1 local_18;
  undefined8 local_10;
  
  local_10 = 0xfffffffffffffffe;
  FUN_14007bbf0(local_38,param_2);
  local_18 = FUN_140076910(param_1,(longlong)local_38);
  FUN_14007bc70(local_38);
  return local_18;
}


// ==== FUN_140076c40 @ 140076c40  undefined1 FUN_140076c40(longlong * param_1, undefined8 param_2)

undefined1 FUN_140076c40(longlong *param_1,undefined8 param_2)

{
  undefined8 uVar1;
  undefined8 local_38 [4];
  undefined1 local_18;
  undefined8 local_10;
  
  local_10 = 0xfffffffffffffffe;
  FUN_14007bbf0(local_38,param_2);
  uVar1 = FUN_140076aa0(param_1,(longlong)local_38);
  local_18 = (undefined1)uVar1;
  FUN_14007bc70(local_38);
  return local_18;
}


// ==== FUN_140076ca0 @ 140076ca0  undefined FUN_140076ca0(longlong * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

/* WARNING: Removing unreachable block (ram,0x000140076cd3) */
/* WARNING: Removing unreachable block (ram,0x000140076cf5) */
/* WARNING: Removing unreachable block (ram,0x000140076d01) */
/* WARNING: Removing unreachable block (ram,0x000140076d03) */
/* WARNING: Removing unreachable block (ram,0x000140076cf0) */
/* WARNING: Removing unreachable block (ram,0x000140076dbc) */
/* WARNING: Removing unreachable block (ram,0x000140076dca) */
/* WARNING: Removing unreachable block (ram,0x000140076ddd) */
/* WARNING: Removing unreachable block (ram,0x000140076deb) */
/* WARNING: Removing unreachable block (ram,0x000140076dfe) */

void FUN_140076ca0(longlong *param_1,
                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_2)

{
  FUN_140076e30(param_1,param_2);
  return;
}


// ==== FUN_140076e30 @ 140076e30  undefined8 FUN_140076e30(longlong * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

undefined8
FUN_140076e30(longlong *param_1,
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  int iVar1;
  int iVar2;
  __uint64 _Var3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  
  _Var3 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (param_2);
  iVar1 = (**(code **)(*param_1 + 0x40))(param_1);
  FUN_140077900(param_2,(longlong)((int)_Var3 + iVar1));
  lVar4 = FUN_140077930(param_2);
  lVar4 = lVar4 + (int)_Var3;
  lVar5 = (**(code **)(*param_1 + 0x50))(param_1,lVar4);
  lVar6 = (longlong)iVar1;
  if (lVar5 - lVar4 != lVar6) {
    iVar2 = (**(code **)(*param_1 + 0x40))(param_1);
    lVar6 = FUN_140075f60(iVar1,iVar2,(int)lVar5 - (int)lVar4);
  }
  return CONCAT71((int7)((ulonglong)lVar6 >> 8),1);
}


// ==== FUN_140076f00 @ 140076f00  undefined FUN_140076f00(longlong * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

void FUN_140076f00(longlong *param_1,
                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_2)

{
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::clear(param_2);
  FUN_140076ca0(param_1,param_2);
  return;
}


// ==== FUN_140076f40 @ 140076f40  undefined FUN_140076f40(longlong * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

void FUN_140076f40(longlong *param_1,
                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_2)

{
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::clear(param_2);
  FUN_140076e30(param_1,param_2);
  return;
}


// ==== FUN_140076f80 @ 140076f80  undefined FUN_140076f80(longlong * param_1, longlong param_2, int param_3)

/* WARNING: Removing unreachable block (ram,0x000140076fb8) */
/* WARNING: Removing unreachable block (ram,0x000140076fda) */
/* WARNING: Removing unreachable block (ram,0x000140076fe6) */
/* WARNING: Removing unreachable block (ram,0x000140076fe8) */
/* WARNING: Removing unreachable block (ram,0x000140076fd5) */
/* WARNING: Removing unreachable block (ram,0x0001400770a1) */
/* WARNING: Removing unreachable block (ram,0x0001400770af) */
/* WARNING: Removing unreachable block (ram,0x0001400770c2) */
/* WARNING: Removing unreachable block (ram,0x0001400770d0) */
/* WARNING: Removing unreachable block (ram,0x0001400770e3) */

void FUN_140076f80(longlong *param_1,longlong param_2,int param_3)

{
  FUN_140077120(param_1,param_2,param_3);
  return;
}


// ==== FUN_140077120 @ 140077120  undefined8 FUN_140077120(longlong * param_1, longlong param_2, int param_3)

longlong FUN_140077120(longlong *param_1,longlong param_2,int param_3)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  longlong lVar4;
  
  iVar1 = (**(code **)(*param_1 + 0x40))(param_1);
  if (param_3 < iVar1) {
    lVar3 = (ulonglong)(uint3)((uint)iVar1 >> 8) << 8;
  }
  else {
    lVar3 = (**(code **)(*param_1 + 0x50))(param_1,param_2);
    lVar4 = (longlong)iVar1;
    if (lVar3 - param_2 != lVar4) {
      iVar2 = (**(code **)(*param_1 + 0x40))(param_1);
      lVar4 = FUN_140075f60(iVar1,iVar2,(int)lVar3 - (int)param_2);
    }
    lVar3 = CONCAT71((int7)((ulonglong)lVar4 >> 8),1);
  }
  return lVar3;
}


// ==== FUN_1400771d0 @ 1400771d0  undefined FUN_1400771d0(longlong * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

void FUN_1400771d0(longlong *param_1,
                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_2)

{
  char cVar1;
  undefined1 auStack_78 [40];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_50 [40];
  uint local_28;
  undefined8 local_20;
  ulonglong local_18;
  
  local_20 = 0xfffffffffffffffe;
  local_18 = DAT_140103510 ^ (ulonglong)auStack_78;
  local_28 = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_50);
  cVar1 = FUN_140076ca0(param_1,local_50);
  if (cVar1 == '\0') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::clear
              (local_50);
  }
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(param_2,local_50);
  local_28 = local_28 | 1;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_50);
  __security_check_cookie(local_18 ^ (ulonglong)auStack_78);
  return;
}


// ==== FUN_140077280 @ 140077280  undefined FUN_140077280(longlong * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

void FUN_140077280(longlong *param_1,
                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_2)

{
  ulonglong uVar1;
  undefined1 auStack_78 [40];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_50 [40];
  uint local_28;
  undefined8 local_20;
  ulonglong local_18;
  
  local_20 = 0xfffffffffffffffe;
  local_18 = DAT_140103510 ^ (ulonglong)auStack_78;
  local_28 = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_50);
  uVar1 = FUN_140076e30(param_1,local_50);
  if ((uVar1 & 0xff) == 0) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::clear
              (local_50);
  }
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(param_2,local_50);
  local_28 = local_28 | 1;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_50);
  __security_check_cookie(local_18 ^ (ulonglong)auStack_78);
  return;
}


// ==== FUN_140077370 @ 140077370  ulonglong FUN_140077370(undefined8 param_1, longlong * param_2)

ulonglong FUN_140077370(undefined8 param_1,longlong *param_2)

{
  char cVar1;
  ulonglong uVar2;
  int *piVar3;
  ulonglong extraout_RAX;
  longlong lVar4;
  undefined1 *puVar5;
  undefined1 local_a8 [8];
  undefined4 local_a0 [16];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_60 [40];
  undefined8 local_38;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_28;
  undefined4 *local_20;
  undefined4 *local_18;
  
  local_38 = 0xfffffffffffffffe;
  cVar1 = (**(code **)(*param_2 + 0x38))(param_2,param_1);
  if (cVar1 == '\0') {
    uVar2 = 0;
  }
  else {
    cVar1 = (**(code **)(*param_2 + 0x20))(param_2);
    if (cVar1 == '\0') {
      puVar5 = local_a8;
      for (lVar4 = 1; lVar4 != 0; lVar4 = lVar4 + -1) {
        *puVar5 = 0;
        puVar5 = puVar5 + 1;
      }
      local_30 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 FUN_140076190(local_60,"parse",param_2);
      local_28 = local_30;
      local_20 = FUN_1400783d0(local_a0,2,
                               "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\message_lite.cc"
                               ,0x7b);
      local_18 = local_20;
      piVar3 = (int *)FUN_140077ff0((longlong)local_20,local_28);
      FUN_140078580(local_a8,piVar3);
      FUN_140078440((longlong)local_a0);
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_60);
      uVar2 = extraout_RAX & 0xffffffffffffff00;
    }
    else {
      uVar2 = 1;
    }
  }
  return uVar2;
}


// ==== FUN_1400774a0 @ 1400774a0  undefined FUN_1400774a0(undefined8 param_1, longlong * param_2)

void FUN_1400774a0(undefined8 param_1,longlong *param_2)

{
  (**(code **)(*param_2 + 0x18))(param_2);
  FUN_140077370(param_1,param_2);
  return;
}


// ==== FUN_1400774e0 @ 1400774e0  undefined FUN_1400774e0(undefined8 param_1, longlong * param_2)

void FUN_1400774e0(undefined8 param_1,longlong *param_2)

{
  (**(code **)(*param_2 + 0x18))(param_2);
  (**(code **)(*param_2 + 0x38))(param_2,param_1);
  return;
}


// ==== FUN_140077520 @ 140077520  undefined1 FUN_140077520(longlong param_1)

undefined1 FUN_140077520(longlong param_1)

{
  return *(undefined1 *)(param_1 + 0x24);
}


// ==== FUN_140077530 @ 140077530  undefined8 * FUN_140077530(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_140077530(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = param_2;
  param_1[1] = 0;
  param_1[2] = 0;
  *(undefined4 *)(param_1 + 3) = 0;
  *(undefined4 *)((longlong)param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined1 *)((longlong)param_1 + 0x24) = 0;
  *(undefined1 *)((longlong)param_1 + 0x25) = 0;
  *(undefined4 *)(param_1 + 5) = 0x7fffffff;
  *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 6) = 0x4000000;
  *(undefined4 *)((longlong)param_1 + 0x34) = 0x2000000;
  *(undefined4 *)(param_1 + 7) = 0;
  *(undefined4 *)((longlong)param_1 + 0x3c) = DAT_1401036a0;
  param_1[8] = 0;
  param_1[9] = 0;
  FUN_14007b7e0(param_1);
  return param_1;
}


// ==== FUN_140077620 @ 140077620  undefined1 FUN_140077620(longlong param_1, int param_2, longlong * param_3)

undefined1 FUN_140077620(longlong param_1,int param_2,longlong *param_3)

{
  char cVar1;
  longlong local_78 [10];
  undefined1 local_28;
  undefined8 local_20;
  undefined4 local_18;
  
  local_20 = 0xfffffffffffffffe;
  FUN_1400776c0(local_78,param_1,param_2);
  cVar1 = FUN_1400774a0(local_78,param_3);
  if (cVar1 != '\0') {
    cVar1 = FUN_140077520((longlong)local_78);
    if (cVar1 != '\0') {
      local_18 = 1;
      goto LAB_14007769b;
    }
  }
  local_18 = 0;
LAB_14007769b:
  local_28 = (undefined1)local_18;
  FUN_14007a700(local_78);
  return local_28;
}


// ==== FUN_1400776c0 @ 1400776c0  undefined8 * FUN_1400776c0(undefined8 * param_1, longlong param_2, int param_3)

undefined8 * FUN_1400776c0(undefined8 *param_1,longlong param_2,int param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  param_1[2] = param_2 + param_3;
  *(int *)(param_1 + 3) = param_3;
  *(undefined4 *)((longlong)param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined1 *)((longlong)param_1 + 0x24) = 0;
  *(undefined1 *)((longlong)param_1 + 0x25) = 0;
  *(int *)(param_1 + 5) = param_3;
  *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 6) = 0x4000000;
  *(undefined4 *)((longlong)param_1 + 0x34) = 0x2000000;
  *(undefined4 *)(param_1 + 7) = 0;
  *(undefined4 *)((longlong)param_1 + 0x3c) = DAT_1401036a0;
  param_1[8] = 0;
  param_1[9] = 0;
  return param_1;
}


// ==== FUN_1400777a0 @ 1400777a0  undefined1 FUN_1400777a0(longlong param_1, int param_2, longlong * param_3)

undefined1 FUN_1400777a0(longlong param_1,int param_2,longlong *param_3)

{
  char cVar1;
  longlong local_78 [10];
  undefined1 local_28;
  undefined8 local_20;
  undefined4 local_18;
  
  local_20 = 0xfffffffffffffffe;
  FUN_1400776c0(local_78,param_1,param_2);
  cVar1 = FUN_1400774e0(local_78,param_3);
  if (cVar1 != '\0') {
    cVar1 = FUN_140077520((longlong)local_78);
    if (cVar1 != '\0') {
      local_18 = 1;
      goto LAB_14007781b;
    }
  }
  local_18 = 0;
LAB_14007781b:
  local_28 = (undefined1)local_18;
  FUN_14007a700(local_78);
  return local_28;
}


// ==== FUN_140077840 @ 140077840  undefined1 FUN_140077840(longlong param_1)

undefined1 FUN_140077840(longlong param_1)

{
  return *(undefined1 *)(param_1 + 0x18);
}


// ==== FUN_140077850 @ 140077850  undefined8 FUN_140077850(longlong param_1, int param_2)

undefined8 FUN_140077850(longlong param_1,int param_2)

{
  undefined8 uVar1;
  
  if (*(int *)(param_1 + 0x10) < param_2) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined8 *)(param_1 + 8);
    FUN_1400778c0(param_1,param_2);
  }
  return uVar1;
}


// ==== FUN_1400778a0 @ 1400778a0  int FUN_1400778a0(longlong param_1)

int FUN_1400778a0(longlong param_1)

{
  return *(int *)(param_1 + 0x14) - *(int *)(param_1 + 0x10);
}


// ==== FUN_1400778c0 @ 1400778c0  undefined FUN_1400778c0(longlong param_1, int param_2)

void FUN_1400778c0(longlong param_1,int param_2)

{
  *(longlong *)(param_1 + 8) = (longlong)param_2 + *(longlong *)(param_1 + 8);
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) - param_2;
  return;
}


// ==== FUN_140077900 @ 140077900  undefined FUN_140077900(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_1, __uint64 param_2)

void FUN_140077900(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                   *param_1,__uint64 param_2)

{
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::resize
            (param_1,param_2);
  return;
}


// ==== FUN_140077930 @ 140077930  undefined FUN_140077930(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_1)

void FUN_140077930(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                   *param_1)

{
  FUN_140077950(param_1);
  return;
}


// ==== FUN_140077950 @ 140077950  undefined8 FUN_140077950(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_1)

undefined8
FUN_140077950(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1)

{
  bool bVar1;
  _Iterator_base *p_Var2;
  undefined8 local_18;
  
  bVar1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::empty
                    (param_1);
  if (bVar1) {
    local_18 = 0;
  }
  else {
    p_Var2 = (_Iterator_base *)
             std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             begin(param_1);
    local_18 = FUN_1400779a0(p_Var2);
  }
  return local_18;
}


// ==== FUN_1400779a0 @ 1400779a0  undefined FUN_1400779a0(_Iterator_base * param_1)

void FUN_1400779a0(_Iterator_base *param_1)

{
  FUN_1400779c0(param_1);
  return;
}


// ==== FUN_1400779c0 @ 1400779c0  undefined8 FUN_1400779c0(_Iterator_base * param_1)

undefined8 FUN_1400779c0(_Iterator_base *param_1)

{
  bool bVar1;
  char *pcVar2;
  
  if (*(longlong *)param_1 != -4) {
    bVar1 = std::_Iterator_base::_Has_container(param_1);
    if (!bVar1) {
      _invalid_parameter_noinfo();
    }
    pcVar2 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             _Myptr(*(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                      **)param_1);
    if (pcVar2 + *(longlong *)(*(longlong *)param_1 + 0x18) <= *(char **)(param_1 + 8)) {
      _invalid_parameter_noinfo();
    }
  }
  return *(undefined8 *)(param_1 + 8);
}


// ==== FUN_140077a60 @ 140077a60  undefined FUN_140077a60(int param_1, int param_2, char * param_3)

void FUN_140077a60(int param_1,int param_2,char *param_3)

{
  int *piVar1;
  longlong lVar2;
  undefined1 *puVar3;
  undefined1 local_1a8 [8];
  undefined4 local_1a0 [16];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_160 [40];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_138 [40];
  undefined1 local_110 [8];
  undefined4 local_108 [16];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_c8 [40];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_a0 [40];
  undefined8 local_78;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_70;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_68;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_60;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_58;
  undefined4 *local_50;
  undefined4 *local_48;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_40;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_38;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_28;
  undefined4 *local_20;
  undefined4 *local_18;
  
  local_78 = 0xfffffffffffffffe;
  if (0x1e9bf1 < param_2) {
    puVar3 = local_1a8;
    for (lVar2 = 1; lVar2 != 0; lVar2 = lVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    local_70 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_140077d40(local_138,0x1e9bf1);
    local_68 = local_70;
    local_60 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_140077d40(local_160,param_2);
    local_58 = local_60;
    local_50 = FUN_1400783d0(local_1a0,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\stubs\\common.cc"
                             ,0x3d);
    local_48 = local_50;
    lVar2 = FUN_140078030((longlong)local_50,"This program requires version ");
    lVar2 = FUN_140077ff0(lVar2,local_58);
    lVar2 = FUN_140078030(lVar2,
                          " of the Protocol Buffer runtime library, but the installed version is ");
    lVar2 = FUN_140077ff0(lVar2,local_68);
    lVar2 = FUN_140078030(lVar2,
                          ".  Please update your library.  If you compiled the program yourself, make sure that your headers are from the same version of Protocol Buffers as your link-time library.  (Version verification failed in \""
                         );
    lVar2 = FUN_140078030(lVar2,param_3);
    piVar1 = (int *)FUN_140078030(lVar2,"\".)");
    FUN_140078580(local_1a8,piVar1);
    FUN_140078440((longlong)local_1a0);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_160);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_138);
  }
  if (param_1 < 0x1e9bf0) {
    puVar3 = local_110;
    for (lVar2 = 1; lVar2 != 0; lVar2 = lVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    local_40 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_140077d40(local_a0,0x1e9bf1);
    local_38 = local_40;
    local_30 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_140077d40(local_c8,param_1);
    local_28 = local_30;
    local_20 = FUN_1400783d0(local_108,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\stubs\\common.cc"
                             ,0x48);
    local_18 = local_20;
    lVar2 = FUN_140078030((longlong)local_20,"This program was compiled against version ");
    lVar2 = FUN_140077ff0(lVar2,local_28);
    lVar2 = FUN_140078030(lVar2,
                          " of the Protocol Buffer runtime library, which is not compatible with the installed version ("
                         );
    lVar2 = FUN_140077ff0(lVar2,local_38);
    lVar2 = FUN_140078030(lVar2,
                          ").  Contact the program author for an update.  If you compiled the program yourself, make sure that your headers are from the same version of Protocol Buffers as your link-time library.  (Version verification failed in \""
                         );
    lVar2 = FUN_140078030(lVar2,param_3);
    piVar1 = (int *)FUN_140078030(lVar2,"\".)");
    FUN_140078580(local_110,piVar1);
    FUN_140078440((longlong)local_108);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_c8);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_a0);
  }
  return;
}


// ==== FUN_140077d40 @ 140077d40  undefined FUN_140077d40(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_1, int param_2)

void FUN_140077d40(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                   *param_1,int param_2)

{
  undefined1 auStack_f8 [32];
  undefined4 local_d8;
  int local_d0;
  int local_c8;
  undefined4 local_c4;
  uint local_c0;
  char local_a8 [127];
  undefined1 local_29;
  uint local_28;
  undefined8 local_20;
  ulonglong local_18;
  
  local_20 = 0xfffffffffffffffe;
  local_18 = DAT_140103510 ^ (ulonglong)auStack_f8;
  local_28 = 0;
  local_c0 = param_2 / 1000000;
  local_d8 = (undefined4)
             ((longlong)
              ((ulonglong)(uint)((int)((longlong)param_2 / 1000) >> 0x1f) << 0x20 |
              (longlong)param_2 / 1000 & 0xffffffffU) % 1000);
  local_d0 = param_2 % 1000;
  local_c8 = local_d0;
  local_c4 = local_d8;
  _snprintf(local_a8,0x80,"%d.%d.%d",(ulonglong)local_c0);
  local_29 = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(param_1,local_a8);
  local_28 = local_28 | 1;
  __security_check_cookie(local_18 ^ (ulonglong)auStack_f8);
  return;
}


// ==== FUN_140077e40 @ 140077e40  undefined FUN_140077e40(int param_1, undefined8 param_2, undefined8 param_3, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_4)

/* WARNING: Restarted to delay deadcode elimination for space: register */

void FUN_140077e40(int param_1,undefined8 param_2,undefined8 param_3,
                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_4)

{
  FILE *pFVar1;
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::c_str(param_4);
  pFVar1 = __iob_func();
  fprintf(pFVar1 + 2,"[libprotobuf %s %s:%d] %s\n",(&PTR_DAT_1401035d0)[param_1],param_2);
  pFVar1 = __iob_func();
  fflush(pFVar1 + 2);
  return;
}


// ==== FUN_140077ef0 @ 140077ef0  undefined FUN_140077ef0(void)

void FUN_140077ef0(void)

{
  if (DAT_140104ce0 != (undefined8 *)0x0) {
    FUN_140078af0(DAT_140104ce0,1);
  }
  DAT_140104ce0 = (undefined8 *)0x0;
  return;
}


// ==== FUN_140077f50 @ 140077f50  undefined FUN_140077f50(void)

void FUN_140077f50(void)

{
  undefined8 *puVar1;
  undefined8 *local_10;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    local_10 = (undefined8 *)0x0;
  }
  else {
    local_10 = FUN_140078730(puVar1);
  }
  DAT_140104ce0 = local_10;
  FUN_140078930(FUN_140077ef0);
  return;
}


// ==== FUN_140077fc0 @ 140077fc0  undefined FUN_140077fc0(void)

void FUN_140077fc0(void)

{
  FUN_140078b30((longlong *)&DAT_140104ce8,FUN_140077f50);
  return;
}


// ==== FUN_140077ff0 @ 140077ff0  longlong FUN_140077ff0(longlong param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

longlong FUN_140077ff0(longlong param_1,
                      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                      *param_2)

{
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18),param_2);
  return param_1;
}


// ==== FUN_140078030 @ 140078030  longlong FUN_140078030(longlong param_1, char * param_2)

longlong FUN_140078030(longlong param_1,char *param_2)

{
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18),param_2);
  return param_1;
}


// ==== FUN_140078070 @ 140078070  undefined FUN_140078070(longlong param_1, char param_2)

void FUN_140078070(longlong param_1,char param_2)

{
  undefined1 auStack_c8 [48];
  char local_98 [127];
  undefined1 local_19;
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_c8;
  _snprintf(local_98,0x80,"%c",(ulonglong)(uint)(int)param_2);
  local_19 = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18),local_98);
  __security_check_cookie(local_18 ^ (ulonglong)auStack_c8);
  return;
}


// ==== FUN_140078100 @ 140078100  undefined FUN_140078100(longlong param_1, uint param_2)

void FUN_140078100(longlong param_1,uint param_2)

{
  undefined1 auStack_c8 [48];
  char local_98 [127];
  undefined1 local_19;
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_c8;
  _snprintf(local_98,0x80,"%d",(ulonglong)param_2);
  local_19 = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18),local_98);
  __security_check_cookie(local_18 ^ (ulonglong)auStack_c8);
  return;
}


// ==== FUN_140078190 @ 140078190  undefined FUN_140078190(longlong param_1, uint param_2)

void FUN_140078190(longlong param_1,uint param_2)

{
  undefined1 auStack_c8 [48];
  char local_98 [127];
  undefined1 local_19;
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_c8;
  _snprintf(local_98,0x80,"%u",(ulonglong)param_2);
  local_19 = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18),local_98);
  __security_check_cookie(local_18 ^ (ulonglong)auStack_c8);
  return;
}


// ==== FUN_140078220 @ 140078220  undefined FUN_140078220(longlong param_1, uint param_2)

void FUN_140078220(longlong param_1,uint param_2)

{
  undefined1 auStack_c8 [48];
  char local_98 [127];
  undefined1 local_19;
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_c8;
  _snprintf(local_98,0x80,"%ld",(ulonglong)param_2);
  local_19 = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18),local_98);
  __security_check_cookie(local_18 ^ (ulonglong)auStack_c8);
  return;
}


// ==== FUN_1400782b0 @ 1400782b0  undefined FUN_1400782b0(longlong param_1, uint param_2)

void FUN_1400782b0(longlong param_1,uint param_2)

{
  undefined1 auStack_c8 [48];
  char local_98 [127];
  undefined1 local_19;
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_c8;
  _snprintf(local_98,0x80,"%lu",(ulonglong)param_2);
  local_19 = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18),local_98);
  __security_check_cookie(local_18 ^ (ulonglong)auStack_c8);
  return;
}


// ==== FUN_140078340 @ 140078340  undefined FUN_140078340(longlong param_1, undefined8 param_2)

void FUN_140078340(longlong param_1,undefined8 param_2)

{
  undefined1 auStack_c8 [48];
  char local_98 [127];
  undefined1 local_19;
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_c8;
  _snprintf(local_98,0x80,"%g",param_2);
  local_19 = 0;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18),local_98);
  __security_check_cookie(local_18 ^ (ulonglong)auStack_c8);
  return;
}


// ==== FUN_1400783d0 @ 1400783d0  undefined4 * FUN_1400783d0(undefined4 * param_1, undefined4 param_2, undefined8 param_3, undefined4 param_4)

undefined4 *
FUN_1400783d0(undefined4 *param_1,undefined4 param_2,undefined8 param_3,undefined4 param_4)

{
  *param_1 = param_2;
  *(undefined8 *)(param_1 + 2) = param_3;
  param_1[4] = param_4;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 6));
  return param_1;
}


// ==== FUN_140078440 @ 140078440  undefined FUN_140078440(longlong param_1)

void FUN_140078440(longlong param_1)

{
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18));
  return;
}


// ==== FUN_140078470 @ 140078470  undefined FUN_140078470(int * param_1)

void FUN_140078470(int *param_1)

{
  bool bVar1;
  undefined8 local_70;
  exception local_68 [80];
  undefined8 local_18;
  uint local_10;
  
  local_18 = 0xfffffffffffffffe;
  bVar1 = false;
  if (*param_1 != 3) {
    FUN_140077fc0();
    FUN_140078d20(&local_70,DAT_140104ce0);
    bVar1 = 0 < DAT_140104cd8;
    local_10 = (uint)bVar1;
    FUN_140078d60(&local_70);
  }
  if (!bVar1) {
    (*(code *)PTR_FUN_1401035c8)(*param_1,*(undefined8 *)(param_1 + 2),param_1[4],param_1 + 6);
  }
  if (*param_1 == 3) {
    FUN_140078d80(local_68,*(undefined8 *)(param_1 + 2),param_1[4],
                  (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                  (param_1 + 6));
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_68,(ThrowInfo *)&DAT_1400fee98);
  }
  return;
}


// ==== FUN_140078580 @ 140078580  undefined FUN_140078580(undefined8 param_1, int * param_2)

void FUN_140078580(undefined8 param_1,int *param_2)

{
  FUN_140078470(param_2);
  return;
}


// ==== FUN_1400785b0 @ 1400785b0  undefined * FUN_1400785b0(undefined * param_1)

undefined * FUN_1400785b0(undefined *param_1)

{
  undefined *local_18;
  
  local_18 = PTR_FUN_1401035c8;
  if (PTR_FUN_1401035c8 == &LAB_140077ed0) {
    local_18 = (undefined *)0x0;
  }
  PTR_FUN_1401035c8 = param_1;
  if (param_1 == (undefined *)0x0) {
    PTR_FUN_1401035c8 = &LAB_140077ed0;
  }
  return local_18;
}


// ==== FUN_140078610 @ 140078610  undefined8 FUN_140078610(undefined8 param_1)

undefined8 FUN_140078610(undefined8 param_1)

{
  undefined8 local_18;
  undefined8 local_10;
  
  local_10 = 0xfffffffffffffffe;
  FUN_140077fc0();
  FUN_140078d20(&local_18,DAT_140104ce0);
  DAT_140104cd8 = DAT_140104cd8 + 1;
  FUN_140078d60(&local_18);
  return param_1;
}


// ==== FUN_140078670 @ 140078670  undefined FUN_140078670(void)

void FUN_140078670(void)

{
  undefined8 local_18;
  undefined8 local_10;
  
  local_10 = 0xfffffffffffffffe;
  FUN_140077fc0();
  FUN_140078d20(&local_18,DAT_140104ce0);
  DAT_140104cd8 = DAT_140104cd8 + -1;
  FUN_140078d60(&local_18);
  return;
}


// ==== FUN_1400786c0 @ 1400786c0  undefined FUN_1400786c0(undefined8 * param_1)

void FUN_1400786c0(undefined8 *param_1)

{
  *param_1 = google::protobuf::Closure::vftable;
  return;
}


// ==== FUN_1400786e0 @ 1400786e0  undefined FUN_1400786e0(undefined8 * param_1)

void FUN_1400786e0(undefined8 *param_1)

{
  *param_1 = google::protobuf::internal::FunctionClosure0::vftable;
  FUN_1400786c0(param_1);
  return;
}


// ==== FUN_140078730 @ 140078730  undefined8 * FUN_140078730(undefined8 * param_1)

undefined8 * FUN_140078730(undefined8 *param_1)

{
  void *pvVar1;
  
  pvVar1 = operator_new(0x28);
  *param_1 = pvVar1;
  InitializeCriticalSection((LPCRITICAL_SECTION)*param_1);
  return param_1;
}


// ==== FUN_140078780 @ 140078780  undefined FUN_140078780(undefined8 * param_1)

void FUN_140078780(undefined8 *param_1)

{
  DeleteCriticalSection((LPCRITICAL_SECTION)*param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_1400787c0 @ 1400787c0  undefined FUN_1400787c0(undefined8 * param_1)

void FUN_1400787c0(undefined8 *param_1)

{
  EnterCriticalSection((LPCRITICAL_SECTION)*param_1);
  return;
}


// ==== FUN_1400787f0 @ 1400787f0  undefined FUN_1400787f0(undefined8 * param_1)

void FUN_1400787f0(undefined8 *param_1)

{
  LeaveCriticalSection((LPCRITICAL_SECTION)*param_1);
  return;
}


// ==== FUN_140078820 @ 140078820  undefined FUN_140078820(void)

void FUN_140078820(void)

{
  return;
}


// ==== FUN_140078830 @ 140078830  undefined4 FUN_140078830(undefined4 param_1)

undefined4 FUN_140078830(undefined4 param_1)

{
  undefined4 local_18;
  
  local_18 = CONCAT13((char)param_1,
                      CONCAT12((char)((uint)param_1 >> 8),
                               CONCAT11((char)((uint)param_1 >> 0x10),(char)((uint)param_1 >> 0x18))
                              ));
  return local_18;
}


// ==== FUN_140078880 @ 140078880  undefined FUN_140078880(void)

void FUN_140078880(void)

{
  undefined8 *puVar1;
  undefined8 local_20;
  undefined8 local_18;
  
  puVar1 = (undefined8 *)operator_new(0x30);
  if (puVar1 == (undefined8 *)0x0) {
    local_20 = (undefined8 *)0x0;
  }
  else {
    local_20 = FUN_140078f20(puVar1);
  }
  DAT_140104cf0 = local_20;
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    local_18 = (undefined8 *)0x0;
  }
  else {
    local_18 = FUN_140078730(puVar1);
  }
  DAT_140104cf8 = local_18;
  return;
}


// ==== FUN_140078930 @ 140078930  undefined FUN_140078930(undefined8 param_1)

void FUN_140078930(undefined8 param_1)

{
  undefined8 local_res8 [4];
  undefined8 local_18;
  undefined8 local_10;
  
  local_10 = 0xfffffffffffffffe;
  local_res8[0] = param_1;
  FUN_140078ec0();
  FUN_140078d20(&local_18,DAT_140104cf8);
  FUN_140079020(DAT_140104cf0,local_res8);
  FUN_140078d60(&local_18);
  return;
}


// ==== FUN_140078980 @ 140078980  undefined FUN_140078980(void)

void FUN_140078980(void)

{
  ulonglong uVar1;
  undefined8 *puVar2;
  int local_48;
  
  FUN_140078ec0();
  if (DAT_140104cf0 != (undefined8 *)0x0) {
    for (local_48 = 0; uVar1 = FUN_140078fa0((longlong)DAT_140104cf0),
        (ulonglong)(longlong)local_48 < uVar1; local_48 = local_48 + 1) {
      puVar2 = (undefined8 *)FUN_140078fc0(DAT_140104cf0,(longlong)local_48);
      (*(code *)*puVar2)();
    }
    if (DAT_140104cf0 != (undefined8 *)0x0) {
      FUN_140078ee0(DAT_140104cf0,1);
    }
    DAT_140104cf0 = (undefined8 *)0x0;
    if (DAT_140104cf8 != (undefined8 *)0x0) {
      FUN_140078af0(DAT_140104cf8,1);
    }
    DAT_140104cf8 = (undefined8 *)0x0;
  }
  return;
}


// ==== FUN_140078a80 @ 140078a80  undefined FUN_140078a80(exception * param_1)

void FUN_140078a80(exception *param_1)

{
  *(undefined ***)param_1 = google::protobuf::FatalException::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x28));
  std::exception::~exception(param_1);
  return;
}


// ==== FUN_140078af0 @ 140078af0  undefined8 * FUN_140078af0(undefined8 * param_1, uint param_2)

undefined8 * FUN_140078af0(undefined8 *param_1,uint param_2)

{
  FUN_140078780(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_140078b30 @ 140078b30  undefined FUN_140078b30(longlong * param_1, undefined8 param_2)

void FUN_140078b30(longlong *param_1,undefined8 param_2)

{
  longlong lVar1;
  longlong local_28 [3];
  undefined8 local_10;
  
  local_10 = 0xfffffffffffffffe;
  lVar1 = FUN_140078d00(param_1);
  if (lVar1 != 2) {
    FUN_140078b90(local_28,param_2,0);
    FUN_14007f360(param_1,local_28);
    FUN_1400786e0(local_28);
  }
  return;
}


// ==== FUN_140078b90 @ 140078b90  undefined8 * FUN_140078b90(undefined8 * param_1, undefined8 param_2, undefined1 param_3)

undefined8 * FUN_140078b90(undefined8 *param_1,undefined8 param_2,undefined1 param_3)

{
  FUN_140078bf0(param_1);
  *param_1 = google::protobuf::internal::FunctionClosure0::vftable;
  param_1[1] = param_2;
  *(undefined1 *)(param_1 + 2) = param_3;
  return param_1;
}


// ==== FUN_140078bf0 @ 140078bf0  undefined8 * FUN_140078bf0(undefined8 * param_1)

undefined8 * FUN_140078bf0(undefined8 *param_1)

{
  *param_1 = google::protobuf::Closure::vftable;
  return param_1;
}


// ==== FUN_140078d00 @ 140078d00  undefined8 FUN_140078d00(undefined8 * param_1)

undefined8 FUN_140078d00(undefined8 *param_1)

{
  return *param_1;
}


// ==== FUN_140078d20 @ 140078d20  undefined8 * FUN_140078d20(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_140078d20(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = param_2;
  FUN_1400787c0((undefined8 *)*param_1);
  return param_1;
}


// ==== FUN_140078d60 @ 140078d60  undefined FUN_140078d60(undefined8 * param_1)

void FUN_140078d60(undefined8 *param_1)

{
  FUN_1400787f0((undefined8 *)*param_1);
  return;
}


// ==== FUN_140078d80 @ 140078d80  exception * FUN_140078d80(exception * param_1, undefined8 param_2, undefined4 param_3, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_4)

exception *
FUN_140078d80(exception *param_1,undefined8 param_2,undefined4 param_3,
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_4)

{
  std::exception::exception(param_1);
  *(undefined ***)param_1 = google::protobuf::FatalException::vftable;
  *(undefined8 *)(param_1 + 0x18) = param_2;
  *(undefined4 *)(param_1 + 0x20) = param_3;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x28),param_4);
  return param_1;
}


// ==== FUN_140078e40 @ 140078e40  exception * FUN_140078e40(exception * param_1, exception * param_2)

exception * FUN_140078e40(exception *param_1,exception *param_2)

{
  std::exception::exception(param_1,param_2);
  *(undefined ***)param_1 = google::protobuf::FatalException::vftable;
  *(undefined8 *)(param_1 + 0x18) = *(undefined8 *)(param_2 + 0x18);
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_2 + 0x20);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x28),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 0x28));
  return param_1;
}


// ==== FUN_140078ec0 @ 140078ec0  undefined FUN_140078ec0(void)

void FUN_140078ec0(void)

{
  FUN_140078b30((longlong *)&DAT_140104d00,FUN_140078880);
  return;
}


// ==== FUN_140078ee0 @ 140078ee0  undefined8 * FUN_140078ee0(undefined8 * param_1, uint param_2)

undefined8 * FUN_140078ee0(undefined8 *param_1,uint param_2)

{
  FUN_140078f70(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_140078f20 @ 140078f20  undefined8 * FUN_140078f20(undefined8 * param_1)

undefined8 * FUN_140078f20(undefined8 *param_1)

{
  undefined1 local_28 [8];
  undefined1 *local_20;
  undefined8 local_18;
  
  local_18 = 0xfffffffffffffffe;
  local_20 = local_28;
  FUN_140079550(local_20);
  FUN_1400794b0(param_1);
  FUN_1400792c0((longlong)param_1,0);
  return param_1;
}


// ==== FUN_140078f70 @ 140078f70  undefined FUN_140078f70(undefined8 * param_1)

void FUN_140078f70(undefined8 *param_1)

{
  FUN_140079370((longlong)param_1);
  FUN_140079100(param_1);
  return;
}


// ==== FUN_140078fa0 @ 140078fa0  longlong FUN_140078fa0(longlong param_1)

longlong FUN_140078fa0(longlong param_1)

{
  return *(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18) >> 3;
}


// ==== FUN_140078fc0 @ 140078fc0  undefined FUN_140078fc0(undefined8 * param_1, ulonglong param_2)

void FUN_140078fc0(undefined8 *param_1,ulonglong param_2)

{
  ulonglong uVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  undefined8 local_28 [2];
  undefined1 local_18 [24];
  
  uVar1 = FUN_140078fa0((longlong)param_1);
  if (uVar1 <= param_2) {
    FUN_140079450();
  }
  puVar2 = FUN_140079180(param_1,local_28);
  plVar3 = (longlong *)FUN_140079580((undefined1 *)puVar2,local_18,param_2);
  FUN_140079560(plVar3);
  return;
}


// ==== FUN_140079020 @ 140079020  undefined FUN_140079020(undefined8 * param_1, undefined8 * param_2)

void FUN_140079020(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  ulonglong uVar2;
  longlong lVar3;
  undefined8 *puVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  longlong *plVar7;
  undefined1 local_68 [16];
  undefined8 local_58 [2];
  undefined1 local_48 [16];
  longlong local_38 [2];
  undefined1 local_28 [24];
  
  uVar1 = FUN_140078fa0((longlong)param_1);
  uVar2 = FUN_140079130((longlong)param_1);
  if (uVar1 < uVar2) {
    lVar3 = FUN_140079400(param_1,param_1[4],1,param_2);
    param_1[4] = lVar3;
  }
  else {
    puVar4 = FUN_1400791b0(param_1,local_58);
    puVar5 = local_28;
    for (lVar3 = 0x10; lVar3 != 0; lVar3 = lVar3 + -1) {
      *puVar5 = *(undefined1 *)puVar4;
      puVar4 = (undefined8 *)((longlong)puVar4 + 1);
      puVar5 = puVar5 + 1;
    }
    puVar5 = local_28;
    puVar6 = local_68;
    for (lVar3 = 0x10; lVar3 != 0; lVar3 = lVar3 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
    puVar5 = local_68;
    plVar7 = local_38;
    for (lVar3 = 0x10; lVar3 != 0; lVar3 = lVar3 + -1) {
      *(undefined1 *)plVar7 = *puVar5;
      puVar5 = puVar5 + 1;
      plVar7 = (longlong *)((longlong)plVar7 + 1);
    }
    FUN_1400791e0(param_1,local_48,local_38,param_2);
  }
  return;
}


// ==== FUN_140079100 @ 140079100  undefined FUN_140079100(undefined8 * param_1)

void FUN_140079100(undefined8 *param_1)

{
  FUN_140079510(param_1);
  return;
}


// ==== FUN_140079130 @ 140079130  longlong FUN_140079130(longlong param_1)

longlong FUN_140079130(longlong param_1)

{
  undefined8 local_18;
  
  if (*(longlong *)(param_1 + 0x18) == 0) {
    local_18 = 0;
  }
  else {
    local_18 = *(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x18) >> 3;
  }
  return local_18;
}


// ==== FUN_140079180 @ 140079180  undefined8 * FUN_140079180(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140079180(undefined8 *param_1,undefined8 *param_2)

{
  FUN_140079cb0(param_2,param_1[3],param_1);
  return param_2;
}


// ==== FUN_1400791b0 @ 1400791b0  undefined8 * FUN_1400791b0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_1400791b0(undefined8 *param_1,undefined8 *param_2)

{
  FUN_140079cb0(param_2,param_1[4],param_1);
  return param_2;
}


// ==== FUN_1400791e0 @ 1400791e0  undefined1 * FUN_1400791e0(undefined8 * param_1, undefined1 * param_2, longlong * param_3, undefined8 * param_4)

undefined1 *
FUN_1400791e0(undefined8 *param_1,undefined1 *param_2,longlong *param_3,undefined8 *param_4)

{
  longlong lVar1;
  longlong *plVar2;
  undefined8 *puVar3;
  longlong lVar4;
  undefined1 *puVar5;
  undefined8 local_60 [2];
  undefined8 local_50 [3];
  undefined1 local_38 [16];
  longlong local_28;
  
  lVar1 = FUN_140078fa0((longlong)param_1);
  if (lVar1 == 0) {
    local_28 = 0;
  }
  else {
    plVar2 = FUN_140079180(param_1,local_60);
    local_28 = FUN_140079d70(param_3,plVar2);
  }
  lVar1 = local_28;
  puVar5 = local_38;
  for (lVar4 = 0x10; lVar4 != 0; lVar4 = lVar4 + -1) {
    *puVar5 = (char)*param_3;
    param_3 = (longlong *)((longlong)param_3 + 1);
    puVar5 = puVar5 + 1;
  }
  FUN_140079650((longlong)param_1,(longlong)local_38,1,param_4);
  puVar3 = FUN_140079180(param_1,local_50);
  FUN_140079580((undefined1 *)puVar3,param_2,lVar1);
  return param_2;
}


// ==== FUN_1400792c0 @ 1400792c0  undefined8 FUN_1400792c0(longlong param_1, ulonglong param_2)

ulonglong FUN_1400792c0(longlong param_1,ulonglong param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  if (param_2 == 0) {
    uVar1 = param_1 & 0xffffffffffffff00;
  }
  else {
    uVar1 = FUN_140079600();
    if (uVar1 < param_2) {
      param_1 = FUN_140079b40();
    }
    else {
      uVar2 = FUN_140079c90(param_1 + 0x10,param_2);
      *(undefined8 *)(param_1 + 0x18) = uVar2;
      *(undefined8 *)(param_1 + 0x20) = *(undefined8 *)(param_1 + 0x18);
      *(ulonglong *)(param_1 + 0x28) = *(longlong *)(param_1 + 0x18) + param_2 * 8;
    }
    uVar1 = CONCAT71((int7)((ulonglong)param_1 >> 8),1);
  }
  return uVar1;
}


// ==== FUN_140079370 @ 140079370  undefined FUN_140079370(longlong param_1)

void FUN_140079370(longlong param_1)

{
  if (*(longlong *)(param_1 + 0x18) != 0) {
    FUN_140079620();
    FUN_140079c60(param_1 + 0x10,*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_140079400 @ 140079400  longlong FUN_140079400(undefined8 param_1, longlong param_2, longlong param_3, undefined8 * param_4)

longlong FUN_140079400(undefined8 param_1,longlong param_2,longlong param_3,undefined8 *param_4)

{
  FUN_140079f70(param_2,param_3,param_4);
  return param_2 + param_3 * 8;
}


// ==== FUN_140079450 @ 140079450  undefined FUN_140079450(void)

void FUN_140079450(void)

{
  exception local_78 [64];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_38 [40];
  undefined8 local_10;
  
  local_10 = 0xfffffffffffffffe;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_38,"invalid vector<T> subscript");
  FUN_14001dc20(local_78,local_38);
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_78,(ThrowInfo *)&DAT_1400feda0);
}


// ==== FUN_1400794b0 @ 1400794b0  undefined8 * FUN_1400794b0(undefined8 * param_1)

undefined8 * FUN_1400794b0(undefined8 *param_1)

{
  undefined1 local_28 [8];
  undefined1 *local_20;
  undefined8 local_18;
  
  local_18 = 0xfffffffffffffffe;
  local_20 = local_28;
  FUN_140079c50(local_20);
  FUN_140079ba0(param_1);
  FUN_140079c50(param_1 + 2);
  return param_1;
}


// ==== FUN_140079510 @ 140079510  undefined FUN_140079510(undefined8 * param_1)

void FUN_140079510(undefined8 *param_1)

{
  FUN_14001dfd0(param_1 + 1,(void *)*param_1);
  FUN_14001da00();
  return;
}


// ==== FUN_140079550 @ 140079550  undefined8 FUN_140079550(undefined8 param_1)

undefined8 FUN_140079550(undefined8 param_1)

{
  return param_1;
}


// ==== FUN_140079560 @ 140079560  undefined FUN_140079560(longlong * param_1)

void FUN_140079560(longlong *param_1)

{
  FUN_140079d20(param_1);
  return;
}


// ==== FUN_140079580 @ 140079580  undefined1 * FUN_140079580(undefined1 * param_1, undefined1 * param_2, longlong param_3)

undefined1 * FUN_140079580(undefined1 *param_1,undefined1 *param_2,longlong param_3)

{
  longlong *plVar1;
  longlong lVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  longlong local_48 [2];
  undefined1 local_38 [16];
  undefined1 local_28 [24];
  
  puVar3 = local_28;
  for (lVar2 = 0x10; lVar2 != 0; lVar2 = lVar2 + -1) {
    *puVar3 = *param_1;
    param_1 = param_1 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar3 = local_28;
  plVar1 = local_48;
  for (lVar2 = 0x10; lVar2 != 0; lVar2 = lVar2 + -1) {
    *(undefined1 *)plVar1 = *puVar3;
    puVar3 = puVar3 + 1;
    plVar1 = (longlong *)((longlong)plVar1 + 1);
  }
  plVar1 = FUN_140079cf0(local_48,param_3);
  puVar3 = local_38;
  for (lVar2 = 0x10; lVar2 != 0; lVar2 = lVar2 + -1) {
    *puVar3 = (char)*plVar1;
    plVar1 = (longlong *)((longlong)plVar1 + 1);
    puVar3 = puVar3 + 1;
  }
  puVar3 = local_38;
  puVar4 = param_2;
  for (lVar2 = 0x10; lVar2 != 0; lVar2 = lVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  return param_2;
}


// ==== FUN_140079600 @ 140079600  undefined FUN_140079600(void)

void FUN_140079600(void)

{
  max_size();
  return;
}


// ==== FUN_140079620 @ 140079620  undefined FUN_140079620(void)

void FUN_140079620(void)

{
  FUN_140079fe0();
  return;
}


// ==== FUN_140079650 @ 140079650  undefined FUN_140079650(longlong param_1, longlong param_2, ulonglong param_3, undefined8 * param_4)

void FUN_140079650(longlong param_1,longlong param_2,ulonglong param_3,undefined8 *param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  longlong lVar3;
  void *pvVar4;
  undefined8 uVar5;
  ulonglong local_58;
  undefined8 local_38;
  longlong local_30;
  undefined8 local_28;
  undefined8 local_20;
  ulonglong local_18;
  
  local_20 = 0xfffffffffffffffe;
  uVar1 = FUN_140079130(param_1);
  if (param_3 != 0) {
    lVar2 = FUN_140079600();
    lVar3 = FUN_140078fa0(param_1);
    if ((ulonglong)(lVar2 - lVar3) < param_3) {
      FUN_140079b40();
    }
    else {
      lVar2 = FUN_140078fa0(param_1);
      if (uVar1 < lVar2 + param_3) {
        lVar2 = FUN_140079600();
        if (lVar2 - uVar1 / 2 < uVar1) {
          local_18 = 0;
        }
        else {
          local_18 = uVar1 + uVar1 / 2;
        }
        uVar1 = local_18;
        local_58 = local_18;
        lVar2 = FUN_140078fa0(param_1);
        if (uVar1 < lVar2 + param_3) {
          lVar2 = FUN_140078fa0(param_1);
          local_58 = lVar2 + param_3;
        }
        pvVar4 = (void *)FUN_140079c90(param_1 + 0x10,local_58);
        lVar2 = *(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18) >> 3;
        FUN_140079400(param_1,(longlong)((longlong)pvVar4 + lVar2 * 8),param_3,param_4);
        FUN_14007a030(param_1,*(undefined8 *)(param_1 + 0x18),*(undefined8 *)(param_2 + 8),pvVar4);
        FUN_14007a030(param_1,*(undefined8 *)(param_2 + 8),*(undefined8 *)(param_1 + 0x20),
                      (void *)((longlong)pvVar4 + (lVar2 + param_3) * 8));
        lVar2 = FUN_140078fa0(param_1);
        if (*(longlong *)(param_1 + 0x18) != 0) {
          FUN_140079620();
          FUN_140079c60(param_1 + 0x10,*(void **)(param_1 + 0x18));
        }
        *(void **)(param_1 + 0x28) = (void *)((longlong)pvVar4 + local_58 * 8);
        *(void **)(param_1 + 0x20) = (void *)((longlong)pvVar4 + (param_3 + lVar2) * 8);
        *(void **)(param_1 + 0x18) = pvVar4;
      }
      else if ((ulonglong)(*(longlong *)(param_1 + 0x20) - *(longlong *)(param_2 + 8) >> 3) <
               param_3) {
        local_38 = *param_4;
        FUN_14007a030(param_1,*(undefined8 *)(param_2 + 8),*(undefined8 *)(param_1 + 0x20),
                      (void *)(*(longlong *)(param_2 + 8) + param_3 * 8));
        FUN_140079400(param_1,*(longlong *)(param_1 + 0x20),
                      param_3 - (*(longlong *)(param_1 + 0x20) - *(longlong *)(param_2 + 8) >> 3),
                      &local_38);
        *(ulonglong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + param_3 * 8;
        FUN_14007a070(*(undefined8 *)(param_2 + 8),*(longlong *)(param_1 + 0x20) + param_3 * -8,
                      &local_38);
      }
      else {
        local_28 = *param_4;
        local_30 = *(longlong *)(param_1 + 0x20);
        uVar5 = FUN_14007a030(param_1,local_30 + param_3 * -8,local_30,*(void **)(param_1 + 0x20));
        *(undefined8 *)(param_1 + 0x20) = uVar5;
        FUN_14007a0c0(*(undefined8 *)(param_2 + 8),local_30 + param_3 * -8,local_30);
        FUN_14007a070(*(undefined8 *)(param_2 + 8),*(longlong *)(param_2 + 8) + param_3 * 8,
                      &local_28);
      }
    }
  }
  return;
}


// ==== FUN_140079b40 @ 140079b40  undefined FUN_140079b40(void)

void FUN_140079b40(void)

{
  exception local_78 [64];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_38 [40];
  undefined8 local_10;
  
  local_10 = 0xfffffffffffffffe;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_38,"vector<T> too long");
  FUN_14001f4f0(local_78,local_38);
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_78,(ThrowInfo *)&DAT_1400fee30);
}


// ==== FUN_140079ba0 @ 140079ba0  undefined8 * FUN_140079ba0(undefined8 * param_1)

undefined8 * FUN_140079ba0(undefined8 *param_1)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  undefined8 *local_18;
  
  FUN_14001d9f0(param_1);
  FUN_14007a150(param_1 + 1);
  uVar1 = FUN_14001e6f0(param_1 + 1,1);
  puVar2 = (undefined8 *)FUN_14001d9c0(8,uVar1);
  if (puVar2 == (undefined8 *)0x0) {
    local_18 = (undefined8 *)0x0;
  }
  else {
    local_18 = FUN_14001d9e0(puVar2,param_1);
  }
  *param_1 = local_18;
  return param_1;
}


// ==== FUN_140079c50 @ 140079c50  undefined8 FUN_140079c50(undefined8 param_1)

undefined8 FUN_140079c50(undefined8 param_1)

{
  return param_1;
}


// ==== FUN_140079c60 @ 140079c60  undefined FUN_140079c60(undefined8 param_1, void * param_2)

void FUN_140079c60(undefined8 param_1,void *param_2)

{
  operator_delete(param_2);
  return;
}


// ==== FUN_140079c90 @ 140079c90  undefined FUN_140079c90(undefined8 param_1, ulonglong param_2)

void FUN_140079c90(undefined8 param_1,ulonglong param_2)

{
  FUN_14007a160(param_2);
  return;
}


// ==== FUN_140079cb0 @ 140079cb0  undefined8 * FUN_140079cb0(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140079cb0(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  FUN_140079e10(param_1,param_2,param_3);
  return param_1;
}


// ==== FUN_140079cf0 @ 140079cf0  longlong * FUN_140079cf0(longlong * param_1, longlong param_2)

longlong * FUN_140079cf0(longlong *param_1,longlong param_2)

{
  FUN_140079e90(param_1,param_2);
  return param_1;
}


// ==== FUN_140079d20 @ 140079d20  longlong FUN_140079d20(longlong * param_1)

longlong FUN_140079d20(longlong *param_1)

{
  bool bVar1;
  longlong lVar2;
  
  bVar1 = FUN_14001da40(param_1);
  if (!bVar1) {
    _invalid_parameter_noinfo();
  }
  lVar2 = FUN_14001f4e0(param_1);
  if (*(ulonglong *)(lVar2 + 0x20) <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_140079d70 @ 140079d70  longlong FUN_140079d70(longlong * param_1, longlong * param_2)

longlong FUN_140079d70(longlong *param_1,longlong *param_2)

{
  bool bVar1;
  
  bVar1 = FUN_14001da40(param_1);
  if (bVar1) {
    bVar1 = FUN_14001da30(param_1,param_2);
    if (bVar1) goto LAB_140079dab;
  }
  _invalid_parameter_noinfo();
LAB_140079dab:
  return param_1[1] - param_2[1] >> 3;
}


// ==== FUN_140079e10 @ 140079e10  undefined8 * FUN_140079e10(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140079e10(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  FUN_140079f30(param_1);
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  FUN_14001da20(param_1,param_3);
  param_1[1] = param_2;
  return param_1;
}


// ==== FUN_140079e90 @ 140079e90  longlong * FUN_140079e90(longlong * param_1, longlong param_2)

longlong * FUN_140079e90(longlong *param_1,longlong param_2)

{
  longlong lVar1;
  bool bVar2;
  longlong lVar3;
  
  bVar2 = FUN_14001da40(param_1);
  if (!bVar2) {
    _invalid_parameter_noinfo();
  }
  lVar1 = param_1[1];
  lVar3 = FUN_14001f4e0(param_1);
  if ((ulonglong)(lVar1 + param_2 * 8) <= *(ulonglong *)(lVar3 + 0x20)) {
    lVar1 = param_1[1];
    lVar3 = FUN_14001f4e0(param_1);
    if (*(ulonglong *)(lVar3 + 0x18) <= (ulonglong)(lVar1 + param_2 * 8)) goto LAB_140079f00;
  }
  _invalid_parameter_noinfo();
LAB_140079f00:
  param_1[1] = param_1[1] + param_2 * 8;
  return param_1;
}


// ==== FUN_140079f30 @ 140079f30  undefined8 * FUN_140079f30(undefined8 * param_1)

undefined8 * FUN_140079f30(undefined8 *param_1)

{
  FUN_140079f50(param_1);
  return param_1;
}


// ==== FUN_140079f50 @ 140079f50  undefined8 * FUN_140079f50(undefined8 * param_1)

undefined8 * FUN_140079f50(undefined8 *param_1)

{
  FUN_14001da10(param_1);
  return param_1;
}


// ==== FUN_140079f70 @ 140079f70  undefined FUN_140079f70(undefined8 param_1, longlong param_2, undefined8 * param_3)

void FUN_140079f70(undefined8 param_1,longlong param_2,undefined8 *param_3)

{
  longlong lVar1;
  undefined1 *puVar2;
  undefined1 local_18 [16];
  
  puVar2 = local_18;
  for (lVar1 = 1; lVar1 != 0; lVar1 = lVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  local_18[1] = FUN_14007a1d0();
  FUN_14007a1f0(param_1,param_2,param_3);
  return;
}


// ==== FUN_140079fe0 @ 140079fe0  undefined FUN_140079fe0(void)

void FUN_140079fe0(void)

{
  FUN_14007a1d0();
  FUN_14007a230();
  return;
}


// ==== FUN_14007a030 @ 14007a030  undefined FUN_14007a030(longlong param_1, undefined8 param_2, undefined8 param_3, void * param_4)

void FUN_14007a030(longlong param_1,undefined8 param_2,undefined8 param_3,void *param_4)

{
  FUN_14007a250(param_2,param_3,param_4,param_1 + 0x10);
  return;
}


// ==== FUN_14007a070 @ 14007a070  undefined FUN_14007a070(undefined8 param_1, undefined8 param_2, undefined8 * param_3)

void FUN_14007a070(undefined8 param_1,undefined8 param_2,undefined8 *param_3)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  undefined8 local_res8;
  undefined8 local_res10;
  undefined8 *local_res18;
  
  local_res8 = param_1;
  local_res10 = param_2;
  local_res18 = param_3;
  puVar1 = (undefined8 *)FUN_14007a2d0(&local_res10);
  puVar2 = (undefined8 *)FUN_14007a2d0(&local_res8);
  FUN_14007a2f0(puVar2,puVar1,local_res18);
  return;
}


// ==== FUN_14007a0c0 @ 14007a0c0  undefined FUN_14007a0c0(undefined8 param_1, undefined8 param_2, longlong param_3)

void FUN_14007a0c0(undefined8 param_1,undefined8 param_2,longlong param_3)

{
  void *pvVar1;
  longlong lVar2;
  undefined1 *puVar3;
  undefined8 local_res8;
  undefined8 local_res10;
  longlong local_res18;
  undefined1 local_28 [24];
  
  puVar3 = local_28;
  for (lVar2 = 1; lVar2 != 0; lVar2 = lVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  local_res8 = param_1;
  local_res10 = param_2;
  local_res18 = param_3;
  local_28[1] = FUN_14007a350();
  FUN_14007a330(local_28 + 2);
  lVar2 = FUN_14007a2d0(&local_res10);
  pvVar1 = (void *)FUN_14007a2d0(&local_res8);
  FUN_14007a370(pvVar1,lVar2,local_res18);
  return;
}


// ==== FUN_14007a150 @ 14007a150  undefined8 FUN_14007a150(undefined8 param_1)

undefined8 FUN_14007a150(undefined8 param_1)

{
  return param_1;
}


// ==== FUN_14007a160 @ 14007a160  undefined FUN_14007a160(ulonglong param_1)

void FUN_14007a160(ulonglong param_1)

{
  undefined1 auVar1 [16];
  ulonglong local_res8;
  exception local_28 [40];
  
  if (param_1 == 0) {
    local_res8 = 0;
  }
  else {
    auVar1._8_8_ = 0;
    auVar1._0_8_ = param_1;
    local_res8 = param_1;
    if (SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 8) {
      FUN_14001da50(local_28,(char *)0x0);
                    /* WARNING: Subroutine does not return */
      _CxxThrowException(local_28,(ThrowInfo *)&DAT_1400fed18);
    }
  }
  operator_new(local_res8 << 3);
  return;
}


// ==== FUN_14007a1d0 @ 14007a1d0  undefined1 FUN_14007a1d0(void)

undefined1 FUN_14007a1d0(void)

{
  undefined1 local_18;
  
  return local_18;
}


// ==== FUN_14007a1f0 @ 14007a1f0  undefined FUN_14007a1f0(undefined8 param_1, longlong param_2, undefined8 * param_3)

void FUN_14007a1f0(undefined8 param_1,longlong param_2,undefined8 *param_3)

{
  FUN_14007a3e0(param_1,param_2,param_3);
  return;
}


// ==== FUN_14007a230 @ 14007a230  undefined FUN_14007a230(void)

void FUN_14007a230(void)

{
  return;
}


// ==== FUN_14007a250 @ 14007a250  undefined FUN_14007a250(undefined8 param_1, undefined8 param_2, void * param_3, undefined8 param_4)

void FUN_14007a250(undefined8 param_1,undefined8 param_2,void *param_3,undefined8 param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  longlong lVar3;
  undefined1 *puVar4;
  undefined8 local_res8;
  undefined8 local_res10;
  void *local_res18;
  undefined8 local_res20;
  undefined1 local_18 [16];
  
  puVar4 = local_18;
  for (lVar3 = 1; lVar3 != 0; lVar3 = lVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  local_res8 = param_1;
  local_res10 = param_2;
  local_res18 = param_3;
  local_res20 = param_4;
  local_18[1] = FUN_14007a350();
  uVar1 = FUN_14007a2d0(&local_res10);
  uVar2 = FUN_14007a2d0(&local_res8);
  FUN_14007a440(uVar2,uVar1,local_res18,local_res20);
  return;
}


// ==== FUN_14007a2d0 @ 14007a2d0  undefined FUN_14007a2d0(undefined8 * param_1)

void FUN_14007a2d0(undefined8 *param_1)

{
  FUN_14007a480(param_1);
  return;
}


// ==== FUN_14007a2f0 @ 14007a2f0  undefined FUN_14007a2f0(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

void FUN_14007a2f0(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  undefined8 *local_res8;
  
  for (local_res8 = param_1; local_res8 != param_2; local_res8 = local_res8 + 1) {
    *local_res8 = *param_3;
  }
  return;
}


// ==== FUN_14007a330 @ 14007a330  undefined8 FUN_14007a330(undefined8 param_1)

undefined8 FUN_14007a330(undefined8 param_1)

{
  return param_1;
}


// ==== FUN_14007a350 @ 14007a350  undefined1 FUN_14007a350(void)

undefined1 FUN_14007a350(void)

{
  undefined1 local_18;
  
  return local_18;
}


// ==== FUN_14007a370 @ 14007a370  undefined FUN_14007a370(void * param_1, longlong param_2, longlong param_3)

void FUN_14007a370(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  undefined1 *puVar2;
  undefined1 local_18 [16];
  
  puVar2 = local_18;
  for (lVar1 = 1; lVar1 != 0; lVar1 = lVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  local_18[1] = FUN_14007a1d0();
  FUN_14007a4a0(param_1,param_2,param_3);
  return;
}


// ==== FUN_14007a3e0 @ 14007a3e0  undefined FUN_14007a3e0(undefined8 param_1, longlong param_2, undefined8 * param_3)

void FUN_14007a3e0(undefined8 param_1,longlong param_2,undefined8 *param_3)

{
  undefined1 *puVar1;
  longlong lVar2;
  undefined1 local_18 [16];
  
  puVar1 = local_18;
  for (lVar2 = 1; lVar2 != 0; lVar2 = lVar2 + -1) {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
  }
  puVar1 = (undefined1 *)FUN_14007a520(local_18 + 1);
  FUN_14007a540(param_1,param_2,param_3,*puVar1);
  return;
}


// ==== FUN_14007a440 @ 14007a440  undefined FUN_14007a440(undefined8 param_1, undefined8 param_2, void * param_3, undefined8 param_4)

void FUN_14007a440(undefined8 param_1,undefined8 param_2,void *param_3,undefined8 param_4)

{
  FUN_14007a5b0(param_1,param_2,param_3,param_4);
  return;
}


// ==== FUN_14007a480 @ 14007a480  undefined8 FUN_14007a480(undefined8 * param_1)

undefined8 FUN_14007a480(undefined8 *param_1)

{
  return *param_1;
}


// ==== FUN_14007a4a0 @ 14007a4a0  void * FUN_14007a4a0(void * param_1, longlong param_2, longlong param_3)

void * FUN_14007a4a0(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _Dst = (void *)(param_3 + lVar1 * -8);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 << 3,param_1,lVar1 << 3);
  }
  return _Dst;
}


// ==== FUN_14007a520 @ 14007a520  undefined8 FUN_14007a520(undefined8 param_1)

undefined8 FUN_14007a520(undefined8 param_1)

{
  return param_1;
}


// ==== FUN_14007a540 @ 14007a540  undefined FUN_14007a540(undefined8 param_1, longlong param_2, undefined8 * param_3, undefined1 param_4)

void FUN_14007a540(undefined8 param_1,longlong param_2,undefined8 *param_3,undefined1 param_4)

{
  undefined8 *puVar1;
  longlong lVar2;
  undefined1 *puVar3;
  undefined8 local_res8;
  longlong local_res10;
  undefined8 *local_res18;
  undefined1 local_res20;
  undefined1 local_10 [8];
  
  puVar3 = local_10;
  for (lVar2 = 1; lVar2 != 0; lVar2 = lVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  local_res8 = param_1;
  local_res10 = param_2;
  local_res18 = param_3;
  local_res20 = param_4;
  puVar1 = (undefined8 *)FUN_14007a2d0(&local_res8);
  FUN_14007a630(puVar1,local_res10,local_res18);
  return;
}


// ==== FUN_14007a5b0 @ 14007a5b0  undefined FUN_14007a5b0(undefined8 param_1, undefined8 param_2, void * param_3, undefined8 param_4)

void FUN_14007a5b0(undefined8 param_1,undefined8 param_2,void *param_3,undefined8 param_4)

{
  void *pvVar1;
  longlong lVar2;
  undefined1 *puVar3;
  undefined8 local_res8;
  undefined8 local_res10;
  void *local_res18;
  undefined8 local_res20;
  undefined1 local_18 [16];
  
  puVar3 = local_18;
  for (lVar2 = 1; lVar2 != 0; lVar2 = lVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  local_res8 = param_1;
  local_res10 = param_2;
  local_res18 = param_3;
  local_res20 = param_4;
  local_18[1] = FUN_14007a1d0();
  lVar2 = FUN_14007a2d0(&local_res10);
  pvVar1 = (void *)FUN_14007a2d0(&local_res8);
  FUN_14007a680(pvVar1,lVar2,local_res18);
  return;
}


// ==== FUN_14007a630 @ 14007a630  undefined FUN_14007a630(undefined8 * param_1, longlong param_2, undefined8 * param_3)

void FUN_14007a630(undefined8 *param_1,longlong param_2,undefined8 *param_3)

{
  undefined8 *local_res8;
  longlong local_res10;
  
  local_res8 = param_1;
  for (local_res10 = param_2; local_res10 != 0; local_res10 = local_res10 + -1) {
    *local_res8 = *param_3;
    local_res8 = local_res8 + 1;
  }
  return;
}


// ==== FUN_14007a680 @ 14007a680  void * FUN_14007a680(void * param_1, longlong param_2, void * param_3)

void * FUN_14007a680(void *param_1,longlong param_2,void *param_3)

{
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  if (lVar1 != 0) {
    memmove_s(param_3,lVar1 << 3,param_1,lVar1 << 3);
  }
  return (void *)((longlong)param_3 + lVar1 * 8);
}


// ==== FUN_14007a700 @ 14007a700  undefined FUN_14007a700(longlong * param_1)

void FUN_14007a700(longlong *param_1)

{
  int *piVar1;
  longlong lVar2;
  undefined1 *puVar3;
  undefined1 local_68 [8];
  undefined4 local_60 [16];
  undefined8 local_20;
  undefined4 *local_18;
  undefined4 *local_10;
  
  local_20 = 0xfffffffffffffffe;
  if (*param_1 != 0) {
    FUN_14007a830(param_1);
  }
  if (*(int *)((longlong)param_1 + 0x34) == -2) {
    puVar3 = local_68;
    for (lVar2 = 1; lVar2 != 0; lVar2 = lVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    local_18 = FUN_1400783d0(local_60,1,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\coded_stream.cc"
                             ,0x4e);
    local_10 = local_18;
    lVar2 = FUN_140078030((longlong)local_18,"The total number of bytes read was ");
    piVar1 = (int *)FUN_140078100(lVar2,*(uint *)(param_1 + 3));
    FUN_140078580(local_68,piVar1);
    FUN_140078440((longlong)local_60);
  }
  return;
}


// ==== FUN_14007a7d0 @ 14007a7d0  undefined FUN_14007a7d0(undefined8 * param_1, char param_2)

void FUN_14007a7d0(undefined8 *param_1,char param_2)

{
  char cVar1;
  undefined1 local_18;
  
  if (param_2 != '\0') {
    cVar1 = (**(code **)(*(longlong *)*param_1 + 0x28))(*param_1);
    if (cVar1 != '\0') {
      local_18 = 1;
      goto LAB_14007a815;
    }
  }
  local_18 = 0;
LAB_14007a815:
  *(undefined1 *)((longlong)param_1 + 0x19) = local_18;
  return;
}


// ==== FUN_14007a830 @ 14007a830  undefined FUN_14007a830(undefined8 * param_1)

void FUN_14007a830(undefined8 *param_1)

{
  int iVar1;
  longlong lVar2;
  
  lVar2 = FUN_14007c650((longlong)param_1);
  iVar1 = (int)lVar2 + *(int *)((longlong)param_1 + 0x2c) + *(int *)((longlong)param_1 + 0x1c);
  if (0 < iVar1) {
    (**(code **)(*(longlong *)*param_1 + 0x10))(*param_1,iVar1);
    lVar2 = FUN_14007c650((longlong)param_1);
    *(int *)(param_1 + 3) =
         *(int *)(param_1 + 3) - ((int)lVar2 + *(int *)((longlong)param_1 + 0x2c));
    param_1[2] = param_1[1];
    *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
    *(undefined4 *)((longlong)param_1 + 0x1c) = 0;
  }
  return;
}


// ==== FUN_14007a8e0 @ 14007a8e0  int FUN_14007a8e0(longlong param_1, int param_2)

int FUN_14007a8e0(longlong param_1,int param_2)

{
  int *piVar1;
  int local_18;
  int local_14;
  
  local_14 = FUN_14007c670(param_1);
  local_18 = *(int *)(param_1 + 0x28);
  if ((param_2 < 0) || (0x7fffffff - local_14 < param_2)) {
    *(undefined4 *)(param_1 + 0x28) = 0x7fffffff;
  }
  else {
    *(int *)(param_1 + 0x28) = local_14 + param_2;
  }
  piVar1 = FUN_14007d140((int *)(param_1 + 0x28),&local_18);
  *(int *)(param_1 + 0x28) = *piVar1;
  FUN_14007c6a0(param_1);
  return local_18;
}


// ==== FUN_14007a980 @ 14007a980  undefined FUN_14007a980(longlong param_1, undefined4 param_2)

void FUN_14007a980(longlong param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x28) = param_2;
  FUN_14007c6a0(param_1);
  *(undefined1 *)(param_1 + 0x24) = 0;
  return;
}


// ==== FUN_14007a9c0 @ 14007a9c0  int FUN_14007a9c0(longlong param_1)

int FUN_14007a9c0(longlong param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x28) == 0x7fffffff) {
    iVar1 = -1;
  }
  else {
    iVar1 = FUN_14007c670(param_1);
    iVar1 = *(int *)(param_1 + 0x28) - iVar1;
  }
  return iVar1;
}


// ==== FUN_14007aa10 @ 14007aa10  undefined FUN_14007aa10(longlong param_1, int param_2, int param_3)

void FUN_14007aa10(longlong param_1,int param_2,int param_3)

{
  int *piVar1;
  int local_res10 [2];
  int local_res18;
  int local_18 [6];
  
  local_res10[0] = param_2;
  local_res18 = param_3;
  local_18[0] = FUN_14007c670(param_1);
  piVar1 = FUN_14007d190(local_18,local_res10);
  *(int *)(param_1 + 0x30) = *piVar1;
  if (local_res18 < 0) {
    *(undefined4 *)(param_1 + 0x34) = 0xffffffff;
  }
  else {
    *(int *)(param_1 + 0x34) = local_res18;
  }
  FUN_14007c6a0(param_1);
  return;
}


// ==== FUN_14007aa80 @ 14007aa80  int FUN_14007aa80(longlong param_1)

int FUN_14007aa80(longlong param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x30) == 0x7fffffff) {
    iVar1 = -1;
  }
  else {
    iVar1 = FUN_14007c670(param_1);
    iVar1 = *(int *)(param_1 + 0x30) - iVar1;
  }
  return iVar1;
}


// ==== FUN_14007aad0 @ 14007aad0  undefined FUN_14007aad0(longlong param_1)

void FUN_14007aad0(longlong param_1)

{
  int *piVar1;
  longlong lVar2;
  undefined1 *puVar3;
  undefined1 local_68 [8];
  undefined4 local_60 [16];
  undefined8 local_20;
  undefined4 *local_18;
  undefined4 *local_10;
  
  local_20 = 0xfffffffffffffffe;
  puVar3 = local_68;
  for (lVar2 = 1; lVar2 != 0; lVar2 = lVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  local_18 = FUN_1400783d0(local_60,2,
                           "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\coded_stream.cc"
                           ,0xb4);
  local_10 = local_18;
  lVar2 = FUN_140078030((longlong)local_18,
                        "A protocol message was rejected because it was too big (more than ");
  lVar2 = FUN_140078100(lVar2,*(uint *)(param_1 + 0x30));
  piVar1 = (int *)FUN_140078030(lVar2,
                                " bytes).  To increase the limit (or to disable these warnings), see CodedInputStream::SetTotalBytesLimit() in google/protobuf/io/coded_stream.h."
                               );
  FUN_140078580(local_68,piVar1);
  FUN_140078440((longlong)local_60);
  return;
}


// ==== FUN_14007ab80 @ 14007ab80  undefined8 FUN_14007ab80(undefined8 * param_1, int param_2)

ulonglong FUN_14007ab80(undefined8 *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  ulonglong in_RAX;
  longlong lVar3;
  undefined8 uVar4;
  ulonglong uVar5;
  int *piVar6;
  
  if (param_2 < 0) {
    uVar5 = in_RAX & 0xffffffffffffff00;
  }
  else {
    lVar3 = FUN_14007c650((longlong)param_1);
    iVar2 = (int)lVar3;
    if (iVar2 < param_2) {
      if (*(int *)((longlong)param_1 + 0x2c) < 1) {
        uVar1 = param_2 - iVar2;
        param_1[1] = 0;
        param_1[2] = param_1[1];
        piVar6 = FUN_14007d140((int *)(param_1 + 5),(int *)(param_1 + 6));
        iVar2 = *piVar6 - *(int *)(param_1 + 3);
        uVar5 = (ulonglong)uVar1;
        if (iVar2 < (int)uVar1) {
          if (0 < iVar2) {
            *(int *)(param_1 + 3) = *piVar6;
            uVar5 = (**(code **)(*(longlong *)*param_1 + 0x18))(*param_1,iVar2);
          }
          uVar5 = uVar5 & 0xffffffffffffff00;
        }
        else {
          *(uint *)(param_1 + 3) = *(int *)(param_1 + 3) + uVar1;
          uVar5 = (**(code **)(*(longlong *)*param_1 + 0x18))(*param_1,uVar1);
        }
      }
      else {
        uVar5 = FUN_14007c740((longlong)param_1,iVar2);
        uVar5 = uVar5 & 0xffffffffffffff00;
      }
    }
    else {
      uVar4 = FUN_14007c740((longlong)param_1,param_2);
      uVar5 = CONCAT71((int7)((ulonglong)uVar4 >> 8),1);
    }
  }
  return uVar5;
}


// ==== FUN_14007acc0 @ 14007acc0  undefined8 FUN_14007acc0(undefined8 * param_1, undefined8 * param_2, undefined4 * param_3)

undefined8 FUN_14007acc0(undefined8 *param_1,undefined8 *param_2,undefined4 *param_3)

{
  longlong lVar1;
  ulonglong uVar2;
  
  lVar1 = FUN_14007c650((longlong)param_1);
  if (((int)lVar1 == 0) && (uVar2 = FUN_14007b7e0(param_1), (uVar2 & 0xff) == 0)) {
    return 0;
  }
  *param_2 = param_1[1];
  lVar1 = FUN_14007c650((longlong)param_1);
  *param_3 = (int)lVar1;
  return CONCAT71((int7)((ulonglong)param_3 >> 8),1);
}


// ==== FUN_14007ad30 @ 14007ad30  undefined8 FUN_14007ad30(undefined8 * param_1, void * param_2, int param_3)

undefined8 FUN_14007ad30(undefined8 *param_1,void *param_2,int param_3)

{
  int iVar1;
  longlong lVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  void *local_res10;
  int local_res18;
  
  local_res10 = param_2;
  local_res18 = param_3;
  do {
    lVar2 = FUN_14007c650((longlong)param_1);
    iVar1 = (int)lVar2;
    if (local_res18 <= iVar1) {
      memcpy(local_res10,(void *)param_1[1],(longlong)local_res18);
      uVar4 = FUN_14007c740((longlong)param_1,local_res18);
      return CONCAT71((int7)((ulonglong)uVar4 >> 8),1);
    }
    memcpy(local_res10,(void *)param_1[1],(longlong)iVar1);
    local_res10 = (void *)((longlong)local_res10 + (longlong)iVar1);
    local_res18 = local_res18 - iVar1;
    FUN_14007c740((longlong)param_1,iVar1);
    uVar3 = FUN_14007b7e0(param_1);
  } while ((uVar3 & 0xff) != 0);
  return 0;
}


// ==== FUN_14007adf0 @ 14007adf0  ulonglong FUN_14007adf0(undefined8 * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2, int param_3)

ulonglong FUN_14007adf0(undefined8 *param_1,
                       basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *param_2,int param_3)

{
  ulonglong in_RAX;
  ulonglong uVar1;
  
  if (param_3 < 0) {
    uVar1 = in_RAX & 0xffffffffffffff00;
  }
  else {
    uVar1 = FUN_14007c770(param_1,param_2,param_3);
  }
  return uVar1;
}


// ==== FUN_14007ae30 @ 14007ae30  undefined8 FUN_14007ae30(undefined8 * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2, int param_3)

undefined8
FUN_14007ae30(undefined8 *param_1,
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2,
             int param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  longlong lVar5;
  ulonglong uVar6;
  undefined8 uVar7;
  int local_res18;
  
  bVar1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::empty
                    (param_2);
  if (!bVar1) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::clear
              (param_2);
  }
  piVar4 = FUN_14007d140((int *)(param_1 + 5),(int *)(param_1 + 6));
  iVar3 = *piVar4;
  local_res18 = param_3;
  if (iVar3 != 0x7fffffff) {
    iVar2 = FUN_14007c670((longlong)param_1);
    iVar3 = iVar3 - iVar2;
    if (((0 < iVar3) && (0 < param_3)) && (param_3 <= iVar3)) {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::reserve
                (param_2,(longlong)param_3);
    }
  }
  do {
    lVar5 = FUN_14007c650((longlong)param_1);
    iVar3 = (int)lVar5;
    if (local_res18 <= iVar3) {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
                (param_2,(char *)param_1[1],(longlong)local_res18);
      uVar7 = FUN_14007c740((longlong)param_1,local_res18);
      return CONCAT71((int7)((ulonglong)uVar7 >> 8),1);
    }
    if (iVar3 != 0) {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
                (param_2,(char *)param_1[1],(longlong)iVar3);
    }
    local_res18 = local_res18 - iVar3;
    FUN_14007c740((longlong)param_1,iVar3);
    uVar6 = FUN_14007b7e0(param_1);
  } while ((uVar6 & 0xff) != 0);
  return 0;
}


// ==== FUN_14007af70 @ 14007af70  undefined8 FUN_14007af70(undefined8 * param_1, undefined4 * param_2)

undefined8 FUN_14007af70(undefined8 *param_1,undefined4 *param_2)

{
  longlong lVar1;
  ulonglong uVar2;
  undefined4 *puVar3;
  undefined4 *local_18;
  undefined4 local_10 [4];
  
  lVar1 = FUN_14007c650((longlong)param_1);
  if ((uint)lVar1 < 4) {
    uVar2 = FUN_14007ad30(param_1,local_10,4);
    if ((uVar2 & 0xff) == 0) {
      return 0;
    }
    local_18 = local_10;
  }
  else {
    local_18 = (undefined4 *)param_1[1];
    FUN_14007c740((longlong)param_1,4);
  }
  puVar3 = FUN_14007c810(local_18,param_2);
  return CONCAT71((int7)((ulonglong)puVar3 >> 8),1);
}


// ==== FUN_14007b000 @ 14007b000  undefined FUN_14007b000(undefined8 * param_1, undefined8 * param_2)

void FUN_14007b000(undefined8 *param_1,undefined8 *param_2)

{
  longlong lVar1;
  ulonglong uVar2;
  undefined1 auStack_48 [32];
  undefined8 *local_28;
  undefined8 local_18;
  ulonglong local_10;
  
  local_10 = DAT_140103510 ^ (ulonglong)auStack_48;
  lVar1 = FUN_14007c650((longlong)param_1);
  if ((uint)lVar1 < 8) {
    uVar2 = FUN_14007ad30(param_1,&local_18,8);
    if ((uVar2 & 0xff) == 0) goto LAB_14007b089;
    local_28 = &local_18;
  }
  else {
    local_28 = (undefined8 *)param_1[1];
    FUN_14007c740((longlong)param_1,8);
  }
  FUN_14007c860(local_28,param_2);
LAB_14007b089:
  __security_check_cookie(local_10 ^ (ulonglong)auStack_48);
  return;
}


// ==== FUN_14007b0b0 @ 14007b0b0  undefined8 FUN_14007b0b0(undefined8 * param_1, undefined4 * param_2)

undefined8 FUN_14007b0b0(undefined8 *param_1,undefined4 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  undefined4 local_18 [6];
  
  uVar1 = FUN_14007b420(param_1,(ulonglong *)local_18);
  if ((uVar1 & 0xff) == 0) {
    uVar2 = 0;
  }
  else {
    *param_2 = local_18[0];
    uVar2 = CONCAT71((uint7)(uint3)((uint)local_18[0] >> 8),1);
  }
  return uVar2;
}


// ==== FUN_14007b0f0 @ 14007b0f0  undefined8 FUN_14007b0f0(undefined8 * param_1, uint * param_2)

undefined8 FUN_14007b0f0(undefined8 *param_1,uint *param_2)

{
  longlong lVar1;
  byte *pbVar2;
  undefined8 uVar3;
  
  lVar1 = FUN_14007c650((longlong)param_1);
  if (((int)lVar1 < 10) &&
     (((ulonglong)param_1[2] <= (ulonglong)param_1[1] || ((*(byte *)(param_1[2] + -1) & 0x80) != 0))
     )) {
    uVar3 = FUN_14007b0b0(param_1,param_2);
  }
  else {
    pbVar2 = FUN_14007c910((byte *)param_1[1],param_2);
    if (pbVar2 == (byte *)0x0) {
      uVar3 = 0;
    }
    else {
      param_1[1] = pbVar2;
      uVar3 = CONCAT71((int7)((ulonglong)pbVar2 >> 8),1);
    }
  }
  return uVar3;
}


// ==== FUN_14007b190 @ 14007b190  ulonglong FUN_14007b190(undefined8 * param_1)

ulonglong FUN_14007b190(undefined8 *param_1)

{
  ulonglong uVar1;
  ulonglong local_18 [3];
  
  if ((param_1[1] == param_1[2]) && (uVar1 = FUN_14007b7e0(param_1), (uVar1 & 0xff) == 0)) {
    if (*(int *)(param_1 + 3) - *(int *)((longlong)param_1 + 0x2c) < *(int *)(param_1 + 6)) {
      *(undefined1 *)((longlong)param_1 + 0x24) = 1;
    }
    else {
      *(bool *)((longlong)param_1 + 0x24) = *(int *)(param_1 + 5) == *(int *)(param_1 + 6);
    }
    local_18[0] = 0;
  }
  else {
    local_18[0] = 0;
    uVar1 = FUN_14007caf0(param_1,local_18);
    if ((uVar1 & 0xff) == 0) {
      local_18[0] = 0;
    }
    else {
      local_18[0] = local_18[0] & 0xffffffff;
    }
  }
  return local_18[0];
}


// ==== FUN_14007b260 @ 14007b260  ulonglong FUN_14007b260(undefined8 * param_1)

ulonglong FUN_14007b260(undefined8 *param_1)

{
  int iVar1;
  longlong lVar2;
  byte *pbVar3;
  ulonglong uVar4;
  uint local_14 [5];
  
  lVar2 = FUN_14007c650((longlong)param_1);
  iVar1 = (int)lVar2;
  if ((iVar1 < 10) && ((iVar1 < 1 || ((*(byte *)(param_1[2] + -1) & 0x80) != 0)))) {
    if ((iVar1 == 0) &&
       (((0 < *(int *)((longlong)param_1 + 0x2c) || (*(int *)(param_1 + 3) == *(int *)(param_1 + 5))
         ) && (*(int *)(param_1 + 3) - *(int *)((longlong)param_1 + 0x2c) < *(int *)(param_1 + 6))))
       ) {
      *(undefined1 *)((longlong)param_1 + 0x24) = 1;
      uVar4 = 0;
    }
    else {
      uVar4 = FUN_14007b190(param_1);
    }
  }
  else {
    pbVar3 = FUN_14007c910((byte *)param_1[1],local_14);
    if (pbVar3 == (byte *)0x0) {
      uVar4 = 0;
    }
    else {
      param_1[1] = pbVar3;
      uVar4 = (ulonglong)local_14[0];
    }
  }
  return uVar4;
}


// ==== FUN_14007b340 @ 14007b340  ulonglong FUN_14007b340(undefined8 * param_1, ulonglong * param_2)

ulonglong FUN_14007b340(undefined8 *param_1,ulonglong *param_2)

{
  byte bVar1;
  ulonglong in_RAX;
  ulonglong uVar2;
  int local_18;
  ulonglong local_10;
  
  local_10 = 0;
  local_18 = 0;
  do {
    if (local_18 == 10) {
      return in_RAX & 0xffffffffffffff00;
    }
    while (param_1[1] == param_1[2]) {
      uVar2 = FUN_14007b7e0(param_1);
      if ((uVar2 & 0xff) == 0) {
        return 0;
      }
    }
    bVar1 = *(byte *)param_1[1];
    local_10 = local_10 | (ulonglong)(bVar1 & 0x7f) << ((char)local_18 * '\a' & 0x3fU);
    FUN_14007c740((longlong)param_1,1);
    local_18 = local_18 + 1;
    in_RAX = 0;
  } while ((bVar1 & 0x80) != 0);
  *param_2 = local_10;
  return CONCAT71((int7)(local_10 >> 8),1);
}


// ==== FUN_14007b420 @ 14007b420  ulonglong FUN_14007b420(undefined8 * param_1, ulonglong * param_2)

ulonglong FUN_14007b420(undefined8 *param_1,ulonglong *param_2)

{
  byte bVar1;
  byte *pbVar2;
  longlong lVar3;
  ulonglong uVar4;
  uint local_28;
  byte *local_20;
  uint local_14;
  uint local_10;
  
  lVar3 = FUN_14007c650((longlong)param_1);
  if (((int)lVar3 < 10) &&
     (((ulonglong)param_1[2] <= (ulonglong)param_1[1] || ((*(byte *)(param_1[2] + -1) & 0x80) != 0))
     )) {
    uVar4 = FUN_14007b340(param_1,param_2);
  }
  else {
    pbVar2 = (byte *)param_1[1];
    local_28 = 0;
    local_14 = 0;
    local_10 = (uint)*pbVar2;
    local_20 = pbVar2 + 1;
    if ((*pbVar2 & 0x80) != 0) {
      bVar1 = *local_20;
      local_20 = pbVar2 + 2;
      local_10 = (local_10 - 0x80) + (uint)bVar1 * 0x80;
      if ((bVar1 & 0x80) != 0) {
        bVar1 = *local_20;
        local_20 = pbVar2 + 3;
        local_10 = (local_10 - 0x4000) + (uint)bVar1 * 0x4000;
        if ((bVar1 & 0x80) != 0) {
          bVar1 = *local_20;
          local_20 = pbVar2 + 4;
          local_10 = (local_10 - 0x200000) + (uint)bVar1 * 0x200000;
          if ((bVar1 & 0x80) != 0) {
            local_10 = local_10 + 0xf0000000;
            bVar1 = *local_20;
            local_28 = (uint)bVar1;
            local_20 = pbVar2 + 5;
            if ((bVar1 & 0x80) != 0) {
              bVar1 = *local_20;
              local_20 = pbVar2 + 6;
              local_28 = (local_28 - 0x80) + (uint)bVar1 * 0x80;
              if ((bVar1 & 0x80) != 0) {
                bVar1 = *local_20;
                local_20 = pbVar2 + 7;
                local_28 = (local_28 - 0x4000) + (uint)bVar1 * 0x4000;
                if ((bVar1 & 0x80) != 0) {
                  bVar1 = *local_20;
                  local_20 = pbVar2 + 8;
                  local_28 = (local_28 - 0x200000) + (uint)bVar1 * 0x200000;
                  if ((bVar1 & 0x80) != 0) {
                    local_28 = local_28 + 0xf0000000;
                    bVar1 = *local_20;
                    local_14 = (uint)bVar1;
                    local_20 = pbVar2 + 9;
                    if ((bVar1 & 0x80) != 0) {
                      bVar1 = *local_20;
                      local_20 = pbVar2 + 10;
                      local_14 = (local_14 - 0x80) + (uint)bVar1 * 0x80;
                      if ((bVar1 & 0x80) != 0) {
                        return 0;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    FUN_14007c740((longlong)param_1,(int)local_20 - (int)param_1[1]);
    *param_2 = (ulonglong)local_10 | (ulonglong)local_28 << 0x1c | (ulonglong)local_14 << 0x38;
    uVar4 = CONCAT71((int7)((ulonglong)param_2 >> 8),1);
  }
  return uVar4;
}


// ==== FUN_14007b7e0 @ 14007b7e0  undefined8 FUN_14007b7e0(undefined8 * param_1)

/* WARNING: Removing unreachable block (ram,0x00014007b80e) */
/* WARNING: Removing unreachable block (ram,0x00014007b821) */
/* WARNING: Removing unreachable block (ram,0x00014007b82d) */
/* WARNING: Removing unreachable block (ram,0x00014007b82f) */
/* WARNING: Removing unreachable block (ram,0x00014007b81f) */
/* WARNING: Removing unreachable block (ram,0x00014007b896) */
/* WARNING: Removing unreachable block (ram,0x00014007b8a4) */
/* WARNING: Removing unreachable block (ram,0x00014007b8b6) */

ulonglong FUN_14007b7e0(undefined8 *param_1)

{
  char cVar1;
  ulonglong uVar2;
  int *piVar3;
  undefined8 uVar4;
  longlong lVar5;
  undefined1 *puVar6;
  undefined8 local_138;
  int local_130;
  int local_12c;
  undefined1 local_e0 [8];
  undefined4 local_d8 [16];
  undefined1 local_98 [8];
  undefined4 local_90 [16];
  uint local_50;
  undefined8 local_48;
  undefined4 *local_30;
  undefined4 *local_28;
  undefined4 *local_20;
  undefined4 *local_18;
  
  local_48 = 0xfffffffffffffffe;
  local_50 = 0;
  if (((*(int *)((longlong)param_1 + 0x2c) < 1) && (*(int *)((longlong)param_1 + 0x1c) < 1)) &&
     (*(int *)(param_1 + 3) != *(int *)(param_1 + 5))) {
    if ((-1 < *(int *)((longlong)param_1 + 0x34)) &&
       (*(int *)((longlong)param_1 + 0x34) <= *(int *)(param_1 + 3))) {
      puVar6 = local_e0;
      for (lVar5 = 1; lVar5 != 0; lVar5 = lVar5 + -1) {
        *puVar6 = 0;
        puVar6 = puVar6 + 1;
      }
      local_30 = FUN_1400783d0(local_d8,1,
                               "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\coded_stream.cc"
                               ,0x219);
      local_28 = local_30;
      lVar5 = FUN_140078030((longlong)local_30,
                            "Reading dangerously large protocol message.  If the message turns out to be larger than "
                           );
      lVar5 = FUN_140078100(lVar5,*(uint *)(param_1 + 6));
      piVar3 = (int *)FUN_140078030(lVar5,
                                    " bytes, parsing will be halted for security reasons.  To increase the limit (or to disable these warnings), see CodedInputStream::SetTotalBytesLimit() in google/protobuf/io/coded_stream.h."
                                   );
      FUN_140078580(local_e0,piVar3);
      FUN_140078440((longlong)local_d8);
      *(undefined4 *)((longlong)param_1 + 0x34) = 0xfffffffe;
    }
    cVar1 = FUN_14007cb70((longlong *)*param_1,&local_138,&local_130);
    if (cVar1 == '\0') {
      param_1[1] = 0;
      param_1[2] = 0;
      uVar2 = (ulonglong)param_1 & 0xffffffffffffff00;
    }
    else {
      param_1[1] = local_138;
      param_1[2] = (longlong)local_130 + param_1[1];
      if (local_130 < 0) {
        puVar6 = local_98;
        for (lVar5 = 1; lVar5 != 0; lVar5 = lVar5 + -1) {
          *puVar6 = 0;
          puVar6 = puVar6 + 1;
        }
        local_20 = FUN_1400783d0(local_90,3,
                                 "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\coded_stream.cc"
                                 ,0x22a);
        local_50 = local_50 | 2;
        local_18 = local_20;
        piVar3 = (int *)FUN_140078030((longlong)local_20,"CHECK failed: (buffer_size) >= (0): ");
        FUN_140078580(local_98,piVar3);
      }
      if ((local_50 & 2) != 0) {
        local_50 = local_50 & 0xfffffffd;
        FUN_140078440((longlong)local_90);
      }
      if (0x7fffffff - local_130 < *(int *)(param_1 + 3)) {
        *(int *)((longlong)param_1 + 0x1c) = *(int *)(param_1 + 3) - (0x7fffffff - local_130);
        param_1[2] = param_1[2] - (longlong)*(int *)((longlong)param_1 + 0x1c);
        *(undefined4 *)(param_1 + 3) = 0x7fffffff;
      }
      else {
        *(int *)(param_1 + 3) = *(int *)(param_1 + 3) + local_130;
      }
      uVar4 = FUN_14007c6a0((longlong)param_1);
      uVar2 = CONCAT71((int7)((ulonglong)uVar4 >> 8),1);
    }
  }
  else {
    local_12c = *(int *)(param_1 + 3) - *(int *)((longlong)param_1 + 0x2c);
    uVar2 = (ulonglong)*(uint *)(param_1 + 6);
    if (((int)*(uint *)(param_1 + 6) <= local_12c) &&
       (uVar2 = (ulonglong)*(uint *)(param_1 + 5), *(uint *)(param_1 + 6) != *(uint *)(param_1 + 5))
       ) {
      uVar2 = FUN_14007aad0((longlong)param_1);
    }
    uVar2 = uVar2 & 0xffffffffffffff00;
  }
  return uVar2;
}


// ==== FUN_14007bbf0 @ 14007bbf0  undefined8 * FUN_14007bbf0(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_14007bbf0(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = param_2;
  param_1[1] = 0;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14) = 0;
  *(undefined1 *)(param_1 + 3) = 0;
  *(undefined1 *)((longlong)param_1 + 0x19) = 0;
  FUN_14007c350(param_1);
  *(undefined1 *)(param_1 + 3) = 0;
  return param_1;
}


// ==== FUN_14007bc70 @ 14007bc70  undefined FUN_14007bc70(undefined8 * param_1)

void FUN_14007bc70(undefined8 *param_1)

{
  if (0 < *(int *)(param_1 + 2)) {
    (**(code **)(*(longlong *)*param_1 + 0x10))(*param_1,*(undefined4 *)(param_1 + 2));
  }
  return;
}


// ==== FUN_14007bcb0 @ 14007bcb0  undefined8 FUN_14007bcb0(undefined8 * param_1, int param_2)

ulonglong FUN_14007bcb0(undefined8 *param_1,int param_2)

{
  bool bVar1;
  ulonglong in_RAX;
  ulonglong uVar2;
  undefined8 uVar3;
  int local_res10;
  
  local_res10 = param_2;
  if (param_2 < 0) {
    uVar2 = in_RAX & 0xffffffffffffff00;
  }
  else {
    do {
      if (local_res10 <= *(int *)(param_1 + 2)) {
        uVar3 = FUN_1400778c0((longlong)param_1,local_res10);
        return CONCAT71((int7)((ulonglong)uVar3 >> 8),1);
      }
      local_res10 = local_res10 - *(int *)(param_1 + 2);
      bVar1 = FUN_14007c350(param_1);
    } while (bVar1);
    uVar2 = 0;
  }
  return uVar2;
}


// ==== FUN_14007bd20 @ 14007bd20  undefined8 FUN_14007bd20(undefined8 * param_1, undefined8 * param_2, undefined4 * param_3)

undefined8 FUN_14007bd20(undefined8 *param_1,undefined8 *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  bool bVar2;
  
  if ((*(int *)(param_1 + 2) == 0) && (bVar2 = FUN_14007c350(param_1), !bVar2)) {
    return 0;
  }
  *param_2 = param_1[1];
  uVar1 = *(undefined4 *)(param_1 + 2);
  *param_3 = uVar1;
  return CONCAT71((uint7)(uint3)((uint)uVar1 >> 8),1);
}


// ==== FUN_14007bd80 @ 14007bd80  undefined FUN_14007bd80(undefined8 * param_1, void * param_2, int param_3)

void FUN_14007bd80(undefined8 *param_1,void *param_2,int param_3)

{
  bool bVar1;
  void *local_res10;
  int local_res18;
  
  local_res10 = param_2;
  local_res18 = param_3;
  do {
    if (local_res18 <= *(int *)(param_1 + 2)) {
      memcpy((void *)param_1[1],local_res10,(longlong)local_res18);
      FUN_1400778c0((longlong)param_1,local_res18);
      return;
    }
    memcpy((void *)param_1[1],local_res10,(longlong)*(int *)(param_1 + 2));
    local_res18 = local_res18 - *(int *)(param_1 + 2);
    local_res10 = (void *)((longlong)local_res10 + (longlong)*(int *)(param_1 + 2));
    bVar1 = FUN_14007c350(param_1);
  } while (bVar1);
  return;
}


// ==== FUN_14007be30 @ 14007be30  longlong FUN_14007be30(void * param_1, int param_2, void * param_3)

longlong FUN_14007be30(void *param_1,int param_2,void *param_3)

{
  memcpy(param_3,param_1,(longlong)param_2);
  return (longlong)param_3 + (longlong)param_2;
}


// ==== FUN_14007be70 @ 14007be70  undefined FUN_14007be70(undefined8 * param_1, void * param_2, int param_3)

void FUN_14007be70(undefined8 *param_1,void *param_2,int param_3)

{
  char cVar1;
  
  if (param_3 < *(int *)(param_1 + 2)) {
    FUN_14007bd80(param_1,param_2,param_3);
  }
  else {
    if (0 < *(int *)(param_1 + 2)) {
      (**(code **)(*(longlong *)*param_1 + 0x10))(*param_1,*(undefined4 *)(param_1 + 2));
      *(int *)((longlong)param_1 + 0x14) =
           *(int *)((longlong)param_1 + 0x14) - *(int *)(param_1 + 2);
      param_1[1] = 0;
      *(undefined4 *)(param_1 + 2) = 0;
    }
    *(int *)((longlong)param_1 + 0x14) = *(int *)((longlong)param_1 + 0x14) + param_3;
    cVar1 = (**(code **)(*(longlong *)*param_1 + 0x20))(*param_1,param_2,param_3);
    *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | cVar1 == '\0';
  }
  return;
}


// ==== FUN_14007bf80 @ 14007bf80  undefined FUN_14007bf80(undefined8 * param_1, undefined4 param_2)

void FUN_14007bf80(undefined8 *param_1,undefined4 param_2)

{
  bool bVar1;
  undefined1 local_18 [4];
  uint local_14;
  undefined1 *local_10;
  
  bVar1 = 3 < *(uint *)(param_1 + 2);
  local_14 = (uint)bVar1;
  if (bVar1) {
    local_10 = (undefined1 *)param_1[1];
  }
  else {
    local_10 = local_18;
  }
  FUN_14007cbc0(param_2,local_10);
  if (bVar1) {
    FUN_1400778c0((longlong)param_1,4);
  }
  else {
    FUN_14007bd80(param_1,local_18,4);
  }
  return;
}


// ==== FUN_14007c030 @ 14007c030  undefined FUN_14007c030(undefined8 * param_1, undefined8 param_2)

void FUN_14007c030(undefined8 *param_1,undefined8 param_2)

{
  undefined1 auStack_68 [32];
  char local_48;
  undefined1 *local_40;
  undefined1 local_30 [8];
  uint local_28;
  undefined1 *local_20;
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_68;
  local_48 = 7 < *(uint *)(param_1 + 2);
  local_28 = (uint)(byte)local_48;
  if ((bool)local_48) {
    local_20 = (undefined1 *)param_1[1];
  }
  else {
    local_20 = local_30;
  }
  local_40 = local_20;
  FUN_14007cc10(param_2,local_20);
  if (local_48 == '\0') {
    FUN_14007bd80(param_1,local_30,8);
  }
  else {
    FUN_1400778c0((longlong)param_1,8);
  }
  __security_check_cookie(local_18 ^ (ulonglong)auStack_68);
  return;
}


// ==== FUN_14007c100 @ 14007c100  undefined FUN_14007c100(undefined8 * param_1, uint param_2)

void FUN_14007c100(undefined8 *param_1,uint param_2)

{
  uint local_res10;
  undefined1 auStack_68 [32];
  int local_48;
  byte *local_40;
  byte *local_38;
  int local_30;
  byte local_20 [8];
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_68;
  if (*(int *)(param_1 + 2) < 5) {
    local_30 = 0;
    for (local_res10 = param_2; 0x7f < local_res10; local_res10 = local_res10 >> 7) {
      local_20[local_30] = (byte)local_res10 & 0x7f | 0x80;
      local_30 = local_30 + 1;
    }
    local_20[local_30] = (byte)local_res10 & 0x7f;
    local_30 = local_30 + 1;
    FUN_14007bd80(param_1,local_20,local_30);
  }
  else {
    local_38 = (byte *)param_1[1];
    local_40 = FUN_14007ccb0(param_2,local_38);
    local_48 = (int)local_40 - (int)local_38;
    FUN_1400778c0((longlong)param_1,local_48);
  }
  __security_check_cookie(local_18 ^ (ulonglong)auStack_68);
  return;
}


// ==== FUN_14007c1f0 @ 14007c1f0  undefined FUN_14007c1f0(uint param_1, byte * param_2)

void FUN_14007c1f0(uint param_1,byte *param_2)

{
  FUN_14007ccb0(param_1,param_2);
  return;
}


// ==== FUN_14007c220 @ 14007c220  undefined FUN_14007c220(undefined8 * param_1, ulonglong param_2)

void FUN_14007c220(undefined8 *param_1,ulonglong param_2)

{
  ulonglong local_res10;
  undefined1 auStack_68 [32];
  int local_48;
  byte *local_40;
  byte *local_38;
  int local_30;
  byte local_20 [16];
  ulonglong local_10;
  
  local_10 = DAT_140103510 ^ (ulonglong)auStack_68;
  if (*(int *)(param_1 + 2) < 10) {
    local_30 = 0;
    for (local_res10 = param_2; 0x7f < local_res10; local_res10 = local_res10 >> 7) {
      local_20[local_30] = (byte)local_res10 & 0x7f | 0x80;
      local_30 = local_30 + 1;
    }
    local_20[local_30] = (byte)local_res10 & 0x7f;
    local_30 = local_30 + 1;
    FUN_14007bd80(param_1,local_20,local_30);
  }
  else {
    local_38 = (byte *)param_1[1];
    local_40 = FUN_14007cde0(param_2,local_38);
    local_48 = (int)local_40 - (int)local_38;
    FUN_1400778c0((longlong)param_1,local_48);
  }
  __security_check_cookie(local_10 ^ (ulonglong)auStack_68);
  return;
}


// ==== FUN_14007c320 @ 14007c320  undefined FUN_14007c320(ulonglong param_1, byte * param_2)

void FUN_14007c320(ulonglong param_1,byte *param_2)

{
  FUN_14007cde0(param_1,param_2);
  return;
}


// ==== FUN_14007c350 @ 14007c350  bool FUN_14007c350(undefined8 * param_1)

bool FUN_14007c350(undefined8 *param_1)

{
  char cVar1;
  undefined8 local_18 [3];
  
  cVar1 = (**(code **)(*(longlong *)*param_1 + 8))(*param_1,local_18,param_1 + 2);
  if (cVar1 == '\0') {
    param_1[1] = 0;
    *(undefined4 *)(param_1 + 2) = 0;
    *(undefined1 *)(param_1 + 3) = 1;
  }
  else {
    param_1[1] = local_18[0];
    *(int *)((longlong)param_1 + 0x14) = *(int *)((longlong)param_1 + 0x14) + *(int *)(param_1 + 2);
  }
  return cVar1 != '\0';
}


// ==== FUN_14007c3e0 @ 14007c3e0  undefined8 FUN_14007c3e0(uint param_1)

undefined8 FUN_14007c3e0(uint param_1)

{
  undefined8 uVar1;
  
  if (param_1 < 0x80) {
    uVar1 = 1;
  }
  else if (param_1 < 0x4000) {
    uVar1 = 2;
  }
  else if (param_1 < 0x200000) {
    uVar1 = 3;
  }
  else if (param_1 < 0x10000000) {
    uVar1 = 4;
  }
  else {
    uVar1 = 5;
  }
  return uVar1;
}


// ==== FUN_14007c440 @ 14007c440  undefined8 FUN_14007c440(ulonglong param_1)

undefined8 FUN_14007c440(ulonglong param_1)

{
  undefined8 uVar1;
  
  if (param_1 < 0x800000000) {
    if (param_1 < 0x80) {
      uVar1 = 1;
    }
    else if (param_1 < 0x4000) {
      uVar1 = 2;
    }
    else if (param_1 < 0x200000) {
      uVar1 = 3;
    }
    else if (param_1 < 0x10000000) {
      uVar1 = 4;
    }
    else {
      uVar1 = 5;
    }
  }
  else if (param_1 < 0x40000000000) {
    uVar1 = 6;
  }
  else if (param_1 < 0x2000000000000) {
    uVar1 = 7;
  }
  else if (param_1 < 0x100000000000000) {
    uVar1 = 8;
  }
  else if (param_1 < 0x8000000000000000) {
    uVar1 = 9;
  }
  else {
    uVar1 = 10;
  }
  return uVar1;
}


// ==== FUN_14007c530 @ 14007c530  undefined FUN_14007c530(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_1, byte * param_2)

/* WARNING: Removing unreachable block (ram,0x00014007c55d) */
/* WARNING: Removing unreachable block (ram,0x00014007c57a) */
/* WARNING: Removing unreachable block (ram,0x00014007c586) */
/* WARNING: Removing unreachable block (ram,0x00014007c588) */
/* WARNING: Removing unreachable block (ram,0x00014007c578) */
/* WARNING: Removing unreachable block (ram,0x00014007c5e3) */
/* WARNING: Removing unreachable block (ram,0x00014007c5ee) */
/* WARNING: Removing unreachable block (ram,0x00014007c5fd) */

void FUN_14007c530(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                   *param_1,byte *param_2)

{
  __uint64 _Var1;
  byte *pbVar2;
  
  _Var1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (param_1);
  pbVar2 = FUN_14007d0b0((uint)_Var1,param_2);
  FUN_14007d100(param_1,pbVar2);
  return;
}


// ==== FUN_14007c650 @ 14007c650  longlong FUN_14007c650(longlong param_1)

longlong FUN_14007c650(longlong param_1)

{
  return *(longlong *)(param_1 + 0x10) - *(longlong *)(param_1 + 8);
}


// ==== FUN_14007c670 @ 14007c670  int FUN_14007c670(longlong param_1)

int FUN_14007c670(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = FUN_14007c650(param_1);
  return *(int *)(param_1 + 0x18) - ((int)lVar1 + *(int *)(param_1 + 0x2c));
}


// ==== FUN_14007c6a0 @ 14007c6a0  undefined FUN_14007c6a0(longlong param_1)

void FUN_14007c6a0(longlong param_1)

{
  int *piVar1;
  
  *(longlong *)(param_1 + 0x10) = (longlong)*(int *)(param_1 + 0x2c) + *(longlong *)(param_1 + 0x10)
  ;
  piVar1 = FUN_14007d140((int *)(param_1 + 0x28),(int *)(param_1 + 0x30));
  if (*piVar1 < *(int *)(param_1 + 0x18)) {
    *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x18) - *piVar1;
    *(longlong *)(param_1 + 0x10) =
         *(longlong *)(param_1 + 0x10) - (longlong)*(int *)(param_1 + 0x2c);
  }
  else {
    *(undefined4 *)(param_1 + 0x2c) = 0;
  }
  return;
}


// ==== FUN_14007c740 @ 14007c740  undefined FUN_14007c740(longlong param_1, int param_2)

void FUN_14007c740(longlong param_1,int param_2)

{
  *(longlong *)(param_1 + 8) = (longlong)param_2 + *(longlong *)(param_1 + 8);
  return;
}


// ==== FUN_14007c770 @ 14007c770  undefined8 FUN_14007c770(undefined8 * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2, int param_3)

ulonglong FUN_14007c770(undefined8 *param_1,
                       basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *param_2,int param_3)

{
  ulonglong in_RAX;
  longlong lVar1;
  undefined8 uVar2;
  void *_Dst;
  ulonglong uVar3;
  
  if (param_3 < 0) {
    uVar3 = in_RAX & 0xffffffffffffff00;
  }
  else {
    lVar1 = FUN_14007c650((longlong)param_1);
    if ((int)lVar1 < param_3) {
      uVar3 = FUN_14007ae30(param_1,param_2,param_3);
    }
    else {
      uVar2 = FUN_140077900(param_2,(longlong)param_3);
      if (0 < param_3) {
        _Dst = (void *)FUN_140077930(param_2);
        memcpy(_Dst,(void *)param_1[1],(longlong)param_3);
        uVar2 = FUN_14007c740((longlong)param_1,param_3);
      }
      uVar3 = CONCAT71((int7)((ulonglong)uVar2 >> 8),1);
    }
  }
  return uVar3;
}


// ==== FUN_14007c810 @ 14007c810  undefined4 * FUN_14007c810(undefined4 * param_1, undefined4 * param_2)

undefined4 * FUN_14007c810(undefined4 *param_1,undefined4 *param_2)

{
  *param_2 = *param_1;
  return param_1 + 1;
}


// ==== FUN_14007c860 @ 14007c860  undefined8 * FUN_14007c860(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14007c860(undefined8 *param_1,undefined8 *param_2)

{
  *param_2 = *param_1;
  return param_1 + 1;
}


// ==== FUN_14007c910 @ 14007c910  byte * FUN_14007c910(byte * param_1, uint * param_2)

byte * FUN_14007c910(byte *param_1,uint *param_2)

{
  byte bVar1;
  byte *local_28;
  uint local_1c;
  int local_18;
  
  local_1c = (uint)*param_1;
  local_28 = param_1 + 1;
  if ((*param_1 & 0x80) != 0) {
    bVar1 = *local_28;
    local_28 = param_1 + 2;
    local_1c = (local_1c - 0x80) + (uint)bVar1 * 0x80;
    if ((bVar1 & 0x80) != 0) {
      bVar1 = *local_28;
      local_28 = param_1 + 3;
      local_1c = (local_1c - 0x4000) + (uint)bVar1 * 0x4000;
      if ((bVar1 & 0x80) != 0) {
        bVar1 = *local_28;
        local_28 = param_1 + 4;
        local_1c = (local_1c - 0x200000) + (uint)bVar1 * 0x200000;
        if ((bVar1 & 0x80) != 0) {
          bVar1 = *local_28;
          local_28 = param_1 + 5;
          local_1c = local_1c + 0xf0000000 + (uint)bVar1 * 0x10000000;
          if ((bVar1 & 0x80) != 0) {
            local_18 = 0;
            while( true ) {
              if (4 < local_18) {
                return (byte *)0x0;
              }
              bVar1 = *local_28;
              local_28 = local_28 + 1;
              if ((bVar1 & 0x80) == 0) break;
              local_18 = local_18 + 1;
            }
          }
        }
      }
    }
  }
  *param_2 = local_1c;
  return local_28;
}


// ==== FUN_14007caf0 @ 14007caf0  ulonglong FUN_14007caf0(undefined8 * param_1, ulonglong * param_2)

ulonglong FUN_14007caf0(undefined8 *param_1,ulonglong *param_2)

{
  undefined8 uVar1;
  ulonglong uVar2;
  
  if (((ulonglong)param_1[1] < (ulonglong)param_1[2]) && (*(byte *)param_1[1] < 0x80)) {
    *param_2 = (ulonglong)*(byte *)param_1[1];
    uVar1 = FUN_14007c740((longlong)param_1,1);
    uVar2 = CONCAT71((int7)((ulonglong)uVar1 >> 8),1);
  }
  else {
    uVar2 = FUN_14007b420(param_1,param_2);
  }
  return uVar2;
}


// ==== FUN_14007cb70 @ 14007cb70  char FUN_14007cb70(longlong * param_1, undefined8 param_2, int * param_3)

char FUN_14007cb70(longlong *param_1,undefined8 param_2,int *param_3)

{
  char cVar1;
  
  do {
    cVar1 = (**(code **)(*param_1 + 8))(param_1,param_2,param_3);
    if (cVar1 == '\0') {
      return '\0';
    }
  } while (*param_3 == 0);
  return cVar1;
}


// ==== FUN_14007cbc0 @ 14007cbc0  undefined1 * FUN_14007cbc0(undefined4 param_1, undefined1 * param_2)

undefined1 * FUN_14007cbc0(undefined4 param_1,undefined1 *param_2)

{
  undefined1 local_res8;
  
  local_res8 = (undefined1)param_1;
  *param_2 = local_res8;
  param_2[1] = (char)((uint)param_1 >> 8);
  param_2[2] = (char)((uint)param_1 >> 0x10);
  param_2[3] = (char)((uint)param_1 >> 0x18);
  return param_2 + 4;
}


// ==== FUN_14007cc10 @ 14007cc10  undefined1 * FUN_14007cc10(undefined8 param_1, undefined1 * param_2)

undefined1 * FUN_14007cc10(undefined8 param_1,undefined1 *param_2)

{
  undefined1 local_18;
  undefined1 local_14;
  
  local_14 = (undefined1)param_1;
  *param_2 = local_14;
  param_2[1] = (char)((ulonglong)param_1 >> 8);
  param_2[2] = (char)((ulonglong)param_1 >> 0x10);
  param_2[3] = (char)((ulonglong)param_1 >> 0x18);
  local_18 = (undefined1)((ulonglong)param_1 >> 0x20);
  param_2[4] = local_18;
  param_2[5] = (char)((ulonglong)param_1 >> 0x28);
  param_2[6] = (char)((ulonglong)param_1 >> 0x30);
  param_2[7] = (char)((ulonglong)param_1 >> 0x38);
  return param_2 + 8;
}


// ==== FUN_14007ccb0 @ 14007ccb0  byte * FUN_14007ccb0(uint param_1, byte * param_2)

byte * FUN_14007ccb0(uint param_1,byte *param_2)

{
  byte *pbVar1;
  
  *param_2 = (byte)param_1 | 0x80;
  if (param_1 < 0x80) {
    *param_2 = *param_2 & 0x7f;
    pbVar1 = param_2 + 1;
  }
  else {
    param_2[1] = (byte)(param_1 >> 7) | 0x80;
    if (param_1 < 0x4000) {
      param_2[1] = param_2[1] & 0x7f;
      pbVar1 = param_2 + 2;
    }
    else {
      param_2[2] = (byte)(param_1 >> 0xe) | 0x80;
      if (param_1 < 0x200000) {
        param_2[2] = param_2[2] & 0x7f;
        pbVar1 = param_2 + 3;
      }
      else {
        param_2[3] = (byte)(param_1 >> 0x15) | 0x80;
        if (param_1 < 0x10000000) {
          param_2[3] = param_2[3] & 0x7f;
          pbVar1 = param_2 + 4;
        }
        else {
          param_2[4] = (byte)(param_1 >> 0x1c);
          pbVar1 = param_2 + 5;
        }
      }
    }
  }
  return pbVar1;
}


// ==== FUN_14007cde0 @ 14007cde0  byte * FUN_14007cde0(ulonglong param_1, byte * param_2)

byte * FUN_14007cde0(ulonglong param_1,byte *param_2)

{
  byte bVar1;
  uint uVar2;
  uint local_res8;
  int local_74;
  
  local_res8 = (uint)param_1;
  uVar2 = (uint)(param_1 >> 0x1c);
  bVar1 = (byte)(param_1 >> 0x38);
  if (bVar1 == 0) {
    if (uVar2 != 0) {
      if (0x3fff < uVar2) {
        if (0x1fffff < uVar2) {
          local_74 = 8;
          goto LAB_14007cfaa;
        }
        local_74 = 7;
        goto LAB_14007cfc2;
      }
      if (0x7f < uVar2) {
        local_74 = 6;
        goto LAB_14007cfda;
      }
      local_74 = 5;
      goto LAB_14007cff2;
    }
    if (0x3fff < local_res8) {
      if (0x1fffff < local_res8) {
        local_74 = 4;
        goto LAB_14007d007;
      }
      local_74 = 3;
      goto LAB_14007d01f;
    }
    if (local_res8 < 0x80) {
      local_74 = 1;
      goto LAB_14007d04f;
    }
    local_74 = 2;
  }
  else {
    if (bVar1 < 0x80) {
      local_74 = 9;
    }
    else {
      local_74 = 10;
      param_2[9] = bVar1 >> 7 | 0x80;
    }
    param_2[8] = bVar1 | 0x80;
LAB_14007cfaa:
    param_2[7] = (byte)(uVar2 >> 0x15) | 0x80;
LAB_14007cfc2:
    param_2[6] = (byte)(uVar2 >> 0xe) | 0x80;
LAB_14007cfda:
    param_2[5] = (byte)(uVar2 >> 7) | 0x80;
LAB_14007cff2:
    param_2[4] = (byte)(param_1 >> 0x1c) | 0x80;
LAB_14007d007:
    param_2[3] = (byte)(local_res8 >> 0x15) | 0x80;
LAB_14007d01f:
    param_2[2] = (byte)(local_res8 >> 0xe) | 0x80;
  }
  param_2[1] = (byte)(local_res8 >> 7) | 0x80;
LAB_14007d04f:
  *param_2 = (byte)param_1 | 0x80;
  param_2[local_74 + -1] = param_2[local_74 + -1] & 0x7f;
  return param_2 + local_74;
}


// ==== FUN_14007d0b0 @ 14007d0b0  byte * FUN_14007d0b0(uint param_1, byte * param_2)

byte * FUN_14007d0b0(uint param_1,byte *param_2)

{
  byte *pbVar1;
  byte local_res8;
  
  if (param_1 < 0x80) {
    local_res8 = (byte)param_1;
    *param_2 = local_res8;
    pbVar1 = param_2 + 1;
  }
  else {
    pbVar1 = (byte *)FUN_14007c1f0(param_1,param_2);
  }
  return pbVar1;
}


// ==== FUN_14007d100 @ 14007d100  undefined FUN_14007d100(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_1, void * param_2)

void FUN_14007d100(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                   *param_1,void *param_2)

{
  __uint64 _Var1;
  char *pcVar2;
  
  _Var1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (param_1);
  pcVar2 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::data
                     (param_1);
  FUN_14007be30(pcVar2,(int)_Var1,param_2);
  return;
}


// ==== FUN_14007d140 @ 14007d140  int * FUN_14007d140(int * param_1, int * param_2)

int * FUN_14007d140(int *param_1,int *param_2)

{
  int *local_10;
  
  local_10 = param_1;
  if (*param_2 < *param_1) {
    local_10 = param_2;
  }
  return local_10;
}


// ==== FUN_14007d190 @ 14007d190  int * FUN_14007d190(int * param_1, int * param_2)

int * FUN_14007d190(int *param_1,int *param_2)

{
  int *local_10;
  
  local_10 = param_1;
  if (*param_1 < *param_2) {
    local_10 = param_2;
  }
  return local_10;
}


// ==== FUN_14007d1e0 @ 14007d1e0  undefined8 * FUN_14007d1e0(undefined8 * param_1, undefined8 param_2, int param_3, int param_4)

undefined8 * FUN_14007d1e0(undefined8 *param_1,undefined8 param_2,int param_3,int param_4)

{
  int local_10;
  
  FUN_14007efb0(param_1);
  *param_1 = google::protobuf::io::ArrayInputStream::vftable;
  param_1[1] = param_2;
  *(int *)(param_1 + 2) = param_3;
  local_10 = param_3;
  if (0 < param_4) {
    local_10 = param_4;
  }
  *(int *)((longlong)param_1 + 0x14) = local_10;
  *(undefined4 *)(param_1 + 3) = 0;
  *(undefined4 *)((longlong)param_1 + 0x1c) = 0;
  return param_1;
}


// ==== FUN_14007d290 @ 14007d290  undefined FUN_14007d290(undefined8 * param_1)

void FUN_14007d290(undefined8 *param_1)

{
  *param_1 = google::protobuf::io::ArrayInputStream::vftable;
  FUN_14007f440(param_1);
  return;
}


// ==== FUN_14007d760 @ 14007d760  undefined8 * FUN_14007d760(undefined8 * param_1, undefined8 param_2, int param_3, int param_4)

undefined8 * FUN_14007d760(undefined8 *param_1,undefined8 param_2,int param_3,int param_4)

{
  int local_10;
  
  FUN_14007f050(param_1);
  *param_1 = google::protobuf::io::ArrayOutputStream::vftable;
  param_1[1] = param_2;
  *(int *)(param_1 + 2) = param_3;
  local_10 = param_3;
  if (0 < param_4) {
    local_10 = param_4;
  }
  *(int *)((longlong)param_1 + 0x14) = local_10;
  *(undefined4 *)(param_1 + 3) = 0;
  *(undefined4 *)((longlong)param_1 + 0x1c) = 0;
  return param_1;
}


// ==== FUN_14007d810 @ 14007d810  undefined FUN_14007d810(undefined8 * param_1)

void FUN_14007d810(undefined8 *param_1)

{
  *param_1 = google::protobuf::io::ArrayOutputStream::vftable;
  FUN_14007f460(param_1);
  return;
}


// ==== FUN_14007dbb0 @ 14007dbb0  undefined8 * FUN_14007dbb0(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_14007dbb0(undefined8 *param_1,undefined8 param_2)

{
  FUN_14007f050(param_1);
  *param_1 = google::protobuf::io::StringOutputStream::vftable;
  param_1[1] = param_2;
  return param_1;
}


// ==== FUN_14007dc00 @ 14007dc00  undefined FUN_14007dc00(undefined8 * param_1)

void FUN_14007dc00(undefined8 *param_1)

{
  *param_1 = google::protobuf::io::StringOutputStream::vftable;
  FUN_14007f460(param_1);
  return;
}


// ==== FUN_14007dfd0 @ 14007dfd0  undefined FUN_14007dfd0(undefined8 * param_1)

void FUN_14007dfd0(undefined8 *param_1)

{
  *param_1 = google::protobuf::io::CopyingInputStream::vftable;
  return;
}


// ==== FUN_14007e0f0 @ 14007e0f0  undefined8 * FUN_14007e0f0(undefined8 * param_1, undefined8 param_2, int param_3)

undefined8 * FUN_14007e0f0(undefined8 *param_1,undefined8 param_2,int param_3)

{
  int local_10;
  
  FUN_14007efb0(param_1);
  *param_1 = google::protobuf::io::CopyingInputStreamAdaptor::vftable;
  param_1[1] = param_2;
  *(undefined1 *)(param_1 + 2) = 0;
  *(undefined1 *)((longlong)param_1 + 0x11) = 0;
  param_1[3] = 0;
  FUN_14007f240(param_1 + 4,0);
  local_10 = param_3;
  if (param_3 < 1) {
    local_10 = 0x2000;
  }
  *(int *)(param_1 + 5) = local_10;
  *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 6) = 0;
  return param_1;
}


// ==== FUN_14007e1c0 @ 14007e1c0  undefined FUN_14007e1c0(undefined8 * param_1)

void FUN_14007e1c0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  *param_1 = google::protobuf::io::CopyingInputStreamAdaptor::vftable;
  if ((*(char *)(param_1 + 2) != '\0') &&
     (puVar1 = (undefined8 *)param_1[1], puVar1 != (undefined8 *)0x0)) {
    (**(code **)*puVar1)(puVar1,1);
  }
  FUN_14007f260(param_1 + 4);
  FUN_14007f440(param_1);
  return;
}


// ==== FUN_14007e830 @ 14007e830  undefined FUN_14007e830(longlong param_1)

void FUN_14007e830(longlong param_1)

{
  longlong lVar1;
  void *pvVar2;
  
  lVar1 = FUN_14007f2e0((undefined8 *)(param_1 + 0x20));
  if (lVar1 == 0) {
    pvVar2 = operator_new__((longlong)*(int *)(param_1 + 0x28));
    FUN_14007f290((longlong *)(param_1 + 0x20),(longlong)pvVar2);
  }
  return;
}


// ==== FUN_14007e880 @ 14007e880  undefined FUN_14007e880(longlong param_1)

void FUN_14007e880(longlong param_1)

{
  int *piVar1;
  longlong lVar2;
  undefined1 *puVar3;
  undefined1 local_78 [8];
  undefined4 local_70 [16];
  uint local_30;
  undefined8 local_28;
  undefined4 *local_20;
  undefined4 *local_18;
  
  local_28 = 0xfffffffffffffffe;
  local_30 = 0;
  if (*(int *)(param_1 + 0x30) != 0) {
    puVar3 = local_78;
    for (lVar2 = 1; lVar2 != 0; lVar2 = lVar2 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    local_20 = FUN_1400783d0(local_70,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\io\\zero_copy_stream_impl_lite.cc"
                             ,0x139);
    local_30 = local_30 | 1;
    local_18 = local_20;
    piVar1 = (int *)FUN_140078030((longlong)local_20,"CHECK failed: (backup_bytes_) == (0): ");
    FUN_140078580(local_78,piVar1);
  }
  if ((local_30 & 1) != 0) {
    local_30 = local_30 & 0xfffffffe;
    FUN_140078440((longlong)local_70);
  }
  *(undefined4 *)(param_1 + 0x2c) = 0;
  FUN_14007f290((longlong *)(param_1 + 0x20),0);
  return;
}


// ==== FUN_14007e970 @ 14007e970  undefined FUN_14007e970(undefined8 * param_1)

void FUN_14007e970(undefined8 *param_1)

{
  *param_1 = google::protobuf::io::CopyingOutputStream::vftable;
  return;
}


// ==== FUN_14007e990 @ 14007e990  undefined8 * FUN_14007e990(undefined8 * param_1, undefined8 param_2, int param_3)

undefined8 * FUN_14007e990(undefined8 *param_1,undefined8 param_2,int param_3)

{
  int local_10;
  
  FUN_14007f050(param_1);
  *param_1 = google::protobuf::io::CopyingOutputStreamAdaptor::vftable;
  param_1[1] = param_2;
  *(undefined1 *)(param_1 + 2) = 0;
  *(undefined1 *)((longlong)param_1 + 0x11) = 0;
  param_1[3] = 0;
  FUN_14007f240(param_1 + 4,0);
  local_10 = param_3;
  if (param_3 < 1) {
    local_10 = 0x2000;
  }
  *(int *)(param_1 + 5) = local_10;
  *(undefined4 *)((longlong)param_1 + 0x2c) = 0;
  return param_1;
}


// ==== FUN_14007ea50 @ 14007ea50  undefined FUN_14007ea50(undefined8 * param_1)

void FUN_14007ea50(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  *param_1 = google::protobuf::io::CopyingOutputStreamAdaptor::vftable;
  FUN_14007ee60((longlong)param_1);
  if ((*(char *)(param_1 + 2) != '\0') &&
     (puVar1 = (undefined8 *)param_1[1], puVar1 != (undefined8 *)0x0)) {
    (**(code **)*puVar1)(puVar1,1);
  }
  FUN_14007f260(param_1 + 4);
  FUN_14007f460(param_1);
  return;
}


// ==== FUN_14007eaf0 @ 14007eaf0  undefined FUN_14007eaf0(longlong param_1)

void FUN_14007eaf0(longlong param_1)

{
  FUN_14007ee60(param_1);
  return;
}


// ==== FUN_14007ee60 @ 14007ee60  undefined8 FUN_14007ee60(longlong param_1)

ulonglong FUN_14007ee60(longlong param_1)

{
  char cVar1;
  undefined7 uVar4;
  undefined8 uVar2;
  ulonglong uVar3;
  
  if (*(char *)(param_1 + 0x11) == '\0') {
    uVar4 = (undefined7)((ulonglong)param_1 >> 8);
    if (*(int *)(param_1 + 0x2c) == 0) {
      uVar3 = CONCAT71(uVar4,1);
    }
    else {
      uVar2 = FUN_14007f2e0((undefined8 *)(param_1 + 0x20));
      cVar1 = (**(code **)(**(longlong **)(param_1 + 8) + 8))
                        (*(undefined8 *)(param_1 + 8),uVar2,*(undefined4 *)(param_1 + 0x2c));
      if (cVar1 == '\0') {
        *(undefined1 *)(param_1 + 0x11) = 1;
        uVar3 = FUN_14007ef80(param_1);
        uVar3 = uVar3 & 0xffffffffffffff00;
      }
      else {
        *(longlong *)(param_1 + 0x18) =
             (longlong)*(int *)(param_1 + 0x2c) + *(longlong *)(param_1 + 0x18);
        *(undefined4 *)(param_1 + 0x2c) = 0;
        uVar3 = CONCAT71(uVar4,1);
      }
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}


// ==== FUN_14007ef20 @ 14007ef20  undefined FUN_14007ef20(longlong param_1)

void FUN_14007ef20(longlong param_1)

{
  bool bVar1;
  void *pvVar2;
  
  bVar1 = FUN_14007f2f0((longlong *)(param_1 + 0x20),0);
  if (bVar1) {
    pvVar2 = operator_new__((longlong)*(int *)(param_1 + 0x28));
    FUN_14007f290((longlong *)(param_1 + 0x20),(longlong)pvVar2);
  }
  return;
}


// ==== FUN_14007ef80 @ 14007ef80  undefined FUN_14007ef80(longlong param_1)

void FUN_14007ef80(longlong param_1)

{
  *(undefined4 *)(param_1 + 0x2c) = 0;
  FUN_14007f290((longlong *)(param_1 + 0x20),0);
  return;
}


// ==== FUN_14007efb0 @ 14007efb0  undefined8 * FUN_14007efb0(undefined8 * param_1)

undefined8 * FUN_14007efb0(undefined8 *param_1)

{
  *param_1 = google::protobuf::io::ZeroCopyInputStream::vftable;
  return param_1;
}


// ==== FUN_14007f050 @ 14007f050  undefined8 * FUN_14007f050(undefined8 * param_1)

undefined8 * FUN_14007f050(undefined8 *param_1)

{
  *param_1 = google::protobuf::io::ZeroCopyOutputStream::vftable;
  return param_1;
}


// ==== FUN_14007f240 @ 14007f240  undefined8 * FUN_14007f240(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_14007f240(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = param_2;
  return param_1;
}


// ==== FUN_14007f260 @ 14007f260  undefined FUN_14007f260(undefined8 * param_1)

void FUN_14007f260(undefined8 *param_1)

{
  operator_delete__((void *)*param_1);
  return;
}


// ==== FUN_14007f290 @ 14007f290  undefined FUN_14007f290(longlong * param_1, longlong param_2)

void FUN_14007f290(longlong *param_1,longlong param_2)

{
  if (param_2 != *param_1) {
    operator_delete__((void *)*param_1);
    *param_1 = param_2;
  }
  return;
}


// ==== FUN_14007f2e0 @ 14007f2e0  undefined8 FUN_14007f2e0(undefined8 * param_1)

undefined8 FUN_14007f2e0(undefined8 *param_1)

{
  return *param_1;
}


// ==== FUN_14007f2f0 @ 14007f2f0  bool FUN_14007f2f0(longlong * param_1, longlong param_2)

bool FUN_14007f2f0(longlong *param_1,longlong param_2)

{
  return *param_1 == param_2;
}


// ==== FUN_14007f330 @ 14007f330  undefined4 FUN_14007f330(undefined4 * param_1)

undefined4 FUN_14007f330(undefined4 *param_1)

{
  return *param_1;
}


// ==== FUN_14007f340 @ 14007f340  undefined FUN_14007f340(void)

void FUN_14007f340(void)

{
  Sleep(0);
  return;
}


// ==== FUN_14007f360 @ 14007f360  undefined FUN_14007f360(longlong * param_1, longlong * param_2)

void FUN_14007f360(longlong *param_1,longlong *param_2)

{
  longlong lVar1;
  undefined8 local_18;
  
  lVar1 = FUN_140078d00(param_1);
  if (lVar1 != 2) {
    local_18 = FUN_14007f410(param_1,0,1);
    if (local_18 == 0) {
      (**(code **)(*param_2 + 8))(param_2);
      FUN_14007f3f0(param_1,2);
    }
    else {
      while (local_18 == 1) {
        FUN_14007f340();
        local_18 = FUN_140078d00(param_1);
      }
    }
  }
  return;
}


// ==== FUN_14007f3f0 @ 14007f3f0  undefined FUN_14007f3f0(undefined8 * param_1, undefined8 param_2)

void FUN_14007f3f0(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = param_2;
  return;
}


// ==== FUN_14007f410 @ 14007f410  undefined FUN_14007f410(longlong * param_1, longlong param_2, longlong param_3)

void FUN_14007f410(longlong *param_1,longlong param_2,longlong param_3)

{
  FUN_14007f5b0(param_1,param_2,param_3);
  return;
}


// ==== FUN_14007f440 @ 14007f440  undefined FUN_14007f440(undefined8 * param_1)

void FUN_14007f440(undefined8 *param_1)

{
  *param_1 = google::protobuf::io::ZeroCopyInputStream::vftable;
  return;
}


// ==== FUN_14007f460 @ 14007f460  undefined FUN_14007f460(undefined8 * param_1)

void FUN_14007f460(undefined8 *param_1)

{
  *param_1 = google::protobuf::io::ZeroCopyOutputStream::vftable;
  return;
}


// ==== FUN_14007f510 @ 14007f510  int FUN_14007f510(int * param_1, int param_2, int param_3)

int FUN_14007f510(int *param_1,int param_2,int param_3)

{
  int iVar1;
  
  LOCK();
  iVar1 = *param_1;
  if (param_2 == iVar1) {
    *param_1 = param_3;
    iVar1 = param_2;
  }
  UNLOCK();
  return iVar1;
}


// ==== FUN_14007f550 @ 14007f550  undefined4 FUN_14007f550(undefined4 * param_1, undefined4 param_2)

undefined4 FUN_14007f550(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  LOCK();
  uVar1 = *param_1;
  *param_1 = param_2;
  UNLOCK();
  return uVar1;
}


// ==== FUN_14007f5b0 @ 14007f5b0  longlong FUN_14007f5b0(longlong * param_1, longlong param_2, longlong param_3)

longlong FUN_14007f5b0(longlong *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  
  LOCK();
  lVar1 = *param_1;
  if (param_2 == lVar1) {
    *param_1 = param_3;
    lVar1 = param_2;
  }
  UNLOCK();
  return lVar1;
}


// ==== FUN_14007f5f0 @ 14007f5f0  undefined8 FUN_14007f5f0(undefined8 * param_1, undefined8 param_2)

undefined8 FUN_14007f5f0(undefined8 *param_1,undefined8 param_2)

{
  undefined8 uVar1;
  
  LOCK();
  uVar1 = *param_1;
  *param_1 = param_2;
  UNLOCK();
  return uVar1;
}


// ==== FUN_14007f630 @ 14007f630  longlong FUN_14007f630(longlong * param_1, longlong param_2)

longlong FUN_14007f630(longlong *param_1,longlong param_2)

{
  longlong lVar1;
  
  LOCK();
  lVar1 = *param_1;
  *param_1 = *param_1 + param_2;
  UNLOCK();
  return lVar1 + param_2;
}


// ==== FUN_14007f6c0 @ 14007f6c0  undefined FUN_14007f6c0(undefined8 * param_1)

void FUN_14007f6c0(undefined8 *param_1)

{
  *param_1 = IMapData::vftable;
  return;
}


// ==== FUN_14007fa10 @ 14007fa10  undefined8 FUN_14007fa10(void)

undefined8 FUN_14007fa10(void)

{
  log_InlineLogERROR("Bad call to IMapData::CreateNew()");
  return 0;
}


// ==== FUN_14007fae0 @ 14007fae0  longlong FUN_14007fae0(longlong param_1, ulonglong param_2)

longlong FUN_14007fae0(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18)) / 0x30) <= param_2
     ) {
    _invalid_parameter_noinfo();
  }
  return param_2 * 0x30 + *(longlong *)(param_1 + 0x18);
}


// ==== FUN_14007fb40 @ 14007fb40  longlong FUN_14007fb40(longlong param_1, ulonglong param_2)

longlong FUN_14007fb40(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18)) / 0x30) <= param_2
     ) {
    _invalid_parameter_noinfo();
  }
  return param_2 * 0x30 + *(longlong *)(param_1 + 0x18);
}


// ==== FUN_14007fbb0 @ 14007fbb0  bool FUN_14007fbb0(longlong * param_1, longlong * param_2)

bool FUN_14007fbb0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_14007fbf0 @ 14007fbf0  bool FUN_14007fbf0(longlong * param_1, longlong * param_2)

bool FUN_14007fbf0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_14007fc30 @ 14007fc30  longlong FUN_14007fc30(longlong * param_1)

longlong FUN_14007fc30(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14007fc52;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14007fc52:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_14007fc70 @ 14007fc70  longlong * FUN_14007fc70(longlong * param_1)

longlong * FUN_14007fc70(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14007fc92;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14007fc92:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + 4;
  return param_1;
}


// ==== FUN_14007fe30 @ 14007fe30  longlong * FUN_14007fe30(longlong * param_1)

longlong * FUN_14007fe30(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14007fe52;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14007fe52:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + 0x30;
  return param_1;
}


// ==== FUN_14007fe70 @ 14007fe70  longlong FUN_14007fe70(longlong * param_1, longlong * param_2)

longlong FUN_14007fe70(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return (param_1[1] - param_2[1]) / 0x30;
}


// ==== FUN_14007fed0 @ 14007fed0  longlong * FUN_14007fed0(longlong * param_1)

longlong * FUN_14007fed0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14007fef2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14007fef2:
  if (param_1[1] == puVar1[5]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = *(longlong *)param_1[1];
  return param_1;
}


// ==== FUN_14007ff20 @ 14007ff20  longlong * FUN_14007ff20(longlong * param_1, longlong * param_2)

longlong * FUN_14007ff20(longlong *param_1,longlong *param_2)

{
  undefined8 *puVar1;
  
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_14007ff57;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_14007ff57:
  if (param_1[1] == puVar1[5]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = *(longlong *)param_1[1];
  return param_2;
}


// ==== FUN_14007ff80 @ 14007ff80  bool FUN_14007ff80(longlong * param_1, longlong * param_2)

bool FUN_14007ff80(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_14007ffd0 @ 14007ffd0  bool FUN_14007ffd0(longlong * param_1, longlong * param_2)

bool FUN_14007ffd0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_140080020 @ 140080020  longlong FUN_140080020(longlong * param_1)

longlong FUN_140080020(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140080042;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140080042:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_140080070 @ 140080070  undefined FUN_140080070(void)

void FUN_140080070(void)

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


