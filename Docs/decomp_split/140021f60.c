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
