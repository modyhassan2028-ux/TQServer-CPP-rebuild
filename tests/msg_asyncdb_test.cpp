// asyncdbthread.cpp: 1400018c0 / 1400029f0 / 140026a60 / 140005c70
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "asyncdbthread.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static SAsyncDbSeams g{};
static int g_log=0,g_del=0,g_dtor=0,g_close=0; static void* g_closed=nullptr;
static void LG(const char*){ g_log++; }
static void DE(void*){ g_del++; }
static void DT(CAsyncDBThread*){ g_dtor++; }
static void CH(void* h){ g_close++; g_closed=h; }
static void* O19(void*,void*,int,int){ return nullptr; }
int main(){
    g.Log=LG; g.CloseHandle=CH; g.Delete=DE; g.Dtor=DT; g.Ordinal19=O19;
    // instance getter starts null
    CK(CAsyncDBThread::Instance()==nullptr,"instance starts null");
    // destroy with no instance is a no-op
    CAsyncDBThread::DestroyInstance(g);
    CK(g_del==0 && g_close==0,"destroy without instance does nothing");
    static CAsyncDBThread t;
    std::memset(&t,0,sizeof t);
    CAsyncDBThread::InstanceRef(g)=&t;
    CK(CAsyncDBThread::Instance()==&t,"instance returns the stored pointer");
    // a set handle is closed, then the object is deleted and the pointer cleared
    *(void**)(t.raw_+8)=(void*)0xabc;
    CAsyncDBThread::DestroyInstance(g);
    CK(g_close==1 && g_closed==(void*)0xabc,"handle at +0x08 is closed");
    CK(g_del==1 && CAsyncDBThread::Instance()==nullptr,"object deleted and pointer cleared");
    // null handle must not be closed
    static CAsyncDBThread t2; std::memset(&t2,0,sizeof t2);
    CAsyncDBThread::InstanceRef(g)=&t2; g_close=0; g_del=0;
    CAsyncDBThread::DestroyInstance(g);
    CK(g_close==0 && g_del==1,"null handle skips CloseHandle");
    // deleting destructor honours the flag bit
    static CAsyncDBThread t3; std::memset(&t3,0,sizeof t3);
    g_dtor=0; g_del=0;
    CK(CAsyncDBThread::DeleteSelf(&t3,0,g)==&t3,"DeleteSelf returns self");
    CK(g_dtor==1 && g_del==0,"flag 0 skips the delete");
    CK(CAsyncDBThread::DeleteSelf(&t3,1,g)==&t3,"DeleteSelf returns self with flag");
    CK(g_dtor==2 && g_del==1,"flag 1 frees the object");
    CK(CAsyncDBThread::DeleteSelf(&t3,0x10,g)==&t3 && g_del==1,"only bit 0 frees");
    // ClearPacket
    CAsyncDBThread c; std::memset(&c,0,sizeof c);
    *(int*)(c.raw_+0x2030)=1; g_log=0;
    CK(c.ClearPacket(5,g)==0,"state other than 2 returns 0");
    CK(g_log==1,"an overrun is logged even outside state 2");
    *(int*)(c.raw_+0x2030)=2;
    *(int*)(c.raw_+0x1028)=10;
    for(int i=0;i<10;i++) c.raw_[0x28+i]=(uint8_t)('A'+i);
    CK(c.ClearPacket(4,g)==1,"consuming part of the buffer succeeds");
    CK(*(int*)(c.raw_+0x1028)==6,"length drops by nLen");
    CK(c.raw_[0x28]=='E' && c.raw_[0x2d]=='J',"the remainder shifts to the head");
    CK(c.ClearPacket(6,g)==1 && *(int*)(c.raw_+0x1028)==0,"exact drain leaves zero");
    *(int*)(c.raw_+0x1028)=3;
    CK(c.ClearPacket(5,g)==0,"overrun reports 0");
    CK(*(int*)(c.raw_+0x1028)==0,"overrun clamps the length to 0");
    CK(c.ClearPacket(0,g)==1,"zero length succeeds on an empty buffer");
    std::printf("ASYNCDB-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
