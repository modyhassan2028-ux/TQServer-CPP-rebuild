// NpcServer.exe :: CSingleMap2<class_CConstGameData<&char*_szItemTypeTable,&char*_szItemTypeTableID>_>  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CSingleMap2<class_CConstGameData<&char*_szItemTypeTable,&char*_szItemTypeTableID>_>::vf_0x0 @ 140020f80  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 *
CSingleMap2<class_CConstGameData<&char*_szItemTypeTable,&char*_szItemTypeTableID>_>::vf_0x0
          (undefined8 *param_1,uint param_2)

{
  FUN_140020dd0(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


