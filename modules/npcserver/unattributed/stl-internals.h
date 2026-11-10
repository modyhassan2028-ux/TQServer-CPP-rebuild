// The container-internal bodies of NpcServer.exe 0x140080000..0x140090000.
//
// Every function here was transcribed from that address's own decompiled body by tools/gen_stl_family.py: the
// shapes repeat, so the offsets and deltas were read back out of each body rather than assumed. A body that did not
// match a known shape was left out and is listed in Docs/PORTING_LOG.md.
#ifndef TQ_NPCSERVER_STL_INTERNALS_H
#define TQ_NPCSERVER_STL_INTERNALS_H

#include <cstddef>

namespace tq {

// _invalid_parameter_noinfo, behind the same seam the rest of the module uses.
void NpcInvalidParameter(void);

// One entry per ported body, so a suite can walk the whole family.
struct NpcStlEntry {
    const char* pszAddress;
    const char* pszFamily;
    void*       pfn;
    int         nArg1;
    int         nArg2;
    int         nArg3;
};

long long    FUN_140080020(long long* pThis);
void         FUN_140080100(void** pThis);
void         FUN_140080130(void** pThis);
long long    FUN_140080170(long long* pThis);
bool         FUN_140080680(long long* pFirst, long long* pSecond);
bool         FUN_140080ba0(long long* pFirst, long long* pSecond);
bool         FUN_140080f00(long long* pFirst, long long* pSecond);
long long    FUN_140080f40(long long* pThis);
bool         FUN_140080fd0(long long* pFirst, long long* pSecond);
void         FUN_140081010(void** pThis);
void         FUN_140081020(void** pThis);
void         FUN_140081030(char* pThis);
void         FUN_140081070(void** pThis);
void         FUN_140081080(void** pThis);
void         FUN_140081090(char* pThis);
void         FUN_1400810d0(char* pThis);
void         FUN_140081110(char* pThis);
void         FUN_140081150(char* pThis);
long long    FUN_140081190(long long* pThis);
long long    FUN_1400811d0(long long* pThis);
void         FUN_140081270(void** pThis);
void         FUN_140081290(void** pThis);
void**       FUN_1400812d0(void** pThis);
void**       FUN_140081640(void** pThis);
void**       FUN_140081710(void** pThis);
void**       FUN_140081800(void** pThis);
void**       FUN_140081840(void** pThis);
bool         FUN_1400818a0(long long* pFirst, long long* pSecond);
bool         FUN_140081bc0(long long* pFirst, long long* pSecond);
void         FUN_140081dc0(char* pThis);
void         FUN_140081e30(char* pThis);
void         FUN_140081e90(char* pThis);
void         FUN_140081ed0(char* pThis);
void         FUN_140081f10(char* pThis);
long long    FUN_140081f50(long long* pThis);
long long    FUN_140081f90(long long* pThis);
long long    FUN_140081fd0(long long* pThis);
long long    FUN_140082010(long long* pThis);
void         FUN_1400820a0(void** pThis);
void         FUN_1400820c0(void** pThis);
void         FUN_1400820e0(void** pThis);
void**       FUN_140082170(void** pThis);
void**       FUN_140082200(void** pThis);
void**       FUN_140082470(void** pThis);
void**       FUN_1400825b0(void** pThis);
void**       FUN_1400828c0(void** pThis);
void**       FUN_140082930(void** pThis);
void         FUN_140082c70(char* pThis);
void         FUN_140082cc0(char* pThis);
void         FUN_140082d10(char* pThis);
void         FUN_140083100(void** pThis);
void         FUN_140083120(void** pThis);
void**       FUN_1400834c0(void** pThis);
void**       FUN_140083540(void** pThis);
void         FUN_140083b50(char* pThis);
void         FUN_140084100(void** pThis);
void         FUN_140084120(void** pThis);
void**       FUN_140084180(void** pThis);
void**       FUN_140084250(void** pThis);
void         FUN_1400845b0(char* pThis);
void         FUN_140084600(char* pThis);
bool         FUN_14008d950(long long* pFirst, long long* pSecond);
bool         FUN_14008d9b0(long long* pFirst, long long* pSecond);
long long    FUN_14008db20(long long* pThis);
bool         FUN_14008e0c0(long long* pFirst, long long* pSecond);
bool         FUN_14008e100(long long* pFirst, long long* pSecond);
void         FUN_14008e150(void** pThis);
void         FUN_14008e180(void** pThis);
long long    FUN_14008e190(long long* pThis);
long long    FUN_14008e1d0(long long* pThis);
long long    FUN_14008e210(long long* pThis);
void**       FUN_14008e770(void** pThis);
void**       FUN_14008e7b0(void** pThis);
long long    FUN_14008e870(long long* pThis);
long long    FUN_14008e8b0(long long* pThis);
void         FUN_14008e940(void** pThis);
void         FUN_14008e960(void** pThis);
void**       FUN_14008f1a0(void** pThis);
void**       FUN_14008f1f0(void** pThis);
void         FUN_14008f3c0(void** pThis);
void         FUN_14008f3e0(void** pThis);
void**       FUN_14008fa30(void** pThis);
void**       FUN_14008fa80(void** pThis);
void         FUN_14008fad0(char* pThis);
void         FUN_14008fcb0(void** pThis);
void         FUN_14008fcd0(void** pThis);

extern const NpcStlEntry g_aNpcStl_140080000[];
extern const int g_nNpcStl_140080000;

}  // namespace tq

#endif
