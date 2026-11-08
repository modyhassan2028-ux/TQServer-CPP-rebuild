// Batteries for the nine class slots in SyndicateDtorFamily.h. The expected sequence of
// effects is read off each body: destructor first, release only when `flags & 1`, and the
// value the body returns. Nothing here asserts behaviour the disassembly does not state.
#include "modules/syndicate/src/SyndicateDtorFamily.h"
#include <cstdio>
#include <cstring>
#include <vector>

using namespace tq;

static int g_checks, g_fails;
#define CHECK(x) do { ++g_checks; if (!(x)) { ++g_fails; std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); } } while (0)

static std::vector<const char*> g_log;
static void* g_last;

static void d_cross(void*)   { g_log.push_back("dtor<cross>"); }
static void d_league(void*)  { g_log.push_back("dtor<league>"); }
static void d_leaguemgr(void*) { g_log.push_back("dtor<leaguemgr>"); }
static void d_cis(void*)     { g_log.push_back("dtor<cis>"); }
static void d_cos(void*)     { g_log.push_back("dtor<cos>"); }
static void d_fatal(void*)   { g_log.push_back("dtor<fatal>"); }
static void d_fatalbase(void* p) { g_log.push_back("dtor<fatal+0x28>"); g_last = p; }
static void d_tibase(void*)  { g_log.push_back("dtor<typeinfo>"); }

static unsigned g_size_seen, g_size_arg;
static const void* g_name_seen;
static void d_tidestroy(void*, unsigned size, unsigned data, const void* name) {
    g_log.push_back("destroy");
    g_size_arg = size;
    g_size_seen = data;
    g_name_seen = name;
}

static void rel(void* p) { g_log.push_back("release"); g_last = p; }

static void reset() {
    g_log.clear();
    g_last = nullptr;
    g_size_seen = g_size_arg = 0;
    g_name_seen = nullptr;
    g_pfnSyRelease = rel;
    g_pfnSyFatalBaseDtor = d_fatalbase;
    g_pfnCCrossMeritMgrDtor = d_cross;
    g_pfnCLeagueDtor = d_league;
    g_pfnCLeagueMgrDtor = d_leaguemgr;
    g_pfnCopyingInputStreamDtor = d_cis;
    g_pfnCopyingOutputStreamDtor = d_cos;
    g_pfnFatalExceptionDtor = d_fatal;
    g_pfnTypeInfoBaseDtor = d_tibase;
    g_pfnTypeInfoDestroy = d_tidestroy;
}

