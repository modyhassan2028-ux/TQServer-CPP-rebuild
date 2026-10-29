undefined8 FUN_140006880(longlong param_1,void *param_2,int param_3,char param_4)
{
  undefined8 uVar1;
  if (*(int *)(param_1 + 0x2030) != 2) {
    return 0;
  }
  if (*(longlong *)(param_1 + 0x20) == -1) {
    log_InlineLogERROR("SendPacket() invalid socket failed.");
    if (*(longlong *)(param_1 + 0x20) != -1) {
      Ordinal_3();
    }
  }
  else {
    if (0x1000 < param_3 + *(int *)(param_1 + 0x202c)) {
      FUN_140005d60(param_1);
    }
    if (*(int *)(param_1 + 0x202c) + param_3 < 0x1001) {
      memcpy((void *)((longlong)*(int *)(param_1 + 0x202c) + 0x102c + param_1),param_2,
             (longlong)param_3);
      *(int *)(param_1 + 0x202c) = *(int *)(param_1 + 0x202c) + param_3;
      if (param_4 != '\0') {
        uVar1 = FUN_140005d60(param_1);
        return uVar1;
      }
      return 1;
    }
    log_InlineLogERROR("SendPacket() buf full!");
    if (*(longlong *)(param_1 + 0x20) != -1) {
      Ordinal_3();
      *(undefined8 *)(param_1 + 0x20) = 0xffffffffffffffff;
      *(undefined4 *)(param_1 + 0x2030) = 0;
      *(undefined4 *)(param_1 + 0x1028) = 0;
      *(undefined4 *)(param_1 + 0x202c) = 0;
      return 0;
    }
  }
  *(undefined8 *)(param_1 + 0x20) = 0xffffffffffffffff;
  *(undefined4 *)(param_1 + 0x2030) = 0;
  *(undefined4 *)(param_1 + 0x1028) = 0;
  *(undefined4 *)(param_1 + 0x202c) = 0;
  return 0;
}
