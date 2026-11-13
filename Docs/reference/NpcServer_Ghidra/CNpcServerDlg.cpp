// NpcServer.exe :: CNpcServerDlg  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CNpcServerDlg::vf_0x8 @ 140003a70  undefined vf_0x8(longlong param_1)

void CNpcServerDlg::vf_0x8(longlong param_1)

{
  *(undefined4 *)(param_1 + 0x1d8) = 3;
  return;
}


// ==== CNpcServerDlg::vf_0x0 @ 1400044a0  undefined vf_0x0(longlong param_1, char * param_2)

void CNpcServerDlg::vf_0x0(longlong param_1,char *param_2)

{
  int iVar1;
  CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *pCVar2;
  undefined1 auStack_78 [32];
  CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> local_58 [8];
  undefined8 local_50;
  CSingleLock local_48 [24];
  char local_30 [11];
  char local_25 [13];
  ulonglong local_18;
  
  local_50 = 0xfffffffffffffffe;
  local_18 = DAT_140103510 ^ (ulonglong)auStack_78;
  CSingleLock::CSingleLock(local_48,(CSyncObject *)(param_1 + 0xc0),1);
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::operator+=
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0xf8),&DAT_1400bfea8);
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::operator+=
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0xf8),param_2);
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::operator+=
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0xf8),&DAT_1400bfea0);
  if (7 < *(int *)(param_1 + 0x140)) {
    iVar1 = ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::Find
                      ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
                       (param_1 + 0x138),"\n",0);
    if (iVar1 != -1) {
      pCVar2 = (CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
               ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::Mid
                         ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>
                           *)(param_1 + 0x138),(int)local_58);
      ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::operator=
                ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
                 (param_1 + 0x138),pCVar2);
      ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
      ~CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>(local_58);
    }
  }
  tq::DateTime(local_30,0);
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::operator+=
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0x138),local_25);
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::operator+=
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0x138),&DAT_1400bfea8);
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::operator+=
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0x138),param_2);
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::operator+=
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0x138),&DAT_1400bfe98);
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::operator+=
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0x138),"\r\n");
  *(int *)(param_1 + 0x140) = *(int *)(param_1 + 0x140) + 1;
  log_InlineLogMessage("SHELL: %s",param_2);
  CSingleLock::Unlock(local_48);
  __security_check_cookie(local_18 ^ (ulonglong)auStack_78);
  return;
}


// ==== CNpcServerDlg::vf_0x10 @ 140004620  undefined vf_0x10(longlong param_1, char * param_2)

void CNpcServerDlg::vf_0x10(longlong param_1,char *param_2)

{
  CSingleLock local_20 [24];
  
  CSingleLock::CSingleLock(local_20,(CSyncObject *)(param_1 + 0xc0),1);
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::operator=
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (param_1 + 0xb0),param_2);
  CSingleLock::Unlock(local_20);
  return;
}


// ==== CNpcServerDlg::vf_0x18 @ 140004680  undefined vf_0x18(longlong param_1)

void CNpcServerDlg::vf_0x18(longlong param_1)

{
  CSingleLock local_28 [40];
  
  CSingleLock::CSingleLock(local_28,(CSyncObject *)(param_1 + 0xc0),1);
  CSingleLock::Unlock(local_28);
  return;
}


// ==== CNpcServerDlg::vf_0x8 @ 1400048a0  CDialog * vf_0x8(CDialog * param_1, uint param_2)

CDialog * CNpcServerDlg::vf_0x8(CDialog *param_1,uint param_2)

