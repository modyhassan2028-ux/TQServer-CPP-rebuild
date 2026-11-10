// The forwarding wrappers and pair constructs of NpcServer.exe 0x140080000..0x140090000.
//
// Transcribed from each address's own decompiled body by tools/gen_stl_iterators.py. A wrapper calls the
// address the image calls; where that callee is not ported yet it goes through a seam named for the address.
#ifndef TQ_NPCSERVER_STL_ITERATORS_H
#define TQ_NPCSERVER_STL_ITERATORS_H

namespace tq {

long long*               FUN_1400804c0(long long* pThis, long long nValue);
long long*               FUN_1400817d0(long long* pThis, long long nValue);
long long*               FUN_140081880(long long* pThis, long long nValue);
unsigned long long*      FUN_140082310(unsigned long long* pPair, unsigned long long nSecond, unsigned long long* pSource);
unsigned long long*      FUN_1400827c0(unsigned long long* pPair, unsigned long long nSecond, unsigned long long* pSource);
unsigned long long*      FUN_1400833f0(unsigned long long* pPair, unsigned long long nSecond, unsigned long long* pSource);
unsigned long long*      FUN_140083430(unsigned long long* pPair, unsigned long long nSecond, unsigned long long* pSource);
long long*               FUN_140085a30(long long* pThis);
long long*               FUN_140085f40(long long* pThis, long long nValue);
long long*               FUN_1400863b0(long long* pThis);
long long*               FUN_140086410(long long* pThis);
long long*               FUN_140086da0(long long* pThis);
long long*               FUN_14008e750(long long* pThis);
long long*               FUN_14008e830(long long* pThis, long long nValue);
unsigned long long*      FUN_14008e980(unsigned long long* pPair, unsigned long long nSecond, unsigned long long* pSource);
long long*               FUN_14008ea50(long long* pThis);
long long*               FUN_14008ea70(long long* pThis);
unsigned long long*      FUN_14008ea90(unsigned long long* pPair, unsigned long long nSecond, unsigned long long* pSource);
long long*               FUN_14008ead0(long long* pThis);
unsigned long long*      FUN_14008eaf0(unsigned long long* pPair, unsigned long long nSecond, unsigned long long* pSource);
long long*               FUN_14008f0e0(long long* pThis);
unsigned long long*      FUN_14008f4a0(unsigned long long* pPair, unsigned long long nSecond, unsigned long long* pSource);
long long*               FUN_14008f4e0(long long* pThis);

extern long long (*g_pfnNpc_140080450)(long long*, long long);
extern long long (*g_pfnNpc_140080560)(long long*, long long);
extern long long (*g_pfnNpc_140080610)(long long*, long long);
extern long long (*g_pfnNpc_1400848c0)(long long*);
extern long long (*g_pfnNpc_140085580)(long long*, long long);
extern long long (*g_pfnNpc_1400857f0)(long long*);
extern long long (*g_pfnNpc_14008dd10)(long long*);
extern long long (*g_pfnNpc_14008dfc0)(long long*, long long);
extern long long (*g_pfnNpc_14008e4e0)(long long*);
extern long long (*g_pfnNpc_14008e580)(long long*);
extern long long (*g_pfnNpc_14008e610)(long long*);

struct NpcIteratorEntry {
    const char* pszAddress;
    const char* pszFamily;
    void*       pfn;
    long long   nArg1;
};

extern const NpcIteratorEntry g_aNpcIter_140080000[];
extern const int g_nNpcIter_140080000;

}  // namespace tq

#endif
