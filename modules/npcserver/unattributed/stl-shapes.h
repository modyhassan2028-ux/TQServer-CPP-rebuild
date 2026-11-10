// The allocation, forward-move, range-check and position shapes of NpcServer.exe 0x140080000..0x140090000.
//
// Transcribed from each address's own decompiled text by tools/gen_stl_shapes.py; every element size, shift
// and member offset below was read out of that text. Bodies that do not match a shape are skipped, not
// approximated.
#ifndef TQ_NPCSERVER_STL_SHAPES_H
#define TQ_NPCSERVER_STL_SHAPES_H

#include <cstddef>

namespace tq {

// operator_new, as the image calls it (extern void* (*g_pfnNpcOperatorNew)(long long)).
extern void* (*g_pfnNpcOperatorNew)(long long nBytes);

// memmove_s: same contract the image uses (destination and source sizes both equal to the byte count).
// The default forwards to std::memmove; the image links the CRT wrapper instead.
extern void (*g_pfnNpcMemmoveS)(void* pDst, size_t cbDst, const void* pSrc, size_t cbSrc);

void NpcInvalidParameter(void);

void                   FUN_1400806e0(unsigned long long nCount);   // alloc-raw
void                   FUN_140080760(unsigned long long nCount);   // alloc-raw
void                   FUN_140080800(unsigned long long nCount);   // alloc-raw
void                   FUN_1400808a0(unsigned long long nCount);   // alloc-raw
void*                  FUN_140080ca0(void* pFirst, long long nLast, void* pDest);   // memmove-forward
void                   FUN_140081310(void* pAllocator, unsigned long long nCount);   // alloc-raw
void                   FUN_140081380(void* pAllocator, unsigned long long nCount);   // alloc-raw
void                   FUN_140081410(void* pAllocator, unsigned long long nCount);   // alloc-raw
void                   FUN_140081680(void* pAllocator, unsigned long long nCount);   // alloc-raw
void*                  FUN_140081cb0(void* pFirst, long long nLast, void* pDest);   // memmove-forward
unsigned long long*    FUN_140082760(unsigned long long* pOut, unsigned long long nPosition, unsigned long long* pSource);   // iterator-bounds
unsigned long long*    FUN_140082800(unsigned long long* pOut, unsigned long long nPosition, unsigned long long* pSource);   // iterator-bounds
unsigned long long*    FUN_140082860(unsigned long long* pOut, unsigned long long nPosition, unsigned long long* pSource);   // iterator-bounds
unsigned long long*    FUN_140082aa0(unsigned long long* pOut, unsigned long long* pSource);   // position-build
unsigned long long*    FUN_140082af0(unsigned long long* pOut, unsigned long long nPosition, unsigned long long* pSource);   // iterator-bounds
void*                  FUN_140082df0(void* pFirst, long long nLast, void* pDest);   // memmove-forward
unsigned long long*    FUN_1400831a0(unsigned long long* pOut, unsigned long long* pSource);   // position-build
unsigned long long*    FUN_1400831f0(unsigned long long* pOut, unsigned long long* pSource);   // position-build
unsigned long long*    FUN_1400832e0(unsigned long long* pOut, unsigned long long nPosition, unsigned long long* pSource);   // iterator-bounds
unsigned long long*    FUN_140083470(unsigned long long* pOut, unsigned long long* pSource);   // position-build
unsigned long long*    FUN_140083710(unsigned long long* pOut, unsigned long long nPosition, unsigned long long* pSource);   // iterator-bounds
void*                  FUN_1400839b0(void* pFirst, long long nLast, void* pDest);   // memmove-forward
unsigned long long*    FUN_140083db0(unsigned long long* pOut, unsigned long long* pSource);   // position-build
unsigned long long*    FUN_140083e00(unsigned long long* pOut, unsigned long long* pSource);   // position-build
unsigned long long*    FUN_1400843a0(unsigned long long* pOut, unsigned long long* pSource);   // position-build
unsigned long long*    FUN_1400843f0(unsigned long long* pOut, unsigned long long* pSource);   // position-build
void                   FUN_14008dde0(unsigned long long nCount);   // alloc-raw
void                   FUN_14008de60(unsigned long long nCount);   // alloc-raw
void                   FUN_14008e470(void* pAllocator, unsigned long long nCount);   // alloc-raw
void                   FUN_14008e6b0(void* pAllocator, unsigned long long nCount);   // alloc-raw

struct NpcShapeEntry {
    const char* pszAddress;
    const char* pszFamily;
    void*       pfn;
    long long   nElem;
    long long   nArg;
};

extern const NpcShapeEntry g_aNpcShape_140080000[];
extern const int g_nNpcShape_140080000;

}  // namespace tq

#endif
