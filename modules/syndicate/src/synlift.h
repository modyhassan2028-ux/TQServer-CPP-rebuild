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


uint64_t SynLift_141721000(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141721000

uint64_t SynLift_141721110(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141721110

uint64_t SynLift_141721170(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141721170

uint64_t SynLift_141721230(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141721230

uint64_t SynLift_141721290(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141721290

uint64_t SynLift_1417213e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417213e0

uint64_t SynLift_141721420(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141721420

uint64_t SynLift_1417214c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417214c0

uint64_t SynLift_1417214f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417214f0

uint64_t SynLift_141721530(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141721530

uint64_t SynLift_1417215a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417215a0

uint64_t SynLift_1417215d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417215d0

uint64_t SynLift_141721720(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141721720

uint64_t SynLift_141721780(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141721780

uint64_t SynLift_141721cf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141721cf0

uint64_t SynLift_141721ec0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141721ec0

uint64_t SynLift_1417224f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417224f0

uint64_t SynLift_141722680(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141722680

uint64_t SynLift_1417227e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417227e0

uint64_t SynLift_141722c70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141722c70

uint64_t SynLift_141722ce0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141722ce0

uint64_t SynLift_141722d30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141722d30

uint64_t SynLift_141722ef0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141722ef0

uint64_t SynLift_141722fc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141722fc0

uint64_t SynLift_141723090(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141723090

uint64_t SynLift_141723180(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141723180

uint64_t SynLift_141723200(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141723200

uint64_t SynLift_141723280(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141723280

uint64_t SynLift_141723600(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141723600

uint64_t SynLift_141723750(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141723750

uint64_t SynLift_1417238d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417238d0

uint64_t SynLift_141723940(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141723940

uint64_t SynLift_141723a50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141723a50

uint64_t SynLift_1417241a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417241a0

uint64_t SynLift_141724870(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141724870

uint64_t SynLift_141724950(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141724950

uint64_t SynLift_1417249e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417249e0

uint64_t SynLift_141724c50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141724c50

uint64_t SynLift_141724cb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141724cb0

uint64_t SynLift_141724ed0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141724ed0

uint64_t SynLift_141725000(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141725000

uint64_t SynLift_141725060(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141725060

uint64_t SynLift_141725e80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141725e80

uint64_t SynLift_141726210(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141726210

uint64_t SynLift_141726260(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141726260

uint64_t SynLift_1417262c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417262c0

uint64_t SynLift_141726310(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141726310

uint64_t SynLift_141726360(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141726360

uint64_t SynLift_141726430(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141726430

uint64_t SynLift_141726620(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141726620

uint64_t SynLift_141726800(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141726800

uint64_t SynLift_1417268e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417268e0

uint64_t SynLift_141726a90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141726a90

uint64_t SynLift_141726fa0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141726fa0

uint64_t SynLift_141726ff0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141726ff0

uint64_t SynLift_1417270a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417270a0

uint64_t SynLift_141727310(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141727310

uint64_t SynLift_141727490(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141727490

uint64_t SynLift_141727500(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141727500

uint64_t SynLift_141727620(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141727620

uint64_t SynLift_141727640(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141727640

uint64_t SynLift_1417276c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417276c0

uint64_t SynLift_141727740(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141727740

uint64_t SynLift_1417277c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417277c0

uint64_t SynLift_141727880(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141727880

uint64_t SynLift_1417278c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417278c0

uint64_t SynLift_1417279d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417279d0

uint64_t SynLift_141728290(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141728290

uint64_t SynLift_141728650(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141728650

uint64_t SynLift_141728750(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141728750

uint64_t SynLift_141728b10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141728b10

uint64_t SynLift_141728d70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141728d70

uint64_t SynLift_141728d90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141728d90

uint64_t SynLift_141728dc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141728dc0

uint64_t SynLift_141728e10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141728e10

uint64_t SynLift_141728f00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141728f00

uint64_t SynLift_141728f40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141728f40

uint64_t SynLift_141728fa0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141728fa0

uint64_t SynLift_141729000(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141729000

uint64_t SynLift_141729040(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141729040

uint64_t SynLift_141729090(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141729090

uint64_t SynLift_141729200(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141729200

uint64_t SynLift_141729260(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141729260

uint64_t SynLift_1417292b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417292b0

uint64_t SynLift_141729f70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141729f70

uint64_t SynLift_14172a3b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172a3b0

uint64_t SynLift_14172a410(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172a410

uint64_t SynLift_14172a63d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172a63d

uint64_t SynLift_14172a65f(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172a65f

uint64_t SynLift_14172a770(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172a770

uint64_t SynLift_14172a7c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172a7c0

uint64_t SynLift_14172a970(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172a970

uint64_t SynLift_14172acb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172acb0

uint64_t SynLift_14172acf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172acf0

uint64_t SynLift_14172ad60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172ad60

uint64_t SynLift_14172ade0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172ade0

uint64_t SynLift_14172ae00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172ae00

uint64_t SynLift_14172ae7c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172ae7c

uint64_t SynLift_14172ae9e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172ae9e

uint64_t SynLift_14172afb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172afb0

uint64_t SynLift_14172b02c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172b02c

uint64_t SynLift_14172b04e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172b04e

uint64_t SynLift_14172b160(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172b160

uint64_t SynLift_14172b6c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172b6c0

uint64_t SynLift_14172b73c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172b73c

uint64_t SynLift_14172b75e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172b75e

uint64_t SynLift_14172b870(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172b870

uint64_t SynLift_14172bd00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172bd00

uint64_t SynLift_14172c20d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172c20d

uint64_t SynLift_14172c22f(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172c22f

uint64_t SynLift_14172c410(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172c410

uint64_t SynLift_14172c600(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172c600

uint64_t SynLift_14172c63a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172c63a

uint64_t SynLift_14172c7ee(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172c7ee

uint64_t SynLift_14172c8a5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172c8a5

uint64_t SynLift_14172c90c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172c90c

uint64_t SynLift_14172c920(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172c920

uint64_t SynLift_14172c95a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172c95a

uint64_t SynLift_14172cb0e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172cb0e

uint64_t SynLift_14172cbc5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172cbc5

uint64_t SynLift_14172cc2c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172cc2c

uint64_t SynLift_14172cc40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172cc40

uint64_t SynLift_14172cc7a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172cc7a

uint64_t SynLift_14172ce31(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172ce31

uint64_t SynLift_14172cee5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172cee5

uint64_t SynLift_14172cf4e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172cf4e

uint64_t SynLift_14172d120(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172d120

uint64_t SynLift_14172d3c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172d3c0

uint64_t SynLift_14172d610(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172d610

uint64_t SynLift_14172d810(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172d810

uint64_t SynLift_14172da60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172da60

uint64_t SynLift_14172db90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172db90

uint64_t SynLift_14172de40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172de40

uint64_t SynLift_14172de80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172de80

uint64_t SynLift_14172ded0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172ded0

uint64_t SynLift_14172e00c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172e00c

uint64_t SynLift_14172e072(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172e072

uint64_t SynLift_14172e15a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172e15a

uint64_t SynLift_14172e25c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172e25c

uint64_t SynLift_14172e335(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172e335

uint64_t SynLift_14172e41a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172e41a

uint64_t SynLift_14172e4f2(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172e4f2

uint64_t SynLift_14172e5cc(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172e5cc

uint64_t SynLift_14172e5ec(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172e5ec

uint64_t SynLift_14172e6a5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172e6a5

uint64_t SynLift_14172e760(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172e760

uint64_t SynLift_14172e78a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172e78a

uint64_t SynLift_14172e7aa(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172e7aa

uint64_t SynLift_14172e862(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172e862

uint64_t SynLift_14172e910(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172e910

uint64_t SynLift_14172e959(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172e959

uint64_t SynLift_14172e97c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172e97c

uint64_t SynLift_14172ea30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172ea30

uint64_t SynLift_14172eae0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172eae0

uint64_t SynLift_14172eb29(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172eb29

uint64_t SynLift_14172eb4c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172eb4c

uint64_t SynLift_14172ec00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172ec00

uint64_t SynLift_14172ecb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172ecb0

uint64_t SynLift_14172ecf9(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172ecf9

uint64_t SynLift_14172eed6(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172eed6

uint64_t SynLift_14172f040(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172f040

uint64_t SynLift_14172f08f(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172f08f

uint64_t SynLift_14172f271(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172f271

uint64_t SynLift_14172f310(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172f310

uint64_t SynLift_14172f33f(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172f33f

uint64_t SynLift_14172f38a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172f38a

uint64_t SynLift_14172f3ef(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172f3ef

uint64_t SynLift_14172f420(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172f420

uint64_t SynLift_14172f433(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172f433

uint64_t SynLift_14172f467(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172f467

uint64_t SynLift_14172f490(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172f490

uint64_t SynLift_14172f500(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172f500

uint64_t SynLift_14172f542(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172f542

uint64_t SynLift_14172f5a3(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172f5a3

uint64_t SynLift_14172f760(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172f760

uint64_t SynLift_14172f970(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14172f970

uint64_t SynLift_141730240(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141730240

uint64_t SynLift_141730450(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141730450

uint64_t SynLift_141730750(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141730750

uint64_t SynLift_141730850(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141730850

uint64_t SynLift_141730b10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141730b10

uint64_t SynLift_141730bc5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141730bc5

uint64_t SynLift_141730c03(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141730c03

uint64_t SynLift_141730cd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141730cd0

uint64_t SynLift_1417311d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417311d0

uint64_t SynLift_141731300(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141731300

uint64_t SynLift_1417317b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417317b0

uint64_t SynLift_141731ba0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141731ba0

uint64_t SynLift_141731c30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141731c30

uint64_t SynLift_141731c77(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141731c77

uint64_t SynLift_141731cc7(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141731cc7

uint64_t SynLift_141731d25(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141731d25

uint64_t SynLift_141731ec0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141731ec0

uint64_t SynLift_141731f50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141731f50

uint64_t SynLift_141731f90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141731f90

uint64_t SynLift_141732040(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141732040

uint64_t SynLift_1417322b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417322b0

uint64_t SynLift_1417324c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417324c0

uint64_t SynLift_141733480(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141733480

uint64_t SynLift_1417335f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417335f0

uint64_t SynLift_141733820(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141733820

uint64_t SynLift_141734580(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141734580

uint64_t SynLift_141734c90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141734c90

uint64_t SynLift_141734fcd(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141734fcd

uint64_t SynLift_141734fef(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141734fef

uint64_t SynLift_141735100(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141735100

uint64_t SynLift_141735350(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141735350

uint64_t SynLift_14173538a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173538a

uint64_t SynLift_141735541(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141735541

uint64_t SynLift_1417355f5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417355f5

uint64_t SynLift_14173565e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173565e

uint64_t SynLift_141735680(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141735680

uint64_t SynLift_1417356b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417356b0

uint64_t SynLift_1417357d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417357d0

uint64_t SynLift_141735a60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141735a60

uint64_t SynLift_141735bb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141735bb0

uint64_t SynLift_141735c80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141735c80

uint64_t SynLift_1417360a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417360a0

uint64_t SynLift_141736400(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141736400

uint64_t SynLift_1417369c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417369c0

uint64_t SynLift_141737c00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141737c00

uint64_t SynLift_141738bc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141738bc0

uint64_t SynLift_141738ed0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141738ed0

uint64_t SynLift_141739200(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141739200

uint64_t SynLift_1417394f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417394f0

uint64_t SynLift_14173a450(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173a450

uint64_t SynLift_14173abf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173abf0

uint64_t SynLift_14173b0e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173b0e0

uint64_t SynLift_14173b140(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173b140

uint64_t SynLift_14173b240(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173b240

uint64_t SynLift_14173bc60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173bc60

uint64_t SynLift_14173bd10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173bd10

uint64_t SynLift_14173bf40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173bf40

uint64_t SynLift_14173c0b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173c0b0

uint64_t SynLift_14173c470(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173c470

uint64_t SynLift_14173c4f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173c4f0

uint64_t SynLift_14173c9a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173c9a0

uint64_t SynLift_14173cb50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173cb50

uint64_t SynLift_14173cb90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173cb90

uint64_t SynLift_14173cd80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173cd80

uint64_t SynLift_14173cea0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173cea0

uint64_t SynLift_14173cf1c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173cf1c

uint64_t SynLift_14173cf3e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173cf3e

uint64_t SynLift_14173d0f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173d0f0

uint64_t SynLift_14173d2b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173d2b0

uint64_t SynLift_14173d440(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173d440

uint64_t SynLift_14173d47a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173d47a

uint64_t SynLift_14173d62e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173d62e

uint64_t SynLift_14173d6e5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173d6e5

uint64_t SynLift_14173d74c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173d74c

uint64_t SynLift_14173d898(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173d898

uint64_t SynLift_14173d8e9(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173d8e9

uint64_t SynLift_14173d975(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173d975

uint64_t SynLift_14173d9a8(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173d9a8

uint64_t SynLift_14173d9c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173d9c0

uint64_t SynLift_14173db90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173db90

uint64_t SynLift_14173dbc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173dbc0

uint64_t SynLift_14173dd10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173dd10

uint64_t SynLift_14173de50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173de50

uint64_t SynLift_14173dee0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173dee0

uint64_t SynLift_14173dfa0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173dfa0

uint64_t SynLift_14173dfd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173dfd0

uint64_t SynLift_14173e010(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173e010

uint64_t SynLift_14173e080(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173e080

uint64_t SynLift_14173e0c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173e0c0

uint64_t SynLift_14173e120(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173e120

uint64_t SynLift_14173e160(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173e160

uint64_t SynLift_14173e1a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173e1a0

uint64_t SynLift_14173e240(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173e240

uint64_t SynLift_14173e350(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173e350

uint64_t SynLift_14173ead0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173ead0

uint64_t SynLift_14173eb10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173eb10

uint64_t SynLift_14173ed60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173ed60

uint64_t SynLift_14173eddc(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173eddc

uint64_t SynLift_14173edfe(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173edfe

uint64_t SynLift_14173ef80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173ef80

uint64_t SynLift_14173f0c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173f0c0

uint64_t SynLift_14173f0fa(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173f0fa

uint64_t SynLift_14173f2ae(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173f2ae

uint64_t SynLift_14173f365(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173f365

uint64_t SynLift_14173f3cc(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173f3cc

uint64_t SynLift_14173f3e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173f3e0

uint64_t SynLift_14173f410(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173f410

uint64_t SynLift_14173f450(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173f450

uint64_t SynLift_14173f490(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173f490

uint64_t SynLift_14173f4b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173f4b0

uint64_t SynLift_14173f4d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173f4d0

uint64_t SynLift_14173f680(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173f680

uint64_t SynLift_14173f8e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173f8e0

uint64_t SynLift_14173fa40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173fa40

uint64_t SynLift_14173fcc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173fcc0

uint64_t SynLift_14173fd70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173fd70

uint64_t SynLift_14173fe40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14173fe40

uint64_t SynLift_1417405f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417405f0

uint64_t SynLift_1417406b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417406b0

uint64_t SynLift_1417406f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417406f0

uint64_t SynLift_1417408a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417408a0

uint64_t SynLift_141740970(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141740970

uint64_t SynLift_1417409d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417409d0

uint64_t SynLift_141740a00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141740a00

uint64_t SynLift_141740aa0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141740aa0

uint64_t SynLift_141740af0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141740af0

uint64_t SynLift_141740bc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141740bc0

uint64_t SynLift_141740c20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141740c20

uint64_t SynLift_141740c60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141740c60

uint64_t SynLift_141740cb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141740cb0

uint64_t SynLift_141740cf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141740cf0

uint64_t SynLift_141740de0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141740de0

uint64_t SynLift_141740e10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141740e10

uint64_t SynLift_141740e80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141740e80

uint64_t SynLift_141740ea3(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141740ea3

uint64_t SynLift_141740ee1(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141740ee1

uint64_t SynLift_141740f00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141740f00

uint64_t SynLift_141740f50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141740f50

uint64_t SynLift_141740fd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141740fd0

uint64_t SynLift_1417410f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417410f0

uint64_t SynLift_141741410(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141741410

uint64_t SynLift_1417414a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417414a0

uint64_t SynLift_141741530(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141741530

uint64_t SynLift_1417415a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417415a0

uint64_t SynLift_141741600(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141741600

uint64_t SynLift_141741690(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141741690

uint64_t SynLift_141741730(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141741730

uint64_t SynLift_141741af0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141741af0

uint64_t SynLift_141741d50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141741d50

uint64_t SynLift_141742110(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141742110

uint64_t SynLift_141742170(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141742170

uint64_t SynLift_1417421fd(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417421fd

uint64_t SynLift_141742262(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141742262

uint64_t SynLift_1417425ea(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417425ea

uint64_t SynLift_141742610(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141742610

uint64_t SynLift_141742810(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141742810

uint64_t SynLift_141742aa0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141742aa0

uint64_t SynLift_141742cd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141742cd0

uint64_t SynLift_141742d20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141742d20

uint64_t SynLift_141742e50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141742e50

uint64_t SynLift_141742fc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141742fc0

uint64_t SynLift_1417431c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417431c0

uint64_t SynLift_141743330(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141743330

uint64_t SynLift_141743450(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141743450

uint64_t SynLift_1417434f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417434f0

uint64_t SynLift_141743b60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141743b60

uint64_t SynLift_141743d10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141743d10

uint64_t SynLift_141743d70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141743d70

uint64_t SynLift_141743dd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141743dd0

uint64_t SynLift_141743e00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141743e00

uint64_t SynLift_141743e30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141743e30

uint64_t SynLift_141743e80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141743e80

uint64_t SynLift_141743f90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141743f90

uint64_t SynLift_141744030(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141744030

uint64_t SynLift_1417441f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417441f0

uint64_t SynLift_141744210(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141744210

uint64_t SynLift_141744560(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141744560

uint64_t SynLift_1417447d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417447d0

uint64_t SynLift_1417448c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417448c0

uint64_t SynLift_141744cb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141744cb0

uint64_t SynLift_141744dd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141744dd0

uint64_t SynLift_1417450c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417450c0

uint64_t SynLift_141745520(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141745520

uint64_t SynLift_141745760(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141745760

uint64_t SynLift_141745920(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141745920

uint64_t SynLift_141745ad0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141745ad0

uint64_t SynLift_141745c30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141745c30

uint64_t SynLift_141745c90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141745c90

uint64_t SynLift_141746310(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141746310

uint64_t SynLift_1417463a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417463a0

uint64_t SynLift_141746480(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141746480

uint64_t SynLift_1417464f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417464f0

uint64_t SynLift_141746600(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141746600

uint64_t SynLift_141746650(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141746650

uint64_t SynLift_1417466e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417466e0

uint64_t SynLift_141746790(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141746790

uint64_t SynLift_141746960(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141746960

uint64_t SynLift_141746d50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141746d50

uint64_t SynLift_141746e20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141746e20

uint64_t SynLift_141746e90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141746e90

uint64_t SynLift_141746f30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141746f30

uint64_t SynLift_141746f5a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141746f5a

uint64_t SynLift_141747010(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141747010

uint64_t SynLift_141747090(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141747090

uint64_t SynLift_1417470a5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417470a5

uint64_t SynLift_1417470bd(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417470bd

uint64_t SynLift_1417471a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417471a0

uint64_t SynLift_1417471c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417471c0

uint64_t SynLift_1417471f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417471f0

uint64_t SynLift_141747270(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141747270

uint64_t SynLift_141747400(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141747400

uint64_t SynLift_1417477c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417477c0

uint64_t SynLift_141747ac0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141747ac0

uint64_t SynLift_141747bb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141747bb0

uint64_t SynLift_141747bd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141747bd0

uint64_t SynLift_141747ec0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141747ec0

uint64_t SynLift_141747ee5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141747ee5

uint64_t SynLift_141747f60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141747f60

uint64_t SynLift_141747f80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141747f80

uint64_t SynLift_141748060(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141748060

uint64_t SynLift_1417480c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417480c0

uint64_t SynLift_1417481d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417481d0

uint64_t SynLift_1417483c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417483c0

uint64_t SynLift_141748b60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141748b60

uint64_t SynLift_141748c00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141748c00

uint64_t SynLift_141748c50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141748c50

uint64_t SynLift_141748ca0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141748ca0

uint64_t SynLift_141748e10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141748e10

uint64_t SynLift_141748e30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141748e30

uint64_t SynLift_141748ea0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141748ea0

uint64_t SynLift_141749040(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141749040

uint64_t SynLift_141749240(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141749240

uint64_t SynLift_141749350(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141749350

uint64_t SynLift_141749410(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141749410

uint64_t SynLift_141749540(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141749540

uint64_t SynLift_1417495d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417495d0

uint64_t SynLift_141749690(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141749690

uint64_t SynLift_14174970c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174970c

uint64_t SynLift_14174972e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174972e

uint64_t SynLift_141749840(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141749840

uint64_t SynLift_141749a50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141749a50

uint64_t SynLift_141749acc(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141749acc

uint64_t SynLift_141749aee(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141749aee

uint64_t SynLift_141749c00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141749c00

uint64_t SynLift_14174a150(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174a150

uint64_t SynLift_14174a350(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174a350

uint64_t SynLift_14174a600(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174a600

uint64_t SynLift_14174a650(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174a650

uint64_t SynLift_14174a6d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174a6d0

uint64_t SynLift_14174ad50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174ad50

uint64_t SynLift_14174b000(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174b000

uint64_t SynLift_14174b0f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174b0f0

uint64_t SynLift_14174b210(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174b210

uint64_t SynLift_14174b4c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174b4c0

uint64_t SynLift_14174b610(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174b610

uint64_t SynLift_14174b622(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174b622

uint64_t SynLift_14174b63e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174b63e

uint64_t SynLift_14174b678(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174b678

uint64_t SynLift_14174b6c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174b6c0

uint64_t SynLift_14174b960(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174b960

uint64_t SynLift_14174be40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174be40

uint64_t SynLift_14174bf70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174bf70

uint64_t SynLift_14174c0c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174c0c0

uint64_t SynLift_14174c5a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174c5a0

uint64_t SynLift_14174cb10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174cb10

uint64_t SynLift_14174cc40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174cc40

uint64_t SynLift_14174cd20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174cd20

uint64_t SynLift_14174cf30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174cf30

uint64_t SynLift_14174cf90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174cf90

uint64_t SynLift_14174cfc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174cfc0

uint64_t SynLift_14174d080(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174d080

uint64_t SynLift_14174d170(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174d170

uint64_t SynLift_14174d3e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174d3e0

uint64_t SynLift_14174d490(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174d490

uint64_t SynLift_14174d5a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174d5a0

uint64_t SynLift_14174d830(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174d830

uint64_t SynLift_14174d900(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174d900

uint64_t SynLift_14174da00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174da00

uint64_t SynLift_14174dcd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174dcd0

uint64_t SynLift_14174e010(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174e010

uint64_t SynLift_14174e050(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174e050

uint64_t SynLift_14174e080(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174e080

uint64_t SynLift_14174e180(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174e180

uint64_t SynLift_14174e1a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174e1a0

uint64_t SynLift_14174e1e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174e1e0

uint64_t SynLift_14174e256(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174e256

uint64_t SynLift_14174e295(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174e295

uint64_t SynLift_14174e2d6(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174e2d6

uint64_t SynLift_14174e300(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174e300

uint64_t SynLift_14174e334(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174e334

uint64_t SynLift_14174e373(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174e373

uint64_t SynLift_14174e400(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174e400

uint64_t SynLift_14174e520(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174e520

uint64_t SynLift_14174e760(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174e760

uint64_t SynLift_14174e7f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174e7f0

uint64_t SynLift_14174e9e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174e9e0

uint64_t SynLift_14174eae0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174eae0

uint64_t SynLift_14174ebe0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174ebe0

uint64_t SynLift_14174ec50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174ec50

uint64_t SynLift_14174ed50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174ed50

uint64_t SynLift_14174edc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174edc0

uint64_t SynLift_14174ee40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174ee40

uint64_t SynLift_14174ee90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174ee90

uint64_t SynLift_14174eee0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174eee0

uint64_t SynLift_14174f080(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174f080

uint64_t SynLift_14174f640(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174f640

uint64_t SynLift_14174fe10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14174fe10

uint64_t SynLift_141750010(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141750010

uint64_t SynLift_1417500a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417500a0

uint64_t SynLift_141750490(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141750490

uint64_t SynLift_141750760(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141750760

uint64_t SynLift_141750a30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141750a30

uint64_t SynLift_141750e20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141750e20

uint64_t SynLift_141750ed0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141750ed0

uint64_t SynLift_141751170(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141751170

uint64_t SynLift_1417512f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417512f0

uint64_t SynLift_141751380(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141751380

uint64_t SynLift_141751db0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141751db0

uint64_t SynLift_141752010(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141752010

uint64_t SynLift_1417520a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417520a0

uint64_t SynLift_141752140(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141752140

uint64_t SynLift_141752220(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141752220

uint64_t SynLift_1417522a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417522a0

uint64_t SynLift_1417523c2(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417523c2

uint64_t SynLift_141752406(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141752406

uint64_t SynLift_1417524d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417524d0

uint64_t SynLift_141752ac0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141752ac0

uint64_t SynLift_141752cd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141752cd0

uint64_t SynLift_141752d30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141752d30

uint64_t SynLift_141752ef0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141752ef0

uint64_t SynLift_141752f50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141752f50

uint64_t SynLift_1417530a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417530a0

uint64_t SynLift_141753100(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753100

uint64_t SynLift_141753320(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753320

uint64_t SynLift_141753380(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753380

uint64_t SynLift_141753470(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753470

uint64_t SynLift_141753620(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753620

uint64_t SynLift_1417536b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417536b0

uint64_t SynLift_1417538f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417538f0

uint64_t SynLift_141753ab0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753ab0

uint64_t SynLift_141753b10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753b10

uint64_t SynLift_141753bf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753bf0

uint64_t SynLift_141753c50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753c50

uint64_t SynLift_141753d70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141753d70

uint64_t SynLift_141754000(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141754000

uint64_t SynLift_1417540c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417540c0

uint64_t SynLift_141754a40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141754a40

uint64_t SynLift_141754bc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141754bc0

uint64_t SynLift_141754c50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141754c50

uint64_t SynLift_141754d70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141754d70

uint64_t SynLift_141754f20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141754f20

uint64_t SynLift_141754f50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141754f50

uint64_t SynLift_141754fc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141754fc0

uint64_t SynLift_141755490(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141755490

uint64_t SynLift_1417554e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417554e0

uint64_t SynLift_141755550(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141755550

uint64_t SynLift_1417555f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417555f0

uint64_t SynLift_141755640(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141755640

uint64_t SynLift_141755690(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141755690

uint64_t SynLift_1417556e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417556e0

uint64_t SynLift_141755730(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141755730

uint64_t SynLift_141755860(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141755860

uint64_t SynLift_141755960(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141755960

uint64_t SynLift_1417559f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417559f0

uint64_t SynLift_141755a70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141755a70

uint64_t SynLift_141755b70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141755b70

uint64_t SynLift_141755ff0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141755ff0

uint64_t SynLift_141756320(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141756320

uint64_t SynLift_141756530(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141756530

uint64_t SynLift_141756670(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141756670

uint64_t SynLift_1417567f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417567f0

uint64_t SynLift_141756920(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141756920

uint64_t SynLift_141756cf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141756cf0

uint64_t SynLift_141756d90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141756d90

uint64_t SynLift_141756e10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141756e10

uint64_t SynLift_141756e70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141756e70

uint64_t SynLift_141756f00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141756f00

uint64_t SynLift_141756f2a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141756f2a

uint64_t SynLift_141756fc7(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141756fc7

uint64_t SynLift_141756fe0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141756fe0

uint64_t SynLift_14175708d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175708d

uint64_t SynLift_14175724e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175724e

uint64_t SynLift_1417572fc(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417572fc

uint64_t SynLift_141757320(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141757320

uint64_t SynLift_141757344(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141757344

uint64_t SynLift_14175735e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175735e

uint64_t SynLift_141757442(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141757442

uint64_t SynLift_141757460(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141757460

uint64_t SynLift_141757480(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141757480

uint64_t SynLift_141757580(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141757580

uint64_t SynLift_141757600(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141757600

uint64_t SynLift_141757640(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141757640

uint64_t SynLift_1417576c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417576c0

uint64_t SynLift_141757740(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141757740

uint64_t SynLift_1417577c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417577c0

uint64_t SynLift_141757840(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141757840

uint64_t SynLift_141757f70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141757f70

uint64_t SynLift_141758050(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141758050

uint64_t SynLift_141758410(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141758410

uint64_t SynLift_141759110(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141759110

uint64_t SynLift_1417591f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417591f0

uint64_t SynLift_141759600(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141759600

uint64_t SynLift_1417599c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417599c0

uint64_t SynLift_141759a90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141759a90

uint64_t SynLift_141759ef0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141759ef0

uint64_t SynLift_14175a300(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175a300

uint64_t SynLift_14175a710(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175a710

uint64_t SynLift_14175ae40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175ae40

uint64_t SynLift_14175ae60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175ae60

uint64_t SynLift_14175ae90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175ae90

uint64_t SynLift_14175afd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175afd0

uint64_t SynLift_14175b200(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175b200

uint64_t SynLift_14175b228(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175b228

uint64_t SynLift_14175b6a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175b6a0

uint64_t SynLift_14175b6c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175b6c0

uint64_t SynLift_14175b780(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175b780

uint64_t SynLift_14175b7e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175b7e0

uint64_t SynLift_14175b830(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175b830

uint64_t SynLift_14175b880(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175b880

uint64_t SynLift_14175b8e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175b8e0

uint64_t SynLift_14175b930(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175b930

uint64_t SynLift_14175bcf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175bcf0

uint64_t SynLift_14175bda0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175bda0

uint64_t SynLift_14175bf90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175bf90

uint64_t SynLift_14175c360(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175c360

uint64_t SynLift_14175c3c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175c3c0

uint64_t SynLift_14175c4b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175c4b0

uint64_t SynLift_14175c520(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175c520

uint64_t SynLift_14175d2a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175d2a0

uint64_t SynLift_14175d690(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175d690

uint64_t SynLift_14175d840(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175d840

uint64_t SynLift_14175d8bc(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175d8bc

uint64_t SynLift_14175d8de(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175d8de

uint64_t SynLift_14175d9f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175d9f0

uint64_t SynLift_14175dba0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175dba0

uint64_t SynLift_14175dd50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175dd50

uint64_t SynLift_14175ddcc(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175ddcc

uint64_t SynLift_14175ddee(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175ddee

uint64_t SynLift_14175df00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175df00

uint64_t SynLift_14175e0b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175e0b0

uint64_t SynLift_14175e2dd(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175e2dd

uint64_t SynLift_14175e2ff(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175e2ff

uint64_t SynLift_14175e410(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175e410

uint64_t SynLift_14175e8e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175e8e0

uint64_t SynLift_14175ea00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175ea00

uint64_t SynLift_14175ea40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175ea40

uint64_t SynLift_14175ea60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175ea60

uint64_t SynLift_14175eb70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175eb70

uint64_t SynLift_14175ecb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175ecb0

uint64_t SynLift_14175ee00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175ee00

uint64_t SynLift_14175ef30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175ef30

uint64_t SynLift_14175efe0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175efe0

uint64_t SynLift_14175f290(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175f290

uint64_t SynLift_14175f4a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175f4a0

uint64_t SynLift_14175f730(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175f730

uint64_t SynLift_14175fa60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175fa60

uint64_t SynLift_14175fba0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175fba0

uint64_t SynLift_14175fdb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175fdb0

uint64_t SynLift_14175fdd9(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175fdd9

uint64_t SynLift_14175fed0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14175fed0

uint64_t SynLift_1417601b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417601b0

uint64_t SynLift_14176022c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176022c

uint64_t SynLift_14176024e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176024e

uint64_t SynLift_141760360(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141760360

uint64_t SynLift_141760570(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141760570

uint64_t SynLift_141760600(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141760600

uint64_t SynLift_1417606c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417606c0

uint64_t SynLift_141760700(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141760700

uint64_t SynLift_1417607a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417607a0

uint64_t SynLift_14176081c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176081c

uint64_t SynLift_14176083e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176083e

uint64_t SynLift_141760bc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141760bc0

uint64_t SynLift_141760c3c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141760c3c

uint64_t SynLift_141760c5e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141760c5e

uint64_t SynLift_14176105d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176105d

uint64_t SynLift_14176107f(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176107f

uint64_t SynLift_141761330(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141761330

uint64_t SynLift_1417613ac(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417613ac

uint64_t SynLift_1417613ce(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417613ce

uint64_t SynLift_1417614e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417614e0

uint64_t SynLift_141761ae0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141761ae0

uint64_t SynLift_141761c40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141761c40

uint64_t SynLift_141761c7a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141761c7a

uint64_t SynLift_141761e2e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141761e2e

uint64_t SynLift_141761ee5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141761ee5

uint64_t SynLift_141761f4c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141761f4c

uint64_t SynLift_141762040(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141762040

uint64_t SynLift_14176207a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176207a

uint64_t SynLift_14176222e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176222e

uint64_t SynLift_1417622e5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417622e5

uint64_t SynLift_14176234c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176234c

uint64_t SynLift_141762440(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141762440

uint64_t SynLift_14176247a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176247a

uint64_t SynLift_141762631(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141762631

uint64_t SynLift_1417626e5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417626e5

uint64_t SynLift_14176274e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176274e

uint64_t SynLift_141762880(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141762880

uint64_t SynLift_141762db0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141762db0

uint64_t SynLift_141762f60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141762f60

uint64_t SynLift_141763070(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141763070

uint64_t SynLift_1417632e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417632e0

uint64_t SynLift_141763315(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141763315

uint64_t SynLift_14176334f(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176334f

uint64_t SynLift_14176338b(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176338b

uint64_t SynLift_1417633b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417633b0

uint64_t SynLift_141763680(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141763680

uint64_t SynLift_141763790(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141763790

uint64_t SynLift_1417638e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417638e0

uint64_t SynLift_141763bc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141763bc0

uint64_t SynLift_141763bf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141763bf0

uint64_t SynLift_141763c25(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141763c25

uint64_t SynLift_141763c6b(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141763c6b

uint64_t SynLift_141763c80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141763c80

uint64_t SynLift_141763fa7(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141763fa7

uint64_t SynLift_141763feb(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141763feb

uint64_t SynLift_1417641d7(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417641d7

uint64_t SynLift_14176421b(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176421b

uint64_t SynLift_141764258(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141764258

uint64_t SynLift_1417642b2(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417642b2

uint64_t SynLift_141764524(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141764524

uint64_t SynLift_141764541(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141764541

uint64_t SynLift_1417645c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417645c0

uint64_t SynLift_14176462f(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176462f

uint64_t SynLift_1417646ca(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417646ca

uint64_t SynLift_1417646f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417646f0

uint64_t SynLift_1417647e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417647e0

uint64_t SynLift_141764810(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141764810

uint64_t SynLift_141764990(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141764990

uint64_t SynLift_1417649b3(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417649b3

uint64_t SynLift_141764ad2(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141764ad2

uint64_t SynLift_141764b80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141764b80

uint64_t SynLift_141764bad(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141764bad

uint64_t SynLift_141764c02(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141764c02

uint64_t SynLift_141764cbc(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141764cbc

uint64_t SynLift_141764d01(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141764d01

uint64_t SynLift_141764d6e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141764d6e

uint64_t SynLift_141764edd(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141764edd

uint64_t SynLift_141764ef8(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141764ef8

uint64_t SynLift_141764f10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141764f10

uint64_t SynLift_141764f2f(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141764f2f

uint64_t SynLift_141764f95(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141764f95

uint64_t SynLift_141764ffb(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141764ffb

uint64_t SynLift_141765038(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141765038

uint64_t SynLift_141765060(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141765060

uint64_t SynLift_1417652c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417652c0

uint64_t SynLift_141765410(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141765410

uint64_t SynLift_141765540(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141765540

uint64_t SynLift_1417655c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417655c0

uint64_t SynLift_141765800(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141765800

uint64_t SynLift_141766950(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141766950

uint64_t SynLift_141766a70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141766a70

uint64_t SynLift_141767670(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141767670

uint64_t SynLift_1417676e1(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417676e1

uint64_t SynLift_141767713(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141767713

uint64_t SynLift_1417677ee(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417677ee

uint64_t SynLift_141767820(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141767820

uint64_t SynLift_141767890(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141767890

uint64_t SynLift_1417678fc(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417678fc

uint64_t SynLift_14176792e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176792e

uint64_t SynLift_141767a0e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141767a0e

uint64_t SynLift_141767a40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141767a40

uint64_t SynLift_141767ab0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141767ab0

uint64_t SynLift_141767b1c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141767b1c

uint64_t SynLift_141767b4e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141767b4e

uint64_t SynLift_141767bc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141767bc0

uint64_t SynLift_141767c2c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141767c2c

uint64_t SynLift_141767c5e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141767c5e

uint64_t SynLift_141767d3c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141767d3c

uint64_t SynLift_141767d6e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141767d6e

uint64_t SynLift_141767de0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141767de0

uint64_t SynLift_141767f00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141767f00

uint64_t SynLift_1417681b8(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417681b8

uint64_t SynLift_1417681d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417681d0

uint64_t SynLift_1417682f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417682f0

uint64_t SynLift_141768410(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141768410

uint64_t SynLift_141768421(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141768421

uint64_t SynLift_14176843d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176843d

uint64_t SynLift_141768474(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141768474

uint64_t SynLift_1417684b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417684b0

uint64_t SynLift_1417685f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417685f0

uint64_t SynLift_141768730(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141768730

uint64_t SynLift_141768870(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141768870

uint64_t SynLift_141768a10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141768a10

uint64_t SynLift_141768acf(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141768acf

uint64_t SynLift_141768b20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141768b20

uint64_t SynLift_141768b5d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141768b5d

uint64_t SynLift_141768b98(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141768b98

uint64_t SynLift_141768c70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141768c70

uint64_t SynLift_141768ec0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141768ec0

uint64_t SynLift_141768eed(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141768eed

uint64_t SynLift_1417690e8(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417690e8

uint64_t SynLift_1417695b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417695b0

uint64_t SynLift_141769670(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141769670

uint64_t SynLift_141769750(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141769750

uint64_t SynLift_1417698d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417698d0

uint64_t SynLift_141769bf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141769bf0

uint64_t SynLift_14176a5a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176a5a0

uint64_t SynLift_14176a870(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176a870

uint64_t SynLift_14176a8a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176a8a0

uint64_t SynLift_14176a8d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176a8d0

uint64_t SynLift_14176a900(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176a900

uint64_t SynLift_14176a930(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176a930

uint64_t SynLift_14176a960(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176a960

uint64_t SynLift_14176a990(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176a990

uint64_t SynLift_14176a9c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176a9c0

uint64_t SynLift_14176aae0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176aae0

uint64_t SynLift_14176aca0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176aca0

uint64_t SynLift_14176acf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176acf0

uint64_t SynLift_14176b020(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176b020

uint64_t SynLift_14176dac0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176dac0

uint64_t SynLift_14176dc40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176dc40

uint64_t SynLift_14176dff0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176dff0

uint64_t SynLift_14176e210(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176e210

uint64_t SynLift_14176e320(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176e320

uint64_t SynLift_14176e360(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176e360

uint64_t SynLift_14176e3a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176e3a0

uint64_t SynLift_14176e3e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176e3e0

uint64_t SynLift_14176e500(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176e500

uint64_t SynLift_14176e538(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176e538

uint64_t SynLift_14176e5b3(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176e5b3

uint64_t SynLift_14176e5e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176e5e0

uint64_t SynLift_14176e6f9(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176e6f9

uint64_t SynLift_14176e7d6(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176e7d6

uint64_t SynLift_14176e8f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176e8f0

uint64_t SynLift_14176ecf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176ecf0

uint64_t SynLift_14176ed25(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176ed25

uint64_t SynLift_14176f183(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176f183

uint64_t SynLift_14176f380(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176f380

uint64_t SynLift_14176f5b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176f5b0

uint64_t SynLift_14176f610(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176f610

uint64_t SynLift_14176f650(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176f650

uint64_t SynLift_14176f690(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176f690

uint64_t SynLift_14176f700(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176f700

uint64_t SynLift_14176f770(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176f770

uint64_t SynLift_14176f7b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176f7b0

uint64_t SynLift_14176f7f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176f7f0

uint64_t SynLift_14176f990(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176f990

uint64_t SynLift_14176fa90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176fa90

uint64_t SynLift_14176fbf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176fbf0

uint64_t SynLift_14176fc31(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176fc31

uint64_t SynLift_14176fd39(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176fd39

uint64_t SynLift_14176ff50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14176ff50

uint64_t SynLift_141770300(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141770300

uint64_t SynLift_1417703a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417703a0

uint64_t SynLift_141770400(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141770400

uint64_t SynLift_141770470(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141770470

uint64_t SynLift_1417704b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417704b0

uint64_t SynLift_141770520(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141770520

uint64_t SynLift_141770940(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141770940

uint64_t SynLift_1417709e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417709e0

uint64_t SynLift_141770a20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141770a20

uint64_t SynLift_141770e60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141770e60

uint64_t SynLift_141770ea0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141770ea0

uint64_t SynLift_141770f1c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141770f1c

uint64_t SynLift_141770f3e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141770f3e

uint64_t SynLift_141771390(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141771390

uint64_t SynLift_1417713d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417713d0

uint64_t SynLift_1417714e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417714e0

uint64_t SynLift_141773cb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141773cb0

uint64_t SynLift_141773d2c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141773d2c

uint64_t SynLift_141773d4e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141773d4e

uint64_t SynLift_141773e60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141773e60

uint64_t SynLift_1417742a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417742a0

uint64_t SynLift_1417742e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417742e0

uint64_t SynLift_1417744c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417744c0

uint64_t SynLift_141774500(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141774500

uint64_t SynLift_141774bac(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141774bac

uint64_t SynLift_141774bf4(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141774bf4

uint64_t SynLift_141774c20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141774c20

uint64_t SynLift_141775350(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141775350

uint64_t SynLift_141775470(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141775470

uint64_t SynLift_1417756f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417756f0

uint64_t SynLift_1417757d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417757d0

uint64_t SynLift_141775800(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141775800

uint64_t SynLift_141776070(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141776070

uint64_t SynLift_141776360(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141776360

uint64_t SynLift_141776460(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141776460

uint64_t SynLift_1417766d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417766d0

uint64_t SynLift_1417767b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417767b0

uint64_t SynLift_141776c90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141776c90

uint64_t SynLift_141777050(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141777050

uint64_t SynLift_1417771a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417771a0

uint64_t SynLift_14177721c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177721c

uint64_t SynLift_14177723e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177723e

uint64_t SynLift_141777350(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141777350

uint64_t SynLift_141777550(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141777550

uint64_t SynLift_141777640(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141777640

uint64_t SynLift_14177767a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177767a

uint64_t SynLift_141777831(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141777831

uint64_t SynLift_1417778e5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417778e5

uint64_t SynLift_14177794e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177794e

uint64_t SynLift_141777a5d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141777a5d

uint64_t SynLift_141777b0d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141777b0d

uint64_t SynLift_141777b40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141777b40

uint64_t SynLift_141777b60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141777b60

uint64_t SynLift_141777d60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141777d60

uint64_t SynLift_141777d90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141777d90

uint64_t SynLift_141777ee0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141777ee0

uint64_t SynLift_141777fa0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141777fa0

uint64_t SynLift_1417780a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417780a0

uint64_t SynLift_1417782c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417782c0

uint64_t SynLift_141778330(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141778330

uint64_t SynLift_1417783a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417783a0

uint64_t SynLift_1417783e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417783e0

uint64_t SynLift_1417784c2(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417784c2

uint64_t SynLift_141778506(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141778506

uint64_t SynLift_1417786d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417786d0

uint64_t SynLift_141778760(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141778760

uint64_t SynLift_141778880(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141778880

uint64_t SynLift_1417788c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417788c0

uint64_t SynLift_1417788ea(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417788ea

uint64_t SynLift_141778987(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141778987

uint64_t SynLift_1417789a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417789a0

uint64_t SynLift_141778a20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141778a20

uint64_t SynLift_141778a32(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141778a32

uint64_t SynLift_141778a4d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141778a4d

uint64_t SynLift_141778b30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141778b30

uint64_t SynLift_141778b60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141778b60

uint64_t SynLift_141778d90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141778d90

uint64_t SynLift_141778db8(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141778db8

uint64_t SynLift_141778e20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141778e20

uint64_t SynLift_141778e60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141778e60

uint64_t SynLift_141778e7a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141778e7a

uint64_t SynLift_141778f5d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141778f5d

uint64_t SynLift_141778f80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141778f80

uint64_t SynLift_141779090(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141779090

uint64_t SynLift_141779400(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141779400

uint64_t SynLift_1417794c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417794c0

uint64_t SynLift_141779790(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141779790

uint64_t SynLift_141779900(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141779900

uint64_t SynLift_141779960(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141779960

uint64_t SynLift_141779b60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141779b60

uint64_t SynLift_141779b83(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141779b83

uint64_t SynLift_141779bed(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141779bed

uint64_t SynLift_141779cca(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141779cca

uint64_t SynLift_141779cf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141779cf0

uint64_t SynLift_141779d11(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141779d11

uint64_t SynLift_141779e94(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141779e94

uint64_t SynLift_141779eb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141779eb0

uint64_t SynLift_141779f40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141779f40

uint64_t SynLift_141779f67(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141779f67

uint64_t SynLift_14177a32c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177a32c

uint64_t SynLift_14177a350(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177a350

uint64_t SynLift_14177a460(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177a460

uint64_t SynLift_14177a5c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177a5c0

uint64_t SynLift_14177a860(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177a860

uint64_t SynLift_14177aa60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177aa60

uint64_t SynLift_14177aba0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177aba0

uint64_t SynLift_14177ac60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177ac60

uint64_t SynLift_14177b300(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177b300

uint64_t SynLift_14177b650(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177b650

uint64_t SynLift_14177b6cc(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177b6cc

uint64_t SynLift_14177b6ee(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177b6ee

uint64_t SynLift_14177b800(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177b800

uint64_t SynLift_14177bcb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177bcb0

uint64_t SynLift_14177beb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177beb0

uint64_t SynLift_14177c0a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177c0a0

uint64_t SynLift_14177c2a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177c2a0

uint64_t SynLift_14177c4f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177c4f0

uint64_t SynLift_14177c542(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177c542

uint64_t SynLift_14177c58f(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177c58f

uint64_t SynLift_14177c620(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177c620

uint64_t SynLift_14177c660(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177c660

uint64_t SynLift_14177c740(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177c740

uint64_t SynLift_14177c870(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177c870

uint64_t SynLift_14177c8ac(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177c8ac

uint64_t SynLift_14177c927(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177c927

uint64_t SynLift_14177c970(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177c970

uint64_t SynLift_14177ca42(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177ca42

uint64_t SynLift_14177cad0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177cad0

uint64_t SynLift_14177cb40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177cb40

uint64_t SynLift_14177cb90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177cb90

uint64_t SynLift_14177cbd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177cbd0

uint64_t SynLift_14177cc42(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177cc42

uint64_t SynLift_14177cd14(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177cd14

uint64_t SynLift_14177cd18(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177cd18

uint64_t SynLift_14177cd40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177cd40

uint64_t SynLift_14177cdc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177cdc0

uint64_t SynLift_14177cdff(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177cdff

uint64_t SynLift_14177cf48(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177cf48

uint64_t SynLift_14177cfa0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177cfa0

uint64_t SynLift_14177d040(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177d040

uint64_t SynLift_14177d450(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177d450

uint64_t SynLift_14177d5f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177d5f0

uint64_t SynLift_14177d64b(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177d64b

uint64_t SynLift_14177d6bc(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177d6bc

uint64_t SynLift_14177d77e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177d77e

uint64_t SynLift_14177d9cb(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177d9cb

uint64_t SynLift_14177dfe0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177dfe0

uint64_t SynLift_14177e004(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177e004

uint64_t SynLift_14177e269(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177e269

uint64_t SynLift_14177e3b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177e3b0

uint64_t SynLift_14177e430(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177e430

uint64_t SynLift_14177e6dd(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177e6dd

uint64_t SynLift_14177e841(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177e841

uint64_t SynLift_14177e890(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177e890

uint64_t SynLift_14177ead0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177ead0

uint64_t SynLift_14177ed50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177ed50

uint64_t SynLift_14177f0d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177f0d0

uint64_t SynLift_14177f2d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177f2d0

uint64_t SynLift_14177f340(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177f340

uint64_t SynLift_14177f660(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177f660

uint64_t SynLift_14177f6b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177f6b0

uint64_t SynLift_14177f700(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177f700

uint64_t SynLift_14177f980(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177f980

uint64_t SynLift_14177f998(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177f998

uint64_t SynLift_14177f9d8(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177f9d8

uint64_t SynLift_14177f9f4(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177f9f4

uint64_t SynLift_14177fad0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14177fad0

uint64_t SynLift_1417800b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417800b0

uint64_t SynLift_141780170(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141780170

uint64_t SynLift_141780330(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141780330

uint64_t SynLift_141780440(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141780440

uint64_t SynLift_141780750(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141780750

uint64_t SynLift_1417807c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417807c0

uint64_t SynLift_1417807f3(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417807f3

uint64_t SynLift_14178086c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178086c

uint64_t SynLift_141780a30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141780a30

uint64_t SynLift_1417814c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417814c0

uint64_t SynLift_141781a6b(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141781a6b

uint64_t SynLift_141781ac2(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141781ac2

uint64_t SynLift_141781ae0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141781ae0

uint64_t SynLift_141781afb(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141781afb

uint64_t SynLift_141781b10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141781b10

uint64_t SynLift_141781c20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141781c20

uint64_t SynLift_141781eb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141781eb0

uint64_t SynLift_141781f30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141781f30

uint64_t SynLift_1417820e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417820e0

uint64_t SynLift_1417821d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417821d0

uint64_t SynLift_1417822d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417822d0

uint64_t SynLift_1417823e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417823e0

uint64_t SynLift_141782550(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141782550

uint64_t SynLift_141782685(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141782685

uint64_t SynLift_14178272e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178272e

uint64_t SynLift_141782793(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141782793

uint64_t SynLift_1417827eb(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417827eb

uint64_t SynLift_141782810(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141782810

uint64_t SynLift_141782823(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141782823

uint64_t SynLift_14178283e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178283e

uint64_t SynLift_141782970(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141782970

uint64_t SynLift_141782a40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141782a40

uint64_t SynLift_141782a90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141782a90

uint64_t SynLift_141782b90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141782b90

uint64_t SynLift_141782bf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141782bf0

uint64_t SynLift_1417831f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417831f0

uint64_t SynLift_141783250(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141783250

uint64_t SynLift_1417832b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417832b0

uint64_t SynLift_141783300(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141783300

uint64_t SynLift_141783350(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141783350

uint64_t SynLift_1417833b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417833b0

uint64_t SynLift_141783470(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141783470

uint64_t SynLift_141783940(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141783940

uint64_t SynLift_141783a10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141783a10

uint64_t SynLift_141783a40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141783a40

uint64_t SynLift_141783a90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141783a90

uint64_t SynLift_141783ad0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141783ad0

uint64_t SynLift_1417849f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417849f0

uint64_t SynLift_141784a89(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141784a89

uint64_t SynLift_141784c02(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141784c02

uint64_t SynLift_141784c50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141784c50

uint64_t SynLift_141785740(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141785740

uint64_t SynLift_1417857a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417857a0

uint64_t SynLift_14178590d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178590d

uint64_t SynLift_141785a40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141785a40

uint64_t SynLift_141785c70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141785c70

uint64_t SynLift_141785dc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141785dc0

uint64_t SynLift_141785e20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141785e20

uint64_t SynLift_141785f00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141785f00

uint64_t SynLift_141785ff0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141785ff0

uint64_t SynLift_1417860e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417860e0

uint64_t SynLift_1417861d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417861d0

uint64_t SynLift_141786620(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141786620

uint64_t SynLift_1417866d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417866d0

uint64_t SynLift_1417867d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417867d0

uint64_t SynLift_141786850(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141786850

uint64_t SynLift_1417868c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417868c0

uint64_t SynLift_141786960(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141786960

uint64_t SynLift_141786a20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141786a20

uint64_t SynLift_141786aa0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141786aa0

uint64_t SynLift_141786b30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141786b30

uint64_t SynLift_141786d80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141786d80

uint64_t SynLift_141786e30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141786e30

uint64_t SynLift_141786eb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141786eb0

uint64_t SynLift_141786f10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141786f10

uint64_t SynLift_141786f90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141786f90

uint64_t SynLift_141786ff0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141786ff0

uint64_t SynLift_141787050(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141787050

uint64_t SynLift_1417870c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417870c0

uint64_t SynLift_1417871c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417871c0

uint64_t SynLift_141787240(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141787240

uint64_t SynLift_1417872a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417872a0

uint64_t SynLift_14178732c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178732c

uint64_t SynLift_141787bb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141787bb0

uint64_t SynLift_141787c60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141787c60

uint64_t SynLift_141787d80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141787d80

uint64_t SynLift_141787de0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141787de0

uint64_t SynLift_141787f90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141787f90

uint64_t SynLift_1417881f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417881f0

uint64_t SynLift_141788224(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141788224

uint64_t SynLift_14178823e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178823e

uint64_t SynLift_14178826b(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178826b

uint64_t SynLift_14178834d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178834d

uint64_t SynLift_141788370(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141788370

uint64_t SynLift_1417886b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417886b0

uint64_t SynLift_1417887b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417887b0

uint64_t SynLift_1417888b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417888b0

uint64_t SynLift_1417889b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417889b0

uint64_t SynLift_141788ab0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141788ab0

uint64_t SynLift_141788c20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141788c20

uint64_t SynLift_141788e1e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141788e1e

uint64_t SynLift_141788fbe(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141788fbe

uint64_t SynLift_141789158(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141789158

uint64_t SynLift_141789160(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141789160

uint64_t SynLift_141789193(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141789193

uint64_t SynLift_1417891ae(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417891ae

uint64_t SynLift_1417891df(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417891df

uint64_t SynLift_141789327(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141789327

uint64_t SynLift_141789350(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141789350

uint64_t SynLift_1417893e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417893e0

uint64_t SynLift_141789440(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141789440

uint64_t SynLift_1417899a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417899a0

uint64_t SynLift_141789c00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141789c00

uint64_t SynLift_141789d70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141789d70

uint64_t SynLift_141789ea0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141789ea0

uint64_t SynLift_141789f00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141789f00

uint64_t SynLift_141789f80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141789f80

uint64_t SynLift_14178a200(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178a200

uint64_t SynLift_14178a290(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178a290

uint64_t SynLift_14178a4e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178a4e0

uint64_t SynLift_14178a560(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178a560

uint64_t SynLift_14178a650(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178a650

uint64_t SynLift_14178a7e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178a7e0

uint64_t SynLift_14178a810(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178a810

uint64_t SynLift_14178aa20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178aa20

uint64_t SynLift_14178ab70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178ab70

uint64_t SynLift_14178af30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178af30

uint64_t SynLift_14178afb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178afb0

uint64_t SynLift_14178b140(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178b140

uint64_t SynLift_14178b173(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178b173

uint64_t SynLift_14178b1c1(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178b1c1

uint64_t SynLift_14178b2a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178b2a0

uint64_t SynLift_14178b370(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178b370

uint64_t SynLift_14178b460(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178b460

uint64_t SynLift_14178b530(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178b530

uint64_t SynLift_14178b790(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178b790

uint64_t SynLift_14178b8b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178b8b0

uint64_t SynLift_14178ba60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178ba60

uint64_t SynLift_14178be50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178be50

uint64_t SynLift_14178c1b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178c1b0

uint64_t SynLift_14178c580(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178c580

uint64_t SynLift_14178c6a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178c6a0

uint64_t SynLift_14178c790(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178c790

uint64_t SynLift_14178c9f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178c9f0

uint64_t SynLift_14178ca80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178ca80

uint64_t SynLift_14178cb80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178cb80

uint64_t SynLift_14178cbfc(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178cbfc

uint64_t SynLift_14178cc1e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178cc1e

uint64_t SynLift_14178cd30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178cd30

uint64_t SynLift_14178ce70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178ce70

uint64_t SynLift_14178cee3(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178cee3

uint64_t SynLift_14178cf05(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178cf05

uint64_t SynLift_14178d060(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178d060

uint64_t SynLift_14178d140(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178d140

uint64_t SynLift_14178d330(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178d330

uint64_t SynLift_14178d500(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178d500

uint64_t SynLift_14178d850(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178d850

uint64_t SynLift_14178da90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178da90

uint64_t SynLift_14178dac0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178dac0

uint64_t SynLift_14178db20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178db20

uint64_t SynLift_14178dba0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178dba0

uint64_t SynLift_14178dd50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178dd50

uint64_t SynLift_14178dec0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178dec0

uint64_t SynLift_14178df30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178df30

uint64_t SynLift_14178e200(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178e200

uint64_t SynLift_14178e270(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178e270

uint64_t SynLift_14178e2e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178e2e0

uint64_t SynLift_14178e370(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178e370

uint64_t SynLift_14178e400(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178e400

uint64_t SynLift_14178e4a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178e4a0

uint64_t SynLift_14178e540(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178e540

uint64_t SynLift_14178e590(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178e590

uint64_t SynLift_14178ecd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178ecd0

uint64_t SynLift_14178ed80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178ed80

uint64_t SynLift_14178efd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178efd0

uint64_t SynLift_14178f004(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f004

uint64_t SynLift_14178f043(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f043

uint64_t SynLift_14178f080(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f080

uint64_t SynLift_14178f0bd(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f0bd

uint64_t SynLift_14178f0fa(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f0fa

uint64_t SynLift_14178f137(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f137

uint64_t SynLift_14178f174(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f174

uint64_t SynLift_14178f1a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f1a0

uint64_t SynLift_14178f204(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f204

uint64_t SynLift_14178f243(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f243

uint64_t SynLift_14178f2d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f2d0

uint64_t SynLift_14178f4f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f4f0

uint64_t SynLift_14178f550(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f550

uint64_t SynLift_14178f5b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f5b0

uint64_t SynLift_14178f610(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f610

uint64_t SynLift_14178f670(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f670

uint64_t SynLift_14178f6d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f6d0

uint64_t SynLift_14178f730(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f730

uint64_t SynLift_14178f7d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f7d0

uint64_t SynLift_14178f800(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f800

uint64_t SynLift_14178f870(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f870

uint64_t SynLift_14178f900(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f900

uint64_t SynLift_14178f960(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f960

uint64_t SynLift_14178f9f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178f9f0

uint64_t SynLift_14178fa70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178fa70

uint64_t SynLift_14178fbc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178fbc0

uint64_t SynLift_14178fca8(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178fca8

uint64_t SynLift_14178fd20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178fd20

uint64_t SynLift_14178fdc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178fdc0

uint64_t SynLift_14178fdf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14178fdf0

uint64_t SynLift_141790120(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141790120

uint64_t SynLift_141790390(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141790390

uint64_t SynLift_1417903d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417903d0

uint64_t SynLift_141790440(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141790440

uint64_t SynLift_141790a10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141790a10

uint64_t SynLift_141790bf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141790bf0

uint64_t SynLift_141790ce0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141790ce0

uint64_t SynLift_141790e10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141790e10

uint64_t SynLift_141790fe0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141790fe0

uint64_t SynLift_1417913f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417913f0

uint64_t SynLift_1417917a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417917a0

uint64_t SynLift_141791872(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141791872

uint64_t SynLift_1417918b6(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417918b6

uint64_t SynLift_141791a50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141791a50

uint64_t SynLift_141791ad0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141791ad0

uint64_t SynLift_141791b60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141791b60

uint64_t SynLift_141791bf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141791bf0

uint64_t SynLift_141792160(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141792160

uint64_t SynLift_1417921c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417921c0

uint64_t SynLift_141792240(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141792240

uint64_t SynLift_1417923e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417923e0

uint64_t SynLift_141792950(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141792950

uint64_t SynLift_1417929f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417929f0

uint64_t SynLift_141792ae0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141792ae0

uint64_t SynLift_141792b70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141792b70

uint64_t SynLift_141792c50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141792c50

uint64_t SynLift_141792c80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141792c80

uint64_t SynLift_141793180(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793180

uint64_t SynLift_141793220(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793220

uint64_t SynLift_1417933f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417933f0

uint64_t SynLift_141793470(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793470

uint64_t SynLift_141793630(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793630

uint64_t SynLift_1417936e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417936e0

uint64_t SynLift_1417939d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417939d0

uint64_t SynLift_141793aa0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793aa0

uint64_t SynLift_141793bf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793bf0

uint64_t SynLift_141793c1a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793c1a

uint64_t SynLift_141793cd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793cd0

uint64_t SynLift_141793d50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793d50

uint64_t SynLift_141793d65(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793d65

uint64_t SynLift_141793d7d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793d7d

uint64_t SynLift_141793e70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793e70

uint64_t SynLift_141793e9a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793e9a

uint64_t SynLift_141793f37(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793f37

uint64_t SynLift_141793f50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793f50

uint64_t SynLift_141793fd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793fd0

uint64_t SynLift_141793fe2(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793fe2

uint64_t SynLift_141793ffd(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141793ffd

uint64_t SynLift_1417940e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417940e0

uint64_t SynLift_141794110(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141794110

uint64_t SynLift_141794160(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141794160

uint64_t SynLift_1417941a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417941a0

uint64_t SynLift_1417941f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417941f0

uint64_t SynLift_141794280(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141794280

uint64_t SynLift_141794690(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141794690

uint64_t SynLift_141794770(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141794770

uint64_t SynLift_1417948b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417948b0

uint64_t SynLift_141794c70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141794c70

uint64_t SynLift_141794cf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141794cf0

uint64_t SynLift_141795230(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141795230

uint64_t SynLift_141795760(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141795760

uint64_t SynLift_141795850(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141795850

uint64_t SynLift_141795940(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141795940

uint64_t SynLift_141795980(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141795980

uint64_t SynLift_141795a30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141795a30

uint64_t SynLift_141795ca0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141795ca0

uint64_t SynLift_141795cc5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141795cc5

uint64_t SynLift_141795d40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141795d40

uint64_t SynLift_141795f70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141795f70

uint64_t SynLift_141795f98(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141795f98

uint64_t SynLift_141796000(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141796000

uint64_t SynLift_141796040(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141796040

uint64_t SynLift_141796390(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141796390

uint64_t SynLift_141796620(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141796620

uint64_t SynLift_141796680(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141796680

uint64_t SynLift_1417966d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417966d0

uint64_t SynLift_141796980(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141796980

uint64_t SynLift_1417969a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417969a0

uint64_t SynLift_141796a50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141796a50

uint64_t SynLift_141796b10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141796b10

uint64_t SynLift_141796cc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141796cc0

uint64_t SynLift_1417970d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417970d0

uint64_t SynLift_14179714c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179714c

uint64_t SynLift_14179716e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179716e

uint64_t SynLift_141797280(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141797280

uint64_t SynLift_141797520(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141797520

uint64_t SynLift_141797590(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141797590

uint64_t SynLift_141797630(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141797630

uint64_t SynLift_141797670(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141797670

uint64_t SynLift_1417976e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417976e0

uint64_t SynLift_141797750(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141797750

uint64_t SynLift_1417977d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417977d0

uint64_t SynLift_141797850(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141797850

uint64_t SynLift_141797890(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141797890

uint64_t SynLift_141797ce0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141797ce0

uint64_t SynLift_141797e00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141797e00

uint64_t SynLift_141797ef0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141797ef0

uint64_t SynLift_141798060(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141798060

uint64_t SynLift_141798160(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141798160

uint64_t SynLift_1417981f4(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417981f4

uint64_t SynLift_14179823f(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179823f

uint64_t SynLift_141798297(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141798297

uint64_t SynLift_1417983b3(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417983b3

uint64_t SynLift_1417983e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417983e0

uint64_t SynLift_141798407(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141798407

uint64_t SynLift_14179845e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179845e

uint64_t SynLift_1417984e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417984e0

uint64_t SynLift_141798650(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141798650

uint64_t SynLift_141798800(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141798800

uint64_t SynLift_141798910(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141798910

uint64_t SynLift_141798a20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141798a20

uint64_t SynLift_141798e90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141798e90

uint64_t SynLift_141798f80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141798f80

uint64_t SynLift_1417990c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417990c0

uint64_t SynLift_1417991f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417991f0

uint64_t SynLift_141799320(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141799320

uint64_t SynLift_141799480(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141799480

uint64_t SynLift_1417995c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417995c0

uint64_t SynLift_14179963c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179963c

uint64_t SynLift_14179965e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179965e

uint64_t SynLift_1417998d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417998d0

uint64_t SynLift_14179990a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179990a

uint64_t SynLift_141799abe(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141799abe

uint64_t SynLift_141799b75(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141799b75

uint64_t SynLift_141799bdc(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141799bdc

uint64_t SynLift_141799c60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141799c60

uint64_t SynLift_14179a020(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179a020

uint64_t SynLift_14179a150(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179a150

uint64_t SynLift_14179a500(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179a500

uint64_t SynLift_14179a720(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179a720

uint64_t SynLift_14179aa50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179aa50

uint64_t SynLift_14179ba80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179ba80

uint64_t SynLift_14179baa5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179baa5

uint64_t SynLift_14179bb82(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179bb82

uint64_t SynLift_14179bbd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179bbd0

uint64_t SynLift_14179bd60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179bd60

uint64_t SynLift_14179bf60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179bf60

uint64_t SynLift_14179bf80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179bf80

uint64_t SynLift_14179c0c6(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179c0c6

uint64_t SynLift_14179c0d5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179c0d5

uint64_t SynLift_14179c0f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179c0f0

uint64_t SynLift_14179c1b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179c1b0

uint64_t SynLift_14179c201(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179c201

uint64_t SynLift_14179c28d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179c28d

uint64_t SynLift_14179c2f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179c2f0

uint64_t SynLift_14179c490(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179c490

uint64_t SynLift_14179c5f4(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179c5f4

uint64_t SynLift_14179c610(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179c610

uint64_t SynLift_14179c700(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179c700

uint64_t SynLift_14179c765(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179c765

uint64_t SynLift_14179c7ab(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179c7ab

uint64_t SynLift_14179c820(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179c820

uint64_t SynLift_14179c8b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179c8b0

uint64_t SynLift_14179c940(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179c940

uint64_t SynLift_14179c9d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179c9d0

uint64_t SynLift_14179cb30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179cb30

uint64_t SynLift_14179cde0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179cde0

uint64_t SynLift_14179cf10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179cf10

uint64_t SynLift_14179d030(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179d030

uint64_t SynLift_14179d060(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179d060

uint64_t SynLift_14179d090(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179d090

uint64_t SynLift_14179d140(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179d140

uint64_t SynLift_14179d1f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179d1f0

uint64_t SynLift_14179d230(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179d230

uint64_t SynLift_14179d390(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179d390

uint64_t SynLift_14179d3c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179d3c0

uint64_t SynLift_14179d420(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179d420

uint64_t SynLift_14179d5d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179d5d0

uint64_t SynLift_14179d610(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179d610

uint64_t SynLift_14179d650(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179d650

uint64_t SynLift_14179d6b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179d6b0

uint64_t SynLift_14179d710(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179d710

uint64_t SynLift_14179d750(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179d750

uint64_t SynLift_14179d770(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179d770

uint64_t SynLift_14179d950(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179d950

uint64_t SynLift_14179db39(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179db39

uint64_t SynLift_14179dfaf(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179dfaf

uint64_t SynLift_14179e0b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179e0b0

uint64_t SynLift_14179e0fe(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179e0fe

uint64_t SynLift_14179e165(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179e165

uint64_t SynLift_14179e18a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179e18a

uint64_t SynLift_14179e1b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179e1b0

uint64_t SynLift_14179e210(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179e210

uint64_t SynLift_14179e280(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179e280

uint64_t SynLift_14179e390(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179e390

uint64_t SynLift_14179e420(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179e420

uint64_t SynLift_14179e580(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179e580

uint64_t SynLift_14179e620(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179e620

uint64_t SynLift_14179e690(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179e690

uint64_t SynLift_14179e6d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179e6d0

uint64_t SynLift_14179eb50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179eb50

uint64_t SynLift_14179eb90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179eb90

uint64_t SynLift_14179ec0c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179ec0c

uint64_t SynLift_14179ec2e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179ec2e

uint64_t SynLift_14179ed40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179ed40

uint64_t SynLift_14179f180(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179f180

uint64_t SynLift_14179f290(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179f290

uint64_t SynLift_14179f650(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179f650

uint64_t SynLift_14179f6e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179f6e0

uint64_t SynLift_14179fa60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179fa60

uint64_t SynLift_14179fc00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179fc00

uint64_t SynLift_14179fe10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179fe10

uint64_t SynLift_14179fe56(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14179fe56

uint64_t SynLift_1417a000e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a000e

uint64_t SynLift_1417a0020(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a0020

uint64_t SynLift_1417a0066(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a0066

uint64_t SynLift_1417a021e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a021e

uint64_t SynLift_1417a0230(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a0230

uint64_t SynLift_1417a0273(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a0273

uint64_t SynLift_1417a0320(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a0320

uint64_t SynLift_1417a0340(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a0340

uint64_t SynLift_1417a0450(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a0450

uint64_t SynLift_1417a04c2(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a04c2

uint64_t SynLift_1417a04df(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a04df

uint64_t SynLift_1417a0510(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a0510

uint64_t SynLift_1417a0556(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a0556

uint64_t SynLift_1417a056b(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a056b

uint64_t SynLift_1417a0588(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a0588

uint64_t SynLift_1417a05b6(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a05b6

uint64_t SynLift_1417a05d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a05d0

uint64_t SynLift_1417a065b(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a065b

uint64_t SynLift_1417a06b6(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a06b6

uint64_t SynLift_1417a0760(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a0760

uint64_t SynLift_1417a08d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a08d0

uint64_t SynLift_1417a0910(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a0910

uint64_t SynLift_1417a0a20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a0a20

uint64_t SynLift_1417a0ce0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a0ce0

uint64_t SynLift_1417a0fa0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a0fa0

uint64_t SynLift_1417a1180(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a1180

uint64_t SynLift_1417a2a10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a2a10

uint64_t SynLift_1417a2bf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a2bf0

uint64_t SynLift_1417a2c80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a2c80

uint64_t SynLift_1417a2cc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a2cc0

uint64_t SynLift_1417a2d20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a2d20

uint64_t SynLift_1417a2df0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a2df0

uint64_t SynLift_1417a2e70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a2e70

uint64_t SynLift_1417a2fd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a2fd0

uint64_t SynLift_1417a3380(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a3380

uint64_t SynLift_1417a3a90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a3a90

uint64_t SynLift_1417a3bd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a3bd0

uint64_t SynLift_1417a3c40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a3c40

uint64_t SynLift_1417a3cb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a3cb0

uint64_t SynLift_1417a3d20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a3d20

uint64_t SynLift_1417a3e30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a3e30

uint64_t SynLift_1417a4180(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a4180

uint64_t SynLift_1417a41af(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a41af

uint64_t SynLift_1417a4349(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a4349

uint64_t SynLift_1417a4397(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a4397

uint64_t SynLift_1417a43d1(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a43d1

uint64_t SynLift_1417a4530(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a4530

uint64_t SynLift_1417a45d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a45d0

uint64_t SynLift_1417a45e4(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a45e4

uint64_t SynLift_1417a45fc(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a45fc

uint64_t SynLift_1417a46e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a46e0

uint64_t SynLift_1417a4750(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a4750

uint64_t SynLift_1417a4980(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a4980

uint64_t SynLift_1417a4c70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a4c70

uint64_t SynLift_1417a4c90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a4c90

uint64_t SynLift_1417a4d00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a4d00

uint64_t SynLift_1417a4d40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a4d40

uint64_t SynLift_1417a4dc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a4dc0

uint64_t SynLift_1417a4e20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a4e20

uint64_t SynLift_1417a4e70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a4e70

uint64_t SynLift_1417a4ec0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a4ec0

uint64_t SynLift_1417a4f20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a4f20

uint64_t SynLift_1417a5010(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a5010

uint64_t SynLift_1417a5060(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a5060

uint64_t SynLift_1417a50b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a50b0

uint64_t SynLift_1417a5170(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a5170

uint64_t SynLift_1417a51b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a51b0

uint64_t SynLift_1417a51f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a51f0

uint64_t SynLift_1417a52a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a52a0

uint64_t SynLift_1417a5370(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a5370

uint64_t SynLift_1417a5400(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a5400

uint64_t SynLift_1417a54f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a54f0

uint64_t SynLift_1417a5610(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a5610

uint64_t SynLift_1417a58c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a58c0

uint64_t SynLift_1417a5b70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a5b70

uint64_t SynLift_1417a5c70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a5c70

uint64_t SynLift_1417a5d80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a5d80

uint64_t SynLift_1417a5e40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a5e40

uint64_t SynLift_1417a5f70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a5f70

uint64_t SynLift_1417a60a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a60a0

uint64_t SynLift_1417a62e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a62e0

uint64_t SynLift_1417a6390(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a6390

uint64_t SynLift_1417a6440(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a6440

uint64_t SynLift_1417a64b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a64b0

uint64_t SynLift_1417a6710(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a6710

uint64_t SynLift_1417a6960(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a6960

uint64_t SynLift_1417a6de0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a6de0

uint64_t SynLift_1417a6f90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a6f90

uint64_t SynLift_1417a70b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a70b0

uint64_t SynLift_1417a7320(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a7320

uint64_t SynLift_1417a75b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a75b0

uint64_t SynLift_1417a7620(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a7620

uint64_t SynLift_1417a7780(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a7780

uint64_t SynLift_1417a7d70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a7d70

uint64_t SynLift_1417a7d88(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a7d88

uint64_t SynLift_1417a7fb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a7fb0

uint64_t SynLift_1417a802c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a802c

uint64_t SynLift_1417a804e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a804e

uint64_t SynLift_1417a8160(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a8160

uint64_t SynLift_1417a8610(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a8610

uint64_t SynLift_1417a8940(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a8940

uint64_t SynLift_1417a8a50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a8a50

uint64_t SynLift_1417a8a7e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a8a7e

uint64_t SynLift_1417a8ab5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a8ab5

uint64_t SynLift_1417a8e40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a8e40

uint64_t SynLift_1417a8f70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a8f70

uint64_t SynLift_1417a9150(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a9150

uint64_t SynLift_1417a9180(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a9180

uint64_t SynLift_1417a9440(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a9440

uint64_t SynLift_1417a9470(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a9470

uint64_t SynLift_1417a9520(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a9520

uint64_t SynLift_1417a9560(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a9560

uint64_t SynLift_1417a95e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a95e0

uint64_t SynLift_1417a9680(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a9680

uint64_t SynLift_1417a9f20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a9f20

uint64_t SynLift_1417a9fc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417a9fc0

uint64_t SynLift_1417aa170(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aa170

uint64_t SynLift_1417aa280(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aa280

uint64_t SynLift_1417aa320(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aa320

uint64_t SynLift_1417aa3c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aa3c0

uint64_t SynLift_1417aa4e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aa4e0

uint64_t SynLift_1417aa510(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aa510

uint64_t SynLift_1417aa540(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aa540

uint64_t SynLift_1417aa56a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aa56a

uint64_t SynLift_1417aa5a3(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aa5a3

uint64_t SynLift_1417aab70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aab70

uint64_t SynLift_1417aabf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aabf0

uint64_t SynLift_1417aac33(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aac33

uint64_t SynLift_1417aac6a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aac6a

uint64_t SynLift_1417aac80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aac80

uint64_t SynLift_1417aacb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aacb0

uint64_t SynLift_1417aad30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aad30

uint64_t SynLift_1417aae40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aae40

uint64_t SynLift_1417aaff0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aaff0

uint64_t SynLift_1417ab020(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ab020

uint64_t SynLift_1417ab080(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ab080

uint64_t SynLift_1417ab0a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ab0a0

uint64_t SynLift_1417ab0c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ab0c0

uint64_t SynLift_1417ab0e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ab0e0

uint64_t SynLift_1417ab100(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ab100

uint64_t SynLift_1417ab170(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ab170

uint64_t SynLift_1417ab1a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ab1a0

uint64_t SynLift_1417ab8c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ab8c0

uint64_t SynLift_1417abc20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417abc20

uint64_t SynLift_1417abc70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417abc70

uint64_t SynLift_1417abcd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417abcd0

uint64_t SynLift_1417abe70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417abe70

uint64_t SynLift_1417abe90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417abe90

uint64_t SynLift_1417abec0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417abec0

uint64_t SynLift_1417abf50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417abf50

uint64_t SynLift_1417abfe0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417abfe0

uint64_t SynLift_1417ac040(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ac040

uint64_t SynLift_1417ac060(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ac060

uint64_t SynLift_1417ac080(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ac080

uint64_t SynLift_1417ac0d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ac0d0

uint64_t SynLift_1417ac100(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ac100

uint64_t SynLift_1417ac1b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ac1b0

uint64_t SynLift_1417ac1e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ac1e0

uint64_t SynLift_1417ac210(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ac210

uint64_t SynLift_1417ac440(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ac440

uint64_t SynLift_1417ac510(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ac510

uint64_t SynLift_1417ac52e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ac52e

uint64_t SynLift_1417ac54b(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ac54b

uint64_t SynLift_1417ac59a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ac59a

uint64_t SynLift_1417ac730(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ac730

uint64_t SynLift_1417ac750(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ac750

uint64_t SynLift_1417ac820(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ac820

uint64_t SynLift_1417ac9f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ac9f0

uint64_t SynLift_1417acc80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417acc80

uint64_t SynLift_1417adeb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417adeb0

uint64_t SynLift_1417ae130(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ae130

uint64_t SynLift_1417ae3a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ae3a0

uint64_t SynLift_1417ae6b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ae6b0

uint64_t SynLift_1417ae7b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ae7b0

uint64_t SynLift_1417ae7db(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ae7db

uint64_t SynLift_1417ae977(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ae977

uint64_t SynLift_1417ae994(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ae994

uint64_t SynLift_1417aea90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aea90

uint64_t SynLift_1417aebb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aebb0

uint64_t SynLift_1417af040(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417af040

uint64_t SynLift_1417af230(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417af230

uint64_t SynLift_1417af250(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417af250

uint64_t SynLift_1417af3e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417af3e0

uint64_t SynLift_1417af460(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417af460

uint64_t SynLift_1417af480(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417af480

uint64_t SynLift_1417af4b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417af4b0

uint64_t SynLift_1417af4d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417af4d0

uint64_t SynLift_1417af580(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417af580

uint64_t SynLift_1417af620(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417af620

uint64_t SynLift_1417af670(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417af670

uint64_t SynLift_1417af6c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417af6c0

uint64_t SynLift_1417af720(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417af720

uint64_t SynLift_1417af780(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417af780

uint64_t SynLift_1417af7d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417af7d0

uint64_t SynLift_1417af8e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417af8e0

uint64_t SynLift_1417af940(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417af940

uint64_t SynLift_1417af990(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417af990

uint64_t SynLift_1417af9f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417af9f0

uint64_t SynLift_1417afa70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417afa70

uint64_t SynLift_1417afba0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417afba0

uint64_t SynLift_1417afc40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417afc40

uint64_t SynLift_1417afc90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417afc90

uint64_t SynLift_1417afd50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417afd50

uint64_t SynLift_1417afdb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417afdb0

uint64_t SynLift_1417afe10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417afe10

uint64_t SynLift_1417afe40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417afe40

uint64_t SynLift_1417aff60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aff60

uint64_t SynLift_1417aff80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417aff80

uint64_t SynLift_1417affa0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417affa0

uint64_t SynLift_1417b0100(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b0100

uint64_t SynLift_1417b0200(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b0200

uint64_t SynLift_1417b02f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b02f0

uint64_t SynLift_1417b0770(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b0770

uint64_t SynLift_1417b07c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b07c0

uint64_t SynLift_1417b07d8(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b07d8

uint64_t SynLift_1417b07f4(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b07f4

uint64_t SynLift_1417b0810(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b0810

uint64_t SynLift_1417b0890(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b0890

uint64_t SynLift_1417b0980(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b0980

uint64_t SynLift_1417b0ca0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b0ca0

uint64_t SynLift_1417b0d80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b0d80

uint64_t SynLift_1417b0db0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b0db0

uint64_t SynLift_1417b0de0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b0de0

uint64_t SynLift_1417b0e00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b0e00

uint64_t SynLift_1417b0e20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b0e20

uint64_t SynLift_1417b0e50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b0e50

uint64_t SynLift_1417b0e70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b0e70

uint64_t SynLift_1417b1090(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b1090

uint64_t SynLift_1417b1240(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b1240

uint64_t SynLift_1417b1380(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b1380

uint64_t SynLift_1417b13b3(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b13b3

uint64_t SynLift_1417b1416(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b1416

uint64_t SynLift_1417b1436(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b1436

uint64_t SynLift_1417b1450(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b1450

uint64_t SynLift_1417b1647(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b1647

uint64_t SynLift_1417b1660(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b1660

uint64_t SynLift_1417b1690(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b1690

uint64_t SynLift_1417b1960(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b1960

uint64_t SynLift_1417b1980(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b1980

uint64_t SynLift_1417b19e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b19e0

uint64_t SynLift_1417b1a62(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b1a62

uint64_t SynLift_1417b1b30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b1b30

uint64_t SynLift_1417b1cf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b1cf0

uint64_t SynLift_1417b1d99(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b1d99

uint64_t SynLift_1417b1dbb(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b1dbb

uint64_t SynLift_1417b2320(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b2320

uint64_t SynLift_1417b2400(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b2400

uint64_t SynLift_1417b2437(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b2437

uint64_t SynLift_1417b2483(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b2483

uint64_t SynLift_1417b264d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b264d

uint64_t SynLift_1417b26f3(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b26f3

uint64_t SynLift_1417b2741(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b2741

uint64_t SynLift_1417b276b(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b276b

uint64_t SynLift_1417b2780(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b2780

uint64_t SynLift_1417b27b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b27b0

uint64_t SynLift_1417b2815(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b2815

uint64_t SynLift_1417b287d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b287d

uint64_t SynLift_1417b2881(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b2881

uint64_t SynLift_1417b28c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b28c0

uint64_t SynLift_1417b29a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b29a0

uint64_t SynLift_1417b2a30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b2a30

uint64_t SynLift_1417b2df0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b2df0

uint64_t SynLift_1417b31c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b31c0

uint64_t SynLift_1417b3276(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b3276

uint64_t SynLift_1417b52d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b52d0

uint64_t SynLift_1417b5300(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b5300

uint64_t SynLift_1417b5510(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b5510

uint64_t SynLift_1417b5710(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b5710

uint64_t SynLift_1417b5760(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b5760

uint64_t SynLift_1417b5830(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b5830

uint64_t SynLift_1417b5880(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b5880

uint64_t SynLift_1417b5910(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b5910

uint64_t SynLift_1417b5d90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b5d90

uint64_t SynLift_1417b5e70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b5e70

uint64_t SynLift_1417b6170(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b6170

uint64_t SynLift_1417b61e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b61e0

uint64_t SynLift_1417b64e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b64e0

uint64_t SynLift_1417b6620(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b6620

uint64_t SynLift_1417b6770(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b6770

uint64_t SynLift_1417b6ab0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b6ab0

uint64_t SynLift_1417b6df0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b6df0

uint64_t SynLift_1417b6e30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b6e30

uint64_t SynLift_1417b6e70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b6e70

uint64_t SynLift_1417b7850(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b7850

uint64_t SynLift_1417b7ae0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b7ae0

uint64_t SynLift_1417b7c10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b7c10

uint64_t SynLift_1417b7e70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b7e70

uint64_t SynLift_1417b8150(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b8150

uint64_t SynLift_1417b8620(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b8620

uint64_t SynLift_1417b90b4(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b90b4

uint64_t SynLift_1417b920c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b920c

uint64_t SynLift_1417b9220(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b9220

uint64_t SynLift_1417b923d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b923d

uint64_t SynLift_1417b9286(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b9286

uint64_t SynLift_1417b92b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b92b0

uint64_t SynLift_1417b92f4(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b92f4

uint64_t SynLift_1417b935b(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b935b

uint64_t SynLift_1417b9380(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b9380

uint64_t SynLift_1417b93c2(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b93c2

uint64_t SynLift_1417b93e1(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b93e1

uint64_t SynLift_1417b9486(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b9486

uint64_t SynLift_1417b9628(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b9628

uint64_t SynLift_1417b9650(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b9650

uint64_t SynLift_1417b9f30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b9f30

uint64_t SynLift_1417b9f80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417b9f80

uint64_t SynLift_1417ba160(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ba160

uint64_t SynLift_1417ba5a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ba5a0

uint64_t SynLift_1417ba630(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ba630

uint64_t SynLift_1417ba6f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ba6f0

uint64_t SynLift_1417bad50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bad50

uint64_t SynLift_1417bb0e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bb0e0

uint64_t SynLift_1417bb500(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bb500

uint64_t SynLift_1417bb730(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bb730

uint64_t SynLift_1417bb920(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bb920

uint64_t SynLift_1417bb980(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bb980

uint64_t SynLift_1417bbaae(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bbaae

uint64_t SynLift_1417bbb82(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bbb82

uint64_t SynLift_1417bbd54(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bbd54

uint64_t SynLift_1417bbd70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bbd70

uint64_t SynLift_1417bbdb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bbdb0

uint64_t SynLift_1417bbde0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bbde0

uint64_t SynLift_1417bc0b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bc0b0

uint64_t SynLift_1417bc150(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bc150

uint64_t SynLift_1417bc640(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bc640

uint64_t SynLift_1417bc6b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bc6b0

uint64_t SynLift_1417bc732(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bc732

uint64_t SynLift_1417bc8e5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bc8e5

uint64_t SynLift_1417bc952(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bc952

uint64_t SynLift_1417bcb09(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bcb09

uint64_t SynLift_1417bcbb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bcbb0

uint64_t SynLift_1417bcc10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bcc10

uint64_t SynLift_1417bcc70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bcc70

uint64_t SynLift_1417bccd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bccd0

uint64_t SynLift_1417bcd10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bcd10

uint64_t SynLift_1417bcfd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bcfd0

uint64_t SynLift_1417bd1a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bd1a0

uint64_t SynLift_1417bd310(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bd310

uint64_t SynLift_1417bd550(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bd550

uint64_t SynLift_1417bdb20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bdb20

uint64_t SynLift_1417bdf20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bdf20

uint64_t SynLift_1417be250(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417be250

uint64_t SynLift_1417be280(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417be280

uint64_t SynLift_1417be2b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417be2b0

uint64_t SynLift_1417be310(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417be310

uint64_t SynLift_1417be5f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417be5f0

uint64_t SynLift_1417bf530(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bf530

uint64_t SynLift_1417bf570(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bf570

uint64_t SynLift_1417bf5b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bf5b0

uint64_t SynLift_1417bf960(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bf960

uint64_t SynLift_1417bfdd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417bfdd0

uint64_t SynLift_1417c0510(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c0510

uint64_t SynLift_1417c1180(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c1180

uint64_t SynLift_1417c13e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c13e0

uint64_t SynLift_1417c16f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c16f0

uint64_t SynLift_1417c4511(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c4511

uint64_t SynLift_1417c5500(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c5500

uint64_t SynLift_1417c5b30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c5b30

uint64_t SynLift_1417c5b80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c5b80

uint64_t SynLift_1417c5e10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c5e10

uint64_t SynLift_1417c6210(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c6210

uint64_t SynLift_1417c77e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c77e0

uint64_t SynLift_1417c7850(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c7850

uint64_t SynLift_1417c81f3(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c81f3

uint64_t SynLift_1417c8241(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c8241

uint64_t SynLift_1417c8370(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c8370

uint64_t SynLift_1417c8950(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c8950

uint64_t SynLift_1417c8980(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c8980

uint64_t SynLift_1417c89d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c89d0

uint64_t SynLift_1417c8aa0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c8aa0

uint64_t SynLift_1417c8c10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c8c10

uint64_t SynLift_1417c8d80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c8d80

uint64_t SynLift_1417c92f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c92f0

uint64_t SynLift_1417c96e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c96e0

uint64_t SynLift_1417c9760(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c9760

uint64_t SynLift_1417c9b20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c9b20

uint64_t SynLift_1417c9ca0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417c9ca0

uint64_t SynLift_1417ca7f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ca7f0

uint64_t SynLift_1417ca840(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ca840

uint64_t SynLift_1417ca930(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ca930

uint64_t SynLift_1417caa00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417caa00

uint64_t SynLift_1417cab90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cab90

uint64_t SynLift_1417cad23(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cad23

uint64_t SynLift_1417cad55(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cad55

uint64_t SynLift_1417cad90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cad90

uint64_t SynLift_1417cadb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cadb0

uint64_t SynLift_1417cade0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cade0

uint64_t SynLift_1417cb000(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cb000

uint64_t SynLift_1417cb030(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cb030

uint64_t SynLift_1417cb1c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cb1c0

uint64_t SynLift_1417cb580(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cb580

uint64_t SynLift_1417cb5fc(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cb5fc

uint64_t SynLift_1417cb61e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cb61e

uint64_t SynLift_1417cb7a3(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cb7a3

uint64_t SynLift_1417cb7c5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cb7c5

uint64_t SynLift_1417cb8e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cb8e0

uint64_t SynLift_1417ccb70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ccb70

uint64_t SynLift_1417ccf80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ccf80

uint64_t SynLift_1417cd4e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cd4e0

uint64_t SynLift_1417cd520(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cd520

uint64_t SynLift_1417cd59c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cd59c

uint64_t SynLift_1417cd5be(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cd5be

uint64_t SynLift_1417cd7a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cd7a0

uint64_t SynLift_1417cd7d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cd7d0

uint64_t SynLift_1417cdb50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cdb50

uint64_t SynLift_1417cec20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cec20

uint64_t SynLift_1417cf360(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cf360

uint64_t SynLift_1417cfa30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cfa30

uint64_t SynLift_1417cfb60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417cfb60

uint64_t SynLift_1417d0020(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d0020

uint64_t SynLift_1417d0080(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d0080

uint64_t SynLift_1417d03a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d03a0

uint64_t SynLift_1417d0430(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d0430

uint64_t SynLift_1417d0480(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d0480

uint64_t SynLift_1417d04e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d04e0

uint64_t SynLift_1417d0540(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d0540

uint64_t SynLift_1417d05a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d05a0

uint64_t SynLift_1417d0640(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d0640

uint64_t SynLift_1417d06a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d06a0

uint64_t SynLift_1417d0740(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d0740

uint64_t SynLift_1417d07a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d07a0

uint64_t SynLift_1417d08a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d08a0

uint64_t SynLift_1417d09a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d09a0

uint64_t SynLift_1417d0aa0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d0aa0

uint64_t SynLift_1417d0ba0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d0ba0

uint64_t SynLift_1417d0ca0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d0ca0

uint64_t SynLift_1417d0da0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d0da0

uint64_t SynLift_1417d1030(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d1030

uint64_t SynLift_1417d12d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d12d0

uint64_t SynLift_1417d1300(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d1300

uint64_t SynLift_1417d1358(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d1358

uint64_t SynLift_1417d137a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d137a

uint64_t SynLift_1417d13d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d13d0

uint64_t SynLift_1417d150c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d150c

uint64_t SynLift_1417d1669(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d1669

uint64_t SynLift_1417d1680(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d1680

uint64_t SynLift_1417d16b4(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d16b4

uint64_t SynLift_1417d16f7(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d16f7

uint64_t SynLift_1417d1840(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d1840

uint64_t SynLift_1417d18d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d18d0

uint64_t SynLift_1417d1930(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d1930

uint64_t SynLift_1417d1a20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d1a20

uint64_t SynLift_1417d1ca2(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d1ca2

uint64_t SynLift_1417d1ce6(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d1ce6

uint64_t SynLift_1417d2080(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2080

uint64_t SynLift_1417d2110(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2110

uint64_t SynLift_1417d2230(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2230

uint64_t SynLift_1417d2280(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2280

uint64_t SynLift_1417d22f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d22f0

uint64_t SynLift_1417d2360(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2360

uint64_t SynLift_1417d2590(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2590

uint64_t SynLift_1417d25ba(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d25ba

uint64_t SynLift_1417d2657(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2657

uint64_t SynLift_1417d2670(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2670

uint64_t SynLift_1417d26f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d26f0

uint64_t SynLift_1417d2702(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2702

uint64_t SynLift_1417d271d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d271d

uint64_t SynLift_1417d2800(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2800

uint64_t SynLift_1417d2990(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2990

uint64_t SynLift_1417d2bc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2bc0

uint64_t SynLift_1417d2be8(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2be8

uint64_t SynLift_1417d2c50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2c50

uint64_t SynLift_1417d2c90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2c90

uint64_t SynLift_1417d2cf0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2cf0

uint64_t SynLift_1417d2d40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2d40

uint64_t SynLift_1417d2d90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2d90

uint64_t SynLift_1417d2df0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2df0

uint64_t SynLift_1417d2f10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2f10

uint64_t SynLift_1417d2f50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2f50

uint64_t SynLift_1417d2fc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d2fc0

uint64_t SynLift_1417d3100(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d3100

uint64_t SynLift_1417d3530(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d3530

uint64_t SynLift_1417d35b4(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d35b4

uint64_t SynLift_1417d35e3(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d35e3

uint64_t SynLift_1417d3680(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d3680

uint64_t SynLift_1417d3800(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d3800

uint64_t SynLift_1417d3890(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d3890

uint64_t SynLift_1417d3980(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d3980

uint64_t SynLift_1417d3c40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d3c40

uint64_t SynLift_1417d3e80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d3e80

uint64_t SynLift_1417d3eb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d3eb0

uint64_t SynLift_1417d3fe0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d3fe0

uint64_t SynLift_1417d4160(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d4160

uint64_t SynLift_1417d4270(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d4270

uint64_t SynLift_1417d4480(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d4480

uint64_t SynLift_1417d44a3(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d44a3

uint64_t SynLift_1417d4510(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d4510

uint64_t SynLift_1417d4670(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d4670

uint64_t SynLift_1417d4870(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d4870

uint64_t SynLift_1417d4d60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d4d60

uint64_t SynLift_1417d4e10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d4e10

uint64_t SynLift_1417d4e70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d4e70

uint64_t SynLift_1417d4ed0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d4ed0

uint64_t SynLift_1417d4fd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d4fd0

uint64_t SynLift_1417d5070(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d5070

uint64_t SynLift_1417d50c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d50c0

uint64_t SynLift_1417d50f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d50f0

uint64_t SynLift_1417d5140(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d5140

uint64_t SynLift_1417d53f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d53f0

uint64_t SynLift_1417d5460(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d5460

uint64_t SynLift_1417d54b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d54b0

uint64_t SynLift_1417d5588(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d5588

uint64_t SynLift_1417d55a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d55a0

uint64_t SynLift_1417d55e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d55e0

uint64_t SynLift_1417d56b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d56b0

uint64_t SynLift_1417d5780(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d5780

uint64_t SynLift_1417d5820(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d5820

uint64_t SynLift_1417d58d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d58d0

uint64_t SynLift_1417d5a50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d5a50

uint64_t SynLift_1417d5aa0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d5aa0

uint64_t SynLift_1417d5ae0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d5ae0

uint64_t SynLift_1417d5b50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d5b50

uint64_t SynLift_1417d5c10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d5c10

uint64_t SynLift_1417d5cc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d5cc0

uint64_t SynLift_1417d5e50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d5e50

uint64_t SynLift_1417d5ea0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d5ea0

uint64_t SynLift_1417d5f00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d5f00

uint64_t SynLift_1417d6110(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d6110

uint64_t SynLift_1417d6160(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d6160

uint64_t SynLift_1417d61c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d61c0

uint64_t SynLift_1417d6360(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d6360

uint64_t SynLift_1417d63b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d63b0

uint64_t SynLift_1417d6640(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d6640

uint64_t SynLift_1417d6790(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d6790

uint64_t SynLift_1417d6820(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d6820

uint64_t SynLift_1417d7350(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d7350

uint64_t SynLift_1417d73a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d73a0

uint64_t SynLift_1417d73e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d73e0

uint64_t SynLift_1417d7440(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d7440

uint64_t SynLift_1417d7500(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d7500

uint64_t SynLift_1417d75b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d75b0

uint64_t SynLift_1417d7650(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d7650

uint64_t SynLift_1417d7770(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d7770

uint64_t SynLift_1417d7800(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d7800

uint64_t SynLift_1417d7850(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d7850

uint64_t SynLift_1417d78b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d78b0

uint64_t SynLift_1417d7ab0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d7ab0

uint64_t SynLift_1417d7b00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d7b00

uint64_t SynLift_1417d7b60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d7b60

uint64_t SynLift_1417d7be0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d7be0

uint64_t SynLift_1417d7d60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d7d60

uint64_t SynLift_1417d7df0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d7df0

uint64_t SynLift_1417d7e40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d7e40

uint64_t SynLift_1417d7ee0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d7ee0

uint64_t SynLift_1417d7f20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d7f20

uint64_t SynLift_1417d7ff0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d7ff0

uint64_t SynLift_1417d80c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d80c0

uint64_t SynLift_1417d8160(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d8160

uint64_t SynLift_1417d8220(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d8220

uint64_t SynLift_1417d82b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d82b0

uint64_t SynLift_1417d8390(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d8390

uint64_t SynLift_1417d84d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d84d0

uint64_t SynLift_1417d8530(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d8530

uint64_t SynLift_1417d8570(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d8570

uint64_t SynLift_1417d8640(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d8640

uint64_t SynLift_1417d8710(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d8710

uint64_t SynLift_1417d8730(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d8730

uint64_t SynLift_1417d8c20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d8c20

uint64_t SynLift_1417d8c70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d8c70

uint64_t SynLift_1417d8cd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d8cd0

uint64_t SynLift_1417d8d40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d8d40

uint64_t SynLift_1417d8f90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d8f90

uint64_t SynLift_1417d9000(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d9000

uint64_t SynLift_1417d932c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d932c

uint64_t SynLift_1417d9365(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d9365

uint64_t SynLift_1417d9410(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d9410

uint64_t SynLift_1417d9460(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d9460

uint64_t SynLift_1417d94c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d94c0

uint64_t SynLift_1417d9710(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d9710

uint64_t SynLift_1417d9900(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d9900

uint64_t SynLift_1417d9950(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d9950

uint64_t SynLift_1417d9a00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d9a00

uint64_t SynLift_1417d9a60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d9a60

uint64_t SynLift_1417d9ac0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d9ac0

uint64_t SynLift_1417d9b30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d9b30

uint64_t SynLift_1417d9cc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d9cc0

uint64_t SynLift_1417d9e60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d9e60

uint64_t SynLift_1417d9f10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d9f10

uint64_t SynLift_1417d9f90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417d9f90

uint64_t SynLift_1417da020(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417da020

uint64_t SynLift_1417da0d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417da0d0

uint64_t SynLift_1417da170(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417da170

uint64_t SynLift_1417da5b1(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417da5b1

uint64_t SynLift_1417da602(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417da602

uint64_t SynLift_1417da63e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417da63e

uint64_t SynLift_1417da68c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417da68c

uint64_t SynLift_1417da6ae(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417da6ae

uint64_t SynLift_1417da712(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417da712

uint64_t SynLift_1417da860(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417da860

uint64_t SynLift_1417dab00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dab00

uint64_t SynLift_1417dac30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dac30

uint64_t SynLift_1417dae10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dae10

uint64_t SynLift_1417daf60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417daf60

uint64_t SynLift_1417dafb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dafb0

uint64_t SynLift_1417db2b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417db2b0

uint64_t SynLift_1417db3a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417db3a0

uint64_t SynLift_1417db450(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417db450

uint64_t SynLift_1417db630(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417db630

uint64_t SynLift_1417dca60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dca60

uint64_t SynLift_1417dcf77(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dcf77

uint64_t SynLift_1417dd050(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dd050

uint64_t SynLift_1417dd230(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dd230

uint64_t SynLift_1417dd2e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dd2e0

uint64_t SynLift_1417dd4b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dd4b0

uint64_t SynLift_1417dd6e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dd6e0

uint64_t SynLift_1417dd9f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dd9f0

uint64_t SynLift_1417ddc60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ddc60

uint64_t SynLift_1417ddd10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ddd10

uint64_t SynLift_1417ddf50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ddf50

uint64_t SynLift_1417de000(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417de000

uint64_t SynLift_1417de240(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417de240

uint64_t SynLift_1417de4a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417de4a0

uint64_t SynLift_1417de560(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417de560

uint64_t SynLift_1417de840(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417de840

uint64_t SynLift_1417de9d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417de9d0

uint64_t SynLift_1417dea00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dea00

uint64_t SynLift_1417dea30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dea30

uint64_t SynLift_1417dea60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dea60

uint64_t SynLift_1417deb00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417deb00

uint64_t SynLift_1417deba0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417deba0

uint64_t SynLift_1417dec60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dec60

uint64_t SynLift_1417ded20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ded20

uint64_t SynLift_1417ded70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ded70

uint64_t SynLift_1417dedc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dedc0

uint64_t SynLift_1417dee00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dee00

uint64_t SynLift_1417df150(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417df150

uint64_t SynLift_1417df290(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417df290

uint64_t SynLift_1417df2f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417df2f0

uint64_t SynLift_1417df4e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417df4e0

uint64_t SynLift_1417df5b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417df5b0

uint64_t SynLift_1417df5f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417df5f0

uint64_t SynLift_1417df7d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417df7d0

uint64_t SynLift_1417df880(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417df880

uint64_t SynLift_1417df930(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417df930

uint64_t SynLift_1417dfb50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dfb50

uint64_t SynLift_1417dfb90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dfb90

uint64_t SynLift_1417dfbe0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dfbe0

uint64_t SynLift_1417dfcd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dfcd0

uint64_t SynLift_1417dfe50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dfe50

uint64_t SynLift_1417dff00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417dff00

uint64_t SynLift_1417e0000(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e0000

uint64_t SynLift_1417e0050(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e0050

uint64_t SynLift_1417e0070(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e0070

uint64_t SynLift_1417e01f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e01f0

uint64_t SynLift_1417e02c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e02c0

uint64_t SynLift_1417e07a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e07a0

uint64_t SynLift_1417e1040(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1040

uint64_t SynLift_1417e1090(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1090

uint64_t SynLift_1417e10e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e10e0

uint64_t SynLift_1417e1120(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1120

uint64_t SynLift_1417e1150(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1150

uint64_t SynLift_1417e1190(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1190

uint64_t SynLift_1417e1290(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1290

uint64_t SynLift_1417e13e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e13e0

uint64_t SynLift_1417e1450(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1450

uint64_t SynLift_1417e1490(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1490

uint64_t SynLift_1417e14f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e14f0

uint64_t SynLift_1417e1660(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1660

uint64_t SynLift_1417e17a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e17a0

uint64_t SynLift_1417e1820(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1820

uint64_t SynLift_1417e1840(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1840

uint64_t SynLift_1417e1880(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1880

uint64_t SynLift_1417e18d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e18d0

uint64_t SynLift_1417e1920(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1920

uint64_t SynLift_1417e1a90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1a90

uint64_t SynLift_1417e1ae0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1ae0

uint64_t SynLift_1417e1b10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1b10

uint64_t SynLift_1417e1c20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1c20

uint64_t SynLift_1417e1cd0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1cd0

uint64_t SynLift_1417e1d60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1d60

uint64_t SynLift_1417e1db0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1db0

uint64_t SynLift_1417e1e10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1e10

uint64_t SynLift_1417e1ec0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1ec0

uint64_t SynLift_1417e1f60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1f60

uint64_t SynLift_1417e1f80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e1f80

uint64_t SynLift_1417e24a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e24a0

uint64_t SynLift_1417e2500(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e2500

uint64_t SynLift_1417e25c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e25c0

uint64_t SynLift_1417e25f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e25f0

uint64_t SynLift_1417e2610(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e2610

uint64_t SynLift_1417e2650(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e2650

uint64_t SynLift_1417e2680(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e2680

uint64_t SynLift_1417e26d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e26d0

uint64_t SynLift_1417e2730(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e2730

uint64_t SynLift_1417e2770(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e2770

uint64_t SynLift_1417e27f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e27f0

uint64_t SynLift_1417e2890(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e2890

uint64_t SynLift_1417e28b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e28b0

uint64_t SynLift_1417e2940(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e2940

uint64_t SynLift_1417e2990(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e2990

uint64_t SynLift_1417e29d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e29d0

uint64_t SynLift_1417e2b30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e2b30

uint64_t SynLift_1417e2b50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e2b50

uint64_t SynLift_1417e2c30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e2c30

uint64_t SynLift_1417e2c90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e2c90

uint64_t SynLift_1417e2da0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e2da0

uint64_t SynLift_1417e2e00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e2e00

uint64_t SynLift_1417e2e80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e2e80

uint64_t SynLift_1417e2fe0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e2fe0

uint64_t SynLift_1417e3130(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e3130

uint64_t SynLift_1417e3190(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e3190

uint64_t SynLift_1417e3240(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e3240

uint64_t SynLift_1417e32e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e32e0

uint64_t SynLift_1417e3320(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e3320

uint64_t SynLift_1417e3370(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e3370

uint64_t SynLift_1417e33e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e33e0

uint64_t SynLift_1417e34e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e34e0

uint64_t SynLift_1417e3620(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e3620

uint64_t SynLift_1417e3690(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e3690

uint64_t SynLift_1417e3750(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e3750

uint64_t SynLift_1417e5af0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e5af0

uint64_t SynLift_1417e5ba0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e5ba0

uint64_t SynLift_1417e5be0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e5be0

uint64_t SynLift_1417e7920(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e7920

uint64_t SynLift_1417e7c70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e7c70

uint64_t SynLift_1417e7d20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e7d20

uint64_t SynLift_1417e81e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e81e0

uint64_t SynLift_1417e8250(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e8250

uint64_t SynLift_1417e8370(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e8370

uint64_t SynLift_1417e83b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e83b0

uint64_t SynLift_1417e83e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e83e0

uint64_t SynLift_1417e85e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e85e0

uint64_t SynLift_1417e8690(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e8690

uint64_t SynLift_1417e86d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e86d0

uint64_t SynLift_1417e87d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e87d0

uint64_t SynLift_1417e88a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e88a0

uint64_t SynLift_1417e89a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e89a0

uint64_t SynLift_1417e8a00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e8a00

uint64_t SynLift_1417e8a70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e8a70

uint64_t SynLift_1417e8b20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e8b20

uint64_t SynLift_1417e8ba0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e8ba0

uint64_t SynLift_1417e8cb4(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e8cb4

uint64_t SynLift_1417e8d00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e8d00

uint64_t SynLift_1417e8d20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e8d20

uint64_t SynLift_1417e8d34(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e8d34

uint64_t SynLift_1417e9014(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e9014

uint64_t SynLift_1417e9080(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e9080

uint64_t SynLift_1417e9094(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e9094

uint64_t SynLift_1417e90e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e90e0

uint64_t SynLift_1417e9142(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e9142

uint64_t SynLift_1417e9175(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e9175

uint64_t SynLift_1417e91a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e91a0

uint64_t SynLift_1417e9200(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e9200

uint64_t SynLift_1417e9572(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e9572

uint64_t SynLift_1417e959e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e959e

uint64_t SynLift_1417e95ca(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e95ca

uint64_t SynLift_1417e9642(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e9642

uint64_t SynLift_1417e9675(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e9675

uint64_t SynLift_1417e9685(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e9685

uint64_t SynLift_1417e977d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e977d

uint64_t SynLift_1417e97f6(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e97f6

uint64_t SynLift_1417e9836(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e9836

uint64_t SynLift_1417e9990(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e9990

uint64_t SynLift_1417e99f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e99f0

uint64_t SynLift_1417e9ed0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e9ed0

uint64_t SynLift_1417e9f10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417e9f10

uint64_t SynLift_1417ea060(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ea060

uint64_t SynLift_1417ea0d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ea0d0

uint64_t SynLift_1417ea240(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ea240

uint64_t SynLift_1417ea290(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ea290

uint64_t SynLift_1417ea2e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ea2e0

uint64_t SynLift_1417ea52a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ea52a

uint64_t SynLift_1417ea559(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ea559

uint64_t SynLift_1417ea7f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ea7f0

uint64_t SynLift_1417ea9a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ea9a0

uint64_t SynLift_1417ea9f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ea9f0

uint64_t SynLift_1417eaa40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eaa40

uint64_t SynLift_1417eab40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eab40

uint64_t SynLift_1417eac90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eac90

uint64_t SynLift_1417eade0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eade0

uint64_t SynLift_1417eaea4(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eaea4

uint64_t SynLift_1417eaef0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eaef0

uint64_t SynLift_1417eaf10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eaf10

uint64_t SynLift_1417eaf24(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eaf24

uint64_t SynLift_1417eb474(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eb474

uint64_t SynLift_1417eb4e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eb4e0

uint64_t SynLift_1417eb4f4(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eb4f4

uint64_t SynLift_1417eb5a2(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eb5a2

uint64_t SynLift_1417eb5d5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eb5d5

uint64_t SynLift_1417eb600(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eb600

uint64_t SynLift_1417eb660(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eb660

uint64_t SynLift_1417eb7c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eb7c0

uint64_t SynLift_1417eb948(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eb948

uint64_t SynLift_1417eb96e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eb96e

uint64_t SynLift_1417eb99a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eb99a

uint64_t SynLift_1417eb9c5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eb9c5

uint64_t SynLift_1417eb9f5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eb9f5

uint64_t SynLift_1417eba05(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eba05

uint64_t SynLift_1417eba5d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eba5d

uint64_t SynLift_1417ebaae(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ebaae

uint64_t SynLift_1417ebae2(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ebae2

uint64_t SynLift_1417ebc00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ebc00

uint64_t SynLift_1417ebc60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ebc60

uint64_t SynLift_1417ec050(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ec050

uint64_t SynLift_1417ec090(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ec090

uint64_t SynLift_1417ec1e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ec1e0

uint64_t SynLift_1417ec334(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ec334

uint64_t SynLift_1417ec38b(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ec38b

uint64_t SynLift_1417ec4a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ec4a0

uint64_t SynLift_1417ec630(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ec630

uint64_t SynLift_1417ec680(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ec680

uint64_t SynLift_1417ec6d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ec6d0

uint64_t SynLift_1417ec730(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ec730

uint64_t SynLift_1417ec790(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ec790

uint64_t SynLift_1417ec800(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ec800

uint64_t SynLift_1417ec8b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ec8b0

uint64_t SynLift_1417ec960(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ec960

uint64_t SynLift_1417eca14(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eca14

uint64_t SynLift_1417eca60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eca60

uint64_t SynLift_1417eca80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eca80

uint64_t SynLift_1417eca94(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eca94

uint64_t SynLift_1417ecd94(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ecd94

uint64_t SynLift_1417ece00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ece00

uint64_t SynLift_1417ece14(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ece14

uint64_t SynLift_1417ece60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ece60

uint64_t SynLift_1417ecec2(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ecec2

uint64_t SynLift_1417ecef5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ecef5

uint64_t SynLift_1417ecf20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ecf20

uint64_t SynLift_1417ecf80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ecf80

uint64_t SynLift_1417ed130(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ed130

uint64_t SynLift_1417ed2bb(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ed2bb

uint64_t SynLift_1417ed2e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ed2e0

uint64_t SynLift_1417ed31a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ed31a

uint64_t SynLift_1417ed344(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ed344

uint64_t SynLift_1417ed375(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ed375

uint64_t SynLift_1417ed385(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ed385

uint64_t SynLift_1417ed3ef(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ed3ef

uint64_t SynLift_1417ed43e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ed43e

uint64_t SynLift_1417ed472(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ed472

uint64_t SynLift_1417ed590(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ed590

uint64_t SynLift_1417ed5f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ed5f0

uint64_t SynLift_1417ed950(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ed950

uint64_t SynLift_1417ed990(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ed990

uint64_t SynLift_1417eda90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eda90

uint64_t SynLift_1417edb00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417edb00

uint64_t SynLift_1417edb90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417edb90

uint64_t SynLift_1417edbe0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417edbe0

uint64_t SynLift_1417edc10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417edc10

uint64_t SynLift_1417edd24(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417edd24

uint64_t SynLift_1417edd55(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417edd55

uint64_t SynLift_1417edd85(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417edd85

uint64_t SynLift_1417ede80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ede80

uint64_t SynLift_1417edfe0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417edfe0

uint64_t SynLift_1417ee030(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ee030

uint64_t SynLift_1417ee0e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ee0e0

uint64_t SynLift_1417ee210(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ee210

uint64_t SynLift_1417ee2a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ee2a0

uint64_t SynLift_1417ee354(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ee354

uint64_t SynLift_1417ee3a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ee3a0

uint64_t SynLift_1417ee3c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ee3c0

uint64_t SynLift_1417ee3d4(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ee3d4

uint64_t SynLift_1417ee644(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ee644

uint64_t SynLift_1417ee6b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ee6b0

uint64_t SynLift_1417ee6c4(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ee6c4

uint64_t SynLift_1417ee710(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ee710

uint64_t SynLift_1417ee772(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ee772

uint64_t SynLift_1417ee7a5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ee7a5

uint64_t SynLift_1417ee7d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ee7d0

uint64_t SynLift_1417ee830(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ee830

uint64_t SynLift_1417ee9f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ee9f0

uint64_t SynLift_1417eeb7b(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eeb7b

uint64_t SynLift_1417eeba0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eeba0

uint64_t SynLift_1417eebda(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eebda

uint64_t SynLift_1417eec04(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eec04

uint64_t SynLift_1417eec35(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eec35

uint64_t SynLift_1417eec45(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eec45

uint64_t SynLift_1417eecbd(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eecbd

uint64_t SynLift_1417eed86(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eed86

uint64_t SynLift_1417eedc2(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eedc2

uint64_t SynLift_1417eeee0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eeee0

uint64_t SynLift_1417eef40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eef40

uint64_t SynLift_1417ef300(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ef300

uint64_t SynLift_1417ef340(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ef340

uint64_t SynLift_1417ef430(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ef430

uint64_t SynLift_1417ef4a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ef4a0

uint64_t SynLift_1417ef520(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ef520

uint64_t SynLift_1417ef590(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ef590

uint64_t SynLift_1417ef620(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ef620

uint64_t SynLift_1417ef670(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ef670

uint64_t SynLift_1417ef6b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ef6b0

uint64_t SynLift_1417ef848(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ef848

uint64_t SynLift_1417ef8d9(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ef8d9

uint64_t SynLift_1417ef9e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ef9e0

uint64_t SynLift_1417efb40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417efb40

uint64_t SynLift_1417efb90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417efb90

uint64_t SynLift_1417efc50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417efc50

uint64_t SynLift_1417efdb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417efdb0

uint64_t SynLift_1417efe60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417efe60

uint64_t SynLift_1417eff34(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eff34

uint64_t SynLift_1417eff80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eff80

uint64_t SynLift_1417eff94(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417eff94

uint64_t SynLift_1417f0284(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f0284

uint64_t SynLift_1417f02d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f02d0

uint64_t SynLift_1417f02e4(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f02e4

uint64_t SynLift_1417f0330(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f0330

uint64_t SynLift_1417f0392(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f0392

uint64_t SynLift_1417f03c5(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f03c5

uint64_t SynLift_1417f03f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f03f0

uint64_t SynLift_1417f0450(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f0450

uint64_t SynLift_1417f05f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f05f0

uint64_t SynLift_1417f077c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f077c

uint64_t SynLift_1417f07ae(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f07ae

uint64_t SynLift_1417f07da(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f07da

uint64_t SynLift_1417f081d(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f081d

uint64_t SynLift_1417f0855(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f0855

uint64_t SynLift_1417f0865(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f0865

uint64_t SynLift_1417f08f3(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f08f3

uint64_t SynLift_1417f093e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f093e

uint64_t SynLift_1417f0976(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f0976

uint64_t SynLift_1417f0aa0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f0aa0

uint64_t SynLift_1417f0b00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f0b00

uint64_t SynLift_1417f0f40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f0f40

uint64_t SynLift_1417f0f80(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f0f80

uint64_t SynLift_1417f10a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f10a0

uint64_t SynLift_1417f1110(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f1110

uint64_t SynLift_1417f1170(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f1170

uint64_t SynLift_1417f11a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f11a0

uint64_t SynLift_1417f11e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f11e0

uint64_t SynLift_1417f1348(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f1348

uint64_t SynLift_1417f13e2(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f13e2

uint64_t SynLift_1417f1413(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f1413

uint64_t SynLift_1417f1550(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f1550

uint64_t SynLift_1417f1680(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f1680

uint64_t SynLift_1417f17c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f17c0

uint64_t SynLift_1417f1970(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f1970

uint64_t SynLift_1417f1db0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f1db0

uint64_t SynLift_1417f1de0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f1de0

uint64_t SynLift_1417f1e50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f1e50

uint64_t SynLift_1417f1f00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f1f00

uint64_t SynLift_1417f2024(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f2024

uint64_t SynLift_1417f2060(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f2060

uint64_t SynLift_1417f2080(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f2080

uint64_t SynLift_1417f2094(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f2094

uint64_t SynLift_1417f20e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f20e0

uint64_t SynLift_1417f2224(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f2224

uint64_t SynLift_1417f2280(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f2280

uint64_t SynLift_1417f2294(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f2294

uint64_t SynLift_1417f2310(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f2310

uint64_t SynLift_1417f24fc(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f24fc

uint64_t SynLift_1417f252e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f252e

uint64_t SynLift_1417f293a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f293a

uint64_t SynLift_1417f29e7(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f29e7

uint64_t SynLift_1417f2a15(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f2a15

uint64_t SynLift_1417f2a25(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f2a25

uint64_t SynLift_1417f2b1a(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f2b1a

uint64_t SynLift_1417f2b70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f2b70

uint64_t SynLift_1417f2cc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f2cc0

uint64_t SynLift_1417f2dc0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f2dc0

uint64_t SynLift_1417f2e60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f2e60

uint64_t SynLift_1417f2ff0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f2ff0

uint64_t SynLift_1417f3130(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f3130

uint64_t SynLift_1417f3244(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f3244

uint64_t SynLift_1417f3260(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f3260

uint64_t SynLift_1417f330c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f330c

uint64_t SynLift_1417f3980(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f3980

uint64_t SynLift_1417f39b8(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f39b8

uint64_t SynLift_1417f3bdc(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f3bdc

uint64_t SynLift_1417f3d6c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f3d6c

uint64_t SynLift_1417f4220(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f4220

uint64_t SynLift_1417f4290(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f4290

uint64_t SynLift_1417f4310(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f4310

uint64_t SynLift_1417f4340(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f4340

uint64_t SynLift_1417f4390(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f4390

uint64_t SynLift_1417f43d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f43d0

uint64_t SynLift_1417f4400(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f4400

uint64_t SynLift_1417f4450(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f4450

uint64_t SynLift_1417f4500(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f4500

uint64_t SynLift_1417f4540(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f4540

uint64_t SynLift_1417f45c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f45c0

uint64_t SynLift_1417f4600(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f4600

uint64_t SynLift_1417f4640(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f4640

uint64_t SynLift_1417f4680(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f4680

uint64_t SynLift_1417f46c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f46c0

uint64_t SynLift_1417f4700(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f4700

uint64_t SynLift_1417f4740(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f4740

uint64_t SynLift_1417f4860(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f4860

uint64_t SynLift_1417f4d60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f4d60

uint64_t SynLift_1417f5180(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f5180

uint64_t SynLift_1417f51e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f51e0

uint64_t SynLift_1417f5230(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f5230

uint64_t SynLift_1417f5260(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f5260

uint64_t SynLift_1417f5290(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f5290

uint64_t SynLift_1417f52f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f52f0

uint64_t SynLift_1417f5330(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f5330

uint64_t SynLift_1417f53c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f53c0

uint64_t SynLift_1417f5430(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f5430

uint64_t SynLift_1417f5450(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f5450

uint64_t SynLift_1417f5470(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f5470

uint64_t SynLift_1417f54b0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f54b0

uint64_t SynLift_1417f54e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f54e0

uint64_t SynLift_1417f5500(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f5500

uint64_t SynLift_1417f5530(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f5530

uint64_t SynLift_1417f5580(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f5580

uint64_t SynLift_1417f55d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f55d0

uint64_t SynLift_1417f55f0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f55f0

uint64_t SynLift_1417f5620(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f5620

uint64_t SynLift_1417f5640(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f5640

uint64_t SynLift_1417f5710(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f5710

uint64_t SynLift_1417f5750(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f5750

uint64_t SynLift_1417f5770(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f5770

uint64_t SynLift_1417f57c0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f57c0

uint64_t SynLift_1417f5910(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f5910

uint64_t SynLift_1417f59a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f59a0

uint64_t SynLift_1417f5e60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f5e60

uint64_t SynLift_1417f8d10(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417f8d10

uint64_t SynLift_1417fbc70(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417fbc70

uint64_t SynLift_1417ff750(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1417ff750

uint64_t SynLift_1418014a0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1418014a0

uint64_t SynLift_1418016d0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1418016d0

uint64_t SynLift_141804720(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141804720

uint64_t SynLift_14180beb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14180beb0

uint64_t SynLift_14180cf40(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14180cf40

uint64_t SynLift_14180d090(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14180d090

uint64_t SynLift_14180d1e0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14180d1e0

uint64_t SynLift_14180d780(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14180d780

uint64_t SynLift_14180da30(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14180da30

uint64_t SynLift_14180da90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14180da90

uint64_t SynLift_14180dc20(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14180dc20

uint64_t SynLift_14180dc90(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14180dc90

uint64_t SynLift_14180dce0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14180dce0

uint64_t SynLift_14180dfb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14180dfb0

uint64_t SynLift_14180e030(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14180e030

uint64_t SynLift_14180e560(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14180e560

uint64_t SynLift_14180eac0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14180eac0

uint64_t SynLift_141810840(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141810840

uint64_t SynLift_14181d510(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14181d510

uint64_t SynLift_14181dc60(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14181dc60

uint64_t SynLift_14181df00(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14181df00

uint64_t SynLift_14181edb0(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14181edb0

uint64_t SynLift_14181ee50(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14181ee50

uint64_t SynLift_14182161c(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14182161c

uint64_t SynLift_141821635(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141821635

uint64_t SynLift_141821674(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141821674

uint64_t SynLift_14182169e(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x14182169e

uint64_t SynLift_1418216cb(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x1418216cb

uint64_t SynLift_141821720(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141821720

uint64_t SynLift_141821741(uint64_t rcxA, uint64_t rdxA, uint64_t r8A, uint64_t r9A);   // 0x141821741
// seams: an indirect call the bodies make out of the image (import thunks and other bodies)
extern uint64_t (*g_fnLIFT_141721110)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141721230)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141721350)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141721370)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141721390)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417213a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417213b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417213c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417213d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417214a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417215d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141721780)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141721a40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141721b50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141721cf0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417224f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141722680)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417227e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141722c70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141722ef0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141722fc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141723090)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141723200)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141723a50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141724870)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141724950)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417249e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141724c50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141724cb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141724d10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141724ed0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141725000)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141725060)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417250d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141725170)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141725260)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417253c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141725420)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141725d00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141725e80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141726210)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417262c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141726310)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141726360)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141726430)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417264d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141726c30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417270a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417272d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141727310)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141727380)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141727450)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141727490)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141727640)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417276c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141727740)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417277c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141727e60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141728290)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141728750)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141728b10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141728dc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417293c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141729790)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141729ba0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172a070)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172a410)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172a5c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172acb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172acf0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172ae00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172afb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172b160)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172b520)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172b6c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172b870)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172bc30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172bd00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172c0c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172c560)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172c600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172c920)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172cf70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172cfe0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172d120)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172da60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172db90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172e030)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172e230)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172e3f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172e5a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172e760)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172e910)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172eae0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172ecb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172f500)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172f970)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14172fdb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417309d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141730b10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141730cd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141730e80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141730ff0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417310e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417311d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417317b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141732040)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141732200)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417322b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417325f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417329f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141733480)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141733570)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141733630)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417336b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141733a00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141734360)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141734c90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141734ee0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141734f50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141735100)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417356b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141735800)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141735880)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141735a60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141735bb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141735c80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417360a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141736400)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417364e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141736750)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417369c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141736d40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417384e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141739810)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173a450)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173a680)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173abf0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173b0e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173b140)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173b240)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173b6c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173b830)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173b890)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173bc00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173bc60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173bcb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173bd10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173bf40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173c0b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173c470)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173c4f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173c5c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173cb90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173cd80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173ce30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173cea0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173d1e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173d330)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173d440)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173d9c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173de50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173df20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173e240)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173e350)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173e790)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173eb10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173ecf0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173ed60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173ef10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173ef80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173f0c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173f450)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173f490)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173f4b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173f600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173f680)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173f9c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173fcc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14173fd70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141740250)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141740390)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141740860)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141740e10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141740fd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417418b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141741a30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141741af0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141741c50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141741d50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141742170)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141742320)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141742810)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141742b10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141742e50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141742fc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417431c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141743330)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417434f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141743b60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141743c80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141743cb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141743d10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141743dd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141743e60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141743e70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141743e80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141743f20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141743f90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417440d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141744130)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417441e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417441f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141744210)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141744560)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417447d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141744b50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141744cb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141745480)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141745520)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141745760)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141745920)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141745ad0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141745c30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141745c90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141745f80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417461f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141746310)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417463a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141746480)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141746600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141746650)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141746a00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141746d00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141746e20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141747090)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417471f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141747270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141747400)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417477c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141747c80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141747ec0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417481d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417483e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141748720)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141748820)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141748dd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141748e30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141748ea0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141749040)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141749240)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141749410)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417495d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141749690)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141749840)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141749980)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141749a50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141749c00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174a350)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174a650)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174a6d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174ad50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174b000)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174b360)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174b610)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174b6c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174b960)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174be40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174c0c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174c530)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174c5a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174cb10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174cc70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174cd20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174d080)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174d170)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174d3e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174d490)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174d5a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174d6b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174d830)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174d900)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174da00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174e010)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174e080)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174e3f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174e400)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174e520)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174e760)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174ea30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174ea40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174ea50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174eae0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174ed50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174ed80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174eda0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174edc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174ee00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174ee20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174ee90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174eec0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174eee0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174ef40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174ef60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174efa0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174efc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174f000)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174f060)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174f080)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174f120)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174f130)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174f930)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14174fe10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141750010)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141750670)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141750760)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141750a30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417512f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141751380)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417522a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417524d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141752760)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141752ac0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141752cd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141752d30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141752dc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141752ef0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141752f50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417530a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753100)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417531c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753220)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753320)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753380)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753470)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141753500)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
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
extern uint64_t (*g_fnLIFT_141754970)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141754a90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141754bc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141754c50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141754f50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141755490)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417555f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141755640)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141755690)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417556e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141755730)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141755f90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141755ff0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417563b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141756470)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417567f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141756920)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141756d50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141756e10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141756f00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141757060)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141757580)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141757640)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417576c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141757740)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417577c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141757840)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141757f70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141758050)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141758410)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417585d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141758a10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141758dd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141759110)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417591f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141759600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417599c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141759a90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141759ef0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175a300)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175a710)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175afd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175b200)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175bcf0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175bda0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175bfb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175c2f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175c600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175ca70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175ce90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175d2a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175d350)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175d840)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175dd50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175e260)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175ea00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175ea60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175ecb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175ee00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175efe0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175f290)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175fba0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14175fed0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417600e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417601b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141760360)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417604a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141760600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141760a20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141760af0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141760bc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141760e40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141760f10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141760fe0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141761330)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417614e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417618a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141761bd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141761c40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141761f60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141761fd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141762040)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141762360)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417623d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141762770)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141762880)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141762db0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417630d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417631d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417632e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417633b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141763680)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141763790)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417638e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141763c80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417646f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417647e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141764870)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141764990)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141765060)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141766e90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141767560)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141767670)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141767780)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141767890)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417679a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141767ab0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141767de0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141767f00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141768020)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417681d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417682f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141768410)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417689b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141768b20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141768c70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417695b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141769750)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417698d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141769a30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141769bf0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176a1a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176a5a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176aa20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176aaa0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176aae0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176aca0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176acf0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176dac0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176dc40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176dff0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176e3e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176e500)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176e600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176e8f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176ea30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176f190)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176f530)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176f990)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176fa90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14176fbf0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141770400)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141770600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141770a20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141771050)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417713d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417714e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141773cb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141773e60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141774500)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141775400)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141775680)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141776070)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141776360)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141776460)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417767b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141776900)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141776c90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141777050)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417771a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141777640)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141777970)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141777a30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141777f20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141778060)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417780a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417782c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141778330)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417785e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417786d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141778760)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417788c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141778a20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141778b60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141778d90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141778e60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141778f80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141779090)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417791e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417792a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141779670)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141779790)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417798b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141779960)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141779b60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141779eb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141779f40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177a460)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177a5c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177a860)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177aa60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177ac60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177af70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177b300)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177b650)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177b800)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177beb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177c0a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177c230)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177c4f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177c6c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177c770)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177c800)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177caa0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177cad0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177cb40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177cb90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177cd40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177cdc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177d180)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177d350)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177d3d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177d7a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177d9b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177db30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177db90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177dfe0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177eda0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177f2f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177fa90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177fad0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177fbc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14177ff70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141780330)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141780750)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417807c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141780970)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141780cb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417814c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141781860)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141781b60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141781ca0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141781eb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141781f30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141782060)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417820e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141782260)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141782480)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141782550)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141783ad0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417848f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141784cd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141785740)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417857a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141785a40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141785d00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141785dc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141785ea0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417860e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417861d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417862c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141786320)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141786380)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417863e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141786440)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417864a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141786500)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141786560)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417865c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141786620)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417866d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417867d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141786830)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141786840)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141786850)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417868c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141786960)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417869f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141786a20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141786aa0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141786c00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141786d80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141786e30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141786eb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141786f10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141786f90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787050)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417870c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787120)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787130)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787150)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787160)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787170)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417871a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417871b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417871c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787240)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417872a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787300)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787370)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787380)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787390)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417873a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787bb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787c50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787c60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787d60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787d70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787d80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787de0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787ed0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141787f90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141788040)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417886b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417887b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417888b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417889b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141788ab0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141788b60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141788c20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141789160)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417899e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141789d70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141789ea0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141789f00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141789fe0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178a040)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178a200)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178a4e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178a650)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178a6a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178ab70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178af30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178afb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178b140)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178b6c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178b790)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178b8b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178ba80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178bdc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178be70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178c1b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178c580)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178c790)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178c8e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178c9f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178ca80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178cb80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178cd30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178ce70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178d500)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178d6e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178d850)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178dba0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178dc50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178dcd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178de40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178dec0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178e200)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178e270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178e2e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178e590)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178e600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178e610)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178eb10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178ecd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178ed80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178f270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178f2d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178f3a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178f400)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178f410)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178f470)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178f4e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178f4f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178f870)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178f900)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178f960)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178f9f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178fbc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178fdc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178fe90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14178ffa0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141790100)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141790110)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141790120)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417902e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141790390)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417903d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141790a10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141790ce0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141790e10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141791080)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417917a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141791a50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141791ad0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141791b60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141791bf0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141791c60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141791f60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141792010)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141792070)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141792160)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417921c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141792240)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417923e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141792950)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417929f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141792ae0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141792b70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141792cb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141793220)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141793630)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141793980)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141793bf0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141793d50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141793e70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141793fd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141794280)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141794690)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141794770)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417948b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141794c70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141794cf0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141794e10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141795230)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141795a30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141795ca0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141795d40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141795f70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141796390)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141796480)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141796740)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417969a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141796b10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141796ce0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141796d90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417970d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141797520)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141797590)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141797630)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141797670)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417976e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141797750)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417977d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141797ce0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141797ef0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141798060)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417983e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417984e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141798650)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141798910)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141798a20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141798e90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141798f80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417990c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417991f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417993b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141799480)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417998d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141799bf0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141799c60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179a020)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179a150)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179a280)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179a500)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179a720)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179aa50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179ad50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179ba80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179bbd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179bd60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179bf60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179bf80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179c1b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179c2f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179c410)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179c610)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179c8b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179c940)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179c9d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179cb30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179cde0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179cf10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179d090)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179d140)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179d230)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179d420)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179d770)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179d950)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179db30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179e020)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179e0b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179e280)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179e390)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179e420)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179e6d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179e810)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179eb90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179ed40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179f180)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179f290)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179f650)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179f6e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179fa60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179fc00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_14179fe10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a0020)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a0230)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a0340)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a0450)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a0510)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a05d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a0760)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a0a20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a0ce0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a1180)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a28c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a2bf0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a2d20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a34d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a3690)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a3780)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a3a90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a3fe0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a4050)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a4180)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a45d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a4980)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a5170)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a51b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a51f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a5400)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a5610)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a58c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a5c70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a5d80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a5e40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a5f70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a60a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a64b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a6960)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a6a40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a6f90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a70b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a7320)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a75b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a76e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a7780)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a79e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a7d70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a8160)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a8520)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a8610)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a8c70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a8e40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a8f70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a9180)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a93c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a9520)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417a9680)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ac6e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ac6f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ac710)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ac7d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ac810)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ae7b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417aebb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417af040)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417af6c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417b0370)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417b0ea0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417b1240)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417b19c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417b2df0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417b2e20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417b52d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417b5d90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417b5e70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417b6210)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417b8210)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417b8470)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417b9010)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417b9220)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417b92b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ba4c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417bc640)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417bcd10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417bcfd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417be310)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c1180)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c45b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c4780)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c4840)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c4b60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c4c00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c4cb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c5030)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c5320)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c53c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c5420)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c5830)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c6a60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c6b30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c6bd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c6c80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c6c90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c7ff0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c81c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c8590)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c8aa0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c8f70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c9310)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c9780)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417c9b20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cab90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cad00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cad90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cade0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cb000)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cb030)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cb270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cb360)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cb450)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cb480)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cb4b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cb4e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cb510)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cb540)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cb580)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cba90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cbb60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cc2a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cc450)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cc600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ccf80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cd250)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cd3a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cd520)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ce230)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ce710)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ce880)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cec20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cef50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cf1c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cf2e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cfa30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417cfb60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0020)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0080)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0140)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d03a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0430)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0480)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d04e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0540)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d05a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0640)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d06a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0740)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d07a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0840)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d08a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0940)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d09a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0a40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0aa0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0b40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0ba0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0c40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0ca0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0d40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0da0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0f00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d0fc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d1030)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d11e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d1300)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d13d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d1840)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d1ed0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d2080)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d2110)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d24d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d2590)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d26f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d2990)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d2bc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d2f10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d2f50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d2fc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d3530)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d3680)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d3800)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d3890)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d3980)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d3cb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d3eb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d3fe0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d4100)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d4160)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d4270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d4480)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d4670)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d4870)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d4a10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d4d60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d4db0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d4e70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d4ed0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d4fd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d5070)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d50f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d5140)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d51a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d5250)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d5780)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d5e50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d5ea0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d5f00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d5f60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d60a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d6360)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d63b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d6410)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d6490)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d64c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d6640)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d66c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d6790)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d6820)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d7350)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d73a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d73e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d7440)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d75b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d7770)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d7ab0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d7b00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d7b60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d7be0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d7cb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d7d60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d80c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d8390)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d9000)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d9410)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d9460)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d94c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d9550)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d9690)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d9710)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d9900)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d9950)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d9ac0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d9b30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d9cc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d9e60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d9eb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417d9f90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417da020)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417da170)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417da210)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417da310)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417da420)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417da440)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417da860)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417da8b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417da910)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dab00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dac30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dae10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417daf60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dafb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417db010)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417db2b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417db330)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417db3a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417db450)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417db530)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417db630)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417db730)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dca60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dcaf0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dcb60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dd050)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dd230)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dd280)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dd2e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dd340)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dd4b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dd6e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dd730)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dd790)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dd9f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ddc60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ddcb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ddd10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ddf50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ddfa0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417de000)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417de080)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417de0b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417de240)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417de560)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417de610)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dea00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dea30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417defc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417df150)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417df350)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417df4e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417df630)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dfa20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dfb50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dfb90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dfbd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dfbe0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dfcd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dfd70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dfe50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dfef0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dff00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dff50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dff70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dffb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417dffe0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e0050)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e0070)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e00e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e0110)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e01f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e02c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e0320)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e0370)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e0990)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e0d30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e0da0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e0ee0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1020)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1040)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e10e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1490)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e14f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1550)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1660)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1680)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e16c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1820)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e18d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1900)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1980)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1a60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1ae0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1c20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1cd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1db0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1e10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1eb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1ec0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1ee0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1f60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e1f80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e24a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e2500)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e25b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e25c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e25f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e2610)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e2680)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e2730)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e2770)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e27f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e2890)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e28b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e28d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e2940)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e2ab0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e2ac0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e2b30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e2b90)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e2bb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e2c30)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e2c50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e2d40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e2de0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e2f10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e3060)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e3240)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e32e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e3320)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e38d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e3960)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e3a50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e3bc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e3d80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e4140)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e4550)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e45d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e46e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e47d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e48e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e4990)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e4a60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e4b80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e4cb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e4d40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e4da0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e4fb0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e4fd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e5000)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e50a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e50d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e5aa0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e5ba0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e78c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e7c50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e7c70)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e7d00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e7d20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e7d50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e7ec0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e8016)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e8050)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e8330)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e8520)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e88e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e89a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e8ea0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e93b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e9440)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e98a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417e9dc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ea4c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ea660)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417eaab0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417eafa0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417eb7c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417eb830)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ebb40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ebf80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ec320)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ec3b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ec730)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ecb40)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ed130)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ed1a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ed4d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ed880)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417edd10)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417edda0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ee070)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ee450)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ee9f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417eea60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417eee20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ef230)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ef830)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417ef8f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417efbd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f0010)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f05f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f09e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f0e60)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f1430)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f1600)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f1710)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f18b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2370)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2400)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2b80)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2d00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2f4a)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f2fdc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f30a0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f30c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f30cc)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3154)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3160)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3166)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3260)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f32ac)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f330c)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3948)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3966)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3ae0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3cc4)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3dd0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f3f50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f4220)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f4290)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f4580)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f4820)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f4b00)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f4c20)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f4dc0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f5330)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f53c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f5400)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f5450)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f5470)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f54b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f5500)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f5530)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f5560)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f5580)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f55b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f55d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f55f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f5620)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f5640)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f5750)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f57c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f5830)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f5950)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1417f5a50)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823008)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823020)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823028)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823030)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823038)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823040)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823048)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823050)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823058)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823080)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823090)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823098)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418230a8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418230b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418230b8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418230d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418230f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823108)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823120)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823128)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823130)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823138)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418231b8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418231c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418231d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418231d8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418231e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418231e8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418231f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823210)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823220)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823228)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823230)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823238)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823250)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823258)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823260)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823270)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823278)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823280)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823288)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823290)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418232a8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418232b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418232c8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418232d0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418232d8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418232f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823300)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823308)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823350)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233b0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233c8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233d8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233e0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233e8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f0)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_1418233f8)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823400)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141823418)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t (*g_fnLIFT_141887590)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

}  // namespace tq
