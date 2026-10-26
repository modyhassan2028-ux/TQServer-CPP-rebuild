// ============================================================
// Syndicate.dll port — T14/D39: the release walks,
// verbatim (see SyndicateLeagueRelease.h).
// ============================================================
#include "SyndicateLeagueRelease.h"
#include "SyndicateCrossMerit.h"      // the opdelete/invalid seams
#include "SyndicateLeagueTree.h"      // LeagueFreeSubtree
#include "SyndicateLeagueLife.h"      // UsersFreeSubtree

namespace syndicate {

// ================= 141748ea0 =================
// the users release walk: the begin-walk with the CRT
// gates + the value dual-release, then the inlined
// map clear (users family)
void LeagueReleaseUsers(int64_t lEntity, int64_t lP2,
                        int64_t lP3, int64_t lP4) {
    char* param_1 = (char*)lEntity;
    (void)lP2; (void)lP3; (void)lP4;
    // plVar6 = **(head) — the FIRST node
    char** plVar6 =
        *(char***)*(char**)(param_1 + 0x88);
    // plVar2 = the map proxy @+0x58
    char** plVar2 = *(char***)(param_1 + 0x58);
    char** plVar3;
    char** plVar5;
    char cVar1;
    while (true) {
        plVar3 = *(char***)(param_1 + 0x88);  // the head
        if ((plVar2 == nullptr)
            || (plVar2 != *(char***)(param_1 + 0x58))) {
            g_fnMeritInvalid();
        }
        if (plVar6 == plVar3) break;   // END
        // lVar7 = *proxy = the owner back-ref (the map)
        int64_t lVar7 = (plVar2 == nullptr)
            ? 0 : *(int64_t*)plVar2;
        if (plVar6 == *(char***)(lVar7 + 0x30)) {
            g_fnMeritInvalid();
        }
        // the node VALUE @+0x20 → rec->vt[0](rec, 1)
        char** puVar4 = (char**)*(int64_t*)((char*)plVar6 + 0x20);
        if (puVar4 != nullptr) {
            void** vt = *(void***)puVar4;
            ((void (*)(void*, int64_t))vt[0])(
                (void*)puVar4, 1);
        }
        if (plVar2 == nullptr) {
            g_fnMeritInvalid();
        }
        // the inline successor advance (isnil@0x29)
        if (*(char*)((char*)plVar6 + 0x29) == '\0') {
            plVar3 = *(char***)((char*)plVar6 + 0x10);
            if (*(char*)((char*)plVar3 + 0x29) == '\0') {
                // the do-style prelude: plVar6 = the right
                // child first, plVar3 = its left, then the
                // descend loop (the roles VERBATIM)
                cVar1 = *(char*)(*(char**)plVar3 + 0x29);
                plVar6 = plVar3;
                plVar3 = *(char***)plVar3;
                while (cVar1 == '\0') {
                    cVar1 =
                        *(char*)(*(char**)plVar3 + 0x29);
                    plVar6 = plVar3;
                    plVar3 = *(char***)plVar3;
                }
            } else {
                cVar1 =
                    *(char*)(*(char**)((char*)plVar6 + 8)
                             + 0x29);
                plVar5 = *(char***)((char*)plVar6 + 8);
                plVar3 = plVar6;
                while (true) {
                    plVar6 = plVar5;
                    if (cVar1 != '\0'
                        || plVar3 != *(char***)(
                            (char*)plVar6 + 0x10)) break;
                    cVar1 =
                        *(char*)(*(char**)((char*)plVar6 + 8)
                                 + 0x29);
                    plVar5 = *(char***)((char*)plVar6 + 8);
                    plVar3 = plVar6;
                }
            }
        } else {
            g_fnMeritInvalid();
        }
    }
    // the inlined clear: root walk + the subtree free +
    // delete + the head relinks + size 0
    char* head = *(char**)(param_1 + 0x88);
    char* node = *(char**)(head + 8);   // the root
    cVar1 = *(char*)(node + 0x29);
    while (cVar1 == '\0') {
        UsersFreeSubtree((void*)(param_1 + 0x58),
            *(char**)(node + 0x10));    // the right
        char* next = *(char**)node;     // the left
        g_fnMeritOpDelete(node);
        node = next;
        cVar1 = *(char*)(node + 0x29);
    }
    *(char**)(head + 8) = head;
    *(uint64_t*)(param_1 + 0x90) = 0;
    *(char**)head = head;
    *(char**)(head + 0x10) = head;
}

// ================= 1417d4db0 =================
// the token release: the +8 sub-object dual-release +
// the token's OWN deleting dtor
void LeagueTokenRelease(void* pToken, int64_t lP2,
                        int64_t lP3, int64_t lP4) {
    char** param_1 = (char**)pToken;
    (void)lP2;
    if (param_1[1] != 0) {
        // vt[0](sub, 1, p3, p4, -2)
        void** vt = *(void***)param_1[1];
        ((void (*)(void*, int64_t, int64_t, int64_t,
                   int64_t))vt[0])(
            (void*)param_1[1], 1, lP3, lP4, -2);
        param_1[1] = 0;
        param_1[1] = 0;
    }
    // the token's OWN deleting dtor via vt slot 0
    void** tvt = *(void***)param_1;
    ((void (*)(void*, int64_t))tvt[0])(
        (void*)param_1, 1);
}

// ================= 141749040 =================
// the tokens release walk: the same begin-walk over
// the tokens map (+0xd8) with the TRIPLE CRT check
// blocks around the direct LeagueTokenRelease call +
// the value zeroed TWICE, then the inlined clear with
// the D32-family subtree free
void LeagueReleaseTokens(int64_t lEntity, int64_t lP2,
                         int64_t lP3, int64_t lP4) {
    char* param_1 = (char*)lEntity;
    // plVar5 = **(head) — the FIRST node
    char** plVar5 =
        *(char***)*(char**)(param_1 + 0x108);
    char** plVar2 = *(char***)(param_1 + 0xd8);
    char** plVar3;
    char** plVar4;
    char cVar1;
    int64_t lVar7 = 0;
    while (true) {
        plVar3 = *(char***)(param_1 + 0x108);
        if ((plVar2 == nullptr)
            || (plVar2 != *(char***)(param_1 + 0xd8))) {
            g_fnMeritInvalid();
        }
        if (plVar5 == plVar3) break;   // END
        if (plVar5[4] != 0) {   // the VALUE @+0x20
            // (the compiler duplicated the CRT check
            // block around each access — verbatim)
            int64_t lVar6 = (plVar2 == nullptr)
                ? lVar7 : *(int64_t*)plVar2;
            if (plVar5 == *(char***)(lVar6 + 0x30)) {
                g_fnMeritInvalid();
            }
            LeagueTokenRelease((void*)plVar5[4],
                               lP2, lP3, lP4);
            lVar6 = (plVar2 == nullptr)
                ? lVar7 : *(int64_t*)plVar2;
            if (plVar5 == *(char***)(lVar6 + 0x30)) {
                g_fnMeritInvalid();
            }
            plVar5[4] = 0;
            lVar6 = (plVar2 == nullptr)
                ? lVar7 : *(int64_t*)plVar2;
            if (plVar5 == *(char***)(lVar6 + 0x30)) {
                g_fnMeritInvalid();
            }
            plVar5[4] = 0;
        }
        if (plVar2 == nullptr) {
            g_fnMeritInvalid();
        }
        // the inline successor advance (isnil@0x29)
        if (*(char*)((char*)plVar5 + 0x29) == '\0') {
            plVar3 = *(char***)((char*)plVar5 + 0x10);
            if (*(char*)((char*)plVar3 + 0x29) == '\0') {
                // the do-style prelude, the roles VERBATIM
                cVar1 = *(char*)(*(char**)plVar3 + 0x29);
                plVar5 = plVar3;
                plVar3 = *(char***)plVar3;
                while (cVar1 == '\0') {
                    cVar1 =
                        *(char*)(*(char**)plVar3 + 0x29);
                    plVar5 = plVar3;
                    plVar3 = *(char***)plVar3;
                }
            } else {
                cVar1 =
                    *(char*)(*(char**)((char*)plVar5 + 8)
                             + 0x29);
                plVar4 = *(char***)((char*)plVar5 + 8);
                plVar3 = plVar5;
                while (true) {
                    plVar5 = plVar4;
                    if (cVar1 != '\0'
                        || plVar3 != *(char***)(
                            (char*)plVar5 + 0x10)) break;
                    cVar1 =
                        *(char*)(*(char**)((char*)plVar5 + 8)
                                 + 0x29);
                    plVar4 = *(char***)((char*)plVar5 + 8);
                    plVar3 = plVar5;
                }
            }
        } else {
            g_fnMeritInvalid();
        }
    }
    // the inlined clear (the D32 family)
    char* head = *(char**)(param_1 + 0x108);
    char* node = *(char**)(head + 8);   // the root
    cVar1 = *(char*)(node + 0x29);
    while (cVar1 == '\0') {
        LeagueFreeSubtree((void*)(param_1 + 0xd8),
            *(char**)(node + 0x10));    // the right
        char* next = *(char**)node;     // the left
        g_fnMeritOpDelete(node);
        node = next;
        cVar1 = *(char*)(node + 0x29);
    }
    *(char**)(head + 8) = head;
    *(uint64_t*)(param_1 + 0x110) = 0;
    *(char**)head = head;
    *(char**)(head + 0x10) = head;
}

}  // namespace syndicate
