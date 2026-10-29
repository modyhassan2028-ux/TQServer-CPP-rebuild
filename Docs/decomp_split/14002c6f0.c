void FUN_14002c6f0(longlong param_1)
{
  CSingleLock local_20 [24];
  CSingleLock::CSingleLock(local_20,(CSyncObject *)(param_1 + 0x50),1);
  *(undefined4 *)(param_1 + 0xc) = 2;
  CSingleLock::Unlock(local_20);
  return;
}
