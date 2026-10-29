// ==== CAsyncDBThread::helper_1400018c0  @1400018c0  [medium:callgraph-r0]  (orig: FUN_1400018c0)
undefined8 FUN_1400018c0(void)

{
  return DAT_1409754e8;
}

// ==== CAsyncDBThread::helper_1400029f0  @1400029f0  [medium:callgraph-r0]  (orig: FUN_1400029f0)
void FUN_1400029f0(void)

{
  void *pvVar1;
  
  pvVar1 = DAT_1409754e8;
  if (DAT_1409754e8 != (void *)0x0) {
    if (*(HANDLE *)((longlong)DAT_1409754e8 + 8) != (HANDLE)0x0) {
      CloseHandle(*(HANDLE *)((longlong)DAT_1409754e8 + 8));
    }
    operator_delete(pvVar1);
    DAT_1409754e8 = (void *)0x0;
  }
  return;
}

// ==== CAsyncDBThread::helper_140005c70  @140005c70  [medium:callgraph-r0]  (orig: FUN_140005c70)
undefined8 FUN_140005c70(longlong param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x1028) < param_2) {
    log_InlineLogERROR(
                      "ClearPacket()  error, Getpacket OutBufSize:%d, ClearPacket nLen:%d, m_nLen:%d, unMsgType:%d at %s, %d"
                      );
  }
  if (*(int *)(param_1 + 0x2030) == 2) {
    iVar2 = *(int *)(param_1 + 0x1028) - param_2;
    if (0 < iVar2) {
      memcpy((void *)(param_1 + 0x28),(void *)((longlong)param_2 + 0x28 + param_1),(longlong)iVar2);
    }
    piVar1 = (int *)(param_1 + 0x1028);
    *piVar1 = *piVar1 - param_2;
    if (-1 < *piVar1) {
      return 1;
    }
    *(undefined4 *)(param_1 + 0x1028) = 0;
  }
  return 0;
}

// ==== CAsyncDBThread::helper_140005d60  @140005d60  [medium:callgraph-r1]  (orig: FUN_140005d60)
bool FUN_140005d60(longlong param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  if (*(int *)(param_1 + 0x2030) != 2) {
    return false;
  }
  if (*(int *)(param_1 + 0x202c) == 0) {
    return true;
  }
  iVar2 = Ordinal_19(*(undefined8 *)(param_1 + 0x20),param_1 + 0x102c,*(int *)(param_1 + 0x202c),0);
  if (0 < iVar2) {
    iVar3 = *(int *)(param_1 + 0x202c) - iVar2;
    if (0 < iVar3) {
      memcpy((void *)(param_1 + 0x102c),(void *)((longlong)iVar2 + 0x102c + param_1),(longlong)iVar3
            );
    }
    piVar1 = (int *)(param_1 + 0x202c);
    *piVar1 = *piVar1 - iVar2;
    if (*piVar1 < 0) {
      log_InlineLogERROR(&DAT_1406d9c10);
    }
    return *(int *)(param_1 + 0x202c) == 0;
  }
  iVar2 = Ordinal_111();
  if (iVar2 != 0x2746) {
    log_InlineLogERROR("Flush packet failed[%d].");
  }
  if (*(longlong *)(param_1 + 0x20) != -1) {
    Ordinal_3();
  }
  *(undefined4 *)(param_1 + 0x2030) = 0;
  *(undefined4 *)(param_1 + 0x1028) = 0;
  *(undefined4 *)(param_1 + 0x202c) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0xffffffffffffffff;
  return false;
}

// ==== CAsyncDBThread::helper_140006730  @140006730  [medium:callgraph-r0]  (orig: FUN_140006730)
longlong FUN_140006730(longlong param_1,undefined4 *param_2,char param_3)

{
  int iVar1;
  
  if (param_2 == (undefined4 *)0x0) {
    log_InlineLogERROR(&DAT_1406d9c10);
    return 0;
  }
  *param_2 = 0;
  if (*(int *)(param_1 + 0x2030) == 2) {
    if (*(longlong *)(param_1 + 0x20) != -1) {
      if (param_3 != '\0') {
        iVar1 = *(int *)(param_1 + 0x1028);
        if (iVar1 < 0x1000) {
          iVar1 = Ordinal_16(*(longlong *)(param_1 + 0x20),(longlong)iVar1 + 0x28 + param_1,
                             0x1000 - iVar1,0);
          if (iVar1 < 1) {
            if (iVar1 == 0) {
              log_InlineLogERROR("GetPacket() connect be close.");
            }
            else {
              if (-1 < iVar1) goto LAB_140006857;
              iVar1 = Ordinal_111();
              if (iVar1 == 0x2733) goto LAB_140006857;
              if (iVar1 != 0x2746) {
                log_InlineLogERROR("recv packet failed[%d].");
              }
            }
            FUN_140005d20(param_1);
          }
          else {
            *(int *)(param_1 + 0x1028) = *(int *)(param_1 + 0x1028) + iVar1;
          }
        }
      }
LAB_140006857:
      *param_2 = *(undefined4 *)(param_1 + 0x1028);
      return param_1 + 0x28;
    }
    log_InlineLogERROR("GetPacket() invalid socket failed.");
    if (*(longlong *)(param_1 + 0x20) != -1) {
      Ordinal_3();
    }
    *(undefined8 *)(param_1 + 0x20) = 0xffffffffffffffff;
    *(undefined4 *)(param_1 + 0x2030) = 0;
    *(undefined4 *)(param_1 + 0x1028) = 0;
    *(undefined4 *)(param_1 + 0x202c) = 0;
  }
  return 0;
}

// ==== CAsyncDBThread::helper_140006880  @140006880  [medium:callgraph-r0]  (orig: FUN_140006880)
undefined8 FUN_140006880(longlong param_1,void *param_2,int param_3,char param_4)

{
  undefined8 uVar1;
  
  if (*(int *)(param_1 + 0x2030) != 2) {
    return 0;
  }
  if (*(longlong *)(param_1 + 0x20) == -1) {
    log_InlineLogERROR("SendPacket() invalid socket failed.");
    if (*(longlong *)(param_1 + 0x20) != -1) {
      Ordinal_3();
    }
  }
  else {
    if (0x1000 < param_3 + *(int *)(param_1 + 0x202c)) {
      FUN_140005d60(param_1);
    }
    if (*(int *)(param_1 + 0x202c) + param_3 < 0x1001) {
      memcpy((void *)((longlong)*(int *)(param_1 + 0x202c) + 0x102c + param_1),param_2,
             (longlong)param_3);
      *(int *)(param_1 + 0x202c) = *(int *)(param_1 + 0x202c) + param_3;
      if (param_4 != '\0') {
        uVar1 = FUN_140005d60(param_1);
        return uVar1;
      }
      return 1;
    }
    log_InlineLogERROR("SendPacket() buf full!");
    if (*(longlong *)(param_1 + 0x20) != -1) {
      Ordinal_3();
      *(undefined8 *)(param_1 + 0x20) = 0xffffffffffffffff;
      *(undefined4 *)(param_1 + 0x2030) = 0;
      *(undefined4 *)(param_1 + 0x1028) = 0;
      *(undefined4 *)(param_1 + 0x202c) = 0;
      return 0;
    }
  }
  *(undefined8 *)(param_1 + 0x20) = 0xffffffffffffffff;
  *(undefined4 *)(param_1 + 0x2030) = 0;
  *(undefined4 *)(param_1 + 0x1028) = 0;
  *(undefined4 *)(param_1 + 0x202c) = 0;
  return 0;
}

// ==== CAsyncDBThread::helper_14001e720  @14001e720  [medium:callgraph-r0]  (orig: FUN_14001e720)
void FUN_14001e720(void)

{
  IAnalyst *pIVar1;
  
  pIVar1 = Analyst();
  (**(code **)(*(longlong *)pIVar1 + 8))(pIVar1,"syslog/analyst");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0,1,"CMapGroupThread::OnProcess");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,1,1,"|-CMapGroupThread ProcessMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,2,1,"| |-ProcessMsg KERNEL_CLOSEKERNEL");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,3,1,"| |-ProcessMsg MAPGROUP_LOGINOVER");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,4,1,"| | |-MAPGROUP_LOGINOVER CreateAllItem");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,5,1,"| | |-MAPGROUP_LOGINOVER GameLogin");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,6,1,"| | `-MAPGROUP_LOGINOVER CUserManager::LoginUser");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,7,1,"| |-ProcessClientMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,8,1,"| | `-CUser::OnLoginOver");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,9,1,"| |-ProcessCrossMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,10,1,"| |-ProcessOSToGSServerMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0xb,1,"| `-ProcessGSToOSMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0xc,1,"`-CMapGroupKernel::OnTimer");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0xd,1,"  |-CMapGroup::OnTimer");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0xe,1,"  | |-CRoleManager::OnTimer");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0xf,1,"  | | |-CUser::OnTimer");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x10,1,"  | | | |-CUser::OnTimer ProcessAutoAttack");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x11,1,"  | | | |-CUser::OnTimer Process Action");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x12,1,"  | | | `-CUser::OnTimer Other Section2");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)
            (pIVar1,0x13,1,"  | | |   `-CUser::OnTimer ProcessExploreResult");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x14,1,"  | |-CUserManager::OnTimer");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x15,1,"  | | `-CUserManager::OnTimer New day init");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x16,1,"  | `-CMapGroup::OnTimer ProcessAction");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x17,1,"  |-CGame::OnTimer");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x18,1,"  |-CElitePKArenicMgr::OnTimer");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x19,1,"  `-CFrontierFlagWarMgr::OnTimer");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x1a,1,"      |-CFlag::OnTimer");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x1b,1,"      |-RefreshHighRateAltar");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x1c,1,"      `-BroadcastAltarAttackRank");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x1d,1,"CWorldThread::OnProcess");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x1e,1,"|-CWorldThread ProcessMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x1f,1,"`-CWorldKernel::OnTimer");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x20,1,"CUserLoginThread::OnProcess");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x21,1,"|-CUserLoginThread ProcessMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x22,1,"`-CUserKernel::OnTimer");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x23,1,"CSocketThread::OnProcess");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x24,1,"|-CSocketThread ProcessMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x25,1,"| |-CONNECTMSG");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x26,1,"| |-READMSG");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x27,1,"| |-EVENTMSG");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x28,1,"| |-SOCKET_BROADCAST_MAPGROUPMSG");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x29,1,"| `-SOCKET_SENDMULTICLIENTMSG");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x2a,1,"`-CSocketKernel::OnTimer");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x2b,1,"CCrossClientThread::OnProcess");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x2c,1,"|-CCrossClientThread ProcessClientMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x2d,1,"|-CCrossKernel::ProcessLocalMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x2e,1,"|-CCrossClientThread::ProcessSocket");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x2f,1,"CChatThread::OnProcess");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x30,1,"|-CChatThread ProcessMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x31,1,"`-CChatThread OnTimer");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x32,1,"CAuctionSearchThread::OnProcess");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x33,1,"|-CAuctionSearchThread ProcessMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x34,1,"`-CAuctionSearchThread OnTimer");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x35,1,"CIPADPaymentsSocketThread::OnProcess");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x36,1,"|-CIPADPaymentsSocketThread ProcessMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x37,1,"`-CIPADPaymentsSocketThread::OnTimer");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x38,1,"CGooglePaymentsThread::OnProcess");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x39,1,"|-CGooglePaymentsThread::ProcessMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x3a,1,"`-CGooglePaymentsThread::OnTimer");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x3b,1,"  `CGooglePaymentsThread::ProcessPayResultData")
  ;
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x3e,1,"CAsyncDBThread::OnProcess");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x3f,1,"|-CAsyncDBThread mysql_query");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x40,1,"| |-CDatabase::ExcuteMySQL update");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x41,1,"| |-CDatabase::ExcuteMySQL delete");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x42,1,"| |-CDatabase::ExcuteMySQL other");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x43,1,"CDatabase::ExcuteMySQL insert");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x44,1,"CDatabase::ExecuteSyncSQL");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x45,1,"CDatabase::ExcuteMySQL select");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x46,1,"CRecord::Insert failure");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x47,1,"CMapGroupThread WaitMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x48,1,"CCrossClientThread WaitMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x49,1,"CChatThread WaitMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x4a,1,"CAuctionSearchThread WaitMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x4b,1,"CAsyncDBThread WaitMsg");
  pIVar1 = Analyst();
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x3c,1,"CLogThread OnProcess");
  pIVar1 = Analyst();
                    /* WARNING: Could not recover jumptable at 0x00014001f06c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)**(undefined8 **)pIVar1)(pIVar1,0x3d,1,"`-CLogThread ProcessMsg");
  return;
}

// ==== CAsyncDBThread::helper_14001f070  @14001f070  [medium:callgraph-r0]  (orig: FUN_14001f070)
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_14001f070(void)

