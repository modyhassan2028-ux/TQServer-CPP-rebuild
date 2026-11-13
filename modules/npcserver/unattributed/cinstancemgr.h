// CInstanceMgr: the instance lookup, CreateInstance and DestroyInstance.
//
// Transcribed verbatim from NpcServer.exe. Every callee is a ported body (0x140024fe0, 0x1400491b0, 0x140049070,
// 0x140024970, 0x140049050, 0x140048f90, 0x140024b20), so this file carries no seams.
#ifndef TQ_NPCSERVER_CINSTANCEMGR_H
#define TQ_NPCSERVER_CINSTANCEMGR_H

namespace tq {

// 0x1400250e0 - the instance at node+0x20 for a type id, or 0. Same shape as 0x140024fe0, with the head at +0x78 and
// the iterator owner at +0x48.
unsigned long long FUN_1400250e0(long long pMgr, unsigned nType);

// 0x140025690 - look the type up, build the instance around the map it carries, then insert it by its own type.
unsigned long long FUN_140025690(long long pMgr, unsigned nParam2, unsigned nParam3, unsigned nType);

// 0x140025750 - find the instance of that type, release it, then erase its entry.
void FUN_140025750(long long pMgr, unsigned nType);

struct NpcInstanceMgrEntry {
    const char* pszAddress;
    const char* pszKind;
    void*       pfn;
};

extern const NpcInstanceMgrEntry g_aNpcInstanceMgr[];
extern const int g_nNpcInstanceMgr;

}  // namespace tq

#endif
