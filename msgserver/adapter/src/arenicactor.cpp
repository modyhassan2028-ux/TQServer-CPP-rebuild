#include "arenicactor.h"
#include <cstring>
#include <cstdio>
#if defined(_MSC_VER)
#define RAW_SNPRINTF _snprintf
#else
#define RAW_SNPRINTF snprintf
#endif
// RAW builds the same 0x100 buffer with memset(&buf[1],0,0xff) and forces
// buf[0xff] = 0 afterwards; both are kept. The decompiler recovered only
// one vararg for the two format specs, so the id value is passed to both
// and that elision is declared in the handoff.
namespace adapter {
int CArenicActor::OnUserArenicWin(int id, uint32_t n, SArenicActorSeams& s) {
    if (id == 0) return 0;
    char buf[0x100];
    buf[0] = 0;
    std::memset(&buf[1], 0, 0xff);
    RAW_SNPRINTF(buf, 0x100, "</F>UserArenicWins</N>%lu</N>%u",
                 (unsigned long)n, n);
    buf[0xff] = 0;
    void* lua = s.LuaState();
    if (lua == nullptr) { s.LogCheck(0x3cd); lua = nullptr; }
    if (s.CallLua(lua, buf, id, 0) == 0)
        s.LogLuaFault("CArenicActor::OnUserArenicWin");
    return 1;
}
int CArenicActor::OnUserArenicCompete(int id, uint32_t n, SArenicActorSeams& s) {
    if (id == 0) return 0;
    char buf[0x100];
    buf[0] = 0;
    std::memset(&buf[1], 0, 0xff);
    RAW_SNPRINTF(buf, 0x100, "</F>UserArenicCompetes</N>%lu</N>%u",
                 (unsigned long)n, n);
    buf[0xff] = 0;
    void* lua = s.LuaState();
    if (lua == nullptr) { s.LogCheck(0x3cd); lua = nullptr; }
    if (s.CallLua(lua, buf, id, 0) == 0)
        s.LogLuaFault("CArenicActor::OnUserArenicCompete");
    return 1;
}
} // namespace adapter
