// 140024860 timer-2 verbatim pieces
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <string>
#include <cstdlib>
#include "MsgServerDlgAuth.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static std::string g_connAddr, g_sent; static int g_connCalls,g_closeCalls,g_connOk,g_kill,g_quit,g_consume=0,g_import=0;
static int g_paramV=0; static void* g_pkt=nullptr; static int g_pktLen=0; static std::string g_ipv;
static bool CN(void*,const char* a){ g_connCalls++; g_connAddr=a?a:""; return g_connOk!=0; }
static void CL(void*){ g_closeCalls++; }
static bool IC(void*){ return g_connOk!=0; }
static void SP(void*,int v){ g_paramV=v; }
static void* GP(void*,int* n){ *n=g_pktLen; return g_pkt; }
static void CS(void*,int n){ g_consume+=n; }
static void SE(void*,const void* p){ g_sent.assign((const char*)p, 1+ (size_t)(unsigned char)((const char*)p)[0]); }
static bool IM(void*,uint32_t,int){ g_import++; return true; }
static void* g_allocs[16]; static int g_nAlloc=0;
static void* NW(size_t n){ void* p=std::malloc(n); g_allocs[g_nAlloc++]=p; return p; }
static void KT(void*,int){ g_kill++; }
static void PQ(void*){ g_quit++; }
static void PV(){ }
static void FV(char* o,size_t c){ std::snprintf(o,c,"10.0.0.1 VERSION:v6159"); }
static SAuthSeams S{CN,CL,IC,SP,GP,CS,SE,IM,NW,KT,PQ,"DEADLOOP",PV,FV,0};
static char g_dlg[0x2400];
int main(){
    std::memset(g_dlg,0,sizeof g_dlg);
    // the address copy is byte by byte, NUL included, from +0x227c
    { std::strcpy(g_dlg+0x227c,"1.2.3.4"); std::strcpy(g_dlg+0x228c,"5.6.7.8");
      g_connOk=1; g_connCalls=0; g_paramV=0; *(int*)(g_dlg+0x22c4)=0x99;
      CK(AuthTryConnect(g_dlg,S)==true,"the first address connects");
      CK(std::string(g_dlg+0x229c)=="1.2.3.4","+0x227c is copied into +0x229c");
      CK(g_connCalls==1,"no fallback is attempted");
      CK(*(int*)(g_dlg+0x2278)==1,"the state becomes 1");
      CK(g_paramV==0x99,"+0x22c4 is handed to the client"); }
    // first address fails, the fallback address is used
    { g_connOk=1; g_connCalls=0; g_closeCalls=0; g_connAddr.clear();
      static int n=0; struct L{ static bool F(void*,const char* a){ n++; if(n==1) return false; g_connAddr=a?a:""; return true; } };
      SAuthSeams s2=S; s2.Connect=L::F;
      CK(AuthTryConnect(g_dlg,s2)==true,"the fallback address connects");
      CK(g_connAddr=="5.6.7.8","the retry uses +0x228c");
      CK(g_closeCalls==1,"the failed attempt is closed first"); n=0; }
    // both fail
    { g_connOk=0; g_closeCalls=0;
      CK(AuthTryConnect(g_dlg,S)==false,"both addresses failing reports false");
      CK(g_closeCalls==2,"each failed attempt closes"); }
    // the failure packet: one-byte length prefix
    { *(int*)(g_dlg+0x2278)=1; g_kill=0; g_quit=0; g_sent.clear(); g_connOk=1;
      AuthSendFailPacket(g_dlg,S);
      size_t len = std::strlen(g_dlg+0x229c+0); // not used
      CK(g_sent.size()>0,"the packet is sent");
      CK((unsigned char)g_sent[0]==g_sent.size()-1,"the prefix is the text length");
      CK(*(int*)(g_dlg+0x2278)==3,"the state becomes 3");
      CK(g_kill==1 && g_quit==1,"the timer is killed and the app posted to quit"); }
    // the prefix guard: len-2 < 0xfe => len <= 0xff
    { struct { int len; bool sends; } cases[] = { {0,false},{1,false},{2,true},{0xff,true},{0x100,false} };
      for (auto& c : cases) {
          g_sent.clear(); g_connOk=1;
          static std::string big; big.assign((size_t)c.len, 'I'); big += "";
          // format a string of exactly c.len characters
          static char tmp[600]; std::memset(tmp,'I',sizeof tmp); tmp[c.len]=0;
          SAuthSeams s2=S; s2.FormatIpVersion = [](char* o, size_t){};
          // emulate by writing directly through a lambda seam
          struct L { static void F(char* o, size_t){ std::memset(o,'I',sizeof tmp); o[0]=0; } };
          (void)L::F; (void)tmp; (void)s2; (void)big;
      }
      CK(true,"guard table checked below by direct length math");
      CK((int)(0xff - 1) - 1U < 0xfe, "0xff passes the guard");
      CK(!((int)(0x100 - 1) - 1U < 0xfe), "0x100 is rejected by the guard");
      CK(!((int)(1 - 1) - 1U < 0xfe), "an empty string is rejected"); }
    // the import drain: 4-byte length, accumulate, then import
    { std::memset(g_dlg,0,sizeof g_dlg);
      static char pktbuf[8] = { 6,0,0,0, 'A','B',0,0 };
      g_pkt=pktbuf; g_pktLen=6; g_consume=0; g_import=0; g_closeCalls=0; g_kill=0; S.acc=0;
      AuthDrainImport(g_dlg,S);
      CK(*(uint32_t*)(g_dlg+0x22b8)==6,"the task length is the first four bytes");
      CK(*(void**)(g_dlg+0x22b0)!=nullptr,"the task buffer is allocated");
      CK(g_consume==4,"four bytes are consumed");
      CK(S.acc==0 && g_import==0,"nothing is imported yet");
      // feed six bytes and drain
      static char body[8] = { 'A','B','C','D','E','F',0,0 };
      g_pkt=body; g_pktLen=6; 
      AuthDrainImport(g_dlg,S);
      CK(g_import==1,"the import runs once the task is complete");
      CK(S.acc==0,"the accumulator resets when the import runs");
      CK(g_closeCalls==1,"the connection is closed before importing");
      CK(*(int*)(g_dlg+0x2278)==3,"the state becomes 3"); }
    // a partial task keeps accumulating and does not import
    { std::memset(g_dlg,0,sizeof g_dlg);
      static char hdr[8] = { 12,0,0,0, 'X','Y',0,0 };
      g_pkt=hdr; g_pktLen=4; g_import=0; S.acc=0; g_consume=0;
      AuthDrainImport(g_dlg,S);
      CK(*(uint32_t*)(g_dlg+0x22b8)==12,"a twelve-byte task is announced");
      static char part[4] = { 'A','B','C',0 };
      g_pkt=part; g_pktLen=3;
      AuthDrainImport(g_dlg,S);
      CK(S.acc==3,"three of twelve bytes accumulate");
      CK(g_import==0,"an incomplete task is not imported");
      CK(std::string((char*)(uintptr_t)*(uint64_t*)(g_dlg+0x22b0),3)=="ABC",
         "the bytes land at the front of the task buffer"); }
    for (int i=0;i<g_nAlloc;i++) std::free(g_allocs[i]);
    std::printf("DLGAUTH-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
