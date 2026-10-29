void * FUN_140022d80(void *param_1,longlong param_2,longlong param_3)
{
  longlong lVar1;
  void *_Dst;
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _Dst = (void *)(param_3 + lVar1 * -8);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 8,param_1,lVar1 * 8);
  }
  return _Dst;
}
