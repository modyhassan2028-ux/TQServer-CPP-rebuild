undefined8 FUN_140005c70(longlong param_1,int param_2)
{
  int *piVar1;
  int iVar2;
  if (*(int *)(param_1 + 0x1028) < param_2) {
    log_InlineLogERROR(
                      "ClearPacket()  error, Getpacket OutBufSize:%d, ClearPacket nLen:%d, m_nLen:%d, unMsgType:%d at %s, %d"
                      );
  }
  if (*(int *)(param_1 + 0x2030) == 2) {
    iVar2 = *(int *)(param_1 + 0x1028) - param_2;
    if (0 < iVar2) {
      memcpy((void *)(param_1 + 0x28),(void *)((longlong)param_2 + 0x28 + param_1),(longlong)iVar2);
    }
    piVar1 = (int *)(param_1 + 0x1028);
    *piVar1 = *piVar1 - param_2;
    if (-1 < *piVar1) {
      return 1;
    }
    *(undefined4 *)(param_1 + 0x1028) = 0;
  }
  return 0;
}