{
  int iVar1;
  char cVar2;
  IAnalyst *pIVar3;
  int iVar4;
  undefined4 *puVar5;
  longlong lVar6;
  longlong lVar7;
  int local_res10 [2];
  undefined8 local_res18;
  undefined8 local_res20;
  longlong local_48;
  undefined4 local_40 [10];
  
  pIVar3 = Analyst();
  (**(code **)(*(longlong *)pIVar3 + 0x30))(pIVar3,"syslog/analyst");
  iVar4 = DAT_140975998;
  _DAT_140975968 = 0;
  _DAT_140975970 = 0;
  DAT_140975978 = 0;
  DAT_140975980 = 0;
  DAT_140975988 = 0;
  DAT_140975990 = 0;
  _DAT_140975998 = 0;
  pIVar3 = Analyst();
  cVar2 = (**(code **)(*(longlong *)pIVar3 + 0x10))
                    (pIVar3,0x45,&local_res18,&local_res20,local_res10);
  if (cVar2 != '\0') {
    _DAT_140975968 = CONCAT44(DAT_14097596c,local_res10[0]);
    DAT_140975978 = local_res18;
    DAT_140975988 = local_res20;
  }
  pIVar3 = Analyst();
  cVar2 = (**(code **)(*(longlong *)pIVar3 + 0x10))
                    (pIVar3,0x43,&local_res18,&local_res20,local_res10);
  if (cVar2 != '\0') {
    _DAT_140975968 = CONCAT44(local_res10[0],DAT_140975968);
    DAT_140975980 = local_res18;
    DAT_140975990 = local_res20;
  }
  pIVar3 = Analyst();
  cVar2 = (**(code **)(*(longlong *)pIVar3 + 0x10))(pIVar3,0x40,0,0,local_res10);
  iVar1 = DAT_140975970;
  if (cVar2 != '\0') {
    iVar1 = local_res10[0];
  }
  DAT_140975970 = iVar1;
  pIVar3 = Analyst();
  cVar2 = (**(code **)(*(longlong *)pIVar3 + 0x10))(pIVar3,0x41,0,0,local_res10);
  if (cVar2 != '\0') {
    DAT_140975974 = local_res10[0];
  }
  pIVar3 = Analyst();
  cVar2 = (**(code **)(*(longlong *)pIVar3 + 0x10))(pIVar3,0x46,0,0,local_res10);
  if (cVar2 != '\0') {
    iVar4 = iVar4 + local_res10[0];
  }
  LOCK();
  _DAT_140975998 = CONCAT44(DAT_140975998_4,iVar4);
  UNLOCK();
  lVar7 = 0;
  local_40[1] = 0x1d;
  lVar6 = 8;
  local_40[0] = 0;
  local_40[2] = 0x20;
  local_40[3] = 0x23;
  local_40[4] = 0x2b;
  local_40[5] = 0x2f;
  local_40[6] = 0x32;
  local_40[7] = 0x3e;
  local_48 = 0;
  puVar5 = local_40;
  do {
    pIVar3 = Analyst();
    (**(code **)(*(longlong *)pIVar3 + 0x10))(pIVar3,*puVar5,&local_48,0,0);
    lVar7 = lVar7 + local_48;
    puVar5 = puVar5 + 1;
    lVar6 = lVar6 + -1;
  } while (lVar6 != 0);
  LOCK();
  UNLOCK();
  DAT_1409759a8 = lVar7;
  pIVar3 = Analyst();
  (**(code **)(*(longlong *)pIVar3 + 0x28))(pIVar3);
  LOCK();
  _DAT_1409759a0 = _DAT_1409759a0 + 1;
  UNLOCK();
  return;
}

// ==== CAsyncDBThread::helper_14001f5b0  @14001f5b0  [medium:callgraph-r0]  (orig: FUN_14001f5b0)
longlong FUN_14001f5b0(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)(*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18) >> 3) <= param_2) {
    _invalid_parameter_noinfo();
  }
  return *(longlong *)(param_1 + 0x18) + param_2 * 8;
}

// ==== CAsyncDBThread::helper_14001f810  @14001f810  [medium:callgraph-r3]  (orig: FUN_14001f810)
void FUN_14001f810(void)

{
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_30 [48];
  
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
  basic_string<char,std::char_traits<char>,std::allocator<char>_>(local_70,"vector<T> too long");
  std::exception::exception((exception *)local_48);
  local_48[0] = std::logic_error::vftable;
  std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
  basic_string<char,std::char_traits<char>,std::allocator<char>_>
            (local_30,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)local_70);
  local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_48,(ThrowInfo *)&DAT_140944488);
}

// ==== CAsyncDBThread::helper_140021bd0  @140021bd0  [medium:callgraph-r0]  (orig: FUN_140021bd0)
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined8 FUN_140021bd0(longlong param_1)

{
  char cVar1;
  undefined8 uVar2;
  undefined1 auStack_488 [32];
  undefined1 *local_468;
  undefined4 *local_460;
  undefined4 local_458;
  undefined4 local_454;
  undefined4 local_450;
  undefined8 local_448;
  undefined1 local_438 [1056];
  ulonglong local_18;
  
  local_448 = 0xfffffffffffffffe;
  local_18 = DAT_1409707c0 ^ (ulonglong)auStack_488;
  local_460 = &local_458;
  local_468 = local_438;
  cVar1 = (**(code **)(**(longlong **)(param_1 + 0x1f0) + 0x48))
                    (*(longlong **)(param_1 + 0x1f0),0xffffffff,0xffffffff,0x418);
  if (cVar1 == '\0') {
    uVar2 = 1;
  }
  else {
    local_468 = (undefined1 *)CONCAT44(local_468._4_4_,local_458);
    cVar1 = FUN_14001e670(param_1,local_454,local_438,local_450);
    if (cVar1 == '\0') {
      FUN_14001e540(param_1,"ERROR: CMsgServerDlg::Process() ProcessMsg()");
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  return uVar2;
}

// ==== CAsyncDBThread::helper_140021f60  @140021f60  [medium:callgraph-r0]  (orig: FUN_140021f60)
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_140021f60(undefined8 param_1)

{
  int iVar1;
  DWORD DVar2;
  BOOL BVar3;
  __uint64 _Var4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar5;
  HANDLE hProcess;
  uint uVar6;
  undefined1 auStack_598 [32];
  undefined8 local_578;
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_570 [40];
  basic_string<char,std::char_traits<char>,std::allocator<char>_> local_548 [48];
  CIniFile local_518 [1024];
  char local_118 [128];
  char local_98 [127];
  undefined1 local_19;
  ulonglong local_18;
  
  local_578 = 0xfffffffffffffffe;
  local_18 = DAT_1409707c0 ^ (ulonglong)auStack_598;
  CIniFile::CIniFile(local_518,"ExtraProc.ini","Config");
  iVar1 = CIniFile::GetInt(local_518,"Count");
  uVar6 = 0;
  if (0 < iVar1) {
    do {
      uVar6 = uVar6 + 1;
      _snprintf(local_98,0x80,"Exe%d",(ulonglong)uVar6);
      local_19 = 0;
      CIniFile::SetSection(local_518,local_98);
      memset(local_118,0,0x80);
      CIniFile::GetString(local_518,local_118,"ExeName",0x80);
      std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
      basic_string<char,std::char_traits<char>,std::allocator<char>_>(local_548,local_118);
      _Var4 = std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::rfind
                        (local_548,"\\",*(__uint64 *)npos_exref,1);
      if (_Var4 != *(__uint64 *)npos_exref) {
        pbVar5 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::substr
                           (local_548,(__uint64)local_570,_Var4 + 1);
        std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::operator=
                  (local_548,pbVar5);
        std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
        ~basic_string<char,std::char_traits<char>,std::allocator<char>_>(local_570);
      }
      DVar2 = FUN_14001f4d0(param_1);
      if (DVar2 != 0) {
        hProcess = OpenProcess(0x29,0,DVar2);
        if (hProcess == (HANDLE)0x0) {
          std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
          ~basic_string<char,std::char_traits<char>,std::allocator<char>_>(local_548);
          CIniFile::~CIniFile(local_518);
          return;
        }
        BVar3 = TerminateProcess(hProcess,0);
        if (BVar3 == 0) {
          DVar2 = GetLastError();
          tq::SysLogSave("extrapro","Close exe (%s) error(%d) FALSE!",local_118,(ulonglong)DVar2);
        }
        else {
          tq::SysLogSave("extrapro","Close exe (%s) Success!",local_118);
        }
      }
      std::basic_string<char,std::char_traits<char>,std::allocator<char>_>::
      ~basic_string<char,std::char_traits<char>,std::allocator<char>_>(local_548);
    } while ((int)uVar6 < iVar1);
  }
  CIniFile::~CIniFile(local_518);
  return;
}

// ==== CAsyncDBThread::helper_1400221b0  @1400221b0  [medium:callgraph-r0]  (orig: FUN_1400221b0)
longlong FUN_1400221b0(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18)) / 0x30) <= param_2
     ) {
    log_InlineLogERROR(&DAT_1406d9c10);
  }
  if ((ulonglong)((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18)) / 0x30) <= param_2
     ) {
    _invalid_parameter_noinfo();
  }
  return param_2 * 0x30 + *(longlong *)(param_1 + 0x18);
}

// ==== CAsyncDBThread::helper_1400223a0  @1400223a0  [medium:callgraph-r3]  (orig: FUN_1400223a0)
void FUN_1400223a0(undefined8 param_1,ulonglong param_2)

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
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_140944540);
  }
  operator_new(param_2 * 8);
  return;
}

// ==== CAsyncDBThread::helper_140022d80  @140022d80  [medium:callgraph-r3]  (orig: FUN_140022d80)
void * FUN_140022d80(void *param_1,longlong param_2,longlong param_3)

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

// ==== CAsyncDBThread::helper_140023700  @140023700  [medium:callgraph-r3]  (orig: FUN_140023700)
void * FUN_140023700(undefined8 param_1,void *param_2,longlong param_3,void *param_4)

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

// ==== CAsyncDBThread::helper_140023c10  @140023c10  [medium:callgraph-r1]  (orig: FUN_140023c10)
ulonglong FUN_140023c10(longlong *param_1)

{
  ulonglong uVar1;
  longlong lVar2;
  longlong lVar3;
  
  uVar1 = param_1[4];
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  param_1 = (longlong *)*param_1;
  lVar3 = 0;
  if (param_1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar2 = lVar3;
  }
  else {
    lVar2 = *param_1;
  }
  uVar1 = uVar1 - 8;
  if (uVar1 <= *(ulonglong *)(lVar2 + 0x20)) {
    lVar2 = lVar3;
    if (param_1 != (longlong *)0x0) {
      lVar2 = *param_1;
    }
    if (*(ulonglong *)(lVar2 + 0x18) <= uVar1) goto LAB_140023c87;
  }
  _invalid_parameter_noinfo();
LAB_140023c87:
  if (param_1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  else {
    lVar3 = *param_1;
  }
  if (*(ulonglong *)(lVar3 + 0x20) <= uVar1) {
    _invalid_parameter_noinfo();
  }
  return uVar1;
}

// ==== CAsyncDBThread::helper_140023cc0  @140023cc0  [medium:callgraph-r2]  (orig: FUN_140023cc0)
void FUN_140023cc0(longlong param_1,longlong param_2,ulonglong param_3,undefined8 *param_4)

{
  void *pvVar1;
  undefined8 uVar2;
  void *_Dst;
  undefined8 uVar3;
  longlong lVar4;
  ulonglong uVar5;
  undefined8 *puVar6;
  longlong lVar7;
  rsize_t rVar8;
  ulonglong uVar9;
  ulonglong uVar10;
  undefined8 *puVar11;
  
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
                    /* WARNING: Subroutine does not return */
      FUN_14001f810();
    }
    uVar10 = param_3 + lVar4;
    if (uVar5 < uVar10) {
      if (uVar5 <= 0x1fffffffffffffff - (uVar5 >> 1)) {
        uVar9 = uVar5 + (uVar5 >> 1);
      }
      if (uVar9 < uVar10) {
        uVar9 = uVar10;
      }
      _Dst = (void *)FUN_1400223a0(param_1 + 0x10,uVar9);
      lVar4 = *(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18) >> 3;
      puVar6 = (undefined8 *)((longlong)_Dst + lVar4 * 8);
      for (uVar5 = param_3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *puVar6 = *param_4;
        puVar6 = puVar6 + 1;
      }
      lVar7 = *(longlong *)(param_2 + 8) - (longlong)*(void **)(param_1 + 0x18) >> 3;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 3;
        memmove_s(_Dst,rVar8,*(void **)(param_1 + 0x18),rVar8);
      }
      lVar7 = *(longlong *)(param_1 + 0x20) - (longlong)*(void **)(param_2 + 8) >> 3;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 3;
        memmove_s((void *)((longlong)_Dst + (lVar4 + param_3) * 8),rVar8,*(void **)(param_2 + 8),
                  rVar8);
      }
      pvVar1 = *(void **)(param_1 + 0x18);
      lVar4 = *(longlong *)(param_1 + 0x20);
      if (pvVar1 != (void *)0x0) {
        operator_delete(pvVar1);
      }
      *(void **)(param_1 + 0x28) = (void *)((longlong)_Dst + uVar9 * 8);
      *(void **)(param_1 + 0x20) =
           (void *)((longlong)_Dst + (param_3 + (lVar4 - (longlong)pvVar1 >> 3)) * 8);
      *(void **)(param_1 + 0x18) = _Dst;
    }
    else if ((ulonglong)(lVar7 - *(longlong *)(param_2 + 8) >> 3) < param_3) {
      uVar2 = *param_4;
      FUN_140023700(param_1,*(longlong *)(param_2 + 8),lVar7,
                    *(longlong *)(param_2 + 8) + param_3 * 8);
      puVar6 = *(undefined8 **)(param_1 + 0x20);
      for (lVar4 = param_3 - ((longlong)puVar6 - *(longlong *)(param_2 + 8) >> 3); lVar4 != 0;
          lVar4 = lVar4 + -1) {
        *puVar6 = uVar2;
        puVar6 = puVar6 + 1;
      }
      *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + param_3 * 8;
      lVar4 = *(longlong *)(param_1 + 0x20);
      for (puVar6 = *(undefined8 **)(param_2 + 8); puVar6 != (undefined8 *)(lVar4 + param_3 * -8);
          puVar6 = puVar6 + 1) {
        *puVar6 = uVar2;
      }
    }
    else {
      uVar2 = *param_4;
      lVar4 = lVar7 + param_3 * -8;
      uVar3 = FUN_140023700(param_1,lVar4,lVar7,lVar7);
      *(undefined8 *)(param_1 + 0x20) = uVar3;
      FUN_140022d80(*(undefined8 *)(param_2 + 8),lVar4,lVar7);
      puVar11 = *(undefined8 **)(param_2 + 8);
      puVar6 = puVar11 + param_3;
      for (; puVar11 != puVar6; puVar11 = puVar11 + 1) {
        *puVar11 = uVar2;
      }
    }
  }
  return;
}

