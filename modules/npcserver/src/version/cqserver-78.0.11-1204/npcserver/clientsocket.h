// version/cqserver-78.0.11-1204/npcserver/clientsocket.h
//
// This translation unit's provenance is evidence, not inference: the body at 0x1400017b0 passes
// "f:\version\cqserver-78.0.11-1204\npcserver\clientsocket.cpp" to log_InlineLogERROR itself.
#ifndef NPCSERVER_CLIENTSOCKET_H
#define NPCSERVER_CLIENTSOCKET_H

namespace tq {

// seams (definitions live in modules/npcserver/unattributed/front-of-image.cpp)
extern void (*g_pfnNpcInlineLogError)(const void* pMsg, ...);
extern unsigned char g_symNpcStr_1400be0b0;                    // DAT_1400be0b0
extern void* (*g_pfnNpcKernelFrom_1400022e0)(long long hKernelThread);   // FUN_1400022e0
extern void  (*g_pfnNpcTickAnalystCtor)(void* pThis, int nId);           // CTickAnalyst::CTickAnalyst
extern void  (*g_pfnNpcTickAnalystDtor)(void* pThis);                    // CTickAnalyst::~CTickAnalyst

void FUN_1400017b0(long long pThis);

}  // namespace tq

#endif
