// NpcServer.exe :: CEdit  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CEdit::vf_0x208 @ 140003ea0  undefined vf_0x208(void)

void CEdit::vf_0x208(void)

{
  return;
}


// ==== CEdit::vf_0x8 @ 140003f10  CEdit * vf_0x8(CEdit * param_1, uint param_2)

CEdit * CEdit::vf_0x8(CEdit *param_1,uint param_2)

{
  CEdit::~CEdit(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CEdit::SetSel @ 140003fa0  void SetSel(CEdit * this, int param_1, int param_2, int param_3)

/* Library Function - Single Match
    public: void __cdecl CEdit::SetSel(int,int,int) __ptr64
   
   Libraries: Visual Studio 2008 Release, Visual Studio 2010 Release, Visual Studio 2012 Release */

void __thiscall CEdit::SetSel(CEdit *this,int param_1,int param_2,int param_3)

{
  SendMessageA(*(HWND *)(this + 0x40),0xb1,(longlong)param_1,(longlong)param_2);
  if (param_3 == 0) {
    SendMessageA(*(HWND *)(this + 0x40),0xb7,0,0);
  }
  return;
}


