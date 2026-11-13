// NpcServer.exe :: _crt_std  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== std::tr1::_Ref_count_base::vf_0x18 @ 140001060  undefined8 vf_0x18(void)

undefined8 std::tr1::_Ref_count_base::vf_0x18(void)

{
  return 0;
}


// ==== std::tr1::_Ref_count_base::vf_0x10 @ 140001070  undefined8 * vf_0x10(undefined8 * param_1, byte param_2)

undefined8 * std::tr1::_Ref_count_base::vf_0x10(undefined8 *param_1,byte param_2)

{
  *param_1 = vftable;
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== std::tr1::_Ref_count_d<char,void_(__cdecl*)(char*___ptr64),class_std::allocator<int>_>::vf_0x18 @ 140001ab0  longlong vf_0x18(longlong param_1, type_info * param_2)

longlong std::tr1::_Ref_count_d<char,void_(__cdecl*)(char*___ptr64),class_std::allocator<int>_>::
         vf_0x18(longlong param_1,type_info *param_2)

{
  bool bVar1;
  
  bVar1 = type_info::operator==(param_2,(type_info *)&TypeDescriptor_140102090);
  if (bVar1) {
    return param_1 + 0x20;
  }
  return 0;
}


// ==== std::tr1::_Ref_count_d<char,void_(__cdecl*)(char*___ptr64),class_std::allocator<int>_>::vf_0x0 @ 140001af0  undefined vf_0x0(longlong param_1)

void std::tr1::_Ref_count_d<char,void_(__cdecl*)(char*___ptr64),class_std::allocator<int>_>::vf_0x0
               (longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x000140001af7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(param_1 + 0x20))(*(undefined8 *)(param_1 + 8));
  return;
}


// ==== std::tr1::_Ref_count_d<char,void_(__cdecl*)(char*___ptr64),class_std::allocator<int>_>::vf_0x10 @ 140001b40  undefined8 * vf_0x10(undefined8 * param_1, byte param_2)

undefined8 *
std::tr1::_Ref_count_d<char,void_(__cdecl*)(char*___ptr64),class_std::allocator<int>_>::vf_0x10
          (undefined8 *param_1,byte param_2)

