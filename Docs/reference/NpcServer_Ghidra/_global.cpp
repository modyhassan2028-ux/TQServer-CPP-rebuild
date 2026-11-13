// NpcServer.exe :: _global  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== DoDataExchange @ 1400042b0  undefined DoDataExchange(longlong param_1, CDataExchange * param_2)

/* Library Function - Multiple Matches With Same Base Name
    protected: virtual void __cdecl CMFCColorDialog::DoDataExchange(class CDataExchange * __ptr64)
   __ptr64
    protected: virtual void __cdecl CMFCToolBarsCommandsPropertyPage::DoDataExchange(class
   CDataExchange * __ptr64) __ptr64
   
   Libraries: Visual Studio 2010 Release, Visual Studio 2012 Release */

void DoDataExchange(longlong param_1,CDataExchange *param_2)

{
  DDX_Control(param_2,1000,(CWnd *)(param_1 + 0xf0));
  DDX_Text(param_2,0x3ea,
           (CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
           (param_1 + 0x198));
  DDX_Text(param_2,0x3e9,
           (CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
           (param_1 + 0x1a0));
  return;
}


// ==== _Move<> @ 140051460  longlong * _Move<>(longlong * param_1, longlong * param_2, longlong * param_3)

/* Library Function - Multiple Matches With Same Base Name
    class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > * __ptr64 __cdecl
   std::_Move<class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64>(class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > * __ptr64)
    class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > * __ptr64 __cdecl
   std::_Move<class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64>(class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,struct std::_Nonscalar_ptr_iterator_tag)
    class std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned
   char,class Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64 __cdecl
   std::_Move<class std::shared_ptr<struct Concurrency::details::_Task_impl<struct
   std::pair<unsigned char,class Concurrency::details::_CancellationTokenState * __ptr64> > > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned
   char,class Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64>(class
   std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64,class
   std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64,class
   std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64)
    class std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned
   char,class Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64 __cdecl
   std::_Move<class std::shared_ptr<struct Concurrency::details::_Task_impl<struct
   std::pair<unsigned char,class Concurrency::details::_CancellationTokenState * __ptr64> > > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned
   char,class Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64>(class
   std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64,class
   std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64,class
   std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64,struct
   std::_Nonscalar_ptr_iterator_tag)
   
   Library: Visual Studio 2012 Release */

longlong * _Move<>(longlong *param_1,longlong *param_2,longlong *param_3)

{
  if (param_1 != param_2) {
    do {
      FUN_1400447b0(param_3,param_1);
      param_1 = param_1 + 6;
      param_3 = param_3 + 6;
    } while (param_1 != param_2);
  }
  return param_3;
}


// ==== _Move<> @ 1400524b0  longlong * _Move<>(longlong * param_1, longlong * param_2, longlong * param_3)

/* Library Function - Multiple Matches With Same Base Name
    class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > * __ptr64 __cdecl
   std::_Move<class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64>(class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > * __ptr64)
    class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > * __ptr64 __cdecl
   std::_Move<class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64>(class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,struct std::_Nonscalar_ptr_iterator_tag)
    class std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned
   char,class Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64 __cdecl
   std::_Move<class std::shared_ptr<struct Concurrency::details::_Task_impl<struct
   std::pair<unsigned char,class Concurrency::details::_CancellationTokenState * __ptr64> > > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned
   char,class Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64>(class
   std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64,class
   std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64,class
   std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64)
    class std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned
   char,class Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64 __cdecl
   std::_Move<class std::shared_ptr<struct Concurrency::details::_Task_impl<struct
   std::pair<unsigned char,class Concurrency::details::_CancellationTokenState * __ptr64> > > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned
   char,class Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64>(class
   std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64,class
   std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64,class
   std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64,struct
   std::_Nonscalar_ptr_iterator_tag)
   
   Library: Visual Studio 2012 Release */

longlong * _Move<>(longlong *param_1,longlong *param_2,longlong *param_3)

{
  if (param_1 != param_2) {
    do {
      FUN_1400522b0(param_3,param_1);
      param_1 = param_1 + 6;
      param_3 = param_3 + 6;
    } while (param_1 != param_2);
  }
  return param_3;
}


// ==== FID_conflict:`vector_deleting_destructor' @ 1400729fc  type_info * FID_conflict:`vector_deleting_destructor'(type_info * param_1, uint param_2)

/* Library Function - Multiple Matches With Different Base Names
    public: virtual void * __ptr64 __cdecl exception::`vector deleting destructor'(unsigned int)
   __ptr64
    public: virtual void * __ptr64 __cdecl std::exception::`vector deleting destructor'(unsigned
   int) __ptr64
    public: virtual void * __ptr64 __cdecl logic_error::`vector deleting destructor'(unsigned int)
   __ptr64
    public: virtual void * __ptr64 __cdecl type_info::`vector deleting destructor'(unsigned int)
   __ptr64
   
   Library: Visual Studio 2008 Release */

type_info * FID_conflict__vector_deleting_destructor_(type_info *param_1,uint param_2)

{
  if ((param_2 & 2) == 0) {
    type_info::_type_info_dtor_internal_method(param_1);
    if ((param_2 & 1) != 0) {
      operator_delete(param_1);
    }
  }
  else {
    _eh_vector_destructor_iterator_
              (param_1,0x18,*(int *)(param_1 + -8),type_info::_type_info_dtor_internal_method);
    if ((param_2 & 1) != 0) {
      operator_delete(param_1 + -8);
    }
    param_1 = param_1 + -8;
  }
  return param_1;
}


// ==== __GSHandlerCheckCommon @ 140072a74  undefined __GSHandlerCheckCommon(ulonglong param_1, longlong param_2, uint * param_3)

/* Library Function - Single Match
    __GSHandlerCheckCommon
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release, Visual Studio 2012 Release,
   Visual Studio 2019 Release */

void __GSHandlerCheckCommon(ulonglong param_1,longlong param_2,uint *param_3)

{
  longlong lVar1;
  ulonglong uVar2;
  
  uVar2 = param_1;
  if ((*param_3 & 4) != 0) {
    uVar2 = (longlong)(int)param_3[1] + param_1 & (longlong)(int)-param_3[2];
  }
  lVar1 = (ulonglong)*(uint *)(*(longlong *)(param_2 + 0x10) + 8) + *(longlong *)(param_2 + 8);
  if ((*(byte *)(lVar1 + 3) & 0xf) != 0) {
    param_1 = param_1 + (longlong)(int)(*(byte *)(lVar1 + 3) & 0xfffffff0);
  }
  __security_check_cookie(param_1 ^ *(ulonglong *)((longlong)(int)(*param_3 & 0xfffffff8) + uVar2));
  return;
}


// ==== __GSHandlerCheck @ 140072ad8  undefined8 __GSHandlerCheck(undefined8 param_1, ulonglong param_2, undefined8 param_3, longlong param_4)

/* Library Function - Single Match
    __GSHandlerCheck
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release, Visual Studio 2012 Release,
   Visual Studio 2019 Release */

undefined8
__GSHandlerCheck(undefined8 param_1,ulonglong param_2,undefined8 param_3,longlong param_4)

{
  __GSHandlerCheckCommon(param_2,param_4,*(uint **)(param_4 + 0x38));
  return 1;
}


// ==== __security_check_cookie @ 140072b10  void __security_check_cookie(uintptr_t _StackCookie)

/* Library Function - Single Match
    __security_check_cookie
   
   Libraries: Visual Studio 2008 Debug, Visual Studio 2008 Release */

void __cdecl __security_check_cookie(uintptr_t _StackCookie)

{
  if ((_StackCookie == DAT_140103510) && ((short)(_StackCookie >> 0x30) == 0)) {
    return;
  }
                    /* WARNING: Subroutine does not return */
  __report_gsfailure(_StackCookie);
}


// ==== _onexit @ 140072c04  _onexit_t _onexit(_onexit_t _Func)

/* Library Function - Single Match
    _onexit
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release, Visual Studio 2012 Release */

_onexit_t __cdecl _onexit(_onexit_t _Func)

{
  _onexit_t p_Var1;
  undefined8 uVar2;
  longlong local_res10;
  undefined8 local_res18 [2];
  
  local_res10 = _decode_pointer(DAT_1401071c8);
  if (local_res10 == -1) {
    p_Var1 = _onexit(_Func);
  }
  else {
    _lock(8);
    local_res10 = _decode_pointer(DAT_1401071c8);
    local_res18[0] = _decode_pointer(DAT_1401071c0);
    uVar2 = _encode_pointer(_Func);
    p_Var1 = (_onexit_t)__dllonexit(uVar2,&local_res10,local_res18);
    DAT_1401071c8 = _encode_pointer(local_res10);
    DAT_1401071c0 = _encode_pointer(local_res18[0]);
    _unlock(8);
  }
  return p_Var1;
}


// ==== atexit @ 140072cb4  int atexit(_func_5014 * param_1)

/* Library Function - Single Match
    atexit
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release, Visual Studio 2012 Release */

int __cdecl atexit(_func_5014 *param_1)

{
  _onexit_t p_Var1;
  
  p_Var1 = _onexit((_onexit_t)param_1);
  return (p_Var1 != (_onexit_t)0x0) - 1;
}


// ==== __tmainCRTStartup @ 140072d48  int __tmainCRTStartup(void)

/* Library Function - Single Match
    __tmainCRTStartup
   
   Library: Visual Studio 2008 Release */

int __tmainCRTStartup(void)

{
  void *pvVar1;
  bool bVar2;
  bool bVar3;
  void *pvVar4;
  BOOL BVar5;
  int iVar6;
  void *pvVar7;
  byte *pbVar8;
  uint uVar9;
  bool bVar10;
  _STARTUPINFOA local_78;
  
  bVar3 = false;
  GetStartupInfoA(&local_78);
  pvVar1 = StackBase;
  bVar2 = false;
  while( true ) {
    pvVar7 = (void *)0x0;
    LOCK();
    bVar10 = DAT_1401071b0 == (void *)0x0;
    pvVar4 = pvVar1;
    if (!bVar10) {
      pvVar7 = DAT_1401071b0;
      pvVar4 = DAT_1401071b0;
    }
    DAT_1401071b0 = pvVar4;
    UNLOCK();
    if (bVar10) goto LAB_140072d9b;
    if (pvVar7 == pvVar1) break;
    Sleep(1000);
  }
  bVar2 = true;
LAB_140072d9b:
  if (DAT_1401071ac == 1) {
    _amsg_exit(0x1f);
  }
  else if (DAT_1401071ac == 0) {
    DAT_1401071ac = 1;
    iVar6 = _initterm_e(&DAT_1400bdf68);
    if (iVar6 != 0) {
      return 0xff;
    }
  }
  else {
    DAT_140104724 = 1;
  }
  if (DAT_1401071ac == 1) {
    _initterm(&DAT_1400bdf08);
    DAT_1401071ac = 2;
  }
  if (!bVar2) {
    LOCK();
    DAT_1401071b0 = (void *)0x0;
    UNLOCK();
  }
  if ((DAT_1401071b8 != (code *)0x0) &&
     (BVar5 = _IsNonwritableInCurrentImage((PBYTE)&DAT_1401071b8), BVar5 != 0)) {
    (*DAT_1401071b8)(0);
  }
  pbVar8 = *(byte **)_acmdln_exref;
  while ((0x20 < *pbVar8 || ((*pbVar8 != 0 && (bVar3))))) {
    if (*pbVar8 == 0x22) {
      bVar3 = !bVar3;
    }
    iVar6 = _ismbblead((uint)*pbVar8);
    if (iVar6 != 0) {
      pbVar8 = pbVar8 + 1;
    }
    pbVar8 = pbVar8 + 1;
  }
  for (; (*pbVar8 != 0 && (*pbVar8 < 0x21)); pbVar8 = pbVar8 + 1) {
  }
  uVar9 = 10;
  if (((byte)local_78.dwFlags & 1) != 0) {
    uVar9 = (uint)local_78.wShowWindow;
  }
  DAT_140104720 =
       AfxWinMain((HINSTANCE__ *)&IMAGE_DOS_HEADER_140000000,(HINSTANCE__ *)0x0,(char *)pbVar8,uVar9
                 );
  if (DAT_140104704 != 0) {
    if (DAT_140104724 == 0) {
      _cexit();
    }
    return DAT_140104720;
  }
                    /* WARNING: Subroutine does not return */
  exit(DAT_140104720);
}


// ==== entry @ 1400730a0  undefined entry(void)

void entry(void)

{
  __security_init_cookie();
  __tmainCRTStartup();
  return;
}


// ==== __ArrayUnwind @ 1400731f0  void __ArrayUnwind(void * param_1, __uint64 param_2, int param_3, _func_void_void_ptr * param_4)

/* Library Function - Single Match
    void __cdecl __ArrayUnwind(void * __ptr64,unsigned __int64,int,void (__cdecl*)(void * __ptr64))
   
   Library: Visual Studio 2008 Release */

void __cdecl __ArrayUnwind(void *param_1,__uint64 param_2,int param_3,_func_void_void_ptr *param_4)

{
  while( true ) {
    param_3 = param_3 + -1;
    if (param_3 < 0) break;
    param_1 = (void *)((longlong)param_1 - param_2);
    (*param_4)(param_1);
  }
  return;
}


// ==== `eh_vector_destructor_iterator' @ 14007323c  void `eh_vector_destructor_iterator'(void * param_1, __uint64 param_2, int param_3, _func_void_void_ptr * param_4)

/* Library Function - Single Match
    void __cdecl `eh vector destructor iterator'(void * __ptr64,unsigned __int64,int,void
   (__cdecl*)(void * __ptr64))
   
   Library: Visual Studio 2008 Release */

void __cdecl
_eh_vector_destructor_iterator_
          (void *param_1,__uint64 param_2,int param_3,_func_void_void_ptr *param_4)

{
  void *pvVar1;
  uint uVar2;
  ulonglong uVar3;
  
  uVar3 = (ulonglong)param_3;
  pvVar1 = (void *)(uVar3 * param_2 + (longlong)param_1);
  while( true ) {
    uVar2 = (int)uVar3 - 1;
    uVar3 = (ulonglong)uVar2;
    if ((int)uVar2 < 0) break;
    pvVar1 = (void *)((longlong)pvVar1 - param_2);
    (*param_4)(pvVar1);
  }
  return;
}


// ==== __report_gsfailure @ 14007329c  void __report_gsfailure(uintptr_t _StackCookie)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __report_gsfailure
   
   Libraries: Visual Studio 2008 Debug, Visual Studio 2008 Release */

void __cdecl __report_gsfailure(uintptr_t _StackCookie)

{
  HANDLE hProcess;
  DWORD64 unaff_retaddr;
  uintptr_t local_res8 [4];
  PVOID local_48;
  ulonglong local_40;
  PRUNTIME_FUNCTION local_38;
  DWORD64 local_30;
  DWORD64 local_28;
  undefined8 local_20;
  undefined8 local_18;
  
  local_res8[0] = _StackCookie;
  RtlCaptureContext(&DAT_1401047d0);
  local_30 = DAT_1401048c8;
  local_38 = RtlLookupFunctionEntry(DAT_1401048c8,&local_28,(PUNWIND_HISTORY_TABLE)0x0);
  if (local_38 == (PRUNTIME_FUNCTION)0x0) {
    _DAT_140104868 = local_res8;
    DAT_1401048c8 = unaff_retaddr;
  }
  else {
    RtlVirtualUnwind(0,local_28,local_30,local_38,(PCONTEXT)&DAT_1401047d0,&local_48,&local_40,
                     (PKNONVOLATILE_CONTEXT_POINTERS)0x0);
  }
  _DAT_140104740 = DAT_1401048c8;
  _DAT_140104850 = local_res8[0];
  _DAT_140104730 = 0xc0000409;
  _DAT_140104734 = 1;
  local_20 = DAT_140103510;
  local_18 = DAT_140103518;
  DAT_1401047c8 = IsDebuggerPresent();
  __crt_debugger_hook(1);
  SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)0x0);
  UnhandledExceptionFilter((_EXCEPTION_POINTERS *)&PTR_DAT_1400ccda8);
  if (DAT_1401047c8 == 0) {
    __crt_debugger_hook(1);
  }
  hProcess = GetCurrentProcess();
  TerminateProcess(hProcess,0xc0000409);
  return;
}


