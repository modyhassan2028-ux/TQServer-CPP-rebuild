// NpcServer.exe :: CMessagePort  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMessagePort::vf_0x8 @ 14006de30  undefined4 vf_0x8(longlong param_1)

undefined4 CMessagePort::vf_0x8(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0xc);
}


// ==== CMessagePort::vf_0x10 @ 14006de50  undefined4 vf_0x10(longlong param_1)

undefined4 CMessagePort::vf_0x10(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x10);
}


// ==== CMessagePort::vf_0x20 @ 14006de60  bool vf_0x20(longlong param_1)

bool CMessagePort::vf_0x20(longlong param_1)

{
  return *(int *)(param_1 + 0x14) == 0;
}


// ==== CMessagePort::vf_0x40 @ 14006de70  undefined vf_0x40(longlong param_1, int param_2)

void CMessagePort::vf_0x40(longlong param_1,int param_2)

{
  if (param_2 < 1) {
    param_2 = 1;
  }
  *(int *)(param_1 + 0x18) = param_2;
  return;
}


// ==== CMessagePort::vf_0x30 @ 14006e970  undefined4 vf_0x30(longlong param_1)

undefined4 CMessagePort::vf_0x30(longlong param_1)

{
  int iVar1;
  CSingleLock local_20 [24];
  
  CSingleLock::CSingleLock(local_20,(CSyncObject *)(param_1 + 0x68),1);
  *(undefined4 *)(param_1 + 0x14) = 1;
  iVar1 = CSingleLock::Unlock(local_20);
  return CONCAT31((int3)((uint)iVar1 >> 8),1);
}


// ==== CMessagePort::vf_0x18 @ 14006ea60  longlong vf_0x18(void)

longlong CMessagePort::vf_0x18(void)

{
  return DAT_140104698 - DAT_140104690 >> 3;
}


// ==== CMessagePort::vf_0x58 @ 14006eb00  ulonglong vf_0x58(longlong * param_1, DWORD param_2)

ulonglong CMessagePort::vf_0x58(longlong *param_1,DWORD param_2)

{
  int iVar1;
  DWORD DVar2;
  undefined4 extraout_var;
  ulonglong uVar3;
  undefined4 extraout_var_00;
  undefined4 extraout_var_01;
  undefined4 extraout_var_02;
  CSingleLock local_20 [24];
  
  CSingleLock::CSingleLock(local_20,(CSyncObject *)(param_1 + 0xd),1);
  if (*(int *)((longlong)param_1 + 0x14) == 1) {
    iVar1 = CSingleLock::Unlock(local_20);
    uVar3 = CONCAT44(extraout_var,iVar1) & 0xffffffffffffff00;
  }
  else if ((int)param_1[2] == 0) {
    ResetEvent((HANDLE)param_1[4]);
    CSingleLock::Unlock(local_20);
    DVar2 = WaitForSingleObject((HANDLE)param_1[4],param_2);
    if (DVar2 == 0) {
      iVar1 = CSingleLock::Unlock(local_20);
      uVar3 = CONCAT71((int7)(CONCAT44(extraout_var_02,iVar1) >> 8),1);
    }
    else {
      if (DVar2 == 0x80) {
        (**(code **)(*param_1 + 0x30))(param_1);
      }
      iVar1 = CSingleLock::Unlock(local_20);
      uVar3 = CONCAT44(extraout_var_01,iVar1) & 0xffffffffffffff00;
    }
  }
  else {
    iVar1 = CSingleLock::Unlock(local_20);
    uVar3 = CONCAT71((int7)(CONCAT44(extraout_var_00,iVar1) >> 8),1);
  }
  return uVar3;
}


// ==== CMessagePort::vf_0x28 @ 1400701d0  undefined vf_0x28(longlong param_1)

void CMessagePort::vf_0x28(longlong param_1)

