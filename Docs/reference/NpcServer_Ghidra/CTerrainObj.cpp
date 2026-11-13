// NpcServer.exe :: CTerrainObj  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CTerrainObj::vf_0x8 @ 1400954b0  undefined vf_0x8(longlong param_1, int param_2, int param_3)

void CTerrainObj::vf_0x8(longlong param_1,int param_2,int param_3)

{
  int *piVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong *plVar4;
  int iVar5;
  int iVar6;
  longlong *plVar7;
  longlong lVar8;
  undefined8 uVar9;
  longlong *plVar10;
  longlong *plVar11;
  
  uVar9 = 0xfffffffffffffffe;
  CMapObj::vf_0x8(param_1,param_2,param_3);
  plVar7 = *(longlong **)(param_1 + 0x38);
  if (*(longlong **)(param_1 + 0x40) < plVar7) {
    _invalid_parameter_noinfo();
  }
  plVar2 = *(longlong **)(param_1 + 0x20);
  while( true ) {
    plVar3 = *(longlong **)(param_1 + 0x40);
    if (plVar3 < *(longlong **)(param_1 + 0x38)) {
      _invalid_parameter_noinfo();
    }
    if ((plVar2 == (longlong *)0x0) || (plVar2 != *(longlong **)(param_1 + 0x20))) {
      _invalid_parameter_noinfo();
    }
    if (plVar7 == plVar3) break;
    if (plVar2 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar8 = 0;
    }
    else {
      lVar8 = *plVar2;
    }
    if (*(longlong **)(lVar8 + 0x20) <= plVar7) {
      _invalid_parameter_noinfo();
    }
    plVar3 = (longlong *)plVar7[1];
    plVar4 = (longlong *)*plVar7;
    if (plVar3 != (longlong *)0x0) {
      LOCK();
      *(int *)(plVar3 + 2) = (int)plVar3[2] + 1;
      UNLOCK();
    }
    plVar10 = plVar4;
    plVar11 = plVar3;
    iVar5 = FUN_140093bd0((longlong)plVar4);
    iVar6 = FUN_140093be0((longlong)plVar4);
    (**(code **)(*plVar4 + 8))(plVar4,param_2 + iVar5,param_3 + iVar6,*plVar4,uVar9,plVar10,plVar11)
    ;
    if (plVar3 != (longlong *)0x0) {
      LOCK();
      plVar4 = plVar3 + 2;
      *(int *)plVar4 = (int)*plVar4 + -1;
      UNLOCK();
      if ((int)*plVar4 == 0) {
        (**(code **)*plVar3)(plVar3);
        LOCK();
        piVar1 = (int *)((longlong)plVar3 + 0x14);
        *piVar1 = *piVar1 + -1;
        UNLOCK();
        if (*piVar1 == 0) {
          (**(code **)(*plVar3 + 8))(plVar3);
        }
      }
    }
    if (plVar2 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar8 = 0;
    }
    else {
      lVar8 = *plVar2;
    }
    if (*(longlong **)(lVar8 + 0x20) <= plVar7) {
      _invalid_parameter_noinfo();
    }
    plVar7 = plVar7 + 2;
  }
  return;
}


// ==== CTerrainObj::vf_0x0 @ 140096300  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CTerrainObj::vf_0x0(undefined8 *param_1,uint param_2)

{
  FUN_1400961b0(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


