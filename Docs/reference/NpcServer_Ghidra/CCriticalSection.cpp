// NpcServer.exe :: CCriticalSection  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CCriticalSection::vf_0x30 @ 140003300  undefined8 vf_0x30(void)

undefined8 CCriticalSection::vf_0x30(void)

{
  return 1;
}


// ==== CCriticalSection::vf_0x38 @ 140003350  undefined8 vf_0x38(longlong param_1)

undefined8 CCriticalSection::vf_0x38(longlong param_1)

{
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x10));
  return 1;
}


// ==== CCriticalSection::vf_0x8 @ 140003550  CSyncObject * vf_0x8(CSyncObject * param_1, uint param_2)

CSyncObject * CCriticalSection::vf_0x8(CSyncObject *param_1,uint param_2)

{
  *(undefined ***)param_1 = vftable;
  DeleteCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x10));
  CSyncObject::~CSyncObject(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


// ==== CCriticalSection::Init @ 140004030  int Init(CCriticalSection * this)

/* Library Function - Single Match
    private: int __cdecl CCriticalSection::Init(void) __ptr64
   
   Libraries: Visual Studio 2005 Release, Visual Studio 2008 Release */

int __thiscall CCriticalSection::Init(CCriticalSection *this)

{
  InitializeCriticalSection((LPCRITICAL_SECTION)(this + 0x10));
  return 1;
}


// ==== CCriticalSection::CCriticalSection @ 140004050  undefined CCriticalSection(CCriticalSection * this)

/* Library Function - Single Match
    public: __cdecl CCriticalSection::CCriticalSection(void) __ptr64
   
   Libraries: Visual Studio 2005 Release, Visual Studio 2008 Release */

CCriticalSection * __thiscall CCriticalSection::CCriticalSection(CCriticalSection *this)

{
  int iVar1;
  
  CSyncObject::CSyncObject((CSyncObject *)this,(char *)0x0);
  *(undefined ***)this = vftable;
  iVar1 = Init(this);
  if (iVar1 == 0) {
    AfxThrowMemoryException();
  }
  return this;
}


