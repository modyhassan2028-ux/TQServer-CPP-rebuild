// NpcServer.exe :: CLogThread  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CLogThread::vf_0x8 @ 140002e90  undefined vf_0x8(longlong param_1)

void CLogThread::vf_0x8(longlong param_1)

{
  int iVar1;
  undefined1 auStack_778 [32];
  char local_758 [1855];
  undefined1 local_19;
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_778;
  iVar1 = (**(code **)(**(longlong **)(param_1 + 0x48) + 0x10))();
  if (0 < iVar1) {
    (**(code **)(**(longlong **)(param_1 + 0x48) + 0x10))();
    _snprintf(local_758,0x740,"error:: LOG_MSG_PORT have %d LOG not print!");
    local_19 = 0;
    (**(code **)(**(longlong **)(param_1 + 0x40) + 0x28))
              (*(longlong **)(param_1 + 0x40),param_1 + 0x50,local_758,1);
  }
  (**(code **)(**(longlong **)(param_1 + 0x40) + 0x20))();
  *(undefined8 *)(param_1 + 0x40) = 0;
  __security_check_cookie(local_18 ^ (ulonglong)auStack_778);
  return;
}


// ==== CLogThread::vf_0x10 @ 140002f30  undefined vf_0x10(void)

void CLogThread::vf_0x10(void)

{
  return;
}


// ==== CLogThread::vf_0x18 @ 140002f40  undefined vf_0x18(longlong param_1)

void CLogThread::vf_0x18(longlong param_1)

{
  char cVar1;
  ulong uVar2;
  uint uVar3;
  undefined1 auStack_8a8 [32];
  char *local_888;
  undefined4 *local_880;
  ulong local_878;
  longlong local_870;
  undefined4 local_868;
  undefined4 local_864;
  undefined4 local_860;
  undefined8 local_858;
  CTickAnalyst local_850 [24];
  CTickAnalyst local_838 [32];
  char local_818;
  undefined1 local_817 [1854];
  undefined1 local_d9;
  ulonglong local_18;
  
  local_858 = 0xfffffffffffffffe;
  local_18 = DAT_140103510 ^ (ulonglong)auStack_8a8;
  local_870 = param_1;
  if ((DAT_140103c6c & 1) == 0) {
    DAT_140103c6c = DAT_140103c6c | 1;
    DAT_140103c68 = tq::TimeGet(0);
  }
  cVar1 = (**(code **)(**(longlong **)(param_1 + 0x48) + 0x58))
                    (*(longlong **)(param_1 + 0x48),s___AVCLogThread___140102168._20_4_);
  CTickAnalyst::CTickAnalyst(local_838,0x3c);
  uVar2 = tq::TimeGet(0);
  local_878 = uVar2;
  if (cVar1 == '\0') {
    (**(code **)(**(longlong **)(param_1 + 0x40) + 0x18))();
    uVar3 = uVar2 - DAT_140103c68;
    if (uVar3 < 0x2711) {
      DAT_140103c68 = DAT_140103c68 + 1000;
    }
    else {
      local_818 = '\0';
      memset(local_817,0,0x73f);
      _snprintf(&local_818,0x740,"error:: resync CLogThread::OnTimer cumulative deviation %ldms",
                (ulonglong)uVar3);
      local_d9 = 0;
      (**(code **)(**(longlong **)(param_1 + 0x40) + 0x28))
                (*(longlong **)(param_1 + 0x40),param_1 + 0x50,&local_818,1);
      DAT_140103c68 = uVar2;
    }
  }
  else {
    while( true ) {
      local_880 = &local_868;
      local_888 = &local_818;
      cVar1 = (**(code **)(**(longlong **)(param_1 + 0x48) + 0x48))
                        (*(longlong **)(param_1 + 0x48),0xffffffff,0xffffffff,0x800);
      if (cVar1 == '\0') break;
      CTickAnalyst::CTickAnalyst(local_850,0x3d);
      local_888 = (char *)CONCAT44(local_888._4_4_,local_868);
      (**(code **)(**(longlong **)(param_1 + 0x40) + 0x10))
                (*(longlong **)(param_1 + 0x40),local_864,&local_818,local_860);
      CTickAnalyst::~CTickAnalyst(local_850);
    }
  }
  uVar2 = tq::TimeGet(0);
  if ((int)(uVar2 - DAT_140103c68) < 1000) {
    s___AVCLogThread___140102168._20_4_ = 1000 - (uVar2 - DAT_140103c68);
  }
  else {
    s___AVCLogThread___140102168[0x14] = '\0';
    s___AVCLogThread___140102168[0x15] = '\0';
    s___AVCLogThread___140102168[0x16] = '\0';
    s___AVCLogThread___140102168[0x17] = '\0';
  }
  CTickAnalyst::~CTickAnalyst(local_838);
  __security_check_cookie(local_18 ^ (ulonglong)auStack_8a8);
  return;
}


// ==== CLogThread::vf_0x0 @ 140003150  CThreadBase * vf_0x0(CThreadBase * param_1, uint param_2)

CThreadBase * CLogThread::vf_0x0(CThreadBase *param_1,uint param_2)

{
  *(undefined ***)param_1 = vftable;
  CThreadBase::~CThreadBase(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


