undefined8 * FUN_14050a570(undefined8 *param_1)
{
  *param_1 = MD5::CMD5Checksum::vftable;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  *(undefined4 *)((longlong)param_1 + 0x4c) = 0;
  *(undefined4 *)(param_1 + 9) = 0;
  *(undefined4 *)(param_1 + 10) = 0x67452301;
  *(undefined4 *)((longlong)param_1 + 0x54) = 0xefcdab89;
  *(undefined4 *)(param_1 + 0xb) = 0x98badcfe;
  *(undefined4 *)((longlong)param_1 + 0x5c) = 0x10325476;
  return param_1;
}
