// NpcServer.exe :: CMsgPlayer  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMsgPlayer::vf_0x8 @ 140063040  ulonglong vf_0x8(longlong param_1, void * param_2, uint param_3)

ulonglong CMsgPlayer::vf_0x8(longlong param_1,void *param_2,uint param_3)

{
  ulonglong uVar1;
  
  uVar1 = CNetMsg::vf_0x8(param_1,param_2,param_3);
  if ((int)uVar1 == 0) {
    return uVar1;
  }
  return (ulonglong)(*(int *)(param_1 + 8) == 0x271e);
}


// ==== CMsgPlayer::vf_0x0 @ 140063080  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMsgPlayer::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  tq::CStringPacker::~CStringPacker((CStringPacker *)(param_1 + 0x84));
  FUN_140034810(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CMsgPlayer::vf_0x18 @ 140063100  undefined vf_0x18(longlong param_1)

void CMsgPlayer::vf_0x18(longlong param_1)

{
  undefined4 uVar1;
  int iVar2;
  longlong *plVar3;
  longlong lVar4;
  undefined8 uVar5;
  longlong *plVar6;
  undefined1 auStack_108 [32];
  undefined4 local_e8;
  int local_d8;
  longlong local_d0 [3];
  undefined4 local_b8;
  char local_b4 [36];
  uint local_90;
  undefined2 local_8c;
  undefined4 local_88 [6];
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined2 local_4c;
  undefined2 local_4a;
  undefined2 local_48;
  undefined1 local_46;
  undefined4 local_44;
  undefined2 local_40;
  undefined1 local_3e;
  undefined2 local_3c;
  char local_38 [40];
  ulonglong local_10;
  
  local_d0[1] = 0xfffffffffffffffe;
  local_10 = DAT_140103510 ^ (ulonglong)auStack_108;
  plVar3 = (longlong *)FUN_14001c210();
  plVar3 = (longlong *)(**(code **)(*plVar3 + 0x10))(plVar3);
  (**(code **)(*plVar3 + 0x28))(plVar3);
  local_38[0] = '\0';
  local_38[1] = '\0';
  local_38[2] = '\0';
  local_38[3] = '\0';
  local_38[4] = '\0';
  local_38[5] = '\0';
  local_38[6] = '\0';
  local_38[7] = '\0';
  local_38[8] = '\0';
  local_38[9] = '\0';
  local_38[10] = '\0';
  local_38[0xb] = '\0';
  local_38[0xc] = '\0';
  local_38[0xd] = '\0';
  local_38[0xe] = '\0';
  local_38[0xf] = '\0';
  local_38[0x10] = '\0';
  local_38[0x11] = '\0';
  local_38[0x12] = '\0';
  local_38[0x13] = '\0';
  local_38[0x14] = '\0';
  local_38[0x15] = '\0';
  local_38[0x16] = '\0';
  local_38[0x17] = '\0';
  local_38[0x18] = '\0';
  local_38[0x19] = '\0';
  local_38[0x1a] = '\0';
  local_38[0x1b] = '\0';
  local_38[0x1c] = '\0';
  local_38[0x1d] = '\0';
  local_38[0x1e] = '\0';
  local_38[0x1f] = '\0';
  local_38[0x20] = '\0';
  local_38[0x21] = '\0';
  local_38[0x22] = '\0';
  local_38[0x23] = 0;
  tq::CStringPacker::GetString((CStringPacker *)(param_1 + 0x420),0,local_38,0x24);
  for (local_d8 = 5; -1 < local_d8; local_d8 = local_d8 + -1) {
    local_88[local_d8] = 0;
  }
  memset(&local_b8,0,0x80);
  local_b8 = *(undefined4 *)(*(longlong *)(param_1 + 0x418) + 8);
  tq::SafeCopy(local_b4,local_38,0x24);
  lVar4 = *(longlong *)(param_1 + 0x418);
  local_90 = *(uint *)(lVar4 + 4);
  local_8c = *(undefined2 *)(lVar4 + 0x6f);
  FUN_140061d80(lVar4 + 0x16,(longlong)local_88);
  lVar4 = *(longlong *)(param_1 + 0x418);
  local_50 = *(undefined4 *)(lVar4 + 0x10);
  local_54 = *(undefined4 *)(lVar4 + 0xc);
  local_4c = *(undefined2 *)(lVar4 + 0x14);
  local_70 = *(undefined4 *)(lVar4 + 0x30);
  local_6c = *(undefined4 *)(lVar4 + 0x38);
  local_68 = *(undefined4 *)(lVar4 + 0x40);
  local_64 = *(undefined4 *)(lVar4 + 0x3c);
  local_60 = *(undefined4 *)(lVar4 + 0x4c);
  local_5c = *(undefined4 *)(lVar4 + 0x50);
  local_58 = *(undefined4 *)(lVar4 + 0x67);
  local_4a = *(undefined2 *)(lVar4 + 0x6b);
  local_48 = *(undefined2 *)(lVar4 + 0x6d);
  local_46 = *(undefined1 *)(lVar4 + 0x71);
  local_44 = *(undefined4 *)(lVar4 + 0x72);
  local_40 = *(undefined2 *)(lVar4 + 0x76);
  local_3c = *(undefined2 *)(lVar4 + 0x7a);
  local_3e = 0;
  if (local_90 / 10000000 != 0) {
    uVar1 = FUN_14003b9a0(local_90 / 10000000);
    local_3e = (undefined1)uVar1;
  }
  uVar1 = *(undefined4 *)(param_1 + 0x410);
  lVar4 = FUN_14001c7a0();
  plVar3 = (longlong *)FUN_140027a40(lVar4,uVar1);
  if (plVar3 != (longlong *)0x0) {
    lVar4 = FUN_14001c7a0();
    lVar4 = FUN_140027a40(lVar4,local_b8);
    if (lVar4 == 0) {
      iVar2 = (**(code **)(*plVar3 + 0x30))(plVar3);
      if (iVar2 == 0) {
        local_e8 = 0x61;
        log_InlineLogERROR(&DAT_1400be0b0,"MYASSERT","idMap",
                           "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\network\\msgplayer.cpp"
                          );
      }
      else {
        local_d0[0] = 0;
        (**(code **)(*plVar3 + 0xb0))(plVar3,0x1040,local_d0);
        if (local_d0[0] != 0) {
          FUN_140057c10(local_d0[0]);
        }
        plVar3 = FUN_140066fd0();
        if (plVar3 == (longlong *)0x0) {
          local_e8 = 0x6d;
          log_InlineLogERROR(&DAT_1400be0b0,"MYASSERT","pUser",
                             "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\network\\msgplayer.cpp"
                            );
        }
        uVar5 = FUN_140065f80(plVar3,&local_b8,iVar2);
        if ((char)uVar5 == '\0') {
          (**(code **)(*plVar3 + 0x20))(plVar3);
          local_e8 = 0x76;
          log_InlineLogERROR(&DAT_1400be0b0,"MYASSERT","!\"pUser->Create()\"",
                             "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\network\\msgplayer.cpp"
                            );
        }
        else {
          plVar6 = (longlong *)FUN_14001c210();
          plVar6 = (longlong *)(**(code **)(*plVar6 + 0x10))(plVar6);
          (**(code **)(*plVar6 + 0x20))(plVar6,plVar3);
        }
      }
    }
  }
  __security_check_cookie(local_10 ^ (ulonglong)auStack_108);
  return;
}


