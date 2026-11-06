// ============================================================================
// synpbiomisc.h — RAW Syndicate.dll v6159 · ten small bodies from the protobuf io area,
//   each read instruction by instruction:
//     0x1417e4b50  the argument-reloading thunk into 0x1417e5610 (two arguments)
//     0x1417e4c80  the argument-reloading thunk into 0x1417e5740 (two arguments)
//     0x1417e4fd0  return this->[0x18] - (0x1417e4fb0(this) + this->[0x2c])
//     0x1417e7400  return 0x1417e7770(this)
//     0x1417e7890  this->[0x2c] = 0; then 0x1417e7ba0(this + 0x20, 0)
//     0x1417e7b70  return 0x1417f37de(*(void**)this)
//     0x1417e7c00  return (*(void**)this == arg)
//     0x1417e7c50  KERNEL32 Sleep(0)   (xor ecx,ecx ; call [IAT])
//     0x1417e5a60  size() then data() on the string, handed to 0x1417e4790(data, size, sink)
//     0x1417e5a10  write one tag byte: under 0x80 it is stored and the sink advanced by one,
//                  from 0x80 on the body falls through to the 0x1417e4b50 thunk
// ============================================================================
#ifndef SYNDICATE_SYNPBIOMISC_H
#define SYNDICATE_SYNPBIOMISC_H

#include <cstdint>

namespace tq {

extern void* (*g_fnMisc5610)(uint32_t uA, void* pB);   // 0x1417e5610
extern void* (*g_fnMisc5740)(void* pA, void* pB);      // 0x1417e5740
extern int32_t (*g_fnMisc4FB0)(void* pThis);           // 0x1417e4fb0
extern bool (*g_fnMisc7770)(void* pThis);              // 0x1417e7770
extern void (*g_fnMisc7BA0)(void* pThis, void* pArg);  // 0x1417e7ba0
extern void* (*g_fnMisc37DE)(void* p);                 // 0x1417f37de
extern void (*g_fnMiscSleep)(uint32_t uMs);            // KERNEL32 Sleep
extern void* (*g_fnMiscWrite)(void* pData, int32_t nLen, void* pSink); // 0x1417e4790

void* SynMiscThunk5610(uint32_t uA, void* pB);   // 0x1417e4b50
void* SynMiscThunk5740(void* pA, void* pB);      // 0x1417e4c80
int32_t SynMiscRemaining(void* pThis);           // 0x1417e4fd0
bool SynMisc7770(void* pThis);                   // 0x1417e7400
void SynMiscReset(void* pThis);                  // 0x1417e7890
void* SynMisc37DE(void* pThis);                  // 0x1417e7b70
bool SynMiscPtrEq(void* pThis, const void* pOther);  // 0x1417e7c00
void SynMiscYield(void);                         // 0x1417e7c50
void* SynMiscWriteString(const void* pStr, void* pSink);  // 0x1417e5a60
void* SynMiscWriteTag(uint32_t uTag, void* pSink);        // 0x1417e5a10

}  // namespace tq

#endif  // SYNDICATE_SYNPBIOMISC_H
