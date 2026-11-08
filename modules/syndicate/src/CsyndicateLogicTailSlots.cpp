// Instruction-by-instruction port of the twelve CSyndicateLogic slots described in the
// header. Nothing is inferred beyond the registers the bytes read.
#include "CsyndicateLogicTailSlots.h"

namespace tq {

static uint64_t none4(uint64_t, uint64_t, uint64_t, uint64_t) { return 0; }
static uint64_t none2(uint64_t, uint64_t) { return 0; }
static uint64_t none1(uint64_t) { return 0; }

uint64_t (*g_pfnLogic_1417cadb0)(uint64_t, uint64_t, uint64_t, uint64_t) = none4;
uint64_t (*g_pfnLogic_1417caa00)(uint64_t, uint64_t, uint64_t, uint64_t) = none4;
uint64_t (*g_pfnLogic_1417cad90)(uint64_t, uint64_t, uint64_t, uint64_t) = none4;
uint64_t (*g_pfnLogic_1417cb000)(uint64_t, uint64_t, uint64_t, uint64_t) = none4;
uint64_t (*g_pfnLogic_1417873a0)(uint64_t, uint64_t, uint64_t, uint64_t) = none4;
uint64_t (*g_pfnLogic_1417a8a50)(uint64_t, uint64_t, uint64_t, uint64_t) = none4;
uint64_t (*g_pfnLogic_1417a8940)(uint64_t, uint64_t, uint64_t, uint64_t) = none4;
uint64_t (*g_pfnLogic_14177f980)(uint64_t, uint64_t, uint64_t, uint64_t) = none4;

uint64_t (*g_pfnLogic_1417cad00)(uint64_t, uint64_t, uint64_t, uint64_t) = none4;
uint64_t (*g_pfnLogic_141797e00)(uint64_t, uint64_t) = none2;
uint64_t (*g_pfnLogic_14178f470)(uint64_t) = none1;

// 0x1417cad90: sub rsp,0x28 / call 0x1417cad00 / test rax,rax / setne al
int Slot_1417cad90(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t r = g_pfnLogic_1417cad00((uint64_t)(uintptr_t)self, rdx, r8, r9);
    return r != 0;
}

// 0x1417cadb0: mov ebx,edx / mov edx,r8d / call 0x1417cad00 / test rax,rax / jz 0
//              mov edx,ebx / mov rcx,rax / jmp 0x141797e00
// The second argument is truncated to 32 bits before the lookup, and the hit is passed on
// with the ORIGINAL id (also 32-bit) as the second argument.
uint64_t Slot_1417cadb0(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint32_t id = (uint32_t)rdx;
    uint64_t hit = g_pfnLogic_1417cad00((uint64_t)(uintptr_t)self, (uint64_t)(uint32_t)r8, r8, r9);
    if (!hit)
        return 0;
    return g_pfnLogic_141797e00(hit, (uint64_t)id);
}

// 0x1417cb000: call 0x1417cad00 / test rax,rax / jnz L7 / mov rax,0x141827409
//              L7: mov rcx,rax / jmp 0x14178f470
// Only rcx is meaningful at the tail jump: rdx/r8/r9 still hold whatever the lookup left in
// them, which is volatile state, so the seam takes rcx alone rather than forwarding garbage.
uint64_t Slot_1417cb000(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t hit = g_pfnLogic_1417cad00((uint64_t)(uintptr_t)self, rdx, r8, r9);
    uint64_t arg = hit ? hit : (uint64_t)(uintptr_t)0x141827409;
    return g_pfnLogic_14178f470(arg);
}

// 0x1417abe60: mov rcx,[rcx+0x10] / jmp 0x1417cadb0
uint64_t Slot_1417abe60(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t m = *(uint64_t*)((uint8_t*)self + 0x10);
    return g_pfnLogic_1417cadb0(m, rdx, r8, r9);
}

// 0x1417ac010: mov rcx,[rcx+0x10] / jmp 0x1417caa00
uint64_t Slot_1417ac010(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t m = *(uint64_t*)((uint8_t*)self + 0x10);
    return g_pfnLogic_1417caa00(m, rdx, r8, r9);
}

// 0x1417ab1d0: mov rcx,[rcx+0x10] / jmp 0x1417cad90
uint64_t Slot_1417ab1d0(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t m = *(uint64_t*)((uint8_t*)self + 0x10);
    return g_pfnLogic_1417cad90(m, rdx, r8, r9);
}

// 0x1417ab1c0: mov rcx,[rcx+0x10] / jmp 0x1417cb000
uint64_t Slot_1417ab1c0(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t m = *(uint64_t*)((uint8_t*)self + 0x10);
    return g_pfnLogic_1417cb000(m, rdx, r8, r9);
}

// 0x1417aeba0: mov ecx,edx / jmp 0x1417873a0 — the argument is zero-extended into rcx and
// `this` is not passed at all.
uint64_t Slot_1417aeba0(void* /*self*/, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t arg = (uint64_t)(uint32_t)rdx;
    return g_pfnLogic_1417873a0(arg, rdx, r8, r9);
}

// 0x1417aaf90: mov eax,0xf / ret
int Slot_1417aaf90(void* /*self*/) { return 0xf; }

// 0x1417aafa0: mov eax,0xf / ret
int Slot_1417aafa0(void* /*self*/) { return 0xf; }

// 0x1417abc50: cmp edx,0x3de / setge al
int Slot_1417abc50(void* /*self*/, int32_t arg) { return (arg >= 0x3de) ? 1 : 0; }

// 0x1417abc60: cmp edx,0x37a / setle al
int Slot_1417abc60(void* /*self*/, int32_t arg) { return (arg <= 0x37a) ? 1 : 0; }

// 0x1417af2f0: mov rcx,[rcx+0x20] / test rcx,rcx / jz L4 / jmp 0x1417a8a50
//              L4 sets only al, i.e. answers false.
int Slot_1417af2f0(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t m = *(uint64_t*)((uint8_t*)self + 0x20);
    if (!m)
        return 0;
    return (int)g_pfnLogic_1417a8a50(m, rdx, r8, r9);
}

// 0x1417af310: mov rcx,[rcx+0x20] / jz 0 / jmp 0x1417a8940
int Slot_1417af310(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t m = *(uint64_t*)((uint8_t*)self + 0x20);
    if (!m)
        return 0;
    return (int)g_pfnLogic_1417a8940(m, rdx, r8, r9);
}

// 0x1417afac0: mov rcx,[rcx+0x28] / jz 0 / jmp 0x14177f980
int Slot_1417afac0(void* self, uint64_t rdx, uint64_t r8, uint64_t r9) {
    uint64_t m = *(uint64_t*)((uint8_t*)self + 0x28);
    if (!m)
        return 0;
    return (int)g_pfnLogic_14177f980(m, rdx, r8, r9);
}

}  // namespace tq
