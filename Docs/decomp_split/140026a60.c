CAsyncDBThread * FUN_140026a60(CAsyncDBThread *param_1,uint param_2)
{
  CAsyncDBThread::~CAsyncDBThread(param_1);
  if ((param_2 & 1) != 0) {
    operator_delete(param_1);
  }
  return param_1;
}
