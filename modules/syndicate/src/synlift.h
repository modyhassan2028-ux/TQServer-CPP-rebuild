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


uint64_t SynLift_1417224f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417224f0

uint64_t SynLift_141722680(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141722680

uint64_t SynLift_1417227e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417227e0
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141722ef0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141722ef0
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141722fc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141722fc0
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141723090(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141723090
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141723a50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141723a50

uint64_t SynLift_141724870(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141724870

uint64_t SynLift_141724950(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141724950

uint64_t SynLift_1417249e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417249e0

uint64_t SynLift_141724c50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141724c50

uint64_t SynLift_141724cb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141724cb0
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141724ed0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141724ed0

uint64_t SynLift_141725000(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141725000

uint64_t SynLift_141725060(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141725060
extern uint64_t (*g_fnLIFT_141724c50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141724cb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141724ed0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141728290(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141728290
extern uint64_t (*g_fnLIFT_141723a50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141725000)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141725060)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141728750(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141728750
extern uint64_t (*g_fnLIFT_1417224f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141722ef0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141724870)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14172b160(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172b160
extern uint64_t (*g_fnLIFT_141722680)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141723090)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141724950)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14172b870(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172b870
extern uint64_t (*g_fnLIFT_1417227e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141722fc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417249e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14172bd00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172bd00

uint64_t SynLift_14173b0e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173b0e0

uint64_t SynLift_14173b140(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173b140
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14173b240(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173b240
extern uint64_t (*g_fnLIFT_14173b0e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173b140)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173b240)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14173c0b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173c0b0

uint64_t SynLift_141744560(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141744560
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417447d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417447d0
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141744cb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141744cb0

uint64_t SynLift_141745ad0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141745ad0

uint64_t SynLift_141745c30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141745c30

uint64_t SynLift_141745c90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141745c90
extern uint64_t (*g_fnLIFT_141744cb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141745c30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141745c90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141747400(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141747400
extern uint64_t (*g_fnLIFT_141744560)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417447d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141745ad0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141749c00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141749c00

uint64_t SynLift_14174fe10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174fe10
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141750760(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141750760

uint64_t SynLift_141750a30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141750a30
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417512f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417512f0
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141751380(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141751380

uint64_t SynLift_141752ac0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141752ac0

uint64_t SynLift_141752cd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141752cd0

uint64_t SynLift_141752d30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141752d30

uint64_t SynLift_141752ef0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141752ef0

uint64_t SynLift_141752f50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141752f50

uint64_t SynLift_1417530a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417530a0

uint64_t SynLift_141753100(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753100

uint64_t SynLift_141753320(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753320

uint64_t SynLift_141753380(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753380
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141753470(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753470
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141753620(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753620
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417536b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417536b0

uint64_t SynLift_1417538f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417538f0

uint64_t SynLift_141753ab0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753ab0

uint64_t SynLift_141753b10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753b10

uint64_t SynLift_141753bf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753bf0

uint64_t SynLift_141753c50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753c50
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141753d70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753d70
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141754000(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141754000
extern uint64_t (*g_fnLIFT_141752cd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141752d30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753470)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141758050(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141758050
extern uint64_t (*g_fnLIFT_1417512f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141752ef0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141752f50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417591f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417591f0
extern uint64_t (*g_fnLIFT_141750a30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417538f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141754000)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141759600(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141759600
extern uint64_t (*g_fnLIFT_1417530a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753100)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753620)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141759a90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141759a90
extern uint64_t (*g_fnLIFT_141753ab0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753b10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753d70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141759ef0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141759ef0
extern uint64_t (*g_fnLIFT_141751380)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753320)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753380)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14175a300(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175a300
extern uint64_t (*g_fnLIFT_1417536b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753bf0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753c50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14175a710(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175a710
extern uint64_t (*g_fnLIFT_14174fe10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141750760)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141752ac0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417614e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417614e0

uint64_t SynLift_141776070(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141776070

uint64_t SynLift_141776360(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141776360
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141776460(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141776460
extern uint64_t (*g_fnLIFT_141776070)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141776360)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141776460)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141776c90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141776c90

uint64_t SynLift_14177a460(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177a460
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14177a5c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177a5c0

uint64_t SynLift_14177a860(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177a860
extern uint64_t (*g_fnLIFT_14177a460)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177a5c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177a860)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14177b800(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177b800
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141789d70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141789d70

uint64_t SynLift_141789ea0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141789ea0

uint64_t SynLift_141789f00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141789f00
extern uint64_t (*g_fnLIFT_141789d70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141789ea0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141789f00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14178ab70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178ab70

uint64_t SynLift_141790ce0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141790ce0
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141790e10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141790e10

uint64_t SynLift_141792160(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141792160

uint64_t SynLift_1417921c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417921c0
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141792240(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141792240

uint64_t SynLift_1417923e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417923e0
extern uint64_t (*g_fnLIFT_141790ce0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141790e10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417923e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417948b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417948b0
extern uint64_t (*g_fnLIFT_141792160)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417921c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141792240)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141795230(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141795230

uint64_t SynLift_1417a6f90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a6f90
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417a70b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a70b0

uint64_t SynLift_1417a7320(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a7320
extern uint64_t (*g_fnLIFT_1417a6f90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a70b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a7320)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417a8160(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a8160
}  // namespace tq
