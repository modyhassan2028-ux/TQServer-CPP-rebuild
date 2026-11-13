// NpcServer.exe :: _unnamed  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== FUN_140023ab0 @ 140023ab0  undefined8 * FUN_140023ab0(undefined8 * param_1, undefined8 * param_2, char param_3, undefined8 * param_4, undefined8 * param_5)

undefined8 *
FUN_140023ab0(undefined8 *param_1,undefined8 *param_2,char param_3,undefined8 *param_4,
             undefined8 *param_5)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [40];
  
  if (0xffffffffffffffd < (ulonglong)param_1[7]) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_70,"map/set<T> too long");
    std::exception::exception((exception *)local_48);
    local_48[0] = std::logic_error::vftable;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
    local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
  }
  plVar5 = FUN_140022870(param_1,param_1[6],param_4,param_1[6],param_5,0);
  param_1[7] = param_1[7] + 1;
  if (param_4 == (undefined8 *)param_1[6]) {
    ((undefined8 *)param_1[6])[1] = plVar5;
    *(longlong **)param_1[6] = plVar5;
    *(longlong **)(param_1[6] + 0x10) = plVar5;
  }
  else if (param_3 == '\0') {
    param_4[2] = plVar5;
    if (param_4 == *(undefined8 **)(param_1[6] + 0x10)) {
      *(longlong **)(param_1[6] + 0x10) = plVar5;
    }
  }
  else {
    *param_4 = plVar5;
    if (param_4 == *(undefined8 **)param_1[6]) {
      *(longlong **)param_1[6] = plVar5;
    }
  }
  plVar7 = plVar5 + 1;
  cVar1 = *(char *)(*plVar7 + 0x28);
  plVar6 = plVar5;
  while (cVar1 == '\0') {
    plVar2 = (longlong *)*plVar7;
    plVar3 = (longlong *)plVar2[1];
    if (plVar2 == (longlong *)*plVar3) {
      lVar4 = plVar3[2];
      if (*(char *)(lVar4 + 0x28) == '\0') {
        *(undefined1 *)(plVar2 + 5) = 1;
        *(undefined1 *)(lVar4 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        plVar6 = *(longlong **)(*plVar7 + 8);
      }
      else {
        if (plVar6 == (longlong *)plVar2[2]) {
          plVar6 = (longlong *)plVar2[2];
          plVar2[2] = *plVar6;
          if (*(char *)(*plVar6 + 0x29) == '\0') {
            *(longlong **)(*plVar6 + 8) = plVar2;
          }
          plVar7 = plVar2 + 1;
          plVar6[1] = *plVar7;
          if (plVar2 == *(longlong **)(param_1[6] + 8)) {
            *(longlong **)(param_1[6] + 8) = plVar6;
          }
          else {
            plVar3 = (longlong *)*plVar7;
            if (plVar2 == (longlong *)*plVar3) {
              *plVar3 = (longlong)plVar6;
            }
            else {
              plVar3[2] = (longlong)plVar6;
            }
          }
          *plVar6 = (longlong)plVar2;
          *plVar7 = (longlong)plVar6;
          plVar6 = plVar2;
        }
        *(undefined1 *)(*plVar7 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        plVar7 = *(longlong **)(*plVar7 + 8);
        lVar4 = *plVar7;
        *plVar7 = *(longlong *)(lVar4 + 0x10);
        if (*(char *)(*(longlong *)(lVar4 + 0x10) + 0x29) == '\0') {
          *(longlong **)(*(longlong *)(lVar4 + 0x10) + 8) = plVar7;
        }
        *(longlong *)(lVar4 + 8) = plVar7[1];
        if (plVar7 == *(longlong **)(param_1[6] + 8)) {
          *(longlong *)(param_1[6] + 8) = lVar4;
        }
        else {
          plVar2 = (longlong *)plVar7[1];
          if (plVar7 == (longlong *)plVar2[2]) {
            plVar2[2] = lVar4;
          }
          else {
            *plVar2 = lVar4;
          }
        }
        *(longlong **)(lVar4 + 0x10) = plVar7;
        plVar7[1] = lVar4;
      }
    }
    else {
      lVar4 = *plVar3;
      if (*(char *)(lVar4 + 0x28) == '\0') {
        *(undefined1 *)(plVar2 + 5) = 1;
        *(undefined1 *)(lVar4 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        plVar6 = *(longlong **)(*plVar7 + 8);
      }
      else {
        if (plVar6 == (longlong *)*plVar2) {
          lVar4 = *plVar2;
          *plVar2 = *(longlong *)(lVar4 + 0x10);
          if (*(char *)(*(longlong *)(lVar4 + 0x10) + 0x29) == '\0') {
            *(longlong **)(*(longlong *)(lVar4 + 0x10) + 8) = plVar2;
          }
          plVar7 = plVar2 + 1;
          *(longlong *)(lVar4 + 8) = *plVar7;
          if (plVar2 == *(longlong **)(param_1[6] + 8)) {
            *(longlong *)(param_1[6] + 8) = lVar4;
          }
          else {
            plVar6 = (longlong *)*plVar7;
            if (plVar2 == (longlong *)plVar6[2]) {
              plVar6[2] = lVar4;
            }
            else {
              *plVar6 = lVar4;
            }
          }
          *(longlong **)(lVar4 + 0x10) = plVar2;
          *plVar7 = lVar4;
          plVar6 = plVar2;
        }
        *(undefined1 *)(*plVar7 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        lVar4 = *(longlong *)(*plVar7 + 8);
        plVar7 = *(longlong **)(lVar4 + 0x10);
        *(longlong *)(lVar4 + 0x10) = *plVar7;
        if (*(char *)(*plVar7 + 0x29) == '\0') {
          *(longlong *)(*plVar7 + 8) = lVar4;
        }
        plVar7[1] = *(longlong *)(lVar4 + 8);
        if (lVar4 == *(longlong *)(param_1[6] + 8)) {
          *(longlong **)(param_1[6] + 8) = plVar7;
        }
        else {
          plVar2 = *(longlong **)(lVar4 + 8);
          if (lVar4 == *plVar2) {
            *plVar2 = (longlong)plVar7;
          }
          else {
            plVar2[2] = (longlong)plVar7;
          }
        }
        *plVar7 = lVar4;
        *(longlong **)(lVar4 + 8) = plVar7;
      }
    }
    plVar7 = plVar6 + 1;
    cVar1 = *(char *)(*plVar7 + 0x28);
  }
  *(undefined1 *)(*(longlong *)(param_1[6] + 8) + 0x28) = 1;
  param_2[1] = plVar5;
  *param_2 = *param_1;
  return param_2;
}


// ==== FUN_140023df0 @ 140023df0  longlong * FUN_140023df0(longlong * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_140023df0(longlong *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  char cVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong local_28;
  longlong lStack_20;
  undefined8 local_18 [2];
  
  lVar2 = *(longlong *)param_1[6];
  if ((*param_3 == 0) || (*param_3 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (param_3[1] == lVar2) {
    lVar2 = param_1[6];
    if ((*param_4 == 0) || (*param_4 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    if (param_4[1] == lVar2) {
      FUN_140023210((longlong)param_1);
      param_2[1] = *(longlong *)param_1[6];
      *param_2 = *param_1;
      return param_2;
    }
  }
  while( true ) {
    if ((*param_3 == 0) || (*param_3 != *param_4)) {
      _invalid_parameter_noinfo();
    }
    lVar2 = *param_3;
    if (param_3[1] == param_4[1]) break;
    lVar3 = param_3[1];
    if (*param_3 == 0) {
      _invalid_parameter_noinfo();
    }
    lVar4 = param_3[1];
    if (*(char *)(lVar4 + 0x29) == '\0') {
      plVar6 = *(longlong **)(lVar4 + 0x10);
      if (*(char *)((longlong)plVar6 + 0x29) == '\0') {
        cVar1 = *(char *)(*plVar6 + 0x29);
        plVar5 = (longlong *)*plVar6;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar5 + 0x29);
          plVar6 = plVar5;
          plVar5 = (longlong *)*plVar5;
        }
      }
      else {
        plVar6 = *(longlong **)(lVar4 + 8);
        cVar1 = *(char *)((longlong)plVar6 + 0x29);
        while ((cVar1 == '\0' && (param_3[1] == plVar6[2]))) {
          param_3[1] = (longlong)plVar6;
          plVar6 = (longlong *)plVar6[1];
          cVar1 = *(char *)((longlong)plVar6 + 0x29);
        }
      }
      param_3[1] = (longlong)plVar6;
    }
    else {
      _invalid_parameter_noinfo();
    }
    local_28 = lVar2;
    lStack_20 = lVar3;
    FUN_140022e50(param_1,local_18,&local_28);
  }
  lVar2 = param_3[1];
  *param_2 = *param_1;
  param_2[1] = lVar2;
  return param_2;
}


// ==== FUN_140023fe0 @ 140023fe0  undefined8 * FUN_140023fe0(undefined8 * param_1, undefined8 * param_2, uint * param_3)

undefined8 * FUN_140023fe0(undefined8 *param_1,undefined8 *param_2,uint *param_3)

{
  FUN_140023290(param_1,param_2,param_3);
  return param_2;
}


// ==== FUN_140024000 @ 140024000  undefined8 * FUN_140024000(undefined8 * param_1, undefined8 * param_2, char param_3, undefined8 * param_4, undefined8 * param_5)

undefined8 *
FUN_140024000(undefined8 *param_1,undefined8 *param_2,char param_3,undefined8 *param_4,
             undefined8 *param_5)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [40];
  
  if (0xffffffffffffffd < (ulonglong)param_1[7]) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_70,"map/set<T> too long");
    std::exception::exception((exception *)local_48);
    local_48[0] = std::logic_error::vftable;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
    local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
  }
  plVar5 = FUN_1400228f0(param_1,param_1[6],param_4,param_1[6],param_5,0);
  param_1[7] = param_1[7] + 1;
  if (param_4 == (undefined8 *)param_1[6]) {
    ((undefined8 *)param_1[6])[1] = plVar5;
    *(longlong **)param_1[6] = plVar5;
    *(longlong **)(param_1[6] + 0x10) = plVar5;
  }
  else if (param_3 == '\0') {
    param_4[2] = plVar5;
    if (param_4 == *(undefined8 **)(param_1[6] + 0x10)) {
      *(longlong **)(param_1[6] + 0x10) = plVar5;
    }
  }
  else {
    *param_4 = plVar5;
    if (param_4 == *(undefined8 **)param_1[6]) {
      *(longlong **)param_1[6] = plVar5;
    }
  }
  plVar7 = plVar5 + 1;
  cVar1 = *(char *)(*plVar7 + 0x28);
  plVar6 = plVar5;
  while (cVar1 == '\0') {
    plVar2 = (longlong *)*plVar7;
    plVar3 = (longlong *)plVar2[1];
    if (plVar2 == (longlong *)*plVar3) {
      lVar4 = plVar3[2];
      if (*(char *)(lVar4 + 0x28) == '\0') {
        *(undefined1 *)(plVar2 + 5) = 1;
        *(undefined1 *)(lVar4 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        plVar6 = *(longlong **)(*plVar7 + 8);
      }
      else {
        if (plVar6 == (longlong *)plVar2[2]) {
          plVar6 = (longlong *)plVar2[2];
          plVar2[2] = *plVar6;
          if (*(char *)(*plVar6 + 0x29) == '\0') {
            *(longlong **)(*plVar6 + 8) = plVar2;
          }
          plVar7 = plVar2 + 1;
          plVar6[1] = *plVar7;
          if (plVar2 == *(longlong **)(param_1[6] + 8)) {
            *(longlong **)(param_1[6] + 8) = plVar6;
          }
          else {
            plVar3 = (longlong *)*plVar7;
            if (plVar2 == (longlong *)*plVar3) {
              *plVar3 = (longlong)plVar6;
            }
            else {
              plVar3[2] = (longlong)plVar6;
            }
          }
          *plVar6 = (longlong)plVar2;
          *plVar7 = (longlong)plVar6;
          plVar6 = plVar2;
        }
        *(undefined1 *)(*plVar7 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        plVar7 = *(longlong **)(*plVar7 + 8);
        lVar4 = *plVar7;
        *plVar7 = *(longlong *)(lVar4 + 0x10);
        if (*(char *)(*(longlong *)(lVar4 + 0x10) + 0x29) == '\0') {
          *(longlong **)(*(longlong *)(lVar4 + 0x10) + 8) = plVar7;
        }
        *(longlong *)(lVar4 + 8) = plVar7[1];
        if (plVar7 == *(longlong **)(param_1[6] + 8)) {
          *(longlong *)(param_1[6] + 8) = lVar4;
        }
        else {
          plVar2 = (longlong *)plVar7[1];
          if (plVar7 == (longlong *)plVar2[2]) {
            plVar2[2] = lVar4;
          }
          else {
            *plVar2 = lVar4;
          }
        }
        *(longlong **)(lVar4 + 0x10) = plVar7;
        plVar7[1] = lVar4;
      }
    }
    else {
      lVar4 = *plVar3;
      if (*(char *)(lVar4 + 0x28) == '\0') {
        *(undefined1 *)(plVar2 + 5) = 1;
        *(undefined1 *)(lVar4 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        plVar6 = *(longlong **)(*plVar7 + 8);
      }
      else {
        if (plVar6 == (longlong *)*plVar2) {
          lVar4 = *plVar2;
          *plVar2 = *(longlong *)(lVar4 + 0x10);
          if (*(char *)(*(longlong *)(lVar4 + 0x10) + 0x29) == '\0') {
            *(longlong **)(*(longlong *)(lVar4 + 0x10) + 8) = plVar2;
          }
          plVar7 = plVar2 + 1;
          *(longlong *)(lVar4 + 8) = *plVar7;
          if (plVar2 == *(longlong **)(param_1[6] + 8)) {
            *(longlong *)(param_1[6] + 8) = lVar4;
          }
          else {
            plVar6 = (longlong *)*plVar7;
            if (plVar2 == (longlong *)plVar6[2]) {
              plVar6[2] = lVar4;
            }
            else {
              *plVar6 = lVar4;
            }
          }
          *(longlong **)(lVar4 + 0x10) = plVar2;
          *plVar7 = lVar4;
          plVar6 = plVar2;
        }
        *(undefined1 *)(*plVar7 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        lVar4 = *(longlong *)(*plVar7 + 8);
        plVar7 = *(longlong **)(lVar4 + 0x10);
        *(longlong *)(lVar4 + 0x10) = *plVar7;
        if (*(char *)(*plVar7 + 0x29) == '\0') {
          *(longlong *)(*plVar7 + 8) = lVar4;
        }
        plVar7[1] = *(longlong *)(lVar4 + 8);
        if (lVar4 == *(longlong *)(param_1[6] + 8)) {
          *(longlong **)(param_1[6] + 8) = plVar7;
        }
        else {
          plVar2 = *(longlong **)(lVar4 + 8);
          if (lVar4 == *plVar2) {
            *plVar2 = (longlong)plVar7;
          }
          else {
            plVar2[2] = (longlong)plVar7;
          }
        }
        *plVar7 = lVar4;
        *(longlong **)(lVar4 + 8) = plVar7;
      }
    }
    plVar7 = plVar6 + 1;
    cVar1 = *(char *)(*plVar7 + 0x28);
  }
  *(undefined1 *)(*(longlong *)(param_1[6] + 8) + 0x28) = 1;
  param_2[1] = plVar5;
  *param_2 = *param_1;
  return param_2;
}


// ==== FUN_140024340 @ 140024340  undefined FUN_140024340(longlong * param_1)

void FUN_140024340(longlong *param_1)

{
  longlong local_38;
  undefined8 *puStack_30;
  longlong local_28;
  undefined8 uStack_20;
  longlong local_18 [2];
  
  local_38 = *param_1;
  puStack_30 = (undefined8 *)param_1[6];
  uStack_20 = *puStack_30;
  local_28 = local_38;
  FUN_140023df0(param_1,local_18,&local_28,&local_38);
  operator_delete((void *)param_1[6]);
  param_1[6] = 0;
  param_1[7] = 0;
  return;
}


// ==== FUN_1400243b0 @ 1400243b0  longlong * FUN_1400243b0(longlong * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_1400243b0(longlong *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  char cVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong local_28;
  longlong lStack_20;
  undefined8 local_18 [2];
  
  lVar2 = *(longlong *)param_1[6];
  if ((*param_3 == 0) || (*param_3 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (param_3[1] == lVar2) {
    lVar2 = param_1[6];
    if ((*param_4 == 0) || (*param_4 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    if (param_4[1] == lVar2) {
      FUN_1400237c0((longlong)param_1);
      param_2[1] = *(longlong *)param_1[6];
      *param_2 = *param_1;
      return param_2;
    }
  }
  while( true ) {
    if ((*param_3 == 0) || (*param_3 != *param_4)) {
      _invalid_parameter_noinfo();
    }
    lVar2 = *param_3;
    if (param_3[1] == param_4[1]) break;
    lVar3 = param_3[1];
    if (*param_3 == 0) {
      _invalid_parameter_noinfo();
    }
    lVar4 = param_3[1];
    if (*(char *)(lVar4 + 0x29) == '\0') {
      plVar6 = *(longlong **)(lVar4 + 0x10);
      if (*(char *)((longlong)plVar6 + 0x29) == '\0') {
        cVar1 = *(char *)(*plVar6 + 0x29);
        plVar5 = (longlong *)*plVar6;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar5 + 0x29);
          plVar6 = plVar5;
          plVar5 = (longlong *)*plVar5;
        }
      }
      else {
        plVar6 = *(longlong **)(lVar4 + 8);
        cVar1 = *(char *)((longlong)plVar6 + 0x29);
        while ((cVar1 == '\0' && (param_3[1] == plVar6[2]))) {
          param_3[1] = (longlong)plVar6;
          plVar6 = (longlong *)plVar6[1];
          cVar1 = *(char *)((longlong)plVar6 + 0x29);
        }
      }
      param_3[1] = (longlong)plVar6;
    }
    else {
      _invalid_parameter_noinfo();
    }
    local_28 = lVar2;
    lStack_20 = lVar3;
    FUN_140023400(param_1,local_18,&local_28);
  }
  lVar2 = param_3[1];
  *param_2 = *param_1;
  param_2[1] = lVar2;
  return param_2;
}


// ==== FUN_140024560 @ 140024560  undefined8 * FUN_140024560(undefined8 * param_1)

undefined8 * FUN_140024560(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_1400245b0 @ 1400245b0  undefined8 * FUN_1400245b0(undefined8 * param_1)

undefined8 * FUN_1400245b0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140024600 @ 140024600  undefined FUN_140024600(longlong * param_1, longlong * param_2, longlong * param_3)

void FUN_140024600(longlong *param_1,longlong *param_2,longlong *param_3)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  
  lVar2 = *param_2;
  plVar3 = (longlong *)param_2[1];
  lVar4 = *param_1;
  plVar7 = (longlong *)param_1[1];
  while( true ) {
    if ((lVar4 == 0) || (lVar4 != lVar2)) {
      _invalid_parameter_noinfo();
    }
    if (plVar7 == plVar3) break;
    *param_3 = *param_3 + 1;
    if (lVar4 == 0) {
      _invalid_parameter_noinfo();
    }
    if (*(char *)((longlong)plVar7 + 0x29) == '\0') {
      plVar5 = (longlong *)plVar7[2];
      if (*(char *)((longlong)plVar5 + 0x29) == '\0') {
        cVar1 = *(char *)(*plVar5 + 0x29);
        plVar7 = plVar5;
        plVar5 = (longlong *)*plVar5;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar5 + 0x29);
          plVar7 = plVar5;
          plVar5 = (longlong *)*plVar5;
        }
      }
      else {
        cVar1 = *(char *)(plVar7[1] + 0x29);
        plVar6 = (longlong *)plVar7[1];
        plVar5 = plVar7;
        while ((plVar7 = plVar6, cVar1 == '\0' && (plVar5 == (longlong *)plVar7[2]))) {
          cVar1 = *(char *)(plVar7[1] + 0x29);
          plVar6 = (longlong *)plVar7[1];
          plVar5 = plVar7;
        }
      }
    }
    else {
      _invalid_parameter_noinfo();
    }
  }
  return;
}


// ==== FUN_1400246f0 @ 1400246f0  longlong * FUN_1400246f0(longlong * param_1, longlong * param_2, uint * param_3)

longlong * FUN_1400246f0(longlong *param_1,longlong *param_2,uint *param_3)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *plVar4;
  longlong *plVar5;
  longlong *plVar6;
  bool bVar7;
  longlong local_38;
  longlong *local_30;
  
  plVar6 = (longlong *)param_1[6];
  bVar7 = true;
  if (*(char *)(plVar6[1] + 0x29) == '\0') {
    plVar5 = (longlong *)plVar6[1];
    do {
      plVar6 = plVar5;
      bVar7 = *param_3 < *(uint *)(plVar6 + 3);
      if (bVar7) {
        plVar5 = (longlong *)*plVar6;
      }
      else {
        plVar5 = (longlong *)plVar6[2];
      }
    } while (*(char *)((longlong)plVar5 + 0x29) == '\0');
  }
  lVar2 = *param_1;
  plVar5 = plVar6;
  local_38 = lVar2;
  plVar4 = plVar6;
  if (bVar7 == false) {
LAB_14002484d:
    local_30 = plVar4;
    if (*param_3 <= *(uint *)(plVar5 + 3)) {
      *(undefined1 *)(param_2 + 2) = 0;
      *param_2 = local_38;
      goto LAB_14002487c;
    }
  }
  else {
    plVar5 = *(longlong **)param_1[6];
    local_30 = plVar6;
    if (lVar2 == 0) {
      _invalid_parameter_noinfo();
    }
    if (plVar6 != plVar5) {
      if (lVar2 == 0) {
        _invalid_parameter_noinfo();
      }
      if (*(char *)((longlong)plVar6 + 0x29) == '\0') {
        plVar5 = (longlong *)*plVar6;
        if (*(char *)((longlong)plVar5 + 0x29) == '\0') {
          cVar1 = *(char *)(plVar5[2] + 0x29);
          plVar3 = (longlong *)plVar5[2];
          while (plVar4 = plVar5, cVar1 == '\0') {
            cVar1 = *(char *)(plVar3[2] + 0x29);
            plVar5 = plVar3;
            plVar3 = (longlong *)plVar3[2];
          }
        }
        else {
          cVar1 = *(char *)(plVar6[1] + 0x29);
          plVar4 = (longlong *)plVar6[1];
          plVar3 = plVar6;
          while ((plVar5 = plVar4, cVar1 == '\0' && (plVar3 == (longlong *)*plVar5))) {
            cVar1 = *(char *)(plVar5[1] + 0x29);
            plVar4 = (longlong *)plVar5[1];
            plVar3 = plVar5;
            local_30 = plVar5;
          }
          plVar4 = plVar5;
          if (*(char *)((longlong)plVar3 + 0x29) != '\0') {
            _invalid_parameter_noinfo();
            plVar5 = plVar3;
            plVar4 = local_30;
          }
        }
      }
      else {
        plVar5 = (longlong *)plVar6[2];
        plVar4 = plVar5;
        if (*(char *)((longlong)plVar5 + 0x29) != '\0') {
          local_30 = plVar5;
          _invalid_parameter_noinfo();
          plVar4 = local_30;
        }
      }
      goto LAB_14002484d;
    }
    bVar7 = true;
  }
  plVar6 = FUN_140023ab0(param_1,&local_38,bVar7,plVar6,(undefined8 *)param_3);
  *(undefined1 *)(param_2 + 2) = 1;
  local_30 = (longlong *)plVar6[1];
  *param_2 = *plVar6;
LAB_14002487c:
  param_2[1] = (longlong)local_30;
  return param_2;
}


// ==== FUN_1400248a0 @ 1400248a0  longlong * FUN_1400248a0(longlong * param_1, longlong * param_2, uint * param_3)

longlong * FUN_1400248a0(longlong *param_1,longlong *param_2,uint *param_3)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong local_28;
  undefined8 *local_20;
  longlong local_18;
  longlong local_10;
  
  puVar4 = (undefined8 *)param_1[6];
  if (*(char *)((longlong)puVar4[1] + 0x29) == '\0') {
    puVar1 = (undefined8 *)puVar4[1];
    do {
      if (*(uint *)(puVar1 + 3) < *param_3) {
        puVar2 = (undefined8 *)puVar1[2];
      }
      else {
        puVar2 = (undefined8 *)*puVar1;
        puVar4 = puVar1;
      }
      puVar1 = puVar2;
    } while (*(char *)((longlong)puVar2 + 0x29) == '\0');
  }
  puVar1 = (undefined8 *)param_1[6];
  local_20 = puVar4;
  local_28 = *param_1;
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  if ((puVar4 == puVar1) || (*param_3 < *(uint *)(puVar4 + 3))) {
    plVar3 = &local_18;
    local_10 = param_1[6];
    local_18 = *param_1;
  }
  else {
    plVar3 = &local_28;
  }
  *param_2 = *plVar3;
  param_2[1] = plVar3[1];
  return param_2;
}


// ==== FUN_140024970 @ 140024970  longlong * FUN_140024970(longlong * param_1, longlong * param_2, uint * param_3)

longlong * FUN_140024970(longlong *param_1,longlong *param_2,uint *param_3)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *plVar4;
  longlong *plVar5;
  longlong *plVar6;
  bool bVar7;
  longlong local_38;
  longlong *local_30;
  
  plVar6 = (longlong *)param_1[6];
  bVar7 = true;
  if (*(char *)(plVar6[1] + 0x29) == '\0') {
    plVar5 = (longlong *)plVar6[1];
    do {
      plVar6 = plVar5;
      bVar7 = *param_3 < *(uint *)(plVar6 + 3);
      if (bVar7) {
        plVar5 = (longlong *)*plVar6;
      }
      else {
        plVar5 = (longlong *)plVar6[2];
      }
    } while (*(char *)((longlong)plVar5 + 0x29) == '\0');
  }
  lVar2 = *param_1;
  plVar5 = plVar6;
  local_38 = lVar2;
  plVar4 = plVar6;
  if (bVar7 == false) {
LAB_140024acd:
    local_30 = plVar4;
    if (*param_3 <= *(uint *)(plVar5 + 3)) {
      *(undefined1 *)(param_2 + 2) = 0;
      *param_2 = local_38;
      goto LAB_140024afc;
    }
  }
  else {
    plVar5 = *(longlong **)param_1[6];
    local_30 = plVar6;
    if (lVar2 == 0) {
      _invalid_parameter_noinfo();
    }
    if (plVar6 != plVar5) {
      if (lVar2 == 0) {
        _invalid_parameter_noinfo();
      }
      if (*(char *)((longlong)plVar6 + 0x29) == '\0') {
        plVar5 = (longlong *)*plVar6;
        if (*(char *)((longlong)plVar5 + 0x29) == '\0') {
          cVar1 = *(char *)(plVar5[2] + 0x29);
          plVar3 = (longlong *)plVar5[2];
          while (plVar4 = plVar5, cVar1 == '\0') {
            cVar1 = *(char *)(plVar3[2] + 0x29);
            plVar5 = plVar3;
            plVar3 = (longlong *)plVar3[2];
          }
        }
        else {
          cVar1 = *(char *)(plVar6[1] + 0x29);
          plVar4 = (longlong *)plVar6[1];
          plVar3 = plVar6;
          while ((plVar5 = plVar4, cVar1 == '\0' && (plVar3 == (longlong *)*plVar5))) {
            cVar1 = *(char *)(plVar5[1] + 0x29);
            plVar4 = (longlong *)plVar5[1];
            plVar3 = plVar5;
            local_30 = plVar5;
          }
          plVar4 = plVar5;
          if (*(char *)((longlong)plVar3 + 0x29) != '\0') {
            _invalid_parameter_noinfo();
            plVar5 = plVar3;
            plVar4 = local_30;
          }
        }
      }
      else {
        plVar5 = (longlong *)plVar6[2];
        plVar4 = plVar5;
        if (*(char *)((longlong)plVar5 + 0x29) != '\0') {
          local_30 = plVar5;
          _invalid_parameter_noinfo();
          plVar4 = local_30;
        }
      }
      goto LAB_140024acd;
    }
    bVar7 = true;
  }
  plVar6 = FUN_140024000(param_1,&local_38,bVar7,plVar6,(undefined8 *)param_3);
  *(undefined1 *)(param_2 + 2) = 1;
  local_30 = (longlong *)plVar6[1];
  *param_2 = *plVar6;
LAB_140024afc:
  param_2[1] = (longlong)local_30;
  return param_2;
}


// ==== FUN_140024b20 @ 140024b20  longlong FUN_140024b20(longlong * param_1, uint * param_2)

longlong FUN_140024b20(longlong *param_1,uint *param_2)

{
  char cVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  longlong lVar8;
  longlong local_58;
  longlong *local_50;
  longlong local_48;
  longlong *local_40;
  longlong local_38;
  longlong *local_30;
  longlong local_28;
  longlong *local_20;
  
  FUN_140023290(param_1,&local_38,param_2);
  plVar5 = local_20;
  lVar4 = local_28;
  lVar3 = local_38;
  lVar8 = 0;
  local_58 = local_38;
  local_50 = local_30;
  plVar7 = local_30;
  while( true ) {
    if ((lVar3 == 0) || (lVar3 != lVar4)) {
      _invalid_parameter_noinfo();
    }
    if (plVar7 == plVar5) break;
    lVar8 = lVar8 + 1;
    if (lVar3 == 0) {
      _invalid_parameter_noinfo();
    }
    if (*(char *)((longlong)plVar7 + 0x29) == '\0') {
      plVar2 = (longlong *)plVar7[2];
      if (*(char *)((longlong)plVar2 + 0x29) == '\0') {
        cVar1 = *(char *)(*plVar2 + 0x29);
        plVar7 = plVar2;
        plVar2 = (longlong *)*plVar2;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar2 + 0x29);
          plVar7 = plVar2;
          plVar2 = (longlong *)*plVar2;
        }
      }
      else {
        cVar1 = *(char *)(plVar7[1] + 0x29);
        plVar6 = (longlong *)plVar7[1];
        plVar2 = plVar7;
        while ((plVar7 = plVar6, cVar1 == '\0' && (plVar2 == (longlong *)plVar7[2]))) {
          cVar1 = *(char *)(plVar7[1] + 0x29);
          plVar6 = (longlong *)plVar7[1];
          plVar2 = plVar7;
        }
      }
    }
    else {
      _invalid_parameter_noinfo();
    }
  }
  local_58 = local_28;
  local_50 = local_20;
  local_48 = local_38;
  local_40 = local_30;
  FUN_140023df0(param_1,&local_38,&local_48,&local_58);
  return lVar8;
}


// ==== FUN_140024c60 @ 140024c60  longlong * FUN_140024c60(longlong * param_1, longlong * param_2, uint * param_3)

longlong * FUN_140024c60(longlong *param_1,longlong *param_2,uint *param_3)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong local_28;
  undefined8 *local_20;
  longlong local_18;
  longlong local_10;
  
  puVar4 = (undefined8 *)param_1[6];
  if (*(char *)((longlong)puVar4[1] + 0x29) == '\0') {
    puVar1 = (undefined8 *)puVar4[1];
    do {
      if (*(uint *)(puVar1 + 3) < *param_3) {
        puVar2 = (undefined8 *)puVar1[2];
      }
      else {
        puVar2 = (undefined8 *)*puVar1;
        puVar4 = puVar1;
      }
      puVar1 = puVar2;
    } while (*(char *)((longlong)puVar2 + 0x29) == '\0');
  }
  puVar1 = (undefined8 *)param_1[6];
  local_20 = puVar4;
  local_28 = *param_1;
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  if ((puVar4 == puVar1) || (*param_3 < *(uint *)(puVar4 + 3))) {
    plVar3 = &local_18;
    local_10 = param_1[6];
    local_18 = *param_1;
  }
  else {
    plVar3 = &local_28;
  }
  *param_2 = *plVar3;
  param_2[1] = plVar3[1];
  return param_2;
}


// ==== FUN_140024d30 @ 140024d30  undefined FUN_140024d30(undefined8 * param_1)

