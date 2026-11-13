// NpcServer.exe :: CMsgWalk  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CMsgWalk::vf_0x8 @ 140062200  undefined8 vf_0x8(longlong param_1, longlong param_2, int param_3)

undefined8 CMsgWalk::vf_0x8(longlong param_1,longlong param_2,int param_3)

{
  longlong *plVar1;
  char cVar2;
  longlong lVar3;
  undefined8 uVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [40];
  
  if (*(int *)(param_1 + 8) == 0x2715) {
    plVar1 = (longlong *)(param_1 + 0x418);
    cVar2 = FUN_140076710(plVar1,param_2,param_3);
    if (cVar2 == '\0') {
      cVar2 = (**(code **)(*plVar1 + 0x20))(plVar1);
      if (cVar2 == '\0') {
        lVar3 = (**(code **)(*plVar1 + 0x28))(plVar1,local_30);
        if (*(ulonglong *)(lVar3 + 0x20) < 0x10) {
          lVar3 = lVar3 + 8;
        }
        else {
          lVar3 = *(longlong *)(lVar3 + 8);
        }
        log_InlineLogERROR(&DAT_1400ca410,lVar3);
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30);
      }
      else {
        log_InlineLogERROR("CMsgWalk_pb::CreateBufMsg ParseFromArray failed.");
      }
      uVar4 = 0;
    }
    else {
      uVar4 = 1;
    }
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}


// ==== CMsgWalk::vf_0x18 @ 1400622a0  undefined vf_0x18(longlong param_1)

void CMsgWalk::vf_0x18(longlong param_1)

{
  undefined4 uVar1;
  bool bVar2;
  longlong lVar3;
  longlong *plVar4;
  
  bVar2 = FUN_14001c1e0(*(int *)(param_1 + 0x454));
  if (bVar2) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return;
  }
  bVar2 = FUN_14001c1d0(*(int *)(param_1 + 0x454));
  if (!bVar2) {
    uVar1 = *(undefined4 *)(param_1 + 0x454);
    lVar3 = FUN_14001c210();
    plVar4 = (longlong *)
             (**(code **)(**(longlong **)(lVar3 + 8) + 0x30))(*(longlong **)(lVar3 + 8),uVar1);
    if (plVar4 != (longlong *)0x0) {
      FUN_140066300(plVar4,*(int *)(param_1 + 0x450),*(int *)(param_1 + 0x458));
    }
  }
  return;
}


// ==== CMsgWalk::vf_0x0 @ 140062340  undefined8 * vf_0x0(undefined8 * param_1, uint param_2)

undefined8 * CMsgWalk::vf_0x0(undefined8 *param_1,uint param_2)

{
  *param_1 = vftable;
  FUN_1400978b0(param_1 + 0x83);
  FUN_140034810(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


