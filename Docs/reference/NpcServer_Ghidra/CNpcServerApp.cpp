// NpcServer.exe :: CNpcServerApp  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CNpcServerApp::vf_0x10 @ 140003270  undefined vf_0x10(void)

void CNpcServerApp::vf_0x10(void)

{
  return;
}


// ==== CNpcServerApp::vf_0x18 @ 140003290  undefined vf_0x18(void)

void CNpcServerApp::vf_0x18(void)

{
  return;
}


// ==== CNpcServerApp::vf_0x20 @ 1400032a0  undefined vf_0x20(void)

void CNpcServerApp::vf_0x20(void)

{
  return;
}


// ==== CNpcServerApp::vf_0x60 @ 140003370  undefined * * vf_0x60(void)

undefined ** CNpcServerApp::vf_0x60(void)

{
  return &PTR_LAB_1400bee80;
}


// ==== CNpcServerApp::vf_0x8 @ 140003380  CWinApp * vf_0x8(CWinApp * param_1, uint param_2)

CWinApp * CNpcServerApp::vf_0x8(CWinApp *param_1,uint param_2)

{
  CWinApp::~CWinApp(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CNpcServerApp::vf_0xb0 @ 1400035b0  undefined vf_0xb0(longlong param_1)

void CNpcServerApp::vf_0xb0(longlong param_1)

{
  DWORD DVar1;
  int iVar2;
  BOOL BVar3;
  char *pcVar4;
  HANDLE pvVar5;
  HWND pHVar6;
  undefined1 auStack_748 [32];
  CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> local_728 [8];
  undefined8 local_720;
  CIniFile local_718 [1024];
  CDialog local_318 [752];
  char local_28 [16];
  ulonglong local_18;
  
  local_720 = 0xfffffffffffffffe;
  local_18 = DAT_140103510 ^ (ulonglong)auStack_748;
  _set_invalid_parameter_handler(FUN_140003210);
  _set_purecall_handler(FUN_140003240);
  CIniFile::CIniFile(local_718,"shell.ini","AccountServer");
  CIniFile::GetString(local_718,local_28,"SERVERNAME",0x10);
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
  CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>(local_728);
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::Format
            (local_728,"%s - %s","Conquer Online NPC Server",local_28);
  pcVar4 = ATL::CSimpleStringT<char,1>::operator_char_const____ptr64
                     ((CSimpleStringT<char,1> *)local_728);
  pvVar5 = CreateMutexA((LPSECURITY_ATTRIBUTES)0x0,1,pcVar4);
  *(HANDLE *)(param_1 + 0x140) = pvVar5;
  if (pvVar5 == (HANDLE)0x0) {
    pcVar4 = ATL::CSimpleStringT<char,1>::operator_char_const____ptr64
                       ((CSimpleStringT<char,1> *)local_728);
    MessageBoxA((HWND)0x0,"Create mutext failed.",pcVar4,0x30);
    ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
    ~CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>(local_728);
    CIniFile::~CIniFile(local_718);
  }
  else {
    DVar1 = GetLastError();
    if (DVar1 == 0xb7) {
      CloseHandle(*(HANDLE *)(param_1 + 0x140));
      *(undefined8 *)(param_1 + 0x140) = 0;
      pHVar6 = GetDesktopWindow();
      pHVar6 = GetWindow(pHVar6,5);
      iVar2 = IsWindow(pHVar6);
      while (iVar2 != 0) {
        pcVar4 = ATL::CSimpleStringT<char,1>::operator_char_const____ptr64
                           ((CSimpleStringT<char,1> *)local_728);
        pvVar5 = GetPropA(pHVar6,pcVar4);
        if (pvVar5 != (HANDLE)0x0) {
          BVar3 = IsIconic(pHVar6);
          if (BVar3 != 0) {
            ShowWindow(pHVar6,9);
          }
          SetForegroundWindow(pHVar6);
          ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
          ~CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>(local_728);
          CIniFile::~CIniFile(local_718);
          goto LAB_14000381f;
        }
        pHVar6 = GetWindow(pHVar6,2);
        iVar2 = IsWindow(pHVar6);
      }
      pcVar4 = ATL::CSimpleStringT<char,1>::operator_char_const____ptr64
                         ((CSimpleStringT<char,1> *)local_728);
      MessageBoxA((HWND)0x0,"NpcServer is running, but I can\'t find its window.",pcVar4,0x30);
      ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
      ~CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>(local_728);
      CIniFile::~CIniFile(local_718);
    }
    else {
      FUN_140004110(local_318,(CWnd *)0x0);
      *(CDialog **)(param_1 + 0x40) = local_318;
      CDialog::DoModal(local_318);
      FUN_1400033d0(local_318);
      ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
      ~CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>(local_728);
      CIniFile::~CIniFile(local_718);
    }
  }
LAB_14000381f:
  __security_check_cookie(local_18 ^ (ulonglong)auStack_748);
  return;
}


// ==== CNpcServerApp::vf_0xe0 @ 1400039b0  undefined vf_0xe0(CWinApp * param_1)

void CNpcServerApp::vf_0xe0(CWinApp *param_1)

{
  if (*(HANDLE *)(param_1 + 0x140) != (HANDLE)0x0) {
    CloseHandle(*(HANDLE *)(param_1 + 0x140));
    *(undefined8 *)(param_1 + 0x140) = 0;
  }
  FUN_140003940();
  CWinApp::ExitInstance(param_1);
  return;
}


