// NpcServer.exe :: _anon_16C71DD6__CNormalFile  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== _anon_16C71DD6::CNormalFile::vf_0x8 @ 1400968b0  bool vf_0x8(longlong param_1)

bool _anon_16C71DD6::CNormalFile::vf_0x8(longlong param_1)

{
  return *(longlong *)(param_1 + 8) != 0;
}


// ==== _anon_16C71DD6::CNormalFile::vf_0x10 @ 1400968c0  ulonglong vf_0x10(longlong param_1, void * param_2, int param_3, int param_4)

ulonglong _anon_16C71DD6::CNormalFile::vf_0x10
                    (longlong param_1,void *param_2,int param_3,int param_4)

{
  int iVar1;
  size_t sVar2;
  uint uVar3;
  
  if (param_2 != (void *)0x0) {
    sVar2 = fread(param_2,(longlong)param_3,(longlong)param_4,*(FILE **)(param_1 + 8));
    return sVar2 * (longlong)param_3;
  }
  iVar1 = fseek(*(FILE **)(param_1 + 8),param_3 * param_4,1);
  uVar3 = 0;
  if (iVar1 == 0) {
    uVar3 = param_3 * param_4;
  }
  return (ulonglong)uVar3;
}


// ==== _anon_16C71DD6::CNormalFile::vf_0x0 @ 140096e00  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * _anon_16C71DD6::CNormalFile::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  if ((FILE *)param_1[1] != (FILE *)0x0) {
    fclose((FILE *)param_1[1]);
  }
  *param_1 = IFile::vftable;
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


