// D120 — tq::CMsg base class (5 slots)
#include "modules/syndicate/src/msg/cmsgbase.h"
#include <cassert>
#include <cstdio>
#include <cstring>
using namespace syndicate;

static int s_nCreate, s_nErr;
static char s_szErr[128];
static void LogFn(const char* fmt, ...) { s_nErr++; strncpy(s_szErr, fmt, 127); }

int main() {
    g_pfnCMsgCreate = [](void*, char*, uint16_t) -> bool { s_nCreate++; return true; };
    g_pfnInlineLogError = LogFn;
    static unsigned char ab[0x420];
    memset(ab, 0, sizeof ab);

    // Create is the imported thunk, so it forwards verbatim
    assert(CMsgBase::Create(ab, (char*)1, 9) == true);
    assert(s_nCreate == 1);

    // dtor writes the base vftable
    CMsgBase::DeleteDtor(ab, 0);
    assert(*(uintptr_t*)ab == CMsgBase::kVft);

    // the three stubs
    CMsgBase::ProcessActorInfo(ab, 1, (void*)2);
    assert(!strcmp(s_szErr, "tq::CMsg::Process(OBJID idActor, void* pInfo) error"));
    CMsgBase::ProcessActor(ab, 1);
    assert(!strcmp(s_szErr, "tq::CMsg::Process(OBJID idActor) error"));
    CMsgBase::ProcessInfo(ab, (void*)2);
    assert(!strcmp(s_szErr, "tq::CMsg::Process(void* pInfo) error"));
    assert(s_nErr == 3);

    printf("SYNDICATE_D120_OK: tq::CMsg base 5/5 slots\n");
    return 0;
}
