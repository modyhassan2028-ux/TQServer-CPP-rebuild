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