// ==== __CxxUnhandledExceptionFilter @ 140073404  long __CxxUnhandledExceptionFilter(_EXCEPTION_POINTERS * param_1)

/* Library Function - Single Match
    long __cdecl __CxxUnhandledExceptionFilter(struct _EXCEPTION_POINTERS * __ptr64)
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release */

long __cdecl __CxxUnhandledExceptionFilter(_EXCEPTION_POINTERS *param_1)

{
  int iVar1;
  PEXCEPTION_RECORD pEVar2;
  code *pcVar3;
  long lVar4;
  
  pEVar2 = param_1->ExceptionRecord;
  if (((pEVar2->ExceptionCode == 0xe06d7363) && (pEVar2->NumberParameters == 4)) &&
     ((iVar1 = (int)pEVar2->ExceptionInformation[0], iVar1 == 0x19930520 ||
      (((iVar1 == 0x19930521 || (iVar1 == 0x19930522)) || (iVar1 == 0x1994000)))))) {
    terminate();
    pcVar3 = (code *)swi(3);
    lVar4 = (*pcVar3)();
    return lVar4;
  }
  return 0;
}


// ==== _ValidateImageBase @ 140073500  BOOL _ValidateImageBase(PBYTE pImageBase)

/* Library Function - Single Match
    _ValidateImageBase
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release */

