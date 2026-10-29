// D115 — the four member-destructor message wrappers
// (CMsgLeagueConcubines / CMsgLeagueOrderStatus / CMsgLeagueRobList /
//  CMsgOverheadLeagueInfo) and the PB member-destructor bodies.
#include "modules/syndicate/src/CMsgLeagueConcubines.h"
#include "modules/syndicate/src/CMsgLeagueOrderStatus.h"
#include "modules/syndicate/src/CMsgLeagueRobList.h"
#include "modules/syndicate/src/CMsgOverheadLeagueInfo.h"
#include "modules/syndicate/src/CMsgPBMemberDtors.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <new>
#include <string>
using namespace syndicate;

static int      s_nMemDtor[4];
static void*    s_pMemDtorSelf[4];
static uint64_t s_uMemDtorFlags[4];
static int      s_nDelete[4];
static void*    s_pDeleteSelf[4];
static int      s_nLog;

// the four member seams record which class routed
static void MemConcubines(void* s, uint64_t f, uint64_t a, uint64_t b) {
    (void)a; (void)b;
    s_nMemDtor[0]++; s_pMemDtorSelf[0] = s; s_uMemDtorFlags[0] = f; }
static void MemOrderStatus(void* s, uint64_t f, uint64_t a, uint64_t b) {
    (void)a; (void)b;
    s_nMemDtor[1]++; s_pMemDtorSelf[1] = s; s_uMemDtorFlags[1] = f; }
static void MemRobList(void* s, uint64_t f, uint64_t a, uint64_t b) {
    (void)a; (void)b;
    s_nMemDtor[2]++; s_pMemDtorSelf[2] = s; s_uMemDtorFlags[2] = f; }
static void MemOverhead(void* s, uint64_t f, uint64_t a, uint64_t b) {
    (void)a; (void)b;
    s_nMemDtor[3]++; s_pMemDtorSelf[3] = s; s_uMemDtorFlags[3] = f; }

static bool BaseCreate(void* self, const char* buf, uint16_t len) {
    (void)self; (void)buf; (void)len; return true; }

static void DelConcubines(void* p)  { s_nDelete[0]++; s_pDeleteSelf[0] = p; }
static void DelOrderStatus(void* p) { s_nDelete[1]++; s_pDeleteSelf[1] = p; }
static void DelRobList(void* p)     { s_nDelete[2]++; s_pDeleteSelf[2] = p; }
static void DelOverhead(void* p)    { s_nDelete[3]++; s_pDeleteSelf[3] = p; }

static void LogErr(const char* t) { (void)t; s_nLog++; }
static void PbDelete(void* p) { std::free(p); }

static void Reset() {
    std::memset(s_nMemDtor, 0, sizeof(s_nMemDtor));
    std::memset(s_pMemDtorSelf, 0, sizeof(s_pMemDtorSelf));
    std::memset(s_uMemDtorFlags, 0, sizeof(s_uMemDtorFlags));
    std::memset(s_nDelete, 0, sizeof(s_nDelete));
    std::memset(s_pDeleteSelf, 0, sizeof(s_pDeleteSelf));
    s_nLog = 0;
    g_pfnCMsgLeagueConcubinesBaseCreate = BaseCreate;
    g_pfnCMsgLeagueOrderStatusBaseCreate = BaseCreate;
    g_pfnCMsgLeagueRobListBaseCreate = BaseCreate;
    g_pfnCMsgOverheadLeagueInfoBaseCreate = BaseCreate;
    g_pfnCMsgLeagueConcubinesDelete = DelConcubines;
    g_pfnCMsgLeagueOrderStatusDelete = DelOrderStatus;
    g_pfnCMsgLeagueRobListDelete = DelRobList;
    g_pfnCMsgOverheadLeagueInfoDelete = DelOverhead;
    g_pfnCMsgLeagueConcubinesLogError = LogErr;
    g_pfnCMsgLeagueOrderStatusLogError = LogErr;
    g_pfnCMsgLeagueRobListLogError = LogErr;
    g_pfnCMsgOverheadLeagueInfoLogError = LogErr;
    g_pfnCMsgLeagueConcubinesMemDtor = MemConcubines;
    g_pfnCMsgLeagueOrderStatusMemDtor = MemOrderStatus;
    g_pfnCMsgLeagueRobListMemDtor = MemRobList;
    g_pfnCMsgOverheadLeagueInfoMemDtor = MemOverhead;
    g_pfnPbOperatorDelete = PbDelete;
}

// the element vtable: slot 0 = the deleting destructor
static int s_nElemDtor;
static void* s_pElemDtor;
static int s_iElemFlag;
static void ElemDtor(void* p, int flag) {
    s_nElemDtor++; s_pElemDtor = p; s_iElemFlag = flag; }

