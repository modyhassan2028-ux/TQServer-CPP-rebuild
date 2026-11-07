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

// seams: an indirect call the bodies make out of the image (import thunks and other bodies)

}  // namespace tq
