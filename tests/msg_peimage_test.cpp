// peimage.cpp: 140509760 AttachImage / 140509820 GetMaxAlignedSize / 1405094d0
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <vector>
#include <cstdlib>
#include <sys/mman.h>
#include "peimage.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
// minimal PE32 image builder
struct Img {
    std::vector<uint8_t> b;
    explicit Img(uint32_t size=0x800) : b(size,0) {}
    uint8_t* p(){ return b.data(); }
    void mz(int32_t lfanew){ *(uint16_t*)p()=0x5a4d; std::memcpy(p()+0x3c,&lfanew,4); }
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
    // section header at nt+0x108 : +0x08 VirtualSize, +0x0c VirtualAddress,
    // +0x10 SizeOfRawData, +0x14 PointerToRawData. The bound loop starts at
    // nt+0x118 == first header + 0x10, so it checks raw_end against the size.
    void sec(int32_t lfanew,int i,int32_t vsize,int32_t vaddr,int32_t rsize,int32_t raw){
        intptr_t h=(intptr_t)(nt(lfanew)+0x108)+(intptr_t)i*0x28;
        std::memcpy((void*)(h+0x08),&vsize,4); std::memcpy((void*)(h+0x0c),&vaddr,4);
        std::memcpy((void*)(h+0x10),&rsize,4); std::memcpy((void*)(h+0x14),&raw,4);
    }
};
static int g_alloc=0,g_free=0,g_protect=0,g_resolve=1,g_entryRet=1,g_entryCalls=0;
// the RAW truncates the section pointers to 32 bits, so the image has to sit
// below 4 GB, exactly like VirtualAlloc guarantees on the original host
static uint8_t* g_low=(uint8_t*)mmap((void*)0x10000000,0x20000,PROT_READ|PROT_WRITE,
    MAP_PRIVATE|MAP_ANONYMOUS|MAP_FIXED,-1,0);
static void* AL(size_t){ g_alloc++; return g_low+0x10000; }
static int PR(void*,size_t,uint32_t){ g_protect++; return 1; }
static void FR(void*){ g_free++; }
static int RI(CPEImage*,void*){ return g_resolve; }
static int CE(intptr_t,void*,int a,int){ g_entryCalls++; return (a==1)?g_entryRet:1; }
static SLoadSeams L{AL,PR,FR,RI,CE};
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
    // section bounds: SizeOfRawData + PointerToRawData must fit in the file
    { Img g(0x800); CPEImage im; std::memset(&im,0,sizeof im);
      g.mz(0x80); g.pe(0x80,0x2002,0xf0,2);
      g.sec(0x80,0,0x100,0x1000,0x200,0x400);
      g.sec(0x80,1,0x100,0x2000,0x300,0x600);     // 0x600+0x300 = 0x900 > 0x800
      CK(im.AttachImage(g.p(),0x800)==0,"a section whose raw end exceeds the file is rejected");
      Img h(0x1000); CPEImage im2; std::memset(&im2,0,sizeof im2);
      h.mz(0x80); h.pe(0x80,0x2002,0xf0,2);
      h.sec(0x80,0,0x100,0x1000,0x200,0x400);
      h.sec(0x80,1,0x100,0x2000,0x300,0x600);
      CK(im2.AttachImage(h.p(),0x1000)==1,"a file big enough for both sections is accepted"); }
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
    // ---- CopySections
    { Img f(0x1000); CPEImage im; std::memset(&im,0,sizeof im);
      f.mz(0x80); f.pe(0x80,0x2002,0xf0,2);
      f.sec(0x80,0,0x100,0x1000,0x200,0x400);
      f.sec(0x80,1,0x100,0x2000,0x100,0x600);
      std::memset(f.p()+0x400,0xAA,0x200);
      std::memset(f.p()+0x600,0xBB,0x100);
      CK(im.AttachImage(f.p(),0x1000)==1,"copy source attaches");
      CK(g_low!=(uint8_t*)MAP_FAILED,"low image mapped");
      uint8_t* dst=g_low;
      std::memset(dst,0,0x4000);
      std::memcpy(g_low+0x8000,f.p(),0x1000);
      im.CopySections(dst, g_low+0x8000);
      CK(im.base_==(intptr_t)dst,"base re-points at the new image");
      CK(im.nt_==(intptr_t)dst+0x80,"NT re-read from the new image");
      CK(im.sections_==im.nt_+0x108,"sections re-point past the new headers");
      CK(dst[0]==0x4d && dst[1]==0x5a,"DOS header copied");
      CK(dst[0x1000]==0xAA && dst[0x11ff]==0xAA,"section 1 raw data copied");
      CK(dst[0x2000]==0xBB && dst[0x20ff]==0xBB,"section 2 raw data copied"); }
    // ---- Load
    g_alloc=0; g_free=0; g_protect=0; g_resolve=1; g_entryRet=1; g_entryCalls=0;
    { Img f(0x1000); CPEImage im; std::memset(&im,0,sizeof im);
      f.mz(0x80); f.pe(0x80,0x2002,0xf0,1);
      f.sec(0x80,0,0x100,0x1000,0x200,0x400);
      int32_t ep=0x1000;
      std::memcpy((void*)(f.nt(0x80)+0x28),&ep,4);       // entry RVA at nt+0x28
      std::memcpy(g_low+0x8000,f.p(),0x1000);
      CK(im.Load(g_low+0x8000,0x1000,L)==1,"load succeeds when the entry accepts");
      CK(g_alloc==1 && g_protect==1,"one allocation and one protect");
      CK(im.loaded_==1 && im.image_!=0,"the image is recorded");
      CK(im.entry_==im.image_+0x1000,"entry is image plus the RVA");
      CK(g_entryCalls==1,"the entry is called once with 1"); }
    { Img f(0x1000); CPEImage im; std::memset(&im,0,sizeof im);
      f.mz(0x80); f.pe(0x80,0x2002,0xf0,1);
      f.sec(0x80,0,0x100,0x1000,0x200,0x400);
      g_alloc=0; g_free=0; g_entryRet=0; g_entryCalls=0;
      std::memcpy(g_low+0x8000,f.p(),0x1000);
      CK(im.Load(g_low+0x8000,0x1000,L)==0,"a rejecting entry fails the load");
      CK(g_free==1 && g_entryCalls==2,"the image is freed after the shutdown call");
      CK(im.loaded_==0 && im.entry_==0,"nothing is recorded on failure"); }
    { CPEImage im; std::memset(&im,0,sizeof im);
      im.image_=0x1234; g_alloc=0;
      CK(im.Load((void*)0x1000,0x1000,L)==0 && g_alloc==0,"an occupied slot refuses to load"); }
    { CPEImage im; std::memset(&im,0,sizeof im);
      g_resolve=0; g_alloc=0; g_free=0;
      Img f(0x1000); f.mz(0x80); f.pe(0x80,0x2002,0xf0,0);
      std::memcpy(g_low+0x8000,f.p(),0x1000);
      CK(im.Load(g_low+0x8000,0x1000,L)==0 && g_free==1,"a failed resolve frees and reports 0"); }
    std::printf("PEIMAGE-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
