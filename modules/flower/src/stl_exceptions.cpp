// stl_exceptions.cpp — RAW Flower.dll v6159
#include "modules/flower/src/stl_exceptions.h"
#include <cstring>

namespace flower {
namespace stl {

uintptr_t g_uBadAllocVft = 0;
uintptr_t g_uLogicErrorVft = 0;
uintptr_t g_uLengthErrorVft = 0;
uintptr_t g_uOutOfRangeVft = 0;

// the MSVC basic_string copy: 16 bytes or fewer live in the SSO buffer
void MsString::CopyFrom(const std::string& s) {
    uSize = s.size();
    if (uSize > 0xf) {
        pszHeap = (char*)::operator new(uSize + 1);
        ::memcpy(pszHeap, s.data(), uSize);
        pszHeap[uSize] = '\0';
        uCap = uSize;
    } else {
        ::memcpy(szSso, s.data(), uSize);
        szSso[uSize] = '\0';
        uCap = 0xf;
    }
}

void MsString::Release() {
    if (uCap > 0xf) ::operator delete(pszHeap);
    uCap = 0xf;
    uSize = 0;
    szSso[0] = '\0';
}

// 0x140d93bc0
void BadAllocCtor(void* pSelf, const char* szWhat) {
    (void)szWhat;
    *reinterpret_cast<uintptr_t*>(pSelf) = g_uBadAllocVft;
}

// 0x140d93c30
void BadAllocDtor(void* pSelf, uint32_t uFlag) {
    if ((uFlag & 1) != 0) ::operator delete(pSelf);
}

// 0x140d93c90
void EmptyStub() {}

// 0x140d93ca0
void LogicErrorCtor(void* pSelf, const std::string* pText) {
    *reinterpret_cast<uintptr_t*>(pSelf) = g_uLogicErrorVft;
    reinterpret_cast<MsLogicError*>(pSelf)->strText.CopyFrom(*pText);
}

// 0x140d93d30 — what(): the heap pointer past 15 bytes, else the SSO buffer
const char* LogicErrorWhat(void* pSelf) {
    const MsString& s = reinterpret_cast<MsLogicError*>(pSelf)->strText;
    return s.uCap > 0xf ? s.pszHeap : s.szSso;
}

// 0x140d93d50
void LogicErrorDtor(void* pSelf, uint32_t uFlag) {
    reinterpret_cast<MsLogicError*>(pSelf)->strText.Release();
    if ((uFlag & 1) != 0) ::operator delete(pSelf);
}

// 0x140d93db0 — logic_error ctor first, then the length_error vftable
void LengthErrorCtor(void* pSelf, const std::string* pText) {
    LogicErrorCtor(pSelf, pText);
    *reinterpret_cast<uintptr_t*>(pSelf) = g_uLengthErrorVft;
}

// 0x140d93e60
void LengthErrorDtor(void* pSelf, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(pSelf) = g_uLogicErrorVft;
    LogicErrorDtor(pSelf, uFlag);
}

// 0x140d93ed0
void OutOfRangeCtor(void* pSelf, const std::string* pText) {
    LogicErrorCtor(pSelf, pText);
    *reinterpret_cast<uintptr_t*>(pSelf) = g_uOutOfRangeVft;
}

// 0x140d93f80
void OutOfRangeDtor(void* pSelf, uint32_t uFlag) {
    *reinterpret_cast<uintptr_t*>(pSelf) = g_uLogicErrorVft;
    LogicErrorDtor(pSelf, uFlag);
}

}  // namespace stl
}  // namespace flower