// ==== CAsyncDBThread::helper_140024200  @140024200  [medium:callgraph-r0]  (orig: FUN_140024200)
undefined8 FUN_140024200(longlong param_1)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  
  if ((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18) & 0xfffffffffffffff8U) == 0) {
    log_InlineLogERROR(&DAT_1406d9c10);
    return 0;
  }
  puVar2 = (undefined8 *)FUN_140023c10();
  uVar1 = *puVar2;
  if ((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18) & 0xfffffffffffffff8U) != 0) {
    *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + -8;
  }
  return uVar1;
}

// ==== CAsyncDBThread::helper_140024280  @140024280  [medium:callgraph-r1]  (orig: FUN_140024280)
longlong * FUN_140024280(longlong *param_1,longlong *param_2,longlong *param_3,undefined8 param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  longlong *local_28;
  ulonglong uStack_20;
  
  lVar2 = 0;
  uVar1 = param_1[3];
  lVar3 = lVar2;
  if ((param_1[4] - uVar1 & 0xfffffffffffffff8) != 0) {
    if ((ulonglong)param_1[4] < uVar1) {
      _invalid_parameter_noinfo();
    }
    if ((*param_3 == 0) || (*param_3 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    lVar3 = (longlong)(param_3[1] - uVar1) >> 3;
  }
  local_28 = (longlong *)*param_3;
  uStack_20 = param_3[1];
  FUN_140023cc0(param_1,&local_28,1,param_4);
  uVar1 = param_1[3];
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  param_1 = (longlong *)*param_1;
  local_28 = param_1;
  uStack_20 = uVar1;
  if (param_1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar4 = lVar2;
  }
  else {
    lVar4 = *param_1;
  }
  uVar1 = uVar1 + lVar3 * 8;
  if (uVar1 <= *(ulonglong *)(lVar4 + 0x20)) {
    if (param_1 != (longlong *)0x0) {
      lVar2 = *param_1;
    }
    if (*(ulonglong *)(lVar2 + 0x18) <= uVar1) goto LAB_140024374;
  }
  _invalid_parameter_noinfo();
LAB_140024374:
  *param_2 = (longlong)local_28;
  param_2[1] = uVar1;
  return param_2;
}

// ==== CAsyncDBThread::helper_140024590  @140024590  [medium:callgraph-r0]  (orig: FUN_140024590)
void FUN_140024590(undefined8 *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  ulonglong uVar3;
  undefined8 local_28;
  undefined8 *puStack_20;
  undefined1 local_18 [16];
  
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
    param_1[4] = puVar2 + 1;
    return;
  }
  if (puVar2 < puVar1) {
    _invalid_parameter_noinfo();
  }
  local_28 = *param_1;
  puStack_20 = puVar2;
  FUN_140024280(param_1,local_18,&local_28,param_2);
  return;
}

// ==== CAsyncDBThread::ctor_or_dtor  @140024860  [high:vtable-assign]  (orig: FUN_140024860)
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_140024860(CDialog *param_1,longlong param_2)

{
  CDialog CVar1;
  bool bVar2;
  char cVar3;
  DWORD DVar4;
  ulong uVar5;
  __time32_t _Var6;
  int iVar7;
  undefined8 uVar8;
  AFX_MODULE_STATE *pAVar9;
  FILE *_File;
  char *pcVar10;
  HANDLE pvVar11;
  CThreadBase *pCVar12;
  CAsyncDBThread *this;
  CAsyncDBThread *pCVar13;
  undefined8 *puVar14;
  void *pvVar15;
  longlong lVar16;
  CDialog *pCVar17;
  ulonglong uVar18;
  uint uVar19;
  CThreadBase *pCVar20;
  undefined1 auStackY_5d8 [32];
  CDialog *local_518;
  CAsyncDBThread *local_510;
  ulonglong local_508;
  undefined8 local_500;
  char local_4f8 [8];
  char local_4f0;
  char local_4e8 [8];
  char local_4e0 [2];
  char local_4de;
  char local_4d8 [32];
  undefined1 local_4b8;
  char local_4b7 [127];
  char local_438;
  undefined1 local_437 [1023];
  ulonglong local_38;
  
  local_500 = 0xfffffffffffffffe;
  local_38 = DAT_1409707c0 ^ (ulonglong)auStackY_5d8;
  local_518 = param_1;
  if ((DAT_140975940 == 0) &&
     (DVar4 = WaitForSingleObject(*(HANDLE *)(param_1 + 0x208),0x14), DVar4 == 0)) {
    DAT_140975940 = 1;
    local_4f8[0] = s_shutdown_1406e3cf8[0];
    local_4f8[1] = s_shutdown_1406e3cf8[1];
    local_4f8[2] = s_shutdown_1406e3cf8[2];
    local_4f8[3] = s_shutdown_1406e3cf8[3];
    local_4f8[4] = s_shutdown_1406e3cf8[4];
    local_4f8[5] = s_shutdown_1406e3cf8[5];
    local_4f8[6] = s_shutdown_1406e3cf8[6];
    local_4f8[7] = s_shutdown_1406e3cf8[7];
    local_4f0 = s_shutdown_1406e3cf8[8];
    lVar16 = -1;
    pcVar10 = local_4f8;
    do {
      if (lVar16 == 0) break;
      lVar16 = lVar16 + -1;
      cVar3 = *pcVar10;
      pcVar10 = pcVar10 + 1;
    } while (cVar3 != '\0');
    (**(code **)(**(longlong **)(param_1 + 0x1f0) + 0x50))(*(longlong **)(param_1 + 0x1f0),2);
    *(undefined4 *)(param_1 + 0x210) = 0x32;
    uVar5 = tq::TimeGet(0);
    *(uint *)(param_1 + 0x214) = uVar5 / 1000;
  }
  else if ((*(int *)(param_1 + 0x214) == 0) ||
          (uVar5 = tq::TimeGet(0),
          uVar5 / 1000 < (uint)(*(int *)(param_1 + 0x210) + *(int *)(param_1 + 0x214)))) {
    if ((*(int *)(param_1 + 0x21c) != 0) &&
       (uVar5 = tq::TimeGet(0),
       (uint)(*(int *)(param_1 + 0x21c) + *(int *)(param_1 + 0x218)) <= uVar5 / 1000)) {
      *(undefined4 *)(param_1 + 0x21c) = 0;
      *(undefined4 *)(param_1 + 0x218) = 0;
      *(undefined4 *)(param_1 + 0x1fc) = 3;
      FUN_14001e540();
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x214) = 0;
    *(undefined4 *)(param_1 + 0x210) = 0;
    local_4e8[0] = s_kickoutall_1406e3ce8[0];
    local_4e8[1] = s_kickoutall_1406e3ce8[1];
    local_4e8[2] = s_kickoutall_1406e3ce8[2];
    local_4e8[3] = s_kickoutall_1406e3ce8[3];
    local_4e8[4] = s_kickoutall_1406e3ce8[4];
    local_4e8[5] = s_kickoutall_1406e3ce8[5];
    local_4e8[6] = s_kickoutall_1406e3ce8[6];
    local_4e8[7] = s_kickoutall_1406e3ce8[7];
    local_4e0[0] = s_kickoutall_1406e3ce8[8];
    local_4e0[1] = s_kickoutall_1406e3ce8[9];
    local_4de = s_kickoutall_1406e3ce8[10];
    lVar16 = -1;
    pcVar10 = local_4e8;
    do {
      if (lVar16 == 0) break;
      lVar16 = lVar16 + -1;
      cVar3 = *pcVar10;
      pcVar10 = pcVar10 + 1;
    } while (cVar3 != '\0');
    (**(code **)(**(longlong **)(param_1 + 0x1f0) + 0x50))(*(longlong **)(param_1 + 0x1f0),2);
    *(undefined4 *)(param_1 + 0x218) = 10;
    uVar5 = tq::TimeGet(0);
    *(uint *)(param_1 + 0x21c) = uVar5 / 1000;
  }
  pCVar20 = (CThreadBase *)0x0;
  if (param_2 == 1) {
    if (0 < DAT_14097593c) goto LAB_140026a28;
    DAT_14097593c = DAT_14097593c + 1;
    uVar8 = FUN_140028960();
    FUN_14002adc0(uVar8);
    if (*(longlong *)(param_1 + 0x1f0) != 0) {
      FUN_140021bd0(param_1);
    }
    iVar7 = *(int *)(param_1 + 0x1fc);
    if (iVar7 == 0) {
      *(undefined4 *)(param_1 + 0x1fc) = 4;
    }
    else if (iVar7 == 1) {
      *(undefined4 *)(param_1 + 0x1fc) = 3;
      pvVar11 = GetCurrentThread();
      CThreadTimesInfo::AddThreadHandle((CThreadTimesInfo *)(param_1 + 0x168),pvVar11);
      FUN_14001e720(param_1);
      local_510 = operator_new(0xd0);
      pCVar12 = pCVar20;
      if (local_510 != (CAsyncDBThread *)0x0) {
        FUN_14050c340(7);
        pCVar12 = (CThreadBase *)FUN_14001b100();
      }
      *(CThreadBase **)(param_1 + 0x178) = pCVar12;
      if ((pCVar12 != (CThreadBase *)0x0) && (cVar3 = FUN_14001b1b0(), cVar3 != '\0')) {
        pvVar15 = CThreadBase::GetThreadHandle(*(CThreadBase **)(param_1 + 0x178));
        CThreadTimesInfo::AddThreadHandle((CThreadTimesInfo *)(param_1 + 0x168),pvVar15);
        tq::SetLogThreadStatus(1);
        cVar3 = DatabaseInit();
        if (cVar3 != '\0') {
          this = operator_new(0x40);
          pCVar13 = (CAsyncDBThread *)pCVar20;
          local_510 = this;
          if (this != (CAsyncDBThread *)0x0) {
            CAsyncDBThread::CAsyncDBThread(this);
            *(undefined ***)this = CAsyncDBThread::vftable;
            pCVar13 = this;
          }
          *(CAsyncDBThread **)(param_1 + 0x180) = pCVar13;
          if ((pCVar13 != (CAsyncDBThread *)0x0) &&
             (bVar2 = CThreadBase::CreateThread((CThreadBase *)pCVar13,"AsyncDBThread",true), bVar2)
             ) {
            pvVar15 = CThreadBase::GetThreadHandle(*(CThreadBase **)(param_1 + 0x180));
            CThreadTimesInfo::AddThreadHandle((CThreadTimesInfo *)(param_1 + 0x168),pvVar15);
            FUN_14001e540(param_1);
            local_510 = operator_new(0x50);
            pCVar12 = pCVar20;
            if (local_510 != (CAsyncDBThread *)0x0) {
              FUN_14050c340(2);
              pCVar12 = (CThreadBase *)FUN_14002e7e0();
            }
            *(CThreadBase **)(param_1 + 0x1c0) = pCVar12;
            if ((pCVar12 != (CThreadBase *)0x0) && (cVar3 = FUN_14002e860(), cVar3 != '\0')) {
              pvVar15 = CThreadBase::GetThreadHandle(*(CThreadBase **)(param_1 + 0x1c0));
              CThreadTimesInfo::AddThreadHandle((CThreadTimesInfo *)(param_1 + 0x168),pvVar15);
              FUN_14001e540(param_1);
              pCVar13 = operator_new(0x50);
              pCVar12 = pCVar20;
              local_510 = pCVar13;
              if (pCVar13 != (CAsyncDBThread *)0x0) {
                FUN_14050c340(10);
                pCVar12 = (CThreadBase *)FUN_1400f3060(pCVar13);
              }
              *(CThreadBase **)(param_1 + 0x1e0) = pCVar12;
              if ((pCVar12 != (CThreadBase *)0x0) &&
                 (cVar3 = (**(code **)(*(longlong *)pCVar12 + 0x20))(), cVar3 != '\0')) {
                pvVar15 = CThreadBase::GetThreadHandle(*(CThreadBase **)(param_1 + 0x1e0));
                CThreadTimesInfo::AddThreadHandle((CThreadTimesInfo *)(param_1 + 0x168),pvVar15);
                FUN_14001e540(param_1,"Init OK.");
                FUN_14001e540(param_1);
                pCVar12 = pCVar20;
                if (0 < DAT_1409757d0) {
                  do {
                    local_510 = operator_new(0x58);
                    iVar7 = (int)pCVar12;
                    pCVar12 = pCVar20;
                    if (local_510 != (void *)0x0) {
                      FUN_14050c340(iVar7 + 0xe);
                      pCVar12 = (CThreadBase *)FUN_14001d2d0();
                    }
                    local_510 = (CAsyncDBThread *)pCVar12;
                    if (pCVar12 == (CThreadBase *)0x0) {
LAB_140025f61:
                      if (iVar7 < DAT_1409757d0) goto LAB_140026533;
                      break;
                    }
                    FUN_140024590(param_1 + 0x188);
                    cVar3 = (**(code **)(*(longlong *)pCVar12 + 0x20))();
                    if (cVar3 == '\0') goto LAB_140025f61;
                    pvVar15 = CThreadBase::GetThreadHandle(pCVar12);
                    CThreadTimesInfo::AddThreadHandle((CThreadTimesInfo *)(param_1 + 0x168),pvVar15)
                    ;
                    pCVar12 = (CThreadBase *)(ulonglong)(iVar7 + 1U);
                  } while ((int)(iVar7 + 1U) < DAT_1409757d0);
                }
                FUN_14001e540(param_1);
                local_510 = operator_new(0x50);
                pCVar12 = pCVar20;
                if (local_510 != (CAsyncDBThread *)0x0) {
                  FUN_14050c340(4);
                  pCVar12 = (CThreadBase *)FUN_14002e3d0();
                }
                *(CThreadBase **)(param_1 + 0x1c8) = pCVar12;
                if ((pCVar12 != (CThreadBase *)0x0) && (cVar3 = FUN_14002e450(), cVar3 != '\0')) {
                  pvVar15 = CThreadBase::GetThreadHandle(*(CThreadBase **)(param_1 + 0x1c8));
                  CThreadTimesInfo::AddThreadHandle((CThreadTimesInfo *)(param_1 + 0x168),pvVar15);
                  FUN_14001e540(param_1);
                  pCVar13 = operator_new(0x58);
                  pCVar12 = pCVar20;
                  local_510 = pCVar13;
                  if (pCVar13 != (CAsyncDBThread *)0x0) {
                    FUN_14050c340(0xe);
                    FUN_14050c340(1);
                    pCVar12 = (CThreadBase *)FUN_14002bb50(pCVar13);
                  }
                  *(CThreadBase **)(param_1 + 0x1b8) = pCVar12;
                  if ((pCVar12 != (CThreadBase *)0x0) &&
                     (cVar3 = (**(code **)(*(longlong *)pCVar12 + 0x20))(), cVar3 != '\0')) {
                    pvVar15 = CThreadBase::GetThreadHandle(*(CThreadBase **)(param_1 + 0x1b8));
                    CThreadTimesInfo::AddThreadHandle((CThreadTimesInfo *)(param_1 + 0x168),pvVar15)
                    ;
                    FUN_14001e540(param_1,&DAT_1406e3248);
                    if (param_1[0x1d0] != (CDialog)0x0) {
                      FUN_14001e540(param_1);
                      pCVar13 = operator_new(0x68);
                      pCVar12 = pCVar20;
                      local_510 = pCVar13;
                      if (pCVar13 != (CAsyncDBThread *)0x0) {
                        FUN_14050c340(6);
                        pCVar12 = (CThreadBase *)FUN_14004c0a0(pCVar13);
                      }
                      *(CThreadBase **)(param_1 + 0x1d8) = pCVar12;
                      if ((pCVar12 == (CThreadBase *)0x0) ||
                         (cVar3 = (**(code **)(*(longlong *)pCVar12 + 0x20))(), cVar3 == '\0'))
                      goto LAB_140026533;
                      pvVar15 = CThreadBase::GetThreadHandle(*(CThreadBase **)(param_1 + 0x1d8));
                      CThreadTimesInfo::AddThreadHandle
                                ((CThreadTimesInfo *)(param_1 + 0x168),pvVar15);
                      FUN_14001e540(param_1,&DAT_1406e3248);
                    }
                    FUN_14001e540(param_1);
                    local_510 = operator_new(0x50);
                    pCVar12 = pCVar20;
                    if (local_510 != (CAsyncDBThread *)0x0) {
                      FUN_14050c340(8);
                      pCVar12 = (CThreadBase *)FUN_140001000();
                    }
                    *(CThreadBase **)(param_1 + 0x1e8) = pCVar12;
                    if ((pCVar12 != (CThreadBase *)0x0) && (cVar3 = FUN_140001080(), cVar3 != '\0'))
                    {
                      pvVar15 = CThreadBase::GetThreadHandle(*(CThreadBase **)(param_1 + 0x1e8));
                      CThreadTimesInfo::AddThreadHandle
                                ((CThreadTimesInfo *)(param_1 + 0x168),pvVar15);
                      FUN_14001e540(param_1,"Init OK.");
                      if (param_1[0x220] != (CDialog)0x0) {
                        FUN_14001e540(param_1);
                        pCVar13 = operator_new(0x50);
                        pCVar12 = pCVar20;
                        local_510 = pCVar13;
                        if (pCVar13 != (CAsyncDBThread *)0x0) {
                          FUN_14050c340(9);
                          pCVar12 = (CThreadBase *)FUN_14050ff20(pCVar13);
                        }
                        *(CThreadBase **)(param_1 + 0x228) = pCVar12;
                        if ((pCVar12 == (CThreadBase *)0x0) ||
                           (cVar3 = (**(code **)(*(longlong *)pCVar12 + 0x20))(), cVar3 == '\0'))
                        goto LAB_140026533;
                        pvVar15 = CThreadBase::GetThreadHandle(*(CThreadBase **)(param_1 + 0x228));
                        CThreadTimesInfo::AddThreadHandle
                                  ((CThreadTimesInfo *)(param_1 + 0x168),pvVar15);
                        FUN_14001e540(param_1,&DAT_1406e3248);
                      }
                      if (param_1[0x221] != (CDialog)0x0) {
                        FUN_14001e540(param_1);
                        pCVar13 = operator_new(0xb0);
                        pCVar12 = pCVar20;
                        local_510 = pCVar13;
                        if (pCVar13 != (CAsyncDBThread *)0x0) {
                          FUN_14050c340(0xb);
                          pCVar12 = (CThreadBase *)FUN_1400319c0(pCVar13);
                        }
                        *(CThreadBase **)(param_1 + 0x238) = pCVar12;
                        if ((pCVar12 == (CThreadBase *)0x0) ||
                           (cVar3 = (**(code **)(*(longlong *)pCVar12 + 0x20))(), cVar3 == '\0'))
                        goto LAB_140026533;
                        pvVar15 = CThreadBase::GetThreadHandle(*(CThreadBase **)(param_1 + 0x238));
                        CThreadTimesInfo::AddThreadHandle
                                  ((CThreadTimesInfo *)(param_1 + 0x168),pvVar15);
                        FUN_14001e540(param_1,&DAT_1406e31a8);
                      }
                      if (param_1[0x222] != (CDialog)0x0) {
                        FUN_14001e540(param_1);
                        pCVar13 = operator_new(0x8d8);
                        pCVar12 = pCVar20;
                        local_510 = pCVar13;
                        if (pCVar13 != (CAsyncDBThread *)0x0) {
                          FUN_14050c340(0xd);
                          pCVar12 = (CThreadBase *)FUN_140019520(pCVar13);
                        }
                        *(CThreadBase **)(param_1 + 0x230) = pCVar12;
                        if ((pCVar12 == (CThreadBase *)0x0) ||
                           (cVar3 = (**(code **)(*(longlong *)pCVar12 + 0x20))(), cVar3 == '\0'))
                        goto LAB_140026533;
                        pvVar15 = CThreadBase::GetThreadHandle(*(CThreadBase **)(param_1 + 0x230));
                        CThreadTimesInfo::AddThreadHandle
                                  ((CThreadTimesInfo *)(param_1 + 0x168),pvVar15);
                        FUN_14001e540(param_1,&DAT_1406e3248);
                      }
                      CThreadBase::ResumeThread(*(CThreadBase **)(param_1 + 0x1c0));
                      CThreadBase::ResumeThread(*(CThreadBase **)(param_1 + 0x1e0));
                      if (0 < DAT_1409757d0) {
                        do {
                          puVar14 = (undefined8 *)
                                    FUN_14001f5b0(param_1 + 0x188,(longlong)(int)pCVar20);
                          CThreadBase::ResumeThread((CThreadBase *)*puVar14);
                          uVar19 = (int)pCVar20 + 1;
                          pCVar20 = (CThreadBase *)(ulonglong)uVar19;
                        } while ((int)uVar19 < DAT_1409757d0);
                      }
                      CThreadBase::ResumeThread(*(CThreadBase **)(param_1 + 0x1b8));
                      CThreadBase::ResumeThread(*(CThreadBase **)(param_1 + 0x1c8));
                      CThreadBase::ResumeThread(*(CThreadBase **)(param_1 + 0x1e8));
                      if (*(CThreadBase **)(param_1 + 0x1d8) != (CThreadBase *)0x0) {
                        CThreadBase::ResumeThread(*(CThreadBase **)(param_1 + 0x1d8));
                      }
                      if (*(CThreadBase **)(param_1 + 0x228) != (CThreadBase *)0x0) {
                        CThreadBase::ResumeThread(*(CThreadBase **)(param_1 + 0x228));
                      }
                      if (*(CThreadBase **)(param_1 + 0x238) != (CThreadBase *)0x0) {
                        CThreadBase::ResumeThread(*(CThreadBase **)(param_1 + 0x238));
                      }
                      if (*(CThreadBase **)(param_1 + 0x230) != (CThreadBase *)0x0) {
                        CThreadBase::ResumeThread(*(CThreadBase **)(param_1 + 0x230));
                      }
                      FUN_14001e540(param_1,&DAT_1406e3160);
                      *(undefined4 *)(param_1 + 0x1fc) = 2;
                      uVar8 = FUN_140028960();
                      pvVar15 = (void *)FUN_14002ba80(uVar8);
                      if (pvVar15 != (void *)0x0) {
                        CThreadTimesInfo::AddThreadHandle
                                  ((CThreadTimesInfo *)(param_1 + 0x168),pvVar15);
                      }
                      uVar8 = FUN_1400018c0();
                      pvVar15 = (void *)FUN_140005550(uVar8);
                      if (pvVar15 != (void *)0x0) {
                        CThreadTimesInfo::AddThreadHandle
                                  ((CThreadTimesInfo *)(param_1 + 0x168),pvVar15);
                      }
                      CPerformanceInfo::Init((CPerformanceInfo *)(param_1 + 0x158),"syslog/process")
                      ;
                      CThreadTimesInfo::Init((CThreadTimesInfo *)(param_1 + 0x168));
                      *(undefined4 *)(param_1 + 0x144) = 600;
                      uVar5 = tq::TimeGet(0);
                      *(uint *)(param_1 + 0x148) = uVar5 / 1000;
                      *(undefined4 *)(param_1 + 0x14c) = 300;
                      uVar5 = tq::TimeGet(0);
                      *(uint *)(param_1 + 0x150) = uVar5 / 1000;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    else if (iVar7 == 2) {
      cVar3 = FUN_1400149a0(param_1 + 0x144);
      if (cVar3 != '\0') {
        CPerformanceInfo::RecrodPerformanceInfo((CPerformanceInfo *)(param_1 + 0x158));
        CThreadTimesInfo::RecordThreadTimesInfo((CThreadTimesInfo *)(param_1 + 0x168),true);
        CMyHeapMgr::SaveLog((CMyHeapMgr *)g_MyHeapMgr_exref);
      }
      cVar3 = FUN_1400149a0(param_1 + 0x14c);
      if (cVar3 != '\0') {
        FUN_14001f070(param_1);
      }
      cVar3 = FUN_1400222e0(param_1 + 0x134,300);
      if (cVar3 != '\0') {
        LOCK();
        DAT_1409756f8 = 0;
        UNLOCK();
        LOCK();
        DAT_1409756fc = 0;
        UNLOCK();
        LOCK();
        DAT_140975714 = 0;
        UNLOCK();
        LOCK();
        DAT_140975718 = 0;
        UNLOCK();
        LOCK();
        DAT_140975730 = 0;
        UNLOCK();
        LOCK();
        DAT_140975734 = 0;
        UNLOCK();
        LOCK();
        DAT_140975744 = 0;
        UNLOCK();
        LOCK();
        DAT_140975740 = 0;
        UNLOCK();
        log_InlineLogMessage
                  ("-----------------------------------------------\n%s%s-----------------------------------------------\n"
                   ,*(undefined8 *)(param_1 + 0xf8),*(undefined8 *)(param_1 + 0xe8));
        log_InlineLogMessage
                  ("\n-----------------------------------------------\nclient socket send bytes: %d\nclient socket send Msgs: %d\nclient socket recv bytes: %d\nclient socket recv Msgs: %d\n-----------------------------\nNpc socket send bytes: %d\nNpc socket send Msgs: %d\nNpc socket recv bytes: %d\nNpc socket recv Msgs: %d\n-----------------------------\nAccount socket send bytes: %d\nAccount socket send Msgs: %d\nAccount socket recv bytes: %d\nAccount socket recv Msgs: %d\n-----------------------------------------------\n"
                   ,(ulonglong)DAT_140975788);
        LOCK();
        DAT_140975788 = 0;
        UNLOCK();
        LOCK();
        DAT_14097578c = 0;
        UNLOCK();
        LOCK();
        DAT_140975790 = 0;
        UNLOCK();
        LOCK();
        DAT_140975794 = 0;
        UNLOCK();
        LOCK();
        DAT_140975798 = 0;
        UNLOCK();
        LOCK();
        DAT_14097579c = 0;
        UNLOCK();
        LOCK();
        DAT_1409757a0 = 0;
        UNLOCK();
        LOCK();
        DAT_1409757a4 = 0;
        UNLOCK();
        LOCK();
        DAT_1409757a8 = 0;
        UNLOCK();
        LOCK();
        DAT_1409757ac = 0;
        UNLOCK();
        LOCK();
        DAT_1409757b0 = 0;
        UNLOCK();
        LOCK();
        DAT_1409757b4 = 0;
        UNLOCK();
      }
      if ((DAT_1409756f0 - DAT_1409756f4 < 10) && (-10 < DAT_1409756f0 - DAT_1409756f4)) {
        if (DAT_1409756f4 == 0) {
          if (DAT_1409756f0 != 0) goto LAB_140025599;
        }
        else if (DAT_1409756f0 == 0) goto LAB_140025599;
      }
      else {
LAB_140025599:
        log_InlineLogMessage("CCU:%d, PCU:%d, login:%d, logout:%d");
        LOCK();
        DAT_140975700 = 0;
        UNLOCK();
        LOCK();
        DAT_140975704 = 0;
        UNLOCK();
        LOCK();
        DAT_1409756f4 = DAT_1409756f0;
        UNLOCK();
      }
      uVar19 = DAT_14097570c - DAT_140975710 >> 0x1f;
      if ((int)((DAT_14097570c - DAT_140975710 ^ uVar19) - uVar19) < 10) {
        if (DAT_140975710 == 0) {
          if (DAT_14097570c != 0) goto LAB_140025604;
        }
        else if (DAT_14097570c == 0) goto LAB_140025604;
      }
      else {
LAB_140025604:
        log_InlineLogMessage("FromOSCCU:%d, PCU:%d, in:%d, back:%d",(ulonglong)(uint)DAT_14097570c);
        LOCK();
        DAT_14097571c = 0;
        UNLOCK();
        LOCK();
        DAT_140975720 = 0;
        UNLOCK();
        LOCK();
        DAT_140975710 = DAT_14097570c;
        UNLOCK();
      }
      uVar19 = DAT_140975728 - DAT_14097572c >> 0x1f;
      if ((int)((DAT_140975728 - DAT_14097572c ^ uVar19) - uVar19) < 10) {
        if (DAT_14097572c == 0) {
          if (DAT_140975728 != 0) goto LAB_140025671;
        }
        else if (DAT_140975728 == 0) goto LAB_140025671;
      }
      else {
LAB_140025671:
        log_InlineLogMessage("ToOSCCU:%d, PCU:%d, out:%d, back:%d",(ulonglong)(uint)DAT_140975728);
        LOCK();
        DAT_140975738 = 0;
        UNLOCK();
        LOCK();
        DAT_14097573c = 0;
        UNLOCK();
        LOCK();
        DAT_14097572c = DAT_140975728;
        UNLOCK();
      }
      cVar3 = FUN_1400222e0();
      if (cVar3 != '\0') {
        _Var6 = _time32((__time32_t *)0x0);
        tq::DateTime(local_4d8,(longlong)_Var6);
        ATL::CStringT<char,StrTraitMFC_DLL<char,ATL::ChTraitsCRT<char>_>_>::Format
                  ((CStringT<char,StrTraitMFC_DLL<char,ATL::ChTraitsCRT<char>_>_> *)(param_1 + 0xf0)
                   ,
                   "start server: %s\ncurrent: %s\n\nsocket thread: %3d(max:%ld)\nworld thread:  %3d(max:%ld)\nmap group 0 thread: %3d(max:%ld)\nmap group 1 thread: %3d(max:%ld)\nmap group 2 thread: %3d(max:%ld)\nmap group 3 thread: %3d(max:%ld)\nmap group 4 thread: %3d(max:%ld)\ndebug [%ld][%ld][%ld][%ld][%ld]\n"
                   ,param_1 + 0x120,local_4d8);
        if (DAT_1409756a0 != 0) {
          pCVar20 = (CThreadBase *)((longlong)DAT_14097569c / (longlong)DAT_1409756a0 & 0xffffffff);
        }
        ATL::CStringT<char,StrTraitMFC_DLL<char,ATL::ChTraitsCRT<char>_>_>::Format
                  ((CStringT<char,StrTraitMFC_DLL<char,ATL::ChTraitsCRT<char>_>_> *)(param_1 + 0xf8)
                   ,
                   "current: %s\nsocket thread: %3d(max:%ld)\nworld thread:  %3d(max:%ld)\nmap group 0 thread: %3d(max:%ld)\ndebug [%ld][%ld][%ld][%ld][%ld]\n"
                   ,local_4d8,pCVar20);
        MaxPlayerGet();
        ATL::CStringT<char,StrTraitMFC_DLL<char,ATL::ChTraitsCRT<char>_>_>::Format
                  ((CStringT<char,StrTraitMFC_DLL<char,ATL::ChTraitsCRT<char>_>_> *)(param_1 + 0xe8)
                   ,
                   "players: %3ld(max:%ld, limit:%u)\nlogin: %ld/5min, logout: %ld/5min\nFrom OS players: %3ld(max:%ld)\nFrom OS in: %ld, back: %ld\nTo OS players: %3ld(max:%ld)\nTo OS out: %ld, back: %ld\nclose socket: %ld/5min, AveMsg: %d/5min\nsocket bytes: %3d/s (pps: %d)\nnpc socket bytes: %3d/s (pps: %d)\naccount socket bytes: %3d/s (pps: %d)\n"
                  );
        LOCK();
        DAT_140975748 = 0;
        UNLOCK();
        LOCK();
        DAT_14097574c = 0;
        UNLOCK();
        LOCK();
        DAT_140975750 = 0;
        UNLOCK();
        LOCK();
        DAT_140975754 = 0;
        UNLOCK();
        LOCK();
        DAT_140975758 = 0;
        UNLOCK();
        LOCK();
        DAT_14097575c = 0;
        UNLOCK();
        CWnd::UpdateData((CWnd *)param_1,0);
        _File = fopen("Game server online.txt","wt");
        if (_File != (FILE *)0x0) {
          pcVar10 = ATL::CSimpleStringT<char,1>::operator_char_const____ptr64
                              ((CSimpleStringT<char,1> *)(param_1 + 0xf0));
          fprintf(_File,pcVar10);
          fprintf(_File,"\n\n");
          pcVar10 = ATL::CSimpleStringT<char,1>::operator_char_const____ptr64
                              ((CSimpleStringT<char,1> *)(param_1 + 0xe8));
          fprintf(_File,pcVar10);
          fclose(_File);
        }
      }
      iVar7 = FUN_14050c390();
      if ((10000 < iVar7) && (iVar7 == (iVar7 / 1000) * 1000)) {
        FUN_14001e540(param_1,"Message pipe block, server may be slowly!!!");
        log_InlineLogERROR("dump all call stack:");
        tq::CMySingleLock::CMySingleLock((CMySingleLock *)&local_508,(ILockObj *)m_xDump_exref);
        lVar16 = FUN_1400221b0(g_setDeadLoop_exref);
        uVar18 = *(longlong *)(lVar16 + 0x20) - *(longlong *)(lVar16 + 0x18);
        while ((uVar18 & 0xfffffffffffffff8) != 0) {
          uVar8 = FUN_1400221b0(g_setDeadLoop_exref,0xe);
          uVar8 = FUN_140024200(uVar8);
          log_InlineLogERROR("* %s",uVar8);
          lVar16 = FUN_1400221b0(g_setDeadLoop_exref);
          uVar18 = *(longlong *)(lVar16 + 0x20) - *(longlong *)(lVar16 + 0x18);
        }
        tq::CMySingleLock::~CMySingleLock((CMySingleLock *)&local_508);
      }
      if (DAT_1409758f0 != 0) {
        *(undefined4 *)(param_1 + 0x1fc) = 3;
      }
    }
    else if (iVar7 == 3) {
      FUN_14001e540(param_1,"Kernel closing...");
      CThreadTimesInfo::RecordThreadTimesInfo((CThreadTimesInfo *)(param_1 + 0x168),true);
      uVar8 = FUN_14002e300();
      FUN_14002c6f0(uVar8);
      if (*(CThreadBase **)(param_1 + 0x228) != (CThreadBase *)0x0) {
        CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x228),2000);
      }
      if (*(CThreadBase **)(param_1 + 0x230) != (CThreadBase *)0x0) {
        CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x230),3000);
      }
      if (*(CThreadBase **)(param_1 + 0x238) != (CThreadBase *)0x0) {
        CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x238),4000);
      }
      if (*(CThreadBase **)(param_1 + 0x1b8) != (CThreadBase *)0x0) {
        CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x1b8),10000);
      }
      if (*(CThreadBase **)(param_1 + 0x1c8) != (CThreadBase *)0x0) {
        CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x1c8),120000);
      }
      if (*(CThreadBase **)(param_1 + 0x1e0) != (CThreadBase *)0x0) {
        CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x1e0),3000);
      }
      if (*(longlong *)(param_1 + 0x1a8) - *(longlong *)(param_1 + 0x1a0) >> 3 != 0) {
        do {
          if ((CThreadBase *)(*(longlong *)(param_1 + 0x1a8) - *(longlong *)(param_1 + 0x1a0) >> 3)
              <= pCVar20) {
            _invalid_parameter_noinfo();
          }
          CThreadBase::CloseThread
                    (*(CThreadBase **)(*(longlong *)(param_1 + 0x1a0) + (longlong)pCVar20 * 8),60000
                    );
          pCVar20 = pCVar20 + 1;
        } while (pCVar20 < (CThreadBase *)
                           (*(longlong *)(param_1 + 0x1a8) - *(longlong *)(param_1 + 0x1a0) >> 3));
      }
      if (*(CThreadBase **)(param_1 + 0x1d8) != (CThreadBase *)0x0) {
        CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x1d8),8000);
      }
      if (*(CThreadBase **)(param_1 + 0x1c0) != (CThreadBase *)0x0) {
        CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x1c0),4000);
      }
      if (*(CThreadBase **)(param_1 + 0x228) != (CThreadBase *)0x0) {
        bVar2 = CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x228),60000);
        if (bVar2) {
          FUN_14001e540(param_1);
        }
        else {
          FUN_14001e540(param_1);
        }
        if (*(longlong *)(param_1 + 0x228) != 0) {
          if (*(undefined8 **)(param_1 + 0x228) != (undefined8 *)0x0) {
            (**(code **)**(undefined8 **)(param_1 + 0x228))();
          }
          *(undefined8 *)(param_1 + 0x228) = 0;
        }
        FUN_140021bd0(param_1);
      }
      if (*(CThreadBase **)(param_1 + 0x230) != (CThreadBase *)0x0) {
        bVar2 = CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x230),60000);
        if (bVar2) {
          FUN_14001e540(param_1);
        }
        else {
          FUN_14001e540(param_1);
        }
        if (*(longlong *)(param_1 + 0x230) != 0) {
          if (*(undefined8 **)(param_1 + 0x230) != (undefined8 *)0x0) {
            (**(code **)**(undefined8 **)(param_1 + 0x230))();
          }
          *(undefined8 *)(param_1 + 0x230) = 0;
        }
        FUN_140021bd0(param_1);
      }
      if (*(CThreadBase **)(param_1 + 0x238) != (CThreadBase *)0x0) {
        bVar2 = CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x238),60000);
        if (bVar2) {
          FUN_14001e540(param_1);
        }
        else {
          FUN_14001e540(param_1);
        }
        if (*(longlong *)(param_1 + 0x238) != 0) {
          if (*(undefined8 **)(param_1 + 0x238) != (undefined8 *)0x0) {
            (**(code **)**(undefined8 **)(param_1 + 0x238))();
          }
          *(undefined8 *)(param_1 + 0x238) = 0;
        }
        FUN_140021bd0(param_1);
      }
      if (*(CThreadBase **)(param_1 + 0x1b8) != (CThreadBase *)0x0) {
        bVar2 = CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x1b8),60000);
        if (bVar2) {
          FUN_14001e540(param_1);
        }
        else {
          FUN_14001e540(param_1);
        }
        if (*(longlong *)(param_1 + 0x1b8) != 0) {
          if (*(undefined8 **)(param_1 + 0x1b8) != (undefined8 *)0x0) {
            (**(code **)**(undefined8 **)(param_1 + 0x1b8))();
          }
          *(undefined8 *)(param_1 + 0x1b8) = 0;
        }
        FUN_140021bd0(param_1);
      }
      if (*(CThreadBase **)(param_1 + 0x1c8) != (CThreadBase *)0x0) {
        bVar2 = CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x1c8),60000);
        if (bVar2) {
          FUN_14001e540(param_1);
        }
        else {
          FUN_14001e540(param_1);
        }
        if (*(longlong *)(param_1 + 0x1c8) != 0) {
          if (*(undefined8 **)(param_1 + 0x1c8) != (undefined8 *)0x0) {
            (**(code **)**(undefined8 **)(param_1 + 0x1c8))();
          }
          *(undefined8 *)(param_1 + 0x1c8) = 0;
        }
        FUN_140021bd0(param_1);
      }
      local_508 = 0;
      while (uVar18 = local_508,
            local_508 <
            (ulonglong)(*(longlong *)(param_1 + 0x1a8) - *(longlong *)(param_1 + 0x1a0) >> 3)) {
        local_438 = '\0';
        memset(local_437,0,0x3ff);
        if ((ulonglong)(*(longlong *)(param_1 + 0x1a8) - *(longlong *)(param_1 + 0x1a0) >> 3) <=
            uVar18) {
          _invalid_parameter_noinfo();
        }
        bVar2 = CThreadBase::CloseThread
                          (*(CThreadBase **)(*(longlong *)(param_1 + 0x1a0) + uVar18 * 8),300000);
        if (bVar2) {
          _snprintf(&local_438,0x3ff,&DAT_1406e3b48);
        }
        else {
          _snprintf(&local_438,0x3ff,"Close map group thread[%d] failed!");
        }
        FUN_14001e540(param_1);
        if ((ulonglong)(*(longlong *)(param_1 + 0x1a8) - *(longlong *)(param_1 + 0x1a0) >> 3) <=
            uVar18) {
          _invalid_parameter_noinfo();
        }
        lVar16 = *(longlong *)(param_1 + 0x1a0);
        if (*(longlong *)(lVar16 + uVar18 * 8) != 0) {
          puVar14 = *(undefined8 **)(lVar16 + uVar18 * 8);
          if (puVar14 != (undefined8 *)0x0) {
            (**(code **)*puVar14)();
          }
          *(undefined8 *)(lVar16 + uVar18 * 8) = 0;
        }
        FUN_140021bd0(param_1);
        local_508 = uVar18 + 1;
      }
      if (*(CThreadBase **)(param_1 + 0x1d8) != (CThreadBase *)0x0) {
        bVar2 = CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x1d8),60000);
        if (bVar2) {
          FUN_14001e540(param_1,&DAT_1406e3b08);
        }
        else {
          FUN_14001e540(param_1,"Close cross client failed!");
        }
        if (*(longlong *)(param_1 + 0x1d8) != 0) {
          puVar14 = *(undefined8 **)(param_1 + 0x1d8);
          if (puVar14 != (undefined8 *)0x0) {
            (**(code **)*puVar14)(puVar14,1);
          }
          *(undefined8 *)(param_1 + 0x1d8) = 0;
        }
        FUN_140021bd0(param_1);
      }
      if (*(CThreadBase **)(param_1 + 0x1c0) != (CThreadBase *)0x0) {
        bVar2 = CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x1c0),60000);
        if (bVar2) {
          FUN_14001e540(param_1,&DAT_1406e3ad0);
        }
        else {
          FUN_14001e540(param_1,"Close world thread failed!");
        }
        if (*(longlong *)(param_1 + 0x1c0) != 0) {
          puVar14 = *(undefined8 **)(param_1 + 0x1c0);
          if (puVar14 != (undefined8 *)0x0) {
            (**(code **)*puVar14)(puVar14,1);
          }
          *(undefined8 *)(param_1 + 0x1c0) = 0;
        }
        FUN_140021bd0(param_1);
      }
      if (*(CThreadBase **)(param_1 + 0x1e8) != (CThreadBase *)0x0) {
        bVar2 = CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x1e8),60000);
        if (bVar2) {
          FUN_14001e540(param_1,"Close Chat Thread OK.");
        }
        else {
          FUN_14001e540(param_1,"Close Chat Thread Failed.");
        }
        if (*(longlong *)(param_1 + 0x1e8) != 0) {
          puVar14 = *(undefined8 **)(param_1 + 0x1e8);
          if (puVar14 != (undefined8 *)0x0) {
            (**(code **)*puVar14)(puVar14,1);
          }
          *(undefined8 *)(param_1 + 0x1e8) = 0;
        }
        FUN_140021bd0(param_1);
      }
      if (*(CThreadBase **)(param_1 + 0x1e0) != (CThreadBase *)0x0) {
        bVar2 = CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x1e0),60000);
        if (bVar2) {
          FUN_14001e540(param_1,"Close Auction Search Thread OK.");
        }
        else {
          FUN_14001e540(param_1,"Close Auction Search Thread Failed.");
        }
        if (*(longlong *)(param_1 + 0x1e0) != 0) {
          puVar14 = *(undefined8 **)(param_1 + 0x1e0);
          if (puVar14 != (undefined8 *)0x0) {
            (**(code **)*puVar14)(puVar14,1);
          }
          *(undefined8 *)(param_1 + 0x1e0) = 0;
        }
        FUN_140021bd0(param_1);
      }
      if (*(CThreadBase **)(param_1 + 0x180) != (CThreadBase *)0x0) {
        bVar2 = CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x180),60000);
        if (bVar2) {
          FUN_14001e540(param_1,"Close async DB thread OK.");
        }
        else {
          FUN_14001e540(param_1,"Close async DB thread failed.");
        }
        if (*(longlong *)(param_1 + 0x180) != 0) {
          puVar14 = *(undefined8 **)(param_1 + 0x180);
          if (puVar14 != (undefined8 *)0x0) {
            (**(code **)*puVar14)(puVar14,1);
          }
          *(undefined8 *)(param_1 + 0x180) = 0;
        }
        FUN_140021bd0();
      }
      tq::SetLogThreadStatus(0);
      if (*(CThreadBase **)(param_1 + 0x178) != (CThreadBase *)0x0) {
        bVar2 = CThreadBase::CloseThread(*(CThreadBase **)(param_1 + 0x178),60000);
        if (bVar2) {
          FUN_14001e540(param_1,"Close Log thread OK.");
        }
        else {
          FUN_14001e540(param_1,"Close Log thread failed.");
        }
        if (*(longlong *)(param_1 + 0x178) != 0) {
          puVar14 = *(undefined8 **)(param_1 + 0x178);
          if (puVar14 != (undefined8 *)0x0) {
            (**(code **)*puVar14)(puVar14,1);
          }
          *(undefined8 *)(param_1 + 0x178) = 0;
        }
        FUN_140021bd0(param_1);
      }
      FUN_14001e540(param_1);
      FUN_140021bd0(param_1);
      (**(code **)(**(longlong **)(param_1 + 0x1f0) + 0x30))();
      FUN_14050e8c0();
      uVar8 = FUN_14002e300();
      FUN_14002d220(uVar8);
      *(undefined8 *)(param_1 + 0x1f0) = 0;
      DatabaseUnInit();
      FUN_140021f60();
      *(undefined4 *)(param_1 + 0x1fc) = 4;
    }
    else if (iVar7 == 4) {
      KillTimer(*(HWND *)(param_1 + 0x40),1);
      FUN_14001f070(param_1);
      Sleep(3000);
      if (DAT_1409758f0 != 0) {
        pAVar9 = AfxGetModuleState();
        ShellExecuteA(*(HWND *)(param_1 + 0x40),(LPCSTR)0x0,*(LPCSTR *)(pAVar9 + 0x20),(LPCSTR)0x0,
                      (LPCSTR)0x0,1);
      }
      FUN_140028960();
      FUN_14002ad90();
      FUN_1400018c0();
      FUN_1400029f0();
      CDialog::OnOK(param_1);
    }
    else {
      log_InlineLogERROR(&DAT_1406d9c10);
    }
