// D93 — CMsgLeagueConcubinesInfoPB MergeFrom (0x1417ea660) + Merge (0x1417eafa0)
#include "modules/syndicate/src/msg/msgleagueconcubinesinfopb.h"
#include "modules/syndicate/src/msg/msgpbcommon.h"
#include "modules/syndicate/src/msg/msgpbmemberdtors.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <string>

using namespace syndicate;

static int s_nCheckFail;
static char s_szCheckFile[512];
static int s_nStrSeam;
static int s_nBoolSeam;
static uint64_t s_uUnknownAdd;
static int s_nUnknownDone;
static int s_nReaderOpen, s_nReaderDone;

int main() {
    unsigned char abSelf[0x80];
    unsigned char abFrom[0x80];
    unsigned char abIn[0x80];

    g_pfnPbCheckFail = [](const char* f, int32_t n,
                          const char* t) {
        s_nCheckFail++;
        snprintf(s_szCheckFile, sizeof s_szCheckFile, "%s|%d|%s", f, n, t); };
    g_pfnPb64C0 = [](void* out, void* src) { (void)src;
        s_nReaderOpen++; return out; };
    g_pfnPb4550 = [](void* out, void* in) { (void)in; return out; };
    g_pfnPb6510 = [](void*) { s_nReaderDone++;
        return (uint64_t)0; };
    g_pfnPb45D0 = [](void*) { s_nUnknownDone++; return (void*)0; };
    // 1417ea0d0/1417ea060 are the field-3 setters: they raise HasBit 2
    g_pfnPbEA0D0 = [](void* self) {
        *(uint32_t*)((unsigned char*)self + 0x30) |= 4;
        return self; };
    g_pfnPbF51E0 = [](void*, void* s) { s_nStrSeam++;
        (void)s; return (uint64_t)1; };
    g_pfnPbEAA40 = [](void* in, void* dst) {
        unsigned char* c = *(unsigned char**)((unsigned char*)in + 8);
        *(unsigned char*)dst = *c;
        *(unsigned char**)((unsigned char*)in + 8) = c + 1;
        s_nBoolSeam++; return (uint64_t)1; };
    g_pfnPbEA060 = [](void* self, void* src) {
        *(uint32_t*)((unsigned char*)self + 0x30) |= 4;
        *(void**)((unsigned char*)self + 0x40) = src; };
    g_pfnPb3A50 = [](void*, uint32_t*) { return (uint64_t)0; };

    // ---- S1: MergeFrom copies every set field and its flag bit ----
    memset(abSelf, 0, sizeof abSelf);
    memset(abFrom, 0, sizeof abFrom);
    new (abSelf + 8) std::string();
    new (abFrom + 8) std::string("from");
    *(uint32_t*)(abFrom + 0x30) = 0x3ff;
    *(uint32_t*)(abFrom + 0x38) = 11;
    *(uint32_t*)(abFrom + 0x3c) = 12;
    *(uint32_t*)(abFrom + 0x48) = 14;
    *(uint32_t*)(abFrom + 0x4c) = 15;
    *(uint32_t*)(abFrom + 0x50) = 16;
    *(uint32_t*)(abFrom + 0x54) = 17;
    *(uint32_t*)(abFrom + 0x58) = 18;
    *(unsigned char*)(abFrom + 0x5c) = 1;
    *(uint32_t*)(abFrom + 0x60) = 20;
    CMsgLeagueConcubinesInfoPB::MergeFrom(abSelf, abFrom);
    assert(*(uint32_t*)(abSelf + 0x30) == 0x3ff);
    assert(*(uint32_t*)(abSelf + 0x38) == 11 &&
           *(uint32_t*)(abSelf + 0x3c) == 12);
    assert(*(uint32_t*)(abSelf + 0x48) == 14 &&
           *(uint32_t*)(abSelf + 0x4c) == 15 &&
           *(uint32_t*)(abSelf + 0x50) == 16 &&
           *(uint32_t*)(abSelf + 0x54) == 17 &&
           *(uint32_t*)(abSelf + 0x58) == 18);
    assert(*(unsigned char*)(abSelf + 0x5c) == 1);
    assert(*(uint32_t*)(abSelf + 0x60) == 20);
    assert(*(std::string*)(abSelf + 8) == "from");
    assert(s_nCheckFail == 0);

    // ---- S2: self == from fires the protobuf CHECKF literal ----
    CMsgLeagueConcubinesInfoPB::MergeFrom(abSelf, abSelf);
    assert(s_nCheckFail == 1);
    assert(strstr(s_szCheckFile,
                  "msgleagueconcubines.pb.cc|499|"
                  "CHECK failed: (&from) != (this): ") != nullptr);

    // ---- S3: Merge walks the tag chain 1..10 ----
    *(std::string*)(abSelf + 8) = std::string();
    memset(abSelf, 0, 0x30);   // clear everything below the flags
    *(uint32_t*)(abSelf + 0x30) = 0;
    unsigned char abStream[] = {
        0x08, 0x05,              // field 1
        0x10, 0x07,              // field 2
        0x1a,                    // field 3 (the seam consumes
                                 // the length byte itself)
        0x20, 0x01,              // field 4
        0x28, 0x02,              // field 5
        0x30, 0x03,              // field 6
        0x38, 0x04,              // field 7
        0x40, 0x05,              // field 8
        0x48, 0x01,              // field 9 (bool seam)
        0x50, 0x09               // field 10
    };
    memset(abIn, 0, sizeof abIn);
    *(unsigned char**)(abIn + 0x08) = abStream;
    *(unsigned char**)(abIn + 0x10) = abStream + sizeof abStream;
    *(uint64_t*)(abIn + 0x28) = 0x50;
    g_pfnPb3BC0 = [](void*) { return (uint64_t)0; };
    bool bOk = CMsgLeagueConcubinesInfoPB::Merge(abSelf, abIn);
    assert(bOk);
    assert(*(uint32_t*)(abSelf + 0x38) == 5);
    assert(*(uint32_t*)(abSelf + 0x3c) == 7);
    assert(s_nStrSeam == 1);
    assert(*(uint32_t*)(abSelf + 0x48) == 1);
    assert(*(uint32_t*)(abSelf + 0x4c) == 2);
    assert(*(uint32_t*)(abSelf + 0x50) == 3);
    assert(*(uint32_t*)(abSelf + 0x54) == 4);
    assert(*(uint32_t*)(abSelf + 0x58) == 5);
    assert(s_nBoolSeam == 1 && *(unsigned char*)(abSelf + 0x5c) == 1);
    assert(*(uint32_t*)(abSelf + 0x60) == 9);
    assert(*(uint32_t*)(abSelf + 0x30) == 0x3ff);
    assert(s_nUnknownDone == 1 && s_nReaderDone == 1);
    (void)s_nReaderOpen; (void)s_uUnknownAdd;

    // ---- S4: an unknown tag goes through the skipper ----
    memset(abSelf, 0, 0x30);
    *(uint32_t*)(abSelf + 0x30) = 0;
    unsigned char abS4[] = { 0x58, 0x01 };   // field 11 (unknown)
    memset(abIn, 0, sizeof abIn);
    *(unsigned char**)(abIn + 0x08) = abS4;
    *(unsigned char**)(abIn + 0x10) = abS4 + 2;
    g_pfnPbF3F50 = [](void*, uint32_t, void*) { return (char)1; };
    assert(CMsgLeagueConcubinesInfoPB::Merge(abSelf, abIn));
    assert(*(uint32_t*)(abSelf + 0x30) == 0);

    // ---- S5: a failing skipper returns false ----
    memset(abSelf, 0, 0x30);
    *(uint32_t*)(abSelf + 0x30) = 0;
    *(unsigned char**)(abIn + 0x08) = abS4;
    *(unsigned char**)(abIn + 0x10) = abS4 + 2;
    g_pfnPbF3F50 = [](void*, uint32_t, void*) { return (char)0; };
    assert(!CMsgLeagueConcubinesInfoPB::Merge(abSelf, abIn));

    (*(std::string*)(abSelf + 8)).~basic_string();
    (*(std::string*)(abFrom + 8)).~basic_string();
    printf("SYNDICATE_D93_OK: MergeFrom + Merge\n");
    return 0;
}