BOOL __cdecl _ValidateImageBase(PBYTE pImageBase)

{
  uint uVar1;
  
  if (*(short *)pImageBase != 0x5a4d) {
    return 0;
  }
  uVar1 = 0;
  if (*(int *)(pImageBase + *(int *)(pImageBase + 0x3c)) == 0x4550) {
    uVar1 = (uint)((short)*(int *)((longlong)(pImageBase + *(int *)(pImageBase + 0x3c)) + 0x18) ==
                  0x20b);
  }
  return uVar1;
}


// ==== _FindPESection @ 140073530  PIMAGE_SECTION_HEADER _FindPESection(PBYTE pImageBase, DWORD_PTR rva)

/* Library Function - Single Match
    _FindPESection
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release, Visual Studio 2019 Release */

PIMAGE_SECTION_HEADER __cdecl _FindPESection(PBYTE pImageBase,DWORD_PTR rva)

{
  int iVar1;
  PIMAGE_SECTION_HEADER p_Var2;
  uint uVar3;
  
  iVar1 = *(int *)(pImageBase + 0x3c);
  uVar3 = 0;
  p_Var2 = (PIMAGE_SECTION_HEADER)
           (pImageBase +
           (ulonglong)*(ushort *)(pImageBase + (longlong)iVar1 + 0x14) + 0x18 + (longlong)iVar1);
  if (*(ushort *)(pImageBase + (longlong)iVar1 + 6) != 0) {
    do {
      if ((p_Var2->VirtualAddress <= rva) &&
         (rva < (p_Var2->Misc).PhysicalAddress + p_Var2->VirtualAddress)) {
        return p_Var2;
      }
      uVar3 = uVar3 + 1;
      p_Var2 = p_Var2 + 1;
    } while (uVar3 < *(ushort *)(pImageBase + (longlong)iVar1 + 6));
  }
  return (PIMAGE_SECTION_HEADER)0x0;
}


