/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
undefined4 FUN_1405095a0(longlong param_1,longlong param_2)
{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  ulonglong uVar4;
  longlong lVar5;
  HMODULE hModule;
  FARPROC pFVar6;
  ulonglong *puVar7;
  longlong lVar8;
  ulonglong *puVar9;
  char *pcVar10;
  longlong lVar11;
  undefined1 auStack_168 [32];
  CHAR local_148 [256];
  ulonglong local_48;
  local_48 = DAT_1409707c0 ^ (ulonglong)auStack_168;
  uVar2 = *(uint *)(*(longlong *)(param_1 + 0x20) + 0x90);
  if (uVar2 != 0) {
    lVar11 = param_2 + (ulonglong)uVar2;
    uVar2 = *(uint *)(param_2 + (ulonglong)uVar2);
    while (uVar2 != 0) {
      uVar3 = *(uint *)(lVar11 + 0x10);
      puVar9 = (ulonglong *)((ulonglong)uVar2 + param_2);
      local_148[0] = '\0';
      memset(local_148 + 1,0,0xff);
      lVar5 = 0;
      pcVar10 = (char *)((ulonglong)*(uint *)(lVar11 + 0xc) + param_2);
      lVar8 = -(longlong)pcVar10;
      while (*pcVar10 != '\0') {
        lVar5 = lVar5 + 1;
        pcVar10[(longlong)(local_148 + lVar8)] = *pcVar10;
        pcVar10 = pcVar10 + 1;
        if (0xff < lVar5) {
          return 0;
        }
      }
      if (0xff < lVar5) {
        return 0;
      }
      local_148[lVar5] = '\0';
      hModule = GetModuleHandleA(local_148);
      if (hModule == (HMODULE)0x0) {
        return 0;
      }
      lVar8 = 0;
      if (*puVar9 != 0) {
        lVar5 = 0;
        puVar7 = puVar9;
        do {
          uVar4 = *puVar7;
          if ((uVar4 & 0x8000000000000000) == 0) {
            pFVar6 = GetProcAddress(hModule,(LPCSTR)(uVar4 + 2 + param_2));
          }
          else {
            pFVar6 = GetProcAddress(hModule,(LPCSTR)(uVar4 & 0xffff));
          }
          if (pFVar6 == (FARPROC)0x0) {
            return 0;
          }
          lVar8 = lVar8 + 1;
          *(FARPROC *)(lVar5 + (ulonglong)uVar3 + param_2) = pFVar6;
          lVar5 = lVar8 * 8;
          puVar7 = puVar9 + lVar8;
        } while (puVar9[lVar8] != 0);
      }
      puVar1 = (uint *)(lVar11 + 0x14);
      lVar11 = lVar11 + 0x14;
      uVar2 = *puVar1;
    }
  }
  return 1;
}
