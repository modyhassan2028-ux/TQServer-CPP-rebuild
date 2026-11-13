// NpcServer.exe :: CAsyncDBThread  (Ghidra 11.4.2 decompile - pseudo C, not compilable)

// ==== CAsyncDBThread::vf_0x0 @ 140005360  CAsyncDBThread * vf_0x0(CAsyncDBThread * param_1, uint param_2)

CAsyncDBThread * CAsyncDBThread::vf_0x0(CAsyncDBThread *param_1,uint param_2)

{
  CAsyncDBThread::~CAsyncDBThread(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}


