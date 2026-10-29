/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void FUN_14001f070(void)
{
  int iVar1;
  char cVar2;
  IAnalyst *pIVar3;
  int iVar4;
  undefined4 *puVar5;
  longlong lVar6;
  longlong lVar7;
  int local_res10 [2];
  undefined8 local_res18;
  undefined8 local_res20;
  longlong local_48;
  undefined4 local_40 [10];
  pIVar3 = Analyst();
  (**(code **)(*(longlong *)pIVar3 + 0x30))(pIVar3,"syslog/analyst");
  iVar4 = DAT_140975998;
  _DAT_140975968 = 0;
  _DAT_140975970 = 0;
  DAT_140975978 = 0;
  DAT_140975980 = 0;
  DAT_140975988 = 0;
  DAT_140975990 = 0;
  _DAT_140975998 = 0;
  pIVar3 = Analyst();
  cVar2 = (**(code **)(*(longlong *)pIVar3 + 0x10))
                    (pIVar3,0x45,&local_res18,&local_res20,local_res10);
  if (cVar2 != '\0') {
    _DAT_140975968 = CONCAT44(DAT_14097596c,local_res10[0]);
    DAT_140975978 = local_res18;
    DAT_140975988 = local_res20;
  }
  pIVar3 = Analyst();
  cVar2 = (**(code **)(*(longlong *)pIVar3 + 0x10))
                    (pIVar3,0x43,&local_res18,&local_res20,local_res10);
  if (cVar2 != '\0') {
    _DAT_140975968 = CONCAT44(local_res10[0],DAT_140975968);
    DAT_140975980 = local_res18;
    DAT_140975990 = local_res20;
  }
  pIVar3 = Analyst();
  cVar2 = (**(code **)(*(longlong *)pIVar3 + 0x10))(pIVar3,0x40,0,0,local_res10);
  iVar1 = DAT_140975970;
  if (cVar2 != '\0') {
    iVar1 = local_res10[0];
  }
  DAT_140975970 = iVar1;
  pIVar3 = Analyst();
  cVar2 = (**(code **)(*(longlong *)pIVar3 + 0x10))(pIVar3,0x41,0,0,local_res10);
  if (cVar2 != '\0') {
    DAT_140975974 = local_res10[0];
  }
  pIVar3 = Analyst();
  cVar2 = (**(code **)(*(longlong *)pIVar3 + 0x10))(pIVar3,0x46,0,0,local_res10);
  if (cVar2 != '\0') {
    iVar4 = iVar4 + local_res10[0];
  }
  LOCK();
  _DAT_140975998 = CONCAT44(DAT_140975998_4,iVar4);
  UNLOCK();
  lVar7 = 0;
  local_40[1] = 0x1d;
  lVar6 = 8;
  local_40[0] = 0;
  local_40[2] = 0x20;
  local_40[3] = 0x23;
  local_40[4] = 0x2b;
  local_40[5] = 0x2f;
  local_40[6] = 0x32;
  local_40[7] = 0x3e;
  local_48 = 0;
  puVar5 = local_40;
  do {
    pIVar3 = Analyst();
    (**(code **)(*(longlong *)pIVar3 + 0x10))(pIVar3,*puVar5,&local_48,0,0);
    lVar7 = lVar7 + local_48;
    puVar5 = puVar5 + 1;
    lVar6 = lVar6 + -1;
  } while (lVar6 != 0);
  LOCK();
  UNLOCK();
  DAT_1409759a8 = lVar7;
  pIVar3 = Analyst();
  (**(code **)(*(longlong *)pIVar3 + 0x28))(pIVar3);
  LOCK();
  _DAT_1409759a0 = _DAT_1409759a0 + 1;
  UNLOCK();
  return;
}
