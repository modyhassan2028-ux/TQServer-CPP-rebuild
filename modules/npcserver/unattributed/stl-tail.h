// Four tail shapes of NpcServer.exe 0x140080000..0x140090000.
//
// Transcribed from each address's own decompiled text by tools/gen_stl_tail.py.
#ifndef TQ_NPCSERVER_STL_TAIL_H
#define TQ_NPCSERVER_STL_TAIL_H

#include <cstddef>

namespace tq {

extern void (*g_pfnNpcMemmoveS)(void* pDst, size_t cbDst, const void* pSrc, size_t cbSrc);
void NpcInvalidParameter(void);
void FUN_1400814a0(unsigned long long* pOut, unsigned long long pValue, void* pControl);
void FUN_1400819a0(unsigned long long* pOut, unsigned long long pValue, void* pControl);
void FUN_140081a30(unsigned long long* pOut, unsigned long long pValue, void* pControl);

void*                  FUN_140080c40(void* pFirst, long long nLast, long long nDst);   // move-backward
void*                  FUN_140081b10(void* pFirst, long long nLast, long long nDst);   // move-backward
void                   FUN_140081c10(unsigned long long* pOut);   // clear-or-drop
void                   FUN_140082280(unsigned long long* pOut);   // clear-or-drop
void                   FUN_140082b70(unsigned long long* pOut, unsigned long long* pSource);   // ref-fill
void*                  FUN_140082c30(void* pFirst, long long nLast, long long nDst);   // move-backward
unsigned long long*    FUN_140082d80(unsigned long long* pSource, unsigned long long* pOut, long long pMember);   // position-member
unsigned long long*    FUN_140083630(unsigned long long* pSource, unsigned long long* pOut, long long pMember);   // position-member
unsigned long long*    FUN_140083770(unsigned long long* pSource, unsigned long long* pOut, long long pMember);   // position-member
void                   FUN_1400837d0(unsigned long long* pOut, unsigned long long* pSource);   // ref-fill
void                   FUN_140083b10(unsigned long long* pOut, unsigned long long* pSource);   // ref-fill
void                   FUN_14008e9c0(unsigned long long* pOut);   // clear-or-drop

struct NpcTailEntry {
    const char* pszAddress;
    const char* pszFamily;
    void*       pfn;
    long long   nValue;
};

extern const NpcTailEntry g_aNpcTail_140080000[];
extern const int g_nNpcTail_140080000;

}  // namespace tq

#endif
