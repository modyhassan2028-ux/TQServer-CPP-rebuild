// Battery for CSynManager::SetValue (1417c5860). Expectations read off the bytes: two
// independent 32-bit id gates and a return of this+0x98.
#include "modules/syndicate/src/CSynManager.h"
#include <cstdio>
#include <cstring>

using namespace syndicate;

static int g_checks, g_fails;
#define CHECK(x) do { ++g_checks; if (!(x)) { ++g_fails; std::printf("FAILED %s:%d  %s\n", __FILE__, __LINE__, #x); } } while (0)

int main() {
    unsigned char object[0x100];
    std::memset(object, 0x5A, sizeof(object));
    CSynManager* mgr = (CSynManager*)object;

    void* r = mgr->SetValue(0x40e, 0x11223344);
    CHECK(r == (void*)(object + 0x98));                      // lea rax,[rcx+0x98]
    CHECK(*(uint32_t*)(object + 0xa8) == 0x11223344u);
    CHECK(*(uint32_t*)(object + 0xac) == 0x5A5A5A5Au);       // the other field untouched

    r = mgr->SetValue(1000, 0xDEADBEEF);
    CHECK(r == (void*)(object + 0x98));
    CHECK(*(uint32_t*)(object + 0xac) == 0xDEADBEEFu);
    CHECK(*(uint32_t*)(object + 0xa8) == 0x11223344u);       // first field kept

    // the first gate does not return: a second call with the other id still lands, and a value
    // written by the first gate survives it
    r = mgr->SetValue(0x40e, 7);
    CHECK(r == (void*)(object + 0x98));
    CHECK(*(uint32_t*)(object + 0xa8) == 7u);
    CHECK(*(uint32_t*)(object + 0xac) == 0xDEADBEEFu);

    // any other id writes nothing but still returns the same pointer
    std::memset(object, 0x11, sizeof(object));
    r = mgr->SetValue(0x40d, 0xFFFFFFFF);
    CHECK(r == (void*)(object + 0x98));
    CHECK(*(uint32_t*)(object + 0xa8) == 0x11111111u);
    CHECK(*(uint32_t*)(object + 0xac) == 0x11111111u);
    r = mgr->SetValue(0x3e9, 1);
    CHECK(*(uint32_t*)(object + 0xa8) == 0x11111111u);
    CHECK(*(uint32_t*)(object + 0xac) == 0x11111111u);

    // the store is 32-bit: a 64-bit value only keeps its low half in the field
    std::memset(object, 0, sizeof(object));
    mgr->SetValue(0x40e, 0xFFFFFFFFu);
    CHECK(*(uint32_t*)(object + 0xa8) == 0xFFFFFFFFu);
    CHECK(*(uint32_t*)(object + 0xac) == 0u);

    std::printf("%s checks=%d fails=%d\n", g_fails ? "CSYNMANAGER_FAIL" : "CSYNMANAGER_OK",
                g_checks, g_fails);
    return g_fails ? 1 : 0;
}
