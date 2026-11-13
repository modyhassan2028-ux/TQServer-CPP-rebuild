// NpcServer.exe :: CUser  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CUser::vf_0xa8 @ 140065e30  undefined vf_0xa8(longlong param_1, uint param_2)

void CUser::vf_0xa8(longlong param_1,uint param_2)

{
  if (param_2 != *(byte *)(param_1 + 0x8a)) {
    if (*(longlong **)(param_1 + 8) != (longlong *)0x0) {
      FUN_14004c6f0(*(longlong **)(param_1 + 8),(longlong *)(param_1 + -0x10));
      *(char *)(param_1 + 0x8a) = (char)param_2;
      FUN_14004dba0(*(longlong **)(param_1 + 8),(longlong *)(param_1 + -0x10));
      return;
    }
    *(char *)(param_1 + 0x8a) = (char)param_2;
  }
  return;
}


// ==== CUser::vf_0x30 @ 140065f20  undefined vf_0x30(longlong param_1)

void CUser::vf_0x30(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x000140065f27. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(longlong **)(param_1 + 8) + 8))();
  return;
}


// ==== CUser::vf_0x20 @ 140065f50  undefined vf_0x20(longlong * param_1)

void CUser::vf_0x20(longlong *param_1)

{
  FUN_140065df0(param_1);
  if (param_1 != (longlong *)0x0) {
    (**(code **)*param_1)(param_1,1);
  }
  return;
}


// ==== CUser::vf_0x10 @ 140066780  int vf_0x10(longlong * param_1, int param_2)

int CUser::vf_0x10(longlong *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  undefined8 *puVar4;
  longlong *plVar5;
  
  if ((int)param_1[0xc] != 0) {
    lVar3 = FUN_14001c200();
    lVar3 = FUN_14001cab0(lVar3);
    puVar4 = (undefined8 *)FUN_14001dd90(lVar3);
    if (puVar4 != (undefined8 *)0x0) {
      plVar5 = (longlong *)(**(code **)(*(longlong *)*puVar4 + 0x10))((longlong *)*puVar4,0x20);
      iVar1 = (**(code **)(*plVar5 + 0x48))(plVar5);
      iVar2 = (**(code **)(*param_1 + 0x48))(param_1);
      return (iVar2 + 1 + param_2) / 2 + iVar1;
    }
  }
  iVar1 = (**(code **)(*param_1 + 0x48))(param_1);
  return (iVar1 + 1 + param_2) / 2 + 1;
}


// ==== CUser::vf_0x90 @ 140066ad0  undefined vf_0x90(longlong param_1, uint * param_2)

void CUser::vf_0x90(longlong param_1,uint *param_2)

{
  if ((((((byte)(*param_2 >> 10) ^ (byte)(*(uint *)(param_1 + 0x40) >> 10)) & 1) != 0) ||
      (((byte)((byte)(*param_2 >> 0x18) ^ (byte)(*(uint *)(param_1 + 0x40) >> 0x18)) >> 3 & 1) != 0)
      ) && (*(longlong **)(param_1 + 8) != (longlong *)0x0)) {
    FUN_14004c6f0(*(longlong **)(param_1 + 8),(longlong *)(param_1 + -0x10));
    *(uint *)(param_1 + 0x40) = *param_2;
    *(uint *)(param_1 + 0x44) = param_2[1];
    *(uint *)(param_1 + 0x48) = param_2[2];
    *(uint *)(param_1 + 0x4c) = param_2[3];
    *(uint *)(param_1 + 0x50) = param_2[4];
    *(uint *)(param_1 + 0x54) = param_2[5];
    FUN_14004dba0(*(longlong **)(param_1 + 8),(longlong *)(param_1 + -0x10));
    return;
  }
  *(uint *)(param_1 + 0x40) = *param_2;
  *(uint *)(param_1 + 0x44) = param_2[1];
  *(uint *)(param_1 + 0x48) = param_2[2];
  *(uint *)(param_1 + 0x4c) = param_2[3];
  *(uint *)(param_1 + 0x50) = param_2[4];
  *(uint *)(param_1 + 0x54) = param_2[5];
  return;
}