// ==== _IsNonwritableInCurrentImage @ 140073580  BOOL _IsNonwritableInCurrentImage(PBYTE pTarget)

/* Library Function - Single Match
    _IsNonwritableInCurrentImage
   
   Library: Visual Studio 2008 Release */

BOOL __cdecl _IsNonwritableInCurrentImage(PBYTE pTarget)

{
  uint uVar1;
  PIMAGE_SECTION_HEADER p_Var2;
  IMAGE_DOS_HEADER *pImageBase;
  
  pImageBase = &IMAGE_DOS_HEADER_140000000;
  uVar1 = _ValidateImageBase((PBYTE)&IMAGE_DOS_HEADER_140000000);
  p_Var2 = (PIMAGE_SECTION_HEADER)(ulonglong)uVar1;
  if (uVar1 != 0) {
    p_Var2 = _FindPESection((PBYTE)pImageBase,(longlong)pTarget - (longlong)pImageBase);
    if (p_Var2 != (PIMAGE_SECTION_HEADER)0x0) {
      p_Var2 = (PIMAGE_SECTION_HEADER)(ulonglong)(~(p_Var2->Characteristics >> 0x1f) & 1);
    }
  }
  return (BOOL)p_Var2;
}


// ==== __security_init_cookie @ 1400735ec  void __security_init_cookie(void)

