// peimage.cpp: 1405095a0 ResolveImports / 140509380 LookupExport / 140508f60 BootValidate
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <cstdlib>
#include <sys/mman.h>
#include "peimage.h"
using namespace msg;
static int g_fail=0,g_ok=0;
#define CK(c,m) do{ if(c){g_ok++;}else{g_fail++;std::printf("  FAIL %s\n",m);} }while(0)
template <class T> static void put(void* p, size_t off, T v){ std::memcpy((uint8_t*)p+off,&v,sizeof v); }
static uint8_t* LOW=(uint8_t*)mmap((void*)0x10000000,0x80000,PROT_READ|PROT_WRITE,
                                   MAP_PRIVATE|MAP_ANONYMOUS|MAP_FIXED,-1,0);
// --- import seams
static int g_gh=0,g_gpa=0,g_gpao=0,g_haveMod=1,g_haveProc=1;
static void* GH(const char* n){ g_gh++; return (g_haveMod && std::strcmp(n,"KERNEL32.dll")==0)?(void*)0x11:nullptr; }
static void* GP(void* m,const char* n){ g_gpa++; (void)m; return g_haveProc?(void*)0x22:nullptr; }
static void* GPO(void* m,uint16_t o){ g_gpao++; (void)m; return (g_haveProc&&o==7)?(void*)0x33:nullptr; }
static SImportSeams IMP{GH,GP,GPO};
// --- loader seams
static uint8_t* g_img=nullptr;
static int g_create=1,g_setkey=0,g_proc=0,g_destroy=0,g_lib=0,g_log=0,g_parse=1,g_order[4],g_ordn=0;
static void* CO(int kind){ g_create++; return kind==0?(void*)0x44:nullptr; }
static int SK(void*,const char* k){ g_setkey++; g_order[g_ordn++]=1; return k!=nullptr; }
static int PR(void*,void*,uint32_t sz){ g_proc++; g_order[g_ordn++]=2; return (int)sz; }
static void CD(void*){ g_destroy++; g_order[g_ordn++]=3; }
static void* LL(const char*){ g_lib++; return (void*)0x55; }
static void LG(const char*){ g_log++; }
static int PI(CPEImage* im,void* file,uint32_t){ g_parse++; (void)file; im->loaded_=1; im->image_=(intptr_t)g_img; im->nt_=(intptr_t)g_img+0x100; return 1; }
static SLoaderSeams LDR{CO,SK,PR,CD,LL,LG,PI};
// build an export directory with the four loader names at image + 0x200
static void build_exports(uint8_t* img, int nFuncs, const char** names, int drop){
    std::memset(img,0,0x4000);
    put<int32_t>(img,0x20,0);                 // nt placeholder region is not used by the lookup
    int32_t dirRva=0x200;
    // nt at +0x100: export dir RVA/size
    put<uint32_t>(img,0x100+0x88,(uint32_t)dirRva);
    put<uint32_t>(img,0x100+0x8c,0x80);
    uint8_t* d=img+dirRva;
    put<uint32_t>(d,0x10,1);                 // Base = 1
    put<int32_t>(d,0x14,nFuncs);             // NumberOfFunctions
    put<int32_t>(d,0x18,nFuncs-(drop>=0&&drop<3?1:0));  // NumberOfNames
    put<int32_t>(d,0x1c,0x300);              // AddressOfFunctions
    put<int32_t>(d,0x20,0x340);              // AddressOfNames
    put<int32_t>(d,0x24,0x380);              // AddressOfNameOrdinals
    int32_t nameRva=0x400;
    for(int i=0;i<nFuncs;i++){
        put<uint32_t>(img,0x300+i*4,(uint32_t)(0x1000+i*0x10));
        put<int32_t>(img,0x340+i*4,nameRva);
        put<uint16_t>(img,0x380+i*2,(uint16_t)i);
        std::strcpy((char*)(img+nameRva),names[i]);
        nameRva+=(int32_t)std::strlen(names[i])+1;
    }
}
int main(){
    CK(LOW!=(uint8_t*)MAP_FAILED,"low memory mapped");
    g_img=LOW+0x20000;
    // ---- LookupExport by name
    { const char* nm[4]={"CreateMapGroup","CreateWorldKernel","CreateNewMapData","CreateMapGroupDefaultData"};
      build_exports(g_img,4,nm,-1);
      CPEImage im; std::memset(&im,0,sizeof im); im.nt_=(intptr_t)g_img+0x100; im.image_=(intptr_t)g_img; im.loaded_=1;
      CK(im.LookupExport((uintptr_t)"CreateMapGroup")==(intptr_t)g_img+0x1000,"first export resolves");
      CK(im.LookupExport((uintptr_t)"CreateMapGroupDefaultData")==(intptr_t)g_img+0x1030,"last export resolves");
      CK(im.LookupExport((uintptr_t)"Nope")==0,"an unknown name reports 0");
      // ordinal path: value below 0x10000, Base is 1 so ordinal 2 -> index 1
      CK(im.LookupExport(3)==(intptr_t)g_img+0x1020,"ordinal 3 lands on index (0xffff-Base)\&3 = 2");
      put<uint32_t>(g_img,0x300,0x240);   // an rva inside the export directory
      CK(im.LookupExport(1)==0,"an rva inside the export directory is rejected");
      put<uint32_t>(g_img,0x300,0x100);
      CK(im.LookupExport(1)==(intptr_t)g_img+0x100,"an rva below the directory is accepted");
      put<uint32_t>(g_img,0x300,0x1000);
      // gates
      im.loaded_=0; CK(im.LookupExport((uintptr_t)"CreateMapGroup")==0,"the loaded flag gates the lookup");
      im.loaded_=1; put<uint32_t>(g_img,0x100+0x8c,0);
      CK(im.LookupExport((uintptr_t)"CreateMapGroup")==0,"a zero export size gates the lookup"); }
    // ---- ResolveImports
    { std::memset(g_img,0,0x4000);
      put<uint32_t>(g_img,0x100+0x90,0x600);       // import dir RVA
      uint8_t* desc=g_img+0x600;
      put<uint32_t>(desc,0x00,0x700);              // OriginalFirstThunk
      put<uint32_t>(desc,0x0c,0x680);              // Name RVA
      put<uint32_t>(desc,0x10,0x740);              // FirstThunk
      std::strcpy((char*)(g_img+0x680),"KERNEL32.dll");
      put<uint64_t>(g_img,0x700,0x800);            // by name -> 0x800+2
      put<uint64_t>(g_img,0x708,0x8000000000000007ull); // by ordinal 7
      std::strcpy((char*)(g_img+0x802),"GetTickCount");
      CPEImage im; std::memset(&im,0,sizeof im); im.nt_=(intptr_t)g_img+0x100;
      CK(im.ResolveImports(g_img,IMP)==1,"imports resolve");
      CK(g_gh==1 && g_gpa==1 && g_gpao==1,"one module and two thunk lookups");
      CK(*(uint64_t*)(g_img+0x740)==0x22 && *(uint64_t*)(g_img+0x748)==0x33,
         "both thunk slots are patched");
      g_haveMod=0; CK(im.ResolveImports(g_img,IMP)==0,"a missing module fails the resolve");
      g_haveMod=1; g_haveProc=0;
      CK(im.ResolveImports(g_img,IMP)==0,"a missing function fails the resolve");
      g_haveProc=1; std::memset(g_img+0x680,'a',0x100); g_img[0x780]=0;
      CK(im.ResolveImports(g_img,IMP)==0,"a 0x100-byte module name fails"); }
    // ---- BootValidate
    { const char* nm[4]={"CreateMapGroup","CreateWorldKernel","CreateNewMapData","CreateMapGroupDefaultData"};
      build_exports(g_img,4,nm,-1);
      g_parse=0; g_lib=0; g_log=0; g_setkey=0; g_proc=0; g_destroy=0; g_ordn=0; g_create=0;
      CPEImage im0; std::memset(&im0,0,sizeof im0);
      CK(CPEImage::BootValidate(g_img,0x1000,0,LDR,im0)==1,"a full image boots");
      CK(g_parse==1 && g_lib==2,"parse ran and both CRT libraries were requested");
      CK(g_setkey==0 && g_proc==0,"no decrypt without the flag");
      CPEImage im2; CK(CPEImage::BootValidate(g_img,0x1001,0,LDR,im2)==0,"a size that is not 8-aligned fails");
      CK(CPEImage::BootValidate(g_img,0x0,0,LDR,im2)==0,"a zero size fails");
      CK(CPEImage::BootValidate(nullptr,0x1000,0,LDR,im2)==0,"a null buffer fails");
      g_ordn=0;
      CPEImage im3; CK(CPEImage::BootValidate(g_img,0x1000,1,LDR,im3)==1,"the decrypt path boots");
      CK(g_setkey==1 && g_proc==1 && g_destroy==1,"the cipher is set, fed and destroyed");
      CK(g_order[0]==1 && g_order[1]==2 && g_order[2]==3,"the cipher order is set, process, destroy");
      g_create=0; g_parse=0;
      build_exports(g_img,4,nm,-1);
      // drop one export name -> the boot must fail
      build_exports(g_img,3,nm,0);
      CPEImage im4; CK(CPEImage::BootValidate(g_img,0x1000,0,LDR,im4)==0,"a missing export fails the boot");
      g_parse=1; }
    std::printf("PEIMAGE2-%s: %d assertions\n", g_fail?"FAIL":"OK", g_fail?g_fail:g_ok);
    return g_fail?1:0;
}
