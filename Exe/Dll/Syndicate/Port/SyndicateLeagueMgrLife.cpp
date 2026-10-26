// ============================================================
// Syndicate.dll port — T15/D40a: the CLeagueMgr life
// cycle, verbatim (see SyndicateLeagueMgrLife.h).
// ============================================================
#include "SyndicateLeagueMgrLife.h"
#include "SyndicateCrossMerit.h"    // the opnew/opdelete
#include "SyndicateOwnTree.h"        // OwnAnchorAlloc
#include "SyndicateEraseLayer.h"     // OwnEraseRange
#include "SyndicateLeagueLife.h"     // LeagueUsersMapCtor
#include "SyndicateLeagueMgrErase.h"  // the D41a real
                                     //  erase-ranges

namespace syndicate {

int64_t g_MgrDat141886d00 = 0;
void* g_fnMgrVftable = nullptr;
// the D41 seams now DEFAULT to the real D41a
// erase-ranges (tests may override for isolation)
FnMgrEraseRange g_fnMgrErase38  = &MgrEraseRange38;
FnMgrEraseRange g_fnMgrErase538 = &MgrEraseRange538;
FnMgrEraseRange g_fnMgrErase4f8 = &MgrEraseRange4f8;
FnMgrEraseRange g_fnMgrErase4b0 = &MgrEraseRange4b0;
FnMgrEraseRange g_fnMgrErase470 = &MgrEraseRange470;
FnMgrEraseRange g_fnMgrErase318 = &MgrEraseRange318;
FnMgrEraseRange g_fnMgrErase2b0 = &MgrEraseRange2b0;
FnMgrEraseRange g_fnMgrErase228 = &MgrEraseRange228;
FnMgrEraseRange g_fnMgrErase108 = &MgrEraseRange108;

// ============ the head allocators ============
// 141756200 (0x30, isnil 0x29, +0x28 color 1)
void* MgrHeadAlloc30_29() {
    uint8_t* p = (uint8_t*)g_fnMeritOpNew(0x30);
    *(uint64_t*)(p + 0) = 0;
    *(uint64_t*)(p + 8) = 0;
    *(uint64_t*)(p + 0x10) = 0;
    *(uint8_t*)(p + 0x28) = 1;
    *(uint8_t*)(p + 0x29) = 0;
    return p;
}
// 141756260 (0x60, isnil 0x59, +0x58 color 1)
void* MgrHeadAlloc60_59() {
    uint8_t* p = (uint8_t*)g_fnMeritOpNew(0x60);
    *(uint64_t*)(p + 0) = 0;
    *(uint64_t*)(p + 8) = 0;
    *(uint64_t*)(p + 0x10) = 0;
    *(uint8_t*)(p + 0x58) = 1;
    *(uint8_t*)(p + 0x59) = 0;
    return p;
}
// 1417562c0 (0x30, isnil 0x29 — the twin of 141756200)
void* MgrHeadAlloc2c0() {
    uint8_t* p = (uint8_t*)g_fnMeritOpNew(0x30);
    *(uint64_t*)(p + 0) = 0;
    *(uint64_t*)(p + 8) = 0;
    *(uint64_t*)(p + 0x10) = 0;
    *(uint8_t*)(p + 0x28) = 1;
    *(uint8_t*)(p + 0x29) = 0;
    return p;
}
// 141756470 (0x68, isnil 0x61, +0x60 color 1)
void* MgrHeadAlloc68_61() {
    uint8_t* p = (uint8_t*)g_fnMeritOpNew(0x68);
    *(uint64_t*)(p + 0) = 0;
    *(uint64_t*)(p + 8) = 0;
    *(uint64_t*)(p + 0x10) = 0;
    *(uint8_t*)(p + 0x60) = 1;
    *(uint8_t*)(p + 0x61) = 0;
    return p;
}
// 1417564d0 (0x30, isnil 0x29)
void* MgrHeadAlloc4d0() {
    uint8_t* p = (uint8_t*)g_fnMeritOpNew(0x30);
    *(uint64_t*)(p + 0) = 0;
    *(uint64_t*)(p + 8) = 0;
    *(uint64_t*)(p + 0x10) = 0;
    *(uint8_t*)(p + 0x28) = 1;
    *(uint8_t*)(p + 0x29) = 0;
    return p;
}
// 1417565b0 (0x70, isnil 0x69, +0x68 color 1)
void* MgrHeadAlloc70_69() {
    uint8_t* p = (uint8_t*)g_fnMeritOpNew(0x70);
    *(uint64_t*)(p + 0) = 0;
    *(uint64_t*)(p + 8) = 0;
    *(uint64_t*)(p + 0x10) = 0;
    *(uint8_t*)(p + 0x68) = 1;
    *(uint8_t*)(p + 0x69) = 0;
    return p;
}
// 141756610 (0x30 — NO color/isnil writes, verbatim)
void* MgrHeadAlloc610() {
    uint8_t* p = (uint8_t*)g_fnMeritOpNew(0x30);
    *(uint64_t*)(p + 0) = 0;
    *(uint64_t*)(p + 8) = 0;
    *(uint64_t*)(p + 0x10) = 0;
    return p;
}
// 141756410 (0x30, isnil 0x29)
void* MgrHeadAlloc410() {
    uint8_t* p = (uint8_t*)g_fnMeritOpNew(0x30);
    *(uint64_t*)(p + 0) = 0;
    *(uint64_t*)(p + 8) = 0;
    *(uint64_t*)(p + 0x10) = 0;
    *(uint8_t*)(p + 0x28) = 1;
    *(uint8_t*)(p + 0x29) = 0;
    return p;
}
// 1417563b0 (0x68, isnil 0x61)
void* MgrHeadAlloc3b0() {
    uint8_t* p = (uint8_t*)g_fnMeritOpNew(0x68);
    *(uint64_t*)(p + 0) = 0;
    *(uint64_t*)(p + 8) = 0;
    *(uint64_t*)(p + 0x10) = 0;
    *(uint8_t*)(p + 0x60) = 1;
    *(uint8_t*)(p + 0x61) = 0;
    return p;
}

// ============ the map ctors ============
// the shared template: proxy(8, backref=map) + head +
// the self-links + size 0 — only the head allocator and
// the isnil offset differ (verbatim per function)
static void* MgrMapCtorTmpl(void* pMap, void* head,
                            int isnilOff) {
    void* proxy = g_fnMeritOpNew(8);
    if (proxy == nullptr) {
        *(void**)pMap = nullptr;
    } else {
        *(void**)proxy = pMap;
        *(void**)pMap = proxy;
    }
    *(void**)((char*)pMap + 0x30) = head;
    *(uint8_t*)((char*)head + isnilOff) = 1;
    *(void**)((char*)head + 8) = head;
    *(void**)((char*)head + 0) = head;
    *(void**)((char*)head + 0x10) = head;
    *(uint64_t*)((char*)pMap + 0x38) = 0;
    return pMap;
}
// the per-family entry points below
static void* MgrMapCtorImpl(void* pMap, void* head,
                            int isnilOff) {
    return MgrMapCtorTmpl(pMap, head, isnilOff);
}
void* MgrMapCtor38R(void* pMap) {
    return MgrMapCtorImpl(pMap,
        MgrHeadAlloc30_29(), 0x29);
}
void* MgrMapCtor108R(void* pMap) {
    return MgrMapCtorImpl(pMap,
        MgrHeadAlloc60_59(), 0x59);
}
void* MgrMapCtor148R(void* pMap) {
    return MgrMapCtorImpl(pMap,
        OwnAnchorAlloc(), 0x21);
}
void* MgrMapCtor228R(void* pMap) {
    return MgrMapCtorImpl(pMap,
        MgrHeadAlloc2c0(), 0x29);
}
void* MgrMapCtor370R(void* pMap) {
    return MgrMapCtorImpl(pMap,
        MgrHeadAlloc68_61(), 0x61);
}
void* MgrMapCtor4b0R(void* pMap) {
    return MgrMapCtorImpl(pMap,
        MgrHeadAlloc4d0(), 0x29);
}
void* MgrMapCtor4f8R(void* pMap) {
    return MgrMapCtorImpl(pMap,
        MgrHeadAlloc70_69(), 0x69);
}
void* MgrMapCtor538R(void* pMap) {
    return MgrMapCtorImpl(pMap,
        MgrHeadAlloc610(), 0x29);
}
void* MgrMapCtor318R(void* pMap) {
    return MgrMapCtorImpl(pMap,
        MgrHeadAlloc410(), 0x29);
}
// 141775ac0 (+0x2b0 — the special one: its OWN head
// alloc 1417563b0 + isnil 0x61)
void* MgrMapCtor2b0(void* pMap) {
    return MgrMapCtorImpl(pMap,
        MgrHeadAlloc3b0(), 0x61);
}

// ============ the family dtor wrappers ============
// the shared template (verbatim): the iterator pair
// {proxy, first} + {proxy, head}, the family erase-
// range call, then delete head + null [6]/[7]
static void MgrMapDtorTmpl(void* pMap,
                           FnMgrEraseRange erase) {
    char** param_1 = (char**)pMap;
    int64_t local_38 = *(int64_t*)param_1;  // the proxy
    char* head = *(char**)(param_1 + 6);
    int64_t uStack_20 = *(int64_t*)head;   // first
    int64_t local_28 = local_38;
    int64_t pair1[2] = { local_28, uStack_20 };
    int64_t pair2[2] = { local_38, (int64_t)head };
    int64_t out[2];
    erase(pMap, out, pair1, pair2);
    g_fnMeritOpDelete(head);
    param_1[6] = nullptr;
    param_1[7] = nullptr;
}
void MgrMapDtorC2f0(void* m) {
    MgrMapDtorTmpl(m, g_fnMgrErase38); }
void MgrMapDtor2770(void* m) {
    MgrMapDtorTmpl(m, g_fnMgrErase538); }
void MgrMapDtor23d0(void* m) {
    MgrMapDtorTmpl(m, g_fnMgrErase4f8); }
void MgrMapDtor2360(void* m) {
    MgrMapDtorTmpl(m, g_fnMgrErase4b0); }
void MgrMapDtor5400(void* m) {
    MgrMapDtorTmpl(m, g_fnMgrErase470); }
void MgrMapDtor1fd0(void* m) {
    MgrMapDtorTmpl(m, g_fnMgrErase318); }
void MgrMapDtor5680(void* m) {
    MgrMapDtorTmpl(m, g_fnMgrErase2b0); }
void MgrMapDtor1f60(void* m) {
    MgrMapDtorTmpl(m, g_fnMgrErase228); }
void MgrMapDtor1bd0(void* m) {
    MgrMapDtorTmpl(m, g_fnMgrErase108); }
// 14173ce30 — the 0x28 family, wired to the ALREADY
// PORTED OwnEraseRange (14173cb90)
void MgrMapDtor028(void* m) {
    MgrMapDtorTmpl(m, &OwnEraseRange); }

// ============ the post-init clears + subtree frees ====
// 141755690 — the recursive free (isnil 0x29)
void MgrSubtreeFree29(void* pMap, void* pNode) {
    char** node = (char**)pNode;
    while (*(char*)((char*)node + 0x29) == '\0') {
        MgrSubtreeFree29(pMap,
            *(char**)(node + 2));   // the right
        char** next = *(char***)node;   // the left
        g_fnMeritOpDelete(node);
        node = next;
    }
}
// 1417556e0 — the recursive free (isnil 0x69)
void MgrSubtreeFree69(void* pMap, void* pNode) {
    char** node = (char**)pNode;
    while (*(char*)((char*)node + 0x69) == '\0') {
        MgrSubtreeFree69(pMap,
            *(char**)(node + 2));   // the right
        char** next = *(char***)node;   // the left
        g_fnMeritOpDelete(node);
        node = next;
    }
}
// 141757740 — the clear of the +0x4b0 map (isnil 0x29)
void MgrClear4b0(int64_t lMap) {
    char* param_1 = (char*)lMap;
    char* node = *(char**)(*(char**)(param_1 + 0x30) + 8);
    while (*(char*)(node + 0x29) == '\0') {
        MgrSubtreeFree29((void*)param_1,
            *(char**)(node + 0x10));   // the right
        char* next = *(char**)node;     // the left
        g_fnMeritOpDelete(node);
        node = next;
    }
    char* head = *(char**)(param_1 + 0x30);
    *(char**)(head + 8) = head;
    *(uint64_t*)(param_1 + 0x38) = 0;
    *(char**)head = head;
    *(char**)(head + 0x10) = head;
}
// 1417577c0 — the clear of the +0x4f8 map (isnil 0x69)
void MgrClear4f8(int64_t lMap) {
    char* param_1 = (char*)lMap;
    char* node = *(char**)(*(char**)(param_1 + 0x30) + 8);
    while (*(char*)(node + 0x69) == '\0') {
        MgrSubtreeFree69((void*)param_1,
            *(char**)(node + 0x10));   // the right
        char* next = *(char**)node;     // the left
        g_fnMeritOpDelete(node);
        node = next;
    }
    char* head = *(char**)(param_1 + 0x30);
    *(char**)(head + 8) = head;
    *(uint64_t*)(param_1 + 0x38) = 0;
    *(char**)head = head;
    *(char**)(head + 0x10) = head;
}

// ============ 141775b40 — the MGR ctor ============
void* MgrCtor(void* pMgr) {
    char** param_1 = (char**)pMgr;
    // the vftable
    param_1[0] = (char*)g_fnMgrVftable;
    *(uint32_t*)(param_1 + 5) = 0;
    // the 19 maps + the 3 inline groups (verbatim order)
    MgrMapCtor38R(param_1 + 7);          // +0x38
    // the +0x78 group (proxy + 3 zeros)
    void* proxy = g_fnMeritOpNew(8);
    if (proxy == nullptr) {
        param_1[0xf] = (char*)nullptr;
    } else {
        *(void**)proxy = param_1 + 0xf;
        param_1[0xf] = (char*)proxy;
    }
    param_1[0x12] = nullptr;
    param_1[0x13] = nullptr;
    param_1[0x14] = nullptr;
    // the +0xa8 group
    proxy = g_fnMeritOpNew(8);
    if (proxy == nullptr) {
        param_1[0x15] = (char*)nullptr;
    } else {
        *(void**)proxy = param_1 + 0x15;
        param_1[0x15] = (char*)proxy;
    }
    param_1[0x18] = nullptr;
    param_1[0x19] = nullptr;
    param_1[0x1a] = nullptr;
    // the +0xd8 group
    proxy = g_fnMeritOpNew(8);
    if (proxy == nullptr) {
        param_1[0x1b] = (char*)nullptr;
    } else {
        *(void**)proxy = param_1 + 0x1b;
        param_1[0x1b] = (char*)proxy;
    }
    param_1[0x1e] = nullptr;
    param_1[0x1f] = nullptr;
    param_1[0x20] = nullptr;
    MgrMapCtor108R(param_1 + 0x21);
    MgrMapCtor148R(param_1 + 0x29);
    LeagueUsersMapCtor(param_1 + 0x34);  // 141733570
    MgrMapCtor148R(param_1 + 0x3c);
    MgrMapCtor228R(param_1 + 0x45);
    MgrMapCtor148R(param_1 + 0x4e);
    MgrMapCtor2b0(param_1 + 0x56);       // 141775ac0
    MgrMapCtor318R(param_1 + 0x63);
    *(uint32_t*)(param_1 + 0x6b) = 0;
    *(uint32_t*)((long long)param_1 + 0x35c) = 0;
    *(uint32_t*)(param_1 + 0x6c) = 0;
    *(uint32_t*)((long long)param_1 + 0x364) = 0;
    *(uint32_t*)(param_1 + 0x6d) = 0;
    MgrMapCtor370R(param_1 + 0x6e);
    MgrMapCtor370R(param_1 + 0x76);
    MgrMapCtor370R(param_1 + 0x7e);
    MgrMapCtor370R(param_1 + 0x86);
    MgrMapCtor370R(param_1 + 0x8e);
    MgrMapCtor4b0R(param_1 + 0x96);
    param_1[0x9e] = nullptr;
    MgrMapCtor4f8R(param_1 + 0x9f);
    MgrMapCtor538R(param_1 + 0xa7);
    param_1[1] = nullptr;
    param_1[2] = nullptr;
    g_MgrDat141886d00 = 0;
    // the config defaults (verbatim offsets)
    *(uint32_t*)(param_1 + 0x31) = 10000;
    *(uint32_t*)((long long)param_1 + 0x18c) = 0x10e;
    *(uint32_t*)(param_1 + 3) = 0;
    *(uint32_t*)((long long)param_1 + 0x1c) = 0;
    *(uint32_t*)(param_1 + 0x32) = 0x16;
    *(uint8_t*)(param_1 + 4) = 0;
    *(uint32_t*)((long long)param_1 + 0x194) = 2;
    *(uint32_t*)(param_1 + 0x33) = 5;
    *(uint32_t*)((long long)param_1 + 0x24) = 0;
    *(uint32_t*)((long long)param_1 + 0x26c) = 180000;
    *(uint32_t*)(param_1 + 0x4d) = 1;
    *(uint32_t*)(param_1 + 0x5e) = 0;
    *(uint32_t*)((long long)param_1 + 0x2f4) = 0;
    *(uint32_t*)(param_1 + 0x5f) = 0;
    *(uint32_t*)((long long)param_1 + 0x2fc) = 0;
    *(uint32_t*)(param_1 + 0x60) = 0;
    *(uint32_t*)((long long)param_1 + 0x304) = 0;
    *(uint32_t*)(param_1 + 0x61) = 0;
    *(uint32_t*)((long long)param_1 + 0x30c) = 0xb4;
    *(uint32_t*)(param_1 + 0x62) = 0;
    *(uint8_t*)((long long)param_1 + 0x2c) = 0;
    *(uint32_t*)(param_1 + 6) = 0;
    *(uint32_t*)((long long)param_1 + 0x314) = 0;
    // the two post-init clears
    MgrClear4b0((long long)(param_1 + 0x96));  // 141757740
    MgrClear4f8((long long)(param_1 + 0x9f));  // 1417577c0
    return param_1;
}

// ============ 141775800 — the MGR dtor ============
void MgrDtor(void* pMgr) {
    char** param_1 = (char**)pMgr;
    param_1[0] = (char*)g_fnMgrVftable;
    MgrMapDtor2770(param_1 + 0xa7);
    g_fnMeritOpDelete(param_1[0xa7]);
    MgrMapDtor23d0(param_1 + 0x9f);
    g_fnMeritOpDelete(param_1[0x9f]);
    MgrMapDtor2360(param_1 + 0x96);
    g_fnMeritOpDelete(param_1[0x96]);
    MgrMapDtor5400(param_1 + 0x8e);
    g_fnMeritOpDelete(param_1[0x8e]);
    MgrMapDtor5400(param_1 + 0x86);
    g_fnMeritOpDelete(param_1[0x86]);
    MgrMapDtor5400(param_1 + 0x7e);
    g_fnMeritOpDelete(param_1[0x7e]);
    MgrMapDtor5400(param_1 + 0x76);
    g_fnMeritOpDelete(param_1[0x76]);
    MgrMapDtor5400(param_1 + 0x6e);
    g_fnMeritOpDelete(param_1[0x6e]);
    MgrMapDtor1fd0(param_1 + 99);
    g_fnMeritOpDelete(param_1[99]);
    MgrMapDtor5680(param_1 + 0x56);
    g_fnMeritOpDelete(param_1[0x56]);
    MgrMapDtor028(param_1 + 0x4e);
    g_fnMeritOpDelete(param_1[0x4e]);
    MgrMapDtor1f60(param_1 + 0x45);
    g_fnMeritOpDelete(param_1[0x45]);
    MgrMapDtor028(param_1 + 0x3c);
    g_fnMeritOpDelete(param_1[0x3c]);
    LeagueUsersMapDtor(param_1 + 0x34);   // 141730e80
    g_fnMeritOpDelete(param_1[0x34]);
    MgrMapDtor028(param_1 + 0x29);
    g_fnMeritOpDelete(param_1[0x29]);
    MgrMapDtor1bd0(param_1 + 0x21);
    g_fnMeritOpDelete(param_1[0x21]);
    // the +0xd8 inline group
    if (param_1[0x1e] != nullptr) {
        g_fnMeritOpDelete(param_1[0x1e]);
    }
    param_1[0x1e] = nullptr;
    param_1[0x1f] = nullptr;
    param_1[0x20] = nullptr;
    g_fnMeritOpDelete(param_1[0x1b]);
    // the +0xa8 group
    if (param_1[0x18] != nullptr) {
        g_fnMeritOpDelete(param_1[0x18]);
    }
    param_1[0x18] = nullptr;
    param_1[0x19] = nullptr;
    param_1[0x1a] = nullptr;
    g_fnMeritOpDelete(param_1[0x15]);
    // the +0x78 group
    if (param_1[0x12] != nullptr) {
        g_fnMeritOpDelete(param_1[0x12]);
    }
    param_1[0x12] = nullptr;
    param_1[0x13] = nullptr;
    param_1[0x14] = nullptr;
    g_fnMeritOpDelete(param_1[0xf]);
    MgrMapDtorC2f0(param_1 + 7);
    g_fnMeritOpDelete(param_1[7]);
}

// ============ 141775df0 — the deleting dtor ============
void* MgrDeletingDtor(void* pMgr, uint32_t uFlags) {
    char** param_1 = (char**)pMgr;
    MgrDtor(param_1);
    if ((uFlags & 1) != 0) {
        g_fnMeritOpDelete(param_1);
    }
    return param_1;
}

}  // namespace syndicate
