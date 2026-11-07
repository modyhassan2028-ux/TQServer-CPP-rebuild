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


uint64_t SynLift_14172a7c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172a7c0

uint64_t SynLift_141740e80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141740e80

uint64_t SynLift_141763e04(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141763e04

uint64_t SynLift_141763feb(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141763feb

uint64_t SynLift_141788c20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141788c20

uint64_t SynLift_14179db30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179db30

uint64_t SynLift_1417a4180(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a4180

uint64_t SynLift_1417ac510(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ac510

uint64_t SynLift_1417b07c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b07c0

uint64_t SynLift_1417cb580(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cb580

uint64_t SynLift_141821720(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141821720

uint64_t SynLift_141821741(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141821741
// seams: an indirect call the bodies make out of the image (import thunks and other bodies)
extern uint64_t (*g_fnLIFT_1417224f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141722680)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417227e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141722ef0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141722fc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141723090)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141723a50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141724870)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141724950)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417249e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141724c50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141724cb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141724ed0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141725000)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141725060)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141726210)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417262c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141726310)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141726360)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417270a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141727640)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417276c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141727740)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417277c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141728290)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141728750)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141728b10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417293c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141729790)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141729ba0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172b160)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172b870)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172bd00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173b0e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173b140)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173b240)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173bc60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173c0b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173c470)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173c5c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173e790)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141744560)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417447d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141744cb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141745ad0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141745c30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141745c90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141746600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141746650)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417471f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141747270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141747400)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417483e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141748820)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141749c00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174fe10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141750760)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141750a30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417512f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141751380)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141752ac0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141752cd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141752d30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141752ef0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141752f50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417530a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753100)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753320)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753380)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753470)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753620)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417536b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417538f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753ab0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753b10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753bf0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753c50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753d70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141754000)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417540c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141755490)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417555f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141755640)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141755690)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417556e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141755730)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417567f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141756920)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141757580)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141757640)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417576c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141757740)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417577c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141757840)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141758050)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417585d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141758a10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417591f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141759600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417599c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141759a90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141759ef0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175a300)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175a710)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175bfb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175c600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175ca70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175d350)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417614e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141770600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141771050)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141776070)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141776360)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141776460)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417767b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141776c90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141777050)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177a460)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177a5c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177a860)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177aa60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177ac60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177af70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177b800)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141789d70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141789ea0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141789f00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178a650)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178ab70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178af30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178ba80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141790ce0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141790e10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141792160)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417921c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141792240)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417923e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141793220)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141793630)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141794280)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417948b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141794c70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141794e10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141795230)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141796d90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a6f90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a70b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a7320)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a75b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a7780)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a79e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a8160)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c9310)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cbb60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

}  // namespace tq
