// NpcServer.exe :: CMsgTalk  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMsgTalk::vf_0x8 @ 140064fa0  undefined8 vf_0x8(longlong param_1, void * param_2, uint param_3)

undefined8 CMsgTalk::vf_0x8(longlong param_1,void *param_2,uint param_3)

{
  if (param_2 == (void *)0x0) {
    return 0;
  }
  memcpy((void *)(param_1 + 0x10),param_2,(ulonglong)param_3);
  return 1;
}


// ==== CMsgTalk::vf_0x0 @ 140064fd0  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMsgTalk::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  tq::CStringPacker::~CStringPacker((CStringPacker *)(param_1 + 0x84));
  FUN_140034810(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CMsgTalk::vf_0x18 @ 140065030  undefined vf_0x18(longlong param_1)

void CMsgTalk::vf_0x18(longlong param_1)

{
  short sVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  longlong lVar7;
  longlong lVar8;
  undefined8 uVar9;
  ulonglong uVar10;
  longlong *plVar11;
  char *pcVar12;
  char *pcVar13;
  bool bVar14;
  undefined1 auStack_258 [32];
  uint local_238;
  undefined4 local_230;
  undefined4 local_228;
  undefined4 local_220;
  undefined8 *local_218;
  undefined8 local_210;
  undefined8 local_208;
  longlong *local_200;
  char local_1f8 [16];
  char local_1e8 [16];
  char local_1d8 [48];
  char local_1a8 [256];
  char local_a8 [128];
  ulonglong local_28;
  
  local_28 = DAT_140103510 ^ (ulonglong)auStack_258;
  tq::CStringPacker::GetString((CStringPacker *)(param_1 + 0x420),0,local_1d8,0x24);
  tq::CStringPacker::GetString((CStringPacker *)(param_1 + 0x420),1,local_1e8,0x10);
  tq::CStringPacker::GetString((CStringPacker *)(param_1 + 0x420),2,local_1f8,0x10);
  tq::CStringPacker::GetString((CStringPacker *)(param_1 + 0x420),3,local_1a8,0x100);
  uVar10 = 0xffffffffffffffff;
  pcVar12 = local_1a8;
  do {
    if (uVar10 == 0) break;
    uVar10 = uVar10 - 1;
    cVar2 = *pcVar12;
    pcVar12 = pcVar12 + 1;
  } while (cVar2 != '\0');
  if (~uVar10 - 1 < 0x100) {
    sVar1 = *(short *)(*(longlong *)(param_1 + 0x418) + 8);
    if (sVar1 != 0x7da) {
      bVar14 = sVar1 == 0x835;
      if (bVar14) {
        lVar7 = 10;
        pcVar12 = local_1a8;
        pcVar13 = "ANSWER_OK";
        do {
          if (lVar7 == 0) break;
          lVar7 = lVar7 + -1;
          bVar14 = *pcVar12 == *pcVar13;
          pcVar12 = pcVar12 + 1;
          pcVar13 = pcVar13 + 1;
        } while (bVar14);
        if (bVar14) {
          lVar7 = FUN_14001c200();
          FUN_14001c120(lVar7);
          lVar7 = FUN_14001c200();
          FUN_14001c700(lVar7);
        }
        else {
          lVar7 = 0x15;
          pcVar12 = local_1a8;
          pcVar13 = "ERROR: login refuse!";
          do {
            if (lVar7 == 0) break;
            lVar7 = lVar7 + -1;
            bVar14 = *pcVar12 == *pcVar13;
            pcVar12 = pcVar12 + 1;
            pcVar13 = pcVar13 + 1;
          } while (bVar14);
          if (bVar14) {
            lVar7 = FUN_14001c200();
            FUN_14001c120(lVar7);
            lVar7 = FUN_14001c200();
            FUN_14001c120(lVar7);
            lVar7 = FUN_14001c200();
            FUN_14001c100(lVar7);
          }
          else {
            lVar7 = FUN_14001c200();
            FUN_14001c120(lVar7);
            lVar7 = FUN_14001c200();
            FUN_14001c120(lVar7);
            lVar7 = FUN_14001c200();
            FUN_14001c120(lVar7);
            lVar7 = FUN_14001c200();
            FUN_14001c120(lVar7);
            lVar7 = FUN_14001c200();
            FUN_14001c120(lVar7);
            lVar7 = *(longlong *)(param_1 + 0x418);
            local_220 = *(undefined4 *)(lVar7 + 0x14);
            local_228 = *(undefined4 *)(lVar7 + 0x10);
            local_230 = *(undefined4 *)(lVar7 + 0xc);
            local_238 = (uint)*(ushort *)(lVar7 + 10);
            sprintf(local_a8,"%u, %u, %u, %u, %u, %u",(ulonglong)*(uint *)(lVar7 + 4),
                    (ulonglong)*(ushort *)(lVar7 + 8));
          }
        }
      }
      else if ((sVar1 != 0x839) && (iVar3 = _stricmp(local_1e8,"GUARD"), iVar3 == 0)) {
        lVar7 = FUN_14001c210();
        lVar7 = FUN_14003bab0(lVar7,(longlong)local_1d8);
        if ((lVar7 != 0) && (cVar2 = FUN_1400587e0(local_1d8), cVar2 != '\0')) {
          lVar8 = FUN_14001c7a0();
          lVar8 = FUN_140025c40(lVar8);
          local_200 = (longlong *)0x0;
          local_208 = **(undefined8 **)(lVar8 + 0x40);
          local_218 = (undefined8 *)(lVar8 + 0x10);
          local_210 = *local_218;
          uVar9 = FUN_14004f510((longlong *)&local_218);
          cVar2 = (char)uVar9;
          while (cVar2 != '\0') {
            if (((local_200 != (longlong *)0x0) &&
                (lVar8 = (**(code **)(*local_200 + 0xb0))(local_200,0x1040,0), lVar8 != 0)) &&
               (uVar4 = FUN_140057e20(lVar8), (char)uVar4 != '\0')) {
              plVar11 = (longlong *)(lVar8 + 0x10);
              iVar3 = (**(code **)(*(longlong *)(lVar7 + 0x10) + 0x30))(lVar7 + 0x10);
              iVar5 = (**(code **)(*plVar11 + 0x30))(plVar11);
              if (iVar5 == iVar3) {
                lVar8 = *plVar11;
                (**(code **)(*(longlong *)(lVar7 + 0x10) + 0x40))(lVar7 + 0x10);
                uVar6 = (**(code **)(*(longlong *)(lVar7 + 0x10) + 0x38))(lVar7 + 0x10);
                iVar3 = (**(code **)(lVar8 + 8))(plVar11,uVar6);
                if (iVar3 < 0x12) {
                  (**(code **)(*plVar11 + 0x108))(plVar11,local_1d8,local_1a8,local_1f8);
                }
              }
            }
            uVar9 = FUN_14004f510((longlong *)&local_218);
            cVar2 = (char)uVar9;
          }
        }
      }
    }
  }
  else {
    local_238 = 0x5d;
    log_InlineLogERROR(&DAT_1400be0b0,"CHECK","strlen(szWords) <= 255",
                       "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\network\\msgtalk.cpp"
                      );
  }
  __security_check_cookie(local_28 ^ (ulonglong)auStack_258);
  return;
}


