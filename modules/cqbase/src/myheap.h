// ============================================================================
// myheap.h — RAW CQBase.dll v6159 · myheap.cpp
//   CMyBaseHeap  +0x00 the live allocation count (touched under LOCK),
//                +0x08 the std::string name, +0x30 the HANDLE of the heap
//   CMyHeap      +0x00 the CMyBaseHeap it owns
//   Every allocation goes through HeapAlloc with the zeroing flag 8 and every
//   count change is a lock prefixed add or subtract, exactly as written.
// +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
// MODELLING NOTE (declared, not guessed):
//   The Win32 heap entry points are seams so the units run off Windows; the
//   Windows build uses HeapCreate, HeapAlloc, HeapFree, HeapValidate and
//   HeapDestroy as they are. CMyHeapMgr::AddMyHeap is registered on construction
//   exactly as the original does, through a seam that keeps the same list.
// ============================================================================
#ifndef CQBASE_MYHEAP_H
#define CQBASE_MYHEAP_H

#include <cstdint>
#include <string>

namespace tq {

// the heap entry points, defaulted to the real ones on Windows
struct HeapApi {
    void* (*pfnCreate)(uint32_t uOptions, size_t uInitial, size_t uMaximum);
    void* (*pfnAlloc)(void* hHeap, uint32_t uFlags, size_t uBytes);
    bool (*pfnFree)(void* hHeap, uint32_t uFlags, void* pMem);
    bool (*pfnValidate)(void* hHeap, uint32_t uFlags, const void* pMem);
    bool (*pfnDestroy)(void* hHeap);
};
extern HeapApi g_HeapApi;

class CMyBaseHeap {
public:
    CMyBaseHeap(const char* pszName);              // 0x140b9d700
    ~CMyBaseHeap();
    void* Alloc(size_t uBytes);                    // 0x140b9d7d0
    void Free(void* pMem);                         // 0x140b9d840
    int32_t m_nNumAlloc;      // +0x00
    std::string m_strName;    // +0x08
    void* m_hHeap;            // +0x30
};

class CMyHeap {
public:
    CMyHeap(const char* pszName);                  // 0x140b9dac0
    ~CMyHeap();                                    // 0x140b9e0f0
    void* Alloc(size_t uBytes);                    // 0x140b9d980
    void Free(void* pMem);                         // 0x140b9d9b0
    bool IsValidPt(const void* pMem);              // 0x140b9da00
    CMyHeap& operator=(const CMyHeap& rOther);     // 0x140b9d6f0
    CMyBaseHeap* m_pBaseHeap;                      // +0x00
};

// the manager every heap files itself into
class CMyHeapMgr {
public:
    CMyHeapMgr& operator=(const CMyHeapMgr& rOther);   // 0x140b9d6e0
    void AddMyHeap(const char* pszName, CMyBaseHeap* pBase);   // 0x140b9f760
};
extern CMyHeapMgr g_MyHeapMgr;

}  // namespace tq
#endif
