// NpcServer.exe :: CGameData<&char*_szMonsterClusterTable,&char*_szID>  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CGameData<&char*_szMonsterClusterTable,&char*_szID>::vf_0x8 @ 1400606a0  undefined vf_0x8(longlong param_1)

void CGameData<&char*_szMonsterClusterTable,&char*_szID>::vf_0x8(longlong param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)
           (**(code **)(**(longlong **)(param_1 + 8) + 0x20))
                     (*(longlong **)(param_1 + 8),&DAT_140102d90);
                    /* WARNING: Could not recover jumptable at 0x0001400606bf. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x40))(plVar1);
  return;
}


// ==== CGameData<&char*_szMonsterClusterTable,&char*_szID>::vf_0x10 @ 1400606d0  undefined vf_0x10(longlong param_1)

void CGameData<&char*_szMonsterClusterTable,&char*_szID>::vf_0x10(longlong param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(**(code **)(**(longlong **)(param_1 + 8) + 0x10))();
                    /* WARNING: Could not recover jumptable at 0x0001400606e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x48))(plVar1);
  return;
}


// ==== CGameData<&char*_szMonsterClusterTable,&char*_szID>::vf_0x18 @ 1400606f0  undefined vf_0x18(longlong param_1)

void CGameData<&char*_szMonsterClusterTable,&char*_szID>::vf_0x18(longlong param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(**(code **)(**(longlong **)(param_1 + 8) + 0x10))();
                    /* WARNING: Could not recover jumptable at 0x000140060708. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x78))(plVar1);
  return;
}


// ==== CGameData<&char*_szMonsterClusterTable,&char*_szID>::vf_0x20 @ 140060710  undefined vf_0x20(longlong param_1)

void CGameData<&char*_szMonsterClusterTable,&char*_szID>::vf_0x20(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x000140060717. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(longlong **)(param_1 + 8) + 0x58))();
  return;
}


// ==== CGameData<&char*_szMonsterClusterTable,&char*_szID>::vf_0x28 @ 140060720  undefined vf_0x28(longlong param_1, undefined4 param_2, longlong * param_3)

void CGameData<&char*_szMonsterClusterTable,&char*_szID>::vf_0x28
               (longlong param_1,undefined4 param_2,longlong *param_3)

{
  longlong *plVar1;
  longlong lVar2;
  undefined8 uVar3;
  undefined1 auStack_458 [32];
  undefined4 local_438;
  char local_428 [1024];
  ulonglong local_28;
  
  local_28 = DAT_140103510 ^ (ulonglong)auStack_458;
  if (param_3 == (longlong *)0x0) {
    local_438 = 0x5c;
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  else if (*(char *)(param_1 + 0x10) == '\0') {
    local_438 = param_2;
    sprintf(local_428,"SELECT * FROM %s WHERE %s=%lu LIMIT 1");
    plVar1 = (longlong *)(**(code **)(*param_3 + 0x10))(param_3,local_428,2);
    if (plVar1 != (longlong *)0x0) {
      lVar2 = (**(code **)(*plVar1 + 0x40))(plVar1);
      if (lVar2 == 0) {
        uVar3 = (**(code **)(*param_3 + 0x20))(param_3,s_cq_monster_cluster_140102f68);
      }
      else {
        uVar3 = (**(code **)(*plVar1 + 0x38))(plVar1);
      }
      *(undefined8 *)(param_1 + 8) = uVar3;
      (**(code **)*plVar1)(plVar1);
    }
  }
  else {
    local_438 = 0x5e;
    log_InlineLogERROR(&DAT_1400be0b0);
  }
  __security_check_cookie(local_28 ^ (ulonglong)auStack_458);
  return;
}


// ==== CGameData<&char*_szMonsterClusterTable,&char*_szID>::vf_0x0 @ 140060a60  undefined8 * vf_0x0(undefined8 * param_1, uint param_2, undefined8 param_3, undefined8 param_4)

undefined8 *
CGameData<&char*_szMonsterClusterTable,&char*_szID>::vf_0x0
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


