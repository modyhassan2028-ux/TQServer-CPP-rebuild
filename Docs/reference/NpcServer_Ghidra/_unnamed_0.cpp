// NpcServer.exe :: _unnamed  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== FUN_140001020 @ 140001020  undefined FUN_140001020(undefined8 * param_1)

void FUN_140001020(undefined8 *param_1)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  return;
}


// ==== FUN_140001040 @ 140001040  undefined FUN_140001040(longlong * param_1)

void FUN_140001040(longlong *param_1)

{
  int *piVar1;
  
  LOCK();
  piVar1 = (int *)((longlong)param_1 + 0x14);
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (*piVar1 == 0) {
    (**(code **)(*param_1 + 8))();
  }
  return;
}


// ==== FUN_1400010b0 @ 1400010b0  undefined FUN_1400010b0(void)

void FUN_1400010b0(void)

{
  log_InlineLogERROR(&DAT_1400be0b0);
  return;
}


// ==== FUN_140001130 @ 140001130  undefined FUN_140001130(void)

void FUN_140001130(void)

{
  int iVar1;
  undefined1 auStack_1d8 [32];
  short local_1b8 [208];
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_1d8;
  iVar1 = Ordinal_115(2,local_1b8);
  if (iVar1 != 0) {
    log_InlineLogERROR("ERROR: Init WSAStartup() failed.");
    __security_check_cookie(local_18 ^ (ulonglong)auStack_1d8);
    return;
  }
  if (local_1b8[0] != 2) {
    log_InlineLogERROR("ERROR: WSAStartup Version not match 2.0");
    __security_check_cookie(local_18 ^ (ulonglong)auStack_1d8);
    return;
  }
  __security_check_cookie(local_18 ^ (ulonglong)auStack_1d8);
  return;
}


// ==== FUN_1400011d0 @ 1400011d0  undefined1 FUN_1400011d0(void)

undefined1 FUN_1400011d0(void)

{
  Ordinal_116();
  return 1;
}


// ==== FUN_1400011f0 @ 1400011f0  undefined FUN_1400011f0(void * param_1)

void FUN_1400011f0(void *param_1)

{
  if (param_1 != (void *)0x0) {
    operator_delete__(param_1);
  }
  return;
}


// ==== FUN_140001210 @ 140001210  undefined1 * FUN_140001210(undefined1 * param_1)

undefined1 * FUN_140001210(undefined1 *param_1)

{
  *(undefined4 *)(param_1 + 0x10) = 0;
  memset(param_1 + 0x14,0,0x800);
  *(undefined8 *)(param_1 + 0x818) = 0xffffffffffffffff;
  *(undefined4 *)(param_1 + 0x814) = 0;
  *(undefined4 *)(param_1 + 0x830) = 0;
  *(undefined8 *)(param_1 + 0x820) = 0;
  *(undefined8 *)(param_1 + 0x828) = 0;
  *param_1 = 0;
  return param_1;
}


// ==== FUN_140001280 @ 140001280  void * FUN_140001280(void * param_1, byte param_2)

void * FUN_140001280(void *param_1,byte param_2)

{
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_1400012a0 @ 1400012a0  undefined8 FUN_1400012a0(longlong param_1, int param_2)

ulonglong FUN_1400012a0(longlong param_1,int param_2)

{
  int *piVar1;
  uint uVar2;
  void *in_RAX;
  void *extraout_RAX;
  
  if (*(int *)(param_1 + 0x814) < param_2) {
    log_InlineLogERROR(&DAT_1400be0b0);
    in_RAX = extraout_RAX;
  }
  if (*(int *)(param_1 + 0x830) == 2) {
    uVar2 = *(uint *)(param_1 + 0x814);
    in_RAX = (void *)(ulonglong)uVar2;
    if (param_2 < (int)uVar2) {
      in_RAX = memcpy((void *)(param_1 + 0x14),(void *)((longlong)param_2 + 0x14 + param_1),
                      (longlong)(int)(uVar2 - param_2));
    }
    piVar1 = (int *)(param_1 + 0x814);
    *piVar1 = *piVar1 - param_2;
    if (-1 < *piVar1) {
      return CONCAT71((int7)((ulonglong)in_RAX >> 8),1);
    }
    *(undefined4 *)(param_1 + 0x814) = 0;
  }
  return (ulonglong)in_RAX & 0xffffffffffffff00;
}


// ==== FUN_140001340 @ 140001340  undefined FUN_140001340(longlong param_1)

void FUN_140001340(longlong param_1)

{
  if (*(longlong **)(param_1 + 0x820) != (longlong *)0x0) {
    FUN_140006a60(*(longlong **)(param_1 + 0x820));
    *(undefined8 *)(param_1 + 0x820) = 0;
  }
  *(undefined4 *)(param_1 + 0x830) = 0;
  *(undefined8 *)(param_1 + 0x818) = 0xffffffffffffffff;
  return;
}


// ==== FUN_140001390 @ 140001390  undefined4 FUN_140001390(longlong param_1, void * param_2, int param_3)

uint FUN_140001390(longlong param_1,void *param_2,int param_3)

{
  uint in_EAX;
  uint extraout_EAX;
  int iVar1;
  uint uVar2;
  
  if (*(int *)(param_1 + 0x830) == 2) {
    if (*(longlong *)(param_1 + 0x818) != -1) {
      iVar1 = FUN_140005bf0(*(longlong *)(param_1 + 0x820),param_2,(longlong)param_3);
      if (iVar1 < 0) {
        iVar1 = FUN_140007540(*(longlong *)(param_1 + 0x818));
        if (iVar1 != 0x2746) {
          log_InlineLogERROR("CClientSocket::SendPacket, bufferevent_write packet failed[%d].");
        }
        uVar2 = FUN_140001340(param_1);
        return uVar2 & 0xffffff00;
      }
      return CONCAT31((int3)((uint)iVar1 >> 8),1);
    }
    log_InlineLogERROR("CClientSocket::SendPacket, invalid socket failed.");
    in_EAX = extraout_EAX;
    if (*(longlong **)(param_1 + 0x820) != (longlong *)0x0) {
      in_EAX = FUN_140006a60(*(longlong **)(param_1 + 0x820));
      *(undefined8 *)(param_1 + 0x820) = 0;
    }
    *(undefined8 *)(param_1 + 0x818) = 0xffffffffffffffff;
    *(undefined4 *)(param_1 + 0x830) = 0;
  }
  return in_EAX & 0xffffff00;
}


// ==== FUN_140001440 @ 140001440  bool FUN_140001440(longlong param_1)

bool FUN_140001440(longlong param_1)

{
  return *(int *)(param_1 + 0x830) == 2;
}


// ==== FUN_140001490 @ 140001490  undefined FUN_140001490(longlong * param_1)

void FUN_140001490(longlong *param_1)

{
  longlong *plVar1;
  int *piVar2;
  
  LOCK();
  plVar1 = param_1 + 2;
  *(int *)plVar1 = (int)*plVar1 + -1;
  UNLOCK();
  if ((int)*plVar1 == 0) {
    (**(code **)*param_1)();
    LOCK();
    piVar2 = (int *)((longlong)param_1 + 0x14);
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (*piVar2 == 0) {
      (**(code **)(*param_1 + 8))(param_1);
    }
  }
  return;
}


// ==== FUN_1400014d0 @ 1400014d0  undefined FUN_1400014d0(void * param_1)

void FUN_1400014d0(void *param_1)

{
  if (*(longlong **)((longlong)param_1 + 0x820) != (longlong *)0x0) {
    FUN_140006a60(*(longlong **)((longlong)param_1 + 0x820));
    *(undefined8 *)((longlong)param_1 + 0x820) = 0;
  }
  *(undefined8 *)((longlong)param_1 + 0x818) = 0xffffffffffffffff;
  *(undefined4 *)((longlong)param_1 + 0x830) = 0;
  operator_delete(param_1);
  return;
}


// ==== FUN_140001520 @ 140001520  undefined FUN_140001520(char * param_1)

void FUN_140001520(char *param_1)

{
  undefined2 uVar1;
  int iVar2;
  longlong lVar3;
  longlong *plVar4;
  char *pcVar5;
  code *pcVar6;
  undefined1 auStackY_58 [32];
  ushort local_28 [2];
  int iStack_24;
  undefined8 local_20;
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStackY_58;
  if (*param_1 == '\0') {
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  if (*(longlong *)(param_1 + 0x828) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
LAB_14000159b:
    __security_check_cookie(local_18 ^ (ulonglong)auStackY_58);
    return;
  }
  if (*(int *)(param_1 + 0x830) == 2) {
    __security_check_cookie(local_18 ^ (ulonglong)auStackY_58);
    return;
  }
  if (*(int *)(param_1 + 0x830) != 0) goto LAB_14000159b;
  if (*(longlong *)(param_1 + 0x818) != -1) {
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  iVar2 = Ordinal_11(param_1);
  if (iVar2 == -1) {
    lVar3 = Ordinal_52(param_1);
    if (lVar3 == 0) {
      log_InlineLogERROR(&DAT_1400be2d8);
      FUN_140001340((longlong)param_1);
      goto LAB_140001789;
    }
    iVar2 = *(int *)**(undefined8 **)(lVar3 + 0x18);
  }
  local_20 = 0;
  _local_28 = 2;
  uVar1 = Ordinal_9(*(undefined2 *)(param_1 + 0x10));
  _local_28 = CONCAT44(iVar2,CONCAT22(uVar1,local_28[0]));
  lVar3 = FUN_1400022c0(*(longlong *)(param_1 + 0x828));
  plVar4 = FUN_14000b3e0(lVar3,(HANDLE)0xffffffffffffffff,3);
  *(longlong **)(param_1 + 0x820) = plVar4;
  if (plVar4 == (longlong *)0x0) {
    Ordinal_111();
    pcVar5 = "CClientSocket::Open, bufferevent_socket_new error[%d], at %s, %d.";
  }
  else {
    pcVar6 = FUN_140002380;
    FUN_140005a50((longlong)plVar4,FUN_1400022f0,&DAT_140002370,FUN_140002380,
                  *(undefined8 *)(param_1 + 0x828));
    iVar2 = FUN_14000b9f0(*(longlong **)(param_1 + 0x820),local_28,0x10,pcVar6);
    if (iVar2 < 0) {
      Ordinal_111();
      pcVar5 = "CClientSocket::Open, bufferevent_socket_connect error[%d], at %s, %d.";
    }
    else {
      lVar3 = FUN_140006200(*(longlong *)(param_1 + 0x820));
      *(longlong *)(param_1 + 0x818) = lVar3;
      if (-1 < lVar3) {
        param_1[0x814] = '\0';
        param_1[0x815] = '\0';
        param_1[0x816] = '\0';
        param_1[0x817] = '\0';
        param_1[0x830] = '\x02';
        param_1[0x831] = '\0';
        param_1[0x832] = '\0';
        param_1[0x833] = '\0';
        goto LAB_140001789;
      }
      Ordinal_111();
      pcVar5 = "CClientSocket::Open, bufferevent_getfd error[%d], at %s, %d.";
    }
  }
  log_InlineLogERROR(pcVar5);
  FUN_140001340((longlong)param_1);
LAB_140001789:
  __security_check_cookie(local_18 ^ (ulonglong)auStackY_58);
  return;
}


// ==== FUN_1400017b0 @ 1400017b0  undefined FUN_1400017b0(longlong param_1)

void FUN_1400017b0(longlong param_1)

{
  ushort uVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  longlong *plVar5;
  undefined8 uVar6;
  CTickAnalyst local_50 [24];
  
  if (*(longlong *)(param_1 + 0x828) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0,"CHECK","m_pKernelThread",
                       "f:\\version\\cqserver-78.0.11-1204\\npcserver\\clientsocket.cpp",0x184);
  }
  else {
    plVar5 = (longlong *)FUN_1400022e0(*(longlong *)(param_1 + 0x828));
    if (plVar5 == (longlong *)0x0) {
      log_InlineLogERROR(&DAT_1400be0b0,"CHECK","pKernel",
                         "f:\\version\\cqserver-78.0.11-1204\\npcserver\\clientsocket.cpp",0x187);
    }
    else if ((*(int *)(param_1 + 0x830) == 2) && (0 < *(int *)(param_1 + 0x814))) {
      do {
        iVar3 = *(int *)(param_1 + 0x814);
        if (iVar3 < 1) {
          return;
        }
        if (iVar3 < 9) {
          return;
        }
        uVar1 = *(ushort *)(param_1 + 0x14);
        if (iVar3 < (int)(uint)uVar1) {
          return;
        }
        if (uVar1 < 4) {
          return;
        }
        if (0x400 < uVar1) {
          return;
        }
        uVar2 = *(undefined2 *)(param_1 + 0x16);
        uVar4 = *(undefined4 *)(param_1 + 0x18);
        if (uVar1 == 0) {
          return;
        }
        CTickAnalyst::CTickAnalyst(local_50,0x4e);
        (**(code **)(*plVar5 + 0x18))(plVar5,uVar2,param_1 + 0x1c,uVar1 - 8,uVar4);
        CTickAnalyst::~CTickAnalyst(local_50);
        uVar6 = FUN_1400012a0(param_1,(uint)uVar1);
      } while ((char)uVar6 != '\0');
      log_InlineLogERROR(&DAT_1400be0b0,"IF_NOT","this->ClearPacket(nNetPacketSize)",
                         "f:\\version\\cqserver-78.0.11-1204\\npcserver\\clientsocket.cpp",0x1a7);
    }
  }
  return;
}


// ==== FUN_140001970 @ 140001970  undefined FUN_140001970(longlong param_1)

void FUN_140001970(longlong param_1)

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


// ==== FUN_1400019b0 @ 1400019b0  undefined FUN_1400019b0(undefined8 * param_1, undefined8 param_2, longlong param_3)

void FUN_1400019b0(undefined8 *param_1,undefined8 param_2,longlong param_3)

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


// ==== FUN_140001a50 @ 140001a50  undefined8 * FUN_140001a50(undefined8 * param_1, undefined8 param_2, undefined8 param_3)

undefined8 * FUN_140001a50(undefined8 *param_1,undefined8 param_2,undefined8 param_3)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  param_1[1] = param_2;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14) = 1;
  *param_1 = std::tr1::_Ref_count_d<char,void_(__cdecl*)(char*___ptr64),class_std::allocator<int>_>
             ::vftable;
  param_1[4] = param_3;
  return param_1;
}


// ==== FUN_140001b00 @ 140001b00  undefined FUN_140001b00(undefined8 * param_1)

void FUN_140001b00(undefined8 *param_1)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  return;
}


// ==== FUN_140001ba0 @ 140001ba0  undefined FUN_140001ba0(char * param_1, longlong param_2)

void FUN_140001ba0(char *param_1,longlong param_2)

{
  char cVar1;
  int iVar2;
  undefined1 auStack_448 [32];
  undefined8 local_428;
  CIniFile local_418 [1024];
  ulonglong local_18;
  
  local_428 = 0xfffffffffffffffe;
  local_18 = DAT_140103510 ^ (ulonglong)auStack_448;
  *(longlong *)(param_1 + 0x828) = param_2;
  if (param_2 == 0) {
    log_InlineLogERROR("CClientSocket::Create, m_pKernelThread is NULL.");
  }
  else {
    CIniFile::CIniFile(local_418,"config.ini","GameServer");
    CIniFile::GetString(local_418,param_1,"GAMESERVER_IP",0x10);
    iVar2 = CIniFile::GetInt(local_418,"GAMESERVER_PORT");
    if (iVar2 == 0) {
      log_InlineLogERROR(&DAT_1400be4c8,
                         "f:\\version\\cqserver-78.0.11-1204\\npcserver\\clientsocket.cpp",0x81);
      iVar2 = 0x16b8;
    }
    *(int *)(param_1 + 0x10) = iVar2 + 4;
    cVar1 = FUN_140001520(param_1);
    if (cVar1 == '\0') {
      log_InlineLogERROR("CClientSocket::Create, NpcServer client socket Open error.");
      CIniFile::~CIniFile(local_418);
    }
    else {
      CIniFile::~CIniFile(local_418);
    }
  }
  __security_check_cookie(local_18 ^ (ulonglong)auStack_448);
  return;
}


// ==== FUN_140001cb0 @ 140001cb0  undefined FUN_140001cb0(longlong param_1)

void FUN_140001cb0(longlong param_1)

{
  longlong lVar1;
  ulonglong uVar2;
  int iVar3;
  int iVar4;
  
  if (*(longlong *)(param_1 + 0x820) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return;
  }
  if (*(int *)(param_1 + 0x830) == 2) {
    if (0x7ff < *(int *)(param_1 + 0x814)) {
      FUN_1400017b0(param_1);
    }
    lVar1 = FUN_140005b70(*(longlong *)(param_1 + 0x820));
    uVar2 = FUN_14000c370(lVar1);
    if (0 < (int)uVar2) {
      while( true ) {
        iVar3 = 0x800 - *(int *)(param_1 + 0x814);
        iVar4 = (int)uVar2;
        if (iVar4 <= iVar3) {
          iVar3 = iVar4;
        }
        lVar1 = FUN_140005c30(*(longlong *)(param_1 + 0x820),
                              (void *)((longlong)*(int *)(param_1 + 0x814) + 0x14 + param_1),
                              (longlong)iVar3);
        iVar3 = (int)lVar1;
        if (iVar3 < 1) break;
        *(int *)(param_1 + 0x814) = *(int *)(param_1 + 0x814) + iVar3;
        uVar2 = (ulonglong)(uint)(iVar4 - iVar3);
        FUN_1400017b0(param_1);
        if (iVar4 - iVar3 < 1) {
          return;
        }
      }
      FUN_140007540(*(longlong *)(param_1 + 0x818));
      log_InlineLogERROR("CClientSocket::ProcessAllIncoming, bufferevent_read err[%d].");
      FUN_140001340(param_1);
    }
  }
  return;
}


// ==== FUN_140001db0 @ 140001db0  undefined FUN_140001db0(longlong param_1)

void FUN_140001db0(longlong param_1)

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


// ==== FUN_140001df0 @ 140001df0  undefined8 * FUN_140001df0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140001df0(undefined8 *param_1,undefined8 *param_2)

{
  FUN_1400019b0(param_1,*param_2,param_2[1]);
  return param_1;
}


// ==== FUN_140001e10 @ 140001e10  undefined FUN_140001e10(undefined8 * param_1)

void FUN_140001e10(undefined8 *param_1)

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


// ==== FUN_140001ea0 @ 140001ea0  undefined FUN_140001ea0(undefined8 * param_1, undefined8 param_2, undefined8 param_3)

void FUN_140001ea0(undefined8 *param_1,undefined8 param_2,undefined8 param_3)

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
    *puVar1 = std::tr1::_Ref_count_d<char,void_(__cdecl*)(char*___ptr64),class_std::allocator<int>_>
              ::vftable;
    puVar1[4] = param_3;
  }
  FUN_1400019b0(param_1,param_2,(longlong)puVar1);
  return;
}


// ==== FUN_140001f40 @ 140001f40  undefined FUN_140001f40(longlong param_1)

void FUN_140001f40(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_1 + 0x10);
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


// ==== FUN_140001f90 @ 140001f90  undefined8 * FUN_140001f90(undefined8 * param_1)

undefined8 * FUN_140001f90(undefined8 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_140001e10(param_1);
  return param_1;
}


// ==== FUN_140001fb0 @ 140001fb0  undefined8 * FUN_140001fb0(undefined8 * param_1, undefined8 param_2, undefined8 param_3)

undefined8 * FUN_140001fb0(undefined8 *param_1,undefined8 param_2,undefined8 param_3)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_140001ea0(param_1,param_2,param_3);
  return param_1;
}


// ==== FUN_140001fd0 @ 140001fd0  int * FUN_140001fd0(int * param_1, void * param_2, int param_3)

int * FUN_140001fd0(int *param_1,void *param_2,int param_3)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  void *pvVar4;
  undefined8 local_40;
  longlong *local_38;
  
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  FUN_140001e10((undefined8 *)(param_1 + 2));
  param_1[1] = 0;
  pvVar4 = operator_new__((longlong)param_3);
  local_40 = 0;
  local_38 = (longlong *)0x0;
  FUN_140001ea0(&local_40,pvVar4,FUN_1400011f0);
  plVar1 = local_38;
  FUN_1400019b0((undefined8 *)(param_1 + 2),local_40,(longlong)local_38);
  plVar3 = local_38;
  if (plVar1 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar1 + 2;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)*plVar1 == 0) {
      (**(code **)*local_38)(local_38);
      LOCK();
      piVar2 = (int *)((longlong)plVar3 + 0x14);
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (*piVar2 == 0) {
        (**(code **)(*local_38 + 8))();
      }
    }
  }
  if (*(void **)(param_1 + 2) == (void *)0x0) {
    *param_1 = 0;
  }
  else {
    memcpy(*(void **)(param_1 + 2),param_2,(longlong)param_3);
    *param_1 = param_3;
  }
  return param_1;
}


// ==== FUN_1400020d0 @ 1400020d0  undefined FUN_1400020d0(void)

void FUN_1400020d0(void)

{
  return;
}


// ==== FUN_1400021f0 @ 1400021f0  undefined FUN_1400021f0(CThreadBase * param_1)

void FUN_1400021f0(CThreadBase *param_1)

{
  *(undefined ***)param_1 = CKernelThread::vftable;
  *(undefined ***)(param_1 + 0x40) = CKernelThread::vftable;
                    /* WARNING: Could not recover jumptable at 0x00014000221b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  CThreadBase::~CThreadBase(param_1);
  return;
}


// ==== FUN_1400022a0 @ 1400022a0  undefined FUN_1400022a0(longlong param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_1400022a0(longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  if (*(longlong **)(param_1 + 0x58) != (longlong *)0x0) {
    FUN_140016270(*(longlong **)(param_1 + 0x58),param_2,param_3,param_4);
  }
  return;
}


// ==== FUN_1400022c0 @ 1400022c0  undefined8 FUN_1400022c0(longlong param_1)

undefined8 FUN_1400022c0(longlong param_1)

{
  return *(undefined8 *)(param_1 + 0x58);
}


// ==== FUN_1400022e0 @ 1400022e0  undefined8 FUN_1400022e0(longlong param_1)

undefined8 FUN_1400022e0(longlong param_1)

{
  return *(undefined8 *)(param_1 + 0x68);
}


// ==== FUN_1400022f0 @ 1400022f0  undefined FUN_1400022f0(longlong param_1, longlong param_2)

void FUN_1400022f0(longlong param_1,longlong param_2)

{
  longlong local_res10 [3];
  
  local_res10[0] = FUN_140006200(param_1);
  if (local_res10[0] == -1) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return;
  }
  (**(code **)(**(longlong **)(param_2 + 0x50) + 0x50))
            (*(longlong **)(param_2 + 0x50),1,0x1fbd1,8,local_res10);
  return;
}


// ==== FUN_140002380 @ 140002380  undefined FUN_140002380(longlong * param_1, byte param_2, longlong param_3)

void FUN_140002380(longlong *param_1,byte param_2,longlong param_3)

{
  int iVar1;
  char *pcVar2;
  longlong local_res18 [2];
  
  local_res18[0] = FUN_140006200((longlong)param_1);
  if (-1 < local_res18[0]) {
    if ((char)param_2 < '\0') {
      iVar1 = FUN_1400071b0(param_1,6);
      if (-1 < iVar1) {
        return;
      }
      Ordinal_111();
      pcVar2 = "CKernelThread::BufferEventCb, client bufferevent_enable error[%d].";
    }
    else {
      if ((param_2 & 0x30) != 0) {
        (**(code **)(**(longlong **)(param_3 + 0x50) + 0x50))
                  (*(longlong **)(param_3 + 0x50),1,0x1fbd2,8,local_res18);
        return;
      }
      pcVar2 = "CKernelThread::BufferEventCb, events[%0x] error.";
    }
    log_InlineLogERROR(pcVar2);
  }
  return;
}


// ==== FUN_140002450 @ 140002450  int FUN_140002450(longlong param_1)

int FUN_140002450(longlong param_1)

{
  ulong uVar1;
  
  uVar1 = tq::TimeGet(0);
  *(uint *)(param_1 + 4) = uVar1 / 1000;
  return uVar1 * 0x10624dd3;
}


// ==== FUN_140002480 @ 140002480  ulonglong FUN_140002480(int * param_1)

ulonglong FUN_140002480(int *param_1)

{
  ulong uVar1;
  
  uVar1 = tq::TimeGet(0);
  return CONCAT71((int7)((ulonglong)uVar1 * 0x10624dd3 >> 8),
                  (uint)(param_1[1] + *param_1) <= uVar1 / 1000) & 0xffffffff;
}


// ==== FUN_1400024c0 @ 1400024c0  undefined FUN_1400024c0(undefined8 * param_1)

void FUN_1400024c0(undefined8 *param_1)

{
  if ((void *)*param_1 != (void *)0x0) {
    FUN_1400014d0((void *)*param_1);
    *param_1 = 0;
  }
  return;
}


// ==== FUN_1400024f0 @ 1400024f0  undefined8 FUN_1400024f0(longlong param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

undefined8 FUN_1400024f0(longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  log_InlineLogMessage("EvnetRoutine worker thread is up and running");
  FUN_1400022a0(param_1,param_2,param_3,param_4);
  log_InlineLogMessage("EvnetRoutine worker thread exited");
  return 0;
}


// ==== FUN_140002700 @ 140002700  ulonglong FUN_140002700(int * param_1)

ulonglong FUN_140002700(int *param_1)

{
  ulong uVar1;
  
  uVar1 = tq::TimeGet(0);
  if ((uint)(param_1[1] + *param_1) <= uVar1 / 1000) {
    uVar1 = tq::TimeGet(0);
    param_1[1] = uVar1 / 1000;
    return CONCAT71((uint7)((ulonglong)uVar1 * 0x10624dd3 >> 8) & 0xffffff,1);
  }
  return (ulonglong)uVar1 * 0x10624dd3 & 0xffffff00;
}


// ==== FUN_140002760 @ 140002760  int FUN_140002760(undefined4 * param_1, undefined4 param_2)

int FUN_140002760(undefined4 *param_1,undefined4 param_2)

{
  ulong uVar1;
  
  *param_1 = param_2;
  uVar1 = tq::TimeGet(0);
  param_1[1] = uVar1 / 1000;
  return uVar1 * 0x10624dd3;
}


// ==== FUN_140002790 @ 140002790  CThreadBase * FUN_140002790(CThreadBase * param_1)

CThreadBase * FUN_140002790(CThreadBase *param_1)

{
  CThreadBase::CThreadBase(param_1);
  *(undefined ***)param_1 = CKernelThread::vftable;
  *(undefined ***)(param_1 + 0x40) = CKernelThread::vftable;
  *(undefined4 *)(param_1 + 0x78) = 0;
  *(undefined4 *)(param_1 + 0x7c) = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  *(undefined8 *)(param_1 + 0x68) = 0;
  *(undefined8 *)(param_1 + 0x50) = 0;
  *(undefined8 *)(param_1 + 0x58) = 0;
  *(undefined8 *)(param_1 + 0x70) = 0;
  *(undefined8 *)(param_1 + 0x60) = 0;
  return param_1;
}


// ==== FUN_140002b30 @ 140002b30  void * FUN_140002b30(CThreadBase * param_1, longlong param_2, longlong * param_3, undefined8 * param_4)

void * FUN_140002b30(CThreadBase *param_1,longlong param_2,longlong *param_3,undefined8 *param_4)

{
  char cVar1;
  bool bVar2;
  DWORD DVar3;
  DWORD DVar4;
  ulong uVar5;
  undefined8 *puVar6;
  longlong *plVar7;
  ulonglong uVar8;
  undefined1 *puVar9;
  char *pcVar10;
  HANDLE Thread;
  undefined7 extraout_var;
  uint *puVar11;
  ulonglong extraout_RAX;
  ulonglong extraout_RAX_00;
  ulonglong extraout_RAX_01;
  ulonglong extraout_RAX_02;
  undefined8 uVar12;
  _SYSTEM_INFO local_40;
  
  bVar2 = SUB81(param_4,0);
  if ((param_2 != 0) && (param_3 != (longlong *)0x0)) {
    *(longlong *)(param_1 + 0x48) = param_2;
    *(longlong **)(param_1 + 0x50) = param_3;
    (**(code **)(*param_3 + 0x38))(param_3);
    plVar7 = *(longlong **)(param_1 + 0x50);
    uVar12 = 0x1e;
    (**(code **)(*plVar7 + 0x40))();
    FUN_140005750(plVar7,uVar12,param_3,param_4);
    puVar6 = FUN_140012580();
    if (puVar6 == (undefined8 *)0x0) {
      log_InlineLogERROR("CKernelThread::Create event_config_new failed");
      register0x00000020 = (BADSPACEBASE *)(extraout_RAX_02 & 0xffffffffffffff00);
    }
    else {
      FUN_140010a00((longlong)puVar6,4);
      GetSystemInfo(&local_40);
      uVar8 = (ulonglong)local_40.dwNumberOfProcessors;
      FUN_140010a20((longlong)puVar6,local_40.dwNumberOfProcessors);
      plVar7 = FUN_140015ed0(puVar6,uVar8,(longlong)param_3,param_4);
      *(longlong **)(param_1 + 0x58) = plVar7;
      FUN_140012660(puVar6);
      if (*(undefined8 **)(param_1 + 0x58) == (undefined8 *)0x0) {
        log_InlineLogERROR("CKernelThread::Create m_pEventBase is NULL");
        register0x00000020 = (BADSPACEBASE *)(extraout_RAX_01 & 0xffffffffffffff00);
      }
      else {
        uVar12 = FUN_140010d80(*(undefined8 **)(param_1 + 0x58));
        log_InlineLogMessage("libevent method: %s",uVar12);
        register0x00000020 = (BADSPACEBASE *)FUN_14001d350();
        *(BADSPACEBASE **)(param_1 + 0x68) = register0x00000020;
        if ((undefined8 *)register0x00000020 != (undefined8 *)0x0) {
          cVar1 = (*(code *)**(undefined8 **)register0x00000020)(register0x00000020,param_1 + 0x40);
          if (cVar1 == '\0') {
            uVar8 = (**(code **)(**(longlong **)(param_1 + 0x68) + 0x10))();
            register0x00000020 = (BADSPACEBASE *)(uVar8 & 0xffffffffffffff00);
          }
          else {
            puVar9 = (undefined1 *)operator_new(0x838);
            if (puVar9 == (undefined1 *)0x0) {
              pcVar10 = (char *)0x0;
            }
            else {
              pcVar10 = FUN_140001210(puVar9);
            }
            *(char **)(param_1 + 0x60) = pcVar10;
            if ((pcVar10 == (char *)0x0) ||
               (cVar1 = FUN_140001ba0(pcVar10,(longlong)param_1), cVar1 == '\0')) {
              log_InlineLogERROR("CNpcWorld::Create, cannot create NpcServer client socket.");
              uVar8 = extraout_RAX_00;
              if (*(longlong *)(param_1 + 0x60) != 0) {
                uVar8 = FUN_1400014d0(*(void **)(param_1 + 0x60));
                *(undefined8 *)(param_1 + 0x60) = 0;
              }
              register0x00000020 = (BADSPACEBASE *)(uVar8 & 0xffffffffffffff00);
            }
            else {
              Thread = (HANDLE)_beginthreadex((void *)0x0,0,FUN_1400024f0,param_1,0,(uint *)0x0);
              *(HANDLE *)(param_1 + 0x70) = Thread;
              if (Thread == (HANDLE)0x0) {
                puVar11 = (uint *)_errno();
                log_InlineLogERROR("CSocketKernel::Create _beginthreadex failed with error code:%u",
                                   (ulonglong)*puVar11);
                register0x00000020 = (BADSPACEBASE *)(extraout_RAX & 0xffffffffffffff00);
              }
              else {
                DVar3 = GetThreadId(Thread);
                DVar4 = GetCurrentThreadId();
                log_InlineLogMessage
                          ("thread %u created libevent worker thread %u",(ulonglong)DVar4,
                           (ulonglong)DVar3);
                *(undefined4 *)(param_1 + 0x78) = 1;
                uVar5 = tq::TimeGet(0);
                *(uint *)(param_1 + 0x7c) = uVar5 / 1000;
                bVar2 = CThreadBase::CreateThread(param_1,"NPC Server KernelThread",bVar2);
                register0x00000020 = (BADSPACEBASE *)CONCAT71(extraout_var,bVar2);
              }
            }
          }
        }
      }
    }
  }
  return register0x00000020;
}


// ==== FUN_140002d70 @ 140002d70  CThreadBase * FUN_140002d70(CThreadBase * param_1, undefined8 param_2, char * param_3)

CThreadBase * FUN_140002d70(CThreadBase *param_1,undefined8 param_2,char *param_3)

{
  CThreadBase::CThreadBase(param_1);
  *(undefined ***)param_1 = CLogThread::vftable;
  *(undefined8 *)(param_1 + 0x40) = 0;
  *(undefined8 *)(param_1 + 0x48) = param_2;
  if (param_3 != (char *)0x0) {
    tq::SafeCopy((char *)(param_1 + 0x50),param_3,0x80);
  }
  return param_1;
}


// ==== FUN_140002df0 @ 140002df0  undefined FUN_140002df0(CThreadBase * param_1)

void FUN_140002df0(CThreadBase *param_1)

{
  *(undefined ***)param_1 = CLogThread::vftable;
                    /* WARNING: Could not recover jumptable at 0x000140002e10. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  CThreadBase::~CThreadBase(param_1);
  return;
}


// ==== FUN_140002e20 @ 140002e20  bool FUN_140002e20(CThreadBase * param_1, bool param_2)

bool FUN_140002e20(CThreadBase *param_1,bool param_2)

{
  char cVar1;
  bool bVar2;
  ILogKernel *pIVar3;
  
  pIVar3 = ILogKernel::CreateNew();
  *(ILogKernel **)(param_1 + 0x40) = pIVar3;
  if (pIVar3 != (ILogKernel *)0x0) {
    cVar1 = (**(code **)(*(longlong *)pIVar3 + 8))
                      (pIVar3,*(undefined8 *)(param_1 + 0x48),param_1 + 0x50);
    if (cVar1 != '\0') {
                    /* WARNING: Could not recover jumptable at 0x000140002e6d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      bVar2 = CThreadBase::CreateThread(param_1,"LogThread",param_2);
      return bVar2;
    }
  }
  return false;
}


// ==== FUN_1400031b0 @ 1400031b0  CWinApp * FUN_1400031b0(CWinApp * param_1)

CWinApp * FUN_1400031b0(CWinApp *param_1)

{
  CWinApp::CWinApp(param_1,(char *)0x0);
  *(undefined ***)param_1 = CNpcServerApp::vftable;
  *(undefined8 *)(param_1 + 0x140) = 0;
  return param_1;
}


// ==== FUN_1400031f0 @ 1400031f0  undefined FUN_1400031f0(CWinApp * param_1)

void FUN_1400031f0(CWinApp *param_1)

{
  CWinApp::~CWinApp(param_1);
  return;
}


// ==== FUN_140003210 @ 140003210  undefined FUN_140003210(void)

void FUN_140003210(void)

{
  char *local_18 [3];
  
  local_18[0] = "Invalid parameter!";
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_18,(ThrowInfo *)&DAT_1400fec90);
}


// ==== FUN_140003240 @ 140003240  undefined FUN_140003240(void)

void FUN_140003240(void)

{
  char *local_res8 [4];
  
  local_res8[0] = "pure call handler!";
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_res8,(ThrowInfo *)&DAT_1400fec90);
}


// ==== FUN_1400032c0 @ 1400032c0  undefined FUN_1400032c0(CSyncObject * param_1)

void FUN_1400032c0(CSyncObject *param_1)

{
  *(undefined ***)param_1 = CCriticalSection::vftable;
  DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x10));
  CSyncObject::~CSyncObject(param_1);
  return;
}


// ==== FUN_140003310 @ 140003310  undefined8 FUN_140003310(longlong param_1)

undefined8 FUN_140003310(longlong param_1)

{
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x10));
  return 1;
}


// ==== FUN_1400033d0 @ 1400033d0  undefined FUN_1400033d0(CDialog * param_1)

void FUN_1400033d0(CDialog *param_1)

{
  FUN_1400021f0((CThreadBase *)(param_1 + 0x238));
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
  ~CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0x220));
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
  ~CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0x1e0));
  *(undefined ***)(param_1 + 0x1a8) = CCriticalSection::vftable;
  DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x1b8));
  CSyncObject::~CSyncObject((CSyncObject *)(param_1 + 0x1a8));
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
  ~CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0x1a0));
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
  ~CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0x198));
  CEdit::~CEdit((CEdit *)(param_1 + 0xf0));
  CDialog::~CDialog(param_1);
  return;
}


// ==== FUN_140003480 @ 140003480  undefined FUN_140003480(undefined8 * param_1, undefined8 param_2, longlong param_3)

void FUN_140003480(undefined8 *param_1,undefined8 param_2,longlong param_3)

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


// ==== FUN_140003510 @ 140003510  undefined FUN_140003510(longlong param_1)

void FUN_140003510(longlong param_1)

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


// ==== FUN_140003840 @ 140003840  undefined FUN_140003840(undefined8 * param_1)

void FUN_140003840(undefined8 *param_1)

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


// ==== FUN_1400038d0 @ 1400038d0  undefined8 * FUN_1400038d0(undefined8 * param_1)

undefined8 * FUN_1400038d0(undefined8 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_140003840(param_1);
  return param_1;
}


// ==== FUN_1400038f0 @ 1400038f0  undefined FUN_1400038f0(longlong param_1)

void FUN_1400038f0(longlong param_1)

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


// ==== FUN_140003940 @ 140003940  undefined FUN_140003940(void)

void FUN_140003940(void)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = DAT_140103c78;
  if (DAT_140103c78 != (longlong *)0x0) {
    LOCK();
    plVar1 = DAT_140103c78 + 2;
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
    DAT_140103c78 = (longlong *)0x0;
    DAT_140103c70 = 0;
    return;
  }
  DAT_140103c78 = (longlong *)0x0;
  DAT_140103c70 = 0;
  return;
}


// ==== FUN_1400039f0 @ 1400039f0  CDialog * FUN_1400039f0(CDialog * param_1)

CDialog * FUN_1400039f0(CDialog *param_1)

{
  CDialog::CDialog(param_1,100,(CWnd *)0x0);
  *(undefined ***)param_1 = CAboutDlg::vftable;
  return param_1;
}


// ==== FUN_140003a30 @ 140003a30  undefined FUN_140003a30(CDialog * param_1)

void FUN_140003a30(CDialog *param_1)

{
  CDialog::~CDialog(param_1);
  return;
}


// ==== FUN_140003a80 @ 140003a80  undefined FUN_140003a80(void)

void FUN_140003a80(void)

{
  IAnalyst *pIVar1;
  
  pIVar1 = Analyst();
  (**(code **)(*(longlong *)pIVar1 + 8))(pIVar1,"syslog/npcanalyst");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x3c,1,"CLogThread OnProcess");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x3d,1,"`-CLogThread ProcessMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x4c,1,"CKernelThread::OnProcess");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x4d,1,"|-READMSG");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x4e,1,"| |-CNpcWorld::ProcessMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x4f,1,"|-EVENTMSG");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x50,1,"`-CNpcWorld::OnTimer");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x51,1,"  `-NpcManager::OnTimer");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x52,1,"    |-CNpcGenerator::DoGenerator");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x53,1,"    | `-CNpcGenerator::Generator");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x54,1,"    `-CNpc::OnTimer");
  pIVar1 = Analyst();
                    /* WARNING: Could not recover jumptable at 0x000140003c10. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x55,1,"CNpcWorld::SendMsg");
  return;
}


// ==== FUN_140003c20 @ 140003c20  undefined FUN_140003c20(longlong param_1)

void FUN_140003c20(longlong param_1)

{
  uint uVar1;
  undefined1 auStack_1a8 [32];
  undefined1 local_188 [344];
  int local_30;
  int local_2c;
  uint local_28;
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_1a8;
  memcpy(local_188,&DAT_140103dd0,0x168);
  memset(&DAT_140103dd0,0,0x168);
  if (local_30 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = local_2c / local_30;
  }
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::Format
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0x1a0),"kernel(ms): %d/%ld",(ulonglong)uVar1,(ulonglong)local_28);
  __security_check_cookie(local_18 ^ (ulonglong)auStack_1a8);
  return;
}


// ==== FUN_140003d00 @ 140003d00  undefined FUN_140003d00(longlong * param_1)

void FUN_140003d00(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
    *param_1 = 0;
  }
  return;
}


// ==== FUN_140003d30 @ 140003d30  undefined FUN_140003d30(longlong * param_1)

void FUN_140003d30(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
    *param_1 = 0;
  }
  return;
}


// ==== FUN_140003d60 @ 140003d60  undefined8 FUN_140003d60(void)

undefined8 FUN_140003d60(void)

{
  AFX_MODULE_STATE *pAVar1;
  
  pAVar1 = AfxGetModuleState();
  return *(undefined8 *)(pAVar1 + 8);
}


// ==== FUN_140003d80 @ 140003d80  undefined8 FUN_140003d80(void)

undefined8 FUN_140003d80(void)

{
  AFX_MODULE_STATE *pAVar1;
  
  pAVar1 = AfxGetModuleState();
  return *(undefined8 *)(pAVar1 + 0x20);
}


// ==== FUN_140003e00 @ 140003e00  undefined FUN_140003e00(longlong param_1, BOOL param_2)

void FUN_140003e00(longlong param_1,BOOL param_2)

{
  HMENU pHVar1;
  
  pHVar1 = GetSystemMenu(*(HWND *)(param_1 + 0x40),param_2);
  CMenu::FromHandle(pHVar1);
  return;
}


// ==== FUN_140003ee0 @ 140003ee0  CWnd * FUN_140003ee0(CWnd * param_1)

CWnd * FUN_140003ee0(CWnd *param_1)

{
  CWnd::CWnd(param_1);
  *(undefined ***)param_1 = CEdit::vftable;
  return param_1;
}


// ==== FUN_140003ff0 @ 140003ff0  undefined FUN_140003ff0(undefined8 param_1, ushort param_2)

void FUN_140003ff0(undefined8 param_1,ushort param_2)

{
  HINSTANCE__ *hInstance;
  
  hInstance = AfxFindResourceHandle((char *)(ulonglong)param_2,(char *)0xe);
                    /* WARNING: Could not recover jumptable at 0x000140004011. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LoadIconA(hInstance,(char *)(ulonglong)param_2);
  return;
}


// ==== FUN_140004110 @ 140004110  CDialog * FUN_140004110(CDialog * param_1, CWnd * param_2)

CDialog * FUN_140004110(CDialog *param_1,CWnd *param_2)

{
  CSyncObject *this;
  int iVar1;
  HINSTANCE__ *hInstance;
  HICON pHVar2;
  
  CDialog::CDialog(param_1,0x66,param_2);
  *(undefined ***)param_1 = CNpcServerDlg::vftable;
  *(undefined ***)(param_1 + 0xe8) = CNpcServerDlg::vftable;
  CWnd::CWnd((CWnd *)(param_1 + 0xf0));
  *(undefined ***)(param_1 + 0xf0) = CEdit::vftable;
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
  CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0x198));
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
  CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0x1a0));
  this = (CSyncObject *)(param_1 + 0x1a8);
  CSyncObject::CSyncObject(this,(char *)0x0);
  *(undefined ***)this = CCriticalSection::vftable;
  iVar1 = CCriticalSection::Init((CCriticalSection *)this);
  if (iVar1 == 0) {
    AfxThrowMemoryException();
  }
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
  CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0x1e0));
  *(undefined4 *)(param_1 + 0x1f0) = 0;
  *(undefined4 *)(param_1 + 500) = 0;
  *(undefined4 *)(param_1 + 0x1f8) = 0;
  *(undefined4 *)(param_1 + 0x1fc) = 0;
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
  CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0x220));
  FUN_140002790((CThreadBase *)(param_1 + 0x238));
  *(undefined4 *)(param_1 + 0x2d8) = 0;
  *(undefined4 *)(param_1 + 0x2dc) = 0;
  *(undefined4 *)(param_1 + 0x2e0) = 0;
  *(undefined4 *)(param_1 + 0x2e4) = 0;
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::operator=
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0x198),"");
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::operator=
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0x1a0),"");
  AfxGetModuleState();
  hInstance = AfxFindResourceHandle((char *)0x80,(char *)0xe);
  pHVar2 = LoadIconA(hInstance,(LPCSTR)0x80);
  *(HICON *)(param_1 + 0x2c8) = pHVar2;
  *(undefined4 *)(param_1 + 0x2c0) = 0;
  param_1[0x210] = (CDialog)0x0;
  *(undefined4 *)(param_1 + 0x228) = 0;
  *(undefined8 *)(param_1 + 0x1e8) = 0;
  *(undefined8 *)(param_1 + 0x2d0) = 0;
  *(undefined8 *)(param_1 + 0x2b8) = 0;
  *(undefined8 *)(param_1 + 0x200) = 0;
  *(undefined8 *)(param_1 + 0x208) = 0;
  return param_1;
}


// ==== FUN_140004310 @ 140004310  undefined FUN_140004310(CWnd * param_1, uint param_2)

void FUN_140004310(CWnd *param_1,uint param_2)

{
  undefined **local_f8 [31];
  
  if ((param_2 & 0xfff0) == 0x10) {
    CDialog::CDialog((CDialog *)local_f8,100,(CWnd *)0x0);
    local_f8[0] = CAboutDlg::vftable;
    CDialog::DoModal((CDialog *)local_f8);
    CDialog::~CDialog((CDialog *)local_f8);
  }
  else if ((param_2 & 0xfff0) == 0xf060) {
    PostMessageA(*(HWND *)(param_1 + 0x40),0x111,2,0);
  }
  else {
    CWnd::Default(param_1);
  }
  return;
}


// ==== FUN_140004390 @ 140004390  undefined FUN_140004390(CDialog * param_1)

void FUN_140004390(CDialog *param_1)

{
  BOOL BVar1;
  int iVar2;
  int iVar3;
  undefined1 auStack_c8 [32];
  tagRECT local_a8;
  undefined8 local_98;
  CPaintDC local_88 [8];
  HDC local_80;
  ulonglong local_18;
  
  local_98 = 0xfffffffffffffffe;
  local_18 = DAT_140103510 ^ (ulonglong)auStack_c8;
  BVar1 = IsIconic(*(HWND *)(param_1 + 0x40));
  if (BVar1 == 0) {
    CDialog::OnPaint(param_1);
  }
  else {
    CPaintDC::CPaintDC(local_88,(CWnd *)param_1);
    SendMessageA(*(HWND *)(param_1 + 0x40),0x27,(WPARAM)local_80,0);
    iVar2 = GetSystemMetrics(0xb);
    iVar3 = GetSystemMetrics(0xc);
    GetClientRect(*(HWND *)(param_1 + 0x40),&local_a8);
    DrawIcon(local_80,(((local_a8.right - local_a8.left) - iVar2) + 1) / 2,
             (((local_a8.bottom - local_a8.top) - iVar3) + 1) / 2,*(HICON *)(param_1 + 0x2c8));
    CPaintDC::~CPaintDC(local_88);
  }
  __security_check_cookie(local_18 ^ (ulonglong)auStack_c8);
  return;
}


// ==== FUN_1400046b0 @ 1400046b0  undefined FUN_1400046b0(CWnd * param_1)

void FUN_1400046b0(CWnd *param_1)

{
  bool bVar1;
  LRESULT LVar2;
  char *lParam;
  CSingleLock local_20 [24];
  
  bVar1 = ATL::CSimpleStringT<char,1>::IsEmpty((CSimpleStringT<char,1> *)(param_1 + 0x1e0));
  if (!bVar1) {
    CSingleLock::CSingleLock(local_20,(CSyncObject *)(param_1 + 0x1a8),1);
    LVar2 = SendMessageA(*(HWND *)(param_1 + 0x130),0xba,0,0);
    if (500 < (int)LVar2) {
      LVar2 = SendMessageA(*(HWND *)(param_1 + 0x130),0xbb,0xfa,0);
      SendMessageA(*(HWND *)(param_1 + 0x130),0xb1,0,(longlong)(int)LVar2);
      SendMessageA(*(HWND *)(param_1 + 0x130),0xc2,0,0x1400bfaf8);
    }
    SendMessageA(*(HWND *)(param_1 + 0x130),0xb1,0x7fffffff,0x7fffffff);
    lParam = ATL::CSimpleStringT<char,1>::operator_char_const____ptr64
                       ((CSimpleStringT<char,1> *)(param_1 + 0x1e0));
    SendMessageA(*(HWND *)(param_1 + 0x130),0xc2,0,(LPARAM)lParam);
    CWnd::UpdateData(param_1,0);
    ATL::CSimpleStringT<char,1>::Empty((CSimpleStringT<char,1> *)(param_1 + 0x1e0));
    CSingleLock::Unlock(local_20);
  }
  return;
}


// ==== FUN_1400047d0 @ 1400047d0  undefined FUN_1400047d0(CWnd * param_1)

void FUN_1400047d0(CWnd *param_1)

{
  HWND hWnd;
  char *lpString;
  CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> local_res8 [32];
  undefined8 uVar1;
  
  uVar1 = 0xfffffffffffffffe;
  CWnd::OnDestroy(param_1);
  CloseHandle(*(HANDLE *)(param_1 + 0x2d0));
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
  CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>(local_res8);
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::Format
            (local_res8,"%s - %s","Conquer Online NPC Server",param_1 + 0x200,uVar1);
  hWnd = *(HWND *)(param_1 + 0x40);
  lpString = ATL::CSimpleStringT<char,1>::operator_char_const____ptr64
                       ((CSimpleStringT<char,1> *)local_res8);
  RemovePropA(hWnd,lpString);
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
  ~CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>(local_res8);
  return;
}


// ==== FUN_140004850 @ 140004850  ulonglong FUN_140004850(int * param_1)

ulonglong FUN_140004850(int *param_1)

{
  ulong uVar1;
  ulonglong in_RAX;
  
  if (param_1[1] != 0) {
    uVar1 = tq::TimeGet(0);
    in_RAX = (ulonglong)(uint)(*param_1 + param_1[1]);
    if ((uint)(*param_1 + param_1[1]) <= uVar1 / 1000) {
      param_1[1] = 0;
      *param_1 = 0;
      return 1;
    }
  }
  return in_RAX & 0xffffffffffffff00;
}


// ==== FUN_140004d00 @ 140004d00  undefined FUN_140004d00(CWnd * param_1, longlong param_2, undefined8 param_3, undefined8 param_4)

void FUN_140004d00(CWnd *param_1,longlong param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  undefined8 *puVar2;
  bool bVar3;
  DWORD DVar4;
  ulong uVar5;
  AFX_MODULE_STATE *pAVar6;
  IAnalyst *pIVar7;
  ulonglong uVar8;
  char *pcVar9;
  CThreadBase *pCVar10;
  undefined8 uVar11;
  CThreadBase *pCVar12;
  CAsyncDBThread *this;
  longlong *plVar13;
  void *pvVar14;
  CAsyncDBThread *this_00;
  CSingleLock local_20 [24];
  
  if ((DAT_140103f3c == 0) &&
     (DVar4 = WaitForSingleObject(*(HANDLE *)(param_1 + 0x2d0),0), DVar4 == 0)) {
    DAT_140103f3c = 1;
    *(undefined4 *)(param_1 + 0x2e0) = 0x32;
    uVar5 = tq::TimeGet(0);
    *(uint *)(param_1 + 0x2e4) = uVar5 / 1000;
  }
  else if ((*(int *)(param_1 + 0x2e4) != 0) &&
          (uVar5 = tq::TimeGet(0),
          (uint)(*(int *)(param_1 + 0x2e4) + *(int *)(param_1 + 0x2e0)) <= uVar5 / 1000)) {
    *(undefined4 *)(param_1 + 0x2e4) = 0;
    *(undefined4 *)(param_1 + 0x2e0) = 0;
    *(undefined4 *)(param_1 + 0x2c0) = 3;
  }
  this_00 = (CAsyncDBThread *)0x0;
  if (param_2 == 1) {
    iVar1 = *(int *)(param_1 + 0x2c0);
    if (iVar1 == 1) {
      *(undefined4 *)(param_1 + 0x2c0) = 2;
      FUN_140003a80();
      *(undefined4 *)(param_1 + 0x2d8) = 300;
      uVar5 = tq::TimeGet(0);
      *(uint *)(param_1 + 0x2dc) = uVar5 / 1000;
      pCVar10 = (CThreadBase *)operator_new(0xd0);
      pCVar12 = (CThreadBase *)this_00;
      if (pCVar10 != (CThreadBase *)0x0) {
        uVar11 = FUN_14006e9b0(0);
        pCVar12 = FUN_140002d70(pCVar10,uVar11,"syslog/npcserver");
      }
      *(CThreadBase **)(param_1 + 0x230) = pCVar12;
      if (pCVar12 == (CThreadBase *)0x0) {
        (*(code *)**(undefined8 **)(param_1 + 0xe8))(param_1 + 0xe8,"Cannot log thread");
        FUN_1400046b0(param_1);
        *(undefined4 *)(param_1 + 0x2c0) = 3;
      }
      else {
        bVar3 = FUN_140002e20(pCVar12,true);
        if (bVar3) {
          tq::SetLogThreadStatus(1);
          DatabaseInit();
          this = (CAsyncDBThread *)operator_new(0x40);
          if (this != (CAsyncDBThread *)0x0) {
            CAsyncDBThread::CAsyncDBThread(this);
            *(undefined ***)this = CAsyncDBThread::vftable;
            this_00 = this;
          }
          *(CAsyncDBThread **)(param_1 + 0x2b8) = this_00;
          if (this_00 == (CAsyncDBThread *)0x0) {
            (*(code *)**(undefined8 **)(param_1 + 0xe8))
                      (param_1 + 0xe8,"Cannot new async DB thread");
            FUN_1400046b0(param_1);
            *(undefined4 *)(param_1 + 0x2c0) = 3;
          }
          else {
            bVar3 = CThreadBase::CreateThread((CThreadBase *)this_00,"AsyncDBThread",true);
            if (bVar3) {
              plVar13 = (longlong *)FUN_14006e9b0(1);
              pvVar14 = FUN_140002b30((CThreadBase *)(param_1 + 0x238),(longlong)(param_1 + 0xe8),
                                      plVar13,(undefined8 *)
                                              CONCAT71((int7)((ulonglong)param_4 >> 8),1));
              if ((char)pvVar14 == '\0') {
                (*(code *)**(undefined8 **)(param_1 + 0xe8))
                          (param_1 + 0xe8,"Can\'t create kernel thread!");
                FUN_1400046b0(param_1);
                *(undefined4 *)(param_1 + 0x2c0) = 3;
              }
              else {
                (*(code *)**(undefined8 **)(param_1 + 0xe8))
                          (param_1 + 0xe8,"Create kernel thread ok.");
                FUN_1400046b0(param_1);
              }
            }
            else {
              if (*(longlong *)(param_1 + 0x2b8) != 0) {
                puVar2 = *(undefined8 **)(param_1 + 0x2b8);
                if (puVar2 != (undefined8 *)0x0) {
                  (**(code **)*puVar2)(puVar2,1);
                }
                *(undefined8 *)(param_1 + 0x2b8) = 0;
              }
              (*(code *)**(undefined8 **)(param_1 + 0xe8))
                        (param_1 + 0xe8,"Cannot create async DB thread");
              FUN_1400046b0(param_1);
              *(undefined4 *)(param_1 + 0x2c0) = 3;
            }
          }
        }
        else {
          if (*(longlong *)(param_1 + 0x230) != 0) {
            puVar2 = *(undefined8 **)(param_1 + 0x230);
            if (puVar2 != (undefined8 *)0x0) {
              (**(code **)*puVar2)(puVar2,1);
            }
            *(undefined8 *)(param_1 + 0x230) = 0;
          }
          (*(code *)**(undefined8 **)(param_1 + 0xe8))(param_1 + 0xe8,"Cannot create log thread");
          FUN_1400046b0(param_1);
          *(undefined4 *)(param_1 + 0x2c0) = 3;
        }
      }
    }
    else if (iVar1 == 2) {
      bVar3 = ATL::CSimpleStringT<char,1>::IsEmpty((CSimpleStringT<char,1> *)(param_1 + 0x1e0));
      if (!bVar3) {
        FUN_1400046b0(param_1);
      }
      uVar8 = FUN_140002700((int *)(param_1 + 0x1f0));
      if ((char)uVar8 != '\0') {
        FUN_140003c20((longlong)param_1);
        uVar8 = FUN_140002700((int *)(param_1 + 0x1f8));
        if ((char)uVar8 != '\0') {
          pcVar9 = ATL::CSimpleStringT<char,1>::operator_char_const____ptr64
                             ((CSimpleStringT<char,1> *)(param_1 + 0x1a0));
          log_InlineLogMessage(pcVar9);
          pcVar9 = ATL::CSimpleStringT<char,1>::operator_char_const____ptr64
                             ((CSimpleStringT<char,1> *)(param_1 + 0x198));
          log_InlineLogMessage(pcVar9);
        }
        CSingleLock::CSingleLock(local_20,(CSyncObject *)(param_1 + 0x1a8),1);
        CWnd::UpdateData(param_1,0);
        CSingleLock::Unlock(local_20);
      }
      if (DAT_140103f38 != 0) {
        *(undefined4 *)(param_1 + 0x2c0) = 3;
      }
      uVar8 = FUN_140002700((int *)(param_1 + 0x2d8));
      if ((char)uVar8 != '\0') {
        pIVar7 = Analyst();
        (**(code **)(*(longlong *)pIVar7 + 0x30))(pIVar7,"syslog/npcanalyst");
        pIVar7 = Analyst();
        (**(code **)(*(longlong *)pIVar7 + 0x28))(pIVar7);
      }
    }
    else if (iVar1 == 3) {
      bVar3 = CThreadBase::CloseThread((CThreadBase *)(param_1 + 0x238),60000);
      if (bVar3) {
        (*(code *)**(undefined8 **)(param_1 + 0xe8))(param_1 + 0xe8,"Close kernel thread ok.");
        FUN_1400046b0(param_1);
        if (*(HANDLE *)(param_1 + 0x1e8) != (HANDLE)0x0) {
          CloseHandle(*(HANDLE *)(param_1 + 0x1e8));
          ReleaseMutex(*(HANDLE *)(param_1 + 0x1e8));
          *(undefined8 *)(param_1 + 0x1e8) = 0;
        }
        *(undefined4 *)(param_1 + 0x2c0) = 4;
      }
      else {
        (*(code *)**(undefined8 **)(param_1 + 0xe8))(param_1 + 0xe8,&DAT_1400c0260);
        FUN_1400046b0(param_1);
      }
    }
    else if (iVar1 == 4) {
      KillTimer(*(HWND *)(param_1 + 0x40),1);
      *(undefined4 *)(param_1 + 0x2c0) = 0;
      Sleep(1000);
      if (DAT_140103f38 != 0) {
        pAVar6 = AfxGetModuleState();
        ShellExecuteA(*(HWND *)(param_1 + 0x40),(LPCSTR)0x0,*(LPCSTR *)(pAVar6 + 0x20),(LPCSTR)0x0,
                      (LPCSTR)0x0,1);
      }
      if (*(CThreadBase **)(param_1 + 0x2b8) != (CThreadBase *)0x0) {
        bVar3 = CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x2b8),2000);
        if (bVar3) {
          (*(code *)**(undefined8 **)(param_1 + 0xe8))(param_1 + 0xe8,"Close async DB thread OK");
        }
        else {
          (*(code *)**(undefined8 **)(param_1 + 0xe8))
                    (param_1 + 0xe8,"Close async DB thread failed");
        }
        FUN_1400046b0(param_1);
        if (*(longlong *)(param_1 + 0x2b8) != 0) {
          puVar2 = *(undefined8 **)(param_1 + 0x2b8);
          if (puVar2 != (undefined8 *)0x0) {
            (**(code **)*puVar2)(puVar2,1);
          }
          *(undefined8 *)(param_1 + 0x2b8) = 0;
        }
      }
      DatabaseUnInit();
      pIVar7 = Analyst();
      (**(code **)(*(longlong *)pIVar7 + 0x30))(pIVar7,"syslog/npcanalyst");
      pIVar7 = Analyst();
      (**(code **)(*(longlong *)pIVar7 + 0x28))(pIVar7);
      CDialog::OnCancel((CDialog *)param_1);
      tq::SetLogThreadStatus(0);
      if (*(CThreadBase **)(param_1 + 0x230) != (CThreadBase *)0x0) {
        bVar3 = CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x230),60000);
        if (bVar3) {
          (*(code *)**(undefined8 **)(param_1 + 0xe8))(param_1 + 0xe8,"Close log thread OK");
        }
        else {
          (*(code *)**(undefined8 **)(param_1 + 0xe8))(param_1 + 0xe8,"Close log thread failed");
        }
        FUN_1400046b0(param_1);
        if (*(longlong *)(param_1 + 0x230) != 0) {
          puVar2 = *(undefined8 **)(param_1 + 0x230);
          if (puVar2 != (undefined8 *)0x0) {
            (**(code **)*puVar2)(puVar2,1);
          }
          *(undefined8 *)(param_1 + 0x230) = 0;
        }
      }
      FUN_140070f30();
    }
  }
  CWnd::Default(param_1);
  return;
}


// ==== FUN_140005400 @ 140005400  LPCRITICAL_SECTION FUN_140005400(void)

LPCRITICAL_SECTION FUN_140005400(void)

{
  BOOL BVar1;
  LPCRITICAL_SECTION lpCriticalSection;
  
  lpCriticalSection = (LPCRITICAL_SECTION)FUN_140011830(0x28);
  if (lpCriticalSection != (LPCRITICAL_SECTION)0x0) {
    BVar1 = InitializeCriticalSectionAndSpinCount(lpCriticalSection,2000);
    if (BVar1 != 0) {
      return lpCriticalSection;
    }
    FUN_1400119c0(lpCriticalSection);
  }
  return (LPCRITICAL_SECTION)0x0;
}


// ==== FUN_140005450 @ 140005450  undefined FUN_140005450(LPCRITICAL_SECTION param_1)

void FUN_140005450(LPCRITICAL_SECTION param_1)

{
  DeleteCriticalSection(param_1);
  FUN_1400119c0(param_1);
  return;
}


// ==== FUN_140005470 @ 140005470  bool FUN_140005470(ulonglong param_1, LPCRITICAL_SECTION param_2)

bool FUN_140005470(ulonglong param_1,LPCRITICAL_SECTION param_2)

{
  BOOL BVar1;
  
  if ((param_1 & 0x10) != 0) {
    BVar1 = TryEnterCriticalSection(param_2);
    return BVar1 == 0;
  }
  EnterCriticalSection(param_2);
  return false;
}


// ==== FUN_1400054a0 @ 1400054a0  undefined8 FUN_1400054a0(undefined8 param_1, LPCRITICAL_SECTION param_2)

undefined8 FUN_1400054a0(undefined8 param_1,LPCRITICAL_SECTION param_2)

{
  LeaveCriticalSection(param_2);
  return 0;
}


// ==== FUN_1400054d0 @ 1400054d0  undefined8 * FUN_1400054d0(void)

undefined8 * FUN_1400054d0(void)

{
  BOOL BVar1;
  undefined8 *puVar2;
  HANDLE pvVar3;
  
  puVar2 = (undefined8 *)FUN_140011830(0x40);
  if (puVar2 == (undefined8 *)0x0) {
    return (undefined8 *)0x0;
  }
  BVar1 = InitializeCriticalSectionAndSpinCount((LPCRITICAL_SECTION)(puVar2 + 1),2000);
  if (BVar1 != 0) {
    pvVar3 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,1,0,(LPCSTR)0x0);
    *puVar2 = pvVar3;
    if (pvVar3 != (HANDLE)0x0) {
      *(undefined4 *)(puVar2 + 7) = 0;
      *(undefined4 *)((longlong)puVar2 + 0x34) = 0;
      *(undefined4 *)(puVar2 + 6) = 0;
      return puVar2;
    }
    DeleteCriticalSection((LPCRITICAL_SECTION)(puVar2 + 1));
  }
  FUN_1400119c0(puVar2);
  return (undefined8 *)0x0;
}


// ==== FUN_140005560 @ 140005560  undefined FUN_140005560(undefined8 * param_1)

void FUN_140005560(undefined8 *param_1)

{
  DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
  CloseHandle((HANDLE)*param_1);
  FUN_1400119c0(param_1);
  return;
}


// ==== FUN_140005590 @ 140005590  undefined8 FUN_140005590(undefined8 * param_1, int param_2)

undefined8 FUN_140005590(undefined8 *param_1,int param_2)

{
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
  if (param_2 == 0) {
    *(int *)((longlong)param_1 + 0x34) = *(int *)((longlong)param_1 + 0x34) + 1;
  }
  else {
    *(undefined4 *)((longlong)param_1 + 0x34) = *(undefined4 *)(param_1 + 6);
  }
  *(int *)(param_1 + 7) = *(int *)(param_1 + 7) + 1;
  SetEvent((HANDLE)*param_1);
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
  return 0;
}


// ==== FUN_1400055f0 @ 1400055f0  undefined4 FUN_1400055f0(undefined8 * param_1, LPCRITICAL_SECTION param_2, int * param_3)

undefined4 FUN_1400055f0(undefined8 *param_1,LPCRITICAL_SECTION param_2,int *param_3)

{
  int iVar1;
  bool bVar2;
  DWORD DVar3;
  DWORD DVar4;
  undefined4 uVar5;
  DWORD dwMilliseconds;
  DWORD DVar6;
  
  uVar5 = 0xffffffff;
  DVar6 = 0xffffffff;
  bVar2 = true;
  if (param_3 != (int *)0x0) {
    DVar6 = FUN_140016450(param_3);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
  iVar1 = *(int *)(param_1 + 7);
  *(int *)(param_1 + 6) = *(int *)(param_1 + 6) + 1;
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
  LeaveCriticalSection(param_2);
  DVar3 = GetTickCount();
  dwMilliseconds = DVar6;
  do {
    DVar4 = WaitForSingleObject((HANDLE)*param_1,dwMilliseconds);
    EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
    if ((*(int *)((longlong)param_1 + 0x34) == 0) || (*(int *)(param_1 + 7) == iVar1)) {
      if (DVar4 == 0) {
        if (dwMilliseconds != 0xffffffff) {
          DVar4 = GetTickCount();
          if (DVar3 + DVar6 <= DVar4) {
            *(int *)(param_1 + 6) = *(int *)(param_1 + 6) + -1;
            uVar5 = 1;
            bVar2 = false;
            goto LAB_1400056ef;
          }
          dwMilliseconds = (DVar3 - DVar4) + DVar6;
        }
        if (*(int *)((longlong)param_1 + 0x34) == 0) {
          ResetEvent((HANDLE)*param_1);
        }
      }
      else {
        uVar5 = 0xffffffff;
        if (DVar4 == 0x102) {
          uVar5 = 1;
        }
        *(int *)(param_1 + 6) = *(int *)(param_1 + 6) + -1;
        bVar2 = false;
      }
    }
    else {
      *(int *)(param_1 + 6) = *(int *)(param_1 + 6) + -1;
      uVar5 = 0;
      *(int *)((longlong)param_1 + 0x34) = *(int *)((longlong)param_1 + 0x34) + -1;
      bVar2 = false;
    }
LAB_1400056ef:
    LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
    if (!bVar2) {
      EnterCriticalSection(param_2);
      EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
      if (*(int *)(param_1 + 6) == 0) {
        ResetEvent((HANDLE)*param_1);
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
      return uVar5;
    }
  } while( true );
}


// ==== FUN_140005750 @ 140005750  undefined8 FUN_140005750(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

undefined8
FUN_140005750(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  int local_58 [2];
  code *local_50;
  code *local_48;
  code *local_40;
  code *local_38;
  int local_30 [2];
  code *local_28;
  code *local_20;
  code *local_18;
  code *local_10;
  
  local_58[0] = 1;
  local_58[1] = 1;
  local_30[0] = 1;
  local_50 = FUN_140005400;
  local_48 = FUN_140005450;
  local_40 = FUN_140005470;
  local_38 = FUN_1400054a0;
  local_28 = FUN_1400054d0;
  local_20 = FUN_140005560;
  local_18 = FUN_140005590;
  local_10 = FUN_1400055f0;
  FUN_140016890(local_58,param_2,param_3,param_4);
  FUN_140016880(&DAT_1400054c0);
  FUN_140016990(local_30,param_2,param_3,param_4);
  return 0;
}


// ==== FUN_1400057f0 @ 1400057f0  undefined FUN_1400057f0(longlong param_1, ushort param_2)

void FUN_1400057f0(longlong param_1,ushort param_2)

{
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  if (*(short *)(param_1 + 0x176) == 0) {
    (**(code **)(*(longlong *)(param_1 + 8) + 0x18))(param_1,2);
  }
  *(ushort *)(param_1 + 0x176) = *(ushort *)(param_1 + 0x176) | param_2;
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_140005860 @ 140005860  undefined FUN_140005860(longlong param_1, ushort param_2)

void FUN_140005860(longlong param_1,ushort param_2)

{
  ushort *puVar1;
  
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  puVar1 = (ushort *)(param_1 + 0x176);
  *puVar1 = *puVar1 & ~param_2;
  if ((*puVar1 == 0) && ((*(byte *)(param_1 + 0x160) & 2) != 0)) {
    (**(code **)(*(longlong *)(param_1 + 8) + 0x10))(param_1,2);
  }
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_1400058d0 @ 1400058d0  undefined FUN_1400058d0(longlong param_1, ushort param_2)

void FUN_1400058d0(longlong param_1,ushort param_2)

{
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  if (*(short *)(param_1 + 0x178) == 0) {
    (**(code **)(*(longlong *)(param_1 + 8) + 0x18))(param_1,4);
  }
  *(ushort *)(param_1 + 0x178) = *(ushort *)(param_1 + 0x178) | param_2;
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_140005940 @ 140005940  undefined FUN_140005940(longlong param_1, ushort param_2)

void FUN_140005940(longlong param_1,ushort param_2)

{
  ushort *puVar1;
  
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  puVar1 = (ushort *)(param_1 + 0x178);
  *puVar1 = *puVar1 & ~param_2;
  if ((*puVar1 == 0) && ((*(byte *)(param_1 + 0x160) & 4) != 0)) {
    (**(code **)(*(longlong *)(param_1 + 8) + 0x10))(param_1,4);
  }
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_1400059b0 @ 1400059b0  undefined FUN_1400059b0(longlong param_1, undefined8 param_2, longlong param_3)

void FUN_1400059b0(longlong param_1,undefined8 param_2,longlong param_3)

{
  ushort *puVar1;
  ulonglong uVar2;
  
  uVar2 = FUN_14000c370(param_1);
  if (uVar2 < *(ulonglong *)(param_3 + 0x118)) {
    if (*(longlong *)(param_3 + 0x1b8) != 0) {
      FUN_140016e30();
    }
    puVar1 = (ushort *)(param_3 + 0x176);
    *puVar1 = *puVar1 & 0xfffe;
    if ((*puVar1 == 0) && ((*(byte *)(param_3 + 0x160) & 2) != 0)) {
      (**(code **)(*(longlong *)(param_3 + 8) + 0x10))(param_3,2);
    }
  }
  else {
    if (*(longlong *)(param_3 + 0x1b8) != 0) {
      FUN_140016e30();
    }
    if (*(short *)(param_3 + 0x176) == 0) {
      (**(code **)(*(longlong *)(param_3 + 8) + 0x18))(param_3,2);
    }
    *(ushort *)(param_3 + 0x176) = *(ushort *)(param_3 + 0x176) | 1;
  }
  if (*(longlong *)(param_3 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_140005a50 @ 140005a50  undefined FUN_140005a50(longlong param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, undefined8 param_5)

void FUN_140005a50(longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                  undefined8 param_5)

{
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  *(undefined8 *)(param_1 + 0x130) = param_2;
  *(undefined8 *)(param_1 + 0x138) = param_3;
  *(undefined8 *)(param_1 + 0x140) = param_4;
  *(undefined8 *)(param_1 + 0x148) = param_5;
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_140005ad0 @ 140005ad0  undefined FUN_140005ad0(longlong param_1, undefined8 * param_2, undefined8 * param_3, undefined8 * param_4, undefined8 * param_5)

void FUN_140005ad0(longlong param_1,undefined8 *param_2,undefined8 *param_3,undefined8 *param_4,
                  undefined8 *param_5)

{
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  if (param_2 != (undefined8 *)0x0) {
    *param_2 = *(undefined8 *)(param_1 + 0x130);
  }
  if (param_3 != (undefined8 *)0x0) {
    *param_3 = *(undefined8 *)(param_1 + 0x138);
  }
  if (param_4 != (undefined8 *)0x0) {
    *param_4 = *(undefined8 *)(param_1 + 0x140);
  }
  if (param_5 != (undefined8 *)0x0) {
    *param_5 = *(undefined8 *)(param_1 + 0x148);
  }
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_140005b70 @ 140005b70  undefined8 FUN_140005b70(longlong param_1)

undefined8 FUN_140005b70(longlong param_1)

{
  return *(undefined8 *)(param_1 + 0x100);
}


// ==== FUN_140005ba0 @ 140005ba0  uint FUN_140005ba0(longlong * param_1)

uint FUN_140005ba0(longlong *param_1)

{
  bool bVar1;
  undefined1 uVar2;
  int iVar3;
  undefined7 extraout_var;
  undefined7 extraout_var_00;
  
  bVar1 = FUN_1400110f0((longlong)(param_1 + 2));
  if ((int)CONCAT71(extraout_var,bVar1) != 0) {
    uVar2 = FUN_1400111b0((longlong)(param_1 + 2));
    return (uint)CONCAT71(extraout_var_00,uVar2);
  }
  iVar3 = FUN_140010a70(*param_1);
  return iVar3 / 2;
}


// ==== FUN_140005bf0 @ 140005bf0  int FUN_140005bf0(longlong param_1, void * param_2, ulonglong param_3)

int FUN_140005bf0(longlong param_1,void *param_2,ulonglong param_3)

{
  int iVar1;
  
  iVar1 = FUN_14000e6c0(*(longlong **)(param_1 + 0x108),param_2,param_3);
  return (iVar1 != -1) - 1;
}


// ==== FUN_140005c10 @ 140005c10  int FUN_140005c10(longlong param_1, longlong * param_2)

int FUN_140005c10(longlong param_1,longlong *param_2)

{
  undefined8 uVar1;
  
  uVar1 = FUN_14000de70(*(longlong **)(param_1 + 0x108),param_2);
  return ((int)uVar1 != -1) - 1;
}


// ==== FUN_140005c30 @ 140005c30  longlong FUN_140005c30(longlong param_1, void * param_2, ulonglong param_3)

longlong FUN_140005c30(longlong param_1,void *param_2,ulonglong param_3)

{
  ulonglong uVar1;
  
  uVar1 = FUN_14000e3e0(*(longlong **)(param_1 + 0x100),param_2,param_3);
  return (longlong)(int)uVar1;
}


// ==== FUN_140005c70 @ 140005c70  undefined4 FUN_140005c70(longlong param_1, undefined8 * param_2, undefined8 * param_3)

undefined4 FUN_140005c70(longlong param_1,undefined8 *param_2,undefined8 *param_3)

{
  code *pcVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  if (param_2 == (undefined8 *)0x0) {
    *(undefined4 *)(param_1 + 0x154) = 0;
    *(undefined4 *)(param_1 + 0x150) = 0;
  }
  else {
    *(undefined8 *)(param_1 + 0x150) = *param_2;
  }
  if (param_3 == (undefined8 *)0x0) {
    *(undefined4 *)(param_1 + 0x15c) = 0;
    *(undefined4 *)(param_1 + 0x158) = 0;
  }
  else {
    *(undefined8 *)(param_1 + 0x158) = *param_3;
  }
  pcVar1 = *(code **)(*(longlong *)(param_1 + 8) + 0x30);
  if (pcVar1 != (code *)0x0) {
    uVar2 = (*pcVar1)(param_1);
  }
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return uVar2;
}


// ==== FUN_140005d20 @ 140005d20  undefined FUN_140005d20(longlong param_1, uint param_2, uint param_3)

void FUN_140005d20(longlong param_1,uint param_2,uint param_3)

{
  ulonglong *puVar1;
  ulonglong *puVar2;
  ulonglong local_res20;
  ulonglong local_18 [3];
  
  puVar1 = (ulonglong *)0x0;
  local_res20 = 0;
  local_18[0] = 0;
  puVar2 = puVar1;
  if (param_2 != 0) {
    local_res20 = (ulonglong)param_2;
    puVar2 = &local_res20;
  }
  if (param_3 != 0) {
    local_18[0] = (ulonglong)param_3;
    puVar1 = local_18;
  }
  FUN_140005c70(param_1,puVar2,puVar1);
  return;
}


// ==== FUN_140005d70 @ 140005d70  undefined4 FUN_140005d70(longlong param_1, ushort param_2)

undefined4 FUN_140005d70(longlong param_1,ushort param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  *(uint *)(param_1 + 0x170) = *(uint *)(param_1 + 0x170) & 0xfffffff7;
  *(ushort *)(param_1 + 0x160) = *(ushort *)(param_1 + 0x160) & ~param_2;
  iVar1 = (**(code **)(*(longlong *)(param_1 + 8) + 0x18))(param_1,param_2);
  uVar2 = 0;
  if (iVar1 < 0) {
    uVar2 = 0xffffffff;
  }
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return uVar2;
}


// ==== FUN_140005df0 @ 140005df0  undefined4 FUN_140005df0(longlong param_1, ushort param_2)

undefined4 FUN_140005df0(longlong param_1,ushort param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  *(ushort *)(param_1 + 0x160) = *(ushort *)(param_1 + 0x160) & ~param_2;
  iVar1 = (**(code **)(*(longlong *)(param_1 + 8) + 0x18))(param_1,param_2);
  uVar2 = 0;
  if (iVar1 < 0) {
    uVar2 = 0xffffffff;
  }
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return uVar2;
}


// ==== FUN_140005e70 @ 140005e70  undefined FUN_140005e70(longlong param_1, ushort param_2, undefined8 param_3, ulonglong param_4)

void FUN_140005e70(longlong param_1,ushort param_2,undefined8 param_3,ulonglong param_4)

{
  longlong *plVar1;
  ulonglong uVar2;
  
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  if ((param_2 & 4) != 0) {
    *(undefined8 *)(param_1 + 0x120) = param_3;
    *(ulonglong *)(param_1 + 0x128) = param_4;
  }
  if ((param_2 & 2) == 0) goto LAB_140005f72;
  *(undefined8 *)(param_1 + 0x110) = param_3;
  *(ulonglong *)(param_1 + 0x118) = param_4;
  if (param_4 == 0) {
    if (*(longlong *)(param_1 + 0x168) != 0) {
      FUN_14000d900(*(longlong *)(param_1 + 0x100),*(longlong *)(param_1 + 0x168),1);
    }
  }
  else {
    if (*(longlong *)(param_1 + 0x168) == 0) {
      plVar1 = FUN_14000d6e0(*(longlong *)(param_1 + 0x100),0x1400059b0,param_1);
      *(longlong **)(param_1 + 0x168) = plVar1;
    }
    FUN_14000d8b0(*(longlong *)(param_1 + 0x100),*(longlong *)(param_1 + 0x168),3);
    uVar2 = FUN_14000c370(*(longlong *)(param_1 + 0x100));
    if (param_4 <= uVar2) {
      FUN_1400057f0(param_1,1);
      goto LAB_140005f72;
    }
    uVar2 = FUN_14000c370(*(longlong *)(param_1 + 0x100));
    if (param_4 <= uVar2) goto LAB_140005f72;
  }
  FUN_140005860(param_1,1);
LAB_140005f72:
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_140005fa0 @ 140005fa0  undefined8 FUN_140005fa0(longlong param_1, short param_2, undefined8 * param_3, undefined8 * param_4)

undefined8 FUN_140005fa0(longlong param_1,short param_2,undefined8 *param_3,undefined8 *param_4)

{
  undefined8 uVar1;
  
  if (param_2 == 4) {
    if (*(longlong *)(param_1 + 0x1b8) != 0) {
      FUN_140016e30();
    }
    if (param_3 != (undefined8 *)0x0) {
      *param_3 = *(undefined8 *)(param_1 + 0x120);
    }
    if (param_4 == (undefined8 *)0x0) goto LAB_140005fef;
    uVar1 = *(undefined8 *)(param_1 + 0x128);
  }
  else {
    if (param_2 != 2) {
      return 0xffffffff;
    }
    if (*(longlong *)(param_1 + 0x1b8) != 0) {
      FUN_140016e30();
    }
    if (param_3 != (undefined8 *)0x0) {
      *param_3 = *(undefined8 *)(param_1 + 0x110);
    }
    if (param_4 == (undefined8 *)0x0) goto LAB_140005fef;
    uVar1 = *(undefined8 *)(param_1 + 0x118);
  }
  *param_4 = uVar1;
LAB_140005fef:
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return 0;
}


// ==== FUN_140006060 @ 140006060  undefined4 FUN_140006060(longlong param_1, undefined2 param_2, undefined4 param_3)

undefined4 FUN_140006060(longlong param_1,undefined2 param_2,undefined4 param_3)

{
  code *pcVar1;
  undefined4 uVar2;
  
  uVar2 = 0xffffffff;
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  pcVar1 = *(code **)(*(longlong *)(param_1 + 8) + 0x38);
  if (pcVar1 != (code *)0x0) {
    uVar2 = (*pcVar1)(param_1,param_2,param_3);
  }
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return uVar2;
}


// ==== FUN_1400060e0 @ 1400060e0  undefined FUN_1400060e0(longlong param_1)

void FUN_1400060e0(longlong param_1)

{
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
    *(int *)(param_1 + 0x1b4) = *(int *)(param_1 + 0x1b4) + 1;
    return;
  }
  *(int *)(param_1 + 0x1b4) = *(int *)(param_1 + 0x1b4) + 1;
  return;
}


// ==== FUN_140006120 @ 140006120  undefined FUN_140006120(longlong * param_1)

void FUN_140006120(longlong *param_1)

{
  if (param_1[0x37] != 0) {
    FUN_140016e30();
  }
  FUN_140006940(param_1);
  return;
}


// ==== FUN_140006150 @ 140006150  undefined FUN_140006150(longlong param_1)

void FUN_140006150(longlong param_1)

{
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  *(int *)(param_1 + 0x1b4) = *(int *)(param_1 + 0x1b4) + 1;
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_140006190 @ 140006190  undefined4 FUN_140006190(longlong param_1, undefined8 param_2)

undefined4 FUN_140006190(longlong param_1,undefined8 param_2)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined8 local_res8;
  
  uVar2 = 0xffffffff;
  local_res8 = param_2;
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  pcVar1 = *(code **)(*(longlong *)(param_1 + 8) + 0x40);
  if (pcVar1 != (code *)0x0) {
    uVar2 = (*pcVar1)(param_1,0,&local_res8);
  }
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return uVar2;
}


// ==== FUN_140006200 @ 140006200  undefined8 FUN_140006200(longlong param_1)

undefined8 FUN_140006200(longlong param_1)

{
  code *pcVar1;
  int iVar2;
  undefined8 local_res8;
  
  iVar2 = -1;
  local_res8 = 0xffffffffffffffff;
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  pcVar1 = *(code **)(*(longlong *)(param_1 + 8) + 0x40);
  if (pcVar1 != (code *)0x0) {
    iVar2 = (*pcVar1)(param_1,1,&local_res8);
  }
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  if (iVar2 < 0) {
    local_res8 = 0xffffffffffffffff;
  }
  return local_res8;
}


// ==== FUN_140006280 @ 140006280  undefined4 FUN_140006280(longlong param_1)

undefined4 FUN_140006280(longlong param_1)

{
  undefined4 uVar1;
  
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  uVar1 = *(undefined4 *)(param_1 + 0x1b0);
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return uVar1;
}


// ==== FUN_1400062d0 @ 1400062d0  undefined FUN_1400062d0(longlong param_1)

void FUN_1400062d0(longlong param_1)

{
  code *pcVar1;
  undefined8 local_res8 [4];
  
  local_res8[0] = 0;
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  pcVar1 = *(code **)(*(longlong *)(param_1 + 8) + 0x40);
  if (pcVar1 != (code *)0x0) {
    (*pcVar1)(param_1,3,local_res8);
  }
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_140006330 @ 140006330  undefined2 FUN_140006330(longlong param_1)

undefined2 FUN_140006330(longlong param_1)

{
  undefined2 uVar1;
  
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  uVar1 = *(undefined2 *)(param_1 + 0x160);
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return uVar1;
}


// ==== FUN_140006380 @ 140006380  undefined8 FUN_140006380(longlong param_1)

undefined8 FUN_140006380(longlong param_1)

{
  code *pcVar1;
  int iVar2;
  undefined8 local_res8;
  
  iVar2 = -1;
  local_res8 = 0;
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  pcVar1 = *(code **)(*(longlong *)(param_1 + 8) + 0x40);
  if (pcVar1 != (code *)0x0) {
    iVar2 = (*pcVar1)(param_1,2,&local_res8);
  }
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  if (iVar2 < 0) {
    local_res8 = 0;
  }
  return local_res8;
}


// ==== FUN_140006400 @ 140006400  undefined8 FUN_140006400(longlong param_1)

undefined8 FUN_140006400(longlong param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  undefined8 *puVar4;
  longlong lVar5;
  
  uVar1 = *(ushort *)(param_1 + 0x160);
  if ((((uVar1 & 2) == 0) || (*(short *)(param_1 + 0x176) != 0)) ||
     ((*(int *)(param_1 + 0x150) == 0 && (*(int *)(param_1 + 0x154) == 0)))) {
    iVar2 = FUN_140014300((longlong *)(param_1 + 0x10));
  }
  else {
    puVar4 = FUN_140015e10((longlong *)(param_1 + 0x10),(ulonglong *)(param_1 + 0x150));
    iVar2 = (int)puVar4;
  }
  if ((((uVar1 & 4) != 0) && (*(short *)(param_1 + 0x178) == 0)) &&
     ((*(int *)(param_1 + 0x158) != 0 || (*(int *)(param_1 + 0x15c) != 0)))) {
    lVar5 = FUN_14000c370(*(longlong *)(param_1 + 0x108));
    if (lVar5 != 0) {
      puVar4 = FUN_140015e10((longlong *)(param_1 + 0x88),(ulonglong *)(param_1 + 0x158));
      iVar3 = (int)puVar4;
      goto LAB_1400064a8;
    }
  }
  iVar3 = FUN_140014300((longlong *)(param_1 + 0x88));
LAB_1400064a8:
  if ((-1 < iVar2) && (-1 < iVar3)) {
    return 0;
  }
  return 0xffffffff;
}


// ==== FUN_1400064e0 @ 1400064e0  undefined FUN_1400064e0(longlong * param_1, ulonglong * param_2)

void FUN_1400064e0(longlong *param_1,ulonglong *param_2)

{
  if (((int)*param_2 == 0) && (*(int *)((longlong)param_2 + 4) == 0)) {
    param_2 = (ulonglong *)0x0;
  }
  FUN_140015e10(param_1,param_2);
  return;
}


// ==== FUN_140006500 @ 140006500  undefined FUN_140006500(longlong param_1)

void FUN_140006500(longlong param_1)

{
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
    *(int *)(param_1 + 0x1b4) = *(int *)(param_1 + 0x1b4) + 1;
    return;
  }
  *(int *)(param_1 + 0x1b4) = *(int *)(param_1 + 0x1b4) + 1;
  return;
}


// ==== FUN_140006540 @ 140006540  undefined FUN_140006540(longlong * param_1, uint param_2)

void FUN_140006540(longlong *param_1,uint param_2)

{
  ulonglong uVar1;
  
  if ((code *)param_1[0x26] != (code *)0x0) {
    if (((*(uint *)(param_1 + 0x36) | param_2) & 4) == 0) {
      (*(code *)param_1[0x26])(param_1,param_1[0x29]);
    }
    else {
      *(uint *)(param_1 + 0x2e) = *(uint *)(param_1 + 0x2e) | 2;
      uVar1 = FUN_140012c10(*param_1,param_1 + 0x31);
      if ((int)uVar1 != 0) {
        if (param_1[0x37] != 0) {
          FUN_140016e30();
        }
        *(int *)((longlong)param_1 + 0x1b4) = *(int *)((longlong)param_1 + 0x1b4) + 1;
        if (param_1[0x37] != 0) {
          FUN_140016e50();
          return;
        }
      }
    }
  }
  return;
}


// ==== FUN_1400065c0 @ 1400065c0  undefined FUN_1400065c0(longlong * param_1, uint param_2)

void FUN_1400065c0(longlong *param_1,uint param_2)

{
  ulonglong uVar1;
  
  if ((code *)param_1[0x27] != (code *)0x0) {
    if (((*(uint *)(param_1 + 0x36) | param_2) & 4) == 0) {
      (*(code *)param_1[0x27])(param_1,param_1[0x29]);
    }
    else {
      *(uint *)(param_1 + 0x2e) = *(uint *)(param_1 + 0x2e) | 4;
      uVar1 = FUN_140012c10(*param_1,param_1 + 0x31);
      if ((int)uVar1 != 0) {
        if (param_1[0x37] != 0) {
          FUN_140016e30();
        }
        *(int *)((longlong)param_1 + 0x1b4) = *(int *)((longlong)param_1 + 0x1b4) + 1;
        if (param_1[0x37] != 0) {
          FUN_140016e50();
          return;
        }
      }
    }
  }
  return;
}


// ==== FUN_140006640 @ 140006640  undefined FUN_140006640(longlong * param_1, undefined8 param_2, uint param_3)

void FUN_140006640(longlong *param_1,undefined8 param_2,uint param_3)

{
  undefined4 uVar1;
  ulonglong uVar2;
  
  if ((code *)param_1[0x28] != (code *)0x0) {
    if (((*(uint *)(param_1 + 0x36) | param_3) & 4) == 0) {
      (*(code *)param_1[0x28])(param_1,param_2,param_1[0x29]);
    }
    else {
      *(ushort *)((longlong)param_1 + 0x174) =
           *(ushort *)((longlong)param_1 + 0x174) | (ushort)param_2;
      uVar1 = Ordinal_111();
      *(undefined4 *)((longlong)param_1 + 0x17c) = uVar1;
      uVar2 = FUN_140012c10(*param_1,param_1 + 0x31);
      if ((int)uVar2 != 0) {
        if (param_1[0x37] != 0) {
          FUN_140016e30();
        }
        *(int *)((longlong)param_1 + 0x1b4) = *(int *)((longlong)param_1 + 0x1b4) + 1;
        if (param_1[0x37] != 0) {
          FUN_140016e50();
          return;
        }
      }
    }
  }
  return;
}


// ==== FUN_1400066d0 @ 1400066d0  undefined FUN_1400066d0(undefined8 param_1, longlong param_2)

void FUN_1400066d0(undefined8 param_1,longlong param_2)

{
  code *pcVar1;
  longlong *plVar2;
  
  if (*(longlong *)(param_2 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  plVar2 = (longlong *)FUN_140006380(param_2);
  pcVar1 = *(code **)(*(longlong *)(param_2 + 8) + 0x28);
  if (pcVar1 != (code *)0x0) {
    (*pcVar1)(param_2);
  }
  FUN_14000c300(*(undefined8 **)(param_2 + 0x100));
  FUN_14000c300(*(undefined8 **)(param_2 + 0x108));
  if (*(longlong *)(param_2 + 0x1d0) != 0) {
    if (*(longlong *)(*(longlong *)(param_2 + 0x1d0) + 0x10) != 0) {
      FUN_140017ba0(param_2,0);
    }
    FUN_1400119c0(*(void **)(param_2 + 0x1d0));
    *(undefined8 *)(param_2 + 0x1d0) = 0;
  }
  if (*(longlong *)(param_2 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  if (((*(byte *)(param_2 + 0x170) & 1) != 0) && (*(longlong *)(param_2 + 0x1b8) != 0)) {
    FUN_140016e10();
  }
  FUN_1400119c0((void *)(param_2 - *(int *)(*(longlong *)(param_2 + 8) + 8)));
  if (plVar2 != (longlong *)0x0) {
    if (plVar2[0x37] != 0) {
      FUN_140016e30();
    }
    FUN_140006940(plVar2);
  }
  return;
}


// ==== FUN_1400067d0 @ 1400067d0  undefined8 FUN_1400067d0(longlong param_1, longlong param_2)

undefined8 FUN_1400067d0(longlong param_1,longlong param_2)

{
  longlong lVar1;
  
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    return 0xffffffff;
  }
  lVar1 = FUN_140006380(param_1);
  if (param_2 == 0) {
    if ((lVar1 == 0) || (param_2 = *(longlong *)(lVar1 + 0x1b8), param_2 == 0)) {
      param_2 = FUN_140016df0();
      if (param_2 == 0) {
        return 0xffffffff;
      }
      *(uint *)(param_1 + 0x170) = *(uint *)(param_1 + 0x170) | 1;
      *(longlong *)(param_1 + 0x1b8) = param_2;
    }
    else {
      *(uint *)(param_1 + 0x170) = *(uint *)(param_1 + 0x170) & 0xfffffffe;
      *(longlong *)(param_1 + 0x1b8) = param_2;
    }
  }
  else {
    *(uint *)(param_1 + 0x170) = *(uint *)(param_1 + 0x170) & 0xfffffffe;
    *(longlong *)(param_1 + 0x1b8) = param_2;
  }
  FUN_14000bfc0(*(longlong *)(param_1 + 0x100),param_2);
  FUN_14000bfc0(*(longlong *)(param_1 + 0x108),param_2);
  if ((lVar1 != 0) && (*(longlong *)(lVar1 + 0x1b8) == 0)) {
    FUN_1400067d0(lVar1,param_2);
  }
  return 0;
}


// ==== FUN_1400068c0 @ 1400068c0  undefined FUN_1400068c0(longlong * param_1, ushort param_2, uint param_3)

void FUN_1400068c0(longlong *param_1,ushort param_2,uint param_3)

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


// ==== FUN_140006940 @ 140006940  undefined8 FUN_140006940(longlong * param_1)

undefined8 FUN_140006940(longlong *param_1)

{
  int *piVar1;
  bool bVar2;
  undefined7 extraout_var;
  undefined8 uVar3;
  longlong lVar4;
  int iVar5;
  longlong *local_88 [3];
  longlong local_70;
  
  piVar1 = (int *)((longlong)param_1 + 0x1b4);
  *piVar1 = *piVar1 + -1;
  if (*piVar1 != 0) {
    if (param_1[0x37] != 0) {
      FUN_140016e50();
    }
    return 0;
  }
  if (*(code **)(param_1[1] + 0x20) != (code *)0x0) {
    (**(code **)(param_1[1] + 0x20))();
  }
  local_88[0] = param_1 + 2;
  iVar5 = 3;
  local_88[1] = param_1 + 0x11;
  local_88[2] = param_1 + 0x31;
  if (param_1[0x3a] != 0) {
    lVar4 = param_1[0x3a] + 0x38;
    bVar2 = FUN_1400110f0(lVar4);
    if ((int)CONCAT71(extraout_var,bVar2) != 0) {
      iVar5 = 4;
      local_70 = lVar4;
    }
  }
  uVar3 = FUN_14000d9f0(param_1[0x20],(longlong *)(local_88 + iVar5),0x10 - iVar5);
  iVar5 = iVar5 + (int)uVar3;
  uVar3 = FUN_14000d9f0(param_1[0x21],(longlong *)(local_88 + iVar5),0x10 - iVar5);
  FUN_140013e70(*param_1,(int)uVar3 + iVar5,local_88,0x1400066d0);
  if (param_1[0x37] != 0) {
    FUN_140016e50();
  }
  return 1;
}


// ==== FUN_140006a60 @ 140006a60  undefined FUN_140006a60(longlong * param_1)

void FUN_140006a60(longlong *param_1)

{
  undefined8 local_res8 [4];
  
  if (param_1[0x37] != 0) {
    FUN_140016e30();
  }
  if (param_1[0x37] != 0) {
    FUN_140016e30();
  }
  param_1[0x26] = 0;
  param_1[0x27] = 0;
  param_1[0x28] = 0;
  param_1[0x29] = 0;
  if (param_1[0x37] != 0) {
    FUN_140016e50();
  }
  local_res8[0] = 0;
  if (param_1[0x37] != 0) {
    FUN_140016e30();
  }
  if (*(code **)(param_1[1] + 0x40) != (code *)0x0) {
    (**(code **)(param_1[1] + 0x40))(param_1,3,local_res8);
  }
  if (param_1[0x37] != 0) {
    FUN_140016e50();
  }
  FUN_140006940(param_1);
  return;
}


// ==== FUN_140006b20 @ 140006b20  undefined FUN_140006b20(undefined8 param_1, undefined8 param_2, longlong * param_3)

void FUN_140006b20(undefined8 param_1,undefined8 param_2,longlong *param_3)

{
  if (param_3[0x37] != 0) {
    FUN_140016e30();
  }
  *(int *)((longlong)param_3 + 0x1b4) = *(int *)((longlong)param_3 + 0x1b4) + 1;
  if (param_3[0x37] != 0) {
    FUN_140016e30();
  }
  *(ushort *)(param_3 + 0x2c) = *(ushort *)(param_3 + 0x2c) & 0xfffd;
  (**(code **)(param_3[1] + 0x18))(param_3,2);
  if (param_3[0x37] != 0) {
    FUN_140016e50();
  }
  FUN_140006640(param_3,0x41,0);
  FUN_140006940(param_3);
  return;
}


// ==== FUN_140006ba0 @ 140006ba0  undefined FUN_140006ba0(undefined8 param_1, undefined8 param_2, longlong * param_3)

void FUN_140006ba0(undefined8 param_1,undefined8 param_2,longlong *param_3)

{
  if (param_3[0x37] != 0) {
    FUN_140016e30();
  }
  *(int *)((longlong)param_3 + 0x1b4) = *(int *)((longlong)param_3 + 0x1b4) + 1;
  if (param_3[0x37] != 0) {
    FUN_140016e30();
  }
  *(ushort *)(param_3 + 0x2c) = *(ushort *)(param_3 + 0x2c) & 0xfffb;
  (**(code **)(param_3[1] + 0x18))(param_3,4);
  if (param_3[0x37] != 0) {
    FUN_140016e50();
  }
  FUN_140006640(param_3,0x42,0);
  FUN_140006940(param_3);
  return;
}


// ==== FUN_140006c20 @ 140006c20  undefined FUN_140006c20(longlong * param_1)

void FUN_140006c20(longlong *param_1)

{
  FUN_140010e40((undefined *)(param_1 + 2),*param_1,0xffffffffffffffff,0x40,FUN_140006b20,
                (undefined *)param_1);
  FUN_140010e40((undefined *)(param_1 + 0x11),*param_1,0xffffffffffffffff,0x40,FUN_140006ba0,
                (undefined *)param_1);
  return;
}


// ==== FUN_140006c90 @ 140006c90  undefined FUN_140006c90(undefined8 param_1, longlong * param_2)

void FUN_140006c90(undefined8 param_1,longlong *param_2)

{
  short sVar1;
  undefined4 uVar2;
  
  if (param_2[0x37] != 0) {
    FUN_140016e30();
  }
  if (((char)*(ushort *)((longlong)param_2 + 0x174) < '\0') && (param_2[0x28] != 0)) {
    *(ushort *)((longlong)param_2 + 0x174) = *(ushort *)((longlong)param_2 + 0x174) & 0xff7f;
    (*(code *)param_2[0x28])(param_2,0x80,param_2[0x29]);
  }
  if (((*(uint *)(param_2 + 0x2e) & 2) != 0) && (param_2[0x26] != 0)) {
    *(uint *)(param_2 + 0x2e) = *(uint *)(param_2 + 0x2e) & 0xfffffffd;
    (*(code *)param_2[0x26])(param_2,param_2[0x29]);
  }
  if (((*(uint *)(param_2 + 0x2e) & 4) != 0) && (param_2[0x27] != 0)) {
    *(uint *)(param_2 + 0x2e) = *(uint *)(param_2 + 0x2e) & 0xfffffffb;
    (*(code *)param_2[0x27])(param_2,param_2[0x29]);
  }
  sVar1 = *(short *)((longlong)param_2 + 0x174);
  if ((sVar1 != 0) && (param_2[0x28] != 0)) {
    uVar2 = *(undefined4 *)((longlong)param_2 + 0x17c);
    *(undefined2 *)((longlong)param_2 + 0x174) = 0;
    *(undefined4 *)((longlong)param_2 + 0x17c) = 0;
    Ordinal_112(uVar2);
    (*(code *)param_2[0x28])(param_2,sVar1,param_2[0x29]);
  }
  FUN_140006940(param_2);
  return;
}


// ==== FUN_140006da0 @ 140006da0  undefined FUN_140006da0(undefined8 param_1, longlong * param_2)

void FUN_140006da0(undefined8 param_1,longlong *param_2)

{
  short sVar1;
  undefined4 uVar2;
  code *pcVar3;
  longlong lVar4;
  
  if (param_2[0x37] != 0) {
    FUN_140016e30();
  }
  if (((char)*(ushort *)((longlong)param_2 + 0x174) < '\0') &&
     (pcVar3 = (code *)param_2[0x28], pcVar3 != (code *)0x0)) {
    lVar4 = param_2[0x29];
    *(ushort *)((longlong)param_2 + 0x174) = *(ushort *)((longlong)param_2 + 0x174) & 0xff7f;
    if (param_2[0x37] != 0) {
      FUN_140016e50();
    }
    (*pcVar3)(param_2,0x80,lVar4);
    if (param_2[0x37] != 0) {
      FUN_140016e30();
    }
  }
  if (((*(uint *)(param_2 + 0x2e) & 2) != 0) &&
     (pcVar3 = (code *)param_2[0x26], pcVar3 != (code *)0x0)) {
    lVar4 = param_2[0x29];
    *(uint *)(param_2 + 0x2e) = *(uint *)(param_2 + 0x2e) & 0xfffffffd;
    if (param_2[0x37] != 0) {
      FUN_140016e50();
    }
    (*pcVar3)(param_2,lVar4);
    if (param_2[0x37] != 0) {
      FUN_140016e30();
    }
  }
  if (((*(uint *)(param_2 + 0x2e) & 4) != 0) &&
     (pcVar3 = (code *)param_2[0x27], pcVar3 != (code *)0x0)) {
    lVar4 = param_2[0x29];
    *(uint *)(param_2 + 0x2e) = *(uint *)(param_2 + 0x2e) & 0xfffffffb;
    if (param_2[0x37] != 0) {
      FUN_140016e50();
    }
    (*pcVar3)(param_2,lVar4);
    if (param_2[0x37] != 0) {
      FUN_140016e30();
    }
  }
  sVar1 = *(short *)((longlong)param_2 + 0x174);
  if ((sVar1 != 0) && (pcVar3 = (code *)param_2[0x28], pcVar3 != (code *)0x0)) {
    uVar2 = *(undefined4 *)((longlong)param_2 + 0x17c);
    lVar4 = param_2[0x29];
    *(undefined2 *)((longlong)param_2 + 0x174) = 0;
    *(undefined4 *)((longlong)param_2 + 0x17c) = 0;
    Ordinal_112(uVar2);
    if (param_2[0x37] != 0) {
      FUN_140016e50();
    }
    (*pcVar3)(param_2,sVar1,lVar4);
    if (param_2[0x37] != 0) {
      FUN_140016e30();
    }
  }
  FUN_140006940(param_2);
  return;
}


// ==== FUN_140006f60 @ 140006f60  undefined FUN_140006f60(longlong * param_1, ushort param_2, uint param_3)

void FUN_140006f60(longlong *param_1,ushort param_2,uint param_3)

{
  if (param_1[0x37] != 0) {
    FUN_140016e30();
  }
  *(int *)((longlong)param_1 + 0x1b4) = *(int *)((longlong)param_1 + 0x1b4) + 1;
  FUN_1400068c0(param_1,param_2,param_3 & 0x10004);
  FUN_140006940(param_1);
  return;
}


// ==== FUN_140006fc0 @ 140006fc0  undefined FUN_140006fc0(longlong * param_1, ushort param_2, uint param_3)

void FUN_140006fc0(longlong *param_1,ushort param_2,uint param_3)

{
  if (param_1[0x37] != 0) {
    FUN_140016e30();
  }
  *(int *)((longlong)param_1 + 0x1b4) = *(int *)((longlong)param_1 + 0x1b4) + 1;
  FUN_140006640(param_1,(ulonglong)param_2,param_3 & 0x10004);
  FUN_140006940(param_1);
  return;
}


// ==== FUN_140007020 @ 140007020  undefined8 FUN_140007020(longlong * param_1, longlong param_2, longlong param_3, ulonglong param_4)

undefined8 FUN_140007020(longlong *param_1,longlong param_2,longlong param_3,ulonglong param_4)

{
  int iVar1;
  longlong lVar2;
  undefined8 uVar3;
  longlong lVar4;
  longlong lVar5;
  code *pcVar6;
  ulonglong uVar7;
  
  lVar4 = param_2;
  lVar5 = param_3;
  uVar7 = param_4;
  if (param_1[0x20] == 0) {
    lVar2 = FUN_14000be80();
    param_1[0x20] = lVar2;
    if (lVar2 != 0) goto LAB_14000705b;
LAB_140007082:
    uVar3 = 0xffffffff;
  }
  else {
LAB_14000705b:
    if (param_1[0x21] == 0) {
      lVar2 = FUN_14000be80();
      param_1[0x21] = lVar2;
      if (lVar2 == 0) {
        FUN_14000c300((undefined8 *)param_1[0x20]);
        goto LAB_140007082;
      }
    }
    *(undefined4 *)((longlong)param_1 + 0x1b4) = 1;
    *param_1 = param_2;
    param_1[1] = param_3;
    *(undefined4 *)((longlong)param_1 + 0x154) = 0;
    *(undefined4 *)(param_1 + 0x2a) = 0;
    *(undefined4 *)((longlong)param_1 + 0x15c) = 0;
    *(undefined4 *)(param_1 + 0x2b) = 0;
    FUN_1400181f0((longlong)param_1);
    *(undefined2 *)(param_1 + 0x2c) = 4;
    if ((param_4 & 2) != 0) {
      lVar4 = 0;
      uVar3 = FUN_1400067d0((longlong)param_1,0);
      if ((int)uVar3 < 0) {
        FUN_14000c300((undefined8 *)param_1[0x20]);
        FUN_14000c300((undefined8 *)param_1[0x21]);
        param_1[0x20] = 0;
        param_1[0x21] = 0;
        return 0xffffffff;
      }
    }
    if (((byte)param_4 & 0xc) == 8) {
      FUN_1400191c0("UNLOCK_CALLBACKS requires DEFER_CALLBACKS",lVar4,lVar5,uVar7);
      uVar3 = 0xffffffff;
    }
    else {
      if ((param_4 & 8) == 0) {
        iVar1 = FUN_140010a70(param_2);
        pcVar6 = FUN_140006c90;
      }
      else {
        iVar1 = FUN_140010a70(param_2);
        pcVar6 = FUN_140006da0;
      }
      FUN_1400112a0(param_1 + 0x31,(char)(iVar1 / 2),pcVar6,param_1);
      *(int *)(param_1 + 0x36) = (int)param_4;
      FUN_14000c010(param_1[0x20],param_1);
      FUN_14000c010(param_1[0x21],param_1);
      uVar3 = 0;
    }
  }
  return uVar3;
}


// ==== FUN_1400071b0 @ 1400071b0  undefined4 FUN_1400071b0(longlong * param_1, ushort param_2)

undefined4 FUN_1400071b0(longlong *param_1,ushort param_2)

{
  int iVar1;
  undefined4 uVar2;
  ushort uVar3;
  
  uVar2 = 0;
  if (param_1[0x37] != 0) {
    FUN_140016e30();
  }
  *(int *)((longlong)param_1 + 0x1b4) = *(int *)((longlong)param_1 + 0x1b4) + 1;
  uVar3 = param_2;
  if (*(short *)((longlong)param_1 + 0x176) != 0) {
    uVar3 = param_2 & 0xfffd;
  }
  if ((short)param_1[0x2f] != 0) {
    uVar3 = uVar3 & 0xfffb;
  }
  *(ushort *)(param_1 + 0x2c) = *(ushort *)(param_1 + 0x2c) | param_2;
  if (uVar3 != 0) {
    iVar1 = (**(code **)(param_1[1] + 0x10))(param_1,uVar3);
    uVar2 = 0;
    if (iVar1 < 0) {
      uVar2 = 0xffffffff;
    }
  }
  FUN_140006940(param_1);
  return uVar2;
}


// ==== FUN_140007250 @ 140007250  undefined * FUN_140007250(DWORD param_1)

undefined * FUN_140007250(DWORD param_1)

{
  FormatMessageA(0x12ff,(LPCVOID)0x0,param_1,0x400,&DAT_140106da0,0x400,(va_list *)0x0);
  return &DAT_140106da0;
}


// ==== FUN_1400072a0 @ 1400072a0  int FUN_1400072a0(char * param_1, int param_2)

int FUN_1400072a0(char *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = _open(param_1,param_2);
  if (iVar1 < 0) {
    iVar1 = -1;
  }
  return iVar1;
}


// ==== FUN_1400072c0 @ 1400072c0  undefined4 FUN_1400072c0(char * param_1, undefined8 * param_2, ulonglong * param_3, int param_4)

undefined4 FUN_1400072c0(char *param_1,undefined8 *param_2,ulonglong *param_3,int param_4)

{
  int _FileHandle;
  int iVar1;
  undefined4 uVar2;
  void *pvVar3;
  uint _MaxCharCount;
  ulonglong uVar4;
  ulonglong uVar5;
  undefined1 local_58 [24];
  ulonglong local_40;
  
  uVar5 = 0;
  *param_2 = 0;
  uVar4 = uVar5;
  if (param_4 != 0) {
    uVar4 = 0x8000;
  }
  *param_3 = 0;
  _FileHandle = _open(param_1,(int)uVar4);
  if (-1 < _FileHandle) {
    iVar1 = _fstat64(_FileHandle,local_58);
    if ((iVar1 == 0) && (local_40 < 0x7fffffffffffffff)) {
      pvVar3 = FUN_140011830(local_40 + 1);
      if (pvVar3 == (void *)0x0) {
        _close(_FileHandle);
        uVar2 = 0xfffffffe;
      }
      else {
        do {
          if (local_40 - uVar5 < 0x80000000) {
            _MaxCharCount = (int)local_40 - (int)uVar5;
          }
          else {
            _MaxCharCount = 0x7fffffff;
          }
          iVar1 = _read(_FileHandle,(void *)((longlong)pvVar3 + uVar5),_MaxCharCount);
        } while ((0 < iVar1) && (uVar5 = uVar5 + (longlong)iVar1, uVar5 < local_40));
        _close(_FileHandle);
        if (iVar1 < 0) {
          FUN_1400119c0(pvVar3);
          uVar2 = 0xfffffffe;
        }
        else {
          *(undefined1 *)((longlong)pvVar3 + uVar5) = 0;
          *param_3 = uVar5;
          uVar2 = 0;
          *param_2 = pvVar3;
        }
      }
      return uVar2;
    }
    _close(_FileHandle);
    return 0xfffffffe;
  }
  return 0xffffffff;
}


// ==== FUN_140007430 @ 140007430  undefined8 FUN_140007430(ulonglong param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

undefined8 FUN_140007430(ulonglong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  undefined4 local_res10 [6];
  
  local_res10[0] = 1;
  iVar1 = Ordinal_10(param_1,0x8004667e,local_res10);
  if (iVar1 == -1) {
    FUN_140019120(param_1,"fcntl(%d, F_GETFL)",param_1 & 0xffffffff,param_4);
    return 0xffffffff;
  }
  return 0;
}


// ==== FUN_140007480 @ 140007480  undefined8 FUN_140007480(ulonglong param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

undefined8 FUN_140007480(ulonglong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  undefined4 local_res10 [6];
  
  local_res10[0] = 1;
  iVar1 = Ordinal_10(param_1,0x8004667e,local_res10);
  if (iVar1 == -1) {
    FUN_140019120(param_1,"fcntl(%d, F_GETFL)",param_1 & 0xffffffff,param_4);
    return 0xffffffff;
  }
  return 0;
}


// ==== FUN_140007540 @ 140007540  int FUN_140007540(longlong param_1)

int FUN_140007540(longlong param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_res10 [2];
  int local_res18 [4];
  
  local_res10[0] = 4;
  iVar1 = Ordinal_111();
  if ((iVar1 == 0x2733) && (-1 < param_1)) {
    iVar2 = Ordinal_7(param_1,0xffff,0x1007,local_res18,local_res10);
    if (iVar2 != 0) {
      return 0x2733;
    }
    if (local_res18[0] != 0) {
      return local_res18[0];
    }
  }
  return iVar1;
}


// ==== FUN_1400075c0 @ 1400075c0  undefined8 FUN_1400075c0(ulonglong * param_1, undefined2 * param_2, undefined4 param_3, undefined8 param_4)

undefined8
FUN_1400075c0(ulonglong *param_1,undefined2 *param_2,undefined4 param_3,undefined8 param_4)

{
  bool bVar1;
  int iVar2;
  ulonglong uVar3;
  undefined4 local_res8 [2];
  
  bVar1 = false;
  if ((longlong)*param_1 < 0) {
    uVar3 = Ordinal_23(*param_2,1,0);
    *param_1 = uVar3;
    if ((longlong)uVar3 < 0) {
      return 0xffffffff;
    }
    bVar1 = true;
    local_res8[0] = 1;
    iVar2 = Ordinal_10(uVar3,0x8004667e,local_res8);
    if (iVar2 == -1) {
      FUN_140019120(uVar3,"fcntl(%d, F_GETFL)",uVar3 & 0xffffffff,param_4);
      goto LAB_14000767e;
    }
  }
  iVar2 = Ordinal_4(*param_1,param_2,param_3);
  if (-1 < iVar2) {
    return 1;
  }
  iVar2 = FUN_140007540(*param_1);
  if ((((iVar2 == 0x2733) || (iVar2 == 0x2714)) || (iVar2 == 0x2734)) || (iVar2 == 0x2726)) {
    return 0;
  }
  if (iVar2 == 0x274d) {
    return 2;
  }
  if (!bVar1) {
    return 0xffffffff;
  }
LAB_14000767e:
  Ordinal_3(*param_1);
  *param_1 = 0xffffffffffffffff;
  return 0xffffffff;
}


// ==== FUN_1400076b0 @ 1400076b0  undefined8 FUN_1400076b0(undefined8 param_1)

undefined8 FUN_1400076b0(undefined8 param_1)

{
  int iVar1;
  undefined4 local_res10 [2];
  int local_res18 [4];
  
  local_res10[0] = 4;
  iVar1 = Ordinal_7(param_1,0xffff,0x1007,local_res18,local_res10);
  if (-1 < iVar1) {
    if (local_res18[0] == 0) {
      return 1;
    }
    if ((((local_res18[0] == 0x2733) || (local_res18[0] == 0x2714)) || (local_res18[0] == 0x2734))
       || (local_res18[0] == 0x2726)) {
      return 0;
    }
    Ordinal_112();
  }
  return 0xffffffff;
}


// ==== FUN_140007730 @ 140007730  undefined FUN_140007730(short * param_1)

void FUN_140007730(short *param_1)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  undefined1 auStack_48 [32];
  undefined8 local_28;
  undefined8 local_20;
  undefined1 local_18;
  ulonglong local_10;
  
  local_10 = DAT_140103510 ^ (ulonglong)auStack_48;
  local_28 = 0;
  local_20 = 0;
  local_18 = 0;
  if (*param_1 == 2) {
    uVar3 = Ordinal_14(*(undefined4 *)(param_1 + 2));
    if (((uVar3 != 0) && (uVar3 >> 0x18 != 0x7f)) && (((byte)(uVar3 >> 0x18) & 0xf0) != 0xe0)) {
      DAT_140103f5c = 1;
      __security_check_cookie(local_10 ^ (ulonglong)auStack_48);
      return;
    }
  }
  else if (((((*param_1 == 0x17) && (*(longlong *)(param_1 + 4) != 0)) &&
            (bVar1 = (byte)*(longlong *)(param_1 + 4), (bVar1 & 0xfe) != 0xfc)) &&
           ((bVar1 != 0xfe ||
            ((bVar2 = *(byte *)((longlong)param_1 + 9) & 0xc0, bVar2 != 0x80 && (bVar2 != 0xc0))))))
          && (bVar1 != 0xff)) {
    DAT_140103f60 = 1;
  }
  __security_check_cookie(local_10 ^ (ulonglong)auStack_48);
  return;
}


// ==== FUN_140007850 @ 140007850  uint FUN_140007850(char * param_1)

uint FUN_140007850(char *param_1)

{
  uint uVar1;
  char *local_res10 [3];
  
  local_res10[0] = (char *)0x0;
  uVar1 = strtol(param_1,local_res10,10);
  if ((((0xffff < uVar1) || (*param_1 == '\0')) || (local_res10[0] == (char *)0x0)) ||
     (*local_res10[0] != '\0')) {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}


// ==== FUN_1400078a0 @ 1400078a0  uint FUN_1400078a0(char * param_1, undefined8 param_2, byte * param_3)

uint FUN_1400078a0(char *param_1,undefined8 param_2,byte *param_3)

{
  ushort uVar1;
  uint uVar2;
  longlong lVar3;
  char *local_res20;
  
  local_res20 = (char *)0x0;
  uVar2 = strtol(param_1,&local_res20,10);
  if ((((0xffff < uVar2) || (*param_1 == '\0')) || (local_res20 == (char *)0x0)) ||
     (*local_res20 != '\0')) {
    if ((*param_3 & 8) == 0) {
      lVar3 = Ordinal_55(param_1,param_2);
      if (lVar3 != 0) {
        uVar1 = Ordinal_15(*(undefined2 *)(lVar3 + 0x18));
        return (uint)uVar1;
      }
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


// ==== FUN_140007940 @ 140007940  undefined * FUN_140007940(int param_1)

undefined * FUN_140007940(int param_1)

{
  undefined8 *puVar1;
  
  if (param_1 != 0) {
    if (param_1 == 6) {
      return &DAT_1400c093c;
    }
    if (param_1 == 0x11) {
      return &DAT_1400c0940;
    }
    puVar1 = (undefined8 *)Ordinal_54();
    if (puVar1 != (undefined8 *)0x0) {
      return (undefined *)*puVar1;
    }
  }
  return (undefined *)0x0;
}


// ==== FUN_1400079e0 @ 1400079e0  undefined FUN_1400079e0(void)

void FUN_1400079e0(void)

{
  int iVar1;
  int iVar2;
  longlong local_res8;
  longlong local_res10;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  
  local_30 = 0;
  local_28 = 0;
  local_20 = 0;
  local_18 = 0;
  local_10 = 0;
  local_res10 = 0;
  local_res8 = 0;
  local_38 = 0xc;
  iVar1 = getaddrinfo("1.2.3.4",&DAT_1400c0944,&local_38,&local_res10);
  local_30 = CONCAT44(local_30._4_4_,1);
  iVar2 = getaddrinfo("1.2.3.4",&DAT_1400c0944,&local_38,&local_res8);
  if ((iVar2 == 0) && (iVar1 != 0)) {
    DAT_140103f64 = 1;
  }
  if ((local_res8 != 0) && (*(int *)(local_res8 + 0xc) == 0)) {
    DAT_140103f68 = 1;
  }
  if (local_res10 != 0) {
    freeaddrinfo(local_res10);
  }
  if (local_res8 != 0) {
    freeaddrinfo();
  }
  DAT_140103f6c = 1;
  return;
}


// ==== FUN_140007ad0 @ 140007ad0  undefined4 FUN_140007ad0(void)

undefined4 FUN_140007ad0(void)

{
  if (DAT_140103f6c == 0) {
    FUN_1400079e0();
  }
  return DAT_140103f64;
}


// ==== FUN_140007af0 @ 140007af0  undefined4 FUN_140007af0(void)

undefined4 FUN_140007af0(void)

{
  if (DAT_140103f6c == 0) {
    FUN_1400079e0();
  }
  return DAT_140103f68;
}


// ==== FUN_140007b10 @ 140007b10  undefined FUN_140007b10(undefined2 param_1, longlong * param_2)

void FUN_140007b10(undefined2 param_1,longlong *param_2)

{
  longlong lVar1;
  short *psVar2;
  short sVar3;
  
  lVar1 = *param_2;
  do {
    if (lVar1 == 0) {
      return;
    }
    lVar1 = *param_2;
    psVar2 = *(short **)(lVar1 + 0x20);
    if (psVar2 == (short *)0x0) {
LAB_140007b6a:
      *param_2 = *(longlong *)(lVar1 + 0x28);
      *(undefined8 *)(lVar1 + 0x28) = 0;
      freeaddrinfo();
    }
    else if (*psVar2 == 2) {
      sVar3 = Ordinal_9(param_1);
      psVar2[1] = sVar3;
    }
    else {
      if (*psVar2 != 0x17) goto LAB_140007b6a;
      sVar3 = Ordinal_9(param_1);
      psVar2[1] = sVar3;
    }
    param_2 = (longlong *)(*param_2 + 0x28);
    lVar1 = *param_2;
  } while( true );
}


// ==== FUN_140007ba0 @ 140007ba0  undefined8 FUN_140007ba0(undefined8 * param_1)

undefined8 FUN_140007ba0(undefined8 *param_1)

{
  int iVar1;
  undefined8 *puVar2;
  
  if (param_1 != (undefined8 *)0x0) {
    do {
      if (*(int *)((longlong)param_1 + 0xc) == 0) {
        iVar1 = *(int *)(param_1 + 1);
        if (iVar1 != 0) {
          if (iVar1 == 2) {
            *(undefined4 *)((longlong)param_1 + 0xc) = 0x11;
          }
          else if (iVar1 == 1) {
            *(undefined4 *)((longlong)param_1 + 0xc) = 6;
          }
        }
      }
      if (*(int *)(param_1 + 1) == 0) {
        iVar1 = *(int *)((longlong)param_1 + 0xc);
        if (iVar1 != 0) {
          if (iVar1 == 0x11) {
            *(undefined4 *)(param_1 + 1) = 2;
          }
          else if (iVar1 == 6) {
            *(undefined4 *)(param_1 + 1) = 1;
          }
        }
        if ((*(int *)(param_1 + 1) == 0) && (*(int *)((longlong)param_1 + 0xc) == 0)) {
          puVar2 = (undefined8 *)FUN_140011830(0x30);
          if (puVar2 == (undefined8 *)0x0) {
            return 0xffffffff;
          }
          *puVar2 = *param_1;
          puVar2[1] = param_1[1];
          puVar2[2] = param_1[2];
          puVar2[3] = param_1[3];
          puVar2[4] = param_1[4];
          puVar2[5] = param_1[5];
          *(undefined4 *)(param_1 + 1) = 1;
          *(undefined4 *)((longlong)param_1 + 0xc) = 6;
          *(undefined4 *)(puVar2 + 1) = 2;
          *(undefined4 *)((longlong)puVar2 + 0xc) = 0x11;
          puVar2[5] = param_1[5];
          param_1[5] = puVar2;
        }
      }
      param_1 = (undefined8 *)param_1[5];
    } while (param_1 != (undefined8 *)0x0);
  }
  return 0;
}


// ==== FUN_140007ca0 @ 140007ca0  undefined FUN_140007ca0(int * param_1)

void FUN_140007ca0(int *param_1)

{
  int *piVar1;
  
  if (*param_1 < 0) {
    do {
      piVar1 = *(int **)(param_1 + 10);
      if (*(void **)(param_1 + 6) != (void *)0x0) {
        FUN_1400119c0(*(void **)(param_1 + 6));
      }
      FUN_1400119c0(param_1);
      param_1 = piVar1;
    } while (piVar1 != (int *)0x0);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000140007cb4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  freeaddrinfo();
  return;
}


// ==== FUN_140007df0 @ 140007df0  undefined FUN_140007df0(char * param_1)

void FUN_140007df0(char *param_1)

{
  char cVar1;
  ulonglong uVar2;
  char *pcVar3;
  
  if (param_1 != (char *)0x0) {
    uVar2 = 0xffffffffffffffff;
    pcVar3 = param_1;
    do {
      if (uVar2 == 0) break;
      uVar2 = uVar2 - 1;
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    uVar2 = ~uVar2;
    if ((((uVar2 != 1) && (param_1[uVar2 - 2] == '\n')) &&
        (param_1[uVar2 - 2] = '\0', uVar2 - 2 != 0)) && (param_1[uVar2 - 3] == '\r')) {
      param_1[uVar2 - 3] = '\0';
    }
  }
  return;
}


// ==== FUN_140008010 @ 140008010  undefined8 FUN_140008010(longlong * param_1, uint param_2)

undefined8 FUN_140008010(longlong *param_1,uint param_2)

{
  uint uVar1;
  ulonglong uVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  void *_Dst;
  undefined8 *puVar5;
  uint uVar6;
  uint uVar7;
  undefined *puVar8;
  size_t _Size;
  ulonglong uVar9;
  ulonglong uVar10;
  undefined8 *puVar11;
  undefined8 *puVar12;
  uint uVar13;
  ulonglong uVar14;
  uint uVar15;
  
  uVar14 = (ulonglong)*(int *)((longlong)param_1 + 0x14);
  if ((*(int *)((longlong)param_1 + 0x14) == DAT_140102408 + -1) ||
     (param_2 < *(uint *)(param_1 + 2))) {
    return 0;
  }
  puVar8 = &DAT_140102410 + uVar14 * 4;
  do {
    uVar1 = *(uint *)(puVar8 + 4);
    uVar9 = (ulonglong)uVar1;
    puVar8 = puVar8 + 4;
    uVar13 = (int)uVar14 + 1;
    uVar14 = (ulonglong)uVar13;
    uVar15 = (uint)(longlong)((double)uVar9 * 0.5);
    if (param_2 < uVar15) break;
  } while ((int)uVar13 < DAT_140102408);
  _Size = uVar9 << 3;
  _Dst = FUN_140011830(_Size);
  if (_Dst == (void *)0x0) {
    puVar5 = (undefined8 *)FUN_1400119a0((void *)*param_1,_Size);
    if (puVar5 == (undefined8 *)0x0) {
      return 0xffffffff;
    }
    memset(puVar5 + *(uint *)(param_1 + 1),0,(ulonglong)(uVar1 - *(uint *)(param_1 + 1)) << 3);
    uVar6 = 0;
    puVar12 = puVar5;
    if ((int)param_1[1] != 0) {
      do {
        puVar4 = (undefined8 *)*puVar12;
        puVar3 = puVar12;
        while (puVar11 = puVar4, puVar11 != (undefined8 *)0x0) {
          uVar7 = (*(uint *)(puVar11 + 1) >> 0x10 ^ *(uint *)(puVar11 + 1)) * -0x7a143595;
          uVar7 = (uVar7 >> 0xd ^ uVar7) * -0x3d4d51cb;
          uVar14 = (ulonglong)(uVar7 >> 0x10 ^ uVar7) % (ulonglong)uVar1;
          if ((uint)uVar14 != uVar6) {
            *puVar3 = *puVar11;
            *puVar11 = puVar5[uVar14];
            puVar5[uVar14] = puVar11;
            puVar11 = puVar3;
          }
          puVar3 = puVar11;
          puVar4 = (undefined8 *)*puVar11;
        }
        uVar6 = uVar6 + 1;
        puVar12 = puVar12 + 1;
      } while (uVar6 < *(uint *)(param_1 + 1));
    }
    *param_1 = (longlong)puVar5;
  }
  else {
    memset(_Dst,0,_Size);
    uVar10 = 0;
    uVar14 = uVar10;
    if ((int)param_1[1] != 0) {
      do {
        puVar5 = *(undefined8 **)(uVar10 + *param_1);
        while (puVar5 != (undefined8 *)0x0) {
          puVar12 = (undefined8 *)*puVar5;
          uVar6 = (*(uint *)(puVar5 + 1) >> 0x10 ^ *(uint *)(puVar5 + 1)) * -0x7a143595;
          uVar6 = (uVar6 >> 0xd ^ uVar6) * -0x3d4d51cb;
          uVar2 = (ulonglong)(uVar6 >> 0x10 ^ uVar6) % uVar9;
          *puVar5 = *(undefined8 *)((longlong)_Dst + uVar2 * 8);
          *(undefined8 **)((longlong)_Dst + uVar2 * 8) = puVar5;
          puVar5 = puVar12;
        }
        uVar6 = (int)uVar14 + 1;
        uVar10 = uVar10 + 8;
        uVar14 = (ulonglong)uVar6;
      } while (uVar6 < *(uint *)(param_1 + 1));
    }
    if ((void *)*param_1 != (void *)0x0) {
      FUN_1400119c0((void *)*param_1);
    }
    *param_1 = (longlong)_Dst;
  }
  *(uint *)(param_1 + 1) = uVar1;
  *(uint *)((longlong)param_1 + 0x14) = uVar13;
  *(uint *)(param_1 + 2) = uVar15;
  return 0;
}


// ==== FUN_140008220 @ 140008220  undefined FUN_140008220(undefined8 * param_1)

void FUN_140008220(undefined8 *param_1)

{
  if ((void *)*param_1 != (void *)0x0) {
    FUN_1400119c0((void *)*param_1);
  }
  *(undefined4 *)((longlong)param_1 + 0x14) = 0xffffffff;
  *(undefined4 *)(param_1 + 1) = 0;
  *param_1 = 0;
  *(undefined4 *)((longlong)param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 2) = 0;
  return;
}


// ==== FUN_140008260 @ 140008260  int FUN_140008260(longlong * param_1)

int FUN_140008260(longlong *param_1)

{
  uint uVar1;
  undefined8 *puVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined8 *puVar6;
  uint uVar7;
  uint uVar8;
  
  uVar1 = *(uint *)(param_1 + 1);
  if (uVar1 == 0) {
    if ((((*param_1 == 0) && (*(int *)((longlong)param_1 + 0xc) == 0)) && ((int)param_1[2] == 0)) &&
       (*(int *)((longlong)param_1 + 0x14) == -1)) {
      return 0;
    }
    return 1;
  }
  puVar6 = (undefined8 *)*param_1;
  if (((puVar6 == (undefined8 *)0x0) || (*(int *)((longlong)param_1 + 0x14) < 0)) ||
     (uVar7 = *(uint *)(param_1 + 2), uVar7 == 0)) {
    return 2;
  }
  if (uVar7 < *(uint *)((longlong)param_1 + 0xc)) {
    return 3;
  }
  if (uVar1 == *(uint *)(&DAT_140102410 + (longlong)*(int *)((longlong)param_1 + 0x14) * 4)) {
    if (uVar7 != (uint)(longlong)((double)uVar1 * 0.5)) {
      return 5;
    }
    uVar8 = 0;
    uVar7 = 0;
    if (uVar1 != 0) {
      do {
        for (puVar2 = (undefined8 *)*puVar6; puVar2 != (undefined8 *)0x0;
            puVar2 = (undefined8 *)*puVar2) {
          uVar5 = *(uint *)(puVar2 + 1);
          uVar4 = (uVar5 >> 0x10 ^ uVar5) * -0x7a143595;
          uVar4 = (uVar4 >> 0xd ^ uVar4) * -0x3d4d51cb;
          uVar5 = (uVar5 >> 0x10 ^ uVar5) * -0x7a143595;
          uVar5 = (uVar5 >> 0xd ^ uVar5) * -0x3d4d51cb;
          if ((uVar4 >> 0x10 ^ uVar4) != (uVar5 >> 0x10 ^ uVar5)) {
            return uVar8 + 1000;
          }
          uVar5 = (*(uint *)(puVar2 + 1) >> 0x10 ^ *(uint *)(puVar2 + 1)) * -0x7a143595;
          uVar5 = (uVar5 >> 0xd ^ uVar5) * -0x3d4d51cb;
          if ((uVar5 >> 0x10 ^ uVar5) % uVar1 != uVar8) {
            return uVar8 + 10000;
          }
          uVar7 = uVar7 + 1;
        }
        uVar8 = uVar8 + 1;
        puVar6 = puVar6 + 1;
      } while (uVar8 < uVar1);
    }
    iVar3 = 0;
    if (uVar7 != *(uint *)((longlong)param_1 + 0xc)) {
      iVar3 = 6;
    }
    return iVar3;
  }
  return 4;
}


// ==== FUN_140008440 @ 140008440  undefined8 FUN_140008440(uint param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

undefined8 FUN_140008440(uint param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  ulonglong uVar1;
  
  uVar1 = (ulonglong)param_1;
  DAT_140103f78 = FUN_140016ce0(DAT_140103f78,0,param_1);
  if (DAT_140103f78 == (undefined4 *)0x0) {
    FUN_140019050("Couldn\'t allocate %s","windows_socket_errors_lock_",uVar1,param_4);
    return 0xffffffff;
  }
  return 0;
}


// ==== FUN_140008490 @ 140008490  undefined FUN_140008490(void)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_140008490(void)

{
  uint uVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong *plVar4;
  longlong *plVar5;
  
  plVar5 = (longlong *)0x0;
  plVar2 = plVar5;
  plVar4 = DAT_1401023f0;
  if (DAT_1401023f8 != 0) {
    do {
      if (*plVar4 != 0) {
        plVar2 = DAT_1401023f0 + (longlong)plVar2;
        while (plVar2 != (longlong *)0x0) {
          plVar4 = (longlong *)*plVar2;
          uVar1 = *(uint *)(plVar4 + 1);
          *plVar2 = *plVar4;
          DAT_1401023fc = DAT_1401023fc + -1;
          uVar1 = (uVar1 >> 0x10 ^ uVar1) * -0x7a143595;
          uVar1 = (uVar1 >> 0xd ^ uVar1) * -0x3d4d51cb;
          if (*plVar2 == 0) {
            uVar1 = (uVar1 >> 0x10 ^ uVar1) % DAT_1401023f8 + 1;
            plVar2 = plVar5;
            if (uVar1 < DAT_1401023f8) {
              plVar3 = DAT_1401023f0 + (int)uVar1;
              do {
                if (*plVar3 != 0) {
                  plVar2 = DAT_1401023f0 + uVar1;
                  break;
                }
                uVar1 = uVar1 + 1;
                plVar3 = plVar3 + 1;
              } while (uVar1 < DAT_1401023f8);
            }
          }
          LocalFree((HLOCAL)plVar4[2]);
          FUN_1400119c0(plVar4);
        }
        break;
      }
      uVar1 = (int)plVar2 + 1;
      plVar2 = (longlong *)(ulonglong)uVar1;
      plVar4 = plVar4 + 1;
    } while (uVar1 < DAT_1401023f8);
  }
  if (DAT_1401023f0 != (longlong *)0x0) {
    FUN_1400119c0(DAT_1401023f0);
  }
  DAT_1401023f8 = 0;
  DAT_1401023f0 = (longlong *)0x0;
  DAT_1401023fc = 0;
  DAT_140102400 = 0;
  _DAT_140102404 = 0xffffffff;
  if (DAT_140103f78 != 0) {
    FUN_140016e10();
    DAT_140103f78 = 0;
  }
  return;
}


// ==== FUN_1400085e0 @ 1400085e0  int FUN_1400085e0(char * param_1, size_t param_2, char * param_3, va_list param_4)

int FUN_1400085e0(char *param_1,size_t param_2,char *param_3,va_list param_4)

{
  int iVar1;
  
  if (param_2 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = _vsnprintf(param_1,param_2,param_3,param_4);
    if (iVar1 < 0) {
      iVar1 = _vscprintf(param_3,param_4);
    }
    param_1[param_2 - 1] = '\0';
  }
  return iVar1;
}


// ==== FUN_140008640 @ 140008640  int FUN_140008640(ushort * param_1, ushort * param_2, int param_3)

int FUN_140008640(ushort *param_1,ushort *param_2,int param_3)

{
  ushort uVar1;
  int iVar2;
  
  uVar1 = *param_1;
  iVar2 = (uint)uVar1 - (uint)*param_2;
  if (iVar2 == 0) {
    if (uVar1 == 2) {
      if (*(uint *)(param_1 + 2) < *(uint *)(param_2 + 2)) {
        return -1;
      }
      if (*(uint *)(param_1 + 2) <= *(uint *)(param_2 + 2)) {
        if ((param_3 != 0) && ((uint)param_1[1] - (uint)param_2[1] != 0)) {
          return (uint)param_1[1] - (uint)param_2[1];
        }
        return 0;
      }
    }
    else if (uVar1 == 0x17) {
      iVar2 = memcmp(param_1 + 4,param_2 + 4,0x10);
      if (iVar2 != 0) {
        return iVar2;
      }
      if ((param_3 != 0) && ((uint)param_1[1] - (uint)param_2[1] != 0)) {
        return (uint)param_1[1] - (uint)param_2[1];
      }
      return 0;
    }
    iVar2 = 1;
  }
  return iVar2;
}


// ==== FUN_140008820 @ 140008820  undefined1 FUN_140008820(byte param_1)

undefined1 FUN_140008820(byte param_1)

{
  return (&DAT_1400c0700)[param_1];
}


// ==== FUN_1400088d0 @ 1400088d0  undefined FUN_1400088d0(char * param_1)

void FUN_1400088d0(char *param_1)

{
  char *pcVar1;
  char *pcVar2;
  
  if ((param_1 != (char *)0x0) && (pcVar2 = strchr(param_1,0), pcVar2 != (char *)0x0)) {
    while (pcVar2 != param_1) {
      pcVar1 = pcVar2 + -1;
      pcVar2 = pcVar2 + -1;
      if ((*pcVar1 != ' ') && (*pcVar1 != '\t')) {
        return;
      }
      *pcVar2 = '\0';
    }
  }
  return;
}


// ==== FUN_140008930 @ 140008930  int FUN_140008930(int * param_1, int param_2)

int FUN_140008930(int *param_1,int param_2)

{
  int iVar1;
  int local_res8;
  int local_resc;
  
  if (param_2 == 0) {
    FUN_1400163c0(&local_res8);
    iVar1 = _getpid();
    iVar1 = local_resc + local_res8 + iVar1;
    *param_1 = iVar1;
    return iVar1;
  }
  *param_1 = param_2;
  return param_2;
}


// ==== FUN_1400089a0 @ 1400089a0  undefined FUN_1400089a0(uint * param_1, int param_2)

void FUN_1400089a0(uint *param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = *param_1;
  do {
    uVar1 = uVar1 * -0x3e39b193 + 0x3039 & 0x7fffffff;
  } while (param_2 <= (int)uVar1 / (int)(0x7fffffff / (longlong)param_2));
  *param_1 = uVar1;
  return;
}


// ==== FUN_1400089f0 @ 1400089f0  undefined FUN_1400089f0(undefined8 param_1, undefined8 param_2)

void FUN_1400089f0(undefined8 param_1,undefined8 param_2)

{
                    /* WARNING: Could not recover jumptable at 0x0001400089fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR_memset_140102478)(param_1,0,param_2);
  return;
}


// ==== FUN_140008a00 @ 140008a00  bool FUN_140008a00(short * param_1)

bool FUN_140008a00(short *param_1)

{
  uint uVar1;
  bool bVar2;
  
  if (*param_1 == 2) {
    uVar1 = Ordinal_14(*(undefined4 *)(param_1 + 2));
    return (uVar1 & 0xff000000) == 0x7f000000;
  }
  if (*param_1 == 0x17) {
    bVar2 = false;
    if ((*(longlong *)(param_1 + 4) == 0) &&
       (bVar2 = *(ulonglong *)(param_1 + 8) < 0x100000000000000,
       *(ulonglong *)(param_1 + 8) == 0x100000000000000)) {
      return true;
    }
    return 1 - bVar2 == (uint)(bVar2 != 0);
  }
  return false;
}


// ==== FUN_140008b90 @ 140008b90  undefined FUN_140008b90(char * param_1)

void FUN_140008b90(char *param_1)

{
  char cVar1;
  UINT UVar2;
  ulonglong uVar3;
  longlong lVar4;
  char *pcVar5;
  char *pcVar6;
  undefined1 auStack_148 [32];
  CHAR local_128 [272];
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_148;
  UVar2 = GetSystemDirectoryA(local_128,0x104);
  if (UVar2 != 0) {
    uVar3 = 0xffffffffffffffff;
    pcVar5 = param_1;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    if (~uVar3 + 1 + (ulonglong)UVar2 < 0x104) {
      lVar4 = -1;
      pcVar5 = local_128;
      do {
        pcVar6 = pcVar5;
        if (lVar4 == 0) break;
        lVar4 = lVar4 + -1;
        pcVar6 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar6;
      } while (cVar1 != '\0');
      lVar4 = -1;
      pcVar6[-1] = '\\';
      pcVar6[0] = '\0';
      pcVar5 = local_128;
      do {
        pcVar6 = pcVar5;
        if (lVar4 == 0) break;
        lVar4 = lVar4 + -1;
        pcVar6 = pcVar5 + 1;
        cVar1 = *pcVar5;
        pcVar5 = pcVar6;
      } while (cVar1 != '\0');
      lVar4 = 0;
      do {
        cVar1 = param_1[lVar4];
        pcVar6[lVar4 + -1] = cVar1;
        lVar4 = lVar4 + 1;
      } while (cVar1 != '\0');
      LoadLibraryA(local_128);
    }
  }
  __security_check_cookie(local_18 ^ (ulonglong)auStack_148);
  return;
}


// ==== FUN_140008c50 @ 140008c50  ulonglong FUN_140008c50(undefined8 param_1, uint param_2, undefined8 param_3, undefined8 param_4)

ulonglong FUN_140008c50(undefined8 param_1,uint param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  ulonglong uVar2;
  undefined4 local_res10 [6];
  
  uVar2 = Ordinal_23(param_1,param_2 & 0x7bffffff);
  if ((longlong)uVar2 < 0) {
    return 0xffffffffffffffff;
  }
  if ((param_2 >> 0x1a & 1) != 0) {
    local_res10[0] = 1;
    iVar1 = Ordinal_10(uVar2,0x8004667e,local_res10);
    if (iVar1 == -1) {
      FUN_140019120(uVar2,"fcntl(%d, F_GETFL)",uVar2 & 0xffffffff,param_4);
      Ordinal_3(uVar2);
      return 0xffffffffffffffff;
    }
  }
  return uVar2;
}


// ==== FUN_140008cd0 @ 140008cd0  ulonglong FUN_140008cd0(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

ulonglong FUN_140008cd0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  ulonglong uVar1;
  undefined8 uVar2;
  uint uVar3;
  
  uVar3 = (uint)param_4;
  uVar1 = Ordinal_1();
  if (((-1 < (longlong)uVar1) && ((uVar3 >> 0x1a & 1) != 0)) &&
     (uVar2 = FUN_140007480(uVar1,param_2,param_3,param_4), (int)uVar2 < 0)) {
    Ordinal_3(uVar1);
    return 0xffffffffffffffff;
  }
  return uVar1;
}


// ==== FUN_140008d40 @ 140008d40  undefined FUN_140008d40(void)

void FUN_140008d40(void)

{
  FUN_140019610();
  FUN_140008490();
  return;
}


// ==== FUN_140008d60 @ 140008d60  undefined FUN_140008d60(int param_1, ulonglong param_2, int param_3, longlong * param_4)

void FUN_140008d60(int param_1,ulonglong param_2,int param_3,longlong *param_4)

{
  undefined4 uVar1;
  int iVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  undefined1 auStack_78 [32];
  int local_58 [2];
  undefined8 local_50;
  undefined8 local_48;
  short local_40;
  short local_3e;
  int local_3c;
  ulonglong local_30;
  
  local_30 = DAT_140103510 ^ (ulonglong)auStack_78;
  lVar5 = -1;
  lVar4 = -1;
  if ((param_3 != 0) || ((param_1 != 2 && (param_1 != 1)))) {
    Ordinal_112(0x273f);
    goto LAB_140008f2d;
  }
  if (param_4 == (longlong *)0x0) {
    Ordinal_112(0x2726);
    goto LAB_140008f2d;
  }
  lVar3 = Ordinal_23(2,param_2,0);
  if (lVar3 < 0) goto LAB_140008f2d;
  local_50 = 2;
  local_48 = 0;
  uVar1 = Ordinal_8(0x7f000001);
  local_50 = CONCAT44(uVar1,(undefined4)local_50) & 0xffffffff0000ffff;
  iVar2 = Ordinal_2(lVar3,&local_50,0x10);
  if (((iVar2 == -1) || (iVar2 = Ordinal_13(lVar3,1), iVar2 == -1)) ||
     (lVar5 = Ordinal_23(2,param_2 & 0xffffffff,0), lVar5 < 0)) {
LAB_140008f4b:
    uVar1 = Ordinal_111();
  }
  else {
    local_58[0] = 0x10;
    iVar2 = Ordinal_6(lVar3,&local_40,local_58);
    if (iVar2 == -1) goto LAB_140008f4b;
    if (local_58[0] != 0x10) goto LAB_140008f44;
    iVar2 = Ordinal_4(lVar5,&local_40,0x10);
    if (iVar2 == -1) goto LAB_140008f4b;
    local_58[0] = 0x10;
    lVar4 = Ordinal_1(lVar3,&local_50,local_58);
    if (lVar4 < 0) goto LAB_140008f4b;
    if (local_58[0] == 0x10) {
      iVar2 = Ordinal_6(lVar5,&local_40,local_58);
      if (iVar2 == -1) goto LAB_140008f4b;
      if (((local_58[0] == 0x10) && ((short)local_50 == local_40)) &&
         ((local_50._4_4_ == local_3c && (local_50._2_2_ == local_3e)))) {
        Ordinal_3(lVar3);
        *param_4 = lVar5;
        param_4[1] = lVar4;
        goto LAB_140008f2d;
      }
    }
LAB_140008f44:
    uVar1 = 0x2745;
  }
  if (lVar3 != -1) {
    Ordinal_3(lVar3);
  }
  if (lVar5 != -1) {
    Ordinal_3(lVar5);
  }
  if (lVar4 != -1) {
    Ordinal_3(lVar4);
  }
  Ordinal_112(uVar1);
LAB_140008f2d:
  __security_check_cookie(local_30 ^ (ulonglong)auStack_78);
  return;
}


// ==== FUN_140008fa0 @ 140008fa0  undefined8 FUN_140008fa0(void)

undefined8 FUN_140008fa0(void)

{
  longlong *plVar1;
  longlong lVar2;
  int iVar3;
  HMODULE hModule;
  FARPROC pFVar4;
  void *pvVar5;
  INT_PTR IVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  void *pvVar9;
  uint local_res8 [2];
  
  hModule = (HMODULE)FUN_140008b90("ihplapi.dll");
  pvVar5 = (void *)0x0;
  uVar7 = 0xffffffff;
  if (hModule == (HMODULE)0x0) {
    return 0xffffffff;
  }
  pFVar4 = GetProcAddress(hModule,"GetAdaptersAddresses");
  uVar8 = 0xffffffff;
  if (pFVar4 != (FARPROC)0x0) {
    local_res8[0] = 0x3c00;
    pvVar5 = FUN_140011830(0x3c00);
    uVar8 = uVar7;
    if (pvVar5 != (void *)0x0) {
      IVar6 = (*pFVar4)(0,0xe,0,pvVar5,local_res8);
      iVar3 = (int)IVar6;
      if (iVar3 == 0x6f) {
        FUN_1400119c0(pvVar5);
        pvVar5 = FUN_140011830((ulonglong)local_res8[0]);
        if (pvVar5 == (void *)0x0) goto LAB_14000908d;
        IVar6 = (*pFVar4)(0,0xe,0,pvVar5,local_res8);
        iVar3 = (int)IVar6;
      }
      pvVar9 = pvVar5;
      if (iVar3 == 0) {
        do {
          for (lVar2 = *(longlong *)((longlong)pvVar9 + 0x18); lVar2 != 0;
              lVar2 = *(longlong *)(lVar2 + 8)) {
            FUN_140007730(*(short **)(lVar2 + 0x10));
          }
          plVar1 = (longlong *)((longlong)pvVar9 + 8);
          pvVar9 = (void *)*plVar1;
        } while ((void *)*plVar1 != (void *)0x0);
        uVar8 = 0;
      }
    }
  }
LAB_14000908d:
  FreeLibrary(hModule);
  if (pvVar5 != (void *)0x0) {
    FUN_1400119c0(pvVar5);
  }
  return uVar8;
}


// ==== FUN_1400090c0 @ 1400090c0  int * FUN_1400090c0(ushort * param_1, int param_2, undefined8 * param_3)

int * FUN_1400090c0(ushort *param_1,int param_2,undefined8 *param_3)

{
  ushort uVar1;
  int *piVar2;
  int *piVar3;
  size_t _Size;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  
  _Size = (size_t)param_2;
  if ((*(int *)(param_3 + 1) == 0) && (*(int *)((longlong)param_3 + 0xc) == 0)) {
    local_38 = *param_3;
    local_28 = param_3[2];
    local_20 = param_3[3];
    local_18 = param_3[4];
    local_10 = param_3[5];
    local_30 = 0x600000001;
    piVar2 = FUN_1400090c0(param_1,param_2,&local_38);
    if (piVar2 != (int *)0x0) {
      local_30 = 0x1100000002;
      piVar3 = FUN_1400090c0(param_1,param_2,&local_38);
      if (piVar3 != (int *)0x0) {
        *(int **)(piVar2 + 10) = piVar3;
        return piVar2;
      }
      FUN_140007ca0(piVar2);
    }
  }
  else {
    piVar2 = (int *)FUN_140011850(1,_Size + 0x30);
    if (piVar2 != (int *)0x0) {
      *(int **)(piVar2 + 8) = piVar2 + 0xc;
      memcpy(piVar2 + 0xc,param_1,_Size);
      *(size_t *)(piVar2 + 4) = _Size;
      uVar1 = *param_1;
      *piVar2 = -0x80000000;
      piVar2[1] = (uint)uVar1;
      piVar2[2] = *(int *)(param_3 + 1);
      piVar2[3] = *(int *)((longlong)param_3 + 0xc);
      return piVar2;
    }
  }
  return (int *)0x0;
}


// ==== FUN_1400091e0 @ 1400091e0  undefined FUN_1400091e0(longlong * param_1, undefined8 * param_2)

void FUN_1400091e0(longlong *param_1,undefined8 *param_2)

{
  longlong lVar1;
  ulonglong uVar2;
  uint uVar3;
  
  if ((*param_1 == 0) || (*(uint *)(param_1 + 2) <= *(uint *)((longlong)param_1 + 0xc))) {
    FUN_140008010(param_1,*(int *)((longlong)param_1 + 0xc) + 1);
  }
  *(int *)((longlong)param_1 + 0xc) = *(int *)((longlong)param_1 + 0xc) + 1;
  uVar3 = (*(uint *)(param_2 + 1) >> 0x10 ^ *(uint *)(param_2 + 1)) * -0x7a143595;
  lVar1 = *param_1;
  uVar3 = (uVar3 >> 0xd ^ uVar3) * -0x3d4d51cb;
  uVar2 = (ulonglong)(uVar3 >> 0x10 ^ uVar3) % (ulonglong)*(uint *)(param_1 + 1);
  *param_2 = *(undefined8 *)(lVar1 + uVar2 * 8);
  *(undefined8 **)(lVar1 + uVar2 * 8) = param_2;
  return;
}


// ==== FUN_140009250 @ 140009250  int FUN_140009250(char * param_1, size_t param_2, char * param_3, undefined8 param_4)

int FUN_140009250(char *param_1,size_t param_2,char *param_3,undefined8 param_4)

{
  int iVar1;
  undefined8 local_res20;
  
  if (param_2 == 0) {
    return 0;
  }
  local_res20 = param_4;
  iVar1 = _vsnprintf(param_1,param_2,param_3,(va_list)&local_res20);
  if (iVar1 < 0) {
    iVar1 = _vscprintf(param_3,(va_list)&local_res20);
  }
  param_1[param_2 - 1] = '\0';
  return iVar1;
}


// ==== FUN_1400092b0 @ 1400092b0  undefined FUN_1400092b0(int param_1, byte * param_2, char * param_3, size_t param_4)

void FUN_1400092b0(int param_1,byte *param_2,char *param_3,size_t param_4)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  uint uVar8;
  char *pcVar9;
  ulonglong uVar10;
  char *pcVar11;
  int iVar12;
  ulonglong uVar13;
  undefined1 auStack_e8 [32];
  uint local_c8;
  uint local_c0;
  uint local_b8;
  uint local_b0;
  undefined4 local_a8;
  char *local_a0;
  ushort local_98 [8];
  char local_88 [64];
  ulonglong local_48 [2];
  
  local_48[0] = DAT_140103510 ^ (ulonglong)auStack_e8;
  local_a0 = param_3;
  if (param_1 == 2) {
    uVar3 = Ordinal_14(*(undefined4 *)param_2);
    local_b8 = uVar3 & 0xff;
    local_c0 = uVar3 >> 8 & 0xff;
    local_c8 = uVar3 >> 0x10 & 0xff;
    FUN_140009250(param_3,param_4,"%d.%d.%d.%d",(ulonglong)(uVar3 >> 0x18));
  }
  else if (param_1 == 0x17) {
    local_98[0] = (ushort)*param_2 * 0x100 + (ushort)param_2[1];
    local_98[1] = (ushort)param_2[2] * 0x100 + (ushort)param_2[3];
    local_a8 = 0x100;
    local_98[2] = (ushort)param_2[4] * 0x100 + (ushort)param_2[5];
    uVar4 = 0;
    local_98[3] = (ushort)param_2[6] * 0x100 + (ushort)param_2[7];
    uVar13 = 0xffffffff;
    local_98[4] = (ushort)param_2[8] * 0x100 + (ushort)param_2[9];
    local_98[5] = (ushort)param_2[10] * 0x100 + (ushort)param_2[0xb];
    local_98[6] = (ushort)param_2[0xc] * 0x100 + (ushort)param_2[0xd];
    bVar2 = param_2[0xf];
    local_98[7] = (ushort)param_2[0xe] * 0x100 + (ushort)bVar2;
    uVar7 = uVar4;
    uVar5 = uVar4;
    uVar10 = uVar4;
    if (((((local_98[0] == 0) && (local_98[1] == 0)) && (local_98[2] == 0)) &&
        ((local_98[3] == 0 && (local_98[4] == 0)))) &&
       (((local_98[5] == 0 && ((local_98[6] != 0 && (local_98[7] != 0)))) || (local_98[5] == 0xffff)
        ))) {
      local_c8 = (uint)param_2[0xc];
      local_c0 = (uint)param_2[0xd];
      local_b8 = (uint)param_2[0xe];
      if (local_98[5] == 0) {
        uVar4 = (ulonglong)local_c8;
        local_c8 = local_c0;
        local_c0 = local_b8;
        local_b8 = (uint)bVar2;
        FUN_140009250(local_88,0x40,"::%d.%d.%d.%d",uVar4);
      }
      else {
        local_b0 = (uint)bVar2;
        FUN_140009250(local_88,0x40,"::%x:%d.%d.%d.%d",(ulonglong)local_98[5]);
      }
      uVar4 = 0xffffffffffffffff;
      pcVar9 = local_88;
      do {
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar9 + 1;
      } while (cVar1 != '\0');
    }
    else {
      do {
        uVar3 = (uint)uVar5;
        if (local_98[uVar7] == 0) {
          uVar8 = 1;
          while( true ) {
            uVar7 = uVar7 + 1;
            uVar3 = uVar3 + 1;
            uVar6 = (ulonglong)uVar3;
            if ((7 < (longlong)uVar7) || (local_98[uVar7] != 0)) break;
            uVar8 = uVar8 + 1;
          }
          if ((int)uVar10 < (int)uVar8) {
            uVar10 = (ulonglong)uVar8;
            uVar13 = uVar5;
          }
        }
        else {
          uVar6 = (ulonglong)(uVar3 + 1);
          uVar7 = uVar7 + 1;
        }
        uVar5 = uVar6;
      } while ((int)uVar6 < 8);
      pcVar9 = local_88;
      iVar12 = (int)uVar13;
      if ((int)uVar10 < 2) {
        iVar12 = -1;
      }
      do {
        if ((local_98[uVar4] == 0) && ((longlong)iVar12 == uVar4)) {
          if (uVar4 == 0) {
            *pcVar9 = ':';
            pcVar9 = pcVar9 + 1;
          }
          *pcVar9 = ':';
          pcVar9 = pcVar9 + 1;
          for (; ((longlong)uVar4 < 8 && (local_98[uVar4] == 0)); uVar4 = uVar4 + 1) {
          }
          uVar4 = uVar4 - 1;
        }
        else {
          FUN_140009250(pcVar9,(longlong)local_48 - (longlong)pcVar9,"%x",(ulonglong)local_98[uVar4]
                       );
          uVar7 = 0xffffffffffffffff;
          pcVar11 = pcVar9;
          do {
            if (uVar7 == 0) break;
            uVar7 = uVar7 - 1;
            cVar1 = *pcVar11;
            pcVar11 = pcVar11 + 1;
          } while (cVar1 != '\0');
          pcVar9 = pcVar9 + (~uVar7 - 1);
          if (uVar4 != 7) {
            *pcVar9 = ':';
            pcVar9 = pcVar9 + 1;
          }
        }
        uVar4 = uVar4 + 1;
      } while ((longlong)uVar4 < 8);
      uVar4 = 0xffffffffffffffff;
      *pcVar9 = '\0';
      pcVar9 = local_88;
      do {
        param_3 = local_a0;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar9 + 1;
      } while (cVar1 != '\0');
    }
    if (~uVar4 - 1 <= param_4) {
      FUN_140019a40(param_3,local_88,param_4);
    }
  }
  __security_check_cookie(local_48[0] ^ (ulonglong)auStack_e8);
  return;
}


// ==== FUN_140009660 @ 140009660  undefined FUN_140009660(int param_1, byte * param_2, undefined4 * param_3)

void FUN_140009660(int param_1,byte *param_2,undefined4 *param_3)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  long lVar4;
  byte *pbVar5;
  ulonglong uVar6;
  int iVar7;
  byte *pbVar8;
  byte *_Src;
  int iVar9;
  undefined2 *puVar10;
  undefined1 auStack_a8 [32];
  uint *local_88;
  uint *local_80;
  undefined1 *local_78;
  undefined1 local_68 [4];
  uint local_64;
  uint local_60;
  uint local_5c;
  undefined8 local_58;
  undefined2 local_50;
  undefined1 local_4e;
  undefined1 local_4c;
  undefined1 local_4a;
  undefined1 local_48;
  undefined1 local_46;
  ushort local_44;
  ushort local_42;
  ulonglong local_40;
  
  local_40 = DAT_140103510 ^ (ulonglong)auStack_a8;
  if (param_1 == 2) {
    local_78 = local_68;
    local_80 = (uint *)&local_58;
    local_88 = &local_60;
    iVar2 = sscanf((char *)param_2,"%u.%u.%u.%u%c");
    if ((((iVar2 == 4) && (local_5c < 0x100)) && (local_64 < 0x100)) &&
       ((local_60 < 0x100 && ((uint)local_58 < 0x100)))) {
      uVar3 = Ordinal_8(((local_5c << 8 | local_64) << 8 | local_60) << 8 | (uint)local_58);
      *param_3 = uVar3;
    }
  }
  else if (param_1 == 0x17) {
    iVar2 = -1;
    iVar9 = 0;
    pbVar5 = (byte *)strchr((char *)param_2,0x2e);
    if (pbVar5 != param_2) {
      pbVar8 = pbVar5;
      if (pbVar5 == (byte *)0x0) {
        uVar6 = 0xffffffffffffffff;
        pbVar8 = param_2;
        do {
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          bVar1 = *pbVar8;
          pbVar8 = pbVar8 + 1;
        } while (bVar1 != 0);
        _Src = param_2 + (~uVar6 - 1);
      }
      else {
        do {
          _Src = pbVar8;
          pbVar8 = _Src + -1;
          if (pbVar8 < param_2) break;
        } while ((*(uint *)(&DAT_1400c0678 + (ulonglong)(*pbVar8 >> 5) * 4) >> (*pbVar8 & 0x1f) & 1)
                 != 0);
        local_78 = local_68;
        local_80 = &local_5c;
        local_88 = &local_64;
        iVar9 = sscanf((char *)_Src,"%u.%u.%u.%u%c");
        if (((iVar9 != 4) || (0xff < (uint)local_58)) ||
           ((0xff < local_60 || ((0xff < local_64 || (0xff < local_5c)))))) goto LAB_140009958;
        iVar9 = 2;
        local_44 = (short)(uint)local_58 << 8 | (ushort)local_60;
        local_42 = (short)local_64 << 8 | (ushort)local_5c;
      }
      iVar7 = 0;
      if (param_2 < _Src) {
        puVar10 = &local_50;
        iVar2 = -1;
        do {
          if (7 < iVar7) goto LAB_140009958;
          bVar1 = *param_2;
          if ((*(uint *)(&DAT_1400c0658 + (ulonglong)(bVar1 >> 5) * 4) >> (bVar1 & 0x1f) & 1) == 0)
          {
            if (bVar1 != 0x3a) goto LAB_140009958;
            if ((iVar7 < 1) || (iVar2 != -1)) {
              if ((iVar7 != 0) || ((param_2[1] != 0x3a || (iVar2 != -1)))) goto LAB_140009958;
              iVar2 = 0;
              param_2 = param_2 + 2;
            }
            else {
              param_2 = param_2 + 1;
              iVar2 = iVar7;
            }
          }
          else {
            lVar4 = strtol((char *)param_2,(char **)&local_58,0x10);
            pbVar8 = (byte *)CONCAT44(local_58._4_4_,(uint)local_58);
            if ((((param_2 + 4 < pbVar8) || (pbVar8 == param_2)) || (lVar4 < 0)) ||
               (0x10000 < lVar4)) goto LAB_140009958;
            *puVar10 = (short)lVar4;
            puVar10 = puVar10 + 1;
            iVar7 = iVar7 + 1;
            iVar9 = iVar9 + 1;
            if ((*pbVar8 != 0x3a) && (pbVar8 != _Src)) goto LAB_140009958;
            param_2 = pbVar8 + 1;
          }
        } while (param_2 < _Src);
      }
      if (iVar9 < 9) {
        if (iVar9 == 8) {
          if (iVar2 != -1) goto LAB_140009958;
        }
        else {
          if ((iVar9 < 8) && (iVar2 == -1)) goto LAB_140009958;
          if (-1 < iVar2) {
            iVar7 = (iVar9 - (-(uint)(pbVar5 != (byte *)0x0) & 2)) - iVar2;
            if (iVar7 < 0) goto LAB_140009958;
            memmove(&local_50 + ((8 - iVar9) + iVar2),&local_50 + iVar2,(longlong)iVar7 * 2);
            memset(&local_50 + iVar2,0,(longlong)(8 - iVar9) * 2);
          }
        }
        *(char *)param_3 = (char)((ushort)local_50 >> 8);
        *(undefined1 *)((longlong)param_3 + 1) = (undefined1)local_50;
        *(char *)((longlong)param_3 + 2) = (char)((ushort)_local_4e >> 8);
        *(undefined1 *)((longlong)param_3 + 3) = local_4e;
        *(char *)(param_3 + 1) = (char)((ushort)_local_4c >> 8);
        *(undefined1 *)((longlong)param_3 + 5) = local_4c;
        *(char *)((longlong)param_3 + 6) = (char)((ushort)_local_4a >> 8);
        *(undefined1 *)((longlong)param_3 + 7) = local_4a;
        *(char *)(param_3 + 2) = (char)((ushort)_local_48 >> 8);
        *(undefined1 *)((longlong)param_3 + 9) = local_48;
        *(char *)((longlong)param_3 + 10) = (char)((ushort)_local_46 >> 8);
        *(undefined1 *)((longlong)param_3 + 0xb) = local_46;
        *(char *)(param_3 + 3) = (char)(local_44 >> 8);
        *(undefined1 *)((longlong)param_3 + 0xd) = (undefined1)local_44;
        *(char *)((longlong)param_3 + 0xe) = (char)(local_42 >> 8);
        *(undefined1 *)((longlong)param_3 + 0xf) = (undefined1)local_42;
      }
    }
  }
LAB_140009958:
  __security_check_cookie(local_40 ^ (ulonglong)auStack_a8);
  return;
}


// ==== FUN_140009aa0 @ 140009aa0  undefined FUN_140009aa0(byte * param_1, undefined8 * param_2, int * param_3)

void FUN_140009aa0(byte *param_1,undefined8 *param_2,int *param_3)

{
  bool bVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  char *pcVar6;
  char *pcVar7;
  char *_Str;
  size_t _Size;
  char *pcVar8;
  undefined1 auStack_148 [32];
  uint *local_128;
  uint *local_120;
  undefined1 *local_118;
  undefined1 local_108 [4];
  uint local_104;
  uint local_100;
  uint local_fc;
  uint local_f8;
  undefined8 local_f0;
  undefined8 local_e8;
  undefined8 local_e0;
  undefined4 local_d8;
  byte local_c8 [128];
  ulonglong local_48;
  
  local_48 = DAT_140103510 ^ (ulonglong)auStack_148;
  pcVar6 = strchr((char *)param_1,0x3a);
  pcVar8 = (char *)0x0;
  if (*param_1 == 0x5b) {
    pcVar6 = strchr((char *)param_1,0x5d);
    if ((pcVar6 == (char *)0x0) || (iVar3 = ((int)pcVar6 - (int)param_1) + -1, 0x7f < iVar3))
    goto LAB_140009bc0;
    memcpy(local_c8,param_1 + 1,(longlong)iVar3);
    local_c8[iVar3] = 0;
    if (pcVar6[1] == ':') {
      bVar1 = true;
      _Str = pcVar6 + 2;
    }
    else {
      bVar1 = true;
      _Str = pcVar8;
    }
LAB_140009ba1:
    param_1 = local_c8;
    if (_Str == (char *)0x0) goto LAB_140009be5;
    uVar4 = atoi(_Str);
    pcVar8 = (char *)(ulonglong)uVar4;
    if (0xfffe < uVar4 - 1) goto LAB_140009bc0;
  }
  else {
    bVar1 = false;
    if (pcVar6 != (char *)0x0) {
      _Str = pcVar6 + 1;
      pcVar7 = strchr(_Str,0x3a);
      if (pcVar7 == (char *)0x0) {
        _Size = (longlong)pcVar6 - (longlong)param_1;
        if (0x7f < (longlong)_Size) goto LAB_140009bc0;
        memcpy(local_c8,param_1,_Size);
        local_c8[_Size] = 0;
        goto LAB_140009ba1;
      }
      bVar1 = true;
    }
LAB_140009be5:
    if (param_1 == (byte *)0x0) goto LAB_140009bc0;
  }
  local_e8 = 0;
  if (bVar1) {
    local_e0 = 0;
    local_d8 = 0;
    local_f0 = 0x17;
    uVar2 = Ordinal_9();
    local_f0._0_4_ = CONCAT22(uVar2,(undefined2)local_f0);
    iVar3 = FUN_140009660(0x17,param_1,(undefined4 *)&local_e8);
    if ((iVar3 == 1) && (0x1b < *param_3)) {
      memset(param_2,0,(longlong)*param_3);
      *param_2 = local_f0;
      param_2[1] = local_e8;
      param_2[2] = local_e0;
      *(undefined4 *)(param_2 + 3) = local_d8;
      *param_3 = 0x1c;
    }
  }
  else {
    local_f0 = 2;
    uVar2 = Ordinal_9((ulonglong)pcVar8 & 0xffff);
    local_f0._0_4_ = CONCAT22(uVar2,(undefined2)local_f0);
    local_118 = local_108;
    local_120 = &local_100;
    local_128 = &local_104;
    iVar3 = sscanf((char *)param_1,"%u.%u.%u.%u%c");
    if ((((iVar3 == 4) && (local_f8 < 0x100)) && (local_fc < 0x100)) &&
       ((local_104 < 0x100 && (local_100 < 0x100)))) {
      uVar5 = Ordinal_8(((local_f8 << 8 | local_fc) << 8 | local_104) << 8 | local_100);
      local_f0 = CONCAT44(uVar5,(undefined4)local_f0);
      if (0xf < *param_3) {
        memset(param_2,0,(longlong)*param_3);
        *param_2 = local_f0;
        param_2[1] = local_e8;
        *param_3 = 0x10;
      }
    }
  }
LAB_140009bc0:
  __security_check_cookie(local_48 ^ (ulonglong)auStack_148);
  return;
}


// ==== FUN_140009d70 @ 140009d70  undefined FUN_140009d70(ushort * param_1, char * param_2, size_t param_3)

void FUN_140009d70(ushort *param_1,char *param_2,size_t param_3)

{
  ushort uVar1;
  uint uVar2;
  longlong lVar3;
  char *pcVar4;
  undefined1 auStack_e8 [32];
  uint local_c8;
  uint local_c0;
  uint local_b8;
  char local_a8 [128];
  ulonglong local_28;
  
  local_28 = DAT_140103510 ^ (ulonglong)auStack_e8;
  if (*param_1 == 2) {
    uVar2 = Ordinal_14(*(undefined4 *)(param_1 + 2));
    local_c0 = uVar2 >> 8 & 0xff;
    local_b8 = uVar2 & 0xff;
    local_c8 = uVar2 >> 0x10 & 0xff;
    uVar2 = FUN_140009250(local_a8,0x80,"%d.%d.%d.%d",(ulonglong)(uVar2 >> 0x18));
    if (((int)uVar2 < 0) || (0x7f < uVar2)) {
      pcVar4 = (char *)0x0;
    }
    else {
      pcVar4 = local_a8;
    }
    uVar1 = Ordinal_15(param_1[1]);
    if (pcVar4 != (char *)0x0) {
      local_c8 = (uint)uVar1;
      FUN_140009250(param_2,param_3,"%s:%d",local_a8);
      goto LAB_140009e9a;
    }
  }
  else if (*param_1 == 0x17) {
    lVar3 = FUN_1400092b0(0x17,(byte *)(param_1 + 4),local_a8,0x80);
    uVar1 = Ordinal_15(param_1[1]);
    if (lVar3 != 0) {
      local_c8 = (uint)uVar1;
      FUN_140009250(param_2,param_3,"[%s]:%d",local_a8);
      goto LAB_140009e9a;
    }
  }
  FUN_140009250(param_2,param_3,"<addr with socktype %d>",(ulonglong)*param_1);
LAB_140009e9a:
  __security_check_cookie(local_28 ^ (ulonglong)auStack_e8);
  return;
}


// ==== FUN_140009ed0 @ 140009ed0  undefined FUN_140009ed0(int param_1)

void FUN_140009ed0(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  longlong lVar5;
  undefined1 auStack_d8 [32];
  uint *local_b8;
  uint *local_b0;
  undefined1 *local_a8;
  undefined1 local_98 [4];
  undefined4 local_94;
  undefined4 local_90;
  uint local_8c;
  uint local_88;
  uint local_84;
  uint local_80 [2];
  undefined8 local_78;
  undefined8 local_70;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined4 local_50;
  short local_48 [8];
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined4 local_20;
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_d8;
  local_94 = 0x10;
  local_90 = 0x1c;
  if (((DAT_140103f58 == 0) || (param_1 != 0)) && (uVar4 = FUN_140008fa0(), (int)uVar4 != 0)) {
    local_70 = 0;
    local_78 = 2;
    uVar1 = Ordinal_9(0x35);
    local_78._0_4_ = CONCAT22(uVar1,(undefined2)local_78);
    local_a8 = local_98;
    local_b0 = &local_84;
    local_b8 = local_80;
    iVar2 = sscanf("18.244.0.188","%u.%u.%u.%u%c");
    if (((iVar2 == 4) && (local_88 < 0x100)) &&
       ((local_8c < 0x100 && ((local_80[0] < 0x100 && (local_84 < 0x100)))))) {
      uVar3 = Ordinal_8(((local_88 << 8 | local_8c) << 8 | local_80[0]) << 8 | local_84);
      local_78 = CONCAT44(uVar3,(undefined4)local_78);
    }
    local_60 = 0;
    local_58 = 0;
    local_50 = 0;
    local_68 = 0x17;
    uVar1 = Ordinal_9(0x35);
    local_68._0_4_ = CONCAT22(uVar1,(undefined2)local_68);
    FUN_140009660(0x17,(byte *)"2001:4860:b002::68",(undefined4 *)&local_60);
    local_48[0] = 0;
    local_48[1] = 0;
    local_48[2] = 0;
    local_48[3] = 0;
    local_48[4] = 0;
    local_48[5] = 0;
    local_48[6] = 0;
    local_48[7] = 0;
    local_38 = 0;
    local_30 = 0;
    local_28 = 0;
    local_20 = 0;
    lVar5 = Ordinal_23(2,2,0x11);
    if (-1 < lVar5) {
      iVar2 = Ordinal_4(lVar5,&local_78,0x10);
      if ((iVar2 == 0) && (iVar2 = Ordinal_6(lVar5,local_48,&local_94), iVar2 == 0)) {
        FUN_140007730(local_48);
      }
      Ordinal_3(lVar5);
    }
    lVar5 = Ordinal_23(0x17,2,0x11);
    if (-1 < lVar5) {
      iVar2 = Ordinal_4(lVar5,&local_68,0x1c);
      if ((iVar2 == 0) && (iVar2 = Ordinal_6(lVar5,&local_38,&local_90), iVar2 == 0)) {
        FUN_140007730((short *)&local_38);
      }
      Ordinal_3(lVar5);
    }
  }
  __security_check_cookie(local_18 ^ (ulonglong)auStack_d8);
  return;
}


// ==== FUN_14000a150 @ 14000a150  undefined FUN_14000a150(byte * param_1, char * param_2, byte * param_3, undefined8 * param_4, undefined4 * param_5)

void FUN_14000a150(byte *param_1,char *param_2,byte *param_3,undefined8 *param_4,undefined4 *param_5
                  )

{
  longlong lVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined8 *puVar7;
  int *piVar8;
  int *piVar9;
  int *piVar10;
  undefined1 auStack_d8 [32];
  uint *local_b8;
  uint *local_b0;
  undefined1 *local_a8;
  undefined1 local_98 [4];
  uint local_94;
  uint local_90;
  uint local_8c;
  uint local_88;
  ushort local_80 [2];
  undefined4 uStack_7c;
  undefined8 local_78;
  ushort local_70 [4];
  undefined8 local_68;
  undefined8 local_60;
  undefined4 local_58;
  ulonglong local_50;
  
  local_50 = DAT_140103510 ^ (ulonglong)auStack_d8;
  piVar9 = (int *)0x0;
  if (((param_1 != (byte *)0x0) || (param_2 != (char *)0x0)) &&
     ((iVar6 = *(int *)(param_3 + 4), iVar6 == 0 || ((iVar6 == 2 || (iVar6 == 0x17)))))) {
    if ((*(int *)(param_3 + 0xc) == 0) && (iVar6 = *(int *)(param_3 + 8), iVar6 != 0)) {
      if (iVar6 == 2) {
        param_3[0xc] = 0x11;
        param_3[0xd] = 0;
        param_3[0xe] = 0;
        param_3[0xf] = 0;
      }
      else if (iVar6 == 1) {
        param_3[0xc] = 6;
        param_3[0xd] = 0;
        param_3[0xe] = 0;
        param_3[0xf] = 0;
      }
    }
    if ((*(int *)(param_3 + 8) == 0) && (iVar6 = *(int *)(param_3 + 0xc), iVar6 != 0)) {
      if (iVar6 == 0x11) {
        param_3[8] = 2;
        param_3[9] = 0;
        param_3[10] = 0;
        param_3[0xb] = 0;
      }
      else if (iVar6 == 6) {
        param_3[8] = 1;
        param_3[9] = 0;
        param_3[10] = 0;
        param_3[0xb] = 0;
      }
    }
    iVar6 = *(int *)(param_3 + 0xc);
    if (iVar6 == 0) {
      piVar8 = (int *)0x0;
    }
    else if (iVar6 == 6) {
      piVar8 = (int *)&DAT_1400c093c;
    }
    else if (iVar6 == 0x11) {
      piVar8 = (int *)&DAT_1400c0940;
    }
    else {
      puVar7 = (undefined8 *)Ordinal_54();
      piVar8 = piVar9;
      if (puVar7 != (undefined8 *)0x0) {
        piVar8 = (int *)*puVar7;
      }
    }
    piVar10 = piVar9;
    if (param_2 != (char *)0x0) {
      uVar4 = FUN_1400078a0(param_2,piVar8,param_3);
      piVar10 = (int *)(ulonglong)uVar4;
      if ((int)uVar4 < 0) goto LAB_14000a4f7;
    }
    if (param_1 == (byte *)0x0) {
      piVar8 = piVar9;
      if (*(int *)(param_3 + 4) != 2) {
        local_70[0] = 0x17;
        local_70[1] = 0;
        local_70[2] = 0;
        local_70[3] = 0;
        local_68 = 0;
        local_60 = 0;
        local_58 = 0;
        uVar3 = Ordinal_9((ulonglong)piVar10 & 0xffff);
        local_70[1] = uVar3;
        uVar2 = local_60._7_1_;
        if ((*param_3 & 1) == 0) {
          uVar2 = 1;
        }
        local_60 = CONCAT17(uVar2,(undefined7)local_60);
        piVar8 = FUN_1400090c0(local_70,0x1c,(undefined8 *)param_3);
        if (piVar8 == (int *)0x0) goto LAB_14000a4f7;
      }
      if (*(int *)(param_3 + 4) != 0x17) {
        local_78 = 0;
        _local_80 = 2;
        uVar3 = Ordinal_9((ulonglong)piVar10 & 0xffff);
        local_80 = (ushort  [2])CONCAT22(uVar3,local_80[0]);
        if ((*param_3 & 1) == 0) {
          uVar5 = Ordinal_8(0x7f000001);
          _local_80 = CONCAT44(uVar5,local_80);
        }
        piVar9 = FUN_1400090c0(local_80,0x10,(undefined8 *)param_3);
        if (piVar9 == (int *)0x0) {
          if (piVar8 != (int *)0x0) {
            FUN_140007ca0(piVar8);
          }
          goto LAB_14000a4f7;
        }
      }
      if (piVar9 != (int *)0x0) {
        lVar1 = *(longlong *)(piVar9 + 10);
        piVar10 = piVar9;
        while (lVar1 != 0) {
          piVar10 = *(int **)(piVar10 + 10);
          lVar1 = *(longlong *)(piVar10 + 10);
        }
        *(int **)(piVar10 + 10) = piVar8;
        piVar8 = piVar9;
      }
      *param_4 = piVar8;
    }
    else {
      if ((*(int *)(param_3 + 4) == 0x17) || (*(int *)(param_3 + 4) == 0)) {
        local_70[0] = 0;
        local_70[1] = 0;
        local_70[2] = 0;
        local_70[3] = 0;
        local_68 = 0;
        local_60 = 0;
        local_58 = 0;
        iVar6 = FUN_140009660(0x17,param_1,(undefined4 *)&local_68);
        if (iVar6 == 1) {
          local_70[0] = 0x17;
          uVar3 = Ordinal_9((ulonglong)piVar10 & 0xffff);
          local_70[1] = uVar3;
          piVar9 = FUN_1400090c0(local_70,0x1c,(undefined8 *)param_3);
          *param_4 = piVar9;
          goto LAB_14000a4f7;
        }
      }
      if ((*(int *)(param_3 + 4) == 2) || (*(int *)(param_3 + 4) == 0)) {
        _local_80 = 0;
        local_78 = 0;
        local_a8 = local_98;
        local_b0 = &local_90;
        local_b8 = &local_94;
        iVar6 = sscanf((char *)param_1,"%u.%u.%u.%u%c");
        if (((iVar6 == 4) && (((local_88 < 0x100 && (local_8c < 0x100)) && (local_94 < 0x100)))) &&
           (local_90 < 0x100)) {
          uVar5 = Ordinal_8(((local_88 << 8 | local_8c) << 8 | local_94) << 8 | local_90);
          _local_80 = CONCAT44(uVar5,local_80);
          _local_80 = CONCAT62(stack0xffffffffffffff82,2);
          uVar3 = Ordinal_9((ulonglong)piVar10 & 0xffff);
          local_80 = (ushort  [2])CONCAT22(uVar3,local_80[0]);
          piVar9 = FUN_1400090c0(local_80,0x10,(undefined8 *)param_3);
          *param_4 = piVar9;
          goto LAB_14000a4f7;
        }
      }
      if ((*param_3 & 4) == 0) {
        *param_5 = (int)piVar10;
      }
    }
  }
LAB_14000a4f7:
  __security_check_cookie(local_50 ^ (ulonglong)auStack_d8);
  return;
}


// ==== FUN_14000a520 @ 14000a520  undefined FUN_14000a520(uint * param_1)

void FUN_14000a520(uint *param_1)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  longlong lVar5;
  undefined1 auStack_d8 [32];
  uint *local_b8;
  uint *local_b0;
  undefined1 *local_a8;
  undefined1 local_98 [4];
  undefined4 local_94;
  undefined4 local_90;
  uint local_8c;
  uint local_88;
  uint local_84;
  uint local_80 [2];
  undefined8 local_78;
  undefined8 local_70;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined4 local_50;
  short local_48 [8];
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined4 local_20;
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_d8;
  if (((*param_1 >> 10 & 1) != 0) && (param_1[1] == 0)) {
    if (DAT_140103f58 == 0) {
      local_94 = 0x10;
      local_90 = 0x1c;
      uVar4 = FUN_140008fa0();
      if ((int)uVar4 != 0) {
        local_78 = 2;
        local_70 = 0;
        uVar1 = Ordinal_9(0x35);
        local_78._0_4_ = CONCAT22(uVar1,(undefined2)local_78);
        local_a8 = local_98;
        local_b0 = &local_84;
        local_b8 = local_80;
        iVar2 = sscanf("18.244.0.188","%u.%u.%u.%u%c");
        if ((((iVar2 == 4) && (local_88 < 0x100)) && (local_8c < 0x100)) &&
           ((local_80[0] < 0x100 && (local_84 < 0x100)))) {
          uVar3 = Ordinal_8(((local_88 << 8 | local_8c) << 8 | local_80[0]) << 8 | local_84);
          local_78 = CONCAT44(uVar3,(undefined4)local_78);
        }
        local_60 = 0;
        local_58 = 0;
        local_50 = 0;
        local_68 = 0x17;
        uVar1 = Ordinal_9(0x35);
        local_68._0_4_ = CONCAT22(uVar1,(undefined2)local_68);
        FUN_140009660(0x17,(byte *)"2001:4860:b002::68",(undefined4 *)&local_60);
        local_48[0] = 0;
        local_48[1] = 0;
        local_48[2] = 0;
        local_48[3] = 0;
        local_48[4] = 0;
        local_48[5] = 0;
        local_48[6] = 0;
        local_48[7] = 0;
        local_38 = 0;
        local_30 = 0;
        local_28 = 0;
        local_20 = 0;
        lVar5 = Ordinal_23(2,2,0x11);
        if (-1 < lVar5) {
          iVar2 = Ordinal_4(lVar5,&local_78,0x10);
          if ((iVar2 == 0) && (iVar2 = Ordinal_6(lVar5,local_48,&local_94), iVar2 == 0)) {
            FUN_140007730(local_48);
          }
          Ordinal_3(lVar5);
        }
        lVar5 = Ordinal_23(0x17,2,0x11);
        if (-1 < lVar5) {
          iVar2 = Ordinal_4(lVar5,&local_68,0x1c);
          if ((iVar2 == 0) && (iVar2 = Ordinal_6(lVar5,&local_38,&local_90), iVar2 == 0)) {
            FUN_140007730((short *)&local_38);
          }
          Ordinal_3(lVar5);
        }
      }
    }
    if (DAT_140103f5c == 0) {
      if (DAT_140103f60 != 0) {
        param_1[1] = 0x17;
      }
    }
    else if (DAT_140103f60 == 0) {
      param_1[1] = 2;
    }
  }
  __security_check_cookie(local_18 ^ (ulonglong)auStack_d8);
  return;
}


// ==== FUN_14000a7d0 @ 14000a7d0  ulonglong FUN_14000a7d0(byte * param_1, char * param_2, ulonglong * param_3, longlong * param_4)

ulonglong FUN_14000a7d0(byte *param_1,char *param_2,ulonglong *param_3,longlong *param_4)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  ulonglong uVar5;
  undefined8 uVar6;
  uint local_res18 [2];
  ulonglong local_48;
  undefined8 local_40;
  ulonglong local_38;
  ulonglong local_30;
  ulonglong local_28;
  ulonglong local_20;
  
  uVar3 = 0xffffffff;
  if (param_3 == (ulonglong *)0x0) {
    local_48 = 0;
    local_40 = 0;
    local_38 = 0;
    local_30 = 0;
    local_28 = 0;
    local_20 = 0;
  }
  else {
    local_48 = *param_3;
    local_40 = param_3[1];
    local_38 = param_3[2];
    local_30 = param_3[3];
    local_28 = param_3[4];
    local_20 = param_3[5];
  }
  uVar5 = FUN_14000a150(param_1,param_2,(byte *)&local_48,param_4,local_res18);
  iVar2 = (int)uVar5;
  if (iVar2 == 0) {
    return uVar5;
  }
  if (iVar2 == 8) {
    return uVar5;
  }
  if (iVar2 == 0x2af9) {
    return uVar5;
  }
  if (DAT_140103f6c == 0) {
    FUN_1400079e0();
  }
  if (((DAT_140103f64 == 0) || (param_2 == (char *)0x0)) || (uVar3 = 0xffffffff, (int)local_40 != 0)
     ) {
LAB_14000a90a:
    bVar1 = false;
    iVar2 = (int)local_40;
  }
  else {
    uVar3 = FUN_140007850(param_2);
    local_res18[0] = uVar3;
    if ((int)uVar3 < 0) goto LAB_14000a90a;
    bVar1 = true;
    if (param_1 == (byte *)0x0) {
      uVar5 = FUN_14000a150((byte *)0x0,param_2,(byte *)&local_48,param_4,local_res18);
      return uVar5;
    }
    param_2 = (char *)0x0;
    iVar2 = (int)local_40;
  }
  if (DAT_140103f6c == 0) {
    FUN_1400079e0();
    iVar2 = (int)local_40;
  }
  if (DAT_140103f68 == 0) goto LAB_14000a973;
  if (local_40._4_4_ == 0) {
    if (iVar2 == 0) goto LAB_14000a973;
    if (iVar2 == 2) {
      local_40 = CONCAT44(0x11,(int)local_40);
      goto LAB_14000a973;
    }
    if (iVar2 == 1) {
      local_40 = CONCAT44(6,(int)local_40);
      goto LAB_14000a973;
    }
  }
  if ((iVar2 == 0) && (local_40._4_4_ != 0)) {
    if (local_40._4_4_ == 0x11) {
      local_40 = 0x1100000002;
    }
    else {
      local_40 = CONCAT44(local_40._4_4_,(uint)(local_40._4_4_ == 6));
    }
  }
LAB_14000a973:
  local_48 = local_48 & 0xffffffff7fffffff;
  uVar4 = getaddrinfo(param_1,param_2,&local_48,param_4);
  uVar5 = (ulonglong)uVar4;
  if (bVar1) {
    FUN_140007b10((short)uVar3,param_4);
  }
  if (DAT_140103f6c == 0) {
    FUN_1400079e0();
  }
  if ((DAT_140103f68 != 0) && (uVar6 = FUN_140007ba0((undefined8 *)*param_4), (int)uVar6 < 0)) {
    FUN_140007ca0((int *)*param_4);
    *param_4 = 0;
    uVar5 = 8;
  }
  return uVar5;
}


// ==== FUN_14000aa00 @ 14000aa00  undefined8 FUN_14000aa00(longlong param_1, byte * param_2, char * param_3, ulonglong * param_4, undefined * param_5, undefined8 param_6)

undefined8
FUN_14000aa00(longlong param_1,byte *param_2,char *param_3,ulonglong *param_4,undefined *param_5,
             undefined8 param_6)

{
  ulonglong uVar1;
  longlong local_res8;
  
  if ((param_1 != 0) && (DAT_140103f70 != (code *)0x0)) {
    (*DAT_140103f70)();
    return 0;
  }
  local_res8 = 0;
  uVar1 = FUN_14000a7d0(param_2,param_3,param_4,&local_res8);
  (*(code *)param_5)(uVar1 & 0xffffffff,local_res8,param_6);
  return 0;
}


// ==== FUN_14000aa90 @ 14000aa90  char * FUN_14000aa90(uint param_1)

char * FUN_14000aa90(uint param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong lVar4;
  longlong *plVar5;
  uint uVar6;
  DWORD DVar7;
  undefined8 *puVar8;
  ulonglong uVar9;
  char *pcVar10;
  char *local_res10 [3];
  
  local_res10[0] = (char *)0x0;
  if (DAT_140103f78 != 0) {
    FUN_140016e30();
  }
  if (DAT_1401023f0 != 0) {
    uVar6 = (param_1 >> 0x10 ^ param_1) * -0x7a143595;
    uVar6 = (uVar6 >> 0xd ^ uVar6) * -0x3d4d51cb;
    uVar9 = (ulonglong)(uVar6 >> 0x10 ^ uVar6) % (ulonglong)DAT_1401023f8;
    plVar5 = *(longlong **)(DAT_1401023f0 + uVar9 * 8);
    plVar3 = (longlong *)(DAT_1401023f0 + uVar9 * 8);
    while ((plVar2 = plVar5, plVar2 != (longlong *)0x0 && (*(uint *)(plVar2 + 1) != param_1))) {
      plVar3 = plVar2;
      plVar5 = (longlong *)*plVar2;
    }
    if (*plVar3 != 0) {
      local_res10[0] = *(char **)(*plVar3 + 0x10);
      goto LAB_14000ac86;
    }
  }
  DVar7 = FormatMessageA(0x1300,(LPCVOID)0x0,param_1,0,(LPSTR)local_res10,0,(va_list *)0x0);
  if (DVar7 == 0) {
    local_res10[0] = (char *)LocalAlloc(0,0x32);
    if (local_res10[0] == (char *)0x0) {
      local_res10[0] = "LocalAlloc failed during Winsock error";
      goto LAB_14000ac86;
    }
    FUN_140009250(local_res10[0],0x32,"winsock error 0x%08x",(ulonglong)param_1);
  }
  else if (local_res10[0] != (char *)0x0) {
    uVar9 = 0xffffffffffffffff;
    pcVar10 = local_res10[0];
    do {
      if (uVar9 == 0) break;
      uVar9 = uVar9 - 1;
      cVar1 = *pcVar10;
      pcVar10 = pcVar10 + 1;
    } while (cVar1 != '\0');
    uVar9 = ~uVar9;
    if ((((uVar9 != 1) && (local_res10[0][uVar9 - 2] == '\n')) &&
        (local_res10[0][uVar9 - 2] = '\0', uVar9 - 2 != 0)) && (local_res10[0][uVar9 - 3] == '\r'))
    {
      local_res10[0][uVar9 - 3] = '\0';
    }
  }
  puVar8 = (undefined8 *)FUN_140011830(0x18);
  if (puVar8 == (undefined8 *)0x0) {
    LocalFree(local_res10[0]);
    local_res10[0] = "malloc failed during Winsock error";
  }
  else {
    *(uint *)(puVar8 + 1) = param_1;
    puVar8[2] = local_res10[0];
    if ((DAT_1401023f0 == 0) || (DAT_140102400 <= DAT_1401023fc)) {
      FUN_140008010(&DAT_1401023f0,DAT_1401023fc + 1);
    }
    lVar4 = DAT_1401023f0;
    DAT_1401023fc = DAT_1401023fc + 1;
    uVar6 = (*(uint *)(puVar8 + 1) >> 0x10 ^ *(uint *)(puVar8 + 1)) * -0x7a143595;
    uVar6 = (uVar6 >> 0xd ^ uVar6) * -0x3d4d51cb;
    uVar9 = (ulonglong)(uVar6 >> 0x10 ^ uVar6) % (ulonglong)DAT_1401023f8;
    *puVar8 = *(undefined8 *)(DAT_1401023f0 + uVar9 * 8);
    *(undefined8 **)(lVar4 + uVar9 * 8) = puVar8;
  }
LAB_14000ac86:
  if (DAT_140103f78 != 0) {
    FUN_140016e50();
  }
  return local_res10[0];
}


// ==== FUN_14000acb0 @ 14000acb0  undefined FUN_14000acb0(ulonglong * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_14000acb0(ulonglong *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined4 uVar1;
  int iVar2;
  longlong lVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  undefined1 auStack_68 [32];
  int local_48 [2];
  undefined8 local_40;
  undefined8 local_38;
  short local_30;
  short local_2e;
  int local_2c;
  ulonglong local_20;
  
  local_20 = DAT_140103510 ^ (ulonglong)auStack_68;
  uVar5 = 0xffffffffffffffff;
  uVar4 = 0xffffffffffffffff;
  if (param_1 == (ulonglong *)0x0) {
    uVar1 = 0x2726;
LAB_14000af12:
    Ordinal_112(uVar1);
  }
  else {
    lVar3 = Ordinal_23(2,1);
    if (-1 < lVar3) {
      local_40 = 2;
      local_38 = 0;
      uVar1 = Ordinal_8(0x7f000001);
      local_40 = CONCAT44(uVar1,(undefined4)local_40) & 0xffffffff0000ffff;
      iVar2 = Ordinal_2(lVar3,&local_40,0x10);
      if (((iVar2 == -1) || (iVar2 = Ordinal_13(lVar3,1), iVar2 == -1)) ||
         (uVar5 = Ordinal_23(2,1,0), (longlong)uVar5 < 0)) {
LAB_14000aed9:
        uVar1 = Ordinal_111();
      }
      else {
        local_48[0] = 0x10;
        iVar2 = Ordinal_6(lVar3,&local_30,local_48);
        if (iVar2 == -1) goto LAB_14000aed9;
        if (local_48[0] != 0x10) goto LAB_14000aed1;
        iVar2 = Ordinal_4(uVar5,&local_30,0x10);
        if (iVar2 == -1) goto LAB_14000aed9;
        local_48[0] = 0x10;
        uVar4 = Ordinal_1(lVar3,&local_40,local_48);
        if ((longlong)uVar4 < 0) goto LAB_14000aed9;
        if (local_48[0] == 0x10) {
          iVar2 = Ordinal_6(uVar5,&local_30,local_48);
          if (iVar2 == -1) goto LAB_14000aed9;
          if (((local_48[0] == 0x10) && ((short)local_40 == local_30)) &&
             ((local_40._4_4_ == local_2c && (local_40._2_2_ == local_2e)))) {
            Ordinal_3(lVar3);
            *param_1 = uVar5;
            param_1[1] = uVar4;
            local_48[0] = 1;
            iVar2 = Ordinal_10(uVar5,0x8004667e,local_48);
            if (iVar2 != -1) {
              uVar5 = param_1[1];
              local_48[0] = 1;
              iVar2 = Ordinal_10(uVar5,0x8004667e,local_48);
              if (iVar2 != -1) goto LAB_14000af2a;
            }
            FUN_140019120(uVar5,"fcntl(%d, F_GETFL)",uVar5 & 0xffffffff,param_4);
            Ordinal_3(*param_1);
            Ordinal_3(param_1[1]);
            goto LAB_14000af18;
          }
        }
LAB_14000aed1:
        uVar1 = 0x2745;
      }
      if (lVar3 != -1) {
        Ordinal_3(lVar3);
      }
      if (uVar5 != 0xffffffffffffffff) {
        Ordinal_3(uVar5);
      }
      if (uVar4 != 0xffffffffffffffff) {
        Ordinal_3(uVar4);
      }
      goto LAB_14000af12;
    }
  }
LAB_14000af18:
  *param_1 = 0xffffffffffffffff;
  param_1[1] = 0xffffffffffffffff;
LAB_14000af2a:
  __security_check_cookie(local_20 ^ (ulonglong)auStack_68);
  return;
}


// ==== FUN_14000af50 @ 14000af50  undefined FUN_14000af50(longlong * param_1, ushort param_2, uint param_3)

void FUN_14000af50(longlong *param_1,ushort param_2,uint param_3)

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


// ==== FUN_14000afd0 @ 14000afd0  undefined FUN_14000afd0(undefined8 param_1, longlong param_2, longlong param_3)

void FUN_14000afd0(undefined8 param_1,longlong param_2,longlong param_3)

{
  ushort uVar1;
  undefined2 extraout_var;
  
  if ((((*(longlong *)(param_2 + 8) != 0) && ((*(byte *)(param_3 + 0x160) & 4) != 0)) &&
      (uVar1 = FUN_140011000(param_3 + 0x88,4,(int *)0x0), CONCAT22(extraout_var,uVar1) == 0)) &&
     (*(ushort *)(param_3 + 0x178) == uVar1)) {
    FUN_1400064e0((longlong *)(param_3 + 0x88),(ulonglong *)(param_3 + 0x158));
  }
  return;
}


// ==== FUN_14000b030 @ 14000b030  undefined FUN_14000b030(longlong param_1, short param_2, longlong * param_3)

void FUN_14000b030(longlong param_1,short param_2,longlong *param_3)

{
  longlong *plVar1;
  int iVar2;
  longlong lVar3;
  ulonglong uVar4;
  longlong lVar5;
  uint uVar6;
  
  uVar6 = 1;
  lVar5 = -1;
  FUN_1400060e0((longlong)param_3);
  if (param_2 == 1) {
    uVar6 = 0x41;
  }
  else {
    plVar1 = (longlong *)param_3[0x20];
    if (param_3[0x23] != 0) {
      lVar5 = FUN_14000c370((longlong)plVar1);
      lVar5 = param_3[0x23] - lVar5;
      if (lVar5 < 1) {
        FUN_1400057f0((longlong)param_3,1);
        goto LAB_14000b160;
      }
    }
    lVar3 = FUN_1400183c0(param_3);
    if ((lVar5 < 0) || (lVar3 < lVar5)) {
      lVar5 = lVar3;
    }
    if (*(short *)((longlong)param_3 + 0x176) != 0) goto LAB_14000b160;
    FUN_14000d9a0((longlong)plVar1,0);
    iVar2 = FUN_14000ee10(plVar1,param_1,(int)lVar5);
    FUN_14000d950((longlong)plVar1,0);
    if (iVar2 == -1) {
      iVar2 = FUN_140007540(param_1);
      if ((iVar2 == 0x2733) || (iVar2 == 0x2714)) goto LAB_14000b160;
      uVar6 = 0x21;
    }
    else if (iVar2 == 0) {
      uVar6 = 0x11;
    }
    else if (0 < iVar2) {
      FUN_140018560((longlong)param_3,(longlong)iVar2);
      uVar4 = FUN_14000c370(param_3[0x20]);
      if ((ulonglong)param_3[0x22] <= uVar4) {
        FUN_140006540(param_3,0);
      }
      goto LAB_14000b160;
    }
  }
  FUN_140005df0((longlong)param_3,2);
  FUN_140006640(param_3,(ulonglong)uVar6,0);
LAB_14000b160:
  FUN_140006940(param_3);
  return;
}


// ==== FUN_14000b180 @ 14000b180  undefined FUN_14000b180(longlong param_1, short param_2, longlong * param_3)

void FUN_14000b180(longlong param_1,short param_2,longlong *param_3)

{
  bool bVar1;
  int iVar2;
  undefined8 uVar3;
  ulonglong uVar4;
  longlong lVar5;
  uint uVar6;
  int iVar7;
  
  iVar2 = 0;
  uVar6 = 2;
  bVar1 = false;
  FUN_1400060e0((longlong)param_3);
  if (param_2 == 1) {
    uVar6 = 0x42;
    goto LAB_14000b345;
  }
  if ((*(byte *)(param_3 + 0x2e) & 8) != 0) {
    uVar3 = FUN_1400076b0(param_1);
    iVar7 = (int)uVar3;
    if ((*(uint *)(param_3 + 0x2e) & 0x10) == 0) {
      if (iVar7 == 0) goto LAB_14000b3b2;
    }
    else {
      iVar7 = -1;
      *(uint *)(param_3 + 0x2e) = *(uint *)(param_3 + 0x2e) & 0xffffffef;
    }
    *(uint *)(param_3 + 0x2e) = *(uint *)(param_3 + 0x2e) & 0xfffffff7;
    if (iVar7 < 0) {
      FUN_140014300(param_3 + 0x11);
      FUN_140014300(param_3 + 2);
      FUN_140006640(param_3,0x20,0);
      goto LAB_14000b3b2;
    }
    bVar1 = true;
    if ((undefined **)param_3[1] == &PTR_s_socket_async_1400ccde0) {
      FUN_140014300(param_3 + 0x11);
      FUN_1400741d0(param_3);
      FUN_140006640(param_3,0x80,0);
      goto LAB_14000b3b2;
    }
    FUN_140006640(param_3,0x80,0);
    if (((*(byte *)(param_3 + 0x2c) & 4) != 0) && ((short)param_3[0x2f] == 0)) goto LAB_14000b295;
LAB_14000b32e:
    FUN_140014300(param_3 + 0x11);
    goto LAB_14000b3b2;
  }
LAB_14000b295:
  uVar4 = FUN_140018490(param_3);
  if ((short)param_3[0x2f] != 0) goto LAB_14000b3b2;
  lVar5 = FUN_14000c370(param_3[0x21]);
  if (lVar5 == 0) {
LAB_14000b36d:
    lVar5 = FUN_14000c370(param_3[0x21]);
    if (lVar5 == 0) {
      FUN_140014300(param_3 + 0x11);
    }
    if ((iVar2 != 0) || (!bVar1)) {
      uVar4 = FUN_14000c370(param_3[0x21]);
      if (uVar4 <= (ulonglong)param_3[0x24]) {
        FUN_1400065c0(param_3,0);
      }
    }
  }
  else {
    FUN_14000d9a0(param_3[0x21],1);
    uVar4 = FUN_14000f130((longlong *)param_3[0x21],param_1,uVar4);
    iVar2 = (int)uVar4;
    FUN_14000d950(param_3[0x21],1);
    if (iVar2 == -1) {
      iVar2 = FUN_140007540(param_1);
      if ((iVar2 == 0x2733) || (iVar2 == 0x2714)) {
        lVar5 = FUN_14000c370(param_3[0x21]);
        if (lVar5 != 0) goto LAB_14000b3b2;
        goto LAB_14000b32e;
      }
      uVar6 = 0x22;
    }
    else {
      if (iVar2 == 0) {
        uVar6 = 0x12;
      }
      if (0 < iVar2) {
        FUN_1400186a0((longlong)param_3,(longlong)iVar2);
        goto LAB_14000b36d;
      }
    }
LAB_14000b345:
    FUN_140005df0((longlong)param_3,4);
    FUN_140006640(param_3,(ulonglong)uVar6,0);
  }
LAB_14000b3b2:
  FUN_140006940(param_3);
  return;
}


// ==== FUN_14000b3e0 @ 14000b3e0  longlong * FUN_14000b3e0(longlong param_1, HANDLE param_2, uint param_3)

longlong * FUN_14000b3e0(longlong param_1,HANDLE param_2,uint param_3)

{
  longlong lVar1;
  longlong *plVar2;
  undefined8 uVar3;
  
  if ((param_1 != 0) && (lVar1 = FUN_140074eb0(param_1), lVar1 != 0)) {
    plVar2 = FUN_1400745d0(param_1,param_2,param_3);
    return plVar2;
  }
  plVar2 = (longlong *)FUN_140011850(1,0x1d8);
  if (plVar2 != (longlong *)0x0) {
    uVar3 = FUN_140007020(plVar2,param_1,0x1400c0c80,(ulonglong)param_3);
    if (-1 < (int)uVar3) {
      FUN_14000bec0(plVar2[0x21],1);
      FUN_140010e40((undefined *)(plVar2 + 2),*plVar2,param_2,0x52,FUN_14000b030,(undefined *)plVar2
                   );
      FUN_140010e40((undefined *)(plVar2 + 0x11),*plVar2,param_2,0x54,FUN_14000b180,
                    (undefined *)plVar2);
      FUN_14000d6e0(plVar2[0x21],0x14000afd0,(longlong)plVar2);
      FUN_14000d950(plVar2[0x20],0);
      FUN_14000d950(plVar2[0x21],1);
      return plVar2;
    }
    FUN_1400119c0(plVar2);
  }
  return (longlong *)0x0;
}


// ==== FUN_14000b520 @ 14000b520  undefined4 FUN_14000b520(longlong param_1)

undefined4 FUN_14000b520(longlong param_1)

{
  undefined4 uVar1;
  
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  uVar1 = *(undefined4 *)(param_1 + 0x180);
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return uVar1;
}


// ==== FUN_14000b570 @ 14000b570  longlong * FUN_14000b570(HANDLE param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, undefined8 param_5)

longlong *
FUN_14000b570(HANDLE param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             undefined8 param_5)

{
  longlong *plVar1;
  
  plVar1 = FUN_14000b3e0(0,param_1,0);
  if (plVar1 != (longlong *)0x0) {
    FUN_140005a50((longlong)plVar1,param_2,param_3,param_4,param_5);
  }
  return plVar1;
}


// ==== FUN_14000b5e0 @ 14000b5e0  undefined8 FUN_14000b5e0(longlong param_1, ushort param_2)

undefined8 FUN_14000b5e0(longlong param_1,ushort param_2)

{
  int iVar1;
  
  if (((param_2 & 2) != 0) &&
     (iVar1 = FUN_1400064e0((longlong *)(param_1 + 0x10),(ulonglong *)(param_1 + 0x150)),
     iVar1 == -1)) {
    return 0xffffffff;
  }
  if (((param_2 & 4) != 0) &&
     (iVar1 = FUN_1400064e0((longlong *)(param_1 + 0x88),(ulonglong *)(param_1 + 0x158)),
     iVar1 == -1)) {
    return 0xffffffff;
  }
  return 0;
}


// ==== FUN_14000b650 @ 14000b650  undefined8 FUN_14000b650(longlong param_1, ushort param_2)

undefined8 FUN_14000b650(longlong param_1,ushort param_2)

{
  int iVar1;
  
  if (((param_2 & 2) != 0) && (iVar1 = FUN_140014300((longlong *)(param_1 + 0x10)), iVar1 == -1)) {
    return 0xffffffff;
  }
  if ((((param_2 & 4) != 0) && ((*(byte *)(param_1 + 0x170) & 8) == 0)) &&
     (iVar1 = FUN_140014300((longlong *)(param_1 + 0x88)), iVar1 == -1)) {
    return 0xffffffff;
  }
  return 0;
}


// ==== FUN_14000b6b0 @ 14000b6b0  undefined FUN_14000b6b0(longlong param_1)

void FUN_14000b6b0(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = FUN_140011160(param_1 + 0x10);
  if (((*(byte *)(param_1 + 0x1b0) & 1) != 0) && (-1 < lVar1)) {
    Ordinal_3(lVar1);
  }
  return;
}


// ==== FUN_14000b6e0 @ 14000b6e0  undefined4 FUN_14000b6e0(longlong param_1)

undefined4 FUN_14000b6e0(longlong param_1)

{
  ushort uVar1;
  int iVar2;
  undefined6 extraout_var;
  undefined6 extraout_var_00;
  undefined4 uVar3;
  
  uVar1 = FUN_140011000(param_1 + 0x10,2,(int *)0x0);
  uVar3 = 0;
  if ((int)CONCAT62(extraout_var,uVar1) != 0) {
    if ((*(int *)(param_1 + 0x150) == 0) && (*(int *)(param_1 + 0x154) == 0)) {
      FUN_140012ee0(param_1 + 0x10);
      uVar3 = 0;
    }
    else {
      iVar2 = FUN_1400064e0((longlong *)(param_1 + 0x10),(ulonglong *)(param_1 + 0x150));
      uVar3 = 0;
      if (iVar2 < 0) {
        uVar3 = 0xffffffff;
      }
    }
  }
  uVar1 = FUN_140011000(param_1 + 0x88,4,(int *)0x0);
  if ((int)CONCAT62(extraout_var_00,uVar1) != 0) {
    if ((*(int *)(param_1 + 0x158) == 0) && (*(int *)(param_1 + 0x15c) == 0)) {
      FUN_140012ee0(param_1 + 0x88);
    }
    else {
      iVar2 = FUN_1400064e0((longlong *)(param_1 + 0x88),(ulonglong *)(param_1 + 0x158));
      if (iVar2 < 0) {
        uVar3 = 0xffffffff;
      }
    }
  }
  return uVar3;
}


// ==== FUN_14000b7b0 @ 14000b7b0  undefined FUN_14000b7b0(longlong * param_1, longlong param_2)

void FUN_14000b7b0(longlong *param_1,longlong param_2)

{
  if (param_1[0x37] != 0) {
    FUN_140016e30();
  }
  FUN_140014300(param_1 + 2);
  FUN_140014300(param_1 + 0x11);
  FUN_140010e40((undefined *)(param_1 + 2),*param_1,param_2,0x52,FUN_14000b030,(undefined *)param_1)
  ;
  FUN_140010e40((undefined *)(param_1 + 0x11),*param_1,param_2,0x54,FUN_14000b180,
                (undefined *)param_1);
  if (-1 < param_2) {
    FUN_1400071b0(param_1,*(ushort *)(param_1 + 0x2c));
  }
  if (param_1[0x37] != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_14000b880 @ 14000b880  undefined8 FUN_14000b880(longlong param_1, int param_2)

undefined8 FUN_14000b880(longlong param_1,int param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e30();
  }
  uVar2 = 0xffffffff;
  if (*(undefined ***)(param_1 + 8) == &PTR_s_socket_1400c0c80) {
    uVar1 = FUN_140010fe0(param_1 + 0x10,param_2);
    uVar2 = 0xffffffff;
    if ((int)uVar1 != -1) {
      uVar1 = FUN_140010fe0(param_1 + 0x88,param_2);
      if ((int)uVar1 != -1) {
        FUN_1400112c0(param_1 + 0x188,(char)param_2);
        uVar2 = 0;
      }
    }
  }
  if (*(longlong *)(param_1 + 0x1b8) != 0) {
    FUN_140016e50();
  }
  return uVar2;
}


// ==== FUN_14000b920 @ 14000b920  ulonglong FUN_14000b920(longlong param_1, longlong * param_2)

ulonglong FUN_14000b920(longlong param_1,longlong *param_2)

{
  ulonglong uVar1;
  ulonglong uVar2;
  
  uVar2 = 0xffffffff;
  if (param_2[0x37] != 0) {
    FUN_140016e30();
  }
  if ((undefined **)param_2[1] == &PTR_s_socket_1400c0c80) {
    *param_2 = param_1;
    uVar1 = FUN_140010f00(param_1,(longlong)(param_2 + 2));
    uVar2 = uVar1 & 0xffffffff;
    if ((int)uVar1 != -1) {
      uVar2 = FUN_140010f00(param_1,(longlong)(param_2 + 0x11));
      uVar2 = uVar2 & 0xffffffff;
    }
  }
  if (param_2[0x37] != 0) {
    FUN_140016e50();
  }
  return uVar2;
}


// ==== FUN_14000b9b0 @ 14000b9b0  undefined8 FUN_14000b9b0(longlong * param_1, int param_2, longlong * param_3)

undefined8 FUN_14000b9b0(longlong *param_1,int param_2,longlong *param_3)

{
  longlong lVar1;
  
  if (param_2 == 0) {
    FUN_14000b7b0(param_1,*param_3);
    return 0;
  }
  if (param_2 != 1) {
    return 0xffffffff;
  }
  lVar1 = FUN_140011160((longlong)(param_1 + 2));
  *param_3 = lVar1;
  return 0;
}


// ==== FUN_14000b9f0 @ 14000b9f0  undefined4 FUN_14000b9f0(longlong * param_1, ushort * param_2, undefined4 param_3, undefined8 param_4)

undefined4 FUN_14000b9f0(longlong *param_1,ushort *param_2,undefined4 param_3,undefined8 param_4)

{
  bool bVar1;
  int iVar2;
  undefined8 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  ulonglong local_res8;
  
  iVar2 = 0;
  uVar4 = 0xffffffff;
  bVar1 = false;
  FUN_1400060e0((longlong)param_1);
  uVar5 = 0xffffffff;
  if (param_1 == (longlong *)0x0) goto LAB_14000bb7e;
  local_res8 = FUN_140006200((longlong)param_1);
  uVar5 = uVar4;
  if ((longlong)local_res8 < 0) {
    if ((param_2 == (ushort *)0x0) ||
       (local_res8 = FUN_140008c50((ulonglong)*param_2,0x4000001,0,param_4),
       (longlong)local_res8 < 0)) goto LAB_14000bb7e;
    bVar1 = true;
  }
  if (param_2 == (ushort *)0x0) {
LAB_14000baee:
    if ((undefined **)param_1[1] == &PTR_s_socket_async_1400ccde0) {
      FUN_140010e40((undefined *)(param_1 + 0x11),*param_1,local_res8,0x54,FUN_14000b180,
                    (undefined *)param_1);
    }
    FUN_140006190((longlong)param_1,local_res8);
    if (iVar2 == 0) {
      iVar2 = FUN_1400064e0(param_1 + 0x11,(ulonglong *)(param_1 + 0x2b));
      if (iVar2 != -1) {
        *(uint *)(param_1 + 0x2e) = *(uint *)(param_1 + 0x2e) | 8;
        uVar5 = 0;
      }
    }
    else {
      uVar5 = 0;
      if (iVar2 == 1) {
        *(uint *)(param_1 + 0x2e) = *(uint *)(param_1 + 0x2e) | 8;
      }
      else {
        *(uint *)(param_1 + 0x2e) = *(uint *)(param_1 + 0x2e) | 0x18;
      }
      FUN_140014790(param_1 + 0x11,4,1);
    }
  }
  else {
    uVar3 = FUN_140074210(param_1);
    if ((int)uVar3 == 0) {
      uVar3 = FUN_1400075c0(&local_res8,param_2,param_3,param_4);
      iVar2 = (int)uVar3;
      if (-1 < iVar2) goto LAB_14000baee;
    }
    else {
      FUN_140006190((longlong)param_1,local_res8);
      iVar2 = FUN_140074270(param_1,local_res8,(short *)param_2,param_3);
      if (-1 < iVar2) {
        *(uint *)(param_1 + 0x2e) = *(uint *)(param_1 + 0x2e) | 8;
        uVar5 = 0;
        goto LAB_14000bb7e;
      }
    }
    FUN_140006640(param_1,0x20,0);
    if (bVar1) {
      Ordinal_3(local_res8);
    }
  }
LAB_14000bb7e:
  FUN_140006940(param_1);
  return uVar5;
}


// ==== FUN_14000bbb0 @ 14000bbb0  undefined FUN_14000bbb0(int param_1, int * param_2, longlong * param_3, undefined8 param_4)

void FUN_14000bbb0(int param_1,int *param_2,longlong *param_3,undefined8 param_4)

{
  if (param_3[0x37] != 0) {
    FUN_140016e30();
  }
  FUN_140005940((longlong)param_3,8);
  FUN_140005860((longlong)param_3,8);
  if (param_1 == 0) {
    FUN_14000b9f0(param_3,*(ushort **)(param_2 + 8),param_2[4],param_4);
    FUN_140006940(param_3);
  }
  else {
    *(int *)(param_3 + 0x30) = param_1;
    FUN_140006640(param_3,0x20,0);
    FUN_140006940(param_3);
    if (param_2 == (int *)0x0) {
      return;
    }
  }
  FUN_140007ca0(param_2);
  return;
}


// ==== FUN_14000bc50 @ 14000bc50  undefined FUN_14000bc50(longlong * param_1, longlong param_2, uint param_3, byte * param_4, uint param_5)

void FUN_14000bc50(longlong *param_1,longlong param_2,uint param_3,byte *param_4,uint param_5)

{
  undefined8 uVar1;
  undefined1 auStackY_a8 [32];
  ulonglong local_78 [6];
  char local_48 [16];
  ulonglong local_38;
  
  local_38 = DAT_140103510 ^ (ulonglong)auStackY_a8;
  if ((((param_3 == 2) || (param_3 == 0x17)) || (param_3 == 0)) && (param_5 - 1 < 0xffff)) {
    if (param_1[0x37] != 0) {
      FUN_140016e30();
    }
    *(undefined4 *)(param_1 + 0x30) = 0;
    if (param_1[0x37] != 0) {
      FUN_140016e50();
    }
    FUN_140009250(local_48,10,"%d",(ulonglong)param_5);
    local_78[2] = 0;
    local_78[3] = 0;
    local_78[4] = 0;
    local_78[5] = 0;
    local_78[0] = (ulonglong)param_3 << 0x20;
    local_78[1] = 0x600000001;
    FUN_1400058d0((longlong)param_1,8);
    FUN_1400057f0((longlong)param_1,8);
    FUN_140006150((longlong)param_1);
    uVar1 = FUN_14000aa00(param_2,param_4,local_48,local_78,FUN_14000bbb0,param_1);
    if ((int)uVar1 != 0) {
      FUN_140005940((longlong)param_1,8);
      FUN_140005860((longlong)param_1,8);
      FUN_140006120(param_1);
    }
  }
  __security_check_cookie(local_38 ^ (ulonglong)auStackY_a8);
  return;
}


// ==== FUN_14000bdc0 @ 14000bdc0  undefined8 * FUN_14000bdc0(ulonglong param_1)

undefined8 * FUN_14000bdc0(ulonglong param_1)

{
  undefined8 *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  
  if (0x7fffffffffffffcf < param_1) {
    return (undefined8 *)0x0;
  }
  uVar2 = param_1 + 0x30;
  uVar3 = uVar2;
  if ((uVar2 < 0x3fffffffffffffff) && (uVar3 = 0x400, 0x400 < uVar2)) {
    do {
      uVar3 = uVar3 * 2;
    } while (uVar3 < uVar2);
  }
  puVar1 = (undefined8 *)FUN_140011830(uVar3);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1[1] = uVar3 - 0x30;
    *(undefined4 *)((longlong)puVar1 + 0x24) = 1;
    puVar1[5] = puVar1 + 6;
    return puVar1;
  }
  return (undefined8 *)0x0;
}


// ==== FUN_14000be60 @ 14000be60  undefined FUN_14000be60(longlong param_1, uint param_2)

void FUN_14000be60(longlong param_1,uint param_2)

{
  *(uint *)(param_1 + 0x20) = *(uint *)(param_1 + 0x20) | param_2;
  return;
}


// ==== FUN_14000be80 @ 14000be80  undefined FUN_14000be80(void)

void FUN_14000be80(void)

{
  void *pvVar1;
  
  pvVar1 = FUN_140011850(1,0x88);
  if (pvVar1 == (void *)0x0) {
    return;
  }
  *(undefined8 *)((longlong)pvVar1 + 0x78) = 0;
  *(undefined4 *)((longlong)pvVar1 + 0x48) = 1;
  *(void **)((longlong)pvVar1 + 0x10) = pvVar1;
  return;
}


// ==== FUN_14000bec0 @ 14000bec0  undefined8 FUN_14000bec0(longlong param_1, uint param_2)

undefined8 FUN_14000bec0(longlong param_1,uint param_2)

{
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e30();
  }
  *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) | param_2;
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e50();
  }
  return 0;
}


// ==== FUN_14000bf00 @ 14000bf00  undefined8 FUN_14000bf00(longlong param_1, uint param_2)

undefined8 FUN_14000bf00(longlong param_1,uint param_2)

{
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e30();
  }
  *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) & ~param_2;
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e50();
  }
  return 0;
}


// ==== FUN_14000bf50 @ 14000bf50  undefined FUN_14000bf50(longlong param_1)

void FUN_14000bf50(longlong param_1)

{
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e30();
  }
  *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + 1;
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_14000bf90 @ 14000bf90  undefined FUN_14000bf90(longlong param_1)

void FUN_14000bf90(longlong param_1)

{
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e30();
    *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + 1;
    return;
  }
  *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + 1;
  return;
}


// ==== FUN_14000bfc0 @ 14000bfc0  undefined8 FUN_14000bfc0(longlong param_1, longlong param_2)

undefined8 FUN_14000bfc0(longlong param_1,longlong param_2)

{
  longlong lVar1;
  
  if (*(longlong *)(param_1 + 0x30) == 0) {
    if (param_2 != 0) {
      *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) & 0xfffffffe;
      *(longlong *)(param_1 + 0x30) = param_2;
      return 0;
    }
    lVar1 = FUN_140016df0();
    if (lVar1 != 0) {
      *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) | 1;
      *(longlong *)(param_1 + 0x30) = lVar1;
      return 0;
    }
  }
  return 0xffffffff;
}


// ==== FUN_14000c010 @ 14000c010  undefined FUN_14000c010(longlong param_1, undefined8 param_2)

void FUN_14000c010(longlong param_1,undefined8 param_2)

{
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e30();
  }
  *(undefined8 *)(param_1 + 0x80) = param_2;
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_14000c060 @ 14000c060  undefined FUN_14000c060(longlong param_1, int param_2)

void FUN_14000c060(longlong param_1,int param_2)

{
  longlong lVar1;
  longlong *plVar2;
  bool bVar3;
  uint uVar4;
  uint uVar5;
  longlong *plVar6;
  longlong local_38;
  longlong local_30;
  longlong local_28;
  
  bVar3 = true;
  if (param_2 == 0) {
    if ((*(byte *)(param_1 + 0x38) & 8) == 0) {
      uVar5 = 1;
      uVar4 = 1;
    }
    else {
      uVar5 = 3;
      bVar3 = false;
      uVar4 = 3;
    }
  }
  else {
    uVar5 = 3;
    uVar4 = 1;
  }
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016ef0();
  }
  plVar6 = *(longlong **)(param_1 + 0x78);
  if (plVar6 == (longlong *)0x0) {
    *(undefined8 *)(param_1 + 0x28) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
  }
  else {
    local_30 = *(longlong *)(param_1 + 0x20);
    if ((local_30 != 0) || (*(longlong *)(param_1 + 0x28) != 0)) {
      local_28 = *(longlong *)(param_1 + 0x28);
      lVar1 = *(longlong *)(param_1 + 0x18);
      local_38 = (local_28 - local_30) + lVar1;
      if (bVar3) {
        *(undefined8 *)(param_1 + 0x20) = 0;
        *(undefined8 *)(param_1 + 0x28) = 0;
      }
      do {
        plVar2 = (longlong *)*plVar6;
        if ((*(uint *)(plVar6 + 4) & uVar5) == uVar4) {
          if ((*(uint *)(plVar6 + 4) >> 0x12 & 1) == 0) {
            (*(code *)plVar6[2])(param_1,&local_38,plVar6[3]);
          }
          else {
            (*(code *)plVar6[2])(param_1,local_38,lVar1,plVar6[3]);
          }
        }
        plVar6 = plVar2;
      } while (plVar2 != (longlong *)0x0);
    }
  }
  return;
}


// ==== FUN_14000c160 @ 14000c160  undefined FUN_14000c160(longlong param_1)

void FUN_14000c160(longlong param_1)

{
  ulonglong uVar1;
  
  if (*(longlong *)(param_1 + 0x78) == 0) {
    *(undefined8 *)(param_1 + 0x28) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    return;
  }
  if ((*(byte *)(param_1 + 0x38) & 8) != 0) {
    uVar1 = FUN_140012c10(*(longlong *)(param_1 + 0x40),(longlong *)(param_1 + 0x50));
    if ((int)uVar1 != 0) {
      if (*(longlong *)(param_1 + 0x30) != 0) {
        FUN_140016e30();
      }
      *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + 1;
      if (*(longlong *)(param_1 + 0x80) != 0) {
        FUN_140006150(*(longlong *)(param_1 + 0x80));
      }
    }
    if (*(longlong *)(param_1 + 0x30) != 0) {
      FUN_140016e50();
    }
  }
  FUN_14000c060(param_1,0);
  return;
}


// ==== FUN_14000c1e0 @ 14000c1e0  undefined FUN_14000c1e0(longlong param_1)

void FUN_14000c1e0(longlong param_1)

{
  longlong *plVar1;
  
  plVar1 = *(longlong **)(param_1 + 0x78);
  while (plVar1 != (longlong *)0x0) {
    if (*plVar1 != 0) {
      *(longlong *)(*plVar1 + 8) = plVar1[1];
    }
    *(longlong *)plVar1[1] = *plVar1;
    FUN_1400119c0(plVar1);
    plVar1 = *(longlong **)(param_1 + 0x78);
  }
  return;
}


// ==== FUN_14000c220 @ 14000c220  undefined FUN_14000c220(undefined8 * param_1)

void FUN_14000c220(undefined8 *param_1)

{
  undefined8 *puVar1;
  longlong *plVar2;
  undefined8 *puVar3;
  
  if (param_1[6] != 0) {
    FUN_140016ef0();
  }
  *(int *)(param_1 + 9) = *(int *)(param_1 + 9) + -1;
  if (*(int *)(param_1 + 9) < 1) {
    puVar3 = (undefined8 *)*param_1;
    while (puVar3 != (undefined8 *)0x0) {
      puVar1 = (undefined8 *)*puVar3;
      FUN_14000da70(puVar3);
      puVar3 = puVar1;
    }
    plVar2 = (longlong *)param_1[0xf];
    while (plVar2 != (longlong *)0x0) {
      if (*plVar2 != 0) {
        *(longlong *)(*plVar2 + 8) = plVar2[1];
      }
      *(longlong *)plVar2[1] = *plVar2;
      FUN_1400119c0(plVar2);
      plVar2 = (longlong *)param_1[0xf];
    }
    if ((*(byte *)(param_1 + 7) & 8) != 0) {
      FUN_1400148f0(param_1[8],param_1 + 10);
    }
    if (param_1[6] != 0) {
      FUN_140016e50();
    }
    if (((*(byte *)(param_1 + 7) & 1) != 0) && (param_1[6] != 0)) {
      FUN_140016e10();
    }
    FUN_1400119c0(param_1);
  }
  else if (param_1[6] != 0) {
    FUN_140016e50();
    return;
  }
  return;
}


// ==== FUN_14000c300 @ 14000c300  undefined FUN_14000c300(undefined8 * param_1)

void FUN_14000c300(undefined8 *param_1)

{
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  FUN_14000c220(param_1);
  return;
}


// ==== FUN_14000c330 @ 14000c330  undefined FUN_14000c330(longlong param_1)

void FUN_14000c330(longlong param_1)

{
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e30();
  }
  return;
}


// ==== FUN_14000c350 @ 14000c350  undefined FUN_14000c350(longlong param_1)

void FUN_14000c350(longlong param_1)

{
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_14000c370 @ 14000c370  undefined8 FUN_14000c370(longlong param_1)

undefined8 FUN_14000c370(longlong param_1)

{
  undefined8 uVar1;
  
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e30();
  }
  uVar1 = *(undefined8 *)(param_1 + 0x18);
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e50();
  }
  return uVar1;
}


// ==== FUN_14000c3b0 @ 14000c3b0  undefined8 FUN_14000c3b0(longlong * param_1)

undefined8 FUN_14000c3b0(longlong *param_1)

{
  undefined8 uVar1;
  
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  if (*param_1 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined8 *)(*param_1 + 0x18);
  }
  if (param_1[6] != 0) {
    FUN_140016e50();
  }
  return uVar1;
}


// ==== FUN_14000c400 @ 14000c400  int FUN_14000c400(longlong param_1)

int FUN_14000c400(longlong param_1)

{
  longlong lVar1;
  longlong *plVar2;
  int iVar3;
  
  iVar3 = 0;
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016ef0();
  }
  if (**(longlong **)(param_1 + 0x10) != 0) {
    lVar1 = *(longlong *)**(longlong **)(param_1 + 0x10);
    while ((lVar1 != 0 &&
           (plVar2 = (longlong *)**(undefined8 **)(param_1 + 0x10),
           *(longlong *)(*plVar2 + 0x18) != 0))) {
      *(longlong **)(param_1 + 0x10) = plVar2;
      iVar3 = iVar3 + 1;
      lVar1 = *(longlong *)*plVar2;
    }
    return iVar3;
  }
  return 0;
}


// ==== FUN_14000c470 @ 14000c470  undefined8 FUN_14000c470(longlong param_1, longlong * param_2, int param_3)

undefined8 FUN_14000c470(longlong param_1,longlong *param_2,int param_3)

{
  ulonglong uVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  longlong lVar4;
  longlong lVar5;
  longlong *plVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  
  uVar8 = 0xffffffff;
  lVar4 = 0;
  lVar5 = (longlong)param_3;
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e30();
  }
  uVar9 = 0xffffffff;
  if ((*(byte *)(param_1 + 0x38) & 4) != 0) goto LAB_14000c646;
  if (param_3 == 0) {
    uVar9 = 0;
    goto LAB_14000c646;
  }
  uVar9 = uVar8;
  if ((param_3 == 1) && (lVar7 = *(longlong *)(param_1 + 8), lVar7 != 0)) {
    if (*param_2 !=
        *(longlong *)(lVar7 + 0x28) + *(longlong *)(lVar7 + 0x10) + *(longlong *)(lVar7 + 0x18))
    goto LAB_14000c51d;
    if ((*(byte *)(lVar7 + 0x20) & 8) == 0) {
      uVar1 = (*(longlong *)(lVar7 + 8) - *(longlong *)(lVar7 + 0x10)) - *(longlong *)(lVar7 + 0x18)
      ;
    }
    else {
      uVar1 = 0;
    }
    if (uVar1 < (ulonglong)param_2[1]) goto LAB_14000c646;
    *(longlong *)(lVar7 + 0x18) = *(longlong *)(lVar7 + 0x18) + param_2[1];
    lVar4 = param_2[1];
    if (lVar4 != 0) {
      FUN_14000c400(param_1);
    }
  }
  else {
LAB_14000c51d:
    plVar3 = (longlong *)**(longlong **)(param_1 + 0x10);
    if (plVar3 == (longlong *)0x0) goto LAB_14000c646;
    if (((*(byte *)(plVar3 + 4) & 8) != 0) ||
       (plVar6 = *(longlong **)(param_1 + 0x10), plVar3[1] - plVar3[3] == plVar3[2])) {
      plVar6 = plVar3;
    }
    puVar2 = (undefined8 *)*plVar6;
    lVar7 = 0;
    plVar3 = param_2;
    if (0 < param_3) {
      do {
        if (puVar2 == (undefined8 *)0x0) goto LAB_14000c646;
        if (*plVar3 != puVar2[5] + puVar2[2] + puVar2[3]) goto LAB_14000c646;
        if ((*(byte *)(puVar2 + 4) & 8) == 0) {
          uVar1 = (puVar2[1] - puVar2[2]) - puVar2[3];
        }
        else {
          uVar1 = 0;
        }
        if (uVar1 < (ulonglong)plVar3[1]) goto LAB_14000c646;
        puVar2 = (undefined8 *)*puVar2;
        lVar7 = lVar7 + 1;
        plVar3 = plVar3 + 2;
      } while (lVar7 < lVar5);
    }
    if (0 < lVar5) {
      plVar3 = param_2 + 1;
      do {
        *(longlong *)(*plVar6 + 0x18) = *(longlong *)(*plVar6 + 0x18) + *plVar3;
        lVar4 = lVar4 + *plVar3;
        if (*plVar3 != 0) {
          *(longlong **)(param_1 + 0x10) = plVar6;
        }
        plVar6 = (longlong *)*plVar6;
        plVar3 = plVar3 + 2;
        lVar5 = lVar5 + -1;
      } while (lVar5 != 0);
    }
  }
  *(longlong *)(param_1 + 0x18) = *(longlong *)(param_1 + 0x18) + lVar4;
  *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + lVar4;
  if (*(longlong *)(param_1 + 0x78) == 0) {
    *(undefined8 *)(param_1 + 0x28) = 0;
    *(undefined8 *)(param_1 + 0x20) = 0;
    uVar9 = 0;
  }
  else {
    if ((*(byte *)(param_1 + 0x38) & 8) != 0) {
      uVar1 = FUN_140012c10(*(longlong *)(param_1 + 0x40),(longlong *)(param_1 + 0x50));
      if ((int)uVar1 != 0) {
        if (*(longlong *)(param_1 + 0x30) != 0) {
          FUN_140016e30();
        }
        *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + 1;
        if (*(longlong *)(param_1 + 0x80) != 0) {
          FUN_140006150(*(longlong *)(param_1 + 0x80));
        }
      }
      if (*(longlong *)(param_1 + 0x30) != 0) {
        FUN_140016e50();
      }
    }
    FUN_14000c060(param_1,0);
    uVar9 = 0;
  }
LAB_14000c646:
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e50();
  }
  return uVar9;
}


// ==== FUN_14000c690 @ 14000c690  undefined FUN_14000c690(undefined8 * param_1)

void FUN_14000c690(undefined8 *param_1)

{
  if (param_1[6] != 0) {
    FUN_140016ef0();
  }
  param_1[2] = param_1;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[3] = 0;
  return;
}


// ==== FUN_14000c6c0 @ 14000c6c0  undefined8 FUN_14000c6c0(longlong param_1, longlong * param_2, undefined8 * param_3)

undefined8 FUN_14000c6c0(longlong param_1,longlong *param_2,undefined8 *param_3)

{
  longlong *plVar1;
  longlong lVar2;
  undefined8 *puVar3;
  undefined8 uVar4;
  longlong *plVar5;
  
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016ef0();
  }
  if ((*(longlong *)(param_1 + 8) != 0) &&
     ((*(byte *)(*(longlong *)(param_1 + 8) + 0x20) & 0x10) != 0)) {
    plVar1 = (longlong *)**(longlong **)(param_1 + 0x10);
    plVar5 = *(longlong **)(param_1 + 0x10);
    if ((*(byte *)(plVar1 + 4) & 0x10) == 0) {
      plVar5 = plVar1;
    }
    lVar2 = *plVar5;
    *param_2 = lVar2;
    *param_3 = *(undefined8 *)(param_1 + 8);
    if (*(ulonglong *)(lVar2 + 0x18) == 0) {
      uVar4 = 0;
      *(undefined8 *)(param_1 + 8) = **(undefined8 **)(param_1 + 0x10);
      *plVar5 = 0;
    }
    else {
      puVar3 = FUN_14000bdc0(*(ulonglong *)(lVar2 + 0x18));
      if (puVar3 == (undefined8 *)0x0) {
        uVar4 = 0xffffffff;
      }
      else {
        memcpy((void *)puVar3[5],(void *)(*(longlong *)(lVar2 + 0x28) + *(longlong *)(lVar2 + 0x10))
               ,*(size_t *)(lVar2 + 0x18));
        puVar3[3] = *(undefined8 *)(lVar2 + 0x18);
        **(undefined8 **)(param_1 + 0x10) = puVar3;
        *(undefined8 **)(param_1 + 8) = puVar3;
        *(longlong *)(lVar2 + 0x10) = *(longlong *)(lVar2 + 0x10) + *(longlong *)(lVar2 + 0x18);
        uVar4 = 0;
        *(undefined8 *)(lVar2 + 0x18) = 0;
      }
    }
    return uVar4;
  }
  *param_3 = 0;
  *param_2 = 0;
  return 0;
}


// ==== FUN_14000c7b0 @ 14000c7b0  undefined FUN_14000c7b0(longlong * param_1, longlong param_2, longlong param_3)

void FUN_14000c7b0(longlong *param_1,longlong param_2,longlong param_3)

{
  if (param_1[6] != 0) {
    FUN_140016ef0();
  }
  if (param_2 == 0) {
    if (param_1[6] != 0) {
      FUN_140016ef0();
    }
    *param_1 = 0;
    param_1[1] = 0;
  }
  else {
    *param_1 = param_2;
    param_1[1] = param_3;
  }
  param_1[3] = 0;
  param_1[2] = (longlong)param_1;
  return;
}


// ==== FUN_14000c810 @ 14000c810  undefined FUN_14000c810(undefined8 * param_1, undefined8 * param_2)

void FUN_14000c810(undefined8 *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  
  if (param_1[6] != 0) {
    FUN_140016ef0();
  }
  if (param_2[6] != 0) {
    FUN_140016ef0();
  }
  *param_1 = *param_2;
  puVar1 = (undefined8 *)param_2[2];
  if ((undefined8 *)param_2[2] == param_2) {
    puVar1 = param_1;
  }
  param_1[2] = puVar1;
  param_1[1] = param_2[1];
  param_1[3] = param_2[3];
  return;
}


// ==== FUN_14000c870 @ 14000c870  undefined FUN_14000c870(longlong param_1, undefined8 * param_2)

void FUN_14000c870(longlong param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016ef0();
  }
  if (param_2[6] != 0) {
    FUN_140016ef0();
  }
  **(undefined8 **)(param_1 + 8) = *param_2;
  puVar1 = (undefined8 *)param_2[2];
  if (puVar1 == param_2) {
    puVar1 = *(undefined8 **)(param_1 + 8);
  }
  *(undefined8 **)(param_1 + 0x10) = puVar1;
  *(undefined8 *)(param_1 + 8) = param_2[1];
  *(longlong *)(param_1 + 0x18) = *(longlong *)(param_1 + 0x18) + param_2[3];
  return;
}


// ==== FUN_14000c8d0 @ 14000c8d0  undefined FUN_14000c8d0(longlong * param_1, longlong * param_2)

void FUN_14000c8d0(longlong *param_1,longlong *param_2)

{
  longlong *plVar1;
  
  if (param_1[6] != 0) {
    FUN_140016ef0();
  }
  if (param_2[6] != 0) {
    FUN_140016ef0();
  }
  *(longlong *)param_2[1] = *param_1;
  *param_1 = *param_2;
  param_1[3] = param_1[3] + param_2[3];
  if (*(longlong *)param_1[2] == 0) {
    plVar1 = (longlong *)param_2[2];
    if ((longlong *)param_2[2] == param_2) {
      plVar1 = param_1;
    }
    param_1[2] = (longlong)plVar1;
    return;
  }
  if ((longlong *)param_1[2] == param_1) {
    param_1[2] = param_2[1];
  }
  return;
}


// ==== FUN_14000c950 @ 14000c950  ulonglong FUN_14000c950(longlong * param_1, longlong * param_2, void * param_3, ulonglong param_4)

ulonglong FUN_14000c950(longlong *param_1,longlong *param_2,void *param_3,ulonglong param_4)

{
  longlong lVar1;
  ulonglong uVar2;
  ulonglong _Size;
  undefined8 *puVar3;
  ulonglong uVar4;
  ulonglong _Size_00;
  
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  if (param_2 == (longlong *)0x0) {
    puVar3 = (undefined8 *)*param_1;
    uVar2 = 0;
    if ((ulonglong)param_1[3] < param_4) {
      param_4 = param_1[3];
    }
  }
  else {
    lVar1 = *param_2;
    if (0x7fffffffffffffffU - lVar1 < param_4) {
      uVar4 = 0xffffffffffffffff;
      goto LAB_14000ca56;
    }
    puVar3 = (undefined8 *)param_2[1];
    uVar2 = param_2[2];
    if ((ulonglong)param_1[3] < lVar1 + param_4) {
      param_4 = param_1[3] - lVar1;
    }
  }
  uVar4 = 0;
  if (param_4 != 0) {
    _Size_00 = param_4;
    if ((*(byte *)(param_1 + 7) & 2) == 0) {
      do {
        _Size = puVar3[3] - uVar2;
        uVar4 = param_4;
        if (_Size_00 < _Size) {
          if (_Size_00 != 0) {
            memcpy(param_3,(void *)(puVar3[5] + puVar3[2] + uVar2),_Size_00);
          }
          break;
        }
        memcpy(param_3,(void *)(puVar3[5] + puVar3[2] + uVar2),_Size);
        puVar3 = (undefined8 *)*puVar3;
        param_3 = (void *)((longlong)param_3 + _Size);
        _Size_00 = _Size_00 - _Size;
        uVar2 = 0;
      } while (_Size_00 != 0);
    }
    else {
      uVar4 = 0xffffffffffffffff;
    }
  }
LAB_14000ca56:
  if (param_1[6] != 0) {
    FUN_140016e50();
  }
  return uVar4;
}


// ==== FUN_14000ca90 @ 14000ca90  longlong FUN_14000ca90(longlong * param_1, char param_2)

longlong FUN_14000ca90(longlong *param_1,char param_2)

{
  void *pvVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  
  plVar2 = (longlong *)param_1[1];
  lVar4 = param_1[2];
  if (plVar2 != (longlong *)0x0) {
    do {
      lVar3 = plVar2[5] + plVar2[2];
      pvVar1 = memchr((void *)(lVar4 + lVar3),(int)param_2,plVar2[3] - lVar4);
      if (pvVar1 != (void *)0x0) {
        param_1[1] = (longlong)plVar2;
        param_1[2] = (longlong)pvVar1 - lVar3;
        *param_1 = (longlong)pvVar1 + *param_1 + (-lVar4 - lVar3);
        return *param_1;
      }
      lVar3 = plVar2[3] - lVar4;
      lVar4 = 0;
      *param_1 = *param_1 + lVar3;
      plVar2 = (longlong *)*plVar2;
    } while (plVar2 != (longlong *)0x0);
  }
  return -1;
}


// ==== FUN_14000cb30 @ 14000cb30  void * FUN_14000cb30(void * param_1, longlong param_2)

void * FUN_14000cb30(void *param_1,longlong param_2)

{
  void *pvVar1;
  void *pvVar2;
  void *pvVar3;
  size_t _MaxCount;
  void *pvVar4;
  size_t sVar5;
  
  pvVar1 = (void *)((longlong)param_1 + param_2);
  if (param_1 < pvVar1) {
    pvVar4 = (void *)((longlong)param_1 + 0x80);
    sVar5 = (longlong)pvVar1 - (longlong)param_1;
    do {
      _MaxCount = sVar5;
      if (pvVar4 < pvVar1) {
        _MaxCount = 0x80;
      }
      pvVar2 = memchr(param_1,0xd,_MaxCount);
      pvVar3 = memchr(param_1,10,_MaxCount);
      if (pvVar2 != (void *)0x0) {
        if ((pvVar3 != (void *)0x0) && (pvVar3 < pvVar2)) {
          return pvVar3;
        }
        return pvVar2;
      }
      if (pvVar3 != (void *)0x0) {
        return pvVar3;
      }
      param_1 = (void *)((longlong)param_1 + 0x80);
      pvVar4 = (void *)((longlong)pvVar4 + 0x80);
      sVar5 = sVar5 - 0x80;
    } while (param_1 < pvVar1);
  }
  return (void *)0x0;
}


// ==== FUN_14000cbf0 @ 14000cbf0  longlong FUN_14000cbf0(longlong * param_1)

longlong FUN_14000cbf0(longlong *param_1)

{
  undefined8 *puVar1;
  void *pvVar2;
  longlong lVar3;
  longlong lVar4;
  
  puVar1 = (undefined8 *)param_1[1];
  lVar4 = param_1[2];
  while( true ) {
    if (puVar1 == (undefined8 *)0x0) {
      return -1;
    }
    lVar3 = puVar1[5] + puVar1[2];
    pvVar2 = FUN_14000cb30((void *)(lVar4 + lVar3),puVar1[3] - lVar4);
    if (pvVar2 != (void *)0x0) break;
    lVar3 = puVar1[3] - lVar4;
    lVar4 = 0;
    *param_1 = *param_1 + lVar3;
    puVar1 = (undefined8 *)*puVar1;
  }
  param_1[1] = (longlong)puVar1;
  param_1[2] = (longlong)pvVar2 - lVar3;
  *param_1 = (longlong)pvVar2 + *param_1 + (-lVar4 - lVar3);
  return *param_1;
}


// ==== FUN_14000cc90 @ 14000cc90  int FUN_14000cc90(longlong * param_1, char * param_2)

int FUN_14000cc90(longlong *param_1,char *param_2)

{
  char cVar1;
  longlong *plVar2;
  char *pcVar3;
  ulonglong uVar4;
  int iVar5;
  longlong *plVar6;
  
  uVar4 = param_1[2];
  iVar5 = 0;
  plVar2 = (longlong *)param_1[1];
  if ((longlong *)param_1[1] == (longlong *)0x0) {
    return 0;
  }
  do {
    plVar6 = plVar2;
    for (; pcVar3 = param_2, uVar4 < (ulonglong)plVar6[3]; uVar4 = uVar4 + 1) {
      do {
        cVar1 = *pcVar3;
        if (cVar1 == '\0') {
          *param_1 = *param_1 + (longlong)iVar5;
          goto LAB_14000cd0d;
        }
        pcVar3 = pcVar3 + 1;
      } while (*(char *)(plVar6[5] + plVar6[2] + uVar4) != cVar1);
      iVar5 = iVar5 + 1;
    }
    uVar4 = 0;
    plVar2 = (longlong *)*plVar6;
  } while ((longlong *)*plVar6 != (longlong *)0x0);
  *param_1 = *param_1 + (longlong)iVar5;
LAB_14000cd0d:
  param_1[2] = uVar4;
  param_1[1] = (longlong)plVar6;
  return iVar5;
}


// ==== FUN_14000cd60 @ 14000cd60  undefined FUN_14000cd60(longlong param_1)

void FUN_14000cd60(longlong param_1)

{
  memmove(*(void **)(param_1 + 0x28),
          (void *)((longlong)*(void **)(param_1 + 0x28) + *(longlong *)(param_1 + 0x10)),
          *(size_t *)(param_1 + 0x18));
  *(undefined8 *)(param_1 + 0x10) = 0;
  return;
}


// ==== FUN_14000cdc0 @ 14000cdc0  int FUN_14000cdc0(longlong param_1, ulonglong param_2, longlong * param_3, int param_4, longlong * param_5, int param_6)

int FUN_14000cdc0(longlong param_1,ulonglong param_2,longlong *param_3,int param_4,longlong *param_5
                 ,int param_6)

{
  longlong *plVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  ulonglong uVar5;
  undefined8 *puVar6;
  ulonglong uVar7;
  int iVar8;
  longlong lVar9;
  longlong *plVar10;
  
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016ef0();
  }
  if ((longlong)param_2 < 0) {
    iVar8 = -1;
  }
  else {
    uVar7 = 0;
    plVar1 = (longlong *)**(longlong **)(param_1 + 0x10);
    if (((*(byte *)(plVar1 + 4) & 8) != 0) ||
       (plVar10 = *(longlong **)(param_1 + 0x10), plVar1[1] - plVar1[3] == plVar1[2])) {
      plVar10 = plVar1;
    }
    puVar6 = (undefined8 *)*plVar10;
    iVar8 = 0;
    lVar9 = 0;
    if (0 < param_4) {
      do {
        if (param_2 <= uVar7) break;
        if ((*(byte *)(puVar6 + 4) & 8) == 0) {
          uVar5 = (puVar6[1] - puVar6[3]) - puVar6[2];
        }
        else {
          uVar5 = 0;
        }
        if ((param_2 - uVar7 < uVar5) && (param_6 != 0)) {
          uVar5 = param_2 - uVar7;
        }
        lVar2 = puVar6[5];
        lVar9 = lVar9 + 1;
        lVar3 = puVar6[3];
        uVar7 = uVar7 + uVar5;
        iVar8 = iVar8 + 1;
        lVar4 = puVar6[2];
        param_3[1] = uVar5;
        *param_3 = lVar2 + lVar3 + lVar4;
        puVar6 = (undefined8 *)*puVar6;
        param_3 = param_3 + 2;
      } while (lVar9 < param_4);
    }
    *param_5 = (longlong)plVar10;
  }
  return iVar8;
}


// ==== FUN_14000ceb0 @ 14000ceb0  undefined4 FUN_14000ceb0(undefined8 param_1)

undefined4 FUN_14000ceb0(undefined8 param_1)

{
  int iVar1;
  undefined4 local_res10 [6];
  
  local_res10[0] = 0x1000;
  iVar1 = Ordinal_10(param_1,0x4004667f,local_res10);
  if (iVar1 < 0) {
    local_res10[0] = 0xffffffff;
  }
  return local_res10[0];
}


// ==== FUN_14000cee0 @ 14000cee0  undefined4 FUN_14000cee0(longlong * param_1, undefined8 param_2, ulonglong param_3)

undefined4 FUN_14000cee0(longlong *param_1,undefined8 param_2,ulonglong param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  longlong lVar3;
  longlong *plVar4;
  int iVar5;
  undefined4 local_res8 [2];
  undefined4 local_108 [2];
  longlong local_100 [31];
  
  plVar4 = (longlong *)*param_1;
  iVar5 = 0;
  if ((longlong)param_3 < 0) {
    uVar1 = 0xffffffff;
  }
  else {
    if (param_1[6] != 0) {
      FUN_140016ef0();
    }
    lVar3 = 0;
    if (plVar4 != (longlong *)0x0) {
      puVar2 = local_108;
      do {
        if ((0xf < lVar3) || (param_3 == 0)) break;
        *(longlong *)(puVar2 + 2) = plVar4[5] + plVar4[2];
        if (param_3 < (ulonglong)plVar4[3]) {
          lVar3 = (longlong)iVar5;
          iVar5 = iVar5 + 1;
          local_108[lVar3 * 4] = (int)param_3;
          break;
        }
        iVar5 = iVar5 + 1;
        lVar3 = lVar3 + 1;
        *puVar2 = (int)plVar4[3];
        param_3 = param_3 - plVar4[3];
        plVar4 = (longlong *)*plVar4;
        puVar2 = puVar2 + 4;
      } while (plVar4 != (longlong *)0x0);
      if (iVar5 != 0) {
        iVar5 = WSASend(param_2,local_108,iVar5,local_res8,0,0,0);
        if (iVar5 == 0) {
          return local_res8[0];
        }
        return 0xffffffff;
      }
    }
    uVar1 = 0;
  }
  return uVar1;
}


// ==== FUN_14000cfe0 @ 14000cfe0  ulonglong FUN_14000cfe0(undefined8 * param_1, ulonglong * param_2, ulonglong param_3, int param_4)

ulonglong FUN_14000cfe0(undefined8 *param_1,ulonglong *param_2,ulonglong param_3,int param_4)

{
  ulonglong uVar1;
  undefined8 *puVar2;
  ulonglong unaff_RSI;
  
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  if (param_4 == 0) {
    puVar2 = (undefined8 *)*param_1;
    *param_2 = param_3;
    uVar1 = 0;
  }
  else {
    if (param_4 != 1) goto LAB_14000d08e;
    uVar1 = *param_2;
    if (((longlong)uVar1 < 0) || (-param_3 - 1 < uVar1)) {
      if (param_1[6] == 0) {
        return unaff_RSI;
      }
      FUN_140016e50();
      return unaff_RSI;
    }
    puVar2 = (undefined8 *)param_2[1];
    *param_2 = uVar1 + param_3;
    uVar1 = param_2[2];
  }
  for (; puVar2 != (undefined8 *)0x0; puVar2 = (undefined8 *)*puVar2) {
    if (param_3 + uVar1 < (ulonglong)puVar2[3]) {
      param_2[1] = (ulonglong)puVar2;
      param_2[2] = param_3 + uVar1;
      goto LAB_14000d0a5;
    }
    param_3 = param_3 + (uVar1 - puVar2[3]);
    uVar1 = 0;
  }
LAB_14000d08e:
  param_2[1] = 0;
  param_2[2] = 0;
  if (param_3 != 0) {
    *param_2 = 0xffffffffffffffff;
  }
LAB_14000d0a5:
  if (param_1[6] != 0) {
    FUN_140016e50();
  }
  return unaff_RSI;
}


// ==== FUN_14000d0f0 @ 14000d0f0  int FUN_14000d0f0(longlong param_1, ulonglong * param_2, void * param_3, size_t param_4)

int FUN_14000d0f0(longlong param_1,ulonglong *param_2,void *param_3,size_t param_4)

{
  int iVar1;
  ulonglong uVar2;
  size_t _Size;
  undefined8 *puVar3;
  
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016ef0();
  }
  uVar2 = *param_2;
  if ((((longlong)uVar2 < 0) || (-param_4 - 1 < uVar2)) ||
     (*(ulonglong *)(param_1 + 0x18) < uVar2 + param_4)) {
    iVar1 = -1;
  }
  else {
    puVar3 = (undefined8 *)param_2[1];
    uVar2 = param_2[2];
    if (param_4 != 0) {
      do {
        if (puVar3 == (undefined8 *)0x0) break;
        _Size = param_4;
        if ((ulonglong)puVar3[3] < uVar2 + param_4) {
          _Size = puVar3[3] - uVar2;
        }
        iVar1 = memcmp((void *)(puVar3[5] + puVar3[2] + uVar2),param_3,_Size);
        if (iVar1 != 0) {
          return iVar1;
        }
        puVar3 = (undefined8 *)*puVar3;
        param_3 = (void *)((longlong)param_3 + _Size);
        param_4 = param_4 - _Size;
        uVar2 = 0;
      } while (param_4 != 0);
    }
    iVar1 = 0;
  }
  return iVar1;
}


// ==== FUN_14000d1b0 @ 14000d1b0  ulonglong * FUN_14000d1b0(ulonglong * param_1, undefined8 * param_2, char * param_3, ulonglong param_4, ulonglong * param_5, longlong * param_6)

ulonglong *
FUN_14000d1b0(ulonglong *param_1,undefined8 *param_2,char *param_3,ulonglong param_4,
             ulonglong *param_5,longlong *param_6)

{
  char cVar1;
  int iVar2;
  void *pvVar3;
  void *_Buf;
  undefined8 *puVar4;
  undefined8 *puVar5;
  
  puVar5 = (undefined8 *)0x0;
  if (param_2[6] != 0) {
    FUN_140016e30();
  }
  if (param_5 == (ulonglong *)0x0) {
    *param_1 = 0;
    puVar4 = (undefined8 *)*param_2;
    param_1[2] = 0;
    param_1[1] = (ulonglong)puVar4;
  }
  else {
    *param_1 = *param_5;
    param_1[1] = param_5[1];
    param_1[2] = param_5[2];
    puVar4 = (undefined8 *)param_1[1];
  }
  if (param_6 != (longlong *)0x0) {
    puVar5 = (undefined8 *)param_6[1];
  }
  if ((param_4 != 0) && (param_4 < 0x8000000000000000)) {
    if (puVar4 != (undefined8 *)0x0) {
      cVar1 = *param_3;
      do {
        _Buf = (void *)(puVar4[5] + puVar4[2] + param_1[2]);
        pvVar3 = memchr(_Buf,(int)cVar1,puVar4[3] - param_1[2]);
        if (pvVar3 == (void *)0x0) {
          if (puVar4 == puVar5) break;
          *param_1 = *param_1 + (puVar4[3] - param_1[2]);
          puVar4 = (undefined8 *)*puVar4;
          param_1[2] = 0;
          param_1[1] = (ulonglong)puVar4;
        }
        else {
          param_1[2] = (longlong)pvVar3 + (param_1[2] - (longlong)_Buf);
          *param_1 = (longlong)pvVar3 + (*param_1 - (longlong)_Buf);
          iVar2 = FUN_14000d0f0((longlong)param_2,param_1,param_3,param_4);
          if (iVar2 == 0) {
            if ((param_6 == (longlong *)0x0) || ((longlong)(param_4 + *param_1) <= *param_6))
            goto LAB_14000d332;
            break;
          }
          param_1[2] = param_1[2] + 1;
          *param_1 = *param_1 + 1;
          if (param_1[2] == puVar4[3]) {
            puVar4 = (undefined8 *)*puVar4;
            param_1[2] = 0;
            param_1[1] = (ulonglong)puVar4;
          }
        }
      } while (puVar4 != (undefined8 *)0x0);
    }
    *param_1 = 0xffffffffffffffff;
    param_1[1] = 0;
    param_1[2] = 0;
  }
LAB_14000d332:
  if (param_2[6] != 0) {
    FUN_140016e50();
  }
  return param_1;
}


// ==== FUN_14000d370 @ 14000d370  ulonglong FUN_14000d370(undefined8 * param_1, longlong param_2, longlong * param_3, longlong * param_4, int param_5)

ulonglong FUN_14000d370(undefined8 *param_1,longlong param_2,longlong *param_3,longlong *param_4,
                       int param_5)

{
  undefined8 *puVar1;
  longlong lVar2;
  longlong lVar3;
  longlong *plVar4;
  longlong *plVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  longlong lVar8;
  
  uVar6 = 0;
  if ((param_3 == (longlong *)0x0) || (param_3[1] != 0)) {
    if (param_1[6] != 0) {
      FUN_140016e30();
    }
    if (param_3 == (longlong *)0x0) {
      plVar4 = (longlong *)*param_1;
      uVar7 = uVar6;
    }
    else {
      puVar1 = (undefined8 *)param_3[1];
      lVar8 = param_3[2];
      uVar6 = 1;
      uVar7 = puVar1[3] - lVar8;
      if (0 < param_5) {
        lVar2 = puVar1[5];
        lVar3 = puVar1[2];
        param_4[1] = uVar7;
        *param_4 = lVar2 + lVar3 + lVar8;
      }
      plVar4 = (longlong *)*puVar1;
    }
    if (((param_5 == 0) && (param_2 < 0)) && (param_2 = param_1[3], param_3 != (longlong *)0x0)) {
      param_2 = param_2 - *param_3;
    }
    lVar8 = (longlong)(int)uVar6;
    if (plVar4 != (longlong *)0x0) {
      plVar5 = param_4 + lVar8 * 2;
      do {
        if ((-1 < param_2) && (param_2 <= (longlong)uVar7)) break;
        if (lVar8 < param_5) {
          *plVar5 = plVar4[5] + plVar4[2];
          plVar5[1] = plVar4[3];
        }
        else if (param_2 < 0) break;
        uVar7 = uVar7 + plVar4[3];
        plVar4 = (longlong *)*plVar4;
        uVar6 = (ulonglong)((int)uVar6 + 1);
        lVar8 = lVar8 + 1;
        plVar5 = plVar5 + 2;
      } while (plVar4 != (longlong *)0x0);
    }
    if (param_1[6] != 0) {
      FUN_140016e50();
    }
  }
  else {
    uVar6 = 0;
  }
  return uVar6;
}


// ==== FUN_14000d490 @ 14000d490  undefined8 FUN_14000d490(longlong param_1)

undefined8 FUN_14000d490(longlong param_1)

{
  int _FileHandle;
  size_t sVar1;
  int iVar2;
  HANDLE pvVar3;
  longlong lVar4;
  void *pvVar5;
  longlong lVar6;
  int *piVar7;
  longlong lVar8;
  
  _FileHandle = *(int *)(param_1 + 0x14);
  sVar1 = *(size_t *)(param_1 + 0x40);
  lVar6 = *(longlong *)(param_1 + 0x30);
  if (*(longlong *)(param_1 + 0x28) != 0) {
    return 0;
  }
  lVar8 = 0;
  if ((*(byte *)(param_1 + 0xc) & 2) == 0) {
    pvVar3 = (HANDLE)_get_osfhandle(_FileHandle);
    if (pvVar3 == (HANDLE)0xffffffffffffffff) {
      return 0xffffffff;
    }
    pvVar3 = CreateFileMappingA(pvVar3,(LPSECURITY_ATTRIBUTES)0x0,2,(DWORD)(lVar6 + sVar1 >> 0x20),
                                (DWORD)(lVar6 + sVar1),(LPCSTR)0x0);
    if (pvVar3 != (HANDLE)0xffffffffffffffff) {
      *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | 2;
      *(HANDLE *)(param_1 + 0x20) = pvVar3;
      *(longlong *)(param_1 + 0x38) = lVar6;
      return 0;
    }
  }
  lVar4 = _lseeki64(_FileHandle,0,1);
  pvVar5 = FUN_140011830(sVar1);
  if (pvVar5 != (void *)0x0) {
    if (lVar4 < 0) {
      FUN_1400119c0(pvVar5);
    }
    else {
      lVar6 = _lseeki64(_FileHandle,lVar6,0);
      if (-1 < lVar6) {
        lVar6 = lVar8;
        if (0 < (longlong)sVar1) {
          do {
            iVar2 = _read(_FileHandle,(void *)(lVar8 + (longlong)pvVar5),(int)sVar1 - (int)lVar8);
            lVar6 = (longlong)iVar2;
            if (iVar2 < 1) break;
            lVar8 = lVar8 + lVar6;
          } while (lVar8 < (longlong)sVar1);
        }
        piVar7 = _errno();
        iVar2 = *piVar7;
        lVar4 = _lseeki64(_FileHandle,lVar4,0);
        if ((lVar6 < 0) || ((lVar6 == 0 && (lVar8 < (longlong)sVar1)))) {
          FUN_1400119c0(pvVar5);
          piVar7 = _errno();
          *piVar7 = iVar2;
          return 0xffffffff;
        }
        if (-1 < lVar4) {
          *(void **)(param_1 + 0x28) = pvVar5;
          return 0;
        }
      }
      FUN_1400119c0(pvVar5);
    }
  }
  return 0xffffffff;
}


// ==== FUN_14000d630 @ 14000d630  undefined FUN_14000d630(longlong * param_1)

void FUN_14000d630(longlong *param_1)

{
  longlong lVar1;
  
  if (*param_1 != 0) {
    FUN_140016e30();
  }
  *(int *)(param_1 + 1) = (int)param_1[1] + -1;
  lVar1 = param_1[1];
  if (*param_1 != 0) {
    FUN_140016e50();
  }
  if ((int)lVar1 < 1) {
    if ((*(byte *)(param_1 + 2) & 2) == 0) {
      if ((void *)param_1[5] != (void *)0x0) {
        FUN_1400119c0((void *)param_1[5]);
      }
    }
    else {
      CloseHandle((HANDLE)param_1[4]);
    }
    if (((*(byte *)((longlong)param_1 + 0xc) & 1) != 0) && (-1 < *(int *)((longlong)param_1 + 0x14))
       ) {
      _close(*(int *)((longlong)param_1 + 0x14));
    }
    if ((code *)param_1[9] != (code *)0x0) {
      (*(code *)param_1[9])(param_1,*(undefined4 *)((longlong)param_1 + 0xc),param_1[10]);
      param_1[9] = 0;
      param_1[10] = 0;
    }
    if (*param_1 != 0) {
      FUN_140016e10();
    }
    FUN_1400119c0(param_1);
  }
  return;
}


// ==== FUN_14000d6e0 @ 14000d6e0  longlong * FUN_14000d6e0(longlong param_1, longlong param_2, longlong param_3)

longlong * FUN_14000d6e0(longlong param_1,longlong param_2,longlong param_3)

{
  longlong *plVar1;
  longlong lVar2;
  longlong *plVar3;
  
  plVar3 = (longlong *)FUN_140011850(1,0x28);
  if (plVar3 != (longlong *)0x0) {
    if (*(longlong *)(param_1 + 0x30) != 0) {
      FUN_140016e30();
    }
    plVar1 = (longlong *)(param_1 + 0x78);
    plVar3[2] = param_2;
    plVar3[3] = param_3;
    *(undefined4 *)(plVar3 + 4) = 1;
    lVar2 = *plVar1;
    *plVar3 = lVar2;
    if (lVar2 != 0) {
      *(longlong **)(*plVar1 + 8) = plVar3;
    }
    *plVar1 = (longlong)plVar3;
    plVar3[1] = (longlong)plVar1;
    if (*(longlong *)(param_1 + 0x30) != 0) {
      FUN_140016e50();
    }
  }
  return plVar3;
}


// ==== FUN_14000d780 @ 14000d780  undefined8 FUN_14000d780(longlong param_1, longlong * param_2)

undefined8 FUN_14000d780(longlong param_1,longlong *param_2)

{
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e30();
  }
  if (*param_2 != 0) {
    *(longlong *)(*param_2 + 8) = param_2[1];
  }
  *(longlong *)param_2[1] = *param_2;
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e50();
  }
  FUN_1400119c0(param_2);
  return 0;
}


// ==== FUN_14000d7e0 @ 14000d7e0  undefined8 FUN_14000d7e0(longlong param_1, longlong param_2, longlong param_3)

undefined8 FUN_14000d7e0(longlong param_1,longlong param_2,longlong param_3)

{
  longlong *plVar1;
  undefined8 uVar2;
  
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e30();
  }
  plVar1 = *(longlong **)(param_1 + 0x78);
  do {
    uVar2 = 0xffffffff;
    if (plVar1 == (longlong *)0x0) {
LAB_14000d87b:
      if (*(longlong *)(param_1 + 0x30) != 0) {
        FUN_140016e50();
      }
      return uVar2;
    }
    if ((param_2 == plVar1[2]) && (param_3 == plVar1[3])) {
      if (*(longlong *)(param_1 + 0x30) != 0) {
        FUN_140016e30();
      }
      if (*plVar1 != 0) {
        *(longlong *)(*plVar1 + 8) = plVar1[1];
      }
      *(longlong *)plVar1[1] = *plVar1;
      if (*(longlong *)(param_1 + 0x30) != 0) {
        FUN_140016e50();
      }
      FUN_1400119c0(plVar1);
      uVar2 = 0;
      goto LAB_14000d87b;
    }
    plVar1 = (longlong *)*plVar1;
  } while( true );
}


// ==== FUN_14000d8b0 @ 14000d8b0  undefined8 FUN_14000d8b0(longlong param_1, longlong param_2, ushort param_3)

undefined8 FUN_14000d8b0(longlong param_1,longlong param_2,ushort param_3)

{
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e30();
  }
  *(uint *)(param_2 + 0x20) = *(uint *)(param_2 + 0x20) | (uint)param_3;
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e50();
  }
  return 0;
}


// ==== FUN_14000d900 @ 14000d900  undefined8 FUN_14000d900(longlong param_1, longlong param_2, ushort param_3)

undefined8 FUN_14000d900(longlong param_1,longlong param_2,ushort param_3)

{
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e30();
  }
  *(uint *)(param_2 + 0x20) = *(uint *)(param_2 + 0x20) & ~(uint)param_3;
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e50();
  }
  return 0;
}


// ==== FUN_14000d950 @ 14000d950  undefined8 FUN_14000d950(longlong param_1, int param_2)

undefined8 FUN_14000d950(longlong param_1,int param_2)

{
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e30();
  }
  if (param_2 == 0) {
    *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) | 4;
  }
  else {
    *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) | 2;
  }
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e50();
  }
  return 0;
}


// ==== FUN_14000d9a0 @ 14000d9a0  undefined8 FUN_14000d9a0(longlong param_1, int param_2)

undefined8 FUN_14000d9a0(longlong param_1,int param_2)

{
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e30();
  }
  if (param_2 == 0) {
    *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) & 0xfffffffb;
  }
  else {
    *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) & 0xfffffffd;
  }
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e50();
  }
  return 0;
}


// ==== FUN_14000d9f0 @ 14000d9f0  undefined8 FUN_14000d9f0(longlong param_1, longlong * param_2, int param_3)

undefined8 FUN_14000d9f0(longlong param_1,longlong *param_2,int param_3)

{
  undefined8 uVar1;
  
  uVar1 = 0;
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e30();
  }
  if ((*(byte *)(param_1 + 0x38) & 8) != 0) {
    if (param_3 < 1) {
      uVar1 = 0xffffffff;
    }
    else {
      uVar1 = 1;
      *param_2 = param_1 + 0x50;
    }
  }
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e50();
  }
  return uVar1;
}


// ==== FUN_14000da70 @ 14000da70  undefined FUN_14000da70(void * param_1)

void FUN_14000da70(void *param_1)

{
  uint uVar1;
  
  *(int *)((longlong)param_1 + 0x24) = *(int *)((longlong)param_1 + 0x24) + -1;
  if (*(int *)((longlong)param_1 + 0x24) < 1) {
    uVar1 = *(uint *)((longlong)param_1 + 0x20);
    if ((uVar1 & 0x30) != 0) {
      *(uint *)((longlong)param_1 + 0x20) = uVar1 | 0x40;
      *(int *)((longlong)param_1 + 0x24) = *(int *)((longlong)param_1 + 0x24) + 1;
      return;
    }
    if (((uVar1 & 4) != 0) && (*(code **)((longlong)param_1 + 0x30) != (code *)0x0)) {
      (**(code **)((longlong)param_1 + 0x30))
                (*(undefined8 *)((longlong)param_1 + 0x28),*(undefined8 *)((longlong)param_1 + 8),
                 *(undefined8 *)((longlong)param_1 + 0x38));
    }
    if (((*(byte *)((longlong)param_1 + 0x20) & 1) != 0) &&
       (*(longlong *)((longlong)param_1 + 0x30) != 0)) {
      if ((*(byte *)(*(longlong *)((longlong)param_1 + 0x30) + 0x10) & 2) != 0) {
        UnmapViewOfFile(*(LPCVOID *)((longlong)param_1 + 0x28));
      }
      FUN_14000d630(*(longlong **)((longlong)param_1 + 0x30));
    }
    if ((*(byte *)((longlong)param_1 + 0x20) & 0x80) != 0) {
      if (*(longlong *)(*(longlong *)((longlong)param_1 + 0x30) + 0x30) != 0) {
        FUN_140016e30();
      }
      FUN_14000da70(*(void **)((longlong)param_1 + 0x38));
      FUN_14000c220(*(undefined8 **)((longlong)param_1 + 0x30));
    }
    FUN_1400119c0(param_1);
  }
  return;
}


// ==== FUN_14000db20 @ 14000db20  undefined FUN_14000db20(longlong * param_1)

void FUN_14000db20(longlong *param_1)

{
  longlong *plVar1;
  
  if (param_1 != (longlong *)0x0) {
    do {
      plVar1 = (longlong *)*param_1;
      FUN_14000da70(param_1);
      param_1 = plVar1;
    } while (plVar1 != (longlong *)0x0);
  }
  return;
}


// ==== FUN_14000db50 @ 14000db50  longlong * FUN_14000db50(longlong param_1)

longlong * FUN_14000db50(longlong param_1)

{
  longlong *plVar1;
  longlong *plVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_1 + 0x10);
  if (*plVar3 != 0) {
    do {
      plVar2 = (longlong *)*plVar3;
      if ((plVar2[3] == 0) && ((*(byte *)(plVar2 + 4) & 0x30) == 0)) break;
      plVar3 = plVar2;
    } while (*plVar2 != 0);
    plVar2 = (longlong *)*plVar3;
    if (plVar2 != (longlong *)0x0) {
      do {
        plVar1 = (longlong *)*plVar2;
        FUN_14000da70(plVar2);
        plVar2 = plVar1;
      } while (plVar1 != (longlong *)0x0);
      *plVar3 = 0;
    }
  }
  return plVar3;
}


// ==== FUN_14000dbb0 @ 14000dbb0  undefined FUN_14000dbb0(longlong * param_1, longlong param_2)

void FUN_14000dbb0(longlong *param_1,longlong param_2)

{
  longlong *plVar1;
  longlong *plVar2;
  longlong *plVar3;
  
  if (param_1[6] != 0) {
    FUN_140016ef0();
  }
  plVar3 = (longlong *)param_1[2];
  if (*plVar3 == 0) {
    *param_1 = param_2;
  }
  else {
    if (*plVar3 != 0) {
      do {
        plVar2 = (longlong *)*plVar3;
        if ((plVar2[3] == 0) && ((*(byte *)(plVar2 + 4) & 0x30) == 0)) break;
        plVar3 = plVar2;
      } while (*plVar2 != 0);
      plVar2 = (longlong *)*plVar3;
      if (plVar2 != (longlong *)0x0) {
        do {
          plVar1 = (longlong *)*plVar2;
          FUN_14000da70(plVar2);
          plVar2 = plVar1;
        } while (plVar1 != (longlong *)0x0);
        *plVar3 = 0;
      }
    }
    *plVar3 = param_2;
    if (*(longlong *)(param_2 + 0x18) != 0) {
      param_1[2] = (longlong)plVar3;
    }
  }
  param_1[1] = param_2;
  param_1[3] = param_1[3] + *(longlong *)(param_2 + 0x18);
  return;
}


// ==== FUN_14000dc60 @ 14000dc60  undefined8 * FUN_14000dc60(longlong * param_1, ulonglong param_2)

undefined8 * FUN_14000dc60(longlong *param_1,ulonglong param_2)

{
  undefined8 *puVar1;
  
  puVar1 = FUN_14000bdc0(param_2);
  if (puVar1 == (undefined8 *)0x0) {
    return (undefined8 *)0x0;
  }
  FUN_14000dbb0(param_1,(longlong)puVar1);
  return puVar1;
}


// ==== FUN_14000dcb0 @ 14000dcb0  undefined FUN_14000dcb0(void * param_1, uint param_2)

void FUN_14000dcb0(void *param_1,uint param_2)

{
  *(uint *)((longlong)param_1 + 0x20) = *(uint *)((longlong)param_1 + 0x20) & ~param_2;
  if ((*(byte *)((longlong)param_1 + 0x20) & 0x40) != 0) {
    FUN_14000da70(param_1);
  }
  return;
}


// ==== FUN_14000dcd0 @ 14000dcd0  undefined FUN_14000dcd0(undefined8 param_1, undefined8 * param_2)

void FUN_14000dcd0(undefined8 param_1,undefined8 *param_2)

{
  longlong *plVar1;
  
  if (param_2[6] != 0) {
    FUN_140016e30();
  }
  plVar1 = (longlong *)param_2[0x10];
  FUN_14000c060((longlong)param_2,1);
  FUN_14000c220(param_2);
  if (plVar1 != (longlong *)0x0) {
    FUN_140006120(plVar1);
  }
  return;
}


// ==== FUN_14000dd30 @ 14000dd30  undefined FUN_14000dd30(longlong * param_1, undefined8 * param_2, undefined8 param_3, undefined8 param_4)

void FUN_14000dd30(longlong *param_1,undefined8 *param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  undefined8 *puVar3;
  
  puVar1 = (undefined8 *)*param_2;
  if (param_1[6] != 0) {
    FUN_140016ef0();
  }
  if (param_2[6] != 0) {
    FUN_140016ef0();
  }
  do {
    if (puVar1 == (undefined8 *)0x0) {
      return;
    }
    if ((puVar1[3] != 0) && ((*(byte *)(puVar1 + 4) & 0x40) == 0)) {
      puVar3 = (undefined8 *)FUN_140011830(0x400);
      if (puVar3 == (undefined8 *)0x0) {
        FUN_140019050("%s: out of memory","APPEND_CHAIN_MULTICAST",param_3,param_4);
        return;
      }
      *puVar3 = 0;
      puVar3[2] = 0;
      puVar3[3] = 0;
      puVar3[4] = 0;
      puVar3[1] = 0x3d0;
      puVar3[5] = puVar3 + 6;
      *(undefined4 *)((longlong)puVar3 + 0x24) = 1;
      if (param_2[6] != 0) {
        FUN_140016e30();
      }
      *(int *)(param_2 + 9) = *(int *)(param_2 + 9) + 1;
      if (param_2[6] != 0) {
        FUN_140016e50();
      }
      puVar3[6] = param_2;
      *(int *)((longlong)puVar1 + 0x24) = *(int *)((longlong)puVar1 + 0x24) + 1;
      puVar3[7] = puVar1;
      *(uint *)(puVar1 + 4) = *(uint *)(puVar1 + 4) | 8;
      puVar3[1] = puVar1[1];
      puVar3[2] = puVar1[2];
      uVar2 = puVar1[3];
      *(uint *)(puVar3 + 4) = *(uint *)(puVar3 + 4) | 0x88;
      puVar3[3] = uVar2;
      puVar3[5] = puVar1[5];
      FUN_14000dbb0(param_1,(longlong)puVar3);
    }
    puVar1 = (undefined8 *)*puVar1;
  } while( true );
}


// ==== FUN_14000de70 @ 14000de70  undefined8 FUN_14000de70(longlong * param_1, longlong * param_2)

undefined8 FUN_14000de70(longlong *param_1,longlong *param_2)

{
  longlong lVar1;
  longlong lVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  longlong *plVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  ulonglong uVar10;
  undefined8 uVar11;
  bool bVar12;
  longlong local_res8;
  longlong local_res10;
  
  uVar10 = param_2[6];
  uVar8 = param_1[6];
  uVar11 = 0;
  uVar7 = uVar8;
  if (uVar10 != 0) {
    if ((uVar8 != 0) && (uVar8 < uVar10)) {
      uVar7 = uVar10;
      uVar10 = uVar8;
    }
    if (uVar10 != 0) {
      FUN_140016e30();
    }
  }
  if ((uVar7 != uVar10) && (uVar7 != 0)) {
    FUN_140016e30();
  }
  lVar1 = param_2[3];
  lVar2 = param_1[3];
  if ((lVar1 != 0) && (param_1 != param_2)) {
    if (((*(byte *)(param_1 + 7) & 4) == 0) &&
       (((*(byte *)(param_2 + 7) & 2) == 0 &&
        (uVar5 = FUN_14000c6c0((longlong)param_2,&local_res10,&local_res8), -1 < (int)uVar5)))) {
      if (lVar2 == 0) {
        puVar4 = (undefined8 *)*param_1;
        while (puVar4 != (undefined8 *)0x0) {
          puVar3 = (undefined8 *)*puVar4;
          FUN_14000da70(puVar4);
          puVar4 = puVar3;
        }
        FUN_14000c810(param_1,param_2);
      }
      else {
        if (param_1[6] != 0) {
          FUN_140016ef0();
        }
        if (param_2[6] != 0) {
          FUN_140016ef0();
        }
        *(longlong *)param_1[1] = *param_2;
        plVar6 = (longlong *)param_2[2];
        if (plVar6 == param_2) {
          plVar6 = (longlong *)param_1[1];
        }
        param_1[2] = (longlong)plVar6;
        param_1[1] = param_2[1];
        param_1[3] = param_1[3] + param_2[3];
      }
      FUN_14000c7b0(param_2,local_res10,local_res8);
      param_2[5] = param_2[5] + lVar1;
      param_1[4] = param_1[4] + lVar1;
      FUN_14000c160((longlong)param_2);
      FUN_14000c160((longlong)param_1);
    }
    else {
      uVar11 = 0xffffffff;
    }
  }
  uVar10 = param_2[6];
  uVar8 = param_1[6];
  uVar7 = uVar8;
  uVar9 = uVar10;
  if (((uVar10 == 0) || (uVar8 == 0)) ||
     (bVar12 = uVar8 == uVar10, uVar7 = uVar10, uVar9 = uVar8, uVar8 < uVar10)) {
    bVar12 = uVar7 == uVar9;
    uVar8 = uVar7;
    uVar10 = uVar9;
  }
  if ((!bVar12) && (uVar8 != 0)) {
    FUN_140016e50();
  }
  if (uVar10 != 0) {
    FUN_140016e50();
  }
  return uVar11;
}


// ==== FUN_14000e010 @ 14000e010  undefined8 FUN_14000e010(longlong * param_1, longlong * param_2, undefined8 param_3, undefined8 param_4)

undefined8 FUN_14000e010(longlong *param_1,longlong *param_2,undefined8 param_3,undefined8 param_4)

{
  longlong lVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  undefined8 uVar8;
  bool bVar9;
  
  uVar7 = param_2[6];
  uVar5 = param_1[6];
  uVar8 = 0;
  uVar4 = uVar5;
  if (uVar7 != 0) {
    if ((uVar5 != 0) && (uVar5 < uVar7)) {
      uVar4 = uVar7;
      uVar7 = uVar5;
    }
    if (uVar7 != 0) {
      FUN_140016e30();
    }
  }
  if ((uVar4 != uVar7) && (uVar4 != 0)) {
    FUN_140016e30();
  }
  lVar1 = param_2[3];
  puVar2 = (undefined8 *)*param_2;
  if (lVar1 != 0) {
    if (((*(byte *)(param_1 + 7) & 4) == 0) && (param_1 != param_2)) {
      for (; puVar2 != (undefined8 *)0x0; puVar2 = (undefined8 *)*puVar2) {
        if ((*(byte *)(puVar2 + 4) & 0x83) != 0) goto LAB_14000e0d9;
      }
      if (param_1[3] == 0) {
        puVar2 = (undefined8 *)*param_1;
        while (puVar2 != (undefined8 *)0x0) {
          puVar3 = (undefined8 *)*puVar2;
          FUN_14000da70(puVar2);
          puVar2 = puVar3;
        }
      }
      FUN_14000dd30(param_1,param_2,param_3,param_4);
      param_1[4] = param_1[4] + lVar1;
      FUN_14000c160((longlong)param_1);
    }
    else {
LAB_14000e0d9:
      uVar8 = 0xffffffff;
    }
  }
  uVar7 = param_2[6];
  uVar5 = param_1[6];
  uVar4 = uVar5;
  uVar6 = uVar7;
  if (((uVar7 == 0) || (uVar5 == 0)) ||
     (bVar9 = uVar5 == uVar7, uVar4 = uVar7, uVar6 = uVar5, uVar5 < uVar7)) {
    bVar9 = uVar4 == uVar6;
    uVar5 = uVar4;
    uVar7 = uVar6;
  }
  if ((!bVar9) && (uVar5 != 0)) {
    FUN_140016e50();
  }
  if (uVar7 != 0) {
    FUN_140016e50();
  }
  return uVar8;
}


// ==== FUN_14000e140 @ 14000e140  undefined8 FUN_14000e140(longlong * param_1, longlong * param_2)

undefined8 FUN_14000e140(longlong *param_1,longlong *param_2)

{
  longlong lVar1;
  longlong lVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 uVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  undefined8 uVar10;
  bool bVar11;
  longlong local_res8;
  longlong local_res10;
  
  uVar9 = param_2[6];
  uVar7 = param_1[6];
  uVar10 = 0;
  uVar6 = uVar7;
  if (uVar9 != 0) {
    if ((uVar7 != 0) && (uVar7 < uVar9)) {
      uVar6 = uVar9;
      uVar9 = uVar7;
    }
    if (uVar9 != 0) {
      FUN_140016e30();
    }
  }
  if ((uVar6 != uVar9) && (uVar6 != 0)) {
    FUN_140016e30();
  }
  lVar1 = param_2[3];
  lVar2 = param_1[3];
  if ((lVar1 != 0) && (param_2 != param_1)) {
    if (((*(byte *)(param_1 + 7) & 2) == 0) &&
       (((*(byte *)(param_2 + 7) & 2) == 0 &&
        (uVar5 = FUN_14000c6c0((longlong)param_2,&local_res10,&local_res8), -1 < (int)uVar5)))) {
      if (lVar2 == 0) {
        puVar4 = (undefined8 *)*param_1;
        while (puVar4 != (undefined8 *)0x0) {
          puVar3 = (undefined8 *)*puVar4;
          FUN_14000da70(puVar4);
          puVar4 = puVar3;
        }
        FUN_14000c810(param_1,param_2);
      }
      else {
        FUN_14000c8d0(param_1,param_2);
      }
      FUN_14000c7b0(param_2,local_res10,local_res8);
      param_2[5] = param_2[5] + lVar1;
      param_1[4] = param_1[4] + lVar1;
      FUN_14000c160((longlong)param_2);
      FUN_14000c160((longlong)param_1);
    }
    else {
      uVar10 = 0xffffffff;
    }
  }
  uVar9 = param_2[6];
  uVar7 = param_1[6];
  uVar6 = uVar7;
  uVar8 = uVar9;
  if (((uVar9 == 0) || (uVar7 == 0)) ||
     (bVar11 = uVar7 == uVar9, uVar6 = uVar9, uVar8 = uVar7, uVar7 < uVar9)) {
    bVar11 = uVar6 == uVar8;
    uVar7 = uVar6;
    uVar9 = uVar8;
  }
  if ((!bVar11) && (uVar7 != 0)) {
    FUN_140016e50();
  }
  if (uVar9 != 0) {
    FUN_140016e50();
  }
  return uVar10;
}


// ==== FUN_14000e2a0 @ 14000e2a0  undefined8 FUN_14000e2a0(longlong * param_1, ulonglong param_2)

undefined8 FUN_14000e2a0(longlong *param_1,ulonglong param_2)

{
  undefined8 *puVar1;
  longlong lVar2;
  undefined8 *puVar3;
  longlong *plVar4;
  longlong *plVar5;
  ulonglong uVar6;
  undefined8 uVar7;
  
  uVar7 = 0;
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  uVar6 = param_1[3];
  if (uVar6 != 0) {
    if ((*(byte *)(param_1 + 7) & 2) == 0) {
      if ((param_2 < uVar6) ||
         ((param_1[1] != 0 && (param_2 = uVar6, (*(byte *)(param_1[1] + 0x20) & 0x10) != 0)))) {
        plVar4 = (longlong *)*param_1;
        param_1[3] = uVar6 - param_2;
        plVar5 = plVar4;
        uVar6 = param_2;
        if ((ulonglong)plVar4[3] <= param_2) {
          do {
            uVar6 = uVar6 - plVar4[3];
            plVar5 = (longlong *)*plVar4;
            if (plVar4 == *(longlong **)param_1[2]) {
              param_1[2] = (longlong)param_1;
            }
            if (plVar4 == (longlong *)param_1[2]) {
              param_1[2] = (longlong)param_1;
            }
            if ((*(byte *)(plVar4 + 4) & 0x10) != 0) {
              lVar2 = plVar4[3];
              plVar4[3] = 0;
              plVar4[2] = plVar4[2] + lVar2;
              plVar5 = plVar4;
              break;
            }
            FUN_14000da70(plVar4);
            plVar4 = plVar5;
          } while ((ulonglong)plVar5[3] <= uVar6);
        }
        *param_1 = (longlong)plVar5;
        plVar5[2] = plVar5[2] + uVar6;
        plVar5[3] = plVar5[3] - uVar6;
        uVar6 = param_2;
      }
      else {
        puVar3 = (undefined8 *)*param_1;
        while (puVar3 != (undefined8 *)0x0) {
          puVar1 = (undefined8 *)*puVar3;
          FUN_14000da70(puVar3);
          puVar3 = puVar1;
        }
        if (param_1[6] != 0) {
          FUN_140016ef0();
        }
        *param_1 = 0;
        param_1[1] = 0;
        param_1[2] = (longlong)param_1;
        param_1[3] = 0;
      }
      param_1[5] = param_1[5] + uVar6;
      FUN_14000c160((longlong)param_1);
    }
    else {
      uVar7 = 0xffffffff;
    }
  }
  if (param_1[6] != 0) {
    FUN_140016e50();
  }
  return uVar7;
}


// ==== FUN_14000e3e0 @ 14000e3e0  ulonglong FUN_14000e3e0(longlong * param_1, void * param_2, ulonglong param_3)

ulonglong FUN_14000e3e0(longlong *param_1,void *param_2,ulonglong param_3)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  uVar1 = FUN_14000c950(param_1,(longlong *)0x0,param_2,param_3);
  if (0 < (longlong)uVar1) {
    uVar2 = FUN_14000e2a0(param_1,uVar1);
    if ((int)uVar2 < 0) {
      uVar1 = 0xffffffffffffffff;
    }
  }
  if (param_1[6] != 0) {
    FUN_140016e50();
  }
  return uVar1 & 0xffffffff;
}


// ==== FUN_14000e470 @ 14000e470  ulonglong FUN_14000e470(undefined8 * param_1, ulonglong param_2)

ulonglong FUN_14000e470(undefined8 *param_1,ulonglong param_2)

{
  longlong *plVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  longlong *plVar4;
  ulonglong uVar5;
  longlong *plVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  int iVar9;
  int iVar10;
  ulonglong uVar11;
  void *_Dst;
  
  uVar11 = 0;
  iVar9 = 0;
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  plVar1 = (longlong *)*param_1;
  if ((longlong)param_2 < 0) {
    param_2 = param_1[3];
  }
  if ((param_2 != 0) && (param_2 <= (ulonglong)param_1[3])) {
    uVar7 = plVar1[3];
    if (uVar7 < param_2) {
      uVar8 = param_2 - uVar7;
      plVar6 = (longlong *)*plVar1;
      uVar5 = uVar8;
      for (puVar2 = plVar6; puVar2 != (undefined8 *)0x0; puVar2 = (undefined8 *)*puVar2) {
        if ((*(byte *)(puVar2 + 4) & 0x30) != 0) goto LAB_14000e692;
        if (uVar5 <= (ulonglong)puVar2[3]) break;
        uVar5 = uVar5 - puVar2[3];
      }
      plVar4 = plVar1;
      if ((*(uint *)(plVar1 + 4) & 0x30) == 0) {
        if ((ulonglong)(plVar1[1] - plVar1[2]) < param_2) {
          plVar4 = FUN_14000bdc0(param_2);
          if (plVar4 == (undefined8 *)0x0) {
            FUN_140019050("%s: out of memory","evbuffer_pullup",uVar7,uVar8);
            goto LAB_14000e692;
          }
          _Dst = (void *)plVar4[5];
          plVar4[3] = param_2;
          *param_1 = plVar4;
          plVar6 = plVar1;
        }
        else {
          plVar1[3] = param_2;
          _Dst = (void *)(plVar1[5] + plVar1[2] + uVar7);
          param_2 = param_2 - uVar7;
        }
      }
      else {
        uVar5 = uVar11;
        if ((*(uint *)(plVar1 + 4) & 8) == 0) {
          uVar5 = (plVar1[1] - plVar1[2]) - uVar7;
        }
        if (uVar5 < uVar8) goto LAB_14000e692;
        plVar1[3] = param_2;
        _Dst = (void *)(plVar1[5] + plVar1[2] + uVar7);
        param_2 = param_2 - uVar7;
      }
      puVar2 = *(undefined8 **)param_1[2];
      iVar10 = iVar9;
      while (plVar6 != (undefined8 *)0x0) {
        iVar10 = (int)uVar11;
        if (param_2 < (ulonglong)plVar6[3]) {
          memcpy(_Dst,(void *)(plVar6[5] + plVar6[2]),param_2);
          plVar6[2] = plVar6[2] + param_2;
          plVar6[3] = plVar6[3] - param_2;
          goto LAB_14000e629;
        }
        puVar3 = (undefined8 *)*plVar6;
        memcpy(_Dst,(void *)(plVar6[5] + plVar6[2]),plVar6[3]);
        param_2 = param_2 - plVar6[3];
        _Dst = (void *)((longlong)_Dst + plVar6[3]);
        if (plVar6 == puVar2) {
          uVar11 = 1;
        }
        iVar10 = (int)uVar11;
        if (plVar6 == (undefined8 *)param_1[2]) {
          iVar9 = 1;
        }
        FUN_14000da70(plVar6);
        plVar6 = puVar3;
      }
      param_1[1] = plVar4;
LAB_14000e629:
      *plVar4 = (longlong)plVar6;
      if (iVar10 == 0) {
        if (iVar9 != 0) {
          plVar1 = (longlong *)*param_1;
          if ((*plVar1 == 0) || (*(longlong *)(*plVar1 + 0x18) == 0)) {
            param_1[2] = param_1;
          }
          else {
            param_1[2] = plVar1;
          }
        }
      }
      else {
        param_1[2] = param_1;
      }
      uVar11 = plVar4[5] + plVar4[2];
    }
    else {
      uVar11 = plVar1[5] + plVar1[2];
    }
  }
LAB_14000e692:
  if (param_1[6] != 0) {
    FUN_140016e50();
  }
  return uVar11;
}


// ==== FUN_14000e6c0 @ 14000e6c0  undefined4 FUN_14000e6c0(longlong * param_1, void * param_2, ulonglong param_3)

undefined4 FUN_14000e6c0(longlong *param_1,void *param_2,ulonglong param_3)

{
  longlong lVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  size_t _Size;
  size_t _Size_00;
  undefined4 uVar6;
  
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  uVar6 = 0xffffffff;
  if (((*(byte *)(param_1 + 7) & 4) != 0) || (-param_1[3] - 1U < param_3)) goto LAB_14000e870;
  puVar2 = (undefined8 *)param_1[1];
  uVar6 = 0xffffffff;
  if (puVar2 == (undefined8 *)0x0) {
    puVar2 = FUN_14000bdc0(param_3);
    if (puVar2 == (undefined8 *)0x0) goto LAB_14000e870;
    FUN_14000dbb0(param_1,(longlong)puVar2);
  }
  if ((*(uint *)(puVar2 + 4) & 8) == 0) {
    uVar4 = puVar2[3];
    lVar1 = puVar2[2];
    uVar5 = puVar2[1] - uVar4;
    _Size = uVar5 - lVar1;
    if (_Size < param_3) {
      if (((((*(uint *)(puVar2 + 4) & 0x30) != 0) || (uVar5 < param_3)) ||
          ((ulonglong)puVar2[1] >> 1 <= uVar4)) || (0x800 < uVar4)) goto LAB_14000e7e4;
      memmove((void *)puVar2[5],(void *)((longlong)puVar2[5] + lVar1),uVar4);
      puVar2[2] = 0;
      memcpy((void *)(puVar2[5] + puVar2[3]),param_2,param_3);
      puVar2[3] = puVar2[3] + param_3;
      param_1[3] = param_1[3] + param_3;
      param_1[4] = param_1[4] + param_3;
    }
    else {
      memcpy((void *)(puVar2[5] + lVar1 + uVar4),param_2,param_3);
      puVar2[3] = puVar2[3] + param_3;
      param_1[3] = param_1[3] + param_3;
      param_1[4] = param_1[4] + param_3;
    }
  }
  else {
    _Size = 0;
LAB_14000e7e4:
    uVar4 = puVar2[1];
    if (uVar4 < 0x801) {
      uVar4 = uVar4 * 2;
    }
    if (uVar4 < param_3) {
      uVar4 = param_3;
    }
    puVar3 = FUN_14000bdc0(uVar4);
    if (puVar3 == (undefined8 *)0x0) goto LAB_14000e870;
    if (_Size != 0) {
      memcpy((void *)(puVar2[5] + puVar2[2] + puVar2[3]),param_2,_Size);
      puVar2[3] = puVar2[3] + _Size;
      param_1[3] = param_1[3] + _Size;
      param_1[4] = param_1[4] + _Size;
    }
    _Size_00 = param_3 - _Size;
    memcpy((void *)puVar3[5],(void *)((longlong)param_2 + _Size),_Size_00);
    puVar3[3] = _Size_00;
    FUN_14000dbb0(param_1,(longlong)puVar3);
    param_1[4] = param_1[4] + _Size_00;
  }
  FUN_14000c160((longlong)param_1);
  uVar6 = 0;
LAB_14000e870:
  if (param_1[6] != 0) {
    FUN_140016e50();
  }
  return uVar6;
}


// ==== FUN_14000e8a0 @ 14000e8a0  undefined4 FUN_14000e8a0(longlong * param_1, void * param_2, ulonglong param_3)

undefined4 FUN_14000e8a0(longlong *param_1,void *param_2,ulonglong param_3)

{
  ulonglong _Size;
  undefined8 *puVar1;
  undefined8 *puVar2;
  undefined4 uVar3;
  
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  uVar3 = 0xffffffff;
  if (((*(byte *)(param_1 + 7) & 2) != 0) || (-param_1[3] - 1U < param_3)) goto LAB_14000e9f0;
  puVar1 = (undefined8 *)*param_1;
  uVar3 = 0xffffffff;
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = FUN_14000bdc0(param_3);
    if (puVar1 == (undefined8 *)0x0) goto LAB_14000e9f0;
    FUN_14000dbb0(param_1,(longlong)puVar1);
  }
  if ((*(byte *)(puVar1 + 4) & 8) == 0) {
    if (puVar1[3] == 0) {
      puVar1[2] = puVar1[1];
    }
    _Size = puVar1[2];
    if (_Size < param_3) {
      if (_Size != 0) {
        memcpy((void *)puVar1[5],(void *)((longlong)param_2 + (param_3 - _Size)),_Size);
        puVar1[3] = puVar1[3] + puVar1[2];
        param_1[3] = param_1[3] + puVar1[2];
        param_1[4] = param_1[4] + puVar1[2];
        param_3 = param_3 - puVar1[2];
        puVar1[2] = 0;
      }
      goto LAB_14000e997;
    }
    memcpy((void *)((puVar1[5] - param_3) + _Size),param_2,param_3);
    puVar1[3] = puVar1[3] + param_3;
    puVar1[2] = puVar1[2] - param_3;
    param_1[3] = param_1[3] + param_3;
    param_1[4] = param_1[4] + param_3;
  }
  else {
LAB_14000e997:
    puVar2 = FUN_14000bdc0(param_3);
    if (puVar2 == (undefined8 *)0x0) goto LAB_14000e9f0;
    *param_1 = (longlong)puVar2;
    if ((longlong *)param_1[2] == param_1) {
      param_1[2] = (longlong)puVar2;
    }
    *puVar2 = puVar1;
    puVar2[3] = param_3;
    puVar2[2] = puVar2[1] - param_3;
    memcpy((void *)((puVar2[1] - param_3) + puVar2[5]),param_2,param_3);
    param_1[3] = param_1[3] + param_3;
    param_1[4] = param_1[4] + puVar1[2];
  }
  FUN_14000c160((longlong)param_1);
  uVar3 = 0;
LAB_14000e9f0:
  if (param_1[6] != 0) {
    FUN_140016e50();
  }
  return uVar3;
}


// ==== FUN_14000ea20 @ 14000ea20  longlong * FUN_14000ea20(longlong * param_1, ulonglong param_2)

longlong * FUN_14000ea20(longlong *param_1,ulonglong param_2)

{
  longlong *plVar1;
  ulonglong uVar2;
  longlong *plVar3;
  ulonglong uVar4;
  longlong *plVar5;
  uint uVar6;
  ulonglong uVar7;
  
  if (param_1[6] != 0) {
    FUN_140016ef0();
  }
  plVar5 = (longlong *)param_1[2];
  plVar1 = (longlong *)*plVar5;
  if ((plVar1 != (longlong *)0x0) &&
     (((*(byte *)(plVar1 + 4) & 8) != 0 || (plVar1[1] - plVar1[3] == plVar1[2])))) {
    plVar5 = plVar1;
  }
  plVar1 = (longlong *)*plVar5;
  if ((plVar1 != (longlong *)0x0) && ((*(uint *)(plVar1 + 4) & 0x38) == 0)) {
    uVar6 = *(uint *)(plVar1 + 4) & 8;
    if (uVar6 == 0) {
      uVar4 = (plVar1[1] - plVar1[3]) - plVar1[2];
    }
    else {
      uVar4 = 0;
    }
    if (param_2 <= uVar4) {
      return plVar1;
    }
    uVar4 = plVar1[3];
    if (uVar4 != 0) {
      uVar2 = plVar1[1];
      if (((param_2 <= uVar2 - uVar4) && (uVar4 < uVar2 >> 1)) && (uVar4 < 0x801)) {
        memmove((void *)plVar1[5],(void *)(plVar1[5] + plVar1[2]),uVar4);
        plVar1[2] = 0;
        return plVar1;
      }
      if (uVar6 == 0) {
        uVar7 = (uVar2 - uVar4) - plVar1[2];
      }
      else {
        uVar7 = 0;
      }
      if (((uVar2 >> 3 <= uVar7) && (uVar4 < 0x1001)) &&
         ((0x7ffffffffffffffe < param_2 || (0x7fffffffffffffff - param_2 < uVar4)))) {
        plVar3 = FUN_14000bdc0(uVar4 + param_2);
        if (plVar3 != (longlong *)0x0) {
          plVar3[3] = plVar1[3];
          memcpy((void *)plVar3[5],(void *)(plVar1[5] + plVar1[2]),plVar1[3]);
          *plVar5 = (longlong)plVar3;
          if ((longlong *)param_1[1] == plVar1) {
            param_1[1] = (longlong)plVar3;
          }
          *plVar3 = *plVar1;
          FUN_14000da70(plVar1);
          return plVar3;
        }
        return (longlong *)0x0;
      }
      plVar1 = (longlong *)*plVar1;
      if (plVar1 != (longlong *)0x0) {
        if ((*(byte *)(plVar1 + 4) & 8) == 0) {
          uVar4 = (plVar1[1] - plVar1[3]) - plVar1[2];
        }
        else {
          uVar4 = 0;
        }
        if (param_2 <= uVar4) {
          return plVar1;
        }
      }
    }
  }
  plVar5 = FUN_14000bdc0(param_2);
  if (plVar5 != (longlong *)0x0) {
    FUN_14000dbb0(param_1,(longlong)plVar5);
  }
  return plVar5;
}


// ==== FUN_14000ebd0 @ 14000ebd0  undefined8 FUN_14000ebd0(longlong * param_1, ulonglong param_2, int param_3)

undefined8 FUN_14000ebd0(longlong *param_1,ulonglong param_2,int param_3)

{
  undefined8 *puVar1;
  longlong lVar2;
  undefined8 *puVar3;
  undefined8 uVar4;
  ulonglong uVar5;
  int iVar6;
  ulonglong uVar7;
  int iVar8;
  ulonglong uVar9;
  
  lVar2 = param_1[1];
  if (param_1[6] != 0) {
    FUN_140016ef0();
  }
  if ((lVar2 == 0) || ((*(byte *)(lVar2 + 0x20) & 8) != 0)) {
    puVar3 = FUN_14000bdc0(param_2);
    if (puVar3 == (undefined8 *)0x0) {
      return 0xffffffff;
    }
    FUN_14000dbb0(param_1,(longlong)puVar3);
    return 0;
  }
  uVar7 = 0;
  iVar6 = 0;
  uVar5 = uVar7;
  uVar9 = uVar7;
  iVar8 = iVar6;
  for (puVar3 = *(undefined8 **)param_1[2]; puVar3 != (undefined8 *)0x0;
      puVar3 = (undefined8 *)*puVar3) {
    if (puVar3[3] == 0) {
      uVar5 = uVar5 + puVar3[1];
      puVar3[2] = 0;
      uVar9 = (ulonglong)((int)uVar9 + 1);
    }
    else if (((*(byte *)(puVar3 + 4) & 8) == 0) &&
            (lVar2 = (puVar3[1] - puVar3[2]) - puVar3[3], lVar2 != 0)) {
      uVar5 = uVar5 + lVar2;
      uVar9 = (ulonglong)((int)uVar9 + 1);
    }
    iVar8 = (int)uVar9;
    if (param_2 <= uVar5) goto LAB_14000ec8f;
    if (iVar8 == param_3) break;
  }
  if (iVar8 < param_3) {
    puVar3 = FUN_14000bdc0(param_2 - uVar5);
    if (puVar3 == (undefined8 *)0x0) {
      uVar4 = 0xffffffff;
    }
    else {
      *(undefined8 **)param_1[1] = puVar3;
      param_1[1] = (longlong)puVar3;
LAB_14000ec8f:
      uVar4 = 0;
    }
  }
  else {
    puVar3 = *(undefined8 **)param_1[2];
    if (puVar3[3] == 0) {
      iVar6 = 1;
    }
    else {
      if ((*(byte *)(puVar3 + 4) & 8) == 0) {
        uVar7 = (puVar3[1] - puVar3[2]) - puVar3[3];
      }
      puVar3 = (undefined8 *)*puVar3;
    }
    while (puVar3 != (undefined8 *)0x0) {
      puVar1 = (undefined8 *)*puVar3;
      FUN_14000da70(puVar3);
      puVar3 = puVar1;
    }
    puVar3 = FUN_14000bdc0(param_2 - uVar7);
    if (puVar3 == (undefined8 *)0x0) {
      if (iVar6 == 0) {
        param_1[1] = *(longlong *)param_1[2];
        **(undefined8 **)param_1[2] = 0;
      }
      else {
        if (param_1[6] != 0) {
          FUN_140016ef0();
        }
        *param_1 = 0;
        param_1[1] = 0;
        param_1[2] = (longlong)param_1;
        param_1[3] = 0;
      }
      uVar4 = 0xffffffff;
    }
    else if (iVar6 == 0) {
      uVar4 = 0;
      **(undefined8 **)param_1[2] = puVar3;
      param_1[1] = (longlong)puVar3;
    }
    else {
      param_1[1] = (longlong)puVar3;
      *param_1 = (longlong)puVar3;
      param_1[2] = (longlong)param_1;
      uVar4 = 0;
    }
  }
  return uVar4;
}


// ==== FUN_14000edb0 @ 14000edb0  int FUN_14000edb0(longlong * param_1, ulonglong param_2)

int FUN_14000edb0(longlong *param_1,ulonglong param_2)

{
  longlong *plVar1;
  
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  plVar1 = FUN_14000ea20(param_1,param_2);
  if (param_1[6] != 0) {
    FUN_140016e50();
  }
  return (plVar1 != (longlong *)0x0) - 1;
}


// ==== FUN_14000ee10 @ 14000ee10  int FUN_14000ee10(longlong * param_1, undefined8 param_2, int param_3)

int FUN_14000ee10(longlong *param_1,undefined8 param_2,int param_3)

{
  longlong *plVar1;
  longlong lVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  undefined8 *puVar8;
  longlong lVar9;
  ulonglong uVar10;
  longlong *plVar11;
  uint uVar12;
  ulonglong *puVar13;
  ulonglong uVar14;
  int iVar15;
  ulonglong uVar16;
  int local_res8;
  undefined4 uStackX_c;
  int local_res20 [2];
  ulonglong local_a8;
  ulonglong local_a0 [7];
  undefined4 local_68 [2];
  undefined8 auStack_60 [7];
  
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  if ((*(byte *)(param_1 + 7) & 4) == 0) {
    local_res8 = 0x1000;
    iVar3 = Ordinal_10(param_2,0x4004667f,&local_res8);
    if (((iVar3 < 0) || (local_res8 < 1)) || (iVar3 = local_res8, 0x1000 < local_res8)) {
      iVar3 = 0x1000;
    }
    if ((param_3 < 0) || (iVar3 < param_3)) {
      param_3 = iVar3;
    }
    uVar10 = (ulonglong)param_3;
    uVar5 = FUN_14000ebd0(param_1,uVar10,4);
    if ((int)uVar5 == -1) {
      iVar3 = -1;
    }
    else {
      if (param_1[6] != 0) {
        FUN_140016ef0();
      }
      uVar16 = 0;
      iVar15 = 0;
      if ((longlong)uVar10 < 0) {
        plVar11 = (longlong *)CONCAT44(uStackX_c,local_res8);
        iVar4 = -1;
      }
      else {
        plVar1 = *(longlong **)param_1[2];
        if (((*(byte *)(plVar1 + 4) & 8) != 0) ||
           (plVar11 = (longlong *)param_1[2], plVar1[1] - plVar1[3] == plVar1[2])) {
          plVar11 = plVar1;
        }
        puVar8 = (undefined8 *)*plVar11;
        uVar7 = uVar16;
        puVar13 = local_a0;
        uVar14 = uVar16;
        iVar4 = iVar15;
        do {
          if (uVar10 <= uVar7) break;
          uVar6 = uVar16;
          if ((*(byte *)(puVar8 + 4) & 8) == 0) {
            uVar6 = (puVar8[1] - puVar8[3]) - puVar8[2];
          }
          if (uVar10 - uVar7 < uVar6) {
            uVar6 = uVar10 - uVar7;
          }
          lVar9 = puVar8[5];
          uVar14 = uVar14 + 1;
          lVar2 = puVar8[3];
          *puVar13 = uVar6;
          plVar1 = puVar8 + 2;
          puVar8 = (undefined8 *)*puVar8;
          uVar7 = uVar7 + uVar6;
          puVar13[-1] = lVar9 + lVar2 + *plVar1;
          iVar4 = iVar4 + 1;
          puVar13 = puVar13 + 2;
        } while ((longlong)uVar14 < 2);
      }
      lVar9 = (longlong)iVar4;
      uVar10 = uVar16;
      if (0 < iVar4) {
        do {
          lVar9 = lVar9 + -1;
          *(undefined8 *)((longlong)auStack_60 + uVar10) =
               *(undefined8 *)((longlong)local_a0 + (uVar10 - 8));
          *(undefined4 *)((longlong)local_68 + uVar10) =
               *(undefined4 *)((longlong)local_a0 + uVar10);
          uVar10 = uVar10 + 0x10;
        } while (lVar9 != 0);
      }
      local_res8 = 0;
      iVar3 = WSARecv(param_2,local_68,iVar4,local_res20,&local_res8,0,0);
      if (iVar3 == 0) {
        iVar3 = -1;
        if ((local_res20[0] != -1) && (iVar3 = iVar15, local_res20[0] != 0)) {
          uVar10 = uVar16;
          iVar3 = local_res20[0];
          if (0 < iVar4) {
            do {
              lVar9 = *plVar11;
              uVar7 = uVar16;
              if (((*(byte *)(lVar9 + 0x20) & 8) == 0) &&
                 (uVar7 = (*(longlong *)(lVar9 + 8) - *(longlong *)(lVar9 + 0x18)) -
                          *(longlong *)(lVar9 + 0x10), 0x7fffffffffffffff < uVar7)) {
                uVar7 = 0x7fffffffffffffff;
              }
              if ((longlong)iVar3 <= (longlong)uVar7) {
                *(longlong *)(lVar9 + 0x18) = *(longlong *)(lVar9 + 0x18) + (longlong)iVar3;
                param_1[2] = (longlong)plVar11;
                break;
              }
              *(longlong *)(lVar9 + 0x18) = *(longlong *)(lVar9 + 0x18) + uVar7;
              plVar11 = (longlong *)*plVar11;
              uVar12 = (int)uVar10 + 1;
              uVar10 = (ulonglong)uVar12;
              iVar3 = iVar3 - (int)uVar7;
            } while ((int)uVar12 < iVar4);
          }
          param_1[3] = param_1[3] + (longlong)local_res20[0];
          param_1[4] = param_1[4] + (longlong)local_res20[0];
          iVar3 = local_res20[0];
          if (param_1[0xf] == 0) {
            param_1[5] = 0;
            param_1[4] = 0;
          }
          else {
            if ((*(byte *)(param_1 + 7) & 8) != 0) {
              uVar10 = FUN_140012c10(param_1[8],param_1 + 10);
              if ((int)uVar10 != 0) {
                if (param_1[6] != 0) {
                  FUN_140016e30();
                }
                *(int *)(param_1 + 9) = (int)param_1[9] + 1;
                if (param_1[0x10] != 0) {
                  FUN_140006150(param_1[0x10]);
                }
              }
              if (param_1[6] != 0) {
                FUN_140016e50();
              }
            }
            FUN_14000c060((longlong)param_1,0);
          }
        }
      }
      else {
        iVar4 = Ordinal_111();
        iVar3 = iVar15;
        if (iVar4 != 0x2745) {
          iVar3 = -1;
        }
      }
    }
  }
  else {
    iVar3 = -1;
  }
  if (param_1[6] != 0) {
    FUN_140016e50();
  }
  return iVar3;
}


// ==== FUN_14000f130 @ 14000f130  ulonglong FUN_14000f130(longlong * param_1, undefined8 param_2, ulonglong param_3)

ulonglong FUN_14000f130(longlong *param_1,undefined8 param_2,ulonglong param_3)

{
  int iVar1;
  ulonglong uVar2;
  
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  uVar2 = 0xffffffff;
  if ((*(byte *)(param_1 + 7) & 2) == 0) {
    if (((longlong)param_3 < 0) || ((ulonglong)param_1[3] < param_3)) {
      param_3 = param_1[3];
    }
    uVar2 = 0xffffffff;
    if (0 < (longlong)param_3) {
      iVar1 = FUN_14000cee0(param_1,param_2,param_3);
      uVar2 = (ulonglong)iVar1;
      if (0 < iVar1) {
        FUN_14000e2a0(param_1,uVar2);
      }
    }
  }
  if (param_1[6] != 0) {
    FUN_140016e50();
  }
  return uVar2 & 0xffffffff;
}


// ==== FUN_14000f1d0 @ 14000f1d0  ulonglong FUN_14000f1d0(longlong * param_1, undefined8 param_2)

ulonglong FUN_14000f1d0(longlong *param_1,undefined8 param_2)

{
  int iVar1;
  ulonglong uVar2;
  
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  uVar2 = 0xffffffff;
  if (((*(byte *)(param_1 + 7) & 2) == 0) && (uVar2 = 0xffffffff, 0 < param_1[3])) {
    iVar1 = FUN_14000cee0(param_1,param_2,param_1[3]);
    uVar2 = (ulonglong)iVar1;
    if (0 < iVar1) {
      FUN_14000e2a0(param_1,uVar2);
    }
  }
  if (param_1[6] != 0) {
    FUN_140016e50();
  }
  return uVar2 & 0xffffffff;
}


// ==== FUN_14000f2a0 @ 14000f2a0  ulonglong * FUN_14000f2a0(ulonglong * param_1, undefined8 * param_2, char * param_3, ulonglong param_4, ulonglong * param_5)

ulonglong *
FUN_14000f2a0(ulonglong *param_1,undefined8 *param_2,char *param_3,ulonglong param_4,
             ulonglong *param_5)

{
  ulonglong uVar1;
  ulonglong uVar2;
  ulonglong *puVar3;
  ulonglong local_28 [4];
  
  puVar3 = FUN_14000d1b0(local_28,param_2,param_3,param_4,param_5,(longlong *)0x0);
  uVar1 = puVar3[1];
  uVar2 = puVar3[2];
  *param_1 = *puVar3;
  param_1[1] = uVar1;
  param_1[2] = uVar2;
  return param_1;
}


// ==== FUN_14000f2f0 @ 14000f2f0  int FUN_14000f2f0(longlong * param_1, char * param_2, va_list param_3)

int FUN_14000f2f0(longlong *param_1,char *param_2,va_list param_3)

{
  int iVar1;
  longlong *plVar2;
  size_t sVar3;
  ulonglong uVar4;
  int iVar5;
  
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  iVar5 = -1;
  if ((*(byte *)(param_1 + 7) & 4) == 0) {
    plVar2 = FUN_14000ea20(param_1,0x40);
    while (iVar5 = -1, plVar2 != (longlong *)0x0) {
      if ((*(byte *)(plVar2 + 4) & 8) == 0) {
        sVar3 = (plVar2[1] - plVar2[2]) - plVar2[3];
      }
      else {
        sVar3 = 0;
      }
      iVar1 = FUN_1400085e0((char *)(plVar2[5] + plVar2[2] + plVar2[3]),sVar3,param_2,param_3);
      uVar4 = (ulonglong)iVar1;
      iVar5 = -1;
      if (iVar1 < 0) break;
      if (uVar4 < sVar3) {
        plVar2[3] = plVar2[3] + uVar4;
        param_1[3] = param_1[3] + uVar4;
        param_1[4] = param_1[4] + uVar4;
        FUN_14000c400((longlong)param_1);
        FUN_14000c160((longlong)param_1);
        iVar5 = iVar1;
        break;
      }
      plVar2 = FUN_14000ea20(param_1,(longlong)(iVar1 + 1));
    }
  }
  if (param_1[6] != 0) {
    FUN_140016e50();
  }
  return iVar5;
}


// ==== FUN_14000f420 @ 14000f420  undefined FUN_14000f420(longlong * param_1, char * param_2, undefined8 param_3, undefined8 param_4)

void FUN_14000f420(longlong *param_1,char *param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 local_res18;
  undefined8 local_res20;
  
  local_res18 = param_3;
  local_res20 = param_4;
  FUN_14000f2f0(param_1,param_2,(va_list)&local_res18);
  return;
}


// ==== FUN_14000f450 @ 14000f450  undefined8 FUN_14000f450(longlong * param_1, undefined8 param_2, longlong param_3, undefined8 param_4, undefined8 param_5)

undefined8
FUN_14000f450(longlong *param_1,undefined8 param_2,longlong param_3,undefined8 param_4,
             undefined8 param_5)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  
  uVar2 = 0xffffffff;
  puVar1 = (undefined8 *)FUN_140011830(0x400);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1[1] = 0x3d0;
    puVar1[5] = puVar1 + 6;
    *(undefined4 *)((longlong)puVar1 + 0x24) = 1;
    *(uint *)(puVar1 + 4) = *(uint *)(puVar1 + 4) | 0xc;
    puVar1[5] = param_2;
    puVar1[1] = param_3;
    puVar1[3] = param_3;
    puVar1[7] = param_5;
    puVar1[6] = param_4;
    if (param_1[6] != 0) {
      FUN_140016e30();
    }
    if ((*(byte *)(param_1 + 7) & 4) == 0) {
      FUN_14000dbb0(param_1,(longlong)puVar1);
      param_1[4] = param_1[4] + param_3;
      FUN_14000c160((longlong)param_1);
      uVar2 = 0;
    }
    else {
      FUN_1400119c0(puVar1);
    }
    if (param_1[6] != 0) {
      FUN_140016e50();
    }
  }
  return uVar2;
}


// ==== FUN_14000f540 @ 14000f540  undefined8 * FUN_14000f540(undefined4 param_1, ulonglong param_2, ulonglong param_3, uint param_4)

undefined8 * FUN_14000f540(undefined4 param_1,ulonglong param_2,ulonglong param_3,uint param_4)

{
  int iVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  undefined1 local_38 [20];
  int local_24;
  
  puVar2 = (undefined8 *)FUN_140011850(0x58,1);
  if (puVar2 == (undefined8 *)0x0) {
    return (undefined8 *)0x0;
  }
  *(undefined4 *)(puVar2 + 1) = 1;
  *(undefined4 *)((longlong)puVar2 + 0x14) = param_1;
  *(uint *)((longlong)puVar2 + 0xc) = param_4;
  puVar2[6] = param_2;
  puVar2[9] = 0;
  puVar2[10] = 0;
  if (param_3 == 0xffffffffffffffff) {
    iVar1 = _fstat64i32(param_1,local_38);
    if (iVar1 < 0) goto LAB_14000f5fe;
    param_3 = (ulonglong)local_24;
  }
  puVar2[8] = param_3;
  if ((((-1 < (longlong)param_2) && (-1 < (longlong)param_3)) && (param_3 < 0x8000000000000000)) &&
     ((param_2 <= 0x7fffffffffffffff - param_3 &&
      (uVar3 = FUN_14000d490((longlong)puVar2), -1 < (int)uVar3)))) {
    if ((param_4 & 8) == 0) {
      uVar3 = FUN_140016df0();
      *puVar2 = uVar3;
      return puVar2;
    }
    return puVar2;
  }
LAB_14000f5fe:
  FUN_1400119c0(puVar2);
  return (undefined8 *)0x0;
}


// ==== FUN_14000f630 @ 14000f630  undefined8 FUN_14000f630(longlong * param_1, longlong * param_2, longlong param_3, longlong param_4)

undefined8 FUN_14000f630(longlong *param_1,longlong *param_2,longlong param_3,longlong param_4)

{
  longlong lVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  LPVOID pvVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  _SYSTEM_INFO local_48;
  
  uVar5 = 0;
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  if (*param_2 != 0) {
    FUN_140016e30();
  }
  if ((*(byte *)((longlong)param_1 + 0x3c) & 1) == 0) {
    uVar6 = uVar5;
    if ((param_2[5] == 0) && (uVar3 = FUN_14000d490((longlong)param_2), uVar6 = 0, (int)uVar3 < 0))
    {
      if (*param_2 != 0) {
        FUN_140016e50();
      }
      if (param_1[6] != 0) {
        FUN_140016e50();
      }
      return 0xffffffff;
    }
  }
  else {
    uVar6 = 1;
  }
  *(int *)(param_2 + 1) = (int)param_2[1] + 1;
  if (*param_2 != 0) {
    FUN_140016e50();
  }
  if ((*(byte *)(param_1 + 7) & 4) == 0) {
    if (param_4 < 0) {
      if (param_2[8] < param_3) goto LAB_14000f7e6;
      param_4 = param_2[8] - param_3;
    }
    if ((param_3 + param_4 <= param_2[8]) &&
       (puVar2 = FUN_14000bdc0(0x10), puVar2 != (undefined8 *)0x0)) {
      *(uint *)(puVar2 + 4) = *(uint *)(puVar2 + 4) | 9;
      if (((int)uVar6 == 0) || ((*(byte *)(param_2 + 2) & 1) == 0)) {
        if ((*(byte *)(param_2 + 2) & 2) == 0) {
          lVar1 = param_2[5];
          puVar2[1] = param_4;
          puVar2[3] = param_4;
          puVar2[5] = param_3 + lVar1;
        }
        else {
          uVar6 = param_3 + param_2[7];
          uVar7 = uVar5;
          if (uVar6 != 0) {
            local_48.u = (_union_552)0x0;
            local_48.dwPageSize = 0;
            local_48.lpMinimumApplicationAddress = (LPVOID)0x0;
            local_48.lpMaximumApplicationAddress = (LPVOID)0x0;
            local_48.dwActiveProcessorMask = 0;
            local_48.dwNumberOfProcessors = 0;
            local_48.dwProcessorType = 0;
            local_48.dwAllocationGranularity = 0;
            local_48.wProcessorLevel = 0;
            local_48.wProcessorRevision = 0;
            GetSystemInfo(&local_48);
            uVar5 = uVar6 % (local_48._40_8_ & 0xffffffff);
            uVar7 = uVar6 - uVar5;
          }
          pvVar4 = MapViewOfFile((HANDLE)param_2[4],4,(DWORD)(uVar7 >> 0x20),(DWORD)uVar7,
                                 uVar5 + param_4);
          if (pvVar4 == (LPVOID)0x0) {
            FUN_1400119c0(puVar2);
            goto LAB_14000f7e6;
          }
          puVar2[5] = pvVar4;
          puVar2[1] = uVar5 + param_4;
          puVar2[2] = uVar5;
          puVar2[3] = param_4;
        }
      }
      else {
        *(uint *)(puVar2 + 4) = *(uint *)(puVar2 + 4) | 2;
        lVar1 = param_2[6];
        puVar2[3] = param_4;
        puVar2[2] = param_3 + lVar1;
        puVar2[1] = param_3 + lVar1 + param_4;
      }
      puVar2[6] = param_2;
      param_1[4] = param_1[4] + param_4;
      FUN_14000dbb0(param_1,(longlong)puVar2);
      FUN_14000c160((longlong)param_1);
      if (param_1[6] != 0) {
        FUN_140016e50();
      }
      return 0;
    }
  }
LAB_14000f7e6:
  if (param_1[6] != 0) {
    FUN_140016e50();
  }
  FUN_14000d630(param_2);
  return 0xffffffff;
}


// ==== FUN_14000f880 @ 14000f880  ulonglong FUN_14000f880(longlong * param_1, undefined4 param_2, ulonglong param_3, ulonglong param_4)

ulonglong FUN_14000f880(longlong *param_1,undefined4 param_2,ulonglong param_3,ulonglong param_4)

{
  longlong *plVar1;
  ulonglong uVar2;
  
  plVar1 = FUN_14000f540(param_2,param_3,param_4,1);
  if (plVar1 == (longlong *)0x0) {
    return 0xffffffff;
  }
  uVar2 = FUN_14000f630(param_1,plVar1,0,param_4);
  if ((int)uVar2 == 0) {
    FUN_14000d630(plVar1);
  }
  return uVar2 & 0xffffffff;
}


// ==== FUN_14000f900 @ 14000f900  undefined FUN_14000f900(longlong param_1, longlong param_2, longlong param_3)

void FUN_14000f900(longlong param_1,longlong param_2,longlong param_3)

{
  longlong *plVar1;
  
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e30();
  }
  plVar1 = *(longlong **)(param_1 + 0x78);
  while (plVar1 != (longlong *)0x0) {
    if (*plVar1 != 0) {
      *(longlong *)(*plVar1 + 8) = plVar1[1];
    }
    *(longlong *)plVar1[1] = *plVar1;
    FUN_1400119c0(plVar1);
    plVar1 = *(longlong **)(param_1 + 0x78);
  }
  if (param_2 != 0) {
    plVar1 = FUN_14000d6e0(param_1,0,param_3);
    *(uint *)(plVar1 + 4) = *(uint *)(plVar1 + 4) | 0x40000;
    plVar1[2] = param_2;
  }
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_14000f9a0 @ 14000f9a0  undefined8 FUN_14000f9a0(longlong param_1, longlong param_2)

undefined8 FUN_14000f9a0(longlong param_1,longlong param_2)

{
  int iVar1;
  
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e30();
  }
  *(uint *)(param_1 + 0x38) = *(uint *)(param_1 + 0x38) | 8;
  *(longlong *)(param_1 + 0x40) = param_2;
  iVar1 = FUN_140010a70(param_2);
  FUN_1400112a0((undefined8 *)(param_1 + 0x50),(char)(iVar1 / 2),FUN_14000dcd0,param_1);
  if (*(longlong *)(param_1 + 0x30) != 0) {
    FUN_140016e50();
  }
  return 0;
}


// ==== FUN_14000fa10 @ 14000fa10  longlong FUN_14000fa10(longlong * param_1, longlong param_2, int param_3)

longlong FUN_14000fa10(longlong *param_1,longlong param_2,int param_3)

{
  int iVar1;
  longlong *plVar2;
  undefined8 uVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  ulonglong *puVar7;
  longlong lVar8;
  longlong lVar9;
  longlong lVar10;
  
  lVar6 = (longlong)param_3;
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  lVar8 = 0;
  lVar5 = lVar8;
  lVar10 = lVar8;
  lVar9 = lVar8;
  if (1 < lVar6) {
    plVar2 = (longlong *)(param_2 + 0x18);
    lVar4 = (lVar6 - 2U >> 1) + 1;
    lVar9 = lVar4 * 2;
    do {
      lVar10 = lVar10 + plVar2[-2];
      lVar5 = lVar5 + *plVar2;
      plVar2 = plVar2 + 4;
      lVar4 = lVar4 + -1;
    } while (lVar4 != 0);
  }
  lVar4 = lVar8;
  if (lVar9 < lVar6) {
    lVar4 = *(longlong *)(param_2 + 8 + lVar9 * 0x10);
  }
  uVar3 = FUN_14000ebd0(param_1,lVar5 + lVar10 + lVar4,2);
  if ((-1 < (int)uVar3) && (0 < param_3)) {
    puVar7 = (ulonglong *)(param_2 + 8);
    lVar9 = lVar8;
    do {
      iVar1 = FUN_14000e6c0(param_1,(void *)puVar7[-1],*puVar7);
      if (iVar1 < 0) break;
      lVar8 = lVar8 + *puVar7;
      lVar9 = lVar9 + 1;
      puVar7 = puVar7 + 2;
    } while (lVar9 < lVar6);
  }
  if (param_1[6] != 0) {
    FUN_140016e50();
  }
  return lVar8;
}


// ==== FUN_14000fb20 @ 14000fb20  int FUN_14000fb20(longlong * param_1, ulonglong param_2, longlong * param_3, int param_4)

int FUN_14000fb20(longlong *param_1,ulonglong param_2,longlong *param_3,int param_4)

{
  int iVar1;
  longlong *plVar2;
  undefined8 uVar3;
  int iVar4;
  longlong local_res8;
  
  iVar4 = -1;
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  iVar1 = -1;
  if (((*(byte *)(param_1 + 7) & 4) == 0) && (iVar1 = iVar4, 0 < param_4)) {
    if (param_4 == 1) {
      plVar2 = FUN_14000ea20(param_1,param_2);
      if (plVar2 != (longlong *)0x0) {
        *param_3 = plVar2[5] + plVar2[3] + plVar2[2];
        if ((*(byte *)(plVar2 + 4) & 8) == 0) {
          param_3[1] = (plVar2[1] - plVar2[3]) - plVar2[2];
          iVar1 = 1;
        }
        else {
          param_3[1] = 0;
          iVar1 = 1;
        }
      }
    }
    else {
      uVar3 = FUN_14000ebd0(param_1,param_2,param_4);
      if (-1 < (int)uVar3) {
        iVar1 = FUN_14000cdc0((longlong)param_1,param_2,param_3,param_4,&local_res8,0);
      }
    }
  }
  if (param_1[6] != 0) {
    FUN_140016e50();
  }
  return iVar1;
}


// ==== FUN_14000fc10 @ 14000fc10  ulonglong FUN_14000fc10(longlong * param_1, longlong * param_2, ulonglong param_3)

ulonglong FUN_14000fc10(longlong *param_1,longlong *param_2,ulonglong param_3)

{
  longlong *plVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  undefined8 *puVar6;
  undefined8 *puVar7;
  longlong lVar8;
  ulonglong uVar9;
  bool bVar10;
  
  uVar9 = param_1[6];
  uVar5 = param_2[6];
  lVar8 = 0;
  uVar3 = uVar9;
  if (uVar9 != 0) {
    if ((uVar5 != 0) && (uVar5 < uVar9)) {
      uVar3 = uVar5;
      uVar5 = uVar9;
    }
    if (uVar3 != 0) {
      FUN_140016e30();
    }
  }
  if ((uVar5 != uVar3) && (uVar5 != 0)) {
    FUN_140016e30();
  }
  puVar7 = (undefined8 *)*param_1;
  if ((param_3 == 0) || (param_2 == param_1)) {
    uVar9 = 0;
  }
  else if (((*(byte *)(param_2 + 7) & 4) == 0) && ((*(byte *)(param_1 + 7) & 2) == 0)) {
    uVar9 = param_1[3];
    if (param_3 < uVar9) {
      if ((ulonglong)puVar7[3] <= param_3) {
        do {
          puVar6 = puVar7;
          lVar8 = lVar8 + puVar6[3];
          param_3 = param_3 - puVar6[3];
          if ((undefined8 *)param_1[2] == puVar6) {
            param_1[2] = (longlong)param_1;
          }
          puVar7 = (undefined8 *)*puVar6;
        } while ((ulonglong)puVar7[3] <= param_3);
        if (lVar8 != 0) {
          plVar1 = FUN_14000db50((longlong)param_2);
          if (*param_2 == 0) {
            *param_2 = *param_1;
          }
          else {
            *plVar1 = *param_1;
          }
          param_2[1] = (longlong)puVar6;
          *puVar6 = 0;
          *param_1 = (longlong)puVar7;
          FUN_14000c400((longlong)param_2);
          param_2[3] = param_2[3] + lVar8;
          param_2[4] = param_2[4] + lVar8;
        }
      }
      FUN_14000e6c0(param_2,(void *)(puVar7[5] + puVar7[2]),param_3);
      puVar7[2] = puVar7[2] + param_3;
      puVar7[3] = puVar7[3] - param_3;
      uVar9 = lVar8 + param_3;
      param_1[3] = param_1[3] - uVar9;
      param_1[5] = param_1[5] + uVar9;
      if (uVar9 != 0) {
        FUN_14000c160((longlong)param_2);
        FUN_14000c160((longlong)param_1);
      }
      uVar9 = uVar9 & 0xffffffff;
    }
    else {
      FUN_14000de70(param_2,param_1);
    }
  }
  else {
    uVar9 = 0xffffffff;
  }
  uVar5 = param_1[6];
  uVar3 = param_2[6];
  uVar2 = uVar3;
  uVar4 = uVar5;
  if (((uVar5 == 0) || (uVar3 == 0)) ||
     (bVar10 = uVar3 == uVar5, uVar2 = uVar5, uVar4 = uVar3, uVar3 < uVar5)) {
    bVar10 = uVar2 == uVar4;
    uVar3 = uVar2;
    uVar5 = uVar4;
  }
  if ((!bVar10) && (uVar3 != 0)) {
    FUN_140016e50();
  }
  if (uVar5 != 0) {
    FUN_140016e50();
  }
  return uVar9 & 0xffffffff;
}


// ==== FUN_14000fdd0 @ 14000fdd0  ulonglong * FUN_14000fdd0(ulonglong * param_1, ulonglong * param_2, ulonglong * param_3, ulonglong * param_4, int param_5)

ulonglong *
FUN_14000fdd0(ulonglong *param_1,ulonglong *param_2,ulonglong *param_3,ulonglong *param_4,
             int param_5)

{
  char cVar1;
  bool bVar2;
  longlong lVar3;
  ulonglong *puVar4;
  char *pcVar5;
  undefined8 *puVar6;
  int iVar7;
  ulonglong uVar8;
  ulonglong uVar9;
  ulonglong uVar10;
  ulonglong local_48;
  undefined8 *local_40;
  ulonglong local_38;
  
  uVar9 = 0;
  uVar8 = 0;
  bVar2 = false;
  if ((param_3 != (ulonglong *)0x0) && (param_3[1] == 0)) {
    *param_1 = 0xffffffffffffffff;
    param_1[1] = 0;
    param_1[2] = 0;
    if (param_4 == (ulonglong *)0x0) {
      return param_1;
    }
    *param_4 = 0;
    return param_1;
  }
  if (param_2[6] != 0) {
    FUN_140016e30();
  }
  if (param_3 == (ulonglong *)0x0) {
    *param_1 = 0;
    uVar10 = *param_2;
    param_1[2] = 0;
    param_1[1] = uVar10;
  }
  else {
    *param_1 = *param_3;
    param_1[1] = param_3[1];
    param_1[2] = param_3[2];
  }
  iVar7 = 0;
  if (param_5 == 0) {
    lVar3 = FUN_14000cbf0((longlong *)param_1);
    if (lVar3 < 0) goto LAB_140010116;
    local_48 = *param_1;
    local_38 = param_1[2];
    local_40 = (undefined8 *)param_1[1];
    uVar8 = local_38;
    uVar10 = uVar9;
    for (puVar6 = local_40; puVar6 != (undefined8 *)0x0; puVar6 = (undefined8 *)*puVar6) {
      for (; iVar7 = (int)uVar10, uVar8 < (ulonglong)puVar6[3]; uVar8 = uVar8 + 1) {
        pcVar5 = "\r\n";
        do {
          cVar1 = *pcVar5;
          if (cVar1 == '\0') goto LAB_14001010e;
          pcVar5 = pcVar5 + 1;
        } while (*(char *)(puVar6[5] + puVar6[2] + uVar8) != cVar1);
        uVar10 = (ulonglong)(iVar7 + 1);
      }
      uVar8 = uVar9;
    }
LAB_14001010e:
    uVar8 = (ulonglong)iVar7;
  }
  else if (param_5 == 1) {
    uVar9 = *param_1;
    lVar3 = FUN_14000ca90((longlong *)param_1,'\n');
    if (lVar3 < 0) goto LAB_140010116;
    uVar8 = 1;
    if (*param_1 != uVar9) {
      local_48 = *param_1;
      puVar6 = (undefined8 *)param_1[1];
      local_38 = param_1[2];
      local_40 = puVar6;
      if ((-1 < (longlong)local_48) && (local_48 != 0)) {
        if ((puVar6 == (undefined8 *)0x0) || (local_38 == 0)) {
          uVar9 = local_48 - 1;
          if (param_2[6] != 0) {
            FUN_140016e30();
          }
          local_38 = uVar9;
          for (local_40 = (undefined8 *)*param_2; local_48 = uVar9, local_40 != (undefined8 *)0x0;
              local_40 = (undefined8 *)*local_40) {
            if (local_38 < (ulonglong)local_40[3]) goto LAB_140010023;
            local_38 = local_38 - local_40[3];
          }
          if (local_38 == 0) {
            local_38 = 0;
            local_40 = (undefined8 *)0x0;
          }
          else {
            local_48 = 0xffffffffffffffff;
            local_38 = 0;
            iVar7 = -1;
            local_40 = (undefined8 *)0x0;
          }
LAB_140010023:
          uVar9 = local_38;
          puVar6 = local_40;
          if (param_2[6] != 0) {
            FUN_140016e50();
          }
          if (iVar7 < 0) goto LAB_140010111;
        }
        else {
          uVar9 = local_38 - 1;
          local_48 = local_48 - 1;
          local_38 = uVar9;
        }
        if ((puVar6 != (undefined8 *)0x0) && (*(char *)(puVar6[5] + puVar6[2] + uVar9) == '\r')) {
          uVar8 = 2;
          *param_1 = local_48;
          param_1[1] = (ulonglong)local_40;
          param_1[2] = local_38;
        }
      }
    }
  }
  else if (param_5 == 2) {
    puVar4 = FUN_14000d1b0(&local_48,param_2,"\r\n",2,param_1,(longlong *)0x0);
    *param_1 = *puVar4;
    param_1[1] = puVar4[1];
    param_1[2] = puVar4[2];
    if ((longlong)*param_1 < 0) goto LAB_140010116;
    uVar8 = 2;
  }
  else if (param_5 == 3) {
    lVar3 = FUN_14000ca90((longlong *)param_1,'\n');
    if (lVar3 < 0) goto LAB_140010116;
    uVar8 = 1;
  }
  else {
    uVar8 = uVar9;
    if ((param_5 != 4) || (lVar3 = FUN_14000ca90((longlong *)param_1,'\0'), lVar3 < 0))
    goto LAB_140010116;
    uVar8 = 1;
  }
LAB_140010111:
  bVar2 = true;
LAB_140010116:
  if (param_2[6] != 0) {
    FUN_140016e50();
  }
  if (!bVar2) {
    *param_1 = 0xffffffffffffffff;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  if (param_4 != (ulonglong *)0x0) {
    *param_4 = uVar8;
  }
  return param_1;
}


// ==== FUN_140010170 @ 140010170  void * FUN_140010170(ulonglong * param_1, ulonglong * param_2, int param_3)

void * FUN_140010170(ulonglong *param_1,ulonglong *param_2,int param_3)

{
  void *pvVar1;
  ulonglong *puVar2;
  void *pvVar3;
  void *pvVar4;
  undefined8 uVar5;
  ulonglong *puVar6;
  void *pvVar7;
  ulonglong local_res8;
  ulonglong local_40 [3];
  
  pvVar4 = (void *)0x0;
  local_res8 = 0;
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  pvVar3 = pvVar4;
  pvVar7 = pvVar4;
  if ((param_1[7] & 2) == 0) {
    puVar6 = &local_res8;
    uVar5 = 0;
    puVar2 = FUN_14000fdd0(local_40,param_1,(ulonglong *)0x0,puVar6,param_3);
    pvVar1 = (void *)*puVar2;
    if (-1 < (longlong)pvVar1) {
      pvVar3 = FUN_140011830((longlong)pvVar1 + 1);
      pvVar7 = pvVar1;
      if (pvVar3 == (void *)0x0) {
        FUN_140019050("%s: out of memory","evbuffer_readln",uVar5,puVar6);
        pvVar3 = pvVar4;
      }
      else {
        FUN_14000e3e0((longlong *)param_1,pvVar3,(ulonglong)pvVar1);
        *(undefined1 *)((longlong)pvVar1 + (longlong)pvVar3) = 0;
        FUN_14000e2a0((longlong *)param_1,local_res8);
      }
    }
  }
  if (param_1[6] != 0) {
    FUN_140016e50();
  }
  if (param_2 != (ulonglong *)0x0) {
    if (pvVar3 != (void *)0x0) {
      pvVar4 = pvVar7;
    }
    *param_2 = (ulonglong)pvVar4;
  }
  return pvVar3;
}


// ==== FUN_140010290 @ 140010290  ulonglong FUN_140010290(undefined8 * param_1, char * param_2, ulonglong param_3)

ulonglong FUN_140010290(undefined8 *param_1,char *param_2,ulonglong param_3)

{
  ulonglong uVar1;
  ulonglong *puVar2;
  ulonglong uVar3;
  ulonglong local_20 [3];
  
  if (param_1[6] != 0) {
    FUN_140016e30();
  }
  uVar3 = 0;
  puVar2 = FUN_14000d1b0(local_20,param_1,param_2,param_3,(ulonglong *)0x0,(longlong *)0x0);
  uVar1 = *puVar2;
  if (-1 < (longlong)uVar1) {
    uVar3 = FUN_14000e470(param_1,uVar1 + param_3);
    if (uVar3 != 0) {
      uVar3 = uVar3 + uVar1;
    }
  }
  if (param_1[6] != 0) {
    FUN_140016e50();
  }
  return uVar3;
}


// ==== FUN_1400103c0 @ 1400103c0  undefined FUN_1400103c0(longlong * param_1, uint param_2, longlong param_3)

void FUN_1400103c0(longlong *param_1,uint param_2,longlong param_3)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  int iVar4;
  ulonglong uVar5;
  int iVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  bool bVar9;
  bool bVar10;
  
  uVar5 = (ulonglong)param_2;
  uVar8 = (ulonglong)(param_2 - 1 >> 1);
  do {
    uVar7 = uVar8;
    *(undefined8 *)(*param_1 + uVar5 * 8) = *(undefined8 *)(*param_1 + uVar7 * 8);
    *(int *)(*(longlong *)(*param_1 + uVar5 * 8) + 0x28) = (int)uVar5;
    iVar6 = (int)uVar7;
    uVar8 = (ulonglong)(iVar6 - 1U >> 1);
    if (iVar6 == 0) break;
    iVar1 = *(int *)(param_3 + 0x6c);
    lVar3 = *(longlong *)(*param_1 + uVar8 * 8);
    iVar2 = *(int *)(lVar3 + 0x6c);
    bVar10 = SBORROW4(iVar2,iVar1);
    iVar4 = iVar2 - iVar1;
    bVar9 = iVar2 == iVar1;
    if (bVar9) {
      iVar1 = *(int *)(param_3 + 0x70);
      iVar2 = *(int *)(lVar3 + 0x70);
      bVar10 = SBORROW4(iVar2,iVar1);
      iVar4 = iVar2 - iVar1;
      bVar9 = iVar2 == iVar1;
    }
    uVar5 = uVar7;
  } while (!bVar9 && bVar10 == iVar4 < 0);
  *(longlong *)(*param_1 + uVar7 * 8) = param_3;
  *(int *)(param_3 + 0x28) = iVar6;
  return;
}


// ==== FUN_140010440 @ 140010440  undefined FUN_140010440(longlong * param_1, uint param_2, longlong param_3)

void FUN_140010440(longlong *param_1,uint param_2,longlong param_3)

{
  longlong lVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar4 = param_2 - 1;
  if (param_2 != 0) {
    do {
      uVar5 = uVar4 >> 1;
      lVar1 = *(longlong *)(*param_1 + (ulonglong)uVar5 * 8);
      if (*(int *)(lVar1 + 0x6c) == *(int *)(param_3 + 0x6c)) {
        bVar2 = *(int *)(param_3 + 0x70) < *(int *)(lVar1 + 0x70);
      }
      else {
        bVar2 = *(int *)(param_3 + 0x6c) < *(int *)(lVar1 + 0x6c);
      }
      if (!bVar2) break;
      *(longlong *)(*param_1 + (ulonglong)param_2 * 8) = lVar1;
      *(uint *)(*(longlong *)(*param_1 + (ulonglong)param_2 * 8) + 0x28) = param_2;
      uVar3 = uVar4 >> 1;
      param_2 = uVar5;
      uVar4 = uVar5 - 1;
    } while (uVar3 != 0);
  }
  *(longlong *)(*param_1 + (ulonglong)param_2 * 8) = param_3;
  *(uint *)(param_3 + 0x28) = param_2;
  return;
}


// ==== FUN_1400104d0 @ 1400104d0  undefined FUN_1400104d0(longlong * param_1, int param_2, longlong param_3)

void FUN_1400104d0(longlong *param_1,int param_2,longlong param_3)

{
  int iVar1;
  longlong lVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  ulonglong uVar7;
  ulonglong uVar8;
  longlong lVar9;
  ulonglong uVar10;
  uint uVar11;
  bool bVar12;
  bool bVar13;
  
  uVar8 = (ulonglong)param_2;
  uVar11 = param_2 * 2 + 2;
  lVar9 = (longlong)(int)uVar11;
  bVar12 = uVar11 == *(uint *)(param_1 + 1);
  uVar7 = uVar8;
  if (uVar11 <= *(uint *)(param_1 + 1)) {
    do {
      if (bVar12) {
LAB_140010535:
        iVar5 = 1;
        lVar6 = 1;
      }
      else {
        lVar6 = *(longlong *)(*param_1 + -8 + lVar9 * 8);
        lVar2 = *(longlong *)(*param_1 + lVar9 * 8);
        iVar5 = *(int *)(lVar2 + 0x6c);
        iVar1 = *(int *)(lVar6 + 0x6c);
        bVar13 = SBORROW4(iVar5,iVar1);
        iVar3 = iVar5 - iVar1;
        bVar12 = iVar5 == iVar1;
        if (bVar12) {
          iVar5 = *(int *)(lVar6 + 0x70);
          iVar1 = *(int *)(lVar2 + 0x70);
          bVar13 = SBORROW4(iVar1,iVar5);
          iVar3 = iVar1 - iVar5;
          bVar12 = iVar1 == iVar5;
        }
        if (!bVar12 && bVar13 == iVar3 < 0) goto LAB_140010535;
        iVar5 = 0;
        lVar6 = 0;
      }
      uVar10 = lVar9 - lVar6;
      lVar9 = *(longlong *)(*param_1 + uVar10 * 8);
      iVar1 = *(int *)(param_3 + 0x6c);
      iVar3 = *(int *)(lVar9 + 0x6c);
      bVar13 = SBORROW4(iVar1,iVar3);
      iVar4 = iVar1 - iVar3;
      bVar12 = iVar1 == iVar3;
      if (bVar12) {
        iVar1 = *(int *)(lVar9 + 0x70);
        iVar3 = *(int *)(param_3 + 0x70);
        bVar13 = SBORROW4(iVar3,iVar1);
        iVar4 = iVar3 - iVar1;
        bVar12 = iVar3 == iVar1;
      }
      if (bVar12 || bVar13 != iVar4 < 0) break;
      *(longlong *)(*param_1 + uVar7 * 8) = lVar9;
      lVar9 = uVar10 * 2 + 2;
      *(int *)(*(longlong *)(*param_1 + uVar7 * 8) + 0x28) = (int)uVar8;
      uVar8 = (ulonglong)(uVar11 - iVar5);
      uVar11 = (uVar11 - iVar5) * 2 + 2;
      bVar12 = uVar11 == *(uint *)(param_1 + 1);
      uVar7 = uVar10;
    } while (uVar11 <= *(uint *)(param_1 + 1));
  }
  *(longlong *)(*param_1 + (uVar8 & 0xffffffff) * 8) = param_3;
  *(int *)(param_3 + 0x28) = (int)uVar8;
  return;
}


// ==== FUN_1400105b0 @ 1400105b0  ulonglong FUN_1400105b0(longlong param_1, int * param_2)

ulonglong FUN_1400105b0(longlong param_1,int *param_2)

{
  int iVar1;
  ulonglong uVar2;
  int local_res8;
  int local_resc;
  
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016ef0();
  }
  if (*(int *)(param_1 + 0x160) != 0) {
    *(undefined8 *)param_2 = *(undefined8 *)(param_1 + 0x160);
    return 0;
  }
  uVar2 = FUN_140016720((undefined8 *)(param_1 + 0x168),param_2);
  if ((int)uVar2 == -1) {
    return uVar2 & 0xffffffff;
  }
  if (*(longlong *)(param_1 + 0x1c0) + 5 < (longlong)*param_2) {
    FUN_1400163c0(&local_res8);
    *(int *)(param_1 + 0x1b8) = local_res8 - *param_2;
    iVar1 = param_2[1];
    *(int *)(param_1 + 0x1bc) = local_resc - iVar1;
    if (local_resc - iVar1 < 0) {
      *(int *)(param_1 + 0x1b8) = *(int *)(param_1 + 0x1b8) + -1;
      *(int *)(param_1 + 0x1bc) = *(int *)(param_1 + 0x1bc) + 1000000;
    }
    *(longlong *)(param_1 + 0x1c0) = (longlong)*param_2;
  }
  return 0;
}


// ==== FUN_140010680 @ 140010680  ulonglong FUN_140010680(longlong param_1, int * param_2)

ulonglong FUN_140010680(longlong param_1,int *param_2)

{
  ulonglong uVar1;
  int iVar2;
  
  if ((param_1 == 0) && (param_1 = DAT_140103f80, DAT_140103f80 == 0)) {
    uVar1 = FUN_1400163c0(param_2);
    return uVar1;
  }
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  if (*(int *)(param_1 + 0x160) == 0) {
    uVar1 = FUN_1400163c0(param_2);
    uVar1 = uVar1 & 0xffffffff;
  }
  else {
    *param_2 = *(int *)(param_1 + 0x160) + *(int *)(param_1 + 0x1b8);
    iVar2 = *(int *)(param_1 + 0x1bc) + *(int *)(param_1 + 0x164);
    param_2[1] = iVar2;
    if (999999 < iVar2) {
      *param_2 = *param_2 + 1;
      param_2[1] = param_2[1] + -1000000;
    }
    uVar1 = 0;
  }
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return uVar1;
}


// ==== FUN_140010740 @ 140010740  undefined FUN_140010740(longlong param_1)

void FUN_140010740(longlong param_1)

{
  *(int *)(param_1 + 0x160) = 0;
  if ((*(byte *)(param_1 + 0x1f8) & 8) == 0) {
    FUN_1400105b0(param_1,(int *)(param_1 + 0x160));
  }
  return;
}


// ==== FUN_140010770 @ 140010770  undefined8 FUN_140010770(longlong param_1)

undefined8 FUN_140010770(longlong param_1)

{
  if ((param_1 == 0) && (param_1 = DAT_140103f80, DAT_140103f80 == 0)) {
    return 0xffffffff;
  }
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  if (*(int *)(param_1 + 0xf0) != 0) {
    *(int *)(param_1 + 0x160) = 0;
    if ((*(byte *)(param_1 + 0x1f8) & 8) == 0) {
      FUN_1400105b0(param_1,(int *)(param_1 + 0x160));
    }
  }
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return 0;
}


// ==== FUN_140010860 @ 140010860  undefined FUN_140010860(undefined8 param_1)

void FUN_140010860(undefined8 param_1)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  undefined1 auStack_78 [32];
  char local_58 [8];
  byte local_50 [56];
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_78;
  FUN_140009250(local_58,0x40,"EVENT_NO%s",param_1);
  if (local_50[0] != 0) {
    pbVar2 = local_50;
    do {
      bVar1 = FUN_140008820(*pbVar2);
      pbVar3 = pbVar2 + 1;
      *pbVar2 = bVar1;
      pbVar2 = pbVar3;
    } while (*pbVar3 != 0);
  }
  getenv(local_58);
  __security_check_cookie(local_18 ^ (ulonglong)auStack_78);
  return;
}


// ==== FUN_140010900 @ 140010900  undefined8 FUN_140010900(longlong param_1, DWORD param_2, undefined8 param_3, undefined8 param_4)

undefined8 FUN_140010900(longlong param_1,DWORD param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 *puVar1;
  
  if (*(longlong *)(param_1 + 0x1f0) == 0) {
    puVar1 = FUN_140074b80(param_2);
    *(undefined8 **)(param_1 + 0x1f0) = puVar1;
    if (puVar1 == (undefined8 *)0x0) {
      FUN_1400191c0("%s: Couldn\'t launch IOCP","event_base_start_iocp_",param_3,param_4);
      return 0xffffffff;
    }
  }
  return 0;
}


// ==== FUN_140010950 @ 140010950  undefined FUN_140010950(longlong param_1)

void FUN_140010950(longlong param_1)

{
  if (*(undefined8 **)(param_1 + 0x1f0) != (undefined8 *)0x0) {
    FUN_140074d90(*(undefined8 **)(param_1 + 0x1f0),0xffffffff);
    *(undefined8 *)(param_1 + 0x1f0) = 0;
  }
  return;
}


// ==== FUN_140010990 @ 140010990  ulonglong FUN_140010990(longlong param_1, int * param_2)

ulonglong FUN_140010990(longlong param_1,int *param_2)

{
  ulonglong uVar1;
  
  if ((param_1 != 0) && (param_2 != (int *)0x0)) {
    if (*(longlong *)(param_1 + 0x1d0) != 0) {
      FUN_140016e30();
    }
    uVar1 = FUN_140016720((undefined8 *)(param_1 + 0x168),param_2);
    if (*(longlong *)(param_1 + 0x1d0) != 0) {
      FUN_140016e50();
    }
    return uVar1 & 0xffffffff;
  }
  return 0xffffffff;
}


// ==== FUN_140010a00 @ 140010a00  undefined8 FUN_140010a00(longlong param_1, uint param_2)

undefined8 FUN_140010a00(longlong param_1,uint param_2)

{
  if (param_1 == 0) {
    return 0xffffffff;
  }
  *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) | param_2;
  return 0;
}


// ==== FUN_140010a20 @ 140010a20  undefined8 FUN_140010a20(longlong param_1, undefined4 param_2)

undefined8 FUN_140010a20(longlong param_1,undefined4 param_2)

{
  if (param_1 == 0) {
    return 0xffffffff;
  }
  *(undefined4 *)(param_1 + 0x10) = param_2;
  return 0;
}


// ==== FUN_140010a70 @ 140010a70  undefined4 FUN_140010a70(longlong param_1)

undefined4 FUN_140010a70(longlong param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    param_1 = DAT_140103f80;
  }
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  uVar1 = *(undefined4 *)(param_1 + 0x100);
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return uVar1;
}


// ==== FUN_140010ad0 @ 140010ad0  int FUN_140010ad0(longlong param_1, uint param_2)

int FUN_140010ad0(longlong param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = 0;
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  if ((param_2 & 1) != 0) {
    iVar1 = *(int *)(param_1 + 0xd8);
  }
  if ((param_2 & 2) != 0) {
    iVar1 = iVar1 + *(int *)(param_1 + 200);
  }
  if ((param_2 & 4) != 0) {
    iVar1 = iVar1 + *(int *)(param_1 + 0xd0);
  }
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return iVar1;
}


// ==== FUN_140010b50 @ 140010b50  int FUN_140010b50(longlong param_1, uint param_2, int param_3)

int FUN_140010b50(longlong param_1,uint param_2,int param_3)

{
  int iVar1;
  
  iVar1 = 0;
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  if (((param_2 & 1) != 0) && (iVar1 = *(int *)(param_1 + 0xdc), param_3 != 0)) {
    *(undefined4 *)(param_1 + 0xdc) = 0;
  }
  if (((param_2 & 2) != 0) && (iVar1 = iVar1 + *(int *)(param_1 + 0xcc), param_3 != 0)) {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  if (((param_2 & 4) != 0) && (iVar1 = iVar1 + *(int *)(param_1 + 0xd4), param_3 != 0)) {
    *(undefined4 *)(param_1 + 0xd4) = 0;
  }
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return iVar1;
}


// ==== FUN_140010c00 @ 140010c00  undefined8 FUN_140010c00(longlong param_1)

undefined8 FUN_140010c00(longlong param_1)

{
  if ((*(int *)(param_1 + 200) < 1) && (*(int *)(param_1 + 0xd0) < 1)) {
    return 0;
  }
  return 1;
}


// ==== FUN_140010c20 @ 140010c20  undefined FUN_140010c20(longlong param_1, longlong param_2)

void FUN_140010c20(longlong param_1,longlong param_2)

{
  int iVar1;
  short local_res8 [4];
  
  local_res8[0] = *(short *)(param_2 + 0x58);
  if (local_res8[0] != 0) {
    *(short **)(param_2 + 0x60) = local_res8;
  }
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  do {
    if (local_res8[0] == 0) {
      return;
    }
    local_res8[0] = local_res8[0] + -1;
    *(short *)(param_2 + 0x58) = local_res8[0];
    if (local_res8[0] == 0) {
      *(undefined8 *)(param_2 + 0x60) = 0;
    }
    (**(code **)(param_2 + 0x18))
              (*(undefined8 *)(param_2 + 0x38),*(undefined2 *)(param_2 + 0x6a),
               *(undefined8 *)(param_2 + 0x20));
    if (*(longlong *)(param_1 + 0x1d0) != 0) {
      FUN_140016e30();
    }
    iVar1 = *(int *)(param_1 + 0xe4);
    if (*(longlong *)(param_1 + 0x1d0) != 0) {
      FUN_140016e50();
    }
  } while (iVar1 == 0);
  if (local_res8[0] != 0) {
    *(undefined8 *)(param_2 + 0x60) = 0;
  }
  return;
}


// ==== FUN_140010d40 @ 140010d40  undefined FUN_140010d40(longlong param_1, undefined8 param_2, longlong param_3)

void FUN_140010d40(longlong param_1,undefined8 param_2,longlong param_3)

{
  ulonglong local_res8 [4];
  
  local_res8[0] = *(ulonglong *)(param_3 + 0x6c) & 0xfffffffffffff;
  FUN_140013f70((longlong *)(param_1 + 0x18),local_res8,1);
  return;
}


// ==== FUN_140010d80 @ 140010d80  undefined8 FUN_140010d80(undefined8 * param_1)

undefined8 FUN_140010d80(undefined8 *param_1)

{
  return *(undefined8 *)*param_1;
}


// ==== FUN_140010da0 @ 140010da0  undefined4 FUN_140010da0(longlong param_1)

undefined4 FUN_140010da0(longlong param_1)

{
  undefined4 uVar1;
  
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  uVar1 = *(undefined4 *)(param_1 + 0xe4);
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return uVar1;
}


// ==== FUN_140010df0 @ 140010df0  undefined4 FUN_140010df0(longlong param_1)

undefined4 FUN_140010df0(longlong param_1)

{
  undefined4 uVar1;
  
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  uVar1 = *(undefined4 *)(param_1 + 0xe0);
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return uVar1;
}


// ==== FUN_140010e40 @ 140010e40  undefined8 FUN_140010e40(undefined * param_1, longlong param_2, undefined8 param_3, ulonglong param_4, undefined8 param_5, undefined * param_6)

undefined8
FUN_140010e40(undefined *param_1,longlong param_2,undefined8 param_3,ulonglong param_4,
             undefined8 param_5,undefined *param_6)

{
  if (param_2 == 0) {
    param_2 = DAT_140103f80;
  }
  *(undefined8 *)(param_1 + 0x38) = param_3;
  *(short *)(param_1 + 0x68) = (short)param_4;
  if (param_6 == &DAT_140103f88) {
    param_6 = param_1;
  }
  *(undefined8 *)(param_1 + 0x18) = param_5;
  *(undefined **)(param_1 + 0x20) = param_6;
  *(undefined2 *)(param_1 + 0x10) = 0x80;
  *(longlong *)(param_1 + 0x40) = param_2;
  *(undefined2 *)(param_1 + 0x6a) = 0;
  *(undefined2 *)(param_1 + 0x58) = 0;
  *(undefined8 *)(param_1 + 0x60) = 0;
  if ((param_4 & 8) == 0) {
    if ((param_4 & 0x10) == 0) {
      param_1[0x13] = 0;
    }
    else {
      *(undefined4 *)(param_1 + 0x5c) = 0;
      *(undefined4 *)(param_1 + 0x58) = 0;
      param_1[0x13] = 2;
    }
  }
  else {
    if ((param_4 & 0x86) != 0) {
      FUN_1400191c0("%s: EV_SIGNAL is not compatible with EV_READ, EV_WRITE or EV_CLOSED",
                    "event_assign",param_3,param_4);
      return 0xffffffff;
    }
    param_1[0x13] = 1;
  }
  *(undefined4 *)(param_1 + 0x28) = 0xffffffff;
  if (param_2 != 0) {
    param_1[0x12] = (char)(*(int *)(param_2 + 0x100) / 2);
  }
  return 0;
}


// ==== FUN_140010f00 @ 140010f00  undefined8 FUN_140010f00(longlong param_1, longlong param_2)

undefined8 FUN_140010f00(longlong param_1,longlong param_2)

{
  if (*(short *)(param_2 + 0x10) != 0x80) {
    return 0xffffffff;
  }
  *(longlong *)(param_2 + 0x40) = param_1;
  *(char *)(param_2 + 0x12) = (char)(*(int *)(param_1 + 0x100) / 2);
  return 0;
}


// ==== FUN_140010f30 @ 140010f30  undefined FUN_140010f30(undefined * param_1, undefined8 param_2, ushort param_3, undefined8 param_4, undefined * param_5)

void FUN_140010f30(undefined *param_1,undefined8 param_2,ushort param_3,undefined8 param_4,
                  undefined *param_5)

{
  FUN_140010e40(param_1,DAT_140103f80,param_2,(ulonglong)param_3,param_4,param_5);
  return;
}


// ==== FUN_140010f70 @ 140010f70  longlong FUN_140010f70(longlong param_1)

longlong FUN_140010f70(longlong param_1)

{
  undefined8 uVar1;
  longlong lVar2;
  
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  uVar1 = FUN_140016dd0();
  lVar2 = 0;
  if ((*(int *)(param_1 + 0x1c8) == (int)uVar1) &&
     ((*(byte *)(*(longlong *)(param_1 + 0x1e8) + 0x10) & 0x80) != 0)) {
    lVar2 = *(longlong *)(param_1 + 0x1e8);
  }
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return lVar2;
}


// ==== FUN_140010fd0 @ 140010fd0  undefined FUN_140010fd0(longlong param_1)

void FUN_140010fd0(longlong param_1)

{
  *(ushort *)(param_1 + 0x10) = *(ushort *)(param_1 + 0x10) & 0xff7f;
  return;
}


// ==== FUN_140010fe0 @ 140010fe0  undefined8 FUN_140010fe0(longlong param_1, int param_2)

undefined8 FUN_140010fe0(longlong param_1,int param_2)

{
  if ((((*(byte *)(param_1 + 0x10) & 8) == 0) && (-1 < param_2)) &&
     (param_2 < *(int *)(*(longlong *)(param_1 + 0x40) + 0x100))) {
    *(char *)(param_1 + 0x12) = (char)param_2;
    return 0;
  }
  return 0xffffffff;
}


// ==== FUN_140011000 @ 140011000  ushort FUN_140011000(longlong param_1, ushort param_2, int * param_3)

ushort FUN_140011000(longlong param_1,ushort param_2,int *param_3)

{
  ushort uVar1;
  undefined8 uVar2;
  int iVar3;
  ushort uVar4;
  int local_res8;
  
  uVar4 = 0;
  if (*(longlong *)(*(longlong *)(param_1 + 0x40) + 0x1d0) != 0) {
    FUN_140016e30();
  }
  uVar1 = *(ushort *)(param_1 + 0x10);
  if ((uVar1 & 2) != 0) {
    uVar4 = *(ushort *)(param_1 + 0x68) & 0x8e;
  }
  if ((uVar1 & 0x28) != 0) {
    uVar4 = uVar4 | *(ushort *)(param_1 + 0x6a);
  }
  if ((uVar1 & 1) != 0) {
    uVar4 = uVar4 | 1;
  }
  if ((param_3 != (int *)0x0) && ((param_2 & 0x8f & uVar4 & 1) != 0)) {
    uVar2 = *(undefined8 *)(param_1 + 0x6c);
    local_res8 = (int)uVar2;
    *param_3 = *(int *)(*(longlong *)(param_1 + 0x40) + 0x1b8) + local_res8;
    iVar3 = *(int *)(*(longlong *)(param_1 + 0x40) + 0x1bc) +
            ((uint)((ulonglong)uVar2 >> 0x20) & 0xfffff);
    param_3[1] = iVar3;
    if (999999 < iVar3) {
      *param_3 = *param_3 + 1;
      param_3[1] = param_3[1] + -1000000;
    }
  }
  if (*(longlong *)(*(longlong *)(param_1 + 0x40) + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return param_2 & 0x8f & uVar4;
}


// ==== FUN_1400110f0 @ 1400110f0  bool FUN_1400110f0(longlong param_1)

bool FUN_1400110f0(longlong param_1)

{
  return (*(byte *)(param_1 + 0x10) & 0x80) != 0;
}


// ==== FUN_140011160 @ 140011160  undefined8 FUN_140011160(longlong param_1)

undefined8 FUN_140011160(longlong param_1)

{
  return *(undefined8 *)(param_1 + 0x38);
}


// ==== FUN_140011170 @ 140011170  undefined8 FUN_140011170(longlong param_1)

undefined8 FUN_140011170(longlong param_1)

{
  return *(undefined8 *)(param_1 + 0x40);
}


// ==== FUN_1400111b0 @ 1400111b0  undefined1 FUN_1400111b0(longlong param_1)

undefined1 FUN_1400111b0(longlong param_1)

{
  return *(undefined1 *)(param_1 + 0x12);
}


// ==== FUN_1400111c0 @ 1400111c0  undefined8 FUN_1400111c0(longlong param_1)

undefined8 FUN_1400111c0(longlong param_1)

{
  int iVar1;
  int *piVar2;
  undefined1 local_res8 [32];
  
  local_res8[0] = 0;
  iVar1 = Ordinal_19(*(undefined8 *)(param_1 + 0x218),local_res8,1);
  if (iVar1 < 0) {
    piVar2 = _errno();
    if (*piVar2 != 0x2733) {
      piVar2 = _errno();
      if (*piVar2 != 0xb) {
        return 0xffffffff;
      }
    }
  }
  return 0;
}


// ==== FUN_140011210 @ 140011210  undefined8 FUN_140011210(longlong param_1)

undefined8 FUN_140011210(longlong param_1)

{
  undefined8 uVar1;
  
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016ef0();
  }
  if (*(code **)(param_1 + 0x298) == (code *)0x0) {
    return 0xffffffff;
  }
  if (*(int *)(param_1 + 0x20c) != 0) {
    return 0;
  }
  *(undefined4 *)(param_1 + 0x20c) = 1;
                    /* WARNING: Could not recover jumptable at 0x000140011260. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (**(code **)(param_1 + 0x298))(param_1);
  return uVar1;
}


// ==== FUN_1400112a0 @ 1400112a0  undefined FUN_1400112a0(undefined8 * param_1, undefined1 param_2, undefined8 param_3, undefined8 param_4)

void FUN_1400112a0(undefined8 *param_1,undefined1 param_2,undefined8 param_3,undefined8 param_4)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = param_3;
  param_1[4] = param_4;
  *(undefined1 *)((longlong)param_1 + 0x12) = param_2;
  *(undefined1 *)((longlong)param_1 + 0x13) = 3;
  return;
}


// ==== FUN_1400112c0 @ 1400112c0  undefined FUN_1400112c0(longlong param_1, undefined1 param_2)

void FUN_1400112c0(longlong param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x12) = param_2;
  return;
}


// ==== FUN_1400112d0 @ 1400112d0  ulonglong FUN_1400112d0(longlong param_1, undefined8 * param_2)

ulonglong FUN_1400112d0(longlong param_1,undefined8 *param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  longlong lVar4;
  int iVar5;
  ulonglong uVar6;
  bool bVar7;
  bool bVar8;
  int local_res8;
  int iStackX_c;
  
  piVar3 = (int *)*param_2;
  if ((*(int *)(param_1 + 0x158) == 0) || (lVar4 = **(longlong **)(param_1 + 0x150), lVar4 == 0)) {
    *param_2 = 0;
  }
  else {
    uVar6 = FUN_1400105b0(param_1,&local_res8);
    if ((int)uVar6 == -1) {
      return uVar6 & 0xffffffff;
    }
    iVar1 = *(int *)(lVar4 + 0x6c);
    bVar8 = SBORROW4(iVar1,local_res8);
    iVar5 = iVar1 - local_res8;
    bVar7 = iVar1 == local_res8;
    if (bVar7) {
      iVar2 = *(int *)(lVar4 + 0x70);
      bVar8 = SBORROW4(iVar2,iStackX_c);
      iVar5 = iVar2 - iStackX_c;
      bVar7 = iVar2 == iStackX_c;
    }
    if (bVar7 || bVar8 != iVar5 < 0) {
      piVar3[1] = 0;
      *piVar3 = 0;
      return 0;
    }
    *piVar3 = iVar1 - local_res8;
    iStackX_c = *(int *)(lVar4 + 0x70) - iStackX_c;
    piVar3[1] = iStackX_c;
    if (iStackX_c < 0) {
      *piVar3 = *piVar3 + -1;
      piVar3[1] = piVar3[1] + 1000000;
      return 0;
    }
  }
  return 0;
}


// ==== FUN_140011390 @ 140011390  undefined FUN_140011390(longlong param_1, longlong param_2)

void FUN_140011390(longlong param_1,longlong param_2)

{
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016ef0();
  }
  *(int *)(param_1 + 0xd0) =
       *(int *)(param_1 + 0xd0) - (~((int)*(short *)(param_2 + 0x10) >> 4) & 1U);
  *(ushort *)(param_2 + 0x10) = *(ushort *)(param_2 + 0x10) & 0xfffd;
  return;
}


// ==== FUN_1400113e0 @ 1400113e0  undefined FUN_1400113e0(longlong param_1, longlong * param_2)

void FUN_1400113e0(longlong param_1,longlong *param_2)

{
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016ef0();
  }
  *(int *)(param_1 + 0xd0) = *(int *)(param_1 + 0xd0) - (~((int)(short)param_2[2] >> 4) & 1U);
  *(ushort *)(param_2 + 2) = *(ushort *)(param_2 + 2) & 0xfff7;
  *(int *)(param_1 + 0xd8) = *(int *)(param_1 + 0xd8) + -1;
  if (*param_2 == 0) {
    *(longlong *)
     (*(longlong *)(param_1 + 0xf8) + 8 + (ulonglong)*(byte *)((longlong)param_2 + 0x12) * 0x10) =
         param_2[1];
  }
  else {
    *(longlong *)(*param_2 + 8) = param_2[1];
  }
  *(longlong *)param_2[1] = *param_2;
  return;
}


// ==== FUN_140011460 @ 140011460  undefined FUN_140011460(longlong param_1, longlong * param_2)

void FUN_140011460(longlong param_1,longlong *param_2)

{
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016ef0();
  }
  *(int *)(param_1 + 0xd0) = *(int *)(param_1 + 0xd0) - (~((int)(short)param_2[2] >> 4) & 1U);
  *(ushort *)(param_2 + 2) = *(ushort *)(param_2 + 2) & 0xffdf;
  *(int *)(param_1 + 0xd8) = *(int *)(param_1 + 0xd8) + -1;
  if (*param_2 == 0) {
    *(longlong *)(param_1 + 0x110) = param_2[1];
  }
  else {
    *(longlong *)(*param_2 + 8) = param_2[1];
  }
  *(longlong *)param_2[1] = *param_2;
  return;
}


// ==== FUN_1400114d0 @ 1400114d0  undefined FUN_1400114d0(longlong * param_1, longlong param_2)

void FUN_1400114d0(longlong *param_1,longlong param_2)

{
  longlong *plVar1;
  longlong *plVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  int iVar6;
  longlong lVar7;
  bool bVar8;
  
  lVar7 = **(longlong **)(param_1[1] + 8);
  if (lVar7 != 0) {
    iVar3 = *(int *)(param_2 + 0x6c);
    do {
      iVar4 = *(int *)(lVar7 + 0x6c);
      bVar8 = SBORROW4(iVar3,iVar4);
      iVar6 = iVar3 - iVar4;
      if (iVar3 == iVar4) {
        bVar8 = SBORROW4(*(int *)(param_2 + 0x70),*(int *)(lVar7 + 0x70));
        iVar6 = *(int *)(param_2 + 0x70) - *(int *)(lVar7 + 0x70);
      }
      if (bVar8 == iVar6 < 0) {
        lVar5 = *(longlong *)(lVar7 + 0x28);
        plVar1 = (longlong *)(lVar7 + 0x28);
        plVar2 = (longlong *)(param_2 + 0x28);
        *plVar2 = lVar5;
        if (lVar5 != 0) {
          *(longlong **)(lVar5 + 0x30) = plVar2;
          *plVar1 = param_2;
          *(longlong **)(param_2 + 0x30) = plVar1;
          return;
        }
        param_1[1] = (longlong)plVar2;
        *plVar1 = param_2;
        *(longlong **)(param_2 + 0x30) = plVar1;
        return;
      }
      lVar7 = **(longlong **)(*(longlong *)(lVar7 + 0x30) + 8);
    } while (lVar7 != 0);
  }
  lVar7 = *param_1;
  plVar1 = (longlong *)(param_2 + 0x28);
  *plVar1 = lVar7;
  if (lVar7 != 0) {
    *(longlong **)(*param_1 + 0x30) = plVar1;
    *param_1 = param_2;
    *(longlong **)(param_2 + 0x30) = param_1;
    return;
  }
  param_1[1] = (longlong)plVar1;
  *param_1 = param_2;
  *(longlong **)(param_2 + 0x30) = param_1;
  return;
}


// ==== FUN_140011570 @ 140011570  undefined FUN_140011570(longlong param_1, longlong param_2)

void FUN_140011570(longlong param_1,longlong param_2)

{
  int iVar1;
  
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016ef0();
  }
  *(int *)(param_1 + 0xd0) =
       *(int *)(param_1 + 0xd0) + (~((int)*(short *)(param_2 + 0x10) >> 4) & 1U);
  iVar1 = *(int *)(param_1 + 0xd0);
  if (*(int *)(param_1 + 0xd0) < *(int *)(param_1 + 0xd4)) {
    iVar1 = *(int *)(param_1 + 0xd4);
  }
  *(int *)(param_1 + 0xd4) = iVar1;
  *(ushort *)(param_2 + 0x10) = *(ushort *)(param_2 + 0x10) | 2;
  return;
}


// ==== FUN_1400115d0 @ 1400115d0  undefined FUN_1400115d0(longlong param_1, undefined8 * param_2)

void FUN_1400115d0(longlong param_1,undefined8 *param_2)

{
  uint uVar1;
  ulonglong in_RAX;
  int iVar2;
  
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    uVar1 = FUN_140016ef0();
    in_RAX = (ulonglong)uVar1;
  }
  if ((*(ushort *)(param_2 + 2) & 8) == 0) {
    *(int *)(param_1 + 0xd0) =
         *(int *)(param_1 + 0xd0) +
         (~((int)CONCAT62((int6)(in_RAX >> 0x10),*(ushort *)(param_2 + 2)) >> 4) & 1U);
    iVar2 = *(int *)(param_1 + 0xd0);
    if (*(int *)(param_1 + 0xd0) < *(int *)(param_1 + 0xd4)) {
      iVar2 = *(int *)(param_1 + 0xd4);
    }
    *(int *)(param_1 + 0xd4) = iVar2;
    *(ushort *)(param_2 + 2) = *(ushort *)(param_2 + 2) | 8;
    *(int *)(param_1 + 0xd8) = *(int *)(param_1 + 0xd8) + 1;
    iVar2 = *(int *)(param_1 + 0xd8);
    if (*(int *)(param_1 + 0xd8) < *(int *)(param_1 + 0xdc)) {
      iVar2 = *(int *)(param_1 + 0xdc);
    }
    *(int *)(param_1 + 0xdc) = iVar2;
    *param_2 = 0;
    param_2[1] = *(undefined8 *)
                  (*(longlong *)(param_1 + 0xf8) + 8 +
                  (ulonglong)*(byte *)((longlong)param_2 + 0x12) * 0x10);
    **(undefined8 **)
      (*(longlong *)(param_1 + 0xf8) + 8 + (ulonglong)*(byte *)((longlong)param_2 + 0x12) * 0x10) =
         param_2;
    *(undefined8 **)
     (*(longlong *)(param_1 + 0xf8) + 8 + (ulonglong)*(byte *)((longlong)param_2 + 0x12) * 0x10) =
         param_2;
  }
  return;
}


// ==== FUN_140011690 @ 140011690  undefined FUN_140011690(longlong param_1, undefined8 * param_2)

void FUN_140011690(longlong param_1,undefined8 *param_2)

{
  uint uVar1;
  ulonglong in_RAX;
  int iVar2;
  
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    uVar1 = FUN_140016ef0();
    in_RAX = (ulonglong)uVar1;
  }
  if ((*(ushort *)(param_2 + 2) & 0x28) == 0) {
    *(int *)(param_1 + 0xd0) =
         *(int *)(param_1 + 0xd0) +
         (~((int)CONCAT62((int6)(in_RAX >> 0x10),*(ushort *)(param_2 + 2)) >> 4) & 1U);
    iVar2 = *(int *)(param_1 + 0xd0);
    if (*(int *)(param_1 + 0xd0) < *(int *)(param_1 + 0xd4)) {
      iVar2 = *(int *)(param_1 + 0xd4);
    }
    *(int *)(param_1 + 0xd4) = iVar2;
    *(ushort *)(param_2 + 2) = *(ushort *)(param_2 + 2) | 0x20;
    *(int *)(param_1 + 0xd8) = *(int *)(param_1 + 0xd8) + 1;
    iVar2 = *(int *)(param_1 + 0xd8);
    if (*(int *)(param_1 + 0xd8) < *(int *)(param_1 + 0xdc)) {
      iVar2 = *(int *)(param_1 + 0xdc);
    }
    *(int *)(param_1 + 0xdc) = iVar2;
    *param_2 = 0;
    param_2[1] = *(undefined8 *)(param_1 + 0x110);
    **(undefined8 **)(param_1 + 0x110) = param_2;
    *(undefined8 **)(param_1 + 0x110) = param_2;
  }
  return;
}


// ==== FUN_140011730 @ 140011730  undefined FUN_140011730(longlong param_1)

void FUN_140011730(longlong param_1)

{
  longlong *plVar1;
  
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016ef0();
  }
  plVar1 = *(longlong **)(param_1 + 0x108);
  while (plVar1 != (longlong *)0x0) {
    if (*plVar1 == 0) {
      *(longlong *)(param_1 + 0x110) = plVar1[1];
    }
    else {
      *(longlong *)(*plVar1 + 8) = plVar1[1];
    }
    *(longlong *)plVar1[1] = *plVar1;
    *(ushort *)(plVar1 + 2) = *(ushort *)(plVar1 + 2) & 0xffdf;
    *(ushort *)(plVar1 + 2) = *(ushort *)(plVar1 + 2) | 8;
    *plVar1 = 0;
    plVar1[1] = *(longlong *)
                 (*(longlong *)(param_1 + 0xf8) + 8 +
                 (ulonglong)*(byte *)((longlong)plVar1 + 0x12) * 0x10);
    **(undefined8 **)
      (*(longlong *)(param_1 + 0xf8) + 8 + (ulonglong)*(byte *)((longlong)plVar1 + 0x12) * 0x10) =
         plVar1;
    *(longlong **)
     (*(longlong *)(param_1 + 0xf8) + 8 + (ulonglong)*(byte *)((longlong)plVar1 + 0x12) * 0x10) =
         plVar1;
    *(int *)(param_1 + 0xf4) =
         *(int *)(param_1 + 0xf4) + (uint)(*(char *)((longlong)plVar1 + 0x13) == '\x03');
    plVar1 = *(longlong **)(param_1 + 0x108);
  }
  return;
}


// ==== FUN_140011830 @ 140011830  void * FUN_140011830(size_t param_1)

void * FUN_140011830(size_t param_1)

{
  void *pvVar1;
  
  if (param_1 == 0) {
    return (void *)0x0;
  }
  if (DAT_140103f98 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000140011844. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    pvVar1 = (void *)(*DAT_140103f98)();
    return pvVar1;
  }
                    /* WARNING: Could not recover jumptable at 0x000140011847. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = malloc(param_1);
  return pvVar1;
}


// ==== FUN_140011850 @ 140011850  void * FUN_140011850(ulonglong param_1, ulonglong param_2)

void * FUN_140011850(ulonglong param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  void *pvVar2;
  int *piVar3;
  
  if ((param_1 == 0) || (param_2 == 0)) {
    return (void *)0x0;
  }
  if (DAT_140103f98 == (code *)0x0) {
    pvVar2 = calloc(param_1,param_2);
    if (pvVar2 != (void *)0x0) {
      return pvVar2;
    }
  }
  else {
    auVar1._8_8_ = 0;
    auVar1._0_8_ = param_2;
    if ((param_1 <= SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0)) &&
       (pvVar2 = (void *)(*DAT_140103f98)(param_1 * param_2), pvVar2 != (void *)0x0)) {
      memset(pvVar2,0,param_1 * param_2);
      return pvVar2;
    }
  }
  piVar3 = _errno();
  *piVar3 = 0xc;
  return (void *)0x0;
}


// ==== FUN_1400118f0 @ 1400118f0  void * FUN_1400118f0(char * param_1)

void * FUN_1400118f0(char *param_1)

{
  char cVar1;
  int *piVar2;
  void *pvVar3;
  ulonglong uVar4;
  char *pcVar5;
  
  if (param_1 == (char *)0x0) {
    piVar2 = _errno();
    *piVar2 = 0x16;
    return (void *)0x0;
  }
  if (DAT_140103f98 == (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000140011994. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    pvVar3 = (void *)_strdup();
    return pvVar3;
  }
  uVar4 = 0xffffffffffffffff;
  pcVar5 = param_1;
  do {
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  if (uVar4 != 0) {
    pvVar3 = (void *)(*DAT_140103f98)(uVar4);
    if (pvVar3 != (void *)0x0) {
      memcpy(pvVar3,param_1,uVar4);
      return pvVar3;
    }
  }
  piVar2 = _errno();
  *piVar2 = 0xc;
  return (void *)0x0;
}


// ==== FUN_1400119a0 @ 1400119a0  undefined FUN_1400119a0(void * param_1, size_t param_2)

void FUN_1400119a0(void *param_1,size_t param_2)

{
  if (DAT_140103fa0 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0001400119ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*DAT_140103fa0)();
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0001400119af. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  realloc(param_1,param_2);
  return;
}


// ==== FUN_1400119c0 @ 1400119c0  undefined FUN_1400119c0(void * param_1)

void FUN_1400119c0(void *param_1)

{
  if (DAT_140103fa8 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x0001400119cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*DAT_140103fa8)();
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0001400119cf. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  free(param_1);
  return;
}


// ==== FUN_140011a00 @ 140011a00  undefined FUN_140011a00(undefined8 param_1, undefined8 param_2, longlong param_3)

void FUN_140011a00(undefined8 param_1,undefined8 param_2,longlong param_3)

{
  int iVar1;
  undefined1 auStack_438 [32];
  undefined1 local_418 [1024];
  ulonglong local_18;
  
  local_18 = DAT_140103510 ^ (ulonglong)auStack_438;
  do {
    iVar1 = Ordinal_16(param_1,local_418,0x400,0);
  } while (0 < iVar1);
  if (*(longlong *)(param_3 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  *(undefined4 *)(param_3 + 0x20c) = 0;
  if (*(longlong *)(param_3 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  __security_check_cookie(local_18 ^ (ulonglong)auStack_438);
  return;
}


// ==== FUN_140011aa0 @ 140011aa0  ulonglong FUN_140011aa0(longlong param_1, undefined * param_2, undefined8 param_3)

ulonglong FUN_140011aa0(longlong param_1,undefined *param_2,undefined8 param_3)

{
  longlong lVar1;
  undefined8 *puVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  uint uVar6;
  ulonglong uVar7;
  
  uVar3 = FUN_14001b330(param_1,param_2,param_3);
  if ((int)uVar3 == 0) {
    uVar7 = 0;
    uVar3 = uVar7;
    uVar5 = uVar7;
    if (*(int *)(param_1 + 0x158) != 0) {
      do {
        lVar1 = *(longlong *)(uVar5 + *(longlong *)(param_1 + 0x150));
        if (((*(byte *)(lVar1 + 0x10) & 2) == 0) &&
           (uVar4 = (*(code *)param_2)(param_1,lVar1,param_3), (int)uVar4 != 0)) {
          return uVar4;
        }
        uVar6 = (int)uVar3 + 1;
        uVar3 = (ulonglong)uVar6;
        uVar5 = uVar5 + 8;
      } while (uVar6 < *(uint *)(param_1 + 0x158));
    }
    uVar3 = uVar7;
    uVar5 = uVar7;
    if (0 < *(int *)(param_1 + 0x120)) {
      do {
        for (lVar1 = **(longlong **)(*(longlong *)(param_1 + 0x118) + uVar3); lVar1 != 0;
            lVar1 = *(longlong *)(lVar1 + 0x28)) {
          if (((*(byte *)(lVar1 + 0x10) & 2) == 0) &&
             (uVar4 = (*(code *)param_2)(param_1,lVar1,param_3), (int)uVar4 != 0)) {
            return uVar4;
          }
        }
        uVar6 = (int)uVar5 + 1;
        uVar3 = uVar3 + 8;
        uVar5 = (ulonglong)uVar6;
      } while ((int)uVar6 < *(int *)(param_1 + 0x120));
    }
    uVar3 = uVar7;
    if (0 < *(int *)(param_1 + 0x100)) {
      do {
        for (puVar2 = *(undefined8 **)(uVar7 + *(longlong *)(param_1 + 0xf8));
            puVar2 != (undefined8 *)0x0; puVar2 = (undefined8 *)*puVar2) {
          if (((*(byte *)(puVar2 + 2) & 0x83) == 0x80) &&
             (uVar5 = (*(code *)param_2)(param_1,puVar2,param_3), (int)uVar5 != 0)) {
            return uVar5;
          }
        }
        uVar6 = (int)uVar3 + 1;
        uVar7 = uVar7 + 0x10;
        uVar3 = (ulonglong)uVar6;
      } while ((int)uVar6 < *(int *)(param_1 + 0x100));
    }
    uVar3 = 0;
  }
  return uVar3;
}


// ==== FUN_140011bf0 @ 140011bf0  undefined8 FUN_140011bf0(longlong param_1, longlong param_2, FILE * param_3)

/* WARNING: Restarted to delay deadcode elimination for space: register */

undefined8 FUN_140011bf0(longlong param_1,longlong param_2,FILE *param_3)

{
  uint uVar1;
  uint uVar2;
  undefined *puVar3;
  
  if ((*(ushort *)(param_2 + 0x10) & 3) != 0) {
    puVar3 = &DAT_1400c0e40;
    if ((*(ushort *)(param_2 + 0x68) & 8) != 0) {
      puVar3 = &DAT_1400c0e3c;
    }
    fprintf(param_3,"  %p [%s %I64d]%s%s%s%s%s%s",param_2,puVar3);
    if ((*(byte *)(param_2 + 0x10) & 1) != 0) {
      uVar1 = *(int *)(param_2 + 0x6c) + *(int *)(param_1 + 0x1b8);
      uVar2 = (*(uint *)(param_2 + 0x70) & 0xfffff) + *(int *)(param_1 + 0x1bc);
      if (999999 < (int)uVar2) {
        uVar1 = uVar1 + 1;
        uVar2 = uVar2 - 1000000;
      }
      fprintf(param_3," Timeout=%ld.%06d",(ulonglong)uVar1,(ulonglong)uVar2 & 0xffffffff000fffff);
    }
    fputc(10,param_3);
  }
  return 0;
}


// ==== FUN_140011d60 @ 140011d60  undefined8 FUN_140011d60(undefined8 param_1, longlong param_2, FILE * param_3)

/* WARNING: Restarted to delay deadcode elimination for space: register */

undefined8 FUN_140011d60(undefined8 param_1,longlong param_2,FILE *param_3)

{
  undefined *puVar1;
  
  if ((*(ushort *)(param_2 + 0x10) & 0x28) != 0) {
    puVar1 = &DAT_1400c0e40;
    if ((*(byte *)(param_2 + 0x68) & 8) != 0) {
      puVar1 = &DAT_1400c0e3c;
    }
    fprintf(param_3,"  %p [%s %I64d, priority=%d]%s%s%s%s%s active%s%s\n",param_2,puVar1);
  }
  return 0;
}


// ==== FUN_140011e90 @ 140011e90  ulonglong FUN_140011e90(longlong param_1, undefined * param_2, undefined8 param_3)

ulonglong FUN_140011e90(longlong param_1,undefined *param_2,undefined8 param_3)

{
  ulonglong uVar1;
  
  if ((param_2 != (undefined *)0x0) && (param_1 != 0)) {
    if (*(longlong *)(param_1 + 0x1d0) != 0) {
      FUN_140016e30();
    }
    uVar1 = FUN_140011aa0(param_1,param_2,param_3);
    if (*(longlong *)(param_1 + 0x1d0) != 0) {
      FUN_140016e50();
    }
    return uVar1 & 0xffffffff;
  }
  return 0xffffffff;
}


// ==== FUN_140011f10 @ 140011f10  undefined FUN_140011f10(longlong param_1, FILE * param_2)

void FUN_140011f10(longlong param_1,FILE *param_2)

{
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  fprintf(param_2,"Inserted events:\n");
  FUN_140011aa0(param_1,FUN_140011bf0,param_2);
  fprintf(param_2,"Active events:\n");
  FUN_140011aa0(param_1,FUN_140011d60,param_2);
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_140011fa0 @ 140011fa0  undefined FUN_140011fa0(longlong param_1, longlong param_2, ushort param_3)

void FUN_140011fa0(longlong param_1,longlong param_2,ushort param_3)

{
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  FUN_14001a5d0(param_1,param_2,param_3 & 0x86);
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_140012010 @ 140012010  undefined FUN_140012010(longlong param_1, int param_2)

void FUN_140012010(longlong param_1,int param_2)

{
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  FUN_14001a810(param_1,(longlong)param_2,1);
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_140012070 @ 140012070  undefined FUN_140012070(longlong param_1)

void FUN_140012070(longlong param_1)

{
  int iVar1;
  
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  *(int *)(param_1 + 200) = *(int *)(param_1 + 200) + 1;
  iVar1 = *(int *)(param_1 + 200);
  if (*(int *)(param_1 + 200) < *(int *)(param_1 + 0xcc)) {
    iVar1 = *(int *)(param_1 + 0xcc);
  }
  *(int *)(param_1 + 0xcc) = iVar1;
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_1400120d0 @ 1400120d0  undefined FUN_1400120d0(longlong param_1)

void FUN_1400120d0(longlong param_1)

{
  int *piVar1;
  undefined8 uVar2;
  
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  piVar1 = (int *)(param_1 + 200);
  *piVar1 = *piVar1 + -1;
  if ((*piVar1 == 0) && (*(int *)(param_1 + 0xf0) != 0)) {
    uVar2 = FUN_140016dd0();
    if (*(int *)(param_1 + 0x1c8) != (int)uVar2) {
      FUN_140011210(param_1);
    }
  }
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_140012170 @ 140012170  undefined FUN_140012170(void)

void FUN_140012170(void)

{
  FUN_14001bad0();
  FUN_140008d40();
  return;
}


// ==== FUN_140012190 @ 140012190  undefined FUN_140012190(void)

void FUN_140012190(void)

{
  FUN_14001bad0();
  FUN_140008d40();
  return;
}


// ==== FUN_1400121b0 @ 1400121b0  int FUN_1400121b0(uint param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

int FUN_1400121b0(uint param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 uVar1;
  
  uVar1 = FUN_14001bb00(param_1,param_2,param_3,param_4);
  if (-1 < (int)uVar1) {
    uVar1 = FUN_140008440(param_1,param_2,param_3,param_4);
    if (-1 < (int)uVar1) {
      uVar1 = FUN_140019580(param_1,param_2,param_3,param_4);
      return (-1 < (int)uVar1) - 1;
    }
  }
  return -1;
}


// ==== FUN_1400121f0 @ 1400121f0  undefined FUN_1400121f0(longlong * param_1)

void FUN_1400121f0(longlong *param_1)

{
  longlong lVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong lVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  longlong lVar7;
  ulonglong uVar8;
  
  FUN_14001b1e0(param_1);
  uVar8 = (ulonglong)*(uint *)(param_1 + 0x24);
  if (0 < (int)*(uint *)(param_1 + 0x24)) {
    puVar6 = (undefined8 *)param_1[0x23];
    do {
      lVar7 = *(longlong *)*puVar6;
      if (lVar7 != 0) {
        lVar1 = *(longlong *)(lVar7 + 0x28);
        lVar4 = lVar7;
        while (lVar2 = lVar7, lVar1 != 0) {
          lVar4 = *(longlong *)(lVar4 + 0x28);
          if ((*(longlong *)(lVar1 + 0x28) == 0) ||
             (lVar1 = *(longlong *)(*(longlong *)(lVar1 + 0x28) + 0x28), lVar4 == 0)) break;
        }
        do {
          plVar3 = (longlong *)(lVar2 + 0x28);
          lVar2 = *plVar3;
        } while (*plVar3 != 0);
        for (; lVar7 != 0; lVar7 = *(longlong *)(lVar7 + 0x28)) {
        }
      }
      puVar6 = puVar6 + 1;
      uVar8 = uVar8 - 1;
    } while (uVar8 != 0);
  }
  uVar8 = (ulonglong)*(uint *)(param_1 + 0x20);
  if (0 < (int)*(uint *)(param_1 + 0x20)) {
    lVar7 = 0;
    do {
      puVar6 = *(undefined8 **)(lVar7 + param_1[0x1f]);
      if (puVar6 != (undefined8 *)0x0) {
        plVar3 = (longlong *)*puVar6;
        puVar5 = puVar6;
        while (plVar3 != (longlong *)0x0) {
          puVar5 = (undefined8 *)*puVar5;
          if (((undefined8 *)*plVar3 == (undefined8 *)0x0) ||
             (plVar3 = *(longlong **)*plVar3, puVar5 == (undefined8 *)0x0)) break;
        }
        puVar5 = puVar6;
        if (puVar6 != (undefined8 *)0x0) {
          do {
            puVar5 = (undefined8 *)*puVar5;
          } while (puVar5 != (undefined8 *)0x0);
          for (; puVar6 != (undefined8 *)0x0; puVar6 = (undefined8 *)*puVar6) {
          }
        }
      }
      lVar7 = lVar7 + 0x10;
      uVar8 = uVar8 - 1;
    } while (uVar8 != 0);
  }
  for (puVar6 = (undefined8 *)param_1[0x21]; puVar6 != (undefined8 *)0x0;
      puVar6 = (undefined8 *)*puVar6) {
  }
  return;
}


// ==== FUN_1400122f0 @ 1400122f0  undefined FUN_1400122f0(undefined8 * param_1)

void FUN_1400122f0(undefined8 *param_1)

{
  if ((void *)*param_1 != (void *)0x0) {
    if (DAT_140103fa8 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00014001230c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*DAT_140103fa8)();
      return;
    }
    free((void *)*param_1);
  }
  return;
}


// ==== FUN_140012320 @ 140012320  undefined8 FUN_140012320(longlong * param_1, longlong param_2)

undefined8 FUN_140012320(longlong *param_1,longlong param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  longlong lVar5;
  int iVar6;
  bool bVar7;
  bool bVar8;
  
  if (*(int *)(param_2 + 0x28) == -1) {
    return 0xffffffff;
  }
  *(int *)(param_1 + 1) = (int)param_1[1] + -1;
  uVar1 = *(uint *)(param_2 + 0x28);
  lVar4 = *(longlong *)(*param_1 + (ulonglong)*(uint *)(param_1 + 1) * 8);
  if (0 < (int)uVar1) {
    lVar5 = *(longlong *)(*param_1 + (ulonglong)(uint)((int)(uVar1 - 1) / 2) * 8);
    iVar2 = *(int *)(lVar4 + 0x6c);
    iVar3 = *(int *)(lVar5 + 0x6c);
    bVar8 = SBORROW4(iVar3,iVar2);
    iVar6 = iVar3 - iVar2;
    bVar7 = iVar3 == iVar2;
    if (bVar7) {
      iVar2 = *(int *)(lVar4 + 0x70);
      iVar3 = *(int *)(lVar5 + 0x70);
      bVar8 = SBORROW4(iVar3,iVar2);
      iVar6 = iVar3 - iVar2;
      bVar7 = iVar3 == iVar2;
    }
    if (!bVar7 && bVar8 == iVar6 < 0) {
      FUN_1400103c0(param_1,uVar1,lVar4);
      *(undefined4 *)(param_2 + 0x28) = 0xffffffff;
      return 0;
    }
  }
  FUN_1400104d0(param_1,uVar1,lVar4);
  *(undefined4 *)(param_2 + 0x28) = 0xffffffff;
  return 0;
}


// ==== FUN_1400123b0 @ 1400123b0  undefined8 FUN_1400123b0(undefined8 * param_1, uint param_2)

undefined8 FUN_1400123b0(undefined8 *param_1,uint param_2)

{
  uint uVar1;
  void *pvVar2;
  uint uVar3;
  ulonglong uVar4;
  
  uVar1 = *(uint *)((longlong)param_1 + 0xc);
  if (uVar1 < param_2) {
    uVar3 = uVar1 * 2;
    if (uVar1 == 0) {
      uVar3 = 8;
    }
    uVar4 = (ulonglong)uVar3;
    if (uVar3 < param_2) {
      uVar4 = (ulonglong)param_2;
    }
    if (DAT_140103fa0 == (code *)0x0) {
      pvVar2 = realloc((void *)*param_1,uVar4 << 3);
    }
    else {
      pvVar2 = (void *)(*DAT_140103fa0)();
    }
    if (pvVar2 == (void *)0x0) {
      return 0xffffffff;
    }
    *param_1 = pvVar2;
    *(int *)((longlong)param_1 + 0xc) = (int)uVar4;
  }
  return 0;
}


// ==== FUN_140012420 @ 140012420  void * FUN_140012420(void)

void * FUN_140012420(void)

{
  undefined8 *puVar1;
  void *_Memory;
  undefined **ppuVar2;
  void *_Dst;
  int *piVar3;
  int iVar4;
  int iVar5;
  ulonglong _Count;
  undefined **ppuVar6;
  
  ppuVar6 = &PTR_PTR_140102480;
  iVar5 = 0;
  iVar4 = 0;
  ppuVar2 = &PTR_PTR_140102480;
  if (PTR_PTR_140102480 != (undefined *)0x0) {
    do {
      ppuVar2 = ppuVar2 + 1;
      iVar4 = iVar5 + 1;
      iVar5 = iVar4;
    } while (*ppuVar2 != (undefined *)0x0);
  }
  _Count = (ulonglong)(iVar4 + 1);
  if (iVar4 + 1 == 0) {
    return (void *)0x0;
  }
  if (DAT_140103f98 == (code *)0x0) {
    _Dst = calloc(_Count,8);
    if (_Dst != (void *)0x0) goto LAB_1400124b0;
  }
  else if ((_Count < 0x2000000000000000) &&
          (_Dst = (void *)(*DAT_140103f98)(_Count * 8), _Dst != (void *)0x0)) {
    memset(_Dst,0,_Count * 8);
LAB_1400124b0:
    if (_Dst == (void *)0x0) {
      return (void *)0x0;
    }
    iVar5 = 0;
    puVar1 = (undefined8 *)PTR_PTR_140102480;
    _Memory = DAT_140103f90;
    while (DAT_140103f90 = _Memory, puVar1 != (undefined8 *)0x0) {
      ppuVar6 = ppuVar6 + 1;
      iVar5 = iVar5 + 1;
      *(undefined8 *)((longlong)_Dst + -0x140102488 + (longlong)ppuVar6) = *puVar1;
      _Memory = DAT_140103f90;
      puVar1 = (undefined8 *)*ppuVar6;
    }
    *(undefined8 *)((longlong)_Dst + (longlong)iVar5 * 8) = 0;
    if (_Memory != (void *)0x0) {
      if (DAT_140103fa8 != (code *)0x0) {
        (*DAT_140103fa8)();
        DAT_140103f90 = _Dst;
        return _Dst;
      }
      free(_Memory);
    }
    DAT_140103f90 = _Dst;
    return _Dst;
  }
  piVar3 = _errno();
  *piVar3 = 0xc;
  return (void *)0x0;
}


// ==== FUN_140012580 @ 140012580  undefined8 * FUN_140012580(void)

undefined8 * FUN_140012580(void)

{
  undefined8 *puVar1;
  int *piVar2;
  
  if (DAT_140103f98 == (code *)0x0) {
    puVar1 = (undefined8 *)calloc(1,0x30);
    if (puVar1 == (undefined8 *)0x0) goto LAB_1400125d2;
  }
  else {
    puVar1 = (undefined8 *)(*DAT_140103f98)();
    if (puVar1 == (undefined8 *)0x0) {
LAB_1400125d2:
      piVar2 = _errno();
      *piVar2 = 0xc;
      return (undefined8 *)0x0;
    }
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1[5] = 0;
    if (puVar1 == (undefined8 *)0x0) {
      return (undefined8 *)0x0;
    }
  }
  *puVar1 = 0;
  puVar1[1] = puVar1;
  *(undefined4 *)((longlong)puVar1 + 0x14) = 0xffffffff;
  *(undefined4 *)((longlong)puVar1 + 0x1c) = 0x7fffffff;
  *(undefined4 *)(puVar1 + 4) = 1;
  return puVar1;
}


// ==== FUN_140012610 @ 140012610  undefined FUN_140012610(void * param_1)

void FUN_140012610(void *param_1)

{
  if (*(void **)((longlong)param_1 + 0x10) != (void *)0x0) {
    if (DAT_140103fa8 == (code *)0x0) {
      free(*(void **)((longlong)param_1 + 0x10));
      goto LAB_14001264d;
    }
    (*DAT_140103fa8)();
  }
  if (DAT_140103fa8 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000140012644. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*DAT_140103fa8)(param_1);
    return;
  }
LAB_14001264d:
                    /* WARNING: Could not recover jumptable at 0x000140012655. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  free(param_1);
  return;
}


// ==== FUN_140012660 @ 140012660  undefined FUN_140012660(undefined8 * param_1)

void FUN_140012660(undefined8 *param_1)

{
  longlong *_Memory;
  code *UNRECOVERED_JUMPTABLE;
  
  _Memory = (longlong *)*param_1;
  UNRECOVERED_JUMPTABLE = DAT_140103fa8;
  do {
    if (_Memory == (longlong *)0x0) {
      if (UNRECOVERED_JUMPTABLE == (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00014001270e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        free(param_1);
        return;
      }
                    /* WARNING: Could not recover jumptable at 0x0001400126fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*UNRECOVERED_JUMPTABLE)();
      return;
    }
    if (*_Memory == 0) {
      param_1[1] = _Memory[1];
    }
    else {
      *(longlong *)(*_Memory + 8) = _Memory[1];
    }
    *(longlong *)_Memory[1] = *_Memory;
    if ((void *)_Memory[2] == (void *)0x0) {
LAB_1400126b8:
      if (UNRECOVERED_JUMPTABLE == (code *)0x0) goto LAB_1400126d1;
      (*UNRECOVERED_JUMPTABLE)(_Memory);
      UNRECOVERED_JUMPTABLE = DAT_140103fa8;
    }
    else {
      if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
        (*UNRECOVERED_JUMPTABLE)();
        UNRECOVERED_JUMPTABLE = DAT_140103fa8;
        goto LAB_1400126b8;
      }
      free((void *)_Memory[2]);
LAB_1400126d1:
      free(_Memory);
    }
    _Memory = (longlong *)*param_1;
  } while( true );
}


// ==== FUN_140012720 @ 140012720  undefined8 FUN_140012720(longlong param_1, char * param_2)

undefined8 FUN_140012720(longlong param_1,char *param_2)

{
  undefined8 *_Memory;
  void *pvVar1;
  
  if (DAT_140103f98 == (code *)0x0) {
    _Memory = (undefined8 *)malloc(0x18);
  }
  else {
    _Memory = (undefined8 *)(*DAT_140103f98)();
  }
  if (_Memory != (undefined8 *)0x0) {
    pvVar1 = FUN_1400118f0(param_2);
    _Memory[2] = pvVar1;
    if (pvVar1 != (void *)0x0) {
      *_Memory = 0;
      _Memory[1] = *(undefined8 *)(param_1 + 8);
      **(undefined8 **)(param_1 + 8) = _Memory;
      *(undefined8 **)(param_1 + 8) = _Memory;
      return 0;
    }
    if (DAT_140103fa8 != (code *)0x0) {
      (*DAT_140103fa8)();
      return 0xffffffff;
    }
    free(_Memory);
  }
  return 0xffffffff;
}


// ==== FUN_1400127e0 @ 1400127e0  ulonglong FUN_1400127e0(longlong param_1, int param_2, undefined8 param_3, undefined8 param_4)

ulonglong FUN_1400127e0(longlong param_1,int param_2,undefined8 param_3,undefined8 param_4)

{
  void *pvVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  uint uVar4;
  ulonglong uVar5;
  
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  uVar3 = 0xffffffff;
  if ((*(int *)(param_1 + 0xd8) == 0) && (uVar3 = 0xffffffff, param_2 - 1U < 0xff)) {
    uVar3 = 0;
    if (param_2 != *(int *)(param_1 + 0x100)) {
      if (*(int *)(param_1 + 0x100) != 0) {
        if (DAT_140103fa8 == (code *)0x0) {
          free(*(void **)(param_1 + 0xf8));
        }
        else {
          (*DAT_140103fa8)();
        }
        *(undefined4 *)(param_1 + 0x100) = 0;
      }
      pvVar1 = FUN_140011850((longlong)param_2,0x10);
      *(void **)(param_1 + 0xf8) = pvVar1;
      if (pvVar1 == (void *)0x0) {
        FUN_140019050("%s: calloc","event_base_priority_init",param_3,param_4);
        uVar3 = 0xffffffff;
      }
      else {
        *(int *)(param_1 + 0x100) = param_2;
        uVar2 = uVar3;
        uVar5 = uVar3;
        if (0 < param_2) {
          do {
            *(undefined8 *)(uVar2 + *(longlong *)(param_1 + 0xf8)) = 0;
            uVar4 = (int)uVar5 + 1;
            *(longlong *)(uVar2 + 8 + *(longlong *)(param_1 + 0xf8)) =
                 (longlong)(int)uVar5 * 0x10 + *(longlong *)(param_1 + 0xf8);
            uVar2 = uVar2 + 0x10;
            uVar5 = (ulonglong)uVar4;
          } while ((int)uVar4 < *(int *)(param_1 + 0x100));
        }
      }
    }
  }
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return uVar3;
}


// ==== FUN_140012910 @ 140012910  ulonglong FUN_140012910(longlong param_1)

ulonglong FUN_140012910(longlong param_1)

{
  undefined8 uVar1;
  ulonglong uVar2;
  
  if (param_1 == 0) {
    return 0xffffffff;
  }
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  *(undefined4 *)(param_1 + 0xe4) = 1;
  if (*(int *)(param_1 + 0xf0) != 0) {
    uVar1 = FUN_140016dd0();
    if (*(int *)(param_1 + 0x1c8) != (int)uVar1) {
      uVar2 = FUN_140011210(param_1);
      uVar2 = uVar2 & 0xffffffff;
      goto LAB_14001296d;
    }
  }
  uVar2 = 0;
LAB_14001296d:
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return uVar2;
}


// ==== FUN_140012990 @ 140012990  ulonglong FUN_140012990(longlong param_1)

ulonglong FUN_140012990(longlong param_1)

{
  undefined8 uVar1;
  ulonglong uVar2;
  
  if (param_1 == 0) {
    return 0xffffffff;
  }
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  *(undefined4 *)(param_1 + 0xe8) = 1;
  if (*(int *)(param_1 + 0xf0) != 0) {
    uVar1 = FUN_140016dd0();
    if (*(int *)(param_1 + 0x1c8) != (int)uVar1) {
      uVar2 = FUN_140011210(param_1);
      uVar2 = uVar2 & 0xffffffff;
      goto LAB_1400129ed;
    }
  }
  uVar2 = 0;
LAB_1400129ed:
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return uVar2;
}


// ==== FUN_140012a10 @ 140012a10  undefined FUN_140012a10(undefined8 param_1, undefined8 param_2, longlong * param_3)

void FUN_140012a10(undefined8 param_1,undefined8 param_2,longlong *param_3)

{
  (*(code *)param_3[0x11])(param_1,param_2,param_3[0x12]);
  if (*(longlong *)(param_3[10] + 0x1d0) != 0) {
    FUN_140016e30();
  }
  if (*param_3 != 0) {
    *(longlong *)(*param_3 + 8) = param_3[1];
  }
  *(longlong *)param_3[1] = *param_3;
  if (*(longlong *)(param_3[10] + 0x1d0) != 0) {
    FUN_140016e50();
  }
  *(ushort *)(param_3 + 4) = *(ushort *)(param_3 + 4) & 0xff7f;
  if (DAT_140103fa8 != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x000140012a8b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*DAT_140103fa8)();
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000140012a93. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  free(param_3);
  return;
}


// ==== FUN_140012aa0 @ 140012aa0  undefined * FUN_140012aa0(longlong param_1, undefined8 param_2, ulonglong param_3, undefined8 param_4, undefined * param_5)

undefined *
FUN_140012aa0(longlong param_1,undefined8 param_2,ulonglong param_3,undefined8 param_4,
             undefined *param_5)

{
  undefined *_Memory;
  undefined8 uVar1;
  
  if (DAT_140103f98 == (code *)0x0) {
    _Memory = (undefined *)malloc(0x78);
  }
  else {
    _Memory = (undefined *)(*DAT_140103f98)();
  }
  if (_Memory != (undefined *)0x0) {
    uVar1 = FUN_140010e40(_Memory,param_1,param_2,param_3 & 0xffff,param_4,param_5);
    if (-1 < (int)uVar1) {
      return _Memory;
    }
    if (DAT_140103fa8 != (code *)0x0) {
      (*DAT_140103fa8)();
      return (undefined *)0x0;
    }
    free(_Memory);
  }
  return (undefined *)0x0;
}


// ==== FUN_140012b50 @ 140012b50  undefined8 FUN_140012b50(longlong param_1, longlong * param_2)

undefined8 FUN_140012b50(longlong param_1,longlong *param_2)

{
  ushort uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  
  uVar1 = *(ushort *)(param_2 + 2);
  uVar3 = 1;
  if ((uVar1 & 0x40) != 0) {
    return 0;
  }
  if ((uVar1 & 0x28) != 0) {
    if ((uVar1 & 0x28) == 8) {
      return 0;
    }
    FUN_140011460(param_1,param_2);
    uVar3 = 0;
  }
  FUN_1400115d0(param_1,param_2);
  if ((*(int *)(param_1 + 0xf0) != 0) &&
     (uVar2 = FUN_140016dd0(), *(int *)(param_1 + 0x1c8) != (int)uVar2)) {
    FUN_140011210(param_1);
  }
  return uVar3;
}


// ==== FUN_140012bd0 @ 140012bd0  undefined FUN_140012bd0(longlong param_1, undefined8 * param_2)

void FUN_140012bd0(longlong param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  
  if ((*(byte *)(param_2 + 2) & 0x28) == 0) {
    FUN_140011690(param_1,param_2);
    if (*(int *)(param_1 + 0xf0) != 0) {
      uVar1 = FUN_140016dd0();
      if (*(int *)(param_1 + 0x1c8) != (int)uVar1) {
        FUN_140011210(param_1);
      }
    }
  }
  return;
}


// ==== FUN_140012c10 @ 140012c10  ulonglong FUN_140012c10(longlong param_1, longlong * param_2)

ulonglong FUN_140012c10(longlong param_1,longlong *param_2)

{
  undefined8 uVar1;
  ulonglong uVar2;
  
  if (param_1 == 0) {
    param_1 = DAT_140103f80;
  }
  uVar2 = 1;
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  if (*(int *)(param_1 + 0xf4) < 0x21) {
    *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf4) + 1;
    uVar2 = FUN_140012b50(param_1,param_2);
    uVar2 = uVar2 & 0xffffffff;
  }
  else if ((*(byte *)(param_2 + 2) & 0x28) == 0) {
    FUN_140011690(param_1,param_2);
    if (*(int *)(param_1 + 0xf0) != 0) {
      uVar1 = FUN_140016dd0();
      if (*(int *)(param_1 + 0x1c8) != (int)uVar1) {
        FUN_140011210(param_1);
      }
    }
  }
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return uVar2;
}


// ==== FUN_140012cc0 @ 140012cc0  undefined FUN_140012cc0(longlong param_1, longlong param_2)

void FUN_140012cc0(longlong param_1,longlong param_2)

{
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016ef0();
  }
  *(int *)(param_1 + 0xd0) =
       *(int *)(param_1 + 0xd0) - (~((int)*(short *)(param_2 + 0x10) >> 4) & 1U);
  *(ushort *)(param_2 + 0x10) = *(ushort *)(param_2 + 0x10) & 0xfffe;
  if (((*(uint *)(param_2 + 0x70) & 0xf0000000) == 0x50000000) &&
     ((int)((int)*(uint *)(param_2 + 0x70) >> 0x14 & 0xffU) < *(int *)(param_1 + 0x120))) {
    if (*(longlong *)(param_2 + 0x28) != 0) {
      *(undefined8 *)(*(longlong *)(param_2 + 0x28) + 0x30) = *(undefined8 *)(param_2 + 0x30);
      **(undefined8 **)(param_2 + 0x30) = *(undefined8 *)(param_2 + 0x28);
      return;
    }
    *(undefined8 *)
     (*(longlong *)
       (*(longlong *)(param_1 + 0x118) +
       ((longlong)(ulonglong)*(uint *)(param_2 + 0x70) >> 0x14 & 0xffU) * 8) + 8) =
         *(undefined8 *)(param_2 + 0x30);
    **(undefined8 **)(param_2 + 0x30) = *(undefined8 *)(param_2 + 0x28);
    return;
  }
  FUN_140012320((longlong *)(param_1 + 0x150),param_2);
  return;
}


// ==== FUN_140012d90 @ 140012d90  undefined FUN_140012d90(longlong * param_1)

void FUN_140012d90(longlong *param_1)

{
  if (param_1[0x3a] != 0) {
    FUN_140016e30();
  }
  FUN_1400121f0(param_1);
  if (param_1[0x3a] != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_140012dd0 @ 140012dd0  undefined8 FUN_140012dd0(longlong * param_1, longlong param_2)

undefined8 FUN_140012dd0(longlong *param_1,longlong param_2)

{
  uint uVar1;
  void *pvVar2;
  uint uVar3;
  uint uVar4;
  
  uVar1 = *(uint *)((longlong)param_1 + 0xc);
  uVar3 = (int)param_1[1] + 1;
  if (uVar1 < uVar3) {
    uVar4 = uVar1 * 2;
    if (uVar1 == 0) {
      uVar4 = 8;
    }
    if (uVar4 < uVar3) {
      uVar4 = uVar3;
    }
    if (DAT_140103fa0 == (code *)0x0) {
      pvVar2 = realloc((void *)*param_1,(ulonglong)uVar4 << 3);
    }
    else {
      pvVar2 = (void *)(*DAT_140103fa0)();
    }
    if (pvVar2 == (void *)0x0) {
      return 0xffffffff;
    }
    *param_1 = (longlong)pvVar2;
    *(uint *)((longlong)param_1 + 0xc) = uVar4;
  }
  uVar1 = *(uint *)(param_1 + 1);
  *(uint *)(param_1 + 1) = uVar1 + 1;
  FUN_140010440(param_1,uVar1,param_2);
  return 0;
}


// ==== FUN_140012e90 @ 140012e90  undefined8 FUN_140012e90(longlong param_1)

undefined8 FUN_140012e90(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = *(longlong *)(param_1 + 0x40);
  if (*(longlong *)(lVar1 + 0x1d0) != 0) {
    FUN_140016ef0();
  }
  if ((*(byte *)(param_1 + 0x10) & 1) != 0) {
    FUN_140012cc0(lVar1,param_1);
    *(undefined4 *)(param_1 + 0x5c) = 0;
    *(undefined4 *)(param_1 + 0x58) = 0;
  }
  return 0;
}


// ==== FUN_140012ee0 @ 140012ee0  undefined8 FUN_140012ee0(longlong param_1)

undefined8 FUN_140012ee0(longlong param_1)

{
  longlong lVar1;
  
  if (*(longlong *)(*(longlong *)(param_1 + 0x40) + 0x1d0) != 0) {
    FUN_140016e30();
  }
  lVar1 = *(longlong *)(param_1 + 0x40);
  if (*(longlong *)(lVar1 + 0x1d0) != 0) {
    FUN_140016ef0();
  }
  if ((*(byte *)(param_1 + 0x10) & 1) != 0) {
    FUN_140012cc0(lVar1,param_1);
    *(undefined4 *)(param_1 + 0x5c) = 0;
    *(undefined4 *)(param_1 + 0x58) = 0;
  }
  if (*(longlong *)(*(longlong *)(param_1 + 0x40) + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return 0;
}


// ==== FUN_140012f60 @ 140012f60  ulonglong FUN_140012f60(longlong * param_1, int param_2)

ulonglong FUN_140012f60(longlong *param_1,int param_2)

{
  longlong *plVar1;
  undefined8 uVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  
  uVar4 = 0;
  if (param_1[8] == 0) {
    uVar4 = 0xffffffff;
  }
  else {
    if (*(longlong *)(param_1[8] + 0x1d0) != 0) {
      FUN_140016ef0();
    }
    if ((param_2 == 3) || ((*(byte *)(param_1 + 2) & 0x40) == 0)) {
      plVar1 = (longlong *)param_1[8];
      if ((((param_2 != 0) &&
           (((longlong *)plVar1[0x3d] == param_1 &&
            (uVar2 = FUN_140016dd0(), (int)plVar1[0x39] != (int)uVar2)))) &&
          ((param_2 == 1 || ((*(byte *)(param_1 + 0xd) & 0x40) == 0)))) &&
         (*(int *)(plVar1 + 0x3c) = (int)plVar1[0x3c] + 1, plVar1[0x3b] != 0)) {
        FUN_140016ed0();
      }
      if ((((*(byte *)(param_1 + 0xd) & 8) != 0) && ((short)param_1[0xb] != 0)) &&
         ((undefined2 *)param_1[0xc] != (undefined2 *)0x0)) {
        *(undefined2 *)param_1[0xc] = 0;
      }
      if ((*(byte *)(param_1 + 2) & 1) != 0) {
        FUN_140012cc0((longlong)plVar1,(longlong)param_1);
      }
      if ((*(ushort *)(param_1 + 2) & 8) == 0) {
        if ((*(ushort *)(param_1 + 2) & 0x20) != 0) {
          FUN_140011460((longlong)plVar1,param_1);
        }
      }
      else {
        FUN_1400113e0((longlong)plVar1,param_1);
      }
      if ((*(byte *)(param_1 + 2) & 2) != 0) {
        if (plVar1[0x3a] != 0) {
          FUN_140016ef0();
        }
        *(uint *)(plVar1 + 0x1a) = (int)plVar1[0x1a] - (~((int)(short)param_1[2] >> 4) & 1U);
        *(ushort *)(param_1 + 2) = *(ushort *)(param_1 + 2) & 0xfffd;
        if ((*(byte *)(param_1 + 0xd) & 0x86) == 0) {
          uVar3 = FUN_14001a790((longlong)plVar1,(int)param_1[7],(longlong)param_1);
        }
        else {
          uVar3 = FUN_14001a460(plVar1,param_1[7],(longlong)param_1);
        }
        uVar4 = uVar3 & 0xffffffff;
        if ((((int)uVar3 == 1) && (uVar4 = 0, (int)plVar1[0x1e] != 0)) &&
           (uVar2 = FUN_140016dd0(), (int)plVar1[0x39] != (int)uVar2)) {
          FUN_140011210((longlong)plVar1);
        }
      }
    }
    else {
      uVar4 = 0;
    }
  }
  return uVar4;
}


// ==== FUN_1400130f0 @ 1400130f0  undefined FUN_1400130f0(longlong * param_1, ushort param_2, undefined2 param_3)

void FUN_1400130f0(longlong *param_1,ushort param_2,undefined2 param_3)

{
  ushort uVar1;
  longlong lVar2;
  undefined8 uVar3;
  
  lVar2 = param_1[8];
  if (*(longlong *)(lVar2 + 0x1d0) != 0) {
    FUN_140016ef0();
  }
  uVar1 = *(ushort *)(param_1 + 2);
  if ((uVar1 & 0x40) == 0) {
    if ((uVar1 & 0x28) == 0) {
      *(ushort *)((longlong)param_1 + 0x6a) = param_2;
    }
    else {
      if ((uVar1 & 0x28) == 8) {
        *(ushort *)((longlong)param_1 + 0x6a) = *(ushort *)((longlong)param_1 + 0x6a) | param_2;
        return;
      }
      if ((uVar1 & 0x28) == 0x20) {
        *(ushort *)((longlong)param_1 + 0x6a) = *(ushort *)((longlong)param_1 + 0x6a) | param_2;
      }
    }
    if ((int)(uint)*(byte *)((longlong)param_1 + 0x12) < *(int *)(lVar2 + 0xec)) {
      *(undefined4 *)(lVar2 + 0xe8) = 1;
    }
    if ((*(byte *)(param_1 + 0xd) & 8) != 0) {
      if (((*(longlong **)(lVar2 + 0x1e8) == param_1) &&
          (uVar3 = FUN_140016dd0(), *(int *)(lVar2 + 0x1c8) != (int)uVar3)) &&
         (*(int *)(lVar2 + 0x1e0) = *(int *)(lVar2 + 0x1e0) + 1, *(longlong *)(lVar2 + 0x1d8) != 0))
      {
        FUN_140016ed0();
      }
      *(undefined2 *)(param_1 + 0xb) = param_3;
      param_1[0xc] = 0;
    }
    FUN_140012b50(lVar2,param_1);
  }
  return;
}


// ==== FUN_1400131d0 @ 1400131d0  undefined FUN_1400131d0(undefined8 * param_1, ushort param_2)

void FUN_1400131d0(undefined8 *param_1,ushort param_2)

{
  longlong lVar1;
  undefined8 uVar2;
  
  lVar1 = param_1[8];
  if (*(longlong *)(lVar1 + 0x1d0) != 0) {
    FUN_140016ef0();
  }
  if ((*(byte *)(param_1 + 2) & 0x28) != 0) {
    *(ushort *)((longlong)param_1 + 0x6a) = *(ushort *)((longlong)param_1 + 0x6a) | param_2;
    return;
  }
  *(ushort *)((longlong)param_1 + 0x6a) = param_2;
  FUN_140011690(lVar1,param_1);
  if (*(int *)(lVar1 + 0xf0) != 0) {
    uVar2 = FUN_140016dd0();
    if (*(int *)(lVar1 + 0x1c8) != (int)uVar2) {
      FUN_140011210(lVar1);
    }
  }
  return;
}


// ==== FUN_140013250 @ 140013250  ulonglong FUN_140013250(longlong param_1, longlong * param_2)

ulonglong FUN_140013250(longlong param_1,longlong *param_2)

{
  ulonglong uVar1;
  
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  uVar1 = FUN_140012b50(param_1,param_2);
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
    uVar1 = uVar1 & 0xffffffff;
  }
  return uVar1;
}


// ==== FUN_1400132a0 @ 1400132a0  ulonglong FUN_1400132a0(longlong param_1, longlong * param_2, int param_3)

ulonglong FUN_1400132a0(longlong param_1,longlong *param_2,int param_3)

{
  ushort uVar1;
  ulonglong uVar2;
  
  uVar1 = *(ushort *)(param_2 + 2);
  if (((uVar1 & 0x40) == 0) || (param_3 != 0)) {
    if ((char)uVar1 < '\0') {
      uVar2 = FUN_140012f60(param_2,(param_3 != 0) + 2);
      return uVar2;
    }
    if ((uVar1 & 0x28) != 0) {
      if ((uVar1 & 0x28) == 8) {
        FUN_1400113e0(param_1,param_2);
      }
      else if ((uVar1 & 0x28) == 0x20) {
        FUN_140011460(param_1,param_2);
        return 0;
      }
    }
  }
  return 0;
}


// ==== FUN_140013300 @ 140013300  undefined FUN_140013300(longlong param_1)

void FUN_140013300(longlong param_1)

{
  longlong *plVar1;
  longlong *plVar2;
  bool bVar3;
  int iVar4;
  undefined8 uVar6;
  int local_res8;
  int iStackX_c;
  longlong lVar5;
  
  if (*(int *)(param_1 + 0x158) != 0) {
    FUN_1400105b0(param_1,&local_res8);
    while ((*(int *)(param_1 + 0x158) != 0 &&
           (plVar1 = (longlong *)**(undefined8 **)(param_1 + 0x150), plVar1 != (longlong *)0x0))) {
      if (*(int *)((longlong)plVar1 + 0x6c) == local_res8) {
        bVar3 = iStackX_c < (int)plVar1[0xe];
      }
      else {
        bVar3 = local_res8 < *(int *)((longlong)plVar1 + 0x6c);
      }
      if (bVar3) {
        return;
      }
      if (plVar1[8] != 0) {
        if (*(longlong *)(plVar1[8] + 0x1d0) != 0) {
          FUN_140016ef0();
        }
        if ((*(byte *)(plVar1 + 2) & 0x40) == 0) {
          plVar2 = (longlong *)plVar1[8];
          if ((((*(byte *)(plVar1 + 0xd) & 8) != 0) && ((short)plVar1[0xb] != 0)) &&
             ((undefined2 *)plVar1[0xc] != (undefined2 *)0x0)) {
            *(undefined2 *)plVar1[0xc] = 0;
          }
          if ((*(byte *)(plVar1 + 2) & 1) != 0) {
            FUN_140012cc0((longlong)plVar2,(longlong)plVar1);
          }
          if ((*(ushort *)(plVar1 + 2) & 8) == 0) {
            if ((*(ushort *)(plVar1 + 2) & 0x20) != 0) {
              FUN_140011460((longlong)plVar2,plVar1);
            }
          }
          else {
            FUN_1400113e0((longlong)plVar2,plVar1);
          }
          if ((*(byte *)(plVar1 + 2) & 2) != 0) {
            if (plVar2[0x3a] != 0) {
              FUN_140016ef0();
            }
            *(uint *)(plVar2 + 0x1a) = (int)plVar2[0x1a] - (~((int)(short)plVar1[2] >> 4) & 1U);
            *(ushort *)(plVar1 + 2) = *(ushort *)(plVar1 + 2) & 0xfffd;
            if ((*(byte *)(plVar1 + 0xd) & 0x86) == 0) {
              uVar6 = FUN_14001a790((longlong)plVar2,(int)plVar1[7],(longlong)plVar1);
              iVar4 = (int)uVar6;
            }
            else {
              lVar5 = FUN_14001a460(plVar2,plVar1[7],(longlong)plVar1);
              iVar4 = (int)lVar5;
            }
            if (((iVar4 == 1) && ((int)plVar2[0x1e] != 0)) &&
               (uVar6 = FUN_140016dd0(), (int)plVar2[0x39] != (int)uVar6)) {
              FUN_140011210((longlong)plVar2);
            }
          }
        }
      }
      FUN_1400130f0(plVar1,1,1);
    }
  }
  return;
}


// ==== FUN_140013490 @ 140013490  undefined FUN_140013490(longlong param_1, longlong param_2)

void FUN_140013490(longlong param_1,longlong param_2)

{
  int iVar1;
  
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016ef0();
  }
  *(int *)(param_1 + 0xd0) =
       *(int *)(param_1 + 0xd0) + (~((int)*(short *)(param_2 + 0x10) >> 4) & 1U);
  iVar1 = *(int *)(param_1 + 0xd0);
  if (*(int *)(param_1 + 0xd0) < *(int *)(param_1 + 0xd4)) {
    iVar1 = *(int *)(param_1 + 0xd4);
  }
  *(int *)(param_1 + 0xd4) = iVar1;
  *(ushort *)(param_2 + 0x10) = *(ushort *)(param_2 + 0x10) | 1;
  if (((*(uint *)(param_2 + 0x70) & 0xf0000000) == 0x50000000) &&
     ((int)((int)*(uint *)(param_2 + 0x70) >> 0x14 & 0xffU) < *(int *)(param_1 + 0x120))) {
    FUN_1400114d0(*(longlong **)
                   (*(longlong *)(param_1 + 0x118) +
                   ((longlong)(ulonglong)*(uint *)(param_2 + 0x70) >> 0x14 & 0xffU) * 8),param_2);
    return;
  }
  FUN_140012dd0((longlong *)(param_1 + 0x150),param_2);
  return;
}


// ==== FUN_140013550 @ 140013550  undefined FUN_140013550(undefined8 param_1, undefined8 param_2, undefined8 * param_3)

void FUN_140013550(undefined8 param_1,undefined8 param_2,undefined8 *param_3)

{
  longlong lVar1;
  longlong *plVar2;
  longlong *plVar3;
  int iVar4;
  undefined8 uVar6;
  int local_res18;
  int iStackX_1c;
  ulonglong local_res20;
  longlong lVar5;
  
  lVar1 = param_3[0x12];
  if (*(longlong *)(lVar1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  FUN_1400105b0(lVar1,&local_res18);
  plVar2 = (longlong *)*param_3;
  do {
    if (plVar2 == (longlong *)0x0) {
LAB_1400137b7:
      if (*(longlong *)(lVar1 + 0x1d0) != 0) {
        FUN_140016e50();
      }
      return;
    }
    if ((local_res18 < *(int *)((longlong)plVar2 + 0x6c)) ||
       ((*(int *)((longlong)plVar2 + 0x6c) == local_res18 &&
        (iStackX_1c < (int)(*(uint *)(plVar2 + 0xe) & 0xfffff))))) {
      local_res20 = *(ulonglong *)((longlong)plVar2 + 0x6c) & 0xfffffffffffff;
      FUN_140013f70(param_3 + 3,&local_res20,1);
      goto LAB_1400137b7;
    }
    if (plVar2[8] != 0) {
      if (*(longlong *)(plVar2[8] + 0x1d0) != 0) {
        FUN_140016ef0();
      }
      if ((*(byte *)(plVar2 + 2) & 0x40) == 0) {
        plVar3 = (longlong *)plVar2[8];
        if ((((*(byte *)(plVar2 + 0xd) & 8) != 0) && ((short)plVar2[0xb] != 0)) &&
           ((undefined2 *)plVar2[0xc] != (undefined2 *)0x0)) {
          *(undefined2 *)plVar2[0xc] = 0;
        }
        if ((*(byte *)(plVar2 + 2) & 1) != 0) {
          FUN_140012cc0((longlong)plVar3,(longlong)plVar2);
        }
        if ((*(ushort *)(plVar2 + 2) & 8) == 0) {
          if ((*(ushort *)(plVar2 + 2) & 0x20) != 0) {
            if (plVar3[0x3a] != 0) {
              FUN_140016ef0();
            }
            *(uint *)(plVar3 + 0x1a) = (int)plVar3[0x1a] - (~((int)(short)plVar2[2] >> 4) & 1U);
            *(ushort *)(plVar2 + 2) = *(ushort *)(plVar2 + 2) & 0xffdf;
            *(int *)(plVar3 + 0x1b) = (int)plVar3[0x1b] + -1;
            if (*plVar2 == 0) {
              plVar3[0x22] = plVar2[1];
            }
            else {
              *(longlong *)(*plVar2 + 8) = plVar2[1];
            }
            *(longlong *)plVar2[1] = *plVar2;
          }
        }
        else {
          if (plVar3[0x3a] != 0) {
            FUN_140016ef0();
          }
          *(uint *)(plVar3 + 0x1a) = (int)plVar3[0x1a] - (~((int)(short)plVar2[2] >> 4) & 1U);
          *(ushort *)(plVar2 + 2) = *(ushort *)(plVar2 + 2) & 0xfff7;
          *(int *)(plVar3 + 0x1b) = (int)plVar3[0x1b] + -1;
          if (*plVar2 == 0) {
            *(longlong *)(plVar3[0x1f] + 8 + (ulonglong)*(byte *)((longlong)plVar2 + 0x12) * 0x10) =
                 plVar2[1];
            *(longlong *)plVar2[1] = *plVar2;
          }
          else {
            *(longlong *)(*plVar2 + 8) = plVar2[1];
            *(longlong *)plVar2[1] = *plVar2;
          }
        }
        if ((*(byte *)(plVar2 + 2) & 2) != 0) {
          if (plVar3[0x3a] != 0) {
            FUN_140016ef0();
          }
          *(uint *)(plVar3 + 0x1a) = (int)plVar3[0x1a] - (~((int)(short)plVar2[2] >> 4) & 1U);
          *(ushort *)(plVar2 + 2) = *(ushort *)(plVar2 + 2) & 0xfffd;
          if ((*(byte *)(plVar2 + 0xd) & 0x86) == 0) {
            uVar6 = FUN_14001a790((longlong)plVar3,(int)plVar2[7],(longlong)plVar2);
            iVar4 = (int)uVar6;
          }
          else {
            lVar5 = FUN_14001a460(plVar3,plVar2[7],(longlong)plVar2);
            iVar4 = (int)lVar5;
          }
          if (((iVar4 == 1) && ((int)plVar3[0x1e] != 0)) &&
             (uVar6 = FUN_140016dd0(), (int)plVar3[0x39] != (int)uVar6)) {
            FUN_140011210((longlong)plVar3);
          }
        }
      }
    }
    FUN_1400130f0(plVar2,1,1);
    plVar2 = (longlong *)*param_3;
  } while( true );
}


// ==== FUN_1400137e0 @ 1400137e0  undefined8 * FUN_1400137e0(longlong param_1, int * param_2)

undefined8 * FUN_1400137e0(longlong param_1,int *param_2)

{
  uint uVar1;
  undefined8 uVar2;
  longlong lVar3;
  void *pvVar4;
  undefined8 *_Dst;
  int *piVar5;
  undefined8 *puVar6;
  uint uVar7;
  longlong *plVar8;
  int iVar9;
  undefined8 *puVar10;
  ulonglong uVar11;
  int local_res8;
  int iStackX_c;
  
  puVar6 = (undefined8 *)0x0;
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  uVar1 = param_2[1];
  if (1000000 < (int)uVar1) {
    uVar2 = *(undefined8 *)param_2;
    uVar7 = (uint)((ulonglong)uVar2 >> 0x20);
    if (((uVar1 & 0xf0000000) == 0x50000000) &&
       ((int)((int)uVar1 >> 0x14 & 0xffU) < *(int *)(param_1 + 0x120))) {
      uVar7 = uVar7 & 0xfffff;
    }
    param_2 = &local_res8;
    local_res8 = (int)uVar2;
    _local_res8 = CONCAT44((int)uVar7 % 1000000,local_res8 + (int)uVar7 / 1000000);
  }
  uVar1 = *(uint *)(param_1 + 0x120);
  uVar11 = (ulonglong)uVar1;
  puVar10 = puVar6;
  if (0 < (int)uVar1) {
    plVar8 = *(longlong **)(param_1 + 0x118);
    do {
      lVar3 = *plVar8;
      if ((*param_2 == *(int *)(lVar3 + 0x10)) &&
         (param_2[1] == (*(uint *)(lVar3 + 0x14) & 0xfffff))) {
        puVar6 = (undefined8 *)(lVar3 + 0x10);
        goto LAB_140013a85;
      }
      uVar7 = (int)puVar10 + 1;
      puVar10 = (undefined8 *)(ulonglong)uVar7;
      plVar8 = plVar8 + 1;
    } while ((int)uVar7 < (int)uVar1);
  }
  if (uVar1 == 0x100) {
    FUN_1400191c0("%s: Too many common timeouts already in use; we only support %d per event_base",
                  "event_base_init_common_timeout",0x100,uVar11);
    goto LAB_140013a85;
  }
  if (*(uint *)(param_1 + 0x124) == uVar1) {
    if ((int)uVar1 < 0x10) {
      iVar9 = 0x10;
    }
    else {
      iVar9 = uVar1 * 2;
    }
    if (DAT_140103fa0 == (code *)0x0) {
      pvVar4 = realloc(*(void **)(param_1 + 0x118),(longlong)iVar9 << 3);
    }
    else {
      pvVar4 = (void *)(*DAT_140103fa0)();
    }
    if (pvVar4 == (void *)0x0) {
      FUN_140019050("%s: realloc","event_base_init_common_timeout",puVar10,uVar11);
      goto LAB_140013a85;
    }
    *(int *)(param_1 + 0x124) = iVar9;
    *(void **)(param_1 + 0x118) = pvVar4;
  }
  if (DAT_140103f98 == (code *)0x0) {
    _Dst = (undefined8 *)calloc(1,0x98);
    if (_Dst != (undefined8 *)0x0) goto LAB_14001397a;
LAB_1400139af:
    piVar5 = _errno();
    *piVar5 = 0xc;
  }
  else {
    _Dst = (undefined8 *)(*DAT_140103f98)(0x98);
    if (_Dst == (undefined8 *)0x0) goto LAB_1400139af;
    puVar10 = (undefined8 *)0x98;
    memset(_Dst,0,0x98);
LAB_14001397a:
    if (_Dst != (undefined8 *)0x0) {
      *_Dst = 0;
      _Dst[1] = _Dst;
      *(int *)(_Dst + 2) = *param_2;
      *(uint *)((longlong)_Dst + 0x14) = (*(uint *)(param_1 + 0x120) | 0x500) << 0x14 | param_2[1];
      _Dst[6] = FUN_140013550;
      _Dst[0xb] = param_1;
      _Dst[10] = 0xffffffffffffffff;
      *(undefined2 *)(_Dst + 0x10) = 0;
      *(undefined2 *)((longlong)_Dst + 0x82) = 0;
      *(undefined2 *)(_Dst + 0xe) = 0;
      _Dst[0xf] = 0;
      *(undefined1 *)((longlong)_Dst + 0x2b) = 0;
      *(undefined4 *)(_Dst + 8) = 0xffffffff;
      puVar6 = _Dst;
      if (_Dst == (undefined8 *)&DAT_140103f88) {
        puVar6 = _Dst + 3;
      }
      _Dst[7] = puVar6;
      *(undefined2 *)(_Dst + 5) = 0x80;
      *(char *)((longlong)_Dst + 0x2a) = (char)(*(int *)(param_1 + 0x100) / 2);
      *(ushort *)(_Dst + 5) = *(ushort *)(_Dst + 5) | 0x10;
      if (((*(byte *)(_Dst + 5) & 8) == 0) && (0 < *(int *)(_Dst[0xb] + 0x100))) {
        *(undefined1 *)((longlong)_Dst + 0x2a) = 0;
      }
      _Dst[0x12] = param_1;
      *(undefined8 **)(*(longlong *)(param_1 + 0x118) + (longlong)*(int *)(param_1 + 0x120) * 8) =
           _Dst;
      *(int *)(param_1 + 0x120) = *(int *)(param_1 + 0x120) + 1;
      puVar6 = _Dst + 2;
      goto LAB_140013a85;
    }
  }
  FUN_140019050("%s: calloc","event_base_init_common_timeout",puVar10,uVar11);
LAB_140013a85:
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return puVar6;
}


// ==== FUN_140013ab0 @ 140013ab0  undefined8 FUN_140013ab0(undefined8 param_1, uint param_2, longlong * param_3, longlong param_4)

undefined8 FUN_140013ab0(undefined8 param_1,uint param_2,longlong *param_3,longlong param_4)

{
  longlong *plVar1;
  int iVar2;
  undefined8 uVar4;
  longlong lVar3;
  
  if (param_3[8] != 0) {
    if (*(longlong *)(param_3[8] + 0x1d0) != 0) {
      FUN_140016ef0();
    }
    if ((*(byte *)(param_3 + 2) & 0x40) == 0) {
      plVar1 = (longlong *)param_3[8];
      if ((((*(byte *)(param_3 + 0xd) & 8) != 0) && ((short)param_3[0xb] != 0)) &&
         ((undefined2 *)param_3[0xc] != (undefined2 *)0x0)) {
        *(undefined2 *)param_3[0xc] = 0;
      }
      if ((*(byte *)(param_3 + 2) & 1) != 0) {
        FUN_140012cc0((longlong)plVar1,(longlong)param_3);
      }
      if ((*(ushort *)(param_3 + 2) & 8) == 0) {
        if ((*(ushort *)(param_3 + 2) & 0x20) != 0) {
          FUN_140011460((longlong)plVar1,param_3);
        }
      }
      else {
        FUN_1400113e0((longlong)plVar1,param_3);
      }
      if ((*(byte *)(param_3 + 2) & 2) != 0) {
        if (plVar1[0x3a] != 0) {
          FUN_140016ef0();
        }
        *(uint *)(plVar1 + 0x1a) = (int)plVar1[0x1a] - (~((int)(short)param_3[2] >> 4) & 1U);
        *(ushort *)(param_3 + 2) = *(ushort *)(param_3 + 2) & 0xfffd;
        if ((*(byte *)(param_3 + 0xd) & 0x86) == 0) {
          uVar4 = FUN_14001a790((longlong)plVar1,(int)param_3[7],(longlong)param_3);
          iVar2 = (int)uVar4;
        }
        else {
          lVar3 = FUN_14001a460(plVar1,param_3[7],(longlong)param_3);
          iVar2 = (int)lVar3;
        }
        if (((iVar2 == 1) && ((int)plVar1[0x1e] != 0)) &&
           (uVar4 = FUN_140016dd0(), (int)plVar1[0x39] != (int)uVar4)) {
          FUN_140011210((longlong)plVar1);
        }
      }
    }
  }
  *(char *)((longlong)param_3 + 0x13) = ((param_2 >> 0x10 & 1) != 0) + '\x05';
  param_3[3] = param_4;
  FUN_1400130f0(param_3,0x40,1);
  *(ushort *)(param_3 + 2) = *(ushort *)(param_3 + 2) | 0x40;
  return 0;
}


// ==== FUN_140013c00 @ 140013c00  ulonglong FUN_140013c00(uint param_1, longlong * param_2, longlong param_3)

ulonglong FUN_140013c00(uint param_1,longlong *param_2,longlong param_3)

{
  longlong lVar1;
  ulonglong uVar2;
  
  lVar1 = param_2[8];
  if (*(longlong *)(lVar1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  uVar2 = FUN_140013ab0(lVar1,param_1,param_2,param_3);
  if (*(longlong *)(lVar1 + 0x1d0) != 0) {
    FUN_140016e50();
    uVar2 = uVar2 & 0xffffffff;
  }
  return uVar2;
}


// ==== FUN_140013c90 @ 140013c90  undefined FUN_140013c90(longlong param_1, undefined8 param_2, longlong * param_3, longlong param_4)

void FUN_140013c90(longlong param_1,undefined8 param_2,longlong *param_3,longlong param_4)

{
  ushort uVar1;
  longlong *plVar2;
  int iVar3;
  undefined8 uVar5;
  longlong lVar4;
  
  uVar1 = *(ushort *)(param_3 + 2);
  if ((char)uVar1 < '\0') {
    if (param_3[8] != 0) {
      if (*(longlong *)(param_3[8] + 0x1d0) != 0) {
        FUN_140016ef0();
      }
      if ((*(byte *)(param_3 + 2) & 0x40) == 0) {
        plVar2 = (longlong *)param_3[8];
        if ((((*(byte *)(param_3 + 0xd) & 8) != 0) && ((short)param_3[0xb] != 0)) &&
           ((undefined2 *)param_3[0xc] != (undefined2 *)0x0)) {
          *(undefined2 *)param_3[0xc] = 0;
        }
        if ((*(byte *)(param_3 + 2) & 1) != 0) {
          FUN_140012cc0((longlong)plVar2,(longlong)param_3);
        }
        if ((*(ushort *)(param_3 + 2) & 8) == 0) {
          if ((*(ushort *)(param_3 + 2) & 0x20) != 0) {
            FUN_140011460((longlong)plVar2,param_3);
          }
        }
        else {
          FUN_1400113e0((longlong)plVar2,param_3);
        }
        if ((*(byte *)(param_3 + 2) & 2) != 0) {
          if (plVar2[0x3a] != 0) {
            FUN_140016ef0();
          }
          *(uint *)(plVar2 + 0x1a) = (int)plVar2[0x1a] - (~((int)(short)param_3[2] >> 4) & 1U);
          *(ushort *)(param_3 + 2) = *(ushort *)(param_3 + 2) & 0xfffd;
          if ((*(byte *)(param_3 + 0xd) & 0x86) == 0) {
            uVar5 = FUN_14001a790((longlong)plVar2,(int)param_3[7],(longlong)param_3);
            iVar3 = (int)uVar5;
          }
          else {
            lVar4 = FUN_14001a460(plVar2,param_3[7],(longlong)param_3);
            iVar3 = (int)lVar4;
          }
          if ((iVar3 == 1) && ((int)plVar2[0x1e] != 0)) {
            uVar5 = FUN_140016dd0();
            if ((int)plVar2[0x39] != (int)uVar5) {
              FUN_140011210((longlong)plVar2);
            }
          }
        }
      }
    }
  }
  else if (((uVar1 & 0x40) == 0) && ((uVar1 & 0x28) != 0)) {
    if ((uVar1 & 0x28) == 8) {
      FUN_1400113e0(param_1,param_3);
    }
    else if ((uVar1 & 0x28) == 0x20) {
      FUN_140011460(param_1,param_3);
    }
  }
  *(undefined1 *)((longlong)param_3 + 0x13) = 4;
  param_3[3] = param_4;
  FUN_140012b50(param_1,param_3);
  *(ushort *)(param_3 + 2) = *(ushort *)(param_3 + 2) | 0x40;
  return;
}


// ==== FUN_140013e00 @ 140013e00  undefined FUN_140013e00(longlong param_1, uint param_2, longlong * param_3, longlong param_4)

void FUN_140013e00(longlong param_1,uint param_2,longlong *param_3,longlong param_4)

{
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  FUN_140013c90(param_1,(ulonglong)param_2,param_3,param_4);
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_140013e70 @ 140013e70  undefined8 FUN_140013e70(longlong param_1, int param_2, undefined8 * param_3, longlong param_4)

undefined8 FUN_140013e70(longlong param_1,int param_2,undefined8 *param_3,longlong param_4)

{
  ushort uVar1;
  longlong *plVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  
  uVar3 = 0;
  if (param_1 == 0) {
    param_1 = DAT_140103f80;
  }
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  uVar4 = uVar3;
  if (0 < (longlong)param_2) {
    do {
      plVar2 = (longlong *)param_3[uVar3];
      if (plVar2 == *(longlong **)(param_1 + 0x1e8)) {
        FUN_140013c90(param_1,0,plVar2,param_4);
        uVar4 = (ulonglong)((int)uVar4 + 1);
      }
      else {
        uVar1 = *(ushort *)(plVar2 + 2);
        if ((uVar1 & 0x40) == 0) {
          if ((char)uVar1 < '\0') {
            FUN_140012f60(plVar2,2);
          }
          else if ((uVar1 & 0x28) != 0) {
            if ((uVar1 & 0x28) == 8) {
              FUN_1400113e0(param_1,plVar2);
            }
            else if ((uVar1 & 0x28) == 0x20) {
              FUN_140011460(param_1,plVar2);
            }
          }
        }
      }
      uVar3 = uVar3 + 1;
    } while ((longlong)uVar3 < (longlong)param_2);
    if ((int)uVar4 != 0) goto LAB_140013f3d;
  }
  FUN_140013c90(param_1,0,(longlong *)*param_3,param_4);
LAB_140013f3d:
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return 0;
}


// ==== FUN_140013f70 @ 140013f70  undefined8 * FUN_140013f70(longlong * param_1, ulonglong * param_2, int param_3)

undefined8 * FUN_140013f70(longlong *param_1,ulonglong *param_2,int param_3)

{
  ushort uVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong lVar4;
  int iVar5;
  bool bVar6;
  undefined8 uVar7;
  undefined8 *puVar8;
  int iVar9;
  bool bVar10;
  uint local_res8;
  int local_38;
  int iStack_34;
  ulonglong local_30 [2];
  
  plVar2 = (longlong *)param_1[8];
  bVar10 = false;
  bVar6 = false;
  local_res8 = 0;
  if (plVar2[0x3a] != 0) {
    FUN_140016ef0();
  }
  if ((*(ushort *)(param_1 + 2) & 0x40) != 0) {
    return (undefined8 *)0xffffffff;
  }
  if (((param_2 != (ulonglong *)0x0) && ((*(ushort *)(param_1 + 2) & 1) == 0)) &&
     (uVar7 = FUN_1400123b0(plVar2 + 0x2a,(int)plVar2[0x2b] + 1), (int)uVar7 == -1)) {
    return (undefined8 *)0xffffffff;
  }
  if ((((longlong *)plVar2[0x3d] == param_1) && ((*(byte *)(param_1 + 0xd) & 8) != 0)) &&
     ((uVar7 = FUN_140016dd0(), (int)plVar2[0x39] != (int)uVar7 &&
      (*(int *)(plVar2 + 0x3c) = (int)plVar2[0x3c] + 1, plVar2[0x3b] != 0)))) {
    FUN_140016ed0();
  }
  uVar1 = *(ushort *)(param_1 + 0xd);
  if (((uVar1 & 0x8e) != 0) && ((*(byte *)(param_1 + 2) & 0x2a) == 0)) {
    if ((uVar1 & 0x86) == 0) {
      if ((uVar1 & 8) != 0) {
        puVar8 = (undefined8 *)FUN_14001a680((longlong)plVar2,(int)param_1[7],(longlong)param_1);
        goto LAB_140014056;
      }
LAB_14001405f:
      if (plVar2[0x3a] != 0) {
        FUN_140016ef0();
      }
      *(uint *)(plVar2 + 0x1a) = (int)plVar2[0x1a] + (~((int)(short)param_1[2] >> 4) & 1U);
      iVar9 = (int)plVar2[0x1a];
      if ((int)plVar2[0x1a] < *(int *)((longlong)plVar2 + 0xd4)) {
        iVar9 = *(int *)((longlong)plVar2 + 0xd4);
      }
      puVar8 = (undefined8 *)(ulonglong)local_res8;
      *(int *)((longlong)plVar2 + 0xd4) = iVar9;
      *(ushort *)(param_1 + 2) = *(ushort *)(param_1 + 2) | 2;
    }
    else {
      puVar8 = FUN_14001a240(plVar2,param_1[7],(longlong)param_1);
LAB_140014056:
      local_res8 = (uint)puVar8;
      if (local_res8 != 0xffffffff) goto LAB_14001405f;
    }
    if ((int)puVar8 == 1) {
      local_res8 = 0;
      bVar6 = true;
    }
    else if ((int)puVar8 == -1) {
      return puVar8;
    }
  }
  if (param_2 == (ulonglong *)0x0) {
LAB_140014264:
    if (!bVar6) goto LAB_140014289;
  }
  else {
    if ((*(char *)((longlong)param_1 + 0x13) == '\x02') && (param_3 == 0)) {
      param_1[0xb] = *param_2;
    }
    if ((*(byte *)(param_1 + 2) & 1) != 0) {
      FUN_140012cc0((longlong)plVar2,(longlong)param_1);
    }
    if (((*(byte *)(param_1 + 2) & 8) != 0) && ((*(byte *)((longlong)param_1 + 0x6a) & 1) != 0)) {
      if (((*(byte *)(param_1 + 0xd) & 8) != 0) &&
         (((short)param_1[0xb] != 0 && ((undefined2 *)param_1[0xc] != (undefined2 *)0x0)))) {
        *(undefined2 *)param_1[0xc] = 0;
      }
      FUN_1400113e0((longlong)plVar2,param_1);
    }
    FUN_1400105b0((longlong)plVar2,&local_38);
    if ((*(uint *)((longlong)param_2 + 4) & 0xf0000000) == 0x50000000) {
      bVar10 = (int)((int)*(uint *)((longlong)param_2 + 4) >> 0x14 & 0xffU) < (int)plVar2[0x24];
    }
    if (param_3 == 0) {
      if (bVar10) {
        local_30[0] = *param_2;
        iVar9 = iStack_34 + ((uint)(local_30[0] >> 0x20) & 0xfffff);
        *(int *)((longlong)param_1 + 0x6c) = (int)local_30[0] + local_38;
        *(int *)(param_1 + 0xe) = iVar9;
        if (999999 < iVar9) {
          *(int *)((longlong)param_1 + 0x6c) = (int)local_30[0] + local_38 + 1;
          *(int *)(param_1 + 0xe) = iVar9 + -1000000;
        }
        *(uint *)(param_1 + 0xe) =
             *(uint *)(param_1 + 0xe) | *(uint *)((longlong)param_2 + 4) & 0xfff00000;
      }
      else {
        *(int *)((longlong)param_1 + 0x6c) = (int)*param_2 + local_38;
        iVar9 = *(int *)((longlong)param_2 + 4) + iStack_34;
        *(int *)(param_1 + 0xe) = iVar9;
        if (999999 < iVar9) {
          *(int *)((longlong)param_1 + 0x6c) = *(int *)((longlong)param_1 + 0x6c) + 1;
          *(int *)(param_1 + 0xe) = (int)param_1[0xe] + -1000000;
        }
      }
    }
    else {
      *(ulonglong *)((longlong)param_1 + 0x6c) = *param_2;
    }
    FUN_140013490((longlong)plVar2,(longlong)param_1);
    if (bVar10) {
      plVar3 = *(longlong **)
                (plVar2[0x23] + ((longlong)(ulonglong)*(uint *)(param_1 + 0xe) >> 0x14 & 0xffU) * 8)
      ;
      if (param_1 == (longlong *)*plVar3) {
        local_30[0] = *(ulonglong *)((longlong)param_1 + 0x6c) & 0xfffffffffffff;
        FUN_140013f70(plVar3 + 3,local_30,1);
      }
      goto LAB_140014264;
    }
    if ((int)param_1[5] != 0) {
      if (((int)plVar2[0x2b] != 0) && (lVar4 = *(longlong *)plVar2[0x2a], lVar4 != 0)) {
        iVar9 = *(int *)(lVar4 + 0x6c);
        bVar10 = SBORROW4(iVar9,local_38);
        iVar5 = iVar9 - local_38;
        if (iVar9 == local_38) {
          bVar10 = SBORROW4(*(int *)(lVar4 + 0x70),iStack_34);
          iVar5 = *(int *)(lVar4 + 0x70) - iStack_34;
        }
        if (bVar10 != iVar5 < 0) goto LAB_14001426b;
      }
      goto LAB_140014264;
    }
  }
LAB_14001426b:
  if (((int)plVar2[0x1e] != 0) && (uVar7 = FUN_140016dd0(), (int)plVar2[0x39] != (int)uVar7)) {
    FUN_140011210((longlong)plVar2);
  }
LAB_140014289:
  return (undefined8 *)(ulonglong)local_res8;
}


// ==== FUN_1400142a0 @ 1400142a0  ulonglong FUN_1400142a0(longlong * param_1, int param_2)

ulonglong FUN_1400142a0(longlong *param_1,int param_2)

{
  ulonglong uVar1;
  
  if (*(longlong *)(param_1[8] + 0x1d0) != 0) {
    FUN_140016e30();
  }
  uVar1 = FUN_140012f60(param_1,param_2);
  if (*(longlong *)(param_1[8] + 0x1d0) != 0) {
    FUN_140016e50();
    uVar1 = uVar1 & 0xffffffff;
  }
  return uVar1;
}


// ==== FUN_140014300 @ 140014300  int FUN_140014300(longlong * param_1)

int FUN_140014300(longlong *param_1)

{
  longlong *plVar1;
  undefined8 uVar2;
  longlong lVar3;
  int iVar4;
  int iVar5;
  
  if (*(longlong *)(param_1[8] + 0x1d0) != 0) {
    FUN_140016e30();
  }
  iVar4 = 0;
  if (param_1[8] == 0) {
    iVar5 = -1;
  }
  else {
    if (*(longlong *)(param_1[8] + 0x1d0) != 0) {
      FUN_140016ef0();
    }
    iVar5 = 0;
    if ((*(byte *)(param_1 + 2) & 0x40) == 0) {
      plVar1 = (longlong *)param_1[8];
      if (((((longlong *)plVar1[0x3d] == param_1) &&
           (uVar2 = FUN_140016dd0(), (int)plVar1[0x39] != (int)uVar2)) &&
          ((*(byte *)(param_1 + 0xd) & 0x40) == 0)) &&
         (*(int *)(plVar1 + 0x3c) = (int)plVar1[0x3c] + 1, plVar1[0x3b] != 0)) {
        FUN_140016ed0();
      }
      if ((((*(byte *)(param_1 + 0xd) & 8) != 0) && ((short)param_1[0xb] != 0)) &&
         ((undefined2 *)param_1[0xc] != (undefined2 *)0x0)) {
        *(undefined2 *)param_1[0xc] = 0;
      }
      if ((*(byte *)(param_1 + 2) & 1) != 0) {
        FUN_140012cc0((longlong)plVar1,(longlong)param_1);
      }
      if ((*(ushort *)(param_1 + 2) & 8) == 0) {
        if ((*(ushort *)(param_1 + 2) & 0x20) != 0) {
          FUN_140011460((longlong)plVar1,param_1);
        }
      }
      else {
        FUN_1400113e0((longlong)plVar1,param_1);
      }
      iVar5 = iVar4;
      if ((*(byte *)(param_1 + 2) & 2) != 0) {
        if (plVar1[0x3a] != 0) {
          FUN_140016ef0();
        }
        *(uint *)(plVar1 + 0x1a) = (int)plVar1[0x1a] - (~((int)(short)param_1[2] >> 4) & 1U);
        *(ushort *)(param_1 + 2) = *(ushort *)(param_1 + 2) & 0xfffd;
        if ((*(byte *)(param_1 + 0xd) & 0x86) == 0) {
          uVar2 = FUN_14001a790((longlong)plVar1,(int)param_1[7],(longlong)param_1);
          iVar5 = (int)uVar2;
        }
        else {
          lVar3 = FUN_14001a460(plVar1,param_1[7],(longlong)param_1);
          iVar5 = (int)lVar3;
        }
        if (((iVar5 == 1) && (iVar5 = iVar4, (int)plVar1[0x1e] != 0)) &&
           (uVar2 = FUN_140016dd0(), (int)plVar1[0x39] != (int)uVar2)) {
          FUN_140011210((longlong)plVar1);
        }
      }
    }
  }
  if (*(longlong *)(param_1[8] + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return iVar5;
}


// ==== FUN_1400144a0 @ 1400144a0  int FUN_1400144a0(longlong * param_1)

int FUN_1400144a0(longlong *param_1)

{
  longlong *plVar1;
  undefined8 uVar2;
  longlong lVar3;
  int iVar4;
  int iVar5;
  
  if (*(longlong *)(param_1[8] + 0x1d0) != 0) {
    FUN_140016e30();
  }
  iVar4 = 0;
  if (param_1[8] == 0) {
    iVar5 = -1;
  }
  else {
    if (*(longlong *)(param_1[8] + 0x1d0) != 0) {
      FUN_140016ef0();
    }
    iVar5 = 0;
    if ((*(byte *)(param_1 + 2) & 0x40) == 0) {
      plVar1 = (longlong *)param_1[8];
      if ((((longlong *)plVar1[0x3d] == param_1) &&
          (uVar2 = FUN_140016dd0(), (int)plVar1[0x39] != (int)uVar2)) &&
         (*(int *)(plVar1 + 0x3c) = (int)plVar1[0x3c] + 1, plVar1[0x3b] != 0)) {
        FUN_140016ed0();
      }
      if ((((*(byte *)(param_1 + 0xd) & 8) != 0) && ((short)param_1[0xb] != 0)) &&
         ((undefined2 *)param_1[0xc] != (undefined2 *)0x0)) {
        *(undefined2 *)param_1[0xc] = 0;
      }
      if ((*(byte *)(param_1 + 2) & 1) != 0) {
        FUN_140012cc0((longlong)plVar1,(longlong)param_1);
      }
      if ((*(ushort *)(param_1 + 2) & 8) == 0) {
        if ((*(ushort *)(param_1 + 2) & 0x20) != 0) {
          FUN_140011460((longlong)plVar1,param_1);
        }
      }
      else {
        FUN_1400113e0((longlong)plVar1,param_1);
      }
      iVar5 = iVar4;
      if ((*(byte *)(param_1 + 2) & 2) != 0) {
        if (plVar1[0x3a] != 0) {
          FUN_140016ef0();
        }
        *(uint *)(plVar1 + 0x1a) = (int)plVar1[0x1a] - (~((int)(short)param_1[2] >> 4) & 1U);
        *(ushort *)(param_1 + 2) = *(ushort *)(param_1 + 2) & 0xfffd;
        if ((*(byte *)(param_1 + 0xd) & 0x86) == 0) {
          uVar2 = FUN_14001a790((longlong)plVar1,(int)param_1[7],(longlong)param_1);
          iVar5 = (int)uVar2;
        }
        else {
          lVar3 = FUN_14001a460(plVar1,param_1[7],(longlong)param_1);
          iVar5 = (int)lVar3;
        }
        if (((iVar5 == 1) && (iVar5 = iVar4, (int)plVar1[0x1e] != 0)) &&
           (uVar2 = FUN_140016dd0(), (int)plVar1[0x39] != (int)uVar2)) {
          FUN_140011210((longlong)plVar1);
        }
      }
    }
  }
  if (*(longlong *)(param_1[8] + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return iVar5;
}


// ==== FUN_140014630 @ 140014630  int FUN_140014630(longlong * param_1)

int FUN_140014630(longlong *param_1)

{
  longlong *plVar1;
  longlong lVar2;
  undefined8 uVar3;
  int iVar4;
  int iVar5;
  
  if (*(longlong *)(param_1[8] + 0x1d0) != 0) {
    FUN_140016e30();
  }
  iVar4 = 0;
  if (param_1[8] == 0) {
    iVar5 = -1;
  }
  else {
    if (*(longlong *)(param_1[8] + 0x1d0) != 0) {
      FUN_140016ef0();
    }
    iVar5 = 0;
    if ((*(byte *)(param_1 + 2) & 0x40) == 0) {
      plVar1 = (longlong *)param_1[8];
      if ((((*(byte *)(param_1 + 0xd) & 8) != 0) && ((short)param_1[0xb] != 0)) &&
         ((undefined2 *)param_1[0xc] != (undefined2 *)0x0)) {
        *(undefined2 *)param_1[0xc] = 0;
      }
      if ((*(byte *)(param_1 + 2) & 1) != 0) {
        FUN_140012cc0((longlong)plVar1,(longlong)param_1);
      }
      if ((*(ushort *)(param_1 + 2) & 8) == 0) {
        if ((*(ushort *)(param_1 + 2) & 0x20) != 0) {
          FUN_140011460((longlong)plVar1,param_1);
        }
      }
      else {
        FUN_1400113e0((longlong)plVar1,param_1);
      }
      iVar5 = iVar4;
      if ((*(byte *)(param_1 + 2) & 2) != 0) {
        if (plVar1[0x3a] != 0) {
          FUN_140016ef0();
        }
        *(uint *)(plVar1 + 0x1a) = (int)plVar1[0x1a] - (~((int)(short)param_1[2] >> 4) & 1U);
        *(ushort *)(param_1 + 2) = *(ushort *)(param_1 + 2) & 0xfffd;
        if ((*(byte *)(param_1 + 0xd) & 0x86) == 0) {
          uVar3 = FUN_14001a790((longlong)plVar1,(int)param_1[7],(longlong)param_1);
          iVar5 = (int)uVar3;
        }
        else {
          lVar2 = FUN_14001a460(plVar1,param_1[7],(longlong)param_1);
          iVar5 = (int)lVar2;
        }
        if (((iVar5 == 1) && (iVar5 = iVar4, (int)plVar1[0x1e] != 0)) &&
           (uVar3 = FUN_140016dd0(), (int)plVar1[0x39] != (int)uVar3)) {
          FUN_140011210((longlong)plVar1);
        }
      }
    }
  }
  if (*(longlong *)(param_1[8] + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return iVar5;
}


// ==== FUN_140014790 @ 140014790  undefined FUN_140014790(longlong * param_1, ushort param_2, undefined2 param_3)

void FUN_140014790(longlong *param_1,ushort param_2,undefined2 param_3)

{
  if (*(longlong *)(param_1[8] + 0x1d0) != 0) {
    FUN_140016e30();
  }
  FUN_1400130f0(param_1,param_2,param_3);
  if (*(longlong *)(param_1[8] + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_140014800 @ 140014800  undefined FUN_140014800(undefined8 * param_1, ushort param_2)

void FUN_140014800(undefined8 *param_1,ushort param_2)

{
  if (*(longlong *)(param_1[8] + 0x1d0) != 0) {
    FUN_140016e30();
  }
  FUN_1400131d0(param_1,param_2);
  if (*(longlong *)(param_1[8] + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return;
}


// ==== FUN_140014860 @ 140014860  ulonglong FUN_140014860(longlong param_1, longlong * param_2)

ulonglong FUN_140014860(longlong param_1,longlong *param_2)

{
  ushort uVar1;
  ulonglong uVar2;
  
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e30();
  }
  uVar1 = *(ushort *)(param_2 + 2);
  if ((uVar1 & 0x40) == 0) {
    if ((char)uVar1 < '\0') {
      uVar2 = FUN_140012f60(param_2,2);
      uVar2 = uVar2 & 0xffffffff;
      goto LAB_1400148c9;
    }
    if ((uVar1 & 0x28) != 0) {
      if ((uVar1 & 0x28) == 8) {
        FUN_1400113e0(param_1,param_2);
      }
      else if ((uVar1 & 0x28) == 0x20) {
        FUN_140011460(param_1,param_2);
      }
    }
  }
  uVar2 = 0;
LAB_1400148c9:
  if (*(longlong *)(param_1 + 0x1d0) != 0) {
    FUN_140016e50();
  }
  return uVar2;
}


