undefined8 FUN_140508f60(longlong param_1,int param_2,char param_3)
{
  int iVar1;
  HMODULE pHVar2;
  longlong lVar3;
  uint uVar4;
  longlong *local_res8;
  if (((param_1 != 0) && (0 < param_2)) &&
     (uVar4 = param_2 >> 0x1f & 7, (param_2 + uVar4 & 7) == uVar4)) {
    if (param_3 != '\0') {
      local_res8 = (longlong *)0x0;
      FUN_140509280(0,&local_res8);
      if (local_res8 == (longlong *)0x0) {
        return 0;
      }
      (**(code **)(*local_res8 + 0x18))(local_res8,"*J_@\'n 3");
      (**(code **)(*local_res8 + 0x10))(local_res8,param_1,param_2);
      (**(code **)*local_res8)();
    }
    pHVar2 = LoadLibraryA("msvcp90.dll");
    if (pHVar2 == (HMODULE)0x0) {
      log_InlineLogERROR("Cannot load msvcp90.dll");
    }
    pHVar2 = LoadLibraryA("msvcr90.dll");
    if (pHVar2 == (HMODULE)0x0) {
      log_InlineLogERROR("Cannot load msvcr90.dll");
    }
    iVar1 = FUN_140509990(&DAT_1409766a0,param_1,param_2);
    if (((iVar1 != 0) && (lVar3 = FUN_140509380(&DAT_1409766a0,"CreateMapGroup"), lVar3 != 0)) &&
       ((lVar3 = FUN_140509380(&DAT_1409766a0,"CreateWorldKernel"), lVar3 != 0 &&
        ((lVar3 = FUN_140509380(&DAT_1409766a0,"CreateNewMapData"), lVar3 != 0 &&
         (lVar3 = FUN_140509380(&DAT_1409766a0,"CreateMapGroupDefaultData"), lVar3 != 0)))))) {
      return 1;
    }
  }
  return 0;
}
