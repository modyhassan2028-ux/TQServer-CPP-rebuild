void FUN_1400029f0(void)
{
  void *pvVar1;
  pvVar1 = DAT_1409754e8;
  if (DAT_1409754e8 != (void *)0x0) {
    if (*(HANDLE *)((longlong)DAT_1409754e8 + 8) != (HANDLE)0x0) {
      CloseHandle(*(HANDLE *)((longlong)DAT_1409754e8 + 8));
    }
    operator_delete(pvVar1);
    DAT_1409754e8 = (void *)0x0;
  }
  return;
}
