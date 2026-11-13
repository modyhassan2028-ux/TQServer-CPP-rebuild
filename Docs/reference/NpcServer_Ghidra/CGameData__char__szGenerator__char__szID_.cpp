// NpcServer.exe :: CGameData<&char*_szGenerator,&char*_szID>  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CGameData<&char*_szGenerator,&char*_szID>::vf_0x8 @ 1400601e0  undefined vf_0x8(longlong param_1)

void CGameData<&char*_szGenerator,&char*_szID>::vf_0x8(longlong param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)
           (**(code **)(**(longlong **)(param_1 + 8) + 0x20))
                     (*(longlong **)(param_1 + 8),&DAT_140102d90);
                    /* WARNING: Could not recover jumptable at 0x0001400601ff. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x40))(plVar1);
  return;
}


// ==== CGameData<&char*_szGenerator,&char*_szID>::vf_0x10 @ 140060210  undefined vf_0x10(longlong param_1)

void CGameData<&char*_szGenerator,&char*_szID>::vf_0x10(longlong param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(**(code **)(**(longlong **)(param_1 + 8) + 0x10))();
                    /* WARNING: Could not recover jumptable at 0x000140060228. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x48))(plVar1);
  return;
}


// ==== CGameData<&char*_szGenerator,&char*_szID>::vf_0x18 @ 140060230  undefined vf_0x18(longlong param_1)

void CGameData<&char*_szGenerator,&char*_szID>::vf_0x18(longlong param_1)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(**(code **)(**(longlong **)(param_1 + 8) + 0x10))();
                    /* WARNING: Could not recover jumptable at 0x000140060248. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x78))(plVar1);
  return;
}


// ==== CGameData<&char*_szGenerator,&char*_szID>::vf_0x20 @ 140060250  undefined vf_0x20(longlong param_1)

void CGameData<&char*_szGenerator,&char*_szID>::vf_0x20(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x000140060257. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(longlong **)(param_1 + 8) + 0x58))();
  return;
}


// ==== CGameData<&char*_szGenerator,&char*_szID>::vf_0x28 @ 140060260  undefined vf_0x28(longlong param_1, undefined4 param_2, longlong * param_3)

void CGameData<&char*_szGenerator,&char*_szID>::vf_0x28
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
        uVar3 = (**(code **)(*param_3 + 0x20))(param_3,s_cq_generator_140102f58);
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


// ==== CGameData<&char*_szGenerator,&char*_szID>::vf_0x30 @ 1400603a0  bool vf_0x30(longlong param_1, longlong * param_2)

bool CGameData<&char*_szGenerator,&char*_szID>::vf_0x30(longlong param_1,longlong *param_2)

{
  longlong lVar1;
  
  if (*(char *)(param_1 + 0x10) != '\0') {
    log_InlineLogERROR(&DAT_1400be0b0);
    return false;
  }
  lVar1 = (**(code **)(*param_2 + 0x38))(param_2);
  *(longlong *)(param_1 + 8) = lVar1;
  return lVar1 != 0;
}


// ==== CGameData<&char*_szGenerator,&char*_szID>::vf_0x38 @ 140060400  bool vf_0x38(longlong param_1, undefined8 param_2)

bool CGameData<&char*_szGenerator,&char*_szID>::vf_0x38(longlong param_1,undefined8 param_2)

{
  longlong *plVar1;
  longlong lVar2;
  
  plVar1 = (longlong *)InstanceGet();
  lVar2 = (**(code **)(*plVar1 + 0x20))(plVar1,param_2);
  *(longlong *)(param_1 + 8) = lVar2;
  return lVar2 != 0;
}


// ==== CGameData<&char*_szGenerator,&char*_szID>::vf_0x40 @ 140060440  bool vf_0x40(longlong param_1)

bool CGameData<&char*_szGenerator,&char*_szID>::vf_0x40(longlong param_1)

{
  longlong *plVar1;
  longlong lVar2;
  
  plVar1 = (longlong *)InstanceGet();
  lVar2 = (**(code **)(*plVar1 + 0x20))(plVar1,s_cq_generator_140102f58);
  *(longlong *)(param_1 + 8) = lVar2;
  return lVar2 != 0;
}


// ==== CGameData<&char*_szGenerator,&char*_szID>::vf_0x48 @ 140060470  ulonglong vf_0x48(longlong param_1)

ulonglong CGameData<&char*_szGenerator,&char*_szID>::vf_0x48(longlong param_1)

{
  ulonglong extraout_RAX;
  ulonglong uVar1;
  
  if (*(char *)(param_1 + 0x10) != '\0') {
    log_InlineLogERROR(&DAT_1400be0b0);
    return extraout_RAX & 0xffffffffffffff00;
  }
                    /* WARNING: Could not recover jumptable at 0x0001400604b6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (**(code **)(**(longlong **)(param_1 + 8) + 0x40))();
  return uVar1;
}


// ==== CGameData<&char*_szGenerator,&char*_szID>::vf_0x50 @ 1400604c0  undefined vf_0x50(longlong param_1)

void CGameData<&char*_szGenerator,&char*_szID>::vf_0x50(longlong param_1)

{
  longlong *plVar1;
  
  (**(code **)(**(longlong **)(param_1 + 8) + 0x50))(*(longlong **)(param_1 + 8),1);
  plVar1 = (longlong *)
           (**(code **)(**(longlong **)(param_1 + 8) + 0x20))
                     (*(longlong **)(param_1 + 8),&DAT_140102d90);
                    /* WARNING: Could not recover jumptable at 0x0001400604f1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x40))(plVar1);
  return;
}


// ==== CGameData<&char*_szGenerator,&char*_szID>::vf_0x58 @ 140060500  undefined vf_0x58(undefined8 * param_1)

void CGameData<&char*_szGenerator,&char*_szID>::vf_0x58(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    (**(code **)*param_1)(param_1,1);
  }
  return;
}


// ==== CGameData<&char*_szGenerator,&char*_szID>::vf_0x60 @ 140060520  undefined vf_0x60(longlong param_1, undefined8 param_2, undefined4 param_3)

void CGameData<&char*_szGenerator,&char*_szID>::vf_0x60
               (longlong param_1,undefined8 param_2,undefined4 param_3)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(**(code **)(**(longlong **)(param_1 + 8) + 0x10))();
                    /* WARNING: Could not recover jumptable at 0x000140060540. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0xb0))(plVar1,param_3);
  return;
}


// ==== CGameData<&char*_szGenerator,&char*_szID>::vf_0x68 @ 140060550  undefined vf_0x68(longlong param_1, undefined8 param_2, undefined8 param_3)

void CGameData<&char*_szGenerator,&char*_szID>::vf_0x68
               (longlong param_1,undefined8 param_2,undefined8 param_3)

{
  longlong *plVar1;
  
  plVar1 = (longlong *)(**(code **)(**(longlong **)(param_1 + 8) + 0x10))();
                    /* WARNING: Could not recover jumptable at 0x000140060571. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x80))(plVar1,param_3);
  return;
}


// ==== CGameData<&char*_szGenerator,&char*_szID>::vf_0x70 @ 140060580  undefined8 vf_0x70(longlong param_1)

undefined8 CGameData<&char*_szGenerator,&char*_szID>::vf_0x70(longlong param_1)

{
  undefined8 in_RAX;
  undefined8 uVar1;
  
  if (*(char *)(param_1 + 0x10) == '\0') {
                    /* WARNING: Could not recover jumptable at 0x00014006058f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(**(longlong **)(param_1 + 8) + 0x38))(*(longlong **)(param_1 + 8),0);
    return uVar1;
  }
  return CONCAT71((int7)((ulonglong)in_RAX >> 8),1);
}


// ==== CGameData<&char*_szGenerator,&char*_szID>::vf_0x0 @ 1400605a0  undefined8 * vf_0x0(undefined8 * param_1, uint param_2, undefined8 param_3, undefined8 param_4)

undefined8 *
CGameData<&char*_szGenerator,&char*_szID>::vf_0x0
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


