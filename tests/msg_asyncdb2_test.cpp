// asyncdbthread.cpp: 140005d60 FlushPending / 140006730 GetPacket
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "asyncdbthread.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static SAsyncDbSeams g{};
static int g_sendRet=0,g_recvRet=0,g_err=0,g_sent=0,g_recv=0,g_close=0,g_tear=0,g_log=0;
static void LG(const char*){ g_log++; }
static void DE(void*){}
static void DT(CAsyncDBThread*){}
static void CH(void*){}
static void* O19(void*,void*,int,int){ g_sent++; return (void*)(intptr_t)g_sendRet; }
static int O16(void*,void*,int,int){ g_recv++; return g_recvRet; }
static int O111(){ return g_err; }
static void O3(void*){ g_close++; }
static void TD(CAsyncDBThread*){ g_tear++; }
static void RESET(){ g_sendRet=0; g_recvRet=0; g_err=0; g_sent=0; g_recv=0;
                     g_close=0; g_tear=0; g_log=0; }
int main(){
    g.Log=LG; g.CloseHandle=CH; g.Delete=DE; g.Dtor=DT; g.Ordinal19=O19;
    g.Ordinal16=O16; g.Ordinal111=O111; g.Ordinal3=O3; g.Teardown=TD;
    CAsyncDBThread c; std::memset(&c,0,sizeof c);
    // ---- FlushPending
    RESET(); *(int*)(c.raw_+0x2030)=1; *(int*)(c.raw_+0x202c)=4;
    CK(c.FlushPending(g)==false && g_sent==0,"wrong state does not flush");
    *(int*)(c.raw_+0x2030)=2; *(int*)(c.raw_+0x202c)=0;
    RESET();
    CK(c.FlushPending(g)==true && g_sent==0,"nothing pending reports drained");
    // partial send keeps the tail
    *(int*)(c.raw_+0x202c)=10;
    for(int i=0;i<10;i++) c.raw_[0x102c+i]=(uint8_t)('a'+i);
    RESET(); g_sendRet=4;
    CK(c.FlushPending(g)==false && g_sent==1,"partial send reports not drained");
    CK(*(int*)(c.raw_+0x202c)==6,"pending drops by the sent count");
    CK(c.raw_[0x102c]=='e' && c.raw_[0x1031]=='j',"the unsent tail shifts to the front");
    // exact send drains
    RESET(); g_sendRet=6;
    CK(c.FlushPending(g)==true && *(int*)(c.raw_+0x202c)==0,"exact send drains");
    // failed send: 0x2746 is silent, socket closed and parked, lengths wiped
    *(int*)(c.raw_+0x202c)=3; *(int64_t*)(c.raw_+0x20)=42; *(int*)(c.raw_+0x1028)=7;
    RESET(); g_sendRet=-1; g_err=0x2746;
    CK(c.FlushPending(g)==false,"failed send reports false");
    CK(g_log==0,"0x2746 is not logged");
    CK(g_close==1 && *(int64_t*)(c.raw_+0x20)==-1,"socket closed and parked at -1");
    CK(*(int*)(c.raw_+0x2030)==0 && *(int*)(c.raw_+0x1028)==0 && *(int*)(c.raw_+0x202c)==0,
       "state and lengths wiped");
    // other errors are logged, and an already parked socket is not closed again
    *(int*)(c.raw_+0x2030)=2; *(int*)(c.raw_+0x202c)=3;
    RESET(); g_sendRet=-1; g_err=0x1234;
    c.FlushPending(g);
    CK(g_log==1 && g_close==0,"unknown error logs without closing a parked socket");
    // ---- GetPacket
    RESET(); uint32_t len=99;
    CK(c.GetPacket(nullptr,1,g)==nullptr && g_log==1,"null out pointer logs and reports null");
    CK(len==99,"null out pointer leaves the caller value alone");
    *(int64_t*)(c.raw_+0x20)=-1; *(int*)(c.raw_+0x2030)=1;
    RESET();
    CK(c.GetPacket(&len,1,g)==nullptr && len==0,"wrong state reports null with length 0");
    *(int*)(c.raw_+0x2030)=2;
    RESET();
    CK(c.GetPacket(&len,1,g)==nullptr,"dead socket reports null");
    CK(g_log==1 && *(int*)(c.raw_+0x2030)==0,"dead socket logs and resets the state");
    // live socket, recv appends
    *(int64_t*)(c.raw_+0x20)=7; *(int*)(c.raw_+0x2030)=2; *(int*)(c.raw_+0x1028)=0;
    RESET(); g_recvRet=5;
    void* p=c.GetPacket(&len,1,g);
    CK(p==(void*)(c.raw_+0x28) && len==5 && g_recv==1,"recv appends and returns the buffer");
    // a zero recv is logged as a close and the teardown runs
    RESET(); g_recvRet=0;
    p=c.GetPacket(&len,1,g);
    CK(p==(void*)(c.raw_+0x28) && g_log==1 && g_tear==1,"zero recv logs the close and tears down");
    // 0x2733 is silent, 0x2746 is silent, others log
    RESET(); g_recvRet=-1; g_err=0x2733;
    c.GetPacket(&len,1,g);
    CK(g_log==0 && g_tear==0,"0x2733 is silent and skips the teardown");
    RESET(); g_recvRet=-1; g_err=0x2746;
    c.GetPacket(&len,1,g);
    CK(g_log==0 && g_tear==1,"0x2746 is silent but tears down");
    RESET(); g_recvRet=-1; g_err=0x99;
    c.GetPacket(&len,1,g);
    CK(g_log==1 && g_tear==1,"other recv errors are logged");
    // fill=0 and a full buffer never read from the socket
    RESET();
    c.GetPacket(&len,0,g);
    CK(g_recv==0,"fill=0 skips the recv");
    *(int*)(c.raw_+0x1028)=0x1000; RESET();
    c.GetPacket(&len,1,g);
    CK(g_recv==0 && len==0x1000,"a full buffer skips the recv");
    std::printf("ASYNCDB2-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
