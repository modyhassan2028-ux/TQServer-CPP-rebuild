// ============================================================================
// cqbase_d77 — the message block the throw sites build. Pinned here: the append calls answer the
//   BLOCK (that is what the original returns, and callers chain on it), the number is formatted
//   with "%d", and the block survives init/append/destroy/re-init in place.
// ============================================================================
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "modules/syndicate/src/synexc.h"

using namespace tq;

static int g_nChecks = 0;
#define CHECK(x) do { ++g_nChecks; if (!(x)) { \
    std::fprintf(stderr, "FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); std::abort(); } } while (0)

int main() {
    alignas(SynMsgBlock) unsigned char aStorage[sizeof(SynMsgBlock)];
    SynMsgBlock* p = (SynMsgBlock*)aStorage;

    // ---- init fills the three fields and starts an empty message
    {
        SynMsgBlock* pBack = SynMsgInit(p, 3, "syndicate.cc", 0x207);
        CHECK(pBack == p);
        CHECK(p->nKind == 3);
        CHECK(std::strcmp(p->pszFile, "syndicate.cc") == 0);
        CHECK(p->nLine == 0x207);
        CHECK(p->strMessage.empty());
    }

    // ---- append answers the block and grows the message in order
    {
        SynMsgBlock* pBack = SynMsgAppend(p, "Invalid ");
        CHECK(pBack == p);
        CHECK(p->strMessage == "Invalid ");
        SynMsgAppend(p, "tag");
        CHECK(p->strMessage == "Invalid tag");
    }

    // ---- the number goes in with "%d"
    {
        SynMsgBlock* pBack = SynMsgAppendNumber(p, 42);
        CHECK(pBack == p);
        CHECK(p->strMessage == "Invalid tag42");
        SynMsgAppend(p, " / ");
        SynMsgAppendNumber(p, -7);
        CHECK(p->strMessage == "Invalid tag42 / -7");
        SynMsgAppendNumber(p, 0);
        CHECK(p->strMessage == "Invalid tag42 / -70");
    }

    // ---- destroy then init again over the same bytes
    {
        SynMsgDestroy(p);
        SynMsgInit(p, 1, "second", 9);
        CHECK(p->nKind == 1);
        CHECK(p->strMessage.empty());
        SynMsgAppend(p, "again");
        CHECK(p->strMessage == "again");
        SynMsgDestroy(p);
    }

    std::printf("SYNDICATE_D77_OK: the message block, %d checks\n", g_nChecks);
    return 0;
}
