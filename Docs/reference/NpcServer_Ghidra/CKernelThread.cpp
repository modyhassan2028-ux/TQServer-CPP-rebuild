// NpcServer.exe :: CKernelThread  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CKernelThread::vf_0x0 @ 140002230  undefined vf_0x0(longlong param_1)

void CKernelThread::vf_0x0(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x000140002237. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)**(undefined8 **)(param_1 + 8))();
  return;
}


// ==== CKernelThread::vf_0x8 @ 140002240  undefined vf_0x8(longlong param_1)

void CKernelThread::vf_0x8(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x000140002247. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(longlong **)(param_1 + 8) + 8))();
  return;
}


// ==== CKernelThread::vf_0x10 @ 140002250  undefined vf_0x10(longlong param_1)

void CKernelThread::vf_0x10(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x000140002257. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(longlong **)(param_1 + 8) + 0x10))();
  return;
}


// ==== CKernelThread::vf_0x18 @ 140002260  undefined vf_0x18(longlong param_1)

void CKernelThread::vf_0x18(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x000140002267. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(longlong **)(param_1 + 8) + 0x18))();
  return;
}


// ==== CKernelThread::vf_0x10 @ 140002270  undefined vf_0x10(void)

void CKernelThread::vf_0x10(void)

{
  return;
}


// ==== CKernelThread::vf_0x20 @ 140002280  undefined vf_0x20(longlong param_1, void * param_2, int param_3)

void CKernelThread::vf_0x20(longlong param_1,void *param_2,int param_3)

{
  FUN_140001390(*(longlong *)(param_1 + 0x20),param_2,param_3);
  return;
}


// ==== CKernelThread::vf_0x28 @ 140002290  undefined vf_0x28(longlong param_1)

void CKernelThread::vf_0x28(longlong param_1)

{
  FUN_140001440(*(longlong *)(param_1 + 0x20));
  return;
}


// ==== CKernelThread::vf_0x0 @ 140002540  CThreadBase * vf_0x0(CThreadBase * param_1, uint param_2)

CThreadBase * CKernelThread::vf_0x0(CThreadBase *param_1,uint param_2)

