longlong FUN_140006730(longlong param_1,undefined4 *param_2,char param_3)
{
  int iVar1;
  if (param_2 == (undefined4 *)0x0) {
    log_InlineLogERROR(&DAT_1406d9c10);
    return 0;
  }
  *param_2 = 0;
  if (*(int *)(param_1 + 0x2030) == 2) {
    if (*(longlong *)(param_1 + 0x20) != -1) {
      if (param_3 != '\0') {
        iVar1 = *(int *)(param_1 + 0x1028);
        if (iVar1 < 0x1000) {
          iVar1 = Ordinal_16(*(longlong *)(param_1 + 0x20),(longlong)iVar1 + 0x28 + param_1,
                             0x1000 - iVar1,0);
          if (iVar1 < 1) {
            if (iVar1 == 0) {
              log_InlineLogERROR("GetPacket() connect be close.");
            }
            else {
              if (-1 < iVar1) goto LAB_140006857;
              iVar1 = Ordinal_111();
              if (iVar1 == 0x2733) goto LAB_140006857;
              if (iVar1 != 0x2746) {
                log_InlineLogERROR("recv packet failed[%d].");
              }
            }
            FUN_140005d20(param_1);
          }
          else {
            *(int *)(param_1 + 0x1028) = *(int *)(param_1 + 0x1028) + iVar1;
          }
        }
      }
LAB_140006857:
      *param_2 = *(undefined4 *)(param_1 + 0x1028);
      return param_1 + 0x28;
    }
    log_InlineLogERROR("GetPacket() invalid socket failed.");
    if (*(longlong *)(param_1 + 0x20) != -1) {
      Ordinal_3();
    }
    *(undefined8 *)(param_1 + 0x20) = 0xffffffffffffffff;
    *(undefined4 *)(param_1 + 0x2030) = 0;
    *(undefined4 *)(param_1 + 0x1028) = 0;
    *(undefined4 *)(param_1 + 0x202c) = 0;
  }
  return 0;
}
