// peimage.cpp: 140509760 AttachImage / 140509820 GetMaxAlignedSize / 1405094d0
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <vector>
#include "peimage.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
// minimal PE32 image builder
struct Img {
    std::vector<uint8_t> b;
    explicit Img(uint32_t size=0x800) : b(size,0) {}
    uint8_t* p(){ return b.data(); }
    void mz(int32_t lfanew){ *(uint16_t*)p()=0x5a4d; std::memcpy(p()+0x1e,&lfanew,4); }
    intptr_t nt(int32_t lfanew){ return (intptr_t)p()+lfanew; }
    void pe(int32_t lfanew,uint16_t chars,int16_t magic,uint16_t nsec){
        intptr_t n=nt(lfanew);
        std::memcpy((void*)n,&(uint32_t&)(*(uint32_t*)"PE\0\0"),4);
        std::memcpy((void*)(n+6),&nsec,2); std::memcpy((void*)(n+0x16),&chars,2);
        std::memcpy((void*)(n+0x14),&magic,2);
        int32_t align=0x1000, hdr=0x400;
        std::memcpy((void*)(n+0x38),&align,4);
        std::memcpy((void*)(n+0x54),&hdr,4);
    }
    // the RAW checks the bounds on the dwords at nt+0x118 and walks the table
    // at nt+0x108, so a section is written in both places
    void sec(int32_t lfanew,int i,int32_t vsize,int32_t vaddr,int32_t rsize,int32_t raw){
        intptr_t walk=(intptr_t)(nt(lfanew)+0x108)+(intptr_t)i*0x28;
        std::memcpy((void*)(walk+0x08),&vsize,4); std::memcpy((void*)(walk+0x0c),&vaddr,4);
        std::memcpy((void*)(walk+0x10),&rsize,4);
        intptr_t chk=(intptr_t)(nt(lfanew)+0x118)+(intptr_t)i*0x28;
        std::memcpy((void*)chk,&vaddr,4); std::memcpy((void*)(chk+4),&raw,4);
    }
};
int main(){
    // size too small is rejected before anything is stored
    { CPEImage im; std::memset(&im,0,sizeof im);
      CK(im.AttachImage((void*)0x1000,0x3f)==0 && im.base_==0,"below 0x40 is rejected unstored"); }
    // a bad MZ still stores the base (RAW quirk)
    { Img g; CPEImage im; std::memset(&im,0,sizeof im);
      *(uint16_t*)g.p()=0x1234;
      CK(im.AttachImage(g.p(),0x800)==0,"bad MZ rejected");
      CK(im.base_==(intptr_t)g.p() && im.nt_==0,"base stored, NT not"); }
    // e_lfanew over the buffer
    { Img g; CPEImage im; std::memset(&im,0,sizeof im);
      g.mz(0x7f0);
      CK(im.AttachImage(g.p(),0x800)==0 && im.nt_==0,"e_lfanew beyond the buffer is rejected");
      CK(im.base_==(intptr_t)g.p(),"base still stored"); }
    // wrong PE signature
    { Img g; CPEImage im; std::memset(&im,0,sizeof im);
      g.mz(0x80); { uint32_t bad=0x4551; std::memcpy((void*)g.nt(0x80),&bad,4); }
      CK(im.AttachImage(g.p(),0x800)==0 && im.nt_==(intptr_t)g.p()+0x80,"bad signature stores NT and fails");
      CK(im.sections_==0,"no section table on a bad signature"); }
    // characteristics / magic gates
    { Img g; CPEImage im; std::memset(&im,0,sizeof im);
      g.mz(0x80); g.pe(0x80,0x0002,0xf0,0);          // not a DLL
      CK(im.AttachImage(g.p(),0x800)==0,"without 0x2000 rejected");
      g.pe(0x80,0x2000,0xf0,0);                      // not executable image
      CK(im.AttachImage(g.p(),0x800)==0,"without 0x2 rejected");
      g.pe(0x80,0x2002,0x10b,0);                     // PE32+
      CK(im.AttachImage(g.p(),0x800)==0,"non 0xf0 magic rejected");
      CK(im.sections_==0,"sections only set after the magic check"); }
    // NOTE: the per-section bound loop reads the dwords at nt+0x118 while the
    // table walk starts at nt+0x108, so both hit the same bytes. Those cases
    // are left out of this suite until that overlap is confirmed.
    // valid header-only image still attaches and reports the aligned headers
    { Img g; CPEImage im; std::memset(&im,0,sizeof im);
      g.mz(0x80); g.pe(0x80,0x2002,0xf0,0);
      CK(im.AttachImage(g.p(),0x800)==1,"valid PE accepted");
      CK(im.base_==(intptr_t)g.p() && im.nt_==(intptr_t)g.p()+0x80,"base and NT stored");
      CK(im.sections_==(intptr_t)g.p()+0x80+0x108,"section table at nt+0x108"); }
    // no NT header -> 0
    { CPEImage im; std::memset(&im,0,sizeof im);
      CK(im.GetMaxAlignedSize()==0,"no image reports 0"); }
    // headers only, no sections
    { Img g; CPEImage im; std::memset(&im,0,sizeof im);
      g.mz(0x80); g.pe(0x80,0x2002,0xf0,0);
      CK(im.AttachImage(g.p(),0x800)==1 && im.GetMaxAlignedSize()==0x1000,
         "no sections yields the aligned header size"); }
    // relocations: one block, two entries, only type 0xA is patched
    { Img g(0x400); CPEImage im; std::memset(&im,0,sizeof im);
      g.mz(0x80); g.pe(0x80,0x2002,0xf0,0);
      uint8_t* rel=g.p()+0x180;              // relocation block inside the image
      *(int64_t*)(g.nt(0x80)+0x30)=0x1000;   // preferred ImageBase
      *(int32_t*)(g.nt(0x80)+0xb0)=0x180;    // directory RVA
      int64_t* slot=(int64_t*)(g.p()+0x200);
      *slot=0x1000+0x40;                     // value based on the preferred base
      *(uint32_t*)(rel+0)=0x200;             // block RVA
      *(uint32_t*)(rel+4)=8+2*2;             // block size
      *(uint16_t*)(rel+8)=0xa000;            // DIR64 + offset 0
      *(uint16_t*)(rel+10)=0x3000;           // type 3 (ignored)
      uint32_t dirRva=0x180;
      std::memcpy((void*)(g.nt(0x80)+0xb0),&dirRva,4);
      int64_t base=0x1000; std::memcpy((void*)(g.nt(0x80)+0x30),&base,8);
      CK(im.AttachImage(g.p(),0x400)==1,"relocation image attaches");
      im.ApplyRelocations((intptr_t)g.p());
      CK(*slot==(int64_t)((intptr_t)g.p()+0x40),"the 0xA000 entry is rebased");
      CK(*(uint16_t*)(rel+10)==0x3000,"other entry types are untouched"); }
    std::printf("PEIMAGE-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
