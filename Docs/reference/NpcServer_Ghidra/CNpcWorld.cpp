// NpcServer.exe :: CNpcWorld  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CNpcWorld::vf_0x10 @ 14001c180  undefined8 vf_0x10(longlong * param_1)

undefined8 CNpcWorld::vf_0x10(longlong *param_1)

{
  if (param_1 != (longlong *)0x0) {
    (**(code **)(*param_1 + 0x30))(param_1,1);
  }
  return 0;
}


// ==== CNpcWorld::vf_0x28 @ 14001c1a0  undefined vf_0x28(void)

void CNpcWorld::vf_0x28(void)

{
  return;
}


// ==== CNpcWorld::vf_0x18 @ 14001c570  undefined vf_0x18(undefined8 param_1, uint param_2, longlong param_3, int param_4, undefined4 param_5)

void CNpcWorld::vf_0x18(undefined8 param_1,uint param_2,longlong param_3,int param_4,
                       undefined4 param_5)

{
  longlong *plVar1;
  
  if (((param_3 != 0) && (param_4 - 1U < 0x400)) &&
     (plVar1 = FUN_1400349a0(param_5,param_2,param_3,param_4), plVar1 != (longlong *)0x0)) {
    (**(code **)(*plVar1 + 0x18))(plVar1,param_1);
    (**(code **)*plVar1)(plVar1,1);
  }
  return;
}


// ==== CNpcWorld::vf_0x8 @ 14001c5e0  undefined vf_0x8(longlong param_1)

void CNpcWorld::vf_0x8(longlong param_1)

{
  *(undefined4 *)(param_1 + 8) = 3;
  return;
}


// ==== CNpcWorld::vf_0x30 @ 14001cf50  undefined8 * vf_0x30(undefined8 * param_1, ulonglong param_2, undefined8 param_3, undefined8 param_4)

undefined8 *
CNpcWorld::vf_0x30(undefined8 *param_1,ulonglong param_2,undefined8 param_3,undefined8 param_4)

