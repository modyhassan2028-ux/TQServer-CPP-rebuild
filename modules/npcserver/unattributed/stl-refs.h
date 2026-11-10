// The shared-owner and length-error shapes of NpcServer.exe 0x140080000..0x140090000.
//
// Transcribed from each address's own decompiled text by tools/gen_stl_refs.py. The control-block offsets,
// the two reference counters and the vtable slots are the ones that text names.
#ifndef TQ_NPCSERVER_STL_REFS_H
#define TQ_NPCSERVER_STL_REFS_H

namespace tq {

extern void* (*g_pfnNpcOperatorDelete)(void* p);

void                   FUN_140080070(void);   // too-long
void                   FUN_140080260(void);   // too-long
void                   FUN_140080300(void);   // too-long
void                   FUN_1400803c0(void);   // too-long
void                   FUN_1400814a0(unsigned long long* pOut, unsigned long long pValue, void* pControl);   // ref-assign
void                   FUN_140081910(unsigned long long* pOut, unsigned long long pValue, void* pControl);   // ref-assign
void                   FUN_1400819a0(unsigned long long* pOut, unsigned long long pValue, void* pControl);   // ref-assign
void                   FUN_140081a30(unsigned long long* pOut, unsigned long long pValue, void* pControl);   // ref-assign
unsigned long long*    FUN_140081e00(unsigned long long* pOut, unsigned long long* pSource);   // ref-copy
void                   FUN_1400824c0(void);   // too-long
void                   FUN_140082600(void);   // too-long
void*                  FUN_140082e60(void* pThis, unsigned int nFlags);   // ref-release
unsigned long long*    FUN_140083060(unsigned long long* pOut, unsigned long long* pSource);   // ref-copy
unsigned long long*    FUN_1400830d0(unsigned long long* pOut, unsigned long long* pSource);   // ref-copy
unsigned long long*    FUN_1400836e0(unsigned long long* pOut, unsigned long long* pSource);   // ref-copy
void                   FUN_140086430(void);   // too-long


struct NpcRefEntry {
    const char* pszAddress;
    const char* pszFamily;
    void*       pfn;
    const char* pszText;
    long long   nOffset;
};

extern const NpcRefEntry g_aNpcRef_140080000[];
extern const int g_nNpcRef_140080000;

}  // namespace tq

#endif
