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
