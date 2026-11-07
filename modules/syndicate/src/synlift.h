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
extern uint64_t (*g_fnLIFT_1417cbb60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417cd520(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cd520
extern uint64_t (*g_fnLIFT_141726210)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141726210(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141726210
extern uint64_t (*g_fnLIFT_1417262c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417262c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417262c0
extern uint64_t (*g_fnLIFT_141726310)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141726310(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141726310
extern uint64_t (*g_fnLIFT_141726360)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141726360(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141726360
extern uint64_t (*g_fnLIFT_1417270a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417270a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417270a0
extern uint64_t (*g_fnLIFT_14173bc60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14173bc60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173bc60
extern uint64_t (*g_fnLIFT_141746600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141746600(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141746600
extern uint64_t (*g_fnLIFT_141746650)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141746650(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141746650
extern uint64_t (*g_fnLIFT_1417540c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417540c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417540c0
extern uint64_t (*g_fnLIFT_141755490)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141755490(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141755490
extern uint64_t (*g_fnLIFT_1417555f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417555f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417555f0
extern uint64_t (*g_fnLIFT_141755640)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141755640(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141755640
extern uint64_t (*g_fnLIFT_141755690)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141755690(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141755690
extern uint64_t (*g_fnLIFT_1417556e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417556e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417556e0
extern uint64_t (*g_fnLIFT_141755730)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141755730(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141755730
extern uint64_t (*g_fnLIFT_141756920)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141756920(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141756920
extern uint64_t (*g_fnLIFT_1417767b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417767b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417767b0
extern uint64_t (*g_fnLIFT_14177aa60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14177aa60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177aa60
extern uint64_t (*g_fnLIFT_14178a650)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14178a650(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178a650
extern uint64_t (*g_fnLIFT_141793220)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141793220(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793220
extern uint64_t (*g_fnLIFT_141793630)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141793630(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793630
extern uint64_t (*g_fnLIFT_1417a75b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417a75b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a75b0
extern uint64_t (*g_fnLIFT_141726210)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141727640(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141727640
extern uint64_t (*g_fnLIFT_1417262c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417276c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417276c0
extern uint64_t (*g_fnLIFT_141726310)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141727740(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141727740
extern uint64_t (*g_fnLIFT_141726360)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417277c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417277c0
extern uint64_t (*g_fnLIFT_1417270a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141728b10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141728b10
extern uint64_t (*g_fnLIFT_14173bc60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14173c470(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173c470
extern uint64_t (*g_fnLIFT_141746600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417471f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417471f0
extern uint64_t (*g_fnLIFT_141746650)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141747270(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141747270
extern uint64_t (*g_fnLIFT_1417540c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417567f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417567f0
extern uint64_t (*g_fnLIFT_141755490)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141757580(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141757580
extern uint64_t (*g_fnLIFT_1417555f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141757640(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141757640
extern uint64_t (*g_fnLIFT_141755640)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417576c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417576c0
extern uint64_t (*g_fnLIFT_141755690)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141757740(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141757740
extern uint64_t (*g_fnLIFT_1417556e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417577c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417577c0
extern uint64_t (*g_fnLIFT_141755730)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141757840(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141757840
extern uint64_t (*g_fnLIFT_141756920)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417599c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417599c0
extern uint64_t (*g_fnLIFT_1417767b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141777050(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141777050
extern uint64_t (*g_fnLIFT_14177aa60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14177ac60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177ac60
extern uint64_t (*g_fnLIFT_14178a650)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14178af30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178af30
extern uint64_t (*g_fnLIFT_141793220)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141794280(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141794280
extern uint64_t (*g_fnLIFT_141793630)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141794c70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141794c70
extern uint64_t (*g_fnLIFT_1417a75b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417a7780(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a7780
extern uint64_t (*g_fnLIFT_141727640)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141728290)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14172a410(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172a410
extern uint64_t (*g_fnLIFT_1417276c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172b160)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14172d3c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172d3c0
extern uint64_t (*g_fnLIFT_141727740)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172b870)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14172d610(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172d610
extern uint64_t (*g_fnLIFT_1417277c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172bd00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14172d810(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172d810
extern uint64_t (*g_fnLIFT_14173c0b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173c470)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14173cb90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173cb90
extern uint64_t (*g_fnLIFT_1417471f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141747400)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417481d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417481d0
extern uint64_t (*g_fnLIFT_141747270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141749c00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14174a150(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174a150
extern uint64_t (*g_fnLIFT_141757580)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141758050)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14175bda0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175bda0
extern uint64_t (*g_fnLIFT_141757640)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417591f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14175d690(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175d690
extern uint64_t (*g_fnLIFT_141759600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417599c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14175d9f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175d9f0
extern uint64_t (*g_fnLIFT_1417576c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141759a90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14175dba0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175dba0
extern uint64_t (*g_fnLIFT_141757740)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141759ef0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14175df00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175df00
extern uint64_t (*g_fnLIFT_1417577c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175a300)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14175e0b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175e0b0
extern uint64_t (*g_fnLIFT_141757840)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175a710)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14175e410(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175e410
extern uint64_t (*g_fnLIFT_1417567f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417614e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141762db0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141762db0
extern uint64_t (*g_fnLIFT_141776c90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141777050)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141777350(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141777350
extern uint64_t (*g_fnLIFT_14177ac60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177b800)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14177bcb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177bcb0
extern uint64_t (*g_fnLIFT_14178ab70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178af30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_14178b8b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178b8b0
extern uint64_t (*g_fnLIFT_1417948b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141794c70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141796b10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141796b10
extern uint64_t (*g_fnLIFT_141794280)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141795230)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_141797280(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141797280
extern uint64_t (*g_fnLIFT_1417a7780)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a8160)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

uint64_t SynLift_1417a8610(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a8610
}  // namespace tq
