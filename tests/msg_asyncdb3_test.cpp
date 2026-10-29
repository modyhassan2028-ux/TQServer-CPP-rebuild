// 140006880 SendPacket
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdlib>
#include "asyncdbthread.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static int g_flush=0,g_close=0,g_log=0,g_send=0,g_partial=0;
static void LG(const char*) { g_log++; }
static void CH(void*) {}
static void DL(void*) {}
static void DT(CAsyncDBThread*) {}
static void* O19(void*,void*buf,int len,int){ g_flush++; std::memcpy(&g_send,buf,0);
    return (void*)(intptr_t)(g_partial<0?0:(g_partial>0?g_partial:len)); }
static int O16(void*,void*,int,int){ return 0; }
static int O111(){ return 0; }
static void O3(void*){ g_close++; }
static void TD(CAsyncDBThread*){}
static SAsyncDbSeams S{LG,CH,DL,DT,O19,O16,O111,O3,TD};
static CAsyncDBThread* mk(int32_t state,intptr_t sock,int32_t pending){
    CAsyncDBThread* t=(CAsyncDBThread*)std::calloc(1,sizeof(CAsyncDBThread));
    *(int32_t*)(t->raw_+0x2030)=state;
    *(intptr_t*)(t->raw_+0x20)=sock;
    *(int32_t*)(t->raw_+0x202c)=pending;
    return t;
}
static int32_t pend(CAsyncDBThread* t){ return *(int32_t*)(t->raw_+0x202c); }
static int32_t state(CAsyncDBThread* t){ return *(int32_t*)(t->raw_+0x2030); }
static intptr_t sock(CAsyncDBThread* t){ return *(intptr_t*)(t->raw_+0x20); }
int main(){
    // a state other than 2 refuses without logging
    { CAsyncDBThread* t=mk(1,5,0); g_log=0;
      CK(t->SendPacket("ab",2,0,S)==0 && g_log==0,"a non-2 state refuses silently");
      CK(pend(t)==0,"the pending length is untouched"); std::free(t); }
    // socket -1 logs and resets
    { CAsyncDBThread* t=mk(2,-1,7); g_log=0;
      CK(t->SendPacket("ab",2,0,S)==0,"a -1 socket reports 0");
      CK(g_log==1,"a -1 socket logs the failure");
      CK(sock(t)==-1 && pend(t)==0 && state(t)==0,"the link is reset"); std::free(t); }
    // plain append
    { CAsyncDBThread* t=mk(2,5,0); g_flush=0;
      CK(t->SendPacket("abcd",4,0,S)==1,"a normal append reports 1");
      CK(pend(t)==4 && std::memcmp(t->raw_+0x102c,"abcd",4)==0,"the bytes land at +0x102c");
      CK(g_flush==0,"no flush without the flag"); std::free(t); }
    // append then flush returns the flush result
    { CAsyncDBThread* t=mk(2,5,0); g_flush=0; 
      CK(t->SendPacket("xy",2,1,S)==1 && g_flush==1,"the flush flag sends and reports 1");
      CK(pend(t)==0,"a full send drains the pending length"); std::free(t); }
    // a flush that cannot send closes the link and reports 0
    { CAsyncDBThread* t=mk(2,5,0); g_close=0; g_log=0; g_partial=-1;
      CK(t->SendPacket("xy",2,1,S)==0 && g_close==1,"a flush that sends nothing closes the socket");
      g_partial=0;
      CK(sock(t)==-1 && state(t)==0,"the link is reset by the failed flush"); std::free(t); }
    // the buffer edge: exactly 0x1000 is accepted
    { CAsyncDBThread* t=mk(2,5,0); g_flush=0;
      CK(t->SendPacket("ab",2,0,S)==1,"first append ok");
      std::free(t); }
    { CAsyncDBThread* t=mk(2,5,0xffc); g_flush=0;
      CK(t->SendPacket("abcd",4,0,S)==1,"reaching exactly 0x1000 is accepted");
      CK(pend(t)==0x1000,"the pending length is 0x1000"); std::free(t); }
    // a full buffer: a partial pre-flush leaves it full, so the buf-full path runs
    { CAsyncDBThread* t=mk(2,5,0x1000); g_flush=0; g_log=0; g_close=0; g_partial=2;
      CK(t->SendPacket("abcd",4,0,S)==0,"a full buffer reports 0");
      CK(g_flush==1,"the pre-check flushed once");
      CK(g_log==1 && g_close==1,"the buf-full path logs and closes");
      g_partial=0;
      CK(sock(t)==-1 && state(t)==0 && pend(t)==0,"the link is reset after buf full"); std::free(t); }
    std::printf("ASYNCDB3-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