{
  FUN_1400033d0(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CNpcServerDlg::vf_0x2b0 @ 1400048d0  undefined vf_0x2b0(CDialog * param_1)

void CNpcServerDlg::vf_0x2b0(CDialog *param_1)

{
  CDialog *pCVar1;
  bool bVar2;
  __time32_t _Var3;
  ulong uVar4;
  HMENU pHVar5;
  CMenu *pCVar6;
  char *lpNewItem;
  HANDLE pvVar7;
  undefined8 uVar8;
  undefined1 auStack_c68 [32];
  CDialog *local_c48;
  char *local_c40;
  char *local_c38;
  CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> local_c28 [8];
  undefined8 local_c20;
  CIniFile local_c18 [1024];
  CIniFile local_818 [1024];
  char local_418 [1023];
  undefined1 local_19;
  ulonglong local_18;
  
  local_c20 = 0xfffffffffffffffe;
  local_18 = DAT_140103510 ^ (ulonglong)auStack_c68;
  CDialog::OnInitDialog(param_1);
  pHVar5 = GetSystemMenu(*(HWND *)(param_1 + 0x40),0);
  pCVar6 = CMenu::FromHandle(pHVar5);
  if (pCVar6 != (CMenu *)0x0) {
    ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
    CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>(local_c28);
    ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::LoadStringA
              (local_c28,0x65);
    bVar2 = ATL::CSimpleStringT<char,1>::IsEmpty((CSimpleStringT<char,1> *)local_c28);
    if (!bVar2) {
      AppendMenuA(*(HMENU *)(pCVar6 + 8),0x800,0,(LPCSTR)0x0);
      lpNewItem = ATL::CSimpleStringT<char,1>::operator_char_const____ptr64
                            ((CSimpleStringT<char,1> *)local_c28);
      AppendMenuA(*(HMENU *)(pCVar6 + 8),0,0x10,lpNewItem);
    }
    ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
    ~CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>(local_c28);
  }
  SendMessageA(*(HWND *)(param_1 + 0x40),0x80,1,*(LPARAM *)(param_1 + 0x2c8));
  SendMessageA(*(HWND *)(param_1 + 0x40),0x80,0,*(LPARAM *)(param_1 + 0x2c8));
  pvVar7 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,1,0,(LPCSTR)0x0);
  *(HANDLE *)(param_1 + 0x2d0) = pvVar7;
  if (pvVar7 == (HANDLE)0x0) {
    CWnd::MessageBoxA((CWnd *)param_1,"Create exit event failed!",(char *)0x0,0);
    CDialog::EndDialog(param_1,-1);
  }
  else {
    pvVar7 = CreateMutexA((LPSECURITY_ATTRIBUTES)0x0,0,(LPCSTR)0x0);
    *(HANDLE *)(param_1 + 0x1e8) = pvVar7;
    if (pvVar7 == (HANDLE)0x0) {
      CWnd::MessageBoxA((CWnd *)param_1,"Create mutext failed!",(char *)0x0,0);
      CDialog::EndDialog(param_1,-1);
    }
    else {
      GetLastError();
      CIniFile::CIniFile(local_c18,"shell.ini","AccountServer");
      pCVar1 = param_1 + 0x200;
      CIniFile::GetString(local_c18,(char *)pCVar1,"SERVERNAME",0x10);
      local_c38 = "14:01:42";
      local_c40 = "Dec  4 2015";
      local_c48 = pCVar1;
      _snprintf(local_418,0x400,"%s - %s - %s %s","Conquer Online NPC Server");
      local_19 = 0;
      CWnd::SetWindowTextA((CWnd *)param_1,local_418);
      CreateDirectoryA("syslog",(LPSECURITY_ATTRIBUTES)0x0);
      _Var3 = _time32((__time32_t *)0x0);
      tq::InitLog(local_418,"syslog/npcserver","syslog/npcdb",(longlong)_Var3);
      tq::log_Save("syslog/npcserver","\n\n\n",0);
      log_InlineLogMessage("=================================================================");
      log_InlineLogMessage(local_418);
      log_InlineLogMessage("=================================================================");
      log_InlineLogMessage("f:\\version\\cqserver-78.0.11-1204\\npcserver\\npcserverdlg.cpp");
      *(undefined4 *)(param_1 + 0x2c0) = 1;
      *(undefined4 *)(param_1 + 0x1f0) = 10;
      uVar4 = tq::TimeGet(0);
      *(uint *)(param_1 + 500) = uVar4 / 1000;
      *(undefined4 *)(param_1 + 0x1f8) = 300;
      uVar4 = tq::TimeGet(0);
      *(uint *)(param_1 + 0x1fc) = uVar4 / 1000;
      CIniFile::CIniFile(local_818,"config.ini","System");
      CIniFile::GetString(local_818,(char *)(param_1 + 0x210),"SERVERNAME",0x10);
      SetTimer(*(HWND *)(param_1 + 0x40),1,500,(TIMERPROC)0x0);
      local_c48 = pCVar1;
      _snprintf(local_418,0x400,"%s - %s");
      SetPropA(*(HWND *)(param_1 + 0x40),local_418,(HANDLE)0x1);
      uVar8 = FUN_140071f20(2);
      if ((char)uVar8 == '\0') {
        CWnd::MessageBoxA((CWnd *)param_1,"Initial intra message port failed!",(char *)0x0,0);
      }
      CIniFile::~CIniFile(local_818);
      CIniFile::~CIniFile(local_c18);
    }
  }
  __security_check_cookie(local_18 ^ (ulonglong)auStack_c68);
  return;
}


// ==== CNpcServerDlg::vf_0x2c8 @ 140004cb0  undefined vf_0x2c8(CWnd * param_1)

void CNpcServerDlg::vf_0x2c8(CWnd *param_1)

{
  int iVar1;
  
  (*(code *)**(undefined8 **)(param_1 + 0xe8))(param_1 + 0xe8,"CLOSE button pressed.");
  FUN_1400046b0(param_1);
  iVar1 = AfxMessageBox("Are you CLOSE server new?",0x101,0);
  if (iVar1 == 1) {
    *(undefined4 *)(param_1 + 0x2c0) = 3;
  }
  return;
}


// ==== CNpcServerDlg::vf_0x60 @ 1400053a0  undefined * * vf_0x60(void)

undefined ** CNpcServerDlg::vf_0x60(void)

{
  return &PTR_LAB_1400c02f8;
}