int main() {
    Reset();

    // ---- S1: the four Destruct bodies route to their member ----
    alignas(16) static unsigned char abObj[0x600];
    std::memset(abObj, 0, sizeof(abObj));
    void* pObj = abObj;

    CMsgLeagueConcubines o1;
    (void)o1;
    *((uintptr_t*)pObj) = 0;
    CMsgLeagueConcubines* pC =
        reinterpret_cast<CMsgLeagueConcubines*>(pObj);
    void* pRet = pC->Destruct(0, 7, 8);
    assert(pRet == pObj);
    assert(s_nMemDtor[0] == 1);
    assert(s_pMemDtorSelf[0] ==
           (void*)(abObj + CMsgLeagueConcubines::kMemberOff));
    assert(s_uMemDtorFlags[0] == 0);
    assert(s_nDelete[0] == 0);
    // class vtable then base vtable
    assert(*((uintptr_t*)pObj) == CMsgLeagueConcubines::kBaseVft);

    // flag bit 0 -> the delete seam
    pC->Destruct(1, 0, 0);
    assert(s_nDelete[0] == 1 && s_pDeleteSelf[0] == pObj);

    // the other three route to their own member seam
    std::memset(abObj, 0, sizeof(abObj));
    reinterpret_cast<CMsgLeagueOrderStatus*>(pObj)->Destruct(1, 0, 0);
    assert(s_nMemDtor[1] == 1 && s_nMemDtor[0] == 2);
    assert(s_pMemDtorSelf[1] ==
           (void*)(abObj + CMsgLeagueOrderStatus::kMemberOff));
    assert(s_nDelete[1] == 1);

    std::memset(abObj, 0, sizeof(abObj));
    reinterpret_cast<CMsgLeagueRobList*>(pObj)->Destruct(1, 0, 0);
    assert(s_nMemDtor[2] == 1);
    assert(s_nDelete[2] == 1);

    std::memset(abObj, 0, sizeof(abObj));
    reinterpret_cast<CMsgOverheadLeagueInfo*>(pObj)->Destruct(0, 0, 0);
    assert(s_nMemDtor[3] == 1 && s_nDelete[3] == 0);

    // ---- S2: the shared Create seam ----
    assert(CMsgLeagueConcubines::Create(pObj, "x", 1) == true);
    assert(CMsgOverheadLeagueInfo::Create(pObj, "x", 1) == true);

    // ---- S3: the three shared error loggers ----
    CMsgLeagueConcubines::ProcessActorInfoError();
    CMsgLeagueConcubines::ProcessActorError();
    CMsgLeagueConcubines::ProcessInfoError();
    assert(s_nLog == 3);

    // ---- S4: the PB vector member destructor ----
    Reset();
    s_nElemDtor = 0;
    alignas(16) static unsigned char abPb[0x200];
    std::memset(abPb, 0, sizeof(abPb));
    // a real std::string at +8 (the body destroys it)
    new (abPb + 8) std::string("member");
    // two element pointers at +0x38, count at +0x44
    // two real element objects: first field = the vtable pointer
    static void* apElemVt[1] = { (void*)ElemDtor };
    static unsigned char abElem0[16], abElem1[16];
    *((void**)abElem0) = (void*)apElemVt;
    *((void**)abElem1) = (void*)apElemVt;
    void* apElems = std::malloc(2 * sizeof(void*));
    ((void**)apElems)[0] = abElem0;
    ((void**)apElems)[1] = abElem1;
    *((void**)(abPb + 0x38)) = apElems;
    *((int*)(abPb + 0x44)) = 2;
    ConcubinesPbMemberDtor(abPb, 0, 0, 0);
    // both elements ran their deleting destructor
    assert(s_nElemDtor == 2);
    assert(s_pElemDtor == abElem1);
    assert(s_iElemFlag == 1);
    // the vtable ended up as the MessageLite base
    assert(*((uintptr_t*)abPb) == kMessageLiteVft);

    // ---- S5: the Overhead string-vector body ----
    Reset();
    alignas(16) static unsigned char abOh[0x200];
    std::memset(abOh, 0, sizeof(abOh));
    new (abOh + 8) std::string("oh");
    void* apStr = std::malloc(2 * sizeof(void*));
    ((void**)apStr)[0] = std::malloc(8);
    ((void**)apStr)[1] = nullptr;   // the null guard
    *((void**)(abOh + 0x48)) = apStr;
    *((int*)(abOh + 0x54)) = 2;
    OverheadPbMemberDtor(abOh, 0, 0, 0);
    assert(*((uintptr_t*)abOh) == kMessageLiteVft);

    std::printf("SYNDICATE_D115_OK: the four member-dtor wrappers\n");
    return 0;
}
