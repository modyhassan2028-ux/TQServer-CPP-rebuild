// 140509280 CreateObject + 14050a570 CMD5Checksum::Init
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdlib>
#include "peimage.h"
#include "md5.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
static int g_alloc=0,g_log=0;
static void* AL(size_t n){ g_alloc++; return std::malloc(n); }
static void LG(const char*){ g_log++; }
static int g_desV=0,g_md5V=0,g_stdV=0;
static SFactorySeams F{};
int main(){
    F.Log=LG; F.Alloc=AL; F.desVftable=&g_desV; F.md5Vftable=&g_md5V; F.md5StandardVftable=&g_stdV;
    // kind 0: a 0x890 DES object carrying DES::vftable
    { void* out=nullptr; g_alloc=0;
      void* p=CPEImage::CreateObject(0,&out,F);
      CK(p!=nullptr && out==p,"kind 0 fills the out slot");
      CK(*(void**)p==&g_desV,"kind 0 stores the DES vftable");
      CK(g_alloc==1,"one allocation for DES"); std::free(p); }
    // kind 1: MD5 seeded
    { void* out=nullptr; g_alloc=0;
      CMD5Checksum* p=(CMD5Checksum*)CPEImage::CreateObject(1,&out,F);
      CK(p!=nullptr && out==p,"kind 1 fills the out slot");
      CK(p->vft_==&g_md5V,"kind 1 keeps the MD5 vftable");
      CK(p->h0_==0x67452301 && p->h1_==0xefcdab89 && p->h2_==0x98badcfe && p->h3_==0x10325476,
         "kind 1 seeds the MD5 IV");
      CK(p->zero1_==0 && p->zero8_==0 && p->at48_==0 && p->at4c_==0,"kind 1 clears the state");
      std::free(p); }
    // kind 2: MD5 then the standard vftable on top
    { void* out=nullptr;
      CMD5Checksum* p=(CMD5Checksum*)CPEImage::CreateObject(2,&out,F);
      CK(p!=nullptr && out==p,"kind 2 fills the out slot");
      CK(p->vft_==&g_stdV,"kind 2 overwrites the vftable");
      CK(p->h0_==0x67452301,"kind 2 is still seeded");
      std::free(p); }
    // kind 3 leaves the slot untouched (RAW hole) and returns null
    { void* out=(void*)0x77;
      CK(CPEImage::CreateObject(3,&out,F)==nullptr,"kind 3 reports null");
      CK(out==(void*)0x77,"kind 3 leaves the out slot untouched"); }
    // anything else zeroes the slot
    { void* out=(void*)0x77; std::free;
      CK(CPEImage::CreateObject(4,&out,F)==nullptr && out==nullptr,"kind 4 zeroes the out slot");
      out=(void*)0x77;
      CK(CPEImage::CreateObject(-1,&out,F)==nullptr && out==nullptr,"a negative kind zeroes the out slot"); }
    // the ctor is usable on its own
    { CMD5Checksum m; std::memset(&m,0xFF,sizeof m);
      CK(CMD5Checksum::Init(&m,&g_md5V)==&m,"Init returns self");
      CK(m.vft_==&g_md5V && m.at4c_==0 && m.h3_==0x10325476,"Init writes the same layout standalone"); }
    std::printf("PEIMAGE3-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