// ==== CUser::vf_0x8 @ 140066bf0  int vf_0x8(longlong * param_1, int param_2, int param_3)

int CUser::vf_0x8(longlong *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = (**(code **)(*param_1 + 0x38))();
  uVar3 = param_2 - iVar1 >> 0x1f;
  iVar2 = (**(code **)(*param_1 + 0x40))(param_1);
  uVar4 = param_3 - iVar2 >> 0x1f;
  if ((int)((param_3 - iVar2 ^ uVar4) - uVar4) < (int)((param_2 - iVar1 ^ uVar3) - uVar3)) {
    iVar1 = (**(code **)(*param_1 + 0x38))();
    uVar3 = param_2 - iVar1;
  }
  else {
    iVar1 = (**(code **)(*param_1 + 0x40))(param_1);
    uVar3 = param_3 - iVar1;
  }
  return (uVar3 ^ (int)uVar3 >> 0x1f) - ((int)uVar3 >> 0x1f);
}


// ==== CUser::vf_0x18 @ 140066c70  undefined1 vf_0x18(longlong param_1)

undefined1 CUser::vf_0x18(longlong param_1)

{
  return *(undefined1 *)(param_1 + 0x82);
}


// ==== CUser::vf_0x20 @ 140066c80  undefined4 * vf_0x20(longlong param_1, undefined4 * param_2)

undefined4 * CUser::vf_0x20(longlong param_1,undefined4 *param_2)

{
  *param_2 = *(undefined4 *)(param_1 + 0x40);
  param_2[1] = *(undefined4 *)(param_1 + 0x44);
  param_2[2] = *(undefined4 *)(param_1 + 0x48);
  param_2[3] = *(undefined4 *)(param_1 + 0x4c);
  param_2[4] = *(undefined4 *)(param_1 + 0x50);
  param_2[5] = *(undefined4 *)(param_1 + 0x54);
  return param_2;
}


// ==== CUser::vf_0x8 @ 140066cb0  undefined4 vf_0x8(longlong param_1)

undefined4 CUser::vf_0x8(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x20);
}


// ==== CUser::vf_0x38 @ 140066cc0  undefined2 vf_0x38(longlong param_1)

undefined2 CUser::vf_0x38(longlong param_1)

{
  return *(undefined2 *)(param_1 + 0x7e);
}


// ==== CUser::vf_0x40 @ 140066cd0  undefined2 vf_0x40(longlong param_1)

undefined2 CUser::vf_0x40(longlong param_1)

{
  return *(undefined2 *)(param_1 + 0x80);
}


// ==== CUser::vf_0x48 @ 140066ce0  undefined1 vf_0x48(longlong param_1)

undefined1 CUser::vf_0x48(longlong param_1)

{
  return *(undefined1 *)(param_1 + 0x8a);
}


// ==== CUser::vf_0x80 @ 140066cf0  undefined8 vf_0x80(longlong param_1)

undefined8 CUser::vf_0x80(longlong param_1)

{
  return *(undefined8 *)(param_1 + 8);
}


// ==== CUser::vf_0x88 @ 140066d00  longlong vf_0x88(longlong param_1)

longlong CUser::vf_0x88(longlong param_1)

{
  return param_1 + 0x98;
}


// ==== CUser::vf_0x98 @ 140066d10  undefined vf_0x98(void)

void CUser::vf_0x98(void)

{
  return;
}


// ==== CUser::vf_0xa0 @ 140066d20  undefined vf_0xa0(void)

void CUser::vf_0xa0(void)

{
  return;
}


// ==== CUser::vf_0xb0 @ 140066d30  undefined vf_0xb0(longlong param_1, int param_2, longlong * param_3)

