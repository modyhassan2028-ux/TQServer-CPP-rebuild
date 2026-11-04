// syniter2.cpp — see syniter2.h
#include "modules/syndicate/src/syniter2.h"

#include <new>

namespace tq {

namespace {

inline void** Vft(const void* p) { return *(void***)p; }

}  // namespace

// 0x1417c6c80
void SynIterDerefHolder(void* pIter) {
    uint8_t* p = (uint8_t*)pIter;
    void* pHolder = *(void**)(p + 0x98);
    ((void (*)(void))Vft(pHolder)[0x00 / 8])();
}

// 0x1417c6c90
void SynIterDerefSelf(void* pIter) {
    void* pOwner = *(void**)pIter;
    ((void (*)(void))Vft(pOwner)[0x00 / 8])();
}

// 0x1417c6ca0
bool SynIterEqualA(void* pLeft, void* pRight) {
    void** pL = (void**)pLeft;
    void** pR = (void**)pRight;
    if (pL[0] == nullptr || pL[0] != pR[0]) ::syndicate::g_fnInvalidParam();
    return pL[1] != pR[1];
}

// 0x1417c6ce0
bool SynIterEqualB(void* pLeft, void* pRight) {
    void** pL = (void**)pLeft;
    void** pR = (void**)pRight;
    if (pL[0] == nullptr || pL[0] != pR[0]) ::syndicate::g_fnInvalidParam();
    return pL[1] != pR[1];
}

// 0x1417c6d50
void SynIterDelete50(void* pIter) { ::operator delete(*(void**)pIter); }
// 0x1417c6d80
void SynIterDelete80(void* pIter) { ::operator delete(*(void**)pIter); }
// 0x1417c6db0
void SynIterDeleteB0(void* pIter) { ::operator delete(*(void**)pIter); }
// 0x1417c6f10
void SynIterDeleteF10(void* pIter) { ::operator delete(*(void**)pIter); }

// 0x1417c6dc0
void* SynIterValue(void* pIter) {
    void** p = (void**)pIter;
    void* pOwner = p[0];
    void* pHead = nullptr;
    if (pOwner == nullptr) {
        ::syndicate::g_fnInvalidParam();
        pOwner = p[0];
        pHead = nullptr;
        // the release build never returns from the call, so this jump is unreachable there
        if (pOwner == nullptr) goto Checked;
    }
    pHead = *(void**)pOwner;
Checked:
    if (p[1] == *(void**)((uint8_t*)pHead + 0x30)) ::syndicate::g_fnInvalidParam();
    return (uint8_t*)p[1] + 0x18;
}

// 0x1417c6e40
void* SynIterValue2(void* pIter) {
    void** p = (void**)pIter;
    void* pOwner = p[0];
    void* pHead = nullptr;
    if (pOwner == nullptr) {
        ::syndicate::g_fnInvalidParam();
        pOwner = p[0];
        pHead = nullptr;
        if (pOwner == nullptr) goto Checked;
    }
    pHead = *(void**)pOwner;
Checked:
    if (p[1] == *(void**)((uint8_t*)pHead + 0x30)) ::syndicate::g_fnInvalidParam();
    return (uint8_t*)p[1] + 0x18;
}

// 0x1417c6e00
void* SynIterInit(void* pOut, void* pOwner, void* pSource) {
    void** p = (void**)pOut;
    p[0] = nullptr;
    p[1] = pOwner;
    if (pSource == nullptr) ::syndicate::g_fnInvalidParam();
    // unreachable in the original: _invalid_parameter_noinfo terminates before this read
    p[0] = *(void**)pSource;
    return pOut;
}

}  // namespace tq
