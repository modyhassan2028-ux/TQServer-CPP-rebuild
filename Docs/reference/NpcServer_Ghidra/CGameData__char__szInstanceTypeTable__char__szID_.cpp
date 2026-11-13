// NpcServer.exe :: CGameData<&char*_szInstanceTypeTable,&char*_szID>  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CGameData<&char*_szInstanceTypeTable,&char*_szID>::vf_0x0 @ 1400226a0  undefined8 * vf_0x0(undefined8 * param_1, uint param_2, undefined8 param_3, undefined8 param_4)

undefined8 *
CGameData<&char*_szInstanceTypeTable,&char*_szID>::vf_0x0
          (undefined8 *param_1,uint param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 *puVar1;
  
  *param_1 = vftable;
  puVar1 = (undefined8 *)param_1[1];
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,*(char *)(param_1 + 2) == '\0',param_3,param_4,0xfffffffffffffffe);
  }
  *param_1 = IGameData::vftable;
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


