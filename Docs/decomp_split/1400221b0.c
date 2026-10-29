longlong FUN_1400221b0(longlong param_1,ulonglong param_2)
{
  if ((ulonglong)((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18)) / 0x30) <= param_2
     ) {
    log_InlineLogERROR(&DAT_1406d9c10);
  }
  if ((ulonglong)((*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18)) / 0x30) <= param_2
     ) {
    _invalid_parameter_noinfo();
  }
  return param_2 * 0x30 + *(longlong *)(param_1 + 0x18);
}