void CUser::vf_0xb0(longlong param_1,int param_2,longlong *param_3)

{
  longlong lVar1;
  
  lVar1 = 0;
  if (param_2 == 0x1001) {
    lVar1 = param_1 + -0x10;
  }
  if (param_3 != (longlong *)0x0) {
    *param_3 = lVar1;
  }
  return;
}


// ==== CUser::vf_0x28 @ 140066d60  undefined vf_0x28(longlong param_1)

void CUser::vf_0x28(longlong param_1)

{
  vf_0x8(param_1 + -0x10);
  return;
}


// ==== CUser::vf_0x0 @ 140066d70  undefined vf_0x0(longlong param_1, uint param_2)

void CUser::vf_0x0(longlong param_1,uint param_2)

{
  vf_0x0((undefined8 *)(param_1 + -0x10),param_2);
  return;
}


// ==== CUser::vf_0x60 @ 140066d80  bool vf_0x60(longlong param_1)

bool CUser::vf_0x60(longlong param_1)

{
  return *(int *)(param_1 + 100) != 0;
}


// ==== CUser::vf_0x50 @ 140066d90  ulonglong vf_0x50(longlong * param_1)

ulonglong CUser::vf_0x50(longlong *param_1)

{
  uint *puVar1;
  undefined1 local_28 [40];
  
  puVar1 = (uint *)(**(code **)(*param_1 + 0x20))(param_1,local_28);
  return CONCAT71((int7)((ulonglong)puVar1 >> 8),~(byte)(*puVar1 >> 5)) & 0xffffffffffffff01;
}


// ==== CUser::vf_0x58 @ 140066db0  undefined8 vf_0x58(longlong * param_1)

ulonglong CUser::vf_0x58(longlong *param_1)

{
  uint *puVar1;
  undefined1 local_38 [24];
  undefined1 local_20 [24];
  
  puVar1 = (uint *)(**(code **)(*param_1 + 0x20))(param_1,local_38);
  if ((*puVar1 >> 0xf & 1) == 0) {
    puVar1 = (uint *)(**(code **)(*param_1 + 0x20))(param_1,local_20);
    if ((*puVar1 & 1) == 0) {
      return (ulonglong)puVar1 & 0xffffffffffffff00;
    }
  }
  return CONCAT71((int7)((ulonglong)puVar1 >> 8),1);
}


// ==== CUser::vf_0x68 @ 140066e00  uint vf_0x68(longlong * param_1)

uint CUser::vf_0x68(longlong *param_1)

{
  uint *puVar1;
  undefined1 local_28 [40];
  
  puVar1 = (uint *)(**(code **)(*param_1 + 0x20))(param_1,local_28);
  return *puVar1 >> 0x16 & 0xffffff01;
}


// ==== CUser::vf_0x70 @ 140066e20  ulonglong vf_0x70(longlong * param_1)

ulonglong CUser::vf_0x70(longlong *param_1)

{
  uint *puVar1;
  undefined1 local_28 [40];
  
  puVar1 = (uint *)(**(code **)(*param_1 + 0x20))(param_1,local_28);
  return CONCAT71((int7)((ulonglong)puVar1 >> 8),~(byte)(*puVar1 >> 0xf)) & 0xffffffffffffff01;
}


// ==== CUser::vf_0x78 @ 140066e40  uint vf_0x78(longlong * param_1)

uint CUser::vf_0x78(longlong *param_1)

{
  uint *puVar1;
  undefined1 local_28 [40];
  
  puVar1 = (uint *)(**(code **)(*param_1 + 0x20))(param_1,local_28);
  return *puVar1 >> 0x1b & 0xffffff01;
}


// ==== CUser::vf_0x0 @ 140066f50  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CUser::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  param_1[2] = vftable;
  FUN_14005a970(param_1 + 0x15);
  param_1[2] = IRole::vftable;
  FUN_1400695e0(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