void FUN_140024d30(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140024d50 @ 140024d50  undefined FUN_140024d50(undefined8 * param_1)

void FUN_140024d50(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140024d70 @ 140024d70  undefined FUN_140024d70(longlong * param_1)

void FUN_140024d70(longlong *param_1)

{
  longlong local_38;
  undefined8 *puStack_30;
  longlong local_28;
  undefined8 uStack_20;
  longlong local_18 [2];
  
  local_38 = *param_1;
  puStack_30 = (undefined8 *)param_1[6];
  uStack_20 = *puStack_30;
  local_28 = local_38;
  FUN_1400243b0(param_1,local_18,&local_28,&local_38);
  operator_delete((void *)param_1[6]);
  param_1[6] = 0;
  param_1[7] = 0;
  return;
}


// ==== FUN_140024de0 @ 140024de0  undefined8 * FUN_140024de0(undefined8 * param_1)

undefined8 * FUN_140024de0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140024e30 @ 140024e30  undefined8 * FUN_140024e30(undefined8 * param_1)

undefined8 * FUN_140024e30(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140024e80 @ 140024e80  longlong * FUN_140024e80(longlong param_1)

longlong * FUN_140024e80(longlong param_1)

{
  char cVar1;
  int iVar2;
  longlong *plVar3;
  longlong *plVar4;
  undefined8 uVar5;
  longlong *plVar6;
  uint uVar7;
  longlong *plVar8;
  uint local_50 [2];
  longlong *local_48;
  longlong local_40 [3];
  
  plVar3 = (longlong *)InstanceGet();
  plVar3 = (longlong *)(**(code **)(*plVar3 + 0x10))(plVar3,"SELECT * FROM cq_instancetype",1);
  if (plVar3 != (longlong *)0x0) {
    iVar2 = (**(code **)(*plVar3 + 0x40))(plVar3);
    plVar8 = (longlong *)0x0;
    if (0 < iVar2) {
      do {
        (**(code **)(*plVar3 + 0x30))(plVar3,(longlong)(int)plVar8);
        plVar4 = (longlong *)operator_new(0x18);
        plVar6 = (longlong *)0x0;
        if (plVar4 != (longlong *)0x0) {
          *plVar4 = (longlong)IGameData::vftable;
          *plVar4 = (longlong)CGameData<&char*_szInstanceTypeTable,&char*_szID>::vftable;
          *(undefined1 *)(plVar4 + 2) = 0;
          plVar4[1] = 0;
          plVar6 = plVar4;
        }
        if (plVar6 == (longlong *)0x0) {
          log_InlineLogERROR(&DAT_1400be0b0);
        }
        else {
          cVar1 = (**(code **)(*plVar6 + 0x30))(plVar6,plVar3);
          if (cVar1 == '\0') {
            (**(code **)*plVar6)(plVar6,1);
          }
          else {
            local_50[0] = (**(code **)(*plVar6 + 8))(plVar6);
            local_48 = plVar6;
            FUN_1400246f0((longlong *)(param_1 + 8),local_40,local_50);
          }
        }
        uVar7 = (int)plVar8 + 1;
        iVar2 = (**(code **)(*plVar3 + 0x40))(plVar3);
        plVar8 = (longlong *)(ulonglong)uVar7;
      } while ((int)uVar7 < iVar2);
    }
    uVar5 = (**(code **)*plVar3)(plVar3);
    plVar3 = (longlong *)CONCAT71((int7)((ulonglong)uVar5 >> 8),1);
  }
  return plVar3;
}


// ==== FUN_140024fe0 @ 140024fe0  undefined8 FUN_140024fe0(longlong param_1, uint param_2)

undefined8 FUN_140024fe0(longlong param_1,uint param_2)

{
  char cVar1;
  longlong *plVar2;
  undefined8 *puVar3;
  longlong lVar4;
  undefined8 *puVar5;
  undefined8 uVar6;
  longlong *plVar7;
  undefined8 *puVar8;
  longlong lVar9;
  longlong local_38;
  undefined8 *local_30;
  longlong local_28;
  undefined8 local_20;
  longlong *local_18;
  longlong local_10;
  
  puVar8 = (undefined8 *)(*(undefined8 **)(param_1 + 0x38))[1];
  cVar1 = *(char *)((longlong)puVar8 + 0x29);
  puVar3 = *(undefined8 **)(param_1 + 0x38);
  while (cVar1 == '\0') {
    if (*(uint *)(puVar8 + 3) < param_2) {
      puVar5 = (undefined8 *)puVar8[2];
      puVar8 = puVar3;
    }
    else {
      puVar5 = (undefined8 *)*puVar8;
    }
    puVar3 = puVar8;
    puVar8 = puVar5;
    cVar1 = *(char *)((longlong)puVar5 + 0x29);
  }
  puVar8 = *(undefined8 **)(param_1 + 0x38);
  local_30 = puVar3;
  local_38 = *(longlong *)(param_1 + 8);
  if (*(longlong *)(param_1 + 8) == 0) {
    _invalid_parameter_noinfo();
  }
  if ((puVar3 == puVar8) || (param_2 < *(uint *)(puVar3 + 3))) {
    plVar7 = &local_28;
    local_20 = *(undefined8 *)(param_1 + 0x38);
    local_28 = *(longlong *)(param_1 + 8);
  }
  else {
    plVar7 = &local_38;
  }
  plVar2 = (longlong *)*plVar7;
  lVar9 = *(longlong *)(param_1 + 0x38);
  local_18 = plVar2;
  local_10 = plVar7[1];
  if ((plVar2 == (longlong *)0x0) || (plVar2 != *(longlong **)(param_1 + 8))) {
    _invalid_parameter_noinfo();
  }
  lVar4 = local_10;
  if (local_10 == lVar9) {
    uVar6 = 0;
  }
  else {
    if (plVar2 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar9 = 0;
    }
    else {
      lVar9 = *plVar2;
    }
    if (lVar4 == *(longlong *)(lVar9 + 0x30)) {
      _invalid_parameter_noinfo();
    }
    uVar6 = *(undefined8 *)(lVar4 + 0x20);
  }
  return uVar6;
}


// ==== FUN_1400250e0 @ 1400250e0  undefined8 FUN_1400250e0(longlong param_1, uint param_2)

undefined8 FUN_1400250e0(longlong param_1,uint param_2)

{
  char cVar1;
  longlong *plVar2;
  undefined8 *puVar3;
  longlong lVar4;
  undefined8 *puVar5;
  undefined8 uVar6;
  longlong *plVar7;
  undefined8 *puVar8;
  longlong lVar9;
  longlong local_38;
  undefined8 *local_30;
  longlong local_28;
  undefined8 local_20;
  longlong *local_18;
  longlong local_10;
  
  puVar8 = (undefined8 *)(*(undefined8 **)(param_1 + 0x78))[1];
  cVar1 = *(char *)((longlong)puVar8 + 0x29);
  puVar3 = *(undefined8 **)(param_1 + 0x78);
  while (cVar1 == '\0') {
    if (*(uint *)(puVar8 + 3) < param_2) {
      puVar5 = (undefined8 *)puVar8[2];
      puVar8 = puVar3;
    }
    else {
      puVar5 = (undefined8 *)*puVar8;
    }
    puVar3 = puVar8;
    puVar8 = puVar5;
    cVar1 = *(char *)((longlong)puVar5 + 0x29);
  }
  puVar8 = *(undefined8 **)(param_1 + 0x78);
  local_30 = puVar3;
  local_38 = *(longlong *)(param_1 + 0x48);
  if (*(longlong *)(param_1 + 0x48) == 0) {
    _invalid_parameter_noinfo();
  }
  if ((puVar3 == puVar8) || (param_2 < *(uint *)(puVar3 + 3))) {
    plVar7 = &local_28;
    local_20 = *(undefined8 *)(param_1 + 0x78);
    local_28 = *(longlong *)(param_1 + 0x48);
  }
  else {
    plVar7 = &local_38;
  }
  plVar2 = (longlong *)*plVar7;
  lVar9 = *(longlong *)(param_1 + 0x78);
  local_18 = plVar2;
  local_10 = plVar7[1];
  if ((plVar2 == (longlong *)0x0) || (plVar2 != *(longlong **)(param_1 + 0x48))) {
    _invalid_parameter_noinfo();
  }
  lVar4 = local_10;
  if (local_10 == lVar9) {
    uVar6 = 0;
  }
  else {
    if (plVar2 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar9 = 0;
    }
    else {
      lVar9 = *plVar2;
    }
    if (lVar4 == *(longlong *)(lVar9 + 0x30)) {
      _invalid_parameter_noinfo();
    }
    uVar6 = *(undefined8 *)(lVar4 + 0x20);
  }
  return uVar6;
}


// ==== FUN_1400251e0 @ 1400251e0  undefined FUN_1400251e0(longlong * param_1)

void FUN_1400251e0(longlong *param_1)

{
  FUN_140024d70(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140025210 @ 140025210  undefined FUN_140025210(longlong * param_1)

void FUN_140025210(longlong *param_1)

{
  FUN_140024340(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140025240 @ 140025240  undefined8 * FUN_140025240(undefined8 * param_1)

undefined8 * FUN_140025240(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140025290 @ 140025290  undefined8 * FUN_140025290(undefined8 * param_1)

undefined8 * FUN_140025290(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_1400252e0 @ 1400252e0  undefined FUN_1400252e0(longlong * param_1)

void FUN_1400252e0(longlong *param_1)

{
  FUN_140024d70(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140025310 @ 140025310  undefined FUN_140025310(longlong * param_1)

void FUN_140025310(longlong *param_1)

{
  FUN_140024340(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140025340 @ 140025340  undefined FUN_140025340(undefined8 * param_1)

void FUN_140025340(undefined8 *param_1)

{
  char cVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  undefined8 *puVar6;
  longlong lVar7;
  longlong *local_58;
  undefined8 *puStack_50;
  longlong *local_48;
  undefined8 *puStack_40;
  longlong local_38 [2];
  
  *param_1 = CInstanceMgr::vftable;
  puVar2 = (undefined8 *)param_1[0xf];
  puVar6 = (undefined8 *)*puVar2;
  plVar3 = (longlong *)param_1[9];
  local_58 = plVar3;
  puStack_50 = puVar6;
  local_48 = plVar3;
  puStack_40 = puVar2;
  while( true ) {
    if (plVar3 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
    }
    if (puVar6 == puVar2) break;
    if (plVar3 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar7 = 0;
    }
    else {
      lVar7 = *plVar3;
    }
    if (puVar6 == *(undefined8 **)(lVar7 + 0x30)) {
      _invalid_parameter_noinfo();
    }
    puVar4 = (undefined8 *)puVar6[4];
    if (puVar4 != (undefined8 *)0x0) {
      FUN_140049050((longlong)puVar4);
      FUN_140048f90(puVar4);
    }
    if (plVar3 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
    }
    if (*(char *)((longlong)puVar6 + 0x29) == '\0') {
      puVar4 = (undefined8 *)puVar6[2];
      if (*(char *)((longlong)puVar4 + 0x29) == '\0') {
        cVar1 = *(char *)((longlong)*puVar4 + 0x29);
        puVar6 = puVar4;
        puVar4 = (undefined8 *)*puVar4;
        while (puStack_50 = puVar6, cVar1 == '\0') {
          cVar1 = *(char *)((longlong)*puVar4 + 0x29);
          puVar6 = puVar4;
          puVar4 = (undefined8 *)*puVar4;
        }
      }
      else {
        cVar1 = *(char *)((longlong)puVar6[1] + 0x29);
        puVar5 = (undefined8 *)puVar6[1];
        puVar4 = puVar6;
        while ((puVar6 = puVar5, puStack_50 = puVar6, cVar1 == '\0' &&
               (puVar4 == (undefined8 *)puVar6[2]))) {
          cVar1 = *(char *)((longlong)puVar6[1] + 0x29);
          puVar5 = (undefined8 *)puVar6[1];
          puVar4 = puVar6;
        }
      }
    }
    else {
      _invalid_parameter_noinfo();
    }
  }
  puVar2 = (undefined8 *)param_1[7];
  puVar6 = (undefined8 *)*puVar2;
  plVar3 = (longlong *)param_1[1];
  local_58 = plVar3;
  puStack_50 = puVar6;
  local_48 = plVar3;
  puStack_40 = puVar2;
  while( true ) {
    if (plVar3 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
    }
    if (puVar6 == puVar2) break;
    if (plVar3 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar7 = 0;
    }
    else {
      lVar7 = *plVar3;
    }
    if (puVar6 == *(undefined8 **)(lVar7 + 0x30)) {
      _invalid_parameter_noinfo();
    }
    if ((longlong *)puVar6[4] != (longlong *)0x0) {
      (**(code **)(*(longlong *)puVar6[4] + 0x58))();
    }
    if (plVar3 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
    }
    if (*(char *)((longlong)puVar6 + 0x29) == '\0') {
      puVar4 = (undefined8 *)puVar6[2];
      if (*(char *)((longlong)puVar4 + 0x29) == '\0') {
        cVar1 = *(char *)((longlong)*puVar4 + 0x29);
        puVar6 = puVar4;
        puVar4 = (undefined8 *)*puVar4;
        while (puStack_50 = puVar6, cVar1 == '\0') {
          cVar1 = *(char *)((longlong)*puVar4 + 0x29);
          puVar6 = puVar4;
          puVar4 = (undefined8 *)*puVar4;
        }
      }
      else {
        cVar1 = *(char *)((longlong)puVar6[1] + 0x29);
        puVar5 = (undefined8 *)puVar6[1];
        puVar4 = puVar6;
        while ((puVar6 = puVar5, puStack_50 = puVar6, cVar1 == '\0' &&
               (puVar4 == (undefined8 *)puVar6[2]))) {
          cVar1 = *(char *)((longlong)puVar6[1] + 0x29);
          puVar5 = (undefined8 *)puVar6[1];
          puVar4 = puVar6;
        }
      }
    }
    else {
      _invalid_parameter_noinfo();
    }
  }
  plVar3 = param_1 + 9;
  puStack_40 = (undefined8 *)param_1[0xf];
  local_58 = (longlong *)*plVar3;
  puStack_50 = (undefined8 *)*puStack_40;
  local_48 = local_58;
  FUN_140023df0(plVar3,local_38,(longlong *)&local_58,(longlong *)&local_48);
  operator_delete((void *)param_1[0xf]);
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  operator_delete((void *)*plVar3);
  plVar3 = param_1 + 1;
  puStack_40 = (undefined8 *)param_1[7];
  local_58 = (longlong *)*plVar3;
  puStack_50 = (undefined8 *)*puStack_40;
  local_48 = local_58;
  FUN_1400243b0(plVar3,local_38,(longlong *)&local_58,(longlong *)&local_48);
  operator_delete((void *)param_1[7]);
  param_1[7] = 0;
  param_1[8] = 0;
  operator_delete((void *)*plVar3);
  return;
}


// ==== FUN_140025690 @ 140025690  undefined8 FUN_140025690(longlong param_1, undefined4 param_2, undefined4 param_3, uint param_4)

ulonglong FUN_140025690(longlong param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  longlong lVar1;
  ulonglong extraout_RAX;
  ulonglong uVar2;
  ulonglong extraout_RAX_00;
  longlong *plVar3;
  uint local_38 [2];
  undefined8 *local_30;
  longlong local_28 [4];
  
  lVar1 = FUN_140024fe0(param_1,param_4);
  if (lVar1 == 0) {
    log_InlineLogERROR("CInstanceMgr::CreateInstance InstanceType:%u not find");
    uVar2 = extraout_RAX & 0xffffffffffffff00;
  }
  else {
    local_30 = FUN_1400491b0(param_3,lVar1,param_2);
    if (local_30 == (undefined8 *)0x0) {
      log_InlineLogERROR(&DAT_1400be0b0);
      uVar2 = extraout_RAX_00 & 0xffffffffffffff00;
    }
    else {
      local_38[0] = FUN_140049070((longlong)local_30);
      plVar3 = FUN_140024970((longlong *)(param_1 + 0x48),local_28,local_38);
      uVar2 = CONCAT71((int7)((ulonglong)plVar3 >> 8),1);
    }
  }
  return uVar2;
}


// ==== FUN_140025750 @ 140025750  undefined FUN_140025750(longlong param_1, uint param_2)

void FUN_140025750(longlong param_1,uint param_2)

{
  undefined8 *puVar1;
  uint local_res10 [6];
  
  local_res10[0] = param_2;
  puVar1 = (undefined8 *)FUN_1400250e0(param_1,param_2);
  if (puVar1 != (undefined8 *)0x0) {
    FUN_140049050((longlong)puVar1);
    FUN_140048f90(puVar1);
    FUN_140024b20((longlong *)(param_1 + 0x48),local_res10);
  }
  return;
}


// ==== FUN_1400257a0 @ 1400257a0  undefined8 * FUN_1400257a0(undefined8 * param_1)

undefined8 * FUN_1400257a0(undefined8 *param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  lVar2 = FUN_140022a40();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x29) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_140025820 @ 140025820  undefined8 * FUN_140025820(undefined8 * param_1)

undefined8 * FUN_140025820(undefined8 *param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  lVar2 = FUN_140022af0();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x29) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_1400258d0 @ 1400258d0  undefined8 * FUN_1400258d0(undefined8 * param_1)

undefined8 * FUN_1400258d0(undefined8 *param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  lVar2 = FUN_140022a40();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x29) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_140025950 @ 140025950  undefined8 * FUN_140025950(undefined8 * param_1)

undefined8 * FUN_140025950(undefined8 *param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  lVar2 = FUN_140022af0();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x29) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_1400259d0 @ 1400259d0  undefined8 * FUN_1400259d0(undefined8 * param_1)

undefined8 * FUN_1400259d0(undefined8 *param_1)

{
  *param_1 = CInstanceMgr::vftable;
  FUN_1400258d0(param_1 + 1);
  FUN_140025950(param_1 + 9);
  return param_1;
}


// ==== FUN_140025a10 @ 140025a10  undefined8 * FUN_140025a10(void)

undefined8 * FUN_140025a10(void)

{
  undefined8 *puVar1;
  longlong *plVar2;
  
  puVar1 = (undefined8 *)operator_new(0x88);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = CInstanceMgr::vftable;
    FUN_1400258d0(puVar1 + 1);
    FUN_140025950(puVar1 + 9);
  }
  if ((puVar1 == (undefined8 *)0x0) ||
     (plVar2 = FUN_140024e80((longlong)puVar1), (char)plVar2 == '\0')) {
    log_InlineLogERROR(&DAT_1400be0b0);
    puVar1 = (undefined8 *)0x0;
  }
  return puVar1;
}


// ==== FUN_140025aa0 @ 140025aa0  undefined8 * FUN_140025aa0(void)

undefined8 * FUN_140025aa0(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x18);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    puVar1 = FUN_140057400(puVar1);
  }
  return puVar1;
}


// ==== FUN_140025ae0 @ 140025ae0  undefined8 FUN_140025ae0(undefined8 * param_1)

undefined8 FUN_140025ae0(undefined8 *param_1)

{
  if (param_1 != (undefined8 *)0x0) {
    (**(code **)*param_1)(param_1,1);
  }
  return 0;
}


// ==== FUN_140025b10 @ 140025b10  longlong FUN_140025b10(longlong param_1)

longlong FUN_140025b10(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = *(longlong *)(param_1 + 8);
  if (lVar1 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    lVar1 = 0;
  }
  return lVar1;
}


// ==== FUN_140025b50 @ 140025b50  longlong FUN_140025b50(longlong param_1)

longlong FUN_140025b50(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = *(longlong *)(param_1 + 0x10);
  if (lVar1 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    lVar1 = 0;
  }
  return lVar1;
}


// ==== FUN_140025ba0 @ 140025ba0  longlong FUN_140025ba0(longlong param_1)

longlong FUN_140025ba0(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = *(longlong *)(param_1 + 0x18);
  if (lVar1 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    lVar1 = 0;
  }
  return lVar1;
}


// ==== FUN_140025be0 @ 140025be0  longlong FUN_140025be0(longlong param_1)

longlong FUN_140025be0(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = *(longlong *)(param_1 + 0x20);
  if (lVar1 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    lVar1 = 0;
  }
  return lVar1;
}


// ==== FUN_140025c20 @ 140025c20  longlong FUN_140025c20(longlong param_1)

longlong FUN_140025c20(longlong param_1)

{
  return param_1 + 0x28;
}


// ==== FUN_140025c40 @ 140025c40  longlong FUN_140025c40(longlong param_1)

longlong FUN_140025c40(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = *(longlong *)(param_1 + 8);
  if (lVar1 == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    lVar1 = 0;
  }
  return lVar1;
}


// ==== FUN_140025c80 @ 140025c80  undefined FUN_140025c80(undefined8 * param_1)

void FUN_140025c80(undefined8 *param_1)

{
  *param_1 = ISingleMap<class_INpc>::vftable;
  return;
}


// ==== FUN_140025e50 @ 140025e50  undefined FUN_140025e50(undefined8 * param_1)

void FUN_140025e50(undefined8 *param_1)

{
  *param_1 = IGameObjSet<class_IGenerator>::vftable;
  return;
}


// ==== FUN_140026020 @ 140026020  undefined FUN_140026020(undefined8 * param_1)

void FUN_140026020(undefined8 *param_1)

{
  *param_1 = IGameObjSet<class_CNpcType>::vftable;
  return;
}


// ==== FUN_1400261f0 @ 1400261f0  bool FUN_1400261f0(longlong * param_1, longlong * param_2)

bool FUN_1400261f0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_140026230 @ 140026230  bool FUN_140026230(longlong * param_1, longlong * param_2)

bool FUN_140026230(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_140026270 @ 140026270  bool FUN_140026270(longlong * param_1, longlong * param_2)

bool FUN_140026270(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_1400262b0 @ 1400262b0  bool FUN_1400262b0(longlong * param_1, longlong * param_2)

bool FUN_1400262b0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_1400264e0 @ 1400264e0  undefined FUN_1400264e0(longlong param_1, longlong * param_2)

void FUN_1400264e0(longlong param_1,longlong *param_2)

{
  longlong lVar1;
  longlong *plVar2;
  
  lVar1 = *param_2;
  *param_2 = *(longlong *)(lVar1 + 0x10);
  if (*(char *)(*(longlong *)(lVar1 + 0x10) + 0x51) == '\0') {
    *(longlong **)(*(longlong *)(lVar1 + 0x10) + 8) = param_2;
  }
  *(longlong *)(lVar1 + 8) = param_2[1];
  if (param_2 == *(longlong **)(*(longlong *)(param_1 + 0x30) + 8)) {
    *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = lVar1;
    *(longlong **)(lVar1 + 0x10) = param_2;
    param_2[1] = lVar1;
    return;
  }
  plVar2 = (longlong *)param_2[1];
  if (param_2 == (longlong *)plVar2[2]) {
    plVar2[2] = lVar1;
    *(longlong **)(lVar1 + 0x10) = param_2;
    param_2[1] = lVar1;
    return;
  }
  *plVar2 = lVar1;
  *(longlong **)(lVar1 + 0x10) = param_2;
  param_2[1] = lVar1;
  return;
}


// ==== FUN_140026600 @ 140026600  longlong FUN_140026600(longlong * param_1)

longlong FUN_140026600(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140026622;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140026622:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_140026640 @ 140026640  longlong * FUN_140026640(longlong * param_1)

longlong * FUN_140026640(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140026662;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140026662:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + 8;
  return param_1;
}


// ==== FUN_140026680 @ 140026680  bool FUN_140026680(longlong * param_1, longlong * param_2)

bool FUN_140026680(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_140026700 @ 140026700  longlong FUN_140026700(longlong * param_1)

longlong FUN_140026700(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140026722;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140026722:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_140026740 @ 140026740  longlong * FUN_140026740(longlong * param_1)

longlong * FUN_140026740(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140026762;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140026762:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + 4;
  return param_1;
}


// ==== FUN_140026780 @ 140026780  bool FUN_140026780(longlong * param_1, longlong * param_2)

bool FUN_140026780(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_1400267c0 @ 1400267c0  bool FUN_1400267c0(longlong * param_1, longlong * param_2)

bool FUN_1400267c0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_1400268f0 @ 1400268f0  longlong FUN_1400268f0(longlong * param_1)

longlong FUN_1400268f0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140026912;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140026912:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_140026930 @ 140026930  undefined FUN_140026930(longlong * param_1)

void FUN_140026930(longlong *param_1)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *plVar4;
  
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  lVar2 = param_1[1];
  if (*(char *)(lVar2 + 0x51) == '\0') {
    plVar3 = *(longlong **)(lVar2 + 0x10);
    if (*(char *)((longlong)plVar3 + 0x51) != '\0') {
      lVar2 = *(longlong *)(lVar2 + 8);
      cVar1 = *(char *)(lVar2 + 0x51);
      while ((cVar1 == '\0' && (param_1[1] == *(longlong *)(lVar2 + 0x10)))) {
        param_1[1] = lVar2;
        lVar2 = *(longlong *)(lVar2 + 8);
        cVar1 = *(char *)(lVar2 + 0x51);
      }
      param_1[1] = lVar2;
      return;
    }
    cVar1 = *(char *)(*plVar3 + 0x51);
    plVar4 = (longlong *)*plVar3;
    while (cVar1 == '\0') {
      cVar1 = *(char *)(*plVar4 + 0x51);
      plVar3 = plVar4;
      plVar4 = (longlong *)*plVar4;
    }
    param_1[1] = (longlong)plVar3;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000140026954. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_1400269c0 @ 1400269c0  undefined FUN_1400269c0(void)

void FUN_1400269c0(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [48];
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_70,"vector<T> too long");
  std::exception::exception((exception *)local_48);
  local_48[0] = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
  local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
}


// ==== FUN_140026a30 @ 140026a30  longlong FUN_140026a30(longlong * param_1)

longlong FUN_140026a30(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140026a52;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140026a52:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_140026a70 @ 140026a70  undefined FUN_140026a70(void)

void FUN_140026a70(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [48];
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_70,"vector<T> too long");
  std::exception::exception((exception *)local_48);
  local_48[0] = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
  local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
}


// ==== FUN_140026b00 @ 140026b00  longlong FUN_140026b00(longlong * param_1, longlong * param_2)

longlong FUN_140026b00(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] - param_2[1] >> 3;
}


// ==== FUN_140026b40 @ 140026b40  longlong FUN_140026b40(longlong * param_1, longlong * param_2)

longlong FUN_140026b40(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] - param_2[1] >> 2;
}


// ==== FUN_140026b80 @ 140026b80  longlong FUN_140026b80(longlong * param_1)

longlong FUN_140026b80(longlong *param_1)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  ulonglong uVar6;
  
  uVar1 = param_1[1];
  plVar2 = (longlong *)*param_1;
  lVar5 = 0;
  uVar6 = uVar1 >> 2;
  lVar3 = lVar5;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar2 = (longlong *)*param_1;
    lVar4 = lVar5;
    if (plVar2 == (longlong *)0x0) goto LAB_140026bd0;
  }
  lVar4 = *plVar2;
  if (plVar2 != (longlong *)0x0) {
    lVar3 = lVar4;
  }
LAB_140026bd0:
  if ((ulonglong)(*(longlong *)(lVar3 + 0x38) + *(longlong *)(lVar4 + 0x30)) <=
      (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)*param_1;
  lVar3 = lVar5;
  if (plVar2 != (longlong *)0x0) {
    lVar3 = *plVar2;
  }
  if (*(ulonglong *)(lVar3 + 0x28) <= uVar6) {
    lVar3 = lVar5;
    if (plVar2 != (longlong *)0x0) {
      lVar3 = *plVar2;
    }
    uVar6 = uVar6 - *(longlong *)(lVar3 + 0x28);
  }
  if (plVar2 != (longlong *)0x0) {
    lVar5 = *plVar2;
  }
  return *(longlong *)(*(longlong *)(lVar5 + 0x20) + uVar6 * 8) + (ulonglong)((uint)uVar1 & 3) * 4;
}


// ==== FUN_140026cf0 @ 140026cf0  undefined FUN_140026cf0(undefined8 * param_1)

void FUN_140026cf0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140026d10 @ 140026d10  undefined FUN_140026d10(undefined8 * param_1)

void FUN_140026d10(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140026d30 @ 140026d30  undefined FUN_140026d30(undefined8 * param_1)

void FUN_140026d30(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140026d50 @ 140026d50  undefined FUN_140026d50(longlong * param_1)

void FUN_140026d50(longlong *param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)param_1[1];
  if (*(char *)((longlong)plVar2 + 0x51) == '\0') {
    lVar3 = *plVar2;
    if (*(char *)(lVar3 + 0x51) == '\0') {
      cVar1 = *(char *)(*(longlong *)(lVar3 + 0x10) + 0x51);
      lVar4 = *(longlong *)(lVar3 + 0x10);
      while (lVar5 = lVar4, cVar1 == '\0') {
        lVar4 = *(longlong *)(lVar5 + 0x10);
        cVar1 = *(char *)(lVar4 + 0x51);
        lVar3 = lVar5;
      }
      param_1[1] = lVar3;
      return;
    }
    plVar2 = (longlong *)plVar2[1];
    cVar1 = *(char *)((longlong)plVar2 + 0x51);
    while ((cVar1 == '\0' && (param_1[1] == *plVar2))) {
      param_1[1] = (longlong)plVar2;
      plVar2 = (longlong *)plVar2[1];
      cVar1 = *(char *)((longlong)plVar2 + 0x51);
    }
    if (*(char *)(param_1[1] + 0x51) == '\0') {
      param_1[1] = (longlong)plVar2;
      return;
    }
  }
  else {
    lVar3 = plVar2[2];
    param_1[1] = lVar3;
    if (*(char *)(lVar3 + 0x51) == '\0') {
      return;
    }
  }
                    /* WARNING: Could not recover jumptable at 0x000140026d82. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_140026ea0 @ 140026ea0  undefined FUN_140026ea0(void)

void FUN_140026ea0(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [48];
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_70,"vector<T> too long");
  std::exception::exception((exception *)local_48);
  local_48[0] = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
  local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
}


// ==== FUN_140026f30 @ 140026f30  undefined FUN_140026f30(void)

void FUN_140026f30(void)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [48];
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_70,"vector<T> too long");
  std::exception::exception((exception *)local_48);
  local_48[0] = std::logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
  local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
  _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
}


// ==== FUN_140026fc0 @ 140026fc0  longlong * FUN_140026fc0(longlong * param_1, longlong param_2)

longlong * FUN_140026fc0(longlong *param_1,longlong param_2)

{
  longlong *plVar1;
  ulonglong uVar2;
  longlong lVar3;
  longlong lVar4;
  
  plVar1 = (longlong *)*param_1;
  lVar3 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar1 = (longlong *)*param_1;
    lVar4 = lVar3;
    if (plVar1 != (longlong *)0x0) goto LAB_140026ff0;
  }
  else {
LAB_140026ff0:
    lVar4 = *plVar1;
  }
  uVar2 = param_1[1] + param_2 * 8;
  if (uVar2 <= *(ulonglong *)(lVar4 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar2) goto LAB_140027018;
  }
  _invalid_parameter_noinfo();
LAB_140027018:
  param_1[1] = param_1[1] + param_2 * 8;
  return param_1;
}


// ==== FUN_140027030 @ 140027030  longlong * FUN_140027030(longlong * param_1, longlong param_2)

longlong * FUN_140027030(longlong *param_1,longlong param_2)

{
  longlong *plVar1;
  ulonglong uVar2;
  longlong lVar3;
  longlong lVar4;
  
  plVar1 = (longlong *)*param_1;
  lVar3 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar1 = (longlong *)*param_1;
    lVar4 = lVar3;
    if (plVar1 != (longlong *)0x0) goto LAB_140027060;
  }
  else {
LAB_140027060:
    lVar4 = *plVar1;
  }
  uVar2 = param_1[1] + param_2 * 4;
  if (uVar2 <= *(ulonglong *)(lVar4 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar2) goto LAB_140027088;
  }
  _invalid_parameter_noinfo();
LAB_140027088:
  param_1[1] = param_1[1] + param_2 * 4;
  return param_1;
}


// ==== FUN_1400270f0 @ 1400270f0  undefined FUN_1400270f0(longlong param_1, longlong param_2)

void FUN_1400270f0(longlong param_1,longlong param_2)

{
  longlong *plVar1;
  longlong *plVar2;
  
  plVar1 = *(longlong **)(param_2 + 0x10);
  *(longlong *)(param_2 + 0x10) = *plVar1;
  if (*(char *)(*plVar1 + 0x29) == '\0') {
    *(longlong *)(*plVar1 + 8) = param_2;
  }
  plVar1[1] = *(longlong *)(param_2 + 8);
  if (param_2 == *(longlong *)(*(longlong *)(param_1 + 0x30) + 8)) {
    *(longlong **)(*(longlong *)(param_1 + 0x30) + 8) = plVar1;
    *plVar1 = param_2;
    *(longlong **)(param_2 + 8) = plVar1;
    return;
  }
  plVar2 = *(longlong **)(param_2 + 8);
  if (param_2 == *plVar2) {
    *plVar2 = (longlong)plVar1;
    *plVar1 = param_2;
    *(longlong **)(param_2 + 8) = plVar1;
    return;
  }
  plVar2[2] = (longlong)plVar1;
  *plVar1 = param_2;
  *(longlong **)(param_2 + 8) = plVar1;
  return;
}


// ==== FUN_140027180 @ 140027180  undefined FUN_140027180(longlong param_1, longlong * param_2)

void FUN_140027180(longlong param_1,longlong *param_2)

{
  longlong lVar1;
  longlong *plVar2;
  
  lVar1 = *param_2;
  *param_2 = *(longlong *)(lVar1 + 0x10);
  if (*(char *)(*(longlong *)(lVar1 + 0x10) + 0x29) == '\0') {
    *(longlong **)(*(longlong *)(lVar1 + 0x10) + 8) = param_2;
  }
  *(longlong *)(lVar1 + 8) = param_2[1];
  if (param_2 == *(longlong **)(*(longlong *)(param_1 + 0x30) + 8)) {
    *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = lVar1;
    *(longlong **)(lVar1 + 0x10) = param_2;
    param_2[1] = lVar1;
    return;
  }
  plVar2 = (longlong *)param_2[1];
  if (param_2 == (longlong *)plVar2[2]) {
    plVar2[2] = lVar1;
    *(longlong **)(lVar1 + 0x10) = param_2;
    param_2[1] = lVar1;
    return;
  }
  *plVar2 = lVar1;
  *(longlong **)(lVar1 + 0x10) = param_2;
  param_2[1] = lVar1;
  return;
}


// ==== FUN_1400271f0 @ 1400271f0  undefined FUN_1400271f0(longlong * param_1)

void FUN_1400271f0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
    *param_1 = 0;
  }
  return;
}


// ==== FUN_140027230 @ 140027230  undefined FUN_140027230(ulonglong param_1)

void FUN_140027230(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 4)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 << 2);
  return;
}


// ==== FUN_140027300 @ 140027300  undefined FUN_140027300(ulonglong param_1)

void FUN_140027300(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 8)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 << 3);
  return;
}


// ==== FUN_140027380 @ 140027380  undefined FUN_140027380(ulonglong param_1)

void FUN_140027380(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x58)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 * 0x58);
  return;
}


// ==== FUN_140027400 @ 140027400  undefined FUN_140027400(ulonglong param_1)

void FUN_140027400(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x58)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 * 0x58);
  return;
}


// ==== FUN_1400274d0 @ 1400274d0  undefined FUN_1400274d0(ulonglong param_1)

void FUN_1400274d0(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 8)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 << 3);
  return;
}


// ==== FUN_140027550 @ 140027550  undefined FUN_140027550(ulonglong param_1)

void FUN_140027550(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 8)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 << 3);
  return;
}


// ==== FUN_140027600 @ 140027600  undefined FUN_140027600(ulonglong param_1)

void FUN_140027600(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x30)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 * 0x30);
  return;
}


// ==== FUN_1400277f0 @ 1400277f0  void * FUN_1400277f0(void * param_1, longlong param_2, void * param_3)

void * FUN_1400277f0(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _DstSize = lVar1 * 4;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_140027840 @ 140027840  void * FUN_140027840(void * param_1, longlong param_2, void * param_3)

void * FUN_140027840(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_140027890 @ 140027890  void * FUN_140027890(void * param_1, longlong param_2, longlong param_3)

void * FUN_140027890(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _Dst = (void *)(param_3 + lVar1 * -4);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 4,param_1,lVar1 * 4);
  }
  return _Dst;
}


// ==== FUN_1400278e0 @ 1400278e0  void * FUN_1400278e0(void * param_1, longlong param_2, longlong param_3)

void * FUN_1400278e0(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _Dst = (void *)(param_3 + lVar1 * -8);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 8,param_1,lVar1 * 8);
  }
  return _Dst;
}


// ==== FUN_1400279c0 @ 1400279c0  void * FUN_1400279c0(void * param_1, longlong param_2, void * param_3)

void * FUN_1400279c0(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _DstSize = lVar1 * 4;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_140027a00 @ 140027a00  void * FUN_140027a00(void * param_1, longlong param_2, void * param_3)

void * FUN_140027a00(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_140027a40 @ 140027a40  undefined FUN_140027a40(longlong param_1, undefined4 param_2)

void FUN_140027a40(longlong param_1,undefined4 param_2)

{
  longlong *plVar1;
  
  plVar1 = *(longlong **)(param_1 + 8);
  if (plVar1 == (longlong *)0x0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    plVar1 = (longlong *)0x0;
  }
                    /* WARNING: Could not recover jumptable at 0x000140027a87. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*plVar1 + 0x40))(plVar1,param_2);
  return;
}


// ==== FUN_140027ab0 @ 140027ab0  longlong FUN_140027ab0(longlong * param_1)

longlong FUN_140027ab0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140027ad2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140027ad2:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_140027af0 @ 140027af0  longlong * FUN_140027af0(longlong * param_1)

longlong * FUN_140027af0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140027b12;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140027b12:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + 8;
  return param_1;
}


// ==== FUN_140027b30 @ 140027b30  bool FUN_140027b30(longlong * param_1, longlong * param_2)

bool FUN_140027b30(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_140027b70 @ 140027b70  longlong FUN_140027b70(longlong * param_1)

longlong FUN_140027b70(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140027b92;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140027b92:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_140027bb0 @ 140027bb0  longlong * FUN_140027bb0(longlong * param_1)

longlong * FUN_140027bb0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140027bd2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140027bd2:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + 4;
  return param_1;
}


// ==== FUN_140027bf0 @ 140027bf0  bool FUN_140027bf0(longlong * param_1, longlong * param_2)

bool FUN_140027bf0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_140027c30 @ 140027c30  bool FUN_140027c30(longlong * param_1, longlong * param_2)

bool FUN_140027c30(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_140027c70 @ 140027c70  undefined FUN_140027c70(undefined8 * param_1)

void FUN_140027c70(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140027ca0 @ 140027ca0  undefined FUN_140027ca0(undefined8 * param_1)

void FUN_140027ca0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140027cc0 @ 140027cc0  undefined FUN_140027cc0(longlong param_1, longlong param_2)

void FUN_140027cc0(longlong param_1,longlong param_2)

{
  longlong *plVar1;
  longlong *plVar2;
  
  plVar1 = *(longlong **)(param_2 + 0x10);
  *(longlong *)(param_2 + 0x10) = *plVar1;
  if (*(char *)(*plVar1 + 0x51) == '\0') {
    *(longlong *)(*plVar1 + 8) = param_2;
  }
  plVar1[1] = *(longlong *)(param_2 + 8);
  if (param_2 == *(longlong *)(*(longlong *)(param_1 + 0x30) + 8)) {
    *(longlong **)(*(longlong *)(param_1 + 0x30) + 8) = plVar1;
    *plVar1 = param_2;
    *(longlong **)(param_2 + 8) = plVar1;
    return;
  }
  plVar2 = *(longlong **)(param_2 + 8);
  if (param_2 == *plVar2) {
    *plVar2 = (longlong)plVar1;
    *plVar1 = param_2;
    *(longlong **)(param_2 + 8) = plVar1;
    return;
  }
  plVar2[2] = (longlong)plVar1;
  *plVar1 = param_2;
  *(longlong **)(param_2 + 8) = plVar1;
  return;
}


// ==== FUN_140027d20 @ 140027d20  undefined FUN_140027d20(undefined8 * param_1)

void FUN_140027d20(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140027d30 @ 140027d30  longlong FUN_140027d30(longlong * param_1)

longlong FUN_140027d30(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140027d52;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140027d52:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_140027d70 @ 140027d70  longlong * FUN_140027d70(longlong * param_1)

longlong * FUN_140027d70(longlong *param_1)

{
  FUN_140026930(param_1);
  return param_1;
}


// ==== FUN_140027d90 @ 140027d90  longlong FUN_140027d90(longlong * param_1)

longlong FUN_140027d90(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140027db2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140027db2:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_140027dd0 @ 140027dd0  undefined FUN_140027dd0(undefined8 * param_1)

void FUN_140027dd0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140027df0 @ 140027df0  undefined FUN_140027df0(undefined8 param_1, ulonglong param_2)

void FUN_140027df0(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 4)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 4);
  return;
}


// ==== FUN_140027ee0 @ 140027ee0  undefined FUN_140027ee0(longlong param_1, longlong param_2)

void FUN_140027ee0(longlong param_1,longlong param_2)

{
  longlong *plVar1;
  longlong *plVar2;
  
  plVar1 = *(longlong **)(param_2 + 0x10);
  *(longlong *)(param_2 + 0x10) = *plVar1;
  if (*(char *)(*plVar1 + 0x51) == '\0') {
    *(longlong *)(*plVar1 + 8) = param_2;
  }
  plVar1[1] = *(longlong *)(param_2 + 8);
  if (param_2 == *(longlong *)(*(longlong *)(param_1 + 0x30) + 8)) {
    *(longlong **)(*(longlong *)(param_1 + 0x30) + 8) = plVar1;
    *plVar1 = param_2;
    *(longlong **)(param_2 + 8) = plVar1;
    return;
  }
  plVar2 = *(longlong **)(param_2 + 8);
  if (param_2 == *plVar2) {
    *plVar2 = (longlong)plVar1;
    *plVar1 = param_2;
    *(longlong **)(param_2 + 8) = plVar1;
    return;
  }
  plVar2[2] = (longlong)plVar1;
  *plVar1 = param_2;
  *(longlong **)(param_2 + 8) = plVar1;
  return;
}


// ==== FUN_140027f40 @ 140027f40  undefined FUN_140027f40(longlong param_1, longlong * param_2)

void FUN_140027f40(longlong param_1,longlong *param_2)

{
  longlong lVar1;
  longlong *plVar2;
  
  lVar1 = *param_2;
  *param_2 = *(longlong *)(lVar1 + 0x10);
  if (*(char *)(*(longlong *)(lVar1 + 0x10) + 0x51) == '\0') {
    *(longlong **)(*(longlong *)(lVar1 + 0x10) + 8) = param_2;
  }
  *(longlong *)(lVar1 + 8) = param_2[1];
  if (param_2 == *(longlong **)(*(longlong *)(param_1 + 0x30) + 8)) {
    *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = lVar1;
    *(longlong **)(lVar1 + 0x10) = param_2;
    param_2[1] = lVar1;
    return;
  }
  plVar2 = (longlong *)param_2[1];
  if (param_2 == (longlong *)plVar2[2]) {
    plVar2[2] = lVar1;
    *(longlong **)(lVar1 + 0x10) = param_2;
    param_2[1] = lVar1;
    return;
  }
  *plVar2 = lVar1;
  *(longlong **)(lVar1 + 0x10) = param_2;
  param_2[1] = lVar1;
  return;
}


// ==== FUN_140028010 @ 140028010  longlong * FUN_140028010(longlong * param_1)

longlong * FUN_140028010(longlong *param_1)

{
  FUN_140026d50(param_1);
  return param_1;
}


// ==== FUN_140028040 @ 140028040  undefined FUN_140028040(longlong * param_1)

void FUN_140028040(longlong *param_1)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *plVar4;
  
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  lVar2 = param_1[1];
  if (*(char *)(lVar2 + 0x51) == '\0') {
    plVar3 = *(longlong **)(lVar2 + 0x10);
    if (*(char *)((longlong)plVar3 + 0x51) != '\0') {
      lVar2 = *(longlong *)(lVar2 + 8);
      cVar1 = *(char *)(lVar2 + 0x51);
      while ((cVar1 == '\0' && (param_1[1] == *(longlong *)(lVar2 + 0x10)))) {
        param_1[1] = lVar2;
        lVar2 = *(longlong *)(lVar2 + 8);
        cVar1 = *(char *)(lVar2 + 0x51);
      }
      param_1[1] = lVar2;
      return;
    }
    cVar1 = *(char *)(*plVar3 + 0x51);
    plVar4 = (longlong *)*plVar3;
    while (cVar1 == '\0') {
      cVar1 = *(char *)(*plVar4 + 0x51);
      plVar3 = plVar4;
      plVar4 = (longlong *)*plVar4;
    }
    param_1[1] = (longlong)plVar3;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000140028064. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_1400280e0 @ 1400280e0  undefined FUN_1400280e0(undefined8 param_1, ulonglong param_2)

void FUN_1400280e0(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 8)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 8);
  return;
}


// ==== FUN_140028150 @ 140028150  undefined FUN_140028150(undefined8 * param_1)

void FUN_140028150(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140028170 @ 140028170  undefined FUN_140028170(undefined8 * param_1)

void FUN_140028170(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_1400281e0 @ 1400281e0  undefined FUN_1400281e0(undefined8 * param_1)

void FUN_1400281e0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140028200 @ 140028200  undefined FUN_140028200(undefined8 param_1, ulonglong param_2)

void FUN_140028200(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x58)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 0x58);
  return;
}


// ==== FUN_140028270 @ 140028270  undefined FUN_140028270(undefined8 param_1, ulonglong param_2)

void FUN_140028270(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x58)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 0x58);
  return;
}


// ==== FUN_1400282e0 @ 1400282e0  longlong * FUN_1400282e0(longlong * param_1, longlong * param_2)

longlong * FUN_1400282e0(longlong *param_1,longlong *param_2)

{
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  FUN_140026930(param_1);
  return param_2;
}


// ==== FUN_140028310 @ 140028310  undefined FUN_140028310(longlong * param_1)

void FUN_140028310(longlong *param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)param_1[1];
  if (*(char *)((longlong)plVar2 + 0x51) == '\0') {
    lVar3 = *plVar2;
    if (*(char *)(lVar3 + 0x51) == '\0') {
      cVar1 = *(char *)(*(longlong *)(lVar3 + 0x10) + 0x51);
      lVar4 = *(longlong *)(lVar3 + 0x10);
      while (lVar5 = lVar4, cVar1 == '\0') {
        lVar4 = *(longlong *)(lVar5 + 0x10);
        cVar1 = *(char *)(lVar4 + 0x51);
        lVar3 = lVar5;
      }
      param_1[1] = lVar3;
      return;
    }
    plVar2 = (longlong *)plVar2[1];
    cVar1 = *(char *)((longlong)plVar2 + 0x51);
    while ((cVar1 == '\0' && (param_1[1] == *plVar2))) {
      param_1[1] = (longlong)plVar2;
      plVar2 = (longlong *)plVar2[1];
      cVar1 = *(char *)((longlong)plVar2 + 0x51);
    }
    if (*(char *)(param_1[1] + 0x51) == '\0') {
      param_1[1] = (longlong)plVar2;
      return;
    }
  }
  else {
    lVar3 = plVar2[2];
    param_1[1] = lVar3;
    if (*(char *)(lVar3 + 0x51) == '\0') {
      return;
    }
  }
                    /* WARNING: Could not recover jumptable at 0x000140028342. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_1400283b0 @ 1400283b0  longlong * FUN_1400283b0(longlong * param_1, longlong param_2)

longlong * FUN_1400283b0(longlong *param_1,longlong param_2)

{
  FUN_140026fc0(param_1,param_2);
  return param_1;
}


// ==== FUN_1400283d0 @ 1400283d0  longlong * FUN_1400283d0(longlong * param_1, longlong param_2)

longlong * FUN_1400283d0(longlong *param_1,longlong param_2)

{
  FUN_140027030(param_1,param_2);
  return param_1;
}


// ==== FUN_1400283f0 @ 1400283f0  undefined8 * FUN_1400283f0(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_1400283f0(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_140028430 @ 140028430  undefined FUN_140028430(longlong * param_1)

void FUN_140028430(longlong *param_1)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *plVar4;
  
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  lVar2 = param_1[1];
  if (*(char *)(lVar2 + 0x29) == '\0') {
    plVar3 = *(longlong **)(lVar2 + 0x10);
    if (*(char *)((longlong)plVar3 + 0x29) != '\0') {
      lVar2 = *(longlong *)(lVar2 + 8);
      cVar1 = *(char *)(lVar2 + 0x29);
      while ((cVar1 == '\0' && (param_1[1] == *(longlong *)(lVar2 + 0x10)))) {
        param_1[1] = lVar2;
        lVar2 = *(longlong *)(lVar2 + 8);
        cVar1 = *(char *)(lVar2 + 0x29);
      }
      param_1[1] = lVar2;
      return;
    }
    cVar1 = *(char *)(*plVar3 + 0x29);
    plVar4 = (longlong *)*plVar3;
    while (cVar1 == '\0') {
      cVar1 = *(char *)(*plVar4 + 0x29);
      plVar3 = plVar4;
      plVar4 = (longlong *)*plVar4;
    }
    param_1[1] = (longlong)plVar3;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000140028454. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_1400284c0 @ 1400284c0  undefined8 * FUN_1400284c0(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_1400284c0(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[6])) ||
     ((ulonglong)(param_3[6] + param_3[7]) < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_140028560 @ 140028560  undefined8 * FUN_140028560(undefined8 * param_1)

undefined8 * FUN_140028560(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_1400285a0 @ 1400285a0  undefined FUN_1400285a0(undefined8 param_1, ulonglong param_2)

void FUN_1400285a0(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 8)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 8);
  return;
}


// ==== FUN_140028620 @ 140028620  undefined8 * FUN_140028620(undefined8 * param_1)

undefined8 * FUN_140028620(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140028660 @ 140028660  undefined FUN_140028660(undefined8 param_1, ulonglong param_2)

void FUN_140028660(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 8)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 8);
  return;
}


// ==== FUN_1400286d0 @ 1400286d0  undefined8 * FUN_1400286d0(undefined8 * param_1)

undefined8 * FUN_1400286d0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140028710 @ 140028710  undefined8 * FUN_140028710(undefined8 * param_1)

undefined8 * FUN_140028710(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140028750 @ 140028750  undefined FUN_140028750(undefined8 param_1, ulonglong param_2)

void FUN_140028750(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x30)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 * 0x30);
  return;
}


// ==== FUN_1400287e0 @ 1400287e0  undefined8 * FUN_1400287e0(undefined8 * param_1)

undefined8 * FUN_1400287e0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140028820 @ 140028820  bool FUN_140028820(undefined8 * param_1, longlong * param_2)

bool FUN_140028820(undefined8 *param_1,longlong *param_2)

{
  longlong lVar1;
  
  if (param_1 == (undefined8 *)0x0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    return false;
  }
  if (param_2 != (longlong *)0x0) {
    lVar1 = (**(code **)(*param_2 + 0xb0))(param_2,0x1040,param_1);
    return lVar1 != 0;
  }
  *param_1 = 0;
  return false;
}


// ==== FUN_1400288e0 @ 1400288e0  void * FUN_1400288e0(void * param_1, longlong param_2, longlong param_3)

void * FUN_1400288e0(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _Dst = (void *)(param_3 + lVar1 * -4);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 4,param_1,lVar1 * 4);
  }
  return _Dst;
}


// ==== FUN_140028930 @ 140028930  void * FUN_140028930(void * param_1, longlong param_2, longlong param_3)

void * FUN_140028930(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _Dst = (void *)(param_3 + lVar1 * -8);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 8,param_1,lVar1 * 8);
  }
  return _Dst;
}


// ==== FUN_1400289f0 @ 1400289f0  void * FUN_1400289f0(void * param_1, longlong param_2, void * param_3)

void * FUN_1400289f0(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _DstSize = lVar1 * 4;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_140028a30 @ 140028a30  void * FUN_140028a30(void * param_1, longlong param_2, void * param_3)

void * FUN_140028a30(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_140028a70 @ 140028a70  longlong FUN_140028a70(longlong * param_1)

longlong FUN_140028a70(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140028a92;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140028a92:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_140028ab0 @ 140028ab0  longlong * FUN_140028ab0(longlong * param_1)

longlong * FUN_140028ab0(longlong *param_1)

{
  FUN_140026930(param_1);
  return param_1;
}


// ==== FUN_140028ad0 @ 140028ad0  longlong FUN_140028ad0(longlong * param_1)

longlong FUN_140028ad0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140028af2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140028af2:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_140028b10 @ 140028b10  undefined FUN_140028b10(undefined8 * param_1)

void FUN_140028b10(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140028b30 @ 140028b30  undefined FUN_140028b30(undefined8 * param_1)

void FUN_140028b30(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140028b50 @ 140028b50  undefined FUN_140028b50(undefined8 * param_1)

void FUN_140028b50(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140028b70 @ 140028b70  undefined FUN_140028b70(undefined8 * param_1)

void FUN_140028b70(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140028b90 @ 140028b90  undefined FUN_140028b90(undefined8 * param_1)

void FUN_140028b90(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140028bf0 @ 140028bf0  undefined FUN_140028bf0(longlong param_1)

void FUN_140028bf0(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = *(longlong *)(param_1 + 0x38);
  while (lVar1 != 0) {
    if ((*(longlong *)(param_1 + 0x38) != 0) &&
       (lVar1 = *(longlong *)(param_1 + 0x38) + -1, *(longlong *)(param_1 + 0x38) = lVar1,
       lVar1 == 0)) {
      *(undefined8 *)(param_1 + 0x30) = 0;
    }
    lVar1 = *(longlong *)(param_1 + 0x38);
  }
  lVar1 = *(longlong *)(param_1 + 0x28);
  while (lVar1 != 0) {
    lVar1 = lVar1 + -1;
    if (*(longlong *)(*(longlong *)(param_1 + 0x20) + lVar1 * 8) != 0) {
      operator_delete(*(void **)(*(longlong *)(param_1 + 0x20) + lVar1 * 8));
    }
  }
  if (*(void **)(param_1 + 0x20) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x20));
  }
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_140028c90 @ 140028c90  longlong * FUN_140028c90(longlong * param_1)

longlong * FUN_140028c90(longlong *param_1)

{
  FUN_140026d50(param_1);
  return param_1;
}


// ==== FUN_140028cb0 @ 140028cb0  undefined8 FUN_140028cb0(longlong param_1, ulonglong param_2)

undefined8 FUN_140028cb0(longlong param_1,ulonglong param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  longlong lVar3;
  
  uVar2 = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  if (param_2 != 0) {
    if (0x3fffffffffffffff < param_2) {
      FUN_1400269c0();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_140027df0(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    lVar3 = lVar3 + param_2 * 4;
    *(longlong *)(param_1 + 0x28) = lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
  }
  return uVar2;
}


// ==== FUN_140028d10 @ 140028d10  longlong * FUN_140028d10(longlong * param_1)

longlong * FUN_140028d10(longlong *param_1)

{
  FUN_140028040(param_1);
  return param_1;
}


// ==== FUN_140028d30 @ 140028d30  undefined8 FUN_140028d30(longlong param_1, ulonglong param_2)

undefined8 FUN_140028d30(longlong param_1,ulonglong param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  longlong lVar3;
  
  uVar2 = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  if (param_2 != 0) {
    if (0x1fffffffffffffff < param_2) {
      FUN_140026a70();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_1400280e0(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    lVar3 = lVar3 + param_2 * 8;
    *(longlong *)(param_1 + 0x28) = lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
  }
  return uVar2;
}


// ==== FUN_140028d90 @ 140028d90  undefined8 * FUN_140028d90(undefined8 * param_1)

undefined8 * FUN_140028d90(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140028dd0 @ 140028dd0  undefined8 * FUN_140028dd0(undefined8 * param_1)

undefined8 * FUN_140028dd0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140028e20 @ 140028e20  undefined8 * FUN_140028e20(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_140028e20(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_140028e70 @ 140028e70  undefined8 * FUN_140028e70(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_140028e70(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_140028eb0 @ 140028eb0  longlong * FUN_140028eb0(longlong * param_1)

longlong * FUN_140028eb0(longlong *param_1)

{
  FUN_140028310(param_1);
  return param_1;
}


// ==== FUN_140028ee0 @ 140028ee0  undefined8 * FUN_140028ee0(undefined8 * param_1)

undefined8 * FUN_140028ee0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140028f20 @ 140028f20  longlong * FUN_140028f20(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_140028f20(longlong *param_1,longlong *param_2,longlong param_3)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  
  plVar2 = (longlong *)*param_1;
  lVar3 = param_1[1];
  lVar4 = 0;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar4;
  }
  else {
    lVar5 = *plVar2;
  }
  uVar1 = lVar3 + param_3 * 8;
  if (uVar1 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar2 != (longlong *)0x0) {
      lVar4 = *plVar2;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar1) goto LAB_140028f8a;
  }
  _invalid_parameter_noinfo();
LAB_140028f8a:
  *param_2 = (longlong)plVar2;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_140028fc0 @ 140028fc0  undefined8 * FUN_140028fc0(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140028fc0(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_140029020 @ 140029020  longlong * FUN_140029020(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_140029020(longlong *param_1,longlong *param_2,longlong param_3)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  
  plVar2 = (longlong *)*param_1;
  lVar3 = param_1[1];
  lVar4 = 0;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar4;
  }
  else {
    lVar5 = *plVar2;
  }
  uVar1 = lVar3 + param_3 * 4;
  if (uVar1 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar2 != (longlong *)0x0) {
      lVar4 = *plVar2;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar1) goto LAB_14002908a;
  }
  _invalid_parameter_noinfo();
LAB_14002908a:
  *param_2 = (longlong)plVar2;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_1400290c0 @ 1400290c0  undefined8 * FUN_1400290c0(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_1400290c0(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_140029120 @ 140029120  undefined8 * FUN_140029120(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_140029120(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_140029170 @ 140029170  longlong * FUN_140029170(longlong * param_1)

longlong * FUN_140029170(longlong *param_1)

{
  FUN_140028430(param_1);
  return param_1;
}


// ==== FUN_140029190 @ 140029190  undefined8 * FUN_140029190(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140029190(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[6])) ||
     ((ulonglong)(param_3[6] + param_3[7]) < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_1400291f0 @ 1400291f0  undefined FUN_1400291f0(undefined8 * param_1)

void FUN_1400291f0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140029210 @ 140029210  undefined FUN_140029210(void)

void FUN_140029210(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x58);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = 0;
  }
  if (puVar1 + 1 != (undefined8 *)0x0) {
    puVar1[1] = 0;
  }
  if (puVar1 + 2 != (undefined8 *)0x0) {
    puVar1[2] = 0;
  }
  *(undefined1 *)(puVar1 + 10) = 1;
  *(undefined1 *)((longlong)puVar1 + 0x51) = 0;
  return;
}


// ==== FUN_140029270 @ 140029270  undefined FUN_140029270(void)

void FUN_140029270(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x58);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = 0;
  }
  if (puVar1 + 1 != (undefined8 *)0x0) {
    puVar1[1] = 0;
  }
  if (puVar1 + 2 != (undefined8 *)0x0) {
    puVar1[2] = 0;
  }
  *(undefined1 *)(puVar1 + 10) = 1;
  *(undefined1 *)((longlong)puVar1 + 0x51) = 0;
  return;
}


// ==== FUN_1400292d0 @ 1400292d0  undefined8 FUN_1400292d0(longlong param_1, ulonglong param_2)

undefined8 FUN_1400292d0(longlong param_1,ulonglong param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  longlong lVar3;
  
  uVar2 = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  if (param_2 != 0) {
    if (0x1fffffffffffffff < param_2) {
      FUN_140026ea0();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_1400285a0(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    lVar3 = lVar3 + param_2 * 8;
    *(longlong *)(param_1 + 0x28) = lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
  }
  return uVar2;
}


// ==== FUN_140029330 @ 140029330  undefined8 * FUN_140029330(undefined8 * param_1)

undefined8 * FUN_140029330(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140029380 @ 140029380  undefined8 FUN_140029380(longlong param_1, ulonglong param_2)

undefined8 FUN_140029380(longlong param_1,ulonglong param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  longlong lVar3;
  
  uVar2 = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  if (param_2 != 0) {
    if (0x1fffffffffffffff < param_2) {
      FUN_140026f30();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_140028660(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    lVar3 = lVar3 + param_2 * 8;
    *(longlong *)(param_1 + 0x28) = lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
  }
  return uVar2;
}


// ==== FUN_1400293e0 @ 1400293e0  undefined8 * FUN_1400293e0(undefined8 * param_1)

undefined8 * FUN_1400293e0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140029430 @ 140029430  longlong * FUN_140029430(longlong * param_1, longlong * param_2)

longlong * FUN_140029430(longlong *param_1,longlong *param_2)

{
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  FUN_140028040(param_1);
  return param_2;
}


// ==== FUN_140029480 @ 140029480  undefined8 * FUN_140029480(undefined8 * param_1)

undefined8 * FUN_140029480(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_1400294d0 @ 1400294d0  undefined8 * FUN_1400294d0(undefined8 * param_1)

undefined8 * FUN_1400294d0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140029520 @ 140029520  undefined8 * FUN_140029520(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_140029520(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  undefined8 uVar1;
  
  uVar1 = *(undefined8 *)(param_3 + 8);
  if (param_1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_2 = *param_1;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_140029570 @ 140029570  undefined8 * FUN_140029570(undefined8 * param_1, undefined8 * param_2, longlong * param_3)

undefined8 * FUN_140029570(undefined8 *param_1,undefined8 *param_2,longlong *param_3)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong lVar5;
  longlong *plVar6;
  longlong *plVar7;
  longlong *plVar8;
  longlong *plVar9;
  undefined **local_80 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_68 [40];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_40 [40];
  
  plVar2 = (longlong *)param_3[1];
  if (*(char *)((longlong)plVar2 + 0x29) != '\0') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_40,"invalid map/set<T> iterator");
    std::exception::exception((exception *)local_80);
    local_80[0] = std::logic_error::vftable;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_68,local_40);
    local_80[0] = std::out_of_range::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_80,(ThrowInfo *)&DAT_1400feda0);
  }
  FUN_140028430(param_3);
  plVar8 = (longlong *)*plVar2;
  if (*(char *)((longlong)plVar8 + 0x29) == '\0') {
    plVar9 = plVar8;
    if (*(char *)(plVar2[2] + 0x29) == '\0') {
      plVar7 = (longlong *)param_3[1];
      plVar9 = (longlong *)plVar7[2];
      if (plVar7 != plVar2) {
        plVar8[1] = (longlong)plVar7;
        *plVar7 = *plVar2;
        plVar8 = plVar7;
        if (plVar7 != (longlong *)plVar2[2]) {
          plVar8 = (longlong *)plVar7[1];
          if (*(char *)((longlong)plVar9 + 0x29) == '\0') {
            plVar9[1] = (longlong)plVar8;
          }
          *plVar8 = (longlong)plVar9;
          plVar7[2] = plVar2[2];
          *(longlong **)(plVar2[2] + 8) = plVar7;
        }
        if (*(longlong **)(param_1[6] + 8) == plVar2) {
          *(longlong **)(param_1[6] + 8) = plVar7;
        }
        else {
          puVar4 = (undefined8 *)plVar2[1];
          if ((longlong *)*puVar4 == plVar2) {
            *puVar4 = plVar7;
          }
          else {
            puVar4[2] = plVar7;
          }
        }
        plVar7[1] = plVar2[1];
        plVar3 = plVar2 + 5;
        plVar7 = plVar7 + 5;
        if (plVar7 != plVar3) {
          lVar5 = *plVar7;
          *(char *)plVar7 = (char)*plVar3;
          *(char *)plVar3 = (char)lVar5;
        }
        goto LAB_14002975c;
      }
    }
  }
  else {
    plVar9 = (longlong *)plVar2[2];
  }
  plVar8 = (longlong *)plVar2[1];
  if (*(char *)((longlong)plVar9 + 0x29) == '\0') {
    plVar9[1] = (longlong)plVar8;
  }
  if (*(longlong **)(param_1[6] + 8) == plVar2) {
    *(longlong **)(param_1[6] + 8) = plVar9;
  }
  else if ((longlong *)*plVar8 == plVar2) {
    *plVar8 = (longlong)plVar9;
  }
  else {
    plVar8[2] = (longlong)plVar9;
  }
  if (*(longlong **)param_1[6] == plVar2) {
    plVar7 = plVar8;
    if (*(char *)((longlong)plVar9 + 0x29) == '\0') {
      cVar1 = *(char *)(*plVar9 + 0x29);
      plVar3 = (longlong *)*plVar9;
      plVar7 = plVar9;
      while (plVar6 = plVar3, cVar1 == '\0') {
        plVar3 = (longlong *)*plVar6;
        cVar1 = *(char *)((longlong)plVar3 + 0x29);
        plVar7 = plVar6;
      }
    }
    *(longlong **)param_1[6] = plVar7;
  }
  if (*(longlong **)(param_1[6] + 0x10) == plVar2) {
    plVar7 = plVar8;
    if (*(char *)((longlong)plVar9 + 0x29) == '\0') {
      cVar1 = *(char *)(plVar9[2] + 0x29);
      plVar3 = (longlong *)plVar9[2];
      plVar7 = plVar9;
      while (plVar6 = plVar3, cVar1 == '\0') {
        plVar3 = (longlong *)plVar6[2];
        cVar1 = *(char *)((longlong)plVar3 + 0x29);
        plVar7 = plVar6;
      }
    }
    *(longlong **)(param_1[6] + 0x10) = plVar7;
  }
LAB_14002975c:
  if ((char)plVar2[5] == '\x01') {
    if (plVar9 != *(longlong **)(param_1[6] + 8)) {
      do {
        plVar7 = plVar8;
        if ((char)plVar9[5] != '\x01') break;
        plVar8 = (longlong *)*plVar7;
        if (plVar9 == plVar8) {
          plVar8 = (longlong *)plVar7[2];
          if ((char)plVar8[5] == '\0') {
            *(undefined1 *)(plVar8 + 5) = 1;
            *(undefined1 *)(plVar7 + 5) = 0;
            FUN_1400270f0((longlong)param_1,(longlong)plVar7);
            plVar8 = (longlong *)plVar7[2];
          }
          if (*(char *)((longlong)plVar8 + 0x29) == '\0') {
            if ((*(char *)(*plVar8 + 0x28) != '\x01') || (*(char *)(plVar8[2] + 0x28) != '\x01')) {
              if (*(char *)(plVar8[2] + 0x28) == '\x01') {
                *(undefined1 *)(*plVar8 + 0x28) = 1;
                *(undefined1 *)(plVar8 + 5) = 0;
                FUN_140027180((longlong)param_1,plVar8);
                plVar8 = (longlong *)plVar7[2];
              }
              *(char *)(plVar8 + 5) = (char)plVar7[5];
              *(undefined1 *)(plVar7 + 5) = 1;
              *(undefined1 *)(plVar8[2] + 0x28) = 1;
              FUN_1400270f0((longlong)param_1,(longlong)plVar7);
              break;
            }
            *(undefined1 *)(plVar8 + 5) = 0;
          }
        }
        else {
          if ((char)plVar8[5] == '\0') {
            *(undefined1 *)(plVar8 + 5) = 1;
            *(undefined1 *)(plVar7 + 5) = 0;
            FUN_140027180((longlong)param_1,plVar7);
            plVar8 = (longlong *)*plVar7;
          }
          if (*(char *)((longlong)plVar8 + 0x29) == '\0') {
            if ((*(char *)(plVar8[2] + 0x28) != '\x01') || (*(char *)(*plVar8 + 0x28) != '\x01')) {
              if (*(char *)(*plVar8 + 0x28) == '\x01') {
                *(undefined1 *)(plVar8[2] + 0x28) = 1;
                *(undefined1 *)(plVar8 + 5) = 0;
                FUN_1400270f0((longlong)param_1,(longlong)plVar8);
                plVar8 = (longlong *)*plVar7;
              }
              *(char *)(plVar8 + 5) = (char)plVar7[5];
              *(undefined1 *)(plVar7 + 5) = 1;
              *(undefined1 *)(*plVar8 + 0x28) = 1;
              FUN_140027180((longlong)param_1,plVar7);
              break;
            }
            *(undefined1 *)(plVar8 + 5) = 0;
          }
        }
        plVar8 = (longlong *)plVar7[1];
        plVar9 = plVar7;
      } while (plVar7 != *(longlong **)(param_1[6] + 8));
    }
    *(undefined1 *)(plVar9 + 5) = 1;
  }
  operator_delete(plVar2);
  if (param_1[7] != 0) {
    param_1[7] = param_1[7] + -1;
  }
  lVar5 = param_3[1];
  *param_2 = *param_1;
  param_2[1] = lVar5;
  return param_2;
}


// ==== FUN_140029930 @ 140029930  undefined FUN_140029930(void)

void FUN_140029930(void)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x30);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = 0;
  }
  if (puVar1 + 1 != (undefined8 *)0x0) {
    puVar1[1] = 0;
  }
  if (puVar1 + 2 != (undefined8 *)0x0) {
    puVar1[2] = 0;
  }
  *(undefined1 *)(puVar1 + 5) = 1;
  *(undefined1 *)((longlong)puVar1 + 0x29) = 0;
  return;
}


// ==== FUN_140029990 @ 140029990  longlong * FUN_140029990(longlong * param_1, longlong * param_2)

longlong * FUN_140029990(longlong *param_1,longlong *param_2)

{
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  FUN_140028430(param_1);
  return param_2;
}


// ==== FUN_1400299c0 @ 1400299c0  undefined FUN_1400299c0(undefined8 param_1, longlong * param_2)

void FUN_1400299c0(undefined8 param_1,longlong *param_2)

{
  char cVar1;
  longlong *plVar2;
  
  cVar1 = *(char *)((longlong)param_2 + 0x29);
  while (cVar1 == '\0') {
    FUN_1400299c0(param_1,(longlong *)param_2[2]);
    plVar2 = (longlong *)*param_2;
    operator_delete(param_2);
    param_2 = plVar2;
    cVar1 = *(char *)((longlong)plVar2 + 0x29);
  }
  return;
}


// ==== FUN_140029a10 @ 140029a10  undefined8 * FUN_140029a10(undefined8 * param_1)

undefined8 * FUN_140029a10(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140029a90 @ 140029a90  void * FUN_140029a90(void * param_1, longlong param_2, longlong param_3)

void * FUN_140029a90(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _Dst = (void *)(param_3 + lVar1 * -4);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 4,param_1,lVar1 * 4);
  }
  return _Dst;
}


// ==== FUN_140029b00 @ 140029b00  void * FUN_140029b00(void * param_1, longlong param_2, longlong param_3)

void * FUN_140029b00(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _Dst = (void *)(param_3 + lVar1 * -8);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 8,param_1,lVar1 * 8);
  }
  return _Dst;
}


// ==== FUN_140029bc0 @ 140029bc0  void * FUN_140029bc0(void * param_1, longlong param_2, void * param_3)

void * FUN_140029bc0(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _DstSize = lVar1 * 4;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_140029c00 @ 140029c00  void * FUN_140029c00(void * param_1, longlong param_2, void * param_3)

void * FUN_140029c00(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_140029c40 @ 140029c40  longlong * FUN_140029c40(longlong * param_1)

longlong * FUN_140029c40(longlong *param_1)

{
  FUN_140028040(param_1);
  return param_1;
}


// ==== FUN_140029c60 @ 140029c60  undefined FUN_140029c60(undefined8 * param_1)

void FUN_140029c60(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140029c80 @ 140029c80  undefined FUN_140029c80(undefined8 * param_1)

void FUN_140029c80(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140029ca0 @ 140029ca0  undefined FUN_140029ca0(undefined8 * param_1)

void FUN_140029ca0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140029cc0 @ 140029cc0  undefined8 * FUN_140029cc0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140029cc0(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  longlong lVar2;
  undefined8 uVar3;
  
  uVar1 = param_1[6];
  lVar2 = param_1[7];
  *param_2 = 0;
  if (uVar1 + lVar2 < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar3 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar3;
  return param_2;
}


// ==== FUN_140029d10 @ 140029d10  undefined8 * FUN_140029d10(undefined8 * param_1)

undefined8 * FUN_140029d10(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140029da0 @ 140029da0  undefined8 * FUN_140029da0(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_140029da0(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_140029de0 @ 140029de0  undefined FUN_140029de0(longlong param_1)

void FUN_140029de0(longlong param_1)

{
  if (*(void **)(param_1 + 0x18) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_140029e10 @ 140029e10  undefined8 * FUN_140029e10(undefined8 * param_1)

undefined8 * FUN_140029e10(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140029e60 @ 140029e60  undefined8 * FUN_140029e60(undefined8 * param_1, undefined8 param_2, undefined8 * param_3)

undefined8 * FUN_140029e60(undefined8 *param_1,undefined8 param_2,undefined8 *param_3)

{
  *param_1 = 0;
  param_1[1] = param_2;
  if (param_3 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_1 = *param_3;
  return param_1;
}


// ==== FUN_140029ea0 @ 140029ea0  longlong * FUN_140029ea0(longlong * param_1)

longlong * FUN_140029ea0(longlong *param_1)

{
  FUN_140028310(param_1);
  return param_1;
}


// ==== FUN_140029ec0 @ 140029ec0  undefined FUN_140029ec0(longlong param_1)

void FUN_140029ec0(longlong param_1)

{
  if (*(void **)(param_1 + 0x18) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_140029ef0 @ 140029ef0  undefined8 * FUN_140029ef0(undefined8 * param_1)

undefined8 * FUN_140029ef0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_140029f40 @ 140029f40  undefined8 * FUN_140029f40(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140029f40(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_140029fa0 @ 140029fa0  undefined8 * FUN_140029fa0(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140029fa0(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_14002a010 @ 14002a010  longlong * FUN_14002a010(longlong * param_1)

longlong * FUN_14002a010(longlong *param_1)

{
  FUN_140028430(param_1);
  return param_1;
}


// ==== FUN_14002a030 @ 14002a030  undefined FUN_14002a030(longlong param_1)

void FUN_14002a030(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = FUN_140029210();
  *(longlong *)(param_1 + 0x30) = lVar1;
  *(undefined1 *)(lVar1 + 0x51) = 1;
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)*(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x30);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 0x10) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = 0;
  return;
}


// ==== FUN_14002a070 @ 14002a070  undefined FUN_14002a070(longlong param_1)

void FUN_14002a070(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = FUN_140029270();
  *(longlong *)(param_1 + 0x30) = lVar1;
  *(undefined1 *)(lVar1 + 0x51) = 1;
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)*(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x30);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 0x10) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = 0;
  return;
}


// ==== FUN_14002a0b0 @ 14002a0b0  undefined8 * FUN_14002a0b0(undefined8 * param_1)

undefined8 * FUN_14002a0b0(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  puVar2 = (undefined8 *)0x0;
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_1;
    puVar2 = puVar1;
  }
  *param_1 = puVar2;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  return param_1;
}


// ==== FUN_14002a110 @ 14002a110  undefined8 * FUN_14002a110(undefined8 * param_1)

undefined8 * FUN_14002a110(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  puVar2 = (undefined8 *)0x0;
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_1;
    puVar2 = puVar1;
  }
  *param_1 = puVar2;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  return param_1;
}


// ==== FUN_14002a170 @ 14002a170  undefined8 * FUN_14002a170(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14002a170(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[3];
  *param_2 = 0;
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14002a1c0 @ 14002a1c0  undefined8 * FUN_14002a1c0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14002a1c0(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[4];
  *param_2 = 0;
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14002a210 @ 14002a210  undefined8 * FUN_14002a210(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14002a210(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[3];
  *param_2 = 0;
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14002a260 @ 14002a260  undefined8 * FUN_14002a260(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14002a260(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[4];
  *param_2 = 0;
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14002a2b0 @ 14002a2b0  undefined FUN_14002a2b0(undefined8 * param_1)

void FUN_14002a2b0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14002a2d0 @ 14002a2d0  undefined8 * FUN_14002a2d0(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14002a2d0(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  undefined8 uVar1;
  
  uVar1 = *(undefined8 *)(param_3 + 8);
  if (param_1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_2 = *param_1;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_14002a320 @ 14002a320  undefined FUN_14002a320(longlong param_1)

void FUN_14002a320(longlong param_1)

{
  if (*(void **)(param_1 + 0x18) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_14002a350 @ 14002a350  undefined FUN_14002a350(longlong param_1)

void FUN_14002a350(longlong param_1)

{
  if (*(void **)(param_1 + 0x18) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_14002a380 @ 14002a380  undefined8 * FUN_14002a380(undefined8 * param_1)

undefined8 * FUN_14002a380(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_14002a3d0 @ 14002a3d0  undefined8 * FUN_14002a3d0(undefined8 * param_1)

undefined8 * FUN_14002a3d0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_14002a420 @ 14002a420  undefined FUN_14002a420(longlong param_1)

void FUN_14002a420(longlong param_1)

{
  longlong lVar1;
  
  lVar1 = FUN_140029930();
  *(longlong *)(param_1 + 0x30) = lVar1;
  *(undefined1 *)(lVar1 + 0x29) = 1;
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)*(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x30);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 0x10) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = 0;
  return;
}


// ==== FUN_14002a460 @ 14002a460  undefined FUN_14002a460(longlong param_1)

void FUN_14002a460(longlong param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  
  plVar2 = *(longlong **)(*(longlong *)(param_1 + 0x30) + 8);
  cVar1 = *(char *)((longlong)plVar2 + 0x29);
  while (cVar1 == '\0') {
    FUN_1400299c0(param_1,(longlong *)plVar2[2]);
    plVar3 = (longlong *)*plVar2;
    operator_delete(plVar2);
    plVar2 = plVar3;
    cVar1 = *(char *)((longlong)plVar3 + 0x29);
  }
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)*(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x30);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 0x10) = *(longlong *)(param_1 + 0x30);
  return;
}


// ==== FUN_14002a4e0 @ 14002a4e0  undefined8 * FUN_14002a4e0(undefined8 * param_1)

undefined8 * FUN_14002a4e0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_14002a530 @ 14002a530  void * FUN_14002a530(longlong param_1, longlong param_2, void * param_3)

void * FUN_14002a530(longlong param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = *(longlong *)(param_2 + 8) - (longlong)*(void **)(param_1 + 8) >> 2;
  _DstSize = lVar1 * 4;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,*(void **)(param_1 + 8),_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14002a5a0 @ 14002a5a0  void * FUN_14002a5a0(longlong param_1, longlong param_2, void * param_3)

void * FUN_14002a5a0(longlong param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = *(longlong *)(param_2 + 8) - (longlong)*(void **)(param_1 + 8) >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,*(void **)(param_1 + 8),_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14002a610 @ 14002a610  void * FUN_14002a610(void * param_1, longlong param_2, void * param_3)

void * FUN_14002a610(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 2;
  _DstSize = lVar1 * 4;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14002a650 @ 14002a650  void * FUN_14002a650(void * param_1, longlong param_2, void * param_3)

void * FUN_14002a650(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14002a690 @ 14002a690  undefined4 FUN_14002a690(longlong * param_1)

undefined4 FUN_14002a690(longlong *param_1)

{
  longlong lVar1;
  ulonglong uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  longlong local_18;
  ulonglong local_10;
  
  if (param_1[7] == 0) {
    uVar3 = 0;
  }
  else {
    uVar2 = param_1[6];
    if (param_1[7] + uVar2 < uVar2) {
      _invalid_parameter_noinfo();
    }
    local_18 = *param_1;
    local_10 = uVar2;
    puVar4 = (undefined4 *)FUN_140026b80(&local_18);
    uVar3 = *puVar4;
    if (param_1[7] != 0) {
      param_1[6] = param_1[6] + 1;
      if ((ulonglong)(param_1[5] << 2) <= (ulonglong)param_1[6]) {
        param_1[6] = 0;
      }
      lVar1 = param_1[7] + -1;
      param_1[7] = lVar1;
      if (lVar1 == 0) {
        param_1[6] = 0;
        return uVar3;
      }
    }
  }
  return uVar3;
}


// ==== FUN_14002a720 @ 14002a720  undefined8 * FUN_14002a720(undefined8 * param_1)

undefined8 * FUN_14002a720(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  puVar2 = (undefined8 *)0x0;
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_1;
    puVar2 = puVar1;
  }
  *param_1 = puVar2;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_14002a780 @ 14002a780  undefined FUN_14002a780(undefined8 * param_1)

void FUN_14002a780(undefined8 *param_1)

{
  FUN_140028bf0((longlong)param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14002a8d0 @ 14002a8d0  undefined8 * FUN_14002a8d0(undefined8 * param_1)

undefined8 * FUN_14002a8d0(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  puVar2 = (undefined8 *)0x0;
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_1;
    puVar2 = puVar1;
  }
  *param_1 = puVar2;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  return param_1;
}


// ==== FUN_14002a930 @ 14002a930  undefined FUN_14002a930(undefined8 * param_1)

void FUN_14002a930(undefined8 *param_1)

{
  if ((void *)param_1[3] != (void *)0x0) {
    operator_delete((void *)param_1[3]);
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14002a970 @ 14002a970  undefined8 * FUN_14002a970(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14002a970(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[3];
  *param_2 = 0;
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14002a9c0 @ 14002a9c0  undefined8 * FUN_14002a9c0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14002a9c0(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[4];
  *param_2 = 0;
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14002aa10 @ 14002aa10  undefined8 * FUN_14002aa10(undefined8 * param_1)

undefined8 * FUN_14002aa10(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  puVar2 = (undefined8 *)0x0;
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_1;
    puVar2 = puVar1;
  }
  *param_1 = puVar2;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  return param_1;
}


// ==== FUN_14002aa70 @ 14002aa70  undefined FUN_14002aa70(undefined8 * param_1)

void FUN_14002aa70(undefined8 *param_1)

{
  if ((void *)param_1[3] != (void *)0x0) {
    operator_delete((void *)param_1[3]);
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14002aab0 @ 14002aab0  undefined8 * FUN_14002aab0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14002aab0(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[3];
  *param_2 = 0;
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14002ab00 @ 14002ab00  undefined8 * FUN_14002ab00(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14002ab00(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[4];
  *param_2 = 0;
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14002ab50 @ 14002ab50  longlong * FUN_14002ab50(longlong * param_1, longlong * param_2)

longlong * FUN_14002ab50(longlong *param_1,longlong *param_2)

{
  *param_2 = *param_1;
  param_2[1] = param_1[1];
  FUN_140028430(param_1);
  return param_2;
}


// ==== FUN_14002ab80 @ 14002ab80  undefined FUN_14002ab80(undefined8 * param_1)

void FUN_14002ab80(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14002aba0 @ 14002aba0  undefined FUN_14002aba0(undefined8 * param_1)

void FUN_14002aba0(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14002ac00 @ 14002ac00  undefined8 * FUN_14002ac00(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14002ac00(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  undefined8 uVar1;
  
  uVar1 = *(undefined8 *)(param_3 + 8);
  if (param_1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
  }
  *param_2 = *param_1;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_14002ac90 @ 14002ac90  undefined FUN_14002ac90(undefined8 * param_1)

void FUN_14002ac90(undefined8 *param_1)

{
  if ((void *)param_1[3] != (void *)0x0) {
    operator_delete((void *)param_1[3]);
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14002acd0 @ 14002acd0  undefined FUN_14002acd0(undefined8 * param_1)

void FUN_14002acd0(undefined8 *param_1)

{
  if ((void *)param_1[3] != (void *)0x0) {
    operator_delete((void *)param_1[3]);
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14002ad10 @ 14002ad10  undefined FUN_14002ad10(undefined8 * param_1)

void FUN_14002ad10(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14002ad30 @ 14002ad30  undefined8 * FUN_14002ad30(undefined8 * param_1)

undefined8 * FUN_14002ad30(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_14002ad80 @ 14002ad80  undefined8 * FUN_14002ad80(undefined8 * param_1)

undefined8 * FUN_14002ad80(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_14002add0 @ 14002add0  longlong * FUN_14002add0(longlong * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_14002add0(longlong *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  char cVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong local_28;
  longlong lStack_20;
  undefined8 local_18 [2];
  
  lVar2 = *(longlong *)param_1[6];
  if ((*param_3 == 0) || (*param_3 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (param_3[1] == lVar2) {
    lVar2 = param_1[6];
    if ((*param_4 == 0) || (*param_4 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    if (param_4[1] == lVar2) {
      FUN_14002a460((longlong)param_1);
      param_2[1] = *(longlong *)param_1[6];
      *param_2 = *param_1;
      return param_2;
    }
  }
  while( true ) {
    if ((*param_3 == 0) || (*param_3 != *param_4)) {
      _invalid_parameter_noinfo();
    }
    lVar2 = *param_3;
    if (param_3[1] == param_4[1]) break;
    lVar3 = param_3[1];
    if (*param_3 == 0) {
      _invalid_parameter_noinfo();
    }
    lVar4 = param_3[1];
    if (*(char *)(lVar4 + 0x29) == '\0') {
      plVar6 = *(longlong **)(lVar4 + 0x10);
      if (*(char *)((longlong)plVar6 + 0x29) == '\0') {
        cVar1 = *(char *)(*plVar6 + 0x29);
        plVar5 = (longlong *)*plVar6;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar5 + 0x29);
          plVar6 = plVar5;
          plVar5 = (longlong *)*plVar5;
        }
      }
      else {
        plVar6 = *(longlong **)(lVar4 + 8);
        cVar1 = *(char *)((longlong)plVar6 + 0x29);
        while ((cVar1 == '\0' && (param_3[1] == plVar6[2]))) {
          param_3[1] = (longlong)plVar6;
          plVar6 = (longlong *)plVar6[1];
          cVar1 = *(char *)((longlong)plVar6 + 0x29);
        }
      }
      param_3[1] = (longlong)plVar6;
    }
    else {
      _invalid_parameter_noinfo();
    }
    local_28 = lVar2;
    lStack_20 = lVar3;
    FUN_140029570(param_1,local_18,&local_28);
  }
  lVar2 = param_3[1];
  *param_2 = *param_1;
  param_2[1] = lVar2;
  return param_2;
}


// ==== FUN_14002af80 @ 14002af80  undefined8 * FUN_14002af80(undefined8 * param_1)

undefined8 * FUN_14002af80(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_14002afd0 @ 14002afd0  void * FUN_14002afd0(undefined8 param_1, longlong param_2, longlong param_3, void * param_4)

void * FUN_14002afd0(undefined8 param_1,longlong param_2,longlong param_3,void *param_4)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = *(longlong *)(param_3 + 8) - (longlong)*(void **)(param_2 + 8) >> 2;
  _DstSize = lVar1 * 4;
  if (lVar1 != 0) {
    memmove_s(param_4,_DstSize,*(void **)(param_2 + 8),_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_4);
}


// ==== FUN_14002b070 @ 14002b070  void * FUN_14002b070(undefined8 param_1, longlong param_2, longlong param_3, void * param_4)

void * FUN_14002b070(undefined8 param_1,longlong param_2,longlong param_3,void *param_4)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = *(longlong *)(param_3 + 8) - (longlong)*(void **)(param_2 + 8) >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_4,_DstSize,*(void **)(param_2 + 8),_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_4);
}


// ==== FUN_14002b110 @ 14002b110  void * FUN_14002b110(undefined8 param_1, void * param_2, longlong param_3, void * param_4)

void * FUN_14002b110(undefined8 param_1,void *param_2,longlong param_3,void *param_4)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_3 - (longlong)param_2 >> 2;
  _DstSize = lVar1 * 4;
  if (lVar1 != 0) {
    memmove_s(param_4,_DstSize,param_2,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_4);
}


// ==== FUN_14002b150 @ 14002b150  void * FUN_14002b150(undefined8 param_1, void * param_2, longlong param_3, void * param_4)

void * FUN_14002b150(undefined8 param_1,void *param_2,longlong param_3,void *param_4)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_3 - (longlong)param_2 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_4,_DstSize,param_2,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_4);
}


// ==== FUN_14002b190 @ 14002b190  undefined8 * FUN_14002b190(undefined8 * param_1)

undefined8 * FUN_14002b190(undefined8 *param_1)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  puVar2 = (undefined8 *)0x0;
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_1;
    puVar2 = puVar1;
  }
  *param_1 = puVar2;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_14002b1f0 @ 14002b1f0  undefined FUN_14002b1f0(undefined8 * param_1)

void FUN_14002b1f0(undefined8 *param_1)

{
  FUN_140028bf0((longlong)param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14002b220 @ 14002b220  undefined FUN_14002b220(longlong param_1)

void FUN_14002b220(longlong param_1)

{
  if (*(void **)(param_1 + 0x20) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x20));
  }
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x30) = 0;
  operator_delete(*(void **)(param_1 + 8));
  return;
}


// ==== FUN_14002b270 @ 14002b270  uint FUN_14002b270(uint * param_1)

uint FUN_14002b270(uint *param_1)

{
  uint uVar1;
  
  if (*(longlong *)(param_1 + 0x18) != 0) {
    uVar1 = FUN_14002a690((longlong *)(param_1 + 10));
    return uVar1;
  }
  if (*param_1 < 499999) {
    uVar1 = *param_1 + 1;
    *param_1 = uVar1;
    return uVar1;
  }
  *param_1 = 0x61a81;
  log_InlineLogERROR(&DAT_1400c3fd0);
  return *param_1;
}


// ==== FUN_14002b2d0 @ 14002b2d0  int FUN_14002b2d0(longlong param_1)

int FUN_14002b2d0(longlong param_1)

{
  int iVar1;
  
  if (*(longlong *)(param_1 + 0xa0) != 0) {
    iVar1 = FUN_14002a690((longlong *)(param_1 + 0x68));
    return iVar1;
  }
  if (*(uint *)(param_1 + 4) < 0x5f767a0) {
    iVar1 = *(uint *)(param_1 + 4) + 1;
    *(int *)(param_1 + 4) = iVar1;
    return iVar1;
  }
  *(undefined4 *)(param_1 + 4) = 0x5f5e101;
  log_InlineLogERROR(&DAT_1400c4010);
  return *(int *)(param_1 + 4);
}


// ==== FUN_14002b330 @ 14002b330  undefined FUN_14002b330(longlong param_1)

void FUN_14002b330(longlong param_1)

{
  if (*(void **)(param_1 + 0x20) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x20));
  }
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x30) = 0;
  operator_delete(*(void **)(param_1 + 8));
  return;
}


// ==== FUN_14002b380 @ 14002b380  undefined FUN_14002b380(longlong param_1)

void FUN_14002b380(longlong param_1)

{
  char cVar1;
  ulonglong uVar2;
  longlong *plVar3;
  bool bVar4;
  int iVar5;
  ulonglong uVar6;
  longlong *plVar7;
  int iVar8;
  ulonglong local_res18 [2];
  longlong local_68;
  longlong *plStack_60;
  longlong local_58;
  longlong *plStack_50;
  CTickAnalyst local_48 [24];
  CTickAnalyst local_30 [24];
  
  local_res18[0] = 0;
  iVar8 = DAT_1401028c0;
  while( true ) {
    uVar2 = local_res18[0];
    plVar7 = *(longlong **)(param_1 + 0x10);
    if (plVar7 == (longlong *)0x0) {
      log_InlineLogERROR(&DAT_1400be0b0,"CHECKF","m_pNpcGenSet",
                         "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\npcmanager.cpp",
                         0x1a1);
      plVar7 = (longlong *)0x0;
    }
    uVar6 = (**(code **)(*plVar7 + 0x10))();
    if ((uVar6 <= uVar2) || (iVar8 < 1)) break;
    plVar7 = (longlong *)FUN_140025b50(param_1);
    plVar7 = (longlong *)
             (**(code **)(*plVar7 + 0x18))
                       (plVar7,uVar2,
                        "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\npcmanager.cpp",
                        0x16a);
    if (plVar7 == (longlong *)0x0) {
      log_InlineLogERROR(&DAT_1400be0b0,"MYASSERT","pNpcGenerator",
                         "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\npcmanager.cpp",
                         0x16b);
    }
    CTickAnalyst::CTickAnalyst(local_48,0x52);
    iVar5 = (**(code **)(*plVar7 + 0x80))(plVar7,iVar8);
    iVar8 = iVar8 - iVar5;
    CTickAnalyst::~CTickAnalyst(local_48);
    local_res18[0] = uVar2 + 1;
  }
  DAT_1401045cc = DAT_1401045cc + 1;
  if (2 < DAT_1401045cc) {
    DAT_1401045cc = 0;
    plVar7 = *(longlong **)(param_1 + 8);
    if (plVar7 == (longlong *)0x0) {
      log_InlineLogERROR(&DAT_1400be0b0,"CHECKF","m_pNpcSet",
                         "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\npcmanager.cpp",
                         0x1d4);
      plVar7 = (longlong *)0x0;
    }
    (**(code **)(*plVar7 + 0x10))(plVar7,&local_68);
    while( true ) {
      plVar7 = *(longlong **)(param_1 + 8);
      if (plVar7 == (longlong *)0x0) {
        log_InlineLogERROR(&DAT_1400be0b0,"CHECKF","m_pNpcSet",
                           "f:\\version\\cqserver-78.0.11-1204\\npcserver\\npckernel\\npcmanager.cpp"
                           ,0x1d4);
        plVar7 = (longlong *)0x0;
      }
      plVar7 = (longlong *)(**(code **)(*plVar7 + 0x18))(plVar7,local_48);
      if ((local_68 == 0) || (local_68 != *plVar7)) {
        _invalid_parameter_noinfo();
      }
      if (plStack_60 == (longlong *)plVar7[1]) break;
      local_58 = local_68;
      plStack_50 = plStack_60;
      plVar7 = (longlong *)FUN_140025c40(param_1);
      plVar7 = (longlong *)(**(code **)(*plVar7 + 0x20))(plVar7,&local_58);
      if ((plVar7 != (longlong *)0x0) &&
         ((bVar4 = FUN_140028820(local_res18,plVar7), !bVar4 ||
          (bVar4 = FUN_140057cf0(local_res18[0]), !bVar4)))) {
        CTickAnalyst::CTickAnalyst(local_30,0x54);
        (**(code **)(*plVar7 + 0xe0))(plVar7);
        CTickAnalyst::~CTickAnalyst(local_30);
      }
      if (local_68 == 0) {
        _invalid_parameter_noinfo();
      }
      if (*(char *)((longlong)plStack_60 + 0x29) == '\0') {
        plVar7 = (longlong *)plStack_60[2];
        if (*(char *)((longlong)plVar7 + 0x29) == '\0') {
          cVar1 = *(char *)(*plVar7 + 0x29);
          plStack_60 = plVar7;
          plVar7 = (longlong *)*plVar7;
          while (cVar1 == '\0') {
            cVar1 = *(char *)(*plVar7 + 0x29);
            plStack_60 = plVar7;
            plVar7 = (longlong *)*plVar7;
          }
        }
        else {
          cVar1 = *(char *)(plStack_60[1] + 0x29);
          plVar3 = (longlong *)plStack_60[1];
          plVar7 = plStack_60;
          while ((plStack_60 = plVar3, cVar1 == '\0' && (plVar7 == (longlong *)plStack_60[2]))) {
            cVar1 = *(char *)(plStack_60[1] + 0x29);
            plVar3 = (longlong *)plStack_60[1];
            plVar7 = plStack_60;
          }
        }
      }
      else {
        _invalid_parameter_noinfo();
      }
    }
  }
  return;
}


// ==== FUN_14002b6a0 @ 14002b6a0  int FUN_14002b6a0(longlong param_1)

int FUN_14002b6a0(longlong param_1)

{
  char cVar1;
  longlong *plVar2;
  bool bVar3;
  longlong *plVar4;
  longlong lVar5;
  int iVar6;
  longlong local_res8;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined8 uStack_30;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined1 local_18 [16];
  
  plVar4 = *(longlong **)(param_1 + 8);
  iVar6 = 0;
  if (plVar4 == (longlong *)0x0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    plVar4 = (longlong *)0x0;
  }
  (**(code **)(*plVar4 + 0x10))(plVar4,&local_38);
  while( true ) {
    plVar4 = *(longlong **)(param_1 + 8);
    if (plVar4 == (longlong *)0x0) {
      log_InlineLogERROR(&DAT_1400be0b0);
      plVar4 = (longlong *)0x0;
    }
    plVar4 = (longlong *)(**(code **)(*plVar4 + 0x18))(plVar4,local_18);
    if ((CONCAT44(uStack_34,local_38) == 0) || (CONCAT44(uStack_34,local_38) != *plVar4)) {
      _invalid_parameter_noinfo();
    }
    if (uStack_30 == (longlong *)plVar4[1]) break;
    plVar4 = *(longlong **)(param_1 + 8);
    local_28 = local_38;
    uStack_24 = uStack_34;
    uStack_20 = (undefined4)uStack_30;
    uStack_1c = uStack_30._4_4_;
    if (plVar4 == (longlong *)0x0) {
      log_InlineLogERROR(&DAT_1400be0b0);
      plVar4 = (longlong *)0x0;
    }
    plVar4 = (longlong *)(**(code **)(*plVar4 + 0x20))(plVar4,&local_28);
    if ((plVar4 != (longlong *)0x0) &&
       ((lVar5 = (**(code **)(*plVar4 + 0xb0))(plVar4,0x1040,&local_res8), lVar5 == 0 ||
        (bVar3 = FUN_140057cf0(local_res8), !bVar3)))) {
      iVar6 = iVar6 + 1;
    }
    if (CONCAT44(uStack_34,local_38) == 0) {
      _invalid_parameter_noinfo();
    }
    if (*(char *)((longlong)uStack_30 + 0x29) == '\0') {
      plVar4 = (longlong *)uStack_30[2];
      if (*(char *)((longlong)plVar4 + 0x29) == '\0') {
        cVar1 = *(char *)(*plVar4 + 0x29);
        uStack_30 = plVar4;
        plVar4 = (longlong *)*plVar4;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar4 + 0x29);
          uStack_30 = plVar4;
          plVar4 = (longlong *)*plVar4;
        }
      }
      else {
        cVar1 = *(char *)(uStack_30[1] + 0x29);
        plVar2 = (longlong *)uStack_30[1];
        plVar4 = uStack_30;
        while ((uStack_30 = plVar2, cVar1 == '\0' && (plVar4 == (longlong *)uStack_30[2]))) {
          cVar1 = *(char *)(uStack_30[1] + 0x29);
          plVar2 = (longlong *)uStack_30[1];
          plVar4 = uStack_30;
        }
      }
    }
    else {
      _invalid_parameter_noinfo();
    }
  }
  return iVar6;
}


// ==== FUN_14002b870 @ 14002b870  longlong * FUN_14002b870(longlong * param_1, longlong * param_2, uint * param_3)

longlong * FUN_14002b870(longlong *param_1,longlong *param_2,uint *param_3)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong local_28;
  undefined8 *local_20;
  longlong local_18;
  longlong local_10;
  
  puVar4 = (undefined8 *)param_1[6];
  if (*(char *)((longlong)puVar4[1] + 0x51) == '\0') {
    puVar1 = (undefined8 *)puVar4[1];
    do {
      if (*(uint *)(puVar1 + 3) < *param_3) {
        puVar2 = (undefined8 *)puVar1[2];
      }
      else {
        puVar2 = (undefined8 *)*puVar1;
        puVar4 = puVar1;
      }
      puVar1 = puVar2;
    } while (*(char *)((longlong)puVar2 + 0x51) == '\0');
  }
  puVar1 = (undefined8 *)param_1[6];
  local_20 = puVar4;
  local_28 = *param_1;
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  if ((puVar4 == puVar1) || (*param_3 < *(uint *)(puVar4 + 3))) {
    plVar3 = &local_18;
    local_10 = param_1[6];
    local_18 = *param_1;
  }
  else {
    plVar3 = &local_28;
  }
  *param_2 = *plVar3;
  param_2[1] = plVar3[1];
  return param_2;
}


// ==== FUN_14002b940 @ 14002b940  longlong * FUN_14002b940(longlong * param_1, longlong * param_2, uint * param_3)

longlong * FUN_14002b940(longlong *param_1,longlong *param_2,uint *param_3)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong local_28;
  undefined8 *local_20;
  longlong local_18;
  longlong local_10;
  
  puVar4 = (undefined8 *)param_1[6];
  if (*(char *)((longlong)puVar4[1] + 0x51) == '\0') {
    puVar1 = (undefined8 *)puVar4[1];
    do {
      if (*(uint *)(puVar1 + 3) < *param_3) {
        puVar2 = (undefined8 *)puVar1[2];
      }
      else {
        puVar2 = (undefined8 *)*puVar1;
        puVar4 = puVar1;
      }
      puVar1 = puVar2;
    } while (*(char *)((longlong)puVar2 + 0x51) == '\0');
  }
  puVar1 = (undefined8 *)param_1[6];
  local_20 = puVar4;
  local_28 = *param_1;
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  if ((puVar4 == puVar1) || (*param_3 < *(uint *)(puVar4 + 3))) {
    plVar3 = &local_18;
    local_10 = param_1[6];
    local_18 = *param_1;
  }
  else {
    plVar3 = &local_28;
  }
  *param_2 = *plVar3;
  param_2[1] = plVar3[1];
  return param_2;
}


// ==== FUN_14002ba10 @ 14002ba10  undefined FUN_14002ba10(undefined8 * param_1)

void FUN_14002ba10(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14002ba30 @ 14002ba30  undefined FUN_14002ba30(undefined8 * param_1)

void FUN_14002ba30(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14002ba50 @ 14002ba50  undefined8 * FUN_14002ba50(undefined8 * param_1, undefined1 param_2)

undefined8 * FUN_14002ba50(undefined8 *param_1,undefined1 param_2)

{
  longlong *plVar1;
  longlong *plVar2;
  
  *param_1 = IGameObjSet<class_IGenerator>::vftable;
  *param_1 = CGameObjSet<class_IGenerator>::vftable;
  plVar1 = (longlong *)operator_new(8);
  plVar2 = (longlong *)0x0;
  if (plVar1 != (longlong *)0x0) {
    *plVar1 = (longlong)(param_1 + 1);
    plVar2 = plVar1;
  }
  param_1[1] = plVar2;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  *(undefined1 *)(param_1 + 7) = param_2;
  return param_1;
}


// ==== FUN_14002bb00 @ 14002bb00  longlong FUN_14002bb00(longlong param_1, ulonglong param_2)

longlong FUN_14002bb00(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)(*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18) >> 3) <= param_2) {
    _invalid_parameter_noinfo();
  }
  return *(longlong *)(param_1 + 0x18) + param_2 * 8;
}


// ==== FUN_14002bc00 @ 14002bc00  longlong * FUN_14002bc00(longlong * param_1, longlong param_2)

longlong * FUN_14002bc00(longlong *param_1,longlong param_2)

{
  longlong *plVar1;
  ulonglong uVar2;
  longlong lVar3;
  longlong lVar4;
  
  plVar1 = (longlong *)*param_1;
  lVar3 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar1 = (longlong *)*param_1;
    lVar4 = lVar3;
    if (plVar1 != (longlong *)0x0) goto LAB_14002bc30;
  }
  else {
LAB_14002bc30:
    lVar4 = *plVar1;
  }
  uVar2 = param_1[1] + param_2 * 8;
  if (uVar2 <= *(ulonglong *)(lVar4 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar2) goto LAB_14002bc58;
  }
  _invalid_parameter_noinfo();
LAB_14002bc58:
  param_1[1] = param_1[1] + param_2 * 8;
  return param_1;
}


// ==== FUN_14002bc70 @ 14002bc70  longlong FUN_14002bc70(longlong * param_1, longlong * param_2)

longlong FUN_14002bc70(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] - param_2[1] >> 3;
}


// ==== FUN_14002bcc0 @ 14002bcc0  bool FUN_14002bcc0(longlong * param_1, longlong * param_2)

bool FUN_14002bcc0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_14002bd10 @ 14002bd10  void * FUN_14002bd10(void * param_1, longlong param_2, void * param_3)

void * FUN_14002bd10(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (0 < lVar1) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14002bda0 @ 14002bda0  void * FUN_14002bda0(void * param_1, longlong param_2, longlong param_3)

void * FUN_14002bda0(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _Dst = (void *)(param_3 + lVar1 * -8);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 8,param_1,lVar1 * 8);
  }
  return _Dst;
}


// ==== FUN_14002be20 @ 14002be20  void * FUN_14002be20(void * param_1, longlong param_2, void * param_3)

void * FUN_14002be20(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14002bf20 @ 14002bf20  longlong * FUN_14002bf20(longlong * param_1, longlong param_2)

longlong * FUN_14002bf20(longlong *param_1,longlong param_2)

{
  FUN_14002bc00(param_1,param_2);
  return param_1;
}


// ==== FUN_14002bf50 @ 14002bf50  bool FUN_14002bf50(longlong * param_1, longlong * param_2)

bool FUN_14002bf50(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_14002bfa0 @ 14002bfa0  void * FUN_14002bfa0(void * param_1, longlong param_2, longlong param_3)

void * FUN_14002bfa0(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _Dst = (void *)(param_3 + lVar1 * -8);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 8,param_1,lVar1 * 8);
  }
  return _Dst;
}


// ==== FUN_14002c010 @ 14002c010  void * FUN_14002c010(void * param_1, longlong param_2, void * param_3)

void * FUN_14002c010(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14002c050 @ 14002c050  longlong * FUN_14002c050(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_14002c050(longlong *param_1,longlong *param_2,longlong param_3)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  
  plVar2 = (longlong *)*param_1;
  lVar3 = param_1[1];
  lVar4 = 0;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar4;
  }
  else {
    lVar5 = *plVar2;
  }
  uVar1 = lVar3 + param_3 * 8;
  if (uVar1 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar2 != (longlong *)0x0) {
      lVar4 = *plVar2;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar1) goto LAB_14002c0ba;
  }
  _invalid_parameter_noinfo();
LAB_14002c0ba:
  *param_2 = (longlong)plVar2;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_14002c0f0 @ 14002c0f0  undefined8 * FUN_14002c0f0(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_14002c0f0(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_14002c150 @ 14002c150  void * FUN_14002c150(void * param_1, longlong param_2, void * param_3)

void * FUN_14002c150(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (0 < lVar1) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14002c1c0 @ 14002c1c0  void * FUN_14002c1c0(void * param_1, longlong param_2, longlong param_3)

void * FUN_14002c1c0(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _Dst = (void *)(param_3 + lVar1 * -8);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 8,param_1,lVar1 * 8);
  }
  return _Dst;
}


// ==== FUN_14002c230 @ 14002c230  void * FUN_14002c230(void * param_1, longlong param_2, void * param_3)

void * FUN_14002c230(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14002c270 @ 14002c270  undefined8 * FUN_14002c270(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_14002c270(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_14002c300 @ 14002c300  void * FUN_14002c300(void * param_1, longlong param_2, void * param_3)

void * FUN_14002c300(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14002c340 @ 14002c340  undefined8 * FUN_14002c340(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14002c340(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[3];
  *param_2 = 0;
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14002c390 @ 14002c390  undefined8 * FUN_14002c390(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14002c390(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[4];
  *param_2 = 0;
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14002c3e0 @ 14002c3e0  undefined8 * FUN_14002c3e0(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14002c3e0(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (undefined8 *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14002c470 @ 14002c470  void * FUN_14002c470(undefined8 param_1, void * param_2, longlong param_3, void * param_4)

void * FUN_14002c470(undefined8 param_1,void *param_2,longlong param_3,void *param_4)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_3 - (longlong)param_2 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_4,_DstSize,param_2,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_4);
}


// ==== FUN_14002c4b0 @ 14002c4b0  longlong * FUN_14002c4b0(longlong * param_1, longlong * param_2, longlong param_3, longlong param_4)

longlong * FUN_14002c4b0(longlong *param_1,longlong *param_2,longlong param_3,longlong param_4)

{
  rsize_t _DstSize;
  ulonglong uVar1;
  void *_Src;
  void *_Dst;
  longlong lVar2;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (longlong *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  lVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = lVar2;
  _Src = *(void **)(param_4 + 8);
  if ((_Src < (void *)param_1[3]) || ((void *)param_1[4] < _Src)) {
    _invalid_parameter_noinfo();
  }
  if ((*param_2 == 0) || (*param_2 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  _Dst = (void *)param_2[1];
  if (_Dst != _Src) {
    lVar2 = param_1[4] - (longlong)_Src >> 3;
    _DstSize = lVar2 * 8;
    if (0 < lVar2) {
      memmove_s(_Dst,_DstSize,_Src,_DstSize);
    }
    param_1[4] = (longlong)(_DstSize + (longlong)_Dst);
  }
  return param_2;
}


// ==== FUN_14002c5a0 @ 14002c5a0  undefined8 * FUN_14002c5a0(undefined8 * param_1, undefined1 param_2)

undefined8 * FUN_14002c5a0(undefined8 *param_1,undefined1 param_2)

{
  longlong *plVar1;
  longlong *plVar2;
  
  *param_1 = IGameObjSet<class_CNpcType>::vftable;
  *param_1 = CGameObjSet<class_CNpcType>::vftable;
  plVar1 = (longlong *)operator_new(8);
  plVar2 = (longlong *)0x0;
  if (plVar1 != (longlong *)0x0) {
    *plVar1 = (longlong)(param_1 + 1);
    plVar2 = plVar1;
  }
  param_1[1] = plVar2;
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  *(undefined1 *)(param_1 + 7) = param_2;
  return param_1;
}


// ==== FUN_14002c650 @ 14002c650  longlong FUN_14002c650(longlong param_1, ulonglong param_2)

longlong FUN_14002c650(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)(*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18) >> 3) <= param_2) {
    _invalid_parameter_noinfo();
  }
  return *(longlong *)(param_1 + 0x18) + param_2 * 8;
}


// ==== FUN_14002c750 @ 14002c750  longlong * FUN_14002c750(longlong * param_1, longlong param_2)

longlong * FUN_14002c750(longlong *param_1,longlong param_2)

{
  longlong *plVar1;
  ulonglong uVar2;
  longlong lVar3;
  longlong lVar4;
  
  plVar1 = (longlong *)*param_1;
  lVar3 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar1 = (longlong *)*param_1;
    lVar4 = lVar3;
    if (plVar1 != (longlong *)0x0) goto LAB_14002c780;
  }
  else {
LAB_14002c780:
    lVar4 = *plVar1;
  }
  uVar2 = param_1[1] + param_2 * 8;
  if (uVar2 <= *(ulonglong *)(lVar4 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar2) goto LAB_14002c7a8;
  }
  _invalid_parameter_noinfo();
LAB_14002c7a8:
  param_1[1] = param_1[1] + param_2 * 8;
  return param_1;
}


// ==== FUN_14002c7c0 @ 14002c7c0  longlong FUN_14002c7c0(longlong * param_1, longlong * param_2)

longlong FUN_14002c7c0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] - param_2[1] >> 3;
}


// ==== FUN_14002c810 @ 14002c810  bool FUN_14002c810(longlong * param_1, longlong * param_2)

bool FUN_14002c810(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_14002c860 @ 14002c860  void * FUN_14002c860(void * param_1, longlong param_2, void * param_3)

void * FUN_14002c860(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (0 < lVar1) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14002c8f0 @ 14002c8f0  void * FUN_14002c8f0(void * param_1, longlong param_2, longlong param_3)

void * FUN_14002c8f0(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _Dst = (void *)(param_3 + lVar1 * -8);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 8,param_1,lVar1 * 8);
  }
  return _Dst;
}


// ==== FUN_14002c970 @ 14002c970  void * FUN_14002c970(void * param_1, longlong param_2, void * param_3)

void * FUN_14002c970(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14002ca70 @ 14002ca70  longlong * FUN_14002ca70(longlong * param_1, longlong param_2)

longlong * FUN_14002ca70(longlong *param_1,longlong param_2)

{
  FUN_14002c750(param_1,param_2);
  return param_1;
}


// ==== FUN_14002caa0 @ 14002caa0  bool FUN_14002caa0(longlong * param_1, longlong * param_2)

bool FUN_14002caa0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_14002caf0 @ 14002caf0  void * FUN_14002caf0(void * param_1, longlong param_2, longlong param_3)

void * FUN_14002caf0(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _Dst = (void *)(param_3 + lVar1 * -8);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 8,param_1,lVar1 * 8);
  }
  return _Dst;
}


// ==== FUN_14002cb60 @ 14002cb60  void * FUN_14002cb60(void * param_1, longlong param_2, void * param_3)

void * FUN_14002cb60(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14002cba0 @ 14002cba0  longlong * FUN_14002cba0(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_14002cba0(longlong *param_1,longlong *param_2,longlong param_3)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  
  plVar2 = (longlong *)*param_1;
  lVar3 = param_1[1];
  lVar4 = 0;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar4;
  }
  else {
    lVar5 = *plVar2;
  }
  uVar1 = lVar3 + param_3 * 8;
  if (uVar1 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar2 != (longlong *)0x0) {
      lVar4 = *plVar2;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar1) goto LAB_14002cc0a;
  }
  _invalid_parameter_noinfo();
LAB_14002cc0a:
  *param_2 = (longlong)plVar2;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_14002cc40 @ 14002cc40  undefined8 * FUN_14002cc40(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_14002cc40(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_14002cca0 @ 14002cca0  void * FUN_14002cca0(void * param_1, longlong param_2, void * param_3)

void * FUN_14002cca0(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (0 < lVar1) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14002cd10 @ 14002cd10  void * FUN_14002cd10(void * param_1, longlong param_2, longlong param_3)

void * FUN_14002cd10(void *param_1,longlong param_2,longlong param_3)

{
  longlong lVar1;
  void *_Dst;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _Dst = (void *)(param_3 + lVar1 * -8);
  if (0 < lVar1) {
    memmove_s(_Dst,lVar1 * 8,param_1,lVar1 * 8);
  }
  return _Dst;
}


// ==== FUN_14002cd80 @ 14002cd80  void * FUN_14002cd80(void * param_1, longlong param_2, void * param_3)

void * FUN_14002cd80(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14002cdc0 @ 14002cdc0  undefined8 * FUN_14002cdc0(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_14002cdc0(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  *param_1 = 0;
  if (((param_3 == (undefined8 *)0x0) || (param_2 < (ulonglong)param_3[3])) ||
     ((ulonglong)param_3[4] < param_2)) {
    _invalid_parameter_noinfo();
  }
  uVar1 = *param_3;
  param_1[1] = param_2;
  *param_1 = uVar1;
  return param_1;
}


// ==== FUN_14002ce50 @ 14002ce50  void * FUN_14002ce50(void * param_1, longlong param_2, void * param_3)

void * FUN_14002ce50(void *param_1,longlong param_2,void *param_3)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_2 - (longlong)param_1 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_3,_DstSize,param_1,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_3);
}


// ==== FUN_14002ce90 @ 14002ce90  undefined8 * FUN_14002ce90(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14002ce90(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[3];
  *param_2 = 0;
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14002cee0 @ 14002cee0  undefined8 * FUN_14002cee0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14002cee0(undefined8 *param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = param_1[4];
  *param_2 = 0;
  if (uVar1 < (ulonglong)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14002cf30 @ 14002cf30  undefined8 * FUN_14002cf30(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14002cf30(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  ulonglong uVar1;
  undefined8 uVar2;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (undefined8 *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14002cfc0 @ 14002cfc0  void * FUN_14002cfc0(undefined8 param_1, void * param_2, longlong param_3, void * param_4)

void * FUN_14002cfc0(undefined8 param_1,void *param_2,longlong param_3,void *param_4)

{
  rsize_t _DstSize;
  longlong lVar1;
  
  lVar1 = param_3 - (longlong)param_2 >> 3;
  _DstSize = lVar1 * 8;
  if (lVar1 != 0) {
    memmove_s(param_4,_DstSize,param_2,_DstSize);
  }
  return (void *)(_DstSize + (longlong)param_4);
}


// ==== FUN_14002d000 @ 14002d000  longlong * FUN_14002d000(longlong * param_1, longlong * param_2, longlong param_3, longlong param_4)

longlong * FUN_14002d000(longlong *param_1,longlong *param_2,longlong param_3,longlong param_4)

{
  rsize_t _DstSize;
  ulonglong uVar1;
  void *_Src;
  void *_Dst;
  longlong lVar2;
  
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if (((param_1 == (longlong *)0x0) || (uVar1 < (ulonglong)param_1[3])) ||
     ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  lVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = lVar2;
  _Src = *(void **)(param_4 + 8);
  if ((_Src < (void *)param_1[3]) || ((void *)param_1[4] < _Src)) {
    _invalid_parameter_noinfo();
  }
  if ((*param_2 == 0) || (*param_2 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  _Dst = (void *)param_2[1];
  if (_Dst != _Src) {
    lVar2 = param_1[4] - (longlong)_Src >> 3;
    _DstSize = lVar2 * 8;
    if (0 < lVar2) {
      memmove_s(_Dst,_DstSize,_Src,_DstSize);
    }
    param_1[4] = (longlong)(_DstSize + (longlong)_Dst);
  }
  return param_2;
}


// ==== FUN_14002d0f0 @ 14002d0f0  undefined8 * FUN_14002d0f0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14002d0f0(undefined8 *param_1,undefined8 *param_2)

{
  code *pcVar1;
  undefined8 *puVar2;
  longlong lVar3;
  void *pvVar4;
  ulonglong uVar5;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined8 local_28;
  ulonglong uStack_20;
  
  puVar2 = (undefined8 *)operator_new(8);
  if (puVar2 == (undefined8 *)0x0) {
    puVar2 = (undefined8 *)0x0;
  }
  else {
    *puVar2 = param_1;
  }
  *param_1 = puVar2;
  uVar5 = (longlong)(param_2[4] - param_2[3]) >> 2;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  if (uVar5 != 0) {
    if (0x3fffffffffffffff < uVar5) {
      FUN_1400269c0();
      pcVar1 = (code *)swi(3);
      puVar2 = (undefined8 *)(*pcVar1)();
      return puVar2;
    }
    lVar3 = FUN_140027df0(param_1 + 2,uVar5);
    param_1[3] = lVar3;
    param_1[4] = lVar3;
    param_1[5] = lVar3 + uVar5 * 4;
    uVar5 = param_2[4];
    if (uVar5 < (ulonglong)param_2[3]) {
      _invalid_parameter_noinfo();
    }
    local_58 = (undefined4)*param_2;
    uStack_54 = (undefined4)((ulonglong)*param_2 >> 0x20);
    uStack_50 = (undefined4)uVar5;
    uStack_4c = (undefined4)(uVar5 >> 0x20);
    local_38 = local_58;
    uStack_34 = uStack_54;
    uStack_30 = uStack_50;
    uStack_2c = uStack_4c;
    uVar5 = param_2[3];
    if ((ulonglong)param_2[4] < uVar5) {
      _invalid_parameter_noinfo();
    }
    local_28 = *param_2;
    uStack_20 = uVar5;
    pvVar4 = FUN_14002afd0(param_1,(longlong)&local_28,(longlong)&local_38,(void *)param_1[3]);
    param_1[4] = pvVar4;
  }
  return param_1;
}


// ==== FUN_14002d250 @ 14002d250  undefined8 * FUN_14002d250(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_14002d250(undefined8 *param_1,undefined8 *param_2)

{
  code *pcVar1;
  undefined8 *puVar2;
  longlong lVar3;
  void *pvVar4;
  ulonglong uVar5;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined8 local_28;
  ulonglong uStack_20;
  
  puVar2 = (undefined8 *)operator_new(8);
  if (puVar2 == (undefined8 *)0x0) {
    puVar2 = (undefined8 *)0x0;
  }
  else {
    *puVar2 = param_1;
  }
  *param_1 = puVar2;
  uVar5 = (longlong)(param_2[4] - param_2[3]) >> 3;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  if (uVar5 != 0) {
    if (0x1fffffffffffffff < uVar5) {
      FUN_140026a70();
      pcVar1 = (code *)swi(3);
      puVar2 = (undefined8 *)(*pcVar1)();
      return puVar2;
    }
    lVar3 = FUN_1400280e0(param_1 + 2,uVar5);
    param_1[3] = lVar3;
    param_1[4] = lVar3;
    param_1[5] = lVar3 + uVar5 * 8;
    uVar5 = param_2[4];
    if (uVar5 < (ulonglong)param_2[3]) {
      _invalid_parameter_noinfo();
    }
    local_58 = (undefined4)*param_2;
    uStack_54 = (undefined4)((ulonglong)*param_2 >> 0x20);
    uStack_50 = (undefined4)uVar5;
    uStack_4c = (undefined4)(uVar5 >> 0x20);
    local_38 = local_58;
    uStack_34 = uStack_54;
    uStack_30 = uStack_50;
    uStack_2c = uStack_4c;
    uVar5 = param_2[3];
    if ((ulonglong)param_2[4] < uVar5) {
      _invalid_parameter_noinfo();
    }
    local_28 = *param_2;
    uStack_20 = uVar5;
    pvVar4 = FUN_14002b070(param_1,(longlong)&local_28,(longlong)&local_38,(void *)param_1[3]);
    param_1[4] = pvVar4;
  }
  return param_1;
}


// ==== FUN_14002d3b0 @ 14002d3b0  undefined8 * FUN_14002d3b0(undefined8 * param_1)

undefined8 * FUN_14002d3b0(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_14002d400 @ 14002d400  undefined8 * FUN_14002d400(undefined8 * param_1)

undefined8 * FUN_14002d400(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_14002d450 @ 14002d450  undefined FUN_14002d450(longlong param_1, longlong param_2, ulonglong param_3, undefined4 * param_4)

void FUN_14002d450(longlong param_1,longlong param_2,ulonglong param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  code *pcVar2;
  void *pvVar3;
  longlong lVar4;
  ulonglong uVar5;
  undefined4 *puVar6;
  longlong lVar7;
  rsize_t rVar8;
  ulonglong uVar9;
  void *pvVar10;
  ulonglong uVar11;
  undefined4 *puVar12;
  
  lVar4 = *(longlong *)(param_1 + 0x18);
  if (lVar4 == 0) {
    uVar5 = 0;
  }
  else {
    uVar5 = *(longlong *)(param_1 + 0x28) - lVar4 >> 2;
  }
  uVar9 = 0;
  if (param_3 != 0) {
    lVar7 = *(longlong *)(param_1 + 0x20);
    lVar4 = lVar7 - lVar4 >> 2;
    if (0x3fffffffffffffffU - lVar4 < param_3) {
      FUN_1400269c0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    uVar11 = param_3 + lVar4;
    if (uVar5 < uVar11) {
      if (uVar5 <= 0x3fffffffffffffff - (uVar5 >> 1)) {
        uVar9 = uVar5 + (uVar5 >> 1);
      }
      if (uVar9 < uVar11) {
        uVar9 = uVar11;
      }
      pvVar3 = (void *)FUN_140027df0(param_1 + 0x10,uVar9);
      lVar4 = *(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18) >> 2;
      puVar6 = (undefined4 *)((longlong)pvVar3 + lVar4 * 4);
      for (uVar5 = param_3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *puVar6 = *param_4;
        puVar6 = puVar6 + 1;
      }
      lVar7 = *(longlong *)(param_2 + 8) - (longlong)*(void **)(param_1 + 0x18) >> 2;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 2;
        memmove_s(pvVar3,rVar8,*(void **)(param_1 + 0x18),rVar8);
      }
      lVar7 = *(longlong *)(param_1 + 0x20) - (longlong)*(void **)(param_2 + 8) >> 2;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 2;
        memmove_s((void *)((longlong)pvVar3 + (lVar4 + param_3) * 4),rVar8,*(void **)(param_2 + 8),
                  rVar8);
      }
      pvVar10 = *(void **)(param_1 + 0x18);
      lVar4 = *(longlong *)(param_1 + 0x20);
      if (pvVar10 != (void *)0x0) {
        operator_delete(pvVar10);
      }
      *(void **)(param_1 + 0x28) = (void *)((longlong)pvVar3 + uVar9 * 4);
      *(void **)(param_1 + 0x20) =
           (void *)((longlong)pvVar3 + (param_3 + (lVar4 - (longlong)pvVar10 >> 2)) * 4);
      *(void **)(param_1 + 0x18) = pvVar3;
    }
    else if ((ulonglong)(lVar7 - *(longlong *)(param_2 + 8) >> 2) < param_3) {
      uVar1 = *param_4;
      FUN_14002b110(param_1,*(void **)(param_2 + 8),lVar7,
                    (void *)((longlong)*(void **)(param_2 + 8) + param_3 * 4));
      puVar6 = *(undefined4 **)(param_1 + 0x20);
      for (lVar4 = param_3 - ((longlong)puVar6 - *(longlong *)(param_2 + 8) >> 2); lVar4 != 0;
          lVar4 = lVar4 + -1) {
        *puVar6 = uVar1;
        puVar6 = puVar6 + 1;
      }
      *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + param_3 * 4;
      lVar4 = *(longlong *)(param_1 + 0x20);
      for (puVar6 = *(undefined4 **)(param_2 + 8); puVar6 != (undefined4 *)(lVar4 + param_3 * -4);
          puVar6 = puVar6 + 1) {
        *puVar6 = uVar1;
      }
    }
    else {
      uVar1 = *param_4;
      pvVar10 = (void *)(lVar7 + param_3 * -4);
      pvVar3 = FUN_14002b110(param_1,pvVar10,lVar7,(void *)lVar7);
      *(void **)(param_1 + 0x20) = pvVar3;
      FUN_140029a90(*(void **)(param_2 + 8),(longlong)pvVar10,lVar7);
      puVar12 = *(undefined4 **)(param_2 + 8);
      puVar6 = puVar12 + param_3;
      for (; puVar12 != puVar6; puVar12 = puVar12 + 1) {
        *puVar12 = uVar1;
      }
    }
  }
  return;
}


// ==== FUN_14002d6f0 @ 14002d6f0  undefined FUN_14002d6f0(longlong param_1, longlong param_2, ulonglong param_3, undefined8 * param_4)

void FUN_14002d6f0(longlong param_1,longlong param_2,ulonglong param_3,undefined8 *param_4)

{
  undefined8 uVar1;
  code *pcVar2;
  void *pvVar3;
  longlong lVar4;
  ulonglong uVar5;
  undefined8 *puVar6;
  longlong lVar7;
  rsize_t rVar8;
  ulonglong uVar9;
  void *pvVar10;
  ulonglong uVar11;
  undefined8 *puVar12;
  
  lVar4 = *(longlong *)(param_1 + 0x18);
  if (lVar4 == 0) {
    uVar5 = 0;
  }
  else {
    uVar5 = *(longlong *)(param_1 + 0x28) - lVar4 >> 3;
  }
  uVar9 = 0;
  if (param_3 != 0) {
    lVar7 = *(longlong *)(param_1 + 0x20);
    lVar4 = lVar7 - lVar4 >> 3;
    if (0x1fffffffffffffffU - lVar4 < param_3) {
      FUN_140026a70();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    uVar11 = param_3 + lVar4;
    if (uVar5 < uVar11) {
      if (uVar5 <= 0x1fffffffffffffff - (uVar5 >> 1)) {
        uVar9 = uVar5 + (uVar5 >> 1);
      }
      if (uVar9 < uVar11) {
        uVar9 = uVar11;
      }
      pvVar3 = (void *)FUN_1400280e0(param_1 + 0x10,uVar9);
      lVar4 = *(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18) >> 3;
      puVar6 = (undefined8 *)((longlong)pvVar3 + lVar4 * 8);
      for (uVar5 = param_3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *puVar6 = *param_4;
        puVar6 = puVar6 + 1;
      }
      lVar7 = *(longlong *)(param_2 + 8) - (longlong)*(void **)(param_1 + 0x18) >> 3;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 3;
        memmove_s(pvVar3,rVar8,*(void **)(param_1 + 0x18),rVar8);
      }
      lVar7 = *(longlong *)(param_1 + 0x20) - (longlong)*(void **)(param_2 + 8) >> 3;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 3;
        memmove_s((void *)((longlong)pvVar3 + (lVar4 + param_3) * 8),rVar8,*(void **)(param_2 + 8),
                  rVar8);
      }
      pvVar10 = *(void **)(param_1 + 0x18);
      lVar4 = *(longlong *)(param_1 + 0x20);
      if (pvVar10 != (void *)0x0) {
        operator_delete(pvVar10);
      }
      *(void **)(param_1 + 0x28) = (void *)((longlong)pvVar3 + uVar9 * 8);
      *(void **)(param_1 + 0x20) =
           (void *)((longlong)pvVar3 + (param_3 + (lVar4 - (longlong)pvVar10 >> 3)) * 8);
      *(void **)(param_1 + 0x18) = pvVar3;
    }
    else if ((ulonglong)(lVar7 - *(longlong *)(param_2 + 8) >> 3) < param_3) {
      uVar1 = *param_4;
      FUN_14002b150(param_1,*(void **)(param_2 + 8),lVar7,
                    (void *)((longlong)*(void **)(param_2 + 8) + param_3 * 8));
      puVar6 = *(undefined8 **)(param_1 + 0x20);
      for (lVar4 = param_3 - ((longlong)puVar6 - *(longlong *)(param_2 + 8) >> 3); lVar4 != 0;
          lVar4 = lVar4 + -1) {
        *puVar6 = uVar1;
        puVar6 = puVar6 + 1;
      }
      *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + param_3 * 8;
      lVar4 = *(longlong *)(param_1 + 0x20);
      for (puVar6 = *(undefined8 **)(param_2 + 8); puVar6 != (undefined8 *)(lVar4 + param_3 * -8);
          puVar6 = puVar6 + 1) {
        *puVar6 = uVar1;
      }
    }
    else {
      uVar1 = *param_4;
      pvVar10 = (void *)(lVar7 + param_3 * -8);
      pvVar3 = FUN_14002b150(param_1,pvVar10,lVar7,(void *)lVar7);
      *(void **)(param_1 + 0x20) = pvVar3;
      FUN_140029b00(*(void **)(param_2 + 8),(longlong)pvVar10,lVar7);
      puVar12 = *(undefined8 **)(param_2 + 8);
      puVar6 = puVar12 + param_3;
      for (; puVar12 != puVar6; puVar12 = puVar12 + 1) {
        *puVar12 = uVar1;
      }
    }
  }
  return;
}


// ==== FUN_14002d9a0 @ 14002d9a0  undefined FUN_14002d9a0(longlong * param_1)

void FUN_14002d9a0(longlong *param_1)

{
  longlong local_38;
  undefined8 *puStack_30;
  longlong local_28;
  undefined8 uStack_20;
  longlong local_18 [2];
  
  local_38 = *param_1;
  puStack_30 = (undefined8 *)param_1[6];
  uStack_20 = *puStack_30;
  local_28 = local_38;
  FUN_14002add0(param_1,local_18,&local_28,&local_38);
  operator_delete((void *)param_1[6]);
  param_1[6] = 0;
  param_1[7] = 0;
  return;
}


// ==== FUN_14002da10 @ 14002da10  undefined4 * FUN_14002da10(undefined4 * param_1, undefined4 * param_2)

undefined4 * FUN_14002da10(undefined4 *param_1,undefined4 *param_2)

{
  *param_1 = *param_2;
  FUN_14002d250((undefined8 *)(param_1 + 2),(undefined8 *)(param_2 + 2));
  return param_1;
}


// ==== FUN_14002da50 @ 14002da50  undefined4 * FUN_14002da50(undefined4 * param_1, undefined4 * param_2)

undefined4 * FUN_14002da50(undefined4 *param_1,undefined4 *param_2)

{
  *param_1 = *param_2;
  FUN_14002d0f0((undefined8 *)(param_1 + 2),(undefined8 *)(param_2 + 2));
  return param_1;
}


// ==== FUN_14002da90 @ 14002da90  undefined8 * FUN_14002da90(undefined8 * param_1)

undefined8 * FUN_14002da90(undefined8 *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  return param_1;
}


// ==== FUN_14002dae0 @ 14002dae0  undefined FUN_14002dae0(longlong param_1)

void FUN_14002dae0(longlong param_1)

{
  if (*(void **)(param_1 + 0x38) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x38));
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  operator_delete(*(void **)(param_1 + 0x20));
  return;
}


// ==== FUN_14002db30 @ 14002db30  undefined FUN_14002db30(longlong param_1)

void FUN_14002db30(longlong param_1)

{
  if (*(void **)(param_1 + 0x38) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x38));
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  operator_delete(*(void **)(param_1 + 0x20));
  return;
}


// ==== FUN_14002db80 @ 14002db80  undefined8 * FUN_14002db80(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14002db80(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  void *_Src;
  ulonglong uVar1;
  undefined8 uVar2;
  longlong lVar3;
  rsize_t _DstSize;
  
  _Src = (void *)((longlong)*(void **)(param_3 + 8) + 8);
  lVar3 = param_1[4] - (longlong)_Src >> 3;
  if (0 < lVar3) {
    _DstSize = lVar3 << 3;
    memmove_s(*(void **)(param_3 + 8),_DstSize,_Src,_DstSize);
  }
  param_1[4] = param_1[4] + -8;
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if ((uVar1 < (ulonglong)param_1[3]) || ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14002dc10 @ 14002dc10  undefined8 * FUN_14002dc10(undefined8 * param_1, undefined8 * param_2, longlong param_3)

undefined8 * FUN_14002dc10(undefined8 *param_1,undefined8 *param_2,longlong param_3)

{
  void *_Src;
  ulonglong uVar1;
  undefined8 uVar2;
  longlong lVar3;
  rsize_t _DstSize;
  
  _Src = (void *)((longlong)*(void **)(param_3 + 8) + 8);
  lVar3 = param_1[4] - (longlong)_Src >> 3;
  if (0 < lVar3) {
    _DstSize = lVar3 << 3;
    memmove_s(*(void **)(param_3 + 8),_DstSize,_Src,_DstSize);
  }
  param_1[4] = param_1[4] + -8;
  uVar1 = *(ulonglong *)(param_3 + 8);
  *param_2 = 0;
  if ((uVar1 < (ulonglong)param_1[3]) || ((ulonglong)param_1[4] < uVar1)) {
    _invalid_parameter_noinfo();
  }
  uVar2 = *param_1;
  param_2[1] = uVar1;
  *param_2 = uVar2;
  return param_2;
}


// ==== FUN_14002dd00 @ 14002dd00  undefined FUN_14002dd00(longlong param_1, longlong param_2, ulonglong param_3, undefined8 * param_4)

void FUN_14002dd00(longlong param_1,longlong param_2,ulonglong param_3,undefined8 *param_4)

{
  undefined8 uVar1;
  code *pcVar2;
  void *pvVar3;
  longlong lVar4;
  ulonglong uVar5;
  undefined8 *puVar6;
  longlong lVar7;
  rsize_t rVar8;
  ulonglong uVar9;
  void *pvVar10;
  ulonglong uVar11;
  undefined8 *puVar12;
  
  lVar4 = *(longlong *)(param_1 + 0x18);
  if (lVar4 == 0) {
    uVar5 = 0;
  }
  else {
    uVar5 = *(longlong *)(param_1 + 0x28) - lVar4 >> 3;
  }
  uVar9 = 0;
  if (param_3 != 0) {
    lVar7 = *(longlong *)(param_1 + 0x20);
    lVar4 = lVar7 - lVar4 >> 3;
    if (0x1fffffffffffffffU - lVar4 < param_3) {
      FUN_140026ea0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    uVar11 = param_3 + lVar4;
    if (uVar5 < uVar11) {
      if (uVar5 <= 0x1fffffffffffffff - (uVar5 >> 1)) {
        uVar9 = uVar5 + (uVar5 >> 1);
      }
      if (uVar9 < uVar11) {
        uVar9 = uVar11;
      }
      pvVar3 = (void *)FUN_1400285a0(param_1 + 0x10,uVar9);
      lVar4 = *(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18) >> 3;
      puVar6 = (undefined8 *)((longlong)pvVar3 + lVar4 * 8);
      for (uVar5 = param_3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *puVar6 = *param_4;
        puVar6 = puVar6 + 1;
      }
      lVar7 = *(longlong *)(param_2 + 8) - (longlong)*(void **)(param_1 + 0x18) >> 3;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 3;
        memmove_s(pvVar3,rVar8,*(void **)(param_1 + 0x18),rVar8);
      }
      lVar7 = *(longlong *)(param_1 + 0x20) - (longlong)*(void **)(param_2 + 8) >> 3;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 3;
        memmove_s((void *)((longlong)pvVar3 + (lVar4 + param_3) * 8),rVar8,*(void **)(param_2 + 8),
                  rVar8);
      }
      pvVar10 = *(void **)(param_1 + 0x18);
      lVar4 = *(longlong *)(param_1 + 0x20);
      if (pvVar10 != (void *)0x0) {
        operator_delete(pvVar10);
      }
      *(void **)(param_1 + 0x28) = (void *)((longlong)pvVar3 + uVar9 * 8);
      *(void **)(param_1 + 0x20) =
           (void *)((longlong)pvVar3 + (param_3 + (lVar4 - (longlong)pvVar10 >> 3)) * 8);
      *(void **)(param_1 + 0x18) = pvVar3;
    }
    else if ((ulonglong)(lVar7 - *(longlong *)(param_2 + 8) >> 3) < param_3) {
      uVar1 = *param_4;
      FUN_14002c470(param_1,*(void **)(param_2 + 8),lVar7,
                    (void *)((longlong)*(void **)(param_2 + 8) + param_3 * 8));
      puVar6 = *(undefined8 **)(param_1 + 0x20);
      for (lVar4 = param_3 - ((longlong)puVar6 - *(longlong *)(param_2 + 8) >> 3); lVar4 != 0;
          lVar4 = lVar4 + -1) {
        *puVar6 = uVar1;
        puVar6 = puVar6 + 1;
      }
      *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + param_3 * 8;
      lVar4 = *(longlong *)(param_1 + 0x20);
      for (puVar6 = *(undefined8 **)(param_2 + 8); puVar6 != (undefined8 *)(lVar4 + param_3 * -8);
          puVar6 = puVar6 + 1) {
        *puVar6 = uVar1;
      }
    }
    else {
      uVar1 = *param_4;
      pvVar10 = (void *)(lVar7 + param_3 * -8);
      pvVar3 = FUN_14002c470(param_1,pvVar10,lVar7,(void *)lVar7);
      *(void **)(param_1 + 0x20) = pvVar3;
      FUN_14002c1c0(*(void **)(param_2 + 8),(longlong)pvVar10,lVar7);
      puVar12 = *(undefined8 **)(param_2 + 8);
      puVar6 = puVar12 + param_3;
      for (; puVar12 != puVar6; puVar12 = puVar12 + 1) {
        *puVar12 = uVar1;
      }
    }
  }
  return;
}


// ==== FUN_14002dfb0 @ 14002dfb0  undefined FUN_14002dfb0(longlong param_1, longlong param_2, ulonglong param_3, undefined8 * param_4)

void FUN_14002dfb0(longlong param_1,longlong param_2,ulonglong param_3,undefined8 *param_4)

{
  undefined8 uVar1;
  code *pcVar2;
  void *pvVar3;
  longlong lVar4;
  ulonglong uVar5;
  undefined8 *puVar6;
  longlong lVar7;
  rsize_t rVar8;
  ulonglong uVar9;
  void *pvVar10;
  ulonglong uVar11;
  undefined8 *puVar12;
  
  lVar4 = *(longlong *)(param_1 + 0x18);
  if (lVar4 == 0) {
    uVar5 = 0;
  }
  else {
    uVar5 = *(longlong *)(param_1 + 0x28) - lVar4 >> 3;
  }
  uVar9 = 0;
  if (param_3 != 0) {
    lVar7 = *(longlong *)(param_1 + 0x20);
    lVar4 = lVar7 - lVar4 >> 3;
    if (0x1fffffffffffffffU - lVar4 < param_3) {
      FUN_140026f30();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    uVar11 = param_3 + lVar4;
    if (uVar5 < uVar11) {
      if (uVar5 <= 0x1fffffffffffffff - (uVar5 >> 1)) {
        uVar9 = uVar5 + (uVar5 >> 1);
      }
      if (uVar9 < uVar11) {
        uVar9 = uVar11;
      }
      pvVar3 = (void *)FUN_140028660(param_1 + 0x10,uVar9);
      lVar4 = *(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18) >> 3;
      puVar6 = (undefined8 *)((longlong)pvVar3 + lVar4 * 8);
      for (uVar5 = param_3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *puVar6 = *param_4;
        puVar6 = puVar6 + 1;
      }
      lVar7 = *(longlong *)(param_2 + 8) - (longlong)*(void **)(param_1 + 0x18) >> 3;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 3;
        memmove_s(pvVar3,rVar8,*(void **)(param_1 + 0x18),rVar8);
      }
      lVar7 = *(longlong *)(param_1 + 0x20) - (longlong)*(void **)(param_2 + 8) >> 3;
      if (lVar7 != 0) {
        rVar8 = lVar7 << 3;
        memmove_s((void *)((longlong)pvVar3 + (lVar4 + param_3) * 8),rVar8,*(void **)(param_2 + 8),
                  rVar8);
      }
      pvVar10 = *(void **)(param_1 + 0x18);
      lVar4 = *(longlong *)(param_1 + 0x20);
      if (pvVar10 != (void *)0x0) {
        operator_delete(pvVar10);
      }
      *(void **)(param_1 + 0x28) = (void *)((longlong)pvVar3 + uVar9 * 8);
      *(void **)(param_1 + 0x20) =
           (void *)((longlong)pvVar3 + (param_3 + (lVar4 - (longlong)pvVar10 >> 3)) * 8);
      *(void **)(param_1 + 0x18) = pvVar3;
    }
    else if ((ulonglong)(lVar7 - *(longlong *)(param_2 + 8) >> 3) < param_3) {
      uVar1 = *param_4;
      FUN_14002cfc0(param_1,*(void **)(param_2 + 8),lVar7,
                    (void *)((longlong)*(void **)(param_2 + 8) + param_3 * 8));
      puVar6 = *(undefined8 **)(param_1 + 0x20);
      for (lVar4 = param_3 - ((longlong)puVar6 - *(longlong *)(param_2 + 8) >> 3); lVar4 != 0;
          lVar4 = lVar4 + -1) {
        *puVar6 = uVar1;
        puVar6 = puVar6 + 1;
      }
      *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + param_3 * 8;
      lVar4 = *(longlong *)(param_1 + 0x20);
      for (puVar6 = *(undefined8 **)(param_2 + 8); puVar6 != (undefined8 *)(lVar4 + param_3 * -8);
          puVar6 = puVar6 + 1) {
        *puVar6 = uVar1;
      }
    }
    else {
      uVar1 = *param_4;
      pvVar10 = (void *)(lVar7 + param_3 * -8);
      pvVar3 = FUN_14002cfc0(param_1,pvVar10,lVar7,(void *)lVar7);
      *(void **)(param_1 + 0x20) = pvVar3;
      FUN_14002cd10(*(void **)(param_2 + 8),(longlong)pvVar10,lVar7);
      puVar12 = *(undefined8 **)(param_2 + 8);
      puVar6 = puVar12 + param_3;
      for (; puVar12 != puVar6; puVar12 = puVar12 + 1) {
        *puVar12 = uVar1;
      }
    }
  }
  return;
}


// ==== FUN_14002e260 @ 14002e260  undefined FUN_14002e260(longlong * param_1)

void FUN_14002e260(longlong *param_1)

{
  rsize_t _DstSize;
  void *_Src;
  void *_Dst;
  longlong lVar1;
  
  _Src = (void *)param_1[4];
  if (_Src < (void *)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  _Dst = (void *)param_1[3];
  if ((void *)param_1[4] < _Dst) {
    _invalid_parameter_noinfo();
  }
  if ((_Dst < (void *)param_1[3]) || ((void *)param_1[4] < _Dst)) {
    _invalid_parameter_noinfo();
  }
  lVar1 = *param_1;
  if ((_Src < (void *)param_1[3]) || ((void *)param_1[4] < _Src)) {
    _invalid_parameter_noinfo();
  }
  if ((lVar1 == 0) || (lVar1 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (_Dst != _Src) {
    lVar1 = param_1[4] - (longlong)_Src >> 3;
    _DstSize = lVar1 * 8;
    if (0 < lVar1) {
      memmove_s(_Dst,_DstSize,_Src,_DstSize);
    }
    param_1[4] = (longlong)(_DstSize + (longlong)_Dst);
  }
  return;
}


// ==== FUN_14002e320 @ 14002e320  undefined FUN_14002e320(longlong * param_1)

void FUN_14002e320(longlong *param_1)

{
  rsize_t _DstSize;
  void *_Src;
  void *_Dst;
  longlong lVar1;
  
  _Src = (void *)param_1[4];
  if (_Src < (void *)param_1[3]) {
    _invalid_parameter_noinfo();
  }
  _Dst = (void *)param_1[3];
  if ((void *)param_1[4] < _Dst) {
    _invalid_parameter_noinfo();
  }
  if ((_Dst < (void *)param_1[3]) || ((void *)param_1[4] < _Dst)) {
    _invalid_parameter_noinfo();
  }
  lVar1 = *param_1;
  if ((_Src < (void *)param_1[3]) || ((void *)param_1[4] < _Src)) {
    _invalid_parameter_noinfo();
  }
  if ((lVar1 == 0) || (lVar1 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (_Dst != _Src) {
    lVar1 = param_1[4] - (longlong)_Src >> 3;
    _DstSize = lVar1 * 8;
    if (0 < lVar1) {
      memmove_s(_Dst,_DstSize,_Src,_DstSize);
    }
    param_1[4] = (longlong)(_DstSize + (longlong)_Dst);
  }
  return;
}


// ==== FUN_14002e3e0 @ 14002e3e0  undefined8 * FUN_14002e3e0(undefined1 param_1)

undefined8 * FUN_14002e3e0(undefined1 param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x40);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    puVar1 = FUN_14002ba50(puVar1,param_1);
  }
  return puVar1;
}


// ==== FUN_14002e420 @ 14002e420  undefined8 * FUN_14002e420(undefined1 param_1)

undefined8 * FUN_14002e420(undefined1 param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x40);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    puVar1 = FUN_14002c5a0(puVar1,param_1);
  }
  return puVar1;
}


// ==== FUN_14002e460 @ 14002e460  undefined4 * FUN_14002e460(undefined4 * param_1, undefined4 * param_2, undefined8 * param_3)

undefined4 * FUN_14002e460(undefined4 *param_1,undefined4 *param_2,undefined8 *param_3)

{
  *param_1 = *param_2;
  FUN_14002d0f0((undefined8 *)(param_1 + 2),param_3);
  return param_1;
}


// ==== FUN_14002e490 @ 14002e490  undefined4 * FUN_14002e490(undefined4 * param_1, undefined4 * param_2, undefined8 * param_3)

undefined4 * FUN_14002e490(undefined4 *param_1,undefined4 *param_2,undefined8 *param_3)

{
  *param_1 = *param_2;
  FUN_14002d250((undefined8 *)(param_1 + 2),param_3);
  return param_1;
}


// ==== FUN_14002e4c0 @ 14002e4c0  undefined8 * FUN_14002e4c0(undefined8 * param_1)

undefined8 * FUN_14002e4c0(undefined8 *param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  lVar2 = FUN_140029210();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x51) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_14002e540 @ 14002e540  undefined8 * FUN_14002e540(undefined8 * param_1)

undefined8 * FUN_14002e540(undefined8 *param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  lVar2 = FUN_140029270();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x51) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_14002e5c0 @ 14002e5c0  longlong * FUN_14002e5c0(longlong * param_1, longlong * param_2, longlong * param_3, undefined4 * param_4)

longlong * FUN_14002e5c0(longlong *param_1,longlong *param_2,longlong *param_3,undefined4 *param_4)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  longlong *local_28;
  ulonglong uStack_20;
  
  lVar3 = 0;
  uVar1 = param_1[3];
  lVar4 = lVar3;
  if ((param_1[4] - uVar1 & 0xfffffffffffffffc) != 0) {
    if ((ulonglong)param_1[4] < uVar1) {
      _invalid_parameter_noinfo();
    }
    if ((*param_3 == 0) || (*param_3 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    lVar4 = (longlong)(param_3[1] - uVar1) >> 2;
  }
  local_28 = (longlong *)*param_3;
  uStack_20 = param_3[1];
  FUN_14002d450((longlong)param_1,(longlong)&local_28,1,param_4);
  uVar1 = param_1[3];
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)*param_1;
  local_28 = plVar2;
  uStack_20 = uVar1;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar3;
  }
  else {
    lVar5 = *plVar2;
  }
  uVar1 = uVar1 + lVar4 * 4;
  if (uVar1 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar2 != (longlong *)0x0) {
      lVar3 = *plVar2;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar1) goto LAB_14002e6b4;
  }
  _invalid_parameter_noinfo();
LAB_14002e6b4:
  *param_2 = (longlong)local_28;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_14002e6f0 @ 14002e6f0  longlong * FUN_14002e6f0(longlong * param_1, longlong * param_2, longlong * param_3, undefined8 * param_4)

longlong * FUN_14002e6f0(longlong *param_1,longlong *param_2,longlong *param_3,undefined8 *param_4)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  longlong *local_28;
  ulonglong uStack_20;
  
  lVar3 = 0;
  uVar1 = param_1[3];
  lVar4 = lVar3;
  if ((param_1[4] - uVar1 & 0xfffffffffffffff8) != 0) {
    if ((ulonglong)param_1[4] < uVar1) {
      _invalid_parameter_noinfo();
    }
    if ((*param_3 == 0) || (*param_3 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    lVar4 = (longlong)(param_3[1] - uVar1) >> 3;
  }
  local_28 = (longlong *)*param_3;
  uStack_20 = param_3[1];
  FUN_14002d6f0((longlong)param_1,(longlong)&local_28,1,param_4);
  uVar1 = param_1[3];
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)*param_1;
  local_28 = plVar2;
  uStack_20 = uVar1;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar3;
  }
  else {
    lVar5 = *plVar2;
  }
  uVar1 = uVar1 + lVar4 * 8;
  if (uVar1 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar2 != (longlong *)0x0) {
      lVar3 = *plVar2;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar1) goto LAB_14002e7e4;
  }
  _invalid_parameter_noinfo();
LAB_14002e7e4:
  *param_2 = (longlong)local_28;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_14002e820 @ 14002e820  undefined FUN_14002e820(longlong * param_1)

void FUN_14002e820(longlong *param_1)

{
  FUN_14002d9a0(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14002e850 @ 14002e850  undefined8 * FUN_14002e850(undefined8 * param_1)

undefined8 * FUN_14002e850(undefined8 *param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  lVar2 = FUN_140029930();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x29) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_14002e8d0 @ 14002e8d0  undefined8 * FUN_14002e8d0(undefined8 * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, undefined4 * param_5, undefined1 param_6)

undefined8 *
FUN_14002e8d0(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             undefined4 *param_5,undefined1 param_6)

{
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  *(undefined4 *)(param_1 + 3) = *param_5;
  FUN_14002d250(param_1 + 4,(undefined8 *)(param_5 + 2));
  *(undefined1 *)(param_1 + 10) = param_6;
  *(undefined1 *)((longlong)param_1 + 0x51) = 0;
  return param_1;
}


// ==== FUN_14002e930 @ 14002e930  undefined8 * FUN_14002e930(undefined8 * param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, undefined4 * param_5, undefined1 param_6)

undefined8 *
FUN_14002e930(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             undefined4 *param_5,undefined1 param_6)

{
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  *(undefined4 *)(param_1 + 3) = *param_5;
  FUN_14002d0f0(param_1 + 4,(undefined8 *)(param_5 + 2));
  *(undefined1 *)(param_1 + 10) = param_6;
  *(undefined1 *)((longlong)param_1 + 0x51) = 0;
  return param_1;
}


// ==== FUN_14002ef30 @ 14002ef30  void * FUN_14002ef30(void * param_1, uint param_2)

void * FUN_14002ef30(void *param_1,uint param_2)

{
  if (*(void **)((longlong)param_1 + 0x38) != (void *)0x0) {
    operator_delete(*(void **)((longlong)param_1 + 0x38));
  }
  *(undefined8 *)((longlong)param_1 + 0x38) = 0;
  *(undefined8 *)((longlong)param_1 + 0x40) = 0;
  *(undefined8 *)((longlong)param_1 + 0x48) = 0;
  operator_delete(*(void **)((longlong)param_1 + 0x20));
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_14002efb0 @ 14002efb0  void * FUN_14002efb0(void * param_1, uint param_2)

void * FUN_14002efb0(void *param_1,uint param_2)

{
  if (*(void **)((longlong)param_1 + 0x38) != (void *)0x0) {
    operator_delete(*(void **)((longlong)param_1 + 0x38));
  }
  *(undefined8 *)((longlong)param_1 + 0x38) = 0;
  *(undefined8 *)((longlong)param_1 + 0x40) = 0;
  *(undefined8 *)((longlong)param_1 + 0x48) = 0;
  operator_delete(*(void **)((longlong)param_1 + 0x20));
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_14002f030 @ 14002f030  longlong * FUN_14002f030(longlong * param_1, longlong * param_2, longlong * param_3, undefined8 * param_4)

longlong * FUN_14002f030(longlong *param_1,longlong *param_2,longlong *param_3,undefined8 *param_4)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  longlong *local_28;
  ulonglong uStack_20;
  
  lVar3 = 0;
  uVar1 = param_1[3];
  lVar4 = lVar3;
  if ((param_1[4] - uVar1 & 0xfffffffffffffff8) != 0) {
    if ((ulonglong)param_1[4] < uVar1) {
      _invalid_parameter_noinfo();
    }
    if ((*param_3 == 0) || (*param_3 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    lVar4 = (longlong)(param_3[1] - uVar1) >> 3;
  }
  local_28 = (longlong *)*param_3;
  uStack_20 = param_3[1];
  FUN_14002dd00((longlong)param_1,(longlong)&local_28,1,param_4);
  uVar1 = param_1[3];
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)*param_1;
  local_28 = plVar2;
  uStack_20 = uVar1;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar3;
  }
  else {
    lVar5 = *plVar2;
  }
  uVar1 = uVar1 + lVar4 * 8;
  if (uVar1 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar2 != (longlong *)0x0) {
      lVar3 = *plVar2;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar1) goto LAB_14002f124;
  }
  _invalid_parameter_noinfo();
LAB_14002f124:
  *param_2 = (longlong)local_28;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_14002f160 @ 14002f160  longlong * FUN_14002f160(longlong * param_1, longlong * param_2, longlong * param_3, undefined8 * param_4)

longlong * FUN_14002f160(longlong *param_1,longlong *param_2,longlong *param_3,undefined8 *param_4)

{
  ulonglong uVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  longlong *local_28;
  ulonglong uStack_20;
  
  lVar3 = 0;
  uVar1 = param_1[3];
  lVar4 = lVar3;
  if ((param_1[4] - uVar1 & 0xfffffffffffffff8) != 0) {
    if ((ulonglong)param_1[4] < uVar1) {
      _invalid_parameter_noinfo();
    }
    if ((*param_3 == 0) || (*param_3 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    lVar4 = (longlong)(param_3[1] - uVar1) >> 3;
  }
  local_28 = (longlong *)*param_3;
  uStack_20 = param_3[1];
  FUN_14002dfb0((longlong)param_1,(longlong)&local_28,1,param_4);
  uVar1 = param_1[3];
  if ((ulonglong)param_1[4] < uVar1) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)*param_1;
  local_28 = plVar2;
  uStack_20 = uVar1;
  if (plVar2 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar3;
  }
  else {
    lVar5 = *plVar2;
  }
  uVar1 = uVar1 + lVar4 * 8;
  if (uVar1 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar2 != (longlong *)0x0) {
      lVar3 = *plVar2;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar1) goto LAB_14002f254;
  }
  _invalid_parameter_noinfo();
LAB_14002f254:
  *param_2 = (longlong)local_28;
  param_2[1] = uVar1;
  return param_2;
}


// ==== FUN_14002f290 @ 14002f290  undefined FUN_14002f290(longlong param_1)

void FUN_14002f290(longlong param_1)

{
  longlong *plVar1;
  ulonglong uVar2;
  
  if ((*(char *)(param_1 + 0x38) != '\0') &&
     (uVar2 = 0, *(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3 != 0)) {
    do {
      if ((ulonglong)(*(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3) <= uVar2)
      {
        _invalid_parameter_noinfo();
      }
      plVar1 = *(longlong **)(*(longlong *)(param_1 + 0x20) + uVar2 * 8);
      if (plVar1 != (longlong *)0x0) {
        (**(code **)(*plVar1 + 0xa0))();
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < (ulonglong)(*(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3)
            );
  }
  FUN_14002e260((longlong *)(param_1 + 8));
  return;
}


// ==== FUN_14002f320 @ 14002f320  undefined FUN_14002f320(longlong param_1)

void FUN_14002f320(longlong param_1)

{
  undefined8 *puVar1;
  ulonglong uVar2;
  
  if ((*(char *)(param_1 + 0x38) != '\0') &&
     (uVar2 = 0, *(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3 != 0)) {
    do {
      if ((ulonglong)(*(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3) <= uVar2)
      {
        _invalid_parameter_noinfo();
      }
      puVar1 = *(undefined8 **)(*(longlong *)(param_1 + 0x20) + uVar2 * 8);
      if (puVar1 != (undefined8 *)0x0) {
        (**(code **)*puVar1)(puVar1,1);
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < (ulonglong)(*(longlong *)(param_1 + 0x28) - *(longlong *)(param_1 + 0x20) >> 3)
            );
  }
  FUN_14002e320((longlong *)(param_1 + 8));
  return;
}


// ==== FUN_14002f3b0 @ 14002f3b0  undefined FUN_14002f3b0(longlong * param_1, undefined4 * param_2)

void FUN_14002f3b0(longlong *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  ulonglong uVar3;
  longlong local_28;
  undefined4 *puStack_20;
  longlong local_18 [2];
  
  puVar1 = (undefined4 *)param_1[3];
  if (puVar1 == (undefined4 *)0x0) {
    uVar3 = 0;
  }
  else {
    uVar3 = param_1[5] - (longlong)puVar1 >> 2;
  }
  puVar2 = (undefined4 *)param_1[4];
  if ((ulonglong)((longlong)puVar2 - (longlong)puVar1 >> 2) < uVar3) {
    *puVar2 = *param_2;
    param_1[4] = (longlong)(puVar2 + 1);
    return;
  }
  if (puVar2 < puVar1) {
    _invalid_parameter_noinfo();
  }
  local_28 = *param_1;
  puStack_20 = puVar2;
  FUN_14002e5c0(param_1,local_18,&local_28,param_2);
  return;
}


// ==== FUN_14002f460 @ 14002f460  undefined FUN_14002f460(longlong * param_1, undefined8 * param_2)

void FUN_14002f460(longlong *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  ulonglong uVar3;
  longlong local_28;
  undefined8 *puStack_20;
  longlong local_18 [2];
  
  puVar1 = (undefined8 *)param_1[3];
  if (puVar1 == (undefined8 *)0x0) {
    uVar3 = 0;
  }
  else {
    uVar3 = param_1[5] - (longlong)puVar1 >> 3;
  }
  puVar2 = (undefined8 *)param_1[4];
  if ((ulonglong)((longlong)puVar2 - (longlong)puVar1 >> 3) < uVar3) {
    *puVar2 = *param_2;
    param_1[4] = (longlong)(puVar2 + 1);
    return;
  }
  if (puVar2 < puVar1) {
    _invalid_parameter_noinfo();
  }
  local_28 = *param_1;
  puStack_20 = puVar2;
  FUN_14002e6f0(param_1,local_18,&local_28,param_2);
  return;
}


// ==== FUN_14002f510 @ 14002f510  undefined FUN_14002f510(longlong * param_1)

void FUN_14002f510(longlong *param_1)

{
  FUN_14002d9a0(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_14002f540 @ 14002f540  undefined8 * FUN_14002f540(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, undefined4 * param_5, undefined1 param_6)

undefined8 *
FUN_14002f540(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             undefined4 *param_5,undefined1 param_6)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x58);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_2;
    puVar1[1] = param_3;
    puVar1[2] = param_4;
    *(undefined4 *)(puVar1 + 3) = *param_5;
    FUN_14002d250(puVar1 + 4,(undefined8 *)(param_5 + 2));
    *(undefined1 *)(puVar1 + 10) = param_6;
    *(undefined1 *)((longlong)puVar1 + 0x51) = 0;
  }
  return puVar1;
}


// ==== FUN_14002f5e0 @ 14002f5e0  undefined8 * FUN_14002f5e0(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, undefined4 * param_5, undefined1 param_6)

undefined8 *
FUN_14002f5e0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             undefined4 *param_5,undefined1 param_6)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x58);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_2;
    puVar1[1] = param_3;
    puVar1[2] = param_4;
    *(undefined4 *)(puVar1 + 3) = *param_5;
    FUN_14002d0f0(puVar1 + 4,(undefined8 *)(param_5 + 2));
    *(undefined1 *)(puVar1 + 10) = param_6;
    *(undefined1 *)((longlong)puVar1 + 0x51) = 0;
  }
  return puVar1;
}


// ==== FUN_14002f680 @ 14002f680  undefined8 * FUN_14002f680(undefined8 * param_1)

undefined8 * FUN_14002f680(undefined8 *param_1)

{
  undefined8 *puVar1;
  longlong lVar2;
  
  puVar1 = (undefined8 *)operator_new(8);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = param_1;
  }
  *param_1 = puVar1;
  lVar2 = FUN_140029930();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x29) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_14002f700 @ 14002f700  undefined FUN_14002f700(undefined8 * param_1)

void FUN_14002f700(undefined8 *param_1)

{
  *param_1 = CGameObjSet<class_IGenerator>::vftable;
  FUN_14002f290((longlong)param_1);
  if ((void *)param_1[4] != (void *)0x0) {
    operator_delete((void *)param_1[4]);
  }
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  operator_delete((void *)param_1[1]);
  *param_1 = IGameObjSet<class_IGenerator>::vftable;
  return;
}


// ==== FUN_14002f770 @ 14002f770  undefined FUN_14002f770(undefined8 * param_1)

void FUN_14002f770(undefined8 *param_1)

{
  *param_1 = CGameObjSet<class_CNpcType>::vftable;
  FUN_14002f320((longlong)param_1);
  if ((void *)param_1[4] != (void *)0x0) {
    operator_delete((void *)param_1[4]);
  }
  param_1[4] = 0;
  param_1[5] = 0;
  param_1[6] = 0;
  operator_delete((void *)param_1[1]);
  *param_1 = IGameObjSet<class_CNpcType>::vftable;
  return;
}


// ==== FUN_14002f7e0 @ 14002f7e0  undefined FUN_14002f7e0(longlong param_1)

void FUN_14002f7e0(longlong param_1)

{
  if (*(void **)(param_1 + 0x38) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x38));
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  operator_delete(*(void **)(param_1 + 0x20));
  return;
}


// ==== FUN_14002f830 @ 14002f830  undefined FUN_14002f830(longlong param_1)

void FUN_14002f830(longlong param_1)

{
  if (*(void **)(param_1 + 0x38) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x38));
  }
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  *(undefined8 *)(param_1 + 0x48) = 0;
  operator_delete(*(void **)(param_1 + 0x20));
  return;
}


// ==== FUN_14002f880 @ 14002f880  undefined FUN_14002f880(longlong * param_1, undefined8 * param_2)

void FUN_14002f880(longlong *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  ulonglong uVar3;
  longlong local_28;
  undefined8 *puStack_20;
  longlong local_18 [2];
  
  puVar1 = (undefined8 *)param_1[3];
  if (puVar1 == (undefined8 *)0x0) {
    uVar3 = 0;
  }
  else {
    uVar3 = param_1[5] - (longlong)puVar1 >> 3;
  }
  puVar2 = (undefined8 *)param_1[4];
  if ((ulonglong)((longlong)puVar2 - (longlong)puVar1 >> 3) < uVar3) {
    *puVar2 = *param_2;
    param_1[4] = (longlong)(puVar2 + 1);
    return;
  }
  if (puVar2 < puVar1) {
    _invalid_parameter_noinfo();
  }
  local_28 = *param_1;
  puStack_20 = puVar2;
  FUN_14002f030(param_1,local_18,&local_28,param_2);
  return;
}


// ==== FUN_14002f930 @ 14002f930  undefined FUN_14002f930(longlong * param_1, undefined8 * param_2)

void FUN_14002f930(longlong *param_1,undefined8 *param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  ulonglong uVar3;
  longlong local_28;
  undefined8 *puStack_20;
  longlong local_18 [2];
  
  puVar1 = (undefined8 *)param_1[3];
  if (puVar1 == (undefined8 *)0x0) {
    uVar3 = 0;
  }
  else {
    uVar3 = param_1[5] - (longlong)puVar1 >> 3;
  }
  puVar2 = (undefined8 *)param_1[4];
  if ((ulonglong)((longlong)puVar2 - (longlong)puVar1 >> 3) < uVar3) {
    *puVar2 = *param_2;
    param_1[4] = (longlong)(puVar2 + 1);
    return;
  }
  if (puVar2 < puVar1) {
    _invalid_parameter_noinfo();
  }
  local_28 = *param_1;
  puStack_20 = puVar2;
  FUN_14002f160(param_1,local_18,&local_28,param_2);
  return;
}


// ==== FUN_14002f9e0 @ 14002f9e0  undefined8 * FUN_14002f9e0(undefined8 * param_1, undefined8 * param_2, char param_3, undefined8 * param_4, undefined4 * param_5)

undefined8 *
FUN_14002f9e0(undefined8 *param_1,undefined8 *param_2,char param_3,undefined8 *param_4,
             undefined4 *param_5)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [40];
  
  if (0x492492492492490 < (ulonglong)param_1[7]) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_70,"map/set<T> too long");
    std::exception::exception((exception *)local_48);
    local_48[0] = std::logic_error::vftable;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
    local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
  }
  plVar5 = FUN_14002f540(param_1,param_1[6],param_4,param_1[6],param_5,0);
  param_1[7] = param_1[7] + 1;
  if (param_4 == (undefined8 *)param_1[6]) {
    ((undefined8 *)param_1[6])[1] = plVar5;
    *(longlong **)param_1[6] = plVar5;
    *(longlong **)(param_1[6] + 0x10) = plVar5;
  }
  else if (param_3 == '\0') {
    param_4[2] = plVar5;
    if (param_4 == *(undefined8 **)(param_1[6] + 0x10)) {
      *(longlong **)(param_1[6] + 0x10) = plVar5;
    }
  }
  else {
    *param_4 = plVar5;
    if (param_4 == *(undefined8 **)param_1[6]) {
      *(longlong **)param_1[6] = plVar5;
    }
  }
  plVar7 = plVar5 + 1;
  cVar1 = *(char *)(*plVar7 + 0x50);
  plVar6 = plVar5;
  while (cVar1 == '\0') {
    plVar2 = (longlong *)*plVar7;
    plVar3 = (longlong *)plVar2[1];
    if (plVar2 == (longlong *)*plVar3) {
      lVar4 = plVar3[2];
      if (*(char *)(lVar4 + 0x50) == '\0') {
        *(undefined1 *)(plVar2 + 10) = 1;
        *(undefined1 *)(lVar4 + 0x50) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x50) = 0;
        plVar6 = *(longlong **)(*plVar7 + 8);
      }
      else {
        if (plVar6 == (longlong *)plVar2[2]) {
          plVar6 = (longlong *)plVar2[2];
          plVar2[2] = *plVar6;
          if (*(char *)(*plVar6 + 0x51) == '\0') {
            *(longlong **)(*plVar6 + 8) = plVar2;
          }
          plVar7 = plVar2 + 1;
          plVar6[1] = *plVar7;
          if (plVar2 == *(longlong **)(param_1[6] + 8)) {
            *(longlong **)(param_1[6] + 8) = plVar6;
          }
          else {
            plVar3 = (longlong *)*plVar7;
            if (plVar2 == (longlong *)*plVar3) {
              *plVar3 = (longlong)plVar6;
            }
            else {
              plVar3[2] = (longlong)plVar6;
            }
          }
          *plVar6 = (longlong)plVar2;
          *plVar7 = (longlong)plVar6;
          plVar6 = plVar2;
        }
        *(undefined1 *)(*plVar7 + 0x50) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x50) = 0;
        plVar7 = *(longlong **)(*plVar7 + 8);
        lVar4 = *plVar7;
        *plVar7 = *(longlong *)(lVar4 + 0x10);
        if (*(char *)(*(longlong *)(lVar4 + 0x10) + 0x51) == '\0') {
          *(longlong **)(*(longlong *)(lVar4 + 0x10) + 8) = plVar7;
        }
        *(longlong *)(lVar4 + 8) = plVar7[1];
        if (plVar7 == *(longlong **)(param_1[6] + 8)) {
          *(longlong *)(param_1[6] + 8) = lVar4;
        }
        else {
          plVar2 = (longlong *)plVar7[1];
          if (plVar7 == (longlong *)plVar2[2]) {
            plVar2[2] = lVar4;
          }
          else {
            *plVar2 = lVar4;
          }
        }
        *(longlong **)(lVar4 + 0x10) = plVar7;
        plVar7[1] = lVar4;
      }
    }
    else {
      lVar4 = *plVar3;
      if (*(char *)(lVar4 + 0x50) == '\0') {
        *(undefined1 *)(plVar2 + 10) = 1;
        *(undefined1 *)(lVar4 + 0x50) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x50) = 0;
        plVar6 = *(longlong **)(*plVar7 + 8);
      }
      else {
        if (plVar6 == (longlong *)*plVar2) {
          lVar4 = *plVar2;
          *plVar2 = *(longlong *)(lVar4 + 0x10);
          if (*(char *)(*(longlong *)(lVar4 + 0x10) + 0x51) == '\0') {
            *(longlong **)(*(longlong *)(lVar4 + 0x10) + 8) = plVar2;
          }
          plVar7 = plVar2 + 1;
          *(longlong *)(lVar4 + 8) = *plVar7;
          if (plVar2 == *(longlong **)(param_1[6] + 8)) {
            *(longlong *)(param_1[6] + 8) = lVar4;
          }
          else {
            plVar6 = (longlong *)*plVar7;
            if (plVar2 == (longlong *)plVar6[2]) {
              plVar6[2] = lVar4;
            }
            else {
              *plVar6 = lVar4;
            }
          }
          *(longlong **)(lVar4 + 0x10) = plVar2;
          *plVar7 = lVar4;
          plVar6 = plVar2;
        }
        *(undefined1 *)(*plVar7 + 0x50) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x50) = 0;
        lVar4 = *(longlong *)(*plVar7 + 8);
        plVar7 = *(longlong **)(lVar4 + 0x10);
        *(longlong *)(lVar4 + 0x10) = *plVar7;
        if (*(char *)(*plVar7 + 0x51) == '\0') {
          *(longlong *)(*plVar7 + 8) = lVar4;
        }
        plVar7[1] = *(longlong *)(lVar4 + 8);
        if (lVar4 == *(longlong *)(param_1[6] + 8)) {
          *(longlong **)(param_1[6] + 8) = plVar7;
        }
        else {
          plVar2 = *(longlong **)(lVar4 + 8);
          if (lVar4 == *plVar2) {
            *plVar2 = (longlong)plVar7;
          }
          else {
            plVar2[2] = (longlong)plVar7;
          }
        }
        *plVar7 = lVar4;
        *(longlong **)(lVar4 + 8) = plVar7;
      }
    }
    plVar7 = plVar6 + 1;
    cVar1 = *(char *)(*plVar7 + 0x50);
  }
  *(undefined1 *)(*(longlong *)(param_1[6] + 8) + 0x50) = 1;
  param_2[1] = plVar5;
  *param_2 = *param_1;
  return param_2;
}


// ==== FUN_14002fd20 @ 14002fd20  undefined8 * FUN_14002fd20(undefined8 * param_1, undefined8 * param_2, char param_3, undefined8 * param_4, undefined4 * param_5)

undefined8 *
FUN_14002fd20(undefined8 *param_1,undefined8 *param_2,char param_3,undefined8 *param_4,
             undefined4 *param_5)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [40];
  
  if (0x492492492492490 < (ulonglong)param_1[7]) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_70,"map/set<T> too long");
    std::exception::exception((exception *)local_48);
    local_48[0] = std::logic_error::vftable;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
    local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
  }
  plVar5 = FUN_14002f5e0(param_1,param_1[6],param_4,param_1[6],param_5,0);
  param_1[7] = param_1[7] + 1;
  if (param_4 == (undefined8 *)param_1[6]) {
    ((undefined8 *)param_1[6])[1] = plVar5;
    *(longlong **)param_1[6] = plVar5;
    *(longlong **)(param_1[6] + 0x10) = plVar5;
  }
  else if (param_3 == '\0') {
    param_4[2] = plVar5;
    if (param_4 == *(undefined8 **)(param_1[6] + 0x10)) {
      *(longlong **)(param_1[6] + 0x10) = plVar5;
    }
  }
  else {
    *param_4 = plVar5;
    if (param_4 == *(undefined8 **)param_1[6]) {
      *(longlong **)param_1[6] = plVar5;
    }
  }
  plVar7 = plVar5 + 1;
  cVar1 = *(char *)(*plVar7 + 0x50);
  plVar6 = plVar5;
  while (cVar1 == '\0') {
    plVar2 = (longlong *)*plVar7;
    plVar3 = (longlong *)plVar2[1];
    if (plVar2 == (longlong *)*plVar3) {
      lVar4 = plVar3[2];
      if (*(char *)(lVar4 + 0x50) == '\0') {
        *(undefined1 *)(plVar2 + 10) = 1;
        *(undefined1 *)(lVar4 + 0x50) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x50) = 0;
        plVar6 = *(longlong **)(*plVar7 + 8);
      }
      else {
        if (plVar6 == (longlong *)plVar2[2]) {
          plVar6 = (longlong *)plVar2[2];
          plVar2[2] = *plVar6;
          if (*(char *)(*plVar6 + 0x51) == '\0') {
            *(longlong **)(*plVar6 + 8) = plVar2;
          }
          plVar7 = plVar2 + 1;
          plVar6[1] = *plVar7;
          if (plVar2 == *(longlong **)(param_1[6] + 8)) {
            *(longlong **)(param_1[6] + 8) = plVar6;
          }
          else {
            plVar3 = (longlong *)*plVar7;
            if (plVar2 == (longlong *)*plVar3) {
              *plVar3 = (longlong)plVar6;
            }
            else {
              plVar3[2] = (longlong)plVar6;
            }
          }
          *plVar6 = (longlong)plVar2;
          *plVar7 = (longlong)plVar6;
          plVar6 = plVar2;
        }
        *(undefined1 *)(*plVar7 + 0x50) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x50) = 0;
        plVar7 = *(longlong **)(*plVar7 + 8);
        lVar4 = *plVar7;
        *plVar7 = *(longlong *)(lVar4 + 0x10);
        if (*(char *)(*(longlong *)(lVar4 + 0x10) + 0x51) == '\0') {
          *(longlong **)(*(longlong *)(lVar4 + 0x10) + 8) = plVar7;
        }
        *(longlong *)(lVar4 + 8) = plVar7[1];
        if (plVar7 == *(longlong **)(param_1[6] + 8)) {
          *(longlong *)(param_1[6] + 8) = lVar4;
        }
        else {
          plVar2 = (longlong *)plVar7[1];
          if (plVar7 == (longlong *)plVar2[2]) {
            plVar2[2] = lVar4;
          }
          else {
            *plVar2 = lVar4;
          }
        }
        *(longlong **)(lVar4 + 0x10) = plVar7;
        plVar7[1] = lVar4;
      }
    }
    else {
      lVar4 = *plVar3;
      if (*(char *)(lVar4 + 0x50) == '\0') {
        *(undefined1 *)(plVar2 + 10) = 1;
        *(undefined1 *)(lVar4 + 0x50) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x50) = 0;
        plVar6 = *(longlong **)(*plVar7 + 8);
      }
      else {
        if (plVar6 == (longlong *)*plVar2) {
          lVar4 = *plVar2;
          *plVar2 = *(longlong *)(lVar4 + 0x10);
          if (*(char *)(*(longlong *)(lVar4 + 0x10) + 0x51) == '\0') {
            *(longlong **)(*(longlong *)(lVar4 + 0x10) + 8) = plVar2;
          }
          plVar7 = plVar2 + 1;
          *(longlong *)(lVar4 + 8) = *plVar7;
          if (plVar2 == *(longlong **)(param_1[6] + 8)) {
            *(longlong *)(param_1[6] + 8) = lVar4;
          }
          else {
            plVar6 = (longlong *)*plVar7;
            if (plVar2 == (longlong *)plVar6[2]) {
              plVar6[2] = lVar4;
            }
            else {
              *plVar6 = lVar4;
            }
          }
          *(longlong **)(lVar4 + 0x10) = plVar2;
          *plVar7 = lVar4;
          plVar6 = plVar2;
        }
        *(undefined1 *)(*plVar7 + 0x50) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x50) = 0;
        lVar4 = *(longlong *)(*plVar7 + 8);
        plVar7 = *(longlong **)(lVar4 + 0x10);
        *(longlong *)(lVar4 + 0x10) = *plVar7;
        if (*(char *)(*plVar7 + 0x51) == '\0') {
          *(longlong *)(*plVar7 + 8) = lVar4;
        }
        plVar7[1] = *(longlong *)(lVar4 + 8);
        if (lVar4 == *(longlong *)(param_1[6] + 8)) {
          *(longlong **)(param_1[6] + 8) = plVar7;
        }
        else {
          plVar2 = *(longlong **)(lVar4 + 8);
          if (lVar4 == *plVar2) {
            *plVar2 = (longlong)plVar7;
          }
          else {
            plVar2[2] = (longlong)plVar7;
          }
        }
        *plVar7 = lVar4;
        *(longlong **)(lVar4 + 8) = plVar7;
      }
    }
    plVar7 = plVar6 + 1;
    cVar1 = *(char *)(*plVar7 + 0x50);
  }
  *(undefined1 *)(*(longlong *)(param_1[6] + 8) + 0x50) = 1;
  param_2[1] = plVar5;
  *param_2 = *param_1;
  return param_2;
}


// ==== FUN_140030060 @ 140030060  undefined FUN_140030060(undefined8 param_1, longlong param_2)

void FUN_140030060(undefined8 param_1,longlong param_2)

{
  if (*(void **)(param_2 + 0x38) != (void *)0x0) {
    operator_delete(*(void **)(param_2 + 0x38));
  }
  *(undefined8 *)(param_2 + 0x38) = 0;
  *(undefined8 *)(param_2 + 0x40) = 0;
  *(undefined8 *)(param_2 + 0x48) = 0;
  operator_delete(*(void **)(param_2 + 0x20));
  return;
}


// ==== FUN_1400300b0 @ 1400300b0  undefined8 * FUN_1400300b0(undefined8 * param_1, undefined1 param_2)

undefined8 * FUN_1400300b0(undefined8 *param_1,undefined1 param_2)

{
  *param_1 = ISingleMap<class_INpc>::vftable;
  *param_1 = CSingleMap<class_INpc>::vftable;
  FUN_14002f680(param_1 + 2);
  *(undefined1 *)(param_1 + 1) = param_2;
  return param_1;
}


// ==== FUN_140030160 @ 140030160  undefined FUN_140030160(longlong * param_1)

void FUN_140030160(longlong *param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  plVar2 = (longlong *)param_1[1];
  if (*(char *)((longlong)plVar2 + 0x29) == '\0') {
    lVar3 = *plVar2;
    if (*(char *)(lVar3 + 0x29) == '\0') {
      cVar1 = *(char *)(*(longlong *)(lVar3 + 0x10) + 0x29);
      lVar4 = *(longlong *)(lVar3 + 0x10);
      while (lVar5 = lVar4, cVar1 == '\0') {
        lVar4 = *(longlong *)(lVar5 + 0x10);
        cVar1 = *(char *)(lVar4 + 0x29);
        lVar3 = lVar5;
      }
      param_1[1] = lVar3;
      return;
    }
    plVar2 = (longlong *)plVar2[1];
    cVar1 = *(char *)((longlong)plVar2 + 0x29);
    while ((cVar1 == '\0' && (param_1[1] == *plVar2))) {
      param_1[1] = (longlong)plVar2;
      plVar2 = (longlong *)plVar2[1];
      cVar1 = *(char *)((longlong)plVar2 + 0x29);
    }
    if (*(char *)(param_1[1] + 0x29) == '\0') {
      param_1[1] = (longlong)plVar2;
      return;
    }
  }
  else {
    lVar3 = plVar2[2];
    param_1[1] = lVar3;
    if (*(char *)(lVar3 + 0x29) == '\0') {
      return;
    }
  }
                    /* WARNING: Could not recover jumptable at 0x000140030192. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _invalid_parameter_noinfo();
  return;
}


// ==== FUN_1400302b0 @ 1400302b0  longlong FUN_1400302b0(longlong * param_1)

longlong FUN_1400302b0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_1400302d2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_1400302d2:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_140030330 @ 140030330  longlong * FUN_140030330(longlong * param_1)

longlong * FUN_140030330(longlong *param_1)

{
  FUN_140030160(param_1);
  return param_1;
}


// ==== FUN_140030360 @ 140030360  undefined8 * FUN_140030360(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, undefined8 * param_5, undefined1 param_6)

undefined8 *
FUN_140030360(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
             undefined8 *param_5,undefined1 param_6)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x30);
  if (puVar1 != (undefined8 *)0x0) {
    *puVar1 = param_2;
    puVar1[1] = param_3;
    puVar1[2] = param_4;
    puVar1[3] = *param_5;
    puVar1[4] = param_5[1];
    *(undefined1 *)(puVar1 + 5) = param_6;
    *(undefined1 *)((longlong)puVar1 + 0x29) = 0;
  }
  return puVar1;
}


// ==== FUN_1400303e0 @ 1400303e0  longlong * FUN_1400303e0(longlong * param_1)

longlong * FUN_1400303e0(longlong *param_1)

{
  FUN_140030160(param_1);
  return param_1;
}


// ==== FUN_140030400 @ 140030400  longlong FUN_140030400(longlong * param_1)

longlong FUN_140030400(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140030422;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140030422:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_140030480 @ 140030480  undefined8 * FUN_140030480(undefined8 * param_1, undefined8 * param_2, uint * param_3)

undefined8 * FUN_140030480(undefined8 *param_1,undefined8 *param_2,uint *param_3)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  
  puVar4 = (undefined8 *)param_1[6];
  puVar5 = puVar4;
  if (*(char *)((longlong)puVar4[1] + 0x29) == '\0') {
    puVar2 = (undefined8 *)puVar4[1];
    do {
      if (*(uint *)(puVar2 + 3) < *param_3) {
        puVar3 = (undefined8 *)puVar2[2];
      }
      else {
        if ((*(char *)((longlong)puVar4 + 0x29) != '\0') && (*param_3 < *(uint *)(puVar2 + 3))) {
          puVar4 = puVar2;
        }
        puVar3 = (undefined8 *)*puVar2;
        puVar5 = puVar2;
      }
      puVar2 = puVar3;
    } while (*(char *)((longlong)puVar3 + 0x29) == '\0');
  }
  if (*(char *)((longlong)puVar4 + 0x29) == '\0') {
    puVar2 = (undefined8 *)*puVar4;
  }
  else {
    puVar2 = *(undefined8 **)(param_1[6] + 8);
  }
  if (*(char *)((longlong)puVar2 + 0x29) == '\0') {
    do {
      if (*param_3 < *(uint *)(puVar2 + 3)) {
        puVar3 = (undefined8 *)*puVar2;
        puVar4 = puVar2;
      }
      else {
        puVar3 = (undefined8 *)puVar2[2];
      }
      puVar2 = puVar3;
    } while (*(char *)((longlong)puVar3 + 0x29) == '\0');
  }
  uVar1 = *param_1;
  *param_2 = uVar1;
  param_2[1] = puVar5;
  param_2[2] = uVar1;
  param_2[3] = puVar4;
  return param_2;
}


// ==== FUN_140030560 @ 140030560  undefined8 * FUN_140030560(undefined8 * param_1, undefined8 * param_2, char param_3, undefined8 * param_4, undefined8 * param_5)

undefined8 *
FUN_140030560(undefined8 *param_1,undefined8 *param_2,char param_3,undefined8 *param_4,
             undefined8 *param_5)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_70 [40];
  undefined **local_48 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_30 [40];
  
  if (0xffffffffffffffd < (ulonglong)param_1[7]) {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_70,"map/set<T> too long");
    std::exception::exception((exception *)local_48);
    local_48[0] = std::logic_error::vftable;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_30,local_70);
    local_48[0] = std::length_error::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_48,(ThrowInfo *)&DAT_1400fee30);
  }
  plVar5 = FUN_140030360(param_1,param_1[6],param_4,param_1[6],param_5,0);
  param_1[7] = param_1[7] + 1;
  if (param_4 == (undefined8 *)param_1[6]) {
    ((undefined8 *)param_1[6])[1] = plVar5;
    *(longlong **)param_1[6] = plVar5;
    *(longlong **)(param_1[6] + 0x10) = plVar5;
  }
  else if (param_3 == '\0') {
    param_4[2] = plVar5;
    if (param_4 == *(undefined8 **)(param_1[6] + 0x10)) {
      *(longlong **)(param_1[6] + 0x10) = plVar5;
    }
  }
  else {
    *param_4 = plVar5;
    if (param_4 == *(undefined8 **)param_1[6]) {
      *(longlong **)param_1[6] = plVar5;
    }
  }
  plVar7 = plVar5 + 1;
  cVar1 = *(char *)(*plVar7 + 0x28);
  plVar6 = plVar5;
  while (cVar1 == '\0') {
    plVar2 = (longlong *)*plVar7;
    plVar3 = (longlong *)plVar2[1];
    if (plVar2 == (longlong *)*plVar3) {
      lVar4 = plVar3[2];
      if (*(char *)(lVar4 + 0x28) == '\0') {
        *(undefined1 *)(plVar2 + 5) = 1;
        *(undefined1 *)(lVar4 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        plVar6 = *(longlong **)(*plVar7 + 8);
      }
      else {
        if (plVar6 == (longlong *)plVar2[2]) {
          plVar6 = (longlong *)plVar2[2];
          plVar2[2] = *plVar6;
          if (*(char *)(*plVar6 + 0x29) == '\0') {
            *(longlong **)(*plVar6 + 8) = plVar2;
          }
          plVar7 = plVar2 + 1;
          plVar6[1] = *plVar7;
          if (plVar2 == *(longlong **)(param_1[6] + 8)) {
            *(longlong **)(param_1[6] + 8) = plVar6;
          }
          else {
            plVar3 = (longlong *)*plVar7;
            if (plVar2 == (longlong *)*plVar3) {
              *plVar3 = (longlong)plVar6;
            }
            else {
              plVar3[2] = (longlong)plVar6;
            }
          }
          *plVar6 = (longlong)plVar2;
          *plVar7 = (longlong)plVar6;
          plVar6 = plVar2;
        }
        *(undefined1 *)(*plVar7 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        plVar7 = *(longlong **)(*plVar7 + 8);
        lVar4 = *plVar7;
        *plVar7 = *(longlong *)(lVar4 + 0x10);
        if (*(char *)(*(longlong *)(lVar4 + 0x10) + 0x29) == '\0') {
          *(longlong **)(*(longlong *)(lVar4 + 0x10) + 8) = plVar7;
        }
        *(longlong *)(lVar4 + 8) = plVar7[1];
        if (plVar7 == *(longlong **)(param_1[6] + 8)) {
          *(longlong *)(param_1[6] + 8) = lVar4;
        }
        else {
          plVar2 = (longlong *)plVar7[1];
          if (plVar7 == (longlong *)plVar2[2]) {
            plVar2[2] = lVar4;
          }
          else {
            *plVar2 = lVar4;
          }
        }
        *(longlong **)(lVar4 + 0x10) = plVar7;
        plVar7[1] = lVar4;
      }
    }
    else {
      lVar4 = *plVar3;
      if (*(char *)(lVar4 + 0x28) == '\0') {
        *(undefined1 *)(plVar2 + 5) = 1;
        *(undefined1 *)(lVar4 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        plVar6 = *(longlong **)(*plVar7 + 8);
      }
      else {
        if (plVar6 == (longlong *)*plVar2) {
          lVar4 = *plVar2;
          *plVar2 = *(longlong *)(lVar4 + 0x10);
          if (*(char *)(*(longlong *)(lVar4 + 0x10) + 0x29) == '\0') {
            *(longlong **)(*(longlong *)(lVar4 + 0x10) + 8) = plVar2;
          }
          plVar7 = plVar2 + 1;
          *(longlong *)(lVar4 + 8) = *plVar7;
          if (plVar2 == *(longlong **)(param_1[6] + 8)) {
            *(longlong *)(param_1[6] + 8) = lVar4;
          }
          else {
            plVar6 = (longlong *)*plVar7;
            if (plVar2 == (longlong *)plVar6[2]) {
              plVar6[2] = lVar4;
            }
            else {
              *plVar6 = lVar4;
            }
          }
          *(longlong **)(lVar4 + 0x10) = plVar2;
          *plVar7 = lVar4;
          plVar6 = plVar2;
        }
        *(undefined1 *)(*plVar7 + 0x28) = 1;
        *(undefined1 *)(*(longlong *)(*plVar7 + 8) + 0x28) = 0;
        lVar4 = *(longlong *)(*plVar7 + 8);
        plVar7 = *(longlong **)(lVar4 + 0x10);
        *(longlong *)(lVar4 + 0x10) = *plVar7;
        if (*(char *)(*plVar7 + 0x29) == '\0') {
          *(longlong *)(*plVar7 + 8) = lVar4;
        }
        plVar7[1] = *(longlong *)(lVar4 + 8);
        if (lVar4 == *(longlong *)(param_1[6] + 8)) {
          *(longlong **)(param_1[6] + 8) = plVar7;
        }
        else {
          plVar2 = *(longlong **)(lVar4 + 8);
          if (lVar4 == *plVar2) {
            *plVar2 = (longlong)plVar7;
          }
          else {
            plVar2[2] = (longlong)plVar7;
          }
        }
        *plVar7 = lVar4;
        *(longlong **)(lVar4 + 8) = plVar7;
      }
    }
    plVar7 = plVar6 + 1;
    cVar1 = *(char *)(*plVar7 + 0x28);
  }
  *(undefined1 *)(*(longlong *)(param_1[6] + 8) + 0x28) = 1;
  param_2[1] = plVar5;
  *param_2 = *param_1;
  return param_2;
}


// ==== FUN_1400308a0 @ 1400308a0  longlong FUN_1400308a0(longlong * param_1)

longlong FUN_1400308a0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_1400308c2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_1400308c2:
  if (param_1[1] == puVar1[6]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] + 0x18;
}


// ==== FUN_1400308e0 @ 1400308e0  longlong * FUN_1400308e0(longlong * param_1, longlong * param_2, uint * param_3)

longlong * FUN_1400308e0(longlong *param_1,longlong *param_2,uint *param_3)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong local_28;
  undefined8 *local_20;
  longlong local_18;
  longlong local_10;
  
  puVar4 = (undefined8 *)param_1[6];
  if (*(char *)((longlong)puVar4[1] + 0x29) == '\0') {
    puVar1 = (undefined8 *)puVar4[1];
    do {
      if (*(uint *)(puVar1 + 3) < *param_3) {
        puVar2 = (undefined8 *)puVar1[2];
      }
      else {
        puVar2 = (undefined8 *)*puVar1;
        puVar4 = puVar1;
      }
      puVar1 = puVar2;
    } while (*(char *)((longlong)puVar2 + 0x29) == '\0');
  }
  puVar1 = (undefined8 *)param_1[6];
  local_20 = puVar4;
  local_28 = *param_1;
  if (*param_1 == 0) {
    _invalid_parameter_noinfo();
  }
  if ((puVar4 == puVar1) || (*param_3 < *(uint *)(puVar4 + 3))) {
    plVar3 = &local_18;
    local_10 = param_1[6];
    local_18 = *param_1;
  }
  else {
    plVar3 = &local_28;
  }
  *param_2 = *plVar3;
  param_2[1] = plVar3[1];
  return param_2;
}


// ==== FUN_1400309b0 @ 1400309b0  undefined8 * FUN_1400309b0(undefined8 * param_1, undefined8 * param_2, uint * param_3)

undefined8 * FUN_1400309b0(undefined8 *param_1,undefined8 *param_2,uint *param_3)

{
  FUN_140030480(param_1,param_2,param_3);
  return param_2;
}


// ==== FUN_1400309d0 @ 1400309d0  longlong * FUN_1400309d0(longlong * param_1, longlong * param_2, uint * param_3)

longlong * FUN_1400309d0(longlong *param_1,longlong *param_2,uint *param_3)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *plVar4;
  longlong *plVar5;
  longlong *plVar6;
  bool bVar7;
  longlong local_38;
  longlong *local_30;
  
  plVar6 = (longlong *)param_1[6];
  bVar7 = true;
  if (*(char *)(plVar6[1] + 0x29) == '\0') {
    plVar5 = (longlong *)plVar6[1];
    do {
      plVar6 = plVar5;
      bVar7 = *param_3 < *(uint *)(plVar6 + 3);
      if (bVar7) {
        plVar5 = (longlong *)*plVar6;
      }
      else {
        plVar5 = (longlong *)plVar6[2];
      }
    } while (*(char *)((longlong)plVar5 + 0x29) == '\0');
  }
  lVar2 = *param_1;
  plVar5 = plVar6;
  local_38 = lVar2;
  plVar4 = plVar6;
  if (bVar7 == false) {
LAB_140030b2d:
    local_30 = plVar4;
    if (*param_3 <= *(uint *)(plVar5 + 3)) {
      *(undefined1 *)(param_2 + 2) = 0;
      *param_2 = local_38;
      goto LAB_140030b5c;
    }
  }
  else {
    plVar5 = *(longlong **)param_1[6];
    local_30 = plVar6;
    if (lVar2 == 0) {
      _invalid_parameter_noinfo();
    }
    if (plVar6 != plVar5) {
      if (lVar2 == 0) {
        _invalid_parameter_noinfo();
      }
      if (*(char *)((longlong)plVar6 + 0x29) == '\0') {
        plVar5 = (longlong *)*plVar6;
        if (*(char *)((longlong)plVar5 + 0x29) == '\0') {
          cVar1 = *(char *)(plVar5[2] + 0x29);
          plVar3 = (longlong *)plVar5[2];
          while (plVar4 = plVar5, cVar1 == '\0') {
            cVar1 = *(char *)(plVar3[2] + 0x29);
            plVar5 = plVar3;
            plVar3 = (longlong *)plVar3[2];
          }
        }
        else {
          cVar1 = *(char *)(plVar6[1] + 0x29);
          plVar4 = (longlong *)plVar6[1];
          plVar3 = plVar6;
          while ((plVar5 = plVar4, cVar1 == '\0' && (plVar3 == (longlong *)*plVar5))) {
            cVar1 = *(char *)(plVar5[1] + 0x29);
            plVar4 = (longlong *)plVar5[1];
            plVar3 = plVar5;
            local_30 = plVar5;
          }
          plVar4 = plVar5;
          if (*(char *)((longlong)plVar3 + 0x29) != '\0') {
            _invalid_parameter_noinfo();
            plVar5 = plVar3;
            plVar4 = local_30;
          }
        }
      }
      else {
        plVar5 = (longlong *)plVar6[2];
        plVar4 = plVar5;
        if (*(char *)((longlong)plVar5 + 0x29) != '\0') {
          local_30 = plVar5;
          _invalid_parameter_noinfo();
          plVar4 = local_30;
        }
      }
      goto LAB_140030b2d;
    }
    bVar7 = true;
  }
  plVar6 = FUN_140030560(param_1,&local_38,bVar7,plVar6,(undefined8 *)param_3);
  *(undefined1 *)(param_2 + 2) = 1;
  local_30 = (longlong *)plVar6[1];
  *param_2 = *plVar6;
LAB_140030b5c:
  param_2[1] = (longlong)local_30;
  return param_2;
}


// ==== FUN_140030b80 @ 140030b80  undefined FUN_140030b80(longlong * param_1, longlong * param_2, longlong * param_3)

void FUN_140030b80(longlong *param_1,longlong *param_2,longlong *param_3)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *plVar4;
  
  while( true ) {
    if ((*param_1 == 0) || (*param_1 != *param_2)) {
      _invalid_parameter_noinfo();
    }
    if (param_1[1] == param_2[1]) break;
    *param_3 = *param_3 + 1;
    if (*param_1 == 0) {
      _invalid_parameter_noinfo();
    }
    lVar2 = param_1[1];
    if (*(char *)(lVar2 + 0x29) == '\0') {
      plVar3 = *(longlong **)(lVar2 + 0x10);
      if (*(char *)((longlong)plVar3 + 0x29) == '\0') {
        cVar1 = *(char *)(*plVar3 + 0x29);
        plVar4 = (longlong *)*plVar3;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar4 + 0x29);
          plVar3 = plVar4;
          plVar4 = (longlong *)*plVar4;
        }
        param_1[1] = (longlong)plVar3;
      }
      else {
        lVar2 = *(longlong *)(lVar2 + 8);
        cVar1 = *(char *)(lVar2 + 0x29);
        while ((cVar1 == '\0' && (param_1[1] == *(longlong *)(lVar2 + 0x10)))) {
          param_1[1] = lVar2;
          lVar2 = *(longlong *)(lVar2 + 8);
          cVar1 = *(char *)(lVar2 + 0x29);
        }
        param_1[1] = lVar2;
      }
    }
    else {
      _invalid_parameter_noinfo();
    }
  }
  return;
}


// ==== FUN_140030dd0 @ 140030dd0  longlong * FUN_140030dd0(longlong * param_1, longlong * param_2, longlong * param_3, uint * param_4)

longlong * FUN_140030dd0(longlong *param_1,longlong *param_2,longlong *param_3,uint *param_4)

{
  char cVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  uint uVar8;
  longlong *plVar9;
  longlong local_38;
  longlong *local_30;
  
  if (param_1[7] == 0) {
    FUN_140030560(param_1,param_2,'\x01',(undefined8 *)param_1[6],(undefined8 *)param_4);
  }
  else {
    puVar2 = *(undefined8 **)param_1[6];
    if ((*param_3 == 0) || (*param_3 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    puVar3 = (undefined8 *)param_3[1];
    if (puVar3 == puVar2) {
      if (*param_4 < *(uint *)(puVar3 + 3)) {
        FUN_140030560(param_1,param_2,'\x01',puVar3,(undefined8 *)param_4);
        return param_2;
      }
    }
    else {
      lVar4 = param_1[6];
      if ((*param_3 == 0) || (*param_3 != *param_1)) {
        _invalid_parameter_noinfo();
      }
      if (param_3[1] == lVar4) {
        if (*(uint *)(*(undefined8 **)(param_1[6] + 0x10) + 3) < *param_4) {
          FUN_140030560(param_1,param_2,'\0',*(undefined8 **)(param_1[6] + 0x10),
                        (undefined8 *)param_4);
          return param_2;
        }
      }
      else {
        uVar8 = *param_4;
        if (uVar8 < *(uint *)(param_3[1] + 0x18)) {
          local_38 = *param_3;
          local_30 = (longlong *)param_3[1];
          if (local_38 == 0) {
            _invalid_parameter_noinfo();
          }
          if (*(char *)((longlong)local_30 + 0x29) == '\0') {
            plVar7 = (longlong *)*local_30;
            if (*(char *)((longlong)plVar7 + 0x29) == '\0') {
              cVar1 = *(char *)(plVar7[2] + 0x29);
              plVar9 = (longlong *)plVar7[2];
              while (local_30 = plVar7, cVar1 == '\0') {
                cVar1 = *(char *)(plVar9[2] + 0x29);
                plVar7 = plVar9;
                plVar9 = (longlong *)plVar9[2];
              }
            }
            else {
              cVar1 = *(char *)(local_30[1] + 0x29);
              plVar5 = (longlong *)local_30[1];
              plVar9 = local_30;
              while ((plVar7 = plVar5, cVar1 == '\0' && (plVar9 == (longlong *)*plVar7))) {
                cVar1 = *(char *)(plVar7[1] + 0x29);
                plVar5 = (longlong *)plVar7[1];
                plVar9 = plVar7;
              }
              local_30 = plVar7;
              if (*(char *)((longlong)plVar9 + 0x29) != '\0') {
                local_30 = plVar9;
                _invalid_parameter_noinfo();
                plVar7 = plVar9;
              }
            }
          }
          else {
            plVar7 = (longlong *)local_30[2];
            local_30 = plVar7;
            if (*(char *)((longlong)plVar7 + 0x29) != '\0') {
              _invalid_parameter_noinfo();
            }
          }
          uVar8 = *param_4;
          if (*(uint *)(plVar7 + 3) < uVar8) {
            if (*(char *)(plVar7[2] + 0x29) != '\0') {
              FUN_140030560(param_1,param_2,'\0',plVar7,(undefined8 *)param_4);
              return param_2;
            }
            FUN_140030560(param_1,param_2,'\x01',(undefined8 *)param_3[1],(undefined8 *)param_4);
            return param_2;
          }
        }
        if (*(uint *)(param_3[1] + 0x18) < uVar8) {
          local_38 = *param_3;
          plVar7 = (longlong *)param_1[6];
          local_30 = (longlong *)param_3[1];
          lVar4 = *param_1;
          if (local_38 == 0) {
            _invalid_parameter_noinfo();
          }
          plVar9 = local_30;
          if (*(char *)((longlong)local_30 + 0x29) == '\0') {
            plVar9 = (longlong *)local_30[2];
            if (*(char *)((longlong)plVar9 + 0x29) == '\0') {
              cVar1 = *(char *)(*plVar9 + 0x29);
              plVar5 = (longlong *)*plVar9;
              while (cVar1 == '\0') {
                cVar1 = *(char *)(*plVar5 + 0x29);
                plVar9 = plVar5;
                plVar5 = (longlong *)*plVar5;
              }
            }
            else {
              cVar1 = *(char *)(local_30[1] + 0x29);
              plVar6 = (longlong *)local_30[1];
              plVar5 = local_30;
              while ((plVar9 = plVar6, cVar1 == '\0' && (plVar5 == (longlong *)plVar9[2]))) {
                cVar1 = *(char *)(plVar9[1] + 0x29);
                plVar6 = (longlong *)plVar9[1];
                plVar5 = plVar9;
              }
            }
          }
          else {
            _invalid_parameter_noinfo();
          }
          if ((local_38 == 0) || (local_38 != lVar4)) {
            _invalid_parameter_noinfo();
          }
          if ((plVar9 == plVar7) || (*param_4 < *(uint *)(plVar9 + 3))) {
            if (*(char *)(((undefined8 *)param_3[1])[2] + 0x29) != '\0') {
              FUN_140030560(param_1,param_2,'\0',(undefined8 *)param_3[1],(undefined8 *)param_4);
              return param_2;
            }
            FUN_140030560(param_1,param_2,'\x01',plVar9,(undefined8 *)param_4);
            return param_2;
          }
        }
      }
    }
    plVar7 = FUN_1400309d0(param_1,&local_38,param_4);
    *param_2 = *plVar7;
    param_2[1] = plVar7[1];
  }
  return param_2;
}


// ==== FUN_1400310f0 @ 1400310f0  undefined FUN_1400310f0(longlong * param_1)

void FUN_1400310f0(longlong *param_1)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined8 uStack_30;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined1 local_18 [16];
  
  if (((char)param_1[1] != '\0') && (param_1[9] != 0)) {
    (**(code **)(*param_1 + 0x10))(param_1,&local_38);
    while( true ) {
      plVar3 = (longlong *)(**(code **)(*param_1 + 0x18))(param_1,local_18);
      if ((CONCAT44(uStack_34,local_38) == 0) || (CONCAT44(uStack_34,local_38) != *plVar3)) {
        _invalid_parameter_noinfo();
      }
      if (uStack_30 == (longlong *)plVar3[1]) break;
      local_28 = local_38;
      uStack_24 = uStack_34;
      uStack_20 = (undefined4)uStack_30;
      uStack_1c = uStack_30._4_4_;
      plVar3 = (longlong *)(**(code **)(*param_1 + 0x20))(param_1,&local_28);
      (**(code **)(*plVar3 + 0xf0))(plVar3);
      if (CONCAT44(uStack_34,local_38) == 0) {
        _invalid_parameter_noinfo();
      }
      if (*(char *)((longlong)uStack_30 + 0x29) == '\0') {
        plVar3 = (longlong *)uStack_30[2];
        if (*(char *)((longlong)plVar3 + 0x29) == '\0') {
          cVar1 = *(char *)(*plVar3 + 0x29);
          uStack_30 = plVar3;
          plVar3 = (longlong *)*plVar3;
          while (cVar1 == '\0') {
            cVar1 = *(char *)(*plVar3 + 0x29);
            uStack_30 = plVar3;
            plVar3 = (longlong *)*plVar3;
          }
        }
        else {
          cVar1 = *(char *)(uStack_30[1] + 0x29);
          plVar2 = (longlong *)uStack_30[1];
          plVar3 = uStack_30;
          while ((uStack_30 = plVar2, cVar1 == '\0' && (plVar3 == (longlong *)uStack_30[2]))) {
            cVar1 = *(char *)(uStack_30[1] + 0x29);
            plVar2 = (longlong *)uStack_30[1];
            plVar3 = uStack_30;
          }
        }
      }
      else {
        _invalid_parameter_noinfo();
      }
    }
  }
  cVar1 = *(char *)((longlong)*(longlong **)(param_1[8] + 8) + 0x29);
  plVar3 = *(longlong **)(param_1[8] + 8);
  while (cVar1 == '\0') {
    FUN_1400299c0(param_1 + 2,(longlong *)plVar3[2]);
    plVar2 = (longlong *)*plVar3;
    operator_delete(plVar3);
    plVar3 = plVar2;
    cVar1 = *(char *)((longlong)plVar2 + 0x29);
  }
  *(longlong *)(param_1[8] + 8) = param_1[8];
  param_1[9] = 0;
  *(longlong *)param_1[8] = param_1[8];
  *(longlong *)(param_1[8] + 0x10) = param_1[8];
  return;
}


// ==== FUN_140031260 @ 140031260  undefined FUN_140031260(longlong * param_1, longlong * param_2, longlong * param_3)

void FUN_140031260(longlong *param_1,longlong *param_2,longlong *param_3)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  
  lVar2 = *param_2;
  plVar3 = (longlong *)param_2[1];
  lVar4 = *param_1;
  plVar7 = (longlong *)param_1[1];
  while( true ) {
    if ((lVar4 == 0) || (lVar4 != lVar2)) {
      _invalid_parameter_noinfo();
    }
    if (plVar7 == plVar3) break;
    *param_3 = *param_3 + 1;
    if (lVar4 == 0) {
      _invalid_parameter_noinfo();
    }
    if (*(char *)((longlong)plVar7 + 0x29) == '\0') {
      plVar5 = (longlong *)plVar7[2];
      if (*(char *)((longlong)plVar5 + 0x29) == '\0') {
        cVar1 = *(char *)(*plVar5 + 0x29);
        plVar7 = plVar5;
        plVar5 = (longlong *)*plVar5;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar5 + 0x29);
          plVar7 = plVar5;
          plVar5 = (longlong *)*plVar5;
        }
      }
      else {
        cVar1 = *(char *)(plVar7[1] + 0x29);
        plVar6 = (longlong *)plVar7[1];
        plVar5 = plVar7;
        while ((plVar7 = plVar6, cVar1 == '\0' && (plVar5 == (longlong *)plVar7[2]))) {
          cVar1 = *(char *)(plVar7[1] + 0x29);
          plVar6 = (longlong *)plVar7[1];
          plVar5 = plVar7;
        }
      }
    }
    else {
      _invalid_parameter_noinfo();
    }
  }
  return;
}


// ==== FUN_140031350 @ 140031350  undefined8 * FUN_140031350(longlong * param_1, uint * param_2)

undefined8 * FUN_140031350(longlong *param_1,uint *param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong lVar5;
  longlong *plVar6;
  uint local_48 [2];
  undefined8 local_40;
  longlong *local_38;
  undefined8 *puStack_30;
  longlong local_28 [2];
  
  puVar4 = (undefined8 *)param_1[6];
  if (*(char *)((longlong)puVar4[1] + 0x29) == '\0') {
    puVar1 = (undefined8 *)puVar4[1];
    do {
      if (*(uint *)(puVar1 + 3) < *param_2) {
        puVar2 = (undefined8 *)puVar1[2];
      }
      else {
        puVar2 = (undefined8 *)*puVar1;
        puVar4 = puVar1;
      }
      puVar1 = puVar2;
    } while (*(char *)((longlong)puVar2 + 0x29) == '\0');
  }
  plVar6 = (longlong *)*param_1;
  puVar1 = (undefined8 *)param_1[6];
  if (plVar6 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  lVar5 = 0;
  if ((puVar4 == puVar1) || (*param_2 < *(uint *)(puVar4 + 3))) {
    local_48[0] = *param_2;
    local_40 = 0;
    local_38 = plVar6;
    puStack_30 = puVar4;
    plVar3 = FUN_140030dd0(param_1,local_28,(longlong *)&local_38,local_48);
    plVar6 = (longlong *)*plVar3;
    puVar4 = (undefined8 *)plVar3[1];
  }
  if (plVar6 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  else {
    lVar5 = *plVar6;
  }
  if (puVar4 == *(undefined8 **)(lVar5 + 0x30)) {
    _invalid_parameter_noinfo();
  }
  return puVar4 + 4;
}


// ==== FUN_140031450 @ 140031450  longlong FUN_140031450(longlong * param_1, uint * param_2)

longlong FUN_140031450(longlong *param_1,uint *param_2)

{
  char cVar1;
  longlong *plVar2;
  longlong lVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong *plVar7;
  longlong lVar8;
  longlong local_58;
  longlong *local_50;
  longlong local_48;
  longlong *local_40;
  longlong local_38;
  longlong *local_30;
  longlong local_28;
  longlong *local_20;
  
  FUN_140030480(param_1,&local_38,param_2);
  plVar5 = local_20;
  lVar4 = local_28;
  lVar3 = local_38;
  lVar8 = 0;
  local_58 = local_38;
  local_50 = local_30;
  plVar7 = local_30;
  while( true ) {
    if ((lVar3 == 0) || (lVar3 != lVar4)) {
      _invalid_parameter_noinfo();
    }
    if (plVar7 == plVar5) break;
    lVar8 = lVar8 + 1;
    if (lVar3 == 0) {
      _invalid_parameter_noinfo();
    }
    if (*(char *)((longlong)plVar7 + 0x29) == '\0') {
      plVar2 = (longlong *)plVar7[2];
      if (*(char *)((longlong)plVar2 + 0x29) == '\0') {
        cVar1 = *(char *)(*plVar2 + 0x29);
        plVar7 = plVar2;
        plVar2 = (longlong *)*plVar2;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar2 + 0x29);
          plVar7 = plVar2;
          plVar2 = (longlong *)*plVar2;
        }
      }
      else {
        cVar1 = *(char *)(plVar7[1] + 0x29);
        plVar6 = (longlong *)plVar7[1];
        plVar2 = plVar7;
        while ((plVar7 = plVar6, cVar1 == '\0' && (plVar2 == (longlong *)plVar7[2]))) {
          cVar1 = *(char *)(plVar7[1] + 0x29);
          plVar6 = (longlong *)plVar7[1];
          plVar2 = plVar7;
        }
      }
    }
    else {
      _invalid_parameter_noinfo();
    }
  }
  local_58 = local_28;
  local_50 = local_20;
  local_48 = local_38;
  local_40 = local_30;
  FUN_14002add0(param_1,&local_38,&local_48,&local_58);
  return lVar8;
}


// ==== FUN_140031780 @ 140031780  undefined FUN_140031780(longlong * param_1)

void FUN_140031780(longlong *param_1)

{
  *param_1 = (longlong)CSingleMap<class_INpc>::vftable;
  FUN_1400310f0(param_1);
  FUN_14002d9a0(param_1 + 2);
  operator_delete((void *)param_1[2]);
  *param_1 = (longlong)ISingleMap<class_INpc>::vftable;
  return;
}


// ==== FUN_1400318c0 @ 1400318c0  undefined FUN_1400318c0(undefined8 param_1, longlong param_2)

void FUN_1400318c0(undefined8 param_1,longlong param_2)

{
  if (*(void **)(param_2 + 0x38) != (void *)0x0) {
    operator_delete(*(void **)(param_2 + 0x38));
  }
  *(undefined8 *)(param_2 + 0x38) = 0;
  *(undefined8 *)(param_2 + 0x40) = 0;
  *(undefined8 *)(param_2 + 0x48) = 0;
  operator_delete(*(void **)(param_2 + 0x20));
  return;
}


// ==== FUN_140031910 @ 140031910  undefined FUN_140031910(undefined8 param_1, longlong * param_2, undefined8 param_3, undefined8 param_4)

void FUN_140031910(undefined8 param_1,longlong *param_2,undefined8 param_3,undefined8 param_4)

{
  char cVar1;
  longlong *plVar2;
  
  cVar1 = *(char *)((longlong)param_2 + 0x51);
  while (cVar1 == '\0') {
    FUN_140031910(param_1,(longlong *)param_2[2],param_3,param_4);
    plVar2 = (longlong *)*param_2;
    if ((void *)param_2[7] != (void *)0x0) {
      operator_delete((void *)param_2[7]);
    }
    param_2[7] = 0;
    param_2[8] = 0;
    param_2[9] = 0;
    operator_delete((void *)param_2[4]);
    operator_delete(param_2);
    param_2 = plVar2;
    cVar1 = *(char *)((longlong)plVar2 + 0x51);
  }
  return;
}


// ==== FUN_140031b60 @ 140031b60  longlong * FUN_140031b60(longlong * param_1, longlong * param_2, uint * param_3)

longlong * FUN_140031b60(longlong *param_1,longlong *param_2,uint *param_3)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *plVar4;
  longlong *plVar5;
  longlong *plVar6;
  bool bVar7;
  longlong local_38;
  longlong *local_30;
  
  plVar6 = (longlong *)param_1[6];
  bVar7 = true;
  if (*(char *)(plVar6[1] + 0x51) == '\0') {
    plVar5 = (longlong *)plVar6[1];
    do {
      plVar6 = plVar5;
      bVar7 = *param_3 < *(uint *)(plVar6 + 3);
      if (bVar7) {
        plVar5 = (longlong *)*plVar6;
      }
      else {
        plVar5 = (longlong *)plVar6[2];
      }
    } while (*(char *)((longlong)plVar5 + 0x51) == '\0');
  }
  lVar2 = *param_1;
  plVar5 = plVar6;
  local_38 = lVar2;
  plVar4 = plVar6;
  if (bVar7 == false) {
LAB_140031cbd:
    local_30 = plVar4;
    if (*param_3 <= *(uint *)(plVar5 + 3)) {
      *(undefined1 *)(param_2 + 2) = 0;
      *param_2 = local_38;
      goto LAB_140031cec;
    }
  }
  else {
    plVar5 = *(longlong **)param_1[6];
    local_30 = plVar6;
    if (lVar2 == 0) {
      _invalid_parameter_noinfo();
    }
    if (plVar6 != plVar5) {
      if (lVar2 == 0) {
        _invalid_parameter_noinfo();
      }
      if (*(char *)((longlong)plVar6 + 0x51) == '\0') {
        plVar5 = (longlong *)*plVar6;
        if (*(char *)((longlong)plVar5 + 0x51) == '\0') {
          cVar1 = *(char *)(plVar5[2] + 0x51);
          plVar3 = (longlong *)plVar5[2];
          while (plVar4 = plVar5, cVar1 == '\0') {
            cVar1 = *(char *)(plVar3[2] + 0x51);
            plVar5 = plVar3;
            plVar3 = (longlong *)plVar3[2];
          }
        }
        else {
          cVar1 = *(char *)(plVar6[1] + 0x51);
          plVar4 = (longlong *)plVar6[1];
          plVar3 = plVar6;
          while ((plVar5 = plVar4, cVar1 == '\0' && (plVar3 == (longlong *)*plVar5))) {
            cVar1 = *(char *)(plVar5[1] + 0x51);
            plVar4 = (longlong *)plVar5[1];
            plVar3 = plVar5;
            local_30 = plVar5;
          }
          plVar4 = plVar5;
          if (*(char *)((longlong)plVar3 + 0x51) != '\0') {
            _invalid_parameter_noinfo();
            plVar5 = plVar3;
            plVar4 = local_30;
          }
        }
      }
      else {
        plVar5 = (longlong *)plVar6[2];
        plVar4 = plVar5;
        if (*(char *)((longlong)plVar5 + 0x51) != '\0') {
          local_30 = plVar5;
          _invalid_parameter_noinfo();
          plVar4 = local_30;
        }
      }
      goto LAB_140031cbd;
    }
    bVar7 = true;
  }
  plVar6 = FUN_14002f9e0(param_1,&local_38,bVar7,plVar6,param_3);
  *(undefined1 *)(param_2 + 2) = 1;
  local_30 = (longlong *)plVar6[1];
  *param_2 = *plVar6;
LAB_140031cec:
  param_2[1] = (longlong)local_30;
  return param_2;
}


// ==== FUN_140031d10 @ 140031d10  longlong * FUN_140031d10(longlong * param_1, longlong * param_2, uint * param_3)

longlong * FUN_140031d10(longlong *param_1,longlong *param_2,uint *param_3)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *plVar4;
  longlong *plVar5;
  longlong *plVar6;
  bool bVar7;
  longlong local_38;
  longlong *local_30;
  
  plVar6 = (longlong *)param_1[6];
  bVar7 = true;
  if (*(char *)(plVar6[1] + 0x51) == '\0') {
    plVar5 = (longlong *)plVar6[1];
    do {
      plVar6 = plVar5;
      bVar7 = *param_3 < *(uint *)(plVar6 + 3);
      if (bVar7) {
        plVar5 = (longlong *)*plVar6;
      }
      else {
        plVar5 = (longlong *)plVar6[2];
      }
    } while (*(char *)((longlong)plVar5 + 0x51) == '\0');
  }
  lVar2 = *param_1;
  plVar5 = plVar6;
  local_38 = lVar2;
  plVar4 = plVar6;
  if (bVar7 == false) {
LAB_140031e6d:
    local_30 = plVar4;
    if (*param_3 <= *(uint *)(plVar5 + 3)) {
      *(undefined1 *)(param_2 + 2) = 0;
      *param_2 = local_38;
      goto LAB_140031e9c;
    }
  }
  else {
    plVar5 = *(longlong **)param_1[6];
    local_30 = plVar6;
    if (lVar2 == 0) {
      _invalid_parameter_noinfo();
    }
    if (plVar6 != plVar5) {
      if (lVar2 == 0) {
        _invalid_parameter_noinfo();
      }
      if (*(char *)((longlong)plVar6 + 0x51) == '\0') {
        plVar5 = (longlong *)*plVar6;
        if (*(char *)((longlong)plVar5 + 0x51) == '\0') {
          cVar1 = *(char *)(plVar5[2] + 0x51);
          plVar3 = (longlong *)plVar5[2];
          while (plVar4 = plVar5, cVar1 == '\0') {
            cVar1 = *(char *)(plVar3[2] + 0x51);
            plVar5 = plVar3;
            plVar3 = (longlong *)plVar3[2];
          }
        }
        else {
          cVar1 = *(char *)(plVar6[1] + 0x51);
          plVar4 = (longlong *)plVar6[1];
          plVar3 = plVar6;
          while ((plVar5 = plVar4, cVar1 == '\0' && (plVar3 == (longlong *)*plVar5))) {
            cVar1 = *(char *)(plVar5[1] + 0x51);
            plVar4 = (longlong *)plVar5[1];
            plVar3 = plVar5;
            local_30 = plVar5;
          }
          plVar4 = plVar5;
          if (*(char *)((longlong)plVar3 + 0x51) != '\0') {
            _invalid_parameter_noinfo();
            plVar5 = plVar3;
            plVar4 = local_30;
          }
        }
      }
      else {
        plVar5 = (longlong *)plVar6[2];
        plVar4 = plVar5;
        if (*(char *)((longlong)plVar5 + 0x51) != '\0') {
          local_30 = plVar5;
          _invalid_parameter_noinfo();
          plVar4 = local_30;
        }
      }
      goto LAB_140031e6d;
    }
    bVar7 = true;
  }
  plVar6 = FUN_14002fd20(param_1,&local_38,bVar7,plVar6,param_3);
  *(undefined1 *)(param_2 + 2) = 1;
  local_30 = (longlong *)plVar6[1];
  *param_2 = *plVar6;
LAB_140031e9c:
  param_2[1] = (longlong)local_30;
  return param_2;
}


// ==== FUN_140031ec0 @ 140031ec0  undefined8 * FUN_140031ec0(undefined8 * param_1, undefined8 * param_2, longlong * param_3)

undefined8 * FUN_140031ec0(undefined8 *param_1,undefined8 *param_2,longlong *param_3)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong lVar5;
  longlong *plVar6;
  longlong *plVar7;
  longlong *plVar8;
  longlong *plVar9;
  undefined **local_80 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_68 [40];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_40 [40];
  
  plVar2 = (longlong *)param_3[1];
  if (*(char *)((longlong)plVar2 + 0x51) != '\0') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_40,"invalid map/set<T> iterator");
    std::exception::exception((exception *)local_80);
    local_80[0] = std::logic_error::vftable;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_68,local_40);
    local_80[0] = std::out_of_range::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_80,(ThrowInfo *)&DAT_1400feda0);
  }
  FUN_140026930(param_3);
  plVar8 = (longlong *)*plVar2;
  if (*(char *)((longlong)plVar8 + 0x51) == '\0') {
    plVar9 = plVar8;
    if (*(char *)(plVar2[2] + 0x51) == '\0') {
      plVar7 = (longlong *)param_3[1];
      plVar9 = (longlong *)plVar7[2];
      if (plVar7 != plVar2) {
        plVar8[1] = (longlong)plVar7;
        *plVar7 = *plVar2;
        plVar8 = plVar7;
        if (plVar7 != (longlong *)plVar2[2]) {
          plVar8 = (longlong *)plVar7[1];
          if (*(char *)((longlong)plVar9 + 0x51) == '\0') {
            plVar9[1] = (longlong)plVar8;
          }
          *plVar8 = (longlong)plVar9;
          plVar7[2] = plVar2[2];
          *(longlong **)(plVar2[2] + 8) = plVar7;
        }
        if (*(longlong **)(param_1[6] + 8) == plVar2) {
          *(longlong **)(param_1[6] + 8) = plVar7;
        }
        else {
          puVar4 = (undefined8 *)plVar2[1];
          if ((longlong *)*puVar4 == plVar2) {
            *puVar4 = plVar7;
          }
          else {
            puVar4[2] = plVar7;
          }
        }
        plVar7[1] = plVar2[1];
        plVar3 = plVar2 + 10;
        plVar7 = plVar7 + 10;
        if (plVar7 != plVar3) {
          lVar5 = *plVar7;
          *(char *)plVar7 = (char)*plVar3;
          *(char *)plVar3 = (char)lVar5;
        }
        goto LAB_1400320ac;
      }
    }
  }
  else {
    plVar9 = (longlong *)plVar2[2];
  }
  plVar8 = (longlong *)plVar2[1];
  if (*(char *)((longlong)plVar9 + 0x51) == '\0') {
    plVar9[1] = (longlong)plVar8;
  }
  if (*(longlong **)(param_1[6] + 8) == plVar2) {
    *(longlong **)(param_1[6] + 8) = plVar9;
  }
  else if ((longlong *)*plVar8 == plVar2) {
    *plVar8 = (longlong)plVar9;
  }
  else {
    plVar8[2] = (longlong)plVar9;
  }
  if (*(longlong **)param_1[6] == plVar2) {
    plVar7 = plVar8;
    if (*(char *)((longlong)plVar9 + 0x51) == '\0') {
      cVar1 = *(char *)(*plVar9 + 0x51);
      plVar3 = (longlong *)*plVar9;
      plVar7 = plVar9;
      while (plVar6 = plVar3, cVar1 == '\0') {
        plVar3 = (longlong *)*plVar6;
        cVar1 = *(char *)((longlong)plVar3 + 0x51);
        plVar7 = plVar6;
      }
    }
    *(longlong **)param_1[6] = plVar7;
  }
  if (*(longlong **)(param_1[6] + 0x10) == plVar2) {
    plVar7 = plVar8;
    if (*(char *)((longlong)plVar9 + 0x51) == '\0') {
      cVar1 = *(char *)(plVar9[2] + 0x51);
      plVar3 = (longlong *)plVar9[2];
      plVar7 = plVar9;
      while (plVar6 = plVar3, cVar1 == '\0') {
        plVar3 = (longlong *)plVar6[2];
        cVar1 = *(char *)((longlong)plVar3 + 0x51);
        plVar7 = plVar6;
      }
    }
    *(longlong **)(param_1[6] + 0x10) = plVar7;
  }
LAB_1400320ac:
  if ((char)plVar2[10] == '\x01') {
    if (plVar9 != *(longlong **)(param_1[6] + 8)) {
      do {
        plVar7 = plVar8;
        if ((char)plVar9[10] != '\x01') break;
        plVar8 = (longlong *)*plVar7;
        if (plVar9 == plVar8) {
          plVar8 = (longlong *)plVar7[2];
          if ((char)plVar8[10] == '\0') {
            *(undefined1 *)(plVar8 + 10) = 1;
            *(undefined1 *)(plVar7 + 10) = 0;
            FUN_140027cc0((longlong)param_1,(longlong)plVar7);
            plVar8 = (longlong *)plVar7[2];
          }
          if (*(char *)((longlong)plVar8 + 0x51) == '\0') {
            if ((*(char *)(*plVar8 + 0x50) != '\x01') || (*(char *)(plVar8[2] + 0x50) != '\x01')) {
              if (*(char *)(plVar8[2] + 0x50) == '\x01') {
                *(undefined1 *)(*plVar8 + 0x50) = 1;
                *(undefined1 *)(plVar8 + 10) = 0;
                FUN_1400264e0((longlong)param_1,plVar8);
                plVar8 = (longlong *)plVar7[2];
              }
              *(char *)(plVar8 + 10) = (char)plVar7[10];
              *(undefined1 *)(plVar7 + 10) = 1;
              *(undefined1 *)(plVar8[2] + 0x50) = 1;
              FUN_140027cc0((longlong)param_1,(longlong)plVar7);
              break;
            }
            *(undefined1 *)(plVar8 + 10) = 0;
          }
        }
        else {
          if ((char)plVar8[10] == '\0') {
            *(undefined1 *)(plVar8 + 10) = 1;
            *(undefined1 *)(plVar7 + 10) = 0;
            FUN_1400264e0((longlong)param_1,plVar7);
            plVar8 = (longlong *)*plVar7;
          }
          if (*(char *)((longlong)plVar8 + 0x51) == '\0') {
            if ((*(char *)(plVar8[2] + 0x50) != '\x01') || (*(char *)(*plVar8 + 0x50) != '\x01')) {
              if (*(char *)(*plVar8 + 0x50) == '\x01') {
                *(undefined1 *)(plVar8[2] + 0x50) = 1;
                *(undefined1 *)(plVar8 + 10) = 0;
                FUN_140027cc0((longlong)param_1,(longlong)plVar8);
                plVar8 = (longlong *)*plVar7;
              }
              *(char *)(plVar8 + 10) = (char)plVar7[10];
              *(undefined1 *)(plVar7 + 10) = 1;
              *(undefined1 *)(*plVar8 + 0x50) = 1;
              FUN_1400264e0((longlong)param_1,plVar7);
              break;
            }
            *(undefined1 *)(plVar8 + 10) = 0;
          }
        }
        plVar8 = (longlong *)plVar7[1];
        plVar9 = plVar7;
      } while (plVar7 != *(longlong **)(param_1[6] + 8));
    }
    *(undefined1 *)(plVar9 + 10) = 1;
  }
  if ((void *)plVar2[7] != (void *)0x0) {
    operator_delete((void *)plVar2[7]);
  }
  plVar2[7] = 0;
  plVar2[8] = 0;
  plVar2[9] = 0;
  operator_delete((void *)plVar2[4]);
  operator_delete(plVar2);
  if (param_1[7] != 0) {
    param_1[7] = param_1[7] + -1;
  }
  lVar5 = param_3[1];
  *param_2 = *param_1;
  param_2[1] = lVar5;
  return param_2;
}


// ==== FUN_1400322b0 @ 1400322b0  undefined8 * FUN_1400322b0(undefined1 param_1)

undefined8 * FUN_1400322b0(undefined1 param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x50);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = ISingleMap<class_INpc>::vftable;
    *puVar1 = CSingleMap<class_INpc>::vftable;
    FUN_14002f680(puVar1 + 2);
    *(undefined1 *)(puVar1 + 1) = param_1;
  }
  return puVar1;
}


// ==== FUN_140032320 @ 140032320  undefined8 * FUN_140032320(undefined8 * param_1, undefined8 * param_2, longlong * param_3)

undefined8 * FUN_140032320(undefined8 *param_1,undefined8 *param_2,longlong *param_3)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong lVar5;
  longlong *plVar6;
  longlong *plVar7;
  longlong *plVar8;
  longlong *plVar9;
  undefined **local_80 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_68 [40];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_40 [40];
  
  plVar2 = (longlong *)param_3[1];
  if (*(char *)((longlong)plVar2 + 0x51) != '\0') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_40,"invalid map/set<T> iterator");
    std::exception::exception((exception *)local_80);
    local_80[0] = std::logic_error::vftable;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_68,local_40);
    local_80[0] = std::out_of_range::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_80,(ThrowInfo *)&DAT_1400feda0);
  }
  FUN_140028040(param_3);
  plVar8 = (longlong *)*plVar2;
  if (*(char *)((longlong)plVar8 + 0x51) == '\0') {
    plVar9 = plVar8;
    if (*(char *)(plVar2[2] + 0x51) == '\0') {
      plVar7 = (longlong *)param_3[1];
      plVar9 = (longlong *)plVar7[2];
      if (plVar7 != plVar2) {
        plVar8[1] = (longlong)plVar7;
        *plVar7 = *plVar2;
        plVar8 = plVar7;
        if (plVar7 != (longlong *)plVar2[2]) {
          plVar8 = (longlong *)plVar7[1];
          if (*(char *)((longlong)plVar9 + 0x51) == '\0') {
            plVar9[1] = (longlong)plVar8;
          }
          *plVar8 = (longlong)plVar9;
          plVar7[2] = plVar2[2];
          *(longlong **)(plVar2[2] + 8) = plVar7;
        }
        if (*(longlong **)(param_1[6] + 8) == plVar2) {
          *(longlong **)(param_1[6] + 8) = plVar7;
        }
        else {
          puVar4 = (undefined8 *)plVar2[1];
          if ((longlong *)*puVar4 == plVar2) {
            *puVar4 = plVar7;
          }
          else {
            puVar4[2] = plVar7;
          }
        }
        plVar7[1] = plVar2[1];
        plVar3 = plVar2 + 10;
        plVar7 = plVar7 + 10;
        if (plVar7 != plVar3) {
          lVar5 = *plVar7;
          *(char *)plVar7 = (char)*plVar3;
          *(char *)plVar3 = (char)lVar5;
        }
        goto LAB_14003250c;
      }
    }
  }
  else {
    plVar9 = (longlong *)plVar2[2];
  }
  plVar8 = (longlong *)plVar2[1];
  if (*(char *)((longlong)plVar9 + 0x51) == '\0') {
    plVar9[1] = (longlong)plVar8;
  }
  if (*(longlong **)(param_1[6] + 8) == plVar2) {
    *(longlong **)(param_1[6] + 8) = plVar9;
  }
  else if ((longlong *)*plVar8 == plVar2) {
    *plVar8 = (longlong)plVar9;
  }
  else {
    plVar8[2] = (longlong)plVar9;
  }
  if (*(longlong **)param_1[6] == plVar2) {
    plVar7 = plVar8;
    if (*(char *)((longlong)plVar9 + 0x51) == '\0') {
      cVar1 = *(char *)(*plVar9 + 0x51);
      plVar3 = (longlong *)*plVar9;
      plVar7 = plVar9;
      while (plVar6 = plVar3, cVar1 == '\0') {
        plVar3 = (longlong *)*plVar6;
        cVar1 = *(char *)((longlong)plVar3 + 0x51);
        plVar7 = plVar6;
      }
    }
    *(longlong **)param_1[6] = plVar7;
  }
  if (*(longlong **)(param_1[6] + 0x10) == plVar2) {
    plVar7 = plVar8;
    if (*(char *)((longlong)plVar9 + 0x51) == '\0') {
      cVar1 = *(char *)(plVar9[2] + 0x51);
      plVar3 = (longlong *)plVar9[2];
      plVar7 = plVar9;
      while (plVar6 = plVar3, cVar1 == '\0') {
        plVar3 = (longlong *)plVar6[2];
        cVar1 = *(char *)((longlong)plVar3 + 0x51);
        plVar7 = plVar6;
      }
    }
    *(longlong **)(param_1[6] + 0x10) = plVar7;
  }
LAB_14003250c:
  if ((char)plVar2[10] == '\x01') {
    if (plVar9 != *(longlong **)(param_1[6] + 8)) {
      do {
        plVar7 = plVar8;
        if ((char)plVar9[10] != '\x01') break;
        plVar8 = (longlong *)*plVar7;
        if (plVar9 == plVar8) {
          plVar8 = (longlong *)plVar7[2];
          if ((char)plVar8[10] == '\0') {
            *(undefined1 *)(plVar8 + 10) = 1;
            *(undefined1 *)(plVar7 + 10) = 0;
            FUN_140027ee0((longlong)param_1,(longlong)plVar7);
            plVar8 = (longlong *)plVar7[2];
          }
          if (*(char *)((longlong)plVar8 + 0x51) == '\0') {
            if ((*(char *)(*plVar8 + 0x50) != '\x01') || (*(char *)(plVar8[2] + 0x50) != '\x01')) {
              if (*(char *)(plVar8[2] + 0x50) == '\x01') {
                *(undefined1 *)(*plVar8 + 0x50) = 1;
                *(undefined1 *)(plVar8 + 10) = 0;
                FUN_140027f40((longlong)param_1,plVar8);
                plVar8 = (longlong *)plVar7[2];
              }
              *(char *)(plVar8 + 10) = (char)plVar7[10];
              *(undefined1 *)(plVar7 + 10) = 1;
              *(undefined1 *)(plVar8[2] + 0x50) = 1;
              FUN_140027ee0((longlong)param_1,(longlong)plVar7);
              break;
            }
            *(undefined1 *)(plVar8 + 10) = 0;
          }
        }
        else {
          if ((char)plVar8[10] == '\0') {
            *(undefined1 *)(plVar8 + 10) = 1;
            *(undefined1 *)(plVar7 + 10) = 0;
            FUN_140027f40((longlong)param_1,plVar7);
            plVar8 = (longlong *)*plVar7;
          }
          if (*(char *)((longlong)plVar8 + 0x51) == '\0') {
            if ((*(char *)(plVar8[2] + 0x50) != '\x01') || (*(char *)(*plVar8 + 0x50) != '\x01')) {
              if (*(char *)(*plVar8 + 0x50) == '\x01') {
                *(undefined1 *)(plVar8[2] + 0x50) = 1;
                *(undefined1 *)(plVar8 + 10) = 0;
                FUN_140027ee0((longlong)param_1,(longlong)plVar8);
                plVar8 = (longlong *)*plVar7;
              }
              *(char *)(plVar8 + 10) = (char)plVar7[10];
              *(undefined1 *)(plVar7 + 10) = 1;
              *(undefined1 *)(*plVar8 + 0x50) = 1;
              FUN_140027f40((longlong)param_1,plVar7);
              break;
            }
            *(undefined1 *)(plVar8 + 10) = 0;
          }
        }
        plVar8 = (longlong *)plVar7[1];
        plVar9 = plVar7;
      } while (plVar7 != *(longlong **)(param_1[6] + 8));
    }
    *(undefined1 *)(plVar9 + 10) = 1;
  }
  if ((void *)plVar2[7] != (void *)0x0) {
    operator_delete((void *)plVar2[7]);
  }
  plVar2[7] = 0;
  plVar2[8] = 0;
  plVar2[9] = 0;
  operator_delete((void *)plVar2[4]);
  operator_delete(plVar2);
  if (param_1[7] != 0) {
    param_1[7] = param_1[7] + -1;
  }
  lVar5 = param_3[1];
  *param_2 = *param_1;
  param_2[1] = lVar5;
  return param_2;
}


// ==== FUN_140032710 @ 140032710  undefined FUN_140032710(longlong param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_140032710(longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  FUN_140031910(param_1,*(longlong **)(*(longlong *)(param_1 + 0x30) + 8),param_3,param_4);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)*(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x30);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 0x10) = *(longlong *)(param_1 + 0x30);
  return;
}


// ==== FUN_140032750 @ 140032750  undefined FUN_140032750(undefined8 param_1, longlong * param_2, undefined8 param_3, undefined8 param_4)

void FUN_140032750(undefined8 param_1,longlong *param_2,undefined8 param_3,undefined8 param_4)

{
  char cVar1;
  longlong *plVar2;
  
  cVar1 = *(char *)((longlong)param_2 + 0x51);
  while (cVar1 == '\0') {
    FUN_140032750(param_1,(longlong *)param_2[2],param_3,param_4);
    plVar2 = (longlong *)*param_2;
    if ((void *)param_2[7] != (void *)0x0) {
      operator_delete((void *)param_2[7]);
    }
    param_2[7] = 0;
    param_2[8] = 0;
    param_2[9] = 0;
    operator_delete((void *)param_2[4]);
    operator_delete(param_2);
    param_2 = plVar2;
    cVar1 = *(char *)((longlong)plVar2 + 0x51);
  }
  return;
}


// ==== FUN_140032800 @ 140032800  longlong * FUN_140032800(longlong param_1)

/* WARNING: Removing unreachable block (ram,0x000140032a63) */
/* WARNING: Removing unreachable block (ram,0x000140032a83) */
/* WARNING: Removing unreachable block (ram,0x000140032a9c) */
/* WARNING: Removing unreachable block (ram,0x000140032ad0) */
/* WARNING: Removing unreachable block (ram,0x000140032ad5) */
/* WARNING: Removing unreachable block (ram,0x000140032ae0) */
/* WARNING: Removing unreachable block (ram,0x000140032ae5) */
/* WARNING: Removing unreachable block (ram,0x000140032aea) */
/* WARNING: Removing unreachable block (ram,0x000140032af0) */

longlong * FUN_140032800(longlong param_1)

{
  bool bVar1;
  void **ppvVar2;
  void *pvVar3;
  longlong *plVar4;
  longlong lVar5;
  bool bVar6;
  bool bVar7;
  int iVar8;
  uint uVar9;
  undefined4 uVar10;
  ulonglong extraout_RAX;
  ulonglong extraout_RAX_00;
  ulonglong extraout_RAX_01;
  ulonglong extraout_RAX_02;
  longlong *plVar11;
  longlong *plVar12;
  longlong *plVar13;
  void *pvVar14;
  ulonglong uVar15;
  undefined8 *puVar16;
  undefined8 uVar17;
  longlong lVar18;
  int iVar19;
  void **local_res10;
  longlong *local_res18;
  void **local_res20;
  void **local_108 [3];
  void *local_f0;
  void *local_e8;
  undefined8 local_e0;
  longlong *local_d8;
  longlong local_d0;
  void **local_c8;
  undefined8 uStack_c0;
  uint local_b8 [2];
  void *local_b0 [3];
  void *local_98;
  undefined8 local_90;
  undefined8 local_88;
  void **local_78;
  undefined8 uStack_70;
  undefined8 local_68;
  longlong local_60 [4];
  
  local_68 = 0xfffffffffffffffe;
  if (*(longlong *)(param_1 + 8) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    plVar11 = (longlong *)(extraout_RAX & 0xffffffffffffff00);
  }
  else if (*(longlong *)(param_1 + 0x10) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    plVar11 = (longlong *)(extraout_RAX_00 & 0xffffffffffffff00);
  }
  else if (*(longlong *)(param_1 + 0x18) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    plVar11 = (longlong *)(extraout_RAX_01 & 0xffffffffffffff00);
  }
  else if (*(longlong *)(param_1 + 0x20) == 0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    plVar11 = (longlong *)(extraout_RAX_02 & 0xffffffffffffff00);
  }
  else {
    plVar11 = (longlong *)InstanceGet();
    plVar11 = (longlong *)
              (**(code **)(*plVar11 + 0x10))
                        (plVar11,"SELECT * FROM cq_generator order by mask desc",2);
    if (plVar11 != (longlong *)0x0) {
      bVar7 = false;
      bVar1 = false;
      iVar19 = 0;
      iVar8 = (**(code **)(*plVar11 + 0x40))(plVar11);
      if (0 < iVar8) {
        do {
          (**(code **)(*plVar11 + 0x30))(plVar11,(longlong)iVar19);
          plVar12 = (longlong *)(**(code **)(*plVar11 + 0x38))(plVar11);
          if (plVar12 == (longlong *)0x0) {
            return (longlong *)0x0;
          }
          local_res18 = plVar12;
          plVar13 = (longlong *)(**(code **)(*plVar12 + 0x10))(plVar12,0x12);
          uVar9 = (**(code **)(*plVar13 + 0x40))(plVar13);
          bVar6 = FUN_14005f730(uVar9,0);
          if (bVar6) {
            plVar13 = (longlong *)(**(code **)(*plVar12 + 0x10))(plVar12,1);
            uVar10 = (**(code **)(*plVar13 + 0x40))(plVar13);
            local_res10 = (void **)CONCAT44(local_res10._4_4_,uVar10);
            plVar13 = (longlong *)(param_1 + 0xa8);
            FUN_14002b870(plVar13,(longlong *)&local_d8,(uint *)&local_res10);
            plVar4 = local_d8;
            lVar18 = *(longlong *)(param_1 + 0xd8);
            if (((longlong *)*plVar13 == (longlong *)0x0) || ((longlong *)*plVar13 != local_d8)) {
              _invalid_parameter_noinfo();
            }
            lVar5 = local_d0;
            bVar7 = bVar1;
            if (lVar18 == local_d0) {
              local_res10 = (void **)operator_new(8);
              if (local_res10 == (void **)0x0) {
                local_108[0] = (void **)0x0;
              }
              else {
                *local_res10 = local_108;
                local_108[0] = local_res10;
              }
              uStack_c0 = 0;
              local_e0 = 0;
              local_e8 = (void *)0x0;
              local_f0 = (void *)0x0;
              uStack_70 = 0;
              local_res20 = local_res10;
              local_c8 = local_108[0];
              local_78 = local_108[0];
              FUN_14002d6f0((longlong)local_108,(longlong)&local_78,1,&local_res18);
              pvVar3 = local_f0;
              if (local_e8 < local_f0) {
                _invalid_parameter_noinfo();
              }
              ppvVar2 = local_108[0];
              if (local_108[0] == (void **)0x0) {
                _invalid_parameter_noinfo();
                pvVar14 = (void *)0x0;
              }
              else {
                pvVar14 = *local_108[0];
              }
              if (*(void **)((longlong)pvVar14 + 0x20) < pvVar3) {
LAB_140032b6b:
                _invalid_parameter_noinfo();
              }
              else {
                if (ppvVar2 == (void **)0x0) {
                  pvVar14 = (void *)0x0;
                }
                else {
                  pvVar14 = *ppvVar2;
                }
                if (pvVar3 < *(void **)((longlong)pvVar14 + 0x18)) goto LAB_140032b6b;
              }
              plVar12 = (longlong *)(**(code **)(*plVar12 + 0x10))(plVar12,1);
              local_b8[0] = (**(code **)(*plVar12 + 0x40))(plVar12);
              FUN_14002d250(local_b0,local_108);
              FUN_140031b60(plVar13,local_60,local_b8);
              local_res10 = local_b0;
              if (local_98 != (void *)0x0) {
                operator_delete(local_98);
              }
              local_98 = (void *)0x0;
              local_90 = 0;
              local_88 = 0;
              operator_delete(local_b0[0]);
              if (local_f0 != (void *)0x0) {
                operator_delete(local_f0);
              }
              local_f0 = (void *)0x0;
              local_e8 = (void *)0x0;
              local_e0 = 0;
              operator_delete(local_108[0]);
            }
            else {
              if (plVar4 == (longlong *)0x0) {
                _invalid_parameter_noinfo();
                lVar18 = 0;
              }
              else {
                lVar18 = *plVar4;
              }
              if (lVar5 == *(longlong *)(lVar18 + 0x30)) {
                _invalid_parameter_noinfo();
              }
              FUN_14002f460((longlong *)(lVar5 + 0x20),&local_res18);
            }
          }
          else {
            plVar13 = FUN_140060e20();
            if (plVar13 == (longlong *)0x0) {
              uVar15 = (**(code **)*plVar11)(plVar11);
              return (longlong *)(uVar15 & 0xffffffffffffff00);
            }
            uVar17 = FUN_140061040(plVar13,plVar12,0);
            if ((char)uVar17 == '\0') {
              bVar7 = true;
              bVar1 = true;
              (**(code **)(*plVar13 + 0xa0))(plVar13);
            }
            else {
              plVar12 = (longlong *)FUN_140025b50(param_1);
              lVar18 = *plVar12;
              uVar17 = FUN_14005f720(plVar13);
              (**(code **)(lVar18 + 0x20))(plVar12,uVar17);
            }
          }
          iVar19 = iVar19 + 1;
          iVar8 = (**(code **)(*plVar11 + 0x40))(plVar11);
        } while (iVar19 < iVar8);
      }
      uVar15 = (**(code **)*plVar11)(plVar11);
      if (bVar7) {
        plVar11 = (longlong *)(uVar15 & 0xffffffffffffff00);
      }
      else {
        plVar11 = (longlong *)InstanceGet();
        plVar11 = (longlong *)
                  (**(code **)(*plVar11 + 0x10))(plVar11,"SELECT * FROM cq_monstertype",2);
        if (plVar11 != (longlong *)0x0) {
          iVar19 = 0;
          iVar8 = (**(code **)(*plVar11 + 0x40))(plVar11);
          if (0 < iVar8) {
            do {
              (**(code **)(*plVar11 + 0x30))(plVar11,(longlong)iVar19);
              puVar16 = (undefined8 *)operator_new(0x18);
              if (puVar16 == (undefined8 *)0x0) {
                puVar16 = (undefined8 *)0x0;
              }
              else {
                puVar16 = FUN_140057400(puVar16);
              }
              if (puVar16 == (undefined8 *)0x0) {
                uVar15 = (**(code **)*plVar11)(plVar11);
                return (longlong *)(uVar15 & 0xffffffffffffff00);
              }
              bVar7 = FUN_140056de0((longlong)puVar16);
              if (!bVar7) {
                (**(code **)*plVar11)(plVar11);
                uVar15 = (**(code **)*puVar16)(puVar16,1);
                return (longlong *)(uVar15 & 0xffffffffffffff00);
              }
              plVar12 = (longlong *)FUN_140025be0(param_1);
              (**(code **)(*plVar12 + 0x20))(plVar12,puVar16);
              iVar19 = iVar19 + 1;
              iVar8 = (**(code **)(*plVar11 + 0x40))(plVar11);
            } while (iVar19 < iVar8);
          }
          uVar17 = (**(code **)*plVar11)(plVar11);
          plVar11 = (longlong *)CONCAT71((int7)((ulonglong)uVar17 >> 8),1);
        }
      }
    }
  }
  return plVar11;
}


// ==== FUN_140032e20 @ 140032e20  longlong FUN_140032e20(longlong param_1, uint param_2, uint param_3)

longlong FUN_140032e20(longlong param_1,uint param_2,uint param_3)

{
  void *pvVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined8 *puVar6;
  undefined4 uVar7;
  longlong lVar8;
  longlong *extraout_RAX;
  longlong *extraout_RAX_00;
  longlong *extraout_RAX_01;
  longlong *extraout_RAX_02;
  longlong *extraout_RAX_03;
  longlong *extraout_RAX_04;
  longlong *extraout_RAX_05;
  longlong *extraout_RAX_06;
  longlong *extraout_RAX_07;
  longlong *extraout_RAX_08;
  longlong *plVar9;
  longlong *plVar10;
  ulonglong uVar11;
  undefined8 uVar12;
  void **ppvVar13;
  longlong *extraout_RAX_09;
  longlong *extraout_RAX_10;
  longlong *extraout_RAX_11;
  void **ppvVar14;
  void **ppvVar15;
  void **ppvVar16;
  void *pvVar17;
  longlong *plVar18;
  uint local_res10 [2];
  uint local_res18 [2];
  void **local_res20;
  longlong *local_118;
  void *local_110;
  void **local_108 [3];
  undefined4 *local_f0;
  undefined4 *local_e8;
  longlong local_e0;
  undefined8 *local_d8;
  void *local_d0;
  void **local_c8;
  undefined4 *puStack_c0;
  uint local_b8 [2];
  void *local_b0 [3];
  void *local_98;
  undefined8 local_90;
  undefined8 local_88;
  void **local_78;
  undefined4 *puStack_70;
  undefined8 local_68;
  void **local_60;
  longlong local_58 [4];
  
  local_68 = 0xfffffffffffffffe;
  local_res10[0] = param_2;
  local_res18[0] = param_3;
  lVar8 = FUN_14001c790();
  plVar9 = *(longlong **)(lVar8 + 8);
  if (plVar9 == (longlong *)0x0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    plVar9 = (longlong *)0x0;
  }
  ppvVar14 = (void **)0x0;
  lVar8 = (**(code **)(*plVar9 + 0x30))(plVar9,param_3);
  if (lVar8 != 0) {
    FUN_14002b870((longlong *)(param_1 + 0xa8),(longlong *)&local_118,local_res10);
    plVar10 = local_118;
    pvVar1 = *(void **)(param_1 + 0xd8);
    plVar9 = *(longlong **)(param_1 + 0xa8);
    if ((plVar9 == (longlong *)0x0) || (plVar9 != local_118)) {
      _invalid_parameter_noinfo();
      plVar9 = extraout_RAX;
    }
    pvVar17 = local_110;
    if (pvVar1 != local_110) {
      if (plVar10 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        plVar9 = extraout_RAX_00;
        ppvVar16 = ppvVar14;
      }
      else {
        ppvVar16 = (void **)*plVar10;
      }
      if (pvVar17 == ppvVar16[6]) {
        _invalid_parameter_noinfo();
        plVar9 = extraout_RAX_01;
      }
      plVar18 = *(longlong **)((longlong)pvVar17 + 0x38);
      if (*(longlong **)((longlong)pvVar17 + 0x40) < plVar18) {
        _invalid_parameter_noinfo();
        plVar9 = extraout_RAX_02;
      }
      puVar2 = *(undefined8 **)((longlong)pvVar17 + 0x20);
      do {
        if (plVar10 == (longlong *)0x0) {
          _invalid_parameter_noinfo();
          plVar9 = extraout_RAX_03;
          ppvVar16 = ppvVar14;
        }
        else {
          ppvVar16 = (void **)*plVar10;
        }
        if (pvVar17 == ppvVar16[6]) {
          _invalid_parameter_noinfo();
          plVar9 = extraout_RAX_04;
        }
        plVar10 = *(longlong **)((longlong)pvVar17 + 0x40);
        if (plVar10 < *(longlong **)((longlong)pvVar17 + 0x38)) {
          _invalid_parameter_noinfo();
          plVar9 = extraout_RAX_05;
        }
        if ((puVar2 == (undefined8 *)0x0) || (puVar2 != *(undefined8 **)((longlong)pvVar17 + 0x20)))
        {
          _invalid_parameter_noinfo();
          plVar9 = extraout_RAX_06;
        }
        if (plVar18 == plVar10) {
          return CONCAT71((int7)((ulonglong)plVar9 >> 8),1);
        }
        if (puVar2 == (undefined8 *)0x0) {
          _invalid_parameter_noinfo();
          plVar9 = extraout_RAX_07;
          ppvVar16 = ppvVar14;
        }
        else {
          ppvVar16 = (void **)*puVar2;
        }
        if (ppvVar16[4] <= plVar18) {
          _invalid_parameter_noinfo();
          plVar9 = extraout_RAX_08;
        }
        if (((longlong *)*plVar18 != (longlong *)0x0) &&
           (plVar9 = (longlong *)(**(code **)(*(longlong *)*plVar18 + 0x30))(),
           plVar9 != (longlong *)0x0)) {
          plVar10 = FUN_140060e20();
          if (plVar10 == (longlong *)0x0) {
            uVar11 = (**(code **)*plVar9)(plVar9,1);
            return uVar11 & 0xffffffffffffff00;
          }
          uVar12 = FUN_140061040(plVar10,plVar9,param_3);
          if ((char)uVar12 == '\0') {
            plVar9 = (longlong *)(**(code **)(*plVar10 + 0xa0))(plVar10);
            pvVar17 = local_110;
          }
          else {
            plVar9 = (longlong *)FUN_140025b50(param_1);
            lVar8 = *plVar9;
            uVar12 = FUN_14005f720(plVar10);
            (**(code **)(lVar8 + 0x20))(plVar9,uVar12);
            FUN_14002b940((longlong *)(param_1 + 0xe8),(longlong *)&local_d8,local_res18);
            puVar6 = local_d8;
            pvVar1 = *(void **)(param_1 + 0x118);
            puVar3 = *(undefined8 **)(param_1 + 0xe8);
            if ((puVar3 == (undefined8 *)0x0) || (puVar3 != local_d8)) {
              _invalid_parameter_noinfo();
            }
            pvVar17 = local_d0;
            if (pvVar1 == local_d0) {
              local_res20 = (void **)operator_new(8);
              local_108[0] = ppvVar14;
              if (local_res20 != (void **)0x0) {
                *local_res20 = local_108;
                local_108[0] = local_res20;
              }
              local_f0 = (undefined4 *)0x0;
              local_e8 = (undefined4 *)0x0;
              local_e0 = 0;
              local_60 = local_res20;
              uVar7 = (**(code **)(*plVar10 + 8))(plVar10);
              puVar5 = local_e8;
              local_res20 = (void **)CONCAT44(local_res20._4_4_,uVar7);
              if ((local_f0 == (undefined4 *)0x0) ||
                 ((ulonglong)(local_e0 - (longlong)local_f0 >> 2) <=
                  (ulonglong)((longlong)local_e8 - (longlong)local_f0 >> 2))) {
                if (local_e8 < local_f0) {
                  _invalid_parameter_noinfo();
                }
                puVar4 = local_f0;
                ppvVar16 = local_108[0];
                local_c8 = local_108[0];
                puStack_c0 = puVar5;
                ppvVar15 = ppvVar14;
                if (((longlong)local_e8 - (longlong)local_f0 & 0xfffffffffffffffcU) != 0) {
                  if (local_e8 < local_f0) {
                    _invalid_parameter_noinfo();
                  }
                  if ((ppvVar16 == (void **)0x0) || (ppvVar16 != local_108[0])) {
                    _invalid_parameter_noinfo();
                  }
                  ppvVar15 = (void **)((longlong)puVar5 - (longlong)puVar4 >> 2);
                }
                local_78 = local_c8;
                puStack_70 = puStack_c0;
                FUN_14002d450((longlong)local_108,(longlong)&local_78,1,(undefined4 *)&local_res20);
                puVar5 = local_f0;
                if (local_e8 < local_f0) {
                  _invalid_parameter_noinfo();
                }
                ppvVar16 = local_108[0];
                if (local_108[0] == (void **)0x0) {
                  _invalid_parameter_noinfo();
                  ppvVar13 = ppvVar14;
                }
                else {
                  ppvVar13 = (void **)*local_108[0];
                }
                if (puVar5 + (longlong)ppvVar15 <= ppvVar13[4]) {
                  ppvVar13 = ppvVar14;
                  if (ppvVar16 != (void **)0x0) {
                    ppvVar13 = (void **)*ppvVar16;
                  }
                  if (ppvVar13[3] <= puVar5 + (longlong)ppvVar15) goto LAB_1400331e9;
                }
                _invalid_parameter_noinfo();
              }
              else {
                *local_e8 = uVar7;
                local_e8 = local_e8 + 1;
              }
LAB_1400331e9:
              param_3 = local_res18[0];
              local_b8[0] = local_res18[0];
              FUN_14002d0f0(local_b0,local_108);
              FUN_140031d10((longlong *)(param_1 + 0xe8),local_58,local_b8);
              local_res20 = local_b0;
              if (local_98 != (void *)0x0) {
                operator_delete(local_98);
              }
              local_98 = (void *)0x0;
              local_90 = 0;
              local_88 = 0;
              operator_delete(local_b0[0]);
              if (local_f0 != (undefined4 *)0x0) {
                operator_delete(local_f0);
              }
              local_f0 = (undefined4 *)0x0;
              local_e8 = (undefined4 *)0x0;
              local_e0 = 0;
              operator_delete(local_108[0]);
              plVar9 = extraout_RAX_09;
              pvVar17 = local_110;
            }
            else {
              uVar7 = (**(code **)(*plVar10 + 8))(plVar10);
              local_res20 = (void **)CONCAT44(local_res20._4_4_,uVar7);
              if (puVar6 == (undefined8 *)0x0) {
                _invalid_parameter_noinfo();
                ppvVar16 = ppvVar14;
              }
              else {
                ppvVar16 = (void **)*puVar6;
              }
              if (pvVar17 == ppvVar16[6]) {
                _invalid_parameter_noinfo();
              }
              plVar9 = (longlong *)
                       FUN_14002f3b0((longlong *)((longlong)pvVar17 + 0x20),
                                     (undefined4 *)&local_res20);
              pvVar17 = local_110;
              param_3 = local_res18[0];
            }
          }
        }
        if (puVar2 == (undefined8 *)0x0) {
          _invalid_parameter_noinfo();
          plVar9 = extraout_RAX_10;
          ppvVar16 = ppvVar14;
        }
        else {
          ppvVar16 = (void **)*puVar2;
        }
        if (ppvVar16[4] <= plVar18) {
          _invalid_parameter_noinfo();
          plVar9 = extraout_RAX_11;
        }
        plVar18 = plVar18 + 1;
        plVar10 = local_118;
      } while( true );
    }
    lVar8 = CONCAT71((int7)((ulonglong)plVar9 >> 8),1);
  }
  return lVar8;
}


// ==== FUN_140033340 @ 140033340  undefined8 FUN_140033340(longlong param_1, uint * param_2)

undefined8 FUN_140033340(longlong param_1,uint *param_2)

{
  undefined4 *puVar1;
  void **ppvVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  longlong lVar5;
  longlong *plVar6;
  longlong *plVar7;
  ulonglong uVar8;
  undefined8 uVar9;
  void **ppvVar10;
  undefined8 extraout_RAX;
  void **ppvVar11;
  void **ppvVar12;
  void **local_res18;
  void **local_res20;
  void **local_b8 [3];
  undefined4 *local_a0;
  undefined4 *local_98;
  longlong local_90;
  void **local_88;
  undefined4 *puStack_80;
  uint local_68 [2];
  void *local_60 [3];
  void *local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  
  local_30 = 0xfffffffffffffffe;
  lVar5 = FUN_14001c790();
  plVar6 = *(longlong **)(lVar5 + 8);
  if (plVar6 == (longlong *)0x0) {
    log_InlineLogERROR(&DAT_1400be0b0);
    plVar6 = (longlong *)0x0;
  }
  ppvVar10 = (void **)0x0;
  lVar5 = (**(code **)(*plVar6 + 0x30))(plVar6,*param_2);
  if (lVar5 == 0) {
    return 0;
  }
  if (*(uint *)(lVar5 + 0x8c) != param_2[1]) {
    return (ulonglong)(uint3)(*(uint *)(lVar5 + 0x8c) >> 8) << 8;
  }
  plVar6 = (longlong *)InstanceGet();
  plVar6 = (longlong *)(**(code **)(*plVar6 + 0x20))(plVar6,"cq_generator");
  if (plVar6 == (longlong *)0x0) {
    return 0;
  }
  param_2[0xb] = param_2[0xb] | 1;
  plVar7 = (longlong *)(**(code **)(*plVar6 + 0x10))(plVar6,2);
  (**(code **)(*plVar7 + 0xb0))(plVar7,param_2[2]);
  plVar7 = (longlong *)(**(code **)(*plVar6 + 0x10))(plVar6,3);
  (**(code **)(*plVar7 + 0xb0))(plVar7,param_2[3]);
  plVar7 = (longlong *)(**(code **)(*plVar6 + 0x10))(plVar6,4);
  (**(code **)(*plVar7 + 0xb0))(plVar7,param_2[4]);
  plVar7 = (longlong *)(**(code **)(*plVar6 + 0x10))(plVar6,5);
  (**(code **)(*plVar7 + 0xb0))(plVar7,param_2[5]);
  plVar7 = (longlong *)(**(code **)(*plVar6 + 0x10))(plVar6,6);
  (**(code **)(*plVar7 + 0xb0))(plVar7,param_2[6]);
  plVar7 = (longlong *)(**(code **)(*plVar6 + 0x10))(plVar6,7);
  (**(code **)(*plVar7 + 0xb0))(plVar7,param_2[7]);
  plVar7 = (longlong *)(**(code **)(*plVar6 + 0x10))(plVar6,8);
  (**(code **)(*plVar7 + 0xb0))(plVar7,param_2[8]);
  plVar7 = (longlong *)(**(code **)(*plVar6 + 0x10))(plVar6,9);
  (**(code **)(*plVar7 + 0xb8))(plVar7,param_2[9]);
  plVar7 = (longlong *)(**(code **)(*plVar6 + 0x10))(plVar6,0x11);
  (**(code **)(*plVar7 + 0xb0))(plVar7,param_2[10]);
  plVar7 = (longlong *)(**(code **)(*plVar6 + 0x10))(plVar6,0x12);
  (**(code **)(*plVar7 + 0xb8))(plVar7,param_2[0xb]);
  plVar7 = FUN_140060e20();
  if (plVar7 == (longlong *)0x0) {
    uVar8 = (**(code **)*plVar6)(plVar6,1);
    return uVar8 & 0xffffffffffffff00;
  }
  uVar9 = FUN_140061040(plVar7,plVar6,*param_2);
  if ((char)uVar9 == '\0') {
    uVar8 = (**(code **)(*plVar7 + 0xa0))(plVar7);
    return uVar8 & 0xffffffffffffff00;
  }
  plVar6 = (longlong *)FUN_140025b50(param_1);
  lVar5 = *plVar6;
  uVar9 = FUN_14005f720(plVar7);
  (**(code **)(lVar5 + 0x20))(plVar6,uVar9);
  FUN_14002b940((longlong *)(param_1 + 0xe8),(longlong *)&local_88,param_2);
  ppvVar2 = local_88;
  puVar1 = *(undefined4 **)(param_1 + 0x118);
  if ((*(void ***)(param_1 + 0xe8) == (void **)0x0) || (*(void ***)(param_1 + 0xe8) != local_88)) {
    _invalid_parameter_noinfo();
  }
  if (puVar1 != puStack_80) {
    uVar4 = (**(code **)(*plVar7 + 8))(plVar7);
    local_res18 = (void **)CONCAT44(local_res18._4_4_,uVar4);
    if (ppvVar2 == (void **)0x0) {
      _invalid_parameter_noinfo();
    }
    else {
      ppvVar10 = (void **)*ppvVar2;
    }
    if (puStack_80 == (undefined4 *)ppvVar10[6]) {
      _invalid_parameter_noinfo();
    }
    uVar9 = FUN_14002f3b0((longlong *)(puStack_80 + 8),(undefined4 *)&local_res18);
    goto LAB_140033838;
  }
  local_res18 = (void **)operator_new(8);
  local_b8[0] = ppvVar10;
  if (local_res18 != (void **)0x0) {
    *local_res18 = local_b8;
    local_b8[0] = local_res18;
  }
  local_a0 = (undefined4 *)0x0;
  local_98 = (undefined4 *)0x0;
  local_90 = 0;
  local_res20 = local_res18;
  uVar4 = (**(code **)(*plVar7 + 8))(plVar7);
  puVar1 = local_98;
  local_res18 = (void **)CONCAT44(local_res18._4_4_,uVar4);
  if ((local_a0 == (undefined4 *)0x0) ||
     ((ulonglong)(local_90 - (longlong)local_a0 >> 2) <=
      (ulonglong)((longlong)local_98 - (longlong)local_a0 >> 2))) {
    if (local_98 < local_a0) {
      _invalid_parameter_noinfo();
    }
    puVar3 = local_a0;
    ppvVar2 = local_b8[0];
    local_88 = local_b8[0];
    puStack_80 = puVar1;
    ppvVar11 = ppvVar10;
    if (((longlong)local_98 - (longlong)local_a0 & 0xfffffffffffffffcU) != 0) {
      if (local_98 < local_a0) {
        _invalid_parameter_noinfo();
      }
      if ((ppvVar2 == (void **)0x0) || (ppvVar2 != local_b8[0])) {
        _invalid_parameter_noinfo();
      }
      ppvVar11 = (void **)((longlong)puVar1 - (longlong)puVar3 >> 2);
    }
    FUN_14002d450((longlong)local_b8,(longlong)&local_88,1,(undefined4 *)&local_res18);
    puVar1 = local_a0;
    if (local_98 < local_a0) {
      _invalid_parameter_noinfo();
    }
    ppvVar2 = local_b8[0];
    if (local_b8[0] == (void **)0x0) {
      _invalid_parameter_noinfo();
      ppvVar12 = ppvVar10;
    }
    else {
      ppvVar12 = (void **)*local_b8[0];
    }
    if (puVar1 + (longlong)ppvVar11 <= ppvVar12[4]) {
      if (ppvVar2 != (void **)0x0) {
        ppvVar10 = (void **)*ppvVar2;
      }
      if (ppvVar10[3] <= puVar1 + (longlong)ppvVar11) goto LAB_140033750;
    }
    _invalid_parameter_noinfo();
  }
  else {
    *local_98 = uVar4;
    local_98 = local_98 + 1;
  }
LAB_140033750:
  local_68[0] = *param_2;
  FUN_14002d0f0(local_60,local_b8);
  FUN_140031d10((longlong *)(param_1 + 0xe8),(longlong *)&local_88,local_68);
  local_res18 = local_60;
  if (local_48 != (void *)0x0) {
    operator_delete(local_48);
  }
  local_48 = (void *)0x0;
  local_40 = 0;
  local_38 = 0;
  operator_delete(local_60[0]);
  if (local_a0 != (undefined4 *)0x0) {
    operator_delete(local_a0);
  }
  local_a0 = (undefined4 *)0x0;
  local_98 = (undefined4 *)0x0;
  local_90 = 0;
  operator_delete(local_b8[0]);
  uVar9 = extraout_RAX;
LAB_140033838:
  return CONCAT71((int7)((ulonglong)uVar9 >> 8),1);
}


// ==== FUN_140033860 @ 140033860  undefined FUN_140033860(longlong param_1, uint param_2)

void FUN_140033860(longlong param_1,uint param_2)

{
  char cVar1;
  longlong *plVar2;
  longlong *plVar3;
  undefined4 *puVar4;
  longlong *plVar5;
  undefined8 *puVar6;
  longlong lVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  undefined4 *puVar10;
  longlong lVar11;
  longlong *plVar12;
  longlong local_58;
  undefined8 *local_50;
  longlong local_48;
  undefined8 local_40;
  longlong *local_38;
  longlong local_30;
  
  puVar9 = (undefined8 *)(*(undefined8 **)(param_1 + 0x118))[1];
  cVar1 = *(char *)((longlong)puVar9 + 0x51);
  puVar6 = *(undefined8 **)(param_1 + 0x118);
  while (cVar1 == '\0') {
    if (*(uint *)(puVar9 + 3) < param_2) {
      puVar8 = (undefined8 *)puVar9[2];
      puVar9 = puVar6;
    }
    else {
      puVar8 = (undefined8 *)*puVar9;
    }
    puVar6 = puVar9;
    puVar9 = puVar8;
    cVar1 = *(char *)((longlong)puVar8 + 0x51);
  }
  puVar9 = *(undefined8 **)(param_1 + 0x118);
  local_50 = puVar6;
  local_58 = *(longlong *)(param_1 + 0xe8);
  if (*(longlong *)(param_1 + 0xe8) == 0) {
    _invalid_parameter_noinfo();
  }
  if ((puVar6 == puVar9) || (param_2 < *(uint *)(puVar6 + 3))) {
    plVar12 = &local_48;
    local_40 = *(undefined8 *)(param_1 + 0x118);
    local_48 = *(longlong *)(param_1 + 0xe8);
  }
  else {
    plVar12 = &local_58;
  }
  plVar2 = (longlong *)*plVar12;
  lVar11 = *(longlong *)(param_1 + 0x118);
  local_38 = plVar2;
  local_30 = plVar12[1];
  if ((*(longlong **)(param_1 + 0xe8) == (longlong *)0x0) ||
     (*(longlong **)(param_1 + 0xe8) != plVar2)) {
    _invalid_parameter_noinfo();
  }
  lVar7 = local_30;
  if (lVar11 != local_30) {
    if (plVar2 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar11 = 0;
    }
    else {
      lVar11 = *plVar2;
    }
    if (lVar7 == *(longlong *)(lVar11 + 0x30)) {
      _invalid_parameter_noinfo();
    }
    puVar10 = *(undefined4 **)(lVar7 + 0x38);
    if (*(undefined4 **)(lVar7 + 0x40) < puVar10) {
      _invalid_parameter_noinfo();
    }
    plVar3 = *(longlong **)(lVar7 + 0x20);
    while( true ) {
      if (plVar2 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar11 = 0;
      }
      else {
        lVar11 = *plVar2;
      }
      if (lVar7 == *(longlong *)(lVar11 + 0x30)) {
        _invalid_parameter_noinfo();
      }
      puVar4 = *(undefined4 **)(lVar7 + 0x40);
      if (puVar4 < *(undefined4 **)(lVar7 + 0x38)) {
        _invalid_parameter_noinfo();
      }
      if ((plVar3 == (longlong *)0x0) || (plVar3 != *(longlong **)(lVar7 + 0x20))) {
        _invalid_parameter_noinfo();
      }
      if (puVar10 == puVar4) break;
      plVar5 = *(longlong **)(param_1 + 0x10);
      if (plVar5 == (longlong *)0x0) {
        log_InlineLogERROR(&DAT_1400be0b0);
      }
      if (plVar3 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar11 = 0;
      }
      else {
        lVar11 = *plVar3;
      }
      if (*(undefined4 **)(lVar11 + 0x20) <= puVar10) {
        _invalid_parameter_noinfo();
      }
      (**(code **)(*plVar5 + 0x28))(plVar5,*puVar10);
      if (plVar3 == (longlong *)0x0) {
        _invalid_parameter_noinfo();
        lVar11 = 0;
      }
      else {
        lVar11 = *plVar3;
      }
      if (*(undefined4 **)(lVar11 + 0x20) <= puVar10) {
        _invalid_parameter_noinfo();
      }
      puVar10 = puVar10 + 1;
    }
    local_38 = (longlong *)*plVar12;
    local_30 = plVar12[1];
    FUN_140031ec0((undefined8 *)(param_1 + 0xe8),&local_48,(longlong *)&local_38);
  }
  return;
}


// ==== FUN_140033aa0 @ 140033aa0  longlong * FUN_140033aa0(longlong * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_140033aa0(longlong *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  char cVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong local_28;
  longlong lStack_20;
  undefined8 local_18 [2];
  
  lVar2 = *(longlong *)param_1[6];
  plVar5 = param_3;
  plVar6 = param_4;
  if ((*param_3 == 0) || (*param_3 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (param_3[1] == lVar2) {
    lVar2 = param_1[6];
    if ((*param_4 == 0) || (*param_4 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    if (param_4[1] == lVar2) {
      FUN_140031910(param_1,*(longlong **)(param_1[6] + 8),plVar5,plVar6);
      *(longlong *)(param_1[6] + 8) = param_1[6];
      param_1[7] = 0;
      *(longlong *)param_1[6] = param_1[6];
      *(longlong *)(param_1[6] + 0x10) = param_1[6];
      lVar2 = *(longlong *)param_1[6];
      *param_2 = *param_1;
      param_2[1] = lVar2;
      return param_2;
    }
  }
  while( true ) {
    if ((*param_3 == 0) || (*param_3 != *param_4)) {
      _invalid_parameter_noinfo();
    }
    lVar2 = *param_3;
    if (param_3[1] == param_4[1]) break;
    lVar3 = param_3[1];
    if (*param_3 == 0) {
      _invalid_parameter_noinfo();
    }
    lVar4 = param_3[1];
    if (*(char *)(lVar4 + 0x51) == '\0') {
      plVar5 = *(longlong **)(lVar4 + 0x10);
      if (*(char *)((longlong)plVar5 + 0x51) == '\0') {
        cVar1 = *(char *)(*plVar5 + 0x51);
        plVar6 = (longlong *)*plVar5;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar6 + 0x51);
          plVar5 = plVar6;
          plVar6 = (longlong *)*plVar6;
        }
      }
      else {
        plVar5 = *(longlong **)(lVar4 + 8);
        cVar1 = *(char *)((longlong)plVar5 + 0x51);
        while ((cVar1 == '\0' && (param_3[1] == plVar5[2]))) {
          param_3[1] = (longlong)plVar5;
          plVar5 = (longlong *)plVar5[1];
          cVar1 = *(char *)((longlong)plVar5 + 0x51);
        }
      }
      param_3[1] = (longlong)plVar5;
    }
    else {
      _invalid_parameter_noinfo();
    }
    local_28 = lVar2;
    lStack_20 = lVar3;
    FUN_140031ec0(param_1,local_18,&local_28);
  }
  lVar2 = param_3[1];
  *param_2 = *param_1;
  param_2[1] = lVar2;
  return param_2;
}


// ==== FUN_140033c80 @ 140033c80  undefined FUN_140033c80(longlong param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_140033c80(longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  FUN_140032750(param_1,*(longlong **)(*(longlong *)(param_1 + 0x30) + 8),param_3,param_4);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)*(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x30);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 0x10) = *(longlong *)(param_1 + 0x30);
  return;
}


// ==== FUN_140033cc0 @ 140033cc0  undefined FUN_140033cc0(longlong param_1, uint param_2)

void FUN_140033cc0(longlong param_1,uint param_2)

{
  if (param_2 != 0) {
    FUN_140033860(param_1,param_2);
  }
  return;
}


// ==== FUN_140033ce0 @ 140033ce0  undefined FUN_140033ce0(longlong * param_1)

void FUN_140033ce0(longlong *param_1)

{
  longlong local_38;
  undefined8 *puStack_30;
  longlong local_28;
  undefined8 uStack_20;
  longlong local_18 [2];
  
  local_38 = *param_1;
  puStack_30 = (undefined8 *)param_1[6];
  uStack_20 = *puStack_30;
  local_28 = local_38;
  FUN_140033aa0(param_1,local_18,&local_28,&local_38);
  operator_delete((void *)param_1[6]);
  param_1[6] = 0;
  param_1[7] = 0;
  return;
}


// ==== FUN_140033d50 @ 140033d50  longlong * FUN_140033d50(longlong * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_140033d50(longlong *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  char cVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong *plVar6;
  longlong local_28;
  longlong lStack_20;
  undefined8 local_18 [2];
  
  lVar2 = *(longlong *)param_1[6];
  plVar5 = param_3;
  plVar6 = param_4;
  if ((*param_3 == 0) || (*param_3 != *param_1)) {
    _invalid_parameter_noinfo();
  }
  if (param_3[1] == lVar2) {
    lVar2 = param_1[6];
    if ((*param_4 == 0) || (*param_4 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    if (param_4[1] == lVar2) {
      FUN_140032750(param_1,*(longlong **)(param_1[6] + 8),plVar5,plVar6);
      *(longlong *)(param_1[6] + 8) = param_1[6];
      param_1[7] = 0;
      *(longlong *)param_1[6] = param_1[6];
      *(longlong *)(param_1[6] + 0x10) = param_1[6];
      lVar2 = *(longlong *)param_1[6];
      *param_2 = *param_1;
      param_2[1] = lVar2;
      return param_2;
    }
  }
  while( true ) {
    if ((*param_3 == 0) || (*param_3 != *param_4)) {
      _invalid_parameter_noinfo();
    }
    lVar2 = *param_3;
    if (param_3[1] == param_4[1]) break;
    lVar3 = param_3[1];
    if (*param_3 == 0) {
      _invalid_parameter_noinfo();
    }
    lVar4 = param_3[1];
    if (*(char *)(lVar4 + 0x51) == '\0') {
      plVar5 = *(longlong **)(lVar4 + 0x10);
      if (*(char *)((longlong)plVar5 + 0x51) == '\0') {
        cVar1 = *(char *)(*plVar5 + 0x51);
        plVar6 = (longlong *)*plVar5;
        while (cVar1 == '\0') {
          cVar1 = *(char *)(*plVar6 + 0x51);
          plVar5 = plVar6;
          plVar6 = (longlong *)*plVar6;
        }
      }
      else {
        plVar5 = *(longlong **)(lVar4 + 8);
        cVar1 = *(char *)((longlong)plVar5 + 0x51);
        while ((cVar1 == '\0' && (param_3[1] == plVar5[2]))) {
          param_3[1] = (longlong)plVar5;
          plVar5 = (longlong *)plVar5[1];
          cVar1 = *(char *)((longlong)plVar5 + 0x51);
        }
      }
      param_3[1] = (longlong)plVar5;
    }
    else {
      _invalid_parameter_noinfo();
    }
    local_28 = lVar2;
    lStack_20 = lVar3;
    FUN_140032320(param_1,local_18,&local_28);
  }
  lVar2 = param_3[1];
  *param_2 = *param_1;
  param_2[1] = lVar2;
  return param_2;
}


// ==== FUN_140033f30 @ 140033f30  undefined FUN_140033f30(longlong * param_1)

void FUN_140033f30(longlong *param_1)

{
  FUN_140033ce0(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140033f60 @ 140033f60  undefined FUN_140033f60(longlong * param_1)

void FUN_140033f60(longlong *param_1)

{
  longlong local_38;
  undefined8 *puStack_30;
  longlong local_28;
  undefined8 uStack_20;
  longlong local_18 [2];
  
  local_38 = *param_1;
  puStack_30 = (undefined8 *)param_1[6];
  uStack_20 = *puStack_30;
  local_28 = local_38;
  FUN_140033d50(param_1,local_18,&local_28,&local_38);
  operator_delete((void *)param_1[6]);
  param_1[6] = 0;
  param_1[7] = 0;
  return;
}


// ==== FUN_140033fd0 @ 140033fd0  undefined FUN_140033fd0(longlong * param_1)

void FUN_140033fd0(longlong *param_1)

{
  FUN_140033ce0(param_1);
  operator_delete((void *)*param_1);
  return;
}


