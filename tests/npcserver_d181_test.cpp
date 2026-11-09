// D181 — NpcServer.exe 0x140012660 event_config_free.
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include "modules/npcserver/unattributed/front-of-image.h"

using namespace tq;

static void* g_freed[8]; static const char* g_via[8]; static int g_freeN = 0;
static void Record(void* p, const char* how) {
    if (g_freeN < 8) { g_freed[g_freeN] = p; g_via[g_freeN] = how; }
    ++g_freeN;
}
static void* CrtFree(void* p) { Record(p, "crt"); return nullptr; }
static void* HookFree(void* p) { Record(p, "hook"); return nullptr; }

// the queue nodes the body expects: next at +0, prev at +8, name at +0x10
struct Node { void* pNext; void* pPrev; char* pszName; };

int main() {
    // a single node: the head takes the node's prev, and the queue empties
    {
        unsigned char cfg[0x30];
        std::memset(cfg, 0, sizeof cfg);
        static char szA[] = "poll";
        Node n; n.pNext = nullptr; n.pPrev = (void*)cfg; n.pszName = szA;
        *(void**)(cfg + 0) = &n;
        *(void**)(cfg + 8) = &n.pNext;
        g_pfnNpcCrtFree = &CrtFree; g_pfnNpcEventFree_140103fa8 = nullptr; g_freeN = 0;
        FUN_140012660(cfg);
        assert(g_freeN == 3);
        assert(g_freed[0] == (void*)szA && std::strcmp(g_via[0], "crt") == 0);      // the name first
        assert(g_freed[1] == (void*)&n && std::strcmp(g_via[1], "crt") == 0);       // then the node
        assert(g_freed[2] == (void*)cfg);                                          // then the config
        assert(*(void**)(cfg + 0) == nullptr);                                     // the queue is empty
        assert(*(void**)(cfg + 8) == (void*)cfg);                                  // the tail points at the head
        assert(n.pPrev == (void*)cfg);
    }

    // two nodes: the first one hands its prev to the second and only the tail is rewritten
    {
        unsigned char cfg[0x30];
        std::memset(cfg, 0, sizeof cfg);
        static char szA[] = "select";
        Node n1, n2;
        n1.pNext = &n2; n1.pPrev = (void*)cfg; n1.pszName = szA;
        n2.pNext = nullptr; n2.pPrev = &n1.pNext; n2.pszName = nullptr;            // no name on this one
        *(void**)(cfg + 0) = &n1;
        *(void**)(cfg + 8) = &n2.pNext;
        g_pfnNpcCrtFree = &CrtFree; g_pfnNpcEventFree_140103fa8 = nullptr; g_freeN = 0;
        FUN_140012660(cfg);
        assert(g_freeN == 4);                                                      // name, n1, n2, config
        assert(g_freed[0] == (void*)szA);
        assert(g_freed[1] == (void*)&n1);
        assert(g_freed[2] == (void*)&n2);                                          // the nameless node
        assert(g_freed[3] == (void*)cfg);
        assert(n2.pPrev == (void*)cfg);                                            // n1's prev moved on
        assert(*(void**)(cfg + 8) == (void*)cfg);
        assert(*(void**)(cfg + 0) == nullptr);
    }

    // with a hook installed every release goes through it, and never through the runtime free
    {
        unsigned char cfg[0x30];
        std::memset(cfg, 0, sizeof cfg);
        static char szA[] = "kqueue";
        Node n; n.pNext = nullptr; n.pPrev = (void*)cfg; n.pszName = szA;
        *(void**)(cfg + 0) = &n;
        *(void**)(cfg + 8) = &n.pNext;
        g_pfnNpcCrtFree = &CrtFree; g_pfnNpcEventFree_140103fa8 = &HookFree; g_freeN = 0;
        FUN_140012660(cfg);
        assert(g_freeN == 3);
        for (int i = 0; i < 3; ++i) assert(std::strcmp(g_via[i], "hook") == 0);
        assert(g_freed[0] == (void*)szA && g_freed[1] == (void*)&n && g_freed[2] == (void*)cfg);
    }

    // an empty config releases only itself
    {
        unsigned char cfg[0x30];
        std::memset(cfg, 0, sizeof cfg);
        g_pfnNpcCrtFree = &CrtFree; g_pfnNpcEventFree_140103fa8 = nullptr; g_freeN = 0;
        FUN_140012660(cfg);
        assert(g_freeN == 1 && g_freed[0] == (void*)cfg);
    }

    std::printf("NPCSERVER_D181_OK: 0x140012660 event_config_free\n");
    return 0;
}
