void * FUN_140023700(undefined8 param_1,void *param_2,longlong param_3,void *param_4)
{
  rsize_t _DstSize;
  longlong lVar1;
  lVar1 = param_3 - (longlong)param_2 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_4,_DstSize,param_2,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_4);
}
