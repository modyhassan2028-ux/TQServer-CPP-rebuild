// 140028960 / 14002ad90
#include <cstdio>
#include <cstdint>
#include "globalmgr.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static int g_destroyCalls=0, g_destroyFlag=-1; static void* g_destroyed=nullptr;
static void DS(void* o,int f){ g_destroyCalls++; g_destroyed=o; g_destroyFlag=f; }
static SGlobalSeams S{DS};
int main(){
    GlobalMgrSlot() = nullptr;
    CK(GetGlobalMgr()==nullptr,"an empty slot reads back as null");
    int objStorage = 0; void* obj = &objStorage;
    GlobalMgrSlot() = obj;
    CK(GetGlobalMgr()==obj,"the getter returns the slot");
    CK(g_destroyCalls==0,"reading never destroys");
    // teardown of a live object
    ResetGlobalMgr(S);
    CK(g_destroyCalls==1,"the teardown destroys once");
    CK(g_destroyed==obj,"the slot object is what gets destroyed");
    CK(g_destroyFlag==1,"the delete flag is 1");
    CK(GlobalMgrSlot()==nullptr,"the slot is cleared");
    CK(GetGlobalMgr()==nullptr,"the getter is empty after teardown");
    // a second teardown does nothing
    ResetGlobalMgr(S);
    CK(g_destroyCalls==1,"an empty slot is not destroyed twice");
    CK(g_destroyFlag==1,"the last flag stays untouched");
    std::printf("GLOBALMGR-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
