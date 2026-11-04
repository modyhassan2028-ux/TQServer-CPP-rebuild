// synuserattr.cpp — see synuserattr.h
#include "modules/syndicate/src/synuserattr.h"

#include "modules/syndicate/src/msg/msgseams.h"

#include <cstddef>

namespace tq {
namespace {

// the raw vtable dispatch: provider->vt[2](provider, index) -> container, then container->vt[slot]
void* GetContainer(void* pProvider, int nIndex) {
    typedef void* (*Slot2Fn)(void*, int);
    void** ppVt = *(void***)pProvider;
    return ((Slot2Fn)ppVt[2])(pProvider, nIndex);
}

uint64_t CallQword(void* pContainer, size_t uSlot) {
    typedef uint64_t (*GetFn)(void*);
    void** ppVt = *(void***)pContainer;
    return ((GetFn)ppVt[uSlot])(pContainer);
}

const char* CallString(void* pContainer, size_t uSlot) {
    typedef const char* (*GetFn)(void*);
    void** ppVt = *(void***)pContainer;
    return ((GetFn)ppVt[uSlot])(pContainer);
}

// the shared gate: user + 0x428, with the CHECKF report on each getter's own source line
void* ProviderOf(void* pUser, int nLine) {
    void* pProvider = *(void**)((uint8_t*)pUser + 0x428);
    if (pProvider == nullptr) {
        // ORIGINAL: call [0x141823030](&DAT_141824ca8, 0x14182666c, 0x141828944, 0x1418319b0, line)
        // the four data pointers stay raw on purpose: they address strings inside the original
        // image, which the port does not carry
        ::syndicate::g_fn_141823030((const char*)0x141824ca8ULL, (const void*)0x14182666cULL,
                                    (const void*)0x141828944ULL, (const void*)0x1418319b0ULL,
                                    nLine);
    }
    return pProvider;
}

}  // namespace

// 0x14178f270 — the id, slot 8 of the container at index 0
uint64_t SynUserAttrId(void* pUser) {
    void* pProvider = ProviderOf(pUser, 0x862);
    if (pProvider == nullptr) return 0;
    return CallQword(GetContainer(pProvider, 0), 8);
}

// 0x14178f330 — the name, slot 0xf of the container at index 2, "" when the provider is gone
const char* SynUserAttrName(void* pUser) {
    void* pProvider = ProviderOf(pUser, 0x87c);
    if (pProvider == nullptr) return "";
    return CallString(GetContainer(pProvider, 2), 0xf);
}

// 0x14178f3a0 — the number, slot 9 of the container at index 0x2b
uint64_t SynUserAttrNumber(void* pUser) {
    void* pProvider = ProviderOf(pUser, 0x889);
    if (pProvider == nullptr) return 0;
    return CallQword(GetContainer(pProvider, 0x2b), 9);
}

}  // namespace tq