/* Library Function - Single Match
    __security_init_cookie
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release */

void __cdecl __security_init_cookie(void)

{
  _FILETIME _Var1;
  DWORD DVar2;
  DWORD DVar3;
  DWORD DVar4;
  _FILETIME local_res8;
  LARGE_INTEGER local_res10;
  
  local_res8.dwLowDateTime = 0;
  local_res8.dwHighDateTime = 0;
  if (DAT_140103510 == 0x2b992ddfa232) {
    GetSystemTimeAsFileTime(&local_res8);
    _Var1 = local_res8;
    DVar2 = GetCurrentProcessId();
    DVar3 = GetCurrentThreadId();
    DVar4 = GetTickCount();
    QueryPerformanceCounter(&local_res10);
    DAT_140103510 =
         (local_res10.QuadPart ^
         (ulonglong)_Var1 ^ (ulonglong)DVar2 ^ (ulonglong)DVar3 ^ (ulonglong)DVar4) & 0xffffffffffff
    ;
    if (DAT_140103510 == 0x2b992ddfa232) {
      DAT_140103510 = 0x2b992ddfa233;
    }
    DAT_140103518 = ~DAT_140103510;
  }
  else {
    DAT_140103518 = ~DAT_140103510;
  }
  return;
}


// ==== max_size @ 140079dd0  undefined8 max_size(void)

