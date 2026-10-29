void FUN_1400223a0(undefined8 param_1,ulonglong param_2)
{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 8)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_140944540);
  }
  operator_new(param_2 * 8);
  return;
}
