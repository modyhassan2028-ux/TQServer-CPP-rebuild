void * FUN_14002a510(void *param_1,uint param_2)
{
  DeleteCriticalSection((LPCRITICAL_SECTION)((longlong)param_1 + 0x40));
  if (*(HANDLE *)((longlong)param_1 + 0x68) != (HANDLE)0x0) {
    CloseHandle(*(HANDLE *)((longlong)param_1 + 0x68));
  }
  if (*(void **)((longlong)param_1 + 0x28) != (void *)0x0) {
    operator_delete(*(void **)((longlong)param_1 + 0x28));
  }
  *(undefined8 *)((longlong)param_1 + 0x28) = 0;
  *(undefined8 *)((longlong)param_1 + 0x30) = 0;
  *(undefined8 *)((longlong)param_1 + 0x38) = 0;
  operator_delete(*(void **)((longlong)param_1 + 0x10));
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}