{
  FUN_14001cce0(param_1,param_2,param_3,param_4);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CNpcWorld::vf_0x0 @ 14001cf80  longlong * vf_0x0(longlong param_1, longlong param_2)

longlong * CNpcWorld::vf_0x0(longlong param_1,longlong param_2)

{
  int *piVar1;
  longlong lVar2;
  ulong uVar3;
  uint uVar4;
  ulonglong extraout_RAX;
  longlong *plVar5;
  undefined8 *puVar6;
  longlong *plVar7;
  undefined4 *puVar8;
  ulonglong uVar9;
  undefined8 uVar10;
  undefined8 local_20;
  longlong *local_18;
  
  if (param_2 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    plVar5 = (longlong *)(extraout_RAX & 0xffffffffffffff00);
  }
  else {
    *(longlong *)(param_1 + 0x10) = param_2;
    DAT_1401045b8 = param_1;
    *(undefined4 *)(param_1 + 0x18) = 5;
    uVar3 = tq::TimeGet(0);
    *(uint *)(param_1 + 0x1c) = uVar3 / 1000;
    *(undefined4 *)(param_1 + 0x20) = 10;
    uVar3 = tq::TimeGet(0);
    *(uint *)(param_1 + 0x24) = uVar3 / 1000;
    plVar5 = (longlong *)InstanceGet();
    plVar5 = (longlong *)
             (**(code **)(*plVar5 + 0x10))(plVar5,"SELECT * FROM cq_map WHERE id=0 LIMIT 1",2);
    *(longlong **)(param_1 + 0x48) = plVar5;
    if (plVar5 != (longlong *)0x0) {
      (**(code **)**(undefined8 **)(param_1 + 0x10))
                (*(undefined8 **)(param_1 + 0x10),"Create map set...");
      puVar6 = (undefined8 *)operator_new(0x18);
      plVar5 = (longlong *)0x0;
      plVar7 = plVar5;
      if (puVar6 != (undefined8 *)0x0) {
        plVar7 = FUN_14003e4e0(puVar6);
      }
      *(longlong **)(param_1 + 0x28) = plVar7;
      if ((plVar7 == (longlong *)0x0) ||
         (plVar7 = FUN_14003c390((longlong)plVar7), (char)plVar7 == '\0')) {
        plVar5 = (longlong *)((ulonglong)plVar7 & 0xffffffffffffff00);
      }
      else {
        (**(code **)**(undefined8 **)(param_1 + 0x10))
                  (*(undefined8 **)(param_1 + 0x10),"Create player set...");
        puVar6 = (undefined8 *)operator_new(0x10);
        plVar7 = plVar5;
        if (puVar6 != (undefined8 *)0x0) {
          plVar7 = FUN_14003bf40(puVar6);
        }
        *(longlong **)(param_1 + 0x38) = plVar7;
        if ((plVar7 == (longlong *)0x0) ||
           (plVar7 = (longlong *)FUN_14003bf90((longlong)plVar7), (char)plVar7 == '\0')) {
          plVar5 = (longlong *)((ulonglong)plVar7 & 0xffffffffffffff00);
        }
        else {
          (**(code **)**(undefined8 **)(param_1 + 0x10))
                    (*(undefined8 **)(param_1 + 0x10),"Create npc set...");
          puVar8 = (undefined4 *)operator_new(0x128);
          if (puVar8 != (undefined4 *)0x0) {
            plVar5 = (longlong *)FUN_1400345d0(puVar8);
          }
          *(longlong **)(param_1 + 0x30) = plVar5;
          if ((plVar5 == (longlong *)0x0) ||
             (plVar5 = FUN_140032800((longlong)plVar5), (char)plVar5 == '\0')) {
            plVar5 = (longlong *)((ulonglong)plVar5 & 0xffffffffffffff00);
          }
          else {
            plVar5 = FUN_140025a10();
            *(longlong **)(param_1 + 0x40) = plVar5;
            if (plVar5 != (longlong *)0x0) {
              (**(code **)**(undefined8 **)(param_1 + 0x10))
                        (*(undefined8 **)(param_1 + 0x10),"Create NPC protect path...");
              plVar5 = FUN_140037df0();
              *(longlong **)(param_1 + 0x50) = plVar5;
              if (plVar5 != (longlong *)0x0) {
                puVar6 = FUN_14001beb0();
                local_20 = 0;
                local_18 = (longlong *)0x0;
                FUN_14001cbb0(&local_20,puVar6);
                plVar5 = local_18;
                uVar9 = FUN_14001c830((undefined8 *)(param_1 + 0x58),local_20,(longlong)local_18);
                plVar7 = local_18;
                if (plVar5 != (longlong *)0x0) {
                  LOCK();
                  plVar5 = plVar5 + 2;
                  lVar2 = *plVar5;
                  *(int *)plVar5 = (int)*plVar5 + -1;
                  UNLOCK();
                  uVar4 = (int)lVar2 - 1;
                  uVar9 = (ulonglong)uVar4;
                  if (uVar4 == 0) {
                    uVar9 = (**(code **)*local_18)(local_18);
                    LOCK();
                    piVar1 = (int *)((longlong)plVar7 + 0x14);
                    *piVar1 = *piVar1 + -1;
                    UNLOCK();
                    if (*piVar1 == 0) {
                      uVar9 = (**(code **)(*local_18 + 8))();
                    }
                  }
                }
                if ((*(longlong *)(param_1 + 0x58) == 0) ||
                   (uVar9 = FUN_140021020(*(longlong *)(param_1 + 0x58)), (char)uVar9 == '\0')) {
                  plVar5 = (longlong *)(uVar9 & 0xffffffffffffff00);
                }
                else {
                  uVar10 = (**(code **)**(undefined8 **)(param_1 + 0x10))
                                     (*(undefined8 **)(param_1 + 0x10),
                                      "======== Create cq server kernel ok! ========");
                  plVar5 = (longlong *)CONCAT71((int7)((ulonglong)uVar10 >> 8),1);
                }
              }
            }
          }
        }
      }
    }
  }
  return plVar5;
}


// ==== CNpcWorld::vf_0x20 @ 14001d390  undefined vf_0x20(ulonglong param_1)

void CNpcWorld::vf_0x20(ulonglong param_1)

{
  char cVar1;
  ulong uVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  ulonglong uVar6;
  longlong lVar7;
  longlong lVar8;
  undefined8 uVar9;
  ulonglong uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  longlong *plVar14;
  undefined1 auStack_938 [32];
  int local_918;
  int local_910;
  int local_908;
  undefined8 local_900;
  longlong local_8f8;
  longlong local_8f0;
  longlong local_8e8;
  int local_8e0;
  int local_8d8;
  int local_8d0;
  longlong local_8c8;
  undefined4 local_8c0;
  longlong local_8b8;
  int local_8b0 [2];
  longlong *local_8a8;
  longlong local_8a0;
  int local_898;
  int local_894;
  int local_890;
  int local_88c;
  longlong local_888;
  ulonglong local_880;
  longlong local_878;
  ulonglong local_870;
  ulonglong local_868;
  undefined8 local_860;
  CTickAnalyst local_858 [32];
  char local_838 [2048];
  ulonglong local_38;
  
  local_860 = 0xfffffffffffffffe;
  local_38 = DAT_140103510 ^ (ulonglong)auStack_938;
  local_880 = param_1;
  cVar1 = (**(code **)(**(longlong **)(param_1 + 0x10) + 0x28))();
  if (cVar1 != '\0') {
    iVar11 = *(int *)(param_1 + 8);
    if (iVar11 == 2) {
      if (*(int *)(param_1 + 0x1c) == 0) {
        FUN_14003c520();
        FUN_140037f80(*(longlong **)(param_1 + 0x38));
        CTickAnalyst::CTickAnalyst(local_858,0x51);
        FUN_14002b380(*(longlong *)(param_1 + 0x30));
        CTickAnalyst::~CTickAnalyst(local_858);
        lVar4 = FUN_14001d230();
        FUN_1400489b0(lVar4);
        uVar2 = tq::TimeGet(0);
        if ((uint)(*(int *)(param_1 + 0x20) + *(int *)(param_1 + 0x24)) <= uVar2 / 1000) {
          uVar2 = tq::TimeGet(0);
          *(uint *)(param_1 + 0x24) = uVar2 / 1000;
          iVar11 = 0;
          local_894 = 0;
          iVar12 = 0;
          local_88c = 0;
          iVar13 = 0;
          local_890 = 0;
          local_8b8 = 0;
          lVar4 = 0;
          local_888 = 0;
          local_8a0 = 0;
          local_868 = 0;
          while( true ) {
            uVar10 = local_868;
            plVar5 = (longlong *)FUN_140025b50(*(longlong *)(DAT_1401045b8 + 0x30));
            uVar6 = (**(code **)(*plVar5 + 0x10))(plVar5);
            if (uVar6 <= uVar10) break;
            plVar5 = (longlong *)FUN_140025b50(*(longlong *)(DAT_1401045b8 + 0x30));
            plVar5 = (longlong *)
                     (**(code **)(*plVar5 + 0x18))
                               (plVar5,uVar10,
                                "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\npcworld.cpp"
                                ,0xda);
            if (plVar5 != (longlong *)0x0) {
              iVar3 = (**(code **)(*plVar5 + 0x30))(plVar5);
              plVar14 = (longlong *)(longlong)iVar3;
              iVar3 = (**(code **)(*plVar5 + 0x48))(plVar5);
              local_8a8 = (longlong *)(longlong)iVar3;
              if (plVar14 < local_8a8) {
                iVar11 = iVar11 + 1;
                local_894 = iVar11;
              }
              else if (local_8a8 == plVar14) {
                iVar12 = iVar12 + 1;
                local_88c = iVar12;
              }
              else {
                iVar13 = iVar13 + 1;
                local_890 = iVar13;
              }
              local_8b8 = local_8b8 + (longlong)plVar14;
              iVar3 = (**(code **)(*plVar5 + 0x20))(plVar5);
              lVar4 = local_888 + iVar3;
              local_8a0 = local_8a0 + (longlong)local_8a8;
              local_888 = lVar4;
            }
            local_868 = uVar10 + 1;
          }
          local_870 = 0;
          while( true ) {
            uVar10 = local_870;
            plVar5 = (longlong *)FUN_140025ba0(*(longlong *)(DAT_1401045b8 + 0x30));
            uVar6 = (**(code **)(*plVar5 + 0x10))(plVar5);
            if (uVar6 <= uVar10) break;
            plVar5 = (longlong *)FUN_140025ba0(*(longlong *)(DAT_1401045b8 + 0x30));
            plVar5 = (longlong *)
                     (**(code **)(*plVar5 + 0x18))
                               (plVar5,uVar10,
                                "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\npcworld.cpp"
                                ,0xf1);
            if (plVar5 != (longlong *)0x0) {
              iVar3 = (**(code **)(*plVar5 + 0x30))(plVar5);
              plVar14 = (longlong *)(longlong)iVar3;
              iVar3 = (**(code **)(*plVar5 + 0x48))(plVar5);
              local_8a8 = (longlong *)(longlong)iVar3;
              if (plVar14 < local_8a8) {
                iVar11 = iVar11 + 1;
                local_894 = iVar11;
              }
              else if (local_8a8 == plVar14) {
                iVar12 = iVar12 + 1;
                local_88c = iVar12;
              }
              else {
                iVar13 = iVar13 + 1;
                local_890 = iVar13;
              }
              local_8b8 = local_8b8 + (longlong)plVar14;
              iVar3 = (**(code **)(*plVar5 + 0x20))(plVar5);
              lVar4 = local_888 + iVar3;
              local_8a0 = local_8a0 + (longlong)local_8a8;
              local_888 = lVar4;
            }
            local_870 = uVar10 + 1;
          }
          local_880 = local_880 & 0xffffffff00000000;
          local_8b0[0] = 0;
          local_898 = 0;
          FUN_140038090(*(longlong *)(DAT_1401045b8 + 0x38),(int *)&local_880,local_8b0,&local_898);
          local_8a8 = (longlong *)FUN_140025b50(*(longlong *)(DAT_1401045b8 + 0x30));
          plVar5 = (longlong *)FUN_140025ba0(*(longlong *)(DAT_1401045b8 + 0x30));
          plVar14 = (longlong *)FUN_140025c40(*(longlong *)(DAT_1401045b8 + 0x30));
          local_878 = *(longlong *)(DAT_1401045b8 + 0x30);
          lVar7 = (**(code **)(*plVar5 + 0x10))(plVar5);
          lVar8 = (**(code **)(*local_8a8 + 0x10))(local_8a8);
          uVar9 = (**(code **)(*plVar14 + 0x48))(plVar14);
          local_908 = FUN_14002b6a0(local_878);
          local_8c0 = *(undefined4 *)(param_1 + 0xc);
          local_8e8 = local_8a0;
          local_8f0 = local_8b8;
          local_910 = local_898;
          local_918 = local_8b0[0];
          local_900 = uVar9;
          local_8f8 = lVar4;
          local_8e0 = iVar11;
          local_8d8 = iVar12;
          local_8d0 = iVar13;
          local_8c8 = lVar7 + lVar8;
          _snprintf(local_838,0x800,
                    "Player + Pet + Other: %u + %u + %u\nNPC active / total: %u / %u\nNPC: in game / generated / limit\n\t%d / %d / %d\nGenerator: active+full+over / total\n\t%u + %u + %u / %u\nSynPet: %u"
                    ,local_880 & 0xffffffff);
          (**(code **)(**(longlong **)(param_1 + 0x10) + 0x10))
                    (*(longlong **)(param_1 + 0x10),local_838);
        }
      }
      else {
        uVar2 = tq::TimeGet(0);
        if (*(int *)(param_1 + 0x1c) + 10U <= uVar2 / 1000) {
          *(undefined4 *)(param_1 + 0x1c) = 0;
          *(undefined4 *)(param_1 + 0x18) = 0;
          (**(code **)**(undefined8 **)(param_1 + 0x10))
                    (*(undefined8 **)(param_1 + 0x10),"Generator begin.");
        }
      }
    }
    else if (iVar11 == 1) {
      uVar10 = FUN_14001c2c0(param_1 + 0x18,5);
      if ((char)uVar10 != '\0') {
        (**(code **)**(undefined8 **)(param_1 + 0x10))
                  (*(undefined8 **)(param_1 + 0x10),"Login game server . . .");
      }
    }
    else if (iVar11 == 0) {
      *(undefined4 *)(param_1 + 8) = 1;
      FUN_140048d20((undefined8 *)local_838);
      uVar9 = FUN_140048da0((longlong)local_838,0x3ade68b1,"NpcServer Tqdig","skl8934##VJICW ");
      if ((int)uVar9 != 0) {
        FUN_14001c5f0(param_1,0,(longlong)local_838);
      }
      FUN_140048d70((undefined8 *)local_838);
    }
    else if (iVar11 == 3) {
      *(undefined4 *)(param_1 + 8) = 1;
      FUN_140048d20((undefined8 *)local_838);
      uVar9 = FUN_140048da0((longlong)local_838,0x3ade68b2,"NpcServer Tqdig","skl8934##VJICW ");
      if ((int)uVar9 != 0) {
        FUN_14001c5f0(param_1,0,(longlong)local_838);
      }
      FUN_140048d70((undefined8 *)local_838);
    }
    else {
      local_918 = 0x13c;
      log_InlineLogERROR(&DAT_1400be0b0,"MYASSERT","!\"CNpcWorld::OnTimer\"",
                         "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\npcworld.cpp");
    }
  }
  __security_check_cookie(local_38 ^ (ulonglong)auStack_938);
  return;
}