{
  *(undefined ***)param_1 = vftable;
  *(undefined ***)(param_1 + 0x40) = vftable;
  CThreadBase::~CThreadBase(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CKernelThread::vf_0x8 @ 140002630  undefined vf_0x8(longlong param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void CKernelThread::vf_0x8
               (longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  ulonglong *puVar2;
  undefined4 local_res10;
  undefined4 local_res14;
  
  if (*(longlong **)(param_1 + 0x68) != (longlong *)0x0) {
    (**(code **)(**(longlong **)(param_1 + 0x68) + 0x10))();
    *(undefined8 *)(param_1 + 0x68) = 0;
  }
  if ((*(longlong *)(param_1 + 0x60) != 0) &&
     (FUN_140001340(*(longlong *)(param_1 + 0x60)), *(longlong *)(param_1 + 0x60) != 0)) {
    FUN_1400014d0(*(void **)(param_1 + 0x60));
    *(undefined8 *)(param_1 + 0x60) = 0;
  }
  local_res10 = 2;
  local_res14 = 0;
  puVar2 = (ulonglong *)&local_res10;
  iVar1 = FUN_140016280(*(longlong *)(param_1 + 0x58),puVar2);
  if (iVar1 < 0) {
    log_InlineLogERROR("CKernelThread::OnDestroy, event_base_loopexit error.");
  }
  Sleep(0x9c4);
  CloseHandle(*(HANDLE *)(param_1 + 0x70));
  if (*(longlong **)(param_1 + 0x58) != (longlong *)0x0) {
    FUN_140014eb0(*(longlong **)(param_1 + 0x58),puVar2,param_3,param_4);
    *(undefined8 *)(param_1 + 0x58) = 0;
  }
  FUN_140012190();
  (**(code **)(**(longlong **)(param_1 + 0x50) + 0x30))();
  return;
}


// ==== CKernelThread::vf_0x18 @ 1400027f0  undefined vf_0x18(longlong param_1)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void CKernelThread::vf_0x18(longlong param_1)

{
  char cVar1;
  bool bVar2;
  ulong uVar3;
  int iVar4;
  undefined1 auStack_508 [32];
  longlong *local_4e8;
  undefined1 *local_4e0;
  char local_4d8;
  int local_4d4;
  ulong local_4d0;
  longlong local_4c8;
  ulong local_4c0;
  undefined1 local_4b8 [4];
  int local_4b4;
  int *local_4a8;
  CTickAnalyst local_4a0 [24];
  CTickAnalyst local_488 [24];
  undefined8 local_470;
  CTickAnalyst local_468 [24];
  CTickAnalyst local_450 [24];
  longlong local_438 [132];
  ulonglong local_18;
  
  local_470 = 0xfffffffffffffffe;
  local_18 = DAT_140103510 ^ (ulonglong)auStack_508;
  local_4c8 = param_1;
  if ((*(longlong *)(param_1 + 0x60) == 0) || (*(longlong *)(param_1 + 0x50) == 0)) {
    log_InlineLogERROR("CKernelThread::OnProcess(), pointer is null.");
  }
  else {
    cVar1 = (**(code **)(**(longlong **)(param_1 + 0x50) + 0x58))
                      (*(longlong **)(param_1 + 0x50),DAT_140102148);
    local_4d8 = cVar1;
    local_4d0 = tq::TimeGet(0);
    CTickAnalyst::CTickAnalyst(local_450,0x4c);
    if (cVar1 != '\0') {
      while( true ) {
        local_4e0 = local_4b8;
        local_4e8 = local_438;
        cVar1 = (**(code **)(**(longlong **)(param_1 + 0x50) + 0x48))
                          (*(longlong **)(param_1 + 0x50),0xffffffff,0xffffffff,0x418);
        if (cVar1 == '\0') break;
        if (local_4b4 == 0x1fbd1) {
          CTickAnalyst::CTickAnalyst(local_4a0,0x4d);
          if (local_438[0] == -1) {
            CTickAnalyst::~CTickAnalyst(local_4a0);
          }
          else {
            FUN_140001cb0(*(longlong *)(param_1 + 0x60));
            CTickAnalyst::~CTickAnalyst(local_4a0);
          }
        }
        else if (local_4b4 == 0x1fbd2) {
          CTickAnalyst::CTickAnalyst(local_488,0x4f);
          if (local_438[0] == -1) {
            CTickAnalyst::~CTickAnalyst(local_488);
          }
          else {
            FUN_140001340(*(longlong *)(param_1 + 0x60));
            CTickAnalyst::~CTickAnalyst(local_488);
          }
        }
        else {
          log_InlineLogERROR("CKernelThread::OnProcess(), packet[%d].");
        }
      }
    }
    bVar2 = FUN_140001440(*(longlong *)(param_1 + 0x60));
    if ((!bVar2) && (*(int *)(param_1 + 0x7c) != 0)) {
      local_4a8 = (int *)(param_1 + 0x78);
      uVar3 = tq::TimeGet(0);
      if ((uint)(*(int *)(param_1 + 0x78) + *(int *)(param_1 + 0x7c)) <= uVar3 / 1000) {
        uVar3 = tq::TimeGet(0);
        *(uint *)(param_1 + 0x7c) = uVar3 / 1000;
        (**(code **)(**(longlong **)(param_1 + 0x68) + 8))();
        (**(code **)**(undefined8 **)(param_1 + 0x48))
                  (*(undefined8 **)(param_1 + 0x48),"Connect to game server again . . .");
        FUN_140001520(*(char **)(param_1 + 0x60));
      }
    }
    if ((DAT_140103c64 & 1) == 0) {
      DAT_140103c64 = DAT_140103c64 | 1;
      DAT_140103c60 = tq::TimeGet(0);
    }
    uVar3 = tq::TimeGet(0);
    iVar4 = uVar3 - DAT_140103c60;
    local_4c8 = CONCAT44(local_4c8._4_4_,iVar4);
    local_4c0 = uVar3;
    if (99 < iVar4) {
      if (iVar4 < 0x2711) {
        DAT_140103c60 = DAT_140103c60 + 100;
      }
      else {
        log_InlineLogWARNING(&DAT_1400beae0,(ulonglong)(uint)(iVar4 / 1000));
        DAT_140103c60 = uVar3;
      }
      CTickAnalyst::CTickAnalyst(local_468,0x50);
      (**(code **)(**(longlong **)(param_1 + 0x68) + 0x20))(*(longlong **)(param_1 + 0x68),uVar3);
      CTickAnalyst::~CTickAnalyst(local_468);
    }
    uVar3 = tq::TimeGet(0);
    local_4d4 = uVar3 - local_4d0;
    LOCK();
    _DAT_140103f28 = _DAT_140103f28 + 1;
    UNLOCK();
    LOCK();
    DAT_140103f2c = DAT_140103f2c + local_4d4;
    UNLOCK();
    if (DAT_140103f30 < local_4d4) {
      LOCK();
      UNLOCK();
      DAT_140103f30 = local_4d4;
    }
    DAT_140102148 = (0x32 - DAT_140102148) - local_4d4;
    if (DAT_140102148 < 1) {
      DAT_140102148 = 1;
    }
    CTickAnalyst::~CTickAnalyst(local_450);
  }
  __security_check_cookie(local_18 ^ (ulonglong)auStack_508);
  return;
}


