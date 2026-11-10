// The template shapes that recur across the whole of NpcServer.exe.
//
// Transcribed from each address's own decompiled text by tools/gen_stl_global.py.
#ifndef TQ_NPCSERVER_STL_GLOBAL_H
#define TQ_NPCSERVER_STL_GLOBAL_H

#include <cstddef>

namespace tq {

extern void* (*g_pfnNpcOperatorNew)(long long nBytes);
extern void* (*g_pfnNpcOperatorDelete)(void* p);
extern void (*g_pfnNpcMemmoveS)(void* pDst, size_t cbDst, const void* pSrc, size_t cbSrc);

void         FUN_14001e5e0(void* pObject);   // delete-holder
void         FUN_14001e7b0(void* pObject);   // delete-holder
void*        FUN_14001ed70(void* pObject);   // node-push
void         FUN_14001ee00(void* pObject);   // delete-holder
void*        FUN_14001eee0(void* pObject);   // node-push
void         FUN_14001efd0(void* pObject);   // delete-holder
void*        FUN_14001f1a0(void* pObject);   // node-push
void         FUN_14001f1f0(void* pObject);   // delete-holder
void*        FUN_14001f280(void* pObject);   // node-push
void*        FUN_14001f300(void* pObject);   // node-push
void         FUN_140021c50(void* pObject);   // delete-holder
void         FUN_140021c80(void* pObject);   // delete-holder
void         FUN_1400227d0(void* pObject);   // delete-holder
void         FUN_1400227f0(void* pObject);   // delete-holder
void*        FUN_140022bd0(void* pObject);   // node-push
void*        FUN_140022c10(void* pObject);   // node-push
void         FUN_140022ce0(void* pObject);   // delete-holder
void         FUN_140022d00(void* pObject);   // delete-holder
void*        FUN_140023840(void* pObject);   // node-push
void*        FUN_140023890(void* pObject);   // node-push
void         FUN_140023a30(void* pObject);   // delete-holder
void         FUN_140023a50(void* pObject);   // delete-holder
void*        FUN_140024560(void* pObject);   // node-push
void*        FUN_1400245b0(void* pObject);   // node-push
void         FUN_140024d30(void* pObject);   // delete-holder
void         FUN_140024d50(void* pObject);   // delete-holder
void*        FUN_140024de0(void* pObject);   // node-push
void*        FUN_140024e30(void* pObject);   // node-push
void*        FUN_140025240(void* pObject);   // node-push
void*        FUN_140025290(void* pObject);   // node-push
void         FUN_140026cf0(void* pObject);   // delete-holder
void         FUN_140026d10(void* pObject);   // delete-holder
void         FUN_140026d30(void* pObject);   // delete-holder
void*        FUN_1400277f0(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_140027840(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_1400279c0(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_140027a00(void* pFirst, long long nLast, void* pDst);   // move-forward
void         FUN_140027c70(void* pObject);   // delete-holder
void         FUN_140027ca0(void* pObject);   // delete-holder
void         FUN_140027d20(void* pObject);   // delete-holder
void         FUN_140027dd0(void* pObject);   // delete-holder
void         FUN_140028150(void* pObject);   // delete-holder
void         FUN_140028170(void* pObject);   // delete-holder
void         FUN_1400281e0(void* pObject);   // delete-holder
void*        FUN_140028560(void* pObject);   // node-push
void*        FUN_140028620(void* pObject);   // node-push
void*        FUN_1400286d0(void* pObject);   // node-push
void*        FUN_140028710(void* pObject);   // node-push
void*        FUN_1400287e0(void* pObject);   // node-push
void*        FUN_1400289f0(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_140028a30(void* pFirst, long long nLast, void* pDst);   // move-forward
void         FUN_140028b10(void* pObject);   // delete-holder
void         FUN_140028b30(void* pObject);   // delete-holder
void         FUN_140028b50(void* pObject);   // delete-holder
void         FUN_140028b70(void* pObject);   // delete-holder
void         FUN_140028b90(void* pObject);   // delete-holder
void*        FUN_140028d90(void* pObject);   // node-push
void*        FUN_140028dd0(void* pObject);   // node-push
void*        FUN_140028ee0(void* pObject);   // node-push
void         FUN_1400291f0(void* pObject);   // delete-holder
void*        FUN_140029330(void* pObject);   // node-push
void*        FUN_1400293e0(void* pObject);   // node-push
void*        FUN_140029480(void* pObject);   // node-push
void*        FUN_1400294d0(void* pObject);   // node-push
void*        FUN_140029a10(void* pObject);   // node-push
void*        FUN_140029bc0(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_140029c00(void* pFirst, long long nLast, void* pDst);   // move-forward
void         FUN_140029c60(void* pObject);   // delete-holder
void         FUN_140029c80(void* pObject);   // delete-holder
void         FUN_140029ca0(void* pObject);   // delete-holder
void*        FUN_140029d10(void* pObject);   // node-push
void*        FUN_140029e10(void* pObject);   // node-push
void*        FUN_140029ef0(void* pObject);   // node-push
void         FUN_14002a2b0(void* pObject);   // delete-holder
void*        FUN_14002a380(void* pObject);   // node-push
void*        FUN_14002a3d0(void* pObject);   // node-push
void*        FUN_14002a4e0(void* pObject);   // node-push
void*        FUN_14002a610(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14002a650(void* pFirst, long long nLast, void* pDst);   // move-forward
void         FUN_14002ab80(void* pObject);   // delete-holder
void         FUN_14002aba0(void* pObject);   // delete-holder
void         FUN_14002ad10(void* pObject);   // delete-holder
void*        FUN_14002ad30(void* pObject);   // node-push
void*        FUN_14002ad80(void* pObject);   // node-push
void*        FUN_14002af80(void* pObject);   // node-push
void         FUN_14002ba10(void* pObject);   // delete-holder
void         FUN_14002ba30(void* pObject);   // delete-holder
void*        FUN_14002be20(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14002c010(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14002c230(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14002c300(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14002c970(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14002cb60(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14002cd80(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14002ce50(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14002d3b0(void* pObject);   // node-push
void*        FUN_14002d400(void* pObject);   // node-push
void*        FUN_14002da90(void* pObject);   // node-push
void         FUN_1400354b0(void* pObject);   // delete-holder
void         FUN_140035610(void* pObject);   // delete-holder
void*        FUN_140035b20(void* pObject);   // node-push
void         FUN_140035bd0(void* pObject);   // delete-holder
void*        FUN_140035cb0(void* pObject);   // node-push
void         FUN_140035f50(void* pObject);   // delete-holder
void*        FUN_140036120(void* pObject);   // node-push
void         FUN_1400362a0(void* pObject);   // delete-holder
void*        FUN_140036330(void* pObject);   // node-push
void*        FUN_1400363b0(void* pObject);   // node-push
void         FUN_1400386b0(void* pObject);   // delete-holder
void         FUN_140038ae0(void* pObject);   // delete-holder
void         FUN_140038c10(void* pObject);   // delete-holder
void*        FUN_140038f00(void* pObject);   // node-push
void         FUN_140038f90(void* pObject);   // delete-holder
void*        FUN_140039290(void* pObject);   // node-push
void*        FUN_1400392d0(void* pObject);   // node-push
void         FUN_140039320(void* pObject);   // delete-holder
void*        FUN_140039c30(void* pObject);   // node-push
void*        FUN_140039c80(void* pObject);   // node-push
void         FUN_140039cf0(void* pObject);   // delete-holder
void*        FUN_14003a220(void* pObject);   // node-push
void         FUN_14003a3c0(void* pObject);   // delete-holder
void*        FUN_14003aad0(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14003ad30(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14003aeb0(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14003b110(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14003b310(void* pObject);   // node-push
void         FUN_14003ccb0(void* pObject);   // delete-holder
void         FUN_14003cea0(void* pObject);   // delete-holder
void*        FUN_14003cf30(void* pObject);   // node-push
void*        FUN_14003cfa0(void* pObject);   // node-push
void*        FUN_14003d460(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14003d650(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14003d870(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14003d940(void* pFirst, long long nLast, void* pDst);   // move-forward
void         FUN_14003f3c0(void* pObject);   // delete-holder
void*        FUN_14003f7e0(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14003f840(void* pFirst, long long nLast, void* pDst);   // move-forward
void         FUN_14003f9e0(void* pObject);   // delete-holder
void*        FUN_14003fcb0(void* pFirst, long long nLast, void* pDst);   // move-forward
void         FUN_140040020(void* pObject);   // delete-holder
void         FUN_140040070(void* pObject);   // delete-holder
void         FUN_140040080(void* pObject);   // delete-holder
void         FUN_140040a70(void* pObject);   // delete-holder
void*        FUN_140040a90(void* pObject);   // node-push
void*        FUN_140040b10(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_140040b70(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_140040d10(void* pFirst, long long nLast, void* pDst);   // move-forward
void         FUN_140040d50(void* pObject);   // delete-holder
void*        FUN_140040e90(void* pObject);   // node-push
void         FUN_1400410c0(void* pObject);   // delete-holder
void         FUN_1400410e0(void* pObject);   // delete-holder
void         FUN_140041100(void* pObject);   // delete-holder
void*        FUN_140041580(void* pObject);   // node-push
void*        FUN_1400415c0(void* pObject);   // node-push
void*        FUN_140041600(void* pObject);   // node-push
void*        FUN_140041b10(void* pObject);   // node-push
void*        FUN_140041d20(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_140042150(void* pObject);   // node-push
void*        FUN_140042560(void* pObject);   // node-push
void*        FUN_1400425b0(void* pObject);   // node-push
void*        FUN_140042600(void* pObject);   // node-push
void         FUN_1400498e0(void* pObject);   // delete-holder
void*        FUN_14004a8f0(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14004aa10(void* pFirst, long long nLast, void* pDst);   // move-forward
void         FUN_14004b240(void* pObject);   // delete-holder
void         FUN_14004b250(void* pObject);   // delete-holder
void         FUN_14004b270(void* pObject);   // delete-holder
void         FUN_14004b340(void* pObject);   // delete-holder
void*        FUN_14004b550(void* pObject);   // node-push
void*        FUN_14004ba50(void* pObject);   // node-push
void*        FUN_14004bee0(void* pFirst, long long nLast, void* pDst);   // move-forward
void         FUN_14004cd50(void* pObject);   // delete-holder
void         FUN_14004cd70(void* pObject);   // delete-holder
void         FUN_14004cd90(void* pObject);   // delete-holder
void*        FUN_14004ce90(void* pObject);   // node-push
void*        FUN_14004ced0(void* pObject);   // node-push
void*        FUN_14004cf80(void* pObject);   // node-push
void*        FUN_14004d6e0(void* pObject);   // node-push
void*        FUN_14004d9e0(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14004da20(void* pFirst, long long nLast, void* pDst);   // move-forward
void         FUN_14004e360(void* pObject);   // delete-holder
void*        FUN_14004e380(void* pObject);   // node-push
void*        FUN_14004e3d0(void* pObject);   // node-push
void*        FUN_14004f0c0(void* pObject);   // node-push
void*        FUN_14004f200(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14004f240(void* pFirst, long long nLast, void* pDst);   // move-forward
void         FUN_14004f5e0(void* pObject);   // delete-holder
void*        FUN_14004fc20(void* pObject);   // node-push
void         FUN_1400500a0(void* pObject);   // delete-holder
void*        FUN_1400504e0(void* pObject);   // node-push
void*        FUN_140059220(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14005b440(void* pFirst, long long nLast, void* pDst);   // move-forward
void         FUN_140067c30(void* pObject);   // delete-holder
void         FUN_140067cd0(void* pObject);   // delete-holder
void*        FUN_140067d60(void* pObject);   // node-push
void*        FUN_140067dd0(void* pObject);   // node-push
void*        FUN_140068290(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_140068480(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_1400686a0(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_140068770(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14006e630(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14006e930(void* pFirst, long long nLast, void* pDst);   // move-forward
void         FUN_14006ed40(void* pObject);   // delete-holder
void         FUN_14006edd0(void* pObject);   // delete-holder
void*        FUN_14006f2e0(void* pFirst, long long nLast, void* pDst);   // move-forward
void         FUN_14006f320(void* pObject);   // delete-holder
void         FUN_14006f340(void* pObject);   // delete-holder
void*        FUN_14006f430(void* pObject);   // node-push
void*        FUN_14006f5d0(void* pObject);   // node-push
void*        FUN_14006f610(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14006f880(void* pFirst, long long nLast, void* pDst);   // move-forward
void         FUN_14006f8e0(void* pObject);   // delete-holder
void*        FUN_14006f9d0(void* pObject);   // node-push
void*        FUN_14006fb40(void* pObject);   // node-push
void*        FUN_14006fc50(void* pFirst, long long nLast, void* pDst);   // move-forward
void*        FUN_14006ff80(void* pObject);   // node-push
void*        FUN_140090180(void* pObject);   // node-push
void*        FUN_1400901d0(void* pObject);   // node-push
void         FUN_140090cb0(void* pObject);   // delete-holder
void         FUN_140090cd0(void* pObject);   // delete-holder
void*        FUN_1400913d0(void* pObject);   // node-push
void*        FUN_140091420(void* pObject);   // node-push
void         FUN_140094b20(void* pObject);   // delete-holder
void         FUN_140094c70(void* pObject);   // delete-holder
void*        FUN_140094d90(void* pObject);   // node-push
void*        FUN_140095030(void* pObject);   // node-push

struct NpcGlobalEntry {
    const char* pszAddress;
    const char* pszFamily;
    void*       pfn;
    long long   nValue;
};

extern const NpcGlobalEntry g_aNpcGlobal[];
extern const int g_nNpcGlobal;

}  // namespace tq

#endif