/* WARNING: Removing unreachable block (ram,0x000140079df9) */
/* Library Function - Multiple Matches With Same Base Name
    public: unsigned __int64 __cdecl std::allocator<unsigned short>::max_size(void)const __ptr64
    public: unsigned __int64 __cdecl std::allocator<wchar_t>::max_size(void)const __ptr64
   
   Libraries: Visual Studio 2005 Debug, Visual Studio 2008 Debug, Visual Studio 2010 Debug, Visual
   Studio 2010 Release */

undefined8 max_size(void)

{
  return 0x1fffffffffffffff;
}


// ==== _Move<> @ 140089a90  longlong * _Move<>(longlong * param_1, longlong * param_2, longlong * param_3)

/* Library Function - Multiple Matches With Same Base Name
    class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > * __ptr64 __cdecl
   std::_Move<class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64>(class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > * __ptr64)
    class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > * __ptr64 __cdecl
   std::_Move<class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64>(class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<unsigned char> > *
   __ptr64,struct std::_Nonscalar_ptr_iterator_tag)
    class std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned
   char,class Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64 __cdecl
   std::_Move<class std::shared_ptr<struct Concurrency::details::_Task_impl<struct
   std::pair<unsigned char,class Concurrency::details::_CancellationTokenState * __ptr64> > > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned
   char,class Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64>(class
   std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64,class
   std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64,class
   std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64)
    class std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned
   char,class Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64 __cdecl
   std::_Move<class std::shared_ptr<struct Concurrency::details::_Task_impl<struct
   std::pair<unsigned char,class Concurrency::details::_CancellationTokenState * __ptr64> > > *
   __ptr64,class std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned
   char,class Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64>(class
   std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64,class
   std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64,class
   std::shared_ptr<struct Concurrency::details::_Task_impl<struct std::pair<unsigned char,class
   Concurrency::details::_CancellationTokenState * __ptr64> > > * __ptr64,struct
   std::_Nonscalar_ptr_iterator_tag)
   
   Library: Visual Studio 2012 Release */

longlong * _Move<>(longlong *param_1,longlong *param_2,longlong *param_3)

{
  if (param_1 != param_2) {
    do {
      FUN_140089910(param_3,param_1);
      param_1 = param_1 + 6;
      param_3 = param_3 + 6;
    } while (param_1 != param_2);
  }
  return param_3;
}


// ==== AfxInitialize @ 140097f44  int AfxInitialize(int param_1, ulong param_2)

/* Library Function - Single Match
    int __cdecl AfxInitialize(int,unsigned long)
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release, Visual Studio 2012 Release,
   Visual Studio 2015 Release */

int __cdecl AfxInitialize(int param_1,ulong param_2)

{
  AFX_MODULE_STATE *pAVar1;
  
  pAVar1 = AfxGetModuleState();
  pAVar1[0x28] = SUB41(param_1,0);
  *(ulong *)(pAVar1 + 0x78) = param_2;
  if (param_1 == 0) {
    _setmbcp(-3);
  }
  return 1;
}


// ==== __chkstk @ 1400a3e70  undefined __chkstk(void)

/* WARNING: This is an inlined function */
/* Library Function - Single Match
    __chkstk
   
   Libraries: Visual Studio 2005, Visual Studio 2008, Visual Studio 2010, Visual Studio 2012 */

void __chkstk(void)

{
  undefined1 *in_RAX;
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 local_res8 [32];
  
  puVar1 = local_res8 + -(longlong)in_RAX;
  if (local_res8 < in_RAX) {
    puVar1 = (undefined1 *)0x0;
  }
  if (puVar1 < StackLimit) {
    puVar2 = (undefined1 *)StackLimit;
    do {
      puVar2 = puVar2 + -0x1000;
      *puVar2 = 0;
    } while ((undefined1 *)((ulonglong)puVar1 & 0xfffffffffffff000) != puVar2);
  }
  return;
}


