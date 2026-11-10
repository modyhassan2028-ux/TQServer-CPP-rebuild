// D233 — the 226 template bodies that recur across NpcServer.exe: 88 node-push, 86 delete-holder, 52 move-forward.
#include <cassert>
#include <cstdio>
#include <cstring>
#include "modules/npcserver/unattributed/stl-global.h"

using namespace tq;

static char g_aArena[1 << 16];
static int g_news = 0, g_deletes = 0, g_moves = 0;
static void* g_pDeleted = nullptr;

static void* FakeNew(long long) { ++g_news; return g_aArena; }
static void* FakeDelete(void* p) { ++g_deletes; g_pDeleted = p; return p; }
static void FakeMove(void* pDst, size_t, const void* pSrc, size_t cbSrc) { ++g_moves; std::memmove(pDst, pSrc, cbSrc); }

int main() {
    g_pfnNpcOperatorNew = &FakeNew;
    g_pfnNpcOperatorDelete = &FakeDelete;
    g_pfnNpcMemmoveS = &FakeMove;

    assert(g_nNpcGlobal == 226);
    int nPush = 0, nDelete = 0, nMove = 0;

    for (int i = 0; i < g_nNpcGlobal; ++i) {
        const NpcGlobalEntry& e = g_aNpcGlobal[i];
        assert(e.pszAddress && e.pszFamily && e.pfn);

        if (std::strcmp(e.pszFamily, "node-push") == 0) {
            unsigned long long aObject[2] = { 0, 0 };
            std::memset(g_aArena, 0, 64);
            g_news = 0;
            void* pRet = ((void* (*)(void*))e.pfn)(aObject);
            assert(pRet == aObject);
            assert(g_news == 1);
            void** pNode = (void**)aObject[0];
            assert(pNode == (void**)g_aArena);            // the node is the freshly allocated block
            assert(pNode[0] == (void*)aObject);           // and it points back at the object
            ++nPush;

        } else if (std::strcmp(e.pszFamily, "delete-holder") == 0) {
            unsigned long long aObject[2] = { 0x1234, 0x5678 };
            g_deletes = 0; g_pDeleted = nullptr;
            ((void (*)(void*))e.pfn)(aObject);
            assert(g_deletes == 1);
            assert(g_pDeleted == (void*)0x1234ULL);       // the object's own first word, not the object
            ++nDelete;

        } else if (std::strcmp(e.pszFamily, "move-forward") == 0) {
            const long long nElem = e.nValue;
            unsigned char aFrom[64], aTo[128];
            std::memset(aFrom, 0x5A, sizeof aFrom);
            std::memset(aTo, 0, sizeof aTo);
            g_moves = 0;
            void* pEnd = ((void* (*)(void*, long long, void*))e.pfn)
                (aFrom, (long long)aFrom + 3 * nElem, aTo);
            assert(g_moves == 1);
            assert(pEnd == aTo + 3 * nElem);              // the returned end is one range past the destination
            assert(aTo[0] == 0x5A && aTo[3 * nElem - 1] == 0x5A && aTo[3 * nElem] == 0);
            g_moves = 0;
            pEnd = ((void* (*)(void*, long long, void*))e.pfn)(aFrom, (long long)aFrom, aTo);
            assert(pEnd == aTo && g_moves == 0);          // an empty range moves nothing
            ++nMove;

        } else {
            assert(!"unknown family in the manifest");
        }
    }

    assert(nPush == 88 && nDelete == 86 && nMove == 52);
    std::printf("NPCSERVER_D233_OK: 226 binary-wide template bodies\n");
    return 0;
}