{
  *param_1 = _Ref_count_base::vftable;
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== std::tr1::_Ref_count_d<char,void_(__cdecl*)(char*___ptr64),class_std::allocator<int>_>::vf_0x8 @ 140001f20  undefined vf_0x8(longlong * param_1)

void std::tr1::_Ref_count_d<char,void_(__cdecl*)(char*___ptr64),class_std::allocator<int>_>::vf_0x8
               (longlong *param_1)

{
  (**(code **)(*param_1 + 0x10))(param_1,0);
  operator_delete(param_1);
  return;
}


// ==== std::tr1::_Ref_count<class_CAIStrategyMgr>::vf_0x0 @ 14001c510  undefined vf_0x0(longlong param_1)

void std::tr1::_Ref_count<class_CAIStrategyMgr>::vf_0x0(longlong param_1)

{
  undefined8 *puVar1;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  return;
}


// ==== std::tr1::_Ref_count<class_CAIStrategyMgr>::vf_0x8 @ 14001c530  undefined vf_0x8(longlong * param_1)

void std::tr1::_Ref_count<class_CAIStrategyMgr>::vf_0x8(longlong *param_1)

{
  if (param_1 != (longlong *)0x0) {
    (**(code **)(*param_1 + 0x10))(param_1,1);
  }
  return;
}


// ==== std::tr1::_Ref_count_d<class_CItemType,class_TReleaseDeleter<class_CItemType>,class_std::allocator<int>_>::vf_0x18 @ 14001c970  longlong vf_0x18(longlong param_1, type_info * param_2)

longlong std::tr1::
         _Ref_count_d<class_CItemType,class_TReleaseDeleter<class_CItemType>,class_std::allocator<int>_>
         ::vf_0x18(longlong param_1,type_info *param_2)

{
  bool bVar1;
  
  bVar1 = type_info::operator==
                    (param_2,(type_info *)&TReleaseDeleter<class_CItemType>::RTTI_Type_Descriptor);
  if (bVar1) {
    return param_1 + 0x19;
  }
  return 0;
}


// ==== std::tr1::_Ref_count_d<class_CItemType,class_TReleaseDeleter<class_CItemType>,class_std::allocator<int>_>::vf_0x0 @ 14001c9b0  undefined vf_0x0(longlong param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)

void std::tr1::
     _Ref_count_d<class_CItemType,class_TReleaseDeleter<class_CItemType>,class_std::allocator<int>_>
     ::vf_0x0(longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  FUN_14001c480(param_1 + 0x19,*(undefined8 **)(param_1 + 8),param_3,param_4);
  return;
}


// ==== std::tr1::_Ref_count_d<class_CItemType,class_TReleaseDeleter<class_CItemType>,class_std::allocator<int>_>::vf_0x10 @ 14001ca00  undefined8 * vf_0x10(undefined8 * param_1, byte param_2)

undefined8 *
std::tr1::
_Ref_count_d<class_CItemType,class_TReleaseDeleter<class_CItemType>,class_std::allocator<int>_>::
vf_0x10(undefined8 *param_1,byte param_2)

{
  *param_1 = _Ref_count_base::vftable;
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== std::tr1::_Ref_count<class_CAIStrategyMgr>::vf_0x10 @ 14001ca60  undefined8 * vf_0x10(undefined8 * param_1, byte param_2)

undefined8 * std::tr1::_Ref_count<class_CAIStrategyMgr>::vf_0x10(undefined8 *param_1,byte param_2)

{
  *param_1 = _Ref_count_base::vftable;
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== std::tr1::_Ref_count_d<class_CItemType,class_TReleaseDeleter<class_CItemType>,class_std::allocator<int>_>::vf_0x8 @ 14001cc40  undefined vf_0x8(longlong * param_1)

void std::tr1::
     _Ref_count_d<class_CItemType,class_TReleaseDeleter<class_CItemType>,class_std::allocator<int>_>
     ::vf_0x8(longlong *param_1)

{
  (**(code **)(*param_1 + 0x10))(param_1,0);
  operator_delete(param_1);
  return;
}


// ==== std::bad_alloc::vf_0x0 @ 14001dac0  exception * vf_0x0(exception * param_1, uint param_2)

exception * std::bad_alloc::vf_0x0(exception *param_1,uint param_2)

{
  *(undefined ***)param_1 = vftable;
  std::exception::~exception(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== std::logic_error::vf_0x8 @ 14001dba0  longlong vf_0x8(longlong param_1)

longlong std::logic_error::vf_0x8(longlong param_1)

{
  if (0xf < *(ulonglong *)(param_1 + 0x38)) {
    return *(longlong *)(param_1 + 0x20);
  }
  return param_1 + 0x20;
}


// ==== std::logic_error::vf_0x0 @ 14001dbc0  exception * vf_0x0(exception * param_1, uint param_2)

exception * std::logic_error::vf_0x0(exception *param_1,uint param_2)

{
  *(undefined ***)param_1 = vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18));
  std::exception::~exception(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== std::out_of_range::vf_0x0 @ 14001dcd0  exception * vf_0x0(exception * param_1, uint param_2)

exception * std::out_of_range::vf_0x0(exception *param_1,uint param_2)

{
  *(undefined ***)param_1 = vftable;
  *(undefined ***)param_1 = logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18));
  std::exception::~exception(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== std::length_error::vf_0x0 @ 14001f5a0  exception * vf_0x0(exception * param_1, uint param_2)

exception * std::length_error::vf_0x0(exception *param_1,uint param_2)

{
  *(undefined ***)param_1 = vftable;
  *(undefined ***)param_1 = logic_error::vftable;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  ~basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             (param_1 + 0x18));
  std::exception::~exception(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== std::tr1::_Ref_count<class_CNeuralAIStrategy>::vf_0x0 @ 14003f6a0  undefined vf_0x0(longlong param_1)

void std::tr1::_Ref_count<class_CNeuralAIStrategy>::vf_0x0(longlong param_1)

{
  undefined8 *puVar1;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  return;
}


// ==== std::tr1::_Ref_count<class_CNeuralAIStrategy>::vf_0x8 @ 14003f6c0  undefined vf_0x8(longlong * param_1)

void std::tr1::_Ref_count<class_CNeuralAIStrategy>::vf_0x8(longlong *param_1)

{
  if (param_1 != (longlong *)0x0) {
    (**(code **)(*param_1 + 0x10))(param_1,1);
  }
  return;
}


// ==== std::tr1::_Ref_count<class_CDefaultAIStrategy>::vf_0x0 @ 14003f720  undefined vf_0x0(longlong param_1)

void std::tr1::_Ref_count<class_CDefaultAIStrategy>::vf_0x0(longlong param_1)

{
  undefined8 *puVar1;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  return;
}


// ==== std::tr1::_Ref_count<class_CDefaultAIStrategy>::vf_0x8 @ 14003f740  undefined vf_0x8(longlong * param_1)

void std::tr1::_Ref_count<class_CDefaultAIStrategy>::vf_0x8(longlong *param_1)

{
  if (param_1 != (longlong *)0x0) {
    (**(code **)(*param_1 + 0x10))(param_1,1);
  }
  return;
}


// ==== std::tr1::_Ref_count<class_CNeuralAIStrategy>::vf_0x10 @ 140040c60  undefined8 * vf_0x10(undefined8 * param_1, byte param_2)

undefined8 *
std::tr1::_Ref_count<class_CNeuralAIStrategy>::vf_0x10(undefined8 *param_1,byte param_2)

{
  *param_1 = _Ref_count_base::vftable;
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== std::tr1::_Ref_count<class_CDefaultAIStrategy>::vf_0x10 @ 140040ca0  undefined8 * vf_0x10(undefined8 * param_1, byte param_2)

undefined8 *
std::tr1::_Ref_count<class_CDefaultAIStrategy>::vf_0x10(undefined8 *param_1,byte param_2)

{
  *param_1 = _Ref_count_base::vftable;
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== std::tr1::_Ref_count_d<struct__iobuf,int_(__cdecl*)(struct__iobuf*___ptr64),class_std::allocator<int>_>::vf_0x18 @ 14004bcf0  longlong vf_0x18(longlong param_1, type_info * param_2)

longlong std::tr1::
         _Ref_count_d<struct__iobuf,int_(__cdecl*)(struct__iobuf*___ptr64),class_std::allocator<int>_>
         ::vf_0x18(longlong param_1,type_info *param_2)

{
  bool bVar1;
  
  bVar1 = type_info::operator==(param_2,(type_info *)&TypeDescriptor_140102df8);
  if (bVar1) {
    return param_1 + 0x20;
  }
  return 0;
}


// ==== std::tr1::_Ref_count_d<struct__iobuf,int_(__cdecl*)(struct__iobuf*___ptr64),class_std::allocator<int>_>::vf_0x0 @ 14004bd30  undefined vf_0x0(longlong param_1)

void std::tr1::
     _Ref_count_d<struct__iobuf,int_(__cdecl*)(struct__iobuf*___ptr64),class_std::allocator<int>_>::
     vf_0x0(longlong param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00014004bd37. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(param_1 + 0x20))(*(undefined8 *)(param_1 + 8));
  return;
}


// ==== std::tr1::_Ref_count_d<struct__iobuf,int_(__cdecl*)(struct__iobuf*___ptr64),class_std::allocator<int>_>::vf_0x10 @ 14004bd80  undefined8 * vf_0x10(undefined8 * param_1, byte param_2)

undefined8 *
std::tr1::
_Ref_count_d<struct__iobuf,int_(__cdecl*)(struct__iobuf*___ptr64),class_std::allocator<int>_>::
vf_0x10(undefined8 *param_1,byte param_2)

{
  *param_1 = _Ref_count_base::vftable;
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== std::tr1::_Ref_count_d<struct__iobuf,int_(__cdecl*)(struct__iobuf*___ptr64),class_std::allocator<int>_>::vf_0x8 @ 14004d9b0  undefined vf_0x8(longlong * param_1)

void std::tr1::
     _Ref_count_d<struct__iobuf,int_(__cdecl*)(struct__iobuf*___ptr64),class_std::allocator<int>_>::
     vf_0x8(longlong *param_1)

{
  (**(code **)(*param_1 + 0x10))(param_1,0);
  operator_delete(param_1);
  return;
}


// ==== ATL::CComTypeInfoHolder::stringdispid::`vector_deleting_destructor' @ 14007297c  void * `vector_deleting_destructor'(stringdispid * this, uint param_1)

/* Library Function - Single Match
    public: void * __ptr64 __cdecl ATL::CComTypeInfoHolder::stringdispid::`vector deleting
   destructor'(unsigned int) __ptr64
   
   Library: Visual Studio 2008 Release */

void * __thiscall
ATL::CComTypeInfoHolder::stringdispid::_vector_deleting_destructor_(stringdispid *this,uint param_1)

{
  if ((param_1 & 2) == 0) {
    Ordinal_6(*(undefined8 *)this);
    if ((param_1 & 1) != 0) {
      operator_delete(this);
    }
  }
  else {
    _eh_vector_destructor_iterator_
              (this,0x10,*(int *)(this + -8),(_func_void_void_ptr *)&LAB_140072970);
    if ((param_1 & 1) != 0) {
      operator_delete(this + -8);
    }
    this = this + -8;
  }
  return this;
}


// ==== std::_Iterator_base::_Has_container @ 140077a30  bool _Has_container(_Iterator_base * this)

/* Library Function - Single Match
    public: bool __cdecl std::_Iterator_base::_Has_container(void)const __ptr64
   
   Library: Visual Studio 2008 Debug */

bool __thiscall std::_Iterator_base::_Has_container(_Iterator_base *this)

{
  return *(longlong *)this != 0;
}


// ==== std::tr1::_Ref_count<struct_NodeInfo>::vf_0x8 @ 140080b40  undefined vf_0x8(longlong * param_1)

void std::tr1::_Ref_count<struct_NodeInfo>::vf_0x8(longlong *param_1)

{
  if (param_1 != (longlong *)0x0) {
    (**(code **)(*param_1 + 0x10))(param_1,1);
  }
  return;
}


// ==== std::tr1::_Ref_count<struct_NodeInfo>::vf_0x10 @ 140081b80  undefined8 * vf_0x10(undefined8 * param_1, byte param_2)

undefined8 * std::tr1::_Ref_count<struct_NodeInfo>::vf_0x10(undefined8 *param_1,byte param_2)

{
  *param_1 = _Ref_count_base::vftable;
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== std::tr1::_Ref_count<struct_NodeInfo>::vf_0x0 @ 140083aa0  undefined vf_0x0(longlong param_1)

void std::tr1::_Ref_count<struct_NodeInfo>::vf_0x0(longlong param_1)

{
  longlong *plVar1;
  int *piVar2;
  void *pvVar3;
  longlong *plVar4;
  
  pvVar3 = *(void **)(param_1 + 8);
  if (pvVar3 != (void *)0x0) {
    plVar4 = *(longlong **)((longlong)pvVar3 + 0x20);
    if (plVar4 != (longlong *)0x0) {
      LOCK();
      plVar1 = plVar4 + 2;
      *(int *)plVar1 = (int)*plVar1 + -1;
      UNLOCK();
      if ((int)*plVar1 == 0) {
        (**(code **)*plVar4)(plVar4);
        LOCK();
        piVar2 = (int *)((longlong)plVar4 + 0x14);
        *piVar2 = *piVar2 + -1;
        UNLOCK();
        if (*piVar2 == 0) {
          (**(code **)(*plVar4 + 8))(plVar4);
        }
      }
    }
    operator_delete(pvVar3);
  }
  return;
}


// ==== std::tr1::_Ref_count<class_CMapStaticData>::vf_0x8 @ 14008df80  undefined vf_0x8(longlong * param_1)

void std::tr1::_Ref_count<class_CMapStaticData>::vf_0x8(longlong *param_1)

{
  if (param_1 != (longlong *)0x0) {
    (**(code **)(*param_1 + 0x10))(param_1,1);
  }
  return;
}


// ==== std::tr1::_Ref_count<class_CMapStaticData>::vf_0x10 @ 14008e7f0  undefined8 * vf_0x10(undefined8 * param_1, byte param_2)

undefined8 * std::tr1::_Ref_count<class_CMapStaticData>::vf_0x10(undefined8 *param_1,byte param_2)

{
  *param_1 = _Ref_count_base::vftable;
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== std::tr1::_Ref_count<class_CMapStaticData>::vf_0x0 @ 140092320  undefined vf_0x0(longlong param_1)

void std::tr1::_Ref_count<class_CMapStaticData>::vf_0x0(longlong param_1)

{
  void *pvVar1;
  
  pvVar1 = *(void **)(param_1 + 8);
  if (pvVar1 != (void *)0x0) {
    FUN_1400921d0((longlong)pvVar1);
    operator_delete(pvVar1);
  }
  return;
}


// ==== std::tr1::_Ref_count<class_CLayer>::vf_0x0 @ 1400939b0  undefined vf_0x0(longlong param_1)

void std::tr1::_Ref_count<class_CLayer>::vf_0x0(longlong param_1)

{
  operator_delete(*(void **)(param_1 + 8));
  return;
}


// ==== std::tr1::_Ref_count<class_CLayer>::vf_0x8 @ 1400939c0  undefined vf_0x8(longlong * param_1)

void std::tr1::_Ref_count<class_CLayer>::vf_0x8(longlong *param_1)

{
  if (param_1 != (longlong *)0x0) {
    (**(code **)(*param_1 + 0x10))(param_1,1);
  }
  return;
}


// ==== std::tr1::_Ref_count<class_CLayer>::vf_0x10 @ 140093a00  undefined8 * vf_0x10(undefined8 * param_1, byte param_2)

undefined8 * std::tr1::_Ref_count<class_CLayer>::vf_0x10(undefined8 *param_1,byte param_2)

{
  *param_1 = _Ref_count_base::vftable;
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== std::tr1::_Ref_count<class_CTerrainObjPart>::vf_0x0 @ 140093c40  undefined vf_0x0(longlong param_1)

void std::tr1::_Ref_count<class_CTerrainObjPart>::vf_0x0(longlong param_1)

{
  undefined8 *puVar1;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  return;
}


// ==== std::tr1::_Ref_count<class_CTerrainObjPart>::vf_0x8 @ 140093c60  undefined vf_0x8(longlong * param_1)

void std::tr1::_Ref_count<class_CTerrainObjPart>::vf_0x8(longlong *param_1)

{
  if (param_1 != (longlong *)0x0) {
    (**(code **)(*param_1 + 0x10))(param_1,1);
  }
  return;
}


// ==== std::tr1::_Ref_count<class_CTerrainObjPart>::vf_0x10 @ 140093d90  undefined8 * vf_0x10(undefined8 * param_1, byte param_2)

undefined8 * std::tr1::_Ref_count<class_CTerrainObjPart>::vf_0x10(undefined8 *param_1,byte param_2)

{
  *param_1 = _Ref_count_base::vftable;
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== std::tr1::_Ref_count<class_CTerrainObj>::vf_0x0 @ 1400949c0  undefined vf_0x0(longlong param_1)

void std::tr1::_Ref_count<class_CTerrainObj>::vf_0x0(longlong param_1)

{
  undefined8 *puVar1;
  
  puVar1 = *(undefined8 **)(param_1 + 8);
  if (puVar1 != (undefined8 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  return;
}


// ==== std::tr1::_Ref_count<class_CTerrainObj>::vf_0x8 @ 1400949e0  undefined vf_0x8(longlong * param_1)

void std::tr1::_Ref_count<class_CTerrainObj>::vf_0x8(longlong *param_1)

{
  if (param_1 != (longlong *)0x0) {
    (**(code **)(*param_1 + 0x10))(param_1,1);
  }
  return;
}


// ==== std::tr1::_Ref_count<class_CTerrainObj>::vf_0x10 @ 140094bf0  undefined8 * vf_0x10(undefined8 * param_1, byte param_2)

undefined8 * std::tr1::_Ref_count<class_CTerrainObj>::vf_0x10(undefined8 *param_1,byte param_2)

{
  *param_1 = _Ref_count_base::vftable;
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