LAB_140026533:
    DAT_14097593c = DAT_14097593c + -1;
  }
  if (param_2 == 2) {
    if (*(int *)(param_1 + 0x2278) == 0) {
      pCVar17 = param_1 + 0x227c;
      lVar16 = 0x229c - (longlong)pCVar17;
      do {
        CVar1 = *pCVar17;
        pCVar17[(longlong)(param_1 + lVar16)] = CVar1;
        pCVar17 = pCVar17 + 1;
      } while (CVar1 != (CDialog)0x0);
      cVar3 = FUN_140005ea0(param_1 + 0x240,param_1 + 0x229c);
      if (cVar3 == '\0') {
        FUN_140005d20(param_1 + 0x240);
        pCVar17 = param_1 + 0x228c;
        lVar16 = 0x229c - (longlong)pCVar17;
        do {
          CVar1 = *pCVar17;
          pCVar17[(longlong)(param_1 + lVar16)] = CVar1;
          pCVar17 = pCVar17 + 1;
        } while (CVar1 != (CDialog)0x0);
        cVar3 = FUN_140005ea0(param_1 + 0x240,param_1 + 0x229c);
        if (cVar3 == '\0') {
          FUN_140005d20(param_1 + 0x240);
        }
      }
      cVar3 = FUN_140005e80();
      if (cVar3 == '\0') {
        if (DAT_140949790 != '\0') {
          log_InlineLogERROR("reconnect authserver(%s) failed.",param_1 + 0x229c);
        }
      }
      else {
        *(undefined4 *)(param_1 + 0x2278) = 1;
        FUN_14001e0b0(param_1 + 0x240,*(undefined4 *)(param_1 + 0x22c4));
        if (DAT_140949790 != '\0') {
          log_InlineLogMessage("reconnect authserver(%s) success.",param_1 + 0x229c);
        }
      }
    }
    else if (*(int *)(param_1 + 0x2278) == 1) {
      cVar3 = FUN_140005e80(param_1 + 0x240);
      if (cVar3 == '\0') {
        if (DAT_140949790 != '\0') {
          log_InlineLogERROR("authserver(%s) close the connection.");
        }
        local_4b8 = 0;
        memset(local_4b7,0,0x7f);
        if ((((*PTR_s_DEADLOOP_DEADLOOP_140949748 == 'D') &&
             (PTR_s_DEADLOOP_DEADLOOP_140949748[1] == 'E')) &&
            (PTR_s_DEADLOOP_DEADLOOP_140949748[2] == 'A')) &&
           (PTR_s_DEADLOOP_DEADLOOP_140949748[3] == 'D')) {
          sprintf(local_4b7,"IP:%s VERSION:%s");
        }
        else {
          Ordinal_12(*(undefined4 *)PTR_s_DEADLOOP_DEADLOOP_140949748);
          sprintf(local_4b7,"IP:%s VERSION:%s");
        }
        uVar18 = 0xffffffffffffffff;
        pcVar10 = local_4b7;
        do {
          if (uVar18 == 0) break;
          uVar18 = uVar18 - 1;
          cVar3 = *pcVar10;
          pcVar10 = pcVar10 + 1;
        } while (cVar3 != '\0');
        if ((int)(~uVar18 - 1) - 1U < 0xfe) {
          local_4b8 = (undefined1)(~uVar18 - 1);
          cVar3 = FUN_140005ea0(param_1 + 0x240,param_1 + 0x229c);
          if (cVar3 != '\0') {
            FUN_140006880(param_1 + 0x240,&local_4b8);
            FUN_140005d20(param_1 + 0x240);
          }
        }
        if (DAT_140949790 != '\0') {
          log_InlineLogERROR("authentication(%s) faild.",param_1 + 0x229c);
        }
        *(undefined4 *)(param_1 + 0x2278) = 3;
        KillTimer(*(HWND *)(param_1 + 0x40),2);
        PostMessageA(*(HWND *)(param_1 + 0x40),0x12,0,0);
      }
      else {
        local_518 = (CDialog *)((ulonglong)local_518 & 0xffffffff00000000);
        pvVar15 = (void *)FUN_140006730(param_1 + 0x240,&local_518);
        if (pvVar15 != (void *)0x0) {
          if (0 < (int)local_518) {
            if (*(longlong *)(param_1 + 0x22b0) == 0) {
              if (3 < (int)local_518) {
                memmove(param_1 + 0x22b8,pvVar15,4);
                pvVar15 = operator_new__((ulonglong)*(uint *)(param_1 + 0x22b8));
                *(void **)(param_1 + 0x22b0) = pvVar15;
                FUN_140005c70(param_1 + 0x240,4);
                DAT_140975938 = 0;
              }
            }
            else {
              memmove((void *)((ulonglong)DAT_140975938 + *(longlong *)(param_1 + 0x22b0)),pvVar15,
                      (longlong)(int)local_518);
              DAT_140975938 = DAT_140975938 + (int)local_518;
              FUN_140005c70();
            }
          }
        }
        if ((*(longlong *)(param_1 + 0x22b0) != 0) && (*(uint *)(param_1 + 0x22b8) <= DAT_140975938)
           ) {
          DAT_140975938 = 0;
          FUN_140005d20(param_1 + 0x240);
          *(undefined4 *)(param_1 + 0x2278) = 3;
          KillTimer(*(HWND *)(param_1 + 0x40),2);
          cVar3 = FUN_140508f60(*(undefined8 *)(param_1 + 0x22b0),*(undefined4 *)(param_1 + 0x22b8),
                                1);
          if (cVar3 == '\0') {
            log_InlineLogERROR("import function failed at %s, %d",
                               "f:\\version\\cqserver-78.0.11-1204\\msgserver\\msgserverdlg.cpp");
            PostMessageA(*(HWND *)(param_1 + 0x40),0x12,0,0);
          }
          else {
            *(undefined4 *)(param_1 + 0x22c0) = 0;
            *(undefined4 *)(param_1 + 0x22bc) = 0;
            SetTimer(*(HWND *)(param_1 + 0x40),1,200,(TIMERPROC)0x0);
            if (DAT_140949790 != '\0') {
              log_InlineLogMessage("authentication(%s) success.",param_1 + 0x229c);
            }
          }
        }
      }
    }
    if ((*(int *)(param_1 + 0x22c0) != 0) &&
       (uVar5 = tq::TimeGet(0),
       (uint)(*(int *)(param_1 + 0x22bc) + *(int *)(param_1 + 0x22c0)) <= uVar5 / 1000)) {
      *(undefined4 *)(param_1 + 0x22c0) = 0;
      *(undefined4 *)(param_1 + 0x22bc) = 0;
      KillTimer(*(HWND *)(param_1 + 0x40),2);
      PostMessageA(*(HWND *)(param_1 + 0x40),0x12,0,0);
    }
  }
