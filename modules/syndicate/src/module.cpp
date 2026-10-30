// module.cpp — RAW Syndicate.dll v6159
#include "modules/syndicate/src/module.h"
#include "modules/syndicate/src/SyndicateCrossMerit.h"  // g_fnGetGameMgr
namespace syndicate {

void (*g_fnModBaseDtor)(void*) = nullptr;
void (*g_fnModMem41a8)(void*) = nullptr;
void (*g_fnModMem3d50)(void*) = nullptr;
void (*g_fnModMem3928)(void*) = nullptr;
void (*g_fnModMem3518)(void*) = nullptr;
void (*g_fnModMem3108)(void*) = nullptr;
void (*g_fnModMem2cf8)(void*) = nullptr;
void (*g_fnModMem28e8)(void*) = nullptr;
void (*g_fnModMem24d8)(void*) = nullptr;
void (*g_fnModMem20c8)(void*) = nullptr;
void (*g_fnModMem1cb8)(void*) = nullptr;
void (*g_fnModMem18a8)(void*) = nullptr;
void (*g_fnModMem1088)(void*) = nullptr;
void (*g_fnModMem0c78)(void*) = nullptr;
void (*g_fnModMem0850)(void*) = nullptr;
void (*g_fnModMem0428)(void*) = nullptr;
void (*g_fnModPureCall)() = nullptr;
bool (*g_fnModProviderInit)(void*, void*) = nullptr;
void* (*g_fnModSlotAA0Tail)(void*) = nullptr;

// ============================ gs::IModule ===============================
// 0x14177e380
void* IModule::DeleteDtor(void* self, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(self) = kClassVft;
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}
// 0x1417f3374 — the four declaration-only slots jump the purecall slot
bool IModule::PureVirtual() {
    if (g_fnModPureCall != nullptr) g_fnModPureCall();
    return false;
}
bool IModule::Off340() { return false; }  // 0x14177e340
bool IModule::Off350() { return false; }  // 0x14177e350
bool IModule::Off360() { return false; }  // 0x14177e360
bool IModule::Off370() { return false; }  // 0x14177e370

// ============================ syndicate::CModule ========================
// 0x14177e4c0 — the member chain, verbatim rcx-only calls in binary order
void CModule::MemberDtor(void* self) {
    unsigned char* p = (unsigned char*)self;
    *reinterpret_cast<uintptr_t*>(p) = kClassVft;
    g_fnModBaseDtor(p);
    g_fnModMem41a8(p + 0x41a8);
    g_fnModMem3d50(p + 0x3d50);
    g_fnModMem3928(p + 0x3928);
    g_fnModMem3518(p + 0x3518);
    g_fnModMem3108(p + 0x3108);
    g_fnModMem2cf8(p + 0x2cf8);
    g_fnModMem28e8(p + 0x28e8);
    g_fnModMem24d8(p + 0x24d8);
    g_fnModMem20c8(p + 0x20c8);
    g_fnModMem1cb8(p + 0x1cb8);
    g_fnModMem18a8(p + 0x18a8);
    *reinterpret_cast<uintptr_t*>(p + 0x1498) = 0x14182e520ull;
    *reinterpret_cast<uintptr_t*>(p + 0x1498) = 0x14182e368ull;
    g_fnModMem1088(p + 0x1088);
    g_fnModMem0c78(p + 0x0c78);
    g_fnModMem0850(p + 0x0850);
    g_fnModMem0428(p + 0x0428);
    *reinterpret_cast<uintptr_t*>(p + 0x10) = 0x14182e4a0ull;
    *reinterpret_cast<uintptr_t*>(p + 0x10) = 0x14182e368ull;
    *reinterpret_cast<uintptr_t*>(p) = kBaseIModuleVft;
}

// 0x14177ec00 — member chain, then the optional delete
void* CModule::DeleteDtor(void* self, uint32_t uFlag) {
    MemberDtor(self);
    if ((uFlag & 1) != 0) ::operator delete(self);
    return self;
}

// 0x14177e600 — release the handed object through its own slot 0, return false
bool CModule::Slot600(void* self, void* pObj) {
    (void)self;
    if (pObj != nullptr) {
        void** vt = *reinterpret_cast<void***>(pObj);
        ((void (*)(void*, uint32_t))vt[0])(pObj, 1);
    }
    return false;
}

// 0x14177e620 — pull the consumer, ask its vt[+0x30] for 0x16, then init
bool CModule::Init(void* self) {
    void* pConsumer = *reinterpret_cast<void**>(
        (unsigned char*)self + kOffConsumer);
    void** vt = *reinterpret_cast<void***>(pConsumer);
    void* pProvider = ((void* (*)(void*, int))vt[6])(pConsumer, 0x16);
    if (pProvider == nullptr) {
        // 0x14182e610 "pConsumer", line 0x1e, module.cpp
        g_fn_141823030(
            "\\xA1\\xEF%s(%s)\\xA1\\xEF in %s, %d",  // 0x141824ca8
            "CHECKF", "pConsumer",
            "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\module.cpp",
            0x1e);
        return false;
    }
    void* pMgr = g_fnGetGameMgr();
    if (!g_fnModProviderInit(pMgr, pProvider)) {
        // 0x14182e5f0 "rProvider.Init(pConsumer)", line 0x22
        g_fn_141823030(
            "\\xA1\\xEF%s(%s)\\xA1\\xEF in %s, %d",
            "CHECKF", "rProvider.Init(pConsumer)",
            "f:\\version\\cqserver-78.0.11-1204\\modules\\syndicate\\src\\module.cpp",
            0x22);
        return false;
    }
    return true;
}

// 0x14177eaa0 — mgr = GetSyndicateMgr(); tail-call 0x1417ac5e0(mgr)
void* CModule::SlotAA0(void* self) {
    (void)self;
    void* pMgr = g_fnGetGameMgr();
    return g_fnModSlotAA0Tail(pMgr);
}

// 0x14177ec30 — the packet wrapper: factory, then the Create slot with the
// payload length, then *(uint16*)(msg+8)
void* CModule::CreateMsg(void* self, uint32_t uCount32, void* pPacket,
                         uint16_t uCount16) {
    void* pMsg = CreateMsgCore(self, pPacket, uCount16);
    if (pMsg != nullptr) {
        void** vt = *reinterpret_cast<void***>(pMsg);
        ((void (*)(void*, uint32_t))vt[3])(pMsg, uCount32);
        return (void*)(uintptr_t)*reinterpret_cast<uint16_t*>(
            (unsigned char*)pMsg + 8);
    }
    return nullptr;
}

// 0x14177e6c0 — the type -> member-message map, verbatim
void* CModule::CreateMsgCore(void* self, void* pPacket, uint16_t uCount) {
    unsigned char* p = (unsigned char*)self;
    if (pPacket == nullptr) return nullptr;
    if (uCount < *reinterpret_cast<uint16_t*>(pPacket)) return nullptr;
    uint16_t uType = *reinterpret_cast<uint16_t*>(
        (unsigned char*)pPacket + 2);
    void* pMsg;
    switch (uType) {
    case 0x3ea: case 0x3eb: pMsg = p + 0x10;   break;
    case 0x422: pMsg = p + 0x0c78;             break;
    case 0x425: pMsg = p + 0x20c8;             break;
    case 0x427: pMsg = p + 0x28e8;             break;
    case 0x452: pMsg = p + 0x1088;             break;
    case 0x453: pMsg = p + 0x428;              break;
    case 0x458: pMsg = p + 0x18a8;             break;
    case 0x836: pMsg = p + 0x1cb8;             break;
    case 0x837: pMsg = p + 0x1498;             break;
    case 0x8b1: pMsg = p + 0x2cf8;             break;
    case 0x8b2: pMsg = p + 0x3518;             break;
    case 0x8b3: pMsg = p + 0x3108;             break;
    case 0x9ce: pMsg = p + 0x0850;             break;
    case 0xa3e: pMsg = p + 0x3928;             break;
    case 0xa49: pMsg = p + 0x3d50;             break;
    case 0xa52: pMsg = p + 0x41a8;             break;
    default: return nullptr;
    }
    void** vt = *reinterpret_cast<void***>(pMsg);
    *reinterpret_cast<uint16_t*>((unsigned char*)pMsg + 0x0a) = uType;
    bool bOk = ((bool (*)(void*, void*, uint16_t))vt[1])(
        pMsg, pPacket, *reinterpret_cast<uint16_t*>(pPacket));
    return bOk ? pMsg : nullptr;
}

}  // namespace syndicate
