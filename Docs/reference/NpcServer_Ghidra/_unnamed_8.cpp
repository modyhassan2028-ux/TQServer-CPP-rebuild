// NpcServer.exe :: _unnamed  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== FUN_140091090 @ 140091090  undefined8 * FUN_140091090(undefined8 * param_1, undefined8 * param_2, char param_3, undefined8 * param_4, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_5)

undefined8 *
FUN_140091090(undefined8 *param_1,undefined8 *param_2,char param_3,undefined8 *param_4,
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_5)

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
  plVar5 = FUN_1400900f0(param_1,param_1[6],param_4,param_1[6],param_5,0);
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


// ==== FUN_1400913d0 @ 1400913d0  undefined8 * FUN_1400913d0(undefined8 * param_1)

undefined8 * FUN_1400913d0(undefined8 *param_1)

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


// ==== FUN_140091420 @ 140091420  undefined8 * FUN_140091420(undefined8 * param_1)

undefined8 * FUN_140091420(undefined8 *param_1)

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


// ==== FUN_140091480 @ 140091480  undefined8 * FUN_140091480(longlong * param_1, longlong * param_2)

undefined8 * FUN_140091480(longlong *param_1,longlong *param_2)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  longlong lVar5;
  longlong *plVar6;
  longlong local_48;
  undefined4 local_40;
  longlong *local_38;
  undefined8 *puStack_30;
  longlong local_28 [2];
  
  puVar4 = (undefined8 *)param_1[6];
  if (*(char *)((longlong)puVar4[1] + 0x29) == '\0') {
    puVar1 = (undefined8 *)puVar4[1];
    do {
      if ((longlong)puVar1[3] < *param_2) {
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
  if ((puVar4 == puVar1) || (*param_2 < (longlong)puVar4[3])) {
    local_48 = *param_2;
    local_40 = 0;
    local_38 = plVar6;
    puStack_30 = puVar4;
    plVar3 = FUN_140090cf0(param_1,local_28,(longlong *)&local_38,&local_48);
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


// ==== FUN_140091580 @ 140091580  undefined FUN_140091580(longlong * param_1)

void FUN_140091580(longlong *param_1)

{
  FUN_140091020(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_1400915b0 @ 1400915b0  longlong * FUN_1400915b0(longlong * param_1, longlong * param_2, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_3)

longlong *
FUN_1400915b0(longlong *param_1,longlong *param_2,
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_3)

{
  char cVar1;
  longlong lVar2;
  longlong *plVar3;
  longlong *plVar4;
  bool bVar5;
  bool bVar6;
  longlong *plVar7;
  longlong *plVar8;
  longlong local_38;
  longlong *local_30;
  
  plVar7 = (longlong *)((longlong *)param_1[6])[1];
  bVar5 = true;
  cVar1 = *(char *)((longlong)plVar7 + 0x51);
  plVar3 = (longlong *)param_1[6];
  while (cVar1 == '\0') {
    bVar5 = std::operator<<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                      (param_3,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                                *)(plVar7 + 3));
    if (bVar5) {
      plVar8 = (longlong *)*plVar7;
    }
    else {
      plVar8 = (longlong *)plVar7[2];
    }
    plVar3 = plVar7;
    plVar7 = plVar8;
    cVar1 = *(char *)((longlong)plVar8 + 0x51);
  }
  lVar2 = *param_1;
  plVar7 = plVar3;
  local_38 = lVar2;
  plVar8 = plVar3;
  if (bVar5 == false) {
LAB_1400916fd:
    local_30 = plVar8;
    bVar6 = std::operator<<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                      ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                        *)(plVar7 + 3),param_3);
    if (!bVar6) {
      *(undefined1 *)(param_2 + 2) = 0;
      *param_2 = local_38;
      goto LAB_140091735;
    }
  }
  else {
    plVar7 = *(longlong **)param_1[6];
    local_30 = plVar3;
    if (lVar2 == 0) {
      _invalid_parameter_noinfo();
    }
    if (plVar3 != plVar7) {
      if (lVar2 == 0) {
        _invalid_parameter_noinfo();
      }
      if (*(char *)((longlong)plVar3 + 0x51) == '\0') {
        plVar7 = (longlong *)*plVar3;
        if (*(char *)((longlong)plVar7 + 0x51) == '\0') {
          cVar1 = *(char *)(plVar7[2] + 0x51);
          plVar4 = (longlong *)plVar7[2];
          while (plVar8 = plVar7, cVar1 == '\0') {
            cVar1 = *(char *)(plVar4[2] + 0x51);
            plVar7 = plVar4;
            plVar4 = (longlong *)plVar4[2];
          }
        }
        else {
          cVar1 = *(char *)(plVar3[1] + 0x51);
          plVar8 = (longlong *)plVar3[1];
          plVar4 = plVar3;
          while ((plVar7 = plVar8, cVar1 == '\0' && (plVar4 == (longlong *)*plVar7))) {
            cVar1 = *(char *)(plVar7[1] + 0x51);
            plVar8 = (longlong *)plVar7[1];
            plVar4 = plVar7;
            local_30 = plVar7;
          }
          plVar8 = plVar7;
          if (*(char *)((longlong)plVar4 + 0x51) != '\0') {
            _invalid_parameter_noinfo();
            plVar7 = plVar4;
            plVar8 = local_30;
          }
        }
      }
      else {
        plVar7 = (longlong *)plVar3[2];
        plVar8 = plVar7;
        if (*(char *)((longlong)plVar7 + 0x51) != '\0') {
          local_30 = plVar7;
          _invalid_parameter_noinfo();
          plVar8 = local_30;
        }
      }
      goto LAB_1400916fd;
    }
    bVar5 = true;
  }
  plVar7 = FUN_140091090(param_1,&local_38,bVar5,plVar3,param_3);
  *(undefined1 *)(param_2 + 2) = 1;
  local_30 = (longlong *)plVar7[1];
  *param_2 = *plVar7;
LAB_140091735:
  param_2[1] = (longlong)local_30;
  return param_2;
}


// ==== FUN_140091760 @ 140091760  undefined8 * FUN_140091760(undefined8 * param_1)

undefined8 * FUN_140091760(undefined8 *param_1)

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
  lVar2 = FUN_14008ef40();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x29) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_1400917e0 @ 1400917e0  undefined8 * FUN_1400917e0(undefined8 * param_1)

undefined8 * FUN_1400917e0(undefined8 *param_1)

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
  lVar2 = FUN_14008f020();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x51) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_140091870 @ 140091870  undefined8 * FUN_140091870(undefined8 * param_1, undefined8 * param_2, longlong * param_3)

undefined8 * FUN_140091870(undefined8 *param_1,undefined8 *param_2,longlong *param_3)

{
  int *piVar1;
  char cVar2;
  longlong *plVar3;
  longlong *plVar4;
  undefined8 *puVar5;
  longlong lVar6;
  longlong *plVar7;
  longlong *plVar8;
  longlong *plVar9;
  longlong *plVar10;
  undefined **local_90 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_78 [40];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_50 [40];
  
  plVar3 = (longlong *)param_3[1];
  if (*(char *)((longlong)plVar3 + 0x51) != '\0') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (local_50,"invalid map/set<T> iterator");
    std::exception::exception((exception *)local_90);
    local_90[0] = std::logic_error::vftable;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_78,local_50);
    local_90[0] = std::out_of_range::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_90,(ThrowInfo *)&DAT_1400feda0);
  }
  FUN_14008dd10(param_3);
  plVar9 = (longlong *)*plVar3;
  if (*(char *)((longlong)plVar9 + 0x51) == '\0') {
    plVar10 = plVar9;
    if (*(char *)(plVar3[2] + 0x51) == '\0') {
      plVar8 = (longlong *)param_3[1];
      plVar10 = (longlong *)plVar8[2];
      if (plVar8 != plVar3) {
        plVar9[1] = (longlong)plVar8;
        *plVar8 = *plVar3;
        plVar9 = plVar8;
        if (plVar8 != (longlong *)plVar3[2]) {
          plVar9 = (longlong *)plVar8[1];
          if (*(char *)((longlong)plVar10 + 0x51) == '\0') {
            plVar10[1] = (longlong)plVar9;
          }
          *plVar9 = (longlong)plVar10;
          plVar8[2] = plVar3[2];
          *(longlong **)(plVar3[2] + 8) = plVar8;
        }
        if (*(longlong **)(param_1[6] + 8) == plVar3) {
          *(longlong **)(param_1[6] + 8) = plVar8;
        }
        else {
          puVar5 = (undefined8 *)plVar3[1];
          if ((longlong *)*puVar5 == plVar3) {
            *puVar5 = plVar8;
          }
          else {
            puVar5[2] = plVar8;
          }
        }
        plVar8[1] = plVar3[1];
        plVar4 = plVar3 + 10;
        plVar8 = plVar8 + 10;
        if (plVar8 != plVar4) {
          lVar6 = *plVar8;
          *(char *)plVar8 = (char)*plVar4;
          *(char *)plVar4 = (char)lVar6;
        }
        goto LAB_140091a5e;
      }
    }
  }
  else {
    plVar10 = (longlong *)plVar3[2];
  }
  plVar9 = (longlong *)plVar3[1];
  if (*(char *)((longlong)plVar10 + 0x51) == '\0') {
    plVar10[1] = (longlong)plVar9;
  }
  if (*(longlong **)(param_1[6] + 8) == plVar3) {
    *(longlong **)(param_1[6] + 8) = plVar10;
  }
  else if ((longlong *)*plVar9 == plVar3) {
    *plVar9 = (longlong)plVar10;
  }
  else {
    plVar9[2] = (longlong)plVar10;
  }
  if (*(longlong **)param_1[6] == plVar3) {
    plVar8 = plVar9;
    if (*(char *)((longlong)plVar10 + 0x51) == '\0') {
      cVar2 = *(char *)(*plVar10 + 0x51);
      plVar4 = (longlong *)*plVar10;
      plVar8 = plVar10;
      while (plVar7 = plVar4, cVar2 == '\0') {
        plVar4 = (longlong *)*plVar7;
        cVar2 = *(char *)((longlong)plVar4 + 0x51);
        plVar8 = plVar7;
      }
    }
    *(longlong **)param_1[6] = plVar8;
  }
  if (*(longlong **)(param_1[6] + 0x10) == plVar3) {
    plVar8 = plVar9;
    if (*(char *)((longlong)plVar10 + 0x51) == '\0') {
      cVar2 = *(char *)(plVar10[2] + 0x51);
      plVar4 = (longlong *)plVar10[2];
      plVar8 = plVar10;
      while (plVar7 = plVar4, cVar2 == '\0') {
        plVar4 = (longlong *)plVar7[2];
        cVar2 = *(char *)((longlong)plVar4 + 0x51);
        plVar8 = plVar7;
      }
    }
    *(longlong **)(param_1[6] + 0x10) = plVar8;
  }
LAB_140091a5e:
  if ((char)plVar3[10] == '\x01') {
    if (plVar10 != *(longlong **)(param_1[6] + 8)) {
      do {
        plVar8 = plVar9;
        if ((char)plVar10[10] != '\x01') break;
        plVar9 = (longlong *)*plVar8;
        if (plVar10 == plVar9) {
          plVar9 = (longlong *)plVar8[2];
          if ((char)plVar9[10] == '\0') {
            *(undefined1 *)(plVar9 + 10) = 1;
            *(undefined1 *)(plVar8 + 10) = 0;
            FUN_14008e310((longlong)param_1,(longlong)plVar8);
            plVar9 = (longlong *)plVar8[2];
          }
          if (*(char *)((longlong)plVar9 + 0x51) == '\0') {
            if ((*(char *)(*plVar9 + 0x50) != '\x01') || (*(char *)(plVar9[2] + 0x50) != '\x01')) {
              if (*(char *)(plVar9[2] + 0x50) == '\x01') {
                *(undefined1 *)(*plVar9 + 0x50) = 1;
                *(undefined1 *)(plVar9 + 10) = 0;
                FUN_14008e370((longlong)param_1,plVar9);
                plVar9 = (longlong *)plVar8[2];
              }
              *(char *)(plVar9 + 10) = (char)plVar8[10];
              *(undefined1 *)(plVar8 + 10) = 1;
              *(undefined1 *)(plVar9[2] + 0x50) = 1;
              FUN_14008e310((longlong)param_1,(longlong)plVar8);
              break;
            }
            *(undefined1 *)(plVar9 + 10) = 0;
          }
        }
        else {
          if ((char)plVar9[10] == '\0') {
            *(undefined1 *)(plVar9 + 10) = 1;
            *(undefined1 *)(plVar8 + 10) = 0;
            FUN_14008e370((longlong)param_1,plVar8);
            plVar9 = (longlong *)*plVar8;
          }
          if (*(char *)((longlong)plVar9 + 0x51) == '\0') {
            if ((*(char *)(plVar9[2] + 0x50) != '\x01') || (*(char *)(*plVar9 + 0x50) != '\x01')) {
              if (*(char *)(*plVar9 + 0x50) == '\x01') {
                *(undefined1 *)(plVar9[2] + 0x50) = 1;
                *(undefined1 *)(plVar9 + 10) = 0;
                FUN_14008e310((longlong)param_1,(longlong)plVar9);
                plVar9 = (longlong *)*plVar8;
              }
              *(char *)(plVar9 + 10) = (char)plVar8[10];
              *(undefined1 *)(plVar8 + 10) = 1;
              *(undefined1 *)(*plVar9 + 0x50) = 1;
              FUN_14008e370((longlong)param_1,plVar8);
              break;
            }
            *(undefined1 *)(plVar9 + 10) = 0;
          }
        }
        plVar9 = (longlong *)plVar8[1];
        plVar10 = plVar8;
      } while (plVar8 != *(longlong **)(param_1[6] + 8));
    }
    *(undefined1 *)(plVar10 + 10) = 1;
  }
  plVar9 = (longlong *)plVar3[9];
  if (plVar9 != (longlong *)0x0) {
    LOCK();
    plVar10 = plVar9 + 2;
    *(int *)plVar10 = (int)*plVar10 + -1;
    UNLOCK();
    if ((int)*plVar10 == 0) {
      (**(code **)*plVar9)(plVar9);
      LOCK();
      piVar1 = (int *)((longlong)plVar9 + 0x14);
      *piVar1 = *piVar1 + -1;
      UNLOCK();
      if (*piVar1 == 0) {
        (**(code **)(*plVar9 + 8))(plVar9);
      }
    }
  }
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (plVar3 + 3));
  operator_delete(plVar3);
  if (param_1[7] != 0) {
    param_1[7] = param_1[7] + -1;
  }
  lVar6 = param_3[1];
  *param_2 = *param_1;
  param_2[1] = lVar6;
  return param_2;
}


// ==== FUN_140091c70 @ 140091c70  undefined FUN_140091c70(longlong * param_1)

void FUN_140091c70(longlong *param_1)

{
  FUN_140091020(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140091ca0 @ 140091ca0  undefined FUN_140091ca0(longlong param_1, int * param_2)

void FUN_140091ca0(longlong param_1,int *param_2)

{
  int *piVar1;
  ulonglong local_res8 [4];
  
  local_res8[0] = (longlong)param_2[1] << 0x20 | (longlong)*param_2;
  piVar1 = (int *)FUN_140091480((longlong *)(param_1 + 0x18),(longlong *)local_res8);
  *piVar1 = param_2[2];
  return;
}


// ==== FUN_140091ce0 @ 140091ce0  undefined8 * FUN_140091ce0(undefined8 * param_1)

undefined8 * FUN_140091ce0(undefined8 *param_1)

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
  lVar2 = FUN_14008ef40();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x29) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_140091d60 @ 140091d60  undefined FUN_140091d60(undefined8 param_1, longlong * param_2, undefined8 param_3, undefined8 param_4)

void FUN_140091d60(undefined8 param_1,longlong *param_2,undefined8 param_3,undefined8 param_4)

{
  longlong *plVar1;
  int *piVar2;
  char cVar3;
  longlong *plVar4;
  longlong *plVar5;
  
  cVar3 = *(char *)((longlong)param_2 + 0x51);
  while (cVar3 == '\0') {
    FUN_140091d60(param_1,(longlong *)param_2[2],param_3,param_4);
    plVar4 = (longlong *)*param_2;
    plVar5 = (longlong *)param_2[9];
    if (plVar5 != (longlong *)0x0) {
      LOCK();
      plVar1 = plVar5 + 2;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)*plVar1 == 0) {
        (**(code **)*plVar5)(plVar5);
        LOCK();
        piVar2 = (int *)((longlong)plVar5 + 0x14);
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (*piVar2 == 0) {
          (**(code **)(*plVar5 + 8))(plVar5);
        }
      }
    }
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               (param_2 + 3));
    operator_delete(param_2);
    param_2 = plVar4;
    cVar3 = *(char *)((longlong)plVar4 + 0x51);
  }
  return;
}


// ==== FUN_140091e10 @ 140091e10  undefined FUN_140091e10(longlong param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void FUN_140091e10(longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  FUN_140091d60(param_1,*(longlong **)(*(longlong *)(param_1 + 0x30) + 8),param_3,param_4);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 8) = *(longlong *)(param_1 + 0x30);
  *(undefined8 *)(param_1 + 0x38) = 0;
  *(undefined8 *)*(undefined8 *)(param_1 + 0x30) = *(undefined8 *)(param_1 + 0x30);
  *(longlong *)(*(longlong *)(param_1 + 0x30) + 0x10) = *(longlong *)(param_1 + 0x30);
  return;
}


// ==== FUN_140091e50 @ 140091e50  longlong * FUN_140091e50(longlong * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_140091e50(longlong *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

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
      FUN_140091d60(param_1,*(longlong **)(param_1[6] + 8),plVar5,plVar6);
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
    FUN_140091870(param_1,local_18,&local_28);
  }
  lVar2 = param_3[1];
  *param_2 = *param_1;
  param_2[1] = lVar2;
  return param_2;
}


// ==== FUN_140092030 @ 140092030  undefined FUN_140092030(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_140092030(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  FUN_140091d60(&DAT_140104d10,*(longlong **)(DAT_140104d40 + 8),param_3,param_4);
  *(longlong *)(DAT_140104d40 + 8) = DAT_140104d40;
  _DAT_140104d48 = 0;
  *(longlong *)DAT_140104d40 = DAT_140104d40;
  *(longlong *)(DAT_140104d40 + 0x10) = DAT_140104d40;
  return;
}


// ==== FUN_140092080 @ 140092080  undefined FUN_140092080(longlong * param_1)

void FUN_140092080(longlong *param_1)

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
  FUN_140091e50(param_1,local_18,&local_28,&local_38);
  operator_delete((void *)param_1[6]);
  param_1[6] = 0;
  param_1[7] = 0;
  return;
}


// ==== FUN_1400920f0 @ 1400920f0  undefined FUN_1400920f0(longlong * param_1)

void FUN_1400920f0(longlong *param_1)

{
  FUN_140092080(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140092120 @ 140092120  undefined FUN_140092120(longlong * param_1)

void FUN_140092120(longlong *param_1)

{
  FUN_140092080(param_1);
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140092150 @ 140092150  undefined8 * FUN_140092150(undefined8 * param_1)

undefined8 * FUN_140092150(undefined8 *param_1)

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
  lVar2 = FUN_14008f020();
  param_1[6] = lVar2;
  *(undefined1 *)(lVar2 + 0x51) = 1;
  *(undefined8 *)(param_1[6] + 8) = param_1[6];
  *(undefined8 *)param_1[6] = param_1[6];
  *(undefined8 *)(param_1[6] + 0x10) = param_1[6];
  param_1[7] = 0;
  return param_1;
}


// ==== FUN_1400921d0 @ 1400921d0  undefined FUN_1400921d0(longlong param_1)

void FUN_1400921d0(longlong param_1)

{
  if (*(undefined8 **)(param_1 + 0x70) != (undefined8 *)0x0) {
    FUN_14008a680(*(undefined8 **)(param_1 + 0x70),*(undefined8 **)(param_1 + 0x78));
    operator_delete(*(void **)(param_1 + 0x70));
  }
  *(undefined8 *)(param_1 + 0x70) = 0;
  *(undefined8 *)(param_1 + 0x78) = 0;
  *(undefined8 *)(param_1 + 0x80) = 0;
  operator_delete(*(void **)(param_1 + 0x58));
  FUN_140091020((longlong *)(param_1 + 0x18));
  operator_delete(*(void **)(param_1 + 0x18));
  if (*(void **)(param_1 + 0x10) != (void *)0x0) {
    operator_delete__(*(void **)(param_1 + 0x10));
  }
  return;
}


// ==== FUN_140092270 @ 140092270  undefined4 * FUN_140092270(undefined4 * param_1)

undefined4 * FUN_140092270(undefined4 *param_1)

{
  longlong *plVar1;
  longlong *plVar2;
  
  plVar2 = (longlong *)0x0;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  *(undefined8 *)(param_1 + 4) = 0;
  FUN_140091ce0((undefined8 *)(param_1 + 6));
  plVar1 = (longlong *)operator_new(8);
  if (plVar1 != (longlong *)0x0) {
    *plVar1 = (longlong)(param_1 + 0x16);
    plVar2 = plVar1;
  }
  *(longlong **)(param_1 + 0x16) = plVar2;
  *(undefined8 *)(param_1 + 0x1c) = 0;
  *(undefined8 *)(param_1 + 0x1e) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  return param_1;
}


// ==== FUN_1400922f0 @ 1400922f0  void * FUN_1400922f0(void * param_1, uint param_2)

void * FUN_1400922f0(void *param_1,uint param_2)

{
  FUN_1400921d0((longlong)param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_140092350 @ 140092350  undefined8 FUN_140092350(int * param_1, longlong * param_2)

undefined8 FUN_140092350(int *param_1,longlong *param_2)

{
  longlong *plVar1;
  int *piVar2;
  undefined8 *puVar3;
  undefined2 *puVar4;
  undefined2 *puVar5;
  ushort uVar6;
  short sVar7;
  undefined2 uVar8;
  int iVar9;
  uint uVar10;
  undefined8 *puVar11;
  ulonglong *puVar12;
  undefined6 extraout_var;
  longlong *plVar13;
  ulonglong extraout_RAX;
  ulonglong uVar14;
  longlong lVar15;
  int iVar16;
  int iVar17;
  longlong lVar18;
  int iVar19;
  int local_154;
  uint local_150;
  int local_14c;
  undefined2 *local_148;
  longlong *local_140;
  int local_138;
  undefined8 local_130;
  longlong local_128;
  longlong *local_120;
  undefined2 *local_118;
  longlong *local_110;
  longlong local_108;
  undefined8 local_100;
  longlong local_f8;
  longlong local_e8;
  undefined8 *puStack_e0;
  longlong local_d8;
  undefined8 *puStack_d0;
  longlong *local_c8 [3];
  undefined8 local_b0;
  undefined8 local_a8;
  undefined8 local_a0;
  longlong **local_98;
  longlong local_88;
  undefined8 *puStack_80;
  undefined8 local_78;
  longlong local_68;
  undefined8 *puStack_60;
  longlong *local_58;
  longlong *local_50;
  
  local_78 = 0xfffffffffffffffe;
  puVar11 = (undefined8 *)FUN_140094a50(*param_2);
  local_138 = (int)puVar11;
  local_14c = 0;
  if (0 < local_138) {
    do {
      FUN_140095250(*param_2,&local_128,local_14c);
      puVar12 = (ulonglong *)FUN_140093ba0(local_128);
      uVar14 = *puVar12;
      local_100 = uVar14;
      puVar11 = (undefined8 *)FUN_140093bc0(local_128);
      local_130 = *puVar11;
      local_154 = 0;
      iVar17 = (int)local_130;
      if (0 < iVar17) {
        do {
          puVar11 = (undefined8 *)0x0;
          local_150 = 0;
          iVar16 = (int)uVar14;
          if (0 < local_130._4_4_) {
            iVar19 = local_100._4_4_;
            do {
              uVar10 = (uint)puVar11;
              if ((((-1 < iVar16) && (-1 < iVar19)) && (iVar16 < *param_1)) && (iVar19 < param_1[1])
                 ) {
                FUN_140093f60(local_128,&local_118,local_154,uVar10);
                FUN_140093af0(&local_148);
                puVar5 = local_118;
                puVar4 = local_148;
                if (local_148 == (undefined2 *)0x0) {
                  log_InlineLogERROR("CMapStaticData cannot create layer data");
                  uVar14 = extraout_RAX;
                  if (local_140 != (longlong *)0x0) {
                    LOCK();
                    plVar13 = local_140 + 2;
                    lVar15 = *plVar13;
                    *(int *)plVar13 = (int)*plVar13 + -1;
                    UNLOCK();
                    uVar10 = (int)lVar15 - 1;
                    uVar14 = (ulonglong)uVar10;
                    if (uVar10 == 0) {
                      (**(code **)*local_140)(local_140);
                      LOCK();
                      piVar2 = (int *)((longlong)local_140 + 0x14);
                      iVar17 = *piVar2;
                      *piVar2 = *piVar2 + -1;
                      UNLOCK();
                      uVar14 = (ulonglong)(iVar17 - 1U);
                      if (iVar17 - 1U == 0) {
                        uVar14 = (**(code **)(*local_140 + 8))(local_140);
                      }
                    }
                  }
                  if (local_110 != (longlong *)0x0) {
                    LOCK();
                    plVar13 = local_110 + 2;
                    lVar15 = *plVar13;
                    *(int *)plVar13 = (int)*plVar13 + -1;
                    UNLOCK();
                    uVar10 = (int)lVar15 - 1;
                    uVar14 = (ulonglong)uVar10;
                    if (uVar10 == 0) {
                      (**(code **)*local_110)(local_110);
                      LOCK();
                      piVar2 = (int *)((longlong)local_110 + 0x14);
                      iVar17 = *piVar2;
                      *piVar2 = *piVar2 + -1;
                      UNLOCK();
                      uVar14 = (ulonglong)(iVar17 - 1U);
                      if (iVar17 - 1U == 0) {
                        uVar14 = (**(code **)(*local_110 + 8))(local_110);
                      }
                    }
                  }
                  if (local_120 != (longlong *)0x0) {
                    LOCK();
                    plVar13 = local_120 + 2;
                    lVar15 = *plVar13;
                    *(int *)plVar13 = (int)*plVar13 + -1;
                    UNLOCK();
                    uVar10 = (int)lVar15 - 1;
                    uVar14 = (ulonglong)uVar10;
                    if (uVar10 == 0) {
                      (**(code **)*local_120)(local_120);
                      LOCK();
                      piVar2 = (int *)((longlong)local_120 + 0x14);
                      iVar17 = *piVar2;
                      *piVar2 = *piVar2 + -1;
                      UNLOCK();
                      uVar14 = (ulonglong)(iVar17 - 1U);
                      if (iVar17 - 1U == 0) {
                        uVar14 = (**(code **)(*local_120 + 8))(local_120);
                      }
                    }
                  }
                  plVar13 = (longlong *)param_2[1];
                  if (plVar13 != (longlong *)0x0) {
                    LOCK();
                    plVar1 = plVar13 + 2;
                    lVar15 = *plVar1;
                    *(int *)plVar1 = (int)*plVar1 + -1;
                    UNLOCK();
                    uVar10 = (int)lVar15 - 1;
                    uVar14 = (ulonglong)uVar10;
                    if (uVar10 == 0) {
                      uVar14 = (**(code **)*plVar13)(plVar13);
                      LOCK();
                      piVar2 = (int *)((longlong)plVar13 + 0x14);
                      iVar17 = *piVar2;
                      *piVar2 = *piVar2 + -1;
                      UNLOCK();
                      if (iVar17 == 1) {
                        uVar14 = (**(code **)(*plVar13 + 8))(plVar13);
                      }
                    }
                  }
                  return uVar14 & 0xffffffffffffff00;
                }
                uVar6 = FUN_1400902e0(param_1,iVar16,iVar19);
                sVar7 = FUN_140093910(puVar5);
                FUN_140093940(puVar4,sVar7 + uVar6);
                puVar4 = local_148;
                uVar8 = FUN_140093920((longlong)local_118);
                FUN_140093950((longlong)puVar4,uVar8);
                puVar4 = local_148;
                uVar8 = FUN_140093930((longlong)local_118);
                FUN_140093960((longlong)puVar4,uVar8);
                local_f8 = *(longlong *)(param_1 + 4) + (longlong)(iVar19 * *param_1 + iVar16) * 4;
                uVar8 = FUN_1400967a0(local_f8);
                iVar9 = (int)CONCAT62(extraout_var,uVar8);
                if (iVar9 == 0xffff) {
                  lVar15 = (*(longlong *)(param_1 + 0x1e) - *(longlong *)(param_1 + 0x1c)) / 6 +
                           (*(longlong *)(param_1 + 0x1e) - *(longlong *)(param_1 + 0x1c) >> 0x3f);
                  lVar15 = (lVar15 >> 3) - (lVar15 >> 0x3f);
                  local_98 = local_c8;
                  local_108 = lVar15;
                  local_58 = (longlong *)operator_new(8);
                  if (local_58 == (longlong *)0x0) {
                    local_c8[0] = (longlong *)0x0;
                  }
                  else {
                    *local_58 = (longlong)local_c8;
                    local_c8[0] = local_58;
                  }
                  local_b0 = 0;
                  local_a8 = 0;
                  local_a0 = 0;
                  local_50 = local_58;
                  FUN_14008bb20((longlong *)(param_1 + 0x16),(longlong)((int)lVar15 + 1),local_c8);
                  plVar13 = (longlong *)FUN_140083e50((longlong *)(param_1 + 0x16));
                  puVar11 = (undefined8 *)plVar13[3];
                  if (puVar11 == (undefined8 *)0x0) {
                    uVar14 = 0;
                  }
                  else {
                    uVar14 = plVar13[5] - (longlong)puVar11 >> 4;
                  }
                  puVar3 = (undefined8 *)plVar13[4];
                  if ((ulonglong)((longlong)puVar3 - (longlong)puVar11 >> 4) < uVar14) {
                    FUN_140085740(puVar3,1,&local_148);
                    plVar13[4] = (longlong)(puVar3 + 2);
                  }
                  else {
                    if (puVar3 < puVar11) {
                      _invalid_parameter_noinfo();
                    }
                    lVar15 = *plVar13;
                    uVar14 = plVar13[3];
                    local_d8 = lVar15;
                    puStack_d0 = puVar3;
                    if ((plVar13[4] - uVar14 & 0xfffffffffffffff0) == 0) {
                      lVar15 = 0;
                    }
                    else {
                      if ((ulonglong)plVar13[4] < uVar14) {
                        _invalid_parameter_noinfo();
                      }
                      if ((lVar15 == 0) || (lVar15 != *plVar13)) {
                        _invalid_parameter_noinfo();
                      }
                      lVar15 = (longlong)((longlong)puVar3 - uVar14) >> 4;
                    }
                    local_88 = local_d8;
                    puStack_80 = puStack_d0;
                    FUN_140087110((longlong)plVar13,(longlong)&local_88,1,(longlong *)&local_148);
                    uVar14 = plVar13[3];
                    if ((ulonglong)plVar13[4] < uVar14) {
                      _invalid_parameter_noinfo();
                    }
                    plVar13 = (longlong *)*plVar13;
                    if (plVar13 == (longlong *)0x0) {
                      _invalid_parameter_noinfo();
                      lVar18 = 0;
                    }
                    else {
                      lVar18 = *plVar13;
                    }
                    uVar14 = uVar14 + lVar15 * 0x10;
                    if (uVar14 <= *(ulonglong *)(lVar18 + 0x20)) {
                      if (plVar13 == (longlong *)0x0) {
                        lVar15 = 0;
                      }
                      else {
                        lVar15 = *plVar13;
                      }
                      if (*(ulonglong *)(lVar15 + 0x18) <= uVar14) goto LAB_1400926f4;
                    }
                    _invalid_parameter_noinfo();
                  }
LAB_1400926f4:
                  FUN_1400967c0(local_f8,(short)local_108);
                }
                else {
                  if ((ulonglong)
                      ((*(longlong *)(param_1 + 0x1e) - *(longlong *)(param_1 + 0x1c)) / 0x30) <=
                      (ulonglong)(longlong)iVar9) {
                    _invalid_parameter_noinfo();
                  }
                  plVar13 = (longlong *)((longlong)iVar9 * 0x30 + *(longlong *)(param_1 + 0x1c));
                  puVar11 = (undefined8 *)plVar13[3];
                  if (puVar11 == (undefined8 *)0x0) {
                    uVar14 = 0;
                  }
                  else {
                    uVar14 = plVar13[5] - (longlong)puVar11 >> 4;
                  }
                  puVar3 = (undefined8 *)plVar13[4];
                  if ((ulonglong)((longlong)puVar3 - (longlong)puVar11 >> 4) < uVar14) {
                    FUN_140085740(puVar3,1,&local_148);
                    plVar13[4] = (longlong)(puVar3 + 2);
                  }
                  else {
                    if (puVar3 < puVar11) {
                      _invalid_parameter_noinfo();
                    }
                    lVar15 = *plVar13;
                    uVar14 = plVar13[3];
                    local_e8 = lVar15;
                    puStack_e0 = puVar3;
                    if ((plVar13[4] - uVar14 & 0xfffffffffffffff0) == 0) {
                      lVar15 = 0;
                    }
                    else {
                      if ((ulonglong)plVar13[4] < uVar14) {
                        _invalid_parameter_noinfo();
                      }
                      if ((lVar15 == 0) || (lVar15 != *plVar13)) {
                        _invalid_parameter_noinfo();
                      }
                      lVar15 = (longlong)((longlong)puVar3 - uVar14) >> 4;
                    }
                    local_68 = local_e8;
                    puStack_60 = puStack_e0;
                    FUN_140087110((longlong)plVar13,(longlong)&local_68,1,(longlong *)&local_148);
                    uVar14 = plVar13[3];
                    if ((ulonglong)plVar13[4] < uVar14) {
                      _invalid_parameter_noinfo();
                    }
                    plVar13 = (longlong *)*plVar13;
                    if (plVar13 == (longlong *)0x0) {
                      _invalid_parameter_noinfo();
                      lVar18 = 0;
                    }
                    else {
                      lVar18 = *plVar13;
                    }
                    uVar14 = uVar14 + lVar15 * 0x10;
                    if (uVar14 <= *(ulonglong *)(lVar18 + 0x20)) {
                      if (plVar13 == (longlong *)0x0) {
                        lVar15 = 0;
                      }
                      else {
                        lVar15 = *plVar13;
                      }
                      if (*(ulonglong *)(lVar15 + 0x18) <= uVar14) goto LAB_140092889;
                    }
                    _invalid_parameter_noinfo();
                  }
                }
LAB_140092889:
                plVar13 = local_140;
                if (local_140 != (longlong *)0x0) {
                  LOCK();
                  plVar1 = local_140 + 2;
                  *(int *)plVar1 = (int)*plVar1 + -1;
                  UNLOCK();
                  if ((int)*plVar1 == 0) {
                    (**(code **)*local_140)(local_140);
                    LOCK();
                    piVar2 = (int *)((longlong)plVar13 + 0x14);
                    *piVar2 = *piVar2 + -1;
                    UNLOCK();
                    if (*piVar2 == 0) {
                      (**(code **)(*plVar13 + 8))(plVar13);
                    }
                  }
                }
                plVar13 = local_110;
                uVar10 = local_150;
                if (local_110 != (longlong *)0x0) {
                  LOCK();
                  plVar1 = local_110 + 2;
                  lVar15 = *plVar1;
                  *(int *)plVar1 = (int)*plVar1 + -1;
                  UNLOCK();
                  if ((int)lVar15 == 1) {
                    (**(code **)*local_110)(local_110);
                    LOCK();
                    piVar2 = (int *)((longlong)plVar13 + 0x14);
                    iVar9 = *piVar2;
                    *piVar2 = *piVar2 + -1;
                    UNLOCK();
                    if (iVar9 == 1) {
                      (**(code **)(*plVar13 + 8))(plVar13);
                    }
                  }
                }
              }
              local_150 = uVar10 + 1;
              puVar11 = (undefined8 *)(ulonglong)local_150;
              iVar19 = iVar19 + -1;
            } while ((int)local_150 < local_130._4_4_);
          }
          local_154 = local_154 + 1;
          uVar14 = (ulonglong)(iVar16 - 1);
        } while (local_154 < iVar17);
      }
      plVar13 = local_120;
      if (local_120 != (longlong *)0x0) {
        LOCK();
        plVar1 = local_120 + 2;
        lVar15 = *plVar1;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        uVar10 = (int)lVar15 - 1;
        puVar11 = (undefined8 *)(ulonglong)uVar10;
        if (uVar10 == 0) {
          (**(code **)*local_120)(local_120);
          LOCK();
          piVar2 = (int *)((longlong)plVar13 + 0x14);
          iVar17 = *piVar2;
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          puVar11 = (undefined8 *)(ulonglong)(iVar17 - 1U);
          if (iVar17 - 1U == 0) {
            puVar11 = (undefined8 *)(**(code **)(*plVar13 + 8))(plVar13);
          }
        }
      }
      local_14c = local_14c + 1;
    } while (local_14c < local_138);
  }
  plVar13 = (longlong *)param_2[1];
  if (plVar13 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar13 + 2;
    lVar15 = *plVar1;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    uVar10 = (int)lVar15 - 1;
    puVar11 = (undefined8 *)(ulonglong)uVar10;
    if (uVar10 == 0) {
      puVar11 = (undefined8 *)(**(code **)*plVar13)(plVar13);
      LOCK();
      piVar2 = (int *)((longlong)plVar13 + 0x14);
      iVar17 = *piVar2;
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (iVar17 == 1) {
        puVar11 = (undefined8 *)(**(code **)(*plVar13 + 8))(plVar13);
      }
    }
  }
  return CONCAT71((int7)((ulonglong)puVar11 >> 8),1);
}


// ==== FUN_140092b10 @ 140092b10  undefined FUN_140092b10(uint * param_1, char * param_2)

/* WARNING: Removing unreachable block (ram,0x000140092f60) */
/* WARNING: Removing unreachable block (ram,0x000140092f6c) */
/* WARNING: Removing unreachable block (ram,0x000140092f80) */

void FUN_140092b10(uint *param_1,char *param_2)

{
  uint *puVar1;
  longlong *plVar2;
  int *piVar3;
  longlong *plVar4;
  char cVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  ulonglong uVar9;
  undefined8 *puVar10;
  undefined8 uVar11;
  longlong lVar12;
  int iVar13;
  int iVar14;
  char *pcVar15;
  undefined1 auStack_328 [32];
  undefined4 local_308;
  longlong local_2f8;
  int local_2f0;
  uint local_2ec;
  short local_2e8;
  undefined4 local_2e4;
  short local_2e0;
  undefined4 local_2dc;
  longlong *local_2d8;
  longlong *local_2d0;
  longlong *local_2c8;
  longlong *local_2c0;
  int local_2b8;
  int local_2b4;
  undefined4 local_2b0;
  ulonglong local_2a8;
  longlong **local_2a0;
  undefined8 local_298;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_290 [40];
  char local_268;
  undefined1 local_267 [271];
  char local_158;
  undefined1 local_157 [271];
  ulonglong local_48;
  
  local_298 = 0xfffffffffffffffe;
  local_48 = DAT_140103510 ^ (ulonglong)auStack_328;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_290,param_2);
  FUN_140096e70(&local_2f8,local_290);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_290);
  uVar9 = FUN_140096950(&local_2f8);
  if ((char)uVar9 == '\0') {
    log_InlineLogERROR("CMapStaticData cannot open file %s",param_2);
    FUN_140096930(&local_2f8);
  }
  else {
    FUN_140096970(&local_2f8);
    FUN_140096970(&local_2f8);
    FUN_140096970(&local_2f8);
    puVar1 = param_1 + 1;
    FUN_140096970(&local_2f8);
    uVar6 = *param_1;
    uVar7 = *puVar1;
    if (uVar6 == uVar7) {
      bVar8 = FUN_14008d830((int *)(param_1 + 2),uVar7 * uVar6);
      if (bVar8) {
        iVar13 = 0;
        if (0 < (int)*puVar1) {
          do {
            iVar14 = 0;
            if (0 < (int)*param_1) {
              do {
                FUN_140096970(&local_2f8);
                FUN_140096970(&local_2f8);
                FUN_140096970(&local_2f8);
                FUN_140096770((ushort *)
                              (*(longlong *)(param_1 + 4) +
                              (longlong)(int)(*param_1 * iVar13 + iVar14) * 4),local_2e8,
                              local_2e0 != 0);
                iVar14 = iVar14 + 1;
              } while (iVar14 < (int)*param_1);
            }
            FUN_140096970(&local_2f8);
            iVar13 = iVar13 + 1;
          } while (iVar13 < (int)*puVar1);
        }
        FUN_140096970(&local_2f8);
        iVar13 = 0;
        if (0 < local_2f0) {
          do {
            FUN_140096970(&local_2f8);
            local_2a8 = (longlong)local_2b4 << 0x20 | (longlong)local_2b8;
            puVar10 = FUN_140091480((longlong *)(param_1 + 6),(longlong *)&local_2a8);
            *(undefined4 *)puVar10 = local_2b0;
            iVar13 = iVar13 + 1;
          } while (iVar13 < local_2f0);
        }
        local_158 = '\0';
        memset(local_157,0,0x103);
        lVar12 = -1;
        pcVar15 = param_2;
        do {
          if (lVar12 == 0) break;
          lVar12 = lVar12 + -1;
          cVar5 = *pcVar15;
          pcVar15 = pcVar15 + 1;
        } while (cVar5 != '\0');
        iVar13 = ~(uint)lVar12 - 2;
        lVar12 = (longlong)iVar13;
        if (-1 < iVar13) {
          do {
            if ((param_2[lVar12] == '.') && (3 < iVar13)) {
              strncpy(&local_158,param_2 + (iVar13 + -4),4);
              break;
            }
            iVar13 = iVar13 + -1;
            lVar12 = lVar12 + -1;
          } while (-1 < lVar12);
        }
        _stricmp(&local_158,"_new");
        FUN_140096970(&local_2f8);
        iVar13 = 0;
        if (0 < local_2f0) {
          do {
            FUN_140096970(&local_2f8);
            switch(local_2dc) {
            case 1:
              local_2ec = 0;
              local_2e4 = 0;
              local_268 = '\0';
              memset(local_267,0,0x103);
              FUN_140096970(&local_2f8);
              FUN_140096970(&local_2f8);
              FUN_140096970(&local_2f8);
              FUN_140096390(&local_2c8,&local_268,0);
              if (local_2c8 == (longlong *)0x0) {
                log_InlineLogERROR("CMapStaticData file %s cannot create terrain from file %s",
                                   param_2,&local_268);
                if (local_2c0 != (longlong *)0x0) {
                  LOCK();
                  plVar4 = local_2c0 + 2;
                  lVar12 = *plVar4;
                  *(int *)plVar4 = (int)*plVar4 + -1;
                  UNLOCK();
                  if ((int)lVar12 == 1) {
                    (**(code **)*local_2c0)(local_2c0);
                    LOCK();
                    piVar3 = (int *)((longlong)local_2c0 + 0x14);
                    iVar13 = *piVar3;
                    *piVar3 = *piVar3 + -1;
                    UNLOCK();
                    if (iVar13 == 1) {
                      (**(code **)(*local_2c0 + 8))(local_2c0);
                    }
                  }
                }
                FUN_140096930(&local_2f8);
                goto LAB_1400931aa;
              }
              (**(code **)(*local_2c8 + 8))(local_2c8,local_2ec,local_2e4);
              local_2a0 = &local_2d8;
              if (local_2c0 != (longlong *)0x0) {
                LOCK();
                *(int *)(local_2c0 + 2) = (int)local_2c0[2] + 1;
                UNLOCK();
              }
              local_2d0 = local_2c0;
              local_2d8 = local_2c8;
              uVar11 = FUN_140092350((int *)param_1,(longlong *)&local_2d8);
              plVar4 = local_2c0;
              if ((char)uVar11 == '\0') {
                local_308 = local_2e4;
                log_InlineLogERROR("CMapStaticData file %s cannot add obj from %s to (%d, %d)",
                                   param_2,&local_268,(ulonglong)local_2ec);
                if (local_2c0 != (longlong *)0x0) {
                  LOCK();
                  plVar4 = local_2c0 + 2;
                  lVar12 = *plVar4;
                  *(int *)plVar4 = (int)*plVar4 + -1;
                  UNLOCK();
                  if ((int)lVar12 == 1) {
                    (**(code **)*local_2c0)(local_2c0);
                    LOCK();
                    piVar3 = (int *)((longlong)local_2c0 + 0x14);
                    iVar13 = *piVar3;
                    *piVar3 = *piVar3 + -1;
                    UNLOCK();
                    if (iVar13 == 1) {
                      (**(code **)(*local_2c0 + 8))(local_2c0);
                    }
                  }
                }
                FUN_140096930(&local_2f8);
                goto LAB_1400931aa;
              }
              if (local_2c0 != (longlong *)0x0) {
                LOCK();
                plVar2 = local_2c0 + 2;
                lVar12 = *plVar2;
                *(int *)plVar2 = (int)*plVar2 + -1;
                UNLOCK();
                if ((int)lVar12 == 1) {
                  (**(code **)*local_2c0)(local_2c0);
                  LOCK();
                  piVar3 = (int *)((longlong)plVar4 + 0x14);
                  iVar14 = *piVar3;
                  *piVar3 = *piVar3 + -1;
                  UNLOCK();
                  if (iVar14 == 1) {
                    (**(code **)(*plVar4 + 8))(plVar4);
                  }
                }
              }
              break;
            default:
              log_InlineLogERROR("CMapStaticData file %s has a unknown map object type %d",param_2);
              FUN_140096930(&local_2f8);
              goto LAB_1400931aa;
            case 3:
              FUN_140096970(&local_2f8);
              break;
            case 4:
              FUN_140096970(&local_2f8);
              break;
            case 10:
              FUN_140096970(&local_2f8);
              break;
            case 0xf:
              FUN_140096970(&local_2f8);
              break;
            case 0x13:
              FUN_140096970(&local_2f8);
            }
            iVar13 = iVar13 + 1;
          } while (iVar13 < local_2f0);
        }
        FUN_140096930(&local_2f8);
      }
      else {
        log_InlineLogERROR("CMapStaticData file %s cannot create cells(%d, %d)",param_2,
                           (ulonglong)*param_1,(ulonglong)*puVar1);
        FUN_140096930(&local_2f8);
      }
    }
    else {
      log_InlineLogERROR("CMapStaticData file %s has a bad size(%d, %d)",param_2,(ulonglong)uVar6,
                         (ulonglong)uVar7);
      FUN_140096930(&local_2f8);
    }
  }
LAB_1400931aa:
  __security_check_cookie(local_48 ^ (ulonglong)auStack_328);
  return;
}


// ==== FUN_140093230 @ 140093230  undefined FUN_140093230(undefined8 * param_1, undefined8 param_2)

void FUN_140093230(undefined8 *param_1,undefined8 param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x18);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = std::tr1::_Ref_count_base::vftable;
    puVar1[1] = param_2;
    *(undefined4 *)(puVar1 + 2) = 0;
    *(undefined4 *)((longlong)puVar1 + 0x14) = 1;
    *puVar1 = std::tr1::_Ref_count<class_CMapStaticData>::vftable;
  }
  FUN_140081910(param_1,param_2,(longlong)puVar1);
  return;
}


// ==== FUN_1400932b0 @ 1400932b0  undefined8 * FUN_1400932b0(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_1400932b0(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_140093230(param_1,param_2);
  return param_1;
}


// ==== FUN_1400932d0 @ 1400932d0  undefined FUN_1400932d0(undefined8 * param_1, uint param_2, char * param_3, int param_4)

void FUN_1400932d0(undefined8 *param_1,uint param_2,char *param_3,int param_4)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  char *pcVar4;
  bool bVar5;
  char cVar6;
  int iVar7;
  longlong *plVar8;
  undefined8 *puVar9;
  undefined4 *puVar10;
  char *pcVar11;
  longlong **pplVar12;
  longlong *plVar13;
  longlong lVar14;
  uint *puVar15;
  undefined1 auStack_2a8 [32];
  int local_288;
  undefined4 local_278;
  uint *local_270;
  longlong *local_268;
  uint local_260;
  longlong *local_258;
  longlong *local_250;
  longlong *local_248;
  longlong *local_240;
  longlong *local_238;
  longlong *local_230;
  undefined8 local_228;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_220 [40];
  undefined8 local_1f8;
  longlong *local_1f0;
  undefined8 *local_1e8;
  longlong local_1b0 [3];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_198 [48];
  char local_168 [272];
  ulonglong local_58;
  
  local_228 = 0xfffffffffffffffe;
  local_58 = DAT_140103510 ^ (ulonglong)auStack_2a8;
  local_278 = 0;
  local_260 = param_2;
  local_1e8 = param_1;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_198,param_3);
  plVar8 = (longlong *)
           std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::begin
                     (local_198);
  local_258 = (longlong *)*plVar8;
  local_250 = (longlong *)plVar8[1];
  puVar9 = (undefined8 *)
           std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::end
                     (local_198);
  local_248 = (longlong *)*puVar9;
  local_240 = (longlong *)puVar9[1];
  puVar9 = (undefined8 *)
           std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::begin
                     (local_198);
  plVar13 = local_240;
  plVar3 = local_250;
  plVar1 = local_258;
  local_238 = (longlong *)*puVar9;
  plVar8 = (longlong *)puVar9[1];
  local_230 = plVar8;
  if (local_258 != (longlong *)0xfffffffffffffffc) {
    if (local_258 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
    }
    if (*(ulonglong *)((longlong)plVar1 + 0x20) < 0x10) {
      lVar14 = (longlong)plVar1 + 8;
    }
    else {
      lVar14 = *(longlong *)((longlong)plVar1 + 8);
    }
    pcVar11 = (char *)((longlong)plVar1 + 8);
    pcVar4 = (char *)((longlong)plVar13 + ((longlong)plVar3 - (longlong)plVar8));
    if (pcVar4 <= (char *)(lVar14 + *(longlong *)((longlong)plVar1 + 0x18))) {
      if (0xf < *(ulonglong *)((longlong)plVar1 + 0x20)) {
        pcVar11 = *(char **)pcVar11;
      }
      if (pcVar11 <= pcVar4) goto LAB_14009341b;
    }
    _invalid_parameter_noinfo();
  }
LAB_14009341b:
  if (plVar8 != plVar13) {
    lVar14 = (longlong)plVar3 - (longlong)plVar8;
    do {
      iVar7 = tolower((int)(char)*plVar8);
      *(char *)(lVar14 + (longlong)plVar8) = (char)iVar7;
      plVar8 = (longlong *)((longlong)plVar8 + 1);
    } while (plVar8 != plVar13);
  }
  cVar6 = *(char *)(DAT_140104d40[1] + 0x51);
  plVar8 = (longlong *)DAT_140104d40[1];
  plVar1 = DAT_140104d40;
  plVar3 = DAT_140104d40;
  while (plVar13 = plVar8, DAT_140104d40 = plVar3, cVar6 == '\0') {
    bVar5 = std::operator<<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                      ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                        *)(plVar13 + 3),local_198);
    if (bVar5) {
      plVar8 = (longlong *)plVar13[2];
      plVar13 = plVar1;
    }
    else {
      plVar8 = (longlong *)*plVar13;
    }
    cVar6 = *(char *)((longlong)plVar8 + 0x51);
    plVar1 = plVar13;
    plVar3 = DAT_140104d40;
  }
  local_230 = plVar1;
  local_238 = DAT_140104d10;
  if (DAT_140104d10 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
  }
  if ((plVar1 == plVar3) ||
     (bVar5 = std::operator<<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                        (local_198,
                         (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                          *)(plVar1 + 3)), bVar5)) {
    local_240 = DAT_140104d40;
    local_248 = DAT_140104d10;
    pplVar12 = &local_248;
  }
  else {
    pplVar12 = &local_238;
  }
  plVar1 = DAT_140104d40;
  plVar8 = *pplVar12;
  local_250 = pplVar12[1];
  local_258 = plVar8;
  if ((plVar8 == (longlong *)0x0) || (plVar8 != DAT_140104d10)) {
    _invalid_parameter_noinfo();
  }
  plVar3 = local_250;
  if (local_250 == plVar1) {
    local_270 = (uint *)operator_new(0x88);
    if (local_270 == (uint *)0x0) {
      puVar10 = (undefined4 *)0x0;
    }
    else {
      puVar10 = FUN_140092270(local_270);
    }
    local_270 = (uint *)0x0;
    local_268 = (longlong *)0x0;
    FUN_140093230(&local_270,puVar10);
    puVar15 = local_270;
    if (local_270 == (uint *)0x0) {
      log_InlineLogERROR("CMapStaticData cannot create map data");
      *param_1 = 0;
      param_1[1] = 0;
      FUN_14008e9c0(param_1);
      plVar8 = local_268;
      local_278 = 1;
      if (local_268 != (longlong *)0x0) {
        LOCK();
        plVar1 = local_268 + 2;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)*plVar1 == 0) {
          (**(code **)*local_268)(local_268);
          LOCK();
          piVar2 = (int *)((longlong)plVar8 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*local_268 + 8))();
          }
        }
      }
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_198);
    }
    else {
      cVar6 = FUN_140092b10(local_270,param_3);
      if (cVar6 == '\0') {
        log_InlineLogERROR("CMapStaticData cannot load map %d from file %s",(ulonglong)local_260,
                           param_3);
        *param_1 = 0;
        param_1[1] = 0;
        FUN_14008e9c0(param_1);
        plVar8 = local_268;
        local_278 = 1;
        if (local_268 != (longlong *)0x0) {
          LOCK();
          plVar1 = local_268 + 2;
          *(int *)plVar1 = (int)*plVar1 + -1;
          UNLOCK();
          if ((int)*plVar1 == 0) {
            (**(code **)*local_268)(local_268);
            LOCK();
            piVar2 = (int *)((longlong)plVar8 + 0x14);
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (*piVar2 == 0) {
              (**(code **)(*local_268 + 8))();
            }
          }
        }
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_198);
      }
      else {
        iVar7 = _stricmp("none",local_168);
        if ((iVar7 == 0) || (cVar6 = FUN_140090890((int *)puVar15,local_168,param_4), cVar6 != '\0')
           ) {
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                    (local_220,local_198);
          plVar8 = local_268;
          local_1f8 = 0;
          local_1f0 = (longlong *)0x0;
          FUN_140081910(&local_1f8,puVar15,(longlong)local_268);
          FUN_1400915b0((longlong *)&DAT_140104d10,local_1b0,local_220);
          plVar1 = local_1f0;
          if (local_1f0 != (longlong *)0x0) {
            LOCK();
            plVar3 = local_1f0 + 2;
            *(int *)plVar3 = (int)*plVar3 + -1;
            UNLOCK();
            plVar8 = local_268;
            puVar15 = local_270;
            if ((int)*plVar3 == 0) {
              (**(code **)*local_1f0)(local_1f0);
              LOCK();
              piVar2 = (int *)((longlong)plVar1 + 0x14);
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              plVar8 = local_268;
              puVar15 = local_270;
              if (*piVar2 == 0) {
                (**(code **)(*plVar1 + 8))(plVar1);
                plVar8 = local_268;
                puVar15 = local_270;
              }
            }
          }
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_220);
          *param_1 = 0;
          param_1[1] = 0;
          FUN_140081910(param_1,puVar15,(longlong)plVar8);
          plVar1 = local_268;
          local_278 = 1;
          if (plVar8 != (longlong *)0x0) {
            LOCK();
            plVar8 = plVar8 + 2;
            *(int *)plVar8 = (int)*plVar8 + -1;
            UNLOCK();
            if ((int)*plVar8 == 0) {
              (**(code **)*local_268)(local_268);
              LOCK();
              piVar2 = (int *)((longlong)plVar1 + 0x14);
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (*piVar2 == 0) {
                (**(code **)(*local_268 + 8))();
              }
            }
          }
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_198);
        }
        else {
          local_288 = param_4;
          log_InlineLogERROR("CMapStaticData map %d (%s) cannot load puzzle %s, blocksize=%d",
                             (ulonglong)local_260,param_3,local_168);
          *param_1 = 0;
          param_1[1] = 0;
          FUN_14008e9c0(param_1);
          plVar8 = local_268;
          local_278 = 1;
          if (local_268 != (longlong *)0x0) {
            LOCK();
            plVar1 = local_268 + 2;
            *(int *)plVar1 = (int)*plVar1 + -1;
            UNLOCK();
            if ((int)*plVar1 == 0) {
              (**(code **)*local_268)(local_268);
              LOCK();
              piVar2 = (int *)((longlong)plVar8 + 0x14);
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (*piVar2 == 0) {
                (**(code **)(*local_268 + 8))();
              }
            }
          }
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_198);
        }
      }
    }
  }
  else {
    if (plVar8 == (longlong *)0x0) {
      _invalid_parameter_noinfo();
      lVar14 = 0;
    }
    else {
      lVar14 = *plVar8;
    }
    if (plVar3 == *(longlong **)(lVar14 + 0x30)) {
      _invalid_parameter_noinfo();
    }
    plVar8 = (longlong *)plVar3[9];
    local_258 = (longlong *)plVar3[8];
    if (plVar8 != (longlong *)0x0) {
      LOCK();
      *(int *)(plVar8 + 2) = (int)plVar8[2] + 1;
      UNLOCK();
    }
    *param_1 = 0;
    param_1[1] = 0;
    local_250 = plVar8;
    FUN_140081910(param_1,local_258,(longlong)plVar8);
    local_278 = 1;
    if (plVar8 != (longlong *)0x0) {
      LOCK();
      plVar1 = plVar8 + 2;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)*plVar1 == 0) {
        (**(code **)*plVar8)(plVar8);
        LOCK();
        piVar2 = (int *)((longlong)plVar8 + 0x14);
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (*piVar2 == 0) {
          (**(code **)(*plVar8 + 8))(plVar8);
        }
      }
    }
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_198);
  }
  __security_check_cookie(local_58 ^ (ulonglong)auStack_2a8);
  return;
}


// ==== FUN_140093910 @ 140093910  undefined2 FUN_140093910(undefined2 * param_1)

undefined2 FUN_140093910(undefined2 *param_1)

{
  return *param_1;
}


// ==== FUN_140093920 @ 140093920  undefined2 FUN_140093920(longlong param_1)

undefined2 FUN_140093920(longlong param_1)

{
  return *(undefined2 *)(param_1 + 2);
}


// ==== FUN_140093930 @ 140093930  undefined2 FUN_140093930(longlong param_1)

undefined2 FUN_140093930(longlong param_1)

{
  return *(undefined2 *)(param_1 + 4);
}


// ==== FUN_140093940 @ 140093940  undefined FUN_140093940(undefined2 * param_1, undefined2 param_2)

void FUN_140093940(undefined2 *param_1,undefined2 param_2)

{
  *param_1 = param_2;
  return;
}


// ==== FUN_140093950 @ 140093950  undefined FUN_140093950(longlong param_1, undefined2 param_2)

void FUN_140093950(longlong param_1,undefined2 param_2)

{
  *(undefined2 *)(param_1 + 2) = param_2;
  return;
}


// ==== FUN_140093960 @ 140093960  undefined FUN_140093960(longlong param_1, undefined2 param_2)

void FUN_140093960(longlong param_1,undefined2 param_2)

{
  *(undefined2 *)(param_1 + 4) = param_2;
  return;
}


// ==== FUN_140093970 @ 140093970  undefined8 * FUN_140093970(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_140093970(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  param_1[1] = param_2;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14) = 1;
  *param_1 = std::tr1::_Ref_count<class_CLayer>::vftable;
  return param_1;
}


// ==== FUN_1400939e0 @ 1400939e0  undefined FUN_1400939e0(undefined8 * param_1)

void FUN_1400939e0(undefined8 *param_1)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  return;
}


// ==== FUN_140093a50 @ 140093a50  undefined FUN_140093a50(undefined8 * param_1, undefined8 param_2)

void FUN_140093a50(undefined8 *param_1,undefined8 param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x18);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = std::tr1::_Ref_count_base::vftable;
    puVar1[1] = param_2;
    *(undefined4 *)(puVar1 + 2) = 0;
    *(undefined4 *)((longlong)puVar1 + 0x14) = 1;
    *puVar1 = std::tr1::_Ref_count<class_CLayer>::vftable;
  }
  FUN_140081a30(param_1,param_2,(longlong)puVar1);
  return;
}


// ==== FUN_140093ad0 @ 140093ad0  undefined8 * FUN_140093ad0(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_140093ad0(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_140093a50(param_1,param_2);
  return param_1;
}


// ==== FUN_140093af0 @ 140093af0  undefined8 * FUN_140093af0(undefined8 * param_1)

undefined8 * FUN_140093af0(undefined8 *param_1)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  
  puVar2 = (undefined2 *)0x0;
  puVar1 = (undefined2 *)operator_new(6);
  if (puVar1 != (undefined2 *)0x0) {
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar2 = puVar1;
  }
  *param_1 = 0;
  param_1[1] = 0;
  FUN_140093a50(param_1,puVar2);
  return param_1;
}


// ==== FUN_140093b60 @ 140093b60  undefined8 * FUN_140093b60(undefined8 * param_1, undefined4 param_2)

undefined8 * FUN_140093b60(undefined8 *param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 1) = param_2;
  *param_1 = CMapObj::vftable;
  *(undefined4 *)((longlong)param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 2) = 0;
  return param_1;
}


// ==== FUN_140093b80 @ 140093b80  undefined FUN_140093b80(undefined8 * param_1)

void FUN_140093b80(undefined8 *param_1)

{
  *param_1 = CMapObj::vftable;
  return;
}


// ==== FUN_140093ba0 @ 140093ba0  longlong FUN_140093ba0(longlong param_1)

longlong FUN_140093ba0(longlong param_1)

{
  return param_1 + 0xc;
}


// ==== FUN_140093bc0 @ 140093bc0  longlong FUN_140093bc0(longlong param_1)

longlong FUN_140093bc0(longlong param_1)

{
  return param_1 + 0x18;
}


// ==== FUN_140093bd0 @ 140093bd0  undefined4 FUN_140093bd0(longlong param_1)

undefined4 FUN_140093bd0(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x20);
}


// ==== FUN_140093be0 @ 140093be0  undefined4 FUN_140093be0(longlong param_1)

undefined4 FUN_140093be0(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x24);
}


// ==== FUN_140093c00 @ 140093c00  undefined8 * FUN_140093c00(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_140093c00(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  param_1[1] = param_2;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14) = 1;
  *param_1 = std::tr1::_Ref_count<class_CTerrainObjPart>::vftable;
  return param_1;
}


// ==== FUN_140093c80 @ 140093c80  undefined FUN_140093c80(undefined8 * param_1)

void FUN_140093c80(undefined8 *param_1)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  return;
}


// ==== FUN_140093ca0 @ 140093ca0  longlong FUN_140093ca0(longlong param_1, ulonglong param_2)

longlong FUN_140093ca0(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)(*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18) >> 4) <= param_2) {
    _invalid_parameter_noinfo();
  }
  return param_2 * 0x10 + *(longlong *)(param_1 + 0x18);
}


// ==== FUN_140093cf0 @ 140093cf0  undefined FUN_140093cf0(undefined8 * param_1, undefined8 param_2, longlong param_3)

void FUN_140093cf0(undefined8 *param_1,undefined8 param_2,longlong param_3)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  if (param_3 != 0) {
    LOCK();
    *(int *)(param_3 + 0x10) = *(int *)(param_3 + 0x10) + 1;
    UNLOCK();
  }
  plVar3 = (longlong *)param_1[1];
  if (plVar3 == (longlong *)0x0) {
    param_1[1] = param_3;
    *param_1 = param_2;
  }
  else {
    LOCK();
    plVar1 = plVar3 + 2;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)*plVar1 == 0) {
      (**(code **)*plVar3)(plVar3);
      LOCK();
      piVar2 = (int *)((longlong)plVar3 + 0x14);
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (*piVar2 == 0) {
        (**(code **)(*plVar3 + 8))(plVar3);
      }
      param_1[1] = param_3;
      *param_1 = param_2;
    }
    else {
      param_1[1] = param_3;
      *param_1 = param_2;
    }
  }
  return;
}


// ==== FUN_140093de0 @ 140093de0  undefined8 * FUN_140093de0(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140093de0(undefined8 *param_1,undefined8 *param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_140093cf0(param_1,*param_2,param_2[1]);
  return param_1;
}


// ==== FUN_140093e10 @ 140093e10  undefined FUN_140093e10(undefined8 * param_1)

void FUN_140093e10(undefined8 *param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = (longlong *)param_1[1];
  if (plVar3 == (longlong *)0x0) {
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
  LOCK();
  plVar1 = plVar3 + 2;
  *(int *)plVar1 = (int)*plVar1 + -1;
  UNLOCK();
  if ((int)*plVar1 == 0) {
    (**(code **)*plVar3)(plVar3);
    LOCK();
    piVar2 = (int *)((longlong)plVar3 + 0x14);
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (*piVar2 == 0) {
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
  param_1[1] = 0;
  *param_1 = 0;
  return;
}


// ==== FUN_140093ea0 @ 140093ea0  undefined FUN_140093ea0(undefined8 * param_1, undefined8 param_2)

void FUN_140093ea0(undefined8 *param_1,undefined8 param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x18);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = std::tr1::_Ref_count_base::vftable;
    puVar1[1] = param_2;
    *(undefined4 *)(puVar1 + 2) = 0;
    *(undefined4 *)((longlong)puVar1 + 0x14) = 1;
    *puVar1 = std::tr1::_Ref_count<class_CTerrainObjPart>::vftable;
  }
  FUN_140093cf0(param_1,param_2,(longlong)puVar1);
  return;
}


// ==== FUN_140093f20 @ 140093f20  undefined8 * FUN_140093f20(undefined8 * param_1)

undefined8 * FUN_140093f20(undefined8 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_140093e10(param_1);
  return param_1;
}


// ==== FUN_140093f40 @ 140093f40  undefined8 * FUN_140093f40(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_140093f40(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_140093ea0(param_1,param_2);
  return param_1;
}


// ==== FUN_140093f60 @ 140093f60  undefined8 * FUN_140093f60(longlong param_1, undefined8 * param_2, int param_3, int param_4)

undefined8 * FUN_140093f60(longlong param_1,undefined8 *param_2,int param_3,int param_4)

{
  ulonglong uVar1;
  undefined8 *puVar2;
  
  uVar1 = (ulonglong)(*(int *)(param_1 + 0x18) * param_4 + param_3);
  if ((ulonglong)(*(longlong *)(param_1 + 0x48) - *(longlong *)(param_1 + 0x40) >> 4) <= uVar1) {
    _invalid_parameter_noinfo();
  }
  puVar2 = (undefined8 *)(uVar1 * 0x10 + *(longlong *)(param_1 + 0x40));
  *param_2 = 0;
  param_2[1] = 0;
  FUN_140081a30(param_2,*puVar2,puVar2[1]);
  return param_2;
}


// ==== FUN_140094000 @ 140094000  undefined8 * FUN_140094000(undefined8 * param_1)

undefined8 * FUN_140094000(undefined8 *param_1)

{
  longlong *plVar1;
  longlong *plVar2;
  
  FUN_140093b60(param_1,2);
  *param_1 = CTerrainObjPart::vftable;
  plVar1 = (longlong *)operator_new(8);
  plVar2 = (longlong *)0x0;
  if (plVar1 != (longlong *)0x0) {
    *plVar1 = (longlong)(param_1 + 5);
    plVar2 = plVar1;
  }
  param_1[5] = plVar2;
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  *(undefined4 *)(param_1 + 3) = 2;
  *(undefined4 *)((longlong)param_1 + 0x1c) = 2;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)((longlong)param_1 + 0x24) = 0;
  return param_1;
}


// ==== FUN_140094090 @ 140094090  undefined FUN_140094090(undefined8 * param_1)

void FUN_140094090(undefined8 *param_1)

{
  *param_1 = CTerrainObjPart::vftable;
  if ((longlong *)param_1[8] != (longlong *)0x0) {
    FUN_1400867a0(param_1 + 5,(longlong *)param_1[8],(longlong *)param_1[9]);
    operator_delete((void *)param_1[8]);
  }
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[10] = 0;
  operator_delete((void *)param_1[5]);
  FUN_140093b80(param_1);
  return;
}


// ==== FUN_140094140 @ 140094140  undefined8 * FUN_140094140(undefined8 * param_1, FILE * param_2)

undefined8 * FUN_140094140(undefined8 *param_1,FILE *param_2)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  undefined8 uVar4;
  undefined8 *puVar5;
  int iVar6;
  undefined8 *puVar7;
  longlong lVar8;
  ulonglong uVar9;
  longlong *plVar10;
  int iVar11;
  longlong lVar12;
  int iVar13;
  undefined4 local_res20 [2];
  int local_a4;
  longlong local_90;
  longlong *local_88;
  undefined2 *local_80;
  longlong *local_78;
  longlong local_68;
  undefined8 *puStack_60;
  longlong local_58;
  undefined8 *puStack_50;
  
  puVar7 = (undefined8 *)operator_new(0x58);
  if (puVar7 == (undefined8 *)0x0) {
    puVar7 = (undefined8 *)0x0;
  }
  else {
    puVar7 = FUN_140094000(puVar7);
  }
  local_90 = 0;
  local_88 = (longlong *)0x0;
  FUN_140093ea0(&local_90,puVar7);
  lVar8 = local_90;
  if (local_90 == 0) {
    log_InlineLogERROR("CTerrainObjPart cannot create terrain obj part data");
    *param_1 = 0;
    param_1[1] = 0;
    FUN_140093e10(param_1);
    plVar3 = local_88;
    plVar10 = local_88;
    if (local_88 != (longlong *)0x0) {
      LOCK();
      plVar1 = local_88 + 2;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)*plVar1 == 0) {
        (**(code **)*local_88)();
        LOCK();
        piVar2 = (int *)((longlong)plVar3 + 0x14);
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (*piVar2 == 0) {
          (**(code **)(*local_88 + 8))();
          plVar10 = local_88;
        }
      }
    }
  }
  else {
    fseek(param_2,0x14c,1);
    fread((void *)(lVar8 + 0x18),4,1,param_2);
    fread((void *)(lVar8 + 0x1c),4,1,param_2);
    fseek(param_2,4,1);
    fread((void *)(lVar8 + 0x20),4,1,param_2);
    fread((void *)(lVar8 + 0x24),4,1,param_2);
    fseek(param_2,4,1);
    uVar4 = *(undefined8 *)(lVar8 + 0x18);
    local_a4 = 0;
    iVar6 = (int)((ulonglong)uVar4 >> 0x20);
    if (0 < iVar6) {
      do {
        iVar13 = 0;
        iVar11 = (int)uVar4;
        if (0 < iVar11) {
          do {
            FUN_140093af0(&local_80);
            if (local_80 == (undefined2 *)0x0) {
              log_InlineLogERROR("CTerrainObjPart cannot create layer data");
              param_1[1] = 0;
              *param_1 = 0;
              if (local_78 != (longlong *)0x0) {
                LOCK();
                plVar3 = local_78 + 2;
                *(int *)plVar3 = (int)*plVar3 + -1;
                UNLOCK();
                if ((int)*plVar3 == 0) {
                  (**(code **)*local_78)(local_78);
                  LOCK();
                  piVar2 = (int *)((longlong)local_78 + 0x14);
                  *piVar2 = *piVar2 + -1;
                  UNLOCK();
                  if (*piVar2 == 0) {
                    (**(code **)(*local_78 + 8))(local_78);
                  }
                }
              }
              plVar3 = local_88;
              if (local_88 == (longlong *)0x0) {
                return (undefined8 *)0x0;
              }
              LOCK();
              plVar10 = local_88 + 2;
              *(int *)plVar10 = (int)*plVar10 + -1;
              UNLOCK();
              if ((int)*plVar10 != 0) {
                return local_88;
              }
              plVar10 = local_88;
              (**(code **)*local_88)();
              LOCK();
              piVar2 = (int *)((longlong)plVar3 + 0x14);
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (*piVar2 != 0) {
                return plVar10;
              }
              (**(code **)(*local_88 + 8))();
              return local_88;
            }
            local_res20[0] = 0;
            fread(local_res20,4,1,param_2);
            FUN_140093950((longlong)local_80,(undefined2)local_res20[0]);
            fread(local_res20,4,1,param_2);
            FUN_140093960((longlong)local_80,(undefined2)local_res20[0]);
            fread(local_res20,4,1,param_2);
            FUN_140093940(local_80,(undefined2)local_res20[0]);
            plVar3 = (longlong *)(lVar8 + 0x28);
            puVar7 = *(undefined8 **)(lVar8 + 0x40);
            if (puVar7 == (undefined8 *)0x0) {
              uVar9 = 0;
            }
            else {
              uVar9 = *(longlong *)(lVar8 + 0x50) - (longlong)puVar7 >> 4;
            }
            puVar5 = *(undefined8 **)(lVar8 + 0x48);
            if ((ulonglong)((longlong)puVar5 - (longlong)puVar7 >> 4) < uVar9) {
              FUN_140085740(puVar5,1,&local_80);
              *(undefined8 **)(lVar8 + 0x48) = puVar5 + 2;
            }
            else {
              if (puVar5 < puVar7) {
                _invalid_parameter_noinfo();
              }
              lVar12 = *plVar3;
              uVar9 = *(ulonglong *)(lVar8 + 0x40);
              local_68 = lVar12;
              puStack_60 = puVar5;
              if ((*(ulonglong *)(lVar8 + 0x48) - uVar9 & 0xfffffffffffffff0) == 0) {
                lVar12 = 0;
              }
              else {
                if (*(ulonglong *)(lVar8 + 0x48) < uVar9) {
                  _invalid_parameter_noinfo();
                }
                if ((lVar12 == 0) || (lVar12 != *plVar3)) {
                  _invalid_parameter_noinfo();
                }
                lVar12 = (longlong)((longlong)puVar5 - uVar9) >> 4;
              }
              local_58 = local_68;
              puStack_50 = puStack_60;
              FUN_140087110((longlong)plVar3,(longlong)&local_58,1,(longlong *)&local_80);
              uVar9 = *(ulonglong *)(lVar8 + 0x40);
              if (*(ulonglong *)(lVar8 + 0x48) < uVar9) {
                _invalid_parameter_noinfo();
              }
              plVar3 = (longlong *)*plVar3;
              if (plVar3 == (longlong *)0x0) {
                _invalid_parameter_noinfo();
                lVar8 = 0;
              }
              else {
                lVar8 = *plVar3;
              }
              uVar9 = uVar9 + lVar12 * 0x10;
              if (uVar9 <= *(ulonglong *)(lVar8 + 0x20)) {
                if (plVar3 == (longlong *)0x0) {
                  lVar8 = 0;
                }
                else {
                  lVar8 = *plVar3;
                }
                if (*(ulonglong *)(lVar8 + 0x18) <= uVar9) goto LAB_1400944c7;
              }
              _invalid_parameter_noinfo();
            }
LAB_1400944c7:
            plVar3 = local_78;
            if (local_78 != (longlong *)0x0) {
              LOCK();
              plVar10 = local_78 + 2;
              *(int *)plVar10 = (int)*plVar10 + -1;
              UNLOCK();
              if ((int)*plVar10 == 0) {
                (**(code **)*local_78)(local_78);
                LOCK();
                piVar2 = (int *)((longlong)plVar3 + 0x14);
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (*piVar2 == 0) {
                  (**(code **)(*plVar3 + 8))(plVar3);
                }
              }
            }
            iVar13 = iVar13 + 1;
            lVar8 = local_90;
          } while (iVar13 < iVar11);
        }
        local_a4 = local_a4 + 1;
      } while (local_a4 < iVar6);
    }
    plVar3 = local_88;
    *param_1 = 0;
    param_1[1] = 0;
    FUN_140093cf0(param_1,lVar8,(longlong)local_88);
    plVar1 = local_88;
    plVar10 = param_1;
    if (plVar3 != (longlong *)0x0) {
      LOCK();
      plVar3 = plVar3 + 2;
      *(int *)plVar3 = (int)*plVar3 + -1;
      UNLOCK();
      plVar10 = param_1;
      if ((int)*plVar3 == 0) {
        plVar10 = local_88;
        (**(code **)*local_88)();
        LOCK();
        piVar2 = (int *)((longlong)plVar1 + 0x14);
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (*piVar2 == 0) {
          (**(code **)(*local_88 + 8))();
          plVar10 = local_88;
        }
      }
    }
  }
  return plVar10;
}


// ==== FUN_140094620 @ 140094620  undefined4 FUN_140094620(longlong param_1)

undefined4 FUN_140094620(longlong param_1)

{
  return *(undefined4 *)(param_1 + 0x18);
}


// ==== FUN_140094640 @ 140094640  longlong FUN_140094640(longlong param_1, ulonglong param_2)

longlong FUN_140094640(longlong param_1,ulonglong param_2)

{
  if ((ulonglong)(*(longlong *)(param_1 + 0x20) - *(longlong *)(param_1 + 0x18) >> 4) <= param_2) {
    _invalid_parameter_noinfo();
  }
  return param_2 * 0x10 + *(longlong *)(param_1 + 0x18);
}


// ==== FUN_1400946b0 @ 1400946b0  longlong FUN_1400946b0(longlong * param_1)

longlong FUN_1400946b0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_1400946d2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_1400946d2:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_1400946f0 @ 1400946f0  longlong * FUN_1400946f0(longlong * param_1)

longlong * FUN_1400946f0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140094712;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140094712:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + 0x10;
  return param_1;
}


// ==== FUN_140094730 @ 140094730  bool FUN_140094730(longlong * param_1, longlong * param_2)

bool FUN_140094730(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] == param_2[1];
}


// ==== FUN_140094770 @ 140094770  undefined FUN_140094770(void)

void FUN_140094770(void)

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


// ==== FUN_140094800 @ 140094800  longlong FUN_140094800(longlong * param_1, longlong * param_2)

longlong FUN_140094800(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] - param_2[1] >> 4;
}


// ==== FUN_140094860 @ 140094860  longlong * FUN_140094860(longlong * param_1, longlong param_2)

longlong * FUN_140094860(longlong *param_1,longlong param_2)

{
  longlong *plVar1;
  longlong lVar2;
  longlong lVar3;
  ulonglong uVar4;
  
  plVar1 = (longlong *)*param_1;
  lVar3 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    plVar1 = (longlong *)*param_1;
    lVar2 = lVar3;
    if (plVar1 != (longlong *)0x0) goto LAB_140094890;
  }
  else {
LAB_140094890:
    lVar2 = *plVar1;
  }
  uVar4 = param_1[1] + param_2 * 0x10;
  if (uVar4 <= *(ulonglong *)(lVar2 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar3 = *plVar1;
    }
    if (*(ulonglong *)(lVar3 + 0x18) <= uVar4) goto LAB_1400948b8;
  }
  _invalid_parameter_noinfo();
LAB_1400948b8:
  param_1[1] = param_1[1] + param_2 * 0x10;
  return param_1;
}


// ==== FUN_1400948e0 @ 1400948e0  undefined FUN_1400948e0(ulonglong param_1)

void FUN_1400948e0(ulonglong param_1)

{
  undefined1 auVar1 [16];
  char *local_res8 [4];
  undefined **local_20 [4];
  
  if ((param_1 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_1,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x10)) {
    local_res8[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res8);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_1 << 4);
  return;
}


// ==== FUN_140094980 @ 140094980  undefined8 * FUN_140094980(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_140094980(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  param_1[1] = param_2;
  *(undefined4 *)(param_1 + 2) = 0;
  *(undefined4 *)((longlong)param_1 + 0x14) = 1;
  *param_1 = std::tr1::_Ref_count<class_CTerrainObj>::vftable;
  return param_1;
}


// ==== FUN_140094a00 @ 140094a00  undefined FUN_140094a00(undefined8 * param_1)

void FUN_140094a00(undefined8 *param_1)

{
  *param_1 = std::tr1::_Ref_count_base::vftable;
  return;
}


// ==== FUN_140094a50 @ 140094a50  longlong FUN_140094a50(longlong param_1)

longlong FUN_140094a50(longlong param_1)

{
  return *(longlong *)(param_1 + 0x40) - *(longlong *)(param_1 + 0x38) >> 4;
}


// ==== FUN_140094a60 @ 140094a60  longlong FUN_140094a60(longlong * param_1)

longlong FUN_140094a60(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140094a82;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140094a82:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  return param_1[1];
}


// ==== FUN_140094aa0 @ 140094aa0  longlong * FUN_140094aa0(longlong * param_1)

longlong * FUN_140094aa0(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 == (undefined8 *)0x0) {
    _invalid_parameter_noinfo();
    puVar1 = (undefined8 *)*param_1;
    if (puVar1 == (undefined8 *)0x0) goto LAB_140094ac2;
  }
  puVar1 = (undefined8 *)*puVar1;
LAB_140094ac2:
  if ((ulonglong)puVar1[4] <= (ulonglong)param_1[1]) {
    _invalid_parameter_noinfo();
  }
  param_1[1] = param_1[1] + 0x10;
  return param_1;
}


// ==== FUN_140094ae0 @ 140094ae0  bool FUN_140094ae0(longlong * param_1, longlong * param_2)

bool FUN_140094ae0(longlong *param_1,longlong *param_2)

{
  if ((*param_1 == 0) || (*param_1 != *param_2)) {
    _invalid_parameter_noinfo();
  }
  return param_1[1] != param_2[1];
}


// ==== FUN_140094b20 @ 140094b20  undefined FUN_140094b20(undefined8 * param_1)

void FUN_140094b20(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140094b40 @ 140094b40  undefined FUN_140094b40(undefined8 param_1, ulonglong param_2)

void FUN_140094b40(undefined8 param_1,ulonglong param_2)

{
  undefined1 auVar1 [16];
  char *local_res10 [3];
  undefined **local_20 [4];
  
  if ((param_2 != 0) &&
     (auVar1._8_8_ = 0, auVar1._0_8_ = param_2,
     SUB168((ZEXT816(0) << 0x40 | ZEXT816(0xffffffffffffffff)) / auVar1,0) < 0x10)) {
    local_res10[0] = (char *)0x0;
    std::exception::exception((exception *)local_20,local_res10);
    local_20[0] = std::bad_alloc::vftable;
                    /* WARNING: Subroutine does not return */
    _CxxThrowException(local_20,(ThrowInfo *)&DAT_1400fed18);
  }
  operator_new(param_2 << 4);
  return;
}


// ==== FUN_140094bc0 @ 140094bc0  longlong * FUN_140094bc0(longlong * param_1, longlong param_2)

longlong * FUN_140094bc0(longlong *param_1,longlong param_2)

{
  FUN_140094860(param_1,param_2);
  return param_1;
}


// ==== FUN_140094c70 @ 140094c70  undefined FUN_140094c70(undefined8 * param_1)

void FUN_140094c70(undefined8 *param_1)

{
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140094c90 @ 140094c90  undefined8 FUN_140094c90(longlong param_1, ulonglong param_2)

undefined8 FUN_140094c90(longlong param_1,ulonglong param_2)

{
  code *pcVar1;
  undefined8 uVar2;
  longlong lVar3;
  
  uVar2 = 0;
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  if (param_2 != 0) {
    if (0xfffffffffffffff < param_2) {
      FUN_140094770();
      pcVar1 = (code *)swi(3);
      uVar2 = (*pcVar1)();
      return uVar2;
    }
    lVar3 = FUN_140094b40(param_1 + 0x10,param_2);
    *(longlong *)(param_1 + 0x18) = lVar3;
    *(longlong *)(param_1 + 0x20) = lVar3;
    *(ulonglong *)(param_1 + 0x28) = param_2 * 0x10 + lVar3;
    uVar2 = CONCAT71((int7)((ulonglong)lVar3 >> 8),1);
  }
  return uVar2;
}


// ==== FUN_140094d00 @ 140094d00  undefined FUN_140094d00(undefined8 * param_1)

void FUN_140094d00(undefined8 *param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = (longlong *)param_1[1];
  if (plVar3 == (longlong *)0x0) {
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
  LOCK();
  plVar1 = plVar3 + 2;
  *(int *)plVar1 = (int)*plVar1 + -1;
  UNLOCK();
  if ((int)*plVar1 == 0) {
    (**(code **)*plVar3)(plVar3);
    LOCK();
    piVar2 = (int *)((longlong)plVar3 + 0x14);
    *piVar2 = *piVar2 + -1;
    UNLOCK();
    if (*piVar2 == 0) {
      (**(code **)(*plVar3 + 8))(plVar3);
    }
    param_1[1] = 0;
    *param_1 = 0;
    return;
  }
  param_1[1] = 0;
  *param_1 = 0;
  return;
}


// ==== FUN_140094d90 @ 140094d90  undefined8 * FUN_140094d90(undefined8 * param_1)

undefined8 * FUN_140094d90(undefined8 *param_1)

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


// ==== FUN_140094dd0 @ 140094dd0  longlong * FUN_140094dd0(longlong * param_1, longlong * param_2, longlong param_3)

longlong * FUN_140094dd0(longlong *param_1,longlong *param_2,longlong param_3)

{
  longlong *plVar1;
  longlong lVar2;
  ulonglong uVar3;
  longlong lVar4;
  longlong lVar5;
  
  plVar1 = (longlong *)*param_1;
  lVar2 = param_1[1];
  lVar4 = 0;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar4;
  }
  else {
    lVar5 = *plVar1;
  }
  uVar3 = param_3 * 0x10 + lVar2;
  if (uVar3 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar4 = *plVar1;
    }
    if (*(ulonglong *)(lVar4 + 0x18) <= uVar3) goto LAB_140094e3d;
  }
  _invalid_parameter_noinfo();
LAB_140094e3d:
  *param_2 = (longlong)plVar1;
  param_2[1] = uVar3;
  return param_2;
}


// ==== FUN_140094e70 @ 140094e70  undefined8 * FUN_140094e70(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140094e70(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_140094ed0 @ 140094ed0  undefined FUN_140094ed0(undefined8 * param_1, undefined8 param_2)

void FUN_140094ed0(undefined8 *param_1,undefined8 param_2)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)operator_new(0x18);
  if (puVar1 == (undefined8 *)0x0) {
    puVar1 = (undefined8 *)0x0;
  }
  else {
    *puVar1 = std::tr1::_Ref_count_base::vftable;
    puVar1[1] = param_2;
    *(undefined4 *)(puVar1 + 2) = 0;
    *(undefined4 *)((longlong)puVar1 + 0x14) = 1;
    *puVar1 = std::tr1::_Ref_count<class_CTerrainObj>::vftable;
  }
  FUN_1400819a0(param_1,param_2,(longlong)puVar1);
  return;
}


// ==== FUN_140094f50 @ 140094f50  undefined8 * FUN_140094f50(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140094f50(undefined8 *param_1,undefined8 *param_2)

{
  FUN_140093cf0(param_1,*param_2,param_2[1]);
  return param_1;
}


// ==== FUN_140094f70 @ 140094f70  void * FUN_140094f70(void * param_1, uint param_2)

void * FUN_140094f70(void *param_1,uint param_2)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)((longlong)param_1 + 8);
  if (plVar3 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar3 + 2;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)*plVar1 == 0) {
      (**(code **)*plVar3)(plVar3);
      LOCK();
      piVar2 = (int *)((longlong)plVar3 + 0x14);
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (*piVar2 == 0) {
        (**(code **)(*plVar3 + 8))(plVar3);
      }
    }
  }
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== FUN_140095010 @ 140095010  undefined8 * FUN_140095010(undefined8 * param_1)

undefined8 * FUN_140095010(undefined8 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_140094d00(param_1);
  return param_1;
}


// ==== FUN_140095030 @ 140095030  undefined8 * FUN_140095030(undefined8 * param_1)

undefined8 * FUN_140095030(undefined8 *param_1)

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


// ==== FUN_140095080 @ 140095080  undefined8 * FUN_140095080(undefined8 * param_1, ulonglong param_2, undefined8 * param_3)

undefined8 * FUN_140095080(undefined8 *param_1,ulonglong param_2,undefined8 *param_3)

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


// ==== FUN_1400950e0 @ 1400950e0  undefined8 * FUN_1400950e0(undefined8 * param_1, undefined8 param_2)

undefined8 * FUN_1400950e0(undefined8 *param_1,undefined8 param_2)

{
  *param_1 = 0;
  param_1[1] = 0;
  FUN_140094ed0(param_1,param_2);
  return param_1;
}


// ==== FUN_140095100 @ 140095100  undefined FUN_140095100(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

void FUN_140095100(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  longlong *plVar1;
  int *piVar2;
  longlong lVar3;
  undefined8 uVar4;
  longlong *plVar5;
  
  if (param_1 != param_2) {
    do {
      lVar3 = param_3[1];
      uVar4 = *param_3;
      if (lVar3 != 0) {
        LOCK();
        *(int *)(lVar3 + 0x10) = *(int *)(lVar3 + 0x10) + 1;
        UNLOCK();
      }
      plVar5 = (longlong *)param_1[1];
      if (plVar5 != (longlong *)0x0) {
        LOCK();
        plVar1 = plVar5 + 2;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)*plVar1 == 0) {
          (**(code **)*plVar5)(plVar5);
          LOCK();
          piVar2 = (int *)((longlong)plVar5 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*plVar5 + 8))(plVar5);
          }
        }
      }
      param_1[1] = lVar3;
      *param_1 = uVar4;
      param_1 = param_1 + 2;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_1400951a0 @ 1400951a0  undefined FUN_1400951a0(undefined8 * param_1, undefined8 * param_2)

void FUN_1400951a0(undefined8 *param_1,undefined8 *param_2)

{
  if (param_1 != (undefined8 *)0x0) {
    *param_1 = 0;
    param_1[1] = 0;
    FUN_140093cf0(param_1,*param_2,param_2[1]);
  }
  return;
}


// ==== FUN_1400951e0 @ 1400951e0  undefined FUN_1400951e0(longlong param_1)

void FUN_1400951e0(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_1 + 8);
  if (plVar3 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar3 + 2;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)*plVar1 == 0) {
      (**(code **)*plVar3)(plVar3);
      LOCK();
      piVar2 = (int *)((longlong)plVar3 + 0x14);
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (*piVar2 == 0) {
        (**(code **)(*plVar3 + 8))(plVar3);
      }
    }
  }
  return;
}


// ==== FUN_140095250 @ 140095250  undefined8 * FUN_140095250(longlong param_1, undefined8 * param_2, int param_3)

undefined8 * FUN_140095250(longlong param_1,undefined8 *param_2,int param_3)

{
  undefined8 *puVar1;
  
  if ((ulonglong)(*(longlong *)(param_1 + 0x40) - *(longlong *)(param_1 + 0x38) >> 4) <=
      (ulonglong)(longlong)param_3) {
    _invalid_parameter_noinfo();
  }
  puVar1 = (undefined8 *)((longlong)param_3 * 0x10 + *(longlong *)(param_1 + 0x38));
  *param_2 = 0;
  param_2[1] = 0;
  FUN_140093cf0(param_2,*puVar1,puVar1[1]);
  return param_2;
}


// ==== FUN_1400952e0 @ 1400952e0  undefined8 * FUN_1400952e0(undefined8 * param_1)

undefined8 * FUN_1400952e0(undefined8 *param_1)

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


// ==== FUN_140095340 @ 140095340  undefined8 * FUN_140095340(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140095340(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_140095390 @ 140095390  undefined8 * FUN_140095390(undefined8 * param_1, undefined8 * param_2)

undefined8 * FUN_140095390(undefined8 *param_1,undefined8 *param_2)

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


// ==== FUN_1400953f0 @ 1400953f0  undefined FUN_1400953f0(undefined8 param_1, undefined8 * param_2, undefined8 * param_3)

void FUN_1400953f0(undefined8 param_1,undefined8 *param_2,undefined8 *param_3)

{
  if (param_2 != (undefined8 *)0x0) {
    *param_2 = 0;
    param_2[1] = 0;
    FUN_140093cf0(param_2,*param_3,param_3[1]);
  }
  return;
}


// ==== FUN_140095440 @ 140095440  undefined FUN_140095440(undefined8 param_1, longlong param_2)

void FUN_140095440(undefined8 param_1,longlong param_2)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  plVar3 = *(longlong **)(param_2 + 8);
  if (plVar3 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar3 + 2;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)*plVar1 == 0) {
      (**(code **)*plVar3)(plVar3);
      LOCK();
      piVar2 = (int *)((longlong)plVar3 + 0x14);
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (*piVar2 == 0) {
        (**(code **)(*plVar3 + 8))(plVar3);
      }
    }
  }
  return;
}


// ==== FUN_140095610 @ 140095610  undefined FUN_140095610(undefined8 * param_1, longlong param_2, undefined8 * param_3)

void FUN_140095610(undefined8 *param_1,longlong param_2,undefined8 *param_3)

{
  for (; param_2 != 0; param_2 = param_2 + -1) {
    if (param_1 != (undefined8 *)0x0) {
      *param_1 = 0;
      param_1[1] = 0;
      FUN_140093cf0(param_1,*param_3,param_3[1]);
    }
    param_1 = param_1 + 2;
  }
  return;
}


// ==== FUN_140095690 @ 140095690  undefined FUN_140095690(longlong param_1, longlong param_2)

void FUN_140095690(longlong param_1,longlong param_2)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  if (param_1 != param_2) {
    do {
      plVar3 = *(longlong **)(param_1 + 8);
      if (plVar3 != (longlong *)0x0) {
        LOCK();
        plVar1 = plVar3 + 2;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)*plVar1 == 0) {
          (**(code **)*plVar3)(plVar3);
          LOCK();
          piVar2 = (int *)((longlong)plVar3 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*plVar3 + 8))(plVar3);
          }
        }
      }
      param_1 = param_1 + 0x10;
    } while (param_1 != param_2);
  }
  return;
}


// ==== FUN_140095700 @ 140095700  undefined8 * FUN_140095700(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

/* WARNING: Removing unreachable block (ram,0x0001400957d3) */
/* WARNING: Removing unreachable block (ram,0x0001400957dc) */
/* WARNING: Removing unreachable block (ram,0x0001400957f0) */
/* WARNING: Removing unreachable block (ram,0x000140095805) */

undefined8 * FUN_140095700(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  undefined8 *puVar1;
  undefined8 *puVar2;
  undefined8 uVar3;
  
  for (; param_1 != param_2; param_1 = param_1 + 2) {
    if (param_3 != (undefined8 *)0x0) {
      *param_3 = 0;
      param_3[1] = 0;
      FUN_140093cf0(param_3,0,0);
    }
    puVar1 = param_1 + 1;
    puVar2 = param_3 + 1;
    if (puVar2 != puVar1) {
      uVar3 = *puVar2;
      *puVar2 = *puVar1;
      *puVar1 = uVar3;
    }
    if (param_3 != param_1) {
      uVar3 = *param_3;
      *param_3 = *param_1;
      *param_1 = uVar3;
    }
    param_3 = param_3 + 2;
  }
  return param_3;
}


// ==== FUN_140095880 @ 140095880  undefined FUN_140095880(undefined8 * param_1, longlong param_2, undefined8 * param_3)

void FUN_140095880(undefined8 *param_1,longlong param_2,undefined8 *param_3)

{
  FUN_140095610(param_1,param_2,param_3);
  return;
}


// ==== FUN_1400958a0 @ 1400958a0  undefined FUN_1400958a0(longlong * param_1, longlong * param_2)

void FUN_1400958a0(longlong *param_1,longlong *param_2)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  longlong *plVar4;
  
  if (param_1 != param_2) {
    plVar4 = param_1 + 1;
    do {
      plVar3 = (longlong *)*plVar4;
      if (plVar3 != (longlong *)0x0) {
        LOCK();
        plVar1 = plVar3 + 2;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)*plVar1 == 0) {
          (**(code **)*plVar3)(plVar3);
          LOCK();
          piVar2 = (int *)((longlong)plVar3 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*plVar3 + 8))(plVar3);
          }
        }
      }
      plVar3 = plVar4 + 1;
      plVar4 = plVar4 + 2;
    } while (plVar3 != param_2);
  }
  return;
}


// ==== FUN_140095910 @ 140095910  undefined FUN_140095910(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

void FUN_140095910(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  FUN_140095700(param_1,param_2,param_3);
  return;
}


// ==== FUN_140095930 @ 140095930  longlong FUN_140095930(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

longlong FUN_140095930(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  longlong lVar3;
  undefined8 *puVar4;
  longlong lVar6;
  undefined8 *puVar5;
  
  lVar3 = (longlong)param_3 - ((longlong)param_2 - (longlong)param_1 & 0xfffffffffffffff0U);
  if (param_1 != param_2) {
    lVar6 = (longlong)param_3 - (longlong)param_2;
    puVar4 = param_2 + 1;
    do {
      puVar5 = puVar4 + -2;
      param_3 = param_3 + -2;
      puVar1 = (undefined8 *)((longlong)puVar5 + lVar6);
      if (puVar1 != puVar5) {
        uVar2 = *puVar1;
        *puVar1 = *puVar5;
        *puVar5 = uVar2;
      }
      puVar1 = puVar4 + -3;
      if (param_3 != puVar1) {
        uVar2 = *param_3;
        *param_3 = *puVar1;
        *puVar1 = uVar2;
      }
      puVar4 = puVar5;
    } while (puVar1 != param_1);
  }
  return lVar3;
}


// ==== FUN_1400959b0 @ 1400959b0  undefined8 * FUN_1400959b0(undefined8 param_1, undefined8 * param_2, longlong param_3, undefined8 * param_4)

undefined8 *
FUN_1400959b0(undefined8 param_1,undefined8 *param_2,longlong param_3,undefined8 *param_4)

{
  FUN_140095610(param_2,param_3,param_4);
  return param_2 + param_3 * 2;
}


// ==== FUN_140095a00 @ 140095a00  undefined FUN_140095a00(undefined8 param_1, longlong * param_2, longlong * param_3)

void FUN_140095a00(undefined8 param_1,longlong *param_2,longlong *param_3)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  longlong *plVar4;
  
  if (param_2 != param_3) {
    plVar4 = param_2 + 1;
    do {
      plVar3 = (longlong *)*plVar4;
      if (plVar3 != (longlong *)0x0) {
        LOCK();
        plVar1 = plVar3 + 2;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)*plVar1 == 0) {
          (**(code **)*plVar3)(plVar3);
          LOCK();
          piVar2 = (int *)((longlong)plVar3 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*plVar3 + 8))(plVar3);
          }
        }
      }
      plVar3 = plVar4 + 1;
      plVar4 = plVar4 + 2;
    } while (plVar3 != param_3);
  }
  return;
}


// ==== FUN_140095a70 @ 140095a70  undefined FUN_140095a70(undefined8 param_1, undefined8 * param_2, undefined8 * param_3, undefined8 * param_4)

void FUN_140095a70(undefined8 param_1,undefined8 *param_2,undefined8 *param_3,undefined8 *param_4)

{
  FUN_140095700(param_2,param_3,param_4);
  return;
}


// ==== FUN_140095ab0 @ 140095ab0  longlong FUN_140095ab0(undefined8 * param_1, undefined8 * param_2, undefined8 * param_3)

longlong FUN_140095ab0(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3)

{
  undefined8 *puVar1;
  undefined8 uVar2;
  longlong lVar3;
  undefined8 *puVar4;
  longlong lVar6;
  undefined8 *puVar5;
  
  lVar3 = (longlong)param_3 - ((longlong)param_2 - (longlong)param_1 & 0xfffffffffffffff0U);
  if (param_1 != param_2) {
    lVar6 = (longlong)param_3 - (longlong)param_2;
    puVar4 = param_2 + 1;
    do {
      puVar5 = puVar4 + -2;
      param_3 = param_3 + -2;
      puVar1 = (undefined8 *)((longlong)puVar5 + lVar6);
      if (puVar1 != puVar5) {
        uVar2 = *puVar1;
        *puVar1 = *puVar5;
        *puVar5 = uVar2;
      }
      puVar1 = puVar4 + -3;
      if (param_3 != puVar1) {
        uVar2 = *param_3;
        *param_3 = *puVar1;
        *puVar1 = uVar2;
      }
      puVar4 = puVar5;
    } while (puVar1 != param_1);
  }
  return lVar3;
}


// ==== FUN_140095b30 @ 140095b30  undefined FUN_140095b30(longlong param_1)

void FUN_140095b30(longlong param_1)

{
  if (*(longlong **)(param_1 + 0x18) != (longlong *)0x0) {
    FUN_140095a00(param_1,*(longlong **)(param_1 + 0x18),*(longlong **)(param_1 + 0x20));
    operator_delete(*(void **)(param_1 + 0x18));
  }
  *(undefined8 *)(param_1 + 0x18) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_140095b70 @ 140095b70  undefined FUN_140095b70(longlong param_1, longlong param_2, ulonglong param_3, longlong * param_4)

void FUN_140095b70(longlong param_1,longlong param_2,ulonglong param_3,longlong *param_4)

{
  int *piVar1;
  longlong *plVar2;
  ulonglong uVar3;
  int iVar4;
  longlong *plVar5;
  longlong lVar6;
  longlong *plVar7;
  code *pcVar8;
  undefined8 *puVar9;
  undefined8 *puVar10;
  longlong lVar11;
  ulonglong uVar12;
  ulonglong uVar13;
  longlong *plVar14;
  longlong *plVar15;
  longlong local_60;
  longlong *local_58;
  longlong local_50;
  longlong *local_48;
  undefined8 local_40;
  
  local_40 = 0xfffffffffffffffe;
  lVar11 = *(longlong *)(param_1 + 0x18);
  if (lVar11 == 0) {
    uVar12 = 0;
  }
  else {
    uVar12 = *(longlong *)(param_1 + 0x28) - lVar11 >> 4;
  }
  uVar13 = 0;
  if (param_3 != 0) {
    lVar11 = *(longlong *)(param_1 + 0x20) - lVar11 >> 4;
    if (0xfffffffffffffffU - lVar11 < param_3) {
      FUN_140094770();
      pcVar8 = (code *)swi(3);
      (*pcVar8)();
      return;
    }
    uVar3 = lVar11 + param_3;
    if (uVar12 < uVar3) {
      if (uVar12 <= 0xfffffffffffffff - (uVar12 >> 1)) {
        uVar13 = uVar12 + (uVar12 >> 1);
      }
      if (uVar13 < uVar3) {
        uVar13 = uVar3;
      }
      puVar9 = (undefined8 *)FUN_140094b40(param_1 + 0x10,uVar13);
      lVar11 = *(longlong *)(param_2 + 8) - *(longlong *)(param_1 + 0x18) >> 4;
      FUN_140095610(puVar9 + lVar11 * 2,param_3,param_4);
      FUN_140095700(*(undefined8 **)(param_1 + 0x18),*(undefined8 **)(param_2 + 8),puVar9);
      FUN_140095700(*(undefined8 **)(param_2 + 8),*(undefined8 **)(param_1 + 0x20),
                    puVar9 + (lVar11 + param_3) * 2);
      plVar5 = *(longlong **)(param_1 + 0x18);
      lVar11 = *(longlong *)(param_1 + 0x20);
      if (plVar5 != (longlong *)0x0) {
        FUN_140095a00(param_1,plVar5,*(longlong **)(param_1 + 0x20));
        operator_delete(*(void **)(param_1 + 0x18));
      }
      *(undefined8 **)(param_1 + 0x28) = puVar9 + uVar13 * 2;
      *(undefined8 **)(param_1 + 0x20) = puVar9 + (param_3 + (lVar11 - (longlong)plVar5 >> 4)) * 2;
      *(undefined8 **)(param_1 + 0x18) = puVar9;
    }
    else if ((ulonglong)(*(longlong *)(param_1 + 0x20) - *(longlong *)(param_2 + 8) >> 4) < param_3)
    {
      plVar5 = (longlong *)param_4[1];
      lVar11 = *param_4;
      if (plVar5 != (longlong *)0x0) {
        LOCK();
        *(int *)(plVar5 + 2) = (int)plVar5[2] + 1;
        UNLOCK();
      }
      local_60 = lVar11;
      local_58 = plVar5;
      FUN_140095700(*(undefined8 **)(param_2 + 8),*(undefined8 **)(param_1 + 0x20),
                    *(undefined8 **)(param_2 + 8) + param_3 * 2);
      FUN_140095610(*(undefined8 **)(param_1 + 0x20),
                    param_3 - ((longlong)*(undefined8 **)(param_1 + 0x20) -
                               *(longlong *)(param_2 + 8) >> 4),&local_60);
      *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + param_3 * 0x10;
      lVar6 = *(longlong *)(param_1 + 0x20);
      for (plVar14 = *(longlong **)(param_2 + 8); plVar14 != (longlong *)(lVar6 + param_3 * -0x10);
          plVar14 = plVar14 + 2) {
        if (plVar5 != (longlong *)0x0) {
          LOCK();
          *(int *)(plVar5 + 2) = (int)plVar5[2] + 1;
          UNLOCK();
        }
        plVar15 = (longlong *)plVar14[1];
        if (plVar15 != (longlong *)0x0) {
          LOCK();
          plVar7 = plVar15 + 2;
          *(int *)plVar7 = (int)*plVar7 + -1;
          UNLOCK();
          if ((int)*plVar7 == 0) {
            (**(code **)*plVar15)(plVar15);
            LOCK();
            piVar1 = (int *)((longlong)plVar15 + 0x14);
            *piVar1 = *piVar1 + -1;
            UNLOCK();
            if (*piVar1 == 0) {
              (**(code **)(*plVar15 + 8))(plVar15);
            }
          }
        }
        plVar14[1] = (longlong)plVar5;
        *plVar14 = lVar11;
      }
      if (plVar5 != (longlong *)0x0) {
        LOCK();
        plVar14 = plVar5 + 2;
        lVar11 = *plVar14;
        *(int *)plVar14 = (int)*plVar14 + -1;
        UNLOCK();
        if ((int)lVar11 == 1) {
          (**(code **)*plVar5)(plVar5);
          LOCK();
          piVar1 = (int *)((longlong)plVar5 + 0x14);
          iVar4 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar4 == 1) {
            (**(code **)(*plVar5 + 8))(plVar5);
          }
        }
      }
    }
    else {
      plVar5 = (longlong *)param_4[1];
      lVar11 = *param_4;
      if (plVar5 != (longlong *)0x0) {
        LOCK();
        *(int *)(plVar5 + 2) = (int)plVar5[2] + 1;
        UNLOCK();
      }
      puVar9 = *(undefined8 **)(param_1 + 0x20);
      local_50 = lVar11;
      local_48 = plVar5;
      puVar10 = FUN_140095700(puVar9 + param_3 * -2,puVar9,puVar9);
      *(undefined8 **)(param_1 + 0x20) = puVar10;
      FUN_140095ab0(*(undefined8 **)(param_2 + 8),puVar9 + param_3 * -2,puVar9);
      plVar14 = *(longlong **)(param_2 + 8);
      if (plVar14 != plVar14 + param_3 * 2) {
        plVar15 = plVar14 + 1;
        do {
          if (plVar5 != (longlong *)0x0) {
            LOCK();
            *(int *)(plVar5 + 2) = (int)plVar5[2] + 1;
            UNLOCK();
          }
          plVar7 = (longlong *)*plVar15;
          if (plVar7 != (longlong *)0x0) {
            LOCK();
            plVar2 = plVar7 + 2;
            *(int *)plVar2 = (int)*plVar2 + -1;
            UNLOCK();
            if ((int)*plVar2 == 0) {
              (**(code **)*plVar7)(plVar7);
              LOCK();
              piVar1 = (int *)((longlong)plVar7 + 0x14);
              *piVar1 = *piVar1 + -1;
              UNLOCK();
              if (*piVar1 == 0) {
                (**(code **)(*plVar7 + 8))(plVar7);
              }
            }
          }
          *plVar15 = (longlong)plVar5;
          plVar15[-1] = lVar11;
          plVar7 = plVar15 + 1;
          plVar15 = plVar15 + 2;
        } while (plVar7 != plVar14 + param_3 * 2);
      }
      if (plVar5 != (longlong *)0x0) {
        LOCK();
        plVar14 = plVar5 + 2;
        lVar11 = *plVar14;
        *(int *)plVar14 = (int)*plVar14 + -1;
        UNLOCK();
        if ((int)lVar11 == 1) {
          (**(code **)*plVar5)(plVar5);
          LOCK();
          piVar1 = (int *)((longlong)plVar5 + 0x14);
          iVar4 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar4 == 1) {
            (**(code **)(*plVar5 + 8))(plVar5);
          }
        }
      }
    }
  }
  return;
}


// ==== FUN_140095fa0 @ 140095fa0  undefined FUN_140095fa0(undefined8 * param_1)

void FUN_140095fa0(undefined8 *param_1)

{
  if ((longlong *)param_1[3] != (longlong *)0x0) {
    FUN_140095a00(param_1,(longlong *)param_1[3],(longlong *)param_1[4]);
    operator_delete((void *)param_1[3]);
  }
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  operator_delete((void *)*param_1);
  return;
}


// ==== FUN_140095ff0 @ 140095ff0  longlong * FUN_140095ff0(longlong * param_1, longlong * param_2, longlong * param_3, longlong * param_4)

longlong * FUN_140095ff0(longlong *param_1,longlong *param_2,longlong *param_3,longlong *param_4)

{
  longlong *plVar1;
  longlong lVar2;
  longlong lVar3;
  ulonglong uVar4;
  longlong lVar5;
  longlong *local_28;
  ulonglong uStack_20;
  
  lVar2 = 0;
  uVar4 = param_1[3];
  lVar3 = lVar2;
  if ((param_1[4] - uVar4 & 0xfffffffffffffff0) != 0) {
    if ((ulonglong)param_1[4] < uVar4) {
      _invalid_parameter_noinfo();
    }
    if ((*param_3 == 0) || (*param_3 != *param_1)) {
      _invalid_parameter_noinfo();
    }
    lVar3 = (longlong)(param_3[1] - uVar4) >> 4;
  }
  local_28 = (longlong *)*param_3;
  uStack_20 = param_3[1];
  FUN_140095b70((longlong)param_1,(longlong)&local_28,1,param_4);
  uVar4 = param_1[3];
  if ((ulonglong)param_1[4] < uVar4) {
    _invalid_parameter_noinfo();
  }
  plVar1 = (longlong *)*param_1;
  local_28 = plVar1;
  uStack_20 = uVar4;
  if (plVar1 == (longlong *)0x0) {
    _invalid_parameter_noinfo();
    lVar5 = lVar2;
  }
  else {
    lVar5 = *plVar1;
  }
  uVar4 = lVar3 * 0x10 + uVar4;
  if (uVar4 <= *(ulonglong *)(lVar5 + 0x20)) {
    if (plVar1 != (longlong *)0x0) {
      lVar2 = *plVar1;
    }
    if (*(ulonglong *)(lVar2 + 0x18) <= uVar4) goto LAB_1400960e7;
  }
  _invalid_parameter_noinfo();
LAB_1400960e7:
  *param_2 = (longlong)local_28;
  param_2[1] = uVar4;
  return param_2;
}


// ==== FUN_140096130 @ 140096130  undefined8 * FUN_140096130(undefined8 * param_1, undefined4 param_2)

undefined8 * FUN_140096130(undefined8 *param_1,undefined4 param_2)

{
  longlong *plVar1;
  longlong *plVar2;
  
  FUN_140093b60(param_1,1);
  *param_1 = CTerrainObj::vftable;
  *(undefined4 *)(param_1 + 3) = param_2;
  plVar1 = (longlong *)operator_new(8);
  plVar2 = (longlong *)0x0;
  if (plVar1 != (longlong *)0x0) {
    *plVar1 = (longlong)(param_1 + 4);
    plVar2 = plVar1;
  }
  param_1[4] = plVar2;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  return param_1;
}


// ==== FUN_1400961b0 @ 1400961b0  undefined FUN_1400961b0(undefined8 * param_1)

void FUN_1400961b0(undefined8 *param_1)

{
  *param_1 = CTerrainObj::vftable;
  if ((longlong *)param_1[7] != (longlong *)0x0) {
    FUN_140095a00(param_1 + 4,(longlong *)param_1[7],(longlong *)param_1[8]);
    operator_delete((void *)param_1[7]);
  }
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[9] = 0;
  operator_delete((void *)param_1[4]);
  FUN_140093b80(param_1);
  return;
}


// ==== FUN_140096230 @ 140096230  undefined FUN_140096230(longlong * param_1, longlong * param_2)

void FUN_140096230(longlong *param_1,longlong *param_2)

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
    uVar3 = param_1[5] - (longlong)puVar1 >> 4;
  }
  puVar2 = (undefined8 *)param_1[4];
  if ((ulonglong)((longlong)puVar2 - (longlong)puVar1 >> 4) < uVar3) {
    FUN_140095610(puVar2,1,param_2);
    param_1[4] = (longlong)(puVar2 + 2);
    return;
  }
  if (puVar2 < puVar1) {
    _invalid_parameter_noinfo();
  }
  local_28 = *param_1;
  puStack_20 = puVar2;
  FUN_140095ff0(param_1,local_18,&local_28,param_2);
  return;
}


// ==== FUN_140096330 @ 140096330  undefined FUN_140096330(longlong param_1, longlong * param_2)

void FUN_140096330(longlong param_1,longlong *param_2)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  
  FUN_140096230((longlong *)(param_1 + 0x20),param_2);
  plVar3 = (longlong *)param_2[1];
  if (plVar3 != (longlong *)0x0) {
    LOCK();
    plVar1 = plVar3 + 2;
    *(int *)plVar1 = (int)*plVar1 + -1;
    UNLOCK();
    if ((int)*plVar1 == 0) {
      (**(code **)*plVar3)(plVar3);
      LOCK();
      piVar2 = (int *)((longlong)plVar3 + 0x14);
      *piVar2 = *piVar2 + -1;
      UNLOCK();
      if (*piVar2 == 0) {
        (**(code **)(*plVar3 + 8))(plVar3);
      }
    }
  }
  return;
}


// ==== FUN_140096390 @ 140096390  undefined8 * FUN_140096390(undefined8 * param_1, char * param_2, undefined4 param_3)

undefined8 * FUN_140096390(undefined8 *param_1,char *param_2,undefined4 param_3)

{
  longlong *plVar1;
  int *piVar2;
  longlong *plVar3;
  FILE *_File;
  undefined8 *puVar4;
  undefined8 *puVar5;
  uint uVar6;
  int local_res20 [2];
  longlong local_68;
  longlong *local_60;
  undefined8 local_58;
  longlong *local_50;
  longlong local_48;
  longlong *local_40;
  longlong local_38;
  longlong *local_30;
  undefined8 *puVar7;
  
  puVar7 = (undefined8 *)0x0;
  _File = fopen(param_2,"rb");
  if (_File == (FILE *)0x0) {
    log_InlineLogERROR("CTerrainObj cannot open file %s");
    *param_1 = 0;
    param_1[1] = 0;
    FUN_140094d00(param_1);
  }
  else {
    local_58 = 0;
    local_50 = (longlong *)0x0;
    FUN_14004f180(&local_58,_File,fclose_exref);
    puVar4 = (undefined8 *)operator_new(0x50);
    puVar5 = puVar7;
    if (puVar4 != (undefined8 *)0x0) {
      puVar5 = FUN_140096130(puVar4,param_3);
    }
    local_68 = 0;
    local_60 = (longlong *)0x0;
    FUN_140094ed0(&local_68,puVar5);
    if (local_68 == 0) {
      log_InlineLogERROR("CTerrainObj cannot create terrain data");
      *param_1 = 0;
      param_1[1] = 0;
      FUN_140094d00(param_1);
      plVar3 = local_60;
      if (local_60 != (longlong *)0x0) {
        LOCK();
        plVar1 = local_60 + 2;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)*plVar1 == 0) {
          (**(code **)*local_60)(local_60);
          LOCK();
          piVar2 = (int *)((longlong)plVar3 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*local_60 + 8))();
          }
        }
      }
      plVar3 = local_50;
      if (local_50 != (longlong *)0x0) {
        LOCK();
        plVar1 = local_50 + 2;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)*plVar1 == 0) {
          (**(code **)*local_50)(local_50);
          LOCK();
          piVar2 = (int *)((longlong)plVar3 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*local_50 + 8))();
          }
        }
      }
    }
    else {
      local_res20[0] = 0;
      fread(local_res20,4,1,_File);
      if (0 < local_res20[0]) {
        do {
          FUN_140094140(&local_38,_File);
          if (local_38 == 0) {
            log_InlineLogERROR("CTerrainObj %s added %d of %d parts");
            *param_1 = 0;
            param_1[1] = 0;
            FUN_140094d00(param_1);
            if (local_30 != (longlong *)0x0) {
              LOCK();
              plVar3 = local_30 + 2;
              *(int *)plVar3 = (int)*plVar3 + -1;
              UNLOCK();
              if ((int)*plVar3 == 0) {
                (**(code **)*local_30)(local_30);
                LOCK();
                piVar2 = (int *)((longlong)local_30 + 0x14);
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (*piVar2 == 0) {
                  (**(code **)(*local_30 + 8))(local_30);
                }
              }
            }
            plVar3 = local_60;
            if (local_60 != (longlong *)0x0) {
              LOCK();
              plVar1 = local_60 + 2;
              *(int *)plVar1 = (int)*plVar1 + -1;
              UNLOCK();
              if ((int)*plVar1 == 0) {
                (**(code **)*local_60)(local_60);
                LOCK();
                piVar2 = (int *)((longlong)plVar3 + 0x14);
                *piVar2 = *piVar2 + -1;
                UNLOCK();
                if (*piVar2 == 0) {
                  (**(code **)(*local_60 + 8))();
                }
              }
            }
            plVar3 = local_50;
            if (local_50 == (longlong *)0x0) {
              return param_1;
            }
            LOCK();
            plVar1 = local_50 + 2;
            *(int *)plVar1 = (int)*plVar1 + -1;
            UNLOCK();
            if ((int)*plVar1 != 0) {
              return param_1;
            }
            (**(code **)*local_50)(local_50);
            LOCK();
            piVar2 = (int *)((longlong)plVar3 + 0x14);
            *piVar2 = *piVar2 + -1;
            UNLOCK();
            if (*piVar2 != 0) {
              return param_1;
            }
            (**(code **)(*local_50 + 8))();
            return param_1;
          }
          local_48 = 0;
          local_40 = (longlong *)0x0;
          FUN_140093cf0(&local_48,local_38,(longlong)local_30);
          FUN_140096230((longlong *)(local_68 + 0x20),&local_48);
          plVar3 = local_40;
          if (local_40 != (longlong *)0x0) {
            LOCK();
            plVar1 = local_40 + 2;
            *(int *)plVar1 = (int)*plVar1 + -1;
            UNLOCK();
            if ((int)*plVar1 == 0) {
              (**(code **)*local_40)(local_40);
              LOCK();
              piVar2 = (int *)((longlong)plVar3 + 0x14);
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (*piVar2 == 0) {
                (**(code **)(*plVar3 + 8))(plVar3);
              }
            }
          }
          plVar3 = local_30;
          if (local_30 != (longlong *)0x0) {
            LOCK();
            plVar1 = local_30 + 2;
            *(int *)plVar1 = (int)*plVar1 + -1;
            UNLOCK();
            if ((int)*plVar1 == 0) {
              (**(code **)*local_30)(local_30);
              LOCK();
              piVar2 = (int *)((longlong)plVar3 + 0x14);
              *piVar2 = *piVar2 + -1;
              UNLOCK();
              if (*piVar2 == 0) {
                (**(code **)(*plVar3 + 8))(plVar3);
              }
            }
          }
          uVar6 = (int)puVar7 + 1;
          puVar7 = (undefined8 *)(ulonglong)uVar6;
        } while ((int)uVar6 < local_res20[0]);
      }
      plVar3 = local_60;
      *param_1 = 0;
      param_1[1] = 0;
      FUN_1400819a0(param_1,local_68,(longlong)local_60);
      plVar1 = local_60;
      if (plVar3 != (longlong *)0x0) {
        LOCK();
        plVar3 = plVar3 + 2;
        *(int *)plVar3 = (int)*plVar3 + -1;
        UNLOCK();
        if ((int)*plVar3 == 0) {
          (**(code **)*local_60)(local_60);
          LOCK();
          piVar2 = (int *)((longlong)plVar1 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*local_60 + 8))();
          }
        }
      }
      plVar3 = local_50;
      if (local_50 != (longlong *)0x0) {
        LOCK();
        plVar1 = local_50 + 2;
        *(int *)plVar1 = (int)*plVar1 + -1;
        UNLOCK();
        if ((int)*plVar1 == 0) {
          (**(code **)*local_50)(local_50);
          LOCK();
          piVar2 = (int *)((longlong)plVar3 + 0x14);
          *piVar2 = *piVar2 + -1;
          UNLOCK();
          if (*piVar2 == 0) {
            (**(code **)(*local_50 + 8))();
          }
        }
      }
    }
  }
  return param_1;
}


// ==== FUN_140096770 @ 140096770  undefined FUN_140096770(ushort * param_1, short param_2, char param_3)

void FUN_140096770(ushort *param_1,short param_2,char param_3)

{
  *param_1 = (ushort)(param_3 != '\0') | param_2 * 2;
  param_1[1] = 0xffff;
  return;
}


// ==== FUN_140096790 @ 140096790  ushort FUN_140096790(ushort * param_1)

ushort FUN_140096790(ushort *param_1)

{
  return *param_1 >> 1;
}


// ==== FUN_1400967a0 @ 1400967a0  undefined2 FUN_1400967a0(longlong param_1)

undefined2 FUN_1400967a0(longlong param_1)

{
  return *(undefined2 *)(param_1 + 2);
}


// ==== FUN_1400967b0 @ 1400967b0  bool FUN_1400967b0(byte * param_1)

bool FUN_1400967b0(byte *param_1)

{
  return (*param_1 & 1) == 1;
}


// ==== FUN_1400967c0 @ 1400967c0  undefined FUN_1400967c0(longlong param_1, undefined2 param_2)

void FUN_1400967c0(longlong param_1,undefined2 param_2)

{
  *(undefined2 *)(param_1 + 2) = param_2;
  return;
}


// ==== FUN_1400967d0 @ 1400967d0  undefined FUN_1400967d0(ushort * param_1)

void FUN_1400967d0(ushort *param_1)

{
  *param_1 = *param_1 | 1;
  return;
}


// ==== FUN_140096920 @ 140096920  undefined FUN_140096920(undefined8 * param_1)

void FUN_140096920(undefined8 *param_1)

{
  *param_1 = IFile::vftable;
  return;
}


// ==== FUN_140096930 @ 140096930  undefined FUN_140096930(longlong * param_1)

void FUN_140096930(longlong *param_1)

{
  undefined8 *puVar1;
  
  puVar1 = (undefined8 *)*param_1;
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  return;
}


// ==== FUN_140096950 @ 140096950  ulonglong FUN_140096950(longlong * param_1)

ulonglong FUN_140096950(longlong *param_1)

{
  ulonglong in_RAX;
  ulonglong uVar1;
  
  if ((longlong *)*param_1 != (longlong *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00014009695b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (**(code **)(*(longlong *)*param_1 + 8))();
    return uVar1;
  }
  return in_RAX & 0xffffffffffffff00;
}


// ==== FUN_140096970 @ 140096970  undefined FUN_140096970(undefined8 * param_1)

void FUN_140096970(undefined8 *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x000140096976. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(longlong *)*param_1 + 0x10))();
  return;
}


// ==== FUN_140096980 @ 140096980  undefined FUN_140096980(undefined8 * param_1, longlong param_2)

void FUN_140096980(undefined8 *param_1,longlong param_2)

{
  int iVar1;
  FILE *_File;
  char *_Filename;
  LPCSTR pCVar2;
  undefined1 auStack_68 [32];
  undefined4 local_48 [2];
  undefined8 local_40;
  undefined8 *local_38;
  char local_30;
  char local_2f;
  char local_2e;
  char local_2d;
  char local_2c;
  char local_2b;
  ulonglong local_28;
  
  local_40 = 0xfffffffffffffffe;
  local_28 = DAT_140103510 ^ (ulonglong)auStack_68;
  *param_1 = IFile::vftable;
  *param_1 = _anon_16C71DD6::C7zFile::vftable;
  *(undefined4 *)(param_1 + 1) = 0;
  *(undefined4 *)((longlong)param_1 + 0xc) = 0;
  param_1[2] = 0;
  if (*(ulonglong *)(param_2 + 0x20) < 0x10) {
    _Filename = (char *)(param_2 + 8);
  }
  else {
    _Filename = *(char **)(param_2 + 8);
  }
  pCVar2 = (LPCSTR)(param_2 + 8);
  local_38 = param_1;
  _File = fopen(_Filename,"rb");
  if (_File != (FILE *)0x0) {
    fread(&local_30,1,6,_File);
    fclose(_File);
    if ((((local_30 == '7') && (local_2f == 'z')) && (local_2e == -0x44)) &&
       (((local_2d == -0x51 && (local_2c == '\'')) && (local_2b == '\x1c')))) {
      FUN_14009804c();
      if (0xf < *(ulonglong *)(param_2 + 0x20)) {
        pCVar2 = *(LPCSTR *)pCVar2;
      }
      iVar1 = FUN_140098050(pCVar2,param_1 + 2,(ulonglong *)local_48);
      if (iVar1 == 0) {
        *(undefined4 *)(param_1 + 1) = local_48[0];
      }
    }
  }
  __security_check_cookie(local_28 ^ (ulonglong)auStack_68);
  return;
}


// ==== FUN_140096aa0 @ 140096aa0  undefined FUN_140096aa0(undefined8 * param_1)

void FUN_140096aa0(undefined8 *param_1)

{
  *param_1 = _anon_16C71DD6::C7zFile::vftable;
  if (param_1[2] != 0) {
    FUN_140098300(param_1[2]);
  }
  *param_1 = IFile::vftable;
  return;
}


// ==== FUN_140096ae0 @ 140096ae0  undefined8 * FUN_140096ae0(undefined8 * param_1, longlong param_2)

undefined8 * FUN_140096ae0(undefined8 *param_1,longlong param_2)

{
  int iVar1;
  FILE *_File;
  void *pvVar2;
  undefined8 uVar3;
  char *_Filename;
  undefined8 *puVar4;
  char local_res10;
  char local_res11;
  uint local_res18 [4];
  
  *param_1 = IFile::vftable;
  *param_1 = _anon_16C71DD6::CGzFile::vftable;
  *(undefined4 *)(param_1 + 1) = 0;
  *(undefined4 *)((longlong)param_1 + 0xc) = 0;
  param_1[2] = 0;
  if (*(ulonglong *)(param_2 + 0x20) < 0x10) {
    _Filename = (char *)(param_2 + 8);
  }
  else {
    _Filename = *(char **)(param_2 + 8);
  }
  puVar4 = (undefined8 *)(param_2 + 8);
  _File = fopen(_Filename,"rb");
  if (_File != (FILE *)0x0) {
    fread(&local_res10,1,2,_File);
    if ((local_res10 == '\x1f') && (local_res11 == -0x75)) {
      local_res18[0] = 0;
      fseek(_File,-4,2);
      fread(local_res18,1,4,_File);
      fclose(_File);
      pvVar2 = operator_new__((ulonglong)local_res18[0]);
      param_1[2] = pvVar2;
      if (pvVar2 != (void *)0x0) {
        if (0xf < *(ulonglong *)(param_2 + 0x20)) {
          puVar4 = (undefined8 *)*puVar4;
        }
        uVar3 = Ordinal_16(puVar4,&DAT_1400c8270);
        iVar1 = Ordinal_17(uVar3,param_1[2],local_res18[0]);
        if (iVar1 == -1) {
          operator_delete__((void *)param_1[2]);
          param_1[2] = 0;
        }
        else {
          *(uint *)(param_1 + 1) = local_res18[0];
        }
        Ordinal_12(uVar3);
      }
    }
    else {
      fclose(_File);
    }
  }
  return param_1;
}


// ==== FUN_140096c40 @ 140096c40  undefined FUN_140096c40(undefined8 * param_1)

void FUN_140096c40(undefined8 *param_1)

{
  *param_1 = _anon_16C71DD6::CGzFile::vftable;
  if ((void *)param_1[2] != (void *)0x0) {
    operator_delete__((void *)param_1[2]);
  }
  *param_1 = IFile::vftable;
  return;
}


// ==== FUN_140096c80 @ 140096c80  undefined8 * FUN_140096c80(undefined8 * param_1, longlong param_2)

undefined8 * FUN_140096c80(undefined8 *param_1,longlong param_2)

{
  FILE *pFVar1;
  char *_Filename;
  
  *param_1 = IFile::vftable;
  *param_1 = _anon_16C71DD6::CNormalFile::vftable;
  if (*(ulonglong *)(param_2 + 0x20) < 0x10) {
    _Filename = (char *)(param_2 + 8);
  }
  else {
    _Filename = *(char **)(param_2 + 8);
  }
  pFVar1 = fopen(_Filename,"rb");
  param_1[1] = pFVar1;
  return param_1;
}


// ==== FUN_140096ce0 @ 140096ce0  undefined FUN_140096ce0(undefined8 * param_1)

void FUN_140096ce0(undefined8 *param_1)

{
  *param_1 = _anon_16C71DD6::CNormalFile::vftable;
  if ((FILE *)param_1[1] != (FILE *)0x0) {
    fclose((FILE *)param_1[1]);
  }
  *param_1 = IFile::vftable;
  return;
}


// ==== FUN_140096e70 @ 140096e70  undefined FUN_140096e70(undefined8 * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

void FUN_140096e70(undefined8 *param_1,
                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_2)

{
  char *pcVar1;
  int iVar2;
  longlong *plVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  __uint64 _Var6;
  undefined8 uVar7;
  longlong lVar8;
  char *pcVar9;
  char *pcVar10;
  longlong lVar11;
  undefined1 auStack_e8 [32];
  undefined8 *local_c8;
  longlong local_c0;
  undefined8 local_b8;
  char *local_b0;
  undefined8 local_a8;
  char *local_a0;
  undefined8 local_98;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_60 [40];
  ulonglong local_38;
  
  local_98 = 0xfffffffffffffffe;
  local_38 = DAT_140103510 ^ (ulonglong)auStack_e8;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_60,param_2);
  plVar3 = (longlong *)
           std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::begin
                     (local_60);
  local_c8 = (undefined8 *)*plVar3;
  local_c0 = plVar3[1];
  puVar4 = (undefined8 *)
           std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::end
                     (local_60);
  local_a8 = *puVar4;
  local_a0 = (char *)puVar4[1];
  puVar5 = (undefined8 *)
           std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::begin
                     (local_60);
  pcVar1 = local_a0;
  lVar11 = local_c0;
  puVar4 = local_c8;
  local_b8 = *puVar5;
  pcVar10 = (char *)puVar5[1];
  local_b0 = pcVar10;
  if (local_c8 != (undefined8 *)0xfffffffffffffffc) {
    if (local_c8 == (undefined8 *)0x0) {
      _invalid_parameter_noinfo();
    }
    if (*(ulonglong *)((longlong)puVar4 + 0x20) < 0x10) {
      lVar8 = (longlong)puVar4 + 8;
    }
    else {
      lVar8 = *(longlong *)((longlong)puVar4 + 8);
    }
    pcVar9 = (char *)((longlong)puVar4 + 8);
    if (pcVar1 + (lVar11 - (longlong)pcVar10) <=
        (char *)(lVar8 + *(longlong *)((longlong)puVar4 + 0x18))) {
      if (0xf < *(ulonglong *)((longlong)puVar4 + 0x20)) {
        pcVar9 = *(char **)pcVar9;
      }
      if (pcVar9 <= pcVar1 + (lVar11 - (longlong)pcVar10)) goto LAB_140096f97;
    }
    _invalid_parameter_noinfo();
  }
LAB_140096f97:
  if (pcVar10 != pcVar1) {
    lVar11 = lVar11 - (longlong)pcVar10;
    do {
      iVar2 = tolower((int)*pcVar10);
      pcVar10[lVar11] = (char)iVar2;
      pcVar10 = pcVar10 + 1;
    } while (pcVar10 != pcVar1);
  }
  _Var6 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::find
                    (local_60,".7z",0,3);
  if (*(__uint64 *)npos_exref == _Var6) {
    _Var6 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::find
                      (local_60,".gz",0,3);
    if (*(__uint64 *)npos_exref == _Var6) {
      local_c8 = (undefined8 *)operator_new(0x10);
      if (local_c8 == (undefined8 *)0x0) {
        puVar4 = (undefined8 *)0x0;
      }
      else {
        puVar4 = FUN_140096c80(local_c8,(longlong)param_2);
      }
      *param_1 = puVar4;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_60);
    }
    else {
      local_c8 = (undefined8 *)operator_new(0x18);
      if (local_c8 == (undefined8 *)0x0) {
        puVar4 = (undefined8 *)0x0;
      }
      else {
        puVar4 = FUN_140096ae0(local_c8,(longlong)param_2);
      }
      *param_1 = puVar4;
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_60);
    }
  }
  else {
    local_c8 = (undefined8 *)operator_new(0x18);
    if (local_c8 == (undefined8 *)0x0) {
      uVar7 = 0;
    }
    else {
      uVar7 = FUN_140096980(local_c8,(longlong)param_2);
    }
    *param_1 = uVar7;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_60);
  }
  __security_check_cookie(local_38 ^ (ulonglong)auStack_e8);
  return;
}


// ==== FUN_140097280 @ 140097280  uint FUN_140097280(uint param_1)

uint FUN_140097280(uint param_1)

{
  return param_1 & 7;
}


// ==== FUN_140097290 @ 140097290  uint FUN_140097290(uint param_1)

uint FUN_140097290(uint param_1)

{
  return param_1 >> 3;
}


// ==== FUN_1400972c0 @ 1400972c0  undefined FUN_1400972c0(void)

void FUN_1400972c0(void)

{
  if (DAT_140104d50 != (undefined8 *)0x0) {
    (**(code **)*DAT_140104d50)(DAT_140104d50,1);
  }
  return;
}


// ==== FUN_140097500 @ 140097500  undefined FUN_140097500(longlong param_1, longlong param_2)

void FUN_140097500(longlong param_1,longlong param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int *piVar3;
  undefined1 local_res8 [8];
  undefined4 local_48 [16];
  
  if (param_2 == param_1) {
    local_res8[0] = 0;
    puVar2 = FUN_1400783d0(local_48,3,"f:\\version\\cqserver-78.0.11-1204\\protobuf\\msgwalk.pb.cc",
                           0x155);
    piVar3 = (int *)FUN_140078030((longlong)puVar2,"CHECK failed: (&from) != (this): ");
    FUN_140078580(local_res8,piVar3);
    FUN_140078440((longlong)local_48);
  }
  if (*(char *)(param_2 + 0x30) != '\0') {
    if ((*(byte *)(param_2 + 0x30) & 1) != 0) {
      uVar1 = *(undefined4 *)(param_2 + 0x38);
      *(uint *)(param_1 + 0x30) = *(uint *)(param_1 + 0x30) | 1;
      *(undefined4 *)(param_1 + 0x38) = uVar1;
    }
    if ((*(uint *)(param_2 + 0x30) >> 1 & 1) != 0) {
      uVar1 = *(undefined4 *)(param_2 + 0x3c);
      *(uint *)(param_1 + 0x30) = *(uint *)(param_1 + 0x30) | 2;
      *(undefined4 *)(param_1 + 0x3c) = uVar1;
    }
    if ((*(uint *)(param_2 + 0x30) >> 2 & 1) != 0) {
      uVar1 = *(undefined4 *)(param_2 + 0x40);
      *(uint *)(param_1 + 0x30) = *(uint *)(param_1 + 0x30) | 4;
      *(undefined4 *)(param_1 + 0x40) = uVar1;
    }
    if ((*(uint *)(param_2 + 0x30) >> 3 & 1) != 0) {
      uVar1 = *(undefined4 *)(param_2 + 0x44);
      *(uint *)(param_1 + 0x30) = *(uint *)(param_1 + 0x30) | 8;
      *(undefined4 *)(param_1 + 0x44) = uVar1;
    }
    if ((*(uint *)(param_2 + 0x30) >> 4 & 1) != 0) {
      uVar1 = *(undefined4 *)(param_2 + 0x48);
      *(uint *)(param_1 + 0x30) = *(uint *)(param_1 + 0x30) | 0x10;
      *(undefined4 *)(param_1 + 0x48) = uVar1;
    }
  }
                    /* WARNING: Could not recover jumptable at 0x000140097608. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 8),
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_2 + 8));
  return;
}


// ==== FUN_140097610 @ 140097610  undefined FUN_140097610(longlong * param_1, longlong * param_2)

void FUN_140097610(longlong *param_1,longlong *param_2)

{
  if (param_2 != param_1) {
    (**(code **)(*param_1 + 0x18))();
    FUN_140097500((longlong)param_1,(longlong)param_2);
  }
  return;
}


// ==== FUN_140097710 @ 140097710  undefined8 FUN_140097710(undefined8 * param_1, uint * param_2)

undefined8 FUN_140097710(undefined8 *param_1,uint *param_2)

{
  byte bVar1;
  undefined8 uVar2;
  
  if (((byte *)param_1[1] < (byte *)param_1[2]) && (bVar1 = *(byte *)param_1[1], bVar1 < 0x80)) {
    *param_2 = (uint)bVar1;
    param_1[1] = param_1[1] + 1;
    return 1;
  }
  uVar2 = FUN_14007b0f0(param_1,param_2);
  return uVar2;
}


// ==== FUN_1400977d0 @ 1400977d0  undefined8 * FUN_1400977d0(undefined8 * param_1)

undefined8 * FUN_1400977d0(undefined8 *param_1)

{
  *param_1 = google::protobuf::MessageLite::vftable;
  *param_1 = CMsgWalkPB::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 1));
  *(undefined4 *)((longlong)param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 7) = 0;
  *(undefined4 *)((longlong)param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)((longlong)param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 9) = 0;
  *(undefined4 *)(param_1 + 6) = 0;
  return param_1;
}


// ==== FUN_140097840 @ 140097840  undefined8 * FUN_140097840(undefined8 * param_1, longlong param_2)

undefined8 * FUN_140097840(undefined8 *param_1,longlong param_2)

{
  *param_1 = google::protobuf::MessageLite::vftable;
  *param_1 = CMsgWalkPB::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 1));
  *(undefined4 *)((longlong)param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 7) = 0;
  *(undefined4 *)((longlong)param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)((longlong)param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 9) = 0;
  *(undefined4 *)(param_1 + 6) = 0;
  FUN_140097500((longlong)param_1,param_2);
  return param_1;
}


// ==== FUN_1400978b0 @ 1400978b0  undefined FUN_1400978b0(undefined8 * param_1)

void FUN_1400978b0(undefined8 *param_1)

{
  *param_1 = CMsgWalkPB::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 1));
  FUN_140075ef0(param_1);
  return;
}


// ==== FUN_140097960 @ 140097960  undefined FUN_140097960(longlong param_1, longlong param_2)

void FUN_140097960(longlong param_1,longlong param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  if (param_2 != param_1) {
    puVar2 = (undefined4 *)(param_2 + 0x38);
    puVar3 = (undefined4 *)(param_1 + 0x38);
    if (puVar3 != puVar2) {
      uVar1 = *puVar3;
      *puVar3 = *puVar2;
      *puVar2 = uVar1;
    }
    puVar2 = (undefined4 *)(param_2 + 0x3c);
    puVar3 = (undefined4 *)(param_1 + 0x3c);
    if (puVar3 != puVar2) {
      uVar1 = *puVar3;
      *puVar3 = *puVar2;
      *puVar2 = uVar1;
    }
    puVar2 = (undefined4 *)(param_2 + 0x40);
    puVar3 = (undefined4 *)(param_1 + 0x40);
    if (puVar3 != puVar2) {
      uVar1 = *puVar3;
      *puVar3 = *puVar2;
      *puVar2 = uVar1;
    }
    puVar2 = (undefined4 *)(param_2 + 0x44);
    puVar3 = (undefined4 *)(param_1 + 0x44);
    if (puVar3 != puVar2) {
      uVar1 = *puVar3;
      *puVar3 = *puVar2;
      *puVar2 = uVar1;
    }
    puVar2 = (undefined4 *)(param_2 + 0x48);
    puVar3 = (undefined4 *)(param_1 + 0x48);
    if (puVar3 != puVar2) {
      uVar1 = *puVar3;
      *puVar3 = *puVar2;
      *puVar2 = uVar1;
    }
    puVar2 = (undefined4 *)(param_2 + 0x30);
    puVar3 = (undefined4 *)(param_1 + 0x30);
    if (puVar3 != puVar2) {
      uVar1 = *puVar3;
      *puVar3 = *puVar2;
      *puVar2 = uVar1;
    }
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::swap
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               (param_1 + 8),
               (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               (param_2 + 8));
    puVar2 = (undefined4 *)(param_2 + 0x34);
    puVar3 = (undefined4 *)(param_1 + 0x34);
    if (puVar3 != puVar2) {
      uVar1 = *puVar3;
      *puVar3 = *puVar2;
      *puVar2 = uVar1;
    }
  }
  return;
}


// ==== FUN_140097a60 @ 140097a60  uint * FUN_140097a60(undefined8 * param_1, uint * param_2, uint param_3)

uint * FUN_140097a60(undefined8 *param_1,uint *param_2,uint param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  ulonglong uVar3;
  uint uVar4;
  bool bVar5;
  
  pbVar2 = (byte *)param_1[1];
  if (pbVar2 < (byte *)param_1[2]) {
    if ((char)*pbVar2 < '\x01') {
      if (((param_3 < 0x80) || (pbVar1 = pbVar2 + 1, (byte *)param_1[2] <= pbVar1)) ||
         ((~*pbVar1 & *pbVar2) < 0x80)) goto LAB_140097aee;
      bVar5 = param_3 < 0x3fff;
      uVar4 = (uint)*pbVar1 * 0x80 + -0x80 + (uint)*pbVar2;
      pbVar2 = pbVar2 + 2;
    }
    else {
      uVar4 = (uint)*pbVar2;
      bVar5 = param_3 < 0x7f;
      pbVar2 = pbVar2 + 1;
    }
    param_1[1] = pbVar2;
    *(uint *)(param_1 + 4) = uVar4;
    if ((bVar5) && (param_3 < uVar4)) {
      bVar5 = false;
      *param_2 = uVar4;
    }
    else {
      bVar5 = true;
      *param_2 = uVar4;
    }
  }
  else {
LAB_140097aee:
    uVar3 = FUN_14007b260(param_1);
    uVar4 = (uint)uVar3;
    *(uint *)(param_1 + 4) = uVar4;
    *param_2 = uVar4;
    bVar5 = uVar4 - 1 < param_3;
  }
  *(bool *)(param_2 + 1) = bVar5;
  return param_2;
}


// ==== FUN_140097b20 @ 140097b20  undefined FUN_140097b20(void)

void FUN_140097b20(void)

{
  undefined8 *puVar1;
  
  if (DAT_140104d59 == '\0') {
    DAT_140104d59 = '\x01';
    FUN_140077a60(0x1e9bf1,0x1e9bf0,"f:\\version\\cqserver-78.0.11-1204\\protobuf\\msgwalk.pb.cc");
    puVar1 = (undefined8 *)operator_new(0x50);
    if (puVar1 == (undefined8 *)0x0) {
      DAT_140104d50 = (undefined8 *)0x0;
    }
    else {
      DAT_140104d50 = FUN_1400977d0(puVar1);
    }
    FUN_140078930(FUN_1400972c0);
  }
  return;
}


// ==== FUN_140097b90 @ 140097b90  undefined8 FUN_140097b90(undefined8 param_1)

undefined8 FUN_140097b90(undefined8 param_1)

{
  FUN_140097b20();
  return param_1;
}


// ==== FUN_140097c10 @ 140097c10  longlong FUN_140097c10(void)

longlong FUN_140097c10(void)

{
  if (DAT_140104d50 == 0) {
    FUN_140097b20();
  }
  return DAT_140104d50;
}


// ==== FUN_14009804c @ 14009804c  undefined FUN_14009804c(void)

void FUN_14009804c(void)

{
  return;
}


// ==== FUN_140098050 @ 140098050  undefined FUN_140098050(LPCSTR param_1, longlong * param_2, ulonglong * param_3)

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void FUN_140098050(LPCSTR param_1,longlong *param_2,ulonglong *param_3)

{
  int iVar1;
  longlong lVar2;
  undefined2 *puVar3;
  ulonglong uVar4;
  uint uVar5;
  undefined1 auStackY_4218 [32];
  longlong local_41c8;
  ulonglong local_41c0;
  uint local_41b8 [2];
  code *local_41b0;
  code *local_41a8;
  longlong local_41a0 [2];
  code *local_4190;
  undefined1 *local_4188;
  undefined8 local_4180 [2];
  longlong local_4170;
  uint local_4168 [24];
  uint local_4108;
  longlong local_40f8;
  undefined8 local_4088 [4];
  undefined8 *local_4068;
  ulonglong local_48;
  undefined8 uStack_40;
  
  uStack_40 = 0x140098065;
  local_48 = DAT_140103510 ^ (ulonglong)auStackY_4218;
  puVar3 = (undefined2 *)0x0;
  if (param_2 != (longlong *)0x0) {
    *param_2 = 0;
  }
  if (param_3 != (ulonglong *)0x0) {
    *param_3 = 0;
  }
  if (param_1 != (LPCSTR)0x0) {
    local_41b0 = FUN_140098314;
    local_41a8 = FUN_140098330;
    local_4190 = FUN_14009833c;
    local_4188 = &LAB_140098358;
    iVar1 = FUN_1400983dc(&local_4170,param_1);
    if (iVar1 == 0) {
      FUN_1400986dc(local_4180);
      FUN_14009ba58(local_4088,0);
      local_4068 = local_4180;
      FUN_14009ba94((longlong)local_4088);
      FUN_14009b690();
      FUN_1400988c0(local_4168);
      iVar1 = FUN_14009b330(local_4168,local_4088,&local_41b0,&local_4190);
      if (iVar1 == 0) {
        local_41b8[0] = 0xffffffff;
        local_41c8 = 0;
        local_41c0 = 0;
        uVar4 = 0;
        if (local_4108 != 0) {
          local_41a0[0] = 0;
          local_41a0[1] = 0;
          do {
            if ((*(byte *)((uVar4 >> 3) + local_40f8) & (byte)(0x80 >> ((byte)uVar4 & 7))) == 0) {
              lVar2 = FUN_14009b5e4((longlong)local_4168,uVar4,(undefined2 *)0x0);
              if (lVar2 != 0) {
                FUN_140098330(0,(void *)0x0);
                puVar3 = (undefined2 *)FUN_140098314(0,lVar2 * 2);
                if (puVar3 == (undefined2 *)0x0) break;
              }
              FUN_14009b5e4((longlong)local_4168,uVar4,puVar3);
              uVar4 = FUN_14009b370((longlong)local_4168,local_4088,(uint)uVar4,local_41b8,
                                    &local_41c8,&local_41c0,local_41a0,local_41a0 + 1,&local_41b0,
                                    &local_4190);
              if ((int)uVar4 == 0) {
                if (param_2 != (longlong *)0x0) {
                  *param_2 = local_41c8;
                }
                if (param_3 != (ulonglong *)0x0) {
                  *param_3 = local_41c0;
                }
              }
              else {
                (*local_41a8)(&local_41b0,local_41c8);
                local_41c8 = 0;
                local_41c0 = 0;
              }
              break;
            }
            uVar5 = (uint)uVar4 + 1;
            uVar4 = (ulonglong)uVar5;
          } while (uVar5 < local_4108);
        }
      }
      FUN_140098948(local_4168,(longlong)&local_41b0);
      FUN_140098330(0,puVar3);
      FUN_140098474(&local_4170);
    }
  }
  __security_check_cookie(local_48 ^ (ulonglong)auStackY_4218);
  return;
}


// ==== FUN_140098300 @ 140098300  undefined FUN_140098300(undefined8 param_1)

void FUN_140098300(undefined8 param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00014009830a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)PTR_FUN_140103c38)(&PTR_FUN_140103c30,param_1);
  return;
}


// ==== FUN_140098314 @ 140098314  void * FUN_140098314(undefined8 param_1, size_t param_2)

void * FUN_140098314(undefined8 param_1,size_t param_2)

{
  void *pvVar1;
  
  if (param_2 == 0) {
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = malloc(param_2);
  }
  return pvVar1;
}


// ==== FUN_140098330 @ 140098330  undefined FUN_140098330(undefined8 param_1, void * param_2)

void FUN_140098330(undefined8 param_1,void *param_2)

{
                    /* WARNING: Could not recover jumptable at 0x000140098333. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  free(param_2);
  return;
}


// ==== FUN_14009833c @ 14009833c  void * FUN_14009833c(undefined8 param_1, size_t param_2)

void * FUN_14009833c(undefined8 param_1,size_t param_2)

{
  void *pvVar1;
  
  if (param_2 == 0) {
    pvVar1 = (void *)0x0;
  }
  else {
    pvVar1 = malloc(param_2);
  }
  return pvVar1;
}


// ==== FUN_14009836c @ 14009836c  DWORD FUN_14009836c(undefined8 * param_1, LPCSTR param_2, int param_3)

DWORD FUN_14009836c(undefined8 *param_1,LPCSTR param_2,int param_3)

{
  DWORD DVar1;
  HANDLE pvVar2;
  
  DVar1 = 0;
  pvVar2 = CreateFileA(param_2,(-(uint)(param_3 != 0) & 0xc0000000) + 0x80000000,1,
                       (LPSECURITY_ATTRIBUTES)0x0,3 - (param_3 != 0),0x80,(HANDLE)0x0);
  *param_1 = pvVar2;
  if (pvVar2 == (HANDLE)0xffffffffffffffff) {
    DVar1 = GetLastError();
  }
  return DVar1;
}


// ==== FUN_1400983dc @ 1400983dc  undefined FUN_1400983dc(undefined8 * param_1, LPCSTR param_2)

void FUN_1400983dc(undefined8 *param_1,LPCSTR param_2)

{
  FUN_14009836c(param_1,param_2,0);
  return;
}


// ==== FUN_1400983f0 @ 1400983f0  DWORD FUN_1400983f0(undefined8 * param_1, LPCWSTR param_2, int param_3)

DWORD FUN_1400983f0(undefined8 *param_1,LPCWSTR param_2,int param_3)

{
  DWORD DVar1;
  HANDLE pvVar2;
  
  DVar1 = 0;
  pvVar2 = CreateFileW(param_2,(-(uint)(param_3 != 0) & 0xc0000000) + 0x80000000,1,
                       (LPSECURITY_ATTRIBUTES)0x0,3 - (param_3 != 0),0x80,(HANDLE)0x0);
  *param_1 = pvVar2;
  if (pvVar2 == (HANDLE)0xffffffffffffffff) {
    DVar1 = GetLastError();
  }
  return DVar1;
}


// ==== FUN_140098474 @ 140098474  DWORD FUN_140098474(longlong * param_1)

DWORD FUN_140098474(longlong *param_1)

{
  BOOL BVar1;
  DWORD DVar2;
  
  if (*param_1 != -1) {
    BVar1 = CloseHandle((HANDLE)*param_1);
    if (BVar1 == 0) {
      DVar2 = GetLastError();
      return DVar2;
    }
    *param_1 = -1;
  }
  return 0;
}


// ==== FUN_1400984a4 @ 1400984a4  DWORD FUN_1400984a4(undefined8 * param_1, LPVOID param_2, ulonglong * param_3)

DWORD FUN_1400984a4(undefined8 *param_1,LPVOID param_2,ulonglong *param_3)

{
  BOOL BVar1;
  DWORD DVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  DWORD local_res18 [4];
  
  uVar4 = *param_3;
  if (uVar4 != 0) {
    *param_3 = 0;
    do {
      local_res18[0] = 0;
      DVar2 = (DWORD)uVar4;
      if (0x400000 < uVar4) {
        DVar2 = 0x400000;
      }
      BVar1 = ReadFile((HANDLE)*param_1,param_2,DVar2,local_res18,(LPOVERLAPPED)0x0);
      uVar3 = (ulonglong)local_res18[0];
      *param_3 = *param_3 + uVar3;
      param_2 = (LPVOID)((longlong)param_2 + uVar3);
      uVar4 = uVar4 - uVar3;
      if (BVar1 == 0) {
        DVar2 = GetLastError();
        return DVar2;
      }
    } while ((local_res18[0] != 0) && (uVar4 != 0));
  }
  return 0;
}


// ==== FUN_140098534 @ 140098534  DWORD FUN_140098534(undefined8 * param_1, LPCVOID param_2, ulonglong * param_3)

DWORD FUN_140098534(undefined8 *param_1,LPCVOID param_2,ulonglong *param_3)

{
  BOOL BVar1;
  DWORD DVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  DWORD local_res18 [4];
  
  uVar4 = *param_3;
  if (uVar4 != 0) {
    *param_3 = 0;
    do {
      local_res18[0] = 0;
      DVar2 = (DWORD)uVar4;
      if (0x400000 < uVar4) {
        DVar2 = 0x400000;
      }
      BVar1 = WriteFile((HANDLE)*param_1,param_2,DVar2,local_res18,(LPOVERLAPPED)0x0);
      uVar3 = (ulonglong)local_res18[0];
      *param_3 = *param_3 + uVar3;
      param_2 = (LPCVOID)((longlong)param_2 + uVar3);
      uVar4 = uVar4 - uVar3;
      if (BVar1 == 0) {
        DVar2 = GetLastError();
        return DVar2;
      }
    } while ((local_res18[0] != 0) && (uVar4 != 0));
  }
  return 0;
}


// ==== FUN_1400985c4 @ 1400985c4  DWORD FUN_1400985c4(undefined8 * param_1, LONG * param_2, int param_3)

DWORD FUN_1400985c4(undefined8 *param_1,LONG *param_2,int param_3)

{
  DWORD DVar1;
  DWORD DVar2;
  LONG local_res14 [5];
  
  local_res14[0] = (LONG)((ulonglong)*(undefined8 *)param_2 >> 0x20);
  if (param_3 == 0) {
    DVar1 = 0;
  }
  else {
    DVar1 = 1;
    if (param_3 != 1) {
      if (param_3 != 2) {
        return 0x57;
      }
      DVar1 = 2;
    }
  }
  DVar1 = SetFilePointer((HANDLE)*param_1,*param_2,local_res14,DVar1);
  if ((DVar1 != 0xffffffff) || (DVar2 = GetLastError(), DVar2 == 0)) {
    DVar2 = 0;
    *(ulonglong *)param_2 = CONCAT44(local_res14[0],DVar1);
  }
  return DVar2;
}


// ==== FUN_140098644 @ 140098644  DWORD FUN_140098644(undefined8 * param_1, undefined8 * param_2)

DWORD FUN_140098644(undefined8 *param_1,undefined8 *param_2)

{
  DWORD DVar1;
  DWORD DVar2;
  DWORD local_res18 [4];
  
  DVar1 = GetFileSize((HANDLE)*param_1,local_res18);
  if ((DVar1 == 0xffffffff) && (DVar2 = GetLastError(), DVar2 != 0)) {
    return DVar2;
  }
  *param_2 = CONCAT44(local_res18[0],DVar1);
  return 0;
}


// ==== FUN_14009868c @ 14009868c  byte FUN_14009868c(longlong param_1, LPVOID param_2, ulonglong * param_3)

byte FUN_14009868c(longlong param_1,LPVOID param_2,ulonglong *param_3)

{
  DWORD DVar1;
  
  DVar1 = FUN_1400984a4((undefined8 *)(param_1 + 8),param_2,param_3);
  return -(DVar1 != 0) & 8;
}


// ==== FUN_1400986b4 @ 1400986b4  byte FUN_1400986b4(longlong param_1, LPVOID param_2, ulonglong * param_3)

byte FUN_1400986b4(longlong param_1,LPVOID param_2,ulonglong *param_3)

{
  DWORD DVar1;
  
  DVar1 = FUN_1400984a4((undefined8 *)(param_1 + 0x10),param_2,param_3);
  return -(DVar1 != 0) & 8;
}


// ==== FUN_1400986dc @ 1400986dc  undefined FUN_1400986dc(undefined8 * param_1)

void FUN_1400986dc(undefined8 *param_1)

{
  *param_1 = FUN_1400986b4;
  param_1[1] = &LAB_1400986d0;
  return;
}


// ==== FUN_1400986f4 @ 1400986f4  ulonglong FUN_1400986f4(longlong param_1, LPCVOID param_2, ulonglong param_3)

ulonglong FUN_1400986f4(longlong param_1,LPCVOID param_2,ulonglong param_3)

{
  ulonglong local_res18 [2];
  
  local_res18[0] = param_3;
  FUN_140098534((undefined8 *)(param_1 + 8),param_2,local_res18);
  return local_res18[0];
}


// ==== FUN_140098724 @ 140098724  undefined8 FUN_140098724(longlong * param_1, longlong param_2, undefined8 * param_3)

undefined8 FUN_140098724(longlong *param_1,longlong param_2,undefined8 *param_3)

{
  longlong lVar1;
  undefined8 uVar2;
  
  if (param_2 == 0) {
    *param_1 = 0;
    param_1[1] = 0;
LAB_14009877c:
    uVar2 = 0;
  }
  else {
    lVar1 = (*(code *)*param_3)(param_3,param_2 + 7U >> 3);
    *param_1 = lVar1;
    if (lVar1 != 0) {
      lVar1 = (*(code *)*param_3)(param_3,param_2 << 2);
      param_1[1] = lVar1;
      if (lVar1 != 0) goto LAB_14009877c;
    }
    uVar2 = 2;
  }
  return uVar2;
}


// ==== FUN_140098790 @ 140098790  undefined FUN_140098790(undefined8 * param_1, longlong param_2)

void FUN_140098790(undefined8 *param_1,longlong param_2)

{
  (**(code **)(param_2 + 8))(param_2,*param_1);
  *param_1 = 0;
  (**(code **)(param_2 + 8))(param_2,param_1[1]);
  param_1[1] = 0;
  return;
}


// ==== FUN_1400987c8 @ 1400987c8  undefined FUN_1400987c8(undefined8 * param_1, longlong param_2)

void FUN_1400987c8(undefined8 *param_1,longlong param_2)

{
  (**(code **)(param_2 + 8))(param_2,*param_1);
  *param_1 = 0;
  (**(code **)(param_2 + 8))(param_2,param_1[1]);
  param_1[1] = 0;
  return;
}


// ==== FUN_140098828 @ 140098828  undefined FUN_140098828(undefined4 * param_1, longlong param_2)

void FUN_140098828(undefined4 *param_1,longlong param_2)

{
  (**(code **)(param_2 + 8))(param_2,*(undefined8 *)(param_1 + 0x10));
  (**(code **)(param_2 + 8))(param_2,*(undefined8 *)(param_1 + 0xe));
  (**(code **)(param_2 + 8))(param_2,*(undefined8 *)(param_1 + 2));
  (**(code **)(param_2 + 8))(param_2,*(undefined8 *)(param_1 + 8));
  (**(code **)(param_2 + 8))(param_2,*(undefined8 *)(param_1 + 10));
  (**(code **)(param_2 + 8))(param_2,*(undefined8 *)(param_1 + 0xc));
  FUN_140098790((undefined8 *)(param_1 + 4),param_2);
  *param_1 = 0;
  param_1[1] = 0;
  *(undefined8 *)(param_1 + 2) = 0;
  *(undefined8 *)(param_1 + 4) = 0;
  *(undefined8 *)(param_1 + 6) = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined8 *)(param_1 + 10) = 0;
  *(undefined8 *)(param_1 + 0xc) = 0;
  *(undefined8 *)(param_1 + 0xe) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  return;
}


// ==== FUN_1400988c0 @ 1400988c0  undefined FUN_1400988c0(undefined4 * param_1)

void FUN_1400988c0(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  *(undefined8 *)(param_1 + 2) = 0;
  *(undefined8 *)(param_1 + 4) = 0;
  *(undefined8 *)(param_1 + 6) = 0;
  *(undefined8 *)(param_1 + 8) = 0;
  *(undefined8 *)(param_1 + 10) = 0;
  *(undefined8 *)(param_1 + 0xc) = 0;
  *(undefined8 *)(param_1 + 0xe) = 0;
  *(undefined8 *)(param_1 + 0x10) = 0;
  param_1[0x18] = 0;
  *(undefined8 *)(param_1 + 0x16) = 0;
  *(undefined8 *)(param_1 + 0x1a) = 0;
  *(undefined8 *)(param_1 + 0x1c) = 0;
  *(undefined8 *)(param_1 + 0x2e) = 0;
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined8 *)(param_1 + 0x32) = 0;
  *(undefined8 *)(param_1 + 0x34) = 0;
  *(undefined8 *)(param_1 + 0x1e) = 0;
  *(undefined8 *)(param_1 + 0x20) = 0;
  *(undefined8 *)(param_1 + 0x22) = 0;
  *(undefined8 *)(param_1 + 0x24) = 0;
  *(undefined8 *)(param_1 + 0x26) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  *(undefined8 *)(param_1 + 0x2a) = 0;
  *(undefined8 *)(param_1 + 0x2c) = 0;
  return;
}


// ==== FUN_140098948 @ 140098948  undefined FUN_140098948(undefined4 * param_1, longlong param_2)

void FUN_140098948(undefined4 *param_1,longlong param_2)

{
  (**(code **)(param_2 + 8))(param_2,*(undefined8 *)(param_1 + 0x2e));
  (**(code **)(param_2 + 8))(param_2,*(undefined8 *)(param_1 + 0x30));
  (**(code **)(param_2 + 8))(param_2,*(undefined8 *)(param_1 + 0x32));
  (**(code **)(param_2 + 8))(param_2,*(undefined8 *)(param_1 + 0x34));
  FUN_1400987c8((undefined8 *)(param_1 + 0x2a),param_2);
  FUN_1400987c8((undefined8 *)(param_1 + 0x26),param_2);
  FUN_140098790((undefined8 *)(param_1 + 0x1e),param_2);
  FUN_140098790((undefined8 *)(param_1 + 0x22),param_2);
  (**(code **)(param_2 + 8))(param_2,*(undefined8 *)(param_1 + 0x1c));
  (**(code **)(param_2 + 8))(param_2,*(undefined8 *)(param_1 + 0x1a));
  FUN_140098828(param_1,param_2);
  FUN_1400988c0(param_1);
  return;
}


// ==== FUN_140098a4c @ 140098a4c  undefined8 FUN_140098a4c(longlong * param_1, ulonglong * param_2)

undefined8 FUN_140098a4c(longlong *param_1,ulonglong *param_2)

{
  byte bVar1;
  byte bVar2;
  longlong lVar3;
  byte *pbVar4;
  undefined8 uVar5;
  byte bVar6;
  byte bVar7;
  uint uVar8;
  byte bVar9;
  
  lVar3 = param_1[1];
  if (lVar3 == 0) {
LAB_140098a60:
    uVar5 = 0x10;
  }
  else {
    pbVar4 = (byte *)*param_1;
    param_1[1] = lVar3 + -1;
    bVar1 = *pbVar4;
    *param_1 = (longlong)(pbVar4 + 1);
    if ((char)bVar1 < '\0') {
      if (lVar3 + -1 == 0) goto LAB_140098a60;
      param_1[1] = lVar3 + -2;
      bVar2 = pbVar4[1];
      *param_1 = (longlong)(pbVar4 + 2);
      if ((bVar1 & 0x40) == 0) {
        *param_2 = (ulonglong)((bVar1 & 0x3f) << 8) | (ulonglong)bVar2;
      }
      else {
        if (lVar3 + -2 == 0) goto LAB_140098a60;
        uVar8 = 0x10;
        param_1[1] = lVar3 + -3;
        bVar6 = pbVar4[2];
        *param_1 = (longlong)(pbVar4 + 3);
        bVar9 = 2;
        bVar7 = 0x20;
        *param_2 = (ulonglong)CONCAT11(bVar6,bVar2);
        do {
          if ((bVar1 & bVar7) == 0) {
            *param_2 = *param_2 | ((ulonglong)(bVar7 - 1) & (ulonglong)bVar1) << ((bVar9 & 7) << 3);
            break;
          }
          if (param_1[1] == 0) goto LAB_140098a60;
          bVar7 = bVar7 >> 1;
          bVar9 = bVar9 + 1;
          param_1[1] = param_1[1] + -1;
          bVar2 = *(byte *)*param_1;
          *param_1 = (longlong)((byte *)*param_1 + 1);
          bVar6 = (byte)uVar8;
          uVar8 = uVar8 + 8;
          *param_2 = *param_2 | (ulonglong)bVar2 << (bVar6 & 0x3f);
        } while (uVar8 < 0x40);
      }
    }
    else {
      *param_2 = (ulonglong)bVar1;
    }
    uVar5 = 0;
  }
  return uVar5;
}


// ==== FUN_140098b4c @ 140098b4c  undefined8 FUN_140098b4c(longlong * param_1, uint * param_2)

undefined8 FUN_140098b4c(longlong *param_1,uint *param_2)

{
  undefined8 uVar1;
  ulonglong local_res8 [4];
  
  if (param_1[1] == 0) {
    return 0x10;
  }
  if ((*(byte *)*param_1 & 0x80) == 0) {
    *param_2 = (uint)*(byte *)*param_1;
    *param_1 = *param_1 + 1;
    param_1[1] = param_1[1] + -1;
  }
  else {
    uVar1 = FUN_140098a4c(param_1,local_res8);
    if ((int)uVar1 != 0) {
      return uVar1;
    }
    if ((0x7ffffffe < local_res8[0]) || (0xfffffffffffffff < local_res8[0])) {
      return 4;
    }
    *param_2 = (uint)local_res8[0];
  }
  return 0;
}


// ==== FUN_140098bb4 @ 140098bb4  undefined8 FUN_140098bb4(longlong * param_1)

undefined8 FUN_140098bb4(longlong *param_1)

{
  undefined8 uVar1;
  ulonglong local_res10 [3];
  
  uVar1 = FUN_140098a4c(param_1,local_res10);
  if ((int)uVar1 == 0) {
    if ((ulonglong)param_1[1] < local_res10[0]) {
      uVar1 = 0x10;
    }
    else {
      *param_1 = *param_1 + local_res10[0];
      param_1[1] = param_1[1] - local_res10[0];
      uVar1 = 0;
    }
  }
  return uVar1;
}


// ==== FUN_140098bf4 @ 140098bf4  undefined8 FUN_140098bf4(longlong * param_1, ulonglong param_2)

undefined8 FUN_140098bf4(longlong *param_1,ulonglong param_2)

{
  undefined8 uVar1;
  ulonglong local_res18 [2];
  
  do {
    uVar1 = FUN_140098a4c(param_1,local_res18);
    if ((int)uVar1 != 0) {
      return uVar1;
    }
    if (local_res18[0] == param_2) {
      return 0;
    }
    if (local_res18[0] == 0) {
      return 0x10;
    }
    uVar1 = FUN_140098bb4(param_1);
  } while ((int)uVar1 == 0);
  return uVar1;
}


// ==== FUN_140098c6c @ 140098c6c  int FUN_140098c6c(byte * param_1, int param_2)

int FUN_140098c6c(byte *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  
  bVar3 = 0;
  iVar1 = 0;
  iVar2 = 0;
  if (param_2 != 0) {
    do {
      if (iVar1 == 0) {
        bVar3 = *param_1;
        iVar1 = 8;
        param_1 = param_1 + 1;
      }
      iVar1 = iVar1 + -1;
      iVar2 = iVar2 + (bVar3 >> ((byte)iVar1 & 0x1f) & 1);
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  return iVar2;
}


// ==== FUN_140098ca8 @ 140098ca8  undefined8 FUN_140098ca8(longlong * param_1, uint param_2, undefined8 * param_3, undefined8 * param_4)

undefined8 FUN_140098ca8(longlong *param_1,uint param_2,undefined8 *param_3,undefined8 *param_4)

{
  char cVar1;
  void *pvVar2;
  undefined8 uVar3;
  sbyte sVar4;
  ulonglong uVar5;
  uint uVar6;
  ulonglong _Size;
  
  *param_3 = 0;
  uVar6 = param_2 + 7 >> 3;
  _Size = (ulonglong)uVar6;
  if (param_1[1] == 0) {
LAB_140098d80:
    uVar3 = 0x10;
  }
  else {
    uVar5 = param_1[1] - 1;
    param_1[1] = uVar5;
    cVar1 = *(char *)*param_1;
    *param_1 = (longlong)((char *)*param_1 + 1);
    if (uVar6 != 0) {
      if (cVar1 == '\0') {
        if (uVar5 < _Size) goto LAB_140098d80;
        pvVar2 = (void *)(*(code *)*param_4)(param_4,_Size);
        *param_3 = pvVar2;
        if (pvVar2 == (void *)0x0) {
          return 2;
        }
        memcpy(pvVar2,(void *)*param_1,_Size);
        param_1[1] = param_1[1] - _Size;
        *param_1 = *param_1 + _Size;
      }
      else {
        pvVar2 = (void *)(*(code *)*param_4)(param_4,_Size);
        *param_3 = pvVar2;
        if (pvVar2 == (void *)0x0) {
          return 2;
        }
        memset(pvVar2,0xff,(ulonglong)uVar6);
        if ((param_2 & 7) != 0) {
          sVar4 = (sbyte)(param_2 & 7);
          *(char *)((ulonglong)(uVar6 - 1) + (longlong)pvVar2) =
               ('\x01' << sVar4) + -1 << (8U - sVar4 & 0x1f);
        }
      }
    }
    uVar3 = 0;
  }
  return uVar3;
}


// ==== FUN_140098da0 @ 140098da0  undefined8 FUN_140098da0(undefined8 * param_1, uint param_2, longlong * param_3, undefined8 * param_4)

undefined8 FUN_140098da0(undefined8 *param_1,uint param_2,longlong *param_3,undefined8 *param_4)

{
  undefined4 uVar1;
  longlong lVar2;
  undefined4 *puVar3;
  ulonglong uVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 *local_18;
  ulonglong uStack_10;
  
  if (param_2 == 0) {
    param_3[1] = 0;
  }
  else {
    lVar2 = (*(code *)*param_4)(param_4,(ulonglong)param_2 << 2);
    param_3[1] = lVar2;
    if (lVar2 == 0) {
      return 2;
    }
  }
  puVar5 = (undefined4 *)*param_1;
  uVar4 = param_1[1];
  lVar2 = *param_3;
  puVar3 = (undefined4 *)param_3[1];
  uVar6 = 0;
  local_18 = puVar5;
  uStack_10 = uVar4;
  if (param_2 != 0) {
    do {
      if ((*(byte *)((ulonglong)(uVar6 >> 3) + lVar2) & (byte)(0x80 >> ((byte)uVar6 & 7))) == 0) {
        *puVar3 = 0;
      }
      else {
        if (uVar4 < 4) {
          return 0x10;
        }
        uVar1 = *puVar5;
        uVar4 = uVar4 - 4;
        puVar5 = puVar5 + 1;
        *puVar3 = uVar1;
        local_18 = puVar5;
        uStack_10 = uVar4;
      }
      uVar6 = uVar6 + 1;
      puVar3 = puVar3 + 1;
    } while (uVar6 < param_2);
  }
  *param_1 = local_18;
  param_1[1] = uStack_10;
  return 0;
}


// ==== FUN_140098e78 @ 140098e78  undefined FUN_140098e78(longlong * param_1, uint param_2, longlong * param_3, undefined8 * param_4)

void FUN_140098e78(longlong *param_1,uint param_2,longlong *param_3,undefined8 *param_4)

{
  undefined8 uVar1;
  
  FUN_140098790(param_3,(longlong)param_4);
  uVar1 = FUN_140098ca8(param_1,param_2,param_3,param_4);
  if ((int)uVar1 == 0) {
    FUN_140098da0(param_1,param_2,param_3,param_4);
  }
  return;
}


// ==== FUN_140098edc @ 140098edc  undefined8 FUN_140098edc(longlong * param_1, uint param_2)

undefined8 FUN_140098edc(longlong *param_1,uint param_2)

{
  byte *pbVar1;
  char cVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  
  if (param_1[1] != 0) {
    uVar3 = param_1[1] - 1;
    param_1[1] = uVar3;
    cVar2 = *(char *)*param_1;
    pbVar1 = (byte *)((char *)*param_1 + 1);
    *param_1 = (longlong)pbVar1;
    if (cVar2 == '\0') {
      uVar4 = (ulonglong)(param_2 + 7 >> 3);
      if (uVar3 < uVar4) {
        return 0x10;
      }
      param_2 = FUN_140098c6c(pbVar1,param_2);
      *param_1 = (longlong)(pbVar1 + uVar4);
      param_1[1] = uVar3 - uVar4;
    }
    uVar3 = (ulonglong)param_2;
    if (uVar3 <= (ulonglong)param_1[1] >> 2) {
      *param_1 = *param_1 + uVar3 * 4;
      param_1[1] = param_1[1] + uVar3 * -4;
      return 0;
    }
  }
  return 0x10;
}


// ==== FUN_140098f84 @ 140098f84  undefined8 FUN_140098f84(uint * param_1, longlong * param_2, undefined8 * param_3)

undefined8 FUN_140098f84(uint *param_1,longlong *param_2,undefined8 *param_3)

{
  uint uVar1;
  undefined8 uVar2;
  longlong lVar3;
  ulonglong uVar4;
  uint uVar5;
  ulonglong uVar6;
  ulonglong local_res20;
  
  uVar2 = FUN_140098b4c(param_2,param_1);
  if (((int)uVar2 == 0) && (uVar2 = FUN_140098bf4(param_2,9), (int)uVar2 == 0)) {
    lVar3 = (*(code *)*param_3)(param_3,(ulonglong)*param_1 * 8 + 8);
    *(longlong *)(param_1 + 2) = lVar3;
    if (lVar3 == 0) {
      uVar2 = 2;
    }
    else {
      uVar1 = *param_1;
      uVar4 = 0;
      uVar6 = 0;
      if (uVar1 != 0) {
        lVar3 = 0;
        do {
          *(ulonglong *)(lVar3 + *(longlong *)(param_1 + 2)) = uVar4;
          uVar2 = FUN_140098a4c(param_2,&local_res20);
          if ((int)uVar2 != 0) {
            return uVar2;
          }
          uVar4 = uVar4 + local_res20;
          if (uVar4 < local_res20) {
            return 0x10;
          }
          uVar5 = (int)uVar6 + 1;
          uVar6 = (ulonglong)uVar5;
          lVar3 = lVar3 + 8;
        } while (uVar5 < uVar1);
      }
      *(ulonglong *)(*(longlong *)(param_1 + 2) + uVar6 * 8) = uVar4;
      do {
        uVar2 = FUN_140098a4c(param_2,&local_res20);
        if ((int)uVar2 != 0) {
          return uVar2;
        }
        if (local_res20 == 0) {
          return 0;
        }
        if (local_res20 == 10) {
          uVar2 = FUN_140098edc(param_2,*param_1);
        }
        else {
          uVar2 = FUN_140098bb4(param_2);
        }
      } while ((int)uVar2 == 0);
    }
  }
  return uVar2;
}


// ==== FUN_140099090 @ 140099090  undefined FUN_140099090(uint * param_1, longlong * param_2, longlong * param_3)

void FUN_140099090(uint *param_1,longlong *param_2,longlong *param_3)

{
  uint *puVar1;
  byte bVar2;
  byte bVar3;
  longlong lVar4;
  longlong lVar5;
  uint uVar6;
  longlong *plVar7;
  undefined8 uVar8;
  ulonglong uVar9;
  uint *puVar10;
  char *pcVar11;
  ulonglong uVar12;
  ulonglong uVar13;
  uint uVar14;
  ulonglong uVar15;
  byte *pbVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  undefined1 auStack_78 [32];
  uint local_58;
  uint local_54;
  longlong *local_50;
  char local_48 [8];
  ulonglong local_40;
  
  local_40 = DAT_140103510 ^ (ulonglong)auStack_78;
  lVar4 = *param_2;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  uVar18 = 0;
  local_50 = param_3;
  uVar8 = FUN_140098b4c(param_2,&local_54);
  uVar6 = local_54;
  if ((((int)uVar8 == 0) && (uVar13 = (ulonglong)local_54, local_54 != 0)) && (local_54 < 5)) {
    uVar17 = 0;
    if (local_54 != 0) {
      puVar10 = param_1 + 0xe;
      uVar18 = 0;
      do {
        if (param_2[1] == 0) goto LAB_1400993d3;
        uVar12 = param_2[1] - 1;
        param_2[1] = uVar12;
        bVar2 = *(byte *)*param_2;
        pbVar16 = (byte *)*param_2 + 1;
        *param_2 = (longlong)pbVar16;
        if ((bVar2 & 0xc0) != 0) goto LAB_1400993d3;
        if ((8 < (bVar2 & 0xf)) || (uVar15 = (ulonglong)(bVar2 & 0xf), uVar12 < uVar15))
        goto LAB_1400993d3;
        uVar9 = 0;
        if ((bVar2 & 0xf) != 0) {
          do {
            bVar3 = *pbVar16;
            uVar12 = uVar12 - 1;
            pbVar16 = pbVar16 + 1;
            uVar9 = uVar9 << 8 | (ulonglong)bVar3;
            uVar15 = uVar15 - 1;
            *param_2 = (longlong)pbVar16;
            param_2[1] = uVar12;
          } while (uVar15 != 0);
          if (0xffffffff < uVar9) goto LAB_1400993d3;
        }
        puVar10[0] = 0;
        puVar10[1] = 0;
        puVar10[2] = (uint)uVar9;
        *(undefined1 *)(puVar10 + 3) = 1;
        *(undefined1 *)((longlong)puVar10 + 0xd) = 0;
        if ((bVar2 & 0x10) != 0) {
          uVar8 = FUN_140098b4c(param_2,&local_58);
          if (((int)uVar8 != 0) || (7 < local_58)) goto LAB_1400993d3;
          *(char *)(puVar10 + 3) = (char)local_58;
          uVar8 = FUN_140098b4c(param_2,&local_58);
          if (((int)uVar8 != 0) || (local_58 != 1)) goto LAB_1400993d3;
        }
        uVar18 = uVar18 + (byte)puVar10[3];
        if (7 < uVar18) goto LAB_1400993d3;
        if ((bVar2 & 0x20) != 0) {
          local_54 = 0;
          uVar8 = FUN_140098b4c(param_2,&local_54);
          if ((((int)uVar8 != 0) || (uVar12 = (ulonglong)local_54, (ulonglong)param_2[1] < uVar12))
             || (0x7f < local_54)) goto LAB_1400993d3;
          lVar5 = *param_2;
          *(char *)((longlong)puVar10 + 0xd) = (char)local_54;
          *(longlong *)puVar10 = lVar5 - lVar4;
          *param_2 = *param_2 + uVar12;
          param_2[1] = param_2[1] - uVar12;
        }
        uVar17 = uVar17 + 1;
        puVar10 = puVar10 + 4;
      } while (uVar17 < uVar6);
    }
    uVar17 = uVar6 - 1;
    if ((uVar17 <= uVar18) && (uVar17 < 4)) {
      param_1[1] = uVar17;
      uVar14 = uVar18 - uVar17;
      if (uVar14 < 5) {
        param_1[2] = uVar14;
        if (uVar18 != 0) {
          memset(local_48,0,(ulonglong)uVar18);
        }
        if (uVar17 != 0) {
          if (uVar6 != 0) {
            memset(&local_58,0,uVar13);
          }
          uVar19 = 0;
          if (uVar17 != 0) {
            puVar10 = param_1 + 8;
            do {
              uVar8 = FUN_140098b4c(param_2,puVar10);
              if ((((int)uVar8 != 0) || (uVar18 <= *puVar10)) || (local_48[*puVar10] != '\0'))
              goto LAB_1400993d3;
              local_48[*puVar10] = '\x01';
              uVar8 = FUN_140098b4c(param_2,puVar10 + 1);
              if ((((int)uVar8 != 0) || (uVar6 <= puVar10[1])) ||
                 (puVar1 = puVar10 + 1, *(char *)((longlong)&local_58 + (ulonglong)*puVar1) != '\0')
                 ) goto LAB_1400993d3;
              uVar19 = uVar19 + 1;
              puVar10 = puVar10 + 2;
              *(undefined1 *)((longlong)&local_58 + (ulonglong)*puVar1) = 1;
            } while (uVar19 < uVar17);
          }
          uVar17 = 0;
          if (uVar6 != 0) {
            puVar10 = &local_58;
            do {
              if ((char)*puVar10 == '\0') {
                param_1[3] = uVar17;
                break;
              }
              uVar17 = uVar17 + 1;
              puVar10 = (uint *)((longlong)puVar10 + 1);
            } while (uVar17 < uVar6);
          }
          if (uVar17 == uVar6) goto LAB_1400993d3;
        }
        if (uVar14 == 1) {
          uVar17 = 0;
          if (uVar18 != 0) {
            pcVar11 = local_48;
            do {
              if (*pcVar11 == '\0') break;
              uVar17 = uVar17 + 1;
              pcVar11 = pcVar11 + 1;
            } while (uVar17 < uVar18);
          }
          if (uVar17 == uVar18) goto LAB_1400993d3;
          param_1[4] = uVar17;
        }
        else {
          uVar17 = 0;
          if (uVar14 != 0) {
            puVar10 = param_1 + 4;
            do {
              uVar8 = FUN_140098b4c(param_2,&local_54);
              if ((((int)uVar8 != 0) || (uVar18 <= local_54)) || (local_48[local_54] != '\0'))
              goto LAB_1400993d3;
              uVar17 = uVar17 + 1;
              *puVar10 = local_54;
              puVar10 = puVar10 + 1;
              local_48[local_54] = '\x01';
            } while (uVar17 < uVar14);
          }
        }
        plVar7 = local_50;
        uVar13 = 0;
        if (uVar6 != 0) {
          do {
            uVar8 = FUN_140098a4c(plVar7,(ulonglong *)(param_1 + uVar13 * 2 + 0x1e));
            if ((int)uVar8 != 0) goto LAB_1400993d3;
            uVar18 = (int)uVar13 + 1;
            uVar13 = (ulonglong)uVar18;
          } while (uVar18 < uVar6);
        }
        *param_1 = uVar6;
      }
    }
  }
LAB_1400993d3:
  __security_check_cookie(local_40 ^ (ulonglong)auStack_78);
  return;
}


// ==== FUN_1400993f8 @ 1400993f8  undefined8 FUN_1400993f8(undefined8 * param_1, int param_2)

undefined8 FUN_1400993f8(undefined8 *param_1,int param_2)

{
  byte bVar1;
  longlong lVar2;
  ulonglong uVar3;
  uint uVar4;
  ulonglong uVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte bVar8;
  
  pbVar6 = (byte *)*param_1;
  uVar3 = param_1[1];
  pbVar7 = pbVar6;
  if (param_2 != 0) {
    do {
      if (uVar3 == 0) {
        return 0x10;
      }
      bVar1 = *pbVar6;
      uVar3 = uVar3 - 1;
      pbVar7 = pbVar6 + 1;
      if ((char)bVar1 < '\0') {
        if ((bVar1 & 0x40) == 0) {
          if (uVar3 == 0) {
            return 0x10;
          }
          lVar2 = -1;
          pbVar7 = pbVar6 + 2;
        }
        else {
          bVar8 = 0x20;
          uVar5 = 2;
          do {
            if ((bVar1 & bVar8) == 0) break;
            uVar4 = (int)uVar5 + 1;
            uVar5 = (ulonglong)uVar4;
            bVar8 = bVar8 >> 1;
          } while (uVar4 < 8);
          if (uVar3 < uVar5) {
            return 0x10;
          }
          lVar2 = -uVar5;
          pbVar7 = pbVar7 + uVar5;
        }
        uVar3 = uVar3 + lVar2;
      }
      param_2 = param_2 + -1;
      pbVar6 = pbVar7;
    } while (param_2 != 0);
  }
  *param_1 = pbVar7;
  param_1[1] = uVar3;
  return 0;
}


// ==== FUN_140099490 @ 140099490  undefined FUN_140099490(uint * param_1, longlong * param_2, uint param_3, longlong param_4, uint param_5, undefined8 * param_6)

void FUN_140099490(uint *param_1,longlong *param_2,uint param_3,longlong param_4,uint param_5,
                  undefined8 *param_6)

{
  byte bVar1;
  int iVar2;
  undefined8 uVar3;
  longlong lVar4;
  longlong lVar5;
  ulonglong uVar6;
  void *pvVar7;
  char *pcVar8;
  uint uVar9;
  ulonglong uVar10;
  byte *pbVar11;
  size_t sVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  undefined1 auStack_158 [32];
  byte *local_138;
  ulonglong uStack_130;
  uint local_128;
  char local_124;
  uint local_120;
  uint local_11c;
  uint local_118;
  uint local_114;
  uint local_110;
  uint local_10c;
  uint local_108 [2];
  ulonglong local_100;
  uint local_f8;
  uint local_f4;
  uint local_f0 [2];
  byte *local_e8;
  longlong local_e0;
  longlong *local_d8;
  char local_c8 [64];
  char local_88 [64];
  ulonglong local_48;
  
  local_48 = DAT_140103510 ^ (ulonglong)auStack_158;
  local_d8 = param_2;
  uVar3 = FUN_140098bf4(param_2,0xb);
  if ((((int)uVar3 == 0) &&
      (uVar3 = FUN_140098b4c(param_2,&local_10c), uVar9 = local_10c, (int)uVar3 == 0)) &&
     (uVar6 = (ulonglong)local_10c, local_10c <= param_3)) {
    param_1[1] = local_10c;
    if (param_2[1] != 0) {
      param_2[1] = param_2[1] + -1;
      local_124 = *(char *)*param_2;
      *param_2 = (longlong)((char *)*param_2 + 1);
      if (local_124 == '\0') {
        pbVar11 = (byte *)*param_2;
        uVar10 = param_2[1];
      }
      else {
        uVar3 = FUN_140098b4c(param_2,&local_114);
        if (((int)uVar3 != 0) || (param_5 <= local_114)) goto LAB_140099afb;
        pbVar11 = *(byte **)(param_4 + (ulonglong)local_114 * 0x10);
        uVar10 = *(ulonglong *)(param_4 + 8 + (ulonglong)local_114 * 0x10);
      }
      lVar5 = uVar6 * 8 + 8;
      local_138 = pbVar11;
      uStack_130 = uVar10;
      lVar4 = (*(code *)*param_6)(param_6,lVar5);
      *(longlong *)(param_1 + 8) = lVar4;
      if (lVar4 != 0) {
        lVar5 = (*(code *)*param_6)(param_6,lVar5);
        *(longlong *)(param_1 + 10) = lVar5;
        if (lVar5 != 0) {
          lVar5 = (*(code *)*param_6)(param_6,uVar6 * 4 + 4);
          *(longlong *)(param_1 + 0xc) = lVar5;
          if (lVar5 != 0) {
            local_f8 = 0;
            local_110 = 0;
            local_114 = 0;
            local_e8 = pbVar11;
            if (uVar9 != 0) {
              local_e0 = 0;
              local_100 = 0;
              do {
                sVar12 = 0;
                *(longlong *)(local_100 + *(longlong *)(param_1 + 8)) =
                     (longlong)pbVar11 - (longlong)local_e8;
                local_120 = 0;
                uVar3 = FUN_140098b4c((longlong *)&local_138,&local_128);
                if ((((int)uVar3 != 0) || (local_128 == 0)) || (0x40 < local_128))
                goto LAB_140099afb;
                uVar15 = 0;
                uVar9 = local_128;
                if (local_128 != 0) {
                  do {
                    if (uStack_130 == 0) goto LAB_140099afb;
                    bVar1 = *local_138;
                    if ((((bVar1 & 0xc0) != 0) || (8 < (bVar1 & 0xf))) ||
                       (uVar6 = (ulonglong)(bVar1 & 0xf), uStack_130 - 1 < uVar6))
                    goto LAB_140099afb;
                    uStack_130 = (uStack_130 - 1) - uVar6;
                    local_138 = local_138 + uVar6 + 1;
                    local_118 = 1;
                    if (((bVar1 & 0x10) != 0) &&
                       (((uVar3 = FUN_140098b4c((longlong *)&local_138,&local_118), (int)uVar3 != 0
                         || (uVar3 = FUN_140098b4c((longlong *)&local_138,local_f0), (int)uVar3 != 0
                            )) || ((0x40 < local_118 || (uVar9 = local_128, local_f0[0] != 1))))))
                    goto LAB_140099afb;
                    local_120 = local_120 + local_118;
                    if ((bVar1 & 0x20) != 0) {
                      uVar3 = FUN_140098b4c((longlong *)&local_138,&local_f4);
                      if (((int)uVar3 != 0) || (uVar6 = (ulonglong)local_f4, uStack_130 < uVar6))
                      goto LAB_140099afb;
                      uStack_130 = uStack_130 - uVar6;
                      local_138 = local_138 + uVar6;
                      uVar9 = local_128;
                    }
                    uVar15 = uVar15 + 1;
                  } while (uVar15 < uVar9);
                  sVar12 = (size_t)local_120;
                }
                uVar10 = uStack_130;
                pbVar11 = local_138;
                uVar14 = 0;
                local_118 = 0;
                uVar15 = 1;
                uVar13 = (uint)sVar12;
                if ((uVar9 != 1) || (uVar13 != 1)) {
                  if ((uVar13 < uVar9 - 1) || (0x40 < uVar13)) goto LAB_140099afb;
                  uVar14 = uVar9;
                  if (uVar13 != 0) {
                    memset(local_c8,0,sVar12);
                    uVar14 = local_128;
                  }
                  if (uVar14 != 0) {
                    memset(local_88,0,(ulonglong)uVar14);
                    uVar14 = local_128;
                  }
                  uVar15 = local_120;
                  uVar13 = 0;
                  if (uVar9 != 1) {
                    do {
                      uVar3 = FUN_140098b4c((longlong *)&local_138,&local_11c);
                      if ((((int)uVar3 != 0) || (uVar15 <= local_11c)) ||
                         (local_c8[local_11c] != '\0')) goto LAB_140099afb;
                      local_c8[local_11c] = '\x01';
                      uVar3 = FUN_140098b4c((longlong *)&local_138,&local_11c);
                      if ((((int)uVar3 != 0) || (local_128 <= local_11c)) ||
                         (local_88[local_11c] != '\0')) goto LAB_140099afb;
                      uVar13 = uVar13 + 1;
                      local_88[local_11c] = '\x01';
                      uVar10 = uStack_130;
                      pbVar11 = local_138;
                      uVar14 = local_128;
                    } while (uVar13 < uVar9 - 1);
                  }
                  uVar15 = local_120 - (uVar14 - 1);
                  uVar9 = uVar14;
                  if ((uVar15 != 1) && (uVar14 = 0, uVar15 != 0)) {
                    do {
                      uVar3 = FUN_140098b4c((longlong *)&local_138,local_108);
                      if (((int)uVar3 != 0) ||
                         ((local_120 <= local_108[0] || (local_c8[local_108[0]] != '\0'))))
                      goto LAB_140099afb;
                      uVar14 = uVar14 + 1;
                      local_c8[local_108[0]] = '\x01';
                      uVar10 = uStack_130;
                      pbVar11 = local_138;
                      uVar9 = local_128;
                    } while (uVar14 < uVar15);
                  }
                  uVar13 = 0;
                  uVar14 = uVar13;
                  if (uVar9 != 0) {
                    pcVar8 = local_88;
                    do {
                      uVar14 = uVar13;
                      if (*pcVar8 == '\0') break;
                      uVar13 = uVar13 + 1;
                      pcVar8 = pcVar8 + 1;
                      uVar14 = local_118;
                    } while (uVar13 < uVar9);
                  }
                  if (uVar13 == uVar9) goto LAB_140099afb;
                }
                local_110 = local_110 + uVar9;
                *(uint *)(local_e0 + *(longlong *)(param_1 + 0xc)) = local_f8;
                *(ulonglong *)(local_100 + *(longlong *)(param_1 + 10)) =
                     (ulonglong)(uVar9 << 8 | uVar14);
                if (((local_110 < uVar9) || (local_f8 = local_f8 + uVar15, local_f8 < uVar15)) ||
                   (*param_1 < local_f8)) goto LAB_140099afb;
                local_114 = local_114 + 1;
                local_e0 = local_e0 + 4;
                local_100 = local_100 + 8;
                param_2 = local_d8;
                uVar9 = local_10c;
              } while (local_114 < local_10c);
            }
            uVar15 = local_110;
            sVar12 = (longlong)pbVar11 - (longlong)local_e8;
            *(uint *)(*(longlong *)(param_1 + 0xc) + (ulonglong)local_114 * 4) = local_f8;
            *(size_t *)(*(longlong *)(param_1 + 8) + (ulonglong)local_114 * 8) = sVar12;
            if (sVar12 == 0) {
              param_1 = (uint *)0x0;
            }
            else {
              pvVar7 = (void *)(*(code *)*param_6)(param_6,sVar12);
              *(void **)(param_1 + 0xe) = pvVar7;
              if (pvVar7 == (void *)0x0) goto LAB_140099afb;
              memcpy(pvVar7,local_e8,sVar12);
            }
            if (local_124 != '\0') {
              if (uVar10 != 0) goto LAB_140099afb;
              local_138 = (byte *)*param_2;
              uStack_130 = param_2[1];
            }
            uVar3 = FUN_140098bf4((longlong *)&local_138,0xc);
            uVar6 = uStack_130;
            if (((int)uVar3 == 0) && (uVar3 = FUN_1400993f8(&local_138,uVar15), (int)uVar3 == 0)) {
              sVar12 = uVar6 - uStack_130;
              if (sVar12 == 0) {
                param_1 = (uint *)0x0;
              }
              else {
                pvVar7 = (void *)(*(code *)*param_6)(param_6,sVar12);
                *(void **)(param_1 + 0x10) = pvVar7;
                if (pvVar7 == (void *)0x0) goto LAB_140099afb;
                memcpy(pvVar7,local_138 + -sVar12,sVar12);
              }
              *(size_t *)(param_1 + 0x12) = sVar12;
              do {
                uVar3 = FUN_140098a4c((longlong *)&local_138,&local_100);
                if ((int)uVar3 != 0) break;
                if (local_100 == 0) {
                  *param_2 = (longlong)local_138;
                  param_2[1] = uStack_130;
                  break;
                }
                if (local_100 == 10) {
                  FUN_140098790((undefined8 *)(param_1 + 4),(longlong)param_6);
                  uVar3 = FUN_140098ca8((longlong *)&local_138,uVar9,(undefined8 *)(param_1 + 4),
                                        param_6);
                  if ((int)uVar3 != 0) break;
                  uVar3 = FUN_140098da0(&local_138,uVar9,(longlong *)(param_1 + 4),param_6);
                  iVar2 = (int)uVar3;
                }
                else {
                  uVar3 = FUN_140098bb4((longlong *)&local_138);
                  iVar2 = (int)uVar3;
                }
              } while (iVar2 == 0);
            }
          }
        }
      }
    }
  }
LAB_140099afb:
  __security_check_cookie(local_48 ^ (ulonglong)auStack_158);
  return;
}


// ==== FUN_140099b28 @ 140099b28  undefined8 FUN_140099b28(longlong param_1, longlong * param_2, uint * param_3)

undefined8 FUN_140099b28(longlong param_1,longlong *param_2,uint *param_3)

{
  uint uVar1;
  int iVar2;
  undefined8 uVar3;
  uint uVar4;
  ulonglong uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint local_res8 [2];
  ulonglong local_res20;
  
  uVar1 = *(uint *)(param_1 + 4);
  local_res20 = 0;
  uVar6 = 0;
  iVar9 = 0;
  uVar7 = uVar1;
  do {
    while( true ) {
      uVar3 = FUN_140098a4c(param_2,&local_res20);
      uVar5 = local_res20;
      if ((int)uVar3 != 0) {
        return uVar3;
      }
      if (local_res20 == 0xd) break;
      if (((local_res20 == 10) || (local_res20 == 9)) || (local_res20 == 0)) {
        if ((*(longlong *)(param_3 + 2) == 0) &&
           (uVar6 = uVar1, *(byte **)(param_1 + 0x10) != (byte *)0x0)) {
          iVar2 = FUN_140098c6c(*(byte **)(param_1 + 0x10),uVar1);
          uVar6 = uVar1 - iVar2;
        }
        *param_3 = uVar7;
        param_3[1] = uVar6;
        if (uVar5 != 9) goto LAB_140099c8e;
        *(longlong *)(param_3 + 6) = *param_2;
        uVar3 = FUN_1400993f8(param_2,iVar9);
        if ((int)uVar3 != 0) {
          return uVar3;
        }
        *(longlong *)(param_3 + 8) = *param_2 - *(longlong *)(param_3 + 6);
        while( true ) {
          uVar3 = FUN_140098a4c(param_2,&local_res20);
          uVar5 = local_res20;
          if ((int)uVar3 != 0) {
            return uVar3;
          }
LAB_140099c8e:
          if (uVar5 == 0) break;
          if (uVar5 == 10) {
            *(longlong *)(param_3 + 10) = *param_2;
            uVar3 = FUN_140098edc(param_2,uVar6);
            if ((int)uVar3 != 0) {
              return uVar3;
            }
            *(longlong *)(param_3 + 0xc) = *param_2 - *(longlong *)(param_3 + 10);
          }
          else {
            uVar3 = FUN_140098bb4(param_2);
            if ((int)uVar3 != 0) {
              return uVar3;
            }
          }
        }
        return 0;
      }
      uVar3 = FUN_140098bb4(param_2);
      if ((int)uVar3 != 0) {
        return uVar3;
      }
    }
    uVar7 = 0;
    uVar6 = 0;
    uVar4 = 0;
    *(longlong *)(param_3 + 2) = *param_2;
    uVar8 = uVar7;
    if (uVar1 != 0) {
      do {
        uVar3 = FUN_140098b4c(param_2,local_res8);
        if ((int)uVar3 != 0) {
          return uVar3;
        }
        uVar7 = local_res8[0] + uVar8;
        if (uVar7 < uVar8) {
          return 4;
        }
        if (local_res8[0] != 0) {
          iVar9 = iVar9 + -1 + local_res8[0];
        }
        if (((local_res8[0] != 1) || (*(longlong *)(param_1 + 0x10) == 0)) ||
           ((*(byte *)((ulonglong)(uVar4 >> 3) + *(longlong *)(param_1 + 0x10)) &
            (byte)(0x80 >> ((byte)uVar4 & 7))) == 0)) {
          uVar6 = uVar6 + local_res8[0];
        }
        uVar4 = uVar4 + 1;
        uVar8 = uVar7;
      } while (uVar4 < uVar1);
    }
    *(longlong *)(param_3 + 4) = *param_2 - *(longlong *)(param_3 + 2);
  } while( true );
}


// ==== FUN_140099ce0 @ 140099ce0  ulonglong FUN_140099ce0(uint * param_1, longlong * param_2, uint param_3, longlong param_4, uint param_5, ulonglong * param_6, uint * param_7, undefined8 * param_8)

ulonglong FUN_140099ce0(uint *param_1,longlong *param_2,uint param_3,longlong param_4,uint param_5,
                       ulonglong *param_6,uint *param_7,undefined8 *param_8)

{
  uint *puVar1;
  undefined8 *puVar2;
  ulonglong uVar3;
  
  puVar1 = param_7;
  param_7[6] = 0;
  param_7[7] = 0;
  param_7[8] = 0;
  param_7[9] = 0;
  param_7[10] = 0;
  param_7[0xb] = 0;
  param_7[0xc] = 0;
  param_7[0xd] = 0;
  param_7[2] = 0;
  param_7[3] = 0;
  param_7[4] = 0;
  param_7[5] = 0;
  *param_6 = 0;
  uVar3 = FUN_140098a4c(param_2,(ulonglong *)&param_7);
  puVar2 = param_8;
  if ((((int)uVar3 == 0) &&
      ((param_7 != (uint *)0x6 ||
       (((uVar3 = FUN_140098a4c(param_2,param_6), (int)uVar3 == 0 &&
         (uVar3 = FUN_140098f84(param_1,param_2,puVar2), (int)uVar3 == 0)) &&
        (uVar3 = FUN_140098a4c(param_2,(ulonglong *)&param_7), (int)uVar3 == 0)))))) &&
     ((param_7 != (uint *)0x7 ||
      ((uVar3 = FUN_140099490(param_1,param_2,param_3,param_4,param_5,puVar2), (int)uVar3 == 0 &&
       (uVar3 = FUN_140098a4c(param_2,(ulonglong *)&param_7), (int)uVar3 == 0)))))) {
    if (param_7 == (uint *)0x8) {
      uVar3 = FUN_140099b28((longlong)param_1,param_2,puVar1);
      if ((int)uVar3 != 0) {
        return uVar3;
      }
      uVar3 = FUN_140098a4c(param_2,(ulonglong *)&param_7);
      if ((int)uVar3 != 0) {
        return uVar3;
      }
    }
    else {
      *puVar1 = param_1[1];
    }
    uVar3 = (ulonglong)(-(uint)(param_7 != (uint *)0x0) & 4);
  }
  return uVar3;
}


// ==== FUN_140099e54 @ 140099e54  ulonglong FUN_140099e54(undefined8 * param_1, longlong * param_2, undefined8 * param_3, uint param_4, longlong param_5, uint * param_6, undefined8 * param_7)

ulonglong FUN_140099e54(undefined8 *param_1,longlong *param_2,undefined8 *param_3,uint param_4,
                       longlong param_5,uint *param_6,undefined8 *param_7)

{
  uint uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  uint uVar5;
  longlong lVar6;
  uint uVar7;
  longlong lVar8;
  longlong lVar9;
  longlong *local_98;
  uint local_90;
  longlong local_88;
  undefined8 local_80;
  ulonglong local_78;
  ulonglong local_70;
  uint local_68 [16];
  
  uVar2 = FUN_140099ce0(param_6,param_2,param_4,0,0,(ulonglong *)&local_98,local_68,param_7);
  if ((int)uVar2 == 0) {
    lVar8 = (longlong)local_98 + param_5;
    if (param_6[1] == 0) {
      uVar2 = 0x10;
    }
    else {
      lVar6 = *(longlong *)(param_6 + 0x10);
      local_80 = *(undefined8 *)(param_6 + 0x12);
      uVar2 = 0;
      local_88 = lVar6;
      if (param_6[1] != 0) {
        do {
          FUN_14009cbd0(param_3 + uVar2 * 2);
          uVar5 = (int)uVar2 + 1;
          uVar2 = (ulonglong)uVar5;
        } while (uVar5 < param_6[1]);
      }
      uVar2 = 0;
      if (param_6[1] != 0) {
        lVar9 = 0;
        do {
          uVar5 = *(uint *)(lVar9 + *(longlong *)(param_6 + 10));
          uVar7 = 0;
          uVar1 = uVar5 & 0xff;
          local_98 = param_3 + uVar2 * 2;
          local_78 = 0;
          *(longlong *)(lVar9 + *(longlong *)(param_6 + 10)) = lVar6 - *(longlong *)(param_6 + 0x10)
          ;
          uVar3 = 0;
          local_90 = uVar1;
          if (uVar5 >> 8 != 0) {
            do {
              uVar3 = FUN_140098a4c(&local_88,&local_70);
              if ((int)uVar3 != 0) {
                return uVar3;
              }
              uVar3 = local_70;
              lVar6 = local_88;
            } while ((uVar7 != uVar1) && (uVar7 = uVar7 + 1, uVar3 = local_78, uVar7 < uVar5 >> 8));
          }
          if (uVar7 == uVar5 >> 8) {
            return 0xb;
          }
          uVar4 = FUN_14009cbdc(local_98,uVar3,param_7);
          if ((int)uVar4 == 0) {
            return 2;
          }
          uVar5 = (int)uVar2 + 1;
          uVar2 = (ulonglong)uVar5;
          lVar9 = lVar9 + 8;
        } while (uVar5 < param_6[1]);
      }
      *(longlong *)(*(longlong *)(param_6 + 10) + uVar2 * 8) = lVar6 - *(longlong *)(param_6 + 0x10)
      ;
      uVar5 = 0;
      if (param_6[1] != 0) {
        lVar6 = 0;
        do {
          uVar2 = FUN_14009b7fc((longlong)param_1,lVar8);
          if ((int)uVar2 != 0) {
            return uVar2;
          }
          uVar2 = FUN_14009ca6c((longlong)param_6,uVar5,param_1,lVar8,(void *)*param_3,param_3[1],
                                param_7);
          if ((int)uVar2 != 0) {
            return uVar2;
          }
          if (((*(longlong *)(param_6 + 4) != 0) &&
              ((*(byte *)((ulonglong)(uVar5 >> 3) + *(longlong *)(param_6 + 4)) &
               (byte)(0x80 >> ((byte)uVar5 & 7))) != 0)) &&
             (uVar1 = FUN_14009b63c(*param_3,param_3[1]),
             uVar1 != *(uint *)(lVar6 + *(longlong *)(param_6 + 6)))) {
            return 3;
          }
          uVar5 = uVar5 + 1;
          param_3 = param_3 + 2;
          lVar6 = lVar6 + 4;
        } while (uVar5 < param_6[1]);
      }
      uVar2 = 0;
    }
  }
  return uVar2;
}


// ==== FUN_14009a110 @ 14009a110  undefined8 FUN_14009a110(longlong * param_1, uint param_2, longlong * param_3, longlong param_4, uint param_5, undefined8 * param_6)

undefined8
FUN_14009a110(longlong *param_1,uint param_2,longlong *param_3,longlong param_4,uint param_5,
             undefined8 *param_6)

{
  char cVar1;
  undefined8 uVar2;
  longlong lVar3;
  ulonglong uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  uint uVar7;
  uint local_38 [2];
  undefined4 *local_30;
  ulonglong uStack_28;
  
  uVar2 = FUN_140098ca8(param_3,param_2,param_1,param_6);
  if ((int)uVar2 != 0) {
    return uVar2;
  }
  if (param_3[1] == 0) {
LAB_14009a26d:
    uVar2 = 0x10;
  }
  else {
    param_3[1] = param_3[1] + -1;
    cVar1 = *(char *)*param_3;
    *param_3 = (longlong)((char *)*param_3 + 1);
    if (cVar1 == '\0') {
      puVar5 = (undefined4 *)*param_3;
      uVar4 = param_3[1];
    }
    else {
      uVar2 = FUN_140098b4c(param_3,local_38);
      if ((int)uVar2 != 0) {
        return uVar2;
      }
      if (param_5 <= local_38[0]) goto LAB_14009a26d;
      puVar5 = *(undefined4 **)(param_4 + (ulonglong)local_38[0] * 0x10);
      uVar4 = *(ulonglong *)(param_4 + 8 + (ulonglong)local_38[0] * 0x10);
    }
    local_30 = puVar5;
    uStack_28 = uVar4;
    if (param_2 == 0) {
      param_1[1] = 0;
    }
    else {
      lVar3 = (*(code *)*param_6)(param_6,(ulonglong)param_2 << 3);
      param_1[1] = lVar3;
      if (lVar3 == 0) {
        return 2;
      }
    }
    puVar6 = (undefined4 *)param_1[1];
    lVar3 = *param_1;
    uVar7 = 0;
    if (param_2 != 0) {
      do {
        if ((*(byte *)((ulonglong)(uVar7 >> 3) + lVar3) & (byte)(0x80 >> ((byte)uVar7 & 7))) == 0) {
          *puVar6 = 0;
          puVar6[1] = 0;
        }
        else {
          if (uVar4 < 8) goto LAB_14009a26d;
          uVar4 = uVar4 - 8;
          local_30 = puVar5 + 2;
          *puVar6 = *puVar5;
          puVar6[1] = puVar5[1];
          puVar5 = local_30;
          uStack_28 = uVar4;
        }
        uVar7 = uVar7 + 1;
        puVar6 = puVar6 + 2;
      } while (uVar7 < param_2);
    }
    if (cVar1 == '\0') {
      *param_3 = (longlong)local_30;
      param_3[1] = uStack_28;
    }
    uVar2 = 0;
  }
  return uVar2;
}


// ==== FUN_14009a294 @ 14009a294  ulonglong FUN_14009a294(uint * param_1, longlong * param_2, undefined8 * param_3, undefined8 * param_4, uint * param_5, undefined8 * param_6, undefined8 * param_7)

ulonglong FUN_14009a294(uint *param_1,longlong *param_2,undefined8 *param_3,undefined8 *param_4,
                       uint *param_5,undefined8 *param_6,undefined8 *param_7)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  byte bVar4;
  ulonglong uVar5;
  longlong lVar6;
  void *_Dst;
  ulonglong uVar7;
  longlong lVar8;
  longlong *plVar9;
  uint *puVar10;
  short *psVar11;
  ulonglong uVar12;
  ulonglong *puVar13;
  int iVar14;
  uint uVar15;
  byte *pbVar16;
  uint uVar17;
  byte *pbVar18;
  uint uVar19;
  char *_Src;
  byte *pbVar20;
  byte local_138;
  byte local_137;
  byte local_136;
  byte local_135;
  uint local_134;
  uint local_130;
  uint local_12c;
  byte *local_128;
  undefined8 local_120;
  uint local_118 [2];
  byte *local_110;
  longlong local_108;
  longlong local_100;
  ulonglong local_f8;
  longlong local_f0;
  byte *local_e8;
  longlong local_e0;
  undefined8 local_d8;
  longlong local_d0;
  uint local_c8;
  int local_c4;
  longlong local_c0 [4];
  byte *local_a0;
  longlong local_98;
  ulonglong local_90;
  ulonglong local_88 [2];
  uint local_78;
  uint local_74;
  undefined8 local_70;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  
  local_134 = 0;
  local_130 = 0;
  local_e8 = (byte *)0x0;
  local_d0 = 0;
  local_c0[2] = 0;
  local_c0[3] = 0;
  local_a0 = (byte *)0x0;
  local_98 = 0;
  local_c0[0] = 0;
  local_c0[1] = 0;
  local_c4 = 0;
  local_c8 = 0;
  uVar5 = FUN_140098a4c(param_2,&local_120);
  if ((int)uVar5 != 0) {
    return uVar5;
  }
  lVar6 = CONCAT44(local_120._4_4_,(uint)local_120);
  if (lVar6 == 2) {
    while( true ) {
      uVar5 = FUN_140098a4c(param_2,(ulonglong *)&local_128);
      if ((int)uVar5 != 0) {
        return uVar5;
      }
      if (local_128 == (byte *)0x0) break;
      uVar5 = FUN_140098bb4(param_2);
      if ((int)uVar5 != 0) {
        return uVar5;
      }
    }
    uVar5 = FUN_140098a4c(param_2,&local_120);
    if ((int)uVar5 != 0) {
      return uVar5;
    }
    lVar6 = CONCAT44(local_120._4_4_,(uint)local_120);
  }
  if (lVar6 == 3) {
    local_78 = 0;
    local_74 = 0;
    local_70 = 0;
    local_68 = 0;
    local_60 = 0;
    local_58 = 0;
    local_50 = 0;
    local_48 = 0;
    local_40 = 0;
    local_38 = 0;
    uVar5 = FUN_140099e54(param_3,param_2,param_4,8,*(longlong *)(param_1 + 0x14),&local_78,param_7)
    ;
    uVar19 = local_74;
    FUN_140098828(&local_78,(longlong)param_7);
    if ((int)uVar5 != 0) {
      return uVar5 & 0xffffffff;
    }
    *param_5 = uVar19;
    uVar5 = FUN_140098a4c(param_2,&local_120);
    if ((int)uVar5 != 0) {
      return uVar5;
    }
    lVar6 = CONCAT44(local_120._4_4_,(uint)local_120);
  }
  uVar19 = 0;
  if (lVar6 == 4) {
    puVar13 = (ulonglong *)(param_1 + 0x16);
    uVar5 = FUN_140099ce0(param_1,param_2,0x40000000,(longlong)param_4,*param_5,puVar13,&local_c8,
                          param_6);
    if ((int)uVar5 != 0) {
      return uVar5;
    }
    *puVar13 = *puVar13 + *(longlong *)(param_1 + 0x14);
    uVar5 = FUN_140098a4c(param_2,&local_120);
    if ((int)uVar5 != 0) {
      return uVar5;
    }
    lVar6 = CONCAT44(local_120._4_4_,(uint)local_120);
  }
  if (lVar6 == 0) {
    return 0;
  }
  if (lVar6 != 5) {
    return 0x10;
  }
  uVar5 = FUN_140098b4c(param_2,&local_134);
  if ((int)uVar5 != 0) {
    return uVar5;
  }
  param_1[0x18] = local_134;
  uVar5 = FUN_140098a4c(param_2,(ulonglong *)&local_128);
  if ((int)uVar5 != 0) {
    return uVar5;
  }
  while (pbVar18 = local_128, uVar2 = local_134, local_128 != (byte *)0x0) {
    uVar5 = FUN_140098a4c(param_2,&local_f8);
    if ((int)uVar5 != 0) {
      return uVar5;
    }
    uVar5 = param_2[1];
    if (uVar5 < local_f8) {
      return 0x10;
    }
    if (pbVar18 < (byte *)0x100) {
      iVar14 = (int)pbVar18;
      if (iVar14 == 0xe) {
        uVar19 = local_134 + 7 >> 3;
        if (uVar5 < uVar19) {
          return 0x10;
        }
        local_e8 = (byte *)*param_2;
        param_2[1] = uVar5 - uVar19;
        *param_2 = (longlong)(local_e8 + uVar19);
        local_130 = FUN_140098c6c(local_e8,local_134);
        uVar19 = local_130;
      }
      else if (iVar14 == 0xf) {
        uVar7 = (ulonglong)(uVar19 + 7 >> 3);
        if (uVar5 < uVar7) {
          return 0x10;
        }
        local_d0 = *param_2;
        param_2[1] = uVar5 - uVar7;
        *param_2 = local_d0 + uVar7;
      }
      else if (iVar14 == 0x11) {
        if (uVar5 == 0) {
          return 0x10;
        }
        param_2[1] = uVar5 - 1;
        cVar1 = *(char *)*param_2;
        _Src = (char *)*param_2 + 1;
        *param_2 = (longlong)_Src;
        if (cVar1 == '\0') {
          uVar5 = local_f8 - 1;
        }
        else {
          uVar5 = FUN_140098b4c(param_2,local_118);
          if ((int)uVar5 != 0) {
            return uVar5;
          }
          if (*param_5 <= local_118[0]) {
            return 0x10;
          }
          _Src = (char *)param_4[(ulonglong)local_118[0] * 2];
          uVar5 = param_4[(ulonglong)local_118[0] * 2 + 1];
        }
        if ((uVar5 & 1) != 0) {
          return 0x10;
        }
        lVar6 = (*(code *)*param_6)(param_6,(ulonglong)(local_134 + 1) << 3);
        puVar10 = (uint *)0x0;
        *(longlong *)(param_1 + 0x32) = lVar6;
        if (lVar6 == 0) {
          return 2;
        }
        if (uVar5 != 0) {
          _Dst = (void *)(*(code *)*param_6)(param_6,uVar5);
          *(void **)(param_1 + 0x34) = _Dst;
          if (_Dst == (void *)0x0) {
            return 2;
          }
          memcpy(_Dst,_Src,uVar5);
          puVar10 = param_1;
        }
        uVar12 = 0;
        puVar13 = *(ulonglong **)(puVar10 + 0x32);
        lVar6 = *(longlong *)(puVar10 + 0x34);
        *puVar13 = 0;
        uVar7 = uVar5;
        if (local_134 == 0) {
LAB_14009a77e:
          uVar7 = (ulonglong)(-(uint)(uVar7 != 0) & 0x10);
        }
        else {
          if (uVar5 < 2) {
            return 0x10;
          }
          if ((*(char *)(lVar6 + -2 + uVar5) == '\0') &&
             (uVar19 = local_134, *(char *)(lVar6 + -1 + uVar5) == '\0')) {
            do {
              puVar13 = puVar13 + 1;
              if (uVar12 == uVar5) {
                return 0x10;
              }
              for (psVar11 = (short *)(uVar12 + lVar6); *psVar11 != 0; psVar11 = psVar11 + 1) {
              }
              uVar12 = (longlong)psVar11 + (2 - lVar6);
              *puVar13 = uVar12 >> 1;
              uVar19 = uVar19 - 1;
            } while (uVar19 != 0);
            uVar7 = uVar12 - uVar5;
            goto LAB_14009a77e;
          }
          uVar7 = 0x10;
        }
        if ((int)uVar7 != 0) {
          return uVar7;
        }
        param_1 = puVar10;
        uVar19 = local_130;
        if (cVar1 == '\0') {
          param_2[1] = param_2[1] - uVar5;
          *param_2 = *param_2 + uVar5;
        }
      }
      else {
        if (iVar14 == 0x12) {
          puVar10 = param_1 + 0x2a;
LAB_14009a66e:
          uVar5 = FUN_14009a110((longlong *)puVar10,local_134,param_2,(longlong)param_4,*param_5,
                                param_6);
        }
        else {
          if (iVar14 == 0x14) {
            puVar10 = param_1 + 0x26;
            goto LAB_14009a66e;
          }
          if (iVar14 != 0x15) goto LAB_14009a56b;
          FUN_140098790((undefined8 *)(param_1 + 0x22),(longlong)param_6);
          uVar5 = FUN_140098ca8(param_2,local_134,(undefined8 *)(param_1 + 0x22),param_6);
          if ((int)uVar5 != 0) {
            return uVar5;
          }
          if (param_2[1] == 0) {
            return 0x10;
          }
          param_2[1] = param_2[1] + -1;
          cVar1 = *(char *)*param_2;
          *param_2 = (longlong)((char *)*param_2 + 1);
          plVar9 = param_2;
          if (cVar1 != '\0') {
            uVar5 = FUN_140098b4c(param_2,(uint *)&local_120);
            if ((int)uVar5 != 0) {
              return uVar5;
            }
            if (*param_5 <= (uint)local_120) {
              return 0x10;
            }
            local_e0 = param_4[(ulonglong)(uint)local_120 * 2];
            local_d8 = param_4[(ulonglong)(uint)local_120 * 2 + 1];
            plVar9 = &local_e0;
          }
          uVar5 = FUN_140098da0(plVar9,local_134,(longlong *)(param_1 + 0x22),param_6);
        }
        if ((int)uVar5 != 0) {
          return uVar5;
        }
      }
    }
    else {
LAB_14009a56b:
      *param_2 = *param_2 + local_f8;
      param_2[1] = uVar5 - local_f8;
    }
    uVar5 = FUN_140098a4c(param_2,(ulonglong *)&local_128);
    if ((int)uVar5 != 0) {
      return uVar5;
    }
  }
  if (local_134 - uVar19 != local_c8) {
    return 0x10;
  }
  uVar5 = FUN_140098a4c(param_2,(ulonglong *)&local_128);
  pbVar18 = (byte *)0x0;
  while( true ) {
    if ((int)uVar5 != 0) {
      return uVar5;
    }
    if (local_128 == (byte *)0x0) break;
    uVar5 = FUN_140098bb4(param_2);
    if ((int)uVar5 != 0) {
      return uVar5;
    }
    uVar5 = FUN_140098a4c(param_2,(ulonglong *)&local_128);
  }
  lVar6 = *(longlong *)(param_1 + 0x10);
  local_d8 = *(undefined8 *)(param_1 + 0x12);
  local_130 = 0xffffffff;
  local_118[0] = 0;
  local_12c = 0;
  local_100 = 0;
  local_128 = (byte *)0x0;
  local_110 = (byte *)0x0;
  local_135 = 0;
  local_136 = 0;
  local_138 = 0;
  local_137 = 0x80;
  local_f0 = lVar6;
  local_e0 = lVar6;
  lVar8 = (*(code *)*param_6)(param_6,(ulonglong)(param_1[1] + 1) << 2);
  *(longlong *)(param_1 + 0x2e) = lVar8;
  if (lVar8 == 0) {
    return 2;
  }
  if (param_1[0x18] == 0) {
    param_1[0x30] = 0;
    param_1[0x31] = 0;
  }
  else {
    lVar8 = (*(code *)*param_6)(param_6,(ulonglong)param_1[0x18] << 2);
    *(longlong *)(param_1 + 0x30) = lVar8;
    if (lVar8 == 0) {
      return 2;
    }
  }
  lVar8 = (*(code *)*param_6)(param_6,(ulonglong)(param_1[0x18] + 1) << 3);
  *(longlong *)(param_1 + 0x1a) = lVar8;
  if (lVar8 == 0) {
    return 2;
  }
  if ((param_1[0x18] + 7 & 0xfffffff8) == 0) {
    param_1[0x1c] = 0;
    param_1[0x1d] = 0;
  }
  else {
    lVar8 = (*(code *)*param_6)(param_6,param_1[0x18] + 7 >> 3);
    *(longlong *)(param_1 + 0x1c) = lVar8;
    if (lVar8 == 0) {
      return 2;
    }
  }
  uVar5 = (ulonglong)param_1[0x18];
  if (uVar5 == 0) {
    param_1[0x1e] = 0;
    param_1[0x1f] = 0;
    param_1[0x20] = 0;
    param_1[0x21] = 0;
  }
  else {
    lVar8 = (*(code *)*param_6)(param_6,uVar5 + 7 >> 3);
    *(longlong *)(param_1 + 0x1e) = lVar8;
    if (lVar8 == 0) {
      return 2;
    }
    lVar8 = (*(code *)*param_6)(param_6,uVar5 << 2);
    *(longlong *)(param_1 + 0x20) = lVar8;
    if (lVar8 == 0) {
      return 2;
    }
  }
  pbVar16 = pbVar18;
  if (local_98 != 0) {
    local_98 = local_98 + -1;
    local_135 = *local_a0;
    local_a0 = local_a0 + 1;
    pbVar16 = local_a0;
    local_110 = local_a0;
    if (local_135 == 0) {
      pbVar16 = local_a0 + (local_c4 + 7U >> 3);
      local_128 = local_a0;
      local_110 = local_a0 + (local_c4 + 7U >> 3);
    }
  }
  lVar8 = 0;
  local_108 = 0;
  pbVar20 = pbVar18;
  if (uVar2 == 0) goto LAB_14009ae94;
  local_f8 = 0;
  do {
    uVar19 = (uint)pbVar20;
    if (local_137 == 0) {
      uVar5 = (ulonglong)(uVar19 - 1 >> 3);
      local_137 = 0x80;
      *(byte *)(uVar5 + *(longlong *)(param_1 + 0x1c)) = local_136;
      *(byte *)(uVar5 + *(longlong *)(param_1 + 0x1e)) = local_138;
      local_136 = 0;
      local_138 = 0;
    }
    *(longlong *)(local_f8 + *(longlong *)(param_1 + 0x1a)) = local_100;
    *(undefined4 *)(lVar8 + *(longlong *)(param_1 + 0x20)) = 0;
    iVar14 = (int)pbVar18;
    bVar4 = (byte)pbVar20;
    uVar2 = local_130;
    if ((local_e8 == (byte *)0x0) ||
       ((local_e8[(ulonglong)pbVar20 >> 3] & (byte)(0x80 >> (bVar4 & 7))) == 0)) {
      if (iVar14 == 0) {
        while( true ) {
          if (param_1[1] <= local_12c) {
            return 0x10;
          }
          *(uint *)(*(longlong *)(param_1 + 0x2e) + local_108 * 4) = uVar19;
          local_130 = 1;
          local_120._0_4_ = 1;
          uVar2 = (uint)local_120;
          if (local_c0[0] == 0) break;
          uVar5 = FUN_140098b4c(local_c0,(uint *)&local_120);
          if ((int)uVar5 != 0) {
            return uVar5;
          }
          uVar2 = (uint)local_120;
          if ((uint)local_120 != 0) break;
          local_12c = local_12c + 1;
          local_108 = local_108 + 1;
        }
      }
LAB_14009ac5a:
      local_130 = uVar2;
      uVar5 = 0;
      *(uint *)(lVar8 + *(longlong *)(param_1 + 0x30)) = local_12c;
      if ((local_e8 == (byte *)0x0) ||
         ((local_e8[(ulonglong)pbVar20 >> 3] & (byte)(0x80 >> (bVar4 & 7))) == 0)) {
        pbVar18 = (byte *)(ulonglong)(iVar14 + 1U);
        if (iVar14 + 1U < local_130) {
          uVar5 = FUN_140098a4c(local_c0 + 2,local_88);
          if ((int)uVar5 != 0) {
            return uVar5;
          }
          local_100 = local_100 + local_88[0];
          if ((local_135 != 0) || ((local_128 != (byte *)0x0 && ((*local_128 & 0x80) != 0)))) {
            local_110 = pbVar16 + 4;
            local_138 = local_138 | local_137;
            *(undefined4 *)(lVar8 + *(longlong *)(param_1 + 0x20)) = *(undefined4 *)pbVar16;
          }
        }
        else {
          uVar2 = *(uint *)(*(longlong *)(param_1 + 10) + local_108 * 8);
          uVar15 = 0;
          uVar17 = uVar2 >> 8;
          *(longlong *)(*(longlong *)(param_1 + 10) + local_108 * 8) =
               local_f0 - *(longlong *)(param_1 + 0x10);
          uVar7 = uVar5;
          if (uVar17 != 0) {
            do {
              uVar15 = (uint)uVar7;
              uVar7 = FUN_140098a4c(&local_e0,&local_90);
              if ((int)uVar7 != 0) {
                return uVar7;
              }
              uVar12 = local_90;
              if (uVar15 == (uVar2 & 0xff)) break;
              uVar15 = uVar15 + 1;
              uVar7 = (ulonglong)uVar15;
              uVar12 = uVar5;
            } while (uVar15 < uVar17);
            local_f0 = local_e0;
            uVar5 = uVar12;
          }
          pbVar18 = (byte *)0x0;
          if (uVar15 == uVar17) {
            return 0xb;
          }
          lVar6 = *(longlong *)
                   (*(longlong *)(param_1 + 0x1a) +
                   (ulonglong)*(uint *)(*(longlong *)(param_1 + 0x2e) + local_108 * 4) * 8);
          if (uVar5 < (ulonglong)(local_100 - lVar6)) {
            return 0x10;
          }
          local_100 = lVar6 + uVar5;
          if (((local_130 == 1) && (*(longlong *)(param_1 + 4) != 0)) &&
             ((*(byte *)(((ulonglong)pbVar20 >> 3) + *(longlong *)(param_1 + 4)) &
              (byte)(0x80 >> (bVar4 & 7))) != 0)) {
            *(undefined4 *)(lVar8 + *(longlong *)(param_1 + 0x20)) =
                 *(undefined4 *)(*(longlong *)(param_1 + 6) + local_108 * 4);
            local_138 = local_138 | local_137;
          }
          else if ((local_135 != 0) || ((local_128 != (byte *)0x0 && ((*local_128 & 0x80) != 0)))) {
            uVar3 = *(undefined4 *)local_110;
            local_110 = local_110 + 4;
            *(undefined4 *)(lVar8 + *(longlong *)(param_1 + 0x20)) = uVar3;
            local_138 = local_138 | local_137;
          }
          local_12c = local_12c + 1;
          local_108 = local_108 + 1;
          lVar6 = local_f0;
        }
      }
    }
    else {
      if ((local_d0 == 0) ||
         ((*(byte *)((ulonglong)(local_118[0] >> 3) + local_d0) &
          (byte)(0x80 >> ((byte)local_118[0] & 7))) == 0)) {
        local_136 = local_136 | local_137;
      }
      local_118[0] = local_118[0] + 1;
      if (iVar14 != 0) goto LAB_14009ac5a;
      *(undefined4 *)(lVar8 + *(longlong *)(param_1 + 0x30)) = 0xffffffff;
    }
    local_137 = local_137 >> 1;
    pbVar20 = (byte *)(ulonglong)(uVar19 + 1);
    local_f8 = local_f8 + 8;
    lVar8 = lVar8 + 4;
    pbVar16 = local_110;
    if (local_134 <= uVar19 + 1) {
      if (local_137 != 0x80) {
        *(byte *)((ulonglong)(uVar19 >> 3) + *(longlong *)(param_1 + 0x1c)) = local_136;
        *(byte *)((ulonglong)(uVar19 >> 3) + *(longlong *)(param_1 + 0x1e)) = local_138;
      }
LAB_14009ae94:
      *(longlong *)(*(longlong *)(param_1 + 0x1a) + (longlong)pbVar20 * 8) = local_100;
      *(int *)(*(longlong *)(param_1 + 0x2e) + (ulonglong)local_12c * 4) = (int)pbVar20;
      *(longlong *)(*(longlong *)(param_1 + 10) + (ulonglong)local_12c * 8) =
           lVar6 - *(longlong *)(param_1 + 0x10);
      return 0;
    }
  } while( true );
}


// ==== FUN_14009aeec @ 14009aeec  ulonglong FUN_14009aeec(uint * param_1, longlong * param_2, undefined8 * param_3, undefined8 * param_4, undefined8 * param_5)

ulonglong FUN_14009aeec(uint *param_1,longlong *param_2,undefined8 *param_3,undefined8 *param_4,
                       undefined8 *param_5)

{
  ulonglong uVar1;
  ulonglong uVar2;
  undefined8 *puVar3;
  ulonglong uVar4;
  longlong lVar5;
  uint local_a8 [4];
  undefined8 local_98 [16];
  
  local_a8[0] = 0;
  puVar3 = local_98;
  lVar5 = 8;
  do {
    FUN_14009cbd0(puVar3);
    puVar3 = puVar3 + 2;
    lVar5 = lVar5 + -1;
  } while (lVar5 != 0);
  uVar1 = FUN_14009a294(param_1,param_2,param_3,local_98,local_a8,param_4,param_5);
  uVar2 = uVar1 & 0xffffffff;
  uVar4 = (ulonglong)local_a8[0];
  if (local_a8[0] != 0) {
    puVar3 = local_98;
    do {
      FUN_14009cc24(puVar3,(longlong)param_5);
      puVar3 = puVar3 + 2;
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
  }
  if ((int)uVar1 == 0) {
    uVar2 = (ulonglong)(-(uint)(param_2[1] != 0) & 0xb);
  }
  return uVar2;
}


// ==== FUN_14009afc8 @ 14009afc8  undefined FUN_14009afc8(uint * param_1, undefined8 * param_2, undefined8 * param_3, undefined8 * param_4)

void FUN_14009afc8(uint *param_1,undefined8 *param_2,undefined8 *param_3,undefined8 *param_4)

{
  int iVar1;
  ulonglong uVar2;
  undefined8 uVar3;
  ulonglong uVar4;
  longlong lVar5;
  uint uVar6;
  undefined1 auStackY_148 [32];
  ulonglong local_108;
  longlong local_100;
  undefined8 local_f8;
  longlong local_f0;
  undefined8 local_e8;
  longlong local_e0;
  longlong local_d8;
  undefined8 local_d0;
  uint local_c8 [20];
  char local_78 [6];
  char local_72;
  uint local_70;
  ulonglong local_6c;
  longlong local_64;
  uint local_5c;
  ulonglong local_58;
  
  local_58 = DAT_140103510 ^ (ulonglong)auStackY_148;
  local_e0 = 0;
  iVar1 = (*(code *)param_2[3])(param_2,&local_e0,1);
  if ((iVar1 != 0) ||
     (uVar2 = FUN_14009b870((longlong)param_2,(longlong)local_78,0x20,0x11), (int)uVar2 != 0))
  goto LAB_14009b2fe;
  uVar6 = 0;
  lVar5 = 0;
  do {
    if (local_78[lVar5] != (&DAT_1400d23f8)[lVar5]) goto LAB_14009b2fe;
    uVar6 = uVar6 + 1;
    lVar5 = lVar5 + 1;
  } while (uVar6 < 6);
  if (local_72 != '\0') goto LAB_14009b2fe;
  *(longlong *)(param_1 + 0x14) = local_e0 + 0x20;
  uVar6 = FUN_14009b63c(&local_6c,0x14);
  if ((((uVar6 != local_70) || (local_64 == 0)) || (uVar2 = local_64 + local_6c, uVar2 < local_6c))
     || (uVar2 + 0x20 < local_6c)) goto LAB_14009b2fe;
  local_108 = 0;
  iVar1 = (*(code *)param_2[3])(param_2,&local_108,2);
  if ((((iVar1 != 0) || (local_108 < local_6c + local_e0)) ||
      ((uVar4 = local_6c + local_e0 + 0x20, local_108 < uVar4 ||
       ((local_108 < local_e0 + 0x20 + uVar2 ||
        (iVar1 = FUN_14009b7fc((longlong)param_2,uVar4), iVar1 != 0)))))) ||
     (uVar3 = FUN_14009cbdc(&local_100,local_64,param_4), (int)uVar3 == 0)) goto LAB_14009b2fe;
  iVar1 = FUN_14009b8dc((longlong)param_2,local_100,local_64);
  if ((iVar1 == 0) && (uVar6 = FUN_14009b63c(local_100,local_64), uVar6 == local_5c)) {
    local_f0 = local_100;
    local_e8 = local_f8;
    uVar3 = FUN_140098a4c(&local_f0,&local_108);
    uVar2 = local_108;
    if ((int)uVar3 == 0) {
      if (local_108 == 0x17) {
        FUN_14009cbd0(&local_d8);
        local_c8[0] = 0;
        local_c8[1] = 0;
        local_c8[2] = 0;
        local_c8[3] = 0;
        local_c8[4] = 0;
        local_c8[5] = 0;
        local_c8[6] = 0;
        local_c8[7] = 0;
        local_c8[8] = 0;
        local_c8[9] = 0;
        local_c8[10] = 0;
        local_c8[0xb] = 0;
        local_c8[0xc] = 0;
        local_c8[0xd] = 0;
        local_c8[0xe] = 0;
        local_c8[0xf] = 0;
        local_c8[0x10] = 0;
        local_c8[0x11] = 0;
        uVar4 = FUN_140099e54(param_2,&local_f0,&local_d8,1,*(longlong *)(param_1 + 0x14),local_c8,
                              param_4);
        iVar1 = (int)uVar4;
        FUN_140098828(local_c8,(longlong)param_4);
        if (iVar1 == 0) {
          FUN_14009cc24(&local_100,(longlong)param_4);
          local_100 = local_d8;
          local_f8 = local_d0;
          local_f0 = local_d8;
          local_e8 = local_d0;
          uVar3 = FUN_140098a4c(&local_f0,&local_108);
          iVar1 = (int)uVar3;
          uVar2 = local_108;
        }
        else {
          FUN_14009cc24(&local_d8,(longlong)param_4);
        }
        if (iVar1 != 0) goto LAB_14009b2ef;
      }
      if (uVar2 == 1) {
        FUN_14009aeec(param_1,&local_f0,param_2,param_3,param_4);
      }
    }
  }
LAB_14009b2ef:
  FUN_14009cc24(&local_100,(longlong)param_4);
LAB_14009b2fe:
  __security_check_cookie(local_58 ^ (ulonglong)auStackY_148);
  return;
}


// ==== FUN_14009b330 @ 14009b330  int FUN_14009b330(uint * param_1, undefined8 * param_2, undefined8 * param_3, undefined8 * param_4)

int FUN_14009b330(uint *param_1,undefined8 *param_2,undefined8 *param_3,undefined8 *param_4)

{
  int iVar1;
  
  iVar1 = FUN_14009afc8(param_1,param_2,param_3,param_4);
  if (iVar1 != 0) {
    FUN_140098948(param_1,(longlong)param_3);
  }
  return iVar1;
}


// ==== FUN_14009b370 @ 14009b370  ulonglong FUN_14009b370(longlong param_1, undefined8 * param_2, uint param_3, uint * param_4, longlong * param_5, ulonglong * param_6, longlong * param_7, longlong * param_8, undefined8 * param_9, undefined8 * param_10)

ulonglong FUN_14009b370(longlong param_1,undefined8 *param_2,uint param_3,uint *param_4,
                       longlong *param_5,ulonglong *param_6,longlong *param_7,longlong *param_8,
                       undefined8 *param_9,undefined8 *param_10)

{
  uint uVar1;
  uint uVar2;
  longlong lVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  ulonglong uVar6;
  longlong lVar7;
  
  uVar5 = 0;
  uVar2 = *(uint *)((ulonglong)param_3 * 4 + *(longlong *)(param_1 + 0xc0));
  *param_7 = 0;
  *param_8 = 0;
  if (uVar2 == 0xffffffff) {
    (*(code *)param_9[1])(param_9,*param_5);
    *param_4 = 0xffffffff;
    *param_5 = 0;
    *param_6 = 0;
    return 0;
  }
  if ((*param_5 == 0) || (*param_4 != uVar2)) {
    lVar7 = (ulonglong)uVar2 * 4;
    uVar6 = *(longlong *)
             (*(longlong *)(param_1 + 0x68) +
             (ulonglong)*(uint *)(*(longlong *)(param_1 + 0xb8) + (ulonglong)(uVar2 + 1) * 4) * 8) -
            *(longlong *)
             (*(longlong *)(param_1 + 0x68) +
             (ulonglong)*(uint *)(lVar7 + *(longlong *)(param_1 + 0xb8)) * 8);
    *param_4 = uVar2;
    (*(code *)param_9[1])(param_9,*param_5);
    *param_5 = 0;
    *param_6 = uVar6;
    if (uVar6 != 0) {
      lVar3 = (*(code *)*param_9)(param_9,uVar6);
      *param_5 = lVar3;
      if (lVar3 == 0) {
        return 2;
      }
    }
    uVar4 = FUN_14009ca6c(param_1,uVar2,param_2,*(longlong *)(param_1 + 0x58),(void *)*param_5,uVar6
                          ,param_10);
    uVar5 = uVar4 & 0xffffffff;
    if ((int)uVar4 != 0) {
      return uVar5;
    }
    if (((*(longlong *)(param_1 + 0x10) != 0) &&
        ((*(byte *)((ulonglong)(uVar2 >> 3) + *(longlong *)(param_1 + 0x10)) &
         (byte)(0x80 >> ((byte)uVar2 & 7))) != 0)) &&
       (uVar1 = FUN_14009b63c(*param_5,uVar6),
       uVar1 != *(uint *)(lVar7 + *(longlong *)(param_1 + 0x18)))) {
      uVar5 = 3;
    }
    if ((int)uVar5 != 0) {
      return uVar5;
    }
  }
  lVar7 = *(longlong *)(*(longlong *)(param_1 + 0x68) + (ulonglong)param_3 * 8);
  *param_7 = lVar7 - *(longlong *)
                      (*(longlong *)(param_1 + 0x68) +
                      (ulonglong)*(uint *)(*(longlong *)(param_1 + 0xb8) + (ulonglong)uVar2 * 4) * 8
                      );
  lVar7 = *(longlong *)(*(longlong *)(param_1 + 0x68) + (ulonglong)(param_3 + 1) * 8) - lVar7;
  *param_8 = lVar7;
  if (*param_6 < (ulonglong)(*param_7 + lVar7)) {
    uVar5 = 0xb;
  }
  else if (((*(longlong *)(param_1 + 0x78) != 0) &&
           ((*(byte *)((ulonglong)(param_3 >> 3) + *(longlong *)(param_1 + 0x78)) &
            (byte)(0x80 >> ((byte)param_3 & 7))) != 0)) &&
          (uVar2 = FUN_14009b63c(*param_7 + *param_5,lVar7),
          uVar2 != *(uint *)((ulonglong)param_3 * 4 + *(longlong *)(param_1 + 0x80)))) {
    uVar5 = 3;
  }
  return uVar5;
}


// ==== FUN_14009b5e4 @ 14009b5e4  longlong FUN_14009b5e4(longlong param_1, longlong param_2, undefined2 * param_3)

longlong FUN_14009b5e4(longlong param_1,longlong param_2,undefined2 *param_3)

{
  longlong lVar1;
  longlong lVar2;
  longlong lVar3;
  
  lVar1 = *(longlong *)(*(longlong *)(param_1 + 200) + param_2 * 8);
  lVar3 = *(longlong *)(*(longlong *)(param_1 + 200) + 8 + param_2 * 8) - lVar1;
  if ((param_3 != (undefined2 *)0x0) && (lVar3 != 0)) {
    lVar2 = (*(longlong *)(param_1 + 0xd0) + lVar1 * 2) - (longlong)param_3;
    lVar1 = lVar3;
    do {
      *param_3 = *(undefined2 *)(lVar2 + (longlong)param_3);
      param_3 = param_3 + 1;
      lVar1 = lVar1 + -1;
    } while (lVar1 != 0);
  }
  return lVar3;
}


// ==== FUN_14009b63c @ 14009b63c  uint FUN_14009b63c(undefined8 param_1, undefined8 param_2)

uint FUN_14009b63c(undefined8 param_1,undefined8 param_2)

{
  uint uVar1;
  
  uVar1 = (*DAT_140106d80)(0xffffffff,param_1,param_2,&DAT_140104d80);
  return ~uVar1;
}


// ==== FUN_14009b690 @ 14009b690  undefined FUN_14009b690(void)

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_14009b690(void)

{
  undefined8 uVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  ulonglong uVar5;
  longlong lVar6;
  
  uVar2 = 0;
  puVar3 = &DAT_140104d80;
  do {
    lVar6 = 8;
    uVar4 = uVar2;
    do {
      uVar4 = ~((uVar4 & 1) - 1) & 0xedb88320 ^ uVar4 >> 1;
      lVar6 = lVar6 + -1;
    } while (lVar6 != 0);
    uVar2 = uVar2 + 1;
    *puVar3 = uVar4;
    puVar3 = puVar3 + 1;
  } while (uVar2 < 0x100);
  if (uVar2 < 0x800) {
    puVar3 = &DAT_140104d80 + (int)uVar2;
    uVar5 = (ulonglong)(0x800 - uVar2);
    do {
      *puVar3 = (&DAT_140104d80)[puVar3[-0x100] & 0xff] ^ puVar3[-0x100] >> 8;
      puVar3 = puVar3 + 1;
      uVar5 = uVar5 - 1;
    } while (uVar5 != 0);
  }
  _DAT_140104d68 = FUN_14009ce00;
  DAT_140106d80 = FUN_14009ce00;
  _DAT_140104d60 = FUN_14009cee0;
  uVar1 = FUN_14009cce8();
  if ((int)uVar1 == 0) {
    DAT_140106d80 = FUN_14009cee0;
  }
  return;
}


// ==== FUN_14009b754 @ 14009b754  ulonglong FUN_14009b754(undefined8 * param_1, longlong param_2, longlong param_3, uint param_4)

ulonglong FUN_14009b754(undefined8 *param_1,longlong param_2,longlong param_3,uint param_4)

{
  ulonglong uVar1;
  longlong local_res18;
  
  if (param_3 != 0) {
    do {
      local_res18 = param_3;
      uVar1 = (*(code *)*param_1)(param_1,param_2,&local_res18);
      if ((int)uVar1 != 0) {
        return uVar1;
      }
      if (local_res18 == 0) {
        return (ulonglong)param_4;
      }
      param_2 = param_2 + local_res18;
      param_3 = param_3 - local_res18;
    } while (param_3 != 0);
  }
  return 0;
}


// ==== FUN_14009b7cc @ 14009b7cc  ulonglong FUN_14009b7cc(undefined8 * param_1, undefined8 param_2)

ulonglong FUN_14009b7cc(undefined8 *param_1,undefined8 param_2)

{
  ulonglong uVar1;
  longlong local_res8 [4];
  
  local_res8[0] = 1;
  uVar1 = (*(code *)*param_1)(param_1,param_2,local_res8);
  if ((int)uVar1 == 0) {
    uVar1 = (ulonglong)(-(uint)(local_res8[0] != 1) & 6);
  }
  return uVar1;
}


// ==== FUN_14009b7fc @ 14009b7fc  undefined FUN_14009b7fc(longlong param_1, undefined8 param_2)

void FUN_14009b7fc(longlong param_1,undefined8 param_2)

{
  undefined8 local_res8 [4];
  
  local_res8[0] = param_2;
  (**(code **)(param_1 + 0x18))(param_1,local_res8,0);
  return;
}


// ==== FUN_14009b818 @ 14009b818  undefined8 FUN_14009b818(undefined8 * param_1, void * param_2, size_t * param_3)

undefined8 FUN_14009b818(undefined8 *param_1,void *param_2,size_t *param_3)

{
  undefined8 uVar1;
  void *local_res18 [2];
  
  if (*param_3 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = (*(code *)*param_1)(param_1,local_res18);
    if ((int)uVar1 == 0) {
      memcpy(param_2,local_res18[0],*param_3);
      uVar1 = (*(code *)param_1[1])(param_1,*param_3);
    }
  }
  return uVar1;
}


// ==== FUN_14009b870 @ 14009b870  ulonglong FUN_14009b870(longlong param_1, longlong param_2, longlong param_3, uint param_4)

ulonglong FUN_14009b870(longlong param_1,longlong param_2,longlong param_3,uint param_4)

{
  ulonglong uVar1;
  longlong local_res18;
  
  if (param_3 != 0) {
    do {
      local_res18 = param_3;
      uVar1 = (**(code **)(param_1 + 0x10))(param_1,param_2,&local_res18);
      if ((int)uVar1 != 0) {
        return uVar1;
      }
      if (local_res18 == 0) {
        return (ulonglong)param_4;
      }
      param_2 = param_2 + local_res18;
      param_3 = param_3 - local_res18;
    } while (param_3 != 0);
  }
  return 0;
}


// ==== FUN_14009b8dc @ 14009b8dc  undefined FUN_14009b8dc(longlong param_1, longlong param_2, longlong param_3)

void FUN_14009b8dc(longlong param_1,longlong param_2,longlong param_3)

{
  FUN_14009b870(param_1,param_2,param_3,6);
  return;
}


// ==== FUN_14009b8e8 @ 14009b8e8  undefined4 FUN_14009b8e8(longlong param_1, longlong * param_2, ulonglong * param_3)

undefined4 FUN_14009b8e8(longlong param_1,longlong *param_2,ulonglong *param_3)

{
  undefined4 uVar1;
  ulonglong local_res8;
  
  uVar1 = 0;
  local_res8 = *(longlong *)(param_1 + 0x30) - *(longlong *)(param_1 + 0x28);
  if ((local_res8 == 0) && (*param_3 != 0)) {
    *(undefined8 *)(param_1 + 0x28) = 0;
    local_res8 = 0x4000;
    uVar1 = (*(code *)**(undefined8 **)(param_1 + 0x20))
                      (*(undefined8 **)(param_1 + 0x20),param_1 + 0x38,&local_res8);
    *(ulonglong *)(param_1 + 0x30) = local_res8;
  }
  if (local_res8 < *param_3) {
    *param_3 = local_res8;
  }
  *param_2 = *(longlong *)(param_1 + 0x28) + 0x38 + param_1;
  return uVar1;
}


// ==== FUN_14009b964 @ 14009b964  undefined FUN_14009b964(longlong param_1, longlong * param_2, ulonglong * param_3)

void FUN_14009b964(longlong param_1,longlong *param_2,ulonglong *param_3)

{
  ulonglong uVar1;
  
  uVar1 = *(longlong *)(param_1 + 0x30) - *(longlong *)(param_1 + 0x28);
  if ((uVar1 == 0) && (*param_3 != 0)) {
    *(undefined8 *)(param_1 + 0x28) = 0;
    if (0x4000 < *param_3) {
      *param_3 = 0x4000;
    }
    (*(code *)**(undefined8 **)(param_1 + 0x20))(*(undefined8 **)(param_1 + 0x20),param_1 + 0x38);
    uVar1 = *param_3;
    *(ulonglong *)(param_1 + 0x30) = uVar1;
  }
  if (uVar1 < *param_3) {
    *param_3 = uVar1;
  }
  *param_2 = *(longlong *)(param_1 + 0x28) + 0x38 + param_1;
  return;
}


// ==== FUN_14009b9e0 @ 14009b9e0  undefined8 FUN_14009b9e0(longlong param_1, void * param_2, ulonglong * param_3)

undefined8 FUN_14009b9e0(longlong param_1,void *param_2,ulonglong *param_3)

{
  undefined8 uVar1;
  ulonglong _Size;
  
  _Size = *(longlong *)(param_1 + 0x30) - *(longlong *)(param_1 + 0x28);
  if (_Size == 0) {
    uVar1 = (*(code *)**(undefined8 **)(param_1 + 0x20))(*(undefined8 **)(param_1 + 0x20));
  }
  else {
    if (*param_3 < _Size) {
      _Size = *param_3;
    }
    memcpy(param_2,(void *)(*(longlong *)(param_1 + 0x28) + 0x38 + param_1),_Size);
    *(longlong *)(param_1 + 0x28) = *(longlong *)(param_1 + 0x28) + _Size;
    *param_3 = _Size;
    uVar1 = 0;
  }
  return uVar1;
}


// ==== FUN_14009ba58 @ 14009ba58  undefined FUN_14009ba58(undefined8 * param_1, int param_2)

void FUN_14009ba58(undefined8 *param_1,int param_2)

{
  code *pcVar1;
  
  pcVar1 = FUN_14009b964;
  if (param_2 != 0) {
    pcVar1 = FUN_14009b8e8;
  }
  *param_1 = pcVar1;
  param_1[1] = &LAB_14009b9d8;
  param_1[2] = FUN_14009b9e0;
  param_1[3] = &LAB_14009ba40;
  return;
}


// ==== FUN_14009ba94 @ 14009ba94  undefined FUN_14009ba94(longlong param_1)

void FUN_14009ba94(longlong param_1)

{
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined8 *)(param_1 + 0x28) = 0;
  return;
}


// ==== FUN_14009bad0 @ 14009bad0  undefined1 FUN_14009bad0(longlong param_1)

undefined1 FUN_14009bad0(longlong param_1)

{
  undefined1 *puVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  longlong local_res8;
  
  puVar1 = *(undefined1 **)(param_1 + 8);
  if (puVar1 == *(undefined1 **)(param_1 + 0x10)) {
    if (*(int *)(param_1 + 0x2c) == 0) {
      local_res8 = (longlong)puVar1 - *(longlong *)(param_1 + 0x18);
      *(longlong *)(param_1 + 0x20) = *(longlong *)(param_1 + 0x20) + local_res8;
      uVar3 = (**(code **)(*(longlong *)(param_1 + 0x30) + 8))(*(longlong *)(param_1 + 0x30));
      *(undefined4 *)(param_1 + 0x2c) = uVar3;
      local_res8 = 0x2000000;
      uVar3 = (*(code *)**(undefined8 **)(param_1 + 0x30))
                        (*(undefined8 **)(param_1 + 0x30),param_1 + 0x18,&local_res8);
      puVar1 = *(undefined1 **)(param_1 + 0x18);
      *(undefined4 *)(param_1 + 0x2c) = uVar3;
      *(undefined1 **)(param_1 + 8) = puVar1;
      *(undefined1 **)(param_1 + 0x10) = puVar1 + local_res8;
      if (local_res8 != 0) {
        uVar2 = *puVar1;
        *(undefined1 **)(param_1 + 8) = puVar1 + 1;
        return uVar2;
      }
    }
    *(undefined4 *)(param_1 + 0x28) = 1;
    uVar2 = 0;
  }
  else {
    uVar2 = *puVar1;
    *(undefined1 **)(param_1 + 8) = puVar1 + 1;
  }
  return uVar2;
}


// ==== FUN_14009bb6c @ 14009bb6c  undefined FUN_14009bb6c(byte * param_1, int param_2, undefined8 param_3, undefined8 param_4, longlong param_5, ulonglong param_6, undefined8 * param_7)

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void FUN_14009bb6c(byte *param_1,int param_2,longlong param_3,undefined8 param_4,longlong param_5,
                  ulonglong param_6,undefined8 *param_7)

{
  byte bVar1;
  bool bVar2;
  uint uVar3;
  undefined8 uVar4;
  undefined7 extraout_var;
  ulonglong uVar5;
  undefined1 auStack_4ba8 [32];
  code *local_4b88;
  undefined8 local_4b80;
  undefined8 local_4b78;
  undefined8 local_4b70;
  undefined8 local_4b68;
  int local_4b60;
  undefined4 local_4b5c;
  undefined8 local_4b58;
  undefined8 local_4b50 [4];
  code **local_4b30;
  ulonglong local_4b28 [2398];
  ulonglong local_38;
  undefined8 uStack_30;
  
  uStack_30 = 0x14009bb83;
  local_38 = DAT_140103510 ^ (ulonglong)auStack_4ba8;
  uVar5 = 0;
  local_4b80 = 0;
  local_4b78 = 0;
  local_4b70 = 0;
  local_4b88 = FUN_14009bad0;
  local_4b60 = 0;
  local_4b5c = 0;
  local_4b68 = 0;
  local_4b58 = param_4;
  if (param_2 == 5) {
    bVar1 = *param_1;
    uVar3 = *(uint *)(param_1 + 1);
    if ((bVar1 - 2 < 0x3f) && (uVar3 - 0x800 < 0xfffff7dc)) {
      FUN_14009d014((longlong)local_4b28);
      uVar4 = FUN_14009d13c((longlong)local_4b28,uVar3,param_7);
      if ((int)uVar4 != 0) {
        FUN_14009d7f8((longlong *)local_4b28,(uint)bVar1);
        FUN_14009e3b8(local_4b50);
        local_4b30 = &local_4b88;
        bVar2 = FUN_14009e274((longlong)local_4b50);
        if ((((int)CONCAT71(extraout_var,bVar2) != 0) && (local_4b60 == 0)) && (param_6 != 0)) {
          do {
            uVar3 = FUN_14009e3dc(local_4b28,local_4b50);
            if ((local_4b60 != 0) || ((int)uVar3 < 0)) break;
            *(char *)(param_5 + uVar5) = (char)uVar3;
            uVar5 = uVar5 + 1;
          } while (uVar5 < param_6);
        }
        FUN_14009d114((longlong)local_4b28,(longlong)param_7);
      }
    }
  }
  __security_check_cookie(local_38 ^ (ulonglong)auStack_4ba8);
  return;
}


// ==== FUN_14009bd24 @ 14009bd24  undefined FUN_14009bd24(byte * param_1, uint param_2, ulonglong param_3, undefined8 * param_4, undefined8 param_5, ulonglong param_6, undefined8 * param_7)

void FUN_14009bd24(byte *param_1,uint param_2,ulonglong param_3,undefined8 *param_4,
                  undefined8 param_5,ulonglong param_6,undefined8 *param_7)

{
  ulonglong uVar1;
  bool bVar2;
  int iVar3;
  undefined7 extraout_var;
  undefined1 auStackY_128 [32];
  int local_f8 [2];
  ulonglong local_f0;
  byte *local_e8;
  ulonglong local_e0;
  char local_d8 [16];
  undefined8 local_c8;
  undefined8 local_c0;
  ulonglong local_a8;
  ulonglong local_a0;
  ulonglong local_48;
  
  local_48 = DAT_140103510 ^ (ulonglong)auStackY_128;
  local_c0 = 0;
  local_c8 = 0;
  iVar3 = FUN_1400a0a44((undefined8 *)local_d8,param_1,param_2,param_7);
  if (iVar3 == 0) {
    local_c0 = param_5;
    local_a0 = param_6;
    FUN_1400a047c((longlong)local_d8);
    while( true ) {
      local_e8 = (byte *)0x0;
      local_f0 = 0x40000;
      if (param_3 < 0x40000) {
        local_f0 = param_3;
      }
      iVar3 = (*(code *)*param_4)(param_4,&local_e8,&local_f0);
      uVar1 = local_a8;
      if (iVar3 != 0) break;
      local_e0 = local_f0;
      bVar2 = FUN_1400a04ec(local_d8,param_6,local_e8,&local_e0,1,local_f8);
      param_3 = param_3 - local_e0;
      local_f0 = local_f0 - local_e0;
      if (((((int)CONCAT71(extraout_var,bVar2) != 0) || (local_a8 == local_a0)) ||
          ((local_e0 == 0 && (uVar1 == local_a8)))) ||
         (iVar3 = (*(code *)param_4[1])(param_4), iVar3 != 0)) break;
    }
    FUN_1400a08d0((longlong)local_d8,(longlong)param_7);
  }
  __security_check_cookie(local_48 ^ (ulonglong)auStackY_128);
  return;
}


// ==== FUN_14009bea8 @ 14009bea8  undefined FUN_14009bea8(undefined1 * param_1, undefined8 param_2, ulonglong param_3, undefined8 * param_4, undefined8 param_5, longlong param_6, undefined8 * param_7)

void FUN_14009bea8(undefined1 *param_1,undefined8 param_2,ulonglong param_3,undefined8 *param_4,
                  undefined8 param_5,longlong param_6,undefined8 *param_7)

{
  longlong lVar1;
  int iVar2;
  undefined8 uVar3;
  undefined1 auStackY_138 [32];
  ulonglong local_108;
  int local_100 [2];
  byte *local_f8;
  ulonglong local_f0;
  uint local_e8 [4];
  undefined8 local_d8;
  undefined8 local_d0;
  longlong local_b8;
  longlong local_b0;
  ulonglong local_38;
  
  local_38 = DAT_140103510 ^ (ulonglong)auStackY_138;
  local_d0 = 0;
  local_d8 = 0;
  if (((int)param_2 == 1) &&
     (iVar2 = FUN_1400a0ce4((undefined8 *)local_e8,
                            (uint)CONCAT71((int7)((ulonglong)param_2 >> 8),*param_1),param_7),
     iVar2 == 0)) {
    local_d0 = param_5;
    local_b0 = param_6;
    FUN_1400a0df4((longlong)local_e8);
    while( true ) {
      local_f8 = (byte *)0x0;
      local_108 = 0x40000;
      if (param_3 < 0x40000) {
        local_108 = param_3;
      }
      iVar2 = (*(code *)*param_4)(param_4,&local_f8,&local_108);
      lVar1 = local_b8;
      if (iVar2 != 0) break;
      local_f0 = local_108;
      uVar3 = FUN_1400a0fb4(local_e8,param_6,local_f8,(longlong *)&local_f0,1,local_100);
      local_108 = local_108 - local_f0;
      param_3 = param_3 - local_f0;
      if (((((int)uVar3 != 0) || (local_b8 == local_b0)) || ((local_f0 == 0 && (lVar1 == local_b8)))
          ) || (iVar2 = (*(code *)param_4[1])(param_4), iVar2 != 0)) break;
    }
    FUN_1400a08d0((longlong)local_e8,(longlong)param_7);
  }
  __security_check_cookie(local_38 ^ (ulonglong)auStackY_138);
  return;
}


// ==== FUN_14009c038 @ 14009c038  undefined8 FUN_14009c038(ulonglong param_1, undefined8 * param_2, void * param_3)

undefined8 FUN_14009c038(ulonglong param_1,undefined8 *param_2,void *param_3)

{
  undefined8 uVar1;
  size_t local_res8;
  void *local_res20;
  
  if (param_1 != 0) {
    do {
      local_res8 = 0x40000;
      if (param_1 < 0x40000) {
        local_res8 = param_1;
      }
      uVar1 = (*(code *)*param_2)(param_2,&local_res20,&local_res8);
      if ((int)uVar1 != 0) {
        return uVar1;
      }
      if (local_res8 == 0) {
        return 6;
      }
      memcpy(param_3,local_res20,local_res8);
      param_3 = (void *)((longlong)param_3 + local_res8);
      param_1 = param_1 - local_res8;
      uVar1 = (*(code *)param_2[1])(param_2);
      if ((int)uVar1 != 0) {
        return uVar1;
      }
    } while (param_1 != 0);
  }
  return 0;
}


// ==== FUN_14009c29c @ 14009c29c  undefined FUN_14009c29c(uint * param_1, longlong param_2, ulonglong * param_3, longlong param_4, undefined8 * param_5, longlong param_6, void * param_7, ulonglong param_8, undefined8 * param_9, longlong * param_10)

void FUN_14009c29c(uint *param_1,longlong param_2,ulonglong *param_3,longlong param_4,
                  undefined8 *param_5,longlong param_6,void *param_7,ulonglong param_8,
                  undefined8 *param_9,longlong *param_10)

{
  uint uVar1;
  longlong lVar2;
  undefined8 *puVar3;
  int iVar4;
  longlong lVar5;
  undefined8 uVar6;
  void *pvVar7;
  void **ppvVar8;
  uint uVar9;
  ulonglong uVar10;
  ulonglong uVar11;
  uint *puVar12;
  uint uVar13;
  uint *puVar14;
  bool bVar15;
  undefined1 auStackY_4a8 [32];
  longlong *local_440;
  ulonglong *local_438;
  uint local_428 [2];
  undefined8 *local_420;
  longlong local_418;
  ulonglong *local_410;
  void *local_408;
  ulonglong local_400;
  uint local_3f8 [4];
  ulonglong local_3e8;
  ulonglong local_3e0 [3];
  void *local_3c8;
  longlong local_3c0;
  longlong local_3b8;
  longlong local_3b0;
  void *local_3a8;
  longlong local_3a0;
  longlong local_398;
  longlong local_390;
  void *local_388;
  void *local_380;
  int local_378;
  int local_368;
  undefined1 local_158 [256];
  ulonglong local_58;
  
  local_58 = DAT_140103510 ^ (ulonglong)auStackY_4a8;
  uVar13 = 0;
  uVar9 = *param_1;
  local_420 = param_5;
  local_3e8 = 0;
  local_3e0[0] = 0;
  local_400 = 0;
  local_408 = (void *)0x0;
  local_418 = param_4;
  local_410 = param_3;
  if ((((uVar9 == 0) || (4 < uVar9)) || ((char)param_1[0x11] != '\x01')) ||
     (((uVar1 = param_1[0x10], uVar1 != 0 && (uVar1 != 0x21)) &&
      ((uVar1 != 0x30101 && (uVar1 != 0x30401)))))) goto LAB_14009c398;
  if (uVar9 == 1) {
    if (((param_1[2] != 1) || (param_1[4] != 0)) || (param_1[1] != 0)) goto LAB_14009c398;
  }
  else {
    if (uVar9 == 2) {
      if (((((char)param_1[0x15] != '\x01') || (param_1[2] != 1)) || (param_1[4] != 0)) ||
         (((param_1[1] != 1 || (param_1[8] != 1)) || (param_1[9] != 0)))) goto LAB_14009c398;
      uVar1 = param_1[0x14];
      if (((uVar1 == 3) || (uVar1 == 0x3030103)) ||
         ((uVar1 == 0x3030205 ||
          (((uVar1 == 0x3030401 || (uVar1 == 0x3030501)) || (uVar1 == 0x3030701))))))
      goto LAB_14009c509;
      bVar15 = uVar1 == 0x3030805;
    }
    else {
      if ((((uVar9 != 4) || ((char)param_1[0x15] != '\x01')) ||
          (((uVar1 = param_1[0x14], uVar1 != 0 &&
            (((uVar1 != 0x21 && (uVar1 != 0x30101)) && (uVar1 != 0x30401)))) ||
           ((char)param_1[0x19] != '\x01')))) ||
         (((((uVar1 = param_1[0x18], uVar1 != 0 && (uVar1 != 0x21)) &&
            ((uVar1 != 0x30101 && (uVar1 != 0x30401)))) ||
           ((param_1[0x1c] != 0x303011b || ((char)param_1[0x1d] != '\x04')))) ||
          ((param_1[2] != 4 ||
           (((((((param_1[4] != 2 || (param_1[5] != 6)) || (param_1[6] != 1)) ||
               ((param_1[7] != 0 || (param_1[1] != 3)))) ||
              ((param_1[8] != 5 || ((param_1[9] != 0 || (param_1[10] != 4)))))) ||
             (param_1[0xb] != 1)) || (param_1[0xc] != 3)))))))) goto LAB_14009c398;
      bVar15 = param_1[0xd] == 2;
    }
    if (!bVar15) goto LAB_14009c398;
  }
LAB_14009c509:
  if (uVar9 != 0) {
    local_438 = local_3e0;
    puVar14 = local_3f8;
    puVar12 = param_1 + 0x10;
    local_440 = param_10 + 1;
    do {
      uVar11 = 0;
      if (((*puVar12 == 0) || (*puVar12 == 0x21)) ||
         ((*puVar12 == 0x30101 || (*puVar12 == 0x30401)))) {
        uVar10 = param_8;
        pvVar7 = param_7;
        if (uVar9 == 4) {
          local_3f8[2] = 0;
          uVar10 = *local_410;
          local_3f8[0] = 3;
          local_3f8[1] = 2;
          uVar11 = (ulonglong)*puVar14;
          if (uVar13 < 2) {
            pvVar7 = (void *)(*(code *)*param_9)(param_9,uVar10);
            if ((pvVar7 == (void *)0x0) && (uVar10 != 0)) break;
            *local_440 = (longlong)pvVar7;
            *local_438 = uVar10;
          }
          else {
            if ((uVar13 != 2) || (param_8 < uVar10)) break;
            pvVar7 = (void *)((param_8 - uVar10) + (longlong)param_7);
            local_408 = pvVar7;
            local_400 = uVar10;
          }
        }
        puVar3 = local_420;
        lVar2 = *(longlong *)(local_418 + uVar11 * 8);
        uVar11 = *(longlong *)(local_418 + (ulonglong)((int)uVar11 + 1) * 8) - lVar2;
        iVar4 = FUN_14009b7fc((longlong)local_420,lVar2 + param_6);
        if (iVar4 != 0) break;
        if (*puVar12 == 0) {
          if (uVar11 != uVar10) break;
          uVar6 = FUN_14009c038(uVar11,puVar3,pvVar7);
          iVar4 = (int)uVar6;
        }
        else if (*puVar12 == 0x30101) {
          iVar4 = FUN_14009bd24((byte *)(param_2 + *(longlong *)(puVar12 + -2)),
                                (uint)*(byte *)((longlong)puVar12 + 5),uVar11,puVar3,pvVar7,uVar10,
                                param_9);
        }
        else if (*puVar12 == 0x21) {
          iVar4 = FUN_14009bea8((undefined1 *)(param_2 + *(longlong *)(puVar12 + -2)),
                                (ulonglong)*(byte *)((longlong)puVar12 + 5),uVar11,puVar3,pvVar7,
                                uVar10,param_9);
        }
        else {
          if (*puVar12 != 0x30401) break;
          iVar4 = FUN_14009bb6c((byte *)(param_2 + *(longlong *)(puVar12 + -2)),
                                (uint)*(byte *)((longlong)puVar12 + 5),uVar11,puVar3,
                                (longlong)pvVar7,uVar10,param_9);
        }
joined_r0x00014009c9ec:
        if (iVar4 != 0) break;
      }
      else {
        if (*puVar12 == 0x303011b) {
          lVar2 = *(longlong *)(local_418 + 8);
          uVar11 = *(longlong *)(local_418 + 0x10) - lVar2;
          if (uVar13 == 3) {
            lVar5 = (*(code *)*param_9)(param_9,uVar11);
            puVar3 = local_420;
            param_10[2] = lVar5;
            if (((((lVar5 != 0) || (uVar11 == 0)) &&
                 (iVar4 = FUN_14009b7fc((longlong)local_420,lVar2 + param_6), iVar4 == 0)) &&
                ((uVar6 = FUN_14009c038(uVar11,puVar3,(void *)param_10[2]), (int)uVar6 == 0 &&
                 ((local_3e8 & 3) == 0)))) &&
               (((local_3e0[0] & 3) == 0 && (local_400 + local_3e0[0] + local_3e8 == param_8)))) {
              local_3c8 = local_408;
              local_3a8 = (void *)((longlong)local_408 + local_400);
              local_3c0 = *param_10;
              local_3a0 = local_3c0 + local_3e8;
              local_3b8 = param_10[1];
              local_398 = local_3b8 + local_3e0[0];
              local_3b0 = param_10[2];
              local_390 = local_3b0 + uVar11;
              local_380 = (void *)(param_8 + (longlong)param_7);
              local_388 = param_7;
              FUN_1400a1e74((longlong)&local_3c8);
              uVar6 = FUN_1400a1ea8((longlong *)&local_3c8);
              uVar9 = 0;
              if ((int)uVar6 == 0) {
                ppvVar8 = &local_3c8;
                do {
                  if (*ppvVar8 != ppvVar8[4]) goto LAB_14009c398;
                  uVar9 = uVar9 + 1;
                  ppvVar8 = ppvVar8 + 1;
                } while (uVar9 < 4);
                if ((local_368 == 0) && (local_388 == local_380)) {
                  local_368 = 0;
                  iVar4 = local_378;
                  goto joined_r0x00014009c9ec;
                }
              }
            }
          }
          break;
        }
        if (uVar13 != 1) break;
        if (*puVar12 == 3) {
          if (*(char *)((longlong)puVar12 + 5) != '\x01') break;
          FUN_1400a1c7c(local_158);
          FUN_1400a1d90(local_158,*(byte *)(*(longlong *)(puVar12 + -2) + param_2) + 1,
                        (longlong)param_7,param_8);
        }
        else {
          if (*(char *)((longlong)puVar12 + 5) != '\0') break;
          if (*puVar12 == 0x3030103) {
            local_428[0] = 0;
            FUN_1400a1654((longlong)param_7,param_8,0,local_428,0);
          }
          else if (*puVar12 == 0x3030205) {
            FUN_1400a1930((longlong)param_7,param_8,0,0);
          }
          else if (*puVar12 == 0x3030401) {
            FUN_1400a1afc((longlong)param_7,param_8,0,0);
          }
          else if (*puVar12 == 0x3030501) {
            FUN_1400a17cc((longlong)param_7,param_8,0,0);
          }
          else if (*puVar12 == 0x3030701) {
            FUN_1400a1860((longlong)param_7,param_8,0,0);
          }
          else {
            if (*puVar12 != 0x3030805) break;
            FUN_1400a19fc((longlong)param_7,param_8,0,0);
          }
        }
      }
      uVar9 = *param_1;
      local_440 = local_440 + -1;
      local_438 = local_438 + -1;
      local_410 = local_410 + 1;
      uVar13 = uVar13 + 1;
      puVar12 = puVar12 + 4;
      puVar14 = puVar14 + 1;
    } while (uVar13 < uVar9);
  }
LAB_14009c398:
  __security_check_cookie(local_58 ^ (ulonglong)auStackY_4a8);
  return;
}


// ==== FUN_14009ca6c @ 14009ca6c  ulonglong FUN_14009ca6c(longlong param_1, uint param_2, undefined8 * param_3, longlong param_4, void * param_5, ulonglong param_6, undefined8 * param_7)

ulonglong FUN_14009ca6c(longlong param_1,uint param_2,undefined8 *param_3,longlong param_4,
                       void *param_5,ulonglong param_6,undefined8 *param_7)

{
  longlong lVar1;
  uint uVar2;
  ulonglong uVar3;
  longlong *plVar4;
  longlong lVar5;
  longlong lVar6;
  ulonglong uVar7;
  longlong local_e8;
  longlong local_e0;
  longlong local_d8 [4];
  longlong local_b8;
  uint local_a8 [3];
  uint local_9c;
  ulonglong local_30 [5];
  
  lVar6 = *(longlong *)(param_1 + 0x20);
  uVar7 = (ulonglong)param_2;
  lVar5 = *(longlong *)(param_1 + 0x38) + *(longlong *)(lVar6 + uVar7 * 8);
  lVar1 = *(longlong *)(param_1 + 0x28);
  local_e0 = *(longlong *)(lVar6 + (ulonglong)(param_2 + 1) * 8) - *(longlong *)(lVar6 + uVar7 * 8);
  local_d8[3] = *(longlong *)(param_1 + 0x40) + *(longlong *)(lVar1 + uVar7 * 8);
  local_b8 = *(longlong *)(lVar1 + (ulonglong)(param_2 + 1) * 8) - *(longlong *)(lVar1 + uVar7 * 8);
  local_e8 = lVar5;
  uVar3 = FUN_140099090(local_a8,&local_e8,local_d8 + 3);
  if ((int)uVar3 == 0) {
    if ((local_e0 == 0) && (param_6 == local_30[local_9c])) {
      local_d8[0] = 0;
      local_d8[1] = 0;
      local_d8[2] = 0;
      uVar2 = FUN_14009c29c(local_a8,lVar5,local_30,
                            *(longlong *)(param_1 + 8) +
                            (ulonglong)*(uint *)(*(longlong *)(param_1 + 0x30) + uVar7 * 4) * 8,
                            param_3,param_4,param_5,param_6,param_7,local_d8);
      plVar4 = local_d8;
      uVar3 = (ulonglong)uVar2;
      lVar6 = 3;
      do {
        (*(code *)param_7[1])(param_7,*plVar4);
        plVar4 = plVar4 + 1;
        lVar6 = lVar6 + -1;
      } while (lVar6 != 0);
    }
    else {
      uVar3 = 0xb;
    }
  }
  return uVar3;
}


// ==== FUN_14009cbd0 @ 14009cbd0  undefined FUN_14009cbd0(undefined8 * param_1)

void FUN_14009cbd0(undefined8 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  return;
}


// ==== FUN_14009cbdc @ 14009cbdc  undefined8 FUN_14009cbdc(longlong * param_1, longlong param_2, undefined8 * param_3)

undefined8 FUN_14009cbdc(longlong *param_1,longlong param_2,undefined8 *param_3)

{
  longlong lVar1;
  
  param_1[1] = 0;
  if (param_2 == 0) {
    *param_1 = 0;
  }
  else {
    lVar1 = (*(code *)*param_3)(param_3);
    *param_1 = lVar1;
    if (lVar1 == 0) {
      return 0;
    }
    param_1[1] = param_2;
  }
  return 1;
}


// ==== FUN_14009cc24 @ 14009cc24  undefined FUN_14009cc24(undefined8 * param_1, longlong param_2)

void FUN_14009cc24(undefined8 *param_1,longlong param_2)

{
  (**(code **)(param_2 + 8))(param_2,*param_1);
  *param_1 = 0;
  param_1[1] = 0;
  return;
}


// ==== FUN_14009cc48 @ 14009cc48  undefined FUN_14009cc48(int param_1, undefined4 * param_2, undefined4 * param_3, undefined4 * param_4, undefined4 * param_5)

void FUN_14009cc48(int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
                  undefined4 *param_5)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (param_1 == 0) {
    puVar1 = (undefined4 *)cpuid_basic_info(0);
  }
  else if (param_1 == 1) {
    puVar1 = (undefined4 *)cpuid_Version_info(1);
  }
  else if (param_1 == 2) {
    puVar1 = (undefined4 *)cpuid_cache_tlb_info(2);
  }
  else if (param_1 == 3) {
    puVar1 = (undefined4 *)cpuid_serial_info(3);
  }
  else if (param_1 == 4) {
    puVar1 = (undefined4 *)cpuid_Deterministic_Cache_Parameters_info(4);
  }
  else if (param_1 == 5) {
    puVar1 = (undefined4 *)cpuid_MONITOR_MWAIT_Features_info(5);
  }
  else if (param_1 == 6) {
    puVar1 = (undefined4 *)cpuid_Thermal_Power_Management_info(6);
  }
  else if (param_1 == 7) {
    puVar1 = (undefined4 *)cpuid_Extended_Feature_Enumeration_info(7);
  }
  else if (param_1 == 9) {
    puVar1 = (undefined4 *)cpuid_Direct_Cache_Access_info(9);
  }
  else if (param_1 == 10) {
    puVar1 = (undefined4 *)cpuid_Architectural_Performance_Monitoring_info(10);
  }
  else if (param_1 == 0xb) {
    puVar1 = (undefined4 *)cpuid_Extended_Topology_info(0xb);
  }
  else if (param_1 == 0xd) {
    puVar1 = (undefined4 *)cpuid_Processor_Extended_States_info(0xd);
  }
  else if (param_1 == 0xf) {
    puVar1 = (undefined4 *)cpuid_Quality_of_Service_info(0xf);
  }
  else if (param_1 == -0x7ffffffe) {
    puVar1 = (undefined4 *)cpuid_brand_part1_info(0x80000002);
  }
  else if (param_1 == -0x7ffffffd) {
    puVar1 = (undefined4 *)cpuid_brand_part2_info(0x80000003);
  }
  else if (param_1 == -0x7ffffffc) {
    puVar1 = (undefined4 *)cpuid_brand_part3_info(0x80000004);
  }
  else {
    puVar1 = (undefined4 *)cpuid(param_1);
  }
  uVar2 = puVar1[1];
  uVar3 = puVar1[2];
  uVar4 = puVar1[3];
  *param_2 = *puVar1;
  *param_3 = uVar2;
  *param_4 = uVar4;
  *param_5 = uVar3;
  return;
}


// ==== FUN_14009cc6c @ 14009cc6c  undefined8 FUN_14009cc6c(undefined4 * param_1)

/* WARNING: Removing unreachable block (ram,0x00014009cc94) */
/* WARNING: Removing unreachable block (ram,0x00014009cc78) */

undefined8 FUN_14009cc6c(undefined4 *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  puVar1 = (undefined4 *)cpuid_basic_info(0);
  uVar2 = puVar1[1];
  uVar3 = puVar1[2];
  uVar4 = puVar1[3];
  *param_1 = *puVar1;
  param_1[3] = uVar4;
  param_1[1] = uVar2;
  param_1[2] = uVar3;
  puVar1 = (undefined4 *)cpuid_Version_info(1);
  uVar2 = puVar1[1];
  uVar3 = puVar1[2];
  uVar4 = puVar1[3];
  param_1[4] = *puVar1;
  param_1[5] = uVar2;
  param_1[6] = uVar4;
  param_1[7] = uVar3;
  return 1;
}


// ==== FUN_14009ccb0 @ 14009ccb0  uint FUN_14009ccb0(longlong param_1)

uint FUN_14009ccb0(longlong param_1)

{
  uint uVar1;
  int *piVar2;
  
  uVar1 = 0;
  piVar2 = (int *)0x1400d2408;
  do {
    if (piVar2[-2] == *(int *)(param_1 + 4)) {
      if (piVar2[-1] == *(int *)(param_1 + 8)) {
        if (*piVar2 == *(int *)(param_1 + 0xc)) {
          return uVar1;
        }
      }
    }
    uVar1 = uVar1 + 1;
    piVar2 = piVar2 + 3;
  } while (uVar1 < 3);
  return 0xffffffff;
}


// ==== FUN_14009cce8 @ 14009cce8  undefined8 FUN_14009cce8(void)

/* WARNING: Removing unreachable block (ram,0x00014009cd11) */
/* WARNING: Removing unreachable block (ram,0x00014009ccfb) */

undefined8 FUN_14009cce8(void)

{
  undefined4 *puVar1;
  uint *puVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  
  puVar1 = (undefined4 *)cpuid_basic_info(0);
  local_28 = *puVar1;
  local_24 = puVar1[1];
  local_20 = puVar1[2];
  local_1c = puVar1[3];
  puVar2 = (uint *)cpuid_Version_info(1);
  local_18 = *puVar2;
  local_14 = puVar2[1];
  local_c = puVar2[2];
  local_10 = puVar2[3];
  uVar4 = (local_18 >> 8 & 0xf00 | local_18 & 0xf0) >> 4;
  uVar5 = (local_18 & 0xf00 | local_18 >> 8 & 0xff000) >> 8;
  uVar3 = FUN_14009ccb0((longlong)&local_28);
  if (uVar3 == 0) {
    if (uVar5 < 6) {
      return 1;
    }
    if (uVar5 != 6) {
      return 0;
    }
    if (uVar4 == 0x1c) {
      return 1;
    }
    if (uVar4 == 0x26) {
      return 1;
    }
    if (uVar4 == 0x27) {
      return 1;
    }
    if (uVar4 == 0x35) {
      return 1;
    }
    bVar6 = uVar4 == 0x36;
  }
  else {
    if (uVar3 != 1) {
      if (uVar3 != 2) {
        return 1;
      }
      if (uVar5 < 6) {
        return 1;
      }
      if (uVar5 != 6) {
        return 0;
      }
      if (uVar4 < 0xf) {
        return 1;
      }
      return 0;
    }
    if (uVar5 < 5) {
      return 1;
    }
    if (uVar5 != 5) {
      return 0;
    }
    if (uVar4 < 6) {
      return 1;
    }
    bVar6 = uVar4 == 10;
  }
  if (bVar6) {
    return 1;
  }
  return 0;
}


// ==== FUN_14009cdc0 @ 14009cdc0  uint FUN_14009cdc0(void)

/* WARNING: Removing unreachable block (ram,0x00014009cde2) */
/* WARNING: Removing unreachable block (ram,0x00014009cdca) */

uint FUN_14009cdc0(void)

{
  longlong lVar1;
  
  cpuid_basic_info(0);
  lVar1 = cpuid_Version_info(1);
  return *(uint *)(lVar1 + 0xc) >> 0x19 & 1;
}


// ==== FUN_14009ce00 @ 14009ce00  ulonglong FUN_14009ce00(uint param_1, uint * param_2, ulonglong param_3, longlong param_4)

ulonglong FUN_14009ce00(uint param_1,uint *param_2,ulonglong param_3,longlong param_4)

{
  ulonglong uVar1;
  uint uVar2;
  
  if (param_3 != 0) {
    do {
      if (((ulonglong)param_2 & 3) == 0) break;
      uVar2 = *param_2;
      param_2 = (uint *)((longlong)param_2 + 1);
      param_1 = *(uint *)(param_4 + (((ulonglong)(byte)uVar2 ^ (ulonglong)param_1) & 0xff) * 4) ^
                param_1 >> 8;
      param_3 = param_3 - 1;
    } while (param_3 != 0);
  }
  if (3 < param_3) {
    uVar1 = param_3 >> 2;
    param_3 = param_3 + uVar1 * -4;
    do {
      uVar2 = param_1 ^ *param_2;
      param_2 = param_2 + 1;
      param_1 = *(uint *)(param_4 + (ulonglong)((uVar2 >> 8 & 0xff) + 0x200) * 4) ^
                *(uint *)(param_4 + (ulonglong)((uVar2 >> 0x10 & 0xff) + 0x100) * 4) ^
                *(uint *)(param_4 + (ulonglong)((uVar2 & 0xff) + 0x300) * 4) ^
                *(uint *)(param_4 + (ulonglong)(uVar2 >> 0x18) * 4);
      uVar1 = uVar1 - 1;
    } while (uVar1 != 0);
  }
  for (; param_3 != 0; param_3 = param_3 - 1) {
    uVar2 = *param_2;
    param_2 = (uint *)((longlong)param_2 + 1);
    param_1 = *(uint *)(param_4 + (((ulonglong)(byte)uVar2 ^ (ulonglong)param_1) & 0xff) * 4) ^
              param_1 >> 8;
  }
  return (ulonglong)param_1;
}


// ==== FUN_14009cee0 @ 14009cee0  ulonglong FUN_14009cee0(uint param_1, uint * param_2, ulonglong param_3, longlong param_4)

ulonglong FUN_14009cee0(uint param_1,uint *param_2,ulonglong param_3,longlong param_4)

{
  uint uVar1;
  ulonglong uVar2;
  uint uVar3;
  
  if (param_3 != 0) {
    do {
      if (((ulonglong)param_2 & 7) == 0) break;
      uVar1 = *param_2;
      param_2 = (uint *)((longlong)param_2 + 1);
      param_1 = *(uint *)(param_4 + (((ulonglong)(byte)uVar1 ^ (ulonglong)param_1) & 0xff) * 4) ^
                param_1 >> 8;
      param_3 = param_3 - 1;
    } while (param_3 != 0);
  }
  if (7 < param_3) {
    uVar2 = param_3 >> 3;
    param_3 = param_3 + uVar2 * -8;
    do {
      uVar3 = param_1 ^ *param_2;
      uVar1 = param_2[1];
      param_2 = param_2 + 2;
      param_1 = *(uint *)(param_4 + (ulonglong)((uVar3 >> 8 & 0xff) + 0x600) * 4) ^
                *(uint *)(param_4 + (ulonglong)((uVar3 >> 0x10 & 0xff) + 0x500) * 4) ^
                *(uint *)(param_4 + (ulonglong)((uVar1 >> 8 & 0xff) + 0x200) * 4) ^
                *(uint *)(param_4 + (ulonglong)((uVar1 >> 0x10 & 0xff) + 0x100) * 4) ^
                *(uint *)(param_4 + (ulonglong)((uVar3 & 0xff) + 0x700) * 4) ^
                *(uint *)(param_4 + (ulonglong)((uVar1 & 0xff) + 0x300) * 4) ^
                *(uint *)(param_4 + (ulonglong)((uVar3 >> 0x18) + 0x400) * 4) ^
                *(uint *)(param_4 + (ulonglong)(uVar1 >> 0x18) * 4);
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  for (; param_3 != 0; param_3 = param_3 - 1) {
    uVar1 = *param_2;
    param_2 = (uint *)((longlong)param_2 + 1);
    param_1 = *(uint *)(param_4 + (((ulonglong)(byte)uVar1 ^ (ulonglong)param_1) & 0xff) * 4) ^
              param_1 >> 8;
  }
  return (ulonglong)param_1;
}


// ==== FUN_14009d014 @ 14009d014  undefined FUN_14009d014(longlong param_1)

void FUN_14009d014(longlong param_1)

{
  ulonglong uVar1;
  uint uVar2;
  uint uVar3;
  ulonglong uVar4;
  ulonglong uVar6;
  undefined1 *puVar7;
  int iVar8;
  int iVar9;
  ulonglong uVar5;
  
  uVar6 = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  puVar7 = (undefined1 *)(param_1 + 0x6c);
  uVar1 = uVar6;
  uVar5 = uVar6;
  do {
    uVar4 = uVar5;
    iVar9 = (int)(uVar1 >> 2) + 1;
    if (0xb < (uint)uVar1) {
      iVar9 = 4;
    }
    do {
      iVar8 = iVar9;
      uVar3 = (int)uVar4 + 1;
      uVar5 = (ulonglong)uVar3;
      iVar9 = iVar8 + -1;
      *(char *)(uVar4 + 0x92 + param_1) = (char)uVar1;
      uVar4 = uVar5;
    } while (iVar9 != 0);
    uVar2 = (uint)uVar1 + 1;
    uVar1 = (ulonglong)uVar2;
    *puVar7 = (char)uVar3;
    puVar7 = puVar7 + 1;
  } while (uVar2 < 0x26);
  *(undefined1 *)(param_1 + 0x2ac) = 0;
  *(undefined1 *)(param_1 + 0x2ad) = 2;
  *(undefined8 *)(param_1 + 0x2ae) = 0x404040404040404;
  *(undefined1 *)(param_1 + 0x2b6) = 4;
  memset((void *)(param_1 + 0x2b7),iVar8 + 5,0xf5);
  puVar7 = (undefined1 *)(param_1 + 0x1ac);
  do {
    *puVar7 = (char)uVar6;
    uVar3 = (int)uVar6 + 1;
    uVar6 = (ulonglong)uVar3;
    puVar7 = puVar7 + 1;
  } while (uVar3 < 3);
  iVar9 = 1;
  if (uVar3 < 0x100) {
    puVar7 = (undefined1 *)(uVar6 + 0x1ac + param_1);
    uVar1 = (ulonglong)(0x100 - uVar3);
    do {
      iVar9 = iVar9 + -1;
      *puVar7 = (char)uVar6;
      if (iVar9 == 0) {
        iVar9 = (int)uVar6;
        uVar6 = (ulonglong)(iVar9 + 1);
        iVar9 = iVar9 + -1;
      }
      puVar7 = puVar7 + 1;
      uVar1 = uVar1 - 1;
    } while (uVar1 != 0);
  }
  memset((void *)(param_1 + 0x3ac),0,0x40);
  memset((void *)(param_1 + 0x3ec),8,0xc0);
  return;
}


// ==== FUN_14009d114 @ 14009d114  undefined FUN_14009d114(longlong param_1, longlong param_2)

void FUN_14009d114(longlong param_1,longlong param_2)

{
  (**(code **)(param_2 + 8))(param_2,*(undefined8 *)(param_1 + 0x40));
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined8 *)(param_1 + 0x40) = 0;
  return;
}


// ==== FUN_14009d13c @ 14009d13c  undefined8 FUN_14009d13c(longlong param_1, uint param_2, undefined8 * param_3)

undefined8 FUN_14009d13c(longlong param_1,uint param_2,undefined8 *param_3)

{
  longlong lVar1;
  
  if ((*(longlong *)(param_1 + 0x40) == 0) || (*(uint *)(param_1 + 0x34) != param_2)) {
    (*(code *)param_3[1])(param_3);
    *(undefined4 *)(param_1 + 0x34) = 0;
    *(undefined8 *)(param_1 + 0x40) = 0;
    *(uint *)(param_1 + 0x68) = -(param_2 & 3) + 4;
    lVar1 = (*(code *)*param_3)(param_3,-(param_2 & 3) + 0x10 + param_2);
    *(longlong *)(param_1 + 0x40) = lVar1;
    if (lVar1 == 0) {
      return 0;
    }
    *(uint *)(param_1 + 0x34) = param_2;
  }
  return 1;
}


// ==== FUN_14009d1e4 @ 14009d1e4  undefined FUN_14009d1e4(longlong param_1, longlong param_2, ulonglong param_3, ulonglong param_4)

void FUN_14009d1e4(longlong param_1,longlong param_2,ulonglong param_3,ulonglong param_4)

{
  byte bVar1;
  uint uVar2;
  ulonglong uVar3;
  uint uVar4;
  ulonglong uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  bVar1 = *(byte *)((param_4 & 0xffffffff) + 0x6c + param_1);
  uVar2 = (uint)*(byte *)((param_3 & 0xffffffff) + 0x6c + param_1) - (uint)bVar1;
  puVar7 = (undefined4 *)((ulonglong)(((uint)bVar1 + (uint)bVar1 * 2) * 4) + param_2);
  bVar1 = *(byte *)((ulonglong)(uVar2 - 1) + 0x92 + param_1);
  uVar5 = (ulonglong)bVar1;
  if (*(byte *)(uVar5 + 0x6c + param_1) != uVar2) {
    uVar4 = bVar1 - 1;
    uVar5 = (ulonglong)uVar4;
    bVar1 = *(byte *)((ulonglong)uVar4 + 0x6c + param_1);
    uVar3 = (ulonglong)((uVar2 - bVar1) - 1);
    puVar6 = (undefined4 *)((ulonglong)(((uint)bVar1 + (uint)bVar1 * 2) * 4) + (longlong)puVar7);
    *puVar6 = *(undefined4 *)(param_1 + 0x114 + uVar3 * 4);
    *(int *)(param_1 + 0x114 + uVar3 * 4) = (int)puVar6 - *(int *)(param_1 + 0x40);
  }
  *puVar7 = *(undefined4 *)(param_1 + 0x114 + uVar5 * 4);
  *(int *)(param_1 + 0x114 + uVar5 * 4) = (int)puVar7 - *(int *)(param_1 + 0x40);
  return;
}


// ==== FUN_14009d268 @ 14009d268  undefined FUN_14009d268(longlong param_1)

void FUN_14009d268(longlong param_1)

{
  byte bVar1;
  ushort uVar2;
  ulonglong uVar3;
  uint uVar4;
  uint *puVar5;
  longlong lVar6;
  byte *pbVar7;
  uint uVar8;
  ulonglong uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  uint uVar12;
  uint *puVar13;
  short *psVar14;
  ulonglong uVar15;
  uint uVar16;
  
  lVar6 = 0x26;
  uVar16 = *(int *)(param_1 + 0x68) + *(int *)(param_1 + 0x34);
  uVar15 = (ulonglong)uVar16;
  *(undefined4 *)(param_1 + 0x38) = 0xff;
  pbVar7 = (byte *)(param_1 + 0x6c);
  puVar13 = (uint *)(param_1 + 0x114);
  uVar3 = uVar15;
  do {
    bVar1 = *pbVar7;
    uVar8 = *puVar13;
    *puVar13 = 0;
    while (uVar8 != 0) {
      puVar5 = (uint *)((ulonglong)uVar8 + *(longlong *)(param_1 + 0x40));
      puVar5[1] = (uint)uVar3;
      uVar9 = (ulonglong)uVar8;
      *(uint *)(uVar3 + 8 + *(longlong *)(param_1 + 0x40)) = uVar8;
      uVar8 = *puVar5;
      *(undefined2 *)puVar5 = 0;
      *(ushort *)((longlong)puVar5 + 2) = (ushort)bVar1;
      uVar3 = uVar9;
    }
    puVar13 = puVar13 + 1;
    pbVar7 = pbVar7 + 1;
    lVar6 = lVar6 + -1;
  } while (lVar6 != 0);
  *(undefined2 *)(uVar15 + *(longlong *)(param_1 + 0x40)) = 1;
  *(uint *)(*(longlong *)(param_1 + 0x40) + 4 + uVar15) = (uint)uVar3;
  *(uint *)(uVar3 + 8 + *(longlong *)(param_1 + 0x40)) = uVar16;
  if (*(undefined2 **)(param_1 + 0x48) != *(undefined2 **)(param_1 + 0x50)) {
    **(undefined2 **)(param_1 + 0x48) = 1;
  }
  for (; (uint)uVar3 != uVar16; uVar3 = (ulonglong)*(uint *)(uVar3 + 4 + lVar6)) {
    lVar6 = *(longlong *)(param_1 + 0x40);
    uVar9 = (ulonglong)*(ushort *)(uVar3 + 2 + lVar6);
    psVar14 = (short *)(uVar3 + uVar9 * 0xc + lVar6);
    while( true ) {
      uVar8 = (int)uVar9 + (uint)(ushort)psVar14[1];
      uVar9 = (ulonglong)uVar8;
      if ((*psVar14 != 0) || (0xffff < uVar8)) break;
      *(undefined4 *)((ulonglong)*(uint *)(psVar14 + 4) + 4 + *(longlong *)(param_1 + 0x40)) =
           *(undefined4 *)(psVar14 + 2);
      *(undefined4 *)((ulonglong)*(uint *)(psVar14 + 2) + 8 + *(longlong *)(param_1 + 0x40)) =
           *(undefined4 *)(psVar14 + 4);
      *(short *)(uVar3 + 2 + lVar6) = (short)uVar8;
      psVar14 = (short *)(*(longlong *)(param_1 + 0x40) + uVar9 * 0xc + uVar3);
    }
  }
  uVar8 = *(uint *)(*(longlong *)(param_1 + 0x40) + 4 + uVar15);
  while (uVar8 != uVar16) {
    puVar10 = (undefined4 *)((ulonglong)uVar8 + *(longlong *)(param_1 + 0x40));
    uVar2 = *(ushort *)((longlong)puVar10 + 2);
    uVar12 = (uint)uVar2;
    uVar8 = puVar10[1];
    if (0x80 < uVar2) {
      uVar3 = (ulonglong)((uVar2 - 0x81 >> 7) + 1);
      puVar11 = puVar10;
      do {
        uVar12 = uVar12 - 0x80;
        *puVar11 = *(undefined4 *)(param_1 + 0x1a8);
        puVar10 = puVar11 + 0x180;
        uVar3 = uVar3 - 1;
        *(int *)(param_1 + 0x1a8) = (int)puVar11 - *(int *)(param_1 + 0x40);
        puVar11 = puVar10;
      } while (uVar3 != 0);
    }
    bVar1 = *(byte *)((ulonglong)(uVar12 - 1) + 0x92 + param_1);
    uVar3 = (ulonglong)bVar1;
    if (*(byte *)(uVar3 + 0x6c + param_1) != uVar12) {
      uVar4 = bVar1 - 1;
      uVar3 = (ulonglong)uVar4;
      bVar1 = *(byte *)((ulonglong)uVar4 + 0x6c + param_1);
      uVar15 = (ulonglong)((uVar12 - bVar1) - 1);
      puVar10[(ulonglong)bVar1 * 3] = *(undefined4 *)(param_1 + 0x114 + uVar15 * 4);
      *(int *)(param_1 + 0x114 + uVar15 * 4) =
           (int)(puVar10 + (ulonglong)bVar1 * 3) - *(int *)(param_1 + 0x40);
    }
    *puVar10 = *(undefined4 *)(param_1 + 0x114 + uVar3 * 4);
    *(int *)(param_1 + 0x114 + uVar3 * 4) = (int)puVar10 - *(int *)(param_1 + 0x40);
  }
  return;
}


// ==== FUN_14009d468 @ 14009d468  undefined4 * FUN_14009d468(longlong param_1, uint param_2)

undefined4 * FUN_14009d468(longlong param_1,uint param_2)

{
  byte bVar1;
  undefined4 *puVar2;
  int *piVar3;
  ulonglong uVar4;
  uint uVar5;
  ulonglong uVar6;
  
  uVar4 = (ulonglong)param_2;
  if (*(int *)(param_1 + 0x38) == 0) {
    FUN_14009d268(param_1);
    uVar5 = *(uint *)(param_1 + 0x114 + uVar4 * 4);
    if (uVar5 != 0) {
      puVar2 = (undefined4 *)((ulonglong)uVar5 + *(longlong *)(param_1 + 0x40));
      *(undefined4 *)(param_1 + 0x114 + uVar4 * 4) = *puVar2;
      return puVar2;
    }
  }
  uVar6 = (ulonglong)param_2;
  piVar3 = (int *)(param_1 + 0x114 + (longlong)(int)param_2 * 4);
  do {
    uVar5 = (int)uVar6 + 1;
    uVar6 = (ulonglong)uVar5;
    piVar3 = piVar3 + 1;
    if (uVar5 == 0x26) {
      bVar1 = *(byte *)(uVar4 + 0x6c + param_1);
      *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + -1;
      uVar5 = ((uint)bVar1 + (uint)bVar1 * 2) * 4;
      if ((uint)(*(int *)(param_1 + 0x60) - *(int *)(param_1 + 0x58)) <= uVar5) {
        return (undefined4 *)0x0;
      }
      *(longlong *)(param_1 + 0x60) = *(longlong *)(param_1 + 0x60) - (ulonglong)uVar5;
      return *(undefined4 **)(param_1 + 0x60);
    }
  } while (*piVar3 == 0);
  puVar2 = (undefined4 *)
           ((ulonglong)*(uint *)(param_1 + 0x114 + uVar6 * 4) + *(longlong *)(param_1 + 0x40));
  *(undefined4 *)(param_1 + 0x114 + uVar6 * 4) = *puVar2;
  FUN_14009d1e4(param_1,(longlong)puVar2,uVar6,(ulonglong)param_2);
  return puVar2;
}


// ==== FUN_14009d51c @ 14009d51c  undefined FUN_14009d51c(longlong param_1, uint param_2)

void FUN_14009d51c(longlong param_1,uint param_2)

{
  byte bVar1;
  ulonglong uVar2;
  uint uVar3;
  
  uVar2 = (ulonglong)param_2;
  uVar3 = *(uint *)(param_1 + 0x114 + uVar2 * 4);
  if (uVar3 == 0) {
    bVar1 = *(byte *)(uVar2 + 0x6c + param_1);
    uVar3 = ((uint)bVar1 + (uint)bVar1 * 2) * 4;
    if ((uint)(*(int *)(param_1 + 0x50) - *(int *)(param_1 + 0x48)) < uVar3) {
      FUN_14009d468(param_1,param_2);
    }
    else {
      *(ulonglong *)(param_1 + 0x48) = (ulonglong)uVar3 + *(longlong *)(param_1 + 0x48);
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x114 + uVar2 * 4) =
         *(undefined4 *)((ulonglong)uVar3 + *(longlong *)(param_1 + 0x40));
  }
  return;
}


// ==== FUN_14009d574 @ 14009d574  undefined4 * FUN_14009d574(longlong param_1, undefined4 * param_2, int param_3, int param_4)

undefined4 * FUN_14009d574(longlong param_1,undefined4 *param_2,int param_3,int param_4)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  ulonglong uVar6;
  undefined4 *puVar7;
  
  bVar1 = *(byte *)((ulonglong)(param_3 - 1) + 0x92 + param_1);
  bVar2 = *(byte *)((ulonglong)(param_4 - 1) + 0x92 + param_1);
  uVar6 = (ulonglong)bVar2;
  if ((uint)bVar1 != (uint)bVar2) {
    uVar3 = *(uint *)(param_1 + 0x114 + uVar6 * 4);
    if (uVar3 == 0) {
      FUN_14009d1e4(param_1,(longlong)param_2,(ulonglong)(uint)bVar1,uVar6);
    }
    else {
      puVar4 = param_2 + 2;
      puVar7 = (undefined4 *)((ulonglong)uVar3 + *(longlong *)(param_1 + 0x40));
      *(undefined4 *)(param_1 + 0x114 + uVar6 * 4) = *puVar7;
      puVar5 = puVar7;
      do {
        *puVar5 = puVar4[-2];
        puVar5[1] = puVar4[-1];
        *(undefined4 *)(((longlong)puVar7 - (longlong)param_2) + (longlong)puVar4) = *puVar4;
        puVar4 = puVar4 + 3;
        param_4 = param_4 + -1;
        puVar5 = puVar5 + 3;
      } while (param_4 != 0);
      *param_2 = *(undefined4 *)(param_1 + 0x114 + (ulonglong)bVar1 * 4);
      *(int *)(param_1 + 0x114 + (ulonglong)bVar1 * 4) = (int)param_2 - *(int *)(param_1 + 0x40);
      param_2 = puVar7;
    }
  }
  return param_2;
}


// ==== FUN_14009d644 @ 14009d644  undefined FUN_14009d644(longlong * param_1)

void FUN_14009d644(longlong *param_1)

{
  ushort uVar1;
  uint uVar2;
  longlong *plVar3;
  longlong lVar4;
  ulonglong uVar5;
  uint uVar6;
  undefined1 *puVar8;
  longlong lVar9;
  ulonglong uVar10;
  longlong *plVar11;
  ushort *puVar12;
  longlong *plVar13;
  ulonglong uVar7;
  
  memset((void *)((longlong)param_1 + 0x114),0,0x98);
  lVar9 = (ulonglong)*(uint *)((longlong)param_1 + 0x34) +
          (ulonglong)*(uint *)(param_1 + 0xd) + param_1[8];
  param_1[0xb] = (ulonglong)*(uint *)(param_1 + 0xd) + param_1[8];
  uVar10 = 0;
  *(undefined4 *)(param_1 + 7) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  lVar4 = lVar9 - (ulonglong)((*(uint *)((longlong)param_1 + 0x34) / 0x60) * 0x54);
  uVar6 = *(uint *)((longlong)param_1 + 0x24);
  param_1[9] = lVar4;
  *(uint *)(param_1 + 3) = uVar6;
  param_1[0xc] = lVar4;
  uVar2 = 0xc;
  if (uVar6 < 0xc) {
    uVar2 = uVar6;
  }
  *(uint *)(param_1 + 6) = -1 - uVar2;
  *(uint *)((longlong)param_1 + 0x2c) = -1 - uVar2;
  lVar4 = lVar9 + -0xc;
  param_1[10] = lVar4;
  param_1[1] = lVar4;
  *param_1 = lVar4;
  *(undefined4 *)(lVar9 + -4) = 0;
  *(undefined2 *)*param_1 = 0x100;
  *(undefined2 *)(*param_1 + 2) = 0x101;
  param_1[2] = param_1[9];
  param_1[9] = param_1[9] + 0x600;
  *(int *)(*param_1 + 4) = (int)param_1[2] - (int)param_1[8];
  uVar5 = uVar10;
  uVar7 = uVar10;
  do {
    lVar9 = param_1[2];
    *(char *)(uVar5 + lVar9) = (char)uVar7;
    uVar6 = (int)uVar7 + 1;
    uVar7 = (ulonglong)uVar6;
    *(undefined1 *)(uVar5 + 1 + lVar9) = 1;
    *(undefined2 *)(uVar5 + 2 + lVar9) = 0;
    *(undefined2 *)(uVar5 + 4 + lVar9) = 0;
    uVar5 = uVar5 + 6;
  } while (uVar6 < 0x100);
  plVar11 = param_1 + 0x15e;
  uVar5 = uVar10;
  do {
    puVar12 = &DAT_1400d2438;
    lVar9 = 8;
    plVar13 = plVar11;
    do {
      uVar1 = *puVar12;
      lVar4 = 8;
      plVar3 = plVar13;
      do {
        *(short *)plVar3 = 0x4000 - (short)((uint)uVar1 / ((int)uVar5 + 2U));
        plVar3 = plVar3 + 2;
        lVar4 = lVar4 + -1;
      } while (lVar4 != 0);
      plVar13 = (longlong *)((longlong)plVar13 + 2);
      puVar12 = puVar12 + 1;
      lVar9 = lVar9 + -1;
    } while (lVar9 != 0);
    uVar6 = (int)uVar5 + 1;
    uVar5 = (ulonglong)uVar6;
    plVar11 = plVar11 + 0x10;
  } while (uVar6 < 0x80);
  puVar8 = (undefined1 *)((longlong)param_1 + 0x4b3);
  do {
    lVar9 = 0x10;
    do {
      puVar8[-1] = 3;
      *(short *)(puVar8 + -3) = ((short)uVar10 + 2) * 0x28;
      *puVar8 = 4;
      puVar8 = puVar8 + 4;
      lVar9 = lVar9 + -1;
    } while (lVar9 != 0);
    uVar6 = (int)uVar10 + 1;
    uVar10 = (ulonglong)uVar6;
  } while (uVar6 < 0x19);
  return;
}


// ==== FUN_14009d7f8 @ 14009d7f8  undefined FUN_14009d7f8(longlong * param_1, undefined4 param_2)

void FUN_14009d7f8(longlong *param_1,undefined4 param_2)

{
  *(undefined4 *)((longlong)param_1 + 0x24) = param_2;
  FUN_14009d644(param_1);
  *(undefined1 *)((longlong)param_1 + 0x4ae) = 7;
  *(undefined1 *)((longlong)param_1 + 0x4af) = 0x40;
  *(undefined2 *)((longlong)param_1 + 0x4ac) = 0;
  return;
}


// ==== FUN_14009d828 @ 14009d828  ushort * FUN_14009d828(undefined8 * param_1, int param_2)

ushort * FUN_14009d828(undefined8 *param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  uint uVar4;
  ushort *puVar5;
  int iVar6;
  ushort *puVar7;
  char **ppcVar8;
  uint uVar9;
  char cStackX_9;
  undefined2 uStackX_a;
  ushort local_resc;
  char *local_218 [64];
  
  pcVar3 = (char *)param_1[2];
  puVar7 = (ushort *)*param_1;
  uVar2 = *(uint *)(pcVar3 + 2);
  if (param_2 == 0) {
    local_218[0] = pcVar3;
  }
  uVar9 = (uint)(param_2 == 0);
  uVar4 = *(uint *)(puVar7 + 4);
  if (uVar4 != 0) {
    ppcVar8 = local_218 + (int)uVar9;
    do {
      puVar7 = (ushort *)((ulonglong)uVar4 + param_1[8]);
      if (*puVar7 == 1) {
        puVar5 = puVar7 + 1;
      }
      else {
        puVar5 = (ushort *)((ulonglong)*(uint *)(puVar7 + 2) + param_1[8]);
        cVar1 = (char)*puVar5;
        while (cVar1 != *pcVar3) {
          puVar5 = puVar5 + 3;
          cVar1 = (char)*puVar5;
        }
      }
      if (*(uint *)(puVar5 + 1) != uVar2) {
        puVar7 = (ushort *)((ulonglong)*(uint *)(puVar5 + 1) + param_1[8]);
        if (uVar9 == 0) {
          return puVar7;
        }
        break;
      }
      uVar4 = *(uint *)(puVar7 + 4);
      *ppcVar8 = (char *)puVar5;
      uVar9 = uVar9 + 1;
      ppcVar8 = ppcVar8 + 1;
    } while (uVar4 != 0);
  }
  cVar1 = *(char *)((ulonglong)uVar2 + param_1[8]);
  if (*puVar7 == 1) {
    cStackX_9 = *(char *)((longlong)puVar7 + 3);
  }
  else {
    for (pcVar3 = (char *)((ulonglong)*(uint *)(puVar7 + 2) + param_1[8]); *pcVar3 != cVar1;
        pcVar3 = pcVar3 + 6) {
    }
    iVar6 = (byte)pcVar3[1] - 1;
    uVar4 = ((uint)puVar7[1] - (uint)*puVar7) - iVar6;
    if (uVar4 < (uint)(iVar6 * 2)) {
      cStackX_9 = (char)((uVar4 * 3 + -1 + iVar6 * 2) / (uVar4 * 2));
    }
    else {
      cStackX_9 = uVar4 < (uint)(iVar6 * 5);
    }
    cStackX_9 = cStackX_9 + '\x01';
  }
  ppcVar8 = local_218 + (int)uVar9;
  do {
    local_resc = (ushort)(uVar2 + 1 >> 0x10);
    uStackX_a = (undefined2)(uVar2 + 1);
    if (param_1[10] == param_1[9]) {
      if (*(int *)((longlong)param_1 + 0x114) == 0) {
        puVar5 = (ushort *)FUN_14009d468((longlong)param_1,0);
        if (puVar5 == (ushort *)0x0) {
          return (ushort *)0x0;
        }
      }
      else {
        puVar5 = (ushort *)((ulonglong)*(uint *)((longlong)param_1 + 0x114) + param_1[8]);
        *(undefined4 *)((longlong)param_1 + 0x114) = *(undefined4 *)puVar5;
      }
    }
    else {
      puVar5 = (ushort *)(param_1[10] + -0xc);
      param_1[10] = puVar5;
    }
    *puVar5 = 1;
    ppcVar8 = ppcVar8 + -1;
    *(uint *)(puVar5 + 1) = CONCAT22(uStackX_a,CONCAT11(cStackX_9,cVar1));
    pcVar3 = *ppcVar8;
    puVar5[3] = local_resc;
    *(int *)(puVar5 + 4) = (int)puVar7 - *(int *)(param_1 + 8);
    uVar9 = uVar9 - 1;
    *(int *)(pcVar3 + 2) = (int)puVar5 - *(int *)(param_1 + 8);
    puVar7 = puVar5;
  } while (uVar9 != 0);
  return puVar5;
}


// ==== FUN_14009da40 @ 14009da40  undefined FUN_14009da40(longlong * param_1)

void FUN_14009da40(longlong *param_1)

{
  longlong *plVar1;
  byte bVar2;
  byte bVar3;
  undefined1 uVar4;
  undefined2 uVar5;
  ushort uVar6;
  ushort uVar7;
  ushort uVar8;
  undefined4 uVar9;
  char *pcVar10;
  uint uVar11;
  ushort *puVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  char *pcVar15;
  char *pcVar16;
  undefined4 *puVar17;
  undefined1 *puVar18;
  uint uVar19;
  ushort *puVar20;
  uint uVar21;
  short sVar22;
  short *psVar23;
  undefined4 *puVar24;
  ushort uVar25;
  uint uVar26;
  ulonglong uVar27;
  
  pcVar10 = (char *)param_1[2];
  uVar21 = *(uint *)(pcVar10 + 2);
  if (((byte)pcVar10[1] < 0x1f) && (*(int *)(*param_1 + 8) != 0)) {
    psVar23 = (short *)((ulonglong)*(uint *)(*param_1 + 8) + param_1[8]);
    if (*psVar23 == 1) {
      if (*(byte *)((longlong)psVar23 + 3) < 0x20) {
        *(byte *)((longlong)psVar23 + 3) = *(byte *)((longlong)psVar23 + 3) + 1;
      }
    }
    else {
      pcVar15 = (char *)((ulonglong)*(uint *)(psVar23 + 2) + param_1[8]);
      if (*pcVar15 != *pcVar10) {
        do {
          pcVar16 = pcVar15;
          pcVar15 = pcVar16 + 6;
        } while (*pcVar15 != *pcVar10);
        if ((byte)pcVar16[1] <= (byte)pcVar16[7]) {
          uVar9 = *(undefined4 *)pcVar15;
          uVar5 = *(undefined2 *)(pcVar16 + 10);
          *(undefined4 *)pcVar15 = *(undefined4 *)pcVar16;
          *(undefined2 *)(pcVar16 + 10) = *(undefined2 *)(pcVar16 + 4);
          *(undefined4 *)pcVar16 = uVar9;
          *(undefined2 *)(pcVar16 + 4) = uVar5;
          pcVar15 = pcVar16;
        }
      }
      if ((byte)pcVar15[1] < 0x73) {
        pcVar15[1] = pcVar15[1] + 2;
        psVar23[1] = psVar23[1] + 2;
      }
    }
  }
  if ((int)param_1[3] == 0) {
    puVar12 = FUN_14009d828(param_1,1);
    param_1[1] = (longlong)puVar12;
    *param_1 = (longlong)puVar12;
    if (puVar12 != (ushort *)0x0) {
      *(int *)(param_1[2] + 2) = (int)puVar12 - (int)param_1[8];
      return;
    }
  }
  else {
    *(undefined1 *)param_1[0xb] = *(undefined1 *)param_1[2];
    param_1[0xb] = param_1[0xb] + 1;
    uVar19 = (int)param_1[0xb] - (int)param_1[8];
    if ((ulonglong)param_1[0xb] < (ulonglong)param_1[0xc]) {
      if (uVar21 == 0) {
        *(uint *)(param_1[2] + 2) = uVar19;
        uVar21 = (int)*param_1 - (int)param_1[8];
      }
      else {
        if (uVar21 <= uVar19) {
          puVar12 = FUN_14009d828(param_1,0);
          if (puVar12 == (ushort *)0x0) goto LAB_14009db30;
          uVar21 = (int)puVar12 - (int)param_1[8];
        }
        plVar1 = param_1 + 3;
        *(int *)plVar1 = (int)*plVar1 + -1;
        if ((int)*plVar1 == 0) {
          param_1[0xb] = param_1[0xb] - (ulonglong)(param_1[1] != *param_1);
          uVar19 = uVar21;
        }
      }
      puVar12 = (ushort *)*param_1;
      puVar20 = (ushort *)param_1[1];
      uVar6 = *puVar12;
      uVar7 = puVar12[1];
      bVar2 = *(byte *)(param_1[2] + 1);
      if (puVar20 != puVar12) {
        do {
          uVar8 = *puVar20;
          if (uVar8 == 1) {
            puVar13 = (undefined4 *)FUN_14009d51c((longlong)param_1,0);
            if (puVar13 == (undefined4 *)0x0) goto LAB_14009db30;
            *puVar13 = *(undefined4 *)(puVar20 + 1);
            *(ushort *)(puVar13 + 1) = puVar20[3];
            *(int *)(puVar20 + 2) = (int)puVar13 - (int)param_1[8];
            if (*(byte *)((longlong)puVar13 + 1) < 0x1e) {
              *(byte *)((longlong)puVar13 + 1) = *(byte *)((longlong)puVar13 + 1) * '\x02';
            }
            else {
              *(undefined1 *)((longlong)puVar13 + 1) = 0x78;
            }
            puVar20[1] = (ushort)(3 < uVar6) + *(short *)((longlong)param_1 + 0x1c) +
                         (ushort)*(byte *)((longlong)puVar13 + 1);
          }
          else {
            if ((uVar8 & 1) == 0) {
              uVar27 = (ulonglong)(uint)(uVar8 >> 1);
              bVar3 = *(byte *)((ulonglong)((uVar8 >> 1) - 1) + 0x92 + (longlong)param_1);
              if (bVar3 != *(byte *)(uVar27 + 0x92 + (longlong)param_1)) {
                puVar13 = (undefined4 *)FUN_14009d51c((longlong)param_1,bVar3 + 1);
                if (puVar13 == (undefined4 *)0x0) goto LAB_14009db30;
                puVar17 = (undefined4 *)((ulonglong)*(uint *)(puVar20 + 2) + param_1[8]);
                puVar14 = puVar17 + 2;
                puVar24 = puVar13;
                do {
                  *puVar24 = puVar14[-2];
                  puVar24[1] = puVar14[-1];
                  *(undefined4 *)(((longlong)puVar13 - (longlong)puVar17) + (longlong)puVar14) =
                       *puVar14;
                  puVar14 = puVar14 + 3;
                  uVar26 = (int)uVar27 - 1;
                  uVar27 = (ulonglong)uVar26;
                  puVar24 = puVar24 + 3;
                } while (uVar26 != 0);
                *puVar17 = *(undefined4 *)((longlong)param_1 + (ulonglong)bVar3 * 4 + 0x114);
                *(int *)((longlong)param_1 + (ulonglong)bVar3 * 4 + 0x114) =
                     (int)puVar17 - (int)param_1[8];
                *(int *)(puVar20 + 2) = (int)puVar13 - (int)param_1[8];
              }
            }
            puVar20[1] = (ushort)((uint)puVar20[1] <= (uint)uVar8 << 3 &&
                                 (uint)uVar8 << 2 <= (uint)uVar6) * 2 + puVar20[1] +
                         (ushort)((uint)uVar8 + (uint)uVar8 < (uint)uVar6);
          }
          uVar25 = puVar20[1];
          uVar26 = (uint)uVar25 + (((uint)uVar7 - (uint)bVar2) - (uint)uVar6) + 1;
          uVar11 = (uint)*(byte *)(param_1[2] + 1) * (uVar25 + 6) * 2;
          if (uVar11 < uVar26 * 6) {
            uVar25 = uVar25 + 3;
            sVar22 = (uVar26 * 4 <= uVar11) + 1 + (ushort)(uVar26 < uVar11);
          }
          else {
            sVar22 = (ushort)(uVar26 * 0xf <= uVar11) + (ushort)(uVar26 * 0xc <= uVar11) + 4 +
                     (ushort)(uVar26 * 9 <= uVar11);
            uVar25 = uVar25 + sVar22;
          }
          puVar20[1] = uVar25;
          puVar18 = (undefined1 *)
                    ((ulonglong)*(uint *)(puVar20 + 2) + (ulonglong)uVar8 * 6 + param_1[8]);
          *(short *)(puVar18 + 2) = (short)uVar19;
          *(short *)(puVar18 + 4) = (short)(uVar19 >> 0x10);
          uVar4 = *(undefined1 *)param_1[2];
          puVar18[1] = (char)sVar22;
          *puVar18 = uVar4;
          *puVar20 = uVar8 + 1;
          puVar20 = (ushort *)((ulonglong)*(uint *)(puVar20 + 4) + param_1[8]);
        } while (puVar20 != (ushort *)*param_1);
      }
      *param_1 = (ulonglong)uVar21 + param_1[8];
      param_1[1] = (ulonglong)uVar21 + param_1[8];
      return;
    }
  }
LAB_14009db30:
  FUN_14009d644(param_1);
  return;
}


// ==== FUN_14009de28 @ 14009de28  undefined FUN_14009de28(longlong * param_1)

void FUN_14009de28(longlong *param_1)

{
  undefined2 uVar1;
  ushort uVar2;
  undefined4 uVar3;
  ushort *puVar4;
  longlong lVar5;
  uint uVar6;
  byte bVar7;
  uint uVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  ulonglong uVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  char *pcVar14;
  uint uVar15;
  int iVar16;
  uint uVar17;
  undefined4 *puVar18;
  bool bVar19;
  undefined4 local_res8;
  
  puVar12 = (undefined4 *)param_1[2];
  uVar3 = *puVar12;
  puVar18 = (undefined4 *)((ulonglong)*(uint *)(*param_1 + 4) + param_1[8]);
  uVar1 = *(undefined2 *)(puVar12 + 1);
  puVar13 = puVar12;
  for (; puVar12 != puVar18; puVar12 = (undefined4 *)((longlong)puVar12 + -6)) {
    *puVar12 = *(undefined4 *)((longlong)puVar13 + -6);
    *(undefined2 *)(puVar12 + 1) = *(undefined2 *)((longlong)puVar13 + -2);
    puVar13 = (undefined4 *)((longlong)puVar13 + -6);
  }
  *puVar12 = uVar3;
  *(undefined2 *)(puVar12 + 1) = uVar1;
  uVar15 = (uint)*(ushort *)(*param_1 + 2) - (uint)*(byte *)((longlong)puVar12 + 1);
  bVar7 = *(byte *)((longlong)puVar12 + 1) + 4;
  *(byte *)((longlong)puVar12 + 1) = bVar7;
  bVar19 = (int)param_1[3] != 0;
  uVar6 = (uint)bVar7 + (uint)bVar19 >> 1;
  *(char *)((longlong)puVar12 + 1) = (char)uVar6;
  iVar16 = *(ushort *)*param_1 - 1;
  do {
    puVar13 = puVar12;
    puVar12 = (undefined4 *)((longlong)puVar13 + 6);
    uVar15 = uVar15 - *(byte *)((longlong)puVar13 + 7);
    uVar8 = (uint)*(byte *)((longlong)puVar13 + 7) + (uint)bVar19 >> 1;
    bVar7 = (byte)uVar8;
    *(byte *)((longlong)puVar13 + 7) = bVar7;
    uVar6 = uVar6 + uVar8;
    if (*(byte *)((longlong)puVar13 + 1) < bVar7) {
      uVar3 = *puVar12;
      uVar1 = *(undefined2 *)((longlong)puVar13 + 10);
      local_res8._1_1_ = (byte)((uint)uVar3 >> 8);
      puVar10 = puVar12;
      do {
        puVar9 = puVar10;
        *puVar9 = *(undefined4 *)((longlong)puVar9 + -6);
        puVar10 = (undefined4 *)((longlong)puVar9 + -6);
        *(undefined2 *)(puVar9 + 1) = *(undefined2 *)((longlong)puVar9 + -2);
        if (puVar10 == puVar18) break;
      } while (*(byte *)((longlong)puVar9 + -0xb) < local_res8._1_1_);
      *puVar10 = uVar3;
      *(undefined2 *)((longlong)puVar9 + -2) = uVar1;
    }
    iVar16 = iVar16 + -1;
    if (iVar16 == 0) {
      pcVar14 = (char *)((longlong)puVar13 + 7);
      if (*pcVar14 == '\0') {
        puVar4 = (ushort *)*param_1;
        uVar2 = *puVar4;
        iVar16 = 0;
        do {
          pcVar14 = pcVar14 + -6;
          iVar16 = iVar16 + 1;
        } while (*pcVar14 == '\0');
        *puVar4 = *puVar4 - (short)iVar16;
        uVar15 = uVar15 + iVar16;
        if (*(ushort *)*param_1 == 1) {
          uVar3 = *puVar18;
          uVar1 = *(undefined2 *)(puVar18 + 1);
          local_res8._1_1_ = (byte)((uint)uVar3 >> 8);
          do {
            uVar15 = uVar15 >> 1;
            local_res8._1_1_ = local_res8._1_1_ - (local_res8._1_1_ >> 1);
          } while (1 < uVar15);
          local_res8._2_2_ = (undefined2)((uint)uVar3 >> 0x10);
          local_res8._0_1_ = (undefined1)uVar3;
          uVar11 = (ulonglong)
                   *(byte *)((ulonglong)((uVar2 + 1 >> 1) - 1) + 0x92 + (longlong)param_1);
          *puVar18 = *(undefined4 *)((longlong)param_1 + uVar11 * 4 + 0x114);
          *(int *)((longlong)param_1 + uVar11 * 4 + 0x114) = (int)puVar18 - (int)param_1[8];
          lVar5 = *param_1;
          puVar12 = (undefined4 *)(lVar5 + 2);
          param_1[2] = (longlong)puVar12;
          *puVar12 = local_res8;
          *(undefined2 *)(lVar5 + 6) = uVar1;
          return;
        }
        uVar8 = uVar2 + 1 >> 1;
        uVar17 = (int)(*(ushort *)*param_1 + 1) >> 1;
        if (uVar8 != uVar17) {
          puVar12 = FUN_14009d574((longlong)param_1,puVar18,uVar8,uVar17);
          *(int *)(*param_1 + 4) = (int)puVar12 - (int)param_1[8];
        }
      }
      *(short *)(*param_1 + 2) = ((short)uVar15 - (short)(uVar15 >> 1)) + (short)uVar6;
      param_1[2] = (ulonglong)*(uint *)(*param_1 + 4) + param_1[8];
      return;
    }
  } while( true );
}


// ==== FUN_14009e034 @ 14009e034  ushort * FUN_14009e034(undefined8 * param_1, uint param_2, int * param_3)

ushort * FUN_14009e034(undefined8 *param_1,uint param_2,int *param_3)

{
  ushort uVar1;
  uint uVar2;
  ushort *puVar3;
  
  puVar3 = (ushort *)*param_1;
  uVar2 = *puVar3 - param_2;
  if (*puVar3 == 0x100) {
    puVar3 = (ushort *)((longlong)param_1 + 0x4ac);
    *param_3 = 1;
  }
  else {
    puVar3 = (ushort *)
             ((longlong)param_1 +
             ((longlong)(int)((uint)((uint)puVar3[1] < (uint)*puVar3 * 0xb) * 2) +
              (ulonglong)
              (uVar2 < (uint)*(ushort *)((ulonglong)*(uint *)(puVar3 + 4) + param_1[8]) -
                       (uint)*puVar3) +
              (ulonglong)*(byte *)((ulonglong)(uVar2 - 1) + 0x1ac + (longlong)param_1) * 0x10 +
              (longlong)(int)((uint)(uVar2 < param_2) << 2) + (ulonglong)*(uint *)(param_1 + 5)) * 4
             + 0x4b0);
    uVar1 = *puVar3 >> ((byte)puVar3[1] & 0x1f);
    *puVar3 = *puVar3 - uVar1;
    *param_3 = (uint)(uVar1 == 0) + (uint)uVar1;
  }
  return puVar3;
}


// ==== FUN_14009e110 @ 14009e110  undefined FUN_14009e110(ulonglong * param_1)

void FUN_14009e110(ulonglong *param_1)

{
  ulonglong uVar1;
  
  uVar1 = (ulonglong)*(uint *)(param_1[2] + 2) + param_1[8];
  if (((int)param_1[3] == 0) && (param_1[0xb] < uVar1)) {
    param_1[1] = uVar1;
    *param_1 = uVar1;
  }
  else {
    FUN_14009da40((longlong *)param_1);
  }
  return;
}


// ==== FUN_14009e14c @ 14009e14c  undefined FUN_14009e14c(ulonglong * param_1)

void FUN_14009e14c(ulonglong *param_1)

{
  undefined4 *puVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  
  puVar4 = (undefined4 *)param_1[2];
  *(char *)((longlong)puVar4 + 1) = *(char *)((longlong)puVar4 + 1) + '\x04';
  *(short *)(*param_1 + 2) = *(short *)(*param_1 + 2) + 4;
  if (*(byte *)((longlong)puVar4 + -5) < *(byte *)((longlong)puVar4 + 1)) {
    uVar3 = *puVar4;
    puVar1 = (undefined4 *)((longlong)puVar4 + -6);
    uVar2 = *(undefined2 *)(puVar4 + 1);
    *puVar4 = *puVar1;
    *(undefined2 *)(puVar4 + 1) = *(undefined2 *)((longlong)puVar4 + -2);
    *puVar1 = uVar3;
    *(undefined2 *)((longlong)puVar4 + -2) = uVar2;
    param_1[2] = (ulonglong)puVar1;
    if (0x7c < *(byte *)((longlong)puVar4 + -5)) {
      FUN_14009de28((longlong *)param_1);
    }
  }
  FUN_14009e110(param_1);
  return;
}


// ==== FUN_14009e1c0 @ 14009e1c0  undefined FUN_14009e1c0(ulonglong * param_1)

void FUN_14009e1c0(ulonglong *param_1)

{
  short *psVar1;
  uint uVar2;
  
  uVar2 = (uint)(*(ushort *)(*param_1 + 2) < (ushort)((ushort)*(byte *)(param_1[2] + 1) * 2));
  *(int *)((longlong)param_1 + 0x2c) = *(int *)((longlong)param_1 + 0x2c) + uVar2;
  *(uint *)(param_1 + 4) = uVar2;
  psVar1 = (short *)(*param_1 + 2);
  *psVar1 = *psVar1 + 4;
  *(char *)(param_1[2] + 1) = *(char *)(param_1[2] + 1) + '\x04';
  if (0x7c < *(byte *)(param_1[2] + 1)) {
    FUN_14009de28((longlong *)param_1);
  }
  FUN_14009e110(param_1);
  return;
}


// ==== FUN_14009e218 @ 14009e218  undefined FUN_14009e218(ulonglong * param_1)

void FUN_14009e218(ulonglong *param_1)

{
  byte bVar1;
  
  bVar1 = *(byte *)(param_1[2] + 1);
  *(byte *)(param_1[2] + 1) = bVar1 + (bVar1 < 0x80);
  *(int *)((longlong)param_1 + 0x2c) = *(int *)((longlong)param_1 + 0x2c) + 1;
  *(undefined4 *)(param_1 + 4) = 1;
  FUN_14009e110(param_1);
  return;
}


// ==== FUN_14009e238 @ 14009e238  undefined FUN_14009e238(longlong * param_1)

void FUN_14009e238(longlong *param_1)

{
  *(short *)(*param_1 + 2) = *(short *)(*param_1 + 2) + 4;
  *(char *)(param_1[2] + 1) = *(char *)(param_1[2] + 1) + '\x04';
  if (0x7c < *(byte *)(param_1[2] + 1)) {
    FUN_14009de28(param_1);
  }
  *(int *)((longlong)param_1 + 0x2c) = (int)param_1[6];
  FUN_14009da40(param_1);
  return;
}


// ==== FUN_14009e274 @ 14009e274  bool FUN_14009e274(longlong param_1)

bool FUN_14009e274(longlong param_1)

{
  char cVar1;
  byte bVar2;
  longlong lVar3;
  uint uVar4;
  bool bVar5;
  
  *(undefined4 *)(param_1 + 0x18) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  cVar1 = (*(code *)**(undefined8 **)(param_1 + 0x20))(*(undefined8 **)(param_1 + 0x20));
  if (cVar1 == '\0') {
    lVar3 = 4;
    do {
      bVar2 = (*(code *)**(undefined8 **)(param_1 + 0x20))(*(undefined8 **)(param_1 + 0x20));
      uVar4 = (uint)bVar2 | *(int *)(param_1 + 0x1c) << 8;
      lVar3 = lVar3 + -1;
      *(uint *)(param_1 + 0x1c) = uVar4;
    } while (lVar3 != 0);
    bVar5 = uVar4 != 0xffffffff;
  }
  else {
    bVar5 = false;
  }
  return bVar5;
}


// ==== FUN_14009e2fc @ 14009e2fc  undefined FUN_14009e2fc(longlong param_1)

void FUN_14009e2fc(longlong param_1)

{
  byte bVar1;
  
  if (*(uint *)(param_1 + 0x18) < 0x1000000) {
    bVar1 = (*(code *)**(undefined8 **)(param_1 + 0x20))(*(undefined8 **)(param_1 + 0x20));
    *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) << 8;
    *(uint *)(param_1 + 0x1c) = (uint)bVar1 | *(int *)(param_1 + 0x1c) << 8;
    if (*(uint *)(param_1 + 0x18) < 0x1000000) {
      bVar1 = (*(code *)**(undefined8 **)(param_1 + 0x20))(*(undefined8 **)(param_1 + 0x20));
      *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) << 8;
      *(uint *)(param_1 + 0x1c) = (uint)bVar1 | *(int *)(param_1 + 0x1c) << 8;
    }
  }
  return;
}


// ==== FUN_14009e378 @ 14009e378  bool FUN_14009e378(longlong param_1, int param_2)

bool FUN_14009e378(longlong param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = (*(uint *)(param_1 + 0x18) >> 0xe) * param_2;
  uVar1 = *(uint *)(param_1 + 0x1c);
  if (uVar2 <= uVar1) {
    *(uint *)(param_1 + 0x18) = *(uint *)(param_1 + 0x18) - uVar2;
    *(uint *)(param_1 + 0x1c) = uVar1 - uVar2;
  }
  else {
    *(uint *)(param_1 + 0x18) = uVar2;
  }
  FUN_14009e2fc(param_1);
  return uVar2 <= uVar1;
}


// ==== FUN_14009e3b8 @ 14009e3b8  undefined FUN_14009e3b8(undefined8 * param_1)

void FUN_14009e3b8(undefined8 *param_1)

{
  *param_1 = &LAB_14009e2e0;
  param_1[1] = &LAB_14009e35c;
  param_1[2] = FUN_14009e378;
  return;
}


// ==== FUN_14009e3dc @ 14009e3dc  uint FUN_14009e3dc(ulonglong * param_1, undefined8 * param_2)

uint FUN_14009e3dc(ulonglong *param_1,undefined8 *param_2)

{
  char *pcVar1;
  byte bVar2;
  ushort uVar3;
  short *psVar4;
  short sVar5;
  uint uVar6;
  uint uVar7;
  undefined8 *puVar8;
  ushort uVar9;
  int iVar10;
  longlong lVar11;
  uint uVar12;
  ushort *puVar13;
  longlong *plVar14;
  byte *pbVar15;
  byte *pbVar16;
  ulonglong uVar17;
  uint local_res8 [2];
  char local_928 [16];
  undefined8 local_918 [30];
  longlong local_828 [256];
  
  psVar4 = (short *)*param_1;
  if (*psVar4 == 1) {
    uVar17 = *param_1;
    uVar6 = (uint)*(byte *)((ulonglong)*(byte *)param_1[2] + 0x3ac + (longlong)param_1);
    *(uint *)(param_1 + 5) = uVar6;
    lVar11 = (ulonglong)
             ((*(int *)((longlong)param_1 + 0x2c) >> 0x1a & 0x20U) +
              *(byte *)((ulonglong)*(ushort *)((ulonglong)*(uint *)(uVar17 + 8) + param_1[8]) +
                        0x2ab + (longlong)param_1) + uVar6 +
              (uint)*(byte *)((ulonglong)*(byte *)(uVar17 + 2) + 0x3ac + (longlong)param_1) * 2 +
             (int)param_1[4]) + (longlong)(int)(*(byte *)(uVar17 + 3) - 1) * 0x40;
    iVar10 = (*(code *)param_2[2])(param_2,*(undefined2 *)((longlong)param_1 + lVar11 * 2 + 0xaf0));
    uVar9 = *(ushort *)((longlong)param_1 + lVar11 * 2 + 0xaf0);
    sVar5 = (short)((int)(uVar9 + 0x20) >> 7);
    if (iVar10 == 0) {
      *(ushort *)((longlong)param_1 + lVar11 * 2 + 0xaf0) = (uVar9 - sVar5) + 0x80;
      param_1[2] = *param_1 + 2;
      bVar2 = *(byte *)(*param_1 + 2);
      FUN_14009e218(param_1);
      return (uint)bVar2;
    }
    uVar9 = uVar9 - sVar5;
    *(ushort *)((longlong)param_1 + lVar11 * 2 + 0xaf0) = uVar9;
    lVar11 = 4;
    *(uint *)((longlong)param_1 + 0x1c) = (uint)(byte)(&DAT_1400d2428)[uVar9 >> 10];
    puVar8 = local_918;
    do {
      puVar8[-2] = 0xffffffffffffffff;
      puVar8[-1] = 0xffffffffffffffff;
      *puVar8 = 0xffffffffffffffff;
      puVar8[1] = 0xffffffffffffffff;
      puVar8[2] = 0xffffffffffffffff;
      puVar8[3] = 0xffffffffffffffff;
      puVar8[4] = 0xffffffffffffffff;
      puVar8[5] = 0xffffffffffffffff;
      puVar8 = puVar8 + 8;
      lVar11 = lVar11 + -1;
    } while (lVar11 != 0);
    bVar2 = *(byte *)(*param_1 + 2);
    *(undefined4 *)(param_1 + 4) = 0;
    local_928[bVar2] = '\0';
  }
  else {
    pbVar15 = (byte *)((ulonglong)*(uint *)(psVar4 + 2) + param_1[8]);
    uVar6 = (*(code *)*param_2)(param_2,psVar4[1]);
    bVar2 = pbVar15[1];
    uVar12 = (uint)bVar2;
    if (uVar6 < bVar2) {
      (*(code *)param_2[1])(param_2,0,(uint)bVar2);
      param_1[2] = (ulonglong)pbVar15;
      bVar2 = *pbVar15;
      FUN_14009e1c0(param_1);
      return (uint)bVar2;
    }
    *(undefined4 *)(param_1 + 4) = 0;
    puVar13 = (ushort *)*param_1;
    iVar10 = *puVar13 - 1;
    do {
      pbVar16 = pbVar15 + 6;
      uVar12 = uVar12 + pbVar15[7];
      if (uVar6 < uVar12) {
        (*(code *)param_2[1])(param_2,uVar12 - pbVar15[7]);
        param_1[2] = (ulonglong)pbVar16;
        bVar2 = *pbVar16;
        FUN_14009e14c(param_1);
        return (uint)bVar2;
      }
      iVar10 = iVar10 + -1;
      pbVar15 = pbVar16;
    } while (iVar10 != 0);
    if (puVar13[1] <= uVar6) {
      return 0xfffffffe;
    }
    *(uint *)(param_1 + 5) =
         (uint)*(byte *)((ulonglong)*(byte *)param_1[2] + 0x3ac + (longlong)param_1);
    (*(code *)param_2[1])(param_2,uVar12,puVar13[1] - uVar12);
    puVar8 = local_918;
    lVar11 = 4;
    do {
      puVar8[-2] = 0xffffffffffffffff;
      puVar8[-1] = 0xffffffffffffffff;
      *puVar8 = 0xffffffffffffffff;
      puVar8[1] = 0xffffffffffffffff;
      puVar8[2] = 0xffffffffffffffff;
      puVar8[3] = 0xffffffffffffffff;
      puVar8[4] = 0xffffffffffffffff;
      puVar8[5] = 0xffffffffffffffff;
      puVar8 = puVar8 + 8;
      lVar11 = lVar11 + -1;
    } while (lVar11 != 0);
    local_928[*pbVar16] = '\0';
    iVar10 = *(ushort *)*param_1 - 1;
    do {
      pbVar16 = pbVar16 + -6;
      iVar10 = iVar10 + -1;
      local_928[*pbVar16] = '\0';
    } while (iVar10 != 0);
  }
  while( true ) {
    uVar9 = *(ushort *)*param_1;
    do {
      *(int *)(param_1 + 3) = (int)param_1[3] + 1;
      if (*(int *)(*param_1 + 8) == 0) {
        return 0xffffffff;
      }
      puVar13 = (ushort *)((ulonglong)*(uint *)(*param_1 + 8) + param_1[8]);
      *param_1 = (ulonglong)puVar13;
    } while ((uint)*puVar13 == (uint)uVar9);
    uVar3 = *puVar13;
    uVar6 = 0;
    uVar17 = 0;
    pbVar15 = (byte *)((ulonglong)*(uint *)(puVar13 + 2) + param_1[8]);
    do {
      bVar2 = *pbVar15;
      local_828[uVar17] = (longlong)pbVar15;
      uVar12 = (int)uVar17 - (int)local_928[bVar2];
      uVar17 = (ulonglong)uVar12;
      uVar6 = uVar6 + ((uint)pbVar15[1] & (int)local_928[bVar2]);
      pbVar15 = pbVar15 + 6;
    } while (uVar12 != (uint)uVar3 - (uint)uVar9);
    puVar13 = FUN_14009e034(param_1,(uint)uVar9,(int *)local_res8);
    local_res8[0] = local_res8[0] + uVar6;
    uVar7 = (*(code *)*param_2)(param_2);
    if (uVar7 < uVar6) break;
    if (local_res8[0] <= uVar7) {
      return 0xfffffffe;
    }
    (*(code *)param_2[1])(param_2,uVar6,local_res8[0] - uVar6);
    *puVar13 = *puVar13 + (short)local_res8[0];
    plVar14 = local_828 + (int)uVar12;
    do {
      plVar14 = plVar14 + -1;
      uVar6 = (int)uVar17 - 1;
      uVar17 = (ulonglong)uVar6;
      local_928[*(byte *)*plVar14] = '\0';
    } while (uVar6 != 0);
  }
  plVar14 = local_828;
  for (uVar6 = (uint)*(byte *)(local_828[0] + 1); uVar6 <= uVar7;
      uVar6 = uVar6 + *(byte *)(*plVar14 + 1)) {
    plVar14 = plVar14 + 1;
  }
  pbVar15 = (byte *)*plVar14;
  (*(code *)param_2[1])(param_2,uVar6 - pbVar15[1]);
  bVar2 = (byte)puVar13[1];
  if (bVar2 < 7) {
    pcVar1 = (char *)((longlong)puVar13 + 3);
    *pcVar1 = *pcVar1 + -1;
    if (*pcVar1 == '\0') {
      *puVar13 = *puVar13 << 1;
      *(byte *)(puVar13 + 1) = bVar2 + 1;
      *(char *)((longlong)puVar13 + 3) = '\x03' << (bVar2 & 0x1f);
    }
  }
  param_1[2] = (ulonglong)pbVar15;
  bVar2 = *pbVar15;
  FUN_14009e238((longlong *)param_1);
  return (uint)bVar2;
}


// ==== FUN_14009e7ac @ 14009e7ac  undefined8 FUN_14009e7ac(undefined4 * param_1, ulonglong param_2, byte * param_3)

undefined8 FUN_14009e7ac(undefined4 *param_1,ulonglong param_2,byte *param_3)

{
  undefined1 *puVar1;
  byte bVar2;
  ushort uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  uint uVar7;
  longlong lVar8;
  longlong lVar9;
  ulonglong uVar10;
  char cVar11;
  int iVar12;
  uint uVar13;
  ulonglong uVar14;
  ulonglong uVar15;
  uint uVar16;
  ulonglong uVar17;
  undefined1 *puVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  longlong lVar23;
  uint uVar24;
  uint uVar25;
  uint uVar26;
  longlong lVar27;
  ushort *puVar28;
  longlong lVar29;
  byte *pbVar30;
  uint local_res8;
  uint local_res20;
  uint local_88;
  uint local_84;
  ulonglong local_78;
  byte local_60;
  
  local_res20 = param_1[0x14];
  local_res8 = param_1[0x13];
  uVar14 = (ulonglong)local_res8;
  lVar8 = *(longlong *)(param_1 + 4);
  uVar21 = param_1[0x12];
  local_88 = param_1[0x15];
  local_78 = *(ulonglong *)(param_1 + 0xc);
  uVar20 = param_1[0x10];
  pbVar30 = *(byte **)(param_1 + 8);
  uVar25 = param_1[10];
  uVar24 = param_1[0xb];
  local_84 = param_1[0x16];
  uVar4 = param_1[2];
  uVar5 = param_1[1];
  uVar6 = *param_1;
  lVar9 = *(longlong *)(param_1 + 6);
  uVar10 = *(ulonglong *)(param_1 + 0xe);
  uVar7 = param_1[0x11];
  iVar12 = 0;
  do {
    uVar16 = local_84;
    uVar19 = uVar20 & (1 << ((byte)uVar4 & 0x1f)) - 1U;
    lVar29 = (ulonglong)(uVar21 << 4) + (ulonglong)uVar19;
    uVar3 = *(ushort *)(lVar8 + lVar29 * 2);
    if (uVar25 < 0x1000000) {
      uVar25 = uVar25 << 8;
      uVar24 = uVar24 << 8 | (uint)*pbVar30;
      pbVar30 = pbVar30 + 1;
    }
    uVar26 = (uVar25 >> 0xb) * (uint)uVar3;
    if (uVar24 < uVar26) {
      *(ushort *)(lVar8 + lVar29 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
      lVar29 = lVar8 + 0xe6c;
      if ((uVar20 != 0) || (uVar7 != 0)) {
        uVar17 = local_78;
        if (local_78 == 0) {
          uVar17 = uVar10;
        }
        local_60 = (byte)uVar6;
        uVar14 = (ulonglong)local_res8;
        lVar29 = lVar29 + (ulonglong)
                          (((uint)(*(byte *)((uVar17 - 1) + lVar9) >> (8 - local_60 & 0x1f)) +
                           ((uVar20 & (1 << ((byte)uVar5 & 0x1f)) - 1U) << (local_60 & 0x1f))) *
                          0x300) * 2;
      }
      uVar20 = uVar20 + 1;
      if (uVar21 < 7) {
        uVar3 = *(ushort *)(lVar29 + 2);
        uVar25 = 3;
        if (uVar21 < 4) {
          uVar25 = uVar21;
        }
        uVar21 = uVar21 - uVar25;
        if (uVar26 < 0x1000000) {
          uVar26 = uVar26 * 0x100;
          uVar24 = uVar24 << 8 | (uint)*pbVar30;
          pbVar30 = pbVar30 + 1;
        }
        uVar25 = (uVar26 >> 0xb) * (uint)uVar3;
        if (uVar24 < uVar25) {
          uVar16 = 2;
          *(ushort *)(lVar29 + 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
          uVar26 = uVar25;
        }
        else {
          uVar26 = uVar26 - uVar25;
          uVar24 = uVar24 - uVar25;
          uVar16 = 3;
          *(ushort *)(lVar29 + 2) = uVar3 - (uVar3 >> 5);
        }
        uVar14 = (ulonglong)uVar16;
        uVar3 = *(ushort *)(lVar29 + uVar14 * 2);
        if (uVar26 < 0x1000000) {
          uVar26 = uVar26 << 8;
          uVar24 = uVar24 << 8 | (uint)*pbVar30;
          pbVar30 = pbVar30 + 1;
        }
        uVar25 = (uVar26 >> 0xb) * (uint)uVar3;
        if (uVar24 < uVar25) {
          uVar16 = uVar16 * 2;
          *(ushort *)(lVar29 + uVar14 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
          uVar26 = uVar25;
        }
        else {
          uVar26 = uVar26 - uVar25;
          uVar24 = uVar24 - uVar25;
          uVar16 = uVar16 * 2 + 1;
          *(ushort *)(lVar29 + uVar14 * 2) = uVar3 - (uVar3 >> 5);
        }
        uVar14 = (ulonglong)uVar16;
        uVar3 = *(ushort *)(lVar29 + uVar14 * 2);
        if (uVar26 < 0x1000000) {
          uVar26 = uVar26 << 8;
          uVar24 = uVar24 << 8 | (uint)*pbVar30;
          pbVar30 = pbVar30 + 1;
        }
        uVar25 = (uVar26 >> 0xb) * (uint)uVar3;
        if (uVar24 < uVar25) {
          *(ushort *)(lVar29 + uVar14 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
          uVar16 = uVar16 * 2;
          uVar26 = uVar25;
        }
        else {
          uVar26 = uVar26 - uVar25;
          uVar24 = uVar24 - uVar25;
          *(ushort *)(lVar29 + uVar14 * 2) = uVar3 - (uVar3 >> 5);
          uVar16 = uVar16 * 2 + 1;
        }
        uVar14 = (ulonglong)uVar16;
        uVar3 = *(ushort *)(lVar29 + uVar14 * 2);
        if (uVar26 < 0x1000000) {
          uVar26 = uVar26 << 8;
          uVar24 = uVar24 << 8 | (uint)*pbVar30;
          pbVar30 = pbVar30 + 1;
        }
        uVar25 = (uVar26 >> 0xb) * (uint)uVar3;
        if (uVar24 < uVar25) {
          *(ushort *)(lVar29 + uVar14 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
          uVar16 = uVar16 * 2;
          uVar26 = uVar25;
        }
        else {
          uVar26 = uVar26 - uVar25;
          uVar24 = uVar24 - uVar25;
          *(ushort *)(lVar29 + uVar14 * 2) = uVar3 - (uVar3 >> 5);
          uVar16 = uVar16 * 2 + 1;
        }
        uVar14 = (ulonglong)uVar16;
        uVar3 = *(ushort *)(lVar29 + uVar14 * 2);
        if (uVar26 < 0x1000000) {
          uVar26 = uVar26 << 8;
          uVar24 = uVar24 << 8 | (uint)*pbVar30;
          pbVar30 = pbVar30 + 1;
        }
        uVar25 = (uVar26 >> 0xb) * (uint)uVar3;
        if (uVar24 < uVar25) {
          *(ushort *)(lVar29 + uVar14 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
          uVar16 = uVar16 * 2;
          uVar26 = uVar25;
        }
        else {
          uVar26 = uVar26 - uVar25;
          uVar24 = uVar24 - uVar25;
          *(ushort *)(lVar29 + uVar14 * 2) = uVar3 - (uVar3 >> 5);
          uVar16 = uVar16 * 2 + 1;
        }
        uVar14 = (ulonglong)uVar16;
        uVar3 = *(ushort *)(lVar29 + uVar14 * 2);
        if (uVar26 < 0x1000000) {
          uVar26 = uVar26 << 8;
          uVar24 = uVar24 << 8 | (uint)*pbVar30;
          pbVar30 = pbVar30 + 1;
        }
        uVar25 = (uVar26 >> 0xb) * (uint)uVar3;
        if (uVar24 < uVar25) {
          *(ushort *)(lVar29 + uVar14 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
          uVar16 = uVar16 * 2;
          uVar26 = uVar25;
        }
        else {
          uVar26 = uVar26 - uVar25;
          uVar24 = uVar24 - uVar25;
          *(ushort *)(lVar29 + uVar14 * 2) = uVar3 - (uVar3 >> 5);
          uVar16 = uVar16 * 2 + 1;
        }
        uVar14 = (ulonglong)uVar16;
        uVar3 = *(ushort *)(lVar29 + uVar14 * 2);
        if (uVar26 < 0x1000000) {
          uVar26 = uVar26 << 8;
          uVar24 = uVar24 << 8 | (uint)*pbVar30;
          pbVar30 = pbVar30 + 1;
        }
        uVar25 = (uVar26 >> 0xb) * (uint)uVar3;
        if (uVar24 < uVar25) {
          *(ushort *)(lVar29 + uVar14 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
          uVar16 = uVar16 * 2;
          uVar26 = uVar25;
        }
        else {
          uVar26 = uVar26 - uVar25;
          uVar24 = uVar24 - uVar25;
          *(ushort *)(lVar29 + uVar14 * 2) = uVar3 - (uVar3 >> 5);
          uVar16 = uVar16 * 2 + 1;
        }
        uVar14 = (ulonglong)uVar16;
        uVar3 = *(ushort *)(lVar29 + uVar14 * 2);
        if (uVar26 < 0x1000000) {
          uVar26 = uVar26 << 8;
          uVar24 = uVar24 << 8 | (uint)*pbVar30;
          pbVar30 = pbVar30 + 1;
        }
        uVar25 = (uVar26 >> 0xb) * (uint)uVar3;
        if (uVar24 < uVar25) {
          *(ushort *)(lVar29 + uVar14 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
          cVar11 = (char)uVar16 * '\x02';
        }
        else {
          uVar24 = uVar24 - uVar25;
          cVar11 = (char)uVar16 * '\x02' + '\x01';
          *(ushort *)(lVar29 + uVar14 * 2) = uVar3 - (uVar3 >> 5);
          uVar25 = uVar26 - uVar25;
        }
      }
      else {
        uVar21 = uVar21 - ((-(uint)(uVar21 < 10) & 0xfffffffd) + 6);
        bVar2 = *(byte *)(((-(ulonglong)(local_78 < uVar14) & uVar10) - uVar14) + local_78 + lVar9);
        uVar19 = (uint)bVar2 + (uint)bVar2;
        uVar16 = uVar19 & 0x100;
        uVar14 = (ulonglong)uVar16;
        uVar3 = *(ushort *)(lVar29 + 0x202 + uVar14 * 2);
        if (uVar26 < 0x1000000) {
          uVar26 = uVar26 * 0x100;
          uVar24 = uVar24 << 8 | (uint)*pbVar30;
          pbVar30 = pbVar30 + 1;
        }
        uVar13 = (uVar26 >> 0xb) * (uint)uVar3;
        if (uVar24 < uVar13) {
          lVar23 = 2;
          *(ushort *)(lVar29 + 0x202 + uVar14 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
          uVar16 = ~uVar16;
          uVar25 = uVar13;
        }
        else {
          uVar25 = uVar26 - uVar13;
          uVar24 = uVar24 - uVar13;
          lVar23 = 3;
          *(ushort *)(lVar29 + 0x202 + uVar14 * 2) = uVar3 - (uVar3 >> 5);
        }
        uVar16 = uVar16 & 0x100;
        uVar26 = uVar16 & uVar19 * 2;
        lVar27 = (ulonglong)uVar26 + (ulonglong)uVar16 + lVar23;
        uVar3 = *(ushort *)(lVar29 + lVar27 * 2);
        if (uVar25 < 0x1000000) {
          uVar25 = uVar25 << 8;
          uVar24 = uVar24 << 8 | (uint)*pbVar30;
          pbVar30 = pbVar30 + 1;
        }
        uVar13 = (uVar25 >> 0xb) * (uint)uVar3;
        if (uVar24 < uVar13) {
          uVar26 = ~uVar26;
          uVar22 = (int)lVar23 * 2;
          *(ushort *)(lVar29 + lVar27 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
          uVar25 = uVar13;
        }
        else {
          uVar25 = uVar25 - uVar13;
          uVar24 = uVar24 - uVar13;
          uVar22 = (int)lVar23 * 2 + 1;
          *(ushort *)(lVar29 + lVar27 * 2) = uVar3 - (uVar3 >> 5);
        }
        uVar16 = uVar16 & uVar26;
        uVar26 = uVar16 & uVar19 * 4;
        lVar23 = (ulonglong)uVar26 + (ulonglong)uVar16 + (ulonglong)uVar22;
        uVar3 = *(ushort *)(lVar29 + lVar23 * 2);
        if (uVar25 < 0x1000000) {
          uVar25 = uVar25 << 8;
          uVar24 = uVar24 << 8 | (uint)*pbVar30;
          pbVar30 = pbVar30 + 1;
        }
        uVar13 = (uVar25 >> 0xb) * (uint)uVar3;
        if (uVar24 < uVar13) {
          uVar26 = ~uVar26;
          uVar22 = uVar22 * 2;
          *(ushort *)(lVar29 + lVar23 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
          uVar25 = uVar13;
        }
        else {
          uVar25 = uVar25 - uVar13;
          uVar24 = uVar24 - uVar13;
          uVar22 = uVar22 * 2 + 1;
          *(ushort *)(lVar29 + lVar23 * 2) = uVar3 - (uVar3 >> 5);
        }
        uVar16 = uVar16 & uVar26;
        uVar26 = uVar16 & uVar19 * 8;
        lVar23 = (ulonglong)uVar26 + (ulonglong)uVar16 + (ulonglong)uVar22;
        uVar3 = *(ushort *)(lVar29 + lVar23 * 2);
        if (uVar25 < 0x1000000) {
          uVar25 = uVar25 << 8;
          uVar24 = uVar24 << 8 | (uint)*pbVar30;
          pbVar30 = pbVar30 + 1;
        }
        uVar13 = (uVar25 >> 0xb) * (uint)uVar3;
        if (uVar24 < uVar13) {
          uVar26 = ~uVar26;
          uVar22 = uVar22 * 2;
          *(ushort *)(lVar29 + lVar23 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
          uVar25 = uVar13;
        }
        else {
          uVar25 = uVar25 - uVar13;
          uVar24 = uVar24 - uVar13;
          uVar22 = uVar22 * 2 + 1;
          *(ushort *)(lVar29 + lVar23 * 2) = uVar3 - (uVar3 >> 5);
        }
        uVar16 = uVar16 & uVar26;
        uVar26 = uVar16 & uVar19 * 0x10;
        lVar23 = (ulonglong)uVar26 + (ulonglong)uVar16 + (ulonglong)uVar22;
        uVar3 = *(ushort *)(lVar29 + lVar23 * 2);
        if (uVar25 < 0x1000000) {
          uVar25 = uVar25 << 8;
          uVar24 = uVar24 << 8 | (uint)*pbVar30;
          pbVar30 = pbVar30 + 1;
        }
        uVar13 = (uVar25 >> 0xb) * (uint)uVar3;
        if (uVar24 < uVar13) {
          uVar26 = ~uVar26;
          uVar22 = uVar22 * 2;
          *(ushort *)(lVar29 + lVar23 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
          uVar25 = uVar13;
        }
        else {
          uVar25 = uVar25 - uVar13;
          uVar24 = uVar24 - uVar13;
          uVar22 = uVar22 * 2 + 1;
          *(ushort *)(lVar29 + lVar23 * 2) = uVar3 - (uVar3 >> 5);
        }
        uVar16 = uVar16 & uVar26;
        uVar26 = uVar16 & uVar19 * 0x20;
        lVar23 = (ulonglong)uVar26 + (ulonglong)uVar16 + (ulonglong)uVar22;
        uVar3 = *(ushort *)(lVar29 + lVar23 * 2);
        if (uVar25 < 0x1000000) {
          uVar25 = uVar25 << 8;
          uVar24 = uVar24 << 8 | (uint)*pbVar30;
          pbVar30 = pbVar30 + 1;
        }
        uVar13 = (uVar25 >> 0xb) * (uint)uVar3;
        if (uVar24 < uVar13) {
          uVar22 = uVar22 * 2;
          uVar26 = ~uVar26;
          *(ushort *)(lVar29 + lVar23 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
          uVar25 = uVar13;
        }
        else {
          uVar25 = uVar25 - uVar13;
          uVar24 = uVar24 - uVar13;
          uVar22 = uVar22 * 2 + 1;
          *(ushort *)(lVar29 + lVar23 * 2) = uVar3 - (uVar3 >> 5);
        }
        uVar16 = uVar16 & uVar26;
        uVar26 = uVar16 & uVar19 * 0x40;
        lVar23 = (ulonglong)uVar26 + (ulonglong)uVar16 + (ulonglong)uVar22;
        uVar3 = *(ushort *)(lVar29 + lVar23 * 2);
        if (uVar25 < 0x1000000) {
          uVar25 = uVar25 << 8;
          uVar24 = uVar24 << 8 | (uint)*pbVar30;
          pbVar30 = pbVar30 + 1;
        }
        uVar13 = (uVar25 >> 0xb) * (uint)uVar3;
        if (uVar24 < uVar13) {
          uVar22 = uVar22 * 2;
          uVar26 = ~uVar26;
          *(ushort *)(lVar29 + lVar23 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
          uVar25 = uVar13;
        }
        else {
          uVar25 = uVar25 - uVar13;
          uVar24 = uVar24 - uVar13;
          uVar22 = uVar22 * 2 + 1;
          *(ushort *)(lVar29 + lVar23 * 2) = uVar3 - (uVar3 >> 5);
        }
        lVar23 = (ulonglong)uVar22 +
                 (ulonglong)(uVar16 & uVar26) + (ulonglong)(uVar19 * 0x80 & uVar16 & uVar26);
        uVar3 = *(ushort *)(lVar29 + lVar23 * 2);
        if (uVar25 < 0x1000000) {
          uVar25 = uVar25 << 8;
          uVar24 = uVar24 << 8 | (uint)*pbVar30;
          pbVar30 = pbVar30 + 1;
        }
        uVar16 = (uVar25 >> 0xb) * (uint)uVar3;
        if (uVar24 < uVar16) {
          *(ushort *)(lVar29 + lVar23 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
          cVar11 = (char)uVar22 * '\x02';
          uVar25 = uVar16;
        }
        else {
          uVar25 = uVar25 - uVar16;
          uVar24 = uVar24 - uVar16;
          cVar11 = (char)uVar22 * '\x02' + '\x01';
          *(ushort *)(lVar29 + lVar23 * 2) = uVar3 - (uVar3 >> 5);
        }
      }
      *(char *)(local_78 + lVar9) = cVar11;
      local_78 = local_78 + 1;
LAB_14009fc6a:
      uVar14 = (ulonglong)local_res8;
    }
    else {
      uVar25 = uVar25 - uVar26;
      uVar24 = uVar24 - uVar26;
      uVar14 = (ulonglong)uVar21;
      *(ushort *)(lVar8 + lVar29 * 2) = uVar3 - (uVar3 >> 5);
      uVar3 = *(ushort *)(lVar8 + 0x180 + uVar14 * 2);
      if (uVar25 < 0x1000000) {
        uVar25 = uVar25 * 0x100;
        uVar24 = uVar24 * 0x100 | (uint)*pbVar30;
        pbVar30 = pbVar30 + 1;
      }
      uVar26 = (uVar25 >> 0xb) * (uint)uVar3;
      if (uVar24 < uVar26) {
        uVar21 = uVar21 + 0xc;
        *(ushort *)(lVar8 + 0x180 + uVar14 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
        puVar28 = (ushort *)(lVar8 + 0x664);
LAB_14009f2c9:
        uVar3 = *puVar28;
        if (uVar26 < 0x1000000) {
          uVar26 = uVar26 << 8;
          uVar24 = uVar24 << 8 | (uint)*pbVar30;
          pbVar30 = pbVar30 + 1;
        }
        uVar25 = (uVar26 >> 0xb) * (uint)uVar3;
        if (uVar24 < uVar25) {
          *puVar28 = (short)(0x800 - uVar3 >> 5) + uVar3;
          uVar14 = (ulonglong)(uVar19 << 3);
          uVar3 = puVar28[uVar14 + 3];
          if (uVar25 < 0x1000000) {
            uVar25 = uVar25 * 0x100;
            uVar24 = uVar24 << 8 | (uint)*pbVar30;
            pbVar30 = pbVar30 + 1;
          }
          uVar16 = (uVar25 >> 0xb) * (uint)uVar3;
          if (uVar24 < uVar16) {
            puVar28[uVar14 + 3] = (short)(0x800 - uVar3 >> 5) + uVar3;
            lVar29 = 2;
            uVar25 = uVar16;
          }
          else {
            uVar25 = uVar25 - uVar16;
            uVar24 = uVar24 - uVar16;
            lVar29 = 3;
            puVar28[uVar14 + 3] = uVar3 - (uVar3 >> 5);
          }
          lVar23 = lVar29 * 2;
          uVar3 = puVar28[uVar14 + lVar29 + 2];
          if (uVar25 < 0x1000000) {
            uVar25 = uVar25 << 8;
            uVar24 = uVar24 << 8 | (uint)*pbVar30;
            pbVar30 = pbVar30 + 1;
          }
          uVar16 = (uVar25 >> 0xb) * (uint)uVar3;
          if (uVar24 < uVar16) {
            iVar12 = (int)lVar29 * 2;
            puVar28[uVar14 + lVar29 + 2] = (short)(0x800 - uVar3 >> 5) + uVar3;
            uVar25 = uVar16;
          }
          else {
            uVar25 = uVar25 - uVar16;
            uVar24 = uVar24 - uVar16;
            iVar12 = (int)lVar29 * 2 + 1;
            puVar28[uVar14 + lVar29 + 2] = uVar3 - (uVar3 >> 5);
            lVar23 = lVar23 + 1;
          }
          uVar3 = puVar28[uVar14 + lVar23 + 2];
          if (uVar25 < 0x1000000) {
            uVar25 = uVar25 << 8;
            uVar24 = uVar24 << 8 | (uint)*pbVar30;
            pbVar30 = pbVar30 + 1;
          }
          uVar16 = (uVar25 >> 0xb) * (uint)uVar3;
          if (uVar24 < uVar16) {
            iVar12 = iVar12 * 2;
            puVar28[uVar14 + lVar23 + 2] = (short)(0x800 - uVar3 >> 5) + uVar3;
            uVar25 = uVar16;
          }
          else {
            uVar25 = uVar25 - uVar16;
            uVar24 = uVar24 - uVar16;
            iVar12 = iVar12 * 2 + 1;
            puVar28[uVar14 + lVar23 + 2] = uVar3 - (uVar3 >> 5);
          }
          uVar16 = iVar12 - 8;
        }
        else {
          uVar26 = uVar26 - uVar25;
          uVar24 = uVar24 - uVar25;
          *puVar28 = uVar3 - (uVar3 >> 5);
          uVar3 = puVar28[1];
          if (uVar26 < 0x1000000) {
            uVar26 = uVar26 * 0x100;
            uVar24 = uVar24 * 0x100 | (uint)*pbVar30;
            pbVar30 = pbVar30 + 1;
          }
          uVar16 = (uVar26 >> 0xb) * (uint)uVar3;
          if (uVar24 < uVar16) {
            puVar28[1] = (short)(0x800 - uVar3 >> 5) + uVar3;
            uVar14 = (ulonglong)(uVar19 << 3);
            uVar3 = puVar28[uVar14 + 0x83];
            if (uVar16 < 0x1000000) {
              uVar16 = uVar16 * 0x100;
              uVar24 = uVar24 << 8 | (uint)*pbVar30;
              pbVar30 = pbVar30 + 1;
            }
            uVar19 = (uVar16 >> 0xb) * (uint)uVar3;
            if (uVar24 < uVar19) {
              puVar28[uVar14 + 0x83] = (short)(0x800 - uVar3 >> 5) + uVar3;
              lVar29 = 2;
              uVar25 = uVar19;
            }
            else {
              uVar25 = uVar16 - uVar19;
              uVar24 = uVar24 - uVar19;
              lVar29 = 3;
              puVar28[uVar14 + 0x83] = uVar3 - (uVar3 >> 5);
            }
            lVar23 = lVar29 * 2;
            uVar3 = puVar28[uVar14 + lVar29 + 0x82];
            if (uVar25 < 0x1000000) {
              uVar25 = uVar25 << 8;
              uVar24 = uVar24 << 8 | (uint)*pbVar30;
              pbVar30 = pbVar30 + 1;
            }
            uVar16 = (uVar25 >> 0xb) * (uint)uVar3;
            if (uVar24 < uVar16) {
              iVar12 = (int)lVar29 * 2;
              puVar28[uVar14 + lVar29 + 0x82] = (short)(0x800 - uVar3 >> 5) + uVar3;
              uVar25 = uVar16;
            }
            else {
              uVar25 = uVar25 - uVar16;
              uVar24 = uVar24 - uVar16;
              iVar12 = (int)lVar29 * 2 + 1;
              puVar28[uVar14 + lVar29 + 0x82] = uVar3 - (uVar3 >> 5);
              lVar23 = lVar23 + 1;
            }
            uVar3 = puVar28[uVar14 + lVar23 + 0x82];
            if (uVar25 < 0x1000000) {
              uVar25 = uVar25 << 8;
              uVar24 = uVar24 << 8 | (uint)*pbVar30;
              pbVar30 = pbVar30 + 1;
            }
            uVar19 = (uVar25 >> 0xb) * (uint)uVar3;
            if (uVar24 < uVar19) {
              uVar16 = iVar12 * 2;
              puVar28[uVar14 + lVar23 + 0x82] = (short)(0x800 - uVar3 >> 5) + uVar3;
              uVar25 = uVar19;
            }
            else {
              uVar25 = uVar25 - uVar19;
              uVar24 = uVar24 - uVar19;
              uVar16 = iVar12 * 2 + 1;
              puVar28[uVar14 + lVar23 + 0x82] = uVar3 - (uVar3 >> 5);
            }
          }
          else {
            uVar25 = uVar26 - uVar16;
            uVar24 = uVar24 - uVar16;
            uVar16 = 1;
            puVar28[1] = uVar3 - (uVar3 >> 5);
            lVar29 = 1;
            do {
              lVar23 = lVar29 * 2;
              uVar3 = puVar28[lVar29 + 0x102];
              if (uVar25 < 0x1000000) {
                uVar25 = uVar25 << 8;
                uVar24 = uVar24 << 8 | (uint)*pbVar30;
                pbVar30 = pbVar30 + 1;
              }
              uVar19 = (uVar25 >> 0xb) * (uint)uVar3;
              if (uVar24 < uVar19) {
                uVar16 = uVar16 * 2;
                puVar28[lVar29 + 0x102] = (short)(0x800 - uVar3 >> 5) + uVar3;
                uVar25 = uVar19;
              }
              else {
                uVar25 = uVar25 - uVar19;
                uVar24 = uVar24 - uVar19;
                uVar16 = uVar16 * 2 + 1;
                lVar23 = lVar23 + 1;
                puVar28[lVar29 + 0x102] = uVar3 - (uVar3 >> 5);
              }
              lVar29 = lVar23;
            } while (uVar16 < 0x100);
            uVar16 = uVar16 - 0xf0;
          }
        }
        if (0xb < uVar21) {
          lVar29 = 3;
          uVar19 = 3;
          if (uVar16 < 4) {
            uVar19 = uVar16;
          }
          lVar23 = lVar8 + 0x360 + (ulonglong)(uVar19 << 6) * 2;
          uVar3 = *(ushort *)(lVar23 + 2);
          if (uVar25 < 0x1000000) {
            uVar25 = uVar25 << 8;
            uVar24 = uVar24 << 8 | (uint)*pbVar30;
            pbVar30 = pbVar30 + 1;
          }
          uVar19 = (uVar25 >> 0xb) * (uint)uVar3;
          if (uVar24 < uVar19) {
            *(ushort *)(lVar23 + 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
            iVar12 = 2;
            lVar29 = 2;
            uVar25 = uVar19;
          }
          else {
            uVar25 = uVar25 - uVar19;
            uVar24 = uVar24 - uVar19;
            iVar12 = 3;
            *(ushort *)(lVar23 + 2) = uVar3 - (uVar3 >> 5);
          }
          lVar29 = lVar29 * 2;
          uVar3 = *(ushort *)(lVar29 + lVar23);
          if (uVar25 < 0x1000000) {
            uVar25 = uVar25 << 8;
            uVar24 = uVar24 << 8 | (uint)*pbVar30;
            pbVar30 = pbVar30 + 1;
          }
          uVar19 = (uVar25 >> 0xb) * (uint)uVar3;
          if (uVar24 < uVar19) {
            iVar12 = iVar12 * 2;
            *(ushort *)(lVar29 + lVar23) = (short)(0x800 - uVar3 >> 5) + uVar3;
            uVar25 = uVar19;
          }
          else {
            uVar25 = uVar25 - uVar19;
            uVar24 = uVar24 - uVar19;
            iVar12 = iVar12 * 2 + 1;
            *(ushort *)(lVar29 + lVar23) = uVar3 - (uVar3 >> 5);
            lVar29 = lVar29 + 1;
          }
          uVar3 = *(ushort *)(lVar23 + lVar29 * 2);
          if (uVar25 < 0x1000000) {
            uVar25 = uVar25 << 8;
            uVar24 = uVar24 << 8 | (uint)*pbVar30;
            pbVar30 = pbVar30 + 1;
          }
          uVar19 = (uVar25 >> 0xb) * (uint)uVar3;
          if (uVar24 < uVar19) {
            *(ushort *)(lVar23 + lVar29 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
            uVar26 = iVar12 * 2;
            uVar25 = uVar19;
          }
          else {
            uVar25 = uVar25 - uVar19;
            uVar24 = uVar24 - uVar19;
            *(ushort *)(lVar23 + lVar29 * 2) = uVar3 - (uVar3 >> 5);
            uVar26 = iVar12 * 2 + 1;
          }
          uVar14 = (ulonglong)uVar26;
          uVar3 = *(ushort *)(lVar23 + uVar14 * 2);
          if (uVar25 < 0x1000000) {
            uVar25 = uVar25 << 8;
            uVar24 = uVar24 << 8 | (uint)*pbVar30;
            pbVar30 = pbVar30 + 1;
          }
          uVar19 = (uVar25 >> 0xb) * (uint)uVar3;
          if (uVar24 < uVar19) {
            *(ushort *)(lVar23 + uVar14 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
            uVar26 = uVar26 * 2;
            uVar25 = uVar19;
          }
          else {
            uVar25 = uVar25 - uVar19;
            uVar24 = uVar24 - uVar19;
            *(ushort *)(lVar23 + uVar14 * 2) = uVar3 - (uVar3 >> 5);
            uVar26 = uVar26 * 2 + 1;
          }
          uVar14 = (ulonglong)uVar26;
          uVar3 = *(ushort *)(lVar23 + uVar14 * 2);
          if (uVar25 < 0x1000000) {
            uVar25 = uVar25 << 8;
            uVar24 = uVar24 << 8 | (uint)*pbVar30;
            pbVar30 = pbVar30 + 1;
          }
          uVar19 = (uVar25 >> 0xb) * (uint)uVar3;
          if (uVar24 < uVar19) {
            *(ushort *)(lVar23 + uVar14 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
            uVar26 = uVar26 * 2;
            uVar25 = uVar19;
          }
          else {
            uVar25 = uVar25 - uVar19;
            uVar24 = uVar24 - uVar19;
            *(ushort *)(lVar23 + uVar14 * 2) = uVar3 - (uVar3 >> 5);
            uVar26 = uVar26 * 2 + 1;
          }
          uVar14 = (ulonglong)uVar26;
          uVar3 = *(ushort *)(lVar23 + uVar14 * 2);
          if (uVar25 < 0x1000000) {
            uVar25 = uVar25 << 8;
            uVar24 = uVar24 << 8 | (uint)*pbVar30;
            pbVar30 = pbVar30 + 1;
          }
          uVar19 = (uVar25 >> 0xb) * (uint)uVar3;
          if (uVar24 < uVar19) {
            *(ushort *)(lVar23 + uVar14 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
            iVar12 = uVar26 * 2;
            uVar25 = uVar19;
          }
          else {
            uVar25 = uVar25 - uVar19;
            uVar24 = uVar24 - uVar19;
            *(ushort *)(lVar23 + uVar14 * 2) = uVar3 - (uVar3 >> 5);
            iVar12 = uVar26 * 2 + 1;
          }
          uVar19 = iVar12 - 0x40;
          if (3 < uVar19) {
            uVar14 = (ulonglong)uVar19;
            uVar26 = uVar19 & 1 | 2;
            iVar12 = (uVar19 >> 1) - 1;
            if (uVar19 < 0xe) {
              uVar13 = 1;
              uVar19 = uVar26 << ((byte)iVar12 & 0x1f);
              lVar23 = 1;
              lVar29 = lVar8 + 0x55e + (uVar19 - uVar14) * 2;
              do {
                lVar23 = lVar23 * 2;
                uVar3 = *(ushort *)(lVar23 + lVar29);
                if (uVar25 < 0x1000000) {
                  uVar25 = uVar25 << 8;
                  uVar24 = uVar24 << 8 | (uint)*pbVar30;
                  pbVar30 = pbVar30 + 1;
                }
                uVar26 = (uVar25 >> 0xb) * (uint)uVar3;
                if (uVar24 < uVar26) {
                  *(ushort *)(lVar23 + lVar29) = (short)(0x800 - uVar3 >> 5) + uVar3;
                  uVar25 = uVar26;
                }
                else {
                  uVar25 = uVar25 - uVar26;
                  uVar24 = uVar24 - uVar26;
                  *(ushort *)(lVar23 + lVar29) = uVar3 - (uVar3 >> 5);
                  lVar23 = lVar23 + 1;
                  uVar19 = uVar19 | uVar13;
                }
                uVar13 = uVar13 * 2;
                iVar12 = iVar12 + -1;
              } while (iVar12 != 0);
            }
            else {
              iVar12 = (uVar19 >> 1) - 5;
              do {
                if (uVar25 < 0x1000000) {
                  uVar25 = uVar25 << 8;
                  uVar24 = uVar24 << 8 | (uint)*pbVar30;
                  pbVar30 = pbVar30 + 1;
                }
                uVar25 = uVar25 >> 1;
                uVar19 = (int)(uVar24 - uVar25) >> 0x1f;
                uVar26 = uVar19 + 1 + uVar26 * 2;
                uVar24 = (uVar24 - uVar25) + (uVar19 & uVar25);
                iVar12 = iVar12 + -1;
              } while (iVar12 != 0);
              uVar3 = *(ushort *)(lVar8 + 0x646);
              uVar19 = uVar26 * 0x10;
              if (uVar25 < 0x1000000) {
                uVar25 = uVar25 << 8;
                uVar24 = uVar24 * 0x100 | (uint)*pbVar30;
                pbVar30 = pbVar30 + 1;
              }
              uVar26 = (uVar25 >> 0xb) * (uint)uVar3;
              if (uVar24 < uVar26) {
                *(ushort *)(lVar8 + 0x646) = (short)(0x800 - uVar3 >> 5) + uVar3;
                lVar29 = 2;
                uVar25 = uVar26;
              }
              else {
                uVar25 = uVar25 - uVar26;
                uVar24 = uVar24 - uVar26;
                lVar29 = 3;
                uVar19 = uVar19 | 1;
                *(ushort *)(lVar8 + 0x646) = uVar3 - (uVar3 >> 5);
              }
              lVar23 = lVar29 * 2;
              uVar3 = *(ushort *)(lVar23 + 0x644 + lVar8);
              if (uVar25 < 0x1000000) {
                uVar25 = uVar25 << 8;
                uVar24 = uVar24 << 8 | (uint)*pbVar30;
                pbVar30 = pbVar30 + 1;
              }
              uVar26 = (uVar25 >> 0xb) * (uint)uVar3;
              if (uVar24 < uVar26) {
                iVar12 = (int)lVar29 * 2;
                *(ushort *)(lVar23 + 0x644 + lVar8) = (short)(0x800 - uVar3 >> 5) + uVar3;
                lVar29 = lVar23;
                uVar25 = uVar26;
              }
              else {
                uVar25 = uVar25 - uVar26;
                uVar24 = uVar24 - uVar26;
                iVar12 = (int)lVar29 * 2 + 1;
                lVar29 = lVar23 + 1;
                uVar19 = uVar19 | 2;
                *(ushort *)(lVar23 + 0x644 + lVar8) = uVar3 - (uVar3 >> 5);
              }
              uVar3 = *(ushort *)(lVar8 + 0x644 + lVar29 * 2);
              if (uVar25 < 0x1000000) {
                uVar25 = uVar25 << 8;
                uVar24 = uVar24 << 8 | (uint)*pbVar30;
                pbVar30 = pbVar30 + 1;
              }
              uVar26 = (uVar25 >> 0xb) * (uint)uVar3;
              if (uVar24 < uVar26) {
                *(ushort *)(lVar8 + 0x644 + lVar29 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
                uVar13 = iVar12 * 2;
                uVar25 = uVar26;
              }
              else {
                uVar25 = uVar25 - uVar26;
                uVar24 = uVar24 - uVar26;
                uVar13 = iVar12 * 2 + 1;
                uVar19 = uVar19 | 4;
                *(ushort *)(lVar8 + 0x644 + lVar29 * 2) = uVar3 - (uVar3 >> 5);
              }
              uVar14 = (ulonglong)uVar13;
              uVar3 = *(ushort *)(lVar8 + 0x644 + uVar14 * 2);
              if (uVar25 < 0x1000000) {
                uVar25 = uVar25 << 8;
                uVar24 = uVar24 << 8 | (uint)*pbVar30;
                pbVar30 = pbVar30 + 1;
              }
              uVar26 = (uVar25 >> 0xb) * (uint)uVar3;
              if (uVar24 < uVar26) {
                *(ushort *)(lVar8 + 0x644 + uVar14 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
                uVar25 = uVar26;
              }
              else {
                uVar25 = uVar25 - uVar26;
                uVar24 = uVar24 - uVar26;
                uVar19 = uVar19 | 8;
                *(ushort *)(lVar8 + 0x644 + uVar14 * 2) = uVar3 - (uVar3 >> 5);
              }
              if (uVar19 == 0xffffffff) {
                iVar12 = uVar16 + 0x112;
                uVar21 = uVar21 - 0xc;
LAB_14009fca0:
                if (uVar25 < 0x1000000) {
                  uVar25 = uVar25 << 8;
                  uVar24 = uVar24 << 8 | (uint)*pbVar30;
                  pbVar30 = pbVar30 + 1;
                }
                *(byte **)(param_1 + 8) = pbVar30;
                param_1[0x13] = local_res8;
                param_1[0x16] = local_84;
                param_1[0x14] = local_res20;
                param_1[10] = uVar25;
                param_1[0xb] = uVar24;
                param_1[0x17] = iVar12;
                *(ulonglong *)(param_1 + 0xc) = local_78;
                param_1[0x15] = local_88;
                param_1[0x10] = uVar20;
                param_1[0x12] = uVar21;
                return 0;
              }
            }
          }
          local_84 = local_88;
          local_88 = local_res20;
          local_res20 = local_res8;
          uVar26 = uVar7;
          if (uVar7 == 0) {
            uVar26 = uVar20;
          }
          if (uVar26 <= uVar19) goto LAB_14009fcfd;
          uVar21 = (-(uint)(uVar21 < 0x13) & 0xfffffffd) + 10;
          local_res8 = uVar19 + 1;
        }
        uVar16 = uVar16 + 2;
        uVar14 = param_2 - local_78;
        if (uVar14 == 0) {
LAB_14009fcfd:
          *(ulonglong *)(param_1 + 0xc) = local_78;
          return 1;
        }
        uVar17 = (ulonglong)uVar16;
        if (uVar14 < uVar16) {
          uVar17 = uVar14 & 0xffffffff;
        }
        uVar20 = uVar20 + (int)uVar17;
        iVar12 = uVar16 - (int)uVar17;
        uVar14 = ((-(ulonglong)(local_78 < local_res8) & uVar10) - (ulonglong)local_res8) + local_78
        ;
        if (uVar10 - uVar14 < uVar17) {
          do {
            uVar15 = uVar14 + 1;
            *(undefined1 *)(local_78 + lVar9) = *(undefined1 *)(uVar14 + lVar9);
            local_78 = local_78 + 1;
            uVar14 = uVar15;
            if (uVar15 == uVar10) {
              uVar14 = 0;
            }
            uVar16 = (int)uVar17 - 1;
            uVar17 = (ulonglong)uVar16;
          } while (uVar16 != 0);
        }
        else {
          lVar29 = uVar14 - local_78;
          puVar18 = (undefined1 *)(local_78 + lVar9);
          local_78 = local_78 + uVar17;
          puVar1 = puVar18 + uVar17;
          do {
            *puVar18 = puVar18[lVar29];
            puVar18 = puVar18 + 1;
          } while (puVar18 != puVar1);
        }
        goto LAB_14009fc6a;
      }
      uVar25 = uVar25 - uVar26;
      uVar24 = uVar24 - uVar26;
      *(ushort *)(lVar8 + 0x180 + uVar14 * 2) = uVar3 - (uVar3 >> 5);
      if ((uVar7 == 0) && (uVar20 == 0)) {
        return 1;
      }
      uVar3 = *(ushort *)(lVar8 + 0x198 + uVar14 * 2);
      if (uVar25 < 0x1000000) {
        uVar25 = uVar25 * 0x100;
        uVar24 = uVar24 * 0x100 | (uint)*pbVar30;
        pbVar30 = pbVar30 + 1;
      }
      uVar26 = (uVar25 >> 0xb) * (uint)uVar3;
      if (uVar26 <= uVar24) {
        uVar25 = uVar25 - uVar26;
        uVar24 = uVar24 - uVar26;
        *(ushort *)(lVar8 + 0x198 + uVar14 * 2) = uVar3 - (uVar3 >> 5);
        uVar3 = *(ushort *)(lVar8 + 0x1b0 + uVar14 * 2);
        if (uVar25 < 0x1000000) {
          uVar25 = uVar25 * 0x100;
          uVar24 = uVar24 * 0x100 | (uint)*pbVar30;
          pbVar30 = pbVar30 + 1;
        }
        uVar26 = (uVar25 >> 0xb) * (uint)uVar3;
        if (uVar24 < uVar26) {
          *(ushort *)(lVar8 + 0x1b0 + uVar14 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
          uVar16 = local_res20;
        }
        else {
          uVar25 = uVar25 - uVar26;
          uVar24 = uVar24 - uVar26;
          *(ushort *)(lVar8 + 0x1b0 + uVar14 * 2) = uVar3 - (uVar3 >> 5);
          uVar3 = *(ushort *)(lVar8 + 0x1c8 + uVar14 * 2);
          if (uVar25 < 0x1000000) {
            uVar25 = uVar25 * 0x100;
            uVar24 = uVar24 * 0x100 | (uint)*pbVar30;
            pbVar30 = pbVar30 + 1;
          }
          uVar13 = (uVar25 >> 0xb) * (uint)uVar3;
          if (uVar24 < uVar13) {
            *(ushort *)(lVar8 + 0x1c8 + uVar14 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
            uVar26 = uVar13;
            uVar16 = local_88;
          }
          else {
            uVar26 = uVar25 - uVar13;
            uVar24 = uVar24 - uVar13;
            *(ushort *)(lVar8 + 0x1c8 + uVar14 * 2) = uVar3 - (uVar3 >> 5);
            local_84 = local_88;
          }
          local_88 = local_res20;
        }
        local_res20 = local_res8;
        local_res8 = uVar16;
LAB_14009f2b1:
        puVar28 = (ushort *)(lVar8 + 0xa68);
        uVar21 = (-(uint)(uVar21 < 7) & 0xfffffffd) + 0xb;
        goto LAB_14009f2c9;
      }
      *(ushort *)(lVar8 + 0x198 + uVar14 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
      uVar3 = *(ushort *)(lVar8 + 0x1e0 + lVar29 * 2);
      if (uVar26 < 0x1000000) {
        uVar26 = uVar26 * 0x100;
        uVar24 = uVar24 << 8 | (uint)*pbVar30;
        pbVar30 = pbVar30 + 1;
      }
      uVar25 = (uVar26 >> 0xb) * (uint)uVar3;
      if (uVar25 <= uVar24) {
        uVar26 = uVar26 - uVar25;
        uVar24 = uVar24 - uVar25;
        *(ushort *)(lVar8 + 0x1e0 + lVar29 * 2) = uVar3 - (uVar3 >> 5);
        goto LAB_14009f2b1;
      }
      uVar14 = (ulonglong)local_res8;
      *(ushort *)(lVar8 + 0x1e0 + lVar29 * 2) = (short)(0x800 - uVar3 >> 5) + uVar3;
      uVar20 = uVar20 + 1;
      *(undefined1 *)(local_78 + lVar9) =
           *(undefined1 *)(((-(ulonglong)(local_78 < uVar14) & uVar10) - uVar14) + local_78 + lVar9)
      ;
      local_78 = local_78 + 1;
      uVar21 = (-(uint)(uVar21 < 7) & 0xfffffffe) + 0xb;
    }
    if ((param_2 <= local_78) || (param_3 <= pbVar30)) goto LAB_14009fca0;
  } while( true );
}


// ==== FUN_14009fd18 @ 14009fd18  undefined FUN_14009fd18(longlong param_1, longlong param_2)

void FUN_14009fd18(longlong param_1,longlong param_2)

{
  uint uVar1;
  uint uVar2;
  longlong lVar3;
  ulonglong uVar4;
  uint uVar5;
  ulonglong uVar6;
  ulonglong uVar7;
  
  uVar1 = *(uint *)(param_1 + 0x5c);
  if ((uVar1 != 0) && (uVar1 < 0x112)) {
    uVar7 = *(ulonglong *)(param_1 + 0x30);
    lVar3 = *(longlong *)(param_1 + 0x18);
    uVar4 = *(ulonglong *)(param_1 + 0x38);
    uVar2 = *(uint *)(param_1 + 0x4c);
    uVar6 = (ulonglong)uVar1;
    if (param_2 - uVar7 < (ulonglong)uVar1) {
      uVar6 = param_2 - uVar7 & 0xffffffff;
    }
    uVar5 = (uint)uVar6;
    if ((*(int *)(param_1 + 0x44) == 0) &&
       ((uint)(*(int *)(param_1 + 0xc) - *(int *)(param_1 + 0x40)) <= uVar5)) {
      *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0xc);
    }
    *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + uVar5;
    *(uint *)(param_1 + 0x5c) = uVar1 - uVar5;
    while (uVar5 != 0) {
      *(undefined1 *)(uVar7 + lVar3) =
           *(undefined1 *)
            (((-(ulonglong)(uVar7 < uVar2) & uVar4) - (ulonglong)uVar2) + uVar7 + lVar3);
      uVar7 = uVar7 + 1;
      uVar5 = (int)uVar6 - 1;
      uVar6 = (ulonglong)uVar5;
    }
    *(ulonglong *)(param_1 + 0x30) = uVar7;
  }
  return;
}


// ==== FUN_14009fda8 @ 14009fda8  undefined8 FUN_14009fda8(undefined4 * param_1, ulonglong param_2, byte * param_3)

undefined8 FUN_14009fda8(undefined4 *param_1,ulonglong param_2,byte *param_3)

{
  undefined8 uVar1;
  ulonglong uVar2;
  
  while( true ) {
    uVar2 = param_2;
    if (param_1[0x11] == 0) {
      if ((ulonglong)(uint)(param_1[3] - param_1[0x10]) < param_2 - *(longlong *)(param_1 + 0xc)) {
        uVar2 = (ulonglong)(uint)(param_1[3] - param_1[0x10]) + *(longlong *)(param_1 + 0xc);
      }
    }
    uVar1 = FUN_14009e7ac(param_1,uVar2,param_3);
    if ((int)uVar1 != 0) break;
    if ((param_1[0x11] == 0) && ((uint)param_1[3] <= (uint)param_1[0x10])) {
      param_1[0x11] = param_1[3];
    }
    FUN_14009fd18((longlong)param_1,param_2);
    if (((param_2 <= *(ulonglong *)(param_1 + 0xc)) || (param_3 <= *(byte **)(param_1 + 8))) ||
       (0x111 < (uint)param_1[0x17])) {
      if (0x112 < (uint)param_1[0x17]) {
        param_1[0x17] = 0x112;
      }
      return 0;
    }
  }
  return uVar1;
}


// ==== FUN_14009fe48 @ 14009fe48  undefined4 FUN_14009fe48(char * param_1, byte * param_2, longlong param_3)

undefined4 FUN_14009fe48(char *param_1,byte *param_2,longlong param_3)

{
  byte *pbVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  ushort *puVar7;
  longlong lVar8;
  longlong lVar9;
  longlong lVar10;
  uint uVar11;
  uint uVar12;
  ulonglong uVar13;
  uint uVar14;
  undefined4 local_res8;
  
  uVar12 = *(uint *)(param_1 + 0x28);
  uVar3 = *(uint *)(param_1 + 0x48);
  uVar13 = (ulonglong)uVar3;
  uVar11 = *(uint *)(param_1 + 0x2c);
  lVar9 = *(longlong *)(param_1 + 0x10);
  pbVar1 = param_2 + param_3;
  uVar14 = (1 << ((byte)*(undefined4 *)(param_1 + 8) & 0x1f)) - 1U & *(uint *)(param_1 + 0x40);
  lVar10 = (ulonglong)(uVar3 << 4) + (ulonglong)uVar14;
  if (uVar12 < 0x1000000) {
    if (pbVar1 <= param_2) {
      return 0;
    }
    uVar12 = uVar12 << 8;
    uVar11 = uVar11 << 8 | (uint)*param_2;
    param_2 = param_2 + 1;
  }
  uVar2 = (uVar12 >> 0xb) * (uint)*(ushort *)(lVar9 + lVar10 * 2);
  if (uVar11 < uVar2) {
    lVar10 = 0;
    lVar9 = lVar9 + 0xe6c;
    if ((*(int *)(param_1 + 0x44) != 0) || (*(int *)(param_1 + 0x40) != 0)) {
      lVar8 = *(longlong *)(param_1 + 0x30);
      if (lVar8 == 0) {
        lVar8 = *(longlong *)(param_1 + 0x38);
      }
      lVar9 = lVar9 + (ulonglong)
                      (((uint)(*(byte *)(*(longlong *)(param_1 + 0x18) + -1 + lVar8) >>
                              (8U - *param_1 & 0x1f)) +
                       (((1 << ((byte)*(undefined4 *)(param_1 + 4) & 0x1f)) - 1U &
                        *(uint *)(param_1 + 0x40)) << ((byte)*(undefined4 *)param_1 & 0x1f))) *
                      0x300) * 2;
    }
    if (uVar3 < 7) {
      uVar12 = 1;
      lVar10 = 1;
      do {
        lVar10 = lVar10 * 2;
        if (uVar2 < 0x1000000) {
          if (pbVar1 <= param_2) {
            return 0;
          }
          uVar2 = uVar2 << 8;
          uVar11 = uVar11 << 8 | (uint)*param_2;
          param_2 = param_2 + 1;
        }
        uVar3 = (uVar2 >> 0xb) * (uint)*(ushort *)(lVar10 + lVar9);
        if (uVar11 < uVar3) {
          uVar12 = uVar12 * 2;
          uVar2 = uVar3;
        }
        else {
          uVar2 = uVar2 - uVar3;
          uVar11 = uVar11 - uVar3;
          uVar12 = uVar12 * 2 + 1;
          lVar10 = lVar10 + 1;
        }
      } while (uVar12 < 0x100);
    }
    else {
      if (*(ulonglong *)(param_1 + 0x30) < (ulonglong)*(uint *)(param_1 + 0x4c)) {
        lVar10 = *(longlong *)(param_1 + 0x38);
      }
      lVar8 = 1;
      uVar14 = 0x100;
      uVar3 = (uint)*(byte *)((*(longlong *)(param_1 + 0x18) - (ulonglong)*(uint *)(param_1 + 0x4c))
                              + *(longlong *)(param_1 + 0x30) + lVar10);
      uVar12 = 1;
      do {
        uVar3 = uVar3 * 2;
        uVar5 = uVar14 & uVar3;
        if (uVar2 < 0x1000000) {
          if (pbVar1 <= param_2) {
            return 0;
          }
          uVar2 = uVar2 << 8;
          uVar11 = uVar11 << 8 | (uint)*param_2;
          param_2 = param_2 + 1;
        }
        uVar4 = (uVar2 >> 0xb) *
                (uint)*(ushort *)(lVar9 + ((ulonglong)uVar14 + (ulonglong)uVar5 + lVar8) * 2);
        if (uVar11 < uVar4) {
          uVar12 = uVar12 * 2;
          uVar5 = ~uVar5;
          lVar8 = lVar8 * 2;
          uVar2 = uVar4;
        }
        else {
          uVar2 = uVar2 - uVar4;
          uVar12 = uVar12 * 2 + 1;
          lVar8 = lVar8 * 2 + 1;
          uVar11 = uVar11 - uVar4;
        }
        uVar14 = uVar14 & uVar5;
      } while (uVar12 < 0x100);
    }
    local_res8 = 1;
    goto LAB_1400a0429;
  }
  uVar12 = uVar12 - uVar2;
  uVar11 = uVar11 - uVar2;
  if (uVar12 < 0x1000000) {
    if (pbVar1 <= param_2) {
      return 0;
    }
    uVar12 = uVar12 * 0x100;
    uVar11 = uVar11 * 0x100 | (uint)*param_2;
    param_2 = param_2 + 1;
  }
  iVar6 = 0;
  uVar3 = (uVar12 >> 0xb) * (uint)*(ushort *)(lVar9 + 0x180 + uVar13 * 2);
  if (uVar11 < uVar3) {
    uVar12 = 0;
    puVar7 = (ushort *)(lVar9 + 0x664);
    local_res8 = 2;
  }
  else {
    uVar12 = uVar12 - uVar3;
    uVar11 = uVar11 - uVar3;
    local_res8 = 3;
    if (uVar12 < 0x1000000) {
      if (pbVar1 <= param_2) {
        return 0;
      }
      uVar12 = uVar12 * 0x100;
      uVar11 = uVar11 * 0x100 | (uint)*param_2;
      param_2 = param_2 + 1;
    }
    uVar2 = (uVar12 >> 0xb) * (uint)*(ushort *)(lVar9 + 0x198 + uVar13 * 2);
    if (uVar11 < uVar2) {
      if (uVar2 < 0x1000000) {
        if (pbVar1 <= param_2) {
          return 0;
        }
        uVar2 = uVar2 * 0x100;
        uVar11 = uVar11 << 8 | (uint)*param_2;
        param_2 = param_2 + 1;
      }
      uVar12 = (uVar2 >> 0xb) * (uint)*(ushort *)(lVar9 + 0x1e0 + lVar10 * 2);
      if (uVar11 < uVar12) {
        if ((uVar12 < 0x1000000) && (pbVar1 <= param_2)) {
          return 0;
        }
        return 3;
      }
LAB_1400a01b1:
      uVar3 = uVar2 - uVar12;
      uVar11 = uVar11 - uVar12;
    }
    else {
      uVar12 = uVar12 - uVar2;
      uVar11 = uVar11 - uVar2;
      if (uVar12 < 0x1000000) {
        if (pbVar1 <= param_2) {
          return 0;
        }
        uVar12 = uVar12 * 0x100;
        uVar11 = uVar11 * 0x100 | (uint)*param_2;
        param_2 = param_2 + 1;
      }
      uVar3 = (uVar12 >> 0xb) * (uint)*(ushort *)(lVar9 + 0x1b0 + uVar13 * 2);
      if (uVar3 <= uVar11) {
        uVar2 = uVar12 - uVar3;
        uVar11 = uVar11 - uVar3;
        if (uVar2 < 0x1000000) {
          if (pbVar1 <= param_2) {
            return 0;
          }
          uVar2 = uVar2 * 0x100;
          uVar11 = uVar11 * 0x100 | (uint)*param_2;
          param_2 = param_2 + 1;
        }
        uVar3 = (uVar2 >> 0xb) * (uint)*(ushort *)(lVar9 + 0x1c8 + uVar13 * 2);
        uVar12 = uVar3;
        if (uVar3 <= uVar11) goto LAB_1400a01b1;
      }
    }
    uVar12 = 0xc;
    puVar7 = (ushort *)(lVar9 + 0xa68);
  }
  if (uVar3 < 0x1000000) {
    if (pbVar1 <= param_2) {
      return 0;
    }
    uVar3 = uVar3 << 8;
    uVar11 = uVar11 << 8 | (uint)*param_2;
    param_2 = param_2 + 1;
  }
  uVar2 = (uVar3 >> 0xb) * (uint)*puVar7;
  if (uVar11 < uVar2) {
    uVar3 = 8;
    puVar7 = puVar7 + (ulonglong)(uVar14 << 3) + 2;
  }
  else {
    uVar3 = uVar3 - uVar2;
    uVar11 = uVar11 - uVar2;
    if (uVar3 < 0x1000000) {
      if (pbVar1 <= param_2) {
        return 0;
      }
      uVar3 = uVar3 * 0x100;
      uVar11 = uVar11 * 0x100 | (uint)*param_2;
      param_2 = param_2 + 1;
    }
    uVar5 = (uVar3 >> 0xb) * (uint)puVar7[1];
    if (uVar11 < uVar5) {
      uVar3 = 8;
      iVar6 = 8;
      puVar7 = puVar7 + (ulonglong)(uVar14 << 3) + 0x82;
      uVar2 = uVar5;
    }
    else {
      uVar2 = uVar3 - uVar5;
      puVar7 = puVar7 + 0x102;
      iVar6 = 0x10;
      uVar11 = uVar11 - uVar5;
      uVar3 = 0x100;
    }
  }
  uVar5 = 1;
  uVar14 = 1;
  lVar10 = 1;
  do {
    lVar8 = lVar10 * 2;
    if (uVar2 < 0x1000000) {
      if (pbVar1 <= param_2) {
        return 0;
      }
      uVar2 = uVar2 << 8;
      uVar11 = uVar11 << 8 | (uint)*param_2;
      param_2 = param_2 + 1;
    }
    uVar4 = (uVar2 >> 0xb) * (uint)puVar7[lVar10];
    if (uVar11 < uVar4) {
      uVar14 = uVar14 * 2;
      uVar2 = uVar4;
    }
    else {
      uVar2 = uVar2 - uVar4;
      uVar11 = uVar11 - uVar4;
      uVar14 = uVar14 * 2 + 1;
      lVar8 = lVar8 + 1;
    }
    lVar10 = lVar8;
  } while (uVar14 < uVar3);
  uVar14 = uVar14 + (iVar6 - uVar3);
  if (uVar12 < 4) {
    uVar12 = 3;
    if (uVar14 < 4) {
      uVar12 = uVar14;
    }
    lVar10 = 1;
    do {
      lVar10 = lVar10 * 2;
      if (uVar2 < 0x1000000) {
        if (pbVar1 <= param_2) {
          return 0;
        }
        uVar2 = uVar2 << 8;
        uVar11 = uVar11 << 8 | (uint)*param_2;
        param_2 = param_2 + 1;
      }
      uVar3 = (uVar2 >> 0xb) *
              (uint)*(ushort *)(lVar10 + lVar9 + 0x360 + (ulonglong)(uVar12 << 6) * 2);
      if (uVar11 < uVar3) {
        uVar5 = uVar5 * 2;
        uVar2 = uVar3;
      }
      else {
        uVar2 = uVar2 - uVar3;
        uVar11 = uVar11 - uVar3;
        uVar5 = uVar5 * 2 + 1;
        lVar10 = lVar10 + 1;
      }
    } while (uVar5 < 0x40);
    uVar5 = uVar5 - 0x40;
    if (3 < uVar5) {
      iVar6 = (uVar5 >> 1) - 1;
      if (uVar5 < 0xe) {
        lVar9 = lVar9 + 0x55e +
                ((ulonglong)((uVar5 & 1 | 2) << ((byte)iVar6 & 0x1f)) - (ulonglong)uVar5) * 2;
      }
      else {
        iVar6 = (uVar5 >> 1) - 5;
        do {
          if (uVar2 < 0x1000000) {
            if (pbVar1 <= param_2) {
              return 0;
            }
            uVar2 = uVar2 << 8;
            uVar11 = uVar11 << 8 | (uint)*param_2;
            param_2 = param_2 + 1;
          }
          uVar2 = uVar2 >> 1;
          uVar11 = uVar11 - (0xffffffffU - ((int)(uVar11 - uVar2) >> 0x1f) & uVar2);
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
        lVar9 = lVar9 + 0x644;
        iVar6 = 4;
      }
      lVar10 = 1;
      do {
        lVar10 = lVar10 * 2;
        uVar12 = uVar2;
        if (uVar2 < 0x1000000) {
          if (pbVar1 <= param_2) {
            return 0;
          }
          uVar12 = uVar2 << 8;
          uVar11 = uVar11 << 8 | (uint)*param_2;
          param_2 = param_2 + 1;
        }
        uVar2 = (uVar12 >> 0xb) * (uint)*(ushort *)(lVar10 + lVar9);
        if (uVar2 <= uVar11) {
          uVar11 = uVar11 - uVar2;
          lVar10 = lVar10 + 1;
          uVar2 = uVar12 - uVar2;
        }
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
  }
LAB_1400a0429:
  if (0xffffff < uVar2) {
    return local_res8;
  }
  if (pbVar1 <= param_2) {
    return 0;
  }
  return local_res8;
}


// ==== FUN_1400a0450 @ 1400a0450  undefined FUN_1400a0450(longlong param_1, int param_2, int param_3)

void FUN_1400a0450(longlong param_1,int param_2,int param_3)

{
  *(undefined4 *)(param_1 + 0x60) = 1;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  if (param_2 != 0) {
    *(undefined4 *)(param_1 + 0x40) = 0;
    *(undefined4 *)(param_1 + 0x44) = 0;
    *(undefined4 *)(param_1 + 100) = 1;
  }
  if (param_3 != 0) {
    *(undefined4 *)(param_1 + 100) = 1;
  }
  return;
}


// ==== FUN_1400a047c @ 1400a047c  undefined FUN_1400a047c(longlong param_1)

void FUN_1400a047c(longlong param_1)

{
  *(undefined8 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x60) = 1;
  *(undefined4 *)(param_1 + 100) = 1;
  return;
}


// ==== FUN_1400a0498 @ 1400a0498  undefined FUN_1400a0498(undefined4 * param_1)

void FUN_1400a0498(undefined4 *param_1)

{
  ulonglong uVar1;
  uint uVar2;
  undefined2 *puVar3;
  
  uVar2 = (0x300 << ((char)param_1[1] + (char)*param_1 & 0x1fU)) + 0x736;
  uVar1 = (ulonglong)uVar2;
  if (uVar2 != 0) {
    puVar3 = *(undefined2 **)(param_1 + 4);
    for (; uVar1 != 0; uVar1 = uVar1 - 1) {
      *puVar3 = 0x400;
      puVar3 = puVar3 + 1;
    }
  }
  param_1[0x12] = 0;
  param_1[0x19] = 0;
  param_1[0x16] = 1;
  param_1[0x15] = 1;
  param_1[0x14] = 1;
  param_1[0x13] = 1;
  return;
}


// ==== FUN_1400a04ec @ 1400a04ec  bool FUN_1400a04ec(char * param_1, ulonglong param_2, byte * param_3, ulonglong * param_4, int param_5, undefined4 * param_6)

bool FUN_1400a04ec(char *param_1,ulonglong param_2,byte *param_3,ulonglong *param_4,int param_5,
                  undefined4 *param_6)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  int iVar6;
  uint uVar7;
  undefined8 uVar8;
  ulonglong uVar9;
  uint uVar10;
  undefined2 *puVar11;
  byte *pbVar12;
  ulonglong _Size;
  uint uVar13;
  bool bVar14;
  byte *local_res18;
  
  _Size = *param_4;
  *param_4 = 0;
  FUN_14009fd18((longlong)param_1,param_2);
  *param_6 = 0;
  bVar14 = true;
  local_res18 = param_3;
  do {
    if (*(int *)(param_1 + 0x5c) == 0x112) {
      bVar14 = *(int *)(param_1 + 0x2c) == 0;
      if (bVar14) {
        *param_6 = 1;
        bVar14 = *(int *)(param_1 + 0x2c) == 0;
      }
      return !bVar14;
    }
    if (*(int *)(param_1 + 0x60) != 0) {
      while ((_Size != 0 && (*(uint *)(param_1 + 0x6c) < 5))) {
        bVar1 = *local_res18;
        local_res18 = local_res18 + 1;
        param_1[(ulonglong)*(uint *)(param_1 + 0x6c) + 0x70] = bVar1;
        *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 0x6c) + 1;
        *param_4 = *param_4 + 1;
        _Size = _Size - 1;
      }
      if (*(uint *)(param_1 + 0x6c) < 5) goto LAB_1400a074b;
      if (param_1[0x70] != '\0') {
        return true;
      }
      param_1[0x60] = '\0';
      param_1[0x61] = '\0';
      param_1[0x62] = '\0';
      param_1[99] = '\0';
      param_1[0x6c] = '\0';
      param_1[0x6d] = '\0';
      param_1[0x6e] = '\0';
      param_1[0x6f] = '\0';
      param_1[0x28] = -1;
      param_1[0x29] = -1;
      param_1[0x2a] = -1;
      param_1[0x2b] = -1;
      *(uint *)(param_1 + 0x2c) =
           CONCAT31(CONCAT21(CONCAT11(param_1[0x71],param_1[0x72]),param_1[0x73]),param_1[0x74]);
    }
    bVar3 = false;
    bVar2 = false;
    if (param_2 <= *(ulonglong *)(param_1 + 0x30)) {
      if ((*(int *)(param_1 + 0x5c) == 0) && (*(int *)(param_1 + 0x2c) == 0)) {
        *param_6 = 4;
        return false;
      }
      if (param_5 == 0) {
        bVar14 = false;
        goto LAB_1400a0761;
      }
      if (*(int *)(param_1 + 0x5c) != 0) goto LAB_1400a0761;
      bVar3 = true;
      bVar2 = true;
    }
    if (*(int *)(param_1 + 100) != 0) {
      uVar9 = (ulonglong)
              ((0x300 << ((char)*(undefined4 *)(param_1 + 4) + (char)*(undefined4 *)param_1 & 0x1fU)
               ) + 0x736);
      if (uVar9 != 0) {
        puVar11 = *(undefined2 **)(param_1 + 0x10);
        for (; uVar9 != 0; uVar9 = uVar9 - 1) {
          *puVar11 = 0x400;
          puVar11 = puVar11 + 1;
        }
      }
      param_1[0x58] = '\x01';
      param_1[0x59] = '\0';
      param_1[0x5a] = '\0';
      param_1[0x5b] = '\0';
      param_1[0x54] = '\x01';
      param_1[0x55] = '\0';
      param_1[0x56] = '\0';
      param_1[0x57] = '\0';
      param_1[0x50] = '\x01';
      param_1[0x51] = '\0';
      param_1[0x52] = '\0';
      param_1[0x53] = '\0';
      param_1[0x4c] = '\x01';
      param_1[0x4d] = '\0';
      param_1[0x4e] = '\0';
      param_1[0x4f] = '\0';
      param_1[0x48] = '\0';
      param_1[0x49] = '\0';
      param_1[0x4a] = '\0';
      param_1[0x4b] = '\0';
      param_1[100] = '\0';
      param_1[0x65] = '\0';
      param_1[0x66] = '\0';
      param_1[0x67] = '\0';
    }
    uVar10 = *(uint *)(param_1 + 0x6c);
    uVar9 = (ulonglong)(int)uVar10;
    uVar4 = uVar9;
    uVar5 = 0;
    pbVar12 = local_res18;
    if (uVar10 == 0) {
      if ((_Size < 0x14) || (bVar2)) {
        iVar6 = FUN_14009fe48(param_1,local_res18,_Size);
        if (iVar6 == 0) {
          memcpy(param_1 + 0x70,local_res18,_Size);
          *(int *)(param_1 + 0x6c) = (int)_Size;
          *param_4 = *param_4 + _Size;
LAB_1400a074b:
          *param_6 = 3;
          return false;
        }
        if ((bVar3) && (iVar6 != 2)) {
LAB_1400a0761:
          *param_6 = 2;
          return bVar14;
        }
      }
      else {
        pbVar12 = local_res18 + (_Size - 0x14);
      }
      *(byte **)(param_1 + 0x20) = local_res18;
      uVar8 = FUN_14009fda8((undefined4 *)param_1,param_2,pbVar12);
      if ((int)uVar8 != 0) {
        return true;
      }
      uVar9 = *(longlong *)(param_1 + 0x20) - (longlong)local_res18;
      *param_4 = *param_4 + uVar9;
    }
    else {
      while ((uVar13 = (uint)uVar5, uVar10 < 0x14 && (uVar10 = (uint)uVar4, uVar5 < _Size))) {
        uVar10 = uVar10 + 1;
        param_1[uVar9 + 0x70] = *pbVar12;
        uVar9 = uVar9 + 1;
        uVar4 = (ulonglong)uVar10;
        pbVar12 = pbVar12 + 1;
        uVar5 = (ulonglong)(uVar13 + 1);
      }
      *(uint *)(param_1 + 0x6c) = uVar10;
      if ((uVar10 < 0x14) || (bVar2)) {
        iVar6 = FUN_14009fe48(param_1,(byte *)(param_1 + 0x70),(ulonglong)uVar10);
        if (iVar6 == 0) {
          *param_4 = *param_4 + uVar5;
          goto LAB_1400a074b;
        }
        if ((bVar3) && (iVar6 != 2)) goto LAB_1400a0761;
      }
      *(char **)(param_1 + 0x20) = param_1 + 0x70;
      uVar8 = FUN_14009fda8((undefined4 *)param_1,param_2,(byte *)(param_1 + 0x70));
      if ((int)uVar8 != 0) {
        return true;
      }
      uVar7 = (*(int *)(param_1 + 0x20) - (int)param_1) - 0x70;
      if ((uVar10 < uVar7) || (uVar10 = uVar10 - uVar7, uVar13 < uVar10)) {
        return true;
      }
      uVar9 = (ulonglong)(uVar13 - uVar10);
      *param_4 = *param_4 + uVar9;
      param_1[0x6c] = '\0';
      param_1[0x6d] = '\0';
      param_1[0x6e] = '\0';
      param_1[0x6f] = '\0';
    }
    local_res18 = local_res18 + uVar9;
    _Size = _Size - uVar9;
  } while( true );
}


// ==== FUN_1400a07bc @ 1400a07bc  ulonglong FUN_1400a07bc(char * param_1, void * param_2, ulonglong * param_3, byte * param_4, longlong * param_5, int param_6, undefined4 * param_7)

ulonglong FUN_1400a07bc(char *param_1,void *param_2,ulonglong *param_3,byte *param_4,
                       longlong *param_5,int param_6,undefined4 *param_7)

{
  longlong lVar1;
  bool bVar2;
  int iVar3;
  undefined7 extraout_var;
  ulonglong uVar4;
  ulonglong uVar5;
  size_t _Size;
  byte *pbVar6;
  void *local_res10;
  byte *local_res20;
  
  uVar5 = *param_3;
  pbVar6 = (byte *)*param_5;
  *param_3 = 0;
  *param_5 = 0;
  local_res10 = param_2;
  while( true ) {
    uVar4 = *(ulonglong *)(param_1 + 0x38);
    if (*(ulonglong *)(param_1 + 0x30) == uVar4) {
      param_1[0x30] = '\0';
      param_1[0x31] = '\0';
      param_1[0x32] = '\0';
      param_1[0x33] = '\0';
      param_1[0x34] = '\0';
      param_1[0x35] = '\0';
      param_1[0x36] = '\0';
      param_1[0x37] = '\0';
    }
    lVar1 = *(longlong *)(param_1 + 0x30);
    if (uVar4 - lVar1 < uVar5) {
      iVar3 = 0;
    }
    else {
      uVar4 = lVar1 + uVar5;
      iVar3 = param_6;
    }
    local_res20 = pbVar6;
    bVar2 = FUN_1400a04ec(param_1,uVar4,param_4,(ulonglong *)&local_res20,iVar3,param_7);
    *param_5 = (longlong)(local_res20 + *param_5);
    pbVar6 = pbVar6 + -(longlong)local_res20;
    _Size = *(longlong *)(param_1 + 0x30) - lVar1;
    local_res20 = param_4 + (longlong)local_res20;
    memcpy(local_res10,(void *)(lVar1 + *(longlong *)(param_1 + 0x18)),_Size);
    *param_3 = *param_3 + _Size;
    local_res10 = (void *)((longlong)local_res10 + _Size);
    uVar5 = uVar5 - _Size;
    if ((int)CONCAT71(extraout_var,bVar2) != 0) break;
    if ((_Size == 0) || (param_4 = local_res20, uVar5 == 0)) {
      return 0;
    }
  }
  return CONCAT71(extraout_var,bVar2) & 0xffffffff;
}


// ==== FUN_1400a08d0 @ 1400a08d0  undefined FUN_1400a08d0(longlong param_1, longlong param_2)

void FUN_1400a08d0(longlong param_1,longlong param_2)

{
  (**(code **)(param_2 + 8))(param_2,*(undefined8 *)(param_1 + 0x10));
  *(undefined8 *)(param_1 + 0x10) = 0;
  return;
}


// ==== FUN_1400a08f4 @ 1400a08f4  undefined FUN_1400a08f4(longlong param_1, longlong param_2)

void FUN_1400a08f4(longlong param_1,longlong param_2)

{
  (**(code **)(param_2 + 8))(param_2,*(undefined8 *)(param_1 + 0x18));
  *(undefined8 *)(param_1 + 0x18) = 0;
  return;
}


// ==== FUN_1400a0918 @ 1400a0918  undefined FUN_1400a0918(longlong param_1, longlong param_2)

void FUN_1400a0918(longlong param_1,longlong param_2)

{
  (**(code **)(param_2 + 8))(param_2,*(undefined8 *)(param_1 + 0x10));
  *(undefined8 *)(param_1 + 0x10) = 0;
  (**(code **)(param_2 + 8))(param_2,*(undefined8 *)(param_1 + 0x18));
  *(undefined8 *)(param_1 + 0x18) = 0;
  return;
}


// ==== FUN_1400a0954 @ 1400a0954  undefined8 FUN_1400a0954(uint * param_1, byte * param_2, uint param_3)

undefined8 FUN_1400a0954(uint *param_1,byte *param_2,uint param_3)

{
  uint uVar1;
  
  if (4 < param_3) {
    uVar1 = *(uint *)(param_2 + 1);
    if (uVar1 < 0x1000) {
      uVar1 = 0x1000;
    }
    param_1[3] = uVar1;
    if (*param_2 < 0xe1) {
      uVar1 = *param_2 / 9;
      *param_1 = (uint)*param_2 % 9;
      param_1[2] = uVar1 / 5;
      param_1[1] = uVar1 % 5;
      return 0;
    }
  }
  return 4;
}


// ==== FUN_1400a09d4 @ 1400a09d4  undefined8 FUN_1400a09d4(longlong param_1, undefined4 * param_2, undefined8 * param_3)

undefined8 FUN_1400a09d4(longlong param_1,undefined4 *param_2,undefined8 *param_3)

{
  longlong lVar1;
  uint uVar2;
  
  uVar2 = (0x300 << ((char)param_2[1] + (char)*param_2 & 0x1fU)) + 0x736;
  if ((*(longlong *)(param_1 + 0x10) == 0) || (uVar2 != *(uint *)(param_1 + 0x68))) {
    (*(code *)param_3[1])(param_3);
    *(undefined8 *)(param_1 + 0x10) = 0;
    lVar1 = (*(code *)*param_3)(param_3,(ulonglong)uVar2 * 2);
    *(uint *)(param_1 + 0x68) = uVar2;
    *(longlong *)(param_1 + 0x10) = lVar1;
    if (lVar1 == 0) {
      return 2;
    }
  }
  return 0;
}


// ==== FUN_1400a0a44 @ 1400a0a44  undefined FUN_1400a0a44(undefined8 * param_1, byte * param_2, uint param_3, undefined8 * param_4)

void FUN_1400a0a44(undefined8 *param_1,byte *param_2,uint param_3,undefined8 *param_4)

{
  undefined8 uVar1;
  undefined8 local_18;
  undefined8 uStack_10;
  
  uVar1 = FUN_1400a0954((uint *)&local_18,param_2,param_3);
  if ((int)uVar1 == 0) {
    uVar1 = FUN_1400a09d4((longlong)param_1,(undefined4 *)&local_18,param_4);
    if ((int)uVar1 == 0) {
      *param_1 = local_18;
      param_1[1] = uStack_10;
    }
  }
  return;
}


// ==== FUN_1400a0a84 @ 1400a0a84  undefined8 FUN_1400a0a84(undefined8 * param_1, byte * param_2, uint param_3, undefined8 * param_4)

undefined8 FUN_1400a0a84(undefined8 *param_1,byte *param_2,uint param_3,undefined8 *param_4)

{
  undefined8 uVar1;
  ulonglong uVar2;
  longlong lVar3;
  ulonglong uVar4;
  undefined8 local_18;
  undefined4 uStack_10;
  uint uStack_c;
  
  uVar1 = FUN_1400a0954((uint *)&local_18,param_2,param_3);
  if (((int)uVar1 == 0) &&
     (uVar1 = FUN_1400a09d4((longlong)param_1,(undefined4 *)&local_18,param_4), (int)uVar1 == 0)) {
    uVar2 = (ulonglong)uStack_c;
    uVar4 = 0xfff;
    if (uStack_c < 0x40000000) {
      if (0x3fffff < uStack_c) {
        uVar4 = 0xfffff;
      }
    }
    else {
      uVar4 = 0x3fffff;
    }
    uVar4 = uVar2 + uVar4 & ~uVar4;
    if (uVar4 < uVar2) {
      uVar4 = uVar2;
    }
    if ((param_1[3] == 0) || (uVar4 != param_1[7])) {
      (*(code *)param_4[1])(param_4);
      param_1[3] = 0;
      lVar3 = (*(code *)*param_4)(param_4,uVar4);
      param_1[3] = lVar3;
      if (lVar3 == 0) {
        (*(code *)param_4[1])(param_4,param_1[2]);
        param_1[2] = 0;
        return 2;
      }
    }
    param_1[7] = uVar4;
    uVar1 = 0;
    *param_1 = local_18;
    param_1[1] = CONCAT44(uStack_c,uStack_10);
  }
  return uVar1;
}


// ==== FUN_1400a0b5c @ 1400a0b5c  undefined FUN_1400a0b5c(undefined8 param_1, ulonglong * param_2, byte * param_3, ulonglong * param_4, byte * param_5, uint param_6, int param_7, undefined4 * param_8, undefined8 * param_9)

void FUN_1400a0b5c(undefined8 param_1,ulonglong *param_2,byte *param_3,ulonglong *param_4,
                  byte *param_5,uint param_6,int param_7,undefined4 *param_8,undefined8 *param_9)

{
  ulonglong uVar1;
  ulonglong uVar2;
  int iVar3;
  undefined1 auStackY_118 [32];
  char local_e8 [16];
  undefined8 local_d8;
  undefined8 local_d0;
  ulonglong local_b8;
  ulonglong local_b0;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_7c;
  ulonglong local_58;
  
  local_58 = DAT_140103510 ^ (ulonglong)auStackY_118;
  uVar1 = *param_4;
  uVar2 = *param_2;
  *param_4 = 0;
  *param_2 = 0;
  *param_8 = 0;
  if (4 < uVar1) {
    local_d0 = 0;
    local_d8 = 0;
    iVar3 = FUN_1400a0a44((undefined8 *)local_e8,param_5,param_6,param_9);
    if (iVar3 == 0) {
      local_b8 = 0;
      local_8c = 0;
      local_88 = 1;
      local_84 = 1;
      local_7c = 0;
      local_a8 = 0;
      local_a4 = 0;
      *param_4 = uVar1;
      local_d0 = param_1;
      local_b0 = uVar2;
      FUN_1400a04ec(local_e8,uVar2,param_3,param_4,param_7,param_8);
      *param_2 = local_b8;
      (*(code *)param_9[1])(param_9,local_d8);
    }
  }
  __security_check_cookie(local_58 ^ (ulonglong)auStackY_118);
  return;
}


// ==== FUN_1400a0ce4 @ 1400a0ce4  undefined FUN_1400a0ce4(undefined8 * param_1, uint param_2, undefined8 * param_3)

void FUN_1400a0ce4(undefined8 *param_1,uint param_2,undefined8 *param_3)

{
  int iVar1;
  undefined1 auStack_38 [32];
  byte local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 local_14;
  ulonglong local_10;
  
  local_10 = DAT_140103510 ^ (ulonglong)auStack_38;
  if ((byte)param_2 < 0x29) {
    if ((byte)param_2 == 0x28) {
      iVar1 = -1;
    }
    else {
      iVar1 = (param_2 & 1 | 2) << ((char)((param_2 & 0xff) >> 1) + 0xbU & 0x1f);
    }
    local_17 = (undefined1)iVar1;
    local_16 = (undefined1)((uint)iVar1 >> 8);
    local_14 = (undefined1)((uint)iVar1 >> 0x18);
    local_18 = 4;
    local_15 = (undefined1)((uint)iVar1 >> 0x10);
    FUN_1400a0a44(param_1,&local_18,5,param_3);
  }
  __security_check_cookie(local_10 ^ (ulonglong)auStack_38);
  return;
}


// ==== FUN_1400a0d6c @ 1400a0d6c  undefined FUN_1400a0d6c(undefined8 * param_1, uint param_2, undefined8 * param_3)

void FUN_1400a0d6c(undefined8 *param_1,uint param_2,undefined8 *param_3)

{
  int iVar1;
  undefined1 auStack_38 [32];
  byte local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 local_14;
  ulonglong local_10;
  
  local_10 = DAT_140103510 ^ (ulonglong)auStack_38;
  if ((byte)param_2 < 0x29) {
    if ((byte)param_2 == 0x28) {
      iVar1 = -1;
    }
    else {
      iVar1 = (param_2 & 1 | 2) << ((char)((param_2 & 0xff) >> 1) + 0xbU & 0x1f);
    }
    local_17 = (undefined1)iVar1;
    local_16 = (undefined1)((uint)iVar1 >> 8);
    local_14 = (undefined1)((uint)iVar1 >> 0x18);
    local_18 = 4;
    local_15 = (undefined1)((uint)iVar1 >> 0x10);
    FUN_1400a0a84(param_1,&local_18,5,param_3);
  }
  __security_check_cookie(local_10 ^ (ulonglong)auStack_38);
  return;
}


// ==== FUN_1400a0df4 @ 1400a0df4  undefined FUN_1400a0df4(longlong param_1)

void FUN_1400a0df4(longlong param_1)

{
  *(undefined4 *)(param_1 + 0x90) = 0;
  *(undefined4 *)(param_1 + 0x98) = 1;
  *(undefined4 *)(param_1 + 0x9c) = 1;
  *(undefined4 *)(param_1 + 0xa0) = 1;
  FUN_1400a047c(param_1);
  return;
}


// ==== FUN_1400a0f6c @ 1400a0f6c  undefined FUN_1400a0f6c(longlong param_1, void * param_2, size_t param_3)

void FUN_1400a0f6c(longlong param_1,void *param_2,size_t param_3)

{
  memcpy((void *)(*(longlong *)(param_1 + 0x18) + *(longlong *)(param_1 + 0x30)),param_2,param_3);
  *(longlong *)(param_1 + 0x30) = *(longlong *)(param_1 + 0x30) + param_3;
  if ((*(int *)(param_1 + 0x44) == 0) &&
     ((uint)(*(int *)(param_1 + 0xc) - *(int *)(param_1 + 0x40)) <= param_3)) {
    *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0xc);
  }
  *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + (int)param_3;
  return;
}


// ==== FUN_1400a0fb4 @ 1400a0fb4  undefined8 FUN_1400a0fb4(uint * param_1, longlong param_2, byte * param_3, longlong * param_4, int param_5, int * param_6)

undefined8
FUN_1400a0fb4(uint *param_1,longlong param_2,byte *param_3,longlong *param_4,int param_5,
             int *param_6)

{
  byte bVar1;
  longlong lVar2;
  longlong lVar3;
  int *piVar4;
  bool bVar5;
  undefined7 extraout_var;
  uint uVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  uint uVar10;
  
  piVar4 = param_6;
  lVar2 = *param_4;
  *param_4 = 0;
  *param_6 = 0;
  uVar10 = param_1[0x24];
  do {
    if (uVar10 == 8) {
      *piVar4 = 1;
      return 0;
    }
    uVar10 = param_1[0x24];
    lVar3 = *(longlong *)(param_1 + 0xc);
    if (uVar10 == 9) {
      return 1;
    }
    if ((lVar3 == param_2) && (param_5 == 0)) {
      *piVar4 = 2;
      return 0;
    }
    if ((uVar10 == 6) || (uVar10 == 7)) {
      piVar7 = (int *)(ulonglong)param_1[0x23];
      param_6 = (int *)(lVar2 - *param_4);
      piVar8 = (int *)(param_2 - lVar3);
      piVar9 = piVar8;
      if (piVar7 <= piVar8) {
        piVar9 = piVar7;
      }
      bVar1 = (byte)param_1[0x25];
      if ((char)bVar1 < '\0') {
        if (uVar10 == 6) {
          uVar10 = (uint)((bVar1 >> 5 & 3) == 3);
          if (((uVar10 == 0) && (param_1[0x26] != 0)) ||
             ((uVar6 = (uint)((bVar1 >> 5 & 3) != 0), uVar6 == 0 && (param_1[0x27] != 0))))
          goto LAB_1400a11c7;
          FUN_1400a0450((longlong)param_1,uVar10,uVar6);
          param_1[0x26] = 0;
          param_1[0x27] = 0;
          param_1[0x24] = 7;
        }
        if ((int *)(ulonglong)param_1[0x22] < param_6) {
          param_6 = (int *)(ulonglong)param_1[0x22];
        }
        bVar5 = FUN_1400a04ec((char *)param_1,lVar3 + (longlong)piVar9,param_3,(ulonglong *)&param_6
                              ,(uint)(piVar7 <= piVar8),piVar4);
        *param_4 = *param_4 + (longlong)param_6;
        param_1[0x22] = param_1[0x22] - (int)param_6;
        param_3 = param_3 + (longlong)param_6;
        param_1[0x23] = param_1[0x23] - (int)(*(longlong *)(param_1 + 0xc) - lVar3);
        if ((int)CONCAT71(extraout_var,bVar5) != 0) {
          return CONCAT71(extraout_var,bVar5);
        }
        if (*piVar4 == 3) {
          return 0;
        }
        if ((param_6 == (int *)0x0) && (*(longlong *)(param_1 + 0xc) - lVar3 == 0)) {
          if ((*piVar4 != 4) || ((param_1[0x23] != 0 || (param_1[0x22] != 0)))) goto LAB_1400a11c7;
          param_1[0x24] = 0;
        }
        if (*piVar4 == 4) {
          *piVar4 = 2;
        }
      }
      else {
        if (*param_4 == lVar2) goto LAB_1400a141b;
        if (uVar10 == 6) {
          if ((bVar1 == 1) == 0) {
            if (param_1[0x26] != 0) goto LAB_1400a11c7;
          }
          else {
            param_1[0x27] = 1;
            param_1[0x28] = 1;
          }
          param_1[0x26] = 0;
          FUN_1400a0450((longlong)param_1,(uint)(bVar1 == 1),0);
        }
        piVar7 = param_6;
        if (piVar9 < param_6) {
          piVar7 = piVar9;
        }
        if (piVar7 == (int *)0x0) goto LAB_1400a11c7;
        param_6 = piVar7;
        memcpy((void *)(*(longlong *)(param_1 + 6) + *(longlong *)(param_1 + 0xc)),param_3,
               (size_t)piVar7);
        *(longlong *)(param_1 + 0xc) = *(longlong *)(param_1 + 0xc) + (longlong)piVar7;
        if ((param_1[0x11] == 0) && ((int *)(ulonglong)(param_1[3] - param_1[0x10]) <= piVar7)) {
          param_1[0x11] = param_1[3];
        }
        param_1[0x10] = param_1[0x10] + (int)piVar7;
        *param_4 = *param_4 + (longlong)param_6;
        param_1[0x23] = param_1[0x23] - (int)param_6;
        param_3 = param_3 + (longlong)param_6;
        param_1[0x24] = -(uint)(param_1[0x23] != 0) & 7;
      }
    }
    else {
      if (*param_4 == lVar2) {
LAB_1400a141b:
        *piVar4 = 3;
        return 0;
      }
      *param_4 = *param_4 + 1;
      uVar10 = param_1[0x24];
      bVar1 = *param_3;
      if (uVar10 == 0) {
        *(byte *)(param_1 + 0x25) = bVar1;
        if (bVar1 == 0) {
          uVar10 = 8;
        }
        else {
          if ((char)bVar1 < '\0') {
            param_1[0x23] = (bVar1 & 0x1f) << 0x10;
          }
          else {
            if (2 < (bVar1 & 0x7f)) goto LAB_1400a1188;
            param_1[0x23] = 0;
          }
          uVar10 = 1;
        }
      }
      else if (uVar10 == 1) {
        param_1[0x23] = param_1[0x23] | (uint)bVar1 << 8;
        uVar10 = 2;
      }
      else if (uVar10 == 2) {
        param_1[0x23] = ((uint)bVar1 | param_1[0x23]) + 1;
        uVar10 = -(uint)((param_1[0x25] & 0x80) != 0) & 0xfffffffd;
LAB_1400a1154:
        uVar10 = uVar10 + 6;
      }
      else if (uVar10 == 3) {
        param_1[0x22] = (uint)bVar1 << 8;
        uVar10 = 4;
      }
      else if (uVar10 == 4) {
        param_1[0x22] = ((uint)bVar1 | param_1[0x22]) + 1;
        if (((byte)param_1[0x25] & 0x60) < 0x40) {
          uVar10 = -(uint)(param_1[0x28] != 0) & 3;
          goto LAB_1400a1154;
        }
        uVar10 = 5;
      }
      else {
        if ((uVar10 == 5) && (bVar1 < 0xe1)) {
          uVar10 = bVar1 / 9;
          uVar6 = (uint)bVar1 % 9;
          param_1[2] = uVar10 / 5;
          uVar10 = uVar10 % 5;
          if (uVar10 + uVar6 < 5) {
            *param_1 = uVar6;
            param_1[1] = uVar10;
            param_1[0x28] = 0;
            uVar10 = 6;
            goto LAB_1400a11ac;
          }
        }
LAB_1400a1188:
        uVar10 = 9;
      }
LAB_1400a11ac:
      param_3 = param_3 + 1;
      param_1[0x24] = uVar10;
      if ((lVar3 == param_2) && (uVar10 != 8)) {
LAB_1400a11c7:
        param_1[0x24] = 9;
        return 1;
      }
    }
    uVar10 = param_1[0x24];
  } while( true );
}


// ==== FUN_1400a1444 @ 1400a1444  ulonglong FUN_1400a1444(uint * param_1, void * param_2, ulonglong * param_3, byte * param_4, longlong * param_5, int param_6, int * param_7)

ulonglong FUN_1400a1444(uint *param_1,void *param_2,ulonglong *param_3,byte *param_4,
                       longlong *param_5,int param_6,int *param_7)

{
  longlong lVar1;
  int iVar2;
  ulonglong uVar3;
  longlong lVar4;
  ulonglong uVar5;
  size_t _Size;
  byte *pbVar6;
  void *local_res10;
  byte *local_res20;
  
  uVar5 = *param_3;
  pbVar6 = (byte *)*param_5;
  *param_3 = 0;
  *param_5 = 0;
  local_res10 = param_2;
  while( true ) {
    lVar4 = *(longlong *)(param_1 + 0xe);
    if (*(longlong *)(param_1 + 0xc) == lVar4) {
      param_1[0xc] = 0;
      param_1[0xd] = 0;
    }
    lVar1 = *(longlong *)(param_1 + 0xc);
    if ((ulonglong)(lVar4 - lVar1) < uVar5) {
      iVar2 = 0;
    }
    else {
      lVar4 = lVar1 + uVar5;
      iVar2 = param_6;
    }
    local_res20 = pbVar6;
    uVar3 = FUN_1400a0fb4(param_1,lVar4,param_4,(longlong *)&local_res20,iVar2,param_7);
    *param_5 = (longlong)(local_res20 + *param_5);
    pbVar6 = pbVar6 + -(longlong)local_res20;
    _Size = *(longlong *)(param_1 + 0xc) - lVar1;
    local_res20 = param_4 + (longlong)local_res20;
    memcpy(local_res10,(void *)(lVar1 + *(longlong *)(param_1 + 6)),_Size);
    *param_3 = *param_3 + _Size;
    local_res10 = (void *)((longlong)local_res10 + _Size);
    uVar5 = uVar5 - _Size;
    if ((int)uVar3 != 0) break;
    if ((_Size == 0) || (param_4 = local_res20, uVar5 == 0)) {
      return 0;
    }
  }
  return uVar3 & 0xffffffff;
}


// ==== FUN_1400a1558 @ 1400a1558  undefined FUN_1400a1558(undefined8 param_1, longlong * param_2, byte * param_3, longlong * param_4, undefined1 param_5, int param_6, int * param_7, undefined8 * param_8)

void FUN_1400a1558(undefined8 param_1,longlong *param_2,byte *param_3,longlong *param_4,
                  undefined1 param_5,int param_6,int *param_7,undefined8 *param_8)

{
  longlong lVar1;
  longlong lVar2;
  int iVar3;
  undefined1 auStackY_138 [32];
  uint local_108 [4];
  undefined8 local_f8;
  undefined8 local_f0;
  longlong local_d8;
  longlong local_d0;
  ulonglong local_58;
  
  local_58 = DAT_140103510 ^ (ulonglong)auStackY_138;
  lVar1 = *param_2;
  lVar2 = *param_4;
  *param_4 = 0;
  *param_2 = 0;
  *param_7 = 0;
  local_f0 = 0;
  local_f8 = 0;
  iVar3 = FUN_1400a0ce4((undefined8 *)local_108,
                        (uint)CONCAT71((int7)((ulonglong)param_2 >> 8),param_5),param_8);
  if (iVar3 == 0) {
    local_f0 = param_1;
    local_d0 = lVar1;
    FUN_1400a0df4((longlong)local_108);
    *param_4 = lVar2;
    FUN_1400a0fb4(local_108,lVar1,param_3,param_4,param_6,param_7);
    *param_2 = local_d8;
    FUN_1400a08d0((longlong)local_108,(longlong)param_8);
  }
  __security_check_cookie(local_58 ^ (ulonglong)auStackY_138);
  return;
}


// ==== FUN_1400a1654 @ 1400a1654  longlong FUN_1400a1654(longlong param_1, ulonglong param_2, int param_3, uint * param_4, int param_5)

longlong FUN_1400a1654(longlong param_1,ulonglong param_2,int param_3,uint *param_4,int param_5)

{
  byte *pbVar1;
  int iVar2;
  byte *pbVar3;
  sbyte sVar4;
  uint uVar5;
  byte *pbVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  longlong lVar10;
  longlong lVar11;
  uint uVar12;
  
  lVar11 = 0;
  uVar8 = *param_4 & 7;
  if (param_2 < 5) {
    lVar10 = 0;
  }
  else {
    pbVar1 = (byte *)(param_1 + -4 + param_2);
    while( true ) {
      for (pbVar6 = (byte *)(lVar11 + param_1); (pbVar6 < pbVar1 && ((*pbVar6 & 0xfe) != 0xe8));
          pbVar6 = pbVar6 + 1) {
      }
      lVar10 = (longlong)pbVar6 - param_1;
      pbVar3 = pbVar6 + (-param_1 - lVar11);
      uVar12 = 0;
      if (pbVar1 <= pbVar6) break;
      uVar9 = uVar12;
      if ((((pbVar3 < (byte *)0x3) && (uVar9 = uVar8 >> ((byte)pbVar3 & 0x1f), uVar9 != 0)) &&
          ((4 < uVar9 || ((uVar9 == 3 || ((pbVar6[(uVar9 >> 1) + 1] + 1 & 0xfe) == 0)))))) ||
         ((pbVar6[4] + 1 & 0xfe) != 0)) {
        uVar8 = (uVar9 | 8) >> 1;
        lVar11 = lVar10 + 1;
      }
      else {
        iVar7 = (int)lVar10 + 5 + param_3;
        lVar11 = lVar10 + 5;
        iVar2 = iVar7;
        if (param_5 == 0) {
          iVar2 = -iVar7;
        }
        uVar5 = CONCAT31(CONCAT21(CONCAT11(pbVar6[4],pbVar6[3]),pbVar6[2]),pbVar6[1]) + iVar2;
        uVar8 = uVar9;
        if ((uVar9 != 0) &&
           (sVar4 = (sbyte)((uVar9 & 6) << 2), uVar8 = uVar12, ((uVar5 >> sVar4) + 1 & 0xfe) == 0))
        {
          uVar5 = uVar5 ^ (0x100 << sVar4) - 1U;
          if (param_5 == 0) {
            uVar5 = uVar5 - iVar7;
          }
          else {
            uVar5 = uVar5 + iVar7;
          }
        }
        pbVar6[1] = (byte)uVar5;
        pbVar6[2] = (byte)(uVar5 >> 8);
        pbVar6[3] = (byte)(uVar5 >> 0x10);
        pbVar6[4] = -((byte)(uVar5 >> 0x18) & 1);
      }
    }
    uVar8 = uVar8 >> ((byte)pbVar3 & 0x1f);
    if ((byte *)0x2 < pbVar3) {
      uVar8 = uVar12;
    }
    *param_4 = uVar8;
  }
  return lVar10;
}


// ==== FUN_1400a17cc @ 1400a17cc  ulonglong FUN_1400a17cc(longlong param_1, ulonglong param_2, int param_3, int param_4)

ulonglong FUN_1400a17cc(longlong param_1,ulonglong param_2,int param_3,int param_4)

{
  undefined1 *puVar1;
  int iVar2;
  uint uVar3;
  ulonglong uVar4;
  
  if (param_2 < 4) {
    uVar4 = 0;
  }
  else {
    uVar4 = 0;
    do {
      puVar1 = (undefined1 *)(uVar4 + param_1);
      if (puVar1[3] == -0x15) {
        iVar2 = (uint)CONCAT21(CONCAT11(*(undefined1 *)(uVar4 + 2 + param_1),
                                        *(undefined1 *)(uVar4 + 1 + param_1)),*puVar1) * 4;
        if (param_4 == 0) {
          uVar3 = (iVar2 - (int)uVar4) - (param_3 + 8);
        }
        else {
          uVar3 = iVar2 + (int)uVar4 + param_3 + 8;
        }
        uVar3 = uVar3 >> 2;
        *puVar1 = (char)uVar3;
        *(char *)(uVar4 + 2 + param_1) = (char)(uVar3 >> 0x10);
        *(char *)(uVar4 + 1 + param_1) = (char)(uVar3 >> 8);
      }
      uVar4 = uVar4 + 4;
    } while (uVar4 <= param_2 - 4);
  }
  return uVar4;
}


// ==== FUN_1400a1860 @ 1400a1860  ulonglong FUN_1400a1860(longlong param_1, ulonglong param_2, int param_3, int param_4)

ulonglong FUN_1400a1860(longlong param_1,ulonglong param_2,int param_3,int param_4)

{
  int iVar1;
  ulonglong uVar2;
  uint uVar3;
  
  if (param_2 < 4) {
    uVar2 = 0;
  }
  else {
    uVar2 = 0;
    do {
      if (((*(byte *)(param_1 + 1 + uVar2) & 0xf8) == 0xf0) &&
         ((*(byte *)(uVar2 + 3 + param_1) & 0xf8) == 0xf8)) {
        iVar1 = ((((*(byte *)(param_1 + 1 + uVar2) & 7) << 8 | (uint)*(byte *)(uVar2 + param_1)) <<
                  3 | *(byte *)(uVar2 + 3 + param_1) & 7) << 8 |
                (uint)*(byte *)(uVar2 + 2 + param_1)) * 2;
        if (param_4 == 0) {
          uVar3 = (iVar1 - (int)uVar2) - (param_3 + 4);
        }
        else {
          uVar3 = iVar1 + (int)uVar2 + param_3 + 4;
        }
        *(char *)(uVar2 + 2 + param_1) = (char)(uVar3 >> 1);
        *(byte *)(uVar2 + 3 + param_1) = (byte)((uVar3 >> 1) >> 8) | 0xf8;
        *(byte *)(param_1 + 1 + uVar2) = (byte)(uVar3 >> 0x14) & 7 | 0xf0;
        *(char *)(uVar2 + param_1) = (char)(uVar3 >> 0xc);
        uVar2 = uVar2 + 2;
      }
      uVar2 = uVar2 + 2;
    } while (uVar2 <= param_2 - 4);
  }
  return uVar2;
}


// ==== FUN_1400a1930 @ 1400a1930  ulonglong FUN_1400a1930(longlong param_1, ulonglong param_2, int param_3, int param_4)

ulonglong FUN_1400a1930(longlong param_1,ulonglong param_2,int param_3,int param_4)

{
  ulonglong uVar1;
  uint uVar2;
  int iVar3;
  
  if (param_2 < 4) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0;
    do {
      if (((*(byte *)(uVar1 + param_1) & 0xfc) == 0x48) &&
         ((*(byte *)(uVar1 + 3 + param_1) & 3) == 1)) {
        uVar2 = (*(byte *)(uVar1 + param_1) & 3) << 0x18 |
                *(byte *)(uVar1 + 3 + param_1) & 0xfffffffc |
                (uint)CONCAT11(*(undefined1 *)(uVar1 + 1 + param_1),
                               *(undefined1 *)(uVar1 + 2 + param_1)) << 8;
        if (param_4 == 0) {
          iVar3 = (uVar2 - (int)uVar1) - param_3;
        }
        else {
          iVar3 = uVar2 + (int)uVar1 + param_3;
        }
        *(char *)(uVar1 + 1 + param_1) = (char)((uint)iVar3 >> 0x10);
        *(byte *)(uVar1 + 3 + param_1) = (byte)iVar3 | 1;
        *(byte *)(uVar1 + param_1) = (byte)((uint)iVar3 >> 0x18) & 3 | 0x48;
        *(char *)(uVar1 + 2 + param_1) = (char)((uint)iVar3 >> 8);
      }
      uVar1 = uVar1 + 4;
    } while (uVar1 <= param_2 - 4);
  }
  return uVar1;
}


// ==== FUN_1400a19fc @ 1400a19fc  uint FUN_1400a19fc(longlong param_1, ulonglong param_2, int param_3, int param_4)

uint FUN_1400a19fc(longlong param_1,ulonglong param_2,int param_3,int param_4)

{
  uint uVar1;
  longlong lVar2;
  byte bVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  if (param_2 < 4) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0;
    lVar2 = 0;
    do {
      if (((*(char *)(lVar2 + param_1) == '@') &&
          (bVar3 = *(byte *)(lVar2 + 1 + param_1), (bVar3 & 0xc0) == 0)) ||
         ((*(char *)(lVar2 + param_1) == '\x7f' &&
          (bVar3 = *(byte *)(lVar2 + 1 + param_1), (bVar3 & 0xc0) == 0xc0)))) {
        iVar4 = CONCAT31(CONCAT21(CONCAT11(*(undefined1 *)(lVar2 + param_1),bVar3),
                                  *(undefined1 *)(lVar2 + 2 + param_1)),
                         *(undefined1 *)(lVar2 + 3 + param_1)) * 4;
        if (param_4 == 0) {
          uVar5 = (iVar4 - uVar1) - param_3;
        }
        else {
          uVar5 = iVar4 + uVar1 + param_3;
        }
        uVar6 = uVar5 >> 2 & 0x3fffff;
        iVar4 = (-(uVar5 >> 0x18 & 1) & 0xff | 0x100) << 0x16;
        *(char *)(lVar2 + 3 + param_1) = (char)uVar6;
        *(char *)(lVar2 + param_1) = (char)((uint)iVar4 >> 0x18);
        *(byte *)(lVar2 + 1 + param_1) = (byte)((uint)iVar4 >> 0x10) | (byte)(uVar6 >> 0x10);
        *(char *)(lVar2 + 2 + param_1) = (char)(uVar6 >> 8);
      }
      uVar1 = uVar1 + 4;
      lVar2 = lVar2 + 4;
    } while ((ulonglong)uVar1 <= param_2 - 4);
  }
  return uVar1;
}


// ==== FUN_1400a1afc @ 1400a1afc  ulonglong FUN_1400a1afc(longlong param_1, ulonglong param_2, int param_3, int param_4)

ulonglong FUN_1400a1afc(longlong param_1,ulonglong param_2,int param_3,int param_4)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  uint uVar6;
  ulonglong uVar7;
  byte *pbVar8;
  ulonglong uVar9;
  byte *pbVar10;
  ulonglong uVar11;
  int iVar12;
  uint uVar13;
  
  if (param_2 < 0x10) {
    uVar7 = 0;
  }
  else {
    uVar7 = 0;
    do {
      uVar13 = 5;
      iVar12 = 0;
      bVar1 = (&DAT_1400d2448)[*(byte *)(uVar7 + param_1) & 0x1f];
      do {
        if ((bVar1 >> ((byte)iVar12 & 0x1f) & 1) != 0) {
          uVar9 = 0;
          bVar2 = (byte)uVar13 & 7;
          iVar5 = 0;
          pbVar8 = (byte *)((uVar13 >> 3) + uVar7 + param_1);
          pbVar10 = pbVar8;
          do {
            bVar4 = *pbVar10;
            pbVar10 = pbVar10 + 1;
            bVar3 = (byte)iVar5;
            iVar5 = iVar5 + 8;
            uVar9 = uVar9 + ((ulonglong)bVar4 << (bVar3 & 0x3f));
          } while (iVar5 < 0x30);
          uVar11 = uVar9 >> bVar2;
          if ((((byte)(uVar11 >> 0x25) & 0xf) == 5) && ((uVar11 & 0xe00) == 0)) {
            iVar5 = (((uint)(uVar11 >> 0x24) & 1) << 0x14 | (uint)(uVar11 >> 0xd) & 0xfffff) * 0x10;
            if (param_4 == 0) {
              uVar6 = (iVar5 - (int)uVar7) - param_3;
            }
            else {
              uVar6 = iVar5 + (int)uVar7 + param_3;
            }
            iVar5 = 0;
            do {
              bVar4 = (byte)iVar5;
              iVar5 = iVar5 + 8;
              *pbVar8 = (byte)(((((ulonglong)(uVar6 >> 4 & 0x100000) << 3 |
                                 (ulonglong)(uVar6 >> 4 & 0xfffff)) << 0xd |
                                uVar11 & 0xffffffee00001fff) << bVar2 |
                               (longlong)((1 << bVar2) + -1) & uVar9) >> (bVar4 & 0x3f));
              pbVar8 = pbVar8 + 1;
            } while (iVar5 < 0x30);
          }
        }
        iVar12 = iVar12 + 1;
        uVar13 = uVar13 + 0x29;
      } while (iVar12 < 3);
      uVar7 = uVar7 + 0x10;
    } while (uVar7 <= param_2 - 0x10);
  }
  return uVar7;
}


// ==== FUN_1400a1c7c @ 1400a1c7c  undefined FUN_1400a1c7c(void * param_1)

void FUN_1400a1c7c(void *param_1)

{
  memset(param_1,0,0x100);
  return;
}


// ==== FUN_1400a1ca8 @ 1400a1ca8  undefined FUN_1400a1ca8(void * param_1, uint param_2, longlong param_3, ulonglong param_4)

void FUN_1400a1ca8(void *param_1,uint param_2,longlong param_3,ulonglong param_4)

{
  char cVar1;
  char cVar2;
  ulonglong uVar3;
  uint uVar4;
  char *pcVar6;
  undefined1 auStack_158 [32];
  char local_138 [256];
  ulonglong local_38;
  ulonglong uVar5;
  
  local_38 = DAT_140103510 ^ (ulonglong)auStack_158;
  if (param_2 != 0) {
    memcpy(local_138,param_1,(ulonglong)param_2);
  }
  uVar3 = 0;
  uVar4 = 0;
  if (param_4 != 0) {
    do {
      uVar4 = 0;
      if (param_2 != 0) {
        pcVar6 = local_138;
        uVar5 = 0;
        do {
          uVar4 = (uint)uVar5;
          if (param_4 <= uVar3) goto LAB_1400a1d2f;
          cVar1 = *(char *)(param_3 + uVar3);
          uVar4 = uVar4 + 1;
          uVar5 = (ulonglong)uVar4;
          cVar2 = *pcVar6;
          *pcVar6 = cVar1;
          pcVar6 = pcVar6 + 1;
          *(char *)(param_3 + uVar3) = cVar1 - cVar2;
          uVar3 = uVar3 + 1;
        } while (uVar4 < param_2);
      }
    } while (uVar3 < param_4);
  }
LAB_1400a1d2f:
  if (uVar4 == param_2) {
    uVar4 = 0;
  }
  if (param_2 - uVar4 != 0) {
    memcpy(param_1,local_138 + (int)uVar4,(ulonglong)(param_2 - uVar4));
  }
  if (uVar4 != 0) {
    memcpy((void *)(((longlong)(int)param_2 - (longlong)(int)uVar4) + (longlong)param_1),local_138,
           (ulonglong)uVar4);
  }
  __security_check_cookie(local_38 ^ (ulonglong)auStack_158);
  return;
}


// ==== FUN_1400a1d90 @ 1400a1d90  undefined FUN_1400a1d90(void * param_1, uint param_2, longlong param_3, ulonglong param_4)

void FUN_1400a1d90(void *param_1,uint param_2,longlong param_3,ulonglong param_4)

{
  char *pcVar1;
  ulonglong uVar2;
  char *pcVar3;
  uint uVar4;
  undefined1 auStack_158 [32];
  char local_138 [256];
  ulonglong local_38;
  ulonglong uVar5;
  
  local_38 = DAT_140103510 ^ (ulonglong)auStack_158;
  if (param_2 != 0) {
    memcpy(local_138,param_1,(ulonglong)param_2);
  }
  uVar2 = 0;
  uVar4 = 0;
  if (param_4 != 0) {
    do {
      uVar4 = 0;
      if (param_2 != 0) {
        pcVar3 = local_138;
        uVar5 = 0;
        do {
          uVar4 = (uint)uVar5;
          if (param_4 <= uVar2) goto LAB_1400a1e13;
          uVar4 = uVar4 + 1;
          uVar5 = (ulonglong)uVar4;
          *(char *)(param_3 + uVar2) = *(char *)(param_3 + uVar2) + *pcVar3;
          pcVar1 = (char *)(param_3 + uVar2);
          uVar2 = uVar2 + 1;
          *pcVar3 = *pcVar1;
          pcVar3 = pcVar3 + 1;
        } while (uVar4 < param_2);
      }
    } while (uVar2 < param_4);
  }
LAB_1400a1e13:
  if (uVar4 == param_2) {
    uVar4 = 0;
  }
  if (param_2 - uVar4 != 0) {
    memcpy(param_1,local_138 + (int)uVar4,(ulonglong)(param_2 - uVar4));
  }
  if (uVar4 != 0) {
    memcpy((void *)(((longlong)(int)param_2 - (longlong)(int)uVar4) + (longlong)param_1),local_138,
           (ulonglong)uVar4);
  }
  __security_check_cookie(local_38 ^ (ulonglong)auStack_158);
  return;
}


// ==== FUN_1400a1e74 @ 1400a1e74  undefined FUN_1400a1e74(longlong param_1)

void FUN_1400a1e74(longlong param_1)

{
  longlong lVar1;
  undefined2 *puVar2;
  
  *(undefined4 *)(param_1 + 0x50) = 9;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined1 *)(param_1 + 0x5b) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  puVar2 = (undefined2 *)(param_1 + 100);
  for (lVar1 = 0x102; lVar1 != 0; lVar1 = lVar1 + -1) {
    *puVar2 = 0x400;
    puVar2 = puVar2 + 1;
  }
  return;
}


// ==== FUN_1400a1ea8 @ 1400a1ea8  undefined8 FUN_1400a1ea8(longlong * param_1)

undefined8 FUN_1400a1ea8(longlong *param_1)

{
  byte *pbVar1;
  byte bVar2;
  ushort uVar3;
  uint uVar4;
  undefined1 *puVar5;
  uint *puVar6;
  int *piVar7;
  uint uVar8;
  ulonglong uVar9;
  byte *pbVar10;
  ulonglong uVar11;
  int iVar12;
  byte *pbVar13;
  longlong lVar14;
  byte bVar15;
  ulonglong uVar16;
  
  uVar11 = 0;
  uVar8 = *(uint *)((longlong)param_1 + 0x5c);
  if (uVar8 < 6) {
    *(undefined4 *)(param_1 + 10) = 9;
    while (uVar8 != 5) {
      if ((*(int *)((longlong)param_1 + 0x5c) == 1) && ((int)param_1[0xc] != 0)) {
        return 1;
      }
      pbVar10 = (byte *)param_1[3];
      if (pbVar10 == (byte *)param_1[7]) goto LAB_1400a1f00;
      bVar2 = *pbVar10;
      param_1[3] = (longlong)(pbVar10 + 1);
      uVar8 = *(int *)((longlong)param_1 + 0x5c) + 1;
      *(uint *)(param_1 + 0xc) = (int)param_1[0xc] << 8 | (uint)bVar2;
      *(uint *)((longlong)param_1 + 0x5c) = uVar8;
    }
    if ((int)param_1[0xc] == -1) {
      return 1;
    }
    *(undefined4 *)((longlong)param_1 + 0x5c) = 0xffffffff;
  }
  else if (3 < *(uint *)(param_1 + 10)) {
    uVar8 = *(uint *)(param_1 + 10);
    while (uVar8 < 8) {
      puVar5 = (undefined1 *)param_1[8];
      if (puVar5 == (undefined1 *)param_1[9]) {
        return 0;
      }
      *puVar5 = *(undefined1 *)((ulonglong)((int)param_1[10] - 4) + 0x58 + (longlong)param_1);
      *(int *)(param_1 + 10) = (int)param_1[10] + 1;
      param_1[8] = (longlong)(puVar5 + 1);
      uVar8 = *(uint *)(param_1 + 10);
    }
  }
  do {
    while (((int)param_1[10] != 1 && ((int)param_1[10] != 2))) {
      if (*(uint *)((longlong)param_1 + 0x5c) < 0x1000000) {
        pbVar10 = (byte *)param_1[3];
        if (pbVar10 == (byte *)param_1[7]) {
LAB_1400a1f00:
          *(undefined4 *)(param_1 + 10) = 3;
          return 0;
        }
        *(uint *)((longlong)param_1 + 0x5c) = *(uint *)((longlong)param_1 + 0x5c) << 8;
        bVar2 = *pbVar10;
        param_1[3] = (longlong)(pbVar10 + 1);
        *(uint *)(param_1 + 0xc) = (int)param_1[0xc] << 8 | (uint)bVar2;
      }
      pbVar10 = (byte *)*param_1;
      uVar9 = param_1[4] - (longlong)pbVar10;
      if (uVar9 == 0) {
        *(undefined4 *)(param_1 + 10) = 0;
        return 0;
      }
      pbVar13 = (byte *)param_1[8];
      uVar16 = param_1[9] - (longlong)pbVar13;
      if ((uVar16 < uVar9) && (uVar9 = uVar16, uVar16 == 0)) {
        *(undefined4 *)(param_1 + 10) = 8;
        return 0;
      }
      pbVar1 = pbVar10 + uVar9;
      if ((*(char *)((longlong)param_1 + 0x5b) == '\x0f') && ((*pbVar10 & 0xf0) == 0x80)) {
        *pbVar13 = *pbVar10;
      }
      else {
        do {
          while( true ) {
            bVar2 = *pbVar10;
            *pbVar13 = bVar2;
            if (bVar2 == 0xf) break;
            if ((bVar2 & 0xfe) == 0xe8) goto LAB_1400a2011;
            pbVar10 = pbVar10 + 1;
            pbVar13 = pbVar13 + 1;
            if (pbVar10 == pbVar1) goto LAB_1400a2011;
          }
          pbVar10 = pbVar10 + 1;
          pbVar13 = pbVar13 + 1;
          if (pbVar10 == pbVar1) goto LAB_1400a2011;
        } while ((*pbVar10 & 0xf0) != 0x80);
        *pbVar13 = *pbVar10;
      }
LAB_1400a2011:
      lVar14 = (longlong)pbVar10 - *param_1;
      if (pbVar10 == pbVar1) {
        bVar2 = pbVar10[-1];
        *(int *)((longlong)param_1 + 0x54) = *(int *)((longlong)param_1 + 0x54) + (int)lVar14;
        param_1[8] = param_1[8] + lVar14;
        *param_1 = (longlong)pbVar10;
        *(byte *)((longlong)param_1 + 0x5b) = bVar2;
        *(uint *)(param_1 + 10) = -(uint)(pbVar10 != (byte *)param_1[4]) & 8;
        return 0;
      }
      bVar2 = *pbVar10;
      if (lVar14 == 0) {
        bVar15 = *(byte *)((longlong)param_1 + 0x5b);
      }
      else {
        bVar15 = pbVar10[-1];
      }
      *(int *)((longlong)param_1 + 0x54) = *(int *)((longlong)param_1 + 0x54) + (int)(lVar14 + 1);
      param_1[8] = param_1[8] + lVar14 + 1;
      *param_1 = (longlong)(pbVar10 + 1);
      *(byte *)((longlong)param_1 + 0x5b) = bVar2;
      uVar9 = (ulonglong)(bVar2 == 0xe9);
      if (bVar2 == 0xe8) {
        uVar9 = (ulonglong)(bVar15 + 2);
      }
      uVar3 = *(ushort *)((longlong)param_1 + uVar9 * 2 + 100);
      uVar8 = (*(uint *)((longlong)param_1 + 0x5c) >> 0xb) * (uint)uVar3;
      if (uVar8 <= *(uint *)(param_1 + 0xc)) {
        *(uint *)((longlong)param_1 + 0x5c) = *(uint *)((longlong)param_1 + 0x5c) - uVar8;
        *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) - uVar8;
        *(ushort *)((longlong)param_1 + uVar9 * 2 + 100) = uVar3 - (uVar3 >> 5);
        goto LAB_1400a20be;
      }
      *(uint *)((longlong)param_1 + 0x5c) = uVar8;
      *(ushort *)((longlong)param_1 + uVar9 * 2 + 100) = (short)(0x800 - uVar3 >> 5) + uVar3;
    }
    *(undefined4 *)(param_1 + 10) = 9;
LAB_1400a20be:
    uVar8 = (*(char *)((longlong)param_1 + 0x5b) != -0x18) + 1;
    puVar6 = (uint *)param_1[uVar8];
    if (puVar6 == (uint *)param_1[(ulonglong)uVar8 + 4]) goto LAB_1400a2173;
    uVar4 = *puVar6;
    param_1[uVar8] = (longlong)(puVar6 + 1);
    *(int *)((longlong)param_1 + 0x54) = *(int *)((longlong)param_1 + 0x54) + 4;
    piVar7 = (int *)param_1[8];
    iVar12 = (uVar4 >> 0x18 | (uVar4 & 0xff0000) >> 8 | (uVar4 & 0xff00) << 8 | uVar4 << 0x18) -
             *(int *)((longlong)param_1 + 0x54);
    uVar9 = param_1[9] - (longlong)piVar7;
    if (uVar9 < 4) {
      *(int *)(param_1 + 0xb) = iVar12;
      if (uVar9 != 0) {
        do {
          *(undefined1 *)(uVar11 + (longlong)piVar7) =
               *(undefined1 *)((longlong)param_1 + uVar11 + 0x58);
          uVar11 = uVar11 + 1;
        } while (uVar11 < uVar9);
      }
      param_1[8] = uVar9 + (longlong)piVar7;
      uVar8 = (int)uVar9 + 4;
LAB_1400a2173:
      *(uint *)(param_1 + 10) = uVar8;
      if ((*(uint *)((longlong)param_1 + 0x5c) < 0x1000000) &&
         (pbVar10 = (byte *)param_1[3], pbVar10 != (byte *)param_1[7])) {
        *(uint *)((longlong)param_1 + 0x5c) = *(uint *)((longlong)param_1 + 0x5c) << 8;
        bVar2 = *pbVar10;
        param_1[3] = (longlong)(pbVar10 + 1);
        *(uint *)(param_1 + 0xc) = (int)param_1[0xc] << 8 | (uint)bVar2;
      }
      return 0;
    }
    *piVar7 = iVar12;
    param_1[8] = (longlong)(piVar7 + 1);
    *(char *)((longlong)param_1 + 0x5b) = (char)((uint)iVar12 >> 0x18);
  } while( true );
}


// ==== FUN_1400a21b0 @ 1400a21b0  ulonglong FUN_1400a21b0(undefined8 * param_1, uint param_2)

ulonglong FUN_1400a21b0(undefined8 *param_1,uint param_2)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  undefined4 extraout_var;
  ulonglong uVar4;
  ulonglong local_28;
  undefined8 local_20;
  uint local_18;
  undefined4 local_14;
  uint local_10;
  
  local_10 = FUN_140097280(param_2);
  if (local_10 < 6) {
    switch(local_10) {
    case 0:
      uVar4 = FUN_14007caf0(param_1,&local_28);
      if ((uVar4 & 0xff) == 0) {
        uVar4 = 0;
      }
      else {
        uVar4 = 1;
      }
      break;
    case 1:
      cVar2 = FUN_1400a3640(param_1,&local_20);
      if (cVar2 == '\0') {
        uVar4 = 0;
      }
      else {
        uVar4 = 1;
      }
      break;
    case 2:
      uVar4 = FUN_140097710(param_1,&local_18);
      if ((uVar4 & 0xff) == 0) {
        uVar4 = 0;
      }
      else {
        uVar4 = FUN_14007ab80(param_1,local_18);
        if ((uVar4 & 0xff) == 0) {
          uVar4 = 0;
        }
        else {
          uVar4 = 1;
        }
      }
      break;
    case 3:
      uVar3 = FUN_1400a36b0((longlong)param_1);
      if ((uVar3 & 0xff) == 0) {
        uVar4 = 0;
      }
      else {
        uVar4 = FUN_1400a2600(param_1);
        if ((uVar4 & 0xff) == 0) {
          uVar4 = 0;
        }
        else {
          FUN_1400a3700((longlong)param_1);
          uVar3 = FUN_140097290(param_2);
          uVar3 = FUN_1400a3730(uVar3,4);
          bVar1 = FUN_1400a3670((longlong)param_1,uVar3);
          if (bVar1) {
            uVar4 = 1;
          }
          else {
            uVar4 = 0;
          }
        }
      }
      break;
    case 4:
      uVar4 = (ulonglong)
              (IMAGE_DOS_HEADER_140000000.e_magic +
              (&switchD_1400a21eb::switchdataD_1400a2304)[(int)local_10]) & 0xffffffffffffff00;
      break;
    case 5:
      cVar2 = FUN_1400a3610(param_1,&local_14);
      if (cVar2 == '\0') {
        uVar4 = 0;
      }
      else {
        uVar4 = 1;
      }
    }
  }
  else {
    uVar4 = CONCAT44(extraout_var,local_10) & 0xffffffffffffff00;
  }
  return uVar4;
}


// ==== FUN_1400a2330 @ 1400a2330  undefined FUN_1400a2330(undefined8 * param_1, uint param_2, undefined8 * param_3)

void FUN_1400a2330(undefined8 *param_1,uint param_2,undefined8 *param_3)

{
  char cVar1;
  uint uVar2;
  ulonglong uVar3;
  undefined1 auStack_98 [32];
  ulonglong local_78;
  undefined8 local_70;
  uint local_68 [4];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_58 [40];
  undefined4 local_30;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined8 local_28;
  uint local_20;
  ulonglong local_18;
  
  local_28 = 0xfffffffffffffffe;
  local_18 = DAT_140103510 ^ (ulonglong)auStack_98;
  local_20 = FUN_140097280(param_2);
  switch(local_20) {
  case 0:
    uVar3 = FUN_14007caf0(param_1,&local_78);
    if ((uVar3 & 0xff) != 0) {
      FUN_14007c100(param_3,param_2);
      FUN_14007c220(param_3,local_78);
    }
    break;
  case 1:
    cVar1 = FUN_1400a3640(param_1,&local_70);
    if (cVar1 != '\0') {
      FUN_14007c100(param_3,param_2);
      FUN_14007c030(param_3,local_70);
    }
    break;
  case 2:
    uVar3 = FUN_140097710(param_1,local_68);
    if ((uVar3 & 0xff) != 0) {
      FUN_14007c100(param_3,param_2);
      FUN_14007c100(param_3,local_68[0]);
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_58);
      uVar3 = FUN_14007adf0(param_1,local_58,local_68[0]);
      if ((uVar3 & 0xff) == 0) {
        local_2c = 0;
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_58);
      }
      else {
        FUN_1400a3750(param_3,local_58);
        local_2b = 1;
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_58);
      }
    }
    break;
  case 3:
    FUN_14007c100(param_3,param_2);
    uVar2 = FUN_1400a36b0((longlong)param_1);
    if (((uVar2 & 0xff) != 0) && (uVar3 = FUN_1400a2670(param_1,param_3), (uVar3 & 0xff) != 0)) {
      FUN_1400a3700((longlong)param_1);
      uVar2 = FUN_140097290(param_2);
      uVar2 = FUN_1400a3730(uVar2,4);
      FUN_1400a3670((longlong)param_1,uVar2);
    }
    break;
  case 4:
    break;
  case 5:
    cVar1 = FUN_1400a3610(param_1,&local_30);
    if (cVar1 != '\0') {
      FUN_14007c100(param_3,param_2);
      FUN_14007bf80(param_3,local_30);
    }
  }
  __security_check_cookie(local_18 ^ (ulonglong)auStack_98);
  return;
}


// ==== FUN_1400a2600 @ 1400a2600  undefined8 FUN_1400a2600(undefined8 * param_1)

undefined8 FUN_1400a2600(undefined8 *param_1)

{
  uint uVar1;
  uint uVar2;
  undefined4 extraout_var;
  undefined4 extraout_var_00;
  ulonglong uVar3;
  
  while( true ) {
    uVar1 = FUN_1400a3790(param_1);
    if (uVar1 == 0) {
      return CONCAT71((int7)(CONCAT44(extraout_var,uVar1) >> 8),1);
    }
    uVar2 = FUN_140097280(uVar1);
    if (uVar2 == 4) break;
    uVar3 = FUN_1400a21b0(param_1,uVar1);
    if ((uVar3 & 0xff) == 0) {
      return 0;
    }
  }
  return CONCAT71((int7)(CONCAT44(extraout_var_00,uVar2) >> 8),1);
}


// ==== FUN_1400a2670 @ 1400a2670  undefined8 FUN_1400a2670(undefined8 * param_1, undefined8 * param_2)

undefined8 FUN_1400a2670(undefined8 *param_1,undefined8 *param_2)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  undefined4 extraout_var;
  undefined8 uVar4;
  
  while( true ) {
    uVar2 = FUN_1400a3790(param_1);
    if (uVar2 == 0) {
      return CONCAT71((int7)(CONCAT44(extraout_var,uVar2) >> 8),1);
    }
    uVar3 = FUN_140097280(uVar2);
    if (uVar3 == 4) break;
    cVar1 = FUN_1400a2330(param_1,uVar2,param_2);
    if (cVar1 == '\0') {
      return 0;
    }
  }
  uVar4 = FUN_14007c100(param_2,uVar2);
  return CONCAT71((int7)((ulonglong)uVar4 >> 8),1);
}


// ==== FUN_1400a26f0 @ 1400a26f0  undefined FUN_1400a26f0(undefined8 param_1, undefined8 * param_2, uint param_3)

void FUN_1400a26f0(undefined8 param_1,undefined8 *param_2,uint param_3)

{
  FUN_1400a21b0(param_2,param_3);
  return;
}


// ==== FUN_1400a2720 @ 1400a2720  undefined FUN_1400a2720(undefined8 param_1, undefined8 * param_2)

void FUN_1400a2720(undefined8 param_1,undefined8 *param_2)

{
  FUN_1400a2600(param_2);
  return;
}


// ==== FUN_1400a2770 @ 1400a2770  undefined FUN_1400a2770(longlong param_1, undefined8 * param_2, uint param_3)

void FUN_1400a2770(longlong param_1,undefined8 *param_2,uint param_3)

{
  FUN_1400a2330(param_2,param_3,*(undefined8 **)(param_1 + 8));
  return;
}


// ==== FUN_1400a27b0 @ 1400a27b0  undefined FUN_1400a27b0(longlong param_1, undefined8 * param_2)

void FUN_1400a27b0(longlong param_1,undefined8 *param_2)

{
  FUN_1400a2670(param_2,*(undefined8 **)(param_1 + 8));
  return;
}


// ==== FUN_1400a27e0 @ 1400a27e0  undefined FUN_1400a27e0(longlong param_1, uint param_2, int param_3)

void FUN_1400a27e0(longlong param_1,uint param_2,int param_3)

{
  FUN_14007c100(*(undefined8 **)(param_1 + 8),param_2);
  FUN_14007c220(*(undefined8 **)(param_1 + 8),(longlong)param_3);
  return;
}


// ==== FUN_1400a2830 @ 1400a2830  undefined8 FUN_1400a2830(undefined8 * param_1, undefined * param_2, longlong * param_3)

undefined8 FUN_1400a2830(undefined8 *param_1,undefined *param_2,longlong *param_3)

{
  char cVar1;
  int iVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  uint local_18;
  int local_14;
  uint local_10 [4];
  
  uVar3 = FUN_140097710(param_1,&local_18);
  if ((uVar3 & 0xff) == 0) {
    uVar4 = 0;
  }
  else {
    local_14 = FUN_14007a8e0((longlong)param_1,local_18);
    while (iVar2 = FUN_14007a9c0((longlong)param_1), 0 < iVar2) {
      uVar3 = FUN_1400a3820(param_1,local_10);
      if ((uVar3 & 0xff) == 0) {
        return 0;
      }
      cVar1 = (*(code *)param_2)(local_10[0]);
      if (cVar1 != '\0') {
        FUN_1400a3c20(param_3,local_10);
      }
    }
    uVar4 = FUN_14007a980((longlong)param_1,local_14);
    uVar4 = CONCAT71((int7)((ulonglong)uVar4 >> 8),1);
  }
  return uVar4;
}


// ==== FUN_1400a28e0 @ 1400a28e0  undefined FUN_1400a28e0(int param_1, uint param_2, undefined8 * param_3)

void FUN_1400a28e0(int param_1,uint param_2,undefined8 *param_3)

{
  FUN_1400a3860(param_1,0,param_3);
  FUN_1400a38b0(param_2,param_3);
  return;
}


// ==== FUN_1400a2920 @ 1400a2920  undefined FUN_1400a2920(int param_1, ulonglong param_2, undefined8 * param_3)

void FUN_1400a2920(int param_1,ulonglong param_2,undefined8 *param_3)

{
  FUN_1400a3860(param_1,0,param_3);
  FUN_1400a3910(param_2,param_3);
  return;
}


// ==== FUN_1400a2960 @ 1400a2960  undefined FUN_1400a2960(int param_1, uint param_2, undefined8 * param_3)

void FUN_1400a2960(int param_1,uint param_2,undefined8 *param_3)

{
  FUN_1400a3860(param_1,0,param_3);
  FUN_1400a3940(param_2,param_3);
  return;
}


// ==== FUN_1400a29a0 @ 1400a29a0  undefined FUN_1400a29a0(int param_1, ulonglong param_2, undefined8 * param_3)

void FUN_1400a29a0(int param_1,ulonglong param_2,undefined8 *param_3)

{
  FUN_1400a3860(param_1,0,param_3);
  FUN_1400a3960(param_2,param_3);
  return;
}


// ==== FUN_1400a29e0 @ 1400a29e0  undefined FUN_1400a29e0(int param_1, int param_2, undefined8 * param_3)

void FUN_1400a29e0(int param_1,int param_2,undefined8 *param_3)

{
  FUN_1400a3860(param_1,0,param_3);
  FUN_1400a3990(param_2,param_3);
  return;
}


// ==== FUN_1400a2a20 @ 1400a2a20  undefined FUN_1400a2a20(int param_1, longlong param_2, undefined8 * param_3)

void FUN_1400a2a20(int param_1,longlong param_2,undefined8 *param_3)

{
  FUN_1400a3860(param_1,0,param_3);
  FUN_1400a39e0(param_2,param_3);
  return;
}


// ==== FUN_1400a2a60 @ 1400a2a60  undefined FUN_1400a2a60(int param_1, undefined4 param_2, undefined8 * param_3)

void FUN_1400a2a60(int param_1,undefined4 param_2,undefined8 *param_3)

{
  FUN_1400a3860(param_1,5,param_3);
  FUN_1400a3a30(param_2,param_3);
  return;
}


// ==== FUN_1400a2aa0 @ 1400a2aa0  undefined FUN_1400a2aa0(int param_1, undefined8 param_2, undefined8 * param_3)

void FUN_1400a2aa0(int param_1,undefined8 param_2,undefined8 *param_3)

{
  FUN_1400a3860(param_1,1,param_3);
  FUN_1400a3a50(param_2,param_3);
  return;
}


// ==== FUN_1400a2ae0 @ 1400a2ae0  undefined FUN_1400a2ae0(int param_1, undefined4 param_2, undefined8 * param_3)

void FUN_1400a2ae0(int param_1,undefined4 param_2,undefined8 *param_3)

{
  FUN_1400a3860(param_1,5,param_3);
  FUN_1400a3a80(param_2,param_3);
  return;
}


// ==== FUN_1400a2b20 @ 1400a2b20  undefined FUN_1400a2b20(int param_1, undefined8 param_2, undefined8 * param_3)

void FUN_1400a2b20(int param_1,undefined8 param_2,undefined8 *param_3)

{
  FUN_1400a3860(param_1,1,param_3);
  FUN_1400a3aa0(param_2,param_3);
  return;
}


// ==== FUN_1400a2b60 @ 1400a2b60  undefined FUN_1400a2b60(int param_1, undefined4 param_2, undefined8 * param_3)

void FUN_1400a2b60(int param_1,undefined4 param_2,undefined8 *param_3)

{
  FUN_1400a3860(param_1,5,param_3);
  FUN_1400a3ad0(param_2,param_3);
  return;
}


// ==== FUN_1400a2bb0 @ 1400a2bb0  undefined FUN_1400a2bb0(int param_1, undefined8 param_2, undefined8 * param_3)

void FUN_1400a2bb0(int param_1,undefined8 param_2,undefined8 *param_3)

{
  FUN_1400a3860(param_1,1,param_3);
  FUN_1400a3b20(param_2,param_3);
  return;
}


// ==== FUN_1400a2c00 @ 1400a2c00  undefined FUN_1400a2c00(int param_1, char param_2, undefined8 * param_3)

void FUN_1400a2c00(int param_1,char param_2,undefined8 *param_3)

{
  FUN_1400a3860(param_1,0,param_3);
  FUN_1400a3b70(param_2,param_3);
  return;
}


// ==== FUN_1400a2c40 @ 1400a2c40  undefined FUN_1400a2c40(int param_1, uint param_2, undefined8 * param_3)

void FUN_1400a2c40(int param_1,uint param_2,undefined8 *param_3)

{
  FUN_1400a3860(param_1,0,param_3);
  FUN_1400a3bb0(param_2,param_3);
  return;
}


// ==== FUN_1400a2c80 @ 1400a2c80  undefined FUN_1400a2c80(int param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2, undefined8 * param_3)

void FUN_1400a2c80(int param_1,
                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_2,undefined8 *param_3)

{
  __uint64 _Var1;
  int *piVar2;
  longlong lVar3;
  undefined1 *puVar4;
  undefined1 local_78 [8];
  undefined4 local_70 [16];
  uint local_30;
  undefined8 local_28;
  undefined4 *local_20;
  undefined4 *local_18;
  
  local_28 = 0xfffffffffffffffe;
  local_30 = 0;
  FUN_1400a3860(param_1,2,param_3);
  _Var1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (param_2);
  if (0x7fffffff < _Var1) {
    puVar4 = local_78;
    for (lVar3 = 1; lVar3 != 0; lVar3 = lVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    local_20 = FUN_1400783d0(local_70,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\wire_format_lite.cc"
                             ,0x179);
    local_30 = local_30 | 1;
    local_18 = local_20;
    piVar2 = (int *)FUN_140078030((longlong)local_20,"CHECK failed: value.size() <= kint32max: ");
    FUN_140078580(local_78,piVar2);
  }
  if ((local_30 & 1) != 0) {
    local_30 = local_30 & 0xfffffffe;
    FUN_140078440((longlong)local_70);
  }
  _Var1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (param_2);
  FUN_14007c100(param_3,(uint)_Var1);
  FUN_1400a3750(param_3,param_2);
  return;
}


// ==== FUN_1400a2da0 @ 1400a2da0  undefined FUN_1400a2da0(int param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2, undefined8 * param_3)

void FUN_1400a2da0(int param_1,
                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_2,undefined8 *param_3)

{
  __uint64 _Var1;
  int *piVar2;
  char *pcVar3;
  longlong lVar4;
  undefined1 *puVar5;
  undefined1 local_78 [8];
  undefined4 local_70 [16];
  uint local_30;
  undefined8 local_28;
  undefined4 *local_20;
  undefined4 *local_18;
  
  local_28 = 0xfffffffffffffffe;
  local_30 = 0;
  FUN_1400a3860(param_1,2,param_3);
  _Var1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (param_2);
  if (0x7fffffff < _Var1) {
    puVar5 = local_78;
    for (lVar4 = 1; lVar4 != 0; lVar4 = lVar4 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    local_20 = FUN_1400783d0(local_70,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\wire_format_lite.cc"
                             ,0x182);
    local_30 = local_30 | 1;
    local_18 = local_20;
    piVar2 = (int *)FUN_140078030((longlong)local_20,"CHECK failed: value.size() <= kint32max: ");
    FUN_140078580(local_78,piVar2);
  }
  if ((local_30 & 1) != 0) {
    local_30 = local_30 & 0xfffffffe;
    FUN_140078440((longlong)local_70);
  }
  _Var1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (param_2);
  FUN_14007c100(param_3,(uint)_Var1);
  _Var1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (param_2);
  pcVar3 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::data
                     (param_2);
  FUN_1400a3bd0(param_3,pcVar3,(int)_Var1);
  return;
}


// ==== FUN_1400a2ee0 @ 1400a2ee0  undefined FUN_1400a2ee0(int param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2, undefined8 * param_3)

void FUN_1400a2ee0(int param_1,
                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_2,undefined8 *param_3)

{
  __uint64 _Var1;
  int *piVar2;
  longlong lVar3;
  undefined1 *puVar4;
  undefined1 local_78 [8];
  undefined4 local_70 [16];
  uint local_30;
  undefined8 local_28;
  undefined4 *local_20;
  undefined4 *local_18;
  
  local_28 = 0xfffffffffffffffe;
  local_30 = 0;
  FUN_1400a3860(param_1,2,param_3);
  _Var1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (param_2);
  if (0x7fffffff < _Var1) {
    puVar4 = local_78;
    for (lVar3 = 1; lVar3 != 0; lVar3 = lVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    local_20 = FUN_1400783d0(local_70,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\wire_format_lite.cc"
                             ,0x189);
    local_30 = local_30 | 1;
    local_18 = local_20;
    piVar2 = (int *)FUN_140078030((longlong)local_20,"CHECK failed: value.size() <= kint32max: ");
    FUN_140078580(local_78,piVar2);
  }
  if ((local_30 & 1) != 0) {
    local_30 = local_30 & 0xfffffffe;
    FUN_140078440((longlong)local_70);
  }
  _Var1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (param_2);
  FUN_14007c100(param_3,(uint)_Var1);
  FUN_1400a3750(param_3,param_2);
  return;
}


// ==== FUN_1400a3000 @ 1400a3000  undefined FUN_1400a3000(int param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2, undefined8 * param_3)

void FUN_1400a3000(int param_1,
                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_2,undefined8 *param_3)

{
  __uint64 _Var1;
  int *piVar2;
  char *pcVar3;
  longlong lVar4;
  undefined1 *puVar5;
  undefined1 local_78 [8];
  undefined4 local_70 [16];
  uint local_30;
  undefined8 local_28;
  undefined4 *local_20;
  undefined4 *local_18;
  
  local_28 = 0xfffffffffffffffe;
  local_30 = 0;
  FUN_1400a3860(param_1,2,param_3);
  _Var1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (param_2);
  if (0x7fffffff < _Var1) {
    puVar5 = local_78;
    for (lVar4 = 1; lVar4 != 0; lVar4 = lVar4 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
    local_20 = FUN_1400783d0(local_70,3,
                             "F:\\cq\\64\\develop\\protobuf\\src\\google\\protobuf\\wire_format_lite.cc"
                             ,0x191);
    local_30 = local_30 | 1;
    local_18 = local_20;
    piVar2 = (int *)FUN_140078030((longlong)local_20,"CHECK failed: value.size() <= kint32max: ");
    FUN_140078580(local_78,piVar2);
  }
  if ((local_30 & 1) != 0) {
    local_30 = local_30 & 0xfffffffe;
    FUN_140078440((longlong)local_70);
  }
  _Var1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (param_2);
  FUN_14007c100(param_3,(uint)_Var1);
  _Var1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (param_2);
  pcVar3 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::data
                     (param_2);
  FUN_1400a3bd0(param_3,pcVar3,(int)_Var1);
  return;
}


// ==== FUN_1400a3140 @ 1400a3140  undefined FUN_1400a3140(int param_1, longlong * param_2, undefined8 * param_3)

void FUN_1400a3140(int param_1,longlong *param_2,undefined8 *param_3)

{
  FUN_1400a3860(param_1,3,param_3);
  (**(code **)(*param_2 + 0x48))(param_2,param_3);
  FUN_1400a3860(param_1,4,param_3);
  return;
}


// ==== FUN_1400a31a0 @ 1400a31a0  undefined FUN_1400a31a0(int param_1, longlong * param_2, undefined8 * param_3)

void FUN_1400a31a0(int param_1,longlong *param_2,undefined8 *param_3)

{
  uint uVar1;
  
  FUN_1400a3860(param_1,2,param_3);
  uVar1 = (**(code **)(*param_2 + 0x58))(param_2);
  FUN_14007c100(param_3,uVar1);
  (**(code **)(*param_2 + 0x48))(param_2,param_3);
  return;
}


// ==== FUN_1400a3210 @ 1400a3210  undefined FUN_1400a3210(int param_1, longlong * param_2, undefined8 * param_3)

/* WARNING: Removing unreachable block (ram,0x0001400a32bc) */
/* WARNING: Removing unreachable block (ram,0x0001400a32d5) */
/* WARNING: Removing unreachable block (ram,0x0001400a32e1) */
/* WARNING: Removing unreachable block (ram,0x0001400a32e3) */
/* WARNING: Removing unreachable block (ram,0x0001400a32d3) */
/* WARNING: Removing unreachable block (ram,0x0001400a334a) */
/* WARNING: Removing unreachable block (ram,0x0001400a3358) */
/* WARNING: Removing unreachable block (ram,0x0001400a336a) */

void FUN_1400a3210(int param_1,longlong *param_2,undefined8 *param_3)

{
  int iVar1;
  longlong lVar2;
  
  FUN_1400a3860(param_1,3,param_3);
  iVar1 = (**(code **)(*param_2 + 0x58))(param_2);
  lVar2 = FUN_140077850((longlong)param_3,iVar1);
  if (lVar2 == 0) {
    (**(code **)(*param_2 + 0x48))(param_2,param_3);
  }
  else {
    (**(code **)(*param_2 + 0x50))(param_2,lVar2);
  }
  FUN_1400a3860(param_1,4,param_3);
  return;
}


// ==== FUN_1400a33c0 @ 1400a33c0  undefined FUN_1400a33c0(int param_1, longlong * param_2, undefined8 * param_3)

/* WARNING: Removing unreachable block (ram,0x0001400a347d) */
/* WARNING: Removing unreachable block (ram,0x0001400a3496) */
/* WARNING: Removing unreachable block (ram,0x0001400a34a2) */
/* WARNING: Removing unreachable block (ram,0x0001400a34a4) */
/* WARNING: Removing unreachable block (ram,0x0001400a3494) */
/* WARNING: Removing unreachable block (ram,0x0001400a350b) */
/* WARNING: Removing unreachable block (ram,0x0001400a3519) */
/* WARNING: Removing unreachable block (ram,0x0001400a352b) */

void FUN_1400a33c0(int param_1,longlong *param_2,undefined8 *param_3)

{
  uint uVar1;
  longlong lVar2;
  
  FUN_1400a3860(param_1,2,param_3);
  uVar1 = (**(code **)(*param_2 + 0x58))(param_2);
  FUN_14007c100(param_3,uVar1);
  lVar2 = FUN_140077850((longlong)param_3,uVar1);
  if (lVar2 == 0) {
    (**(code **)(*param_2 + 0x48))(param_2,param_3);
  }
  else {
    (**(code **)(*param_2 + 0x50))(param_2,lVar2);
  }
  return;
}


// ==== FUN_1400a3560 @ 1400a3560  undefined8 FUN_1400a3560(undefined8 * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

undefined8
FUN_1400a3560(undefined8 *param_1,
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  uint local_18 [6];
  
  uVar1 = FUN_140097710(param_1,local_18);
  if ((uVar1 & 0xff) == 0) {
    uVar2 = 0;
  }
  else {
    uVar1 = FUN_14007c770(param_1,param_2,local_18[0]);
    if ((uVar1 & 0xff) == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  return uVar2;
}


// ==== FUN_1400a35c0 @ 1400a35c0  undefined8 FUN_1400a35c0(undefined8 * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

undefined8
FUN_1400a35c0(undefined8 *param_1,
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  uint local_18 [6];
  
  uVar1 = FUN_140097710(param_1,local_18);
  if ((uVar1 & 0xff) == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_14007c770(param_1,param_2,local_18[0]);
  }
  return uVar2;
}


// ==== FUN_1400a3610 @ 1400a3610  undefined FUN_1400a3610(undefined8 * param_1, undefined4 * param_2)

void FUN_1400a3610(undefined8 *param_1,undefined4 *param_2)

{
  FUN_14007af70(param_1,param_2);
  return;
}


// ==== FUN_1400a3640 @ 1400a3640  undefined FUN_1400a3640(undefined8 * param_1, undefined8 * param_2)

void FUN_1400a3640(undefined8 *param_1,undefined8 *param_2)

{
  FUN_14007b000(param_1,param_2);
  return;
}


// ==== FUN_1400a3670 @ 1400a3670  bool FUN_1400a3670(longlong param_1, int param_2)

bool FUN_1400a3670(longlong param_1,int param_2)

{
  return *(int *)(param_1 + 0x20) == param_2;
}


// ==== FUN_1400a36b0 @ 1400a36b0  undefined4 FUN_1400a36b0(longlong param_1)

undefined4 FUN_1400a36b0(longlong param_1)

{
  *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + 1;
  return CONCAT31((int3)((uint)*(int *)(param_1 + 0x3c) >> 8),
                  *(int *)(param_1 + 0x38) <= *(int *)(param_1 + 0x3c));
}


// ==== FUN_1400a3700 @ 1400a3700  undefined FUN_1400a3700(longlong param_1)

void FUN_1400a3700(longlong param_1)

{
  if (0 < *(int *)(param_1 + 0x38)) {
    *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + -1;
  }
  return;
}


// ==== FUN_1400a3730 @ 1400a3730  uint FUN_1400a3730(int param_1, uint param_2)

uint FUN_1400a3730(int param_1,uint param_2)

{
  return param_1 << 3 | param_2;
}


// ==== FUN_1400a3750 @ 1400a3750  undefined FUN_1400a3750(undefined8 * param_1, basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * param_2)

void FUN_1400a3750(undefined8 *param_1,
                  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_2)

{
  __uint64 _Var1;
  char *pcVar2;
  
  _Var1 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::size
                    (param_2);
  pcVar2 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::data
                     (param_2);
  FUN_14007bd80(param_1,pcVar2,(int)_Var1);
  return;
}


// ==== FUN_1400a3790 @ 1400a3790  undefined4 FUN_1400a3790(undefined8 * param_1)

undefined4 FUN_1400a3790(undefined8 *param_1)

{
  undefined4 uVar1;
  ulonglong uVar2;
  
  if (((ulonglong)param_1[1] < (ulonglong)param_1[2]) && (*(byte *)param_1[1] < 0x80)) {
    *(uint *)(param_1 + 4) = (uint)*(byte *)param_1[1];
    FUN_14007c740((longlong)param_1,1);
    uVar1 = *(undefined4 *)(param_1 + 4);
  }
  else {
    uVar2 = FUN_14007b260(param_1);
    *(int *)(param_1 + 4) = (int)uVar2;
    uVar1 = *(undefined4 *)(param_1 + 4);
  }
  return uVar1;
}


// ==== FUN_1400a3820 @ 1400a3820  undefined8 FUN_1400a3820(undefined8 * param_1, uint * param_2)

undefined8 FUN_1400a3820(undefined8 *param_1,uint *param_2)

{
  ulonglong uVar1;
  undefined8 uVar2;
  uint local_18 [6];
  
  uVar1 = FUN_140097710(param_1,local_18);
  if ((uVar1 & 0xff) == 0) {
    uVar2 = 0;
  }
  else {
    *param_2 = local_18[0];
    uVar2 = CONCAT71((uint7)(uint3)(local_18[0] >> 8),1);
  }
  return uVar2;
}


// ==== FUN_1400a3860 @ 1400a3860  undefined FUN_1400a3860(int param_1, uint param_2, undefined8 * param_3)

void FUN_1400a3860(int param_1,uint param_2,undefined8 *param_3)

{
  uint uVar1;
  
  uVar1 = FUN_1400a3730(param_1,param_2);
  FUN_1400a3890(param_3,uVar1);
  return;
}


// ==== FUN_1400a3890 @ 1400a3890  undefined FUN_1400a3890(undefined8 * param_1, uint param_2)

void FUN_1400a3890(undefined8 *param_1,uint param_2)

{
  FUN_14007c100(param_1,param_2);
  return;
}


// ==== FUN_1400a38b0 @ 1400a38b0  undefined FUN_1400a38b0(uint param_1, undefined8 * param_2)

void FUN_1400a38b0(uint param_1,undefined8 *param_2)

{
  FUN_1400a38d0(param_2,param_1);
  return;
}


// ==== FUN_1400a38d0 @ 1400a38d0  undefined FUN_1400a38d0(undefined8 * param_1, uint param_2)

void FUN_1400a38d0(undefined8 *param_1,uint param_2)

{
  if ((int)param_2 < 0) {
    FUN_14007c220(param_1,(longlong)(int)param_2);
  }
  else {
    FUN_14007c100(param_1,param_2);
  }
  return;
}


// ==== FUN_1400a3910 @ 1400a3910  undefined FUN_1400a3910(ulonglong param_1, undefined8 * param_2)

void FUN_1400a3910(ulonglong param_1,undefined8 *param_2)

{
  FUN_14007c220(param_2,param_1);
  return;
}


// ==== FUN_1400a3940 @ 1400a3940  undefined FUN_1400a3940(uint param_1, undefined8 * param_2)

void FUN_1400a3940(uint param_1,undefined8 *param_2)

{
  FUN_14007c100(param_2,param_1);
  return;
}


// ==== FUN_1400a3960 @ 1400a3960  undefined FUN_1400a3960(ulonglong param_1, undefined8 * param_2)

void FUN_1400a3960(ulonglong param_1,undefined8 *param_2)

{
  FUN_14007c220(param_2,param_1);
  return;
}


// ==== FUN_1400a3990 @ 1400a3990  undefined FUN_1400a3990(int param_1, undefined8 * param_2)

void FUN_1400a3990(int param_1,undefined8 *param_2)

{
  uint uVar1;
  
  uVar1 = FUN_1400a39c0(param_1);
  FUN_14007c100(param_2,uVar1);
  return;
}


// ==== FUN_1400a39c0 @ 1400a39c0  uint FUN_1400a39c0(int param_1)

uint FUN_1400a39c0(int param_1)

{
  return param_1 << 1 ^ param_1 >> 0x1f;
}


// ==== FUN_1400a39e0 @ 1400a39e0  undefined FUN_1400a39e0(longlong param_1, undefined8 * param_2)

void FUN_1400a39e0(longlong param_1,undefined8 *param_2)

{
  ulonglong uVar1;
  
  uVar1 = FUN_1400a3a10(param_1);
  FUN_14007c220(param_2,uVar1);
  return;
}


// ==== FUN_1400a3a10 @ 1400a3a10  ulonglong FUN_1400a3a10(longlong param_1)

ulonglong FUN_1400a3a10(longlong param_1)

{
  return param_1 << 1 ^ param_1 >> 0x3f;
}


// ==== FUN_1400a3a30 @ 1400a3a30  undefined FUN_1400a3a30(undefined4 param_1, undefined8 * param_2)

void FUN_1400a3a30(undefined4 param_1,undefined8 *param_2)

{
  FUN_14007bf80(param_2,param_1);
  return;
}


// ==== FUN_1400a3a50 @ 1400a3a50  undefined FUN_1400a3a50(undefined8 param_1, undefined8 * param_2)

void FUN_1400a3a50(undefined8 param_1,undefined8 *param_2)

{
  FUN_14007c030(param_2,param_1);
  return;
}


// ==== FUN_1400a3a80 @ 1400a3a80  undefined FUN_1400a3a80(undefined4 param_1, undefined8 * param_2)

void FUN_1400a3a80(undefined4 param_1,undefined8 *param_2)

{
  FUN_14007bf80(param_2,param_1);
  return;
}


// ==== FUN_1400a3aa0 @ 1400a3aa0  undefined FUN_1400a3aa0(undefined8 param_1, undefined8 * param_2)

void FUN_1400a3aa0(undefined8 param_1,undefined8 *param_2)

{
  FUN_14007c030(param_2,param_1);
  return;
}


// ==== FUN_1400a3ad0 @ 1400a3ad0  undefined FUN_1400a3ad0(undefined4 param_1, undefined8 * param_2)

void FUN_1400a3ad0(undefined4 param_1,undefined8 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = FUN_1400a3b00(param_1);
  FUN_14007bf80(param_2,uVar1);
  return;
}


// ==== FUN_1400a3b00 @ 1400a3b00  undefined4 FUN_1400a3b00(undefined4 param_1)

undefined4 FUN_1400a3b00(undefined4 param_1)

{
  return param_1;
}


// ==== FUN_1400a3b20 @ 1400a3b20  undefined FUN_1400a3b20(undefined8 param_1, undefined8 * param_2)

void FUN_1400a3b20(undefined8 param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  
  uVar1 = FUN_1400a3b50(param_1);
  FUN_14007c030(param_2,uVar1);
  return;
}


// ==== FUN_1400a3b50 @ 1400a3b50  undefined8 FUN_1400a3b50(undefined8 param_1)

undefined8 FUN_1400a3b50(undefined8 param_1)

{
  return param_1;
}


// ==== FUN_1400a3b70 @ 1400a3b70  undefined FUN_1400a3b70(char param_1, undefined8 * param_2)

void FUN_1400a3b70(char param_1,undefined8 *param_2)

{
  uint local_18;
  
  local_18 = (uint)(param_1 != '\0');
  FUN_14007c100(param_2,local_18);
  return;
}


// ==== FUN_1400a3bb0 @ 1400a3bb0  undefined FUN_1400a3bb0(uint param_1, undefined8 * param_2)

void FUN_1400a3bb0(uint param_1,undefined8 *param_2)

{
  FUN_1400a38d0(param_2,param_1);
  return;
}


// ==== FUN_1400a3bd0 @ 1400a3bd0  undefined FUN_1400a3bd0(undefined8 * param_1, void * param_2, int param_3)

void FUN_1400a3bd0(undefined8 *param_1,void *param_2,int param_3)

{
  if (*(char *)((longlong)param_1 + 0x19) == '\0') {
    FUN_14007bd80(param_1,param_2,param_3);
  }
  else {
    FUN_14007be70(param_1,param_2,param_3);
  }
  return;
}


// ==== FUN_1400a3c20 @ 1400a3c20  undefined FUN_1400a3c20(longlong * param_1, undefined4 * param_2)

void FUN_1400a3c20(longlong *param_1,undefined4 *param_2)

{
  if ((int)param_1[1] == *(int *)((longlong)param_1 + 0xc)) {
    FUN_1400a3c90(param_1,*(int *)((longlong)param_1 + 0xc) + 1);
  }
  *(undefined4 *)(*param_1 + (longlong)(int)param_1[1] * 4) = *param_2;
  *(int *)(param_1 + 1) = (int)param_1[1] + 1;
  return;
}


// ==== FUN_1400a3c90 @ 1400a3c90  undefined FUN_1400a3c90(undefined8 * param_1, int param_2)

void FUN_1400a3c90(undefined8 *param_1,int param_2)

{
  void *pvVar1;
  undefined1 auVar2 [16];
  int *piVar3;
  __uint64 _Var4;
  int local_res10 [6];
  int local_20 [2];
  void *local_18;
  void *local_10;
  
  if (*(int *)((longlong)param_1 + 0xc) < param_2) {
    pvVar1 = (void *)*param_1;
    local_20[0] = *(int *)((longlong)param_1 + 0xc) << 1;
    local_res10[0] = param_2;
    piVar3 = FUN_14007d190(local_20,local_res10);
    piVar3 = FUN_14007d190((int *)&DAT_1400d2480,piVar3);
    *(int *)((longlong)param_1 + 0xc) = *piVar3;
    auVar2._8_8_ = 0;
    auVar2._0_8_ = (longlong)*(int *)((longlong)param_1 + 0xc);
    _Var4 = SUB168(ZEXT816(4) * auVar2,0);
    if (SUB168(ZEXT816(4) * auVar2,8) != 0) {
      _Var4 = 0xffffffffffffffff;
    }
    local_18 = operator_new__(_Var4);
    *param_1 = local_18;
    if (pvVar1 != (void *)0x0) {
      FUN_1400a3d70(param_1,(void *)*param_1,pvVar1,*(int *)(param_1 + 1));
      local_10 = pvVar1;
      operator_delete__(pvVar1);
    }
  }
  return;
}


// ==== FUN_1400a3d70 @ 1400a3d70  undefined FUN_1400a3d70(undefined8 param_1, void * param_2, void * param_3, int param_4)

void FUN_1400a3d70(undefined8 param_1,void *param_2,void *param_3,int param_4)

{
  FUN_1400a3db0(param_1,param_2,param_3,param_4);
  return;
}


// ==== FUN_1400a3db0 @ 1400a3db0  undefined FUN_1400a3db0(undefined8 param_1, void * param_2, void * param_3, int param_4)

void FUN_1400a3db0(undefined8 param_1,void *param_2,void *param_3,int param_4)

{
  longlong lVar1;
  undefined1 *puVar2;
  undefined1 local_18 [16];
  
  puVar2 = local_18;
  for (lVar1 = 1; lVar1 != 0; lVar1 = lVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  FUN_1400a3e00(local_18,param_2,param_3,param_4);
  return;
}


// ==== FUN_1400a3e00 @ 1400a3e00  undefined FUN_1400a3e00(undefined8 param_1, void * param_2, void * param_3, int param_4)

void FUN_1400a3e00(undefined8 param_1,void *param_2,void *param_3,int param_4)

{
  memcpy(param_2,param_3,(longlong)param_4 << 2);
  return;
}


// ==== Unwind@1400a3ec0 @ 1400a3ec0  undefined Unwind@1400a3ec0(undefined8 param_1, longlong param_2)

void Unwind_1400a3ec0(undefined8 param_1,longlong param_2)

{
  CTickAnalyst::~CTickAnalyst((CTickAnalyst *)(param_2 + 0x38));
  return;
}


// ==== Catch@1400a3ee0 @ 1400a3ee0  undefined * Catch@1400a3ee0(void)

undefined * Catch_1400a3ee0(void)

{
  log_InlineLogCATCH_ERROR("pKernel->ProcessMsg() @%s,%d");
  return &DAT_1400018f7;
}


// ==== Unwind@1400a3f20 @ 1400a3f20  undefined Unwind@1400a3f20(undefined8 param_1, longlong param_2)

void Unwind_1400a3f20(undefined8 param_1,longlong param_2)

{
  FUN_140001020(*(undefined8 **)(param_2 + 0x20));
  return;
}


// ==== Unwind@1400a3f40 @ 1400a3f40  undefined Unwind@1400a3f40(undefined8 param_1, longlong param_2)

void Unwind_1400a3f40(undefined8 param_1,longlong param_2)

{
  FUN_140001020(*(undefined8 **)(param_2 + 0x20));
  return;
}


// ==== Unwind@1400a3f60 @ 1400a3f60  undefined Unwind@1400a3f60(undefined8 param_1, longlong param_2)

void Unwind_1400a3f60(undefined8 param_1,longlong param_2)

{
  FUN_140001020(*(undefined8 **)(param_2 + 0x40));
  return;
}


// ==== Unwind@1400a3f80 @ 1400a3f80  undefined Unwind@1400a3f80(undefined8 param_1, longlong param_2)

void Unwind_1400a3f80(undefined8 param_1,longlong param_2)

{
  CIniFile::~CIniFile((CIniFile *)(param_2 + 0x30));
  return;
}


// ==== Unwind@1400a3fa0 @ 1400a3fa0  undefined Unwind@1400a3fa0(undefined8 param_1, longlong param_2)

void Unwind_1400a3fa0(undefined8 param_1,longlong param_2)

{
  operator_delete(*(void **)(param_2 + 0x68));
  return;
}


// ==== Unwind@1400a3fc0 @ 1400a3fc0  undefined Unwind@1400a3fc0(undefined8 param_1, longlong param_2)

void Unwind_1400a3fc0(undefined8 param_1,longlong param_2)

{
  FUN_140001020(*(undefined8 **)(param_2 + 0x68));
  return;
}


// ==== Catch@1400a3fe0 @ 1400a3fe0  undefined Catch@1400a3fe0(undefined8 param_1, longlong param_2)

void Catch_1400a3fe0(undefined8 param_1,longlong param_2)

{
  (**(code **)(param_2 + 0x60))();
                    /* WARNING: Subroutine does not return */
  _CxxThrowException((void *)0x0,(ThrowInfo *)0x0);
}


// ==== Unwind@1400a4010 @ 1400a4010  undefined Unwind@1400a4010(undefined8 param_1, longlong param_2)

void Unwind_1400a4010(undefined8 param_1,longlong param_2)

{
  FUN_140001db0(*(longlong *)(param_2 + 0x40) + 8);
  return;
}


// ==== Unwind@1400a4030 @ 1400a4030  undefined Unwind@1400a4030(undefined8 param_1, longlong param_2)

void Unwind_1400a4030(undefined8 param_1,longlong param_2)

{
  FUN_140001db0(*(longlong *)(param_2 + 0x70) + 8);
  return;
}


// ==== Unwind@1400a4050 @ 1400a4050  undefined Unwind@1400a4050(undefined8 param_1, longlong param_2)

void Unwind_1400a4050(undefined8 param_1,longlong param_2)

{
  FUN_140001db0(param_2 + 0x28);
  return;
}


// ==== Unwind@1400a4070 @ 1400a4070  undefined Unwind@1400a4070(undefined8 param_1, longlong param_2)

void Unwind_1400a4070(undefined8 param_1,longlong param_2)

{
  CThreadBase::~CThreadBase(*(CThreadBase **)(param_2 + 0x40));
  return;
}


// ==== Catch@1400a4090 @ 1400a4090  undefined * Catch@1400a4090(void)

undefined * Catch_1400a4090(void)

{
  log_InlineLogCATCH_ERROR("CKernelThread::EvnetRoutine");
  return &DAT_140002529;
}


// ==== Unwind@1400a40c0 @ 1400a40c0  undefined Unwind@1400a40c0(undefined8 param_1, longlong param_2)

void Unwind_1400a40c0(undefined8 param_1,longlong param_2)

{
  CThreadBase::~CThreadBase(*(CThreadBase **)(param_2 + 0x40));
  return;
}


// ==== Catch@1400a40e0 @ 1400a40e0  undefined * Catch@1400a40e0(void)

undefined * Catch_1400a40e0(void)

{
  log_InlineLogCATCH_ERROR("SAFE_RELEASE(m_pSockClient) @%s,%d");
  return &DAT_140002686;
}


// ==== Unwind@1400a4120 @ 1400a4120  undefined Unwind@1400a4120(undefined8 param_1, longlong param_2)

void Unwind_1400a4120(undefined8 param_1,longlong param_2)

{
  CThreadBase::~CThreadBase(*(CThreadBase **)(param_2 + 0x40));
  return;
}


// ==== Unwind@1400a4140 @ 1400a4140  undefined Unwind@1400a4140(undefined8 param_1, longlong param_2)

void Unwind_1400a4140(undefined8 param_1,longlong param_2)

{
  CTickAnalyst::~CTickAnalyst((CTickAnalyst *)(param_2 + 0xb8));
  return;
}


// ==== Unwind@1400a4160 @ 1400a4160  undefined Unwind@1400a4160(undefined8 param_1, longlong param_2)

void Unwind_1400a4160(undefined8 param_1,longlong param_2)

{
  CTickAnalyst::~CTickAnalyst((CTickAnalyst *)(param_2 + 0x68));
  return;
}


// ==== Unwind@1400a4180 @ 1400a4180  undefined Unwind@1400a4180(undefined8 param_1, longlong param_2)

void Unwind_1400a4180(undefined8 param_1,longlong param_2)

{
  CTickAnalyst::~CTickAnalyst((CTickAnalyst *)(param_2 + 0x80));
  return;
}


// ==== Catch@1400a41a0 @ 1400a41a0  undefined * Catch@1400a41a0(void)

undefined * Catch_1400a41a0(void)

{
  log_InlineLogCATCH_ERROR("CKernelThread::OnProcess, ProcessMsg packet:%d, port:%d.");
  return &DAT_140002965;
}


// ==== Unwind@1400a41e0 @ 1400a41e0  undefined Unwind@1400a41e0(void)

void Unwind_1400a41e0(void)

{
  DAT_140103c64 = DAT_140103c64 & 0xfffffffe;
  return;
}


// ==== Unwind@1400a4200 @ 1400a4200  undefined Unwind@1400a4200(undefined8 param_1, longlong param_2)

void Unwind_1400a4200(undefined8 param_1,longlong param_2)

{
  CTickAnalyst::~CTickAnalyst((CTickAnalyst *)(param_2 + 0xa0));
  return;
}


// ==== Catch@1400a4220 @ 1400a4220  undefined8 Catch@1400a4220(void)

undefined8 Catch_1400a4220(void)

{
  log_InlineLogCATCH_ERROR("m_pKernel->OnTimer() @%s,%d");
  return 0x140002a8f;
}


// ==== Catch@1400a4260 @ 1400a4260  undefined8 Catch@1400a4260(void)

undefined8 Catch_1400a4260(void)

{
  log_InlineLogCATCH_ERROR("CKernelThread::OnProcess @%s,%d");
  return 0x140002afb;
}


// ==== Unwind@1400a42a0 @ 1400a42a0  undefined Unwind@1400a42a0(undefined8 param_1, longlong param_2)

void Unwind_1400a42a0(undefined8 param_1,longlong param_2)

{
  operator_delete(*(void **)(param_2 + 0x88));
  return;
}


// ==== Catch@1400a42c0 @ 1400a42c0  undefined8 Catch@1400a42c0(void)

undefined8 Catch_1400a42c0(void)

{
  log_InlineLogCATCH_ERROR("SAFE_RELEASE(m_pSockClient) @%s,%d");
  return 0x140002d27;
}


// ==== Unwind@1400a4300 @ 1400a4300  undefined Unwind@1400a4300(undefined8 param_1, longlong param_2)

void Unwind_1400a4300(undefined8 param_1,longlong param_2)

{
  CThreadBase::~CThreadBase(*(CThreadBase **)(param_2 + 0x40));
  return;
}


// ==== Unwind@1400a4320 @ 1400a4320  undefined Unwind@1400a4320(undefined8 param_1, longlong param_2)

void Unwind_1400a4320(undefined8 param_1,longlong param_2)

{
  CThreadBase::~CThreadBase(*(CThreadBase **)(param_2 + 0x40));
  return;
}


// ==== Unwind@1400a4340 @ 1400a4340  undefined Unwind@1400a4340(void)

void Unwind_1400a4340(void)

{
  DAT_140103c6c = DAT_140103c6c & 0xfffffffe;
  return;
}


// ==== Unwind@1400a4360 @ 1400a4360  undefined Unwind@1400a4360(undefined8 param_1, longlong param_2)

void Unwind_1400a4360(undefined8 param_1,longlong param_2)

{
  CTickAnalyst::~CTickAnalyst((CTickAnalyst *)(param_2 + 0x70));
  return;
}


// ==== Unwind@1400a4380 @ 1400a4380  undefined Unwind@1400a4380(undefined8 param_1, longlong param_2)

void Unwind_1400a4380(undefined8 param_1,longlong param_2)

{
  CTickAnalyst::~CTickAnalyst((CTickAnalyst *)(param_2 + 0x58));
  return;
}


// ==== Catch@1400a43a0 @ 1400a43a0  undefined * Catch@1400a43a0(undefined8 param_1, longlong param_2)

undefined * Catch_1400a43a0(undefined8 param_1,longlong param_2)

{
  longlong *plVar1;
  
  plVar1 = *(longlong **)(*(longlong *)(param_2 + 0x38) + 0x40);
  (**(code **)(*plVar1 + 0x28))
            (plVar1,*(longlong *)(param_2 + 0x38) + 0x50,
             "catch:: catch at CLogThread::OnProcess m_pLogKernel->OnTimer",1);
  return &DAT_140003060;
}


// ==== Catch@1400a43e0 @ 1400a43e0  undefined * Catch@1400a43e0(undefined8 param_1, longlong param_2)

undefined * Catch_1400a43e0(undefined8 param_1,longlong param_2)

{
  longlong *plVar1;
  
  plVar1 = *(longlong **)(*(longlong *)(param_2 + 0x38) + 0x40);
  (**(code **)(*plVar1 + 0x28))
            (plVar1,*(longlong *)(param_2 + 0x38) + 0x50,"catch:: catch at CLogThread::OnProcess",1)
  ;
  return &DAT_140003129;
}


// ==== Unwind@1400a4420 @ 1400a4420  undefined Unwind@1400a4420(undefined8 param_1, longlong param_2)

void Unwind_1400a4420(undefined8 param_1,longlong param_2)

{
  CThreadBase::~CThreadBase(*(CThreadBase **)(param_2 + 0x40));
  return;
}


// ==== Unwind@1400a4440 @ 1400a4440  undefined Unwind@1400a4440(undefined8 param_1, longlong param_2)

void Unwind_1400a4440(undefined8 param_1,longlong param_2)

{
  CWinApp::~CWinApp(*(CWinApp **)(param_2 + 0x40));
  return;
}


// ==== Unwind@1400a4460 @ 1400a4460  undefined Unwind@1400a4460(undefined8 param_1, longlong param_2)

void Unwind_1400a4460(undefined8 param_1,longlong param_2)

{
  CWinApp::~CWinApp(*(CWinApp **)(param_2 + 0x40));
  return;
}


// ==== Unwind@1400a4480 @ 1400a4480  undefined Unwind@1400a4480(undefined8 param_1, longlong param_2)

void Unwind_1400a4480(undefined8 param_1,longlong param_2)

{
  CSyncObject::~CSyncObject(*(CSyncObject **)(param_2 + 0x40));
  return;
}


// ==== FUN_1400a44a0 @ 1400a44a0  bool FUN_1400a44a0(undefined8 * param_1)

bool FUN_1400a44a0(undefined8 *param_1)

{
  return *(int *)*param_1 == -0x3fffffe9;
}


// ==== Unwind@1400a44d0 @ 1400a44d0  undefined Unwind@1400a44d0(undefined8 param_1, longlong param_2)

void Unwind_1400a44d0(undefined8 param_1,longlong param_2)

{
  CWinApp::~CWinApp(*(CWinApp **)(param_2 + 0x40));
  return;
}


// ==== Unwind@1400a44f0 @ 1400a44f0  undefined Unwind@1400a44f0(undefined8 param_1, longlong param_2)

void Unwind_1400a44f0(undefined8 param_1,longlong param_2)

{
  CDialog::~CDialog(*(CDialog **)(param_2 + 0x40));
  return;
}


// ==== Unwind@1400a4510 @ 1400a4510  undefined Unwind@1400a4510(undefined8 param_1, longlong param_2)

void Unwind_1400a4510(undefined8 param_1,longlong param_2)

{
  CEdit::~CEdit((CEdit *)(*(longlong *)(param_2 + 0x40) + 0xf0));
  return;
}


// ==== Unwind@1400a4530 @ 1400a4530  undefined Unwind@1400a4530(undefined8 param_1, longlong param_2)

void Unwind_1400a4530(undefined8 param_1,longlong param_2)

{
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
  ~CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (*(longlong *)(param_2 + 0x40) + 0x198));
  return;
}


// ==== Unwind@1400a4550 @ 1400a4550  undefined Unwind@1400a4550(undefined8 param_1, longlong param_2)

void Unwind_1400a4550(undefined8 param_1,longlong param_2)

{
  ATL::CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>::
  ~CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_>
            ((CStringT<char,class_StrTraitMFC_DLL<char,class_ATL::ChTraitsCRT<char>_>_> *)
             (*(longlong *)(param_2 + 0x40) + 0x1a0));
  return;
}


// ==== Unwind@1400a4570 @ 1400a4570  undefined Unwind@1400a4570(undefined8 param_1, longlong param_2)

void Unwind_1400a4570(undefined8 param_1,longlong param_2)

{
  FUN_1400032c0((CSyncObject *)(*(longlong *)(param_2 + 0x40) + 0x1a8));
  return;
}


