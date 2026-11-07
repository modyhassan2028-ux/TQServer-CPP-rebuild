// Lifted mechanically by tools/bulk/lift.py - one C++ statement per x86 instruction.
// Registers are uint64_t, memory goes through width-tagged accessors, flags are computed explicitly.
#pragma once
#include <cstdint>

#define ML_M1(p, o) (*(uint8_t*)((uint8_t*)(uintptr_t)(p) + (o)))
#define ML_M2(p, o) (*(uint16_t*)((uint8_t*)(uintptr_t)(p) + (o)))
#define ML_M4(p, o) (*(uint32_t*)((uint8_t*)(uintptr_t)(p) + (o)))
#define ML_M8(p, o) (*(uint64_t*)((uint8_t*)(uintptr_t)(p) + (o)))
#define ML_IAT(a) (*(uint64_t*)(uintptr_t)(a))

namespace tq {

extern uint64_t (*g_fnLIFT_1417293c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14172ae00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172ae00
extern uint64_t (*g_fnLIFT_141729790)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14172afb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172afb0
extern uint64_t (*g_fnLIFT_141729ba0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14172b6c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172b6c0
extern uint64_t (*g_fnLIFT_14173c5c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14173cea0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173cea0
extern uint64_t (*g_fnLIFT_14173e790)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14173ed60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173ed60
extern uint64_t (*g_fnLIFT_1417483e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141749690(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141749690
extern uint64_t (*g_fnLIFT_141748820)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141749a50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141749a50
extern uint64_t (*g_fnLIFT_1417585d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14175d840(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175d840
extern uint64_t (*g_fnLIFT_141758a10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14175dd50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175dd50
extern uint64_t (*g_fnLIFT_14175bfb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417601b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417601b0
extern uint64_t (*g_fnLIFT_14175c600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417607a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417607a0
extern uint64_t (*g_fnLIFT_14175ca70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141760bc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141760bc0
extern uint64_t (*g_fnLIFT_14175d350)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141761330(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141761330
extern uint64_t (*g_fnLIFT_141770600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141770ea0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141770ea0
extern uint64_t (*g_fnLIFT_141771050)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141773cb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141773cb0
extern uint64_t (*g_fnLIFT_14177af70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14177b650(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177b650
extern uint64_t (*g_fnLIFT_14178ba80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14178cb80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178cb80
extern uint64_t (*g_fnLIFT_141794e10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417970d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417970d0
extern uint64_t (*g_fnLIFT_141796d90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417995c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417995c0
extern uint64_t (*g_fnLIFT_1417a79e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417a7fb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a7fb0
extern uint64_t (*g_fnLIFT_1417c9310)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417cb580(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cb580
extern uint64_t (*g_fnLIFT_1417cbb60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417cd520(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cd520
}  // namespace tq
