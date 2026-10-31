// The base-class constructions Flower.dll repeats for its own instances of
// tq::CMsg and gs::IModule. The vftable the dump names as a symbol has no
// address in the decompiled body, so each one is a seam the host installs.
#ifndef FLOWER_FLOWERBASE_H
#define FLOWER_FLOWERBASE_H

#include <cstdint>

namespace flower {

void* CMsgCtorFlower(void* p);                        // 0x140d97c10
void* CMsgBaseCtorFlower(void* p);                    // 0x140d97c40
void* CMsgDtorFlower(void* p, uint8_t uFlags);         // 0x140d97c80
void IModuleBaseCtorFlower(void* p);                   // 0x140d93240

// ---- the two initterm passes and the exit-state reset the CRT wrapper runs
void InitTermA();                                  // 0x140d98b94
void InitTermB();                                  // 0x140d98bcc
void ExitStateReset();                             // 0x140d9a6a1
extern int g_iFlowerExitState;

extern void* g_pVftCMsgFlowerBase;
extern void* g_pVftIModuleFlower;
extern void (*g_pfnCMsgInitFlower)(void*);

}  // namespace flower
#endif