int main() {
    // --- CCrossMeritMgr: vftable refreshed, owned object destroyed, then released, then self
    {
        reset();
        unsigned char object[0x20];
        std::memset(object, 0xCD, sizeof(object));
        *(void**)(object + 0x8) = (void*)0x1234;
        CCrossMeritMgr* self = (CCrossMeritMgr*)object;

        void* r = CCrossMeritMgr_ScalarDeletingDtor(self, 1);
        CHECK(r == (void*)self);
        CHECK(*(void**)object == (void*)(uintptr_t)0x141828048);   // the body writes this literal
        CHECK(g_last == (void*)self);                              // last release is the object itself
        // the body releases the owned pointer unconditionally, then the object only under bit 0
        CHECK(g_log.size() == 3);
        CHECK(std::strcmp(g_log[0], "dtor<cross>") == 0);
        CHECK(std::strcmp(g_log[1], "release") == 0);              // the owned pointer
        CHECK(std::strcmp(g_log[2], "release") == 0);              // the object itself

        // flags without bit 0: the same work minus the final release of the object
        reset();
        *(void**)(object + 0x8) = (void*)0x1234;
        void* r2 = CCrossMeritMgr_ScalarDeletingDtor(self, 0);
        CHECK(r2 == (void*)self);
        CHECK(g_log.size() == 2);
        CHECK(std::strcmp(g_log[0], "dtor<cross>") == 0);
        CHECK(std::strcmp(g_log[1], "release") == 0);
        CHECK(g_last == (void*)0x1234);                            // the owned pointer, not the object

        // any other flag bit does not make the body release the object either
        reset();
        *(void**)(object + 0x8) = (void*)0x1234;
        CCrossMeritMgr_ScalarDeletingDtor(self, 0x2);
        CHECK(g_log.size() == 2);
    }

    // --- the five plain deleting destructors: dtor, release if bit 0, return this
    {
        unsigned char storage[5][0x20];
        void* (*fns[5])(void*, unsigned) = {
            (void* (*)(void*, unsigned))CLeague_ScalarDeletingDtor,
            (void* (*)(void*, unsigned))CLeagueMgr_ScalarDeletingDtor,
            (void* (*)(void*, unsigned))CopyingInputStream_ScalarDeletingDtor,
            (void* (*)(void*, unsigned))CopyingOutputStream_ScalarDeletingDtor,
            (void* (*)(void*, unsigned))FatalException_ScalarDeletingDtor,
        };
        const char* dtors[5] = {"dtor<league>", "dtor<leaguemgr>", "dtor<cis>", "dtor<cos>", "dtor<fatal>"};
        for (int i = 0; i < 5; ++i) {
            std::memset(storage[i], 0x11, 0x20);
            reset();
            void* r = fns[i](storage[i], 1);
            CHECK(r == (void*)storage[i]);
            CHECK(g_log.size() == 2);
            CHECK(std::strcmp(g_log[0], dtors[i]) == 0);
            CHECK(std::strcmp(g_log[1], "release") == 0);
            CHECK(g_last == (void*)storage[i]);

            reset();
            r = fns[i](storage[i], 0);
            CHECK(r == (void*)storage[i]);
            CHECK(g_log.size() == 1);
            CHECK(std::strcmp(g_log[0], dtors[i]) == 0);
        }
    }

    // --- FatalException's second slot: tail call with this+0x28, never touches this
    {
        reset();
        FatalException* self = (FatalException*)0x5000;
        FatalException_BaseDtor(self);
        CHECK(g_log.size() == 1);
        CHECK(std::strcmp(g_log[0], "dtor<fatal+0x28>") == 0);
        CHECK(g_last == (void*)0x5028);
    }

    // --- type_info
    {
        reset();
        unsigned char raw[0x20];
        std::memset(raw, 0, sizeof(raw));
        *(unsigned*)(raw + 0x8) = 0x24;                       // the field read at this-8
        TypeInfo* self = (TypeInfo*)(raw + 0x10);
        void* r = TypeInfo_ScalarDeletingDtor(self, 2);
        CHECK(r == (void*)(raw + 0x8));                        // flags&2 arm returns this-8
        CHECK(g_size_arg == 0x18u);
        CHECK(g_size_seen == 0x24u);
        CHECK(g_name_seen == (const void*)(uintptr_t)0x1417f3b9c);
        CHECK(g_log.size() == 1);
        CHECK(std::strcmp(g_log[0], "destroy") == 0);

        reset();
        r = TypeInfo_ScalarDeletingDtor(self, 3);              // destroy, then release this-8
        CHECK(r == (void*)(raw + 0x8));
        CHECK(g_log.size() == 2);
        CHECK(std::strcmp(g_log[1], "release") == 0);
        CHECK(g_last == (void*)(raw + 0x8));

        reset();
        r = TypeInfo_ScalarDeletingDtor(self, 0);              // base destructor on this
        CHECK(r == (void*)self);
        CHECK(g_log.size() == 1);
        CHECK(std::strcmp(g_log[0], "dtor<typeinfo>") == 0);

        reset();
        r = TypeInfo_ScalarDeletingDtor(self, 1);              // base destructor, then release this
        CHECK(r == (void*)self);
        CHECK(g_log.size() == 2);
        CHECK(g_last == (void*)self);
    }

    // --- Thank_you's only slot is `ret 0`: no side effect at all
    {
        reset();
        ThankYou_EmptySlot((void*)0x7000);
        CHECK(g_log.empty());
    }

    std::printf("%s checks=%d fails=%d\n", g_fails ? "DTOR_FAMILY_FAIL" : "DTOR_FAMILY_OK",
                g_checks, g_fails);
    return g_fails ? 1 : 0;
}