LAB_140026a28:
  CWnd::Default((CWnd *)param_1);
  return;
}

// ==== CAsyncDBThread::vfunc_0  @140026a60  [high:rtti-vtable]  (orig: FUN_140026a60)
CAsyncDBThread * FUN_140026a60(CAsyncDBThread *param_1,uint param_2)

{
  CAsyncDBThread::~CAsyncDBThread(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

// ==== CAsyncDBThread::helper_14002a510  @14002a510  [medium:callgraph-r1]  (orig: FUN_14002a510)
void * FUN_14002a510(void *param_1,uint param_2)

{
  DeleteCriticalSection((LPCRITICAL_SECTION)((longlong)param_1 + 0x40));
  if (*(HANDLE *)((longlong)param_1 + 0x68) != (HANDLE)0x0) {
    CloseHandle(*(HANDLE *)((longlong)param_1 + 0x68));
  }
  if (*(void **)((longlong)param_1 + 0x28) != (void *)0x0) {
    operator_delete(*(void **)((longlong)param_1 + 0x28));
  }
  *(undefined8 *)((longlong)param_1 + 0x28) = 0;
  *(undefined8 *)((longlong)param_1 + 0x30) = 0;
  *(undefined8 *)((longlong)param_1 + 0x38) = 0;
  operator_delete(*(void **)((longlong)param_1 + 0x10));
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}

// ==== CAsyncDBThread::helper_14002ad90  @14002ad90  [medium:callgraph-r0]  (orig: FUN_14002ad90)
void FUN_14002ad90(void)

{
  if (DAT_140975948 != 0) {
    FUN_14002a510(DAT_140975948,1);
    DAT_140975948 = 0;
  }
  return;
}

// ==== CAsyncDBThread::helper_14002adc0  @14002adc0  [medium:callgraph-r0]  (orig: FUN_14002adc0)
void FUN_14002adc0(longlong param_1)

{
  ulong uVar1;
  
  if (DAT_140975948 == 0) {
    log_InlineLogERROR(&DAT_1406d9c10);
    return;
  }
  if (*(int *)(param_1 + 0xc) != 0) {
    uVar1 = tq::TimeGet(0);
    if ((uint)(*(int *)(param_1 + 0xc) + *(int *)(param_1 + 8)) <= uVar1 / 1000) {
      *(undefined4 *)(param_1 + 0xc) = 0;
      *(undefined4 *)(param_1 + 8) = 0;
      FUN_14002a5a0(param_1);
    }
  }
  return;
}

// ==== CAsyncDBThread::helper_14002c6f0  @14002c6f0  [medium:callgraph-r0]  (orig: FUN_14002c6f0)
void FUN_14002c6f0(longlong param_1)

{
  CSingleLock local_20 [24];
  
  CSingleLock::CSingleLock(local_20,(CSyncObject *)(param_1 + 0x50),1);
  *(undefined4 *)(param_1 + 0xc) = 2;
  CSingleLock::Unlock(local_20);
  return;
}

// ==== CAsyncDBThread::helper_140508f60  @140508f60  [medium:callgraph-r0]  (orig: FUN_140508f60)
undefined8 FUN_140508f60(longlong param_1,int param_2,char param_3)

{
  int iVar1;
  HMODULE pHVar2;
  longlong lVar3;
  uint uVar4;
  longlong *local_res8;
  
  if (((param_1 != 0) && (0 < param_2)) &&
     (uVar4 = param_2 >> 0x1f & 7, (param_2 + uVar4 & 7) == uVar4)) {
    if (param_3 != '\0') {
      local_res8 = (longlong *)0x0;
      FUN_140509280(0,&local_res8);
      if (local_res8 == (longlong *)0x0) {
        return 0;
      }
      (**(code **)(*local_res8 + 0x18))(local_res8,"*J_@\'n 3");
      (**(code **)(*local_res8 + 0x10))(local_res8,param_1,param_2);
      (**(code **)*local_res8)();
    }
    pHVar2 = LoadLibraryA("msvcp90.dll");
    if (pHVar2 == (HMODULE)0x0) {
      log_InlineLogERROR("Cannot load msvcp90.dll");
    }
    pHVar2 = LoadLibraryA("msvcr90.dll");
    if (pHVar2 == (HMODULE)0x0) {
      log_InlineLogERROR("Cannot load msvcr90.dll");
    }
    iVar1 = FUN_140509990(&DAT_1409766a0,param_1,param_2);
    if (((iVar1 != 0) && (lVar3 = FUN_140509380(&DAT_1409766a0,"CreateMapGroup"), lVar3 != 0)) &&
       ((lVar3 = FUN_140509380(&DAT_1409766a0,"CreateWorldKernel"), lVar3 != 0 &&
        ((lVar3 = FUN_140509380(&DAT_1409766a0,"CreateNewMapData"), lVar3 != 0 &&
         (lVar3 = FUN_140509380(&DAT_1409766a0,"CreateMapGroupDefaultData"), lVar3 != 0)))))) {
      return 1;
    }
  }
  return 0;
}

// ==== CAsyncDBThread::helper_140509280  @140509280  [medium:callgraph-r1]  (orig: FUN_140509280)
void FUN_140509280(int param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  void *pvVar2;
  undefined8 uVar3;
  
  if (param_1 == 0) {
    puVar1 = operator_new(0x890);
    if (puVar1 == (undefined8 *)0x0) {
      puVar1 = (undefined8 *)0x0;
    }
    else {
      *puVar1 = DES::vftable;
    }
    *param_2 = puVar1;
  }
  else if (param_1 == 1) {
    pvVar2 = operator_new(0x60);
    if (pvVar2 == (void *)0x0) {
      uVar3 = 0;
    }
    else {
      uVar3 = FUN_14050a570(pvVar2);
    }
    *param_2 = uVar3;
  }
  else if (param_1 == 2) {
    puVar1 = operator_new(0x60);
    if (puVar1 == (undefined8 *)0x0) {
      puVar1 = (undefined8 *)0x0;
    }
    else {
      FUN_14050a570(puVar1);
      *puVar1 = MD5::CMD5ChecksumStandard::vftable;
    }
    *param_2 = puVar1;
  }
  else if (param_1 != 3) {
    *param_2 = 0;
  }
  return;
}

// ==== CAsyncDBThread::helper_140509380  @140509380  [medium:callgraph-r1]  (orig: FUN_140509380)
int FUN_140509380(int *param_1,ulonglong param_2)

{
  char cVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  longlong lVar5;
  uint uVar6;
  ulonglong uVar7;
  char *pcVar8;
  longlong lVar9;
  ulonglong uVar10;
  int iVar11;
  ulonglong uVar12;
  
  lVar5 = *(longlong *)(param_1 + 8);
  if (((*(int *)(lVar5 + 0x88) == 0) || (*(int *)(lVar5 + 0x8c) == 0)) || (*param_1 == 0)) {
    return 0;
  }
  iVar3 = param_1[4];
  uVar4 = *(uint *)(lVar5 + 0x88);
  uVar7 = (ulonglong)(iVar3 + uVar4);
  if ((param_2 & 0xffff0000) == 0) {
    uVar6 = 0xffffU - *(int *)((ulonglong)(iVar3 + uVar4) + 0x10) & (uint)param_2;
LAB_14050949f:
    if (((-1 < (int)uVar6) && ((int)uVar6 < *(int *)(uVar7 + 0x14))) &&
       ((uVar6 = *(uint *)((ulonglong)(uint)(*(int *)(uVar7 + 0x1c) + iVar3) +
                          (longlong)(int)uVar6 * 4), uVar6 <= uVar4 ||
        (*(int *)(lVar5 + 0x8c) + uVar4 <= uVar6)))) {
      return param_1[4] + uVar6;
    }
  }
  else {
    uVar10 = 0;
    uVar12 = uVar10;
    if (0 < (longlong)*(int *)(uVar7 + 0x18)) {
      do {
        pcVar8 = (char *)(ulonglong)
                         (uint)(*(int *)((ulonglong)(uint)(*(int *)(uVar7 + 0x20) + iVar3) +
                                        uVar10 * 4) + iVar3);
        lVar9 = param_2 - (longlong)pcVar8;
        do {
          cVar1 = *pcVar8;
          cVar2 = pcVar8[lVar9];
          if (cVar1 != cVar2) break;
          pcVar8 = pcVar8 + 1;
        } while (cVar2 != '\0');
        iVar11 = (int)uVar12;
        if (cVar1 == cVar2) {
          if (iVar11 < 0) {
            return 0;
          }
          uVar6 = (uint)*(ushort *)
                         ((ulonglong)(uint)(*(int *)(uVar7 + 0x24) + iVar3) + (longlong)iVar11 * 2);
          goto LAB_14050949f;
        }
        uVar10 = uVar10 + 1;
        uVar12 = (ulonglong)(iVar11 + 1);
      } while ((longlong)uVar10 < (longlong)*(int *)(uVar7 + 0x18));
    }
  }
  return 0;
}

// ==== CAsyncDBThread::helper_1405094d0  @1405094d0  [medium:callgraph-r2]  (orig: FUN_1405094d0)
void FUN_1405094d0(longlong param_1,longlong param_2)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  longlong *plVar4;
  uint uVar5;
  longlong lVar6;
  uint *puVar7;
  
  uVar5 = *(int *)(*(longlong *)(param_1 + 0x20) + 0xb0) + (int)param_2;
  puVar7 = (uint *)(ulonglong)uVar5;
  uVar2 = ((int *)(ulonglong)uVar5)[1];
  iVar3 = uVar2 + *(int *)(ulonglong)uVar5;
  while (iVar3 != 0) {
    lVar6 = 0;
    iVar3 = (int)((ulonglong)uVar2 - 8 >> 1);
    if (0 < iVar3) {
      do {
        uVar1 = *(ushort *)((longlong)puVar7 + lVar6 * 2 + 8);
        if ((uVar1 & 0xf000) == 0xa000) {
          plVar4 = (longlong *)((ulonglong)*puVar7 + param_2 + (ulonglong)(uVar1 & 0xfff));
          *plVar4 = *plVar4 + (param_2 - *(longlong *)(*(longlong *)(param_1 + 0x20) + 0x30));
        }
        lVar6 = lVar6 + 1;
      } while (lVar6 < iVar3);
    }
    puVar7 = (uint *)((longlong)puVar7 + (ulonglong)puVar7[1]);
    uVar2 = puVar7[1];
    iVar3 = uVar2 + *puVar7;
  }
  return;
}

// ==== CAsyncDBThread::helper_1405095a0  @1405095a0  [medium:callgraph-r2]  (orig: FUN_1405095a0)
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 FUN_1405095a0(longlong param_1,longlong param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  ulonglong uVar4;
  longlong lVar5;
  HMODULE hModule;
  FARPROC pFVar6;
  ulonglong *puVar7;
  longlong lVar8;
  ulonglong *puVar9;
  char *pcVar10;
  longlong lVar11;
  undefined1 auStack_168 [32];
  CHAR local_148 [256];
  ulonglong local_48;
  
  local_48 = DAT_1409707c0 ^ (ulonglong)auStack_168;
  uVar2 = *(uint *)(*(longlong *)(param_1 + 0x20) + 0x90);
  if (uVar2 != 0) {
    lVar11 = param_2 + (ulonglong)uVar2;
    uVar2 = *(uint *)(param_2 + (ulonglong)uVar2);
    while (uVar2 != 0) {
      uVar3 = *(uint *)(lVar11 + 0x10);
      puVar9 = (ulonglong *)((ulonglong)uVar2 + param_2);
      local_148[0] = '\0';
      memset(local_148 + 1,0,0xff);
      lVar5 = 0;
      pcVar10 = (char *)((ulonglong)*(uint *)(lVar11 + 0xc) + param_2);
      lVar8 = -(longlong)pcVar10;
      while (*pcVar10 != '\0') {
        lVar5 = lVar5 + 1;
        pcVar10[(longlong)(local_148 + lVar8)] = *pcVar10;
        pcVar10 = pcVar10 + 1;
        if (0xff < lVar5) {
          return 0;
        }
      }
      if (0xff < lVar5) {
        return 0;
      }
      local_148[lVar5] = '\0';
      hModule = GetModuleHandleA(local_148);
      if (hModule == (HMODULE)0x0) {
        return 0;
      }
      lVar8 = 0;
      if (*puVar9 != 0) {
        lVar5 = 0;
        puVar7 = puVar9;
        do {
          uVar4 = *puVar7;
          if ((uVar4 & 0x8000000000000000) == 0) {
            pFVar6 = GetProcAddress(hModule,(LPCSTR)(uVar4 + 2 + param_2));
          }
          else {
            pFVar6 = GetProcAddress(hModule,(LPCSTR)(uVar4 & 0xffff));
          }
          if (pFVar6 == (FARPROC)0x0) {
            return 0;
          }
          lVar8 = lVar8 + 1;
          *(FARPROC *)(lVar5 + (ulonglong)uVar3 + param_2) = pFVar6;
          lVar5 = lVar8 * 8;
          puVar7 = puVar9 + lVar8;
        } while (puVar9[lVar8] != 0);
      }
      puVar1 = (uint *)(lVar11 + 0x14);
      lVar11 = lVar11 + 0x14;
      uVar2 = *puVar1;
    }
  }
  return 1;
}

// ==== CAsyncDBThread::helper_140509760  @140509760  [medium:callgraph-r2]  (orig: FUN_140509760)
undefined8 FUN_140509760(longlong param_1,short *param_2,uint param_3)

{
  ushort uVar1;
  uint uVar2;
  ulonglong uVar3;
  int *piVar4;
  int iVar5;
  
  if (((0x3f < param_3) && (*(short **)(param_1 + 0x18) = param_2, *param_2 == 0x5a4d)) &&
     ((longlong)*(int *)(param_2 + 0x1e) + 0x108U <= (ulonglong)param_3)) {
    uVar2 = *(int *)(param_2 + 0x1e) + (int)param_2;
    uVar3 = (ulonglong)uVar2;
    *(ulonglong *)(param_1 + 0x20) = uVar3;
    if (((*(int *)(ulonglong)uVar2 == 0x4550) &&
        (uVar1 = *(ushort *)((longlong)(ulonglong)uVar2 + 0x16), (uVar1 & 0x2000) != 0)) &&
       (((uVar1 & 2) != 0 && (*(short *)(uVar3 + 0x14) == 0xf0)))) {
      iVar5 = 0;
      *(longlong *)(param_1 + 0x28) = (longlong)(int)uVar2 + 0x108;
      if (*(short *)(uVar3 + 6) != 0) {
        piVar4 = (int *)((longlong)(int)uVar2 + 0x118);
        do {
          if (param_3 < (uint)(piVar4[1] + *piVar4)) {
            return 0;
          }
          iVar5 = iVar5 + 1;
          piVar4 = piVar4 + 10;
        } while (iVar5 < (int)(uint)*(ushort *)(*(longlong *)(param_1 + 0x20) + 6));
      }
      return 1;
    }
  }
  return 0;
}

// ==== CAsyncDBThread::helper_140509820  @140509820  [medium:callgraph-r2]  (orig: FUN_140509820)
int FUN_140509820(longlong param_1)

{
  int iVar1;
  longlong lVar2;
  int iVar3;
  ulonglong uVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  
  lVar2 = *(longlong *)(param_1 + 0x20);
  if (lVar2 != 0) {
    iVar1 = *(int *)(lVar2 + 0x38);
    uVar4 = (ulonglong)*(ushort *)(lVar2 + 6);
    iVar5 = ((*(int *)(lVar2 + 0x54) + -1 + iVar1) / iVar1) * iVar1;
    if (*(ushort *)(lVar2 + 6) != 0) {
      piVar7 = (int *)(*(longlong *)(param_1 + 0x28) + 0xc);
      piVar6 = (int *)(*(longlong *)(param_1 + 0x28) + 0x10);
      do {
        iVar3 = piVar6[-2];
        if (piVar6[-2] < *piVar6) {
          iVar3 = *piVar6;
        }
        iVar3 = ((iVar3 + *piVar7 + -1 + iVar1) / iVar1) * iVar1;
        if (iVar5 < iVar3) {
          iVar5 = iVar3;
        }
        piVar6 = piVar6 + 10;
        piVar7 = piVar7 + 10;
        uVar4 = uVar4 - 1;
      } while (uVar4 != 0);
    }
    return iVar5;
  }
  return 0;
}

// ==== CAsyncDBThread::helper_1405098b0  @1405098b0  [medium:callgraph-r2]  (orig: FUN_1405098b0)
void FUN_1405098b0(longlong param_1,void *param_2,void *param_3)

{
  ushort uVar1;
  longlong lVar2;
  int iVar3;
  ulonglong uVar4;
  uint uVar5;
  ulonglong uVar6;
  
  uVar1 = *(ushort *)(*(longlong *)(param_1 + 0x20) + 6);
  memmove(param_2,param_3,
          (longlong)
          (int)(*(int *)(*(longlong *)(param_1 + 0x20) + 0x54) + ((uint)uVar1 + (uint)uVar1 * 4) * 8
               ));
  uVar4 = 0;
  uVar6 = uVar4;
  if (*(short *)(*(longlong *)(param_1 + 0x20) + 6) != 0) {
    do {
      lVar2 = *(longlong *)(param_1 + 0x28);
      iVar3 = *(int *)(uVar4 + 0xc + lVar2);
      if ((iVar3 != 0) && (uVar5 = *(uint *)(uVar4 + 0x10 + lVar2), uVar5 != 0)) {
        memmove((void *)(ulonglong)(uint)(iVar3 + (int)param_2),
                (void *)(ulonglong)(uint)(*(int *)(uVar4 + 0x14 + lVar2) + (int)param_3),
                (ulonglong)uVar5);
      }
      uVar5 = (int)uVar6 + 1;
      uVar4 = uVar4 + 0x28;
      uVar6 = (ulonglong)uVar5;
    } while ((int)uVar5 < (int)(uint)*(ushort *)(*(longlong *)(param_1 + 0x20) + 6));
  }
  *(void **)(param_1 + 0x18) = param_2;
  iVar3 = *(int *)((longlong)param_2 + 0x3c) + (int)param_2;
  *(longlong *)(param_1 + 0x20) = (longlong)iVar3;
  *(longlong *)(param_1 + 0x28) = (longlong)iVar3 + 0x108;
  return;
}

// ==== CAsyncDBThread::helper_140509990  @140509990  [medium:callgraph-r1]  (orig: FUN_140509990)
undefined8 FUN_140509990(undefined4 *param_1,undefined8 param_2)

{
  int iVar1;
  int iVar2;
  LPVOID lpAddress;
  code *pcVar3;
  DWORD local_res8 [2];
  
  if (param_1[4] != 0) {
    return 0;
  }
  iVar1 = FUN_140509760();
  if (iVar1 != 0) {
    iVar1 = FUN_140509820(param_1);
    if (iVar1 == 0) {
      return 0;
    }
    lpAddress = VirtualAlloc((LPVOID)0x0,(longlong)iVar1,0x3000,0x40);
    if (lpAddress != (LPVOID)0x0) {
      FUN_1405098b0(param_1,lpAddress,param_2);
      if ((*(int *)(*(longlong *)(param_1 + 8) + 0xb0) != 0) &&
         (*(int *)(*(longlong *)(param_1 + 8) + 0xb4) != 0)) {
        FUN_1405094d0(param_1,lpAddress);
      }
      iVar2 = FUN_1405095a0(param_1,lpAddress);
      if (iVar2 == 0) {
        VirtualFree(lpAddress,0,0x8000);
        return 0;
      }
      VirtualProtect(lpAddress,(longlong)iVar1,0x40,local_res8);
      *(LPVOID *)(*(longlong *)(param_1 + 8) + 0x30) = lpAddress;
      pcVar3 = (code *)(ulonglong)
                       (uint)(*(int *)(*(longlong *)(param_1 + 8) + 0x28) + (int)lpAddress);
      *(code **)(param_1 + 2) = pcVar3;
      iVar1 = (*pcVar3)(lpAddress,1);
      if (iVar1 != 0) {
        *param_1 = 1;
        param_1[4] = (int)lpAddress;
        return 1;
      }
      (**(code **)(param_1 + 2))(lpAddress,0,0);
      VirtualFree(lpAddress,0,0x8000);
      *(undefined8 *)(param_1 + 2) = 0;
    }
    return 0;
  }
  return 0;
}

// ==== CAsyncDBThread::helper_14050a570  @14050a570  [medium:callgraph-r2]  (orig: FUN_14050a570)
undefined8 * FUN_14050a570(undefined8 *param_1)

{
  *param_1 = MD5::CMD5Checksum::vftable;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  *(undefined4 *)((longlong)param_1 + 0x4c) = 0;
  *(undefined4 *)(param_1 + 9) = 0;
  *(undefined4 *)(param_1 + 10) = 0x67452301;
  *(undefined4 *)((longlong)param_1 + 0x54) = 0xefcdab89;
  *(undefined4 *)(param_1 + 0xb) = 0x98badcfe;
  *(undefined4 *)((longlong)param_1 + 0x5c) = 0x10325476;
  return param_1;
}

// ==== CAsyncDBThread::helper_14050c390  @14050c390  [medium:callgraph-r0]  (orig: FUN_14050c390)
undefined8 FUN_14050c390(int param_1)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  if (-1 < param_1) {
    uVar1 = DAT_140976748 - DAT_140976740 >> 3;
    if (param_1 < (int)uVar1) {
      if (uVar1 <= (ulonglong)(longlong)param_1) {
        _invalid_parameter_noinfo();
      }
                    /* WARNING: Could not recover jumptable at 0x00014050c3db. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar2 = (**(code **)(**(longlong **)(DAT_140976740 + (longlong)param_1 * 8) + 0x10))();
      return uVar2;
    }
  }
  return 0xffffffff;
}

// ==== CAsyncDBThread::helper_14050de60  @14050de60  [medium:callgraph-r1]  (orig: FUN_14050de60)
void FUN_14050de60(longlong *param_1)

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

// ==== CAsyncDBThread::helper_14050e8c0  @14050e8c0  [medium:callgraph-r0]  (orig: FUN_14050e8c0)
void FUN_14050e8c0(void)

{
  undefined8 *puVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong *plVar4;
  longlong lVar5;
  
  plVar4 = DAT_140976740;
  plVar2 = DAT_140976728;
  if (DAT_140976748 < DAT_140976740) {
    _invalid_parameter_noinfo();
    plVar2 = DAT_140976728;
  }
  while( true ) {
    plVar3 = DAT_140976748;
    if (DAT_140976748 < DAT_140976740) {
      _invalid_parameter_noinfo();
    }
    if ((plVar2 == (longlong *)0x0) || (plVar2 != DAT_140976728)) {
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
  FUN_14050de60(&DAT_140976728);
  return;
}

