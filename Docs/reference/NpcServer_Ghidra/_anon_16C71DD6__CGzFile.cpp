// NpcServer.exe :: _anon_16C71DD6__CGzFile  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== _anon_16C71DD6::CGzFile::vf_0x8 @ 140096850  bool vf_0x8(longlong param_1)

bool _anon_16C71DD6::CGzFile::vf_0x8(longlong param_1)

{
  return 0 < *(int *)(param_1 + 8);
}


// ==== _anon_16C71DD6::CGzFile::vf_0x10 @ 140096860  int vf_0x10(longlong param_1, void * param_2, int param_3, int param_4)

int _anon_16C71DD6::CGzFile::vf_0x10(longlong param_1,void *param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0xc);
  iVar2 = param_3 * param_4;
  if (*(int *)(param_1 + 8) < iVar1 + iVar2) {
    iVar2 = *(int *)(param_1 + 8) - iVar1;
  }
  if (param_2 != (void *)0x0) {
    memcpy(param_2,(void *)((longlong)iVar1 + *(longlong *)(param_1 + 0x10)),(longlong)iVar2);
  }
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + iVar2;
  return iVar2;
}


// ==== _anon_16C71DD6::CGzFile::vf_0x0 @ 140096d90  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * _anon_16C71DD6::CGzFile::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  if ((void *)param_1[2] != (void *)0x0) {
    operator_delete__((void *)param_1[2]);
  }
  *param_1 = IFile::vftable;
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