{
  longlong *plVar1;
  longlong lVar2;
  void *pvVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  longlong lVar6;
  CSingleLock local_30 [24];
  
  CSingleLock::CSingleLock(local_30,(CSyncObject *)(param_1 + 0x68),1);
  uVar4 = *(ulonglong *)(param_1 + 0x58);
  if (*(longlong *)(param_1 + 0x60) + uVar4 < uVar4) {
    _invalid_parameter_noinfo();
  }
  plVar1 = *(longlong **)(param_1 + 0x28);
  lVar6 = 0;
  while( true ) {
    uVar5 = *(ulonglong *)(param_1 + 0x58) + *(longlong *)(param_1 + 0x60);
    if (uVar5 < *(ulonglong *)(param_1 + 0x58)) {
      _invalid_parameter_noinfo();
    }
    if ((plVar1 == (longlong *)0x0) || (plVar1 != *(longlong **)(param_1 + 0x28))) {
      _invalid_parameter_noinfo();
    }
    if (uVar4 == uVar5) break;
    uVar5 = uVar4 >> 1;
    if (plVar1 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar2 = lVar6;
    }
    else {
      lVar2 = *plVar1;
    }
    if ((ulonglong)(*(longlong *)(lVar2 + 0x38) + *(longlong *)(lVar2 + 0x30)) <= uVar4) {
      _invalid_parameter_noinfo();
    }
    lVar2 = lVar6;
    if (plVar1 != (longlong *)0x0) {
      lVar2 = *plVar1;
    }
    if (*(ulonglong *)(lVar2 + 0x28) <= uVar5) {
      lVar2 = lVar6;
      if (plVar1 != (longlong *)0x0) {
        lVar2 = *plVar1;
      }
      uVar5 = uVar5 - *(longlong *)(lVar2 + 0x28);
    }
    lVar2 = lVar6;
    if (plVar1 != (longlong *)0x0) {
      lVar2 = *plVar1;
    }
    operator_delete(*(void **)(*(longlong *)(*(longlong *)(lVar2 + 0x20) + uVar5 * 8) +
                              (ulonglong)((uint)uVar4 & 1) * 8));
    if (plVar1 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar2 = lVar6;
    }
    else {
      lVar2 = *plVar1;
    }
    if ((ulonglong)(*(longlong *)(lVar2 + 0x38) + *(longlong *)(lVar2 + 0x30)) <= uVar4) {
      _invalid_parameter_noinfo();
    }
    uVar4 = uVar4 + 1;
  }
  FUN_14006f900(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x10) = 0;
  lVar2 = *(longlong *)(param_1 + 0xd8);
  while (lVar2 != 0) {
    if (*(longlong *)(param_1 + 0xd8) == 0) {
      pvVar3 = (void *)0x0;
    }
    else {
      uVar4 = *(ulonglong *)(param_1 + 0xd0);
      if (*(longlong *)(param_1 + 0xd8) + uVar4 < uVar4) {
        _invalid_parameter_noinfo();
      }
      plVar1 = *(longlong **)(param_1 + 0xa0);
      uVar5 = uVar4 >> 1;
      if (plVar1 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar2 = lVar6;
      }
      else {
        lVar2 = *plVar1;
      }
      if ((ulonglong)(*(longlong *)(lVar2 + 0x38) + *(longlong *)(lVar2 + 0x30)) <= uVar4) {
        _invalid_parameter_noinfo();
      }
      lVar2 = lVar6;
      if (plVar1 != (longlong *)0x0) {
        lVar2 = *plVar1;
      }
      if (*(ulonglong *)(lVar2 + 0x28) <= uVar5) {
        lVar2 = lVar6;
        if (plVar1 != (longlong *)0x0) {
          lVar2 = *plVar1;
        }
        uVar5 = uVar5 - *(longlong *)(lVar2 + 0x28);
      }
      lVar2 = lVar6;
      if (plVar1 != (longlong *)0x0) {
        lVar2 = *plVar1;
      }
      pvVar3 = *(void **)(*(longlong *)(*(longlong *)(lVar2 + 0x20) + uVar5 * 8) +
                         (ulonglong)((uint)uVar4 & 1) * 8);
      if (*(longlong *)(param_1 + 0xd8) != 0) {
        *(longlong *)(param_1 + 0xd0) = *(longlong *)(param_1 + 0xd0) + 1;
        if ((ulonglong)(*(longlong *)(param_1 + 200) * 2) <= *(ulonglong *)(param_1 + 0xd0)) {
          *(undefined8 *)(param_1 + 0xd0) = 0;
        }
        lVar2 = *(longlong *)(param_1 + 0xd8) + -1;
        *(longlong *)(param_1 + 0xd8) = lVar2;
        if (lVar2 == 0) {
          *(undefined8 *)(param_1 + 0xd0) = 0;
        }
      }
    }
    operator_delete(pvVar3);
    lVar2 = *(longlong *)(param_1 + 0xd8);
  }
  if (*(HANDLE *)(param_1 + 0x20) != (HANDLE)0x0) {
    CloseHandle(*(HANDLE *)(param_1 + 0x20));
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  CSingleLock::Unlock(local_30);
  return;
}


// ==== CMessagePort::vf_0x0 @ 1400714a0  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMessagePort::vf_0x0(undefined8 *param_1,uint param_2)

{
  FUN_140070e90(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CMessagePort::vf_0x38 @ 1400714d0  undefined8 vf_0x38(longlong param_1)

undefined8 CMessagePort::vf_0x38(longlong param_1)

{
  longlong *plVar1;
  int iVar2;
  longlong lVar3;
  undefined4 extraout_var;
  ulonglong uVar4;
  ulonglong uVar5;
  undefined8 local_res8;
  CSingleLock local_30 [24];
  
  CSingleLock::CSingleLock(local_30,(CSyncObject *)(param_1 + 0x68),1);
  *(undefined4 *)(param_1 + 0x14) = 0;
  uVar4 = *(ulonglong *)(param_1 + 0x58);
  if (uVar4 + *(longlong *)(param_1 + 0x60) < uVar4) {
    _invalid_parameter_noinfo();
  }
  plVar1 = *(longlong **)(param_1 + 0x28);
  while( true ) {
    uVar5 = *(ulonglong *)(param_1 + 0x58) + *(longlong *)(param_1 + 0x60);
    if (uVar5 < *(ulonglong *)(param_1 + 0x58)) {
      _invalid_parameter_noinfo();
    }
    if ((plVar1 == (longlong *)0x0) || (plVar1 != *(longlong **)(param_1 + 0x28))) {
      _invalid_parameter_noinfo();
    }
    if (uVar4 == uVar5) break;
    if (*(int *)(param_1 + 0xd8) < *(int *)(param_1 + 0x18)) {
      uVar5 = uVar4 >> 1;
      if (plVar1 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar3 = 0;
      }
      else {
        lVar3 = *plVar1;
      }
      if ((ulonglong)(*(longlong *)(lVar3 + 0x38) + *(longlong *)(lVar3 + 0x30)) <= uVar4) {
        _invalid_parameter_noinfo();
      }
      if (plVar1 == (longlong *)0x0) {
        lVar3 = 0;
      }
      else {
        lVar3 = *plVar1;
      }
      if (*(ulonglong *)(lVar3 + 0x28) <= uVar5) {
        if (plVar1 == (longlong *)0x0) {
          lVar3 = 0;
        }
        else {
          lVar3 = *plVar1;
        }
        uVar5 = uVar5 - *(longlong *)(lVar3 + 0x28);
      }
      if (plVar1 == (longlong *)0x0) {
        lVar3 = 0;
      }
      else {
        lVar3 = *plVar1;
      }
      local_res8 = *(undefined8 *)
                    (*(longlong *)(*(longlong *)(lVar3 + 0x20) + uVar5 * 8) +
                    (ulonglong)((uint)uVar4 & 1) * 8);
      FUN_140071010(param_1 + 0xa0,&local_res8);
    }
    else {
      uVar5 = uVar4 >> 1;
      if (plVar1 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar3 = 0;
      }
      else {
        lVar3 = *plVar1;
      }
      if ((ulonglong)(*(longlong *)(lVar3 + 0x38) + *(longlong *)(lVar3 + 0x30)) <= uVar4) {
        _invalid_parameter_noinfo();
      }
      if (plVar1 == (longlong *)0x0) {
        lVar3 = 0;
      }
      else {
        lVar3 = *plVar1;
      }
      if (*(ulonglong *)(lVar3 + 0x28) <= uVar5) {
        if (plVar1 == (longlong *)0x0) {
          lVar3 = 0;
        }
        else {
          lVar3 = *plVar1;
        }
        uVar5 = uVar5 - *(longlong *)(lVar3 + 0x28);
      }
      if (plVar1 == (longlong *)0x0) {
        lVar3 = 0;
      }
      else {
        lVar3 = *plVar1;
      }
      operator_delete(*(void **)(*(longlong *)(*(longlong *)(lVar3 + 0x20) + uVar5 * 8) +
                                (ulonglong)((uint)uVar4 & 1) * 8));
    }
    if (plVar1 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar3 = 0;
    }
    else {
      lVar3 = *plVar1;
    }
    if ((ulonglong)(*(longlong *)(lVar3 + 0x38) + *(longlong *)(lVar3 + 0x30)) <= uVar4) {
      _invalid_parameter_noinfo();
    }
    uVar4 = uVar4 + 1;
  }
  FUN_14006f900(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x10) = 0;
  ResetEvent(*(HANDLE *)(param_1 + 0x20));
  iVar2 = CSingleLock::Unlock(local_30);
  return CONCAT71((int7)(CONCAT44(extraout_var,iVar2) >> 8),1);
}


// ==== CMessagePort::vf_0x50 @ 140071970  ulonglong vf_0x50(longlong * param_1, int param_2, uint param_3, uint param_4, void * param_5)

ulonglong CMessagePort::vf_0x50
                    (longlong *param_1,int param_2,uint param_3,uint param_4,void *param_5)

{
  char cVar1;
  int iVar2;
  ulonglong extraout_RAX;
  undefined4 extraout_var;
  undefined4 extraout_var_00;
  ulonglong uVar3;
  undefined4 extraout_var_01;
  undefined4 extraout_var_02;
  CSingleLock local_20 [24];
  
  if (param_5 == (void *)0x0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    uVar3 = extraout_RAX & 0xffffffffffffff00;
  }
  else {
    CSingleLock::CSingleLock(local_20,(CSyncObject *)(param_1 + 0xd),1);
    cVar1 = (**(code **)(*param_1 + 0x20))(param_1);
    if (cVar1 == '\0') {
      iVar2 = CSingleLock::Unlock(local_20);
      uVar3 = CONCAT44(extraout_var,iVar2) & 0xffffffffffffff00;
    }
    else if (param_2 == 60000) {
      iVar2 = CSingleLock::Unlock(local_20);
      uVar3 = CONCAT71((int7)(CONCAT44(extraout_var_00,iVar2) >> 8),1);
    }
    else if ((param_2 < 0) || ((int)(DAT_140104698 - DAT_140104690 >> 3) <= param_2)) {
      log_InlineLogERROR("CMessagePort::Send() with bad port %d");
      iVar2 = CSingleLock::Unlock(local_20);
      uVar3 = CONCAT44(extraout_var_02,iVar2) & 0xffffffffffffff00;
    }
    else {
      CSingleLock::Unlock(local_20);
      if ((ulonglong)(DAT_140104698 - DAT_140104690 >> 3) <= (ulonglong)(longlong)param_2) {
        _invalid_parameter_noinfo();
      }
      uVar3 = FUN_1400716f0(*(longlong *)(DAT_140104690 + (longlong)param_2 * 8),
                            *(uint *)((longlong)param_1 + 0xc),param_3,param_4,param_5);
      iVar2 = CSingleLock::Unlock(local_20);
      uVar3 = CONCAT71((int7)(CONCAT44(extraout_var_01,iVar2) >> 8),(char)uVar3);
    }
  }
  return uVar3;
}


// ==== CMessagePort::vf_0x48 @ 1400723e0  ulonglong vf_0x48(longlong param_1, undefined4 param_2, undefined4 param_3, uint param_4, void * param_5, undefined4 * param_6)

ulonglong CMessagePort::vf_0x48
                    (longlong param_1,undefined4 param_2,undefined4 param_3,uint param_4,
                    void *param_5,undefined4 *param_6)

{
  void *pvVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 extraout_var;
  ulonglong uVar5;
  undefined8 uVar6;
  undefined4 extraout_var_00;
  undefined4 extraout_var_01;
  undefined4 extraout_var_02;
  undefined4 local_res8 [2];
  uint local_48 [2];
  undefined8 local_40;
  CSingleLock local_38 [32];
  
  pvVar1 = param_5;
  local_40 = 0xfffffffffffffffe;
  if (param_5 == (void *)0x0) {
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  CSingleLock::CSingleLock(local_38,(CSyncObject *)(param_1 + 0x68),1);
  if (*(int *)(param_1 + 0x14) == 1) {
    if (param_6 != (undefined4 *)0x0) {
      param_6[3] = 1;
    }
    iVar2 = CSingleLock::Unlock(local_38);
    uVar5 = CONCAT44(extraout_var,iVar2) & 0xffffffffffffff00;
  }
  else {
    local_res8[0] = param_3;
    param_5._0_4_ = param_2;
    uVar6 = FUN_140072260(param_1,(undefined4 *)&param_5,local_res8,local_48,pvVar1);
    if ((char)uVar6 == '\0') {
      if (param_6 != (undefined4 *)0x0) {
        param_6[3] = 0;
      }
      iVar2 = CSingleLock::Unlock(local_38);
      uVar5 = CONCAT44(extraout_var_02,iVar2) & 0xffffffffffffff00;
    }
    else {
      uVar3 = FUN_14006dd80(local_48[0]);
      uVar4 = FUN_14006dd80(param_4);
      if ((int)uVar4 < (int)uVar3) {
        log_InlineLogERROR(&DAT_1400be0b0);
        if (param_6 != (undefined4 *)0x0) {
          param_6[3] = 2;
        }
        iVar2 = CSingleLock::Unlock(local_38);
        uVar5 = CONCAT44(extraout_var_00,iVar2) & 0xffffffffffffff00;
      }
      else {
        if (param_6 != (undefined4 *)0x0) {
          *param_6 = param_5._0_4_;
          param_6[1] = local_res8[0];
          param_6[2] = local_48[0];
          param_6[3] = 0;
        }
        iVar2 = CSingleLock::Unlock(local_38);
        uVar5 = CONCAT71((int7)(CONCAT44(extraout_var_01,iVar2) >> 8),1);
      }
    }
  }
  return uVar5;
}


