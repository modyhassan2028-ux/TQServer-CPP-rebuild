// NpcServer.exe :: CAboutDlg  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CAboutDlg::vf_0x210 @ 140003eb0  undefined vf_0x210(longlong param_1)

void CAboutDlg::vf_0x210(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x000140003eb6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  EnableWindow(*(undefined8 *)(param_1 + 0x40),0);
  return;
}


// ==== CAboutDlg::vf_0x218 @ 140003ec0  undefined vf_0x218(longlong param_1)

void CAboutDlg::vf_0x218(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x000140003ec9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  EnableWindow(*(undefined8 *)(param_1 + 0x40),1);
  return;
}


// ==== CAboutDlg::vf_0x288 @ 140003ed0  undefined vf_0x288(CDialog * param_1, ushort param_2, CWnd * param_3)

void CAboutDlg::vf_0x288(CDialog *param_1,ushort param_2,CWnd *param_3)

{
  CDialog::Create(param_1,(char *)(ulonglong)param_2,param_3);
  return;
}


// ==== CAboutDlg::vf_0x8 @ 1400040a0  CDialog * vf_0x8(CDialog * param_1, uint param_2)

CDialog * CAboutDlg::vf_0x8(CDialog *param_1,uint param_2)

{
  CDialog::~CDialog(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CAboutDlg::vf_0x208 @ 1400040f0  undefined vf_0x208(void)

void CAboutDlg::vf_0x208(void)

{
  return;
}


// ==== CAboutDlg::vf_0x60 @ 140004100  undefined * * vf_0x60(void)

undefined ** CAboutDlg::vf_0x60(void)

{
  return &PTR_LAB_1400bf638;
}


