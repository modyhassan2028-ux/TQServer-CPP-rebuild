// The nine small syndicate message/manager units: ids, the id gate, the
// destructor order and the shared loggers.
#include <cstdio>
#include <cstdint>
#include <cstring>
#include "CMsgLeagueInfo.h"
#include "CMsgLeagueList.h"
#include "CMsgLeagueSynList.h"
#include "CMsgLeagueUserMemberList.h"
#include "CMsgLeagueRank.h"
#include "CMsgLeaguePalaceGuardsList.h"
#include "CMsgLeagueImperialCourtList.h"
#include "CMsgSynCompete.h"
#include "CSynManager.h"
using namespace syndicate;
static int ok=0, bad=0;
#define CK(c,m) do{ if(c) ok++; else { bad++; std::printf("  FAIL %s\n", m); } }while(0)

// a fake message object: the id lives at +0xa
struct FakeMsg { unsigned char raw[0x40]; };
static int baseCalls=0, baseOk=1, deletes=0, logs=0;
static bool BC(void*, const char*, uint16_t){ baseCalls++; return baseOk!=0; }
static void DL(void*){ deletes++; }
static void LG(const char*){ logs++; }
static uintptr_t deletedPtr=0;

template<class T> static void wire(T&, bool (*bc)(void*,const char*,uint16_t), void (*dl)(void*), void (*lg)(const char*)) {}

int main(){
    // per-class constants
    CK(CMsgLeagueInfo::kMsgId==0x0a3f,"info id");
    CK(CMsgLeagueList::kMsgId==0x0a40,"list id");
    CK(CMsgLeagueSynList::kMsgId==0x0a41,"synlist id");
    CK(CMsgLeagueUserMemberList::kMsgId==0x0a42,"memberlist id");
    CK(CMsgLeagueRank::kMsgId==0x0a43,"rank id");
    CK(CMsgLeaguePalaceGuardsList::kMsgId==0x0a44,"palaceguards id");
    CK(CMsgLeagueImperialCourtList::kMsgId==0x0a45,"imperialcourt id");
    CK(CMsgSynCompete::kMsgId==0x0426,"compete id");
    // vtables are distinct and match the binary
    CK(CMsgLeagueInfo::kClassVft==0x14183c448ull,"info vft");
    CK(CMsgLeagueList::kClassVft==0x14183c4f8ull,"list vft");
    CK(CMsgLeagueSynList::kClassVft==0x14183cec8ull,"synlist vft");
    CK(CMsgLeagueUserMemberList::kClassVft==0x14183d1f0ull,"memberlist vft");
    CK(CMsgLeagueRank::kClassVft==0x14183c998ull,"rank vft");
    CK(CMsgLeaguePalaceGuardsList::kClassVft==0x14183c8e8ull,"palaceguards vft");
    CK(CMsgLeagueImperialCourtList::kClassVft==0x14183c398ull,"imperialcourt vft");
    CK(CMsgSynCompete::kClassVft==0x14183dad0ull,"compete vft");
    CK(CMsgLeagueInfo::kBaseVft==0x14182e368ull,"the shared base vftable");

    // Create: base failure short-circuits, id at +0xa gates the result

    auto wireInfo = [](bool okFlag){
        g_pfnCMsgLeagueInfoBaseCreate = BC; g_pfnCMsgLeagueInfoDelete = DL; g_pfnCMsgLeagueInfoLogError = LG;
    };
    wireInfo(true);
    FakeMsg m; std::memset(&m,0,sizeof m);
    baseOk=0; CK(!CMsgLeagueInfo::Create(&m,"x",1),"a base failure returns false");
    baseOk=1; *(uint16_t*)(m.raw+0x0a)=0x0a3f;
    CK(CMsgLeagueInfo::Create(&m,"x",1),"the matching id returns true");
    *(uint16_t*)(m.raw+0x0a)=0x0a40;
    CK(!CMsgLeagueInfo::Create(&m,"x",1),"a foreign id returns false");
    CK(!CMsgLeagueInfo::Create(&m,"x",1) && baseCalls==4,"one base call per attempt");
    // the id gate is 16 bits wide and at +0xa exactly
    *(uint16_t*)(m.raw+0x0a)=0x0a3f; CK(CMsgLeagueInfo::Create(&m,"x",1),"the gate reads +0xa");

    // the other classes share the shape but keep their own id
    g_pfnCMsgSynCompeteBaseCreate = BC;
    FakeMsg c; std::memset(&c,0,sizeof c);
    *(uint16_t*)(c.raw+0x0a)=0x0426;
    CK(CMsgSynCompete::Create(&c,"x",1),"compete accepts its own id");
    *(uint16_t*)(c.raw+0x0a)=0x0a3f;
    CK(!CMsgSynCompete::Create(&c,"x",1),"compete rejects the info id");

    // Destruct: two vftable stores, delete only on flag bit 0
    FakeMsg r; std::memset(&r,0,sizeof r);
    CMsgLeagueRank* pr = reinterpret_cast<CMsgLeagueRank*>(&r);
    g_pfnCMsgLeagueRankDelete = DL;
    g_pfnCMsgLeagueRankLogError = LG;
    deletes=0;
    pr->Destruct(0);
    CK(deletes==0,"flag 0 does not delete");
    CK(*(uintptr_t*)r.raw==CMsgLeagueRank::kBaseVft,"the base vftable is the last store");
    CK(*(uintptr_t*)r.raw!=CMsgLeagueRank::kClassVft,"the class vftable was overwritten");
    pr->Destruct(1);
    CK(deletes==1,"flag 1 deletes");
    pr->Destruct(2);
    CK(deletes==1,"flag 2 (bit 0 clear) does not delete");

    // shared loggers
    CMsgLeagueInfo::ProcessActorInfoError();
    CMsgLeagueInfo::ProcessActorError();
    CMsgLeagueInfo::ProcessInfoError();
    CK(logs==3,"the three shared loggers log");

    // CSynManager
    struct Mgr { unsigned char raw[0x100]; };
    Mgr g; std::memset(&g,0,sizeof g);
    CSynManager* mgr = reinterpret_cast<CSynManager*>(&g);
    mgr->SetValue(0x40e, 0x11111111u);
    CK(*(uint32_t*)(g.raw+0xa8)==0x11111111u,"id 0x40e writes +0xa8");
    CK(*(uint32_t*)(g.raw+0xac)==0,"and leaves +0xac alone");
    mgr->SetValue(1000, 0x22222222u);
    CK(*(uint32_t*)(g.raw+0xac)==0x22222222u,"id 1000 writes +0xac");
    mgr->SetValue(7, 0x33333333u);
    CK(*(uint32_t*)(g.raw+0xa8)==0x11111111u && *(uint32_t*)(g.raw+0xac)==0x22222222u,"any other id is ignored");
    CK(CSynManager::kClassVft==0x14183b430ull,"manager vft");
    CK(CSynManager::kIdStateA==0x40e && CSynManager::kIdStateB==1000,"manager id gates");

    std::printf("MSGFAM-%s: %d assertions\n", bad?"FAIL":"OK", bad?bad:ok);
    return bad?1:0;
}
